/****************************************************************************************
* Project         : WPC                                 *
* File Name       :                                   *
* Compiler        : IAR                                 *
* Author          : Limjo Hong                                            *
* Created at      : 2018-05-24                                                      *
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
void PreventionOfSMKLFInterferenceControl(void);

/*******************************************************************************
* Define Constant and Macro                                                    *
*******************************************************************************/


/*******************************************************************************
* Declare  Variables                                                           *
*******************************************************************************/
static tTimer16 Timer_LFOffCheck = {Off, 0u};

/************************************************************************************************/
/****         Function: PreventionOfSMKLFInterferenceControl                  */
/****         Content: Figure 28 Prevention of SMK LF Interference Control State Chart      */
/****         Called By: 10ms TASK                                */
/****         argument: void                                  */
/****         return value: void                                */
/****     Revision: 2018.05.24 Applied 14th                         */
/************************************************************************************************/
void PreventionOfSMKLFInterferenceControl(void)
{
  static e_PreventionOfSMKLFInterferenceControl sts_PreventionOfSMKLFInterferenceControl = LFSearching_Init;

	UpTimer16(Timer_LFOffCheck);
	
	switch(sts_PreventionOfSMKLFInterferenceControl)
	{
		case LFSearching_Init:
			CancelTimer(Timer_LFOffCheck);
			SetX(kb_LFState, (u8)LF_OFF);
		
			sts_PreventionOfSMKLFInterferenceControl = LFSearching_Off;
			break;
		case LFSearching_Off:
			if((GetX(kC_BCM_SmkOptTyp) == On) &&
				(GetX(kb_WPCStatus) == (u8)WPCStatus_WPCMode))
			{
				if((GetX(kC_Latch_TypeOption_DRV) == (u8)kLatch_TypeOption_On) &&
				   ((GetX(kC_Warn_DrvDrSwSta_SBCM) == On) ||
				  	(GetX(kC_Warn_AsstDrSwSta_SBCM) == On) ||
				  	(GetX(kC_Warn_RrLftDrSwSta_SBCM) == On) ||
				  	(GetX(kC_Warn_RrRtDrSwSta_SBCM) == On) ||
				  	(GetX(kC_LFAnt_SrchSta) == On)))
				{
					SetX(kb_LFState, (u8)LF_ON);
					StartTimer(Timer_LFOffCheck);
					sts_PreventionOfSMKLFInterferenceControl = LFSearching_On;
				}
				else if((GetX(kC_Latch_TypeOption_DRV) != (u8)kLatch_TypeOption_On) &&
						((GetX(kC_Warn_DrvDrSwSta) == On) ||
						(GetX(kC_Warn_AsstDrSwSta) == On) ||
						(GetX(kC_Warn_RrLftDrSwSta) == On) ||
						(GetX(kC_Warn_RrRtDrSwSta) == On) ||
						(GetX(kC_LFAnt_SrchSta) == On)))
				{
					SetX(kb_LFState, (u8)LF_ON);
					StartTimer(Timer_LFOffCheck);
					sts_PreventionOfSMKLFInterferenceControl = LFSearching_On;
				}
				else
				{
					/* Misra-C Rule */
				}

			}
			else
			{
				/* Misra-C Rule */
			}
			break;
	
		case LFSearching_On:
			if((GetX(kb_WPCStatus) == (u8)WPCStatus_Off) ||		/* 20201123 SCR-200519-005 */	
				(GetX(kC_BCM_SmkOptTyp) == Off))
			{
				CancelTimer(Timer_LFOffCheck);
				SetX(kb_LFState, (u8)LF_OFF);
				
				sts_PreventionOfSMKLFInterferenceControl = LFSearching_Off;
			}
			else if(IsChgEvt(kC_LFAnt_SrchSta, On))
			{
				SetX(kb_LFState, (u8)LF_ON);
				StartTimer(Timer_LFOffCheck); /* Restart Timer */
				
				sts_PreventionOfSMKLFInterferenceControl = LFSearching_On;
			}
			else if((GetX(kC_BCM_SmkOptTyp) == On) &&
					(Timer_LFOffCheck.time >= Par_LfOffChkTime) &&
					(GetX(kC_LFAnt_SrchSta) == Off))
			{	
					if((GetX(kC_Latch_TypeOption_DRV) == (u8)kLatch_TypeOption_On) &&
						(GetX(kC_Warn_DrvDrSwSta_SBCM) == Off) && 
						(GetX(kC_Warn_AsstDrSwSta_SBCM) == Off) &&
				    	(GetX(kC_Warn_RrLftDrSwSta_SBCM) == Off) && 
				    	(GetX(kC_Warn_RrRtDrSwSta_SBCM) == Off))				
					{
						SetX(kb_LFState, (u8)LF_OFF);
						CancelTimer(Timer_LFOffCheck);

						sts_PreventionOfSMKLFInterferenceControl = LFSearching_Off;
					}
					else if((GetX(kC_Latch_TypeOption_DRV) != (u8)kLatch_TypeOption_On) &&
							(GetX(kC_Warn_DrvDrSwSta) == Off) && 
					 		(GetX(kC_Warn_AsstDrSwSta) == Off) && 
					 		(GetX(kC_Warn_RrLftDrSwSta) == Off) && 
					 		(GetX(kC_Warn_RrRtDrSwSta) == Off))
					
					{
							SetX(kb_LFState, (u8)LF_OFF);
							CancelTimer(Timer_LFOffCheck);

							sts_PreventionOfSMKLFInterferenceControl = LFSearching_Off;
					}
					else
					{

					}

			}
			else
			{
				/* Misra-C Rule */
			}
			break;
			
		default:
			sts_PreventionOfSMKLFInterferenceControl = LFSearching_Init;
			break;
	}
}

