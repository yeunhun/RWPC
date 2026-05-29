/*******************************************************************************
**                                                                            **
**  (C) 2019-2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Os_Config.c                                                   **
**                                                                            **
**  TARGET    : CYTxxx                                                        **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of constant specific functionality.                 **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: Yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 2.1.0     11-Dec-2020    JH.Cho        Redmine #26391                      **
** 1.1.0     06-Mar-2020    MJ.Woo        Redmine #22057                      **
** 1.0.0     23-Dec-2019    MJ.Woo        Redmine #18913                      **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"
#if (OS_APPLICATION == STD_ON)
#include "Os_IocInternalTypes.h"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define OS_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* FIXME: Move to Common part. Remove unused variable */
/** This global const variable is used to define Application Mode Count
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(AppModeType, OS_CONST) Os_ApplMode_Count = (AppModeType)OS_APPLMODE_COUNT;
/** This global const variable is used to define Task Count
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(TaskType, OS_CONST) Os_Task_Count = (TaskType)OS_TASK_COUNT;
/** This global const variable is used to define Category 2 ISR Count
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(ISRType, OS_CONST) Os_CAT2_ISR_Count = (ISRType)OS_CAT2_ISR_COUNT;
/** This global const variable is used to define Category 1 ISR Count
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(ISRType, OS_CONST) Os_CAT1_ISR_Count = (ISRType)OS_CAT1_ISR_COUNT;
/** This global const variable is used to define All ISR Count
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(ISRType, OS_CONST) Os_ISR_Count = (ISRType)OS_ISR_COUNT;
/** This global const variable is used to define Maximum CAT2 ISR Priority
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(uint16, OS_CONST) Os_CAT2_Max_Priority = (uint16)OS_CAT2_MAX_PRIORITY;
/** This global const variable is used to define Minimum CAT1 ISR Priority
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(uint16, OS_CONST) Os_CAT1_Least_Priority = (uint16)OS_CAT1_LEAST_PRIORITY;
/** This global const variable is used to define Maximum CAT2 ISR Nesting
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(ISRType, OS_CONST) Os_Max_Nest_Level = (ISRType)OS_MAX_NEST_LEVEL;
/** This global const variable is used to define Resource Count
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(ResourceType, OS_CONST) OS_Resource_Count =
                                                (ResourceType)OS_RESOURCE_COUNT;
/** This global const variable is used to define Counter Count
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(CounterType, OS_CONST) Os_Counter_Count = (CounterType)OS_COUNTER_COUNT;
/** This global const variable is used to define Alarm Count
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(AlarmType, OS_CONST) Os_Alarm_Count = (AlarmType)OS_ALARM_COUNT;
/** This global const variable is used to define ScheduleTable Count
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(ScheduleTableType, OS_CONST) Os_Schedule_Count =
                                           (ScheduleTableType)OS_SCHEDULE_COUNT;
/** This global const variable is used to define CPU Core Count
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(uint8, OS_CONST) Os_Core_Count = (uint8)OS_CORE_COUNT;
/** This global const variable is used to define Spinlock Count
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(SpinlockIdType, OS_CONST) Os_Spinlock_Count =
                                              (SpinlockIdType)OS_SPINLOCK_COUNT;
/** This global const variable is used to define IOC Callback Count
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(uint16, OS_CONST) Os_Ioc_Callback_Count = (uint16)OS_IOC_CALLBACK_COUNT;
/** This global const variable is used to define IOC Count
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(uint16, OS_CONST) Os_Ioc_Count = (uint16)OS_IOC_COUNT;
/** This global const variable is used to define OS-Application Count
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(ApplicationType, OS_CONST) Os_Application_Count =
                                          (ApplicationType)OS_APPLICATION_COUNT;
/** This global const variable is used to define Trusted OS Applications start index
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(ApplicationType, OS_CONST) Os_Trusted_Start_Indx =
                                         (ApplicationType)OS_TRUSTED_START_INDX;
/** This global const variable is used to define Trusted Function Count
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(TrustedFunctionIndexType, OS_CONST) Os_Trusted_Func_Count =
                                (TrustedFunctionIndexType)OS_TRUSTED_FUNC_COUNT;
/** This global const variable is used to define Memory Block Count for Memory Protection
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(uint16, OS_CONST) Os_App_MemBlk_Cnt = (uint16)OS_APP_MEMBLK_CNT;

/** This global const variable is used to define Total number of Queued IOC
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(uint16, OS_CONST) Os_Ioc_Count_Queued = (uint16)OS_IOC_COUNT_QUEUED;

/** This global const variable is used to define Total number of Unqueued IOC
 *  \n{Ref: SWR_OS_CYTXXX_010} */
CONST(uint16, OS_CONST) Os_Ioc_Count_Unqueued = (uint16)OS_IOC_COUNT_UNQUEUED;
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define OS_START_SEC_CONST_32
#include "MemMap.h"
/** This global const variable is used to define size of user stack
 *  \n{Ref: SWR_OS_CYTXXX_006} */
CONST(uint32, OS_CONST) Os_User_Stack_Size = (uint32)(OS_USER_STACK_SIZE * sizeof(Os_StackType));
#define OS_STOP_SEC_CONST_32
#include "MemMap.h"

/* Dummy variables for IOC library function */
#if (OS_APPLICATION == STD_ON)

#if (OS_IOC_COUNT_UNQUEUED == OS_PRE_ZERO)
#define OS_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(Os_IocUnqueuedCfgType, OS_CONST) Os_GaaIocUnqueuedCfg[] =
{
  /* Unqueued Ioc Buffer info : 0 - Dummy */
  {
    /* *pBuffer */
    NULL_PTR,

    /* ulDataCount */
    0u
  }
};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif /* if (OS_IOC_COUNT_UNQUEUED == OS_PRE_ZERO) */

#if (OS_IOC_COUNT_QUEUED == OS_PRE_ZERO)
#define OS_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
VAR(Os_IocQueuedCfgType, OS_VAR) Os_GaaIocQueuedCfg[] =
{
  /* Queued Ioc Buffer info : 0 - Dummy */
  {
    /* *pBuffer */
    NULL_PTR,

    /* ulDataCount */
    0u,

    /* ulQueueLen */
    0u,

    /* ulQueueRead */
    0u,

    /* ulQueueWrite */
    0u,

    /* ulQueueCount */
    0u,

    /* blDataLost */
    FALSE
  }
};
#define OS_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif /* if (OS_IOC_COUNT_QUEUED == OS_PRE_ZERO) */

#endif /* if (OS_APPLICATION == STD_ON) */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
