/*******************************************************************************
 * Project        :   SP2 IBU
 * File Name      :   local_input.c
 * Compiler   :   Eclipse
 * Author         :   MyoungKwon Choi (mk210@seoyonelec.com)
 * Created at     :   2017-06-23
 * Code Editor  :   Source Insight (Recomended Font : D2Coding / Size 10)
 * Revision       :   Version 0.1
 * Copyright    :   (c) Copyright Seoyon Electronics Co.Ltd. All Rights Reserved
 * Description    :
 *
 ******************************************************************************/




/*******************************************************************************
  Include Headers
*******************************************************************************/
#include "WPCVehicleOption.h"
#include "WPCType.h"
#include "Define.h"
#include "WPCTimer.h"
#include "Data.h"
#include "Rte_SWC_input.h"
#include "Port.h"

#include "app_input_type.h"
#include "app_input.h"

#include "WPCI2CControl.h"
#include "WPCLogicControl.h"






/*******************************************************************************
  Declare Function Prototypes
*******************************************************************************/
IoHwAb_ValueType Battery_Real_ReadDirect(void);
IoHwAb_ValueType ACC_ReadDirect(void);
static IoHwAb_LevelType VN7140AS_MULTI_ReadDirect(void);
IoHwAb_LevelType VBATSW_EN_ReadDirect(void);
static IoHwAb_LevelType FAN_DIAG_ReadDirect(void);
static IoHwAb_ValueType Input_CoilTemp_ReadDirect(void);
static IoHwAb_ValueType Input_CoilTemp_ReadDirect2(void);
static IoHwAb_ValueType Input_CoilTemp_ReadDirect3(void);
void Input_BatteryVoltage(void);
void Stabilize_Battery(void);
void Input_IGNVoltage(void);
void Stabilize_IGN(void);
void Set_BatteryMonitoring_Chattering(void);
void Set_BatteryMonitoring_Hysteresis(void);
void Battery_Monitoring_For_CAN(void);
void Input_CheckOperatingVoltage(void);
void TempSensorFailMonitor(void);
u16 GetIGNADValue(void);

void Input_Internal_10ms(void);
void Input_Local(void);
void Locking_FAN(void);

extern void DigDir_VBATSW_EN_tmp(uint8 data);
extern void aging_counter_func(void);

/********************************************************************************
* Defines
********************************************************************************/
static  u16 b_CriticalBatteryUnder  = kCriticalBatteryUnder;
static  u16 b_NoramlBatteryUnder  = kNoramlBatteryUnder;
static  u16 b_NormalBatteryOver   = kNormalBatteryOver;
static  u16 b_CriticalBatteryOver = kCriticalBatteryOver;
/*******************************************************************************
  Define Constant and Macro
*******************************************************************************/
typedef struct
{
  uint8  active;     /* prefix value : low active=0 */
  uint8  on_time;    /* prefix value : sw on time   */
  uint8  off_time;   /* prefix value : sw off time */
  uint8  sw_status;  /* 0=deactive state     */
  uint8  old_value;  /* old port value       */
  uint8  change;     /* change mark        */
  uint8  counter;    /* chattering counter   */
  uint8  prev_value; /* previous value buffer */
} sw_input;


static sw_input sw_array[kMaxLocalInput] = {
    {0x00u,0x00u,0x00u,0x00u,0x00u,0x00u,0x00u},  /* kL_IPS_MUL  */
    {0x00u,0x00u,0x00u,0x00u,0x00u,0x00u,0x00u},  /* kL_FAN_DIAG */
};

static const sw_input sw_init[]=
{
  {1,Time_ms(30u),Time_ms(30u),0,0,0,0,0},        /* kL_IPS_MUL  */
  {1,Time_ms(30u),Time_ms(30u),0,0,0,0,0},        /* kL_FAN_DIAG */
};

/*******************************************************************************
  Declare  Variables
*******************************************************************************/


tTimer8 tmr_BAT_stab_delay = {Off,0};
uint8  BAT_stab_finish_flg = Off;

uint8 IGN_stab_reset_flg = On;
uint8 IGN_stabilized = Off;

uint8 Temp_stab_reset_flg = On;
uint8 Temp_stabilized[CoilMax] = {Off, Off, Off};

e_OperatingVoltageState StateOperatingVoltage = OperatingVoltageState_Normal;

/*Temp Sensor : from WCT*/
uint16 b_Temperature_Sensor1 = COIL_TEMP_DEFAULT; /*AD Value for Temperature Sensor 1*/
uint16 b_Temperature_Sensor2 = COIL_TEMP_DEFAULT; /*AD Value for Temperature Sensor 2*/
uint16 b_Temperature_Sensor3 = COIL_TEMP_DEFAULT; /*AD Value for Temperature Sensor 3*/

uint8 b_Temperature_SensorFault1 = Off;
uint8 b_Temperature_SensorFault2 = Off;
uint8 b_Temperature_SensorFault3 = Off;


uint16 b_CurrentCurr = 0u;     /*from P9261 : wInputCurrent : 4000mA Cut Off */
uint16 b_VoltageState = 0u;    /*from P9261 : */
uint8 b_SelecteCoil = 0u;

/*Battery/Ign monitoring*/
uint16 APP_Stabilize_BAT_Source = 0u;
uint16 APP_BeforeChatt_BAT_Source = 0u;
uint16 APP_BAT_Source = 0u;

uint16 APP_Stabilize_IGN_Source = 0u;
uint16 APP_BeforeChatt_IGN_Source = 0u;
uint16 APP_IGN_Source = 0u;

uint16 APP_CoilTemp_Source = 0u;

uint8 bStartupI2CDelayCnt = 0u;

tTimer8 tmr_CAN_Start_delay = {Off,0u};


tTimer8 Timer_IGNONSet = {Off, 0u};
tTimer8 Timer_IGNOFFSet = {Off, 0u};


#if defined(USE_OVER_VOLTAGE_CHARGE_IC_PROTECT)
u32 batt_readDirct_ok_cnt = 0;
u32 batt_readDirct_not_ok_cnt = 0;

Std_ReturnType Battery_ChargeIC_Real_ReadDirect(IoHwAb_ValueType * rslt_value)
{
  Std_ReturnType ret_cnt = RTE_E_OK;


  ret_cnt =   Rte_Call_R_AnaInDir_Battery_Real_ReadDirect(rslt_value, 1u);

  if(ret_cnt==RTE_E_OK)
  {
    batt_readDirct_ok_cnt++;
  }
  else
  {
    batt_readDirct_not_ok_cnt++;
  }

  return ret_cnt;
}
#endif


IoHwAb_ValueType Battery_Real_ReadDirect(void)
{
  IoHwAb_ValueType ReturnValue;

  Rte_Call_R_AnaInDir_Battery_Real_ReadDirect(&ReturnValue, 1u);

  return (IoHwAb_ValueType)ReturnValue;
}

IoHwAb_ValueType ACC_ReadDirect(void)
{
  IoHwAb_ValueType ReturnValue;

  Rte_Call_R_AnaInDir_ACC_ReadDirect(&ReturnValue, 1u);

  return (IoHwAb_ValueType)ReturnValue;
}



IoHwAb_LevelType VN7140AS_MULTI_ReadDirect(void)
{
  IoHwAb_LevelType ReturnValue;

  Rte_Call_R_DigDir_VN7140AS_MULTI_ReadDirect(&ReturnValue);

  return (IoHwAb_LevelType)ReturnValue;
}

