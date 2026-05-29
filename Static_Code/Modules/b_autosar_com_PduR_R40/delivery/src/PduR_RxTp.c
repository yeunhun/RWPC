/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTOEVER Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: PduR_RxTp.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Provision of the functionality of PduR_LoTpStartOfReception(),**
**              PduR_LoTpCopyRxData(),PduR_DETCheckLoTpStartOfReception (),   **
**              PduR_BuffUpdateLoTpStartOfReception(),                        **
**              PduR_<Lo>TpRxIndication(),                                    **
**              PduR_LoTpGWCopyRxData(),PduR_ChangeParameter(),               **
**              PduR_DETCheckChangeParameter(),PduR_DETCheckLoTpCopyRxData(), **
**              PduR_DETCheckLoTpRxIndication(),PduR_DETCheckCancelReceive()  **
**              and PduR_<Up>CancelReceive().                                 **
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
** 2.8.1     07-Jun-2021   HM Shin     #30157                                 **
** 2.6.0     03-Nov-2020   HM Shin     #24937, #24858                         **
** 2.4.0     06-Sep-2019   HM Shin     #18909                                 **
** 2.3.0     22-Aug-2019   JS Lim      #18336, #18851                         **
** 2.2.2     01-Dec-2017   Chan Kim    Redmine #10813, #10820                 **
** 2.2.1     20-Mar-2017   Chan Kim    Redmine #7849                          **
** 2.2.0     01-Feb-2017   Chan Kim    Redmine #6922                          **
** 2.1.5     30-Nov-2016   Chan Kim    Redmine #6568, #6706, #6771            **
** 2.1.4     16-Nov-2016   Chan Kim    Redmine #6681                          **
** 2.1.1     17-Jun-2016   Chan Kim    Redmine #5490, #5632, #5680            **
** 2.1.0     17-Jun-2016   Chan Kim    Redmine #5190, #5250                   **
** 2.0.8     10-Jun-2016   Chan Kim    Redmine #5143                          **
** 2.0.4     19-Feb-2016   Chan Kim    Redmine #3429, #3425, #3813, #3827     **
** 2.0.3     24-Nov-2015   Chan Kim    Redmine #3545, #4519                   **
** 2.0.0     11-Aug-2015   Chan Kim    Redmine #2949                          **
** 1.0.7     10-Jun-2013   Chan Kim    Change code for release Library        **
** 1.0.0     29-Apr-2013   Autoever      Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "PduR.h"                 /* PDU router header file */
#include "PduR_RxTp.h"            /* PduR Rx Tp header */
#include "SchM_PduR.h"            /* SchM header */
#include "string.h"               /* memcpy() */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define PDUR_RXTP_C_AR_RELEASE_MAJOR_VERSION    4
#define PDUR_RXTP_C_AR_RELEASE_MINOR_VERSION    0
#define PDUR_RXTP_C_AR_RELEASE_REVISION_VERSION 3

/* PDUR software version information */
#define PDUR_RXTP_C_SW_MAJOR_VERSION            2
#define PDUR_RXTP_C_SW_MINOR_VERSION            9
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (PDUR_PCTYPES_AR_RELEASE_MAJOR_VERSION !=\
     PDUR_RXTP_C_AR_RELEASE_MAJOR_VERSION)
#error "PduR_RxTp.c : Mismatch in Specification Major Version"
#endif

#if (PDUR_PCTYPES_AR_RELEASE_MINOR_VERSION !=\
     PDUR_RXTP_C_AR_RELEASE_MINOR_VERSION)
#error "PduR_RxTp.c : Mismatch in Specification Minor Version"
#endif

#if (PDUR_PCTYPES_AR_RELEASE_REVISION_VERSION !=\
     PDUR_RXTP_C_AR_RELEASE_REVISION_VERSION)
#error "PduR_RxTp.c : Mismatch in Specification Revision Version"
#endif

#if (PDUR_PCTYPES_SW_MAJOR_VERSION != PDUR_RXTP_C_SW_MAJOR_VERSION)
#error "PduR_RxTp.c : Mismatch in Software Major Version"
#endif

#if (PDUR_PCTYPES_SW_MINOR_VERSION != PDUR_RXTP_C_SW_MINOR_VERSION)
#error "PduR_RxTp.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if ((PDUR_TP_RXINDICATION == STD_ON) && (PDUR_ZERO_COST_OPERATION == STD_OFF))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_DETCheckLoTpStartOfReception(
  PduIdType LddRxPduId, uint8 LucAPIId, uint8 LucModuleType,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) LpBufferSizePtr);

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* */
#endif
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_CANCEL_RECEIVE_SUPPORT == STD_ON) &&\
  (PDUR_TP_RXINDICATION == STD_ON))
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_VAR) PduR_DETCheckCancelReceive(
  PduIdType LddRxPduId, uint8 LucAPIId);

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((PDUR_CANCEL_RECEIVE_SUPPORT == STD_ON) &&
        *(PDUR_TP_RXINDICATION == STD_ON)) */
#endif /* End of if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

#if ((PDUR_ZERO_COST_OPERATION == STD_OFF) && (PDUR_TP_RXINDICATION == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_DETCheckLoTpCopyRxData(
  PduIdType LddRxPduId, uint8 LucModuleType, uint8 LucAPIId,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) LpBufferSizePtr);

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((PDUR_ZERO_COST_OPERATION == STD_OFF) &&
        *(PDUR_TP_RXINDICATION == STD_ON)) */
#endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */

#if ((PDUR_TP_RXINDICATION == STD_ON) && (PDUR_ZERO_COST_OPERATION == STD_OFF))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, PDUR_CODE) PduR_DETCheckLoTpRxIndication(
  PduIdType LddRxPduId, uint8 LucModuleType, uint8 LucAPIId);

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((PDUR_ZERO_COST_OPERATION == STD_OFF) &&
        *(PDUR_TP_RXINDICATION == STD_ON)) */
#endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
/*******************************************************************************
** Function Name        : PduR_LoTpStartOfReception                           **
**                                                                            **
** Service ID           : 0x<LoTpModId>6                                      **
**                                                                            **
** Description          : This function will be called by the transport       **
**                        protocol module at the start of receiving an I-PDU. **
**                        The I-PDU might be fragmented into multiple N-PDUs  **
**                        (FF with one or more following CFs) or might        **
**                        consist of a single N-PDU (SF). The service shall   **
**                        provide the currently available maximum buffer size **
**                        when invoked with TpSdulength equal to 0.           **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PduIdType LddRxPduId, PduLengthType TpSduLength,    **
**                        uint8 LucModuleType, PduLengthType* LpBufferSizePtr **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : BufReq_ReturnType LenBufReqReturn                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_GaaTpRxIndication, PduR_GaaTpStartOfReception, **
**                        PduR_GulGroupMaskValue                              **
**                                                                            **
** Function(s) invoked  : PduR_DETCheckLoTpStartOfReception(),                **
**                        PduR_BuffUpdateLoTpStartOfReception()               **
**                                                                            **
*******************************************************************************/
/* Requirement PDUR507 */
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_RXINDICATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if (PDUR_FOUR_ONE_ONE == STD_ON)
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpStartOfReception(
  PduIdType LddRxPduId,
  uint8 LucAPIId, uint8 LucModuleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr, 
  PduLengthType TpSduLength,
  P2VAR(PduLengthType,AUTOMATIC, PDUR_VAR) bufferSizePtr)
#else
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpStartOfReception(
  PduIdType LddRxPduId,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr, 
  PduLengthType TpSduLength,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr)
