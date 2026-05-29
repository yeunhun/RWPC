/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTOEVER Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: PduR_RxLo.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Provision of the Common functionality of                      **
**              PduR_DETCheckLoRxIndication(), PduR_GWLoRxIndication(),       **
**              PduR_LoRxIndication and PduR_GWBufferUpdate()                 **
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
** 2.6.0     03-Nov-2020   HM Shin     #24937, #24858                         **
** 2.4.0     06-Sep-2019   HM Shin     #18909                                 **
** 2.3.0     22-Aug-2019   JS Lim      #18336                                 **
** 2.2.3     08-Mar-2018   Chan Kim    Redmine #11900                         **
** 2.2.0     01-Feb-2017   Chan Kim    Redmine #6922                          **
** 2.1.5     30-Nov-2016   Chan Kim    Redmine #6568, #6706, #6771            **
** 2.1.4     16-Nov-2016   Chan Kim    Redmine #6681                          **
** 2.1.1     17-Jun-2016   Chan Kim    Redmine #5490, #5632, #5680            **
** 2.1.0     17-Jun-2016   Chan Kim    Redmine #5190                          **
** 2.0.8     10-Jun-2016   Chan Kim    Redmine #5143                          **
** 2.0.4     19-Feb-2016   Chan Kim    Redmine #3429, #3425, #3813, #3827     **
** 2.0.3     24-Nov-2015   Chan Kim    Redmine #3545, #4519                   **
** 2.0.2     18-Sep-2015   Chan Kim    Redmine #3178                          **
** 2.0.0     11-Aug-2015   Chan Kim    Redmine #2949                          **
** 1.0.7     10-Jun-2013   Chan Kim    Change code for release Library        **
** 1.0.0     29-Apr-2013   Autoever      Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "PduR.h"               /* Header File */
#include "PduR_RxLo.h"          /* PduR RxLo header */
#include "SchM_PduR.h"          /* Schedular Manager header */
#include "PduR_Incl.h"          /* Dependent module Header files*/
#include "string.h"             /* memcpy() */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define PDUR_RXLO_C_AR_RELEASE_MAJOR_VERSION    4
#define PDUR_RXLO_C_AR_RELEASE_MINOR_VERSION    0
#define PDUR_RXLO_C_AR_RELEASE_REVISION_VERSION 3

/* PDUR software version information */
#define PDUR_RXLO_C_SW_MAJOR_VERSION            2
#define PDUR_RXLO_C_SW_MINOR_VERSION            9
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (PDUR_PCTYPES_AR_RELEASE_MAJOR_VERSION !=\
     PDUR_RXLO_C_AR_RELEASE_MAJOR_VERSION)
#error "PduR_RxLo.c : Mismatch in Specification Major Version"
#endif

#if (PDUR_PCTYPES_AR_RELEASE_MINOR_VERSION !=\
     PDUR_RXLO_C_AR_RELEASE_MINOR_VERSION)
#error "PduR_RxLo.c : Mismatch in Specification Minor Version"
#endif

#if (PDUR_PCTYPES_AR_RELEASE_REVISION_VERSION !=\
     PDUR_RXLO_C_AR_RELEASE_REVISION_VERSION)
#error "PduR_RxLo.c : Mismatch in Specification Revision Version"
#endif

#if (PDUR_PCTYPES_SW_MAJOR_VERSION != PDUR_RXLO_C_SW_MAJOR_VERSION)
#error "PduR_RxLo.c : Mismatch in Software Major Version"
#endif

#if (PDUR_PCTYPES_SW_MINOR_VERSION != PDUR_RXLO_C_SW_MINOR_VERSION)
#error "PduR_RxLo.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if ((PDUR_ZERO_COST_OPERATION == STD_OFF) && (PDUR_LO_RXINDICATION == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, PDUR_VAR) PduR_DETCheckLoRxIndication(
  PduIdType LddRxPduId, uint8 LucModuleType, uint8 LucAPIId,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_VAR) LpPduInfoPtr);

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if ((PDUR_ZERO_COST_OPERATION == STD_OFF) &&
                                           (PDUR_LO_RXINDICATION == STD_ON)) */
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON)*/

#if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) ||\
  (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON))
#if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
static FUNC(boolean, PDUR_VAR) PduR_GWBufferUpdate
(P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr,
  P2CONST(PduR_LoGWRxIndication, AUTOMATIC, PDUR_CONST) LpGWIfPdu);
#else
static FUNC(void, PDUR_VAR) PduR_GWBufferUpdate
(P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr,
  P2CONST(PduR_LoGWRxIndication, AUTOMATIC, PDUR_CONST) LpGWIfPdu);
#endif
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON)*/
#endif

#if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if ((PDUR_DEV_ERROR_DETECT == STD_ON) && \
((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) || \
(PDUR_SB_TX_BUFFER_SUPPORT == STD_ON)))
static FUNC(boolean, PDUR_VAR) PduR_GWLoRxIndication(PduIdType LddRxPduId,
       P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr);
