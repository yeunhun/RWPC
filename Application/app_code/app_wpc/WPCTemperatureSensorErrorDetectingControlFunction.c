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
void TemperatureSensorErrorDetectingControl(void);
/*******************************************************************************
* Define Constant and Macro                                                    *
*******************************************************************************/


/*******************************************************************************
* Declare  Variables                                                           *
*******************************************************************************/
static tTimer8 Timer_TempSensor_Check = {Off, 0u};

e_TempSensorErrorState StateTempSensorError = TempSensorError_Init;
/************************************************************************************************/
/****         Function: TemperatureSensorErrorDetectionControl                  */
/****         Content: Figure 32 Temperature Sensor Error Detecting Control State Chart     */
/****         Called By: 10ms TASK                                */
/****         argument: void                                  */
/****         return value: void                                */
/****     Revision: 2018.05.25 Applied 14th                         */
/************************************************************************************************/
void TemperatureSensorErrorDetectingControl(void)
{
  UpTimer8(Timer_TempSensor_Check);

	switch(StateTempSensorError)
	{
		case TempSensorError_Init:
			SetX(kb_TempSensorFault, Off);
			CancelTimer(Timer_TempSensor_Check);

			StateTempSensorError = TempSensorError_Off;
			break;
			
		case TempSensorError_Off:
			if((GetX(kb_WPCStatus) == (u8)WPCStatus_WPCMode) &&
				((b_Temperature_SensorFault1 == On) ||
				(b_Temperature_SensorFault2 == On) ||
				(b_Temperature_SensorFault3 == On)))
			{
				StartTimer(Timer_TempSensor_Check);

				StateTempSensorError = TempSensorError_Check;
			}
			break;

		case TempSensorError_Check:
			if((GetX(kb_WPCStatus) != (u8)WPCStatus_WPCMode) ||
				((b_Temperature_SensorFault1 == Off) &&
				(b_Temperature_SensorFault2 == Off) &&
				(b_Temperature_SensorFault3 == Off)))
			{
				SetX(kb_TempSensorFault, Off);
				CancelTimer(Timer_TempSensor_Check);

				StateTempSensorError = TempSensorError_Off;
			}
			else if(Timer_TempSensor_Check.time >= Par_SensorFaultSetTime)
			{
				SetX(kb_TempSensorFault, On);
				CancelTimer(Timer_TempSensor_Check);

				StateTempSensorError = TempSensorError_On;
			}
			else
			{
				/* MISRA-C */
			}
			break;

		case TempSensorError_On:
			if(GetX(kb_WPCStatus) == (u8)WPCStatus_Off)		/*20201123 SCR-200219-002*/
			{
				SetX(kb_TempSensorFault, Off);

				StateTempSensorError = TempSensorError_Off;
			}
			break;

		default:
			StateTempSensorError = TempSensorError_Init;
			break;
	}
}




