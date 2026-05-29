/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Opf_Port.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : OS Profiler                                                   **
**                                                                            **
**  PURPOSE   : Type definition for OS Profiler                               **
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
** 1.5.0     31-Oct-2019    YH.Han        Redmine #19291                      **
** 1.4.0     23-May-2019    YH.Han        Redmine #17493                      **
** 1.3.0     29-Oct-2018    YH.Han        Redmine #12853                      **
** 1.2.0     09-Mar-2018    YH.Han        Redmine #11169                      **
** 1.1.2     22-Aug-2017    MJ.Woo        Redmine #6959                       **
** 1.1.0     30-Nov-2016    SH.Yoo        Redmine #6755, #6816                **
** 1.0.3     28-Oct-2016    SH.Yoo        Redmine #6253                       **
** 1.0.0     14-Jul-2016    SH.Yoo        Redmine #4024                       **
*******************************************************************************/

#ifndef OPF_PORT_H
#define OPF_PORT_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Opf_Types.h"
#include "Opf_Port_Types.h"
#include "Opf_TimeService.h"
#include "Opf_Cfg.h"
#if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
#include "Os_task_internal_types.h"
#include "Os_Platform_timers.h"
#include "Os_alarm_internal_types.h"
#include "Os_internal_api.h"
#elif (OPF_TARGET_OS == OPF_RENESAS_RH850)
#include "Os.h"
#include "Os_rh850_sit.h"
#include "Os_data.h"
#elif (OPF_TARGET_OS == OPF_AUTRON_COMMON)
#include "Os_ErrorExternal.h"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
/** Current STM count value */
#define OPF_STM_TICK                     OSSTM_CNT
/** Max STM count value */
#define OPF_MAX_STM_TICK                 0xFFFFFFFFu
/** 16Mhz IRCOSC  */
#define OPF_BACKUP_CLOCK                 16u
/** 16 MHz IRCOSC */
#define OPF_SYSCLK_IRCOSC                0u
/** div 16 MHz IRCOSC */
#define OPF_SYSCLK_IRCOSC_DIV            1u
/** 4-16 MHz XOSC */
#define OPF_SYSCLK_XOSC                  2u
/** div 4-16 MHz XOSC */
#define OPF_SYSCLK_XOSC_DIV              3u
/** PLL PHI */
#define OPF_SYSCLK_PLL                   4u
/** PLL input division factor value : Clock Inhibit */
#define OPF_PLLCLOCK_INHIBIT             0xFu
/** PLL MAX divide ratio */
#define OPF_PLLCLOCK_DIV_MAX             96u
/** PLL MIN divide ratio */
#define OPF_PLLCLOCK_DIV_MIN             32u

/** FIRC Oscillator Control Register type definition. */
typedef volatile union
{
  struct
  {
    uint32 RSVD0          :10;
    uint32 FIRCTRIM       : 6;  /**< FIRC trimming bits */
    uint32 RSVD1          : 3;
    uint32 FIRCDIV        : 5;  /**< FIRC clock division factor */
    uint32 RSVD2          : 2;
    uint32 FIRCON_STDBY   : 1;  /**< FIRC control in STANDBY mode */
    uint32 RSVD3          : 5;
  } B;
  sint32 I;
  uint32 U;

} OPF_FIRC_CTL_type;
/** Frequency-modulated phase-locked loop Control Register */
#define OPF_FIRC_CTL  (*(OPF_FIRC_CTL_type *)(0xC3FE0060u))

/** Fast External Crystal Oscillator Control Register type definition. */
typedef volatile union
{
  struct
  {
    uint32 OSCBYP         : 1;  /**< Crystal Oscillator bypass */
    uint32 RSVD0          : 7;
    uint32 EOCV           : 8;  /**< End of Count Value */
    uint32 M_OSC          : 1;  /**< Crystal oscillator clock interrupt mask */
    uint32 RSVD1          : 2;
    uint32 OSCDIV         : 5;  /**< Crystal oscillator clock division factor */
    uint32 I_OSC          : 1;  /**< Crystal oscillator clock interrupt */
    uint32 RSVD2          : 5;
  } B;
  sint32 I;
  uint32 U;

} OPF_FXOSC_CTL_type;
/** Frequency-modulated phase-locked loop Control Register */
#define OPF_FXOSC_CTL  (*(OPF_FXOSC_CTL_type *)(0xC3FE0000u))

