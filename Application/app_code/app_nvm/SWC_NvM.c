/*******************************************************************************
**                       HYUNDAI-AUTOEVER PVT LTD                             **
********************************************************************************
** Copyright (C) HYUNDAI-AUTOEVER PVT LTD - All Rights Reserved               **
** Unauthorized copying of this file, via any medium is strictly prohibited   **
** Auto generated file                                                        **
*******************************************************************************/
/* Generate On : ȭ 5�� 17 2022 13:36:36 KST                                    */
/* Generate from : V:/SWP/05_WPC_KA4_PE/e_ka4_pe_wpc_v200_slpwup              */
/* Code Generation Version : 1.0.2                                            */

#include "Rte_SWC_NvM.h"

/* PROTECTED REGION START ID(User Defined File Inclusion):(SWC_NvM) */
/* Start of user defined code  - Do not remove this comment */
#include "Nvm.h"
#include "App_NvM_RamBlock.h"
#include "WPCEepControl.h"
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined File Inclusion):(SWC_NvM) */

/* PROTECTED REGION START ID(User Defined Constants):(SWC_NvM) */
/* Start of user defined code  - Do not remove this comment */
void Callback_NVM_DATA(uint16 rcv_source, uint8 rcv_serviceId, uint8 rcv_jobResult);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Constants):(SWC_NvM) */

/* PROTECTED REGION START ID(User Defined Global Variables):(SWC_NvM) */
/* Start of user defined code  - Do not remove this comment */
extern void WriteEepData(uint8 Block, uint8 WriteReq, ConstVoidPtr *EepData);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Global Variables):(SWC_NvM) */
#define SWC_NvM_START_SEC_CODE
#include "SWC_NvM_MemMap.h"

