/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanTp_Internal.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file provides the function declaration                   **
**              for the CanTp APIS                                            **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     11-Sep-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef CANTP_INTERNAL_H
#define CANTP_INTERNAL_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "CanTp_Types.h"

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

extern Std_ReturnType CanTp_TxDetCheck(PduIdType CanTpTxSduId,
  const PduInfoType* LpCanTpTxInfoPtr);

extern boolean CanTp_CbkTxDetCheck(PduIdType TxPduID);

extern boolean CanTp_RxDetCheck(PduIdType RxPduID,
  const PduInfoType* LpPduInfoPt);

extern void CanTp_ProcessRxFc(PduIdType LddTxSduId, const uint8* CanTpRxPduPtr);

extern void CanTp_CanIfTransmit(const CanTp_TxNsduStatic* LpTxNSdu);

extern void CanTp_RequestCopyTxData(CanTp_ChannelRam* LpChannelRam);

extern void CanTp_TransmissionComplete(CanTp_ChannelRam* LpChannelRam,
  NotifResultType LddResult);

extern boolean CanTp_TxDlcCheck(const CanTp_TxNsduStatic* LpTxNSdu,
  PduLengthType LucTxDatalength);

extern void CanTp_UpdateTxFrameStatus(CanTp_ChannelRam* LpChannelRam,
  const CanTp_TxNsduStatic* LpTxNSdu);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* CANTP_INTERNAL_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
