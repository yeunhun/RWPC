/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Os_Arch_Timer.h                                               **
**                                                                            **
**  TARGET    : CYTxxx                                                        **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for CYTxxx related (OS) Timer API                 **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]:     Yes                                      **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]:  No                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 2.3.0     26-Jan-2021    YH.Han        Redmine #27953                      **
** 1.0.0     23-Dec-2019    MJ.Woo        Redmine #18913                      **
*******************************************************************************/
#ifndef OS_ARCH_TIMER_H_
#define OS_ARCH_TIMER_H_

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<RTE:ABS_ADDR:Not a defect:Justify with annotations> MCU register access */
/* polyspace:begin<MISRA-C3:2.3:Not a defect:Justify with annotations> Informative typedef used */
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_PortTypes.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/**
 * @addtogroup OS_CYTXXX_ESDD
 * @{ */
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define OS_START_SEC_CODE
#include "MemMap.h"

extern FUNC(TickType, OS_CODE) Os_GetCurrentTCPWM(Os_TimerIdType LddTimerId);
extern FUNC(void, OS_CODE) Os_StartTimerHw(Os_TimerIdType timerId,
                                                             uint32 timerCount);

extern FUNC(void, OS_CODE) Os_AdjustTimerInterrupt(TickType LddNewAbsCount,
                  P2VAR(Tdd_Os_HardwareCounter, AUTOMATIC, OS_VAR) LpHwCounter);
extern FUNC(void, OS_CODE) Os_UpdateHwCounter(
                  P2VAR(Tdd_Os_HardwareCounter, AUTOMATIC, OS_VAR) LpHwCounter);
extern FUNC(void, OS_CODE) Os_StartHwCounter(TickType LddNanoSecPerTick,
                  P2VAR(Tdd_Os_HardwareCounter, AUTOMATIC, OS_VAR) LpHwCounter);
extern FUNC(boolean, OS_CODE) Os_CheckTimerExpired(Os_TimerIdType timerId);
extern FUNC(void, OS_CODE) Os_ClearTimerIntFlag(Os_TimerIdType timerId);
extern FUNC(TickType, OS_CODE) Os_GetElapsedTick(TickType LddPrevTick,
                               TickType LddCurrentTick, TickType LddMaxAllowed);
extern FUNC(uint32, OS_CODE) Os_GetElapsedTime(void);
extern FUNC(uint32, OS_CODE) Os_GetReloadTime(void);

#if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO)
extern FUNC(void, OS_CODE) Os_InitTimer0(void);
#if (OS_MULTICORE == STD_ON)
extern FUNC(void, OS_CODE) Os_InitTimer1(void);
#if (OS_CORE_COUNT >= OS_THREE)
extern FUNC(void, OS_CODE) Os_InitTimer2(void);
#endif
#endif
#endif

/** @} */

#define OS_STOP_SEC_CODE
#include "MemMap.h"

#endif /* OS_ARCH_TIMER_H_ */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<RTE:ABS_ADDR:Not a defect:Justify with annotations> MCU register access */
/* polyspace:end<MISRA-C3:2.3:Not a defect:Justify with annotations> Informative typedef used */
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/


