#include "WPCEepControl.h"
#include "WPCI2CControl.h"
#include "Data.h"
#include "WPCTimer.h"
#include "define.h"

#include "WPCVehicleOption.h"

#include "app_input_type.h"
#include "app_input.h"
#include "app_output_type.h"
#include "app_output.h"

#include "Rte_CDD_WPCIC.h"

#include "cy_scb_i2c.h"


/********************************************************************************
* Global Variables
********************************************************************************/
extern uint8 b_UpdateFlashCmd;
uint8 State_OP_STOP = Off;
uint8 State_OP_RUN = Off;
uint8 State_OP_DETECT = Off;
static uint8 Run[6] = {0x0Du, 0x24u,0x02u, 0x00u, 0x01u, 0x00u}; // P9450 Command and Parameters Description_v0.6.pdf
static uint8 Stop[6] = {0x0Du, 0x24u, 0x03u, 0x00u, 0x01u, 0x00u}; // P9450 Command and Parameters Description_v0.6.pdf
static uint8 Run_Scan_Mode[6] = {0x0Du, 0x24u, 0x09u, 0x00u, 0x01, 0x00u}; // P9450 Command and Parameters Description_v0.6.pdf
/* Real Time System Data */
static uint8 RT_TX_State[2] = {0x0Bu, 0x00u};
static uint8 RT_TX_Status[2] = {0x0Bu, 0x08u};
//static uint8 RT_TX_Fault_Reason[2] = {0x0Bu, 0x07u};	//FOD
static uint8 RT_TX_alert_alarm[2] = {0x02u, 0xA4u};
static uint8 RT_Coil_Num[2] = {0x0Bu, 0x1Bu};
static uint8 RT_Coil_Vol_H[2] = {0x02u, 0x94u};
static uint8 RT_Coil_Vol_L[2] = {0x02, 0x95u};
static uint8 RT_Coil_Curr_H[2] = {0x02u, 0x96u};
static uint8 RT_Coil_Curr_L[2] = {0x02u, 0x97u};
static uint8 RI_Rx_Present[2] = {0x0Bu, 0x69u};

static uint8 I2CDataRxBuffer[4] = {0x00u, 0x00u, 0x00u, 0x00u};
#if defined(USE_CHARGE_IC_FWver_READ)
const uint8 RT_FW_Version[2] = {0x00u, 0x04u};
uint8 readSubSWVer_1st[4] = {0u, };
uint8 readSubSWVer_2nd[4] = {0u, };
uint8 readSubSWVer_3rd[4] = {0u, };
uint8 readSubSWVer_from_chargeIC[4] = {0u, };
uint8 readSubSWVer_from_chargeIC_tmp[4] = {0u, };
uint8 readSubSWVer_compare_confirm[4] = {0u, };
uint8 fwread = 5u;
uint8 fwReadConfirm_f = 0u;
#endif
uint8 Phoneset_is_valid;
st_tx_info tx_info;
sint32 i2c_status;
uint8 Rx_Detect_Clear;

static tTimer16 Timer_P9450_StartDelay = {Off, 0u};
static tTimer16 Timer_Run_Charge_Off_Check = {Off, 0u};

