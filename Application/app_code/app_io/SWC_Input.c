/*******************************************************************************
**                       HYUNDAI-AUTOEVER PVT LTD                             **
********************************************************************************
** Copyright (C) HYUNDAI-AUTOEVER PVT LTD - All Rights Reserved               **
** Unauthorized copying of this file, via any medium is strictly prohibited   **
** Auto generated file                                                        **
*******************************************************************************/
/* Generate On : �� 5�� 13 2022 15:29:57 KST                                    */
/* Generate from : W:/e_ka4_pe_wpc_v200_220513                                */
/* Code Generation Version : 1.0.2                                            */

#include "Rte_SWC_Input.h"


/* PROTECTED REGION START ID(User Defined File Inclusion):(SWC_Input) */
/* Start of user defined code  - Do not remove this comment */
#include "app_can_input_type.h"
#include "app_can_input.h"
#include "app_input_type.h"
#include "app_input.h"
#include "app_output_type.h"
#include "app_output.h"
#include "app_can_output_type.h"
#include "app_can_output.h"
#include "define.h"
#include "data.h"
#include "WPCInitialization.h"
#include "WPCI2CControl.h"
#include "WPCDiagonostic.h"


/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined File Inclusion):(SWC_Input) */

/* PROTECTED REGION START ID(User Defined Constants):(SWC_Input) */
/* Start of user defined code  - Do not remove this comment */

/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Constants):(SWC_Input) */

/* PROTECTED REGION START ID(User Defined Global Variables):(SWC_Input) */
/* Start of user defined code  - Do not remove this comment */

FUNC(void, CDD_WPCIC_CODE) wpcic_enable(void);
FUNC(void, CDD_WPCIC_CODE) wpcic_disable(void);
FUNC(void, CDD_WPCIC_CODE) VBATSW_EN_Read(void);


tAPP_CAN_INPUT APP_CAN_INPUT_IF;
tAPP_INPUT APP_INPUT_IF;
tAPP_OUTPUT APP_OUTPUT_IF;
tAPP_CAN_OUTPUT APP_CAN_OUTPUT_IF;

stCanAppFlag  BCANTimeOutFlag;
stCanAppFlag  BCANTimeOutFlag1;
stCanAppFlag  LCANTimeOutFlag;
//stCanAppFlag  BCANTimeOutFlag2;
stCanAppFlag  BCANIndFlag;
stCanAppFlag  BCANIndFlag1;
stCanAppFlag  LCANIndFlag;
//stCanAppFlag  BCANIndFlag2;
extern  stCanAppFlag  BCANNmIndFlag;
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Global Variables):(SWC_Input) */
#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, CDD_WPCIC_CODE) VBATSW_EN_Read(void);

FUNC(void, SWC_Input_CODE) RE_Input_10ms_Process(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Write/IWrite/Send API***** */

/* PROTECTED REGION START ID(User Defined Code):(RE_Input_10ms_Process) */
/* Start of user defined code  - Do not remove this comment */

// Batt, Ign Monitoring
  	Input_BatteryVoltage();
  	Input_IGNVoltage();

// Operating Voltage Monitoring
  	Input_CheckOperatingVoltage();

// FAN Locking Monitoring
  	Locking_FAN();

  
    if( (GetX(kb_WPCOption) == (u8)WPCOpt_MP_WPCNFC) && (GetX(kb_NFC_OPTION)==On) )
    {
      Input_BCAN();
      Input_LCAN();
    }
    else
    {
      Input_BCAN();
    }
	DiagStateTimer();
	Input_Local();
	Input_Internal_10ms();

/* After EEPROM Init */
	if(WPC_Initialize() == On)
	{
		WPC_I2C_Process_20ms();
	}
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_Input_10ms_Process) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}

#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"


#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_BCM_07_200ms(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_BCM_07_200ms_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_BCM_07_200ms_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_BCM_07_200ms) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_BCM_07_200ms) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_BCM_07_200ms_0 = Rte_Read_BCAN_BCM_07_200ms_Lamp_IntTailLmpOnReq(&RE_BCAN_BCM_07_200ms_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_BCM_07_200ms) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_BCM_07_200ms = kOn;
  BCANTimeOut_BCM_07_200ms = kOff;
  
  SetX(kC_Lamp_IntTailLmpOnReq, RE_BCAN_BCM_07_200ms_0);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_BCM_07_200ms) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"


