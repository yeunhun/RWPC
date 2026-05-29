/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE: Dcm_Dsl.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the API definitions  for Dsl layer of Dcm  **
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
** Revision  Date          By                Description                      **
********************************************************************************
** 2.3.4.0   28-Jan-2021   EunKyung Kim      #27941                           **
**                                                                            **
** 2.3.2.0   05-Nov-2020   EunKyung Kim      #26432                           **
**                                                                            **
** 1.0.4     28-10-2016    Jin     Jung      #5535                            **
**                                                                            **
** 1.0.3     03-03-2016    Sungeol Baek      #4267, RTRT reflection           **
**                                                                            **
** 1.0.2     10-08-2015    Youngjin Yun      #2977                            **
**                                                                            **
** 1.0.1     24-03-2015    Sungeol Baek      #2370                            **
**                                                                            **
** 1.0.0     09-01-2013    Autron            Initial Version                  **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm.h"
#include "Dcm_Ram.h"

#if(DCM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#include "Rte_Dcm.h"
#include "SchM_Dcm.h"
#include "ComM_Dcm.h"
#include "PduR_Dcm.h"
#include "Dcm_DslInternal.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_Dsl.h"
#include "Dcm_Config.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:10.4 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace:begin<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > configured memory access index */
/* polyspace:begin<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */

/*******************************************************************************
** Function Name        : DslInternal_ResponseOnOneDataByPeriodicId           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API provides the processing of one event,      **
**                        requested by the DSP internally                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : PeriodicId                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_StatusType                                      **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_GaaCommMode, Dcm_GblResOnPeriodicIdStatus,      **
**                        Dcm_GblNormalReq, Dcm_GaaPduIdTableConfig           **
**                        Dcm_GaaBufferConfig, Dcm_GstCurrentTimingValue,     **
**                        Dcm_GucPeriodicRxPduId , Dcm_GddRxPduId             **
**                        Dcm_GaaProtocolConfig                               **
**                        Function(s) invoked : Dcm_DsdIndication             **
**                                                                            **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"
#if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
FUNC(Dcm_StatusType, DCM_CODE) DslInternal_ResponseOnOneDataByPeriodicId
(uint8 PeriodicId)
{
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST)LpPduIdTable;
  #if (DCM_PROTOCOL_TRANSTYPE2 == STD_OFF)
  P2CONST(Dcm_ProtocolConfig, AUTOMATIC, DCM_APPL_CONST)LpProtocolConfig;
  #endif
  Dcm_ProtocolType LddProtocolId;
  uint8 LucProtocolIDIndex;
  uint8 LucNetworkId;
  /* Local pointer for Rx buffer area */
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpRxBufferId;
  /* Local variable to store return type status of the API */
  Dcm_StatusType LddResponseStatus;

  /* Local variable for Rx buffer Id */
  uint8 LucRxBufferId;
  /* Local variable for return status of Indication */
  boolean LblResponseStatus;

  /* Initialize the return value LddResponseStatus */
  LddResponseStatus = DCM_E_PERIODICID_NOT_ACCEPTED;
  /* Initialize pointer to PduId table corresponding to the RxPduId */
  LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GucPeriodicRxPduId];
  LucNetworkId = LpPduIdTable->ucRxComChannelRef;

  /* Check if the Periodic process is ongoing and communication mode is
   * FULL_COM_MODE and the last periodic identifier event request from
   * application is finished and if any normal request is ongoing
   */
  if((Dcm_GaaCommMode[LucNetworkId] == DCM_FULL_COMMUNICATION)
    #if (DCM_PROTOCOL_TRANSTYPE2 == STD_OFF)
   && ((Dcm_GblResOnPeriodicIdStatus == DCM_FALSE) &&
      (Dcm_GblNormalReq == DCM_FALSE))
    #endif
    )
  {
      SchM_Enter_Dcm_RxPduIdProtection();
      /* FIXME Need to block int */
      /* Change the periodic status to ongoing */
      Dcm_GblResOnPeriodicIdStatus = DCM_TRUE;
      SchM_Exit_Dcm_RxPduIdProtection();

      /* type2 is on , rx/tx is seperated with UDS common buffer */
      #if (DCM_PROTOCOL_TRANSTYPE2 == STD_ON)
      if(Dcm_GaaPduIdTableConfig[Dcm_GucPeriodicRxPduId].pPeriodicTxId != NULL_PTR)
      {
        LucRxBufferId = Dcm_GaaPduIdTableConfig[Dcm_GucPeriodicRxPduId].ucPeriTransRxBufferIndex;
      }
      else
      {
        if((Dcm_GblResOnPeriodicIdStatus == DCM_FALSE) && (Dcm_GblNormalReq == DCM_FALSE))
        {
          /* Initialize the Rx buffer Id for periodic event request */
          LucRxBufferId = Dcm_GaaPduIdTableConfig[Dcm_GucPeriodicRxPduId].ucRxBufferId;
        }
        else
        {
          LucRxBufferId = 0u;
        }
      }
       /* FIXME  FIXME  FIXME  FIXME  FIXME  FIXME  FIXME  FIXME  FIXME */
      /* Initialize pointer to PduId table corresponding to the RxPduId */
      LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GucPeriodicRxPduId];
      /* Get the protocol Id */
      LddProtocolId = LpPduIdTable->ddProtocolId;
      /* Get Protocol Index */
      LucProtocolIDIndex = Dcm_GetProtocolIDIndex(LddProtocolId);

      /*FIXME: LpProtocolConfig = &Dcm_GaaProtocolConfig[LucProtocolIDIndex]; */

      Dcm_GaaReqLength[LucProtocolIDIndex] = 3;

      #else
      /* Initialize the Rx buffer Id for periodic event request */
      LucRxBufferId = Dcm_GaaPduIdTableConfig[Dcm_GucPeriodicRxPduId].ucRxBufferId;
      #endif

    /* MISRA Rule        : 9.1
         Message           : The variable '%s' is possibly unset at this point
         Reason            : "LucRxBufferId" value is checked and
                         verified when
                              DCM_PROTOCOL_TRANSTYPE2 is switched STD_ON.
         Verification      : However, part of the code is verified manually and
                              it is not having any impact.
       */
      /* Initialize pointer to the Rx buffer area */
      LpRxBufferId = Dcm_GaaBufferConfig[LucRxBufferId].pBufferArea;
      /* Update the first byte with service Id 0x22 */
      LpRxBufferId[DCM_ZERO] = DCM_READDATABYIDENTIFIER;
      /* Update the second byte with 0xF2 */
      LpRxBufferId[DCM_ONE] = DCM_HBYTE_PERIODICID;
      LpRxBufferId[DCM_TWO] = PeriodicId;
      
      /* Start the Timer P2ServerMax */
      DCM_START_TIMER(DCM_P2SERVERMAX_TIMER,
        (Dcm_GstCurrentTimingValue.Timer_P2ServerMax -
        Dcm_GstCurrentTimingValue.Timer_P2ServerAdjust));
      SchM_Enter_Dcm_TimerProtection();
      Dcm_TimerReqFlagStatus.ucP2MaxTimer = DCM_TRUE;
      SchM_Exit_Dcm_TimerProtection();
      /* Invoke the Indication function */
      LblResponseStatus = Dcm_DsdIndication(Dcm_GucPeriodicRxPduId, DCM_FALSE, DCM_TRUE, DCM_FALSE);
      /*
      * Check if all the verifications in the indication function was
      * successful
      */
      if(LblResponseStatus == DCM_TRUE)
      {
        /* Update the return value */
        LddResponseStatus = DCM_E_OK;
        
        /* Change the periodic status to ongoing */
        /* Dcm_GblResOnPeriodicIdStatus = DCM_TRUE; */
        
        /*
        * Update the global variable for RxPduId with the PduId for the
        * periodic request
        */
        Dcm_GddRxPduId = Dcm_GucPeriodicRxPduId;

        #if (DCM_PROTOCOL_TRANSTYPE2 == STD_OFF)
        /* Initialize pointer to PduId table corresponding to the RxPduId */
        LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GucPeriodicRxPduId];
        /* Get the protocol Id */
        LddProtocolId = LpPduIdTable->ddProtocolId;
        /* Get Protocol Index */
        LucProtocolIDIndex = Dcm_GetProtocolIDIndex(LddProtocolId);

        LpProtocolConfig = &Dcm_GaaProtocolConfig[LucProtocolIDIndex];

        SchM_Enter_Dcm_RxPduIdProtection();
        *(LpPduIdTable->pPduIdStatus) |= LpPduIdTable->ucPduIdStatusMask;
        SchM_Exit_Dcm_RxPduIdProtection();

        /* Set the status of protocol status */
        SchM_Enter_Dcm_ProtclProtection();
        *(LpProtocolConfig->pProtocolStatus) |= (LpProtocolConfig->ucPrtclStatusMask);
        SchM_Exit_Dcm_ProtclProtection();
        #endif
        
    }
    else
    {
      /* Change the periodic status to idle */
      Dcm_GblResOnPeriodicIdStatus = DCM_FALSE;
    }

  }
  /* Return DCM_E_OK if periodic Id is accepted
  * else DCM_E_PERIODICID_NOT_ACCEPTED
  */
  
  return(LddResponseStatus);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DslTransmit                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is invoked by DSD when the response   **
