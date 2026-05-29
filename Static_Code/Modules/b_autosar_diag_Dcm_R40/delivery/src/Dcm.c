/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE: Dcm.c                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the API definitions for Dsl layer of Dcm,  **
**              Initialization and scheduler functions of Dcm module          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By                Description                      **
********************************************************************************
** 2.3.7.0   08-Apr-2021   EunKyung Kim      #29178                           **
**                                                                            **
** 2.3.6.0   26-Mar-2021   EunKyung Kim      #29050                           **
**                                                                            **
** 2.3.4.0   28-Jan-2021   EunKyung Kim      #27941                           **
**                                                                            **
** 2.3.2.0   05-Nov-2020   EunKyung Kim      #26432                           **
**                                                                            **
** 2.3.1.0   10-Oct-2020   YoungJin Yun      #26044                           **
**                                                                            **
** 1.0.9     02-28-2020    EunKyung Kim      #22299, #21905                   **
**                                                                            **
** 1.0.8     11-25-2019    EunKyung Kim      #19580                           **
**                                                                            **
** 1.0.7     16-07-2019    Y.S     Jeon      #2212                            **
**                                                                            **
** 1.0.19    18-06-2019    Y.S     Jeon      #17902                           **
**                                                                            ** 
** 1.0.18    06-11-2018    Y.S     Jeon      #13923                           **
**                                                                            ** 
** 1.0.17    12-09-2018    Y.S     Jeon      #13032                           **
**                                                                            **
** 1.0.16    18-05-2018    Y.S     Jeon      #12651                           **
**                                                                            **                                                          
** 1.0.15    12-06-2017    Jin     Jung      #5428                            **
**                                                                            **
** 1.0.14    28-03-2017    Jin     Jung      #7631                            **
**                                                                            **
** 1.0.13    01-02-2017    Jin     Jung      #7540                            **
**                                                                            **
** 1.0.12    02-01-2017    Jin     Jung      #6116                            **
**                                                                            **
** 1.0.11    04-10-2016    Jin     Jung      #5673, #5759                     **
**                                                                            **
** 1.0.10    25-05-2016    Jin     Jung      #5397                            **
**                                                                            **
** 1.0.9     25-05-2016    Sungeol Baek      #5006                            **
**                                                                            **
** 1.0.8     03-03-2016    Sungeol Baek      #3754, #3747, RTRT reflection    **
**                                                                            **
** 1.0.7     28-10-2015    Youngjin Yun      #3394                            **
**                                                                            **
** 1.0.6     10-08-2015    Youngjin Yun      #2977                            **
**                                                                            **
** 1.0.5     16-07-2015    Sungeol Baek      #2678                            **
**                                                                            **
** 1.0.4     16-04-2015    Sungeol Baek      #2171                            **
**                                                                            **
** 1.0.3     24-03-2015    Sungeol Baek      #2370                            **
**                                                                            **
** 1.0.2     26-02-2015    Sungeol Baek      #2163                            **
**                                                                            **
** 1.0.1     26-02-2015    YoungJin Yun      #414, #1044                      **
**                                                                            **
** 1.0.0     09-01-2013    Autron            Initial Version                  **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_Types.h"
#include "Rte_Dcm.h"
#include "Dem.h"

#if(DCM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#include "NvM.h"
#include "SchM_Dcm.h"
#include "Dcm_CallOuts.h"
#include "BswM_Dcm.h"
#include "ComM_Dcm.h"
#include "PduR_Dcm.h"
#include "Dcm_Ram.h"
#include "Dcm_Dsl.h"
#include "Dcm_DspMain.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_DslInternal.h"
#include "Dcm_DspServices.h"
#include "Dcm_DspMemoryServices.h"
#include "Dcm_DspNonPagedDTCSubFct.h"
#include "Dcm_DspReadDTCInfo.h"
#include "Dcm_DspOBDInternals.h"
#include "Dcm_DspOBDServices.h"

#if(DCM_ROUTINECONTROL_SERVICE == STD_ON)
#include "Dcm_Routine.h"
#endif

#if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
#include "Dcm_DspResponseOnEvent.h"
#endif

#include "Dcm_Config.h"
#include "Dcm_Lib.h"

/* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.2 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:10.4 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace-begin DEFECT:USELESS_WRITE [Not a defect:Low] "This condition is covered by configuration." */
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Nesting of control structures to achieve better throughput. */
/* polyspace:begin<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
/* polyspace:begin<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */
/* polyspace:begin<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-begin CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-begin CERT-C:DCL39-C [Justified:Low] "Dcm_SetProgConditions is call out and this function is user code . No impact" */
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

static FUNC(void, DCM_CODE) Dcm_Internal_UpdateTime (void);
static FUNC(void, DCM_CODE) Dcm_Internal_TransmitResponse (void);
static FUNC(void, DCM_CODE) Dcm_Internal_processRequest (void);


#if((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
       (DCM_MAX_NO_OF_PRECONFIGURED_DID != DCM_ZERO))
  
static FUNC(void, DCM_CODE) Dcm_Internal_ResponseOnEvent (void);
#endif

static FUNC(void, DCM_CODE) Dcm_Internal_ServicesPending (void);

#if ((DCM_PAGEDBUFFER_ENABLED == STD_ON) && \
       ((DCM_READDTC_SUPPORT == STD_ON) || \
       (DCM_OBD_SUPPORT == STD_ON) || \
       (DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON)))

static FUNC(void, DCM_CODE) Dcm_Internal_ChkUpdatePage (void);
#endif

static FUNC(void, DCM_CODE) Dcm_Internal_GblFirstCallToMain (void);

#if((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) && \
      (DCM_MODE_RULE == STD_ON) && (DCM_DSP_COMM_CONTROL_CONFIGURED == STD_ON))
static FUNC(void, DCM_CODE) Dcm_Internal_ChkCommunicationMode (void);
#endif

static FUNC(void, DCM_CODE) Dcm_Internal_ChkResponseTime (void);

#if(DCM_PAGEDBUFFER_ENABLED == STD_ON)

static FUNC(void, DCM_CODE) Dcm_Internal_ChkPagedBufferTime (void);
#endif

static FUNC(void, DCM_CODE) Dcm_Internal_ChkS3ServerTime (void);

#if((DCM_DSP_CONTROL_DTC_SERVICE == STD_ON) && \
     (DCM_MODE_RULE == STD_ON) && (DCM_DSP_CONTROL_DTC_CONFIGURED == STD_ON))

static FUNC(void, DCM_CODE) Dcm_Internal_ChkControlDTCSetting (void);
#endif

#if(DCM_DSP_SECURITY_SERVICE == STD_ON)
static FUNC(void, DCM_CODE) Dcm_SecurityAccessMainFunction (void);
#endif

#if((DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON) || \
    (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON) || \
    (DCM_TRANSFER_DATA_SERVICE == STD_ON) || \
    (DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON) || \
    (DCM_REQUEST_UPLOAD_SERVICE == STD_ON) || \
    (DCM_TRANSFER_EXIT_SERVICE == STD_ON))
static FUNC(void, DCM_CODE) Dcm_MemoryServicesMainFunction (void);
#endif

#if((DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON)|| \
    (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
    (DCM_ROUTINECONTROL_SERVICE == STD_ON))
static FUNC(void, DCM_CODE) Dcm_DIDServicesMainFunction (void);
#endif

#if((DCM_DSP_CLR_DIAG_SERVICE == STD_ON) || \
    (DCM_OBD_CLRRESET_EMISSION_DIAGINFO_SERVICE == STD_ON)|| \
    (DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON)|| \
    (DCM_RPT_NOOFDTC == STD_ON) || \
    (DCM_RPT_DTC == STD_ON) || \
    (DCM_RPT_DTC_FLT_DET_CTR == STD_ON) || \
    ((DCM_OBD_GETDTC_03_SERVICE == STD_ON) || \
    (DCM_OBD_GETDTC_07_SERVICE == STD_ON) || \
    (DCM_OBD_GETDTC_0A_SERVICE == STD_ON)) || \
    (DCM_FAULT_DETECTION_COUNTER == STD_ON))
static FUNC(void, DCM_CODE) Dcm_OBD_DTC_MainFunction (void);
#endif

