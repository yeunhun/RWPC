/*******************************************************************************
**                                                                            **
**  (C) 2015 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  FILE-NAME : App_Mode.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Application Mode SWC                                  **
**                                                                            **
**  PURPOSE   : Sample SWC code for Application Mode                          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                              Revision History                              **
********************************************************************************
** Revision   Date          By            Description                         **
********************************************************************************
*******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "WPCVehicleOption.h"
#include "Rte_SWC_AppMode.h"
#include "SlpWup.h"

#include "WPCSleepVarTYpe.h"
#include "WPCSleepVar.h"
#include "define.h"

#include "app_input_type.h"
#include "app_input.h"

#include "app_can_output_type.h"
#include "app_can_output.h"

#include "Dem.h"
#include "Dem_Ram.h"
#include "Dem_EventMemory.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define APP_MODE_USER 0ul

uint8 AppMode_GucTestCase = 0u;
uint8 AppMode_GucTestCount = 50u;
uint8 AppMode_GucWakeupCount = 0u;
uint8 AppMode_GucBusoffCount = 0u;
Rte_ModeType_EcuMode AppMode_GddEcuMode = RTE_TRANSITION_EcuMode;
Rte_ModeType_MDG_WakeupEvent AppMode_GddWakeupEvent = RTE_MODE_MDG_WakeupEvent_INITIAL_MODE;

Rte_ModeType_MDG_ComMMode AppMode_GddComMMode_LOCALCAN = RTE_MODE_MDG_ComMMode_NO_COM;
Rte_ModeType_MDG_ComMMode AppMode_GddComMMode_BCAN = RTE_MODE_MDG_ComMMode_NO_COM;
Rte_ModeType_MDG_CanSMBORState AppMode_GddBORState_LOCALCAN = RTE_MODE_MDG_CanSMBORState_COMPLETE;
Rte_ModeType_MDG_CanSMBORState AppMode_GddBORState_BCAN = RTE_MODE_MDG_CanSMBORState_COMPLETE;
uint8 bcan_wakeup_flag = Off;

extern tAPP_SLEEP APP_SLEEP_IF;

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : AppMode_InitCompleted                               **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Runnable invoked when BSW Init Completed            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
/* PortConfigSet container short name  */
//=> Generated/Mcal_Output/include/Port_Cfg.h
//#define PortConf_PortConfigSet_PortConfigSet_0    (Port_Config[0])
//#define PortConf_PortConfigSet_PortConfigSet_Active_NFC    (Port_Config[1])
//#define PortConf_PortConfigSet_PortConfigSet_DeepSleep_NFC    (Port_Config[2])
// Port_Init(&Port_Config);
#include "Port.h"
#include "Port_Cfg.h"
#include "Wdg_66_IA_Api.h"
#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"

extern void nfc_ticktimer_start(void);
extern void Scb_I2C_Initialize(void);
extern void TXCommInit(void);
extern void WPC_Setting_Option(void);
extern void Initial_Input(void);
extern void Init_CAN(void);
extern uint8 DTC_Set_Status;
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
extern void set_wpc_ecu_reset(void);
#endif
FUNC(void,AppMode_CODE) AppMode_InitCompleted(void)
{
  IoHwAb_LevelType ret_NFC_OPTON;
  Rte_ModeType_MDG_InitState LddPrevInitState, LddNextInitState;
  (void)Rte_Mode_modeNotificationPort_InitState_InitState(&LddPrevInitState, &LddNextInitState);
  /* Condition when BSW initialization completed */
  if (LddNextInitState == RTE_MODE_MDG_InitState_COMPLETE)
  {
    //nfc_ticktimer_start();
    Scb_I2C_Initialize();
    TXCommInit();
    Initial_Input();
    WPC_Setting_Option();
    Init_CAN();
    DTC_Set_Status = On;
    SetX(kb_NFC_OPTION, Off);
    Port_Init(&PortConf_PortConfigSet_PortConfigSet_NoneNFC_Ani);    // Non-NFC_Ani



    Rte_Call_OpCycle_POWER_CYCLE_SetOperationCycleState(DEM_CYCLE_STATE_START);
    //Rte_Call_OpCycle_IGNITION_CYCLE_SetOperationCycleState(DEM_CYCLE_STATE_START);
    //Rte_Call_EnableCond_DemEnableCondition_SetEnableCondition(FALSE);

    Dem_EvMem_SetAgingCounter(Dem_PrimaryEventMemory,0u);
    Dem_EvMem_SetAgingCounter(Dem_PrimaryEventMemory+1u,0u);
    Dem_EvMem_SetAgingCounter(Dem_PrimaryEventMemory+2u,0u);
  }

  Wdg_66_IA_SetMode(WDGIF_OFF_MODE);
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
  set_wpc_ecu_reset();
#endif
}
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"

