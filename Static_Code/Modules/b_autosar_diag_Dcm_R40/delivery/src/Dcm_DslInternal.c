/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE: Dcm_DslInternal.c                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the internal function definitions for      **
**              Dsl layer of Dcm module                                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By                 Description                     **
********************************************************************************
** 2.3.2.0   05-Nov-2020   EunKyung Kim    #26432                             **
**                                                                            **
** 1.0.5     02-09-2019    EunKyung Kim       #18790                          **
**                                                                            **
** 1.0.4     21-11-2016    Jin     Jung       #6657                           **
**                                                                            **
** 1.0.3     25-05-2015    Sungeol Baek       #5006                           **
**                                                                            **
** 1.0.2     24-03-2015    Sungeol Baek       #2370                           **
**                                                                            **
** 1.0.1     26-02-2015    Sungeol Baek       #2163                           **
**                                                                            **
** 1.0.0     09-01-2013    Autron             Initial Version                 **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_Ram.h"
#include "Dcm_DslInternal.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_Dsl.h"
#include "Rte_Dcm.h"

#if(DCM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#include "SchM_Dcm.h"
#include "PduR_Dcm.h"
#include "ComM_Dcm.h"
#include "Dcm_Config.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/* polyspace:begin<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
/* polyspace:begin<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */

