/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanIf_TxConfirm.c                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Transmit Confirmation module of CAN Interface                 **
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
** 2.7.4    21-Apr-2021    Sj.Kim    #28280, #29445                           **
** 2.7.0    07-Oct-2020    Sj.Kim    #25877                                   **
** 2.6.2    15-May-2020    Sj.Kim    #23352, #21882, #23360                   **
** 2.6.0    22-Aug-2019    Js.Lim    #18384                                   **
** 2.5.7    26-Dec-2018    Js.Lim    #15285                                   **
** 2.5.6    10-May-2018    Js.Lim    #12222                                   **
** 2.5.4    11-Oct-2017    C.Kim     #10240                                   **
** 2.5.3    07-Jul-2017    Js.Lim    #9769, #9889                             **
** 2.5.0    06-Dec-2016    Js.Lim    #7077                                    **
** 2.3.1    13-Jun-2015    Kt.Kim    Improvement #2724                        **
** 2.3.0    22-Jun-2013    Kt.Kim    Fix null poiunter access                 **
** 2.2.0    17-Jun-2013    Kt.Kim    Error Fix in Defect List                 **
** 2.1.0    30-May-2013    Kt.Kim    Lib-Build Support                        **
** 1.0.0    28-Mar-2013    Kt.Kim    Initial version                          **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "CanIf_Ram.h"           /* Module RAM header file */
#include "CanIf_PCTypes.h"       /* Pre-compile time header file */
#include "CanIf_Cbk.h"           /* Call-back CanIf header file */
#include "CanIf_TxConfirm.h"     /* Tx Confirmation header */
#include "CanSM_Cbk.h"           /* CAN State Manager call back header file */
#include "SchM_CanIf.h"          /* SchM CanIf Header file */
#if  (STD_ON == CANIF_DEV_ERROR_DETECT)
#include "CanIf_Error.h"         /* Det File Check */
#endif
#include "CanIf_UserInc.h"      /* User included header file */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANIF_TXCONFIRM_C_AR_RELEASE_MAJOR_VERSION    4
#define CANIF_TXCONFIRM_C_AR_RELEASE_MINOR_VERSION    0
#define CANIF_TXCONFIRM_C_AR_RELEASE_REVISION_VERSION 3

/* File version information */
#define CANIF_TXCONFIRM_C_SW_MAJOR_VERSION    3
#define CANIF_TXCONFIRM_C_SW_MINOR_VERSION    0

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANIF_TXCONFIRM_AR_RELEASE_MAJOR_VERSION != \
  CANIF_TXCONFIRM_C_AR_RELEASE_MAJOR_VERSION)
  #error "CANIF_TXCONFIRM.c : Mismatch in Specification Major Version"
#endif
#if (CANIF_TXCONFIRM_AR_RELEASE_MINOR_VERSION != \
  CANIF_TXCONFIRM_C_AR_RELEASE_MINOR_VERSION)
  #error "CANIF_TXCONFIRM.c : Mismatch in Specification Minor Version"
#endif
#if (CANIF_TXCONFIRM_AR_RELEASE_REVISION_VERSION != \
  CANIF_TXCONFIRM_C_AR_RELEASE_REVISION_VERSION)
  #error "CANIF_TXCONFIRM.c : Mismatch in Specification Revision Version"
#endif
#if (CANIF_TXCONFIRM_SW_MAJOR_VERSION != CANIF_TXCONFIRM_C_SW_MAJOR_VERSION)
  #error "CANIF_TXCONFIRM.c : Mismatch in Software Major Version"
#endif
#if (CANIF_TXCONFIRM_SW_MINOR_VERSION != CANIF_TXCONFIRM_C_SW_MINOR_VERSION)
  #error "CANIF_TXCONFIRM.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if ((STD_ON == CANIF_DEV_ERROR_DETECT) && (STD_ON == CANIF_TX_LPDU))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, CANIF_CODE) CanIf_DETCancelTxConfirmation (
                       VAR(PduIdType, CANIF_VAR) CanTxPduId,
                       P2CONST(PduInfoType, AUTOMATIC, CANIF_CONST) PduInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_TxConfirmation                                **
