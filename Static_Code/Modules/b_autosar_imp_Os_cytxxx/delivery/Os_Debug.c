/*******************************************************************************
**                                                                            **
**  (C) 2020 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Os_Debug.c                                                    **
**                                                                            **
**  TARGET    : CYTxxx                                                        **
**                                                                            **
**  PRODUCT   : AUTOSAR OS Improvement Code                                   **
**                                                                            **
**  PURPOSE   : Provision of Debugging features functionality                 **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 2.0.0     08-Jul-2020    JH.Cho        Redmine #24402                      **
** 1.0.0     25-Feb-2020    MJ.Woo        Redmine #20864                      **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<RTE:ABS_ADDR:Not a defect:Justify with annotations> Absolute address is needed to access MCU register */
/* polyspace:begin<RTE:OBAI:Not a defect:Justify with annotations> configured array index */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_Debug.h"
#include "Os_Ram.h"
#include "Os_Arch_Context.h"
#include "Os_Arch_Interrupt.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:8.7:Not a defect:Justify with annotations> variables can be used for test application */
#define OS_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
/** This global variable used to save elapsed CPU time. */
VAR(uint32, OS_VAR) Os_GulCPUTimeElapsed[OS_CORE_COUNT];
/** This global variable used to save previous timestamp for CPU load. */
VAR(uint32, OS_VAR) Os_GulTimestampBefore[OS_CORE_COUNT];
/** This global variable used to save idle time. */
VAR(uint32, OS_VAR) Os_GulCPUTimeInIdle[OS_CORE_COUNT];
/** This global variable used to save interrupt time. */
VAR(uint32, OS_VAR) Os_GulCPUTimeInIT[OS_CORE_COUNT];
/** This global variable used to save timestamp when enter idle mode. */
VAR(uint32, OS_VAR) Os_GulIdleEntryTime[OS_CORE_COUNT];
/** This global variable used to save timestamp when enter interrupt context. */
VAR(uint32, OS_VAR) Os_GulITEntryTime[OS_CORE_COUNT];
/** This global variable used to save count of measures. */
VAR(uint32, OS_VAR) Os_GulMeasureCount[OS_CORE_COUNT];
#define OS_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/** This global variable used to save CPU load. */
VAR(uint16, OS_VAR) Os_GusCPULoad[OS_CORE_COUNT];
/** This global variable used to save Interrupt load. */
VAR(uint16, OS_VAR) Os_GusITLoad[OS_CORE_COUNT];
/** This global variable used to save peak CPU load. */
VAR(uint16, OS_VAR) Os_GusCPULoadPeak[OS_CORE_COUNT];
/** This global variable used to save peak Interrupt load. */
VAR(uint16, OS_VAR) Os_GusITLoadPeak[OS_CORE_COUNT];
/** This global variable used to save mean CPU load. */
VAR(uint16, OS_VAR) Os_GusCPULoadMean[OS_CORE_COUNT];
/** This global variable used to save mean Interrupt load. */
VAR(uint16, OS_VAR) Os_GusITLoadMean[OS_CORE_COUNT];
#define OS_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/** This global variable used to save sum of Interrupt load. */
VAR(uint64, OS_VAR) Os_GullITLoadSum[OS_CORE_COUNT];
/** This global variable used to save sum of CPU load. */
VAR(uint64, OS_VAR) Os_GullCPULoadSum[OS_CORE_COUNT];
#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"


#define OS_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/** This global Variable used as a flag to hold idle mode. */
VAR(boolean, OS_VAR) Os_GblInIdleMode[OS_CORE_COUNT];
/** This global variable used to indicate entry of idle task. */
VAR(boolean, OS_VAR) Os_GblEntryIdleTask[OS_CORE_COUNT];
/** This global Variable used to check that 'wait' instruction is not called */
VAR(boolean, OS_VAR) Os_GblBeforeHalt[OS_CORE_COUNT];
#define OS_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/** This global Variable used to check the interrupt context. */
VAR(uint8, OS_VAR) Os_GucITCount[OS_CORE_COUNT];
/** This global variable used to save Idle Task ID. */
VAR(TaskType, OS_VAR) Os_GddIdleTaskId[OS_CORE_COUNT];
#define OS_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/** This global Variable indicates that Power Mode transition is occurred. */
VAR(boolean, OS_VAR) Os_GblPmTransFlag;
#define OS_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* polyspace:end<MISRA-C3:8.7> */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define OS_START_SEC_CODE
#include "MemMap.h"