/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
/* polyspace-begin CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Dcm_DslPduRTransmit                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function transmits the negative response.      **
**                        It further checks the return value of the negative  **
**                        response transmitted and further processing is done **
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
** Remarks              : Global Variable(s) : Dcm_GddRxPduId,                **
**                        Dcm_GaaResponseBuf, Dcm_GaaProtocolConfig,          **
**                        Dcm_GaaPduIdTableConfig, Dcm_TxRespStatus,          **
**                        Dcm_GaaCommMode, Dcm_PrtclTxBufStatus,              **
**                        Dcm_TimerReqFlagStatus , Dcm_GblSecDeclRequest      **
**                        Dcm_GstCurrentTimingValue                           **
**                        Function(s) invoked : PduR_DcmTransmit,             **
**                        Dcm_DslStatusReset, Dcm_DsdConfirmation             **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, DCM_CODE)Dcm_DslPduRTransmit(void)
{
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST)LpDcmPduIdTable;
  P2CONST(Dcm_ProtocolConfig, AUTOMATIC, DCM_APPL_CONST)
    LpDcmProtocolConfig;
  PduInfoType LddPduInfo;
  PduIdType LddTxPduId;
  Std_ReturnType LddReturnValue;
  uint8 LucProtocolIDIndex = DCM_SERVICE_NOT_CONFIGURED;
  uint8 LucNetworkId;

  /* Check if the global bit flag for negative response is set */
  if ((Dcm_TxRespStatus.ucNegResp == DCM_TRUE) && (Dcm_GddRxPduId < Dcm_Num_Of_PduidTableConfig))
  {
    /* Get the structure of the PduIdTable for the corresponding RxPduId */
    LpDcmPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
    /* Get Protocol Index */
    LucProtocolIDIndex = Dcm_GetProtocolIDIndex(LpDcmPduIdTable->ddProtocolId);
  
    /* Get the structure of the Protocol configuration for the corresponding
       RxPduId */
    LpDcmProtocolConfig = NULL_PTR;
    if(LucProtocolIDIndex < Dcm_Num_Of_ProtocolConfig)
    {
      LpDcmProtocolConfig = &Dcm_GaaProtocolConfig[LucProtocolIDIndex];
    }
    /* Update the TxPduId value in the local variable */
    LddTxPduId = LpDcmPduIdTable->ddTxPduId;        
    
    /* Check whether the communication mode is in full communication mode */
    LucNetworkId = LpDcmPduIdTable->ucRxComChannelRef;

    if((NULL_PTR != LpDcmProtocolConfig) && (LucNetworkId < Dcm_No_Of_Comm_Channels))
    {
      /* Check if communication mode is other than DCM_NO_COMMUNICATION */
      if(Dcm_GaaCommMode[LucNetworkId] != DCM_NO_COMMUNICATION)
      {
        /* Update the PduInfoPtr with negative response array */
        LddPduInfo.SduDataPtr = &Dcm_GaaResponseBuf[DCM_ZERO];
        /* Update length as three */
        LddPduInfo.SduLength = DCM_THREE;
        /* Invoke PduR_DcmTransmit */
        LddReturnValue = Dcm_PduRTransmit(LddTxPduId, &LddPduInfo);
        /* Check the return value */
        if(LddReturnValue == E_OK)
        {
          Dcm_GddDcmTxPduId  =  LpDcmPduIdTable->ddTxPduId;
          Dcm_GddDcmTxConfPduId  =  (uint8)LpDcmPduIdTable->usTxConfirmationPduId;
          #if(DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
          if(Dcm_GblSecDeclRequest == DCM_FALSE)
          #endif
          {
            /*
            * Check whether the protocol is not started and preempt timer is not
            * started
            */
            if((Dcm_PrtclTxBufStatus.ucProtclStatus == DCM_FALSE)
              && (Dcm_TimerReqFlagStatus.ucPrtclPreemptTimer == DCM_FALSE))
            {
              /* Start the protocol preempt timer */
              DCM_START_TIMER(DCM_PROTOCOL_PREEMPT_TIMER, LpDcmProtocolConfig->usPrtclPreempTimeOut);
              Dcm_TimerReqFlagStatus.ucPrtclPreemptTimer = DCM_TRUE;
            }
            /* Check whether the P2ServerMax Timer is  started */
            SchM_Enter_Dcm_TimerProtection();
            if(Dcm_TimerReqFlagStatus.ucP2MaxTimer == DCM_TRUE)
            {
              /* Restart the timer P2ServerMax */
              DCM_START_TIMER(DCM_P2SERVERMAX_TIMER,
               (Dcm_GstCurrentTimingValue.Timer_P2StarServerMax -
                Dcm_GstCurrentTimingValue.Timer_P2StrServerAdjust));
              Dcm_TimerReqFlagStatus.ucP2MaxTimer = DCM_TRUE;
            }
            SchM_Exit_Dcm_TimerProtection();
          }
        }
        else
        {
          #if(DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
          if(Dcm_GblSecDeclRequest == DCM_FALSE)
          #endif
          {
            /* Reset the status of the RxPduId */
            Dcm_DslStatusReset();
            /* Provide negative confirmation in case of transmission failure */
            Dcm_DsdConfirmation(NTFRSLT_E_NOT_OK);
          }
          SchM_Enter_Dcm_RxPduIdProtection();  
          /* polyspace +2 MISRA-C3:14.3 [Justified:Low] "Not a defect" */
          /* polyspace +6 MISRA-C3:2.1 [Justified:Low] "Not a defect" */
          if (DCM_TRUE == Dcm_TxRespStatus.ucNeedFailedConfiramtion)
          {
            Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_FALSE;
            /* polyspace +1 MISRA-C3:10.3 [Justified:Low] "Not a defect" */
	          Dcm_TriggerCancelPendingOperation = DCM_TRUE;            
          }
          SchM_Exit_Dcm_RxPduIdProtection();  
          /* Reset global bit flag for negative response to DCM_FALSE */
          Dcm_TxRespStatus.ucNegResp = DCM_FALSE;
        }
      }
      else
      {
        /* TODO: No communication,, Need confirmation ? */
        SchM_Enter_Dcm_RxPduIdProtection();  
        if (DCM_TRUE == Dcm_TxRespStatus.ucNeedFailedConfiramtion)
        {
          Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_FALSE;
          /* polyspace +1 MISRA-C3:10.3 [Justified:Low] "Not a defect" */
          Dcm_TriggerCancelPendingOperation = DCM_TRUE;            
        }
        SchM_Exit_Dcm_RxPduIdProtection();  
          
        /* Reset global bit flag for negative response to DCM_FALSE */
        Dcm_TxRespStatus.ucNegResp = DCM_FALSE;        
      }        
    }
    else
    {
      Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_FALSE;
      Dcm_TxRespStatus.ucNegResp = DCM_FALSE;
      DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_INTERFACE_BUFFER_OVERFLOW);
    }
  }    
  else
  {
    Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_FALSE;  
    Dcm_TxRespStatus.ucNegResp = DCM_FALSE;
    DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_INTERFACE_BUFFER_OVERFLOW);
  }
}