**                                                                            **
** Service ID           : 0x13                                                **
**                                                                            **
** Description          : This service is implemented in the CAN Interface    **
**                        and called by the CAN Driver after the CAN L-PDU    **
**                        has been transmitted on the CAN controller.         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant, Not for same Tx L-PDU                   **
**                                                                            **
** Input Parameters     : CanTxPduId                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_GblCanIfStatus,           **
**                                            CanIf_GaaController             **
**                                            CanIf_GaaTxLpdu,                **
**                                            CanIf_GddTxBuffCon              **
**                        Function(s) invoked:Det_ReportError,                **
**                                            CanIf_QueueTransmit             **
*******************************************************************************/
#if (STD_ON == CANIF_TX_LPDU)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANIF_CODE) CanIf_TxConfirmation(
                                          VAR(PduIdType, CANIF_VAR) CanTxPduId)
{
  P2CONST(CanIf_TxLpdu, AUTOMATIC, CANIF_CONST) LpTxLpdu;
  P2VAR(CanIf_Controller, AUTOMATIC, CANIF_VAR) LpController;
  VAR(uint8, CANIF_VAR) LucVar;

  #if (STD_ON == CANIF_PN_SUPPORT)
  #if (CANIF_ONE < CANIF_NO_OF_CONTROLLER)
  VAR(uint8, CANIF_VAR) LucController;
  #endif
  #endif


  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  VAR(Std_ReturnType, CANIF_VAR) LenStdRetVal;
  /* LenStdRetVal is initialized as E_OK */
  LenStdRetVal = (uint8)E_OK;
  /* Report to DET, if module is not initialized */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_TX_CONFIRMATION_SID, LenStdRetVal);
  /* Report to DET, if TxPduID is out of range */
  CANIF_LPDU_RANGE_ERROR(CANIF_TX_CONFIRMATION_SID, LenStdRetVal);
  /* Check if any development error occurred? */
  if ((uint8)E_OK == LenStdRetVal)
  #endif
  {

    /* Get the pointer to requested Tx L-PDU */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    LpTxLpdu = &CanIf_GaaTxLpduSelect[CanTxPduId];
    #else
    LpTxLpdu = &CanIf_GaaTxLpdu[CanTxPduId];
    #endif
    #if(CANIF_BUSLOAD_DETECTING_SUPPORT == STD_ON)
    #if (CANIF_NO_OF_CONTROLLER > CANIF_ONE)
    /* polyspace +2 RTE:OBAI [Not a defect: Justified] "Pointer is not outside its bounds." */
    /* polyspace +1 RTE:IDP [Not a defect: Justified] "Pointer is not outside its bounds." */
    CanIf_GaaTxMsgCnt[LpTxLpdu->ucControllerId]++;
    #else
    CanIf_GaaTxMsgCnt[CANIF_ZERO]++;
    #endif
    #endif

    #if (CANIF_NO_OF_CONTROLLER > CANIF_ONE)
    /* Get the pointer to controller */
		/* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Genderated array index in range" */	
    LpController = &CanIf_GaaController[LpTxLpdu->ucControllerId];
    #else
    /* Get the pointer to controller */
    LpController = &CanIf_GaaController[CANIF_ZERO];
    #endif
    /* polyspace<RTE: IDP : Not a defect : No Action Planned >
       Its boundary is pre-defined */
    LucVar = (LpController->ucTxStatus & CANIF_TX_ENABLED_MASK);
    /* Check whether TxStatus is active as well as online */
    if ((CANIF_TX_ENABLED == LucVar) || (CANIF_TX_OFFLINE_ACTIVE == LucVar))
    {
      #if (STD_ON == CANIF_PN_SUPPORT)
      #if (CANIF_ONE < CANIF_NO_OF_CONTROLLER)
      /* Get the controller Id */
      LucController = LpTxLpdu->ucControllerId;
      #if (STD_ON == CANIF_TXCONFIRM_POLLING_SUPPORT)
      /* set the Tx status as TX confirmed with PN enabled */
      CanIf_GaaController[LucController].ucTxStatus
                                                 |= CANIF_TX_CONFIRM_PN_ENABLED;
      #else
      /* Disabling the Pn status of the respective controller*/
      CanIf_GaaController[LucController].ucTxStatus |= CANIF_TX_PNENABLED;
      #endif
      #else/* #if (CANIF_ONE < CANIF_NO_OF_CONTROLLER) */
      #if (STD_ON == CANIF_TXCONFIRM_POLLING_SUPPORT)
      /* set the Tx status as TX confirmed with PN enabled */
      CanIf_GaaController[CANIF_ZERO].ucTxStatus |= CANIF_TX_CONFIRM_PN_ENABLED;
      #else
      /* Disabling the Pn status of the respective controller */
      CanIf_GaaController[CANIF_ZERO].ucTxStatus |= CANIF_TX_PNENABLED;
      #endif/* #if (STD_ON == CANIF_TXCONFIRM_POLLING_SUPPORT) */
      #endif/* #if (CANIF_ONE < CANIF_NO_OF_CONTROLLER) */
      #endif/* #if ((STD_ON == CANIF_PN_SUPPORT) */

      /* Get the HTH Type */
			/* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Genderated array index in range" */	
      LucVar = ((CANIF_HTHTYPE_MASK) & (LpTxLpdu->ucHTHTypeOrTXPN));
      /* Check whether HTH type is BasicCAN */
			/* polyspace +1 MISRA-C3:2.1,14.3, DEFECT:USELESS_IF,DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
      if (CANIF_BASIC_CAN == LucVar)
      {
        /* Transmit all the pdus in the queue */
        CanIf_QueueTransmit(LpTxLpdu);
      }
      /* Not to delay transmission of queued pdu
         because of direct transmission on confirmation such as gateway */
      CanIf_TxNotification(LpTxLpdu);
      #if (STD_ON == CANIF_READTXPDU_NOTIFY_STATUS_API)
			/* polyspace +1 MISRA-C3:14.3, DEFECT:USELESS_IF [Not a defect: Justified] "Condition will be executed based on the configured values" */
      if (LpTxLpdu->ucTxCbkUser != CANIF_TX_INVALID_UL_USER)
      {
         /* Set the Status to CANIF_TX_CONFIRMED */
        LpController->ucTxStatus |= CANIF_TX_CONFIRMED;
      }
      #endif/* #if (STD_ON == CANIF_READTXPDU_NOTIFY_STATUS_API) */
    } /* Tx Status should be active - check for Tx_offline_Active */
  } /* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_CancelTxConfirmation                          **
**                                                                            **
** Service ID           : 0x15                                                **
**                                                                            **
** Description          : This service is implemented in the CAN Interface    **
**                        and called by the CAN driver after a previous       **
**                        request for cancellation of a pending L-PDU         **
**                        transmit request was successfully performed.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : PduInfoPtr, CanTxPduId                              **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : The Can Interface must be initialized               **
**                                                                            **
** Remarks              : Global Variable(s):CanIf_GblCanIfStatus,            **
**                                           CanIf_GddNoOfTxLpdu              **
**                                           CanIf_GaaTxLpdu                  **
**                        Function(s)invoked:Det_ReportError,                 **
**                                           CanIf_StoreLpduInQueue,          **
**                                           CanIf_CheckQueueStatus,          **
**                                           CanIf_TxQueueHandling,           **
**                                           SchM_Enter_CanIf_TX_QUEUE_       **
**                                           PROTECTION,                      **
**                                           CanIf_QueueTransmit,             **
**                                           SchM_Exit_CanIf_TX_QUEUE_        **
**                                           PROTECTION                       **
*******************************************************************************/
#if (STD_ON == CANIF_TX_LPDU)
#define CANIF_START_SEC_CODE
#include "MemMap.h"

