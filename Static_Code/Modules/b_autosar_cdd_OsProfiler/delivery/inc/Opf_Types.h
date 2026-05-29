/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Opf_Types.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : OS Profiler                                                   **
**                                                                            **
**  PURPOSE   : Type definetion for OS Profiler                               **
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
** 1.5.4     14-Dec-2021    YH.Han        Redmine #33448, #33412              **
** 1.5.1     17-Jun-2020    YH.Han        Redmine #24104                      **
** 1.3.0     29-Oct-2018    YH.Han        Redmine #12853                      **
** 1.1.2     22-Aug-2017    MJ.Woo        Redmine #6959                       **
** 1.1.0     24-Nov-2016    SH.Yoo        Redmine #6755, #6756                **
** 1.0.0     14-Jul-2016    SH.Yoo        Redmine #4024                       **
*******************************************************************************/

#ifndef OPF_TYPES_H
#define OPF_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/* Definition of zero */
#define OPF_ZERO               0

/* Definition of one */
#define OPF_ONE                1

/* Definition of two */
#define OPF_TWO                2

/* Definition of three */
#define OPF_THREE              3

/* Definition of four */
#define OPF_FOUR               4

/* Definition of five */
#define OPF_FIVE               5

/* Definition of six */
#define OPF_SIX                6

/* Definition of seven */
#define OPF_SEVEN              7

/* Definition of eight */
#define OPF_EIGHT              8

/* Definition of nine */
#define OPF_NINE               9

/* Definition of ten */
#define OPF_TEN                10

/* Definition of thousand */
#define OPF_FULL_PERMILLAGE    1000u

/* Definition of NULL */
#define OPF_NULL               NULL_PTR

/**
  * @typedef OpfTimeStampType
  *
  * Data type for a TimeSpan.
  *
  */
typedef uint32 OpfTimeSpanType;

/**
  * @typedef OpfEventQueuePosType
  *
  * Data type for a position of current event in an event queue.
  *
  */
typedef uint16 OpfEventQueuePosType;

/**
  * @typedef OpfEventCountType
  *
  * Data type for Count of event.
  *
  */
typedef uint32 OpfEventCountType;

/**
  * @typedef OpfEventQueueSizeType
  *
  * Data type for size of event queue.
  *
  */
typedef uint16 OpfEventQueueSizeType;

/**
  * @typedef OpfTaskInfoIdxType
  *
  * Data type for index of task information.
  *
  */
typedef uint8 OpfTaskInfoIdxType;

/**
  * @typedef OpfSysTimerType
  *
  * Data type for a System Timer.
  *
  */
typedef uint32 OpfSystimeTickType;

/**
  * @typedef OpfObjectType
  *
  * Data type for an Object (Task/Cat2Isr).
  *
  */
typedef enum
{
  OPF_OBJECT_INVALID = 0,
  OPF_OBJECT_ISR,
  OPF_OBJECT_TASK,
  OPF_OBJECT_TIME
}OpfObjectType;

/**
  * @typedef OpfObjectType
  *
  * Data type for an Object (Task/Cat2Isr).
  *
  */
typedef enum
{
  OPF_FALSE = 0,
  OPF_TRUE,
}OpfBool;

/**
  * @typedef OpfObjectIDType
  *
  * Data type for an Object ID (Task/Cat2Isr).
  *
  */
typedef uint32 OpfObjectIDType;

/**
  * @typedef OpfTaskIDType
  *
  * Data type for an Task ID.
  *
  */
typedef uint32 OpfTaskIDType;

/**
  * @typedef OpfIsrIDType
  *
  * Data type for an Isr ID.
  *
  */
typedef uint8 OpfIsrIDType;

/**
  * @typedef OpfSpanTickType
  *
  * Data type for an Timer Tick.
  *
  */
typedef uint32 OpfSpanTickType;

/**
  * @typedef OpfTickType
  *
  * Data type for an Timer Tick.
  *
  */
typedef uint32 OpfTickType;

/**
  * @typedef OpfClockType
  *
  * Data type for an Timer Clock.
  *
  */
typedef uint32 OpfClockType;

/**
  * @typedef OpfTimerTickType
  *
  * Data type for an Timer Tick.
  *
  */
typedef uint16 OpfOsLimitCountType;

/**
  * @typedef OpfJitterType
  *
  * Data type for Jitter.
  *
  */
typedef uint32 OpfJitterType;

/**
  * @typedef OpfStateType
  *
  * Data type for a Task/Cat2Isr State.
  *
  */
