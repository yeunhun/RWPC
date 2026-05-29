/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Com_Main.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of declaration of main functions.                   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 2.6.0     10-Sep-2020   SM Kwon     Internal Redmine #23914, #25250        **
** 2.4.2     22-Apr-2019   SM Kwon     Internal Redmine #16805                **
** 2.4.0     13-Dec-2018   SM Kwon     Internal Redmine #14067, #15053        **
** 2.2.3     08-Dec-2017   Chan Kim    Internal Redmine #10849, #10851, #10911**
** 2.2.1     24-Aug-2017   Chan Kim    Internal Redmine #9652, #9657          **
** 2.2.0     16-Apr-2017   Chan Kim    Internal Redmine #7525                 **
** 2.1.7     30-Nov-2016   Chan Kim    Internal Redmine #6806, #6807          **
** 2.1.0     25-May-2016   Chan Kim    Internal Redmine #4998                 **
** 2.0.9     19-Feb-2016   Chan Kim    Internal Redmine #4186                 **
** 2.0.8     12-Feb-2016   Chan Kim    Internal Redmine #4139, #4109          **
** 2.0.3     24-Nov-2015   Chan Kim    Internal Redmine #3544, #3535          **
** 1.0.16    27-Feb-2015   Chan Kim    Internal Redmine #2202                 **
** 1.0.14    03-Nov-2014   Chan Kim    Internal Redmine #1463                 **
** 1.0.11    20-Mar-2014   Chan Kim    Internal Redmine #695                  **
** 1.0.0     29-Apr-2013   Autron      Initial Version                        **
*******************************************************************************/

#ifndef COM_MAIN_H
#define COM_MAIN_H
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define COM_MAIN_AR_RELEASE_MAJOR_VERSION  4
#define COM_MAIN_AR_RELEASE_MINOR_VERSION  0
#define COM_MAIN_AR_RELEASE_REVISION_VERSION  3

/* Software Version Information */
#define COM_MAIN_SW_MAJOR_VERSION  2
#define COM_MAIN_SW_MINOR_VERSION  7

/*******************************************************************************
**                      Include Section                                      **
*******************************************************************************/


/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if(COM_TX_IPDU == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, COM_CODE) Com_Transmit
  (PduIdType LddTxIpduId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_SIGNAL_NOTIFY == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_TxSigConfirmation
                            (P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* Redmine #15053: parameter RxIpduId is removed because it is always unused */
#if(COM_RX_SIGNAL == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_RX_SIGNAL_IDSM_ENABLED == STD_ON)
extern FUNC(void, COM_CODE) Com_RxSigProcessing(
                P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
                PduLengthType LddLength,
                P2VAR(Com_IdsMInfo, AUTOMATIC, COM_VAR) LpIdsMInfo);
#else
extern FUNC(void, COM_CODE) Com_RxSigProcessing(
                P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
                PduLengthType LddLength);
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* Redmine #15053: parameter RxIpduId is removed because it is always unused */
#if(COM_RX_SIGGROUP == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_RX_SIGGROUP_IDSM_ENABLED == STD_ON)
extern FUNC(void, COM_CODE) Com_RxSigGrpProcessing(
                P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
                PduLengthType LddLength,
                P2VAR(Com_IdsMInfo, AUTOMATIC, COM_VAR) LpIdsMInfo);
#else
extern FUNC(void, COM_CODE) Com_RxSigGrpProcessing(
                P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu,
                PduLengthType LddLength);
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_TxClearUpdateBit(
                  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu,
                  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSourcePtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"



#if(COM_RX_IPDU_COUNTER_ENABLED == STD_ON)
#if(COM_TP_RX_IPDU_COUNTER_ENABLED == STD_ON)	
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, COM_CODE) Com_RxIpduCounterChk(PduIdType ComRxPduId, 
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSduDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
 #if((COM_TX_SIGNAL_UB == STD_ON) || \
     (COM_TX_SIGGROUP_UB == STD_ON) || \
     (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON) || \
     (COM_TX_IPDU_REPETITION == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"      
extern FUNC(boolean, COM_CODE) Com_TxIpduConfirmation(PduIdType LddComTxPduId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TP_RX_IPDU_COUNTER_ENABLED == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) 
                Com_DoubleBufferCall(P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST)
        LpRxTPIpdu, P2VAR(Com_RxPduInfoType, AUTOMATIC, COM_VAR) LpPduInfoPtr, 
                                  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSduPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) 
                       Com_TpTxConfMDT(P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST)
                                                                      LpRxIpdu);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_REPETITION == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_TPIpduRept(P2CONST(Com_TxMode, AUTOMATIC, COM_CONST)
          LpTxMode, P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_COUNTER_ENABLED == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE)
        Com_TransIpduCounter(P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_TMS_SIG_BASED == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, COM_CODE) 
  Com_SendSigTMS(P2CONST(Com_TxSignal, AUTOMATIC, COM_CONST)
  LpTxSignal, P2CONST(void, AUTOMATIC, COM_CONST) SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_RX_IPDU_CALLOUT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern boolean Com_CallRxIpduCallout(PduIdType PduId, 
  P2CONST(PduInfoType, AUTOMATIC, COM_CONST) PduInfoPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_TRIGGERCALLOUT == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
extern boolean Com_TxIpduTriggerCallout(PduIdType PduId, 
  P2VAR(PduInfoType, AUTOMATIC, COM_VAR) PduInfoPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_PackRequestWrite
    (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,         
    P2CONST (void, AUTOMATIC, COM_CONST) LpDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE) Com_UnPackRequestRead
  (P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,         
  P2VAR(void, AUTOMATIC, COM_VAR) LpDataPtr);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* COM_MAIN_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