#endif
#else
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
/* polyspace<MISRA-C:8.3:Not a defect:Justify with annotations> */
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpStartOfReception(
  PduIdType LddRxPduId, uint8 LucAPIId, uint8 LucModuleType, 
  PduLengthType TpSduLength, 
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr)
#else
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpStartOfReception(
  PduIdType LddRxPduId,
  PduLengthType TpSduLength, 
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr)
#endif
#endif /* End of if (PDUR_FOUR_ONE_ONE = PDUR_ONE == STD_ON) */
{

  P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST) LpTpRxIndication;
  #if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
  P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) LpGWTpPdu;
  #endif
  BufReq_ReturnType LddBufReqReturn = BUFREQ_E_NOT_OK;
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 LusGroupMaskValue;
  #endif
  #if (PDUR_TOTAL_COUNT_RX_TP_CALLOUT > 0)
  boolean LblLoRxIndFlag = PDUR_TRUE;
  #endif  
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  LddBufReqReturn = PduR_DETCheckLoTpStartOfReception(LddRxPduId, LucAPIId,
    LucModuleType, bufferSizePtr);

  /* Check whether any development errors are detected */
  if (BUFREQ_OK == LddBufReqReturn)
  #endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the pointer to TpRxIndication structure */
    LpTpRxIndication = &PduR_GaaTpRxIndication[LddRxPduId];
    #if (PDUR_FOUR_ONE_ONE == STD_ON)
    #if (PDUR_TOTAL_COUNT_RX_TP_CALLOUT > 0)
    LddBufReqReturn = BUFREQ_E_NOT_OK;
    /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
    if (PDUR_UNDEFINED != LpTpRxIndication->usRxTpIndCallOutIdx)
    {
      if (NULL_PTR != PduR_GpRxTpIndicationUserCallout)
      {
        P2CONST(PduR_RxIndicationCallOut, AUTOMATIC, PDUR_CONST) LpTpRxIndicationCallOut;
       
        LpTpRxIndicationCallOut = &PduR_GpRxTpIndicationUserCallout[LpTpRxIndication->usRxTpIndCallOutIdx];
        
        if (NULL_PTR != LpTpRxIndicationCallOut->pFuncPduRCallOut)
        {

          LblLoRxIndFlag = LpTpRxIndicationCallOut->pFuncPduRCallOut(LddRxPduId, LpPduInfoPtr);

        }
      }
    }
    if (PDUR_TRUE == LblLoRxIndFlag)
    #endif
    #endif
    {
      #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
      uint8 LucRoutingPathBitStatus = 0;

      LusGroupMaskValue = LpTpRxIndication->usGroupMaskValue;

      if (PDUR_UNDEFINED_ROUTINGPATH_GROUP != LusGroupMaskValue)
      {
        if ((uint8)PDUR_ZERO != (PduR_GaaRoutingPathGroupRam[LusGroupMaskValue >> 3] & ((uint8)1 << (uint8)(LusGroupMaskValue % 8))))
        {
          LucRoutingPathBitStatus = (uint8)PDUR_TRUE;
        }
      }

      /* polyspace<DEFECT:USELESS_IF: Not a defect Justify with annotations:Medium> Condition will be executed based on the configured values */
      /* Check if routing path is enabled */
      if ((PDUR_UNDEFINED_ROUTINGPATH_GROUP == LusGroupMaskValue) || (PDUR_FALSE != LucRoutingPathBitStatus))
      #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
      {
        if ((uint8)PDUR_ZERO == ((LpTpRxIndication->ucTargetIndexOrNoOfRoute) &
                                 PDUR_NONGATEWAY_MASK))
        {
          #if (PDUR_FOUR_ONE_ONE == STD_ON)
  
          /* If Modue are DCM,J1939Dcm,SecOc */
          if(((LpTpRxIndication->ucTargetIndexOrNoOfRoute & (uint8)PDUR_TARGETINDX_MASK) == PDUR_UPPER_DCM)||
            ((LpTpRxIndication->ucTargetIndexOrNoOfRoute & (uint8)PDUR_TARGETINDX_MASK) == PDUR_UPPER_J1939DCM)||
            ((LpTpRxIndication->ucTargetIndexOrNoOfRoute & (uint8)PDUR_TARGETINDX_MASK) == PDUR_UPPER_SECOC)||
            ((LpTpRxIndication->ucTargetIndexOrNoOfRoute & (uint8)PDUR_TARGETINDX_MASK) == PDUR_UPPER_LDCOM)||
            ((LpTpRxIndication->ucTargetIndexOrNoOfRoute & (uint8)PDUR_TARGETINDX_MASK) == PDUR_UPPER_CDDTP))
          {        
            #if (PDUR_TOTAL_COUNT_TP_UP_RX_SORI > PDUR_ZERO)
            if(PduR_GaaTpStartOfReceptionInfo[LpTpRxIndication->
              ucTargetIndexOrNoOfRoute & (uint8)PDUR_TARGETINDX_MASK].pTargetLayer
              != NULL_PTR)
            {
              /* Invoke Upper layer StartOfReception() API */
              LddBufReqReturn =
              PduR_GaaTpStartOfReceptionInfo[LpTpRxIndication->
              ucTargetIndexOrNoOfRoute & (uint8)PDUR_TARGETINDX_MASK].pTargetLayer
              ((LpTpRxIndication->ddUpTargetPduId), LpPduInfoPtr, TpSduLength,
              bufferSizePtr);
            }
            else
            #endif   /*end of if (PDUR_TOTAL_COUNT_TP_UP_RX > PDUR_ZERO)*/
            {
              LddBufReqReturn = BUFREQ_E_NOT_OK;
            }
          }
          else
          {
            #if (PDUR_TOTAL_COUNT_TP_UP_RX_SOR > PDUR_ZERO)
            /* Invoke Upper layer StartOfReception() API */
            /* polyspace-begin MISRA2012:2.1 [Justified:Low] "Condition will be executed based on the configured values" */
            /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
            /* polyspace-begin MISRA-C3:14.3, DEFECT:USELESS_IF [Not a defect Justify with annotations] "Condition will be executed based on the configured values" */
            if(PduR_GaaTpStartOfReception[LpTpRxIndication->ucTargetIndexOrNoOfRoute
               & (uint8)PDUR_TARGETINDX_MASK].pTargetLayer != NULL_PTR)
            {
              LddBufReqReturn =
              PduR_GaaTpStartOfReception[
              LpTpRxIndication->ucTargetIndexOrNoOfRoute&
              (uint8)PDUR_TARGETINDX_MASK].pTargetLayer
              ((LpTpRxIndication->ddUpTargetPduId), TpSduLength,
              bufferSizePtr);
            }
            /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
            /* polyspace-end MISRA2012:2.1 [Justified:Low] "Condition will be executed based on the configured values" */
            /* polyspace-end MISRA-C3:14.3, DEFECT:USELESS_IF [Not a defect Justify with annotations] "Condition will be executed based on the configured values" */
            else
            #endif   /*end of if (PDUR_TOTAL_COUNT_TP_UP_RX > PDUR_ZERO)*/
            {
              LddBufReqReturn = BUFREQ_E_NOT_OK;
            }
            
          } 
          #else
          #if (PDUR_TOTAL_COUNT_TP_UP_RX > PDUR_ZERO)
          /* Invoke Upper layer StartOfReception() API */
          if(PduR_GaaTpStartOfReception[LpTpRxIndication->ucTargetIndexOrNoOfRoute
             & (uint8)PDUR_TARGETINDX_MASK].pTargetLayer != NULL_PTR)
          {
            LddBufReqReturn =
            PduR_GaaTpStartOfReception[LpTpRxIndication->ucTargetIndexOrNoOfRoute
            & (uint8)PDUR_TARGETINDX_MASK].pTargetLayer(
            (LpTpRxIndication->ddUpTargetPduId), TpSduLength,bufferSizePtr);
          }
          else
          #endif   /*end of if (PDUR_TOTAL_COUNT_TP_UP_RX > PDUR_ZERO)*/
          {
            LddBufReqReturn = BUFREQ_E_NOT_OK;
          }
          #endif   /*end of if (PDUR_FOUR_ONE_ONE == STD_ON)*/
          
        } /* End of if ((uint8)PDUR_ZERO ==
        *((LpTpRxIndication->ucTargetIndexOrNoOfRoute) & */
        #if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
        else
        {
          /* Get PduR_GWRxTpPdu structure from PduR_TpRxIndication */
          LpGWTpPdu = LpTpRxIndication->pGWRxTpPdu;
  
          if (TpSduLength <= (PduLengthType)PduR_TP_Buffer_Max_Length)
          {
            /* Check whether Tp Buffer is already allocatted */
            if ((uint8)PDUR_ZERO == *(LpGWTpPdu->pRamArea))
            {
              *(LpGWTpPdu->pRamArea) =
                PduR_BuffUpdateLoTpStartOfReception(TpSduLength, bufferSizePtr);
  
              if ((uint8)PDUR_ZERO != *(LpGWTpPdu->pRamArea))
              {
                if ((PduLengthType)PDUR_ZERO != TpSduLength)
                {
                  /* Set the receive status to PDUR_RX_START */
                  *(LpTpRxIndication->pRamArea) = PDUR_RX_START;
                }
                else
                {
                  /* Set the receive status to PDUR_RECEPTION_START */
                  *(LpTpRxIndication->pRamArea) = PDUR_RECEPTION_START;
                }
                /* Set the BufReqReturn to BUFREQ_OK */
                LddBufReqReturn = BUFREQ_OK;
              } /* End of if ((uint8)PDUR_ZERO != *(LpGWTpPdu->pRamArea)) */
              else
              {
                /* Set the BufReqReturn to BUFREQ_E_BUSY */
                LddBufReqReturn = BUFREQ_E_BUSY;
              }
            } /*if(PDUR_ZERO == (*(LpGWTpPdu->pRamArea)) */
            else
            {
              /* Set the BufReqReturn to BUFREQ_E_BUSY */
              LddBufReqReturn = BUFREQ_E_BUSY;
            }
          } /* End of if (TpSduLength <= PduR_TP_Buffer_Max_Length) */
          else
          {
            /* Set the return value to BUFREQ_E_OVFL */
            LddBufReqReturn = BUFREQ_E_OVFL;
          }
        } /* End of else */
        #endif /* End of if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
      }
      #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
      else
      {
        LddBufReqReturn = BUFREQ_E_NOT_OK;
      }
      #endif
    /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
    }
  }
  /* return with the BufReqReturn */
  return (LddBufReqReturn);
} /* End of PduR_LoTpStartOfReception(PduIdType id, PduLengthType
   * TpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr) */

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /*End of if (PDUR_ZERO_COST_OPERATION == STD_OFF) */
#endif /* End of if (PDUR_TP_RXINDICATION == STD_ON) */

