/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanTp_Cbk.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides declarations for callbacks provided by CanTp         **
**              which will be used by lower layer                             **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     11-Sep-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef CANTP_CBK_H
#define CANTP_CBK_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

/* Function indicates the complete data is transferred  */
extern void CanTp_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr);

/* Function indicates the result of transmission through CAN */
extern void CanTp_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* CANTP_CBK_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