#if((DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
    (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(void, DCM_CODE) Dcm_READ_WRITE_DID_MainFunction (void);
#endif

    /* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dcm_Internal_UpdateTime                             **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This function updates internal timer                **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, DCM_CODE) Dcm_Internal_UpdateTime (void)
{
  uint8 LucTimerIndex;
    
  /* Update the respective timers if it is running */
  for(LucTimerIndex = DCM_ZERO; LucTimerIndex < DCM_NINE; LucTimerIndex++)
  {
    if(Dcm_GaaTimer[LucTimerIndex] != DCM_ZERO)
    {
      Dcm_GaaTimer[LucTimerIndex]--;
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_Internal_TransmitResponse                       **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This function transmits response message from       **
**                        main function.                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Internal_TransmitResponse (void)
{
  if(Dcm_GblReceiveRquest != DCM_TRUE)
  {
    if(Dcm_GblSendResponse == DCM_TRUE)
    {
      Dcm_GblSendResponse = DCM_FALSE;
      if (Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE)
      {
        Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
      }
      Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
    }
    /* TODO: plz redesign .. Direct transmission shall be removed */
    else if(Dcm_GblPduRTransmitResponse == DCM_TRUE)
    {
      Dcm_GblPduRTransmitResponse = DCM_FALSE;
      Dcm_DslPduRTransmit();
    }
    else
    {
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_Internal_TransmitResponse                       **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This function processes request message from        **
**                        main function.                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Internal_processRequest (void)
{
  if(Dcm_GblReceiveRquest == DCM_TRUE)
  {
    Dcm_GblReceiveRquest = DCM_FALSE;
    Dcm_DslCheckPrtclStatus();
  }  

}

/*******************************************************************************
** Function Name        : Dcm_Internal_ResponseOnEvent                        **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This function processes response on event from      **
**                        main function.                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#if((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
         (DCM_MAX_NO_OF_PRECONFIGURED_DID != DCM_ZERO))
static FUNC(void, DCM_CODE) Dcm_Internal_ResponseOnEvent (void)
{
  if(Dcm_GblNvmReadFlag == DCM_FALSE)
  {
    Std_ReturnType LddReturnValue;
    NvM_RequestResultType LddRequestResult;
        
    LddReturnValue = NvM_GetErrorStatus(DCM_RESPONSE_ONEVENT_BLOCKID, &LddRequestResult);
    if ((LddReturnValue == E_OK) && (LddRequestResult == NVM_REQ_OK))
    {
      Dcm_RetrieveStoredRoeEvent(DCM_ZERO);
      (void)Dcm_DspEnableRoe();
      /* Setting falg as True indicates Nvm Read all is completed*/
      Dcm_GblNvmReadFlag = DCM_TRUE;
    }
    else if((LddReturnValue == E_OK) &&(LddRequestResult == NVM_REQ_PENDING))
    {
       /* Do Nothing */
    }
    else
    {
      Dcm_DspRestorePreconfigDID();
      /* Setting falg as FALSE indicates Nvm Read all is completed*/
      Dcm_GblNvmReadFlag = DCM_TRUE;
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_Internal_ServicesPending                        **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : Dcm_Internal_ServicesPending                        **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/

static FUNC(void, DCM_CODE) Dcm_Internal_ServicesPending (void)
{
  if(Dcm_TxRespStatus.ucNegResp == DCM_FALSE)
  {
    /* NEED : critical section */
    SchM_Enter_Dcm_RxPduIdProtection();    
    if (DCM_TRUE == Dcm_TriggerCancelPendingOperation)
    {
      Dcm_TriggerCancelPendingOperation = DCM_FALSE;      
      SchM_Exit_Dcm_RxPduIdProtection();
      /* To Stop processing active diagnostic request */
      Dcm_DsdCancelOperation();
      Dcm_ServicePendingStatus.ucReadDataPendingStatus = DCM_FALSE;
        
      /* Update Dcm_GddNegRespError */          
      if((Dcm_PrtclTxBufStatus.ucClearDTCStatus == DCM_TRUE) ||
      (Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus == DCM_TRUE) ||
      (Dcm_PrtclTxBufStatus.ReportNumOfDtc == DCM_TRUE) ||
      (Dcm_GblDTCFDCPending == DCM_TRUE) ||
      (Dcm_PrtclTxBufStatus.ucReportOBDDtc == DCM_TRUE) ||
      (Dcm_GblFaultDetcetionCounter == DCM_TRUE))
      {
        Dem_DcmCancelOperation();
        Dcm_PrtclTxBufStatus.ucClearDTCStatus = DCM_FALSE;
        Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus = DCM_FALSE;
        Dcm_PrtclTxBufStatus.ReportNumOfDtc = DCM_FALSE;
        Dcm_PrtclTxBufStatus.ucReportOBDDtc = DCM_FALSE;
        Dcm_GblFaultDetcetionCounter = DCM_FALSE;
      }
    }
    else
    {
      P2VAR(Dcm_RequestContextType, AUTOMATIC, DCM_APPL_DATA) requestContext;     
      
      SchM_Exit_Dcm_RxPduIdProtection();      
      requestContext = Dcm_DsdInternal_GetRequestContextByRxPduId(Dcm_GddRxPduId);
      if (NULL_PTR == requestContext)
      {
        /* DET Error */
      }
      else if (DCM_E_PENDING == requestContext->rct_RequestResult)
      {        
        Dcm_DiagnosticSerivceDispatch(DCM_PENDING, requestContext);
      }
      else
      {  
        #if((DCM_DSP_CLR_DIAG_SERVICE == STD_ON) || \
        (DCM_OBD_CLRRESET_EMISSION_DIAGINFO_SERVICE == STD_ON)|| \
        (DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON)|| \
        (DCM_RPT_NOOFDTC == STD_ON) || \
        (DCM_RPT_DTC == STD_ON) || \
        (DCM_RPT_DTC_FLT_DET_CTR == STD_ON) || \
        ((DCM_OBD_GETDTC_03_SERVICE == STD_ON) || \
        (DCM_OBD_GETDTC_07_SERVICE == STD_ON) || \
        (DCM_OBD_GETDTC_0A_SERVICE == STD_ON)) || \
        (DCM_FAULT_DETECTION_COUNTER == STD_ON))
          Dcm_OBD_DTC_MainFunction();
        #endif
      
        #if((DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON) || \
          (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON) || \
          (DCM_TRANSFER_DATA_SERVICE == STD_ON) || \
          (DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON) || \
          (DCM_REQUEST_UPLOAD_SERVICE == STD_ON) || \
          (DCM_TRANSFER_EXIT_SERVICE == STD_ON))
        Dcm_MemoryServicesMainFunction();
        #endif
      
      
        #if((DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
          (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON))
        Dcm_READ_WRITE_DID_MainFunction();
        #endif
      
        #if((DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON)|| \
          (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
          (DCM_ROUTINECONTROL_SERVICE == STD_ON))
      
        Dcm_DIDServicesMainFunction();
        #endif
      
        #if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
        Dcm_ROE_MainFunction();
        #endif
      
        #if(DCM_DSP_SECURITY_SERVICE == STD_ON)
        Dcm_SecurityAccessMainFunction();
        #endif
      }
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_Internal_ServicesPending                        **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This function updates page for paged buffer from    **
**                        main function                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#if ((DCM_PAGEDBUFFER_ENABLED == STD_ON) && \
       ((DCM_READDTC_SUPPORT == STD_ON) || \
       (DCM_OBD_SUPPORT == STD_ON) || \
       (DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON)))
static FUNC(void, DCM_CODE) Dcm_Internal_ChkUpdatePage (void)
{
  /* Check whether the Update page was invoked during paged processing */
  if(Dcm_DspSerPgStatus.ucUpdatePageStarted == DCM_TRUE)
  {
    Dcm_DspSerPgStatus.ucUpdatePageStarted = DCM_FALSE;
    /* Perform the update page processing */
    Dcm_DspProcessUpdatePage();
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_Internal_GblFirstCallToMain                     **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This function processes data at first after         **
**                        MCU is reset                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Internal_GblFirstCallToMain (void)
{
  uint8 LucCount;
  /* Mainfunction is called at first after MCU is reset */
  if(Dcm_GblFirstCallToMain == DCM_TRUE)
  {
    Dcm_GblFirstCallToMain = DCM_FALSE;
    /* request the current programming condition */
    if(DCM_WARM_START == Dcm_GetProgConditions(&Dcm_GddProgConditions))
    {
      P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST)LpPduIdTable;
      P2CONST(Dcm_ProtocolConfig, AUTOMATIC, DCM_APPL_CONST) LpProtocolConfig;    
      boolean LblPduIdFound;

      LpPduIdTable = NULL_PTR;
      LblPduIdFound = DCM_FALSE;
      LucCount = DCM_ZERO; 
      while (LucCount < Dcm_Num_Of_PduidTableConfig)
      {
        LpPduIdTable = &Dcm_GaaPduIdTableConfig[LucCount];
        if ((LpPduIdTable->ucProRxTesterSrcAddr == Dcm_GddProgConditions.TesterSourceAddr) &&
            (LpPduIdTable->ucRxAddrType == DCM_ADDR_PHYSICAL))
        {
          Dcm_GstMsgContext.dcmRxPduId  =  LucCount;
          LblPduIdFound = DCM_TRUE;
          break;
        }
        LucCount++;
      }
      if (DCM_TRUE == LblPduIdFound)
      {
        Dcm_GulChannelIdentifier = LpPduIdTable->ulProRxChannelId;
        /* Inform ComM about the change in diagnostic session */
        (void)ComM_DCM_ActiveDiagnostic((NetworkHandleType)Dcm_GulChannelIdentifier);
        
        if((Dcm_GddProgConditions.ResponseRequired == DCM_TRUE) &&
           (LpPduIdTable->ucRxBufferId < Dcm_Num_Of_Buffer_Config) && 
           (LpPduIdTable->ucTxBufferId < Dcm_Num_Of_Buffer_Config))
        {
          uint8 LucProtocolIDIndex;
          Dcm_MsgType LpRxBufferId;
          Dcm_MsgType LpTxBufferId;
  
          Dcm_GddRxPduId = Dcm_GstMsgContext.dcmRxPduId;
          Dcm_GddDcmTxConfPduId  =  (uint8)LpPduIdTable->usTxConfirmationPduId;

          LucProtocolIDIndex = Dcm_GetProtocolIDIndex(LpPduIdTable->ddProtocolId);
          if (LucProtocolIDIndex < Dcm_Num_Of_ProtocolConfig)
          {
            LpProtocolConfig = &Dcm_GaaProtocolConfig[LucProtocolIDIndex];
            Dcm_GucPrtclPriority  = LpProtocolConfig->ucProtocolPrio;
          }

          LpRxBufferId = Dcm_GaaBufferConfig[LpPduIdTable->ucRxBufferId].pBufferArea;
          LpTxBufferId = Dcm_GaaBufferConfig[LpPduIdTable->ucTxBufferId].pBufferArea;

          Dcm_GstMsgContext.resData  = &LpTxBufferId[DCM_ONE];
          Dcm_GstMsgContext.reqData  =  &LpRxBufferId[DCM_ONE];
          LpTxBufferId[DCM_ONE] = Dcm_GddProgConditions.SubFncId;

          Dcm_GstMsgContext.idContext = (Dcm_GddProgConditions.Sid | DCM_RESPONSE_ID);         
          if(Dcm_GddProgConditions.Sid == DCM_DIAGNOSTICSESSIONCONTROL)
          {
            #if(DCM_DSP_DIAG_SESSION_SERVICE == STD_ON)
            P2CONST(Dcm_DiagSessionConfigType, AUTOMATIC, DCM_APPL_CONST) LpDiagData;
            Tun_DcmWord16 LunDcmServerTime;
          
            LpDiagData = Dcm_DsdInternal_GetSessionCfg(
              LpProtocolConfig,Dcm_GddProgConditions.SubFncId, &Dcm_DiagSessionState.sessionTableIndex);
  
            if(NULL_PTR != LpDiagData)
            {
              /* Update the P2ServerMax for the session */
              LunDcmServerTime.usWordReg16 = LpDiagData->usSesP2ServerMax;

              /* Update DCM_SESSION_P2SERVER_MAX time high byte */
              LpTxBufferId[DCM_TWO] = LunDcmServerTime.ddByte.ucMsByte;

              /* Update DCM_SESSION_P2SERVER_MAX time low byte */
              LpTxBufferId[DCM_THREE] = LunDcmServerTime.ddByte.ucLsByte;

              /* Update the P2StarServerMax for the session */
              LunDcmServerTime.usWordReg16 = LpDiagData->usSesP2StrServerMax;

              /* Update DCM_SESSION_P2STRSERVER_MAX time high byte */
              LpTxBufferId[DCM_FOUR] = LunDcmServerTime.ddByte.ucMsByte;

              /* Update DCM_SESSION_P2STRSERVER_MAX time low byte */
              LpTxBufferId[DCM_FIVE] = LunDcmServerTime.ddByte.ucLsByte;

                
              /* Dcm_GpMsgContext->resDataLen will be len+1 
               * when message is transmitted */
              Dcm_GstMsgContext.resDataLen = DCM_FIVE;
            }
            else
            #endif
            {
              Dcm_GstMsgContext.resDataLen = DCM_ONE;
            }
          }
          else /* ECUReset ? */
          {
            Dcm_GstMsgContext.resDataLen = DCM_ONE;
          }

          Dcm_GstMsgContext.msgAddInfo.reqType  =  DCM_ADDR_PHYSICAL;
          Dcm_GstMsgContext.msgAddInfo.suppressPosResponse  =  DCM_FALSE;
          Dcm_GblNormalReq = DCM_TRUE;
          Dcm_GblPosRspTransOnReset = DCM_TRUE; /* Only response */

          /* Initialize TxPduId configured for the RxPduId */
          Dcm_GddDcmTxPduId = LpPduIdTable->ddTxPduId;

          /* Enter DC */
          SchM_Enter_Dcm_RxPduIdProtection();
          /* Set the status of RxPduId */
          *(LpPduIdTable->pPduIdStatus) |= LpPduIdTable->ucPduIdStatusMask;
          /* Exit DC */
          SchM_Exit_Dcm_RxPduIdProtection();

          Dcm_PrtclTxBufStatus.ucProtclStatus = DCM_TRUE;
          Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
          Dcm_GddProgConditions.ResponseRequired = DCM_FALSE;
        }
      }
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_Internal_ChkCommunicationMode                   **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This function checks communication mode in          **
**                        main function                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#if((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) && \
      (DCM_MODE_RULE == STD_ON) && (DCM_DSP_COMM_CONTROL_CONFIGURED == STD_ON))
static FUNC(void, DCM_CODE) Dcm_Internal_ChkCommunicationMode (void)
{
  boolean LblSearchResult;
  uint8 LucCount;
   
  if(Dcm_GucComCtrlMode != DCM_ENABLE_RX_TX_NORM_NM)
  {
    LblSearchResult = Dcm_DsdModeRuleCheck(Dcm_Dsp_Comm_Control_Reenable_Mode_Rule);
    if(LblSearchResult == DCM_FALSE)
    {
      Dcm_GucComCtrlMode = DCM_ENABLE_RX_TX_NORM_NM;
      #if(DCM_TOTAL_NUM_OF_ALL_CHANNEL != DCM_ZERO)
      for(LucCount = DCM_ZERO;LucCount < Dcm_Total_Num_Of_All_Channel; LucCount++)
      {
        Dcm_GaaAllCommControlConfig[LucCount].pSchMSwitchAllCommModeFunc(Dcm_GucComCtrlMode);
        BswM_Dcm_CommunicationMode_CurrentState(Dcm_GaaAllCommControlConfig[LucCount].ucComChannelRef,
          Dcm_GucComCtrlMode);
      }
      #endif
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_Internal_ChkResponseTime                        **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This function checks response time in main function **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Internal_ChkResponseTime (void)
{
  /* Check if the Min response timer is enabled and it is expired */
  /*
    * Check if the Max response timer is enabled and timer has reached
    * half its Initialized value to send NRC
    * RequestCorrectlyReceivedResponsePending
  */
  SchM_Enter_Dcm_TimerProtection();
  if ((Dcm_PrtclTxBufStatus.ucProtclStatus == DCM_TRUE) && 
      (Dcm_TimerReqFlagStatus.ucP2MaxTimer == DCM_TRUE) && 
      (Dcm_GaaTimer[DCM_P2SERVERMAX_TIMER] == DCM_ZERO)
      /* ucPeriodicIdStatus is optional : modified by youngjin.yun */
      #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
      && (Dcm_PrtclTxBufStatus.ucPeriodicIdStatus == DCM_FALSE)
      #endif
  )
  {
    SchM_Exit_Dcm_TimerProtection();
    /* In case of responsePending, suppressPosRspMsgIndicationBit
     * should be cleared. Since final response (negative /positive)
     * is required then.
     */
    Dcm_GstMsgContext.msgAddInfo.suppressPosResponse = DCM_FALSE;
    /* The actual response is not available before the expiry of the
     * P2ServerMin timer
     */
    SchM_Enter_Dcm_TimerProtection();
    if(((Dcm_TxRespStatus.ucNormResponse == DCM_FALSE) &&
       (Dcm_TxRespStatus.ucDslPagedTrans == DCM_FALSE) &&
       (Dcm_TxRespStatus.ucNegResp == DCM_FALSE))
       #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
       || /* #6116, by Jin, 170102 */
       ((Dcm_TimerReqFlagStatus.ucPagedBufferTimer == DCM_TRUE) && 
       (Dcm_GaaTimer[DCM_PAGED_BUFFER_TIMER] != DCM_ZERO))
      #endif
      )
    {
      SchM_Exit_Dcm_TimerProtection();
      /* Update the negative response service Id in the response buffer */
      Dcm_GaaResponseBuf[DCM_ZERO] = DCM_NEGATIVE_RESPONSE_SID;
      /* Update the service Id in the response buffer */
      Dcm_GaaResponseBuf[DCM_ONE] = ((Dcm_GstMsgContext.idContext) & (DCM_BIT6_AND_MASK));
      /* Update the NRC in the response buffer */
      Dcm_GaaResponseBuf[DCM_TWO] = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
      /* Update Dcm_GusMaxNoOfRespPend */
      Dcm_GusMaxNoOfRespPend++;
      if (Dcm_GusMaxNoOfRespPend > (uint16)Dcm_diag_Resp_Max_Num_Respend)
      {
        /* Report to DET */
        #if(DCM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID,
        DCM_MAIN_FUNCTION_SID, DCM_E_INTERFACE_TIMEOUT);
        #endif

        Dcm_GusMaxNoOfRespPend = DCM_ZERO;

        /* Duplicated code : Dcm_DsdCancelOperation()
        #if(DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
        if ((Dcm_GstMsgContext.reqData != NULL_PTR) &&
            (Dcm_GstMsgContext.reqData[DCM_ZERO] == DCM_READDATABYIDENTIFIER))
        {             
          Dcm_DspInternal_DcmReadDataByIdentifier(DCM_CANCEL, &Dcm_GstMsgContext);
        }
        #endif
        */
        /* To Stop processing active diagnostic request */
        Dcm_DsdCancelOperation();
        Dcm_ServicePendingStatus.ucReadDataPendingStatus = DCM_FALSE;
          
        /* Update Dcm_GddNegRespError */          
        if((Dcm_PrtclTxBufStatus.ucClearDTCStatus == DCM_TRUE) ||
        (Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus == DCM_TRUE) ||
        (Dcm_PrtclTxBufStatus.ReportNumOfDtc == DCM_TRUE) ||
        (Dcm_GblDTCFDCPending == DCM_TRUE) ||
        (Dcm_PrtclTxBufStatus.ucReportOBDDtc == DCM_TRUE) ||
        (Dcm_GblFaultDetcetionCounter == DCM_TRUE))
        {
          Dem_DcmCancelOperation();
          Dcm_PrtclTxBufStatus.ucClearDTCStatus = DCM_FALSE;
          Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus = DCM_FALSE;
          Dcm_PrtclTxBufStatus.ReportNumOfDtc = DCM_FALSE;
          Dcm_PrtclTxBufStatus.ucReportOBDDtc = DCM_FALSE;
          Dcm_GblFaultDetcetionCounter = DCM_FALSE;
          /* timeout */
          #if ((DCM_CLEAR_ITC_SERVICE_SUPPRT == STD_ON) ||\
               (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON))
          Dcm_InternalTroubleCodeService = DCM_FALSE;
          #endif
        }
        Dcm_GddOpStatus = DCM_INITIAL;
        /* Report the NRC to the DSD layer */
        Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, DCM_E_GENERALREJECT);

        /* Transmit the response to the DSD layer */
        Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
      }
      else
      {
        /* Update the bit flag for negative response to TRUE */
        Dcm_TxRespStatus.ucNegResp = DCM_TRUE;
        Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_TRUE;

        /* Invoke the internal function to transmit negative response */
        Dcm_DslPduRTransmit();
      }
    }
    else
    {
      SchM_Exit_Dcm_TimerProtection();
    }
  }
  /* Check if the bit flag for protocol status is FALSE */
  else if((Dcm_PrtclTxBufStatus.ucProtclStatus == DCM_FALSE) &&
    (Dcm_TimerReqFlagStatus.ucPrtclPreemptTimer == DCM_FALSE) && 
    (Dcm_TxRespStatus.ucNegResp == DCM_TRUE))
  {
    SchM_Exit_Dcm_TimerProtection();
    /* Transmit the negative response */
    Dcm_DslPduRTransmit();
  }

  else if(
    (Dcm_TimerReqFlagStatus.ucPrtclPreemptTimer == DCM_TRUE) && 
    (Dcm_GaaTimer[DCM_PROTOCOL_PREEMPT_TIMER] != DCM_ZERO) &&
    (Dcm_TxRespStatus.ucNegResp == DCM_FALSE))
  {
    P2VAR (uint8, AUTOMATIC, DCM_APPL_DATA)LpRxPduIdData = &Dcm_GaaBufferArea[0];

    SchM_Exit_Dcm_TimerProtection();

    if(Dcm_GddRxPduId < Dcm_Num_Of_PduidTableConfig)
    {
      /* Get the buffer Id of the TxPduId */
      uint16 rxBufferId = (uint8)Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId].ucRxBufferId;
      if(rxBufferId < Dcm_Num_Of_Buffer_Config)
      {
        /*
         * Update the request data available in the buffer area of RxPduId
         * to the local pointer variable
         */
        LpRxPduIdData = Dcm_GaaBufferConfig[rxBufferId].pBufferArea;

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

        /* Transmit the negative response */
        Dcm_DslPduRTransmit();
      }
      else
      {
        /* Report to DET */
        #if(DCM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID,
        DCM_MAIN_FUNCTION_SID, DCM_E_INTERFACE_BUFFER_OVERFLOW);
        #endif
      }
    }
    else
    {
      /* Report to DET */
      #if(DCM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID,
      DCM_MAIN_FUNCTION_SID, DCM_E_INTERFACE_BUFFER_OVERFLOW);
      #endif
    }
  }

  /* Check if protocol preempt timer is started */
  else if(Dcm_TimerReqFlagStatus.ucPrtclPreemptTimer == DCM_TRUE)
  {
    SchM_Exit_Dcm_TimerProtection();
    /* Check whether the value of protocol preempt timer is ZERO */
    if(Dcm_GaaTimer[DCM_PROTOCOL_PREEMPT_TIMER] == DCM_ZERO)
    {
      uint8 LucIndex1;
      Dcm_StatusType LddStatusValue;
        
      /* Stop the protocol preempt timer */
      DCM_STOP_TIMER(DCM_PROTOCOL_PREEMPT_TIMER);
      Dcm_TimerReqFlagStatus.ucPrtclPreemptTimer = DCM_FALSE;

      /* Clear all the DSP flags */
      Dcm_DspStartProtocol();
        
      /* Clear the security timer */
      #if(DCM_DSP_SECURITY_SERVICE == STD_ON)
      Dcm_DspClearSecurityTimer();
      #endif
      /*  Invoke  DSP  internal  function  to  stop  the  current protocol */
        
      LucIndex1  =  0U; 
      LddStatusValue = DCM_E_OK;
      while((LucIndex1 < Dcm_Total_Num_Of_Callback_Request) &&
            (LddStatusValue != DCM_E_PROTOCOL_NOT_ALLOWED))
      {
        if((NULL_PTR != Dcm_GaaCbkReqServices[LucIndex1].pStartProtocolFun) && \
           (Dcm_GddRxPduId < Dcm_Num_Of_PduidTableConfig))
        {
          LddStatusValue = 
            Dcm_GaaCbkReqServices[LucIndex1].pStartProtocolFun(
                    Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId].ddProtocolId);
        }
        LucIndex1++;
      }

      /* sg.baek 022305 - refer to Bug #2203 in redmine */
      if((LddStatusValue == DCM_E_PROTOCOL_NOT_ALLOWED) || (LddStatusValue == E_NOT_OK))
      {
        #if(DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
          #if(DCM_DEV_ERROR_DETECT == STD_ON)
          Dcm_DslTxIncorrectCondition(DCM_MAIN_FUNCTION_SID);
          #else
          Dcm_DslTxIncorrectCondition();
          #endif
        #else
        /* Update the local variable to DCM_TRUE for clearing the status and
        to start the S3 server Timer */
        Dcm_DslStatusReset();
        #endif  
      }
      else
      {
        Dcm_GblNormalReq = DCM_TRUE;
        Dcm_DslCheckPrtclStatus();
      }     
 
    }
  }
  else
  {
    SchM_Exit_Dcm_TimerProtection();
  }
}

/*******************************************************************************
** Function Name        : Dcm_Internal_ChkPagedBufferTime                     **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : Dcm_Internal_ChkPagedBufferTime                     **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
static FUNC(void, DCM_CODE) Dcm_Internal_ChkPagedBufferTime (void)
{
  /* Check if paged buffer timer is started and the value is equal to ZERO */
  SchM_Enter_Dcm_TimerProtection();
  if((Dcm_TimerReqFlagStatus.ucPagedBufferTimer == DCM_TRUE) && 
     (Dcm_GaaTimer[DCM_PAGED_BUFFER_TIMER] == DCM_ZERO))
  {
     SchM_Exit_Dcm_TimerProtection();
       
    /* Report to DET */
    #if(DCM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID,
    DCM_MAIN_FUNCTION_SID, DCM_E_INTERFACE_TIMEOUT);
    #endif

    /* #if((DCM_PAGEDBUFFER_ENABLED == STD_ON) &&
                (DCM_READDTC_SUPPORT == STD_ON)) */
    /* Invoke the API to cancel paged buffer processing */
    Dcm_DspCancelPagedBufferProcessing();
    /* #endif */
    /* Stop the paged buffer timer */
    DCM_STOP_TIMER(DCM_PAGED_BUFFER_TIMER);

    SchM_Enter_Dcm_TimerProtection();
    Dcm_TimerReqFlagStatus.ucPagedBufferTimer = DCM_FALSE;
    SchM_Exit_Dcm_TimerProtection();
      
    /* Update the bit flag for response failed to TRUE */
    Dcm_TxRespStatus.ucRespFailed = DCM_TRUE;
    Dcm_TxRespStatus.ucPagedTrans = DCM_FALSE;
   
    /* refer XENON */
    /* Dcm_GblNormalReq = DCM_FALSE;
       Dcm_DslStatusReset(); */
  }
  else
  {
    SchM_Exit_Dcm_TimerProtection();
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_Internal_ChkS3ServerTime                        **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This function checks S3Server time in main function **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Internal_ChkS3ServerTime (void)
{
  SchM_Enter_Dcm_TimerProtection();
  /* Check if S3Server timer is started and the value is equal to ZERO */
  if((Dcm_TimerReqFlagStatus.ucS3Timer == DCM_TRUE) &&
    (Dcm_GaaTimer[DCM_S3SERVER_TIMER] == DCM_ZERO))
  {
    SchM_Exit_Dcm_TimerProtection();
    /* Update the current session to DCM_DEFAULT_SESSION
      and Lock the Security level */
    DslInternal_SetSesCtrlType(DCM_DEFAULT_SESSION);
    (void)SchM_Switch_Dcm_DcmDiagnosticSessionControl(DCM_DEFAULT_SESSION);

    #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
    Dcm_GblResOnPeriodicIdStatus = DCM_FALSE;
    #endif

    /* Inform ComM about the change in diagnostic session */
    (void)ComM_DCM_InactiveDiagnostic((NetworkHandleType)Dcm_GulChannelIdentifier);
    /* Stop the timer */
    DCM_STOP_TIMER(DCM_S3SERVER_TIMER);
    SchM_Enter_Dcm_TimerProtection();
    Dcm_TimerReqFlagStatus.ucS3Timer = DCM_FALSE;
    SchM_Exit_Dcm_TimerProtection();
  }
  else
  {
    SchM_Exit_Dcm_TimerProtection();
  }
}

/*******************************************************************************
** Function Name        : Dcm_Internal_ChkS3ServerTime                        **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This function checks control DTC settinging in      **
**                        main function                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#if((DCM_DSP_CONTROL_DTC_SERVICE == STD_ON) && \
     (DCM_MODE_RULE == STD_ON) && (DCM_DSP_CONTROL_DTC_CONFIGURED == STD_ON))
static FUNC(void, DCM_CODE) Dcm_Internal_ChkControlDTCSetting (void)
{
  boolean LblSearchResult;
  
  if(Dcm_GblDTCSettingDisabled == DCM_TRUE)
  {
    LblSearchResult = Dcm_DsdModeRuleCheck(Dcm_Dsp_Control_Dtc_Reenable_Mode_Rule);
  
    if(LblSearchResult == DCM_FALSE)
    {
      (void)Dem_EnableDTCSetting(DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_KIND_ALL_DTCS);
      (void)SchM_Switch_Dcm_DcmControlDTCSetting(ENABLEDTCSETTING);
      Dcm_GblDTCSettingDisabled = DCM_FALSE;
    }
  }
}


#endif

/*******************************************************************************
** Function Name        : Dcm_Internal_NegativeResponse                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function checks negative response in silent    **
**                        com                                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Internal_NegativeResponse (void)
{
  /* Silent com state - try Dcm_DslTransmit again to wait changing full com  */
  if(Dcm_GblNegavieResStatus == DCM_TRUE)
  {
    Dcm_DslTransmit(Dcm_GddDcmTxPduId, DCM_FALSE, DCM_FALSE);  
    Dcm_GblNegavieResStatus = (boolean)DCM_FALSE;
  }
}


/*******************************************************************************
** Function Name        : Dcm_Init                                            **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : The Initialization function will initialize all     **
**                        DCM global variables with the values of the         **
**                        configuration                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_GddCurrentLength, Dcm_DspSerPgStatus,           **
**                        Dcm_GddPIdRxPduId, Dcm_GblResOnPeriodicIdStatus     **
**                        Dcm_GaaCommMode, Dcm_GstMsgContext,                 **
**                        Dcm_GddCurrentSession, Dcm_GddOldSession,           **
**                        Dcm_TimerReqFlagStatus, Dcm_TxRespStatus            **
**                        Dcm_GpMsgContext, Dcm_GddNegRespError               **
**                        Dcm_GucFailedSecurityAccessCount,                   **
**                        Dcm_PrtclTxBufStatus, Dcm_GddSecurityLevel          **
**                        Dcm_GucPrtclPriority, Dcm_GaaProtclStatus           **
**                        Dcm_GddTxResponseLen, Dcm_GblNormalReq              **
**                        Dcm_GblInitStatus , Dcm_GblFirstCallToMain          **
**                        Dcm_GaaPeriodicID,                                  **
**                        Dcm_GucIDIndex,                                     **
**                        Function(s) invoked : Dcm_DspResetRoe,              **
**                                              Dcm_DspClearQueue             **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_Init
(P2CONST(Dcm_ConfigType, AUTOMATIC, DCM_APPL_CONST) ConfigPtr)
{
  /* P2VAR(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_DATA)LpPduIdTable; */
  /* P2CONST(Dcm_ProtocolConfig, AUTOMATIC, DCM_APPL_CONST)LpProtocolConfig; */
  uint8 LucCount;
  #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  uint16 LusIDIndex1;
  #endif

  uint8 LucTimerIndex;
  uint8 LucNetworkId;

  Dcm_ProgConditionsType LstProgConditions;

  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /* Initialize variable to store pending length of paged transmission */
  Dcm_GddCurrentLength = DCM_ZERO;
  #endif

  Dcm_DsdInternal_InitRequestContext();

  Dcm_TriggerCancelPendingOperation= DCM_FALSE;

  /*
  * Initialize variable that contains the bit field to store the
  * status of paged transmission in DSP
  */
  Dcm_DspSerPgStatus.ucDemDisableInvoked = DCM_FALSE;
  Dcm_DspSerPgStatus.ucLastPage = DCM_FALSE;
  Dcm_DspSerPgStatus.ucUpdatePageStarted = DCM_FALSE;
  Dcm_DspSerPgStatus.ucPagingStarted = DCM_FALSE;
  Dcm_DspSerPgStatus.ucFirstPage = DCM_FALSE;
  Dcm_DspSerPgStatus.ucPagingInMid = DCM_FALSE;
  Dcm_DspSerPgStatus.ucMultipleRecd = DCM_FALSE;
  Dcm_DspSerPgStatus.ucSecSeedReq = DCM_FALSE;

  /* Clear the response length flag */
  Dcm_GddTxResponseLen = DCM_ZERO;

  Dcm_GblReset = DCM_FALSE;
  Dcm_GblTheFirstRequest = DCM_TRUE;
  #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  /* Initialize variable to store the Periodic request RxPduId */
  Dcm_GddPIdRxPduId = DCM_ZERO;

  /* Initialize variable to store status of periodic transmission */
  Dcm_GblResOnPeriodicIdStatus = DCM_FALSE;

  #endif

  #if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
  #if(DCM_MAX_NO_OF_PRECONFIGURED_DID != DCM_ZERO)
  Dcm_GblNvmReadFlag = DCM_FALSE;
  #endif
  Dcm_GucRoeSTRTIndex = DCM_ZERO;

  /* Set the variable for ResponseOnEvent to Idle */
  Dcm_DspResetRoe();

  /* Initialize variable to store status of Clear All request */
  Dcm_GblRoeClearAll = DCM_FALSE;

  /*
  * Initialize variable for msgcontext Dcm_GpMsgContext with the
  * address of Dcm_GstMsgContext
  */
  Dcm_GpRoeMsgContext = &Dcm_GstRoeMsgContext;
  Dcm_GddStartRoeRxPduId = DCM_ZERO;
  #if(DCM_ROE_QUEUE_ENABLED == STD_ON)
  /* Initialize variable to store Queue storage ongoing status */
  Dcm_GblRoeQueueOngoing = DCM_FALSE;
  Dcm_DspClearQueue();
  #endif

  #endif

  /* Initialize variable to store current active communication mode */
  for(LucNetworkId = DCM_ZERO; LucNetworkId < Dcm_No_Of_Comm_Channels;
    LucNetworkId++)
  {
    Dcm_GaaCommMode[LucNetworkId] = DCM_NO_COMMUNICATION;
  }

  /* Initialize variable to store the current active session */
  Dcm_GddCurrentSession = DCM_DEFAULT_SESSION;
  Dcm_GulNumOfBytes = DCM_ZERO;

  /* Initialize variable to store old session */
  Dcm_GddOldSession = DCM_DEFAULT_SESSION;

  /* Initialize variable to store status of normal request */
  Dcm_GblNormalReq = DCM_FALSE;

  /* Update the flag to the first call to Dcm_main function */
  Dcm_GblFirstCallToMain = DCM_TRUE;
  Dcm_GblPosRspTransOnReset = DCM_FALSE;

  /* Initialize variable to store the number of response pending transmitted */
  Dcm_GusMaxNoOfRespPend = DCM_ZERO;

  /* Initialize the security level to locked */
  Dcm_GddSecurityLevel = DCM_SEC_LEV_LOCKED;

  /* Initialize local ProgConditionsType struct
                                        for initialization of PROG_CONDITIONS */
  LstProgConditions.TesterSourceAddr = (uint16)0x00;
  LstProgConditions.ProtocolId = (uint8)0x00;
  LstProgConditions.Sid = (uint8)0x00;
  LstProgConditions.SubFncId = (uint8)0x00;
  LstProgConditions.ReprogramingRequest = DCM_FALSE;
  LstProgConditions.ApplUpdated = DCM_FALSE;
  LstProgConditions.ResponseRequired = DCM_FALSE;
  LstProgConditions.SecLvInfo = DCM_SEC_LEV_LOCKED;

  (void)Dcm_GetProgConditions(&Dcm_GddProgConditions);
  /* #6985 Clear PROG_CONDITIONS */
  (void)Dcm_SetProgConditions(&LstProgConditions);
  
  if(Dcm_GddProgConditions.ApplUpdated == DCM_TRUE)
  {
    (void)BswM_Dcm_ApplicationUpdated();
    Dcm_GddProgConditions.ApplUpdated = DCM_FALSE;
  }
  
  #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  for(LusIDIndex1 = DCM_ZERO; LusIDIndex1 < Dcm_Dsp_Max_Periodic_DID;
    LusIDIndex1++)
  {
    Dcm_GaaPeriodicID[LusIDIndex1][DCM_ZERO] = DCM_ZERO;
  }
  Dcm_GucIDIndex = DCM_ZERO;
  #endif

  /*
  * Initialize variable that contains bit field to store the status of
  * timers
  */
  Dcm_TimerReqFlagStatus.ucRoeInterMsgTimer = DCM_FALSE;
  Dcm_TimerReqFlagStatus.ucP2MaxTimer = DCM_FALSE;
  Dcm_TimerReqFlagStatus.ucS3Timer = DCM_FALSE;
  Dcm_TimerReqFlagStatus.ucPagedBufferTimer = DCM_FALSE;
  Dcm_TimerReqFlagStatus.ucPrtclPreemptTimer = DCM_FALSE;
  Dcm_TimerReqFlagStatus.ucSecLevTimer = DCM_FALSE;

  /* Initialize all timer values to ZERO */
  for(LucTimerIndex = DCM_ZERO; LucTimerIndex < DCM_SIX; LucTimerIndex++)
  {
    Dcm_GaaTimer[LucTimerIndex] = DCM_ZERO;
  }

  /*
  * Initialize variable for msgcontext Dcm_GstMsgContext
  */
  Dcm_GstMsgContext.reqData = &Dcm_GaaBufferArea[0];
  Dcm_GstMsgContext.reqDataLen = (Dcm_MsgLenType)0x00;
  Dcm_GstMsgContext.resData = &Dcm_GaaBufferArea[0];
  Dcm_GstMsgContext.resDataLen = (Dcm_MsgLenType)0x00;
  Dcm_GstMsgContext.msgAddInfo.reqType = (uint8)0x00;
  Dcm_GstMsgContext.msgAddInfo.suppressPosResponse = (uint8)0x00;
  Dcm_GstMsgContext.msgAddInfo.cancelOperation = (uint8)0x00;
  Dcm_GstMsgContext.resMaxDataLen = (Dcm_MsgLenType)0x00;
  Dcm_GstMsgContext.idContext = (Dcm_IdContextType)0x00;
  Dcm_GstMsgContext.dcmRxPduId = (PduIdType)0x00;

  #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  Dcm_GpPerMsgContext = &Dcm_GstPerMsgContext;
  #endif

  /*
  * Initialize variable that contains the bit field to store the
  * status of transmission
  */
  Dcm_TxRespStatus.ucNormResponse = DCM_FALSE;
  Dcm_TxRespStatus.ucNegResp = DCM_FALSE;
  Dcm_TxRespStatus.ucRespFailed = DCM_FALSE;
  Dcm_TxRespStatus.ucRespPending = DCM_FALSE;
  Dcm_TxRespStatus.ucFirstPageTrans = DCM_FALSE;
  Dcm_TxRespStatus.ucPagedTrans = DCM_FALSE;
  Dcm_TxRespStatus.ucFailedInd = DCM_FALSE;
  Dcm_TxRespStatus.ucDslPagedTrans = DCM_FALSE;  

  /* Initialize variable to store the temporarily in DSP */
  Dcm_GucFailedSecurityAccessCount = DCM_ZERO;

  /* Initialize variable for the negative response error */
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;

  /* Initialize variable to store the subfunction of the service */
  Dcm_GucSubFunction = DCM_ZERO;

  /* The bit flag for protocol status and provide transmit buffer is
    made FALSE */
  Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus = DCM_FALSE;
  Dcm_PrtclTxBufStatus.ucClearDTCStatus = DCM_FALSE;
  Dcm_PrtclTxBufStatus.ucBufferProvided = DCM_FALSE;
  Dcm_PrtclTxBufStatus.ReportNumOfDtc = DCM_FALSE;
  Dcm_PrtclTxBufStatus.ucPeriodicIdStatus = DCM_FALSE;
  Dcm_PrtclTxBufStatus.ucReportOBDDtc = DCM_FALSE;
  Dcm_PrtclTxBufStatus.ucCopyTxRejected = DCM_FALSE;

  /* Set the initial protocol priority to least value */
  Dcm_GucPrtclPriority = DCM_ZERO;

  /* FIXME */
  Dcm_GblRspPenOnBtlTrans = DCM_FALSE; 
  #if ((DCM_DSP_DIAG_SESSION_SERVICE == STD_ON) || (DCM_DSP_STOP_DIAG_SESSION_SERVICE== STD_ON))
  Dcm_DiagSessionState.sessionTableIndex = 0U;
  Dcm_DiagSessionState.sendPendingResp = DCM_FALSE;
  #endif
  
  #if((DCM_LINK_CONTROL_SERVICE == STD_ON) || \
      (DCM_DSP_DIAG_SESSION_SERVICE == STD_ON))
  Dcm_GblExecuteECUReset = DCM_FALSE;
  #endif

  #if(DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON)
  Dcm_GucComCtrlMode = DCM_ENABLE_RX_TX_NORM_NM;
  #endif

  /* Clear the Status of the Protocol Priority array */
  Dcm_GaaProtclStatus[DCM_ZERO] = DCM_ZERO;

  Dcm_GblSendResponse = DCM_FALSE;
  Dcm_GblPduRTransmitResponse = DCM_FALSE;

  /* sg.baek 022305 - Task #2163 in redmine */
  Dcm_GblReceiveRquest = DCM_FALSE;

  Dcm_GblNegavieResStatus = DCM_FALSE;

  for(LucCount = DCM_ZERO; LucCount < Dcm_Num_Of_PduidTableConfig; LucCount++)
  {
    /* modified by youngjin.yun */
    if(NULL_PTR != Dcm_GaaPduIdTableConfig[LucCount].pPduIdStatus)
    {
      *(Dcm_GaaPduIdTableConfig[LucCount].pPduIdStatus) = DCM_ZERO;
    }
    Dcm_GaaPduIdTableConfig[LucCount].ucReceiveStatus = DCM_RECEPTION_IDLE;
  }

  Dcm_PrtclTxBufStatus.ucProtclStatus = DCM_FALSE;
  for(LucCount = DCM_ZERO; LucCount< Dcm_Num_Protocol_Configd; LucCount++)
  {
    /* modified by youngjin.yun */
    if(NULL_PTR != Dcm_GaaProtocolConfig[LucCount].pProtocolStatus)
    {
      *(Dcm_GaaProtocolConfig[LucCount].pProtocolStatus) = DCM_ZERO;
    }
  }

  #if(DCM_TRANSFER_DATA_SERVICE == STD_ON)
  Dcm_GddTransDataPosRes = DCM_FALSE;
  #endif

  #if(DCM_DSP_SECURITY_SERVICE == STD_ON)
  Dcm_GucSecurSequChk = 0u;
  #if (DCM_SECURITY_CRL_ENABLE == STD_ON)
  Dcm_GaaCRLLegnth = 0U;
  #endif
  #endif

  DCM_UNUSED_PTR(ConfigPtr);

  /* Update the module status has Initialized */
  Dcm_GblInitStatus = DCM_INITIALISED;
}

