/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Opf_Ram.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : OS Profiler                                                   **
**                                                                            **
**  PURPOSE   : Ram Data for OS Profiler                                      **
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
** 1.5.4     14-Dec-2021    YH.Han        Redmine #33448                      **
** 1.5.1     17-Jun-2020    YH.Han        Redmine #24104                      **
** 1.5.0     31-Oct-2019    YH.Han        Redmine #19291, #20113              **
** 1.3.0     29-Oct-2018    YH.Han        Redmine #12853                      **
** 1.1.2     22-Aug-2017    MJ.Woo        Redmine #6959                       **
** 1.1.0     24-Nov-2016    SH.Yoo        Redmine #6849, #6755                **
** 1.0.0     14-Jul-2016    SH.Yoo        Redmine #4024                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C:8.12:Not a defect:Justify with annotations> External linkage with array size makes error because of compiler optimization  */

#ifndef OPF_RAM_H
#define OPF_RAM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Opf_Types.h"
#include "Opf_Cfg.h"
#if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
#include "Os_prop.h"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
extern VAR(Tdd_Opf_GaaTaskCache, OS_VAR) Opf_GaaTaskCache[];
extern VAR(Tdd_Opf_TaskInfo, OS_VAR) Opf_GaaTaskInfo[];

extern VAR(Tdd_Opf_EventQ, OS_VAR) Opf_GddEventQ;
extern VAR(Tdd_Opf_ProfileEventQ, OS_VAR) Opf_GddProfileEventQ;
extern VAR(Tdd_Opf_OsProfiler, OS_VAR) Opf_GddOsProfiler;
extern VAR(uint32, OS_VAR) Opf_GulIndexTicks;
extern VAR(OpfSystimeTickType, OS_VAR) Opf_GddSystimeTick;
extern VAR(OpfTimeSpanType, OS_VAR) Opf_GddSystimeSpan;

#if (OPF_MULTICORE_ENABLED == STD_ON)
#if (OPF_CORE_COUNT >= 2)
extern VAR(Tdd_Opf_EventQ, OS_VAR) Opf_GddEventQCore1;
extern VAR(Tdd_Opf_ProfileEventQ, OS_VAR) Opf_GddProfileEventQCore1;
extern VAR(Tdd_Opf_OsProfiler, OS_VAR) Opf_GddOsProfilerCore1;
extern VAR(uint32, OS_VAR) Opf_GulIndexTicksCore1;
extern VAR(OpfSystimeTickType, OS_VAR) Opf_GddSystimeTickCore1;
extern VAR(OpfTimeSpanType, OS_VAR) Opf_GddSystimeSpanCore1;
#endif

#if (OPF_CORE_COUNT >= 3)
extern VAR(Tdd_Opf_EventQ, OS_VAR) Opf_GddEventQCore2;
extern VAR(Tdd_Opf_ProfileEventQ, OS_VAR) Opf_GddProfileEventQCore2;
extern VAR(Tdd_Opf_OsProfiler, OS_VAR) Opf_GddOsProfilerCore2;
extern VAR(uint32, OS_VAR) Opf_GulIndexTicksCore2;
extern VAR(OpfSystimeTickType, OS_VAR) Opf_GddSystimeTickCore2;
extern VAR(OpfTimeSpanType, OS_VAR) Opf_GddSystimeSpanCore2;
#endif

#if (OPF_CORE_COUNT >= 4)
extern VAR(Tdd_Opf_EventQ, OS_VAR) Opf_GddEventQCore3;
extern VAR(Tdd_Opf_ProfileEventQ, OS_VAR) Opf_GddProfileEventQCore3;
extern VAR(Tdd_Opf_OsProfiler, OS_VAR) Opf_GddOsProfilerCore3;
extern VAR(uint32, OS_VAR) Opf_GulIndexTicksCore3;
extern VAR(OpfSystimeTickType, OS_VAR) Opf_GddSystimeTickCore3;
extern VAR(OpfTimeSpanType, OS_VAR) Opf_GddSystimeSpanCore3;
#endif

