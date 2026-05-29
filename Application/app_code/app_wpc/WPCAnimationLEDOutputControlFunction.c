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

#include "WPCAnimationLEDOutputTable.h"

/*******************************************************************************
* Define Constant and Macro                                                    *
*******************************************************************************/
typedef enum
{
  getGreen = 0,
  getAmber
}eGetIndiColor_t;

typedef enum
{
  Amber_Fadein = 0,
  Green1_Fadein,
  Green2_Fadein,
  Green3_Fadein,
  GreenFadeOut,
  AmberFadeOut
}eFadeInOutNum_t;

typedef struct
{
  uint8 prevNum;
  uint8 currNum;

  uint16 inCnt;
  uint16 outCnt;

  uint16 ledCurrValue;
  uint16 ledMaxValue;
  uint8  autobrightLevel;
}sFadeInOut_t;

/*******************************************************************************
* Define Functions                                                             *
*******************************************************************************/
void AnimationIND_OptionCheck(void);
void GreenLEDAnimationOutputControlforRheoStat(void);
void AmberLEDAnimationOutputControlforRheoStat(void);
void GreenLEDAnimationOutputControlforNoRheoStat(void);
void AmberLEDAnimationOutputControlforNoRheoStat(void);
void WPCLEDAnimationOutputControl(void);
void IndiType2_FadeInOut_Control(eFadeInOutNum_t eFadeInOutNum);
uint16 * get_autobright_level_arr(uint8 idx, eGetIndiColor_t eGetIndiColor);


/*******************************************************************************
* Declare  Variables                                                           *
*******************************************************************************/

extern u8 b_ChargingComplete;

uint8 anisync_flag = 0u;
uint16 * led_value_arr;
sFadeInOut_t sFadeInOut = {0u, };

/*******************************************************************************
* Define Functions                                                             *
*******************************************************************************/


