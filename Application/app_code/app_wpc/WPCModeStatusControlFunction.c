/****************************************************************************************
* Project         : WPC                                 *
* File Name       :                                   *
* Compiler        : IAR                                 *
* Author          : Limjo Hong                                            *
* Created at      : 2018-05-18                                                      *
* Code Editor     : Source Insight                            *
* Revision        : 0.1                                 *
* Copyright       : (c) Copyright Seoyon Electronics Co.Ltd. All Rights Reserved    *
* Description     :                                   *
****************************************************************************************/


/*******************************************************************************
* Include Headers                                                              *
*******************************************************************************/
#include "WPCType.h"
#include "Define.h"
#include "WPCTimer.h"
#include "Data.h"
#include "Rte_SWC_Input.h"

#include "app_can_input_type.h"
#include "app_can_input.h"
#include "app_input_type.h"
#include "app_input.h"
#include "app_output_type.h"
#include "app_output.h"

#include "WPCLogicControl.h"
#include "WPCI2CControl.h"
#include "Superstate_api.h"
#include "WPCPWMControl.h"

/*******************************************************************************
* Define Functions                                                             *
*******************************************************************************/
static void WPCMode_Init_en(void);
static tSTATE* WPCMode_Init_init(void);
static void WPCMode_Init_du(void);
static void WPCMode_Init_ex(void);
static u8 WPCMode_Init_run(void);

static void WPCMode_Disable_en(void);
static tSTATE* WPCMode_Disable_init(void);
static void WPCMode_Disable_du(void);
static void WPCMode_Disable_ex(void);
static u8 WPCMode_Disable_run(void);

static void WPCMode_Enable_en(void);
static tSTATE* WPCMode_Enable_init(void);
static void WPCMode_Enable_du(void);
static void WPCMode_Enable_ex(void);
static u8 WPCMode_Enable_run(void);

static void WPCMode_Off_en(void);
static tSTATE* WPCMode_Off_init(void);
static void WPCMode_Off_du(void);
static void WPCMode_Off_ex(void);
static u8 WPCMode_Off_run(void);

static void WPCMode_NFC_en(void);
static tSTATE* WPCMode_NFC_init(void);
static void WPCMode_NFC_du(void);
static void WPCMode_NFC_ex(void);
static u8 WPCMode_NFC_run(void);

static void WPCMode_Stop_en(void);
static tSTATE* WPCMode_Stop_init(void);
static void WPCMode_Stop_du(void);
static void WPCMode_Stop_ex(void);
static u8 WPCMode_Stop_run(void);

static void WPCMode_Run_en(void);
static tSTATE* WPCMode_Run_init(void);
static void WPCMode_Run_du(void);
static void WPCMode_Run_ex(void);
static u8 WPCMode_Run_run(void);

static void LeavingPhone_Warning_en(void);
static tSTATE* LeavingPhone_Warning_init(void);
static void LeavingPhone_Warning_du(void);
static void LeavingPhone_Warning_ex(void);
static u8 LeavingPhone_Warning_run(void);

static void LeavingPhone_NoWarning_en(void);
static tSTATE* LeavingPhone_NoWarning_init(void);
static void LeavingPhone_NoWarning_du(void);
static void LeavingPhone_NoWarning_ex(void);
static u8 LeavingPhone_NoWarning_run(void);

static void WPCStop_TempErr_en(void);
static tSTATE* WPCStop_TempErr_init(void);
static void WPCStop_TempErr_du(void);
static void WPCStop_TempErr_ex(void);
static u8 WPCStop_TempErr_run(void);

static void WPCStop_NotTempErr_en(void);
static tSTATE* WPCStop_NotTempErr_init(void);
static void WPCStop_NotTempErr_du(void);
static void WPCStop_NotTempErr_ex(void);
static u8 WPCStop_NotTempErr_run(void);

static void WPCRun_Standby_en(void);
static tSTATE* WPCRun_Standby_init(void);
static void WPCRun_Standby_du(void);
static void WPCRun_Standby_ex(void);
static u8 WPCRun_Standby_run(void);

static void WPCRun_FODError_en(void);
static tSTATE* WPCRun_FODError_init(void);
static void WPCRun_FODError_du(void);
static void WPCRun_FODError_ex(void);
static u8 WPCRun_FODError_run(void);

static void WPCRun_Charging_en(void);
static tSTATE* WPCRun_Charging_init(void);
static void WPCRun_Charging_du(void);
static void WPCRun_Charging_ex(void);
static u8 WPCRun_Charging_run(void);

static void WPCRun_ChargingComplete_en(void);
static tSTATE* WPCRun_ChargingComplete_init(void);
static void WPCRun_ChargingComplete_du(void);
static void WPCRun_ChargingComplete_ex(void);
static u8 WPCRun_ChargingComplete_run(void);

/*******************************************************************************
* Define Constant and Macro                                                    *
*******************************************************************************/
static const tSTATE kWPCMode_Init = 
{
	WPCMode_Init_en,
	WPCMode_Init_init,
	WPCMode_Init_du,
	WPCMode_Init_ex,
	WPCMode_Init_run,
	NULL							/* Misra Coding Rule 11.9 : NULL -> V_NULL */
};

static const tSTATE kWPCMode_Disable = 
{
	WPCMode_Disable_en,
	WPCMode_Disable_init,
	WPCMode_Disable_du,
	WPCMode_Disable_ex,
	WPCMode_Disable_run,
	NULL
};

static const tSTATE kWPCMode_Enable = 
{
	WPCMode_Enable_en,
	WPCMode_Enable_init, 
	WPCMode_Enable_du, 
	WPCMode_Enable_ex, 
	WPCMode_Enable_run,
	NULL
};

static const tSTATE kWPCMode_Off =
{
	WPCMode_Off_en,
	WPCMode_Off_init,
	WPCMode_Off_du,
	WPCMode_Off_ex,
	WPCMode_Off_run,
	&kWPCMode_Disable
};

static const tSTATE kWPCMode_NFC =
{
	WPCMode_NFC_en,
	WPCMode_NFC_init,
	WPCMode_NFC_du,
	WPCMode_NFC_ex,
	WPCMode_NFC_run,
	&kWPCMode_Disable
};

