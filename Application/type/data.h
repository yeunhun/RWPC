/*******************************************************************************
 * Project        :   SP2 IBU
 * File Name      :   data.h
 * Compiler   :   Eclipse
 * Author         :   MyoungKwon Choi (mk210@seoyonelec.com)
 * Created at     :   2017-06-23
 * Code Editor  :   Source Insight (Recomended Font : D2Coding / Size 10)
 * Revision       :   Version 0.1
 * Copyright    :   (c) Copyright Seoyon Electronisc Co.Ltd. All Rights Reserved
 * Description    :   This is a header file associated with constants & macro.
 *
 *******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------*/
#ifndef __DATA_H__
#define __DATA_H__



/*******************************************************************************
  enum type tVARs
*******************************************************************************/

typedef enum // Device_State
{
	DeviceStates_Init 			= 0,
	DeviceStates_Reserved		= 1,
	DeviceStates_Standby		= 2,		// Wait Charging
	DeviceStates_Charging		= 3,
	DeviceStates_Full_Charge	= 4,		// EPT + CS100
	DeviceStates_FODError		= 5,
	DeviceStates_DeviceError	= 6,
	DeviceStates_SystemError	= 7,
	DeviceStates_NVMError		= 8,
	DeviceStates_APPError		= 9,
	DeviceStates_ErrorComm		= 255
}e_DeviceStatus;

typedef enum
{
	WPCStatus_Off = 0,
	WPCStatus_WPCMode,
	WPCStatus_NFCMode,
	WPCStatus_LPCDMode,
	WPCStatus_PiccMode,
	WPCStatus_Invalid = 7
}e_WPCStatus;

typedef enum
{
  WPCOpt_LP_WPC = 0,
  WPCOpt_MP_WPCOnly,
  WPCOpt_MP_WPCNFC,
  WPCOpt_Invalid = 7
}e_WPCOption;

typedef enum
{
	Critical_Inhibit_Low = 0,
	Normal_Inhibit_Low,
	Normal_Inhibit_High,
	Critical_Inhibit_High
}e_Battery_Inhibit;

typedef enum
{
	OperatingVoltageState_Normal = 0,
	OperatingVoltageState_Low,
	OperatingVoltageState_High
}e_OperatingVoltageState;

typedef enum
{
	CANInactive_None = 0,
	CANInactive_Off,
	CANInactive_On
}e_CanInactive;

/* WPC NFC Mode Control */
typedef enum
{
	ModeControl_Init = 0,
	ModeControl_Operating
}e_WPCNFCModeControl;

/* Input CAN */
typedef enum
{
	kWPCWarning_Off = 0,
	kWPCWarning_CellphoneOnThePad = 1,
	kWPCWarning_Charging = 2,
	kWPCWarning_ChargingComplete = 3,
	kWPCWarning_CellphoneReminder = 4,
	kWPCWarning_Error = 5,
	kWPCWarning_Reseved6 = 6,
	kWPCWarning_Invalid = 7
}e_CAN_WPCWarning;

typedef enum
{
	kWPCOnOff_Default = 0,
	kWPCOnOff_Off = 1,
	kWPCOnOff_On = 2,
	kWPCOnOff_Invalid = 3
}e_CAN_WPCOnOff;

typedef enum
{
	kWPCNFCStatus_Off = 0,
	kWPCNFCStatus_Detected = 1,
	kWPCNFCStatus_NotDetected = 2,
	kWPCNFCStatus_Invalid = 15
}e_CAN_WPCNFCStatus;

typedef enum
{
	kWPCNFCDetection_Off = 0,
	kWPCNFCDetection_Detected = 1,
	kWPCNFCDetection_NotDetected = 2
}e_CAN_WPC_NFCDetection;

typedef enum
{
	kWPCStatus_Off = 0,
	kWPCStatus_WPCMode = 1,
	kWPCStatus_NFCScanning = 2,
	kWPCStatus_NFCCommunicating = 3,
	kWPCStatus_LPCDMode = 4,
	kWPCStatus_PICCDetected = 5,
	kWPCStatus_RESERVED = 6,
	kWPCStatus_Invalid = 7
}e_CAN_WPCStatus;

typedef enum
{
	kIGNSw_KeyOff = 0,
	kIGNSw_KeyIn = 1,
	kIGNSw_KeyAcc = 2,
	kIGNSw_KeyIgn = 3,
	kIGNSw_KeySt = 4
}e_CAN_IGNSw;

typedef enum
{
	kDoorSw_Close = 0,
	kDoorSw_Open = 1
}e_CAN_DoorSw;

typedef enum
{
	kSMKOption_RKE = 0,
	kSMKOption_SMK = 1
}e_CAN_SMKOption;

typedef enum
{
	kNFCScanCommand_None = 0,
	kNFCScanCommand_ScanStart = 1,
	kNFCScanCommand_ScanStop = 2,
	kNFCScanCommand_Invalid = 3
}e_CAN_NFCScanCommand;

typedef enum
{
	kDigitalKeyEnable_None = 0,
	kDigitalKeyEnable_Disable = 1,
	kDigitalKeyEnable_Enable = 2,
	kDigitalKeyEnable_Invalid = 3
}e_CAN_DigitalKeyEnable;

