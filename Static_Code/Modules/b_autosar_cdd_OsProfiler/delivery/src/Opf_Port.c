/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Opf_Port.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : OS Profiler                                                   **
**                                                                            **
**  PURPOSE   : Implementation of TimeService module                          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.5.4     14-Dec-2021    YH.Han        Redmine #33412, #33448              **
** 1.5.1     17-Jun-2020    YH.Han        Redmine #24104                      **
** 1.5.0     31-Oct-2019    YH.Han        Redmine #18212                      **
** 1.4.0     23-May-2019    YH.Han        Redmine #17493, #17528              **
** 1.3.0     29-Oct-2018    YH.Han        Redmine #12853                      **
** 1.2.0     09-Mar-2018    YH.Han        Redmine #11169                      **
** 1.1.2     22-Aug-2017    MJ.Woo        Redmine #6959                       **
** 1.1.1     24-Mar-2017    JH.Lee        Redmine #6914                       **
** 1.1.0     16-Nov-2016    SH.Yoo        Redmine #6675, #6849, #6755         **
** 1.0.3     28-Oct-2016    SH.Yoo        Redmine #6253                       **
** 1.0.0     14-Jul-2016    SH.Yoo        Redmine #4024                       **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Opf_Port.h"
#include "Opf_Cfg.h"
#include "Opf_Ram.h"
#include "Opf_Task.h"
#include "Opf_ReceiveEvent.h"
#if (OPF_TARGET_OS == OPF_RENESAS_RH850)
#include "Opf_ControlEventQueue.h"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if (OPF_TARGET_OS == OPF_RENESAS_RH850)
extern const T_st_NotifyInfo SYM_AlarmNotifyInfoTableArray[];
extern T_st_SysCtrl			SYM_SysCtrlTable;
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
extern FUNC(OpfBool, OPF_CODE) Opf_IsNewTask(TaskType LucIdx);
extern FUNC(OpfBool, OPF_CODE) Opf_IsNoSuspendedTask(TaskType LucIdx);
#endif

#define OPF_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
 * Function             : OPF_MS_TO_TICKS
 *
 * Service ID           : NA
 *
 * Description          : Micro sec to ticks.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *                        - 0 ~ 0xFFFFFFFF : msec
 *
 * Parameter            : uint32
 *
 * @return              : uint32
 *                        - 0 ~ 0xFFFFFFFF : ticks
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-017
 ******************************************************************************/
FUNC(uint32, OPF_CODE) OPF_MS_TO_TICKS(uint32 MSEC)
{
  return (MSEC * Opf_GddOsProfiler.ddSTMClock);
}

/*******************************************************************************
 * Function             : OPF_ISVALID_TASK
 *
 * Service ID           : NA
 *
 * Description          : Micro sec to ticks.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *                        - 0 ~ 0xFF : task ID
 *
 * Parameter            : OpfTaskIDType
 *
 * @return              : boolean
 *                        - FALSE or TRUE : validation of Task ID
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-017
 ******************************************************************************/
FUNC(boolean, OPF_CODE) OPF_ISVALID_TASK(OpfTaskIDType TaskID)
{
  boolean LblIsTaskIdValid;

  /* polyspace<MISRA-C3:D4.14:Not a defect:Justify with annotations> pre-defined range */
  if ( (Opf_GaaTaskCache[TaskID].ddIsValid == OPF_TC_VALID) )
  {
    LblIsTaskIdValid = TRUE;
  }
  else
  {
    LblIsTaskIdValid = FALSE;
  }

  return LblIsTaskIdValid;
}

/*******************************************************************************
 * Function             : Opf_PortUpdateAlarmTask
 *
 * Service ID           : NA
 *
 * Description          : Micro sec to ticks.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : None
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-017
 ******************************************************************************/
#if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
FUNC(void, OPF_CODE) Opf_PortUpdateAlarmTask(TaskType TaskID)
{
  if(Opf_IsAlarmTask(TaskID) == OPF_TRUE)
  {
    Opf_GaaTaskCache[TaskID].ddIsAlarmTask = OPF_TRUE;
  }
}
#endif

/*******************************************************************************
 * Function             : Opf_PortGetObjID
 *
 * Service ID           : NA
 *
 * Description          : Get OsProfiler Task ID
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : uint16
 *                        - 0 ~ 0xFFFF : Task ID
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-017
 ******************************************************************************/
