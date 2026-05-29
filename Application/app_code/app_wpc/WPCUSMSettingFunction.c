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
#include "app_output_type.h"
#include "app_output.h"

#include "WPCEepControl.h"
#include "WPCLogicControl.h"
#include "Superstate_api.h"
/*******************************************************************************
* Define Functions                                                             *
*******************************************************************************/
static void WPCUSM_SetGuest_en(void);
static tSTATE* WPCUSM_SetGuest_init(void);
static void WPCUSM_SetGuest_du(void);
static void WPCUSM_SetGuest_ex(void);
static u8 WPCUSM_SetGuest_run(void);

static void WPCUSM_SetOne_en(void);
static tSTATE* WPCUSM_SetOne_init(void);
static void WPCUSM_SetOne_du(void);
static void WPCUSM_SetOne_ex(void);
static u8 WPCUSM_SetOne_run(void);

static void WPCUSM_SetTwo_en(void);
static tSTATE* WPCUSM_SetTwo_init(void);
static void WPCUSM_SetTwo_du(void);
static void WPCUSM_SetTwo_ex(void);
static u8 WPCUSM_SetTwo_run(void);

static void Function_ProfileGuestWPCUSM(void);
static void Function_ProfileOneWPCUSM(void);
static void Function_ProfileTwoWPCUSM(void);

void WPCUSMSetting(void);
void WPCCurrentProfileDecision(void);
/*******************************************************************************
* Define Constant and Macro                                                    *
*******************************************************************************/
static const tSTATE kWPCUSM_SetGuest = 
{
	WPCUSM_SetGuest_en,
	WPCUSM_SetGuest_init,
	WPCUSM_SetGuest_du,
	WPCUSM_SetGuest_ex,
	WPCUSM_SetGuest_run,
	NULL
};

static const tSTATE kWPCUSM_SetOne = 
{
	WPCUSM_SetOne_en,
	WPCUSM_SetOne_init,
	WPCUSM_SetOne_du,
	WPCUSM_SetOne_ex,
	WPCUSM_SetOne_run,
	NULL
};

static const tSTATE kWPCUSM_SetTwo = 
{
	WPCUSM_SetTwo_en,
	WPCUSM_SetTwo_init,
	WPCUSM_SetTwo_du,
	WPCUSM_SetTwo_ex,
	WPCUSM_SetTwo_run,
	NULL
};

typedef enum
{
	USMSetting_Init = 0u,
	USMSetting_Operating
}e_WPCUSMSetting;

/*******************************************************************************
* Declare  Variables                                                           *
*******************************************************************************/




/*******************************************************************************
* Define Functions                                                             *
*******************************************************************************/
static tSTATE *WPCUSM_Setting_stateCUR = NULL;

/* State : kWPCUSM_SetGuest */
static void WPCUSM_SetGuest_en(void)
{
	Function_ProfileGuestWPCUSM();
}

static tSTATE* WPCUSM_SetGuest_init(void)
{
	return NULL;
}

static void WPCUSM_SetGuest_du(void)
{
	Function_ProfileGuestWPCUSM();
}

static void WPCUSM_SetGuest_ex(void)
{
	/* MISRA-C */
}

static u8 WPCUSM_SetGuest_run(void)
{
	u8 ret = 0u;

	if(GetX(kb_CurProfile) == (u8)kProfileID_Profile1)
	{
		WPCUSM_Setting_stateCUR = transition_exit(WPCUSM_Setting_stateCUR, &kWPCUSM_SetOne);
		WPCUSM_Setting_stateCUR = transition(WPCUSM_Setting_stateCUR, &kWPCUSM_SetOne);
		
		ret = 1u;
	}
	else if(GetX(kb_CurProfile) == (u8)kProfileID_Profile2)
	{
		WPCUSM_Setting_stateCUR = transition_exit(WPCUSM_Setting_stateCUR, &kWPCUSM_SetTwo);
		WPCUSM_Setting_stateCUR = transition(WPCUSM_Setting_stateCUR, &kWPCUSM_SetTwo);
		
		ret = 1u;
	}
	else
	{
		/* MISRA-C */
	}
		
	return ret;
}

/* State : kWPCUSM_SetOne */
static void WPCUSM_SetOne_en(void)
{
	Function_ProfileOneWPCUSM();
}

static tSTATE* WPCUSM_SetOne_init(void)
{
	return NULL;
}

static void WPCUSM_SetOne_du(void)
{
	Function_ProfileOneWPCUSM();
}

static void WPCUSM_SetOne_ex(void)
{
	/* MISRA-C */
}

