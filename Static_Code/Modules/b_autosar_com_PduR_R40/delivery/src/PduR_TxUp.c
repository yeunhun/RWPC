/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTOEVER Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: PduR_TxUp.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Provision of the functionality of PduR_DETCheckUpTransmit()   **
**              PduR_UpTransmit(), PduR_IfTransmit()                          **
**              and PduR_TpTransmit(), PduR_UpCancelTransmit                  **
**              PduR_DETCheckCancelTransmit                                   **
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
** 2.5.0.0   28-Feb-2020   HM Shin     #19725                                 **
** 2.4.0     06-Sep-2019   HM Shin     #18909                                 **
** 2.3.0     22-Aug-2019   JS Lim      #18851                                 **
** 2.2.1     20-Mar-2017   Chan Kim    Redmine #7849                          **
** 2.2.0     01-Feb-2017   Chan Kim    Redmine #6922                          **
** 2.1.4     16-Nov-2016   Chan Kim    Redmine #6681, #6682                   **
** 2.1.1     17-Jun-2016   Chan Kim    Redmine #5490, #5632, #5680            **
** 2.1.0     17-Jun-2016   Chan Kim    Redmine #5190                          **
** 2.0.8     10-Jun-2016   Chan Kim    Redmine #5143                          **
** 2.0.3     24-Nov-2015   Chan Kim    Redmine #3545, #4519                   **
** 2.0.0     11-Aug-2015   Chan Kim    Redmine #2949                          **
** 1.0.7     10-Jun-2013   Chan Kim    Change code for release Library        **
** 1.0.0     29-Apr-2013   Autoever      Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "PduR.h"                 /* Header File */
#include "PduR_PCTypes.h"   /* PDU Router module post-build time header */
#include "SchM_PduR.h"            /* SchM header */
#include "PduR_TxUp.h"            /* PduR Transmit header */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define PDUR_TXUP_C_AR_RELEASE_MAJOR_VERSION    4
#define PDUR_TXUP_C_AR_RELEASE_MINOR_VERSION    0
#define PDUR_TXUP_C_AR_RELEASE_REVISION_VERSION 3

/* PDUR software version information */
#define PDUR_TXUP_C_SW_MAJOR_VERSION            2
#define PDUR_TXUP_C_SW_MINOR_VERSION            9
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (PDUR_PCTYPES_AR_RELEASE_MAJOR_VERSION !=\
     PDUR_TXUP_C_AR_RELEASE_MAJOR_VERSION)
#error "PduR_TxUp.c : Mismatch in Specification Major Version"
#endif

#if (PDUR_PCTYPES_AR_RELEASE_MINOR_VERSION !=\
     PDUR_TXUP_C_AR_RELEASE_MINOR_VERSION)
#error "PduR_TxUp.c : Mismatch in Specification Minor Version"
#endif

#if (PDUR_PCTYPES_AR_RELEASE_REVISION_VERSION !=\
     PDUR_TXUP_C_AR_RELEASE_REVISION_VERSION)
#error "PduR_TxUp.c : Mismatch in Specification Revision Version"
#endif

#if (PDUR_PCTYPES_SW_MAJOR_VERSION != PDUR_TXUP_C_SW_MAJOR_VERSION)
#error "PduR_TxUp.c : Mismatch in Software Major Version"
#endif

#if (PDUR_PCTYPES_SW_MINOR_VERSION != PDUR_TXUP_C_SW_MINOR_VERSION)
#error "PduR_TxUp.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_IF_TRANSMIT == STD_ON)||(PDUR_TP_TRANSMIT == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_CODE) PduR_DETCheckUpTransmit(
  PduIdType LddTxPduId, uint8 LucAPIId, uint8 LucModuleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr);

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
#endif /* End of if ((PDUR_IF_TRANSMIT == STD_ON)||
        *(PDUR_TP_TRANSMIT == STD_ON))*/
#endif /* End of if (PDUR_ZERO_COST_OPERATION == STD_ON) */

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_IF_CANCEL_TRANSMIT_SUPPORT == STD_ON) ||\
  (PDUR_TP_CANCEL_TRANSMIT_SUPPORT == STD_ON))
#if ((PDUR_IF_TRANSMIT == STD_ON)||(PDUR_TP_TRANSMIT == STD_ON))     
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_CODE) PduR_DETCheckCancelTransmit(
  PduIdType LddTxPduId, uint8 LucAPIId, uint8 LucModuleType);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
#endif
#endif


