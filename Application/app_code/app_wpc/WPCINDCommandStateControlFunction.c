/******************************************************************************
 * Project      	: 	KA4 PE WPC
 * File Name    	: 	wpcindanimationcontrol.c
 * Compiler			: 	Eclipse
 * Author       	: 	Kim Seol Nyun (snowyear@mobaseelec.com)
 * Created at   	: 	2022-08-24
 * Code Editor		: 	Source Insight (Recomended Font : D2Coding / Size 10)
 * Revision     	: 	Version 0.1
 * Copyright  	 	: 	Copyright Seoyon Electronics Co.Ltd. All Rights Reserved
 * Description  	: 	
 *
 ******************************************************************************/




/******************************************************************************
	Include Headers
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
#include "app_output_type.h"
#include "app_output.h"

#include "WPCEepControl.h"
#include "WPCLogicControl.h"
#include "Superstate_api.h"
#include "WPCPWMControl.h"

/******************************************************************************
	Declare Function Prototypes
*******************************************************************************/
static void WPCINDCmdState_Default_en(void);
static const tSTATE* WPCINDCmdState_Default_init(void);
static void WPCINDCmdState_Default_du(void);
static void WPCINDCmdState_Default_ex(void);
static u8 WPCINDCmdState_Default_run(void);

static void WPCINDCmdState_Charging_en(void);
static const tSTATE* WPCINDCmdState_Charging_init(void);
static void WPCINDCmdState_Charging_du(void);
static void WPCINDCmdState_Charging_ex(void);
static u8 WPCINDCmdState_Charging_run(void);

static void WPCINDCmdState_Off_en(void);
static const tSTATE* WPCINDCmdState_Off_init(void);
static void WPCINDCmdState_Off_du(void);
static void WPCINDCmdState_Off_ex(void);
static u8 WPCINDCmdState_Off_run(void);

static void WPCINDCmdState_3rdSync_en(void);
static const tSTATE* WPCINDCmdState_3rdSync_init(void);
static void WPCINDCmdState_3rdSync_du(void);
static void WPCINDCmdState_3rdSync_ex(void);
static u8 WPCINDCmdState_3rdSync_run(void);

static void WPCINDCmdState_2ndSync_en(void);
static const tSTATE* WPCINDCmdState_2ndSync_init(void);
static void WPCINDCmdState_2ndSync_du(void);
static void WPCINDCmdState_2ndSync_ex(void);
static u8 WPCINDCmdState_2ndSync_run(void);

static void WPCINDCmdState_1stSync_en(void);
static const tSTATE* WPCINDCmdState_1stSync_init(void);
static void WPCINDCmdState_1stSync_du(void);
static void WPCINDCmdState_1stSync_ex(void);
static u8 WPCINDCmdState_1stSync_run(void);

static void WPCINDCmdState_ChrgFadeOut_en(void);
static const tSTATE* WPCINDCmdState_ChrgFadeOut_init(void);
static void WPCINDCmdState_ChrgFadeOut_du(void);
static void WPCINDCmdState_ChrgFadeOut_ex(void);
static u8 WPCINDCmdState_ChrgFadeOut_run(void);

#if 0 /* TSCR-1002_WPC_AnimationIND LED Off Time Change */
static void WPCINDCmdState_ChrgOff_en(void);
static const tSTATE* WPCINDCmdState_ChrgOff_init(void);
static void WPCINDCmdState_ChrgOff_du(void);
static void WPCINDCmdState_ChrgOff_ex(void);
static u8 WPCINDCmdState_ChrgOff_run(void);
#endif

static void WPCINDCmdState_3rdChargeFadeIn_en(void);
static const tSTATE* WPCINDCmdState_3rdChargeFadeIn_init(void);
static void WPCINDCmdState_3rdChargeFadeIn_du(void);
static void WPCINDCmdState_3rdChargeFadeIn_ex(void);
static u8 WPCINDCmdState_3rdChargeFadeIn_run(void);

static void WPCINDCmdState_3rdChargeOn_en(void);
static const tSTATE* WPCINDCmdState_3rdChargeOn_init(void);
static void WPCINDCmdState_3rdChargeOn_du(void);
static void WPCINDCmdState_3rdChargeOn_ex(void);
static u8 WPCINDCmdState_3rdChargeOn_run(void);

static void WPCINDCmdState_2ndChargeFadeIn_en(void);
static const tSTATE* WPCINDCmdState_2ndChargeFadeIn_init(void);
static void WPCINDCmdState_2ndChargeFadeIn_du(void);
static void WPCINDCmdState_2ndChargeFadeIn_ex(void);
static u8 WPCINDCmdState_2ndChargeFadeIn_run(void);

