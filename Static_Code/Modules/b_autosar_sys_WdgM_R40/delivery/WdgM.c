/*******************************************************************************
**                                                                            **
**  (C) 2015 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: WdgM.c                                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR WDGM                                                  **
**                                                                            **
**  PURPOSE   : Watchdog Manager API Functionality                            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.2.17    08-Jan-2021   YH.Han       Redmine #27590                        **
** 1.2.16    10-Aug-2020   YH.Han       Redmine #24177                        **
** 1.2.13    04-Dec-2018   YH.Han       Redmine #14965                        **
** 1.2.12    30-Mar-2018   YH.Han       Redmine #11171, #11341                **
** 1.0.28    14-Sep-2015   Sinil        1. Justify runtime error              **
**                                      2. WDGM_PM_MODECHANGE_API flag removed**
** 1.0.27    20-Aug-2015   Sinil        1. Follow function prototype argument **
**                                      naming rule                           **
** 1.0.26    23-Apr-2015   Sinil        1. Fix Misra-c rule violations        **
** 1.0.25    06-Apr-2015   Sinil        1. Trigger Wdgs after successful      **
**                                      WdgMMode change                       **
** 1.0.24    27-Jan-2015   Sinil        1. Fix MISRA-C rule violation         **
**                                      2. Remove unnecessary comment for     **
**                                      polyspace                             **
** 1.0.23    12-Nov-2014   Sinil        1. Fix code and comment for polyspace **
** 1.0.22    03-Nov-2014   Sinil        1. Update Rte notification related to **
**                                      immediate MCU reset                   **
** 1.0.21    28-Oct-2014   Sinil        1. Fix not used variable warning      **
** 1.0.20    22-Oct-2014   Sinil        1. Refactoring WdgM_CheckpointReached,**
**                                      WdgM_UpdateAliveCounter and           **
**                                      WdgM_MainFunction                     **
**                                      2. Change calling WdgM_TriggerWdgIf   **
**                                      seqeunce in WdgM_Init and             **
**                                      WdgM_PerformReset                     **
**                                      3. Remove the condition of updating   **
**                                      global status                         **
**                                      4. Func WdgM_GetErrorInfo added       **
**                                      5. Adjust protected sections          **
**                                      6. Adjust precompile options          **
**                                      7. Change including                   **
**                                      8. Rearrange items and change naming  **
** 1.0.19    07-Oct-2014   Sinil        1. Change WdgM_TriggerWdgIf argument  **
** 1.0.18    01-Oct-2014   Sinil        1. Remove WDGM_LP_SUPPORT precompile  **
**                                      option                                **
**                                      2. Exclude calling pRteSwitchMode in  **
**                                      WdgM_SetMode from exclusive area      **
**                                      protection                            **
** 1.0.17    30-Sep-2014   Sinil        1. Remove Wdgm_PerformTimeStamping    **
** 1.0.16    15-Jul-2014   Sinil        1. Remove WdgM_PmTrigger              **
**                                      2. Update WdgM_PmModeChange           **
** 1.0.15    03-Jun-2014   Sinil        1. WDGM_LP_SUPPORT flag added         **
** 1.0.14    30-May-2014   Sinil        1. WdgM_PmModeChange and              **
**                                      WdgM_PmTrigger added                  **
** 1.0.13    29-Jan-2014   Sinil        TaskID:826                            **
**                                      1. Remove the call pRteSwitchMode in  **
**                                      WdgM_Init func. RedMine:588           **
** 1.0.12    28-Jan-2014   Sinil        TaskID:811                            **
**                                      1. Change usTotalSEInMode to          **
**                                      ddTotalSEInMode                       **
** 1.0.8     03-Jan-2014   Sinil        TaskID:809                            **
**                                      1. Variable names and types changed   **
**                                      2. Modified for dead code defect      **
** 1.0.7     16-Dec-2013   Sinil        Wdgm_Dem_Cfg.h was included and       **
**                                        related macro's adjusted            **
**                                      Report the event of changed SE status **
** 1.0.6     10-Jun-2013   Sinil        CR 127 : Change some macros to const  **
**                                        variables for making library        **
** 1.0.5     05-Jun-2013   Sinil        CR 128 : Fix mode switch event calls  **
**                                        are skipped because of supending    **
**                                         interrupts                         **
** 1.0.4     28-May-2013   Sinil        Adjust changed inteface of            **
**                                        WdgM_TriggerWdgIf func and compile  **
**                                        option DL_ID:119                    **
**                                      Insert WdgM_TriggerWdgIf call in      **
**                                        WdgM_Init func for mode             **
**                                        initialization                      **
**                                      Make API pairs for exclusive area     **
**                                      Adjust changed interface of           **
**                                        WdgM_SEIndexBinarySearch func       **
**                                      Deadline supervision check condition  **
**                                        in WdgM_PerformDeadlineMonitoring   **
**                                        moved to WdgM_CheckpointReached     **
**                                      Put LpSupervisedEntity in             **
**                                        WdgM_UpdateAliveCounter func within **
**                                        WDGM_ENABLE_ALIVE_SUPERVISION macro **
**                                        condition                           **
**                                      Clear compile warning in              **
**                                        WdgM_GetFirstExpiredSEID func       **
** 1.0.0     01-Jan-2013   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Not a Defect] "see MEMMAP003 of AUTOSAR" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "WdgM.h"
#include "Rte_WdgM.h"
#include "WdgM_Config.h"      /* Extern Declarations  of const variables */
#include "WdgM_Ram.h"         /* WdgM Ram variables header file */
#include "WdgM_GenExterns.h"  /* Extern Declarations  of generated variables */
#include "WdgM_PCTypes.h"     /* WdgM Types Header file */
#include "WdgM_Internal.h"    /* Extern Declarations  of internal functions */