#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_BCM_07_200ms_Timeout(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_BCM_07_200ms_Timeout) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_BCM_07_200ms_Timeout) */

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_BCM_07_200ms_Timeout) */
/* Start of user defined code  - Do not remove this comment */
  BCANTimeOut_BCM_07_200ms = kOn;
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_BCM_07_200ms_Timeout) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_CLU_01_20ms_1(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_CLU_01_20ms_1_0;
VAR(uint8, AUTOMATIC) RE_BCAN_CLU_01_20ms_1_1;
VAR(uint8, AUTOMATIC) retRE_BCAN_CLU_01_20ms_1_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_CLU_01_20ms_1_1;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_CLU_01_20ms_1) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_CLU_01_20ms_1) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_CLU_01_20ms_1_0 = Rte_Read_BCAN_CLU_01_20ms_1_CLU_DtntOutSta(&RE_BCAN_CLU_01_20ms_1_0);

retRE_BCAN_CLU_01_20ms_1_1 = Rte_Read_BCAN_CLU_01_20ms_1_CLU_RhstaLvlSta(&RE_BCAN_CLU_01_20ms_1_1);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_CLU_01_20ms_1) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_CLU_01_20ms_1 = kOn;
  BCANTimeOut_CLU_01_20ms_1 = kOff;
  
  SetX(kC_CLU_DtntOutSta, RE_BCAN_CLU_01_20ms_1_0);
  SetX(kC_CLU_RhstaLvlSta, RE_BCAN_CLU_01_20ms_1_1);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_CLU_01_20ms_1) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_CLU_01_20ms_1_Timeout(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_CLU_01_20ms_1_Timeout_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_CLU_01_20ms_1_Timeout_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_CLU_01_20ms_1_Timeout) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_CLU_01_20ms_1_Timeout) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_CLU_01_20ms_1_Timeout_0 = Rte_Read_BCAN_CLU_01_20ms_1_CLU_DtntOutSta(&RE_BCAN_CLU_01_20ms_1_Timeout_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_CLU_01_20ms_1_Timeout) */
/* Start of user defined code  - Do not remove this comment */
  BCANTimeOut_CLU_01_20ms_1 = kOn;
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_CLU_01_20ms_1_Timeout) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_CLU_01_20ms_2(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint16, AUTOMATIC) RE_BCAN_CLU_01_20ms_2_0;
VAR(uint8, AUTOMATIC) RE_BCAN_CLU_01_20ms_2_1;
VAR(uint16, AUTOMATIC) retRE_BCAN_CLU_01_20ms_2_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_CLU_01_20ms_2_1;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_CLU_01_20ms_2) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_CLU_01_20ms_2) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_CLU_01_20ms_2_0 = Rte_Read_BCAN_CLU_01_20ms_2_CLU_DisSpdVal_KPH(&RE_BCAN_CLU_01_20ms_2_0);

retRE_BCAN_CLU_01_20ms_2_1 = Rte_Read_BCAN_CLU_01_20ms_2_CLU_AutoBrightSta(&RE_BCAN_CLU_01_20ms_2_1);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_CLU_01_20ms_2) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_CLU_01_20ms_2 = kOn;
  BCANTimeOut_CLU_01_20ms_2 = kOff;
  
  SetX(kC_CLU_DisSpdVal_KPH, RE_BCAN_CLU_01_20ms_2_0);
  SetX(kC_CLU_AutoBrightSta, RE_BCAN_CLU_01_20ms_2_1);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_CLU_01_20ms_2) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_CLU_01_20ms_2_Timeout(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_CLU_01_20ms_2_Timeout_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_CLU_01_20ms_2_Timeout_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_CLU_01_20ms_2_Timeout) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_CLU_01_20ms_2_Timeout) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_CLU_01_20ms_2_Timeout_0 = Rte_Read_BCAN_CLU_01_20ms_2_CLU_AutoBrightSta(&RE_BCAN_CLU_01_20ms_2_Timeout_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_CLU_01_20ms_2_Timeout) */
/* Start of user defined code  - Do not remove this comment */
  BCANTimeOut_CLU_01_20ms_2 = kOn;
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_CLU_01_20ms_2_Timeout) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_BCM_12_200ms(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_BCM_12_200ms_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_BCM_12_200ms_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_BCM_12_200ms) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_BCM_12_200ms) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_BCM_12_200ms_0 = Rte_Read_BCAN_BCM_12_200ms_BCM_SmkOptTyp(&RE_BCAN_BCM_12_200ms_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_BCM_12_200ms) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_BCM_12_200ms = kOn;
  BCANTimeOut_BCM_12_200ms = kOff;

  SetX(kC_BCM_SmkOptTyp, RE_BCAN_BCM_12_200ms_0);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_BCM_12_200ms) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_BCM_12_200ms_Timeout(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_BCM_12_200ms_Timeout_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_BCM_12_200ms_Timeout_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_BCM_12_200ms_Timeout) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_BCM_12_200ms_Timeout) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_BCM_12_200ms_Timeout_0 = Rte_Read_BCAN_BCM_12_200ms_BCM_SmkOptTyp(&RE_BCAN_BCM_12_200ms_Timeout_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_BCM_12_200ms_Timeout) */