/*******************************************************************************
** Function Name        : PduR_LoTpCopyRxData                                 **
**                                                                            **
** Service ID           : 0x<LoTpModId>4                                      **
**                                                                            **
** Description          : This service is called by the TP for requesting     **
**                        a new buffer (pointer to a PduInfoStructure         **
**                        containing a pointer to a SDU buffer and the buffer **
**                        length) for the TP to fill in the received          **
**                        data.The PDU Router shall translate the             **
**                        CanTpRxPduId into the configured target PDU ID and  **
**                        route this request to the configured target         **
**                        function.This function shall only be provided if    **
**                        the pre-compile time configuration parameter        **
**                        PDUR_CANTP_SUPPORT or PDUR_LINTP_SUPPORT            **
**                        or PDUR_FRTP_SUPPORT is enabled.                    **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PduIdType LddRxPduId, PduInfoType *LpPduInfoPtr,    **
**                        uint8 LucApIId, uint8 LucModuleType,                **
**                        PduLengthType  LpBufferSizePtr                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : BufReq_ReturnType  LenBufReqReturn                  **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_GaaTpRxIndication, PduR_GaaTpCopyRxData        **
**                        PduR_GulGroupMaskValue                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        PduR_DETCheckLoTpCopyRxData()                       **
**                        PduR_LoTpGWCopyRxData()                             **
**                                                                            **
*******************************************************************************/
/* Requirement PDUR512 */
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_RXINDICATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"

#if (PDUR_DEV_ERROR_DETECT == STD_ON)
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpCopyRxData(PduIdType LddRxPduId,
  uint8 LucAPIId, uint8 LucModuleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) LpBufferSizePtr)
#else
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpCopyRxData(PduIdType LddRxPduId,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) LpBufferSizePtr)
#endif
{
  /*Local pointer to generated array of Structure type - PduR_TpRxIndication */
  P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST) LpTpRxIndication;
  PduIdType LddTargetPduId;
  BufReq_ReturnType LenBufReqReturn = BUFREQ_E_NOT_OK;
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 LusGroupMaskValue;
  #endif
  uint8 LucTargetIndex;
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  LenBufReqReturn = PduR_DETCheckLoTpCopyRxData(LddRxPduId, LucModuleType,
    LucAPIId, LpPduInfoPtr, LpBufferSizePtr);

  /* Check whether any development errors are detected */
  if (BUFREQ_OK == LenBufReqReturn)
  #endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    /* Get the group mask value */
    uint8 LucRoutingPathBitStatus = 0;
    #endif 

    if (PDUR_TP_RXINDICATION_MAXPDUID > LddRxPduId)
    {
      /* Get the pointer to TpRxIndication structure */
      LpTpRxIndication = &PduR_GaaTpRxIndication[LddRxPduId];
  
      #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
      LusGroupMaskValue = LpTpRxIndication->usGroupMaskValue;
      /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
        if (PDUR_UNDEFINED_ROUTINGPATH_GROUP != LusGroupMaskValue)
        {
          if ((uint8)PDUR_ZERO != (PduR_GaaRoutingPathGroupRam[LusGroupMaskValue >> 3] & ((uint8)1 << (uint8)(LusGroupMaskValue % 8))))
          {
            LucRoutingPathBitStatus = (uint8)PDUR_TRUE;
          }
        }
  
      /* polyspace<DEFECT:USELESS_IF: Not a defect Justify with annotations:Medium> Condition will be executed based on the configured values */
      /* Check if routing path is enabled */
      if ((PDUR_UNDEFINED_ROUTINGPATH_GROUP == LusGroupMaskValue) || (PDUR_FALSE != LucRoutingPathBitStatus))
      #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
      {
        /* Check if gateway */
        if ((uint8)PDUR_ZERO == (LpTpRxIndication->ucTargetIndexOrNoOfRoute & 
                                                    (uint8)PDUR_NONGATEWAY_MASK))
        {
          /* Get target index */
          LucTargetIndex = LpTpRxIndication->ucTargetIndexOrNoOfRoute;
          /* Get target LddRxPduId */
          LddTargetPduId = LpTpRxIndication->ddUpTargetPduId;
          /* Requirement PDUR428 */
          #if (PDUR_TOTAL_COUNT_TP_UP_RX > PDUR_ZERO)
          /* Invoke Upper Layer CopyRxData() API */
          if(PduR_GaaTpCopyRxData[LucTargetIndex].pTargetLayer != NULL_PTR)
          {
            LenBufReqReturn = PduR_GaaTpCopyRxData[LucTargetIndex].pTargetLayer
                              (LddTargetPduId, LpPduInfoPtr, LpBufferSizePtr);
          }
          else
          #endif		
          {
            LenBufReqReturn = BUFREQ_E_NOT_OK;
          }
        } /* End of if (PDUR_ZERO == */
        #if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
        else
        {
          if((PDUR_RX_START == *(LpTpRxIndication->pRamArea)) ||
            ( PDUR_RX_IN_PROGRESS == *(LpTpRxIndication->pRamArea))||
            (PDUR_RX_TX_COMPLETED == *(LpTpRxIndication->pRamArea)))
          {
            if(PDUR_RX_START == *(LpTpRxIndication->pRamArea))
            {
              (*(LpTpRxIndication->pRamArea)) = PDUR_RX_IN_PROGRESS;
            }
            /* Loop through all the Tp Buffer */
            LenBufReqReturn = PduR_LoTpGWCopyRxData
                                (LddRxPduId, LpPduInfoPtr, LpBufferSizePtr);
          }
        } /* End of else */
        #endif /* #if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
        /* Set the receive status to In progress */
      } /* End of if (((uint32)PDUR_ZERO == LulGroupMaskValue) ||
          ((uint32)PDUR_ZERO != (LulGroupMaskValue & PduR_GulGroupMaskValue))) */
      #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
      else
      {
        LenBufReqReturn = BUFREQ_E_NOT_OK;
      }
      /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
      #endif
    }
  }
  /* return with the BufReqReturn */
  return (LenBufReqReturn);
} /* End of PduR_LoTpCopyRxData(PduIdType LddRxPduId, P2VAR(PduInfoType,
   *AUTOMATIC, PDUR_VAR) LpPduInfoPtr, P2VAR(PduLengthType, AUTOMATIC,
   *PDUR_VAR) LpBufferSizePtr) */

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /*  #if (PDUR_TP_RXINDICATION == STD_ON)  */
#endif  /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF)  */

/*******************************************************************************
** Function Name        : PduR_DETCheckLoTpCopyRxData                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_LoTpCopyRxData function                        **
**                        to check the parameters passed are valid and        **
**                        buffer does not need to be the length of the        **
**                        report to DET in case of invalid values.            **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType LddRxPduId, uint8 LucModuleType,          **
**                        uint8 LucAPIId, PduInfoType LpPduInfoPtr,           **
**                        PduLengthType LpBufferSizePtr                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : BufReq_ReturnType LenBufReqReturn                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_GblInitStatus, PduR_GaaTpRxIndication,         **  
**						  PduR_TP_RxIndication_MaxPduID                       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError                                     **
**                                                                            **
*******************************************************************************/
#if ((PDUR_ZERO_COST_OPERATION == STD_OFF) && (PDUR_TP_RXINDICATION == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_DETCheckLoTpCopyRxData(
  PduIdType LddRxPduId, uint8 LucModuleType, uint8 LucAPIId,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) LpBufferSizePtr)
{
  P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST)LpTpRxIndication;
  BufReq_ReturnType LenBufReqReturn;
  /* Initialize buffer return type to "BUFREQ_OK" */
  LenBufReqReturn = (BufReq_ReturnType)BUFREQ_OK;
  /* Check whether the module is initialised */
  /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  if ((boolean)PDUR_UNINITIALIZED == PduR_GblInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      LucAPIId, PDUR_E_INVALID_REQUEST);
    /* Set the return value to BUFREQ_E_NOT_OK */
    LenBufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
  } /* End of if (PDUR_UNINITIALIZED == PduR_GblInitStatus) */
  else
  {
    /* Get the pointer to TpRxIndication structure */
    LpTpRxIndication = &PduR_GaaTpRxIndication[LddRxPduId];

    if (LddRxPduId >= (PduIdType)PduR_TP_RxIndication_MaxPduID)

    {
      /* Report to DET */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        LucAPIId, PDUR_E_PDU_ID_INVALID);
      /* Set the error flag to TRUE */
      LenBufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
    } /* End of if (LddRxPduId >= PduR_GulTpRxIndiMaxPduId) */
    else
    {
      if (LpTpRxIndication->ucModuleType != LucModuleType)
      {
          /* Report to DET */
          (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
            LucAPIId, PDUR_E_PDU_ID_INVALID);
          /* Set the error flag to TRUE */
          LenBufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
      }  /* End of if (LpTpRxIndication->ucModuleType !=
         *LucModuleType) */
    }
    /* Check If PduInfoPtr is NULL_PTR */
    if (NULL_PTR == LpPduInfoPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        LucAPIId, PDUR_E_NULL_POINTER);
      /* Set the return value to BUFREQ_E_NOT_OK */
      LenBufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
    } /* End of if (NULL_PTR == LpPduInfoPtr) */
    /* Check If PduInfoPtr is NULL_PTR */
    else
    {
      /* polyspace<MISRA-C3:D4.14 :: Not a defect Justify with annotations> No Action Planned, condition used to verify the pointer is NULL or not */
      if(NULL_PTR == LpPduInfoPtr->SduDataPtr)
      {
        /* Report to DET */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          LucAPIId, PDUR_E_NULL_POINTER);
        /* Set the return value to BUFREQ_E_NOT_OK */
        LenBufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
      } /* End of if (NULL_PTR == LpPduInfoPtr->SduDataPtr) */
    } /* End of else */

    /* Check If LpBufferSizePtr is NULL_PTR */
    if (NULL_PTR == LpBufferSizePtr)
    {
      /* Report to DET */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        LucAPIId, PDUR_E_NULL_POINTER);
      /* Set the return value to BUFREQ_E_NOT_OK  */
      LenBufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
    } /* End of if (NULL_PTR == LpBufferSizePtr) */
  }
  /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */  
  return (LenBufReqReturn);
} /* End of PduR_DETCheckLoTpCopyRxData(
   * PduIdType LddRxPduId, uint8 LucModuleType, uint8 LucAPIId,
   * P2VAR(PduInfoType, AUTOMATIC,PDUR_VAR) LpPduInfoPtr,
   * P2VAR(PduLengthType, AUTOMATIC,PDUR_VAR) LpBufferSizePtr)*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
#endif /* #if (PDUR_TP_RXINDICATION == STD_ON) */

