/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE: Dcm_Cbk.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the definitions of callback functions      **
**              provided for lower layers of Dcm module                       **
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
** 2.3.17.0  01-Jan-2022   KaHyun   Kim    #33696                             **
**                                                                            **
** 2.3.15.0  10-Dec-2021   KaHyun   Kim    #33025                             **
**                                                                            **
** 2.3.13.0  06-Oct-2021   YoungJin Yun    #32325                             **
**                                                                            **
** 2.3.11.0  06-Jul-2021   YoungJin Yun    #30719                             **
**                                                                            **
** 2.3.10.0  16-Jun-2021   Soonkyu Park    #30315                             **
**                                                                            **
** 2.3.6.0   26-Mar-2021   EunKyung Kim    #29050                             **
**                                                                            **
** 2.3.2.0   04-Nov-2019   EunKyung Kim    #25404, #26432                     **
**                                                                            **
** 2.3.1.0   10-Oct-2020   YoungJin Yun    #26044                             **
**                                                                            **
** 1.0.10    02-09-2019    EunKyung Kim    #18790                             **
**                                                                            **
** 1.0.9     23-07-2019    Y.S     Jeon    #17648                             **
**                                                                            **
** 1.0.8     16-07-2019    Y.S     Jeon    #2212                              **
**                                                                            **
** 1.0.7     03-07-2019    Y.S     Jeon    #17276                             **
**                                                                            **
** 1.0.6     01-02-2017    Jing    Jung    #6972                              **
**                                                                            **
** 1.0.5     04-01-2017    Jing    Jung    #6174, #6483                       **
**                                                                            **
** 1.0.4     03-03-2016    Sungeol Baek    #4267, RTRT reflection             **
**                                                                            **
** 1.0.3     14-11-2015    Youngjin Yun    #3485, #3488, #3492                **
**                                                                            **
** 1.0.2     24-03-2015    Sungeol Baek    #2370                              **
**                                                                            **
** 1.0.1     26-02-2015    Sungeol Baek    #2163                              **
**                                                                            **
** 1.0.0     09-01-2013    Autron          Initial Version                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_Cbk.h"
#include "Rte_Dcm.h"
#include "PduR_Dcm.h"
#include "Dem.h"

#if(DCM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#include "SchM_Dcm.h"
#include "Dcm_Ram.h"
#include "Dcm_Dsl.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_DslInternal.h"
#include "Dcm_DspServices.h"

#include "ComM_Dcm.h"
#if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
#include "Dcm_DspResponseOnEvent.h"
#endif

#include "Dcm_Config.h"
#include "Dcm_Ram.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
static VAR(boolean,DCM_VAR) Dcm_ConcurrentTesterPresent;
static VAR(boolean,DCM_VAR) Dcm_TransparentTesterPresent;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"


#if(DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
static VAR(boolean,DCM_VAR) Dcm_SecondDeclinedRequest;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif

/* For PagedBuffer */
#if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
/* CAN : max 7 bytes, CAN FD: max 64 */
#define DCM_MAX_PAGED_SDU_LEN 63

#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
static VAR(Dcm_MsgLenType,DCM_VAR) Dcm_GulFilledSduLength;
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
static VAR(uint8,DCM_VAR) Dcm_GaaFilledPagedSdu[DCM_MAX_PAGED_SDU_LEN];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#endif

typedef enum
{
  DCM_REQBUF_ACCEPT = 0, 
  DCM_REQBUF_ACCEPT_PREEMPT_PROTOCOL,  
  DCM_REQBUF_ACCEPT_TRANSPARENT_TESTERPRESENT,   
  DCM_REQBUF_ACCEPT_CONCURRENT_TESTERPRESENT, 
  DCM_REQBUF_NOT_ACCEPTED_NRC21,
  DCM_REQBUF_NOT_ACCEPTED
}Dcm_BufferStatus;

/*******************************************************************************
**                      Function Definitions
*******************************************************************************/
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:10.4 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace:begin<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > configured memory access index */
/* polyspace:begin<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
/* polyspace:begin<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-begin CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */

#define DCM_START_SEC_CODE
#include "MemMap.h"

