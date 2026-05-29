/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  FILE-NAME : EcuM_Callout.c                                                **
**                                                                            **
**  TARGET    : CYTxxx                                                        **
**                                                                            **
**  PRODUCT   : AUTOSAR EcuM Module                                           **
**                                                                            **
**  PURPOSE   :  Callouts implementation for EcuM module                      **
**               EcuM_AL_DriverInitZero                                       **
**               EcuM_AL_DriverInitOne                                        **
**               EcuM_AL_DriverRestart                                        **
**               EcuM_AL_SetProgrammableInterrupts                            **
**               EcuM_OnGoOffOne                                              **
**               EcuM_OnGoOffTwo                                              **
**               EcuM_AL_SwitchOff                                            **
**               EcuM_AL_Reset                                                **
**               EcuM_EnableWakeupSources                                     **
**               EcuM_DisableWakeupSources                                    **
**               EcuM_CheckWakeup                                             **
**               EcuM_StartWakeupSources                                      **
**               EcuM_StopWakeupSources                                       **
**               EcuM_CheckValidation                                         **
**               EcuM_GenerateRamHash                                         **
**               EcuM_SleepActivity                                           **
**               EcuM_CheckRamHash                                            **
**               EcuM_DeterminePbConfiguration                                **
**               EcuM_ErrorHook                                               **
**               EcuM_LoopDetection                                           **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                              Revision History                              **
********************************************************************************
** Revision   Date          By            Description                         **
********************************************************************************
** 2.5.9      25-Oct-2021   Junho Cho     #32580, #32615, #32730              **
** 2.5.8      15-Sep-2021   Junho Cho     #32188                              **
** 2.5.6      06-May-2021   Junho Cho     #29661                              **
** 2.5.4      08-Jan-2021   Manje Woo     #27588, #27589                      **
** 2.5.2      24-Nov-2020   Manje Woo     #26677                              **
** 2.4.0      02-Dec-2019   Junho Cho     Initial version                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:11.4 [Justified:Low] "Required to access MCU registers" */
/* polyspace-begin MISRA2012:20.1 [Justified:Low] "See MEMMAP003 of AUTOSAR" */
/* polyspace-begin MISRA2012:D4.5 [Justified:Low] "This code reviewed manually" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM.h"
#include "EcuM_Config.h"
#include "EcuM_Cbk.h"    /* ECU State Manager Callout-Callback Header File */
#include "EcuM_Generated_Callouts.h"
#include "EcuM_Ram.h"
#include "BswM_EcuM.h"
#include "Mcu.h"
#include "SchM_EcuM.h"
#include "Rte_EcuM.h"

#if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
#include "Os.h"
#endif

#if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
#include "Gpt.h"
#endif
#include "HwResource.h"
#include "arm_ghs.h"

#include "Slpwup_Callouts.h"

#if (ECUM_LP_CALLOUT_ENABLED == STD_ON)
#include "LowPower_Callout.h"
#endif

#if (SWP_USE_DATALOG == STD_ON)
#include "CDD_DataLog.h"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)
#define ECUM_SCB_CCR_IC_Pos                      17U                                           /*!< SCB CCR: Instruction cache enable bit Position */
#define ECUM_SCB_CCR_IC_Msk                     (1UL << ECUM_SCB_CCR_IC_Pos)                   /*!< SCB CCR: Instruction cache enable bit Mask */

/**
  \brief  Structure type to access the System Control Block (SCB).
 */