/*******************************************************************************
** Function Name        : Dcm_GetVin                                          **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : Function to get the VIN (as defined in SAE J1979-DA)**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Data                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GblInitStatus              **
**                        Function(s) invoked : (void)Det_ReportError         **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE)Dcm_GetVin
(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{

  Std_ReturnType LddReturnValue = E_NOT_OK;
  
  #if (DCM_DEV_ERROR_DETECT == STD_ON)
  /* Check whether the module is Initialized */
  if (Dcm_GblInitStatus == DCM_UNINITIALISED)
  {
    /* Report to DET */
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID,
    DCM_GET_VIN_SID, DCM_E_UNINIT);
  }

  /* Check if pointer passed is NULL */
  else if(Data == NULL_PTR)
  {
    /* Report Error to DET */
    (void)Det_ReportError(DCM_MODULE_ID, DCM_INSTANCE_ID,
      DCM_GET_VIN_SID, DCM_E_PARAM_POINTER);
  }
  else
  #endif
  {

    #ifdef DCM_VIN_DID
    uint16 aDataIdentifier;
    boolean searchResult;
    uint16 aDidIndex;
	
    aDataIdentifier = DCM_VIN_DID;

    /* Check if the DID from the request is supported */
    searchResult = Dcm_IDSearch(DCM_GET_DID, aDataIdentifier, &aDidIndex);
  
    if((searchResult == DCM_TRUE) && (DCM_NUM_OF_DIDPARACONFIG > aDidIndex))
    {
      P2VAR(Dcm_DcmDspSignalconfig, AUTOMATIC, DCM_APPL_DATA) 
        pSignal = &Dcm_GaaDIDParaConfig[aDidIndex].pDcmDspSignal[0];

      if (NULL_PTR != pSignal->pDcmDspData)
      {

        P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST)
          pDataElm = pSignal->pDcmDspData; 

        if (NULL_PTR != pDataElm->pReadDataSync)
        {
          LddReturnValue = pDataElm->pReadDataSync(Data);
        }
      
      }            
      
    }

    #endif
  }

  return LddReturnValue;
}