/*******************************************************************************
** Function Name        : Dcm_DslTxIncorrectCondition                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function checks the status of the protocol     **
**                        start and report to DET in case of error in         **
**                        protocol. Further processing of the request is done **
**                        in case of successful protocol start                **
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
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GaaPduIdTableConfig,       **
**                        Dcm_GaaBufferConfig, Dcm_GddRxPduId                 **
**                        Dcm_GstCurrentTimingValue , Dcm_GaaResponseBuf      **
**                        Dcm_PrtclTxBufStatus,Dcm_GddDcmTxPduId              **
**                        Dcm_MemServicePendingStatus, Dcm_GblNormalReq       **
**                        Dcm_TimerReqFlagStatus                              **
**                        Function(s) invoked : Dcm_DslSetParameters,         **
**                        Dcm_DsdIndication, Dcm_DslStatusReset               **
**                                                                            **
*******************************************************************************/
/* sg.baek 022305 - Task #2163 in redmine */
#if (DCM_DEV_ERROR_DETECT == STD_ON)
FUNC(void, DCM_CODE)Dcm_DslTxIncorrectCondition(uint8 API_ServiceId)
#else
FUNC(void, DCM_CODE)Dcm_DslTxIncorrectCondition(void)
#endif
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpRxPduIdData;
  PduIdType LddTxPduId;
  PduInfoType LddPduInfo;
  Std_ReturnType LddReturnValue;
  uint8 LucRxTxBufferId;

  if (Dcm_GddRxPduId >= Dcm_Num_Of_PduidTableConfig)
  {
    DCM_REPORT_ERROR(API_ServiceId, DCM_E_INTERFACE_BUFFER_OVERFLOW);
  }
  else
  {
    /* Get the buffer Id of the TxPduId */
    LucRxTxBufferId = (uint8)Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId].ucRxBufferId;
    if(LucRxTxBufferId >= Dcm_Num_Of_Buffer_Config)
    {
      #if(DCM_DEV_ERROR_DETECT == STD_ON)
      DCM_REPORT_ERROR(API_ServiceId, DCM_E_INTERFACE_BUFFER_OVERFLOW);
      #endif
    }
    else
    {
      DCM_REPORT_ERROR(API_ServiceId, DCM_E_INTERFACE_RETURN_VALUE);

      /* Update the TxPduId value in the local variable */
      LddTxPduId = Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId].ddTxPduId;    
      /*
        * Update the request data available in the buffer area of RxPduId
        * to the local pointer variable
      */
      LpRxPduIdData = Dcm_GaaBufferConfig[LucRxTxBufferId].pBufferArea;
      /* Update the negative response service Id in the response buffer */
      Dcm_GaaResponseBuf[DCM_ZERO] = DCM_NEGATIVE_RESPONSE_SID;
      /* Update the service Id in the response buffer */
      Dcm_GaaResponseBuf[DCM_ONE] = LpRxPduIdData[DCM_ZERO];
      /* Update the NRC in the response buffer */
      Dcm_GaaResponseBuf[DCM_TWO] = DCM_E_CONDITIONSNOTCORRECT;
    
      /*
       * Update the global bit flag indicating negative response to
       * TRUE
       */
      Dcm_TxRespStatus.ucNegResp = DCM_TRUE;
    
      /* Update the PduInfoPtr with negative response array */
      LddPduInfo.SduDataPtr = &Dcm_GaaResponseBuf[DCM_ZERO];
      /* Update length as three */
      LddPduInfo.SduLength =  DCM_THREE;
      /* Invoke PduR_DcmTransmit */
      LddReturnValue = Dcm_PduRTransmit(LddTxPduId, &LddPduInfo);
      if(LddReturnValue == E_OK)
      {
        /* To do Dcm_DslStatusReset() after performing Dcm_TpTxConfirmation()*/
        Dcm_MemServicePendingStatus.ucStartProtocolFailed = DCM_TRUE;
        Dcm_GddDcmTxPduId = LddTxPduId;
      }
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_DslCheckPrtclStatus                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function checks the status of the protocol     **
**                        start and report to DET in case of error in         **
**                        protocol. Further processing of the request is done **
**                        in case of successful protocol start                **
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
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GaaPduIdTableConfig,       **
**                        Dcm_GaaBufferConfig, Dcm_GddRxPduId                 **
**                        Dcm_GstCurrentTimingValue , Dcm_GaaResponseBuf      **
**                        Dcm_PrtclTxBufStatus,                            **
**                        Dcm_MemServicePendingStatus, Dcm_GblNormalReq    **
**                        Dcm_TimerReqFlagStatus                           **
**                        Function(s) invoked : Dcm_DslSetParameters,         **
**                        Dcm_DsdIndication, Dcm_DslStatusReset               **
**                                                                            **
*******************************************************************************/
/* sg.baek 022305 - Task #2163 in redmine */
FUNC(void, DCM_CODE) Dcm_DslCheckPrtclStatus(void)
{
  if (Dcm_GddRxPduId < Dcm_Num_Of_PduidTableConfig)
  {
    /*
     * Check whether protocol started or incoming request RxPduId protocol is
     * not of the current running protocol
    */
    /* polyspace<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */    
    if ((Dcm_PrtclTxBufStatus.ucProtclStatus == DCM_FALSE) ||   /* No active protocol */
         (Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId].ddProtocolId != Dcm_GddProtocolId)) /* preemtion */
    {
      #if(DCM_DSP_SESSION_REF == STD_ON)
      /* Invoke function to set the values after protocol start */
      Dcm_DslSetParameters();
      #endif
      /* Set the global bit flag for protocol status to TRUE */
      Dcm_PrtclTxBufStatus.ucProtclStatus = DCM_TRUE;
    }
  
    /* Dcm_GblNormalReq = DCM_TRUE; */
    if (Dcm_GstCurrentTimingValue.Timer_P2ServerMax >= Dcm_GstCurrentTimingValue.Timer_P2ServerAdjust)
    {
      /* if timeP2ServerMax is reached(timeout!), Dcm may respond the pending message to client */
      uint16 timeP2ServerMax = Dcm_GstCurrentTimingValue.Timer_P2ServerMax - Dcm_GstCurrentTimingValue.Timer_P2ServerAdjust;
      /* Start the Timer P2ServerMax */
      DCM_START_TIMER(DCM_P2SERVERMAX_TIMER, timeP2ServerMax);

      SchM_Enter_Dcm_TimerProtection();
      Dcm_TimerReqFlagStatus.ucP2MaxTimer = DCM_TRUE;
      SchM_Exit_Dcm_TimerProtection();
    }
    else
    {
      DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM);
    }

    /* Forward the request to the DSD layer */
    (void)Dcm_DsdIndication(Dcm_GddRxPduId, DCM_FALSE, DCM_FALSE, DCM_FALSE);
  }
}