static FUNC(void, DCM_APPL_CODE) Dcm_CbkInternal_CopyTxData(
  BufReq_ReturnType *LddReturnValue,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) TxDataCntPtr,
  P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA) LddPduInfoPtr);

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dcm_StartOfReception                                **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : By this service the DCM is requested to provide a   **
**                        buffer for a transport layer on first frame or      **
**                        single frame reception.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-trant                                           **
**                                                                            **
** Input Parameters     : DcmRxPduId, LpPduInfoPtr, TpsduLength               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : RxBufferSizePtr                                     **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this API.  **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GblInitStatus,             **
**                        Dcm_GaaCommMode, Dcm_GddTpSduLength,                **
**                        Dcm_GaaProtocolConfig, Dcm_GaaReqLength,            **
**                        Dcm_GblNormalReq, Dcm_GblResOnPeriodicIdStatus,     **
**                        Dcm_TimerReqFlagStatus , Dcm_GaaPduIdTableConfig **
**                        Dcm_GaaBufferConfig , Dcm_GucPrtclPriority          **
**                        Function(s) invoked : (void)Det_ReportError,        **
**                        Dcm_GetProtocolIDIndex, SchM_Enter_Dcm_<name>       **
**                        SchM_Exit_Dcm_<name>                                **
**                                                                            **
*******************************************************************************/
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_START_SEC_CODE
#include "MemMap.h"
/* polyspace-begin MISRA-C3:15.5 [Justify with annotations:Unset] "No Impact of this rule violation" */
FUNC(BufReq_ReturnType, DCM_APPL_CODE) Dcm_StartOfReception
  (PduIdType DcmRxPduId, 
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr, 
  PduLengthType TpSduLength,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr)
{
  P2CONST(Dcm_ProtocolConfig, AUTOMATIC, DCM_APPL_CONST)LpProtocolConfig;
  P2CONST(Dcm_BufferConfig, AUTOMATIC, DCM_APPL_CONST)LpBufferConfig;
  /* uint32 LulBufferSize; */
  Dcm_ProtocolType LddProtocolId;
  BufReq_ReturnType LddReturnValue;
  uint8 LucProtocolPrio;
  uint8 LucPrtclStatusMask;
  uint8 LucProtocolIDIndex;
  /* uint8 LucNetworkId; */
  static uint16 LucTxConfirmationPduId;

  Dcm_BufferStatus LddBufferStatus = DCM_REQBUF_NOT_ACCEPTED;
  boolean LblIsFunctionalTesterPresent = DCM_FALSE;
  boolean LblAlreadyRunningRequest = DCM_FALSE;
  boolean LblOtherRequestIsOngoing = DCM_FALSE;

  PduIdType LucCount = DCM_ZERO;
  boolean LblAcceptRequest = DCM_FALSE;

  
  Dcm_TransparentTesterPresent = DCM_FALSE;
  Dcm_ConcurrentTesterPresent = DCM_FALSE;
  LddReturnValue = BUFREQ_E_NOT_OK;

  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  /* Check whether the module is Initialized */
  if (Dcm_GblInitStatus == DCM_UNINITIALISED)
  {
    DCM_REPORT_ERROR(DCM_START_OF_RECEPTION_SID, DCM_E_UNINIT);
    /* LddReturnValue = BUFREQ_E_NOT_OK; */
  }
  /* Check whether RxPduId is out of range */
  /* Check the message without data stream */
  else
  #endif /* (DCM_DEV_ERROR_DETECT == STD_ON) */
  
  if (/*(0U == TpSduLength) ||*/ (DcmRxPduId >= Dcm_Num_Of_PduidTableConfig))
  {
    DCM_REPORT_ERROR(DCM_START_OF_RECEPTION_SID, DCM_E_PARAM);
    /* LddReturnValue = BUFREQ_E_NOT_OK; */
  }
  /*Validate for NULL_PTR*/
  else if (RxBufferSizePtr == NULL_PTR)
  {
    DCM_REPORT_ERROR(DCM_START_OF_RECEPTION_SID, DCM_E_PARAM_POINTER);
    /* LddReturnValue = BUFREQ_E_NOT_OK; */
  }
  else if(Dcm_GaaPduIdTableConfig[DcmRxPduId].ucRxComChannelRef >= Dcm_No_Of_Comm_Channels)
  {
    DCM_REPORT_ERROR(DCM_START_OF_RECEPTION_SID, DCM_E_INTERFACE_BUFFER_OVERFLOW);
    /* LddReturnValue = BUFREQ_E_NOT_OK; */   
  }
  else
  {
    if((Dcm_GaaCommMode[Dcm_GaaPduIdTableConfig[DcmRxPduId].ucRxComChannelRef] != DCM_NO_COMMUNICATION) && (Dcm_GblReset != DCM_TRUE))
    {
      Dcm_GaaPduIdTableConfig[DcmRxPduId].ulRxCopiedLength = (uint32)DCM_ZERO;
      
      /* Initialize pointer to corresponding buffer Id structure */
      LpBufferConfig = Dcm_DsdInternal_GetBuffferConfig(DcmRxPduId);
      if (NULL_PTR == LpBufferConfig)
      {
        DCM_REPORT_ERROR(DCM_START_OF_RECEPTION_SID, DCM_E_PARAM_POINTER);
        /* LddReturnValue = BUFREQ_E_NOT_OK; */         
      }
      /* Check whether the request length is more than the Rx Buffer size */
      else if(TpSduLength > LpBufferConfig->ulBufferSize)
      {
        DCM_REPORT_ERROR(DCM_START_OF_RECEPTION_SID, DCM_E_INTERFACE_BUFFER_OVERFLOW);
        LddReturnValue = BUFREQ_E_OVFL;
      }
      else
      {
        /*Update the request length for this request*/
        Dcm_GddTpSduLength = TpSduLength;

        /* Get the protocol Id */
        LddProtocolId = Dcm_GaaPduIdTableConfig[DcmRxPduId].ddProtocolId;
        /* Get Protocol Index */
        LucProtocolIDIndex = Dcm_GetProtocolIDIndex(LddProtocolId);
        /* Get the Pointer to the corresponding protocol structure */
        LpProtocolConfig = NULL_PTR;
        if (LucProtocolIDIndex < Dcm_Num_Of_ProtocolConfig)
        {
          LpProtocolConfig = &Dcm_GaaProtocolConfig[LucProtocolIDIndex];
          LucProtocolPrio = LpProtocolConfig->ucProtocolPrio;
          /* Initialize the status mask */
          LucPrtclStatusMask = LpProtocolConfig->ucPrtclStatusMask;
        }

        #if(DCM_ECURESET_SERVICE == STD_ON)
        /* polyspace +13 MISRA-C3:2.1 [Justified:Low] "Not a defect" */
        /* polyspace +2 MISRA-C3:14.3 [Justified:Low] "Not a defect" */
        /* polyspace +1 MISRA-C3:14.4 [Justified:Low] "Not a defect" */

        #if 0 /* Not Support   */
        if(DCM_TRUE == Dcm_Forced_Ecu_Reset)
        {
          if((LpPduInfoPtr->SduDataPtr != NULL_PTR) &&
          (LpPduInfoPtr->SduDataPtr[0] == 0x11U) &&
          (LpPduInfoPtr->SduDataPtr[1U] == 0x81U) &&
          (LpPduInfoPtr->SduLength == 0x02))
          {
            (void)SchM_Switch_Dcm_DcmEcuReset(HARD);
            Dcm_GblReset = DCM_TRUE;
            Dcm_GblExecuteECUReset = DCM_TRUE;
            return(LddReturnValue);
          }
        }
        #endif
        #endif
    
        /* PDD Status is set in the StartOfReception and cleared in the TxConfirmation */
        /* 
         * [SWS_Dcm_00241] d As soon as a request message is received (after a call of
         * Dcm_TpRxIndication with parameter Result = E_OK (see [SWS_Dcm_00093]) and
         * until a call to Dcm_TpTxConfirmation (see [SWS_Dcm_00351]) for the associated
         * Tx-DcmPduId), the DSL submodule shall block the corresponding DcmPduId. During
         * the processing of this request, no other request of the same DcmDslConnection (e.g.
         * an enhanced session can be ended by a OBD session) can be received, until the cor-
         * responding response message is sent and the DcmPduId is released again (except for
         * concurrent TesterPresent requests). 
         */
        if((NULL_PTR != LpProtocolConfig) &&
           ((*(Dcm_GaaPduIdTableConfig[DcmRxPduId].pPduIdStatus) &
           (Dcm_GaaPduIdTableConfig[DcmRxPduId].ucPduIdStatusMask)) == DCM_ZERO))
        {
          if (
          (LpPduInfoPtr != NULL_PTR) &&
          (LpPduInfoPtr->SduDataPtr != NULL_PTR) &&
          (LpPduInfoPtr->SduDataPtr[0] == 0x3EU) &&
          (LpPduInfoPtr->SduDataPtr[1U] == 0x80U) &&
          (Dcm_GaaPduIdTableConfig[DcmRxPduId].ucRxAddrType == DCM_ADDR_FUNCTIONAL) &&
          (LpPduInfoPtr->SduLength == 0x02))
          {
            LblIsFunctionalTesterPresent = DCM_TRUE;
          }
            
          /* First request after power boot ? */
          if(Dcm_GblTheFirstRequest == DCM_FALSE) /* [flow tag 1] */
          {
            /* Dcm_GblNormalReq : Indication(1)  -> Confirmation (0)
             * ucReceiveStatus : StartOfReception -> Indication
             */
            /* polyspace +8 MISRA-C3:14.2 [Justified:Low] "Not a defect" */
            for(LucCount = (PduIdType )DCM_ZERO; LucCount < Dcm_Num_Of_PduidTableConfig; LucCount++)
            {
              if (LucCount != DcmRxPduId)
              {          
                if (DCM_RECEPTION_ONGOING == Dcm_GaaPduIdTableConfig[LucCount].ucReceiveStatus)          
                {
                  LblOtherRequestIsOngoing = DCM_TRUE;
                  LucCount = Dcm_Num_Of_PduidTableConfig;
                }
              }
            }   
            /* Dcm_GblNormalReq is set in the Indication and cleared in the TxConfirmation */
            /* Validate current request */
            if((Dcm_GblNormalReq == DCM_TRUE)
              #if((DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) && \
                (DCM_PROTOCOL_TRANSTYPE2 == STD_OFF))
              || (Dcm_GblResOnPeriodicIdStatus == DCM_TRUE)
              #endif
            )
            {
              LblAlreadyRunningRequest = DCM_TRUE;
            }
            
            /* Different DcmDslConnection */
            if(Dcm_GaaPduIdTableConfig[DcmRxPduId].usTxConfirmationPduId != LucTxConfirmationPduId) /* [flow tag 2] */
            {
              if(LblIsFunctionalTesterPresent == DCM_TRUE) /* [flow tag 3] */
              {
                /* << CONCURRENT TESTERPRESENT : different DcmDslConnection >>
                 * [SWS_Dcm_01145] 
                 * If the current session is a non-default session and a concurrent
                 * TesterPresent received on a different DcmDslConnection, this request will be ac-
                 * cepted with a BUFREQ_OK, but not further processed. E.g. it is not resetting the
                 * session timeout timer (S3Server) */
                if(CHECK_NONDEFAULT_SESSION(Dcm_GddCurrentSession)) /* [flow tag 4] */
                {
                  /* [SWS_Dcm_01146] [SWS_Dcm_01144]
                  but not further processed
                  it is not resetting the S3Server timer
                  */
                  LddBufferStatus = DCM_REQBUF_ACCEPT_TRANSPARENT_TESTERPRESENT;
                }
                /* else { ddBufferStatus = DCM_REQBUF_NOT_ACCEPTED; } */
              }
              else
              {
                /* A higher priority protocol Than the active one */
                if(LucProtocolPrio < Dcm_GucPrtclPriority) /* [flow tag 5] */
                {
                  /* < Preemption >
                   * [SWS_Dcm_00015] A protocol with higher priority is allowed to preempt the already
                   * running protocol.*/                 
                  LddBufferStatus = DCM_REQBUF_ACCEPT_PREEMPT_PROTOCOL;
                  LucTxConfirmationPduId = Dcm_GaaPduIdTableConfig[DcmRxPduId].usTxConfirmationPduId; 
                }
                else /* A Low-priority or same-priority request */
                {
                  /* in case the same protocol and different connection is in execution,
                   *  second request will not be processed. 
                   * Therefore, SWS_Dcm_00729 is satisfied in this code. 
                   *
                   * [SWS_Dcm_00729] 
                   * In case of multiple clients with different PduIDs which are re-
                   * questing the same protocol, as all the connections of the same protocol are having the
                   * same priority, a second request (with the different RxPduId) will not be processed. If the
                   * configuration parameter DcmDslDiagRespOnSecondDeclinedRequest is TRUE, a
                   * negative response with NRC 0x21 (BusyRepeatRequest) shall be issued for the second
                   * request. If the configuration parameter is FALSE, no response shall be issued.
                   */                
                  if(CHECK_DEFAULT_SESSION(Dcm_GddCurrentSession)) /* [flow tag 7] */
                  {
                    if ( /* [flow tag 6] */
                      ( DCM_TRUE == LblOtherRequestIsOngoing ) ||
                      ( DCM_TRUE == LblAlreadyRunningRequest ) ) 
                    {                         
                      /* [SWS_Dcm_00656] If the current session is the default session and a diagnostic
                       * request is in execution, for any new diagnostic request with same or lower priority protocol
                       * than active one, the Dcm shall act according [SWS_Dcm_00788], [SWS_Dcm_00789]
                       * and [SWS_Dcm_00790]. */
                      #if(DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
                      if(Dcm_PrtclTxBufStatus.ucProtclStatus == DCM_TRUE)
                      {
                        LddBufferStatus = DCM_REQBUF_NOT_ACCEPTED_NRC21;
                      }                      
                      #endif                    
                      /* else { ddBufferStatus = DCM_REQBUF_NOT_ACCEPTED; } */
                    }
                    else
                    {
                      /* [SWS_Dcm_00625] d A Low-priority or same-priority request can preempt a higher
                       * priority protocol if this higher priority protocol is in default session and no active re-
                       * quest is in execution phase. In this case the DSL submodule shall call all configured
                       * Xxx_StopProtocol() functions (see configuration parameter DcmDslCallbackDCMRe-
                       * questService). */    
                      if(
                        (Dcm_TimerReqFlagStatus.ucPrtclPreemptTimer == DCM_FALSE) &&
                        (Dcm_GaaProtclStatus[DCM_ZERO] == DCM_ZERO)
                      )
                      {
                        LddBufferStatus = DCM_REQBUF_ACCEPT_PREEMPT_PROTOCOL;
                        LucTxConfirmationPduId = Dcm_GaaPduIdTableConfig[DcmRxPduId].usTxConfirmationPduId;
                      }
                      /* else { ddBufferStatus = DCM_REQBUF_NOT_ACCEPTED; } */
                    }
                  }
                  else
                  {
                    /* [SWS_Dcm_00655] If the current session is a non-default session and
                     * a new diagnostic request with same or lower priority protocol than active one is detected,
                     * the dcm shall act according [SWS_Dcm_00788], [SWS_Dcm_00789] and [SWS_Dcm_00790]. */          
                    #if(DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
                    if(Dcm_PrtclTxBufStatus.ucProtclStatus == DCM_TRUE)
                    {
                      LddBufferStatus = DCM_REQBUF_NOT_ACCEPTED_NRC21;
                    }                    
                    #endif                    
                    /* else { ddBufferStatus = DCM_REQBUF_NOT_ACCEPTED; } */
                  }               
                }
              }
            }
            else /* the same DcmDslConnection */
            {
              if(LblAlreadyRunningRequest == DCM_TRUE) /* [flow tag 10] */
              {                
                /* Req proceed */
                if(LblIsFunctionalTesterPresent == DCM_TRUE) /* [flow tag 12] */
                {

                  /* Restart S3Server timer */
                  /* For [SWS_Dcm_00112] [SWS_Dcm_00113] */
                  LddBufferStatus = DCM_REQBUF_ACCEPT_CONCURRENT_TESTERPRESENT;
                }
                /* else { ddBufferStatus = DCM_REQBUF_NOT_ACCEPTED; } */
              }
              else
              {
                if (DCM_TRUE == LblOtherRequestIsOngoing)
                {
                  /* << TESTERPRESENT : same DcmDslConnection >>
                   * 
                   * [SWS_Dcm_00557] When processing a diagnostic request, the Dcm module shall
                   * reject (Dcm_StartOfReception shall return BUFREQ_E_NOT_OK) any new diagnostic 
                   * request with the same DcmDslConnection until the current diagnostic request
                   * processing is over. Concurrent TesterPresent requests will be accepted with
                   * a BUFREQ_OK, but not further processed, as the running diagnostic request already
                   * resets the session timeout timer (S3Server).  */
                  if(LblIsFunctionalTesterPresent == DCM_TRUE) /* [flow tag 11] */
                  { 
                    LddBufferStatus = DCM_REQBUF_ACCEPT_TRANSPARENT_TESTERPRESENT;
                  }
                  /* else { ddBufferStatus = DCM_REQBUF_NOT_ACCEPTED; } */
                }
                else             
                {
                  /* [ Exception ]
                   * If Functional TesterPresent does not concurrent with other request, 
                   * the server must wait for P2CAN_SERVER_MAX+deltaCAN time. 
                   * However, some tester do not keep minimum time because of sending TesterPresent periodically. 
                   * To prevent malfunctions, process this in the same way as the concurrent TesterPresent 
                   * 
                   * No Request -> TesterPresent-> Service Request(NOT TP) ( within 10ms )
                   */
                  if(LblIsFunctionalTesterPresent == DCM_TRUE)
                  {
                    /* Note : Concurrent TesterPresent < Reset S3 > */
                    LddBufferStatus = DCM_REQBUF_ACCEPT_CONCURRENT_TESTERPRESENT;
                  }
                  else
                  {
                    /* normal request */
                    LddBufferStatus = DCM_REQBUF_ACCEPT;
                    /*Same: LucTxConfirmationPduId = Dcm_GaaPduIdTableConfig[DcmRxPduId].usTxConfirmationPduId; */
                  }
                }
              }
            }
          }
          else
          {
            Dcm_GblTheFirstRequest = DCM_FALSE;

            /* [ Exception ]
             * If Functional TesterPresent does not concurrent with other request, 
             * the server must wait for P2CAN_SERVER_MAX+deltaCAN time. 
             * However, some tester do not keep minimum time because of sending TesterPresent periodically. 
             * To prevent malfunctions, process this in the same way as SWS_Dcm_00557
             *
             * No Request -> TesterPresent-> Service Request(NOT TP) ( within 10ms )
             */
            if(LblIsFunctionalTesterPresent == DCM_TRUE)
            {
              /* Note : Transparent TesterPresent < Do nothing> */
              LddBufferStatus = DCM_REQBUF_ACCEPT_TRANSPARENT_TESTERPRESENT;
            }
            else
            {
              /* The first Req proceed */
              LddBufferStatus = DCM_REQBUF_ACCEPT;
            }
            LucTxConfirmationPduId = Dcm_GaaPduIdTableConfig[DcmRxPduId].usTxConfirmationPduId;            
          }         
 
          switch(LddBufferStatus)
          {
            case DCM_REQBUF_ACCEPT:
              /* No break */
            case DCM_REQBUF_ACCEPT_PREEMPT_PROTOCOL:
              /* pProtocolStatus:  Dcm_StartOfReception< Accepted Request> : 1 -> Dcm_TpTxConfirmation : 0 */
              if (DCM_FALSE == (*(LpProtocolConfig->pProtocolStatus) & LucPrtclStatusMask))
              {
                LblAcceptRequest = DCM_TRUE;
                LddReturnValue = BUFREQ_OK;
              }
              else
              {
                LddReturnValue = BUFREQ_E_NOT_OK;
              }
              break;
              
            case DCM_REQBUF_ACCEPT_CONCURRENT_TESTERPRESENT:
              Dcm_ConcurrentTesterPresent = DCM_TRUE;
              LddReturnValue = BUFREQ_OK;              
              break;

              /* Concurrent TesterPresent request */
            case DCM_REQBUF_ACCEPT_TRANSPARENT_TESTERPRESENT:
              /* but not further processed it is not resetting the S3Server timer */           
              Dcm_TransparentTesterPresent = DCM_TRUE;
              LddReturnValue = BUFREQ_OK;              
              break;
            #if(DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
            case DCM_REQBUF_NOT_ACCEPTED_NRC21:                 
              Dcm_SecondDeclinedRequest = DCM_TRUE;
              LddReturnValue = BUFREQ_OK;              
              break;
            #endif
            case DCM_REQBUF_NOT_ACCEPTED:
              /* No break; */
              
            default:
              LddReturnValue = BUFREQ_E_NOT_OK;
              break;
          }
          if (DCM_TRUE == LblAcceptRequest)
          {
            /* Set the status of the requested RxPduId's protocol */          
            SchM_Enter_Dcm_ProtclProtection();
            /* This is cleared in Dcm_TpTxConfirmation */
            *(LpProtocolConfig->pProtocolStatus) |= LucPrtclStatusMask;
            SchM_Exit_Dcm_ProtclProtection();            
            
            Dcm_GaaPduIdTableConfig[DcmRxPduId].ucReceiveStatus = DCM_RECEPTION_ONGOING;

            /* Init the received data length */
            SchM_Enter_Dcm_RxLengthProtection();
            LucProtocolIDIndex = Dcm_GetProtocolIDIndex(LddProtocolId);
            if (LucProtocolIDIndex < Dcm_Num_Of_ProtocolConfig)
            {
              Dcm_GaaReqLength[LucProtocolIDIndex] = 0;
            }
            SchM_Exit_Dcm_RxLengthProtection();
          }
          if (BUFREQ_OK == LddReturnValue)
          {
            SchM_Enter_Dcm_RxPduIdProtection();
            /* This is cleared in Dcm_TpTxConfirmation */
            *(Dcm_GaaPduIdTableConfig[DcmRxPduId].pPduIdStatus) |= 
                Dcm_GaaPduIdTableConfig[DcmRxPduId].ucPduIdStatusMask;              
            SchM_Exit_Dcm_RxPduIdProtection();

            /* polyspace +9 MISRA-C3:2.1 [Justified:Low] "Not a defect" */
            /* polyspace +8 MISRA-C3:14.3 [Justified:Low] "Not a defect" */
            if ( (1U == sizeof(PduLengthType)) && (LpBufferConfig->ulBufferSize > 0xFFU) )
            {
              *RxBufferSizePtr = 0xFFU;
            }
            else /* if PduLengthType is 4 bytes? */
            {
               *RxBufferSizePtr = (PduLengthType)LpBufferConfig->ulBufferSize;
            }
                
            /* Meta data - address store */
            if((Dcm_GaaPduIdTableConfig[DcmRxPduId].ucMetaDataLength > 0) &&
               (DCM_FALSE == Dcm_ConcurrentTesterPresent)&&
               (DCM_FALSE == Dcm_TransparentTesterPresent))
            {
              /* +-----------------+----------------+----------------+
               * |  Request        |            Meta data            |    
               * +-----------------+----------------+----------------+
               * |  payload data   | source address | target address | 
               * +-----------------+----------------+----------------+                 
               * |  SdudataLenghth |       2 byte   |      2byte     | 
               * +-----------------+----------------+----------------+
               */
              if ( 
                (LpPduInfoPtr != NULL_PTR) && 
                (LpPduInfoPtr->SduDataPtr != NULL_PTR)
              )
              {
                Dcm_GaaMetaDataAdd[2] = LpPduInfoPtr->SduDataPtr[LpPduInfoPtr->SduLength];
                Dcm_GaaMetaDataAdd[3] = LpPduInfoPtr->SduDataPtr[LpPduInfoPtr->SduLength+1];
                Dcm_GaaMetaDataAdd[0] = LpPduInfoPtr->SduDataPtr[LpPduInfoPtr->SduLength+2];
                Dcm_GaaMetaDataAdd[1] = LpPduInfoPtr->SduDataPtr[LpPduInfoPtr->SduLength+3];
              }
            }            
          }              
          /* polyspace-end MISRA-C3:16.1 [Justify with annotations:Unset] "No Impact of this rule violation" */
          /* polyspace-end MISRA-C3:16.3 [Justify with annotations:Unset] "No Impact of this rule violation" */
        }
        else
        {
          /* LddReturnValue = BUFREQ_E_NOT_OK; */
        }
      }
    } /* end if((Dcm_GaaCommMode[LucNetworkId] != DCM_NO_COMMUNICATION) &&  (Dcm_GblReset != DCM_TRUE)) */
    
    /* [SWS_Dcm_01145] 
     * 
     * If the current session is a non-default session and a concurrent
     * TesterPresent received on a different DcmDslConnection, this request will be ac-
     * cepted with a BUFREQ_OK, but not further processed. E.g. it is not resetting the
     * session timeout timer (S3Server) */
     
    if(DCM_FALSE==Dcm_TransparentTesterPresent)
    {
        SchM_Enter_Dcm_TimerProtection();
        /* Stop the S3ServerTimer if the timer is started and running */
        if((LddReturnValue == BUFREQ_OK) &&
           (Dcm_TimerReqFlagStatus.ucS3Timer == DCM_TRUE))
        {
          /* Stop the timer */
          DCM_STOP_TIMER(DCM_S3SERVER_TIMER);
          Dcm_TimerReqFlagStatus.ucS3Timer = DCM_FALSE;
        }
        SchM_Exit_Dcm_TimerProtection();
    }

  } /* End of Block comment 1 */
  /* Return the parameter */
  return(LddReturnValue);
}
/* polyspace-end MISRA-C3:15.5 [Justify with annotations:Unset] "No Impact of this rule violation" */