/*******************************************************************************
** Function Name        : Dcm_GetVersionInfo                                  **
**                                                                            **
** Service ID           : 0x24                                                **
**                                                                            **
** Description          : This service returns the version information of     **
**                        this module                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : versioninfo                                         **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GblInitStatus              **
**                        Function(s) invoked : (void)Det_ReportError         **
**                                                                            **
*******************************************************************************/
#if(DCM_VERSION_INFO_API == STD_ON)
FUNC(void, DCM_CODE)Dcm_GetVersionInfo
(P2VAR(Std_VersionInfoType, AUTOMATIC, DCM_APPL_DATA) versioninfo)
{
  #if (DCM_DEV_ERROR_DETECT == STD_ON)

  /* Check whether the module is Initialized */
  if (Dcm_GblInitStatus == DCM_UNINITIALISED)
  {
    /* Report to DET */
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID,
    DCM_GET_VERSION_INFO_SID, DCM_E_UNINIT);
  }

  /* Check if pointer passed is NULL */
  else if(versioninfo == NULL_PTR)
  {
    /* Report Error to DET */
    (void)Det_ReportError(DCM_MODULE_ID, DCM_INSTANCE_ID,
      DCM_GET_VERSION_INFO_SID, DCM_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* Copy the vendor Id */
    versioninfo->vendorID = DCM_VENDOR_ID;

    /* Copy the module Id */
    versioninfo->moduleID = DCM_MODULE_ID;

    /* Copy Software Major Version */
    versioninfo->sw_major_version = DCM_SW_MAJOR_VERSION;

    /* Copy Software Minor Version */
    versioninfo->sw_minor_version = DCM_SW_MINOR_VERSION;

    /* Copy Software Patch Version */
    versioninfo->sw_patch_version = DCM_SW_PATCH_VERSION;
  }
}
#endif /* (DCM_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
** Function Name        : Dcm_GetSesCtrlType                                  **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : This API provides the active session level value.   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : SesCtrlType                                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this API.  **
**                                                                            **
** Remarks              : Global Variable(s)     : Dcm_GblInitStatus,         **
**                        Dcm_GddCurrentSession                               **
**                        Function(s) invoked    : (void)Det_ReportError      **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSesCtrlType
(P2VAR(Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA) SesCtrlType)
{
  Std_ReturnType LddReturnValue;
  LddReturnValue = E_OK;
  /* Check if the pre compile DCM_DEV_ERROR_DETECT option is enabled */
  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  /* Check whether the module is Initialized */
  if (Dcm_GblInitStatus == DCM_UNINITIALISED)
  {
    /* Report to DET */
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID,
    DCM_GET_SES_CTRL_TYPE_SID, DCM_E_UNINIT);
    LddReturnValue = E_NOT_OK;
  }
  /* Validate pointer */
  if (SesCtrlType == NULL_PTR)
  {
    /* Report to DET */
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID,
    DCM_GET_SES_CTRL_TYPE_SID, DCM_E_PARAM_POINTER);
    LddReturnValue = E_NOT_OK;
  }
  else
  #endif
  {
    /* Update the return value with the current Session type */
    *SesCtrlType = Dcm_GddCurrentSession;
  }
  return(LddReturnValue);
}

/*******************************************************************************
** Function Name        : DslInternal_SetSesCtrlType                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API is to set the session level in the Dcm     **
**                        module                                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LddSesCtrlType                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dcm_GddOldSession, Dcm_GddCurrentSession,           **
**                        Dcm_GddSecurityLevel, Dcm_GblResOnPeriodicIdStatus  **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) DslInternal_SetSesCtrlType
  (Dcm_SesCtrlType LddSesCtrlType)
{
  #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  boolean resetPeriodicSched = DCM_FALSE;
  #endif
  
  #if((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
      ((DCM_ROE_INIT_ON_DSC == STD_ON) || (DCM_ROE_QUEUE_ENABLED == STD_ON)))       
  boolean resetROE = DCM_FALSE;
  #endif
  #if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
  boolean resetIOControl = DCM_FALSE;
  #endif
  
  #if (DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON)
  boolean resetCommState = DCM_FALSE;
  #endif
  
  #if(DCM_DSP_CONTROL_DTC_SERVICE == STD_ON)  
  boolean resetDTCSetting = DCM_FALSE;
  #endif

  #if(DCM_DSP_SECURITY_SERVICE == STD_ON)
  boolean resetSecurity = DCM_FALSE;
  #endif

  #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  uint8 LusCount;
  #endif

  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the DCM Module is not Initialized */
  if(Dcm_GblInitStatus == DCM_UNINITIALISED)
  {
    /* Report Error to DET */
    (void)Det_ReportError(DCM_MODULE_ID, DCM_INSTANCE_ID,
      DCM_VARIANT_FUNC_SID, DCM_E_UNINIT);
  }
  else
  #endif
  {
    /* Update the old session with the current session */
    Dcm_GddOldSession = Dcm_GddCurrentSession;
    /* Update the Current with the passes parameter LddSesCtrlType */
    Dcm_GddCurrentSession = LddSesCtrlType;
    /* Lock the Security level */
  
  
    /* Refer to Figure 4-1 - Server diagnostic session state diagram of ES95486 */
    if (CHECK_DEFAULT_SESSION(Dcm_GddOldSession))
    {
      /* 1) default->default :
       *  server shall  re-initialize  the  defaultSession  completely.  
       *  The  server  shall  reset  all activated/initiated/changed settings/
       *  controls during the activated session. 
       *      
       *  Note: This does not include long term changes programmed 
       *  into non-volatile memory.  
       */
      if (CHECK_DEFAULT_SESSION(LddSesCtrlType))
      {
        #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
        resetPeriodicSched = DCM_TRUE;
        #endif
        #if((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
        ((DCM_ROE_INIT_ON_DSC == STD_ON) || (DCM_ROE_QUEUE_ENABLED == STD_ON)))       
        resetROE = DCM_TRUE;
        #endif
        #if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
        resetIOControl = DCM_TRUE;
        #endif
        #if (DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON)
        resetCommState = DCM_TRUE;
        #endif
        #if(DCM_DSP_CONTROL_DTC_SERVICE == STD_ON)  
        resetDTCSetting = DCM_TRUE;
        #endif
        #if(DCM_DSP_SECURITY_SERVICE == STD_ON)
        resetSecurity = DCM_TRUE;
        #endif
      }
      /* 2) default-> any other session
       *  -. stop ROE
       */
      else 
      {
        #if((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
        ((DCM_ROE_INIT_ON_DSC == STD_ON) || (DCM_ROE_QUEUE_ENABLED == STD_ON)))       
        resetROE = DCM_TRUE;
        #endif
        #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)    
        resetPeriodicSched = DCM_FALSE;
        #endif
        #if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
        resetIOControl = DCM_FALSE;
        #endif
        #if (DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON)
        resetCommState = DCM_FALSE;
        #endif
        #if(DCM_DSP_CONTROL_DTC_SERVICE == STD_ON)  
        resetDTCSetting = DCM_FALSE;
        #endif
        #if(DCM_DSP_SECURITY_SERVICE == STD_ON)
        resetSecurity = DCM_FALSE;
        #endif
      }
    }
    /* any other session(non-default session) */
    else
    {
      /* 3) any other session->any other session(or same session). The sever shall be
       * -. initialize  the  diagnostic  session
       * -. stop ROE
       * -. security relocked.
       * -. remain periodic scheduler
       * -. remain Communication state
       * -. remain ControlDTCSetting
       */
      if (CHECK_NONDEFAULT_SESSION(LddSesCtrlType))
      {
        #if((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
        ((DCM_ROE_INIT_ON_DSC == STD_ON) || (DCM_ROE_QUEUE_ENABLED == STD_ON)))       
        resetROE = DCM_TRUE;
        #endif
        #if(DCM_DSP_SECURITY_SERVICE == STD_ON)
        /* polyspace +13 MISRA-C3:2.1 [Justified:Low] "Not a defect" */
        /* polyspace +2 MISRA-C3:14.3 [Justified:Low] "Not a defect" */
        #if (DCM_REMAIN_UNLOCK_CONDITION == STD_ON)
        if (Dcm_GddOldSession == DCM_EXTENDED_DIAGNOSTIC_SESSION)
        {
          resetSecurity = DCM_FALSE;
        }
        else
        {
          resetSecurity = DCM_TRUE;
        }
        #else
        resetSecurity = DCM_TRUE;
        #endif
        
        #endif
        #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
        resetPeriodicSched = DCM_FALSE;
        #endif
        #if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
        resetIOControl = DCM_FALSE;
        #endif
        #if (DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON)
        resetCommState = DCM_FALSE;
        #endif
        #if(DCM_DSP_CONTROL_DTC_SERVICE == STD_ON)  
        resetDTCSetting = DCM_FALSE;
        #endif
      }
      /* 4) any other session -> default session. The server shall
       * -. stop ROE.
       * -. security relocked.
       * -. stop periodic scheduler 
       * -. reset CommunicationControl state
       * -. reset ControlDTCSetting 
       * -. reset all activated/initiated/changed settings/controls 
       *    during the activated session. 
       *
       * Note: This does not include long 
       *   term changes programmed into non-volatile memory. 
       */
      else 
      {
        #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
        resetPeriodicSched = DCM_TRUE;
        #endif
        #if((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
        ((DCM_ROE_INIT_ON_DSC == STD_ON) || (DCM_ROE_QUEUE_ENABLED == STD_ON)))       
        resetROE = DCM_FALSE; /*<-FIXME */
        #endif
  
        #if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
        resetIOControl = DCM_TRUE;
        #endif
        #if (DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON)
        resetCommState = DCM_TRUE;
        #endif
        #if(DCM_DSP_CONTROL_DTC_SERVICE == STD_ON)  
        resetDTCSetting = DCM_TRUE;
        #endif
        #if(DCM_DSP_SECURITY_SERVICE == STD_ON)
        resetSecurity = DCM_TRUE;
        #endif
  
        /* FIXME : I don't know that */
        /* [SWS_Dcm_00902]  All RoeEvents which have been in "ROE started"
         * state when leaving the default session shall change back into 
         * "ROE started" state when (re-)entering the default session. */
        #if((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
            ((DCM_ROE_INIT_ON_DSC == STD_ON) || \
             (DCM_ROE_QUEUE_ENABLED == STD_ON)))
        Dcm_DspEnableRoe();
        #endif
      }
    }
  
    /* TODO : Need to verify whether security failed count/canceled operation is reset or not*/
    /* 
     * SecurityAccess Level
     */
    #if(DCM_DSP_SECURITY_SERVICE == STD_ON)
    if (resetSecurity == DCM_TRUE)
    {
      if ((Dcm_DspServiceProcessingSts.ucSecSeedReqPending == DCM_TRUE) || 
         (Dcm_DspServiceProcessingSts.ucSecCompareKeyReqPending == DCM_TRUE))
      {
        if (Dcm_GucDspStIndex < Dcm_Num_Of_Security_Level_Config)
        {
          P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;
          P2CONST(Dcm_SecurityLevConfigType, AUTOMATIC, DCM_APPL_CONST) LpSecData;
          Dcm_NegativeResponseCodeType LddErrorCode;
          uint8 LucSecLvl;

          /* polyspace<RTE: NIV : Not a defect : No Action Planned > initialized variable */
          LucSecLvl = Dcm_GstMsgContext.reqData[DCM_ZERO] & DCM_SUBFUNCTION_MASK;
          LpSecData = &Dcm_GaaSecurityLevConfig[Dcm_GucDspStIndex];
          LpReqResData = Dcm_GstMsgContext.resData;
          (void)Dcm_DspInternal_DcmSecurityAccess(DCM_CANCEL, LpSecData, LpReqResData, &LddErrorCode, LucSecLvl);
          Dcm_DspServiceProcessingSts.ucSecSeedReqPending = DCM_FALSE;
          Dcm_DspServiceProcessingSts.ucSecCompareKeyReqPending = DCM_FALSE;
        }
        else
        {
          DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID,DCM_E_PARAM);        
        }
      }
  
      Dcm_GucSecurSequChk = 0u;
  
      #if((DCM_STANDARD_SUPPORT != DCM_ES96590_SUPPORT) && (DCM_STANDARD_SUPPORT != DCM_QZN04_SUPPORT))
      Dcm_GucFailedSecurityAccessCount = DCM_ZERO;
      /* Set global bit flag indicating the security seed request to FALSE */

      #endif

      Dcm_DspSerPgStatus.ucSecSeedReq = DCM_FALSE;
      Dcm_GddSecurityLevel = DCM_SEC_LEV_LOCKED;
    }
    #endif    
    /* 
     * Enable DTC Setting 
     */
    #if(DCM_DSP_CONTROL_DTC_SERVICE == STD_ON)  
    if ((resetDTCSetting == DCM_TRUE) && 
         (Dcm_GblDTCSettingDisabled == DCM_TRUE))
    {
      (void)Dem_EnableDTCSetting(DEM_DTC_GROUP_ALL_DTCS,
                              DEM_DTC_KIND_ALL_DTCS);
      (void)SchM_Switch_Dcm_DcmControlDTCSetting(ENABLEDTCSETTING);
      
      Dcm_GblDTCSettingDisabled = DCM_FALSE;
    }
    #endif

    /* 
     * Communucation State
     */
    #if (DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON)        
    if (resetCommState == DCM_TRUE)
    {
      uint8 LucLoopcount;
      
      Dcm_GucComCtrlMode = DCM_ENABLE_RX_TX_NORM_NM;
  
      for(LucLoopcount = DCM_ZERO;LucLoopcount < Dcm_Total_Num_Of_All_Channel;
        LucLoopcount++)
      {
        if(NULL_PTR != Dcm_GaaAllCommControlConfig[LucLoopcount].pSchMSwitchAllCommModeFunc)
        {
          Dcm_GaaAllCommControlConfig[LucLoopcount].pSchMSwitchAllCommModeFunc(Dcm_GucComCtrlMode);
          (void)BswM_Dcm_CommunicationMode_CurrentState(
            Dcm_GaaAllCommControlConfig[LucLoopcount].ucComChannelRef,
            Dcm_GucComCtrlMode);
        }
      }
    }
    #endif 
  
    /* 
     * ResponseOnEvent
     */
    #if((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
         ((DCM_ROE_INIT_ON_DSC == STD_ON) ||\
         (DCM_ROE_QUEUE_ENABLED == STD_ON)))
    if (resetROE == DCM_TRUE)
    {
      Dcm_DspDisableRoe();
    }
    #endif
  
    /* 
     * Periodic sheduler
     */
    #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
    if (resetPeriodicSched == DCM_TRUE)
    {
      Dcm_GblResOnPeriodicIdStatus = DCM_FALSE;
      for(LusCount = 0U; LusCount <
            Dcm_Dsp_Max_Periodic_DID_Scheduled; LusCount++)
      {
          /* Remove the periodic DID from the global array */
          Dcm_GaaPeriodicID[LusCount][0] = 0U;
          Dcm_GaaPeriodicID[LusCount][1] = 0U;
      }
    }
    #endif
  
    /* 
     * IOControl 
     */
    #if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
    if(resetIOControl == DCM_TRUE)
    {
      Dcm_DspReturnControlToEcu();
    }
    #endif
  }
}