#if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
FUNC(OpfTaskIDType, OPF_CODE) Opf_PortGetObjID(uint16 ObjID)
{
  OpfTaskIDType LusObjId;

  LusObjId = (OpfTaskIDType) ObjID;

  return LusObjId;
}
#elif (OPF_TARGET_OS == OPF_RENESAS_RH850)
FUNC(OpfTaskIDType, OPF_CODE) Opf_PortGetObjID(uint16 ObjID)
{
  OpfTaskIDType LusObjId;

  LusObjId = (OpfTaskIDType) (ObjID - 1024);

  return LusObjId;
}
#elif (OPF_TARGET_OS == OPF_AUTRON_COMMON)
FUNC(OpfTaskIDType, OPF_CODE) Opf_PortGetObjID(uint16 ObjID)
{
  OpfTaskIDType LusObjId;

  LusObjId = (OpfTaskIDType) ObjID;

  return LusObjId;
}
#endif

#if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
/*******************************************************************************
 * Function             : Opf_PortGetSystemClock
 *
 * Service ID           : NA
 *
 * Description          : This function is used to get System clock value(MHz).
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : uint32
 *                        - 0 ~ 0xFFFFFFFF : System clock value(MHz)
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-017
 ******************************************************************************/
static FUNC(uint32, OS_CODE) Opf_PortGetSystemClock(void)
{
  uint32 LulSystemClock;
  uint32 LulSystemClockSource;

  LulSystemClock = OPF_BACKUP_CLOCK;
  LulSystemClockSource = OPF_MC_CGM_SC_SS.B.SELSTAT;

  switch (LulSystemClockSource)
  {
    case OPF_SYSCLK_IRCOSC:
      LulSystemClock = OPF_BACKUP_CLOCK;
      break;
    case OPF_SYSCLK_IRCOSC_DIV:
      LulSystemClock = OPF_BACKUP_CLOCK /
                                     (OPF_FIRC_CTL.B.FIRCDIV + (uint32)OPF_ONE);
      break;
    case OPF_SYSCLK_XOSC:
      LulSystemClock = Opf_Xosc_Clock;
      break;
    case OPF_SYSCLK_XOSC_DIV:
      LulSystemClock = Opf_Xosc_Clock /
                                     (OPF_FXOSC_CTL.B.OSCDIV + (uint32)OPF_ONE);
      break;
    case OPF_SYSCLK_PLL:
      if ((OPF_FMPLL_CR.B.IDF != OPF_PLLCLOCK_INHIBIT) &&
          ((OPF_FMPLL_CR.B.NDIV >= OPF_PLLCLOCK_DIV_MIN) &&
           (OPF_FMPLL_CR.B.NDIV <= OPF_PLLCLOCK_DIV_MAX)))
      {
        LulSystemClock = (Opf_Xosc_Clock * OPF_FMPLL_CR.B.NDIV)
                / ((OPF_FMPLL_CR.B.IDF + (uint32)OPF_ONE) *
                   ((uint32)OPF_ONE << (OPF_FMPLL_CR.B.ODF + (uint32)OPF_ONE)));
      }
      break;
    default:
      LulSystemClock = OPF_BACKUP_CLOCK;
      break;
  }

  return LulSystemClock;
}
#endif /* #if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB) */

#if (OPF_TARGET_OS == OPF_RENESAS_RH850)
/*******************************************************************************
 * Function             : Opf_PortGetPllPaVal
 *
 * Service ID           : NA
 *
 * Description          : This function is used to get a PA divider of PLL.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : uint8
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-017
 ******************************************************************************/
static FUNC(uint8, OS_CODE) Opf_PortGetPllPaVal(void)
{
  uint8 LucPllPA;

  LucPllPA = OPF_ZERO;

  if(OPF_PLLC.B.PA == OPF_TWO)
  {
    LucPllPA = OPF_PLLC_PA_4;
  }
  else if(OPF_PLLC.B.PA == OPF_THREE)
  {
    LucPllPA = OPF_PLLC_PA_6;
  }
  else if(OPF_PLLC.B.PA == OPF_FOUR)
  {
    LucPllPA = OPF_PLLC_PA_8;
  }
  else if(OPF_PLLC.B.PA == OPF_FIVE)
  {
    LucPllPA = OPF_PLLC_PA_16;
  }

  return LucPllPA;
}
#endif /* #if (OPF_TARGET_OS == OPF_RENESAS_RH850) */