static const tSTATE kWPCMode_Stop =
{
	WPCMode_Stop_en,
	WPCMode_Stop_init,
	WPCMode_Stop_du,
	WPCMode_Stop_ex,
	WPCMode_Stop_run,
	&kWPCMode_Enable
};

static const tSTATE kWPCMode_Run =
{
	WPCMode_Run_en,
	WPCMode_Run_init,
	WPCMode_Run_du,
	WPCMode_Run_ex,
	WPCMode_Run_run,
	&kWPCMode_Enable
};

static const tSTATE kLeavingPhone_Warning =
{
	LeavingPhone_Warning_en,
	LeavingPhone_Warning_init,
	LeavingPhone_Warning_du,
	LeavingPhone_Warning_ex,
	LeavingPhone_Warning_run,
	&kWPCMode_Off
};

static const tSTATE kLeavingPhone_NoWarning =
{
	LeavingPhone_NoWarning_en,
	LeavingPhone_NoWarning_init,
	LeavingPhone_NoWarning_du,
	LeavingPhone_NoWarning_ex,
	LeavingPhone_NoWarning_run,
	&kWPCMode_Off
};

static const tSTATE kWPCStop_TempErr =
{
	WPCStop_TempErr_en,
	WPCStop_TempErr_init,
	WPCStop_TempErr_du,
	WPCStop_TempErr_ex,
	WPCStop_TempErr_run,
	&kWPCMode_Stop
};

static const tSTATE kWPCStop_NotTempErr =
{
	WPCStop_NotTempErr_en,
	WPCStop_NotTempErr_init,
	WPCStop_NotTempErr_du,
	WPCStop_NotTempErr_ex,
	WPCStop_NotTempErr_run,
	&kWPCMode_Stop
};

static const tSTATE kWPCRun_Standby =
{
	WPCRun_Standby_en,
	WPCRun_Standby_init,
	WPCRun_Standby_du,
	WPCRun_Standby_ex,
	WPCRun_Standby_run,
	&kWPCMode_Run
};

static const tSTATE kWPCRun_FODError =
{
	WPCRun_FODError_en,
	WPCRun_FODError_init,
	WPCRun_FODError_du,
	WPCRun_FODError_ex,
	WPCRun_FODError_run,
	&kWPCMode_Run
};

static const tSTATE kWPCRun_Charging =
{
	WPCRun_Charging_en,
	WPCRun_Charging_init,
	WPCRun_Charging_du,
	WPCRun_Charging_ex,
	WPCRun_Charging_run,
	&kWPCMode_Run
};

static const tSTATE kWPCRun_ChargingComplete =
{
	WPCRun_ChargingComplete_en,
	WPCRun_ChargingComplete_init,
	WPCRun_ChargingComplete_du,
	WPCRun_ChargingComplete_ex,
	WPCRun_ChargingComplete_run,
	&kWPCMode_Run
};

static void Function_WPCWarning(void);
static void Function_LEDErrorBlink(void);
static void FODtoStandbyControl(void);
void Function_ChargingINDColor(void);
void WPCModeStatusControl(void);

typedef enum
{
	StatusControl_Init = 0,
	StatusControl_Operating
}e_WPCModeStatusControl;

/*******************************************************************************
* Declare  Variables                                                           *
*******************************************************************************/
u8 b_BlinkState = (u8)Blink_State_Off;

static u8 b_WarnClearEnable = Off;
static u8 b_FODClearEnable = Off;
static u8 Counter_BlinkCnt = 0;
static u8 b_FODSleepModeClear = Off;	/* 20230528 : When Charging area expier FOD Sleep Mode Clear */
u8 b_ChargingComplete = Off;

static tTimer8	Timer_PhoneLeft = {Off, 0u};				// Timer for No Phone Confirm Check			Max : 500ms
static tTimer8	Timer_PhoneWarningCheck = {Off, 0u};		// Timer for Phone Exist Warning Check		Max : 1000ms
static tTimer16	Timer_PhoneReminderCheck = {Off, 0u};	// Timer for Phone Remider Warning Check	Max : 60000ms
static tTimer8	Timer_WarningComplete = {Off, 0u};		// Timer for Warning Clear Check			Max : 500ms
static tTimer16	Timer_AmberInitial = {Off, 0u};			// Timer for Initial Amber On Check			Max : 3000ms
tTimer8	Timer_AmberINDBlk = {Off, 0u};			// Timer for Amber Blinking					Max : 500ms
static tTimer16 Timer_FODComplete = {Off, 0u};
static tTimer16 Timer_FODCheck = {Off, 0u};
static tTimer8 Timer_PhoneLeftFOD = {Off, 0u};
static tTimer16 Timer_FODSleepOff = {Off, 0u};

static tTimer16 Timer_IPHONECheck = {Off, 0u};
static tTimer8 Timer_IPHONEFODCheck = {Off, 0u};

extern uint8 PhoneRemoveDetected;
u8 PhoneWarningtoFOD = Off;

/*******************************************************************************
* Define Functions                                                             *
*******************************************************************************/
static tSTATE *WPCMode_StatusControl_stateCUR = NULL;

/* State : kWPCMode_Init */
static void WPCMode_Init_en(void)
{
	SetOutput(kC_WPC_PhnLftWrngRWPCSta, (u8)kWPCWarning_Off);
	SetX(kb_WPCPower, Off);
	b_WarnClearEnable = Off;
	b_FODClearEnable = Off;
	SetX(kb_GreenINDCmd, Off);
	SetX(kb_AmberINDCmd, Off);
	b_BlinkState = (u8)Blink_State_Off;
	SetX(kb_BlinkState, Blink_State_Off);
	Counter_BlinkCnt = 0u;
	SetX(kb_ChargingState, Off);
	SetX(kb_FANModeCmd, Off);
	SetX(kb_WPCRunMode, (u8)kRunMode_NONE);
	CancelTimer(Timer_PhoneLeft);
	CancelTimer(Timer_PhoneWarningCheck);
	CancelTimer(Timer_PhoneReminderCheck);
	CancelTimer(Timer_WarningComplete);
	CancelTimer(Timer_AmberINDBlk);
	CancelTimer(Timer_FODComplete);
	CancelTimer(Timer_FODCheck);
	CancelTimer(Timer_PhoneLeftFOD);
}

static tSTATE* WPCMode_Init_init(void)
{
	return NULL;
}

static void WPCMode_Init_du(void)
{
	/* MISRA-C */
}

