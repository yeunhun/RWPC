/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTOEVER Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: PduR_TxTp.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Provision of the common functionality of PduR_LoTpCopyTxData()**
**              PduR_DETCheckLoTpCopyTxData(), PduR_LoTpGWCopyTxData,         **
**              PduR_DETCheckLoTpTxConfirmation(), PduR_LoTpTxConfirmation()  **
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
** 2.6.0     03-Nov-2020   HM Shin     #24937                                 **
** 2.4.0     06-Sep-2019   HM Shin     #18909                                 **
** 2.3.0     22-Aug-2019   JS Lim      #18336                                 **
** 2.2.0     01-Feb-2017   Chan Kim    Redmine #6922                          **
** 2.1.5     30-Nov-2016   Chan Kim    Redmine #6568, #6706, #6771            **
** 2.1.4     16-Nov-2016   Chan Kim    Redmine #6682                          **
** 2.1.1     17-Jun-2016   Chan Kim    Redmine #5490, #5632, #5680            **
** 2.1.0     17-Jun-2016   Chan Kim    Redmine #5190                          **
** 2.0.6     27-May-2016   Chan Kim    Redmine #4960                          **
** 2.0.4     19-Feb-2016   Chan Kim    Redmine #3429, #3425, #3813, #3827     **
** 2.0.3     24-Nov-2015   Chan Kim    Redmine #3545, #4519                   **
** 2.0.0     11-Aug-2015   Chan Kim    Redmine #2949                          **
** 1.1.3     18-Mar-2015   Chan Kim    Redmine #2304                          **
** 1.0.7     10-Jun-2013   Chan Kim    Change code for release Library        **
** 1.0.0     29-Apr-2013   Autoever      Initial Version                        **
*******************************************************************************/


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "PduR.h"               /* Header File */
#include "PduR_TxTp.h"          /* Header file for PduR_TxTp.c */
#include "SchM_PduR.h"          /* Schedular Manager header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define PDUR_TXTP_C_AR_RELEASE_MAJOR_VERSION    4
#define PDUR_TXTP_C_AR_RELEASE_MINOR_VERSION    0
#define PDUR_TXTP_C_AR_RELEASE_REVISION_VERSION 3

/* PDUR software version information */
#define PDUR_TXTP_C_SW_MAJOR_VERSION            2
#define PDUR_TXTP_C_SW_MINOR_VERSION            9
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (PDUR_PCTYPES_AR_RELEASE_MAJOR_VERSION !=\
     PDUR_TXTP_C_AR_RELEASE_MAJOR_VERSION)
#error "PduR_TxTp.c : Mismatch in Specification Major Version"
#endif

#if (PDUR_PCTYPES_AR_RELEASE_MINOR_VERSION !=\
     PDUR_TXTP_C_AR_RELEASE_MINOR_VERSION)
#error "PduR_TxTp.c : Mismatch in Specification Minor Version"
#endif

#if (PDUR_PCTYPES_AR_RELEASE_REVISION_VERSION !=\
     PDUR_TXTP_C_AR_RELEASE_REVISION_VERSION)
#error "PduR_TxTp.c : Mismatch in Specification Revision Version"
#endif

#if (PDUR_PCTYPES_SW_MAJOR_VERSION != PDUR_TXTP_C_SW_MAJOR_VERSION)
#error "PduR_TxTp.c : Mismatch in Software Major Version"
#endif

#if (PDUR_PCTYPES_SW_MINOR_VERSION != PDUR_TXTP_C_SW_MINOR_VERSION)
#error "PduR_TxTp.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_TXCONFIRMATION == STD_ON)
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_DETCheckLoTpCopyTxData(
  PduIdType LddTxPduId, uint8 LucModuleType, uint8 LucAPIId,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) LpAvailableDataPtr);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
#endif

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_TXCONFIRMATION == STD_ON)
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, PDUR_CODE) PduR_DETCheckLoTpTxConfirmation(
  PduIdType LddTxPduId, uint8 LucAPIId, PduIdType LucModuleType);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
#endif

