/*******************************************************************************
**                                                                            **
**  (C) 2019-2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: OS_Arch_Ram.c                                                 **
**                                                                            **
**  TARGET    : CYTxxx                                                        **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of constant specific functionality                  **
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
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Arch_Ram.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/**
 * @addtogroup OS_CYTXXX_ESDD
 * @{ */
#define OS_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/** This global variable is used to define in kernel mode
 *  \n{Ref: SWR_OS_CYTXXX_006} */
VAR(uint8, OS_VAR) Os_GucInKernel[OS_CORE_COUNT];

/** This global variable is used to define schedule request
 *  \n{Ref: SWR_OS_CYTXXX_006} */
VAR(uint8, OS_VAR) Os_GucSchedReq[OS_CORE_COUNT];

/** This is global array which signifies the count which gets modified if any
 *  Cagegory1 ISR comes in or it gets completed
 *  \n{Ref: SWR_OS_CYTXXX_006} */
VAR(uint8, OS_VAR) Os_GucNestingCAT1ISR[OS_CORE_COUNT];

/** This is global array which signifies the count which gets modified if any
 *  Category2 ISR comes in or it gets completed
 *  \n{Ref: SWR_OS_CYTXXX_006} */
VAR(uint8, OS_VAR) Os_GucNestingCAT2ISR[OS_CORE_COUNT];

VAR(uint8, OS_VAR) Os_GucCheckCAT2IsrTF[OS_CORE_COUNT];
/* This global variable is used to check if CAT2ISR is killed
 * Because of timing protection*/
VAR(uint8, OS_VAR) Os_GucKillCAT2ISR[OS_CORE_COUNT];
#define OS_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/*Os_GusCurrentIsrNumber will be used to clear pending state of this interrupt
 * when entering into thread mode for executing HOOK function  */
VAR(uint16, OS_VAR) Os_GusCurrentIsrNumber;
VAR(uint16, OS_VAR) Os_GusPreserveBasepri;
VAR(uint16, OS_VAR) Os_GusPreserveControl;

#define OS_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#if (OS_MULTICORE == STD_ON)
#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* polyspace<MISRA-C:3.4:Not a defect:Justify with annotations> It is used to make 32byte alignment  */
VAR(Os_MessageQueueArchType, OS_VAR) Os_GaaInterCoreMsgQ[OS_CORE_COUNT];
/* polyspace<MISRA-C:3.4:Not a defect:Justify with annotations> It is used to return pragma level as the previous pragma level  */
#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#define OS_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
/** This is global array which hold current user stack pointer
 *  \n{Ref: SWR_OS_CYTXXX_006} */
VAR(uint32, OS_VAR) Os_GulUserSP[OS_CORE_COUNT];
/** This is global array which hold bottom of user stack
 *  \n{Ref: SWR_OS_CYTXXX_006} */
VAR(uint32, OS_VAR) Os_GulUserSPBtm[OS_CORE_COUNT];
/** This is global array which hold top of user stack
 *  \n{Ref: SWR_OS_CYTXXX_006} */
VAR(uint32, OS_VAR) Os_GulUserSPTop[OS_CORE_COUNT];

#if (OS_APPLICATION == STD_ON)
/** This is global array which hold current OS-Application stack pointer
 *  \n{Ref: SWR_OS_CYTXXX_006} */
VAR(uint32, OS_VAR) Os_GulOsAppSP[OS_APPLICATION_COUNT];
/** This is global array which hold bottom of OS-Application stack
 *  \n{Ref: SWR_OS_CYTXXX_006} */
VAR(uint32, OS_VAR) Os_GulOsAppSPBtm[OS_APPLICATION_COUNT];
/** This is global array which hold top of OS-Application stack
 *  \n{Ref: SWR_OS_CYTXXX_006} */
VAR(uint32, OS_VAR) Os_GulOsAppSPTop[OS_APPLICATION_COUNT];
#endif /* End of #if (OS_APPLICATION == STD_ON) */

#if (OS_MULTICORE == STD_ON)
/** This is global array which hold current state of spinlock (lock or unlock)
 *  \n{Ref: SWR_OS_CYTXXX_006} */
VAR(uint32, OS_VAR) Os_GulSpinlocks[OS_SPINLOCK_COUNT];
#endif /* End of if (OS_MULTICORE == STD_ON) */

/** This global variable is used to save kernel stack pointer
 *  \n{Ref: SWR_OS_CYTXXX_011} */
VAR(uint32, OS_VAR) Os_GulKernelSP[OS_CORE_COUNT];

/** This global variable is used to save kernel stack base address
 *  \n{Ref: SWR_OS_CYTXXX_011} */
VAR(uint32, OS_VAR) Os_GulKernelSPBase[OS_CORE_COUNT];
#define OS_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#if (OS_APPLICATION == STD_ON)
#define OS_START_SEC_STACK_CORE0_CLEARED_UNSPECIFIED
#include "MemMap.h"
/** This global variable is used to make user stack space for Os_Sleep0 */
VAR(Os_StackType, OS_VAR) Os_GaaRamUserStack0[OS_USER_STACK_SIZE];
#define OS_STOP_SEC_STACK_CORE0_CLEARED_UNSPECIFIED
#include "MemMap.h"
#if (OS_MULTICORE == STD_ON)
#define OS_START_SEC_STACK_CORE1_CLEARED_UNSPECIFIED
#include "MemMap.h"
/** This global variable is used to make user stack space for Os_Sleep1 */
VAR(Os_StackType, OS_VAR) Os_GaaRamUserStack1[OS_USER_STACK_SIZE];
#define OS_STOP_SEC_STACK_CORE1_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* #if (OS_MULTICORE == STD_ON) */
#else  /* #if (OS_APPLICATION == STD_ON) */
#define OS_START_SEC_STACK_CORE0_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* This global variable is used to make user stack space when OS-Application is not used */
VAR(Os_StackType, OS_VAR) Os_GaaRamUserStack[OS_USER_STACK_SIZE];
#define OS_STOP_SEC_STACK_CORE0_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* #if (OS_APPLICATION == STD_ON) */

#define OS_START_SEC_VAR_INIT_32
#include "MemMap.h"
/** This global variable is used to hold STM Clock Frequency in MHz unit
 *  \n{Ref: SWR_OS_CYTXXX_007} */
VAR(uint32, OS_VAR) Os_GulStmClock = OS_TIMER_CLOCK;
#define OS_STOP_SEC_VAR_INIT_32
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/** This global variable is used to save exception information
 *  \n{Ref: SWR_OS_CYTXXX_004} */
VAR(Os_TrapInfoType, OS_VAR) Os_GddTrapInfo[OS_CORE_COUNT];
#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/** @} */
/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