static void WPCMode_Init_ex(void)
{
	/* MISRA-C */
}

static u8 WPCMode_Init_run(void)
{
	u8 ret = 0u;

	if(GetX(kb_WPCStatus) != (u8)WPCStatus_WPCMode)
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCMode_Disable);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCMode_Disable);
	
		ret = 1u;
	}
	else if(GetX(kb_WPCStatus) == (u8)WPCStatus_WPCMode)
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCMode_Enable);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCMode_Enable);
	
		ret = 1u;
	}
	else
	{
		/* MISRA-C */
	}
	
	return ret;
}

/* State : kWPCMode_Disable */
static void WPCMode_Disable_en(void)
{
	//SetX(kb_WPCRunMode, (u8)kRunMode_STOP);
	SetOutput(kC_WPC_PhnLftWrngRWPCSta, (u8)kWPCWarning_Off);

	SetX(kb_FANModeCmd, Off);
	SetX(kb_GreenINDCmd, Off);
	SetX(kb_AmberINDCmd, Off);
	b_BlinkState = (u8)Blink_State_Off;
	SetX(kb_BlinkState, Blink_State_Off);
	Counter_BlinkCnt = 0u;
	CancelTimer(Timer_AmberINDBlk);
}

static tSTATE* WPCMode_Disable_init(void)
{
	tSTATE *ret_state = NULL;
	
	if((GetX(kb_WPCStatus) == (u8)WPCStatus_NFCMode) ||
	   (GetX(kb_WPCStatus) == (u8)WPCStatus_LPCDMode) ||	/* TSCR-837 : Animation Ind SW */
	   (GetX(kb_WPCStatus) == (u8)WPCStatus_PiccMode))
	{
		WPCMode_StatusControl_stateCUR = &kWPCMode_NFC;
		ret_state = &kWPCMode_NFC;
	}
	else if(GetX(kb_WPCStatus) == (u8)WPCStatus_Off)		// @WPCStatus_Off �� �´� �� ����.
	{
		WPCMode_StatusControl_stateCUR = &kWPCMode_Off;
		ret_state = &kWPCMode_Off;
	}
	else
	{
		/* MISRA-C */
	}
	
	return ret_state;
}

static void WPCMode_Disable_du(void)
{
	/* MISRA-C */
}

static void WPCMode_Disable_ex(void)
{
	b_WarnClearEnable = Off;
	CancelTimer(Timer_PhoneLeft);
	CancelTimer(Timer_PhoneWarningCheck);
	CancelTimer(Timer_PhoneReminderCheck);
	CancelTimer(Timer_WarningComplete);
}

static u8 WPCMode_Disable_run(void)
{
	u8 ret = 0u;
	
	if(GetX(kb_WPCStatus) == (u8)WPCStatus_WPCMode)
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCMode_Enable);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCMode_Enable);
		ret = 1u;
	}
	
	return ret;
}

/* State : kWPCMode_Enable */
static void WPCMode_Enable_en(void)
{
	SetX(kb_WPCPower, On);
}

static tSTATE* WPCMode_Enable_init(void)
{
	tSTATE *ret_state = NULL;
	
	WPCMode_StatusControl_stateCUR = &kWPCMode_Stop;
	ret_state = &kWPCMode_Stop;
		
	return ret_state;
}

static void WPCMode_Enable_du(void)
{
	/* MISRA-C */
}

static void WPCMode_Enable_ex(void)
{
	/* MISRA-C */
}

static u8 WPCMode_Enable_run(void)
{
	u8 ret = 0u;
	
	if(GetX(kb_WPCStatus) != (u8)WPCStatus_WPCMode)
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCMode_Disable);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCMode_Disable);	
		ret = 1u;
	}
	
	return ret;
}

/* State : kWPCMode_Off */
static void WPCMode_Off_en(void)
{
	/* MISRA-C */
}

static tSTATE* WPCMode_Off_init(void)
{
	tSTATE *ret_state = NULL;

	if(IsChgEvt(kb_IGN_IN, Off) ||
	   (GetX(kb_WPCPower) == On))
	{
		WPCMode_StatusControl_stateCUR = &kLeavingPhone_Warning;
		ret_state = &kLeavingPhone_Warning;
	}
	else
	{
		WPCMode_StatusControl_stateCUR = &kLeavingPhone_NoWarning;
		ret_state = &kLeavingPhone_NoWarning;
	}
	
	return ret_state;
}

static void WPCMode_Off_du(void)
{
	/* MISRA-C */
}

static void WPCMode_Off_ex(void)
{
	/* MISRA-C */
}

static u8 WPCMode_Off_run(void)
{
	u8 ret = 0u;
	
	if((GetX(kb_WPCStatus) == (u8)WPCStatus_NFCMode) ||
	   (GetX(kb_WPCStatus) == (u8)WPCStatus_LPCDMode) ||	/* TSCR-837 : Animation Ind SW */
	   (GetX(kb_WPCStatus) == (u8)WPCStatus_PiccMode))
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCMode_NFC);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCMode_NFC);	
		ret = 1u;
	}
	
	return ret;
}

/* State : kWPCMode_NFC */
static void WPCMode_NFC_en(void)
{
	SetX(kb_WPCPower, Off);
	b_WarnClearEnable = Off;
	b_FODClearEnable = Off;
	SetX(kb_WPCRunMode, (u8)kRunMode_STOP);
	CancelTimer(Timer_PhoneLeft);
	CancelTimer(Timer_PhoneWarningCheck);
	CancelTimer(Timer_PhoneReminderCheck);
	CancelTimer(Timer_WarningComplete);
}

static tSTATE* WPCMode_NFC_init(void)
{
	return NULL;
}

static void WPCMode_NFC_du(void)
{
	/* MISRA-C */
}

static void WPCMode_NFC_ex(void)
{
	/* MISRA-C */
}

static u8 WPCMode_NFC_run(void)
{
	u8 ret = 0u;

	if(GetX(kb_WPCStatus) == (u8)WPCStatus_Off)		/* TSCR-837 : Animation Ind SW */
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCMode_Off);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCMode_Off);
		ret = 1u;
	}
	return ret;
}

/* State : kWPCMode_Stop */
static void WPCMode_Stop_en(void)
{
	SetX(kb_FANModeCmd, Off);
	SetX(kb_GreenINDCmd, Off);
	SetX(kb_WPCRunMode, (u8)kRunMode_STOP);
}

