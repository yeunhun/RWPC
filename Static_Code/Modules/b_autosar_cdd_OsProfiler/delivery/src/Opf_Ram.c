/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Opf_Ram.c                                                     **
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
**                      Include Section                                       **
*******************************************************************************/
#include "Opf_Ram.h"
#include "Opf_Cfg.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define OPF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

VAR(Tdd_Opf_GaaTaskCache, OS_VAR) Opf_GaaTaskCache[OPF_MAX_TASK_ID];
VAR(Tdd_Opf_TaskInfo, OS_VAR) Opf_GaaTaskInfo[OPF_PROFILE_TASK_COUNT];
VAR(Tdd_Opf_EventQ, OS_VAR) Opf_GddEventQ;
VAR(Tdd_Opf_ProfileEventQ, OS_VAR) Opf_GddProfileEventQ;
VAR(Tdd_Opf_OsProfiler, OS_VAR) Opf_GddOsProfiler;

#define OPF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define OPF_START_SEC_VAR_CLEARED_32
#include "MemMap.h"

VAR(uint32, OS_VAR) Opf_GulIndexTicks;
VAR(OpfSystimeTickType, OS_VAR) Opf_GddSystimeTick;
VAR(OpfTimeSpanType, OS_VAR) Opf_GddSystimeSpan;

#define OPF_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#if (OPF_MULTICORE_ENABLED == STD_ON)
#if (OPF_CORE_COUNT >= 2)
#define OPF_START_CORE1_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

VAR(Tdd_Opf_EventQ, OS_VAR) Opf_GddEventQCore1;
VAR(Tdd_Opf_ProfileEventQ, OS_VAR) Opf_GddProfileEventQCore1;
VAR(Tdd_Opf_OsProfiler, OS_VAR) Opf_GddOsProfilerCore1;

#define OPF_STOP_CORE1_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define OPF_START_CORE1_SEC_VAR_CLEARED_32
#include "MemMap.h"

VAR(uint32, OS_VAR) Opf_GulIndexTicksCore1;
VAR(OpfSystimeTickType, OS_VAR) Opf_GddSystimeTickCore1;
VAR(OpfTimeSpanType, OS_VAR) Opf_GddSystimeSpanCore1;

#define OPF_STOP_CORE1_SEC_VAR_CLEARED_32
#include "MemMap.h"
#endif

#if (OPF_CORE_COUNT >= 3)
#define OPF_START_CORE2_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

VAR(Tdd_Opf_EventQ, OS_VAR) Opf_GddEventQCore2;
VAR(Tdd_Opf_ProfileEventQ, OS_VAR) Opf_GddProfileEventQCore2;
VAR(Tdd_Opf_OsProfiler, OS_VAR) Opf_GddOsProfilerCore2;

#define OPF_STOP_CORE2_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define OPF_START_CORE2_SEC_VAR_CLEARED_32
#include "MemMap.h"

VAR(uint32, OS_VAR) Opf_GulIndexTicksCore2;
VAR(OpfSystimeTickType, OS_VAR) Opf_GddSystimeTickCore2;
VAR(OpfTimeSpanType, OS_VAR) Opf_GddSystimeSpanCore2;

#define OPF_STOP_CORE2_SEC_VAR_CLEARED_32
#include "MemMap.h"
#endif

#if (OPF_CORE_COUNT >= 4)
#define OPF_START_CORE3_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

VAR(Tdd_Opf_EventQ, OS_VAR) Opf_GddEventQCore3;
VAR(Tdd_Opf_ProfileEventQ, OS_VAR) Opf_GddProfileEventQCore3;
VAR(Tdd_Opf_OsProfiler, OS_VAR) Opf_GddOsProfilerCore3;

#define OPF_STOP_CORE3_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define OPF_START_CORE3_SEC_VAR_CLEARED_32
#include "MemMap.h"

VAR(uint32, OS_VAR) Opf_GulIndexTicksCore3;
VAR(OpfSystimeTickType, OS_VAR) Opf_GddSystimeTickCore3;
VAR(OpfTimeSpanType, OS_VAR) Opf_GddSystimeSpanCore3;

#define OPF_STOP_CORE3_SEC_VAR_CLEARED_32
#include "MemMap.h"
#endif

#if (OPF_CORE_COUNT >= 5)
#define OPF_START_CORE4_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

VAR(Tdd_Opf_EventQ, OS_VAR) Opf_GddEventQCore4;
VAR(Tdd_Opf_ProfileEventQ, OS_VAR) Opf_GddProfileEventQCore4;
VAR(Tdd_Opf_OsProfiler, OS_VAR) Opf_GddOsProfilerCore4;

#define OPF_STOP_CORE4_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define OPF_START_CORE4_SEC_VAR_CLEARED_32
#include "MemMap.h"

