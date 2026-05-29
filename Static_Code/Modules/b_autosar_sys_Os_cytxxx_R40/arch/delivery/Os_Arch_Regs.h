/*******************************************************************************
**                                                                            **
**  (C) 2019-2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Os_Arch_Regs.h                                                **
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
** 2.3.0     26-Jan-2021    YH.Han        Redmine #27953                      **
** 2.1.0     11-Dec-2020    JH.Cho        Redmine #26391                      **
** 2.0.1     10-AUG-2020    JH.Cho        Redmine #24903, #25096              **
** 2.0.0     16-JUN-2020    JH.Cho        Redmine #23917                      **
** 1.1.0     06-Mar-2020    MJ.Woo        Redmine #22057                      **
** 1.0.0     23-Dec-2019    MJ.Woo        Redmine #18913                      **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:11.4 [Justified:Medium] "To access Registers" */
/* polyspace-begin MISRA-C3:19.2 [Justified:Low] "These unions are used to specify register" */

#ifndef OS_ARCH_REGS_H_
#define OS_ARCH_REGS_H_

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

/** Macro for PRIV bit mask
 * \n{Ref: SWR_OS_CYTXXX_006} */
#define OS_MASK_MSR_PR                              (0x00004000U)

 /** Macro for base priority
 * \n{Ref: SWR_OS_CYTXXX_006} */
#define OS_MASK_BASEPRI                             (0x00000000U)

/** Macro for CPU_INT_VALID bit mask of the CPUSS_CMx_SYSTEM_INT_CTLn (x: 4, 7_0, 7_1)
 * \n{Ref: SWR_OS_CYTXXX_006} */
#define OS_MASK_CPU_INT_VALID                       (0x80000000U)

 /** Macro for valid LSB of IPR(i.e Priority should be shifted by this value)
 * \n{Ref: SWR_OS_CYTXXX_006} */
#define OS_IPR_LSB                                  (0x00000005U)

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/** Macro to get main stack pointer
 *  \n{Ref: SWR_OS_CYTXXX_006} */
/* polyspace<MISRA-C3:D4.9:Not a defect:Justify with annotations> Function like macro is used to improve performance  */
#define OS_GETMSP()           Os_GetMSP()
/* polyspace<MISRA-C3:D4.9:Not a defect:Justify with annotations> Function like macro is used to improve performance  */
#define OS_GETPSP()           Os_GetPSP()

/** Macro to set main stack pointer
 *  \n{Ref: SWR_OS_CYTXXX_006} */
/* polyspace<MISRA-C3:D4.9:Not a defect:Justify with annotations> Function like macro is used to improve performance  */
#define OS_SETSP(x)           Os_SetMSP(x)

/** @} */

extern uint32 Os_GetMSP(void);
extern void   Os_SetMSP(uint32 cortexM_msp);
extern uint32 Os_GetPSP(void);
extern void   Os_SetPSP(uint32 cortexM_psp);
extern uint32 Os_GetCONTROL(void);
extern uint32 Os_IrqGetVectNumber(void);

/*
 * Peripheral interconnect (PERI)
 */

/* Structure of PERI_DIV_CMD (Divider command) register */
typedef volatile union
{
  struct
  {
    Os_Reg32 DIV_SEL        : 8;
    Os_Reg32 TYPE_SEL       : 2;
    Os_Reg32                : 6;
    Os_Reg32 PA_DIV_SEL     : 8;
    Os_Reg32 PA_TYPE_SEL    : 2;
    Os_Reg32                : 4;
    Os_Reg32 DISABLE        : 1;
    Os_Reg32 ENABLE         : 1;
  } B;
  sint32 I;
  uint32 U;
} OS_PERI_DIV_CMD_type;

/* PERI_DIV_CMD register */
#define OS_PERI_DIV_CMD               (*(volatile OS_PERI_DIV_CMD_type *)(0x40000400u))

/* PERI_PCLK_GR0_DIV_CMD register */
#define OS_PERI_PCLK_GR0_DIV_CMD      (*(volatile OS_PERI_DIV_CMD_type *)(0x40040000u))

/* PERI_PCLK_GR1_DIV_CMD register */
#define OS_PERI_PCLK_GR1_DIV_CMD      (*(volatile OS_PERI_DIV_CMD_type *)(0x40042000u))

/*
 * Peripheral interconnect (PERI)
 */

