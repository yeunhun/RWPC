/******************************************************************************
 * Project      	: 	KA4 PE WPC
 * File Name    	: 	RWPCINDAnimationcontrol.c
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
static void RWPCINDAnimationInit_en(void);
static const tSTATE* RWPCINDAnimationInit_init(void);
static void RWPCINDAnimationInit_du(void);
static void RWPCINDAnimationInit_ex(void);
static u8 RWPCINDAnimationInit_run(void);

static void RWPCINDAnimationCharging_en(void);
static const tSTATE* RWPCINDAnimationCharging_init(void);
static void RWPCINDAnimationCharging_du(void);
static void RWPCINDAnimationCharging_ex(void);
static u8 RWPCINDAnimationCharging_run(void);

static void RWPCINDAnimationPreNone_en(void);
static const tSTATE* RWPCINDAnimationPreNone_init(void);
static void RWPCINDAnimationPreNone_du(void);
static void RWPCINDAnimationPreNone_ex(void);
static u8 RWPCINDAnimationPreNone_run(void);

static void RWPCINDAnimationPreWPC2WPC_en(void);
static const tSTATE* RWPCINDAnimationPreWPC2WPC_init(void);
static void RWPCINDAnimationPreWPC2WPC_du(void);
static void RWPCINDAnimationPreWPC2WPC_ex(void);
static u8 RWPCINDAnimationPreWPC2WPC_run(void);

static void RWPCINDAnimationPreWPCWPC2_en(void);
static const tSTATE* RWPCINDAnimationPreWPCWPC2_init(void);
static void RWPCINDAnimationPreWPCWPC2_du(void);
static void RWPCINDAnimationPreWPCWPC2_ex(void);
static u8 RWPCINDAnimationPreWPCWPC2_run(void);

static void RWPCINDAnimationPreWPC_en(void);
static const tSTATE* RWPCINDAnimationPreWPC_init(void);
static void RWPCINDAnimationPreWPC_du(void);
static void RWPCINDAnimationPreWPC_ex(void);
static u8 RWPCINDAnimationPreWPC_run(void);

static void RWPCINDAnimationPreWPC2_en(void);
static const tSTATE* RWPCINDAnimationPreWPC2_init(void);
static void RWPCINDAnimationPreWPC2_du(void);
static void RWPCINDAnimationPreWPC2_ex(void);
static u8 RWPCINDAnimationPreWPC2_run(void);

static void RWPCINDAnimationActive_en(void);
static const tSTATE* RWPCINDAnimationActive_init(void);
static void RWPCINDAnimationActive_du(void);
static void RWPCINDAnimationActive_ex(void);
static u8 RWPCINDAnimationActive_run(void);

static void RWPCINDAnimationOff_en(void);
static const tSTATE* RWPCINDAnimationOff_init(void);
static void RWPCINDAnimationOff_du(void);
static void RWPCINDAnimationOff_ex(void);
static u8 RWPCINDAnimationOff_run(void);

static void RWPCINDAnimation1stSync_en(void);
static const tSTATE* RWPCINDAnimation1stSync_init(void);
static void RWPCINDAnimation1stSync_du(void);
static void RWPCINDAnimation1stSync_ex(void);
static u8 RWPCINDAnimation1stSync_run(void);

static void RWPCINDAnimation3rdSync_en(void);
static const tSTATE* RWPCINDAnimation3rdSync_init(void);
static void RWPCINDAnimation3rdSync_du(void);
static void RWPCINDAnimation3rdSync_ex(void);
static u8 RWPCINDAnimation3rdSync_run(void);

static void RWPCINDAnimation2ndSync_en(void);
static const tSTATE* RWPCINDAnimation2ndSync_init(void);
static void RWPCINDAnimation2ndSync_du(void);
static void RWPCINDAnimation2ndSync_ex(void);
static u8 RWPCINDAnimation2ndSync_run(void);

#if 0 /*	TSCR-1002_WPC_AnimationIND LED Off Time Change */
static void RWPCINDAnimationOffHold_en(void);
static const tSTATE* RWPCINDAnimationOffHold_init(void);
static void RWPCINDAnimationOffHold_du(void);
static void RWPCINDAnimationOffHold_ex(void);
static u8 RWPCINDAnimationOffHold_run(void);
#endif

static void RWPCINDAnimationOffFadeOut_en(void);
static const tSTATE* RWPCINDAnimationOffFadeOut_init(void);
static void RWPCINDAnimationOffFadeOut_du(void);
static void RWPCINDAnimationOffFadeOut_ex(void);
static u8 RWPCINDAnimationOffFadeOut_run(void);

static void RWPCINDAnimationCharging1stOn_en(void);
static const tSTATE* RWPCINDAnimationCharging1stOn_init(void);
static void RWPCINDAnimationCharging1stOn_du(void);
static void RWPCINDAnimationCharging1stOn_ex(void);
static u8 RWPCINDAnimationCharging1stOn_run(void);

static void RWPCINDAnimationCharging1stFadeIn_en(void);
static const tSTATE* RWPCINDAnimationCharging1stFadeIn_init(void);
static void RWPCINDAnimationCharging1stFadeIn_du(void);
static void RWPCINDAnimationCharging1stFadeIn_ex(void);
static u8 RWPCINDAnimationCharging1stFadeIn_run(void);

static void RWPCINDAnimationCharging2ndOn_en(void);
static const tSTATE* RWPCINDAnimationCharging2ndOn_init(void);
static void RWPCINDAnimationCharging2ndOn_du(void);
static void RWPCINDAnimationCharging2ndOn_ex(void);
static u8 RWPCINDAnimationCharging2ndOn_run(void);

static void RWPCINDAnimationCharging2ndFadeIn_en(void);
static const tSTATE* RWPCINDAnimationCharging2ndFadeIn_init(void);
static void RWPCINDAnimationCharging2ndFadeIn_du(void);
static void RWPCINDAnimationCharging2ndFadeIn_ex(void);
static u8 RWPCINDAnimationCharging2ndFadeIn_run(void);

static void RWPCINDAnimationCharging3rdOn_en(void);
static const tSTATE* RWPCINDAnimationCharging3rdOn_init(void);
static void RWPCINDAnimationCharging3rdOn_du(void);
static void RWPCINDAnimationCharging3rdOn_ex(void);
static u8 RWPCINDAnimationCharging3rdOn_run(void);

static void RWPCINDAnimationCharging3rdFadeIn_en(void);
static const tSTATE* RWPCINDAnimationCharging3rdFadeIn_init(void);
static void RWPCINDAnimationCharging3rdFadeIn_du(void);
static void RWPCINDAnimationCharging3rdFadeIn_ex(void);
static u8 RWPCINDAnimationCharging3rdFadeIn_run(void);

static void RWPCINDAnimationError_en(void);
static const tSTATE* RWPCINDAnimationError_init(void);
static void RWPCINDAnimationError_du(void);
static void RWPCINDAnimationError_ex(void);
static u8 RWPCINDAnimationError_run(void);

static void RWPCINDAnimationErrorPreNone_en(void);
static const tSTATE* RWPCINDAnimationErrorPreNone_init(void);
static void RWPCINDAnimationErrorPreNone_du(void);
static void	RWPCINDAnimationErrorPreNone_ex(void);
static u8 RWPCINDAnimationErrorPreNone_run(void);


static void RWPCINDAnimationErrorPreWPC2WPC_en(void);
static const tSTATE* RWPCINDAnimationErrorPreWPC2WPC_init(void);
static void	RWPCINDAnimationErrorPreWPC2WPC_du(void);
static void	RWPCINDAnimationErrorPreWPC2WPC_ex(void);
static u8 RWPCINDAnimationErrorPreWPC2WPC_run(void);
	
static void RWPCINDAnimationErrorPreWPCWPC2_en(void);
static const tSTATE* RWPCINDAnimationErrorPreWPCWPC2_init(void);
static void	RWPCINDAnimationErrorPreWPCWPC2_du(void);
static void	RWPCINDAnimationErrorPreWPCWPC2_ex(void);
static u8 RWPCINDAnimationErrorPreWPCWPC2_run(void);
	
static void	RWPCINDAnimationErrorPreWPC_en(void);
static const tSTATE* RWPCINDAnimationErrorPreWPC_init(void);
static void	RWPCINDAnimationErrorPreWPC_du(void);
static void	RWPCINDAnimationErrorPreWPC_ex(void);
static u8 RWPCINDAnimationErrorPreWPC_run(void);

