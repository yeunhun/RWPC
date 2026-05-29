/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanIf_Notif.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Provision of callback Bus-Off and Wakeup Notifications        **
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
** 2.7.1    25-Nov-2020    Sj.Kim    #26002                                   **
** 2.7.0    07-Oct-2020    Sj.Kim    #25877                                   **
** 2.6.2    15-May-2020    Sj.Kim    #23352, #21882, #23360                   **
** 2.6.0    22-Aug-2019    Js.Lim    #18384, #19016                           **
** 2.5.0    06-Dec-2016    Js.Lim    #7077                                    **
** 2.1.8    23-Nov-2016    Js.Lim    #6744                                    **
** 2.1.1    13-Jun-2015    Kt.Kim    Improvement #2724                        **
** 2.1.0    30-May-2013    Kt.Kim    Lib-Build Support                        **
** 1.0.0    28-Mar-2013    Kt.Kim    Initial version                          **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf_Ram.h"           /* CanIf RAM header file */
#include "CanIf_PCTypes.h"       /* Pre-compile time header file */
#include "CanIf_Notif.h"         /* Notification header */
#include "CanSM_Cbk.h"           /* CAN State Manager call back header file */
#if (STD_ON == CANIF_WAKEUP_SUPPORT)
#include "EcuM_Cbk.h"            /* EcuM call back header file */
#endif
#include "SchM_CanIf.h"          /* SchM CanIf Header file */
#include "CanIf_UserInc.h"       /* User Included CanIf Header file */
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#include "CanIf_Error.h"         /* CanIf Det file */
#endif
#include "CanIf_Can.h"                  /* CAN Driver Module Header File */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANIF_NOTIF_C_AR_RELEASE_MAJOR_VERSION    4
#define CANIF_NOTIF_C_AR_RELEASE_MINOR_VERSION    0
#define CANIF_NOTIF_C_AR_RELEASE_REVISION_VERSION 3

/* File version information */
#define CANIF_NOTIF_C_SW_MAJOR_VERSION    3
#define CANIF_NOTIF_C_SW_MINOR_VERSION    0

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANIF_NOTIF_AR_RELEASE_MAJOR_VERSION != \
  CANIF_NOTIF_C_AR_RELEASE_MAJOR_VERSION)
  #error "CANIF_NOTIF.c : Mismatch in Specification Major Version"
#endif
#if (CANIF_NOTIF_AR_RELEASE_MINOR_VERSION != \
  CANIF_NOTIF_C_AR_RELEASE_MINOR_VERSION)
  #error "CANIF_NOTIF.c : Mismatch in Specification Minor Version"
#endif
#if (CANIF_NOTIF_AR_RELEASE_REVISION_VERSION != \
  CANIF_NOTIF_C_AR_RELEASE_REVISION_VERSION)
  #error "CANIF_NOTIF.c : Mismatch in Specification Revision Version"
#endif
#if (CANIF_NOTIF_SW_MAJOR_VERSION != CANIF_NOTIF_C_SW_MAJOR_VERSION)
  #error "CANIF_NOTIF.c : Mismatch in Software Major Version"
#endif
#if (CANIF_NOTIF_SW_MINOR_VERSION != CANIF_NOTIF_C_SW_MINOR_VERSION)
  #error "CANIF_NOTIF.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (STD_ON == CANIF_CTRL_WAKEUP_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, CANIF_CODE)CanIf_CanCheckwakeupService (
                P2CONST(CanIf_WakeupSource, AUTOMATIC, CANIF_CONST)LpWkpSource);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif


#if (STD_ON == CANIF_TRCV_WAKEUP_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, CANIF_CODE)CanIf_TrcvCheckwakeupService (
                P2CONST(CanIf_WakeupSource, AUTOMATIC, CANIF_CONST)LpWkpSource);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : CanIf_CheckWakeup                                   **
