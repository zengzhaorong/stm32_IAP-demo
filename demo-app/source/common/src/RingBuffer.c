/******************************************************************
 ** 文件名:RingBuffer.c
 ** Copyright (c) 2012 广东高新兴通信股份有限公司嵌入式软件部
 
 ** 创建人: 朱炽冲
 ** 日  期: 2013-02-25
 ** 描  述: 实现环形缓冲区功能，从头部写，从尾部读,支持一个线程读，一个线程写
            如果要支持多个线程写，必须由外部用户控制。
 ** 版  本: V1.0

 ** 修改人:
 ** 日  期:
 ** 修改描述:
 ** 版  本: 
******************************************************************/

/*****************************************************************
* 包含头文件
******************************************************************/

//#include "includes.h"

#include "RingBuffer.h"

//#include "memPool.h"

#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus 
extern "C" { 
#endif 

/** 
 * @addtogroup Go_COMMON
 * @{ 
 */ 
 
/** 
 * @defgroup C_RINGBUFFER 环形缓冲
 * 
 * @brief \n
 * \n
 * @{ 
 */ 

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
* 静态变量定义
******************************************************************/

/*****************************************************************
* 函数原型声明
******************************************************************/

/******************************************************************/
/**
* 清空缓冲区\n 

* @param[in/out] pRingBuffer 缓冲区结构指针
* @return 返回操作结果
*   - 1   成功
*   - -1  失败

* @author:         
* @date           

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferFlush(struct RingBuffer *pRingBuffer)
{
    //CPU_TS ts;
	 //OS_ERR err;
     /*参数合法性判断*/
     if( NULL == pRingBuffer )
     {
         return -1;
     }
     /*加锁*/
     //OSMutexPend(&pRingBuffer->lock, 0, OS_OPT_PEND_BLOCKING, &ts, &err);

     pRingBuffer->pHead = pRingBuffer->pBuffer;
     pRingBuffer->pTail = pRingBuffer->pBuffer;
     
     /*解锁*/
     //OSMutexPost(&pRingBuffer->lock, OS_OPT_POST_NONE, &err);

     return 1;
}