typedef enum
{
	kDigitalKeyOption_notapplied = 0,
	kDigitalKeyOption_applied = 1,
	kDigitalKeyOption_reserved = 2,
	kDigitalKeyOption_Invalid = 3
}e_CAN_DigitalKeyOptoin;

typedef enum
{
	kProfileID_Default = 0,
	kProfileID_Guest = 1,
	kProfileID_Profile1 = 2,
	kProfileID_Profile2 = 3,
	kProfileID_Invalid = 15
}e_CAN_ProfileID;

typedef enum
{
	kWPCNFCcmd_None = 0,
	kWPCNFCcmd_NFCSearchingOn_HCE = 1,
	kWPCNFCcmd_NFCSearchingOff = 2,
	kWPCNFCcmd_NFCSearchingOn_Usim = 3,
	kWPCNFCcmd_Invalid = 7
}e_CAN_WPCNFCcmd;

typedef enum
{
	kIAUWPCNFCcmd_Default = 0,
	kIAUWPCNFCcmd_NFCPolling_Search = 1,
	kIAUWPCNFCcmd_NFCDeselect_Stop = 2,
	kIAUWPCNFCcmd_Invalid = 3
}e_CAN_IAUWPCNFCcmd;

typedef enum
{
	kIAUStatus_Idle = 0,
	kIAUStatus_Process = 1,
	kIAUStatus_Complete = 2,
	kIAUStatus_Invalid = 7
}e_CAN_IAUStatus;

typedef enum
{
	kEngineState_Stop = 0,
	kEngineState_Cranking = 1,
	kEngineState_StAlled = 2,
	kEngineState_Running = 3,
	kEngineState_Fault = 7
}e_CAN_EngineState;

typedef enum
{
	kHCU_HCU_HevRdySta_HEV_not_ready   = 0,
	kHCU_HCU_HevRdySta_HEV_Drivable	   = 1,	
	kHCU_HCU_HevRdySta_Not_used		   = 2,
	kHCU_HCU_HevRdySta_Error_Indicator = 3
}e_CAN_HCU_HevRdySta;

typedef enum
{
	kVCU_EvDrvRdySta_None   			= 0,
	kVCU_EvDrvRdySta_EV_Drivable	   	= 1,	
	kVCU_EvDrvRdySta_Not_used		   	= 2,
	kVCU_EvDrvRdySta_Error_Indicator 	= 3
}e_CAN_VCU_EvDrvRdySta;

typedef enum
{
	kHEV_EngOpSta_ES = 0,
	kHEV_EngOpSta_ST = 1,
	kHEV_EngOpSta_IS = 2,
	kHEV_EngOpSta_PL = 3,
	kHEV_EngOpSta_PU = 4,
	kHEV_EngOpSta_PUC = 5
}e_CAN_HEV_EngOpSta;

/* WPC LPCD */
typedef enum
{
	OwnerKeyRegStatus_Default = 0,
	OwnerKeyRegStatus_Registered = 1,
	OwnerKeyRegStatus_Reserve = 2,
	OwnerKeyRegStatus_Invalid = 3
}e_CAN_OwnerKey_Reg_Status;
typedef enum
{
	kWPCAnimationOnOff_Off = 0,
	kWPCAnimationOnOff_On  = 1
}e_CAN_WPCAnimationOption;

typedef enum
{
	kWPCAnimation_Default =  0,
	kWPCAnimation_Type_1 = 	 1,
	kWPCAnimation_Type_2 = 	 2,
	kWPCAnimation_Reserved = 3,
	kWPCAnimation_Invalid =  7
}e_CAN_WPCAnimationOnOff;


typedef enum
{
	kWPC2IndSyncVal_Default = 	0,
	kWPC2IndSyncVal_Off = 		1,
	kWPC2IndSyncVal_1stSync = 	2,
	kWPC2IndSyncVal_2ndSync = 	3,
	kWPC2IndSyncVal_3rdSync = 	4,
	kWPC2IndSyncVal_ErrorOff = 5,
	kWPC2IndSyncVal_ErrorOn = 	6,
	kWPC2IndSyncVal_Reserved = 	7
}e_CAN_WPC2IndSyncVal;

typedef enum
{
	kRWPCIndSyncVal_Default = 	0,
	kRWPCIndSyncVal_Off = 		1,
	kRWPCIndSyncVal_1stSync = 	2,
	kRWPCIndSyncVal_2ndSync = 	3,
	kRWPCIndSyncVal_3rdSync = 	4,
	kRWPCIndSyncVal_ErrorOff = 5,
	kRWPCIndSyncVal_ErrorOn = 	6,
	kRWPCIndSyncVal_Reserved = 	7
}e_CAN_RWPCIndSyncVal;

/* Output CAN */
typedef enum
{
	kWPCIndSyncVal_Default = 	0,
	kWPCIndSyncVal_Off = 		1,
	kWPCIndSyncVal_1stSync = 	2,
	kWPCIndSyncVal_2ndSync = 	3,
	kWPCIndSyncVal_3rdSync = 	4,
	kWPCIndSyncVal_ErrorOff = 	5,
	kWPCIndSyncVal_ErrorOn = 	6,
	kWPCIndSyncVal_Reserved = 	7
}e_CAN_WPCIndSyncVal;

