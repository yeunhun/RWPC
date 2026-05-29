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
#include "Superstate_api.h"

/*******************************************************************************
* Define Functions                                                             *
*******************************************************************************/
static void OperationMode_OFF_en(void);
static tSTATE* OperationMode_OFF_init(void);
static void OperationMode_OFF_du(void);
static void OperationMode_OFF_ex(void);
static u8 OperationMode_OFF_run(void);

static void OperationMode_WPC_en(void);
static tSTATE* OperationMode_WPC_init(void);
static void OperationMode_WPC_du(void);
static void OperationMode_WPC_ex(void);
static u8 OperationMode_WPC_run(void);
/*******************************************************************************
* Define Constant and Macro                                                    *
*******************************************************************************/
static const tSTATE kOperationMode_OFF = 
{
	OperationMode_OFF_en,
	OperationMode_OFF_init,
	OperationMode_OFF_du,
	OperationMode_OFF_ex,
	OperationMode_OFF_run,
	NULL
};

static const tSTATE kOperationMode_WPC = 
{
	OperationMode_WPC_en,
	OperationMode_WPC_init,
	OperationMode_WPC_du,
	OperationMode_WPC_ex,
	OperationMode_WPC_run,
	NULL
};

uint8 ModeStatus = Off;

//static void Receive_NFCDetection(void);

void WPCModeControl(void);

/*******************************************************************************
* Declare  Variables                                                           *
*******************************************************************************/
tTimer16 Timer_NFCTimeOutConfirm = {Off, 0u};

/*******************************************************************************
* Define Functions                                                             *
*******************************************************************************/
static tSTATE *WPCNFCMode_Control_stateCUR = NULL;

/* State : kOperationMode_OFF */
static void OperationMode_OFF_en(void)
{
	//SetOutput(kC_WPC_Status, (u8)kWPCStatus_Off);
	SetX(kb_WPCStatus, Off);
}

static tSTATE* OperationMode_OFF_init(void)
{
	return NULL;
}

static void OperationMode_OFF_du(void)
{
	/* MISRA-C */
}

static void OperationMode_OFF_ex(void)
{
	/* MISRA-C */
}

static u8 OperationMode_OFF_run(void)
{
	u8 ret = 0u;

	if ((GetX(kb_IGN_IN) == On) &&		// TSCR-778
	    (GetX(kb_WPCSWOption) == (u8)kWPCOnOff_On))
	{
		WPCNFCMode_Control_stateCUR = transition_exit(WPCNFCMode_Control_stateCUR, &kOperationMode_WPC);
		WPCNFCMode_Control_stateCUR = transition(WPCNFCMode_Control_stateCUR, &kOperationMode_WPC);
		
		ret = 1u;
	}
	else
	{
		/* MISRA-C */
	}

	return ret;
}


/* State : kOperationMode_WPC */
static void OperationMode_WPC_en(void)
{
	SetX(kb_WPCStatus, (u8)WPCStatus_WPCMode);
}

static tSTATE* OperationMode_WPC_init(void)
{
	return NULL;
}

static void OperationMode_WPC_du(void)
{
	/* MISRA-C */
}

static void OperationMode_WPC_ex(void)
{
	/* MISRA-C */
}

static u8 OperationMode_WPC_run(void)
{
	u8 ret = 0u;

	if((GetX(kb_WPCSWOption) == (u8)kWPCOnOff_Off) ||
		    (GetX(kb_IGN_IN) == Off))							/* Function Set 11 */
	{
		WPCNFCMode_Control_stateCUR = transition_exit(WPCNFCMode_Control_stateCUR, &kOperationMode_OFF);
		WPCNFCMode_Control_stateCUR = transition(WPCNFCMode_Control_stateCUR, &kOperationMode_OFF);
		
		ret = 1u;
	}
	else
	{
		/* MISRA-C */
	}
		
	return ret;
}


/************************************************************************************************/
/****         Function: WPCNFCModeControl                           */
/****         Content: Figure 22 WPC & NFC Mode Control for Front WPC Function State Chart    */
/****         Called By: 10ms TASK                                */
/****         argument: void                                  */
/****         return value: void                                */
/****     Revision: 2018.05.24 Applied 14th                         */
/************************************************************************************************/
void WPCNFCModeControl(void)
{
	static e_WPCNFCModeControl sts_WPCNFCModeControl = ModeControl_Init;
	
	switch(sts_WPCNFCModeControl)
	{
		case ModeControl_Init:
			WPCNFCMode_Control_stateCUR = &kOperationMode_OFF;
			WPCNFCMode_Control_stateCUR = transition(WPCNFCMode_Control_stateCUR, &kOperationMode_OFF);			
			sts_WPCNFCModeControl = ModeControl_Operating;
			break;

		case ModeControl_Operating:
			(void)CurrentRun(WPCNFCMode_Control_stateCUR);
			break;
			
		default:
			/* MISRA-C */
			break;
	}
}