/* Start of user defined code  - Do not remove this comment */
  BCANTimeOut_BCM_12_200ms = kOn;
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_BCM_12_200ms_Timeout) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_SBCM_RL_01_200ms(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_SBCM_RL_01_200ms_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_SBCM_RL_01_200ms_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_SBCM_RL_01_200ms) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_SBCM_RL_01_200ms) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_SBCM_RL_01_200ms_0 = Rte_Read_BCAN_SBCM_RL_01_200ms_Warn_RrLftDrSwSta_SBCM(&RE_BCAN_SBCM_RL_01_200ms_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_SBCM_RL_01_200ms) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_SBCM_RL_01_200ms = kOn;
  BCANTimeOut_SBCM_RL_01_200ms = kOff;
  
  SetX(kC_Warn_RrLftDrSwSta_SBCM, RE_BCAN_SBCM_RL_01_200ms_0);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_SBCM_RL_01_200ms) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_SBCM_RL_01_200ms_Timeout(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_SBCM_RL_01_200ms_Timeout_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_SBCM_RL_01_200ms_Timeout_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_SBCM_RL_01_200ms_Timeout) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_SBCM_RL_01_200ms_Timeout) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_SBCM_RL_01_200ms_Timeout_0 = Rte_Read_BCAN_SBCM_RL_01_200ms_Warn_RrLftDrSwSta_SBCM(&RE_BCAN_SBCM_RL_01_200ms_Timeout_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_SBCM_RL_01_200ms_Timeout) */
/* Start of user defined code  - Do not remove this comment */
  BCANTimeOut_SBCM_RL_01_200ms = kOn;
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_SBCM_RL_01_200ms_Timeout) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_ICU_02_200ms(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_ICU_02_200ms_0;
VAR(uint8, AUTOMATIC) RE_BCAN_ICU_02_200ms_1;
VAR(uint8, AUTOMATIC) RE_BCAN_ICU_02_200ms_2;
VAR(uint8, AUTOMATIC) RE_BCAN_ICU_02_200ms_3;
VAR(uint8, AUTOMATIC) retRE_BCAN_ICU_02_200ms_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_ICU_02_200ms_1;
VAR(uint8, AUTOMATIC) retRE_BCAN_ICU_02_200ms_2;
VAR(uint8, AUTOMATIC) retRE_BCAN_ICU_02_200ms_3;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_ICU_02_200ms) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_ICU_02_200ms) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_ICU_02_200ms_0 = Rte_Read_BCAN_ICU_02_200ms_Warn_AsstDrSwSta(&RE_BCAN_ICU_02_200ms_0);	//AST

retRE_BCAN_ICU_02_200ms_1 = Rte_Read_BCAN_ICU_02_200ms_Warn_DrvDrSwSta(&RE_BCAN_ICU_02_200ms_1);	//DRV

retRE_BCAN_ICU_02_200ms_2 = Rte_Read_BCAN_ICU_02_200ms_Warn_RrLftDrSwSta(&RE_BCAN_ICU_02_200ms_2);	//RLD

retRE_BCAN_ICU_02_200ms_3 = Rte_Read_BCAN_ICU_02_200ms_Warn_RrRtDrSwSta(&RE_BCAN_ICU_02_200ms_3);	//RR


/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_ICU_02_200ms) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_ICU_02_200ms = kOn;
  BCANTimeOut_ICU_02_200ms = kOff;
  
  SetX(kC_Warn_AsstDrSwSta, RE_BCAN_ICU_02_200ms_0);
  SetX(kC_Warn_DrvDrSwSta, RE_BCAN_ICU_02_200ms_1);
  SetX(kC_Warn_RrLftDrSwSta, RE_BCAN_ICU_02_200ms_2);
  SetX(kC_Warn_RrRtDrSwSta, RE_BCAN_ICU_02_200ms_3);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_ICU_02_200ms) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_ICU_02_200ms_Timeout(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_ICU_02_200ms_Timeout_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_ICU_02_200ms_Timeout_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_ICU_02_200ms_Timeout) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_ICU_02_200ms_Timeout) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_ICU_02_200ms_Timeout_0 = Rte_Read_BCAN_ICU_02_200ms_Warn_AsstDrSwSta(&RE_BCAN_ICU_02_200ms_Timeout_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_ICU_02_200ms_Timeout) */
