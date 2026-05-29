/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanIf_Rx.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Provision of Receive Indication Functionality                 **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 3.0.0    08-Nov-2021    Sj.Kim    #32882                                   **
** 2.7.2    12-Jan-2021    Sj.Kim    #27560                                   **
** 2.7.1    25-Nov-2020    Sj.Kim    #26002                                   **
** 2.7.0    07-Oct-2020    Sj.Kim    #25877                                   **
** 2.6.2    15-May-2020    Sj.Kim    #23352, #21882, #23360                   **
** 2.6.1    15-May-2020    Js.Lim    #22638                                   **
** 2.6.0    22-Aug-2019    Js.Lim    #18384, #19016                           **
** 2.5.6    10-May-2018    Js.Lim    #12562, #12222                           **
** 2.5.5    10-Jan-2018    Js.Lim    #11197                                   **
** 2.5.4    11-Oct-2017    C.Kim     #9850                                    **
** 2.5.3    20-Jul-2017    Js.Lim    #9287                                    **
** 2.5.2    18-Apr-2017    Js.Lim    #8241                                    **
** 2.5.0    06-Dec-2016    Js.Lim    #6745, #7077                             **
** 2.3.7    13-Jun-2016    Kt.Kim    #5139                                    **
** 2.3.6    18-Mar-2016    Kt.Kim    #4442                                    **
** 2.3.5    11-Mar-2016    Kt.Kim    #4386                                    **
** 2.3.4    12-Feb-2016    Kt.Kim    MISRA Justification                      **
** 2.3.3    25-Aug-2015    Kt.Kim    #2999                                    **
**                                   Justification for Runtime Error          **
** 2.3.2    13-Jun-2015    Kt.Kim    #2724                                    **
** 2.2.0    30-May-2013    Kt.Kim    Lib-Build Support                        **
** 2.1.0    29-May-2013    Kt.Kim    OsekNm Support                           **
** 1.0.0    30-Apr-2013    Kt.Kim    Initial version                          **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf_Ram.h"           /* RAM header file */
#include "CanIf_PCTypes.h"       /* Pre-compile time header file */
#include "CanIf_Rx.h"            /* Receive header */
#include "CanSM_Cbk.h"           /* CAN State Manager call back header file */
#include "SchM_CanIf.h"          /* SchM CanIf Header file */
#include "CanIf_Can.h"                  /* CAN Driver Module Header File */
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#include "CanIf_Error.h"         /* CanIf DET file */
#endif
#if (STD_ON == CANIF_AUTRON_CANTRCV_SUPPORT)
#include "CanTrcv.h"            /* CanTrcv header file */
#endif
#if (STD_ON == CANIF_EXTENAL_CANTRCV_SUPPORT)
#include "CanIf_CanTrcv.h"            /* CanTrcv header file */
#endif
#include "CanIf_UserInc.h"
#if (STD_ON == CANIF_IDSM_SUPPORT)
#include "IdsM_Cbk.h"            /* IdsM Module header file */
#endif
#if (CANIF_CANDRV_VERSION_SUPPORT == CANIF_VER_440)
#include "Can_GeneralTypes.h"
#endif
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define CANIF_RX_C_AR_RELEASE_MAJOR_VERSION    4
#define CANIF_RX_C_AR_RELEASE_MINOR_VERSION    0
#define CANIF_RX_C_AR_RELEASE_REVISION_VERSION 3

/* File version information */
#define CANIF_RX_C_SW_MAJOR_VERSION    3
#define CANIF_RX_C_SW_MINOR_VERSION    0

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANIF_RX_AR_RELEASE_MAJOR_VERSION != \
  CANIF_RX_C_AR_RELEASE_MAJOR_VERSION)
  #error "CANIF_RX.c : Mismatch in Specification Major Version"
#endif
#if (CANIF_RX_AR_RELEASE_MINOR_VERSION != \
  CANIF_RX_C_AR_RELEASE_MINOR_VERSION)
  #error "CANIF_RX.c : Mismatch in Specification Minor Version"
#endif
#if (CANIF_RX_AR_RELEASE_REVISION_VERSION != \
  CANIF_RX_C_AR_RELEASE_REVISION_VERSION)
  #error "CANIF_RX.c : Mismatch in Specification Revision Version"
#endif
#if (CANIF_RX_SW_MAJOR_VERSION != CANIF_RX_C_SW_MAJOR_VERSION)
  #error "CANIF_RX.c : Mismatch in Software Major Version"
#endif
#if (CANIF_RX_SW_MINOR_VERSION != CANIF_RX_C_SW_MINOR_VERSION)
  #error "CANIF_RX.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if ((STD_ON == CANIF_BINARY_SEARCH)||(STD_ON == CANIF_IDTABLE_SEARCH))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* polyspace +1 MISRA-C3:20.7 [Not a defect:Low] "No Impact of this rule violation" */
static FUNC(P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST), CANIF_CODE)
                         CanIf_BinarySearch (
                         P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST) LpRxLpdu,
                         VAR(PduIdType, CANIF_VAR) LddSize,
                         VAR(Can_IdType, CANIF_VAR) LddCanId);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_RX_LPDU)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CANIF_CODE) CanIf_RxNotification (
                         P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST) LpRxLpdu,
                         VAR(uint8, CANIF_VAR) CanDlc,
                         P2CONST(uint8, AUTOMATIC, CANIF_CONST) CanSduPtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if ((STD_ON == CANIF_READRXPDU_NOTIFY_STATUS_API) || \
                                           (STD_ON == CANIF_READRXPDU_DATA_API))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CANIF_CODE) CanIf_RxStatusUpdate (
                       P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST) LpRxLpdu,
                       P2CONST(PduInfoType, AUTOMATIC, CANIF_CONST) PduInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_LINEAR_SEARCH)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* polyspace-begin MISRA-C3:20.7 [Not a defect:Low] "No Impact of this rule violation" */
static FUNC(P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST), CANIF_CODE)
                         CanIf_LinearSearch (
                         P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST) LpRxLpdu,
                         VAR(PduIdType, CANIF_VAR) LddSize,
                         VAR(Can_IdType, CANIF_VAR) LddCanId);
/* polyspace-end MISRA-C3:20.7 [Not a defect:Low] "No Impact of this rule violation" */												 
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* polyspace-begin MISRA-C3:20.7 [Not a defect:Low] "No Impact of this rule violation" */
static FUNC(P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST), CANIF_CODE)
                          CanIf_TriggerSWFilter (
                          P2CONST(CanIf_Hrh, AUTOMATIC, CANIF_CONST) LpHrh,
                          VAR(Can_IdType, CANIF_VAR) CanId);											 
/* polyspace-end MISRA-C3:20.7 [Not a defect:Low] "No Impact of this rule violation" */														 
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/* #5139 */
#if ((STD_ON == CANIF_RX_LPDU) && (STD_ON == CANIF_META_DATA_SUPPORT))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* polyspace-begin MISRA-C3:20.7 [Not a defect:Low] "No Impact of this rule violation" */
static FUNC(P2VAR(uint8, AUTOMATIC, CANIF_VAR), CANIF_CODE) CanIf_RxData
  (Can_IdType CanId, uint8 CanDlc, P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST)
    LpRxLpdu, P2CONST(uint8, AUTOMATIC, CANIF_APPL_CONST) CanSduPtr);