**                                                                            **
** Service ID           : 0x11                                                **
**                                                                            **
** Description          : This service checks, whether an underlying CAN      **
**                        driver or a CAN transceiver driver already signals  **
**                        a wakeup event                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : WakeupSource                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized               **
**                                                                            **
** Remarks              : Global Variable(s):  CanIf_GblCanIfStatus,          **
**                                             CanIf_GaaWakeupSource          **
**                        Function(s) invoked: Det_ReportError                **
**                                             CanIf_TrcvCheckwakeupService   **
**                                             CanIf_CanCheckwakeupService    **
**                                             EcuM_SetWakeupEvent            **
*******************************************************************************/
#if (STD_ON == CANIF_WAKEUP_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckWakeup (
                             VAR(EcuM_WakeupSourceType, CANIF_VAR) WakeupSource)
{
  P2CONST(CanIf_WakeupSource, AUTOMATIC, CANIF_CONST) LpWkpSource;
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  P2VAR(CanIf_Controller, AUTOMATIC, CANIF_VAR) LpController;
  #endif
  EcuM_WakeupSourceType LddWakeupEvent;
  uint8_least LucNoOfWakeupSources;
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  uint8 LucCurrentMode;
  #endif
  Std_ReturnType LenStdRetVal;

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  /* Setting the return val to E_OK */
  LenStdRetVal = (uint8)E_OK;
  /* Report to DET, if module is not initialized */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_CHECK_WAKEUP_SID, LenStdRetVal);
  /* Check for any development error */
  if ((uint8)E_OK == LenStdRetVal)
  #endif /*  (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    /* Set LenStdRetVal to E_NOT_OK */
    LenStdRetVal = (uint8)E_NOT_OK;
    /* Get the number of wakeup sources into the local variable */
    LucNoOfWakeupSources = (uint8_least)CANIF_NO_OF_WAKEUP_SOURCES;
    /* Get the pointer to the wakeup structure */
    LpWkpSource = &CanIf_GaaWakeupSource[CANIF_ZERO];
    while(LucNoOfWakeupSources != (uint8_least)CANIF_ZERO)
    {
      /* Get the wakeup event and store it in a local variable */
      LddWakeupEvent = LpWkpSource->ddWakeupEvent;
      /* Check whether the wakeup event is matched or not */
      if (LddWakeupEvent != WakeupSource)
      {
        /* Decrement the number of wakeup sources */
        LucNoOfWakeupSources--;
        /* MISRA Rule   : 17.4
           Message      : Increment or decrement operation performed on pointer.
           Reason       : Increment operator used to achieve better throughput.
           Verification : However, part of the code is verified manually and it
                          is not having any impact.
        */
        /* Increment wakeup source pointer by one */
        LpWkpSource++;
      }
      else
      {
        /* Set the LucNoOfWakeupSources to zero to break the loop */
        LucNoOfWakeupSources = (uint8_least)CANIF_ZERO;
        /* Setting the return val to E_OK */
        LenStdRetVal = (uint8)E_OK;
      }
    }
    /* Check whether wakeup flag is true */
    if ((uint8)E_OK == LenStdRetVal)
    {
      #if (STD_ON == CANIF_DEV_ERROR_DETECT)
      /* Get the pointer to the controller structure*/
      LpController = &CanIf_GaaController[LpWkpSource->ucControllerConfigId];
      /* Get the current controller mode*/
      LucCurrentMode = LpController->ucControllerMode;
      /* Report to DET, if Controller Mode is Not in Sleep */
      CANIF_NOT_SLEEP_MODE_ERROR(CANIF_CHECK_WAKEUP_SID, LenStdRetVal);
      /* Check if DET invoked or not */
      if ((uint8)E_OK == LenStdRetVal)
      #endif
      {
        #if (STD_ON == CANIF_CTRL_WAKEUP_SUPPORT)
        /* Is the wakeup source is due to Can Driver */
        /* polyspace +1 MISRA-C3:14.3, DEFECT:USELESS_IF [Not a defect: Justified] "Condition will be executed based on the configured values" */
        if (CANIF_CANDRV_WAKEUPSOURCE == (uint8)(LpWkpSource->ucWakeupSource))
        {
          /* invoke CanIf_CanCheckwakeupService */
          LenStdRetVal = CanIf_CanCheckwakeupService(LpWkpSource);
        }
        else
        #endif
        {
          #if (STD_ON == CANIF_TRCV_WAKEUP_SUPPORT)
          /* invoke CanIf_TrcvCheckwakeupService  */
          LenStdRetVal = CanIf_TrcvCheckwakeupService(LpWkpSource);
          #endif
        }

        if ((uint8)E_OK == LenStdRetVal)
        {
          /* Invoke Wakeup Indication function */
          EcuM_SetWakeupEvent(WakeupSource);
        }/* if ((uint8)E_OK == LenStdRetVal) */
      }/* if ((uint8)E_OK == LenStdRetVal) */
    }/*(E_OK == LenStdRetVal) */
    #if (STD_ON == CANIF_DEV_ERROR_DETECT)
    else
    {
      /* Report to DET, if Wakeup sourceId is invalid */
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                            CANIF_CHECK_WAKEUP_SID, CANIF_E_PARAM_WAKEUPSOURCE);
    }
    #endif
  }/*after passing DET Checks */
  return(LenStdRetVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : CanIf_CheckValidation                               **
**                                                                            **
** Service ID           : 0x12                                                **
**                                                                            **
** Description          : This service is performed to validate a previous    **
**                        wakeup event. The CAN Interface checks inside this  **
**                        service, whether a L-PDU is successfully received   **
**                        in the meantime.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : WakeupSource                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized               **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_GaaWakeupSource           **
**                                            CanIf_GblCanIfStatus,           **
**                                            CanIf_GaaController,            **
**                        Function(s) invoked:                                **
**                                            Det_ReportError                 **
**                                            SchM_Enter_CanIf_MODE_STATUS_   **
**                                            PROTECTION,                     **
**                                            SchM_Exit_CanIf_MODE_STATUS_    **
**                                            PROTECTION                      **
*******************************************************************************/
#if (STD_ON == CANIF_WAKEUP_CHECK_VALIDATION_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckValidation (
                             VAR(EcuM_WakeupSourceType, CANIF_VAR) WakeupSource)
{
  P2CONST(CanIf_WakeupSource, AUTOMATIC, CANIF_CONST) LpWkpSource;
  P2VAR(CanIf_Controller, AUTOMATIC, CANIF_VAR) LpController;
  EcuM_WakeupSourceType LddWakeupEvent;
  uint8_least LucNoOfWakeupSources;
  uint8_least LucNoOfCntrl;
  Std_ReturnType LenStdRetVal;

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  /* Setting the return val to E_OK */
  LenStdRetVal = (uint8)E_OK;
  /* Report to DET, if module is not initialized */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_CHECK_VALIDATION_SID, LenStdRetVal);
  /* Check for any development error */
  if ((uint8)E_OK == LenStdRetVal)
  #endif
  {
    /* Set LenStdRetVal to E_NOT_OK */
    LenStdRetVal = (uint8)E_NOT_OK;
    /* Get the number of wakeup sources into the local variable */
    LucNoOfWakeupSources = (uint8_least)CANIF_NO_OF_WAKEUP_SOURCES;
    /* Get the pointer to the wakeup structure */
    LpWkpSource = &CanIf_GaaWakeupSource[CANIF_ZERO];
    while(LucNoOfWakeupSources != (uint8_least)CANIF_ZERO)
    {
      /* Get the wakeup event and store it in a local variable */
      LddWakeupEvent = LpWkpSource->ddWakeupEvent;
      /* Check whether the wakeup event is matched or not */
      if (LddWakeupEvent != WakeupSource)
      {
        /* Decrement the number of wakeup sources */
        LucNoOfWakeupSources--;

        /* Increment wakeup source pointer by one */
        LpWkpSource++;
      }
      else
      {
        /*LucNoOfWakeupSources set to zero to break the loop*/
        LucNoOfWakeupSources = (uint8_least)CANIF_ZERO;
        /* Set LenStdRetVal to E_OK */
        LenStdRetVal = (uint8)E_OK;
      }
    }/*while(LucNoOfWakeupSources != CANIF_ZERO)*/

    if ((uint8)E_OK == LenStdRetVal)
    {
      /* Get the pointer to the controller structure*/
      LpController =  &CanIf_GaaController[LpWkpSource->ucControllerConfigId];
      /* Check the wakeup validation flag for true as per CANIF681 */
      if (LpController->ucRxStatus != CANIF_RX_VALIDATE_WAKEUP)
      {
        /* Set LenStdRetVal to E_NOT_OK */
        LenStdRetVal = (uint8)E_NOT_OK;
      }/* (LpController->ucRxStatus != CANIF_RX_VALIDATE_WAKEUP) */
      else
      {
        /* Invoke EcuM/Cdd_ValidateWakeupEvent function */
        CANIF_DISPATCH_USERVALIDATEWAKEUPEVENT_NAME(WakeupSource);
      }
      /* Disable interrupts */
      SchM_Enter_CanIf_MODE_STATUS_PROTECTION();
      /* Clear the wakeup validation flag */
      LpController->ucRxStatus = CANIF_RX_ENABLED;
      /* Take controllers in local variable */
      LucNoOfCntrl = LpWkpSource->ucNoOfCanCntrlOrTrcvId;
      /* check if multiple controllers are connected */
      /* polyspace +1 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
      while((LucNoOfCntrl >= (uint8_least)CANIF_TWO) && 
			(CANIF_NO_OF_CONTROLLER >= (uint8_least)CANIF_TWO))
      {
        /* Point to next controller */
        LpController++;
        /* Clear the wakeup validation flag */
        /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Genderated array index in range" */	
        LpController->ucRxStatus = CANIF_RX_ENABLED;
        /* Decrement controller */
        LucNoOfCntrl--;
      }
      /* Enable interrupts */
      SchM_Exit_CanIf_MODE_STATUS_PROTECTION();
    }/* (E_OK == LenStdRetVal) */
    #if (STD_ON == CANIF_DEV_ERROR_DETECT)
    else
    {
      /* Report to DET, if Wakeup sourceId is invalid */
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                        CANIF_CHECK_VALIDATION_SID, CANIF_E_PARAM_WAKEUPSOURCE);
    }
    #endif
  }/* after passing DET Checks */
  return(LenStdRetVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif/*(STD_ON == CANIF_WAKEUP_SUPPORT)*/

/*******************************************************************************
** Function Name        : CanIf_ControllerBusOff                              **
**                                                                            **
** Service ID           : 0x16                                                **
**                                                                            **
** Description          : This service indicates a Controller BusOff event    **
**                        referring to the corresponding CAN Controller       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : Controller                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized               **
**                                                                            **
** Remarks              : Global Variable(s) : CanIf_GblCanIfStatus,          **
**                                             CanIf_GaaController,           **
**                                             CanIf_GaaControllerConfigType  **
**                        Function(s) invoked:                                **
**                                             CanIf_ClearTxQueue,            **
**                                             Det_ReportError,               **
**                                             SchM_Enter_CanIf_MODE_STATUS_  **
**                                             PROTECTION,                    **
**                                             SchM_Exit_CanIf_MODE_STATUS_   **
**                                             PROTECTION                     **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANIF_CODE) CanIf_ControllerBusOff (
                                             VAR(uint8, CANIF_VAR) ControllerId)

{
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST)
                                                             LpStaticController;
  P2VAR(CanIf_Controller, AUTOMATIC, CANIF_VAR) LpController;
  /* If the Development errors detection is enabled */
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  VAR(Std_ReturnType, CANIF_VAR) LenStdRetVal;
  /* Initialize the det error flag status to zero */
  LenStdRetVal = (uint8)E_OK;
  /* Report to DET, if module is not initialized */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_CNTRL_BUS_OFF_SID, LenStdRetVal);
  /* Report to DET, if requested controller id is more than available
  controller */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_CNTRL_BUS_OFF_SID, LenStdRetVal);
  /* check for any development occurred? */
  if ((uint8)E_OK == LenStdRetVal)
  #endif /* CANIF_DEV_ERROR_DETECT */
  {
    LpController = &CanIf_GaaController[ControllerId];
    /* Check controller mode is in start mode */
    /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Genderated array index in range" */
    if ((uint8)CANIF_CS_STARTED == LpController->ucControllerMode)
    {
      /* Disable interrupts */
      SchM_Enter_CanIf_MODE_STATUS_PROTECTION();
      /* Change the controller state */
      LpController->ucControllerMode = (uint8)CANIF_CS_STOPPED;
      /* Change the Rx Status to zero */
      LpController->ucRxStatus = CANIF_RX_DISABLED;
      /* Change the Tx Status to zero */
      /* #6744 */
      LpController->ucTxStatus = CANIF_TX_DISABLED;
      /* Enable interrupts */
      SchM_Exit_CanIf_MODE_STATUS_PROTECTION();
      /* Invoke the upper layer function  */
      CANIF_DISPATCH_USERCTRLBUSOFF_NAME(ControllerId);
#if (STD_ON == CANIF_TX_LPDU)
      /* polyspace-begin DEFECT:USELESS_IF [Not a defect:Medium] "The value is generated by Generator." */
      /* polyspace +1 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
      if(STD_ON == CanIf_GddPrecompOpt.ucTxBasicCanPdu)
      /* polyspace-end DEFECT:USELESS_IF [Not a defect:Medium] "The value is generated by Generator." */
      {
        #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
        LpStaticController = &CanIf_GaaControllerConfigTypeSelect[ControllerId];
        #else
        LpStaticController = &CanIf_GaaControllerConfigType[ControllerId];
        #endif
        /* Disabling relevant interrupts*/
        SchM_Enter_CanIf_TX_QUEUE_PROTECTION();
        /* Clear Tx queue */
        CanIf_ClearTxQueue(LpStaticController);
        /* Enabling relevant interrupts*/
        SchM_Exit_CanIf_TX_QUEUE_PROTECTION();
      }
#endif
    }/*if ((uint8)CANIF_CS_STARTED == LpController->ucControllerMode)*/
  }/*if (E_OK == LenStdRetVal)*/
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_CanCheckwakeupService                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to invoke the Can_CheckWakeup **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpWkpSource                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanIf_Init() should be invoked                      **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_GaaCanDriver              **
**                                            CanIf_GaaController             **
**                                                                            **
**                        Function(s) invoked: Can_CheckWakeup                **
**                                    SchM_Enter_CanIf_MODE_STATUS_PROTECTION **
**                                    SchM_Exit_CanIf_MODE_STATUS_PROTECTION  **
*******************************************************************************/
#if (STD_ON == CANIF_CTRL_WAKEUP_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, CANIF_CODE)CanIf_CanCheckwakeupService (
                 P2CONST(CanIf_WakeupSource, AUTOMATIC, CANIF_CONST)LpWkpSource)
{
  #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
  P2CONST(CanIf_CanDriver, AUTOMATIC, CANIF_CONST) LpDriver;
  #endif
  P2VAR(CanIf_Controller, AUTOMATIC, CANIF_VAR) LpController;
  VAR(Std_ReturnType, CANIF_VAR) LenStdRetVal;
  #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
  /* Get the pointer to corresponding Can Driver structure */
  LpDriver = &CanIf_GaaCanDriver[LpWkpSource->ucDriverId];
  /* Invoke corresponding Driver function */
  /* polyspace<RTE: IDP : Not a defect : No Action Planned >
                                          Its boundary is pre-defined           */
  LenStdRetVal = (Std_ReturnType)LpDriver->pCanCheckwakeup(LpWkpSource->ucControllerConfigId);
  #else
  /* Invoke Can_Checkwakeup function */
  LenStdRetVal = (Std_ReturnType)Can_CheckWakeup(LpWkpSource->ucControllerConfigId);
  #endif
  if ((uint8)E_OK == LenStdRetVal)
  {
    /* Get the pointer to the controller structure */
    LpController = &CanIf_GaaController[LpWkpSource->ucControllerConfigId];
    /* Disable interrupts */
    SchM_Enter_CanIf_MODE_STATUS_PROTECTION();
    /* Change the state of the Controller to CANIF_CS_STOPPED */
    LpController->ucControllerMode = (uint8)CANIF_CS_STOPPED;
    #if (STD_ON == CANIF_WAKEUP_CHECK_VALIDATION_SUPPORT)
    /* Change the state of the Rx Status to Wakeup */
    LpController->ucRxStatus = CANIF_RX_VALIDATE_WAKEUP;
    /*CANIF_RX_VALIDATE_WAKEUP = 0x81*/
    #endif/*#if (STD_ON == CANIF_WAKEUP_CHECK_VALIDATION_SUPPORT)*/
    /* Enable interrupts */
    SchM_Exit_CanIf_MODE_STATUS_PROTECTION();
  }
  return (LenStdRetVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_TrcvCheckwakeupService                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to invoke the                 **
**                        CanTrcv_CheckWakeup                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpWkpSource                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : LpRxLpdu                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_GaaCanTrcvDriver          **
**                                                                            **
**                        Function(s) invoked: CanTrcv_CheckWakeup            **
*******************************************************************************/
#if (STD_ON == CANIF_TRCV_WAKEUP_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, CANIF_CODE)CanIf_TrcvCheckwakeupService (
                 P2CONST(CanIf_WakeupSource, AUTOMATIC, CANIF_CONST)LpWkpSource)
{
  #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
  P2CONST(CanIf_CanTrcvDriver, AUTOMATIC, CANIF_CONST) LpCanTrcvDriver;
  #endif
  VAR(Std_ReturnType, CANIF_VAR) LenStdRetVal;
  #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
    /* Get the pointer to corresponding Can Driver structure */
  LpCanTrcvDriver = &CanIf_GaaCanTrcvDriver[LpWkpSource->ucDriverId];
  /* Invoke corresponding Driver function */
  LenStdRetVal = LpCanTrcvDriver->pCanTrcvCheckWakeup
                                              (LpWkpSource->ucCanCntrlOrTrcvId);
  #else/*#if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)*/
  /* Invoke Can_Checkwakeup function */
  LenStdRetVal = CanTrcv_CheckWakeup(LpWkpSource->ucCanCntrlOrTrcvId);
  #endif/*#if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)*/
  return (LenStdRetVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
