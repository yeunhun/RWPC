/*******************************************************************************
**                       HYUNDAI-AUTOEVER PVT LTD                             **
********************************************************************************
** Copyright (C) HYUNDAI-AUTOEVER PVT LTD - All Rights Reserved               **
** Unauthorized copying of this file, via any medium is strictly prohibited   **
** Auto generated file                                                        **
*******************************************************************************/
/* Generate On : �� 5�� 23 2022 12:19:17 KST                                    */
/* Generate from : Y:/01_SWP_Backup/kkh_backup/e_ka4_pe_wpc_v200_220519_1     */
/* Code Generation Version : 1.0.2                                            */

#include "Rte_SWC_WPC_Process.h"

/* PROTECTED REGION START ID(User Defined File Inclusion):(SWC_WPC_Process) */
/* Start of user defined code  - Do not remove this comment */
#include "WPCVehicleOption.h"
#include "WPCType.h"
#include "define.h"
#include "data.h"
#include "app_input_type.h"
#include "app_input.h"
#include "app_can_input_type.h"
#include "app_can_input.h"
#include "WPCInitialization.h"
#include "WPCEepControl.h"
#include "WPCLogicControl.h"
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined File Inclusion):(SWC_WPC_Process) */

/* PROTECTED REGION START ID(User Defined Constants):(SWC_WPC_Process) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Constants):(SWC_WPC_Process) */

/* PROTECTED REGION START ID(User Defined Global Variables):(SWC_WPC_Process) */
/* Start of user defined code  - Do not remove this comment */
extern void SleepModeProcessing(void);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Global Variables):(SWC_WPC_Process) */
#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

extern void SleepModeProcessing(void);
FUNC(void, SWC_WPC_Process_CODE) RE_WPC_Process(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/

/* PROTECTED REGION START ID(User Defined Variable):(RE_WPC_Process) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_WPC_Process) */

/* PROTECTED REGION START ID(User Defined Code):(RE_WPC_Process) */
/* Start of user defined code  - Do not remove this comment */

if(WPC_Initialize() == On)
{
  WPCNFCModeControl();

  WPCModeStatusControl();
  PreventionOfSMKLFInterferenceControl();
  OverCurrentDetectingControl();
  TemperatureSensorErrorDetectingControl();
  OverTemperatureDetectingControl();
  WPCUSMSetting();
  //WPCINDCmdStateControl();
  RWPCINDAnimationControl();
#if defined (NFC_ENABLE)
  NFCCommunication();
#else
  nonNFCCommunication();
#endif

if(GetX(kC_USM_CmdWPCIndSta) == kWPCAnimation_Type_2)
{
  WPCLEDAnimationOutputControl();
}
else
{
  WPCLEDOutputControl();
}

  WPCFANControl();
  DTC_B1621_Control();

  SleepModeProcessing();
}

/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_WPC_Process) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"


