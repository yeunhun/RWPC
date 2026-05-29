/*******************************************************************************
**                                                                            **
**  (C) 2019-2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Os_Arch_Context.h                                             **
**                                                                            **
**  TARGET    : CYTxxx                                                        **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for CYTxxx related register                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]:       Yes                                    **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]:    No                                     **
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
/* polyspace:begin<MISRA-C3:D4.9:Not a defect:Justify with annotations> Function like macro is used to improve performance  */
/* polyspace:begin<MISRA-C3:8.11:Not a defect:Justify with annotations> The generator generates exact size of initializers */
/* polyspace:begin<MISRA-C3:9.5:Not a defect:Justify with annotations> The generator generates exact size of initializers */

#ifndef OS_ARCH_CONTEXT_H_
#define OS_ARCH_CONTEXT_H_

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_Arch_Regs.h"
#include "Os_Arch_Ram.h"
#include "Os_Multicore.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/**
 * @addtogroup OS_CYTXXX_ESDD
 * @{ */

/** Macro for flag of context-switching
 *  \n{Ref: SWR_OS_CYTXXX_006} */
#define CONTEXT_SWITCHING_NONE      0x00u
/** Macro for flag of context-switching
 *  \n{Ref: SWR_OS_CYTXXX_006} */
#define CONTEXT_SWITCHING_STARTUP   0x01u
/** Macro for flag of context-switching
 *  \n{Ref: SWR_OS_CYTXXX_006} */
#define CONTEXT_SWITCHING_LOAD      0x02u
/** Macro for flag of context-switching
 *  \n{Ref: SWR_OS_CYTXXX_006} */
#define CONTEXT_SWITCHING_SAVE      0x04u
/** Macro for flag of context-switching
 *  \n{Ref: SWR_OS_CYTXXX_006} */
#define CONTEXT_SWITCHING_RELOAD    0x08u

/** Macro for Task's initialized PSR
 *  \n{Ref: SWR_OS_CYTXXX_006} */
#define OS_TASK_INIT_PSR            0x01000000u    /* Thumb, Thread mode */
/** Macro for EXEC_RETURN (Thread, PSP)
 *  \n{Ref: SWR_OS_CYTXXX_006} */
#define OS_EXC_RETURN_THREAD_MODE   0xFFFFFFFDu    /* Thread Mode, PSP   */

/** Macro to load the context only of the first Task
 *  \n{Ref: SWR_OS_CYTXXX_006} */
static inline FUNC(void, OS_CODE) OS_STARTUPCONTEXT(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  Os_GucSchedReq[OS_CORE_ID] = CONTEXT_SWITCHING_STARTUP;
}
/** Macro for loading the context
 *  \n{Ref: SWR_OS_CYTXXX_006} */
static inline FUNC(void, OS_CODE) OS_LOADCONTEXT(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  Os_GucSchedReq[OS_CORE_ID] = CONTEXT_SWITCHING_LOAD;
}
/** Macro for saving the context
 *  \n{Ref: SWR_OS_CYTXXX_006} */
static inline FUNC(void, OS_CODE) OS_SAVECONTEXT(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  Os_GucSchedReq[OS_CORE_ID] = CONTEXT_SWITCHING_SAVE;
}
/** Macro to load the context
 *  \n{Ref: SWR_OS_CYTXXX_006} */
static inline FUNC(void, OS_CODE) OS_RELOADCONTEXT(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  Os_GucSchedReq[OS_CORE_ID] = CONTEXT_SWITCHING_RELOAD;
}

#if ((OS_PROTECTION_HOOK == STD_ON) || (OS_APPLICATION == STD_ON))
/** Macro for Removing used context
 *  \n{Ref: SWR_OS_CYTXXX_006} */
#define OS_REMOVECONTEXT(LpStaticTask)  Os_RemoveContext(LpStaticTask)
#endif

/** Macro to write a typical data at the end of stack frame
 *  \n{Ref: SWR_OS_CYTXXX_006} */
#define OS_STACK_PATTERN                (Os_StackType)(0xAAAAAAAAu)

/** Macro for invalid stack pointer
 *  \n{Ref: SWR_OS_CYTXXX_006} */
#define INVALID_STACK_POINTER           0xFFFFFFFFUL

/** Macro for Stack frame (quadword alignment)
 *  \n{Ref: SWR_OS_CYTXXX_006} */
#define OS_STACK_RSVD_SIZE              1U

/** Macro for invalid address
 *  \n{Ref: SWR_OS_CYTXXX_006} */
#define OS_INVALID_ADDRESS              0xFFFFFFFFUL

/** Macro for saved context size
 *  : sizeof(Tdd_Os_ContextSwitch) - sizeof(pPowerOnSP)
 *  \n{Ref: SWR_OS_CYTXXX_006} */
#define OS_CONTEXT_SIZE                 72U

/** @} */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
extern FUNC(void, OS_CODE) Os_Dispatch(void);
extern FUNC(void, OS_CODE) Os_ReInitContext(P2CONST(
                          Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask);
extern FUNC(void, OS_CODE) Os_DoContextSwitch
                 (P2CONST(Tdd_Os_ContextSwitch, AUTOMATIC, OS_CONST) LpContext);
extern FUNC(void, OS_CODE) Os_SetTaskStackPointer(void);
/* polyspace +2 MISRA-C3:20.7 [Justified:Low] "AUTOSAR compiler abstraction" */
extern FUNC(void*, OS_CODE) Os_GetStackPointer(P2CONST(
                          Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask);
#if ((OS_PROTECTION_HOOK == STD_ON) || (OS_APPLICATION == STD_ON))
extern FUNC(void, OS_CODE) Os_RemoveContext(P2CONST(
                          Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask);
#endif

#endif /* OS_ARCH_CONTEXT_H_ */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<MISRA-C3:D4.9:Not a defect:Justify with annotations> Function like macro is used to improve performance  */
/* polyspace:end<MISRA-C3:8.11:Not a defect:Justify with annotations> The generator generates exact size of initializers */
/* polyspace:end<MISRA-C3:9.5:Not a defect:Justify with annotations> The generator generates exact size of initializers */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