#if (OS_DEBUG_CPULOAD == STD_ON)
static INLINE FUNC(void, OS_CODE) Os_SumCPUTimeInIT(uint32 LulTimestampNow);
#endif

/***************************************************************************//**
 * Function Name        : Os_Idle
 *
 * Service ID           : NA
 *
 * Description          : This function is for Idle mode
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        Os_SetIdleForCPULoad
 ******************************************************************************/
FUNC(void, OS_CODE) Os_Idle(CoreIDType LddCoreId)
{
  OS_UNUSED(LddCoreId);
  #if (OS_DEBUG_CPULOAD == STD_ON)
  /* TODO: New service ControleIdle() @ R4.1.1 */
  Os_SetIdleForCPULoad();
  #else
  Os_Halt();
  #endif
}

#if (OS_DEBUG_CPULOAD == STD_ON)
/***************************************************************************//**
 * Function Name        : Os_InitCPULoad
 *
 * Service ID           : NA
 *
 * Description          : This function initializes CPU and IT load variables.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GulCPUTimeElapsed, Os_GulTimestampBefore,
 *                        Os_GulCPUTimeInIdle, Os_GulIdleEntryTime,
 *                        Os_GblInIdleMode, Os_GulCPUTimeInIT,
 *                        Os_GulITEntryTime, Os_GucITCount, Os_GusCPULoad,
 *                        Os_GusITLoad, Os_GusCPULoadPeak, Os_GusITLoadPeak,
 *                        Os_GusCPULoadMean, Os_GusITLoadMean,
 *                        Os_GullCPULoadSum, Os_GullITLoadSum,
 *                        Os_GulMeasureCount, Os_GblPmTransFlag,
 *                        Os_GblEntryIdleTask
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(void, OS_CODE) Os_InitCPULoad(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* polyspace<MISRA-C3:D4.1:Not a defect:Justify with annotations> pre-defined index is used */
  /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> pre-defined index is used */
  Os_GulCPUTimeElapsed[OS_CORE_ID] = OS_ZERO;

  /* polyspace<MISRA-C3:11.3:Not a defect:Justify with annotations> pointer to integral type should be used to access register */
  Os_GulTimestampBefore[OS_CORE_ID] = OS_GET_TIMESTAMP();

  /* Init value is set to ignore first measurement */
  Os_GulCPUTimeInIdle[OS_CORE_ID] = 0x7FFFFFFFu;
  Os_GulIdleEntryTime[OS_CORE_ID] = OS_ZERO;
  Os_GblInIdleMode[OS_CORE_ID] = OS_FALSE;

  Os_GulCPUTimeInIT[OS_CORE_ID] = OS_ZERO;
  Os_GulITEntryTime[OS_CORE_ID] = OS_ZERO;
  Os_GucITCount[OS_CORE_ID] = OS_ZERO;

  Os_GusCPULoad[OS_CORE_ID] = OS_ZERO;
  Os_GusITLoad[OS_CORE_ID] = OS_ZERO;
  Os_GusCPULoadPeak[OS_CORE_ID] = OS_ZERO;
  Os_GblEntryIdleTask[OS_CORE_ID] = OS_FALSE;
  Os_GusITLoadPeak[OS_CORE_ID] = OS_ZERO;
  Os_GusCPULoadMean[OS_CORE_ID] = OS_ZERO;
  Os_GusITLoadMean[OS_CORE_ID] = OS_ZERO;
  Os_GullCPULoadSum[OS_CORE_ID] = OS_ZERO;
  Os_GullITLoadSum[OS_CORE_ID] = OS_ZERO;
  Os_GulMeasureCount[OS_CORE_ID] = OS_ZERO;

  Os_GblPmTransFlag = OS_FALSE;
}
#endif /* if (OS_DEBUG_CPULOAD == STD_ON) */

