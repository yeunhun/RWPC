/*******************************************************************************
**                                                                            **
**  (C) 2015 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: WdgM_Internal.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR WDGM                                                  **
**                                                                            **
**  PURPOSE   : Watchdog Manager internal API Functionality                   **
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
** 1.2.14    15-Mar-2019   YH.Han       Redmine #14572, #16411                **
** 1.2.13    04-Dec-2018   YH.Han       Redmine #14965                        **
** 1.2.12    30-Mar-2018   YH.Han       Redmine #11171                        **
** 1.0.20    11-Sep-2015   Sinil        1. Justify runtime error              **
** 1.0.19    20-Aug-2015   Sinil        1. Follow function prototype argument **
**                                      naming rule                           **
**                                      2. Remove unreached code              **
** 1.0.18    23-Apr-2015   Sinil        1. Fix Misra-c rule violations        **
** 1.0.17    27-Jan-2015   Sinil        1. Remove unnecessary comment for     **
**                                      polyspace                             **
** 1.0.16    12-Nov-2014   Sinil        1. Fix code and comment for polyspace **
** 1.0.15    03-Nov-2014   Sinil        1. Update Rte notification related to **
**                                      immediate MCU reset                   **
**                                      2. Change WdgM_GbaAlreadyUpdated to   **
**                                      WdgM_GaaAlreadyUpdated                **
**                                      3. Update using OsCounter in SE       **
**                                      4. Change ddCounterID to pCounterID   **
** 1.0.14    28-Oct-2014   Sinil        1. Fix not used variable warning      **
** 1.0.13    22-Oct-2014   Sinil        1. Func WdgM_PerformAliveIndication   **
**                                      and WdgM_EvaluateLocalStatus added    **
**                                      2. Adjust protected sections          **
**                                      3. Add stopping update status after   **
**                                      an irrecoverable error occurs         **
**                                      4. Add preserving error info          **
**                                      5. Adjust precompile options          **
**                                      6. Remove initilizing                 **
**                                      WdgM_GddExpSupervisionCycleCounter    **
**                                      from WdgM_ClearActivityFlag           **
**                                      7. Change including                   **
**                                      8. Rearrange items and change naming  **
** 1.0.12    07-Oct-2014   Sinil        1. Change WdgM_TriggerWdgIf argument  **
**                                      2. Fix performing internal logical    **
**                                      supervision                           **
** 1.0.11    30-Sep-2014   Sinil        1. Change using OsCounter             **
**                                      2. Remove Wdgm_PerformTimeStamping    **
**                                      3. Fix exclusive area protection pair **
** 1.0.10    02-Sep-2014   Sinil        Fix loop counter in                   **
**                                        WdgM_PerformAliveSupervision        **
** 1.0.9     28-Jan-2014   Sinil        TaskID:811                            **
**                                      1. Change usTotalSEInMode to          **
**                                      ddTotalSEInMode                       **
** 1.0.8     03-Jan-2014   Sinil        TaskID:809                            **
**                                      1. Variable type changed              **
**                                      2. Include header changed             **
** 1.0.7     16-Dec-2013   Sinil        Wdgm_Dem_Cfg.h was included and       **
**                                        related macro's adjusted            **
**                                      Change the count for internal logical **
**                                        transitions                         **
** 1.0.6     10-Jun-2013   Sinil        CR 127 : Change some macros to const  **
**                                        variables for making library        **
** 1.0.5     05-Jun-2013   Sinil        CR 128 : Fix the problem that         **
**                                        WdgM_PerformDeadlineMonitoring      **
**                                        can't get OsCounter value caused by **
**                                        interrupt lock                      **
**                                      CR 128 : Fix global status changing   **
**                                        event calls are skipped because of  **
**                                        supending interrupts                **
** 1.0.4     28-May-2013   Sinil        WdgM_TriggerWdgIf is used in          **
**                                        WdgM_SetMode func without           **
**                                        reinitializing LpTriggers. So it's  **
**                                        changed to use triggers of          **
**                                        LpMode and to separate cases for    **
**                                        normal mode and timeout mode        **
**                                        DL_ID:119                           **
**                                      Adjust changed interface of           **
**                                        WdgM_SEIndexBinarySearch func       **
**                                      Add more global variables in          **
**                                        WdgM_ClearActivityFlag func to      **
**                                        initialize                          **
**                                      Remove reassigning LddSEArrayIndex    **
**                                        with the first ddSEArrayIndex of    **
**                                        LpActiveSEList in                   **
**                                        WdgM_PerformDeadlineMonitoring func **
**                                      Add APIs for exclusive area invlolved **
**                                        funcs                               **
**                                      Fix that consecutive result           **
**                                        contaminates previous result in     **
**                                        WdgM_PerformAliveSupervision func.  **
**                                        Refer to WDGM115                    **
**                                        DL_ID:105                           **
** 1.0.0     01-Jan-2013   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Not a Defect] "see MEMMAP003 of AUTOSAR" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "WdgM_Internal.h"    /* Extern Declarations  of internal functions */
#include "Rte_WdgM.h"         /* Rte Header file */
#include "WdgM_Config.h"      /* Extern Declarations  of const variables */
#include "WdgM_Ram.h"         /* WdgM Ram variables header file */
#include "WdgM_GenExterns.h"  /* Extern Declarations  of generated variables */
#include "SchM_WdgM.h"        /* SchM Header file */
#include "WdgIf.h"
#if(WDGM_ENABLE_OS_APPLICATION == STD_ON)
#include "BswM_WdgM.h"        /* BswM  Module header file */
#endif
#if(WDGM_IMMEDIATE_RESET == STD_ON)
#include "Mcu.h"              /* Mcu Header file */
#endif
#if(WDGM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"              /* Det Header file */
#endif
#if(WDGM_DEM_ERROR_REPORT == STD_ON)
#include "WdgM_Dem_Cfg.h"              /* Dem Header file */
#endif

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/
/*******************************************************************************
** Function Name      : WdgM_SEIDBinarySearch                                 **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service gives the supervised entity position     **
**                      in the configured mode                                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ddSEID                                                **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : WdgM_ActiveSEType                                     **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      WdgM_GaaModes,                                        **
**                      WdgM_GddCurrentMode                                   **
**                                                                            **
**                      Function(s) invoked : None                            **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
/* polyspace-begin MISRA-C3:20.7 [Not a Defect] "below macro does not affect the result" */
FUNC(P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST), WDGM_CODE)
  WdgM_SEIDBinarySearch(WdgM_SupervisedEntityIdType ddSEID)