/******************************************************************/
/**
* 获取缓冲区数据长度\n 

* @param[in] pRingBuffer 缓冲区结构指针

* @return
*  - 非-1 返回数据长度
*  - -1   失败

* @author:        朱炽冲
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferLen(struct RingBuffer *pRingBuffer)
{
    int nDataLen;
     //CPU_TS ts;
	 //OS_ERR err;

    if( NULL == pRingBuffer )
    {
        return -1;
    }

    //OSMutexPend(&pRingBuffer->lock, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
    nDataLen = (pRingBuffer->pHead >= pRingBuffer->pTail) ? (pRingBuffer->pHead - pRingBuffer->pTail)
           :(pRingBuffer->nBufferLen + (pRingBuffer->pHead - pRingBuffer->pTail));
    //OSMutexPost(&pRingBuffer->lock, OS_OPT_POST_NONE, &err);

    return nDataLen;
}

/******************************************************************/
/**
* 获取缓冲区数据长度\n 

* @param[in] pRingBuffer 缓冲区结构指针

* @return
*  - 非-1 返回数据长度
*  - -1   失败

* @author:        朱炽冲
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferEmptyLen(struct RingBuffer *pRingBuffer)
{
    int nDataLen;
     //CPU_TS ts;
	 //OS_ERR err;

    if( NULL == pRingBuffer )
    {
        return -1;
    }

    //OSMutexPend(&pRingBuffer->lock, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
    nDataLen = (pRingBuffer->pHead >= pRingBuffer->pTail) ? (pRingBuffer->nBufferLen  - (pRingBuffer->pHead - pRingBuffer->pTail))
           :(pRingBuffer->pTail - pRingBuffer->pHead);
    //OSMutexPost(&pRingBuffer->lock, OS_OPT_POST_NONE, &err);

    return nDataLen;

}

/******************************************************************/
/**
* 获取最大可读长度\n 

* @param[in] pRingBuffer  Ringbuf指针

* @return
*  - 非-1 返回实际可读的最大数据长度
*  - -1   失败

* @author:        朱炽冲
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferReadMax(struct RingBuffer *pRingBuffer)
{
    int nReadMax;
    int nDataLen;
    int nLineLen;
     //CPU_TS ts;
	 //OS_ERR err;

    if(NULL == pRingBuffer)
    {
        return -1;
    }

    //OSMutexPend(&pRingBuffer->lock, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
    nDataLen = ( pRingBuffer->pHead >= pRingBuffer->pTail) ? (pRingBuffer->pHead - pRingBuffer->pTail)
           :(pRingBuffer->nBufferLen + (pRingBuffer->pHead - pRingBuffer->pTail));

	nLineLen = pRingBuffer->pEndbuffer - pRingBuffer->pTail;

	nReadMax = min(nLineLen, nDataLen);

    //OSMutexPost(&pRingBuffer->lock, OS_OPT_POST_NONE, &err);

    return nReadMax;
}

/******************************************************************/
/**
* 获取最大可写长度\n 

* @param[in] pRingBuffer  Ringbuf指针

* @return
*  - 非-1 返回实际可写的最大数据长度
*  - -1   失败

* @author:        朱炽冲
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferWriteMax(struct RingBuffer *pRingBuffer)
{
    int nWriteMax;
    int nWriteLen;
    int nLineLen;
    int nDataLen;
     //CPU_TS ts;
	 //OS_ERR err;

    if(NULL == pRingBuffer)
    {
        return -1;
    }
    //OSMutexPend(&pRingBuffer->lock, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
    nDataLen = ( pRingBuffer->pHead >= pRingBuffer->pTail) ? (pRingBuffer->pHead - pRingBuffer->pTail)
           :(pRingBuffer->nBufferLen + (pRingBuffer->pHead - pRingBuffer->pTail));

	nWriteLen = pRingBuffer->nBufferLen - nDataLen - 1;

	nLineLen = pRingBuffer->pEndbuffer - pRingBuffer->pHead;

    nWriteMax = min(nWriteLen, nLineLen);
    //OSMutexPost(&pRingBuffer->lock, OS_OPT_POST_NONE, &err);

	return nWriteMax;
}

/******************************************************************/
/**
* 读环形缓冲区数据\n 

* @param[out] pBuffer      数据接收缓冲
* @param[in]  nLen         数据接收缓冲长度
* @param[in]  pRingBuffer  环形缓冲数据

* @return
*  - 非-1 返回成功读取的数据长度
*  - -1   失败

* @author:        朱炽冲
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferRead(unsigned char *pBuffer, int nLen,struct RingBuffer *pRingBuffer)
{
	 int nReadByte;
     int nReadLen;
     unsigned char *pData;
     //CPU_TS ts;
	 //OS_ERR err;

     /*参数合法性判断*/
     if( NULL == pBuffer || NULL == pRingBuffer )
	 {
		 return -1;
	 }
	
     /*循环读取缓冲区*/
	 nReadByte = 0;
     pData = pBuffer;

	 while (nLen > 0) 
     {
		  nReadLen = RingBufferReadMax(pRingBuffer);
		  nReadLen = min(nReadLen, nLen);
		  if (nReadLen <= 0) 
          {
			  break;
		  }

		  memcpy(pData, pRingBuffer->pTail, nReadLen);
		  pData += nReadLen;
		  nLen -= nReadLen;
		  nReadByte += nReadLen;

          /*更新尾部*/
          //OSMutexPend(&pRingBuffer->lock, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
          pRingBuffer->pTail += nReadLen;
		  if(pRingBuffer->pTail >= pRingBuffer->pEndbuffer)
          {
			  pRingBuffer->pTail  = pRingBuffer->pBuffer;
		  }
          //OSMutexPost(&pRingBuffer->lock, OS_OPT_POST_NONE, &err);
	 }
	 return nReadByte;
}

/******************************************************************/
/**
* 环形缓冲区写，只支持一个线程写\n 

* @param[in]  pBuffer      要写入环形缓冲区的数据
* @param[in]  nLen         要写入数据的字节数
* @param[in]  pRingBuffer  环形缓冲数据

* @return
*  - 非-1 返回成功写入的数据长度
*  - -1   失败

* @author:        朱炽冲
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferWrite(unsigned char *pBuffer, int nLen, struct RingBuffer *pRingBuffer)
{
	 int nWriteByte;
     int nWriteLen;
     int nDataLen;
     unsigned char *pData;

     //CPU_TS ts;
	 //OS_ERR err;
 
     /*参数合法性判断*/
     if( NULL == pBuffer || NULL == pRingBuffer )
	 {
		 return -1;
	 }

     /*写缓冲区数据*/
	 nWriteByte = 0;
     pData = pBuffer;

     nDataLen = RingBufferLen(pRingBuffer);
     if(0 == nDataLen)
     {
          RingBufferFlush(pRingBuffer);
     }

	 while (nLen > 0) 
     {
		nWriteLen = RingBufferWriteMax(pRingBuffer);
		nWriteLen = min(nWriteLen, nLen);

		if (nWriteLen <= 0) 
        {
			return nWriteByte;
		}

		memcpy(pRingBuffer->pHead,pData, nWriteLen);
		pData += nWriteLen;
		nLen -= nWriteLen;
		nWriteByte += nWriteLen;
        /*更新头部*/
        //OSMutexPend(&pRingBuffer->lock, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
        pRingBuffer->pHead += nWriteLen;
		if (pRingBuffer->pHead >= pRingBuffer->pEndbuffer) 
        {
			 pRingBuffer->pHead = pRingBuffer->pBuffer;
		}
        //OSMutexPost(&pRingBuffer->lock, OS_OPT_POST_NONE, &err);
	}

	return nWriteByte;

}

