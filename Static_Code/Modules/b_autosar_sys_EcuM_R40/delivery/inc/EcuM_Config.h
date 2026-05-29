/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  FILE-NAME : EcuM_Config.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR EcuM Module                                           **
**                                                                            **
**  PURPOSE   : Provision of external declaration of constant variables       **
**              to save the configured values                                 **
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
** 3.0.5      17-Aug-2021   Junho Cho     Redmine #31552                      **
** 3.0.0      12-Jun-2019   Manje Woo     Redmine #15128                      **
** 2.5.3      12-Jan-2016   Daejun Park   Redmine #3856                       **
**                                        -Update precompile option           **
** 2.2.1      26-Dec-2014   Daejun Park   Redmine #1879                       **
**                                        -Update to AUTRON template          **
** 2.1.0      24-Sep-2014   Daejun Park    Redmine #1367                      **
**                                         -Add spinlock variable             **
** 2.0.4      12-Jun-2014   Daejun Park    Add feature MCU_NORMAL_MODE        **
** 1.2.0      10-Apr-2014   Daejun Park    Move EcuM_GucNoOfAlarms variable   **
** 1.1.0      07-Mar-2014   Daejun Park    Add new constant variable for lib  **
** 1.0.10     04-Jul-2013   Daejun Park    CR~129, XAR~581 : EcuM library     **
**                                         -Add new precompile option         **
**                                          ECUM_DEMERROR_REPORT              **
**                                         -As per EcuM4047 in SWS,           **
**                                          ECUM_DEF_BEHAVIOUR_ENABLED should **
**                                          affect only ECUM_E_IMPROPER_CALLER**
**                                         -Add new constant variable         **
**                                          EcuM_GulOsNumOfTasks to replace   **
**                                          macro in static code              **
** 1.0.8      07-Jun-2013   Daejun Park    CR~119, XAR~558 : EcuM library     **
**                                         -Add inclusion of header file      **
**                                          EcuM.h                            **
**                                         -Add new constant variables        **
**                                          to replace macros in static code  **
** 1.0.0      04-Mar-2013   Daejun Park   Initial version                     **
*******************************************************************************/

#ifndef ECUM_CONFIG_H_
#define ECUM_CONFIG_H_

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM_Cfg.h"

#include "Mcu.h"
#include "Os.h"
#if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
#include "Gpt.h"
#endif
#if (ECUM_DEMERROR_REPORT == STD_ON)
#include "Dem.h"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define ECUM_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, ECUM_CONST) EcuM_GucNoOfResetModes;

extern CONST(uint8, ECUM_CONST) EcuM_GucNoOfGoDownUsers;

extern CONST(uint8, ECUM_CONST) EcuM_GucNoOfWakeupSources;

extern CONST(uint8, ECUM_CONST) EcuM_GucNoOfShutdownCause;

extern CONST(uint8, ECUM_CONST) EcuM_GucNoOfSleepModes;

extern CONST(uint8, ECUM_CONST) EcuM_GucNoOfCores;

extern CONST(uint8, ECUM_CONST) EcuM_GucNoOfOsResources;

#if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)

extern CONST(uint8, ECUM_CONST) EcuM_GucNoOfAlarms;

extern CONST(uint8, ECUM_CONST) EcuM_GucNoOfClockUsers;

#endif

#if (ECUM_MULTI_CORE_SUPPORT == STD_ON)

extern CONST(uint8, ECUM_CONST) EcuM_GucNoOfOsTasks;

extern CONST(uint8, ECUM_CONST) EcuM_GucNoOfEventMasks;

extern CONST(uint8, ECUM_CONST) EcuM_GucSlaveCoreMask;

#endif

#define ECUM_STOP_SEC_CONST_8
#include "MemMap.h"


#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(AppModeType, ECUM_CONST) EcuM_GddDefaultAppMode;

#if (ECUM_MCU_NORMAL_MODE_SUPPORT == STD_ON)

extern CONST(Mcu_ModeType, ECUM_CONST) EcuM_GulMcuNormalMode;

#endif

#if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)

extern CONST(EcuM_WakeupSourceType, ECUM_CONST) EcuM_GddAlarmWakeupSourceId;

extern CONST(Gpt_ChannelType, ECUM_CONST) EcuM_GucGptChannelId;

#endif

#if (ECUM_MULTI_CORE_SUPPORT == STD_ON)

extern CONST(SpinlockIdType, ECUM_CONST) EcuM_GucSpinlock;

#endif

#if (ECUM_DEMERROR_REPORT == STD_ON)
#if (ECUM_DEF_BEHAVIOUR_ENABLED == STD_ON)

extern CONST(Dem_EventIdType, ECUM_CONST) EcuM_GusEImproperCaller;

#endif

extern CONST(Dem_EventIdType, ECUM_CONST) EcuM_GusEConfigurationDataInconsistent;

extern CONST(Dem_EventIdType, ECUM_CONST) EcuM_GusERamCheckFailed;

#endif

#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)

#define ECUM_START_SEC_CONST_32
#include "MemMap.h"
extern CONST(uint32, ECUM_CONST) EcuM_GulGptChannelTickMax;
#define ECUM_STOP_SEC_CONST_32
#include "MemMap.h"

#endif

#endif /* ECUM_CONFIG_H_ */
