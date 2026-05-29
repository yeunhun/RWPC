/*
 * WPCWPCMode.h
 *
 *  Created on: 2017. 9. 13.
 *      Author: Seoyon
 */

#ifndef WPC_LOGICCONTROL_H_
#define WPC_LOGICCONTROL_H_

#include "WPCType.h"


typedef enum
{
	LF_OFF =0,
	LF_ON
}e_LF_State;

typedef enum
{
	LFSearching_Init = 0,
	LFSearching_Off,
	LFSearching_On
}e_PreventionOfSMKLFInterferenceControl;

typedef enum
{
	CurrentError_Off = 0,
	CurrentError_Check,
	CurrentError_Pending,
	CurrentError_Confirmed
}e_CurrentErrorState;

typedef enum
{
	Temperature_Init = 0,
	Temperature_Normal,
	TemperatureError_OnCheck,
	Temperature_FaultOn,
	TemperatureError_OffCheck
}e_OverTempState;

typedef enum
{
	TempSensorError_Init = 0,
	TempSensorError_Off,
	TempSensorError_Check,
	TempSensorError_On
}e_TempSensorErrorState;

typedef enum
{
	Green_LED_OFF = 0,
	Green_LED_ON
}e_GreenLEDstate;

typedef enum
{
	Amber_LED_OFF = 0,
	Amber_LED_ON
}e_AmberLEDstate;

typedef enum // C_IGNSw
{
	IGNSW_KeyOff = 0,
	IGNSW_KeyIN,
	IGNSW_ACC,
	IGNSW_IGN,
	IGNSW_Start
}e_IGNSWFunc;

typedef enum
{
	kNoAction = 0,
	kActiveAction
} e_ActionState;

typedef enum
{
	FAN_Output_Off = 0,
	FAN_Output_On
}e_FANOutputState;

typedef enum
{
	stsNFC_Init = 0, 
	stsNFC_Deactivated, // go to WPC Mode
	stsNFC_Activated
} e_NFCState;

typedef enum{
	Blink_State_Off = 0,
	Blink_State_On = 1,
	Blink_State_Complete = 2
} LEDBlinkState;

typedef enum
{
	PreSyncAct_Off = 0,
	WPC2PreSyncAct_Off = 1,
	RWPCPreSyncAct_Off = 2,
	PreSyncAct_WPC2 = 3,
	PreSyncAct_WPC2RWPC = 4,
	PreSyncAct_RWPC = 5,
	PreSyncAct_RWPCWPC2 = 6,
	PreSyncAct_WPC = 7,
	PreSyncAct_WPC2WPC = 8,
	PreSyncAct_WPCWPC2 = 9
} e_INDSyncState;

/* TSCR-561 Ani Fadein Fadeout */
typedef enum	
{
	WPCIndCmdState_Default 		 = 0,
	WPCIndCmdState_ChrgOff		 = 1,
	WPCIndCmdState_1stChrgFadeIn = 2,
	WPCIndCmdState_1stChrgOn	 = 3,
	WPCIndCmdState_2ndChrgFadeIn = 4,
	WPCIndCmdState_2ndChrgOn	 = 5,
	WPCIndCmdState_3rdChrgFadeIn = 6,
	WPCIndCmdState_3rdChrgOn	 = 7,
	WPCIndCmdState_ChrgFadeOut	 = 8,
	WPCIndCmdState_ErrorFadeIn	 = 9,
	WPCIndCmdState_ErrorOn		 = 10,
	WPCIndCmdState_ErrorFadeOut	 = 11
}e_WPCIndCmdState;

/* TSCR-561 Ani Fadein Fadeout */
typedef enum	
{
	RWPCIndCmdState_Default 	  = 0,
	RWPCIndCmdState_ChrgOff		  = 1,
	RWPCIndCmdState_1stChrgFadeIn = 2,
	RWPCIndCmdState_1stChrgOn	  = 3,
	RWPCIndCmdState_2ndChrgFadeIn = 4,
	RWPCIndCmdState_2ndChrgOn	  = 5,
	RWPCIndCmdState_3rdChrgFadeIn = 6,
	RWPCIndCmdState_3rdChrgOn	  = 7,
	RWPCIndCmdState_ChrgFadeOut	  = 8,
	RWPCIndCmdState_ErrorFadeIn	  = 9,
	RWPCIndCmdState_ErrorOn		 = 10,
	RWPCIndCmdState_ErrorFadeOut = 11
}e_RWPCIndCmdState;

/* TSCR-561 Ani Fadein Fadeout */
typedef enum	
{
	WPC2IndCmdState_Default 	  = 0,
	WPC2IndCmdState_ChrgOff		  = 1,
	WPC2IndCmdState_1stChrgFadeIn = 2,
	WPC2IndCmdState_1stChrgOn	  = 3,
	WPC2IndCmdState_2ndChrgFadeIn = 4,
	WPC2IndCmdState_2ndChrgOn	  = 5,
	WPC2IndCmdState_3rdChrgFadeIn = 6,
	WPC2IndCmdState_3rdChrgOn	  = 7,
	WPC2IndCmdState_ChrgFadeOut	  = 8,
	WPC2IndCmdState_ErrorFadeIn	  = 9,
	WPC2IndCmdState_ErrorOn		  = 10,
	WPC2IndCmdState_ErrorFadeOut  = 11
}e_WPC2IndCmdState;

typedef enum
{
	SyncTrigger_Init	= 0,
	SyncTrigger_Off		= 1,
	SyncTrigger_On		= 2
}e_AmberSyncStateControl;


typedef enum
{
	SyncIndyTrigger_Init	= 0,
	SyncIndyTrigger_Off 	= 1,
	SyncIndyTrigger_On 		= 2
}e_AmberSyncIndyStateControl;


extern u8 b_BlinkState;
extern tTimer16 Timer_NFCTimeOutConfirm;
extern tTimer8 TimerCANEvtmsgTimeout;
extern tTimer8 p_tWaitingDelay3;
extern tTimer8 p_tWaitingDelay4;

extern e_NFCState stateNFC;
extern e_TempSensorErrorState StateTempSensorError;

extern void WPCNFCModeControl(void);
extern void WPCModeStatusControl(void);
extern void PreventionOfSMKLFInterferenceControl(void);
extern void OverCurrentDetectingControl(void);
extern void TemperatureSensorErrorDetectingControl(void);
extern void OverTemperatureDetectingControl(void);
extern void WPCUSMSetting(void);
extern void RWPCINDAnimationControl(void);
extern void WPCINDCmdStateControl(void);
extern void nonNFCCommunication(void);
extern void WPCLEDOutputControl(void);
extern void WPCLEDAnimationOutputControl(void);
extern void WPCFANControl(void);
extern void DTC_B1621_Control(void);


#endif /* 10W_WPC_LOGIC_H_ */