/* polyspace-end MISRA-C3:20.7 */
{
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) LpMode;
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST) LpActiveSE;
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST) LpFirstSEInMode;
  WdgM_SupervisedEntityIdType LddCurrSEId;
  uint16 LusSize;
  uint16 LusLow;
  uint16 LusHigh;
  uint16 LusMid;

  /* Get the pointer to previous mode array */
  LpMode = &WdgM_GaaModes[WdgM_GddCurrentMode];
  /* Get the total SE's in the previous mode */
  /* polyspace<RTE:IDP:Not a defect> Its boundary is pre-defined */
  /* polyspace<MISRA-C3:D4.1:Not a defect> Its boundary is pre-defined */
  /* polyspace<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
  LusSize = LpMode->ddTotalSEInMode;
  /* Get the pointer to WdgM_GaaModexLocalStatus */
  LpFirstSEInMode = LpMode->pActiveSEList;

  LusHigh = LusSize - WDGM_ONE;
  /* Initialize LusLow  variable with one */
  LusLow  = WDGM_ONE;
  /* Initialize return value with null pointer */
  LpActiveSE = NULL_PTR;
  /* Get the lower limit of SEID */
  /* polyspace<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
  /* polyspace<RTE:NIV:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
  /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
  LddCurrSEId = LpFirstSEInMode->ddSEId;
  /* Check whether search SEID is in range */
  /* polyspace<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
  /* polyspace<RTE:NIV:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
  /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
  if ((ddSEID >= LddCurrSEId) && (ddSEID <= LpFirstSEInMode[LusHigh].ddSEId))
  {
    /* Check whether requested SEID is same as first SEID of the list */
    /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> status check */
    if (ddSEID != LddCurrSEId)
    {
      do
      {
        /* Get the middle index number */
        LusMid = (LusHigh + LusLow) >> WDGM_ONE;
        /* Get the SEID of the mid value in SE array */
        /* polyspace<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
        /* polyspace<RTE:NIV:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
        /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
        LddCurrSEId = LpFirstSEInMode[LusMid].ddSEId;
        /* Compare SEID with the requested one */
        if (LddCurrSEId == ddSEID)
        {
          /* Update the return pointer with the WdgM_GaaModexLocalStatus
            array */
          LpActiveSE = &(LpFirstSEInMode[LusMid]);
          /* Set LusHigh to zero to break the loop */
          LusHigh = WDGM_ZERO;
        }
        else
        {
          /* Compare the SEID with the requested one */
          if (ddSEID < LddCurrSEId)
          {
            /* If the received SEID is lower, update LusHigh */
            LusHigh = LusMid - WDGM_ONE;
          }
          else
          {
            /* If the received SEID is higher, update LusLow  */
            LusLow  = LusMid + WDGM_ONE;
          }
        } /* end if(LddCurrSEId == SEID) */
      } while (LusLow  <= LusHigh);
    } /* if(ddSEID != LddCurrSEId) */
    else
    {
      /* Update the return pointer with the actual SEID mapping structure */
      LpActiveSE = LpFirstSEInMode;
    }
    /* polyspace:end<RTE:UNR> */
  } /* if((ddSEID >= LddCurrSEId) &&... */
  /* Return pointer of SEID*/
  return (LpActiveSE);
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : WdgM_SEIndexBinarySearch                              **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service gives the supervised entity position     **
**                      in the configured mode                                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ddSEID                                                **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : pSEIndex                                              **
**                                                                            **
** Return parameter   : boolean                                               **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      WdgM_GaaSupervisedEntity,                             **
**                      WdgM_GddTotalSEs                                      **
**                                                                            **
**                      Function(s) invoked : None                            **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, WDGM_CODE) WdgM_SEIndexBinarySearch(
  WdgM_SupervisedEntityIdType ddSEID,
  P2VAR(WdgM_SupervisedEntityIndexType, AUTOMATIC, WDGM_DATA) pSEIndex)
{
  P2CONST(WdgM_SupervisedEntityType, AUTOMATIC, WDGM_CONST) LpFirstSE;
  WdgM_SupervisedEntityIdType LddCurrSEId;
  WdgM_SupervisedEntityIndexType LddSize;
  WdgM_SupervisedEntityIndexType LddLow;
  WdgM_SupervisedEntityIndexType LddHigh;
  WdgM_SupervisedEntityIndexType LddMid;
  boolean LblReturn;

  /* If SE is configured then return the value true */
  LblReturn = WDGM_FALSE;
  /* Get the pointer to previous mode array */
  LpFirstSE = &WdgM_GaaSupervisedEntity[WDGM_ZERO];
  /* Get the total SE's in the previous mode */
  LddSize = WdgM_GddTotalSEs;
  /* Initialize LddHigh  variable */
  LddHigh = LddSize - WDGM_ONE;
  /* Initialize LddLow  variable with one */
  LddLow = WDGM_ONE;
  /* Get the lower limit of SEID */
  /* polyspace<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
  /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
  LddCurrSEId = LpFirstSE->ddSEId;
  /* Check whether search SEID is in range */
  /* polyspace<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
  /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
  if ((ddSEID >= LddCurrSEId) && (ddSEID <= LpFirstSE[LddHigh].ddSEId))
  {
    /* Check whether requested SEID is same as first SEID of the list */
    if (ddSEID != LddCurrSEId)
    {
      do
      {
        /* Get the middle index number */
        LddMid = (LddHigh + LddLow) >> WDGM_ONE;

        /* Get the SEID of the middle number */
        LddCurrSEId = LpFirstSE[LddMid].ddSEId;
        /* Compare SEID with the requested one */
        if (LddCurrSEId == ddSEID)
        {
          /* Update the return pointer with the middle index number */
          *pSEIndex = LddMid;
          /* Set LddHigh to zero to break the loop */
          LddHigh = WDGM_ZERO;
        }
        else
        {
          /* Compare the SEID with the requested one */
          /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> range check */
          if (ddSEID < LddCurrSEId)
          {
            /* If the received SEID is lower, update LddHigh */
            LddHigh = LddMid - WDGM_ONE;
          }
          else
          {
            /* If the received SEID is higher, update LddLow  */
            LddLow  = LddMid + WDGM_ONE;
          }
          /* polyspace:end<RTE:UNR> */
        } /* end if(LddCurrSEId == ddSEID) */
      } while (LddLow  <= LddHigh);
    } /* if(ddSEID != LddCurrSEId) */
    else
    {
      /* Update the return pointer with the actual SEID mapping structure */
      *pSEIndex = WDGM_ZERO;
    }
    /* If SE is configured then return the value true */
    LblReturn = WDGM_TRUE;
  } /* if((ddSEID >= LddCurrSEId) &&... */
  /* Return pointer of SEID */
  return (LblReturn);
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : WdgM_InternalSetMode                                  **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service performs the mode switch configured mode **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ddMode                                                **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : boolean                                               **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      WdgM_GaaModes                                         **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      WdgIf_SetMode                                         **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, WDGM_CODE) WdgM_InternalSetMode(WdgM_ModeType ddMode)
{
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) LpMode;
  boolean LblSetModeFailed;
  #if(WDGM_ENABLE_TRIGGER == STD_ON)
  P2CONST(WdgM_TriggerType, AUTOMATIC, WDGM_CONST) LpTriggers;
  /* Local variable for return value */
  Std_ReturnType LddReturnValue;
  uint8 LucCount;
  #endif

  /* Get the pointer to Init mode array */
  LpMode = &WdgM_GaaModes[ddMode];
  LblSetModeFailed = WDGM_FALSE;

  #if(WDGM_ENABLE_TRIGGER == STD_ON)
  /* Get the pointer to watchdog trigger array */
  /* polyspace<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
  /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
  LpTriggers = LpMode->pTriggers;
  LucCount = WDGM_ZERO;
  /* Loop running through all configured watchdog drivers */
  while (LucCount < LpMode->ucTotalTriggers)
  {
    /* Set the Watchdog mode for all the configured drivers */
    /* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    /* polyspace:begin<RTE:NIV:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    LddReturnValue = WdgIf_SetMode(LpTriggers[LucCount].ucWdgIfDeviceId, LpTriggers[LucCount].ddWdgIfMode);
    /* polyspace:end<RTE:IDP> */
    /* polyspace:end<RTE:NIV> */
    /* polyspace:end<MISRA-C3:18.1> */
    if (LddReturnValue == E_NOT_OK)
    {
      LblSetModeFailed = WDGM_TRUE;
      LucCount = LpMode->ucTotalTriggers;
    }
    else
    {
      LucCount++;
    }
  }
  #endif

  return (LblSetModeFailed);
}