/*******************************************************************************
** Function Name        : Dcm_CopyRxData                                      **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : By this service the DCM is requested to provide a   **
**                        buffer for a transport layer on first frame or      **
**                        single frame reception.                             **
**                                                                            **
** Sync/Async          : Synchronous                                          **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DcmRxPduId                                          **
**                                                                            **
** InOut Parameters     : PduInfoPtr                                          **
**                                                                            **
** Output Parameters    : RxBufferSizePtr                                     **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this API.  **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_GblInitStatus, Dcm_GaaCommMode,                 **
**                        Dcm_GaaPduIdTableConfig, Dcm_GaaBufferConfig,       **
**                        Function(s) invoked : (void)Det_ReportError         **
**                                                                            **
*******************************************************************************/
FUNC(BufReq_ReturnType, DCM_APPL_CODE) Dcm_CopyRxData
  (PduIdType DcmRxPduId,
  P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_CONST) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr)
{
  P2VAR(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_DATA)LpPduIdTable;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpBufferArea;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpSduptr;
  P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_CONST) LpInfoPtr;

  uint32 LulBufferSize;
  uint32 LulNoOfBytes;
  uint8 LucPduIdStatusMask;
  uint8 LucNetworkId;
  BufReq_ReturnType LddReturnValue;

  /* Initialize return value to BUFREQ_OK */
  LddReturnValue = BUFREQ_OK;
  LpInfoPtr = PduInfoPtr;
  LulBufferSize = 0u;
  LpBufferArea = NULL_PTR; 
  /* Check if the pre compile option DCM_DEV_ERROR_DETECT is enabled */
  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  /* Check whether the module is Initialized */
  if (Dcm_GblInitStatus == DCM_UNINITIALISED)
  {
    /* Report to DET */
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID, DCM_COPY_RXDATA_SID,
      DCM_E_UNINIT);
    /* Set the return value to BUFREQ_E_NOT_OK */
    LddReturnValue = BUFREQ_E_NOT_OK;
  }
  /* Validate pointer */
  else if((LpInfoPtr == NULL_PTR) || (RxBufferSizePtr == NULL_PTR))
  {
    /* Report to DET */
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID, DCM_COPY_RXDATA_SID,
      DCM_E_PARAM_POINTER);
    /* Set the return value to BUFREQ_E_NOT_OK */
    LddReturnValue = BUFREQ_E_NOT_OK;
  }
  /* Check whether RxPduId is out of range */
  else if (DcmRxPduId >= Dcm_Num_Of_PduidTableConfig)
  {
    /* Report to DET */
    (void)Det_ReportError(DCM_MODULE_ID, DCM_INSTANCE_ID, DCM_COPY_RXDATA_SID,
      DCM_E_PARAM);
    /* Set the return value to BUFREQ_E_NOT_OK */
    LddReturnValue = BUFREQ_E_NOT_OK;
  }
  else  
  #endif /* (DCM_DEV_ERROR_DETECT == STD_ON) */
  if(0U == LpInfoPtr->SduLength)
  {
    /* Report to DET */
    DCM_REPORT_ERROR(DCM_COPY_RXDATA_SID, DCM_E_PARAM);
    /* Set the return value to BUFREQ_E_NOT_OK */
    LddReturnValue = BUFREQ_E_NOT_OK;
  }
  else
  {
    if (DCM_TRUE == Dcm_TransparentTesterPresent)
    {
      *RxBufferSizePtr = 0U; 
      /* LddReturnValue = BUFREQ_OK; */
    }
    else
    {
      LpSduptr = PduInfoPtr->SduDataPtr;
      /* Initialize pointer to PduId table corresponding to the RxPduId */
      LpPduIdTable = &Dcm_GaaPduIdTableConfig[DcmRxPduId];
      LucNetworkId = LpPduIdTable->ucRxComChannelRef;

      if(LucNetworkId < Dcm_No_Of_Comm_Channels)
      {
        /* Check if communication mode is other than DCM_NO_COMMUNICATION */
        if((Dcm_GaaCommMode[LucNetworkId] != DCM_NO_COMMUNICATION) && (Dcm_GblReset != DCM_TRUE))
        {

          /* Initialize the status mask */
          LucPduIdStatusMask = LpPduIdTable->ucPduIdStatusMask;
    
          if((*(LpPduIdTable->pPduIdStatus) & LucPduIdStatusMask) == LucPduIdStatusMask)
          {
            if (DCM_TRUE == Dcm_ConcurrentTesterPresent)
            {      
              Dcm_GaaTesterPresentReqBuff[0U] = LpInfoPtr->SduDataPtr[0U];
              Dcm_GaaTesterPresentReqBuff[1U] = LpInfoPtr->SduDataPtr[1U];              
              *RxBufferSizePtr = 0U;
              /* LulBufferSize = DCM_BUFSZ_TESTERPRESENT;
                LpBufferArea = &Dcm_GaaTesterPresentReqBuff[0U]; */
              
              Dcm_ConcurrentTesterPresent = DCM_FALSE;
              /* LddReturnValue = BUFREQ_OK; */
            }
            else
            {
              if(LpPduIdTable->ucRxBufferId < Dcm_Num_Of_Buffer_Config)
              {
                LulBufferSize = Dcm_GaaBufferConfig[LpPduIdTable->ucRxBufferId].ulBufferSize;
                LpBufferArea = 
                  &Dcm_GaaBufferConfig[LpPduIdTable->ucRxBufferId].pBufferArea[LpPduIdTable->ulRxCopiedLength];      
              }
            
              if ((LulBufferSize > 0U ) && (LpBufferArea != NULL_PTR))
              {   
                uint8 LucProtocolIDIndex;
              
                SchM_Enter_Dcm_RxLengthProtection();
                LucProtocolIDIndex = Dcm_GetProtocolIDIndex(LpPduIdTable->ddProtocolId);
                /* length is initialized by Dcm_StartOfReception */
                if (LucProtocolIDIndex < Dcm_Num_Of_ProtocolConfig)
                {
                  Dcm_GaaReqLength[LucProtocolIDIndex] += LpInfoPtr->SduLength;
                }
                /* Exit DC */
                SchM_Exit_Dcm_RxLengthProtection();

                
                /*Get the length of data to be copied to the Dcm buffer*/
                LulNoOfBytes = LpInfoPtr->SduLength;
                
                LpPduIdTable->ulRxCopiedLength = LpPduIdTable->ulRxCopiedLength + LulNoOfBytes;
                /*Loop until data from the buffer is copied to the Dcm buffer*/
                do
                {
                  /*Decrement the buffer size to send the remaining buffer size*/
                  LulBufferSize--;
                  LulNoOfBytes--;
      
                  /*Copy the data and increment to next location*/
                  /* polyspace<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
                  LpBufferArea[LulNoOfBytes] = LpSduptr[LulNoOfBytes];
                }while(LulNoOfBytes != DCM_ZERO);
      
                /* FIXME: typecasting problem : PduLengthType
                 * possible truncation at implicit conversion to type "unsigned char */
                /* Update the Length of the available buffer in Length parameter */              
                *RxBufferSizePtr = (PduLengthType)LulBufferSize;
              }
              else
              {
                /* Set the return value to BUFREQ_E_NOT_OK */
                LddReturnValue = BUFREQ_E_NOT_OK;
              }
            }
          }
        } /* end if((Dcm_GaaCommMode[LucNetworkId] != DCM_NO_COMMUNICATION)
           && (Dcm_GblReset != DCM_TRUE)) */
        else
        {
          /* Set the return value to BUFREQ_E_NOT_OK */
          LddReturnValue = BUFREQ_E_NOT_OK;
        }
      }
      else
      {
        DCM_REPORT_ERROR(DCM_COPY_RXDATA_SID, DCM_E_PARAM);    
        LddReturnValue = BUFREQ_E_NOT_OK;
      }
    }
  } /* End of Block comment 1 */
  
  /* Return the parameter */
  return(LddReturnValue);
}