/* Start of user defined code  - Do not remove this comment */
  BCANTimeOut_ICU_02_200ms = kOn;
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_ICU_02_200ms_Timeout) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_EMS_07_10ms_2(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_EMS_07_10ms_2_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_EMS_07_10ms_2_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_EMS_07_10ms_2) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_EMS_07_10ms_2) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_EMS_07_10ms_2_0 = Rte_Read_BCAN_EMS_07_10ms_2_HEV_EngOpSta(&RE_BCAN_EMS_07_10ms_2_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_EMS_07_10ms_2) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_EMS_07_10ms_2 = kOn;
  BCANTimeOut_EMS_07_10ms_2 = kOff;
  
  SetX(kC_HEV_EngOpSta, RE_BCAN_EMS_07_10ms_2_0);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_EMS_07_10ms_2) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_EMS_07_10ms_2_Timeout(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_EMS_07_10ms_2_Timeout_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_EMS_07_10ms_2_Timeout_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_EMS_07_10ms_2_Timeout) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_EMS_07_10ms_2_Timeout) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_EMS_07_10ms_2_Timeout_0 = Rte_Read_BCAN_EMS_07_10ms_2_HEV_EngOpSta(&RE_BCAN_EMS_07_10ms_2_Timeout_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_EMS_07_10ms_2_Timeout) */
/* Start of user defined code  - Do not remove this comment */
  BCANTimeOut_EMS_07_10ms_2 = kOn;
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_EMS_07_10ms_2_Timeout) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_SBCM_RR_01_200ms(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_SBCM_RR_01_200ms_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_SBCM_RR_01_200ms_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_SBCM_RR_01_200ms) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_SBCM_RR_01_200ms) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_SBCM_RR_01_200ms_0 = Rte_Read_BCAN_SBCM_RR_01_200ms_Warn_RrRtDrSwSta_SBCM(&RE_BCAN_SBCM_RR_01_200ms_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_SBCM_RR_01_200ms) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_SBCM_RR_01_200ms = kOn;
  BCANTimeOut_SBCM_RR_01_200ms = kOff;
  
  SetX(kC_Warn_RrRtDrSwSta_SBCM, RE_BCAN_SBCM_RR_01_200ms_0);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_SBCM_RR_01_200ms) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_SBCM_RR_01_200ms_Timeout(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_SBCM_RR_01_200ms_Timeout_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_SBCM_RR_01_200ms_Timeout_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_SBCM_RR_01_200ms_Timeout) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_SBCM_RR_01_200ms_Timeout) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_SBCM_RR_01_200ms_Timeout_0 = Rte_Read_BCAN_SBCM_RR_01_200ms_Warn_RrRtDrSwSta_SBCM(&RE_BCAN_SBCM_RR_01_200ms_Timeout_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_SBCM_RR_01_200ms_Timeout) */
/* Start of user defined code  - Do not remove this comment */
  BCANTimeOut_SBCM_RR_01_200ms = kOn;
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_SBCM_RR_01_200ms_Timeout) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_IAU_16_200ms(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */

VAR(uint8, AUTOMATIC) RE_BCAN_IAU_16_200ms_1;
VAR(uint8, AUTOMATIC) retRE_BCAN_IAU_16_200ms_1;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_IAU_16_200ms) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_IAU_16_200ms) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_IAU_16_200ms_1 = Rte_Read_BCAN_IAU_16_200ms_IAU_ProfileIDRVal(&RE_BCAN_IAU_16_200ms_1);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_IAU_16_200ms) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_IAU_16_200ms = kOn;
  BCANTimeOut_IAU_16_200ms = kOff;
  
  SetX(kC_IAU_ProfileIDRVal, RE_BCAN_IAU_16_200ms_1);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_IAU_16_200ms) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_IAU_16_200ms_Timeout(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_IAU_16_200ms_Timeout_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_IAU_16_200ms_Timeout_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_IAU_16_200ms_Timeout) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_IAU_16_200ms_Timeout) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_IAU_16_200ms_Timeout_0 = Rte_Read_BCAN_IAU_16_200ms_IAU_ProfileIDRVal(&RE_BCAN_IAU_16_200ms_Timeout_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_IAU_16_200ms_Timeout) */
