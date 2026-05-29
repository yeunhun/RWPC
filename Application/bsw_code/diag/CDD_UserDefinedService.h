#include "Dcm_PCTypes.h"
#include "Rte_Dcm_Type.h"

/* 0x19 */
#define kReportNumberOfDTCByStatusMask		0x01u
#define kReportDTCByStatusMask				0x02u

#define kTestFailed			0x0u
#define kConfirmedDTC		0x3u
#define kWarningIndiccator	0x7u


/* 0x2F InOut Control */
#define	kDID_F0					0xF0u
#define kSupportedDID_00  		0x00u
#define kSupportedDID_10  		0x10u
#define kSupportedDID_20  		0x20u
#define kSupportedDID_40  		0x40u
#define kAmberLED_11			0x11u
#define kGreenLED_12			0x12u
#define kFANON_13				0x13u
#define kWCTReprogram			0x21u
#define KWCTCancel				0xFDu	//Cancel test
#define kWCTStuats				0xFEu	//Status test
#define kAmberLEDPWMDuty_31		0x31u
#define kGreenLEDPWMDuty_32		0x32u
#define kFANOnPWMDuty_33		0x33u

 
/*  For Forced Output Control */
#define kOperatingComplete	0x00U
#define ForceOn				0x03U	/* By HMC Specification */
#define ForceOff			0x00U	/* By HMC Specification */

#define Control_DTC_Detect_On     0x01u
#define Control_DTC_Detect_Off      0x02u

extern uint8 Get_DTC_BCAN_BusOff_Memorize(void);
extern void Set_DTC_BCAN_BusOff_Memorize(uint8 value);
extern uint8 Get_DTC_BCAN_BusOff_Present(void);
extern void Set_DTC_BCAN_BusOff_Present(uint8 value);
extern uint8 Get_DTC_LCAN_BusOff_Memorize(void);
extern void Set_DTC_LCAN_BusOff_Memorize(uint8 value);
extern uint8 Get_DTC_LCAN_BusOff_Present(void);
extern void Set_DTC_LCAN_BusOff_Present(uint8 value);
extern void Set_DTC_B1621_WPCInternalError_Present(uint8 value);
extern void Set_DTC_B1621_TemperatureSensorFault_Present(uint8 value);
extern void Set_DTC_B1621_TxCoilFault_Present(uint8 value);
extern void Set_DTC_B1621_FANFault_Present(uint8 value);
extern uint8 Get_DTC_B1621_Present(void);
extern void Set_DTC_B1621_Present(uint8 value);
extern uint8 Get_DTCClear_Count_BCAN_BusOff(void);
extern void Set_DTCClear_Count_BCAN_BusOff(uint8 value);
extern uint8 Get_DTCClear_Count_LCAN_BusOff(void);
extern void Set_DTCClear_Count_LCAN_BusOff(uint8 value);

extern Std_ReturnType Dcm_ClearDiagnosticInformation(Dcm_OpStatusType OpStatus, Dcm_MsgContextType *pMsgContext);
extern Std_ReturnType Dcm_ReadDTCInformation(Dcm_OpStatusType OpStatus, Dcm_MsgContextType *pMsgContext);
extern Std_ReturnType Dcm_InputOutputControlByIdentifier(Dcm_OpStatusType OpStatus, Dcm_MsgContextType *pMsgContext);
extern uint8 SetDiag_Supported_IOCBI(uint8 number, uint8 active);
extern uint8 SetDiag_Supported_IOCBI_SY(uint8 number, uint8 duty);
extern Std_ReturnType Dcm_ControlDTCSetting(Dcm_OpStatusType OpStatus, Dcm_MsgContextType *pMsgContext);