FUNC(void, CANIF_CODE) CanIf_CancelTxConfirmation (
                   VAR(PduIdType, CANIF_VAR) CanTxPduId,
                   P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr)
{
  /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "The value is generated by Generator." */
  /* polyspace +1 MISRA-C3:2.1,14.3 [Not a defect:Low] "The value is generated by Generator." */
  if(CanIf_ctrldrv_tx_cancellation == STD_ON)
  /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "The value is generated by Generator." */
  {
    #if (STD_OFF == CANIF_AUTRON_AUTOSAR_CANCELLATION_USED)

    #if (STD_ON == CANIF_DEV_ERROR_DETECT)
    /* invoke CanIf_DETCancelTxConfirmation to check the DET errors */
    (void)CanIf_DETCancelTxConfirmation (CanTxPduId, PduInfoPtr);
    #else
    CANIF_UNUSED(CanTxPduId);
    CANIF_UNUSED_PTR(PduInfoPtr);
    #endif

    #else
    P2CONST(CanIf_TxLpdu, AUTOMATIC, CANIF_CONST) LpTxLpdu;
    P2CONST(CanIf_TxBuffer, AUTOMATIC, CANIF_CONST) LpTxBuffer;
    P2VAR(CanIf_TxQueue, AUTOMATIC, CANIF_VAR) LpFirstTxQueue;
    P2VAR(CanIf_Controller, AUTOMATIC, CANIF_VAR) LpController;
    VAR(Can_PduType, CANIF_VAR) LddCanPduInfo;
    VAR(CanIf_TxQueueType, CANIF_VAR) LddTxQueueId;
    VAR(uint8, CANIF_VAR) LucValue;
    VAR(uint16, CANIF_VAR) LddTxQueueIndex;
    VAR(uint8, CANIF_VAR) LucCount;
    P2VAR(CanIf_TxQueue, AUTOMATIC, CANIF_VAR) LpTxQueue;
    
    #if (STD_ON == CANIF_DEV_ERROR_DETECT)
    VAR(Std_ReturnType, CANIF_VAR) LenStdRetVal;
    #endif

    /* Get the pointer to requested Tx L-PDU */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    LpTxLpdu = &CanIf_GaaTxLpduSelect[CanTxPduId];
    #else
    LpTxLpdu = &CanIf_GaaTxLpdu[CanTxPduId];
    #endif
    #if (STD_ON == CANIF_DEV_ERROR_DETECT)
    /* invoke CanIf_DETCancelTxConfirmation to check the DET errors */
    LenStdRetVal = CanIf_DETCancelTxConfirmation (CanTxPduId, PduInfoPtr);
    /* Check if any DET is invoked */
    if ((uint8)E_OK == LenStdRetVal)
    #endif

    {
      #if (CANIF_NO_OF_CONTROLLER > CANIF_ONE)
      /* Get the pointer to the respective controller structure */
      LpController = &CanIf_GaaController[LpTxLpdu->ucControllerId];
      #else
      /* Get the pointer to the first controller structure */
      LpController = &CanIf_GaaController[CANIF_ZERO];
      #endif
      /* Get the Tx status of the controller*/
      LucValue = (LpController->ucTxStatus & CANIF_TX_STATUS_MASK);
      /* Check if Tx status is active and online */
      if (CANIF_TX_ENABLED == LucValue)
      {
        /* Take the TxLpduLinkToQueue into Local Variable */
        LucValue = ((CANIF_HTHTYPE_MASK) & (LpTxLpdu->ucHTHTypeOrTXPN));
        /* Check whether HTH type is BasicCAN or FullCAN */
        if (CANIF_BASIC_CAN == LucValue)
        {
          /* Get the mapping index to pTxPduToQueueMapping array */
          LddTxQueueIndex = CanIf_GddTxBuffCon.pBasicTxPduIndex[CanTxPduId];
          /* Get the Tx Buffer address */
          LpTxBuffer = &(CanIf_GddTxBuffCon.pTxBuffer[LpTxLpdu->ddHthIdorBufferId]);
          /* Disable interrupts to protect Tx Queue */
          SchM_Enter_CanIf_TX_QUEUE_PROTECTION();
          /* Get the Tx L-PDU index to queue */
          LpFirstTxQueue = *(LpTxBuffer->pTxFirstQueue);
          /* Is LpFirstTxQueue is NULL_PTR */
          if (NULL_PTR != LpFirstTxQueue)
          {
            /* Is the same Pdu is already in queue for transmission */
            if (LpFirstTxQueue->ddTxLPduId != CanTxPduId)
            {
              /* is mapping array for respective pduId is available */
              if (CANIF_INVALID_TXQUEUE == CanIf_GddTxBuffCon.pTxPduToQueueMapping
                                                                     [LddTxQueueIndex])
              {
                /* check the status of queue for storing the Pdu */
                LddTxQueueId = CanIf_CheckQueueStatus(LpTxBuffer);
                /* Is the status of queue for the PduId is available */
                if (CANIF_INVALID_TXQUEUE != LddTxQueueId)
                {
                  /* fill the map array with the stored Pdu Id*/
                  CanIf_GddTxBuffCon.pTxPduToQueueMapping[LddTxQueueIndex] = LddTxQueueId;
                  LpTxQueue = &(CanIf_GddTxBuffCon.pTxQueue[LddTxQueueId]);
                  /* Prepare message to transmit L-PDU to CAN Driver */
                  #if (STD_ON == CANIF_SETDYNAMICTXID_API)
                  if (CANIF_INVALID_DYNCANID != LpTxLpdu->ddDynCanIdIndex)
                  {
                    SchM_Enter_CanIf_TX_DYNCANID_PROTECTION();
                    /* Read the CAN ID from the RAM area */
                    LddCanPduInfo.id = CanIf_GddCanId[LpTxLpdu->ddDynCanIdIndex];
                    SchM_Exit_CanIf_TX_DYNCANID_PROTECTION();
                  }
                  else
                  #endif
                  {
                    /* Read the CAN ID from ROM area */
                    LddCanPduInfo.id = (LpTxLpdu->ddCanId);
                  }
                  /* copy the length */
                  LddCanPduInfo.length = (uint8)PduInfoPtr->SduLength;
                  /* copy the data pointer  */
                  LddCanPduInfo.sdu = PduInfoPtr->SduDataPtr;
                  /* copy the CanTxPduId handle id */
                  LddCanPduInfo.swPduHandle = CanTxPduId;
                  /* Store the PDU in the Queue */
                  /* polyspace:begin<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
                  /* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > configured memory access index */
                  /* polyspace:begin<RTE: NIV : Not a defect : No Action Planned > initialized variable */
                  CANIF_STORE_IN_QUEUE(LddTxQueueId);
                  /* polyspace:end<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
                  /* polyspace:end<RTE: IDP : Not a defect : No Action Planned > configured memory access index */
                  /* polyspace:end<RTE: NIV : Not a defect : No Action Planned > initialized variable */
                  /*Transmitting the pdus in queue */
                  (void)CanIf_QueueTransmit(LpTxLpdu);
                  /* Perform the queue handling to prioritize the pdus in
                  queue */
                  CanIf_TxQueueHandling(LpTxBuffer, LddTxQueueId);
                }/* if (CANIF_INVALID_TXQUEUE != LddTxQueueId */
                else
                {
                  (void)CanIf_QueueTransmit(LpTxLpdu);
                }
              }/* if (CANIF_INVALID_TXQUEUE == CanIf_GddTxBuffCon.pTxPduToQueueMapping) */
            }/* if (LpFirstTxQueue->ddTxLPduId != CanTxPduId) */
            else
            {
              (void)CanIf_QueueTransmit(LpTxLpdu);
            }
          }/* if (NULL_PTR != LpFirstTxQueue)*/
          else
          {
            LddTxQueueId = (LpTxBuffer->ddNoOfTxQueue) +
                                                       (LpTxBuffer->ddQueueIndex);
            LpTxQueue = &(CanIf_GddTxBuffCon.pTxQueue[LddTxQueueId]);
            /* Prepare message to transmit L-PDU to CAN Driver */
            #if (STD_ON == CANIF_SETDYNAMICTXID_API)
            if (CANIF_INVALID_DYNCANID != LpTxLpdu->ddDynCanIdIndex)
            {
              SchM_Enter_CanIf_TX_DYNCANID_PROTECTION();
              /* Read the CAN ID from the RAM area */
              LddCanPduInfo.id = CanIf_GddCanId[LpTxLpdu->ddDynCanIdIndex];
              SchM_Exit_CanIf_TX_DYNCANID_PROTECTION();
            }
            else
            #endif
            {
              /* Read the CAN ID from ROM area */
              LddCanPduInfo.id = (LpTxLpdu->ddCanId);
            }
            /* copy the length */
            LddCanPduInfo.length = (uint8)PduInfoPtr->SduLength;
            /* copy the data pointer  */
            LddCanPduInfo.sdu = PduInfoPtr->SduDataPtr;
            /* copy the CanTxPduId handle id */
            LddCanPduInfo.swPduHandle = CanTxPduId;
            /* If LddTxQueueId is valid or not*/
            if (LddTxQueueId < CanIf_GddPrecompOpt.ddNumOfTxQueue)
            {
              /* 2013-06-17 kt.kim Error Fix in Defect List */
              /* fill the map array with the stored Pdu Id*/
              CanIf_GddTxBuffCon.pTxPduToQueueMapping[LddTxQueueIndex] = LddTxQueueId;
              /* Store the PDU in the Queue */
              /* polyspace:begin<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
              /* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > configured memory access index */
              /* polyspace:begin<RTE: NIV : Not a defect : No Action Planned > initialized variable */
              CANIF_STORE_IN_QUEUE(LddTxQueueId);
              /* polyspace:end<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
              /* polyspace:end<RTE: IDP : Not a defect : No Action Planned > configured memory access index */
              /* polyspace:end<RTE: NIV : Not a defect : No Action Planned > initialized variable */
              /* Perform the queue handling to prioritize the pdus in queue */
              CanIf_TxQueueHandling(LpTxBuffer, LddTxQueueId);
            }
          }
          /* Disable relevant interrupts */
          SchM_Exit_CanIf_TX_QUEUE_PROTECTION();
        } /* if (CANIF_BASIC_CAN == LucValue) */
      } /* if (CANIF_TX_ENABLED == LucValue) */
    }/* if (E_OK == LenStdRetVal)*/
    #endif
  /* polyspace +1 MISRA-C3:2.1 [Justified:High] "The value is generated by Generator." */
  }else{
    CANIF_UNUSED(CanTxPduId);
    CANIF_UNUSED_PTR(PduInfoPtr);
  }
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_ReadTxNotifStatus                             **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : This service provides the status of the CAN         **
**                        L-PDU requested by CanTxPduId. This API service     **
**                        notifies the upper layer about any transmit         **
**                        confirmation or receive indication event to the     **
**                        corresponding requested CAN L-PDU. During this      **
**                        call the CAN L-PDU notification status is reset     **
**                        inside the CAN Interface.                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : CanTxPduId                                          **
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
** Remarks              : Global Variable(s):                                 **
**                        CanIf_GblCanIfStatus, CanIf_GaaBitArray             **
**                        CanIf_GaaTxLpdu                                     **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Det_ReportError,                                    **
**                        SchM_Enter_CanIf_TX_NOTIFSTATUS_PROTECTION,         **
**                        SchM_Exit_CanIf_TX_NOTIFSTATUS_PROTECTION           **
*******************************************************************************/
#if ((STD_ON == CANIF_TX_LPDU) && (STD_ON == CANIF_READTXPDU_NOTIFY_STATUS_API))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(CanIf_NotifStatusType, CANIF_CODE) CanIf_ReadTxNotifStatus (
                                           VAR(PduIdType, CANIF_VAR) CanTxPduId)
{
  P2CONST(CanIf_TxLpdu, AUTOMATIC, CANIF_CONST) LpTxLpdu;
  VAR(CanIf_NotifStatusType, CANIF_VAR) LenNotifStsType;
  VAR(uint8, CANIF_VAR) LucNotifStsMask;
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  VAR(Std_ReturnType, CANIF_VAR) LenStdRetVal;
  #endif
  /* Initialize the return value with no notification */
  LenNotifStsType = CANIF_NO_NOTIFICATION;
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  LenStdRetVal = (uint8)E_OK;
  /* Report to DET, if module is not initialized */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_READ_TX_NOTIF_STATUS_SID, LenStdRetVal);
  /* Report to DET, if CanTxPduId is out of range */
  CANIF_TXPDUID_RANGE_ERROR(CANIF_READ_TX_NOTIF_STATUS_SID, LenStdRetVal);
  /* Check whether any error occurred? */
  if ((uint8)E_OK == LenStdRetVal)
  #endif
  {
    /* Get the pointer to the TxLpdu from requested CanTxPduId */		
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    LpTxLpdu = &CanIf_GaaTxLpduSelect[CanTxPduId];
    #else
    LpTxLpdu = &CanIf_GaaTxLpdu[CanTxPduId];
    #endif
    /* Get the notification mask from the Tx L-PDU structure */
		/* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Genderated array index in range" */	
    LucNotifStsMask = LpTxLpdu->ucTxNotifyStsMask;
    #if (STD_ON == CANIF_DEV_ERROR_DETECT)
    /* Report to DET, if notification is not configured for that Tx L-PDU */
		/* polyspace +1 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
    CANIF_NOTIFICATION_STATUS_ERROR(CANIF_READ_TX_NOTIF_STATUS_SID, \
                                                                   LenStdRetVal);
		/* polyspace +1 MISRA-C3:14.3, DEFECT:USELESS_IF [Not a defect: Justified] "Condition will be executed based on the configured values" */																																	
    if ((uint8)E_OK == LenStdRetVal)
    #endif
    {
      /* Check whether notification flag is set */
			/* polyspace +2 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
      if ((uint8)CANIF_ZERO !=
      (CanIf_GaaBitArray[LpTxLpdu->ucTxNotifyStatusIndex] & LucNotifStsMask))
      {
        /* enter critical area */
        SchM_Enter_CanIf_TX_NOTIFSTATUS_PROTECTION();
        /* Reset the status to zero */
        CanIf_GaaBitArray[LpTxLpdu->ucTxNotifyStatusIndex] &=
                                                    (uint8)(~(LucNotifStsMask));
        /* Exit critical area */
        SchM_Exit_CanIf_TX_NOTIFSTATUS_PROTECTION();
        /* Return confirmation to upper layer */
        LenNotifStsType = CANIF_TX_RX_NOTIFICATION;
      }/* if (CANIF_ZERO != (CanIf_GaaBitArray[LpTxLpdu->...)) */
    }/* if (E_OK == LenStdRetVal) */
  }/* if (E_OK == LenStdRetVal) */
  /* Return the Notification Status */
  return(LenNotifStsType);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        :  CanIf_GetTxConfirmationState                       **