const uint16 gTABLE_WCT_COIL_TEMPERARUE[WCT_COIL_TEMPERATURE_TABLE_SIZE] = { /* -40 ~ 85 */
2753    ,   //  -40 0
2749    ,   //  -39 1
2744    ,   //  -38 2
2740    ,   //  -37 3
2735    ,   //  -36 4
2488    ,   //  -35 5
2241    ,   //  -34 6
2235    ,   //  -33 7
2228    ,   //  -32 8
2222    ,   //  -31 9
2216    ,   //  -30 10
2211    ,   //  -29 11
2206    ,   //  -28 12
2202    ,   //  -27 13
2197    ,   //  -26 14
1948    ,   //  -25 15
1943    ,   //  -24 16
1938    ,   //  -23 17
1934    ,   //  -22 18
1929    ,   //  -21 19
1691    ,   //  -20 20
1687    ,   //  -19 21
1683    ,   //  -18 22
1678    ,   //  -17 23
1674    ,   //  -16 24
1454    ,   //  -15 25
1450    ,   //  -14 26
1446    ,   //  -13 27
1442    ,   //  -12 28
1438    ,   //  -11 29
1240    ,   //  -10 30
1237    ,   //  -9  31
1233    ,   //  -8  32
1229    ,   //  -7  33
1226    ,   //  -6  34
1051    ,   //  -5  35
1048    ,   //  -4  36
1045    ,   //  -3  37
1042    ,   //  -2  38
1039    ,   //  -1  39
887     ,   //   0  40
884     ,   //   1  41
881     ,   //   2  42
879     ,   //   3  43
876   	,   //   4  44
746   	,   //   5  45
744   	,   //   6  46
741   	,   //   7  47
739   	,   //   8  48
737   	,   //   9  49
626   	,   //  10  50
624   	,   //  11  51
623   	,   //  12  52
621   	,   //  13  53
619   	,   //  14  54
526   	,   //  15  55
524   	,   //  16  56
523   	,   //  17  57
521   	,   //  18  58
520   	,   //  19  59
442   	,   //  20  60
441   	,   //  21  61
440   	,   //  22  62
438   	,   //  23  63
437  	,   //  24  64
372  	,   //  25  65
371  	,   //  26  66
370  	,   //  27  67
369  	,   //  28  68
368  	,   //  29  69
314  	,   //  30  70
313  	,   //  31  71
312  	,   //  32  72
311  	,   //  33  73
310  	,   //  34  74
266  	,   //  35  75
265  	,   //  36  76
264  	,   //  37  77
263  	,   //  38  78
263  	,   //  39  79
226  	,   //  40  80
225  	,   //  41  81
224  	,   //  42  82
224  	,   //  43  83
223  	,   //  44  84
192  	,   //  45  85
191  	,   //  46  86
191  	,   //  47  87
190  	,   //  48  88
190  	,   //  49  89
164  	,   //  50  90
163  	,   //  51  91
163  	,   //  52  92
162  	,   //  53  93
162  	,   //  54  94
140  	,   //  55  95
138  	,   //  56  96
135  	,   //  57  97
129  	,   //  58  98
124  	,   //  59  99
120	 	,   //  60  100
116  	,   //  61  101
113  	,   //  62  102
110  	,   //  63  103
106  	,   //  64  104
103  	,   //  65  105
100  	,   //  66  106
97  	,   //  67  107
95  	,   //  68  108
92		,   //  69  109
89 		,   //  70  110
87 		,   //  71  111
84 		,   //  72  112
82 		,   //  73  113
80 		,   //  74  114
77 		,   //  75  115
75 		,   //  76  116
73 		,   //  77  117
71 		,   //  78  118
69 		,   //  79  119
67 		,   //  80  120
65 		,   //  81  121
64 		,   //  82  122
62 		,   //  83  123
60 		,   //  84  124
59 		,   //  85  125
};

extern IoHwAb_LevelType VBATSW_EN_ReadDirect(void);
extern cy_en_scb_i2c_status_t I2C_MasterReceiveData(uint8_t * recv_data, uint8_t length, bool sendstop, uint32_t timeout);
extern cy_en_scb_i2c_status_t I2C_MasterSendData(const uint8 * send_data, uint8_t length, bool sendstop, uint32_t timeout);
extern cy_en_scb_i2c_status_t I2C_MasterReceiveMultiData(uint8_t * recv_data, uint8_t length, bool sendstop, uint32_t timeout);
void I2C_WPC_SendCommand(uint8 cmd);
void I2C_WPC_ReadRealTimeSystemData(const uint8 * Command, uint8 * rxBuff, uint8 txSize, uint8 rxSize);
void WPC_I2C_Process_20ms(void);
void TXCommInit(void);
void Run_Mode_Control(void);
void I2CGetProcess(void);
extern void set_p9450_force_reset(void);
#if defined(USE_CHARGE_IC_FWver_READ)
void ReverseArray(uint8 dataArr[], uint8 len);
uint8 decimalToBcd(uint8 decimal);
#endif

