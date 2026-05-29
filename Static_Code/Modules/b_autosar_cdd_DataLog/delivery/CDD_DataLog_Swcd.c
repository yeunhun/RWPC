/*******************************************************************************
**                                                                            **
**  (C) 2020-2021 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CDD_DataLog.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : DataLog CDD                                                   **
**                                                                            **
**  PURPOSE   : Provision of SWC functions for DataLog                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.1.0     07-Jun-2021    MJ.Woo        Redmine #29944, #30055              **
** 1.0.0     29-Oct-2020    MJ.Woo        Redmine #25497                      **
*******************************************************************************/

/*******************************************************************************
 **                      Include Section                                      **
 ******************************************************************************/
#include "Rte_DataLog.h"
#include "CDD_DataLog.h"
#include "string.h"

/*******************************************************************************
**                       Global Data                                          **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define DataLog_START_SEC_CODE
#include "DataLog_MemMap.h"

/**
* @addtogroup DATALOG_ESDD_007
* @{ */
/***************************************************************************//**
 * Function Name        : CBReadData_DE_DataLog
 *
 * Service ID           : NA
 *
 * Description          : Requests the current value of the data element
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [out]           Data    Freeze Frame buffer of DataLog
 *
 * @return              : Std_ReturnType
 *                        - RTE_E_OK : Operation was successful
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        DataLog_SavedData
 *
 *                        Function(s) invoked    :
 *                        memcpy()
 ******************************************************************************/
FUNC(Std_ReturnType, DataLog_CODE) CBReadData_DE_DataLog(
                                    P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  #if (SWP_USE_DATALOG == STD_ON)
  memcpy(Data, (uint8 *)&DataLog_SavedData, DATALOG_DATA_BYTE_SIZE);
  #endif

  return RTE_E_OK;
}
/** @}  */

#define DataLog_STOP_SEC_CODE
#include "DataLog_MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