#if (OPF_TARGET_OS == OPF_RENESAS_RH850)
/*******************************************************************************
 * Function             : Opf_PortGetDivCpuClock
 *
 * Service ID           : NA
 *
 * Description          : This function is used to get divided Cpu clock
 *                        value(MHz).
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : LulCpuClock   CPU Clock
 *
 * @return              : uint32
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-017
 ******************************************************************************/
static FUNC(uint32, OS_CODE) Opf_PortGetDivCpuClock(uint32 LulCpuClock)
{
  uint8 LucClockDivider;

  LucClockDivider = OPF_CKSC_CPUCLKD_ACT.B.CPUCLKDACT;

  switch (LucClockDivider)
  {
  case OPF_TWO:
    LulCpuClock = LulCpuClock / OPF_TWO;
    break;
  case OPF_THREE:
    LulCpuClock = LulCpuClock / OPF_FOUR;
    break;
  case OPF_FOUR:
    LulCpuClock = LulCpuClock / OPF_EIGHT;
    break;
  default:
    break;
  }

  return LulCpuClock;
}
#endif /* #if (OPF_TARGET_OS == OPF_RENESAS_RH850) */

#if (OPF_TARGET_OS == OPF_RENESAS_RH850)
/*******************************************************************************
 * Function             : Opf_PortGetCPUCLK2
 *
 * Service ID           : NA
 *
 * Description          : This function is used to get Cpu clock value(MHz).
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : uint32
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        Opf_PortGetDivCpuClock()
 *
 * @ingroup               OPF-SRS-FUN-017
 ******************************************************************************/
static FUNC(uint32, OS_CODE) Opf_PortGetCPUCLK2(void)
{
  uint32 LulCpuClock;
  uint32 LulCpuClockSource;
  uint8 LucPllN;
  uint8 LucPllM;
  uint8 LucPllPA;

  LulCpuClockSource = OPF_CKSC_CPUCLKS_ACT.B.CPUCLKSACT;
  LulCpuClock = OPF_ZERO;

  switch (LulCpuClockSource)
  {
  case OPF_CPUCLKS_MAINOSC:
    LulCpuClock = Opf_Xosc_Clock;
    break;
  case OPF_CPUCLKS_CPPLL:
    if ((OPF_PLLS.B.PLLCLKACT == OPF_PLL_ACTIVE) &&
           (OPF_PLLC.B.M <= OPF_PLLCLOCK_MDIV_MAX))
    {
      LucPllN = OPF_PLLC.B.N + OPF_ONE;
      LucPllM = OPF_PLLC.B.M + OPF_ONE;
      LucPllPA = Opf_PortGetPllPaVal();

      if(LucPllPA != OPF_ZERO)
      {
        LulCpuClock = (Opf_Xosc_Clock * LucPllN) / (LucPllM * LucPllPA);
      }
    }
    break;
  default:
	/* assume low speed internal clock is not used */
	LulCpuClock = OPF_INTOSC_CLOCK;
    break;
  }

  LulCpuClock = (Opf_PortGetDivCpuClock(LulCpuClock)/OPF_TWO);

  return LulCpuClock;
}
#endif /* #if (OPF_TARGET_OS == OPF_RENESAS_RH850) */

#if (OPF_TARGET_OS == OPF_RENESAS_RH850)
/*******************************************************************************
 * Function             : Opf_PortGetIPERI1
 *
 * Service ID           : NA
 *
 * Description          : This function is used to get C_ISO_PERI1 clock
 *                        value(MHz).
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        Opf_PortGetCPUCLK2()
 *
 *
 * @ingroup               OPF-SRS-FUN-017
 ******************************************************************************/