/*******************************************************************************
** Function Name        : Dcm_ResetToDefaultSession                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API is to used to reset the session level in   **
**                        the DCM module                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dcm_GddOldSession, Dcm_GddCurrentSession,           **
**                        Dcm_GddSecurityLevel, Dcm_GblResOnPeriodicIdStatus  **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
/* Fixed by youngjin.yun, 2014-12-29, Add return type */
FUNC(Std_ReturnType, DCM_CODE) Dcm_ResetToDefaultSession(void)
{
  /* Update the old session with the current session */
  Dcm_GddOldSession = Dcm_GddCurrentSession;
  /* Update the Current with the default session */
  Dcm_GddCurrentSession = DCM_DEFAULT_SESSION;
  /* Lock the Security level */
  Dcm_GddSecurityLevel = DCM_SEC_LEV_LOCKED;
  #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  Dcm_GblResOnPeriodicIdStatus = DCM_FALSE;
  #endif

  if (CHECK_NONDEFAULT_SESSION(Dcm_GddOldSession))
  {
    (void)SchM_Switch_Dcm_DcmDiagnosticSessionControl(DCM_DEFAULT_SESSION);
  }
  
  /* This value is always returned. */
  return E_OK;
}

/*******************************************************************************
** Function Name        : Dcm_GetSecurityLevel                                **
**                                                                            **
** Service ID           : 0x0D                                                **
**                                                                            **
** Description          : This API is used to get the active security level   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this API.  **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GblInitStatus,             **
**                        Dcm_GddSecurityLevel                                **
**                        Function(s) invoked : (void)Det_ReportError,        **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSecurityLevel
  (P2VAR(Dcm_SecLevelType, AUTOMATIC, DCM_APPL_DATA) SecLevel)
{
  Std_ReturnType LddReturnValue;
  /* Update Return value as E_NOT_OK */
  LddReturnValue = E_OK;

  /* Check if the pre compile option DCM_DEV_ERROR_DETECT is enabled */
  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  /* Check whether the module is Initialized */
  if (Dcm_GblInitStatus == DCM_UNINITIALISED)
  {
    /* Report to DET */
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID,
    DCM_GET_SECURITY_LEVEL_SID, DCM_E_UNINIT);
    /* Update Return value as E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  }

  /* Validate pointer */
  if (SecLevel == NULL_PTR)
  {
    /* Report to DET */
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID,
    DCM_GET_SECURITY_LEVEL_SID, DCM_E_PARAM_POINTER);
    /* Update Return value as E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  }
  else
  #endif /* (DCM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Update the current security level in the variable for return value */
    *SecLevel = Dcm_GddSecurityLevel;
  }

  /*
  * Return the current security level if DET is not reported else return
  * DCM_SEC_LEV_LOCKED
  */
  return(LddReturnValue);
}

/*******************************************************************************
** Function Name        : DslInternal_SetSecurityLevel                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API is to change the current active security   **
**                        level with the passed security level                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : SecurityLevel                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this API.  **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddSecurityLevel           **
**                        Function(s) invoked : NA                            **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) DslInternal_SetSecurityLevel
  (Dcm_SecLevelType SecurityLevel)
{
  /* Update the current security level */
  Dcm_GddSecurityLevel =  SecurityLevel;
}

/*******************************************************************************
** Function Name        : Dcm_GetActiveProtocol                               **
**                                                                            **
** Service ID           : 0x0F                                                **
**                                                                            **
** Description          : This API provides the current active protocol Id    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ActiveProtocol                                      **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this API.  **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GblInitStatus,             **
**                        Dcm_GddProtocolId                                   **
**                        Function(s) invoked : (void)Det_ReportError         **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetActiveProtocol
  (P2VAR(Dcm_ProtocolType, AUTOMATIC, DCM_APPL_DATA)ActiveProtocol)
{
  Std_ReturnType LddReturnType;

  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  /* Check whether the module is Initialized */
  if (Dcm_GblInitStatus == DCM_UNINITIALISED)
  {
    /* Report to DET */
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID,
      DCM_GET_ACTIVE_PROTOCOL_SID, DCM_E_UNINIT);
    LddReturnType = E_NOT_OK;
  }
  /* Validate pointer */
  else if (ActiveProtocol == NULL_PTR)
  {
    /* Report to DET */
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID,
      DCM_GET_ACTIVE_PROTOCOL_SID, DCM_E_PARAM_POINTER);
    LddReturnType = E_NOT_OK;
  }
  else
  #endif /* (DCM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Return the Protocol Id value which is currently active */
      *ActiveProtocol = Dcm_GddProtocolId;
    LddReturnType = E_OK;
   }
  return LddReturnType;
}

/*******************************************************************************
** Function Name       : Dcm_MainFunction                                     **
**                                                                            **
** Service ID          : 0x25                                                 **
**                                                                            **
** Description         : This service is used for processing the tasks of     **
**                        the main loop. It is called periodically as cyclic  **
**                        task by the software system. In this function all   **
**                        scheduled functions will be integrated              **
**                                                                            **
** Sync/Async          : Synchronous                                          **
**                                                                            **
** Re-entrancy         : Non-Reentrant                                        **
**                                                                            **
** Input Parameters    : None                                                 **
**                                                                            **
** InOut parameter     : None                                                 **
**                                                                            **
** Output Parameters   : None                                                 **
**                                                                            **
** Return parameter    : void                                                 **
**                                                                            **
** Preconditions       : Dcm_Init should be called before calling this API.   **
**                                                                            **
** Remarks             : Global Variable(s) : Dcm_GblInitStatus,              **
**                       Dcm_GaaTimer, Dcm_TxRespStatus                       **
**                       Dcm_GaaPduIdTableConfig, Dcm_GaaBufferConfig         **
**                       Dcm_GpMsgContext, Dcm_GblResOnPeriodicIdStatus       **
**                       Dcm_DspSerPgStatus,                                  **
**                       Dcm_GaaResponseBuf,                                  **
**                       Dcm_GblNormalReq , Dcm_GblFirstCallToMain            **
**                       Dcm_GddProgConditions ,Dcm_GulChannelIdentifier      **
**                       Dcm_GddDcmTxPduId , Dcm_GblExecuteECUReset           **
**                       Dcm_GusMaxNoOfRespPend,                              **
**                       Dcm_GblFaultDetcetionCounter, Dcm_GddRxPduId         **
**                       Dcm_GaaCbkReqServices                                **
**                       Function(s) invoked :                                **
**                       ComM_DCM_InactiveDiagnostic,                         **
**                       Dcm_DslPduRTransmit,                                 **
**                       Dcm_DslCheckPrtclStatus, Dcm_PrtclTxBufStatus        **
**                       (void)Det_ReportError,                               **
**                       Dcm_DspProcessUpdatePage,                            **
**                       Dcm_DspCancelPagedBufferProcessing                   **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_MainFunction(void)
{
  /* Check whether the module is Initialized */
  if (Dcm_GblInitStatus != DCM_UNINITIALISED)
  {

    /* process sequence
     *
     * 1. P2Server timing : if P2Service timer is expired, Dcm shall response the 0x78 immediately
     * 2. S3Server timimg : if S3 Service timer is expired, Dcm shall be initialized according to specification
     * 3. Process of the pended request 
     * 4. Tx transmission: response of normal request or pended request
     * 5. New request's process
     */
     
    /* This function have the highest priority in Dcm_MainFunction(). */
    Dcm_Internal_UpdateTime();

    /* P2 Server time : 0x78 */
    Dcm_Internal_ChkResponseTime();

    #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
    Dcm_Internal_ChkPagedBufferTime();
    #endif

    /* if S3 Service timing timout, session will be default session */
    Dcm_Internal_ChkS3ServerTime();


    /* Also consider paged services UDS + OBD remaining */
    #if ((DCM_PAGEDBUFFER_ENABLED == STD_ON) && \
        ((DCM_READDTC_SUPPORT == STD_ON) || \
        (DCM_OBD_SUPPORT == STD_ON) || \
        (DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON)))
    /* This function shoud be above Dcm_Internal_ProcessTxRx(). */
    Dcm_Internal_ChkUpdatePage();
    #endif

    /* To process pending services (include Tx transmission) */ 
    /* This function shoud be above Rx request  */
    Dcm_Internal_ServicesPending();

    /* Silent com mode - try Dcm_DslTransmit again to wait changing full com  */
    Dcm_Internal_NegativeResponse();
  
    /* Tx shall be processed before Reqeust is processed */

    Dcm_Internal_TransmitResponse();
    
    Dcm_Internal_processRequest(); 
    
    /* Dcm_Internal_ProcessTxRx(); */
  
    #if((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
         (DCM_MAX_NO_OF_PRECONFIGURED_DID != DCM_ZERO))
    Dcm_Internal_ResponseOnEvent();
    #endif

    Dcm_Internal_GblFirstCallToMain();

    /* Fixed by youngjin.yun  for preventing multiple activation task */
    #if((DCM_LINK_CONTROL_SERVICE == STD_ON) || \
      (DCM_DSP_DIAG_SESSION_SERVICE == STD_ON) || \
      (DCM_ECURESET_SERVICE == STD_ON))
    if(Dcm_GblExecuteECUReset == DCM_TRUE)
    {
      (void)SchM_Switch_Dcm_DcmEcuReset(EXECUTE);
      Dcm_GblExecuteECUReset = DCM_FALSE;
    }
    #endif

    #if((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) && \
    (DCM_MODE_RULE == STD_ON) && (DCM_DSP_COMM_CONTROL_CONFIGURED == STD_ON))
    Dcm_Internal_ChkCommunicationMode();
    #endif

    #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
    Dcm_PERIODIC_DID_MainFunction();
    #endif


  
    /* This routine shall be execute at the end of mainfunction
      modified by youngjin.yun*/
    #if((DCM_DSP_CONTROL_DTC_SERVICE == STD_ON) && \
    (DCM_MODE_RULE == STD_ON) && (DCM_DSP_CONTROL_DTC_CONFIGURED == STD_ON))
    Dcm_Internal_ChkControlDTCSetting();
    #endif    
  }
  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  else
  {/* Report to DET */
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID,
    DCM_MAIN_FUNCTION_SID, DCM_E_UNINIT);
  }
  #endif /* (DCM_DEV_ERROR_DETECT == STD_ON) */
}