**                        is ready in the DSD layer                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LddTxPduId, LblPeriodicTransmission,                **
**                        LblROETransmission                                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_PrtclTxBufStatus,       **
**                        Dcm_TxRespStatus, Dcm_TimerReqFlagStatus,     **
**                        Dcm_GaaTimer, Dcm_GblNormalReq , Dcm_GaaCommMode    **
**                        Dcm_GblResOnPeriodicIdStatus, Dcm_GucPeriodicRxPduId**
**                        Dcm_GaaCbkReqServices, Dcm_GaaPduIdTableConfig      **
**                        Dcm_GpPerMsgContext , Dcm_GddRxPduId                **
**                        Function(s) invoked : PduR_DcmTransmit              **
**                        Dcm_DsdConfirmation, Dcm_DslStatusReset,            **
**                        Dcm_DspClearSecurityTimer, Dcm_DslCheckPrtclStatus, **
**                        Xxx_StartProtocol                                   **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DslTransmit(PduIdType LddTxPduId,
  boolean LblPeriodicTransmission, boolean LblROETransmission)
{
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST)LpPduIdTable;

  PduInfoType LddPduInfo;
  Std_ReturnType LddReturnValue;
  #if ((DCM_PROTOCOL_TRANSTYPE2 == STD_ON) && \
    (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON))
  P2VAR(Dcm_DslPeriodicTxId, AUTOMATIC, DCM_APPL_DATA) LpPerTxPduIdTable;
  uint8 LucMaxNumTxPduid;
  uint8 LucIndex;
  /* uint8 LucProtocolIDIndex; */

  #endif
  uint8 LucNetworkId;

  if (Dcm_GddRxPduId >= Dcm_Num_Of_PduidTableConfig)
  {
    /* Det Error */
  }
  else if(Dcm_PrtclTxBufStatus.ucProtclStatus == DCM_TRUE)
  {
    /* Check if the negative error flag is FALSE */
    if(Dcm_TxRespStatus.ucNegResp == DCM_FALSE)
    {
      /* Initialize pointer to PduId table corresponding to the RxPduId */
      LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];

      LucNetworkId = LpPduIdTable->ucRxComChannelRef;
      
      if(LucNetworkId < Dcm_No_Of_Comm_Channels)   
      {
        if (
          (Dcm_GaaCommMode[LucNetworkId] == DCM_FULL_COMMUNICATION) &&
          (
            (Dcm_GblNormalReq == DCM_TRUE)
            #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
            || 
            (Dcm_GblResOnPeriodicIdStatus == DCM_TRUE)
            #endif
            
            #if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
            || 
            (Dcm_GucResOnEventStatus == DCM_ROEONGOING)
            #endif
          )
        )
        {
          #if(DCM_PROTOCOL_TRANSTYPE2 == STD_ON)
          if (
            (LblPeriodicTransmission == DCM_TRUE) ||
            (LblROETransmission == DCM_TRUE)
          )
          {
            #if ((DCM_PROTOCOL_TRANSTYPE2 == STD_ON) && \
              (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON))
            LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GucPeriodicRxPduId];
            /* LucProtocolIDIndex = Dcm_GetProtocolIDIndex(LpPduIdTable->ddProtocolId); */
        
            if (
              (Dcm_GblResOnPeriodicIdStatus == DCM_TRUE) &&
              (LblPeriodicTransmission == DCM_TRUE) &&
              (LpPduIdTable->pPeriodicTxId != NULL_PTR)
            )
            {
              /* Update the PduInfo with the buffer address and the data length */
              SchM_Enter_Dcm_ProtclProtection();
              LddPduInfo.SduLength = (uint16)Dcm_GpPerMsgContext->resDataLen;
              LddPduInfo.SduDataPtr = Dcm_GpPerMsgContext->resData;
              SchM_Exit_Dcm_ProtclProtection();
            }
            #endif
            
            #if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)    
            if(LblROETransmission == DCM_TRUE)
            {
              /* Update the PduInfo with the buffer address and the data length */
              LddPduInfo.SduLength = (uint16)Dcm_GpRoeMsgContext->resDataLen;
              LddPduInfo.SduDataPtr = Dcm_GpRoeMsgContext->resData;
            }
            #endif
          }
          else 
          #endif
          {
            /* FIXME: typecasting problem : PduLengthType
             * possible truncation at implicit conversion to type "unsigned char */
            /* Update the Length of the available buffer in Length parameter */ 
            /* Update the PduInfo with the buffer address and the data length */          
            LddPduInfo.SduLength = (PduLengthType)Dcm_GstMsgContext.resDataLen;
            LddPduInfo.SduDataPtr = Dcm_GstMsgContext.resData;
          }
          /* Stop the P2ServerMax timer */
          DCM_STOP_TIMER(DCM_P2SERVERMAX_TIMER);
          SchM_Enter_Dcm_TimerProtection();
          Dcm_TimerReqFlagStatus.ucP2MaxTimer = DCM_FALSE;
          SchM_Exit_Dcm_TimerProtection();
          
          #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
          if(Dcm_TxRespStatus.ucPagedTrans == DCM_TRUE)
          {
            if(Dcm_TxRespStatus.ucFirstPageTrans == DCM_TRUE)
            {
              /* Invoke PduR_DcmTransmit function */
              LddReturnValue = Dcm_PduRTransmit(LddTxPduId, &LddPduInfo);
            }
            else
            {
              LddReturnValue = E_OK;
            }
          }
          else
          #endif
          {
            /* FIXME : LddPduInfo.SduLength is zero */
            
            /* Invoke PduR_DcmTransmit function */
            LddReturnValue = Dcm_PduRTransmit(LddTxPduId, &LddPduInfo);
          }
          /* Check if the transmission was successful */
          if(LddReturnValue == E_OK)
          {
            #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
            if(Dcm_TxRespStatus.ucPagedTrans == DCM_TRUE)
            {
              Dcm_TxRespStatus.ucDslPagedTrans = DCM_TRUE;
            }
            #endif
            #if (DCM_PROTOCOL_TRANSTYPE2 == STD_ON)
            if(LblPeriodicTransmission == DCM_FALSE)
            #endif
            {
              Dcm_TxRespStatus.ucNormResponse = DCM_TRUE;
            }
          }
          else
          {
            if(LblPeriodicTransmission == DCM_TRUE)
            {
              #if ((DCM_PROTOCOL_TRANSTYPE2 == STD_ON) && \
              (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON))
              LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GucPeriodicRxPduId];
              LpPerTxPduIdTable = LpPduIdTable->pPeriodicTxId;
              LucMaxNumTxPduid = LpPduIdTable->ucNoofPeriodicCon;
  
              for (LucIndex = DCM_ZERO; (LucIndex < LucMaxNumTxPduid); LucIndex++)
              {
                if(LddTxPduId == LpPerTxPduIdTable->usPerTxConfmPduId)
                {
                  LucIndex = LucMaxNumTxPduid;
                  
                  /* Clear the  status  of periodic TxPduId */                
                  SchM_Enter_Dcm_ProtclProtection();
                  *(LpPerTxPduIdTable->pPerPduIdStatus) &= ~(LpPerTxPduIdTable->ucPerPduIdStatusMask);
                  Dcm_GaaDslPeriodicData[LpPerTxPduIdTable->ucPeriBufferIndex].ucDataStatus = DCM_PER_DATA_IDLE;
                  LpPerTxPduIdTable->blBufferProvided = DCM_FALSE;
                  SchM_Exit_Dcm_ProtclProtection();
                }
                else
                {
                  LpPerTxPduIdTable++;
                }
              }
              #endif
            }
            /* Provide negative confirmation in case of transmission failure */
            Dcm_DsdConfirmation(NTFRSLT_E_NOT_OK);
  
            #if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
            if(Dcm_GucResOnEventStatus == DCM_IDLE)
            {
              Dcm_GblNormalReq = DCM_FALSE;
              /* Reset the status of the RxPduId */
              Dcm_DslStatusReset();
            }
            else
            {
              /* do nothing */
            }
            #else

	    /* polyspace +1 MISRA-C3:10.3 [Justified:Low] "Not a defect" */
            Dcm_GblNormalReq = DCM_FALSE;
            /* Reset the status of the RxPduId */
            Dcm_DslStatusReset();
            #endif
          }
        }
        else
        {
          /* Silent com state - reset request status*/
          if(Dcm_GblNegavieResStatus == DCM_TRUE)
          {
            /*  Clear  the  Normal  request  status  to  FALSE  */
            Dcm_GblNormalReq = (boolean)DCM_FALSE;
            /*  Reset  the  status  of  the  RxPduId  */
            Dcm_DslStatusReset();            
          }
          else
          {
		    /* Silent com state - wait until change full com*/
            Dcm_GblNegavieResStatus = (boolean)DCM_TRUE;
          }
        }
      }
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      if(Dcm_TxRespStatus.ucPagedTrans == DCM_TRUE)
      {
        /* Stop the paged buffer timeout timer */
        DCM_STOP_TIMER(DCM_PAGED_BUFFER_TIMER);
        SchM_Enter_Dcm_TimerProtection();
        Dcm_TimerReqFlagStatus.ucPagedBufferTimer =
          DCM_FALSE;
        SchM_Exit_Dcm_TimerProtection();
      }
      #endif
    }
    else
    {
      Dcm_TxRespStatus.ucRespPending = DCM_TRUE;
    }
  }
  else
  {
    /* To avoid the QAC warning */
  }
  /* MISRA Rule        : 14.2
    Message            : This statement has no side-effect - it can be removed
    Reason             : To avoid Un used variable warning.
    Verification       : However, part of the code
                         is verified manually and
                       it is not having any impact.
  */
  DCM_UNUSED(LblROETransmission);
}