IoHwAb_LevelType VBATSW_EN_ReadDirect(void)
{
  IoHwAb_LevelType ReturnValue;

  Rte_Call_R_DigDir_VBATSW_EN_ReadDirect(&ReturnValue);

  return (IoHwAb_LevelType)ReturnValue;
}

static IoHwAb_LevelType FAN_DIAG_ReadDirect(void)
{
  IoHwAb_LevelType ReturnValue;

  Rte_Call_R_DigDir_FAN_DIAG_ReadDirect(&ReturnValue);

  return (IoHwAb_LevelType)ReturnValue;
}


static IoHwAb_ValueType Input_CoilTemp_ReadDirect(void)
{
  IoHwAb_ValueType ReturnValue;

  Rte_Call_SWC_Input_R_AnaInDir_Thermistor_ReadDirect(&ReturnValue, 1u);

  return (IoHwAb_ValueType)ReturnValue;
}

static IoHwAb_ValueType Input_CoilTemp_ReadDirect2(void)
{
  IoHwAb_ValueType ReturnValue;

  Rte_Call_SWC_Input_R_AnalnDir_Thermistor2_ReadDirect(&ReturnValue, 1u);

  return (IoHwAb_ValueType)ReturnValue;
}

static IoHwAb_ValueType Input_CoilTemp_ReadDirect3(void)
{
  IoHwAb_ValueType ReturnValue;

  Rte_Call_SWC_Input_R_AnalnDir_Thermistor3_ReadDirect(&ReturnValue, 1u);

  return (IoHwAb_ValueType)ReturnValue;
}
void Set_BatteryMonitoring_Chattering(void)
{
  static u8 BAT_status = 0u;
  static u8 BAT_status_Old = 0u;
  static tTimer8  tmr_BATChatt = {Off,0};


  UpTimer8(tmr_BATChatt);

  if((IsInit() == Off))
  {
    APP_Stabilize_BAT_Source = APP_BeforeChatt_BAT_Source;
  }
  else if(APP_BeforeChatt_BAT_Source < kCriticalBatteryUnder)   //6.8V �̸�
  {
    BAT_status = 1u;
  }
  else if(APP_BeforeChatt_BAT_Source < (kCriticalBatteryUnder + kBattery_hysteresis))   //6.8V �̻� 7V �̸�
  {
    BAT_status = 2u;
  }
  else if(APP_BeforeChatt_BAT_Source < kNoramlBatteryUnder)   //7V �̻� 8.8V �̸�
  {
    BAT_status = 3u;
  }
  else if(APP_BeforeChatt_BAT_Source < (kNoramlBatteryUnder + kBattery_hysteresis))   //8.8V �̻� 9V �̸�
  {
    BAT_status = 4u;
  }
  else if(APP_BeforeChatt_BAT_Source < (kNormalBatteryOver - kBattery_hysteresis))    //9V �̻� 16V �̸�
  {
    BAT_status = 5u;
  }
  else if(APP_BeforeChatt_BAT_Source < kNormalBatteryOver)    //16V �̻� 16.2V �̸�
  {
    BAT_status = 6u;
  }
  else if(APP_BeforeChatt_BAT_Source < (kCriticalBatteryOver - kBattery_hysteresis))    //16.2V �̻� 18V �̸�
  {
    BAT_status = 7u;
  }
  else if(APP_BeforeChatt_BAT_Source < kCriticalBatteryOver)    //18V �̻� 18.2V �̸�
  {
    BAT_status = 8u;
  }
  else                              //18.2V �̻�
  {
    BAT_status = 9u;
  }

  if(tmr_BATChatt.run == Off)
  {
    StartTimer(tmr_BATChatt);
  }
  else if(BAT_status != BAT_status_Old)
  {
    BAT_status_Old = BAT_status;
    StartTimer(tmr_BATChatt);
  }
  else if(tmr_BATChatt.time >= Par_BATChattTime)
  {
    APP_Stabilize_BAT_Source = APP_BeforeChatt_BAT_Source;
  }
  else
  {
    /* MISRA-C Rule*/
  }
}