typedef enum
{
  OPF_TASK_INVALID = 0,
  OPF_TASK_RUNNING,
  OPF_TASK_READY,
  OPF_TASK_WAITING,
  OPF_TASK_SUSPENDED,
  OPF_TASK_DELAYED,       /* Can't decide the current state */
  OPF_TASK_ACTIVATED,     /* New and Ready */
  OPF_TASK_LIMMITERROR,   /* Limit Error */
  OPF_ISR_ENTER,
  OPF_ISR_EXIT,
  OPF_TIME_INDEX
}OpfStateType;

/**
  * @typedef OpfRecModeType
  *
  * Data type for a Record Mode of OS Profiler.
  *
  */
typedef enum
{
  OPF_RECMODE_STOP = 0,
  OPF_RECMODE_EVENT,      /* Event Only */
  OPF_RECMODE_PROFILE,    /* Event, Profiled Event */
  OPF_RECMODE_RESTART     /* Restart */
}OpfRecModeType;

/**
  * @typedef OpfTaskCacheType
  *
  * Data type for checking Task Cache's validity.
  *
  */
typedef enum
{
  OPF_TC_NOCHECK = 0,     /* Not Checked */
  OPF_TC_INVALID,         /* Checked and valid */
  OPF_TC_VALID,           /* Checked, but not valid */
}OpfTaskCacheValidType;

/**
  * @typedef OpfTaskCacheType
  *
  * Data type for checking Task Cache's validity.
  *
  */
typedef enum
{
  OPF_TIV_INVALID,        /* Not valid */
  OPF_TIV_VALID,          /* Valid */
}OpfTaskInfoValidType;

/* polyspace-begin MISRA-C3:D4.8 [Not a Defect] "struct is visible to help user" */
/**
  * @struct Tdd_Opf_Event
  *
  * This structure holds an information of event.
  */
typedef struct
{
  /* System Time for a event */
  OpfTickType ddSysTime;
  /* TimeSpan (Interval) for a event */
  OpfTimeSpanType ddTimeSpan;
  /* Object Type for a event */
  OpfObjectType ddObject;
  /* Object ID Type for an Object */
  OpfObjectIDType ddObjectID;
  /* State for an Object */
  OpfStateType ddState;

} Tdd_Opf_Event;

/**
  * @struct StagTdd_Opf_TaskInfo
  *
  * This structure holds an information of each task.
  */
typedef struct
{
  /* Slack Time */
  OpfJitterType ddST;
  /* Jitter */
  OpfJitterType ddJIT;
  /* Core Execution Time */
  OpfTickType ddCET;
  /* Gross Execution Time */
  OpfTickType ddGET;
  /* Response Time */
  OpfTickType ddRT;
  /* New Ready Tick */
  OpfTickType ddNewReadyT_;
  /* New Ready Tick Validity */
  OpfTickType ddNewReadyTV_;
  /* Previous Ready Tick */
  OpfTickType ddPrevReadyT_;
  /* Previous Running Tick */
  OpfTickType ddPrevRunningT_;
  /* First Running Tick */
  OpfTickType ddFirstRunningT_;
  /* Cumulative Execution Time */
  OpfTickType ddCumulExecT_;
  /* Suspended Tick */
  OpfTickType ddSuspendedT_;
  /* Suspended Tick Validity */
  OpfBool ddSuspendedTV_;
  /* Slack Time */
  OpfTickType ddSlackT_;
  /* Jitter Time */
  OpfTickType ddJitterT_;

} Tdd_Opf_TaskInfo;
/* polyspace-end MISRA-C3:D4.8 */

/**
  * @struct StagTdd_Opf_ProfileTaskInfo
  *
  * This structure holds an information of each profiled task.
  */
/* polyspace-begin MISRA-C3:D4.8 [Not a Defect] "struct is visible to help user" */
typedef struct
{
  /* Task ID */
  OpfTaskIDType ddTaskID; /* will be initialized by generator */
  /* Period of Task */
  OpfTickType ddTaskPeriod;
  /* Min Slack Time */
  OpfJitterType ddMinST;
  /* Max Jitter */
  OpfJitterType ddMaxJIT;
  /* Max Core Execution Time */
  OpfTickType ddMaxCET;
  /* Max Gross Execution Time */
  OpfTickType ddMaxGET;
  /* Max Response Time */
  OpfTickType ddMaxRT;
  /* E_OS_LIMIT count */
  OpfOsLimitCountType ddOsLimitCount;

  /* Pointer to a task information */
  P2VAR(Tdd_Opf_TaskInfo, AUTOMATIC, OS_VAR) pTaskInfo;

} Tdd_Opf_ProfileTaskInfo;
/* polyspace-end MISRA-C3:D4.8 */

typedef struct
{
  /* Validity for the cache */
  OpfTaskCacheValidType ddIsValid;
  /* Index of task information */
  OpfTaskInfoIdxType ddIndex;
  /* Is Alarm Task ? */
  OpfBool ddIsAlarmTask;

} Tdd_Opf_GaaTaskCache;

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* OPF_TYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
