/*******************************************************************************
 * Project        :   SP2 IBU
 * File Name      :   can_input.c
 * Compiler   :   Eclipse
 * Author         :   MyoungKwon Choi (mk210@seoyonelec.com)
 * Created at     :   2017-06-23
 * Code Editor  :   Source Insight (Recomended Font : D2Coding / Size 10)
 * Revision       :   Version 0.1
 * Copyright    :   (c) Copyright Seoyon Electronics Co.Ltd. All Rights Reserved
 * Description    :
 *
 ******************************************************************************/




/*******************************************************************************
  Include Headers
*******************************************************************************/
#include "WPCVehicleOption.h"
#include "Std_Types.h"
#include "WPCType.h"
#include "Define.h"
#include "WPCTimer.h"
#include "Data.h"
#include "WPCPWMControl.h"
//#include "eeprom.h"
#include "Rte_SWC_Input.h"
#include "app_input_type.h"
#include "app_input.h"
#include "app_can_input_type.h"
#include "app_can_input.h"

Dcm_MsgContextTypeLocal pMsgContext_Local = {0, 0, 0, {0, }, 0, 0, {0, }};


/*******************************************************************************
  Declare Function Prototypes
*******************************************************************************/
void Input_BCAN(void);
void Input_LCAN(void);

/*******************************************************************************
  Define Functions
*******************************************************************************/