/*******************************************************************************
** Function Name        : AppMode_EcuModeSwitched                             **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Runnable invoked when EcuMode updated from BswM     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void,AppMode_CODE) AppMode_EcuModeSwitched(void)
{
  //Rte_ModeType_EcuMode LddPrevEcuMode, LddNextEcuMode;
  Rte_ModeType_EcuMode LddPrevEcuMode_local, LddNextEcuMode_local;

  //(void)Rte_Mode_modeNotificationPort_EcuMode_EcuMode(&LddPrevEcuMode, &LddNextEcuMode);
  (void)Rte_Mode_modeNotificationPort_EcuMode_EcuMode(&LddPrevEcuMode_local, &LddNextEcuMode_local);

  SetX(LddNextEcuMode, LddNextEcuMode_local);
  //(void)Rte_Write_SWC_AppMode_P_Slpwup_EcuMode_SR_u8(LddNextEcuMode);
  (void)Rte_Write_SWC_AppMode_P_Slpwup_EcuMode_SR_u8(&LddNextEcuMode);


  if (LddNextEcuMode_local == RTE_MODE_EcuMode_ECUM_STATE_RUN)
  {
    /* Condition when ECU state changed from STARTUP to RUN */
    if(AppMode_GddWakeupEvent == RTE_MODE_MDG_WakeupEvent_INITIAL_MODE)
    {
      /* first It need to the Run Request */
      Rte_Call_clientPort_StateRequest_RequestRUN(APP_MODE_USER);

      /* This code is executed only once shortly after Rte_Start */
      if(GetX(kb_NFC_OPTION)==On)
      {
        Rte_Write_modeRequestPort_ComMMode_LOCALCAN_ComMMode_LOCALCAN(COMM_MODE_FULL_COM);
      }
      Rte_Write_modeRequestPort_ComMMode_BCAN_ComMMode_BCAN(COMM_MODE_FULL_COM);
    }
    /* Condition when ECU state changed from SLEEP to RUN */
    else
    {
      if(GetX(kb_NFC_OPTION)==On)
      {
        if ((AppMode_GddWakeupEvent == RTE_MODE_MDG_WakeupEvent_BCAN_RX) ||
            (AppMode_GddWakeupEvent == RTE_MODE_MDG_WakeupEvent_BCAN_RX_POLL) ||
            (AppMode_GddWakeupEvent == RTE_MODE_MDG_WakeupEvent_LOCALCAN_RX) ||
            (AppMode_GddWakeupEvent == RTE_MODE_MDG_WakeupEvent_LOCALCAN_RX_POLL))
        {
          //Rte_Call_clientPort_StateRequest_RequestRUN(APP_MODE_USER);

          Rte_Write_modeRequestPort_ComMMode_BCAN_ComMMode_BCAN(COMM_MODE_FULL_COM);
          Rte_Write_modeRequestPort_ComMMode_LOCALCAN_ComMMode_LOCALCAN(COMM_MODE_FULL_COM);
        }
        else if (AppMode_GddWakeupEvent == RTE_MODE_MDG_WakeupEvent_IGN_WakeUP)
        {
          Rte_Write_modeRequestPort_ComMMode_LOCALCAN_ComMMode_LOCALCAN(COMM_MODE_FULL_COM);
          Rte_Write_modeRequestPort_ComMMode_BCAN_ComMMode_BCAN(COMM_MODE_FULL_COM);
        }
      }
      else
      {
        if ((AppMode_GddWakeupEvent == RTE_MODE_MDG_WakeupEvent_BCAN_RX) ||
            (AppMode_GddWakeupEvent == RTE_MODE_MDG_WakeupEvent_BCAN_RX_POLL) )
        {
          Rte_Write_modeRequestPort_ComMMode_BCAN_ComMMode_BCAN(COMM_MODE_FULL_COM);
        }
        else if (AppMode_GddWakeupEvent == RTE_MODE_MDG_WakeupEvent_IGN_WakeUP)
        {
          Rte_Write_modeRequestPort_ComMMode_BCAN_ComMMode_BCAN(COMM_MODE_FULL_COM);
        }
      }
    }
    /* When State is RTE_MODE_EcuMode_ECUM_STATE_RUN, execute last */
    Rte_Call_clientPort_StateRequest_SetRunState();
  }
  /* FullCom Request for Integration Test */
  /* This action depends on Application Requirement, Modify Here */
}