#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_TRANSMIT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_CODE) PduR_TpTransmit
(P2CONST(PduR_UpTx, AUTOMATIC, PDUR_CONST) LpUpTransmit,
P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_IF_TRANSMIT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_CODE) PduR_IfTransmit
(P2CONST(PduR_UpTx, AUTOMATIC, PDUR_CONST) LpUpTransmit,
P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
/*******************************************************************************
** Function Name        : PduR_UpTransmit                                     **
**                                                                            **
** Service ID           : 0x<UpModId>9                                        **
**                                                                            **
** Description          : Common function for PduR_ComTransmit(),             **
**                        PduR_DcmTransmit(), PduR_IpdumTransmit()            **
**                                                                            **
** Sync/Async           : Async                                               **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PduIdType LddTxPduId, uint8 LucAPIId,               **
**                        uint8 LucModuleType, PduInfoType LpPduInfoPtr       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType LenReturnVal                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_GaaUpTransmit,                                 **
**                        PduR_GulGroupMaskValue                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        PduR_DETCheckUpTransmit()                           **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_IF_TRANSMIT == STD_ON)||(PDUR_TP_TRANSMIT == STD_ON))
#define PDUR_START_SEC_CODE
#include "MemMap.h"

#if (PDUR_DEV_ERROR_DETECT == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_UpTransmit(PduIdType LddTxPduId,
  uint8 LucAPIId, uint8 LucModuleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr)
#else
FUNC(Std_ReturnType, PDUR_CODE) PduR_UpTransmit(PduIdType LddTxPduId,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr)
#endif
{
  P2CONST(PduR_UpTx, AUTOMATIC, PDUR_CONST) LpUpTransmit;

  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 LusGroupMaskValue;
  #endif

  /* Initialize LenReturnValue */
  Std_ReturnType LenReturnVal = (Std_ReturnType)E_OK;

  /* Check for the DET */
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  LenReturnVal = PduR_DETCheckUpTransmit(LddTxPduId, LucAPIId, LucModuleType,
    LpPduInfoPtr);

  /* Check whether any development errors are detected */
  if ((Std_ReturnType)E_OK == LenReturnVal)
  #endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    /* Get the group mask value */
    uint8 LucRoutingPathBitStatus = 0;
    #endif

    /* Get the pointer to LpUpTransmit from PduR_GaaUpTransmit */
    LpUpTransmit = &PduR_GaaUpTransmit[LddTxPduId];

    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    /* Get the group mask value */
    LusGroupMaskValue = LpUpTransmit->usGroupMaskValue;
     /* polyspace-begin MISRA2012:2.1 [Justified:Low] "Condition will be executed based on the configured values" */
     /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
     /* polyspace-begin MISRA-C3:14.3 [Not a defect:Low] "Condition will be executed based on the configured values" */
     /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
      if (PDUR_UNDEFINED_ROUTINGPATH_GROUP != LusGroupMaskValue)
      {
        if ((uint8)PDUR_ZERO != (PduR_GaaRoutingPathGroupRam[LusGroupMaskValue >> 3] & ((uint8)1 << (uint8)(LusGroupMaskValue % 8))))
        {
          LucRoutingPathBitStatus = (uint8)PDUR_TRUE;
        }
      }
    /* Check if routing path is enabled */    
    /* polyspace<DEFECT:USELESS_IF: Not a defect Justify with annotations:Medium> Condition will be executed based on the configured values */
    if ((PDUR_UNDEFINED_ROUTINGPATH_GROUP == LusGroupMaskValue) || (PDUR_FALSE != LucRoutingPathBitStatus))
    #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
    {

      #if(PDUR_IF_TRANSMIT == STD_ON)
      /* Check whether the transmit request if for TP or If layer */
      if((uint8)PDUR_TP_LAYER !=
                          ((LpUpTransmit->ucFraTIOrNoOfRoute) & PDUR_TP_LAYER))
      {
        LenReturnVal = PduR_IfTransmit(LpUpTransmit, LpPduInfoPtr);
      }
      else
      #endif
      {
        #if (PDUR_TP_TRANSMIT == STD_ON)
        LenReturnVal = PduR_TpTransmit(LpUpTransmit, LpPduInfoPtr);
        #endif
      }
    }
		 /* polyspace-end MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect Justify with annotations] "Condition will be executed based on the configured values" */
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    else 
    {
      LenReturnVal = (Std_ReturnType)E_NOT_OK;
    }
    #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
    /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
    /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */    
    /* polyspace-end MISRA2012:2.1 [Justified:Low] "Condition will be executed based on the configured values" */
    /* polyspace-end MISRA-C3:14.3 [Not a defect:Low] "Condition will be executed based on the configured values" */
  }
  /* Return Std Return Value*/
  return (LenReturnVal);
} /* End of PduR_UpTransmit(PduIdType LddTxPduId, P2CONST(PduInfoType,
   *AUTOMATIC, PDUR_CONST) LpPduInfoPtr) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /*  #if (PDUR_IF_TRANSMIT == STD_ON)  */
#endif /*  #if (PDUR_ZERO_COST_OPERATION == STD_OFF)  */