static u8 WPCUSM_SetOne_run(void)
{
	u8 ret = 0u;

	if(GetX(kb_CurProfile) == (u8)kProfileID_Guest)
	{
		WPCUSM_Setting_stateCUR = transition_exit(WPCUSM_Setting_stateCUR, &kWPCUSM_SetGuest);
		WPCUSM_Setting_stateCUR = transition(WPCUSM_Setting_stateCUR, &kWPCUSM_SetGuest);
		
		ret = 1u;
	}
	else if(GetX(kb_CurProfile) == (u8)kProfileID_Profile2)
	{
		WPCUSM_Setting_stateCUR = transition_exit(WPCUSM_Setting_stateCUR, &kWPCUSM_SetTwo);
		WPCUSM_Setting_stateCUR = transition(WPCUSM_Setting_stateCUR, &kWPCUSM_SetTwo);
		
		ret = 1u;
	}
	else
	{
		/* MISRA-C */
	}
		
	return ret;
}

/* State : kWPCUSM_SetTwo */
static void WPCUSM_SetTwo_en(void)
{
	Function_ProfileTwoWPCUSM();
}

static tSTATE* WPCUSM_SetTwo_init(void)
{
	return NULL;
}

static void WPCUSM_SetTwo_du(void)
{
	Function_ProfileTwoWPCUSM();
}

static void WPCUSM_SetTwo_ex(void)
{
	/* MISRA-C */
}

static u8 WPCUSM_SetTwo_run(void)
{
	u8 ret = 0u;

	if(GetX(kb_CurProfile) == (u8)kProfileID_Guest)
	{
		WPCUSM_Setting_stateCUR = transition_exit(WPCUSM_Setting_stateCUR, &kWPCUSM_SetGuest);
		WPCUSM_Setting_stateCUR = transition(WPCUSM_Setting_stateCUR, &kWPCUSM_SetGuest);
		
		ret = 1u;
	}
	else if(GetX(kb_CurProfile) == (u8)kProfileID_Profile1)
	{
		WPCUSM_Setting_stateCUR = transition_exit(WPCUSM_Setting_stateCUR, &kWPCUSM_SetOne);
		WPCUSM_Setting_stateCUR = transition(WPCUSM_Setting_stateCUR, &kWPCUSM_SetOne);
		
		ret = 1u;
	}
	else
	{
		/* MISRA-C */
	}
		
	return ret;
}

static void Function_ProfileGuestWPCUSM(void)
{	/* CLU_05_00ms_1 */					   /* HU_USM_E_04 */
	if(IsChgEvt(kC_USM_StaRst1Req, On) || IsChgEvt(kC_CF_AVN_CluUSMReset, On))
	{
		SetOutput(kC_USM_CmdWPCSta, (u8)kWPCOnOff_On);
		SetX(kb_WPCSWOption, (u8)kWPCOnOff_On);
		SetX(km_ProfileGuestWPCUSM, (u8)kWPCOnOff_On);
	}/* CLU_09_00ms_1 */									  /* HU_USM_E_02 */	
	else if(IsChgEvt(kC_USM_WpcSetReq, (u8)kWPCOnOff_On) || IsChgEvt(kC_CF_Gway_RWPCNValueSet, (u8)kWPCOnOff_On))
	{
		SetOutput(kC_USM_CmdWPCSta, (u8)kWPCOnOff_On);
		SetX(kb_WPCSWOption, (u8)kWPCOnOff_On);
		SetX(km_ProfileGuestWPCUSM, (u8)kWPCOnOff_On);
	}
	else if(IsChgEvt(kC_USM_WpcSetReq, (u8)kWPCOnOff_Off) || IsChgEvt(kC_CF_Gway_RWPCNValueSet, (u8)kWPCOnOff_Off))
	{
		SetOutput(kC_USM_CmdWPCSta, (u8)kWPCOnOff_Off);
		SetX(kb_WPCSWOption, (u8)kWPCOnOff_Off);
		SetX(km_ProfileGuestWPCUSM, (u8)kWPCOnOff_Off);
	}
	else if(GetX(km_ProfileGuestWPCUSM) == (u8)kWPCOnOff_On)
	{
		SetOutput(kC_USM_CmdWPCSta, (u8)kWPCOnOff_On);
		SetX(kb_WPCSWOption, (u8)kWPCOnOff_On);
	}
	else if(GetX(km_ProfileGuestWPCUSM) == (u8)kWPCOnOff_Off)
	{
		SetOutput(kC_USM_CmdWPCSta, (u8)kWPCOnOff_Off);
		SetX(kb_WPCSWOption, (u8)kWPCOnOff_Off);
	}
	else
	{
		SetOutput(kC_USM_CmdWPCSta, (u8)kWPCOnOff_Off);
		SetX(kb_WPCSWOption, (u8)kWPCOnOff_Off);
		SetX(km_ProfileGuestWPCUSM, (u8)kWPCOnOff_Off);
	}

	if(IsDiffEvt(km_ProfileGuestWPCUSM))
	{
		Set_EepromData_FUNCTION((u8)kFunc_WPCUnknownUSM, GetX(km_ProfileGuestWPCUSM));
		ClrEvt(km_ProfileGuestWPCUSM);
	}

}

