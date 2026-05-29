#ifndef SLPWUP_H
#define SLPWUP_H

#include "Rte_Type.h"
#include "Std_Types.h"

#define EcuMStateRequest_SLEEP  1ul
#define EcuMStateRequest_RUN    2ul

#define SLPWUP_INITIAL (0)

#define SLPWUP_SLEEP_REQUEST_READY (100)
#define SLPWUP_PRECONDITION_OK (101)
#define SLPWUP_NVM_JOB_FINISHED (102)
#define SLPWUP_NO_COM_JOB_FINISHED (103)
#define SLPWUP_NVM_NO_COM_JOB_FINISHED (104)

#define SLPWUP_SLEEP_REQUEST_NOT_READY (160)
#define SLPWUP_NVM_JOB_DETECTED (161)
#define SLPWUP_NVM_JOB_DETECTED_TIMEOUT (162)
#define SLPWUP_FULL_COM_DETECTED (163)
#define SLPWUP_FULL_COM_DETECTED_TIMEOUT (164)
#define SLPWUP_NVM_FULL_COM_DETECTED_TIMEOUT (165)
#define SLPWUP_NOT_ONCE_FULL_COM_TIMEOUT (166)
#define SLPWUP_NOT_ONCE_FULL_COM_DETECTED (167)

#define SLPWUP_SLEEP_PROCESS_TIMEOUT (240)
#define SLPWUP_PRECONDITION_CHECK (241)
#define SLPWUP_PRECONDITION_PASS (242)
#define SLPWUP_PRECONDITION_FAIL (243)
#define SLPWUP_H2L_TRANSITION_SWP (244)
#define SLPWUP_H2L_TRANSITION_APP (245)
#define SLPWUP_GOTO_MCU_SLEEP (246)
#define SLPWUP_EARLY_WAKEUP_DETECTED (247)
#define SLPWUP_L2H_TRANSITION_SWP (248)
#define SLPWUP_L2H_TRANSITION_APP (249)
#define SLPWUP_IGN_L_H            (250)

#define SLPWUP_SLEEP_PROCESS_ERROR (10)
#define SLPWUP_ECUM_UNINIT (16)
#define SLPWUP_UNKNOWN_WAKEUP_SOURCE  (23)
#define SLPWUP_SHUTDOWN_FAILED (25)
#define SLPWUP_UNKNOWN_SLEEP_MODE   (32)
#define SLPWUP_INVALID_API_CALL  (33)
#define SLPWUP_INVALID_SHUTDOWNTARGET   (34)


#define SLPWUP_LPT_DEFAULT_WAKEUP       (170U) /*0xAA*/
#define SLPWUP_LPT_POR_WAKEUP       (0U)
#define SLPWUP_LPT_PERIOD_WAKEUP    (1U)
#define SLPWUP_LPT_USR_WAKEUP       (2U)
#define SLPWUP_LPT_OTHER_WAKEUP     (4U)

#define SLPWUP_LPT_RET_TO_POR       (0U)
#define SLPWUP_LPT_RET_TO_LPTASK    (1U)
#define SLPWUP_LPT_RET_TO_STANDBY   (2U)

#define LP_TASK_ASW    0x55
extern uint8 Slpwup_GulSleepProcessingCount_Flag;
extern uint8 Slpwup_GulSleepProcessState;

extern uint8 f_BCAN_WakeupEvtOn;

extern uint8 f_ComMModeState_BCAN;
extern uint8 ADC_cnt;
extern uint16 cnt_wakeupwait;

extern void Slpwup_RequestSleep(void);
extern void Slpwup_10ms_Task(void);
extern void LowPowerActiveTask(void);
extern FUNC(void, SLPWUP_LPTM_CODE) Slpwup_PreLPMode_Configuration(void);
#endif