/*******************************************************************************
** Function Name        : Dcm_TpRxIndication                                  **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This service indicates the DCM module whether the   **
**                        reception of diagnostic request is finished with    **
**                        or without errors.                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DcmRxPduId, Result                                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : This function is called by PduR                     **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_APPL_CODE) Dcm_TpRxIndication(PduIdType DcmRxPduId,
  NotifResultType Result)
{
  P2CONST(Dcm_ProtocolConfig, AUTOMATIC, DCM_APPL_CONST)
    LpProtocolConfig;
  P2CONST(Dcm_ProtocolConfig, AUTOMATIC, DCM_APPL_CONST)
    LpOldProtocolConfig;
  /* #if(DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON) */
  P2CONST(Dcm_BufferConfig, AUTOMATIC, DCM_APPL_CONST)LpBufferConfig;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)LpRxPduIdData;
  /* #endif */
  Dcm_ProtocolType LddProtocolId;
  Dcm_ProtocolType LddOldProtocolId;
  uint8 LucPduIdStatusMask;
  uint8 LucProtocolIDIndex;
  uint8 LucCount;

  /* Check if the pre compile option DCM_DEV_ERROR_DETECT is enabled */
  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  boolean LblDetErrFlag;

  /* Initialize the error flag to FALSE */
  LblDetErrFlag = DCM_FALSE;
  /* Check whether the module is Initialized */
  if (Dcm_GblInitStatus == DCM_UNINITIALISED)
  {
    DCM_REPORT_ERROR(DCM_RX_INDICATION_SID, DCM_E_UNINIT);
    /* Set the Error Flag to TRUE */
    LblDetErrFlag = DCM_TRUE;
  }
 
  if (DcmRxPduId >= Dcm_Num_Of_PduidTableConfig)
  {
    DCM_REPORT_ERROR(DCM_RX_INDICATION_SID, DCM_E_PARAM);
    /* Set the Error flag to TRUE */
    LblDetErrFlag = DCM_TRUE;
  }
  /* Check whether error flag is FALSE */
  if(LblDetErrFlag == DCM_FALSE)
  #endif /* (DCM_DEV_ERROR_DETECT == STD_ON) */
  {

    if (DCM_TRUE == Dcm_TransparentTesterPresent)
    {
      /*Not resetting the S3 server Timer */
    
      /* unlock function pdu id */
      SchM_Enter_Dcm_RxPduIdProtection();
      *(Dcm_GaaPduIdTableConfig[DcmRxPduId].pPduIdStatus) &= 
        (uint8)(~(Dcm_GaaPduIdTableConfig[DcmRxPduId].ucPduIdStatusMask));
      SchM_Exit_Dcm_RxPduIdProtection();

      Dcm_TransparentTesterPresent = DCM_FALSE;      
    }
    else
    {    
      /* Initialize Dcm_GulNumOfBytes which holds multiframe request length */
      Dcm_GulNumOfBytes = DCM_ZERO;

      /* Initialize the status mask */
      LucPduIdStatusMask = Dcm_GaaPduIdTableConfig[DcmRxPduId].ucPduIdStatusMask;

      /* Get the protocol Id of the corresponding RxPduId */
      LddProtocolId = Dcm_GaaPduIdTableConfig[DcmRxPduId].ddProtocolId;

      /* Get Protocol Index */
      LucProtocolIDIndex = Dcm_GetProtocolIDIndex(LddProtocolId);
      /* Get the Pointer to the corresponding protocol structure */
      LpProtocolConfig = NULL_PTR;
      if (LucProtocolIDIndex < Dcm_Num_Of_ProtocolConfig)
      {
        LpProtocolConfig = &Dcm_GaaProtocolConfig[LucProtocolIDIndex];
      }

      /* Enter DC */
      SchM_Enter_Dcm_RxPduIdProtection();

      /* protocol with parameter DcmRxPduId is active */
      if ((NULL_PTR != LpProtocolConfig) &&
          (Result == NTFRSLT_OK) &&
          ((*(Dcm_GaaPduIdTableConfig[DcmRxPduId].pPduIdStatus) & LucPduIdStatusMask) ==
          LucPduIdStatusMask))
      {
        SchM_Exit_Dcm_RxPduIdProtection();
    
        /*  Send NRC in the current task, but not next task */
        /* #if(DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON) */  
        /* Get the pointer to the corresponding Buffer Structure */
        LpBufferConfig = &Dcm_GaaBufferConfig[Dcm_GaaPduIdTableConfig[DcmRxPduId].ucRxBufferId];
       
        /* Get the pointer to LpRxPduIdData  */
        LpRxPduIdData = LpBufferConfig->pBufferArea;
        /* #endif */

        /* NOTE: Dcm_GucPrtclPriority = 0 in Dcm_Init() */
        
        /* Check if the incoming request has protocol of higher priority than the
           running protocol priority */
        if (LpProtocolConfig->ucProtocolPrio < Dcm_GucPrtclPriority)
        {
          /* Get the protocol Id of the corresponding RxPduId */
          LddOldProtocolId = Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId].ddProtocolId;
          
          /* Get old Protocol Index */
          LucProtocolIDIndex = Dcm_GetProtocolIDIndex(LddOldProtocolId);
          /* Get the Pointer to the corresponding old protocol structure */
          if (LucProtocolIDIndex < Dcm_Num_Of_ProtocolConfig)
          {
            LpOldProtocolConfig = &Dcm_GaaProtocolConfig[LucProtocolIDIndex];
          
            /* Enter the DC */
            SchM_Enter_Dcm_ProtclProtection();
            /* Clear the protocol status */
            *(LpOldProtocolConfig->pProtocolStatus) &= (uint8)(~(LpOldProtocolConfig->ucPrtclStatusMask));
            /* Exit the DC */
            SchM_Exit_Dcm_ProtclProtection();
          }

          /* Dcm_GddRxPduId is old PduId (request is processing currently) */
          if (Dcm_GddRxPduId < Dcm_Num_Of_PduidTableConfig)
          {
            if(Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId].ucReceiveStatus == DCM_RECEPTION_ONGOING)
            {
              #if(DCM_PDUR_CANCEL_RECIEVE == STD_ON)
              (void)PduR_DcmCancelReceive(Dcm_GddRxPduId);
              Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId].ucReceiveStatus = DCM_RECEPTION_CANCELLED;
              #endif
            }
          }

          /* 
          * When a running diagnostic request is preempted by a higher prior request (of another protocol) 
          * and protocol preempt timer is started, a third request(that has higer priority than the second request)
          * shall preempt the second request and restart the protocol preempt timer of the preempting protocol(here the third protocol).
          */
          if((Dcm_TimerReqFlagStatus.ucPrtclPreemptTimer == DCM_TRUE) &&
            (Dcm_GaaTimer[DCM_PROTOCOL_PREEMPT_TIMER] != DCM_ZERO) &&
            (Dcm_PrtclTxBufStatus.ucProtclStatus == DCM_FALSE)
          )
          {
            /* Clear the current RxPduId status */
            SchM_Enter_Dcm_RxPduIdProtection();
            *(Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId].pPduIdStatus) &= 
              (uint8)(~(Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId].ucPduIdStatusMask));
            SchM_Exit_Dcm_RxPduIdProtection();

            Dcm_GddRxPduId = DcmRxPduId;

            Dcm_TimerReqFlagStatus.ucPrtclPreemptTimer = DCM_FALSE;

            /* Update the response array to send "BusyRepeatRequest" */
            Dcm_GaaResponseBuf[DCM_ZERO] = DCM_NEGATIVE_RESPONSE_SID;
            /* Update with the service Id */
            Dcm_GaaResponseBuf[DCM_ONE] = LpRxPduIdData[DCM_ZERO];
            /* Update the NRC value */
            Dcm_GaaResponseBuf[DCM_TWO] = DCM_E_BUSYREPEATREQUEST;
            /* Set the negative response flag to DCM_TRUE */
            Dcm_TxRespStatus.ucNegResp = DCM_TRUE;
          }
          else
          {
            /* When there is request processing */
            if((Dcm_GblNormalReq == DCM_TRUE)
                #if((DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) && \
                  (DCM_PROTOCOL_TRANSTYPE2 == STD_OFF))
                || (Dcm_GblResOnPeriodicIdStatus == DCM_TRUE)
                #endif
                #if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
                || (Dcm_GucResOnEventStatus == DCM_ROEONGOING)
                #endif
              )
            {
              /* Clear the current RxPduId status */
              SchM_Enter_Dcm_RxPduIdProtection();
              *(Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId].pPduIdStatus) &= 
                (uint8)(~(Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId].ucPduIdStatusMask));
              SchM_Exit_Dcm_RxPduIdProtection();
              
              /* (Cancel processing) Forward the stop protocol request to the DSD layer */
              (void)Dcm_DsdIndication(Dcm_GddRxPduId, DCM_TRUE/*LblStopProtocol */, DCM_FALSE/*Per*/, DCM_FALSE/*ROE*/);
              Dcm_GddRxPduId = DcmRxPduId;
              /*
              * Clear the bit flag for the response received for the previous
              * request
              */
              Dcm_TxRespStatus.ucRespPending = DCM_FALSE;
              /*
              * Clear the bit flag for previous response if pre-empted before
              * getting the confirmation
              */
              Dcm_TxRespStatus.ucNormResponse = DCM_FALSE;
              /* Set the Normal, Periodic, ROE request global variables to Idle */
              Dcm_GblNormalReq = DCM_FALSE;
    
              #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
              Dcm_PrtclTxBufStatus.ucPeriodicIdStatus = DCM_FALSE;
              Dcm_GblResOnPeriodicIdStatus = DCM_FALSE;
              #endif
    
              #if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
              Dcm_GucResOnEventStatus = DCM_IDLE;
              #endif
    
              /* DCM_E_BUSYREPEATREQUEST :
               * Test may send the request again after one received DCM_E_BUSYREPEATREQUEST */
               
              /*  Send NRC in the current task, but not next task */
              /* sg.baek 150223 -refer to Bug #2203 in redmine */
              /* #if(DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON) */  
              Dcm_PrtclTxBufStatus.ucProtclStatus = DCM_FALSE;
              /* Update the response array to send "BusyRepeatRequest" */
              Dcm_GaaResponseBuf[DCM_ZERO] = DCM_NEGATIVE_RESPONSE_SID;
              /* Update with the service Id */
              Dcm_GaaResponseBuf[DCM_ONE] = LpRxPduIdData[DCM_ZERO];
              /* Update the NRC value */
              Dcm_GaaResponseBuf[DCM_TWO] = DCM_E_BUSYREPEATREQUEST;
              /* Set the negative response flag to DCM_TRUE */
              Dcm_TxRespStatus.ucNegResp = DCM_TRUE;
              /* #endif */
            }
            /* When there is no request processing */
            else
            {
              Dcm_StatusType LddStatusValue = DCM_E_OK;
              
              /* Clear all the DSP flags */
              Dcm_DspStartProtocol();
    
              Dcm_GaaPduIdTableConfig[DcmRxPduId].ucReceiveStatus = DCM_RECEPTION_COMPLETED;
    
              /* Load the Global variable for RxpduId with the current RxPduId */
              Dcm_GddRxPduId = DcmRxPduId;
              /* Clear the security timer */
              #if(DCM_DSP_SECURITY_SERVICE == STD_ON)
              Dcm_DspClearSecurityTimer();
              #endif
    
              for  (LucCount  =  DCM_ZERO; LucCount < Dcm_Total_Num_Of_Callback_Request;  LucCount++)
              {
                if(NULL_PTR != Dcm_GaaCbkReqServices[LucCount].pStopProtocolFun)
                {
                  (void) Dcm_GaaCbkReqServices[LucCount].pStopProtocolFun(Dcm_GddProtocolId);
                }
              }
    
              /* Set bit flag for protocol status to FALSE */
              Dcm_PrtclTxBufStatus.ucProtclStatus = DCM_FALSE;
    
              LucCount  =  DCM_ZERO;
    
              while((LucCount < Dcm_Total_Num_Of_Callback_Request)&&
                    (LddStatusValue != DCM_E_PROTOCOL_NOT_ALLOWED))
              {
                if(NULL_PTR != Dcm_GaaCbkReqServices[LucCount].pStartProtocolFun)
                {
                  LddStatusValue = Dcm_GaaCbkReqServices[LucCount].pStartProtocolFun(
                    Dcm_GaaPduIdTableConfig[DcmRxPduId].ddProtocolId);
                }
                LucCount++;
              }
    
              /* sg.baek 150223 - Task #2163 in redmine */
              if((LddStatusValue == DCM_E_PROTOCOL_NOT_ALLOWED) || (LddStatusValue == E_NOT_OK))
              {
                #if(DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
                  #if(DCM_DEV_ERROR_DETECT == STD_ON)
                  Dcm_DslTxIncorrectCondition(DCM_RX_INDICATION_SID);
                  #else
                  Dcm_DslTxIncorrectCondition();
                  #endif
                #else
                /* Update the local variable to DCM_TRUE for clearing the status and
                to start the S3 server Timer */
    
                /* Dcm_GblNormalReq is already FALSE. */
                Dcm_DslStatusReset();
                #endif
              }
              else
              {
                Dcm_GblNormalReq = DCM_TRUE;
                Dcm_GblReceiveRquest = DCM_TRUE;
              }  
            }
          }
        }
        /* lower priority than the running protocol priority */
        #if(DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
        else if(Dcm_SecondDeclinedRequest)
        {
          Std_ReturnType LddReturnValue;
          PduInfoType LddPduInfo;
          
          /*  Transmit Negative response DCM_E_BUSYREPEATREQUEST */
          Dcm_GaaPduIdTableConfig[DcmRxPduId].ucReceiveStatus = DCM_RECEPTION_COMPLETED;

          /* Update the negative response service Id in the response buffer */
          Dcm_GaaResponseBuf[DCM_ZERO] = DCM_NEGATIVE_RESPONSE_SID;
          /* Update the service Id in the response buffer */
          Dcm_GaaResponseBuf[DCM_ONE] = LpRxPduIdData[DCM_ZERO];
          /* Update the NRC in the response buffer */
          Dcm_GaaResponseBuf[DCM_TWO] = DCM_E_BUSYREPEATREQUEST;
          /*
           * Update the global bit flag indicating negative response to
           * TRUE
           */
          Dcm_TxRespStatus.ucNegResp = DCM_TRUE;

          Dcm_GddSecDeclTxPduId = Dcm_GaaPduIdTableConfig[DcmRxPduId].ddTxPduId;
          Dcm_GddSecDeclConfTxPduId =
            (PduIdType)Dcm_GaaPduIdTableConfig[DcmRxPduId].usTxConfirmationPduId;

          /* Update the PduInfoPtr with negative response array */
          LddPduInfo.SduDataPtr = &Dcm_GaaResponseBuf[DCM_ZERO];
          /* Update length as three */
          LddPduInfo.SduLength =  DCM_THREE;
          /* Invoke PduR_DcmTransmit */
          LddReturnValue =  Dcm_PduRTransmit(Dcm_GddSecDeclTxPduId, &LddPduInfo);

          if(LddReturnValue == E_OK)
          {
            Dcm_GblSecDeclRequest = DCM_TRUE;
          }

          /* Clear the RxPduId status  of the corresponding RxpduId */
          *(Dcm_GaaPduIdTableConfig[DcmRxPduId].pPduIdStatus) &= 
            (uint8)(~(Dcm_GaaPduIdTableConfig[DcmRxPduId].ucPduIdStatusMask));
            
          Dcm_SecondDeclinedRequest = DCM_FALSE;
        }
        #endif
        else
        {
          Dcm_StatusType dcmStatus = DCM_E_OK;
          /* first request
           * same connection, no running, no tp -> normal request (same protocol)
           * lower or same, non-default, no running, same protocol (same protocol)
           * lower or same, default, no running (same protocol?)
           * higher protocol (different protocol) 
           */
           
          /* Update the return value */
          if 
          ( (Dcm_GaaPduIdTableConfig[DcmRxPduId].ucRxAddrType == DCM_ADDR_FUNCTIONAL) &&
            (Dcm_GaaTesterPresentReqBuff[0U] == 0x3EU) &&
            (Dcm_GaaTesterPresentReqBuff[1U] == 0x80U)
          )
          {
            #if 0        
            DCM_STOP_TIMER(DCM_S3SERVER_TIMER);

            SchM_Enter_Dcm_TimerProtection();
            Dcm_TimerReqFlagStatus.ucS3Timer = DCM_FALSE;
            SchM_Exit_Dcm_TimerProtection();
            #else

            /* [ES95486-XX] S3Server
             * Initial Start:
             *
             * The completion of the transmission of a DiagnosticSessionControl 
             * positive response message for a transition from the default session to 
             * a non-default session, in case a response message is required.
             * Successful completion of the requested action of the */
            if(CHECK_NONDEFAULT_SESSION(Dcm_GddCurrentSession))  
            {
              /* [SWS_Dcm_00112]  
               * When the PduR module calls Dcm_TpRxIndication() 
               * with parameter Result=E_OK (see SWS_Dcm_00093) and if the request is a 
               * 'TesterPresent' command with 'suppressPosRspMsgIndicationBit' set to TRUE (SID 
               * equal to 0x3E, subfunction equal to 0x80), the DSL submodule shall reset the 
               * session timeout timer (S3Server).
              */

              /* Start the s3 timer value */
              DCM_START_TIMER(DCM_S3SERVER_TIMER, (Dcm_GstCurrentTimingValue.Timer_S3Server));
              SchM_Enter_Dcm_TimerProtection();
              /* Need to verify : just resetting ucS3Timer, not starting ???*/
              Dcm_TimerReqFlagStatus.ucS3Timer = DCM_TRUE;
              SchM_Exit_Dcm_TimerProtection();           
            }
            #endif

            /* unlock function pdu id */
            SchM_Enter_Dcm_RxPduIdProtection();
            *(Dcm_GaaPduIdTableConfig[DcmRxPduId].pPduIdStatus) &= 
              (uint8)(~(Dcm_GaaPduIdTableConfig[DcmRxPduId].ucPduIdStatusMask));
            SchM_Exit_Dcm_RxPduIdProtection();

            /* No need to send response code and buffer shall be cleared */
            Dcm_GaaTesterPresentReqBuff[0U] = 0U;
            Dcm_GaaTesterPresentReqBuff[1U] = 0U;
          }
          else if(Dcm_GaaPduIdTableConfig[DcmRxPduId].ucReceiveStatus == DCM_RECEPTION_ONGOING)
          {
            Dcm_GddRxPduId = DcmRxPduId;
            Dcm_GaaPduIdTableConfig[DcmRxPduId].ucReceiveStatus = DCM_RECEPTION_COMPLETED;

            /* FIXME : What means? (LddProtocolId != (Dcm_GddProtocolId) 
             * what is initial value of Dcm_GddProtocolId ? */
            
            /* Check whether the request is coming for the first time */
            if ((Dcm_PrtclTxBufStatus.ucProtclStatus == DCM_FALSE) || 
                (LddProtocolId != (Dcm_GddProtocolId)))
            {
              /* Clear all the DSP flags */
              Dcm_DspStartProtocol();
              /* Clear the security timer */
              #if(DCM_DSP_SECURITY_SERVICE == STD_ON)
                Dcm_DspClearSecurityTimer();
              #endif
              /*  Invoke  DSP  internal  function  to  stop  the  current
              protocol and start the incoming protocol*/
              if(Dcm_PrtclTxBufStatus.ucProtclStatus != DCM_FALSE)
              {
                for  (LucCount  =  DCM_ZERO;
                   LucCount < Dcm_Total_Num_Of_Callback_Request;  LucCount++)
                {
                  if(NULL_PTR != Dcm_GaaCbkReqServices[LucCount].pStopProtocolFun)
                  {
                    (void) Dcm_GaaCbkReqServices[LucCount].pStopProtocolFun(Dcm_GddProtocolId);
                  }
                }
              }

              for  (LucCount  =  DCM_ZERO;
                 LucCount < Dcm_Total_Num_Of_Callback_Request;  LucCount++)
              {
                if(NULL_PTR != Dcm_GaaCbkReqServices[LucCount].pStartProtocolFun)
                {
                  dcmStatus = Dcm_GaaCbkReqServices[LucCount].pStartProtocolFun(
                           Dcm_GaaPduIdTableConfig[DcmRxPduId].ddProtocolId);
                }
          
                if(dcmStatus == DCM_E_PROTOCOL_NOT_ALLOWED)
                {
                  break;
                }
              }
            }
            else
            {  /* [Dcm163] */
              if(CHECK_DEFAULT_SESSION(Dcm_GddCurrentSession))
              {
                (void)ComM_DCM_ActiveDiagnostic
                  ((NetworkHandleType)Dcm_GulChannelIdentifier);
              }
            }
            /* sg.baek 150223 - Task #2163 in redmine */
            if((dcmStatus == DCM_E_PROTOCOL_NOT_ALLOWED) || (dcmStatus == E_NOT_OK))
            {
              #if(DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
                #if(DCM_DEV_ERROR_DETECT == STD_ON)
                Dcm_DslTxIncorrectCondition(DCM_RX_INDICATION_SID);
                #else
                Dcm_DslTxIncorrectCondition();
                #endif
              #else
              /* Update the local variable to DCM_TRUE for clearing the status and
              to start the S3 server Timer */

              /* Dcm_GblNormalReq is already FALSE. */
              Dcm_DslStatusReset();
              #endif  
            }
            else
            {
              /* Set to true to process a new request in Dcm_MainFunction */
              Dcm_GblNormalReq = DCM_TRUE;
              Dcm_GblReceiveRquest = DCM_TRUE;
            }
          }
          else
          {

          }
        }
      }
      else if((NULL_PTR != LpProtocolConfig) &&
              (Result != NTFRSLT_OK) && 
              (Dcm_GaaPduIdTableConfig[DcmRxPduId].ucReceiveStatus != DCM_RECEPTION_COMPLETED))
      {
        SchM_Exit_Dcm_RxPduIdProtection();

        Dcm_GaaPduIdTableConfig[DcmRxPduId].ucReceiveStatus = DCM_RECEPTION_COMPLETED;

        /* [SWS_Dcm_00141]
         *Indicates an error during the reception of a multi-frame request message.(Dcm_TpRxIndication: indication of an error)
         */
        
        /*Restart the S3 server Timer */
        if(CHECK_NONDEFAULT_SESSION(Dcm_GddCurrentSession))
        {
          SchM_Enter_Dcm_TimerProtection();
          DCM_START_TIMER(DCM_S3SERVER_TIMER, Dcm_GstCurrentTimingValue.Timer_S3Server);
          Dcm_TimerReqFlagStatus.ucS3Timer = DCM_TRUE;
          SchM_Exit_Dcm_TimerProtection();   
        }
            
        /* Clear the RxPduId status */
        SchM_Enter_Dcm_RxPduIdProtection();
        *(Dcm_GaaPduIdTableConfig[DcmRxPduId].pPduIdStatus) &= 
          (uint8)(~(Dcm_GaaPduIdTableConfig[DcmRxPduId].ucPduIdStatusMask));
        SchM_Exit_Dcm_RxPduIdProtection();

        /* Clear the status of the requested RxPduId's protocol */
        SchM_Enter_Dcm_ProtclProtection();
        *(LpProtocolConfig->pProtocolStatus) &= (uint8)(~(LpProtocolConfig->ucPrtclStatusMask));
        SchM_Exit_Dcm_ProtclProtection();
      }
      else
      {
        SchM_Exit_Dcm_RxPduIdProtection();
      }
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_CbkInternal_CopyTxData                          **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : This service checks the DCM module to provide the   **
**                        buffer for the response transmission.               **
**                                                                            **
** Sync/Async          : Synchronous                                          **
**                                                                            **
** Re-entrancy          : None                                                **
**                                                                            **
** InOut Parameters     : PduInfoPtr                                          **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GblInitStatus              **
**                                           Dcm_GaaCommMode,                 **
**                        Dcm_TxRespStatus, Dcm_GddTxResponseLen,             **
**                        Dcm_GpMsgContext, Dcm_GstCurrentTimingValue,        **
**                        Dcm_TimerReqFlagStatus , Dcm_PrtclTxBufStatus       **
**                        Dcm_GaaPduIdTableConfig ,Dcm_GucPeriodicRxPduId     **
**                        Dcm_GblResOnPeriodicIdStatus , Dcm_GblSecDeclRequest**
**                        Dcm_GaaResponseBuf , Dcm_GaaDslPeriodicData         **
**                        Function(s) invoked : (void)Det_ReportError,        **
**                        Dcm_DsdConfirmation                                 **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_APPL_CODE) Dcm_CbkInternal_CopyTxData(
  BufReq_ReturnType *LddReturnValue,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) TxDataCntPtr,
  P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA) LddPduInfoPtr)
{   
  #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /*
  * Check whether paged transmission is STD_ON and buffer
  * request is for first page
  */

  /* Local variables for PagedTrans */
  Dcm_MsgLenType LulSduLengthToFill;
  uint8 LucPagedSduIsFull;
  
  if(Dcm_TxRespStatus.ucFirstPageTrans == DCM_TRUE)
  {
    /* The Filled paged length is loaded to a temporary variable */
    Dcm_MsgLenType LulBufferSize = Dcm_GddTxResponseLen;
    /* The total response length is loaded to global variable */
    Dcm_GddTxResponseLen = Dcm_GstMsgContext.resDataLen;
    Dcm_GstMsgContext.resDataLen = LulBufferSize;

    Dcm_GulFilledSduLength = DCM_ZERO;
    
    Dcm_TxRespStatus.ucFirstPageTrans = DCM_FALSE;
  }
  /* Check if Paged transmission is false */
  else if(Dcm_TxRespStatus.ucPagedTrans == DCM_FALSE)
  #endif
  {
    Dcm_GddTxResponseLen = Dcm_GstMsgContext.resDataLen;
  }
  #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  else
  {
    /* To avoid QAC */
  }
  #endif
  /* check whether normal response or paged response is not ready */
  if (((Dcm_TxRespStatus.ucNormResponse == DCM_FALSE) &&
     (Dcm_TxRespStatus.ucRespPending == DCM_TRUE) &&
     (Dcm_TxRespStatus.ucNegResp == DCM_FALSE))
  #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
    || 
    ((Dcm_TxRespStatus.ucPagedTrans == DCM_TRUE) &&
     (Dcm_TxRespStatus.ucNormResponse == DCM_FALSE) &&
     (Dcm_TxRespStatus.ucDslPagedTrans == DCM_FALSE) &&
     (Dcm_TxRespStatus.ucNegResp == DCM_FALSE))
  #endif
  )
  {
    /* Update the return value */
    *LddReturnValue = BUFREQ_E_BUSY;
  }
  /* Check whether the bit flag for negative response in set */
  else if(Dcm_TxRespStatus.ucNegResp == DCM_TRUE)
  {
    Dcm_DspInternal_MemCopy(LddPduInfoPtr->SduDataPtr, Dcm_GaaResponseBuf, LddPduInfoPtr->SduLength);
  
    /*
     * Update the TxDataCntPtr of with the available response
     * length
     */
    *TxDataCntPtr = 0U;
    
    /* Update the return value */
    *LddReturnValue = BUFREQ_OK;
  }
  else
  {
    /* To avoid QAC warning */
  }
  #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /*
  * Check if paged response in true and the previous page is
  * transmitted and total response length is not DCM_ZERO
  */
  if ((Dcm_GstMsgContext.resDataLen == DCM_ZERO) &&
    ((Dcm_TxRespStatus.ucPagedTrans == DCM_TRUE) &&
     (Dcm_TxRespStatus.ucNormResponse == DCM_FALSE) &&
     (Dcm_TxRespStatus.ucDslPagedTrans == DCM_FALSE) &&
     (Dcm_TxRespStatus.ucNegResp == DCM_FALSE)) &&
     (Dcm_GddTxResponseLen != DCM_ZERO))
  {
    /*
     * Invoke the internal confirmation function to confirm
     * transmission of previous page
     */
    Dcm_DsdConfirmation(NTFRSLT_OK);
    DCM_START_TIMER(DCM_P2SERVERMAX_TIMER,
    (Dcm_GstCurrentTimingValue.Timer_P2ServerMax - Dcm_GstCurrentTimingValue.Timer_P2ServerAdjust));
    SchM_Enter_Dcm_TimerProtection();
    Dcm_TimerReqFlagStatus.ucP2MaxTimer = DCM_TRUE;
    SchM_Exit_Dcm_TimerProtection();
    /*
     * Update the bit flag for the paged
     * transmitted from DSL layer to FALSE
     */
    Dcm_TxRespStatus.ucDslPagedTrans = DCM_FALSE;
  }
  /* Check whether response transmission is failed  */
  else if(Dcm_TxRespStatus.ucRespFailed == DCM_TRUE)
  {    
    /* TODO: clear all flags or ucRespFailed */
    Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_FALSE;

    /* Update the variable for response status to ZERO */
    /* Dcm_TxRespStatus.ucMaskByte = DCM_ZERO; */
    Dcm_TxRespStatus.ucNormResponse = DCM_FALSE;    
    Dcm_TxRespStatus.ucNegResp = DCM_FALSE;

    /* Set the global bit flag indicating response failed to FALSE */
    Dcm_TxRespStatus.ucRespFailed = DCM_FALSE;    
    
    Dcm_TxRespStatus.ucRespPending = DCM_FALSE;
    Dcm_TxRespStatus.ucFirstPageTrans = DCM_FALSE;
    Dcm_TxRespStatus.ucPagedTrans = DCM_FALSE;
    Dcm_TxRespStatus.ucFailedInd = DCM_FALSE;
    Dcm_TxRespStatus.ucDslPagedTrans = DCM_FALSE;

    Dcm_GblNormalReq = DCM_FALSE;
    
    /* Add this code #6174 by Jin 170104 */
    Dcm_DslStatusReset();
  }
  else
  #endif
  {
    if((Dcm_TxRespStatus.ucNegResp == DCM_FALSE) && (Dcm_TxRespStatus.ucNormResponse == DCM_TRUE))
    {
      /*
       * Check if the requested length is equal to ZERO and total
       * response length is not equal ZERO
       */
      if((LddPduInfoPtr->SduLength == 0U) && (Dcm_GddTxResponseLen != 0U))
      {
        /* Update the length with the global variable for available response length */
	    /* polyspace +1 DEFECT:CONSTANT_OBJECT_WRITE [Justified:Low] "Not a defect" */
        LddPduInfoPtr->SduLength = (uint8)Dcm_GddTxResponseLen;
      }
      /*
       * Check if the requested length is less than or equal to
       * remaining response bytes to be transmitted
       */
      if(LddPduInfoPtr->SduLength <= Dcm_GddTxResponseLen)
      {
        #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
        LucPagedSduIsFull = DCM_FALSE;
        *LddReturnValue = BUFREQ_E_BUSY;
        
        if(Dcm_TxRespStatus.ucPagedTrans == DCM_TRUE)
        {
          if(LddPduInfoPtr->SduLength > Dcm_GulFilledSduLength)
          {
            LulSduLengthToFill = LddPduInfoPtr->SduLength - Dcm_GulFilledSduLength;

            /* Fill the PagedResData */
            if(LulSduLengthToFill > Dcm_GstMsgContext.resDataLen)
            {
              /* Copy from resData to PagedResData */
              Dcm_DspInternal_MemCopy(&Dcm_GaaFilledPagedSdu[Dcm_GulFilledSduLength], Dcm_GstMsgContext.resData, Dcm_GstMsgContext.resDataLen);
              /* Update PagedDataLen */
              Dcm_GulFilledSduLength += Dcm_GstMsgContext.resDataLen;
              /* Update resData */
              Dcm_GstMsgContext.resData = &Dcm_GstMsgContext.resData[Dcm_GstMsgContext.resDataLen];
              /* Update resDataLen */
              Dcm_GstMsgContext.resDataLen = DCM_ZERO;
            }
            else
            {
              /* Copy from resData to PagedResData */
              Dcm_DspInternal_MemCopy(&Dcm_GaaFilledPagedSdu[Dcm_GulFilledSduLength], Dcm_GstMsgContext.resData, LulSduLengthToFill);
              /* Update PagedDataLen */
              Dcm_GulFilledSduLength += LulSduLengthToFill;
              /* Update resData */
              Dcm_GstMsgContext.resData = &Dcm_GstMsgContext.resData[LulSduLengthToFill];
              /* Update resDataLen */
              Dcm_GstMsgContext.resDataLen -= LulSduLengthToFill;
              /* Update Paged Transmit Flag */
              LucPagedSduIsFull = DCM_TRUE;
            }
          }
          else /* (LddPduInfoPtr->SduLength <= Dcm_GulFilledSduLength) */
          {
            LucPagedSduIsFull = DCM_TRUE;
          }

          /* Copy paged data */
          if(LucPagedSduIsFull == DCM_TRUE)
          {
            Dcm_DspInternal_MemCopy(LddPduInfoPtr->SduDataPtr, Dcm_GaaFilledPagedSdu, LddPduInfoPtr->SduLength);

            Dcm_GulFilledSduLength -= LddPduInfoPtr->SduLength;
            
            /* Decrement the total response length by the size of the buffer provided  */
            Dcm_GddTxResponseLen = (Dcm_GddTxResponseLen - (LddPduInfoPtr->SduLength));
            /* FIXME: PduLengthType is variable range*/
            *TxDataCntPtr = (PduLengthType)Dcm_GddTxResponseLen;
            
            /* Update the return value */
            *LddReturnValue = BUFREQ_OK;
          }
          else /* (LucPagedSduIsFull != DCM_TRUE) */
          {
            /* Do Nothing */
          }
          
          /* Check if the response length is ZERO */
          /* IG issue protection code : BSG */
          if((Dcm_GstMsgContext.resDataLen == 0U) && 
             (Dcm_GddTxResponseLen != 0U))
          {
            /* Update the bit flag for the page transmitted from DSL layer to FALSE */
            Dcm_TxRespStatus.ucDslPagedTrans = DCM_FALSE;
            Dcm_TxRespStatus.ucNormResponse = DCM_FALSE;
          }
          else
          {
            /* Update the flag for buffer provided to TRUE */
            Dcm_PrtclTxBufStatus.ucBufferProvided = DCM_TRUE;
          }
        }
        else /* (Dcm_TxRespStatus.ucPagedTrans != DCM_TRUE) */
        #endif
        {
          /* Copy no paged data */
          Dcm_DspInternal_MemCopy(LddPduInfoPtr->SduDataPtr, Dcm_GstMsgContext.resData, LddPduInfoPtr->SduLength);          
          
          /* Check if the requested length is greater than the filled page length */
          if(LddPduInfoPtr->SduLength > Dcm_GstMsgContext.resDataLen)
          {
            /* Update the TxDataCntPtr of with the available response length */
            *TxDataCntPtr = 0U;
            /* Update the available response length to ZERO */
            Dcm_GstMsgContext.resDataLen = 0U;
          }
          else
          {
            Dcm_GstMsgContext.resData = &Dcm_GstMsgContext.resData[LddPduInfoPtr->SduLength];
            /* Decrement the number of bytes transmitted in the current request */
            Dcm_GstMsgContext.resDataLen -= LddPduInfoPtr->SduLength;
          }
      
          /* Decrement the total response length by the size of the buffer provided  */
          Dcm_GddTxResponseLen = (Dcm_GddTxResponseLen - (LddPduInfoPtr->SduLength));
          /* FIXME: PduLengthType is variable range*/
          *TxDataCntPtr = (PduLengthType)Dcm_GddTxResponseLen;
          
          /* Update the return value */
          *LddReturnValue = BUFREQ_OK;

          /* Update the flag for buffer provided to TRUE */
          Dcm_PrtclTxBufStatus.ucBufferProvided = DCM_TRUE;
        }
      } /* if(LddPduInfoPtr->SduLength > Dcm_GddTxResponseLen) */
      else
      {
        /* Update the flag for buffer provided to TRUE */
        Dcm_PrtclTxBufStatus.ucBufferProvided = DCM_TRUE;
      }
      /* Check whether the total response length is ZERO */
      if(Dcm_GddTxResponseLen == 0U)
      {
        Dcm_TxRespStatus.ucDslPagedTrans = DCM_FALSE;
        /* Update the bit flag for the page transmission layer to FALSE */
        Dcm_TxRespStatus.ucPagedTrans = DCM_FALSE;
        /* Update the flag for buffer provided to TRUE */
        Dcm_PrtclTxBufStatus.ucBufferProvided = DCM_TRUE;
      }/*if(Dcm_TxRespStatus.ucNegResp ==
        DCM_FALSE) */
    }/* end of else part of response not ready and failed transmission */
  }/* end of else part of response not ready and failed transmission */
  
}