/* Structure of PERI_DIV_16_CTL (Divider control (for 16.0 divider)) register */
typedef volatile union
{
  struct
  {
    Os_Reg32 EN             : 1;
    Os_Reg32                : 7;
    Os_Reg32 INT16_DIV      : 16;
    Os_Reg32                : 8;
  } B;
  sint32 I;
  uint32 U;
} OS_PERI_DIV_16_CTL_type;

/* PERI_DIV_16_CTL register */
#define OS_PERI_DIV_16_CTL0           (*(volatile OS_PERI_DIV_16_CTL_type *)(0x40001400u))

/* PERI_PCLK_GR1_DIV_16_CTL register */
#define OS_PERI_PCLK_GR0_DIV_16_CTL0  (*(volatile OS_PERI_DIV_16_CTL_type *)(0x40041400u))

/* PERI_PCLK_GR1_DIV_16_CTL register */
#define OS_PERI_PCLK_GR1_DIV_16_CTL0  (*(volatile OS_PERI_DIV_16_CTL_type *)(0x40043400u))

/* Structure of PERI_CLOCK_CTL (Clock control) register */
typedef volatile union
{
  struct
  {
    Os_Reg32 DIV_SEL        : 5;
    Os_Reg32                : 3;
    Os_Reg32 TYPE_SEL       : 2;
    Os_Reg32                : 22;
  } B;
  sint32 I;
  uint32 U;
} OS_PERI_CLOCK_CTL_type;

#if (OS_PROCESSOR_SERIES == CYT2B7)
/* PERI_CLOCK_CTL107 register */
#define OS_PERI_CLOCK_CTL107  (*(volatile OS_PERI_CLOCK_CTL_type *)(0x40000DACu))
/* PERI_CLOCK_CTL108 register */
#define OS_PERI_CLOCK_CTL108  (*(volatile OS_PERI_CLOCK_CTL_type *)(0x40000DB0u))
#elif (OS_PROCESSOR_SERIES == CYT2B9)
/* PERI_CLOCK_CTL117 register */
#define OS_PERI_CLOCK_CTL117  (*(volatile OS_PERI_CLOCK_CTL_type *)(0x40000DD4u))
/* PERI_CLOCK_CTL118 register */
#define OS_PERI_CLOCK_CTL118  (*(volatile OS_PERI_CLOCK_CTL_type *)(0x40000DD8u))
#elif (OS_PROCESSOR_SERIES == CYT2BL)
/* PERI_CLOCK_CTL117 register */
#define OS_PERI_CLOCK_CTL117  (*(volatile OS_PERI_CLOCK_CTL_type *)(0x40000DD4u))
/* PERI_CLOCK_CTL118 register */
#define OS_PERI_CLOCK_CTL118  (*(volatile OS_PERI_CLOCK_CTL_type *)(0x40000DD8u))
#elif (OS_PROCESSOR_SERIES == CYT4BB)
/* PERI_PCLK_GR1_CLOCK_CTL114 register */
#define OS_PERI_PCLK_GR1_CLOCK_CTL114  (*(volatile OS_PERI_CLOCK_CTL_type *)(0x40042DC8u))
/* PERI_PCLK_GR1_CLOCK_CTL115 register */
#define OS_PERI_PCLK_GR1_CLOCK_CTL115  (*(volatile OS_PERI_CLOCK_CTL_type *)(0x40042DCCu))
/* PERI_PCLK_GR1_CLOCK_CTL116 register */
#define OS_PERI_PCLK_GR1_CLOCK_CTL116  (*(volatile OS_PERI_CLOCK_CTL_type *)(0x40042DD0u))
/* PERI_PCLK_GR1_CLOCK_CTL117 register */
#define OS_PERI_PCLK_GR1_CLOCK_CTL117  (*(volatile OS_PERI_CLOCK_CTL_type *)(0x40042DD4u))
#elif (OS_PROCESSOR_SERIES == CYT4BF)
/* PERI_PCLK_GR0_CLOCK_CTL13 register */
#define OS_PERI_PCLK_GR0_CLOCK_CTL13  (*(volatile OS_PERI_CLOCK_CTL_type *)(0x40040C34u))
/* PERI_PCLK_GR0_CLOCK_CTL14 register */
#define OS_PERI_PCLK_GR0_CLOCK_CTL14  (*(volatile OS_PERI_CLOCK_CTL_type *)(0x40040C38u))
/* PERI_PCLK_GR1_CLOCK_CTL142 register */
#define OS_PERI_PCLK_GR1_CLOCK_CTL142 (*(volatile OS_PERI_CLOCK_CTL_type *)(0x40042E38u))
/* PERI_PCLK_GR1_CLOCK_CTL143 register */
#define OS_PERI_PCLK_GR1_CLOCK_CTL143 (*(volatile OS_PERI_CLOCK_CTL_type *)(0x40042E3Cu))
#else
#error "Specified MCU is not supported."
#endif