/*******************************************************************************
** Function Name        : PduR_LoTpGWCopyRxData                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_LoTpCopyRxData function                        **
**                        in case of multicast gateway.                       **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType LddRxPduId,                               **
**                        PduInfoType LpPduInfoPtr,                           **
**                        PduLengthType LpBufferSizePtr                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : BufReq_ReturnType LenBufReqReturn                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_GaaTpRxIndication,                             **
**                        PduR_GaaTpTransmitService, PduR_GaaTpBuffer         **
**                                                                            **
** Function(s) invoked  : SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA(),      **
**                        SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA()        **
**                                                                            **
*******************************************************************************/
#if(PDUR_TP_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
 FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpGWCopyRxData(
    PduIdType LddRxPduId,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) LpBufferSizePtr)
{
  P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST) LpTpRxIndication;
  P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) LpGWTpPdu;
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) LpTpBuffer;
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) LpDestSduDataPtr;
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) LpSduDataPtr;
  PduLengthType LddSduLength;
  BufReq_ReturnType LenBufReqReturn;
  #if (PDUR_GATEWAY_ONFLY_SUPPORT == STD_ON)
  PduInfoType LddPduInfoPtr;
  Std_ReturnType LddRetVal;
  #endif
  /* Set the BufReqReturn to BUFREQ_E_BUSY */
  LenBufReqReturn = (BufReq_ReturnType)BUFREQ_OK;

  /* Get pGWRxTpPdu to local pointer*/
  LpTpRxIndication = &PduR_GaaTpRxIndication[LddRxPduId];

  /* Get pGWRxTpPdu to local pointer*/
  LpGWTpPdu = LpTpRxIndication->pGWRxTpPdu;
  if((PduLengthType)PDUR_ZERO == LpPduInfoPtr->SduLength)
  {
    LpTpBuffer = &PduR_GaaTpBuffer[*(LpGWTpPdu->pRamArea) - (uint8)PDUR_ONE];
    LpTpBuffer->ddCopiedLength = (PduLengthType)PDUR_ZERO;
   (*(LpTpRxIndication->pRamArea)) = PDUR_RX_START;
    #if (PDUR_GATEWAY_ONFLY_SUPPORT == STD_ON)
    LpTpBuffer->ddOnFlyLength = (PduLengthType)PDUR_ZERO;
    #endif
  }
  else
  {
    LpTpBuffer = &PduR_GaaTpBuffer[*(LpGWTpPdu->pRamArea) - (uint8)PDUR_ONE];
    /* Get the Sdu length */
    LddSduLength = LpPduInfoPtr->SduLength;
    /* Check whether Tp Buffer is free and Buffer length is greater or
     * equal to requested length */
    /* Get the status of Tp Buffer */
    if (((LpTpBuffer->ddReqLength - LpTpBuffer->ddCopiedLength)  >=
                                                                LddSduLength))
    {
      /* Enter into critical area */
      SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA();
      /* Update the Receive buffer length */
      LpDestSduDataPtr = ((LpTpBuffer->pSduPtr) +
                                  (PduR_PtrType)(LpTpBuffer->ddCopiedLength));
      LpSduDataPtr = LpPduInfoPtr->SduDataPtr;
      /* API to copy the Received data for transmitting */

      memcpy((P2VAR(void, AUTOMATIC, PDUR_VAR))(LpDestSduDataPtr),
            (P2CONST(void, AUTOMATIC, PDUR_CONST))(LpSduDataPtr),
            LddSduLength);
      
      LpTpBuffer->ddCopiedLength += LpPduInfoPtr->SduLength;
      SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA();
      #if (PDUR_GATEWAY_ONFLY_SUPPORT == STD_ON)
      if(PDUR_GATEWAY_ONFLY_CONF != LpGWTpPdu->usTpThreshold)
      {
        if (((LpTpBuffer->ddCopiedLength >= LpGWTpPdu->usTpThreshold) &&
            ((PduLengthType)PDUR_ZERO == (LpTpBuffer->ddOnFlyLength)))&&
            (*(LpTpRxIndication->pRamArea) != PDUR_RX_TX_COMPLETED))
        {
          LddPduInfoPtr.SduDataPtr = LpTpBuffer->pSduPtr;
          LddPduInfoPtr.SduLength = LpTpBuffer->ddReqLength;
          #if (PDUR_TOTAL_COUNT_TP_TRANSMIT > PDUR_ZERO)		  
          if(PduR_GaaTpTransmitService [(uint8)LpGWTpPdu->ucTargetIndex &
                    (uint8)PDUR_TARGETINDX_MASK].pTargetLayer != NULL_PTR)
          {
            LddRetVal = PduR_GaaTpTransmitService [(uint8)LpGWTpPdu->ucTargetIndex &
                    (uint8)PDUR_TARGETINDX_MASK].pTargetLayer
                    (LpGWTpPdu->ddTargetPduId,
                    (P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_CONST))
                                                              &LddPduInfoPtr);
          }
          else
          #endif		  
          {
            LddRetVal = (Std_ReturnType)E_NOT_OK;
          }
          LenBufReqReturn = (BufReq_ReturnType)LddRetVal;
          if((BufReq_ReturnType)E_OK == LenBufReqReturn)
          {
            (*(LpTpRxIndication->pRamArea)) = (uint8)PDUR_RX_TX_COMPLETED;
          }
        }
      }
      #endif /* End of if(PDUR_GATEWAY_ONFLY_SUPPORT == STD_ON)*/
      if((LpTpBuffer->ddCopiedLength == LpTpBuffer->ddReqLength)
         && ((uint8)PDUR_RX_TX_COMPLETED != *(LpTpRxIndication->pRamArea)))
      {
        (*(LpTpRxIndication->pRamArea)) = (uint8)PDUR_RX_COMPLETED;
      }
      /* update Remaining Available length */
      *LpBufferSizePtr = (LpTpBuffer->ddReqLength -
                                              LpTpBuffer->ddCopiedLength);
      LenBufReqReturn = (BufReq_ReturnType)BUFREQ_OK;
    } /* End of if (PDUR_TRUE != LblMulticastUpper) */
    else
    {
      /* Set the return value to BUFREQ_E_NOT_OK */
      LenBufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
    }
  } /* End of else */
  return (LenBufReqReturn);
} /* End of PduR_LoTpGWCopyRxData(PduIdType LddRxPduId, P2VAR(PduInfoType,
   *AUTOMATIC, PDUR_VAR) LpPduInfoPtr, P2VAR(PduLengthType, AUTOMATIC,
   *PDUR_VAR) LpBufferSizePtr) */

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /*#if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) &&
        (PDUR_TP_NO_BUFFER_COUNT != PDUR_ZERO) */

