/**
  ******************************************************************************
  * @file			: gxxServer.c
  * @brief			: 服务器程序
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
#include "gxxServer.h"
#include "public.h"
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
struct server_Mngr		gSvrMngr = {0};
struct gxxServer_Info	gxxServerInfo = {0};


/*****************************************************************
* 外部变量声明
******************************************************************/

/*****************************************************************
* 静态变量定义
******************************************************************/
static UINT8 	gSvr_InRingBuf[SVR_RECVBUF_LEN] = {0};

/*****************************************************************
* 函数原型声明
******************************************************************/

/*****************************************************************
* 函数定义
******************************************************************/

/****************************************************************
* Func 	:
* Desc	:	发送协议数据包函数
* Input	:
* Output:
* Return:
*****************************************************************/
int gxxSvr_SendPack(INT8U *pPack, UINT16 nPackLen)
{
	struct server_Mngr		*pSvrMngr = &gSvrMngr;
	int		nRet = 0;
	

	nRet = UART_SEND(pSvrMngr->pSvrInfo->ucUart, pPack, nPackLen);

	return nRet;
}

/****************************************************************
* Func 	:
* Desc	:	读取协议数据函数
* Input	:
* Output:
* Return:
*****************************************************************/
int gxxSvr_getProtoData(struct RingBuffer *pRingBuf)
{
	struct server_Mngr		*pSvrMngr = &gSvrMngr;
	UINT8 	ucTempBuf[GXX_PROTO_MAX_LEN];
	UINT16 	nLen = 0;

	// 先取到原始数据
	nLen = UART_READ(pSvrMngr->pSvrInfo->ucUart, ucTempBuf, sizeof(ucTempBuf));
	if(nLen > 0)
	{
		/*直接写接收缓冲*/
		RingBufferWrite(&ucTempBuf[0], nLen, pRingBuf);
	}

	return 0;
}

/****************************************************************
* Func 	:
* Desc	:	协议处理函数
* Input	:
* Output:
* Return:
*****************************************************************/
int gxxSvr_protoProcess(struct gxxServer_Info *pSvrInfo, UINT8 *pPack, INT16 usPackLen)
{

	return 0;
}

/****************************************************************
* Func 	:
* Desc	:	作为服务器处理通信协议任务函数
* Input	:
* Output:
* Return:
*****************************************************************/
void gxxServer_Task(void)
{
	struct server_Mngr		*pSvrMngr = &gSvrMngr;
	INT32		nDataLen = 0;
	int 		nRet = 0;

	/* 读取协议数据 */
	gxxSvr_getProtoData(&pSvrMngr->pSvrInfo->RingBuf_In);
	nDataLen =  RingBufferLen(&pSvrMngr->pSvrInfo->RingBuf_In);
	if(nDataLen > 0)
	{
		/* 协议包检测 */
		//nRet = gxxProto_packDetect();
		if(nRet == 0)	// 检测到完整协议包
		{
			/* 协议处理 */
			gxxSvr_protoProcess(pSvrMngr->pSvrInfo, pSvrMngr->pSvrInfo->recvBuf, pSvrMngr->pSvrInfo->usRecvLen);
		}
	}

}

/****************************************************************
* Func 	:
* Desc	:	初始化函数
* Input	:
* Output:
* Return:
*****************************************************************/
int gxxServer_Init(void)
{
	struct server_Mngr		*pSvrMngr = &gSvrMngr;

	/* 结构体初始化 */
	pSvrMngr->coTaskFlag = 0;
	pSvrMngr->coTaskNum = 0;

	/* 初始化协议结构 */
	pSvrMngr->pSvrInfo = &gxxServerInfo;
	memset(pSvrMngr->pSvrInfo, 0, sizeof(struct gxxServer_Info));
	pSvrMngr->pSvrInfo->ucUart = UART_INTTL;
	InitRingBuffer(&pSvrMngr->pSvrInfo->RingBuf_In, SVR_RECVBUF_LEN, gSvr_InRingBuf);


	return 0;
}


