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

#include "WPCPWMControl.h"
#include "WPCLogicControl.h"
#include "Superstate_api.h"



/*******************************************************************************
* Define Functions                                                             *
*******************************************************************************/
static void FAN_Off_en(void);
static tSTATE* FAN_Off_init(void);
static void FAN_Off_du(void);
static void FAN_Off_ex(void);
static u8 FAN_Off_run(void);

static void FAN_On_en(void);
static tSTATE* FAN_On_init(void);
static void FAN_On_du(void);
static void FAN_On_ex(void);
static u8 FAN_On_run(void);

void WPCFANControl(void);

/*******************************************************************************
* Define Constant and Macro                               *
*******************************************************************************/
static const tSTATE kFAN_Off = 
{
	FAN_Off_en,
	FAN_Off_init,
	FAN_Off_du,
	FAN_Off_ex,
	FAN_Off_run,
	NULL		/* Misra Coding Rule 11.9 : NULL -> V_NULL */
};

static const tSTATE kFAN_On = 
{
	FAN_On_en,
	FAN_On_init,
	FAN_On_du,
	FAN_On_ex,
	FAN_On_run,
	NULL
};

typedef enum
{
	FanControl_Init = 0,
	FanControl_Operating
}e_WPCFANControl;

/*******************************************************************************
* Declare  Variables                                    *
*******************************************************************************/



/*******************************************************************************
* Define Functions                                      *
*******************************************************************************/
static tSTATE *WPCFAN_Control_stateCUR = NULL;

/* State : kFAN_Off */
static void FAN_Off_en(void)
{
	SetX(kb_FAN_PWM, Par_NoFAN);
	Pwm_FAN_Stop();
	IPS_Control(Off);
	SetX(kL_Fan_OUT, Off);		// SetOutput -> SetX
}

static tSTATE* FAN_Off_init(void)
{
	return NULL;
}

static void FAN_Off_du(void)
{
	/* MISRA-C */
}

static void FAN_Off_ex(void)
{
	/* MISRA-C */
}

static u8 FAN_Off_run(void)
{
	u8 ret = 0u;
	
	if(GetX(kb_ChargingState) == On)		// 20180814_���� ���·� ���� ����
	{
		WPCFAN_Control_stateCUR = transition_exit(WPCFAN_Control_stateCUR, &kFAN_On);
		WPCFAN_Control_stateCUR = transition(WPCFAN_Control_stateCUR, &kFAN_On);
		
		ret = 1u;
	}
	
	return ret;
}

/* State : kFAN_On */
static void FAN_On_en(void)
{
  	IPS_Control(On);
	SetX(kb_FAN_PWM, Par_FANValueLow);
	Pwm_FAN_Start(Par_FANValueLow);	/*20%*/
	Change_PWM_FAN_DutyCycle(Par_FANValueLow);
	SetOutput(kL_Fan_OUT, On);
}

static tSTATE* FAN_On_init(void)
{
	return NULL;
}

static void FAN_On_du(void)
{
	/* MISRA-C */
}

static void FAN_On_ex(void)
{
	/* MISRA-C */
}

static u8 FAN_On_run(void)
{
	u8 ret = 0u;
	
	if(GetX(kb_ChargingState) == Off)		// 20180814_���� ���·� ���� ����
	{
		WPCFAN_Control_stateCUR = transition_exit(WPCFAN_Control_stateCUR, &kFAN_Off);
		WPCFAN_Control_stateCUR = transition(WPCFAN_Control_stateCUR, &kFAN_Off);
		
		ret = 1u;
	}
	
	return ret;
}


/************************************************************************************************/
/****         Function: WPCFANControl                             */
/****         Content: Figure 45 FAN Control Function State Chart               */
/****         Called By: 10ms TASK                                */
/****         argument: void                                  */
/****         return value: void                                */
/****     Revision: 2018.05.18 Applied 14th                         */
/************************************************************************************************/
void WPCFANControl(void)
{
  static e_WPCFANControl sts_WPCFANControl = FanControl_Init;
	
	switch(sts_WPCFANControl)
	{
		case FanControl_Init:
			WPCFAN_Control_stateCUR = &kFAN_Off;
			WPCFAN_Control_stateCUR = transition(WPCFAN_Control_stateCUR, &kFAN_Off);			
			sts_WPCFANControl = FanControl_Operating;
			break;

		case FanControl_Operating:
			(void)CurrentRun(WPCFAN_Control_stateCUR);
			break;
			
		default:
			/* MISRA-C */
			break;
	}
}