void Set_BatteryMonitoring_Hysteresis(void)
{
  static  u8 Batt_InhibitNormalUnderhysteresis = Off;
  static  u8 Batt_InhibitNormalOverhysteresis = Off;
  static  u8 Batt_InhibitCriticalUnderhysteresis = Off;
  static  u8 Batt_InhibitCriticalOverhysteresis = Off;

  if(APP_Stabilize_BAT_Source < kCriticalBatteryUnder)
  {
    Batt_InhibitNormalUnderhysteresis = On;
    Batt_InhibitCriticalUnderhysteresis = On;
    b_CriticalBatteryUnder = kCriticalBatteryUnder + kBattery_hysteresis;
    b_NoramlBatteryUnder = kNoramlBatteryUnder + kBattery_hysteresis;

    Batt_InhibitNormalOverhysteresis = Off;
    Batt_InhibitCriticalOverhysteresis = Off;
    b_NormalBatteryOver = kNormalBatteryOver;
    b_CriticalBatteryOver = kCriticalBatteryOver;
  }
  else if(APP_Stabilize_BAT_Source < (kCriticalBatteryUnder + kBattery_hysteresis))
  {
    if(Batt_InhibitCriticalUnderhysteresis == On)
    {
      b_CriticalBatteryUnder = kCriticalBatteryUnder + kBattery_hysteresis;
    }
    else
    {
      b_CriticalBatteryUnder = kCriticalBatteryUnder;
    }
    b_NoramlBatteryUnder = kNoramlBatteryUnder + kBattery_hysteresis;

    Batt_InhibitNormalUnderhysteresis = On;
    Batt_InhibitNormalOverhysteresis = Off;
    Batt_InhibitCriticalOverhysteresis = Off;
    b_NormalBatteryOver = kNormalBatteryOver;
    b_CriticalBatteryOver = kCriticalBatteryOver;
  }
  else if(APP_Stabilize_BAT_Source < kNoramlBatteryUnder)
  {
    Batt_InhibitNormalUnderhysteresis = On;
    b_NoramlBatteryUnder = kNoramlBatteryUnder + kBattery_hysteresis;

    Batt_InhibitCriticalUnderhysteresis = Off;
    Batt_InhibitNormalOverhysteresis = Off;
    Batt_InhibitCriticalOverhysteresis = Off;
    b_CriticalBatteryUnder = kCriticalBatteryUnder;
    b_NormalBatteryOver = kNormalBatteryOver;
    b_CriticalBatteryOver = kCriticalBatteryOver;
  }
  else if(APP_Stabilize_BAT_Source < (kNoramlBatteryUnder + kBattery_hysteresis))
  {
    if(Batt_InhibitNormalUnderhysteresis == On)
    {
      b_NoramlBatteryUnder = kNoramlBatteryUnder + kBattery_hysteresis;
    }
    else
    {
      b_NoramlBatteryUnder = kNoramlBatteryUnder;
    }

    Batt_InhibitCriticalUnderhysteresis = Off;
    Batt_InhibitNormalOverhysteresis = Off;
    Batt_InhibitCriticalOverhysteresis = Off;
    b_CriticalBatteryUnder = kCriticalBatteryUnder;
    b_NormalBatteryOver = kNormalBatteryOver;
    b_CriticalBatteryOver = kCriticalBatteryOver;
  }
  else if(APP_Stabilize_BAT_Source < (kNormalBatteryOver - kBattery_hysteresis))
  {
    Batt_InhibitCriticalUnderhysteresis = Off;
    Batt_InhibitNormalUnderhysteresis = Off;
    Batt_InhibitCriticalOverhysteresis = Off;
    Batt_InhibitNormalOverhysteresis = Off;
    b_CriticalBatteryUnder = kCriticalBatteryUnder;
    b_NoramlBatteryUnder = kNoramlBatteryUnder;
    b_NormalBatteryOver = kNormalBatteryOver;
    b_CriticalBatteryOver = kCriticalBatteryOver;
  }
  else if(APP_Stabilize_BAT_Source < kNormalBatteryOver)
  {
    if(Batt_InhibitNormalOverhysteresis == On)
    {
      b_NormalBatteryOver = kNormalBatteryOver - kBattery_hysteresis;
    }
    else
    {
      b_NormalBatteryOver = kNormalBatteryOver;
    }

    Batt_InhibitCriticalUnderhysteresis = Off;
    Batt_InhibitNormalUnderhysteresis = Off;
    Batt_InhibitCriticalOverhysteresis = Off;
    b_CriticalBatteryUnder = kCriticalBatteryUnder;
    b_NoramlBatteryUnder = kNoramlBatteryUnder;
    b_CriticalBatteryOver = kCriticalBatteryOver;
  }
  else if(APP_Stabilize_BAT_Source < (kCriticalBatteryOver - kBattery_hysteresis))
  {
    Batt_InhibitNormalOverhysteresis = On;
    b_NormalBatteryOver = kNormalBatteryOver - kBattery_hysteresis;

    Batt_InhibitCriticalUnderhysteresis = Off;
    Batt_InhibitNormalUnderhysteresis = Off;
    Batt_InhibitCriticalOverhysteresis = Off;
    b_CriticalBatteryUnder = kCriticalBatteryUnder;
    b_NoramlBatteryUnder = kNoramlBatteryUnder;
    b_CriticalBatteryOver = kCriticalBatteryOver;
  }
  else if(APP_Stabilize_BAT_Source < kCriticalBatteryOver)
  {
    if(Batt_InhibitCriticalOverhysteresis == On)
    {
      b_CriticalBatteryOver = kCriticalBatteryOver - kBattery_hysteresis;
    }
    else
    {
      b_CriticalBatteryOver = kCriticalBatteryOver;
    }
    b_NormalBatteryOver = kNormalBatteryOver - kBattery_hysteresis;

    Batt_InhibitNormalOverhysteresis = On;
    Batt_InhibitCriticalUnderhysteresis = Off;
    Batt_InhibitNormalUnderhysteresis = Off;
    b_CriticalBatteryUnder = kCriticalBatteryUnder;
    b_NoramlBatteryUnder = kNoramlBatteryUnder;
  }
  else
  {
    b_NormalBatteryOver = kNormalBatteryOver - kBattery_hysteresis;
    Batt_InhibitNormalOverhysteresis = On;
    b_CriticalBatteryOver = kCriticalBatteryOver - kBattery_hysteresis;
    Batt_InhibitCriticalOverhysteresis = On;

    Batt_InhibitCriticalUnderhysteresis = Off;
    Batt_InhibitNormalUnderhysteresis = Off;
    b_CriticalBatteryUnder = kCriticalBatteryUnder;
    b_NoramlBatteryUnder = kNoramlBatteryUnder;
  }
}

u8 Battery_isThresholdUnder(e_Battery_Inhibit batt_condition)
{
  u8 StatusReturn = On;

  switch(batt_condition)
  {
  case Critical_Inhibit_Low:
    if(APP_Stabilize_BAT_Source < b_CriticalBatteryUnder)
    {
      StatusReturn = On;
    }
    else
    {
      StatusReturn = Off;
    }
    break;
  case Normal_Inhibit_Low:
    if(APP_Stabilize_BAT_Source < b_NoramlBatteryUnder)
    {
      StatusReturn = On;
    }
    else
    {
      StatusReturn = Off;
    }
    break;
  case Normal_Inhibit_High:
    if(APP_Stabilize_BAT_Source < b_NormalBatteryOver)
    {
      StatusReturn = On;
    }
    else
    {
      StatusReturn = Off;
    }
    break;
  case Critical_Inhibit_High:
    if(APP_Stabilize_BAT_Source < b_CriticalBatteryOver)
    {
      StatusReturn = On;
    }
    else
    {
      StatusReturn = Off;
    }
    break;

  default:
    /* MISRA-C */
    break;

  }

  return StatusReturn;
}

u8 Battery_isThresholdOver(e_Battery_Inhibit batt_condition)
{
  u8 StatusReturn = On;

  switch(batt_condition)
  {
  case Critical_Inhibit_Low:
    if(APP_Stabilize_BAT_Source >= b_CriticalBatteryUnder)
    {
      StatusReturn = On;
    }
    else
    {
      StatusReturn = Off;
    }
    break;
  case Normal_Inhibit_Low:
    if(APP_Stabilize_BAT_Source >= b_NoramlBatteryUnder)
    {
      StatusReturn = On;
    }
    else
    {
      StatusReturn = Off;
    }
    break;
  case Normal_Inhibit_High:
    if(APP_Stabilize_BAT_Source >= b_NormalBatteryOver)
    {
      StatusReturn = On;
    }
    else
    {
      StatusReturn = Off;
    }
    break;
  case Critical_Inhibit_High:
    if(APP_Stabilize_BAT_Source >= b_CriticalBatteryOver)
    {
      StatusReturn = On;
    }
    else
    {
      StatusReturn = Off;
    }
    break;

  default:
    /* MISRA-C */
    break;

  }

  return StatusReturn;
}

static void Set_BatteryMonitoring_Inhibit(void)
{
  /* Normal Inhibit flag set */
  if((Battery_isThresholdUnder(Normal_Inhibit_High) == On)&&
    (Battery_isThresholdOver(Normal_Inhibit_Low) == On))
  {
    SetX(u1g_InhibitNormalBatt, Off);
    SetX(u1g_InhibitNormalBattOver, Off);
    SetX(u1g_InhibitNormalBattUnder, Off);
  }
  else if(Battery_isThresholdUnder(Normal_Inhibit_High) == Off)
  {
    SetX(u1g_InhibitNormalBatt, On);
    SetX(u1g_InhibitNormalBattOver, On);
    SetX(u1g_InhibitNormalBattUnder, Off);
  }
  else if(Battery_isThresholdOver(Normal_Inhibit_Low) == Off)
  {
    SetX(u1g_InhibitNormalBatt, On);
    SetX(u1g_InhibitNormalBattOver, Off);
    SetX(u1g_InhibitNormalBattUnder, On);
  }
  else
  {
    /* MISRA CODING RULE */
  }

  /* Critical Inhibit flag set */
  if((Battery_isThresholdUnder(Critical_Inhibit_High) == On)&&
    (Battery_isThresholdOver(Critical_Inhibit_Low) == On))
  {
    SetX(u1g_InhibitCriticalBatt, Off);
    SetX(u1g_InhibitCriticalBattOver, Off);
    SetX(u1g_InhibitCriticalBattUnder, Off);
  }
  else if(Battery_isThresholdUnder(Critical_Inhibit_High) == Off)
  {
    SetX(u1g_InhibitCriticalBatt, On);
    SetX(u1g_InhibitCriticalBattOver, On);
    SetX(u1g_InhibitCriticalBattUnder, Off);
  }
  else if(Battery_isThresholdOver(Critical_Inhibit_Low) == Off)
  {
    SetX(u1g_InhibitCriticalBatt, On);
    SetX(u1g_InhibitCriticalBattOver, Off);
    SetX(u1g_InhibitCriticalBattUnder, On);
  }
  else
  {
    /* MISRA CODING RULE */
  }
}


