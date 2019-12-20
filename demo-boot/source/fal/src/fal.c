/**
  ******************************************************************************
  * @file           : fal.c
  * @brief          : 功能层 - functional layer
  ******************************************************************************
  * @attention
  *
  * Copyright: https://blog.csdn.net/qq_30155503
  * All rights reserved.
  *
  ******************************************************************************
  */

/*****************************************************************
* 包含头文件
******************************************************************/
#include <stdio.h>
#include <string.h>
#include "BSP.h"
#include "fal.h"
#include "cpuFlash.h"
#include "update.h"
#include "public.h"



/*****************************************************************
* 宏定义
******************************************************************/
#define IS_NVIC_VECTTAB(VECTTAB) (((VECTTAB) == SRAM_BASE) || \
										  ((VECTTAB) == FLASH_BASE))
										  
#define IS_NVIC_OFFSET(OFFSET)  ((OFFSET) < 0x000FFFFF)

/*****************************************************************
* 结构定义
******************************************************************/

/*****************************************************************
* 全局变量定义
******************************************************************/

/*****************************************************************
* 外部变量声明
******************************************************************/
extern TIM_HandleTypeDef htim3;

/*****************************************************************
* 静态变量定义
******************************************************************/

/*****************************************************************
* 函数原型声明
******************************************************************/

/*****************************************************************
* 函数定义
******************************************************************/


/****************************************************************
* Func 	:
* Desc	:	中断向量表重映射
* Input	:	flash中断向量地址(一般为0x08000000U)、偏移地址(flash程序烧写地址相对NVIC_VectTab偏移)
* Output:
* Return:
*****************************************************************/
void NVIC_SetVectorTable(UINT32 NVIC_VectTab, UINT32 Offset)
{
  /* Check the parameters */
  assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
  assert_param(IS_NVIC_OFFSET(Offset));

  SCB->VTOR = NVIC_VectTab | (Offset & (UINT32)0x1FFFFF80);
}

/****************************************************************
* Func 	:
* Desc	:	校验APP数据函数
* Input	:	APP区起始地址、APP运行地址
* Output:
* Return:
*****************************************************************/
int check_AppInfo(UINT32 unAppAddr, UINT32 unAppRunOffset)
{
	struct APP_headinfo		stAppHead = {0};
	UINT16	usCrcVal = 0;
	INT32	nRet = 0;

	nRet = cpuflash_read(unAppAddr, (UINT8 *)&stAppHead, sizeof(struct APP_headinfo));
	if(nRet != 0)
		return -1;

	if(stAppHead.unAPPSize<1 || stAppHead.unAPPSize > (FLASH_PAGE_APP_END+FLASH_PAGE_SIZE-FLASH_PAGE_APP_START))
		return -1;

	/* 检查CRC校验 */
	usCrcVal = crc16(0, (UINT8 *)(unAppAddr +unAppRunOffset), stAppHead.unAPPSize);
	if(usCrcVal != stAppHead.unCrcCheck)
	{
		printf("ERROR: %s: APP Crc error! %d : %d\n", __FUNCTION__, usCrcVal, stAppHead.unCrcCheck);
		return -1;
	}

	return 0;
}

/****************************************************************
* Func 	:
* Desc	:	加载APP
* Input	:	APP运行地址
* Output:
* Return:
*****************************************************************/
void loadAPP(INT32U unLoadAddr)
{
	void (*fnJump2APP)(void);
	INT32U	unJumpAddr;
	
	if(((*(__IO INT32U *)unLoadAddr) & 0x2FFE0000) == 0x20000000)	/* 检查栈顶地址是否合法 */
	{
		printf("%s: ----------------------> run APP addr: 0x%x\r\n", __FUNCTION__, unLoadAddr);

		/* 用户代码区第5~8字节为程序开始地址(复位地址) */
		unJumpAddr = *(__IO INT32U *)(unLoadAddr + 4);
		fnJump2APP = (void (*)(void))unJumpAddr;
		/* 初始化APP堆栈指针(用户代码区的前4个字节用于存放栈顶地址) */
		__set_MSP(*(__IO INT32U *)unLoadAddr);
		fnJump2APP();
	}
	else
	{
		printf("ERROR: %s: Stack top address is not valid! Can not run func!\r\n", __FUNCTION__);
		while(1);
	}
}

/****************************************************************
* Func 	:
* Desc	:	强制加载APP
* Input	:	参数区地址、APP区地址、APP运行地址
* Output:
* Return:
*****************************************************************/
int force_loadAPP(UINT32 unParamAddr, UINT32 unAppAddr, UINT32 unAppRunOffset)
{
	struct param_info		stParams = {0};

	printf("%s: ----------> enter ...\n", __FUNCTION__);

	/* 检查参数区-判断启动APP/升级? */
	memset(&stParams, 0, sizeof(struct param_info));
	cpuflash_read(unParamAddr, (UINT8 *)&stParams, sizeof(struct param_info));


	stParams.usStartFlag = BOOT_FLAG_FORCE_RUNAPP;		// 置位-强制启动
	cpuflash_erase(unParamAddr, unParamAddr);
	cpuflash_write(unParamAddr, (UINT8 *)&stParams, sizeof(struct param_info));

	HAL_TIM_Base_Stop_IT(&htim3);	// ??? 不关中断跳转不了-原因未明
	loadAPP(unAppAddr +unAppRunOffset);

	return 0;
}

/****************************************************************
* Func 	:
* Desc	:	检验flash参数区函数
* Input	:	参数区地址、APP地址、APP运行地址
* Output:
* Return:
*****************************************************************/
int check_paramInfo(UINT32 unParamAddr, UINT32 unAppAddr, UINT32 unAppRunOffset)
{
	struct param_info		stParams = {0};
	INT32		nRetAppHead = 0;

	/* 检查参数区-判断启动APP/升级? */
	memset(&stParams, 0, sizeof(struct param_info));
	cpuflash_read(unParamAddr, (UINT8 *)&stParams, sizeof(struct param_info));
	if(stParams.usStartFlag == BOOT_FLAG_NORMAL_RUNAPP)		// 直接跳转APP
	{
		/* APP校验 */
		nRetAppHead = check_AppInfo(unAppAddr, unAppRunOffset);
		if(nRetAppHead == 0)
		{
			HAL_TIM_Base_Stop_IT(&htim3);	// ??? 不关中断跳转不了-原因未明
			loadAPP(unAppAddr +unAppRunOffset);
		}
		else
		{
			printf("%s: check_AppInfo failed, [may be crc error] !\n", __FUNCTION__);
		}
	}

	/* 若参数/APP头信息错误-尝试强制启动 */
	if(stParams.usStartFlag==BOOT_FLAG_WAIT_UPGRADE || stParams.usStartFlag==BOOT_FLAG_FORCE_RUNAPP)
	{
		printf("%s: ------------ wait to upgrade ------------\n", __FUNCTION__);
	}
	else
	{
		force_loadAPP(unParamAddr, unAppAddr, unAppRunOffset);
	}

	return 0;
}

/****************************************************************
* Func 	:
* Desc	:	初始化FAL层
* Input	:
* Output:
* Return:
*****************************************************************/
int  fal_Init(void)
{

	/* cpu内部flash初始化 */
	cpuflash_Init();

	/* 检查参数-启动/升级? */
	check_paramInfo(FLASH_PAGE_PARAM_START, FLASH_PAGE_APP_START, FLASH_APP_HEAD_SIZE);

	return 0;
}


