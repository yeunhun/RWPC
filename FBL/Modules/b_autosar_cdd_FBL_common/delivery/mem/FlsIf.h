/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: FlsIf.h                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file provides all the API and function related to        **
**              flash interface module                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef FLSIF_H
#define FLSIF_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "Util.h"

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

extern Mem_ErrorType FlsIf_Init(uint8 Lu8_FlashType);

extern Mem_ErrorType FlsIf_Deinit(void);

extern Mem_ErrorType FlsIf_Write(
  Mem_PositionType Ldt_WriteAddress,
  Mem_MemPtrType   Ldt_WriteBuffer,
  Mem_SizeType     Ldt_WriteLength);
  
extern Mem_ErrorType FlsIf_Read(
  Mem_PositionType Ldt_ReadAddress,
  Mem_MemPtrType   Ldt_ReadBuffer,
  Mem_SizeType     Ldt_ReadLength);
  
extern Mem_ErrorType FlsIf_Erase(
  Mem_PositionType Ldt_EraseAddress,
  Mem_SizeType Ldt_EraseLength);
  
extern Mem_ErrorType FlsIf_ReturnLastErr(void);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* FLSIF_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
