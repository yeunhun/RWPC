/*******************************************************************************
**                       HYUNDAI-AUTOEVER PVT LTD                             **
********************************************************************************
** Copyright (C) HYUNDAI-AUTOEVER PVT LTD - All Rights Reserved               **
** Unauthorized copying of this file, via any medium is strictly prohibited   **
** Auto generated file                                                        **
*******************************************************************************/
/* Generate On : �� 4�� 25 2022 16:45:55 KST                                    */
/* Generate from : V:/SWP/05_WPC_KA4_PE/e_ka4_pe_wpc_v200                     */
/* Code Generation Version : 1.0.2                                            */
#include "WPCType.h"
#include "define.h"
#include "Data.h"

#include "app_input_type.h"
#include "app_input.h"
#include "app_output_type.h"
#include "app_output.h"
#include "WPCOutput.h"
#include "app_can_output_type.h"
#include "app_can_output.h"

#include "WPCInitialization.h"
#include "Rte_SWC_Output.h"


/* PROTECTED REGION START ID(User Defined File Inclusion):(SWC_Output) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined File Inclusion):(SWC_Output) */

/* PROTECTED REGION START ID(User Defined Constants):(SWC_Output) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Constants):(SWC_Output) */

/* PROTECTED REGION START ID(User Defined Global Variables):(SWC_Output) */
/* Start of user defined code  - Do not remove this comment */

/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Global Variables):(SWC_Output) */

//tAPP_OUTPUT APP_OUTPUT_IF;
extern Dcm_MsgContextTypeLocal pMsgContext_Local;

#define SWC_Output_START_SEC_CODE
#include "SWC_Output_MemMap.h"

FUNC(void, SWC_Output_CODE) RE_Output_10ms_Process(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Write/IWrite/Send API***** */

/* **********************Rte Write/Send API************************ */
if(WPC_Initialize() == On)
{
(void)Rte_Write_BCAN_RWPC_01_200ms_RWPC_IndSyncVal(GetX(kC_RWPC_IndSyncVal));
(void)Rte_Write_BCAN_RWPC_01_200ms_USM_ValCmdSta(GetX(kC_USM_CmdWPCSta));
(void)Rte_Write_BCAN_RWPC_01_200ms_USM_ValCmdStaforATS(GetX(kC_USM_ValCmdStaforATS));
(void)Rte_Write_BCAN_RWPC_01_200ms_WPC_PhnLftWrngRWPCSta(GetX(kC_WPC_PhnLftWrngRWPCSta));
(void)Rte_Write_BCAN_RWPC_01_200ms_RWPC_SWVerMajor1(GetX(kC_RWPC_SWVerMajor1));
(void)Rte_Write_BCAN_RWPC_01_200ms_RWPC_SWVerMinor1(GetX(kC_RWPCSWVerMinor1));
(void)Rte_Write_BCAN_RWPC_01_200ms_RWPC_SWVerMinor2(GetX(kC_RWPCSWVerMinor2));
/* PROTECTED REGION START ID(User Defined Code):(RE_Output_10ms_Process) */
/* Start of user defined code  - Do not remove this comment */

	Output_Processing();
}

/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_Output_10ms_Process) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_Output_STOP_SEC_CODE
#include "SWC_Output_MemMap.h"



/* PROTECTED REGION START ID(User Defined Constants):(SWC_Input) */
/* Start of user defined code  - Do not remove this comment */
void DigDir_VBATSW_EN_tmp(uint8 data);
void DigDir_VBATSW_EN_tmp(uint8 data)
{
  Rte_Call_SWC_Output_R_DigDir_VBATSW_EN_WriteDirect(data);
}

/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Constants):(SWC_Input) */



/* PROTECTED REGION START ID(User Defined Constants):(SWC_Input) */
/* Start of user defined code  - Do not remove this comment */
FUNC(void, SWC_Output_CODE) Start_WPCDiagState(void)
{ /* 5s timer Check */
  SetOutput(kC_WPCDiagState, On);
  SetX(kb_WPCDiagStateTimerStart, On);
}

/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Constants):(SWC_Input) */