/*******************************************************************************
** Function Name        : Dcm_SecurityAccessMainFunction                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used for processing the tasks of    **
**                        the main loop for Security Access service.          **
**                        It is called periodically as cyclic task by the     **
**                        software system.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddNegRespError,           **
**                        Dcm_DspSerPgStatus                                  **
**                        Dcm_GaaSecurityLevConfig , Dcm_GucDspStIndex        **
**                        Dcm_GpMsgContext , Dcm_DspServiceProcessingSts      **
**                        Dcm_GucFailedSecurityAccessCount ,                  **
**                        Dcm_GddNegRespError                                 **
**                        Dcm_GaaTimer , Dcm_GaaSeed                          **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if(DCM_DSP_SECURITY_SERVICE == STD_ON)
static FUNC(void, DCM_CODE) Dcm_SecurityAccessMainFunction (void)
{
  P2CONST(Dcm_SecurityLevConfigType, AUTOMATIC, DCM_APPL_CONST)LpSecData;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)LpReqResData;
  Dcm_NegativeResponseCodeType LddErrorCode;
  uint32 LulLoopCnt;
  uint32 LulLength;
  uint8 LucSecLvl;

  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the DCM Module is not Initialized */
  if (Dcm_GblInitStatus == DCM_UNINITIALISED)
  {
    DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_UNINIT);
  }  
  else if (Dcm_GucDspStIndex >= Dcm_Num_Of_Security_Level_Config)
  {
    DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM); 
  }     
  else if((NULL_PTR == Dcm_GstMsgContext.reqData) || 
          (NULL_PTR == Dcm_GstMsgContext.resData))
  {
      DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM_POINTER);
  }
  else
  #endif
  {
    if((Dcm_DspServiceProcessingSts.ucSecCompareKeyReqPending == DCM_TRUE) ||
       (Dcm_DspServiceProcessingSts.ucSecSeedReqPending == DCM_TRUE))
    {
      Std_ReturnType LddReturnValue;
      
      LpSecData = &Dcm_GaaSecurityLevConfig[Dcm_GucDspStIndex];
      LpReqResData = Dcm_GstMsgContext.reqData;
      /* polyspace<RTE: NIV : Not a defect : No Action Planned > initialized variable */
      LucSecLvl = LpReqResData[DCM_ZERO] & DCM_SUBFUNCTION_MASK;
  
      #if((DCM_STANDARD_SUPPORT == DCM_ES96590_SUPPORT) || (DCM_STANDARD_SUPPORT == DCM_QZN04_SUPPORT))
      /* Request Seed & consecutive request check */
      if( ((LucSecLvl & DCM_BIT0_AND_MASK) != DCM_ZERO) && 
          (DCM_TRUE == Dcm_DspSerPgStatus.ucSecSeedReq)
        )
      {
        Dcm_SetSecAccessCntDec(&Dcm_GucFailedSecurityAccessCount, &Dcm_GddNegRespError,
                                 LpSecData);
      }
  
      if(DCM_E_EXCEEDNUMBEROFATTEMPTS != Dcm_GddNegRespError)
      #endif      
      {
        LddReturnValue = Dcm_DspInternal_DcmSecurityAccess(
          DCM_PENDING, LpSecData, LpReqResData, &LddErrorCode, LucSecLvl);
    
        if((LucSecLvl & DCM_BIT0_AND_MASK) == DCM_ZERO)
        {
          /* Get the pointer to the response data buffer */
          LpReqResData = Dcm_GstMsgContext.resData;
    
          /* Check if compare key failed */
          if((LddReturnValue != DCM_E_OK) && (LddReturnValue != DCM_E_PENDING))
          {
            /* Increment the security access count */          
            #if((DCM_STANDARD_SUPPORT == DCM_ES96590_SUPPORT) || \
                (DCM_STANDARD_SUPPORT == DCM_ES95486_SUPPORT) || \
                (DCM_STANDARD_SUPPORT == DCM_ES95486_50_SUPPORT) || \
                (DCM_STANDARD_SUPPORT == DCM_QZN04_SUPPORT))
            Dcm_ChkSecAccessCntInc(&Dcm_GucFailedSecurityAccessCount, LpSecData->ucSecNumMaxAttDelay);
            
            #else
            if(Dcm_GucFailedSecurityAccessCount < DCM_MAXVALUE)
            {
              /* Increment the security access count */
              Dcm_GucFailedSecurityAccessCount++;
            }
            #endif
            
            /*
            * Check whether number of security accesses after which delay time
            * is activated is less than security access count value
            */
            /* Fixed by youngjin.yun, "==" ->  "<" */
            if(Dcm_GucFailedSecurityAccessCount < (LpSecData->ucSecNumMaxAttDelay))
            {
              Dcm_GddNegRespError = DCM_E_INVALIDKEY;
            }
            /* Fixed by youngjin.yun, ">" ->  ">=" */
            else /* if (Dcm_GucFailedSecurityAccessCount >= (LpSecData->ucSecNumMaxAttDelay)) */
            {
              /* Report the exceeded number of attempts NRC */
              Dcm_GddNegRespError = DCM_E_EXCEEDNUMBEROFATTEMPTS;
              DCM_START_TIMER(DCM_SECURITY_TIMER, LpSecData->usSecDelayInvKey);

              #if((DCM_STANDARD_SUPPORT == DCM_ES96590_SUPPORT) || (DCM_STANDARD_SUPPORT == DCM_QZN04_SUPPORT))
              Dcm_ChkSecAccessCntDec(&Dcm_GucFailedSecurityAccessCount);
              /* Set global bit flag indicating the security seed request to FALSE */
              Dcm_DspSerPgStatus.ucSecSeedReq = DCM_FALSE;
              #else
              Dcm_GucFailedSecurityAccessCount = DCM_ZERO;
              #endif
            }
            /* Modified by youngjin.yun
            else
            {    
              
              Dcm_GddNegRespError = DCM_E_INVALIDKEY; 
            }
            */
            
            Dcm_DspServiceProcessingSts.ucSecCompareKeyReqPending = DCM_FALSE;
          }
          else if(LddReturnValue == DCM_E_OK)
          {
            Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
            /* Set the security level to the requested security level */
            DslInternal_SetSecurityLevel(LpSecData->ddSecLevel);
            /* Update sub-function number */
            LpReqResData[DCM_ZERO] = LucSecLvl;
            /* Update the response data length */
            Dcm_GstMsgContext.resDataLen = DCM_ONE;
            
            #if((DCM_STANDARD_SUPPORT != DCM_ES96590_SUPPORT) && (DCM_STANDARD_SUPPORT != DCM_QZN04_SUPPORT))
            Dcm_GucFailedSecurityAccessCount = DCM_ZERO;
            #endif
  
            /* Set global bit flag indicating the security seed request to FALSE */
            Dcm_DspSerPgStatus.ucSecSeedReq = DCM_FALSE;
            Dcm_DspServiceProcessingSts.ucSecCompareKeyReqPending = DCM_FALSE;
            Dcm_GddOpStatus = DCM_INITIAL;
          }
          else
          {
            /* To avoid QAC warning */
          }
        }
        else /* Request Seed */
        {
          if(LddReturnValue == E_OK)
          {
            /* Response message length seed length + sub function */
            Dcm_GstMsgContext.resDataLen = LpSecData->ulSizeOfSeed + 1U;  
            
            /* Initialize the counter to zero */
            LulLoopCnt = DCM_ZERO;
            /* Update sub function number */
            LpReqResData[DCM_ZERO] = LucSecLvl;
            /* Get the pointer to the response data buffer */
            LpReqResData = Dcm_GstMsgContext.resData;
    
            /* Get the seed size configured for the requested security level */
            LulLength = LpSecData->ulSizeOfSeed;
    
            /* Update sub-function number */
            LpReqResData[DCM_ZERO] = LucSecLvl;
    
            /* Increment the pointer to the response buffer area */
            LpReqResData = &LpReqResData[1u];
            /* Transfer the complete seed bytes to the response buffer */
            while(LulLoopCnt < LulLength)
            {
              LpReqResData[LulLoopCnt] = Dcm_GaaSeed[LulLoopCnt];
              /* Increment the counter value */
              LulLoopCnt++;
            }
            /* Set bit flag indicating the security seed request to TRUE */
            Dcm_DspSerPgStatus.ucSecSeedReq = DCM_TRUE;
            Dcm_DspServiceProcessingSts.ucSecSeedReqPending = DCM_FALSE;
    
            Dcm_GddOpStatus = DCM_INITIAL;
          }
          else if(LddReturnValue == E_NOT_OK)
          {
            Dcm_GddNegRespError = LddErrorCode;
            Dcm_DspServiceProcessingSts.ucSecSeedReqPending = DCM_FALSE;
            Dcm_GddOpStatus = DCM_INITIAL;
          }
          else
          {
          /* To avoid QAC warning */
          }
        }
      }
      
      /* FIXME:  condition is always true */
      if((Dcm_DspServiceProcessingSts.ucSecSeedReqPending == DCM_FALSE) &&
         (Dcm_DspServiceProcessingSts.ucSecCompareKeyReqPending == DCM_FALSE))
          /*&& 
         ((Dcm_DspSerPgStatus.ucSecSeedReq == DCM_TRUE)||
          (Dcm_DspSerPgStatus.ucSecSeedReq == DCM_FALSE))) */
      {
        /* Check if the negative response needs to be updated here */
        if(Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE)
        {
          /* Report the NRC to the DSD layer */
          Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
        }
        /* Transmit the response to the DSD layer */
        Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
      }
    }
  }
}
#endif


/*******************************************************************************
** Function Name        : Dcm_MemoryServicesMainFunction                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used for processing the tasks of    **
**                        the main loop for Memory related  services          **
**                        It is called periodically as cyclic task by the     **
**                        software system.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_MemServicePendingStatus    **
**                        Dcm_ServiceForcePendingStatus , Dcm_GpMsgContext    **
**                          Dcm_GblRespPendConfirmation , Dcm_GblUpLoadActive **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if((DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON) || \
    (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON) || \
    (DCM_TRANSFER_DATA_SERVICE == STD_ON) || \
    (DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON) || \
    (DCM_REQUEST_UPLOAD_SERVICE == STD_ON) || \
    (DCM_TRANSFER_EXIT_SERVICE == STD_ON))
static FUNC(void, DCM_CODE) Dcm_MemoryServicesMainFunction (void)
{
  if(Dcm_TxRespStatus.ucNegResp == DCM_FALSE)
  {
    #if(DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON)

    /* [SWS_Dcm_00840] After transmit confirmation of a RCR-RP transmitted on the 
     * context of SWS_Dcm_00839, the DCM calls, from Dcm_MainFunction (due to call 
     * context), Dcm_ReadMemory again with OpStatus = DCM_FORCE_RCRRP_OK. */    
     
    /* Check for DCM_E_PENDING */     
    if 
    ( (Dcm_MemServicePendingStatus.ucReadMemPendingStatus == DCM_TRUE) 
      || 
      (
        (Dcm_ServiceForcePendingStatus.ucReadMemForcePendingStatus == DCM_TRUE) &&
        (Dcm_GblRespPendConfirmation == DCM_TRUE)
      )
    )
    {
      Dcm_GblRespPendConfirmation = DCM_FALSE;
      /* Invoke internal function */
      Dcm_DcmReadMemoryCall(&Dcm_GstMsgContext);
    }
    #endif

    #if(DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
    /* SWS_Dcm_00838] After transmit confirmation of a RCR-RP transmitted on the 
     * context of SWS_Dcm_00837, the DCM calls, from Dcm_MainFunction (due to call 
     * context), Dcm_WriteMemory again with OpStatus = DCM_FORCE_RCRRP_OK. */
    
    /* Check for DCM_E_PENDING */
    if 
    ( (Dcm_MemServicePendingStatus.ucWriteMemPendingStatus == DCM_TRUE) 
       ||
      (
        (Dcm_ServiceForcePendingStatus.ucWriteMemForcePendingStatus == DCM_TRUE)&&
        (Dcm_GblRespPendConfirmation == DCM_TRUE)
      )
    )
    {
      Dcm_GblRespPendConfirmation = DCM_FALSE;
      /* Invoke internal function */
      Dcm_DcmWriteMemoryCall(&Dcm_GstMsgContext);
    }
    #endif

    #if(DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON)
    /* [SWS_Dcm_00529] After transmit confirmation of a RCR-RP transmitted on the 
     * context of [SWS_Dcm_00528, the DCM calls, from Dcm_MainFunction (due to call 
     * context), the operation again with OpStatus = DCM_FORCE_RCRRP_OK */
     
    /* Check for DCM_E_PENDING */
    if 
    ( (Dcm_MemServicePendingStatus.ucDlPendingStatus == DCM_TRUE) 
      ||
      (
        (Dcm_ServiceForcePendingStatus.ucDlForcePendingStatus == DCM_TRUE) && 
        (Dcm_GblRespPendConfirmation == DCM_TRUE)
      )
    )
    {
      Dcm_GblRespPendConfirmation = DCM_FALSE;
      /* Invoke internal function */
      Dcm_DcmDownLoadCall(&Dcm_GstMsgContext);
    }
    #endif

    #if(DCM_REQUEST_UPLOAD_SERVICE == STD_ON)
    /* [SWS_Dcm_00529] After transmit confirmation of a RCR-RP transmitted on the 
     * context of [SWS_Dcm_00528, the DCM calls, from Dcm_MainFunction (due to call 
     * context), the operation again with OpStatus = DCM_FORCE_RCRRP_OK */    
    if 
    ( (Dcm_MemServicePendingStatus.ucUlPendingStatus == DCM_TRUE) 
       ||
      (
        (Dcm_ServiceForcePendingStatus.ucUlForcePendingStatus == DCM_TRUE) && 
        (Dcm_GblRespPendConfirmation == DCM_TRUE)
      )
    )
    {
      Dcm_GblRespPendConfirmation = DCM_FALSE;
      Dcm_DcmUpLoadCall(&Dcm_GstMsgContext);
    }
    #endif
    #if(DCM_TRANSFER_DATA_SERVICE == STD_ON)
    /* [SWS_Dcm_00529] After transmit confirmation of a RCR-RP transmitted on the 
     * context of [SWS_Dcm_00528, the DCM calls, from Dcm_MainFunction (due to call 
     * context), the operation again with OpStatus = DCM_FORCE_RCRRP_OK */
     
    /* Check for DCM_E_PENDING */
    SchM_Enter_Dcm_RxPduIdProtection();
    if 
    ( (Dcm_MemServicePendingStatus.ucTransferDataPendingStatus == DCM_TRUE) 
      ||
      (
        (Dcm_ServiceForcePendingStatus.ucTransferDataForcePendingStatus == DCM_TRUE) &&
        (Dcm_GblRespPendConfirmation == DCM_TRUE)
      )
    )
    {
      SchM_Exit_Dcm_RxPduIdProtection();
      Dcm_GblRespPendConfirmation = DCM_FALSE;
      if(Dcm_GblDownLoadActive == DCM_TRUE)
      {
        #if(DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON)
        Dcm_DownLoadTransferCall(&Dcm_GstMsgContext);
        #endif
      }      
      else if(Dcm_GblUpLoadActive == DCM_TRUE)
      {
        #if(DCM_REQUEST_UPLOAD_SERVICE == STD_ON)
        /* Invoke Dcm_ReadMemory callout */
        Dcm_UpLoadTransferCall(&Dcm_GstMsgContext);
        #endif
      }
      else
      {
      /* To avoid QAC warning */
      }
    }
    else
    {
      SchM_Exit_Dcm_RxPduIdProtection();
    }
    #endif

    #if(DCM_TRANSFER_EXIT_SERVICE == STD_ON)
    /* [SWS_Dcm_00529] After transmit confirmation of a RCR-RP transmitted on the 
     * context of [SWS_Dcm_00528, the DCM calls, from Dcm_MainFunction (due to call 
     * context), the operation again with OpStatus = DCM_FORCE_RCRRP_OK */
     
    /* Check for DCM_E_PENDING */
    if 
    ( (Dcm_MemServicePendingStatus.ucTransferExitPendingStatus == DCM_TRUE) 
      ||
      (
        (Dcm_ServiceForcePendingStatus.ucTransferExitForcePendingStatus == DCM_TRUE) &&
        (Dcm_GblRespPendConfirmation == DCM_TRUE)
      )
    )
    {
      Dcm_GblRespPendConfirmation = DCM_FALSE;
      /* Invoke internal function */
      Dcm_RequestTransferExitCall(&Dcm_GstMsgContext);
      /* Check Ecu Reset status */
    }
    #endif
  }
}
#endif