/* Structure of TCPWM_GRP_CNT_CTRL (Counter control register) register */
typedef volatile union
{
  struct
  {
    Os_Reg32 AUTO_RELOAD_CC0      : 1;
    Os_Reg32 AUTO_RELOAD_CC1      : 1;
    Os_Reg32 AUTO_RELOAD_PERIOD   : 1;
    Os_Reg32 AUTO_RELOAD_LINE_SEL : 1;
    Os_Reg32 CC0_MATCH_UP_EN      : 1;
    Os_Reg32 CC0_MATCH_DOWN_EN    : 1;
    Os_Reg32 CC1_MATCH_UP_EN      : 1;
    Os_Reg32 CC1_MATCH_DOWN_EN    : 1;
    Os_Reg32 PWM_IMM_KILL         : 1;
    Os_Reg32 PWM_STOP_ON_KILL     : 1;
    Os_Reg32 PWM_SYNC_KILL        : 1;
    Os_Reg32                      : 1;
    Os_Reg32 PWM_DISABLE_MODE     : 2;
    Os_Reg32                      : 2;
    Os_Reg32 UP_DOWN_MODE         : 2;
    Os_Reg32 ONE_SHOT             : 1;
    Os_Reg32                      : 1;
    Os_Reg32 QUAD_ENCODING_MODE   : 2;
    Os_Reg32                      : 2;
    Os_Reg32 MODE                 : 3;
    Os_Reg32                      : 3;
    Os_Reg32 DBG_FREEZE_EN        : 1;
    Os_Reg32 ENABLED              : 1;
  } B;
  sint32 I;
  uint32 U;
} OS_TCPWM_GRP_CNT_CTRL_type;

/* Structure of TCPWM_GRP_CNT_TR_CMD (Counter trigger command register) register */
typedef volatile union
{
  struct
  {
    Os_Reg32 CAPTURE0       : 1;
    Os_Reg32                : 1;
    Os_Reg32 RELOAD         : 1;
    Os_Reg32 STOP           : 1;
    Os_Reg32 START          : 1;
    Os_Reg32 CAPTURE1       : 1;
    Os_Reg32                : 26;
  } B;
  sint32 I;
  uint32 U;
} OS_TCPWM_GRP_CNT_TR_CMD_type;

/* Structure of TCPWM_GRP_CNT_PERIOD (Counter period register) register */
typedef volatile union
{
  struct
  {
    Os_Reg32 PERIOD         : 32;
  } B;
  sint32 I;
  uint32 U;
} OS_TCPWM_GRP_CNT_PERIOD_type;

/* Structure of TCPWM_GRP_CNT_INTR (Interrupt request register) register */
typedef volatile union
{
  struct
  {
    Os_Reg32 TC             : 1;
    Os_Reg32 CC0_MATCH      : 1;
    Os_Reg32 CC1_MATCH      : 1;
    Os_Reg32                : 29;
  } B;
  sint32 I;
  uint32 U;
} OS_TCPWM_GRP_CNT_INTR_type;

/* Structure of TCPWM_GRP_CNT_INTR_MASK (Interrupt mask register) register */
typedef volatile union
{
  struct
  {
    Os_Reg32 TC             : 1;
    Os_Reg32 CC0_MATCH      : 1;
    Os_Reg32 CC1_MATCH      : 1;
    Os_Reg32                : 29;
  } B;
  sint32 I;
  uint32 U;
} OS_TCPWM_GRP_CNT_INTR_MASK_type;

/* OS_TCPWM0_GRP2_CNT1_CTRL */
#define OS_TCPWM0_GRP2_CNT1_CTRL      (*(volatile OS_TCPWM_GRP_CNT_CTRL_type *)(0x40390080u))

/* TCPWM0_GRP2_CNT1_COUNTER */
#define OS_TCPWM0_GRP2_CNT1_COUNTER   (*(volatile uint32 *)(0x40390088u))

/* TCPWM0_GRP2_CNT1_PERIOD */
#define OS_TCPWM0_GRP2_CNT1_PERIOD    (*(volatile OS_TCPWM_GRP_CNT_PERIOD_type *)(0x403900A0u))

