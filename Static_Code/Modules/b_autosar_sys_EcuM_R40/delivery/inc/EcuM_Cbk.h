/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  FILE-NAME : EcuM_Cbk.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR EcuM Module                                           **
**                                                                            **
**  PURPOSE   : Header file of EcuM_Cbk.c and EcuM_Callout_Stubs.c            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                              Revision History                              **
********************************************************************************
** Revision   Date          By            Description                         **
********************************************************************************
** 3.1.0      24-Nov-2021   Junho Cho     Redmine #33037                      **
** 3.0.5      17-Aug-2021   Junho Cho     Redmine #31552                      **
** 3.0.0      25-Jun-2019   Manje Woo     Redmine #17850, #16271              **
** 2.10.0     19-Jun-2018   Sanghoon Bae  Redmine #13076                      **
** 2.9.0      17-Apr-2018   Sanghoon Bae  Redmine #12242                      **
** 2.8.0      20-Sep-2017   Sanghoon Bae  Redmine #10090                      **
** 2.7.2      30-May-2017   Sanghoon Bae  Redmine #7696                       **
** 2.5.5      18-May-2016   Sanghoon Bae  MISRA Fix                           **
** 2.4.1      27-May-2015   Jihoon Jung   Redmine #2550                       **
** 2.2.1      26-Dec-2014   Daejun Park   Redmine #1879                       **
**                                        -Update to AUTRON template          **
** 1.1.0      07-Mar-2014   Daejun Park   Cleanup code                        **
** 1.0.11     04-Jul-2013   Daejun Park   CR~129, XAR~581 : EcuM library      **
** 1.0.0      04-Mar-2013   Daejun Park   Initial version                     **
*******************************************************************************/

#ifndef ECUM_CBK_H
#define ECUM_CBK_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM_Generated_Types.h"
#include "EcuM_Types.h"
#include "Mcu.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define ECUM_START_SEC_CODE
#include "MemMap.h"

/* Extern for EcuM_SetWakeupEvent API */
extern FUNC(void, ECUM_CODE) EcuM_SetWakeupEvent
  (EcuM_WakeupSourceType sources);

/* Extern for EcuM_ValidateWakeupEvent API */
extern FUNC(void, ECUM_CODE) EcuM_ValidateWakeupEvent
  (EcuM_WakeupSourceType sources);

/* Extern for EcuM_McuPostInit in Internal.h */
extern FUNC(void, ECUM_CODE) EcuM_McuPostInit (void);

#define ECUM_STOP_SEC_CODE
#include "MemMap.h"

#define ECUM_START_SEC_CALLOUT_CODE
#include "MemMap.h"

/* Extern for EcuM_AL_SetProgrammableInterrupts Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_SetProgrammableInterrupts(void);

/* Extern for EcuM_DeterminePbConfiguration Callout */
/* polyspace +2 MISRA2012:20.7 [Justified:Medium] "AUTOEVER_MISRA_20_7" */
extern FUNC(P2CONST(EcuM_ConfigType, ECUM_CONST, ECUM_APPL_CONST),
  ECUM_CALLOUT_CODE) EcuM_DeterminePbConfiguration(void);

/* Extern for EcuM_UserHook_DeterminePbConfiguration */
extern FUNC(Std_ReturnType, ECUM_CALLOUT_CODE)EcuM_UserHook_DeterminePbConfiguration
  (uint8* VariantIdx);

/* Extern for EcuM_AL_DriverInitZero Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_DriverInitZero(void);

/* Extern for EcuM_AL_DriverInitOne Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_DriverInitOne
  (P2CONST(EcuM_ConfigType, ECUM_CONST, ECUM_APPL_CONST) ConfigPtr);

/* Extern for EcuM_AL_DriverRestart Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_DriverRestart
  (P2CONST(EcuM_ConfigType, ECUM_CONST, ECUM_APPL_CONST) ConfigPtr);

/* Extern for EcuM_OnGoOffOne Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_OnGoOffOne(void);

/* Extern for EcuM_OnGoOffTwo Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_OnGoOffTwo(void);

/* Extern for EcuM_AL_SwitchOff Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_SwitchOff(void);

/* Extern for EcuM_AL_Reset Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_Reset(EcuM_ResetType reset);

/* Extern for EcuM_ClearWakeupInterrupts Callout */
extern FUNC(void, ECUM_CODE) EcuM_ClearWakeupInterrupts
  (EcuM_WakeupSourceType wakeupSource);

/* Extern for EcuM_CheckWakeup Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_CheckWakeup
  (EcuM_WakeupSourceType wakeupSource);

/* Extern for EcuM_GenerateRamHash Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_GenerateRamHash(void);

/* Extern for EcuM_SleepActivity Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_SleepActivity(void);

/* Extern for EcuM_CheckRamHash Callout */
extern FUNC(uint8, ECUM_CALLOUT_CODE) EcuM_CheckRamHash(void);

/* Extern for EcuM_StartWakeupSources Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_StartWakeupSources
  (EcuM_WakeupSourceType wakeupSource);

/* Extern for EcuM_CheckValidation Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_CheckValidation
  (EcuM_WakeupSourceType wakeupSource);

/* Extern for EcuM_SleepActivity Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_StopWakeupSources
  (EcuM_WakeupSourceType wakeupSource);

/* Extern for EcuM_ErrorHook Callout */
/* polyspace +2 MISRA2012:D4.5 [Justified:Low] "Syntax is defined in AUTOSAR specification" */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_ErrorHook(Std_ReturnType reason);

/* Extern for EcuM_SetMode Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_SetMode(Mcu_ModeType McuMode);

/* Extern for EcuM_PreInit */
extern FUNC(void, ECUM_CODE) EcuM_PreInit (void);

/* Extern for EcuM_SetRunState */
/* polyspace +2 MISRA2012:8.5 [Justified:Low] "To separate BSW and SWC, it should be declared in two header files." */
extern  FUNC(void, ECUM_CODE) EcuM_SetRunState(void);

/* Extern for EcuM_PreInit */
extern FUNC(void, ECUM_CODE) EcuM_PostInit (void);

#define ECUM_STOP_SEC_CALLOUT_CODE
#include "MemMap.h"

#endif /* ECUM_CBK_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