/** FMPLL Control Register type definition. */
typedef volatile union
{
  struct
  {
    uint32 RSVD0          : 2;
    uint32 IDF            : 4;  /**< FMPLL Input Division Factor */
    uint32 ODF            : 2;  /**< FMPLL Output Division Factor */
    uint32 RSVD1          : 1;
    uint32 NDIV           : 7;  /**< FMPLL loop Division Factor */
    uint32 RSVD2          : 7;
    uint32 EN_PLL_SW      : 1;  /**< Enable progressive clock switching */
    uint32 RSVD3          : 1;
    uint32 UNLOCK_ONCE    : 1;  /**< FMPLL loss of lock condition */
    uint32 RSVD4          : 1;
    uint32 I_LOCK         : 1;  /**< There is a lock/unlock event */
    uint32 S_LOCK         : 1;  /**< FMPLL has acquired lock */
    uint32 PLL_FAIL_MASK  : 1;  /**< pll_fail output mask */
    uint32 PLL_FAIL_FLAG  : 1;  /**< loss of lock event occurs
                                           while FMPLL is switched on */
    uint32 RSVD5          : 1;
  } B;
  sint32 I;
  uint32 U;

} OPF_FMPLL_CR_type;

/** Frequency-modulated phase-locked loop Control Register */
#define OPF_FMPLL_CR  (*(OPF_FMPLL_CR_type *)(0xC3FE00A0u))

/** System Timer Module base address */
#define OPF_STM_BASE_ADDR  0xFFF3C000u

/** STM Control Register type definition. */
typedef volatile union
{
  struct
  {
    uint32 RSVD0          :16;
    uint32 CPS            : 8;  /**< Counter Prescaler. */
    uint32 RSVD1          : 6;
    uint32 FRZ            : 1;  /**< Freeze. */
    uint32 TEN            : 1;  /**< Timer counter Enabled. */
  } B;
  sint32 I;
  uint32 U;

} OPF_STM_CR_type;
/** STM Control Register */
#define OPF_STM_CR         (*(OPF_STM_CR_type *)(OPF_STM_BASE_ADDR + 0x00u))

/** Clock Generation Module base address */
#define OPF_MC_CGM_BASE_ADDR 0xC3FE0370u

/** System Clock Select Status Register type definition. */
typedef volatile union
{
  struct
  {
    uint32 RSVD0          : 4;
    uint32 SELSTAT        : 4;  /**< System Clock Source
                                           Selection Status */
    uint32 RSVD1          :24;
  } B;
  sint32 I;
  uint32 U;

} OPF_MC_CGM_SC_SS_type;
/** System Clock Select Status Register */
#define OPF_MC_CGM_SC_SS   (*(OPF_MC_CGM_SC_SS_type *)(OPF_MC_CGM_BASE_ADDR \
                                                                     + 0x0008u))

#elif (OPF_TARGET_OS == OPF_RENESAS_RH850)

/** High Speed Internal Oscillator - 8Mhz */
#define OPF_INTOSC_CLOCK                                           8u

/** Internal OSC */
#define OPF_CPUCLKS_INTOSC               1u
/** Main OSC */
#define OPF_CPUCLKS_MAINOSC              2u
/** PLL */
#define OPF_CPUCLKS_CPPLL                3u
/** CPUCLK2 (IPERI1's source clock) */
#define OPF_IPERI1SCLKS_CPUCLK2          1u
/** PPLLCLK (IPERI1's source clock) */
#define OPF_IPERI1SCLKS_PPLLCLK          2u
/** PLL active */
#define OPF_PLL_ACTIVE                   1u
/** PLL inactive */
#define OPF_PLL_INACTIVE                 0u
/** Minimum M divider */
#define OPF_PLLCLOCK_MDIV_MIN            0u
/** Maximum M divider */
#define OPF_PLLCLOCK_MDIV_MAX            2u

