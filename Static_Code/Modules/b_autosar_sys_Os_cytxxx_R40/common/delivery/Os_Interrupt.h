/*******************************************************************************
**                                                                            **
**  (C) 2013-2016 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Os_Interrupt.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for Os_Interrupt.c file containing the declaration**
**              of Interrupt functionality related functions.                 **
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
** 2.0.13    30-Jun-2016    MJ.Woo        Redmine #5368                       **
** 2.0.9     04-May-2015    MJ.Woo        Redmine #1640                       **
** 2.0.4     15-Nov-2013    MJ.Woo        CR: xar~179, TASK: xar~736          **
** 2.0.1     13-Aug-2013    MJ.Woo        CR: xar~160, TASK: xar~655          **
** 2.0.0     22-Jul-2013    SH.Yoo        CR: xar~107, TASK: xar~543          **
**                          DG.Lee,MJ.Woo                                     **
** 1.0.0     26-Mar-2013    Son           Initial version                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> see MEMMAP003 of AUTOSAR */

#ifndef OS_INTERRUPT_H_
#define OS_INTERRUPT_H_

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#define OS_SUSPENDNESTLIMIT   0xFF

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define OS_START_SEC_CODE
#include "MemMap.h"
#if (OS_ISR_COUNT != OS_PRE_ZERO)
extern FUNC(void, OS_CODE) Os_SetISRPriority(void);
#endif /* End of if (OS_ISR_COUNT != OS_PRE_ZERO) */

#if (OS_RES_INT_SHARE == STD_ON)
extern FUNC(uint32, OS_CODE) Os_OriginalPriority
                         (P2VAR(Tdd_Os_Resource, AUTOMATIC, OS_VAR) LpResource);

extern FUNC(uint32, OS_CODE) Os_RaisePriority
          (P2VAR(Tdd_Os_Resource, AUTOMATIC, OS_VAR) LpResource, uint32 HwPrio);
#endif /* End of if (OS_RES_INT_SHARE == STD_ON) */

#define OS_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<MISRA-C3:20.1> */

#endif /* OS_INTERRUPT_H_ */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