/*******************************************************************************
** Function Name        : Dcm_CopyTxData                                      **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : This service request the DCM module to provide the  **
**                        buffer for the response transmission.               **
**                                                                            **
** Sync/Async          : Synchronous                                          **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DcmTxPduId, RetryInfoPtr                            **
**                                                                            **
** InOut Parameters     : PduInfoPtr                                          **
**                                                                            **
** Output Parameters    : TxDataCntPtr -Remaining Tx data after completion    **
**                                      of this call.                         **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GblInitStatus              **
**                        Dcm_GaaCommMode,                                    **
**                        Dcm_TxRespStatus, Dcm_GddTxResponseLen,             **
**                        Dcm_GpMsgContext, Dcm_GstCurrentTimingValue,        **
**                        Dcm_TimerReqFlagStatus , Dcm_PrtclTxBufStatus       **
**                        Dcm_GaaPduIdTableConfig ,Dcm_GucPeriodicRxPduId     **
**                        Dcm_GblResOnPeriodicIdStatus , Dcm_GblSecDeclRequest**
**                        Dcm_GaaResponseBuf , Dcm_GaaDslPeriodicData         **
**                        Function(s) invoked : (void)Det_ReportError,        **
**                        Dcm_DsdConfirmation                                 **
**                                                                            **
*******************************************************************************/
FUNC(BufReq_ReturnType, DCM_APPL_CODE) Dcm_CopyTxData(
  PduIdType DcmTxPduId,
  P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_CONST) PduInfoPtr,
  P2VAR(RetryInfoType, AUTOMATIC, DCM_APPL_DATA) RetryInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) TxDataCntPtr) /* == availableDataPtr[AR 4.2.2] */
{
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST)LpPduIdTable;
  #if((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
  (DCM_PROTOCOL_TRANSTYPE2 == STD_ON))
  P2CONST(Dcm_DslRoeTrans, AUTOMATIC, DCM_APPL_CONST)LpRoeTxId;
  #endif
  P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA) LddPduInfoPtr;
  /* P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpRespBuffer; */
  BufReq_ReturnType LddReturnValue = BUFREQ_E_NOT_OK;
  /* uint32 LulNoOfBytes; */
  uint8 LucPduIdStatusMask;
  #if((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
  (DCM_PROTOCOL_TRANSTYPE2 == STD_ON))
  boolean LblROEType2Res;
  #endif

  #if((DCM_PROTOCOL_TRANSTYPE2 == STD_ON) && \
      (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON))
  boolean LblNormalResp;
  #endif
  uint8 LucNetworkId;

  /* Initialize the return value */
  /* polyspace +2 MISRA-C3:11.8 [Justified:Low] "Not a defect" */
  /* polyspace<MISRA-C:11.5:Not a defect:Justify with annotations> DCM standard. */
  /* polyspace-begin CERT-C:EXP05-C [Justified:Low] "This is Autosar Dcm Specifcation standard. Can not fix" */
  LddPduInfoPtr = (P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA))PduInfoPtr;
  /* polyspace-end CERT-C:EXP05-C [Justified:Low] "This is Autosar Dcm Specifcation standard. Can not fix" */

  /* Check if the pre compile option DCM_DEV_ERROR_DETECT is enabled */
  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  /* Check whether the module is Initialized */
  if (Dcm_GblInitStatus == DCM_UNINITIALISED)
  {
    /* Report to DET */
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID, DCM_COPY_TXDATA_SID, DCM_E_UNINIT);
  }
  else if ((LddPduInfoPtr == NULL_PTR) || (TxDataCntPtr == NULL_PTR))
  {
    /* Report to DET */
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID, DCM_COPY_TXDATA_SID, DCM_E_PARAM_POINTER);
  }
  else
  #endif /* (DCM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if ((DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) && (DCM_PROTOCOL_TRANSTYPE2 == STD_ON))
    LblNormalResp = DCM_FALSE;

    if((Dcm_PrtclTxBufStatus.ucPeriodicIdStatus == DCM_TRUE) &&
      (Dcm_GaaPduIdTableConfig[Dcm_GucPeriodicRxPduId].pPeriodicTxId != NULL_PTR))
    {
      if(Dcm_GddDcmTxConfPduId == DcmTxPduId)
      {
        LblNormalResp = DCM_TRUE;
      }
      else
      {
        LddReturnValue = Dcm_DslCopyPeriodicTxData(DcmTxPduId, LddPduInfoPtr, TxDataCntPtr);
      }
    }
    #endif
    #if ((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && (DCM_PROTOCOL_TRANSTYPE2 == STD_ON))

    LblROEType2Res = DCM_FALSE;
    if(Dcm_GucResOnEventStatus == DCM_ROEONGOING)
    {
      LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GpRoeMsgContext->dcmRxPduId];
      LpRoeTxId = LpPduIdTable->pRoeTxId;

      if(LpRoeTxId->usRoeTxConfirmPduId == DcmTxPduId)
      {
        LddReturnValue = Dcm_DslCopyROETxData(LddPduInfoPtr, TxDataCntPtr);
        LblROEType2Res = DCM_TRUE;
      }
    }
    #endif

    /* FIXME: duplicated 'if statement' */
    #if ((DCM_PROTOCOL_TRANSTYPE2 == STD_ON) && (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON))
    if(((LblNormalResp == DCM_TRUE)  &&
         (Dcm_PrtclTxBufStatus.ucPeriodicIdStatus == DCM_TRUE))
      || ((LblNormalResp == DCM_FALSE)  &&
         (Dcm_GblResOnPeriodicIdStatus == DCM_FALSE)))
    #endif
    #if((DCM_PROTOCOL_TRANSTYPE2 == STD_ON) && (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON))
    if(LblROEType2Res == DCM_FALSE)
    #endif
    {
      #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
      if(Dcm_GblResOnPeriodicIdStatus == DCM_TRUE)
      {
        LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GucPeriodicRxPduId];
      }
      else
      #endif
      {
        /* Initialize the pointer to the PduId table */
        LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
      }
      /* polyspace<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
      LucNetworkId = LpPduIdTable->ucRxComChannelRef;

      if(LucNetworkId < Dcm_No_Of_Comm_Channels)
      {
        if(Dcm_GaaCommMode[LucNetworkId] == DCM_FULL_COMMUNICATION)
        {
          #if(DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
          if ((Dcm_GddSecDeclTxPduId == DcmTxPduId) && 
              (Dcm_GblSecDeclRequest == DCM_TRUE) &&
              (Dcm_TxRespStatus.ucNegResp == DCM_TRUE))
          {
            Dcm_DspInternal_MemCopy(LddPduInfoPtr->SduDataPtr, Dcm_GaaResponseBuf, LddPduInfoPtr->SduLength);
            /* Update the return value */
            LddReturnValue = BUFREQ_OK;
  
            *TxDataCntPtr = DCM_ZERO;
          }
          else
          #endif
          {
            /* Initialize the status mask */
            LucPduIdStatusMask = LpPduIdTable->ucPduIdStatusMask;
            /*
             * Check whether the input parameter TxPduId is valid and
             *  communication mode is not in DCM_NO_COMMUNICATION mode
             */
            if((Dcm_GddDcmTxConfPduId == DcmTxPduId) &&
              ((*(LpPduIdTable->pPduIdStatus) & LucPduIdStatusMask) == LucPduIdStatusMask))
            {
              Dcm_CbkInternal_CopyTxData(&LddReturnValue, TxDataCntPtr, LddPduInfoPtr);
              /* Note : busy */
              /* polyspace<MISRA-C:13.7:Not a defect:Justify with annotations> polyspace bug */
              if(LddReturnValue == BUFREQ_E_NOT_OK)
              {
                DCM_REPORT_ERROR(DCM_COPY_TXDATA_SID, DCM_E_INTERFACE_RETURN_VALUE);
                /* IG issue protection code : BSG */
                Dcm_PrtclTxBufStatus.ucCopyTxRejected = DCM_TRUE;  
              }
            }
            else /* IG issue protection code : BSG */
            {
              DCM_REPORT_ERROR(DCM_COPY_TXDATA_SID, DCM_E_PARAM);            
              Dcm_PrtclTxBufStatus.ucCopyTxRejected = DCM_TRUE;    
            }
          }
        }
        else
        {
          Dcm_PrtclTxBufStatus.ucCopyTxRejected = DCM_TRUE;
        }
      }
      else
      {
        DCM_REPORT_ERROR(DCM_COPY_TXDATA_SID, DCM_E_PARAM);      
      }
    }
  }

  DCM_UNUSED_PTR(RetryInfoPtr);
  
  /* Return the parameter */
  return(LddReturnValue);
}

