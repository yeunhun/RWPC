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
#include "WPCType.h"
#include "Define.h"
#include "WPCTimer.h"
#include "Data.h"
#include "Rte_SWC_Input.h"

#include "app_can_input_type.h"
#include "app_can_input.h"
#include "app_input_type.h"
#include "app_input.h"

#include "WPCLogicControl.h"
/*******************************************************************************
* Define Functions                                                             *
*******************************************************************************/
void OverTemperatureDetectingControl(void);
/*******************************************************************************
* Define Constant and Macro                                                    *
*******************************************************************************/


/*******************************************************************************
* Declare  Variables                                                           *
*******************************************************************************/
static tTimer16 Timer_OverTemp = {Off, 0};

/************************************************************************************************/
/****         Function: OverTemperatureDetectingControl                     */
/****         Content: Figure 39 Over Temperature Detecting Control Function State Chart    */
/****         Called By: 10ms TASK                                */
/****         argument: void                                  */
/****         return value: void                                */
/****     Revision: 2018.05.25 Applied 14th                         */
/************************************************************************************************/
void OverTemperatureDetectingControl(void)
{
  static e_OverTempState StateOverTemp = Temperature_Init;

	UpTimer16(Timer_OverTemp);

	switch(StateOverTemp)
	{
		case Temperature_Init:
			SetX(kb_TemperatureFault, Off);
			CancelTimer(Timer_OverTemp);

			StateOverTemp = Temperature_Normal;
			break;
			
		case Temperature_Normal:
			if((GetX(kb_WPCStatus) == (uint8)WPCStatus_WPCMode) &&
			   (GetX(kb_DeviceState) != (uint8)DeviceStates_Standby) &&
			   (GetX(kb_DeviceState) != (uint8)DeviceStates_Init) &&
				((b_Temperature_Sensor1 <= Par_OverTempSetVal) ||		// NTC : lower is hotter
				(b_Temperature_Sensor2 <= Par_OverTempSetVal) ||
				(b_Temperature_Sensor3 <= Par_OverTempSetVal)))
			{
				StartTimer(Timer_OverTemp);

				StateOverTemp = TemperatureError_OnCheck;
			}
			break;
			
		case TemperatureError_OnCheck:
			if((GetX(kb_WPCStatus) == (uint8)WPCStatus_Off) ||		/*20201123 SCR-200219-002*/
				(GetX(kb_DeviceState) == (uint8)DeviceStates_Standby) ||	/* SCR-211126-004 : WPC OverTemp Error */
				((b_Temperature_Sensor1 > Par_OverTempSetVal) &&
				(b_Temperature_Sensor2 > Par_OverTempSetVal) &&
				(b_Temperature_Sensor3 > Par_OverTempSetVal)))
			{
				CancelTimer(Timer_OverTemp);

				StateOverTemp = Temperature_Normal;
			}
			else if(Timer_OverTemp.time >= Par_OverTempSetTime)
			{
				CancelTimer(Timer_OverTemp);
				SetX(kb_TemperatureFault, On);
				
				StateOverTemp = Temperature_FaultOn;
			}
			else
			{
				/* MISRA-C */
			}
			break;
			
		case Temperature_FaultOn:
			if(GetX(kb_WPCStatus) == (u8)WPCStatus_Off)				/*20201123 SCR-200219-002*/
			{
				SetX(kb_TemperatureFault, Off);

				StateOverTemp = Temperature_Normal;
			}
			else if((b_Temperature_Sensor1 >= Par_OverTempRstVal) &&
					(b_Temperature_Sensor2 >= Par_OverTempRstVal) &&
					(b_Temperature_Sensor3 >= Par_OverTempRstVal))
			{
				StartTimer(Timer_OverTemp);

				StateOverTemp = TemperatureError_OffCheck;
			}
			else
			{
				/* MISRA-C */
			}
			break;
			
		case TemperatureError_OffCheck:
			if((GetX(kb_WPCStatus) == (u8)WPCStatus_Off) ||			/*20201123 SCR-200219-002*/
				(Timer_OverTemp.time >= Par_OverTempRstTime))
			{
				CancelTimer(Timer_OverTemp);
				SetX(kb_TemperatureFault, Off);

				StateOverTemp = Temperature_Normal;
			}
			else if((b_Temperature_Sensor1 < Par_OverTempRstVal) ||
					(b_Temperature_Sensor2 < Par_OverTempRstVal) ||
					(b_Temperature_Sensor3 < Par_OverTempRstVal))
			{
				CancelTimer(Timer_OverTemp);
				SetX(kb_TemperatureFault, On);

				StateOverTemp = Temperature_FaultOn;
			}
			else
			{
				/* MISRA-C */
			}
			break;
			
		default:
			StateOverTemp = Temperature_Init;
			break;
	}
}



