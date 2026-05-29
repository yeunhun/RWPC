#include "WPCVehicleOption.h"
#include "WPCType.h"
#include "WPCTimer.h"
#include "define.h"
#include "Data.h"

#include "app_input_type.h"
#include "app_input.h"
#include "app_output_type.h"
#include "app_output.h"

#include "WPCOutput.h"
#include "WPCPWMControl.h"
#include "WPCLogicControl.h"
#include "Rte_SWC_Output.h"


static tTimer16 Timer_IOCBI_AmberLED = {Off, 0u};
static tTimer16 Timer_IOCBI_GreenLED = {Off, 0u};
static tTimer16 Timer_AmberLED_On = {Off, 0u};
static tTimer16 Timer_GreenLED_On = {Off, 0u};
static tTimer16 Timer_FAN_On = {Off, 0u};

extern uint8 b_UpdateFlashCmd;

#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
extern uint8 get_p9450_auto_reprog_ready(void);
#endif
void LEDBlk_P9261_FlashUpdate(void)
{
  static u8 led_toggle = 0u;

#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
  //if( (b_UpdateFlashCmd == On) && (get_p9450_auto_reprog_ready() == Off) )
  if(b_UpdateFlashCmd == On)
#else
  if(b_UpdateFlashCmd == On)
#endif
  {
    if(GetX(kb_WPCRunMode) != (u8)kRunMode_REPROGRAMMING)
    {
      SetX(kb_WPCRunMode, (u8)kRunMode_REPROGRAMMING);

      Pwm_IND_Stop(Amber);
      Pwm_IND_Stop(Green1);
      Pwm_IND_Stop(Green2);
      Pwm_IND_Stop(Green3);

      Pwm_IND_Start(Green1, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel057));
      Pwm_IND_Start(Green2, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel057));
      Pwm_IND_Start(Green3, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel057));
    }
    else
    {
      led_toggle++;

      if(led_toggle == 20u)
      {
        Pwm_IND_Stop(Green1);
        Pwm_IND_Stop(Green2);
        Pwm_IND_Stop(Green3);
        Pwm_IND_Start(Amber, GetDutyCycle_AutoBright(Par_AmberAutoBrightLevel057));
      }
      else if(led_toggle == 40u)
      {
        led_toggle = 0u;
        Pwm_IND_Stop(Amber);
        Pwm_IND_Start(Green1, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel057));
        Pwm_IND_Start(Green2, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel057));
      	Pwm_IND_Start(Green3, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel057));
      }
      else
      {
        /* Misra */
      }
    }
  }
}