#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : WdgM_TriggerWdgIf                                     **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service triggers all the internal watchdogs      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : pMode, ddTriggerMode                                  **
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
**                      WdgM_GusDeInitTimeout                                 **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      WdgIf_SetTriggerCondition                             **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_TriggerWdgIf(
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) pMode,
  WdgM_TriggerModeType ddTriggerMode)
{
  #if(WDGM_ENABLE_TRIGGER == STD_ON)
  P2CONST(WdgM_TriggerType, AUTOMATIC, WDGM_CONST) LpTriggers;
  /* While loop index variable */
  uint8 LucCount;

  /* polyspace<RTE:IDP:Not a defect> Its boundary is pre-defined */
  /* polyspace<MISRA-C3:D4.1:Not a defect> Its boundary is pre-defined */
  /* polyspace<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
  LpTriggers = pMode->pTriggers;
  LucCount = WDGM_ZERO;
  /* Loop running through all configured watchdog drivers to trigger
    with configured timeout value */
  while (LucCount < pMode->ucTotalTriggers)
  {
    /* polyspace:begin<RTE:NIV:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    /* polyspace<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> status check */
    if (LpTriggers[LucCount].ddWdgIfMode != WDGIF_OFF_MODE)
    {
      /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> range check */
      switch (ddTriggerMode)
      {
      case WDGM_TM_NORMAL:
        WdgIf_SetTriggerCondition(LpTriggers[LucCount].ucWdgIfDeviceId,
          LpTriggers[LucCount].usWdgIfTimeout);
        break;
      case WDGM_TM_TIMEOUT:
        WdgIf_SetTriggerCondition(LpTriggers[LucCount].ucWdgIfDeviceId,
          WDGM_ZERO);
        break;
      case WDGM_TM_DEINIT:
        WdgIf_SetTriggerCondition(LpTriggers[LucCount].ucWdgIfDeviceId,
          WdgM_GusDeInitTimeout);
        break;
      default:
        /* do nothing */
        break;
      }
      /* polyspace:end<RTE:UNR> */
    }
    /* polyspace:end<RTE:NIV> */
    /* polyspace:end<RTE:UNR> */

    /* Increment to next watchdog */
    LucCount++;
  }
  #endif
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : WdgM_ClearActivityFlag                                **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service clears global variables                  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : pCurrentMode                                          **
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
**                      WdgM_GblFirstExpSEIDStatus,                           **
**                      WdgM_GddFirstExpiredSEID,                             **
**                      WdgM_GddInvFirstExpiredSEID,                          **
**                      WdgM_GulFreeRunningCounter,                           **
**                      WdgM_GddFailedRefCycleCounter,                        **
**                      WdgM_GaaAliveIndicationStatus,                        **
**                      WdgM_GaaDeadlineSupervisionStatus,                    **
**                      WdgM_GaaSupervisedEntity,                             **
**                      WdgM_GaaIntLogicalSupervisionStatus,                  **
**                      WdgM_GaaExtLogicalSupervisionStatus                   **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,        **
**                      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION          **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_ClearActivityFlag(
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) pCurrentMode)
{
  uint16 LusCount;
  #if(WDGM_ENABLE_INTERNAL_TRANSITION == STD_ON)
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST) LpActiveSE;
  WdgM_IntLogicSupStatArrIndexType LddILSIndex;
  WdgM_SupervisedEntityIndexType LddSEArrayIndex;
  #endif

  SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();

  /* Reset the expired bit to indicate that no SE is in
    WDGM_LOCAL_STATUS_EXPIRED status */
  WdgM_GblFirstExpSEIDStatus = WDGM_FALSE;
  /* Set the NON-Initialized RAM area for storing expired SEID values to
    WDGM_ZERO */
  WdgM_GddFirstExpiredSEID = WDGM_ZERO;
  WdgM_GddInvFirstExpiredSEID = WDGM_ZERO;

  #if(WDGM_ERROR_INFO_API == STD_ON)
  LusCount = pCurrentMode->ddTotalSEInMode;
  while(LusCount != WDGM_ZERO)
  {
    LusCount--;
    WdgM_GaaErrorInfo[LusCount].ddSEId = WDGM_ZERO;
    WdgM_GaaErrorInfo[LusCount].ddStatus = WDGM_LOCAL_STATUS_OK;
    WdgM_GaaErrorInfo[LusCount].ddSupervision = WDGM_ZERO;
    WdgM_GaaErrorInfo[LusCount].ddCheckpoint = WDGM_ZERO;
  }
  #endif

  #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
  /* Clear the Free running counter */
  WdgM_GulFreeRunningCounter = (uint32)WDGM_ZERO;
  /* Set the count to total number of active SE's configured in the current mode */
  /* polyspace<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
  /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
  LusCount = pCurrentMode->ddTotalSEInMode;
  while(LusCount != WDGM_ZERO)
  {
    LusCount--;
    /* Set the failure cycle count for the corresponding alive supervision to WDGM_ZERO */
    /* polyspace<RTE:OBAI:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    WdgM_GddFailedRefCycleCounter[LusCount] = WDGM_ZERO;
  }

  /* Set the count to total number of alive supervisions configured in
    the current mode */
  LusCount = pCurrentMode->usTotalAliveSupervisions;
  while(LusCount != WDGM_ZERO)
  {
    LusCount--;
    /* Set the alive indication count for the corresponding alive supervision to WDGM_ZERO */
    /* polyspace<RTE:OBAI:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    WdgM_GaaAliveIndicationStatus[LusCount] = WDGM_ZERO;
  }
  #endif

  #if(WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)
  /* Set the count to total number of deadline supervisions configured
    in the current mode */
  LusCount = pCurrentMode->usTotalDeadlineSupervisions;
  /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> below could be reachable according to user configuration */
  while(LusCount != WDGM_ZERO)
  {
    LusCount--;
    /* Set the Deadline supervision status count for the corresponding Deadline
    supervision to WDGM_ZERO */
    WdgM_GaaDeadlineSupervisionStatus[LusCount].ddValue = WDGM_ZERO;
    /* Set the Deadline supervision status for the corresponding Deadline
    supervision to WDGM_DS_NOT_STARTED */
    WdgM_GaaDeadlineSupervisionStatus[LusCount].ucStatus = WDGM_DS_NOT_STARTED;
  }
  /* polyspace:end<RTE:UNR> */
  #endif

  #if(WDGM_ENABLE_INTERNAL_TRANSITION == STD_ON)
  /* Set the count to total number of active SE's configured in the
    current mode */
  LusCount = pCurrentMode->ddTotalSEInMode;
  LpActiveSE = pCurrentMode->pActiveSEList;
  while(LusCount != WDGM_ZERO)
  {
    LusCount--;
    LddSEArrayIndex = LpActiveSE[LusCount].ddSEArrayIndex;
    LddILSIndex = WdgM_GaaSupervisedEntity[LddSEArrayIndex].ddILSIndex;
    /* Set the last reported CP of the corresponding internal logical
      supervision in the SE to WDGM_ZERO */
    WdgM_GaaIntLogicalSupervisionStatus[LddILSIndex].ddLastReportedCP
      = WDGM_ZERO;
    /* Set the activity flag of the corresponding internal logical supervision
      in the SE to WDGM_FALSE */
    WdgM_GaaIntLogicalSupervisionStatus[LddILSIndex].blActivityFlag
      = WDGM_FALSE;
  }
  #endif

  #if(WDGM_ENABLE_EXTERNAL_TRANSITION == STD_ON)
  /* Set the count to total number of external logical supervisions configured
    in the current mode */
  LusCount = pCurrentMode->usTotalExLogicalSupervisions;
  while(LusCount != WDGM_ZERO)
  {
    LusCount--;
    /* Set the last reported reported SE/CP of the corresponding external
      logical supervision in the SE to WDGM_ZERO */
    WdgM_GaaExtLogicalSupervisionStatus[LusCount].ddLastRepExLSGraphArrIdx
      = WDGM_ZERO;
    /* Set the activity flag of the corresponding external logical supervision
      to WDGM_FALSE */
    WdgM_GaaExtLogicalSupervisionStatus[LusCount].blActivityFlag = WDGM_FALSE;
  }
  #endif

  SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : WdgM_PerformAliveIndication                           **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service increases the alive indication of alive  **
**                      supervisions configured                               **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ddSEID, ddCheckpointID                                **
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
**                      WdgM_GaaModes,                                        **
**                      WdgM_GddCurrentMode,                                  **
**                      WdgM_GaaAliveIndicationStatus                         **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,        **
**                      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION          **
*******************************************************************************/
#if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_PerformAliveIndication(
  WdgM_SupervisedEntityIdType ddSEID, WdgM_CheckpointIdType ddCheckpointID)
{
  /* Local pointer for the pointing to the current mode */
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST)LpModes;
  /* Local pointer for the pointing to alive supervision array */
  P2CONST(WdgM_AliveSupervisionType, AUTOMATIC, WDGM_CONST) LpAliveSupervisions;
  /* Local variable for total alive supervisions in the current mode */
  uint16 LusTotalAliveSupervisions;
  uint16 LusIndex;

  LpModes = &WdgM_GaaModes[WdgM_GddCurrentMode];
  /* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
  LpAliveSupervisions = LpModes->pAliveSupervisions;
  LusTotalAliveSupervisions = LpModes->usTotalAliveSupervisions;
  /* polyspace:end<RTE:IDP> */
  /* polyspace:end<MISRA-C3:18.1> */

  LusIndex = WDGM_ZERO;
  /* Match SE and CP in AliveSupervisions list */
  while (LusIndex < LusTotalAliveSupervisions)
  {
    /* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    /* polyspace:begin<RTE:NIV:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    if ((ddSEID == LpAliveSupervisions[LusIndex].ddSEId)
      && (ddCheckpointID == LpAliveSupervisions[LusIndex].ddCheckpoint))
    /* polyspace:end<RTE:IDP> */
    /* polyspace:end<RTE:NIV> */
    /* polyspace:end<MISRA-C3:18.1> */
    {
      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
      /* Update alive counters */
      /* polyspace<RTE:OBAI:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
      /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
      WdgM_GaaAliveIndicationStatus[LusIndex]++;
      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
      LusIndex = LusTotalAliveSupervisions;
    }
    LusIndex++;
  }
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : WdgM_PerformAliveSupervision                          **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service evaluates the result of all the alive    **
**                      supervisions configured                               **
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
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      WdgM_GaaModes,                                        **
**                      WdgM_GddCurrentMode,                                  **
**                      WdgM_GulFreeRunningCounter,                           **
**                      WdgM_GulMaxAliveSupervisionRefCycle,                  **
**                      WdgM_GddTotalSEs,                                     **
**                      WdgM_GaaAlreadyUpdated,                               **
**                      WdgM_GaaAliveIndicationStatus,                        **
**                      WdgM_GaaSEStatus                                      **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,        **
**                      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION          **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_PerformAliveSupervision(void)
{
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) LpCurrentMode;
  P2CONST(WdgM_AliveSupervisionType, AUTOMATIC, WDGM_CONST) LpAliveSupervisions;
  WdgM_SupervisedEntityIndexType LddSEArrayIndex;
  uint16 LusTotalAliveSupervisions;
  uint16 LusIndex;

  SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();

  /* Get the pointer to current mode array */
  LpCurrentMode = &WdgM_GaaModes[WdgM_GddCurrentMode];

  if (WdgM_GulFreeRunningCounter == WdgM_GulMaxAliveSupervisionRefCycle)
  {
    WdgM_GulFreeRunningCounter = WDGM_ZERO;
  }
  /* Increment free running timer */
  WdgM_GulFreeRunningCounter++;
  /* Get the number of alive supervision's in the current mode */
  /* polyspace<RTE:IDP:Not a defect> Its boundary is pre-defined */
  /* polyspace<MISRA-C3:D4.1:Not a defect> Its boundary is pre-defined */
  /* polyspace<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
  LusTotalAliveSupervisions = LpCurrentMode->usTotalAliveSupervisions;
  /* Get the pointer to the Alive supervision's in the current mode */
  LpAliveSupervisions = LpCurrentMode->pAliveSupervisions;
  LusIndex = WDGM_ZERO;
  /* Set the flags of updating status to WDGM_FALSE */
  while (LusIndex < WdgM_GddTotalSEs)
  {
    WdgM_GaaAlreadyUpdated[LusIndex] = WDGM_FALSE;
    LusIndex++;
  }
  /* Set the index to WDGM_ZERO */
  LusIndex = WDGM_ZERO;
  /* Match SE and CP in AliveSupervisions list */
  while (LusIndex < LusTotalAliveSupervisions)
  {
    /* polyspace<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    /* polyspace:begin<RTE:NIV:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    /* polyspace:begin<RTE:OBAI:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    /* polyspace:begin<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
    LddSEArrayIndex = LpAliveSupervisions[LusIndex].ddSEArrayIndex;
    if ((WdgM_GaaSEStatus[LddSEArrayIndex] & WDGM_STATUS_MASK) != WDGM_LOCAL_STATUS_DEACTIVATED)
    {
      if ((LpAliveSupervisions[LusIndex].ddSupervisionRefCycle >= WDGM_ONE)
        && ((WdgM_GulFreeRunningCounter
        % (LpAliveSupervisions[LusIndex].ddSupervisionRefCycle)) == WDGM_ZERO))
      {
        /* Check whether the required number of alive indications has occurred */
        if ((WdgM_GaaAliveIndicationStatus[LusIndex]
          <= ((LpAliveSupervisions[LusIndex].ddExAliveIndications)
          + (LpAliveSupervisions[LusIndex].ucExAliveIndMaxMargin)))
          && (WdgM_GaaAliveIndicationStatus[LusIndex]
          >= ((LpAliveSupervisions[LusIndex].ddExAliveIndications)
          - (LpAliveSupervisions[LusIndex].ucExAliveIndMinMargin))))
        {
          /* Set the result if only SE status's not updated ever */
          /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> status check */
          if (WdgM_GaaAlreadyUpdated[LddSEArrayIndex] == WDGM_FALSE)
          {
            /* Update AI result as CORRECT */
            WdgM_GaaSEStatus[LddSEArrayIndex]
              = WdgM_GaaSEStatus[LddSEArrayIndex]
              | WDGM_ALIVESUPERVISION_CORRECT;
          }
          /* polyspace:end<RTE:UNR> */
        }
        else
        {
          /* Set the flag to WDGM_TRUE */
          WdgM_GaaAlreadyUpdated[LddSEArrayIndex] = WDGM_TRUE;
          /* Update AI result as INCORRECT*/
          WdgM_GaaSEStatus[LddSEArrayIndex] = WdgM_GaaSEStatus[LddSEArrayIndex]
            & WDGM_ALIVESUPERVISION_INCORRECT;

          #if(WDGM_ERROR_INFO_API == STD_ON)
          if ((WdgM_GaaErrorInfo[LddSEArrayIndex].ddStatus
            == WDGM_LOCAL_STATUS_OK)
            || (WdgM_GaaErrorInfo[LddSEArrayIndex].ddStatus
            == WDGM_LOCAL_STATUS_FAILED))
          {
            WdgM_GaaErrorInfo[LddSEArrayIndex].ddSEId
              = LpAliveSupervisions[LusIndex].ddSEId;
            WdgM_GaaErrorInfo[LddSEArrayIndex].ddStatus
              = WDGM_LOCAL_STATUS_FAILED;
            WdgM_GaaErrorInfo[LddSEArrayIndex].ddSupervision
              = WDGM_ALIVE_SUPERVISION;
            WdgM_GaaErrorInfo[LddSEArrayIndex].ddCheckpoint
              = LpAliveSupervisions[LusIndex].ddCheckpoint;
          }
          #endif
        }
        /* Expected alive indication value is reset to WDGM_ZERO */
        WdgM_GaaAliveIndicationStatus[LusIndex] = WDGM_ZERO;
      }
      /* polyspace:end<RTE:NIV> */
      /* polyspace:end<RTE:OBAI> */
      /* polyspace:end<MISRA-C3:18.1> */
    }
    LusIndex++;
  } /* LusIndex < LusTotalAliveSupervisions */

  SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name      : WdgM_PerformDeadlineSupervision                       **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service performs deadline supervision for the    **
