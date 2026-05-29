/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: NvM_Cbk.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : Provision of Memory abstraction Callback functions            **
**              NvM_JobEndNotification                                        **
**              NvM_JobErrorNotification                                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date           By          Description                         **
********************************************************************************
** 1.3.0       25-Jul-2016   Song CY      Redmine #5383                       **
** 1.1.6       03-Mar-2015  Song CY       As per RedMine 2216, Remove version **
**                                        Information                         **
** 1.1.0     18-Apr-2014   Song CY     RedMine718 Version is updated          **
** 1.0.0       25-Jan-2013    CY Song     Initial version                     **
*******************************************************************************/

/*******************************************************************************
 **                   Include Files                                           **
******************************************************************************/

#include "NvM_Cbk.h"         /* NvM_Cbk header file */
#include "NvM_Ram.h"         /* Global variables header file */

/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification" */
/*******************************************************************************
**                        Function Definitions                                **
*******************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : NvM_JobEndNotification                                **
**                                                                            **
** Service ID         : 0x11                                                  **
**                                                                            **
** Description        : Function to be used by the subsequent memory driver   **
**                      to signal end of job without error.                   **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Reentrancy         : Non-Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s)  : NvM_GddJobResultLowLevel        **
**                                                                            **
**                      Function(s) invoked : None                            **
*******************************************************************************/
#if(NVM_POLLING_MODE == STD_OFF)
FUNC(void, NVM_CODE) NvM_JobEndNotification(void)
{
   /* Indicate job is completed without error */
   NvM_GddJobResultLowLevel = NVM_REQ_OK;
}
#endif
/*******************************************************************************
** Function Name      : NvM_JobErrorNotification                              **
**                                                                            **
** Service ID         : 0x12                                                  **
**                                                                            **
** Description        : Function to be used by the subsequent memory driver   **
**                      to signal end of job with error.                      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Reentrancy         : Non-Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s)  : NvM_GddJobResultLowLevel        **
**                                                                            **
**                      Function(s) invoked : None                            **
*******************************************************************************/
#if(NVM_POLLING_MODE == STD_OFF)
FUNC(void, NVM_CODE) NvM_JobErrorNotification(void)
{
  /* Indicate job is completed with error */
  NvM_GddJobResultLowLevel = NVM_REQ_NOT_OK;
}
#endif

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification" */

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
