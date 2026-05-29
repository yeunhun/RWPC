/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanIf_Ram.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Header file of CanIf_Ram.c                                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By              Description                        **
********************************************************************************
** 3.0.0    08-Nov-2021    Sj.Kim    #32882                                   **
** 2.7.1    25-Nov-2020    Sj.Kim    #26002                                   **
** 2.7.0    07-Oct-2020    Sj.Kim    #25877                                   **
** 2.6.2    15-May-2020    Sj.Kim    #23352, #21882, #23360                   **
** 2.6.0    22-Aug-2019    Js.Lim    #18384                                   **
** 2.5.5    10-Jan-2018    Js.Lim    #10934, #10456                           **
** 2.5.0    06-Dec-2016    Js.Lim    #7077                                    **
** 2.3.2    05-Jan-2016    Kt.Kim    #3813                                    **
** 2.3.1    25-Aug-2015    Kt.Kim    Code change and jusitification for       **
**                                   MISRA rule 8.12 (Improvement #2999)      **     
** 2.3.0    17-Jun-2013    Kt.Kim    Lib-Build Support                        **
**                                   Remove declaration for CONST             **
** 2.2.0    30-May-2013    Kt.Kim    Lib-Build Support                        **
** 2.1.0    29-May-2013    Kt.Kim    OsekNm Support                           **
** 1.0.0    04-Feb-2013    Kt.Kim    Initial version                          **
*******************************************************************************/

#ifndef CANIF_RAM_H
#define CANIF_RAM_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf.h"                        /* CAN Interface Module Header File */
#include "CanIf_IntTypes.h"               /* CAN Internal Types Header File */
#include "CanIf_PCTypes.h"                /* Pre-compile time header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CANIF_RAM_AR_RELEASE_MAJOR_VERSION       4
#define CANIF_RAM_AR_RELEASE_MINOR_VERSION       0
#define CANIF_RAM_AR_RELEASE_REVISION_VERSION    3

/* Software Version Information */
#define CANIF_RAM_SW_MAJOR_VERSION    3
#define CANIF_RAM_SW_MINOR_VERSION    0
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* polyspace-begin MISRA-C3:8.11 [Not a defect:Justified] "No Impact of this rule violation(Array size will fixed in linking time)" */
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#define CANIF_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to store Initialization status of CAN Interface */
extern VAR (boolean, CANIF_VAR) CanIf_GblCanIfStatus;
#define CANIF_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_CANTRCV_SUPPORT)
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Operation Mode */
extern VAR (uint8, CANIF_VAR) CanIf_GaaTrcvMode[];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if ((STD_ON == CANIF_CANTRCV_SUPPORT) && (STD_ON == CANIF_DEV_ERROR_DETECT))
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Operation Mode */
extern VAR (uint8, CANIF_VAR) CanIf_GaaOperMode[];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for HrhId */
/* #10934 */
extern VAR (uint16, CANIF_VAR) CanIf_GaaHrhArrayId[];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for HrhOffset */
extern VAR (uint8, CANIF_VAR) CanIf_GaaHrhOffSetId[];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Controller */
extern VAR (CanIf_Controller, CANIF_VAR) CanIf_GaaController[];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global variable for saving CAN identifier of received message */
extern VAR(Can_IdType, CANIF_NOINIT_DATA) CanIf_GddRxCanId;
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (STD_ON == CANIF_TX_LPDU)
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern VAR(uint8, CANIF_NOINIT_DATA) CanIf_GaaTxPduGwStatus[];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(CANIF_BUSLOAD_DETECTING_SUPPORT == STD_ON)
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern VAR (uint32, CANIF_VAR) CanIf_GaaRxMsgCnt[];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern VAR (uint32, CANIF_VAR) CanIf_GaaTxMsgCnt[];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global variable for the transmit queue */
/* polyspace +1 MISRA-C3:8.6 [Not a defect:Low] "No Impact of this rule violation" */
extern VAR(CanIf_TxQueue, CANIF_VAR) CanIf_GaaTxQueue[];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Queue allocation */
/* polyspace +1 MISRA-C3:8.6 [Not a defect:Low] "No Impact of this rule violation" */
extern VAR (CanIf_TxPduIdType, CANIF_VAR) CanIf_GaaTxPduToQueueMapping[];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if ((STD_ON == CANIF_READRXPDU_DATA_API) || \
                                  (STD_ON == CANIF_READRXPDU_NOTIFY_STATUS_API))
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Rx L-PDU notify structure */
extern VAR (CanIf_RxLpduNotify, CANIF_VAR) CanIf_GaaRxLpduNotify[];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_READTXPDU_NOTIFY_STATUS_API)
/* Global array for Tx and Rx notificaton status */
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include"MemMap.h"
extern VAR (uint8, CANIF_VAR) CanIf_GaaBitArray[];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include"MemMap.h"
#endif
/* polyspace-en MISRA-C3:8.11 [Not a defect:Justified] "No Impact of this rule violation(Array size will fixed in linking time)" */
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#endif /* CANIF_RAM_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