extern u8 PhoneWarningtoFOD;
void I2C_WPC_SendCommand(uint8 cmd)
{
  if(cmd == 0u)
  {
    i2c_status = I2C_MasterSendData(Run, sizeof(Run), 1, 10000);
  }
  else if(cmd == 1u)
  {
    i2c_status = I2C_MasterSendData(Stop, sizeof(Stop), 1, 10000);
  }
  else if(cmd == 2u)
  {
	i2c_status = I2C_MasterSendData(Run_Scan_Mode, sizeof(Run_Scan_Mode), 1, 10000);
  }

  if(i2c_status == ERR_NONE)
  {
    SetX(kb_DTCWPCInternalError, Off);
	i2c_status = ERR_NONE;

    if(i2c_status == ERR_NONE)
    {
      SetX(kb_DTCWPCInternalError, Off);
	  i2c_status = ERR_NONE;
      if(i2c_status == ERR_NONE)
      {
		SetX(kb_DTCWPCInternalError, Off);
      }
      else
      {
        SetX(kb_DTCWPCInternalError, On);
      }
	}
    else
    {
      SetX(kb_DTCWPCInternalError, On);
    }
  }
  else
  {
    SetX(kb_DTCWPCInternalError, On);
  }
}
uint8 chip_id_cmd[2] = {0x0A, 0x04};
uint8 chip_id_rx_data[2] = {0x00, 0x00};

void I2C_WPC_ReadRealTimeSystemData(const uint8 * Command, uint8 * rxBuff, uint8 txSize, uint8 rxSize)
{
  i2c_status = I2C_MasterSendData(Command, txSize, 1, 10000);


  if(i2c_status == ERR_NONE)
  {
    SetX(kb_DTCWPCInternalError, Off);

    if(rxSize == 1u)
    {
      i2c_status = I2C_MasterReceiveData(rxBuff, rxSize, 1, 10000);
    }
    else if(rxSize >= 2u)
    {
      i2c_status = I2C_MasterReceiveMultiData(rxBuff, rxSize, 1, 10000);
    }

    if(i2c_status == ERR_NONE)
    {
      SetX(kb_DTCWPCInternalError, Off);
    }
    else
    {
      SetX(kb_DTCWPCInternalError, On);
    }
  }
  else
  {
    SetX(kb_DTCWPCInternalError, On);
  }

  if(GetX(kb_DTCWPCInternalError) == On)
  {
    rxBuff[0] = 0x00u;
    rxBuff[1] = 0x00u;
  }
}

uint8 I2C_Rx_Detect_Clear(void)
{
  uint8 sendbuff[2] = {0x0Bu, 0x69u};
  uint8 ret;

  i2c_status = I2C_MasterSendData(sendbuff, sizeof(sendbuff), 1, 10000);

  if(i2c_status == ERR_NONE)
  {
    ret = On;
  }
  else
  {
    ret = Off;
  }

  return ret;
}

#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
extern uint8 get_wpc_ecu_reset(void);
extern void clr_wpc_ecu_reset(void);
extern void set_p9450_auto_reprog_start(void);
extern void set_p9450_auto_reprog_stop(void);
extern uint8 GetReprogrammingProgress(void);
extern uint8 Cmp_P9450_SWver(void);
extern void Set_p9450_Auto_Reprog_Retry_Ready(void);
extern uint8 Get_p9450_auto_reprog_retry(void);
extern void Clr_p9450_auto_reprog_retry(void);
extern void Set_P9450_SWver_to_rom(void);
extern void set_p9450_auto_reprog_ready(void);
extern uint8 get_p9450_auto_reprog_ready(void);
void Set_Fail_Safety_time(uint32 safety_time);

tTimer16 tmr_ChargeIC_Reprogmming_recover_delay = {Off,0};
uint8 cmp_result = 0;
#endif