/* Start of user defined code  - Do not remove this comment */
  BCANTimeOut_IAU_16_200ms = kOn;
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_IAU_16_200ms_Timeout) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_VCU_01_10ms_1(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_VCU_01_10ms_1_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_VCU_01_10ms_1_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_VCU_01_10ms_1) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_VCU_01_10ms_1) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_VCU_01_10ms_1_0 = Rte_Read_BCAN_VCU_01_10ms_1_VCU_EvDrvRdySta(&RE_BCAN_VCU_01_10ms_1_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_VCU_01_10ms_1) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_VCU_01_10ms_1 = kOn;
  BCANTimeOut_VCU_01_10ms_1 = kOff;
  
  SetX(kC_VCU_EvDrvRdySta, RE_BCAN_VCU_01_10ms_1_0);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_VCU_01_10ms_1) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_VCU_01_10ms_1_Timeout(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_VCU_01_10ms_1_Timeout_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_VCU_01_10ms_1_Timeout_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_VCU_01_10ms_1_Timeout) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_VCU_01_10ms_1_Timeout) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_VCU_01_10ms_1_Timeout_0 = Rte_Read_BCAN_VCU_01_10ms_1_VCU_EvDrvRdySta(&RE_BCAN_VCU_01_10ms_1_Timeout_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_VCU_01_10ms_1_Timeout) */
/* Start of user defined code  - Do not remove this comment */
  BCANTimeOut_VCU_01_10ms_1 = kOn;
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_VCU_01_10ms_1_Timeout) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_HU_GW_PE_01(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_HU_GW_PE_01_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_HU_GW_PE_01_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_HU_GW_PE_01) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_HU_GW_PE_01) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_HU_GW_PE_01_0 = Rte_Read_BCAN_HU_GW_PE_01_CF_AVN_ProfileIDRValue(&RE_BCAN_HU_GW_PE_01_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_HU_GW_PE_01) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_HU_GW_PE_01 = kOn;
  BCANTimeOut_HU_GW_PE_01 = kOff;
  
  SetX(kC_CF_AVN_ProfileIDRValue, RE_BCAN_HU_GW_PE_01_0);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_HU_GW_PE_01) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_HU_GW_PE_01_Timeout(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_HU_GW_PE_01_Timeout_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_HU_GW_PE_01_Timeout_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_HU_GW_PE_01_Timeout) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_HU_GW_PE_01_Timeout) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_HU_GW_PE_01_Timeout_0 = Rte_Read_BCAN_HU_GW_PE_01_CF_AVN_ProfileIDRValue(&RE_BCAN_HU_GW_PE_01_Timeout_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_HU_GW_PE_01_Timeout) */
/* Start of user defined code  - Do not remove this comment */
  BCANTimeOut_HU_GW_PE_01 = kOn;
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_HU_GW_PE_01_Timeout) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_EMS_02_10ms_1(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_EMS_02_10ms_1_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_EMS_02_10ms_1_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_EMS_02_10ms_1) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_EMS_02_10ms_1) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_EMS_02_10ms_1_0 = Rte_Read_BCAN_EMS_02_10ms_1_ENG_EngSta(&RE_BCAN_EMS_02_10ms_1_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_EMS_02_10ms_1) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_EMS_02_10ms_1 = kOn;
  BCANTimeOut_EMS_02_10ms_1 = kOff;
  
  SetX(kC_ENG_EngSta, RE_BCAN_EMS_02_10ms_1_0);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_EMS_02_10ms_1) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_EMS_02_10ms_1_Timeout(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_EMS_02_10ms_1_Timeout_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_EMS_02_10ms_1_Timeout_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_EMS_02_10ms_1_Timeout) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_EMS_02_10ms_1_Timeout) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_EMS_02_10ms_1_Timeout_0 = Rte_Read_BCAN_EMS_02_10ms_1_ENG_EngSta(&RE_BCAN_EMS_02_10ms_1_Timeout_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_EMS_02_10ms_1_Timeout) */
/* Start of user defined code  - Do not remove this comment */
  BCANTimeOut_EMS_02_10ms_1 = kOn;
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_EMS_02_10ms_1_Timeout) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_SBCM_DRV_01_200ms(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_SBCM_DRV_01_200ms_0;
VAR(uint8, AUTOMATIC) RE_BCAN_SBCM_DRV_01_200ms_1;
VAR(uint8, AUTOMATIC) retRE_BCAN_SBCM_DRV_01_200ms_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_SBCM_DRV_01_200ms_1;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_SBCM_DRV_01_200ms) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_SBCM_DRV_01_200ms) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_SBCM_DRV_01_200ms_0 = Rte_Read_BCAN_SBCM_DRV_01_200ms_Warn_DrvDrSwSta_SBCM(&RE_BCAN_SBCM_DRV_01_200ms_0);
retRE_BCAN_SBCM_DRV_01_200ms_1 = Rte_Read_BCAN_SBCM_DRV_01_200ms_Latch_TypeOption_DRV(&RE_BCAN_SBCM_DRV_01_200ms_1);