/*******************************************************************************
** Function Name        : PduR_DETCheckUpTransmit                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Det Check for Transmit Function called by upper     **
**                        layer                                               **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType LddTxPduId, uint8 LucApiId,               **
**                        uint8 LucModuleType, PduInfoType LpPduInfoPtr       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType LenReturnVal                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_GaaUpTransmit, PduR_GblInitStatus              **
**                        PduR_Up_MaxPduID                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_IF_TRANSMIT == STD_ON) || (PDUR_TP_TRANSMIT == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_CODE) PduR_DETCheckUpTransmit(
  PduIdType LddTxPduId, uint8 LucAPIId, uint8 LucModuleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr)
{
  P2CONST(PduR_UpTx, AUTOMATIC, PDUR_CONST) LpUpTransmit;
  /* Initialize LenReturnValue to E_OK */
  Std_ReturnType LenReturnVal = (Std_ReturnType)E_OK;
  /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  /* Check whether the module is initialised */
  if ((boolean)PDUR_UNINITIALIZED == PduR_GblInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      LucAPIId, PDUR_E_INVALID_REQUEST);
    /* Set the return value to E_NOT_OK */
    LenReturnVal = (Std_ReturnType)E_NOT_OK;
  } /* End of if (PDUR_UNINITIALIZED == PduR_GblInitStatus) */
  else
  {
    /* Get the pointer to LpComTransmit from PduR_GaaUpTransmit */
    LpUpTransmit = &PduR_GaaUpTransmit[LddTxPduId];

    #if((PDUR_IF_TRANSMIT == STD_ON)||(PDUR_TP_TRANSMIT == STD_ON))
    if (LddTxPduId >= (PduIdType)PduR_Up_MaxPduID)
    {
      /* Report to DET */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        LucAPIId, PDUR_E_PDU_ID_INVALID);
      /* Set the return value to E_NOT_OK */
      LenReturnVal = (Std_ReturnType)E_NOT_OK;
    } /* End of if (LddTxPduId >= PduR_GulUpMaxPduId) */
    else
    {
      if (LpUpTransmit->ucModuleType != LucModuleType)
      {
        /* Report to DET */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                                             LucAPIId, PDUR_E_PDU_ID_INVALID);
        /* Set the return value to E_NOT_OK */
        LenReturnVal = (Std_ReturnType)E_NOT_OK;
      } /* End of if (PduR_GaaUpTransmit[LddTxPduId].ucModuleType !=
          *LucModuleType) */
    }
    #endif
    /* Check If PduInfoPtr is NULL_PTR */
    if (NULL_PTR == LpPduInfoPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        LucAPIId, PDUR_E_NULL_POINTER);
      /* Set the return value to E_NOT_OK */
      LenReturnVal = (Std_ReturnType)E_NOT_OK;
    } /* End of if (NULL_PTR == LpPduInfoPtr) */

    /* Check If PduInfoPtr is NULL_PTR */
    else
    {
      /* polyspace +2 MISRA-C3:9.1 [Not a defect Justify with annotations:Unset] "No Action Planned, condition used to verify the pointer is NULL or not" */
      /* polyspace<MISRA-C3:D4.14 :: Not a defect Justify with annotations> No Action Planned, condition used to verify the pointer is NULL or not */
      if((NULL_PTR == LpPduInfoPtr->SduDataPtr))
      {
        /* Report to DET */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          LucAPIId, PDUR_E_NULL_POINTER);
        /* Set the return value to E_NOT_OK */
        LenReturnVal = (Std_ReturnType)E_NOT_OK;
      } /* End of if ((NULL_PTR == LpPduInfoPtr->SduDataPtr)) */
    }
  }
  /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  /* Return Std Return Value*/
  return (LenReturnVal);
} /* End of PduR_DETCheckUpTransmit(
   * PduIdType LddTxPduId, uint8 LucAPIId, uint8 LucModuleType,
   * P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr)*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /*#if (PDUR_DEV_ERROR_DETECT == STD_ON)  */
#endif /*#if (PDUR_IF_TRANSMIT == STD_ON)  */
#endif /*#if (PDUR_ZERO_COST_OPERATION == STD_ON)  */