**                      requested checkpoint                                  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ddSEID, ddCheckpointID, ddSEArrayIndex                **
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
**                      WdgM_GaaModes,                                        **
**                      WdgM_GddCurrentMode,                                  **
**                      WdgM_GaaSEStatus,                                     **
**                      WdgM_GaaDeadlineSupervisionStatus,                    **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      GetCounterValue,                                      **
**                      GetElapsedValue,                                      **
**                      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,        **
**                      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION          **
*******************************************************************************/
#if(WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_PerformDeadlineSupervision(
  WdgM_SupervisedEntityIdType ddSEID, WdgM_CheckpointIdType ddCheckpointID,
  WdgM_SupervisedEntityIndexType ddSEArrayIndex)
{
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) LpModes;
  P2CONST(WdgM_DeadlineSupervisionType, AUTOMATIC, WDGM_CONST)
    LpDeadlineSupervisions;
  P2VAR(WdgM_DeadlineSupervisionStatusType, AUTOMATIC, WDGM_DATA)
    LpDeadlineSupervisionStatus;
  P2CONST(WdgM_SupervisedEntityType, AUTOMATIC, WDGM_CONST)
    LpSupervisedEntity;
  uint16 LusTotalDeadlineSupervisions;
  uint16 LusIndex;
  TickType LddTickValue;
  TickType LddValue;

  SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();

  if ((WdgM_GaaSEStatus[ddSEArrayIndex] & WDGM_DEADLINESUPERVISION_CORRECT)
    == WDGM_DEADLINESUPERVISION_CORRECT)
  {
    LpModes = &WdgM_GaaModes[WdgM_GddCurrentMode];
    LusTotalDeadlineSupervisions = LpModes->usTotalDeadlineSupervisions;
    LpDeadlineSupervisions = LpModes->pDeadlineSupervisions;
    LpSupervisedEntity = &WdgM_GaaSupervisedEntity[ddSEArrayIndex];

    LusIndex = WDGM_ZERO;
    LddTickValue = WDGM_ZERO;
    LddValue = WDGM_ZERO;
    while (LusIndex < LusTotalDeadlineSupervisions)
    {
      /* polyspace<RTE:IDP:Not a defect> Its boundary is pre-defined */
      /* polyspace<MISRA-C3:D4.1:Not a defect> Its boundary is pre-defined */
      /* polyspace<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
      if (ddSEID == LpDeadlineSupervisions[LusIndex].ddSEId)
      {
        LpDeadlineSupervisionStatus
          = &WdgM_GaaDeadlineSupervisionStatus[LusIndex];
        if (ddCheckpointID
          == LpDeadlineSupervisions[LusIndex].ddInitialCheckpoint)
        {
          SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
          /* polyspace<RTE:IDP:Not a defect> Its boundary is pre-defined */
          /* polyspace<MISRA-C3:D4.1:Not a defect> Its boundary is pre-defined */
          /* polyspace<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
          (void)GetCounterValue(*(LpSupervisedEntity->pCounterID),
            &LddTickValue);
          SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
          LpDeadlineSupervisionStatus->ddValue = LddTickValue;
          /* Set Monitoring status as started */
          LpDeadlineSupervisionStatus->ucStatus = WDGM_DS_STARTED;
        }
        else if (ddCheckpointID
          == LpDeadlineSupervisions[LusIndex].ddFinalCheckpoint)
        {
          if (LpDeadlineSupervisionStatus->ucStatus == WDGM_DS_STARTED)
          {
            LddTickValue = LpDeadlineSupervisionStatus->ddValue;
            SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
            /* polyspace<RTE:IDP:Not a defect> Its boundary is pre-defined */
            /* polyspace<MISRA-C3:D4.1:Not a defect> Its boundary is pre-defined */
            /* polyspace<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
            (void)GetElapsedValue(*(LpSupervisedEntity->pCounterID),
              &LddTickValue, &LddValue);
            SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
            /* Set Monitoring status as not started */
            LpDeadlineSupervisionStatus->ucStatus = WDGM_DS_NOT_STARTED;

            if ((LddValue <= LpDeadlineSupervisions[LusIndex].ulDeadlineMax)
              && (LddValue >= LpDeadlineSupervisions[LusIndex].ulDeadlineMin))
            {
              /* Clear Time-Stamp */
              LpDeadlineSupervisionStatus->ddValue = WDGM_ZERO;
              /* Set DS result as WDGM_DEADLINESUPERVISION_CORRECT */
              WdgM_GaaSEStatus[ddSEArrayIndex] =
                WdgM_GaaSEStatus[ddSEArrayIndex]
                | WDGM_DEADLINESUPERVISION_CORRECT;
            }
            else
            {
              WdgM_GaaSEStatus[ddSEArrayIndex] =
                WdgM_GaaSEStatus[ddSEArrayIndex]
                & WDGM_DEADLINESUPERVISION_INCORRECT;

              #if(WDGM_ERROR_INFO_API == STD_ON)
              if ((WdgM_GaaErrorInfo[ddSEArrayIndex].ddStatus
                == WDGM_LOCAL_STATUS_OK)
                || (WdgM_GaaErrorInfo[ddSEArrayIndex].ddStatus
                == WDGM_LOCAL_STATUS_FAILED))
              {
                WdgM_GaaErrorInfo[ddSEArrayIndex].ddSEId = ddSEID;
                WdgM_GaaErrorInfo[ddSEArrayIndex].ddStatus
                  = WDGM_LOCAL_STATUS_EXPIRED;
                WdgM_GaaErrorInfo[ddSEArrayIndex].ddSupervision
                  = WDGM_DEADLINE_SUPERVISION;
                WdgM_GaaErrorInfo[ddSEArrayIndex].ddCheckpoint = ddCheckpointID;
              }
              #endif
            }
          }
        }
        else
        {
        }
      }
      LusIndex++;
    } /* LusIndex < LusTotalDeadlineSupervisions */
  }

  SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name      : WdgM_PerformIntLogicalSupervision                     **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service performs internal logical supervision    **