FUNC(uint32, OS_CODE) Opf_PortGetIPERI1(void)
{
  uint32 LulIPERI1Clock;
  uint32 LulIPERI1ClockSource;
  uint8 LucPllN;
  uint8 LucPllM;
  uint8 LucPllPA;

  LulIPERI1ClockSource = OPF_CKSC_IPERI1S_ACT.B.IPERI1SACT;
  LulIPERI1Clock = OPF_ZERO;

  if(LulIPERI1ClockSource == OPF_IPERI1SCLKS_PPLLCLK)
  {
    if ((OPF_PLLS.B.PLLCLKACT == OPF_PLL_ACTIVE) &&
         (OPF_PLLC.B.M <= OPF_PLLCLOCK_MDIV_MAX))
    {
      LucPllN = OPF_PLLC.B.N + OPF_ONE;
      LucPllM = OPF_PLLC.B.M + OPF_ONE;
      LucPllPA = Opf_PortGetPllPaVal();

      if(LucPllPA != OPF_ZERO)
      {
        LulIPERI1Clock = (Opf_Xosc_Clock * LucPllN) / (LucPllM * LucPllPA);
      }
    }
  }
  else if(LulIPERI1ClockSource == OPF_IPERI1SCLKS_CPUCLK2)
  {
    LulIPERI1Clock = Opf_PortGetCPUCLK2();
  }

  return LulIPERI1Clock;
}
#endif /* #if (OPF_TARGET_OS == OPF_RENESAS_RH850) */

/***************************************************************************//**
 * Function             : Opf_PortGetStmClock
 *
 * Service ID           : NA
 *
 * Description          : This function is used to get STM clock value(KHz).
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : STM clock value(MHz)
 *
 * @pre                 : Clock configuration should be complete.
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        Opf_PortGetSystemClock(), Opf_PortGetIPERI1()
 *
 * @ingroup               OPF-SRS-FUN-017
 ******************************************************************************/
FUNC(uint32, OS_CODE) Opf_PortGetStmClock(void)
{
  uint32 LulStmClock;
  #if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
  uint32 LulStmDiv;
  uint32 LulSystemClock;
  #endif

  #if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
  LulSystemClock = Opf_PortGetSystemClock();
  LulStmDiv = OPF_STM_CR.B.CPS + (uint32)OPF_ONE;

  LulStmClock = (LulSystemClock / LulStmDiv) * 1000;
  #elif (OPF_TARGET_OS == OPF_RENESAS_RH850)
  LulStmClock = (Opf_PortGetIPERI1() * 1000);
  #elif (OPF_TARGET_OS == OPF_AUTRON_COMMON)
  LulStmClock = Opf_Stm_Frequency;
  #endif

  return LulStmClock;
}

/***************************************************************************//**
 * Function             : Opf_PortGetTaskID
 *
 * Service ID           : NA
 *
 * Description          : This function gets currunt running Task ID
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : TaskType
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *
 *                        Function(s) invoked    :
 *                        GetTaskID()
 *
 * @ingroup               OPF-SRS-FUN-005
 ******************************************************************************/
FUNC(TaskType, OPF_CODE) Opf_PortGetTaskID(void)
{
  /* polyspace-begin MISRA-C3:D4.5 [Not a Defect] "variable is not in same name space" */
  TaskType LddTaskID;

  LddTaskID = OPF_ZERO;
  (void)GetTaskID(&LddTaskID);
  #if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
  LddTaskID = OS_GETOBJIND(LddTaskID);
  #endif

  return LddTaskID;
  /* polyspace-end MISRA-C3:D4.5 */
}

/***************************************************************************//**
 * Function             : Opf_PortGetTaskState
 *
 * Service ID           : NA
 *
 * Description          : This function gets currunt running Task's state
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            LddTaskID       Task ID
 *
 * @return              : OpfStateType
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        GetTaskState()
 *
 * @ingroup               OPF-SRS-FUN-005
 ******************************************************************************/
