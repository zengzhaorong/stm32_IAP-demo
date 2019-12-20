/**
  ******************************************************************************
  * @file           : cpuFlash.h
  * @brief          : header file
  ******************************************************************************
  * @attention
  *
  * Copyright: https://blog.csdn.net/qq_30155503
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef _CPU_FLASH_H_
#define _CPU_FLASH_H_

/*****************************************************************
* 包含头文件
******************************************************************/
#include "stm32f1xx_hal.h"
#include "typedef.h"

/*****************************************************************
* 宏定义
******************************************************************/

/* Embeded flash */
/* STM32F103xC - 256k */
#define ADDR_FLASH_PAGE_0			((INT32U)0x08000000) /* Base @ of Page 0, 2 Kbyte */
#define ADDR_FLASH_PAGE_1			((INT32U)0x08000800) /* Base @ of Page 1, 2 Kbyte */
#define ADDR_FLASH_PAGE_2			((INT32U)0x08001000) /* Base @ of Page 2, 2 Kbyte */
#define ADDR_FLASH_PAGE_3			((INT32U)0x08001800) /* Base @ of Page 3, 2 Kbyte */
#define ADDR_FLASH_PAGE_4			((INT32U)0x08002000) /* Base @ of Page 4, 2 Kbyte */
#define ADDR_FLASH_PAGE_5			((INT32U)0x08002800) /* Base @ of Page 5, 2 Kbyte */
#define ADDR_FLASH_PAGE_6			((INT32U)0x08003000) /* Base @ of Page 6, 2 Kbyte */
#define ADDR_FLASH_PAGE_7			((INT32U)0x08003800) /* Base @ of Page 7, 2 Kbyte */
#define ADDR_FLASH_PAGE_8			((INT32U)0x08004000) /* Base @ of Page 8, 2 Kbyte */
#define ADDR_FLASH_PAGE_9			((INT32U)0x08004800) /* Base @ of Page 9, 2 Kbyte */
#define ADDR_FLASH_PAGE_10			((INT32U)0x08005000) /* Base @ of Page 10, 2 Kbyte */
#define ADDR_FLASH_PAGE_11			((INT32U)0x08005800) /* Base @ of Page 11, 2 Kbyte */
#define ADDR_FLASH_PAGE_12			((INT32U)0x08006000) /* Base @ of Page 12, 2 Kbyte */
#define ADDR_FLASH_PAGE_13			((INT32U)0x08006800) /* Base @ of Page 13, 2 Kbyte */
#define ADDR_FLASH_PAGE_14			((INT32U)0x08007000) /* Base @ of Page 14, 2 Kbyte */
#define ADDR_FLASH_PAGE_15			((INT32U)0x08007800) /* Base @ of Page 15, 2 Kbyte */
#define ADDR_FLASH_PAGE_16			((INT32U)0x08008000) /* Base @ of Page 16, 2 Kbyte */
#define ADDR_FLASH_PAGE_17			((INT32U)0x08008800) /* Base @ of Page 17, 2 Kbyte */
#define ADDR_FLASH_PAGE_18			((INT32U)0x08009000) /* Base @ of Page 18, 2 Kbyte */
#define ADDR_FLASH_PAGE_19			((INT32U)0x08009800) /* Base @ of Page 19, 2 Kbyte */
#define ADDR_FLASH_PAGE_20			((INT32U)0x0800A000) /* Base @ of Page 20, 2 Kbyte */
#define ADDR_FLASH_PAGE_21			((INT32U)0x0800A800) /* Base @ of Page 21, 2 Kbyte */
#define ADDR_FLASH_PAGE_22			((INT32U)0x0800B000) /* Base @ of Page 22, 2 Kbyte */
#define ADDR_FLASH_PAGE_23			((INT32U)0x0800B800) /* Base @ of Page 23, 2 Kbyte */
#define ADDR_FLASH_PAGE_24			((INT32U)0x0800C000) /* Base @ of Page 24, 2 Kbyte */
#define ADDR_FLASH_PAGE_25			((INT32U)0x0800C800) /* Base @ of Page 25, 2 Kbyte */
#define ADDR_FLASH_PAGE_26			((INT32U)0x0800D000) /* Base @ of Page 26, 2 Kbyte */
#define ADDR_FLASH_PAGE_27			((INT32U)0x0800D800) /* Base @ of Page 27, 2 Kbyte */
#define ADDR_FLASH_PAGE_28			((INT32U)0x0800E000) /* Base @ of Page 28, 2 Kbyte */
#define ADDR_FLASH_PAGE_29			((INT32U)0x0800E800) /* Base @ of Page 29, 2 Kbyte */
#define ADDR_FLASH_PAGE_30			((INT32U)0x0800F000) /* Base @ of Page 30, 2 Kbyte */
#define ADDR_FLASH_PAGE_31			((INT32U)0x0800F800) /* Base @ of Page 31, 2 Kbyte */
#define ADDR_FLASH_PAGE_32			((INT32U)0x08010000) /* Base @ of Page 32, 2 Kbyte */
#define ADDR_FLASH_PAGE_33			((INT32U)0x08010800) /* Base @ of Page 33, 2 Kbyte */
#define ADDR_FLASH_PAGE_34			((INT32U)0x08011000) /* Base @ of Page 34, 2 Kbyte */
#define ADDR_FLASH_PAGE_35			((INT32U)0x08011800) /* Base @ of Page 35, 2 Kbyte */
#define ADDR_FLASH_PAGE_36			((INT32U)0x08012000) /* Base @ of Page 36, 2 Kbyte */
#define ADDR_FLASH_PAGE_37			((INT32U)0x08012800) /* Base @ of Page 37, 2 Kbyte */
#define ADDR_FLASH_PAGE_38			((INT32U)0x08013000) /* Base @ of Page 38, 2 Kbyte */
#define ADDR_FLASH_PAGE_39			((INT32U)0x08013800) /* Base @ of Page 39, 2 Kbyte */
#define ADDR_FLASH_PAGE_40			((INT32U)0x08014000) /* Base @ of Page 40, 2 Kbyte */
#define ADDR_FLASH_PAGE_41			((INT32U)0x08014800) /* Base @ of Page 41, 2 Kbyte */
#define ADDR_FLASH_PAGE_42			((INT32U)0x08015000) /* Base @ of Page 42, 2 Kbyte */
#define ADDR_FLASH_PAGE_43			((INT32U)0x08015800) /* Base @ of Page 43, 2 Kbyte */
#define ADDR_FLASH_PAGE_44			((INT32U)0x08016000) /* Base @ of Page 44, 2 Kbyte */
#define ADDR_FLASH_PAGE_45			((INT32U)0x08016800) /* Base @ of Page 45, 2 Kbyte */
#define ADDR_FLASH_PAGE_46			((INT32U)0x08017000) /* Base @ of Page 46, 2 Kbyte */
#define ADDR_FLASH_PAGE_47			((INT32U)0x08017800) /* Base @ of Page 47, 2 Kbyte */
#define ADDR_FLASH_PAGE_48			((INT32U)0x08018000) /* Base @ of Page 48, 2 Kbyte */
#define ADDR_FLASH_PAGE_49			((INT32U)0x08018800) /* Base @ of Page 49, 2 Kbyte */
#define ADDR_FLASH_PAGE_50			((INT32U)0x08019000) /* Base @ of Page 50, 2 Kbyte */
#define ADDR_FLASH_PAGE_51			((INT32U)0x08019800) /* Base @ of Page 51, 2 Kbyte */
#define ADDR_FLASH_PAGE_52			((INT32U)0x0801A000) /* Base @ of Page 52, 2 Kbyte */
#define ADDR_FLASH_PAGE_53			((INT32U)0x0801A800) /* Base @ of Page 53, 2 Kbyte */
#define ADDR_FLASH_PAGE_54			((INT32U)0x0801B000) /* Base @ of Page 54, 2 Kbyte */
#define ADDR_FLASH_PAGE_55			((INT32U)0x0801B800) /* Base @ of Page 55, 2 Kbyte */
#define ADDR_FLASH_PAGE_56			((INT32U)0x0801C000) /* Base @ of Page 56, 2 Kbyte */
#define ADDR_FLASH_PAGE_57			((INT32U)0x0801C800) /* Base @ of Page 57, 2 Kbyte */
#define ADDR_FLASH_PAGE_58			((INT32U)0x0801D000) /* Base @ of Page 58, 2 Kbyte */
#define ADDR_FLASH_PAGE_59			((INT32U)0x0801D800) /* Base @ of Page 59, 2 Kbyte */
#define ADDR_FLASH_PAGE_60			((INT32U)0x0801E000) /* Base @ of Page 60, 2 Kbyte */
#define ADDR_FLASH_PAGE_61			((INT32U)0x0801E800) /* Base @ of Page 61, 2 Kbyte */
#define ADDR_FLASH_PAGE_62			((INT32U)0x0801F000) /* Base @ of Page 62, 2 Kbyte */
#define ADDR_FLASH_PAGE_63			((INT32U)0x0801F800) /* Base @ of Page 63, 2 Kbyte */
#define ADDR_FLASH_PAGE_64			((INT32U)0x08020000) /* Base @ of Page 64, 2 Kbyte */
#define ADDR_FLASH_PAGE_65			((INT32U)0x08020800) /* Base @ of Page 65, 2 Kbyte */
#define ADDR_FLASH_PAGE_66			((INT32U)0x08021000) /* Base @ of Page 66, 2 Kbyte */
#define ADDR_FLASH_PAGE_67			((INT32U)0x08021800) /* Base @ of Page 67, 2 Kbyte */
#define ADDR_FLASH_PAGE_68			((INT32U)0x08022000) /* Base @ of Page 68, 2 Kbyte */
#define ADDR_FLASH_PAGE_69			((INT32U)0x08022800) /* Base @ of Page 69, 2 Kbyte */
#define ADDR_FLASH_PAGE_70			((INT32U)0x08023000) /* Base @ of Page 70, 2 Kbyte */
#define ADDR_FLASH_PAGE_71			((INT32U)0x08023800) /* Base @ of Page 71, 2 Kbyte */
#define ADDR_FLASH_PAGE_72			((INT32U)0x08024000) /* Base @ of Page 72, 2 Kbyte */
#define ADDR_FLASH_PAGE_73			((INT32U)0x08024800) /* Base @ of Page 73, 2 Kbyte */
#define ADDR_FLASH_PAGE_74			((INT32U)0x08025000) /* Base @ of Page 74, 2 Kbyte */
#define ADDR_FLASH_PAGE_75			((INT32U)0x08025800) /* Base @ of Page 75, 2 Kbyte */
#define ADDR_FLASH_PAGE_76			((INT32U)0x08026000) /* Base @ of Page 76, 2 Kbyte */
#define ADDR_FLASH_PAGE_77			((INT32U)0x08026800) /* Base @ of Page 77, 2 Kbyte */
#define ADDR_FLASH_PAGE_78			((INT32U)0x08027000) /* Base @ of Page 78, 2 Kbyte */
#define ADDR_FLASH_PAGE_79			((INT32U)0x08027800) /* Base @ of Page 79, 2 Kbyte */
#define ADDR_FLASH_PAGE_80			((INT32U)0x08028000) /* Base @ of Page 80, 2 Kbyte */
#define ADDR_FLASH_PAGE_81			((INT32U)0x08028800) /* Base @ of Page 81, 2 Kbyte */
#define ADDR_FLASH_PAGE_82			((INT32U)0x08029000) /* Base @ of Page 82, 2 Kbyte */
#define ADDR_FLASH_PAGE_83			((INT32U)0x08029800) /* Base @ of Page 83, 2 Kbyte */
#define ADDR_FLASH_PAGE_84			((INT32U)0x0802A000) /* Base @ of Page 84, 2 Kbyte */
#define ADDR_FLASH_PAGE_85			((INT32U)0x0802A800) /* Base @ of Page 85, 2 Kbyte */
#define ADDR_FLASH_PAGE_86			((INT32U)0x0802B000) /* Base @ of Page 86, 2 Kbyte */
#define ADDR_FLASH_PAGE_87			((INT32U)0x0802B800) /* Base @ of Page 87, 2 Kbyte */
#define ADDR_FLASH_PAGE_88			((INT32U)0x0802C000) /* Base @ of Page 88, 2 Kbyte */
#define ADDR_FLASH_PAGE_89			((INT32U)0x0802C800) /* Base @ of Page 89, 2 Kbyte */
#define ADDR_FLASH_PAGE_90			((INT32U)0x0802D000) /* Base @ of Page 90, 2 Kbyte */
#define ADDR_FLASH_PAGE_91			((INT32U)0x0802D800) /* Base @ of Page 91, 2 Kbyte */
#define ADDR_FLASH_PAGE_92			((INT32U)0x0802E000) /* Base @ of Page 92, 2 Kbyte */
#define ADDR_FLASH_PAGE_93			((INT32U)0x0802E800) /* Base @ of Page 93, 2 Kbyte */
#define ADDR_FLASH_PAGE_94			((INT32U)0x0802F000) /* Base @ of Page 94, 2 Kbyte */
#define ADDR_FLASH_PAGE_95			((INT32U)0x0802F800) /* Base @ of Page 95, 2 Kbyte */
#define ADDR_FLASH_PAGE_96			((INT32U)0x08030000) /* Base @ of Page 96, 2 Kbyte */
#define ADDR_FLASH_PAGE_97			((INT32U)0x08030800) /* Base @ of Page 97, 2 Kbyte */
#define ADDR_FLASH_PAGE_98			((INT32U)0x08031000) /* Base @ of Page 98, 2 Kbyte */
#define ADDR_FLASH_PAGE_99			((INT32U)0x08031800) /* Base @ of Page 99, 2 Kbyte */
#define ADDR_FLASH_PAGE_100 		((INT32U)0x08032000) /* Base @ of Page 100, 2 Kbyte */
#define ADDR_FLASH_PAGE_101 		((INT32U)0x08032800) /* Base @ of Page 101, 2 Kbyte */
#define ADDR_FLASH_PAGE_102 		((INT32U)0x08033000) /* Base @ of Page 102, 2 Kbyte */
#define ADDR_FLASH_PAGE_103 		((INT32U)0x08033800) /* Base @ of Page 103, 2 Kbyte */
#define ADDR_FLASH_PAGE_104 		((INT32U)0x08034000) /* Base @ of Page 104, 2 Kbyte */
#define ADDR_FLASH_PAGE_105 		((INT32U)0x08034800) /* Base @ of Page 105, 2 Kbyte */
#define ADDR_FLASH_PAGE_106 		((INT32U)0x08035000) /* Base @ of Page 106, 2 Kbyte */
#define ADDR_FLASH_PAGE_107 		((INT32U)0x08035800) /* Base @ of Page 107, 2 Kbyte */
#define ADDR_FLASH_PAGE_108 		((INT32U)0x08036000) /* Base @ of Page 108, 2 Kbyte */
#define ADDR_FLASH_PAGE_109 		((INT32U)0x08036800) /* Base @ of Page 109, 2 Kbyte */
#define ADDR_FLASH_PAGE_110 		((INT32U)0x08037000) /* Base @ of Page 110, 2 Kbyte */
#define ADDR_FLASH_PAGE_111 		((INT32U)0x08037800) /* Base @ of Page 111, 2 Kbyte */
#define ADDR_FLASH_PAGE_112 		((INT32U)0x08038000) /* Base @ of Page 112, 2 Kbyte */
#define ADDR_FLASH_PAGE_113 		((INT32U)0x08038800) /* Base @ of Page 113, 2 Kbyte */
#define ADDR_FLASH_PAGE_114 		((INT32U)0x08039000) /* Base @ of Page 114, 2 Kbyte */
#define ADDR_FLASH_PAGE_115 		((INT32U)0x08039800) /* Base @ of Page 115, 2 Kbyte */
#define ADDR_FLASH_PAGE_116 		((INT32U)0x0803A000) /* Base @ of Page 116, 2 Kbyte */
#define ADDR_FLASH_PAGE_117 		((INT32U)0x0803A800) /* Base @ of Page 117, 2 Kbyte */
#define ADDR_FLASH_PAGE_118 		((INT32U)0x0803B000) /* Base @ of Page 118, 2 Kbyte */
#define ADDR_FLASH_PAGE_119 		((INT32U)0x0803B800) /* Base @ of Page 119, 2 Kbyte */
#define ADDR_FLASH_PAGE_120 		((INT32U)0x0803C000) /* Base @ of Page 120, 2 Kbyte */
#define ADDR_FLASH_PAGE_121 		((INT32U)0x0803C800) /* Base @ of Page 121, 2 Kbyte */
#define ADDR_FLASH_PAGE_122 		((INT32U)0x0803D000) /* Base @ of Page 122, 2 Kbyte */
#define ADDR_FLASH_PAGE_123 		((INT32U)0x0803D800) /* Base @ of Page 123, 2 Kbyte */
#define ADDR_FLASH_PAGE_124 		((INT32U)0x0803E000) /* Base @ of Page 124, 2 Kbyte */
#define ADDR_FLASH_PAGE_125 		((INT32U)0x0803E800) /* Base @ of Page 125, 2 Kbyte */
#define ADDR_FLASH_PAGE_126 		((INT32U)0x0803F000) /* Base @ of Page 126, 2 Kbyte */
#define ADDR_FLASH_PAGE_127 		((INT32U)0x0803F800) /* Base @ of Page 127, 2 Kbyte */