typedef struct
{
  uint32 ECUM_CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  uint32 ECUM_ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  uint32 ECUM_VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  uint32 ECUM_AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  uint32 ECUM_SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  uint32 ECUM_CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  uint8  ECUM_SHPR[12U];              /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  uint32 ECUM_SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  uint32 ECUM_CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  uint32 ECUM_HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  uint32 ECUM_DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  uint32 ECUM_MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  uint32 ECUM_BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  uint32 ECUM_AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  uint32 ECUM_ID_PFR[2U];             /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  uint32 ECUM_ID_DFR;                 /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  uint32 ECUM_ID_AFR;                 /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  uint32 ECUM_ID_MFR[4U];             /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  uint32 ECUM_ID_ISAR[5U];            /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
  uint32 ECUM_RESERVED0[1U];
  uint32 ECUM_CLIDR;                  /*!< Offset: 0x078 (R/ )  Cache Level ID register */
  uint32 ECUM_CTR;                    /*!< Offset: 0x07C (R/ )  Cache Type register */
  uint32 ECUM_CCSIDR;                 /*!< Offset: 0x080 (R/ )  Cache Size ID Register */
  uint32 ECUM_CSSELR;                 /*!< Offset: 0x084 (R/W)  Cache Size Selection Register */
  uint32 ECUM_CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
  uint32 ECUM_RESERVED3[93U];
  uint32 ECUM_STIR;                   /*!< Offset: 0x200 ( /W)  Software Triggered Interrupt Register */
  uint32 ECUM_RESERVED4[15U];
  uint32 ECUM_MVFR0;                  /*!< Offset: 0x240 (R/ )  Media and VFP Feature Register 0 */
  uint32 ECUM_MVFR1;                  /*!< Offset: 0x244 (R/ )  Media and VFP Feature Register 1 */
  uint32 ECUM_MVFR2;                  /*!< Offset: 0x248 (R/ )  Media and VFP Feature Register 2 */
  uint32 ECUM_RESERVED5[1U];
  uint32 ECUM_ICIALLU;                /*!< Offset: 0x250 ( /W)  I-Cache Invalidate All to PoU */
  uint32 ECUM_RESERVED6[1U];
  uint32 ECUM_ICIMVAU;                /*!< Offset: 0x258 ( /W)  I-Cache Invalidate by MVA to PoU */
  uint32 ECUM_DCIMVAC;                /*!< Offset: 0x25C ( /W)  D-Cache Invalidate by MVA to PoC */
  uint32 ECUM_DCISW;                  /*!< Offset: 0x260 ( /W)  D-Cache Invalidate by Set-way */
  uint32 ECUM_DCCMVAU;                /*!< Offset: 0x264 ( /W)  D-Cache Clean by MVA to PoU */
  uint32 ECUM_DCCMVAC;                /*!< Offset: 0x268 ( /W)  D-Cache Clean by MVA to PoC */
  uint32 ECUM_DCCSW;                  /*!< Offset: 0x26C ( /W)  D-Cache Clean by Set-way */
  uint32 ECUM_DCCIMVAC;               /*!< Offset: 0x270 ( /W)  D-Cache Clean and Invalidate by MVA to PoC */
  uint32 ECUM_DCCISW;                 /*!< Offset: 0x274 ( /W)  D-Cache Clean and Invalidate by Set-way */
  uint32 ECUM_RESERVED7[6U];
  uint32 ECUM_ITCMCR;                 /*!< Offset: 0x290 (R/W)  Instruction Tightly-Coupled Memory Control Register */
  uint32 ECUM_DTCMCR;                 /*!< Offset: 0x294 (R/W)  Data Tightly-Coupled Memory Control Registers */
  uint32 ECUM_AHBPCR;                 /*!< Offset: 0x298 (R/W)  AHBP Control Register */
  uint32 ECUM_CACR;                   /*!< Offset: 0x29C (R/W)  L1 Cache Control Register */
  uint32 ECUM_AHBSCR;                 /*!< Offset: 0x2A0 (R/W)  AHB Slave Control Register */
  uint32 ECUM_RESERVED8[1U];
  uint32 ECUM_ABFSR;                  /*!< Offset: 0x2A8 (R/W)  Auxiliary Bus Fault Status Register */
} ECUM_SCB_Type;

#define ECUM_SCS_BASE            (0xE000E000UL)                                      /*!< System Control Space Base Address */
#define ECUM_SCB_BASE            (ECUM_SCS_BASE +  0x0D00UL)                         /*!< System Control Block Base Address */
#define ECUM_SCB                 ((ECUM_SCB_Type       *)     ECUM_SCB_BASE      )   /*!< SCB configuration struct */
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define ECUM_START_SEC_CALLOUT_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : EcuM_AL_DriverInitZero                              **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This callout shall provide driver initialization    **
**                        and other hardware-related startup activities for   **
**                        loading the post-build configuration data. Note:    **
**                        Here only pre-compile and link-time configurable    **
**                        modules may be used.                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked :                               **
**                        EcuM_Gen_AL_DriverInitZero                          **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_DriverInitZero(void)
{
  #if (ECUM_DRIVER_INIT_ZERO == STD_ON)
  EcuM_Gen_AL_DriverInitZero();
  #endif
}

