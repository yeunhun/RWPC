/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTOEVER Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: PduR_TxLo.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Provision of the Common functionality of                      **
**              PduR_DETCheckLoTxConfirmation(), PduR_GWLoTxConfirmation()    **
**              PduR_LoTxConfirmation(), PduR_DETCheckLoTriggerTransmit(),    **
**              PduR_LoTriggerTransmit()                                      **
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
** 2.9.0.0   29-Nov-2021   HM Shin     #32705                                 **
** 2.6.0     03-Nov-2020   HM Shin     #24937                                 **
** 2.5.0     28-Feb-2020   HM Shin     #19725                                 **
** 2.4.0     06-Sep-2019   HM Shin     #18909                                 **
** 2.3.0     22-Aug-2019   JS Lim      #18336                                 **
** 2.2.0     01-Feb-2017   Chan Kim    Redmine #6922                          **
** 2.1.4     16-Nov-2016   Chan Kim    Redmine #6681                          **
** 2.1.1     17-Jun-2016   Chan Kim    Redmine #5490, #5632, #5680            **
** 2.1.0     17-Jun-2016   Chan Kim    Redmine #5190                          **
** 2.0.8     10-Jun-2016   Chan Kim    Redmine #5143                          **
** 2.0.4     19-Feb-2016   Chan Kim    Redmine #3429, #3425, #3813            **
** 2.0.3     24-Nov-2015   Chan Kim    Redmine #3545, #4519                   **
** 2.0.2     18-Sep-2015   Chan Kim    Redmine #3178                          **
** 2.0.0     11-Aug-2015   Chan Kim    Redmine #2949                          **
** 1.1.1     18-Jul-2014   Chan Kim    Redmine #1123                          **
** 1.0.7     10-Jun-2013   Chan Kim    Change code for release Library        **
** 1.0.0     29-Apr-2013   Autoever      Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "PduR.h"               /* Header File */
#include "PduR_TxLo.h"          /* PduR Tx Lo Header */
#include "SchM_PduR.h"          /* SchM header */
#include "PduR_Incl.h"          /* Dependent module Header files*/
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define PDUR_TXLO_C_AR_RELEASE_MAJOR_VERSION    4
#define PDUR_TXLO_C_AR_RELEASE_MINOR_VERSION    0
#define PDUR_TXLO_C_AR_RELEASE_REVISION_VERSION 3

/* PDUR software version information */
#define PDUR_TXLO_C_SW_MAJOR_VERSION            2
#define PDUR_TXLO_C_SW_MINOR_VERSION            9
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (PDUR_PCTYPES_AR_RELEASE_MAJOR_VERSION !=\
     PDUR_TXLO_C_AR_RELEASE_MAJOR_VERSION)
#error "PduR_TxLo.c : Mismatch in Specification Major Version"
#endif

#if (PDUR_PCTYPES_AR_RELEASE_MINOR_VERSION !=\
     PDUR_TXLO_C_AR_RELEASE_MINOR_VERSION)
#error "PduR_TxLo.c : Mismatch in Specification Minor Version"
#endif

#if (PDUR_PCTYPES_AR_RELEASE_REVISION_VERSION !=\
     PDUR_TXLO_C_AR_RELEASE_REVISION_VERSION)
#error "PduR_TxLo.c : Mismatch in Specification Revision Version"
#endif

#if (PDUR_PCTYPES_SW_MAJOR_VERSION != PDUR_TXLO_C_SW_MAJOR_VERSION)
#error "PduR_TxLo.c : Mismatch in Software Major Version"
#endif

#if (PDUR_PCTYPES_SW_MINOR_VERSION != PDUR_TXLO_C_SW_MINOR_VERSION)
#error "PduR_TxLo.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_TRIGGER_TRANSMIT_SUPPORT == STD_ON) &&\
  (PDUR_LO_TXCONFIRMATION == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"

static FUNC(Std_ReturnType, PDUR_CODE) PduR_DETCheckLoTriggerTransmit(
  PduIdType LddTxPduId, uint8 LucAPIId, uint8 LucModuleType,
  P2VAR(PduInfoType, AUTOMATIC, PDUR_VAR) LpPduInfoPtr);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
#endif

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_LO_TXCONFIRMATION == STD_ON)
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"

static FUNC(boolean, PDUR_CODE) PduR_DETCheckLoTxConfirmation(
  PduIdType LddTxPduId, uint8 LucAPIId, uint8 LucModuleType);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
#endif

#if ((PDUR_ZERO_COST_OPERATION == STD_OFF) && \
  (PDUR_LO_TXCONFIRMATION == STD_ON))
#if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, PDUR_CODE) PduR_GWLoTxConfirmation(
       P2CONST(PduR_LoTxConf, AUTOMATIC, PDUR_CONST) LpLoTxConfirmation);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