#else
static FUNC(void, PDUR_VAR) PduR_GWLoRxIndication(PduIdType LddRxPduId,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr);
#endif
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON)*/

/*******************************************************************************
** Function Name        : PduR_LoRxIndication                                 **
**                                                                            **
** Service ID           : 0x<LoModId>1                                        **
**                                                                            **
** Description          : This function is called by the Interface layer after**
**                        a L-PDU has been received. The PDU Router shall     **
**                        translate the RxPduId into the configured target    **
**                        PDU ID and route this indication to the configured  **
**                        target function. This function shall only be        **
**                        provided if the pre-compile time configuration      **
**                        parameter PDUR_CANIF_SUPPORT or PDUR_LINIF_SUPPORT  **
**                        or PDUR_FRIF_SUPPORT or PDUR_IPDUM_SUPPORT is       **
**                        enabled                                             **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant for different PduIds                      **
**                        Non-Reentrant for the same PduId                    **
**                                                                            **
** Input Parameters     : PduIdType LddRxPduId, uint8 LucAPIId,               **
**                        uint8 LucModuleType, PduInfoType *PduInfoPtr        **
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
**                        PduR_GaaLoRxIndication, PduR_GaaIfReceive           **
**                        PduR_GulGroupMaskValue                              **
**                                                                            **
** Function(s) invoked  : PduR_DETCheckLoRxIndication(),                      **
**                        PduR_GWLoRxIndication(),                            **
**                                                                            **
*******************************************************************************/
/* Requirement PDUR362 */
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_LO_RXINDICATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
FUNC(void, PDUR_VAR) PduR_LoRxIndication(PduIdType LddRxPduId, uint8 LucAPIId,
  uint8 LucModuleType, P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr)
#else
FUNC(void, PDUR_VAR) PduR_LoRxIndication(PduIdType LddRxPduId,
                           P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr)
#endif /*#if (PDUR_DEV_ERROR_DETECT == STD_OFF)*/
{
  P2CONST(PduR_LoRxInd, AUTOMATIC, PDUR_CONST) LpLoRxIndication;
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 LusGroupMaskValue;
  #endif
  #if (PDUR_TOTAL_COUNT_RX_LO_CALLOUT > 0)
  boolean LblLoRxIndFlag = PDUR_TRUE;
  #endif
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  boolean LblDetErrorFlag;
  LblDetErrorFlag = PduR_DETCheckLoRxIndication
                            (LddRxPduId, LucModuleType, LucAPIId, LpPduInfoPtr);

  /* Check whether any development errors are detected */
  if ((boolean)PDUR_FALSE == LblDetErrorFlag)
  #endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Pointer to Interface Rx Indication Structure for the source PduId */
    LpLoRxIndication = &PduR_GaaLoRxIndication[LddRxPduId];

    /* polyspace-begin MISRA2012:2.1 [Justified:Low] "Condition will be executed based on the configured values" */
    /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
    /* polyspace-begin MISRA2012:14.3 [Justified:Low] "Condition will be executed based on the configured values" */
    /* polyspace-begin DEFECT:USELESS_IF [Not a defect:Low] "Condition will be executed based on the configured values" */
    /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
    #if (PDUR_TOTAL_COUNT_RX_LO_CALLOUT > 0)
    if (PDUR_UNDEFINED != LpLoRxIndication->usRxLoIndCallOutIdx)
    {
      if (NULL_PTR != PduR_GpRxLoIndicationUserCallout)
      {
        P2CONST(PduR_RxIndicationCallOut, AUTOMATIC, PDUR_CONST) LpLoRxIndicationCallOut;
       
        LpLoRxIndicationCallOut = &PduR_GpRxLoIndicationUserCallout[LpLoRxIndication->usRxLoIndCallOutIdx];
        if (NULL_PTR != LpLoRxIndicationCallOut->pFuncPduRCallOut)
        {
          LblLoRxIndFlag = LpLoRxIndicationCallOut->pFuncPduRCallOut(LddRxPduId, LpPduInfoPtr);
        }
      }
    }

    if (PDUR_TRUE == LblLoRxIndFlag)
    #endif
    {
      #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)

      uint8 LucRoutingPathBitStatus = (uint8)PDUR_FALSE;

      /* Get the group mask value */
      LusGroupMaskValue = LpLoRxIndication->usGroupMaskValue;

      if (PDUR_UNDEFINED_ROUTINGPATH_GROUP != LusGroupMaskValue)
      {
        if ((uint8)PDUR_ZERO != (PduR_GaaRoutingPathGroupRam[LusGroupMaskValue >> 3] & ((uint8)1 << (uint8)(LusGroupMaskValue % 8))))
        {
          LucRoutingPathBitStatus = (uint8)PDUR_TRUE;
        }
      }
      
      /* Check if routing path is enabled */
      if ((PDUR_UNDEFINED_ROUTINGPATH_GROUP == LusGroupMaskValue) || (PDUR_FALSE != LucRoutingPathBitStatus))
      #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
      {
        #if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
        /* check whether it's gateway  */
        if ((uint8)PDUR_ZERO ==
        (LpLoRxIndication->ucTargetIndexOrRoutePDU & (uint8)PDUR_NONGATEWAY_MASK))
        #endif
        {
          #if (PDUR_FUN_IFRXINDICATION_SUPPORT == STD_ON)
          #if(PDUR_TOTAL_COUNT_IF_RECEIVE > PDUR_ZERO)
          /* Invoke <Up>_RxIndication */
          if(PduR_GaaIfReceive[LpLoRxIndication->ucTargetIndexOrRoutePDU]
            .pTargetLayer != NULL_PTR)
          {
            (void)PduR_GaaIfReceive[LpLoRxIndication->ucTargetIndexOrRoutePDU]
              .pTargetLayer((LpLoRxIndication->ddUpTargetPduId), LpPduInfoPtr);
          }
          #endif		
          #endif
        } /* End of if (PDUR_ZERO ==
            (LpLoRxIndication->ucTargetIndexOrRoutePDU & PDUR_NONGATEWAY_MASK))*/
        #if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
        else /* If Gateway */
        {
          #if ((PDUR_DEV_ERROR_DETECT == STD_ON) && \
      ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) || \
        (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON)))
          LblDetErrorFlag = PduR_GWLoRxIndication(LddRxPduId, LpPduInfoPtr);
          if((boolean)PDUR_TRUE == LblDetErrorFlag)
          {
            /* Report to DET */
            (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                                            LucAPIId, PDUR_E_PDU_INSTANCES_LOST);
          }
          #else
          PduR_GWLoRxIndication(LddRxPduId, LpPduInfoPtr);
          #endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
        } /* End of else */
        #endif /* #if (PDUR_IF_GATEWAY_OPERATION == STD_ON) */
      }
    }
    /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
    /* polyspace-end DEFECT:USELESS_IF [Not a defect:Low] "Condition will be executed based on the configured values" */
    /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
    /* polyspace-end MISRA2012:2.1 [Justified:Low] "Condition will be executed based on the configured values" */
    /* polyspace-end MISRA2012:14.3 [Justified:Low] "Condition will be executed based on the configured values" */
  }
} /* End of PduR_LoRxIndication(PduIdType LddRxPduId, P2VAR(PduInfoType,
   *AUTOMATIC, PDUR_VAR) LpPduInfoPtr) */

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_LO_RXINDICATION == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF)*/