#include "SchM_WdgM.h"        /* SchM Header file */
#if(WDGM_IMMEDIATE_RESET == STD_ON)
#include "Mcu.h"              /* Mcu Header file */
#endif
#if(WDGM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"              /* Det Header file */
#endif
#if(WDGM_DEM_ERROR_REPORT == STD_ON)
#include "WdgM_Dem_Cfg.h"     /* Dem Header file */
#endif

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/
/*******************************************************************************
** Function Name      : WdgM_Init                                             **
**                                                                            **
** Service ID         : 0x00                                                  **
**                                                                            **
** Description        : This service performs initialization of WdgM          **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : pConfigPtr                                            **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      WdgM_GddCurrentMode,                                  **
**                      WdgM_GddInitMode,                                     **
**                      WdgM_GaaModes,                                        **
**                      WdgM_GblModuleInitStatus,                             **
**                      WdgM_GddGlobalSupervisionStatus,                      **
**                      WdgM_GddInvGlobalSupervisionStatus                    **
**                      WdgM_GaaSEStatus,                                     **
**                      WdgM_GddESetMode,                                     **
**                      WdgM_GddEMonitoring                                   **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError,                                      **
**                      WdgM_InternalSetMode,                                 **
**                      WdgM_ClearActivityFlag,                               **
**                      WdgM_TriggerWdgIf,                                    **
**                      Dem_ReportErrorStatus,                                **
**                      Mcu_PerformReset                                      **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_Init(
  P2CONST(WdgM_ConfigType, WDGM_CONST, WDGM_CONST)pConfigPtr)
{
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) LpInitMode;
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST) LpInitModeLocalStatus;
  WdgM_SupervisedEntityIndexType LddSEcount;
  boolean LblSetModeFailed;
  #if((WDGM_DEV_ERROR_DETECT == STD_ON) && (WDGM_OFF_MODE_ENABLED == STD_OFF)\
    && (WDGM_ENABLE_TRIGGER == STD_ON))
  P2CONST(WdgM_TriggerType, AUTOMATIC, WDGM_CONST) LpTriggers;
  boolean LblInitResult;
  uint8 LucCount;
  #endif

  /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> NULL pointer check */
  WDGM_UNUSED_PTR(pConfigPtr);
  /* polyspace:end<RTE:UNR> */

  /* Get the initial mode of WdgM */
  WdgM_GddCurrentMode = WdgM_GddInitMode;
  /* Get the pointer to Init mode array */
  LpInitMode = &WdgM_GaaModes[WdgM_GddCurrentMode];

  #if((WDGM_DEV_ERROR_DETECT == STD_ON) && (WDGM_OFF_MODE_ENABLED == STD_OFF)\
    && (WDGM_ENABLE_TRIGGER == STD_ON))
  LblInitResult = WDGM_TRUE;
  /* Update the pointer to first element of Trigger structure array */
  LpTriggers = LpInitMode->pTriggers;
  LucCount = WDGM_ZERO;
  /* Loop running through all configured watchdog drivers */
  while (LucCount < LpInitMode->ucTotalTriggers)
  {
    if ((LpTriggers[LucCount].ddWdgIfMode) == WDGIF_OFF_MODE)
    {
      /* Report to DET */
      (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
        WDGM_INIT_SID, WDGM_E_DISABLE_NOT_ALLOWED);
      /* Update Global Initialization Status to Uninitialized */
      WdgM_GblModuleInitStatus = WDGM_UNINITIALIZED;
      LucCount = LpInitMode->ucTotalTriggers;
      LblInitResult = WDGM_FALSE;
    }
    else
    {
      /* Increment the watchdog count */
      LucCount++;
    }
  }

  if (LblInitResult == WDGM_TRUE)
  #endif
  {
    /* Clear the Global supervision status */
    WdgM_GddGlobalSupervisionStatus = WDGM_GLOBAL_STATUS_DEACTIVATED;
    WdgM_GddInvGlobalSupervisionStatus = ~WdgM_GddGlobalSupervisionStatus;

    /* Get the total SEs configured */
    LddSEcount = WdgM_GddTotalSEs;
    while (LddSEcount != WDGM_ZERO)
    {
      LddSEcount--;
      /* Set Local Status of SEs to WDGM_LOCAL_STATUS_DEACTIVATED */
      WdgM_GaaSEStatus[LddSEcount]
        = ((WdgM_GaaSEStatus[LddSEcount] & WDGM_CLEAR_STATUS)
        | WDGM_SET_ALLSUPVSN_CORRECT) | WDGM_LOCAL_STATUS_DEACTIVATED;
    }

    /* Get the pointer to WdgM_GaaModexLocalStatus */
    /* polyspace<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    LpInitModeLocalStatus = LpInitMode->pActiveSEList;
    /* Get the total SE's in the Init mode */
    LddSEcount = WDGM_ZERO;
    /* polyspace<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    while (LddSEcount < (WdgM_SupervisedEntityIndexType)LpInitMode->ddTotalSEInMode)
    {
      /* Activate the SE present in the Init mode */
      /* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
      /* polyspace:begin<RTE:NIV:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
      /* polyspace:begin<RTE:OBAI:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
      /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
      WdgM_GaaSEStatus[LpInitModeLocalStatus[LddSEcount].ddSEArrayIndex]
        = (WdgM_GaaSEStatus[LpInitModeLocalStatus[LddSEcount].ddSEArrayIndex]
        & WDGM_CLEAR_SE) | WDGM_LOCAL_STATUS_OK;
      /* polyspace:end<RTE:IDP> */
      /* polyspace:end<RTE:NIV> */
      /* polyspace:end<RTE:OBAI> */
      /* polyspace:end<MISRA-C3:18.1> */

      /* Inccrement the SEs loop count */
      LddSEcount++;
    }

    /* Establish the hardware watchdog modes */
    LblSetModeFailed = WdgM_InternalSetMode(WdgM_GddCurrentMode);
    if (LblSetModeFailed == WDGM_FALSE)
    {
      WdgM_ClearActivityFlag(LpInitMode);
      /* Clear the expired supervision cycle counter */
      WdgM_GddExpSupervisionCycleCounter = WDGM_ZERO;

      /* Set Global Supervision Status */
      WdgM_GddGlobalSupervisionStatus = WDGM_GLOBAL_STATUS_OK;
      WdgM_GddInvGlobalSupervisionStatus = ~WdgM_GddGlobalSupervisionStatus;
      #if (WDGM_DEV_ERROR_DETECT == STD_ON)
      /* Update Global Initialization Status to Uninitialized */
      WdgM_GblModuleInitStatus = WDGM_INITIALIZED;
      #endif
      WdgM_TriggerWdgIf(LpInitMode, WDGM_TM_NORMAL);
    }
    else
    {
      /* Update Global Supervision Status */
      WdgM_GddGlobalSupervisionStatus = WDGM_GLOBAL_STATUS_STOPPED;
      WdgM_GddInvGlobalSupervisionStatus = ~WdgM_GddGlobalSupervisionStatus;
      #if (WDGM_DEV_ERROR_DETECT == STD_ON)
      /* Update Global Initialization Status to Uninitialized */
      WdgM_GblModuleInitStatus = WDGM_UNINITIALIZED;
      #endif
      #if(WDGM_DEM_ERROR_REPORT == STD_ON)
      Dem_ReportErrorStatus(WdgM_GddESetMode, DEM_EVENT_STATUS_FAILED);
      #if(WDGM_DEM_STOPPED_SUPERVISION_REPORT == STD_ON)
      Dem_ReportErrorStatus(WdgM_GddEMonitoring, DEM_EVENT_STATUS_FAILED);
      #endif
      #endif
      #if(WDGM_IMMEDIATE_RESET == STD_ON)
      Mcu_PerformReset();
      #endif
      WdgM_TriggerWdgIf(LpInitMode, WDGM_TM_TIMEOUT);
    }
  }
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : WdgM_DeInit                                           **
**                                                                            **
** Service ID         : 0x01                                                  **
**                                                                            **
** Description        : This service performs Deinitialization of WdgM        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : Watchdog Manager should be initialized                **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      WdgM_GblModuleInitStatus,                             **
**                      WdgM_GddGlobalSupervisionStatus,                      **
**                      WdgM_GddInvGlobalSupervisionStatus                    **
**                      WdgM_GaaModes,                                        **
**                      WdgM_GddCurrentMode                                   **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError,                                      **
**                      WdgM_TriggerWdgIf                                     **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_DeInit(void)
{
  /* Get the pointer to current mode */
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST)LpCurrentMode;

  #if(WDGM_DEV_ERROR_DETECT == STD_ON)
  /* Det Check for module initialization*/
  if (WdgM_GblModuleInitStatus == WDGM_UNINITIALIZED)
  {
    /* Report to DET  */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_DEINIT_SID, WDGM_E_NO_INIT);
  }
  else
  #endif
  {
    if (WdgM_GddGlobalSupervisionStatus == WDGM_GLOBAL_STATUS_OK)
    {
      /* Change global supervision status to DEACTIVATED */
      WdgM_GddGlobalSupervisionStatus = WDGM_GLOBAL_STATUS_DEACTIVATED;
      WdgM_GddInvGlobalSupervisionStatus = ~WdgM_GddGlobalSupervisionStatus;
    }
    #if (WDGM_DEV_ERROR_DETECT == STD_ON)
    /* Update Global Initialization Status to Uninitialized */
    WdgM_GblModuleInitStatus = WDGM_UNINITIALIZED;
    #endif
    /* Get the address of currentMode from the Mode structure array into the
      global pointer */
    LpCurrentMode = &WdgM_GaaModes[WdgM_GddCurrentMode];
    /* Trigger all the watchdogs which are not in OFFMODE to the timeout value
      configured  */
    WdgM_TriggerWdgIf(LpCurrentMode, WDGM_TM_DEINIT);
  }
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

