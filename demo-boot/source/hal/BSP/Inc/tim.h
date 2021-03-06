/**
  ******************************************************************************
  * @file           : tim.h
  * @brief          : header file
  ******************************************************************************
  * @attention
  *
  * Copyright: https://blog.csdn.net/qq_30155503
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef _TIM_H_
#define _TIM_H_

/*****************************************************************
* 包含头文件
******************************************************************/
#include "stm32f1xx_hal.h"
#include "typedef.h"

/*****************************************************************
* 宏定义
******************************************************************/

// 定时相关参数
#define TIMER_MARK_MAX					3		// 标志器个数
#define TIMER_LEVEL_LOW					0		// 定时等级 - 低优先级          (也用于数组下标)
#define TIMER_LEVEL_MID					1
#define TIMER_LEVEL_HIGH				2
//定时时间片
#define MARK_TIMEOUT_LOW				2000	//2000ms
#define MARK_TIMEOUT_MID				200		//200ms
#define MARK_TIMEOUT_HIGH				10		//10ms

/*****************************************************************
* 结构、枚举定义
******************************************************************/
struct timer_mark
{
	UINT16		usCount;	// 计数器 1ms计1次
	UINT8		ucFlag;		// 标志：0-not ready; 1-Ready
	UINT16		usSize;		// 大小 ms
};

/*****************************************************************
* 全局变量声明
******************************************************************/

/*****************************************************************
* 函数原型声明
******************************************************************/
INT32 Timer_CheckMark(UINT8 ucFlag);
void Timer_ParamInit(void);

void MX_TIM3_Init(void);


#endif