static void Function_ProfileOneWPCUSM(void)
{	/* CLU_05_00ms_1 */					   /* HU_USM_E_04 */
	if(IsChgEvt(kC_USM_StaRst1Req, On) || IsChgEvt(kC_CF_AVN_CluUSMReset, On))
	{
		SetOutput(kC_USM_CmdWPCSta, (u8)kWPCOnOff_On);
		SetX(kb_WPCSWOption, (u8)kWPCOnOff_On);
		SetX(km_ProfileOneWPCUSM, (u8)kWPCOnOff_On);
	} /* CLU_09_00ms_1 */									  /* HU_USM_E_02 */				
	else if(IsChgEvt(kC_USM_WpcSetReq, (u8)kWPCOnOff_On) || IsChgEvt(kC_CF_Gway_RWPCNValueSet, (u8)kWPCOnOff_On))
	{
		SetOutput(kC_USM_CmdWPCSta, (u8)kWPCOnOff_On);
		SetX(kb_WPCSWOption, (u8)kWPCOnOff_On);
		SetX(km_ProfileOneWPCUSM, (u8)kWPCOnOff_On);
	}
	else if(IsChgEvt(kC_USM_WpcSetReq, (u8)kWPCOnOff_Off) || IsChgEvt(kC_CF_Gway_RWPCNValueSet, (u8)kWPCOnOff_Off))
	{
		SetOutput(kC_USM_CmdWPCSta, (u8)kWPCOnOff_Off);
		SetX(kb_WPCSWOption, (u8)kWPCOnOff_Off);
		SetX(km_ProfileOneWPCUSM, (u8)kWPCOnOff_Off);
	}
	else if(GetX(km_ProfileOneWPCUSM) == (u8)kWPCOnOff_On)
	{
		SetOutput(kC_USM_CmdWPCSta, (u8)kWPCOnOff_On);
		SetX(kb_WPCSWOption, (u8)kWPCOnOff_On);
	}
	else if(GetX(km_ProfileOneWPCUSM) == (u8)kWPCOnOff_Off)
	{
		SetOutput(kC_USM_CmdWPCSta, (u8)kWPCOnOff_Off);
		SetX(kb_WPCSWOption, (u8)kWPCOnOff_Off);
	}
	else
	{
		SetOutput(kC_USM_CmdWPCSta, (u8)kWPCOnOff_Off);
		SetX(kb_WPCSWOption, (u8)kWPCOnOff_Off);
		SetX(km_ProfileOneWPCUSM, (u8)kWPCOnOff_Off);
	}

	if(IsDiffEvt(km_ProfileOneWPCUSM))
	{
		Set_EepromData_FUNCTION((u8)kFunc_WPCOneUSM, GetX(km_ProfileOneWPCUSM));
		ClrEvt(km_ProfileOneWPCUSM);
	}
}

static void Function_ProfileTwoWPCUSM(void)
{	/* CLU_05_00ms_1 */					   /* HU_USM_E_04 */
	if(IsChgEvt(kC_USM_StaRst1Req, On) || IsChgEvt(kC_CF_AVN_CluUSMReset, On))
	{
		SetOutput(kC_USM_CmdWPCSta, (u8)kWPCOnOff_On);
		SetX(kb_WPCSWOption, (u8)kWPCOnOff_On);
		SetX(km_ProfileTwoWPCUSM, (u8)kWPCOnOff_On);
	}/* CLU_09_00ms_1 */									  /* HU_USM_E_02 */	
	else if(IsChgEvt(kC_USM_WpcSetReq, (u8)kWPCOnOff_On) || IsChgEvt(kC_CF_Gway_RWPCNValueSet, (u8)kWPCOnOff_On))
	{
		SetOutput(kC_USM_CmdWPCSta, (u8)kWPCOnOff_On);
		SetX(kb_WPCSWOption, (u8)kWPCOnOff_On);
		SetX(km_ProfileTwoWPCUSM, (u8)kWPCOnOff_On);
	}
	else if(IsChgEvt(kC_USM_WpcSetReq, (u8)kWPCOnOff_Off) || IsChgEvt(kC_CF_Gway_RWPCNValueSet, (u8)kWPCOnOff_Off))
	{
		SetOutput(kC_USM_CmdWPCSta, (u8)kWPCOnOff_Off);
		SetX(kb_WPCSWOption, (u8)kWPCOnOff_Off);
		SetX(km_ProfileTwoWPCUSM, (u8)kWPCOnOff_Off);
	}
	else if(GetX(km_ProfileTwoWPCUSM) == (u8)kWPCOnOff_On)
	{
		SetOutput(kC_USM_CmdWPCSta, (u8)kWPCOnOff_On);
		SetX(kb_WPCSWOption, (u8)kWPCOnOff_On);
	}
	else if(GetX(km_ProfileTwoWPCUSM) == (u8)kWPCOnOff_Off)
	{
		SetOutput(kC_USM_CmdWPCSta, (u8)kWPCOnOff_Off);
		SetX(kb_WPCSWOption, (u8)kWPCOnOff_Off);
	}
	else
	{
		SetOutput(kC_USM_CmdWPCSta, (u8)kWPCOnOff_Off);
		SetX(kb_WPCSWOption, (u8)kWPCOnOff_Off);
		SetX(km_ProfileTwoWPCUSM, (u8)kWPCOnOff_Off);
	}

	if(IsDiffEvt(km_ProfileTwoWPCUSM))
	{
		Set_EepromData_FUNCTION((u8)kFunc_WPCTwoUSM, GetX(km_ProfileTwoWPCUSM));
		ClrEvt(km_ProfileTwoWPCUSM);
	}
}