/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_SBCM_DRV_01_200ms) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_SBCM_DRV_01_200ms = kOn;
  BCANTimeOut_SBCM_DRV_01_200ms = kOff;
  
  SetX(kC_Warn_DrvDrSwSta_SBCM, RE_BCAN_SBCM_DRV_01_200ms_0);
  SetX(kC_Latch_TypeOption_DRV, RE_BCAN_SBCM_DRV_01_200ms_1);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_SBCM_DRV_01_200ms) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_SBCM_DRV_01_200ms_Timeout(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_SBCM_DRV_01_200ms_Timeout_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_SBCM_DRV_01_200ms_Timeout_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_SBCM_DRV_01_200ms_Timeout) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_SBCM_DRV_01_200ms_Timeout) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_SBCM_DRV_01_200ms_Timeout_0 = Rte_Read_BCAN_SBCM_DRV_01_200ms_Warn_DrvDrSwSta_SBCM(&RE_BCAN_SBCM_DRV_01_200ms_Timeout_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_SBCM_DRV_01_200ms_Timeout) */
/* Start of user defined code  - Do not remove this comment */
  BCANTimeOut_SBCM_DRV_01_200ms = kOn;
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_SBCM_DRV_01_200ms_Timeout) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_SMK_06_200ms(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_SMK_06_200ms_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_SMK_06_200ms_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_SMK_06_200ms) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_SMK_06_200ms) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_SMK_06_200ms_0 = Rte_Read_BCAN_SMK_06_200ms_LFAnt_SrchSta(&RE_BCAN_SMK_06_200ms_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_SMK_06_200ms) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_SMK_06_200ms = kOn;
  BCANTimeOut_SMK_06_200ms = kOff;
  
  SetX(kC_LFAnt_SrchSta, RE_BCAN_SMK_06_200ms_0);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_SMK_06_200ms) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_SMK_06_200ms_Timeout(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_SMK_06_200ms_Timeout_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_SMK_06_200ms_Timeout_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_SMK_06_200ms_Timeout) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_SMK_06_200ms_Timeout) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_SMK_06_200ms_Timeout_0 = Rte_Read_BCAN_SMK_06_200ms_LFAnt_SrchSta(&RE_BCAN_SMK_06_200ms_Timeout_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_SMK_06_200ms_Timeout) */
/* Start of user defined code  - Do not remove this comment */
  BCANTimeOut_SMK_06_200ms = kOn;
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_SMK_06_200ms_Timeout) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_SBCM_AST_02_200ms(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_SBCM_AST_02_200ms_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_SBCM_AST_02_200ms_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_SBCM_AST_02_200ms) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_SBCM_AST_02_200ms) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_SBCM_AST_02_200ms_0 = Rte_Read_BCAN_SBCM_AST_02_200ms_Warn_AsstDrSwSta_SBCM(&RE_BCAN_SBCM_AST_02_200ms_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_SBCM_AST_02_200ms) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_SBCM_AST_02_200ms = kOn;
  BCANTimeOut_SBCM_AST_02_200ms = kOff;
  
  SetX(kC_Warn_AsstDrSwSta_SBCM, RE_BCAN_SBCM_AST_02_200ms_0);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_SBCM_AST_02_200ms) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_SBCM_AST_02_200ms_Timeout(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_SBCM_AST_02_200ms_Timeout_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_SBCM_AST_02_200ms_Timeout_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_SBCM_AST_02_200ms_Timeout) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_SBCM_AST_02_200ms_Timeout) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_SBCM_AST_02_200ms_Timeout_0 = Rte_Read_BCAN_SBCM_AST_02_200ms_Warn_AsstDrSwSta_SBCM(&RE_BCAN_SBCM_AST_02_200ms_Timeout_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_SBCM_AST_02_200ms_Timeout) */
/* Start of user defined code  - Do not remove this comment */
  BCANTimeOut_SBCM_AST_02_200ms = kOn;
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_SBCM_AST_02_200ms_Timeout) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"


