/******************************************************************************
 * Project        :   SP2 IBU
 * File Name      :   app_input_type.h
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
#ifndef __APP_INPUT_TYPE_H__
#define __APP_INPUT_TYPE_H__

#include "Rte_Type.h"


/*******************************************************************************
  Define Variables Type
*******************************************************************************/
typedef struct
{
  /* e_LocalInput */
  tVAR kL_IPS_MUL;
  tVAR kL_FAN_DIAG;

  /* INPUT INTERNAL */
/* 001 : */
/* 002 : */

/* 003 : */ tVAR kb_WPCOption;
/* 004 : */ tVAR kb_WPCSWOption;
/* 005 : */ tVAR kb_CurProfile;
/* 006 : */

/* 007 : */ tVAR kb_WPCStatus;
/* 008 : */ tVAR kb_WPCPower;
/* 009 : */ tVAR kb_LFState;

/* 010 : */ tVAR kb_TemperatureFault;
/* 011 : */ tVAR kb_TempSensorFault;
/* 012 : */ tVAR kb_CurrentFault;
/* 013 : */ tVAR kb_CoilFault;
/* 014 : */ tVAR kb_FODFault;
/* 015 : */ tVAR kb_FANFault;

/* 016 : */ tVAR kb_DTCWPCInternalError;
/* 017 : */ tVAR kb_DeviceState;
/* 018 : */ tVAR kb_TX_State;                  // P9261 Device State
/* 019 : */ tVAR kb_TX_Status;                 // P9261 Device Status
/* 020 : */ tVAR kb_TX_Fault_Reason;
/* 020 : */ tVAR kb_WPCPhoneExist;
/* 021 : */ tVAR kb_WPCRunMode;
/* 022 : */ tVAR kb_ChargingState;             // For FAN On/Off

/* 023 : */ tVAR kb_GreenINDCmd;               // charging, error
/* 024 : */ tVAR kb_AmberINDCmd;               // charged EPT or CS100
/* 025 : */ tVAR kb_LED_Duty;                  // from CAN
///* 026 : */	tVARu16 kb_LED_Duty_AutoBright;	   // from CAN for Auto Bright
/* 026 : */ tVARu16 kb_GreenLED_Duty_AutoBright;    // from CAN for Auto Bright
/* 026 : */ tVARu16 kb_AmberLED_Duty_AutoBright;    // from CAN for Auto Bright
/* 026 : */ tVAR kb_FAN_PWM;

/* 027 : */
/* 028 : */
/* 029 : */
/* 030 : */
/* 031 : */
/* 032 : */ tVAR kb_CAN_Inactive;

/* 033 : */ tVAR kb_ACC_IN;                    // On:7.8V, Off:7.1V
/* 034 : */ tVAR kb_IGN_IN;

/* 035 : */ tVAR u1g_InhibitNormalBatt;
/* 036 : */ tVAR u1g_InhibitNormalBattOver;
/* 037 : */ tVAR u1g_InhibitNormalBattUnder;
/* 038 : */ tVAR u1g_InhibitCriticalBatt;
/* 039 : */ tVAR u1g_InhibitCriticalBattOver;
/* 040 : */ tVAR u1g_InhibitCriticalBattUnder;

/* 041 : */ tVAR km_ProfileOneWPCUSM;
/* 042 : */ tVAR km_ProfileTwoWPCUSM;
/* 043 : */ tVAR km_ProfileGuestWPCUSM;

/* 044 : */ tVAR kb_NFCSearchingOffComplete;
/* 045 : */
/* 046 : */
/* 047 : */
/* 048 : */ tVAR kS_WPC_RQST;
/* 049 : */ tVAR kS_IAU_RSPS;

/* 050 : */ tVAR kb_IGNUseOption;
/* 051 : */ tVAR kb_BatteryPowerState;
/* 052 : */ tVAR kb_InitialLEDOption;
/* 053 : */ tVAR kb_WarningOption;
/* 054 : */ tVAR kb_WPCDayTimeLEDOut;

/* 055 : */ tVAR kb_CANError_BCAN;             // Low Speed CAN Error flag



  tVAR  kb_FANModeCmd;

  /* e_CANInput */
  tVAR  kC_RheostatLevel;
  /* NFC MODE */
  tVAR  kb_NFC_OPTION;
  tVAR  kb_WPCIndUSMState;
  tVAR  km_WPCIndUSMState_ProfileOne;
  tVAR  km_WPCIndUSMState_ProfileTwo;
  tVAR  km_WPCIndUSMState_Guest;
  tVAR  kb_Var_PreSyncAct;
  tVAR  kb_WPCIndCmdState;
  tVAR  kb_RWPCIndCmdState;
  tVAR  kb_WPC2IndCmdState;
  tVAR  kb_SyncAmber;
  tVAR  kb_CmdAmberSync;
  tVAR  kb_BlinkState;
  tVAR	kb_PhnLeftChk_Enable;
  tVAR  kb_DrDoorPhnLftHoldComplete;
}tAPP_INPUT;

extern uint8 BAT_stab_finish_flg;
extern uint8 bStartupI2CDelayCnt;

uint8 Get_VN7140AS_MULTI(void);


#endif  /* __APP_INPUT_TYPE_H__ */