static tSTATE* WPCMode_Stop_init(void)
{
	tSTATE *ret_state = NULL;
	
	if(GetX(kb_TemperatureFault) == On)
	{
		WPCMode_StatusControl_stateCUR = &kWPCStop_TempErr;
		ret_state = &kWPCStop_TempErr;
	}
	else
	{
		WPCMode_StatusControl_stateCUR = &kWPCStop_NotTempErr;
		ret_state = &kWPCStop_NotTempErr;
	}
	
	return ret_state;
}

static void WPCMode_Stop_du(void)
{
	/* MISRA-C */
}

static void WPCMode_Stop_ex(void)
{
	/* MISRA-C */
}

static u8 WPCMode_Stop_run(void)
{
	u8 ret = 0u;
	
	if((GetX(kb_DeviceState) == (u8)DeviceStates_Full_Charge) &&
		(GetX(kb_LFState) == (u8)LF_OFF) &&
		(GetX(kb_CurrentFault) == Off) &&
		(GetX(kb_TemperatureFault) == Off) &&
		(GetX(kb_TempSensorFault) == Off) &&
		(StateOperatingVoltage == OperatingVoltageState_Normal))
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCRun_ChargingComplete);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCRun_ChargingComplete);
		ret = 1u;
	}
	else if((GetX(kb_DeviceState) == (u8)DeviceStates_Charging) &&
			(GetX(kb_LFState) == (u8)LF_OFF) &&
			(GetX(kb_CurrentFault) == Off) &&
			(GetX(kb_TemperatureFault) == Off) &&
			(GetX(kb_TempSensorFault) == Off) &&
			(StateOperatingVoltage == OperatingVoltageState_Normal))
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCRun_Charging);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCRun_Charging);
		ret = 1u;
	}
	else
	{
		/* MISRA-C */
	}
	
	return ret;
}

/* State : kWPCMode_Run */
static void WPCMode_Run_en(void)
{
	SetX(kb_WPCRunMode, (u8)kRunMode_RUN);
	SetX(kb_TX_Fault_Reason, (u8)TX_Status_OK);
}

static tSTATE* WPCMode_Run_init(void)
{
	tSTATE *ret_state = NULL;
	
	WPCMode_StatusControl_stateCUR = &kWPCRun_Standby;
	ret_state = &kWPCRun_Standby;

	return ret_state;
}

static void WPCMode_Run_du(void)
{
	/* MISRA-C */
}

static void WPCMode_Run_ex(void)
{
	SetX(kb_DeviceState, (u8)DeviceStates_Init);
	SetX(kb_ChargingState, Off);
	SetX(kb_FANModeCmd, Off);
}

static u8 WPCMode_Run_run(void)
{
	u8 ret = 0u;

	if((GetX(kb_LFState) == (u8)LF_ON) ||
		(GetX(kb_CurrentFault) == On) ||
		(GetX(kb_TempSensorFault) == On) ||
		(GetX(kb_TemperatureFault) == On) ||
		(StateOperatingVoltage != OperatingVoltageState_Normal))		// 20180716_�������� ����
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCMode_Stop);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCMode_Stop);	
		ret = 1u;
	}
	
	return ret;
}

/* State : kLeavingPhone_Warning */
static void LeavingPhone_Warning_en(void)
{
	b_WarnClearEnable = Off;
	StartTimer(Timer_PhoneWarningCheck);
	SetX(kb_WPCRunMode, (u8)kRunMode_RX_DETECT);
	Function_WPCWarning();
}

static tSTATE* LeavingPhone_Warning_init(void)
{
	return NULL;
}

static void LeavingPhone_Warning_du(void)
{
	Function_WPCWarning();
}

static void LeavingPhone_Warning_ex(void)
{
	SetOutput(kC_WPC_PhnLftWrngRWPCSta, (u8)kWPCWarning_Off);		/* Function Set 11 */
}

static u8 LeavingPhone_Warning_run(void)
{
	return 0u;
}

/* State : kLeavingPhone_NoWarning */
static void LeavingPhone_NoWarning_en(void)
{
	/* MISRA-C */
}

static tSTATE* LeavingPhone_NoWarning_init(void)
{
	return NULL;
}

static void LeavingPhone_NoWarning_du(void)
{
	/* MISRA-C */
}

static void LeavingPhone_NoWarning_ex(void)
{
	/* MISRA-C */
}

static u8 LeavingPhone_NoWarning_run(void)
{
	return 0u;
}

/* State : kWPCMode_TempErr */
static void WPCStop_TempErr_en(void)
{
	SetOutput(kC_WPC_PhnLftWrngRWPCSta, (u8)kWPCWarning_Error);
	b_BlinkState = (u8)Blink_State_Off;
	SetX(kb_BlinkState, Blink_State_Off);
	Counter_BlinkCnt = 0u;
	//SetX(kb_AmberINDCmd, On);
	Function_LEDErrorBlink();
}

static tSTATE* WPCStop_TempErr_init(void)
{
	return NULL;
}

static void WPCStop_TempErr_du(void)
{
	Function_LEDErrorBlink();
}

static void WPCStop_TempErr_ex(void)
{
	b_BlinkState = (u8)Blink_State_Off;
	SetX(kb_BlinkState, Blink_State_Off);
	Counter_BlinkCnt = 0u;
	CancelTimer(Timer_AmberINDBlk);
}

static u8 WPCStop_TempErr_run(void)
{
	u8 ret = 0u;

	if(GetX(kb_TemperatureFault) == Off)		/* 20201203 SCR-200121-006 */
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCStop_NotTempErr);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCStop_NotTempErr);
		ret = 1u;
	}
	
	return ret;
}

/* State : kWPCMode_NotTempErr */
static void WPCStop_NotTempErr_en(void)
{
	SetOutput(kC_WPC_PhnLftWrngRWPCSta, (u8)kWPCWarning_Off);
	SetX(kb_AmberINDCmd, Off);
}

static tSTATE* WPCStop_NotTempErr_init(void)
{
	return NULL;
}

static void WPCStop_NotTempErr_du(void)
{
	/* MISRA-C */
}

static void WPCStop_NotTempErr_ex(void)
{
	/* MISRA-C */
}