#if defined(USE_CHARGE_IC_FWver_READ)
void I2CGetP9450VersionProcess(void);
#endif
void WPC_I2C_Process_20ms(void)
{
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
  UpTimer16(tmr_ChargeIC_Reprogmming_recover_delay);
#endif

  if(bStartupI2CDelayCnt > 0u)
  {
    bStartupI2CDelayCnt--;
  }
  else
  {
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
#if defined(USE_CHARGE_IC_FWver_READ)
    //I2CGetP9450VersionProcess();
    if((fwread == 0u) && ( (get_wpc_ecu_reset() == 1u) || (Get_p9450_auto_reprog_retry()==2u) ))
#else    
	if( (get_wpc_ecu_reset() == 1u) || (Get_p9450_auto_reprog_retry()==2u) )
#endif	
	{
      clr_wpc_ecu_reset();
      Clr_p9450_auto_reprog_retry();

      cmp_result = Cmp_P9450_SWver();
      switch(cmp_result)
      {
        case 1:
          Set_P9450_SWver_to_rom();
          break;
        case 2:
          set_p9450_auto_reprog_start();
          set_p9450_auto_reprog_ready();
          break;
        case 3:
          set_p9450_auto_reprog_start();
          set_p9450_auto_reprog_ready();
          break;
        default:
          // MISRA
          break;
      }
    }
#endif

    if((b_UpdateFlashCmd == Off) && (VBATSW_EN_ReadDirect()!=0))
    {
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
      if(tmr_ChargeIC_Reprogmming_recover_delay.run == On)
      {
        CancelTimer(tmr_ChargeIC_Reprogmming_recover_delay);
      }
#endif

      I2CGetProcess();
    }
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
    else if((b_UpdateFlashCmd == On) && (VBATSW_EN_ReadDirect()!=0) && (get_p9450_auto_reprog_ready()==On) )
    {
      if(tmr_ChargeIC_Reprogmming_recover_delay.run == Off)
      {
        StartTimer(tmr_ChargeIC_Reprogmming_recover_delay);
      }//                                                                                                          55000/10=5500
      else if((tmr_ChargeIC_Reprogmming_recover_delay.run == On) && (tmr_ChargeIC_Reprogmming_recover_delay.time > Time_ms(90000)))
      //else if((tmr_ChargeIC_Reprogmming_recover_delay.run == On) && (tmr_ChargeIC_Reprogmming_recover_delay.time > Time_ms(20000)))
      {
        set_p9450_auto_reprog_stop();
        Set_Fail_Safety_time(500u);
        Set_p9450_Auto_Reprog_Retry_Ready();
        CancelTimer(tmr_ChargeIC_Reprogmming_recover_delay);
      }
    }
    else
    {
      // MISRA
    }
#endif
  }
}

void TXCommInit(void)
{
  uint8 i;

  for(i=0u; i<(uint8)CDN_MAX; i++)
  {
    tx_info.is_valid[i] = 0u;
  }

  Phoneset_is_valid = 0u;

  tx_info.TX_state = 0x00u;                           /* Tx current state */
  tx_info.TX_Status = 0x00u;                          /* Tx alert-alarm status */
  tx_info.TX_Fault_Reason = 0x00u;

  tx_info.selected_coil = 0x00u;                      /* Working coil number of the coil that is presently selected for interoperating with the Receiver device */

  tx_info.tx_coil_Q[0] = MEASURED_Q_VALUE_DEFAULT;    /* tx coil MQV : coil 0 ~ 2 */

  tx_info.coil_vol = VRAIL_VOLTAGE_DEFAULT;           /* Inverter Voltage */
  tx_info.coil_curr = 0x0000u;                        /* Inverter Current */

  tx_info.charging_voltage = 0x0000u;
  tx_info.charging_current = 0x0000u;

  tx_info.Phoneset = 0x00u;
}


extern void set_p9450_force_reset(void);
extern void DigDir_VBATSW_EN_tmp(uint8 data);
extern void Set_stop_state(uint8 state);
extern uint8 Get_stop_state(void);
uint32 fail_safety_timer = 0;

