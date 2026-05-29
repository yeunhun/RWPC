/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: PduR_EthDiag.h                                                **
**                                                                            **
**  TARGET    : TC3XX                                                         **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file provides dummy functionality of PduR                **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef PDUR_ETHDIAG_H
#define PDUR_ETHDIAG_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "Dcm_Cbk.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#define PduR_EthDiagCopyRxData                      Dcm_CopyRxData
#define PduR_EthDiagRxIndication                    Dcm_TpRxIndication
#define PduR_EthDiagStartOfReception                Dcm_StartOfReception
#define PduR_EthDiagCopyTxData                      Dcm_CopyTxData
#define PduR_EthDiagTxConfirmation                  Dcm_TpTxConfirmation

#endif /* PDUR_ETHDIAG_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