/*******************************************************************************
** Function Name        : Dcm_DIDServicesMainFunction                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used for processing the tasks of    **
**                        the main loop for DID related services.             **
**                        It is called periodically as cyclic task by the     **
**                        software system.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_DspServiceProcessingSts ,                       **
**                        Dcm_GaaDIDParaConfig , Dcm_GusDIDIndexVal           **
**                        Dcm_GddOpStatus, Dcm_GpMsgContext                   **
**                        Dcm_GddNegRespError, Dcm_MemServicePendingStatus    **
**                        Dcm_GucInOutParameter , Dcm_GusRIDIndex             **
**                        Dcm_GaaRoutineControlConfig ,                       **
**                        Dcm_GusRoutineIdentifier                            **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if((DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON)|| \
    (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
    (DCM_ROUTINECONTROL_SERVICE == STD_ON))
/* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > pointer is not null */
static FUNC(void, DCM_CODE) Dcm_DIDServicesMainFunction (void)
{
  #if(DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON)
  Std_ReturnType LddReturnValue = E_NOT_OK;
  #endif

  /* FIXME: Have to do reverse engineering!!!!! .. remove this code */
  #if(DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON)
  if (Dcm_DspServiceProcessingSts.ucReadScalingDataPending == DCM_TRUE)
  {
    if (Dcm_GusDIDIndexVal < Dcm_Num_Of_DidParaConfig)
    {
      if (NULL_PTR != Dcm_GaaDIDParaConfig[Dcm_GusDIDIndexVal].pDcmDspSignal)
      {
        P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_DATA) 
        cfgDataElement = Dcm_GaaDIDParaConfig[Dcm_GusDIDIndexVal].pDcmDspSignal->pDcmDspData;
        if (NULL_PTR != cfgDataElement)
        {
          /* FIXME: BUG : pDcmDspData[index of data] shall be processed */
          if ((DCM_USE_DATA_ASYNCH_FNC == cfgDataElement->ucDcmDspDataUsePort) || (DCM_USE_DATA_ASYNCH_CLIENT_SERVER == cfgDataElement->ucDcmDspDataUsePort))
          {
            if (NULL_PTR != cfgDataElement->pGetScalingInformationAsync)
            {
               /* Invoke the ScalingInfo function with corresponding buffer for response */
              /* polyspace<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */
              LddReturnValue = cfgDataElement->pGetScalingInformationAsync(
                Dcm_GddOpStatus, &Dcm_GstMsgContext.resData[DCM_TWO], &Dcm_GddNegRespError);        
            }
            else
            {
              DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID,DCM_E_PARAM);

              LddReturnValue = E_NOT_OK;
            }
        
            if (LddReturnValue == E_OK)
            {
              P2CONST(Dcm_DataInfoType, AUTOMATIC, DCM_APPL_DATA) 
              cfgScalingInfo = cfgDataElement->pDataInfo;         
              
              if ((NULL_PTR != cfgScalingInfo) && (NULL_PTR != Dcm_GstMsgContext.reqData))
              {
                Dcm_DspServiceProcessingSts.ucReadScalingDataPending = DCM_FALSE;
                /* Update First Byte DID */
                Dcm_GstMsgContext.resData[DCM_ZERO] = Dcm_GstMsgContext.reqData[DCM_ZERO];
                /* Update Second Byte DID */
                Dcm_GstMsgContext.resData[DCM_ONE] = Dcm_GstMsgContext.reqData[DCM_ONE];
                /* Response message length is Calculated */
                Dcm_GstMsgContext.resDataLen = DCM_TWO + cfgScalingInfo->ulDataScalingInfoSize;
              }
              else
              {
                DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID,DCM_E_PARAM);

                Dcm_DspServiceProcessingSts.ucReadScalingDataPending = DCM_FALSE;
                /* Update the NRC value */
                Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
              }
            }
            else if(LddReturnValue == E_NOT_OK)
            {
              Dcm_DspServiceProcessingSts.ucReadScalingDataPending = DCM_FALSE;
              /* Update the NRC value */
              Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
            }
            else
            {
              /* To avoid QAC warning */
            }
          }
          else
          {
            DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID,DCM_E_PARAM);

            Dcm_DspServiceProcessingSts.ucReadScalingDataPending = DCM_FALSE;
            /* Update the NRC value */
            Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
          }          
        }
        else
        {
          DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID,DCM_E_PARAM);

          Dcm_DspServiceProcessingSts.ucReadScalingDataPending = DCM_FALSE;
          /* Update the NRC value */
          Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
        }        
      }
      else
      {
        DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID,DCM_E_PARAM);

        Dcm_DspServiceProcessingSts.ucReadScalingDataPending = DCM_FALSE;
        /* Update the NRC value */
        Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
      }      
    }
    else
    {
      DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID,DCM_E_PARAM);

      Dcm_DspServiceProcessingSts.ucReadScalingDataPending = DCM_FALSE;
      /* Update the NRC value */
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }  
    
    if(Dcm_DspServiceProcessingSts.ucReadScalingDataPending == DCM_FALSE)
    {
      Dcm_GusDIDIndexVal = DCM_ZERO;
      if(Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE)
      {
        /* Report the NRC to the DSD layer */
        Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
      }
      /* Transmit the response to the DSD layer */
      Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
    }    
  }
  #endif
  
  #if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)

  if(
    (Dcm_ServicePendingStatus.ucIocontrolPendingStatus == DCM_TRUE) || 
    (Dcm_ServicePendingStatus.ucIoCtrlReadCdtChkPendingStatus == DCM_TRUE) ||
    (Dcm_MemServicePendingStatus.ucIoCtrlReadDataPendingStatus == DCM_TRUE)
  )
  {
    (void) Dcm_DspInternal_DcmInputOutputControlByIdentifier(
      DCM_PENDING, Dcm_GucInOutParameter, &Dcm_GaaDIDParaConfig[Dcm_GusDIDIndexVal], &Dcm_GstMsgContext);

    if(
      (Dcm_ServicePendingStatus.ucIocontrolPendingStatus ==  DCM_FALSE) && 
      (Dcm_ServicePendingStatus.ucIoCtrlReadCdtChkPendingStatus == DCM_FALSE) &&
      (Dcm_MemServicePendingStatus.ucIoCtrlReadDataPendingStatus == DCM_FALSE)
    )
    {
      /* Check if the negative response needs to be updated here */
      if (Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE)
      {
        /* Report the NRC to the DSD layer */
        Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
      }
      else
      {
        if(NULL_PTR != Dcm_GstMsgContext.reqData)
        {
          Dcm_GstMsgContext.resDataLen = Dcm_GstMsgContext.resDataLen + DCM_THREE;
          /* Update First Byte DID */
          Dcm_GstMsgContext.resData[DCM_ZERO] = Dcm_GstMsgContext.reqData[DCM_ZERO];
          /* Update Second Byte DID */
          Dcm_GstMsgContext.resData[DCM_ONE] = Dcm_GstMsgContext.reqData[DCM_ONE];
          /* Update Third Byte inputOutputControlParameter*/
          Dcm_GstMsgContext.resData[DCM_TWO] = Dcm_GstMsgContext.reqData[DCM_TWO];
          /* Update inputOutputControlParameter echo from the request */
          Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
        }
        else
        {
          Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
          Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
        }
      }
      /* Transmit the response to the DSD layer */
      Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
      Dcm_ResetDIDOpStatus();
    }
  }
  #endif

  #if(DCM_ROUTINECONTROL_SERVICE == STD_ON)
  Dcm_RoutineMainFunction();
  #endif
}
/* polyspace:end<RTE: NIP : Not a defect : No Action Planned > pointer is not null */
#endif


/*******************************************************************************
** Function Name        : Dcm_OBD_DTC_MainFunction                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used for processing the tasks of    **
**                        the main loop for OBD and DTC related services.     **
**                        It is called periodically as cyclic task by the     **
**                        software system.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddNegRespError,           **
**                        Dcm_DspSerPgStatus , Dcm_PrtclTxBufStatus           **
**                        Dcm_GulDTCValue , Dcm_GpMsgContext                  **
**                        Dcm_GblNumFilterDTCStatusBySevirtMask               **
**                        Dcm_GblFaultDetcetionCounter                        **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if((DCM_DSP_CLR_DIAG_SERVICE == STD_ON) || \
    (DCM_OBD_CLRRESET_EMISSION_DIAGINFO_SERVICE == STD_ON)|| \
    (DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON)|| \
    (DCM_RPT_NOOFDTC == STD_ON) || \
    (DCM_RPT_DTC == STD_ON) || \
    (DCM_RPT_DTC_FLT_DET_CTR == STD_ON) || \
    ((DCM_OBD_GETDTC_03_SERVICE == STD_ON) || \
    (DCM_OBD_GETDTC_07_SERVICE == STD_ON) || \
    (DCM_OBD_GETDTC_0A_SERVICE == STD_ON)) || \
    (DCM_FAULT_DETECTION_COUNTER == STD_ON))
static FUNC(void, DCM_CODE) Dcm_OBD_DTC_MainFunction (void)
{

  #if(DCM_DSP_CLR_DIAG_SERVICE == STD_ON)
  /* Check for DCM_E_PENDING */
  if(Dcm_PrtclTxBufStatus.ucClearDTCStatus == DCM_TRUE)
  {
    /* Invoke internal function */
    Dcm_DspClearDiagInfo(Dcm_GulDTCValue, &Dcm_GstMsgContext);
  }
  #endif

  #if(DCM_OBD_CLRRESET_EMISSION_DIAGINFO_SERVICE == STD_ON)

  /* Check for DCM_E_PENDING */
  if(Dcm_PrtclTxBufStatus.ucClearDTCStatus == DCM_TRUE)
  {
    /* Invoke internal function */
    Dcm_DcmOBDClrResetEmissionDiagInfo(DCM_PENDING, &Dcm_GstMsgContext);
  }
  #endif

  #if(DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON)
  if(Dcm_GblNumFilterDTCStatusBySevirtMask == DCM_TRUE)
  {
    /* Invoke internal function */
    Dcm_GetNumberOfFilteredDtcBySeverityInfo();
    if(Dcm_GblNumFilterDTCStatusBySevirtMask == DCM_FALSE)
    {
      /* Check if the negative response needs to be updated here */
      if (Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE)
      {
        /* Report the NRC to the DSD layer */
        Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
      }
      /* Transmit the response to the DSD layer */
      Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
    }
  }
  #endif
  #if(DCM_RPT_NOOFDTC == STD_ON)
  /* Check for DCM_E_PENDING */
  if(Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus == DCM_TRUE)
  {
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext;
    
    #if((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && (DCM_PROTOCOL_TRANSTYPE2 == STD_ON))
    if(Dcm_GucResOnEventStatus == DCM_ROEONGOING)
    {
      pMsgContext = Dcm_GpRoeMsgContext;    
    }
    else
    #endif
    {
      pMsgContext = &Dcm_GstMsgContext;
    }
    
    /* Invoke internal function */
    Dcm_DemGetNumberOfFilteredDtc(pMsgContext);    
    
    /* Check Ecu Reset status */
    if(Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus == DCM_FALSE)
    {
      /* Check if the negative response needs to be updated here */
      if (Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE)
      {
        /* Report the NRC to the DSD layer */
        Dcm_ExternalSetNegResponse(pMsgContext, Dcm_GddNegRespError);
      }
      /* Transmit the response to the DSD layer */
      Dcm_ExternalProcessingDone(pMsgContext);
    }
  }
  #endif

  #if(DCM_RPT_DTC == STD_ON)
  /* Check for DCM_E_PENDING */
  if(Dcm_PrtclTxBufStatus.ReportNumOfDtc == DCM_TRUE)
  {
    /* Invoke internal function */
    Dcm_DemGetNumberOfReportedDTC();
    /* Check Ecu Reset status */
    if((Dcm_PrtclTxBufStatus.ReportNumOfDtc == DCM_FALSE) &&
      (Dcm_DspSerPgStatus.ucPagingStarted != DCM_TRUE))
    {
      #if (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON)
      Dcm_InternalTroubleCodeService = DCM_FALSE;
      #endif
      /* Check if the negative response needs to be updated here */
      if (Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE)
      {
        /* Report the NRC to the DSD layer */
        Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
      }
      /* Transmit the response to the DSD layer */
      Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
    }
  }
  #endif
  
  #if(DCM_RPT_DTC_FLT_DET_CTR == STD_ON)
  if(Dcm_GblDTCFDCPending == DCM_TRUE)
  {
    /* Invoke internal function */
    (void)Dcm_DspReadReqdDTCFDC(Dcm_GulFDCRespSize);
    if(Dcm_GblDTCFDCPending == DCM_FALSE)
    {
      /* Check if the negative response needs to be updated here */
      if (Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE)
      {
        /* Report the NRC to the DSD layer */
        Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
      }
    }
    /* Transmit the response to the DSD layer */
    Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
  }
  #endif

  #if((DCM_OBD_GETDTC_03_SERVICE == STD_ON) || \
      (DCM_OBD_GETDTC_07_SERVICE == STD_ON) || \
      (DCM_OBD_GETDTC_0A_SERVICE == STD_ON))
  /* Check for DCM_E_PENDING */
  if(Dcm_PrtclTxBufStatus.ucReportOBDDtc == DCM_TRUE)
  {
    /* Invoke internal function */
    Dcm_DemGetNumberOfOBDDTC();
    /* Check Ecu Reset status */
    if((Dcm_PrtclTxBufStatus.ucReportOBDDtc == DCM_FALSE) &&
      (Dcm_DspSerPgStatus.ucPagingStarted != DCM_TRUE))
    {
      /* Check if the negative response needs to be updated here */
      if (Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE)
      {
        /* Report the NRC to the DSD layer */
        Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
      }
      /* Transmit the response to the DSD layer */
      Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
    }
  }
  #endif
  
  #if(DCM_FAULT_DETECTION_COUNTER == STD_ON)
  /* Check for DCM_E_PENDING */
  if((Dcm_GblFaultDetcetionCounter == DCM_TRUE) || (Dcm_GblDTCFDCPending == DCM_TRUE))
  {
    if(Dcm_GblFaultDetcetionCounter == DCM_TRUE)
    {
      Dcm_DspRptDTCFltDetCtr(&Dcm_GstMsgContext);
    }
    else
    {
      (void)Dcm_DspReadReqdDTCFDC(Dcm_GulFDCRespSize);
       /* Check Ecu Reset status */
      if(Dcm_GblDTCFDCPending == DCM_FALSE)
      {
        /* Check if the negative response needs to be updated here */
        if(Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE)
        {
          /* Report the NRC to the DSD layer */
          Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
        }
        /* Transmit the response to the DSD layer */
        Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
      }
    }
  }
  #endif
}
#endif

/*******************************************************************************
** Function Name        : Dcm_READ_WRITE_DID_MainFunction                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used for processing the tasks of    **
**                        the main loop for Read and Write DID services.      **
**                        It is called periodically as cyclic task by the     **
**                        software system.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddNegRespError,           **
**                        Dcm_ServicePendingStatus , Dcm_GblDIDRangePresent   **
**                        Dcm_GusDIDIndexVal, Dcm_GaaDIDParaConfig,           **
**                        Dcm_GpMsgContext, Dcm_GusDataIdentifier,            **
**                        Dcm_GddOpStatus                                     **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if((DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
    (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(void, DCM_CODE) Dcm_READ_WRITE_DID_MainFunction (void)
{
  #if (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)  
  /* Check for DCM_E_PENDING */
  if(Dcm_ServicePendingStatus.ucWriteDataByIdPendingStatus == DCM_TRUE)
  {
    /* TODO : Make Dcm_DspInternal_DcmWriteDataByIdentifier */
    if((DCM_ZERO != Dcm_Num_Of_DcmDspDidRangeConfig) &&
                                           (DCM_TRUE == Dcm_GblDIDRangePresent))
    {
      Dcm_DspWriteDidRangeData(&Dcm_GstMsgContext, Dcm_GusDataIdentifier,
                                                            Dcm_GusDIDIndexVal);
    }
    else
    {
      Dcm_DcmWriteDataByIdentifierCall(&Dcm_GstMsgContext, Dcm_GusDIDIndexVal);
    }

    if(Dcm_ServicePendingStatus.ucWriteDataByIdPendingStatus == DCM_FALSE)
    {
      Dcm_ResetWriteDIDOpStatus();
      /* Check if the negative response needs to be updated here */
      if (Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE)
      {
        /* Report the NRC to the DSD layer */
        Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
      }
      else
      {
        /* TODO : Make Dcm_DspInternal_DcmWriteDataByIdentifier */
        Dcm_GddOpStatus = DCM_INITIAL;

        if(NULL_PTR != Dcm_GstMsgContext.resData)
        {
          Dcm_GstMsgContext.resDataLen = 2U;  /* Response message length is Calculated */
          /* polyspace<RTE: NIV : Not a defect : No Action Planned > initialized variable */
          Dcm_GstMsgContext.resData[0U] = Dcm_GstMsgContext.reqData[0U];  /* Update First Byte DID */
          /* polyspace<RTE: NIV : Not a defect : No Action Planned > initialized variable */
          Dcm_GstMsgContext.resData[1U] = Dcm_GstMsgContext.reqData[1U];  /* Update Second Byte DID */
          
          Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
        }
        else
        {
          Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
          Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
        }
      }
      /* Transmit the response to the DSD layer */
      Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
    }
  }
  #endif

  /* Refactoring by youngjin.yun, 2015-01-05 */
  #if(DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
  
  /* Check for DCM_E_PENDING */
  if (Dcm_ServicePendingStatus.ucReadDataPendingStatus == DCM_TRUE)
  {
    /* FIXME : if Periodic DID is running , periodic context shall be used */
    Dcm_DspInternal_DcmReadDataByIdentifier(DCM_PENDING, &Dcm_GstMsgContext);
    
    /* Dcm_ServicePendingStatus.ucReadDataPendingStatus is changed 
     * in the Dcm_DspInternal_DcmReadDataByIdentifier */
    if (Dcm_ServicePendingStatus.ucReadDataPendingStatus != DCM_TRUE)
    {
      /* Check if the negative response needs to be updated here */
      if (Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE)
      {
        /* Report the NRC to the DSD layer */
        Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
      }
      /* Transmit the response to the DSD layer */
      Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
    }
  }
  #endif
}
#endif