/* sg.baek 022305 - Task #2163 in redmine */
#if 0
/*******************************************************************************
** Function Name        : Dcm_DslCheckPrtclStatus                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function checks the status of the protocol     **
**                        start and report to DET in case of error in         **
**                        protocol. Further processing of the request is done **
**                        in case of successful protocol start                **
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
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GaaPduIdTableConfig,       **
**                        Dcm_GaaBufferConfig, Dcm_GddRxPduId                 **
**                        Dcm_GstCurrentTimingValue , Dcm_GaaResponseBuf      **
**                        Dcm_PrtclTxBufStatus,Dcm_GddDcmTxPduId           **
**                        Dcm_MemServicePendingStatus, Dcm_GblNormalReq    **
**                        Dcm_TimerReqFlagStatus                           **
**                        Function(s) invoked : Dcm_DslSetParameters,         **
**                        Dcm_DsdIndication, Dcm_DslStatusReset               **
**                                                                            **
*******************************************************************************/
#if(DCM_DEV_ERROR_DETECT == STD_ON)
FUNC(void, DCM_CODE)Dcm_DslCheckPrtclStatus(Dcm_StatusType
   LddStatusValue, uint8 API_ServiceId)
#else
FUNC(void, DCM_CODE)Dcm_DslCheckPrtclStatus(Dcm_StatusType
   LddStatusValue)