#if(WDGM_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Function Name        : WdgM_GetVersionInfo                                 **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : This API reads the version information of WdgM      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pVersionInfo                                        **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : None                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, WDGM_APPL_DATA) pVersionInfo)
{
  #if(WDGM_DEV_ERROR_DETECT == STD_ON)
  /* check NULL pointer */
  if (pVersionInfo == NULL_PTR)
  {
    /* Report to DET */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_GETVERSIONINFO_SID, WDGM_E_INV_POINTER);
  }
  else
  #endif
  {
    /* Load the vendor Id */
    pVersionInfo->vendorID = WDGM_VENDOR_ID;
    /* Load the module Id */
    pVersionInfo->moduleID = WDGM_MODULE_ID;
    /* Load Software Major Version */
    pVersionInfo->sw_major_version = WDGM_SW_MAJOR_VERSION;
    /* Load Software Minor Version */
    pVersionInfo->sw_minor_version = WDGM_SW_MINOR_VERSION;
    /* Load Software Patch Version */
    pVersionInfo->sw_patch_version = WDGM_SW_PATCH_VERSION;
  }
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (WDGM_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
** Function Name        : WdgM_SetMode                                        **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This service performs switching between different   **
**                        modes of WdgM                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : ddMode, usCallerID                                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Watchdog Manager should be initialized              **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        WdgM_GaaModes,                                      **
**                        WdgM_GblModuleInitStatus,                           **
**                        WdgM_GddTotalModes,                                 **
**                        WdgM_GucTotalSetModeApiCallers,                     **
**                        WdgM_GaaSetModeCallerId,                            **
**                        WdgM_GddEImproperCaller,                            **
**                        WdgM_GddGlobalSupervisionStatus,                    **
**                        WdgM_GddInvGlobalSupervisionStatus                  **
**                        WdgM_GddESetMode,                                   **
**                        WdgM_GddEMonitoring,                                **
**                        WdgM_GaaSEStatus,                                   **
**                        WdgM_GaaSupervisedEntity,                           **
**                        WdgM_GddCurrentMode,                                **
**                        WdgM_GddFailedRefCycleCounter                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        Dem_ReportErrorStatus,                              **
**                        WdgM_InternalSetMode,                               **
**                        Mcu_PerformReset,                                   **
**                        Rte_Switch_globalMode_currentMode,                  **
**                        WdgM_TriggerWdgIf,                                  **
**                        WdgM_ClearActivityFlag,                             **
**                        pRteSwitchMode,                                     **
**                        SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,      **
**                        SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION        **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, WDGM_CODE) WdgM_SetMode(
  WdgM_ModeType ddMode, uint16 usCallerID)
{
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) LpNewMode;
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) LpPrevMode;
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST) LpNewModeLocalStatus;
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST) LpPrevModeLocalStatus;
  /* Local variable for return value */
  Std_ReturnType LddReturnvalue;
  WdgM_SupervisedEntityIndexType LddSEArrayIndex;
  uint16 LusNewModeTotalSE;
  uint16 LusPrevModeTotalSE;
  boolean LblDeactivateFlag;
  boolean LblSetModeFailed;
  #if(WDGM_DEV_ERROR_DETECT == STD_ON)
  #if((WDGM_OFF_MODE_ENABLED == STD_OFF) && (WDGM_ENABLE_TRIGGER == STD_ON))
  P2CONST(WdgM_TriggerType, AUTOMATIC, WDGM_CONST) LpTriggers;
  #endif
  #if(WDGM_DEFENSIVE_BEHAVIOR == STD_ON)
  boolean LblSetModeCallerflag;
  #endif
  #if((WDGM_OFF_MODE_ENABLED == STD_OFF) || (WDGM_DEFENSIVE_BEHAVIOR == STD_ON))
  uint8 LucCount;
  #endif
  #endif

  LddReturnvalue = E_OK;
  LpNewMode = &WdgM_GaaModes[ddMode];

  #if (WDGM_DEV_ERROR_DETECT == STD_ON)
  /* Det Check for module initialization*/
  if (WdgM_GblModuleInitStatus == WDGM_UNINITIALIZED)
  {
    /* Report to DET  */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_SETMODE_SID, WDGM_E_NO_INIT);
    LddReturnvalue = E_NOT_OK;
  }
  /* Check for Mode is correct */
  if (ddMode >= WdgM_GddTotalModes)
  {
    /* Report to DET  */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_SETMODE_SID, WDGM_E_PARAM_MODE);
    LddReturnvalue = E_NOT_OK;
  }
  /* Is OFFMODE Disabled */
  #if((WDGM_OFF_MODE_ENABLED == STD_OFF) && (WDGM_ENABLE_TRIGGER == STD_ON))
  /* Check the return value */
  if (LddReturnvalue == E_OK)
  {
    /* Update the pointer to first element of Trigger structure array */
    LpTriggers = LpNewMode->pTriggers;
    LucCount = WDGM_ZERO;
    /* Loop running through all configured watchdog drivers */
    while (LucCount < LpNewMode->ucTotalTriggers)
    {
      if ((LpTriggers[LucCount].ddWdgIfMode) == WDGIF_OFF_MODE)
      {
        /* Report to DET  */
        (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
          WDGM_SETMODE_SID, WDGM_E_DISABLE_NOT_ALLOWED);
        LucCount = LpNewMode->ucTotalTriggers;
        LddReturnvalue = E_NOT_OK;
      }
      else
      {
        LucCount++;
      }
    }
  }
  #endif /* #if((WDGM_OFF_MODE_ENABLED == STD_OFF)
    && (WDGM_ENABLE_TRIGGER == STD_ON)) */
  #if(WDGM_DEFENSIVE_BEHAVIOR == STD_ON)
  LblSetModeCallerflag = WDGM_FALSE;
  /* Dem Check for improper setmode caller */
  LucCount = WdgM_GucTotalSetModeApiCallers;
  while (LucCount != WDGM_ZERO)
  {
    LucCount--;

    /* polyspace<RTE:OBAI:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    if (usCallerID == WdgM_GaaSetModeCallerId[LucCount])
    {
      LblSetModeCallerflag = WDGM_TRUE;
      LucCount = WDGM_ZERO;
    }
  }
  if (LblSetModeCallerflag == WDGM_FALSE)
  {
    #if(WDGM_DEM_ERROR_REPORT == STD_ON)
    /* Report to DEM */
    (void)Dem_ReportErrorStatus(WdgM_GddEImproperCaller,
      DEM_EVENT_STATUS_FAILED);
    #endif
    LddReturnvalue = E_NOT_OK;
  }
  #else /* #if (WDGM_DEFENSIVE_BEHAVIOR == STD_ON) */
  WDGM_UNUSED(usCallerID);
  #endif /* #if (WDGM_DEFENSIVE_BEHAVIOR == STD_ON) */
  #else /* #if (WDGM_DEV_ERROR_DETECT == STD_ON) */
  WDGM_UNUSED(usCallerID);
  #endif /* #if (WDGM_DEV_ERROR_DETECT == STD_ON) */

  /* Check the return value */
  if (LddReturnvalue == E_OK)
  {
    SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();

    /* Check if Global Status is WDGM_GLOBAL_STATUS_OK or
      WDGM_GLOBAL_STATUS_FAILED */
    if ((WdgM_GddGlobalSupervisionStatus == WDGM_GLOBAL_STATUS_OK) ||
      (WdgM_GddGlobalSupervisionStatus == WDGM_GLOBAL_STATUS_FAILED))
    {
      /* Establish the hardware watchdog modes */
      LblSetModeFailed = WdgM_InternalSetMode(ddMode);

      if (LblSetModeFailed == WDGM_TRUE)
      {
        /* Update Global supervision */
        WdgM_GddGlobalSupervisionStatus = WDGM_GLOBAL_STATUS_STOPPED;
        WdgM_GddInvGlobalSupervisionStatus = ~WdgM_GddGlobalSupervisionStatus;
        #if(WDGM_DEM_ERROR_REPORT == STD_ON)
        Dem_ReportErrorStatus(WdgM_GddESetMode, DEM_EVENT_STATUS_FAILED);
        #if(WDGM_DEM_STOPPED_SUPERVISION_REPORT == STD_ON)
        Dem_ReportErrorStatus(WdgM_GddEMonitoring, DEM_EVENT_STATUS_FAILED);
        #endif
        #endif
        #if(WDGM_IMMEDIATE_RESET == STD_ON)
        Mcu_PerformReset();
        #else
        SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
        (void)Rte_Switch_globalMode_currentMode(WDGM_GLOBAL_STATUS_STOPPED);
        SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
        #endif
        WdgM_TriggerWdgIf(LpNewMode, WDGM_TM_TIMEOUT);
        LddReturnvalue = E_NOT_OK;
      }
      else
      {
        /* Clear activity flags for all logical supervisions */
        WdgM_ClearActivityFlag(LpNewMode);

        /* Get the total SE's in the new mode */
        LusNewModeTotalSE = WDGM_ZERO;
        /* Get the pointer to WdgM_GaaModexLocalStatus */
        LpNewModeLocalStatus = LpNewMode->pActiveSEList;
        while (LusNewModeTotalSE < LpNewMode->ddTotalSEInMode)
        {
          /* polyspace<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
          /* polyspace<RTE:NIV:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
          /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
          LddSEArrayIndex = LpNewModeLocalStatus[LusNewModeTotalSE].ddSEArrayIndex;

         /* polyspace:begin<RTE:OBAI:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
         /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
          /* Check if the SE in new mode was not activated in old mode */
          if ((WdgM_GaaSEStatus[LddSEArrayIndex] & WDGM_STATUS_MASK) == WDGM_LOCAL_STATUS_DEACTIVATED)
          {
            /* Activate the SE present in the new mode */
            WdgM_GaaSEStatus[LddSEArrayIndex] =
              (WdgM_GaaSEStatus[LddSEArrayIndex] & WDGM_CLEAR_SE)
              | WDGM_LOCAL_STATUS_OK;

            SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
            /* polyspace:begin<RTE:COR:Not a defect:Justify with annotations> function pointer in configured by generator */
            (void)(WdgM_GaaSupervisedEntity[LddSEArrayIndex].pRteSwitchMode)
              (WDGM_LOCAL_STATUS_OK);
            /* polyspace:end<RTE:COR> */
            SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
          }
          else
          {
            /* do_nothing */
          }
          /* polyspace:end<RTE:OBAI> */
          /* polyspace:end<MISRA-C3:18.1> */

          /* Increment the SEs loop count */
          LusNewModeTotalSE++;
        }

        /* Get the pointer to previous mode array */
        LpPrevMode = &WdgM_GaaModes[WdgM_GddCurrentMode];
        /* Get the total SE's in the previous mode */
        LusPrevModeTotalSE = WDGM_ZERO;
        /* Get the pointer to WdgM_GaaModexLocalStatus */
        /* polyspace<RTE:IDP:Not a defect> Its boundary is pre-defined */
        /* polyspace<MISRA-C3:D4.1:Not a defect> Its boundary is pre-defined */
        /* polyspace<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
        LpPrevModeLocalStatus = LpPrevMode->pActiveSEList;
        while (LusPrevModeTotalSE < LpPrevMode->ddTotalSEInMode)
        {
          LblDeactivateFlag = WDGM_TRUE;
          /* Get the pointer to WdgM_GaaModexLocalStatus */
          LpNewModeLocalStatus = LpNewMode->pActiveSEList;
          /* Get the total SE's in the new mode */
          LusNewModeTotalSE = WDGM_ZERO;
          while (LusNewModeTotalSE < LpNewMode->ddTotalSEInMode)
          {
            /* Check if the SE in previous mode is not activated in new mode */
            /* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
            /* polyspace:begin<RTE:NIV:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
            /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
            if ((LpPrevModeLocalStatus[LusPrevModeTotalSE].ddSEArrayIndex)
              == (LpNewModeLocalStatus[LusNewModeTotalSE].ddSEArrayIndex))
            {
              LblDeactivateFlag = WDGM_FALSE;
              LusNewModeTotalSE = LpNewMode->ddTotalSEInMode;
            }
            else
            {
              /* Increment the SEs loop count */
              LusNewModeTotalSE++;
            }
            /* polyspace:end<RTE:IDP> */
            /* polyspace:end<RTE:NIV> */
            /* polyspace:end<MISRA-C3:18.1> */
          }

          /* Deactivate if SE not activated in new mode */
          if (LblDeactivateFlag == WDGM_TRUE)
          {
            /* polyspace<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
            /* polyspace<RTE:NIV:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
            /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
            LddSEArrayIndex = LpPrevModeLocalStatus[LusPrevModeTotalSE].ddSEArrayIndex;

            /* De-Activate the SE not present in the new mode */
            /* polyspace:begin<RTE:OBAI:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
            /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
            WdgM_GaaSEStatus[LddSEArrayIndex] =
              ((WdgM_GaaSEStatus[LddSEArrayIndex] & WDGM_CLEAR_SE)
              | WDGM_SET_ALLSUPVSN_CORRECT) | WDGM_LOCAL_STATUS_DEACTIVATED;
            /* polyspace:end<RTE:OBAI> */
            /* polyspace:end<MISRA-C3:18.1> */

            #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
            /* Reset failure cycle counter */
            WdgM_GddFailedRefCycleCounter[LddSEArrayIndex] = WDGM_ZERO;
            #endif

            SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
            /* polyspace:begin<RTE:COR:Not a defect:Justify with annotations> function pointer in configured by generator */
            /* polyspace:begin<RTE:OBAI:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
            /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
            (void)(WdgM_GaaSupervisedEntity[LddSEArrayIndex].pRteSwitchMode)
              (WDGM_LOCAL_STATUS_DEACTIVATED);
            /* polyspace:end<RTE:COR> */
            /* polyspace:end<RTE:OBAI> */
            /* polyspace:end<MISRA-C3:18.1> */
            SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
          }
          LusPrevModeTotalSE++;
        }
        WdgM_GddCurrentMode = ddMode;

        WdgM_TriggerWdgIf(LpNewMode, WDGM_TM_NORMAL);
      }
    }
    else
    {
    }

    SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
  }
  
  return (LddReturnvalue);
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : WdgM_GetMode                                        **
**                                                                            **
** Service ID           : 0x0b                                                **
**                                                                            **
** Description          : This service Returns the current mode of WdgM       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pMode                                               **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Watchdog Manager should be initialized              **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        WdgM_GblModuleInitStatus,                           **
**                        WdgM_GddCurrentMode                                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,      **
**                        SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION        **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, WDGM_CODE) WdgM_GetMode(
  P2VAR(WdgM_ModeType, WDGM_DATA, WDGM_APPL_DATA) pMode)
{
  /* Local variable for return value */
  Std_ReturnType LddReturnvalue;

  LddReturnvalue = E_OK;

  #if (WDGM_DEV_ERROR_DETECT == STD_ON)
  /* Det Check for module initialization*/
  if (WdgM_GblModuleInitStatus == WDGM_UNINITIALIZED)
  {
    /* Report to DET  */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_GETMODE_SID, WDGM_E_NO_INIT);
    /* Set return value to E_NOT_OK */
    LddReturnvalue = E_NOT_OK;
  }
  /* Det Check for NULL pointer */
  /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> NULL pointer check */
  if (pMode == NULL_PTR)
  {
    /* Report to DET  */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_GETMODE_SID, WDGM_E_INV_POINTER);
    /* Set return value to E_NOT_OK */
    LddReturnvalue = E_NOT_OK;
  }
  /* polyspace:end<RTE:UNR> */
  /* Check the return value */
  #endif /* #if (WDGM_DEV_ERROR_DETECT == STD_ON) */
  if (LddReturnvalue == E_OK)
  {
    SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();

    /* Store the current mode into provided pointer */
    /* polyspace<MISRA-C3:D4.14:Not a defect:Justify with annotations> alredy pointer check is done */
    *pMode = WdgM_GddCurrentMode;

    SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
  }

  return (LddReturnvalue);
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : WdgM_CheckpointReached                              **
**                                                                            **
** Service ID           : 0x0e                                                **
**                                                                            **
** Description          : Indicates to the WdgM that a checkpoint within      **
**                        a supervised entity has been reached                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ddSEID, ddCheckpointID                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Watchdog Manager should be initialized              **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        WdgM_GblModuleInitStatus,                           **
**                        WdgM_GaaSupervisedEntity                            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        WdgM_SEIndexBinarySearch,                           **
**                        WdgM_SEIDBinarySearch,                              **
**                        WdgM_PerformAliveIndication,                        **
**                        WdgM_PerformDeadlineSupervision,                    **
**                        WdgM_PerformIntLogicalSupervision,                  **
**                        WdgM_PerformExtLogicalSupervision                   **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, WDGM_CODE) WdgM_CheckpointReached(
  WdgM_SupervisedEntityIdType ddSEID, WdgM_CheckpointIdType ddCheckpointID)
{
  /* Local pointer for the pointing to the SE array */
  P2CONST(WdgM_SupervisedEntityType, AUTOMATIC, WDGM_CONST) LpSupervisedEntity;
  /* Local pointer for the pointing to SE in the current mode */
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST) LpSEPtr;
  /* Index for looping through Localstatusparam structure array */
  WdgM_SupervisedEntityIndexType LddSEArrayIndex;
  /* Local variable for return value */
  Std_ReturnType LddReturnvalue;
  boolean LblReturn;
  /* Local variable for storing total checkpoints in the corresponding SE */
  #if(WDGM_DEV_ERROR_DETECT == STD_ON)
  WdgM_CheckpointIdType LddTotalCheckpoints;
  #endif

  LddReturnvalue = E_OK;
  LddSEArrayIndex = WDGM_ZERO;

  #if (WDGM_DEV_ERROR_DETECT == STD_ON)
  /* Det Check for module initialization*/
  if (WdgM_GblModuleInitStatus == WDGM_UNINITIALIZED)
  {
    /* Report to DET  */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_CHECKPOINTREACHED_SID, WDGM_E_NO_INIT);
    /* Set return value to E_NOT_OK since module is not initialized */
    LddReturnvalue = E_NOT_OK;
  }
  #endif

  /* Get the pointer to the actual SEIndex array */
  LblReturn = WdgM_SEIndexBinarySearch(ddSEID, &LddSEArrayIndex);
  #if (WDGM_DEV_ERROR_DETECT == STD_ON)
  if (LblReturn != WDGM_TRUE)
  {
    /* Report to DET  */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_CHECKPOINTREACHED_SID, WDGM_E_PARAM_SEID);
    /* Return the E_NOT_OK since SE is invalid */
    LddReturnvalue = E_NOT_OK;
  }
  #else
  (void)(LblReturn);
  #endif

  LpSupervisedEntity = &WdgM_GaaSupervisedEntity[LddSEArrayIndex];
  #if (WDGM_DEV_ERROR_DETECT == STD_ON)
  /* polyspace<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
  /* polyspace<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
  LddTotalCheckpoints = LpSupervisedEntity->ddTotalCheckpoints;
  if (ddCheckpointID >= LddTotalCheckpoints)
  {
    /* Report to DET  */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_CHECKPOINTREACHED_SID, WDGM_E_CPID);
    /* Return the E_NOT_OK since CP is invalid */
    LddReturnvalue = E_NOT_OK;
  }
  #endif

  /* Check the return value */
  if (LddReturnvalue == E_OK)
  {
    /* Check whether SE is active in current mode or not */
    LpSEPtr = WdgM_SEIDBinarySearch(ddSEID);
    if (LpSEPtr != NULL_PTR)
    {
      /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> check each feature is enabled */
      #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
      if ((LpSupervisedEntity->ucSupervisions & WDGM_B0_AS) == WDGM_B0_AS)
      {
        WdgM_PerformAliveIndication(ddSEID, ddCheckpointID);
      }
      #endif /* #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON) */

      #if(WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)
      if ((LpSupervisedEntity->ucSupervisions & WDGM_B1_DS) == WDGM_B1_DS)
      {
        /* Perform deadline monitoring for the requested checkpoint */
        WdgM_PerformDeadlineSupervision(ddSEID, ddCheckpointID,
          LpSEPtr->ddSEArrayIndex);
      }
      #endif

      #if(WDGM_ENABLE_INTERNAL_TRANSITION == STD_ON)
      /* ILS Algorithm */
      if ((LpSupervisedEntity->ucSupervisions & WDGM_B2_ILS) == WDGM_B2_ILS)
      {
        /* Perform internal logical supervision for the requested checkpoint */
        WdgM_PerformIntLogicalSupervision(ddCheckpointID,
          LpSEPtr->ddSEArrayIndex);
      }
      #endif

      #if(WDGM_ENABLE_EXTERNAL_TRANSITION == STD_ON)
      if ((LpSupervisedEntity->ucSupervisions & WDGM_B3_ELS) == WDGM_B3_ELS)
      {
        /* Perform external logical supervision for the requested checkpoint */
        WdgM_PerformExtLogicalSupervision(ddSEID, ddCheckpointID,
          LpSEPtr->ddSEArrayIndex);
      }
      #endif
      /* polyspace:end<RTE:UNR> */
    }
    /* Is Det reporting enabled */
    #if (WDGM_DEV_ERROR_DETECT == STD_ON)
    else
    {
      /* Report to DET  */
      (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
        WDGM_CHECKPOINTREACHED_SID, WDGM_E_SEDEACTIVATED);
      /* Return the E_NOT_OK since SE not configured */
      LddReturnvalue = E_NOT_OK;
    }
    #endif
  }

  return (LddReturnvalue);
}

