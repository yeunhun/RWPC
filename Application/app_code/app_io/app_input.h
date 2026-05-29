
/******************************************************************************
 * Project        :   SP2 IBU
 * File Name      :   app_input.h
 * Compiler     :   Eclipse
 * Author         :   MyoungKwon Choi (mk210@seoyonelec.com)
 * Created at     :   2017-06-23
 * Code Editor    :   Source Insight (Recomended Font : D2Coding / Size 10)
 * Revision       :   Version 0.1
 * Copyright      :   Copyright Seoyon Electronics Co.Ltd. All Rights Reserved
 * Description    :
 *
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------*/
#ifndef __APP_INPUT_H__
#define __APP_INPUT_H__



/*******************************************************************************
  Declare External  Function
*******************************************************************************/
extern uint8 IsInit(void);
extern void Input_BatteryVoltage(void);
extern void Stabilize_Battery(void);
extern void Input_IGNVoltage(void);
extern void Stabilize_IGN(void);
extern void Set_BatteryMonitoring_Chattering(void);
extern void Set_BatteryMonitoring_Hysteresis(void);
extern void Input_CheckOperatingVoltage(void);
extern void Battery_Monitoring_For_CAN(void);
extern void TempSensorFailMonitor(void);
extern uint16 GetIGNADValue(void);

extern void Input_Local(void);
extern void Input_Internal_10ms(void);
extern void Locking_FAN(void);



/*******************************************************************************
  Declare External  Variables
*******************************************************************************/
extern  tAPP_INPUT  APP_INPUT_IF;


/* e_LocalInput */
#define kL_IPS_MUL                    	APP_INPUT_IF.kL_IPS_MUL
#define kL_FAN_DIAG						APP_INPUT_IF.kL_FAN_DIAG

/* INPUT INTERNAL */

#define kb_ACC_IN           			APP_INPUT_IF.kb_ACC_IN          // On:7.8V, Off:7.1V
#define kb_IGN_IN           			APP_INPUT_IF.kb_IGN_IN

#define kb_CANError_BCAN    			APP_INPUT_IF.kb_CANError_BCAN   // Low Speed CAN Error flag
#define kb_ChargingState    			APP_INPUT_IF.kb_ChargingState   // For FAN On/Off
#define kb_BatteryPowerState			APP_INPUT_IF.kb_BatteryPowerState
#define kb_CAN_Inactive					APP_INPUT_IF.kb_CAN_Inactive

#define kb_IGNUseOption					APP_INPUT_IF.kb_IGNUseOption

#define kb_NFCSearchingOffComplete		APP_INPUT_IF.kb_NFCSearchingOffComplete


#define kb_WPCOption                  	APP_INPUT_IF.kb_WPCOption         /* 003 : */
#define kb_WPCSWOption               	APP_INPUT_IF.kb_WPCSWOption       /* 004 : */
#define kb_CurProfile                 	APP_INPUT_IF.kb_CurProfile        /* 005 : */

#define kb_WPCStatus                  	APP_INPUT_IF.kb_WPCStatus         /* 007 : */
#define kb_WPCPower                   	APP_INPUT_IF.kb_WPCPower          /* 008 : */
#define kb_LFState                    	APP_INPUT_IF.kb_LFState           /* 009 : */

#define kb_TempSensorFault            	APP_INPUT_IF.kb_TempSensorFault   /* 010 : */
#define kb_TemperatureFault           	APP_INPUT_IF.kb_TemperatureFault  /* 011 : */
#define kb_CurrentFault					APP_INPUT_IF.kb_CurrentFault      /* 012 : */
#define kb_FODFault                   	APP_INPUT_IF.kb_FODFault          /* 014 : */
#define kb_FANFault                   	APP_INPUT_IF.kb_FANFault          /* 015 : */

#define u1g_InhibitNormalBatt         	APP_INPUT_IF.u1g_InhibitNormalBatt
#define u1g_InhibitNormalBattOver     	APP_INPUT_IF.u1g_InhibitNormalBattOver
#define u1g_InhibitNormalBattUnder    	APP_INPUT_IF.u1g_InhibitNormalBattUnder
#define u1g_InhibitCriticalBatt       	APP_INPUT_IF.u1g_InhibitCriticalBatt
#define u1g_InhibitCriticalBattOver   	APP_INPUT_IF.u1g_InhibitCriticalBattOver
#define u1g_InhibitCriticalBattUnder  	APP_INPUT_IF.u1g_InhibitCriticalBattUnder