/** PLL PAR divider value 4 */
#define OPF_PLLC_PA_4                    4u
/** PLL PAR divider value 6 */
#define OPF_PLLC_PA_6                    6u
/** PLL PAR divider value 8 */
#define OPF_PLLC_PA_8                    8u
/** PLL PAR divider value 16 */
#define OPF_PLLC_PA_16                   16u

/** CKSC_IPERI1S_CTL - C_ISO_PERI1 source clock selection register */
typedef volatile union
{
  struct
  {
    uint32 IPERI1SCSID  : 2;
    uint32 RVSD         : 30;
  } B;
  sint32 I;
  uint32 U;
} OPF_CKSC_IPERI1S_CTL_type;

#define OPF_CKSC_IPERI1S_CTL    (*(OPF_CKSC_IPERI1S_CTL_type *)(0xFFF8A200u))

/** CKSC_IPERI1S_ACT - C_ISO_PERI1 source clock active register */
typedef volatile union
{
  struct
  {
    uint32 IPERI1SACT   : 2;
    uint32 RVSD         : 30;
  } B;
  sint32 I;
  uint32 U;
} OPF_CKSC_IPERI1S_ACT_type;

#define OPF_CKSC_IPERI1S_ACT    (*(OPF_CKSC_IPERI1S_ACT_type *)(0xFFF8A208u))

/** CKSC_CPUCLKS_CTL - C_ISO_CPUCLK source clock selection register */
typedef volatile union
{
  struct
  {
    uint32 CPUCLKSCSID  : 2;
    uint32 RVSD         : 30;
  } B;
  sint32 I;
  uint32 U;
} OPF_CKSC_CPUCLKS_CTL_type;

#define OPF_CKSC_CPUCLKS_CTL    (*(OPF_CKSC_CPUCLKS_CTL_type *)(0xFFF8A000u))

/** CKSC_CPUCLKS_ACK - C_ISO_CPUCLK source clock active register */
typedef volatile union
{
  struct
  {
    uint32 CPUCLKSACT   : 2;
    uint32 RVSD         : 30;
  } B;
  sint32 I;
  uint32 U;
} OPF_CKSC_CPUCLKS_ACT_type;

#define OPF_CKSC_CPUCLKS_ACT    (*(OPF_CKSC_CPUCLKS_ACT_type *)(0xFFF8A008u))

/** CKSC_CPUCLKD_CTL - C_ISO_CPUCLK clock divider register */
typedef volatile union
{
  struct
  {
    uint32 CPUCLKDCSID  : 3;
    uint32 RVSD         : 29;
  } B;
  sint32 I;
  uint32 U;
} OPF_CKSC_CPUCLKD_CTL_type;

#define OPF_CKSC_CPUCLKD_CTL    (*(OPF_CKSC_CPUCLKD_CTL_type *)(0xFFF8A100u))

/** CKSC_CPUCLKD_ACT - C_ISO_CPUCLK clock divider active register */
typedef volatile union
{
  struct
  {
    uint32 CPUCLKDACT   : 3;
    uint32 RVSD         : 29;
  } B;
  sint32 I;
  uint32 U;
} OPF_CKSC_CPUCLKD_ACT_type;

#define OPF_CKSC_CPUCLKD_ACT    (*(OPF_CKSC_CPUCLKD_ACT_type *)(0xFFF8A108u))

/** PLLC - PLL control register */
typedef volatile union
{
  struct
  {
    uint32 N            : 6;
    uint32 RVSD0        : 2;
    uint32 PA           : 3;
    uint32 M            : 2;
    uint32 RVSD1        : 19;
  } B;
  sint32 I;
  uint32 U;
} OPF_PLLC_type;

#define OPF_PLLC                (*(OPF_PLLC_type *)(0xFFF89008u))

/** PLLS - PLL status register */
typedef volatile union
{
  struct
  {
    uint32 RVSD0        : 2;
    uint32 PLLCLKACT    : 1;
    uint32 RVSD1        : 29;
  } B;
  sint32 I;
  uint32 U;
} OPF_PLLS_type;

#define OPF_PLLS                (*(OPF_PLLS_type *)(0xFFF89004u))