static void WPCINDCmdState_2ndChargeOn_en(void);
static const tSTATE* WPCINDCmdState_2ndChargeOn_init(void);
static void WPCINDCmdState_2ndChargeOn_du(void);
static void WPCINDCmdState_2ndChargeOn_ex(void);
static u8 WPCINDCmdState_2ndChargeOn_run(void);

static void WPCINDCmdState_1stChargeFadeIn_en(void);
static const tSTATE* WPCINDCmdState_1stChargeFadeIn_init(void);
static void WPCINDCmdState_1stChargeFadeIn_du(void);
static void WPCINDCmdState_1stChargeFadeIn_ex(void);
static u8 WPCINDCmdState_1stChargeFadeIn_run(void);

static void WPCINDCmdState_1stChargeOn_en(void);
static const tSTATE* WPCINDCmdState_1stChargeOn_init(void);
static void WPCINDCmdState_1stChargeOn_du(void);
static void WPCINDCmdState_1stChargeOn_ex(void);
static u8 WPCINDCmdState_1stChargeOn_run(void);

static void WPCINDCmdState_Error_en(void);
static const tSTATE* WPCINDCmdState_Error_init(void);
static void WPCINDCmdState_Error_du(void);
static void WPCINDCmdState_Error_ex(void);
static u8 WPCINDCmdState_Error_run(void);

static void WPCINDCmdState_ErrorOn_en(void);
static const tSTATE* WPCINDCmdState_ErrorOn_init(void);
static void WPCINDCmdState_ErrorOn_du(void);
static void WPCINDCmdState_ErrorOn_ex(void);
static u8 WPCINDCmdState_ErrorOn_run(void);

static void WPCINDCmdState_ErrorOn_2_en(void);
static const tSTATE* WPCINDCmdState_ErrorOn_2_init(void);
static void WPCINDCmdState_ErrorOn_2_du(void);
static void WPCINDCmdState_ErrorOn_2_ex(void);
static u8 WPCINDCmdState_ErrorOn_2_run(void);

static void WPCINDCmdState_ErrorOff_en(void);
static const tSTATE* WPCINDCmdState_ErrorOff_init(void);
static void WPCINDCmdState_ErrorOff_du(void);
static void WPCINDCmdState_ErrorOff_ex(void);
static u8 WPCINDCmdState_ErrorOff_run(void);


void WPCINDCmdStateControl(void);
//void AmberSyncState(void);
//void AmberSyncIndyState(void);

static const tSTATE kWPCINDCmdState_Default =
{
	WPCINDCmdState_Default_en,
	WPCINDCmdState_Default_init,
	WPCINDCmdState_Default_du,
	WPCINDCmdState_Default_ex,
	WPCINDCmdState_Default_run,
	NULL
};

static const tSTATE kWPCINDCmdState_Charging =
{
	WPCINDCmdState_Charging_en,
	WPCINDCmdState_Charging_init,
	WPCINDCmdState_Charging_du,
	WPCINDCmdState_Charging_ex,
	WPCINDCmdState_Charging_run,
	NULL
};

/* 1 : kWPCINDCmdState_Off */
static const tSTATE kWPCINDCmdState_Off =
{
	WPCINDCmdState_Off_en,
	WPCINDCmdState_Off_init,
	WPCINDCmdState_Off_du,
	WPCINDCmdState_Off_ex,
	WPCINDCmdState_Off_run,
	&kWPCINDCmdState_Charging
};

/* 2 : kWPCINDCmdState_3rdSync */
static const tSTATE kWPCINDCmdState_3rdSync =
{
	WPCINDCmdState_3rdSync_en,
	WPCINDCmdState_3rdSync_init,
	WPCINDCmdState_3rdSync_du,
	WPCINDCmdState_3rdSync_ex,
	WPCINDCmdState_3rdSync_run,
	&kWPCINDCmdState_Charging
};
	
/* 3 : kWPCINDCmdState_2ndSync */	
static const tSTATE kWPCINDCmdState_2ndSync =
{
	WPCINDCmdState_2ndSync_en,
	WPCINDCmdState_2ndSync_init,
	WPCINDCmdState_2ndSync_du,
	WPCINDCmdState_2ndSync_ex,
	WPCINDCmdState_2ndSync_run,
	&kWPCINDCmdState_Charging
};
	
/* 4 : kWPCINDCmdState_1stSync */
static const tSTATE kWPCINDCmdState_1stSync =
{
	WPCINDCmdState_1stSync_en,
	WPCINDCmdState_1stSync_init,
	WPCINDCmdState_1stSync_du,
	WPCINDCmdState_1stSync_ex,
	WPCINDCmdState_1stSync_run,
	&kWPCINDCmdState_Charging
};
	