#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
void Set_Fail_Safety_time(uint32 safety_time)
{
  fail_safety_timer = safety_time;
}
#endif
void Run_Mode_Control(void)
{
  UpTimer16(Timer_P9450_StartDelay);

#if defined(USE_CHARGE_IC_RUN_MODE_7sec_RESET)
  UpTimer16(Timer_Run_Charge_Off_Check);

  if(IsChgEvt(kb_IGN_IN, On))
  {
	StartTimer(Timer_Run_Charge_Off_Check);
  }
  else if((GetOutput(kC_WPC_PhnLftWrngRWPCSta) == (u8)kWPCWarning_Charging) || 
  		   (GetOutput(kC_WPC_PhnLftWrngRWPCSta) == (u8)kWPCWarning_ChargingComplete) ||
  		   (GetOutput(kC_WPC_PhnLftWrngRWPCSta) == (u8)kWPCWarning_Error) ||
  		   (GetX(kb_IGN_IN) == Off))
  {
   	  CancelTimer(Timer_Run_Charge_Off_Check);
  }
  else
  {
		if(Timer_Run_Charge_Off_Check.time > Time_sec(5))
		{
			CancelTimer(Timer_Run_Charge_Off_Check);
			fail_safety_timer = 500;
		}
		else
		{
		  
		}
  }
 #endif

  if((GetX(kb_WPCRunMode) == (u8)kRunMode_STOP) &&
    (State_OP_STOP == Off))
  {
    I2C_WPC_SendCommand(1);

    State_OP_STOP = On;
    State_OP_RUN = Off;
    State_OP_DETECT = Off;
	
    CancelTimer(Timer_P9450_StartDelay);
  }
  else if((GetX(kb_WPCRunMode) == (u8)kRunMode_RUN) &&
      (State_OP_RUN == Off))
  {
    I2C_WPC_SendCommand(0);
	
    State_OP_STOP = Off;
    State_OP_RUN = On;
    State_OP_DETECT = Off;
  }
  else if((GetX(kb_WPCRunMode) == (uint8)kRunMode_RX_DETECT) &&
      (State_OP_DETECT == Off))
  {
    tx_info.TX_state = TX_PHASE_PING;
    tx_info.TX_Status = TX_Status_OK;
    I2C_WPC_SendCommand(2);

    State_OP_STOP = Off;
    State_OP_RUN = Off;
    State_OP_DETECT = On;

    CancelTimer(Timer_P9450_StartDelay);
  }
  else
  {
    /* MISRA-C */
  }

  if((GetX(kb_WPCRunMode) == (u8)kRunMode_RUN) &&
    (Timer_P9450_StartDelay.run == Off) &&
    IS_WCT_STOP)
  {
    StartTimer(Timer_P9450_StartDelay);
  }
  else if((Timer_P9450_StartDelay.time >= Time_sec(2)) &&
      IS_WCT_STOP)
  { // 20181024_WPC RUN && P9261 STOP -> P9261 RUN
    //I2C_WPC_SendCommand(Run);
    I2C_WPC_SendCommand(0);
    CancelTimer(Timer_P9450_StartDelay);
  }
  else if(Timer_P9450_StartDelay.time >= Time_sec(2))
  {
    CancelTimer(Timer_P9450_StartDelay);
  }
  else
  {
    /* MISRA-C */
  }
}