#if (OS_DEBUG_CPULOAD == STD_ON)
/***************************************************************************//**
 * Function Name        : Os_ITEntryForCPULoad
 *
 * Service ID           : NA
 *
 * Description          : Update idle time.
 *                        Start CPU occupancy time measure in Interrupt.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GulCPUTimeInIdle, Os_GulIdleEntryTime,
 *                        Os_GblInIdleMode, Os_GulITEntryTime, Os_GucITCount
 *                        Os_GblEntryIdleTask
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(void, OS_CODE) Os_ITEntryForCPULoad(void)
{
  uint32 LulTimestampNow;
  uint32 LulCPUTimeInIdle;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* polyspace<MISRA-C3:11.3:Not a defect:Justify with annotations> pointer to integral type should be used to access register */
  LulTimestampNow =  OS_GET_TIMESTAMP();

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* polyspace<MISRA-C3:D4.1:Not a defect:Justify with annotations> pre-defined index is used */
  /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> pre-defined index is used */
  /* set Os_GblInIdleMode to TRUE if it is from idle task */
  if (Os_GblEntryIdleTask[OS_CORE_ID] == OS_TRUE)
  {
    Os_GblInIdleMode[OS_CORE_ID] = OS_TRUE;
  }

  /* Sum CPU time in IDLE */
  if (Os_GblInIdleMode[OS_CORE_ID] == OS_TRUE)
  {
    Os_GblInIdleMode[OS_CORE_ID] = OS_FALSE;

    if (LulTimestampNow >= Os_GulIdleEntryTime[OS_CORE_ID])
    {
      LulCPUTimeInIdle = (LulTimestampNow - Os_GulIdleEntryTime[OS_CORE_ID]);
    }
    else
    {
      LulCPUTimeInIdle = (OS_TIMESTAMP_MAX - Os_GulIdleEntryTime[OS_CORE_ID]);
      LulCPUTimeInIdle += (LulTimestampNow + OS_ONE);
    }

    /* add to Os_GulCPUTimeInIdle the duration of idle mode */
    Os_GulCPUTimeInIdle[OS_CORE_ID] += LulCPUTimeInIdle;

    /* reset idle entry time */
    if (Os_GblEntryIdleTask[OS_CORE_ID] == OS_TRUE)
    {
      /* polyspace:begin<MISRA-C:11.3:Not a defect:Justify with annotations> pointer to integral type should be used to access register */
      Os_GulIdleEntryTime[OS_CORE_ID] = OS_GET_TIMESTAMP();
      /* polyspace:end<MISRA-C:11.3> */
    }
  }

  /* Record IT entry time */
  if (Os_GucITCount[OS_CORE_ID] == OS_ZERO)
  {
    Os_GulITEntryTime[OS_CORE_ID] = LulTimestampNow;
  }
  Os_GucITCount[OS_CORE_ID]++;
}

/***************************************************************************//**
 * Function Name        : Os_SumCPUTimeInIT
 *
 * Service ID           : NA
 *
 * Description          : Update CPU time used in ISR.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param[in]             LulTimestampNow    Current timestamp
 *                                           (range : 0 ~ OS_TIMESTAMP_MAX)
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GulCPUTimeInIT, Os_GulITEntryTime
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
static INLINE FUNC(void, OS_CODE) Os_SumCPUTimeInIT(uint32 LulTimestampNow)
{
  uint32 LulCPUTimeInIT;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* polyspace<MISRA-C3:D4.1:Not a defect:Justify with annotations> pre-defined index is used */
  /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> pre-defined index is used */
  if (LulTimestampNow >= Os_GulITEntryTime[OS_CORE_ID])
  {
    LulCPUTimeInIT = (LulTimestampNow - Os_GulITEntryTime[OS_CORE_ID]);
  }
  else
  {
    LulCPUTimeInIT = (OS_TIMESTAMP_MAX - Os_GulITEntryTime[OS_CORE_ID]);
    LulCPUTimeInIT += (LulTimestampNow + OS_ONE);
  }

  /* add to Os_GulCPUTimeInIT the duration of ISR */
  Os_GulCPUTimeInIT[OS_CORE_ID] += LulCPUTimeInIT;
}

/***************************************************************************//**
 * Function Name        : Os_ITExitForCPULoad
 *
 * Service ID           : NA
 *
 * Description          : Stop CPU occupancy time measure in Interrupt.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GucITCount
 *
 *                        Function(s) invoked    :
 *                        Os_SumCPUTimeInIT()
 ******************************************************************************/
