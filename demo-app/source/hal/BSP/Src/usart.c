/**
  ******************************************************************************
  * @file           : usart.c
  * @brief          : 串口
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
#include "usart.h"
#include "main.h"


/*****************************************************************
* 宏定义
******************************************************************/

/*****************************************************************
* 结构定义
******************************************************************/

/*****************************************************************
* 全局变量定义
******************************************************************/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart5;

struct uart_data	gUart1_InTTL;		// TTL串口通信数据


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
* Desc	:	串口发送数据函数
* Input	:
* Output:
* Return:
*****************************************************************/
int UART_SEND(UINT8 ucUartNum, UINT8 *pData, UINT16 usLen)
{
	UART_HandleTypeDef	*pUart = NULL;
	int nRet = 0;
	

	if(pData==NULL || usLen>UART_BUFSIZE_TX)
	{
		printf("params input is illegal!\n");
		return -1;
	}

	switch(ucUartNum)
	{
		case UART_INTTL:
			pUart = &huart1;
			break;
		case UART_DEBUG:
			pUart = &huart5;
			break;

		default:
			return -1;;
	}

	nRet = HAL_UART_Transmit(pUart, pData, usLen, usLen*3);
	if(nRet != HAL_OK)
	{
		printf("HAL UART Transmit data failed !\n");
		return -1;
	}

	return 0;
}

/****************************************************************
* Func 	:
* Desc	:	读取串口数据函数
* Input	:
* Output:
* Return:
*****************************************************************/
int UART_READ(UINT8 ucUartNum, UINT8 *pBuf, UINT16 usSize)
{
	struct uart_data	*pstUart = NULL;
	INT16U usRdPos = 0;
	INT16U usWrPos = 0;
	INT16U usRdLen = 0;
	INT16U usLen = 0;


	switch(ucUartNum)
	{
		case UART_INTTL:
			pstUart = &gUart1_InTTL;
			break;
		case UART_DEBUG:
			break;

		default:
			return -1;
	}

	if(pstUart == NULL)
	{
		printf("ERROR: %s: Not support this uart(NULL) !!!\n", __FUNCTION__);
		return -1;
	}

	if(pstUart->usLen > 0)
	{
		usRdPos = pstUart->usRdPos;
		usWrPos = pstUart->usWrPos;

		if(usRdPos < usWrPos)	//正序
		{
			usRdLen = (usWrPos-usRdPos>usSize ? usSize:usWrPos-usRdPos);
		
			memcpy(pBuf, &pstUart->ucRxBuf[usRdPos], usRdLen);	// copy data
			pstUart->usRdPos += usRdLen;
			pstUart->usLen -= usRdLen;
		}
		else if(usRdPos > usWrPos)	//倒序
		{
			if(usSize < (UART_BUFSIZE_RX - usRdPos))
			{
				usRdLen = usSize;
				memcpy(pBuf, &pstUart->ucRxBuf[usRdPos], usRdLen);	// copy data
				pstUart->usRdPos += usRdLen;
				pstUart->usLen -= usRdLen;
			}
			else
			{
				/* 缓存尾部数据 */
				usRdLen = UART_BUFSIZE_RX-usRdPos;
				memcpy(pBuf, &pstUart->ucRxBuf[usRdPos], usRdLen);	// copy data
				pstUart->usRdPos = 0;
				pstUart->usLen -= usRdLen;
		
				/* 缓存头部数据 */
				usLen = (usWrPos>usSize-usRdLen ? usSize-usRdLen:usWrPos);
				memcpy(pBuf+usRdLen, &pstUart->ucRxBuf[0], usLen);	// copy data
				pstUart->usRdPos += usLen;
				pstUart->usLen -= usLen;
				usRdLen += usLen;
			}
		}
		else
		{
			pstUart->usRdPos = pstUart->usWrPos;
			pstUart->usLen = 0;
		}
	
	}

	return (int)usRdLen;
}

/****************************************************************
* Func 	:
* Desc	:	串口数据接收函数
* Input	:
* Output:
* Return:
*****************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	struct uart_data	*pstUart = NULL;
	int	nRet = 0;


	if(huart == &huart1)
	{
		pstUart = &gUart1_InTTL;
	}
	else if(huart == &huart5)
	{
	}
	else
		return ;

	if(pstUart == NULL)
		return ;

	pstUart->usLen ++;
	pstUart->usWrPos ++;
	if(pstUart->usWrPos >= UART_BUFSIZE_RX)
	{
		pstUart->usWrPos = 0;
	}
	/*增加--若写指针赶上了读指针，读指针往后偏移*/
	if(pstUart->usWrPos == pstUart->usRdPos)
	{
		pstUart->usRdPos ++;
		if(pstUart->usRdPos >= UART_BUFSIZE_RX)
		{
			pstUart->usRdPos = 0;
		}
	}

	/* 重新开启中断 */
	nRet = HAL_UART_Receive_IT(huart, &pstUart->ucRxBuf[pstUart->usWrPos], 1);
	pstUart->ucIT_flag = (nRet==HAL_OK ? 0:1);
	if(nRet != HAL_OK)
	{
		printf("%s: HAL_UART_Receive_IT huart failed\n", __FUNCTION__);
	}

}