**                                                                            **
** Service ID           :  0x19                                               **
**                                                                            **
** Description          :  This service reports, if any TX confirmation has   **
**                         been done for the whole CAN controller since the   **
**                         last CAN controller start.                         **
**                                                                            **
** Sync/Async           :  Synchronous                                        **
**                                                                            **
** Re-entrancy          :  Reentrant                                          **
**                                                                            **
** Input Parameters     :  CanController                                      **
**                                                                            **
** InOut Parameters     :  None                                               **
**                                                                            **
** Output Parameters    :  None                                               **
**                                                                            **
** Return parameter     :  CanIf_NotifStatusType                              **
**                                                                            **
** Preconditions        :  CanIf module must be initialised                   **
**                                                                            **
** Remarks              : Global Variable(s) :  CanIf_GblCanIfStatus          **
**                                              CanIf_GaaController           **
**                        Function(s) invoked:  Det_ReportError               **
*******************************************************************************/
#if (STD_ON == CANIF_TXCONFIRM_POLLING_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(CanIf_NotifStatusType, CANIF_CODE)CanIf_GetTxConfirmationState (
                                             VAR(uint8, CANIF_VAR) ControllerId)
{
  VAR(CanIf_NotifStatusType, CANIF_VAR) LenNotifStsType;
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  VAR(Std_ReturnType, CANIF_VAR) LenStdRetVal;
  #endif
  LenNotifStsType = CANIF_NO_NOTIFICATION;
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  LenStdRetVal = (uint8)E_OK;
  /* Check if CanIf is Initialised */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_GET_TX_CONFIRM_STATE_SID, LenStdRetVal);
  /* Check if the Range of controller is valid */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_GET_TX_CONFIRM_STATE_SID, LenStdRetVal);
  /* Is any DET error detected */
  if ((uint8)E_OK == LenStdRetVal)
  #endif
  {
    /* Set status for Tx confirmation notification */
		/* polyspace +1 MISRA-C3:D4.14,18.1, RTE:OBAI [Not a defect:Justified] "Array range is pre-defined" */
    if (CANIF_TX_CONFIRMED == ((CanIf_GaaController[ControllerId].ucTxStatus)
                                                & CANIF_TX_CONFIRM_STATUS_MASK))
    /* CANIF_TX_CONFIRMED = 0x81
       CANIF_TX_CONFIRM_STATUS_MASK = 0x80 */
    {
    /* setting Tx Rx notification as return value */
      LenNotifStsType = CANIF_TX_RX_NOTIFICATION;
    }
  }/* if (E_OK == LenStdRetVal) */
  return (LenNotifStsType);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : CanIf_DETCancelTxConfirmation                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to detect the DET error in     **
