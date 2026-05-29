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
#include "Superstate_api.h"

/*******************************************************************************
* Define Functions                                                             *
*******************************************************************************/
static void CurrentMonitoring_Off_en(void);
static tSTATE* CurrentMonitoring_Off_init(void);
static void CurrentMonitoring_Off_du(void);
static void CurrentMonitoring_Off_ex(void);
static u8 CurrentMonitoring_Off_run(void);

static void CurrentMonitoring_On_en(void);
static tSTATE* CurrentMonitoring_On_init(void);
static void CurrentMonitoring_On_du(void);
static void CurrentMonitoring_On_ex(void);
static u8 CurrentMonitoring_On_run(void);

static void CurrentMonitoring_FaultOff_en(void);
static tSTATE* CurrentMonitoring_FaultOff_init(void);
static void CurrentMonitoring_FaultOff_du(void);
static void CurrentMonitoring_FaultOff_ex(void);
static u8 CurrentMonitoring_FaultOff_run(void);

static void CurrentMonitoring_FaultOn_en(void);
static tSTATE* CurrentMonitoring_FaultOn_init(void);
static void CurrentMonitoring_FaultOn_du(void);
static void CurrentMonitoring_FaultOn_ex(void);
static u8 CurrentMonitoring_FaultOn_run(void);

static void CurrentMonitoring_Normal_en(void);
static tSTATE* CurrentMonitoring_Normal_init(void);
static void CurrentMonitoring_Normal_du(void);
static void CurrentMonitoring_Normal_ex(void);
static u8 CurrentMonitoring_Normal_run(void);

static void CurrentMonitoring_Filtering_en(void);
static tSTATE* CurrentMonitoring_Filtering_init(void);
static void CurrentMonitoring_Filtering_du(void);
static void CurrentMonitoring_Filtering_ex(void);
static u8 CurrentMonitoring_Filtering_run(void);

static void CurrentMonitoring_Fault_en(void);
static tSTATE* CurrentMonitoring_Fault_init(void);
static void CurrentMonitoring_Fault_du(void);
static void CurrentMonitoring_Fault_ex(void);
static u8 CurrentMonitoring_Fault_run(void);

static void CurrentMonitoring_Inhibit_en(void);
static tSTATE* CurrentMonitoring_Inhibit_init(void);
static void CurrentMonitoring_Inhibit_du(void);
static void CurrentMonitoring_Inhibit_ex(void);
static u8 CurrentMonitoring_Inhibit_run(void);

void OverCurrentDetectingControl(void);

/*******************************************************************************
* Define Constant and Macro                                                    *
*******************************************************************************/
static const tSTATE kCurrentMonitoring_Off = 
{
	CurrentMonitoring_Off_en,
	CurrentMonitoring_Off_init,
	CurrentMonitoring_Off_du,
	CurrentMonitoring_Off_ex,
	CurrentMonitoring_Off_run,
	NULL
};

static const tSTATE kCurrentMonitoring_On = 
{
	CurrentMonitoring_On_en,
	CurrentMonitoring_On_init,
	CurrentMonitoring_On_du,
	CurrentMonitoring_On_ex,
	CurrentMonitoring_On_run,
	NULL
};

static const tSTATE kCurrentMonitoring_FaultOff = 
{
	CurrentMonitoring_FaultOff_en,
	CurrentMonitoring_FaultOff_init,
	CurrentMonitoring_FaultOff_du,
	CurrentMonitoring_FaultOff_ex,
	CurrentMonitoring_FaultOff_run,
	&kCurrentMonitoring_On
};

static const tSTATE kCurrentMonitoring_FaultOn = 
{
	CurrentMonitoring_FaultOn_en,
	CurrentMonitoring_FaultOn_init,
	CurrentMonitoring_FaultOn_du,
	CurrentMonitoring_FaultOn_ex,
	CurrentMonitoring_FaultOn_run,
	&kCurrentMonitoring_On
};

