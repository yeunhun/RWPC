/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  FILE-NAME : EcuM_Internal.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR EcuM Module                                           **
**                                                                            **
**  PURPOSE   : Provision of external declaration of APIs and Service IDs     **
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
** 3.0.3      25-Nov-2020   Manje Woo     Redmine #18654                      **
** 3.0.0      25-Jun-2019   Manje Woo     Redmine #17238, #17850, #16271      **
** 2.7.3      16-May-2017   Sanghoon Bae  Redmine #8552                       **
** 2.5.5      07-Jul-2016   Sanghoon Bae  Redmine #5257                       **
** 2.5.0      20-Aug-2015   Sanghoon Bae  Redmine #2571                       **
**                                        -Add function                       **
**                                         EcuM_SearchSleepModeWakeupSource   **
** 2.2.1      26-Dec-2014   Daejun Park   Redmine #1879                       **
**                                        -Update to AUTRON template          **
** 2.2.0      26-Nov-2014   Daejun Park   Modify alarm wakeup process         **
** 2.1.0      24-Sep-2014   Daejun Park   Redmine #1367                       **
** 1.1.0      07-Mar-2014   Daejun Park   Remove binary search APIs           **
** 1.0.0      04-Mar-2013   Daejun Park   Initial version                     **
*******************************************************************************/

#ifndef ECUM_INTERNAL_H
#define ECUM_INTERNAL_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM_Cfg.h"

#include "Mcu.h"
#if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
#include "Os.h"
#endif


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define ECUM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, ECUM_CODE) EcuM_SearchMode
 (P2VAR(uint8, AUTOMATIC, ECUM_DATA) LpModeIdx, uint8 sleepResetMode);

extern FUNC(boolean, ECUM_CODE) EcuM_SearchShutdownCause
 (P2VAR(uint8, AUTOMATIC, ECUM_DATA) LpCauseIdx,
  EcuM_ShutdownCauseType target);

extern FUNC(boolean, ECUM_CODE) EcuM_SearchWakeupSource
  (P2VAR(uint8, AUTOMATIC, ECUM_DATA) LpSourceIdx,
  EcuM_WakeupSourceType wakeupSource);

extern FUNC(boolean, ECUM_CODE) EcuM_SearchGoDownUser
  (P2VAR(uint8, AUTOMATIC, ECUM_DATA) LpGoDownUserIdx,
  EcuM_UserType user);

#if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
extern FUNC(boolean, ECUM_CODE) EcuM_SearchAlarmClockUser
  (P2VAR(uint8, AUTOMATIC, ECUM_DATA) LpAlarmUserIdx,
  EcuM_UserType user);

extern FUNC(void, ECUM_CODE) EcuM_ClearAlarm(void);

extern FUNC(void, ECUM_CODE) EcuM_GetGptTicks
  (P2VAR(uint32, AUTOMATIC, ECUM_DATA) LpTickValue);
#endif

extern FUNC(void, ECUM_CODE) EcuM_GoSleepSeq(uint8 LucSleepModeIndex);

extern FUNC(void, ECUM_CODE) EcuM_WakeupRestartSeq(uint8 SleepIndex);

extern FUNC(void, ECUM_CODE) EcuM_CheckResetReason(Mcu_ResetType resetReason);

extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_HaltSeq(uint8 LucSleepModeIndex);

extern FUNC(void, ECUM_CODE) EcuM_PollSeq(void);

extern FUNC(void, ECUM_CODE) EcuM_ValidationProtocol(void);

#if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
extern FUNC(void, ECUM_CODE) EcuM_OsWaitEvent(void);

extern FUNC(void, ECUM_CODE) EcuM_SlaveShutDownOrSleep(CoreIdType LddCoreId);
#endif

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_DetReportError(uint8 LucApiId,
  uint8 LucErrorId);
#endif

extern FUNC(boolean, ECUM_CODE) EcuM_SearchSleepModeWakeupSource
  (P2VAR(uint8, AUTOMATIC, ECUM_DATA) LpSourceIdx,
  EcuM_WakeupSourceType wakeupSource);

extern FUNC(void, ECUM_CODE) EcuM_GetOSResource (void);

extern FUNC(void, ECUM_CODE) EcuM_ReleaseOSResource (void);

extern FUNC(void, ECUM_CODE) EcuM_EnableInterrupts (void);

#define ECUM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* ECUM_INTERNAL_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