/* 5 : kWPCINDCmdState_ChrgFadeOut */
static const tSTATE kWPCINDCmdState_ChrgFadeOut =
{
	WPCINDCmdState_ChrgFadeOut_en,
	WPCINDCmdState_ChrgFadeOut_init,
	WPCINDCmdState_ChrgFadeOut_du,
	WPCINDCmdState_ChrgFadeOut_ex,
	WPCINDCmdState_ChrgFadeOut_run,
	&kWPCINDCmdState_Off
};

#if 0 /* TSCR-1002_WPC_AnimationIND LED Off Time Change */
static const tSTATE kWPCINDCmdState_ChrgOff =
{
	WPCINDCmdState_ChrgOff_en,
	WPCINDCmdState_ChrgOff_init,
	WPCINDCmdState_ChrgOff_du,
	WPCINDCmdState_ChrgOff_ex,
	WPCINDCmdState_ChrgOff_run,
	&kWPCINDCmdState_Off
};
#endif
static const tSTATE kWPCINDCmdState_3rdChargeFadeIn =
{
	WPCINDCmdState_3rdChargeFadeIn_en,
	WPCINDCmdState_3rdChargeFadeIn_init,
	WPCINDCmdState_3rdChargeFadeIn_du,
	WPCINDCmdState_3rdChargeFadeIn_ex,
	WPCINDCmdState_3rdChargeFadeIn_run,
	&kWPCINDCmdState_3rdSync
};
static const tSTATE kWPCINDCmdState_3rdChargeOn =
{
	WPCINDCmdState_3rdChargeOn_en,
	WPCINDCmdState_3rdChargeOn_init,
	WPCINDCmdState_3rdChargeOn_du,
	WPCINDCmdState_3rdChargeOn_ex,
	WPCINDCmdState_3rdChargeOn_run,
	&kWPCINDCmdState_3rdSync
};

static const tSTATE kWPCINDCmdState_2ndChargeFadeIn =
{
	WPCINDCmdState_2ndChargeFadeIn_en,
	WPCINDCmdState_2ndChargeFadeIn_init,
	WPCINDCmdState_2ndChargeFadeIn_du,
	WPCINDCmdState_2ndChargeFadeIn_ex,
	WPCINDCmdState_2ndChargeFadeIn_run,
	&kWPCINDCmdState_2ndSync
};
static const tSTATE kWPCINDCmdState_2ndChargeOn =
{
	WPCINDCmdState_2ndChargeOn_en,
	WPCINDCmdState_2ndChargeOn_init,
	WPCINDCmdState_2ndChargeOn_du,
	WPCINDCmdState_2ndChargeOn_ex,
	WPCINDCmdState_2ndChargeOn_run,
	&kWPCINDCmdState_2ndSync
};

static const tSTATE kWPCINDCmdState_1stChargeFadeIn =
{
	WPCINDCmdState_1stChargeFadeIn_en,
	WPCINDCmdState_1stChargeFadeIn_init,
	WPCINDCmdState_1stChargeFadeIn_du,
	WPCINDCmdState_1stChargeFadeIn_ex,
	WPCINDCmdState_1stChargeFadeIn_run,
	&kWPCINDCmdState_1stSync
};
static const tSTATE kWPCINDCmdState_1stChargeOn =
{
	WPCINDCmdState_1stChargeOn_en,
	WPCINDCmdState_1stChargeOn_init,
	WPCINDCmdState_1stChargeOn_du,
	WPCINDCmdState_1stChargeOn_ex,
	WPCINDCmdState_1stChargeOn_run,
	&kWPCINDCmdState_1stSync
};

static const tSTATE kWPCINDCmdState_Error =
{
	WPCINDCmdState_Error_en,
	WPCINDCmdState_Error_init,
	WPCINDCmdState_Error_du,
	WPCINDCmdState_Error_ex,
	WPCINDCmdState_Error_run,
	NULL
};

static const tSTATE kWPCINDCmdState_ErrorOn =
{
	WPCINDCmdState_ErrorOn_en,
	WPCINDCmdState_ErrorOn_init,
	WPCINDCmdState_ErrorOn_du,
	WPCINDCmdState_ErrorOn_ex,
	WPCINDCmdState_ErrorOn_run,
	&kWPCINDCmdState_Error
};

