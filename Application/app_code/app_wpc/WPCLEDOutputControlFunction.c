/****************************************************************************************
* Project         : WPC                                 *
* File Name       :                                   *
* Compiler        : IAR                                 *
* Author          : Limjo Hong                                            *
* Created at      : 2018-05-25                                                      *
* Code Editor     : Source Insight                            *
* Revision        : 0.1                                 *
* Copyright       : (c) Copyright Seoyon Electronics Co.Ltd. All Rights Reserved    *
* Description     :                                   *
****************************************************************************************/


/*******************************************************************************
* Include Headers                                                              *
*******************************************************************************/
#include "WPCVehicleOption.h"
#include "WPCType.h"
#include "Define.h"
#include "WPCTimer.h"
#include "Data.h"
#include "Rte_SWC_Input.h"

#include "app_can_input_type.h"
#include "app_can_input.h"
#include "app_input_type.h"
#include "app_input.h"
#include "app_output_type.h"
#include "app_output.h"

#include "WPCLogicControl.h"
#include "Superstate_api.h"

#include "WPCPWMControl.h"

/*******************************************************************************
* Define Functions                                                             *
*******************************************************************************/
void IND_OptionCheck(void);
void GreenLEDOutputControlforRheoStat(void);
void AmberLEDOutputControlforRheoStat(void);
void GreenLEDOutputControlforNoRheoStat(void);
void AmberLEDOutputControlforNoRheoStat(void);
void GreenLEDOutputControlforAutoBright(void);
void AmberLEDOutputControlforAutoBright(void);
void WPCLEDOutputControl(void);
/*******************************************************************************
* Define Constant and Macro                                                    *
*******************************************************************************/


/*******************************************************************************
* Declare  Variables                                                           *
*******************************************************************************/


/*******************************************************************************
* Define Functions                                                             *
*******************************************************************************/