FUNC(void, SWC_NvM_CODE) RE_NvM_10ms_Process(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
/* *****Local Variable Declaration for Rte Write/IWrite/Send API***** */
#if 0
VAR(tVAR, AUTOMATIC) RE_NvM_10ms_Process_0;
VAR(NvM_RequestResultType, AUTOMATIC) RE_NvM_10ms_Process_00;
VAR(VoidPtr, AUTOMATIC) RE_NvM_10ms_Process_10;
VAR(ConstVoidPtr, AUTOMATIC) RE_NvM_10ms_Process_20;
VAR(NvM_RequestResultType, AUTOMATIC) RE_NvM_10ms_Process_30;
VAR(VoidPtr, AUTOMATIC) RE_NvM_10ms_Process_40;
VAR(ConstVoidPtr, AUTOMATIC) RE_NvM_10ms_Process_50;
VAR(NvM_RequestResultType, AUTOMATIC) RE_NvM_10ms_Process_60;
VAR(VoidPtr, AUTOMATIC) RE_NvM_10ms_Process_70;
VAR(ConstVoidPtr, AUTOMATIC) RE_NvM_10ms_Process_80;
VAR(NvM_RequestResultType, AUTOMATIC) RE_NvM_10ms_Process_90;
VAR(VoidPtr, AUTOMATIC) RE_NvM_10ms_Process_100;
VAR(ConstVoidPtr, AUTOMATIC) RE_NvM_10ms_Process_110;
VAR(NvM_RequestResultType, AUTOMATIC) RE_NvM_10ms_Process_120;
VAR(VoidPtr, AUTOMATIC) RE_NvM_10ms_Process_130;
VAR(ConstVoidPtr, AUTOMATIC) RE_NvM_10ms_Process_140;
VAR(NvM_RequestResultType, AUTOMATIC) RE_NvM_10ms_Process_150;
VAR(VoidPtr, AUTOMATIC) RE_NvM_10ms_Process_160;
VAR(ConstVoidPtr, AUTOMATIC) RE_NvM_10ms_Process_170;
VAR(NvM_RequestResultType, AUTOMATIC) RE_NvM_10ms_Process_180;
VAR(VoidPtr, AUTOMATIC) RE_NvM_10ms_Process_190;
VAR(ConstVoidPtr, AUTOMATIC) RE_NvM_10ms_Process_200;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_0;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_1;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_2;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_3;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_4;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_5;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_6;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_7;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_8;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_9;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_10;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_11;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_12;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_13;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_14;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_15;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_16;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_17;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_18;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_19;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_20;
VAR(Std_ReturnType, AUTOMATIC) retRE_NvM_10ms_Process_0;
#endif
/* PROTECTED REGION START ID(User Defined Variable):(RE_NvM_10ms_Process) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_NvM_10ms_Process) */
/* **********************Rte Synchronous Call API************************ */
#if 0
retRE_NvM_10ms_Process_0 = Rte_Call_PS_NvMBlock_DTCInfo_GetErrorStatus(&RE_NvM_10ms_Process_00);
retRE_NvM_10ms_Process_1 = Rte_Call_PS_NvMBlock_DTCInfo_ReadBlock(RE_NvM_10ms_Process_10);
retRE_NvM_10ms_Process_2 = Rte_Call_PS_NvMBlock_DTCInfo_WriteBlock(RE_NvM_10ms_Process_20);
retRE_NvM_10ms_Process_3 = Rte_Call_PS_NvMBlock_Dummy_GetErrorStatus(&RE_NvM_10ms_Process_30);
retRE_NvM_10ms_Process_4 = Rte_Call_PS_NvMBlock_Dummy_ReadBlock(RE_NvM_10ms_Process_40);
retRE_NvM_10ms_Process_5 = Rte_Call_PS_NvMBlock_Dummy_WriteBlock(RE_NvM_10ms_Process_50);
retRE_NvM_10ms_Process_6 = Rte_Call_PS_NvMBlock_Function_GetErrorStatus(&RE_NvM_10ms_Process_60);
retRE_NvM_10ms_Process_7 = Rte_Call_PS_NvMBlock_Function_ReadBlock(RE_NvM_10ms_Process_70);
retRE_NvM_10ms_Process_8 = Rte_Call_PS_NvMBlock_Function_WriteBlock(RE_NvM_10ms_Process_80);
retRE_NvM_10ms_Process_9 = Rte_Call_PS_NvMBlock_MDate_GetErrorStatus(&RE_NvM_10ms_Process_90);
retRE_NvM_10ms_Process_10 = Rte_Call_PS_NvMBlock_MDate_ReadBlock(RE_NvM_10ms_Process_100);
retRE_NvM_10ms_Process_11 = Rte_Call_PS_NvMBlock_MDate_WriteBlock(RE_NvM_10ms_Process_110);
retRE_NvM_10ms_Process_12 = Rte_Call_PS_NvMBlock_Option_GetErrorStatus(&RE_NvM_10ms_Process_120);
retRE_NvM_10ms_Process_13 = Rte_Call_PS_NvMBlock_Option_ReadBlock(RE_NvM_10ms_Process_130);
retRE_NvM_10ms_Process_14 = Rte_Call_PS_NvMBlock_Option_WriteBlock(RE_NvM_10ms_Process_140);
retRE_NvM_10ms_Process_15 = Rte_Call_PS_NvMBlock_PartNO_GetErrorStatus(&RE_NvM_10ms_Process_150);
retRE_NvM_10ms_Process_16 = Rte_Call_PS_NvMBlock_PartNO_ReadBlock(RE_NvM_10ms_Process_160);
retRE_NvM_10ms_Process_17 = Rte_Call_PS_NvMBlock_PartNO_WriteBlock(RE_NvM_10ms_Process_170);
retRE_NvM_10ms_Process_18 = Rte_Call_PS_NvMBlock_SerialNO_GetErrorStatus(&RE_NvM_10ms_Process_180);
retRE_NvM_10ms_Process_19 = Rte_Call_PS_NvMBlock_SerialNO_ReadBlock(RE_NvM_10ms_Process_190);
retRE_NvM_10ms_Process_20 = Rte_Call_PS_NvMBlock_SerialNO_WriteBlock(RE_NvM_10ms_Process_200);

/* **********************Rte Write/Send API************************ */
retRE_NvM_10ms_Process_0 = Rte_Write_P_Slpwup_NvMJobFinished_SR_u8(&RE_NvM_10ms_Process_0);
#endif
/* PROTECTED REGION START ID(User Defined Code):(RE_NvM_10ms_Process) */
/* Start of user defined code  - Do not remove this comment */
 Eeprom_Control();
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_NvM_10ms_Process) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_NvM_STOP_SEC_CODE
#include "SWC_NvM_MemMap.h"
#define SWC_NvM_START_SEC_CODE
#include "SWC_NvM_MemMap.h"

FUNC(void, SWC_NvM_CODE) RE_NvMJobFinished_DTCInfo(IN VAR(uint8, AUTOMATIC) ServiceId, IN VAR(NvM_RequestResultType, AUTOMATIC) JobResult)
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/

/* PROTECTED REGION START ID(User Defined Variable):(RE_NvMJobFinished_DTCInfo) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_NvMJobFinished_DTCInfo) */

