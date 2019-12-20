/**
  ******************************************************************************
  * @file           : BSP.c
  * @brief          : 板级资源 - Board Support Package
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
#include "BSP.h"
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "tim.h"


/*****************************************************************
* 宏定义
******************************************************************/

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
extern TIM_HandleTypeDef htim4;

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
* Desc	:	时钟初始化
* Input	:
* Output:
* Return:
*****************************************************************/
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/****************************************************************
* Func 	:
* Desc	:	板级初始化-Board Support Package
* Input	:
* Output:
* Return:
*****************************************************************/
void BSP_Init(void)
{
	
	/* MCU Configuration--------------------------------------------------------*/
	
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();
	
	/* Configure the system clock */
	SystemClock_Config();
	
	/* Initialize all configured peripherals */
	
	/* Initialize GPIO */
	MX_GPIO_Init();
	
	/* Initialize usart */
	MX_UART_Init();

	/* Initialize timer */
	Timer_ParamInit();
	MX_TIM3_Init();

}

/****************************************************************
* Func 	:
* Desc	:	系统重启
* Input	:
* Output:
* Return:
*****************************************************************/
void reboot(void)
{
    printf("reboot ...\r\n");
    // __set_FAULTMASK(1);     /* 关闭所有中断 */
    HAL_NVIC_SystemReset();     /* 复位 */
}