/*******************************************************************************
** Function Name        : PduR_DETCheckLoRxIndication                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_LoRxIndication function                        **
**                        to check the parameters passed are valid and        **
**                        buffer does not need to be the length of the        **
**                        report to DET in case of invalid values.            **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType LddRxPduId, uint8 LucModuleType,          **
**                        uint8 LucAPIId, PduInfoType *LpPduInfoPtr           **
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
**                        PduR_GblInitStatus, PduR_GaaLoRxIndication          **
**						  PduR_GpLoRxIndication, PduR_Lo_RxIndication_MaxPduID**
**                                                                            **
** Function(s) invoked  : Det_ReportError()                                   **
*******************************************************************************/
#if ((PDUR_ZERO_COST_OPERATION == STD_OFF) && (PDUR_LO_RXINDICATION == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)

#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, PDUR_VAR) PduR_DETCheckLoRxIndication(
  PduIdType LddRxPduId, uint8 LucModuleType, uint8 LucAPIId,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_VAR) LpPduInfoPtr)
{
  P2CONST(PduR_LoRxInd, AUTOMATIC, PDUR_CONST) LpLoRxIndication;
  boolean LblDetErrorFlag;

  /* Set the DetErrorFlag to the PDUR_FALSE */
  LblDetErrorFlag = (boolean)PDUR_FALSE;
  /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  /* Check whether the module is initialised */
  if ((boolean)PDUR_UNINITIALIZED == PduR_GblInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, LucAPIId,
      PDUR_E_INVALID_REQUEST);
    /* Set the error flag to TRUE */
    LblDetErrorFlag = (boolean)PDUR_TRUE;
  } /* End of if (PDUR_UNINITIALIZED == PduR_GblInitStatus) */
  else
  {
    /* Assign Local Pointer to Interface Rx Indication Structure for the source
     *   PduId */
    LpLoRxIndication = &PduR_GaaLoRxIndication[LddRxPduId];
    if (LddRxPduId >= (PduIdType)PduR_Lo_RxIndication_MaxPduID)
    {
      /* Report to DET */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        LucAPIId, PDUR_E_PDU_ID_INVALID);
      /* Set the error flag to TRUE */
      LblDetErrorFlag = (boolean)PDUR_TRUE;
    } /* End of if (LddRxPduId >= PduR_Lo_RxIndication_MaxPduID) */
    else
    {
      if (LpLoRxIndication->ucModuleType != LucModuleType)
      {
        /* Report to DET */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          LucAPIId, PDUR_E_PDU_ID_INVALID);
        /* Set the error flag to TRUE */
        LblDetErrorFlag = (boolean)PDUR_TRUE;
      } /* End of if (PduR_GaaLoRxIndication[LddRxPduId].ucModuleType !=
         *LucModuleType) */
    }
    /* Check If LpPduInfoPtr is NULL_PTR */
    if (NULL_PTR == LpPduInfoPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, LucAPIId,
        PDUR_E_NULL_POINTER);
      /* Set the error flag to TRUE */
      LblDetErrorFlag = (boolean)PDUR_TRUE;
    } /* End of if (NULL_PTR == LpPduInfoPtr) */
    else
    {
      /* polyspace<MISRA-C3:D4.14 :: Not a defect Justify with annotations> No Action Planned, condition used to verify the pointer is NULL or not */
      if((NULL_PTR == LpPduInfoPtr->SduDataPtr))
      {
        /* Report to DET */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, LucAPIId,
          PDUR_E_NULL_POINTER);
        /* Set the error flag to TRUE */
        LblDetErrorFlag = (boolean)PDUR_TRUE;
      } /* End of if ((NULL_PTR == LpPduInfoPtr->SduDataPtr)) */
    } /*End of else*/
  }
  /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  return (LblDetErrorFlag);
} /* End of PduR_DETCheckLoRxIndication(
   * PduIdType LddRxPduId, uint8 LucModuleType, uint8 LucAPIId,
   * P2CONST(PduInfoType, AUTOMATIC, PDUR_VAR) LpPduInfoPtr) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
#endif /* #if (PDUR_LO_RXINDICATION == STD_ON) */