/* PROTECTED REGION START ID(User Defined Code):(RE_NvMJobFinished_DTCInfo) */
/* Start of user defined code  - Do not remove this comment */
  PNJF_NvMBlock_JobFinish(e_NvmSvcBlock_DTCInfo, ServiceId, JobResult);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_NvMJobFinished_DTCInfo) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_NvM_STOP_SEC_CODE
#include "SWC_NvM_MemMap.h"
#define SWC_NvM_START_SEC_CODE
#include "SWC_NvM_MemMap.h"

FUNC(void, SWC_NvM_CODE) RE_NvMJobFinished_Function(IN VAR(uint8, AUTOMATIC) ServiceId, IN VAR(NvM_RequestResultType, AUTOMATIC) JobResult)
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/

/* PROTECTED REGION START ID(User Defined Variable):(RE_NvMJobFinished_Function) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_NvMJobFinished_Function) */

/* PROTECTED REGION START ID(User Defined Code):(RE_NvMJobFinished_Function) */
/* Start of user defined code  - Do not remove this comment */
  PNJF_NvMBlock_JobFinish(e_NvmSvcBlock_Function, ServiceId, JobResult);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_NvMJobFinished_Function) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_NvM_STOP_SEC_CODE
#include "SWC_NvM_MemMap.h"
#define SWC_NvM_START_SEC_CODE
#include "SWC_NvM_MemMap.h"

FUNC(void, SWC_NvM_CODE) RE_NvMJobFinished_MDate(IN VAR(uint8, AUTOMATIC) ServiceId, IN VAR(NvM_RequestResultType, AUTOMATIC) JobResult)
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/

/* PROTECTED REGION START ID(User Defined Variable):(RE_NvMJobFinished_MDate) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_NvMJobFinished_MDate) */

/* PROTECTED REGION START ID(User Defined Code):(RE_NvMJobFinished_MDate) */
/* Start of user defined code  - Do not remove this comment */
  PNJF_NvMBlock_JobFinish(e_NvmSvcBlock_MDate, ServiceId, JobResult);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_NvMJobFinished_MDate) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_NvM_STOP_SEC_CODE
#include "SWC_NvM_MemMap.h"
#define SWC_NvM_START_SEC_CODE
#include "SWC_NvM_MemMap.h"

FUNC(void, SWC_NvM_CODE) RE_NvMJobFinished_Option(IN VAR(uint8, AUTOMATIC) ServiceId, IN VAR(NvM_RequestResultType, AUTOMATIC) JobResult)
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/

/* PROTECTED REGION START ID(User Defined Variable):(RE_NvMJobFinished_Option) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_NvMJobFinished_Option) */

/* PROTECTED REGION START ID(User Defined Code):(RE_NvMJobFinished_Option) */
/* Start of user defined code  - Do not remove this comment */
  PNJF_NvMBlock_JobFinish(e_NvmSvcBlock_Option, ServiceId, JobResult);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_NvMJobFinished_Option) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_NvM_STOP_SEC_CODE
#include "SWC_NvM_MemMap.h"
#define SWC_NvM_START_SEC_CODE
#include "SWC_NvM_MemMap.h"

FUNC(void, SWC_NvM_CODE) RE_NvMJobFinished_PartNO(IN VAR(uint8, AUTOMATIC) ServiceId, IN VAR(NvM_RequestResultType, AUTOMATIC) JobResult)
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/

/* PROTECTED REGION START ID(User Defined Variable):(RE_NvMJobFinished_PartNO) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_NvMJobFinished_PartNO) */

/* PROTECTED REGION START ID(User Defined Code):(RE_NvMJobFinished_PartNO) */
/* Start of user defined code  - Do not remove this comment */
  PNJF_NvMBlock_JobFinish(e_NvmSvcBlock_PartNO, ServiceId, JobResult);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_NvMJobFinished_PartNO) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_NvM_STOP_SEC_CODE
#include "SWC_NvM_MemMap.h"
#define SWC_NvM_START_SEC_CODE
#include "SWC_NvM_MemMap.h"

FUNC(void, SWC_NvM_CODE) RE_NvMJobFinished_SerialNO(IN VAR(uint8, AUTOMATIC) ServiceId, IN VAR(NvM_RequestResultType, AUTOMATIC) JobResult)
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/

/* PROTECTED REGION START ID(User Defined Variable):(RE_NvMJobFinished_SerialNO) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_NvMJobFinished_SerialNO) */