/******************************************************************/
/**
* 调整读位置\n 

* @param[in]  pRingBuffer  环形缓冲数据
* @param[in]  nSize        已读长度

* @return
*  - 1   成功
*  - -1  失败

* @author:        朱炽冲
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferReadAdj(struct RingBuffer *pRingBuffer, int nSize)
{
		//CPU_TS ts;
		//OS_ERR err;

    /*合法性判断*/
    if(NULL == pRingBuffer)
    {
        return -1;
    }
    /*调整读位置*/
    //OSMutexPend(&pRingBuffer->lock, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
		pRingBuffer->pTail += nSize;
		if(pRingBuffer->pTail >= pRingBuffer->pEndbuffer) 
    {
			pRingBuffer->pTail -= pRingBuffer->nBufferLen;
		}
    //OSMutexPost(&pRingBuffer->lock, OS_OPT_POST_NONE, &err);
    return 1;
}

/******************************************************************/
/**
* 调整写位置\n 

* @param[in]  pRingBuffer  环形缓冲数据
* @param[in]  nSize        已写长度

* @return
*  - 0   成功
*  - -1  失败

* @author:        朱炽冲
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferWriteAdj(struct RingBuffer *pRingBuffer, int nSize)
{
		//CPU_TS ts;
		//OS_ERR err;
	
    /*合法性判断*/
    if(NULL == pRingBuffer)
    {
        return -1;
    }

    /*调整写位置*/
    //OSMutexPend(&pRingBuffer->lock, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
    pRingBuffer->pHead += nSize;
	if ( pRingBuffer->pHead >= pRingBuffer->pEndbuffer)
    {
		pRingBuffer->pHead -= pRingBuffer->nBufferLen;
	}
    //OSMutexPost(&pRingBuffer->lock, OS_OPT_POST_NONE, &err);
    return 1;
}

/******************************************************************/
/**
* 初始化环形缓冲区\n 

* @param[in]  pRingBuffer  环形缓冲数据
* @param[in]  nBufferLen   数据缓冲区长度

* @return
*  - 1  返回成功读取的数据长度
*  - -1 失败

* @author:        朱炽冲
* @date           2013-02-25

* @par Modification History
* @par Author:梁靖仪
* @par Date:2017-07-27
* @par Description:去掉动态分配/释放内存;增加参数pBuffer(静态缓冲区的指针)
*/
/******************************************************************/
int InitRingBuffer(struct RingBuffer *pRingBuffer, int nBufferLen,unsigned char	 *pBuffer)
{
	//OS_ERR err;

	/*参数合法性判断*/
	if((NULL == pRingBuffer)||(NULL == pBuffer))
	{
		return (-1);
	}

	/*动态开辟缓冲区*/
	//pRingBuffer->pBuffer = malloc(nBufferLen); 

	/*静态绑定缓冲区指针到RingBuffer结构体*/
	pRingBuffer->pBuffer = pBuffer;
	
	if(NULL == pRingBuffer->pBuffer)
	{
		return (-1);
	}
	pRingBuffer->nBufferLen = nBufferLen;
	pRingBuffer->pHead = pRingBuffer->pBuffer;
	pRingBuffer->pTail = pRingBuffer->pBuffer;
	pRingBuffer->pEndbuffer = &pRingBuffer->pBuffer[nBufferLen];

	//pthread_mutex_init(&pRingBuffer->lock,NULL);
	//OSMutexCreate(&pRingBuffer->lock, "RingBuffer", &err);
	//if(err != OS_ERR_NONE)
	//{
		//return (-1);
	//}

	return (1);

}

/******************************************************************/
/**
* 释放环形缓冲区,调用该函数时，必须确保没有在其它线程使用该缓冲\n
* 区资源通常在系统结束所有线程后调用。\n 

* @param[in]  pRingBuffer  环形缓冲数据

* @return
*  - 1  返回成功读取的数据长度
*  - -1 失败

* @author:        朱炽冲
* @date           2013-02-25

* @par Modification History
* @par Author:梁靖仪
* @par Date:2017-07-27
* @par Description:去掉动态分配/释放内存
*/
/******************************************************************/
int DeInitRingBuffer(struct RingBuffer *pRingBuffer)
{
		 //OS_ERR err;
	
     /*参数合法性判断*/
     if(NULL == pRingBuffer)
     {
          return (-1);
     }

     /*清空缓冲区数据*/
     RingBufferFlush(pRingBuffer);

	 /*取消真实缓冲区与RingBuffer结构体的指针绑定*/
	 if(pRingBuffer->pBuffer != NULL)
	 {
		  //free(pRingBuffer->pBuffer);
		  pRingBuffer->pBuffer = NULL;
	 }

     //pthread_mutex_destroy(&pRingBuffer->lock);
	 //OSMutexDel(&pRingBuffer->lock, OS_OPT_DEL_NO_PEND, &err);
	 //if(err != OS_ERR_NONE)
	 //{
	//		return (-1);
	 //}
	 return(1);
}

/* @} C_RINGBUFFER */ 
/* @} Go_COMMON */

#ifdef __cplusplus 
} 
#endif  