void Stabilize_Battery(void) // 10ms task
{
  static u16  BAT_array[BAT_ArrayMAX]={0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,
                     0u,0u,0u,0u,0u,0u,0u,0u,0u,0u};
  static  u16 APP_BAT_Source_Old = 0u;
  static  u8  BAT_array_pos = 0u;
  static  u8  BAT_array_full = Off;
  static  u8  BAT_SameData_cnt = 0u;
  u32 BAT_array_sum = 0u;
  u8  i = 0u;

  UpTimer8(tmr_BAT_stab_delay);

  if(tmr_BAT_stab_delay.run == Off)
  {
    /* ó�� ���� �� or LOWEST���� WakeUp �� ���� (timer�� �������� �� ���) */
    /* APP_BeforeChatt_BAT_Source = APP_BAT_Source; */
    StartTimer(tmr_BAT_stab_delay);
    BAT_array_full = Off;
    BAT_array_pos = 0u;
  }
  else if((tmr_BAT_stab_delay.time >= T_BAT_stab_delayTime) && (BAT_array_full == On))
  {/* ���͸� ����͸� �迭 ���� �����Ͱ� ��� �Ҵ�� ���� �� ��� ���� */
    if(GetX(kb_BatteryPowerState) == Off)
    {
      SetX(kb_BatteryPowerState, On);
    }

    BAT_array[BAT_array_pos] = APP_BAT_Source;
    BAT_array_pos++;

    if(BAT_array_pos >= BAT_ArrayMAX)
    {
      BAT_array_pos = 0u;
    }

    if(APP_BAT_Source == APP_BAT_Source_Old)
    {
      BAT_SameData_cnt++;
      if(BAT_SameData_cnt >= Par_SameDataCnt)
      {/* ���� ������ 6ȸ ���� ���� �� �ش� ������ �迭 ���� */
        BAT_SameData_cnt = 0u;
        for(i=0u; i<BAT_ArrayMAX; i++)
        {
          BAT_array[i] = APP_BAT_Source;
        }
      }
    }
    else
    {
      BAT_SameData_cnt = 0u;
    }

    for(i=0u; i<BAT_ArrayMAX; i++)
    {
      BAT_array_sum += BAT_array[i];
    }
    APP_BeforeChatt_BAT_Source = (u16)(BAT_array_sum / BAT_ArrayMAX);
  }
  else if(BAT_array_full == Off)
  {/* ���͸� ����͸� �迭 ���� �����Ͱ� ��� �Ҵ���� ���� ��� ���� */
    BAT_array[BAT_array_pos] = APP_BAT_Source;
    BAT_array_pos++;
    if(BAT_array_pos >= BAT_ArrayMAX)
    {
      BAT_array_full = On;
      BAT_array_pos = 0u;

      for(i=0u; i<BAT_ArrayMAX; i++)
      {
        BAT_array_sum += BAT_array[i];
      }

      APP_BeforeChatt_BAT_Source = (u16)(BAT_array_sum / BAT_ArrayMAX);
      BAT_stab_finish_flg = On;
    }
#if 0
    if(tmr_BAT_stab_delay.time == T_BAT_stab_delayTime)
    {
      APP_BeforeChatt_BAT_Source = APP_BAT_Source;
      BAT_stab_finish_flg = On;
    }
#endif
  }
  else
  {
    /* MISRA-C */
  }

  APP_BAT_Source_Old = APP_BAT_Source;
}

void Stabilize_IGN(void)
{
  static u16 IGN_array[IGN_ArrayMAX]={0u,0u,0u,0u,0u,0u};
  static u8 IGN_array_pos = 0u;
  u32 IGN_array_sum = 0u;
  u16 IGN_Min = 0u;
  u16 IGN_Max = 0u;
  u8 i = 0u;

  if(IGN_stab_reset_flg == On)
  {
    /* ó�� ���� �� or LOWEST���� WakeUp �� ���� (timer�� �������� �� ���) */
    IGN_stab_reset_flg = Off;
    IGN_stabilized = 0u;
    IGN_array_pos = 0u;
  }

/* Buffering */
  if(IGN_stabilized == On)
  {/* IGN �迭 ���� �����Ͱ� ��� �Ҵ�� ���� �� ��� ���� */
    IGN_array[IGN_array_pos] = APP_IGN_Source;
    IGN_array_pos++;

    if(IGN_array_pos >= IGN_ArrayMAX)
    {
      IGN_array_pos = 0u;
    }

    for(i=0u; i<IGN_ArrayMAX; i++)
    {
      IGN_array_sum += IGN_array[i];
    }

/* min, max ���� : ������ ����... */
    IGN_Min = IGN_array[0];

    for(i=1u; i<IGN_ArrayMAX; i++)
    {
      if(IGN_array[i] < IGN_Min)
      {
        IGN_Min = IGN_array[i];
      }
    }

    IGN_Max = IGN_array[0];

    for(i=1u; i<IGN_ArrayMAX; i++)
    {
      if(IGN_array[i] > IGN_Max)
      {
        IGN_Max = IGN_array[i];
      }
    }
    IGN_array_sum -= IGN_Min;
    IGN_array_sum -= IGN_Max;
    APP_Stabilize_IGN_Source = (u16)(IGN_array_sum / (u16)(IGN_ArrayMAX-2u)); /* divide (ArrayMax-2) : Min, Max */
  }
  else if(IGN_stabilized == Off)
  {/* ���͸� ����͸� �迭 ���� �����Ͱ� ��� �Ҵ���� ���� ��� ���� */
    IGN_array[IGN_array_pos] = APP_IGN_Source;
    IGN_array_pos++;

    for(i=0u; i<IGN_array_pos; i++)
    {
      IGN_array_sum += IGN_array[i];
    }

    APP_BeforeChatt_IGN_Source = (u16)(IGN_array_sum/IGN_array_pos);

    if(IGN_array_pos >= IGN_ArrayMAX)
    {
      IGN_stabilized = 1u;
      IGN_array_pos = 0u;
    }
    else
    {
      /* MISRA-C RULE */
    }
  }
  else
  {
    /* MISRA-C RULE */
  }
}

u16 GetIGNADValue(void)
{
  if(IGN_stabilized > 0u)
  {
    return APP_Stabilize_IGN_Source;
  }
  else
  {
    return APP_BeforeChatt_IGN_Source;
  }
}