static void	RWPCINDAnimationErrorPreWPC2_en(void);
static const tSTATE* RWPCINDAnimationErrorPreWPC2_init(void);
static void	RWPCINDAnimationErrorPreWPC2_du(void);
static void	RWPCINDAnimationErrorPreWPC2_ex(void);
static u8 RWPCINDAnimationErrorPreWPC2_run(void);

#if 0
static void RWPCINDAnimationErrorActive_en(void);
static const tSTATE* RWPCINDAnimationErrorActive_init(void);
static void RWPCINDAnimationErrorActive_du(void);
static void RWPCINDAnimationErrorActive_ex(void);
static u8 RWPCINDAnimationErrorActive_run(void);
#endif 

static void RWPCINDAnimationErrorOff_en(void);
static const tSTATE* RWPCINDAnimationErrorOff_init(void);
static void RWPCINDAnimationErrorOff_du(void);
static void RWPCINDAnimationErrorOff_ex(void);
static u8 RWPCINDAnimationErrorOff_run(void);

static void RWPCINDAnimationErrorOn_en(void);
static const tSTATE* RWPCINDAnimationErrorOn_init(void);
static void RWPCINDAnimationErrorOn_du(void);
static void RWPCINDAnimationErrorOn_ex(void);
static u8 RWPCINDAnimationErrorOn_run(void);

void RWPCINDAnimationControl(void);

static void INDAnimationPriority(void);
static void INDAnimationWPC2Priority(void);
static void INDAnimationWPCPriority(void);
void AmberSyncState(void);
void AmberSyncIndyState(void);

void Function_INDErrorOnOut(void);

//static void Function_AniLEDErrorBlink(void);


static const tSTATE kRWPCINDAnimationInit =
{
	RWPCINDAnimationInit_en,
	RWPCINDAnimationInit_init,
	RWPCINDAnimationInit_du,
	RWPCINDAnimationInit_ex,
	RWPCINDAnimationInit_run,
	NULL
};

static const tSTATE kRWPCINDAnimationCharging =
{
	RWPCINDAnimationCharging_en,
	RWPCINDAnimationCharging_init,
	RWPCINDAnimationCharging_du,
	RWPCINDAnimationCharging_ex,
	RWPCINDAnimationCharging_run,
	NULL
};

static const tSTATE kRWPCINDAnimationPreNone =
{/* 5 */
	RWPCINDAnimationPreNone_en,
	RWPCINDAnimationPreNone_init,
	RWPCINDAnimationPreNone_du,
	RWPCINDAnimationPreNone_ex,
	RWPCINDAnimationPreNone_run,
	&kRWPCINDAnimationCharging
};
static const tSTATE kRWPCINDAnimationPreWPC2WPC =
{/* 3 */
	RWPCINDAnimationPreWPC2WPC_en,
	RWPCINDAnimationPreWPC2WPC_init,
	RWPCINDAnimationPreWPC2WPC_du,
	RWPCINDAnimationPreWPC2WPC_ex,
	RWPCINDAnimationPreWPC2WPC_run,
	&kRWPCINDAnimationCharging
};
static const tSTATE kRWPCINDAnimationPreWPCWPC2 =
{/* 4 */
	RWPCINDAnimationPreWPCWPC2_en,
	RWPCINDAnimationPreWPCWPC2_init,
	RWPCINDAnimationPreWPCWPC2_du,
	RWPCINDAnimationPreWPCWPC2_ex,
	RWPCINDAnimationPreWPCWPC2_run,
	&kRWPCINDAnimationCharging
};
static const tSTATE kRWPCINDAnimationPreWPC =
{/* 1 */
	RWPCINDAnimationPreWPC_en,
	RWPCINDAnimationPreWPC_init,
	RWPCINDAnimationPreWPC_du,
	RWPCINDAnimationPreWPC_ex,
	RWPCINDAnimationPreWPC_run,
	&kRWPCINDAnimationCharging
};
static const tSTATE kRWPCINDAnimationPreWPC2 =
{/* 2 */
	RWPCINDAnimationPreWPC2_en,
	RWPCINDAnimationPreWPC2_init,
	RWPCINDAnimationPreWPC2_du,
	RWPCINDAnimationPreWPC2_ex,
	RWPCINDAnimationPreWPC2_run,
	&kRWPCINDAnimationCharging
};
static const tSTATE kRWPCINDAnimationActive =
{
	RWPCINDAnimationActive_en,
	RWPCINDAnimationActive_init,
	RWPCINDAnimationActive_du,
	RWPCINDAnimationActive_ex,
	RWPCINDAnimationActive_run,
	&kRWPCINDAnimationCharging
};
static const tSTATE kRWPCINDAnimationOff =
{
	RWPCINDAnimationOff_en,
	RWPCINDAnimationOff_init,
	RWPCINDAnimationOff_du,
	RWPCINDAnimationOff_ex,
	RWPCINDAnimationOff_run,
	&kRWPCINDAnimationActive
};
static const tSTATE kRWPCINDAnimation1stSync =
{
	RWPCINDAnimation1stSync_en,
	RWPCINDAnimation1stSync_init,
	RWPCINDAnimation1stSync_du,
	RWPCINDAnimation1stSync_ex,
	RWPCINDAnimation1stSync_run,
	&kRWPCINDAnimationActive
};
static const tSTATE kRWPCINDAnimation3rdSync =
{
	RWPCINDAnimation3rdSync_en,
	RWPCINDAnimation3rdSync_init,
	RWPCINDAnimation3rdSync_du,
	RWPCINDAnimation3rdSync_ex,
	RWPCINDAnimation3rdSync_run,
	&kRWPCINDAnimationActive
};
static const tSTATE kRWPCINDAnimation2ndSync =
{
	RWPCINDAnimation2ndSync_en,
	RWPCINDAnimation2ndSync_init,
	RWPCINDAnimation2ndSync_du,
	RWPCINDAnimation2ndSync_ex,
	RWPCINDAnimation2ndSync_run,
	&kRWPCINDAnimationActive
};

#if 0	/*	TSCR-1002_WPC_AnimationIND LED Off Time Change */
static const tSTATE kRWPCINDAnimationOffHold =
{
	RWPCINDAnimationOffHold_en,
	RWPCINDAnimationOffHold_init,
	RWPCINDAnimationOffHold_du,
	RWPCINDAnimationOffHold_ex,
	RWPCINDAnimationOffHold_run,
	&kRWPCINDAnimationOff
};
#endif 
static const tSTATE kRWPCINDAnimationOffFadeOut =
{
	RWPCINDAnimationOffFadeOut_en,
	RWPCINDAnimationOffFadeOut_init,
	RWPCINDAnimationOffFadeOut_du,
	RWPCINDAnimationOffFadeOut_ex,
	RWPCINDAnimationOffFadeOut_run,
	&kRWPCINDAnimationOff
};

static const tSTATE kRWPCINDAnimationCharging1stOn =
{
	RWPCINDAnimationCharging1stOn_en,
	RWPCINDAnimationCharging1stOn_init,
	RWPCINDAnimationCharging1stOn_du,
	RWPCINDAnimationCharging1stOn_ex,
	RWPCINDAnimationCharging1stOn_run,
	&kRWPCINDAnimation1stSync
};

static const tSTATE kRWPCINDAnimationCharging1stFadeIn =
{
	RWPCINDAnimationCharging1stFadeIn_en,
	RWPCINDAnimationCharging1stFadeIn_init,
	RWPCINDAnimationCharging1stFadeIn_du,
	RWPCINDAnimationCharging1stFadeIn_ex,
	RWPCINDAnimationCharging1stFadeIn_run,
	&kRWPCINDAnimation1stSync
};

static const tSTATE kRWPCINDAnimationCharging2ndOn =
{
	RWPCINDAnimationCharging2ndOn_en,
	RWPCINDAnimationCharging2ndOn_init,
	RWPCINDAnimationCharging2ndOn_du,
	RWPCINDAnimationCharging2ndOn_ex,
	RWPCINDAnimationCharging2ndOn_run,
	&kRWPCINDAnimation2ndSync
};

static const tSTATE kRWPCINDAnimationCharging2ndFadeIn =
{
	RWPCINDAnimationCharging2ndFadeIn_en,
	RWPCINDAnimationCharging2ndFadeIn_init,
	RWPCINDAnimationCharging2ndFadeIn_du,
	RWPCINDAnimationCharging2ndFadeIn_ex,
	RWPCINDAnimationCharging2ndFadeIn_run,
	&kRWPCINDAnimation2ndSync
};
static const tSTATE kRWPCINDAnimationCharging3rdOn =
{
	RWPCINDAnimationCharging3rdOn_en,
	RWPCINDAnimationCharging3rdOn_init,
	RWPCINDAnimationCharging3rdOn_du,
	RWPCINDAnimationCharging3rdOn_ex,
	RWPCINDAnimationCharging3rdOn_run,
	&kRWPCINDAnimation3rdSync
};