/*******************************************************************************
** Function Name        : PduR_LoTxConfirmation                               **
**                                                                            **
** Service ID           : 0x<LoModId>2                                        **
**                                                                            **
** Description          : This function is called by the interface layer after**
**                        the PDU has been transmitted on the network. The    **
**                        PDU Router shall translate the TxPduId into the     **
**                        configured target PDU ID and route this             **
**                        confirmation to the configured target function.     **
**                        This function shall only be provided if the         **
**                        pre-compile time configuration parameter            **
**                        PDUR_CANIF_SUPPORT or PDUR_LINIF_SUPPORT or         **
**                        PDUR_FRIF_SUPPORT or PDUR_IPDUM_SUPPORT is enabled. **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different PduIds                      **
**                        Non-Reentrant for the same PduId                    **
**                                                                            **
** Input Parameters     : PduIdType LddTxPduId, uint8 LucAPIId,               **
**                        uint8 LucModuleType                                 **
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
**                        PduR_GaaLoTxConfirmation, PduR_GaaIfConfirmation    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        PduR_DETCheckLoTxConfirmation()                     **
**                        SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA(),      **
**                        SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA()        ** 
**                                                                            **
*******************************************************************************/
/* Requirement PDUR365 */
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_LO_TXCONFIRMATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"

#if (PDUR_DEV_ERROR_DETECT == STD_ON)
FUNC(void, PDUR_CODE) PduR_LoTxConfirmation(PduIdType LddTxPduId,
  uint8 LucAPIId, uint8 LucModuleType)
#else
FUNC(void, PDUR_CODE) PduR_LoTxConfirmation(PduIdType LddTxPduId)
#endif
{
  P2CONST(PduR_LoTxConf, AUTOMATIC, PDUR_CONST) LpLoTxConfirmation;

  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  boolean LblDetErrorFlag;
  LblDetErrorFlag = PduR_DETCheckLoTxConfirmation(LddTxPduId, LucAPIId,
    LucModuleType);

  /* Check whether any development errors are detected */
  if ((boolean)PDUR_FALSE == LblDetErrorFlag)
  #endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the pointer to LoTxConfirmation structure */
    LpLoTxConfirmation = &PduR_GaaLoTxConfirmation[LddTxPduId];
    /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
    #if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
    /* Check if Gateway */
    if (PDUR_GATEWAY_MASK ==
        (LpLoTxConfirmation->ucTargetIndex & PDUR_GATEWAY_MASK))
    {
      /* If Buffered Gateway present  */
      #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
			/* polyspace<DEFECT:DEAD_CODE: Not a defect:Low> Condition will be executed based on the configured values */
			/* polyspace<MISRA-C3:2.1,14.3:: Not a defect Justify with annotations> Condition will be executed based on the configured values */
      if (PDUR_INVALID_BUFFER != LpLoTxConfirmation->usTxBufferIndex)
      {
        PduR_GWLoTxConfirmation(LpLoTxConfirmation);
      } /* if Buffered Gateway present  */
      #endif /* #if(PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) */
    } /* Check if Gateway */
    else
    #endif /* End of if (PDUR_IF_GATEWAY_OPERATION == STD_ON) */
    {
      #if (PDUR_IF_NORMAL_OPERATION == STD_ON)
      /* polyspace<DEFECT:USELESS_IF: Not a defect:Medium> Condition will be executed based on the configured values */
      /* polyspace<MISRA-C3:14.3: Not a defect:Medium> Condition will be executed based on the configured values */
      #if (PDUR_LO_TXCONFIRMATION_ALLPATH == STD_OFF)
      if((boolean)PDUR_TRUE == LpLoTxConfirmation->blLoTxConfirmation)
      #endif
      {
        /* Changes as per Autosar Bugzilla 37948 */
        /* In case of a multicast (1:n, n>1), communication If transmission,
        the PDUR shall call the transmit confirmation API of the upper layer
        module as soon as the first transmit confirmation from a If module
        which supports transmit confirmation has been received*/ 
        /* polyspace<DEFECT:DEAD_CODE: Not a defect:Low> Condition will be executed based on the configured values */
        /* polyspace<MISRA-C3:2.1,14.3:: Not a defect Justify with annotations> Condition will be executed based on the configured values */
        #if (PDUR_MULTICAST_TOTXIF_SUPPORT == STD_ON)
        if(NULL_PTR !=(LpLoTxConfirmation->pRamArea))
        {
          if((uint8)PDUR_ZERO != ((*(LpLoTxConfirmation->pRamArea)) &
                                        (LpLoTxConfirmation->ucTxConfirmMask)))
          {
            /* Protection for PduR data buffer */
            #if(PDUR_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
            SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA();
            #endif
            (*(LpLoTxConfirmation->pRamArea)) &=
                        (uint8)(~(uint8)(LpLoTxConfirmation->ucTxConfirmMask));
            /* Exit protection for PduR Data buffer */
            #if(PDUR_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
            SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA();
            #endif
            /* Requirement PDUR627 */
            #if (PDUR_TOTAL_COUNT_IF_CONFIRMATION > PDUR_ZERO)
            /* Invoke Upper layer TxConfirmation function */
            if(PduR_GaaIfConfirmation
              [LpLoTxConfirmation->ucTargetIndex].pTargetLayer != NULL_PTR)
            {
              (void)PduR_GaaIfConfirmation
                              [LpLoTxConfirmation->ucTargetIndex].pTargetLayer
              (LpLoTxConfirmation->ddTargetPduId);
            }
            #endif			
          }
        }
        /* Single cast */
        else
        #endif
        {
          /* Requirement PDUR627 */
          #if (PDUR_TOTAL_COUNT_IF_CONFIRMATION > PDUR_ZERO)
          /* Invoke Upper layer TxConfirmation function */
          if(PduR_GaaIfConfirmation[LpLoTxConfirmation->ucTargetIndex]
            .pTargetLayer 
          != NULL_PTR)
          {
            (void)PduR_GaaIfConfirmation[LpLoTxConfirmation->ucTargetIndex]
              .pTargetLayer(LpLoTxConfirmation->ddTargetPduId);
          }
          #endif		  
        }
      }
      #endif
      /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
    }
  }
} /* End of PduR_LoTxConfirmation(PduIdType LddTxPduId) */

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_LO_TXCONFIRMATION == STD_ON)  */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_ON)  */