#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : WdgM_UpdateAliveCounter                             **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : This service is deprecated and it is provided only  **
**                        for backward compatibility                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ddSEID                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Watchdog Manager should be initialized              **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        WdgM_GblModuleInitStatus,                           **
**                        WdgM_GaaSupervisedEntity,                           **
**                        WdgM_GaaModes,                                      **
**                        WdgM_GddCurrentMode                                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        WdgM_SEIndexBinarySearch,                           **
**                        WdgM_SEIDBinarySearch,                              **
**                        WdgM_PerformAliveIndication                         **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, WDGM_CODE)
  WdgM_UpdateAliveCounter(WdgM_SupervisedEntityIdType ddSEID)
{
  /* Index for looping through Localstatusparam structure array */
  WdgM_SupervisedEntityIndexType LddSEArrayIndex;
  /* Local variable for return value */
  Std_ReturnType LddReturnvalue;
  boolean LblReturn;
  #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
  /* Local pointer for the pointing to SE in the current mode */
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST) LpSEPtr;
  /* Local pointer for the pointing to the SE array */
  P2CONST(WdgM_SupervisedEntityType, AUTOMATIC, WDGM_CONST) LpSupervisedEntity;
  /* Local pointer for the pointing to the current mode */
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) LpModes;
  /* Local pointer for the pointing to alive supervision array */
  P2CONST(WdgM_AliveSupervisionType, AUTOMATIC, WDGM_CONST) LpAliveSupervisions;
  #if(WDGM_DEV_ERROR_DETECT == STD_ON)
  /* Local variable for total alive supervisions in the current mode */
  uint16 LusTotalAliveSupervisions;
  #endif
  #endif

  LddReturnvalue = E_OK;
  LddSEArrayIndex = WDGM_ZERO;

  #if (WDGM_DEV_ERROR_DETECT == STD_ON)
  /* Det Check for module initialization*/
  if (WdgM_GblModuleInitStatus == WDGM_UNINITIALIZED)
  {
    /* Report to DET  */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_UPDATEALIVECOUNTER_SID, WDGM_E_NO_INIT);
    /* Set return value to E_NOT_OK */
    LddReturnvalue = E_NOT_OK;
  }
  #endif

  /* Get the pointer to the actual SEIndex array */
  LblReturn = WdgM_SEIndexBinarySearch(ddSEID, &LddSEArrayIndex);
  #if (WDGM_DEV_ERROR_DETECT == STD_ON)
  if (LblReturn != WDGM_TRUE)
  {
    /* Report to DET  */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_UPDATEALIVECOUNTER_SID, WDGM_E_PARAM_SEID);
    /* Return the E_NOT_OK since SE not configured */
    LddReturnvalue = E_NOT_OK;
  }
  #else
  (void)(LblReturn);
  #endif

  /* Check the return value */
  if (LddReturnvalue == E_OK)
  {
    #if (WDGM_DEV_ERROR_DETECT == STD_ON)
    /* Det Check for checking deprecated API */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_UPDATEALIVECOUNTER_SID, WDGM_E_DEPRECATED);
    #endif

    #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
    /* Check whether SE is active in current mode or not */
    LpSEPtr = WdgM_SEIDBinarySearch(ddSEID);
    if (LpSEPtr != NULL_PTR)
    {
      LpSupervisedEntity = &WdgM_GaaSupervisedEntity[LddSEArrayIndex];

      /* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
      /* polyspace:begin<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
      /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> range check */
      if ((LpSupervisedEntity->ucSupervisions & WDGM_B0_AS) == WDGM_B0_AS)
      {
        LpModes = &WdgM_GaaModes[WdgM_GddCurrentMode];
        LpAliveSupervisions = LpModes->pAliveSupervisions;

        #if (WDGM_DEV_ERROR_DETECT == STD_ON)
        LusTotalAliveSupervisions = LpModes->usTotalAliveSupervisions;
        if (LusTotalAliveSupervisions > WDGM_ONE)
        {
          /* Report the error to Det if more than one alivesupervision is
            configured in the current mode */
          (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
            WDGM_UPDATEALIVECOUNTER_SID, WDGM_E_AMBIGIOUS);
        }
        else
        #endif
        {
          /* Match SE and CP in AliveSupervisions list */
          /* polyspace:begin<RTE:NIV:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
          if (ddSEID == LpAliveSupervisions->ddSEId)
          {
            WdgM_PerformAliveIndication(ddSEID, LpAliveSupervisions->ddCheckpoint);
          }
          /* polyspace:end<RTE:NIV> */
        }
      }
      /* polyspace:end<RTE:IDP> */
      /* polyspace:end<MISRA-C3:18.1> */
      /* polyspace:end<RTE:UNR> */
    }
    /* Is Det reporting enabled */
    #if (WDGM_DEV_ERROR_DETECT == STD_ON)
    else
    {
      /* Report to DET  */
      (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
        WDGM_UPDATEALIVECOUNTER_SID, WDGM_E_SEDEACTIVATED);
      /* Return the E_NOT_OK since SE not configured */
      LddReturnvalue = E_NOT_OK;
    }
    #endif
    #endif
  }

  return (LddReturnvalue);
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : WdgM_GetLocalStatus                                 **
**                                                                            **
** Service ID           : 0x0c                                                **
**                                                                            **
** Description          : This service provides the supervision status of an  **
**                        individual supervised entity                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ddSEID                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pStatus                                             **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Watchdog Manager should be initialized              **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        WdgM_GblModuleInitStatus,                           **
**                        WdgM_GaaSEStatus                                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        WdgM_SEIndexBinarySearch,                           **
**                        SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,      **
**                        SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION        **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, WDGM_CODE) WdgM_GetLocalStatus(
  WdgM_SupervisedEntityIdType ddSEID,
  P2VAR(WdgM_LocalStatusType, WDGM_DATA, WDGM_APPL_DATA) pStatus)
{
  WdgM_SupervisedEntityIndexType LddSEArrayIndex = WDGM_ZERO;
  /* Local variable for return value */
  Std_ReturnType LddReturnvalue;
  boolean LblReturn;

  LddReturnvalue = E_OK;

  #if (WDGM_DEV_ERROR_DETECT == STD_ON)
  /* Det Check for module initialization*/
  if (WdgM_GblModuleInitStatus == WDGM_UNINITIALIZED)
  {
    /* Report to DET  */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_GETLOCALSTATUS_SID, WDGM_E_NO_INIT);
    /* Set return value to E_NOT_OK */
    LddReturnvalue = E_NOT_OK;
  }

  /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> NULL pointer check */
  /* Det Check for NULL pointer */
  if (pStatus == NULL_PTR)
  {
    /* Report to DET  */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_GETLOCALSTATUS_SID, WDGM_E_INV_POINTER);
    /* Set return value to E_NOT_OK */
    LddReturnvalue = E_NOT_OK;
  }
  /* polyspace:end<RTE:UNR> */
  #endif

  /* Get the pointer to the actual SEIndex array */
  LblReturn = WdgM_SEIndexBinarySearch(ddSEID, &LddSEArrayIndex);
  #if (WDGM_DEV_ERROR_DETECT == STD_ON)
  if (LblReturn != WDGM_TRUE)
  {
    /* Report to DET  */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_GETLOCALSTATUS_SID, WDGM_E_PARAM_SEID);
    /* Return the E_NOT_OK since SE not configured */
    LddReturnvalue = E_NOT_OK;
  }
  #else
  (void)(LblReturn);
  #endif

  /* Check the return value */
  if (LddReturnvalue == E_OK)
  {
    SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();

    /* Update the Local status */
    /* polyspace<MISRA-C3:D4.14:Not a defect:Justify with annotations> alredy pointer check is done */
    *pStatus = (WdgM_LocalStatusType)(WdgM_GaaSEStatus[LddSEArrayIndex] & WDGM_STATUS_MASK);

    SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
  }

  return (LddReturnvalue);
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : WdgM_GetGlobalStatus                                **
**                                                                            **
** Service ID           : 0x0d                                                **
**                                                                            **
** Description          : This service provides global supervision status of  **
**                        WdgM                                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pStatus                                             **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Watchdog Manager should be initialized              **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        WdgM_GblModuleInitStatus,                           **
**                        WdgM_GddGlobalSupervisionStatus                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,      **
**                        SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION        **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, WDGM_CODE) WdgM_GetGlobalStatus
  (P2VAR(WdgM_GlobalStatusType, WDGM_DATA, WDGM_APPL_DATA) pStatus)
{
  /* Local variable for return value */
  Std_ReturnType LddReturnvalue;

  LddReturnvalue = E_OK;

  #if (WDGM_DEV_ERROR_DETECT == STD_ON)
  /* Det Check for module initialization*/
  if (WdgM_GblModuleInitStatus == WDGM_UNINITIALIZED)
  {
    /* Report to DET  */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_GETGLOBALSTATUS_SID, WDGM_E_NO_INIT);
    /* Set return value to E_NOT_OK */
    LddReturnvalue = E_NOT_OK;
  }

  /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> NULL pointer check */
  /* Det Check for NULL pointer */
  if (pStatus == NULL_PTR)
  {
    /* Report to DET  */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_GETGLOBALSTATUS_SID, WDGM_E_INV_POINTER);
    /* Set return value to E_NOT_OK */
    LddReturnvalue = E_NOT_OK;
  }
  /* polyspace:end<RTE:UNR> */
  #endif

  /* Check the return value */
  if (LddReturnvalue == E_OK)
  {
    SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();

    /* Store the global supervision status into the input pointer */
    /* polyspace<MISRA-C3:D4.14:Not a defect:Justify with annotations> alredy pointer check is done */
    *pStatus = WdgM_GddGlobalSupervisionStatus;

    SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
  }

  return (LddReturnvalue);
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : WdgM_PerformReset                                   **
**                                                                            **
** Service ID           : 0x0f                                                **
**                                                                            **
** Description          : This service instructs the WdgM to initiate         **
**                        a watchdog reset                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Watchdog Manager should be initialized              **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        WdgM_GblModuleInitStatus,                           **
**                        WdgM_GaaModes,                                      **
**                        WdgM_GddCurrentMode,                                **
**                        WdgM_GddGlobalSupervisionStatus,                    **
**                        WdgM_GddInvGlobalSupervisionStatus                  **
**                        WdgM_GddEMonitoring                                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        Dem_ReportErrorStatus,                              **
**                        Mcu_PerformReset,                                   **
**                        Rte_Switch_globalMode_currentMode,                  **
**                        WdgM_TriggerWdgIf,                                  **
**                        SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,      **
**                        SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION        **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_PerformReset(void)
{
  /* Local pointer for the pointing to the current mode */
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST)LpMode;

  #if (WDGM_DEV_ERROR_DETECT == STD_ON)
  /* Det Check for module initialization*/
  if (WdgM_GblModuleInitStatus == WDGM_UNINITIALIZED)
  {
    /* Report to DET  */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_PERFORMRESET_SID, WDGM_E_NO_INIT);
  }
  else
  #endif
  {
    /* Get the address of currentMode from the Mode structure array into the
      global pointer */
    SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
    WdgM_GddGlobalSupervisionStatus = WDGM_GLOBAL_STATUS_STOPPED;
    WdgM_GddInvGlobalSupervisionStatus = ~WdgM_GddGlobalSupervisionStatus;
    SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
    #if(WDGM_DEM_ERROR_REPORT == STD_ON)
    #if(WDGM_DEM_STOPPED_SUPERVISION_REPORT == STD_ON)
    Dem_ReportErrorStatus(WdgM_GddEMonitoring, DEM_EVENT_STATUS_FAILED);
    #endif
    #endif
    #if(WDGM_IMMEDIATE_RESET == STD_ON)
    Mcu_PerformReset();
    #else
    /* Report global state to Rte after every supervision cycle */
    (void)Rte_Switch_globalMode_currentMode(WDGM_GLOBAL_STATUS_STOPPED);
    #endif
    LpMode = &WdgM_GaaModes[WdgM_GddCurrentMode];
    WdgM_TriggerWdgIf(LpMode, WDGM_TM_TIMEOUT);
  }
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : WdgM_GetFirstExpiredSEID                            **
**                                                                            **
** Service ID           : 0x10                                                **
**                                                                            **
** Description          : This service returns SEID that first reached the    **
**                        state WDGM_LOCAL_STATUS_EXPIRED                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pSEID                                               **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        WdgM_GddFirstExpiredSEID,                           **
**                        WdgM_GddInvFirstExpiredSEID                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,      **
**                        SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION        **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, WDGM_CODE) WdgM_GetFirstExpiredSEID(
  P2VAR(WdgM_SupervisedEntityIdType, WDGM_DATA, WDGM_APPL_DATA) pSEID)
{
  WdgM_SupervisedEntityIdType LddInvFirstExpiredSEID;
  /* Local variable for return value */
  Std_ReturnType LddReturnvalue;

  LddReturnvalue = E_OK;

  /* Is Det reporting enabled */
  #if (WDGM_DEV_ERROR_DETECT == STD_ON)

  /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> NULL pointer check */
  /* Det Check for NULL pointer */
  if (pSEID == NULL_PTR)
  {
    /* Report to DET  */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_GETFIRSTEXPIRED_SEID_SID, WDGM_E_INV_POINTER);
    /* Set return value to E_NOT_OK */
    LddReturnvalue = E_NOT_OK;
  }
  else
  #endif
  {
    SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();

    /* Check whether double inverse value match */
    LddInvFirstExpiredSEID = ~WdgM_GddInvFirstExpiredSEID;
    if (WdgM_GddFirstExpiredSEID == LddInvFirstExpiredSEID)
    {
      /* Write the first expired SEID value in the out pointer */
      /* polyspace<MISRA-C3:D4.14:Not a defect:Justify with annotations> alredy pointer check is done */
      *pSEID = WdgM_GddFirstExpiredSEID;
    }
    else
    {
      /* Write zero incase double inverse value does not match */
      /* polyspace<MISRA-C3:D4.14:Not a defect:Justify with annotations> alredy pointer check is done */
      *pSEID = WDGM_ZERO;
      /* Set return value to E_NOT_OK */
      LddReturnvalue = E_NOT_OK;
    }

    SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
  }
  /* polyspace:end<RTE:UNR> */

  return (LddReturnvalue);
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : WdgM_MainFunction                                   **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : This service performs the processing of the cyclic  **
**                        Watchdog Manager jobs.                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Watchdog Manager should be initialized              **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        WdgM_GblModuleInitStatus                            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        WdgM_PerformAliveSupervision,                       **
**                        WdgM_EvaluateLocalStatus,                           **
**                        WdgM_EvaluateGlobalStatus                           **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_MainFunction(void)
{
  boolean LblSEExpiredFlag = WDGM_FALSE;
  boolean LblSEFailedFlag = WDGM_FALSE;

  #if (WDGM_DEV_ERROR_DETECT == STD_ON)
  /* Det Check for module initialization*/
  if (WdgM_GblModuleInitStatus == WDGM_UNINITIALIZED)
  {
    /* Report to DET  */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_MAINFUNCTION_SID, WDGM_E_NO_INIT);
  }
  else
  #endif
  {
    #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
    WdgM_PerformAliveSupervision();
    #endif

    /* Evaluate the local supervision status */
    WdgM_EvaluateLocalStatus(&LblSEFailedFlag, &LblSEExpiredFlag);

    /* Evaluate the global supervision status */
    WdgM_EvaluateGlobalStatus(LblSEFailedFlag, LblSEExpiredFlag);
  }
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : WdgM_GetErrorInfo                                   **
**                                                                            **
** Service ID           : 0xa0                                                **
**                                                                            **
** Description          : This service returns ErrorInfo.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : ddSEID                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pErrorInfo                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        WdgM_GaaErrorInfo                                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,      **
**                        SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION        **
*******************************************************************************/
#if(WDGM_ERROR_INFO_API == STD_ON)
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, WDGM_CODE) WdgM_GetErrorInfo(
  WdgM_SupervisedEntityIdType ddSEID,
  P2VAR(WdgM_ErrorInfoType, WDGM_DATA, WDGM_APPL_DATA) pErrorInfo)
{
  WdgM_SupervisedEntityIndexType LddSEArrayIndex = WDGM_ZERO;
  /* Local variable for return value */
  Std_ReturnType LddReturnvalue;
  boolean LblReturn;

  LddReturnvalue = E_OK;

  /* Get the pointer to the actual SEIndex array */
  LblReturn = WdgM_SEIndexBinarySearch(ddSEID, &LddSEArrayIndex);
  #if (WDGM_DEV_ERROR_DETECT == STD_ON)
  if (LblReturn != WDGM_TRUE)
  {
    /* Report to DET  */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_GETERRORINFO_SID, WDGM_E_PARAM_SEID);
    /* Return the E_NOT_OK since SE is invalid */
    LddReturnvalue = E_NOT_OK;
  }

  /* Det Check for NULL pointer */
  if (pErrorInfo == NULL_PTR)
  {
    /* Report to DET  */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_GETERRORINFO_SID, WDGM_E_INV_POINTER);
    /* Set return value to E_NOT_OK */
    LddReturnvalue = E_NOT_OK;
  }
  #else
  (void)(LblReturn);
  #endif

  if (LddReturnvalue == E_OK)
  {
    SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();

    pErrorInfo->ddSEId = WdgM_GaaErrorInfo[LddSEArrayIndex].ddSEId;
    pErrorInfo->ddStatus = WdgM_GaaErrorInfo[LddSEArrayIndex].ddStatus;
    pErrorInfo->ddSupervision = WdgM_GaaErrorInfo[LddSEArrayIndex].ddSupervision;
    pErrorInfo->ddCheckpoint = WdgM_GaaErrorInfo[LddSEArrayIndex].ddCheckpoint;

    SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
  }

  return (LddReturnvalue);
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : WdgM_PmModeChange                                   **
**                                                                            **
** Service ID           : 0xa1                                                **
**                                                                            **
** Description          : This service instructs the Watchdog Manager to      **
**                        change Wdg mode depending requested mode.           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : ddReqMode                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        WdgM_GaaModes,                                      **
**                        WdgM_GddCurrentMode                                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        WdgIf_SetMode,                                      **
**                        WdgIf_SetTriggerCondition                           **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, WDGM_CODE) WdgM_PmModeChange(
  WdgM_ChangeModeIntReqType ddReqMode)
{
  /* Get the pointer to current mode */
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) LpCurrentMode;
  /* Local variable for return value */
  Std_ReturnType LddReturnvalue;
  uint8 LucCount;
  #if(WDGM_ENABLE_TRIGGER == STD_ON)
  P2CONST(WdgM_TriggerType, AUTOMATIC, WDGM_CONST) LpTriggers;
  #endif

  LddReturnvalue = E_OK;

  /* Get the pointer to previous mode array */
  LpCurrentMode = &WdgM_GaaModes[WdgM_GddCurrentMode];

  #if (WDGM_DEV_ERROR_DETECT == STD_ON)
  /* Det Check for module initialization*/
  if (WdgM_GblModuleInitStatus == WDGM_UNINITIALIZED)
  {
    /* Report to DET  */
    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
      WDGM_CHANGEMODEINT_SID, WDGM_E_NO_INIT);
    LddReturnvalue = E_NOT_OK;
  }

  #if((WDGM_OFF_MODE_ENABLED == STD_OFF) && (WDGM_ENABLE_TRIGGER == STD_ON))
  /* Update the pointer to first element of Trigger structure array */
  LpTriggers = LpCurrentMode->pTriggers;
  LucCount = WDGM_ZERO;
  /* Loop running through all configured watchdog drivers */
  while (LucCount < LpCurrentMode->ucTotalTriggers)
  {
    if ((LpTriggers[LucCount].ddWdgIfMode) == WDGIF_OFF_MODE)
    {
      /* Report to DET */
      (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID,
        WDGM_CHANGEMODEINT_SID, WDGM_E_DISABLE_NOT_ALLOWED);
      /* Update Global Initialization Status to Uninitialized */
      LucCount = LpCurrentMode->ucTotalTriggers;
      LddReturnvalue = E_NOT_OK;
    }
    else
    {
      /* Increment the watchdog count */
      LucCount++;
    }
  }
  #endif
  #endif

  if (LddReturnvalue == E_OK)
  {
    #if(WDGM_ENABLE_TRIGGER == STD_ON)
    /* Get the pointer to watchdog trigger array */
    /* polyspace<RTE:IDP:Not a defect> Its boundary is pre-defined */
    /* polyspace<MISRA-C3:D4.1:Not a defect> Its boundary is pre-defined */
    /* polyspace<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
    LpTriggers = LpCurrentMode->pTriggers;
    LucCount = WDGM_ZERO;
    /* Loop running through all configured watchdog drivers */
    while (LucCount < LpCurrentMode->ucTotalTriggers)
    {
      /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> default is need for misra-c */
      switch (ddReqMode)
      {
      case WDGM_CMR_WDG_OFF:
      case WDGM_PM_MODE_LP_REQ:
        /* Set the Watchdog mode for all the configured drivers */
        /* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
        /* polyspace:begin<RTE:NIV:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
        /* polyspace:begin<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
        LddReturnvalue = WdgIf_SetMode(LpTriggers[LucCount].ucWdgIfDeviceId, WDGIF_OFF_MODE);
        /* polyspace:end<RTE:IDP> */
        /* polyspace:end<RTE:NIV> */
        /* polyspace:end<MISRA-C3:18.1> */
        break;

      case WDGM_CMR_WDG_RESTART:
      case WDGM_PM_MODE_HP_REQ:
        /* Set the Watchdog mode for all the configured drivers */
        /* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
        /* polyspace:begin<RTE:NIV:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
        /* polyspace:begin<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
        LddReturnvalue = WdgIf_SetMode(LpTriggers[LucCount].ucWdgIfDeviceId, LpTriggers[LucCount].ddWdgIfMode);
        WdgIf_SetTriggerCondition(LpTriggers[LucCount].ucWdgIfDeviceId, LpTriggers[LucCount].usWdgIfTimeout);
        /* polyspace:end<RTE:IDP> */
        /* polyspace:end<RTE:NIV> */
        /* polyspace:end<MISRA-C3:18.1> */
        break;

      default:
        LddReturnvalue = E_NOT_OK;
        break;
      }
      /* polyspace:end<RTE:UNR> */

      if(LddReturnvalue == E_NOT_OK)
      {
        LucCount = LpCurrentMode->ucTotalTriggers;
      }
      else
      {
        LucCount++;
      }
    }
    #endif
  }

  return LddReturnvalue;
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