static const tSTATE kCurrentMonitoring_Normal = 
{
	CurrentMonitoring_Normal_en,
	CurrentMonitoring_Normal_init,
	CurrentMonitoring_Normal_du,
	CurrentMonitoring_Normal_ex,
	CurrentMonitoring_Normal_run,
	&kCurrentMonitoring_FaultOff
};

static const tSTATE kCurrentMonitoring_Filtering = 
{
	CurrentMonitoring_Filtering_en,
	CurrentMonitoring_Filtering_init,
	CurrentMonitoring_Filtering_du,
	CurrentMonitoring_Filtering_ex,
	CurrentMonitoring_Filtering_run,
	&kCurrentMonitoring_FaultOff
};

static const tSTATE kCurrentMonitoring_Fault = 
{
	CurrentMonitoring_Fault_en,
	CurrentMonitoring_Fault_init,
	CurrentMonitoring_Fault_du,
	CurrentMonitoring_Fault_ex,
	CurrentMonitoring_Fault_run,
	&kCurrentMonitoring_FaultOn
};

static const tSTATE kCurrentMonitoring_Inhibit = 
{
	CurrentMonitoring_Inhibit_en,
	CurrentMonitoring_Inhibit_init,
	CurrentMonitoring_Inhibit_du,
	CurrentMonitoring_Inhibit_ex,
	CurrentMonitoring_Inhibit_run,
	&kCurrentMonitoring_FaultOn
};

typedef enum
{
	OvrCurrDetect_Init = 0u,
	OvrCurrDetect_Operating
}e_OverCurrentDetectingControl;

/*******************************************************************************
* Declare  Variables                                                           *
*******************************************************************************/
static tTimer16	Timer_OvrCurr = {Off, 0u};
static tTimer16	Timer_ReOvrCurr = {Off, 0u};
static u8 Counter_OverCurr = 0u;

/*******************************************************************************
* Define Functions                                                             *
*******************************************************************************/
static tSTATE *OverCurrentDetecting_Control_stateCUR = NULL;

/* State : kCurrentError_Off */
static void CurrentMonitoring_Off_en(void)
{
	SetX(kb_CurrentFault, Off);
	Counter_OverCurr = 0u;
	CancelTimer(Timer_OvrCurr);
	CancelTimer(Timer_ReOvrCurr);
}

static tSTATE* CurrentMonitoring_Off_init(void)
{
	return NULL;
}

static void CurrentMonitoring_Off_du(void)
{
	/* MISRA-C */
}

static void CurrentMonitoring_Off_ex(void)
{
	/* MISRA-C */
}

static u8 CurrentMonitoring_Off_run(void)
{
	u8 ret = 0u;
	
	if(GetX(kb_WPCStatus) == (u8)WPCStatus_WPCMode)
	{
		OverCurrentDetecting_Control_stateCUR = transition_exit(OverCurrentDetecting_Control_stateCUR, &kCurrentMonitoring_On);
		OverCurrentDetecting_Control_stateCUR = transition(OverCurrentDetecting_Control_stateCUR, &kCurrentMonitoring_On);
		
		ret = 1u;
	}
	
	return ret;
}

/* State : kCurrentMonitoring_On */
static void CurrentMonitoring_On_en(void)
{
	/* MISRA-C */
}

static tSTATE* CurrentMonitoring_On_init(void)
{
	tSTATE *ret_state = NULL;
	
	OverCurrentDetecting_Control_stateCUR = &kCurrentMonitoring_FaultOff;
	ret_state = &kCurrentMonitoring_FaultOff;
	
	return ret_state;
}
static void CurrentMonitoring_On_du(void)
{
	/* MISRA-C */
}

static void CurrentMonitoring_On_ex(void)
{
	/* MISRA-C */
}

static u8 CurrentMonitoring_On_run(void)
{
	u8 ret = 0u;
	
	if(GetX(kb_WPCStatus) == (u8)WPCStatus_Off)
	{
		OverCurrentDetecting_Control_stateCUR = transition_exit(OverCurrentDetecting_Control_stateCUR, &kCurrentMonitoring_Off);
		OverCurrentDetecting_Control_stateCUR = transition(OverCurrentDetecting_Control_stateCUR, &kCurrentMonitoring_Off);
		
		ret = 1u;
	}
	
	return ret;
}

