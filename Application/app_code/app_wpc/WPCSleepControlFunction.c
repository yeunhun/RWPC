

/*******************************************************************************
  Include Headers
*******************************************************************************/
#include "WPCType.h"
#include "Define.h"
#include "WPCTimer.h"
#include "Data.h"
#include "WPCVehicleOption.h"
#include "WPCSleepControl.h"
#include "WPC_NFCIC.h"

#include "app_input_type.h"
#include "app_input.h"
#include "app_output_type.h"
#include "app_output.h"

#include "SlpWup.h"
#include "Rte_CDD_SLPWUP.h"
#include "Rte_BswM_Type.h"

#include "Slpwup_Callouts.h"
#include "Slpwup_Cfg.h"
#include "NvM.h"

#include "WPCCANControl.h"

#include "app_can_output_type.h"
#include "app_can_output.h"
#include "WPCI2CControl.h"
#include "WPCLogicControl.h"


extern void Slpwup_RequestSleep(void);
/********************************************************************************
* Global Variables
********************************************************************************/
uint8 u8_Sleep_Flag[MAX_SLEEP_FLAG];
extern uint32 Slpwup_GulSleepRequestProcessingCount;
extern uint32 Slpwup_GulNvMLowPowerAllowCount;

tTimer16 Timer_SleepWait = {Off, 0u};
tTimer16 Timer_SleepWaitVoltage = {Off, 0u};
extern uint8 bcan_wakeup_flag;
/********************************************************************************
* Modules
********************************************************************************/
void LowPower_Allow(uint8 lub_ID)
{
  u8_Sleep_Flag[lub_ID] = LP_OK;
}

void LowPower_Prevent(uint8 lub_ID)
{
  u8_Sleep_Flag[lub_ID] = LP_NO;
}

#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
extern uint8 Get_p9450_auto_reprog_on_off_status(void);
extern uint8 Get_p9450_auto_reprog_retry(void);
#endif
void Func_Enter_Sleep_Check_WPC(void)
{
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
  if( (GetX(kb_WPCPower) == Off) &&
      (GetX(kb_WPCStatus) == (u8)WPCStatus_Off) &&
      (GetOutput(kC_WPC_PhnLftWrngRWPCSta) == (u8)kWPCWarning_Off) &&
      (GetX(kb_IGN_IN) == Off) &&
      (GetOutput(kC_WPCDiagState) == Off) &&
      (Get_p9450_auto_reprog_on_off_status()==Off) &&
      (Get_p9450_auto_reprog_retry()==Off) )
#else
  if((GetX(kb_WPCPower) == Off) &&
     (GetX(kb_WPCStatus) == (u8)WPCStatus_Off) &&
     (GetOutput(kC_WPC_PhnLftWrngRWPCSta) == (u8)kWPCWarning_Off) &&
     (GetX(kb_IGN_IN) == Off) &&
     (GetOutput(kC_WPCDiagState) == Off))
#endif
  {
    LowPower_Allow(WPC_SLEEP_LP_FLAG);
  }
	else
	{
		LowPower_Prevent(WPC_SLEEP_LP_FLAG);
	}
}



void WPC_SleepMode_Control(void)
{
  UpTimer16(Timer_PowerOn);
  UpTimer16(Timer_SleepWait);


  if((Timer_PowerOn.run == On) &&
    (Timer_PowerOn.time >= Par_PowerOn_Wait_Time))
  {
    CancelTimer(Timer_PowerOn);
  }

  if((Timer_SleepWait.run == On) &&
    (Timer_SleepWait.time >= Par_Sleep_Wait_Time))
  {
    CancelTimer(Timer_SleepWait);
  }

  if((Timer_SleepWait.run == Off) &&
    (Timer_PowerOn.run == Off) &&
    (u8_Sleep_Flag[WPC_SLEEP_LP_FLAG] == LP_OK) &&
    ((Slpwup_GulSleepRequestProcessingCount == 0x00u) &&
    (Slpwup_GulNvMLowPowerAllowCount == 0x00u)))
      {
        Slpwup_RequestSleep();
      }
    else if(((u8_Sleep_Flag[WPC_SLEEP_LP_FLAG] != LP_OK) &&
	         (bcan_wakeup_flag == On) &&
		    (Slpwup_GulSleepRequestProcessingCount >= 1u)) ||
		    (IsChgEvt(kb_CAN_Inactive, (u8)CANInactive_Off)))
    {
      	Slpwup_GulSleepProcessingCount_Flag = 0u;
		Slpwup_GulSleepProcessState = SLPWUP_EARLY_WAKEUP_DETECTED;
		
	    Slpwup_modeRequestPort_ComMMode_FULL_COM();
    }
  else
  {
    /*  */
  }
}
//extern FUNC(void,AppMode_CODE) AppMode_Test(void);
extern void Set_No_COM_Req(void);
extern void Set_Full_COM_Req(void);
extern uint8 Slpwup_CheckPrecondition_First_FULL_COM(void);
extern uint8 Slpwup_CheckPrecondition_NO_COM(void);
volatile uint8 lucFirstFullCommPass_tmp = 0u;
volatile uint8 lucNoCommPass_tmp = 0u;
volatile uint8 slp_step_tmp = 0u;

volatile uint32 cnt_com_tmp = 0u;
volatile uint32 cnt_com_total_tmp = 0u;
void SleepModeProcessing(void)
{
  Func_Enter_Sleep_Check_WPC();
  WPC_SleepMode_Control();
}

void Set_Slp_Step(void);
void Set_Slp_Step(void)
{
  slp_step_tmp = 0;
}