/*******************************************************************************
** Function Name        : PduR_LoTpCopyTxData                                 **
**                                                                            **
** Service ID           : 0x<LoTpModId>7                                      **
**                                                                            **
** Description          : This function is called by the TP for               **
**                        requesting a transmit buffer.The length of the      **
**                        buffer does not need to be the length of the        **
**                        complete N-SDU to be transmitted. It only needs to  **
**                        be as large as required by the caller of that       **
**                        service (Length).Within this function, the PDU      **
**                        Router shall translate the TpTxPduId into the       **
**                        configured target PDU ID and route this request to  **
**                        the configured target function.This function shall  **
**                        only be provided if the pre-compile time            **
**                        configuration parameter PDUR_CANTP_SUPPORT or       **
**                        PDUR_LINTP_SUPPORT or PDUR_FRTP_SUPPORT is enabled. **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PduIdType LddTxPduId, uint8 LucAPIId,               **
**                        uint8 LucModuleType, PduInfoType LpPduInfoPtr,      **
**                        RetryInfoType LpRetry                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PduLengthType LpavailableDataPtr                    **
**                                                                            **
** Return parameter     : BufReq_ReturnType LenBufReqReturn                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_GaaTpCopyTxDataBuf,                            **
**                        PduR_GaaTpCopyTxData, PduR_GulGroupMaskValue        **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        PduR_DETCheckLoTpCopyTxData()                       **
**                                                                            **
*******************************************************************************/
#if(PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_TXCONFIRMATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpCopyTxData(PduIdType LddTxPduId,
  uint8 LucAPIId, uint8 LucModuleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr,
	/* polyspace<MISRA-C3:8.13 : Not a defect : Justify with annotations> Modified by other module function */
  P2VAR(RetryInfoType, AUTOMATIC, PDUR_CONST) LpRetry,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) LpAvailableDataPtr)
#else
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpCopyTxData(PduIdType LddTxPduId,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr,
	/* polyspace<MISRA-C3:8.13 : Not a defect : Justify with annotations> Modified by other module function   */
  P2VAR(RetryInfoType, AUTOMATIC, PDUR_CONST) LpRetry,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) LpAvailableDataPtr)