**                        CanIf_CancelTxConfirmation                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant, Not for same Tx L-PDU                   **
**                                                                            **
** Input Parameters     : CanTxPduId                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_GblCanIfStatus,           **
**                                            CanIf_GaaController             **
**                      : Function(s) invoked:                                **
**                        CanIf_GaaTxLpdu, CanIf_GddTxBuffCon                 **
**                        Det_ReportError, CanIf_QueueTransmit                **
*******************************************************************************/
#if ((STD_ON == CANIF_DEV_ERROR_DETECT) && (STD_ON == CANIF_TX_LPDU))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, CANIF_CODE) CanIf_DETCancelTxConfirmation (
                        VAR(PduIdType, CANIF_VAR) CanTxPduId,
                        P2CONST(PduInfoType, AUTOMATIC, CANIF_CONST) PduInfoPtr)
{
  VAR(Std_ReturnType, CANIF_VAR) LenStdRetVal;
  LenStdRetVal = (uint8)E_OK;
  
  /* Check whether CAN Interface is initialized or not */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_CANCEL_TX_CONFRM_SID, LenStdRetVal);
  if ((uint8)E_OK == LenStdRetVal)
  {
    /* Report to DET, If sdu pointer is Null Pointer */
    CANIF_NULL_PTR_ERROR(CANIF_CANCEL_TX_CONFRM_SID, LenStdRetVal, PduInfoPtr);
    /* Report to DET, if PduInfoPtr or SduDataPtr is equal to NULL */
		/* polyspace-begin MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */	
    if ((uint8)E_OK == LenStdRetVal)
    {
      CANIF_NULL_PTR_ERROR(CANIF_CANCEL_TX_CONFRM_SID, LenStdRetVal, \
      PduInfoPtr->SduDataPtr);
    }
    /* polyspace-begin DEFECT:USELESS_IF [Not a defect:Medium] "The value is generated by Generator." */
    /* polyspace +1 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
    if (CanIf_dlc_check_enable == (uint8)STD_ON)
    /* polyspace-end DEFECT:USELESS_IF [Not a defect:Medium] "The value is generated by Generator." */
    {
	  #if (STD_ON == CANIF_CANFD_SUPPORT)
      CANIF_CANFD_CANIDTYPE_DLC_ERROR(CANIF_CANCEL_TX_CONFRM_SID, LenStdRetVal);
	  #else
      /* Report to DET, if DLC is more than 8 byte */
      CANIF_CANIDTYPE_DLC_ERROR(CANIF_CANCEL_TX_CONFRM_SID, LenStdRetVal);
	  #endif
    }
    /* Report to DET, if TXPDU is out of range */
    CANIF_LPDU_RANGE_ERROR(CANIF_CANCEL_TX_CONFRM_SID, LenStdRetVal);
		/* polyspace-end MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */	
  }
  return(LenStdRetVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* Create dummy function for MISRA */
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANIF_CODE) CanIf_DummyTxConfirmation (PduIdType CanTxPduId)
{
  CANIF_UNUSED(CanTxPduId);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