FUNC(void, OS_CODE) Os_ITExitForCPULoad(void)
{
  uint32 LulTimestampNow;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* polyspace<MISRA-C3:11.3:Not a defect:Justify with annotations> pointer to integral type should be used to access register */
  LulTimestampNow = OS_GET_TIMESTAMP();

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* polyspace<MISRA-C3:D4.1:Not a defect:Justify with annotations> pre-defined index is used */
  /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> pre-defined index is used */
  /* Sum CPU time in IT */
  Os_GucITCount[OS_CORE_ID]--;
  if (Os_GucITCount[OS_CORE_ID] == OS_ZERO)
  {
    Os_SumCPUTimeInIT(LulTimestampNow);
  }
}

/***************************************************************************//**
 * Function Name        : Os_ResetIdleEntry
 *
 * Service ID           : NA
 *
 * Description          : If an Interrupt is occurred after set idle flag but
 *                        not passed Halt(wait mode), then reset idle flag and
 *                        idle entry time
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : This function should be called from PreTaskHook()
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GblBeforeHalt, Os_GblInIdleMode,
 *                        Os_GulIdleEntryTime, Os_GddIdleTaskId, Os_GpLinkTask
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(void, OS_CODE) Os_ResetIdleEntry(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
  /* polyspace<RTE: IDP : Not a defect : Justify with annotations > configured memory access index */
  /* polyspace<MISRA-C3:D4.1:Not a defect:Justify with annotations> pre-defined index is used */
  /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> pre-defined index is used */
  if ((Os_GddIdleTaskId[OS_CORE_ID] == Os_GpLinkTask[OS_CORE_ID]->ddTaskID) &&
      (Os_GblBeforeHalt[OS_CORE_ID] == OS_TRUE))
  {
    Os_GblInIdleMode[OS_CORE_ID] = OS_TRUE;
    Os_GblEntryIdleTask[OS_CORE_ID] = OS_TRUE;
    /* polyspace<MISRA-C3:11.3:Not a defect:Justify with annotations> pointer to integral type should be used to access register */
    Os_GulIdleEntryTime[OS_CORE_ID] = OS_GET_TIMESTAMP();
  }
  else
  {
    Os_GblEntryIdleTask[OS_CORE_ID] = OS_FALSE;
  }
}
/***************************************************************************//**
 * Function Name        : Os_MeasureCPULoad
 *
 * Service ID           : NA
 *
 * Description          : This function measures CPU and IT load.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GulCPUTimeElapsed, Os_GulTimestampBefore,
 *                        Os_GulCPUTimeInIdle, Os_GusCPULoad, Os_GusITLoad,
 *                        Os_GusCPULoadPeak, Os_GusITLoadPeak,
 *                        Os_GblPmTransFlag, Os_GusCPULoadMean,
 *                        Os_GusITLoadMean, Os_GullITLoadSum, Os_GullCPULoadSum
 *
 *                        Function(s) invoked    :
 *                        Os_SumCPUTimeInIT()
 ******************************************************************************/
