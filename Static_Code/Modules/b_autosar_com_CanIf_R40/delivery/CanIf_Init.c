/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanIf_Init.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Provision of Initialization and version control functionality **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
*******************************************************************************/
/*******************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 3.0.0    08-Nov-2021    Sj.Kim    #32882                                   **
** 2.7.2    12-Jan-2021    Sj.Kim    #27560                                   **
** 2.7.1    25-Nov-2020    Sj.Kim    #26002                                   **
** 2.7.0    07-Oct-2020    Sj.Kim    #25877                                   **
** 2.6.2    15-May-2020    Sj.Kim    #23352, #21882, #23360                   **
** 2.6.0    22-Aug-2019    Js.Lim    #18384                                   **
** 2.5.8    10-Jul-2019    Js.Lim    #18347                                   **
** 2.5.5    10-Jan-2018    Js.Lim    #10934                                   **
** 2.5.1    23-Mar-2017    Js.Lim    #7042                                    **
** 2.5.0    06-Dec-2016    Js.Lim    #6745, #7077                             **
** 2.2.4    05-Mar-2016    Kt.Kim    #4317                                    **
** 2.2.3    05-Jan-2016    Kt.Kim    #3813                                    **
** 2.2.2    16-Dec-2015    Kt.Kim    Code fix for MISRA 14.2                  **
** 2.2.1    13-Jun-2015    Kt.Kim     Improvement #2724                       **
** 2.2.0    02-Jul-2013    Kt.Kim     Type changed ucNumOfTxQueue ->          **
**                                      ddNumOfTxQueue                        **
**                                    Defect is removed                       **
** 2.1.0    30-May-2013    Kt.Kim     Lib-Build Support                       **
** 1.0.0    28-Mar-2013    Kt.Kim     Initial Version                         **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf.h"               /* Module header file */
#include "CanIf_Ram.h"           /* Module RAM header file */
#include "CanIf_PCTypes.h"       /* Pre-compile time header file */
#include "CanIf_Init.h"          /* Initialization header */
#include "CanIf_Tx.h"            /* Tx Interface header file */
#include "SchM_CanIf.h"          /* SchM CanIf Header file */
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#include "CanIf_Error.h"         /* Module DET header file */
#endif
#if (STD_ON == CANIF_VERSION_INFO_API)
#include "CanIf_Version.h"       /* Module Version header file */
#endif
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANIF_INIT_C_AR_RELEASE_MAJOR_VERSION    4
#define CANIF_INIT_C_AR_RELEASE_MINOR_VERSION    0
#define CANIF_INIT_C_AR_RELEASE_REVISION_VERSION 3

/* File version information */
#define CANIF_INIT_C_SW_MAJOR_VERSION    3
#define CANIF_INIT_C_SW_MINOR_VERSION    0

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANIF_INIT_AR_RELEASE_MAJOR_VERSION != \
  CANIF_INIT_C_AR_RELEASE_MAJOR_VERSION)
  #error "CANIF_INIT.c : Mismatch in Specification Major Version"
#endif
#if (CANIF_INIT_AR_RELEASE_MINOR_VERSION != \
  CANIF_INIT_C_AR_RELEASE_MINOR_VERSION)
  #error "CANIF_INIT.c : Mismatch in Specification Minor Version"
#endif
#if (CANIF_INIT_AR_RELEASE_REVISION_VERSION != \
  CANIF_INIT_C_AR_RELEASE_REVISION_VERSION)
  #error "CANIF_INIT.c : Mismatch in Specification Revision Version"
#endif
#if (CANIF_INIT_SW_MAJOR_VERSION != CANIF_INIT_C_SW_MAJOR_VERSION)
  #error "CANIF_INIT.c : Mismatch in Software Major Version"
#endif
#if (CANIF_INIT_SW_MINOR_VERSION != CANIF_INIT_C_SW_MINOR_VERSION)
  #error "CANIF_INIT.c : Mismatch in Software Minor Version"