/* TCPWM0_GRP2_CNT1_TR_CMD */
#define OS_TCPWM0_GRP2_CNT1_TR_CMD    (*(volatile OS_TCPWM_GRP_CNT_TR_CMD_type *)(0x403900C0u))

/* TCPWM0_GRP2_CNT1_INTR */
#define OS_TCPWM0_GRP2_CNT1_INTR      (*(volatile OS_TCPWM_GRP_CNT_INTR_type *)(0x403900F0u))

/* TCPWM0_GRP2_CNT1_INTR_MASK */
#define OS_TCPWM0_GRP2_CNT1_INTR_MASK (*(volatile OS_TCPWM_GRP_CNT_INTR_MASK_type *)(0x403900F8u))

/* OS_TCPWM0_GRP2_CNT2_CTRL */
#define OS_TCPWM0_GRP2_CNT2_CTRL      (*(volatile OS_TCPWM_GRP_CNT_CTRL_type *)(0x40390100u))

/* TCPWM0_GRP2_CNT2_COUNTER */
#define OS_TCPWM0_GRP2_CNT2_COUNTER   (*(volatile uint32 *)(0x40390108u))

/* TCPWM0_GRP2_CNT2_PERIOD */
#define OS_TCPWM0_GRP2_CNT2_PERIOD    (*(volatile OS_TCPWM_GRP_CNT_PERIOD_type *)(0x40390120u))

/* TCPWM0_GRP2_CNT2_TR_CMD */
#define OS_TCPWM0_GRP2_CNT2_TR_CMD    (*(volatile OS_TCPWM_GRP_CNT_TR_CMD_type *)(0x40390140u))

/* TCPWM0_GRP2_CNT2_INTR */
#define OS_TCPWM0_GRP2_CNT2_INTR      (*(volatile OS_TCPWM_GRP_CNT_INTR_type *)(0x40390170u))

/* TCPWM0_GRP2_CNT2_INTR_MASK */
#define OS_TCPWM0_GRP2_CNT2_INTR_MASK (*(volatile OS_TCPWM_GRP_CNT_INTR_MASK_type *)(0x40390178u))

#if (OS_PROCESSOR_SERIES == CYT4BB)
/* TCPWM0_GRP2_CNT3_CTRL */
#define OS_TCPWM0_GRP2_CNT3_CTRL      (*(volatile OS_TCPWM_GRP_CNT_CTRL_type *)(0x40390180u))

/* TCPWM0_GRP2_CNT3_COUNTER */
#define OS_TCPWM0_GRP2_CNT3_COUNTER   (*(volatile uint32 *)(0x40390188u))

/* TCPWM0_GRP2_CNT3_PERIOD */
#define OS_TCPWM0_GRP2_CNT3_PERIOD    (*(volatile OS_TCPWM_GRP_CNT_PERIOD_type *)(0x403901A0u))

/* TCPWM0_GRP2_CNT3_TR_CMD */
#define OS_TCPWM0_GRP2_CNT3_TR_CMD    (*(volatile OS_TCPWM_GRP_CNT_TR_CMD_type *)(0x403901C0u))

/* TCPWM0_GRP2_CNT3_INTR */
#define OS_TCPWM0_GRP2_CNT3_INTR      (*(volatile OS_TCPWM_GRP_CNT_INTR_type *)(0x403901F0u))

/* TCPWM0_GRP2_CNT3_INTR_MASK */
#define OS_TCPWM0_GRP2_CNT3_INTR_MASK (*(volatile OS_TCPWM_GRP_CNT_INTR_MASK_type *)(0x403901F8u))

/* TCPWM0_GRP2_CNT4_CTRL */
#define OS_TCPWM0_GRP2_CNT4_CTRL      (*(volatile OS_TCPWM_GRP_CNT_CTRL_type *)(0x40390200u))

/* TCPWM0_GRP2_CNT4_COUNTER */
#define OS_TCPWM0_GRP2_CNT4_COUNTER   (*(volatile uint32 *)(0x40390208u))

/* TCPWM0_GRP2_CNT4_PERIOD */
#define OS_TCPWM0_GRP2_CNT4_PERIOD    (*(volatile OS_TCPWM_GRP_CNT_PERIOD_type *)(0x40390220u))

/* TCPWM0_GRP2_CNT4_TR_CMD */
#define OS_TCPWM0_GRP2_CNT4_TR_CMD    (*(volatile OS_TCPWM_GRP_CNT_TR_CMD_type *)(0x40390240u))