/* polyspace<MISRA-C3:8.7:Not a defect:Justify with annotations> below function can be used with external */
FUNC(void, OS_CODE) Os_MeasureCPULoad(void)
{

  uint32 LulTimestampNow;
  uint32 LulCPUTimeElapsed;
  uint32 LulCPULoad;
  uint32 LulMeasureCount;
  boolean LblMeasurementFail = OS_FALSE;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* polyspace<MISRA-C3:11.3:Not a defect:Justify with annotations> pointer to integral type should be used to access register */
  LulTimestampNow = OS_GET_TIMESTAMP();

  /* polyspace<MISRA-C3:D4.1:Not a defect:Justify with annotations> pre-defined index is used */
  /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> pre-defined index is used */
  /* Get the elapsed time since entering here last. */
  if (LulTimestampNow > Os_GulTimestampBefore[OS_CORE_ID])
  {
    LulCPUTimeElapsed = (LulTimestampNow - Os_GulTimestampBefore[OS_CORE_ID]);
  }
  else if (LulTimestampNow < Os_GulTimestampBefore[OS_CORE_ID])
  {
    LulCPUTimeElapsed = (OS_TIMESTAMP_MAX - Os_GulTimestampBefore[OS_CORE_ID]);
    LulCPUTimeElapsed += (LulTimestampNow + OS_ONE);
  }
  else
  {
    LulCPUTimeElapsed = OS_TIMESTAMP_MAX;
  }
  Os_GulTimestampBefore[OS_CORE_ID] = LulTimestampNow;

  /* If entering to Low Power Mode, restart CPU Load measure */
  if (Os_GblPmTransFlag == OS_TRUE)
  {
    LblMeasurementFail = OS_TRUE;
    Os_GblPmTransFlag = OS_FALSE;
  }
  /* Os_GulCPUTimeElapsed overflows */
  else if ((OS_TIMESTAMP_MAX - Os_GulCPUTimeElapsed[OS_CORE_ID]) < LulCPUTimeElapsed)
  {
    LblMeasurementFail = OS_TRUE;
  }
  else
  {
    Os_GulCPUTimeElapsed[OS_CORE_ID] += LulCPUTimeElapsed;
    /* In case that OS enters the idle state rarely
     * or measurement interval is too small
     */
    if ((Os_GulCPUTimeElapsed[OS_CORE_ID] < Os_GulCPUTimeInIdle[OS_CORE_ID]) ||
        (Os_GulCPUTimeElapsed[OS_CORE_ID] < Os_GulCPUTimeInIT[OS_CORE_ID]))
    {
      LblMeasurementFail = OS_TRUE;
    }
  }

  if (LblMeasurementFail == OS_FALSE)
  {
    if (Os_GulCPUTimeElapsed[OS_CORE_ID]<(OS_TIMESTAMP_MAX/OS_FULL_PERMILLAGE))
    {
      /* Calculate CPU load */
      LulCPULoad = Os_GulCPUTimeElapsed[OS_CORE_ID] -
                                              Os_GulCPUTimeInIdle[OS_CORE_ID];
      LulCPULoad = (LulCPULoad * OS_FULL_PERMILLAGE) /
                                             Os_GulCPUTimeElapsed[OS_CORE_ID];
      Os_GusCPULoad[OS_CORE_ID] = (uint16)LulCPULoad;
      /* Calculate IT load */
      /* If current context is ISR */
      if (Os_GucITCount[OS_CORE_ID] > OS_ZERO)
      {
        Os_SumCPUTimeInIT(LulTimestampNow);
        /* Updating Interrupt entry time is required
         * when call this function in ISR */
        Os_GulITEntryTime[OS_CORE_ID] = LulTimestampNow;
      }
      LulCPULoad = Os_GulCPUTimeInIT[OS_CORE_ID];
      LulCPULoad = (LulCPULoad * OS_FULL_PERMILLAGE) /
                                             Os_GulCPUTimeElapsed[OS_CORE_ID];
      Os_GusITLoad[OS_CORE_ID] = (uint16)LulCPULoad;
    }
    else
    {
      /* Calculate CPU load */
      LulCPULoad = Os_GulCPUTimeElapsed[OS_CORE_ID] -
                                              Os_GulCPUTimeInIdle[OS_CORE_ID];
      LulCPULoad = LulCPULoad /
                      (Os_GulCPUTimeElapsed[OS_CORE_ID] / OS_FULL_PERMILLAGE);
      Os_GusCPULoad[OS_CORE_ID] = (uint16)LulCPULoad;
      /* Calculate IT load */
      /* If current context is ISR */
      if (Os_GucITCount[OS_CORE_ID] > OS_ZERO)
      {
        Os_SumCPUTimeInIT(LulTimestampNow);
        /* Updating Interrupt entry time is required
         * when call this function in ISR */
        Os_GulITEntryTime[OS_CORE_ID] = LulTimestampNow;
      }
      LulCPULoad = Os_GulCPUTimeInIT[OS_CORE_ID];
      LulCPULoad = LulCPULoad /
                      (Os_GulCPUTimeElapsed[OS_CORE_ID] / OS_FULL_PERMILLAGE);
      Os_GusITLoad[OS_CORE_ID] = (uint16)LulCPULoad;
    }

    /* Update peak load */
    /* Exclude illegal output of CPU load  */
    if (Os_GusCPULoad[OS_CORE_ID] <= OS_FULL_PERMILLAGE)
    {
      if (Os_GusCPULoad[OS_CORE_ID] > Os_GusCPULoadPeak[OS_CORE_ID])
      {
        Os_GusCPULoadPeak[OS_CORE_ID] = Os_GusCPULoad[OS_CORE_ID];
      }
    }

    if (Os_GusITLoad[OS_CORE_ID] <= OS_FULL_PERMILLAGE)
    {
      if (Os_GusITLoad[OS_CORE_ID] > Os_GusITLoadPeak[OS_CORE_ID])
      {
        Os_GusITLoadPeak[OS_CORE_ID] = Os_GusITLoad[OS_CORE_ID];
      }
    }

    /* Update mean load */
    if(Os_GulMeasureCount[OS_CORE_ID] < OS_MEASURECOUNT_MAX)
    {
      Os_GulMeasureCount[OS_CORE_ID]++;
    }
    LulMeasureCount = Os_GulMeasureCount[OS_CORE_ID];

    Os_GullITLoadSum[OS_CORE_ID] += Os_GusITLoad[OS_CORE_ID];
    Os_GullCPULoadSum[OS_CORE_ID] += Os_GusCPULoad[OS_CORE_ID];
    Os_GusITLoadMean[OS_CORE_ID] = (uint16)(Os_GullITLoadSum[OS_CORE_ID] /
      LulMeasureCount);
    Os_GusCPULoadMean[OS_CORE_ID] = (uint16)(Os_GullCPULoadSum[OS_CORE_ID] /
      LulMeasureCount);

    if(LulMeasureCount == OS_MEASURECOUNT_MAX)
    {
      Os_GulMeasureCount[OS_CORE_ID] = OS_ZERO;
      Os_GullITLoadSum[OS_CORE_ID] = OS_ZERO;
      Os_GullCPULoadSum[OS_CORE_ID] = OS_ZERO;
    }

  }

    /* Restart measurement */
    Os_GulCPUTimeElapsed[OS_CORE_ID] = OS_ZERO;
    Os_GulCPUTimeInIdle[OS_CORE_ID] = OS_ZERO;
    Os_GulCPUTimeInIT[OS_CORE_ID] = OS_ZERO;

}

