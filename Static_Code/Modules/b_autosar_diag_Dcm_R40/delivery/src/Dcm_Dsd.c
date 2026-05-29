/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE: Dcm_Dsd.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the API definitions for Dsd layer of Dcm   **
**              module                                                        **
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
** 1.0.6     29-01-2019    Y.S     Jeon       #15566                          **
**                                                                            **
** 1.0.5     09-11-2018    Y.S     Jeon       #13923                          **
**                                                                            **
** 1.0.4     04-01-2017    Jing    Jung       #6174                           **
**                                                                            **
** 1.0.3     24-03-2016    Sungeol Baek       #3754, #4466                    **
**                                                                            **
** 1.0.2     19-06-2015    YoungJin Yun       #2171                           **
**                                                                            **
** 1.0.1     16-04-2015    Sungeol Baek       #2171                           **
**                                                                            **
** 1.0.0     09-01-2013    Autron             Initial Version                 **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm.h"
#include "Rte_Dcm.h"
#include "Dem.h"

#if(DCM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#include "SchM_Dcm.h"
#include "PduR_Dcm.h"
#include "Dcm_Ram.h"
#include "Dcm_Dsl.h"
#include "Dcm_DspMain.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_Config.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/*
polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard-Chap 5.1.2)
*/
/* polyspace:begin<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > pointer is not null */
/* polyspace:begin<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > configured memory access index */
/* polyspace:begin<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */

/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace-begin MISRA-C3:10.4 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, DCM_CODE) Dcm_DiagnosticSerivceDispatch(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_RequestContextType, AUTOMATIC, DCM_APPL_DATA) requestContext)
{
  if ((NULL_PTR != requestContext) && (NULL_PTR != requestContext->rct_MsgContext))
  {
    if (requestContext->rct_ServiceIndex < Dcm_Num_Of_SidConfig)
    {      
      P2CONST(Dcm_ServiceIdConfigType, AUTOMATIC, DCM_PRIVATE_CONST) cfgSid = NULL_PTR;            
      
      cfgSid =  &Dcm_GaaSIdConfig[requestContext->rct_ServiceIndex];
      /* polyspace<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */
      if (NULL_PTR != cfgSid->pDiagnosticService)
      {
	    /* polyspace +1 MISRA-C3:D4.5 [Justified:Low] "Not a defect" */  
        Std_ReturnType result = cfgSid->pDiagnosticService(OpStatus, requestContext->rct_MsgContext);
        
        if (DCM_CANCEL == OpStatus)
        {
          requestContext->rct_RequestResult = E_OK;
        }
        else
        {
          requestContext->rct_RequestResult = result;
        }
      }
    }
  }
}

FUNC(void, DCM_CODE) 
Dcm_InternalSetNegResponse(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  Dcm_NegativeResponseCodeType ErrorCode)
{
  Dcm_ExternalSetNegResponse(pMsgContext,ErrorCode);
}

FUNC(void, DCM_CODE) Dcm_InternalProcessingDone(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  boolean IsSync)
{
  if (DCM_SYNC_DONE == IsSync)
  {
    /* Why ucPagingStarted ? */
    #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
    if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
    #endif      
    {
      Dcm_ExternalProcessingDone(pMsgContext);
    }
  }
  else
  {
    /* Response is processed on next mainfunction */
    Dcm_GblSendResponse = DCM_TRUE;  
  }
}