/* PROTECTED REGION START ID(User Defined Code):(RE_NvMJobFinished_SerialNO) */
/* Start of user defined code  - Do not remove this comment */
  PNJF_NvMBlock_JobFinish(e_NvmSvcBlock_SerialNO, ServiceId, JobResult);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_NvMJobFinished_SerialNO) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_NvM_STOP_SEC_CODE
#include "SWC_NvM_MemMap.h"
#define SWC_NvM_START_SEC_CODE
#include "SWC_NvM_MemMap.h"

FUNC(void, SWC_NvM_CODE) RE_NvMJobFinished_Dummy(IN VAR(uint8, AUTOMATIC) ServiceId, IN VAR(NvM_RequestResultType, AUTOMATIC) JobResult)
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/

/* PROTECTED REGION START ID(User Defined Variable):(RE_NvMJobFinished_Dummy) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_NvMJobFinished_Dummy) */

/* PROTECTED REGION START ID(User Defined Code):(RE_NvMJobFinished_Dummy) */
/* Start of user defined code  - Do not remove this comment */
  PNJF_NvMBlock_JobFinish(e_NvmSvcBlock_Dummy, ServiceId, JobResult);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_NvMJobFinished_Dummy) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_NvM_STOP_SEC_CODE
#include "SWC_NvM_MemMap.h"
#define SWC_NvM_START_SEC_CODE
#include "SWC_NvM_MemMap.h"

FUNC(void, SWC_NvM_CODE) RE_ReadEepData(IN P2CONST(tEepBlock, AUTOMATIC, RTE_APPL_DATA) Read_EepBlock, OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Read_EepData)
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/

/* PROTECTED REGION START ID(User Defined Variable):(RE_WriteEepData) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_WriteEepData) */

/* PROTECTED REGION START ID(User Defined Code):(RE_WriteEepData) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_WriteEepData) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_NvM_STOP_SEC_CODE
#include "SWC_NvM_MemMap.h"
#define SWC_NvM_START_SEC_CODE
#include "SWC_NvM_MemMap.h"

FUNC(void, SWC_NvM_CODE) RE_WriteEepData(IN P2CONST(tEepBlock, AUTOMATIC, RTE_APPL_DATA) Write_EepBlock, IN P2CONST(tEepWriteReq, AUTOMATIC, RTE_APPL_DATA) Write_EepWriteReq, IN P2CONST(uint8, AUTOMATIC, RTE_APPL_DATA) Write_EepData)
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/

/* PROTECTED REGION START ID(User Defined Variable):(RE_ReadEepData) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_ReadEepData) */

/* PROTECTED REGION START ID(User Defined Code):(RE_ReadEepData) */
/* Start of user defined code  - Do not remove this comment */

  //WriteEepData(*Write_EepBlock, *Write_EepWriteReq, &Write_EepData);
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_ReadEepData) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_NvM_STOP_SEC_CODE
#include "SWC_NvM_MemMap.h"




void Callback_NVM_DATA(uint16 rcv_source, uint8 rcv_serviceId, uint8 rcv_jobResult)
{
  switch(rcv_serviceId)
  {

    case NVM_SETDATAINDEX_SID:
      /* user code*/
    break;

    case NVM_GETDATAINDEX_SID:
      /* user code*/
    break;

    case NVM_SETBLOCKPROTECTION_SID:
      /* user code*/
    break;

    case NVM_GETERRORSTATUS_SID:
      /* user code*/
    break;

    case NVM_SETRAMBLOCKSTATUS_SID:
      /* user code*/
    break;

    case NVM_READALL_SID:
     // Read_NVM_JobResult(rcv_source, rcv_jobResult);
    break;

    case NVM_READBLOCK_SID:
      /* user code*/
    break;

    case NVM_WRITEBLOCK_SID:
   //   Write_NVM_JobResult(rcv_source, rcv_jobResult);
    break;

    case NVM_RESTOREBLOCKDEFAULTS_SID:
      /* user code*/
    break;

    case NVM_ERASENVBLOCK_SID:
      /* user code*/
    break;

    case NVM_CANCELWRITEALL_SID:
      /* user code*/
    break;

    case NVM_INVALIDATENVBLOCK_SID:
      /* user code*/
    break;

    case NVM_WRITEALL_SID:
      /* user code*/
    break;

    case NVM_GETVERSIONINFO_SID:
      /* user code*/
    break;

    case NVM_CANCELJOBS_SID:
      /* user code*/
    break;

    case NVM_SETBLOCKLOCKSTATUS_SID:
      /* user code*/
    break;

    default:
      /* MISRA */
    break;
    }
}