/*******************************************************************************
** Function Name        : PduR_LoTpRxIndication                               **
**                                                                            **
** Service ID           : 0x<LoTpModId>5                                      **
**                                                                            **
** Description          : This function is called by the TP modules. The PDU  **
**                        Router shall translate the <Lo>TpRxPduId into the   **
**                        configured target PDU ID and route this indication  **
**                        to the configured target function.This function     **
**                        shall only be provided if the pre-compile time      **
**                        configuration parameter PDUR_CANTP_SUPPORT is       **
**                        or PDUR_LINTP_SUPPORT or PDUR_FRTP_SUPPORT          **
**                        is enabled.                                         **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PduIdType LddRxPduId, uint8 LucAPIId,               **
**                        uint8 LucModuleType, NotifResultType result         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_GaaTpRxIndication,PduR_GaaTpTransmitService    **
**                        , PduR_GaaTpBuffer,PduR_GaaTpReceive                **
**                                                                            **
** Function(s) invoked  : Det_ReportError(), PduR_DETCheckLoTpRxIndication()  **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_RXINDICATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
FUNC(void, PDUR_CODE) PduR_LoTpRxIndication(PduIdType LddRxPduId,
  uint8 LucAPIId, uint8 LucModuleType, NotifResultType Result)
#else
FUNC(void, PDUR_CODE) PduR_LoTpRxIndication(PduIdType LddRxPduId,
  NotifResultType Result)
#endif
{
  P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST) LpTpRxIndication;
  #if(PDUR_TP_GATEWAY_OPERATION == STD_ON)
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) LpTpBuffer;
  P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) LpGWTpPdu;
  PduInfoType LddPduInfoPtr;
  Std_ReturnType LddReturnVal;
  uint8 LucNoOfRoutePdu;
  boolean LblGatewaySetFlag;
  #endif /* End of if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
  uint8 LucTargetIndexOrNoOfRoute;
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  boolean LblDetErrorFlag;
  #endif

  #if(PDUR_TP_GATEWAY_OPERATION == STD_ON)
  LblGatewaySetFlag = PDUR_ZERO;
  #endif
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  LblDetErrorFlag = PduR_DETCheckLoTpRxIndication
                                          (LddRxPduId, LucModuleType, LucAPIId);

  /* Check whether any development errors are detected */
  if ((boolean)PDUR_FALSE == LblDetErrorFlag)
  #endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
  {

    if (PDUR_TP_RXINDICATION_MAXPDUID > LddRxPduId)
    {
      /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
      /* Assign Local Pointer to TP Rx Indication Structure for the source PduId
       **/
      LpTpRxIndication = &PduR_GaaTpRxIndication[LddRxPduId];
  
      LucTargetIndexOrNoOfRoute = LpTpRxIndication->ucTargetIndexOrNoOfRoute;
      #if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
  
      LucNoOfRoutePdu = (uint8)PDUR_ZERO;
      /* Check if singlecast gateway  */
      if ((uint8)PDUR_GATEWAY_MASK ==
        ((LucTargetIndexOrNoOfRoute) & (uint8)PDUR_GATEWAY_MASK))
      {
  
        /* Get the Number of Route for Source PDU */
        LucNoOfRoutePdu = (uint8)PDUR_ONE;
  
      } /* End of if (PDUR_GATEWAY_MASK ==
               (LucTargetIndexOrNoOfRoute & PDUR_GATEWAY_MASK) */
  
      else if (LucTargetIndexOrNoOfRoute >
          ((uint8)PDUR_MULTICAST_MASK + (uint8)PDUR_ONE))
      {
        /* Get the Number of Route for Source PDU during Multicast */
        LucNoOfRoutePdu = LucTargetIndexOrNoOfRoute &
                          (uint8)PDUR_NOOFROUTE_MASK;
  
      } /* End of if (LucTargetIndexOrNoOfRoute >
            (PDUR_MULTICAST_MASK + PDUR_ONE)) */
      else
      #endif
      {
        #if (PDUR_TOTAL_COUNT_TP_UP_RX > PDUR_ZERO)
        if(PduR_GaaTpReceive[LucTargetIndexOrNoOfRoute &
                          (uint8)PDUR_TARGETINDX_MASK].pTargetLayer != NULL_PTR)
        {
          (void)PduR_GaaTpReceive[LucTargetIndexOrNoOfRoute &
                          (uint8)PDUR_TARGETINDX_MASK].pTargetLayer
                         (LpTpRxIndication->ddUpTargetPduId, Result);
        }
        #endif	  
      }
  
      #if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
      if ((uint8)PDUR_ZERO != LucNoOfRoutePdu)
      {
        /* Assign Local Pointer to LoGWRxIndication Structure */
        LpGWTpPdu = LpTpRxIndication->pGWRxTpPdu;
        LpTpBuffer = &PduR_GaaTpBuffer[*(LpGWTpPdu->pRamArea) - PDUR_ONE];
        if (((uint8)PDUR_RX_COMPLETED == *(LpTpRxIndication->pRamArea)) &&
            ((NotifResultType)NTFRSLT_OK == Result))
        {
          (*(LpTpRxIndication->pRamArea)) = (uint8)PDUR_RX_ACKNOWLEDGE;
          LddPduInfoPtr.SduDataPtr = LpTpBuffer->pSduPtr;
          /* Data requested during gateway has been updated in the PduinfoPtr */
          LddPduInfoPtr.SduLength = LpTpBuffer->ddReqLength;
          do
          {
            /* TP multicast to Upper layer */
            /* As per Autosar Bugzilla 52242 */
            /* In case of multicast Gateway , if upper layer aborts the
            reception, it should be atleast gatewayed*/
            if ((uint8)PDUR_ZERO != ((LpGWTpPdu->ucTargetIndex) & 
                                                            PDUR_UPPERLAYER_MASK))
            {
              PduR_UpTpRxIndication(LpGWTpPdu, LpTpBuffer, Result);
            } /* End of if (PDUR_ZERO != (LucTargetIndex &
             *PDUR_UPPERLAYER_MASK)) */
            else  /* Gateway case only */
            {
              #if (PDUR_TOTAL_COUNT_TP_TRANSMIT > PDUR_ZERO)
              /* Invoke Tp transmit function */
              if(PduR_GaaTpTransmitService[((uint8)(LpGWTpPdu->ucTargetIndex)) &
                                            (uint8)PDUR_TARGETINDX_MASK].
                pTargetLayer != NULL_PTR)
              {
                LddReturnVal =
                PduR_GaaTpTransmitService[((uint8)(LpGWTpPdu->ucTargetIndex)) &
                                            (uint8)PDUR_TARGETINDX_MASK].
                pTargetLayer(LpGWTpPdu->ddTargetPduId,
                  (P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_CONST))
                  & LddPduInfoPtr);
              }
              else
              #endif			
              {
                LddReturnVal = (Std_ReturnType)E_NOT_OK;
              }
              if((Std_ReturnType)E_OK == LddReturnVal)
              {
                LpTpBuffer->ucTxConfStatus |= LpGWTpPdu->ucTxCnfrmStsMask;
                if(LucNoOfRoutePdu > (uint8)PDUR_ONE)
                {
                  LpTpBuffer->ddOnFlyLength = (PduLengthType)
                                                           PDUR_MULTICAST_GATEWAY;
                }
                LblGatewaySetFlag = PDUR_TRUE;
              }
              #if (PDUR_DEV_ERROR_DETECT == STD_ON)
              else
              {
                /* Report to DET */
                (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                  LucAPIId, PDUR_E_TP_TX_REQ_REJECTED);
              }
              #endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
              /* End of
               * if ((*LpTpRxIndication->pRamArea == PDUR_RX_COMPLETED) &&
               * ((NotifResultType)NTFRSLT_OK == Result)) */
            }  /* Gateway only */
            --LucNoOfRoutePdu;
            /* MISRA Rule   : 17.4.
             *   Message      : Increment or decrement operation
             *                  performed on the pointer
             *   Reason       : Increment operator used
             *                  to achieve better throughput.
             *   Verification : However, part of the code
             *                  is verified manually and
             *                  it is not having any impact.
             */
            /* Increment the Rx gateway structure index */
            ++LpGWTpPdu;
          }while((uint8)PDUR_ZERO != LucNoOfRoutePdu);
        } /* while (PDUR_ZERO != LucNoOfRoutePdu) */
        if(((boolean)PDUR_FALSE == LblGatewaySetFlag) &&
          ((uint8)PDUR_RX_TX_COMPLETED != *(LpTpRxIndication->pRamArea)))
        {
          (*(LpTpRxIndication->pRamArea)) = PDUR_RX_YETTOSTART;
          LpGWTpPdu = LpTpRxIndication->pGWRxTpPdu;
          LpTpBuffer->ddReqLength = (PduLengthType)PDUR_ZERO;
          /* Release buffer from buffer index */
          (*(LpGWTpPdu->pRamArea)) = (uint8)PDUR_ZERO;
        }
      }
      /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
      #endif /* #if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
    }
  }
} /* End of PduR_LoTpRxIndication(PduIdType LddRxPduId, NotifResultType Result)
   **/

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_TP_RXINDICATION == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

/*******************************************************************************
** Function Name        : PduR_DETCheckLoTpRxIndication                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_LoTpStartOfReception function                  **
**                        to update the TP buffers.                           **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType LddRxPduId, uint8 LucModuleType,          **
**                        uint8 LucAPIId                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean LblDetErrorFlag                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_GblInitStatus, PduR_GaaTpRxIndication          **
**                        ,PduR_GpdbtocPtr, PduR_TP_RxIndication_MaxPduID     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError                                     **
**                                                                            **
*******************************************************************************/
#if ((PDUR_TP_RXINDICATION == STD_ON) && (PDUR_ZERO_COST_OPERATION == STD_OFF))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, PDUR_CODE) PduR_DETCheckLoTpRxIndication(
  PduIdType LddRxPduId, uint8 LucModuleType, uint8 LucAPIId)
{
  P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST)LpTpRxIndication;
  boolean LblDetErrorFlag;
  /* Set the DetErrorFlag to the PDUR_FALSE */
  LblDetErrorFlag = (boolean)PDUR_FALSE;
  /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  /* Check whether the module is initialised */
  if ((boolean)PDUR_UNINITIALIZED == PduR_GblInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      LucAPIId, PDUR_E_INVALID_REQUEST);
    /* Set the error flag to TRUE */
    LblDetErrorFlag = (boolean)PDUR_TRUE;
  } /* End of if (PDUR_UNINITIALIZED == PduR_GblInitStatus) */
  else
  {
    /* Get the pointer to TpRxIndication structure */
    LpTpRxIndication = &PduR_GaaTpRxIndication[LddRxPduId];

    if (LddRxPduId >= (PduIdType)PduR_TP_RxIndication_MaxPduID)
    {
      /* Report to DET */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        LucAPIId, PDUR_E_PDU_ID_INVALID);
      /* Set the error flag to TRUE */
      LblDetErrorFlag = (boolean)PDUR_TRUE;
    } /* End of if (LddRxPduId >= PduR_GulTpRxIndiMaxPduId) */
    else
    {
      if (LpTpRxIndication->ucModuleType != LucModuleType)
      {
        /* Report to DET */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          LucAPIId, PDUR_E_PDU_ID_INVALID);
        /* Set the error flag to TRUE */
        LblDetErrorFlag = (boolean)PDUR_TRUE;
      } /* End of if (PduR_GaaTpRxIndication[LddRxPduId].ucModuleType !=
           *LucModuleType) */
    }
  }
  /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  return (LblDetErrorFlag);
} /* End of PduR_DETCheckLoTpRxIndication(
   * PduIdType LddRxPduId, uint8 LucModuleType, uint8 LucAPIId) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
#endif /* End of if (PDUR_TP_RXINDICATION == STD_ON) */