static const tSTATE kRWPCINDAnimationCharging3rdFadeIn =
{
	RWPCINDAnimationCharging3rdFadeIn_en,
	RWPCINDAnimationCharging3rdFadeIn_init,
	RWPCINDAnimationCharging3rdFadeIn_du,
	RWPCINDAnimationCharging3rdFadeIn_ex,
	RWPCINDAnimationCharging3rdFadeIn_run,
	&kRWPCINDAnimation3rdSync
};

static const tSTATE kRWPCINDAnimationError =
{
	RWPCINDAnimationError_en,
	RWPCINDAnimationError_init,
	RWPCINDAnimationError_du,
	RWPCINDAnimationError_ex,
	RWPCINDAnimationError_run,
	NULL
};

static const tSTATE kRWPCINDAnimationErrorPreNone =
{
	RWPCINDAnimationErrorPreNone_en,
	RWPCINDAnimationErrorPreNone_init,
	RWPCINDAnimationErrorPreNone_du,
	RWPCINDAnimationErrorPreNone_ex,
	RWPCINDAnimationErrorPreNone_run,
	&kRWPCINDAnimationError
};
static const tSTATE kRWPCINDAnimationErrorPreWPC2WPC =
{
	RWPCINDAnimationErrorPreWPC2WPC_en,
	RWPCINDAnimationErrorPreWPC2WPC_init,
	RWPCINDAnimationErrorPreWPC2WPC_du,
	RWPCINDAnimationErrorPreWPC2WPC_ex,
	RWPCINDAnimationErrorPreWPC2WPC_run,
	&kRWPCINDAnimationError
};
static const tSTATE kRWPCINDAnimationErrorPreWPCWPC2 =
{
	RWPCINDAnimationErrorPreWPCWPC2_en,
	RWPCINDAnimationErrorPreWPCWPC2_init,
	RWPCINDAnimationErrorPreWPCWPC2_du,
	RWPCINDAnimationErrorPreWPCWPC2_ex,
	RWPCINDAnimationErrorPreWPCWPC2_run,
	&kRWPCINDAnimationError
};
static const tSTATE kRWPCINDAnimationErrorPreWPC =
{
	RWPCINDAnimationErrorPreWPC_en,
	RWPCINDAnimationErrorPreWPC_init,
	RWPCINDAnimationErrorPreWPC_du,
	RWPCINDAnimationErrorPreWPC_ex,
	RWPCINDAnimationErrorPreWPC_run,
	&kRWPCINDAnimationError
};
static const tSTATE kRWPCINDAnimationErrorPreWPC2 =
{
	RWPCINDAnimationErrorPreWPC2_en,
	RWPCINDAnimationErrorPreWPC2_init,
	RWPCINDAnimationErrorPreWPC2_du,
	RWPCINDAnimationErrorPreWPC2_ex,
	RWPCINDAnimationErrorPreWPC2_run,
	&kRWPCINDAnimationError
};

#if 0
static const tSTATE kRWPCINDAnimationErrorActive =
{
	RWPCINDAnimationErrorActive_en,
	RWPCINDAnimationErrorActive_init,
	RWPCINDAnimationErrorActive_du,
	RWPCINDAnimationErrorActive_ex,
	RWPCINDAnimationErrorActive_run,
	&kRWPCINDAnimationError
};
#endif

static const tSTATE kRWPCINDAnimationErrorOff =
{
	RWPCINDAnimationErrorOff_en,
	RWPCINDAnimationErrorOff_init,
	RWPCINDAnimationErrorOff_du,
	RWPCINDAnimationErrorOff_ex,
	RWPCINDAnimationErrorOff_run,
	&kRWPCINDAnimationError
};
static const tSTATE kRWPCINDAnimationErrorOn =
{
	RWPCINDAnimationErrorOn_en,
	RWPCINDAnimationErrorOn_init,
	RWPCINDAnimationErrorOn_du,
	RWPCINDAnimationErrorOn_ex,
	RWPCINDAnimationErrorOn_run,
	&kRWPCINDAnimationError
};




/******************************************************************************
	Define Constant and Macro
*******************************************************************************/


typedef enum
{
	kRWPCINDANIMATIONCONTROL_INIT=0,
	kRWPCINDANIMATIONCONTROL_OPERATING
} e_RWPCINDANIMATIONCONTROL;




/******************************************************************************
	Declare Variables
*******************************************************************************/
extern tTimer8	Timer_AmberINDBlk;
//extern u8 b_BlinkState;
//extern u8 Counter_BlinkCnt;
//static tTimer8	Timer_INDBlk = {Off, 0u};			
static tTimer16 Timer_INDLight = {Off, 0u};
static tTimer16 Timer_INDFadeIn = {Off, 0u}; 
static tTimer16 Timer_INDFadeOut = {Off, 0u}; 

uint8 AnimationSync_flag = 0u;
uint8 g_Var_WPC2PreSyncAct = Off;
uint8 g_Var_WPCPreSyncAct = Off;
uint8 g_Counter_BlinkCnt = 0u;

static tSTATE *stateCUR = NULL;


/******************************************************************************
	Define Functions
*******************************************************************************/


static void RWPCINDAnimationInit_en(void)
{
	CancelTimer(Timer_INDLight);
	SetOutput(kC_RWPC_IndSyncVal, kRWPCIndSyncVal_Default);
	SetOutput(kb_RWPCIndCmdState, RWPCIndCmdState_Default);
}


static const tSTATE* RWPCINDAnimationInit_init(void)
{
	return NULL;
}


static void RWPCINDAnimationInit_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimationInit_ex(void)
{
	/* Do Nothing */
}


static u8 RWPCINDAnimationInit_run(void)
{
	u8 ret = 0u;

#if 1
	if ((GetX(kC_WPC_PhnLftWrngRWPCSta) == (u8)kWPCWarning_Charging) &&
		(IsChgEvt(kC_USM_CmdWPCIndSta, (u8)kWPCAnimation_Type_2)))				//kb_WPCIndUSMState -> kC_USM_CmdWPCIndSta
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationCharging3rdOn);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationCharging3rdOn);
		ret = 1u;
	}
#else
	//else if ((GetX(kC_WPC_PhnLftWrngRWPCSta) == (u8)kWPCWarning_Charging) &&
	      if ((GetX(kC_WPC_PhnLftWrngRWPCSta) == (u8)kWPCWarning_Charging) &&
			  (GetX(kC_USM_CmdWPCIndSta) == (u8)kWPCAnimation_Type_2))			//kb_WPCIndUSMState -> kC_USM_CmdWPCIndSta
#endif
	else if ((GetX(kC_WPC_PhnLftWrngRWPCSta) == (u8)kWPCWarning_Charging) &&
			 (GetX(kC_USM_CmdWPCIndSta) == (u8)kWPCAnimation_Type_2))			//kb_WPCIndUSMState -> kC_USM_CmdWPCIndSta

	{ /* 2 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationCharging);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationCharging);
		ret = 1u;
	}
	else if ((GetX(kC_WPC_PhnLftWrngRWPCSta) == (u8)kWPCWarning_Error) &&
			 (GetX(kb_SyncAmber) == On) &&
			 (GetX(kC_USM_CmdWPCIndSta) == (u8)kWPCAnimation_Type_2))			//kb_WPCIndUSMState -> kC_USM_CmdWPCIndSta
	{ /* 3 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationError);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationError);
		ret = 1u;
	}
	else if((GetX(kC_WPC_PhnLftWrngRWPCSta) == (u8)kWPCWarning_Error) &&
			 (GetX(kb_SyncAmber) == On) &&
			 (IsChgEvt(kC_USM_CmdWPCIndSta, (u8)kWPCAnimation_Type_2)))			//kb_WPCIndUSMState -> kC_USM_CmdWPCIndSta
	{ /* 4 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationError);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationError);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}


static void RWPCINDAnimationCharging_en(void)
{
	StartTimer(Timer_INDLight);
	SetOutput(kC_RWPC_IndSyncVal, kRWPCIndSyncVal_3rdSync);
	SetOutput(kb_RWPCIndCmdState, RWPCIndCmdState_3rdChrgOn);
}


static const tSTATE* RWPCINDAnimationCharging_init(void)
{	
	tSTATE *ret_state = NULL;
	
	if(GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC)
	{ /* 1 */
		stateCUR = &kRWPCINDAnimationPreWPC;
		ret_state = &kRWPCINDAnimationPreWPC;
	}
	else if (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC2)
	{ /* 2 */
		stateCUR = &kRWPCINDAnimationPreWPC2;
		ret_state = &kRWPCINDAnimationPreWPC2;
	}
	
	else if (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC2WPC)
	{ /* 3 */
		stateCUR = &kRWPCINDAnimationPreWPC2WPC;
		ret_state = &kRWPCINDAnimationPreWPC2WPC;
	}
	else if (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPCWPC2)
	{ /* 4 */
		stateCUR = &kRWPCINDAnimationPreWPCWPC2;
		ret_state = &kRWPCINDAnimationPreWPCWPC2;
	}
	else if (GetX(kb_Var_PreSyncAct) == PreSyncAct_Off)
	{ /* 5 */
		stateCUR = &kRWPCINDAnimationPreNone;
		ret_state = &kRWPCINDAnimationPreNone;
	}
	else
	{
		/* MISRA-C */
	}

	return ret_state;
}