static const tSTATE kWPCINDCmdState_ErrorOn_2 =
{
	WPCINDCmdState_ErrorOn_2_en,
	WPCINDCmdState_ErrorOn_2_init,
	WPCINDCmdState_ErrorOn_2_du,
	WPCINDCmdState_ErrorOn_2_ex,
	WPCINDCmdState_ErrorOn_2_run,
	&kWPCINDCmdState_Error
};

static const tSTATE kWPCINDCmdState_ErrorOff =
{
	WPCINDCmdState_ErrorOff_en,
	WPCINDCmdState_ErrorOff_init,
	WPCINDCmdState_ErrorOff_du,
	WPCINDCmdState_ErrorOff_ex,
	WPCINDCmdState_ErrorOff_run,
	&kWPCINDCmdState_Error
};


/******************************************************************************
	Define Constant and Macro
*******************************************************************************/


typedef enum
{
	kWPCINDCMDSTATE_INIT=0,
	kWPCINDCMDSTATE_OPERATING
} e_WPCINDCMDSTATE;




/******************************************************************************
	Declare Variables
*******************************************************************************/
extern tTimer8	Timer_AmberINDBlk;

static tTimer16 Timer_INDPhaseState = {Off, 0u};

static tSTATE *stateCUR = NULL;


/******************************************************************************
	Define Functions
*******************************************************************************/


static void WPCINDCmdState_Default_en(void)
{
	SetOutput(kb_WPCIndCmdState, WPCIndCmdState_Default);
}


static const tSTATE* WPCINDCmdState_Default_init(void)
{
	return NULL;
}


static void WPCINDCmdState_Default_du(void)
{
	/* Do Nothing */
}


static void WPCINDCmdState_Default_ex(void)
{
	/* Do Nothing */
}


static u8 WPCINDCmdState_Default_run(void)
{
	u8 ret = 0u;


	if (IsChgEvt(kC_WPC_IndSyncVal,(u8)kWPCIndSyncVal_3rdSync))
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_3rdChargeOn);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_3rdChargeOn);
		ret = 1u;
	}
	else if(IsChgEvt(kC_WPC_IndSyncVal, (u8)kWPCIndSyncVal_ErrorOn))
	{ /* 2 */
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_Error);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_Error);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}


static void WPCINDCmdState_Charging_en(void)
{
	/* MISRA */
}


static const tSTATE* WPCINDCmdState_Charging_init(void)
{	
	tSTATE *ret_state = NULL;
	
	stateCUR = &kWPCINDCmdState_Off;
	ret_state = &kWPCINDCmdState_Off;
		
	return ret_state;
}


static void WPCINDCmdState_Charging_du(void)
{
	/* Do Nothing */
}


static void WPCINDCmdState_Charging_ex(void)
{
	/* Do Nothing */
}


static u8 WPCINDCmdState_Charging_run(void)
{
	u8 ret = 0u;
	
	if (IsChgEvt(kC_WPC_IndSyncVal, (u8)WPCIndCmdState_Default))
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_Default);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_Default);
		ret = 1u;
	}
	else if (IsChgEvt(kC_WPC_IndSyncVal, (u8)kWPCIndSyncVal_ErrorOn))
	{ /* 2 */
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_Error);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_Error);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}

static void WPCINDCmdState_Off_en(void)
{
	/* Do Nothing */
}


static const tSTATE* WPCINDCmdState_Off_init(void)
{
	tSTATE *ret_state = NULL;
	
	stateCUR = &kWPCINDCmdState_ChrgFadeOut;
	ret_state = &kWPCINDCmdState_ChrgFadeOut;
		
	return ret_state;
}


static void WPCINDCmdState_Off_du(void)
{
	/* Do Nothing */
}


static void WPCINDCmdState_Off_ex(void)
{
	/* Do Nothing */
}


static u8 WPCINDCmdState_Off_run(void)
{
	u8 ret = 0u;
	
	if (IsChgEvt(kC_WPC_IndSyncVal, (u8)kWPCIndSyncVal_1stSync))
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_1stSync);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_1stSync);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}

static void WPCINDCmdState_3rdSync_en(void)
{
	/* Do Nothing */
}


static const tSTATE* WPCINDCmdState_3rdSync_init(void)
{
	tSTATE *ret_state = NULL;
	
	stateCUR = &kWPCINDCmdState_3rdChargeFadeIn;
	ret_state = &kWPCINDCmdState_3rdChargeFadeIn;
		
	return ret_state;
}


static void WPCINDCmdState_3rdSync_du(void)
{
	/* Do Nothing */
}


static void WPCINDCmdState_3rdSync_ex(void)
{
	/* Do Nothing */
}