#define km_ProfileOneWPCUSM				APP_INPUT_IF.km_ProfileOneWPCUSM
#define km_ProfileTwoWPCUSM				APP_INPUT_IF.km_ProfileTwoWPCUSM
#define km_ProfileGuestWPCUSM			APP_INPUT_IF.km_ProfileGuestWPCUSM

#define kb_DTCWPCInternalError        	APP_INPUT_IF.kb_DTCWPCInternalError
#define kb_DeviceState					APP_INPUT_IF.kb_DeviceState
#define kb_TX_State						APP_INPUT_IF.kb_TX_State
#define kb_TX_Status					APP_INPUT_IF.kb_TX_Status
#define kb_TX_Fault_Reason				APP_INPUT_IF.kb_TX_Fault_Reason
#define kb_WPCPhoneExist				APP_INPUT_IF.kb_WPCPhoneExist
#define kb_WPCRunMode					APP_INPUT_IF.kb_WPCRunMode

#define kb_GreenINDCmd					APP_INPUT_IF.kb_GreenINDCmd
#define kb_AmberINDCmd					APP_INPUT_IF.kb_AmberINDCmd
#define kb_LED_Duty						APP_INPUT_IF.kb_LED_Duty
//#define kb_LED_Duty_AutoBright			APP_INPUT_IF.kb_LED_Duty_AutoBright
#define kb_GreenLED_Duty_AutoBright      APP_INPUT_IF.kb_GreenLED_Duty_AutoBright
#define kb_AmberLED_Duty_AutoBright      APP_INPUT_IF.kb_AmberLED_Duty_AutoBright
#define kb_FAN_PWM						APP_INPUT_IF.kb_FAN_PWM
#define kb_FANModeCmd					APP_INPUT_IF.kb_FANModeCmd

#define kb_WPCDayTimeLEDOut				APP_INPUT_IF.kb_WPCDayTimeLEDOut

#define kS_WPC_RQST						APP_INPUT_IF.kS_WPC_RQST
#define kS_IAU_RSPS						APP_INPUT_IF.kS_IAU_RSPS

/* e_CANInput */
#define kC_RheostatLevel         		APP_INPUT_IF.kC_RheostatLevel

#define kb_InitialLEDOption     		APP_INPUT_IF.kb_InitialLEDOption
#define kb_WarningOption        		APP_INPUT_IF.kb_WarningOption

/* NFC MODE */
#define kb_NFC_OPTION              		APP_INPUT_IF.kb_NFC_OPTION
/* IND Animation USM Input */
#define kb_WPCIndUSMState				APP_INPUT_IF.kb_WPCIndUSMState
#define km_WPCIndUSMState_ProfileOne	APP_INPUT_IF.km_WPCIndUSMState_ProfileOne
#define km_WPCIndUSMState_ProfileTwo	APP_INPUT_IF.km_WPCIndUSMState_ProfileTwo
#define km_WPCIndUSMState_Guest			APP_INPUT_IF.km_WPCIndUSMState_Guest

/* IND Animation Input */
#define kb_Var_PreSyncAct				APP_INPUT_IF.kb_Var_PreSyncAct
#define kb_WPCIndCmdState				APP_INPUT_IF.kb_WPCIndCmdState
#define kb_RWPCIndCmdState				APP_INPUT_IF.kb_RWPCIndCmdState
#define kb_WPC2IndCmdState				APP_INPUT_IF.kb_WPC2IndCmdState

#define kb_SyncAmber					APP_INPUT_IF.kb_SyncAmber
#define kb_CmdAmberSync					APP_INPUT_IF.kb_CmdAmberSync
#define kb_BlinkState					APP_INPUT_IF.kb_BlinkState

#define kb_PhnLeftChk_Enable			APP_INPUT_IF.kb_PhnLeftChk_Enable
#define kb_DrDoorPhnLftHoldComplete 	APP_INPUT_IF.kb_DrDoorPhnLftHoldComplete
#endif  /* __APP_INPUT_H__ */
