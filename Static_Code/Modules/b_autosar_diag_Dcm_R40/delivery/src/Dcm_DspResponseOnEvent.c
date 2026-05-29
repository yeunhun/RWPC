/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE: Dcm_DspResponseOnEvent.c                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the definitions for UDS services           **
**              implemented by DSP layer of Dcm module                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision   Date          By                  Description                   **
********************************************************************************
** 2.3.2.0   05-Nov-2020   EunKyung Kim    #26432                             **
**                                                                            **
** 1.0.2      15-02-2017    Jin       Jung      #5460                         **
**                                                                            **
** 1.0.1      03-03-2016    Sungeol   Baek      #3754, RTRT reflection        **
**                                                                            **
** 1.0.0      09-01-2013    Autron              Initial Version               **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm_Ram.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_DspResponseOnEvent.h"
#include "Dcm_DspServices.h"
#include "Dcm_DslInternal.h"
#include "Rte_Dcm.h"
#include "NvM.h"
#include "Dcm_Config.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Dcm_DcmSetUpRoeEvent                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API is used to store serviceToRespondToRecord  **
**                        in the request message when the sub-function is     **
**                        equal to "ROE set up sub-functions"                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : eventTypeRecordLength                               **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GucRoeSTRTIndex,           **
**                                                                            **
**                        Function(s) invoked: None                           **
**                                                                            **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"
#if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmSetUpRoeEvent
(uint8 eventTypeRecordLength,
P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST) LpPduIdTable;
  #if(DCM_PROTOCOL_TRANSTYPE2 == STD_ON)
  P2CONST(Dcm_DslRoeTrans, AUTOMATIC, DCM_APPL_CONST) LpRoeTxId;
  #endif
  Dcm_MsgLenType LusReqLength;
  Dcm_MsgType LddReqDataPtr;
  Std_ReturnType LddReturnValue;
  uint8 LucDataCount;

  /* Initialize Return Value */
  LddReturnValue = E_OK;

  /* Check the serviceToRespondTo is full.
  This serviceToRespondTo is ignored - Vendor Specific Requirement */
  if(Dcm_GucRoeSTRTIndex >= DCM_ROE_STRT_SIZE)
  {
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    LusReqLength = pMsgContext->reqDataLen;
    LddReqDataPtr = pMsgContext->reqData;

    Dcm_GddRoeRequestInfo[Dcm_GucRoeSTRTIndex].ucEventWindowTime =
      LddReqDataPtr[DCM_ONE];

    Dcm_GddRoeRequestInfo[Dcm_GucRoeSTRTIndex].ddRoeRxPduId =
    Dcm_GddStartRoeRxPduId;

    Dcm_GddRoeRequestInfo[Dcm_GucRoeSTRTIndex].ucRxAddrType =
      pMsgContext->msgAddInfo.reqType;

    LpPduIdTable = &Dcm_GaaPduIdTableConfig[pMsgContext->dcmRxPduId];

    #if(DCM_PROTOCOL_TRANSTYPE2 == STD_ON)
    LpRoeTxId = LpPduIdTable->pRoeTxId;

    if(LpRoeTxId->blRoeTransType == DCM_ONE)
    {
      Dcm_GddRoeRequestInfo[Dcm_GucRoeSTRTIndex].ddRoeTxPduId =
       LpRoeTxId->ddRoeTxPduId;
    }
    else
    #endif
    {
      Dcm_GddRoeRequestInfo[Dcm_GucRoeSTRTIndex].ddRoeTxPduId =
        LpPduIdTable->ddTxPduId;
    }

    Dcm_GddRoeRequestInfo[Dcm_GucRoeSTRTIndex].ddRoeReqDataLen =
      LusReqLength - (DCM_TWO + eventTypeRecordLength);

    /* Check the length of serviceToRespondTo is bigger than max. value
     (vendor specific parameter)
    the length of serviceToRespondTo should be updated with the max. value
    (it may cause a negative respond when the event occured.) */
    if(Dcm_GddRoeRequestInfo[Dcm_GucRoeSTRTIndex].ddRoeReqDataLen >
      DCM_ROE_MAX_REQ_DATA_LEN)
    {
      Dcm_GddRoeRequestInfo[Dcm_GucRoeSTRTIndex].ddRoeReqDataLen =
        DCM_ROE_MAX_REQ_DATA_LEN;
    }

    for(LucDataCount = DCM_ZERO ;
      LucDataCount <
      Dcm_GddRoeRequestInfo[Dcm_GucRoeSTRTIndex].ddRoeReqDataLen ;
        LucDataCount++)
    {
      Dcm_GddRoeRequestInfo[Dcm_GucRoeSTRTIndex].RoeReqData[LucDataCount] =
        LddReqDataPtr
        [LucDataCount + DCM_TWO + eventTypeRecordLength];
    }

    /* Update the response data */
    pMsgContext->resData[DCM_ZERO] = LddReqDataPtr[DCM_ZERO];
    /* numberOfIdentifiedEvents is equal to zero when the event is set up */
    pMsgContext->resData[DCM_ONE] = DCM_ZERO;

    for(LucDataCount = DCM_ZERO ;
      LucDataCount < (LusReqLength - DCM_ONE) ; LucDataCount++)
    {
      pMsgContext->resData[LucDataCount + DCM_TWO] =
        LddReqDataPtr[LucDataCount + DCM_ONE];
    }

    pMsgContext->resDataLen = LusReqLength + DCM_ONE;

    /* Move to the next buffer */
    Dcm_GucRoeSTRTIndex++;
  }

  return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspDisableRoe                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is disable the activated      **