/*******************************************************************************
** Function Name        : PduR_ChangeParameter                                **
**                                                                            **
** Service ID           : 0x<UpModId>A                                        **
**                                                                            **
** Description          : The PDU Router shall translate the DcmTxPduId       **
**                        into the configured target PDU ID and route this    **
**                        change parameter request to the configured target   **
**                        TP module.This function shall only be provided if   **
**                        the pre-compile time  configuration parameter       **
**                        PDUR_DCM_SUPPORT or PDUR_CDD_SUPPORT is  enabled.   **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant for different PduIds                      **
**                        Non-Reentrant for the same PduId                    **
**                                                                            **
** Input Parameters     : PduIdType LddRxPduId, uint8 LucAPIId                **
**                        TPParameterType PduParameterName, uint16 LusValue   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType LddReturnVal                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_GaaTpRxIndication, PduR_GaaTpChangeparameter   **
**                        PduR_GpdbtocPtr, PduR_Total_No_Of_TP_RxPdu          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        pTargetLayer(), Det_ReportError()                   **
**                                                                            **
*******************************************************************************/
#if(PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_FUN_CHANGEPARAMETER_SUPPORT == STD_ON) &&\
  (PDUR_TP_RXINDICATION == STD_ON))
#define PDUR_START_SEC_CODE
#include "MemMap.h"

#if (PDUR_DEV_ERROR_DETECT == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_ChangeParameter(PduIdType LddRxPduId,
  uint8 LucAPIId, TPParameterType PduParameterName, uint16 LusValue)
#else
FUNC(Std_ReturnType, PDUR_CODE) PduR_ChangeParameter(PduIdType LddRxPduId,
  TPParameterType PduParameterName, uint16 LusValue)
#endif
{
  P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST) LpTpRxIndication;
  Std_ReturnType LddReturnVal;
  PduIdType LddTpRxIndId;
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  boolean LblDetErrorFlag;
  #endif
  LddReturnVal = (Std_ReturnType)E_OK;
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  LblDetErrorFlag = PduR_DETCheckChangeParameter(LddRxPduId,
    LucAPIId, LusValue);

  /* Check whether any development errors are detected */
  if ((boolean)PDUR_FALSE == LblDetErrorFlag)
  #endif /* #if(PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (PDUR_TP_RXINDICATION == STD_ON)
    /* initialize RxId to zero */
    LddTpRxIndId = (PduIdType)PDUR_ZERO;
    /* Get the inital Rx indication structure address into local pointer */

    LpTpRxIndication = &PduR_GaaTpRxIndication[LddRxPduId];

    /* loop through all the destinations to match the PDU ID*/
    do
    {
      /* check for Non-Gateway */
      if ((uint8)PDUR_ZERO == (LpTpRxIndication->ucTargetIndexOrNoOfRoute &
                                                   (uint8)PDUR_NONGATEWAY_MASK))
      {
        #if (PDUR_FUN_CHANGEPARAMETER_SUPPORT == STD_ON)
        #if (PDUR_TOTAL_COUNT_TP_CHG_PRM_ENABLED > PDUR_ZERO)
        /* Invoke Change Parameter Request of corresponding Tp layer */
        if(PduR_GaaTpChangeparameter[LpTpRxIndication->ucSourceIndex].
          pTargetLayer != NULL_PTR)
        {
          LddReturnVal =
          PduR_GaaTpChangeparameter[LpTpRxIndication->ucSourceIndex].
          pTargetLayer(LddTpRxIndId, PduParameterName, LusValue);
        }
        else
        #endif
        {
          LddReturnVal = (Std_ReturnType)E_NOT_OK;
        }
        #endif /* End of if (PDUR_FUN_CHANGEPARAMETER_SUPPORT == STD_ON) */
        /* Assign max no. of pdus to terminate the loop  */
        LddTpRxIndId = (PduIdType)PduR_Total_No_Of_TP_RxPdu;
      } /* End of if (PDUR_ZERO == */
      /* get the next RxTp pdu LddRxPduId */
      LddTpRxIndId++;
      /* MISRA Rule   : 17.4.
       *   Message      : Increment or decrement operation
       *                  performed on the pointer
       *   Reason       : Increment operator used
       *                  to achieve better throughput.
       *   Verification : However, part of the code
       *                  is verified manually and
       *                  it is not having any impact.
       */
      /* Get the next Rx tp pdu */
      LpTpRxIndication++;
    }
    while (LddTpRxIndId < (PduIdType)PduR_Total_No_Of_TP_RxPdu);
    #endif /* #if (PDUR_TP_RXINDICATION == STD_ON) */
  }
  /* return with the LddReturnVal */
  return (LddReturnVal);
} /* End of PduR_ChangeParameter(PduIdType LddRxPduId, TPParameterType
   *PduParameterName, uint16 LusValue) */

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /*End of if((PDUR_FUN_CHANGEPARAMETER_SUPPORT == STD_ON) &&\
  (PDUR_TP_RXINDICATION == STD_ON))*/
#endif

/*******************************************************************************
** Function Name        : PduR_DETCheckChangeParameter                        **
**                                                                            **
** Service ID           : 0x<UpModId>A                                        **
**                                                                            **
** Description          : This function is called by the PduR_LoTpCopyTxData  **
**                        to check the parameters passed are valid and        **
**                        buffer does not need to be the length of the        **
**                        report to DET in case of invalid values.            **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType LddRxPduId, uint16 LusPduParameterValue,  **
**                        uint8 LucAPIId                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean LblDetErrorFlag                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_GblInitStatus                                  **
**                        PduR_TP_RxIndication_MaxPduID                       **
**                                                                            **
** Function(s) invoked  : Det_ReportError()                                   **
**                                                                            **
*******************************************************************************/
#if(PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_FUN_CHANGEPARAMETER_SUPPORT == STD_ON) &&\
  (PDUR_TP_RXINDICATION == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
 FUNC(boolean, PDUR_CODE) PduR_DETCheckChangeParameter(
  PduIdType LddRxPduId, uint8 LucAPIId, uint16 LusPduParameterValue)
{
  boolean LblDetErrorFlag;
  /* Set the error flag to PDUR_FALSE */
  LblDetErrorFlag = (boolean)PDUR_FALSE;

  /* Check whether the module is initialised */
  if ((boolean)PDUR_UNINITIALIZED == PduR_GblInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      LucAPIId, PDUR_E_INVALID_REQUEST);
    /* Set the error flag to TRUE */
    LblDetErrorFlag = (boolean)PDUR_TRUE;
  } /* End of if (PDUR_UNINITIALIZED == PduR_GblInitStatus) */
  else
  {
    if (LddRxPduId >= (PduIdType)PduR_TP_RxIndication_MaxPduID)
    {
      /* Report to DET */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        LucAPIId, PDUR_E_PDU_ID_INVALID);
      /* Set the error flag to TRUE */
      LblDetErrorFlag = (boolean)PDUR_TRUE;
    } /* End of if (LddRxPduId >= PduR_GulTpRxIndiMaxPduId) */

    /* Check new value of the parameter 'CanTp_STMin' is within a range */
    if ((LusPduParameterValue > (uint16)PDUR_STMIN_DIRECT_VALUE_RANGE))
    {
      if((LusPduParameterValue < (uint16)PDUR_STMIN_US_LOW) ||
        (LusPduParameterValue > (uint16)PDUR_STMIN_US_HIGH))
      {
        /* Report to DET */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          LucAPIId, PDUR_E_INVALID_REQUEST);
        /* Set the return flag to TRUE */
        LblDetErrorFlag = (boolean)TRUE;
      }
    } /* End of if (((LusPduParameterValue > PDUR_STMIN_DIRECT_VALUE_RANGE) &&
       **/
    if (LusPduParameterValue > (uint16)PDUR_MAX_BS_VAL)
    {
      /* Report to DET */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        LucAPIId, PDUR_E_INVALID_REQUEST);
      /* Set the return flag to TRUE */
      LblDetErrorFlag = (boolean)TRUE;
    } /* End of if (LusPduParameterValue > PDUR_MAX_BS_VAL) */
  }
 return (LblDetErrorFlag);
} /* End of PduR_DETCheckChangeParameter
   * (PduIdType LddRxPduId, uint8 LucAPIId, uint16 LusPduParameterValue)*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
#endif /* #if ((PDUR_DCM_SUPPORT == STD_ON) && \
        *   (PDUR_FUN_CHANGEPARAMETER_SUPPORT == STD_ON)) */
#endif