VAR(uint32, OS_VAR) Opf_GulIndexTicksCore4;
VAR(OpfSystimeTickType, OS_VAR) Opf_GddSystimeTickCore4;
VAR(OpfTimeSpanType, OS_VAR) Opf_GddSystimeSpanCore4;

#define OPF_STOP_CORE4_SEC_VAR_CLEARED_32
#include "MemMap.h"
#endif

#if (OPF_CORE_COUNT >= 6)
#define OPF_START_CORE5_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

VAR(Tdd_Opf_EventQ, OS_VAR) Opf_GddEventQCore5;
VAR(Tdd_Opf_ProfileEventQ, OS_VAR) Opf_GddProfileEventQCore5;
VAR(Tdd_Opf_OsProfiler, OS_VAR) Opf_GddOsProfilerCore5;

#define OPF_STOP_CORE5_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define OPF_START_CORE5_SEC_VAR_CLEARED_32
#include "MemMap.h"

VAR(uint32, OS_VAR) Opf_GulIndexTicksCore5;
VAR(OpfSystimeTickType, OS_VAR) Opf_GddSystimeTickCore5;
VAR(OpfTimeSpanType, OS_VAR) Opf_GddSystimeSpanCore5;

#define OPF_STOP_CORE5_SEC_VAR_CLEARED_32
#include "MemMap.h"
#endif
#endif

#define OPF_START_SEC_VAR_CLEARED_32
#include "MemMap.h"

#if (OPF_MULTICORE_ENABLED == STD_ON)
P2VAR(Tdd_Opf_EventQ, AUTOMATIC, OS_VAR) Opf_GddEventQInfo[OPF_CORE_COUNT] = 
{
  &Opf_GddEventQ, 
#if (OPF_CORE_COUNT >= 2)
  &Opf_GddEventQCore1, 
#endif
#if (OPF_CORE_COUNT >= 3)
  &Opf_GddEventQCore2, 
#endif
#if (OPF_CORE_COUNT >= 4)
  &Opf_GddEventQCore3, 
#endif
#if (OPF_CORE_COUNT >= 5)
  &Opf_GddEventQCore4, 
#endif
#if (OPF_CORE_COUNT >= 6)
  &Opf_GddEventQCore5, 
#endif
};

P2VAR(Tdd_Opf_ProfileEventQ, AUTOMATIC, OS_VAR) 
                                       Opf_GddProfileEventQInfo[OPF_CORE_COUNT] = 
{
  &Opf_GddProfileEventQ, 
#if (OPF_CORE_COUNT >= 2)
  &Opf_GddProfileEventQCore1, 
#endif
#if (OPF_CORE_COUNT >= 3)
  &Opf_GddProfileEventQCore2, 
#endif
#if (OPF_CORE_COUNT >= 4)
  &Opf_GddProfileEventQCore3, 
#endif
#if (OPF_CORE_COUNT >= 5)
  &Opf_GddProfileEventQCore4, 
#endif
#if (OPF_CORE_COUNT >= 6)
  &Opf_GddProfileEventQCore5, 
#endif
};

P2VAR(Tdd_Opf_OsProfiler, AUTOMATIC, OS_VAR) 
                                          Opf_GddOsProfilerInfo[OPF_CORE_COUNT] = 
{
  &Opf_GddOsProfiler, 
#if (OPF_CORE_COUNT >= 2)
  &Opf_GddOsProfilerCore1, 
#endif
#if (OPF_CORE_COUNT >= 3)
  &Opf_GddOsProfilerCore2, 
#endif
#if (OPF_CORE_COUNT >= 4)
  &Opf_GddOsProfilerCore3, 
#endif
#if (OPF_CORE_COUNT >= 5)
  &Opf_GddOsProfilerCore4, 
#endif
#if (OPF_CORE_COUNT >= 6)
  &Opf_GddOsProfilerCore5, 
#endif
};

P2VAR(uint32, AUTOMATIC, OS_VAR) Opf_GulIndexTicksInfo[OPF_CORE_COUNT] = 
{
  &Opf_GulIndexTicks, 
#if (OPF_CORE_COUNT >= 2)
  &Opf_GulIndexTicksCore1, 
#endif
#if (OPF_CORE_COUNT >= 3)
  &Opf_GulIndexTicksCore2, 
#endif
#if (OPF_CORE_COUNT >= 4)
  &Opf_GulIndexTicksCore3, 
#endif
#if (OPF_CORE_COUNT >= 5)
  &Opf_GulIndexTicksCore4, 
#endif
#if (OPF_CORE_COUNT >= 6)
  &Opf_GulIndexTicksCore5, 
#endif
};