#endif
{
  P2CONST(PduR_TpCopyTxDataBuf, AUTOMATIC, PDUR_CONST) LpTpCopyTxData;
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 LusGroupMaskValue;
  #endif
  /* Local variable to hold the return value of the function */
  BufReq_ReturnType LenBufReqReturn = BUFREQ_E_NOT_OK;


  /* Check for DET */
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  LenBufReqReturn = PduR_DETCheckLoTpCopyTxData(LddTxPduId, LucModuleType,
    LucAPIId, LpPduInfoPtr, LpAvailableDataPtr);

  /* Check whether any development errors are detected */
  if ((BufReq_ReturnType)BUFREQ_OK == LenBufReqReturn)
  #endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    /* Get the group mask value */
    uint8 LucRoutingPathBitStatus = 0;
    #endif

    if (PDUR_TP_TXCONFIRMATION_MAXPDUID > LddTxPduId)
    {
      
      /* Get the pointer to LpTpCopyTxData from PduR_GaaTpProvideTxBuffer*/
      LpTpCopyTxData = &PduR_GaaTpCopyTxDataBuf[LddTxPduId];
      /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
      #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
      LusGroupMaskValue = LpTpCopyTxData->usGroupMaskValue;
      /* polyspace +4 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
      if (PDUR_UNDEFINED_ROUTINGPATH_GROUP != LusGroupMaskValue)
      {
        if ((uint8)PDUR_ZERO != (PduR_GaaRoutingPathGroupRam[LusGroupMaskValue >> 3] & ((uint8)1 << (uint8)(LusGroupMaskValue % 8))))
        {
          LucRoutingPathBitStatus = (uint8)PDUR_TRUE;
        }
      }
        
      /* Check if routing path is enabled */
      /* polyspace<DEFECT:DEAD_CODE: Not a defect: Low> Condition will be executed based on the configured values */
      /* polyspace:begin<MISRA-C3:14.3,2.1:: Not a defect Justify with annotations> Condition will be executed based on the configured values */
      /* Check if routing path is enabled */
      if ((PDUR_UNDEFINED_ROUTINGPATH_GROUP == LusGroupMaskValue) || (PDUR_FALSE != LucRoutingPathBitStatus))    
      #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
      {
        /* Check if gateway present */
        #if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
        if ((uint8)PDUR_ZERO != (LpTpCopyTxData->ucTargetIndex & PDUR_GATEWAY_MASK))
        {
  
          LenBufReqReturn =
                    PduR_LoTpGWCopyTxData(LpTpCopyTxData, LpPduInfoPtr, LpRetry,
                                                                LpAvailableDataPtr);
        }
        else
        #endif
        {
          #if(PDUR_TP_TRANSMIT == STD_ON)
          #if(PDUR_TOTAL_COUNT_TP_UP_TX > PDUR_ZERO)
          /* Invoke the Dcm_CopyTxData() API and get the return value */        
          if(PduR_GaaTpCopyTxData[LpTpCopyTxData->ucTargetIndex &
                  (uint8)PDUR_TARGETINDX_MASK].pTargetLayer != NULL_PTR)
          {
            LenBufReqReturn =
            PduR_GaaTpCopyTxData[LpTpCopyTxData->ucTargetIndex &
                  (uint8)PDUR_TARGETINDX_MASK].pTargetLayer
              (LpTpCopyTxData->ddUpTargetPduId, LpPduInfoPtr, LpRetry,
              LpAvailableDataPtr);
          }
          else
          #endif		
          {
            LenBufReqReturn = BUFREQ_E_NOT_OK;
          }
          #endif
        }
      }/* End of if (((uint32)PDUR_ZERO == LusGroupMaskValue) ||
          ((uint32)PDUR_ZERO != (LusGroupMaskValue & PduR_GulGroupMaskValue))) */   
      #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
      else
      {
        LenBufReqReturn = BUFREQ_E_NOT_OK;
      }
      #endif
      /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
    }
  } /* if (BUFREQ_OK == LenBufReqReturn) */
  /* polyspace:end<MISRA-C3:14.3,2.1 :: Not a defect Justify with annotations> Condition will be executed based on the configured values */
  /* return the Return value */
  return (LenBufReqReturn);
} /* End of PduR_LoTpCopyTxData(PduIdType LddTxPduId, P2VAR(PduInfoType,
  *AUTOMATIC, PDUR_VAR) LpPduInfoPtr, P2VAR(RetryInfoType, AUTOMATIC,
  *PDUR_VAR) LpRetry, P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR)
  *LpavailableDataPtr) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_TP_TXCONFIRMATION == STD_ON)  */
#endif

