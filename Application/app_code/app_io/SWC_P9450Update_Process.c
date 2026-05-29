/*******************************************************************************
**                       HYUNDAI-AUTOEVER PVT LTD                             **
********************************************************************************
** Copyright (C) HYUNDAI-AUTOEVER PVT LTD - All Rights Reserved               **
** Unauthorized copying of this file, via any medium is strictly prohibited   **
** Auto generated file                                                        **
*******************************************************************************/
/* Generate On : ȭ 8�� 16 2022 12:07:56 KST                                    */
/* Generate from : Y:/01_SWP_Backup/e_ka4_pe_wpc_v200_20220815                */
/* Code Generation Version : 1.0.2                                            */

#include "Rte_SWC_P9450Update_Process.h"

/* PROTECTED REGION START ID(User Defined File Inclusion):(SWC_P9450Update_Process) */
/* Start of user defined code  - Do not remove this comment */

/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined File Inclusion):(SWC_P9450Update_Process) */

/* PROTECTED REGION START ID(User Defined Constants):(SWC_P9450Update_Process) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Constants):(SWC_P9450Update_Process) */

/* PROTECTED REGION START ID(User Defined Global Variables):(SWC_P9450Update_Process) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Global Variables):(SWC_P9450Update_Process) */
#define SWC_P9450Update_Process_START_SEC_CODE
#include "SWC_P9450Update_Process_MemMap.h"
extern void EraseFlashCtrl(void);
extern uint8 GetReprogrammingProgress(void);
volatile uint32 re_p9450_task_cnt = 0u;
volatile uint8 p9450_reprog_percent_cnt = 0u;
FUNC(void, SWC_P9450Update_Process_CODE) RE_P9450_Update_Process(void) 
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/

/* PROTECTED REGION START ID(User Defined Variable):(RE_P9450_Update_Process) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_P9450_Update_Process) */

/* PROTECTED REGION START ID(User Defined Code):(RE_P9450_Update_Process) */
/* Start of user defined code  - Do not remove this comment */
  EraseFlashCtrl();
  p9450_reprog_percent_cnt = GetReprogrammingProgress();
  re_p9450_task_cnt++;
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_P9450_Update_Process) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}
#define SWC_P9450Update_Process_STOP_SEC_CODE
#include "SWC_P9450Update_Process_MemMap.h"