void Input_BCAN(void)
{
  /***************************************************************************
  B-CAN BCM_07_200ms
  ***************************************************************************/

  if (BCAN_App_Ind_BCM_07_200ms == kOn)
  {
    BCAN_App_Ind_BCM_07_200ms = kOff;
	SetX(TimeOut_BCM_07_200ms, kOff);
  }
  else if(BCANTimeOut_BCM_07_200ms == kOn)
  {
	SetX(TimeOut_BCM_07_200ms, kOn);
	
  }
  else
  {
	ClrEvt(kC_Lamp_IntTailLmpOnReq);
  }

  /***************************************************************************
  B-CAN BCM_12_200ms
  ***************************************************************************/
  if (BCAN_App_Ind_BCM_12_200ms == kOn)
  {
    BCAN_App_Ind_BCM_12_200ms = kOff;
    SetX(TimeOut_BCM_12_200ms, kOff);
  }
  else if(BCANTimeOut_BCM_12_200ms == kOn)
  {
	SetX(TimeOut_BCM_12_200ms, kOn);
  }
  else
  {
    ClrEvt(kC_BCM_SmkOptTyp);
  }
   /***************************************************************************
   B-CAN CLU_01_20ms_1
   ***************************************************************************/
  if (BCAN_App_Ind_CLU_01_20ms_1 == kOn)
  {
    BCAN_App_Ind_CLU_01_20ms_1 = kOff;
	SetX(TimeOut_CLU_01_20ms_1, kOff);
  
  }
  else if(BCANTimeOut_CLU_01_20ms_1 == kOn)
  {
	SetX(TimeOut_CLU_01_20ms_1, kOn);
  }
  else
  {
    ClrEvt(kC_CLU_DtntOutSta);
    ClrEvt(kC_CLU_RhstaLvlSta);
  }
   /***************************************************************************
   B-CAN CLU_01_20ms_2
   ***************************************************************************/
  if (BCAN_App_Ind_CLU_01_20ms_2 == kOn)
  {
    BCAN_App_Ind_CLU_01_20ms_2 = kOff;
    SetX(TimeOut_CLU_01_20ms_2, kOff);
  }
  else if(BCANTimeOut_CLU_01_20ms_2  == kOn)
  {
	SetX(TimeOut_CLU_01_20ms_2, kOn);
  }
  else
  {
    ClrEvt(kC_CLU_DisSpdVal_KPH);
    ClrEvt(kC_CLU_AutoBrightSta);
  }
 
#if defined (USE_AUTOBRIGHT)
	SetX(kb_GreenLED_Duty_AutoBright, GetDuty_Que_GreenAutoBright());
	SetX(kb_AmberLED_Duty_AutoBright, GetDuty_Que_AmberAutoBright());
#else
	SetX(kb_LED_Duty, GetDuty_Que());
#endif

   /***************************************************************************
   B-CAN CLU_05_00ms_1
   ***************************************************************************/
  if (BCAN_App_Ind_CLU_05_00ms_1 == kOn)
  {
    BCAN_App_Ind_CLU_05_00ms_1 = kOff;
	SetX(TimeOut_CLU_05_00ms_1, kOff);
  }
  else if(BCANTimeOut_CLU_05_00ms_1 == kOn)
  {
	SetX(TimeOut_CLU_05_00ms_1, kOn);		
  }
  else
  {
    ClrEvt(kC_USM_StaRst1Req);
  }

   /***************************************************************************
   B-CAN CLU_09_00ms_1
   ***************************************************************************/
  if (BCAN_App_Ind_CLU_09_00ms_1 == kOn)
  {
    BCAN_App_Ind_CLU_09_00ms_1 = kOff;
  	SetX(TimeOut_CLU_09_00ms_1, kOff);
  }
  else if(BCANTimeOut_CLU_09_00ms_1 == kOn)
  {
	SetX(TimeOut_CLU_09_00ms_1, kOn);
  }
  else
  {
    ClrEvt(kC_USM_WpcSetReq);
  }

   /***************************************************************************
   B-CAN CLU_20_200ms_1
   ***************************************************************************/
  if (BCAN_App_Ind_CLU_20_200ms_1 == kOn)
  {
    BCAN_App_Ind_CLU_20_200ms_1 = kOff;
 	SetX(TimeOut_CLU_20_200ms_1, kOff);
  }
  else if(BCANTimeOut_CLU_20_200ms_1 == kOn)
  {
	SetX(TimeOut_CLU_20_200ms_1, kOn);
  }
  else
  {
    ClrEvt(kC_CLU_ClusterUSM);
  }

   /***************************************************************************
   B-CAN EMS_02_10ms_1
   ***************************************************************************/

  if (BCAN_App_Ind_EMS_02_10ms_1 == kOn)
  {
    BCAN_App_Ind_EMS_02_10ms_1 = kOff;
	SetX(TimeOut_EMS_02_10ms_1, kOff);
  }
  else if(BCANTimeOut_EMS_02_10ms_1 == kOn)
  {
	SetX(TimeOut_EMS_02_10ms_1, kOn);
  }
  else
  {
    ClrEvt(kC_ENG_EngSta);
  }
   /***************************************************************************
   B-CAN EMS_07_10ms_2
   ***************************************************************************/
  if (BCAN_App_Ind_EMS_07_10ms_2 == kOn)
  {
    BCAN_App_Ind_EMS_07_10ms_2 = kOff;
    SetX(TimeOut_EMS_07_10ms_2, kOff);
  }
  else if(BCANTimeOut_EMS_07_10ms_2 == kOn)
  {
	SetX(TimeOut_EMS_07_10ms_2, kOn);
  }
  else
  {
    ClrEvt(kC_HEV_EngOpSta);
  }
   /***************************************************************************
   B-CAN HCU_03_10ms_2
   ***************************************************************************/
  if (BCAN_App_Ind_HCU_03_10ms_2 == kOn)
  {
    BCAN_App_Ind_HCU_03_10ms_2 = kOff;
	SetX(TimeOut_HCU_03_10ms_2, kOff);
  }
  else if(BCANTimeOut_HCU_03_10ms_2 == kOn)
  {
	SetX(TimeOut_HCU_03_10ms_2, kOn);
  }
  else
  {
    ClrEvt(kC_HCU_HevRdySta);
  }
   /***************************************************************************
   B-CAN HU_GW_PE_01
   ***************************************************************************/
  if (BCAN_App_Ind_HU_GW_PE_01 == kOn)
  {
    BCAN_App_Ind_HU_GW_PE_01 = kOff;
  	SetX(TimeOut_HU_GW_PE_01, kOff);
  }
  else if(BCANTimeOut_HU_GW_PE_01 == kOn)
  {
	SetX(TimeOut_HU_GW_PE_01, kOn);
  }
  else
  {
    ClrEvt(kC_CF_AVN_ProfileIDRValue);
  }

   /***************************************************************************
   B-CAN HU_USM_E_02
   ***************************************************************************/
  if (BCAN_App_Ind_HU_USM_E_02 == kOn)
  {
    BCAN_App_Ind_HU_USM_E_02 = kOff;
	SetX(TimeOut_HU_USM_E_02, kOff);
  }
  else if(BCANTimeOut_HU_USM_E_02 == kOn)
  {
	SetX(TimeOut_HU_USM_E_02, kOn);
  }
  else
  {
    ClrEvt(kC_CF_Gway_RWPCNValueSet);
  }
   /***************************************************************************
   B-CAN HU_USM_E_04
   ***************************************************************************/
  if (BCAN_App_Ind_HU_USM_E_04 == kOn)
  {
    BCAN_App_Ind_HU_USM_E_04 = kOff;
    SetX(TimeOut_HU_USM_E_04, kOff);
  }
  else if(BCANTimeOut_HU_USM_E_04 == kOn)
  {
	SetX(TimeOut_HU_USM_E_04, kOn);
  }
  else
  {
    ClrEvt(kC_CF_AVN_CluUSMReset);
  }
   /***************************************************************************
   B-CAN HU_USM_E_14
   ***************************************************************************/
  if (BCAN_App_Ind_HU_USM_E_14 == kOn)
  {
    BCAN_App_Ind_HU_USM_E_14 = kOff;
    SetX(TimeOut_HU_USM_E_14, kOff);
  }
  else if(BCANTimeOut_HU_USM_E_14 == kOn)
  {
	SetX(TimeOut_HU_USM_E_14, kOn);
  }
  else
  {
    ClrEvt(kC_CF_Gway_WPCAnimationNvalueSet);
  }
   /***************************************************************************
   B-CAN IAU_16_200ms
   ***************************************************************************/
  if (BCAN_App_Ind_IAU_16_200ms == kOn)
  {
    BCAN_App_Ind_IAU_16_200ms = kOff;
    SetX(TimeOut_IAU_16_200ms, kOff);
  }
  else if(BCANTimeOut_IAU_16_200ms == kOn)
  {
	SetX(TimeOut_IAU_16_200ms, kOn);
  }
  else
  {
    //ClrEvt(kC_IAU_DigitalKey2Opt);
    ClrEvt(kC_IAU_ProfileIDRVal);
  }
   /***************************************************************************
   B-CAN ICU_02_200ms
   ***************************************************************************/
  if (BCAN_App_Ind_ICU_02_200ms == kOn)
  {
    BCAN_App_Ind_ICU_02_200ms = kOff;
    SetX(TimeOut_ICU_02_200ms, kOff);
  }
  else if(BCANTimeOut_ICU_02_200ms == kOn)
  {
	SetX(TimeOut_ICU_02_200ms, kOn);
  }
  else
  {
    ClrEvt(kC_Warn_AsstDrSwSta);
	ClrEvt(kC_Warn_DrvDrSwSta);
    ClrEvt(kC_Warn_RrLftDrSwSta);
    ClrEvt(kC_Warn_RrRtDrSwSta);
  }
  /***************************************************************************
  B-CAN SBCM_AST_02_200ms
  ***************************************************************************/
  if (BCAN_App_Ind_SBCM_AST_02_200ms == kOn)
  {
    BCAN_App_Ind_SBCM_AST_02_200ms = kOff;
    SetX(TimeOut_SBCM_AST_02_200ms, kOff);
  }
  else if(BCANTimeOut_SBCM_AST_02_200ms == kOn)
  {
	SetX(TimeOut_SBCM_AST_02_200ms, kOn);
  }
  else
  {
    ClrEvt(kC_Warn_AsstDrSwSta_SBCM);
  }
  /***************************************************************************
  B-CAN SBCM_DRV_01_200ms
  ***************************************************************************/
  if (BCAN_App_Ind_SBCM_DRV_01_200ms == kOn)
  {
    BCAN_App_Ind_SBCM_DRV_01_200ms = kOff;
 	SetX(TimeOut_SBCM_DRV_01_200ms, kOff);
  }
  else if(BCANTimeOut_SBCM_DRV_01_200ms == kOn)
  {
	SetX(TimeOut_SBCM_DRV_01_200ms, kOn);
  }
  else
  {
    ClrEvt(kC_Warn_DrvDrSwSta_SBCM);
    ClrEvt(kC_Latch_TypeOption_DRV);
  }
  /***************************************************************************
  B-CAN SBCM_RL_01_200ms
  ***************************************************************************/
  if (BCAN_App_Ind_SBCM_RL_01_200ms == kOn)
  {
    BCAN_App_Ind_SBCM_RL_01_200ms = kOff;
    SetX(TimeOut_SBCM_RL_01_200ms, kOff);
  }
  else if(BCANTimeOut_SBCM_RL_01_200ms == kOn)
  {
	SetX(TimeOut_SBCM_RL_01_200ms, kOn);
  }
  else
  {
    ClrEvt(kC_Warn_RrLftDrSwSta_SBCM);
  }

  /***************************************************************************
  B-CAN SBCM_RR_01_200ms
  ***************************************************************************/
  if (BCAN_App_Ind_SBCM_RR_01_200ms == kOn)
  {
    BCAN_App_Ind_SBCM_RR_01_200ms = kOff;
  	SetX(TimeOut_SBCM_RR_01_200ms, kOff);
  }
  else if(BCANTimeOut_SBCM_RR_01_200ms == kOn)
  {
	SetX(TimeOut_SBCM_RR_01_200ms, kOn);
  }
  else
  {
    ClrEvt(kC_Warn_RrRtDrSwSta_SBCM);
  }
  /***************************************************************************
  B-CAN SMK_06_200ms
  ***************************************************************************/

  if (BCAN_App_Ind_SMK_06_200ms == kOn)
  {
    BCAN_App_Ind_SMK_06_200ms = kOff;
    SetX(TimeOut_SMK_06_200ms, kOff);
  }
  else if(BCANTimeOut_SMK_06_200ms == kOn)
  {
	SetX(TimeOut_SMK_06_200ms, kOn);
  }
  else
  {
    ClrEvt(kC_LFAnt_SrchSta);
  }
  /***************************************************************************
  B-CAN VCU_01_10ms_1
  ***************************************************************************/
 
  if (BCAN_App_Ind_VCU_01_10ms_1  == kOn)
  {
    BCAN_App_Ind_VCU_01_10ms_1  = kOff;
  	SetX(TimeOut_VCU_01_10ms_1, kOff);
  }
  else if(BCANTimeOut_VCU_01_10ms_1 == kOn)
  {
	SetX(TimeOut_VCU_01_10ms_1, kOn);
  }
  else
  {
    ClrEvt(kC_VCU_EvDrvRdySta);
  }
  /***************************************************************************
  B-CAN WPC2_01_200ms
  ***************************************************************************/
  if (BCAN_App_Ind_WPC2_01_200ms == kOn)
  {
    BCAN_App_Ind_WPC2_01_200ms  = kOff;
  	SetX(TimeOut_WPC2_01_200ms, kOff);
  }
  else if(BCANTimeOut_WPC2_01_200ms == kOn)
  {
	SetX(TimeOut_WPC2_01_200ms, kOn);
  }
  else
  {
    ClrEvt(kC_WPC2_IndSyncVal);
  }
  /***************************************************************************
  B-CAN WPC_01_200ms
  ***************************************************************************/
  if (BCAN_App_Ind_WPC_01_200ms == kOn)
  {
	BCAN_App_Ind_WPC_01_200ms  = kOff;
	SetX(TimeOut_WPC_01_200ms, kOff);
  }
  else if(BCANTimeOut_WPC_01_200ms == kOn)
  {
	SetX(TimeOut_WPC_01_200ms, kOn);
  }
  else
  {
	ClrEvt(kC_WPC_IndSyncVal);
	ClrEvt(kC_USM_CmdWPCIndSta);
  }
}

void Input_LCAN(void)
{
	/* Misra-C */
}