/*******************************************************************************
** Function Name        : PduR_GWLoRxIndication                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_LoRxIndication function in case of gateway.    **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType LddRxPduId,                               **
**                        PduInfoType *LpPduInfoPtr                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean LblRetVal                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_GaaLoRxIndication, PduR_GulGroupMaskValue,     **
**                        PduR_GaaIfTransmitService, PduR_GaaIfReceive,       **
**                                                                            **
** Function(s) invoked  : PduR_GWBufferUpdate()                               **
**                                                                            **
*******************************************************************************/
#if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if ((PDUR_DEV_ERROR_DETECT == STD_ON) && \
((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) || \
(PDUR_SB_TX_BUFFER_SUPPORT == STD_ON)))
static FUNC(boolean, PDUR_VAR) PduR_GWLoRxIndication(PduIdType LddRxPduId,
 P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr)
#else
static FUNC(void, PDUR_VAR) PduR_GWLoRxIndication(PduIdType LddRxPduId,
                        P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr)
#endif
{
  P2CONST(PduR_LoRxInd, AUTOMATIC, PDUR_CONST) LpLoRxIndication;
  P2CONST(PduR_LoGWRxIndication, AUTOMATIC, PDUR_CONST) LpGWIfPdu;
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 LusGroupMaskValue;
  #endif
  PduIdType LddTargetPduId;
  uint8 LucNoOfRoutePdu;
  uint16 LusTxBufferIndex;
  uint8 LucTargetIndexBufType;
  #if ((PDUR_DEV_ERROR_DETECT == STD_ON) &&\
  ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) || \