#if defined(USE_CHARGE_IC_FWver_READ)
extern void Set_ECU_Read_SubSWVer(uint8 dataArr[4]);
#endif
void I2CGetProcess(void)
{
  static uint8 cnt = 0u;
  uint16 temp = 0u;

	Run_Mode_Control();
	if(GetX(kb_WPCRunMode) == (u8)kRunMode_RX_DETECT)
	{
		I2C_WPC_ReadRealTimeSystemData(RI_Rx_Present, I2CDataRxBuffer, sizeof(RI_Rx_Present), 1);
		
	    if((I2CDataRxBuffer[0] & 0x03u) == 0x03u)
	    {
	    	tx_info.Phoneset = 0x01u;
	    }
	    else
	    {
	    	tx_info.Phoneset = 0x00u;
	    }
	    Phoneset_is_valid = 1u;
	}
	else
	{
		switch(tx_info.index)
		{
	    	case (uint8)CDN_IDX_TX_state:
	      		I2C_WPC_ReadRealTimeSystemData(RT_TX_State, I2CDataRxBuffer, sizeof(RT_TX_State), 1);

	      	if(I2CDataRxBuffer[0] <= 66u)
	      	{

	        	tx_info.TX_state = (u8)I2CDataRxBuffer[0];

	        	tx_info.is_valid[CDN_IDX_TX_state] = 1u;
	      	}
	      	break;

	    	case (uint8)CDN_IDX_TX_Status:
	      		I2C_WPC_ReadRealTimeSystemData(RT_TX_Status, I2CDataRxBuffer, sizeof(RT_TX_Status), 1);

	        	tx_info.TX_Status = (u8)I2CDataRxBuffer[0];
	        	tx_info.is_valid[CDN_IDX_TX_Status] = 1u;
	      		break;
	      	
			case (uint8)CDN_IDX_TX_alert_alarm:
            	I2C_WPC_ReadRealTimeSystemData(RT_TX_alert_alarm, I2CDataRxBuffer, sizeof(RT_TX_alert_alarm), 1);
            	tx_info.is_valid[CDN_IDX_TX_alert_alarm] = 1u;
            	tx_info.TX_Fault_Reason = (u8)I2CDataRxBuffer[0];
			    break;

	    	case (uint8)CDN_IDX_selected_coil:

		  		I2C_WPC_ReadRealTimeSystemData(RT_Coil_Num, I2CDataRxBuffer, sizeof(RT_Coil_Num), 1);

	      		tx_info.selected_coil = (u8)I2CDataRxBuffer[0];
	      		tx_info.is_valid[CDN_IDX_selected_coil] = 1u;

	      		break;

	    	case (uint8)CDN_IDX_coil_vol:

	      		I2C_WPC_ReadRealTimeSystemData(RT_Coil_Vol_H, &I2CDataRxBuffer[0], sizeof(RT_Coil_Vol_H), 1);
				I2C_WPC_ReadRealTimeSystemData(RT_Coil_Vol_L, &I2CDataRxBuffer[1], sizeof(RT_Coil_Vol_L), 1);
		

	      		tx_info.coil_vol = (((u16)I2CDataRxBuffer[1]<<8u)+((u16)I2CDataRxBuffer[0]));
	      		tx_info.is_valid[CDN_IDX_coil_vol] = 1u;

		      	if(GetX(kb_ChargingState) == On)    // 20180824 : ���� ���� (����/���� ����)
			    {
			        tx_info.charging_voltage = tx_info.coil_vol;
			    }
			    else
			    {
			        tx_info.charging_voltage = 0u;
			    }
			
	      		break;
	    	case (uint8)CDN_IDX_coil_curr:

				I2C_WPC_ReadRealTimeSystemData(RT_Coil_Curr_H, &I2CDataRxBuffer[0], sizeof(RT_Coil_Curr_H), 1);
				I2C_WPC_ReadRealTimeSystemData(RT_Coil_Curr_L, &I2CDataRxBuffer[1], sizeof(RT_Coil_Curr_L), 1);

				temp = (((u16)I2CDataRxBuffer[1]<<8u)+((u16)I2CDataRxBuffer[0]));

		      	if(temp >= 4500)
		      	{
		        	if(cnt > 3u)
		        	{
		          		cnt = 0u;
		          		tx_info.coil_curr = temp;
		        	}
		        	else
		        	{
		          		cnt++;
		        	}
		      	}
		      	else
		      	{
		        	cnt = 0u;
		        	tx_info.coil_curr = temp;
		      	}

	      		tx_info.is_valid[CDN_IDX_coil_curr] = 1u;

		      	if(GetX(kb_ChargingState) == On)    // 20180824 : ���� ���� (����/���� ����)
		      	{
		        	tx_info.charging_current = tx_info.coil_curr;
		      	}
		      	else
		      	{
		        	tx_info.charging_current = 0u;
		      	}

#if defined(USE_CHARGE_IC_FWver_READ)
		      	if(fwread==0)
		      	{
		      	  tx_info.index = CDN_MAX;
		      	}
#endif

		  		break;
#if defined(USE_CHARGE_IC_FWver_READ)
      		case (uint8)CDN_IDX_IC_FW_version_Ready:
	    	    break;
			case (uint8)CDN_IDX_IC_FW_version:
				if(fwread > 0u)
				{
					/* Read Sub SW ver 1st */
					I2C_WPC_ReadRealTimeSystemData(RT_FW_Version, &I2CDataRxBuffer[0], sizeof(RT_FW_Version), sizeof(I2CDataRxBuffer));
          			memcpy(readSubSWVer_1st, I2CDataRxBuffer, sizeof(I2CDataRxBuffer));
					/* Read Sub SW ver 2nd */
          			I2C_WPC_ReadRealTimeSystemData(RT_FW_Version, &I2CDataRxBuffer[0], sizeof(RT_FW_Version), sizeof(I2CDataRxBuffer));
          			memcpy(readSubSWVer_2nd, I2CDataRxBuffer, sizeof(I2CDataRxBuffer));
					/* Read Sub SW ver 3rd */
          			I2C_WPC_ReadRealTimeSystemData(RT_FW_Version, &I2CDataRxBuffer[0], sizeof(RT_FW_Version), sizeof(I2CDataRxBuffer));
          			memcpy(readSubSWVer_3rd, I2CDataRxBuffer, sizeof(I2CDataRxBuffer));
					/* Compare Read Sub SW ver 1st and Read Sub SW ver 2nd */
			        if( memcmp(readSubSWVer_1st, readSubSWVer_2nd, sizeof(I2CDataRxBuffer)) == 0u )
			        {
			        	fwReadConfirm_f = 1u;
			            memcpy(readSubSWVer_compare_confirm, readSubSWVer_1st, sizeof(I2CDataRxBuffer));
			       	}
			       	/* Compare Read Sub SW ver 1st and Read Sub SW ver 3rd */
			        else if( memcmp(readSubSWVer_1st, readSubSWVer_3rd, sizeof(I2CDataRxBuffer)) == 0u )
			        {
			        	fwReadConfirm_f = 2u;
			            memcpy(readSubSWVer_compare_confirm, readSubSWVer_1st, sizeof(I2CDataRxBuffer));
			       	}
			       	/* Compare Read Sub SW ver 2nd and Read Sub SW ver 3rd */
			        else if( memcmp(readSubSWVer_2nd, readSubSWVer_3rd, sizeof(I2CDataRxBuffer)) == 0u )
			        {
			            fwReadConfirm_f = 3u;
			            memcpy(readSubSWVer_compare_confirm, readSubSWVer_2nd, sizeof(I2CDataRxBuffer));
			        }
			        else
			        {
			            fwReadConfirm_f = 0u;
			        }

		          	if(fwReadConfirm_f > 0u)
		          	{
		            	readSubSWVer_from_chargeIC_tmp[0] = readSubSWVer_compare_confirm[3];
		            	readSubSWVer_from_chargeIC_tmp[1] = readSubSWVer_compare_confirm[2];
		            	readSubSWVer_from_chargeIC_tmp[2] = readSubSWVer_compare_confirm[1];
		            	readSubSWVer_from_chargeIC_tmp[3] = readSubSWVer_compare_confirm[0];

		            	readSubSWVer_from_chargeIC[0] = decimalToBcd(readSubSWVer_from_chargeIC_tmp[0]);
		            	readSubSWVer_from_chargeIC[1] = decimalToBcd(readSubSWVer_from_chargeIC_tmp[1]);
		            	readSubSWVer_from_chargeIC[2] = decimalToBcd(readSubSWVer_from_chargeIC_tmp[2]);
		            	readSubSWVer_from_chargeIC[3] = decimalToBcd(readSubSWVer_from_chargeIC_tmp[3]);

		            	Set_ECU_Read_SubSWVer(readSubSWVer_from_chargeIC);

		            	fwread = 0u;
		          	}
		          	else
		          	{
		            	fwread--;
		          	}
				}	
				break;
#endif				
	    	default:
	      		tx_info.index = 0u;
	      	break;
	  	}
	  	if(tx_info.index < (uint8)CDN_MAX)
	  	{
	    	tx_info.index++;
	  	}  
	}
}

