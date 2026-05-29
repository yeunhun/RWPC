/*******************************************************************************
**                       HYUNDAI-AUTOEVER PVT LTD                             **
********************************************************************************
** Copyright (C) HYUNDAI-AUTOEVER PVT LTD - All Rights Reserved               **
** Unauthorized copying of this file, via any medium is strictly prohibited   **
** Auto generated file                                                        **
*******************************************************************************/
/* Generate On : �� 5�� 23 2022 14:37:47 KST                                    */
/* Generate from : Y:/01_SWP_Backup/kkh_backup/e_ka4_pe_wpc_v200_220519_1     */
/* Code Generation Version : 1.0.2                                            */

#include "Rte_SWC_Task.h"

/* PROTECTED REGION START ID(User Defined File Inclusion):(SWC_Task) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined File Inclusion):(SWC_Task) */

/* PROTECTED REGION START ID(User Defined Constants):(SWC_Task) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Constants):(SWC_Task) */

/* PROTECTED REGION START ID(User Defined Global Variables):(SWC_Task) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Global Variables):(SWC_Task) */
#define SWC_Task_START_SEC_CODE
#include "SWC_Task_MemMap.h"

extern uint8 get_init_nvm_test(void);
volatile uint32 fawerawer= 0u;
extern void EraseFlashCtrl(void);
FUNC(void, SWC_Task_CODE) RE_ASW_10ms_TASK(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/

/* PROTECTED REGION START ID(User Defined Variable):(RE_ASW_10ms_TASK) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_ASW_10ms_TASK) */

/* **********************Rte Trigger API************************ */
  if(get_init_nvm_test()==0x1Fu)
  {
    Rte_Trigger_P_RE_Input_10ms_Input_10ms_Process();
    Rte_Trigger_P_RE_WPC_Process_10ms_WPC_Process_10ms();
    Rte_Trigger_P_RE_Output_10ms_Output_10ms_Process();
  }

/* PROTECTED REGION START ID(User Defined Code):(RE_ASW_10ms_TASK) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_ASW_10ms_TASK) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}

#define SWC_Task_STOP_SEC_CODE
#include "SWC_Task_MemMap.h"
#define SWC_Task_START_SEC_CODE
#include "SWC_Task_MemMap.h"
volatile uint32 re_5ms_task_cnt = 0u;
FUNC(void, SWC_Task_CODE) RE_ASW_5ms_TASK(void) 
{
  /*****************************************************************************/
  /*               Start of Runnable                                           */
  /*****************************************************************************/

  /* PROTECTED REGION START ID(User Defined Variable):(RE_ASW_5ms_TASK) */
  /* Start of user defined code  - Do not remove this comment */
  /* End of user defined code - Do not remove this comment */
  /* PROTECTED REGION END ID(User Defined Variable):(RE_ASW_5ms_TASK) */

  /* **********************Rte Trigger API************************ */
  if(get_init_nvm_test()==0x1Fu)
  {
    Rte_Trigger_P_RE_P9450_Update_5ms_P9450_Update_5ms();
    Rte_Trigger_Trg_interface_5ms_NP3_StandardTrigger_5ms_NP3();
  }
  /* PROTECTED REGION START ID(User Defined Code):(RE_ASW_5ms_TASK) */
  /* Start of user defined code  - Do not remove this comment */
  /* End of user defined code - Do not remove this comment */
  /* PROTECTED REGION END ID(User Defined Code):(RE_ASW_5ms_TASK) */
  /*****************************************************************************/
  /*               End of Runnable                                             */
  /*****************************************************************************/
}
#define SWC_Task_STOP_SEC_CODE
#include "SWC_Task_MemMap.h"

