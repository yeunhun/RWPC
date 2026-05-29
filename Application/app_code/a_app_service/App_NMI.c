/*******************************************************************************
**                            HYUNDAI MOTORS GROUP                            **
**                                                                            **
**                            All rights reserved                             **
**                                                                            **
**            You can NOT use this sample code for Product Release            **
*******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_Imp.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define OS_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
* Function             : Os_CallBackNMInterrupt
*
* Service ID           : NA
*
* Description          : This function is a callback function for NMI
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Non Re-entrant
*
* Parameters           : None
*
* @return              : None
*
* @pre                 : None
*
* @remarks             : Global Variable(s)     :
*                        None
*
*                        Function(s) invoked    :
*                        None
******************************************************************************/
FUNC(void, OS_CALLOUT_CODE) Os_CallBackNMInterrupt(void)
{
  /* Do not modify : Start */
  CONSTP2VAR(Os_FaultStructType, OS_CONST, REG_SPACE) faultStructPtr = OS_FAULT_STRUCT1;

  /* polyspace +2 RTE:NIV [Justified:Medium] "Predefined REG_SPACE" */
  switch (faultStructPtr->STATUS)
  {
    case OS_FAULT_RAMC0_NC_ECC:
    case OS_FAULT_RAMC1_NC_ECC:
      Os_InitRamSector32(OS_RAM_SECTOR_POR_COUNT, Os_GaaRamSectorInitPowerOnReset);
      AppCallbackOnSystemError(E_OS_SYS_RAMECC);
      /* Never returns! */
      Os_ResetMCU();
      break;
    case OS_FAULT_FLASHC_MAIN_NC_ECC:
      /* Never returns! */
      ShutdownOS(E_OS_SYS_PFLASHECC);
      break;
    default:
      ShutdownOS(E_OS_SYS_NMI);
      break;
  }

  /* Clear Fault Struct */
  faultStructPtr->STATUS = 0u;
  faultStructPtr->INTR = 1u;
  /* Do not modify : End */
}