typedef enum
{
	kLatch_TypeOption_Off				= 0,
	kLatch_TypeOption_On				= 1,
	kLatch_TypeOption_Reserved			= 2,
	kLatch_TypeOption_ErrorIndicator	= 3
}e_CAN_Latch_TypeOption;
/************* I2C ******************/
typedef enum // TX Running Mode
{
	kRunMode_NONE				= 0x00,
	kRunMode_STOP				= 0x10,
	kRunMode_RUN				= 0x20,
	kRunMode_RX_DETECT			= 0x40,
	kRunMode_REPROGRAMMING 		= 0xA0
}e_TxRunMode;

extern uint16 b_Temperature_Sensor1;
extern uint16 b_Temperature_Sensor2;
extern uint16 b_Temperature_Sensor3;

extern uint8 b_Temperature_SensorFault1;
extern uint8 b_Temperature_SensorFault2;
extern uint8 b_Temperature_SensorFault3;

extern uint16 b_CurrentCurr;

extern e_OperatingVoltageState StateOperatingVoltage;

/* Session List */
#define kDefaultSession_NoSec       0u
#define kProgrammingSession_NoSec   1u
#define kExtendedSession_NoSec      2u
#define kSafetySystemSession_Nosec  3u

//#define kL_IPS_MUL      0
//#define kL_FAN_DIAG     1
#define kMaxLocalInput  2

#define Amber     (0u)
#define Green1    (1u)
#define Green2    (2u)
#define Green3    (3u)




#if defined (USE_AUTOBRIGHT)
#if 0
#define Par_AutoBrightLevel002 (100)		//1.00%
#define Par_AutoBrightLevel003 (171)		//1.17%
#define Par_AutoBrightLevel004 (242)		//2.42%
#define Par_AutoBrightLevel005 (314)		//3.14%
#define Par_AutoBrightLevel006 (385)		//3.85%
#define Par_AutoBrightLevel007 (456)		//4.56%
#define Par_AutoBrightLevel008 (527)		//5.72%
#define Par_AutoBrightLevel009 (598)		//5.98%
#define Par_AutoBrightLevel010 (670)		//6.70%
#define Par_AutoBrightLevel011 (741)		//7.41%
#define Par_AutoBrightLevel012 (812)		//8.12%
#define Par_AutoBrightLevel013 (883)		//8.83%
#define Par_AutoBrightLevel014 (955)		//9.55%
#define Par_AutoBrightLevel015 (1026)		//10.26%
#define Par_AutoBrightLevel016 (1097)		//10.97%
#define Par_AutoBrightLevel017 (1168)		//11.68%
#define Par_AutoBrightLevel018 (1239)		//12.39%
#define Par_AutoBrightLevel019 (1311)		//13.56%
#define Par_AutoBrightLevel020 (1382)		//13.82%
#define Par_AutoBrightLevel021 (1453)		//14.53%
#define Par_AutoBrightLevel022 (1524)		//15.24%
#define Par_AutoBrightLevel023 (1595)		//15.95%
#define Par_AutoBrightLevel024 (1667)		//16.67%
#define Par_AutoBrightLevel025 (1692)		//16.92%
#define Par_AutoBrightLevel026 (1717)		//17.17%
#define Par_AutoBrightLevel027 (1742)		//17.42%
#define Par_AutoBrightLevel028 (1768)		//17.68%
#define Par_AutoBrightLevel029 (1793)		//17.93%
#define Par_AutoBrightLevel030 (1818)		//18.18%
#define Par_AutoBrightLevel031 (1843)		//18.43%
#define Par_AutoBrightLevel032 (1869)		//18.69%
#define Par_AutoBrightLevel033 (1894)		//18.94%
#define Par_AutoBrightLevel034 (1919)		//19.19%
#define Par_AutoBrightLevel035 (1944)		//19.44%
#define Par_AutoBrightLevel036 (1970)		//19.70%
#define Par_AutoBrightLevel037 (1995)		//19.95%
#define Par_AutoBrightLevel038 (2020)		//20.20%
#define Par_AutoBrightLevel039 (2045)		//20.45%
#define Par_AutoBrightLevel040 (2071)		//20.71%
#define Par_AutoBrightLevel041 (2096)		//20.96%
#define Par_AutoBrightLevel042 (2121)		//21.21%
#define Par_AutoBrightLevel043 (2146)		//21.46%
#define Par_AutoBrightLevel044 (2172)		//21.72%
#define Par_AutoBrightLevel045 (2197)		//21.97%
#define Par_AutoBrightLevel046 (2222)		//22.22%
#define Par_AutoBrightLevel047 (2247)		//22.47%
#define Par_AutoBrightLevel048 (2273)		//22.73%
#define Par_AutoBrightLevel049 (2298)		//22.98%
#define Par_AutoBrightLevel050 (2323)		//23.23%
#define Par_AutoBrightLevel051 (2348)		//23.48%
#define Par_AutoBrightLevel052 (2374)		//23.74%
#define Par_AutoBrightLevel053 (2399)		//23.99%
#define Par_AutoBrightLevel054 (2424)		//24.24%
#define Par_AutoBrightLevel055 (2449)		//24.49%
#define Par_AutoBrightLevel056 (2475)		//24.75%
#define Par_AutoBrightLevel057 (2500)		//25.00%
#define Par_AutoBrightLevel058 (2525)		//25.25%
#define Par_AutoBrightLevel059 (2551)		//25.51%
#define Par_AutoBrightLevel060 (2576)		//25.76%
#define Par_AutoBrightLevel061 (2601)		//26.01%
#define Par_AutoBrightLevel062 (2626)		//26.26%
#define Par_AutoBrightLevel063 (2652)		//26.52%
#define Par_AutoBrightLevel064 (2677)		//26.77%
#define Par_AutoBrightLevel065 (2702)		//27.02%
#define Par_AutoBrightLevel066 (2727)		//27.27%
#define Par_AutoBrightLevel067 (2753)		//27.53%
#define Par_AutoBrightLevel068 (2778)		//28.78%
#define Par_AutoBrightLevel069 (2803)		//28.03%
#define Par_AutoBrightLevel070 (2828)		//28.28%
#define Par_AutoBrightLevel071 (2854)		//28.54%
#define Par_AutoBrightLevel072 (2879)		//28.79%
#define Par_AutoBrightLevel073 (2904)		//29.04%
#define Par_AutoBrightLevel074 (2929)		//29.29%
#define Par_AutoBrightLevel075 (2955)		//29.55%
#define Par_AutoBrightLevel076 (2980)		//30.80%
#define Par_AutoBrightLevel077 (3005)		//30.05%
#define Par_AutoBrightLevel078 (3030)		//30.30%
#define Par_AutoBrightLevel079 (3056)		//30.56%
#define Par_AutoBrightLevel080 (3081)		//30.81%
#define Par_AutoBrightLevel081 (3106)		//31.06%
#define Par_AutoBrightLevel082 (3131)		//31.31%
#define Par_AutoBrightLevel083 (3157)		//31.57%
#define Par_AutoBrightLevel084 (3182)		//31.82%
#define Par_AutoBrightLevel085 (3207)		//32.07%
#define Par_AutoBrightLevel086 (3232)		//32.32%
#define Par_AutoBrightLevel087 (3258)		//32.58%
#define Par_AutoBrightLevel088 (3283)		//32.83%
#define Par_AutoBrightLevel089 (3308)		//33.08%
#define Par_AutoBrightLevel090 (3333)		//33.33%
#define Par_AutoBrightLevel091 (10000)		//100.00%
#define Par_AutoBrightLevelMax (10000)		//100.00% : AutoBrightLevel 92~ 200
#endif