/*******************************************************************************
** Function Name        : PduR_DETCheckLoTxConfirmation                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the interface after      **
**                        the PDU has been transmitted on the network. The    **
**                        PDU Router shall translate the LddTxPduId into the  **
**                        configured target PDU ID and route this             **
**                        confirmation to the configured target function.     **
**                        This function shall only be provided if the         **
**                        pre-compile time configuration parameter            **
**                        PDUR_CANIF_SUPPORT or PDUR_LINIF_SUPPORT or         **
**                        PDUR_FRIF_SUPPORT or PDUR_IPDUM_SUPPORT is enabled. **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Reentrant for different PduIds                      **
**                        Non-Reentrant for the same PduId                    **
**                                                                            **
** Input Parameters     : PduIdType LddTxPduId, uint8 LucAPIId,               **
**                        uint8 LucModuleType                                 **
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
**                        PduR_GaaLoTxConfirmation, PduR_GblInitStatus        **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_LO_TXCONFIRMATION == STD_ON)
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"

static FUNC(boolean, PDUR_CODE) PduR_DETCheckLoTxConfirmation(
  PduIdType LddTxPduId, uint8 LucAPIId, uint8 LucModuleType)
{
  P2CONST(PduR_LoTxConf, AUTOMATIC, PDUR_CONST) LpLoTxConfirmation;
  boolean LblDetErrorFlag;
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
    LpLoTxConfirmation = &PduR_GaaLoTxConfirmation[LddTxPduId];

    if (LddTxPduId >= (PduIdType)PduR_Lo_TxConfirmation_MaxPduID)
    {
      /* Report to DET */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        LucAPIId, PDUR_E_PDU_ID_INVALID);
      /* Set the error flag to TRUE */
      LblDetErrorFlag = (boolean)PDUR_TRUE;
    } /* End of if (LddTxPduId >= PduR_GulLoTxConfMaxPduId) */
    else
    {
      if (LpLoTxConfirmation ->ucModuleType != LucModuleType)
      {
        /* Report to DET */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          LucAPIId, PDUR_E_PDU_ID_INVALID);
        /* Set the error flag to TRUE */
        LblDetErrorFlag = (boolean)PDUR_TRUE;
      } /* End of if (PduR_GaaLoTxConfirmation[LddTxPduId].ucModuleType !=
         *LucModuleType) */
    }
  }
  /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  return (LblDetErrorFlag);
} /* End of PduR_DETCheckLoTxConfirmation(
  PduIdType LddTxPduId, uint8 LucAPIId, uint8 LucModuleType)*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON)  */
#endif /* #if (PDUR_LO_TXCONFIRMATION == STD_ON)  */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

/*******************************************************************************
** Function Name        : PduR_GWLoTxConfirmation                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_LoTxConfirmation function in case of gateway.  **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduInfoType *LpPduInfoPtr                           **
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
**                        PduR_GaaIfTransmitService, PduR_GaaTxBuffer         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        SchM_Enter_PduR_FIFO_STATUS_PROTECTION_AREA(),      **
**                        SchM_Exit_PduR_FIFO_STATUS_PROTECTION_AREA(),       ** 
**                        CANIF_TXPDU_GW_STATUS()                             **
*******************************************************************************/
#if ((PDUR_ZERO_COST_OPERATION == STD_OFF) && \
  (PDUR_LO_TXCONFIRMATION == STD_ON))
