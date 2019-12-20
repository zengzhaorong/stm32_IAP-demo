/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright: https://blog.csdn.net/qq_30155503
  * All rights reserved.
  *
  ******************************************************************************
  */


/** 
 * 设计说明 :　\n
 * 核心设计思想就是分层化和模块化 \n
 * 
 * 简单设计为三层:
 *  ---------------------------------------- 
 * |             PAL : 协议接入层           		| 
 * |----------------------------------------| 
 * |             FAL : 功能适配层           		| 
 * |----------------------------------------| 
 * |             HAL : 硬件适配层      		    | 
 *  ----------------------------------------
 *
 * 模块化设计:
 *  ------------------------------------------------ 
 * |                         层                      | 
 * |  -------   -------             -------         | 
 * | | 模块1 | | 模块2 |    ...    | 模块N |        | 
 * |  -------   -------             -------         | 
 *  ------------------------------------------------ 
 *
 */

/*****************************************************************
* 包含头文件
******************************************************************/
#include "main.h"
#include "BSP.h"
#include "fal.h"
#include "task.h"
#include "pal.h"
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
* Desc	:	主函数
* Input	:
* Output:
* Return:
*****************************************************************/
int main(void)
{

	/* 中断向量表重映射 */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, FLASH_PAGE_APP_START -NVIC_VectTab_FLASH +FLASH_APP_HEAD_SIZE);


	/* BSP板级资源初始化 */
	BSP_Init();

	printf("\r\n\r\n[%s]: ----------------- Hello app -----------------\r\n", __FUNCTION__);

	/* 功能层初始化 */
	fal_Init();

	/* 协议层初始化 */
	pal_Init();

	
	/* main loop */
	while (1)
	{

		/* 循环任务 */
		Task_EachRound();

		/* 高优先级任务 */
		Deal_HighRank_Task();

		/* 中优先级任务 */
		Deal_MiddleRank_Task();

		/* 低优先级任务 */
		Deal_LowRank_Task();

	}

	//return 0;
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	printf("ERROR: enter Error_Handler !!!\n");
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