/*******************************************************************************
** Function Name        : Dcm_DslCopyPeriodicTxData                           **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : This service request the DCM module to provide the  **
**                        buffer for the response transmission.               **
**                                                                            **
** Sync/Async          : Synchronous                                          **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DcmTxPduId, RetryInfoPtr                            **
**                                                                            **
** InOut Parameters     : PduInfoPtr                                          **
**                                                                            **
** Output Parameters    : TxDataCntPtr                                        **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GaaPduIdTableConfig,       **
**                        Dcm_GucPeriodicRxPduId , Dcm_GaaDslPeriodicData     **
**                        Dcm_PrtclTxBufStatus                             **
**                        Function(s) Invoked:                                **
**                        SchM_Enter_Dcm_ProtclProtection,                    **
**                        SchM_Exit_Dcm_ProtclProtection                      **
**                                                                            **
*******************************************************************************/
#if ((DCM_PROTOCOL_TRANSTYPE2 == STD_ON) && \
    (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON))
FUNC(BufReq_ReturnType, DCM_APPL_CODE)Dcm_DslCopyPeriodicTxData(
  PduIdType DcmTxPduId,
  P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) TxDataCntPtr)
{

  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST)LpPduIdTable;
  P2VAR(Dcm_DslPeriodicTxId, AUTOMATIC, DCM_APPL_DATA) LpPerTxPduIdTable;
  P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA) LddPduInfoPtr;
  BufReq_ReturnType LddReturnValue;
  uint32 LusDataLen;
  uint32 LusNoOfBytes;
  uint8 LucMaxNumTxPduid;
  uint8 LucIndex;
  uint8 LucPduIdStatusMask;
  uint8 LucPerPduIdStatus;
  uint8 LucBufferIndex;
  boolean LblPeriodicStatus;
  uint8 LucNetworkId;

  LddPduInfoPtr = (P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA))PduInfoPtr;
  LucBufferIndex = DCM_ZERO;

  LddReturnValue = BUFREQ_E_NOT_OK;
  /*
   * Check if the requested length is equal to ZERO and total response
   * length is not equal ZERO
  */
  LblPeriodicStatus = DCM_FALSE;
  LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GucPeriodicRxPduId];
  LucNetworkId = LpPduIdTable->ucRxComChannelRef;

  if(Dcm_GaaCommMode[LucNetworkId] == DCM_FULL_COMMUNICATION)
  {
    LpPerTxPduIdTable = LpPduIdTable->pPeriodicTxId;
    LucMaxNumTxPduid =
    Dcm_GaaPduIdTableConfig[Dcm_GucPeriodicRxPduId].ucNoofPeriodicCon;

    for (LucIndex = DCM_ZERO;LucIndex < LucMaxNumTxPduid; LucIndex++)
    {
      LucPduIdStatusMask = LpPerTxPduIdTable->ucPerPduIdStatusMask;
      SchM_Enter_Dcm_ProtclProtection();
      LucPerPduIdStatus = *(LpPerTxPduIdTable->pPerPduIdStatus);
      SchM_Exit_Dcm_ProtclProtection();
      if( (DcmTxPduId == LpPerTxPduIdTable->usPerTxConfmPduId)&&
        (( LucPerPduIdStatus & LucPduIdStatusMask) == LucPduIdStatusMask))
      {
        LblPeriodicStatus = DCM_TRUE;
        /* MISRA Rule        : 13.6
          Message            : Control variable, LucIndex,
                               modified in body of loop
          Reason             : Once the search element found, control
                               exiting from the for loop to terminate
                               next iteration.
          Verification       : However, part of the code
                               is verified manually and
                               it is not having any impact.
        */
        LucIndex = LucMaxNumTxPduid;
        SchM_Enter_Dcm_ProtclProtection();
        LucBufferIndex = LpPerTxPduIdTable->ucPeriBufferIndex;
        SchM_Exit_Dcm_ProtclProtection();
      }
      else
      {
        /* MISRA Rule        : 17.4
          Message            : Increment or decrement operation
                               performed on pointer
          Reason             : Increment operator not used
                               to achieve better throughput.
          Verification       : However, part of the code
                               is verified manually and
                               it is not having any impact.
        */
        LpPerTxPduIdTable++;
      }
    }

    if(LblPeriodicStatus == DCM_TRUE)
    {
      if(LddPduInfoPtr->SduLength == DCM_ZERO)
      {
        /*
         * Update the length with the global variable for available
         * response length
       */
       /* FIXME: typecasting problem : PduLengthType
        *  possible truncation at implicit conversion to type "unsigned char */
        SchM_Enter_Dcm_ProtclProtection();
        LddPduInfoPtr->SduLength = (PduLengthType)Dcm_GaaDslPeriodicData[LucBufferIndex].ulDataLen;
        SchM_Exit_Dcm_ProtclProtection();
      }
      /*
       * Check if the requested length is less than or equal to remaining
       * response bytes to be transmitted
      */
      SchM_Enter_Dcm_ProtclProtection();
       LusDataLen = Dcm_GaaDslPeriodicData[LucBufferIndex].ulDataLen;
      SchM_Exit_Dcm_ProtclProtection();


      if(PduInfoPtr->SduLength <= LusDataLen)
      {
        LusNoOfBytes = PduInfoPtr->SduLength;
        /*Loop until the data are copied to destination buffer*/
        do
        {
            /* Update 32 bit information */
            SchM_Enter_Dcm_ProtclProtection();
            *(LddPduInfoPtr->SduDataPtr) = *(Dcm_GaaDslPeriodicData[LucBufferIndex].pPerData);
            Dcm_GaaDslPeriodicData[LucBufferIndex].pPerData++;
            SchM_Exit_Dcm_ProtclProtection();
            LddPduInfoPtr->SduDataPtr++;
            LusNoOfBytes--;

        }while(LusNoOfBytes != DCM_ZERO);

        (LddPduInfoPtr->SduDataPtr) -= (PduInfoPtr->SduLength);

        SchM_Enter_Dcm_ProtclProtection();
        Dcm_GaaDslPeriodicData[LucBufferIndex].pPerData -=  
        Dcm_GaaDslPeriodicData[LucBufferIndex].ulDataLen;
        Dcm_GaaDslPeriodicData[LucBufferIndex].ulDataLen -= PduInfoPtr->SduLength;
        SchM_Exit_Dcm_ProtclProtection();
        
        /*
          Check if the requested length is greater than the filled page
          length
         */
        SchM_Enter_Dcm_ProtclProtection();
        LusDataLen = Dcm_GaaDslPeriodicData[LucBufferIndex].ulDataLen;
        SchM_Exit_Dcm_ProtclProtection();
        if(PduInfoPtr->SduLength > LusDataLen)
        {
          /*
            * Update the TxDataCntPtr of with the available response
            * length
          */
          *TxDataCntPtr = DCM_ZERO;

          /* Update the available response length to ZERO */
          SchM_Enter_Dcm_ProtclProtection();
          Dcm_GaaDslPeriodicData[LucBufferIndex].ulDataLen = DCM_ZERO;
          LpPerTxPduIdTable->blBufferProvided = DCM_TRUE;
          SchM_Exit_Dcm_ProtclProtection();
        }
        else
        {

          /* Update the variable for providing buffer as TRUE */
          SchM_Enter_Dcm_ProtclProtection();
          /* MISRA Rule        : 17.4
            Message            : Performing pointer arithmetic
            Reason             : Increment operator not used
                                 to achieve better throughput.
            Verification       : However, part of the code
                                 is verified manually and
                                 it is not having any impact.
          */
          (Dcm_GaaDslPeriodicData[LucBufferIndex].pPerData) +=
            PduInfoPtr->SduLength;
          /*
            * Decrement the number of bytes transmitted in the current
            * request
          */
          Dcm_GaaDslPeriodicData[LucBufferIndex].ulDataLen -=
          PduInfoPtr->SduLength;
          SchM_Exit_Dcm_ProtclProtection();
        }


        /*
          * Decrement the total response length by the size of the
          * buffer provided
        */

        /* Update the return value */
        LddReturnValue = BUFREQ_OK;
        /* Check if the response length is ZERO */
        if((LusDataLen != DCM_ZERO))
        {
          /*
             * Update the bit flag for the page transmitted from DSL layer
             * to FALSE
          */
           Dcm_PrtclTxBufStatus.ucBufferProvided =
            DCM_TRUE;
        }
        else
        {
          /* do nothing */
        }
      } /* if(Length <= Dcm_GddTxResponseLen) */
      else
      {
        /* Update the flag for buffer provided to TRUE */
        Dcm_PrtclTxBufStatus.ucBufferProvided =
          DCM_TRUE;
      }
      /* Check whether the total response length is ZERO */
      if(LusDataLen == DCM_ZERO)
      {
        /* Update the flag for buffer provided to TRUE */
        Dcm_PrtclTxBufStatus.ucBufferProvided =
          DCM_TRUE;
      }/*if(Dcm_TxRespStatus.ucNegResp == DCM_FALSE) */
    }
  }
  return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_TpTxConfirmation                                **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : This service confirms the transmission of the       **