/* State : kCurrentMonitoring_FaultOff */
static void CurrentMonitoring_FaultOff_en(void)
{
	SetX(kb_CurrentFault, Off);
}

static tSTATE* CurrentMonitoring_FaultOff_init(void)
{
	tSTATE *ret_state = NULL;
	
	if(b_CurrentCurr < Par_OvrCurrSetVal)
	{
		OverCurrentDetecting_Control_stateCUR = &kCurrentMonitoring_Normal;
		ret_state = &kCurrentMonitoring_Normal;
	}
	else
	{
		OverCurrentDetecting_Control_stateCUR = &kCurrentMonitoring_Filtering;
		ret_state = &kCurrentMonitoring_Filtering;
	}
	return ret_state;
}
static void CurrentMonitoring_FaultOff_du(void)
{
	/* MISRA-C */
}

static void CurrentMonitoring_FaultOff_ex(void)
{
	/* MISRA-C */
}

static u8 CurrentMonitoring_FaultOff_run(void)
{
	return 0u;
}

/* State : kCurrentMonitoring_FaultOn */
static void CurrentMonitoring_FaultOn_en(void)
{
	SetX(kb_CurrentFault, On);
}

static tSTATE* CurrentMonitoring_FaultOn_init(void)
{
	tSTATE *ret_state = NULL;
	
	OverCurrentDetecting_Control_stateCUR = &kCurrentMonitoring_Fault;
	ret_state = &kCurrentMonitoring_Fault;
	
	return ret_state;
}
static void CurrentMonitoring_FaultOn_du(void)
{
	/* MISRA-C */
}

static void CurrentMonitoring_FaultOn_ex(void)
{
	/* MISRA-C */
}

static u8 CurrentMonitoring_FaultOn_run(void)
{
	u8 ret = 0u;
	
	if((Counter_OverCurr < Par_OvrCurrCnt) &&
	   (Timer_ReOvrCurr.time >= Par_ReOvrCurrSetTime))
	{
		OverCurrentDetecting_Control_stateCUR = transition_exit(OverCurrentDetecting_Control_stateCUR, &kCurrentMonitoring_FaultOff);
		OverCurrentDetecting_Control_stateCUR = transition(OverCurrentDetecting_Control_stateCUR, &kCurrentMonitoring_FaultOff);
		
		ret = 1u;
	}
	
	return ret;
}

/* State : kCurrentMonitoring_Normal */
static void CurrentMonitoring_Normal_en(void)
{
	Counter_OverCurr = 0u;
}

static tSTATE* CurrentMonitoring_Normal_init(void)
{
	return NULL;
}
static void CurrentMonitoring_Normal_du(void)
{
	/* MISRA-C */
}

static void CurrentMonitoring_Normal_ex(void)
{
	/* MISRA-C */
}

static u8 CurrentMonitoring_Normal_run(void)
{
	u8 ret = 0u;
	
	if(b_CurrentCurr >= Par_OvrCurrSetVal)
	{
		OverCurrentDetecting_Control_stateCUR = transition_exit(OverCurrentDetecting_Control_stateCUR, &kCurrentMonitoring_Filtering);
		OverCurrentDetecting_Control_stateCUR = transition(OverCurrentDetecting_Control_stateCUR, &kCurrentMonitoring_Filtering);
		
		ret = 1u;
	}
	
	return ret;
}

/* State : kCurrentMonitoring_Filtering */
static void CurrentMonitoring_Filtering_en(void)
{
	StartTimer(Timer_OvrCurr);
}

static tSTATE* CurrentMonitoring_Filtering_init(void)
{
	return NULL;
}
static void CurrentMonitoring_Filtering_du(void)
{
	/* MISRA-C */
}