/* polyspace-end MISRA-C3:20.7 [Not a defect:Low] "No Impact of this rule violation" */
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : CanIf_RxNotification                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service provides the Rx Indication to the      **
**                        respective upper layers                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpRxLpdu, CanDlc                                    **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The CAN Interface must be initialised.              **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_GblCanIfStatus            **
**                                            CanIf_GaaRxCbkUser              **
**                        Function(s) invoked:Det_ReportError,                **
**                                            CanIf_RxStatusUpdate,           **
**                                            IdsM_MsgReceptionReport         **
*******************************************************************************/
#if (STD_ON == CANIF_RX_LPDU)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CANIF_CODE) CanIf_RxNotification (
                         P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST) LpRxLpdu,
                         VAR(uint8, CANIF_VAR) CanDlc,
                         P2CONST(uint8, AUTOMATIC, CANIF_CONST) CanSduPtr)
{
  P2CONST(CanIf_RxCbkUser, AUTOMATIC, CANIF_CONST) LpRxCbkUser;
  VAR(PduInfoType, CANIF_VAR) LddPduInfo;
  VAR(PduIdType, CANIF_VAR) LddTargetId;
  VAR(uint8, CANIF_VAR) LucVar;
  VAR(uint8, CANIF_VAR) LucDataLen;
  VAR(uint8, CANIF_VAR) LucDataLenCheck;
  LucDataLen = CanDlc;
  LucDataLenCheck = E_OK;
  /* 8241 */
  #if((STD_ON == CANIF_CANFD_SUPPORT) && (STD_ON == CANIF_CANFD_DISCRETE_DLC_SUPPORT))
  if((CanDlc > CANIF_EIGHT) && (CanDlc < CANIF_16))
  {
    LucDataLen = CanIf_GaaDiscreteDlctoDataLength[CanDlc - CANIF_NINE];
  }
  #endif

  /* polyspace-begin DEFECT:USELESS_IF [Not a defect:Medium] "The value is generated by Generator." */
  /* polyspace-begin MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
  if (CanIf_dlc_check_enable == (uint8)STD_ON)
  /* polyspace-end DEFECT:USELESS_IF [Not a defect:Medium] "The value is generated by Generator." */
  {
    /* polyspace +2 MISRA-C3:18.1 [Not a defect: Justified] "Pointer is not outside its bounds." */
    /* polyspace +1 RTE:IDP [Not a defect: Justified] "Pointer is not outside its bounds." */
    if (LpRxLpdu->ucDlc <= LucDataLen)
      {
        LucDataLenCheck = E_OK;
      }else{
        LucDataLenCheck = E_NOT_OK;
      }
  }
  /* polyspace +1 DEFECT:USELESS_IF [Not a defect: Justified] "Condition will be executed based on the configured values" */
  if(LucDataLenCheck == E_OK)
  {
    /* MISRA Rule    : 11.5
       Message       : Dangerous pointer cast results in loss of const
                       qualification ((uint8 *)CanSduPtr).
       Reason        : This is to achieve throughput in the code.
       Verification  : However, the part of the code is verified
                       manually and it is not having any impact on code.
    */
    /* pointer to function used to indicate the respective upper layer*/
    /*  polyspace<MISRA-C:11.5:Not a defect:Justify with annotations>
    No Impact of this rule violation (the part of the code is verified manually)
    */
    LddPduInfo.SduDataPtr = (uint8 *)CanSduPtr;
    /* Get the SDU length*/
	/* #5139 */
    #if (STD_ON == CANIF_META_DATA_SUPPORT)
    /* Get the SDU length*/    
    LddPduInfo.SduLength =  (PduLengthType)LucDataLen + (PduLengthType)LpRxLpdu->ucMetaDataLength;
    #else
    /* Get the SDU length*/
    LddPduInfo.SduLength =  (uint8)LucDataLen;
    #endif

    #if (STD_ON == CANIF_IDSM_SUPPORT)
    if((LpRxLpdu->ucRxUserOrNotifSts & CANIF_RX_IDSM_REPORT_MASK) != CANIF_ZERO)
    {
      IdsM_MsgReceptionReport(LpRxLpdu->ddRxPduId, &LddPduInfo);
    }
    #endif

    #if ((STD_ON == CANIF_READRXPDU_NOTIFY_STATUS_API) || \
                                         (STD_ON == CANIF_READRXPDU_DATA_API))
    /* Invoke CanIf_RxStatusUpdate for updation of RxPdu structure */
    CanIf_RxStatusUpdate(LpRxLpdu, &LddPduInfo);
    #endif
    /* Get the upper layer user into local variable */
    LucVar = ((CANIF_UL_MASK) & (LpRxLpdu->ucRxUserOrNotifSts));
    /* Check whether any upper layer is configured for upper layer
     indication */
    if (CANIF_MAX_UL >= LucVar)
    {
      /* Get TargetId */
      LddTargetId = (PduIdType)LpRxLpdu->ddTargetId;
      if(STD_ON == CanIf_GddPrecompOpt.ucRxMultipleCallback)
      {
        /* Get the pointer to RxCbkUser structure */
        LpRxCbkUser = &CanIf_GpRxMulCbkUser[LpRxLpdu->ucCallbackIndex];
        /* invoke the respective upper layer Indication for received PDU */
        LpRxCbkUser->pRxIndication(LddTargetId, &LddPduInfo);
      }
      else
      {
        /* polyspace-begin MISRA-C3:18.1, RTE:OBAI,IDP [Not a defect:Justified] "Its boundary is pre-defined" */																
        LpRxCbkUser = &CanIf_GaaRxSingleCbkUser[LucVar];

        /* polyspace +1 RTE:COR [Not a defect:Justified] "function is pre-defined" */
        LpRxCbkUser->pRxIndication(LddTargetId, &LddPduInfo);
        /*CanIf_GaaRxSingleCbkUser[LucVar].pRxIndication(LddTargetId, &LddPduInfo);*/
        /* polyspace-end MISRA-C3:18.1, RTE:OBAI,IDP [Not a defect:Justified] "Its boundary is pre-defined" */	
      }
    } /*  if (CANIF_MAX_UL >= LucVar) */
  } /* if (LpRxLpdu->ucDlc <= LucDiscreteLen) */
  /* polyspace-end MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  else
  {
    /* Report to DET for invalid DLC*/
    (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                                    CANIF_RX_INDICATION_SID, CANIF_E_PARAM_DLC);
  }
  #endif
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON == CANIF_RX_LPDU) */

/*******************************************************************************
** Function Name        : CanIf_RxIndication                                  **
**                                                                            **
** Service ID           : 0x14                                                **
**                                                                            **
** Description          : This service indicates a L-PDU reception of a       **
**                        CAN L-PDU in any of the CAN drivers. This           **
**                        service performs software filtering and DLC check.  **
**                        On successful completion of software filtering and  **
**                        DLC check the upper layer is notified with          **
**                        respective upper layer call back function.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant but not for same HRH                     **
**                                                                            **
** Input Parameters     : Hrh, CanId, CanDlc, CanSduPtr                       **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : The CAN Interface must be initialised               **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_GblCanIfStatus,           **
**                                            CanIf_GaaController             **
**                                            CanIf_GaaHrhMapArray,           **
**                                            CanIf_GaaHrh                    **
**                                            CanIf_GddRxCanId                **
**                        Function(s) invoked:CanIf_RxNotification            **
**                                            SchM_Enter_CanIf_MODE_STATUS_   **
**                                            PROTECTION,                     **
**                                            SchM_Exit_CanIf_MODE_STATUS_    **
**                                            PROTECTION,                     **
**                                            Det_ReportError,                **
**                                            CanIf_TriggerSWFilter           **
*******************************************************************************/
#if (STD_ON == CANIF_RX_LPDU)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
#if ((CANIF_CANDRV_VERSION_SUPPORT == CANIF_VER_440) || \
      (((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
      (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_TWO)) || \
      (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR)))
FUNC(void, CANIF_CODE) CanIf_RxIndication(
           P2CONST(Can_HwType, AUTOMATIC, CANIF_APPL_CONST) Mailbox,
           P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr)