/****************************************************************
* Func 	:
* Desc	:	串口异常处理函数
* Input	:
* Output:
* Return:
*****************************************************************/
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	struct uart_data	*pstUart = NULL;
	int	nRet = 0;

	if(huart->ErrorCode == HAL_UART_ERROR_NONE)
		return ;

	printf("%s: ---------- debug enter ++ [Err: %d] ----------\n", __FUNCTION__, huart->ErrorCode);

	/* It is cleared by a software sequence (an read to the USART_SR register 
		followed by a read to the USART_DR register) */
	switch(huart->ErrorCode == HAL_UART_ERROR_NONE)
	{
		case HAL_UART_ERROR_PE:		// Parity error
			__HAL_UART_CLEAR_PEFLAG(huart);
			break;
		case HAL_UART_ERROR_NE:		// Noise error
			__HAL_UART_CLEAR_NEFLAG(huart);
			break;
		case HAL_UART_ERROR_FE:		// Frame error
			__HAL_UART_CLEAR_FEFLAG(huart);
			break;
		case HAL_UART_ERROR_ORE:	// Overrun error
			__HAL_UART_CLEAR_OREFLAG(huart);
			break;
			
		case HAL_UART_ERROR_DMA:	// DMA transfer error
			break;

		default:
			break;
	}

	if(huart == &huart1)
	{
		pstUart = &gUart1_InTTL;
		MX_USART1_UART_Init();
	}
	else if(huart == &huart5)
	{
		MX_UART5_Init();
	}
	else
		return ;

	if(pstUart == NULL)
		return ;

	/* 重新开启中断 */
	nRet = HAL_UART_Receive_IT(huart, &pstUart->ucRxBuf[pstUart->usWrPos], 1);
	pstUart->ucIT_flag = (nRet==HAL_OK ? 0:1);
	if(nRet != HAL_OK)
	{
		pstUart->ucIT_flag = 1;
		printf("%s: HAL_UART_Receive_IT huart failed\n", __FUNCTION__);
	}

}

/****************************************************************
* Func 	:
* Desc	:	串口初始化函数
* Input	:
* Output:
* Return:
*****************************************************************/
void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/****************************************************************
* Func 	:
* Desc	:	串口初始化函数
* Input	:
* Output:
* Return:
*****************************************************************/
void MX_UART5_Init(void)
{

  /* USER CODE BEGIN UART5_Init 0 */

  /* USER CODE END UART5_Init 0 */

  /* USER CODE BEGIN UART5_Init 1 */

  /* USER CODE END UART5_Init 1 */
  huart5.Instance = UART5;
  huart5.Init.BaudRate = 115200;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART5_Init 2 */

  /* USER CODE END UART5_Init 2 */

}

/****************************************************************
* Func 	:
* Desc	:	串口初始化函数
* Input	:
* Output:
* Return:
*****************************************************************/
void MX_UART_Init(void)
{
	int nRet = 0;

	MX_USART1_UART_Init();
	MX_UART5_Init();

	memset(&gUart1_InTTL, 0, sizeof(struct uart_data));
	nRet = HAL_UART_Receive_IT(&huart1, &gUart1_InTTL.ucRxBuf[gUart1_InTTL.usWrPos], 1);
	gUart1_InTTL.ucIT_flag = (nRet==HAL_OK ? 0:1);
	
}


/****************************************************************
* Func 	:
* Desc	:	重定向串口，使用printf 打印调试信息
* Input	:
* Output:
* Return:
*****************************************************************/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart5, (uint8_t *)&ch, 1, 100); 

  return ch;
}

/******************************************************************/
/**
 * 打印16进制的信息到调试串口\n
 *
 * @param[in]   
 * @param[out]    
 * @return     
 * 
 * @author:        GXX
 * @date           2017-02-16
 *
 * @par Modification History
 * @par Author: 
 * @par Date: 
 * @par Description: 
 * 
 * @note  
 *
 * @see 
 */
/******************************************************************/
void printHex(char *pBuff, int nlen, char *pTempBuf)
{
	 int i = 0;

     if(pTempBuf != NULL)
     {
        printf("%s", pTempBuf);
     }
     
	 for(i=0; i<nlen; i++)
	 {
		printf("%02x ", pBuff[i]);
	 }
     printf("\r\n\r\n");

}