/** TAUJ1 channel */
#define OPF_TAUJ1_CHANNEL   3

/** TAUJ1 base address */
#define TAUJ1_BASE_ADDR    0xFFE51000ul

/** TAUJ1 channel counter register */
#if (OPF_TAUJ1_CHANNEL == 0)
#define OPF_TAUJ1_CNTX     (*(uint32 *)(TAUJ1_BASE_ADDR+0x10u))
#elif (OPF_TAUJ1_CHANNEL == 1)
#define OPF_TAUJ1_CNTX     (*(uint32 *)(TAUJ1_BASE_ADDR+0x14u))
#elif (OPF_TAUJ1_CHANNEL == 2)
#define OPF_TAUJ1_CNTX     (*(uint32 *)(TAUJ1_BASE_ADDR+0x18u))
#elif (OPF_TAUJ1_CHANNEL == 3)
#define OPF_TAUJ1_CNTX     (*(uint32 *)(TAUJ1_BASE_ADDR+0x1Cu))
#endif

/** TAUJ1 channel mode OS register */
typedef volatile union
{
  struct
  {
    uint32 TAUJnCKS          : 2;
    uint32 TAUJnCCS          : 2;
    uint32 TAUJnMAS          : 1;
    uint32 TAUJnSTS          : 3;
    uint32 TAUJnCOS          : 2;
    uint32 RVSD              : 1;
    uint32 TAUJnMD           : 5;
  } B;
  sint16 I;
  uint16 U;
} OPF_TAUJ_CMOR_type;

#if (OPF_TAUJ1_CHANNEL == 0)
#define OPF_TAUJ1_CMORX     (*(OPF_TAUJ_CMOR_type *)(TAUJ1_BASE_ADDR+0x80u))
#elif (OPF_TAUJ1_CHANNEL == 1)
#define OPF_TAUJ1_CMORX     (*(OPF_TAUJ_CMOR_type *)(TAUJ1_BASE_ADDR+0x84u))
#elif (OPF_TAUJ1_CHANNEL == 2)
#define OPF_TAUJ1_CMORX     (*(OPF_TAUJ_CMOR_type *)(TAUJ1_BASE_ADDR+0x88u))
#elif (OPF_TAUJ1_CHANNEL == 3)
#define OPF_TAUJ1_CMORX     (*(OPF_TAUJ_CMOR_type *)(TAUJ1_BASE_ADDR+0x8Cu))
#endif

/** TAUJ1 channel mode user register */
#if (OPF_TAUJ1_CHANNEL == 0)
#define OPF_TAUJ1_CMURX	   (*(uint16 *)(TAUJ1_BASE_ADDR+0x20u))
#elif (OPF_TAUJ1_CHANNEL == 1)
#define OPF_TAUJ1_CMURX     (*(uint16 *)(TAUJ1_BASE_ADDR+0x24u))
#elif (OPF_TAUJ1_CHANNEL == 2)
#define OPF_TAUJ1_CMURX     (*(uint16 *)(TAUJ1_BASE_ADDR+0x28u))
#elif (OPF_TAUJ1_CHANNEL == 3)
#define OPF_TAUJ1_CMURX     (*(uint16 *)(TAUJ1_BASE_ADDR+0x2Cu))
#endif

/** TAUJ1 channel start trigger register */
typedef volatile union
{
  struct
  {
    uint32 TAUJnTS00         : 1;
    uint32 TAUJnTS01         : 1;
    uint32 TAUJnTS02         : 1;
    uint32 TAUJnTS03         : 1;
    uint32 RVSD              : 4;
  } B;
  sint32 I;
  uint32 U;
} OPF_TAUJ_CHANNEL_START_type;

#define OPF_TAUJ1_TS    (*(OPF_TAUJ_CHANNEL_START_type *)(TAUJ1_BASE_ADDR+0x54u))