static u8 WPCINDCmdState_3rdSync_run(void)
{
	u8 ret = 0u;

	if (IsChgEvt(kC_WPC_IndSyncVal, (u8)kWPCIndSyncVal_Off))
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_Off);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_Off);
		ret = 1u;
	}
	else if (IsChgEvt(kC_WPC_IndSyncVal, (u8)kWPCIndSyncVal_2ndSync))
	{ /* 2 */
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_2ndSync);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_2ndSync);
		ret = 1u;
	}
	else if (IsChgEvt(kC_WPC_IndSyncVal, (u8)kWPCIndSyncVal_1stSync))
	{ /* 3 */
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_1stSync);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_1stSync);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}


static void WPCINDCmdState_2ndSync_en(void)
{
	/* Do Nothing */
}


static const tSTATE* WPCINDCmdState_2ndSync_init(void)
{
	tSTATE *ret_state = NULL;
	
	stateCUR = &kWPCINDCmdState_2ndChargeFadeIn;
	ret_state = &kWPCINDCmdState_2ndChargeFadeIn;
		
	return ret_state;
}


static void WPCINDCmdState_2ndSync_du(void)
{
	/* Do Nothing */
}


static void WPCINDCmdState_2ndSync_ex(void)
{
	/* Do Nothing */
}


static u8 WPCINDCmdState_2ndSync_run(void)
{
	u8 ret = 0u;

	if (IsChgEvt(kC_WPC_IndSyncVal, (u8)kWPCIndSyncVal_Off))
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_Off);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_Off);
		ret = 1u;
	}
	else if (IsChgEvt(kC_WPC_IndSyncVal, (u8)kWPCIndSyncVal_3rdSync))
	{ /* 2 */
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_3rdSync);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_3rdSync);
		ret = 1u;
	}
	else if (IsChgEvt(kC_WPC_IndSyncVal, (u8)kWPCIndSyncVal_1stSync))
	{ /* 3 */
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_1stSync);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_1stSync);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}

static void WPCINDCmdState_1stSync_en(void)
{
	/* Do Nothing */
}


static const tSTATE* WPCINDCmdState_1stSync_init(void)
{
	tSTATE *ret_state = NULL;
	
	stateCUR = &kWPCINDCmdState_1stChargeFadeIn;
	ret_state = &kWPCINDCmdState_1stChargeFadeIn;
		
	return ret_state;
}


static void WPCINDCmdState_1stSync_du(void)
{
	/* Do Nothing */
}


static void WPCINDCmdState_1stSync_ex(void)
{
	/* Do Nothing */
}


static u8 WPCINDCmdState_1stSync_run(void)
{
	u8 ret = 0u;

	if (IsChgEvt(kC_WPC_IndSyncVal, (u8)kWPCIndSyncVal_Off))
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_Off);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_Off);
		ret = 1u;
	}
	else if (IsChgEvt(kC_WPC_IndSyncVal, (u8)kWPCIndSyncVal_2ndSync))
	{ /* 2 */
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_2ndSync);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_2ndSync);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}

/* 5 : kRWPCINDAnimationPreNone */
static void WPCINDCmdState_ChrgFadeOut_en(void)
{
	StartTimer(Timer_INDPhaseState);
	SetX(kb_WPCIndCmdState, (u8)WPCIndCmdState_ChrgFadeOut);
}


static const tSTATE* WPCINDCmdState_ChrgFadeOut_init(void)
{
	return NULL;
}


static void WPCINDCmdState_ChrgFadeOut_du(void)
{
	CancelTimer(Timer_INDPhaseState);
}


static void WPCINDCmdState_ChrgFadeOut_ex(void)
{
	/* Do Nothing */
}


static u8 WPCINDCmdState_ChrgFadeOut_run(void)
{
#if 0	/* TSCR-1002_WPC_AnimationIND LED Off Time Change */
	u8 ret = 0u;

	if (Timer_INDPhaseState.time >= Par_INDPhaseStateTime)
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_ChrgOff);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_ChrgOff);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
#else
	return 0;
#endif
}

#if 0 /* TSCR-1002_WPC_AnimationIND LED Off Time Change */
static void WPCINDCmdState_ChrgOff_en(void)
{
	StartTimer(Timer_INDPhaseState);
	SetX(kb_WPCIndCmdState, (u8)WPCIndCmdState_ChrgOff);
}


static const tSTATE* WPCINDCmdState_ChrgOff_init(void)
{
	return NULL;
}


static void WPCINDCmdState_ChrgOff_du(void)
{
	/* Do Nothing */
}


static void WPCINDCmdState_ChrgOff_ex(void)
{
	CancelTimer(Timer_INDPhaseState);
}