**                        ROE events and clear the transmission queue.        **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GucRoeSTRTIndex            **
**                                                                            **
**                        Function(s) invoked: DCM_ROE_STOP_FNC,              **
**                                             Dcm_DspClearQueue              **
**                                                                            **
*******************************************************************************/
#if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspDisableRoe(void)
{
  #if(DCM_EXTERNAL_ROE_ENABLED == STD_ON)
  P2CONST(Dcm_DIDParaConfig, AUTOMATIC, DCM_APPL_CONST) LpDIDConfig;
  #endif
  uint8 LucIndex;

  for(LucIndex = DCM_ZERO ; LucIndex < Dcm_GucRoeSTRTIndex ; LucIndex++)
  {
    if(Dcm_GddRoeRequestInfo[LucIndex].blIsRoeStarted == DCM_TRUE)
    {
      /* ROE Stop */
      Dcm_GddRoeRequestInfo[LucIndex].blIsRoeStarted = DCM_FALSE;

      /* Reset eventWindowTime Counter */
      Dcm_GddRoeRequestInfo[LucIndex].ucEventWindowTimeCounter = DCM_ZERO;

      /* Check if the request eventWindowTime is vehicleManufacturerSpecific */
      if(Dcm_GddRoeRequestInfo[LucIndex].ucEventWindowTime !=
        DCM_ROE_SPECIFIC_WINDOW_TIME)
      {
      /* MISRA Rule        : 14.2
    Message          : This statement has no side-effect - it can be removed
    Reason             : To avoid Un used variable warning.
    Verification       : However, part of the code
               is verified manually and
               it is not having any impact.
    */
      #ifdef DCM_ROE_STOP_FNC
        /* Call the configured Api */
        DCM_ROE_STOP_FNC(DCM_ROE_SPECIFIC_WINDOW_TIME);
      #endif

      }

      /* Check if the request is received for
      OnChangeOfDID and if the DID is externally managed */
      if(Dcm_GddRoeRequestInfo[LucIndex].blIsOnChngOfDIDRxed == DCM_TRUE)
      {

        #if(DCM_EXTERNAL_ROE_ENABLED == STD_ON)
                LpDIDConfig = &Dcm_GaaDIDParaConfig[
                      Dcm_GddRoeRequestInfo[LucIndex].usDIDIndex];
        /* Check if the request received for the DID is externally managed */
        if(LpDIDConfig->blDcmDspDidExtRoeEnabled == DCM_TRUE)
        {
          /* Invoke the function to deactivate the event */
          LpDIDConfig->pActivateEventFnc\
            (LpDIDConfig->ucDcmDspDidRoeEventId,  DCM_ROE_UNACTIVE);
        }
        #endif
      }

      if(Dcm_GddRoeRequestInfo[LucIndex].blIsOnDTCStsChngRxed == DCM_TRUE)
      {
        /* unactivate the DTC change supervision */
      }
    }
  }

  if(Dcm_DspServiceProcessingSts.ucRoeServiceRequest
              == DCM_TRUE)
  {

    #if(DCM_MAX_NO_OF_PRECONFIGURED_DID != DCM_ZERO)
    if(Dcm_GucRoeSTRTIndex > DCM_ZERO)
    {
      for(LucIndex = DCM_ZERO; LucIndex < Dcm_Max_No_Of_Preconfigured_Did;\
        LucIndex++)
      {
        if(Dcm_GddPreConfiguredDID[LucIndex].blRoeStarted == DCM_TRUE)
        {
         Dcm_GddPreConfiguredDID[LucIndex].blRoeStarted = DCM_FALSE;
         Dcm_GucRoeSTRTIndex--;
        }
          }
    }
   #endif
  }
  #if(DCM_ROE_QUEUE_ENABLED == STD_ON)
  /* clear transmission messages in QUEUE */
  if(Dcm_GddRoeQueueProcessInfo.blQueueEmpty == DCM_FALSE)
  {
    Dcm_DspClearQueue();
  }
  #endif

}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspReadROEDIDValue                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x22   **
**                        to Read the DID value from the Application          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : DIDIndex                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DIDSize, pBuffer                                    **
**                                                                            **
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : None                           **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
#if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspReadROEDIDValue(
          uint16 DIDIndex, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DIDSize,
          P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pBuffer)
{
  P2CONST(Dcm_DIDParaConfig, AUTOMATIC, DCM_APPL_DATA) LpDIDTAB;
  P2VAR(Dcm_DcmDspSignalconfig, AUTOMATIC, DCM_APPL_DATA) LpDcmDspSignal;
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) LpDcmDspData;
  P2CONST(Dcm_DataInfoType, AUTOMATIC, DCM_APPL_CONST) LpLengthInfo;
  Dcm_NegativeResponseCodeType LddErrorCode;
  Std_ReturnType LddReturnValue;
  uint8 LucSignalIndex;
  uint8 LucSignalCount;

  LddReturnValue = E_OK;

  LpDIDTAB = &Dcm_GaaDIDParaConfig[DIDIndex];
  LucSignalCount = LpDIDTAB->ucDcmDspSignalCount;
  LpDcmDspSignal = LpDIDTAB->pDcmDspSignal;

  /* TODO : Do verify */
  for(LucSignalIndex = DCM_ZERO; LucSignalIndex < LucSignalCount; LucSignalIndex++)
  {
    /*Get the configuration of Data's*/
    LpDcmDspData = LpDcmDspSignal->pDcmDspData;
    LpLengthInfo = LpDcmDspData->pDataInfo;

    LddReturnValue = E_OK;

    /* Get the DID size from the configured DID */
    *DIDSize = LpDcmDspData->usDcmDspDataSize;
    
    switch(LpDcmDspData->ucDcmDspDataUsePort)
    {
      case DCM_USE_DATA_ASYNCH_CLIENT_SERVER:
      case DCM_USE_DATA_ASYNCH_FNC:
        if (NULL_PTR != LpDcmDspData->pConditionCheckReadAsync)
        {
          LddReturnValue = LpDcmDspData->pConditionCheckReadAsync(Dcm_GddOpStatus, &LddErrorCode);
        } 
        if (E_OK == LddReturnValue)
        {
          /* Invoke ReadDataLength function to get the length of the DID with variable Length */
          if (DCM_FALSE == LpLengthInfo->blDataFixedLength)
          {
            if (NULL_PTR != LpDcmDspData->pReadDataLengthAsync)
            {
              LddReturnValue = LpDcmDspData->pReadDataLengthAsync(Dcm_GddOpStatus, DIDSize);
            }
            else
            {
              LddReturnValue = E_NOT_OK;
            }
          }
          
          if (E_OK == LddReturnValue)
          {
            /* TODO : if func is null. what kinds of error shall we return */
            if (NULL_PTR != LpDcmDspData->pReadDataAsync)
            {
              LddReturnValue = LpDcmDspData->pReadDataAsync(Dcm_GddOpStatus, pBuffer);
            }
          }
        }

        break;

      case DCM_USE_DATA_SYNCH_FNC:
      case DCM_USE_DATA_SYNCH_CLIENT_SERVER:
        if (NULL_PTR != LpDcmDspData->pConditionCheckReadSync)
        {
          LddReturnValue = LpDcmDspData->pConditionCheckReadSync(&LddErrorCode);
        }
          
        if (E_OK == LddReturnValue)
        {
          /* Invoke ReadDataLength function to get the length of the DID with variable Length */
          if (DCM_FALSE == LpLengthInfo->blDataFixedLength)
          {
            if (NULL_PTR != LpDcmDspData->pReadDataLengthSync)
            {
              LddReturnValue = LpDcmDspData->pReadDataLengthSync(DIDSize);
            }
          }
          
          if (E_OK == LddReturnValue)
          {
            if (NULL_PTR != LpDcmDspData->pReadDataSync)
            {
              LddReturnValue = LpDcmDspData->pReadDataSync(pBuffer);
            }
          }
        }

        break;

      case DCM_USEECUSIGNAL:
      {
        uint8 i = LpDcmDspData->ucEcuSignalFunctionIndex;

        switch(LpDcmDspData->ucDcmDspDataType)
        {
          case DCM_DSP_DATA_TYPE_UINT8:
            if (NULL_PTR != Dcm_GaaEcuSignalUint8Func[i].pDataReadEcuSignalUint8)
            {
              Dcm_GaaEcuSignalUint8Func[i].pDataReadEcuSignalUint8(pBuffer);
            }
            break;
          case DCM_DSP_DATA_TYPE_UINT16:
            if (NULL_PTR != Dcm_GaaEcuSignalUint16Func[i].pDataReadEcuSignalUint16)
            {
              Dcm_GaaEcuSignalUint16Func[i].pDataReadEcuSignalUint16((P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA))pBuffer);
            }
            break;
          case DCM_DSP_DATA_TYPE_UINT32:
            if (NULL_PTR != Dcm_GaaEcuSignalUint32Func[i].pDataReadEcuSignalUint32)          
            {
              Dcm_GaaEcuSignalUint32Func[i].pDataReadEcuSignalUint32((P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA))pBuffer);
            }
            break;
          case DCM_DSP_DATA_TYPE_SINT8:
            if (NULL_PTR != Dcm_GaaEcuSignalSint8Func[i].pDataReadEcuSignalSint8)
            {
              Dcm_GaaEcuSignalSint8Func[i].pDataReadEcuSignalSint8((P2VAR(sint8, AUTOMATIC, DCM_APPL_DATA))pBuffer);
            }
            break;
          case DCM_DSP_DATA_TYPE_SINT16:
            if (NULL_PTR != Dcm_GaaEcuSignalSint16Func[i].pDataReadEcuSignalSint16)
            {
              Dcm_GaaEcuSignalSint16Func[i].pDataReadEcuSignalSint16((P2VAR(sint16, AUTOMATIC, DCM_APPL_DATA))pBuffer);
            }
            break;
          case DCM_DSP_DATA_TYPE_SINT32:
            if (NULL_PTR != Dcm_GaaEcuSignalSint32Func[i].pDataReadEcuSignalSint32)
            {
              Dcm_GaaEcuSignalSint32Func[i].pDataReadEcuSignalSint32((P2VAR(sint32, AUTOMATIC, DCM_APPL_DATA))pBuffer);
            }
            break;
          default:
            break;
        }
        break;
      }
      default:
        break;      
    }
  }
  return (LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspEnableRoe                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is enable ROE events.         **
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
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GucRoeSTRTIndex            **
**                                             Dcm_GddNegRespError            **
**                                                                            **
**                        Function(s) invoked: Dcm_DspReadROEDIDValue,        **
**                                             DCM_ROE_INIT_FNC               **
**                                                                            **
*******************************************************************************/
#if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspEnableRoe(void)
{

  #if(DCM_EXTERNAL_ROE_ENABLED == STD_ON)
  P2CONST(Dcm_DIDParaConfig, AUTOMATIC, DCM_APPL_CONST) LpDIDConfig;
  #endif
  Std_ReturnType LddReturnValue;
  uint8 LucIndex;

  LddReturnValue = E_OK;

  for(LucIndex = DCM_ZERO ; LucIndex < Dcm_GucRoeSTRTIndex ; LucIndex++)
  {
    if(Dcm_GddRoeRequestInfo[LucIndex].blIsOnChngOfDIDRxed == DCM_TRUE)
    {
      /* If DID is managed internally, get the initial value */
      if(Dcm_GddRoeRequestInfo[LucIndex].blIsDIDManagedInternally == DCM_TRUE)
      {
        Dcm_GddRoeRequestInfo[LucIndex].blDIDValueInit =
          Dcm_DspReadROEDIDValue(Dcm_GddRoeRequestInfo[LucIndex].usDIDIndex,
            &Dcm_GddRoeRequestInfo[LucIndex].usDIDValueSize,
              &Dcm_GddRoeRequestInfo[LucIndex].ucInternalBuffer[DCM_ZERO]);
      }

      #if(DCM_EXTERNAL_ROE_ENABLED == STD_ON)
      LpDIDConfig = &Dcm_GaaDIDParaConfig[
                      Dcm_GddRoeRequestInfo[LucIndex].usDIDIndex];

      /* Check if the request is received for OnChangeOfDID
      and if the DID is externally managed */
      if(LpDIDConfig->blDcmDspDidExtRoeEnabled == DCM_TRUE)
      {
        /* Invoke the function to deactivate the event */
        LddReturnValue = LpDIDConfig->pActivateEventFnc(
          LpDIDConfig->ucDcmDspDidRoeEventId, DCM_ROE_ACTIVE);
          if(LddReturnValue != E_OK)
        {
          /* Update the NRC value */
          Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
        }
      }
      #endif
    }

    /* Check if the request eventWindowTime is vehicleManufacturerSpecific */
    if(Dcm_GddRoeRequestInfo[LucIndex].ucEventWindowTime !=
      DCM_ROE_SPECIFIC_WINDOW_TIME)
    {
    /* MISRA Rule        : 14.2
    Message          : This statement has no side-effect - it can be removed
    Reason             : To avoid Un used variable warning.
    Verification       : However, part of the code
               is verified manually and
               it is not having any impact.
    */
    #ifdef DCM_ROE_INIT_FNC
      /* Call the configured Api */
      DCM_ROE_INIT_FNC(Dcm_GddRoeRequestInfo[LucIndex].ucEventWindowTime);
    #endif
    }

    if(Dcm_GddRoeRequestInfo[LucIndex].blIsRoeStarted == DCM_FALSE)
    {
      Dcm_GddRoeRequestInfo[LucIndex].blIsRoeStarted = DCM_TRUE;

      /* Reset eventWindowTimeCounter */
      Dcm_GddRoeRequestInfo[LucIndex].ucEventWindowTimeCounter = DCM_ZERO;

      Dcm_GddRoeRequestInfo[LucIndex].ddRoeRxPduId = Dcm_GddStartRoeRxPduId;
      /* if the sub-function is equal to onTimeInterrupt, reset timeMask */
      if(Dcm_GddRoeRequestInfo[LucIndex].blIsOnTimeInterruptRxed == DCM_TRUE)
      {
        Dcm_GddRoeRequestInfo[LucIndex].ucTimeMaskCounter = DCM_ZERO;
      }
    }
  }

  return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspResetRoe                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked to reset the       **
**                        variables related to ROE.                           **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GucRoeSTRTIndex            **
**                                             Dcm_GucResOnEventStatus        **
**                                                                            **
**                        Function(s) invoked: None                           **
**                                                                            **
*******************************************************************************/
#if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspResetRoe(void)
{
  uint8 LucIndex;
  uint8 LusMaxDataCount;

  for(LucIndex = DCM_ZERO ; LucIndex < Dcm_GucRoeSTRTIndex ; LucIndex++)
  {
    Dcm_GddRoeRequestInfo[LucIndex].blIsRoeStarted = DCM_FALSE;
    Dcm_GddRoeRequestInfo[LucIndex].blIsOnDTCStsChngRxed = DCM_FALSE;
    Dcm_GddRoeRequestInfo[LucIndex].ucStatusMask = DCM_ZERO;
    Dcm_GddRoeRequestInfo[LucIndex].blIsOnTimeInterruptRxed = DCM_FALSE;
    Dcm_GddRoeRequestInfo[LucIndex].ucTimeMask = DCM_ZERO;
    Dcm_GddRoeRequestInfo[LucIndex].ucTimeMaskCounter = DCM_ZERO;
    Dcm_GddRoeRequestInfo[LucIndex].blIsOnChngOfDIDRxed = DCM_FALSE;
    Dcm_GddRoeRequestInfo[LucIndex].usDIDIndex = DCM_ZERO;
    Dcm_GddRoeRequestInfo[LucIndex].usDIDValue = DCM_ZERO;
    Dcm_GddRoeRequestInfo[LucIndex].blIsDIDManagedInternally = DCM_FALSE;
    Dcm_GddRoeRequestInfo[LucIndex].usDIDValueSize = DCM_ZERO;
    Dcm_GddRoeRequestInfo[LucIndex].blDIDValueInit = DCM_FALSE;
    Dcm_GddRoeRequestInfo[LucIndex].ucNumOfIdentifiedEvents = DCM_ZERO;
    Dcm_GddRoeRequestInfo[LucIndex].ucEventWindowTime = DCM_ZERO;
    Dcm_GddRoeRequestInfo[LucIndex].ucEventWindowTimeCounter = DCM_ZERO;
    Dcm_GddRoeRequestInfo[LucIndex].ddRoeRxPduId = DCM_ZERO;
    Dcm_GddRoeRequestInfo[LucIndex].ddRoeTxPduId = DCM_ZERO;
    Dcm_GddRoeRequestInfo[LucIndex].ddRoeReqDataLen = DCM_ZERO;
    Dcm_GddRoeRequestInfo[LucIndex].ucRxAddrType = DCM_ZERO;

    for(LusMaxDataCount = DCM_ZERO ;
      LusMaxDataCount < Dcm_GddRoeRequestInfo[LucIndex].ddRoeReqDataLen ;
        LusMaxDataCount++)
    {
      Dcm_GddRoeRequestInfo[LucIndex].RoeReqData[LusMaxDataCount] = DCM_ZERO;
    }

    Dcm_GddRoeRequestInfo[LucIndex].ddRoeReqDataLen = DCM_ZERO;
  }

  Dcm_GucRoeSTRTIndex = DCM_ZERO;

  Dcm_GucResOnEventStatus = DCM_IDLE;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspClearQueue                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked to clear the ROE   **
**                        queue event messages and to reset all the variables **
**                        related to ROE queue.                               **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : None                           **
**                                                                            **
**                        Function(s) invoked: None                           **
**                                                                            **
*******************************************************************************/
#if(DCM_ROE_QUEUE_ENABLED == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspClearQueue(void)
{
  Dcm_GddRoeQueueProcessInfo.blQueueElementInProcess = DCM_FALSE;
  Dcm_GddRoeQueueProcessInfo.blQueueEmpty = DCM_TRUE;
  Dcm_GddRoeQueueProcessInfo.QueueReadIndex = DCM_ZERO;
  Dcm_GddRoeQueueProcessInfo.QueueWriteIndex = DCM_ZERO;
  /* Clear Retry Information */
  Dcm_GddRoeRetryProcessInfo.ucRoeTxRetryCount = DCM_ZERO;
  Dcm_GddRoeRetryProcessInfo.blRetryRoeEvent = DCM_FALSE;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmResponseOnEvent                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The ResponseOnEvent service starts or stops the     **
**                        transmission of responses on a specified Event.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GucRoeSTRTIndex            **
**                                             Dcm_GddNegRespError            **
**                                                                            **
**                        Function(s) invoked: Dcm_DspDisableRoe,             **
**                                             Dcm_DcmSetUpRoeEvent,          **
**                                             Dcm_IDSearch,                  **
**                                             Dcm_DspEnableRoe,              **
**                                             Dcm_DspResetRoe,               **
**                                             Dcm_DspClearQueue              **
**                                                                            **
*******************************************************************************/
#if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmResponseOnEvent(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Dcm_MsgLenType LusReqLength;
  Dcm_MsgType LddReqDataPtr;
  uint8 LucSubFunction;
  uint16 LusDIDIndex;
  uint16 LusDIDValue;
  uint8 LucEventWindowTime;
  uint8 LucIndex;
  uint8 LucNumOfActivatedEvents;
  uint8 LucActEventRspMsgIndex;
  uint8 LucCount;
  #if(DCM_MAX_NO_OF_PRECONFIGURED_DID != DCM_ZERO)
  uint8 LucStoreBit;
  uint8 LucDidCount;
  uint8 LucRoeCount;
  boolean LblDidFound;
  #endif
  Std_ReturnType LddEventSet;

  #if(DCM_MAX_NO_OF_PRECONFIGURED_DID != DCM_ZERO)
  /* Initialize LucNumOfIdentifiedEvents */
  LblDidFound = DCM_FALSE;
  LucRoeCount = DCM_ZERO;
  #endif

  LusReqLength = pMsgContext->reqDataLen;
  LddReqDataPtr = pMsgContext->reqData;

  LucEventWindowTime = LddReqDataPtr[DCM_ONE];

  Dcm_GddNegRespError = DCM_FALSE;

  /* Check the length of request message */
  if(LusReqLength < DCM_ROE_MIN_ROE_REQ_MSG_LEN)
  {
    /* Update the NRC value */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  {
    /* Check the TimeWindowTime is valid */
    if((LucEventWindowTime < DCM_TWO) ||
      (LucEventWindowTime > DCM_SUBFUNCTION_MASK))
    {
      /* Update the NRC value */
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    }
    else
    {
      /* Check the subfunction value */
      LucSubFunction =
        (uint8)(LddReqDataPtr[DCM_ZERO] & (DCM_ROE_SUBFUNCTION_MASK));

      #if(DCM_MAX_NO_OF_PRECONFIGURED_DID != DCM_ZERO)
      LucStoreBit = (uint8)(LddReqDataPtr[DCM_ZERO] & (DCM_ROE_STORE_BIT_MASK));
      #endif

      switch(LucSubFunction)
      {
        /* Sub-function parameter is equal to "stopResponseOnEvent". (0x00) */
        case DCM_STOP_ROE:
          if((LusReqLength == DCM_ONE) || (LusReqLength == DCM_TWO))
          {
            Dcm_DspServiceProcessingSts.ucRoeServiceRequest
              = DCM_TRUE;
            /* Update the response data */
            pMsgContext->resData[DCM_ZERO] = LddReqDataPtr[DCM_ZERO];
            pMsgContext->resData[DCM_ONE] = DCM_ZERO;
            pMsgContext->resData[DCM_TWO] = LucEventWindowTime;
            pMsgContext->resDataLen = DCM_THREE;
            Dcm_GddStartRoeRxPduId = DCM_ZERO;
            Dcm_DspDisableRoe();
            #if(DCM_MAX_NO_OF_PRECONFIGURED_DID != DCM_ZERO)
            if(LucStoreBit == DCM_ROE_STORE_BIT_MASK)
            {
              Dcm_StoreRoeEvent();
              Dcm_DspServiceProcessingSts.ucRoeStoreRequest = DCM_TRUE;
            }
            #endif
          }
          else
          {
            /* Update the NRC value */
            Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
          }
        break;

        /* Sub-function parameter is equal to "onDTCStatusChange". (0x01) */
        case DCM_ON_DTC_STATUS_CHANGE:
          if(LusReqLength >= (DCM_TWO + DCM_ROE_ETR_LEN_ONDTCS +
              DCM_ROE_MIN_STRTR_REQ_MSG_LEN))
          {
            LddEventSet =
              Dcm_DcmSetUpRoeEvent(DCM_ROE_ETR_LEN_ONDTCS, pMsgContext);

            if(LddEventSet == E_OK)
            {
              Dcm_GddRoeRequestInfo
              [(Dcm_GucRoeSTRTIndex - DCM_ONE)].blIsOnDTCStsChngRxed = DCM_TRUE;

              Dcm_GddRoeRequestInfo
                [(Dcm_GucRoeSTRTIndex - DCM_ONE)].ucStatusMask =
                  LddReqDataPtr[DCM_TWO];
            }
            else
            {
              /* Update the NRC value */
              Dcm_GddNegRespError = DCM_E_GENERALREJECT;
            }
          }
          else
          {
            /* Update the NRC value */
            Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
          }
        break;

        /* Sub-function parameter is equal to "onTimeInterrupt". (0x02) */
        case DCM_ON_TIME_INTERRUPT:
          if(LusReqLength >= (DCM_TWO + DCM_ROE_ETR_LEN_OTI +
            DCM_ROE_MIN_STRTR_REQ_MSG_LEN))
          {
            LddEventSet =
              Dcm_DcmSetUpRoeEvent(DCM_ROE_ETR_LEN_OTI, pMsgContext);

            if(LddEventSet == E_OK)
            {
              Dcm_GddRoeRequestInfo
                [(Dcm_GucRoeSTRTIndex - DCM_ONE)].blIsOnTimeInterruptRxed =
                  DCM_TRUE;

              Dcm_GddRoeRequestInfo
                [(Dcm_GucRoeSTRTIndex - DCM_ONE)].ucTimeMask =
                  LddReqDataPtr[DCM_TWO];
            }
            else
            {
              /* Update the NRC value */
              Dcm_GddNegRespError = DCM_E_GENERALREJECT;
            }
          }
          else
          {
            /* Update the NRC value */
            Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
          }
        break;

        /* Sub-function parameter is equal to "onChangeOfDataIdentifier"(0x03)*/
        case DCM_ON_CHANGE_OF_DID:
          if(LusReqLength >= (DCM_TWO + DCM_ROE_ETR_LEN_OTI +
              DCM_ROE_MIN_STRTR_REQ_MSG_LEN))
          {
            /* MISRA Rule       : 12.8
               Message          : Right operand of shift operator is greater
                                  than or
                                  equal to the width of the underlying type .
               Reason           : Right operand of shift operators used to
                                  achieve better throughput
               Verification     : However, part of the code
                                  is verified manually and
                                  it is not having any impact.
            */
            /* Update Identifier from the request buffer */
            LusDIDValue =
             (LddReqDataPtr[DCM_TWO] << DCM_EIGHT) | (LddReqDataPtr[DCM_THREE]);

            /* If DID in the request is configured */
            if(Dcm_IDSearch(DCM_GET_DID, LusDIDValue, &LusDIDIndex) == DCM_TRUE)
            {
              LddEventSet =
                Dcm_DcmSetUpRoeEvent(DCM_ROE_ETR_LEN_OCODID, pMsgContext);

              if(LddEventSet == E_OK)
              {
                Dcm_GddRoeRequestInfo
                  [(Dcm_GucRoeSTRTIndex - DCM_ONE)].usDIDIndex = LusDIDIndex;

                Dcm_GddRoeRequestInfo
                  [(Dcm_GucRoeSTRTIndex - DCM_ONE)].usDIDValue = LusDIDValue;

                Dcm_GddRoeRequestInfo
                  [(Dcm_GucRoeSTRTIndex - DCM_ONE)].blIsOnChngOfDIDRxed =
                    DCM_TRUE;

                Dcm_GddRoeRequestInfo
                  [(Dcm_GucRoeSTRTIndex - DCM_ONE)].blIsDIDManagedInternally =
                    DCM_TRUE;

                #if(DCM_EXTERNAL_ROE_ENABLED == STD_ON)
                if(Dcm_GaaDIDParaConfig[LusDIDIndex].blDcmDspDidExtRoeEnabled ==
                  DCM_TRUE)
                {
                  Dcm_GddRoeRequestInfo
                    [(Dcm_GucRoeSTRTIndex - DCM_ONE)].blIsDIDManagedInternally =
                      DCM_FALSE;
                }
                #endif
                #if(DCM_MAX_NO_OF_PRECONFIGURED_DID != DCM_ZERO)
                if(Dcm_GaaDIDParaConfig[LusDIDIndex].blPreConfigEnabled == DCM_TRUE)
                {
                  for(LucDidCount = DCM_ZERO; LucDidCount < Dcm_GucPreConfigRoeDidIndex;
                    LucDidCount++)
                  {
                    if(Dcm_GddPreConfiguredDID[LucDidCount].usDidValue == LusDIDValue)
                    {
                      LblDidFound = DCM_TRUE;
                    }
                  }
                  if(LblDidFound == DCM_FALSE)
                  {
                    Dcm_GddPreConfiguredDID[Dcm_GucPreConfigRoeDidIndex].usDidValue =
                      LusDIDValue;
                    Dcm_GddPreConfiguredDID[Dcm_GucPreConfigRoeDidIndex].
                    usRxPduIdValue = (uint16)pMsgContext->dcmRxPduId;
                    Dcm_GddPreConfiguredDID[Dcm_GucPreConfigRoeDidIndex].
                    usEventWindowTime  = (uint16)LddReqDataPtr[DCM_ONE];

                    Dcm_GucPreConfigRoeDidIndex++;
                  }
                }
                #endif
              }
              else
              {
                /* Update the NRC value */
                Dcm_GddNegRespError = DCM_E_GENERALREJECT;
              }
            }
            else
            {
              /* Report the Request out of range NRC */
              Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
            }
          }
          else
          {
            /* Update the NRC value */
            Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
          }
        break;

        /* Sub-function parameter is equal to "reportActivateEvents". (0x04) */
        case DCM_REPORT_ACTIVATED_EVENTS:
          if((LusReqLength == DCM_ONE) || (LusReqLength == DCM_TWO))
          {
            /* Initialize numberOfActivatedEents */
            LucNumOfActivatedEvents = DCM_ZERO;

            /* Initialize Response Message Index */
            LucActEventRspMsgIndex = DCM_ZERO;

            for(LucIndex = DCM_ZERO ; LucIndex < Dcm_GucRoeSTRTIndex ;
              LucIndex++)
            {
              if(Dcm_GddRoeRequestInfo[LucIndex].blIsRoeStarted == DCM_TRUE)
              {
                /* Check ROE Set up Sub-function */
                if(((Dcm_GddRoeRequestInfo[LucIndex].blIsOnDTCStsChngRxed) ||
                (Dcm_GddRoeRequestInfo[LucIndex].blIsOnTimeInterruptRxed) ||
                (Dcm_GddRoeRequestInfo[LucIndex].blIsOnChngOfDIDRxed)) ==
                  DCM_FALSE)
                {
                  /* Do Nothing */
                }
                else
                {
                  /* Count up numberOfActivatedEents */
                  LucNumOfActivatedEvents++;

                  /* MISRA Rule      : 1.1
                  Message            : Nesting of control structures
                                       (statements) exceeds 15
                  Reason             : The if loops are required
                  Verification       : However, part of the code
                                       is verified manually and
                                       it is not having any impact.
                  */
                  if(Dcm_GddRoeRequestInfo[LucIndex].blIsOnDTCStsChngRxed ==
                    DCM_TRUE)
                  {
                    if(Dcm_DspServiceProcessingSts.
                                           ucRoeStoreRequest == DCM_TRUE)
                    {
                      pMsgContext->resData[LucActEventRspMsgIndex + DCM_TWO] =
                        DCM_ON_DTC_STATUS_CHANGE_STOREBIT;
                    }
                    else
                    {
                      pMsgContext->resData[LucActEventRspMsgIndex + DCM_TWO] =
                        DCM_ON_DTC_STATUS_CHANGE;
                    }
                    /* The time remaining */
                    pMsgContext->resData
                      [LucActEventRspMsgIndex + DCM_TWO + DCM_ONE] =
                        Dcm_GddRoeRequestInfo[LucIndex].ucEventWindowTime;
                    pMsgContext->resData
                      [LucActEventRspMsgIndex + DCM_TWO + DCM_TWO] =
                        Dcm_GddRoeRequestInfo[LucIndex].ucStatusMask;

                    LucActEventRspMsgIndex = LucActEventRspMsgIndex + DCM_THREE;
                  }
                  /* MISRA Rule      : 1.1
                  Message            : Nesting of control structures
                                       (statements) exceeds 15
                  Reason             : The if loops are required
                  Verification       : However, part of the code
                                       is verified manually and
                                       it is not having any impact.
                  */
                  else if(Dcm_GddRoeRequestInfo
                    [LucIndex].blIsOnTimeInterruptRxed == DCM_TRUE)
                  {
                    if(Dcm_DspServiceProcessingSts.
                      ucRoeStoreRequest == DCM_TRUE)
                    {
                      pMsgContext->resData[LucActEventRspMsgIndex + DCM_TWO] =
                        DCM_ON_TIME_INTERRUPT_STOREBIT;
                    }
                    else
                    {
                      pMsgContext->resData[LucActEventRspMsgIndex + DCM_TWO] =
                        DCM_ON_TIME_INTERRUPT;
                    }
                    /* The time remaining */
                    pMsgContext->resData
                      [LucActEventRspMsgIndex + DCM_TWO + DCM_ONE] =
                        Dcm_GddRoeRequestInfo[LucIndex].ucEventWindowTime;
                    pMsgContext->resData
                      [LucActEventRspMsgIndex + DCM_TWO + DCM_TWO] =
                        Dcm_GddRoeRequestInfo[LucIndex].ucTimeMask;

                    LucActEventRspMsgIndex = LucActEventRspMsgIndex + DCM_THREE;
                  }
                  else
                  {
                    if(Dcm_DspServiceProcessingSts.
                         ucRoeStoreRequest == DCM_TRUE)
                    {
                      pMsgContext->resData[LucActEventRspMsgIndex + DCM_TWO] =
                        DCM_ON_CHANGE_OF_DID_STOREBIT;
                    }
                    else
                    {
                      pMsgContext->resData[LucActEventRspMsgIndex + DCM_TWO] =
                        DCM_ON_CHANGE_OF_DID;
                    }
                    /* The time remaining */
                    pMsgContext->resData
                      [LucActEventRspMsgIndex + DCM_TWO + DCM_ONE] =
                        Dcm_GddRoeRequestInfo[LucIndex].ucEventWindowTime;
                    pMsgContext->resData
                      [LucActEventRspMsgIndex + DCM_TWO + DCM_TWO] =
                      (uint8)(Dcm_GddRoeRequestInfo[LucIndex].usDIDValue >>
                        DCM_EIGHT);
                    pMsgContext->resData
                      [LucActEventRspMsgIndex + DCM_TWO + DCM_THREE] =
                        (uint8)(Dcm_GddRoeRequestInfo[LucIndex].usDIDValue);

                    LucActEventRspMsgIndex = LucActEventRspMsgIndex + DCM_FOUR;
                  }

                  /* MISRA Rule        : 1.1
                    Message            : Nesting of control structures
                                        (statements) exceeds 15
                    Reason             : The if loops are required
                    Verification       : However, part of the code
                                         is verified manually and
                                         it is not having any impact.
                   */
                  for(LucCount = DCM_ZERO ;
                    LucCount < Dcm_GddRoeRequestInfo[LucIndex].ddRoeReqDataLen ;
                      LucCount++)
                  {
                    pMsgContext->resData
                      [LucActEventRspMsgIndex + DCM_TWO] =
                        Dcm_GddRoeRequestInfo[LucIndex].RoeReqData[LucCount];
                    LucActEventRspMsgIndex++;
                  }
                }
              }
            }

            /* Update the response data */
            pMsgContext->resData[DCM_ZERO] = DCM_REPORT_ACTIVATED_EVENTS;
            pMsgContext->resData[DCM_ONE] = LucNumOfActivatedEvents;

            pMsgContext->resDataLen = LucActEventRspMsgIndex + DCM_TWO;
          }
          else
          {
            /* Update the NRC value */
            Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
          }
        break;

        /* Sub-function parameter is equal to "startResponseOnEvent". (0x05) */
        case DCM_START_ROE:
          if((LusReqLength == DCM_ONE) || (LusReqLength == DCM_TWO))
          {

            Dcm_GddStartRoeRxPduId = pMsgContext->dcmRxPduId;
            #if(DCM_MAX_NO_OF_PRECONFIGURED_DID != DCM_ZERO)
            for(LucIndex = DCM_ZERO; LucIndex < Dcm_Max_No_Of_Preconfigured_Did;
                                                                  LucIndex++)
            {
              if(Dcm_GddPreConfiguredDID[LucIndex].blRoeStarted == DCM_FALSE)
              {
                Dcm_GddPreConfiguredDID[LucIndex].blRoeStarted = DCM_TRUE;
              }
              else
              {
                LucRoeCount++;
              }
            }
            if((Dcm_DspServiceProcessingSts.ucRoeStartReqRxed == DCM_FALSE) \
              && (LucRoeCount == DCM_ZERO))
            {
              Dcm_RetrieveStoredRoeEvent(Dcm_GddStartRoeRxPduId);
            }
            if(LucStoreBit == DCM_ROE_STORE_BIT_MASK)
            {
              Dcm_StoreRoeEvent();
                Dcm_DspServiceProcessingSts.ucRoeStoreRequest = DCM_TRUE;
            }
            #endif

            if(Dcm_DspServiceProcessingSts.ucRoeStorePending == DCM_FALSE)
            {
              LddEventSet = Dcm_DspEnableRoe();
            }
            else
            {
              LddEventSet = E_OK;
            }

            if(LddEventSet == E_OK)
            {
              /* Update the response data */
              pMsgContext->resData[DCM_ZERO] = LddReqDataPtr[DCM_ZERO];
              pMsgContext->resData[DCM_ONE] = DCM_ZERO;
              pMsgContext->resData[DCM_TWO] = LddReqDataPtr[DCM_ONE];
              pMsgContext->resDataLen = DCM_THREE;
            }
          }
          else
          {
            /* Update the NRC value */
            Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
          }
          Dcm_DspServiceProcessingSts.ucRoeServiceRequest
          = DCM_TRUE;
        break;

        /* Sub-function parameter is equal to "clearResponseOnEvent". (0x06) */
        case DCM_CLEAR_ROE:
          Dcm_DspResetRoe();

          #if(DCM_ROE_QUEUE_ENABLED == STD_ON)
          /* If Queue is not empty, clear data in the queue. */
          if(Dcm_GddRoeQueueProcessInfo.blQueueEmpty != DCM_TRUE)
          {
            Dcm_DspClearQueue();
          }
          #endif

          /* Update the response data */
          pMsgContext->resData[DCM_ZERO] = DCM_CLEAR_ROE;
          pMsgContext->resData[DCM_ONE] = DCM_ZERO;
          pMsgContext->resData[DCM_TWO] = LucEventWindowTime;
          pMsgContext->resDataLen = DCM_THREE;
        break;

        default:
          Dcm_GddNegRespError = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        break;
      }
    }
  }
  if(Dcm_DspServiceProcessingSts.ucRoeStorePending == DCM_FALSE)
  {
    Dcm_DspServiceProcessingSts.ucRoeServiceRequest = DCM_FALSE;

    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspSetQueueIndex                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked to queue the ROE   **
**                        event messages when an ROE Event is ongoing and     **
**                        another Roe Event occurs.                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : QueueMode                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : None                           **
**                                                                            **
**                        Function(s) invoked: None                           **
**                                                                            **
*******************************************************************************/
#if(DCM_ROE_QUEUE_ENABLED == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspSetQueueIndex(boolean QueueMode)
{
  /* Write */
  if(QueueMode == DCM_ROE_QUEUE_WRITE)
  {
    /* check Queue is full */
    if((Dcm_GddRoeQueueProcessInfo.QueueWriteIndex) ==
      (Dcm_GddRoeQueueProcessInfo.QueueReadIndex) &&
        (Dcm_GddRoeQueueProcessInfo.blQueueEmpty == DCM_FALSE))
    {
      /* Drop the oldest event from the queue to make space for the new event */
      Dcm_GddRoeQueueProcessInfo.QueueReadIndex++;

      if(Dcm_GddRoeQueueProcessInfo.QueueReadIndex == Dcm_ROE_Max_Queue_Length)
      {
        Dcm_GddRoeQueueProcessInfo.QueueReadIndex = DCM_ZERO;
      }
    }

    /* Queue is not empty */
    if(Dcm_GddRoeQueueProcessInfo.blQueueEmpty == DCM_TRUE)
    {
      Dcm_GddRoeQueueProcessInfo.blQueueEmpty = DCM_FALSE;
    }

    /* Count-up Queue Write Index */
    Dcm_GddRoeQueueProcessInfo.QueueWriteIndex++;

    if(Dcm_GddRoeQueueProcessInfo.QueueWriteIndex == Dcm_ROE_Max_Queue_Length)
    {
      Dcm_GddRoeQueueProcessInfo.QueueWriteIndex = DCM_ZERO;
    }

  }

  /* Read */
  else
  {
    Dcm_GddRoeQueueProcessInfo.QueueReadIndex++;

    if(Dcm_GddRoeQueueProcessInfo.QueueReadIndex == Dcm_ROE_Max_Queue_Length)
    {
      Dcm_GddRoeQueueProcessInfo.QueueReadIndex = DCM_ZERO;
    }

    /* check queue is empty */
    if((Dcm_GddRoeQueueProcessInfo.QueueWriteIndex) ==
      (Dcm_GddRoeQueueProcessInfo.QueueReadIndex))
    {
      Dcm_GddRoeQueueProcessInfo.blQueueEmpty= DCM_TRUE;
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspQueueRoeEvents                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked to queue the ROE   **
**                        event messages when an ROE Event is ongoing and     **
**                        another Roe Event occurs.                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : IdIndex                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddEventInQueue                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GblRoeQueueOngoing,        **
**                                             Dcm_GddNegRespError            **
**                                                                            **
**                        Function(s) invoked: Dcm_DsdSIdIndex,               **
**                                             Dcm_DsdValidateSession,        **
**                                             Dcm_DsdValidateSecurity,       **
**                                             Dcm_DspSetQueueIndex           **
**                                                                            **
*******************************************************************************/
#if(DCM_ROE_QUEUE_ENABLED == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspQueueRoeEvents(uint8 IdIndex)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBufferId;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpRxBufferId;
  VAR(Dcm_NegativeResponseCodeType, DCM_APPL_DATA) LddNegRespError;
  P2CONST(Dcm_ServiceIdConfigType, AUTOMATIC, DCM_APPL_CONST) LpSIDTAB;
  Std_ReturnType LddEventInQueue;
  uint8 LucSID;
  uint8 LucSIDIndex;
  uint8 LucreqType;
  boolean LblSearchResult;
  boolean LblErrorOccured;

  /* Copy the Global Variable in a Local Variable
  and initialize it.
  (it will be returned at the end of this function) */
  LddNegRespError = Dcm_GddNegRespError;
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  LblErrorOccured = DCM_FALSE;

  /* Initialize pointer to the Rx buffer Id */
  LpRxBufferId = &Dcm_GddRoeRequestInfo[IdIndex].RoeReqData[DCM_ZERO];

  /* Initialize pointer to the Rx buffer Id */
  LpTxBufferId =
    &Dcm_GaaRoeQueueInfo
      [Dcm_GddRoeQueueProcessInfo.QueueWriteIndex].aaRoeQueueBuffer[DCM_ZERO];

  /* Initialize the addressing type for the requested RxPduId */
  LucreqType = Dcm_GddRoeRequestInfo[IdIndex].ucRxAddrType;

  /* Get the Service Id from the first byte of the Rx buffer */
  LucSID = LpRxBufferId[DCM_ZERO];

  LucSIDIndex = Dcm_DsdSIdIndex(LucSID);

  /* Check is service Id configured in the service Id table */
  if(LucSIDIndex != DCM_SERVICE_NOT_CONFIGURED)
  {
    /* Initialize pointer to the parameters of requested service Id*/
    LpSIDTAB = &Dcm_GaaSIdConfig[LucSIDIndex];

    /* Invoke function to validate session */
    if(LpSIDTAB->pSession != NULL_PTR)
    {
      LblSearchResult = Dcm_DsdValidateSession
      (LpSIDTAB->pSession,
        LpSIDTAB->ucSessionCount);
    }
    else
    {
      LblSearchResult = DCM_TRUE;
    }
    /* Check is the current session level supported by the service Id */
    if(LblSearchResult == DCM_TRUE)
    {
      if(LpSIDTAB->pSecurity != NULL_PTR)
      {
        LblSearchResult = Dcm_DsdValidateSecurity(
        LpSIDTAB->pSecurity,
        LpSIDTAB->ucSecurityCount);
      }
      else
      {
        LblSearchResult = DCM_TRUE;
      }
      /* Check is the current security level supported by the service Id */
      if(LblSearchResult == DCM_TRUE)
      {
        /*
        * Clear the first byte of the response buffer since this byte is
        * used to realize if API Dcm_DsdSetNegResponse was called by any of
        * the service in the API Dcm_ExternalProcessingDone
        */
        LpTxBufferId[DCM_ZERO] = DCM_ZERO;

        /* Update the parameters of the MsgContext Structure */
        Dcm_GstMsgContext.idContext = (LucSID | DCM_RESPONSE_ID);
        Dcm_GstMsgContext.reqData = &LpRxBufferId[DCM_ONE];
        Dcm_GstMsgContext.resData = &LpTxBufferId[DCM_ONE];
        Dcm_GstMsgContext.resMaxDataLen = (uint8)Dcm_ROE_Max_Event_Length;
        /* Request data length (excluding service identifier) */
        Dcm_GstMsgContext.reqDataLen =
          Dcm_GddRoeRequestInfo[IdIndex].ddRoeReqDataLen - DCM_ONE;
        Dcm_GstMsgContext.dcmRxPduId =
          Dcm_GddRoeRequestInfo[IdIndex].ddRoeRxPduId;

        /*
        * Check if the Suppress positive bit is set and Sub function is
        * available for the requested service Id
        */
        if(Dcm_GddProtocolId != DCM_ZERO)
        {
          if(((LpRxBufferId[DCM_ONE] & DCM_SUPRESSBIT_MASK) ==
           DCM_SUPRESSBIT_MASK) &&
           ((LpSIDTAB->blSubFunctionAvailable) == DCM_TRUE))
          {
            Dcm_GstMsgContext.msgAddInfo.suppressPosResponse = DCM_TRUE;
          }
          else
          {
            Dcm_GstMsgContext.msgAddInfo.suppressPosResponse = DCM_FALSE;
          }
        }
        else
        {
          Dcm_GstMsgContext.msgAddInfo.suppressPosResponse = DCM_FALSE;
        }
        Dcm_GstMsgContext.msgAddInfo.reqType = LucreqType;

        /* ROE Queue storage is ongoing
        (Do not transmit Response Message) */
        Dcm_GblRoeQueueOngoing = DCM_TRUE;

        if (NULL_PTR != LpSIDTAB->pDiagnosticService)
        {
          /* Invoke Diagnostic service */
          (void)LpSIDTAB->pDiagnosticService(DCM_INITIAL, &Dcm_GstMsgContext);
        }
        /*
        * Check if any NRC is updated, if updated then invoke
          Dcm_DsdSetNegResponse
        * before calling Dcm_ExternalProcessingDone API
        */
        if(Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE)
        {
          /* Requested Service ID is not configured for the current security */
          LpTxBufferId[DCM_TWO] = Dcm_GddNegRespError;
          LblErrorOccured = DCM_TRUE;

          /* Return the Global Variable */
          Dcm_GddNegRespError = LddNegRespError;
        }
      }
      /* Store the NRC error and set the error flag */
      else
      {
        /* Requested Service ID is not configured for the current security */
        LpTxBufferId[DCM_TWO] = DCM_E_SECURITYACCESSDENIED;
        LblErrorOccured = DCM_TRUE;
      }
    }
    /* Store the NRC error and set the error flag */
    else
    {
      /* Requested Service ID is not configured for the current session */
      LpTxBufferId[DCM_TWO] = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
      LblErrorOccured = DCM_TRUE;
    }
  }
  /* Store the NRC error and set the error flag */
  else
  {
    /* Requested Service ID is not configured in the active service table */
    LpTxBufferId[DCM_TWO] = DCM_E_SERVICENOTSUPPORTED;
    LblErrorOccured = DCM_TRUE;
  }

    /* Check if the error flag is set */
    if(LblErrorOccured == DCM_TRUE)
    {
    /* Update the response data buffer pointer */
    Dcm_GstMsgContext.resData = LpTxBufferId;
    /* Update the first byte with the negative response Id */
    LpTxBufferId[DCM_ZERO] = DCM_NEGATIVE_RESPONSE_SID;
    /* Update the second byte with the service Id */
    LpTxBufferId[DCM_ONE] = LucSID;
    /* Update the response length */
    Dcm_GstMsgContext.resDataLen = DCM_THREE;
    }
  else
  {

    Dcm_GaaRoeQueueInfo
      [Dcm_GddRoeQueueProcessInfo.QueueWriteIndex].ulRoeLengthInfoBuffer =
        Dcm_GstMsgContext.resDataLen;

    Dcm_GaaRoeQueueInfo
      [Dcm_GddRoeQueueProcessInfo.QueueWriteIndex].aaRoeQueueBuffer[DCM_ZERO] =
        (Dcm_GddRoeRequestInfo[IdIndex].RoeReqData[DCM_ZERO] | DCM_RESPONSE_ID);

    Dcm_GaaRoeQueueInfo[Dcm_GddRoeQueueProcessInfo.QueueWriteIndex].idContext =
      (Dcm_GddRoeRequestInfo[IdIndex].RoeReqData[DCM_ZERO] | DCM_RESPONSE_ID);

    Dcm_GaaRoeQueueInfo
      [Dcm_GddRoeQueueProcessInfo.QueueWriteIndex].suppressPosResponse =
        Dcm_GstMsgContext.msgAddInfo.suppressPosResponse;

    Dcm_GaaRoeQueueInfo[Dcm_GddRoeQueueProcessInfo.QueueWriteIndex].reqType =
      Dcm_GstMsgContext.msgAddInfo.reqType;

    Dcm_GaaRoeQueueInfo[Dcm_GddRoeQueueProcessInfo.QueueWriteIndex].ucSTRTId =
      IdIndex;
  }

  /* Count up the Queue Write Index */
  Dcm_DspSetQueueIndex(DCM_ROE_QUEUE_WRITE);

  /* Clear ROE Queue storage status */
  Dcm_GblRoeQueueOngoing = DCM_FALSE;

  LddEventInQueue = DCM_TRUE;

  /* Start Tx ROE Queue Messages */
  Dcm_TimerReqFlagStatus.ucRoeInterMsgTimer = DCM_TRUE;

  return (LddEventInQueue);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DemTriggerOnDTCStatus                           **
**                                                                            **
** Service ID           : 0x2B                                                **
**                                                                            **
** Description          : This API is triggered on changes of the UDS DTC     **
**                        status byte. It allows to trigger on ROE Event for  **
**                        subservice OnDTCStatusChanged.                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : DTC, DTCStatusOld, DTCStatusNew                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GucRoeSTRTIndex,           **
**                                             Dcm_GblRoeClearAll             **
**                                                                            **
**                        Function(s) invoked: Dcm_DspQueueRoeEvents,         **
**                                             DslInternal_ResponseOnOneEvent **
**                                                                            **
*******************************************************************************/
#if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DemTriggerOnDTCStatus(
                       uint32 DTC, uint8 DTCStatusOld, uint8 DTCStatusNew)
{
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_PRIVATE_CONST) LpPduIdTable;
  Std_ReturnType LddReturnValue;

  #if(DCM_ROE_QUEUE_ENABLED == STD_OFF)
  Std_ReturnType LddRspOnEventReturnValue;
  #endif

  uint8 LucIndex;
  uint8 LucNetworkId;
  LddReturnValue = E_OK;
  /* Initialize pointer to PduId table corresponding to the RxPduId */
  LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GpRoeMsgContext->dcmRxPduId];
  LucNetworkId = LpPduIdTable->ucRxComChannelRef;

  /* Check if this API is called becasue of 'Clear All DTCs' request*/
  if((Dcm_GaaCommMode[LucNetworkId] == DCM_FULL_COMMUNICATION) &&
    (Dcm_GblRoeClearAll == DCM_FALSE))
  {
  /* Check if the ROE event OnDTCStatusChange is
     setup and the event is started */
    for(LucIndex = DCM_ZERO ; LucIndex < Dcm_GucRoeSTRTIndex ; LucIndex++)
    {
    if((Dcm_GddRoeRequestInfo[LucIndex].blIsRoeStarted == DCM_TRUE) && \
        (Dcm_GddRoeRequestInfo[LucIndex].blIsOnDTCStsChngRxed == DCM_TRUE) &&
        (Dcm_PrtclTxBufStatus.ucClearDTCStatus == DCM_FALSE))
    {
      /* Check if the DTC status is changed */
      if((DTCStatusOld & Dcm_GddRoeRequestInfo[LucIndex].ucStatusMask) \
          != (DTCStatusNew & Dcm_GddRoeRequestInfo[LucIndex].ucStatusMask))
      {
        Dcm_GddRoeRequestInfo[LucIndex].ucNumOfIdentifiedEvents++;

        #if(DCM_ROE_QUEUE_ENABLED == STD_ON)

        (void)Dcm_DspQueueRoeEvents(LucIndex);

        #else

          /*
           * Initialize the global variable with the RxPduId in case the ROE
           * request processing is to be postponed
           */
          Dcm_GddRoeRxPduId = Dcm_GddRoeRequestInfo[LucIndex].ddRoeRxPduId;

          if(((Dcm_TimerReqFlagStatus.ucRoeInterMsgTimer ==
              DCM_TRUE) &&
              (Dcm_GaaTimer[DCM_ROE_INTERMESSAGE_TIMER] == DCM_ZERO)) ||
              (Dcm_TimerReqFlagStatus.ucRoeInterMsgTimer ==
              DCM_FALSE))
          {
            /* Invoke the function to initiate the response transmission */
            LddRspOnEventReturnValue =
              DslInternal_ResponseOnOneEvent
                (&Dcm_GddRoeRequestInfo[LucIndex].RoeReqData[DCM_ZERO],
                  Dcm_GddRoeRequestInfo[LucIndex].ddRoeReqDataLen,
                    Dcm_GddRoeRequestInfo[LucIndex].ddRoeRxPduId);
          }
          else
          {
            LddRspOnEventReturnValue = DCM_E_ROE_NOT_ACCEPTED;
          }

          if(LddRspOnEventReturnValue == DCM_E_ROE_NOT_ACCEPTED)
          {
            LddReturnValue = E_NOT_OK;
          }
        #endif

      }
    }
    }
  }
  else
  {
    LddReturnValue = E_NOT_OK;
  }
  /* MISRA Rule        : 14.2
    Message            : This statement has no side-effect - it can be removed
    Reason             : To avoid Un used variable warning.
    Verification       : However, part of the code
                         is verified manually and
                       it is not having any impact.
  */
  DCM_UNUSED(DTC);
  /* MISRA Rule        : 14.2
    Message            : This statement has no side-effect - it can be removed
    Reason             : To avoid Un used variable warning.
    Verification       : However, part of the code
                         is verified manually and
                       it is not having any impact.
  */
  #if(DCM_ROE_QUEUE_ENABLED == STD_OFF)
  DCM_UNUSED(LddRspOnEventReturnValue);
  #endif
  return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_TriggerOnEvent                                  **
**                                                                            **
** Service ID           : 0x2D                                                **
**                                                                            **
** Description          : This API function allows to trigger an event linked **
**                        to a ResponseOnEvent request.                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : RoeEventId                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GblNormalReq,              **
**                                             Dcm_GucRoeSTRTIndex,           **
**                                             Dcm_GucResOnEventStatus,       **
**                                             Dcm_GddRoeRxPduId              **
**                                                                            **
**                        Function(s) invoked: Dcm_DspQueueRoeEvents,         **
**                                             DslInternal_ResponseOnOneEvent **
**                                                                            **
*******************************************************************************/
#if((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
  (DCM_EXTERNAL_ROE_ENABLED == STD_ON))
FUNC(Std_ReturnType, DCM_CODE)Dcm_TriggerOnEvent(uint8 RoeEventId)
{
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_PRIVATE_CONST) LpPduIdTable;
  Std_ReturnType LddReturnValue;
  #if(DCM_ROE_QUEUE_ENABLED == STD_OFF)
  Dcm_StatusType LddRspOnEventReturnValue;
  #endif
  uint8 LucIndex;
  uint8 LucNetworkId;
  LddReturnValue = E_NOT_OK;

  /* Initialize pointer to PduId table corresponding to the RxPduId */
    LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GpRoeMsgContext->dcmRxPduId];
    LucNetworkId = LpPduIdTable->ucRxComChannelRef;

  if((Dcm_GaaCommMode[LucNetworkId] == DCM_FULL_COMMUNICATION)
  #if(DCM_PROTOCOL_TRANSTYPE2 == STD_OFF)
  && (Dcm_GblNormalReq == DCM_FALSE)
  #endif
  )
  {
    /* Check if the ROE event OnChangeOfDataIdentifier is setup and the
      event is started */
    for(LucIndex = DCM_ZERO ; LucIndex < Dcm_GucRoeSTRTIndex ; LucIndex++)
    {
      if((Dcm_GddRoeRequestInfo[LucIndex].blIsRoeStarted == DCM_TRUE) &&
         (Dcm_GddRoeRequestInfo[LucIndex].blIsOnChngOfDIDRxed == DCM_TRUE))
      {
        if((Dcm_GaaDIDParaConfig
          [Dcm_GddRoeRequestInfo[LucIndex].usDIDIndex].
          blDcmDspDidExtRoeEnabled == DCM_TRUE) && (Dcm_GaaDIDParaConfig[
          Dcm_GddRoeRequestInfo[LucIndex].usDIDIndex].ucDcmDspDidRoeEventId ==
           RoeEventId))
        {
          Dcm_GddRoeRequestInfo[LucIndex].ucNumOfIdentifiedEvents++;

          /* Check if Queue is enabled and ROE is ongoing */
          #if(DCM_ROE_QUEUE_ENABLED == STD_ON)
          if(((Dcm_GucResOnEventStatus == DCM_ROEONGOING) ||
            (Dcm_GddRoeQueueProcessInfo.QueueWriteIndex > DCM_ZERO)) &&
            (Dcm_GaaDIDParaConfig[
              Dcm_GddRoeRequestInfo[LucIndex].usDIDIndex].ucDcmDspDidRoeEventId
              == DCM_TRUE))
          {
            (void)Dcm_DspQueueRoeEvents(LucIndex);
                        LddReturnValue = E_OK;
          }
          #else
            /*
             * Initialize the global variable with the RxPduId in case the ROE
             * request processing is to be postponed
             */
            Dcm_GddRoeRxPduId = Dcm_GddRoeRequestInfo[LucIndex].ddRoeRxPduId;
            /* Invoke the function to initiate the response transmission */


          if(((Dcm_TimerReqFlagStatus.ucRoeInterMsgTimer ==
              DCM_TRUE) &&
              (Dcm_GaaTimer[DCM_ROE_INTERMESSAGE_TIMER] == DCM_ZERO)) ||
              (Dcm_TimerReqFlagStatus.ucRoeInterMsgTimer ==
              DCM_FALSE))
          {

            /* Invoke the function to initiate the response transmission */
            LddRspOnEventReturnValue =
                DslInternal_ResponseOnOneEvent
                (&Dcm_GddRoeRequestInfo[LucIndex].RoeReqData[DCM_ZERO],
                  Dcm_GddRoeRequestInfo[LucIndex].ddRoeReqDataLen,
                    Dcm_GddRoeRequestInfo[LucIndex].ddRoeRxPduId);
          }
          else
          {
            LddRspOnEventReturnValue = DCM_E_ROE_NOT_ACCEPTED;
          }
            if(LddRspOnEventReturnValue != DCM_E_ROE_NOT_ACCEPTED)
            {
              LddReturnValue = E_OK;
            }

          #endif

        }
      }
    }
  }
  /* MISRA Rule        : 14.2
    Message            : This statement has no side-effect - it can be removed
    Reason             : To avoid Un used variable warning.
    Verification       : However, part of the code
                         is verified manually and
                       it is not having any impact.
  */
  #if(DCM_ROE_QUEUE_ENABLED == STD_OFF)
  DCM_UNUSED(LddRspOnEventReturnValue);
  #endif
  return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_StopROE                                         **
**                                                                            **
** Service ID           : 0x2E                                                **
**                                                                            **
** Description          : This function stops ROE and clears the ROE event    **
                                    from the transmission queue.              **
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
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : None                           **
**                                                                            **
**                        Function(s) invoked: Dcm_DspDisableRoe              **
**                                                                            **
*******************************************************************************/
#if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_StopROE(void)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  Dcm_DspDisableRoe();

  /* E_OK is always returned */
  return(LddReturnValue);
}

/*******************************************************************************
** Function Name        : Dcm_RestartROE                                      **
**                                                                            **
** Service ID           : 0x2F                                                **
**                                                                            **
** Description          : This function restart the ROE event.                **
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
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : None                           **
**                                                                            **
**                        Function(s) invoked: Dcm_DspEnableRoe               **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_RestartROE(void)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  (void)Dcm_DspEnableRoe();

  /* E_OK is always returned */
  return(LddReturnValue);
}

/*******************************************************************************
** Function Name        : Dcm_StoreRoeEvent                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function stores the ROE event in NvM           **
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
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : None                           **
**                                                                            **
**                        Function(s) invoked: None                           **
**                                                                            **
*******************************************************************************/
#if(DCM_MAX_NO_OF_PRECONFIGURED_DID != DCM_ZERO)
FUNC(void, DCM_CODE) Dcm_StoreRoeEvent(void)
{
  Std_ReturnType LddReturnValue;
  NvM_RequestResultType LddRequestResult;

  LddReturnValue = NvM_WriteBlock(DCM_RESPONSE_ONEVENT_BLOCKID, &Dcm_GddPreConfiguredDID[DCM_ZERO]);
  if(LddReturnValue == E_OK)
  {
    LddReturnValue = NvM_GetErrorStatus(DCM_RESPONSE_ONEVENT_BLOCKID, &LddRequestResult);
    if((LddReturnValue == E_NOT_OK) ||
          (LddRequestResult == NVM_REQ_NOT_OK))
    {
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }
    else
    {
      if(LddRequestResult == NVM_REQ_PENDING)
      {
        Dcm_DspServiceProcessingSts.ucRoeStorePending
          = DCM_TRUE;
      }
      else if(LddRequestResult != NVM_REQ_OK)
      {
        Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
      }
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_RetrieveStoredRoeEvent                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function retrives the ROE event stored in NvM  **
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
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : None                           **
**                                                                            **
**                        Function(s) invoked: None                           **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_RetrieveStoredRoeEvent(uint8 LucRoepduIdValue)
{
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST) LpPduIdTable;
  #if(DCM_PROTOCOL_TRANSTYPE2 == STD_ON)
  P2CONST(Dcm_DslRoeTrans, AUTOMATIC, DCM_APPL_CONST) LpRoeTxId;
  #endif
  uint16 LusDIDValue;
  uint16 LusDIDIndex;
  uint8 LucIndex;
  uint8 LpduIdValue;

  for(LucIndex = DCM_ZERO; LucIndex < Dcm_Max_No_Of_Preconfigured_Did; LucIndex++)
  {
    if(Dcm_GddPreConfiguredDID[LucIndex].usDidValue != (uint16) DCM_ZERO)
    {
      Dcm_GusRoeDidIndex++;
    }
    if(Dcm_GddPreConfiguredDID[LucIndex].blRoeStarted == DCM_TRUE)
    {
      LpduIdValue = Dcm_GddPreConfiguredDID[LucIndex].usRxPduIdValue;
    }
    else
    {
      LpduIdValue = LucRoepduIdValue;
    }
  }

  if(Dcm_GusRoeDidIndex > 0)
  {
    for(LucIndex = DCM_ZERO; LucIndex < Dcm_GusRoeDidIndex; LucIndex++)
    {
      LusDIDValue = Dcm_GddPreConfiguredDID[LucIndex].usDidValue;

      Dcm_IDSearch(DCM_GET_DID, LusDIDValue, &LusDIDIndex);
      if(Dcm_GddPreConfiguredDID[LucIndex].blRoeStarted == DCM_TRUE)
      {
        Dcm_GddRoeRequestInfo
                  [Dcm_GucRoeSTRTIndex].usDIDIndex = LusDIDIndex;

        Dcm_GddRoeRequestInfo
                  [Dcm_GucRoeSTRTIndex].usDIDValue = LusDIDValue;

        Dcm_GddRoeRequestInfo
                  [Dcm_GucRoeSTRTIndex].blIsOnChngOfDIDRxed = DCM_TRUE;

        Dcm_GddRoeRequestInfo
                    [(Dcm_GucRoeSTRTIndex)].blIsDIDManagedInternally =
                      DCM_TRUE;
        #if(DCM_EXTERNAL_ROE_ENABLED == STD_ON)
        if(Dcm_GaaDIDParaConfig[LusDIDIndex].blDcmDspDidExtRoeEnabled ==
          DCM_TRUE)
        {
          Dcm_GddRoeRequestInfo
            [(Dcm_GucRoeSTRTIndex)].blIsDIDManagedInternally =
              DCM_FALSE;
        }
        #endif

        Dcm_GddRoeRequestInfo[Dcm_GucRoeSTRTIndex].ucEventWindowTime =
          (uint8) Dcm_GddPreConfiguredDID[LucIndex].usEventWindowTime;

        Dcm_GddRoeRequestInfo[Dcm_GucRoeSTRTIndex].ddRoeRxPduId = LpduIdValue;

        LpPduIdTable = &Dcm_GaaPduIdTableConfig
          [Dcm_GddRoeRequestInfo[Dcm_GucRoeSTRTIndex].ddRoeRxPduId];

        Dcm_GddRoeRequestInfo[Dcm_GucRoeSTRTIndex].ucRxAddrType =
          LpPduIdTable->ucRxAddrType;

        #if(DCM_PROTOCOL_TRANSTYPE2 == STD_ON)
        LpRoeTxId = LpPduIdTable->pRoeTxId;

        if(LpRoeTxId->blRoeTransType == DCM_ONE)
        {
          Dcm_GddRoeRequestInfo[Dcm_GucRoeSTRTIndex].ddRoeTxPduId =
           LpRoeTxId->ddRoeTxPduId;
        }
        else
        #endif
        {
          Dcm_GddRoeRequestInfo[Dcm_GucRoeSTRTIndex].ddRoeTxPduId =
            LpPduIdTable->ddTxPduId;
        }
        Dcm_GddRoeRequestInfo[Dcm_GucRoeSTRTIndex].ddRoeReqDataLen =
          DCM_THREE;
        Dcm_GddRoeRequestInfo[Dcm_GucRoeSTRTIndex].RoeReqData[DCM_ZERO] =
          DCM_READDATABYIDENTIFIER;
        Dcm_GddRoeRequestInfo[Dcm_GucRoeSTRTIndex].RoeReqData[DCM_ONE] =
          (uint8)(LusDIDValue >> DCM_EIGHT);
        Dcm_GddRoeRequestInfo[Dcm_GucRoeSTRTIndex].RoeReqData[DCM_TWO] =
          (uint8) LusDIDValue;
        Dcm_GucRoeSTRTIndex++;
      }
      else
      {
        /*Do Nothing*/
      }
    }
    Dcm_GusRoeDidIndex = DCM_ZERO;
  }

}
#endif
#endif
/*******************************************************************************
** Function Name        : Dcm_DspRestorePreconfigDID                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked to restore the     **
**                        variables related to ROE.                           **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : DCM_MAX_NO_OF_PRECONFIGURED_DID**
**                                             Dcm_GusPreconfigDidList        **
**                                                                            **
**                        Function(s) invoked: None                           **
**                                                                            **
*******************************************************************************/
#if((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)&& \
          (DCM_MAX_NO_OF_PRECONFIGURED_DID != DCM_ZERO))
FUNC(void, DCM_CODE) Dcm_DspRestorePreconfigDID()
{
  uint8 LucIndex;

  for( LucIndex = DCM_ZERO ; LucIndex < Dcm_Max_No_Of_Preconfigured_Did; LucIndex++)
  {

    Dcm_GddPreConfiguredDID[LucIndex].usDidValue = Dcm_GusPreconfigureDidList[LucIndex];
    Dcm_GddPreConfiguredDID[LucIndex].usRxPduIdValue = DCM_ZERO;
    Dcm_GddPreConfiguredDID[LucIndex].usEventWindowTime = DCM_ZERO;
    Dcm_GddPreConfiguredDID[LucIndex].blRoeStarted = DCM_ZERO;

  }
}
#endif

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
