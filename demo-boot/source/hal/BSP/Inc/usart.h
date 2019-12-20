/**
  ******************************************************************************
  * @file           : usart.h
  * @brief          : header file
  ******************************************************************************
  * @attention
  *
  * Copyright: https://blog.csdn.net/qq_30155503
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef _USART_H_
#define _USART_H_

/*****************************************************************
* 包含头文件
******************************************************************/
#include "stm32f1xx_hal.h"
#include "typedef.h"

/*****************************************************************
* 宏定义
******************************************************************/
#define UART_BUFSIZE_RX 		512
#define UART_BUFSIZE_TX 		512

#define UART_INTTL				1
#define UART_DEBUG				5

#define UART_MAX_CNT			2		// UART数量

/*****************************************************************
* 结构、枚举定义
******************************************************************/
struct uart_data
{
	UINT8 		ucRxBuf[UART_BUFSIZE_RX];		// 接收环形缓冲区
	//UINT8 		ucTxBuf[UART_BUFSIZE_TX];		// 发送缓冲区
	UINT16 		usRdPos;						// 环形接收缓冲区读位置
	UINT16 		usWrPos;						// 环形接收缓冲区写位置
	UINT16 		usLen;							// 数据长度
	UINT8		ucIT_flag;						// 中断开启标志 0-成功开启
};

/*****************************************************************
* 全局变量声明
******************************************************************/

/*****************************************************************
* 函数原型声明
******************************************************************/
int UART_SEND(UINT8 ucUartNum, UINT8 *pData, UINT16 usLen);
int UART_READ(UINT8 ucUartNum, UINT8 *pBuf, UINT16 usSize);

void MX_USART1_UART_Init(void);
void MX_UART5_Init(void);
void MX_UART_Init(void);
void printHex(char *pBuff, int nlen, char *pTempBuf);


#endif