**                        complete request, the buffer will be unlocked       **
**                        after this confirmation function                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DcmTxPduId, Result                                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GblInitStatus,             **
**                        Dcm_PrtclTxBufStatus, Dcm_TxRespStatus,       **
**                        Dcm_GddCurrentSession, Dcm_GddProtocolId,           **
**                        Dcm_TimerReqFlagStatus, Dcm_GddDcmTxConfPduId    **
**                        Dcm_GaaPduIdTableConfig , Dcm_GddRxPduId            **
**                        Dcm_GblNormalReq , Dcm_GblResOnPeriodicIdStatus     **
**                        Dcm_GaaProtocolConfig , Dcm_GucPeriodicRxPduId      **
**                        Dcm_GaaDslPeriodicData , Dcm_GstCurrentTimingValue  **
**                        Dcm_GulChannelIdentifier,  Dcm_GblSecDeclRequest    **
**                        Dcm_MemServicePendingStatus ,                    **
**                        Dcm_GblRespPendConfirmation                         **
**                        Function(s) invoked : (void)Det_ReportError,        **
**                        SchM_Enter_Dcm_<name>, SchM_Exit_Dcm_<name>,        **
**                        ComM_DCM_InactiveDiagnostic, Dcm_DsdConfirmation    **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_APPL_CODE) Dcm_TpTxConfirmation(PduIdType DcmTxPduId,
  NotifResultType Result)
{
  #if ((DCM_PROTOCOL_TRANSTYPE2 == STD_ON) && \
    (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON))
  P2VAR(Dcm_DslPeriodicTxId, AUTOMATIC, DCM_APPL_DATA) LpPerTxPduIdTable;
  uint8 LucMaxNumTxPduid;
  uint8 LucIndex;
  #endif
  uint8 LucProtocolIDIndex;

  /* Check if the pre compile option DCM_DEV_ERROR_DETECT is enabled */
  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  /* Check whether the module is Initialized */
  if (Dcm_GblInitStatus == DCM_UNINITIALISED)
  {
    /* Report to DET */
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID,
    DCM_TX_CONFIRMATION_SID, DCM_E_UNINIT);
  }
  else
  #endif
  {
    if 
    (
      (
        (
          (Dcm_PrtclTxBufStatus.ucBufferProvided == DCM_TRUE) ||
          (Dcm_PrtclTxBufStatus.ucCopyTxRejected == DCM_TRUE)
        ) 
        && 
        (Dcm_GddDcmTxConfPduId == DcmTxPduId) 
        &&
        (
          (Dcm_GblNormalReq == DCM_TRUE)
          #if((DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) && (DCM_PROTOCOL_TRANSTYPE2 == STD_OFF))
          || 
          (Dcm_GblResOnPeriodicIdStatus == DCM_TRUE)
          #endif
        )
      )
      #if((DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) && (DCM_PROTOCOL_TRANSTYPE2 == STD_ON))
      || 
      (Dcm_PrtclTxBufStatus.ucPeriodicIdStatus == DCM_TRUE)
      #endif     
      
      #if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
      || 
      (Dcm_GucResOnEventStatus == DCM_ROEONGOING)
      #endif
    )
    {
      if(Dcm_TxRespStatus.ucNegResp == DCM_FALSE)
      {
        /* Check if global bit flag for normal response is TRUE */
        if((Dcm_TxRespStatus.ucNormResponse == DCM_TRUE)&&
           /* (Dcm_GddDcmTxConfPduId == DcmTxPduId) &&  duplicated code , refer 1887 */
           (Dcm_GddRxPduId < Dcm_Num_Of_PduidTableConfig)) /* condition is always true , refer line 1842 */
        {
          /* Set the global bit flag for normal response to FALSE */
          Dcm_TxRespStatus.ucNormResponse = DCM_FALSE;
          Dcm_PrtclTxBufStatus.ucBufferProvided = DCM_FALSE;
          Dcm_PrtclTxBufStatus.ucCopyTxRejected = DCM_FALSE;

          SchM_Enter_Dcm_RxPduIdProtection();
          /* Clear the RxPduId status  of the corresponding RxpduId */
          DCM_CLR_PDU_STATUS(&Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId]);
          Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId].ucReceiveStatus = DCM_RECEPTION_IDLE;
          SchM_Exit_Dcm_RxPduIdProtection();

          LucProtocolIDIndex = Dcm_GetProtocolIDIndex(Dcm_GddProtocolId);

          if (LucProtocolIDIndex < Dcm_Num_Of_ProtocolConfig)
          {
            if (NULL_PTR != Dcm_GaaProtocolConfig[LucProtocolIDIndex].pProtocolStatus)             
            {
              SchM_Enter_Dcm_ProtclProtection();
              DCM_CLR_PROTOCOL_STATUS(&Dcm_GaaProtocolConfig[LucProtocolIDIndex]);
              SchM_Exit_Dcm_ProtclProtection();
            }
          }
          
          /* A request is completed and new request can be accepted */
          Dcm_GblNormalReq = DCM_FALSE;
        }

        #if((DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) && (DCM_PROTOCOL_TRANSTYPE2 == STD_ON))
        /*
        * Check if the current request under process is of normal request or
        * periodic request and if the confirmation was not called during
        * paged transmission
        */
        if (((Dcm_GblNormalReq == DCM_TRUE) ||
             (Dcm_PrtclTxBufStatus.ucPeriodicIdStatus == DCM_TRUE)) &&           
             (Dcm_TxRespStatus.ucPagedTrans == DCM_FALSE))
        { 
          /* Reset the global variable for Periodic request */         
          boolean LblPerConfTxPduIdFound = DCM_FALSE;
          
          if ((Dcm_PrtclTxBufStatus.ucPeriodicIdStatus == DCM_TRUE) &&
              (Dcm_GaaPduIdTableConfig[Dcm_GucPeriodicRxPduId].pPeriodicTxId != NULL_PTR))
          {
            LucMaxNumTxPduid = Dcm_GaaPduIdTableConfig[Dcm_GucPeriodicRxPduId].ucNoofPeriodicCon;
            LucIndex = 0U; 
            while ((LucIndex < LucMaxNumTxPduid) && (DCM_TRUE != LblPerConfTxPduIdFound))
            {
              LpPerTxPduIdTable = 
                &Dcm_GaaPduIdTableConfig[Dcm_GucPeriodicRxPduId].pPeriodicTxId[LucIndex];
              if((DcmTxPduId == LpPerTxPduIdTable->usPerTxConfmPduId) &&
                (LpPerTxPduIdTable->blBufferProvided == DCM_TRUE))
              {
                LblPerConfTxPduIdFound = DCM_TRUE;

                SchM_Enter_Dcm_ProtclProtection();

                /* Clear the  status  of periodic TxPduId */
                DCM_CLR_PERIODIC_PDU_STATUS(LpPerTxPduIdTable);
                
                Dcm_GaaDslPeriodicData[LpPerTxPduIdTable->ucPeriBufferIndex].ucDataStatus = DCM_PER_DATA_IDLE;
                LpPerTxPduIdTable->blBufferProvided = DCM_FALSE;
                
                SchM_Exit_Dcm_ProtclProtection();
              }
              LucIndex++;
            }
          }
          if(LblPerConfTxPduIdFound == DCM_FALSE)
          {
            Dcm_GblNormalReq = DCM_FALSE;
          }
        }
        #endif

        /* Invoke the internal DSD confirmation */
        Dcm_DsdConfirmation(Result);
        /*Restart the S3 server Timer */
        if(CHECK_NONDEFAULT_SESSION(Dcm_GddCurrentSession))
        {
          /*
          [SWS_Dcm_00141] 
          Subsequent start:
          Completion of any final response message or an error indication
          (Dcm_TpTxConfirmation: confirmation of complete PDU or indication of
          an error)
          */
          SchM_Enter_Dcm_TimerProtection();
          DCM_START_TIMER(DCM_S3SERVER_TIMER, Dcm_GstCurrentTimingValue.Timer_S3Server);
          Dcm_TimerReqFlagStatus.ucS3Timer = DCM_TRUE;
          SchM_Exit_Dcm_TimerProtection();
        }
        else
        {
          /* Invoke API to inactivate diagnostic session */
          (void)ComM_DCM_InactiveDiagnostic((NetworkHandleType)Dcm_GulChannelIdentifier);
        }
        Dcm_PrtclTxBufStatus.ucBufferProvided = DCM_FALSE;
        Dcm_PrtclTxBufStatus.ucCopyTxRejected = DCM_FALSE;
      }
      else
      {
        Dcm_MemServicePendingStatus.ucStartProtocolFailed = DCM_FALSE;
        /* Update the local variable to DCM_TRUE for clearing the status and
           to start the S3 server Timer */
        Dcm_DslStatusReset();
      }
    }
    #if(DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
    else if(Dcm_GblSecDeclRequest == DCM_TRUE)
    {
      Dcm_GblSecDeclRequest = DCM_FALSE;
      Dcm_GddSecDeclTxPduId = DCM_ZERO;
    }
    #endif
    #if(DCM_DEV_ERROR_DETECT == STD_ON)
    else if(Dcm_GddDcmTxConfPduId != DcmTxPduId)
    {
      /* Report to DET */
      (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID, DCM_TX_CONFIRMATION_SID, DCM_E_PARAM);
    }
    #endif
    else
    {      
      /* FIXME: Dcm_GblRspPenOnBtlTrans is not used
      if(Dcm_GblRspPenOnBtlTrans == DCM_TRUE)
      {
        Dcm_DsdConfirmation(NTFRSLT_E_NOT_OK);
      }
      */
    }
    /* Check if the normal request is ongoing */
    if ((Dcm_TxRespStatus.ucNegResp == DCM_TRUE) 
      &&
      (
        (Dcm_GddDcmTxConfPduId == DcmTxPduId)
        #if(DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
        || 
        (Dcm_GddSecDeclConfTxPduId == DcmTxPduId)
        #endif
      )       
    )    
    {
      if(Dcm_MemServicePendingStatus.ucStartProtocolFailed == DCM_TRUE)
      {
        Dcm_MemServicePendingStatus.ucStartProtocolFailed = DCM_FALSE;
        /* Update the local variable to DCM_TRUE for clearing the status and
           to start the S3 server Timer */
        Dcm_DslStatusReset();
      }

      if (NTFRSLT_OK != Result) 
      {
        if (DCM_TRUE == Dcm_TxRespStatus.ucNeedFailedConfiramtion)
        {
          Dcm_TriggerCancelPendingOperation = DCM_TRUE;
          Dcm_DsdConfirmation(NTFRSLT_E_NOT_OK);        
        }
      }

      Dcm_TxRespStatus.ucNegResp = DCM_FALSE;
      /* #6972 Clear ucNeedFailedConfiramtion for DCM_RES_POS_OK */
      Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_FALSE;
      Dcm_GblRespPendConfirmation = DCM_TRUE;
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_ComM_NoComModeEntered                           **
**                                                                            **
** Service ID           : 0x21                                                **
**                                                                            **
** Description          : This API disables all kind of transmissions and     **
**                        receptions                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : NetworkId                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GaaCommMode,               **
**                        Dcm_GblInitStatus                                   **
**                        Function(s) invoked : (void)Det_ReportError         **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_APPL_CODE) Dcm_ComM_NoComModeEntered(uint8 NetworkId)
{
  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the DCM Module is not Initialized */
  if(Dcm_GblInitStatus == DCM_UNINITIALISED)
  {
    /* Report Error to DET */
    (void)Det_ReportError(DCM_MODULE_ID, DCM_INSTANCE_ID,
      DCM_COMM_NO_COM_MODE_ENTERED_SID, DCM_E_UNINIT);
  }
  else if(NetworkId >= Dcm_No_Of_Comm_Channels)
  {
    /* Report Error to DET */
    (void)Det_ReportError(DCM_MODULE_ID, DCM_INSTANCE_ID,
      DCM_COMM_NO_COM_MODE_ENTERED_SID, DCM_E_INTERFACE_BUFFER_OVERFLOW);
  }
  else
  #endif
  {
    Dcm_GaaCommMode[NetworkId] = DCM_NO_COMMUNICATION;
  }
}

