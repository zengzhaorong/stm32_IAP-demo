/**
  ******************************************************************************
  * @file			: gxxServer.h
  * @brief			: header file
  ******************************************************************************
  * @attention
  *
  * Copyright: https://blog.csdn.net/qq_30155503
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef _GXX_SERVER_H_
#define _GXX_SERVER_H_

/*****************************************************************
* 包含头文件
******************************************************************/
#include "typedef.h"
#include "RingBuffer.h"

/*****************************************************************
* 宏定义
******************************************************************/


#define SVR_RECVBUF_LEN					1024
#define GXX_PROTO_MAX_LEN				1024				// GXX协议最大长度


/*****************************************************************
* 结构、枚举定义
******************************************************************/

struct gxxServer_Info
{
	UINT8						ucUart;							// 串口号
	UINT8						ucState;						// 状态 0-发送 1-接收
	struct RingBuffer			RingBuf_In;						// 接收环形缓冲区
	struct RingBuffer			RingBuf_Out;					// 发送环形缓冲区
	//struct pack_Detect		packDetect;						// 协议包检测结果
    UINT8                     	recvBuf[GXX_PROTO_MAX_LEN];		// 接收的协议包
   	UINT16						usRecvLen;						// packBuf数据长度
    INT8U                     	sendBuf[GXX_PROTO_MAX_LEN];		// 当前要发送的数据
    UINT16						usSendLen;						// packBuf数据长度
};

/* 服务器管理结构 */
struct server_Mngr
{
	UINT8						coTaskFlag;					// 协处理标志 0-无 1-启动
	UINT32						coTaskNum;					// 协处理任务号 (协议号)
	struct gxxServer_Info		*pSvrInfo;					// 协议通信服务端结构
};


/*****************************************************************
* 全局变量声明
******************************************************************/

/*****************************************************************
* 函数原型声明
******************************************************************/
int gxxSvr_SendPack(INT8U *pPack, UINT16 nPackLen);
void gxxServer_startCoTask(int nTaskNum);
void gxxServer_Task(void);
int gxxServer_Init(void);

#endif