/*******************************************************************************
** Function Name        : Dcm_DslSetParameters                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function loads the needed parameters into the  **
**                        global variables after the successful start of the  **
**                        protocol                                            **
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
** Remarks              : Global Variable(s) : Dcm_GaaPduIdTableConfig        **
**                        Dcm_GddProtocolId, Dcm_GaaProtocolConfig,           **
**                        Dcm_GucPrtclPriority, Dcm_GddCurrentSession         **
**                        Dcm_GddSecurityLevel, Dcm_GpMsgContext              **
**                        Dcm_GstCurrentTimingValue , Dcm_GddRxPduId          **
**                        Dcm_GulChannelIdentifier ,                          **
**                        Function(s) invoked : ComM_DCM_ActiveDiagnostic,    **
**                                                                            **
*******************************************************************************/
#if(DCM_DSP_SESSION_REF == STD_ON)
FUNC(void, DCM_CODE) Dcm_DslSetParameters(void)
{
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST) rxPduId;
  
  /* Check if the pre compile option DCM_DEV_ERROR_DETECT is enabled */
  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_GddRxPduId >= Dcm_Num_Of_PduidTableConfig)
  {
    /* Report to DET */
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID, 
                                       DCM_SYNC_WRITE_DATA_SID, DCM_E_PARAM_POINTER);
  }
  else
  #endif
  {
    P2CONST(Dcm_ProtocolConfig, AUTOMATIC, DCM_CONST) cfgProtocol;
    
    /* Get the pointer to the corresponding RxPduId structure */
    rxPduId = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
    cfgProtocol = Dcm_DsdInternal_GetProcotocolByRxPduId(Dcm_GddRxPduId);
  
    if(NULL_PTR != cfgProtocol)
    {   
      P2CONST(Dcm_DiagSessionConfigType, AUTOMATIC, DCM_APPL_CONST) cfgSession;
  
      Dcm_GddProtocolId = rxPduId->ddProtocolId;    
      Dcm_GucPrtclPriority = cfgProtocol->ucProtocolPrio;    
      Dcm_GblProtocolEndianess = cfgProtocol->blProtocolEndiannessConvEnabled;
    
      if(Dcm_GblJumpToBootloader == DCM_FALSE)
      {
        /* Reset the session level in the global variable */
        Dcm_GddCurrentSession = DCM_DEFAULT_SESSION;
      }
      else
      {
        /* if ECU is started from FBL , shall keep the session that was changed in the FBL */
	/* polyspace +1 MISRA-C3:10.3 [Justified:Low] "Not a defect" */
        Dcm_GblJumpToBootloader = DCM_FALSE;
      }
    
      /* Reset the security level in the global variable */
      Dcm_GddSecurityLevel = DCM_SEC_LEV_LOCKED;
    
      /* Update the RxPduId in the message context */
      Dcm_GstMsgContext.dcmRxPduId = Dcm_GddRxPduId;

      (void)SchM_Switch_Dcm_DcmDiagnosticSessionControl(Dcm_GddCurrentSession);

      cfgSession = Dcm_DsdInternal_GetSessionCfg(cfgProtocol, Dcm_GddCurrentSession, NULL_PTR);      
      if(NULL_PTR != cfgSession)
      {
        /* Set the P2ServerMax and P2StarServerMax timer values to the
          corresponding session timer values */
        Dcm_GstCurrentTimingValue.Timer_P2ServerMax = cfgSession->usSesP2ServerMax;
    
        Dcm_GstCurrentTimingValue.Timer_P2StarServerMax = cfgSession->usSesP2StrServerMax;
      }
      else
      {
        /* FIXME .. hard code */
        /*Set the P2ServerMax and P2StarServerMax timer values to the corresponding
           session timer values */
        Dcm_GstCurrentTimingValue.Timer_P2ServerMax = 50U;
    
        Dcm_GstCurrentTimingValue.Timer_P2StarServerMax = 5000U;
      }
      
      /*Update with default value 5ms*/
      Dcm_GstCurrentTimingValue.Timer_S3Server = DCM_TIMSTR_S3_SERVER;
    
      /* Set the ServerAdjust timer values to the to the corresponding protocol
         timer values */
      Dcm_GstCurrentTimingValue.Timer_P2ServerAdjust = cfgProtocol->usTimStrP2ServerAdjust;
    
      /*Update with default value 0ms*/
      Dcm_GstCurrentTimingValue.Timer_P2StrServerAdjust = cfgProtocol->usTimStrP2StarServerAdjust;
    
      /*Get the Channel Identifier associated to the received Pdu*/
      Dcm_GulChannelIdentifier = rxPduId->ulProRxChannelId;
    
      /* Invoke the API to Activate diagnostic session */
      (void)ComM_DCM_ActiveDiagnostic((NetworkHandleType)Dcm_GulChannelIdentifier);
    }
    else
    {
      DCM_REPORT_ERROR(DCM_SYNC_WRITE_DATA_SID, DCM_E_INTERFACE_BUFFER_OVERFLOW);
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DslStatusReset                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function starts the S3 server timer and also   **
**                        clears the RxPduId status                           **
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
** Remarks              : Global Variable(s) : Dcm_GddCurrentSession,         **
**                        Dcm_TimerReqFlagStatus,                          **
**                        Dcm_GaaProtocolConfig, Dcm_GstCurrentTimingValue,   **
**                        Dcm_GddRxPduId ,Dcm_GaaPduIdTableConfig             **
**                        Function(s) invoked : ComM_DCM_InactiveDiagnostic   **
**                        Dcm_GetProtocolIDIndex                              **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DslStatusReset(void)
{
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST)LpPduIdTable;
  Dcm_ProtocolType LddProtocolId;
  uint8 LucProtocolIDIndex = DCM_SERVICE_NOT_CONFIGURED;

  /* Check if the pre compile option DCM_DEV_ERROR_DETECT is enabled */
  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_GddRxPduId >= Dcm_Num_Of_PduidTableConfig)
  {
    /* Report to DET */
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID, 
                                       DCM_SYNC_WRITE_DATA_SID, DCM_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* Initialize the pointer to the PduId table */
    LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
  
    /* Check whether the current session is non default session */
    if(CHECK_NONDEFAULT_SESSION(Dcm_GddCurrentSession))
    {
      /* Start the s3 timer value */
      DCM_START_TIMER(DCM_S3SERVER_TIMER, (Dcm_GstCurrentTimingValue.Timer_S3Server));
      SchM_Enter_Dcm_TimerProtection();
      Dcm_TimerReqFlagStatus.ucS3Timer = DCM_TRUE;
      SchM_Exit_Dcm_TimerProtection();
    }
    else
    {
      /* Invoke API to inactivate diagnostic session */
      (void)ComM_DCM_InactiveDiagnostic((NetworkHandleType)Dcm_GulChannelIdentifier);
    }
    /* Stop the timer P2ServerMax */
    DCM_STOP_TIMER(DCM_P2SERVERMAX_TIMER);
    SchM_Enter_Dcm_TimerProtection();
    Dcm_TimerReqFlagStatus.ucP2MaxTimer = DCM_FALSE;
    SchM_Exit_Dcm_TimerProtection();
  
    /* Enter the DC */
    LddProtocolId = LpPduIdTable->ddProtocolId;
  
    SchM_Enter_Dcm_RxPduIdProtection();
  
    /* Clear the RxPduId status */
    *(LpPduIdTable->pPduIdStatus) &= (uint8)(~(LpPduIdTable->ucPduIdStatusMask));
  
    /* Exit the DC */
    SchM_Exit_Dcm_RxPduIdProtection();
  
    /* Get Protocal index */
    LucProtocolIDIndex = Dcm_GetProtocolIDIndex(LddProtocolId);

    if(LucProtocolIDIndex < Dcm_Num_Of_ProtocolConfig)
    {
      /* Enter the DC */
      SchM_Enter_Dcm_ProtclProtection();
      /* Clear the protocol status */
      *(Dcm_GaaProtocolConfig[LucProtocolIDIndex].pProtocolStatus) &=
                    (uint8)(~(Dcm_GaaProtocolConfig[LucProtocolIDIndex].ucPrtclStatusMask));
    
      /* Exit the DC */
      SchM_Exit_Dcm_ProtclProtection();
    }
  } 
}

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA-C3:10.4 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace:end<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:end<RTE: IDP : Not a defect : No Action Planned > configured memory access index */
/* polyspace:end<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