void Output_Processing(void)
{
	static u8 fd_wpc_old[7u] = {0u, 0u, 0u, 0u, 0u, 0u, 0u};

	LEDBlk_P9261_FlashUpdate();

/* LED Forced Control_HKMC */
	/* Amber LED */
	if(tbl_ForcedDrive_WPC[0u].status == Off)
	{
		if((fd_wpc_old[0u] == On) &&
			(GetX(kb_AmberINDCmd) == Off))
		{
			Pwm_IND_Stop(Amber);
			SetOutput(kL_Amber_OUT, Off);
		}
	}
	else
	{
		AmberLED_Output_IOCBI();
		if((tbl_ForcedDrive_WPC[0u].status == Off) &&
			(GetX(kb_AmberINDCmd) == Off))
		{
			Pwm_IND_Stop(Amber);
		}
	}
	fd_wpc_old[0u] = tbl_ForcedDrive_WPC[0u].status;
	
	/* Green LED */
	if(tbl_ForcedDrive_WPC[1u].status == Off)
	{
		if((fd_wpc_old[1u] == On) &&
			(GetX(kb_GreenINDCmd) == Off))
		{
			Pwm_IND_Stop(Green1);
			Pwm_IND_Stop(Green2);
			Pwm_IND_Stop(Green3);
			SetOutput(kL_Green_OUT, Off);
		}
	}
	else
	{
		GreenLED_Output_IOCBI();
		if((tbl_ForcedDrive_WPC[1u].status == Off) &&
			(GetX(kb_GreenINDCmd) == Off))
		{
			Pwm_IND_Stop(Green1);
			Pwm_IND_Stop(Green2);
			Pwm_IND_Stop(Green3);
		}
	}
	fd_wpc_old[1u] = tbl_ForcedDrive_WPC[1u].status;
	
	/* FAN */
	if(tbl_ForcedDrive_WPC[5u].status == Off)
	{
		if((fd_wpc_old[5u] == On) &&
			(GetX(kb_FAN_PWM) == Par_NoFAN))
		{
			Pwm_FAN_Stop();
			IPS_Control(Off);
			SetOutput(kL_Fan_OUT, Off);
		}
	}
	else
	{
		FAN_Output_IOCBI();
		if((tbl_ForcedDrive_WPC[5u].status == Off) &&
			(GetX(kb_FAN_PWM) == Par_NoFAN))
		{
			Pwm_FAN_Stop();
			IPS_Control(Off);
		}
	}
	fd_wpc_old[5u] = tbl_ForcedDrive_WPC[5u].status;
	
/* LED/FAN Forced Control_SeoYon */
	/* Amber LED Forced Duty */
	if(tbl_ForcedDrive_WPC[2u].status == Off)
	{
		if((fd_wpc_old[2u] == On) &&
			(GetX(kb_AmberINDCmd) == Off))
		{
			Pwm_IND_Stop(Amber);
			SetOutput(kL_Amber_OUT, Off);
		}
	}
	else
	{
		AmberLED_Output_ChangeDuty();
		if((tbl_ForcedDrive_WPC[2u].status == Off) &&
			(GetX(kb_AmberINDCmd) == Off))
		{
			Pwm_IND_Stop(Amber);
		}
	}
	fd_wpc_old[2u] = tbl_ForcedDrive_WPC[2u].status;
	
	/* Green LED Forced Duty */
	if(tbl_ForcedDrive_WPC[3u].status == Off)
	{
		if((fd_wpc_old[3u] == On) &&
			(GetX(kb_GreenINDCmd) == Off))
		{
			Pwm_IND_Stop(Green1);
			Pwm_IND_Stop(Green2);
			Pwm_IND_Stop(Green3);
			SetOutput(kL_Green_OUT, Off);
		}
	}
	else
	{
		GreenLED_Output_ChangeDuty();
		if((tbl_ForcedDrive_WPC[3u].status == Off) &&
			(GetX(kb_GreenINDCmd) == Off))
		{
			Pwm_IND_Stop(Green1);
			Pwm_IND_Stop(Green2);
			Pwm_IND_Stop(Green3);
		}
	}
	fd_wpc_old[3u] = tbl_ForcedDrive_WPC[3u].status;
	
	/* FAN Forced Duty */
	if(tbl_ForcedDrive_WPC[4u].status == Off)
	{
		if((fd_wpc_old[4u] == On) &&
			(GetX(kb_FAN_PWM) == Par_NoFAN))
		{
			Pwm_FAN_Stop();
			IPS_Control(Off);
			SetOutput(kL_Fan_OUT, Off);
		}
	}
	else
	{
		FAN_Output_ChangeDuty();
		if((tbl_ForcedDrive_WPC[5u].status == Off) &&
			(GetX(kb_FAN_PWM) == Par_NoFAN))
		{
			Pwm_FAN_Stop();
			IPS_Control(Off);
		}
	}
	fd_wpc_old[4u] = tbl_ForcedDrive_WPC[4u].status;
	
/* CAN */
	if(GetX(kb_CAN_Inactive) == (u8)CANInactive_Off)
	{
		SetOutput(kC_RWPC_SWVerMajor1, ECU_Read.SWVer[0]);
		SetOutput(kC_RWPCSWVerMinor1,  ECU_Read.SWVer[1]);
		SetOutput(kC_RWPCSWVerMinor2,  ECU_Read.SWVer[2]);
		(void)Rte_Write_BCAN_RWPC_01_200ms_RWPC_SWVerMajor1(GetX(kC_RWPC_SWVerMajor1));
		(void)Rte_Write_BCAN_RWPC_01_200ms_RWPC_SWVerMinor1(GetX(kC_RWPCSWVerMinor1));
		(void)Rte_Write_BCAN_RWPC_01_200ms_RWPC_SWVerMinor2(GetX(kC_RWPCSWVerMinor2));
		(void)Rte_Write_BCAN_RWPC_01_200ms_WPC_PhnLftWrngRWPCSta(GetX(kC_WPC_PhnLftWrngRWPCSta));
	}
}