#else
FUNC(void, CANIF_CODE) CanIf_RxIndication(
           VAR(Can_HwHandleType, CANIF_VAR) Hrh,
           VAR(Can_IdType, CANIF_VAR) CanId,
           VAR(uint8, CANIF_VAR) CanDlc,
           P2CONST(uint8, AUTOMATIC, CANIF_APPL_CONST) CanSduPtr)
#endif
{
  /* #5139 */
  P2CONST(uint8, AUTOMATIC, CANIF_APPL_CONST) LpSduPtr;
  P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST) LpRxLpdu;
  P2CONST(CanIf_Hrh, AUTOMATIC, CANIF_CONST) LpHrh;
  P2VAR(CanIf_Controller, AUTOMATIC, CANIF_VAR) LpController;
  VAR(uint8, CANIF_VAR) LucRxStatus;
  VAR(uint8, CANIF_VAR) LucSftwrFltrng;
  VAR(Can_HwHandleType, CANIF_VAR) Lddhrh;
  VAR(Can_IdType, CANIF_VAR) LddCanId;
  VAR(uint8, CANIF_VAR) LucCanDlc;
  VAR(uint8, CANIF_VAR) LucHrhOffset;
  P2CONST(uint8, AUTOMATIC, CANIF_APPL_CONST) LpCanSduPtr;
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  VAR(uint8, CANIF_VAR) LenStdRetVal;
  #endif
  #if ((CANIF_CANDRV_VERSION_SUPPORT == CANIF_VER_440) || \
      (((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
      (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_TWO)) || \
      (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR)))
  /* polyspace-begin MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */
  Lddhrh = Mailbox->Hoh;
  LddCanId = Mailbox->CanId;
  /* DLC is smaller than 256 */
  LucCanDlc = (uint8)PduInfoPtr->SduLength;
  LpCanSduPtr = PduInfoPtr->SduDataPtr;
  /* polyspace-end MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */
  #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
  LucHrhOffset = CanIf_GaaControllerConfigType[Mailbox->ControllerId].ucCanDriverId;
  LucHrhOffset = CanIf_GaaHrhInit[LucHrhOffset].ucHrhOffSetId;
  #else
  LucHrhOffset = CANIF_ZERO;
  #endif
  #else
  Lddhrh = Hrh;
  LddCanId = CanId;
  LucCanDlc = CanDlc;
  LpCanSduPtr = CanSduPtr;
  LucHrhOffset = CANIF_ZERO;
  #endif

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  /* Initialize error status flag to false */
  LenStdRetVal = (uint8)E_OK;
  /* Report to DET, if module is not initialized */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_RX_INDICATION_SID, LenStdRetVal);
  #if (STD_OFF == CANIF_MULTIPLE_CANDRV_SUPPORT)
  /* Report to DET, if HRH Id is out of range */
  /* polyspace +1 MISRA-C3:18.1, RTE:IDP,OBAI [Not a defect:Justified] "Genderated array index in range" */
  CANIF_INVALID_HRH_ERROR(CANIF_RX_INDICATION_SID, Lddhrh, LenStdRetVal);
  #endif

  if ((uint8)E_OK == LenStdRetVal)
  {
    /* polyspace +1 MISRA-C3:D4.14,18.1, RTE:IDP,OBAI [Not a defect: Justified] "Its boundary is pre-defined" */
    LucSftwrFltrng = CanIf_GaaHrh[CanIf_GaaHrhMapArray[Lddhrh]].ucFilterMethod;
    #if ((STD_ON == CANIF_STANDARD_CANID_ONLY) ||\
                                                (STD_ON == CANIF_EXT_STD_CANID))
    /* If CanId is out of range of STD */
    CANIF_INVALID_STANDARD_CANID_ERROR(CANIF_RX_INDICATION_SID, LenStdRetVal);
    #endif
    #if ((STD_ON == CANIF_EXTENDED_CANID_ONLY) ||\
                                                (STD_ON == CANIF_EXT_STD_CANID))
    /* If CanId is out of range of EXT*/
    CANIF_INVALID_EXTENDED_CANID_ERROR(CANIF_RX_INDICATION_SID, LenStdRetVal);
    #endif
    /* Report to DET, if CanSduPtr is null pointer */
    CANIF_NULL_PTR_ERROR(CANIF_RX_INDICATION_SID, LenStdRetVal, LpCanSduPtr);
  }

  /* Check whether any development errors are detected ?*/
  if ((uint8)E_OK == LenStdRetVal)
  #endif /* if development error is not enabled */
  /* Initialize value as null pointer */
  {

    #if(CANIF_BUSLOAD_DETECTING_SUPPORT == STD_ON)
    #if (CANIF_NO_OF_CONTROLLER > CANIF_ONE)
    /* polyspace +1 RTE:OBAI [Not a defect: Justified] "Pointer is not outside its bounds." */
    CanIf_GaaRxMsgCnt[CanIf_GaaHrh[CanIf_GaaHrhMapArray[Lddhrh]].ucControllerId]++;
    #else
    CanIf_GaaRxMsgCnt[CANIF_ZERO]++;
    #endif
    #endif
    /* Get the pointer to HRH structure */
    LpHrh = &CanIf_GaaHrh[CANIF_ZERO];
    /*  polyspace<MISRA-C:17.4:Not a defect:Justify with annotations> Array Indexing is not used to achieve better throughput. */
    /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
    LpHrh += ((CanIf_PtrSize)CanIf_GaaHrhMapArray[Lddhrh + LucHrhOffset]);

    #if (CANIF_NO_OF_CONTROLLER > CANIF_ONE)
    /* Check which CanDrv version supported */
    #if ((CANIF_CANDRV_VERSION_SUPPORT == CANIF_VER_440) || \
      (((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
      (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_TWO)) || \
      (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR)))
    /* Get the pointer to Controller */
    LpController = &CanIf_GaaController[Mailbox->ControllerId];
    #else
    /* Get the pointer to Controller */
    LpController = &CanIf_GaaController[LpHrh->ucControllerId];
    #endif
    #else
    /* Get the pointer to Controller for single CanIfController configured */
    LpController = &CanIf_GaaController[CANIF_ZERO];
    #endif
    /* Save CAN identifier to global variable */
    CanIf_GddRxCanId = LddCanId;
    /* Check if Rx status of controller is set */
   /* polyspace<RTE: IDP : Not a defect : No Action Planned >
      Its boundary is pre-defined           */
    /* polyspace +1 MISRA-C3:18.1 [Not a defect: Justified] "Pointer is not outside its bounds." */
    LucRxStatus = LpController->ucRxStatus;
    /* Check the rx status of controller is not disabled */
    if (CANIF_RX_DISABLED != LucRxStatus)
    {
      #if ((STD_ON == CANIF_WAKEUP_CHECK_VALIDATION_SUPPORT))
      /* Check the rx status of controller is enabled */
      if (CANIF_RX_ENABLED == LucRxStatus)
      {
        /* Disable relevant interrupts */
        SchM_Enter_CanIf_MODE_STATUS_PROTECTION();
        /* Set the wakeup validation flag  - CANIF_RX_VALIDATE_WAKEUP 0x81 */
        LpController->ucRxStatus = CANIF_RX_VALIDATE_WAKEUP;
        /* Enable relevant interrupts */
        SchM_Exit_CanIf_MODE_STATUS_PROTECTION();
      }
      #endif
      /* Check whether that HRH is FullCAN or BasicCAN */
      /* polyspace +2 MISRA-C3:18.1 [Not a defect: Justified] "Pointer is not outside its bounds." */
      /* polyspace +1 RTE:IDP [Not a defect: Justified] "Pointer is not outside its bounds." */
      LucSftwrFltrng = LpHrh->ucFilterMethod;
      /* Filter Method :
         0x00: -> BasicCAN WITH STANDARD
         0x01: -> BASICCAN WITH EXTENDED
         0x02: -> BASICCAN WITH MIXED
         0x03: -> FULLCAN WITH STANDARD
         0x04: -> FULLCAN WITH EXTENDED
         0x05: -> FULLCAN WITH MIXED
      Check whether received CAN-ID is type of FullCAN or BasicCAN */
      /* polyspace-begin MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
      if ((LucSftwrFltrng <= CANIF_RX_BASIC_CAN_MIXED )
        && (STD_ON == CanIf_GddPrecompOpt.ucRxBasicCanSupport))
      {
        /* call the S/W triggerring function */
        #if (STD_ON == CANIF_CANFD_SUPPORT)
        if(LucSftwrFltrng == CANIF_RX_BASIC_CAN_EXT)
        {
          LpRxLpdu =
             CanIf_TriggerSWFilter(LpHrh, (Can_IdType)(LddCanId & CANIF_EXTENDED_CANID_VALUE));
        }
        else
        {
          LpRxLpdu =
             CanIf_TriggerSWFilter(LpHrh, (Can_IdType)(LddCanId & CANIF_STANDARD_CANID_VALUE));
        }
        #else
          LpRxLpdu =
             CanIf_TriggerSWFilter(LpHrh, LddCanId);
        #endif /* STD_ON == CANIF_CANFD_SUPPORT */
        /* Check whether Rx LPDU is null pointer and invoke notification */
        if (LpRxLpdu != NULL_PTR)
        {
          /* #5139 */
          #if ((STD_ON == CANIF_RX_LPDU) && (STD_ON == CANIF_META_DATA_SUPPORT))
          LpSduPtr = CanIf_RxData(LddCanId, LucCanDlc, LpRxLpdu, LpCanSduPtr);
          #else
          LpSduPtr = LpCanSduPtr;
          #endif /* (STD_ON == CANIF_RX_LPDU) && (STD_ON == CANIF_META_DATA_SUPPORT) */
          CanIf_RxNotification(LpRxLpdu, LucCanDlc, LpSduPtr);
        }
      }
      /* polyspace-end MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
      /* For the Case of FULL CAN */
      else
      {
        /* Get the pointer to desired Rx L-PDU of range/list type */
        #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
        LpRxLpdu = &CanIf_GaaRxLpduSelect[LpHrh->ddRxLpduIndex];
        #else
        LpRxLpdu = &CanIf_GaaRxLpdu[LpHrh->ddRxLpduIndex];
        #endif

        /* Invoke CanIf_RxNotification to invoke upper layer indication */
        CanIf_RxNotification(LpRxLpdu, LucCanDlc, LpCanSduPtr);
      }
    }/* if (CANIF_RX_DISABLED != LucRxStatus) */
  } /* if CANIF_DEV_ERROR_DETECT */
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_ReadRxNotifStatus                             **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : This service provides the status of the CAN Rx      **
**                        L-PDU requested by CanRxPduId. This API service     **
**                        notifies the upper layer about any transmit         **
**                        confirmation or receive indication event to the     **
**                        corresponding requested CAN Rx L-PDU.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : CanRxPduId                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : CanIf_NotifStatusType(CANIF_NO_NOTIFICATION,        **
**                                           CANIF_TX_RX_NOTIFICATION)        **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized               **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_GblCanIfStatus            **
**                                            CanIf_GaaController,            **
**                                            CanIf_GaaRxLpduNotify           **
**                        Function(s) invoked:Det_ReportError                 **
**                                            SchM_Enter_CanIf_RX_NOTIFSTATUS_**
**                                            PROTECTION,                     **
**                                            SchM_Exit_CanIf_RX_NOTIFSTATUS_ **
**                                            PROTECTION                      **
**                                                                            **
*******************************************************************************/
#if (STD_ON == CANIF_READRXPDU_NOTIFY_STATUS_API)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(CanIf_NotifStatusType, CANIF_CODE) CanIf_ReadRxNotifStatus (
                                           VAR(PduIdType, CANIF_VAR) CanRxPduId)
{
  P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST) LpRxLpdu;
  P2VAR(CanIf_RxLpduNotify, AUTOMATIC, CANIF_VAR) LpRxLpduNotify;
  CanIf_NotifStatusType LenNotifStsType;
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  uint8 LucNotifStatus;
  uint8 LenStdRetVal;
  #endif
  uint8 LucPdu;
  uint16 LusRxPduCnt;

  LusRxPduCnt = CanIf_GddPrecompOpt.ddNumOfRxPdu;
  LucPdu = CANIF_FALSE;
  /* Initialize LenNotifStsType to CANIF_NO_NOTIFICATION */
  LenNotifStsType = CANIF_NO_NOTIFICATION;
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  LenStdRetVal = CANIF_ZERO;
  /* Report to DET, if module is not initialized */

  if ((boolean)CANIF_UNINITIALISED == CanIf_GblCanIfStatus)
  {
    (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                                CANIF_READ_RX_NOTIF_STATUS_SID, CANIF_E_UNINIT);
    LenStdRetVal++;
  }
  /* Report to DET, if RXPDUID is not in limits */

  if (CanRxPduId >= CanIf_GddPrecompOpt.ddNumOfRxPdu)
  {
    (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                       CANIF_READ_RX_NOTIF_STATUS_SID, CANIF_E_INVALID_RXPDUID);
    LenStdRetVal++;
  }
  #if (STD_OFF == CANIF_READRXPDU_DATA_API)
  (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                       CANIF_READ_RX_NOTIF_STATUS_SID, CANIF_E_INVALID_RXPDUID);
  LenStdRetVal++;
  #endif
  if ((uint8)CANIF_ZERO == LenStdRetVal)
  #endif
  {
    /* Get the pointer to first Rx L-PDU of range/list type */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    LpRxLpdu = &CanIf_GaaRxLpduSelect[CANIF_ZERO];
    #else
    LpRxLpdu = &CanIf_GaaRxLpdu[CANIF_ZERO];
    #endif
    /* Get the pointer to desired Rx L-PDU of range/list type */
    do
    {
      /* #5139 */
      /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
      if (CanRxPduId != (PduIdType)LpRxLpdu->ddRxPduId)
      {
        
        LpRxLpdu++;
        LusRxPduCnt--;
      }
      else
      {
        #if (STD_ON == CANIF_DEV_ERROR_DETECT)
        LucNotifStatus = LpRxLpdu->ucRxUserOrNotifSts;
        /* Report to DET if Status information is not available for RxPDU*/
        /* polyspace +1 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
        if ((LucNotifStatus & CANIF_RX_NOTIFY_STATUS_MASK) == CANIF_ZERO)
        {
          (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                       CANIF_READ_RX_NOTIF_STATUS_SID, CANIF_E_INVALID_RXPDUID);

          LenStdRetVal++;
        }/* if ((LucNotifStatus & 0x10) == CANIF_ZERO) */
        #endif
        /* to break the loop */
        LucPdu = CANIF_TRUE;
      }
    }while((LucPdu != CANIF_TRUE) && (LusRxPduCnt != CANIF_ZERO));

    #if (STD_ON == CANIF_DEV_ERROR_DETECT)
    /* Check whether any development error are detected */
    /* polyspace +1 MISRA-C3:14.3, DEFECT:USELESS_IF [Not a defect: Justified] "Condition will be executed based on the configured values" */
    if ((uint8)CANIF_ZERO == LenStdRetVal)
    #endif
    {
      if (LucPdu == CANIF_TRUE)
      {
        /* Get the pointer to RxLpduNotify structure */
        /* polyspace +1 MISRA-C3:18.4 [Not a defect: Justified] "Decrement and Increment operator is used to achieve better throughput" */
        LpRxLpduNotify = &CanIf_GaaRxLpduNotify[CANIF_ZERO] +
                                                         LpRxLpdu->ddRxNotifyId;
        /* Check whether RxLpduStatus is set or not */
        if ((LpRxLpduNotify->ucDlcOrNotify & CANIF_NOTIFY_STATUS_MASK) !=
                                                              (uint8)CANIF_ZERO)
        {
          /* Disable relevant interrupts */
          SchM_Enter_CanIf_RX_NOTIFSTATUS_PROTECTION();
          /* Reset the notification status */
          LpRxLpduNotify->ucDlcOrNotify &= (uint8)(~CANIF_NOTIFY_STATUS_MASK);
          /* Enable relevant interrupts */
          SchM_Exit_CanIf_RX_NOTIFSTATUS_PROTECTION();
          /* Set Rx notification to an upper layer */
          LenNotifStsType = CANIF_TX_RX_NOTIFICATION;
        } /*  if ((LpRxLpduNotify->ucDlcOrNotify & ... */
      } /* if (LucPdu == CANIF_TRUE) */
    } /* if ((uint8)E_OK == LenStdRetVal) */
  }/* if (E_OK == LenStdRetVal)*/
  return(LenNotifStsType);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_ReadRxPduData                                 **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : This service provides the CAN DLC and the received  **
