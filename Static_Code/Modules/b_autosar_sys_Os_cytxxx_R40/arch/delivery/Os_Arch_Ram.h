/*******************************************************************************
**                                                                            **
**  (C) 2019-2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Os_Arch_Ram.h                                                 **
**                                                                            **
**  TARGET    : CYTxxx                                                        **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for CYTxxx related global var                     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]:      Yes                                     **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]:   No                                      **
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

#ifndef OS_ARCH_RAM_H_
#define OS_ARCH_RAM_H_

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:8.5:Not a defect:Justify with annotations> Redundant declaration for generated code */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define OS_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
extern VAR(uint32, OS_VAR) Os_GulUserSP[OS_CORE_COUNT];
extern VAR(uint32, OS_VAR) Os_GulUserSPBtm[OS_CORE_COUNT];
extern VAR(uint32, OS_VAR) Os_GulUserSPTop[OS_CORE_COUNT];

#if (OS_APPLICATION == STD_ON)
/* polyspace-begin MISRA-C:8.12 [Justified:Low] "External linkage with array size makes error because of compiler optimization" */
extern VAR(uint32, OS_VAR) Os_GulOsAppSP[];
extern VAR(uint32, OS_VAR) Os_GulOsAppSPBtm[];
extern VAR(uint32, OS_VAR) Os_GulOsAppSPTop[];
/* polyspace-end MISRA-C:8.12 */
#endif /* End of #if (OS_APPLICATION == STD_ON) */

#if (OS_MULTICORE == STD_ON)
extern VAR(uint32, OS_VAR) Os_GulSpinlocks[];
#endif /* End of if (OS_MULTICORE == STD_ON) */

extern VAR(uint32, OS_VAR) Os_GulKernelSP[OS_CORE_COUNT];
extern VAR(uint32, OS_VAR) Os_GulKernelSPBase[OS_CORE_COUNT];
#define OS_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
extern VAR(uint8, OS_VAR) Os_GucInKernel[OS_CORE_COUNT];
extern VAR(uint8, OS_VAR) Os_GucSchedReq[OS_CORE_COUNT];
extern VAR(uint8, OS_VAR) Os_GucNestingCAT1ISR[OS_CORE_COUNT];
extern VAR(uint8, OS_VAR) Os_GucNestingCAT2ISR[OS_CORE_COUNT];
extern VAR(uint8, OS_VAR) Os_GucCheckCAT2IsrTF[OS_CORE_COUNT];
extern VAR(uint8, OS_VAR) Os_GucKillCAT2ISR[OS_CORE_COUNT];
#define OS_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/*Os_GusCurrentIsrNumber will be used to clear pending state of this interrupt
 * when entering into thread mode for executing HOOK function  */
extern VAR(uint16, OS_VAR) Os_GusCurrentIsrNumber;
extern VAR(uint16, OS_VAR) Os_GusPreserveBasepri;
extern VAR(uint16, OS_VAR) Os_GusPreserveControl;

#define OS_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#if (OS_APPLICATION == STD_ON)
#define OS_START_SEC_STACK_CORE0_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern VAR(Os_StackType, OS_VAR) Os_GaaRamUserStack0[OS_USER_STACK_SIZE];
#define OS_STOP_SEC_STACK_CORE0_CLEARED_UNSPECIFIED
#include "MemMap.h"
#if (OS_MULTICORE == STD_ON)
#define OS_START_SEC_STACK_CORE1_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern VAR(Os_StackType, OS_VAR) Os_GaaRamUserStack1[OS_USER_STACK_SIZE];
#define OS_STOP_SEC_STACK_CORE1_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* #if (OS_MULTICORE == STD_ON) */
#else  /* #if (OS_APPLICATION == STD_ON) */
#define OS_START_SEC_STACK_CORE0_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern VAR(Os_StackType, OS_VAR) Os_GaaRamUserStack[OS_USER_STACK_SIZE];
#define OS_STOP_SEC_STACK_CORE0_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* #if (OS_APPLICATION == STD_ON) */

/* Variable to hold STM Clock Frequency in MHz unit */
#define OS_START_SEC_VAR_INIT_32
#include "MemMap.h"
extern VAR(uint32, OS_VAR) Os_GulStmClock;
#define OS_STOP_SEC_VAR_INIT_32
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern VAR(Os_TrapInfoType, OS_VAR) Os_GddTrapInfo[OS_CORE_COUNT];
#if (OS_MULTICORE == STD_ON)
extern Os_MessageQueueArchType Os_GaaInterCoreMsgQ[];
#endif
#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#endif /* OS_ARCH_RAM_H_ */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<MISRA-C3:8.5:Not a defect:Justify with annotations> Redundant declaration for generated code */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
