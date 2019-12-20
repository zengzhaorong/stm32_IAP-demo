/**
  ******************************************************************************
  * @file           : tim.c
  * @brief          : 定时器
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
#include "tim.h"
#include "main.h"
#include "usart.h"


/*****************************************************************
* 宏定义
******************************************************************/

/*****************************************************************
* 结构定义
******************************************************************/

/*****************************************************************
* 全局变量定义
******************************************************************/
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

struct timer_mark	gTimerMask[TIMER_MARK_MAX] = {0};

/*****************************************************************
* 外部变量声明
******************************************************************/

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart5;

extern struct uart_data	gUart1_InTTL;		// TTL串口通信数据

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
* Desc	:	TIM定时器初始化
* Input	:	
* Output:
* Return:
*****************************************************************/
void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 72-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1000-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */
  HAL_TIM_Base_Start_IT(&htim3);

  /* USER CODE END TIM3_Init 2 */

}

/****************************************************************
* Func 	:
* Desc	:	TIM定时器参数初始化
* Input	:	
* Output:
* Return:
*****************************************************************/
void Timer_ParamInit(void)
{
	int i = 0;

	/* Mark Timer init */
	for(i=0; i<TIMER_MARK_MAX; i++)
	{
		gTimerMask[i].ucFlag = 0;
		gTimerMask[i].usCount = 0;
	}
	gTimerMask[TIMER_LEVEL_LOW].usSize = MARK_TIMEOUT_LOW;
	gTimerMask[TIMER_LEVEL_MID].usSize = MARK_TIMEOUT_MID;
	gTimerMask[TIMER_LEVEL_HIGH].usSize = MARK_TIMEOUT_HIGH;


}

/****************************************************************
* Func 	:
* Desc	:	检查定时器超时标志
* Input	:	
* Output:
* Return:
*****************************************************************/
INT32 Timer_CheckMark(UINT8 ucFlag)
{

	/* 定时是否到达 */
	if(gTimerMask[ucFlag%TIMER_MARK_MAX].ucFlag)
	{
		gTimerMask[ucFlag%TIMER_MARK_MAX].ucFlag = 0;
		gTimerMask[ucFlag%TIMER_MARK_MAX].usCount = 0;
		
		return 0;
	}

	return -1;
}

/****************************************************************
* Func 	:
* Desc	:	定时器回调函数(系统函数)
* Input	:	
* Output:
* Return:
*****************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	void (*pFunc[UART_MAX_CNT])(void) = {MX_USART1_UART_Init, MX_UART5_Init};;
	struct uart_data	*pstUart[UART_MAX_CNT] = {&gUart1_InTTL, NULL};
	UART_HandleTypeDef	*phuart[UART_MAX_CNT] = {&huart1, &huart5};
	int nIndex = 0;
	int nRet = 0;

	/* tim3 处理需要定时器协助的任务 */
	if(htim->Instance == htim3.Instance)
	{
		/* timer定时标志器处理 */
		for(nIndex=0; nIndex<TIMER_MARK_MAX; nIndex++)
		{
			gTimerMask[nIndex].usCount ++;
			if(gTimerMask[nIndex].usCount >= gTimerMask[nIndex].usSize)
			{
				gTimerMask[nIndex].ucFlag = 1;
			}
		}


		/* 处理串口相关 */
		for(nIndex=0; nIndex<UART_MAX_CNT; nIndex++)
		{
			if(pstUart[nIndex] == NULL)
				continue;
			if(pstUart[nIndex]->ucIT_flag)
			{
				pFunc[nIndex]();	// 重新初始化
				nRet = HAL_UART_Receive_IT(phuart[nIndex], &pstUart[nIndex]->ucRxBuf[pstUart[nIndex]->usWrPos], 1);
				pstUart[nIndex]->ucIT_flag = (nRet==HAL_OK ? 0:1);
				printf("%s - [ret=%d]: HAL_UART_Receive_IT huart[%d] %s\n", __FUNCTION__, nRet, nIndex, nRet==HAL_OK?"success":"failed");
			}
		}
	}

}


