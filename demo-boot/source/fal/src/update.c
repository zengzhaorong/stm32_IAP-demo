/**
  ******************************************************************************
  * @file           : update.c
  * @brief          : 升级
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
#include <string.h>
#include "update.h"
#include "cpuFlash.h"


/*****************************************************************
* 宏定义
******************************************************************/

/*****************************************************************
* 结构定义
******************************************************************/

/*****************************************************************
* 全局变量定义
******************************************************************/
Update_Status gUpdateSta;

/*****************************************************************
* 外部变量声明
******************************************************************/

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
* Desc	:	初始化
* Input	:	usSeq-顺序号 pData-数据 usDatalen-长度 pstAPPHead-APP头信息(只第一包有用)
* Output:
* Return:
*****************************************************************/
int update_packDataHandle(UINT16 usSeq, UINT8 *pData, UINT16 usDatalen, struct APP_headinfo *pstAPPHead)
{
	static INT16U		usLastSeq = 0;		// 上一次成功的序号
	static INT32U		unProgAddr = 0;		// 烧写地址
	INT32		nRet = 0;


	if(usSeq == usLastSeq)		// 重复包
		return 0;

	gUpdateSta = UPD_STA_ING;

	if(usSeq == 1)
	{
		printf("%s: ----------------- the first packet -----------------\n", __FUNCTION__);

		/* erase APP area */
		nRet = cpuflash_erase(FLASH_PAGE_APP_START, FLASH_PAGE_APP_START +pstAPPHead->unAPPSize);
		if(nRet != 0)
			return -1;

		unProgAddr = FLASH_PAGE_APP_START;
	}

	if(unProgAddr<FLASH_PAGE_APP_START || unProgAddr>=FLASH_PAGE_APP_END+FLASH_PAGE_SIZE)
		return -1;

	nRet = cpuflash_write(unProgAddr, pData, usDatalen);
	if(nRet != 0)
		return -1;

	/* 设置烧写地址偏移和升级包序号-0xFFFF表示最后一包 */
	if(usLastSeq!=0xffff && usSeq!=0xffff)
	{
		unProgAddr += usDatalen;
	}
	usLastSeq = usSeq;
	if (usLastSeq == 0xffff)
	{
		printf("%s: Recv the last packet data.\r\n", __FUNCTION__);
		usLastSeq = 0;
	}

	return 0;
}

/****************************************************************
* Func 	:
* Desc	:	获取升级状态函数
* Input	:
* Output:
* Return:
*****************************************************************/
Update_Status update_getStatus(void)
{
	return gUpdateSta;
}

/****************************************************************
* Func 	:
* Desc	:	初始化
* Input	:
* Output:
* Return:
*****************************************************************/
int update_Init(void)
{
	gUpdateSta = UPD_STA_IDLE;


	return 0;
}


