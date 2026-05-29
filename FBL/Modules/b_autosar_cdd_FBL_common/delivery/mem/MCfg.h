/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: MCfg.h                                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file provides the external function declaration          **
**              for the Memory configuration APIS                             **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.21.0    13-Oct-2021   JYS          Redmine #31612                        **
** 1.19.0    30-Jul-2021   JYS          Redmine #29874                        **
** 1.11.0.0  17-Feb-2021   JYS          Redmine #28341                        **
** 1.10.0.0  07-Feb-2021   JYS          Redmine #28298 #27968                 **
** 1.0.1     29-Jul-2020   JYS          Redmine #24231                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef MCFG_H
#define MCFG_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
/* Header file inclusion for standard type definitions */
#include "Btl.h"

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/
#define BTL_START_SEC_VAR_NO_INIT
#include "Btl_MemMap.h"

extern boolean MCfg_Gbl_XmdDataFound;
extern boolean MCfg_Gbl_XmdDataFlag;
extern boolean MCfg_Gbl_SignDataFlag;

#define BTL_STOP_SEC_VAR_NO_INIT
#include "Btl_MemMap.h"

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

/* External declaration for MCfg_Init */
extern void MCfg_Init(void);

/* External declaration for address validation */
extern Std_ReturnType MCfg_ValidateAddress
  (Mem_PositionType  Ldt_TargetAddress,
  Mem_SizeType      Ldt_Length,
  Mem_AccessType    Ldt_AccessType);

/* External declaration for block validation */
extern Std_ReturnType MCfg_ValidateLogicBlock
  (Mem_BlockIdType Ldt_BlockId, Mem_AccessType Ldt_ReqActType);

/* External declaration for block validation */
extern Std_ReturnType MCfg_ValidateLogicMemoryBlock
  (Mem_BlockIdType Ldt_BlockId, Mem_AccessType Ldt_ReqActType);

/* External declaration for the conversion of block id in address and length */
extern Std_ReturnType MCfg_GetLogicBlkInfo
  (Mem_PositionType *Lpdt_BlkAddress,  Mem_SizeType *Lpdt_BlkSize);

/* External declaration for the conversion of memory block id in address and length */
extern Std_ReturnType MCfg_GetLogicMemBlkInfo
  (Mem_PositionType *Lpdt_BlkAddress,
   Mem_SizeType *Lpdt_BlkSize);
 
/* External declaration for the get erase status functionality */
extern Std_ReturnType MCfg_GetErsSts
  (Mem_PositionType Ldt_TargetAddress, Mem_SizeType Ldt_Length);

/* External declaration for the erase status update functionality */
extern void  MCfg_UpdateErsSts
  (Mem_PositionType Ldt_TargetAddress,
  Mem_SizeType Ldt_Length,
  boolean Lbl_ChngType);
 
#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* MCFG_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