**                        data of the requested CanRxPduId to the calling     **
**                        upper layer.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : CanRxPduId                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : PduInfoPtr                                          **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized               **
**                                                                            **
** Remarks              : Global Variable(s):  CanIf_GblCanIfStatus,          **
**                                             aaRxBufferData                 **
**                                             CanIf_GaaRxLpduNotify,         **
**                                             CanIf_GaaController            **
**                        Function(s) invoked: Det_ReportError                **
**                                             SchM_Enter_CanIf_RX_DATA_      **
**                                             PROTECTION                     **
**                                             SchM_Exit_CanIf_RX_DATA_       **
**                                             PROTECTION                     **
*******************************************************************************/
#if (STD_ON == CANIF_READRXPDU_DATA_API)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_ReadRxPduData (
                      VAR(PduIdType, CANIF_VAR) CanRxPduId,
                      P2VAR(PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr)
{
  P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST) LpRxLpdu;
  P2VAR(CanIf_Controller, AUTOMATIC, CANIF_VAR)LpController;
  P2VAR(CanIf_RxLpduNotify, AUTOMATIC, CANIF_VAR) LpRxLpduNotify;
  P2VAR (uint8, AUTOMATIC, CANIF_VAR) LpDataPtr;
  Std_ReturnType LenStdRetVal;
  uint8 LucDlc;
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  uint8 LucNotifStatus;
  #endif
  uint8 LucPdu;
  uint16 LusRxPduCnt;
  LucPdu = CANIF_FALSE;
  LusRxPduCnt = CanIf_GddPrecompOpt.ddNumOfRxPdu;
  #if (STD_OFF == CANIF_DEV_ERROR_DETECT)
  LenStdRetVal = E_OK;
  #else
  /* Initialize standard return type to E_OK */
  LenStdRetVal = CANIF_ZERO;
  /* Report to DET, if module is not initialized */

  if ((boolean)CANIF_UNINITIALISED == CanIf_GblCanIfStatus)
  {
    (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                                     CANIF_READ_RXPDU_DATA_SID, CANIF_E_UNINIT);
    LenStdRetVal++;
  }

  /* Report to DET, if RXPDUID is not in range */

  if (CanRxPduId >= CanIf_GddPrecompOpt.ddNumOfRxPdu)
  {
    (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                            CANIF_READ_RXPDU_DATA_SID, CANIF_E_INVALID_RXPDUID);
    LenStdRetVal++;
  }
  /* Report to DET, if PduInfopointer is a Null Pointer */

  if (PduInfoPtr == NULL_PTR)
  {
    (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                              CANIF_READ_RXPDU_DATA_SID, CANIF_E_PARAM_POINTER);
    LenStdRetVal++;
  }
  else
  {
    /* polyspace +1 MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */	
    if (PduInfoPtr->SduDataPtr == NULL_PTR)
    {
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                              CANIF_READ_RXPDU_DATA_SID, CANIF_E_PARAM_POINTER);
      LenStdRetVal++;
    }
  }
  if ((uint8)CANIF_ZERO == LenStdRetVal)
  #endif
  {
    /* Get the pointer to first Rx L-PDU of range/list type */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    LpRxLpdu = &CanIf_GaaRxLpduSelect[CANIF_ZERO];
    #else
    LpRxLpdu = &CanIf_GaaRxLpdu[CANIF_ZERO];
    #endif
    /* Get the RxNotifyId */
    do
    {
      /* #5139 */
      /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
      if (CanRxPduId != (PduIdType)LpRxLpdu->ddRxPduId)
      {
        LpRxLpdu++;
        LusRxPduCnt--;
      }
      else
      {
        #if (STD_ON == CANIF_DEV_ERROR_DETECT)
        LucNotifStatus = LpRxLpdu->ucRxUserOrNotifSts;
        /* Report to DET if Read data is not available for RxPDU*/
        /* polyspace +1 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
        if ((LucNotifStatus & CANIF_RX_DATA_STATUS_MASK) == CANIF_ZERO)
        {
          (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                            CANIF_READ_RXPDU_DATA_SID, CANIF_E_INVALID_RXPDUID);

          LenStdRetVal++;
        }




        #endif
        LucPdu = CANIF_TRUE;
      }
    }while((LucPdu != CANIF_TRUE) && (LusRxPduCnt != CANIF_ZERO));

    #if (STD_ON == CANIF_DEV_ERROR_DETECT)
    /* Check whether any development error are detected */
    /* polyspace +1 MISRA-C3:14.3, DEFECT:USELESS_IF [Not a defect: Justified] "Condition will be executed based on the configured values" */
    if ((uint8)CANIF_ZERO == LenStdRetVal)
    #endif
    {
      if (LucPdu == CANIF_TRUE)
      {
        /* Set the LenStdRetVal */
        LenStdRetVal = (Std_ReturnType)E_NOT_OK;
        /* Point to Controller */
        LpController =  &CanIf_GaaController[LpRxLpdu->ucControllerId];
        /* Check if controller mode is started */
        if ((uint8) CANIF_CS_STARTED == LpController->ucControllerMode)
        {
          /* Check ucRxStatus of controller */
          if (CANIF_RX_DISABLED != LpController->ucRxStatus)
          {
            /* Set the LenStdRetVal */
            LenStdRetVal = (Std_ReturnType)E_OK;
            /* Get the pointer to RxLpduNotify structure */
            /* polyspace +1 MISRA-C3:18.4 [Not a defect: Justified] "Decrement and Increment operator is used to achieve better throughput" */
            LpRxLpduNotify = &CanIf_GaaRxLpduNotify[CANIF_ZERO] +
                                                           LpRxLpdu->ddRxNotifyId;
            /* Get the DLC */
            LucDlc = ((LpRxLpduNotify->ucDlcOrNotify) &
                                                      (CANIF_RX_DLC_STATUS_MASK));
            /* Store Length */
            /* polyspace +1 MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */
            PduInfoPtr->SduLength = (uint8)LucDlc;
            /* Get the pointer to SduDataPtr */
            LpDataPtr = (PduInfoPtr->SduDataPtr);
            /* Disable relevant interrupts */
            SchM_Enter_CanIf_RX_DATA_PROTECTION();
            /* Loop to copy the data from BufferData to DataPtr */
            while ((uint8)CANIF_ZERO != LucDlc)
            {
              /* Decrement DLC counter */
              LucDlc--;
              /* Copy the data */
              /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
              LpDataPtr[LucDlc] = LpRxLpduNotify->aaRxBufferData[LucDlc];
              /* Increment buffer pointer by one */
            }
            /* Enable relevant interrupts */
            SchM_Exit_CanIf_RX_DATA_PROTECTION();
          }/* if (E_OK == LenStdRetVal) */
        }/* if ((uint8) CANIF_CS_STARTED == LpController->ucControllerMode) */
      } /* if (LucPdu == CANIF_TRUE) */
    }/* if (E_OK == LenStdRetVal) */
  }/* if (E_OK == LenStdRetVal)*/
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  else
  {
    LenStdRetVal = (uint8)E_NOT_OK;
  }
  #endif
  /* Return std return value */
  return(LenStdRetVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/* #5139 */
/*******************************************************************************
** Function Name        : CanIf_RxData                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service provides the Rx Indication to the      **
**                        respective upper layers                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpRxLpdu, CanDlc                                    **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The CAN Interface must be initialised.              **
**                                                                            **
** Remarks              : Global Variable(s): None                            **
**                                                                            **
**                        Function(s) invoked:None                            **
*******************************************************************************/
#if ((STD_ON == CANIF_RX_LPDU) && (STD_ON == CANIF_META_DATA_SUPPORT))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* polyspace-begin MISRA-C3:20.7 [Not a defect:Low] "No Impact of this rule violation" */
static FUNC(P2VAR(uint8, AUTOMATIC, CANIF_VAR), CANIF_CODE) CanIf_RxData
  (Can_IdType CanId, uint8 CanDlc, P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST)
    LpRxLpdu, P2CONST(uint8, AUTOMATIC, CANIF_APPL_CONST) CanSduPtr)
/* polyspace-end MISRA-C3:20.7 [Not a defect:Low] "No Impact of this rule violation" */
{
  Can_IdType LulCanId = CanId;
  static uint8 Lucdata[CANIF_TWELVE];
  uint8 LucMetadata[CANIF_FOUR];
  uint8 Luclength;
  uint8 LucPayLoadlength;
  uint32 LulRxCanIdMask;
  Luclength = CANIF_ZERO;
  LucPayLoadlength = CANIF_ZERO;
  /* polyspace-begin DEFECT:USELESS_WRITE [Not a defect:Low] "No Impact of this rule violation" */
  /* polyspace +1 MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
  LulRxCanIdMask = CANIF_ZERO;
  /* polyspace-end DEFECT:USELESS_WRITE [Not a defect:Low] "No Impact of this rule violation" */

 LulRxCanIdMask = LpRxLpdu->ulCanIfRxPduCanIdMask;
  switch (LpRxLpdu->ucMetaDataLength)
  {
    case CANIF_ONE:
      LulCanId = LulCanId & LulRxCanIdMask;
      LulCanId = LulCanId & CANIF_CANID_MASK_ONE;
      LucMetadata[CANIF_ZERO] = (uint8)LulCanId;
      Lucdata[Luclength] = LucMetadata[CANIF_ZERO];
      Luclength++;
      break;

    case CANIF_TWO:
      LulCanId = LulCanId & LulRxCanIdMask;
      LulCanId = LulCanId & CANIF_CANID_MASK_TWO;
      LucMetadata[CANIF_ZERO] = (uint8)((LulCanId & CANIF_MASK_BYTE_ONE) >> CANIF_EIGHT);
      Lucdata[Luclength] = LucMetadata[CANIF_ZERO];
      Luclength++;
      LucMetadata[CANIF_ONE] = (uint8)(LulCanId & CANIF_CANID_MASK_ONE);
      Lucdata[Luclength] = LucMetadata[CANIF_ONE];
      Luclength++;
      break;

    case CANIF_FOUR:
      LulCanId = LulCanId & CANIF_CANID_MASK_FOUR;
      LucMetadata[CANIF_ZERO] = (uint8)((LulCanId & CANIF_MASK_BYTE_FOUR) >>
                                                              CANIF_TWENTY_FOUR);
      Lucdata[Luclength] = LucMetadata[CANIF_ZERO];
      Luclength++;
      LucMetadata[CANIF_ONE] = (uint8)((LulCanId & CANIF_MASK_BYTE_THREE) >> CANIF_SIXTEEN);
      Lucdata[Luclength] = LucMetadata[CANIF_ONE];
      Luclength++;
      LucMetadata[CANIF_TWO] = (uint8)((LulCanId & CANIF_MASK_BYTE_ONE) >> CANIF_EIGHT);
      Lucdata[Luclength] = LucMetadata[CANIF_TWO];
      Luclength++;
      LucMetadata[CANIF_THREE] = (uint8)(LulCanId & CANIF_CANID_MASK_ONE);
      Lucdata[Luclength] = LucMetadata[CANIF_THREE];
      Luclength++;
      break;

    default:
      /* empty */
      break;
  }
  /* polyspace-begin MISRA-C3:D4.14,18.1, RTE:OBAI [Not a defect: Justified] "It will not occur." */
  while(LucPayLoadlength < CanDlc)
  {
    Lucdata[Luclength] = CanSduPtr[LucPayLoadlength];
    LucPayLoadlength++;
    Luclength++;
  }
  /* polyspace-end MISRA-C3:D4.14,18.1, RTE:OBAI [Not a defect: Justified] "It will not occur." */
  return Lucdata;
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : CanIf_BinarySearch                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to implement the Binary       **
**                        search                                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpHrh, LddSize, LddCanId                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : LpRxLpdu                                            **
**                                                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                        None                                                **
*******************************************************************************/
#if ((STD_ON == CANIF_BINARY_SEARCH)||(STD_ON == CANIF_IDTABLE_SEARCH))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* polyspace +1 MISRA-C3:20.7 [Not a defect:Low] "No Impact of this rule violation" */
static FUNC(P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST), CANIF_CODE)
                         CanIf_BinarySearch (
                         P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST) LpRxLpdu,
                         VAR(PduIdType, CANIF_VAR) LddSize,
                         VAR(Can_IdType, CANIF_VAR) LddCanId)
{
  P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST) LpRxLpduRetVal;
  VAR(Can_IdType, CANIF_VAR) LddListCanId;
  VAR(PduIdType, CANIF_VAR) LddLow;
  VAR(PduIdType, CANIF_VAR) LddHigh;
  VAR(PduIdType, CANIF_VAR) LddMid;

  /* Initialize LddHigh variable with number of List L-PDUs - 1 */
  LddHigh = LddSize - (PduIdType)CANIF_ONE;
  /* Initialize LddLow variable with zero */
  LddLow = (PduIdType)CANIF_ONE;
  /* Initialize return value with null pointer */
  LpRxLpduRetVal = NULL_PTR;
  /* Get the lower limit of CAN-ID */
  /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Genderated array index in range" */	
  LddListCanId = (LpRxLpdu->ddCanIdLl);
  /* polyspace:begin<MISRA-C:17.4:Not a defect:Justify with annotations> Array Indexing is not used to achieve better throughput. */

  /* Check whether search CAN-ID is in range */
  if ((LddCanId >= LddListCanId) &&
  /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Genderated array index in range" */	
  (LddCanId <= (Can_IdType)((LpRxLpdu + ((CanIf_PtrSize)LddHigh))->ddCanIdLl)))
  {
    /* #5139 */
    /* Check whether requested CAN-ID is same as first CAN-ID of the list */
    #if ((STD_ON == CANIF_RX_LPDU) && \
                                           (STD_ON == CANIF_META_DATA_SUPPORT))
    /* #9287 */
    /* #33236 modify the comparison condition */
    if ((LddCanId & (LpRxLpdu->ulCanIfRxPduCanIdMask)) !=
              (LddListCanId & (LpRxLpdu->ulCanIfRxPduCanIdMask)))
    #else
    /* Check whether requested CAN-ID is same as first CAN-ID of the list */
    if (LddCanId != LddListCanId)
    #endif
    {
      do
      {
        /* Get the middle index number */
        LddMid = (LddHigh + LddLow) >> (PduIdType)CANIF_ONE;

        /* Get the CAN-ID of the mid Rx L-PDU */
        /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Genderated array index in range" */	
        LddListCanId = (Can_IdType)((LpRxLpdu + ((CanIf_PtrSize)LddMid))->ddCanIdLl);
        /* Compare CAN-ID with the requested one */
        /* #5139 */
        #if ((STD_ON == CANIF_RX_LPDU) && \
                                           (STD_ON == CANIF_META_DATA_SUPPORT))
        /* #33236 modify the comparison condition */
        if ((LddCanId & ((LpRxLpdu + ((CanIf_PtrSize)LddMid))->ulCanIfRxPduCanIdMask) ) ==
                  (LddListCanId & ((LpRxLpdu + ((CanIf_PtrSize)LddMid))->ulCanIfRxPduCanIdMask)))

        #else
        if (LddListCanId == LddCanId)
        #endif
        {
          /* Update the return pointer with the Rx L-PDU structure */
          LpRxLpduRetVal = (P2CONST(CanIf_RxLpdu, AUTOMATIC,
                                 CANIF_CONST))(LpRxLpdu + ((CanIf_PtrSize)LddMid));
          /* Set LddHigh to zero to break the loop */
          LddHigh = (PduIdType)CANIF_ZERO;
        }
        else
        {
          /* Compare the CAN-ID with the requested one */
          if (LddCanId < LddListCanId)
          {
            /* If the priority is lower, update LddHigh */
            /* polyspace +1 DEFECT:SIGN_CHANGE [Not a defect: Justified] "Overflow will not occur" */
            LddHigh = LddMid - (PduIdType)CANIF_ONE;
          }
          else
          {
            /* If the priority is higher, update LddLow */
            LddLow = LddMid + (PduIdType)CANIF_ONE;
          }
        }
      }while (LddLow <= LddHigh);
    } /* if (LddCanId != LddListCanId) */
    else
    {
      /* Update the return pointer with the actual Rx L-PDU structure */
      LpRxLpduRetVal = LpRxLpdu;
    }
  } /* if (LddListCanId != LddCanId) */
  /* Return RxLpduRetVal pointer */
  /* polyspace:end<MISRA-C:17.4:Not a defect:Justify with annotations> Array Indexing is not used to achieve better throughput. */
  return (LpRxLpduRetVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_TriggerSWFilter                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is triggerred to do the software      **
**                        filtering for the CanIds                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpHrh, CanId                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : LpRxLpdu                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                        None                                                **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* polyspace +1 MISRA-C3:20.7 [Not a defect:Low] "No Impact of this rule violation" */
static FUNC(P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST), CANIF_CODE)
                          CanIf_TriggerSWFilter (
                          P2CONST(CanIf_Hrh, AUTOMATIC, CANIF_CONST) LpHrh,
                          VAR(Can_IdType, CANIF_VAR) CanId)
{
  P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST) LpRxLpdu;
  VAR(PduIdType, CANIF_VAR) LddNoOfLpdus;
  #if ((STD_ON == CANIF_BINARY_SEARCH) || (STD_ON == CANIF_LINEAR_SEARCH))|| (STD_ON == CANIF_IDTABLE_SEARCH)
  VAR(uint8, CANIF_VAR) LucFilterStatus;
  #endif
  #if(STD_ON == CANIF_IDTABLE_SEARCH)
  VAR(uint8, CANIF_VAR) LucLdpuIdTableIndex;
  P2CONST(CanIf_RxLpduIdTable, AUTOMATIC, CANIF_CONST) LpRxLpduIdTable;
  #endif
  /* Get the pointer to first Rx L-PDU of range/list type */
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  LpRxLpdu = &CanIf_GaaRxLpduSelect[LpHrh->ddRxLpduIndex];
  #else
  LpRxLpdu = &CanIf_GaaRxLpdu[LpHrh->ddRxLpduIndex];
  #endif
  #if ((STD_ON == CANIF_BINARY_SEARCH) || (STD_ON == CANIF_LINEAR_SEARCH))|| (STD_ON == CANIF_IDTABLE_SEARCH)
  /* Check the filter method for BASIC or FULL can*/
  LucFilterStatus = CANIF_FAILURE;
  #endif
  /* Get the number of ranges supported for that HRH */
  LddNoOfLpdus  =  LpHrh->ddNoOfRxLpdusRange;
  /* Check whether HRH is configured for range */
  while ((PduIdType)CANIF_ZERO != LddNoOfLpdus)
  {
    /* Check whether CAN-ID is in range */
    /* polyspace +2 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
    /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Genderated array index in range" */	
    if ((CanId >= LpRxLpdu->ddCanIdLl) && (CanId <= LpRxLpdu->ddCanIdUl))
    {
     #if ((STD_ON == CANIF_BINARY_SEARCH) || (STD_ON == CANIF_LINEAR_SEARCH)) || (STD_ON == CANIF_IDTABLE_SEARCH)
      /* Make software filtering successful (0x80) */
      LucFilterStatus = CANIF_RANGE_SUCCESS;
      #endif
      /* Break the loop */
      LddNoOfLpdus = (PduIdType)CANIF_ZERO;
    } /* if ((CanId >= LddCanId) && (CanId <= */
    else
    {
      /* Decrement the number of Tx L-PDU(s) */
      LddNoOfLpdus--;
      /* Increment the RxLpdu structure */
      /* polyspace<MISRA-C:17.4:Not a defect:Justify with annotations> Increment is used to achieve better throughput. */
      LpRxLpdu++;
    }
  } /* while(LddNoOfLpdus != CANIF_ZERO);*/
  #if(STD_ON == CANIF_IDTABLE_SEARCH)
  /* Index Search Controller ID * 8(IP Table Number of each Controller) */
  LucLdpuIdTableIndex = ((LpRxLpdu->ucControllerId * CANIF_IPTABLE_COUNT)+((CanId&CANIF_STANDARD_ID_FIRSTBIT_MASK) >> CANIF_IPTABLE_COUNT));
  #endif
  #if ((STD_ON == CANIF_BINARY_SEARCH) || (STD_ON == CANIF_LINEAR_SEARCH)) || (STD_ON == CANIF_IDTABLE_SEARCH)
  /* Check whether id is found in range search */
  /* polyspace +1 MISRA-C3:2.1,14.3, DEFECT:USELESS_IF [Not a defect: Justified] "Condition will be executed based on the configured values" */
  if (CANIF_FAILURE == LucFilterStatus)
  {
    #if(STD_ON == CANIF_IDTABLE_SEARCH)
    LpRxLpduIdTable = &CanIf_GaaRxLpduIdTable[LucLdpuIdTableIndex];
    /* Get the pointer to first Rx L-PDU of range/list type */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    LpRxLpdu = &CanIf_GaaRxLpduSelect[LpRxLpduIdTable->ddRxLpduIdTableIndex];
    #else
    LpRxLpdu = &CanIf_GaaRxLpdu[LpRxLpduIdTable->ddRxLpduIdTableIndex];
    #endif
    LddNoOfLpdus = LpRxLpduIdTable->ddNoOfRxLpdusRange;
    #else
    /* Get the number of List IDs from HRH structure */
    LddNoOfLpdus = LpHrh->ddNoOfRxLpdusList;
    #endif
    /* Check whether any list L-PDUs configured for that HRH */
    if ((PduIdType)CANIF_ZERO != LddNoOfLpdus)
    {
      /* Check filter method for that HRH*/
      #if (STD_ON == CANIF_BINARY_SEARCH) || (STD_ON == CANIF_IDTABLE_SEARCH)
      /* Do the Binary Search */
      LpRxLpdu = CanIf_BinarySearch(LpRxLpdu, LddNoOfLpdus, CanId);
      #endif

      #if (STD_ON == CANIF_LINEAR_SEARCH)
      /* Linear Search */
      LpRxLpdu = CanIf_LinearSearch(LpRxLpdu, LddNoOfLpdus, CanId);
      #endif

    } /* if (LddNoOfLpdus != CANIF_ZERO) */
    else
    {
      /* Initialize value as null pointer */
      LpRxLpdu = NULL_PTR;
    }
  } /* if (CANIF_FAILURE == LucFilterStatus)  */
  #endif /* #if ((STD_ON == CANIF_BINARY_SEARCH) ||(...)) */
  /* Check whether software check returns true */
  return (LpRxLpdu);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_LinearSearch                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to implement the liear search **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpHrh, LddSize, LddCanId                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : LpRxLpdu                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                        None                                                **