/***************************************************************************//**
 * Function Name        : Os_SetIdleForCPULoad
 *
 * Service ID           : NA
 *
 * Description          : Start CPU idle time measure and enter wait state
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : None Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GblInIdleMode, Os_GulIdleEntryTime,
 *                        Os_GblBeforeHalt, Os_GddIdleTaskId, Os_GpLinkTask
 *
 *                        Function(s) invoked    :
 *                        Os_Halt()
 ******************************************************************************/
/* polyspace<MISRA-C3:8.7:Not a defect:Justify with annotations> below function can be used with external */
FUNC(void, OS_CODE) Os_SetIdleForCPULoad(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
  /* polyspace<RTE: IDP : Not a defect : Justify with annotations > configured memory access index */
  /* polyspace<MISRA-C3:D4.1:Not a defect:Justify with annotations> pre-defined index is used */
  /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> pre-defined index is used */
  Os_GddIdleTaskId[OS_CORE_ID] = Os_GpLinkTask[OS_CORE_ID]->ddTaskID;

  if (Os_GblInIdleMode[OS_CORE_ID] == OS_FALSE)
  {
    #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
    OS_DISABLEINTERRUPTS();
    #endif

    Os_GblInIdleMode[OS_CORE_ID] = OS_TRUE;
	/* polyspace<MISRA-C:11.3:Not a defect:Justify with annotations> This is to access registers which are assigned to absolute address  */
    Os_GulIdleEntryTime[OS_CORE_ID] = OS_GET_TIMESTAMP();
    Os_GblBeforeHalt[OS_CORE_ID] = OS_TRUE;

    #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
    OS_ENABLEINTERRUPTS();
    #endif
  }
  /* Wait until an interrupt occurs */
  Os_Halt();
  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> pre-defined index is used */
  /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> pre-defined index is used */
  Os_GblBeforeHalt[OS_CORE_ID] = OS_FALSE;
  Os_GblInIdleMode[OS_CORE_ID] = OS_FALSE;
  /* polyspace:end<MISRA-C3:D4.1> */
}

/***************************************************************************//**
 * Function Name        : Os_ClearCPULoadPeak
 *
 * Service ID           : NA
 *
 * Description          : Clear CPU Load Peak value in current core.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GusCPULoadPeak
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(void, OS_CODE) Os_ClearCPULoadPeak(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> pre-defined index is used */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> pre-defined index is used */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  Os_GusCPULoadPeak[OS_CORE_ID] = OS_ZERO;
  /* polyspace:end<MISRA-C3:D4.1> */
  /* polyspace:end<MISRA-C3:18.1> */
}