/*******************************************************************************
* Functions                                                                    *
*******************************************************************************/
void IND_OptionCheck(void)
{
#if defined (USE_DETENTOUT)

	if(GetX(kC_CLU_DtntOutSta) == On)
	{
		SetX(kb_WPCDayTimeLEDOut, On);			/* Day = On, Night = Off */
	}
	else
	{
		SetX(kb_WPCDayTimeLEDOut, Off);
	}
#endif
}
/************************************************************************************************/
/****         Function: GreenLEDOutputControlforRheoStat										*/
/****         Content: Figure 35 Green LED Output Control Function for RheoStat State Chart		*/
/****         Called By: 10ms TASK																*/
/****         argument: void																	*/
/****         return value: void																*/
/****		  Revision: 2018.05.25 Applied 14th													*/
/************************************************************************************************/
#if defined (USE_AUTOBRIGHT)	/* SCR-210706-003 Auto Bright */
void GreenLEDOutputControlforAutoBright(void)
{
	if(GetX(kb_GreenINDCmd) == On)
	{
		if(GetX(kb_WPCDayTimeLEDOut) == On)		/* Day = On, Night = Off */
		{
			if(IsChgEvt(kb_GreenINDCmd, On))
			{
				Pwm_IND_Start(Green1, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel091));	// PWM Start Function
				Pwm_IND_Start(Green2, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel091));	// PWM Start Function
				Pwm_IND_Start(Green3, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel091));	// PWM Start Function
				ClrEvt(kb_GreenINDCmd);
			}
			else if(IsChgEvt(kb_WPCDayTimeLEDOut, On))		// 20190122
			{
				Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel091), Green1);
				Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel091), Green2);
				Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel091), Green3);
			}
			else
			{
				/* Misra Coding Rule */
			}
		}
		else
		{
			if(IsChgEvt(kb_GreenINDCmd, On))
			{
				Pwm_IND_Start(Green1, GetDutyCycle_AutoBright(GetX(kb_GreenLED_Duty_AutoBright)));		// PWM Start Function
				Pwm_IND_Start(Green2, GetDutyCycle_AutoBright(GetX(kb_GreenLED_Duty_AutoBright)));		// PWM Start Function
				Pwm_IND_Start(Green3, GetDutyCycle_AutoBright(GetX(kb_GreenLED_Duty_AutoBright)));		// PWM Start Function
				ClrEvt(kb_GreenINDCmd);
			}
			else if(IsDiffEvt(kb_GreenLED_Duty_AutoBright) ||
					IsChgEvt(kb_WPCDayTimeLEDOut, Off))		// 20190122
			{
				Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(GetX(kb_GreenLED_Duty_AutoBright)), Green1);
				Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(GetX(kb_GreenLED_Duty_AutoBright)), Green2);
				Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(GetX(kb_GreenLED_Duty_AutoBright)), Green3);
			}
			else
			{
				/* Misra Coding Rule */
			}
		}
		
		SetOutput(kL_Green_OUT, On);
	}
	else
	{
		if(IsChgEvt(kb_GreenINDCmd, Off))		// 20180827 : LED On -> Off �� 1ȸ�� ��� �ϵ��� ���� �߰�
		{
			Pwm_IND_Stop(Green1);		//PWM Stop Function
			Pwm_IND_Stop(Green2);		//PWM Stop Function
			Pwm_IND_Stop(Green3);		//PWM Stop Function
			SetOutput(kL_Green_OUT, Off);
			ClrEvt(kb_GreenINDCmd);
		}
	}
}
#else
void GreenLEDOutputControlforRheoStat(void)
{
	if(GetX(kb_GreenINDCmd) == On)
	{
		if(GetX(kb_WPCDayTimeLEDOut) == On)		/* Day = On, Night = Off */
		{
			if(IsChgEvt(kb_GreenINDCmd, On))
			{
				Pwm_IND_Start(Green1, GetDutyCycle(Par_RheostatBrightLevel21));	// PWM Start Function
				Pwm_IND_Start(Green2, GetDutyCycle(Par_RheostatBrightLevel21));	// PWM Start Function
				Pwm_IND_Start(Green3, GetDutyCycle(Par_RheostatBrightLevel21));	// PWM Start Function
				ClrEvt(kb_GreenINDCmd);
			}
			else if(IsChgEvt(kb_WPCDayTimeLEDOut, On))		// 20190122 : When Rheostate event occurs in IND On state
			{
				Change_PWM_IND_DutyCycle(GetDutyCycle(Par_RheostatBrightLevel21), Green1);
				Change_PWM_IND_DutyCycle(GetDutyCycle(Par_RheostatBrightLevel21), Green2);
				Change_PWM_IND_DutyCycle(GetDutyCycle(Par_RheostatBrightLevel21), Green3);
			}
			else
			{
				/* Misra Coding Rule */
			}
		}
		else
		{
			if(IsChgEvt(kb_GreenINDCmd, On))	//When IND event occurs in Rheostate Off state
			{
				Pwm_IND_Start(Green1, GetDutyCycle(GetX(kb_LED_Duty)));		// PWM Start Function
				Pwm_IND_Start(Green2, GetDutyCycle(GetX(kb_LED_Duty)));		// PWM Start Function
				Pwm_IND_Start(Green3, GetDutyCycle(GetX(kb_LED_Duty)));		// PWM Start Function
				ClrEvt(kb_GreenINDCmd);
			}
			else if(IsDiffEvt(kb_LED_Duty) ||
					IsChgEvt(kb_WPCDayTimeLEDOut, Off))		// 20190122
			{
				Change_PWM_IND_DutyCycle(GetDutyCycle(GetX(kb_LED_Duty)), Green1);
			}
			else
			{
				/* Misra Coding Rule */
			}
		}
		
		SetX(kL_Green_OUT, On);
	}
	else
	{
		if(IsChgEvt(kb_GreenINDCmd, Off))		// 20180827 : LED On -> Off �� 1ȸ�� ��� �ϵ��� ���� �߰�
		{
			Pwm_IND_Stop(Green1);		//PWM Stop Function
			Pwm_IND_Stop(Green2);		//PWM Stop Function
			Pwm_IND_Stop(Green3);		//PWM Stop Function
			SetX(kL_Green_OUT, Off);
			ClrEvt(kb_GreenINDCmd);
		}
	}
}
#endif
/************************************************************************************************/
/****         Function: GreenLEDOutputControlforRheoStat										*/
/****         Content: Figure 36 Amber LED Output Control Function for RheoStat State Chart		*/
/****         Called By: 10ms TASK																*/
/****         argument: void																	*/
/****         return value: void																*/
/****		  Revision: 2018.05.25 Applied 14th													*/
/************************************************************************************************/
#if defined (USE_AUTOBRIGHT)	/* SCR-210706-003 Auto Bright */
void AmberLEDOutputControlforAutoBright(void)
{
	if(GetX(kb_AmberINDCmd) == On)
	{
		Pwm_IND_Stop(Green1);		//PWM Stop Function
		Pwm_IND_Stop(Green2);
		Pwm_IND_Stop(Green3);
		
		if(GetX(kb_WPCDayTimeLEDOut) == On)		/* Day = On, Night = Off */
		{
			if(IsChgEvt(kb_AmberINDCmd, On))
			{
				Pwm_IND_Start(Amber, GetDutyCycle_AutoBright(Par_AmberAutoBrightLevel091));	// PWM Start Function
				ClrEvt(kb_AmberINDCmd);
			}
			else if(IsChgEvt(kb_WPCDayTimeLEDOut, On))		// 20190122
			{
				Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(Par_AmberAutoBrightLevel091), Amber);
			}
			else
			{
				/* Misra Coding Rule */
			}
		}
		else
		{
			if(IsChgEvt(kb_AmberINDCmd, On))
			{
				Pwm_IND_Start(Amber, GetDutyCycle_AutoBright(GetX(kb_AmberLED_Duty_AutoBright)));		// PWM Start Function
				ClrEvt(kb_AmberINDCmd);
			}
			else if(IsDiffEvt(kb_AmberLED_Duty_AutoBright) ||
					IsChgEvt(kb_WPCDayTimeLEDOut, Off))		// 20190122
			{
				Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(GetX(kb_AmberLED_Duty_AutoBright)), Amber);
			}
			else
			{
				/* Misra Coding Rule */
			}
		}
		
		SetOutput(kL_Amber_OUT, On);
	}
	else if((GetX(kb_AmberINDCmd) == Off) && (b_BlinkState == (u8)Blink_State_Complete))	/* When changing from type2 to type1 in an error state */  
	{
		Pwm_IND_Stop(Amber);		//PWM Stop Function
	}
	else
	{
		if(IsChgEvt(kb_AmberINDCmd, Off))		// 20180827 : LED On -> Off �� 1ȸ�� ��� �ϵ��� ���� �߰�
		{
			Pwm_IND_Stop(Amber);		//PWM Stop Function
			SetOutput(kL_Amber_OUT, Off);
			ClrEvt(kb_AmberINDCmd);
		}
	}
}
#else
void AmberLEDOutputControlforRheoStat(void)
{
	if(GetX(kb_AmberINDCmd) == On)
	{
		if(GetX(kb_WPCDayTimeLEDOut) == On)		/* Day = On, Night = Off */
		{
			if(IsChgEvt(kb_AmberINDCmd, On))
			{
				Pwm_IND_Start(Amber, GetDutyCycle(Par_RheostatBrightLevel21));	// PWM Start Function
				ClrEvt(kb_AmberINDCmd);
			}
			else if(IsChgEvt(kb_WPCDayTimeLEDOut, On))		// 20190122
			{
				Change_PWM_IND_DutyCycle(GetDutyCycle(Par_RheostatBrightLevel21), Amber);
			}
			else
			{
				/* Misra Coding Rule */
			}
		}
		else
		{
			if(IsChgEvt(kb_AmberINDCmd, On))
			{
				Pwm_IND_Start(Amber, GetDutyCycle(GetX(kb_LED_Duty)));		// PWM Start Function
				ClrEvt(kb_AmberINDCmd);
			}
			else if(IsDiffEvt(kb_LED_Duty) ||
					IsChgEvt(kb_WPCDayTimeLEDOut, Off))		// 20190122
			{
				Change_PWM_IND_DutyCycle(GetDutyCycle(GetX(kb_LED_Duty)), Amber);
			}
			else
			{
				/* Misra Coding Rule */
			}
		}
		
		SetX(kL_Amber_OUT, On);
	}
	else
	{
		if(IsChgEvt(kb_AmberINDCmd, Off))		// 20180827 : LED On -> Off �� 1ȸ�� ��� �ϵ��� ���� �߰�
		{
			Pwm_IND_Stop(Amber);		//PWM Stop Function
			SetX(kL_Amber_OUT, Off);
			ClrEvt(kb_AmberINDCmd);
		}
	}
}
#endif
/************************************************************************************************/
/****         Function: GreenLEDOutputControlforRheoStat										*/
/****         Content: Figure 35 Green LED Output Control Function for No-RheoStat State Chart	*/
/****         Called By: 10ms TASK																*/
/****         argument: void																	*/
/****         return value: void																*/
/****		  Revision: 2018.05.25 Applied 14th													*/
/************************************************************************************************/
void GreenLEDOutputControlforNoRheoStat(void)
{
	if(GetX(kb_GreenINDCmd) == On)
	{
		if(GetX(kb_WPCDayTimeLEDOut) == Off)		/* Day = On, Night = Off */
		{
			if(IsChgEvt(kb_GreenINDCmd, On))
			{
				Pwm_IND_Start(Green1, GetDutyCycle(Par_BrightNight));	// PWM Start Function
				Pwm_IND_Start(Green2, GetDutyCycle(Par_BrightNight));	// PWM Start Function
				Pwm_IND_Start(Green3, GetDutyCycle(Par_BrightNight));	// PWM Start Function
				ClrEvt(kb_GreenINDCmd);
			}
			else if(IsChgEvt(kb_WPCDayTimeLEDOut, Off))		// 20190122
			{
				Change_PWM_IND_DutyCycle(GetDutyCycle(Par_BrightNight), Green1);
				Change_PWM_IND_DutyCycle(GetDutyCycle(Par_BrightNight), Green2);
				Change_PWM_IND_DutyCycle(GetDutyCycle(Par_BrightNight), Green3);
			}
			else
			{
				/* Misra Coding Rule */
			}
		}
		else
		{
			if(IsChgEvt(kb_GreenINDCmd, On))
			{
				Pwm_IND_Start(Green1, GetDutyCycle(Par_BrightDay));	// PWM Start Function
				Pwm_IND_Start(Green2, GetDutyCycle(Par_BrightDay));	// PWM Start Function
				Pwm_IND_Start(Green3, GetDutyCycle(Par_BrightDay));	// PWM Start Function
				ClrEvt(kb_GreenINDCmd);
			}
			else if(IsChgEvt(kb_WPCDayTimeLEDOut, On))		// 20190122
			{
				Change_PWM_IND_DutyCycle(GetDutyCycle(Par_BrightDay), Green1);
				Change_PWM_IND_DutyCycle(GetDutyCycle(Par_BrightDay), Green2);
				Change_PWM_IND_DutyCycle(GetDutyCycle(Par_BrightDay), Green3);
			}
			else
			{
				/* Misra Coding Rule */
			}
		}

		SetX(kL_Green_OUT, On);
	}
	else
	{
		if(IsChgEvt(kb_GreenINDCmd, Off))		// 20180827 : LED On -> Off �� 1ȸ�� ��� �ϵ��� ���� �߰�
		{
			Pwm_IND_Stop(Green1);		//PWM Stop Function
			Pwm_IND_Stop(Green2);		//PWM Stop Function
			Pwm_IND_Stop(Green3);		//PWM Stop Function
			SetX(kL_Green_OUT, Off);
			ClrEvt(kb_GreenINDCmd);
		}
	}
}

