/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanIf_TxConfirm.h                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Prototype definition of CanIf_TxConfirm.c                     **
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
** 2.7.4    21-Apr-2021    Sj.Kim    #29445                                   **
** 2.7.0    07-Oct-2020    Sj.Kim    #25877                                   **
** 2.6.2    15-May-2020    Sj.Kim    #23352, #21882, #23360                   **
** 2.6.0    22-Aug-2019    Js.Lim    #18384                                   **
** 2.5.0    06-Dec-2016    Js.Lim    #7077                                    **
** 1.0.0    04-Feb-2013    Kt.Kim    Initial version                          **
*******************************************************************************/
#ifndef CANIF_TXCONFIRM_H
#define CANIF_TXCONFIRM_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf_Tx.h"              /* Transmit Header */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CANIF_TXCONFIRM_AR_RELEASE_MAJOR_VERSION       4
#define CANIF_TXCONFIRM_AR_RELEASE_MINOR_VERSION       0
#define CANIF_TXCONFIRM_AR_RELEASE_REVISION_VERSION    3

/* Software Version Information */
#define CANIF_TXCONFIRM_SW_MAJOR_VERSION    3
#define CANIF_TXCONFIRM_SW_MINOR_VERSION    0
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Inline Function                                       **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* polyspace +1 MISRA-C3:5.5 [Not a defect:High] "No Impact of this rule violation" */
extern FUNC(void, CANIF_CODE) CanIf_DummyTxConfirmation (PduIdType CanTxPduId);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#endif /* CANIF_TX_CONFIRM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