#endif
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : CanIf_Init                                          **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This service Initializes internal and external      **
**                        interfaces of the CAN Interface for the further     **
**                        processing.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : ConfigPtr                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):  CanIf_GblCanIfStatus           **
**                                             CanIf_GaaController,           **
**                                             CanIf_GaaHrhInit               **
**                                             CanIf_GaaHrhArrayId            **
**                                             CanIf_GaaHrhOffSetId           **
**                                             CanIf_GaaOperMode              **
**                                             CanIf_GaaTrcvMode              **
**                                             CanIf_GaaTxQueue               **
**                        Function(s) invoked: SchM_Enter_CanIf_TX_QUEUE_     **
**                                             PROTECTION                     **
**                                             SchM_Exit_CanIf_TX_QUEUE_      **
**                                             PROTECTION                     **
**                                             CanIf_ClearTxQueue             **
**                                                                            **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANIF_CODE) CanIf_Init (P2CONST(CanIf_ConfigType, AUTOMATIC,
                                                    CANIF_APPL_CONST) ConfigPtr)
{
  /* Improvement #7042 - Delete */

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
  P2CONST(CanIf_HrhInit, AUTOMATIC, CANIF_CONST) LpHrhInit;
  #endif
  #endif

  #if (CANIF_ONE < CANIF_NO_OF_CONTROLLER)
  P2VAR(CanIf_Controller, AUTOMATIC, CANIF_VAR)LpController;
  #endif

  /* Improvement #7042 - Delete */

  VAR(uint16, CANIF_VAR) LusCount;
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT) 
  VAR(CanIf_ConfigType, CANIF_VAR) Select_variant;
  if (NULL_PTR == ConfigPtr)
  {
    #if (STD_ON == CANIF_DEV_ERROR_DETECT)
    /* report to Det */
    (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, 
                                     CANIF_INIT_SID,CANIF_E_PARAM_POINTER); 
    #endif                                 
  } 
  else
  {
    /* init postbuild variable */
    Select_variant = *ConfigPtr; 

    /* Get CanIf Config from selected variant */
    CanIf_GaaControllerConfigTypeSelect = Select_variant.pCanIfGaaControllerConfigType;

    /* Get Rx L-PDU from selected variant */
    CanIf_GaaRxLpduSelect = Select_variant.pCanIfGaaRxLpdu;

    /* Get Tx L-PDU from selected variant */
    CanIf_GaaTxLpduSelect = Select_variant.pCanIfGaaTxLpdu;

  #else /* #if (STD_ON == CANIF_VARIANT_POSTBUID_SUPPORT) */
  {
    /* polyspace-begin RTE:UNR [Not a defect:Justified] "Condition will be executed based on the configured values" */
    CANIF_UNUSED_PTR(ConfigPtr);
    /* polyspace-end RTE:UNR [Not a defect:Justified] "Condition will be executed based on the configured values" */
  #endif /* #if (STD_ON == CANIF_VARIANT_POSTBUID_SUPPORT) */

    #if (CANIF_ONE == CANIF_NO_OF_CONTROLLER)
    /* Put the Controller Mode to Stopped State */
    /* polyspace<RTE: IDP : Not a defect : No Action Planned >
      Its boundary is pre-defined */
    CanIf_GaaController[CANIF_ZERO].ucControllerMode = (uint8)CANIF_CS_STOPPED;
    /* Clear Rx Status */
    CanIf_GaaController[CANIF_ZERO].ucRxStatus = CANIF_RX_DISABLED;
    /* Clear Tx Status */
    CanIf_GaaController[CANIF_ZERO].ucTxStatus = CANIF_TX_DISABLED;

    #if(CANIF_BUSLOAD_DETECTING_SUPPORT == STD_ON)
    CanIf_GaaTxMsgCnt[CANIF_ZERO] = CANIF_ZERO;
    CanIf_GaaRxMsgCnt[CANIF_ZERO] = CANIF_ZERO;
    #endif

    #else
    /* Get the pointer to first Controller */
    LpController =  &CanIf_GaaController[CANIF_ZERO];
    /* Get the number of Controllers into local variable */
    LusCount = (uint16)CANIF_NO_OF_CONTROLLER;
    /* polyspace-begin RTE:UNR [Not a defect:Justified] "Condition will be executed based on the configured values" */
    /* polyspace-begin DEFECT:USELESS_IF [Not a defect:Medium] "The value is generated by Generator." */
    /* polyspace +1 MISRA-C3:14.3 [Not a defect:Low] "The value is generated by Generator." */
    if(LusCount > 0)
    /* polyspace-end DEFECT:USELESS_IF [Not a defect:Medium] "The value is generated by Generator." */
    {
      do
      {
        /* Put the Controller Mode to Stopped State */
        /* polyspace<RTE: IDP : Not a defect : No Action Planned >
          Its boundary is pre-defined           */
        LpController->ucControllerMode = (uint8)CANIF_CS_STOPPED;
        /* Clear Rx Status */
        LpController->ucRxStatus = CANIF_RX_DISABLED;
        /* Clear Tx Status */
        LpController->ucTxStatus = CANIF_TX_DISABLED;
        /* Increment LpController Index by one */
        /*  polyspace<MISRA-C:17.4:Not a defect:Justify with annotations> Array Indexing is not used to achieve better throughput. */
        LpController++;

        #if(CANIF_BUSLOAD_DETECTING_SUPPORT == STD_ON)
        CanIf_GaaTxMsgCnt[LusCount - 1] = CANIF_ZERO;
        CanIf_GaaRxMsgCnt[LusCount - 1] = CANIF_ZERO;
        #endif

        /* Decrement the LusCount by one */
        LusCount--;
      }while((uint16)CANIF_ZERO != LusCount);
    }else{
    /* Do Nothing */
    }
    /* polyspace-end RTE:UNR [Not a defect:Justified] "Condition will be executed based on the configured values" */
    #endif/*#if (CANIF_ONE == CANIF_NO_OF_CONTROLLER) */
    #if (STD_ON == CANIF_DEV_ERROR_DETECT)
    #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
    /* Get the pointer to Hrh Init structure */
    LpHrhInit = &CanIf_GaaHrhInit[CANIF_NO_OF_CANDRIVER - (uint8)CANIF_ONE];
    /* Get the number of CAN Drivers*/
    LusCount = (uint16)CANIF_NO_OF_CANDRIVER;
    do
    {
      LusCount--;
      /* Get the number of Hrh of the Controller */
      /* #10934 */
      CanIf_GaaHrhArrayId[LusCount] = (LpHrhInit->usMaxHrhId);
      /* Get the HrhOffset Id of the Controller */
      CanIf_GaaHrhOffSetId[LusCount] = (LpHrhInit->ucHrhOffSetId);
      /* MISRA Rule    : 17.4
        Message       : Increment or decrement v performed on
                        pointer.
        Reason        : Increment operator used to achieve better throughput.
        Verification  : However, part of the code is verified manually and it
                        is not having any impact.
      */
      /* Increment the pointer of HrhInit structure */
      LpHrhInit--;

    }while((uint16)CANIF_ZERO != LusCount);
    #else
    /* Get the number of Hrh of the Controller */
    /* #10934 */
    /* polyspace +2 MISRA-C3:18.1 [Not a defect:Justified] "range is pre-defined" */
    /* polyspace<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
    CanIf_GaaHrhArrayId[CANIF_ZERO] = (CanIf_GaaHrhInit[CANIF_ZERO].usMaxHrhId);
    #endif/*#if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)*/
    #endif/*#if (STD_ON == CANIF_DEV_ERROR_DETECT*/

    #if ((STD_ON == CANIF_CANTRCV_SUPPORT) && (STD_ON == CANIF_DEV_ERROR_DETECT))
    #if (CANIF_ONE == CANIF_NO_OF_TRANSCEIVER)
    /* Set the Transceiver state to CANIF_TRCV_E_TRCV_NOT_STANDBY */
    /* polyspace<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
    CanIf_GaaOperMode[CANIF_ZERO] = (uint8)CANTRCV_TRCVMODE_STANDBY;
    #else
    /* Get the number of Transceivers into local variable */
    LusCount = (uint16)CANIF_NO_OF_TRANSCEIVER;
    do
    {
      /* Decrement the number of Transceivers */
      LusCount--;
      /* Set the Transceiver state to CANIF_TRCV_E_TRCV_NOT_STANDBY */
      CanIf_GaaOperMode[LusCount] = (uint8)CANTRCV_TRCVMODE_STANDBY;
    }while((uint16)CANIF_ZERO != LusCount);
    #endif/*#if (CANIF_ONE == CANIF_NO_OF_TRANSCEIVER)*/
    #endif/*#if ((STD_ON == CANIF_CANTRCV_SUPPORT) && (...))*/

    #if (STD_ON == CANIF_DEV_ERROR_DETECT)
    /* Change the CAN Interface Global status to "initialised" */
    CanIf_GblCanIfStatus = (boolean)CANIF_INITIALISED;
    #endif
    #if (STD_ON == CANIF_TX_LPDU)
    /* polyspace-begin RTE:UNR [Not a defect:Justified] "Condition will be executed based on the configured values" */
    /* polyspace-begin DEFECT:USELESS_IF [Not a defect:Medium] "The value is generated by Generator." */
    /* polyspace +1 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
    if(STD_ON == CanIf_GddPrecompOpt.ucTxBasicCanPdu)
    /* polyspace-end DEFECT:USELESS_IF [Not a defect:Medium] "The value is generated by Generator." */
    {
      /* Disabling relevant interrupts*/
      SchM_Enter_CanIf_TX_QUEUE_PROTECTION();

      for(LusCount = (uint16)CANIF_ZERO;
                  LusCount < CanIf_GddPrecompOpt.ddNumOfTxQueue; LusCount++)
      {
        CanIf_GddTxBuffCon.pTxQueue[LusCount].ucDlc = (uint8)CANIF_ZERO;
        CanIf_GddTxBuffCon.pTxQueue[LusCount].pTxNextQueue = NULL_PTR;

      }
      for(LusCount = (uint16)CANIF_ZERO;
                  LusCount < CanIf_GddPrecompOpt.ddNumOfTxBasicPdu; LusCount++)
      {
        CanIf_GddTxBuffCon.pTxPduToQueueMapping[LusCount] =
                                      (CanIf_TxPduIdType)CANIF_INVALID_TXQUEUE;
      }
      for(LusCount = (uint16)CANIF_ZERO;
                  LusCount < CanIf_GddPrecompOpt.ddNumOfTxBuffer; LusCount++)
      {
        *(CanIf_GddTxBuffCon.pTxBuffer[LusCount].pTxFirstQueue) = NULL_PTR;
      }
      /* Enabling relevant interrupts */
      SchM_Exit_CanIf_TX_QUEUE_PROTECTION();
    }
    /* polyspace-end RTE:UNR [Not a defect:Justified] "Condition will be executed based on the configured values" */

    for(LusCount = CANIF_ZERO; LusCount < CanIf_GddPrecompOpt.ddNumOfTxPdu ; LusCount++)
    {
      /* polyspace<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
      CanIf_GaaTxPduGwStatus[LusCount] = CANIF_GW_NOREQUEST;
    }
    #endif
    #if (STD_ON == CANIF_CANTRCV_SUPPORT)
    LusCount = (uint16)CANIF_ZERO;
    do
    {
      /* Set the mode for CanTrCv */
      /* polyspace<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
      CanIf_GaaTrcvMode[LusCount] = CANIF_TRCV_INIT_MODE;
      /* increment the count */
      LusCount++;
    }while(LusCount != (uint16)CANIF_NO_OF_TRANSCEIVER);
    #endif
  }
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_GetVersionInfo                                **
**                                                                            **
** Service ID           : 0x0b                                                **
**                                                                            **
** Description          : This service returns the version information of     **
**                        CanIf module.                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : VersionInfo                                         **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):  CanIf_GblCanIfStatus           **
**                                                                            **
**                        Function(s) invoked: None                           **
**                                                                            **
*******************************************************************************/
#if (STD_ON == CANIF_VERSION_INFO_API)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANIF_CODE)CanIf_GetVersionInfo
             (P2VAR(Std_VersionInfoType, AUTOMATIC, CANIF_APPL_DATA)VersionInfo)
{
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  VAR(Std_ReturnType, CANIF_VAR) LenStdRetVal;

  LenStdRetVal = (uint8)E_OK;
  /* Check whether Version Information is equal to NULL Pointer */
  /* polyspace-begin RTE:UNR [Not a defect:Justified] "It is defined by configuration option" */
  CANIF_NULL_PTR_ERROR(CANIF_GET_VERSIONNFO_SID, LenStdRetVal, VersionInfo);
  /* Is any DET Error Invoked*/
  if ((uint8)E_OK == LenStdRetVal)
  #endif
  {
    /* Copy the vendor Id */
    /* polyspace-begin MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */
    VersionInfo->vendorID = CANIF_VENDOR_ID;
    /* Copy the module Id */
    VersionInfo->moduleID = CANIF_MODULE_ID;
    /* Copy Software Major Version */
    VersionInfo->sw_major_version = (uint8)CANIF_VERSION_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    VersionInfo->sw_minor_version = (uint8)CANIF_VERSION_SW_MINOR_VERSION;
    /* polyspace-end MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */
  }
  /* polyspace-end RTE:UNR [Not a defect:Justified] "It is defined by configuration option" */
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