/*******************************************************************************
** Function Name        : PduR_UpCancelTransmit                               **
**                                                                            **
** Service ID           : 0x<UpModId>a                                        **
**                                                                            **
** Description          : The PDU Router shall translate the upper layer      **
**                        into the configured target PDU ID and route this    **
**                        cancel transmit request to the configured target    **
**                        TP or IF module.                                    **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : PduIdType  LddTxPduId, uint8 LucAPIId,              **
**                        uint8 LucModuleType                                 **
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
**                        PduR_GaaTpCancellation, PduR_GaaUpTransmit,         **
**                        PduR_GulGroupMaskValue, PduR_GaaIfCancelTransmitFun **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        PduR_DETCheckIfCancelTransmit()                     **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_IF_CANCEL_TRANSMIT_SUPPORT == STD_ON) ||\
  (PDUR_TP_CANCEL_TRANSMIT_SUPPORT == STD_ON))
#define PDUR_START_SEC_CODE
#include "MemMap.h"

#if (PDUR_DEV_ERROR_DETECT == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_UpCancelTransmit(PduIdType LddTxPduId,
  uint8 LucAPIId, uint8 LucModuleType)
#else
FUNC(Std_ReturnType, PDUR_CODE) PduR_UpCancelTransmit(PduIdType LddTxPduId)
#endif
{
  #if ((PDUR_IF_TRANSMIT == STD_ON)||(PDUR_TP_TRANSMIT == STD_ON)) 
  P2CONST(PduR_UpTx, AUTOMATIC, PDUR_CONST) LpUpTransmit;

  #if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON)
  P2CONST(PduR_MulticastTpPdu, AUTOMATIC, PDUR_CONST) LpMulticastTpPdu;
  #endif
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 LusGroupMaskValue;
  #endif

  #endif
  /* Return value of the function */
  Std_ReturnType LddReturnVal = (Std_ReturnType)E_OK;

  #if ((PDUR_IF_TRANSMIT == STD_ON)||(PDUR_TP_TRANSMIT == STD_ON)) 
  /* Set return value to E_OK */
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  LddReturnVal = PduR_DETCheckCancelTransmit(LddTxPduId, LucAPIId,
    LucModuleType);

  /* Check whether any development errors are detected */
  if ((Std_ReturnType)E_OK == LddReturnVal)
  #endif /* #if(PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    uint8 LucRoutingPathBitStatus = 0;
    #endif
    /* Get the pointer to LpUpTransmit from PduR_GaaTpTransmit */
    LpUpTransmit = &PduR_GaaUpTransmit[LddTxPduId];

    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    LusGroupMaskValue = LpUpTransmit->usGroupMaskValue;
    /* polyspace-begin MISRA2012:2.1 [Justified:Low] "Condition will be executed based on the configured values" */
    /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
    /* polyspace-begin MISRA-C3:14.3, DEFECT:USELESS_IF [Not a defect Justify with annotations] "Condition will be executed based on the configured values" */
    /* polyspace-begin DEFECT:USELESS_IF [Not a defect:Low] "Condition will be executed based on the configured values" */
    /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
      if (PDUR_UNDEFINED_ROUTINGPATH_GROUP != LusGroupMaskValue)
      {
        if ((uint8)PDUR_ZERO != (PduR_GaaRoutingPathGroupRam[LusGroupMaskValue >> 3] & ((uint8)1 << (uint8)(LusGroupMaskValue % 8))))
        {
          LucRoutingPathBitStatus = (uint8)PDUR_TRUE;
        }
      }

    /* Check if routing path is enabled */
    if ((PDUR_UNDEFINED_ROUTINGPATH_GROUP == LusGroupMaskValue) || (PDUR_FALSE != LucRoutingPathBitStatus))
    #endif
    {
      #if(PDUR_IF_TRANSMIT == STD_ON)
      if((uint8)PDUR_TP_LAYER !=
                           ((LpUpTransmit->ucFraTIOrNoOfRoute) & PDUR_TP_LAYER))
      {
        /* Check if Multicast */
        #if (PDUR_IF_CANCEL_TRANSMIT_SUPPORT == STD_ON)
        #if (PDUR_MULTICAST_TOTXIF_SUPPORT == STD_ON)
        if ((uint8)PDUR_MULTICAST_MASK ==
            ((LpUpTransmit->ucFraTIOrNoOfRoute) & ((uint8)PDUR_MULTICAST_MASK)))
        {
          P2CONST(PduR_MulticastTxPdu, AUTOMATIC, PDUR_CONST) LpMulticastTxPdu;
          uint8 LucNoOfRoutePdu;
          /* Assign LddReturnVal with E_OK */
          LddReturnVal = (Std_ReturnType)E_OK;
          LpMulticastTxPdu =
                           (P2CONST(PduR_MulticastTxPdu, AUTOMATIC, PDUR_CONST))
                             (LpUpTransmit->pMulticastTpOrTxPdu);

          /* Get the pointer to LucNoOfRoutePdu from PduR_UpTransmit */
          LucNoOfRoutePdu =
           (uint8)((LpUpTransmit->ucFraTIOrNoOfRoute) & PDUR_TARGET_INDEX_MASK);

          /* Loop for all the destinations in case of multicast */
          do
          {
            #if(PDUR_TOTAL_COUNT_IF_CANCEL_TRANSMIT > PDUR_ZERO)
            /* Invoke Cancel transmit function */
            if(PduR_GaaIfCancelTransmitService[LpMulticastTxPdu->ucTargetIndex].
              pTargetLayer != NULL_PTR)
            {
              LddReturnVal = LddReturnVal |
                PduR_GaaIfCancelTransmitService[LpMulticastTxPdu->ucTargetIndex].
                pTargetLayer(LpMulticastTxPdu->ddTargetPduId);
            }
            else
            #endif
            {
              LddReturnVal = LddReturnVal | (Std_ReturnType)E_NOT_OK;
            }

            /* Get the next LpMulticastTxPdu */
            LpMulticastTxPdu++;

            /* Decrement the counter */
            LucNoOfRoutePdu--;
          }while(LucNoOfRoutePdu != (uint8)PDUR_ZERO);

        } /* Multicast Transmission */
        else
        #endif /* #if (PDUR_MULTICAST_TOTXIF_SUPPORT == STD_ON) */
        {
          #if(PDUR_TOTAL_COUNT_IF_CANCEL_TRANSMIT > PDUR_ZERO)
          /* Invoke Cancel transmit function */
          if(PduR_GaaIfCancelTransmitService[LpUpTransmit->ucFraTIOrNoOfRoute
                              & (uint8)PDUR_TARGET_INDEX_MASK].pTargetLayer 
                              != NULL_PTR)
          {
            LddReturnVal =
              PduR_GaaIfCancelTransmitService[LpUpTransmit->ucFraTIOrNoOfRoute
                                  & (uint8)PDUR_TARGET_INDEX_MASK].pTargetLayer
                                  (LpUpTransmit->ddLoTargetPduId);
          }
          else
          #endif
          {
            LddReturnVal = (Std_ReturnType)E_NOT_OK;
          }
        } /* End of else */
        #endif /*#if ((PDUR_IF_CANCEL_TRANSMIT_SUPPORT == STD_ON)*/
      }
      else
      #endif
      {
        #if(PDUR_TP_TRANSMIT == STD_ON)
        #if(PDUR_TP_CANCEL_TRANSMIT_SUPPORT == STD_ON)
        #if(PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON)
        if ((uint8)PDUR_MULTICAST_MASK ==
            ((LpUpTransmit->ucFraTIOrNoOfRoute) & ((uint8)PDUR_MULTICAST_MASK)))
        {
          uint8 LucNoOfRoutePdu;
          /* Get the pointer to pMulticastPdu from PduR_UpTransmit */
          LpMulticastTpPdu =
                           (P2CONST(PduR_MulticastTpPdu, AUTOMATIC, PDUR_CONST))
                             (LpUpTransmit->pMulticastTpOrTxPdu);
          /* Get the pointer to LucNoOfRoutePdu from PduR_UpTransmit */
          LucNoOfRoutePdu =
           (uint8)((LpUpTransmit->ucFraTIOrNoOfRoute) & PDUR_TARGET_INDEX_MASK);
          /* Assign LddReturnVal with E_OK */
          LddReturnVal = (Std_ReturnType)E_OK;
          /* Loop for all the destinations in case of multicast */
          do
          {
            #if (PDUR_TOTAL_COUNT_TP_CANCEL_TRANSMIT_ENABLED > PDUR_ZERO)
            /* Invoke Cancel transmit frunction */
            if(PduR_GaaTpCancellation[LpMulticastTpPdu->ucTargetIndex]
              .pTargetLayer != NULL_PTR)
            {
              LddReturnVal = LddReturnVal |
              PduR_GaaTpCancellation[LpMulticastTpPdu->ucTargetIndex]
              .pTargetLayer(LpMulticastTpPdu->ddTargetPduId);
            }
            else
            #endif
            {
              LddReturnVal = LddReturnVal | (Std_ReturnType)E_NOT_OK;
            }

            LucNoOfRoutePdu--;

            /* Get the next LpMulticastTpPdu */
            LpMulticastTpPdu++;
          }while ((uint8)PDUR_ZERO != LucNoOfRoutePdu);

        } /* Multicast Transmission */
        else
        #endif /* #if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON) */
        {
          #if (PDUR_TOTAL_COUNT_TP_CANCEL_TRANSMIT_ENABLED > PDUR_ZERO)
          /* Invoke Cancel transmit frunction */
          if(PduR_GaaTpCancellation[LpUpTransmit->ucFraTIOrNoOfRoute
                         &(uint8)PDUR_TARGET_INDEX_MASK].pTargetLayer != 
                         NULL_PTR)
          {
            LddReturnVal = PduR_GaaTpCancellation
                           [LpUpTransmit->ucFraTIOrNoOfRoute
                           &(uint8)PDUR_TARGET_INDEX_MASK].pTargetLayer
                           (LpUpTransmit->ddLoTargetPduId);
          }
          else
          #endif
          {
            LddReturnVal = (Std_ReturnType)E_NOT_OK;
          }
        } /* End of else */
        #endif /*#if(PDUR_TP_CANCEL_TRANSMIT_SUPPORT == STD_ON)*/
        #endif
      }
    }    
    /* Requirement PDUR0710 */
    /* If the routing path for the requested I-PDU is disabled, then
     PduR_UpCancelTransmit shall return E_NOT_OK directly without any
     further action */
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    else
    {
      LddReturnVal = (Std_ReturnType)E_NOT_OK;
    }
    #endif
    /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
    /* polyspace-end DEFECT:USELESS_IF [Not a defect:Low] "Condition will be executed based on the configured values" */
    /* polyspace-end MISRA2012:2.1 [Justified:Low] "Condition will be executed based on the configured values" */
    /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
    /* polyspace-end MISRA-C3:14.3, DEFECT:USELESS_IF [Not a defect Justify with annotations] "Condition will be executed based on the configured values" */
  }
  #endif
  /* Return Std Return Value*/
  return (LddReturnVal);
} /* End of PduR_IfCancelTransmit(PduIdType LddTxPduId) */

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : PduR_DETCheckCancelTransmit                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The PDU Router shall translate the upper layer      **
**                        into the configured target PDU ID and route this    **
**                        cancel transmit request to the configured target    **
**                        TP module.                                          **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType  LddTxPduId, uint8 LucAPIId,              **
**                        uint8 LucModuleType                                 **
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
**                        PduR_GblInitStatus, PduR_GaaUpTransmit              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_IF_CANCEL_TRANSMIT_SUPPORT == STD_ON) ||\
  (PDUR_TP_CANCEL_TRANSMIT_SUPPORT == STD_ON))