/* polyspace-begin MISRA-C3:D4.5 [Not a Defect] "variable is not in same name space" */
FUNC(OpfStateType, OPF_CODE) Opf_PortGetTaskState(OpfObjectIDType LddTaskID)
/* polyspace-end MISRA-C3:D4.5 */
{
  TaskStateType LddTaskState;
  OpfStateType LddOpfState;
  TaskType LddObjID;

  #if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
  LddObjID = ((OSObjectType)(((OSObjectType)(OBJECT_TASK))<<OSOBJSHIFT) |
    (OSObjectType)(LddTaskID));
  #elif (OPF_TARGET_OS == OPF_RENESAS_RH850)
  LddObjID = 1024 + (TaskType)LddTaskID;
  #else
  LddObjID = (TaskType)LddTaskID;
  #endif

  LddTaskState = SUSPENDED;
  (void)GetTaskState(LddObjID, &LddTaskState);

  /* polyspace:begin<MISRA-C3:10.3:Not a defect:Justify with annotations> right side is not effected to cast of other type  */
  if(LddTaskState == READY)
  {
	  LddOpfState = OPF_TASK_READY;
  }
  else if(LddTaskState == RUNNING)
  {
	  LddOpfState = OPF_TASK_RUNNING;
  }
  else if(LddTaskState == WAITING)
  {
	  LddOpfState = OPF_TASK_WAITING;
  }
  else
  {
	  LddOpfState = OPF_TASK_SUSPENDED;
  }
  /* polyspace:end<MISRA-C3:10.3:Not a defect:Justify with annotations> right side is not effected to cast of other type  */

  /* polyspace:begin<MISRA-C3:10.5:Not a defect:Justify with annotations> No data loss due to type casting */
  return LddOpfState;
  /* polyspace-end MISRA-C3:10.5 */
}

/***************************************************************************//**
 * Function             : Opf_PortProcessPreIsr
 *
 * Service ID           : NA
 *
 * Description          : Process PreIsr for system specific job
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GddOsProfiler
 *
 *                        Function(s) invoked    :
 *                        Opf_GetLastEvent(), Opf_PortGetTaskState(),
 *                        Opf_GetLastProfileEvent(), Opf_UpdateTaskInfo()
 *
 * @ingroup               OPF-SRS-FUN-006
 ******************************************************************************/
FUNC(void, OPF_CODE) Opf_PortProcessPreIsr(void)
{
  #if (OPF_TARGET_OS == OPF_RENESAS_RH850)
  Tdd_Opf_Event *pLastEventEntry;
  Tdd_Opf_Event *pLastProfileEventEntry;
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  Tdd_Opf_OsProfiler *pCoreOsProfiler;

  /* polyspace:begin<RTE: OBAI : Not a defect : Justify with annotations > configured array index */
  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  LddCoreID = GetCoreID();
  pCoreOsProfiler = OPF_GET_OS_PROFILER_INFO(LddCoreID);
  /* polyspace:end<RTE: OBAI : Not a defect : Justify with annotations > configured array index */
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  #endif

  /* Update the last event's state */
  pLastEventEntry = Opf_GetLastEvent();
  if((pLastEventEntry->ddObject == OPF_OBJECT_TASK)
                              &&(pLastEventEntry->ddState == OPF_TASK_DELAYED))
  {
    pLastEventEntry->ddState = Opf_PortGetTaskState\
                                                  (pLastEventEntry->ddObjectID);

    #if (OPF_MULTICORE_ENABLED == STD_ON)
    if(pCoreOsProfiler->ddRecMode == OPF_RECMODE_PROFILE)
    #else
    if(Opf_GddOsProfiler.ddRecMode == OPF_RECMODE_PROFILE)
    #endif
    {
      /* Update the last event's state */
      pLastProfileEventEntry = Opf_GetLastProfileEvent();
      pLastProfileEventEntry->ddState = pLastEventEntry->ddState;
    }

    /* Verify task is eligible for profiling */
    Opf_ValidateTask(pLastEventEntry->ddObjectID);

    /* If valid task, update the task's information */
    if((OPF_ISVALID_TASK(pLastEventEntry->ddObjectID)) == TRUE)
    {
      Opf_UpdateTaskInfo(pLastEventEntry);
    }
  }
  #endif
}

 /*******************************************************************************
 * Function             : Opf_PortProcessPreCntIsr
 *
 * Service ID           : NA
 *
 * Description          : Process system specific job before counter ISR
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *
 *
 *                        Function(s) invoked    :
 *
 *
 * @ingroup               OPF-SRS-FUN-001, OPF-SRS-FUN-005, OPF-SRS-FUN-009
 ******************************************************************************/
FUNC(void, OPF_CODE) Opf_PortProcessPreCntIsr(void)
{
  /* Do nothing */
}