/*******************************************************************************
** Function Name        : EcuM_AL_DriverInitOne                               **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This callout shall provide driver initialization    **
**                        and other hardware-related startup activities in    **
**                        case of a power on reset                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ConfigPtr                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked :                               **
**                        EcuM_Gen_AL_DriverInitOne                           **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_DriverInitOne
  (P2CONST(EcuM_ConfigType, AUTOMATIC, ECUM_APPL_CONST) ConfigPtr)
{
  #if (ECUM_DRIVER_INIT_ONE == STD_ON)
  EcuM_Gen_AL_DriverInitOne(ConfigPtr);
  #endif
}

/*******************************************************************************
** Function Name        : EcuM_AL_DriverRestart                               **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This callout shall provide driver initialization    **
**                        and other hardware-related startup activities in    **
**                        case of a power on reset.                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ConfigPtr                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked :                               **
**                        EcuM_Gen_AL_DriverRestart                           **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_DriverRestart
  (P2CONST (EcuM_ConfigType, AUTOMATIC, ECUM_APPL_CONST) ConfigPtr)
{
  #if (ECUM_DRIVER_RESTART == STD_ON)
  EcuM_Gen_AL_DriverRestart(ConfigPtr);
  #else
  ECUM_UNUSED_PTR(ConfigPtr);
  #endif
}

/*******************************************************************************
** Function Name        : EcuM_AL_SetProgrammableInterrupts                   **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This call allows the system designer to notify that **
**                        the GO OFF I state is about to be entered.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_SetProgrammableInterrupts(void)
{
  /* Callout shall be filled by the system designer */
}

/*******************************************************************************
** Function Name        : EcuM_OnGoOffOne                                     **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This call allows the system designer to notify that **
**                        the GO OFF I state is about to be entered.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : EcuM_GddState              **
**                        Function(s) invoked    : BswM_EcuM_CurrentState()   **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_OnGoOffOne(void)
{
  EcuM_GddState = ECUM_STATE_GO_OFF_ONE;

  /* Indicate state change to BswM */
  BswM_EcuM_CurrentState(EcuM_GddState);
}

/*******************************************************************************
** Function Name        : EcuM_OnGoOffTwo                                     **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This call allows the system designer to notify that **
**                        the GO OFF II state is about to be entered.         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : EcuM_GddState              **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_OnGoOffTwo(void)
{
  EcuM_GddState = ECUM_STATE_GO_OFF_TWO;
}

/*******************************************************************************
** Function Name        : EcuM_AL_SwitchOff                                   **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This callout shall take the code for shutting off   **
**                        the power supply of the ECU. If the ECU cannot      **
**                        unpower itself, a reset may be an adequate reaction.**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : EcuM_GddState              **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_SwitchOff(void)
{
  EcuM_GddState = ECUM_STATE_OFF;
}

/*******************************************************************************
** Function Name        : EcuM_AL_Reset                                       **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This callout shall take the code for shutting off   **
**                        the power supply of the ECU. If the ECU cannot      **
**                        unpower itself, a reset may be an adequate reaction.**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : reset                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : EcuM_GddState              **
**                        Function(s) invoked    : Mcu_PerformReset()         **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_Reset(EcuM_ResetType reset)
{
  EcuM_GddState = ECUM_STATE_RESET;

  if ((reset == ECUM_RESET_MCU) || (reset == ECUM_INVALID_SHUTDOWN))
  {
    Mcu_PerformReset();
  }
}

/*******************************************************************************
** Function Name        : EcuM_EnableWakeupSources                            **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : The ECU Manager Module calls EcuM_EnableWakeupSource**
**                        to allow the system designer to notify wakeup       **
**                        sources defined in the wakeupSource bitfield that   **
**                        SLEEP will be entered and to adjust their source    **
**                        accordingly.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : wakeupSource                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
**                        EcuM_ClearWakeupEvent(), DataLog_SetSleepOKLog(),   **
**                        EcuM_H2LTransition_Callout_Swp(),                   **
**                        EcuM_H2LTransition_Callout_App()                    **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_EnableWakeupSources
  (EcuM_WakeupSourceType wakeupSource)
{
  ECUM_UNUSED(wakeupSource);

  /* Clear All Wakeup Sources */
  EcuM_ClearWakeupEvent(ECUM_WKSOURCE_ALL_SOURCES);
  #if (SWP_USE_DATALOG == STD_ON)
  DataLog_SetSleepOKLog();
  #endif

  #if (ECUM_LP_CALLOUT_ENABLED == STD_ON)
  /* Callout For Platform */
  EcuM_H2LTransition_Callout_Swp();

  /* Callout For User */
  EcuM_H2LTransition_Callout_App();
  #endif
}