#if defined(USE_CHARGE_IC_FWver_READ)

void Retry_Reading_Charge_IC_Version(void)
{
  memset(readSubSWVer_1st, 0, sizeof(readSubSWVer_1st));
  memset(readSubSWVer_2nd, 0, sizeof(readSubSWVer_2nd));
  memset(readSubSWVer_3rd, 0, sizeof(readSubSWVer_3rd));
  memset(readSubSWVer_compare_confirm, 0, sizeof(readSubSWVer_compare_confirm));
  memset(readSubSWVer_from_chargeIC_tmp, 0, sizeof(readSubSWVer_from_chargeIC_tmp));
  memset(readSubSWVer_from_chargeIC, 0, sizeof(readSubSWVer_from_chargeIC));

  Set_ECU_Read_SubSWVer(readSubSWVer_from_chargeIC);

  fwReadConfirm_f = 0u;
  fwread = 5u;
}

void ReverseArray(uint8 dataArr[], uint8 len)
{
  uint8 startNum = 0;
  uint8 endNum = len - 1;

  while(startNum < endNum)
  {
    uint8 tmpData = dataArr[startNum];
    dataArr[startNum] = dataArr[endNum];
    dataArr[endNum] = tmpData;

    startNum++;
    endNum--;
  }
}

uint8 decimalToBcd(uint8 decimal)
{
  uint8 bcd = 0;
  uint8 digit, remainder, idx;


  for(idx = 0; decimal > 0; idx++)
  {
      digit = decimal % 10;
      remainder = digit % 10;
      bcd |= remainder << (4 * idx);
      decimal /= 10;
  }

  return bcd;
}