#if (OPF_CORE_COUNT >= 5)
extern VAR(Tdd_Opf_EventQ, OS_VAR) Opf_GddEventQCore4;
extern VAR(Tdd_Opf_ProfileEventQ, OS_VAR) Opf_GddProfileEventQCore4;
extern VAR(Tdd_Opf_OsProfiler, OS_VAR) Opf_GddOsProfilerCore4;
extern VAR(uint32, OS_VAR) Opf_GulIndexTicksCore4;
extern VAR(OpfSystimeTickType, OS_VAR) Opf_GddSystimeTickCore4;
extern VAR(OpfTimeSpanType, OS_VAR) Opf_GddSystimeSpanCore4;
#endif

#if (OPF_CORE_COUNT >= 6)
extern VAR(Tdd_Opf_EventQ, OS_VAR) Opf_GddEventQCore5;
extern VAR(Tdd_Opf_ProfileEventQ, OS_VAR) Opf_GddProfileEventQCore5;
extern VAR(Tdd_Opf_OsProfiler, OS_VAR) Opf_GddOsProfilerCore5;
extern VAR(uint32, OS_VAR) Opf_GulIndexTicksCore5;
extern VAR(OpfSystimeTickType, OS_VAR) Opf_GddSystimeTickCore5;
extern VAR(OpfTimeSpanType, OS_VAR) Opf_GddSystimeSpanCore5;
#endif

extern P2VAR(Tdd_Opf_EventQ, AUTOMATIC, OS_VAR) Opf_GddEventQInfo[];
extern P2VAR(Tdd_Opf_ProfileEventQ, AUTOMATIC, OS_VAR) 
                                                     Opf_GddProfileEventQInfo[];
extern P2VAR(Tdd_Opf_OsProfiler, AUTOMATIC, OS_VAR) Opf_GddOsProfilerInfo[];
extern P2VAR(uint32, AUTOMATIC, OS_VAR) Opf_GulIndexTicksInfo[];
extern P2VAR(OpfSystimeTickType, AUTOMATIC, OS_VAR) Opf_GddSystimeTickInfo[];
extern P2VAR(OpfTimeSpanType, AUTOMATIC, OS_VAR) Opf_GddSystimeSpanInfo[];
#endif

extern CONST(uint8, OS_CONST) Opf_Profile_Isr;
extern CONST(uint8, OS_CONST) Opf_Profile_Time_Index;
extern CONST(uint8, OS_CONST) Opf_Max_Task_Id;
#if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
extern CONST(uint8, OS_CONST) Opf_Xosc_Clock;
extern CONST(uint8, OS_CONST) Opf_OSNTSKS;
#elif (OPF_TARGET_OS == OPF_RENESAS_RH850)
extern CONST(uint8, OS_CONST) Opf_Xosc_Clock;
#endif
#if (OPF_TARGET_OS == OPF_AUTRON_COMMON)
extern P2CONST(uint32, AUTOMATIC, OS_CONST) Opf_Stm_Address;
extern CONST(uint32, OS_CONST) Opf_Max_Stm_Tick_Value;
extern CONST(uint32, OS_CONST) Opf_Stm_Frequency;
#endif

extern CONST(OpfEventQueueSizeType, OS_CONST) Opf_Event_Queue_Length;
extern CONST(uint32, OS_CONST) Opf_Profile_Task_Count;
extern CONST(uint32, OS_CONST) Opf_Time_Index_Msec;

extern CONST(uint32, OS_CONST) Sizeof_Tdd_Opf_Event;
extern CONST(uint32, OS_CONST) Sizeof_Tdd_Opf_EventQ;
extern CONST(uint32, OS_CONST) Sizeof_Tdd_Opf_ProfileEventQ;
extern CONST(uint32, OS_CONST) Sizeof_Tdd_Opf_GaaTaskCache;
extern CONST(uint32, OS_CONST) Sizeof_Tdd_Opf_TaskInfo;

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* OPF_RAM_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<MISRA-C:8.12:Not a defect:Justify with annotations> External linkage with array size makes error because of compiler optimization  */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
