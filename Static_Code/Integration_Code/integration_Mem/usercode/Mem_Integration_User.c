/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Mem_Integration_User.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR MemStack Integration Module                           **
**                                                                            **
**  PURPOSE   : Provision of Version information                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "HwResource.h"
#include "Mem_Integration.h"
#include "Mem_Integration_User.h"

#if (MEM_FEE_USED == STD_ON)
#include "Fee.h"
#endif


#if (MEM_FLS_USED == STD_ON)
#include "Fls.h"
#endif

#define NVM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Mem_PostFeeInitCallback                             **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function is invoked before Fee is initialized  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(void, NVM_CODE) Mem_PostFeeInitCallback(void)
{
  /* USER CODE */
}


/*******************************************************************************
** Function Name        : Mem_Cypress_IllegalStateCallback                    **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function handles exception when Fee module     **
**                        faileds to initialize                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Only Cypress MCU                                    **
*******************************************************************************/
#if (HWRESOURCE_VENDOR(HWRESOURCE_CYPRESS))
FUNC(boolean, NVM_CODE) Mem_Cypress_IllegalStateCallback(void)
{
  static volatile uint8 numOfRetry = 1;
  boolean retVal = MEM_FALSE;

  /* There is no workaround other than erasing the internal EEPROM
   *
   * Please refer to Fee/Fls manual */
  if (numOfRetry > 0U)
  {
    numOfRetry--;
    /* Write the code for Fee illegal State, if App needs to do something */   
  }
  else
  {    
    /* Write the code for Fee illegal State, if App needs to do something */ 
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Mem_Infineon_IllegalStateCallback                   **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Callback function which will be called              **
**                        when the FEE reaches the illegal state.             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Only Infineon MCU                                   **
*******************************************************************************/
#if (HWRESOURCE_VENDOR(HWRESOURCE_INFINEON))
FUNC(void, NVM_CODE) Mem_Infineon_IllegalStateCallback (void)
{
  /* 1. During Initialisation of the FEE driver, FEE reads the state pages 
   *    and the content of the same leads to an invalid / illegal state. 
   *    Eg: Valid State Page is missing in both of the FEE sectors. 
   *     - The only mechanism for recovering from this Illegal State is by 
   *       erasing of the DF_EEPROM area. The user can enable FEE to erase both 
   *       the sectors (not an API request) by configuring FeeEraseAllEnable to 
   *       TRUE, such that the automatic erase of both sectors is executed. 
   *
   * 2. FEE reaches illegal state if it detects a virgin (all 0x00) flash 
   *    (DF_EEPROM) when FeeVirginFlashIllegalState is configured as true and
   *    FeeEraseAllEnable is configured as false
   *
   * For more information, please refer Fee User Manual 
   */
   
   /* Write the code for Fee illegal State, if App needs to do something */
   {
      
   }
}	
#endif

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                         End of File                                        **
*******************************************************************************/