static u8 WPCStop_NotTempErr_run(void)
{
	u8 ret = 0u;
	
	if(GetX(kb_TemperatureFault) == On)
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCStop_TempErr);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCStop_TempErr);
		ret = 1u;
	}
	else if((GetX(kb_LFState) == (u8)LF_OFF) &&
		(GetX(kb_CurrentFault) == Off) &&
		(GetX(kb_TempSensorFault) == Off) &&
		(StateOperatingVoltage == OperatingVoltageState_Normal))		// 20180716_�������� ����
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCMode_Run);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCMode_Run);
		ret = 1u;
	}
	else
	{
		/* MISRA-C */
	}
	
	return ret;
}

/* State : kWPCMode_Standby */
static void WPCRun_Standby_en(void)
{
	SetOutput(kC_WPC_PhnLftWrngRWPCSta, (u8)kWPCWarning_Off);
	SetX(kb_GreenINDCmd, Off);
	SetX(kb_AmberINDCmd, Off);
	SetX(kb_FANModeCmd, Off);
	SetX(kb_ChargingState, Off);
}

static tSTATE* WPCRun_Standby_init(void)
{
	return NULL;
}

static void WPCRun_Standby_du(void)
{
	/* MISRA-C */
}

static void WPCRun_Standby_ex(void)
{
	/* MISRA-C */
}

static u8 WPCRun_Standby_run(void)
{
	u8 ret = 0u;
	
	if(GetX(kb_DeviceState) == (u8)DeviceStates_FODError)
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCRun_FODError);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCRun_FODError);
		ret = 1u;
	}
	else if(GetX(kb_DeviceState) == (u8)DeviceStates_Charging)
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCRun_Charging);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCRun_Charging);
		ret = 1u;
	}
	else if(GetX(kb_DeviceState) == (u8)DeviceStates_Full_Charge)
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCRun_ChargingComplete);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCRun_ChargingComplete);
		ret = 1u;
	}
	else
	{
		/* MISRA-C */
	}
 
	return ret;
}

/* State : kWPCMode_FODError */
static void WPCRun_FODError_en(void)
{
	StartTimer(Timer_FODComplete);
	StartTimer(Timer_FODCheck);
	SetOutput(kC_WPC_PhnLftWrngRWPCSta, (u8)kWPCWarning_Error);
	SetX(kb_WPCRunMode, (u8)kRunMode_RX_DETECT);
	SetX(kb_GreenINDCmd, Off);
	SetX(kb_FANModeCmd, Off);
	SetX(kb_ChargingState, Off);
	b_BlinkState = (u8)Blink_State_Off;
	SetX(kb_BlinkState, Blink_State_Off);
	Counter_BlinkCnt = 0u;
	b_FODClearEnable = Off;
	//SetX(kb_AmberINDCmd, On);
	Function_LEDErrorBlink();
	FODtoStandbyControl();
}

static tSTATE* WPCRun_FODError_init(void)
{
	return NULL;
}

static void WPCRun_FODError_du(void)
{
	Function_LEDErrorBlink();
	FODtoStandbyControl();
}

static void WPCRun_FODError_ex(void)
{
	b_BlinkState = (u8)Blink_State_Off;
	SetX(kb_BlinkState, Blink_State_Off);
	Counter_BlinkCnt = 0u;
	CancelTimer(Timer_AmberINDBlk);
	CancelTimer(Timer_FODComplete); 
	SetX(kb_WPCRunMode, (u8)kRunMode_RUN);
	
}

static u8 WPCRun_FODError_run(void)
{
	u8 ret = 0u;

	if((GetX(kb_DeviceState) == (u8)DeviceStates_Standby) ||			/* 20201203 SCR-200121-006 */
		(GetX(kb_DeviceState) == (u8)DeviceStates_Init))
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCRun_Standby);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCRun_Standby);
		ret = 1u;
	}

	else if(GetX(kb_DeviceState) == (u8)DeviceStates_Charging)		/* 20201203 SCR-200121-006 */
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCRun_Charging);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCRun_Charging);
		ret = 1u;
	}

	else if(GetX(kb_DeviceState) == (u8)DeviceStates_Full_Charge)		/* 20201203 SCR-200121-006 */
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCRun_ChargingComplete);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCRun_ChargingComplete);
		ret = 1u;
	}
	else
	{
		/* MISRA-C */
	}
 
	return ret;
}

/* State : kWPCMode_Charging */
static void WPCRun_Charging_en(void)
{
	SetOutput(kC_WPC_PhnLftWrngRWPCSta, (u8)kWPCWarning_Charging);
	SetX(kb_FANModeCmd, On);
	SetX(kb_ChargingState, On);
	b_ChargingComplete = Off;
	Function_ChargingINDColor();
}

static tSTATE* WPCRun_Charging_init(void)
{
	return NULL;
}

static void WPCRun_Charging_du(void)
{
	Function_ChargingINDColor();
}

static void WPCRun_Charging_ex(void)
{
	/* MISRA-C */
}

static u8 WPCRun_Charging_run(void)
{
	u8 ret = 0u;
	
	if((GetX(kb_DeviceState) == (u8)DeviceStates_Standby) ||
		(GetX(kb_DeviceState) == (u8)DeviceStates_Init))
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCRun_Standby);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCRun_Standby);
		ret = 1u;
	}
	else if(GetX(kb_DeviceState) == (u8)DeviceStates_FODError)
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCRun_FODError);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCRun_FODError);
		ret = 1u;
	}
	else if(GetX(kb_DeviceState) == (u8)DeviceStates_Full_Charge)
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCRun_ChargingComplete);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCRun_ChargingComplete);
		ret = 1u;
	}
	else
	{
		/* MISRA-C */
	}
 
	return ret;
}

/* State : kWPCMode_ChargingComplete */
static void WPCRun_ChargingComplete_en(void)
{
	SetOutput(kC_WPC_PhnLftWrngRWPCSta, (u8)kWPCWarning_ChargingComplete);
	SetX(kb_GreenINDCmd, On);
	SetX(kb_AmberINDCmd, Off);
	SetX(kb_FANModeCmd, On);
	SetX(kb_ChargingState, On);
	b_ChargingComplete = On;
}

static tSTATE* WPCRun_ChargingComplete_init(void)
{
	return NULL;
}

static void WPCRun_ChargingComplete_du(void)
{
	/* MISRA-C */
}