#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_HU_USM_E_04(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_HU_USM_E_04_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_HU_USM_E_04_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_HU_USM_E_04) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_HU_USM_E_04) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_HU_USM_E_04_0 = Rte_Read_BCAN_HU_USM_E_04_CF_AVN_CluUSMReset(&RE_BCAN_HU_USM_E_04_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_HU_USM_E_04) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_HU_USM_E_04 = kOn;
  BCANTimeOut_HU_USM_E_04 = kOff;
  
  SetX(kC_CF_AVN_CluUSMReset, RE_BCAN_HU_USM_E_04_0);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_HU_USM_E_04) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_HU_USM_E_02(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_HU_USM_E_02_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_HU_USM_E_02_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_HU_USM_E_02) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_HU_USM_E_02) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_HU_USM_E_02_0 = Rte_Read_BCAN_HU_USM_E_02_CF_Gway_RWPCNValueSet(&RE_BCAN_HU_USM_E_02_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_HU_USM_E_02) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_HU_USM_E_02 = kOn;
  BCANTimeOut_HU_USM_E_02 = kOff;
  
  SetX(kC_CF_Gway_RWPCNValueSet, RE_BCAN_HU_USM_E_02_0);	//RWPC
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_HU_USM_E_02) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_HU_USM_E_14(void)
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_HU_USM_E_14_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_HU_USM_E_14_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_HU_USM_E_04) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_HU_USM_E_04) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_HU_USM_E_14_0 = Rte_Read_BCAN_HU_USM_E_14_CF_Gway_WPCAnimationNvalueSet(&RE_BCAN_HU_USM_E_14_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_HU_USM_E_04) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_HU_USM_E_14 = kOn;
  BCANTimeOut_HU_USM_E_04 = kOff;

  SetX(kC_CF_Gway_WPCAnimationNvalueSet, RE_BCAN_HU_USM_E_14_0);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_HU_USM_E_04) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_HCU_03_10ms_2(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_HCU_03_10ms_2_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_HCU_03_10ms_2_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_HCU_03_10ms_2) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_HCU_03_10ms_2) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_HCU_03_10ms_2_0 = Rte_Read_BCAN_HCU_03_10ms_2_HCU_HevRdySta(&RE_BCAN_HCU_03_10ms_2_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_HCU_03_10ms_2) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_HCU_03_10ms_2 = kOn;
  BCANTimeOut_HCU_03_10ms_2 = kOff;
  
  SetX(kC_HCU_HevRdySta, RE_BCAN_HCU_03_10ms_2_0);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_HCU_03_10ms_2) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_HCU_03_10ms_2_Timeout(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_HCU_03_10ms_2_Timeout_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_HCU_03_10ms_2_Timeout_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_HCU_03_10ms_2_Timeout) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_HCU_03_10ms_2_Timeout) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_HCU_03_10ms_2_Timeout_0 = Rte_Read_BCAN_HCU_03_10ms_2_HCU_HevRdySta(&RE_BCAN_HCU_03_10ms_2_Timeout_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_HCU_03_10ms_2_Timeout) */
/* Start of user defined code  - Do not remove this comment */
  BCANTimeOut_HCU_03_10ms_2 = kOn;
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_HCU_03_10ms_2_Timeout) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_ATS_00_00ms(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_ATS_00_00ms_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_ATS_00_00ms_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_BCM_07_200ms) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_BCM_07_200ms) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_ATS_00_00ms_0 = Rte_Read_BCAN_ATS_00_00ms_ATS_RWPC_RWPCNValueSet(&RE_BCAN_ATS_00_00ms_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_BCM_07_200ms) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_ATS_00_00ms = kOn;
  BCANTimeOut_ATS_00_00ms = kOff;
  
  SetX(kC_ATS_RWPC_RWPCNValueSet, BCAN_App_Ind_ATS_00_00ms);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_BCM_07_200ms) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/

/********************************************** App Code **********************************************/
	//BCAN_BCM_07_200ms = On;
   // BCANTimeout_BCM_07_200ms = Off;

	//SetQue(kC_IntTailOn, RE_BCAN_BCM_07_200ms_0);
/********************************************** App Code **********************************************/	
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_WPC2_01_200ms(void)
{
/*****************************************************************************/
/*				 Start of Runnable											 */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_WPC2_01_200ms_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_WPC2_01_200ms_0;
/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_HCU_03_10ms_2) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_HCU_03_10ms_2) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_WPC2_01_200ms_0 = Rte_Read_BCAN_WPC2_01_200ms_WPC2_IndSyncVal(&RE_BCAN_WPC2_01_200ms_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_HCU_03_10ms_2) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_WPC2_01_200ms = kOn;
  BCANTimeOut_WPC2_01_200ms = kOff;
  
  SetX(kC_WPC2_IndSyncVal, RE_BCAN_WPC2_01_200ms_0);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_HCU_03_10ms_2) */