#define Par_GreenAutoBrightLevel002 (21)    //1.00%
#define Par_GreenAutoBrightLevel003 (50)    //1.17%
#define Par_GreenAutoBrightLevel004 (90)    //2.42%
#define Par_GreenAutoBrightLevel005 (130)    //3.14%
#define Par_GreenAutoBrightLevel006 (170)    //3.85%
#define Par_GreenAutoBrightLevel007 (210)    //4.56%
#define Par_GreenAutoBrightLevel008 (250)    //5.72%
#define Par_GreenAutoBrightLevel009 (290)    //5.98%
#define Par_GreenAutoBrightLevel010 (330)    //6.70%
#define Par_GreenAutoBrightLevel011 (370)    //7.41%
#define Par_GreenAutoBrightLevel012 (410)    //8.12%
#define Par_GreenAutoBrightLevel013 (450)    //8.83%
#define Par_GreenAutoBrightLevel014 (490)    //9.55%
#define Par_GreenAutoBrightLevel015 (530)   //10.26%
#define Par_GreenAutoBrightLevel016 (570)   //10.97%
#define Par_GreenAutoBrightLevel017 (610)   //11.68%
#define Par_GreenAutoBrightLevel018 (650)   //12.39%
#define Par_GreenAutoBrightLevel019 (690)   //13.56%
#define Par_GreenAutoBrightLevel020 (730)   //13.82%
#define Par_GreenAutoBrightLevel021 (770)   //14.53%
#define Par_GreenAutoBrightLevel022 (810)   //15.24%
#define Par_GreenAutoBrightLevel023 (850)   //15.95%
#define Par_GreenAutoBrightLevel024 (900)   //16.67%
#define Par_GreenAutoBrightLevel025 (930)   //16.92%
#define Par_GreenAutoBrightLevel026 (960)   //17.17%
#define Par_GreenAutoBrightLevel027 (990)   //17.42%
#define Par_GreenAutoBrightLevel028 (1020)   //17.68%
#define Par_GreenAutoBrightLevel029 (1050)   //17.93%
#define Par_GreenAutoBrightLevel030 (1080)   //18.18%
#define Par_GreenAutoBrightLevel031 (1110)   //18.43%
#define Par_GreenAutoBrightLevel032 (1140)   //18.69%
#define Par_GreenAutoBrightLevel033 (1170)   //18.94%
#define Par_GreenAutoBrightLevel034 (1200)   //19.19%
#define Par_GreenAutoBrightLevel035 (1230)   //19.44%
#define Par_GreenAutoBrightLevel036 (1260)   //19.70%
#define Par_GreenAutoBrightLevel037 (1290)   //19.95%
#define Par_GreenAutoBrightLevel038 (1320)   //20.20%
#define Par_GreenAutoBrightLevel039 (1350)   //20.45%
#define Par_GreenAutoBrightLevel040 (1380)   //20.71%
#define Par_GreenAutoBrightLevel041 (1410)   //20.96%
#define Par_GreenAutoBrightLevel042 (1440)   //21.21%
#define Par_GreenAutoBrightLevel043 (1470)   //21.46%
#define Par_GreenAutoBrightLevel044 (1500)   //21.72%
#define Par_GreenAutoBrightLevel045 (1530)   //21.97%
#define Par_GreenAutoBrightLevel046 (1560)   //22.22%
#define Par_GreenAutoBrightLevel047 (1590)   //22.47%
#define Par_GreenAutoBrightLevel048 (1620)   //22.73%
#define Par_GreenAutoBrightLevel049 (1650)   //22.98%
#define Par_GreenAutoBrightLevel050 (1680)   //23.23%
#define Par_GreenAutoBrightLevel051 (1710)   //23.48%
#define Par_GreenAutoBrightLevel052 (1740)   //23.74%
#define Par_GreenAutoBrightLevel053 (1770)   //23.99%
#define Par_GreenAutoBrightLevel054 (1800)   //24.24%
#define Par_GreenAutoBrightLevel055 (1830)   //24.49%
#define Par_GreenAutoBrightLevel056 (1860)   //24.75%
#define Par_GreenAutoBrightLevel057 (1890)   //25.00%
#define Par_GreenAutoBrightLevel058 (1920)   //25.25%
#define Par_GreenAutoBrightLevel059 (1950)   //25.51%
#define Par_GreenAutoBrightLevel060 (1980)   //25.76%
#define Par_GreenAutoBrightLevel061 (2010)   //26.01%
#define Par_GreenAutoBrightLevel062 (2040)   //26.26%
#define Par_GreenAutoBrightLevel063 (2070)   //26.52%
#define Par_GreenAutoBrightLevel064 (2100)   //26.77%
#define Par_GreenAutoBrightLevel065 (2130)   //27.02%
#define Par_GreenAutoBrightLevel066 (2160)   //27.27%
#define Par_GreenAutoBrightLevel067 (2190)   //27.53%
#define Par_GreenAutoBrightLevel068 (2220)   //28.78%
#define Par_GreenAutoBrightLevel069 (2250)   //28.03%
#define Par_GreenAutoBrightLevel070 (2280)   //28.28%
#define Par_GreenAutoBrightLevel071 (2310)   //28.54%
#define Par_GreenAutoBrightLevel072 (2340)   //28.79%
#define Par_GreenAutoBrightLevel073 (2370)   //29.04%
#define Par_GreenAutoBrightLevel074 (2400)   //29.29%
#define Par_GreenAutoBrightLevel075 (2430)   //29.55%
#define Par_GreenAutoBrightLevel076 (2460)   //30.80%
#define Par_GreenAutoBrightLevel077 (2470)   //30.05%
#define Par_GreenAutoBrightLevel078 (2500)   //30.30%
#define Par_GreenAutoBrightLevel079 (2530)   //30.56%
#define Par_GreenAutoBrightLevel080 (2560)   //30.81%
#define Par_GreenAutoBrightLevel081 (2587)   //31.06%
#define Par_GreenAutoBrightLevel082 (2614)   //31.31%
#define Par_GreenAutoBrightLevel083 (2641)   //31.57%
#define Par_GreenAutoBrightLevel084 (2668)   //31.82%
#define Par_GreenAutoBrightLevel085 (2695)   //32.07%
#define Par_GreenAutoBrightLevel086 (2722)   //32.32%
#define Par_GreenAutoBrightLevel087 (2749)   //32.58%
#define Par_GreenAutoBrightLevel088 (2776)   //32.83%
#define Par_GreenAutoBrightLevel089 (2803)   //33.08%
#define Par_GreenAutoBrightLevel090 (2833)   //33.33%
#define Par_GreenAutoBrightLevel091 (8500)    //100.00%
#define Par_GreenAutoBrightLevelMax (8500)    //100.00% : AutoBrightLevel 92~ 200