#if ((PDUR_IF_TRANSMIT == STD_ON)||(PDUR_TP_TRANSMIT == STD_ON))  
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
/*As per MISRA-C3:8.13 Change extern to static function  */
 static FUNC(Std_ReturnType, PDUR_CODE) PduR_DETCheckCancelTransmit(
  PduIdType LddTxPduId, uint8 LucAPIId, uint8 LucModuleType)
{
  P2CONST(PduR_UpTx, AUTOMATIC, PDUR_CONST) LpUpTx;
  /* Initialize LenReturnValue to E_OK */
  Std_ReturnType LddReturnVal;
  /* Set return value to E_OK */
  LddReturnVal = (Std_ReturnType)E_OK;
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
    LpUpTx = &PduR_GaaUpTransmit[LddTxPduId];
    #if((PDUR_IF_TRANSMIT == STD_ON)||(PDUR_TP_TRANSMIT == STD_ON))
    if (LddTxPduId >= (PduIdType)PduR_Up_MaxPduID)
    {
      /* Report to DET */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        LucAPIId, PDUR_E_PDU_ID_INVALID);
      /* Set the return value to E_NOT_OK */
      LddReturnVal = (Std_ReturnType)E_NOT_OK;
    } /* End of if (LddTxPduId >= PduR_GulUpMaxPduId) */
    else
    {
      if (LpUpTx->ucModuleType != LucModuleType)
      {
        /* Report to DET */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          LucAPIId, PDUR_E_PDU_ID_INVALID);
        /* Set the return value to E_NOT_OK */
        LddReturnVal = (Std_ReturnType)E_NOT_OK;
      } /* End of if (PduR_GaaUpTransmit[LddTxPduId].ucModuleType !=
       *LucModuleType) */
    } /* Return Std Return Value*/
    #endif
  } /* Return Std Return Value*/
  return (LddReturnVal);
} /* End Of PduR_DETCheckIfCancelTransmit(
   * PduIdType LddTxPduId, uint8 LucAPIId, uint8 LucModuleType)*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
#endif
#endif

/*******************************************************************************
** Function Name        : PduR_IfTransmit                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The PDU Router shall translate the upper layer      **
**                        into the configured target PDU ID and route this    **
**                        cancel transmit request to the configured target    **
**                        IF layer module.                                    **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : PduInfoType LpPduInfoPtr                            **
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
**                        PduR_GaaIfTransmitService, PduR_GulGroupMaskValue   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_IF_TRANSMIT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_CODE) PduR_IfTransmit(
P2CONST(PduR_UpTx, AUTOMATIC, PDUR_CONST) LpUpTransmit,
P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr)
{
  #if (PDUR_MULTICAST_TOTXIF_SUPPORT == STD_ON)
  P2CONST(PduR_MulticastTxPdu, AUTOMATIC, PDUR_CONST) LpMulticastTxPdu;
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 LusGroupMaskValue;
  #endif
  #endif
  Std_ReturnType LenReturnVal;
  #if (PDUR_MULTICAST_TOTXIF_SUPPORT == STD_ON)
  uint8 LucNoOfRoutePdu;
  #endif
  #if (PDUR_MULTICAST_TOTXIF_SUPPORT == STD_ON)
  /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  if ((uint8)PDUR_MULTICAST_MASK ==
          ((LpUpTransmit->ucFraTIOrNoOfRoute) & ((uint8)PDUR_MULTICAST_MASK)))
  {
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    uint8 LucRoutingPathBitStatus = 0;
    #endif
    
    /* Initialize LenReturnValue to E_OK */
    LenReturnVal = (Std_ReturnType)E_NOT_OK;
    /* Get pMulticastTxPdu to local pointer */
    LpMulticastTxPdu = (P2CONST(PduR_MulticastTxPdu, AUTOMATIC, PDUR_CONST))
                          (LpUpTransmit->pMulticastTpOrTxPdu);
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    /* Get the group mask value */
    LusGroupMaskValue = LpMulticastTxPdu->usGroupMaskValue;

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
      /* Get the local variable to ucNoOfRoutePdu */
      LucNoOfRoutePdu = (uint8)((LpUpTransmit->ucFraTIOrNoOfRoute) &
                        PDUR_TARGET_INDEX_MASK);
      #if (PDUR_LO_TXCONFIRMATION == STD_ON)
      /* Check if confirmations are configured */
      if ((uint8)PDUR_ZERO != (LpUpTransmit->ucTxConfirmMask))
      {
        /* Load No Of confirmations count */ /*@Alert Schm*/
        (*(LpUpTransmit->pRamArea)) |= LpUpTransmit->ucTxConfirmMask;
      } /* End of if (PDUR_ZERO != LpUpTransmit->ucTxConfirmMask) */
      #endif /* End of if (PDUR_LO_TXCONFIRMATION == STD_ON) */
      /* Multicast Transmission */
      do
      {
        /* Invoke <Lo>IfTransmit API with TargePduId and LpPduInfoPtr */
        if(PduR_GaaIfTransmitService[LpMulticastTxPdu->ucTargetIndex].pTargetLayer 
        != NULL_PTR)
        {
          LenReturnVal = LenReturnVal &
                      PduR_GaaIfTransmitService[LpMulticastTxPdu->ucTargetIndex].
                    pTargetLayer(LpMulticastTxPdu->ddTargetPduId, LpPduInfoPtr);
        }
        else
        {
          LenReturnVal = LenReturnVal & (Std_ReturnType)E_NOT_OK;
        }

        /* Get the pointer to next Tx Pdu */
        LpMulticastTxPdu++;

        LucNoOfRoutePdu--;

        /* Check whether NoOfRoutePdu is not equal to zero */
      }while(LucNoOfRoutePdu != (uint8)PDUR_ZERO);
    }
  }
  else
  #endif /* #if (PDUR_MULTICAST_TOTXIF_SUPPORT == STD_ON) */
  /* Singlecast Transmission */
  {
    /* Invoke <Lo>IfTransmit API with TargePduId and LpPduInfoPtr */
    if(PduR_GaaIfTransmitService[(LpUpTransmit->ucFraTIOrNoOfRoute) & PDUR_TARGET_INDEX_MASK].pTargetLayer != 
    NULL_PTR)
    {
      LenReturnVal =
        PduR_GaaIfTransmitService[(LpUpTransmit->ucFraTIOrNoOfRoute) & PDUR_TARGET_INDEX_MASK].
        pTargetLayer(LpUpTransmit->ddLoTargetPduId, LpPduInfoPtr);
    }
    else
    {
      LenReturnVal = (Std_ReturnType)E_NOT_OK;
    }
  }
  /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  /* Return Std Return Value*/
  return (LenReturnVal);
} /* End of PduR_IfCancelTransmit(PduIdType LddTxPduId) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : PduR_TpTransmit                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The PDU Router shall translate the upper layer      **
**                        into the configured target PDU ID and route this    **
**                        cancel transmit request to the configured target    **
**                        Tp layer module.                                    **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : PduInfoType  LpPduInfoPtr                           **
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
**                        PduR_GaaTpTransmitService, PduR_GulGroupMaskValue   **
**                                                                            **
**                        Function(s) invoked    : None                       **
**                        SchM_Enter_PduR_TP_TX_PROTECTION_AREA(),            **
**                        SchM_Exit_PduR_TP_TX_PROTECTION_AREA(),             ** 
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_TRANSMIT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_CODE) PduR_TpTransmit
(P2CONST(PduR_UpTx, AUTOMATIC, PDUR_CONST) LpUpTransmit,
P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr)
{
  #if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON)
  P2CONST(PduR_MulticastTpPdu, AUTOMATIC, PDUR_CONST) LpMulticastTpPdu;
  P2VAR(PduR_MulticastTpInfo, AUTOMATIC, PDUR_VAR) LpMulticastTpInfo;
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 LusGroupMaskValue;
  #endif
  #endif
  Std_ReturnType LenReturnVal;
  #if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON)
  uint8 LucNoOfRoutePdu;
  #endif
  #if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON)
  /* polyspace-begin RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  /* Check if multicast transmission */
  if ((uint8)PDUR_MULTICAST_MASK ==
            ((LpUpTransmit->ucFraTIOrNoOfRoute) & ((uint8)PDUR_MULTICAST_MASK)))
  {
    /* Get the pointer to pMulticastTpPdu from PduR_UpTransmit */
    LpMulticastTpPdu = (P2CONST(PduR_MulticastTpPdu, AUTOMATIC, PDUR_CONST))
                                          (LpUpTransmit->pMulticastTpOrTxPdu);

    /* Assign LenReturnVal with E_OK */
    LenReturnVal = (Std_ReturnType)E_NOT_OK;
    if(LpMulticastTpPdu != NULL_PTR)
    {
      #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
      uint8 LucRoutingPathBitStatus = 0;
      /* Get the group mask value */
      LusGroupMaskValue = LpMulticastTpPdu->usGroupMaskValue;
      
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
        /*Get the pointer to pMulticastTpInfo from PduR_MulticastTpPdu*/
        LpMulticastTpInfo = (LpMulticastTpPdu->pMulticastTpInfo);
        /* Get the number of routing path */
        LucNoOfRoutePdu =
            (uint8)((LpUpTransmit->ucFraTIOrNoOfRoute) & PDUR_TARGET_INDEX_MASK);
        /* Disable relevant interrupts */
        SchM_Enter_PduR_TP_TX_PROTECTION_AREA();
        /* Set the mask for Transmit status bit based on Tp Module */
        LpMulticastTpInfo->ucConfStatus = LpMulticastTpInfo->ucConfStatus|
          LpUpTransmit->ucTxConfirmMask;
        /* Store the result as Buffer OK */
        LpMulticastTpInfo->ddResult = (NotifResultType)NTFRSLT_E_NOT_OK;
        /* Enable relevant interrupts */
        SchM_Exit_PduR_TP_TX_PROTECTION_AREA();

        /* Multicast Transmission */
        do
        {
          #if (PDUR_TOTAL_COUNT_TP_TRANSMIT > PDUR_ZERO)	  
          /* Invoke <Lo>TpTransmit API with TargePduId and PduInfoPtr */
          if(PduR_GaaTpTransmitService[LpMulticastTpPdu->ucTargetIndex].pTargetLayer 
          != NULL_PTR)
          {
            LenReturnVal = LenReturnVal &
              PduR_GaaTpTransmitService[LpMulticastTpPdu->ucTargetIndex].
              pTargetLayer(LpMulticastTpPdu->ddTargetPduId, LpPduInfoPtr);
          }
          else
          #endif			
          {
            LenReturnVal = LenReturnVal & (Std_ReturnType)E_NOT_OK;
          }

          /* Get the next LpMulticastTpPdu */
          LpMulticastTpPdu++;
          /* MISRA Rule   : 17.4.
          *   Message      : Increment or decrement operation
          *                  performed on the pointer
          *   Reason       : Increment operator used
          *                  to achieve better throughput.
          *   Verification : However, part of the code
          *                  is verified manually and
          *                  it is not having any impact.
          */
          /* Decrement the counter by one count */
          LucNoOfRoutePdu--;
        /* Check whether NoOfRoutePdu is not equal to zero */
        }while ((uint8)PDUR_ZERO != LucNoOfRoutePdu);
      }
    }
  }
  else
  #endif /* #if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON) */
    /* Singlecast Transmission */
  {
    #if (PDUR_TOTAL_COUNT_TP_TRANSMIT > PDUR_ZERO)
    /* Invoke Tp transmit function */
    if(PduR_GaaTpTransmitService[LpUpTransmit->ucFraTIOrNoOfRoute &
                            (uint8)PDUR_TARGET_INDEX_MASK].pTargetLayer != 
                            NULL_PTR)
    {
      LenReturnVal =
        PduR_GaaTpTransmitService[LpUpTransmit->ucFraTIOrNoOfRoute &
                              (uint8)PDUR_TARGET_INDEX_MASK].pTargetLayer
          (LpUpTransmit->ddLoTargetPduId, LpPduInfoPtr);
    }
    else
    #endif	
    {
      LenReturnVal = (Std_ReturnType)E_NOT_OK;
    }
  }
  /* polyspace-end RTE:UNR [Not a defect:No action planned] "No problem. Unreachable code" */
  /* Return Std Return Value*/
  return (LenReturnVal);
} /* End of PduR_IfCancelTransmit(PduIdType LddTxPduId) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