#if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, PDUR_CODE) PduR_GWLoTxConfirmation(
P2CONST(PduR_LoTxConf, AUTOMATIC, PDUR_CONST) LpLoTxConfirmation)
{
  P2CONST(PduR_TxBuffer, AUTOMATIC, PDUR_CONST) LpTxBuffer;
  P2VAR(PduInfoType, AUTOMATIC, PDUR_VAR) LpPduInfoPtr;
  P2VAR(PduR_FifoBuffer, AUTOMATIC, PDUR_VAR) LpFIFOBuffer;

  #if(PDUR_CANIF_SUPPORT == STD_ON)
  uint8 LucCanIfPduStatus = PDUR_INVALID;

  if (((LpLoTxConfirmation->ucTargetIndex) & PDUR_INDEX_MASK) == 
  PDUR_LOWERLAYER_CANIF)
  {
    /* polyspace +1 MISRA-C3:D4.14,18.1, RTE:OBAI [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
    LucCanIfPduStatus = CANIF_TXPDU_GW_STATUS(LpLoTxConfirmation->ddTargetPduId);
  }
  #if(PDUR_CDD_ROUTER_IF_SUPPORT == STD_ON)
  #ifdef PDUR_LOWERLAYER_CDD_ROUTERIF
  else if (((LpLoTxConfirmation->ucTargetIndex) & PDUR_INDEX_MASK) == PDUR_LOWERLAYER_CDD_ROUTERIF)
  {
    /* polyspace:begin MISRA-C3:D4.14,18.1, RTE:OBAI [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
    if (CDD_ROUTER_TXPDU_TARGET(LpLoTxConfirmation->ddTargetPduId) == CddComIfUpperLayer)
    {
      uint16 LusTargetPduId = CDD_ROUTER_CANIF_TXPDU(LpLoTxConfirmation->ddTargetPduId);
      LucCanIfPduStatus = CANIF_TXPDU_GW_STATUS(LusTargetPduId);
    }
    /* polyspace:end MISRA-C3:D4.14,18.1, RTE:OBAI [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
  }
  else
  {                                                                                 
    /* Do Nothing */
  }
  #endif
  #endif
  #endif
  
  /* Get the pointer to TxBuffer from the LoTxConfirmation structure */
  LpTxBuffer = &PduR_GaaTxBuffer[LpLoTxConfirmation->usTxBufferIndex];

  /* Check if buffertype is FIFO */
  if (LpLoTxConfirmation->ucBufferType == (uint8)PDUR_D_FIFO)
  {
    /* Get the pointer to FIFO Buffer */
    LpFIFOBuffer = LpTxBuffer->pFifoBuffer;

    /* Enter critical area */	  
    #if(PDUR_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Enter_PduR_FIFO_STATUS_PROTECTION_AREA();
    #endif
    /* Check if depth count is not zero */
    if ((uint8)PDUR_ZERO != (LpFIFOBuffer->ucDepth))
    {
      /* Decrement Depth */
      LpFIFOBuffer->ucDepth--;

      /* Increment read count */
      LpFIFOBuffer->ucRead++;

      /* Reset read index if more than the depth of FIFO */
      if (LpFIFOBuffer->ucRead >= LpTxBuffer->ucFIFODepth)
      {
        /* Set read index to zero */
        LpFIFOBuffer->ucRead = (uint8)PDUR_ZERO;
      }
      if (((uint8)PDUR_ZERO != LpFIFOBuffer->ucDepth)
      #if(PDUR_CANIF_SUPPORT == STD_ON)
        && (!((LucCanIfPduStatus == CANIF_GW_STOPPED) || (LucCanIfPduStatus == 
      CANIF_GW_ERRVOL)))
      #endif
        )
      {
        /* Get PduInfoPtr into local pointer */
        LpPduInfoPtr = LpTxBuffer->pPduInfoPtr;
        /* point to corresponding pPduInfoPtr */
				/* polyspace <MISRA-C:17.4:Not a defect:Justify with annotations> Not a defect, Decrement and Increment operator is used to achieve better throughput*/ 
        LpPduInfoPtr = LpPduInfoPtr + (PduR_PtrType)(LpFIFOBuffer->ucRead);

        /* Invoke transmit function */
	/* polyspace-begin RTE:UNR [Not a defect:Low] "No Impact of this rule violation" */
        if(PduR_GaaIfTransmitService[(LpLoTxConfirmation->ucTargetIndex)
                                    & PDUR_INDEX_MASK].pTargetLayer != 
                                    NULL_PTR)
        {
          (void)PduR_GaaIfTransmitService[(LpLoTxConfirmation->ucTargetIndex)
                                    & PDUR_INDEX_MASK].pTargetLayer
            (LpLoTxConfirmation->ddTargetPduId, LpPduInfoPtr);
        }
	/* polyspace-end RTE:UNR [Not a defect:Low] "No Impact of this rule violation" */
      }
    } /* End of if ((LpFIFOBuffer->ucWrite) > PDUR_ZERO) */

	/* Exit critical area */	  
    #if(PDUR_TX_INTERRUPT_BASED_PROCESS == STD_OFF)    
    SchM_Exit_PduR_FIFO_STATUS_PROTECTION_AREA();		
    #endif	
  } /* if(LpIfTxConfirmation->ucBufferConfig >= PDUR_D_FIFO) */
} /* End of PduR_GWLoTxConfirmation(
     P2CONST(PduR_LoTxConf, AUTOMATIC, PDUR_CONST) LpLoTxConfirmation)*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) */