#define Par_AmberAutoBrightLevel002 (260)    //1.00%
#define Par_AmberAutoBrightLevel003 (280)    //1.17%
#define Par_AmberAutoBrightLevel004 (305)    //2.42%
#define Par_AmberAutoBrightLevel005 (330)    //3.14%
#define Par_AmberAutoBrightLevel006 (385)    //3.85%
#define Par_AmberAutoBrightLevel007 (440)    //4.56%
#define Par_AmberAutoBrightLevel008 (495)    //5.72%
#define Par_AmberAutoBrightLevel009 (550)    //5.98%
#define Par_AmberAutoBrightLevel010 (605)    //6.70%
#define Par_AmberAutoBrightLevel011 (660)    //7.41%
#define Par_AmberAutoBrightLevel012 (715)    //8.12%
#define Par_AmberAutoBrightLevel013 (770)    //8.83%
#define Par_AmberAutoBrightLevel014 (825)    //9.55%
#define Par_AmberAutoBrightLevel015 (880)   //10.26%
#define Par_AmberAutoBrightLevel016 (935)   //10.97%
#define Par_AmberAutoBrightLevel017 (990)   //11.68%
#define Par_AmberAutoBrightLevel018 (1005)   //12.39%
#define Par_AmberAutoBrightLevel019 (1200)   //13.56%
#define Par_AmberAutoBrightLevel020 (1355)   //13.82%
#define Par_AmberAutoBrightLevel021 (1410)   //14.53%
#define Par_AmberAutoBrightLevel022 (1465)   //15.24%
#define Par_AmberAutoBrightLevel023 (1520)   //15.95%
#define Par_AmberAutoBrightLevel024 (1650)   //16.67%
#define Par_AmberAutoBrightLevel025 (1703)   //16.92%
#define Par_AmberAutoBrightLevel026 (1723)   //17.17%
#define Par_AmberAutoBrightLevel027 (1743)   //17.42%
#define Par_AmberAutoBrightLevel028 (1763)   //17.68%
#define Par_AmberAutoBrightLevel029 (1783)   //17.93%
#define Par_AmberAutoBrightLevel030 (1803)   //18.18%
#define Par_AmberAutoBrightLevel031 (1823)   //18.43%
#define Par_AmberAutoBrightLevel032 (1849)   //18.69%
#define Par_AmberAutoBrightLevel033 (1864)   //18.94%
#define Par_AmberAutoBrightLevel034 (1889)   //19.19%
#define Par_AmberAutoBrightLevel035 (1903)   //19.44%
#define Par_AmberAutoBrightLevel036 (1923)   //19.70%
#define Par_AmberAutoBrightLevel037 (1943)   //19.95%
#define Par_AmberAutoBrightLevel038 (1963)   //20.20%
#define Par_AmberAutoBrightLevel039 (1983)   //20.45%
#define Par_AmberAutoBrightLevel040 (2003)   //20.71%
#define Par_AmberAutoBrightLevel041 (2023)   //20.96%
#define Par_AmberAutoBrightLevel042 (2043)   //21.21%
#define Par_AmberAutoBrightLevel043 (2063)   //21.46%
#define Par_AmberAutoBrightLevel044 (2083)   //21.72%
#define Par_AmberAutoBrightLevel045 (2103)   //21.97%
#define Par_AmberAutoBrightLevel046 (2123)   //22.22%
#define Par_AmberAutoBrightLevel047 (2143)   //22.47%
#define Par_AmberAutoBrightLevel048 (2163)   //22.73%
#define Par_AmberAutoBrightLevel049 (2183)   //22.98%
#define Par_AmberAutoBrightLevel050 (2203)   //23.23%
#define Par_AmberAutoBrightLevel051 (2223)   //23.48%
#define Par_AmberAutoBrightLevel052 (2243)   //23.74%
#define Par_AmberAutoBrightLevel053 (2263)   //23.99%
#define Par_AmberAutoBrightLevel054 (2283)   //24.24%
#define Par_AmberAutoBrightLevel055 (2301)   //24.49%
#define Par_AmberAutoBrightLevel056 (2321)   //24.75%
#define Par_AmberAutoBrightLevel057 (2341)   //25.00%
#define Par_AmberAutoBrightLevel058 (2361)   //25.25%
#define Par_AmberAutoBrightLevel059 (2381)   //25.51%
#define Par_AmberAutoBrightLevel060 (2400)   //25.76%
#define Par_AmberAutoBrightLevel061 (2415)   //26.01%
#define Par_AmberAutoBrightLevel062 (2434)   //26.26%
#define Par_AmberAutoBrightLevel063 (2453)   //26.52%
#define Par_AmberAutoBrightLevel064 (2472)   //26.77%
#define Par_AmberAutoBrightLevel065 (2491)   //27.02%
#define Par_AmberAutoBrightLevel066 (2510)   //27.27%
#define Par_AmberAutoBrightLevel067 (2529)   //27.53%
#define Par_AmberAutoBrightLevel068 (2548)   //28.78%
#define Par_AmberAutoBrightLevel069 (2567)   //28.03%
#define Par_AmberAutoBrightLevel070 (2586)   //28.28%
#define Par_AmberAutoBrightLevel071 (2605)   //28.54%
#define Par_AmberAutoBrightLevel072 (2624)   //28.79%
#define Par_AmberAutoBrightLevel073 (2643)   //29.04%
#define Par_AmberAutoBrightLevel074 (2662)   //29.29%
#define Par_AmberAutoBrightLevel075 (2681)   //29.55%
#define Par_AmberAutoBrightLevel076 (2700)   //30.80%
#define Par_AmberAutoBrightLevel077 (2719)   //30.05%
#define Par_AmberAutoBrightLevel078 (2738)   //30.30%
#define Par_AmberAutoBrightLevel079 (2757)   //30.56%
#define Par_AmberAutoBrightLevel080 (2776)   //30.81%
#define Par_AmberAutoBrightLevel081 (2795)   //31.06%
#define Par_AmberAutoBrightLevel082 (2814)   //31.31%
#define Par_AmberAutoBrightLevel083 (2833)   //31.57%
#define Par_AmberAutoBrightLevel084 (2852)   //31.82%
#define Par_AmberAutoBrightLevel085 (2871)   //32.07%
#define Par_AmberAutoBrightLevel086 (2890)   //32.32%
#define Par_AmberAutoBrightLevel087 (3009)   //32.58%
#define Par_AmberAutoBrightLevel088 (3128)   //32.83%
#define Par_AmberAutoBrightLevel089 (3247)   //33.08%
#define Par_AmberAutoBrightLevel090 (3350)   //33.33%
#define Par_AmberAutoBrightLevel091 (9200)    //100.00%
#define Par_AmberAutoBrightLevelMax (9200)    //100.00% : AutoBrightLevel 92~ 200