#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"

/*******************************************************************************
** Function Name        : AppMode_WakeupEventValidated                        **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Runnable invoked when wakeup event occurs           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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

#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
#include "WPCSleepControl.h"
#include "WPCTimer.h"
FUNC(void,AppMode_CODE) AppMode_WakeupEventValidated(void)
{
  Rte_ModeType_MDG_WakeupEvent LddPrevWakeupEvent;
  //Rte_ModeType_EcuMode LddPrevEcuMode;
  //Rte_ModeType_EcuMode LddNextEcuMode;
  //Rte_ModeType_EcuMode LddCurrEcuMode;
  Rte_ModeType_EcuMode LddPrevEcuMode_local;
  Rte_ModeType_EcuMode LddNextEcuMode_local;
  Rte_ModeType_EcuMode LddCurrEcuMode_local;
  Slpwup_GulSleepProcessingCount_Flag = 0u;

  (void)Rte_Mode_modeNotificationPort_WakeupEvent_WakeupEvent(&LddPrevWakeupEvent, &AppMode_GddWakeupEvent);
  LddCurrEcuMode_local = Rte_Mode_modeNotificationPort_EcuMode_EcuMode(&LddPrevEcuMode_local, &LddNextEcuMode_local);

  if ((AppMode_GddWakeupEvent == RTE_MODE_MDG_WakeupEvent_BCAN_RX))
  {
	/* Actions when CanCM Polling Wakeup occurs */
	/* IF full com requested here, App Mode Active should be requested */
	Rte_Write_modeRequestPort_ComMMode_BCAN_ComMMode_BCAN(COMM_MODE_FULL_COM);
	if (LddCurrEcuMode_local != RTE_MODE_EcuMode_ECUM_STATE_RUN)
	{
	Rte_Call_clientPort_StateRequest_RequestRUN(APP_MODE_USER);
	}
	AppMode_GucWakeupCount++;
	StartTimer(Timer_SleepWait);
  }
  else if ((AppMode_GddWakeupEvent == RTE_MODE_MDG_WakeupEvent_BCAN_RX_POLL))
  {
	/* Actions when CanCM Polling Wakeup occurs */
	/* IF full com requested here, App Mode Active should be requested */
	Rte_Write_modeRequestPort_ComMMode_BCAN_ComMMode_BCAN(COMM_MODE_FULL_COM);
	if (LddCurrEcuMode_local != RTE_MODE_EcuMode_ECUM_STATE_RUN)
	{
	  Rte_Call_clientPort_StateRequest_RequestRUN(APP_MODE_USER);
	}
	AppMode_GucWakeupCount++;
	StartTimer(Timer_SleepWait);
  }
  else if (AppMode_GddWakeupEvent == RTE_MODE_MDG_WakeupEvent_IGN_WakeUP)
  {
	Rte_Write_modeRequestPort_ComMMode_BCAN_ComMMode_BCAN(COMM_MODE_FULL_COM);
	if (LddCurrEcuMode_local != RTE_MODE_EcuMode_ECUM_STATE_RUN)
	{
	Rte_Call_clientPort_StateRequest_RequestRUN(APP_MODE_USER);
	}
	AppMode_GucWakeupCount++;
	StartTimer(Timer_SleepWait);
  }
}
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"

