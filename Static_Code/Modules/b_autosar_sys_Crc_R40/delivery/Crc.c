/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Crc.c                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crc Library Module                                    **
**                                                                            **
**  PURPOSE   : Implementation of Version Information for CRC Library Module  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.0.1     03-May-2019   YJ Yun           Redmine #17358, #6718             **
** 1.0.0     07-Feb-2013   CY Song          Initial Version                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Crc.h"                       /* Crc Header file */


/* polyspace-begin MISRA-C3:20.1 [Not a defect:Low] No Impact of this rule violation */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "Value shall be cheched by user" */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#define CRC_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Crc_GetVersionInfo                                  **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : This function returns the version information of CRC**
**                        Library module.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Versioninfo                                         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

FUNC(void, CRC_CODE) Crc_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, CRC_APPL_DATA) Versioninfo)
{
  if(Versioninfo != NULL_PTR)
  {
    /* Copy the vendor Id */
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "This variable is passed by user" */
    Versioninfo->vendorID = CRC_VENDOR_ID;
    /* Copy the module Id */
    Versioninfo->moduleID = CRC_MODULE_ID;
    /* Copy Software Major Version */
    Versioninfo->sw_major_version = CRC_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    Versioninfo->sw_minor_version = CRC_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    Versioninfo->sw_patch_version = CRC_SW_PATCH_VERSION;
  } /* if(Versioninfo != NULL_PTR) */

  /* If the received Versioninfo pointer is NULL it shall return from the
  Crc_GetVersionInfo API without performing any further functionality. */
}
#define CRC_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "Value shall be cheched by user" */
/* polyspace-end MISRA-C3:20.1 [Not a defect:Low] No Impact of this rule violation */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