/***************************************************************************//**
 * Function             : Opf_PortProcessPostIsr
 *
 * Service ID           : NA
 *
 * Description          : Process PostIsr for system specific job
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        OsIsrArray, OsTaskTable
 *
 *                        Function(s) invoked    :
 *                        Opf_PortProcessPostCntIsr()
 *
 * @ingroup               OPF-SRS-FUN-006
 ******************************************************************************/
FUNC(void, OPF_CODE) Opf_PortProcessPostIsr(void)
{
  #if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
  OSISRTYPE LddIsrType;
  #endif

  #if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
  LddIsrType = OsIsrArray[OSISRLEVELMASKED - 1U]->type;

  /* If Counter isr */
  if(LddIsrType == OSSYSINTERRUPT)
  {
    Opf_PortProcessPostCntIsr();
  }
  #endif
}

/*******************************************************************************
 * Function             : Opf_PortProcessPostCntIsr
 *
 * Service ID           : NA
 *
 * Description          : Process system specific job after counter ISR
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        SYM_AlarmCtrlTableArray, SYM_CounterCtrlTableArray,
 *                        SYM_AlarmNotifyInfoTableArray
 *
 *                        Function(s) invoked    :
 *                        Opf_IsNewTask(), Opf_SetActivateTaskEvent(),
 *                        Opf_GetTimeSpan(), Opf_GetSavedSystimeSpan()
 *
 *
 * @ingroup               OPF-SRS-FUN-006
 ******************************************************************************/
FUNC(void, OPF_CODE) Opf_PortProcessPostCntIsr(void)
{
  #if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
  uint8 LucIdx;
  #elif (OPF_TARGET_OS == OPF_RENESAS_RH850)
  uint8 LucIdx;
  uint8 LucAlarmCnt;
  #endif
  #if ((OPF_TARGET_OS == OPF_FREESCALE_MPC560XB) ||\
       (OPF_TARGET_OS == OPF_RENESAS_RH850))
  OpfTimeSpanType LddTimeSpan;
  OpfBool LddIsFirstActTask = OPF_TRUE;
  #endif

  #if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
  for(LucIdx = OPF_ZERO; LucIdx < Opf_OSNTSKS; LucIdx++)
  {
    if(Opf_IsNewTask(LucIdx) == OPF_TRUE)
    {
      if((Opf_Profile_Isr == STD_OFF) && (LddIsFirstActTask == OPF_TRUE))
      {
        LddTimeSpan = Opf_GetSavedSystimeSpan();
        LddIsFirstActTask = OPF_FALSE;
      }
      else
      {
        LddTimeSpan = OPF_ZERO;
      }

      Opf_SetActivateTaskEvent(LucIdx, LddTimeSpan);
    }
  }
  #elif (OPF_TARGET_OS == OPF_RENESAS_RH850)
  LucAlarmCnt = SYM_SysInfoTable.cs2_MaxAlarmID;

  for(LucIdx = OPF_ZERO; LucIdx < LucAlarmCnt; LucIdx++)
  {
    if(SYM_AlarmCtrlTableArray[LucIdx].bu4_RegCountValue == \
                                  SYM_CounterCtrlTableArray[OPF_ZERO].bu4_Value)
    {
      if((Opf_Profile_Isr == STD_OFF) && (LddIsFirstActTask == OPF_TRUE))
      {
        LddTimeSpan = Opf_GetSavedSystimeSpan();
        LddIsFirstActTask = OPF_FALSE;
      }
      else
      {
        LddTimeSpan = OPF_ZERO;
      }

      Opf_SetActivateTaskEvent\
              (SYM_AlarmNotifyInfoTableArray[LucIdx].cs2_ObjectID, LddTimeSpan);
    }
  }
  #endif
}

/***************************************************************************//**
 * Function             : Opf_PortProcessLimitError
 *
 * Service ID           : NA
 *
 * Description          : This function sets Limit error Task event
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        OsCounters, OsTaskTable, OsTimVal,
 *                        SYM_AlarmCtrlTableArray, SYM_CounterCtrlTableArray,
 *                        SYM_AlarmNotifyInfoTableArray
 *
 *                        Function(s) invoked    :
 *                        Opf_SetLimitTaskEvent(), Opf_IsNoSuspendedTask()
 *
 * @ingroup               OPF-SRS-FUN-005
 ******************************************************************************/