void Battery_Monitoring_For_CAN(void)
{
  UpTimer8(tmr_CAN_Start_delay);

  if((APP_BAT_Source < kCriticalBatteryUnder) ||
    (APP_BAT_Source > kCriticalBatteryOver))
  {
    SetX(kb_CAN_Inactive, (u8)CANInactive_On);
    CancelTimer(tmr_CAN_Start_delay);
  }
  else if((APP_BAT_Source >= (kCriticalBatteryUnder + kBattery_hysteresis)) &&
    (APP_BAT_Source <= (kCriticalBatteryOver - kBattery_hysteresis)))
  {
    if((GetX(kb_CAN_Inactive) == (u8)CANInactive_On) && (tmr_CAN_Start_delay.run == Off))
    {
      StartTimer(tmr_CAN_Start_delay);
    }
    else if((tmr_CAN_Start_delay.run == On) && (tmr_CAN_Start_delay.time > Time_ms(180)))
    //else if((tmr_CAN_Start_delay.run == On) && (tmr_CAN_Start_delay.time > Time_ms(160))) //20190320_For Test Can
    {
      SetX(kb_CAN_Inactive, (u8)CANInactive_Off);
      CancelTimer(tmr_CAN_Start_delay);
    }
    else if(tmr_CAN_Start_delay.run == Off)
    {
      SetX(kb_CAN_Inactive, (u8)CANInactive_Off);
    }
    else
    {
      /* Misra-C */
    }
  }
  else
  {
    /* Misra-C */
  }
}

void Input_BatteryVoltage(void)
{

  APP_BAT_Source = Battery_Real_ReadDirect();

  Stabilize_Battery();
  if(BAT_stab_finish_flg == On)
  {
    Set_BatteryMonitoring_Chattering();
    Set_BatteryMonitoring_Hysteresis();
    Set_BatteryMonitoring_Inhibit();
  }
}

#if defined(USE_OVER_VOLTAGE_CHARGE_IC_PROTECT)
void Protection_for_chargeIC(void);
void Protection_for_chargeIC_time_Measure(void);
#define CHARGE_IC_CHATT_MAX 2
#define CHARGE_IC_CHATT_UNDER_MAX 4
uint8 protection_flag = 0u;
uint16 input_voltage_for_chargeIC_var = 0;
uint16 input_voltage_IGN_for_chargeIC_var = 0;
uint16 input_voltage_for_chargeIC_Chat = 0;
uint16 input_voltage_for_chargeIC_sum = 0;
uint16  input_voltage_arr[CHARGE_IC_CHATT_MAX] = {0, };
uint8  input_voltage_idx = 0;
uint8  input_voltage_for_chargeI_over_cnt = 0;
uint8  input_voltage_for_chargeI_under_cnt = 0;
tTimer8 tmr_Protection_for_chargeIC = {Off,0};
e_OperatingVoltageState StateOperatingVoltage_for_ChargeIC = OperatingVoltageState_Normal;
e_OperatingVoltageState StateOperatingVoltage_for_ChargeIC_before = OperatingVoltageState_Normal;
uint8 test_charge_ic_en_f = 0;
#define OVER_MINUS_COR 40
u32 chargeIC_over_volt_time_Measure_cnt = 0;
u8 chargeIC_over_detection_f = 0;
void Protection_for_chargeIC_time_Measure(void)
{
  if(chargeIC_over_detection_f==0)
  {
    if( Battery_ChargeIC_Real_ReadDirect(&input_voltage_for_chargeIC_var) != RTE_E_OK)
    {

    }
    else
    {
      if(input_voltage_for_chargeIC_Chat > (kWPCOperatingVoltageOver + kBattery_hysteresis_dot_5V)) // 16.5V
      {
        chargeIC_over_volt_time_Measure_cnt++;
        if(chargeIC_over_volt_time_Measure_cnt>=8)
        {
          chargeIC_over_detection_f = 1;
          DigDir_VBATSW_EN_tmp(0);
        }
      }
      else if(input_voltage_for_chargeIC_Chat <= kWPCOperatingVoltageOver)
      {
        chargeIC_over_volt_time_Measure_cnt = 0;
        DigDir_VBATSW_EN_tmp(1);
      }
      else
      {
        // MISRA
      }
    }
  }
}

extern uint32 fail_safety_timer;
extern uint8 State_OP_RUN;
extern State_OP_DETECT;
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
extern void Set_p9450_Auto_Reprog_Retry_Start(void);
extern uint8 Get_p9450_auto_reprog_retry(void);
#endif
void Protection_for_chargeIC(void)
{
  uint8 idx;

  if( Battery_ChargeIC_Real_ReadDirect(&input_voltage_for_chargeIC_var) != RTE_E_OK)
  {
    // MISRA
  }
  else
  {
    input_voltage_for_chargeIC_Chat = input_voltage_for_chargeIC_var;

    switch(StateOperatingVoltage_for_ChargeIC)
    {
    case OperatingVoltageState_Normal:
      if(input_voltage_for_chargeIC_Chat < (kWPCOperatingVoltageUnder - kBattery_hysteresis_dot_5V)) /* 8.5V */
      {
        StateOperatingVoltage_for_ChargeIC = OperatingVoltageState_Low;
      }                                         // 3126                     110 = 3236          3164  3179 3185 3189
      else if(input_voltage_for_chargeIC_Chat > (kWPCOperatingVoltageOver + kBattery_hysteresis_dot_5V)) /* 16.5V */
      {
        StateOperatingVoltage_for_ChargeIC = OperatingVoltageState_High;
      }
      else
      {
        /* MISRA CODING RULE */
      }
      break;

    case OperatingVoltageState_Low:
      if(input_voltage_for_chargeIC_Chat > (kWPCOperatingVoltageOver + kBattery_hysteresis_dot_5V)) // 16.5V
      {
        StateOperatingVoltage_for_ChargeIC = OperatingVoltageState_High;
      }
      else if(input_voltage_for_chargeIC_Chat >= kWPCOperatingVoltageUnder) // 9V
      {
        StateOperatingVoltage_for_ChargeIC = OperatingVoltageState_Normal;
        bStartupI2CDelayCnt = 100u; /* 2ms Task : 200ms */
      }
      else
      {
        /* MISRA CODING RULE */
      }
      break;

    case OperatingVoltageState_High:
      if(input_voltage_for_chargeIC_Chat < (kWPCOperatingVoltageUnder - kBattery_hysteresis_dot_5V)) // 8.5V
      {
        StateOperatingVoltage_for_ChargeIC = OperatingVoltageState_Low;
      }
      else if(input_voltage_for_chargeIC_Chat <= kWPCOperatingVoltageOver) // 16V
      {
        StateOperatingVoltage_for_ChargeIC = OperatingVoltageState_Normal;
        bStartupI2CDelayCnt = 100u;  /* 2ms Task : 200ms */
      }
      else
      {
        /* MISRA CODING RULE */
      }
      break;

    default:
      StateOperatingVoltage_for_ChargeIC = OperatingVoltageState_Normal;
      break;
    }

  #if 1
    if(StateOperatingVoltage_for_ChargeIC==OperatingVoltageState_High)
    {
      if(StateOperatingVoltage_for_ChargeIC==StateOperatingVoltage_for_ChargeIC_before)
      {
        if(input_voltage_for_chargeI_over_cnt < CHARGE_IC_CHATT_MAX)
        {
          input_voltage_for_chargeI_over_cnt++;
          if(input_voltage_for_chargeI_over_cnt>=CHARGE_IC_CHATT_MAX)
          {
            input_voltage_for_chargeI_over_cnt = 0;
            DigDir_VBATSW_EN_tmp(0);
            protection_flag = 1u;
            test_charge_ic_en_f = 0;
          }
        }
      }
      else
      {
        input_voltage_for_chargeI_over_cnt = 0;
      }
    }
    else
    {
      if(StateOperatingVoltage_for_ChargeIC==StateOperatingVoltage_for_ChargeIC_before)
      {
        if(input_voltage_for_chargeI_under_cnt < CHARGE_IC_CHATT_UNDER_MAX)
        {
          input_voltage_for_chargeI_under_cnt++;
          if(input_voltage_for_chargeI_under_cnt >= CHARGE_IC_CHATT_UNDER_MAX)
          {
            input_voltage_for_chargeI_under_cnt = 0;

#if defined(USE_CHARGE_IC_RUN_MODE_7sec_RESET)
            if(fail_safety_timer >= 2u)
            {

              fail_safety_timer--;
              DigDir_VBATSW_EN_tmp(0);
            }
            else if(fail_safety_timer == 1u)
            {
              fail_safety_timer = 0;
              bStartupI2CDelayCnt = 20;
              State_OP_RUN = Off;
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
              if(Get_p9450_auto_reprog_retry()==1u)
              {
                Set_p9450_Auto_Reprog_Retry_Start();
              }
#endif
            }
            else
            {
              DigDir_VBATSW_EN_tmp(1);
            }
#else
            DigDir_VBATSW_EN_tmp(1);
#endif

            test_charge_ic_en_f = 1;
            protection_flag = 0u;
          }
        }
      }
      else
      {
        input_voltage_for_chargeI_under_cnt = 0;
      }
    }
  #endif

    StateOperatingVoltage_for_ChargeIC_before = StateOperatingVoltage_for_ChargeIC;
  }
}
#endif