static void RWPCINDAnimationCharging_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimationCharging_ex(void)
{
	CancelTimer(Timer_INDLight);
}


static u8 RWPCINDAnimationCharging_run(void)
{
/* TSCR-561 Ani Fadein Fadeout */
	u8 ret = 0u;
#if 0	
	if(IsChgEvt(kC_USM_CmdWPCIndSta, (u8)kWPCAnimation_Type_1))			//kb_WPCIndUSMState -> kC_USM_CmdWPCIndSta
#else 	/* TSCR-1002_WPC_AnimationIND LED Off Time Change */
	if (IsChgEvt(kC_USM_CmdWPCIndSta, (u8)kWPCAnimation_Type_1) ||
	   (GetX(kC_WPC_PhnLftWrngRWPCSta) != kWPCWarning_Charging))
#endif
	{
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationInit);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationInit);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}


static void RWPCINDAnimationPreNone_en(void)
{
	/* Do Nothing */
}


static const tSTATE* RWPCINDAnimationPreNone_init(void)
{
	return NULL;
}


static void RWPCINDAnimationPreNone_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimationPreNone_ex(void)
{
	/* Do Nothing */
}


static u8 RWPCINDAnimationPreNone_run(void)
{
	u8 ret = 0u;

	if (Timer_INDLight.time >= Par_INDLightTime)
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationActive);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationActive);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}


static void RWPCINDAnimationPreWPC2WPC_en(void)
{
	/* Do Nothing */
}


static const tSTATE* RWPCINDAnimationPreWPC2WPC_init(void)
{
	return NULL;
}


static void RWPCINDAnimationPreWPC2WPC_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimationPreWPC2WPC_ex(void)
{
	/* Do Nothing */
}


static u8 RWPCINDAnimationPreWPC2WPC_run(void)
{
	u8 ret = 0u;

	if (IsChgEvt(kb_Var_PreSyncAct,PreSyncAct_Off))
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationPreNone);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationPreNone);
		ret = 1u;
	}
	else if (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC)
	{ /* 2 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationPreWPC);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationPreWPC);
		ret = 1u;
	}
	else if ((Timer_INDLight.time >= Par_INDLightTime) &&
			 (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC2WPC) &&
			 ((IsDiffEvt(kC_WPC2_IndSyncVal)) ||
			  (IsDiffEvt(kb_WPC2IndCmdState))))
	{ /* 3 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationActive);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationActive);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}


static void RWPCINDAnimationPreWPCWPC2_en(void)
{
	/* Do Nothing */
}


static const tSTATE* RWPCINDAnimationPreWPCWPC2_init(void)
{
	return NULL;
}


static void RWPCINDAnimationPreWPCWPC2_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimationPreWPCWPC2_ex(void)
{
	/* Do Nothing */
}


static u8 RWPCINDAnimationPreWPCWPC2_run(void)
{
	u8 ret = 0u;


	if (IsChgEvt(kb_Var_PreSyncAct, PreSyncAct_Off))
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationPreNone);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationPreNone);
		ret = 1u;
	}
	else if (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC2)
	{ /* 2 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationPreWPC2);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationPreWPC2);
		ret = 1u;
	}
	else if ((Timer_INDLight.time >= Par_INDLightTime) &&
			(GetX(kb_Var_PreSyncAct) == PreSyncAct_WPCWPC2) &&
			((IsDiffEvt(kC_WPC_IndSyncVal)) ||
			(IsDiffEvt(kb_WPCIndCmdState))))
	{ /* 3 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationActive);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationActive);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}

static void RWPCINDAnimationPreWPC_en(void)
{
	/* Do Nothing */
}


static const tSTATE* RWPCINDAnimationPreWPC_init(void)
{
	return NULL;
}


static void RWPCINDAnimationPreWPC_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimationPreWPC_ex(void)
{
	/* Do Nothing */
}


static u8 RWPCINDAnimationPreWPC_run(void)
{
	u8 ret = 0u;

	if (GetX(kb_Var_PreSyncAct) == WPC2PreSyncAct_Off)
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationPreNone);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationPreNone);
		ret = 1u;
	}
	else if ((Timer_INDLight.time >= Par_INDLightTime) &&
			 (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC) &&
			 ((IsDiffEvt(kC_WPC_IndSyncVal)) ||
			 (IsDiffEvt(kb_WPCIndCmdState))))
	{ /* 2 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationActive);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationActive);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}


static void RWPCINDAnimationPreWPC2_en(void)
{
	/* Do Nothing */
}


static const tSTATE* RWPCINDAnimationPreWPC2_init(void)
{
	return NULL;
}


static void RWPCINDAnimationPreWPC2_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimationPreWPC2_ex(void)
{
	/* Do Nothing */
}


static u8 RWPCINDAnimationPreWPC2_run(void)
{
	u8 ret = 0u;

	if (IsChgEvt(kb_Var_PreSyncAct, PreSyncAct_Off))
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationPreNone);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationPreNone);
		ret = 1u;
	}
	else if ((Timer_INDLight.time >= Par_INDLightTime) &&
			 (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC2) &&
			 ((IsDiffEvt(kC_WPC2_IndSyncVal)) ||
			 (IsDiffEvt(kb_WPC2IndCmdState))))
	{ /* 2 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationActive);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationActive);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}


static void RWPCINDAnimationActive_en(void)
{
	StartTimer(Timer_INDLight);
}


static const tSTATE* RWPCINDAnimationActive_init(void)
{
	tSTATE* ret_state = NULL;;


	if ((((GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC) ||
		  (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPCWPC2)) &&
		  (GetX(kC_WPC_IndSyncVal) == kWPCIndSyncVal_3rdSync)) ||
		(((GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC2) ||
		  (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC2WPC)) &&
		  (GetX(kC_WPC2_IndSyncVal) == kWPC2IndSyncVal_3rdSync)))
	{ /* 1 */
		stateCUR = &kRWPCINDAnimation3rdSync;
		ret_state = &kRWPCINDAnimation3rdSync;
	}
	else if ((((GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC) ||
		       (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPCWPC2)) &&
		       (GetX(kC_WPC_IndSyncVal) == kWPCIndSyncVal_2ndSync)) ||
	         (((GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC2) ||
		       (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC2WPC)) &&
		       (GetX(kC_WPC2_IndSyncVal) == kWPC2IndSyncVal_2ndSync)))
	{ /* 2 */
		stateCUR = &kRWPCINDAnimation2ndSync;
		ret_state = &kRWPCINDAnimation2ndSync;
	}
	else if ((((GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC) ||
	           (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPCWPC2)) &&
		       (GetX(kC_WPC_IndSyncVal) == kWPCIndSyncVal_1stSync) ||
		       (GetX(kC_WPC_IndSyncVal) == kWPCIndSyncVal_ErrorOff)) ||
	         (((GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC2) ||
		       (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC2WPC)) &&
		       (GetX(kC_WPC2_IndSyncVal) == kWPC2IndSyncVal_1stSync) ||
		       (GetX(kC_WPC2_IndSyncVal) == kWPC2IndSyncVal_ErrorOff)))
	{ /* 3 */
		stateCUR = &kRWPCINDAnimation1stSync;
		ret_state = &kRWPCINDAnimation1stSync;
	}
	else
	{ /* 4 */
		stateCUR = &kRWPCINDAnimationOff;
		ret_state = &kRWPCINDAnimationOff;
	}

	return ret_state;
}