/* TCPWM0_GRP2_CNT4_INTR */
#define OS_TCPWM0_GRP2_CNT4_INTR      (*(volatile OS_TCPWM_GRP_CNT_INTR_type *)(0x40390270u))

/* TCPWM0_GRP2_CNT4_INTR_MASK */
#define OS_TCPWM0_GRP2_CNT4_INTR_MASK (*(volatile OS_TCPWM_GRP_CNT_INTR_MASK_type *)(0x40390278u))
#elif (OS_PROCESSOR_SERIES == CYT4BF)
/* TCPWM1_GRP2_CNT1_CTRL */
#define OS_TCPWM1_GRP2_CNT1_CTRL      (*(volatile OS_TCPWM_GRP_CNT_CTRL_type *)(0x40590080u))

/* TCPWM1_GRP2_CNT1_COUNTER */
#define OS_TCPWM1_GRP2_CNT1_COUNTER   (*(volatile uint32 *)(0x40590088u))

/* TCPWM1_GRP2_CNT1_PERIOD */
#define OS_TCPWM1_GRP2_CNT1_PERIOD    (*(volatile OS_TCPWM_GRP_CNT_PERIOD_type *)(0x405900A0u))

/* TCPWM1_GRP2_CNT1_TR_CMD */
#define OS_TCPWM1_GRP2_CNT1_TR_CMD    (*(volatile OS_TCPWM_GRP_CNT_TR_CMD_type *)(0x405900C0u))

/* TCPWM1_GRP2_CNT1_INTR */
#define OS_TCPWM1_GRP2_CNT1_INTR      (*(volatile OS_TCPWM_GRP_CNT_INTR_type *)(0x405900F0u))

/* TCPWM1_GRP2_CNT1_INTR_MASK */
#define OS_TCPWM1_GRP2_CNT1_INTR_MASK (*(volatile OS_TCPWM_GRP_CNT_INTR_MASK_type *)(0x405900F8u))

/* TCPWM1_GRP2_CNT2_CTRL */
#define OS_TCPWM1_GRP2_CNT2_CTRL      (*(volatile OS_TCPWM_GRP_CNT_CTRL_type *)(0x40590100u))

/* TCPWM1_GRP2_CNT2_COUNTER */
#define OS_TCPWM1_GRP2_CNT2_COUNTER   (*(volatile uint32 *)(0x40590108u))

/* TCPWM1_GRP2_CNT2_PERIOD */
#define OS_TCPWM1_GRP2_CNT2_PERIOD    (*(volatile OS_TCPWM_GRP_CNT_PERIOD_type *)(0x40590120u))

/* TCPWM1_GRP2_CNT2_TR_CMD */
#define OS_TCPWM1_GRP2_CNT2_TR_CMD    (*(volatile OS_TCPWM_GRP_CNT_TR_CMD_type *)(0x40590140u))

/* TCPWM1_GRP2_CNT2_INTR */
#define OS_TCPWM1_GRP2_CNT2_INTR      (*(volatile OS_TCPWM_GRP_CNT_INTR_type *)(0x40590170u))

/* TCPWM1_GRP2_CNT2_INTR_MASK */
#define OS_TCPWM1_GRP2_CNT2_INTR_MASK (*(volatile OS_TCPWM_GRP_CNT_INTR_MASK_type *)(0x40590178u))
#endif

/* Max counter value of TCPWM0_GRP2 and TCMWP1_GRP2 */
#define OS_TCPWM_N_GRP2_CNT_MAX        (0xFFFFFFFFu)

/*
 * SBC (System Control Block)
 */

/* Structure of HFSR (Hard Fault Status Register) register */
typedef volatile union
{
  struct
  {
    Os_Reg32                : 1;
    Os_Reg32 VECTTBL        : 1;
    Os_Reg32                : 28;
    Os_Reg32 FORCED         : 1;
    Os_Reg32 DEBUGEVT       : 1;
  } B;
  sint32 I;
  uint32 U;
} OS_SBC_HFSR_type;

/* HFSR register */
#define OS_SBC_HFSR          (*(volatile OS_SBC_HFSR_type *)(0xE000ED2Cu))

/* Structure of CFSR (Configurable Fault Status Register) register */
typedef volatile union
{
  struct
  {
    Os_Reg32 MemManage      : 8;  /* MemManage */
    Os_Reg32 BusFault       : 8;  /* BusFault */
    Os_Reg32 UsageFault     : 16; /* UsageFault */
  } B;
  sint32 I;
  uint32 U;
} OS_SBC_CFSR_type;