#endif

#define Par_RheostatBrightLevel01 (5u)
#define Par_RheostatBrightLevel02 (6u)
#define Par_RheostatBrightLevel03 (8u)
#define Par_RheostatBrightLevel04 (10u)
#define Par_RheostatBrightLevel05 (12u)
#define Par_RheostatBrightLevel06 (14u)
#define Par_RheostatBrightLevel07 (16u)
#define Par_RheostatBrightLevel08 (24u)
#define Par_RheostatBrightLevel09 (30u)
#define Par_RheostatBrightLevel10 (37u)
#define Par_RheostatBrightLevel11 (45u)
#define Par_RheostatBrightLevel12 (51u)
#define Par_RheostatBrightLevel13 (61u)
#define Par_RheostatBrightLevel14 (70u)
#define Par_RheostatBrightLevel15 (84u)
#define Par_RheostatBrightLevel16 (106u)
#define Par_RheostatBrightLevel17 (120u)
#define Par_RheostatBrightLevel18 (130u)
#define Par_RheostatBrightLevel19 (136u)
#define Par_RheostatBrightLevel20 (140u)
#define Par_RheostatBrightLevel21 (200u)

#define Par_BrightNight		(30u)		//15%
#define Par_BrightDay		(200u)		//100%

/*Task Timer*/
#define Par_TaskTimer_20ms	20u

