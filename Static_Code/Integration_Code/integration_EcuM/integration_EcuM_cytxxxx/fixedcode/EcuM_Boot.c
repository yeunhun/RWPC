/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  FILE-NAME : EcuM_Boot.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Boot Code                                             **
**                                                                            **
**  PURPOSE   : Platform Boot Functionality                                   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                              Revision History                              **
********************************************************************************
** Revision   Date          By            Description                         **
********************************************************************************
** 2.5.3      16-Dec-2020   JeongSu Lim  #27216                               **
** 2.4.0      02-Dec-2019   Junho Cho    Initial version                      **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Justified:Low] "See MEMMAP003 of AUTOSAR" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM.h"
#include "Os.h"

#if (ECUM_LP_CALLOUT_ENABLED == STD_ON)
#include "LowPower_Callout.h"
#endif

int main(void); /* polyspace MISRA2012:D4.6 [Justified:Low] "'C' standard" */

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/
#define ECUM_START_SEC_CALLOUT_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : main                                                  **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : Booting main function                                 **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) : None                             **
**                      Function(s) invoked :                                 **
**                      EcuM_PreInit                                          **
**                      EcuM_Init                                             **
**                      EcuM_BootCallout                                      **
*******************************************************************************/
int main(void) /* polyspace MISRA2012:D4.6 [Justified:Low] "'C' standard" */
{
  EcuM_PreInit();

  #if (ECUM_LP_CALLOUT_ENABLED == STD_ON)
  /* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "Ecum_Boot_Callout function will be written by customer and then it will not be a deadcode" */
  EcuM_Boot_Callout();
  /* polyspace-end MISRA-C3:2.2 */
  #endif

  /* polyspace<RTE: NTC : Not a defect : No Action Planned > Due to calling StartOs by EcuM_Init */
  EcuM_Init();

  return 0;
}

/*******************************************************************************
* TASK BODIES
*******************************************************************************/
#if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
TASK(OsTask_BSW_Init_Main)
{
  EcuM_StartupTwo();

  (void)TerminateTask();
}

#if (ECUM_NO_OF_CORES > 1)
TASK(OsTask_BSW_Init_Sub1)
{
  EcuM_StartupTwo();

  (void)TerminateTask();
}
#endif

#if (ECUM_NO_OF_CORES > 2)
TASK(OsTask_BSW_Init_Sub2)
{
  EcuM_StartupTwo();

  (void)TerminateTask();
}
#endif

#if (ECUM_NO_OF_CORES > 3)
TASK(OsTask_BSW_Init_Sub3)
{
  EcuM_StartupTwo();

  (void)TerminateTask();
}
#endif

#if (ECUM_NO_OF_CORES > 4)
TASK(OsTask_BSW_Init_Sub4)
{
  EcuM_StartupTwo();

  (void)TerminateTask();
}
#endif

#if (ECUM_NO_OF_CORES > 5)
TASK(OsTask_BSW_Init_Sub5)
{
  EcuM_StartupTwo();

  (void)TerminateTask();
}
#endif

#else
TASK(OsTask_BSW_Init)
{
  EcuM_StartupTwo();

  (void)TerminateTask();
}
#endif

#define ECUM_STOP_SEC_CALLOUT_CODE
#include "MemMap.h"
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