static u8 WPCINDCmdState_ChrgOff_run(void)
{
	return 0;
}
#endif

static void WPCINDCmdState_3rdChargeFadeIn_en(void)
{
	StartTimer(Timer_INDPhaseState);
	SetX(kb_WPCIndCmdState, (u8)WPCIndCmdState_3rdChrgFadeIn);
}


static const tSTATE* WPCINDCmdState_3rdChargeFadeIn_init(void)
{
	return NULL;
}


static void WPCINDCmdState_3rdChargeFadeIn_du(void)
{
	/* Do Nothing */
}


static void WPCINDCmdState_3rdChargeFadeIn_ex(void)
{
	CancelTimer(Timer_INDPhaseState);
}


static u8 WPCINDCmdState_3rdChargeFadeIn_run(void)
{
	u8 ret = 0u;
	
	if(Timer_INDPhaseState.time >= Par_INDPhaseStateTime)
	{ /* 1 */			
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_3rdChargeOn);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_3rdChargeOn);
		ret = 1u;
	}
	return ret;
}


static void WPCINDCmdState_3rdChargeOn_en(void)
{
	StartTimer(Timer_INDPhaseState);
	SetX(kb_WPCIndCmdState, (u8)WPCIndCmdState_3rdChrgOn);
	
}


static const tSTATE* WPCINDCmdState_3rdChargeOn_init(void)
{
	return NULL;
}


static void WPCINDCmdState_3rdChargeOn_du(void)
{
	/* Do Nothing */
}


static void WPCINDCmdState_3rdChargeOn_ex(void)
{
	CancelTimer(Timer_INDPhaseState);
}


static u8 WPCINDCmdState_3rdChargeOn_run(void)
{
	return 0;
}

static void WPCINDCmdState_2ndChargeFadeIn_en(void)
{
	StartTimer(Timer_INDPhaseState);
	SetX(kb_WPCIndCmdState, (u8)WPCIndCmdState_2ndChrgFadeIn);
}


static const tSTATE* WPCINDCmdState_2ndChargeFadeIn_init(void)
{
	return NULL;
}


static void WPCINDCmdState_2ndChargeFadeIn_du(void)
{
	/* Do Nothing */
}


static void WPCINDCmdState_2ndChargeFadeIn_ex(void)
{
	CancelTimer(Timer_INDPhaseState);
}


static u8 WPCINDCmdState_2ndChargeFadeIn_run(void)
{
	u8 ret = 0u;
	
	if(Timer_INDPhaseState.time >= Par_INDPhaseStateTime)
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_2ndChargeOn);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_2ndChargeOn);
		ret = 1u;
	}
	return ret;
}

static void WPCINDCmdState_2ndChargeOn_en(void)
{
	StartTimer(Timer_INDPhaseState);
	SetX(kb_WPCIndCmdState, (u8)WPCIndCmdState_2ndChrgOn);
}


static const tSTATE* WPCINDCmdState_2ndChargeOn_init(void)
{
	return NULL;
}


static void WPCINDCmdState_2ndChargeOn_du(void)
{
	/* Do Nothing */
}


static void WPCINDCmdState_2ndChargeOn_ex(void)
{
	CancelTimer(Timer_INDPhaseState);
}


static u8 WPCINDCmdState_2ndChargeOn_run(void)
{
	return 0;
}


static void WPCINDCmdState_1stChargeFadeIn_en(void)
{
	StartTimer(Timer_INDPhaseState);
	SetX(kb_WPCIndCmdState, (u8)WPCIndCmdState_1stChrgFadeIn);
}


static const tSTATE* WPCINDCmdState_1stChargeFadeIn_init(void)
{
	return NULL;
}


static void WPCINDCmdState_1stChargeFadeIn_du(void)
{
	/* Do Nothing */
}


static void WPCINDCmdState_1stChargeFadeIn_ex(void)
{
	CancelTimer(Timer_INDPhaseState);
}


static u8 WPCINDCmdState_1stChargeFadeIn_run(void)
{
	u8 ret = 0u;
	
	if(Timer_INDPhaseState.time >= Par_INDPhaseStateTime)
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_1stChargeOn);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_1stChargeOn);
		ret = 1u;
	}
	return ret;
}


static void WPCINDCmdState_1stChargeOn_en(void)
{
	StartTimer(Timer_INDPhaseState);
	SetX(kb_WPCIndCmdState, (u8)WPCIndCmdState_1stChrgOn);
}


static const tSTATE* WPCINDCmdState_1stChargeOn_init(void)
{
	return NULL;
}