FUNC(void, OPF_CODE) Opf_PortProcessLimitError(void)
{
  /* polyspace-begin MISRA-C3:D4.5 [Not a Defect] "variable is not in same name space" */
  #if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
  OSAlmType LucAlarmID;
  OSWORD LusTaskID;
  OpfBool LddIsLimit = OPF_FALSE;
  OSALMCB *LddAlarmCB;
  #elif (OPF_TARGET_OS == OPF_RENESAS_RH850)
  uint8 LucAlarmIdx;
  uint8 LucAlarmCnt;
  TaskType LddTaskID;
  OpfBool LddIsLimit = OPF_FALSE;
  TaskStateType LddTaskState;
  #elif (OPF_TARGET_OS == OPF_AUTRON_COMMON)
  TaskType LddTaskID;
  #endif

  #if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
  LucAlarmID = OsCounters[OSTIMER1].alarm;
  LddAlarmCB = (OSALMCB*)LucAlarmID;

  while ((LddAlarmCB != (OSALMCB*)OSALMCBPTR0) && (LddIsLimit == OPF_FALSE))
  {
    #if defined(OSHWCOUNTER)
    if(OsTimVal == LddAlarmCB->value)
    #else
    /* polyspace-begin RTE:IDP [Not a Defect] 
                                      "only access to a pre-defined pointer " */
    /* polyspace-begin RTE:NIV [Not a Defect] 
                                        "only access to a pre-defined value " */
    if(OsCounters[OSTIMER1].value == LddAlarmCB->value)
    /* polyspace-end RTE:IDP */
    /* polyspace-end RTE:NIV */
    #endif
    {
      /* polyspace-begin RTE:NIV [Not a Defect] 
                                        "only access to a pre-defined value " */
      LusTaskID = LddAlarmCB->action.taskIndex;
      /* polyspace-end RTE:NIV */

      if(Opf_IsNoSuspendedTask(LusTaskID))
      {
        Opf_SetLimitTaskEvent((OpfTaskIDType)LusTaskID);
        LddIsLimit = OPF_TRUE;
      }
    }
    /* polyspace-begin RTE:NIP [Not a Defect] 
                                      "only access to a pre-defined pointer " */
    LddAlarmCB = (OSALMCB*)(LddAlarmCB->next);
    /* polyspace-end RTE:NIP */
  }
  #elif (OPF_TARGET_OS == OPF_RENESAS_RH850)
  LucAlarmCnt = SYM_SysInfoTable.cs2_MaxAlarmID;

  for(LucAlarmIdx = OPF_ZERO; (LucAlarmIdx < LucAlarmCnt) && \
                                       (LddIsLimit == OPF_FALSE); LucAlarmIdx++)
  {
    if(SYM_AlarmCtrlTableArray[LucAlarmIdx].bu4_RegCountValue == \
                                  SYM_CounterCtrlTableArray[OPF_ZERO].bu4_Value)
    {
      LddTaskID = \
             (TaskType) SYM_AlarmNotifyInfoTableArray[LucAlarmIdx].cs2_ObjectID;

      GetTaskState(1024 + (TaskType)LddTaskID, &LddTaskState);

      if(LddTaskState != SUSPENDED)
      {
        Opf_SetLimitTaskEvent((OpfTaskIDType)LddTaskID);
        LddIsLimit = OPF_TRUE;
      }
    }
  }
  #elif (OPF_TARGET_OS == OPF_AUTRON_COMMON)
  LddTaskID = OSError_ActivateTask_TaskID();
  Opf_SetLimitTaskEvent((OpfTaskIDType)LddTaskID);
  #endif
  /* polyspace-end MISRA-C3:D4.5 */
}

/***************************************************************************//**
 * Function             : Opf_PortProcessPreTask
 *
 * Service ID           : NA
 *
 * Description          : Process PreTask for system specific job
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-005
 ******************************************************************************/
FUNC(void, OPF_CODE) Opf_PortProcessPreTask(void)
{
  /* Do nothing */
}

/***************************************************************************//**
 * Function             : Opf_PortProcessPostTask
 *
 * Service ID           : NA
 *
 * Description          : Process PostTask for system specific job
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-005
 ******************************************************************************/
FUNC(void, OPF_CODE) Opf_PortProcessPostTask(void)
{
  /* Do nothing */
}

#define OPF_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