/*******************************************************************************
** Function Name        : PduR_DETCheckLoTpCopyTxData                         **
**                                                                            **
** Service ID           : NA                                                  **
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
** Input Parameters     : PduIdType LddTxPduId,uint8 LucModuleType,           **
**                        uint8 LucAPIId,PduInfoType LpPduInfoPtr,            **
**                        PduLengthType LpavailableDataPtr                    **
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
**                        PduR_GblInitStatus, PduR_GaaTpCopyTxDataBuf,        **
**                        PduR_TP_TxConfirmation_MaxPduID                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
**                                                                            **
*******************************************************************************/
#if(PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_TXCONFIRMATION == STD_ON)
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_DETCheckLoTpCopyTxData(
  PduIdType LddTxPduId, uint8 LucModuleType, uint8 LucAPIId,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) LpAvailableDataPtr)
{
  P2CONST(PduR_TpCopyTxDataBuf, AUTOMATIC, PDUR_CONST) LpTpCopyTxData;
  BufReq_ReturnType LenBufReqReturn;
  /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  /* Initialize buffer return type to "BUFREQ_OK" */
  LenBufReqReturn = (BufReq_ReturnType)BUFREQ_OK;
  /* Check whether the module is initialised */
  if ((boolean)PDUR_UNINITIALIZED == PduR_GblInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      LucAPIId, PDUR_E_INVALID_REQUEST);
    /* Set the return value to BUFREQ_E_NOT_OK  */
    LenBufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
  } /* End of if (PDUR_UNINITIALIZED == PduR_GblInitStatus) */
  else
  {
    /* Get the pointer to LpTpCopyTxData from PduR_GaaTpProvideTxBuffer*/
    LpTpCopyTxData = &PduR_GaaTpCopyTxDataBuf[LddTxPduId];

    if (LddTxPduId >= (PduIdType)PduR_TP_TxConfirmation_MaxPduID)
    {
      /* Report to DET */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        LucAPIId, PDUR_E_PDU_ID_INVALID);
      /* Set the error flag to BUFREQ_E_NOT_OK */
      LenBufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
    } /* End of if (LddTxPduId >= PduR_GulTpTxConfMaxPduId) */
    else
    {
      if (LpTpCopyTxData->ucModuleType != LucModuleType)
      {
        /* Report to DET */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          LucAPIId, PDUR_E_PDU_ID_INVALID);
        /* Set the error flag to BUFREQ_E_NOT_OK */
        LenBufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
      } /* End of if (PduR_GaaTpCopyTxDataBuf[LddTxPduId].ucModuleType !=
         *LucModuleType) */
    }

    /* Check If PduInfoPtr is NULL_PTR */
    if (NULL_PTR == LpPduInfoPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        LucAPIId, PDUR_E_NULL_POINTER);
      /* Set the return value to BUFREQ_E_NOT_OK  */
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
        /* Set the return value to BUFREQ_E_NOT_OK  */
        LenBufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
      } /* End of if (NULL_PTR == LpPduInfoPtr->SduDataPtr) */
    }
    /* Check If LpavailableDataPtr is NULL_PTR */
    if (NULL_PTR == LpAvailableDataPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        LucAPIId, PDUR_E_NULL_POINTER);
      /* Set the return value to BUFREQ_E_NOT_OK  */
      LenBufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
    } /* End of if (NULL_PTR == LpavailableDataPtr) */
  }
  /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  return (LenBufReqReturn);
} /* End of PduR_DETCheckLoTpCopyTxData
   *(PduIdType LddTxPduId, uint8 LucModuleType, uint8 LucAPIId,
   *P2VAR(PduInfoType, AUTOMATIC,PDUR_VAR) LpPduInfoPtr,
   *P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) LpAvailableDataPtr)*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
#endif /* #if (PDUR_TP_TXCONFIRMATION == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

/*******************************************************************************
** Function Name        : PduR_LoTpGWCopyTxData                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the TP for               **
**                        requesting a gate buffer in case of gateway.The     **
**                        length of the buffer does not need to be the length **
**                        of the complete N-SDU to be transmitted. It only    **
**                        needs to be as large as required by the caller of   **
**                        that service (Length).Within this function, the PDU **
**                        Router shall translate the TpTxPduId into the       **
**                        configured target PDU ID and route this request to  **
**                        the configured target function.This function shall  **
**                        only be provided if the pre-compile time            **
**                        configuration parameter PDUR_CANTP_SUPPORT or       **
**                        PDUR_LINTP_SUPPORT or PDUR_FRTP_SUPPORT is enabled. **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PduInfoType LpPduInfoPtr,LpTpCopyTxData             **
**                        RetryInfoType LpRetry                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PduLengthType LpavailableDataPtr                    **
**                                                                            **
** Return parameter     : BufReq_ReturnType LenBufReqReturn                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_GaaTpBuffer                                    **
**                                                                            **
** Function(s) invoked  : SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA(),      **
**                        SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA()        **
*******************************************************************************/
#if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
 FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpGWCopyTxData
 (P2CONST(PduR_TpCopyTxDataBuf, AUTOMATIC, PDUR_CONST) LpTpCopyTxData,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_VAR) LpPduInfoPtr,
  P2VAR(RetryInfoType, AUTOMATIC, PDUR_VAR) LpRetry,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) LpAvailableDataPtr)
{
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) LpTpBuffer;
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) LpBufferIndex;
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) LpDestSduDataPtr;
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) LpSduDataPtr;
  PduLengthType LddSduLength;
  BufReq_ReturnType LenBufReqReturn;

  /* Set the return value to BUFREQ_E_NOT_OK */
  LenBufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;

  /* Get Tp Buffer Index to local pointer */
  LpBufferIndex = LpTpCopyTxData->pRamArea;

  /* Is PDU configured for gateway? */
  if ((uint8)PDUR_ZERO != *LpBufferIndex)
  {
    /* Store PduInfoPtr address */
    LpTpBuffer = &PduR_GaaTpBuffer[(*LpBufferIndex) - ((uint8)PDUR_ONE)];
    LpSduDataPtr = LpTpBuffer->pSduPtr;

    LddSduLength = LpPduInfoPtr->SduLength;
    /* TPs which doesn't support the Retransmission, will send retry as 
     NULL_PTR */
    if ((LpRetry == NULL_PTR)|| (LpRetry->TpDataState != TP_DATARETRY))
    {
      /* check whether we have requested length of data for copy */
      /* #2304 : type casting error for TP SF gateway */
      if (((PduLengthType)((LpTpBuffer->ddOnFlyLength) + LddSduLength) <=
          LpTpBuffer->ddCopiedLength))
      {
        /* Set the return value to BUFREQ_OK */
        LenBufReqReturn = (BufReq_ReturnType)BUFREQ_OK;
        SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA();
        LpSduDataPtr = LpTpBuffer->pSduPtr;
        *LpAvailableDataPtr = LpTpBuffer->ddReqLength;
        if((PduLengthType)PDUR_MULTICAST_GATEWAY != LpTpBuffer->ddOnFlyLength)
        {
          /* Update the Transmit buffer length */
          LpSduDataPtr += (PduR_PtrType)(LpTpBuffer->ddOnFlyLength);
          LpTpBuffer->ddOnFlyLength += LddSduLength;
          *LpAvailableDataPtr -= LpTpBuffer->ddOnFlyLength;
        }
        LpDestSduDataPtr = LpPduInfoPtr->SduDataPtr;
        /* Copy the Received data for transmitting */
        while (LddSduLength != (PduLengthType)PDUR_LENGTH_ZERO)
        {
          *(LpDestSduDataPtr) = *(LpSduDataPtr);
          /* MISRA Rule   : 17.4.
           *   Message      : Increment or decrement operation
           *                  performed on pointer
           *   Reason       : Increment operator used
           *                  to achieve better throughput.
           *   Verification : However, part of the code
           *                  is verified manually and
           *                  it is not having any impact.
           */
          LpSduDataPtr++;
          /* MISRA Rule   : 17.4.
           *   Message      : Increment or decrement operation
           *                  performed on pointer
           *   Reason       : Increment operator used
           *                  to achieve better throughput.
           *   Verification : However, part of the code
           *                  is verified manually and
           *                  it is not having any impact.
           */
          LpDestSduDataPtr++;
          LddSduLength--;
        }
        SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA();
      } /* End of if (((LpTpBuffer->ddOnFlyLength) + LddSduLength) <=
      LpTpBuffer->ddCopiedLength) */

    }
    else
    {
      if((LpRetry->TxTpDataCnt) < (LpTpBuffer->ddOnFlyLength))
      {
        LpTpBuffer->ddOnFlyLength -= LpRetry->TxTpDataCnt;
       *LpAvailableDataPtr += LpRetry->TxTpDataCnt;
        LpSduDataPtr = LpSduDataPtr - (PduR_PtrType)LpRetry->TxTpDataCnt;
        LpDestSduDataPtr = LpPduInfoPtr->SduDataPtr;
        LpTpBuffer->ddOnFlyLength += LddSduLength;
        #ifdef AUTOEVER_LOCAL_BUG_FIX
        SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA();
        #endif		  
        while (LddSduLength != (PduLengthType)PDUR_LENGTH_ZERO)
        {
          *(LpDestSduDataPtr) = *(LpSduDataPtr);
          /* MISRA Rule   : 17.4.
          *   Message      : Increment or decrement operation
          *                  performed on pointer
          *   Reason       : Increment operator used
          *                  to achieve better throughput.
          *   Verification : However, part of the code
          *                  is verified manually and
          *                  it is not having any impact.
          */
          LpSduDataPtr++;
          /* MISRA Rule   : 17.4.
          *   Message      : Increment or decrement operation
          *                  performed on pointer
          *   Reason       : Increment operator used
          *                  to achieve better throughput.
          *   Verification : However, part of the code
          *                  is verified manually and
          *                  it is not having any impact.
          */
          LpDestSduDataPtr++;
          LddSduLength--;
        }
        #ifdef AUTOEVER_LOCAL_BUG_FIX
        SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA();
        #endif		  
        /* Set the return value to BUFREQ_OK */
        LenBufReqReturn = (BufReq_ReturnType)BUFREQ_OK;          
      }
      else
      {
        /* Set return value as E_NOT_OK since the TPdatacount */
        LenBufReqReturn = BUFREQ_E_NOT_OK;
      }
      
    }
  } /* if ((uint8)PDUR_ZERO != *LpBufferIndex) */

  return (LenBufReqReturn);
} /* End of PduR_LoTpGWCopyTxData
   *(P2CONST(PduR_TpCopyTxDataBuf, AUTOMATIC, PDUR_CONST) LpTpCopyTxData,
   *P2VAR(PduInfoType, AUTOMATIC, PDUR_VAR) LpPduInfoPtr,
   *P2VAR(RetryInfoType, AUTOMATIC, PDUR_VAR) LpRetry,
  *P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) LpAvailableDataPtr)*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */


/*******************************************************************************
** Function Name        : PduR_LoTpTxConfirmation                             **
**                                                                            **
** Service ID           : 0x<LoTpModId>8                                      **
**                                                                            **
** Description          : This function is called by a transport protocol     **
**                        module after the I-PDU has been transmitted on its  **
**                        network, the result will reveal if the transmission **
**                        was successful or not.                              **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PduIdType LddTxPduId, uint8 LucAPIId,               **
**                        PduIdType LucModuleType, NotifResultType result     **
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
**                        PduR_GaaTpCopyTxDataBuf,                            **
**                        PduR_GaaTpBuffer, PduR_GaaTpConfirmation            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        SchM_Enter_PduR_TP_TX_PROTECTION_AREA() ,           **
**                        SchM_Exit_PduR_TP_TX_PROTECTION_AREA() 			        **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_TXCONFIRMATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"

#if (PDUR_DEV_ERROR_DETECT == STD_ON)
FUNC(void, PDUR_CODE) PduR_LoTpTxConfirmation(PduIdType LddTxPduId,
  uint8 LucAPIId, PduIdType LucModuleType, NotifResultType Result)
#else
FUNC(void, PDUR_CODE) PduR_LoTpTxConfirmation(PduIdType LddTxPduId,
  NotifResultType Result)
#endif
{
  /*  Compiler Warning   :  Argument  'Result' is not used in function
   *  Reason             :  For pre-compile implementation the parameter
   *                        "Result" will not be used.
   *  Verification       :  However, part of the code is verified manually
   *                        and it is not having any impact.
   */
  P2CONST(PduR_TpCopyTxDataBuf, AUTOMATIC, PDUR_CONST)LpTpCopyTxDataBuf;
  #if ((PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON) &&\
      (PDUR_TP_TRANSMIT == STD_ON))
  P2VAR(PduR_MulticastTpInfo, AUTOMATIC, PDUR_VAR)LpMulticastTpInfo;
  #endif
  #if ((PDUR_TP_GATEWAY_OPERATION == STD_ON)&&\
  (PDUR_TP_NO_BUFFER_COUNT != PDUR_ZERO))
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) LpTpBuffer;
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) LpBufferIndex;
  #endif

  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  boolean LblDetErrorFlag;
  LblDetErrorFlag = PduR_DETCheckLoTpTxConfirmation(LddTxPduId,
    LucAPIId, LucModuleType);
  /* polyspace<MISRA-C:14.2 : Low : Justify with annotations> Not a defect */
  PDUR_UNUSED(Result);
  /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  /* Check whether any development errors are detected */
  if ((boolean)PDUR_FALSE == LblDetErrorFlag)
  #endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    if (PDUR_TP_TXCONFIRMATION_MAXPDUID > LddTxPduId)
    {
      /* Get pointer to LpTpCopyTxDataBuf from PduR_GaaTpCopyTxDataBuf */
      LpTpCopyTxDataBuf = &PduR_GaaTpCopyTxDataBuf[LddTxPduId];
  
      #if ((PDUR_TP_GATEWAY_OPERATION == STD_ON) &&\
          (PDUR_TP_NO_BUFFER_COUNT != PDUR_ZERO))
      /* Check whether it's configured for Gateway */
      if ((uint8)PDUR_ZERO !=
                          (LpTpCopyTxDataBuf->ucTargetIndex & PDUR_GATEWAY_MASK))
      {
        /* Get pRamStatus8Bit to local pointer */
        LpBufferIndex = LpTpCopyTxDataBuf->pRamArea;
        /* Check if LpBufferIndex is not defined */
        if ((uint8)PDUR_ZERO != *LpBufferIndex)
        {
          /* Disable relevant interrupts */
          SchM_Enter_PduR_TP_TX_PROTECTION_AREA();
  
          LpTpBuffer = &PduR_GaaTpBuffer[(*LpBufferIndex) - ((uint8)PDUR_ONE)];
  
          /* Release the transmit buffer */
          LpTpBuffer->ucTxConfStatus &=
                              (uint8)(~(LpTpCopyTxDataBuf->ucTxCnfrmStsMask));
          if((uint8)PDUR_ZERO == LpTpBuffer->ucTxConfStatus)
          {
            *LpBufferIndex =  (uint8)PDUR_ZERO;
             LpTpBuffer->ddReqLength = (PduLengthType)PDUR_ZERO;
             LpTpBuffer->ddOnFlyLength = (PduLengthType)PDUR_ZERO;
          }
          /* Enable relevant interrupts */
          SchM_Exit_PduR_TP_TX_PROTECTION_AREA();
        }
      } /* End of if (PDUR_ZERO != (LpTpCopyTxDataBuf->ucTargetIndex &
         *PDUR_GATEWAY_MASK)) */
      else
      #endif /* #if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
      {
        #if (PDUR_TP_TRANSMIT == STD_ON)
        /* Check whether PduConfig is PDUR_TP_GATEWAY */
        #if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON)
        /* Check if confirmation status is non-zero */
        if(((uint8)PDUR_ZERO) != ((LpTpCopyTxDataBuf->ucTargetIndex)
                                                  & ((uint8)PDUR_MULTICAST_MASK)))
        {
          LpMulticastTpInfo = (LpTpCopyTxDataBuf->pMulticastTpInfo);
          /* Disable relevant interrupts */
          SchM_Enter_PduR_TP_TX_PROTECTION_AREA();
  
          /* Check whether Result is other than "BUFREQ_OK" */
          /* Update the Result value */
          /**/
          LpMulticastTpInfo->ddResult &= Result;
          /* Clear the confirmation status */
          LpMulticastTpInfo->ucConfStatus &=
                                (uint8)(~(LpTpCopyTxDataBuf->ucTxCnfrmStsMask));
          /* Enable relevant interrupts */
          SchM_Exit_PduR_TP_TX_PROTECTION_AREA();
          if((uint8)PDUR_ZERO == LpMulticastTpInfo->ucConfStatus)
          {
            #if (PDUR_TOTAL_COUNT_TP_UP_TX > PDUR_ZERO)
            /* Invoke Tp confirmation fucntion */
            if(PduR_GaaTpConfirmation[LpTpCopyTxDataBuf->ucTargetIndex&
                (uint8)PDUR_TARGETINDX_MASK].pTargetLayer != NULL_PTR)
            {
              (void)PduR_GaaTpConfirmation[LpTpCopyTxDataBuf->ucTargetIndex&
                (uint8)PDUR_TARGETINDX_MASK].pTargetLayer
                (LpTpCopyTxDataBuf->ddUpTargetPduId,
                LpMulticastTpInfo->ddResult);
            }
            #endif		  
          }
        } /* End of if (PDUR_ZERO != LpTpCopyTxDataBuf->ucTxCnfrmStsMask) */
        else
        #endif /*  #if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON)  */
        {
          #if (PDUR_TOTAL_COUNT_TP_UP_TX > PDUR_ZERO)
          /* Invoke Tp confirmation function */
          if(PduR_GaaTpConfirmation[(LpTpCopyTxDataBuf->ucTargetIndex) &
              (uint8)PDUR_TARGETINDX_MASK].pTargetLayer != NULL_PTR)
          {
            (void)PduR_GaaTpConfirmation[(LpTpCopyTxDataBuf->ucTargetIndex) &
              (uint8)PDUR_TARGETINDX_MASK].pTargetLayer
              (LpTpCopyTxDataBuf->ddUpTargetPduId, Result);
          }
          #endif		  		
        }
        #endif /* End of if (PDUR_TP_TRANSMIT == STD_ON) */
      }/* End of else */
    } 
  }
  /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
} /* End of PduR_LoTpTxConfirmation(PduIdType LddTxPduId, NotifResultType
   *Result) */

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /*  #if (PDUR_TP_TXCONFIRMATION == STD_ON)  */
#endif /*  #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