(PDUR_SB_TX_BUFFER_SUPPORT == STD_ON)))
  boolean LblReturnValue;
  LblReturnValue = (boolean)PDUR_FALSE;
  #endif

  /* Assign Local Pointer to Interface Rx Indication Structure for the source
   *   PduId */
  LpLoRxIndication = &(PduR_GaaLoRxIndication[LddRxPduId]);

  /* Assign Local Pointer to LoGWRxIndication Structure */
  LpGWIfPdu = LpLoRxIndication->pGWIfPdu;

  /* Check if singlecast gateway */
  if (PDUR_GATEWAY_MASK ==
      (LpLoRxIndication->ucTargetIndexOrRoutePDU & PDUR_GATEWAY_MASK))
  {
    /* Get the Number of Route for Source PDU */
    LucNoOfRoutePdu = (uint8)PDUR_ONE;
  }
  else
  {
    /* Get the Number of Route for Source PDU during Multicast */
    LucNoOfRoutePdu = (LpLoRxIndication->ucTargetIndexOrRoutePDU &
                       (uint8)PDUR_NOOFROUTE_MASK);
  }
  /* Loop for the Number of Route of the Source PDU */
  /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  do
  {
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    /* Get the group mask value */
    uint8 LucRoutingPathBitStatus = 0;
    #endif
    /* Get the buffer index */
    /* polyspace<RTE: IDP : Not a defect Justify with annotations> configured memory access index */
    /* polyspace<MISRA-C3:D4.1, 18.1:: Not a defect Justify with annotations> Its boundary is pre-defined */
    LusTxBufferIndex = LpGWIfPdu->usTxBufferIndex;
    /* Get the Target Layer PduId during Multicast */
    LddTargetPduId = LpGWIfPdu->ddTargetPduId;
    /* Get the target layer configuration */
    LucTargetIndexBufType = (uint8)(LpGWIfPdu->ucTargetIndexBufType);
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    /* Get the group mask value */
    LusGroupMaskValue = LpGWIfPdu->usGroupMaskValue;

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
      if((uint16)PDUR_UPPER_LAYER == LusTxBufferIndex)
      #endif
      {
        #if (PDUR_FUN_IFRXINDICATION_SUPPORT == STD_ON)
        #if(PDUR_TOTAL_COUNT_IF_RECEIVE > PDUR_ZERO)

        /* Invoke <Up>_RxIndication */
        if(PduR_GaaIfReceive[LucTargetIndexBufType & PDUR_INDEX_MASK]
          .pTargetLayer != NULL_PTR)
        {
          (void)PduR_GaaIfReceive[LucTargetIndexBufType & PDUR_INDEX_MASK]
            .pTargetLayer(LddTargetPduId, LpPduInfoPtr);
        }
        #endif
        #endif		
      }
      #if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
      else
      {
        #if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) ||\
        (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON))
        /* Check whether buffer is allocated */
        if ((uint16)PDUR_GATEWAY_NOBUFFER != LusTxBufferIndex)
        {
          #if (PDUR_DEV_ERROR_DETECT == STD_ON)
          LblReturnValue = PduR_GWBufferUpdate(LpPduInfoPtr, LpGWIfPdu);
          #else
          PduR_GWBufferUpdate(LpPduInfoPtr, LpGWIfPdu);
          #endif
        } /* End of if (PDUR_GATEWAY_NOBUFFER != LusTxBufferIndex) */
        else /* gateway without buffer */
        #endif /* #if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) || \
                *                 (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON)) */
        {
          #if (PDUR_TOTAL_COUNT_IF_TRANSMIT > PDUR_ZERO)

          /* Invoke transmit function */
          if(PduR_GaaIfTransmitService[LucTargetIndexBufType
                  & PDUR_INDEX_MASK].pTargetLayer != NULL_PTR)
          {
            (void)PduR_GaaIfTransmitService[LucTargetIndexBufType
                  & PDUR_INDEX_MASK].pTargetLayer(LddTargetPduId, LpPduInfoPtr);
          }
          #endif		  
        }
      }
      #endif
    }
    /* Increment the MulticastGWIfPdu Pointer */
    LpGWIfPdu++;
    /* Decrement the Number of Route PDU */
    LucNoOfRoutePdu--;
  } while ((uint8)PDUR_ZERO != LucNoOfRoutePdu);
  /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  #if ((PDUR_DEV_ERROR_DETECT == STD_ON) &&\
  ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) || \
(PDUR_SB_TX_BUFFER_SUPPORT == STD_ON)))
  return(LblReturnValue);
  #endif
} /* End of PduR_GWLoRxIndication(PduIdType LddRxPduId, P2VAR(PduInfoType,
   *AUTOMATIC, PDUR_VAR) LpPduInfoPtr) */

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_IF_GATEWAY_OPERATION == STD_ON) */

/*******************************************************************************
** Function Name        : PduR_GWBufferUpdate                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_GWLoRxIndication function in case of           **
**                        gateway.                                            **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduInfoType *LpPduInfoPtr, LpGWIfPdu                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean LblRetVal                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_GaaTxBuffer, PduR_GaaIfTransmitService         **
**                                                                            **
** Function(s) invoked  : Det_ReportError(),                                  **
**                        SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA()       **
**                        SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA()        **
**                        SchM_Enter_PduR_FIFO_STATUS_PROTECTION_AREA()       **
**                        SchM_Exit_PduR_FIFO_STATUS_PROTECTION_AREA()        **
**                        CANIF_TXPDU_GW_STATUS()                             **
*******************************************************************************/
#if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
#if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) ||\
  (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON))
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
static FUNC(boolean, PDUR_VAR) PduR_GWBufferUpdate
(P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr,
  P2CONST(PduR_LoGWRxIndication, AUTOMATIC, PDUR_CONST) LpGWIfPdu)
#else
static FUNC(void, PDUR_VAR) PduR_GWBufferUpdate
(P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr,
  P2CONST(PduR_LoGWRxIndication, AUTOMATIC, PDUR_CONST) LpGWIfPdu)