static void RWPCINDAnimationActive_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimationActive_ex(void)
{
	CancelTimer(Timer_INDLight);
}


static u8 RWPCINDAnimationActive_run(void)
{
	return 0;
}


static void RWPCINDAnimationOff_en(void)
{
	CancelTimer(Timer_INDLight);
	SetOutput(kC_RWPC_IndSyncVal, kRWPCIndSyncVal_Off);
}


static const tSTATE* RWPCINDAnimationOff_init(void)
{
	/* TSCR-561 Ani Fadein Fadeout */
	tSTATE* ret_state = NULL;
	/*	TSCR-1002_WPC_AnimationIND LED Off Time Change */	
	if((GetX(kb_WPCIndCmdState) == WPCIndCmdState_ErrorFadeIn) ||
	   (GetX(kb_WPCIndCmdState) == WPCIndCmdState_ErrorOn) ||
	   (GetX(kb_RWPCIndCmdState) == RWPCIndCmdState_ErrorFadeIn) ||
	   (GetX(kb_RWPCIndCmdState) == RWPCIndCmdState_ErrorOn))

	{ /* 1 */
		stateCUR = &kRWPCINDAnimationOffFadeOut;
		ret_state = &kRWPCINDAnimationOffFadeOut;
	}
	else
	{ /* 2 */
		stateCUR = &kRWPCINDAnimationOffFadeOut;
		ret_state = &kRWPCINDAnimationOffFadeOut;
	}
	return ret_state;
}


static void RWPCINDAnimationOff_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimationOff_ex(void)
{
	CancelTimer(Timer_INDLight);
}


static u8 RWPCINDAnimationOff_run(void)
{
	u8 ret = 0u;

/* TSCR-561 Ani Fadein Fadeout */
	if ((Timer_INDFadeOut.time >= Par_INDLightTime) &&
	    (GetX(kC_WPC_PhnLftWrngRWPCSta) == (u8)kWPCWarning_Error))
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationError);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationError);
		ret = 1u;
	}
	else if(((Timer_INDFadeOut.time >= Par_INDFadeOutTime) &&
			 (GetX(kC_WPC_PhnLftWrngRWPCSta) != (u8)kWPCWarning_Charging))||
			 (IsChgEvt(kC_USM_CmdWPCIndSta, (u8)kWPCAnimation_Type_1)))			//kb_WPCIndUSMState -> kC_USM_CmdWPCIndSta
	{ /* 2 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationInit);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationInit);
		ret = 1u;
	}
	else if (Timer_INDFadeOut.time >= Par_INDFadeOutTime)
	{ /* 3 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimation1stSync);
		stateCUR = transition(stateCUR, &kRWPCINDAnimation1stSync);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}


static void RWPCINDAnimation1stSync_en(void)
{
	SetOutput(kC_RWPC_IndSyncVal, kRWPCIndSyncVal_1stSync);
}


static const tSTATE* RWPCINDAnimation1stSync_init(void)
{
	/* TSCR-561 Ani Fadein Fadeout */
	tSTATE* ret_state = NULL;
	
	if((GetX(kb_WPCIndCmdState) == WPCIndCmdState_1stChrgOn) ||
		(GetX(kb_WPC2IndCmdState) == WPC2IndCmdState_1stChrgOn))
		
	{ /* 1 */
		stateCUR = &kRWPCINDAnimationCharging1stOn;
		ret_state = &kRWPCINDAnimationCharging1stOn;
	}
	/* % input GetX(kb_WPCIndCmdState) == WPCIndCmdState_1stChrgFadeIn) || */
	/* % input GetX(kb_WPCIndCmdState) == WPCIndCmdState_ErrorFadeOut) ||  */
	/* % input GetX(kb_WPC2IndCmdState) == WPC2IndCmdState_1stChrgFadeIn) || */ 
	/* % input GetX(kb_WPC2IndCmdState) == WPC2IndCmdState_ErrorFadeOut))    */
	else		
	{ /* 2 */
		stateCUR = &kRWPCINDAnimationCharging1stFadeIn;
		ret_state = &kRWPCINDAnimationCharging1stFadeIn;
	}
	return ret_state;
}


static void RWPCINDAnimation1stSync_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimation1stSync_ex(void)
{
	CancelTimer(Timer_INDLight);
}


static u8 RWPCINDAnimation1stSync_run(void)
{
	u8 ret = 0u;
#if 0
	/* Get rid of phone on the pad or Transfer error state */
	if (GetX(kC_WPC_PhnLftWrngRWPCSta) != (u8)kWPCWarning_Charging)
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationOff);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationOff);
		ret = 1u;
	}
	else if (Timer_INDLight.time >= Par_INDLightTime)
	{ /* 2 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimation2ndSync);
		stateCUR = transition(stateCUR, &kRWPCINDAnimation2ndSync);
		ret = 1u;
	}
	else if(IsChgEvt(kC_USM_CmdWPCIndSta, (u8)kWPCAnimation_Type_1))		//kb_WPCIndUSMState -> kC_USM_CmdWPCIndSta
	{
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationInit);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationInit);
		ret = 1u;
	}
#else	/*	TSCR-1002_WPC_AnimationIND LED Off Time Change */
	if (Timer_INDLight.time >= Par_INDLightTime)
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimation2ndSync);
		stateCUR = transition(stateCUR, &kRWPCINDAnimation2ndSync);
		ret = 1u;
	}
#endif
	return ret;
}


static void RWPCINDAnimation3rdSync_en(void)
{
	SetOutput(kC_RWPC_IndSyncVal, kRWPCIndSyncVal_3rdSync);
}


static const tSTATE* RWPCINDAnimation3rdSync_init(void)
{
	/* TSCR-561 Ani Fadein Fadeout */
	tSTATE* ret_state = NULL;
	
	if((GetX(kb_WPCIndCmdState) == WPCIndCmdState_3rdChrgOn) ||
		(GetX(kb_WPC2IndCmdState) == WPC2IndCmdState_3rdChrgOn))
		
	{ /* 1 */
		stateCUR = &kRWPCINDAnimationCharging3rdOn;
		ret_state = &kRWPCINDAnimationCharging3rdOn;
	}
	/* % input GetX(kb_WPCIndCmdState) == WPCIndCmdState_3rdChrgFadeIn) || */
	/* % input GetX(kb_WPC2IndCmdState) == WPC2IndCmdState_3rdChrgFadeIn)    */		
	else
	{ /* 2 */
		stateCUR = &kRWPCINDAnimationCharging3rdFadeIn;
		ret_state = &kRWPCINDAnimationCharging3rdFadeIn;
	}
	return ret_state;
}


static void RWPCINDAnimation3rdSync_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimation3rdSync_ex(void)
{
	CancelTimer(Timer_INDLight);
}


static u8 RWPCINDAnimation3rdSync_run(void)
{
	u8 ret = 0u;
#if 0
	/* Get rid of phone on the pad or Transfer error state */
	if (GetX(kC_WPC_PhnLftWrngRWPCSta) != (u8)kWPCWarning_Charging)
	{ /* 1 */
	   stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationOff);
	   stateCUR = transition(stateCUR, &kRWPCINDAnimationOff);
	   ret = 1u;
	}
	else if(IsChgEvt(kC_USM_CmdWPCIndSta, (u8)kWPCAnimation_Type_1))		//kb_WPCIndUSMState -> kC_USM_CmdWPCIndSta
	{ /* 2 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationInit);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationInit);
		ret = 1u;
	}
	else if (Timer_INDLight.time >= Par_INDLightTime)
	{ /* 3 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationOff);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationOff);
		ret = 1u;
	}
#else	/* TSCR-1002_WPC_AnimationIND LED Off Time Change */
	if (Timer_INDLight.time >= Par_INDLightTime)
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationOff);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationOff);
		ret = 1u;
	}
#endif
	return ret;
}


static void RWPCINDAnimation2ndSync_en(void)
{
	SetOutput(kC_RWPC_IndSyncVal, kRWPCIndSyncVal_2ndSync);
}