#endif /* #if ((PDUR_ZERO_COST_OPERATION == STD_OFF) &&
       (PDUR_LO_TXCONFIRMATION == STD_ON)) */

/*******************************************************************************
** Function Name        : PduR_LoTriggerTransmit                              **
**                                                                            **
** Service ID           : 0x<LoModId>3                                        **
**                                                                            **
** Description          : This function is called by the Master for           **
**                        sending out a frame. The trigger transmit can       **
**                        be initiated by the Master schedule table itself    **
**                        or a received header. Whether this function is      **
**                        called or not is statically configured for each     **
**                        PDU.The PDU Router shall translate the LddTxPduId   **
**                        into the configuredtarget PDU ID and route this     **
**                        trigger to the configured target function           **
**                        (e.g. AUTOSAR Com).This function shall only be      **
**                        provided if the pre-compile time configuration      **
**                        parameter PDUR_LINIF_SUPPORT or PDUR_FRIF_SUPPORT   **
**                        is enabled.                                         **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant for different PduIds                      **
**                        Non-Reentrant for the same PduId                    **
**                                                                            **
** Input Parameters     : PduIdType LddTxPduId,uint8 LucAPIId,                **
**                        uint8 LucModuleType ,                               **
**                        PduInfoType LpPduInfoPtr                            **
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
**                        PduR_GaaLoTxConfirmation,                           **
**                        PduR_GaaTxBuffer,                                   **
**                        PduR_GaaIfTriggerTransmit, PduR_GaaIfTransmitService**
**                                                                            **
**                        Function(s) invoked    :                            **
**                        PduR_DETCheckLoTriggerTransmit()                    **
**                        Det_ReportError()                                   **
**                        SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA(),      **
**                        SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA(),       ** 
**                        SchM_Enter_PduR_FIFO_STATUS_PROTECTION_AREA(),      **
**                        SchM_Exit_PduR_FIFO_STATUS_PROTECTION_AREA(),       ** 
**                                                                            **
*******************************************************************************/
/* As per Autosar Bugzilla 52600 API name has been changed to
PduR_<Lo>TriggerTransmit from PduR_<Lo>IfTriggerTransmit */
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_TRIGGER_TRANSMIT_SUPPORT == STD_ON) &&\
  (PDUR_LO_TXCONFIRMATION == STD_ON))
#define PDUR_START_SEC_CODE
#include "MemMap.h"

#if (PDUR_DEV_ERROR_DETECT == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_LoTriggerTransmit(PduIdType LddTxPduId,
  uint8 LucAPIId, uint8 LucModuleType,
  P2VAR(PduInfoType, AUTOMATIC, PDUR_VAR) LpPduInfoPtr)
#else
FUNC(Std_ReturnType, PDUR_CODE) PduR_LoTriggerTransmit(PduIdType LddTxPduId,
    P2VAR(PduInfoType, AUTOMATIC, PDUR_VAR) LpPduInfoPtr)