/*******************************************************************************
** Function Name        : EcuM_DisableWakeupSources                           **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : The callout shall set up the given wakeup source(s) **
**                        so that they are not able to wakeup the ECU.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : wakeupSource                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
**                        DataLog_SetWakeupEventLog(),                        **
**                        EcuM_L2HTransition_Callout_Swp(),                   **
**                        EcuM_L2HTransition_Callout_App()                    **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_DisableWakeupSources
  (EcuM_WakeupSourceType wakeupSource)
{
  ECUM_UNUSED(wakeupSource);

  #if (SWP_USE_DATALOG == STD_ON)
  DataLog_SetWakeupEventLog();
  #endif

  #if (ECUM_LP_CALLOUT_ENABLED == STD_ON)
  /* Callout For Platform */
  EcuM_L2HTransition_Callout_Swp();

  /* Callout For User */
  EcuM_L2HTransition_Callout_App();
  #endif
}



/*******************************************************************************
** Function Name        : EcuM_CheckWakeup                                    **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This callout is called by the EcuM to poll a wakeup **
**                        source. It shall also be called by the ISR of a     **
**                        wakeup source to set up the PLL and check other     **
**                        wakeup sources that may be connected to the same    **
**                        interrupt.                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : wakeupSource                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    : Gpt_CheckWakeup            **
**                                                 EcuM_Gen_CheckWakeup       **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_CheckWakeup
  (EcuM_WakeupSourceType wakeupSource)
{
  #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
  if (wakeupSource == ECUM_ALARM_WAKEUP_SOURCE_ID)
  {
    SchM_Enter_EcuM_ALARM_TIME_PROTECTION();

    Gpt_CheckWakeup(wakeupSource);

    SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
  }
  else
  #endif
  {
    /* Wakeup Sequence */
    EcuM_Gen_CheckWakeup(wakeupSource);
  }
}

/*******************************************************************************
** Function Name        : EcuM_StartWakeupSources                             **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : The callout shall start the given wakeup source(s)  **
**                        so that they are ready to perform wakeup validation.**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : wakeupSource                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_StartWakeupSources
  (EcuM_WakeupSourceType wakeupSource)
{
  /* Callout shall be filled by the system designer */
  ECUM_UNUSED(wakeupSource);
}

/*******************************************************************************
** Function Name        : EcuM_StopWakeupSources                              **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : The callout shall stop the given wakeup source(s)   **
**                        after unsuccessful wakeup validation.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : EcuM_WakeupSourceType wakeupSource                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_StopWakeupSources
  (EcuM_WakeupSourceType wakeupSource)
{
  /* Callout shall be filled by the system designer */
  ECUM_UNUSED(wakeupSource);
}

/*******************************************************************************
** Function Name        : EcuM_CheckValidation                                **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This callout is called by the EcuM to validate a    **
**                        wakeup source. If a valid wakeup has been detected, **
**                        it shall be reported to EcuM via                    **
**                        EcuM_ValidateWakeupEvent().                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : wakeupSource                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_CheckValidation
  (EcuM_WakeupSourceType wakeupSource)
{
  /* Callout shall be filled by the system designer */
  ECUM_UNUSED(wakeupSource);
}

/*******************************************************************************
** Function Name        : EcuM_GenerateRamHash                                **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : Used just before Putting the ECU physically to sleep**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_GenerateRamHash(void)
{
  /* Callout shall be filled by the system designer */
}

/*******************************************************************************
** Function Name        : EcuM_SleepActivity                                  **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This callout is invoked periodically in all reduced **
**                        clock sleep modes. It is explicitly allowed to poll **
**                        wakeup sources from this callout and to call wakeup **
**                        notification functions to indicate the end of the   **
**                        sleep state to the ECU State Manager.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_SleepActivity(void)
{
  /* Callout shall be filled by the system designer */
}