**                      for the requested checkpoint                          **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ddCheckpointID, ddSEArrayIndex                        **
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
**                      WdgM_GaaSEStatus,                                     **
**                      WdgM_GaaSupervisedEntity,                             **
**                      WdgM_GaaIntLogicalSupervisionStatus                   **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,        **
**                      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION          **
*******************************************************************************/
#if(WDGM_ENABLE_INTERNAL_TRANSITION == STD_ON)
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_PerformIntLogicalSupervision(
  WdgM_CheckpointIdType ddCheckpointID,
  WdgM_SupervisedEntityIndexType ddSEArrayIndex)
{
  P2CONST(WdgM_SupervisedEntityType, AUTOMATIC, WDGM_CONST) LpSupervisedEntity;
  P2CONST(WdgM_CheckpointIdType, AUTOMATIC, WDGM_CONST) LpIntLSGraphMapArray;
  P2CONST(WdgM_CheckpointGraphType, AUTOMATIC, WDGM_CONST) LpCheckpoint;
  P2CONST(WdgM_CheckpointGraphType, AUTOMATIC, WDGM_CONST) LpLastReportedCP;
  P2VAR(WdgM_IntLogicalSupervisionStatusType, AUTOMATIC, WDGM_DATA)
    LpIntLogicalSupervisionStatus;
  WdgM_CpMapArrayIndexType LddCpMapArrayIndex;
  uint8 LucMaxBranches;
  boolean LblFound;

  SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();

  if ((WdgM_GaaSEStatus[ddSEArrayIndex] & WDGM_LGSUPERVISION_CORRECT)
    == WDGM_LGSUPERVISION_CORRECT)
  {
    LpSupervisedEntity = &WdgM_GaaSupervisedEntity[ddSEArrayIndex];
    /* Connect to CP properties */
    LpCheckpoint = &((LpSupervisedEntity->pCheckpoint)[ddCheckpointID]);
    LpIntLSGraphMapArray = LpSupervisedEntity->pIntLSGraphMapArray;

    /* Check whether the checkpoint is configured for internal LS */
    /* polyspace-begin RTE:IDP [Not a defect] "Its boundary is pre-defined" */
    /* polyspace-begin MISRA-C3:D4.1 [Not a defect] Its boundary is pre-defined */
    /* polyspace-begin MISRA-C3:18.1 [Not a defect] Its boundary is limited to array size */
    if ((LpIntLSGraphMapArray != NULL_PTR)
      && ((LpCheckpoint->ucMaxBranches != WDGM_ZERO)
      || (LpCheckpoint->enCpType != WDGM_CP_BI)))
    /* polyspace-end RTE:IDP */
    /* polyspace-end MISRA-C3:D4.1 */
    /* polyspace-end MISRA-C3:18.1 */
    {
      /* Access ILS Status Array */
      LpIntLogicalSupervisionStatus = &WdgM_GaaIntLogicalSupervisionStatus
        [LpSupervisedEntity->ddILSIndex];
      /* Expecting an initial checkpoint */
      if (LpIntLogicalSupervisionStatus->blActivityFlag == WDGM_FALSE)
      {
        if (LpCheckpoint->enCpType == WDGM_CP_INITIAL)
        {
          LpIntLogicalSupervisionStatus->blActivityFlag = WDGM_TRUE;
          /* Update last reported CP */
          LpIntLogicalSupervisionStatus->ddLastReportedCP = ddCheckpointID;
          /* Set ILS result as WDGM_LGSUPERVISION_CORRECT */
          WdgM_GaaSEStatus[ddSEArrayIndex] = WdgM_GaaSEStatus[ddSEArrayIndex]
            | WDGM_LGSUPERVISION_CORRECT;
        }
        else
        {
          /* Set ILS result as WDGM_LGSUPERVISION_INCORRECT */
          WdgM_GaaSEStatus[ddSEArrayIndex] = WdgM_GaaSEStatus[ddSEArrayIndex]
            & WDGM_LGSUPERVISION_INCORRECT;

          #if(WDGM_ERROR_INFO_API == STD_ON)
          if ((WdgM_GaaErrorInfo[ddSEArrayIndex].ddStatus
            == WDGM_LOCAL_STATUS_OK)
            || (WdgM_GaaErrorInfo[ddSEArrayIndex].ddStatus
            == WDGM_LOCAL_STATUS_FAILED))
          {
            WdgM_GaaErrorInfo[ddSEArrayIndex].ddSEId
              = LpSupervisedEntity->ddSEId;
            WdgM_GaaErrorInfo[ddSEArrayIndex].ddStatus
              = WDGM_LOCAL_STATUS_EXPIRED;
            WdgM_GaaErrorInfo[ddSEArrayIndex].ddSupervision
              = WDGM_INTERNAL_LOGICAL_SUPERVISION;
            WdgM_GaaErrorInfo[ddSEArrayIndex].ddCheckpoint = ddCheckpointID;
          }
          #endif
        }
      }
      /* Expecting a successor */
      else
      {
        /* Access property of last reported CP */
        LpLastReportedCP = &((LpSupervisedEntity->pCheckpoint)
          [LpIntLogicalSupervisionStatus->ddLastReportedCP]);
        /* Get the map array index of Last Reported CP */
        /* polyspace<RTE:IDP:Not a defect> Its boundary is pre-defined */
        /* polyspace<MISRA-C3:D4.1:Not a defect> Its boundary is pre-defined */
        /* polyspace<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
        LddCpMapArrayIndex = LpLastReportedCP->ddCpMapArrayIndex;
        /* Get the maximum branches available for Last Reported CP */
        LucMaxBranches = LpLastReportedCP->ucMaxBranches;
        LblFound = WDGM_FALSE;
        while (LucMaxBranches != WDGM_ZERO)
        {
          /* Check whether the new CP is a successor of the stored CP */
          /* polyspace<RTE:IDP:Not a defect> Its boundary is pre-defined */
          /* polyspace<MISRA-C3:D4.1:Not a defect> Its boundary is pre-defined */
          /* polyspace<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
          if (ddCheckpointID == LpIntLSGraphMapArray[LddCpMapArrayIndex])
          {
            /* Update ILS result */
            WdgM_GaaSEStatus[ddSEArrayIndex] =
              WdgM_GaaSEStatus[ddSEArrayIndex] | WDGM_LGSUPERVISION_CORRECT;
            /* Break the loop */
            LucMaxBranches = WDGM_ZERO;
            LblFound = WDGM_TRUE;
          }
          else
          {
            LddCpMapArrayIndex++;
            LucMaxBranches--;
          }
        }

        if (LblFound == WDGM_TRUE)
        {
          if (LpCheckpoint->enCpType == WDGM_CP_FINAL)
          {
            LpIntLogicalSupervisionStatus->blActivityFlag = WDGM_FALSE;
          }
          else
          {
            /* Update last reported CP */
            LpIntLogicalSupervisionStatus->ddLastReportedCP = ddCheckpointID;
          }
        }
        else
        {
          /* Set ILS result as WDGM_LGSUPERVISION_INCORRECT */
          WdgM_GaaSEStatus[ddSEArrayIndex] = WdgM_GaaSEStatus[ddSEArrayIndex]
            & WDGM_LGSUPERVISION_INCORRECT;

          #if(WDGM_ERROR_INFO_API == STD_ON)
          if ((WdgM_GaaErrorInfo[ddSEArrayIndex].ddStatus
            == WDGM_LOCAL_STATUS_OK)
            || (WdgM_GaaErrorInfo[ddSEArrayIndex].ddStatus
            == WDGM_LOCAL_STATUS_FAILED))
          {
            WdgM_GaaErrorInfo[ddSEArrayIndex].ddSEId
              = LpSupervisedEntity->ddSEId;
            WdgM_GaaErrorInfo[ddSEArrayIndex].ddStatus
              = WDGM_LOCAL_STATUS_EXPIRED;
            WdgM_GaaErrorInfo[ddSEArrayIndex].ddSupervision
              = WDGM_INTERNAL_LOGICAL_SUPERVISION;
            WdgM_GaaErrorInfo[ddSEArrayIndex].ddCheckpoint = ddCheckpointID;
          }
          #endif
        }
      } /* LpIntLogicalSupervisionStatus->blActivityFlag != WDGM_FALSE */
    } /* (LpIntLSGraphMapArray != NULL_PTR) &&.... */
  }

  SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name      : WdgM_PerformExtLogicalSupervision                     **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service performs external logical supervision    **
