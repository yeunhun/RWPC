/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: PduR_CanTp.h                                                  **
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

#ifndef PDUR_CANTP_H
#define PDUR_CANTP_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "Dcm_Cbk.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#define PduR_CanTpCopyRxData                        Dcm_CopyRxData
#define PduR_CanTpCopyTxData                        Dcm_CopyTxData
#define PduR_CanTpStartOfReception                  Dcm_StartOfReception
#define PduR_CanTpRxIndication                      Dcm_TpRxIndication
#define PduR_CanTpTxConfirmation                    Dcm_TpTxConfirmation

#endif /* PDUR_CANTP_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