void Input_IGNVoltage(void)
{
  APP_IGN_Source = ACC_ReadDirect();
  Stabilize_IGN();
}

void Input_CheckOperatingVoltage(void)
{
  switch(StateOperatingVoltage)
  {
  case OperatingVoltageState_Normal:
    if(APP_Stabilize_BAT_Source < (kWPCOperatingVoltageUnder - kBattery_hysteresis_dot_5V)) /* 8.5V */
    {
      StateOperatingVoltage = OperatingVoltageState_Low;
    }
    else if(APP_Stabilize_BAT_Source > (kWPCOperatingVoltageOver + kBattery_hysteresis_dot_5V)) /* 16.5V */
    {
      StateOperatingVoltage = OperatingVoltageState_High;
    }
    else
    {
      /* MISRA CODING RULE */
    }
    break;

  case OperatingVoltageState_Low:
    if(APP_Stabilize_BAT_Source > (kWPCOperatingVoltageOver + kBattery_hysteresis_dot_5V)) // 16.5V
    {
      StateOperatingVoltage = OperatingVoltageState_High;
    }
    else if(APP_Stabilize_BAT_Source >= kWPCOperatingVoltageUnder) // 9V
    {
      StateOperatingVoltage = OperatingVoltageState_Normal;
    }
    else
    {
      /* MISRA CODING RULE */
    }
    break;

  case OperatingVoltageState_High:
    if(APP_Stabilize_BAT_Source < (kWPCOperatingVoltageUnder - kBattery_hysteresis_dot_5V)) // 8.5V
    {
      StateOperatingVoltage = OperatingVoltageState_Low;
    }
    else if(APP_Stabilize_BAT_Source <= kWPCOperatingVoltageOver) // 16V
    {
      StateOperatingVoltage = OperatingVoltageState_Normal;
    }
    else
    {
      /* MISRA CODING RULE */
    }
    break;

  default:
    StateOperatingVoltage = OperatingVoltageState_Normal;
    break;
  }
}
uint8 init_startup_i2c_f = 0;
uint8 stop_state = 0;
volatile uint8 vbat_switching_time_cnt = 0u;
void Set_stop_state(uint8 state);
void Set_stop_state(uint8 state)
{
  stop_state = state;
}
uint8 Get_stop_state(void);
uint8 Get_stop_state(void)
{
  return stop_state;
}

void set_p9450_force_reset(void)
{
  vbat_switching_time_cnt = 50;
}

u16 Stabilize_CoilTemp(uint8 Num, uint16 APP_CoilTemp_Source)
{
	static u16 Temp_array[CoilMax][Temp_ArrayMax] = {{0u,0u,0u,0u,0u},
													{0u,0u,0u,0u,0u},
													{0u,0u,0u,0u,0u}};
	static u8 Temp_array_pos[CoilMax] = {0u,0u,0u};
	u32 Temp_array_sum[CoilMax] = {0u,0u,0u};
	u16 Stabilize_Temp;
	u8 i;
	Num = Num - 1u;

	if(Temp_stab_reset_flg == On)
	{
		Temp_stab_reset_flg = Off;
		
		for(i=0u; i<CoilMax; i++)
		{
			Temp_stabilized[i] = Off;
			Temp_array_pos[i] = 0u;
		}
	}

	if(Temp_stabilized[Num] == On)
	{
		Temp_array[Num][Temp_array_pos[Num]] = APP_CoilTemp_Source;
		Temp_array_pos[Num]++;

		if(Temp_array_pos[Num] >= Temp_ArrayMax)
		{
			Temp_array_pos[Num] = 0u;
		}

		for(i=0u; i<Temp_ArrayMax; i++)
		{
			Temp_array_sum[Num] += Temp_array[Num][i];
		}

		Stabilize_Temp = (u16)(Temp_array_sum[Num] / Temp_ArrayMax);
	}
	else
	{
		Temp_array[Num][Temp_array_pos[Num]] = APP_CoilTemp_Source;
		Temp_array_pos[Num]++;

		for(i=0u; i<Temp_array_pos[Num]; i++)
		{
			Temp_array_sum[Num] += Temp_array[Num][i];
		}

		Stabilize_Temp = (u16)(Temp_array_sum[Num] / Temp_array_pos[Num]);
		
		if(Temp_array_pos[Num] >= Temp_ArrayMax)
		{
			Temp_stabilized[Num] = On;
			Temp_array_pos[Num] = 0u;
		}
	}
	
	return Stabilize_Temp;
}

void Input_CoilTemp1(void)	/* evry 20ms */
{
	APP_CoilTemp_Source = Input_CoilTemp_ReadDirect();
	b_Temperature_Sensor1 = Stabilize_CoilTemp(1u, APP_CoilTemp_Source);
}
extern u8 PhoneWarningtoFOD;
extern st_tx_info tx_info;
void Input_CoilTemp2(void)
{
	APP_CoilTemp_Source = Input_CoilTemp_ReadDirect2();
	b_Temperature_Sensor2 = Stabilize_CoilTemp(2u, APP_CoilTemp_Source);
}

void Input_CoilTemp3(void)
{
	APP_CoilTemp_Source = Input_CoilTemp_ReadDirect3();
	b_Temperature_Sensor3 = Stabilize_CoilTemp(3u, APP_CoilTemp_Source);
}