/************************************************************************************************/
/****         Function: GreenLEDOutputControlforRheoStat										*/
/****         Content: Figure 36 Amber LED Output Control Function for No-RheoStat State Chart	*/
/****         Called By: 10ms TASK																*/
/****         argument: void																	*/
/****         return value: void																*/
/****		  Revision: 2018.05.25 Applied 14th													*/
/************************************************************************************************/
void AmberLEDOutputControlforNoRheoStat(void)
{
	if(GetX(kb_AmberINDCmd) == On)
	{
		if(GetX(kb_WPCDayTimeLEDOut) == Off)		/* Day = On, Night = Off */
		{
			if(IsChgEvt(kb_AmberINDCmd, On))
			{
				Pwm_IND_Start(Amber, GetDutyCycle(Par_BrightNight));	// PWM Start Function
				ClrEvt(kb_AmberINDCmd);
			}
			else if(IsChgEvt(kb_WPCDayTimeLEDOut, Off))		// 20190122
			{
				Change_PWM_IND_DutyCycle(GetDutyCycle(Par_BrightNight), Amber);
			}
			else
			{
				/* Misra Coding Rule */
			}
		}
		else
		{
			if(IsChgEvt(kb_AmberINDCmd, On))
			{
				Pwm_IND_Start(Amber, GetDutyCycle(Par_BrightDay));	// PWM Start Function
				ClrEvt(kb_AmberINDCmd);
			}
			else if(IsChgEvt(kb_WPCDayTimeLEDOut, On))		// 20190122
			{
				Change_PWM_IND_DutyCycle(GetDutyCycle(Par_BrightDay), Amber);
			}
			else
			{
				/* Misra Coding Rule */
			}
		}

		SetX(kL_Amber_OUT, On);
	}
	else
	{
		if(IsChgEvt(kb_AmberINDCmd, Off))		// 20180827 : LED On -> Off �� 1ȸ�� ��� �ϵ��� ���� �߰�
		{
			Pwm_IND_Stop(Amber);		//PWM Stop Function
			SetX(kL_Amber_OUT, Off);
			ClrEvt(kb_AmberINDCmd);
		}
	}
}


/************************************************************************************************/
/****         Function: WPCLEDOutputControl                   */
/****         Content:                                */
/****         Called By: 10ms TASK                                */
/****         argument: void                                  */
/****         return value: void                                */
/****     Revision: 2018.12.05 Applied 14th                         */
/************************************************************************************************/
void WPCLEDOutputControl(void)
{
	IND_OptionCheck();

#if defined (USE_AUTOBRIGHT)	/* SCR-210706-003 Auto Bright */
	GreenLEDOutputControlforAutoBright();
	AmberLEDOutputControlforAutoBright();
#else
	GreenLEDOutputControlforRheoStat();
	AmberLEDOutputControlforRheoStat();
#endif

}