/* Battery Value */
#define kACC_ON_Voltage   1437   /* 7.8V */
#define kACC_OFF_Voltage  1000   /* 7.1V */

#define kIGN_ON_Voltage   1430   /* 7V */ /* 20180820_ADC Value ���� */
#define kIGN_OFF_Voltage  820   /* 4V */ /* 20180820_ADC Value ���� */

#define kCriticalBatteryUnder 1234//1263   /* 6.8V */
#define kNoramlBatteryUnder   1642//1664   /* 8.8 */
#define kNormalBatteryOver    3152//3199   /* 16.2V */
#define kCriticalBatteryOver  3563//3578   /* 18.2V */
/*JX1 PE/RG3 PE RWPC*/
/*18.2V 3563*/
/*18.0V 3521*/
/*16.5V 3216*/
/*16.0V 3111*/
/*9.0V 1683*/
/*8.5V 1580*/
/*7.0V 1275*/
/*6.8V 1234*/
#define kWPCOperatingVoltageUnder 1683//1710   /* 9V */
#define kWPCOperatingVoltageOver  3111//3126   /* 16V */

/* Phone Left Operating Voltage */
#define kWPCPhoneLeftOpVoltUnder  1710   /* 9V */
#define kWPCPhoneLeftOpVoltOver   3126   /* 16V */

#define kBattery_hysteresis     (40)  /* 0.2V */
#define kBattery_hysteresis_dot_5V  (110)  /* 0.5V */

#define Par_BATChattTime			Time_ms(30)	/*Battery Chattering Time*/
#define BAT_ArrayMAX	100	/* 1000ms */
#define	Par_SameDataCnt	30	/* 30ms */

#define ACC_ArrayMAX	30	/* 30ms */
#define IGN_ArrayMAX	30	/* 300ms */

#define CoilMax			3
#define Temp_ArrayMax	5

/* Battery stable time */
#define T_BAT_stab_delayTime	60

/* FAN Control */
#define kError				0x1FFu
#define u16_Error			0x3FFu

#define Par_NoFAN			(0u)	 /* OFF */
#define Par_FANValueLow		(20u)	/* 20% 20190117_30 --> 20% Request of HKMC */
#define Par_FANValueMedium	(50u)	/* 50% */
#define Par_FANValueHigh	(70u)	/* 70% */

/* Default Value */
#define MEASURED_Q_VALUE_DEFAULT 		130
#define VRAIL_VOLTAGE_DEFAULT 			800
#define COIL_TEMP_DEFAULT 				372 //2048 /* 25'C */

/* DTC */
#define DTC_CANBusOff_ConfirmTime	Time_ms(1000)		/* CAN Bus Off */
#define DTC_CANBusOff_ExpireTime	Time_ms(1100)
#define Diag_B1621_ConfirmTime		Time_ms(2000)
#define Diag_B1621_RecoveryTime		Time_ms(500)		/* 20170106 ���?���� : ���?������ 500ms ���� ���?���ɽ� ���� ���� */