/* CFSR register */
#define OS_SBC_CFSR          (*(volatile OS_SBC_CFSR_type *)(0xE000ED28u))

/* Mask for MMFSR error bit */
#define OS_MMFSR_ERROR_MASK  0x3Fu

/* Mask for MMFSR valid bit */
#define OS_MMFSR_VALID_MASK  0x80u

/* MMFAR register */
#define OS_SBC_MMFAR        (*(volatile uint32 *) 0xE000ED34u)

/* Mask for BFSR error bit */
#define OS_BFSR_ERROR_MASK   0x3Fu

/* Mask for BFSR valid bit */
#define OS_BFSR_VALID_MASK   0x80u

/* BFAR register */
#define OS_SBC_BFAR         (*(volatile uint32 *) 0xE000ED38u)


/** Address of the System Handler Priority Register 3 */
#define OS_SHPR3_ADDR   ((volatile uint32 *)0xE000ED20u)

/* Structure of CCR (Configuration and Control Register) register */
typedef volatile union
{
  struct
  {
    Os_Reg32 NONBASETHRDENA      : 1;  /* NONBASETHRDENA */
    Os_Reg32 USERSETMPEND        : 1;  /* USERSETMPEND */
    Os_Reg32                     : 1;  /* Reserved */
    Os_Reg32 UNALIGN_TRP         : 1;  /* UNALIGN_TRP */
    Os_Reg32 DIV_0_TRP           : 1;  /* DIV_0_TRP */
    Os_Reg32                     : 3;  /* Reserved */
    Os_Reg32 BFHFNMIGN           : 1;  /* BFHFNMIGN */
    Os_Reg32 STKALIGN            : 1;  /* STKALIGN */
    Os_Reg32                     : 6;  /* Reserved */
    Os_Reg32 DC                  : 1;  /* DC */
    Os_Reg32 IC                  : 1;  /* IC */
    Os_Reg32 BP                  : 1;  /* BP */
    Os_Reg32                     : 13; /* Reserved */
  } B;
  sint32 I;
  uint32 U;
} OS_SCB_CCR_type;

/* CFSR register */
#define OS_SCB_CCR          (*(volatile OS_SCB_CCR_type *)(0xE000ED14u))

/* Structure of AIRCR (Application Interrupt and Reset Control Register) register */
typedef volatile union
{
  struct
  {
    Os_Reg32 VECTRESET           : 1;  /* VECTRESET */
    Os_Reg32 VECTCLRACTIVE       : 1;  /* VECTCLRACTIVE */
    Os_Reg32 SYSRESETREQ         : 1;  /* SYSRESETREQ */
    Os_Reg32                     : 5;  /* Reserved */
    Os_Reg32 PRIGROUP            : 3;  /* PRIGROUP */
    Os_Reg32                     : 4;  /* Reserved */
    Os_Reg32 ENDIANNESS          : 1;  /* ENDIANNESS */
    Os_Reg32 VECTKEY             : 16; /* VECTKEY */
  } B;
  sint32 I;
  uint32 U;
} OS_SCB_AIRCR_type;

/* CFSR register */
#define OS_SCB_AIRCR       (*(volatile OS_SCB_AIRCR_type *)(0xE000ED0Cu))

/*
 * SYSTICK (The System Timer)
 */

/** Structure of SysTick Control and Status Register */
typedef volatile struct
{
  Os_Reg32 ENABLE         : 1;  /**< Enables the counter */
  Os_Reg32 TICKINT        : 1;  /**< Enables SysTick exception request */
  Os_Reg32 CLKSOURCE      : 1;  /**< Indicates the clock source:
                                     0 = external clock, 1 = processor clock */
  Os_Reg32 reserved1      : 13;
  Os_Reg32 COUNTFLAG      : 1;  /**< Returns 1 if timer counted to 0
                                     since last time this was read */
  Os_Reg32 reserved2      : 15;
} OS_SYST_CSR_type;

/** SysTick Control and Status Register */
#define OS_SYST_CSR     (*(volatile OS_SYST_CSR_type *)0xE000E010u)
/** Processor clock value of the SYST_CSR */
#define OS_SYST_CSR_CLKSOURCE_PROCESSOR     (1u)

/** SysTick Reload Value Register(Valid only 24bit) */
#define OS_SYST_RVR     (*(volatile uint32 *)0xE000E014u)

