/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Stm_Pgm.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Header file for Stm_Pgm.c                                     **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.21.0    26-Oct-2021   JYS          Redmine #29277 #29449                 **
** 1.10.0.0  07-Feb-2021   JYS          Redmine #28298 #27968                 **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef STM_PGM_H
#define STM_PGM_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
/*******************************************************************************
**                            Type Definition                                 **
*******************************************************************************/
#define BTL_START_SEC_VAR_INIT
#include "Btl_MemMap.h"

/* Holds the length of Actual data that need to be written */
extern uint32 Stm_Pgm_Gu32_ActualLength;

#define BTL_STOP_SEC_VAR_INIT
#include "Btl_MemMap.h"
/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

extern void Stm_PgmIndicateBlockStart(uint8 Lu8_BlockId);

extern void Stm_PgmSetMemoryStartAddress(uint32 Lu32_MemoryAddress);

extern void Stm_PgmMainFunction(void);

extern Std_JobReturnType Stm_PgmGetJobResult(void);

extern Std_ReturnType Stm_PgmWriteData(
  const uint8* Lpu8_SourceDataPtr,
  uint32 Lu32_Length
);

extern Std_ReturnType Stm_PgmProcessWrite(
  const uint8* Lpu8_SourceDataPtr,
  uint32 Lu32_Length
);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* STM_PGM_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
