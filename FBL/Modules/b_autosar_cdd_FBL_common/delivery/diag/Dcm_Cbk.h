/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dcm_Cbk.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Header file for Dcm_Cbk.c                                     **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef DCM_CBK_H
#define DCM_CBK_H

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

extern void Dcm_TpRxIndication (PduIdType Ldt_DcmRxPduId,
  NotifResultType Ldt_Result);

extern void Dcm_TpTxConfirmation(PduIdType Ldt_DcmTxPduId,
  NotifResultType Ldt_Result);

extern BufReq_ReturnType Dcm_StartOfReception(PduIdType Ldt_DcmRxPduId,
  const PduInfoType *Lpdt_Info, PduLengthType  Ldt_TpSduLength,
  PduLengthType *Lpdt_RxBufferSize);

extern BufReq_ReturnType Dcm_CopyRxData(PduIdType Ldt_DcmRxPduId,
  const PduInfoType *Lpdt_PduInfo, PduLengthType *Lpdt_RxBufferSize);

extern BufReq_ReturnType Dcm_CopyTxData(PduIdType Ldt_DcmTxPduId,
  const PduInfoType *Lpdt_PduInfo, const RetryInfoType *Lpdt_RetryInfo,
  PduLengthType *Lpdt_TxDataCnt);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* DCM_CBK_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