void AmberLED_Output_IOCBI(void)
{
	static e_ActionState e_AmberLED_IOCBI = kNoAction;
	static u16 repeat_cnt = 0u;
	u8 fd_idx = 0u; /* Amber LED Index */

	UpTimer16(Timer_IOCBI_AmberLED);
	
	if((tbl_ForcedDrive_WPC[fd_idx].initiated == Off) &&
		(GetOutput_IOCBI(tbl_ForcedDrive_WPC[fd_idx].index) == Off))
	{
		//Pwm_IND_Start(Amber, GetDutyCycle(Par_RheostatBrightLevel21));
		Pwm_IND_Start(Amber, GetDutyCycle_AutoBright(Par_AmberAutoBrightLevel091));	// PWM Start Function

		SetOutput(kL_Amber_OUT, On);

		repeat_cnt = 0u;

		tbl_ForcedDrive_WPC[fd_idx].initiated = On;
	
		StartTimer(Timer_IOCBI_AmberLED);
		
		e_AmberLED_IOCBI = kActiveAction;
	}
	
	switch(e_AmberLED_IOCBI)
	{
	case kNoAction:
		if(Timer_IOCBI_AmberLED.time > tbl_ForcedDrive_WPC[fd_idx].off_time)
		{
			repeat_cnt++;
			
			if((repeat_cnt >= tbl_ForcedDrive_WPC[fd_idx].repeat_cnt) ||
				(GetOutput_IOCBI(tbl_ForcedDrive_WPC[fd_idx].index) == On))
			{
				CancelTimer(Timer_IOCBI_AmberLED);
				tbl_ForcedDrive_WPC[fd_idx].status = Off;
				//IOCBI_Status = Off;
				repeat_cnt = 0u;
			}
			else
			{
				//Pwm_IND_Start(Amber, GetDutyCycle(Par_RheostatBrightLevel21));
				Pwm_IND_Start(Amber, GetDutyCycle_AutoBright(Par_AmberAutoBrightLevel091));	// PWM Start Function
				SetOutput(kL_Amber_OUT, On);
				StartTimer(Timer_IOCBI_AmberLED);
				e_AmberLED_IOCBI = kActiveAction;
			}
		}
		break;
	case kActiveAction:
		if(Timer_IOCBI_AmberLED.time > tbl_ForcedDrive_WPC[fd_idx].on_time)
		{
			Pwm_IND_Stop(Amber);		//PWM Stop Function
			SetOutput(kL_Amber_OUT, Off);
			StartTimer(Timer_IOCBI_AmberLED);
			e_AmberLED_IOCBI = kNoAction;
		}
		else if(GetX(kb_AmberINDCmd) == On)
		{
			e_AmberLED_IOCBI = kNoAction;
		}
		else
		{
			/* Misra */
		}
		break;
	default:
		/* MISRA-C */
		break;
	}
}