/*******************************************************************************
* Functions                                                                    *
*******************************************************************************/
void AnimationIND_OptionCheck(void)
{
	if(GetX(kC_CLU_DtntOutSta) == On)
	{
		SetX(kb_WPCDayTimeLEDOut, On);			/* Day = On, Night = Off */
	}
	else
	{
		SetX(kb_WPCDayTimeLEDOut, Off);
	}
}
/************************************************************************************************/
/****         Function: GreenLEDOutputControlforRheoStat										*/
/****         Content: Figure 35 Green LED Output Control Function for RheoStat State Chart		*/
/****         Called By: 10ms TASK																*/
/****         argument: void																	*/
/****         return value: void																*/
/****		  Revision: 2018.05.25 Applied 14th													*/
/************************************************************************************************/
void GreenLEDAnimationOutputControlforRheoStat(void)
{
	if(GetX(kb_GreenINDCmd) == On)
	{
		Pwm_IND_Stop(Amber);
	}
	if((GetX(kb_GreenINDCmd) == On) && (b_ChargingComplete == On))
	{
		if(GetX(kb_WPCDayTimeLEDOut) == On)		/* Day = On, Night = Off */
		{
			if(GetX(kb_GreenINDCmd) == On)
			{
				Pwm_IND_Start(Green1, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel091));	// PWM Start Function
				Pwm_IND_Start(Green2, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel091));	// PWM Start Function
				Pwm_IND_Start(Green3, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel091));	// PWM Start Function
				ClrEvt(kb_GreenINDCmd);
			}
			else if(IsChgEvt(kb_WPCDayTimeLEDOut, On))		// 20190122 : When Rheostate event occurs in IND On state
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
			if(GetX(kb_GreenINDCmd) == On)	//When IND event occurs in Rheostate Off state
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
	}
	
	else if((GetX(kb_GreenINDCmd) == On) && (b_ChargingComplete == Off))
	{
		if(GetX(kb_WPCDayTimeLEDOut) == On)		/* Day = On, Night = Off */
		{
			if(GetX(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_3rdSync)
			{	/* Off -> 3sync max birght */
				if( GetXOld(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_2ndSync )
			  	{
				  	if(GetX(kb_RWPCIndCmdState) == RWPCIndCmdState_3rdChrgFadeIn)
					{
						IndiType2_FadeInOut_Control(Green3_Fadein);
						anisync_flag = 4u; //fadeinsync3
					}
			  	}
				else if( GetXOld(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_Default )	/* When initially placing the mobile phone, the indicator remains ON for 1 second */
			  	{
					Pwm_IND_Start(Green1, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel091));	// PWM Start Function
					Pwm_IND_Start(Green2, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel091));	// PWM Start Function
					Pwm_IND_Start(Green3, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel091));	// PWM Start Function
      				anisync_flag = 5u; //default
			  	}
			  	else if(GetXOld(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_3rdSync)	/* When changing from Type1 to Type2, the indicator remains ON for 1 second */
			  	{
					Pwm_IND_Start(Green1, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel091));	// PWM Start Function
					Pwm_IND_Start(Green2, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel091));	// PWM Start Function
					Pwm_IND_Start(Green3, GetDutyCycle_AutoBright(Par_GreenAutoBrightLevel091));	// PWM Start Function
      				anisync_flag = 6u; //default
			  	}
			}
			else if(GetX(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_Off)
			{
				if(GetXOld(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_3rdSync)
				{
					if(GetX(kb_RWPCIndCmdState) == RWPCIndCmdState_ChrgFadeOut)
					{
            			IndiType2_FadeInOut_Control(GreenFadeOut);
						anisync_flag = 1u; //fadeout
				  	}	
			   	}
			}
			else if(GetX(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_1stSync)
			{
				if(GetXOld(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_Off)
				{
					if(GetX(kb_RWPCIndCmdState) == RWPCIndCmdState_1stChrgFadeIn)
			  	  	{
				  		IndiType2_FadeInOut_Control(Green1_Fadein);
						anisync_flag = 2u; //fadeinsync1	
				  	}
			    }
			}
			else if(GetX(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_2ndSync)
			{
				if(GetXOld(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_1stSync)
				{
					if(GetX(kb_RWPCIndCmdState) == RWPCIndCmdState_2ndChrgFadeIn)
			  		{
						IndiType2_FadeInOut_Control(Green2_Fadein);	
						anisync_flag = 3u; //fadeinsync2
					}
				}
			}
			else
			{
				/* Misra Coding Rule */
			}
		}
		else
		{
			if(IsChgEvt(kb_GreenINDCmd, On) || (GetX(kb_GreenINDCmd) == On))
			{
				if(GetX(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_3rdSync)
				{
				  	if( GetXOld(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_2ndSync )
				  	{
				  		if(GetX(kb_RWPCIndCmdState) == RWPCIndCmdState_3rdChrgFadeIn)
						{
							IndiType2_FadeInOut_Control(Green3_Fadein);
							anisync_flag = 4u; //fadeinsync3
						}
				  	}
				  	else if( GetXOld(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_Default )	/* When initially placing the mobile phone, the indicator remains ON for 1 second */
				  	{
						Pwm_IND_Start(Green1, GetDutyCycle_AutoBright(GetX(kb_GreenLED_Duty_AutoBright)));   // PWM Start Function
          				Pwm_IND_Start(Green2, GetDutyCycle_AutoBright(GetX(kb_GreenLED_Duty_AutoBright)));   // PWM Start Function
          				Pwm_IND_Start(Green3, GetDutyCycle_AutoBright(GetX(kb_GreenLED_Duty_AutoBright)));   // PWM Start Function
          				anisync_flag = 5u; //default
				  	}
				  	else if(GetXOld(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_3rdSync)	/* When changing from Type1 to Type2, the indicator remains ON for 1 second */
				  	{
						Pwm_IND_Start(Green1, GetDutyCycle_AutoBright(GetX(kb_GreenLED_Duty_AutoBright)));   // PWM Start Function
          				Pwm_IND_Start(Green2, GetDutyCycle_AutoBright(GetX(kb_GreenLED_Duty_AutoBright)));   // PWM Start Function
          				Pwm_IND_Start(Green3, GetDutyCycle_AutoBright(GetX(kb_GreenLED_Duty_AutoBright)));   // PWM Start Function
          				anisync_flag = 6u; //default
				  	}
				}
				else if(GetX(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_Off)
				{
					if(GetXOld(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_3rdSync)
					{
						if(GetX(kb_RWPCIndCmdState) == RWPCIndCmdState_ChrgFadeOut)
						{
	            			IndiType2_FadeInOut_Control(GreenFadeOut);
							anisync_flag = 1u; //fadeout
						}				
				   	}
				}
				else if(GetX(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_1stSync)
				{
					if(GetXOld(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_Off)
					{
						if(GetX(kb_RWPCIndCmdState) == RWPCIndCmdState_1stChrgFadeIn)
				  	  	{
					  		IndiType2_FadeInOut_Control(Green1_Fadein);
							anisync_flag = 2u; //fadeinsync1
					  	}
				    }
				}
				else if(GetX(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_2ndSync)
				{
					if(GetXOld(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_1stSync)
					{
						if(GetX(kb_RWPCIndCmdState) == RWPCIndCmdState_2ndChrgFadeIn)
				  		{
							IndiType2_FadeInOut_Control(Green2_Fadein);	
							anisync_flag = 3u; //fadeinsync2
						}
					}
				}
								
			}
			else if(IsDiffEvt(kb_GreenLED_Duty_AutoBright) ||
					IsChgEvt(kb_WPCDayTimeLEDOut, Off))	//Change LED Duty or Rheostat
			{
				if(GetX(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_3rdSync)
				{
					Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(GetX(kb_GreenLED_Duty_AutoBright)), Green1);
					Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(GetX(kb_GreenLED_Duty_AutoBright)), Green2);
					Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(GetX(kb_GreenLED_Duty_AutoBright)), Green3);
				}
				else if(GetX(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_Off)
				{
					Pwm_IND_Stop(Green1);		//PWM Stop Function
					Pwm_IND_Stop(Green2);		//PWM Stop Function
					Pwm_IND_Stop(Green3);		//PWM Stop Function
				}
				else if(GetX(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_1stSync)
				{
					Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(GetX(kb_GreenLED_Duty_AutoBright)), Green1);
				}
				else if(GetX(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_2ndSync)
				{
					Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(GetX(kb_GreenLED_Duty_AutoBright)), Green2);
				}
				else
				{
					/* Misra Coding Rule */
				}
			}
		}
		SetX(kL_Green_OUT, On);
	}
	else
	{
		if(IsChgEvt(kb_GreenINDCmd, Off))		// 20180827 : LED On -> Off �� 1ȸ�� ��� �ϵ��� ���� �߰�
		{
			Pwm_IND_Stop(Green1);		//PWM Stop Function
			Pwm_IND_Stop(Green2);
			Pwm_IND_Stop(Green3);
			SetX(kL_Green_OUT, Off);
			ClrEvt(kb_GreenINDCmd);
		}
	}
}

/************************************************************************************************/
/****         Function: GreenLEDOutputControlforRheoStat										*/
/****         Content: Figure 36 Amber LED Output Control Function for RheoStat State Chart		*/
/****         Called By: 10ms TASK																*/
/****         argument: void																	*/
/****         return value: void																*/
/****		  Revision: 2018.05.25 Applied 14th													*/
/************************************************************************************************/
void AmberLEDAnimationOutputControlforRheoStat(void)
{

	if(GetX(kb_WPCDayTimeLEDOut) == On)		/* Day = On, Night = Off */
	{	
		if(GetX(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_ErrorOn)
		{
			if(GetX(kb_RWPCIndCmdState) == RWPCIndCmdState_ErrorFadeIn)	
			{
			  	IndiType2_FadeInOut_Control(Amber_Fadein);
				ClrEvt(kb_AmberINDCmd);
				SetX(kL_Amber_OUT, On);
			}
		}
		else if(GetX(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_ErrorOff)		
		{
			if(GetX(kb_RWPCIndCmdState) == RWPCIndCmdState_ErrorFadeOut)
			{
				IndiType2_FadeInOut_Control(AmberFadeOut);
				ClrEvt(kb_AmberINDCmd);
				SetX(kL_Amber_OUT, Off);
			}
		}	
		else
		{
			/* Misra Coding Rule */
		}
	}
	else
	{
		if(GetX(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_ErrorOn)
		{
			if(GetX(kb_RWPCIndCmdState) == RWPCIndCmdState_ErrorFadeIn)
			{
				IndiType2_FadeInOut_Control(Amber_Fadein);
				ClrEvt(kb_AmberINDCmd);
				SetX(kL_Amber_OUT, On);
			}
		}
		else if(GetX(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_ErrorOff)
		{
			if(GetX(kb_RWPCIndCmdState) == RWPCIndCmdState_ErrorFadeOut)
			{
				IndiType2_FadeInOut_Control(AmberFadeOut);
				ClrEvt(kb_AmberINDCmd);
				SetX(kL_Amber_OUT, Off);
			}
		}	
		else if(IsDiffEvt(kb_AmberLED_Duty_AutoBright) ||
				IsChgEvt(kb_WPCDayTimeLEDOut, Off))		/* 20190122 */
		{
			if(GetX(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_ErrorOn)
			{
				Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(GetX(kb_AmberLED_Duty_AutoBright)), Amber);
			}
			else if(GetX(kC_RWPC_IndSyncVal) == kRWPCIndSyncVal_ErrorOff)
			{
				Pwm_IND_Stop(Amber);		//PWM Stop Function
				ClrEvt(kb_AmberINDCmd);
				SetX(kL_Amber_OUT, Off);
			}
		}
		else
		{
			/* Misra Coding Rule */
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
void WPCLEDAnimationOutputControl(void)
{
	AnimationIND_OptionCheck();
	GreenLEDAnimationOutputControlforRheoStat();
	AmberLEDAnimationOutputControlforRheoStat();
}



void IndiType2_FadeInOut_Control(eFadeInOutNum_t eFadeInOutNum)
{
  	sFadeInOut.currNum = eFadeInOutNum;
	if(sFadeInOut.prevNum != sFadeInOut.currNum)
	{
	  sFadeInOut.prevNum = sFadeInOut.currNum;
	  sFadeInOut.inCnt = 0u;
	  sFadeInOut.outCnt = 99u;
	}
	
	if(eFadeInOutNum==AmberFadeOut)	/* AmberIND Fade Out */
	{
	  if(GetX(kb_WPCDayTimeLEDOut) == On)
	  {
		 sFadeInOut.autobrightLevel = 91;
	  }
	  else if(GetX(kb_WPCDayTimeLEDOut) == Off)
	  {
	    sFadeInOut.autobrightLevel = GetX(kC_CLU_AutoBrightSta);
	  }
	  led_value_arr = get_autobright_level_arr(sFadeInOut.autobrightLevel, getAmber);
    Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(led_value_arr[sFadeInOut.outCnt]), Amber);

		if(sFadeInOut.outCnt > 0u)
		{
			sFadeInOut.outCnt--;
		}
		else
		{
			Pwm_IND_Stop(Amber);
		}
	}
	else if(eFadeInOutNum==GreenFadeOut) /* GreenIND Fade Out */
	{ 
		if(GetX(kb_WPCDayTimeLEDOut) == On)
		{
			sFadeInOut.autobrightLevel = 91;
		}
		else if(GetX(kb_WPCDayTimeLEDOut) == Off)
		{
			sFadeInOut.autobrightLevel = GetX(kC_CLU_AutoBrightSta);
		}
    	led_value_arr = get_autobright_level_arr(sFadeInOut.autobrightLevel, getGreen);

			Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(led_value_arr[sFadeInOut.outCnt]), Green1);
			Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(led_value_arr[sFadeInOut.outCnt]), Green2);
			Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(led_value_arr[sFadeInOut.outCnt]), Green3);

		if(sFadeInOut.outCnt > 0)
		{
		  sFadeInOut.outCnt--;
		}
		else
		{
			Pwm_IND_Stop(Green1);
			Pwm_IND_Stop(Green2);
			Pwm_IND_Stop(Green3);
		}
	}
	else // FADE IN Green or Amber
	{
		if(GetX(kb_WPCDayTimeLEDOut) == On)
		{
			sFadeInOut.autobrightLevel = 91;
		}
		else if(GetX(kb_WPCDayTimeLEDOut) == Off)
		{
	  		sFadeInOut.autobrightLevel = GetX(kC_CLU_AutoBrightSta);
	  	}
		if((eFadeInOutNum==Green1_Fadein) || (eFadeInOutNum==Green2_Fadein) || (eFadeInOutNum==Green3_Fadein))
		{
			led_value_arr = get_autobright_level_arr(sFadeInOut.autobrightLevel, getGreen);
		}
		else if(eFadeInOutNum == Amber_Fadein)
		{
			led_value_arr = get_autobright_level_arr(sFadeInOut.autobrightLevel, getAmber);
		}
		else
		{
			/* Misra-C */
		}

		sFadeInOut.ledCurrValue = (u16)(led_value_arr[sFadeInOut.inCnt]);
		sFadeInOut.ledMaxValue = (u16)(led_value_arr[99]);

		if(eFadeInOutNum==Green1_Fadein)
		{
			Pwm_IND_Stop(Green2);
			Pwm_IND_Stop(Green3);
			Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(sFadeInOut.ledCurrValue), Green1);
		}
		else if(eFadeInOutNum==Green2_Fadein)
		{
			Pwm_IND_Stop(Green3);
			Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(sFadeInOut.ledMaxValue), Green1);
			Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(sFadeInOut.ledCurrValue), Green2);
		}
		else if(eFadeInOutNum==Green3_Fadein)
		{
			Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(sFadeInOut.ledMaxValue), Green1);
			Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(sFadeInOut.ledMaxValue), Green2);
			Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(sFadeInOut.ledCurrValue), Green3);
		}
		else if(eFadeInOutNum==Amber_Fadein)
		{
			Change_PWM_IND_DutyCycle(GetDutyCycle_AutoBright(sFadeInOut.ledCurrValue), Amber);
		}

		sFadeInOut.inCnt++;
	  if(sFadeInOut.inCnt>=99u)
	  {
	    sFadeInOut.inCnt = 99u;
	  }
	}	
}

uint16 * get_autobright_level_arr(uint8 idx, eGetIndiColor_t eGetIndiColor)
{
  if(eGetIndiColor == getGreen)
  {
    return &sIndiGreenTable[idx].levelArr[0];
  }
  else if(eGetIndiColor == getAmber)
  {
    return &sIndiAmberTable[idx].levelArr[0];
  }
  else
  {
    /* MISRA-C */
  }
}