#endif

uint8 GetTxData_TXState(void)
{
  if(tx_info.is_valid[CDN_IDX_TX_state] > 0u)
  {
    return tx_info.TX_state;
  }
  else
  {
    return 0u;
  }
}

uint8 GetTxData_TXStatus(void)
{
  if(tx_info.is_valid[CDN_IDX_TX_Status] > 0u)
  {
    return tx_info.TX_Status;
  }
  else
  {
    return 0u;
  }
}

uint8 GetTxData_TXFaultReason(void)
{
  if(tx_info.is_valid[CDN_IDX_TX_alert_alarm] > 0u)
  {
    return tx_info.TX_Fault_Reason;
  }
  else
  {
    return 0u;
  }
}

uint8 GetTxData_Phoneset(void)
{
  if(Phoneset_is_valid > 0u)
  {
    return tx_info.Phoneset;
  }
  else
  {
    return 0u;
  }
}

uint8 GetTxData_selectedcoil(void)
{
  if(tx_info.is_valid[CDN_IDX_selected_coil] > 0u)
  {
    return tx_info.selected_coil;
  }
  else
  {
    return 0u;
  }
}

uint16 GetTxData_coilvol(void)
{
  if(tx_info.is_valid[CDN_IDX_coil_vol] > 0u)
  {
    return tx_info.coil_vol;
  }
  else
  {
    return 0u;
  }
}

uint16 GetTxData_coilcurr(void)
{
  if(tx_info.is_valid[CDN_IDX_coil_curr] > 0u)
  {
    return tx_info.coil_curr;
  }
  else
  {
    return 0u;
  }
}

uint16 GetTxData_chargingcoilvol(void)
{
  if((tx_info.is_valid[CDN_IDX_coil_vol] > 0u) && (GetX(kb_ChargingState) == On))
  {
    return tx_info.charging_voltage;
  }
  else
  {
    return 0u;
  }
}

uint16 GetTxData_chargingcoilcurr(void)
{
  if((tx_info.is_valid[CDN_IDX_coil_curr] > 0u) && (GetX(kb_ChargingState) == On))
  {
    return tx_info.charging_current;
  }
  else
  {
    return 0u;
  }
}

uint8 GetTxData_CoilTempN_UDS(uint8 coil_num)
{

  uint16 temp_raw = COIL_TEMP_DEFAULT;
  uint8 idx = 65u;   /* return temperature value 65 = 25'C */
  uint8 i = 0u;
  coil_num = coil_num - 1u;

  if(coil_num < 3u)
  {
    if(coil_num == 0u)
    {
      temp_raw = b_Temperature_Sensor1;
    }
    else if(coil_num == 1u)
    {
      temp_raw = b_Temperature_Sensor2;
    }
    else
    {
      temp_raw = b_Temperature_Sensor3;
    }

    for(i=0; i<WCT_COIL_TEMPERATURE_TABLE_SIZE; i++)
    {
      if(temp_raw >= gTABLE_WCT_COIL_TEMPERARUE[i])
      {
        if(i == 0u)
        {
          idx = i;
        }
        else
        {
          idx = i - 1u;     // temp_raw = 410, i = 63, temp != 23 --> 22.xx
        }
        break;
      }
    }

    if(i >= WCT_COIL_TEMPERATURE_TABLE_SIZE)
    {
      idx = WCT_COIL_TEMPERATURE_TABLE_SIZE-1u;
    }
  }



  return idx;
}