#define NVIC_VectTab_FLASH			FLASH_BASE				// flash中断向量地址



/*********************************************************************
	升级包文件数组组织说明：
	0x08000000 ~ 	|0x08008000 ~	|0x0800C000 ~	|0x0803C000
	bootloader(32K)	|parameter(16K)	|app(192K)		|reserve(16K)
*********************************************************************/


/* flash分配 */
#define FLASH_PAGE_BOOT_START				ADDR_FLASH_PAGE_0		// bootloader起始地址 - 32K
#define FLASH_PAGE_BOOT_END					ADDR_FLASH_PAGE_15		// bootloader结束地址 - 32K
#define FLASH_PAGE_PARAM_START				ADDR_FLASH_PAGE_16		// 参数起始地址			- 16K
#define FLASH_PAGE_PARAM_END				ADDR_FLASH_PAGE_23		// 参数结束地址			- 16K
#define FLASH_PAGE_APP_START				ADDR_FLASH_PAGE_24		// APP区			- 192K
#define FLASH_PAGE_APP_END					ADDR_FLASH_PAGE_119		// APP区			- 192K

#define FLASH_APP_HEAD_SIZE			0x200		// APP头信息长度-程序位于FLASH_PAGE_APP_START+APP_HEAD_SIZE的地址上

/* bootloader启动标志 */
#define BOOT_FLAG_NORMAL_RUNAPP		0x0A		// 正常启动APP
#define BOOT_FLAG_WAIT_UPGRADE		0x0B		// 等待升级
#define BOOT_FLAG_FORCE_RUNAPP		0x0F		// 强制启动APP

/*****************************************************************
* 结构、枚举定义
******************************************************************/

/* flash参数区信息结构 */
struct param_info
{
	UINT16		usStartFlag;				// 启动标志 0x0A-跳至APP 0x0B-等待升级 0x0F-已强制启动过
};

/*****************************************************************
* 全局变量声明
******************************************************************/

/*****************************************************************
* 函数原型声明
******************************************************************/
INT32 cpuflash_read(UINT32 unStartAddr, UINT8 *pData, UINT16 usSize);
INT32 cpuflash_write(UINT32 unStartAddr, UINT8 *pData, UINT16 usSize);
INT32 cpuflash_erase(UINT32 unStartAddr, UINT32 unEndAddr);
void cpuflash_enableReadProtect(void);
void cpuflash_disableReadProtect(void);

int cpuflash_Init(void);


#endif
