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
int check_paramInfo(UINT32 unParamAddr)
{
	struct param_info		stParams = {0};

	/* 读取参数 */
	memset(&stParams, 0, sizeof(struct param_info));
	cpuflash_read(unParamAddr, (UINT8 *)&stParams, sizeof(struct param_info));
	if(stParams.usStartFlag == BOOT_FLAG_FORCE_RUNAPP)		// 强制启动成功-置位正常启动
	{
		stParams.usStartFlag = BOOT_FLAG_NORMAL_RUNAPP;
		printf("%s: ------------ set param flag to normal run APP ------------\n", __FUNCTION__);
		
		/* 写入参数 */
		cpuflash_erase(unParamAddr, unParamAddr);
		cpuflash_write(unParamAddr, (UINT8 *)&stParams, sizeof(struct param_info));
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

	/* 检查参数 */
	check_paramInfo(FLASH_PAGE_PARAM_START);

	return 0;
}