/*****************************************************************************/
/*				 End of Runnable											 */
/*****************************************************************************/

}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_WPC2_01_200ms_Timeout(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_WPC2_01_200ms_Timeout_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_WPC2_01_200ms_Timeout_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_HCU_03_10ms_2_Timeout) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_HCU_03_10ms_2_Timeout) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_WPC2_01_200ms_Timeout_0 = Rte_Read_BCAN_WPC2_01_200ms_WPC2_IndSyncVal(&RE_BCAN_WPC2_01_200ms_Timeout_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_HCU_03_10ms_2_Timeout) */
/* Start of user defined code  - Do not remove this comment */
  BCANTimeOut_WPC2_01_200ms = kOn;
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_HCU_03_10ms_2_Timeout) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_WPC_01_200ms(void)
{
/*****************************************************************************/
/*				 Start of Runnable											 */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_WPC_01_200ms_0;
VAR(uint8, AUTOMATIC) RE_BCAN_WPC_01_200ms_1;
VAR(uint8, AUTOMATIC) retRE_BCAN_WPC_01_200ms_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_WPC_01_200ms_1;
/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_HCU_03_10ms_2) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_HCU_03_10ms_2) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_WPC_01_200ms_0 = Rte_Read_BCAN_WPC_01_200ms_WPC_IndSyncVal(&RE_BCAN_WPC_01_200ms_0);
retRE_BCAN_WPC_01_200ms_1 = Rte_Read_BCAN_WPC_01_200ms_USM_CmdWPCIndSta(&RE_BCAN_WPC_01_200ms_1);


/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_HCU_03_10ms_2) */
/* Start of user defined code  - Do not remove this comment */
  BCAN_App_Ind_WPC_01_200ms = kOn;
  BCANTimeOut_WPC_01_200ms = kOff;
  
  SetX(kC_WPC_IndSyncVal, RE_BCAN_WPC_01_200ms_0);
  SetX(kC_USM_CmdWPCIndSta, RE_BCAN_WPC_01_200ms_1);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_HCU_03_10ms_2) */
/*****************************************************************************/
/*				 End of Runnable											 */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_BCAN_WPC_01_200ms_Timeout(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
VAR(uint8, AUTOMATIC) RE_BCAN_WPC_01_200ms_Timeout_0;
VAR(uint8, AUTOMATIC) retRE_BCAN_WPC_01_200ms_Timeout_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_HCU_03_10ms_2_Timeout) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_HCU_03_10ms_2_Timeout) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

retRE_BCAN_WPC_01_200ms_Timeout_0 = Rte_Read_BCAN_WPC_01_200ms_WPC_IndSyncVal(&RE_BCAN_WPC_01_200ms_Timeout_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_HCU_03_10ms_2_Timeout) */
/* Start of user defined code  - Do not remove this comment */
  BCANTimeOut_WPC_01_200ms = kOn;
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_HCU_03_10ms_2_Timeout) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"

#define SWC_Input_START_SEC_CODE
#include "SWC_Input_MemMap.h"
FUNC(void, SWC_Input_CODE) RE_LOCALCAN_TP_BDC_C_WPC(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Read/DRead/Receive API***** */
//VAR(uint8, AUTOMATIC) RE_LOCALCAN_TP_BDC_C_WPC_0;
//VAR(uint8, AUTOMATIC) retRE_LOCALCAN_TP_BDC_C_WPC_0;


/* PROTECTED REGION START ID(User Defined Variable):(RE_BCAN_HCU_03_10ms_2_Timeout) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_BCAN_HCU_03_10ms_2_Timeout) */

/* **********************Rte Read/IRead/DRead/Receive API************************ */

//retRE_LOCALCAN_TP_BDC_C_WPC_0 = Rte_Receive_LOCALCAN_TP_BDC_C_WPC_LOCALCAN_TP_BDC_C_WPC_signal(&RE_LOCALCAN_TP_BDC_C_WPC_0);

/* PROTECTED REGION START ID(User Defined Code):(RE_BCAN_HCU_03_10ms_2_Timeout) */
/* Start of user defined code  - Do not remove this comment */
 LCAN_App_Ind_TP_BDC_C_WPC = kOn;
 SetX(kS_IAU_RSPS, On);
 SetX(kS_WPC_RQST, Off);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_BCAN_HCU_03_10ms_2_Timeout) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Input_STOP_SEC_CODE
#include "SWC_Input_MemMap.h"