*******************************************************************************/
#if (STD_ON == CANIF_LINEAR_SEARCH)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* polyspace +1 MISRA-C3:20.7 [Not a defect:Low] "No Impact of this rule violation" */
static FUNC(P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST), CANIF_CODE)
                         CanIf_LinearSearch (
                         P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST) LpRxLpdu,
                         VAR(PduIdType, CANIF_VAR) LddSize,
                         VAR(Can_IdType, CANIF_VAR) LddCanId)
{
  /* Copy LpRxLpdu to LpCpyRxLpdu */
  P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST) LpCpyRxLpdu = LpRxLpdu;
  VAR(PduIdType, CANIF_VAR) LddCpySize = LddSize;

  VAR(boolean, CANIF_VAR) LblSearchValue;
  /* Initialize search value to false */
  LblSearchValue = CANIF_FALSE;
  /*Loop all the Rx L-PDUs for the requested CAN ID. */
  do
  {
    /* If the CAN-ID is found in database,
       >> set the flag
       >> break the loop
    */
	/* #5139 */
    #if ((STD_ON == CANIF_RX_LPDU) && \
                                    (STD_ON == CANIF_META_DATA_SUPPORT))
    if (((LpCpyRxLpdu->ddCanIdLl) | (LpCpyRxLpdu->ulCanIfRxPduCanIdMask)) ==
                (LddCanId | (LpCpyRxLpdu->ulCanIfRxPduCanIdMask)))
    #else
    if (LpCpyRxLpdu->ddCanIdLl == LddCanId)
    #endif
    {
      /* Set search flag to true */
      LblSearchValue = CANIF_TRUE;
      /* Set LddCpySize to zero to break the loop */
      LddCpySize = (PduIdType)CANIF_ZERO;
    }
    else
    {
      /* MISRA Rule    : 17.4
         Message       : Increment or decrement operation performed on pointer.
         Reason        : Increment operator used to achieve better throughput.
         Verification  : However, part of the code is verified manually and it
                         is not having any impact.
      */
      /* Increment Rx L-PDU structure */
      LpCpyRxLpdu++;
      /* Decrement the size */
      LddCpySize--;
    }
  }while (LddCpySize != (PduIdType)CANIF_ZERO);

  /* Check whether CAN-ID is found in database */
  if ((boolean)CANIF_FALSE == LblSearchValue)
  {
    /* Return the null pointer */
    LpCpyRxLpdu = NULL_PTR;
  }
  /* Return LpRxLpdu pointer */
  return (LpCpyRxLpdu);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_RxStatusUpdate                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used for the updating the RxStatus **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpRxLpdu                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_GaaRxLpduNotify           **
