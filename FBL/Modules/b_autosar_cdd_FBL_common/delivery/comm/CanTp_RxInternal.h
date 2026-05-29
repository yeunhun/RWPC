/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanTp_RxInternal.h                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file provides the function declaration                   **
**              for the CanTp Rx APIS                                         **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     11-Sep-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef CANTP_RXINTERNAL_H
#define CANTP_RXINTERNAL_H

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

extern void CanTp_CopyRxDatToLocalBuff(CanTp_ChannelRam* LpChannelRam,
  uint8* LpRxSrcPtr);

extern void CanTp_CopyRxFrame(CanTp_ChannelRam* LpChannelRam,
  uint8* LpRxSrcPtr);

extern void CanTp_ReceptionComplete(CanTp_ChannelRam* LpChannelRam,
  NotifResultType LddResult);

extern void CanTp_RequestRxBuffer(CanTp_ChannelRam* LpChannelRam);

extern void CanTp_RxBufferChk(CanTp_ChannelRam* LpChanelRam);

extern boolean CanTp_RxCfDlcCheck(const CanTp_RxNsduStatic* LpRxNSdu,
  uint8 LucReceivedDlc);

extern boolean CanTp_RxNewframeDlcCheck(const CanTp_RxNsduStatic* LpRxNSdu,
  const uint8* LpSrcPtr, uint8 LucReceivedDlc, uint32 LddDecodedSduLength);

extern void CanTp_RxPduBufferChk(CanTp_ChannelRam* LpChannelRam,
  uint8* LpRxSrcPtr);

extern void CanTp_TransmitFc(CanTp_ChannelRam* LpChannelRam);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* CANTP_RXINTERNAL_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