void GreenLED_Output_IOCBI(void)
{
	static e_ActionState e_GreenLED_IOCBI = kNoAction;
	static u16 repeat_cnt = 0u;
	u8 fd_idx = 1u; /* Green LED Index */

	UpTimer16(Timer_IOCBI_GreenLED);
	
	if((tbl_ForcedDrive_WPC[fd_idx].initiated == Off) &&
		(GetOutput_IOCBI(tbl_ForcedDrive_WPC[fd_idx].index) == Off))
	{
		//Pwm_IND_Start(Green1, GetDutyCycle(Par_RheostatBrightLevel21));
		Pwm_IND_Start(Green1, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel091));	// PWM Start Function
		Pwm_IND_Start(Green2, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel091));	// PWM Start Function
		Pwm_IND_Start(Green3, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel091));	// PWM Start Function

		SetOutput(kL_Green_OUT, On);

		repeat_cnt = 0u;

		tbl_ForcedDrive_WPC[fd_idx].initiated = On;
	
		StartTimer(Timer_IOCBI_GreenLED);
		
		e_GreenLED_IOCBI = kActiveAction;
	}
	
	switch(e_GreenLED_IOCBI)
	{
	case kNoAction:
		if(Timer_IOCBI_GreenLED.time > tbl_ForcedDrive_WPC[fd_idx].off_time)
		{
			repeat_cnt++;
			
			if((repeat_cnt >= tbl_ForcedDrive_WPC[fd_idx].repeat_cnt) ||
				(GetOutput_IOCBI(tbl_ForcedDrive_WPC[fd_idx].index) == On))
			{
				CancelTimer(Timer_IOCBI_GreenLED);
				tbl_ForcedDrive_WPC[fd_idx].status = Off;
				//IOCBI_Status = Off;
				repeat_cnt = 0u;
			}
			else
			{
				//Pwm_IND_Start(Green1, GetDutyCycle(Par_RheostatBrightLevel21));
				Pwm_IND_Start(Green1, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel091));	// PWM Start Function
				Pwm_IND_Start(Green2, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel091));	// PWM Start Function
				Pwm_IND_Start(Green3, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel091));	// PWM Start Function

				SetOutput(kL_Green_OUT, On);
				StartTimer(Timer_IOCBI_GreenLED);
				e_GreenLED_IOCBI = kActiveAction;
			}
		}
		break;
	case kActiveAction:
		if(Timer_IOCBI_GreenLED.time > tbl_ForcedDrive_WPC[fd_idx].on_time)
		{
			Pwm_IND_Stop(Green1);
			Pwm_IND_Stop(Green2);
			Pwm_IND_Stop(Green3);
			
			SetOutput(kL_Green_OUT, Off);
			StartTimer(Timer_IOCBI_GreenLED);
			e_GreenLED_IOCBI = kNoAction;
		}
		else if(GetX(kb_GreenINDCmd) == On)
		{
			e_GreenLED_IOCBI = kNoAction;
		}
		else
		{
			/* Misra */
		}
		break;
	default:
		/* MISRA-C */
		break;
	}
}

void FAN_Output_IOCBI(void)
{
	u8 fd_idx = 5u; /* FAN Index */

	UpTimer16(Timer_FAN_On);

	if((tbl_ForcedDrive_WPC[fd_idx].initiated == Off) &&
		(GetOutput_IOCBI(tbl_ForcedDrive_WPC[fd_idx].index) == Off))
	{
		IPS_Control(On);
		Pwm_FAN_Start(Par_FANValueLow);	/*20%*/
		Change_PWM_FAN_DutyCycle(GetDutyCycle(Par_FANValueMedium));	/*50%*/

		SetOutput(kL_Fan_OUT, On);

		tbl_ForcedDrive_WPC[fd_idx].initiated = On;
	
		StartTimer(Timer_FAN_On);
	}
	else
	{
		if(Timer_FAN_On.time > tbl_ForcedDrive_WPC[fd_idx].on_time)
		{
			Pwm_FAN_Stop();
			IPS_Control(Off);
			SetOutput(kL_Fan_OUT, Off);

			CancelTimer(Timer_FAN_On);
			
			tbl_ForcedDrive_WPC[fd_idx].status = Off;
		}
		else if(GetX(kb_FAN_PWM) > Par_NoFAN)
		{
			CancelTimer(Timer_FAN_On);
			
			tbl_ForcedDrive_WPC[fd_idx].status = Off;
		}
		else
		{
			/* MISRA-C */
		}
	}
}