#if (OPF_TAUJ1_CHANNEL == 0)
#define OPF_TAUJ1_TSXX    OPF_TAUJ1_TS.B.TAUJnTS00
#elif (OPF_TAUJ1_CHANNEL == 1)
#define OPF_TAUJ1_TSXX    OPF_TAUJ1_TS.B.TAUJnTS01
#elif (OPF_TAUJ1_CHANNEL == 2)
#define OPF_TAUJ1_TSXX    OPF_TAUJ1_TS.B.TAUJnTS02
#elif (OPF_TAUJ1_CHANNEL == 3)
#define OPF_TAUJ1_TSXX    OPF_TAUJ1_TS.B.TAUJnTS03
#endif

/** Current STM count value */
#define OPF_STM_TICK                     OPF_TAUJ1_CNTX
/** Current STM clock */
#define OPF_STM_CLOCK                    1000u
/** Max STM count value */
#define OPF_MAX_STM_TICK                 0xFFFFFFFFu
/** Max Task Priority */
#define OPF_MAX_TASK_PRIORITY            31u

#elif (OPF_TARGET_OS == OPF_AUTRON_COMMON)
/* do nothing */
#endif /* #if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB) */

#if (OPF_MULTICORE_ENABLED == STD_ON)
#define OPF_GET_EVENTQ_INFO(CoreId) Opf_GddEventQInfo[CoreId]
#define OPF_GET_PROFILE_EVENTQ_INFO(CoreId) Opf_GddProfileEventQInfo[CoreId]
#define OPF_GET_OS_PROFILER_INFO(CoreId) Opf_GddOsProfilerInfo[CoreId]
#define OPF_GET_INDEX_TICKS_INFO(CoreId) Opf_GulIndexTicksInfo[CoreId]
#define OPF_GET_SYS_TIME_SPAN_INFO(CoreId) Opf_GddSystimeSpanInfo[CoreId]
#define OPF_GET_SYS_TIME_TICK_INFO(CoreId) Opf_GddSystimeTickInfo[CoreId]
#endif

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
extern FUNC(void, OPF_CODE) Opf_PortUpdateAlarmTask(TaskID);
#endif

#if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
extern FUNC(OpfTaskIDType, OPF_CODE) Opf_PortGetObjID(uint16 ObjID);
#elif (OPF_TARGET_OS == OPF_RENESAS_RH850)
extern FUNC(OpfTaskIDType, OPF_CODE) Opf_PortGetObjID(uint16 ObjID);
#elif (OPF_TARGET_OS == OPF_AUTRON_COMMON)
extern FUNC(OpfTaskIDType, OPF_CODE) Opf_PortGetObjID(uint16 ObjID);
#endif

extern FUNC(uint32, OPF_CODE) OPF_MS_TO_TICKS(uint32 MSEC);
extern FUNC(boolean, OPF_CODE) OPF_ISVALID_TASK(OpfTaskIDType TaskID);
extern FUNC(TaskType, OPF_CODE) Opf_PortGetTaskID(void);
/* polyspace-begin MISRA-C3:D4.5 [Not a Defect] "variable is not in same name space" */
extern FUNC(OpfStateType, OPF_CODE) Opf_PortGetTaskState\
                                                    (OpfObjectIDType LddTaskID);
/* polyspace-end MISRA-C3:D4.5 */
extern FUNC(void, OPF_CODE) Opf_PortProcessPreIsr(void);
extern FUNC(void, OPF_CODE) Opf_PortProcessPostIsr(void);
extern FUNC(void, OPF_CODE) Opf_PortProcessPreCntIsr(void);
extern FUNC(void, OPF_CODE) Opf_PortProcessPostCntIsr(void);
extern FUNC(void, OPF_CODE) Opf_PortProcessPreTask(void);
extern FUNC(void, OPF_CODE) Opf_PortProcessPostTask(void);
extern FUNC(void, OPF_CODE) Opf_PortProcessLimitError(void);
extern FUNC(uint32, OS_CODE) Opf_PortGetStmClock(void);

#if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
extern FUNC(OpfBool, OPF_CODE) Opf_IsNewTask(TaskType LucIdx);
extern FUNC(OpfBool, OPF_CODE) Opf_IsNoSuspendedTask(TaskType LucIdx);
extern FUNC(OpfBool, OPF_CODE) Opf_IsAlarmTask(TaskType LucIdx);
#endif

#endif /* OPF_PORT_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