#endif
{
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST)LpDcmPduIdTable;
  P2CONST(Dcm_BufferConfig, AUTOMATIC, DCM_APPL_CONST)LpDcmBufferConfig;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpRxPduIdData;
  PduIdType LddTxPduId;
  PduInfoType LddPduInfo;
  Std_ReturnType LddReturnValue;
  uint8 LucSubFunction;
  uint8 LucRxTxBufferId;

  /* Initialize the pointer to the PduId table */
  LpDcmPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  /* Update the TxPduId value in the local variable */
  LddTxPduId = LpDcmPduIdTable->ddTxPduId;
  /* Initialize the pointer to the buffer configuration */
  LpDcmBufferConfig = &Dcm_GaaBufferConfig[(LpDcmPduIdTable->ucRxBufferId)];

  if((LddStatusValue == DCM_E_PROTOCOL_NOT_ALLOWED) || (LddStatusValue == E_NOT_OK))
  {
    #if(DCM_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID, API_ServiceId,
      DCM_E_INTERFACE_RETURN_VALUE);
    #endif

    /* Get the buffer Id of the TxPduId */
    LucRxTxBufferId =
      (uint8)Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId].ucRxBufferId;
    /*
      * Update the request data available in the buffer area of RxPduId
      * to the local pointer variable
    */
    LpRxPduIdData = Dcm_GaaBufferConfig[LucRxTxBufferId].pBufferArea;
    /* Update the negative response service Id in the response buffer */
    Dcm_GaaResponseBuf[DCM_ZERO] = DCM_NEGATIVE_RESPONSE_SID;
    /* Update the service Id in the response buffer */
    Dcm_GaaResponseBuf[DCM_ONE] = LpRxPduIdData[DCM_ZERO];
    /* Update the NRC in the response buffer */
    Dcm_GaaResponseBuf[DCM_TWO] = DCM_E_CONDITIONSNOTCORRECT;

    /*
     * Update the global bit flag indicating negative response to
     * TRUE
     */
    Dcm_TxRespStatus.ucNegResp = DCM_TRUE;

    /* Update the PduInfoPtr with negative response array */
    LddPduInfo.SduDataPtr = &Dcm_GaaResponseBuf[DCM_ZERO];
    /* Update length as three */
    LddPduInfo.SduLength =  DCM_THREE;
    /* Invoke PduR_DcmTransmit */
    LddReturnValue = PduR_DcmTransmit(LddTxPduId, &LddPduInfo);
    if(LddReturnValue == E_OK)
    {
      Dcm_MemServicePendingStatus.ucStartProtocolFailed =
        DCM_TRUE;
      Dcm_GddDcmTxPduId = LddTxPduId;
    }
  }
  else
  {
    /*
     * Check whether protocol started or incoming request RxPduId protocol is
     * not of the current running protocol
    */
    if((Dcm_PrtclTxBufStatus.ucProtclStatus == DCM_FALSE) ||
      ((LpDcmPduIdTable->ddProtocolId) != (Dcm_GddProtocolId)))
    {
      #if(DCM_DSP_SESSION_REF == STD_ON)
      /* Invoke function to set the values after protocol start */
      Dcm_DslSetParameters();
      #endif
      /* Set the global bit flag for protocol status to TRUE */
      Dcm_PrtclTxBufStatus.ucProtclStatus = DCM_TRUE;
    }
    /* Get the pointer to LpRxPduIdData */
    LpRxPduIdData = LpDcmBufferConfig->pBufferArea;

    if((*LpRxPduIdData == DCM_TESTERPRESENT) && (Dcm_GddTpSduLength == DCM_TWO))
    {
      /* Get the Sub function value */
      LucSubFunction = LpRxPduIdData[DCM_ONE];
    }
    else
    {
      LucSubFunction = DCM_ZERO;
    }
    /*
      * Check whether is request is Tester Present and whether the request is
      * functional and Positive response message indication bit is DCM_TRUE
    */
    if(((LucSubFunction & DCM_SUPRESSBIT_MASK) == DCM_SUPRESSBIT_MASK) &&
      (LpDcmPduIdTable->ucRxAddrType == DCM_ADDR_FUNCTIONAL))
    {

      /* Update the local variable to DCM_TRUE for clearing the
                  * status and to start the S3 server Timer */
       Dcm_DslStatusReset();
       /* Update normal request status */
       Dcm_GblNormalReq = DCM_FALSE;

    }
    else
    {
      Dcm_GblNormalReq = DCM_TRUE;

      /* Start the Timer P2ServerMax */
      DCM_START_TIMER(DCM_P2SERVERMAX_TIMER,
        (Dcm_GstCurrentTimingValue.Timer_P2ServerMax -
         Dcm_GstCurrentTimingValue.Timer_P2ServerAdjust));
      SchM_Enter_Dcm_TimerProtection();
      Dcm_TimerReqFlagStatus.ucP2MaxTimer = DCM_TRUE;
      SchM_Exit_Dcm_TimerProtection();

       /* MISRA Rule         : 16.10
          Message            : If a function returns error information,
                               then that error information shall be tested.
          Reason             : The return value is not required in this
                               function.
          Verification       : However, part of the code is verified
                               manually and it is not having any impact.
                */
      /* Forward the request to the DSD layer */
      (void)Dcm_DsdIndication(Dcm_GddRxPduId, DCM_FALSE, DCM_FALSE, DCM_FALSE);
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DslSetSesTimingValues                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function should be requested by the application**
**                        after successful preparation of the timing          **
**                        parameters.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : TimerServerNew                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init and Dcm_PrepareSesTimingValues APIs should **
**                        be called before calling this API.                  **
**                        This API is only used for the service               **
**                        "DiagnosticSessionControl" which is not used within **
**                        UDS on CAN                                          **
**                                                                            **
** Remarks              : Global Variable(s) :Dcm_GstCurrentTimingValue       **
**                        Dcm_GddOldSession, Dcm_GulChannelIdentifier         **
**                        Dcm_GddCurrentSession                               **
**                        Function(s) invoked :ComM_DCM_ActiveDiagnostic      **
**                        ComM_DCM_InactiveDiagnostic                         **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DslSetSesTimingValues
  (P2CONST(Dcm_TimerServerType, AUTOMATIC, DCM_APPL_CONST) TimerServerNew)
{
  if (NULL_PTR != TimerServerNew)
  {
    /* Update the current timing values */
    Dcm_GstCurrentTimingValue.Timer_P2ServerMax =  TimerServerNew->Timer_P2ServerMax;
    Dcm_GstCurrentTimingValue.Timer_P2StarServerMax = TimerServerNew->Timer_P2StarServerMax;

    if((Dcm_GddOldSession != DCM_DEFAULT_SESSION) &&(Dcm_GddCurrentSession == DCM_DEFAULT_SESSION)) 
    {
      /*
       * Inform ComM to inactivate communication mode due to change of session
       * to default diagnostic session
      */
      (void)ComM_DCM_InactiveDiagnostic((NetworkHandleType)Dcm_GulChannelIdentifier);
    }
    else if ((Dcm_GddOldSession == DCM_DEFAULT_SESSION) && (Dcm_GddCurrentSession != DCM_DEFAULT_SESSION))
    {
      /*
      * Inform ComM to activate communication mode due to change of session
      * to Non Default session
      */
      (void)ComM_DCM_ActiveDiagnostic((NetworkHandleType)Dcm_GulChannelIdentifier);
    }
    else
    {
      /* To avoid QAC warning */
    }
  }
}

/*******************************************************************************
** Function Name        : DslInternal_ResponseOnOneEvent                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API provides the processing of one event,      **
**                        requested internally in DCM.                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : MsgPtr, LddMsgLen and LddRxPduId                    **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_StatusType                                      **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_GaaCommMode, Dcm_GblResOnPeriodicIdStatus,      **
**                        Dcm_GaaBufferConfig,                                **
**                        Dcm_GaaPduIdTableConfig, Dcm_GddRxPduId,            **
**                        Dcm_GstCurrentTimingValue                           **
**                        Function(s) invoked : Dcm_DsdIndication             **
*******************************************************************************/
#if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
/* MISRA Rule         : 16.7
   Message            : A pointer parameter in a function prototype should be
                        declared as pointer to const if the pointer is not
                        used to modify the addressed object.
   Reason             : This is the prototype specified in the specification.
   Verification       : However, part of the code is verified
                        manually and it is not having any impact.
*/
FUNC(Dcm_StatusType, DCM_CODE)DslInternal_ResponseOnOneEvent(
   const Dcm_MsgType MsgPtr, Dcm_MsgLenType LddMsgLen, PduIdType LddRxPduId)
{
  P2CONST(Dcm_ProtocolConfig, AUTOMATIC, DCM_PRIVATE_CONST) LpProtocolConfig;
  P2CONST(Dcm_BufferConfig, AUTOMATIC, DCM_PRIVATE_CONST) LpBufferConfig;
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_PRIVATE_CONST) LpPduIdTable;
  P2VAR(uint8, AUTOMATIC, DCM_PRIVATE_DATA) LpRxBuffer;
  Dcm_StatusType LddResponseStatus;
  uint8 LucRxBufferId;
  uint8 LucLoopCount;
  uint8 LucProtocolId;
  uint8 LucNetworkId;
  uint8 LucProtocolIDIndex;
  boolean LblResponseStatus;
  boolean LblROEType2;

  /* Initialize the return value LddResponseStatus */
  LddResponseStatus = DCM_E_ROE_NOT_ACCEPTED;

  /* Initialize pointer to PduId table corresponding to the RxPduId */
  LpPduIdTable = &Dcm_GaaPduIdTableConfig[LddRxPduId];

  #if(DCM_PROTOCOL_TRANSTYPE2 == STD_ON)
  if(((LpPduIdTable->pRoeTxId)->blRoeTransType) == DCM_ONE)
  {
    LucRxBufferId = ((LpPduIdTable->pRoeTxId)->ucRoeRxBufferId);
  }
  else
  {
    /* Initialize the Rx buffer Id for periodic event request */
    LucRxBufferId = Dcm_GaaPduIdTableConfig[LddRxPduId].ucRxBufferId;
  }
  LblROEType2 = DCM_TRUE;
  #else
  /* Initialize the Rx buffer Id for periodic event request */
  LucRxBufferId = Dcm_GaaPduIdTableConfig[LddRxPduId].ucRxBufferId;
  LblROEType2 = DCM_FALSE;
  #endif

  LpBufferConfig = &Dcm_GaaBufferConfig[LucRxBufferId];

  /* Initialize pointer to the Rx buffer area */
  LpRxBuffer = LpBufferConfig->pBufferArea;

  LucNetworkId = LpPduIdTable->ucRxComChannelRef;

  if((Dcm_GaaCommMode[LucNetworkId] == DCM_FULL_COMMUNICATION) &&
     (Dcm_GucResOnEventStatus == DCM_IDLE)&&
     (LddMsgLen < (LpBufferConfig->ulBufferSize)))
  {
    /*
     * To prevent multiple event-triggered request,
     * set the ROE status to pending
     */
    Dcm_GucResOnEventStatus = DCM_ROEPENDING;

    /* Initialize the global variable for the requested message length */
    Dcm_GddRoeReqLength = LddMsgLen;

    /* Initialize the return value */
    LddResponseStatus = DCM_E_OK;

    for(LucLoopCount = DCM_ZERO; LucLoopCount < LddMsgLen; LucLoopCount++)
    {
      LpRxBuffer[LucLoopCount] = MsgPtr[LucLoopCount];
    }

    #if(DCM_PROTOCOL_TRANSTYPE2 == STD_OFF)
    /* Check if the server is idle */
    if (
      (Dcm_GblNormalReq == DCM_FALSE)
      #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
      && (Dcm_GblResOnPeriodicIdStatus == DCM_FALSE)
      #endif
    )
    #endif
    {
      Dcm_GucResOnEventStatus = DCM_ROEONGOING;

      DCM_START_TIMER(DCM_P2SERVERMAX_TIMER,
                    (Dcm_GstCurrentTimingValue.Timer_P2ServerMax));
      SchM_Enter_Dcm_TimerProtection();
      Dcm_TimerReqFlagStatus.ucP2MaxTimer = DCM_TRUE;
      SchM_Exit_Dcm_TimerProtection();

      /* Initialize pointer to PduId table corresponding to the RxPduId */
      LpPduIdTable = &Dcm_GaaPduIdTableConfig[LddRxPduId];
      /* Get the protocol Id */
      LucProtocolId = LpPduIdTable->ddProtocolId;
      /* Get Protocol Index */
      LucProtocolIDIndex = Dcm_GetProtocolIDIndex(LucProtocolId);

      LpProtocolConfig = &Dcm_GaaProtocolConfig[LucProtocolIDIndex];

      Dcm_GaaReqLength[LucProtocolIDIndex] = Dcm_GddRoeReqLength;
      /* Enter DC */
      SchM_Enter_Dcm_RxPduIdProtection();

      /* Set the status of RxPduId */
      *(LpPduIdTable->pPduIdStatus) |=
                                      LpPduIdTable->ucPduIdStatusMask;
      /* Exit DC */
      SchM_Exit_Dcm_RxPduIdProtection();

      /* Enter DC */
      SchM_Enter_Dcm_ProtclProtection();
      /* Set the status of protocol status */
      *(LpProtocolConfig->pProtocolStatus) |=
                           (LpProtocolConfig->ucPrtclStatusMask);

      Dcm_PrtclTxBufStatus.ucProtclStatus = DCM_TRUE;
      /* Exit DC */
      SchM_Exit_Dcm_ProtclProtection();

      /*
       * Update the global variable for RxPduId with the PduId for the
       * ROE request
       */
      Dcm_GddRxPduId = LddRxPduId;

      /* Invoke the Indication function */
      LblResponseStatus =
        Dcm_DsdIndication(Dcm_GddRxPduId, DCM_FALSE, DCM_FALSE, LblROEType2);

      /*
       * Check if all the verifications in the indication function was
       * successful
       */
      if(LblResponseStatus == DCM_FALSE)
      {
        /* Update the return value LddResponseStatus */
        LddResponseStatus = DCM_E_ROE_NOT_ACCEPTED;

        /* Change the ROE status to idle */
        Dcm_GucResOnEventStatus = DCM_IDLE;
      }
    }
  }

  return(LddResponseStatus);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_PduRTransmit                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API provides the processing of meta data and   **
**                        sends to Pdu.                                       **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : TxPduId                                             **
**                                                                            **
** Output Parameters    : PduInfoPtr                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_GaaPduIdTableConfig, Dcm_GddRxPduId,            **
**                        Dcm_GaaMetaDataAdd                                  **
**                        Function(s) invoked : PduR_DcmTransmit              **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_PduRTransmit(PduIdType TxPduId,
P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr)
{
  Std_ReturnType LddReturnVal;
  
  /* Meta data - address store */
  if(Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId].ucMetaDataLength > 0)
  {
    PduInfoPtr->SduDataPtr = &Dcm_GaaMetaDataAdd[0];
  }

  /* polyspace-begin CERT-C:DCL39-C [Justified:Low] "This structure padding is not impact" */
  LddReturnVal = PduR_DcmTransmit(TxPduId, PduInfoPtr);
  /* polyspace-end CERT-C:DCL39-C [Justified:Low] "This structure padding is not impact" */

  return LddReturnVal;
}

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace:end<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:end<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
/* polyspace:end<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */

/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
/* polyspace-end CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

