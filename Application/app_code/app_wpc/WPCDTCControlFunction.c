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
#include "Cdd_UserDefinedService.h"

#include "WPCType.h"
#include "define.h"
#include "WPCTimer.h"
#include "Data.h"

#include "app_input_type.h"
#include "app_input.h"
#include "app_output_type.h"
#include "app_output.h"
#include "WPCEepControl.h"
#include "WPCDiagonostic.h"
#include "WPCLogicControl.h"


/*******************************************************************************
* Define Functions                                                             *
*******************************************************************************/
static void DTC_B1621_WPCIntErr(void);
static void DTC_B1621_TempSensorFault(void);
static void DTC_B1621_FANFault(void);
void DTC_B1621_Control(void);

/*******************************************************************************
* Define Constant and Macro                                                    *
*******************************************************************************/


/*******************************************************************************
* Declare  Variables                                                           *
*******************************************************************************/
static tTimer8 Timer_DTC_B1621_a_Confirm = {Off, 0u};
static tTimer8 Timer_DTC_B1621_a_Recovery = {Off, 0u};
static tTimer8 Timer_DTC_B1621_d_Confirm = {Off, 0u};

/*******************************************************************************
* Define Functions                                                             *
*******************************************************************************/
static void DTC_B1621_WPCIntErr(void)
{
	static e_ActionState e_DTC_B1621_a = kNoAction;
	
	UpTimer8(Timer_DTC_B1621_a_Confirm);
	UpTimer8(Timer_DTC_B1621_a_Recovery);
	
	switch(e_DTC_B1621_a)
	{
		case kNoAction:
			if((GetX(kb_DTCWPCInternalError) == On) &&
				(Timer_DTC_B1621_a_Confirm.run == Off) &&
				(StateOperatingVoltage == OperatingVoltageState_Normal))
			{
				StartTimer(Timer_DTC_B1621_a_Confirm);
			}
			else if((GetX(kb_DTCWPCInternalError) == Off) || 
					(StateOperatingVoltage != OperatingVoltageState_Normal))
			{
				CancelTimer(Timer_DTC_B1621_a_Confirm);
			}
			else if((Timer_DTC_B1621_a_Confirm.time >= Diag_B1621_ConfirmTime) &&
					(StateOperatingVoltage == OperatingVoltageState_Normal))
			{
				CancelTimer(Timer_DTC_B1621_a_Confirm);
				
				Set_DTC_B1621_WPCInternalError_Present(On);
				/* Set_DTCClear_Count_B1621(0u); */

				e_DTC_B1621_a = kActiveAction;
			}
			else
			{
				/* MISRA-C RULE */
			}
			break;
			
		case kActiveAction:
			if(IsChgEvt(kb_IGN_IN, On))
			{
				/* Clear */
				Set_DTC_B1621_WPCInternalError_Present(Off);

				e_DTC_B1621_a = kNoAction;
			}
			else if(Get_DTC_B1621_Present() == Off)
			{
				SetX(kb_DTCWPCInternalError, Off);
				
				e_DTC_B1621_a = kNoAction;
			}
			else if((Timer_DTC_B1621_a_Recovery.run == Off) &&
					(GetX(kb_DTCWPCInternalError) == Off) &&
					(StateOperatingVoltage == OperatingVoltageState_Normal))
			{
				StartTimer(Timer_DTC_B1621_a_Recovery);
			}
			else if((Timer_DTC_B1621_a_Recovery.run == On) &&
					(Timer_DTC_B1621_a_Recovery.time >= Diag_B1621_RecoveryTime))
			{
				if((GetX(kb_DTCWPCInternalError) == On) ||
					(StateOperatingVoltage != OperatingVoltageState_Normal))
				{
					CancelTimer(Timer_DTC_B1621_a_Recovery);
				}
				else if((GetX(kb_DTCWPCInternalError) == Off) &&
					(StateOperatingVoltage == OperatingVoltageState_Normal))
				{
					CancelTimer(Timer_DTC_B1621_a_Recovery);
					/* Clear */
					Set_DTC_B1621_WPCInternalError_Present(Off);

					e_DTC_B1621_a = kNoAction;
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
			break;
			
		default:
			CancelTimer(Timer_DTC_B1621_a_Confirm);
			CancelTimer(Timer_DTC_B1621_a_Recovery);

			e_DTC_B1621_a = kNoAction;
			break;
	}	
}

static void DTC_B1621_TempSensorFault(void)
{
	static e_ActionState e_DTC_B1621_b = kNoAction;
	
	switch(e_DTC_B1621_b)
	{
		case kNoAction:
			if(IsChgEvt(kb_TempSensorFault, On))
			{
				Set_DTC_B1621_TemperatureSensorFault_Present(On);
				//Set_DTCClear_Count_B1621(0u);

				e_DTC_B1621_b = kActiveAction;
			}
			break;
			
		case kActiveAction:
			if(IsChgEvt(kb_IGN_IN, On))
			{
				/* Clear */
				Set_DTC_B1621_TemperatureSensorFault_Present(Off);
				
				e_DTC_B1621_b = kNoAction;
			}
			else if(Get_DTC_B1621_Present() == Off)
			{
				SetX(kb_TempSensorFault, Off);

				StateTempSensorError = TempSensorError_Off;
				e_DTC_B1621_b = kNoAction;
			}
			else
			{
				/* MISRA-C RULE */
			}
			break;
			
		default:
			e_DTC_B1621_b = kNoAction;
			break;
	}	
}

static void DTC_B1621_FANFault(void)
{
	static e_ActionState e_DTC_B1621_d = kNoAction;
	
	UpTimer8(Timer_DTC_B1621_d_Confirm);

	switch(e_DTC_B1621_d)
	{
		case kNoAction:
			if((GetX(kb_FANFault) == On) &&
				(Timer_DTC_B1621_d_Confirm.run == Off) &&
				(StateOperatingVoltage == OperatingVoltageState_Normal))
			{
				StartTimer(Timer_DTC_B1621_d_Confirm);
			}
			else if((GetX(kb_FANFault) == Off) || 
					(StateOperatingVoltage != OperatingVoltageState_Normal))
			{
				CancelTimer(Timer_DTC_B1621_d_Confirm);
			}
			else if((Timer_DTC_B1621_d_Confirm.run == On) &&
					(Timer_DTC_B1621_d_Confirm.time >= Diag_B1621_ConfirmTime) &&
					(StateOperatingVoltage == OperatingVoltageState_Normal))
			{
				CancelTimer(Timer_DTC_B1621_d_Confirm);
				
				Set_DTC_B1621_FANFault_Present(On);
				//Set_DTCClear_Count_B1621(0u);

				e_DTC_B1621_d = kActiveAction;
			}
			else
			{
				/* MISRA-C RULE */
			}
			break;
			
		case kActiveAction:
			if(IsChgEvt(kb_IGN_IN, On))
			{
				/* Clear */
				Set_DTC_B1621_FANFault_Present(Off);

				e_DTC_B1621_d = kNoAction;
			}
			else if(Get_DTC_B1621_Present() == Off)
			{
				SetX(kb_FANFault, Off);
				
				e_DTC_B1621_d = kNoAction;
			}
			else
			{
				/* MISRA-C RULE */
			}
			break;
		default:
			e_DTC_B1621_d = kNoAction;
			break;
	}
}


/************************************************************************************************/
/****         Function: DTC_B1621_Control                           */
/****         Content:                                  */
/****         Called By: 10ms TASK                                */
/****         argument: void                                  */
/****         return value: void                                */
/****      Revision: 2018.05.25 Applied 14th                          */
/************************************************************************************************/

void DTC_B1621_Control(void)
{
	if((DTC_Set_Status == On) && (StateOperatingVoltage == OperatingVoltageState_Normal))
	{
		/* 1. Charging Controller MCU Error */
		DTC_B1621_WPCIntErr();
		/* 2. Temperature Sensor Fail */
		DTC_B1621_TempSensorFault();
		/* 3. FAN Fail */
		DTC_B1621_FANFault();
	}
}