static void WPCINDCmdState_1stChargeOn_du(void)
{
	/* Do Nothing */
}


static void WPCINDCmdState_1stChargeOn_ex(void)
{
	CancelTimer(Timer_INDPhaseState);
}


static u8 WPCINDCmdState_1stChargeOn_run(void)
{
	return 0;
}


static void WPCINDCmdState_Error_en(void)
{
	/* Do Nothing */
}


static const tSTATE* WPCINDCmdState_Error_init(void)
{
	tSTATE *ret_state = NULL;
	
	stateCUR = &kWPCINDCmdState_ErrorOn;
	ret_state = &kWPCINDCmdState_ErrorOn;
		
	return ret_state;
}


static void WPCINDCmdState_Error_du(void)
{
	/* Do Nothing */
}


static void WPCINDCmdState_Error_ex(void)
{
	/* Do Nothing */
}


static u8 WPCINDCmdState_Error_run(void)
{
	u8 ret = 0u;
	
	if(IsChgEvt(kC_WPC_IndSyncVal, (u8)WPCIndCmdState_Default)) 
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_Default);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_Default);
		ret = 1u;
	}
	else if(IsChgEvt(kC_WPC_IndSyncVal, (u8)kWPCIndSyncVal_3rdSync))
	{
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_3rdChargeOn);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_3rdChargeOn);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}


static void WPCINDCmdState_ErrorOn_en(void)
{
	StartTimer(Timer_INDPhaseState);
	SetX(kb_WPCIndCmdState, (u8)WPCIndCmdState_ErrorFadeIn);
}


static const tSTATE* WPCINDCmdState_ErrorOn_init(void)
{
	return NULL;
}


static void WPCINDCmdState_ErrorOn_du(void)
{
	/* Do Nothing */
}


static void WPCINDCmdState_ErrorOn_ex(void)
{
	CancelTimer(Timer_INDPhaseState);
}


static u8 WPCINDCmdState_ErrorOn_run(void)
{
	u8 ret = 0u;

	if(IsChgEvt(kC_WPC_IndSyncVal, (u8)kWPCIndSyncVal_ErrorOff))
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_ErrorOff);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_ErrorOff);
		ret = 1u;
	}
	else if(Timer_INDPhaseState.time >= Par_INDPhaseStateTime)
	{ /* 2 */
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_ErrorOn_2);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_ErrorOn_2);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}

static void WPCINDCmdState_ErrorOn_2_en(void)
{
	StartTimer(Timer_INDPhaseState);
	SetX(kb_WPCIndCmdState, (u8)WPCIndCmdState_ErrorOn);
}


static const tSTATE* WPCINDCmdState_ErrorOn_2_init(void)
{
	return NULL;
}


static void WPCINDCmdState_ErrorOn_2_du(void)
{
	/* Do Nothing */
}


static void WPCINDCmdState_ErrorOn_2_ex(void)
{
	/* Do Nothing */
}


static u8 WPCINDCmdState_ErrorOn_2_run(void)
{
	u8 ret = 0u;
	
	if(IsChgEvt(kC_WPC_IndSyncVal, (u8)kWPCIndSyncVal_ErrorOff))
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_ErrorOff);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_ErrorOff);
		ret = 1u;
	}
	return ret;
}


static void WPCINDCmdState_ErrorOff_en(void)
{
	StartTimer(Timer_INDPhaseState);
	SetX(kb_WPCIndCmdState, (u8)WPCIndCmdState_ErrorFadeOut);
}


static const tSTATE* WPCINDCmdState_ErrorOff_init(void)
{
	return NULL;
}


static void WPCINDCmdState_ErrorOff_du(void)
{
	/* Do Nothing */
}


static void WPCINDCmdState_ErrorOff_ex(void)
{
	CancelTimer(Timer_INDPhaseState);
}


static u8 WPCINDCmdState_ErrorOff_run(void)
{
	u8 ret = 0u;
	
	if(IsChgEvt(kC_WPC_IndSyncVal, (u8)kWPCIndSyncVal_ErrorOn))
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kWPCINDCmdState_ErrorOn);
		stateCUR = transition(stateCUR, &kWPCINDCmdState_ErrorOn);
		ret = 1u;
	}
	return ret;
}