/*******************************************************************************
** Function Name        : PduR_CancelReceive                                  **
**                                                                            **
** Service ID           : 0x<UpModId>C                                        **
**                                                                            **
** Description          : The PDU Router shall translate the DcmRxPduId       **
**                        into the configured target PDU ID and route this    **
**                        cancel receive request to the configured target     **
**                        TP module.This function shall only be provided if   **
**                        the pre-compile time  configuration parameter       **
**                        PDUR_DCM_SUPPORT and  PDUR_CANCEL_RECEIVE_SUPPORT   **
**                        is  enabled.                                        **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : PduIdType LddRxPduId, uint8 LucAPIId                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType LddReturnVal                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_GaaTpCancelReceive,                            **
**                        PduR_GaaTpRxIndication, PduR_GpdbtocPtr             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        PduR_DETCheckCancelReceive                          **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_CANCEL_RECEIVE_SUPPORT == STD_ON) &&\
  (PDUR_TP_RXINDICATION == STD_ON))
#define PDUR_START_SEC_CODE
#include "MemMap.h"

#if (PDUR_DEV_ERROR_DETECT == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_CancelReceive(PduIdType LddRxPduId,
  uint8 LucAPIId)
#else
FUNC(Std_ReturnType, PDUR_CODE) PduR_CancelReceive(PduIdType LddRxPduId)
#endif
{
  P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST) LpTpRxIndication;
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 LusGroupMaskValue;
  #endif
  Std_ReturnType LddReturnVal;
  
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  LddReturnVal = PduR_DETCheckCancelReceive(LddRxPduId, LucAPIId);

  /* Check whether any development errors are detected */
  if ((Std_ReturnType)E_OK == LddReturnVal)
  #endif /* #if(PDUR_DEV_ERROR_DETECT == STD_ON) */
  {

    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    /* Get the group mask value */
    uint8 LucRoutingPathBitStatus = 0;
    #endif
    
    LddReturnVal = (Std_ReturnType)E_OK;

    /* Get the pointer to TpRxIndication structure */
    LpTpRxIndication = &PduR_GaaTpRxIndication[LddRxPduId];
    /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    /* Get group mask LusGroupMaskValue */
    LusGroupMaskValue = LpTpRxIndication->usGroupMaskValue;

      if (PDUR_UNDEFINED_ROUTINGPATH_GROUP != LusGroupMaskValue)
      {
        if ((uint8)PDUR_ZERO != (PduR_GaaRoutingPathGroupRam[LusGroupMaskValue >> 3] & ((uint8)1 << (uint8)(LusGroupMaskValue % 8))))
        {
          LucRoutingPathBitStatus = (uint8)PDUR_TRUE;
        }
      }

    /* polyspace<DEFECT:USELESS_IF: Not a defect Justify with annotations:Medium> Condition will be executed based on the configured values */
    /* Check if routing path is enabled */
    if ((PDUR_UNDEFINED_ROUTINGPATH_GROUP == LusGroupMaskValue) || (PDUR_FALSE != LucRoutingPathBitStatus))    
    #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
    {
      /* check for Non-Gateway */
      if ((uint8)PDUR_ZERO == (LpTpRxIndication->ucTargetIndexOrNoOfRoute &
                                                   (uint8)PDUR_NONGATEWAY_MASK))
      {
        /* Requirement PDUR0727 */
        #if (PDUR_TOTAL_COUNT_TP_CANCEL_RECEIVE_ENABLED > PDUR_ZERO)
         PduIdType LddTpRxPduId;
        /* Set the Tp Rx PduId to zero */
         LddTpRxPduId = (PduIdType)PDUR_ZERO;
        /* Invoke Cancel Receive Request of corresponding Tp layer */
        if(PduR_GaaTpCancelReceive
                  [LpTpRxIndication->ucSourceIndex].pTargetLayer != NULL_PTR)
        {
          LddReturnVal = PduR_GaaTpCancelReceive
                  [LpTpRxIndication->ucSourceIndex].pTargetLayer(LddTpRxPduId);
        }
        else
        #endif
        {
          LddReturnVal = (Std_ReturnType)E_NOT_OK;
        }
      }
    }
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    /* Requirement PDUR0726 */
    /* If the routing path for the requested I-PDUs is disabled, then
    PduR_<Up>CancelReceive shall return E_NOT_OK */
    else
    {
      LddReturnVal = (Std_ReturnType)E_NOT_OK;
    }
    #endif
    /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  }
  /* return with the LddReturnVal */
  return (LddReturnVal);
} /* End of PduR_CancelReceive(PduIdType LddRxPduId) */

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /*#if ((PDUR_CANCEL_RECEIVE_SUPPORT == STD_ON) && (PDUR_DCM_SUPPORT ==
        *                                                             STD_ON))*/
#endif/*#if (PDUR_ZERO_COST_OPERATION == STD_OFF)*/

/*******************************************************************************
** Function Name        : PduR_DETCheckCancelReceive                          **
**                                                                            **
** Service ID           : 0x<UpModId>C                                        **
**                                                                            **
** Description          : The PDU Router shall translate the DcmRxPduId       **
**                        into the configured target PDU ID and route this    **
**                        cancel receive request to the configured target     **
**                        TP module.This function shall only be provided if   **
**                        the pre-compile time  configuration parameter       **
**                        PDUR_DCM_SUPPORT and  PDUR_CANCEL_RECEIVE_SUPPORT   **
**                        is  enabled.                                        **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : PduIdType LddRxPduId, uint8 LucAPIId                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType LddReturnVal                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_GblInitStatus, PduR_TP_RxIndication_MaxPduID   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_CANCEL_RECEIVE_SUPPORT == STD_ON) &&\
  (PDUR_TP_RXINDICATION == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"

static FUNC(Std_ReturnType, PDUR_VAR) PduR_DETCheckCancelReceive(
  PduIdType LddRxPduId, uint8 LucAPIId)
{
  Std_ReturnType LddReturnVal;
  LddReturnVal = (Std_ReturnType)E_OK;

  if ((boolean)PDUR_UNINITIALIZED == PduR_GblInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      LucAPIId, PDUR_E_INVALID_REQUEST);
    /* Set the return flag to E_NOT_OK */
    LddReturnVal = (Std_ReturnType)E_NOT_OK;
  } /* End of if (PDUR_UNINITIALIZED == PduR_GblInitStatus) */
  else
  {
    if (LddRxPduId >= (PduIdType)PduR_TP_RxIndication_MaxPduID)
    {
      /* Report to DET */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        LucAPIId, PDUR_E_PDU_ID_INVALID);
      /* Set the return value to E_NOT_OK */
      LddReturnVal = (Std_ReturnType)E_NOT_OK;
    } /* End of if (LddRxPduId >= PduR_GulTpRxIndiMaxPduId) */
                                    /* return with the LddReturnVal */
  }
  return (LddReturnVal);
} /* End Of PduR_DETCheckCancelReceive(PduIdType LddRxPduId, uint8 LucAPIId)*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /*#if (PDUR_DEV_ERROR_DETECT == STD_OFF)*/
#endif /*#if ((PDUR_CANCEL_RECEIVE_SUPPORT == STD_ON) && (PDUR_DCM_SUPPORT ==
          *                                                           STD_ON))*/
#endif /*#if (PDUR_ZERO_COST_OPERATION == STD_OFF)*/