/*******************************************************************************
** Function Name        : Dcm_ComM_SilentComModeEntered                       **
**                                                                            **
** Service ID           : 0x22                                                **
**                                                                            **
** Description          : This API stops all outgoing transmissions           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : NetworkId                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GaaCommMode,               **
**                        Dcm_GblInitStatus                                   **
**                        Function(s) invoked : (void)Det_ReportError         **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_APPL_CODE) Dcm_ComM_SilentComModeEntered(uint8 NetworkId)

{
  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the DCM Module is not Initialized */
  if(Dcm_GblInitStatus == DCM_UNINITIALISED)
  {
    /* Report Error to DET */
    (void)Det_ReportError(DCM_MODULE_ID, DCM_INSTANCE_ID,
      DCM_COMM_SILENT_COM_MODE_ENTERED_SID, DCM_E_UNINIT);
  }
  else if(NetworkId >= Dcm_No_Of_Comm_Channels)
  {
    /* Report Error to DET */
    (void)Det_ReportError(DCM_MODULE_ID, DCM_INSTANCE_ID,
      DCM_COMM_NO_COM_MODE_ENTERED_SID, DCM_E_INTERFACE_BUFFER_OVERFLOW);
  }
  else
  #endif
  {
    /* Update the global variable for Communication Mode */
    Dcm_GaaCommMode[NetworkId] = DCM_SILENT_COMMUNICATION;
  }
}

/*******************************************************************************
** Function Name        : Dcm_ComM_FullComModeEntered                         **
**                                                                            **
** Service ID           : 0x23                                                **
**                                                                            **
** Description          : This API enables all kind of transmissions and      **
**                        receptions                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : NetworkId                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GaaCommMode,               **
**                        Dcm_GblInitStatus                                   **
**                        Function(s) invoked : (void)Det_ReportError         **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_APPL_CODE) Dcm_ComM_FullComModeEntered(uint8 NetworkId)
{
  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the DCM Module is not Initialized */
  if(Dcm_GblInitStatus == DCM_UNINITIALISED)
  {
    /* Report Error to DET */
    (void)Det_ReportError(DCM_MODULE_ID, DCM_INSTANCE_ID,
      DCM_COMM_FULL_COM_MODE_ENTERED_SID, DCM_E_UNINIT);
  }
  else if(NetworkId >= Dcm_No_Of_Comm_Channels)
  {
    /* Report Error to DET */
    (void)Det_ReportError(DCM_MODULE_ID, DCM_INSTANCE_ID,
      DCM_COMM_NO_COM_MODE_ENTERED_SID, DCM_E_INTERFACE_BUFFER_OVERFLOW);
  }
  else
  #endif
  {
    Dcm_GaaCommMode[NetworkId] = DCM_FULL_COMMUNICATION;
  }
}

/*******************************************************************************
** Function Name        : Dcm_DslCopyROETxData                                **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : This service request the DCM module to provide the  **
**                        buffer for the response transmission.               **
**                                                                            **
** Sync/Async          : Synchronous                                          **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DcmTxPduId, RetryInfoPtr                            **
**                                                                            **
** InOut Parameters     : PduInfoPtr                                          **
**                                                                            **
** Output Parameters    : TxDataCntPtr                                        **
**                                                                            **
** Return parameter     : BufReq_ReturnType                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GpRoeMsgContext            **
**                                                                            **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if ((DCM_PROTOCOL_TRANSTYPE2 == STD_ON) && \
  (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON))
FUNC(BufReq_ReturnType, DCM_APPL_CODE)Dcm_DslCopyROETxData(
  P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) TxDataCntPtr)
{
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST)LpPduIdTable;
  P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA) LddPduInfoPtr;
  BufReq_ReturnType LddReturnValue;
  uint32 LulDataLen;
  uint32 LusNoOfBytes;
  uint8 LucNetworkId;

  LddPduInfoPtr = (P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA))PduInfoPtr;
  LddReturnValue = BUFREQ_E_NOT_OK;
  LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GpRoeMsgContext->dcmRxPduId];
  LucNetworkId = LpPduIdTable->ucRxComChannelRef;

  if(Dcm_GaaCommMode[LucNetworkId] == DCM_FULL_COMMUNICATION)
  {
    if(LddPduInfoPtr->SduLength == DCM_ZERO)
    {
      /*
       * Update the length with the global variable for available
       * response length
     */
      SchM_Enter_Dcm_ProtclProtection();
      LddPduInfoPtr->SduLength = Dcm_GpRoeMsgContext->resDataLen;
      SchM_Exit_Dcm_ProtclProtection();
    }
    /*
     * Check if the requested length is less than or equal to remaining
     * response bytes to be transmitted
    */
    SchM_Enter_Dcm_ProtclProtection();
     LulDataLen = Dcm_GpRoeMsgContext->resDataLen;
    SchM_Exit_Dcm_ProtclProtection();


    if(PduInfoPtr->SduLength <= LulDataLen)
    {
      LusNoOfBytes = PduInfoPtr->SduLength;
      /*Loop until the data are copied to destination buffer*/
      do
      {
          /* Update 32 bit information */
          SchM_Enter_Dcm_ProtclProtection();
          *(LddPduInfoPtr->SduDataPtr) = *(Dcm_GpRoeMsgContext->resData);
          /* MISRA Rule        : 17.4
            Message            : Increment or decrement operation
                                 performed on pointer
            Reason             : Increment operator not used
                                 to achieve better throughput.
            Verification       : However, part of the code
                                 is verified manually and
                                 it is not having any impact.
          */
          Dcm_GpRoeMsgContext->resData++;
          SchM_Exit_Dcm_ProtclProtection();
          /* MISRA Rule        : 17.4
            Message            : Increment or decrement operation
                                 performed on pointer
            Reason             : Increment operator not used
                                 to achieve better throughput.
            Verification       : However, part of the code
                                 is verified manually and
                                 it is not having any impact.
          */
          LddPduInfoPtr->SduDataPtr++;
          LusNoOfBytes--;

      }while(LusNoOfBytes != DCM_ZERO);

      /* MISRA Rule        : 17.4
        Message            : Performing pointer arithmetic
        Reason             : Increment operator not used
                             to achieve better throughput.
        Verification       : However, part of the code
                             is verified manually and
                             it is not having any impact.
      */
      (LddPduInfoPtr->SduDataPtr) -= (PduInfoPtr->SduLength);
      SchM_Enter_Dcm_ProtclProtection();
      /* MISRA Rule        : 17.4
        Message            : Performing pointer arithmetic
        Reason             : Increment operator not used
                             to achieve better throughput.
        Verification       : However, part of the code
                             is verified manually and
                             it is not having any impact.
      */
      Dcm_GpRoeMsgContext->resData -= Dcm_GpRoeMsgContext->resDataLen;
      Dcm_GpRoeMsgContext->resDataLen -= (PduInfoPtr->SduLength);
      SchM_Exit_Dcm_ProtclProtection();
      /*
        Check if the requested length is greater than the filled page
        length
       */
      SchM_Enter_Dcm_ProtclProtection();
      LulDataLen = Dcm_GpRoeMsgContext->resDataLen;
      SchM_Exit_Dcm_ProtclProtection();
      if(Dcm_GpRoeMsgContext->resDataLen != DCM_ZERO)
      {
        /*
          * Update the TxDataCntPtr of with the available response
          * length
        */
        *TxDataCntPtr = Dcm_GpRoeMsgContext->resDataLen;

        /* Update the available response length to ZERO */
        SchM_Enter_Dcm_ProtclProtection();

        /* MISRA Rule        : 17.4
          Message            : Performing pointer arithmetic
          Reason             : Increment operator not used
                               to achieve better throughput.
          Verification       : However, part of the code
                               is verified manually and
                               it is not having any impact.
        */
        Dcm_GpRoeMsgContext->resData += PduInfoPtr->SduLength;

        SchM_Exit_Dcm_ProtclProtection();
      }
      else
      {
      *TxDataCntPtr = DCM_ZERO;
      }

      /*
        * Decrement the total response length by the size of the
        * buffer provided
      */

      /* Update the return value */
      LddReturnValue = BUFREQ_OK;
      /* Check if the response length is ZERO */
      if((LulDataLen != DCM_ZERO))
      {
        /*
           * Update the bit flag for the page transmitted from DSL layer
           * to FALSE
        */
         Dcm_PrtclTxBufStatus.ucBufferProvided =
          DCM_TRUE;
      }
      else
      {
        /* do nothing */
      }
    } /* if(Length <= Dcm_GddTxResponseLen) */
    else
    {
      /* Update the flag for buffer provided to TRUE */
      Dcm_PrtclTxBufStatus.ucBufferProvided =
        DCM_TRUE;
    }
    /* Check whether the total response length is ZERO */
    if(LulDataLen == DCM_ZERO)
    {
      /* Update the flag for buffer provided to TRUE */
      Dcm_PrtclTxBufStatus.ucBufferProvided =
        DCM_TRUE;
    }/*if(Dcm_TxRespStatus.ucNegResp == DCM_FALSE) */
  }

  return(LddReturnValue);
}
#endif

  /* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace:end<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:end<RTE: IDP : Not a defect : No Action Planned > configured memory access index */
/* polyspace:end<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
/* polyspace:end<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace-end MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:10.4 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-end CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */
  
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
