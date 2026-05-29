/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: EthDiag.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file provides the function declaration                   **
**              for the EthDiag APIS                                          **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef ETHDIAG_H
#define ETHDIAG_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "EthDiag_Types.h"

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

/* Function initialize EthDiag module */
extern void EthDiag_Init(void);

/* Function process the Rx message and prepare response */
extern void EthDiag_MainFunction(void);

/* Function deactivate the activation line */
extern void EthDiag_ActivationLineSwitchInactive(void);

/* Function activate the activation line */
extern void EthDiag_ActivationLineSwitchActive(void);

/* Function to check the activation status */
extern Std_ReturnType EthDiag_ActivationSts(void);

/* Function indicates the pdur id transmitting data */
extern Std_ReturnType EthDiag_TpTransmit(
  PduIdType Ldt_TxPduId,
  const PduInfoType* Lpst_PduInfoPtr
);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* ETHDIAG_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