/*******************************************************************************
** Function Name        : EcuM_CheckRamHash                                   **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This callout is intended to provide a RAM integrity **
**                        test.                                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(uint8, ECUM_CALLOUT_CODE) EcuM_CheckRamHash(void)
{
  return (1);
}

/*******************************************************************************
** Function Name        : EcuM_DeterminePbConfiguration                       **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This callout should evaluate some condition,        **
**                        like port pin or NVRAM value, to determine which    **
**                        post-build configuration shall be used in the       **
**                        remainder of the startup process. It shall load     **
**                        this configuration data into a piece of memory that **
**                        is accessible by all BSW modules and shall return a **
**                        pointer to the EcuM post-build configuration as a   **
**                        base for all BSW module post-build configurations.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : EcuM_ConfigType*                                    **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GaaConfig                                      **
**                        Function(s) invoked    :                            **
*******************************************************************************/
const EcuM_ConfigType* EcuM_DeterminePbConfiguration(void)
{
  /* The return value is updated only for compilation purpose. Valid address of
   *   EcuM_GaaConfig structure needs to be provided here. MISRA Rule 11.3 is
   * not considered in this case */
  P2CONST(EcuM_ConfigType, ECUM_CONST, ECUM_CONST) LpConfigPtr;
  LpConfigPtr = &EcuM_GaaConfig[0];
  return (LpConfigPtr);
}

/*******************************************************************************
** Function Name        : EcuM_ErrorHook                                      **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : In unrecoverable error situations, the ECU State    **
**                        Manager will call this callout. It is up the        **
**                        system integrator to react accordingly              **
**                        (reset, halt, restart, safe state etc. )            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : reason                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_ErrorHook(Std_ReturnType reason)
{
  /* Callout shall be filled by the system designer */
  ECUM_UNUSED(reason);
}

/*******************************************************************************
** Function Name        : EcuM_LoopDetection                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Callout used for reset loop detection               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : void                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_LoopDetection(void)
{
}

/*******************************************************************************
** Function Name        : EcuM_SetMode                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Callout used for Set Mcu Mode                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : McuMode                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : EcuM_GulPllCnt             **
**                        Function(s) invoked    :                            **
**                        WdgStack_TransitHighToLow(),                        **
**                        Mcu_GetPllStatus(), WdgStack_TransitHighToLow(),    **
**                        Icu_SetMode(), Mcu_SetMode(), Mcu_InitClock(),      **
**                        EnableAllInterrupts(), DisableAllInterrupts(),      **
**                        Det_ReportError(), Mcu_PerformReset(),              **
**                        SuspendAllInterrupts(), ResumeAllInterrupts()       **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_SetMode
  (Mcu_ModeType McuMode)
{
  /* Disable Interrupts(instruction is equivalent to writing a 1 into PRIMASK)
   * It should be located before EnableAllInterrupts()
   */
  __CPS(__CPS_DISABLE, __CPS_I, __CPS_DEFAULT);
  EnableAllInterrupts();

  Mcu_SetMode(McuMode);
  /* Enable Interrupts(instruction is equivalent to writing a 0 into PRIMASK)
   * It should be located before Icu_SetMode(), because ICU ISR should be
   * executed before peripheral flag cleared by Icu_SetMode()
   */
  __CPS(__CPS_ENABLE, __CPS_I, __CPS_DEFAULT);
  __ISB();

  boolean isMasterCore;   /* 20220517 Added for LPTask. */

  isMasterCore = EcuM_IsMasterCore();
  if (isMasterCore == TRUE) /* Master Core */
  {
    LowPowerActiveTask();
  }
  else/* Slave Core */
  {
    /*Stay in Deep Sleep*/
  }

  DisableAllInterrupts();
}

#if HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)
/*******************************************************************************
** Function Name        : EcuM_Enable_Pcache                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Enable PCache of each cores                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : McuMode                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
*******************************************************************************/
static FUNC(void, ECUM_CALLOUT_CODE) EcuM_Enable_Pcache(void)
{
  __DSB();
  __ISB();
  ECUM_SCB->ECUM_ICIALLU = 0UL;                        /* invalidate I-Cache */
  __DSB();
  __ISB();
  ECUM_SCB->ECUM_CCR |=  (uint32)ECUM_SCB_CCR_IC_Msk;  /* enable I-Cache */
  __DSB();
  __ISB();
}
#endif