extern void Set_Fail_Safety_time(uint32 safety_time);
void Input_Internal_10ms(void)
{
  u16 A_IGN_Value = ACC_ReadDirect();
  u8 State_BCAN_ErrPin;

  UpTimer8(Timer_IGNONSet);
  UpTimer8(Timer_IGNOFFSet);

  Battery_Monitoring_For_CAN();

  //State_BCAN_ErrPin = (u8)gpio_get_pin_level(can0_ERR1);

  if((Timer_IGNOFFSet.run == Off) && (A_IGN_Value <= kIGN_OFF_Voltage))     // 7V
  {
    StartTimer(Timer_IGNOFFSet);
    CancelTimer(Timer_IGNONSet);
  }
  else if((Timer_IGNONSet.run == Off) && (A_IGN_Value >= kIGN_ON_Voltage))    // 4V
  {
    StartTimer(Timer_IGNONSet);
    CancelTimer(Timer_IGNOFFSet);
  }
  else if((Timer_IGNOFFSet.run == On) && (Timer_IGNOFFSet.time >= Time_ms(80)))
  {
    SetX(kb_IGN_IN, Off);
  }
  else if((Timer_IGNONSet.run == On) && (Timer_IGNONSet.time >= Time_ms(100)))
  {
    SetX(kb_IGN_IN, On);
    aging_counter_func();
#if defined(USE_IGN_ON_CHARGE_IC_RESET)
    if(IsChgEvt(kb_IGN_IN, On))
    {
      if( GetXOld(kb_WPCRunMode) == (u8)kRunMode_RUN )
      {
        fail_safety_timer = 500;
      }
    }
#endif
  }
  else
  {
    /* MISRA CODING RULE */
  }

#if !defined(USE_OVER_VOLTAGE_CHARGE_IC_PROTECT)  /* Charging IC Protection */
  if((APP_Stabilize_BAT_Source >= 300) &&           // 20191209_Preventing resetting from low voltage
      (VBATSW_EN_ReadDirect()==0))
  {
      DigDir_VBATSW_EN_tmp(1);
      bStartupI2CDelayCnt = 20u;
  }
#endif
  if(IsChgEvt(kb_WPCPower, On))
  {
      ClrEvt(kb_WPCPower);
      TXCommInit();
  }

  if(State_BCAN_ErrPin == kLow)
  {
    SetX(kb_CANError_BCAN, On);
  }
  else
  {
    SetX(kb_CANError_BCAN, Off);
  }

  if((GetX(kb_WPCPower) == On) &&
    (VBATSW_EN_ReadDirect() != 0) &&
    (bStartupI2CDelayCnt == 0u))
  {
      SetX(kb_TX_State, GetTxData_TXState());
      SetX(kb_TX_Status, GetTxData_TXStatus());
      SetX(kb_TX_Fault_Reason, GetTxData_TXFaultReason());
	  
      b_CurrentCurr = GetTxData_coilcurr();
      b_VoltageState = GetTxData_coilvol();
      if (PhoneWarningtoFOD == On)
      {
        tx_info.TX_Fault_Reason = TX_Status_OK;
        PhoneWarningtoFOD = Off;
      }
      if(IS_WCT_CHARGING)
      {
        SetX(kb_DeviceState, (u8)DeviceStates_Charging);
		if(IS_WCT_FULLCHARGED_CS)
      	{
        	SetX(kb_DeviceState, (u8)DeviceStates_Full_Charge);
      	}
      }
      if(IS_WCT_FODERROR)
      {
        SetX(kb_DeviceState, (u8)DeviceStates_FODError);
	  }
      else if(IS_WCT_STANDBY)
      {
        SetX(kb_DeviceState, (u8)DeviceStates_Standby);
      }
      else if(IS_WCT_STOP)
      {
        SetX(kb_DeviceState, (u8)DeviceStates_Init);
      }
      else
      {
        /* Misra-C */
      }

      TempSensorFailMonitor();    // 20180824 : ��ǰ �� NG �׸� �����ݿ�

      if(GetX(kb_WPCRunMode) == (u8)kRunMode_RX_DETECT)
      {
        SetX(kb_WPCPhoneExist, GetTxData_Phoneset());
	  }
  
      if(GetX(kb_ChargingState) == On)
      {
        SetX(kL_IPS_MUL, sw_array[0].sw_status);

        if((GetX(kL_IPS_MUL) == On) ||
          (GetX(kL_FAN_DIAG) == On))
        {
          SetX(kb_FANFault, On);
        }
        else
        {
          SetX(kb_FANFault, Off);
        }
      }
      else
      {
        SetX(kb_FANFault, Off);
      }
    }
    else
    {
      SetX(kb_DeviceState, (u8)DeviceStates_Init);
    }
}

void Input_Local(void)
{
 	SwInput(0, (u8)VN7140AS_MULTI_ReadDirect);
}


void TempSensorFailMonitor(void)
{
	Input_CoilTemp1();
	Input_CoilTemp2();
	Input_CoilTemp3();

	if((b_Temperature_Sensor1 >= Par_TemperatureSensorLineCut) ||
		(b_Temperature_Sensor1 <= Par_TemperatureSensorShort))
	{
		b_Temperature_SensorFault1 = On;
	}
	else
	{
		b_Temperature_SensorFault1 = Off;
	}

	if((b_Temperature_Sensor2 >= Par_TemperatureSensorLineCut) ||
		(b_Temperature_Sensor2 <= Par_TemperatureSensorShort))
	{
		b_Temperature_SensorFault2 = On;
	}
	else
	{
		b_Temperature_SensorFault2 = Off;
	}

	if((b_Temperature_Sensor3 >= Par_TemperatureSensorLineCut) ||
		(b_Temperature_Sensor3 <= Par_TemperatureSensorShort))
	{
		b_Temperature_SensorFault3 = On;
	}
	else
	{
		b_Temperature_SensorFault3 = Off;
	}
	
}

/******************************************************************************
 * Function name  : SwInput
 * Parameter    : u8 sw_num, u8 value
 * Return     : void
 * Description    : Input Switch Value Chattering Check
 * Revision   :   2018.03.22 Change SwInput Method
 ******************************************************************************/
FUNC(void, SWC_Input_CODE) SwInput(IN VAR(uint8, AUTOMATIC) sw_num, IN VAR(uint8, AUTOMATIC) value)
{
  sw_input *sw = &sw_array[sw_num];

  if( value==sw->old_value )  /* not changed */
  {
    sw->counter = 0;        /* clear counter */
    sw->change = 0;         /* no change mark */
  }
  else
  {
    if(value != sw->prev_value)
    {
      sw->change = 0;         /* change mark clear */
      sw->counter++;          /* chattering counter up */

    }
    else
    {
      sw->counter++;
    }
    sw->change = 0;           /* change mark clear */

    /* chattering counter reach to on time ? */
    if(value==Off)
    {
      if(sw->counter>=sw->off_time)
      {
        sw->counter = 0;      /* clear counter */
        sw->old_value = value;    /* backup value */
        sw->change = 1;       /* change mark */

        if( sw->active==(u8)0)    /* active level check */
        {
          sw->sw_status = 1U; /* active level ok */
        }
        else
        {
          sw->sw_status = 0U; /* active level */
        }
      }
    }
    else
    {
      if( sw->counter >= sw->on_time )
      {
        sw->counter = 0;      /* clear counter */
        sw->old_value = value;    /* backup value */
        sw->change = 1;       /* change mark */

        if(sw->active==(u8)0)     /* active level check */
        {
          sw->sw_status = 0U; /* active level ok */
        }
        else
        {
          sw->sw_status = value;  /* active level */
        }
      }
    }
    sw->prev_value = value;
  }
}


