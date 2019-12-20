/**
  ******************************************************************************
  * @file           : update.h
  * @brief          : header file
  ******************************************************************************
  * @attention
  *
  * Copyright: https://blog.csdn.net/qq_30155503
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef _UPDATE_H_
#define _UPDATE_H_

/*****************************************************************
* 包含头文件
******************************************************************/
#include "stm32f1xx_hal.h"
#include "typedef.h"

/*****************************************************************
* 宏定义
******************************************************************/

/* bootloader启动标志 */
#define BOOT_FLAG_NORMAL_RUNAPP		0x0A		// 正常启动APP
#define BOOT_FLAG_WAIT_UPGRADE		0x0B		// 等待升级
#define BOOT_FLAG_FORCE_RUNAPP		0x0F		// 强制启动APP

/*****************************************************************
* 结构、枚举定义
******************************************************************/

typedef enum 
{
	UPD_STA_IDLE,
	UPD_STA_ING,
	UPD_STA_OK,
	UPD_STA_FAILED,
}Update_Status;

/* flash参数区信息结构 */
struct param_info
{
	UINT16		usStartFlag;				// 启动标志 0x0A-跳至APP 0x0B-等待升级 0x0F-已强制启动过
};

/* 升级文件头的APP信息 */
struct APP_headinfo
{
	UINT32	unVersion;				// APP版本号
	UINT32	unCrcCheck;				// CRC校验码
	UINT32	unAPPSize;	            // APP程序大小
	UINT32	unCreateTime;			// 生成时间
	UINT32	unLoadAddr;				// 加载地址
};


/*****************************************************************
* 全局变量声明
******************************************************************/

/*****************************************************************
* 函数原型声明
******************************************************************/
int update_packDataHandle(UINT16 usSeq, UINT8 *pData, UINT16 usDatalen, struct APP_headinfo *pstAPPHead);
Update_Status update_getStatus(void);

int update_Init(void);


#endif