void AmberLED_Output_ChangeDuty(void)
{
	u8 fd_idx = 2u; /* Amber LED Index */

	UpTimer16(Timer_AmberLED_On);

	if((tbl_ForcedDrive_WPC[fd_idx].initiated == Off) &&
		(GetOutput_IOCBI(tbl_ForcedDrive_WPC[fd_idx].index) == Off))
	{
		//Pwm_IND_Start(Amber, GetDutyCycle(tbl_ForcedDrive_WPC[fd_idx].repeat_cnt));
		Pwm_IND_Start(Amber, GetDutyCycle_AutoBright(tbl_ForcedDrive_WPC[fd_idx].repeat_cnt));

		SetOutput(kL_Amber_OUT, On);

		tbl_ForcedDrive_WPC[fd_idx].initiated = On;
		
		StartTimer(Timer_AmberLED_On);
	}
	else
	{
		if(Timer_AmberLED_On.time > tbl_ForcedDrive_WPC[fd_idx].on_time)
		{
			Pwm_IND_Stop(Amber);
			SetOutput(kL_Amber_OUT, Off);
			CancelTimer(Timer_AmberLED_On);
			tbl_ForcedDrive_WPC[fd_idx].status = Off;
			//IOCBI_Status = Off;
		}
		else if(GetX(kb_AmberINDCmd) == On)
		{
			CancelTimer(Timer_AmberLED_On);
			tbl_ForcedDrive_WPC[fd_idx].status = Off;
			//IOCBI_Status = Off;
		}
		else
		{
			/* Misra */
		}
	}
}

void GreenLED_Output_ChangeDuty(void)
{
	u8 fd_idx = 3u; /* Green LED Index */

	UpTimer16(Timer_GreenLED_On);

	if((tbl_ForcedDrive_WPC[fd_idx].initiated == Off) &&
		(GetOutput_IOCBI(tbl_ForcedDrive_WPC[fd_idx].index) == Off))
	{
		//Pwm_IND_Start(Green1, GetDutyCycle(tbl_ForcedDrive_WPC[fd_idx].repeat_cnt));
		Pwm_IND_Start(Green1, GetDutyCycle_AutoBright(tbl_ForcedDrive_WPC[fd_idx].repeat_cnt));
		Pwm_IND_Start(Green2, GetDutyCycle_AutoBright(tbl_ForcedDrive_WPC[fd_idx].repeat_cnt));
		Pwm_IND_Start(Green3, GetDutyCycle_AutoBright(tbl_ForcedDrive_WPC[fd_idx].repeat_cnt));

		SetOutput(kL_Green_OUT, On);

		tbl_ForcedDrive_WPC[fd_idx].initiated = On;
		
		StartTimer(Timer_GreenLED_On);
	}
	else
	{
		if(Timer_GreenLED_On.time > tbl_ForcedDrive_WPC[fd_idx].on_time)
		{
			Pwm_IND_Stop(Green1);
			Pwm_IND_Stop(Green2);
			Pwm_IND_Stop(Green3);
			SetOutput(kL_Green_OUT, Off);
			CancelTimer(Timer_GreenLED_On);
			tbl_ForcedDrive_WPC[fd_idx].status = Off;
			//IOCBI_Status = Off;
		}
		else if(GetX(kb_GreenINDCmd) == On)
		{
			CancelTimer(Timer_GreenLED_On);
			tbl_ForcedDrive_WPC[fd_idx].status = Off;
			//IOCBI_Status = Off;
		}
		else
		{
			/* Misra */
		}
	}
}

void FAN_Output_ChangeDuty(void)
{
	u8 fd_idx = 4u; /* Green FAN Index */

	UpTimer16(Timer_FAN_On);

	if((tbl_ForcedDrive_WPC[fd_idx].initiated == Off) &&
		(GetOutput_IOCBI(tbl_ForcedDrive_WPC[fd_idx].index) == Off))
	{
		IPS_Control(On);
		Pwm_FAN_Start(GetDutyCycle(tbl_ForcedDrive_WPC[fd_idx].repeat_cnt));
		
		SetOutput(kL_Fan_OUT, On);

		tbl_ForcedDrive_WPC[fd_idx].initiated = On;
		
		StartTimer(Timer_FAN_On);
	}
	else
	{
		if(Timer_FAN_On.time > tbl_ForcedDrive_WPC[fd_idx].on_time)
		{
			Pwm_FAN_Stop();
			IPS_Control(Off);
			SetOutput(kL_Fan_OUT, Off);
			
			CancelTimer(Timer_FAN_On);
			
			tbl_ForcedDrive_WPC[fd_idx].status = Off;
		}
		else if(GetX(kb_FAN_PWM) > Par_NoFAN)
		{
			CancelTimer(Timer_FAN_On);
			
			tbl_ForcedDrive_WPC[fd_idx].status = Off;
		}
		else
		{
			/* MISRA-C */
		}
	}
}