**                      for the requested checkpoint                          **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ddSEID, ddCheckpointID, ddSEArrayIndex                **
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
**                      WdgM_GaaSEStatus,                                     **
**                      WdgM_GaaModes,                                        **
**                      WdgM_GddCurrentMode,                                  **
**                      WdgM_GaaExtLogicalSupervisionStatus                   **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,        **
**                      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION          **
*******************************************************************************/
#if(WDGM_ENABLE_EXTERNAL_TRANSITION == STD_ON)
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_PerformExtLogicalSupervision(
  WdgM_SupervisedEntityIdType ddSEID, WdgM_CheckpointIdType ddCheckpointID,
  WdgM_SupervisedEntityIndexType ddSEArrayIndex)
{
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) LpModes;
  P2CONST(WdgM_ExLSGraphType, AUTOMATIC, WDGM_CONST) LpExLSGraph = NULL_PTR;
  P2CONST(WdgM_ExLSGraphType, AUTOMATIC, WDGM_CONST) LpLastRepExLSGraph;
  P2CONST(WdgM_ExLogicalSupervisionType, AUTOMATIC, WDGM_CONST)
    LpExLogicalSupervision;
  P2VAR(WdgM_ExtLogicalSupervisionStatusType, AUTOMATIC, WDGM_DATA)
    LpExtLogicalSupervisionStatus;
  P2CONST(WdgM_ExLSGraphMapArrayType, AUTOMATIC, WDGM_CONST)
    LpExLSGraphMapArray;
  WdgM_CpMapArrayIndexType LddCpMapArrayIndex;
  WdgM_ExLSGraphArrayType LddExLSGraphArrayIndex;
  WdgM_CheckpointIdType LddTotalCheckpoints;
  uint16 LusTotalExLogicalSupervisions;
  uint16 LusExLSIndex;
  uint8 LucMaxBranches;
  boolean LblValidExLSCP;
  boolean LblFound;
  /*Initialize Variables*/
  LpExLSGraph = NULL_PTR;
  LddExLSGraphArrayIndex = WDGM_ZERO;  

  if ((WdgM_GaaSEStatus[ddSEArrayIndex] & WDGM_LGSUPERVISION_CORRECT)
    == WDGM_LGSUPERVISION_CORRECT)
  {
    LblValidExLSCP = WDGM_FALSE;
    /* Initialize ExLS Status Array Index */
    LusExLSIndex = WDGM_ZERO;
    LpModes = &WdgM_GaaModes[WdgM_GddCurrentMode];
    /* Available logical supervisions in a mode */
    LpExLogicalSupervision = LpModes->pExLogicalSupervisions;
    /* Load total ExLS */
    LusTotalExLogicalSupervisions =
      LpModes->usTotalExLogicalSupervisions;
    /* Check whether reported CP of SE is present in any transition */
    while ((LusTotalExLogicalSupervisions != WDGM_ZERO)
      && (LblValidExLSCP == WDGM_FALSE))
    {
      /* Store ExLS Graph Array Index of the reported SE/CP */
      LddExLSGraphArrayIndex = WDGM_ZERO;
      /* Pointer to ExLS Graph Array */
      /* polyspace<RTE:IDP:Not a defect> Its boundary is pre-defined */
      /* polyspace<MISRA-C3:D4.1:Not a defect> Its boundary is pre-defined */
      /* polyspace<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
      LpExLSGraph = LpExLogicalSupervision[LusExLSIndex].pExLSGraph;
      /* Total CP in ExLS Graph Array (Size of ExLS Graph Array) */
      LddTotalCheckpoints
        = LpExLogicalSupervision[LusExLSIndex].ddTotalCheckpoints;
      /* Loop all CP in WdgM_GaaExLSGraph array */
      while ((LddTotalCheckpoints != WDGM_ZERO)
        && (LblValidExLSCP == WDGM_FALSE))
      {
        /* Match the SE and CP in WdgM_GaaExLSGraph<><> array*/
        /* polyspace<RTE:IDP:Not a defect> Its boundary is pre-defined */
        /* polyspace<MISRA-C3:D4.1:Not a defect> Its boundary is pre-defined */
        /* polyspace<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
        if ((LpExLSGraph[LddExLSGraphArrayIndex].ddSEId == ddSEID)
          && (LpExLSGraph[LddExLSGraphArrayIndex].ddCheckpoint == ddCheckpointID))
        {
          /* Valid Ex Logical Supervision CP detected */
          LblValidExLSCP = WDGM_TRUE;
        }
        else
        {
          LddTotalCheckpoints--;
          /* Next index of the ExLS Graph Array ) */
          LddExLSGraphArrayIndex++;
        }
      }

      if (LblValidExLSCP == WDGM_FALSE)
      {
        LusTotalExLogicalSupervisions--;
        /* Update ExLS Status Array Index */
        LusExLSIndex++;
      }
    } /* LusTotalExLogicalSupervisions != WDGM_ZERO) &&... */

    /* Ignore the CheckpointReached function call in case of an
      invalid ExLS CP (CP is not configured for ExLS) */
    if (LblValidExLSCP == WDGM_TRUE)
    {
      /* Access ExLS Status Array */
      LpExtLogicalSupervisionStatus =
        &WdgM_GaaExtLogicalSupervisionStatus[LusExLSIndex];
      /* Expecting an initial checkpoint */
      if (LpExtLogicalSupervisionStatus->blActivityFlag == WDGM_FALSE)
      {
        /* polyspace<RTE:IDP:Not a defect> Its boundary is pre-defined */
        /* polyspace<MISRA-C3:D4.1:Not a defect> Its boundary is pre-defined */
        /* polyspace<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
        if (LpExLSGraph[LddExLSGraphArrayIndex].enCpType == WDGM_CP_INITIAL)
        {
          LpExtLogicalSupervisionStatus->blActivityFlag = WDGM_TRUE;
          /* Store index of last reported ExLSGraphArrayIndex from this
            we will get previous reported SE and CP */
          LpExtLogicalSupervisionStatus->ddLastRepExLSGraphArrIdx
            = LddExLSGraphArrayIndex;
          /* Set ExLS result as WDGM_LGSUPERVISION_CORRECT */
          SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
          WdgM_GaaSEStatus[ddSEArrayIndex] = WdgM_GaaSEStatus[ddSEArrayIndex]
            | WDGM_LGSUPERVISION_CORRECT;
          SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
        }
        else
        {
          SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
          /* Set ELS result as WDGM_LGSUPERVISION_INCORRECT */
          WdgM_GaaSEStatus[ddSEArrayIndex] = WdgM_GaaSEStatus[ddSEArrayIndex]
            & WDGM_LGSUPERVISION_INCORRECT;

          #if(WDGM_ERROR_INFO_API == STD_ON)
          if ((WdgM_GaaErrorInfo[ddSEArrayIndex].ddStatus
            == WDGM_LOCAL_STATUS_OK)
            || (WdgM_GaaErrorInfo[ddSEArrayIndex].ddStatus
            == WDGM_LOCAL_STATUS_FAILED))
          {
            WdgM_GaaErrorInfo[ddSEArrayIndex].ddSEId
              = LpExLSGraph[LddExLSGraphArrayIndex].ddSEId;
            WdgM_GaaErrorInfo[ddSEArrayIndex].ddStatus
              = WDGM_LOCAL_STATUS_EXPIRED;
            WdgM_GaaErrorInfo[ddSEArrayIndex].ddSupervision
              = WDGM_EXTERNAL_LOGICAL_SUPERVISION;
            WdgM_GaaErrorInfo[ddSEArrayIndex].ddCheckpoint = ddCheckpointID;
          }
          #endif
          SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
        }
      }
      /* Expecting a successor */
      else
      {
        /* Access the last reported SE and CP */
        LpLastRepExLSGraph = &((LpExLogicalSupervision[LusExLSIndex].pExLSGraph)
          [LpExtLogicalSupervisionStatus->ddLastRepExLSGraphArrIdx]);
        /* Get the map array index of Last Reported CP i.e. Index of
          Checkpoint Mapping Array
          WdgM_GaaExLSGraph<MODE_ID><GRAPH_ID>MapArray*/
        /* polyspace<RTE:IDP:Not a defect> Its boundary is pre-defined */
        /* polyspace<MISRA-C3:D4.1:Not a defect> Its boundary is pre-defined */
        /* polyspace<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
        LddCpMapArrayIndex = LpLastRepExLSGraph->ddCpMapArrayIndex;

        LpExLSGraphMapArray
          = &((LpExLogicalSupervision[LusExLSIndex].pExLSGraphMapArray)
          [LddCpMapArrayIndex]);
        /* Get the maximum branches available for Last Reported CP */
        LucMaxBranches = WDGM_ZERO;
        LblFound = WDGM_FALSE;
        while (LucMaxBranches < LpLastRepExLSGraph->ucMaxBranches)
        {
          /* Check whether the new CP is a successor of the stored CP */
          /* polyspace<RTE:IDP:Not a defect> Its boundary is pre-defined */
          /* polyspace<MISRA-C3:D4.1:Not a defect> Its boundary is pre-defined */
          /* polyspace<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
          if ((ddCheckpointID == LpExLSGraphMapArray[LucMaxBranches].ddCheckpoint)
            && (ddSEID == LpExLSGraphMapArray[LucMaxBranches].ddSEId))
          {
            /* Update ILS result */
            SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
            WdgM_GaaSEStatus[ddSEArrayIndex] =
              WdgM_GaaSEStatus[ddSEArrayIndex] | WDGM_LGSUPERVISION_CORRECT;
            SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
            /* Break the loop */
            LucMaxBranches = LpLastRepExLSGraph->ucMaxBranches;
            LblFound = WDGM_TRUE;
          }
          else
          {
            LucMaxBranches++;
          }
        }

        if (LblFound == WDGM_TRUE)
        {
          /* Check the property of current reported ExLS */
          /* polyspace<RTE:IDP:Not a defect> Its boundary is pre-defined */
          /* polyspace<MISRA-C3:D4.1:Not a defect> Its boundary is pre-defined */
          /* polyspace<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
          if (LpExLSGraph[LddExLSGraphArrayIndex].enCpType == WDGM_CP_FINAL)
          {
            /* Reset the activity flag */
            LpExtLogicalSupervisionStatus->blActivityFlag = WDGM_FALSE;
          }
          else
          {
            /* Store index of newly reported ExLSGraphArrayIndex */
            LpExtLogicalSupervisionStatus->ddLastRepExLSGraphArrIdx
              = LddExLSGraphArrayIndex;
          }
        }
        else
        {
          SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
          WdgM_GaaSEStatus[ddSEArrayIndex] = WdgM_GaaSEStatus[ddSEArrayIndex]
            & WDGM_LGSUPERVISION_INCORRECT;

          #if(WDGM_ERROR_INFO_API == STD_ON)
          if ((WdgM_GaaErrorInfo[ddSEArrayIndex].ddStatus
            == WDGM_LOCAL_STATUS_OK)
            || (WdgM_GaaErrorInfo[ddSEArrayIndex].ddStatus
            == WDGM_LOCAL_STATUS_FAILED))
          {
            WdgM_GaaErrorInfo[ddSEArrayIndex].ddSEId
              = LpExLSGraph[LddExLSGraphArrayIndex].ddSEId;
            WdgM_GaaErrorInfo[ddSEArrayIndex].ddStatus
              = WDGM_LOCAL_STATUS_EXPIRED;
            WdgM_GaaErrorInfo[ddSEArrayIndex].ddSupervision
              = WDGM_EXTERNAL_LOGICAL_SUPERVISION;
            WdgM_GaaErrorInfo[ddSEArrayIndex].ddCheckpoint = ddCheckpointID;
          }
          #endif
          SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
        }
      } /* LpExtLogicalSupervisionStatus->blActivityFlag == WDGM_FALSE */
    } /* LblValidExLSCP == WDGM_TRUE */
  }
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*******************************************************************************
** Function Name      : WdgM_EvaluateLocalStatus                              **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service evaluates the local supervision status   **
**                      of supervised entities                                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : pSEFailedFlag, pSEExpiredFlag                         **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      WdgM_GaaModes,                                        **
**                      WdgM_GddCurrentMode,                                  **
**                      WdgM_GaaSupervisedEntity,                             **
**                      WdgM_GaaSEStatus,                                     **
**                      WdgM_GddFailedRefCycleCounter,                        **
**                      WdgM_GblFirstExpSEIDStatus,                           **
**                      WdgM_GddFirstExpiredSEID,                             **
**                      WdgM_GddInvFirstExpiredSEID                           **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      pRteSwitchMode,                                       **
**                      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,        **
**                      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION          **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_EvaluateLocalStatus(
  P2VAR(boolean, AUTOMATIC, WDGM_DATA) pSEFailedFlag,
  P2VAR(boolean, AUTOMATIC, WDGM_DATA) pSEExpiredFlag)
{
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST)LpCurrentMode;
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST)LpActiveSEList;
  P2CONST(WdgM_SupervisedEntityType, AUTOMATIC, WDGM_CONST) LpSupervisedEntity;
  WdgM_SupervisedEntityIndexType LddSEArrayIndex;
  uint16 LusActiveSECnt;
  uint8 LucPreLocalStatus;
  uint8 LucNewLocalStatus;
  boolean LblSEFailedFlag;
  boolean LblSEExpiredFlag;
  #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
  boolean LblASPass;
  uint8 LucFailedTolerance;
  #endif
  #if((WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)\
    ||(WDGM_ENABLE_LOGICAL_SUPERVISION == STD_ON))
  boolean LblDSLSPass;
  #endif

  SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();

  /* Get the pointer to current mode array */
  LpCurrentMode = &WdgM_GaaModes[WdgM_GddCurrentMode];
  /* Get the pointer to the Active SE's in the current mode */
  /* polyspace<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
  /* polyspace<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
  LpActiveSEList = LpCurrentMode->pActiveSEList;
  /* Get the number of active SE's in the current mode */
  LusActiveSECnt = WDGM_ZERO;

  LblSEFailedFlag = WDGM_FALSE;
  LblSEExpiredFlag = WDGM_FALSE;

  /* Loop through all the SE's */
  while (LusActiveSECnt < LpCurrentMode->ddTotalSEInMode)
  {
    /* Get index to the Active SE */
    /* polyspace<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    /* polyspace<RTE:NIV:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    /* polyspace<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
    LddSEArrayIndex = LpActiveSEList[LusActiveSECnt].ddSEArrayIndex;
    /* Get the pointer to current WdgM_GaaSupervisedEntity array */
    LpSupervisedEntity = &WdgM_GaaSupervisedEntity[LddSEArrayIndex];

    /*Set the flag to WDGM_TRUE */
    #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
    LblASPass = WDGM_TRUE;
    #endif
    #if((WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)\
      ||(WDGM_ENABLE_LOGICAL_SUPERVISION == STD_ON))
    LblDSLSPass = WDGM_TRUE;
    #endif

    #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
    /* Load the configured failure tolerance    */
    /* polyspace<RTE:NIV:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    LucFailedTolerance = LpActiveSEList[LusActiveSECnt].ucFailedTolerance;

    /* Check whether the result of alive supervision for the SE is false */
    /* polyspace<RTE:OBAI:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
    /* polyspace<MISRA-C3:18.1:Not a defect> Its boundary is limited to array size */
    if ((WdgM_GaaSEStatus[LddSEArrayIndex] & WDGM_ALIVESUPERVISION_CORRECT) != WDGM_ALIVESUPERVISION_CORRECT)
    {
      /* Set the flag if the result of alive supervision is false */
      LblASPass = WDGM_FALSE;
    }
    #endif

    #if(WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)
    /* Check whether the result of deadline supervisions for the SE is false */
    if ((WdgM_GaaSEStatus[LddSEArrayIndex] & WDGM_DEADLINESUPERVISION_CORRECT)
      != WDGM_DEADLINESUPERVISION_CORRECT)
    {
      /* Set the flag if the result of either logical or deadline supervision
        is false */
      LblDSLSPass = WDGM_FALSE;
    }
    #endif

    #if(WDGM_ENABLE_LOGICAL_SUPERVISION == STD_ON)
    /* Check whether the result of logical supervisions for the SE is false */
    if ((WdgM_GaaSEStatus[LddSEArrayIndex] & WDGM_LGSUPERVISION_CORRECT)
      != WDGM_LGSUPERVISION_CORRECT)
    {
      /* Set the flag if the result of either logical or deadline supervision
        is false */
      LblDSLSPass = WDGM_FALSE;
    }
    #endif

    LucPreLocalStatus = WdgM_GaaSEStatus[LddSEArrayIndex] & WDGM_STATUS_MASK;
    LucNewLocalStatus = LucPreLocalStatus;
    switch (LucPreLocalStatus)
    {
    case WDGM_LOCAL_STATUS_OK:
      #if((WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)\
        ||(WDGM_ENABLE_LOGICAL_SUPERVISION == STD_ON))
      if(LblDSLSPass == WDGM_FALSE)
      {
        /* (2) WDGM_LOCAL_STATUS_OK -> WDGM_LOCAL_STATUS_EXPIRED */
        LucNewLocalStatus = WDGM_LOCAL_STATUS_EXPIRED;
      }
      else
      #endif
      {
        #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
        if (LblASPass == WDGM_FALSE)
        {
          if (LucFailedTolerance == WDGM_ZERO)
          {
            /* (2) WDGM_LOCAL_STATUS_OK -> WDGM_LOCAL_STATUS_EXPIRED */
            LucNewLocalStatus = WDGM_LOCAL_STATUS_EXPIRED;
            #if(WDGM_ERROR_INFO_API == STD_ON)
            if ((WdgM_GaaErrorInfo[LddSEArrayIndex].ddStatus
              == WDGM_LOCAL_STATUS_OK)
              || (WdgM_GaaErrorInfo[LddSEArrayIndex].ddStatus
              == WDGM_LOCAL_STATUS_FAILED))
            {
              WdgM_GaaErrorInfo[LddSEArrayIndex].ddStatus
                = WDGM_LOCAL_STATUS_EXPIRED;
            }
            #endif
          }
          else
          {
            /* (3) WDGM_LOCAL_STATUS_OK -> WDGM_LOCAL_STATUS_FAILED */
            LucNewLocalStatus = WDGM_LOCAL_STATUS_FAILED;

            WdgM_GddFailedRefCycleCounter[LddSEArrayIndex]++;
          }
        }
        else
        #endif
        {
          /* (1) WDGM_LOCAL_STATUS_OK -> WDGM_LOCAL_STATUS_OK */
        }
      }
      break;

    case WDGM_LOCAL_STATUS_FAILED:
      #if((WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)\
        ||(WDGM_ENABLE_LOGICAL_SUPERVISION == STD_ON))
      if(LblDSLSPass == WDGM_FALSE)
      {
        /* (6) WDGM_LOCAL_STATUS_FAILED -> WDGM_LOCAL_STATUS_EXPIRED */
        LucNewLocalStatus = WDGM_LOCAL_STATUS_EXPIRED;
      }
      else
      #endif
      {
        #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
        if (LblASPass == WDGM_FALSE)
        {
          if (WdgM_GddFailedRefCycleCounter[LddSEArrayIndex]
            >= LucFailedTolerance)
          {
            /* (6) WDGM_LOCAL_STATUS_FAILED -> WDGM_LOCAL_STATUS_EXPIRED */
            LucNewLocalStatus = WDGM_LOCAL_STATUS_EXPIRED;
            #if(WDGM_ERROR_INFO_API == STD_ON)
            if ((WdgM_GaaErrorInfo[LddSEArrayIndex].ddStatus
              == WDGM_LOCAL_STATUS_OK)
              || (WdgM_GaaErrorInfo[LddSEArrayIndex].ddStatus
              == WDGM_LOCAL_STATUS_FAILED))
            {
              WdgM_GaaErrorInfo[LddSEArrayIndex].ddStatus
                = WDGM_LOCAL_STATUS_EXPIRED;
            }
            #endif
          }
          else
          {
            /* (4) WDGM_LOCAL_STATUS_FAILED -> WDGM_LOCAL_STATUS_FAILED */
          }
          WdgM_GddFailedRefCycleCounter[LddSEArrayIndex]++;
        }
        else
        {
          if (WdgM_GddFailedRefCycleCounter[LddSEArrayIndex] == WDGM_ONE)
          {
            /* (5) WDGM_LOCAL_STATUS_FAILED -> WDGM_LOCAL_STATUS_OK */
            LucNewLocalStatus = WDGM_LOCAL_STATUS_OK;
          }
          else
          {
            /* (4) WDGM_LOCAL_STATUS_FAILED -> WDGM_LOCAL_STATUS_FAILED */
          }
          WdgM_GddFailedRefCycleCounter[LddSEArrayIndex]--;
        }
        #endif
      }
      break;

    case WDGM_LOCAL_STATUS_EXPIRED:
      LblSEExpiredFlag = WDGM_TRUE;
      break;

    case WDGM_LOCAL_STATUS_DEACTIVATED:
    default:
      /* do nothing */
      break;
    }

    if (LucPreLocalStatus != LucNewLocalStatus)
    {
      WdgM_GaaSEStatus[LddSEArrayIndex] =
        (WdgM_GaaSEStatus[LddSEArrayIndex] & WDGM_CLEAR_SE)
        | LucNewLocalStatus;
      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
      /* polyspace<RTE:COR:Not a defect:Justify with annotations> function pointer in configured by generator */
      /* polyspace<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
      /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
      (void)(*(LpSupervisedEntity->pRteSwitchMode))(LucNewLocalStatus);
      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
    }

    switch (LucNewLocalStatus)
    {
    case WDGM_LOCAL_STATUS_EXPIRED:
      LblSEExpiredFlag = WDGM_TRUE;
      break;

    case WDGM_LOCAL_STATUS_FAILED:
      LblSEFailedFlag = WDGM_TRUE;
      #if(WDGM_ENABLE_OS_APPLICATION == STD_ON)
      if ((LpSupervisedEntity->ucSupervisions & WDGM_B5_APPLICATION)
        == WDGM_B5_APPLICATION)
      {
        SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
        BswM_WdgM_RequestPartitionReset(LpSupervisedEntity->ddApplication);
        SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
      }
      #endif
      break;

    case WDGM_LOCAL_STATUS_OK:
      break;

    default:
      /* do nothing */
      break;
    }

    /* Check whether the current SE is the first one to go to
      WDGM_LOCAL_STATUS_EXPIRED status */
    if ((LblSEExpiredFlag == WDGM_TRUE)
      && (WdgM_GblFirstExpSEIDStatus == WDGM_FALSE))
    {
      /* polyspace:begin<RTE:NIV:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
      /* Write the value of SEID into NON-Initialized RAM area */
      WdgM_GddFirstExpiredSEID = LpActiveSEList[LusActiveSECnt].ddSEId;
      /* Write the inverse value of SEID into NON-Initialized RAM area */
      WdgM_GddInvFirstExpiredSEID = (WdgM_SupervisedEntityIdType)(~LpActiveSEList[LusActiveSECnt].ddSEId);
      WdgM_GblFirstExpSEIDStatus = WDGM_TRUE;
      /* polyspace:end<RTE:NIV> */
    }
    LusActiveSECnt++;
  } /* LusActiveSECnt < LpCurrentMode->ddTotalSEInMode */

  *pSEFailedFlag = LblSEFailedFlag;
  *pSEExpiredFlag = LblSEExpiredFlag;

  SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
}
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : WdgM_EvaluateGlobalStatus                             **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service evaluates the global supervision status  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : blSEFailedFlag, blSEExpiredFlag                       **
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
**                      WdgM_GaaModes,                                        **
**                      WdgM_GddCurrentMode,                                  **
**                      WdgM_GddGlobalSupervisionStatus,                      **
**                      WdgM_GddInvGlobalSupervisionStatus,                   **
**                      WdgM_GddExpSupervisionCycleCounter,                   **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      WdgM_TriggerWdgIf,                                    **
**                      Dem_ReportErrorStatus,                                **
**                      Mcu_PerformReset,                                     **
**                      Rte_Switch_globalMode_currentMode,                    **
**                      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,        **
**                      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION          **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_EvaluateGlobalStatus(
  boolean blSEFailedFlag, boolean blSEExpiredFlag)
{
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST)LpModes;
  WdgM_GlobalStatusType LddPreGlobalStatus;
  WdgM_GlobalStatusType LddNewGlobalStatus;
  uint16 LusExpireTolerance;
  WdgM_GlobalStatusType LddInvSupervisionStatus;

  SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();

  LpModes = &WdgM_GaaModes[WdgM_GddCurrentMode];
  /* polyspace<RTE:IDP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
  /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
  LusExpireTolerance = LpModes->usWdgTrigBlockCount;
  LddPreGlobalStatus = WdgM_GddGlobalSupervisionStatus;
  LddNewGlobalStatus = WdgM_GddGlobalSupervisionStatus;
  LddInvSupervisionStatus = ~WdgM_GddInvGlobalSupervisionStatus;

  /* check whether double inverse value match */
  if (WdgM_GddGlobalSupervisionStatus == LddInvSupervisionStatus)
  {
    switch (LddPreGlobalStatus)
    {
    case WDGM_GLOBAL_STATUS_OK:
      if (blSEExpiredFlag == WDGM_TRUE)
      {
        if (LusExpireTolerance == WDGM_ZERO)
        {
          /* (4) WDGM_GLOBAL_STATUS_OK -> WDGM_GLOBAL_STATUS_STOPPED */
          LddNewGlobalStatus = WDGM_GLOBAL_STATUS_STOPPED;
        }
        else
        {
          /* (3) WDGM_GLOBAL_STATUS_OK -> WDGM_GLOBAL_STATUS_EXPIRED */
          LddNewGlobalStatus = WDGM_GLOBAL_STATUS_EXPIRED;

          WdgM_GddExpSupervisionCycleCounter++;
        }
      }
      else
      {
        if (blSEFailedFlag == WDGM_TRUE)
        {
          /* (2) WDGM_GLOBAL_STATUS_OK -> WDGM_GLOBAL_STATUS_FAILED */
          LddNewGlobalStatus = WDGM_GLOBAL_STATUS_FAILED;
        }
        else
        {
          /* (1) WDGM_GLOBAL_STATUS_OK -> WDGM_GLOBAL_STATUS_OK */
          LddNewGlobalStatus = WDGM_GLOBAL_STATUS_OK;
        }
      }
      break;

    case WDGM_GLOBAL_STATUS_FAILED:
      if (blSEExpiredFlag == WDGM_TRUE)
      {
        if (LusExpireTolerance == WDGM_ZERO)
        {
          /* (8) WDGM_GLOBAL_STATUS_FAILED -> WDGM_GLOBAL_STATUS_STOPPED */
          LddNewGlobalStatus = WDGM_GLOBAL_STATUS_STOPPED;
        }
        else
        {
          /* (7) WDGM_GLOBAL_STATUS_FAILED -> WDGM_GLOBAL_STATUS_EXPIRED */
          LddNewGlobalStatus = WDGM_GLOBAL_STATUS_EXPIRED;

          WdgM_GddExpSupervisionCycleCounter++;
        }
      }
      else
      {
        if (blSEFailedFlag == WDGM_TRUE)
        {
          /* (5) WDGM_GLOBAL_STATUS_FAILED -> WDGM_GLOBAL_STATUS_FAILED */
          LddNewGlobalStatus = WDGM_GLOBAL_STATUS_FAILED;
        }
        else
        {
          /* (6) WDGM_GLOBAL_STATUS_FAILED -> WDGM_GLOBAL_STATUS_OK */
          LddNewGlobalStatus = WDGM_GLOBAL_STATUS_OK;
        }
      }
      break;

    case WDGM_GLOBAL_STATUS_EXPIRED:
      if (blSEExpiredFlag == WDGM_TRUE)
      {
        if (WdgM_GddExpSupervisionCycleCounter < LusExpireTolerance)
        {
          /* (9) WDGM_GLOBAL_STATUS_EXPIRED -> WDGM_GLOBAL_STATUS_EXPIRED */
          LddNewGlobalStatus = WDGM_GLOBAL_STATUS_EXPIRED;

          WdgM_GddExpSupervisionCycleCounter++;
        }
        else
        {
          /* (10) WDGM_GLOBAL_STATUS_EXPIRED -> WDGM_GLOBAL_STATUS_STOPPED */
          LddNewGlobalStatus = WDGM_GLOBAL_STATUS_STOPPED;
        }
      }
      else
      {
        /* Impossible */
      }
      break;

    case WDGM_GLOBAL_STATUS_STOPPED:
      LddNewGlobalStatus = WDGM_GLOBAL_STATUS_STOPPED;
      break;

    case WDGM_GLOBAL_STATUS_DEACTIVATED:
      LddNewGlobalStatus = WDGM_GLOBAL_STATUS_DEACTIVATED;
      break;

    default:
      /* Do nothing */
      break;
    }
  }
  else
  {
    /* if not matched, stop it */
    LddNewGlobalStatus = WDGM_GLOBAL_STATUS_STOPPED;
  }

  WdgM_GddGlobalSupervisionStatus = LddNewGlobalStatus;
  WdgM_GddInvGlobalSupervisionStatus = ~WdgM_GddGlobalSupervisionStatus;

  SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();

  switch (LddNewGlobalStatus)
  {
  case WDGM_GLOBAL_STATUS_OK:
  case WDGM_GLOBAL_STATUS_FAILED:
  case WDGM_GLOBAL_STATUS_EXPIRED:
    WdgM_TriggerWdgIf(LpModes, WDGM_TM_NORMAL);
    break;

  case WDGM_GLOBAL_STATUS_STOPPED:
  case WDGM_GLOBAL_STATUS_DEACTIVATED:
  default:
    /* Do nothing */
    break;
  }

  if(LddPreGlobalStatus != LddNewGlobalStatus)
  {
    switch (LddNewGlobalStatus)
    {
    case WDGM_GLOBAL_STATUS_OK:
    case WDGM_GLOBAL_STATUS_FAILED:
    case WDGM_GLOBAL_STATUS_EXPIRED:
      /* Report global state to Rte after every supervision cycle */
      (void)Rte_Switch_globalMode_currentMode(LddNewGlobalStatus);
      break;

    /* case WDGM_GLOBAL_STATUS_STOPPED is removed for code coverage test */
    /* and case WDGM_GLOBAL_STATUS_STOPPED will be handled at default */
    /* case WDGM_GLOBAL_STATUS_STOPPED: */
    default:
      #if(WDGM_DEM_ERROR_REPORT == STD_ON)
      #if(WDGM_DEM_STOPPED_SUPERVISION_REPORT == STD_ON)
      Dem_ReportErrorStatus(WdgM_GddEMonitoring, DEM_EVENT_STATUS_FAILED);
      #endif
      #endif
      #if(WDGM_IMMEDIATE_RESET == STD_ON)
      Mcu_PerformReset();
      #else
      /* Report global state to Rte after every supervision cycle */
      (void)Rte_Switch_globalMode_currentMode(LddNewGlobalStatus);
      #endif
      WdgM_TriggerWdgIf(LpModes, WDGM_TM_TIMEOUT);
      break;
    }
  }
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