#endif
{
  #if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON))
  P2VAR(PduR_FifoBuffer, AUTOMATIC, PDUR_VAR) LpFIFOBuffer;
  P2VAR(PduInfoType, AUTOMATIC, PDUR_VAR) LpBufPduInfoPtr;
  #endif
  P2CONST(uint8, AUTOMATIC, PDUR_CONST) LpSduPtr;
  P2CONST(PduR_TxBuffer, AUTOMATIC, PDUR_CONST) LpTxBuffer;
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) LpDataBuffer;
  P2VAR(PduInfoType, AUTOMATIC, PDUR_VAR) LpPduInfoUpdatePtr;
  PduLengthType LddLengthVar;
  #if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON))
  uint8 LucMask;
  #if(PDUR_CANIF_SUPPORT == STD_ON)
  uint8 LucCanIfPduStatus;
  #endif
  #endif
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  boolean LblRetVal;
  LblRetVal = (boolean)PDUR_FALSE;
  #endif
  /* Get the respective buffer into local pointer */
  LpTxBuffer = &PduR_GaaTxBuffer[LpGWIfPdu->usTxBufferIndex];

  /* Get the pointer to LpPduInfoUpdatePtr structure */
	/* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect: Justify with annotations] "PduR_GaaTxBuffer array index in range" */
  LpPduInfoUpdatePtr = LpTxBuffer->pPduInfoPtr;
  /* polyspace-begin RTE:UNR [Not a defect:Low] "No Impact of this rule violation" */
  #if(PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
  #if(PDUR_CANIF_SUPPORT == STD_ON)
  LucCanIfPduStatus = PDUR_INVALID;
  if (((LpGWIfPdu->ucTargetIndexBufType) &
      PDUR_INDEX_MASK) == PDUR_LOWERLAYER_CANIF)
  {
    LucCanIfPduStatus = CANIF_TXPDU_GW_STATUS(LpGWIfPdu->ddTargetPduId);
  }
  #if(PDUR_CDD_ROUTER_IF_SUPPORT == STD_ON)
  #ifdef PDUR_LOWERLAYER_CDD_ROUTERIF
  else if (((LpGWIfPdu->ucTargetIndexBufType) & PDUR_INDEX_MASK) == PDUR_LOWERLAYER_CDD_ROUTERIF) // Cdd_Router_Transmit Index
  {
    if (CDD_ROUTER_TXPDU_TARGET(LpGWIfPdu->ddTargetPduId) == CddComIfUpperLayer) // 0 is CanIf , 1 is SoAdIf
    {
      uint16 LusTargetPduId = CDD_ROUTER_CANIF_TXPDU(LpGWIfPdu->ddTargetPduId);
      LucCanIfPduStatus = CANIF_TXPDU_GW_STATUS(LusTargetPduId);
    }
  }
  else
  {
    /* Do Nothing */
  }
  #endif
  #endif
  #endif
  
  LpFIFOBuffer = LpTxBuffer->pFifoBuffer;
  LucMask = ((LpGWIfPdu->ucTargetIndexBufType) & (uint8)(PDUR_BUFFER_MASK));
  /* If the buffer type is FIFO */
	/* polyspace:begin<MISRA-C:17.4::Not a defect Justify with annotations> Not a defect, Decrement and Increment operator is used to achieve better throughput */
  if (((uint8)PDUR_D_FIFO == LucMask)||((uint8)PDUR_TT_FIFO == LucMask))
  {
    /* Enter critical area */
    #if(PDUR_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Enter_PduR_FIFO_STATUS_PROTECTION_AREA();
    #endif
    /* Check whether Depth is greater than configured value */
    if ((LpFIFOBuffer->ucDepth) >= (LpTxBuffer->ucFIFODepth))
    {
      /* Reset all the variable and report to DET if enabled */
      LpFIFOBuffer->ucWrite = (uint8)PDUR_ZERO; 
      LpFIFOBuffer->ucRead = (uint8)PDUR_ZERO;
      LpFIFOBuffer->ucDepth = (uint8)PDUR_ZERO;
      #if (PDUR_DEV_ERROR_DETECT == STD_ON)
      LblRetVal = (boolean)PDUR_TRUE;
      #endif
    }

    #if(PDUR_CANIF_SUPPORT == STD_ON)
    if(((uint8)PDUR_D_FIFO == LucMask) && ((uint8)PDUR_ZERO != 
    (LpFIFOBuffer->ucDepth)))
    {
      /* Check if target lower layer is CanIf */
      if(LucCanIfPduStatus == CANIF_GW_NOREQUEST)
      {
        /* Get PduInfoPtr into local pointer */
        LpBufPduInfoPtr = LpTxBuffer->pPduInfoPtr;
        /* point to corresponding pPduInfoPtr */
        LpBufPduInfoPtr = LpBufPduInfoPtr 
        + (PduR_PtrType)(LpFIFOBuffer->ucRead);

        /* Invoke transmit function */
        if(PduR_GaaIfTransmitService[(LpGWIfPdu->ucTargetIndexBufType)
                                    & PDUR_INDEX_MASK].pTargetLayer != 
                                    NULL_PTR)
        {
          (void)PduR_GaaIfTransmitService[(LpGWIfPdu->ucTargetIndexBufType)
                                    & PDUR_INDEX_MASK].pTargetLayer
            (LpGWIfPdu->ddTargetPduId, LpBufPduInfoPtr);
        }
      }
      else if((LucCanIfPduStatus == CANIF_GW_NOCOMM) || (LucCanIfPduStatus == 
      CANIF_GW_ERRVOL))
      {
        LpFIFOBuffer->ucWrite = (uint8)PDUR_ZERO; 
        LpFIFOBuffer->ucRead = (uint8)PDUR_ZERO;
        LpFIFOBuffer->ucDepth = (uint8)PDUR_ZERO;
      }
      else
      {
        /* Do nothing */
      }
    }
    #endif

    /* Update the UpdatePtr with Txbuffer PduInfoPtr */
    LpPduInfoUpdatePtr = LpPduInfoUpdatePtr 
    + (PduR_PtrType)(LpFIFOBuffer->ucWrite);
    
    /* Exit critical area */
    #if(PDUR_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Exit_PduR_FIFO_STATUS_PROTECTION_AREA();
    #endif
  }/* End of if ((LucMask == (uint8)PDUR_D_FIFO)||
                      (LucMask == (uint8)PDUR_TT_FIFO)) */
  #endif /* End of if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) */
	/* polyspace:end<MISRA-C:17.4::Not a defect Justify with annotations> Not a defect, Decrement and Increment operator is used to achieve better throughput */



  /* polyspace:begin<MISRA-C3:D4.14 :: Not a defect Justify with annotations> No Action Planned, condition used to verify the pointer is NULL or not */
  /* Get the pointer to Data buffer */
	/* polyspace +2 MISRA-C3:18.1, RTE:IDP [Not a defect: Justify with annotations] "PduR_GaaTxBuffer array index in range" */
  LpPduInfoUpdatePtr->SduLength = LpPduInfoPtr->SduLength;
  /* polyspace:end<MISRA-C3:D4.14 :: Not a defect Justify with annotations> No Action Planned, condition used to verify the pointer is NULL or not */
  if(LpGWIfPdu->ddPduLength < LpPduInfoUpdatePtr->SduLength)
  {
    LpPduInfoUpdatePtr->SduLength = LpGWIfPdu->ddPduLength;
  }
  LddLengthVar = LpPduInfoUpdatePtr->SduLength;

  /* Get the data pointer into local variable */
  LpDataBuffer = LpPduInfoUpdatePtr->SduDataPtr;  
  LpSduPtr = LpPduInfoPtr->SduDataPtr;
  #if(PDUR_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA();
  #endif

	/* polyspace +2 MISRA-C3:D4.11, RTE:STD_LIB [Not a defect: Justify with annotations] "Valid arguments are passed" */
  memcpy((P2VAR(void, AUTOMATIC, PDUR_VAR))(LpDataBuffer),
        (P2CONST(void, AUTOMATIC, PDUR_CONST))(LpSduPtr),
        LddLengthVar);
  
  #if(PDUR_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA();
  #endif

  #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
  /* check if return value is E_OK for buffered transmission */
  if ((LucMask == (uint8)PDUR_D_FIFO) || (LucMask == (uint8)PDUR_TT_FIFO))
  {
    if((LpFIFOBuffer->ucDepth == (uint8)PDUR_ZERO)
    #if(PDUR_CANIF_SUPPORT == STD_ON)
      && (!((LucCanIfPduStatus == CANIF_GW_STOPPED) || (LucCanIfPduStatus == 
      CANIF_GW_ERRVOL)))
    #endif
      )
    {
      /* Invoke transmit function */
      if(PduR_GaaIfTransmitService[(LpGWIfPdu->ucTargetIndexBufType) &
              PDUR_INDEX_MASK].pTargetLayer != NULL_PTR)
      {
        (void)PduR_GaaIfTransmitService[(LpGWIfPdu->ucTargetIndexBufType) &
              PDUR_INDEX_MASK].pTargetLayer
                      (LpGWIfPdu->ddTargetPduId, LpPduInfoUpdatePtr);
      }
      else
      {
        /* Do nothing */
      }
    }

    #if(PDUR_CANIF_SUPPORT == STD_ON)
    if(LucCanIfPduStatus != CANIF_GW_ERRVOL)
    #endif
    {
  		/* Enter critical area */	  
      #if(PDUR_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
      SchM_Enter_PduR_FIFO_STATUS_PROTECTION_AREA();		
      #endif
      LpFIFOBuffer->ucWrite++;
      /* Increment Depth */
      LpFIFOBuffer->ucDepth++;
      /* Check whether count is more than the depth of FIFO */
      if ((LpFIFOBuffer->ucWrite) >= (LpTxBuffer->ucFIFODepth))
      {
        LpFIFOBuffer->ucWrite = (uint8)PDUR_ZERO;
      }
  		/* Exit critical area */		
      #if(PDUR_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
      SchM_Exit_PduR_FIFO_STATUS_PROTECTION_AREA();		  
      #endif
    }

  }
  else
  #endif /*#if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)*/
  {
    /* Invoke transmit function */
    if(PduR_GaaIfTransmitService[(LpGWIfPdu->ucTargetIndexBufType) &
              PDUR_INDEX_MASK].pTargetLayer != NULL_PTR)
    {
      (void)PduR_GaaIfTransmitService[(LpGWIfPdu->ucTargetIndexBufType) &
              PDUR_INDEX_MASK].pTargetLayer
                            (LpGWIfPdu->ddTargetPduId, LpPduInfoUpdatePtr);
    }
  }
  /* polyspace-begin RTE:UNR [Not a defect:Low] "No Impact of this rule violation" */
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  return(LblRetVal);
  #endif
} /* End of PduR_GWBufferUpdate(P2CONST(PduInfoType, AUTOMATIC,
   *PDUR_VAR) LpPduInfoPtr, uint8 LucBufferIndex, PduIdType LddTargetPduId,
   *uint8 LucTargetIndexBufType) */

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif /* #if (PDUR_IF_GATEWAY_OPERATION == STD_ON) */

