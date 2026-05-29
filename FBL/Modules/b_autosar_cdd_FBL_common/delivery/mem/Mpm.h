/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Mpm.h                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file provides the external function declaration          **
**              for the Memory Program Manager APIS                           **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef MPM_H
#define MPM_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
/* Header file inclusion for standard types */
#include "Btl.h"

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

/* External declaration for block validation */
extern Std_ReturnType Mpm_ValidateBlock(
  uint8 Lu8_BlockId,
  Mem_AccessType Ldt_AccessType
);

/* External declaration for address validation  */
extern Std_ReturnType Mpm_ValidateAddress(
  uint32 Lu32_TargetAddress,
  uint32 Lu32_Length,
  Mem_AccessType Ldt_AccessType
);

/* External declaration for Mpm_Read */
extern Std_ReturnType Mpm_Read(
  uint32 Lu32_SourceAddress,
  uint8 * Lpu8_TargetAddress,
  uint32 Lu32_Length
);

/* External declaration for Mpm_Write */
extern Std_ReturnType Mpm_Write(
  uint32 Lu32_TargetAddress,
  const uint8 * Lpu8_SourceAddress,
  uint32 Lu32_Length
); 

/* External declaration for handling block-wise erase */
extern Std_ReturnType Mpm_Erase(
  uint8 Lu8_BlockId
);

/* External declaration for Mpm_MainFunction */
extern void Mpm_MainFunction(void);

/* External declaration for Mpm_Init */
extern void Mpm_Init(void);

/* External declaration for Mpm_GetStatus */
extern Std_StatusType Mpm_GetStatus(void);

/* External declaration for Mpm_GetJobResult */
extern Std_JobReturnType Mpm_GetJobResult(void);

/* External declaration for Mpm_IndicateWriteComplete */
extern void Mpm_IndicateWriteComplete(void);

/* External declaration for Mpm_IndicateErsStart */
extern void Mpm_IndicateErsStart(void);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* MPM_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
