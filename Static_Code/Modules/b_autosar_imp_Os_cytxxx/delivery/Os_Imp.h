/*******************************************************************************
**                                                                            **
**  (C) 2020 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Os_Imp.h                                                      **
**                                                                            **
**  TARGET    : CYTxxx                                                        **
**                                                                            **
**  PRODUCT   : AUTOSAR OS Improvement Code                                   **
**                                                                            **
**  PURPOSE   : Header file for OS Improvement Code                           **
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
** 1.0.0     18-Feb-2020    MJ.Woo        Redmine #20864                      **
*******************************************************************************/

#ifndef OS_IMP_H
#define OS_IMP_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_Hook.h"
#include "Os_Imp_Cfg.h"
#include "Os_PortTypes.h"
#include "Os_Debug.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/** Structure of FAULT_STRUCT Registers */
typedef volatile struct
{
  Os_Reg32 CTL;              /*!< 0x00000000 Fault control */
  Os_Reg32 reserved[2];
  Os_Reg32 STATUS;           /*!< 0x0000000C Fault status */
  Os_Reg32 DATA[4];          /*!< 0x00000010 Fault data */
  Os_Reg32 reserved1[8];
  Os_Reg32 PENDING0;         /*!< 0x00000040 Fault pending 0 */
  Os_Reg32 PENDING1;         /*!< 0x00000044 Fault pending 1 */
  Os_Reg32 PENDING2;         /*!< 0x00000048 Fault pending 2 */
  Os_Reg32 reserved2;
  Os_Reg32 MASK0;            /*!< 0x00000050 Fault mask 0 */
  Os_Reg32 MASK1;            /*!< 0x00000054 Fault mask 1 */
  Os_Reg32 MASK2;            /*!< 0x00000058 Fault mask 2 */
  Os_Reg32 reserved3[25];
  Os_Reg32 INTR;             /*!< 0x000000C0 Interrupt */
  Os_Reg32 INTR_SET;         /*!< 0x000000C4 Interrupt set */
  Os_Reg32 INTR_MASK;        /*!< 0x000000C8 Interrupt mask */
  Os_Reg32 INTR_MASKED;      /*!< 0x000000CC Interrupt masked */
  Os_Reg32 reserved4[12];
} Os_FaultStructType;

/* polyspace-begin MISRA-C3:11.4 [Justified:Low] "Required for register access" */
#define OS_FAULT_STRUCT0            ((Os_FaultStructType *)0x40210000u)
#define OS_FAULT_STRUCT1            ((Os_FaultStructType *)0x40210100u)
#define OS_FAULT_STRUCT2            ((Os_FaultStructType *)0x40210200u)
#define OS_FAULT_STRUCT3            ((Os_FaultStructType *)0x40210300u)
/* polyspace-end MISRA-C3:11.4 */

#define OS_FAULT_FLASHC_MAIN_NC_ECC 0x80000032u
#define OS_FAULT_RAMC0_NC_ECC       0x8000003Bu
#define OS_FAULT_RAMC1_NC_ECC       0x8000003Du

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
extern FUNC(void, OS_CODE) Os_InitRamSector32(uint32 ramSectorCount,
                                 CONST(Os_RamSectorType, OS_CONST) ramSector[]);
extern FUNC(void, OS_CODE) Os_ResetMCU(void);
extern FUNC(void, OS_CALLOUT_CODE) Os_CallBackNMInterrupt(void);

#endif /* OS_IMP_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