/** SysTick Current Value Register(Valid only 24bit) */
#define OS_SYST_CVR     (*(volatile uint32 *)0xE000E018u)

/*
 * IPC (Inter Process Communication)
 */

/* Structure of IPC_STRUCT_ACQUIRE register */
typedef volatile union
{
  struct
  {
    Os_Reg32 P              :1;
    Os_Reg32 NS             :1;
    Os_Reg32                :2;
    Os_Reg32 PC             :4;
    Os_Reg32 MS             :4;
    Os_Reg32                :19;
    Os_Reg32 SUCCESS        :1;
  } B;
  sint32 I;
  uint32 U;
} OS_IPC_STRUCT_ACQUIRE_type;

/* Structure of IPC_STRUCT_RELEASE register */
typedef volatile union
{
  struct
  {
    Os_Reg32 INTR_RELEASE   :16;
    Os_Reg32                :16;
  } B;
  sint32 I;
  uint32 U;
} OS_IPC_STRUCT_RELEASE_type;

/* Structure of IPC_STRUCT_NOTIFY register */
typedef volatile union
{
  struct{
    Os_Reg32 INTR_NOTIFY    :16;
    Os_Reg32                :16;
  } B;
  sint32 I;
  uint32 U;
} OS_IPC_STRUCT_NOTIFY_type;

/* Structure of IPC_STRUCT_DATA0 register */
typedef volatile union
{
  struct{
    Os_Reg32 DATA           :32;
  } B;
  sint32 I;
  uint32 U;
} OS_IPC_STRUCT_DATA0_type;

/* Structure of IPC_STRUCT_DATA1 register */
typedef volatile union
{
  struct{
    Os_Reg32 DATA           :32;
  } B;
  sint32 I;
  uint32 U;
} OS_IPC_STRUCT_DATA1_type;

/* Structure of IPC_STRUCT_LOCK_STATUS register */
typedef volatile union
{
  struct
  {
    Os_Reg32 P              :1;
    Os_Reg32 NS             :1;
    Os_Reg32                :2;
    Os_Reg32 PC             :4;
    Os_Reg32 MS             :4;
    Os_Reg32                :19;
    Os_Reg32 ACQUIRED       :1;
  } B;
  sint32 I;
  uint32 U;
} OS_IPC_STRUCT_LOCK_STATUS_type;

/* Structure of IPC_STRUCT register */
typedef struct
{
  OS_IPC_STRUCT_ACQUIRE_type       ACQUIRE;          /*!< 0x00000000 IPC acquire */
  OS_IPC_STRUCT_RELEASE_type       RELEASE;          /*!< 0x00000004 IPC release */
  OS_IPC_STRUCT_NOTIFY_type        NOTIFY;           /*!< 0x00000008 IPC notification */
  OS_IPC_STRUCT_DATA0_type         DATA0;            /*!< 0x0000000C IPC data 0 */
  OS_IPC_STRUCT_DATA1_type         DATA1;            /*!< 0x00000010 IPC data 1 */
  Os_Reg32                         Reserved[2];
  OS_IPC_STRUCT_LOCK_STATUS_type   LOCK_STATUS;      /*!< 0x0000001C IPC lock status */
} OS_IPC_STRUCT_type;


/* Structure of IPC_INTR_STRUCT_INTR register */
typedef volatile union
{
  struct{
    Os_Reg32 RELEASE        :16;
    Os_Reg32 NOTIFY         :16;
  } B;
  sint32 I;
  uint32 U;
} OS_IPC_INTR_STRUCT_INTR_type;

/* Structure of IPC_INTR_STRUCT_INTR_SET register */
typedef volatile union{
  struct
  {
    Os_Reg32 RELEASE        :16;
    Os_Reg32 NOTIFY         :16;
  } B;
  sint32 I;
  uint32 U;
} OS_IPC_INTR_STRUCT_INTR_SET_type;

/* Structure of IPC_INTR_STRUCT_INTR_MASK register */
typedef volatile union
{
  struct
  {
    Os_Reg32 RELEASE        :16;
    Os_Reg32 NOTIFY         :16;
  } B;
  sint32 I;
  uint32 U;
} OS_IPC_INTR_STRUCT_INTR_MASK_type;

/* Structure of IPC_INTR_STRUCT_INTR_MASKED register */
typedef volatile union
{
  struct
  {
    Os_Reg32 RELEASE        :16;
    Os_Reg32 NOTIFY         :16;
  } B;
  sint32 I;
  uint32 U;
} OS_IPC_INTR_STRUCT_INTR_MASKED_type;