static const tSTATE* RWPCINDAnimation2ndSync_init(void)
{
	/* TSCR-561 Ani Fadein Fadeout */
	tSTATE* ret_state = NULL;
	
	if((GetX(kb_WPCIndCmdState) == WPCIndCmdState_2ndChrgOn) ||
		(GetX(kb_WPC2IndCmdState) == WPC2IndCmdState_2ndChrgOn))
		
	{ /* 1 */
		stateCUR = &kRWPCINDAnimationCharging2ndOn;
		ret_state = &kRWPCINDAnimationCharging2ndOn;
	}

	/* input GetX(kb_WPCIndCmdState) == WPCIndCmdState_2ndChrgFadeIn) || */
	/* input GetX(kb_RWPCIndCmdState) == RWPCIndCmdState_2ndChrgFadeIn)    */
	else
	{ /* 2 */
		stateCUR = &kRWPCINDAnimationCharging2ndFadeIn;
		ret_state = &kRWPCINDAnimationCharging2ndFadeIn;
	}
	return ret_state;
}


static void RWPCINDAnimation2ndSync_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimation2ndSync_ex(void)
{
	CancelTimer(Timer_INDLight);
}


static u8 RWPCINDAnimation2ndSync_run(void)
{
	u8 ret = 0u;
#if 0	
	/* Get rid of phone on the pad or Transfer error state */
	if (GetX(kC_WPC_PhnLftWrngRWPCSta) != (u8)kWPCWarning_Charging)
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationOff);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationOff);
		ret = 1u;
	}
	else if (Timer_INDLight.time >= Par_INDLightTime)
	{ /* 2 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimation3rdSync);
		stateCUR = transition(stateCUR, &kRWPCINDAnimation3rdSync);
		ret = 1u;
	}
	else if(IsChgEvt(kC_USM_CmdWPCIndSta, (u8)kWPCAnimation_Type_1))		//kb_WPCIndUSMState -> kC_USM_CmdWPCIndSta
	{ /* 3 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationInit);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationInit);
		ret = 1u;
	}
#else	/* TSCR-1002_WPC_AnimationIND LED Off Time Change */	
	if (Timer_INDLight.time >= Par_INDLightTime)
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimation3rdSync);
		stateCUR = transition(stateCUR, &kRWPCINDAnimation3rdSync);
		ret = 1u;
	}
#endif
	return ret;
}

/* TSCR-561 Ani Fadein Fadeout */
#if 0 /*	TSCR-1002_WPC_AnimationIND LED Off Time Change */
static void RWPCINDAnimationOffHold_en(void)
{
	StartTimer(Timer_INDLight);
	SetOutput(kb_RWPCIndCmdState, RWPCIndCmdState_ChrgOff);
}


static const tSTATE* RWPCINDAnimationOffHold_init(void)
{
	return NULL;
}


static void RWPCINDAnimationOffHold_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimationOffHold_ex(void)
{
	CancelTimer(Timer_INDLight);
}


static u8 RWPCINDAnimationOffHold_run(void)
{
	return 0;
}
#endif
/* TSCR-561 Ani Fadein Fadeout */
static void RWPCINDAnimationOffFadeOut_en(void)
{
	StartTimer(Timer_INDFadeOut);
	//StartTimer(Timer_INDLight);		//20230510
	SetOutput(kb_RWPCIndCmdState, RWPCIndCmdState_ChrgFadeOut);
}


static const tSTATE* RWPCINDAnimationOffFadeOut_init(void)
{
	return NULL;
}


static void RWPCINDAnimationOffFadeOut_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimationOffFadeOut_ex(void)
{
	CancelTimer(Timer_INDFadeOut);
}


static u8 RWPCINDAnimationOffFadeOut_run(void)
{
#if 0	/*	TSCR-1002_WPC_AnimationIND LED Off Time Change */
	u8 ret = 0u;


	if (Timer_INDFadeOut.time >= Par_INDFadeOutTime)
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationOffHold);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationOffHold);
		ret = 1u;
	}
	return ret;
#endif
	return 0;
}


/* TSCR-561 Ani Fadein Fadeout */
static void RWPCINDAnimationCharging1stOn_en(void)
{
	StartTimer(Timer_INDLight);
	SetOutput(kb_RWPCIndCmdState, RWPCIndCmdState_1stChrgOn);
}


static const tSTATE* RWPCINDAnimationCharging1stOn_init(void)
{
	return NULL;
}


static void RWPCINDAnimationCharging1stOn_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimationCharging1stOn_ex(void)
{
	CancelTimer(Timer_INDLight);
}


static u8 RWPCINDAnimationCharging1stOn_run(void)
{
	return 0;
}

/* TSCR-561 Ani Fadein Fadeout */
static void RWPCINDAnimationCharging1stFadeIn_en(void)
{
	CancelTimer(Timer_INDLight);
	StartTimer(Timer_INDFadeIn);
	SetOutput(kb_RWPCIndCmdState, RWPCIndCmdState_1stChrgFadeIn);
}


static const tSTATE* RWPCINDAnimationCharging1stFadeIn_init(void)
{
	return NULL;
}


static void RWPCINDAnimationCharging1stFadeIn_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimationCharging1stFadeIn_ex(void)
{
	CancelTimer(Timer_INDFadeIn);
}


static u8 RWPCINDAnimationCharging1stFadeIn_run(void)
{
	u8 ret = 0u;

	if(Timer_INDFadeIn.time >= Par_INDFadeInTime)
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationCharging1stOn);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationCharging1stOn);
		ret = 1u;
	}
	return ret;
}

/* TSCR-561 Ani Fadein Fadeout */
static void RWPCINDAnimationCharging2ndOn_en(void)
{
	StartTimer(Timer_INDLight);
	SetOutput(kb_RWPCIndCmdState, RWPCIndCmdState_2ndChrgOn);
}


static const tSTATE* RWPCINDAnimationCharging2ndOn_init(void)
{
	return NULL;
}


static void RWPCINDAnimationCharging2ndOn_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimationCharging2ndOn_ex(void)
{
	CancelTimer(Timer_INDLight);
}


static u8 RWPCINDAnimationCharging2ndOn_run(void)
{
	return 0;
}

/* TSCR-561 Ani Fadein Fadeout */
static void RWPCINDAnimationCharging2ndFadeIn_en(void)
{
	CancelTimer(Timer_INDLight);
	StartTimer(Timer_INDFadeIn);
	SetOutput(kb_RWPCIndCmdState, RWPCIndCmdState_2ndChrgFadeIn);
}


static const tSTATE* RWPCINDAnimationCharging2ndFadeIn_init(void)
{
	return NULL;
}


static void RWPCINDAnimationCharging2ndFadeIn_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimationCharging2ndFadeIn_ex(void)
{
	CancelTimer(Timer_INDFadeIn);
}


static u8 RWPCINDAnimationCharging2ndFadeIn_run(void)
{
	u8 ret = 0u;

	if(Timer_INDFadeIn.time >= Par_INDFadeInTime)
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationCharging2ndOn);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationCharging2ndOn);
		ret = 1u;
	}
	return ret;
}

/* TSCR-561 Ani Fadein Fadeout */
static void RWPCINDAnimationCharging3rdOn_en(void)
{
	StartTimer(Timer_INDLight);
	SetOutput(kb_RWPCIndCmdState, RWPCIndCmdState_3rdChrgOn);
}


static const tSTATE* RWPCINDAnimationCharging3rdOn_init(void)
{
	return NULL;
}


static void RWPCINDAnimationCharging3rdOn_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimationCharging3rdOn_ex(void)
{
	CancelTimer(Timer_INDLight);
}


static u8 RWPCINDAnimationCharging3rdOn_run(void)
{
	return 0;
}

/* TSCR-561 Ani Fadein Fadeout */
static void RWPCINDAnimationCharging3rdFadeIn_en(void)
{
	CancelTimer(Timer_INDLight);
	StartTimer(Timer_INDFadeIn);
	SetOutput(kb_RWPCIndCmdState, RWPCIndCmdState_3rdChrgFadeIn);
}


static const tSTATE* RWPCINDAnimationCharging3rdFadeIn_init(void)
{
	return NULL;
}


static void RWPCINDAnimationCharging3rdFadeIn_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimationCharging3rdFadeIn_ex(void)
{
	CancelTimer(Timer_INDFadeIn);
}


static u8 RWPCINDAnimationCharging3rdFadeIn_run(void)
{
	u8 ret = 0u;

	if(Timer_INDFadeIn.time >= Par_INDFadeInTime)
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationCharging3rdOn);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationCharging3rdOn);
		ret = 1u;
	}
	return ret;
}