/*******************************************************************************
** Function Name        : PduR_DETCheckLoTpTxConfirmation                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by a transport protocol     **
**                        module after the I-PDU has been transmitted on its  **
**                        network, the result will reveal if the transmission **
**                        was successful or not.                              **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PduIdType LddTxPduId, uint8 LucAPIId,               **
**                        PduIdType LucModuleType                             **
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
**                        PduR_GblInitStatus,PduR_GaaTpCopyTxDataBuf,         **
**                        PduR_TP_TxConfirmation_MaxPduID                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_TXCONFIRMATION == STD_ON)
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"

static FUNC(boolean, PDUR_CODE) PduR_DETCheckLoTpTxConfirmation(
  PduIdType LddTxPduId, uint8 LucAPIId, PduIdType LucModuleType)

{
  P2CONST(PduR_TpCopyTxDataBuf, AUTOMATIC, PDUR_CONST) LpTpCopyTxData;
  boolean LblDetErrorFlag;
  /* Set the error flag to PDUR_FALSE */
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
    /* Get the pointer to LpTpCopyTxData from PduR_GaaTpProvideTxBuffer*/
    LpTpCopyTxData = &PduR_GaaTpCopyTxDataBuf[LddTxPduId];

    if (LddTxPduId >= (PduIdType)PduR_TP_TxConfirmation_MaxPduID)
    {
      /* Report to DET */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        LucAPIId, PDUR_E_PDU_ID_INVALID);
      /* Set the error flag to TRUE */
      LblDetErrorFlag = (boolean)PDUR_TRUE;
    } /* End of if (LddTxPduId >= PduR_GulTpTxConfMaxPduId) */
    else
    {
      if (LpTpCopyTxData->ucModuleType != LucModuleType)
      {
        /* Report to DET */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          LucAPIId, PDUR_E_PDU_ID_INVALID);
        /* Set the error flag to TRUE */
        LblDetErrorFlag = (boolean)PDUR_TRUE;
      } /* End of if (PduR_GaaTpCopyTxDataBuf[LddTxPduId].ucModuleType !=
         *LucModuleType) */
    }
  }
  /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  return (LblDetErrorFlag);
} /* End of PduR_DETCheckLoTpTxConfirmation
  *(PduIdType LddTxPduId, uint8 LucAPIId, PduIdType LucModuleType)*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /*  #if (PDUR_DEV_ERROR_DETECT == STD_ON)  */
#endif /*  #if (PDUR_TP_TXCONFIRMATION == STD_ON)  */
#endif /*  #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