/*******************************************************************************
** Function Name        : Dcm_PERIODIC_DID_MainFunction                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used for processing the tasks of    **
**                        the main loop for read Periodic DID service.        **
**                        It is called periodically as cyclic task by the     **
**                        software system.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GaaPeriodicID  ,           **
**                        Dcm_GaaDIDParaConfig , Dcm_ServicePendingStatus     **
**                        Dcm_GpMsgContext ,  Dcm_GaaTimer                    **
**                        Dcm_GaaActivePeriodicTimer , Dcm_GaaPeriodicID      **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
FUNC(void, DCM_CODE) Dcm_PERIODIC_DID_MainFunction (void)
{


  if(Dcm_ServicePendingStatus.ucReadPerDIDPendingStatus == DCM_TRUE)
  {

    Std_ReturnType retVal = E_OK;
    /* FIXME  : periodic msg context shall be used */
    retVal = Dcm_DspInternal_DcmReadDataByPeriodicIdentifier(DCM_PENDING, &Dcm_GstMsgContext);
    if(DCM_E_PENDING != retVal)
    {
      Dcm_HandlePeriodicResponse(&Dcm_GstMsgContext);
    }
  }

  /*ucPeriodicIdStatus(true) : Read Periodic By idenfiier is running */
  if(Dcm_PrtclTxBufStatus.ucPeriodicIdStatus == DCM_TRUE)
  { 
    uint16 LusIDIndex1;
    uint8 LucTimerValue;
  
    uint8 LucDataIdentifier;

    boolean LblSlowTimerExpired;
    boolean LblMediumTimerExpired;
    boolean LblFastTimerExpired;

    LblSlowTimerExpired = DCM_FALSE;
    LblMediumTimerExpired = DCM_FALSE;
    LblFastTimerExpired = DCM_FALSE;

    /* Validate expiry of periodic ID timer */
    if((Dcm_GaaTimer[DCM_PERIODIC_SLOW_TIMER] == DCM_ZERO) ||
      (Dcm_GaaTimer[DCM_PERIODIC_MEDIUM_TIMER] == DCM_ZERO) ||
      (Dcm_GaaTimer[DCM_PERIODIC_FAST_TIMER] == DCM_ZERO))
    {
      if((Dcm_GaaActivePeriodicTimer[DCM_ZERO] == DCM_TRUE) &&
        (Dcm_GaaTimer[DCM_PERIODIC_SLOW_TIMER] == DCM_ZERO))
      {
        LblSlowTimerExpired = DCM_TRUE;
      }
      if((Dcm_GaaActivePeriodicTimer[DCM_ONE] == DCM_TRUE) &&
        (Dcm_GaaTimer[DCM_PERIODIC_MEDIUM_TIMER] == DCM_ZERO))
      {
        LblMediumTimerExpired = DCM_TRUE;
      }
      if((Dcm_GaaActivePeriodicTimer[DCM_TWO] == DCM_TRUE) &&
        (Dcm_GaaTimer[DCM_PERIODIC_FAST_TIMER] == DCM_ZERO))
      {
        LblFastTimerExpired = DCM_TRUE;
      }

      if((LblSlowTimerExpired ==  DCM_TRUE) ||
        (LblMediumTimerExpired == DCM_TRUE) ||
        (LblFastTimerExpired == DCM_TRUE))
      {
        for(LusIDIndex1 = DCM_ZERO;
          LusIDIndex1 < Dcm_Dsp_Max_Periodic_DID_Scheduled; LusIDIndex1++)
        {
          if(Dcm_GaaPeriodicID[LusIDIndex1] [DCM_ZERO]!= DCM_ZERO)
          {
            LucTimerValue = (uint8) Dcm_GaaPeriodicID[LusIDIndex1] [DCM_ONE];
            if(((LucTimerValue == DCM_ONE) &&
              (LblSlowTimerExpired == DCM_TRUE)) ||
              ((LucTimerValue == DCM_TWO) &&
              (LblMediumTimerExpired == DCM_TRUE)) ||
              ((LucTimerValue == DCM_THREE) &&
              (LblFastTimerExpired == DCM_TRUE)))
            {
              LucDataIdentifier = (uint8)(Dcm_GaaPeriodicID[LusIDIndex1] [DCM_ZERO] & DCM_MAXVALUE);

              (void)DslInternal_ResponseOnOneDataByPeriodicId(LucDataIdentifier);
            }
            else
            {
              /* Avoid to RTRT error */
            }
          }
        }
      }
    }
    if(LblSlowTimerExpired == DCM_TRUE)
    {
      DCM_START_TIMER(DCM_PERIODIC_SLOW_TIMER, Dcm_Send_At_Low_Rate_Timer);
    }
    if(LblMediumTimerExpired == DCM_TRUE)
    {
      DCM_START_TIMER(DCM_PERIODIC_MEDIUM_TIMER, Dcm_Send_At_Med_Rate_Timer);
    }
    if(LblFastTimerExpired == DCM_TRUE)
    {
      DCM_START_TIMER(DCM_PERIODIC_FAST_TIMER, Dcm_Send_At_Fast_Rate_Timer);
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_ROE_MainFunction                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used for processing the tasks of    **
**                        the main loop for Response on Event service.        **
**                        It is called periodically as cyclic task by the     **
**                        software system.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddDcmTxPduId,             **
**                                             Dcm_GucResOnEventStatus,       **
**                                             Dcm_GblNormalReq,              **
**                                             Dcm_GucRoeSTRTIndex            **
**                                                                            **
**                        Function(s) invoked: Dcm_DslTransmit,               **
**                                             Dcm_ExternalProcessingDone,    **
**                                             Dcm_DspReadROEDIDValue,        **
**                                             Dcm_DspQueueRoeEvents,         **
**                                                                            **
*******************************************************************************/
#if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
FUNC(void, DCM_CODE) Dcm_ROE_MainFunction(void)
{
  P2VAR(uint8, AUTOMATIC, DCM_PRIVATE_DATA) LpRoeInternalBuffer;
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_PRIVATE_CONST)LpPduIdTable;
  uint16 LusDIDSize;
  uint8 LucRoeTempBuffer[DCM_MAXVALUE];
  uint8 LucCount;
  uint8 LucIndexCount;
  uint8 LucNetworkId;
  #if(DCM_ROE_QUEUE_ENABLED == STD_ON)
  uint8 LucQueueReadIndex;
  uint8 LucSTRTId;
  #endif
  Std_ReturnType LddReturnValue;
  #if(DCM_MAX_NO_OF_PRECONFIGURED_DID != DCM_ZERO)
  Std_ReturnType LddEventSet;
  NvM_RequestResultType LddRequestResult;
  #endif
  boolean LblCompareResult;


  if((Dcm_TimerReqFlagStatus.ucRoeInterMsgTimer ==
                                                                      DCM_TRUE )
        && (Dcm_GaaTimer[DCM_ROE_INTERMESSAGE_TIMER] == DCM_ZERO))
  {
    if(Dcm_GucResOnEventStatus == DCM_ROEONGOING)
    {
      #if(DCM_ROE_QUEUE_ENABLED == STD_ON)
      if(Dcm_GddRoeRetryProcessInfo.blRetryRoeEvent == DCM_TRUE)
      {
        uint8 queueIndex = Dcm_GddRoeQueueProcessInfo.QueueReadIndex;
        
        /* Initialize resData from the MsgContext */
        Dcm_GstMsgContext.resData = &Dcm_GaaRoeQueueInfo[queueIndex].aaRoeQueueBuffer[1U];
        /* Initialize resDataLen from the MsgContext */
        Dcm_GstMsgContext.resDataLen = Dcm_GaaRoeQueueInfo[queueIndex].ulRoeLengthInfoBuffer;

        Dcm_DslTransmit(Dcm_GddDcmTxPduId, DCM_FALSE, DCM_FALSE);
      }
      #endif
    }
    else if((Dcm_GucResOnEventStatus == DCM_IDLE) &&
      (Dcm_GblNormalReq == DCM_FALSE))
    {
      #if(DCM_ROE_QUEUE_ENABLED == STD_ON)
      if(Dcm_GddRoeQueueProcessInfo.blQueueEmpty == DCM_FALSE)
      {
        LucQueueReadIndex = Dcm_GddRoeQueueProcessInfo.QueueReadIndex;
        LucSTRTId = Dcm_GaaRoeQueueInfo[LucQueueReadIndex].ucSTRTId;

        Dcm_GstMsgContext.reqData =
          &Dcm_GddRoeRequestInfo[LucSTRTId].RoeReqData[DCM_ONE];
        Dcm_GstMsgContext.reqDataLen =
          Dcm_GddRoeRequestInfo[LucSTRTId].ddRoeReqDataLen;
        Dcm_GstMsgContext.resData =
          &Dcm_GaaRoeQueueInfo[LucQueueReadIndex].aaRoeQueueBuffer[DCM_ONE];
        Dcm_GstMsgContext.resDataLen =
          (Dcm_GaaRoeQueueInfo[Dcm_GddRoeQueueProcessInfo.QueueReadIndex].
            ulRoeLengthInfoBuffer - DCM_ONE);
        Dcm_GstMsgContext.dcmRxPduId =
          Dcm_GddRoeRequestInfo[LucSTRTId].ddRoeRxPduId;
        Dcm_GstMsgContext.idContext =
          Dcm_GaaRoeQueueInfo[LucQueueReadIndex].idContext;
        Dcm_GstMsgContext.msgAddInfo.suppressPosResponse =
          Dcm_GaaRoeQueueInfo[LucQueueReadIndex].suppressPosResponse;
        Dcm_GstMsgContext.msgAddInfo.reqType =
          Dcm_GaaRoeQueueInfo[LucQueueReadIndex].reqType;
        Dcm_GstMsgContext.resMaxDataLen = Dcm_ROE_Max_Event_Length;

        Dcm_GucResOnEventStatus = DCM_ROEONGOING;

        /* Initialize the pointer to the PduId table */
        LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GstMsgContext.dcmRxPduId];

        /* Set the status of RxPduId */
        *(LpPduIdTable->pPduIdStatus) |= LpPduIdTable->ucPduIdStatusMask;

        Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
      }
      #endif
    }
    else
    {
      /* To avoid QAC warning */
    }
  }
   /* Initialize pointer to PduId table corresponding to the RxPduId */
   LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GpRoeMsgContext->dcmRxPduId];
   LucNetworkId = LpPduIdTable->ucRxComChannelRef;

  if((Dcm_GaaCommMode[LucNetworkId] == DCM_FULL_COMMUNICATION)
     #if(DCM_ROE_QUEUE_ENABLED == STD_OFF)
     &&(Dcm_GucResOnEventStatus == DCM_IDLE)&&(Dcm_GblNormalReq == DCM_FALSE)
     #endif
    )
  {
    /* ROE - DID internal management */
    for(LucIndexCount = DCM_ZERO ; LucIndexCount < Dcm_GucRoeSTRTIndex ;
    LucIndexCount++)
    {
      if((Dcm_GddRoeRequestInfo[LucIndexCount].blIsRoeStarted == DCM_TRUE) &&
         (Dcm_GddRoeRequestInfo[LucIndexCount].blIsOnChngOfDIDRxed == DCM_TRUE) &&
         (Dcm_GddRoeRequestInfo[LucIndexCount].blIsDIDManagedInternally ==
         DCM_TRUE))
      {
        LblCompareResult = DCM_FALSE;
        LpRoeInternalBuffer =
        &Dcm_GddRoeRequestInfo[LucIndexCount].ucInternalBuffer[DCM_ZERO];

        /* Get the DID Data Value to the temp buffer */
        LddReturnValue =
          Dcm_DspReadROEDIDValue(Dcm_GddRoeRequestInfo[LucIndexCount].usDIDIndex,
                  &LusDIDSize, &LucRoeTempBuffer[DCM_ZERO]);

        if((LddReturnValue == E_OK) &&
          ((Dcm_GddRoeRequestInfo[LucIndexCount].usDIDValueSize) == LusDIDSize))
        {
          /* check if the new value is different from old value */
          for(LucCount = DCM_ZERO; LucCount<LusDIDSize; LucCount++)
          {
            if(LucRoeTempBuffer[LucCount] != *LpRoeInternalBuffer)
            {
              LblCompareResult = DCM_TRUE;
            }

            /* Update DID value */
            *LpRoeInternalBuffer = LucRoeTempBuffer[LucCount];

            /* MISRA Rule        : 17.4
              Message            : Increment or decrement operation
                                   performed on pointer
              Reason             : Increment operator not used
                                   to achieve better throughput.
              Verification       : However, part of the code
                                   is verified manually and
                                   it is not having any impact.
            */
            LpRoeInternalBuffer++;
          }

          /* Update DID value size */
          Dcm_GddRoeRequestInfo[LucIndexCount].usDIDValueSize = LusDIDSize;

          /* If the new value of the DID is different from the previous value
           copy the data to the buffer used to store the DID value during
           ROE execution */
          if((LblCompareResult == DCM_TRUE) &&
            (Dcm_GddRoeRequestInfo[LucIndexCount].blDIDValueInit == E_OK))
          {
            Dcm_GddRoeRequestInfo[LucIndexCount].ucNumOfIdentifiedEvents++;

            /* Check if Queue is enabled and ROE is ongoing */
            #if(DCM_ROE_QUEUE_ENABLED == STD_ON)
            if(((Dcm_GucResOnEventStatus == DCM_ROEONGOING) ||
             (Dcm_GblNormalReq == DCM_TRUE)) && (Dcm_GaaDIDParaConfig
                 [Dcm_GddRoeRequestInfo[LucIndexCount].usDIDIndex].
              blDidRoeQueueEnabled == DCM_TRUE))
            {
              (void)Dcm_DspQueueRoeEvents(LucIndexCount);
            }
            else
            #endif
            {
              /*
               * Initialize the global variable with the RxPduId in case the ROE
               * request processing is to be postponed
               */
              Dcm_GddRoeRxPduId = Dcm_GddRoeRequestInfo[LucIndexCount].ddRoeRxPduId;
              /* Invoke the function to initiate the response transmission */
              (void)DslInternal_ResponseOnOneEvent
                (&Dcm_GddRoeRequestInfo[LucIndexCount].RoeReqData[DCM_ZERO],
                      Dcm_GddRoeRequestInfo[LucIndexCount].ddRoeReqDataLen,
                      Dcm_GddRoeRequestInfo[LucIndexCount].ddRoeRxPduId);
            }
          }

          /* Did Value is initialized */
          Dcm_GddRoeRequestInfo[LucIndexCount].blDIDValueInit = E_OK;
        }
      }
    }
  }

  #if((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && (DCM_MAX_NO_OF_PRECONFIGURED_DID != DCM_ZERO))
  if((Dcm_DspServiceProcessingSts.ucRoeStorePending == DCM_TRUE) &&
        (Dcm_DspServiceProcessingSts.ucRoeServiceRequest
          == DCM_TRUE))
  {
    LddReturnValue = NvM_GetErrorStatus(DCM_RESPONSE_ONEVENT_BLOCKID, &LddRequestResult);
    if((LddReturnValue == E_NOT_OK) || (LddRequestResult == NVM_REQ_NOT_OK))
    {
      Dcm_DspServiceProcessingSts.ucRoeStorePending = DCM_FALSE;
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }
    else if(LddRequestResult != NVM_REQ_PENDING)
    {
      Dcm_DspServiceProcessingSts.ucRoeStorePending =
        DCM_FALSE;
    }
    else
    {
      /* To avoid QAC */
    }

    if(Dcm_DspServiceProcessingSts.ucRoeStorePending
                  == DCM_FALSE)
    {
      if(((Dcm_GstMsgContext.reqData[0]) & DCM_ROE_SUBFUNCTION_MASK) == DCM_START_ROE)
      {
        LddEventSet = Dcm_DspEnableRoe();
      }
      else
      {
        LddEventSet = E_OK;
      }

      if((LddEventSet != E_OK) || (Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE))
      {
        /* Report the NRC to the DSD layer */
        Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
      }
      else
      {
        if(((Dcm_GstMsgContext.reqData[0]) & DCM_ROE_SUBFUNCTION_MASK) == DCM_START_ROE)
        {
          Dcm_DspServiceProcessingSts.ucRoeStartReqRxed = DCM_TRUE;
        }
        else if(((Dcm_GstMsgContext.reqData[0]) & DCM_ROE_SUBFUNCTION_MASK) == DCM_STOP_ROE)
        {
          Dcm_DspServiceProcessingSts.ucRoeStartReqRxed = DCM_FALSE;
        }
        else
        {
        }
      }
      Dcm_DspServiceProcessingSts.ucRoeServiceRequest
          = DCM_FALSE;
      /* Transmit the response to the DSD layer */
      Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
    }
  }
  #endif
}
#endif

FUNC(boolean, DCM_CODE) Dcm_DemGetInternalTroubleCodeServiceMode(void)
{
  boolean mode;

  #if ((DCM_CLEAR_ITC_SERVICE_SUPPRT == STD_ON) ||\
       (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON))

  mode = Dcm_InternalTroubleCodeService;
  #else
  mode = DCM_FALSE;
  #endif
  
  return mode;
}

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Nesting of control structures to achieve better throughput. */
/* polyspace:end<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:end<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
/* polyspace:end<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */
/* polyspace:end<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace-end MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:10.4 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.2 [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:USELESS_WRITE [Not a defect:Low] "This condition is covered by configuration." */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-end CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-end CERT-C:DCL39-C [Justified:Low] "Dcm_SetProgConditions is call out and this function is user code . No impact" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