/************************************************************************************************/
/****         Function: WPCUSMSetting                             */
/****         Content: WPC USM Setting Function State Chart                   */
/****         Called By: 10ms TASK                                */
/****         argument: void                                  */
/****         return value: void                                */
/****     Revision: 2018.05.25 Applied 14th                         */
/************************************************************************************************/
void WPCUSMSetting(void)
{
  static e_WPCUSMSetting sts_WPCUSMSetting = USMSetting_Init;

	WPCCurrentProfileDecision();
	
	switch(sts_WPCUSMSetting)
	{
		case USMSetting_Init:
			if(GetX(kb_CurProfile) == (u8)kProfileID_Profile1)
			{
				WPCUSM_Setting_stateCUR = &kWPCUSM_SetOne;
				WPCUSM_Setting_stateCUR = transition(WPCUSM_Setting_stateCUR, &kWPCUSM_SetOne);
			}
			else if(GetX(kb_CurProfile) == (u8)kProfileID_Profile2)
			{
				WPCUSM_Setting_stateCUR = &kWPCUSM_SetTwo;
				WPCUSM_Setting_stateCUR = transition(WPCUSM_Setting_stateCUR, &kWPCUSM_SetTwo);
			}
			else
			{
				WPCUSM_Setting_stateCUR = &kWPCUSM_SetGuest;
				WPCUSM_Setting_stateCUR = transition(WPCUSM_Setting_stateCUR, &kWPCUSM_SetGuest);			
			}
			sts_WPCUSMSetting = USMSetting_Operating;
			break;

		case USMSetting_Operating:
			(void)CurrentRun(WPCUSM_Setting_stateCUR);
			break;
			
		default:
			/* MISRA-C */
			break;
	}
}
/************************************************************************************************/
/****         Function: WPC Current Profile Decision															*/
/****         Content: WPC Current Profile Decision Function State Chart										*/
/****         Called By: 10ms TASK																*/
/****         argument: void																	*/
/****         return value: void																*/
/****		Revision: 2018.05.25 Applied 14th													*/
/************************************************************************************************/
void WPCCurrentProfileDecision(void)
{
	//SetQue(kb_CurProfile, (u8)kProfileID_Guest);
	
	if(GetX(kC_IAU_ProfileIDRVal) == (u8)kProfileID_Profile1)	/* IAU_16_200ms */
	{
		SetX(kb_CurProfile, (u8)kProfileID_Profile1);
	}
	else if(GetX(kC_IAU_ProfileIDRVal) == (u8)kProfileID_Profile2)
	{
		SetX(kb_CurProfile, (u8)kProfileID_Profile2);
	}
	else if(GetX(kC_IAU_ProfileIDRVal) == (u8)kProfileID_Guest)
	{
		SetX(kb_CurProfile, (u8)kProfileID_Guest);
	}
	else if(GetX(kC_CF_AVN_ProfileIDRValue) == (u8)kProfileID_Profile1)	/* HU_GW_PE_01 */
	{
		SetX(kb_CurProfile, (u8)kProfileID_Profile1);
	}
	else if(GetX(kC_CF_AVN_ProfileIDRValue) == (u8)kProfileID_Profile2)
	{
		SetX(kb_CurProfile, (u8)kProfileID_Profile2);
	}
	else if(GetX(kC_CF_AVN_ProfileIDRValue) == (u8)kProfileID_Guest)
	{
		SetX(kb_CurProfile, (u8)kProfileID_Guest);
	}
	else
	{
		/* MISRA-C */
	}
}