/*******************************************************************************
** Function Name        : PduR_DETCheckLoTpStartOfReception                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_LoTpStartOfReception function                  **
**                        to check the parameters passed are valid and        **
**                        buffer does not need to be the length of the        **
**                        report to DET in case of invalid values.            **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType LddRxPduId, uint8 LucAPIId,               **
**                        uint8 LucModuleType, PduLengthType LpBufferSizePtr  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : BufReq_ReturnType LenBufReqReturn                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_GblInitStatus, PduR_GaaTpRxIndication          **
**                        PduR_TP_RxIndication_MaxPduID                       **
**                                                                            **
** Function(s) invoked  : Det_ReportError()                                   **
*******************************************************************************/
#if ((PDUR_TP_RXINDICATION == STD_ON) && (PDUR_ZERO_COST_OPERATION == STD_OFF))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_DETCheckLoTpStartOfReception(
  PduIdType LddRxPduId, uint8 LucAPIId, uint8 LucModuleType,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) LpBufferSizePtr)
{
  P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST)LpTpRxIndication;
  BufReq_ReturnType LenBufReqReturn;
  /* Initialize buffer return type to "BUFREQ_OK" */
  LenBufReqReturn = (BufReq_ReturnType)BUFREQ_OK;
  /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  /* Check whether the module is Initialized */
  if ((boolean)PDUR_UNINITIALIZED == PduR_GblInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      LucAPIId, PDUR_E_INVALID_REQUEST);
    /* Set the return value to BUFREQ_E_NOT_OK */
    LenBufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
  } /* End of if (PDUR_UNINITIALIZED == PduR_GblInitStatus) */
  else
  {
    /* Get the pointer to TpRxIndication structure */
    LpTpRxIndication = &PduR_GaaTpRxIndication[LddRxPduId];
    if (LddRxPduId >= (PduIdType)PduR_TP_RxIndication_MaxPduID)
    {
      /* Report to DET */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        LucAPIId, PDUR_E_PDU_ID_INVALID);
      /* Set the error flag to TRUE */
      LenBufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
    } /* End of if (LddRxPduId >= PduR_GulTpRxIndiMaxPduId) */
    else
    {
      if (LpTpRxIndication->ucModuleType != LucModuleType)
      {
        /* Report to DET */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          LucAPIId, PDUR_E_PDU_ID_INVALID);
        /* Set the error flag to TRUE */
        LenBufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
      }
    } /* End of if (PduR_GaaTpRxIndication[LddRxPduId].ucModuleType !=
       *LucModuleType) */
    if (NULL_PTR == LpBufferSizePtr)
    {
      /* Report to DET */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        LucAPIId, PDUR_E_NULL_POINTER);
      /* Set the return value to BUFREQ_E_NOT_OK */
      LenBufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
    } /* End of if (NULL_PTR == LpBufferSizePtr) */
  }
  /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  return (LenBufReqReturn);
} /* End of PduR_DETCheckLoTpStartOfReception(
   * PduIdType LddRxPduId, uint8 LucAPIId, uint8 LucModuleType,
   * P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) LpBufferSizePtr) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
#endif /* End of if (PDUR_TP_RXINDICATION == STD_ON) */
/*******************************************************************************
** Function Name        : PduR_BuffUpdateLoTpStartOfReception                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_LoTpStartOfReception function                  **
**                        to update the TP buffers.                           **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduLengthType LddTpSduLength                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PduLengthType LpBufferSizePt                        **
**                                                                            **
** Return parameter     : uint8 LucBuffIndex                                  **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :   PduR_GaaTpBuffer            **
**                                                                            **
** Function(s) invoked  : None                                                **
**                                                                            **
*******************************************************************************/
#if (PDUR_TP_RXINDICATION == STD_ON)
#if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, PDUR_CODE) PduR_BuffUpdateLoTpStartOfReception
(PduLengthType LddTpSduLength,
        P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) LpBufferSizePtr)
{
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) LpTpBuffer;
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) LpTpBufferptr;
  uint16 LusBufferValue;
  uint8 LucTpBufferCount;
  uint8 LucBuffIndex;
  /* Get the total number of TpBufferCount into variable */
  LucBuffIndex = (uint8)PDUR_ZERO;
  LusBufferValue = (uint16)PDUR_MAX_BUFFER_VALUE;
  /* Get the pointer to Tp Buffer */
  LpTpBuffer = &PduR_GaaTpBuffer[PDUR_TP_NO_BUFFER_COUNT];
  /* Get the total buffer count */
  LucTpBufferCount = (uint8)PDUR_TP_NO_BUFFER_COUNT;
  LpTpBufferptr = (P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR))LpTpBuffer;
  #if(PDUR_TP_NO_BUFFER_COUNT != PDUR_ONE)
  /* Loop through all the Tp Buffer */
  do
  {
  #endif
    /* Decrement Tp Buffer pointer */
    LpTpBuffer--;
    /* Check whether Tp Buffer is free and Buffer length is greater
    *   or equal to requested length */
    /* Get the status of Tp Buffer */
    if (((PduLengthType)PDUR_ZERO == LpTpBuffer->ddReqLength) &&
        ((LusBufferValue - LddTpSduLength) >= (LpTpBuffer->ddPduLength
         - LddTpSduLength)))
    {
      #if(PDUR_TP_NO_BUFFER_COUNT != PDUR_ONE)
      /* Allocate the proper buffer among the available */
      LusBufferValue = (uint16)LpTpBuffer->ddPduLength;
      #endif    
      /* Set the local pointer */
      LpTpBufferptr = (P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR))LpTpBuffer;
      /* Set the Tp Buffer Index */
      LucBuffIndex = LucTpBufferCount;

    } /* End of if ((PDUR_ZERO == LpTpBuffer->ucTxConfStatus) && */
  #if(PDUR_TP_NO_BUFFER_COUNT != PDUR_ONE)
  /* Decrement the Tp Buffer Count */
      LucTpBufferCount--;
  } while ((uint8)PDUR_ZERO != LucTpBufferCount);
  #endif

  if((uint8)PDUR_ZERO != LucBuffIndex)
  {
    /* Set the length of buffer requested */
    LpTpBufferptr->ddReqLength = LddTpSduLength;
    /* CopyTxData available length to lower layer */
    *LpBufferSizePtr = LddTpSduLength;
    /* Update the buffer length */
    LpTpBufferptr->ddCopiedLength = (PduLengthType)PDUR_LENGTH_ZERO;
    /* Set the status mask */
    LpTpBufferptr->ucTxConfStatus = (uint8)PDUR_ZERO;
  }
  return (LucBuffIndex);
} /* End of PduR_BuffUpdateLoTpStartOfReception(PduLengthType LddTpSduLength,
   *P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) LpBufferSizePtr) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
#endif /* End of if (PDUR_TP_RXINDICATION == STD_ON) */
/*******************************************************************************
** Function Name        : PduR_UpTpRxIndication                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_LoTpRxIndication function                      **
**                        to call the API of Upper Layers.                    **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : LpGWTpPdu, LpTpBuffer, NotifResultType result       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :PduR_GaaTpStartOfReception  **
**                            , PduR_GaaTpReceive ,PduR_GaaTpCopyRxData       **
**                                                                            **
** Function(s) invoked  : None                                                **
**                                                                            **
*******************************************************************************/
#if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
FUNC(void, PDUR_CODE) PduR_UpTpRxIndication(
  P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) LpGWTpPdu,
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) LpTpBuffer,
  NotifResultType result)
{
  BufReq_ReturnType LenBufReqReturn;
  PduLengthType LddBufferSize;
  PduInfoType LddPduInfoPtr;
  LddPduInfoPtr.SduDataPtr = LpTpBuffer->pSduPtr;
  LddBufferSize = (PduLengthType)PDUR_ZERO;
  /* Data requested during gateway has been updated in the PduinfoPtr */
  LddPduInfoPtr.SduLength = LpTpBuffer->ddReqLength;
  /* Invoke Upper layer Start of Reception */
  #if (PDUR_TOTAL_COUNT_TP_UP_RX > PDUR_ZERO)    
  if(PduR_GaaTpStartOfReception[(uint8)(LpGWTpPdu->ucTargetIndex &
                              PDUR_TARGETINDX_MASK)].pTargetLayer != NULL_PTR)
  {
    LenBufReqReturn =
    PduR_GaaTpStartOfReception[(uint8)(LpGWTpPdu->ucTargetIndex &
                              PDUR_TARGETINDX_MASK)].pTargetLayer
      (LpGWTpPdu->ddTargetPduId, LpTpBuffer->ddReqLength,
        &LddBufferSize);
  }
  else
  #endif
  {
    LenBufReqReturn = BUFREQ_E_NOT_OK;
  }
  /* Invoke Upper layer CopyRxData once StartOfReception returns */
  if(BUFREQ_OK == LenBufReqReturn)
  {
    if(LpTpBuffer->ddReqLength > LddBufferSize)
    {
      result = (NotifResultType)NTFRSLT_E_NO_BUFFER;
      #if (PDUR_TOTAL_COUNT_TP_UP_RX > PDUR_ZERO)    
      if(PduR_GaaTpReceive[((uint8)(LpGWTpPdu->ucTargetIndex))&
                        PDUR_TARGETINDX_MASK].pTargetLayer != NULL_PTR)
      {
        (void)PduR_GaaTpReceive[((uint8)(LpGWTpPdu->ucTargetIndex))&
                        PDUR_TARGETINDX_MASK].pTargetLayer(
        LpGWTpPdu->ddTargetPduId, result);
      }
      #endif
    }
    else
    {
      #if (PDUR_TOTAL_COUNT_TP_UP_RX > PDUR_ZERO)    
      /* Invoke Up_CopyRxdata */
      if(PduR_GaaTpCopyRxData[((uint8)(LpGWTpPdu->ucTargetIndex)) &
                              PDUR_TARGETINDX_MASK].pTargetLayer != NULL_PTR)
      {
        LenBufReqReturn =
        PduR_GaaTpCopyRxData[((uint8)(LpGWTpPdu->ucTargetIndex)) &
                              PDUR_TARGETINDX_MASK].pTargetLayer
        (LpGWTpPdu->ddTargetPduId, &LddPduInfoPtr, &LddBufferSize);
      }
      else
      #endif
      {
        LenBufReqReturn = BUFREQ_E_NOT_OK;
      }
      /*  Invoke Tp receive function  */
      if(BUFREQ_OK == LenBufReqReturn)
      {
        #if (PDUR_TOTAL_COUNT_TP_UP_RX > PDUR_ZERO)    
        if(PduR_GaaTpReceive[((uint8)(LpGWTpPdu->ucTargetIndex)) &
                          PDUR_TARGETINDX_MASK].pTargetLayer != NULL_PTR)
        {
          (void)PduR_GaaTpReceive[((uint8)(LpGWTpPdu->ucTargetIndex)) &
                          PDUR_TARGETINDX_MASK].pTargetLayer(
                        LpGWTpPdu->ddTargetPduId, result);
        }
        #endif
      }
      else
      {
        result = (NotifResultType)NTFRSLT_E_NOT_OK;
        #if (PDUR_TOTAL_COUNT_TP_UP_RX > PDUR_ZERO)    
        if(PduR_GaaTpReceive[((uint8)(LpGWTpPdu->ucTargetIndex)) &
                          PDUR_TARGETINDX_MASK].pTargetLayer != NULL_PTR)
        {
          (void)PduR_GaaTpReceive[((uint8)(LpGWTpPdu->ucTargetIndex)) &
                          PDUR_TARGETINDX_MASK].pTargetLayer(
                      LpGWTpPdu->ddTargetPduId, result);
        }
        #endif
      }
    }
  }
} /* End of PduR_UpTpRxIndication(
  P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) LpGWTpPdu,
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) LpTpBuffer,
  NotifResultType result) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of #if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