void WPCINDCmdStateControl(void)
{
	static e_WPCINDCMDSTATE sts_WPCINDCMDSTATE = kWPCINDCMDSTATE_INIT;

	UpTimer16(Timer_INDPhaseState);
	
	//AmberSyncState();
	//AmberSyncIndyState();
	
	switch(sts_WPCINDCMDSTATE)
	{
		case kWPCINDCMDSTATE_INIT:
			stateCUR = &kWPCINDCmdState_Default;
			stateCUR = transition(stateCUR, &kWPCINDCmdState_Default);
			sts_WPCINDCMDSTATE = kWPCINDCMDSTATE_OPERATING;
			break;

		case kWPCINDCMDSTATE_OPERATING:
			CurrentRun(stateCUR);
			break;

		default:
			/* MISRA */
			break;
	}
}

#if 0
void AmberSyncState(void)
{
	static e_AmberSyncStateControl sts_AmberSyncStateControl = SyncTrigger_Init;
	
	switch(sts_AmberSyncStateControl)
	{
		case SyncTrigger_Init:
			SetX(kb_CmdAmberSync, Off);
			
			sts_AmberSyncStateControl = SyncTrigger_Off;
			break;
			
		case SyncTrigger_Off:		

			if(IsChgEvt(kb_RWPCIndCmdState, RWPCIndCmdState_ErrorFadeIn) ||
			   IsChgEvt(kb_RWPCIndCmdState, RWPCIndCmdState_ErrorFadeOut))
			break;
		
		case SyncTrigger_On:
#if 1
			if((IsChgEvt(kb_RWPCIndCmdState, RWPCIndCmdState_ErrorOn)) ||
			   (IsChgEvt(kb_RWPCIndCmdState, RWPCIndCmdState_ChrgFadeOut)) ||
			   (IsChgEvt(kb_RWPCIndCmdState, RWPCIndCmdState_3rdChrgOn)) ||
			   (IsChgEvt(kb_RWPCIndCmdState, RWPCIndCmdState_3rdChrgFadeIn)) ||
			   (IsChgEvt(kb_RWPCIndCmdState, RWPCIndCmdState_2ndChrgOn)) ||
			   (IsChgEvt(kb_RWPCIndCmdState, RWPCIndCmdState_2ndChrgFadeIn)) ||
			   (IsChgEvt(kb_RWPCIndCmdState, RWPCIndCmdState_1stChrgOn)) ||
			   (IsChgEvt(kb_RWPCIndCmdState, RWPCIndCmdState_1stChrgFadeIn)) ||
			   (IsChgEvt(kb_RWPCIndCmdState, RWPCIndCmdState_ChrgOff)) ||
			   (IsChgEvt(kb_RWPCIndCmdState, RWPCIndCmdState_Default)))
#else
			//if (IsChgEvt(kb_WPCIndCmdState, WPCIndCmdState_Default))

			if((IsChgEvt(kC_WPC_IndSyncVal, kWPCIndSyncVal_3rdSync)) ||
			    (IsChgEvt(kC_WPC_IndSyncVal, kWPCIndSyncVal_2ndSync)) ||
			    (IsChgEvt(kC_WPC_IndSyncVal, kWPCIndSyncVal_1stSync)) ||
			    (IsChgEvt(kC_WPC_IndSyncVal, kWPCIndSyncVal_Off)) ||
			    (IsChgEvt(kC_WPC_IndSyncVal, kWPCIndSyncVal_Default)))
		    
#endif
			{
				SetX(kb_CmdAmberSync, Off);
				sts_AmberSyncStateControl = SyncTrigger_Off;				
			}
			break;
		default:
			sts_AmberSyncStateControl = SyncTrigger_Init;
			break;
	}
}

void AmberSyncIndyState(void)
{
	static e_AmberSyncIndyStateControl sts_AmberSyncIndyStateControl = SyncIndyTrigger_Init;
	
	switch(sts_AmberSyncIndyStateControl)
	{
		case SyncIndyTrigger_Init:
			SetX(kb_SyncAmber, Off);
			
			sts_AmberSyncIndyStateControl = SyncIndyTrigger_Off;
			break;
		
		case SyncIndyTrigger_Off:
			if(IsChgEvt(kb_BlinkState, Blink_State_On))
			{
				SetX(kb_SyncAmber, On);
				
				sts_AmberSyncIndyStateControl = SyncIndyTrigger_On;
			}
			break;
		
		case SyncIndyTrigger_On:
			if((IsChgEvt(kb_CmdAmberSync, Off)) ||
			   (IsChgEvt(kb_BlinkState, Blink_State_Complete)))
			{
				ClrEvt(kb_CmdAmberSync);
				SetX(kb_SyncAmber, Off)
				Pwm_IND_Stop(Amber);
				sts_AmberSyncIndyStateControl = SyncIndyTrigger_Off;
			}
			break;
		
		default:
			sts_AmberSyncIndyStateControl = SyncIndyTrigger_Init;
			break;
	}
}

#endif