#endif
{
  P2CONST(PduR_LoTxConf, AUTOMATIC, PDUR_CONST) LpIfTriggerTransmit;

  #if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
  #if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) ||\
  (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON))
  P2CONST(PduR_TxBuffer, AUTOMATIC, PDUR_CONST) LpTxBuffer;
  P2VAR(PduInfoType, AUTOMATIC, PDUR_VAR) LpPduInfoUpdatePtr;
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) LpDataBuffer;
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) LpDestSduPtr;
  PduLengthType LddSduLength;
  #endif /* End of if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) ||
          *(PDUR_SB_TX_BUFFER_SUPPORT == STD_ON)) */
  uint8 LucTargetIndex;
  #endif /* End of if (PDUR_IF_GATEWAY_OPERATION == STD_ON) */

  #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
  P2VAR(PduR_FifoBuffer, AUTOMATIC, PDUR_VAR) LpFIFOBuffer;
  #endif

  /* Redmine #1123 CAN to FlexRay gateway : return value problem */
  Std_ReturnType LddReturnVal = (Std_ReturnType)E_OK;

  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  LddReturnVal = PduR_DETCheckLoTriggerTransmit(LddTxPduId, LucAPIId,
    LucModuleType, LpPduInfoPtr);

  /* Check whether any development errors are detected */
  if ((Std_ReturnType)E_OK == LddReturnVal)
  #endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    uint8 LucRoutingPathBitStatus = 0;
    uint16 LusGroupMaskValue;
    #endif 
    /* Get the pointer to LpIfTriggerTransmit from PduR_GaaIfTxConfirmation */
    LpIfTriggerTransmit = &PduR_GaaLoTxConfirmation[LddTxPduId];

    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    /* Get the group mask value */
    LusGroupMaskValue = LpIfTriggerTransmit->usGroupMaskValue;
    /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
    /* polyspace:begin<DEFECT:DEAD_CODE: Not a defect:Low> Condition will be executed based on the configured values */
    /* polyspace:begin<MISRA-C3:14.3,2.1:: Not a defect Justify with annotations> Condition will be executed based on the configured values */
    /* Check if routing path is enabled */

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
      
      #if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
      LucTargetIndex = LpIfTriggerTransmit->ucTargetIndex;
      /* Check whether the Pdu is configured for Gateway operation */
      if (PDUR_GATEWAY_MASK == (LucTargetIndex & PDUR_GATEWAY_MASK))
      {
        /* Check whether buffer has been allocated to target */
        if (PDUR_INVALID_BUFFER != LpIfTriggerTransmit->usTxBufferIndex)
        {
          #if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) ||\
                                          (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON))
          /* Get the pointer to LpTxBuffer from the PduR TxBuffer*/
  
          /* Get the value into local pointer */
          LpTxBuffer = &PduR_GaaTxBuffer[LpIfTriggerTransmit->usTxBufferIndex];
  
          /* Get pPduInfoPtr into local pointer */
          LpPduInfoUpdatePtr = LpTxBuffer->pPduInfoPtr;
  
          #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
          /* Get the pointer to FIFO Buffer */
          LpFIFOBuffer = LpTxBuffer->pFifoBuffer;
  
          /* Check if TT - FIFO*/
          if (LpIfTriggerTransmit->ucBufferType == (uint8)PDUR_TT_FIFO)
          {
            /* point to the LpPduInfoPtr */
            /* polyspace <MISRA-C:17.4:Not a defect:Justify with annotations> Not a defect, Decrement and Increment operator is used to achieve better throughput*/ 
            LpPduInfoUpdatePtr = LpPduInfoUpdatePtr +
                                            (PduR_PtrType)(LpFIFOBuffer->ucRead);
          }
          #endif /* #if(PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) */
          /* Get the pointer to LpDataBuffer from pDataBuffer of PduR_TxBuffer*/
          LpDataBuffer = LpPduInfoUpdatePtr->SduDataPtr;
          /* Get the pointer to LpDataBuffer from pDataBuffer of PduR_TxBuffer*/
					/* polyspace<MISRA-C3:D4.14 : Not a defect: Justify with annotations> Pointer is not a NULL and valid*/	 
          LpDestSduPtr = LpPduInfoPtr->SduDataPtr;
          /* Get the SduLength into Local variable */
          LddSduLength = (PduLengthType)LpIfTriggerTransmit->ddPduLength;
          /* Copy the length to LpPduInfoPtr */
          LpPduInfoPtr->SduLength = LddSduLength;
          /* Disable relevant interrupts */
            SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA();
          /* Copy the data from SduDataPtr to data buffer */
          while ((PduLengthType)PDUR_ZERO != LddSduLength)
          {
            /* copy the data from Sdu Pointer to Data Pointer */
						/* polyspace +1 MISRA-C3:18.1, RTE:NIV,IDP [Not a defect: Justify with annotations] "Pointer is not a NULL and valid" */
            *LpDestSduPtr = *LpDataBuffer;
            /* MISRA Rule     : 17.4.
             *   Message      : Increment or decrement operation
             *                  performed on the pointer
             *   Reason       : Increment operator used
             *                  to achieve better throughput.
             *   Verification : However, part of the code
             *                  is verified manually and
             *                  it is not having any impact.
             */
            /* Increment the LpDataBuffer Pointer */
            LpDataBuffer++;
            /* MISRA Rule     : 17.4.
             *   Message      : Increment or decrement operation
             *                  performed on the pointer
             *   Reason       : Increment operator used
             *                  to achieve better throughput.
             *   Verification : However, part of the code
             *                  is verified manually and
             *                  it is not having any impact.
             */
            /* Increment the Data Pointer */
            LpDestSduPtr++;
            /* Decrement SduLength */
            LddSduLength--;
          }
  
          /* Enable relevant interrupts */
          SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA();
          #endif   /*#if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) || \
                    *                       (PDUR_SB_TX_BUFFER_SUPPORT ==
                    * STD_ON))*/
          #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
          if (LpIfTriggerTransmit->ucBufferType == (uint8)PDUR_TT_FIFO)
          {
            #ifdef AUTOEVER_LOCAL_BUG_FIX
  		      /* Enter critical area */	  
            SchM_Enter_PduR_FIFO_STATUS_PROTECTION_AREA();		
            #endif        
            /* Check if depth count is not zero */
            if ((uint8)PDUR_ZERO != (LpFIFOBuffer->ucDepth))
            {
              /* Decrement Depth */
              LpFIFOBuffer->ucDepth--;
  
              /* Increment read count */
              LpFIFOBuffer->ucRead++;
  
              /* Reset read index if more than the depth of FIFO */
              if (LpFIFOBuffer->ucRead >= LpTxBuffer->ucFIFODepth)
              {
                /* Set read index to zero */
                LpFIFOBuffer->ucRead = (uint8)PDUR_ZERO;
              }
              /* Check if depth count is not zero */
              if ((uint8)PDUR_ZERO != (LpFIFOBuffer->ucDepth))
              {
                #ifndef AUTOEVER_LOCAL_BUG_FIX            
                SchM_Enter_PduR_FIFO_STATUS_PROTECTION_AREA();
                #endif
                /* MISRA Rule   : 17.4.
                 *   Message      : Performing pointer arithmetic
                 *   Reason       : Pointer arithmetic used
                 *                  to achieve better throughput.
                 *   Verification : However, part of the code
                 *                  is verified manually and
                 *                  it is not having any impact.
                 */
                LpPduInfoUpdatePtr = LpTxBuffer->pPduInfoPtr;
  
                /* MISRA Rule   : 17.4.
                 *   Message      : Performing pointer arithmetic
                 *   Reason       : Pointer arithmetic used
                 *                  to achieve better throughput.
                 *   Verification : However, part of the code
                 *                  is verified manually and
                 *                  it is not having any impact.
                 */

				/* polyspace +2 MISRA-C:17.4 [Not a defect:Justify with annotations] "Not a defect, Decrement and Increment operator is used to achieve better throughput"*/ 
                LpPduInfoUpdatePtr = LpPduInfoUpdatePtr 
                + (PduR_PtrType)LpFIFOBuffer->ucRead;
                #ifndef AUTOEVER_LOCAL_BUG_FIX  			  
                SchM_Exit_PduR_FIFO_STATUS_PROTECTION_AREA();
                #endif
                if(PduR_GaaIfTransmitService[LucTargetIndex & PDUR_TARGET_INDEX_MASK].
                                  pTargetLayer != NULL_PTR)
                {
                  LddReturnVal =
                  PduR_GaaIfTransmitService[LucTargetIndex & PDUR_TARGET_INDEX_MASK].
                                 pTargetLayer(LpIfTriggerTransmit->ddTargetPduId,
                 (P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST))LpPduInfoUpdatePtr);
                }
                else
                {
                  LddReturnVal = E_NOT_OK;
                }
                #if (PDUR_DEV_ERROR_DETECT == STD_ON)
                if((Std_ReturnType)E_NOT_OK == LddReturnVal)
                {
                  /* Report to DET */
                  (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                                             LucAPIId, PDUR_E_PDU_INSTANCES_LOST);
                }
                #endif
              }
  
            }
             #ifdef AUTOEVER_LOCAL_BUG_FIX		
        		/* Exit critical area */		
            SchM_Exit_PduR_FIFO_STATUS_PROTECTION_AREA();		  
             #endif		  
          } /* End of if ((LpIfTriggerTransmit->ucBufferType >= PDUR_TT_FIFO) &&*/
          #endif /* End of if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) */
        }
        else
        {
          LddReturnVal = (Std_ReturnType)E_NOT_OK;
        }
      }
      /*
       * Check whether the Pdu is configured for Gateway operation
       * else no gateway
      */
      else
      #endif /* End of if (PDUR_IF_GATEWAY_OPERATION == STD_ON) */
      {
        #if (PDUR_IF_NORMAL_OPERATION == STD_ON)
        #if (PDUR_TOTAL_COUNT_IF_TRIGGER > PDUR_ZERO)
        /* Requirement PDUR430 */
        /* Invoke <Up>_TriggerTransmit */
        if(PduR_GaaIfTriggerTransmit[LpIfTriggerTransmit->ucTargetIndex
                                    & (uint8)PDUR_INDEX_MASK].pTargetLayer != 
                                    NULL_PTR)
        {
          LddReturnVal =
          PduR_GaaIfTriggerTransmit[LpIfTriggerTransmit->ucTargetIndex
                                    & (uint8)PDUR_INDEX_MASK].pTargetLayer
            (LpIfTriggerTransmit->ddTargetPduId, LpPduInfoPtr);
        }
        else
        #endif	  
        {
          LddReturnVal = E_NOT_OK;
        }
        #endif
      }
    }
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    else
    {
      LddReturnVal = (Std_ReturnType)E_NOT_OK;
    }
    #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
    /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
    /* polyspace:end<DEFECT:DEAD_CODE: Not a defect Justify with annotations:Low> Condition will be executed based on the configured values */
    /* polyspace:end<MISRA-C3:14.3,2.1:: Not a defect Justify with annotations> Condition will be executed based on the configured values */   
  } /* Return Std Return Value*/
  return (LddReturnVal);
} /* End of PduR_LoTriggerTransmit(PduIdType LddTxPduId, P2VAR(PduInfoType,
   *AUTOMATIC, PDUR_VAR) LpPduInfoPtr) */

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_LO_TXCONFIRMATION == STD_ON) */
#endif/* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

