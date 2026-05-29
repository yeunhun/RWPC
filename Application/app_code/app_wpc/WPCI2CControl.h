/***********************************************************************************************************************
* File Name    : WPC_10W_I2CControl.h
* Description  : I2C Control
***********************************************************************************************************************/

#ifndef WPC_I2C_CONTROL_H_
#define WPC_I2C_CONTROL_H_

#include "define.h"
#include "cy_scb_i2c.h"
#include "WPCVehicleOption.h"


/********************************************************************************
* TYPE DEFINE
********************************************************************************/
#define WCT_COIL_TEMPERATURE_TABLE_SIZE 126u


typedef enum
{
  CDN_IDX_Dummy = 0u,
  CDN_IDX_TX_state,
  CDN_IDX_TX_Status,
  CDN_IDX_TX_alert_alarm,
  CDN_IDX_selected_coil,
  CDN_IDX_coil_vol,
  CDN_IDX_coil_curr,
  CDN_IDX_IC_FW_version_Ready,
  CDN_IDX_IC_FW_version,
  CDN_MAX
}e_CDN;

typedef enum // TX_State
{
  TX_PHASE_START=0,
  TX_PHASE_PING=1,
  TX_PHASE_CONF=2,
  TX_PHASE_NEGOTIATION=7,
  TX_PHASE_POWETRANSFER=11,
  TX_PHASE_POWERCHARGING=12,
  TX_PHASE_POWERCHARGING1=15,
  TX_PHASE_STOP=66
}e_TXState;

typedef enum // TX_Status
{
	TX_Status_OK = 0,
	TX_Status_FODAlarm = 16,
	TX_Status_Charging = 17,
	TX_Status_FullCharged = 19,          /* CS100 code from Rx */
  	TX_Status_PreEPPCharging = 33,
  	TX_Status_EPPCharging = 49,
  	TX_Status_EPPFullCharged = 51,          /* EPP CS100 code from Rx */
	//TX_Status_FODError = 85
}e_TxStatus;

typedef enum
{
  TXAlertAlarm_OK = 						0x00,
  TXAlertAlarm_STOP = 						0x01,
  TXAlertAlarm_FULLCharge = 				0x0A,
  TXAlertAlarm_PowerLossFOD = 				0x10,
  TXAlertAlarm_OtherEndOfPowerRxEPT = 		0x11,
  TXAlertAlarm_ChargeCompleteRxEPT = 		0x12,
  TXAlertAlarm_InteranlFaultRxEPT = 		0x13,
  TXAlertAlarm_OverTemperatureRxEPT = 		0x14,
  TXAlertAlarm_OverVoltageRxEPT = 			0x15,
  TXAlertAlarm_OverCurrentRxEPT = 			0x16,
  TXAlertAlarm_BatteryFailureRxEPT = 		0x17,
  TXAlertAlarm_NoResponseRxEPT = 			0x18,
  TXAlertAlarm_AbortedNegotiationEPT = 		0x19,
  TXAlertAlarm_RestartRxEPT = 				0x20,
  TXAlertAlarm_Re_pingRxEPT = 				0x21,
  TXAlertAlarm_NFCTagRxEPT = 				0x22,
  TXAlertAlarm_NFCTagProtectionEPT = 		0x23,
  TXAlertAlarm_OverCurrentInternalBuck = 	0x24,
  TXAlertAlarm_OverTemperature = 			0x25,
  TXAlertAlarm_OverVoltalgeInternalBuck = 	0x26,
  TXAlertAlarm_UnderVoltageLockOut = 		0x27,
  TXAlertAlarm_QFOD = 						0x28,
  TXAlertAlarm_OverCurrentBridge = 			0x29,
  TXAlertAlarm_OverVoltageBridge = 			0x30,
  TXAlertAlarm_OverVoltageVIN = 			0x31,
  TXAlertAlarm_UnderVoltageBridge = 		0x32
}e_TXAlertAlarm;
typedef struct
{
  uint8   index;
  uint8   is_valid[CDN_MAX];
  uint8   TX_state;             /* Tx current state */
  uint8   TX_Status;            /*  Tx alert-alarm status */
  uint8	  TX_Fault_Reason;		/*  Tx alert-FOD alarm  */	
  uint8   selected_coil;        /* Working coil number of the coil that is presently selected for interoperating with the Receiver device */
  uint16  tx_coil_Q[3];         /* tx coil fault : coil 0 ~ 2 */
  uint16  coil_vol;             /* Inverter Voltage */
  uint16  coil_curr;            /* Inverter Current */
  uint16  charging_voltage;
  uint16  charging_current;
  uint8   Phoneset;
} st_tx_info;

typedef enum
{
  EraseFlashCtrl_Start = 0u,
  Update_Stop,
  Delay_Erase_Flash,
  Erase_Flash_zero,
  Erase_Flash_1st,
  Erase_Flash_2nd,
  Erase_Flash_3nd,
  Erase_Flash_4nd,
  Write_Flash_Cmd,
  Write_Flash_Data,
  Verify_Flash
} e_EraseFlashCtrl;

#define IS_WCT_STOP       		(GetX(kb_TX_State) == (uint8)TX_PHASE_STOP) && (GetX(kb_TX_Status) == (u8)TX_Status_OK)

#define IS_WCT_STANDBY    		(GetX(kb_TX_State) == (u8)TX_PHASE_START) || (GetX(kb_TX_State) == (u8)TX_PHASE_PING)


/*#define IS_WCT_CHARGING     ((GetX(kb_TX_State) == (u8)TX_PHASE_POWETRANSFER)&&((GetX(kb_TX_Status) == (u8)TX_Status_Charging) || (GetX(kb_TX_Status) == (u8)TX_Status_PreEPPCharging) || (GetX(kb_TX_Status) == (u8)TX_Status_EPPCharging)))*/
#define IS_WCT_CHARGING   		(GetX(kb_TX_State) == (u8)TX_PHASE_POWETRANSFER)


/* #define IS_WCT_FULLCHARGED_CS	((GetX(kb_TX_State) == (u8)TX_PHASE_POWETRANSFER) && (GetX(kb_TX_Status) == (u8)TX_Status_FullCharged)) */
#define IS_WCT_FULLCHARGED_CS	(GetX(kb_TX_Status) == (u8)TX_Status_FullCharged) || (GetX(kb_TX_Status) == (u8)TX_Status_EPPFullCharged)

#define IS_WCT_FODERROR     (GetX(kb_TX_Fault_Reason) == (u8)TXAlertAlarm_PowerLossFOD)
#define IS_WCT_OEPERROR     (GetX(kb_TX_Fault_Reason) == (u8)TXAlertAlarm_OtherEndOfPowerRxEPT)

uint8 I2C_Rx_Detect_Clear(void);
void TXCommInit(void);

uint8 GetTxData_TXState(void);
uint8 GetTxData_TXStatus(void);
uint8 GetTxData_TXFaultReason(void);
uint8 GetTxData_Phoneset(void);
uint8 GetTxData_selectedcoil(void);
uint16 GetTxData_coilvol(void);
uint16 GetTxData_coilcurr(void);
uint16 GetTxData_chargingcoilvol(void);
uint16 GetTxData_chargingcoilcurr(void);

uint8 GetTxData_CoilTempN_UDS(uint8 coil_num);

#define ERR_NONE 0

void i2c_test(void);

void WPC_I2C_Process_20ms(void);

#endif /* WPC_10W_I2CControl_H_ */