/* WPC & NFC Mode Control */
#define Par_NFCComErrTime Time_sec(60)				/* Confirm Time Of NFC Time Out  */
#define Par_NFCSeachingOffDelayTime Time_ms(500)	/* Delay Time to enter NFC Searching off */
#define Par_Timer_NFC_Tagging_Interval Time_ms(100)
// Command Chaining �׽�Ʈ ���� �ӽ� Parameter : 2,246 Bytes ����
#define Par_Timer_NFC_LongData_Receive_Timeout Time_ms(5000) // IAU ���� �� ���?���?Ȯ�� �� ���� �ʿ�

#define Par_WaitingDelay3Time Time_ms(1000)
#define Par_WaitingDelay4Time Time_ms(2000)

/* NFC LPCD */
#define Par_NFCSearchingTimeoutTime	Time_ms(1500)		/* Timeout Time of NFC Searching */
#define Par_DeviceStateWaitTime		Time_ms(3000)		/* Wait time of device detection */ 
#define Par_LPCDOffDelayConfirmTime	Time_sec(60)		/* Confirm time of LPCD Off Delay */

/* WPC Mode Status Control */
#define Par_IdleConfirm Time_ms(100)			/* Time for Idle Status */
#define Par_PhoneCheckTime Time_ms(1000)		/* Time for Finding Phone Exist */
#define Par_PhoneLeftWarning Time_sec(60)		/* Warning time of Phone on the PAD */
#define Par_PhoneReminderWarning Time_ms(500)	/* Warning time of Phone Reminder */
#define Par_PhoneLeftConfirm Time_ms(900)		/* Checking Time for Phone Exist Clear */
#define Par_ErrorHoldingCnt (10)				/* Amber LED Error Blinking Count */
#define Par_LEDBlinkTime Time_ms(500)			/* Amber LED Blinking Time */

/* LF Search */
#define Par_LfOffChkTime			Time_ms(3500)		/* 02 *//* SMK Searching ���� ���� �ð� */

/* Over Current */
#define Par_OvrCurrSetVal			4500 				/* 03 *//* Over Current Detecting Value : 4500mA */
#define Par_OvrCurrSetTime			Time_ms(150)		/* 04 *//* Over Current Detecting Time */
#define Par_OvrCurrCnt				10 					/* 05 *//* Over Current Detecting Count : 10 times */	
#define Par_ReOvrCurrSetTime		Time_sec(5)			/* 06 *//* Over Current Re-Detecting Time */

/* Temperature Sensor */
#define Par_SensorFaultSetTime			Diag_B1621_ConfirmTime	/* 07 *//* Temperature Sensor Error Time : 2 sec */
#define Par_TemperatureSensorShort		0x000Cu					/* (150'c) 12 : NTC Higher is colder */
#define Par_TemperatureSensorLineCut	0x0AC1u					/* (-40'c) 2753 : NTC Higher is colder, todolist : set this value for wpc unit */

/* Thermistor */
#define Par_TemperatureSensor_30 0x013Au /* 314 : NTC Higher is colder */
#define Par_TemperatureSensor_65 0x0067u /* 104 : NTC Higher is colder */
#define Par_TemperatureSensor_70 0x0059u /* 89 :  NTC Higher is colder */

/* Over Temperature */
#define Par_OverTempSetVal Par_TemperatureSensor_70	/* 35 *//*Over Temperature Detecting Value */ 
#define Par_OverTempRstVal Par_TemperatureSensor_65	/* 36 *//*Over Temperature Fault Cancellation Value */
#define Par_OverTempSetTime Time_sec(5)				/* 37 *//*Over Temperature Detecting Time */
#define Par_OverTempRstTime Time_sec(5)				/* 38 *//*Over Temperature Fault Cancellation Time */

/* Ind Animation */
//#define Par_INDBlinkTime	Time_ms(700)			/* Indicator Blink Time */
#define Par_INDOffTime		Time_ms(10)
#define Par_INDLightTime	Time_ms(1000)			/* Animation Blink Time */
#define Par_INDFadeInTime	Time_ms(1000)			/* Animation FadeIn Time */
#define Par_INDFadeOutTime	Time_ms(1000)			/* Animation FadeOut Time */

#define Par_INDPhaseStateTime Time_ms(1000)

#define MAX_TP_LENGTH_LOCAL		1024u

typedef struct STagDcm_MsgContextTypeLocal
{
	uint8 connection;
	uint16 reqDataLen;
	uint16 reqDataIdx;
    uint8 reqData[MAX_TP_LENGTH_LOCAL];
	uint16 resDataLen;
	uint16 resDataIdx;
	uint8 resData[MAX_TP_LENGTH_LOCAL];
}Dcm_MsgContextTypeLocal;

typedef struct
{
  uint8 PartNumber[10];
  uint8 HWVer[4];
  uint8 SWVer[4];
  uint8 SWInVer[3];
  uint8 SubSWVer[6];
  uint8 DBVer[4];
  uint8 CorpCode[4];
  uint8 SystemName[4];
  uint8 PlatHWVer[11];
  uint8 PlatVer[11];
}ECUData;

extern ECUData ECU_Read;

extern void Set_ECU_Identifier(void);


#endif  /* __DATA_H__ */