static void WPCRun_ChargingComplete_ex(void)
{
	b_ChargingComplete = Off;
}

static u8 WPCRun_ChargingComplete_run(void)
{
	u8 ret = 0u;
	
	if((GetX(kb_DeviceState) == (u8)DeviceStates_Standby) ||
		(GetX(kb_DeviceState) == (u8)DeviceStates_Init))
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCRun_Standby);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCRun_Standby);
		ret = 1u;
	}
	else if(GetX(kb_DeviceState) == (u8)DeviceStates_FODError)
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCRun_FODError);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCRun_FODError);
		ret = 1u;
	}
	else if(GetX(kb_DeviceState) == (u8)DeviceStates_Charging)
	{
		WPCMode_StatusControl_stateCUR = transition_exit(WPCMode_StatusControl_stateCUR, &kWPCRun_Charging);
		WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCRun_Charging);
		ret = 1u;
	}
	else
	{
		/* MISRA-C */
	}
 
	return ret;
}


u8 IS_IPHONECheck = 0u;
u8 is_iphone_cnt = 0u;
static void Function_WPCWarning(void)
{
	if((GetX(kb_WPCSWOption) == (u8)kWPCOnOff_Off) ||
		(StateOperatingVoltage != OperatingVoltageState_Normal) ||
		((Timer_PhoneLeft.run == On) &&		/* Check Timer Running */
		(Timer_PhoneLeft.time >= Par_PhoneLeftConfirm)) ||
		((Timer_PhoneWarningCheck.run == On) &&		/* Check Timer Running */
		(Timer_PhoneWarningCheck.time >= Par_PhoneCheckTime) &&
		(GetX(kb_WPCPhoneExist) == Off)))
	{
		SetOutput(kC_WPC_PhnLftWrngRWPCSta, (u8)kWPCWarning_Off);
		SetX(kb_WPCPower, Off);
		SetX(kb_DrDoorPhnLftHoldComplete, On);
		b_WarnClearEnable = Off;
		SetX(kb_WPCRunMode, (u8)kRunMode_STOP);
		CancelTimer(Timer_PhoneLeft);
		CancelTimer(Timer_PhoneWarningCheck);
		CancelTimer(Timer_PhoneReminderCheck);
		CancelTimer(Timer_WarningComplete);
		CancelTimer(Timer_IPHONECheck);
		IS_IPHONECheck = Off;
		is_iphone_cnt = 0u;
		
	}
	else
	{
		if((b_WarnClearEnable == On) &&
			IsChgEvt(kb_WPCPhoneExist, Off))
		{
			StartTimer(Timer_PhoneLeft);
			StartTimer(Timer_IPHONECheck);
		}
		else if((Timer_PhoneLeft.run == On) &&
				(GetX(kb_WPCPhoneExist) == On))
		{
			is_iphone_cnt = 0u;
			CancelTimer(Timer_PhoneLeft);
			CancelTimer(Timer_IPHONECheck);
			IS_IPHONECheck = Off;
		}
	  else if(Timer_IPHONECheck.time >= Time_ms(100))
		{
			SetX(kb_WPCRunMode, (u8)kRunMode_STOP);
			CancelTimer(Timer_IPHONECheck);
			IS_IPHONECheck = On;
		}
		else if(IS_IPHONECheck == On)
		{
			SetX(kb_WPCRunMode, (u8)kRunMode_RX_DETECT);
			IS_IPHONECheck = Off;
		}
		else
		{
			/* MISRA-C */
		}
		
		if((Timer_PhoneWarningCheck.time >= Par_IdleConfirm) &&
			(Timer_PhoneWarningCheck.time <= Par_PhoneCheckTime) &&
			(GetX(kb_WPCPhoneExist) == On))
		{
			SetOutput(kC_WPC_PhnLftWrngRWPCSta, (u8)kWPCWarning_CellphoneOnThePad);
			b_WarnClearEnable = On;
			b_FODClearEnable = Off;
			PhoneWarningtoFOD = On;
			CancelTimer(Timer_PhoneWarningCheck);
			StartTimer(Timer_PhoneReminderCheck);
		}
		else if((Timer_PhoneReminderCheck.time >= Par_PhoneLeftWarning) &&
				(b_WarnClearEnable == On) &&
				(GetX(kb_WPCPhoneExist) == On))
		{
			if((GetX(kC_Latch_TypeOption_DRV) == (u8)kLatch_TypeOption_On) &&
				((GetX(kC_Warn_DrvDrSwSta_SBCM) == On) ||
				 (GetX(kC_Warn_AsstDrSwSta_SBCM) == On)))
			{
				SetOutput(kC_WPC_PhnLftWrngRWPCSta, (u8)kWPCWarning_Off);
				SetX(kb_WPCPower, Off);
				b_WarnClearEnable = Off;
				SetX(kb_WPCRunMode, (u8)kRunMode_STOP);
				CancelTimer(Timer_PhoneReminderCheck);
				SetX(kb_DrDoorPhnLftHoldComplete, On);			
			}
			else if((GetX(kC_Latch_TypeOption_DRV) != (u8)kLatch_TypeOption_On) &&
					((GetX(kC_Warn_DrvDrSwSta) == On) ||
					 (GetX(kC_Warn_AsstDrSwSta) == On)))
			{
				SetOutput(kC_WPC_PhnLftWrngRWPCSta, (u8)kWPCWarning_Off);
				SetX(kb_WPCPower, Off);
				b_WarnClearEnable = Off;
				SetX(kb_WPCRunMode, (u8)kRunMode_STOP);
				CancelTimer(Timer_PhoneReminderCheck);		
				SetX(kb_DrDoorPhnLftHoldComplete, On);		
			}
			else
			{
				SetOutput(kC_WPC_PhnLftWrngRWPCSta, (u8)kWPCWarning_CellphoneReminder);
				CancelTimer(Timer_PhoneReminderCheck);
				StartTimer(Timer_WarningComplete);
			}
		}
		else if((Timer_WarningComplete.time >= Par_PhoneReminderWarning) &&
				(b_WarnClearEnable == On) &&
				(GetX(kb_WPCPhoneExist) == On))
		{
			SetOutput(kC_WPC_PhnLftWrngRWPCSta, (u8)kWPCWarning_Off);
			SetX(kb_WPCPower, Off);
			b_WarnClearEnable = Off;
			SetX(kb_WPCRunMode, (u8)kRunMode_STOP);
			CancelTimer(Timer_WarningComplete);
			SetX(kb_DrDoorPhnLftHoldComplete, On);
		}
		else
		{
			/* MISRA-C */
		}
	}
}