void Locking_FAN(void)
{
  u8 diag = 0u;
  static u8 diag_old = 0u;
  static u16 Cnt = 0u;

  if(GetX(kb_ChargingState) == On)
  {
    diag = (u8)FAN_DIAG_ReadDirect();

    if(diag == diag_old)
    {
      Cnt++;

      if(Cnt >= 100u)
      {
        SetX(kL_FAN_DIAG, On);
        Cnt = 0u;
      }
    }
    else
    {
      SetX(kL_FAN_DIAG, Off);
      Cnt = 0u;
      diag_old = diag;
    }
  }
  else
  {
    SetX(kL_FAN_DIAG, Off);
    Cnt = 0u;
  }
}

uint8 Get_VN7140AS_MULTI(void)
{
  uint8 ret = 0u;

  ret = VN7140AS_MULTI_ReadDirect();

  return ret;
}




void Initial_Input(void)
{
  uint8 i;

  for(i=0u; i<(uint8)kMaxLocalInput; i++)
  {
    sw_array[i] = sw_init[i];
  }

  b_SelecteCoil = 0u;
  b_VoltageState = 0u;
  b_CurrentCurr = 0u;

  b_Temperature_SensorFault1 = Off;
  b_Temperature_SensorFault2 = Off;
  b_Temperature_SensorFault3 = Off;

  b_Temperature_Sensor1 = COIL_TEMP_DEFAULT;
  b_Temperature_Sensor2 = COIL_TEMP_DEFAULT;
  b_Temperature_Sensor3 = COIL_TEMP_DEFAULT;

  SetX(kb_CurProfile, (uint8)kProfileID_Guest);               ClrEvt(kb_CurProfile);
  //SetQue(kb_DigitalKeyOption, (u8)kDigitalKeyEnable_None);  ClrQueChange(kb_DigitalKeyOption);
  SetX(kb_NFCSearchingOffComplete, Off);                      ClrEvt(kb_NFCSearchingOffComplete);

  SetX(kb_WPCStatus, (uint8)WPCStatus_Off);                   ClrEvt(kb_WPCStatus);
  SetX(kb_WPCPower, Off);                                     ClrEvt(kb_WPCPower);
  SetX(kb_LFState, (uint8)LF_OFF);                            ClrEvt(kb_LFState);

  SetX(kb_TemperatureFault, Off);                             ClrEvt(kb_TemperatureFault);
  SetX(kb_TempSensorFault, Off);                              ClrEvt(kb_TempSensorFault);
  SetX(kb_CurrentFault, Off);                                 ClrEvt(kb_CurrentFault);
  SetX(kb_FODFault, Off);                                     ClrEvt(kb_FODFault);
  SetX(kb_FANFault, Off);                                     ClrEvt(kb_FANFault);
  SetX(kb_CANError_BCAN, Off);                                ClrEvt(kb_CANError_BCAN);

  SetX(kb_DTCWPCInternalError, Off);                          ClrEvt(kb_DTCWPCInternalError);
  SetX(kb_DeviceState, (uint8)DeviceStates_Init);             ClrEvt(kb_DeviceState);
  //SetX(kb_TX_State, (uint8)TX_State_STARTUP);                 ClrEvt(kb_TX_State);
  SetX(kb_TX_Status, (uint8)TX_Status_OK);                    ClrEvt(kb_TX_Status);
  SetX(kb_TX_Fault_Reason, (uint8)TX_Status_OK);              ClrEvt(kb_TX_Fault_Reason);
  SetX(kb_WPCPhoneExist, Off);                                ClrEvt(kb_WPCPhoneExist);
  SetX(kb_WPCRunMode, (uint8)kRunMode_NONE);                  ClrEvt(kb_WPCRunMode);
  SetX(kb_ChargingState, Off);                                ClrEvt(kb_ChargingState);

  SetX(kb_AmberINDCmd, Off);                                  ClrEvt(kb_AmberINDCmd);
  SetX(kb_GreenINDCmd, Off);                                  ClrEvt(kb_GreenINDCmd);
  SetX(kb_LED_Duty, (uint8)Par_RheostatBrightLevel10);        ClrEvt(kb_LED_Duty);
  SetX(kb_WPCDayTimeLEDOut, Off);                             ClrEvt(kb_WPCDayTimeLEDOut);

  SetX(kb_CAN_Inactive, (uint8)CANInactive_None);             ClrEvt(kb_CAN_Inactive);
  SetX(kb_IGN_IN, Off);                                       ClrEvt(kb_IGN_IN);
  SetX(kb_Var_PreSyncAct, PreSyncAct_Off);					  ClrEvt(kb_Var_PreSyncAct);
}


void ReInitial_Input(void)      // For Wake Up
{
  uint8 i;

  for(i=0u; i<(uint8)kMaxLocalInput; i++)
  {
    sw_array[i] = sw_init[i];
  }

  b_SelecteCoil = 0u;
  b_VoltageState = 0u;
  b_CurrentCurr = 0u;

  b_Temperature_SensorFault1 = Off;
  b_Temperature_SensorFault2 = Off;
  b_Temperature_SensorFault3 = Off;

  b_Temperature_Sensor1 = COIL_TEMP_DEFAULT;
  b_Temperature_Sensor2 = COIL_TEMP_DEFAULT;
  b_Temperature_Sensor3 = COIL_TEMP_DEFAULT;


  //SetQue(kb_DigitalKeyOption, (u8)kDigitalKeyEnable_None);  ClrQueChange(kb_DigitalKeyOption);
  SetX(kb_NFCSearchingOffComplete, Off);          ClrEvt(kb_NFCSearchingOffComplete);

  SetX(kb_WPCStatus, (u8)WPCStatus_Off);          ClrEvt(kb_WPCStatus);
  SetX(kb_WPCPower, Off);                         ClrEvt(kb_WPCPower);
  SetX(kb_LFState, (u8)LF_OFF);                   ClrEvt(kb_LFState);

  SetX(kb_TemperatureFault, Off);                 ClrEvt(kb_TemperatureFault);
  SetX(kb_TempSensorFault, Off);                  ClrEvt(kb_TempSensorFault);
  SetX(kb_CurrentFault, Off);                     ClrEvt(kb_CurrentFault);
  SetX(kb_FODFault, Off);                         ClrEvt(kb_FODFault);
  SetX(kb_FANFault, Off);                         ClrEvt(kb_FANFault);
  SetX(kb_CANError_BCAN, Off);                    ClrEvt(kb_CANError_BCAN);

  SetX(kb_DTCWPCInternalError, Off);              ClrEvt(kb_DTCWPCInternalError);
  SetX(kb_DeviceState, (u8)DeviceStates_Init);    ClrEvt(kb_DeviceState);
  //SetX(kb_TX_State, (u8)TX_State_STARTUP);        ClrEvt(kb_TX_State);
  SetX(kb_TX_Status, (u8)TX_Status_OK);           ClrEvt(kb_TX_Status);
  SetX(kb_TX_Fault_Reason, (uint8)TX_Status_OK);  ClrEvt(kb_TX_Fault_Reason);
  SetX(kb_WPCPhoneExist, Off);                    ClrEvt(kb_WPCPhoneExist);
  SetX(kb_WPCRunMode, (u8)kRunMode_NONE);         ClrEvt(kb_WPCRunMode);
  SetX(kb_ChargingState, Off);                    ClrEvt(kb_ChargingState);

  SetX(kb_IGN_IN, Off);                           ClrEvt(kb_IGN_IN);
  SetX(kb_Var_PreSyncAct, PreSyncAct_Off);		  ClrEvt(kb_Var_PreSyncAct);
}