/*******************************************************************************
** Function Name        : AppMode_ComMModeSwitched_LOCALCAN                    **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Runnable invoked when ComM Mode switched            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void,AppMode_CODE) AppMode_ComMModeSwitched_LOCALCAN(void)
{
	/* Misra-C */
}
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"
/*******************************************************************************
** Function Name        : AppMode_ComMModeSwitched_BCAN                    **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Runnable invoked when ComM Mode switched            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void,AppMode_CODE) AppMode_ComMModeSwitched_BCAN(void)
{
  Rte_ModeType_MDG_ComMMode LddPrevBusState_local, LddNextBusState_local;
  Rte_Mode_modeNotificationPort_ComMMode_BCAN_ComMMode_BCAN(&LddPrevBusState_local, &LddNextBusState_local);

  /* Conditions when Com Mode No Com switched */
  //if (LddNextBusState == RTE_MODE_MDG_ComMMode_NO_COM)
  if (LddNextBusState_local == RTE_MODE_MDG_ComMMode_NO_COM)
  {
    SetX(LddNextBusState, RTE_MODE_MDG_ComMMode_NO_COM);
    (void)Rte_Write_SWC_AppMode_P_Slpwup_ComMNoti_BCAN_SR_u8(&LddNextBusState);
    f_ComMModeState_BCAN = RTE_MODE_MDG_ComMMode_NO_COM;
	bcan_wakeup_flag = Off;
  }
  /* Conditions when Com Mode Silent Com switched */
  else if (LddNextBusState_local == RTE_MODE_MDG_ComMMode_SILENT_COM)
  {
    SetX(LddNextBusState, RTE_MODE_MDG_ComMMode_SILENT_COM);
    (void)Rte_Write_SWC_AppMode_P_Slpwup_ComMNoti_BCAN_SR_u8(&LddNextBusState);
    f_ComMModeState_BCAN = RTE_MODE_MDG_ComMMode_SILENT_COM;
	bcan_wakeup_flag = Off;
  }
  /* Conditions when Com Mode Full Com switched */
  else if (LddNextBusState_local == RTE_MODE_MDG_ComMMode_FULL_COM)
  {
    SetX(LddNextBusState, RTE_MODE_MDG_ComMMode_FULL_COM);
    (void)Rte_Write_SWC_AppMode_P_Slpwup_ComMNoti_BCAN_SR_u8(&LddNextBusState);

    SetX(First_FullComMode_BCAN, 1u);
    (void)Rte_Write_SWC_AppMode_P_Slpwup_FullComM_BCAN_SR_u8(&First_FullComMode_BCAN);
    f_ComMModeState_BCAN = RTE_MODE_MDG_ComMMode_FULL_COM;
	bcan_wakeup_flag = On;
  }
}
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"
/*******************************************************************************
** Function Name        : AppMode_CanSMBorStateSwitched_LOCALCAN               **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Runnable invoked when CanSM Busoff Recovery State   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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

#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void,AppMode_CODE) AppMode_CanSMBorStateSwitched_LOCALCAN(void)
{
  Rte_ModeType_MDG_CanSMBORState LddPrevState;
  Rte_Mode_modeNotificationPort_CanSMBORState_LOCALCAN_CanSMBORState_LOCALCAN(&LddPrevState, &AppMode_GddBORState_LOCALCAN);
  /* Conditions when bus-off recovery started */
  if (AppMode_GddBORState_LOCALCAN == RTE_MODE_MDG_CanSMBORState_START)
  {
    Set_All(b_CANBUSOFFState_LCAN,On);
  }
  /* Conditions when bus-off recovery completed */
  else if (AppMode_GddBORState_LOCALCAN == RTE_MODE_MDG_CanSMBORState_COMPLETE)
  {
  	Rte_Call_OpCycle_POWER_CYCLE_SetOperationCycleState(DEM_CYCLE_STATE_START);
  	Rte_Call_OpCycle_IGNITION_CYCLE_SetOperationCycleState(DEM_CYCLE_STATE_START);
  	Set_All(b_CANBUSOFFState_LCAN,Off);
  }
}
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"
/*******************************************************************************
** Function Name        : AppMode_CanSMBorStateSwitched_BCAN               **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Runnable invoked when CanSM Busoff Recovery State   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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

#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void,AppMode_CODE) AppMode_CanSMBorStateSwitched_BCAN(void)
{
  Rte_ModeType_MDG_CanSMBORState LddPrevState;
  Rte_Mode_modeNotificationPort_CanSMBORState_BCAN_CanSMBORState_BCAN(&LddPrevState, &AppMode_GddBORState_BCAN);
  /* Conditions when bus-off recovery started */
  if (AppMode_GddBORState_BCAN == RTE_MODE_MDG_CanSMBORState_START)
  {
    Set_All(b_CANBUSOFFState,On);
  }
  /* Conditions when bus-off recovery completed */
  else if (AppMode_GddBORState_BCAN == RTE_MODE_MDG_CanSMBORState_COMPLETE)
  {
    Rte_Call_OpCycle_POWER_CYCLE_SetOperationCycleState(DEM_CYCLE_STATE_START);
    Rte_Call_OpCycle_IGNITION_CYCLE_SetOperationCycleState(DEM_CYCLE_STATE_START);
    Set_All(b_CANBUSOFFState,Off);
  }
}
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"
/* BCAN Bus Off or LCAN Bus Off aging counter Clear function */
void aging_counter_func(void)
{
  if (AppMode_GddBORState_BCAN == RTE_MODE_MDG_CanSMBORState_COMPLETE)
  {
     Dem_ReportErrorStatus(DemConf_DemEventParameter_CANSM_E_BUS_OFF_BCAN, DEM_EVENT_STATUS_PASSED);
  }
  if (AppMode_GddBORState_LOCALCAN == RTE_MODE_MDG_CanSMBORState_COMPLETE)
  {
     Dem_ReportErrorStatus(DemConf_DemEventParameter_CANSM_E_BUS_OFF_LOCALCAN, DEM_EVENT_STATUS_PASSED);
  }
}
/*******************************************************************************
** Function Name        : AppMode_PduGroupSwitched_LOCALCAN_Tx                 **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Runnable invoked when Com PduGroup Switched       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void,AppMode_CODE) AppMode_PduGroupSwitched_LOCALCAN_Tx (void)
{
  Rte_ModeType_MDG_PduGroup LddPrevPduState, LddNextPduState;
  Rte_Mode_modeNotificationPort_PduGroupTx_LOCALCAN_PduGroupTx_LOCALCAN(&LddPrevPduState, &LddNextPduState);

  /* Conditions when PduGroup stopped */
  if (LddNextPduState == RTE_MODE_MDG_PduGroup_STOP)
  {
  }
  /* Conditions when PduGroup started */
  else if (LddNextPduState == RTE_MODE_MDG_PduGroup_START)
  {
  }
}
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"
/*******************************************************************************
** Function Name        : AppMode_PduGroupSwitched_LOCALCAN_Rx                 **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Runnable invoked when CanSM PduGroup Switched       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void,AppMode_CODE) AppMode_PduGroupSwitched_LOCALCAN_Rx (void)
{
  Rte_ModeType_MDG_PduGroup LddPrevPduState, LddNextPduState;
  Rte_Mode_modeNotificationPort_PduGroupRx_LOCALCAN_PduGroupRx_LOCALCAN(&LddPrevPduState, &LddNextPduState);

  /* Conditions when PduGroup stopped */
  if (LddNextPduState == RTE_MODE_MDG_PduGroup_STOP)
  {
  }
  /* Conditions when PduGroup started */
  else if (LddNextPduState == RTE_MODE_MDG_PduGroup_START)
  {
  }
}
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"
/*******************************************************************************
** Function Name        : AppMode_PduGroupSwitched_BCAN_Tx                 **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Runnable invoked when Com PduGroup Switched       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void,AppMode_CODE) AppMode_PduGroupSwitched_BCAN_Tx (void)
{
  Rte_ModeType_MDG_PduGroup LddPrevPduState, LddNextPduState;
  Rte_Mode_modeNotificationPort_PduGroupTx_BCAN_PduGroupTx_BCAN(&LddPrevPduState, &LddNextPduState);

  /* Conditions when PduGroup stopped */
  if (LddNextPduState == RTE_MODE_MDG_PduGroup_STOP)
  {
  }
  /* Conditions when PduGroup started */
  else if (LddNextPduState == RTE_MODE_MDG_PduGroup_START)
  {
  }
}
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"
/*******************************************************************************
** Function Name        : AppMode_PduGroupSwitched_BCAN_Rx                 **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Runnable invoked when CanSM PduGroup Switched       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void,AppMode_CODE) AppMode_PduGroupSwitched_BCAN_Rx (void)
{
  Rte_ModeType_MDG_PduGroup LddPrevPduState, LddNextPduState;
  Rte_Mode_modeNotificationPort_PduGroupRx_BCAN_PduGroupRx_BCAN(&LddPrevPduState, &LddNextPduState);

  /* Conditions when PduGroup stopped */
  if (LddNextPduState == RTE_MODE_MDG_PduGroup_STOP)
  {
  }
  /* Conditions when PduGroup started */
  else if (LddNextPduState == RTE_MODE_MDG_PduGroup_START)
  {
  }
}
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"
/*******************************************************************************
** Function Name        : Slpwup_RequestMode_BCAN                             **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void, SWC_AppMode_CODE) Slpwup_RequestMode_BCAN(IN VAR(uint8, AUTOMATIC) Data)
{
  Rte_ModeType_MDG_ComMMode LddReqBusState;
  LddReqBusState = Data;

  if (LddReqBusState == RTE_MODE_MDG_ComMMode_NO_COM)
  {
    Rte_Write_modeRequestPort_ComMMode_BCAN_ComMMode_BCAN(COMM_MODE_NO_COM);              // int 0u
  }
  else if(LddReqBusState == RTE_MODE_MDG_ComMMode_FULL_COM)
  {
    Rte_Write_modeRequestPort_ComMMode_BCAN_ComMMode_BCAN(COMM_MODE_FULL_COM);            // int 2u
  }
  else
  {

  }
}
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"
/*******************************************************************************
** Function Name        : Slpwup_RequestMode_LCAN                             **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void, SWC_AppMode_CODE) Slpwup_RequestMode_LCAN(IN VAR(uint8, AUTOMATIC) Data)
{
  Rte_ModeType_MDG_ComMMode LddReqBusState;
  LddReqBusState = Data;

  if (LddReqBusState == RTE_MODE_MDG_ComMMode_NO_COM)
  {
    if(GetX(kb_NFC_OPTION)==On)
    {
      Rte_Write_modeRequestPort_ComMMode_LOCALCAN_ComMMode_LOCALCAN(COMM_MODE_NO_COM);        // int 0u
    }
  }
  else if(LddReqBusState == RTE_MODE_MDG_ComMMode_FULL_COM)
  {
    if(GetX(kb_NFC_OPTION)==On)
    {
      Rte_Write_modeRequestPort_ComMMode_LOCALCAN_ComMMode_LOCALCAN(COMM_MODE_FULL_COM);      // int 2u
    }
  }
  else
  {

  }
}
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"
/*******************************************************************************
** Function Name        : Slpwup_EcuM_StateRequest                             **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"
FUNC(void, SWC_AppMode_CODE) Slpwup_EcuM_StateRequest(IN VAR(uint8, AUTOMATIC) Data)
{
  if (Data == EcuMStateRequest_RUN)
  {
    Rte_Call_clientPort_StateRequest_RequestRUN(APP_MODE_USER);
  }
  else if (Data == EcuMStateRequest_SLEEP)
  {
    Rte_Call_clientPort_StateRequest_RequestSleep(APP_MODE_USER);
  }
  else
  {

  }
}
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"
/*******************************************************************************
** Function Name        : AppMode_Test                                        **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Test application runnable                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
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
#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"
Std_ReturnType RetrunVal = 0;
uint8 TestFail = 0;
FUNC(void,AppMode_CODE) AppMode_Test(void)
{
    switch (AppMode_GucTestCase)
    {
    case 1: /* ECU RUN Request */
      Rte_Call_clientPort_StateRequest_RequestRUN(APP_MODE_USER);
      Rte_Write_modeRequestPort_ComMMode_LOCALCAN_ComMMode_LOCALCAN(COMM_MODE_FULL_COM);  // int 2u
      Rte_Write_modeRequestPort_ComMMode_BCAN_ComMMode_BCAN(COMM_MODE_FULL_COM);          // int 2u
      AppMode_GucTestCase = 0;
      break;
    case 2: /* ECU OFF Request */
      Rte_Write_modeRequestPort_ComMMode_LOCALCAN_ComMMode_LOCALCAN(COMM_MODE_NO_COM);    // int 0u
      Rte_Write_modeRequestPort_ComMMode_BCAN_ComMMode_BCAN(COMM_MODE_NO_COM);            // int 0u
      Rte_Call_clientPort_StateRequest_RequestOff(APP_MODE_USER);
      AppMode_GucTestCase = 0;
      break;
    case 3: /* ECU RESET Request */
      Rte_Write_modeRequestPort_ComMMode_LOCALCAN_ComMMode_LOCALCAN(COMM_MODE_NO_COM);    // int 0u
      Rte_Write_modeRequestPort_ComMMode_BCAN_ComMMode_BCAN(COMM_MODE_NO_COM);            // int 0u
      Rte_Call_clientPort_StateRequest_RequestReset(APP_MODE_USER);
      AppMode_GucTestCase = 0;
      break;
    case 4: /* NO COM Request */
      Rte_Write_modeRequestPort_ComMMode_LOCALCAN_ComMMode_LOCALCAN(COMM_MODE_NO_COM);    // int 0u
      Rte_Write_modeRequestPort_ComMMode_BCAN_ComMMode_BCAN(COMM_MODE_NO_COM);            // int 0u
      AppMode_GucTestCase = 0;
      break;
    case 5: /* Sleep Request */
      /* Check that All CommMode are NO_COM) */
      Rte_Call_clientPort_StateRequest_RequestSleep(APP_MODE_USER);
      AppMode_GucTestCase = 0;
      break;


    default:
      break;
    }
}
#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"
void Set_No_COM_Req(void);
void Set_No_COM_Req(void)
{
  if(GetX(kb_NFC_OPTION)==On)
  {
    Rte_Write_modeRequestPort_ComMMode_LOCALCAN_ComMMode_LOCALCAN(COMM_MODE_NO_COM);      // int 0u
  }
  Rte_Write_modeRequestPort_ComMMode_BCAN_ComMMode_BCAN(COMM_MODE_NO_COM);              // int 0u
  AppMode_GucTestCase = 0;
}
void Set_Full_COM_Req(void);
void Set_Full_COM_Req(void)
{
  Rte_Call_clientPort_StateRequest_RequestRUN(APP_MODE_USER);
  if(GetX(kb_NFC_OPTION)==On)
  {
    Rte_Write_modeRequestPort_ComMMode_LOCALCAN_ComMMode_LOCALCAN(COMM_MODE_FULL_COM);    // int 2u
  }
  Rte_Write_modeRequestPort_ComMMode_BCAN_ComMMode_BCAN(COMM_MODE_FULL_COM);            // int 2u
  AppMode_GucTestCase = 0;;
}


