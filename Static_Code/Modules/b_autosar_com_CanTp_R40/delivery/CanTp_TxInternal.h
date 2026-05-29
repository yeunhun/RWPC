/*******************************************************************************
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanTp_TxInternal.h                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transport Protocol                                **
**                                                                            **
**  PURPOSE   : Internal header file for CanTp                                **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.10.2    03-Nov-2020   SM Kwon        Redmine #25248                      **
** 1.9.0     06-Aug-2019   SM Kwon        Redmine #16557                      **
** 1.8.1     12-Mar-2019   SM Kwon        Redmine #15962, #16559              **
** 1.0.0     21-Mar-2013   Lim Jong Sun   Initial Version                     **
*******************************************************************************/
#ifndef CANTP_TXINTERNAL_H
#define CANTP_TXINTERNAL_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanTp_Cfg.h"            /* CanTp cfg Header File */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define CANTP_TXINTERNAL_AR_RELEASE_MAJOR_VERSION    4
#define CANTP_TXINTERNAL_AR_RELEASE_MINOR_VERSION    0
#define CANTP_TXINTERNAL_AR_RELEASE_REVISION_VERSION 3

/* CANTP software version information */
#define CANTP_TXINTERNAL_SW_MAJOR_VERSION            1
#define CANTP_TXINTERNAL_SW_MINOR_VERSION            11

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if (CANTP_TX_NSDU == STD_ON)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,
  CANTP_CODE) CanTp_CanIfTransmit(P2CONST(CanTp_TxNsduStatic, AUTOMATIC,
    CANTP_CONST) LpTxNSdu);
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,
  CANTP_CODE) CanTp_TransmissionComplete(P2VAR(CanTp_ChannelRam, AUTOMATIC,
    CANTP_VAR) LpChannelRam, NotifResultType LddResult);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,
  CANTP_CODE) CanTp_RequestCopyTxData(P2VAR(CanTp_ChannelRam, AUTOMATIC,
    CANTP_VAR) LpChannelRam);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean,
  CANTP_CODE) CanTp_TxDlcCheck(P2CONST(CanTp_TxNsduStatic, AUTOMATIC,
    CANTP_CONST) LpTxNSdu, PduLengthType LucTxDatalength);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#endif /* End of if (CANTP_TX_NSDU == STD_ON) */

#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANTP_CODE) CanTp_ProcessRxFc(PduIdType LddTxSduId, P2CONST(
    uint8, AUTOMATIC, CANTP_CONST) CanTpRxPduPtr);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#endif /* CANTP_TXINTERNAL_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