/***************************************************************************//**
 * Function Name        : Os_ClearITLoadPeak
 *
 * Service ID           : NA
 *
 * Description          : Clear Interrupt Load Peak value in current core.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GusITLoadPeak
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(void, OS_CODE) Os_ClearITLoadPeak(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> pre-defined index is used */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> pre-defined index is used */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  Os_GusITLoadPeak[OS_CORE_ID] = OS_ZERO;
  /* polyspace:end<MISRA-C3:D4.1> */
  /* polyspace:end<MISRA-C3:18.1> */
}

/***************************************************************************//**
 * Function Name        : Os_UserGetCPULoad
 *
 * Service ID           : NA
 *
 * Description          : This service is used to get CPU and Interrupt Load.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : None Re-entrant
 *
 * @param[out]            LpLoad     A pointer for save CPU and IT load
 * @param[in]             restart    OS_TRUE : Get load and restart measurement
 *                                   OS_FALSE : Just get load
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GusCPULoad, Os_GusCPULoadPeak, Os_GusITLoad,
 *                        Os_GusITLoadPeak
 *
 *                        Function(s) invoked    :
 *                        Os_IntDisableAll(), Os_MeasureCPULoad(),
 *                        Os_IntRestore()
 ******************************************************************************/
FUNC(void, OS_CODE) Os_UserGetCPULoad(
                  P2VAR(Os_LoadType, AUTOMATIC, OS_VAR) LpLoad, boolean restart)
{
  #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
  Os_OldLevel_T is;
  #endif
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
  is = OS_DISABLE_AND_SAVE_INTERRUPTS();
  #endif

  if (restart == OS_TRUE)
  {
    Os_MeasureCPULoad();
  }

  /* polyspace<RTE: UNR : Not a defect : No Action Planned > NULL pointer check */
  if (LpLoad != NULL_PTR)
  {
    /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> pre-defined index is used */
	/* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justify with annotations> Already checked wheter it is NULL or not */
    /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> pre-defined index is used */
    LpLoad->usCPULoad = Os_GusCPULoad[OS_CORE_ID];
    LpLoad->usCPULoadPeak = Os_GusCPULoadPeak[OS_CORE_ID];
    LpLoad->usCPULoadMean = Os_GusCPULoadMean[OS_CORE_ID];
    LpLoad->usITLoad = Os_GusITLoad[OS_CORE_ID];
    LpLoad->usITLoadPeak = Os_GusITLoadPeak[OS_CORE_ID];
    LpLoad->usITLoadMean = Os_GusITLoadMean[OS_CORE_ID];
    /* polyspace:end<MISRA-C3:D4.1> */
	/* polyspace:end<MISRA-C3:D4.14> */
  }

  #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
  OS_RESTORE_INTERRUPTS(is);
  #endif
}

/***************************************************************************//**
 * Function Name        : Os_DebugH2L
 *
 * Service ID           : NA
 *
 * Description          : Set a flag which indicates Power Mode transition
 *                        This function is called at PM transition
 *                        (High Power -> Low Power)
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_PmTransFlag
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(void, OS_CODE) Os_DebugH2L(void)
{
  Os_GblPmTransFlag = OS_TRUE;
}

/***************************************************************************//**
 * Function Name        : Os_RestartMeanLoad
 *
 * Service ID           : NA
 *
 * Description          : This service is used to restart the measure of
 *                        the mean of CPU/IT load.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GulMeasureCount
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(void, OS_CODE) Os_RestartMeanLoad(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> pre-defined index is used */
  /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> pre-defined index is used */
  Os_GulMeasureCount[OS_CORE_ID] = OS_ZERO;
  Os_GullITLoadSum[OS_CORE_ID] = OS_ZERO;
  Os_GullCPULoadSum[OS_CORE_ID] = OS_ZERO;
  /* polyspace:end<MISRA-C3:D4.1> */
}
#endif /* if (OS_DEBUG_CPULOAD == STD_ON) */