/***************************************************************************//**
 * Function Name        : EcuM_Enable_Dma
 *
 * Service ID           : NA
 *
 * Description          : Enable Dma for Fls
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
static FUNC(void, ECUM_CALLOUT_CODE) EcuM_Enable_Dma(void)
{
  volatile uint32* dmactl = 0x402A0000;

  *dmactl |= 0x80000000U;
}

/*******************************************************************************
** Function Name        : EcuM_PreInit                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Callout used for before EcuM Init                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : McuMode                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : EcuM_GddResetReason        **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_PreInit(void)
{
  /* Set default reset reason */
  EcuM_GddResetReason = MCU_POWER_ON_RESET;

  #if HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)
  /* Enable PCache */
  EcuM_Enable_Pcache();
  #endif

  /* Enable DMA */
  EcuM_Enable_Dma();
}

/*******************************************************************************
** Function Name        : EcuM_PostInit                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Callout used for after Mcal Init                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : McuMode                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    : EcuM_PostInitUser()        **
*******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_PostInit(void)
{
  #if (ECUM_LP_CALLOUT_ENABLED == STD_ON)
  EcuM_PostInitUser();
  #endif
}

/*******************************************************************************
** Function Name        : EcuM_RequestSleep                                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Integration Code For Request Sleep using Release    **
**                        Run API                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : EcuM_GpEcuMConfigPtr       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_SelectShutdownTarget(),                        **
**                        DataLog_SetSleepConditionLog(), EcuM_ReleaseRUN()   **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CALLOUT_CODE) EcuM_RequestSleep
  (EcuM_UserType user)
{
  Std_ReturnType LddStdRetVal = E_NOT_OK;

  /* polyspace-begin MISRA2012:D4.14 [Justified:Medium] "Pointer is initialized in EcuM_Init" */
  (void)EcuM_SelectShutdownTarget(ECUM_STATE_SLEEP,
                                  EcuM_GpEcuMConfigPtr->ucEcuMDefaultSleepMode);
  /* polyspace-end MISRA2012:D4.14 */

  #if (SWP_USE_DATALOG == STD_ON)
  DataLog_SetSleepConditionLog();
  #endif
  LddStdRetVal = EcuM_ReleaseRUN(user);

  return LddStdRetVal;
}

/*******************************************************************************
** Function Name        : EcuM_RequestReset                                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Integration Code For Request Reset using Release    **
**                        Run API                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
**                        Function(s) invoked    : EcuM_SelectShutdownTarget  **
**                                                 EcuM_ReleaseRUN            **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CALLOUT_CODE) EcuM_RequestReset
  (EcuM_UserType user)
{
  Std_ReturnType LddStdRetVal = E_NOT_OK;

  (void)EcuM_SelectShutdownTarget(ECUM_STATE_RESET, ECUM_RESET_MCU);

  LddStdRetVal = EcuM_ReleaseRUN(user);

  return LddStdRetVal;
}

/*******************************************************************************
** Function Name        : EcuM_RequestOff                                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Integration Code For Request Off using Release Run  **
**                        API                                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
**                        Function(s) invoked    : EcuM_SelectShutdownTarget  **
**                                                 EcuM_ReleaseRUN            **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CALLOUT_CODE) EcuM_RequestOff
  (EcuM_UserType user)
{
  Std_ReturnType LddStdRetVal = E_NOT_OK;

  (void)EcuM_SelectShutdownTarget(ECUM_STATE_OFF, 0);

  LddStdRetVal = EcuM_ReleaseRUN(user);

  return LddStdRetVal;
}

#if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
/* polyspace-begin MISRA2012:8.4 [Justified:Low] "Reserved function" */
/*******************************************************************************
** Function Name        : EcuM_MainFunction1                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Runnable of Service SW Component EcuM_Slave1        **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Reentrancy           : None                                                **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_MainFunction()                                 **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_MainFunction1(void)
{
  EcuM_MainFunction();
}
#endif


#define ECUM_STOP_SEC_CALLOUT_CODE
#include "MemMap.h"
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:11.4 */
/* polyspace-end MISRA2012:20.1 */
/* polyspace-end MISRA2012:D4.5 */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
