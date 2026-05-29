#include "WPCVehicleOption.h"
#include "WPCEepControl.h"
#include "Data.h"
#include "define.h"
#include "app_input_type.h"
#include "app_input.h"
#include "app_output_type.h"
#include "app_output.h"

static uint8 u8_init = Off;
u32 u32_init_eeprom = EEBlk_NONE;

extern tTimer8 tmr_BAT_stab_delay;



uint8 IsInit(void);
void ClearReset(void);


uint8 IsInit(void)
{
  return  u8_init;
}

void ClearReset(void)
{
  u8_init = On;
}

#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
void Set_P9450_Init_SWver_For_Factory(void);
#endif
u8 WPC_Initialize(void)
{
  static uint8 init_status = 0;
  static uint8 Check_VoltageStabilizing = 0;


  if((u8_init == Off) && (init_status == Off))
  {
    if(Get_EepromData_OPTION((u8)kOption_Status) != kMemory_Learnt)
    {
      /* Do initialize EEPROM data */
      Clear_EepromBlock_OPTION();
      Clear_EepromBlock_FUNCTION();
      Clear_EepromBlock_DTC();
      Clear_EepromBlock_FACTORY_SN();
      Clear_EepromBlock_FACTORY_MD();
      //Clear_EepromBlock_FACTORY_PN();
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
      Clear_EepromBlock_DUMMY();
#endif

      Set_EepromData_OPTION((u8)kOption_Status, kMemory_Learnt);

#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
      Set_P9450_Init_SWver_For_Factory();
#endif

      Set_EepromData_FUNCTION((u8)kFunc_WPCOneUSM, (u8)kWPCOnOff_On);
      Set_EepromData_FUNCTION((u8)kFunc_WPCTwoUSM, (u8)kWPCOnOff_On);
      Set_EepromData_FUNCTION((u8)kFunc_WPCUnknownUSM, (u8)kWPCOnOff_On);

	  
      SetX(kb_WPCSWOption, (u8)kWPCOnOff_On);
      SetOutput(kC_USM_CmdWPCSta, GetX(kb_WPCSWOption));

	  
      SetX(km_ProfileOneWPCUSM, (u8)kWPCOnOff_On);
      ClrEvt(km_ProfileOneWPCUSM);
      SetX(km_ProfileTwoWPCUSM, (u8)kWPCOnOff_On);
      ClrEvt(km_ProfileTwoWPCUSM);
      SetX(km_ProfileGuestWPCUSM, (u8)kWPCOnOff_On);
      ClrEvt(km_ProfileGuestWPCUSM);

	  
	  
    }
    else
    {
      /* EEPROM OK */
      SetX(kb_WPCSWOption, Get_EepromData_FUNCTION((u8)kFunc_WPCUnknownUSM));
      SetX(km_ProfileOneWPCUSM, Get_EepromData_FUNCTION((u8)kFunc_WPCOneUSM));
      ClrEvt(km_ProfileOneWPCUSM);
      SetX(km_ProfileTwoWPCUSM, Get_EepromData_FUNCTION((u8)kFunc_WPCTwoUSM));
      ClrEvt(km_ProfileTwoWPCUSM);
      SetX(km_ProfileGuestWPCUSM, Get_EepromData_FUNCTION((u8)kFunc_WPCUnknownUSM));
      ClrEvt(km_ProfileGuestWPCUSM);

      SetOutput(kC_USM_CmdWPCSta, GetX(kb_WPCSWOption));

	  
    }

    init_status = On;
  }

  if((u8_init == Off) && (init_status == On))
  {
    if((tmr_BAT_stab_delay.time >= T_BAT_stab_delayTime) &&
      (BAT_stab_finish_flg == On))
    {
      Check_VoltageStabilizing = On;
    }
    else
    {
      Check_VoltageStabilizing = Off;
    }
  }
  else
  {
    Check_VoltageStabilizing = u8_init;
  }

  return  Check_VoltageStabilizing;
}

/****************************************************
WPC Option
****************************************************/
#define HIGH_POWER
#define USE_IGN
//#define NFC_ENABLE

void WPC_Setting_Option(void)
{
	Set_ECU_Identifier();
  //SetX(kb_WPCSWOption, (u8)kWPCOnOff_On);
#if defined (HIGH_POWER)
  #if defined (NFC_ENABLE)
    SetX(kb_WPCOption, (u8)WPCOpt_MP_WPCNFC);
  #else
    SetX(kb_WPCOption, (u8)WPCOpt_MP_WPCOnly);
  #endif

  #if defined (USE_IGN)
    SetX(kb_IGNUseOption, On);
  #else
    SetX(kb_IGNUseOption, Off);
  #endif

  #if defined (USE_INIT_LED)
    SetX(kb_InitialLEDOption, On);
  #else
    SetX(kb_InitialLEDOption, Off);
  #endif

  #if defined (USE_WARNING)
    SetX(kb_WarningOption, On);
  #else
    SetX(kb_WarningOption, Off);
  #endif
#else
  SetQue(kb_WPCOption, (u8)WPCOpt_LP_WPC);
#endif
}




void Init_Eeprom_OK(void)
{
  u32_init_eeprom = EEBlk_INIT_OK;
}

uint8 get_init_nvm_test(void)
{
  return u32_init_eeprom;
}