/* Structure of IPC_INTR_STRUCT register */
typedef struct
{
  OS_IPC_INTR_STRUCT_INTR_type        INTR;             /*!< 0x00000000 Interrupt */
  OS_IPC_INTR_STRUCT_INTR_SET_type    INTR_SET;         /*!< 0x00000004 Interrupt set */
  OS_IPC_INTR_STRUCT_INTR_MASK_type   INTR_MASK;        /*!< 0x00000008 Interrupt mask */
  OS_IPC_INTR_STRUCT_INTR_MASKED_type INTR_MASKED;      /*!< 0x0000000C Interrupt masked */
  Os_Reg32                            Reserved[4];
} OS_IPC_INTR_STRUCT_type;                               /*!< Size = 32 (0x20) */


/* Structure of IPC register */
typedef struct
{
  OS_IPC_STRUCT_type              STRUCT[16];         /*!< 0x00000000 IPC structure */
  Os_Reg32                        Reserved[896];
  OS_IPC_INTR_STRUCT_type         INTR_STRUCT[16];    /*!< 0x00001000 IPC interrupt structure */
} OS_IPC_type;                                           /*!< Size = 4608 (0x1200) */

/* IPC Base Address */
#define IPC_BASE        0x40220000UL

/* IPC Register expressed as address */
#define OS_IPC_ADDR     ((volatile OS_IPC_type*)IPC_BASE)

/* IPC Register expressed as pointer */
#define OS_IPC_REG      (*(volatile OS_IPC_type*)IPC_BASE)

/*
 * CPUSS (CPU subsystem)
 */
/* Structure of CPUSS_CM7_1_PWR_CTL register */
typedef volatile union
{
  struct
  {
    Os_Reg32 PWR_MODE       :2;
    Os_Reg32                :14;
    Os_Reg32 VECTKEYSTAT    :16;
  } B;
  sint32 I;
  uint32 U;
} OS_CPUSS_CM7_1_PWR_CTL_type;

#define OS_CPUSS_CM7_1_PWR_CTL       (*(volatile OS_CPUSS_CM7_1_PWR_CTL_type *) 0x40201210u)

/* Structure of CPUSS_CM7_1_VECTOR_TABLE_BASE register */
typedef volatile union
{
  struct
  {
    Os_Reg32                :7;
    Os_Reg32 ADDR25         :25;
  } B;
  sint32 I;
  uint32 U;
} OS_CPUSS_CM7_1_VECTOR_TABLE_BASE_type;

/* CM7_1_VECTOR_TABLE_BASE Register */
#define OS_CPUSS_CM7_1_VECTOR_TABLE_BASE (*(volatile OS_CPUSS_CM7_1_VECTOR_TABLE_BASE_type *) 0x40200600u)

/* Structure of CPUSS_CM7_1_CTL register */
typedef volatile union
{
  struct
  {
    Os_Reg32 PPB_LOCK           :4;
    Os_Reg32 CPU_WAIT           :1;
    Os_Reg32                    :3;
    Os_Reg32 INIT_TCM_EN        :2;
    Os_Reg32 INIT_RMW_EN        :2;
    Os_Reg32                    :4;
    Os_Reg32 ITCM_ECC_EN        :1;
    Os_Reg32 ITCM_ECC_INJ_EN    :1;
    Os_Reg32 ITCM_READ_WS       :1;
    Os_Reg32 ITCM_ECC_CHECK_DIS :1;
    Os_Reg32 DTCM_ECC_EN        :1;
    Os_Reg32 DTCM_ECC_INJ_EN    :1;
    Os_Reg32 DTCM_READ_WS       :1;
    Os_Reg32 TCMC_EN            :1;
    Os_Reg32 IOC_MASK           :1;
    Os_Reg32 DZC_MASK           :1;
    Os_Reg32 OFC_MASK           :1;
    Os_Reg32 UFC_MASK           :1;
    Os_Reg32 IXC_MASK           :1;
    Os_Reg32                    :2;
    Os_Reg32 IDC_MASK           :1;
  } B;
  sint32 I;
  uint32 U;
} OS_CPUSS_CM7_1_CTL_type;

/* CM7_1_CTL Register */
#define OS_CPUSS_CM7_1_CTL           (*(volatile OS_CPUSS_CM7_1_CTL_type *) 0x4020040Cu)

#endif /* OS_ARCH_REGS_H_ */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA-C3:11.4 */
/* polyspace-end MISRA-C3:19.2 */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