/*******************************************************************************
** Function Name        : Dcm_ExternalSetNegResponse                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs the setting of the negative  **
**                        response in the corresponding buffer whenever it    **
**                        is called.                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, ErrorCode                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this API.  **
**                                                                            **
** Remarks              : Global Variable(s) :Dcm_TxRespStatus,               **
**                        Dcm_GaaPduIdTableConfig, Dcm_PrtclTxBufStatus       **
**                        Dcm_GaaBufferConfig                                 **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/

/* MISRA Rule         : 16.7
   Message            : A pointer parameter in a function prototype should be
                        declared as pointer to const if the pointer is not
                        used to modify the addressed object.
   Reason             : This is the prototype specified in the specification.
   Verification       : However, part of the code is verified
                        manually and it is not having any impact.
*/
FUNC(void, DCM_CODE) 
Dcm_ExternalSetNegResponse(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  Dcm_NegativeResponseCodeType ErrorCode
)
{
  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  if(NULL_PTR == pMsgContext)
  {
    DCM_REPORT_ERROR(DCM_COPY_TXDATA_SID, DCM_E_PARAM_POINTER);
  }
  else
  #endif 
  {
    Dcm_MsgType txMsgPtr;

    /* If this API is called during paged transmission then set the global
     * variable indicating paged transmission ongoing to FALSE
     */
    Dcm_TxRespStatus.ucPagedTrans = DCM_FALSE;

    /* Initialize pointer to the Tx buffer area */
    txMsgPtr =Dcm_DsdInternal_GetMsgTxBuffer(pMsgContext->dcmRxPduId, DCM_BUFFER_KIND_TX);
    #if(DCM_DEV_ERROR_DETECT == STD_ON)
    if (NULL_PTR == txMsgPtr)
    {
      DCM_REPORT_ERROR(DCM_COPY_TXDATA_SID, DCM_E_PARAM_POINTER);        
    }
    else
    #endif
    {
      /* Update first byte of Tx buffer with NEGATIVE_RESPONSE_SID */
      txMsgPtr[0U] = DCM_NEGATIVE_RESPONSE_SID;

      /* Since NRC has occurred Response Id is changed back to Service Id 
       * Update second byte of Tx buffer with Service Id */
      txMsgPtr[1U] =  pMsgContext->idContext & DCM_SID_MASK;

      /* Update third byte of Tx buffer with Error code */
      txMsgPtr[2U] = (uint8)ErrorCode;
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_ExternalProcessingDone                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API will transmit the response based on data   **
**                        pointed by pMsgContext.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this API.  **
**                                                                            **
** Remarks              : Global Variable(s) :Dcm_GblNormalReq,               **
**                        Dcm_GpMsgContext, Dcm_GaaBufferConfig,              **
**                        Dcm_GaaPduIdTableConfig, Dcm_GaaCommMode            **
**                        Dcm_GblResOnPeriodicIdStatus, Dcm_TxRespStatus      **
**                        Dcm_GucPeriodicSID , Dcm_GucPeriodicRxPduId         **
**                        Dcm_GaaDslPeriodicData , Dcm_IndexOfDslPeriodicData **
**                        Dcm_PrtclTxBufStatus ,                              **
**                        Dcm_GddDcmPeriodicTxConfPduId                       **
**                        Function(s) invoked :                               **
**                        DspInternal_DcmConfirmation, Dcm_DslTransmit,       **
**                        Dcm_DslStatusReset                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_ExternalProcessingDone
(P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST) LpPduIdTable;
  #if((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
  (DCM_PROTOCOL_TRANSTYPE2 == STD_ON))
  P2CONST(Dcm_DslRoeTrans, AUTOMATIC, DCM_APPL_CONST)LpRoeTxId;
  #endif
  /* Local pointer to the Tx buffer */
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBufferId;
  /* Local pointer to point to the response data */
  #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  #if(DCM_PROTOCOL_TRANSTYPE2 == STD_ON)
  P2VAR(Dcm_DslPeriodicTxId, AUTOMATIC, DCM_APPL_DATA) LpPerTxPduIdTable;
  #endif
  #endif
  /* Local variable to store RxPduId */
  PduIdType LddRxPduId;
  /* Local variable to store TxPduId */
  PduIdType LddTxPduId;
  /* Local variable to store Confirmation status */
  Dcm_ConfirmationStatusType LddConfStatus;

  #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  #if(DCM_PROTOCOL_TRANSTYPE2 == STD_ON)
  uint8 LucIndex1 ;
  uint8 LucIndex;
  uint8 LucMaxNumTxPduid;
  uint8 LucDataStatus;
  uint8 LucPerPduIdStatus;
  #endif
  #endif
  #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  /* uint8 LucProtocolIDIndex; */
  #endif
  /* Local variable to store Tx buffer Id */
  uint8 LucTxBufferId = (uint8)0x00;
  /* Local variable to store Response Id */
  uint8 LucIdContext;
  /* Local variable to store Type of addressing */
  uint8 LucreqType;
  /* Local variable to store suppress positive response bit value */
  uint8 LucsuppressPosResponse;
  uint8 LucNetworkId = (uint8)0x00;
  /* Local variable to be used as counter */
  uint8_least LucLoopCount;
  /* Local variable to know if the response is to be suppressed */
  boolean LblSupResp;
  /* Local variable to know if Dcm_ExternalSetNegResponse was called */
  boolean LblNrcOccured;
  boolean LblROEType2;
  #if ((DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) \
               && (DCM_PROTOCOL_TRANSTYPE2 == STD_ON))
  boolean LblTransmit;
  LblTransmit = DCM_FALSE;
  #endif
  LblROEType2 = DCM_FALSE;

  /* Initiate status as DCM_RES_NEG_NOT_OK */
  LddConfStatus = DCM_RES_NEG_NOT_OK;
  
  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  /* Validate pointer */
  if(pMsgContext == NULL_PTR)
  {
    /* Report to DET */
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID, DCM_COPY_TXDATA_SID,
      DCM_E_PARAM_POINTER);
  }
  else if(pMsgContext->dcmRxPduId >= Dcm_Num_Of_PduidTableConfig)
  {
    /* Report to DET */
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID, DCM_COPY_TXDATA_SID,
      DCM_E_INTERFACE_BUFFER_OVERFLOW);
  }
  else
  #endif /* (DCM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Initialize IdContext from the MsgContext */
    LucIdContext = pMsgContext->idContext;
    /* Initialize RxPduId from the MsgContext */
    LddRxPduId = pMsgContext->dcmRxPduId;
    /* Initialize the addressing type whether physical/functional request */
    LucreqType = pMsgContext->msgAddInfo.reqType;
    /* Initialize whether positive response is suppressed */
    LucsuppressPosResponse = pMsgContext->msgAddInfo.suppressPosResponse;
    /* Initialize pointer to the RxPduId table */
    LpPduIdTable = &Dcm_GaaPduIdTableConfig[LddRxPduId];
    /* Initialize Tx buffer Id configured for the RxPduId */
    LucTxBufferId = LpPduIdTable->ucTxBufferId;
    LucNetworkId = LpPduIdTable->ucRxComChannelRef;
  
    /* Initialize TxPduId configured for the RxPduId */
    LddTxPduId = LpPduIdTable->ddTxPduId;
  
    /* Reset the variable to store th number of response pending transmitted */
    Dcm_GusMaxNoOfRespPend = DCM_ZERO;
  
    #if((DCM_PROTOCOL_TRANSTYPE2  ==  STD_ON) && \
      (DCM_RESPONSE_ON_EVENT_SERVICE  ==  STD_ON))
    if(Dcm_GucResOnEventStatus == DCM_ROEONGOING)
    {
      LpRoeTxId = Dcm_GaaPduIdTableConfig[LddRxPduId].pRoeTxId;
      LucTxBufferId = LpRoeTxId->ucRoeTxBufferId;
      LddTxPduId = LpRoeTxId->ddRoeTxPduId;
      LblROEType2 = DCM_TRUE;
    }
    #endif
  
    if((LucTxBufferId < Dcm_Num_Of_Buffer_Config) && 
       (LucNetworkId < Dcm_No_Of_Comm_Channels))
    {
      LpTxBufferId = Dcm_GaaBufferConfig[LucTxBufferId].pBufferArea;
    
      #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
      if((Dcm_GblResOnPeriodicIdStatus == DCM_TRUE) &&
          (Dcm_GucPeriodicSID == DCM_READDATABYPERIODICIDENTIFIER))
      {
        LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GucPeriodicRxPduId];
    
        #if (DCM_PROTOCOL_TRANSTYPE2 == STD_ON)
        if(Dcm_GaaPduIdTableConfig[LddRxPduId].pPeriodicTxId != NULL_PTR)
        {
          SchM_Enter_Dcm_ProtclProtection();
          LpTxBufferId = Dcm_GaaDslPeriodicData[Dcm_IndexOfDslPeriodicData].pPerData;
          SchM_Exit_Dcm_ProtclProtection();
        }
        else
        {
          /* Initialize the Rx buffer Id for periodic event request */
          LucTxBufferId = LpPduIdTable->ucTxBufferId;
          LpTxBufferId = Dcm_GaaBufferConfig[LucTxBufferId].pBufferArea;
        }
        #else
        /* Initialize the Rx buffer Id for periodic event request */
        LucTxBufferId = LpPduIdTable->ucTxBufferId;
        LpTxBufferId = Dcm_GaaBufferConfig[LucTxBufferId].pBufferArea;
        #endif
      }
      #endif
    
      /* Clear the error flag */
      LblNrcOccured = DCM_FALSE;
      /* Check if the first byte of the Tx buffer has Negative response Id */
      if(LpTxBufferId[DCM_ZERO] == DCM_NEGATIVE_RESPONSE_SID)
      {
         /* Set the error flag */
         LblNrcOccured = DCM_TRUE;
         /* Update the MsgContext for the response length */
         Dcm_GstMsgContext.resDataLen = DCM_THREE;
      }
    
      /* Initialize pointer to Tx buffer Id */
      LblSupResp = DCM_FALSE;
      /*
       * Check if NRC is reported while execution and addressing is Functional
       * and the NRC occurred is either DCM_E_SERVICENOTSUPPORTED or
       * DCM_E_SUBFUNCTIONNOTSUPPORTED or DCM_E_REQUESTOUTOFRANGE
       */
      if ((LucreqType == DCM_ADDR_FUNCTIONAL) && 
          ((LblNrcOccured == DCM_TRUE) &&
           ((LpTxBufferId[2U] == DCM_E_SERVICENOTSUPPORTED) ||
            (LpTxBufferId[2U] == DCM_E_SUBFUNCTIONNOTSUPPORTED) ||
            (LpTxBufferId[2U] == DCM_E_REQUESTOUTOFRANGE))))
      {
        /* Set the suppress positive response flag */
        LblSupResp = DCM_TRUE;

        /* www.autosar.org/bugzilla/show_bug.cgi?id=57613#c6
         * As we need to simulate a positive result of negative / positive response transmission. 
         * This to hide to the application, if response is send or suppressed */
        LddConfStatus = DCM_RES_NEG_OK;
      }
      /*
       * Check if Positive Result of execution and indication of
       * suppressPosRspMsgIndicationBit is set in the Request
       */
      else if((LblNrcOccured  == DCM_FALSE) && (LucsuppressPosResponse == DCM_TRUE))
      {
        /* Set the suppress positive response flag */
        LblSupResp = DCM_TRUE;

        /* www.autosar.org/bugzilla/show_bug.cgi?id=57613#c6
         * As we need to simulate a positive result of negative / positive response transmission. 
         * This to hide to the application, if response is send or suppressed */
        LddConfStatus = DCM_RES_POS_OK;
      }
      /*
       * Only if Communication mode is full communication mode, then the
       * response is transmitted
       */
      else if(Dcm_GaaCommMode[LucNetworkId] == DCM_FULL_COMMUNICATION)
      {
        /* Check if no error occurred during the processing of the request */
        if(LblNrcOccured == DCM_FALSE)
        {        
          if(Dcm_GucPeriodicSID != DCM_READDATABYPERIODICIDENTIFIER)
          {
            /* Updated the response Id to the first byte of Tx buffer */
            LpTxBufferId[DCM_ZERO] = LucIdContext;
            /* Incremented response length by one, since SID is added to response
            */
            pMsgContext->resDataLen++;
          }
          /*
           * Check if the Tx buffer address and the response data
           * address in MsgContext are same
           */
          if ( 
            (Dcm_GucPeriodicSID != DCM_READDATABYPERIODICIDENTIFIER) &&
            (pMsgContext->resData != &(LpTxBufferId[1U]))
          )
          {
            /* Transfer all the response from the MsgContext to Tx buffer */
            for(LucLoopCount = DCM_ZERO; LucLoopCount < pMsgContext->resDataLen; LucLoopCount++)
            {
              /* polyspace<RTE: IDP : Not a defect : No Action Planned > configured memory access index */
              /* polyspace<RTE: NIV : Not a defect : No Action Planned > initialized variable */
              LpTxBufferId[1U + LucLoopCount] = pMsgContext->resData[LucLoopCount];
            }
          }
    
          /* Initialize response data in MsgContext with the base buffer value */
          pMsgContext->resData = LpTxBufferId;
    
          #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
          /* Check if periodic transmission is enabled for the current protocol*/
          if ((Dcm_PrtclTxBufStatus.ucPeriodicIdStatus == DCM_TRUE) &&
              (Dcm_GucPeriodicSID == DCM_READDATABYPERIODICIDENTIFIER))
          {
            /* LddProtocolId = LpPduIdTable->ddProtocolId;
            LucProtocolIDIndex = Dcm_GetProtocolIDIndex(LddProtocolId); */
            Dcm_GucPeriodicSID = DCM_ZERO;
            pMsgContext->resData = LpTxBufferId;
            #if (DCM_PROTOCOL_TRANSTYPE2 == STD_ON)
            if(Dcm_GblResOnPeriodicIdStatus == DCM_TRUE)
            {
              if(Dcm_GaaPduIdTableConfig[LddRxPduId].pPeriodicTxId != NULL_PTR)
              {
                LpPduIdTable = &Dcm_GaaPduIdTableConfig[LddRxPduId];
                LpPerTxPduIdTable = LpPduIdTable->pPeriodicTxId;
                LucMaxNumTxPduid =
                Dcm_GaaPduIdTableConfig[Dcm_GucPeriodicRxPduId].ucNoofPeriodicCon;
    
                for (LucIndex1 = DCM_ZERO; LucIndex1 < Dcm_Dsp_Max_Periodic_DID_Scheduled; LucIndex1++)
                {
                  SchM_Enter_Dcm_ProtclProtection();
                  LucDataStatus = Dcm_GaaDslPeriodicData[LucIndex1].ucDataStatus;
                  SchM_Exit_Dcm_ProtclProtection();
  
                  if( LucDataStatus == DCM_PER_DATA_READY)
                  {
                    for (LucIndex = DCM_ZERO;LucIndex < LucMaxNumTxPduid; LucIndex++)
                    {
                      SchM_Enter_Dcm_ProtclProtection();
                      LucPerPduIdStatus = *(LpPerTxPduIdTable->pPerPduIdStatus);
                      SchM_Exit_Dcm_ProtclProtection();
                      if  ((( LucPerPduIdStatus &
                          (LpPerTxPduIdTable->ucPerPduIdStatusMask)) == DCM_ZERO)
                          && (LblTransmit == DCM_FALSE))
                      {
                        /* Set the status of PerTxPduId as busy */
                        SchM_Enter_Dcm_ProtclProtection();
                        *(LpPerTxPduIdTable->pPerPduIdStatus) |= LpPerTxPduIdTable->ucPerPduIdStatusMask;
                        SchM_Exit_Dcm_ProtclProtection();
    
                        LddTxPduId = LpPerTxPduIdTable->ddPerTxPduId;
    
                        Dcm_GddDcmPeriodicTxConfPduId = (PduIdType) LpPerTxPduIdTable->usPerTxConfmPduId;
          
                        /* to break the loop */
                        LucIndex = LucMaxNumTxPduid;
                        SchM_Enter_Dcm_ProtclProtection();
                        Dcm_GaaDslPeriodicData[LucIndex1].ucDataStatus = DCM_PER_DATA_BUSY;
                        LpPerTxPduIdTable->ucPeriBufferIndex = LucIndex1;
                        SchM_Exit_Dcm_ProtclProtection();
                        LblTransmit = DCM_TRUE;
                        /* Invoke the Dcm_DslTransmit function */
                        Dcm_DslTransmit(LddTxPduId, DCM_TRUE, LblROEType2);
                      }
    
                      LpPerTxPduIdTable++;
                    }
                  }
                }
              }
            }
            else
            #endif
            {
              Dcm_DslTransmit(LddTxPduId, DCM_TRUE, LblROEType2);
            }  
          }
          else
          #endif
          {
            Dcm_DslTransmit(LddTxPduId, DCM_FALSE, LblROEType2);
          }
        }
        else
        {
          /*
           * Initialize response data in MsgContext with the base buffer value
           * in case of NRC
           */
          pMsgContext->resData = LpTxBufferId;
          /* Invoke the Dcm_DslTransmit function */
          Dcm_DslTransmit(LddTxPduId, DCM_FALSE, LblROEType2);
        }  
      }
      /* DCM_NO_COMMUNICATION */
      else
      {      
        /* Set the suppress positive response flag */
        LblSupResp = DCM_TRUE;
        if(LblNrcOccured == DCM_FALSE)
        {
          /* Error because of DCM_NO_COMMUNICATION */
          LddConfStatus = DCM_RES_POS_NOT_OK;
        }
        else
        {
          /* Error because of DCM_NO_COMMUNICATION */
          LddConfStatus = DCM_RES_NEG_NOT_OK;
        }
      }
      
      if(LblSupResp == DCM_TRUE)
      {
        uint8 LucIdx;
        Dcm_ConfirmationFunType LpConfirmationFun;
        Dcm_IdContextType SID = LucIdContext & DCM_SID_MASK;
        /*
         * Provide the confirmation to DSP/RTE based on where the service
         * was implemented
         */
        DspInternal_DcmConfirmation(LucIdContext, LddRxPduId, LddConfStatus);

        /* polyspace +17 MISRA-C3:2.1 [Justified:Low] "Not a defect" */
        /* polyspace +2 MISRA-C3:14.3 [Justified:Low] "Not a defect" */
        #if (DCM_REQUEST_MANUFACTURER_INDICATION_ENABLED == STD_ON)
            for(LucIdx = DCM_ZERO;
            LucIdx < Dcm_Number_Of_Request_Manufacturer_Indication;
            LucIdx++)
        {
          LpConfirmationFun = Dcm_GetManuConfirmationFun(LucIdx);
          if(LpConfirmationFun != NULL_PTR)
          {
            (void)LpConfirmationFun
              (SID, LpPduIdTable->ucRxAddrType,
              (uint16)LpPduIdTable->ucProRxTesterSrcAddr,
              (Dcm_ConfirmationStatusType)LddConfStatus);
          }
        }
        #endif
	      /* polyspace +2 DEFECT:USELESS_IF [Justified:Low] "Not a defect" */
        /* polyspace +2 MISRA-C3:14.3 [Justified:Low] "Not a defect" */
        #if (DCM_REQUEST_SUPPLIER_INDICATION_ENABLED == STD_ON)
        for(LucIdx = DCM_ZERO;
            LucIdx < Dcm_Number_Of_Request_Supplier_Indication;
            LucIdx++)
        {
          LpConfirmationFun = Dcm_GetSuppConfirmationFun(LucIdx);
          if(LpConfirmationFun != NULL_PTR)
          {
            (void)LpConfirmationFun
              (SID, LpPduIdTable->ucRxAddrType,
              (uint16)LpPduIdTable->ucProRxTesterSrcAddr,
              (Dcm_ConfirmationStatusType)LddConfStatus);
          }
        }
        #endif
        
        /* Check if pre compile option DCM_PERIODIC_TRANS_ENABLED is enabled */
        #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  
        /* Check if periodic transmission is enabled for the current protocol */
        if(Dcm_GblResOnPeriodicIdStatus == DCM_TRUE)
        {
          /* Clear the periodic status to Idle if response is suppressed */
          Dcm_GblResOnPeriodicIdStatus = DCM_FALSE;
        }
        #endif
        if((Dcm_GblNormalReq == DCM_TRUE) &&
         (Dcm_TxRespStatus.ucPagedTrans == DCM_FALSE))
        {
         /* Clear the normal request status to idle if response is suppressed */
          Dcm_GblNormalReq = DCM_FALSE;
        }
  
        /* Reset the status of the RxPduId 
         * operations are cancelled and variables are initalized */
        Dcm_DslStatusReset();
      }
    }
    else
    {
      DCM_REPORT_ERROR(DCM_COPY_TXDATA_SID, DCM_E_PARAM);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_DsdStartPagedProcessing                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API will give the complete response length to  **
**                        DCM and starts page buffer handling.                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this API.  **
**                                                                            **
** Remarks              : Global Variable(s) :Dcm_TimerReqFlagStatus,         **
**                        Dcm_GddCurrentLength,                               **
**                        Dcm_GaaBufferConfig, Dcm_TxRespStatus               **
**                        Dcm_GaaPduIdTableConfig                             **
**                        Function(s) invoked :                               **
**                        Dcm_DspUpdatePage,                                  **
**                        Dcm_DslStatusReset, DspInternal_DcmConfirmation     **
**                                                                            **
*******************************************************************************/
#if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
FUNC(void, DCM_CODE) Dcm_DsdStartPagedProcessing
(P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  /* Local pointer variable */
  P2CONST(Dcm_BufferConfig, AUTOMATIC, DCM_APPL_CONST) LpBufVar;
  /* Local pointer variable */
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST) LpPduIdTable;
  /* Local pointer to the Tx buffer */
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBufferId;
  /* Local variable for buffer size */
  uint32 LulBufferSize;
  /* Local variable for RxPduId */
  PduIdType LddRxPduId;
  /* Local variable for Tx buffer Id */
  uint8 LucTxBufferId;
  /* Local variable for suppress positive response indication */
  uint8 LucsuppressPosResponse;

  /* Initialize the suppress positive response indication from MsgContext */
  LucsuppressPosResponse = pMsgContext->msgAddInfo.suppressPosResponse;
  /* Initialize RxPduId from the MsgContext */
  LddRxPduId = pMsgContext->dcmRxPduId;
  /* Initialize pointer to the PduId table configured for RxPduId */
  LpPduIdTable = &Dcm_GaaPduIdTableConfig[LddRxPduId];
  /* Check if the response is to be suppressed */
  if(LucsuppressPosResponse == DCM_FALSE)
  {
    /* Set global bit variable indicating first page is to be transmitted */
    Dcm_TxRespStatus.ucFirstPageTrans = DCM_TRUE;
    /* Set global bit variable indicating paged transmission has started */
    Dcm_TxRespStatus.ucPagedTrans = DCM_TRUE;
    /* Initialize the global variable to the complete response length that is
    * to be transmitted
    */
    Dcm_GddCurrentLength = pMsgContext->resDataLen;
    /* Initialize the Tx buffer Id from PduId table */
    LucTxBufferId = LpPduIdTable->ucTxBufferId;
    /* Initialize pointer to the buffer configuration structure */
    LpBufVar = &Dcm_GaaBufferConfig[LucTxBufferId];
    /* Initialize TxPduId's buffer size */
    LulBufferSize = LpBufVar->ulBufferSize;
    /* Initialize pointer to Tx buffer where the response is to be stored */
    LpTxBufferId = LpBufVar->pBufferArea;
    /*
    * Increment the Tx buffer pointer by one byte, to store the response
    * Id in the first byte
    */
    LpTxBufferId++;
    /* Decrement the buffer size that is passed to the update page function */
    LulBufferSize--;

    Dcm_DspUpdatePage(LpTxBufferId, LulBufferSize);

    /* Delete this code #6174 by Jin 170104 */
    /* Start the paged buffer timeout timer */
    /*
    DCM_START_TIMER(DCM_PAGED_BUFFER_TIMER, Dcm_PagedBufferTimeout);
    SchM_Enter_Dcm_TimerProtection();
    Dcm_TimerReqFlagStatus.ucPagedBufferTimer = DCM_TRUE;
    SchM_Exit_Dcm_TimerProtection();
    */
  }
  else
  {
    /* Reset the status of the RxPduId */
    Dcm_DslStatusReset();

    /* www.autosar.org/bugzilla/show_bug.cgi?id=57613#c6
     * As we need to simulate a positive result of negative / positive response transmission. 
     * This to hide to the application, if response is send or suppressed */

    /* Invoke the confirmation function   */
    DspInternal_DcmConfirmation(pMsgContext->idContext, LddRxPduId,
      (Dcm_ConfirmationStatusType)DCM_RES_POS_OK);
  }
}
#endif /* (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : Dcm_DsdProcessPage                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API requests the transmission of the filled    **
**                        page during paged transmission.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : FilledPageLen                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this API.  **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_DspSerPgStatus,            **
**                        Dcm_GddCurrentLength, Dcm_TxRespStatus,             **
**                        Dcm_GpMsgContext, Dcm_GaaBufferConfig,              **
**                        Dcm_GddTxResponseLen , Dcm_GaaPduIdTableConfig      **
**                        Function(s) invoked :                               **
**                        Dcm_DslTransmit                                     **
**                                                                            **
*******************************************************************************/
#if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
FUNC(void, DCM_CODE) Dcm_DsdProcessPage(Dcm_MsgLenType FilledPageLen)
{
  /* Local Pointer variable */
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST) LpVariable;
  /* Local pointer to the Tx buffer */
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBufferId;
  /* Local variable for RxPduId */
  PduIdType LddRxPduId;
  /* Local variable for RxPduId */
  PduIdType LddTxPduId;
  /* Local index to TxPduId buffer */
  uint8 LucTxBufferId;

  /* Initialize RxPduId from the MsgContext */
  LddRxPduId = Dcm_GstMsgContext.dcmRxPduId;
  /* Update the response length with FilledPageLen */
  Dcm_GstMsgContext.resDataLen = FilledPageLen;
  /* Initialize pointer to the RxPduId table */
  LpVariable = &Dcm_GaaPduIdTableConfig[LddRxPduId];
  /* Initialize Tx buffer Id configured in the RxPduId table */
  LucTxBufferId = LpVariable->ucTxBufferId;
  /* Initialize TxPduId configured in the RxPduId table */
  LddTxPduId = LpVariable->ddTxPduId;

  /* Initialize pointer to the TxPduId buffer */
  LpTxBufferId = Dcm_GaaBufferConfig[LucTxBufferId].pBufferArea;

  /* Check if it is first page that is to be transmitted */
  if(Dcm_TxRespStatus.ucFirstPageTrans == DCM_TRUE)
  {
    /*
    * Increment the complete response data length since service id is
    * appended
    */
    Dcm_GstMsgContext.resDataLen = Dcm_GddCurrentLength + DCM_ONE;
    /*
    * Update the global variable with the response length filled for the
    * first time
    */
    Dcm_GddTxResponseLen = FilledPageLen + DCM_ONE;
    /* Store the Response Id to the first byte of the Tx buffer */
    LpTxBufferId[DCM_ZERO] = Dcm_GstMsgContext.idContext;
  }
  /* Initialize resData to the TxBufferId buffer area */
  Dcm_GstMsgContext.resData = LpTxBufferId;
  /* Invoke the transmit once the response is ready */
  Dcm_DslTransmit(LddTxPduId, DCM_FALSE, DCM_FALSE);
  /* Update the response length that is to be transmitted */
  if(Dcm_GddCurrentLength <= FilledPageLen)
  {
    /* Set the bit indicating the last page to DSP layer to True */
    Dcm_DspSerPgStatus.ucLastPage = DCM_TRUE;
  }
  else
  {
    /* Update the response length that is to be transmitted */
    Dcm_GddCurrentLength -= FilledPageLen;
  }
}
#endif /* (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace:end<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */
/* polyspace:end<RTE: NIP : Not a defect : No Action Planned > pointer is not null */
/* polyspace:end<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:end<RTE: IDP : Not a defect : No Action Planned > configured memory access index */
/* polyspace:end<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/*
polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard-Chap 5.1.2)
*/

/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace-end MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:10.4 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