static void Function_LEDErrorBlink(void)
{
	if(GetX(kb_CmdAmberSync) == Off)
	{
		if((b_BlinkState != (u8)Blink_State_Complete) &&
		   (Counter_BlinkCnt >= Par_ErrorHoldingCnt))
		{
			b_BlinkState = (u8)Blink_State_Complete;
			SetX(kb_BlinkState, Blink_State_Complete);
			SetX(kb_AmberINDCmd, Off);
			CancelTimer(Timer_AmberINDBlk);
		}
		else if(Counter_BlinkCnt >= Par_ErrorHoldingCnt)
		{
			b_BlinkState = (u8)Blink_State_Complete;
			SetX(kb_BlinkState, Blink_State_Complete);
			SetX(kb_AmberINDCmd, Off);
			CancelTimer(Timer_AmberINDBlk);
		}
		else if((b_BlinkState != (u8)Blink_State_Complete) &&
			    (Timer_AmberINDBlk.run == Off))
		{
			b_BlinkState = (u8)Blink_State_On;
			SetX(kb_BlinkState, Blink_State_On);
			SetX(kb_AmberINDCmd, On);
			StartTimer(Timer_AmberINDBlk);
		}
		else if((GetX(kC_USM_CmdWPCIndSta) == kWPCAnimation_Type_1) &&
				(b_BlinkState == (u8)Blink_State_Off) &&
				(Timer_AmberINDBlk.time >= Par_LEDBlinkTime))
		{
			b_BlinkState = (u8)Blink_State_On;
			SetX(kb_BlinkState, Blink_State_On);
			SetX(kb_AmberINDCmd, On);
			StartTimer(Timer_AmberINDBlk);
		}
		else if((GetX(kC_USM_CmdWPCIndSta) == kWPCAnimation_Type_1) &&
				(b_BlinkState == (u8)Blink_State_On) &&
				(Timer_AmberINDBlk.time >= Par_LEDBlinkTime))
		{
			b_BlinkState = (u8)Blink_State_Off;
			SetX(kb_BlinkState, Blink_State_Off);
			Counter_BlinkCnt++;
			SetX(kb_AmberINDCmd, Off);
			StartTimer(Timer_AmberINDBlk);
		}
		else if((GetX(kC_USM_CmdWPCIndSta) == kWPCAnimation_Type_2) &&
				(IsChgEvt(kb_RWPCIndCmdState, WPCIndCmdState_ErrorFadeIn)) &&
				(b_BlinkState == (u8)Blink_State_Off))
		{
			b_BlinkState = (u8)Blink_State_On;
			SetX(kb_BlinkState, Blink_State_On);
			SetX(kb_AmberINDCmd, On);
			StartTimer(Timer_AmberINDBlk);
		}
		else if((GetX(kC_USM_CmdWPCIndSta) == kWPCAnimation_Type_2) &&
				(IsChgEvt(kb_RWPCIndCmdState, WPCIndCmdState_ErrorFadeOut)) &&
				(b_BlinkState == (u8)Blink_State_On))
		{
			b_BlinkState = (u8)Blink_State_Off;
			SetX(kb_BlinkState, Blink_State_Off);
			Counter_BlinkCnt++;
			SetX(kb_AmberINDCmd, Off);
			StartTimer(Timer_AmberINDBlk);
		}
	}
	else if(GetX(kb_CmdAmberSync) == On)
	{
		if((b_BlinkState != (u8)Blink_State_Complete) &&
		   (Counter_BlinkCnt >= Par_ErrorHoldingCnt))
		{
			b_BlinkState = (u8)Blink_State_Complete;
			SetX(kb_BlinkState, Blink_State_Complete);
			SetX(kb_AmberINDCmd, Off);
			CancelTimer(Timer_AmberINDBlk);
		}
		else if(Counter_BlinkCnt >= Par_ErrorHoldingCnt)
		{
			b_BlinkState = (u8)Blink_State_Complete;
			SetX(kb_BlinkState, Blink_State_Complete);
			SetX(kb_AmberINDCmd, Off);
			CancelTimer(Timer_AmberINDBlk);
		}
		else if((b_BlinkState != (u8)Blink_State_Complete) &&
			    (Timer_AmberINDBlk.run == Off))
		{
			b_BlinkState = (u8)Blink_State_On;
			SetX(kb_BlinkState, Blink_State_On);
			SetX(kb_AmberINDCmd, On);
			StartTimer(Timer_AmberINDBlk);
		}
		else if((GetX(kC_USM_CmdWPCIndSta) == kWPCAnimation_Type_1) &&
				(b_BlinkState == (u8)Blink_State_Off) &&
				(Timer_AmberINDBlk.time >= Par_LEDBlinkTime))
		{
			b_BlinkState = (u8)Blink_State_On;
			SetX(kb_BlinkState, Blink_State_On);
			SetX(kb_AmberINDCmd, On);
			StartTimer(Timer_AmberINDBlk);
		}
		else if((GetX(kC_USM_CmdWPCIndSta) == kWPCAnimation_Type_1) &&
				(b_BlinkState == (u8)Blink_State_On) &&
				(Timer_AmberINDBlk.time >= Par_LEDBlinkTime))
		{
			b_BlinkState = (u8)Blink_State_Off;
			SetX(kb_BlinkState, Blink_State_Off);
			Counter_BlinkCnt++;
			SetX(kb_AmberINDCmd, Off);
			StartTimer(Timer_AmberINDBlk);
		}
		else if((GetX(kC_USM_CmdWPCIndSta) == kWPCAnimation_Type_2) &&
				(IsChgEvt(kb_RWPCIndCmdState, WPCIndCmdState_ErrorFadeIn)) &&
				(b_BlinkState == (u8)Blink_State_Off))
		{
			b_BlinkState = (u8)Blink_State_On;
			SetX(kb_BlinkState, Blink_State_On);
			SetX(kb_AmberINDCmd, On);
			//StartTimer(Timer_AmberINDBlk);
		}
		else if((GetX(kC_USM_CmdWPCIndSta) == kWPCAnimation_Type_2) &&
				(IsChgEvt(kb_RWPCIndCmdState, WPCIndCmdState_ErrorFadeOut)) &&
				(b_BlinkState == (u8)Blink_State_On))
		{
			b_BlinkState = (u8)Blink_State_Off;
			SetX(kb_BlinkState, Blink_State_Off);
			Counter_BlinkCnt++;
			SetX(kb_AmberINDCmd, Off);
			//StartTimer(Timer_AmberINDBlk);
		}
	}
}