/*******************************************************************************
** Function Name        : PduR_DETCheckLoTriggerTransmit                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the Master for           **
**                        sending out a frame. The trigger transmit can       **
**                        be initiated by the Master schedule table itself    **
**                        or a received header. Whether this function is      **
**                        called or not is statically configured for each     **
**                        PDU.The PDU Router shall translate the LddTxPduId   **
**                        into the configuredtarget PDU ID and route this     **
**                        trigger to the configured target function           **
**                        (e.g. AUTOSAR Com).This function shall only be      **
**                        provided if the pre-compile time configuration      **
**                        parameter PDUR_LINIF_SUPPORT or PDUR_FRIF_SUPPORT   **
**                        is enabled.                                         **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType LddTxPduId,uint8 LucAPIId,                **
**                        uint8 LucModuleType, PduInfoType LpPduInfoPtr       **
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
**                        PduR_GaaLoTxConfirmation, PduR_GblInitStatus        **
**                        PduR_Lo_TxConfirmation_MaxPduID                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_TRIGGER_TRANSMIT_SUPPORT == STD_ON) &&\
  (PDUR_LO_TXCONFIRMATION == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"

static FUNC(Std_ReturnType, PDUR_CODE) PduR_DETCheckLoTriggerTransmit(
  PduIdType LddTxPduId, uint8 LucAPIId, uint8 LucModuleType,
  P2VAR(PduInfoType, AUTOMATIC, PDUR_VAR) LpPduInfoPtr)
{
  P2CONST(PduR_LoTxConf, AUTOMATIC, PDUR_CONST) LpIfTriggerTransmit;
  Std_ReturnType LddReturnVal;
  LddReturnVal = (Std_ReturnType)E_OK;
  /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  /* Check whether the module is initialised */
  if ((boolean)PDUR_UNINITIALIZED == PduR_GblInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      LucAPIId, PDUR_E_INVALID_REQUEST);
    /* Set the return value to E_NOT_OK */
    LddReturnVal = (Std_ReturnType)E_NOT_OK;
  } /* End of if (PDUR_UNINITIALIZED == PduR_GblInitStatus) */
  else
  {
    /* Get the pointer to LpIfTriggerTransmit from PduR_GaaIfTxConfirmation */
    LpIfTriggerTransmit = &PduR_GaaLoTxConfirmation[LddTxPduId];

    if (LddTxPduId >= (PduIdType)PduR_Lo_TxConfirmation_MaxPduID)
    {
      /* Report to DET */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        LucAPIId, PDUR_E_PDU_ID_INVALID);
      /* Set the error flag to TRUE */
      LddReturnVal = (Std_ReturnType)E_NOT_OK;
    } /* End of if (LddTxPduId >= PduR_Lo_TxConfirmation_MaxPduID) */
    else
    {
      if (LpIfTriggerTransmit->ucModuleType != LucModuleType)
      {
        /* Report to DET */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          LucAPIId, PDUR_E_PDU_ID_INVALID);
        /* Set the error flag to TRUE */
        LddReturnVal = (Std_ReturnType)E_NOT_OK;
      } /* End of if (PduR_GaaLoTxConfirmation[LddTxPduId].ucModuleType !=
         *LucModuleType) */
    }
    /* Check If LpPduInfoPtr is NULL_PTR */
    if (NULL_PTR == LpPduInfoPtr)
      {
        /* Report to DET */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          LucAPIId, PDUR_E_NULL_POINTER);
        /* Set the return value to E_NOT_OK */
        LddReturnVal = (Std_ReturnType)E_NOT_OK;
      } /* End of if (NULL_PTR == LpPduInfoPtr) */
    /* Check If SduDataPtr is NULL_PTR */
    else
    {
      /* polyspace<MISRA-C3:D4.14 :: Not a defect Justify with annotations> No Action Planned, condition used to verify the pointer is NULL or not */
      if(NULL_PTR == LpPduInfoPtr->SduDataPtr)
      {
        /* Report to DET */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          LucAPIId, PDUR_E_NULL_POINTER);
        /* Set the return value to E_NOT_OK */
        LddReturnVal = (Std_ReturnType)E_NOT_OK;
      } /* End of if (NULL_PTR == LpPduInfoPtr->SduDataPtr) */
    }
  }
  /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  return (LddReturnVal);
} /* End of PduR_DETCheckLoTriggerTransmit(
  PduIdType LddTxPduId, uint8 LucAPIId, uint8 LucModuleType,
  P2VAR(PduInfoType, AUTOMATIC, PDUR_VAR) LpPduInfoPtr) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON)  */
#endif /* #if (PDUR_TRIGGER_TRANSMIT_SUPPORT == STD_ON)&&
        * (PDUR_LO_TXCONFIRMATION == STD_ON)  */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_ON) */




/*******************************************************************************
** Function Name        : PduR_IfTxConfirmation                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called when routing path is        **
**                        configured from Dcm to CanIf in PduR. This dummy    **
**                        function is created as for Dcm to CanIf routing path**
**                        to avoid compilation error as there is no           **
**                        Confirmation api from Interface layer to Dcm.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : PduIdType TxPduId                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : None                       **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_LO_TXCONFIRMATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
FUNC(void, PDUR_CODE) PduR_IfTxConfirmation(PduIdType TxPduId)
{
  PDUR_UNUSED(TxPduId);
}

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_LO_TXCONFIRMATION == STD_ON) */
#endif /* End of if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