P2VAR(OpfSystimeTickType, AUTOMATIC, OS_VAR) 
                                         Opf_GddSystimeTickInfo[OPF_CORE_COUNT] = 
{
  &Opf_GddSystimeTick, 
#if (OPF_CORE_COUNT >= 2)
  &Opf_GddSystimeTickCore1, 
#endif
#if (OPF_CORE_COUNT >= 3)
  &Opf_GddSystimeTickCore2, 
#endif
#if (OPF_CORE_COUNT >= 4)
  &Opf_GddSystimeTickCore3, 
#endif
#if (OPF_CORE_COUNT >= 5)
  &Opf_GddSystimeTickCore4, 
#endif
#if (OPF_CORE_COUNT >= 6)
  &Opf_GddSystimeTickCore5, 
#endif
};

P2VAR(OpfTimeSpanType, AUTOMATIC, OS_VAR) Opf_GddSystimeSpanInfo[OPF_CORE_COUNT] = 
{
  &Opf_GddSystimeSpan, 
#if (OPF_CORE_COUNT >= 2)
  &Opf_GddSystimeSpanCore1, 
#endif
#if (OPF_CORE_COUNT >= 3)
  &Opf_GddSystimeSpanCore2, 
#endif
#if (OPF_CORE_COUNT >= 4)
  &Opf_GddSystimeSpanCore3, 
#endif
#if (OPF_CORE_COUNT >= 5)
  &Opf_GddSystimeSpanCore4, 
#endif
#if (OPF_CORE_COUNT >= 6)
  &Opf_GddSystimeSpanCore5, 
#endif
};
#endif

#define OPF_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define OPF_START_SEC_CONST_8
#include "MemMap.h"

#if (OPF_PROFILE_ISR == STD_ON)
CONST(uint8, OS_CONST) Opf_Profile_Isr = STD_ON;
#else
CONST(uint8, OS_CONST) Opf_Profile_Isr = STD_OFF;
#endif
#if (OPF_PROFILE_TIME_INDEX == STD_ON)
CONST(uint8, OS_CONST) Opf_Profile_Time_Index = STD_ON;
#else
CONST(uint8, OS_CONST) Opf_Profile_Time_Index = STD_OFF;
#endif
CONST(uint8, OS_CONST) Opf_Max_Task_Id = OPF_MAX_TASK_ID;
#if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
CONST(uint8, OS_CONST) Opf_Xosc_Clock = OPF_XOSC_CLOCK;
CONST(uint8, OS_CONST) Opf_OSNTSKS = OSNTSKS;
#elif (OPF_TARGET_OS == OPF_RENESAS_RH850)
CONST(uint8, OS_CONST) Opf_Xosc_Clock = OPF_XOSC_CLOCK;
#endif
#if (OPF_TARGET_OS == OPF_AUTRON_COMMON) 
P2CONST(uint32, AUTOMATIC, OS_CONST) Opf_Stm_Address = OPF_STM_TICK;
CONST(uint32, OS_CONST) Opf_Max_Stm_Tick_Value = OPF_MAX_STM_TICK;
CONST(uint32, OS_CONST) Opf_Stm_Frequency = OPF_STM_CLOCK;
#endif

#define OPF_STOP_SEC_CONST_8
#include "MemMap.h"

#define OPF_START_SEC_CONST_32
#include "MemMap.h"

CONST(OpfEventQueueSizeType, OS_CONST) Opf_Event_Queue_Length =
                                                         OPF_EVENT_QUEUE_LENGTH;
CONST(uint32, OS_CONST) Opf_Profile_Task_Count = OPF_PROFILE_TASK_COUNT;

#if (OPF_PROFILE_TIME_INDEX == STD_ON)
CONST(uint32, OS_CONST) Opf_Time_Index_Msec = OPF_TIME_INDEX_MSEC;
#else
CONST(uint32, OS_CONST) Opf_Time_Index_Msec = OPF_ZERO;
#endif

CONST(uint32, OS_CONST) Sizeof_Tdd_Opf_Event = sizeof(Tdd_Opf_Event);
CONST(uint32, OS_CONST) Sizeof_Tdd_Opf_EventQ = sizeof(Tdd_Opf_EventQ);
CONST(uint32, OS_CONST) Sizeof_Tdd_Opf_ProfileEventQ =
                                                  sizeof(Tdd_Opf_ProfileEventQ);
CONST(uint32, OS_CONST) Sizeof_Tdd_Opf_GaaTaskCache =
                                                   sizeof(Tdd_Opf_GaaTaskCache);
CONST(uint32, OS_CONST) Sizeof_Tdd_Opf_TaskInfo = sizeof(Tdd_Opf_TaskInfo);

#define OPF_STOP_SEC_CONST_32
#include "MemMap.h"
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
