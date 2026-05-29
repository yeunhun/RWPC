/*******************************************************************************
**  (C) 2014 Hyundai AUTRON                                                   **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: App_WdgM.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR WdgM                                                  **
**                                                                            **
**  PURPOSE   : Sample code for testing WdgM module                           **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.0.4     28-Mar-2017   Kuksun         Redmine #7553                       **
** 1.0.3     26-Feb-2015   Sinil          1. Add a macro for integration test **
** 1.0.2     13-Jan-2015   Sinil          1. Add a flag for testing wdg       **
**                                        expiration                          **
**                                        2. Change naming                    **
** 1.0.1     09-Dec-2014   Sinil          10ms alive supervision only         **
** 1.0.0     15-Oct-2014   Sinil          Initial version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Rte_SWC_WdgMTest.h"

/*******************************************************************************
**                      Function Declarations                                 **
*******************************************************************************/
#define SWC_WdgMTest_START_SEC_CODE
#include "SWC_WdgMTest_MemMap.h"
void RE_Wdg_Cbk(void);
#define SWC_WdgMTest_STOP_SEC_CODE
#include "SWC_WdgMTest_MemMap.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#define WDGMTEST_ENABLE_INTEGRATION_TEST              STD_ON

/*******************************************************************************
**                       Global Data                                          **
*******************************************************************************/
WdgM_GlobalStatusType WdgMTest_GddGlobalStatus;
WdgM_SupervisedEntityIdType WdgMTest_GddExpiredSEID;
boolean WdgMTest_GblStart = FALSE;
#if (WDGMTEST_ENABLE_INTEGRATION_TEST == STD_ON)
boolean WdgMTest_GblExpireWdg = FALSE;
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : RE_WdgMTest                                         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This service provides Test method for WdgM behavior **
**                        using Supervised Entity as expired                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Rte_Start should be initialized                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        WdgMTest_GblStart,                                  **
**                        WdgMTest_GblExpireWdg,                              **
**                        WdgMTest_GddGlobalStatus                            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Rte_Call_WdgM_API_R_SetMode,                        **
**                        Rte_Call_SE_WdgMTest_CheckpointReached,             **
**                        Rte_Call_WdgM_API_R_GetGlobalStatus,                **
**                        Rte_Call_WdgM_API_R_GetFirstExpiredSEID             **
*******************************************************************************/
#define SWC_WdgMTest_START_SEC_CODE
#include "SWC_WdgMTest_MemMap.h"

void RE_WdgMTest(void)
{
#if 0
  if (!WdgMTest_GblStart)
  {
    Rte_Call_WdgM_API_R_SetMode(WDGM_WDGMMODE1, WDGM_SE_INIT);
    WdgMTest_GblStart = TRUE;
  }

  #if (WDGMTEST_ENABLE_INTEGRATION_TEST == STD_ON)
  if (!WdgMTest_GblExpireWdg)
  {
  #endif
    /* WdgMAliveSupervision0 */
//========================================================================================
	// Deadline supervision Sample
    (void)Rte_Call_SE_WdgMTest_CheckpointReached(WDGM_SE_WDGMTEST_CP_WDGMTEST_DS0); //Deadline supervision Start  (Sample Period = 100ms)
		// User Logic
    (void)Rte_Call_SE_WdgMTest_CheckpointReached(WDGM_SE_WDGMTEST_CP_WDGMTEST_DS1); //Deadline supervision End
	//========================================================================================
//========================================================================================
	// Internal Logical SuperVison Sample
    (void)Rte_Call_SE_WdgMTest_CheckpointReached(WDGM_SE_WDGMTEST_CP_WDGMTEST_ILS_0); //Internal Logical SuperVison Start
		// User Logic 1
    (void)Rte_Call_SE_WdgMTest_CheckpointReached(WDGM_SE_WDGMTEST_CP_WDGMTEST_ILS_1); //Internal Logical SuperVison Transition
		// User Logic 2
    (void)Rte_Call_SE_WdgMTest_CheckpointReached(WDGM_SE_WDGMTEST_CP_WDGMTEST_ILS_2); //Internal Logical SuperVison End
	//========================================================================================
    Rte_Call_SE_WdgMTest_CheckpointReached(WDGM_SE_WDGMTEST_CP_WDGMTEST_AS0);
  #if (WDGMTEST_ENABLE_INTEGRATION_TEST == STD_ON)
  }
  #endif
#endif
}
#define SWC_WdgMTest_STOP_SEC_CODE
#include "SWC_WdgMTest_MemMap.h"

/*******************************************************************************
** Function Name        : RE_WdgMTestGlobalMode                               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This service provides check method for              **
**                        WdgM Global Supervision Status                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Rte_Start should be initialized                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        WdgMTest_GddGlobalStatus,                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Rte_Call_WdgM_API_R_GetGlobalStatus,                **
**                        Rte_Call_WdgM_API_R_GetFirstExpiredSEID             **
*******************************************************************************/
#define SWC_WdgMTest_START_SEC_CODE
#include "SWC_WdgMTest_MemMap.h"
void RE_WdgMTestGlobalMode(void)
{
  Rte_Call_WdgM_API_R_GetGlobalStatus(&WdgMTest_GddGlobalStatus);

  switch (WdgMTest_GddGlobalStatus)
  {
  case WDGM_GLOBAL_STATUS_OK:
    break;
  case WDGM_GLOBAL_STATUS_FAILED:
    break;
  case WDGM_GLOBAL_STATUS_EXPIRED:
    Rte_Call_WdgM_API_R_GetFirstExpiredSEID(&WdgMTest_GddExpiredSEID);
    break;
  case WDGM_GLOBAL_STATUS_STOPPED:
    break;
  }
}
#define SWC_WdgMTest_STOP_SEC_CODE
#include "SWC_WdgMTest_MemMap.h"

/*******************************************************************************
** Function Name        : RE_Wdg_Cbk                                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This Callback Function is called by Wdg Callback    **
**                        as configuration in the Wdg module                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Rte_Start should be initialized                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        N/A                                                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        N/A                                                 **
*******************************************************************************/
#define SWC_WdgMTest_START_SEC_CODE
#include "SWC_WdgMTest_MemMap.h"
void RE_Wdg_Cbk(void)
{
}
#define SWC_WdgMTest_STOP_SEC_CODE
#include "SWC_WdgMTest_MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
