/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  FILE-NAME : EcuM_Os.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR EcuM Module                                           **
**                                                                            **
**  PURPOSE   : Os Related Functionality implementation of EcuM               **
**              EcuM_IncrementTimer                                           **
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
** 3.0.5      17-Aug-2021   Junho Cho     Redmine #31552                      **
** 2.2.1      26-Dec-2014   Daejun Park   Redmine #1879                       **
**                                        -Update to AUTRON template          **
** 1.0.0      04-Mar-2013   Daejun Park   Initial version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM.h"
#include "EcuM_Os.h"
#include "EcuM_Ram.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : EcuM_IncrementTimer                                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For incrementing the timer every 1 second           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant, Non-Interruptible                    **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GulRunningTimer                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
#if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
#define ECUM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, ECUM_CODE) EcuM_IncrementTimer(void)
{
  if(EcuM_GddState == ECUM_STATE_STARTUP_TWO)
  {
    /* Increment the running timer every time when EcuM_IncrementTimer is called
                              upon expiry of 1second alarm in Os in Up Phase */
    /*
         *   MISRA Rule        : 17.4
         *   Message           : Performing pointer arithmetic.
         *   Reason            : Array Indexing is not used to achieve better
         *                       throughput.
         *   Verification      : However, part of the code is verified manually
         *                       and it is not having any impact.
    */
    EcuM_GulRunningTimer++;
  }
}
#define ECUM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