static void CurrentMonitoring_Filtering_ex(void)
{
	CancelTimer(Timer_OvrCurr);
}

static u8 CurrentMonitoring_Filtering_run(void)
{
	u8 ret = 0u;
	
	if(b_CurrentCurr < Par_OvrCurrSetVal)
	{
		OverCurrentDetecting_Control_stateCUR = transition_exit(OverCurrentDetecting_Control_stateCUR, &kCurrentMonitoring_Normal);
		OverCurrentDetecting_Control_stateCUR = transition(OverCurrentDetecting_Control_stateCUR, &kCurrentMonitoring_Normal);
		
		ret = 1u;
	}
	else if(Timer_OvrCurr.time >= Par_OvrCurrSetTime)
	{
		OverCurrentDetecting_Control_stateCUR = transition_exit(OverCurrentDetecting_Control_stateCUR, &kCurrentMonitoring_FaultOn);
		OverCurrentDetecting_Control_stateCUR = transition(OverCurrentDetecting_Control_stateCUR, &kCurrentMonitoring_FaultOn);
		
		ret = 1u;
	}
	else
	{
		/* MISRA-C */
	}
	return ret;
}

/* State : kCurrentMonitoring_Fault */
static void CurrentMonitoring_Fault_en(void)
{
	StartTimer(Timer_ReOvrCurr);
	Counter_OverCurr++;
}

static tSTATE* CurrentMonitoring_Fault_init(void)
{
	return NULL;
}
static void CurrentMonitoring_Fault_du(void)
{
	/* MISRA-C */
}

static void CurrentMonitoring_Fault_ex(void)
{
	CancelTimer(Timer_ReOvrCurr);
}

static u8 CurrentMonitoring_Fault_run(void)
{
	u8 ret = 0u;
	
	if(Counter_OverCurr >= Par_OvrCurrCnt)
	{
		OverCurrentDetecting_Control_stateCUR = transition_exit(OverCurrentDetecting_Control_stateCUR, &kCurrentMonitoring_Inhibit);
		OverCurrentDetecting_Control_stateCUR = transition(OverCurrentDetecting_Control_stateCUR, &kCurrentMonitoring_Inhibit);
		
		ret = 1u;
	}
	return ret;
}

/* State : kCurrentMonitoring_Inhibit */
static void CurrentMonitoring_Inhibit_en(void)
{
	/* MISRA-C */
}

static tSTATE* CurrentMonitoring_Inhibit_init(void)
{
	return NULL;
}
static void CurrentMonitoring_Inhibit_du(void)
{
	/* MISRA-C */
}

static void CurrentMonitoring_Inhibit_ex(void)
{
	/* MISRA-C */
}

static u8 CurrentMonitoring_Inhibit_run(void)
{
	return 0u;
}

/************************************************************************************************/
/****         Function: OverCurrentDetectingControl                       */
/****         Content: Figure 30 Over Current Detecting Control State Chart           */
/****         Called By: 10ms TASK                                */
/****         argument: void                                  */
/****         return value: void                                */
/****     Revision: 2018.05.25 Applied 14th                         */
/************************************************************************************************/
void OverCurrentDetectingControl(void)
{
  static e_OverCurrentDetectingControl sts_OverCurrentDetectingControl = OvrCurrDetect_Init;
	
	UpTimer16(Timer_OvrCurr);
	UpTimer16(Timer_ReOvrCurr);

	switch(sts_OverCurrentDetectingControl)
	{
		case OvrCurrDetect_Init:
			OverCurrentDetecting_Control_stateCUR = &kCurrentMonitoring_Off;
			OverCurrentDetecting_Control_stateCUR = transition(OverCurrentDetecting_Control_stateCUR, &kCurrentMonitoring_Off);
			sts_OverCurrentDetectingControl = OvrCurrDetect_Operating;
			break;

		case OvrCurrDetect_Operating:
			(void)CurrentRun(OverCurrentDetecting_Control_stateCUR);
			break;
			
		default:
			/* MISRA-C */
			break;
	}
}