#if (OS_DEBUG_STACKDEPTH == STD_ON)
/* polyspace-begin MISRA-C3:18.1 [Justified:Medium] "Checked array index is used" */
/***************************************************************************//**
 * Function Name        : Os_FillStackPattern
 *
 * Service ID           : NA
 *
 * Description          : This service is used to fill stack pattern
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : None Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStack
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(void, OS_CODE) Os_FillStackPattern(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType coreID = GetCoreID();
  #endif
  Os_StackType* pStackArea;
  uint16 LusStackSize;
  uint16 LusIdx;
  uint16 LusPos;

  #if (OS_MULTICORE == STD_ON)
  if(coreID == OS_CORE_ID_MASTER)
  #endif
  {
    for(LusIdx = OS_ZERO; LusIdx < OS_STACK_COUNT; LusIdx++)
    {
      pStackArea = Os_GaaStack[LusIdx].pStackArea;
      LusStackSize = Os_GaaStack[LusIdx].usStackSize;

      if((pStackArea != NULL_PTR) && (LusStackSize > OS_ONE))
      {
        #if (OS_STACK_MONITORING == STD_ON)
        /* pStackArea[OS_ZERO] is for 'AAAAAAAA' */
        for(LusPos = OS_ONE ; LusPos < LusStackSize; LusPos++)
        #else
        for(LusPos = OS_ZERO ; LusPos < LusStackSize; LusPos++)
        #endif
        {
          /* polyspace +2 RTE:IDP [Justified:Medium] "Valid position" */
          pStackArea[LusPos] = OS_STACK_EMPTY_PATTERN;
        }
      }
    }
  }
}

/***************************************************************************//**
 * Function Name        : Os_GetMaxStackUsage
 *
 * Service ID           : NA
 *
 * Description          : This service is used to get max stack usage of the
 *                        stack which is used by the target Task.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : None Re-entrant
 *
 * @param[out]            pStackUsage  Stack usage of the stack which is used by
 *                                     Task
 * @param[out]            pStackSize   Total stack size of the stack which is
 *                                     used by Task
 * @param[in]             LddTaskId    Task ID
 *
 * @return              : StatusType   E_OK          no error
 *                                     E_OS_STATE    error occurs during execution
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStaticTask, Os_GaaStack
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(StatusType, OS_CODE) Os_GetMaxStackUsage(TaskType LddTaskId, uint32* pStackUsage, uint32* pStackSize)
{
  StatusType LddStatusReturn;
  Os_StackType* pStackArea;
  uint32 LulStackUsage;
  uint32 LulStackEmpty;
  uint16 LusStackSize;
  uint16 LusIdx;
  uint16 LusPos;

  LulStackEmpty = 0u;
  LddStatusReturn = E_OS_STATE;
  if ((LddTaskId < (OS_TASK_COUNT + OS_CAT2_ISR_COUNT + OS_CORE_COUNT)) &&
      (pStackUsage != NULL_PTR) && (pStackSize != NULL_PTR))
  {
    /* 255 means invalid stack index */
    LusIdx = Os_GaaStaticTask[LddTaskId].ucStackIndex;
    if(LusIdx != 255)
    {
      pStackArea = Os_GaaStack[LusIdx].pStackArea;
      LusStackSize = Os_GaaStack[LusIdx].usStackSize;

      if((pStackArea != NULL_PTR) && (LusStackSize > OS_ONE))
      {
        #if (OS_STACK_MONITORING == STD_ON)
        /* pStackArea[OS_ZERO] is for 'AAAAAAAA' */
        for(LusPos = OS_ONE ; LusPos < LusStackSize; LusPos++)
        #else
        for(LusPos = OS_ZERO ; LusPos < LusStackSize; LusPos++)
        #endif
        {
          /* polyspace +3 RTE:NIV [Justified:Medium] "Valid index" */
          /* polyspace +2 RTE:IDP [Justified:Medium] "Valid position" */
          if(pStackArea[LusPos] != OS_STACK_EMPTY_PATTERN)
          {
            LulStackEmpty = LusPos;
            break;
          }
        }
        LulStackUsage = LusStackSize - LulStackEmpty;
		/* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justify with annotations> Already checked wheter it is NULL or not */
        *pStackUsage = LulStackUsage * sizeof(Os_StackType);
        *pStackSize = LusStackSize * sizeof(Os_StackType);
		/* polyspace:end<MISRA-C3:D4.14> */
        LddStatusReturn = E_OK;
      }
    }
  }
  return LddStatusReturn;
}
/* polyspace-end MISRA-C3:18.1 */
#endif /* #if (OS_DEBUG_STACKDEPTH == STD_ON) */

#define OS_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<RTE:ABS_ADDR> */
/* polyspace:end<RTE:OBAI> */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
