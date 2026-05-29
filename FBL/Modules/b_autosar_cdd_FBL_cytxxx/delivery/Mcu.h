/*******************************************************************************
**                                                                            **
**  (C) 2020 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Mcu.h                                                         **
**                                                                            **
**  TARGET    : CYTXXX                                                        **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides access related features of controller register       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision    Date          By           Description                         **
********************************************************************************
** 1.2.0     10-May-2021   JHLim        #28951                                **
** 1.1.0.0     23-Feb-2021   JHLim        Redmine #23964                      **
** 1.0.0       10-April-2020 JaeHyun      Initial version                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:D4.9,2.3,2.4,2.5,6.1,11.4,19.2,20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef MCU_H
#define MCU_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Fbl_cfg.h"
#include "arm_ghs.h"

#if(FBL_MCU_NAME == CYT2B7XX)
#include "Cyt2b7_regs.h"
#elif(FBL_MCU_NAME == CYT2B9XX)
#include "Cyt2b9_regs.h"
#elif(FBL_MCU_NAME == CYT2BLXX)
#include "Cyt2bl_regs.h"
#elif(FBL_MCU_NAME == CYT3BBXX)
#include "Cyt3bb_regs.h"
#elif(FBL_MCU_NAME == CYT4BBXX)
#include "Cyt4bb_regs.h"
#elif(FBL_MCU_NAME == CYT4BFXX)
#include "Cyt4bf_regs.h"
#else
#error "This MCU is not supported in FBL"
#endif

/*******************************************************************************
*                    Processor and Core Peripheral Section
*******************************************************************************/

#ifndef   __ASM
  #define __ASM                           __asm
#endif 
#ifndef   __DMB
  #define __DMB()                   __ASM("dmb")
#endif  
#ifndef   __DSB
  #define __DSB()                   __ASM("dsb")
#endif  
#ifndef   __ISB
  #define __ISB()                   __ASM("isb")
#endif  
#ifndef   __WFI
  #define __WFI()                   __ASM("wfi")
#endif
#ifndef   __WFE
  #define __WFE()                   __ASM("wfe")
#endif
#ifndef   __enable_irq
  #define __enable_irq()            __ASM("cpsie i")
#endif
#ifndef   __disable_irq
  #define __disable_irq()           __ASM("cpsid i")
#endif
 
/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/



/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_PJS_CODE
#include "Btl_MemMap.h"


#define BTL_STOP_SEC_PJS_CODE
#include "Btl_MemMap.h"

#endif /* MCU_H */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:D4.9,2.3,2.4,2.5,6.1,11.4,19.2,20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
