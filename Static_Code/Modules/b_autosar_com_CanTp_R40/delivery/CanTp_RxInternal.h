/*******************************************************************************
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanTp_RxInternal.h                                            **
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
** 1.10.1    16-Oct-2019   SM Kwon        Redmine #19617                      **
** 1.8.1     13-Mar-2019   SM Kwon        Redmine #15962, #16559              **
** 1.0.0     21-Mar-2013   Lim Jong Sun   Initial Version                     **
*******************************************************************************/
#ifndef CANTP_RXINTERNAL_H
#define CANTP_RXINTERNAL_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define CANTP_RXINTERNAL_AR_RELEASE_MAJOR_VERSION    4
#define CANTP_RXINTERNAL_AR_RELEASE_MINOR_VERSION    0
#define CANTP_RXINTERNAL_AR_RELEASE_REVISION_VERSION 3

/* CANTP software version information */
#define CANTP_RXINTERNAL_SW_MAJOR_VERSION            1
#define CANTP_RXINTERNAL_SW_MINOR_VERSION            11

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CANTP_START_SEC_CODE
#include "MemMap.h"
#if (CANTP_RX_NSDU == STD_ON)
extern FUNC(void,
  CANTP_CODE) CanTp_ReceptionComplete(P2VAR(CanTp_ChannelRam, AUTOMATIC,
    CANTP_VAR) LpChannelRam, NotifResultType LddResult);

#endif
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_CODE
#include "MemMap.h"
#if (CANTP_RX_NSDU == STD_ON)
extern FUNC(void,
  CANTP_CODE) CanTp_CopyRxFrame(P2VAR(CanTp_ChannelRam, AUTOMATIC,
    CANTP_VAR) LpChannelRam, P2VAR(uint8, AUTOMATIC, CANTP_VAR) LpRxSrcPtr);

#endif
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_CODE
#include "MemMap.h"
#if (CANTP_RX_NSDU == STD_ON)
extern FUNC(void,
  CANTP_CODE) CanTp_RequestRxBuffer(P2VAR(CanTp_ChannelRam, AUTOMATIC,
    CANTP_VAR) LpChannelRam);

#endif
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#if(CANTP_RX_NSDU == STD_ON)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean,
  CANTP_CODE) CanTp_RxCfDlcCheck(P2CONST(CanTp_RxNsduStatic, AUTOMATIC,
    CANTP_CONST) LpRxNSdu, uint8 LucReceivedDlc);
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define CANTP_START_SEC_CODE
#include "MemMap.h"
#if (CANTP_RX_NSDU == STD_ON)
extern FUNC(boolean, CANTP_CODE) CanTp_RxNewframeDlcCheck(P2CONST(CanTp_RxNsduStatic,
    AUTOMATIC, CANTP_CONST) LpRxNSdu, P2CONST(uint8, AUTOMATIC, CANTP_CONST)
  LpSrcPtr, uint8 LucReceivedDlc, uint32 LddDecodedSduLength);
#endif
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_CODE
#include "MemMap.h"
#if (((CANTP_RX_EXTENDED_ADDRESS == STD_ON) ||\
  (CANTP_RX_MIXED_ADDRESS == STD_ON)) || ((CANTP_TX_EXTENDED_ADDRESS == STD_ON)\
  || (CANTP_TX_MIXED_ADDRESS == STD_ON)))
/* polyspace-begin MISRA-C3:20.7 [Not a defect:Low] "No Impact of this rule violation" */	
extern FUNC(P2CONST(CanTp_RxNSaOrNAeSduMapping, AUTOMATIC, CANTP_CONST),
  CANTP_CODE) CanTp_RxBinarySearch(P2CONST(CanTp_RxNSaOrNAeSduMapping,
    AUTOMATIC, CANTP_CONST) LpFirstSduMapPtr, uint8 LucSize, uint8 LucRxNsa);
/* polyspace-end MISRA-C3:20.7 [Not a defect:Low] "No Impact of this rule violation" */
#endif /* End of if (((CANTP_RX_EXTENDED_ADDRESS == STD_ON) ||
        *(CANTP_RX_MIXED_ADDRESS == STD_ON)) || ((CANTP_TX_EXTENDED_ADDRESS ==
        * STD_ON) || (CANTP_TX_MIXED_ADDRESS == STD_ON))) */
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#endif /* CANTP_RXINTERNAL_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