**                                                                            **
**                        Function(s) invoked:                                **
**                                        SchM_Enter_CanIf_RX_DATA_PROTECTION **
**                                        SchM_Exit_CanIf_RX_DATA_PROTECTION  **
**                                                                            **
*******************************************************************************/
#if ((STD_ON == CANIF_READRXPDU_NOTIFY_STATUS_API) || \
                                           (STD_ON == CANIF_READRXPDU_DATA_API))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CANIF_CODE) CanIf_RxStatusUpdate (
                        P2CONST(CanIf_RxLpdu, AUTOMATIC, CANIF_CONST) LpRxLpdu,
                        P2CONST(PduInfoType, AUTOMATIC, CANIF_CONST) PduInfoPtr)
{
  P2VAR(CanIf_RxLpduNotify, AUTOMATIC, CANIF_VAR) LpRxLpduNotify;
  VAR(PduIdType, CANIF_VAR) LddNotifyId;
  #if (STD_ON == CANIF_READRXPDU_DATA_API)
  VAR(uint8, CANIF_VAR) LucVar;
  #endif
  VAR(uint8, CANIF_VAR) CanDlc;
  CanDlc = (uint8)PduInfoPtr->SduLength;
  /* Get the notify structure id from RxLpdu structure */
  LddNotifyId = LpRxLpdu->ddRxNotifyId;
  /* Check the notification status mask */
  LpRxLpduNotify = &CanIf_GaaRxLpduNotify[LddNotifyId];
  /* update the RxNotifSts with DLC and notification status */
  LpRxLpduNotify->ucDlcOrNotify = (CanDlc | CANIF_NOTIFY_STATUS_MASK);
  /*CANIF_NOTIFY_STATUS_MASK = 0x80*/
  #if (STD_ON == CANIF_READRXPDU_DATA_API)
  /* Get the pointer to RxLpduData pointer from RxLpduNotify
     structure CANIF_DATA_STATUS_MASK - 0X80 */
  if ((LpRxLpdu->ucRxUserOrNotifSts & CANIF_RX_DATA_STATUS_MASK) != CANIF_ZERO)
  {
    /* Assigned length to local variable */
    LucVar = CanDlc;
    /* Disable relevant interrupts */
    SchM_Enter_CanIf_RX_DATA_PROTECTION();
    /* Run Loop to copy the data as per DLC */
    while ((uint8)CANIF_ZERO != LucVar)
    {
      /* decrement the value of LucVar */
      LucVar--;
      /* polyspace +1 MISRA-C3:18.1, RTE:OBAI,IDP [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
      LpRxLpduNotify->aaRxBufferData[LucVar] = PduInfoPtr->SduDataPtr[LucVar];
    }
    /* Enable relevant interrupts */
    SchM_Exit_CanIf_RX_DATA_PROTECTION();
  } /*if ( LpRxLpduData != NULL_PTR) */
  #endif
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_ReadRxCanId                                 **
**                                                                            **
** Service ID           : none                                                **
**                                                                            **
** Description          : This service provides the actual value of           **
**                        CAN identifier received                             **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : none                                                **
**                                                                            **
** Output Parameters    : Can_IdType *CanIdPtr                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized               **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        For post-build and pre-compile Implementation:      **
**                        CanIf_GddRxCanId                                    **
**                                                                            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                                                        f                   **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void,CANIF_CODE) CanIf_ReadRxCanId
    (P2VAR(Can_IdType, AUTOMATIC, CANIF_APPL_DATA) CanIdPtr)
{
  if(CanIdPtr != NULL_PTR)
  {
    /* Copy CAN message identifier value */
		/* polyspace +1 MISRA-C3:D4.14,18.1 [Not a defect:Justified] "Array index in range" */
    *CanIdPtr = CanIf_GddRxCanId;
  }
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