static void RWPCINDAnimationError_en(void)
{
	StartTimer(Timer_INDFadeIn);
	SetOutput(kC_RWPC_IndSyncVal, kRWPCIndSyncVal_ErrorOn);
	SetOutput(kb_RWPCIndCmdState, RWPCIndCmdState_ErrorFadeIn);
}


static const tSTATE* RWPCINDAnimationError_init(void)
{
	tSTATE* ret_state = NULL;


	if (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC)
	{ /* 1 */
		stateCUR = &kRWPCINDAnimationErrorPreWPC;
		ret_state = &kRWPCINDAnimationErrorPreWPC;
	}
	else if (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC2)
	{ /* 2 */
		stateCUR = &kRWPCINDAnimationErrorPreWPC2;
		ret_state = &kRWPCINDAnimationErrorPreWPC2;
	}
	else if (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC2WPC)
	{ /* 3 */
		stateCUR = &kRWPCINDAnimationErrorPreWPC2WPC;
		ret_state = &kRWPCINDAnimationErrorPreWPC2WPC;
	}
	else if (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPCWPC2)
	{ /* 4 */
		stateCUR = &kRWPCINDAnimationErrorPreWPCWPC2;
		ret_state = &kRWPCINDAnimationErrorPreWPCWPC2;
	}
	else if (GetX(kb_Var_PreSyncAct) == PreSyncAct_Off)
	{ /* 5 */
		stateCUR = &kRWPCINDAnimationErrorPreNone;
		ret_state = &kRWPCINDAnimationErrorPreNone;
	}
	else
	{
		/* MISRA-C */
	}

	return ret_state;
}

static void RWPCINDAnimationError_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimationError_ex(void)
{
	CancelTimer(Timer_INDFadeIn);
}


static u8 RWPCINDAnimationError_run(void)
{
	/* TSCR-561 Ani Fadein Fadeout */
	u8 ret = 0u;
	
	if (IsChgEvt(kb_SyncAmber, Off))
	{
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationInit);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationInit);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}

static void RWPCINDAnimationErrorPreNone_en(void)
{
	/* Do Nothing */
}


static const tSTATE* RWPCINDAnimationErrorPreNone_init(void)
{
	return NULL;
}


static void RWPCINDAnimationErrorPreNone_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimationErrorPreNone_ex(void)
{
	/* Do Nothing */
}


static u8 RWPCINDAnimationErrorPreNone_run(void)
{
	u8 ret = 0u;

	if (Timer_INDFadeIn.time >= Par_INDFadeInTime)
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationErrorOff);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationErrorOff);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}


static void RWPCINDAnimationErrorPreWPC2WPC_en(void)
{
	/* Do Nothing */
}


static const tSTATE* RWPCINDAnimationErrorPreWPC2WPC_init(void)
{
	return NULL;
}


static void RWPCINDAnimationErrorPreWPC2WPC_du(void)
{
	/* TSCR-561 Ani Fadein Fadeout */
	Function_INDErrorOnOut();
}


static void RWPCINDAnimationErrorPreWPC2WPC_ex(void)
{
	/* Do Nothing */
}


static u8 RWPCINDAnimationErrorPreWPC2WPC_run(void)
{
	u8 ret = 0u;

	if (IsChgEvt(kb_Var_PreSyncAct,PreSyncAct_Off))
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationErrorPreNone);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationErrorPreNone);
		ret = 1u;
	}
	else if (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC)
	{ /* 2 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationErrorPreWPC);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationErrorPreWPC);
		ret = 1u;
	}
	else if ((Timer_INDFadeIn.time >= Par_INDFadeInTime) &&
			 (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC2WPC) &&
			 ((IsChgEvt(kC_WPC2_IndSyncVal, kWPC2IndSyncVal_1stSync)) ||
			 (IsChgEvt(kC_WPC2_IndSyncVal, kWPC2IndSyncVal_2ndSync))||
			 (IsChgEvt(kC_WPC2_IndSyncVal, kWPC2IndSyncVal_3rdSync)) ||
			 (IsChgEvt(kC_WPC2_IndSyncVal, kWPC2IndSyncVal_Off)) ||
			 (IsChgEvt(kC_WPC2_IndSyncVal, kWPC2IndSyncVal_ErrorOff))))
			 
	{ /* 3 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationErrorOff);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationErrorOff);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}


static void RWPCINDAnimationErrorPreWPCWPC2_en(void)
{
	/* Do Nothing */
}


static const tSTATE* RWPCINDAnimationErrorPreWPCWPC2_init(void)
{
	return NULL;
}


static void RWPCINDAnimationErrorPreWPCWPC2_du(void)
{
	/* TSCR-561 Ani Fadein Fadeout */
	Function_INDErrorOnOut();
}


static void RWPCINDAnimationErrorPreWPCWPC2_ex(void)
{
	/* Do Nothing */
}


static u8 RWPCINDAnimationErrorPreWPCWPC2_run(void)
{
	u8 ret = 0u;


	if (IsChgEvt(kb_Var_PreSyncAct, PreSyncAct_Off))
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationErrorPreNone);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationErrorPreNone);
		ret = 1u;
	}
	else if (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC2)
	{ /* 2 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationErrorPreWPC2);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationErrorPreWPC2);
		ret = 1u;
	}
	else if ((Timer_INDFadeIn.time >= Par_INDFadeInTime) &&
			 (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPCWPC2) &&
			 ((IsChgEvt(kC_WPC_IndSyncVal, kWPCIndSyncVal_1stSync)) ||
			 (IsChgEvt(kC_WPC_IndSyncVal, kWPCIndSyncVal_2ndSync)) ||
			 (IsChgEvt(kC_WPC_IndSyncVal, kWPCIndSyncVal_3rdSync)) ||
			 (IsChgEvt(kC_WPC_IndSyncVal, kWPCIndSyncVal_Off)) ||
			 (IsChgEvt(kC_WPC_IndSyncVal, kWPCIndSyncVal_ErrorOff))))
	{ /* 3 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationErrorOff);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationErrorOff);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}

static void RWPCINDAnimationErrorPreWPC_en(void)
{
	/* Do Nothing */
}


static const tSTATE* RWPCINDAnimationErrorPreWPC_init(void)
{
	return NULL;
}


static void RWPCINDAnimationErrorPreWPC_du(void)
{
	/* TSCR-561 Ani Fadein Fadeout */
	Function_INDErrorOnOut();
}


static void RWPCINDAnimationErrorPreWPC_ex(void)
{
	/* Do Nothing */
}


static u8 RWPCINDAnimationErrorPreWPC_run(void)
{
	u8 ret = 0u;

	if (IsChgEvt(kb_Var_PreSyncAct,PreSyncAct_Off))
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationErrorPreNone);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationErrorPreNone);
		ret = 1u;
	}
	else if ((Timer_INDFadeIn.time >= Par_INDFadeInTime) &&
			 (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC) &&
			 ((IsChgEvt(kC_WPC_IndSyncVal, kWPCIndSyncVal_1stSync)) ||
			 (IsChgEvt(kC_WPC_IndSyncVal, kWPCIndSyncVal_2ndSync)) ||
			 (IsChgEvt(kC_WPC_IndSyncVal, kWPCIndSyncVal_3rdSync)) ||
			 (IsChgEvt(kC_WPC_IndSyncVal, kWPCIndSyncVal_Off)) ||
			 (IsChgEvt(kC_WPC_IndSyncVal, kWPCIndSyncVal_ErrorOff))))
	{ /* 2 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationErrorOff);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationErrorOff);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}


static void RWPCINDAnimationErrorPreWPC2_en(void)
{
	/* Do Nothing */
}


static const tSTATE* RWPCINDAnimationErrorPreWPC2_init(void)
{
	return NULL;
}


static void RWPCINDAnimationErrorPreWPC2_du(void)
{
	/* TSCR-561 Ani Fadein Fadeout */
	Function_INDErrorOnOut();
}


static void RWPCINDAnimationErrorPreWPC2_ex(void)
{
	/* Do Nothing */
}


