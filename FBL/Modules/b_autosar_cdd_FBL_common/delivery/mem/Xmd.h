/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Xmd.h                                                         **
**                                                                            **
**  TARGET    : TC3XX                                                         **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Header file for Xmd.c                                         **
**              Implements memory programming functionality for               **
**              non-standard(Flash) memory for programming                    **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef XMD_H
#define XMD_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "Xmd_Cfg.h"

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_PJS_CODE
#include "Btl_MemMap.h"

extern void Xmd_Init(void);

extern Std_ReturnType Xmd_ValidateAddress(Mem_PositionType Ldt_TargetAddress,
  Mem_SizeType Ldt_Length,
  Mem_AccessType Ldt_AccessType);

#if(XMD_ERASE_MEM_SUPPORT == STD_ON)
extern Std_ReturnType Xmd_GetEraseMemorySts(Mem_PositionType Ldt_ErsAddr,
  Mem_SizeType Ldt_ErsLength);

extern Mem_ErrorType Xmd_EraseMemory(Mem_PositionType Ldt_ErsAddr,
  Mem_SizeType Ldt_ErsLength);
#endif

#if(XMD_READ_MEM_SUPPORT == STD_ON)
extern Mem_ErrorType Xmd_ReadMemory(Mem_PositionType Ldt_SourceAddress,
  Mem_MemPtrType Ldt_TargetAddress,
  Mem_SizeType Ldt_Length);
#endif

#if(XMD_WRITE_MEM_SUPPORT == STD_ON)
extern Mem_ErrorType Xmd_WriteMemory(Mem_PositionType Ldt_TargetAddress,
  const uint8 *  Ldt_SourceAddress,
  Mem_SizeType Ldt_Length);
#endif

#define BTL_STOP_SEC_PJS_CODE
#include "Btl_MemMap.h"

#endif /* XMD_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