u8 is_IPhone_FOD_Check = 0u;
u8 is_IPhone_FOD_Check_cnt = 0u;

static void FODtoStandbyControl(void)
{
	if(((Timer_PhoneLeftFOD.run == On) &&
	   (Timer_PhoneLeftFOD.time >= Par_PhoneLeftConfirm) &&
	   (GetX(kb_WPCPhoneExist) == Off)) ||
	    ((Timer_FODSleepOff.run == On) &&		/* 20230528 : When Charging area expier FOD Sleep Mode Clear */
	    (Timer_FODSleepOff.time >= Time_sec(1)) &&
	    (b_FODSleepModeClear == On)))
	{
		b_FODClearEnable = Off;
		b_FODSleepModeClear = Off;				/* 20230528 : When Charging area expier FOD Sleep Mode Clear */
		SetX(kb_WPCRunMode, (u8)kRunMode_STOP);
		CancelTimer(Timer_PhoneLeftFOD);
		CancelTimer(Timer_FODCheck);
		CancelTimer(Timer_FODComplete);
		CancelTimer(Timer_FODSleepOff);			/* 20230528 : When Charging area expier FOD Sleep Mode Clear */
		CancelTimer(Timer_IPHONEFODCheck);
		is_IPhone_FOD_Check = Off;				/* 20230721 : Whne Removed on the pad, FOD Check Flag Clear*/
		is_IPhone_FOD_Check_cnt = Off;			/* 20230721 : Whne Removed on the pad, FOD Check count Clear*/
	}
	else
	{
		if((b_FODClearEnable == On) &&
		   IsChgEvt(kb_WPCPhoneExist, Off))
		{
			StartTimer(Timer_PhoneLeftFOD);
			StartTimer(Timer_IPHONEFODCheck);
		}
		else if((Timer_PhoneLeftFOD.run == On) &&
				(GetX(kb_WPCPhoneExist) == On))
		{
			CancelTimer(Timer_PhoneLeftFOD);
			CancelTimer(Timer_IPHONEFODCheck);
			is_IPhone_FOD_Check = Off;
		}
		if(Timer_IPHONEFODCheck.time >= Time_ms(100))
		{
			SetX(kb_WPCRunMode, (u8)kRunMode_STOP);
			CancelTimer(Timer_IPHONEFODCheck);
			is_IPhone_FOD_Check = On;
		}
		else if(is_IPhone_FOD_Check == On)
		{
			SetX(kb_WPCRunMode, (u8)kRunMode_RX_DETECT);
			is_IPhone_FOD_Check = Off;
		}
		else
		{
			/* MISRA-C */
		}
		if ((Timer_FODCheck.time >= Par_PhoneCheckTime) &&
			(GetX(kb_WPCPhoneExist) == On))
		{
			b_FODClearEnable = On;
			CancelTimer(Timer_FODCheck);
		}
		else if((Timer_FODCheck.time >= Time_sec(1)) &&		/* 20230528 : When Charging area expier FOD Sleep Mode Clear */
				(GetX(kb_WPCPhoneExist) == Off))
		{
			b_FODSleepModeClear = On;
			CancelTimer(Timer_FODCheck);
			StartTimer(Timer_FODSleepOff);
		}
		else if(Timer_FODComplete.time >= Time_sec(60))
		{
			b_FODClearEnable = Off;
			b_FODSleepModeClear = Off;
			SetX(kb_WPCRunMode, (u8)kRunMode_STOP); 
			CancelTimer(Timer_FODComplete);
			CancelTimer(Timer_FODCheck);
			CancelTimer(Timer_FODSleepOff);
		}
	}
}

void Function_ChargingINDColor(void)
{
	if(GetX(kC_USM_CmdWPCIndSta) == kWPCAnimation_Type_2)
	{
		SetX(kb_GreenINDCmd, On);
		SetX(kb_AmberINDCmd, Off);
	}
	else
	{
		SetX(kb_GreenINDCmd, Off);
		SetX(kb_AmberINDCmd, On);
	}
}

/************************************************************************************************/
/****         Function: WPCModeStatusControl                          */
/****         Content: Figure 25 Front WPC Mode Status Control Function State Chart       */
/****         Called By: 10ms TASK                                */
/****         argument: void                                  */
/****         return value: void                                */
/****     Revision: 2018.05.18 Applied 14th                         */
/************************************************************************************************/
void WPCModeStatusControl(void)
{
  	static e_WPCModeStatusControl sts_WPCModeStatusControl = StatusControl_Init;
	
	UpTimer8(Timer_PhoneLeft);
	UpTimer8(Timer_PhoneWarningCheck);
	UpTimer16(Timer_PhoneReminderCheck);
	UpTimer8(Timer_WarningComplete);
	UpTimer8(Timer_AmberINDBlk);
	UpTimer16(Timer_AmberInitial);
	UpTimer16(Timer_FODComplete);
	UpTimer16(Timer_FODCheck);
	UpTimer8(Timer_PhoneLeftFOD);
	UpTimer16(Timer_FODSleepOff);	/* 20230528 : When Charging area expier FOD Sleep Mode Clear */
	UpTimer16(Timer_IPHONECheck);
	UpTimer8(Timer_IPHONEFODCheck);

	switch(sts_WPCModeStatusControl)
	{
		case StatusControl_Init:
			WPCMode_StatusControl_stateCUR = &kWPCMode_Init;
			WPCMode_StatusControl_stateCUR = transition(WPCMode_StatusControl_stateCUR, &kWPCMode_Init);			
			sts_WPCModeStatusControl = StatusControl_Operating;
			break;

		case StatusControl_Operating:
			(void)CurrentRun(WPCMode_StatusControl_stateCUR);
			break;
			
		default:
			/* MISRA-C */
			break;
	}
}