static u8 RWPCINDAnimationErrorPreWPC2_run(void)
{
	u8 ret = 0u;

	if (IsChgEvt(kb_Var_PreSyncAct, PreSyncAct_Off))
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationErrorPreNone);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationErrorPreNone);
		ret = 1u;
	}
	
	else if ((Timer_INDFadeIn.time >= Par_INDFadeInTime) &&
			 (GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC2) &&
			 ((IsChgEvt(kC_WPC2_IndSyncVal, kWPC2IndSyncVal_1stSync)) ||
			 (IsChgEvt(kC_WPC2_IndSyncVal, kWPC2IndSyncVal_2ndSync)) ||
			 (IsChgEvt(kC_WPC2_IndSyncVal, kWPC2IndSyncVal_3rdSync)) ||
			 (IsChgEvt(kC_WPC2_IndSyncVal, kWPC2IndSyncVal_Off)) ||
			 (IsChgEvt(kC_WPC2_IndSyncVal, kWPC2IndSyncVal_ErrorOff))))
	{ /* 2 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationErrorOff);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationErrorOff);
		ret = 1u;
	}
	else
	{
		/* MISRA */
	}
	return ret;
}

static void RWPCINDAnimationErrorOff_en(void)
{
	CancelTimer(Timer_INDFadeIn);
	StartTimer(Timer_INDFadeOut);
	SetOutput(kC_RWPC_IndSyncVal, kRWPCIndSyncVal_ErrorOff);
	SetOutput(kb_RWPCIndCmdState, RWPCIndCmdState_ErrorFadeOut);
}


static const tSTATE* RWPCINDAnimationErrorOff_init(void)
{
	return NULL;
}


static void RWPCINDAnimationErrorOff_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimationErrorOff_ex(void)
{
	CancelTimer(Timer_INDFadeOut);
}


static u8 RWPCINDAnimationErrorOff_run(void)
{
	u8 ret = 0u;

	if((Timer_INDFadeOut.time >= Par_INDFadeOutTime) &&
	   (GetX(kC_WPC_PhnLftWrngRWPCSta) == (u8)kWPCWarning_Charging))
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationCharging);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationCharging);
		ret = 1u;
	}
	else if((Timer_INDFadeOut.time >= Par_INDFadeOutTime) &&
			(GetX(kC_WPC_PhnLftWrngRWPCSta) != (u8)kWPCWarning_Error))
	{
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationInit);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationInit);
		ret = 1u;
	}
#if 0	
	else if ((Timer_INDFadeOut.time >= Par_INDFadeOutTime) &&
			 (g_Counter_BlinkCnt != 10u))
#else
	else if (Timer_INDFadeOut.time >= Par_INDFadeOutTime)
#endif	
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationErrorOn);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationErrorOn);
		ret = 1u;
	}
	return ret;
}


static void RWPCINDAnimationErrorOn_en(void)
{
	StartTimer(Timer_INDFadeIn);
	SetOutput(kC_RWPC_IndSyncVal, kRWPCIndSyncVal_ErrorOn);
	SetOutput(kb_RWPCIndCmdState, RWPCIndCmdState_ErrorFadeIn);
}


static const tSTATE* RWPCINDAnimationErrorOn_init(void)
{
	return NULL;
}


static void RWPCINDAnimationErrorOn_du(void)
{
	/* Do Nothing */
}


static void RWPCINDAnimationErrorOn_ex(void)
{
	CancelTimer(Timer_INDFadeIn);
}


static u8 RWPCINDAnimationErrorOn_run(void)
{
	u8 ret = 0u;


	if (Timer_INDFadeIn.time >= Par_INDFadeInTime)
	{ /* 1 */
		stateCUR = transition_exit(stateCUR, &kRWPCINDAnimationErrorOff);
		stateCUR = transition(stateCUR, &kRWPCINDAnimationErrorOff);
		ret = 1u;
	}
	return ret;
}

static void INDAnimationWPC2Priority(void)
{
	if((g_Var_WPC2PreSyncAct == Off) && 
	   (IsChgEvt(kC_WPC2_IndSyncVal, kWPC2IndSyncVal_Off)) ||
	   (IsChgEvt(kC_WPC2_IndSyncVal, kWPC2IndSyncVal_1stSync)) ||
	   (IsChgEvt(kC_WPC2_IndSyncVal, kWPC2IndSyncVal_2ndSync)) ||
	   (IsChgEvt(kC_WPC2_IndSyncVal, kWPC2IndSyncVal_3rdSync)) ||
	   (IsChgEvt(kC_WPC2_IndSyncVal, kWPC2IndSyncVal_ErrorOff)) ||
	   (IsChgEvt(kC_WPC2_IndSyncVal, kWPC2IndSyncVal_ErrorOn)))
	{
		g_Var_WPC2PreSyncAct = On;
	}
	else if((g_Var_WPC2PreSyncAct == On) && 
		    (IsChgEvt(kC_WPC2_IndSyncVal, kWPC2IndSyncVal_Default)))
	{
		g_Var_WPC2PreSyncAct = Off;
	}
	else
	{
		/* Do Nothing */
	}

}

static void INDAnimationWPCPriority(void)
{
	if((g_Var_WPCPreSyncAct == Off) && 
		(IsChgEvt(kC_WPC_IndSyncVal, kRWPCIndSyncVal_Off)) ||
		(IsChgEvt(kC_WPC_IndSyncVal, kRWPCIndSyncVal_1stSync)) ||
		(IsChgEvt(kC_WPC_IndSyncVal, kRWPCIndSyncVal_2ndSync)) ||
		(IsChgEvt(kC_WPC_IndSyncVal, kRWPCIndSyncVal_3rdSync)) ||
		(IsChgEvt(kC_WPC_IndSyncVal, kRWPCIndSyncVal_ErrorOff)) ||
		(IsChgEvt(kC_WPC_IndSyncVal, kRWPCIndSyncVal_ErrorOn)))
	{
		g_Var_WPCPreSyncAct = On;
	}
	else if((g_Var_WPCPreSyncAct == On) && 
			(IsChgEvt(kC_WPC_IndSyncVal, kWPCIndSyncVal_Default)))
	{
		g_Var_WPCPreSyncAct = Off;
	}
	else
	{
		/* Do Nothing */
	}
}

static void INDAnimationPriority(void)
{
	if((g_Var_WPCPreSyncAct == On) && (g_Var_WPC2PreSyncAct == Off))
	{
		SetX(kb_Var_PreSyncAct, PreSyncAct_WPC);
	}
	else if((g_Var_WPCPreSyncAct == Off) && (g_Var_WPC2PreSyncAct == On))
	{
		SetX(kb_Var_PreSyncAct, PreSyncAct_WPC2);
	}
	else if((GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC) && 
			(g_Var_WPCPreSyncAct == On) &&
			(g_Var_WPC2PreSyncAct == On))
	{
		SetX(kb_Var_PreSyncAct, PreSyncAct_WPCWPC2);
	}
	else if((GetX(kb_Var_PreSyncAct) == PreSyncAct_WPC2) && 
			(g_Var_WPCPreSyncAct == On) &&
			(g_Var_WPC2PreSyncAct == On))
	{
		SetX(kb_Var_PreSyncAct, PreSyncAct_WPC2WPC);
	}
	else if((g_Var_WPCPreSyncAct == Off) && (g_Var_WPC2PreSyncAct == Off))
	{
		SetX(kb_Var_PreSyncAct, PreSyncAct_Off);
	}	
	else
	{
		/* Do Nothing */
	}

}
#if 1
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

void Function_INDErrorOnOut(void)
{
	if(Timer_INDFadeIn.time >= Par_INDFadeInTime)
	{
		SetOutput(kb_RWPCIndCmdState, RWPCIndCmdState_ErrorOn);
	}
}



void RWPCINDAnimationControl(void)
{
	static e_RWPCINDANIMATIONCONTROL sts_RWPCINDANIMATIONCONTROL = kRWPCINDANIMATIONCONTROL_INIT;

	UpTimer16(Timer_INDLight);
	UpTimer16(Timer_INDFadeIn);
	UpTimer16(Timer_INDFadeOut);

	INDAnimationPriority();
	INDAnimationWPC2Priority();
	INDAnimationWPCPriority();
	AmberSyncState();
	AmberSyncIndyState();

	switch(sts_RWPCINDANIMATIONCONTROL)
	{
		case kRWPCINDANIMATIONCONTROL_INIT:
			stateCUR = &kRWPCINDAnimationInit;
			stateCUR = transition(stateCUR, &kRWPCINDAnimationInit);
			sts_RWPCINDANIMATIONCONTROL = kRWPCINDANIMATIONCONTROL_OPERATING;
			break;

		case kRWPCINDANIMATIONCONTROL_OPERATING:
			CurrentRun(stateCUR);
			break;

		default:
			/* MISRA */
			break;
	}
}