/*******************************************************************************
** Function Name        : PduR_GetGwBufferStatus                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        User in case of gateway to check buffer is available**
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType LddPduRSrcPduId                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PduR_GwBufferStatus                                 **
**                                                                            **
** Return parameter     : PduR_GwBufferStatus ret                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_GaaLoRxIndication                              **
**                                                                            **
** Function(s) invoked  :                                                     **
*******************************************************************************/
#if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
#if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
/* Rx Buffer is always smaller than when this API called. */
FUNC(PduR_GwBufferStatus, PDUR_CODE) PduR_GetGwBufferStatus(PduIdType LddPduRSrcPduId)
{
  PduR_GwBufferStatus LddStatus;

  P2CONST(PduR_LoRxInd, AUTOMATIC, PDUR_CONST) LpLoRxIndication;
  P2CONST(PduR_LoGWRxIndication, AUTOMATIC, PDUR_CONST) LpGWIfPdu;
  P2CONST(PduR_TxBuffer, AUTOMATIC, PDUR_CONST) LpTxBuffer;
  P2VAR(PduR_FifoBuffer, AUTOMATIC, PDUR_VAR) LpFIFOBuffer;
  uint8 LucNoOfRoutePdu = 0;
  uint8 LucMask = 0;
  uint8 LucConfiguredFifoDepth = 0;
  uint8 LucCurrentFifoDepth = 0;

  LddStatus.ucNoOfRoutePdu = 0;
  PduR_Memset(LddStatus.aaPathStatus, 0x00, PDUR_MAX_MULTICAST_COUNT);
  PduR_Memset(LddStatus.aaBufStatus, 0x00, PDUR_MAX_MULTICAST_COUNT);

  if (LddPduRSrcPduId < PDUR_LO_RXINDICATION_MAXPDUID)
  {
    /* Assign Local Pointer to Interface Rx Indication Structure for the source PduId */
    LpLoRxIndication = &PduR_GaaLoRxIndication[LddPduRSrcPduId];
    
    /* Assign Local Pointer to LoGWRxIndication Structure */
    LpGWIfPdu = LpLoRxIndication->pGWIfPdu;
  
    /* Check if multicast gateway */
    if (PDUR_GATEWAY_MASK ==
        (LpLoRxIndication->ucTargetIndexOrRoutePDU & PDUR_GATEWAY_MASK))
    {
      /* Get the Number of Route for Source PDU */
      LucNoOfRoutePdu = (uint8)PDUR_ONE;
    }
    else
    {
      /* Get the Number of Route for Source PDU during Multicast */
      LucNoOfRoutePdu = (LpLoRxIndication->ucTargetIndexOrRoutePDU &
                         (uint8)PDUR_NOOFROUTE_MASK);
    }
  
    LddStatus.ucNoOfRoutePdu = LucNoOfRoutePdu;
    
    /* Loop for the Number of Route of the Source PDU */
    /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
    while ((uint8)PDUR_ZERO != LucNoOfRoutePdu)
    {
      uint8 LucNum = LucNoOfRoutePdu - (uint8)PDUR_ONE;
      LucMask = ((LpGWIfPdu->ucTargetIndexBufType) & (uint8)(PDUR_BUFFER_MASK));
      
      /* If the buffer type is FIFO */
      if ((uint8)PDUR_D_FIFO == LucMask)
      {
        LddStatus.aaPathStatus[LucNum / (uint8)8] |= (uint8)PDUR_ONE << (LucNum % (uint8)8);
        
        LpTxBuffer = &PduR_GaaTxBuffer[LpGWIfPdu->usTxBufferIndex];
      
        /* Get configured TxBuffer */
        LucConfiguredFifoDepth = LpTxBuffer->ucFIFODepth;
      
        LpFIFOBuffer = LpTxBuffer->pFifoBuffer;
      
        /* Get current TxBuffer */
        LucCurrentFifoDepth = LpFIFOBuffer->ucDepth;
      
        LucMask = ((LpGWIfPdu->ucTargetIndexBufType) & (uint8)(PDUR_BUFFER_MASK));
        
        /* Check current Buffer status */
        if (LucConfiguredFifoDepth > LucCurrentFifoDepth)
        {
          LddStatus.aaBufStatus[LucNum / (uint8)8] |= (uint8)PDUR_ONE << (LucNum % (uint8)8);
        }
      }
  
      /* Increment the MulticastGWIfPdu Pointer */
      LpGWIfPdu++;
      /* Decrement the Number of Route PDU */
      LucNoOfRoutePdu--;
    };
    /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  }

  return LddStatus;
}

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif /* #if (PDUR_IF_GATEWAY_OPERATION == STD_ON) */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
