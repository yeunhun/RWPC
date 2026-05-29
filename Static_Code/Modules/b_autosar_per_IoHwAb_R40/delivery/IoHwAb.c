/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: IoHwAb.c                                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_Init                                                   **
**              IoHwAb_DeInit                                                 **
**              IoHwAb_GetVersionInfo                                         **
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
** 1.15.0.2  09-Sep-2021   Yangjin    #31974                                  **
** 1.0.2     25-Mar-2015   Jongyoung  1.Manage the single module version      **
** 1.0.1     19-Aug-2014   Sinil      1. Change null types                    **
**                                    2. Update Det error code                **
**                                    3. Add Dem event report                 **
** 1.0.0     07-Mar-2014   Sinil      Initial version                         **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb.h"

#if (IOHWAB_USE_DIG_DIR == STD_ON)
#include "IoHwAb_DigDir.h"
#endif /* (IOHWAB_USE_DIG_DIR == STD_ON) */
#if (IOHWAB_USE_IO_MAN == STD_ON)
#include "IoHwAb_IOManager.h"
#endif /* (IOHWAB_USE_IO_MAN == STD_ON) */


/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : IoHwAb_Init                                         **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This function initializes all the IO Hardware       **
**                        Abstraction software.                               **
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
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : biostartup_Startup         **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE) IoHwAb_Init(void)
{
  #if (IOHWAB_USE_DIG_DIR == STD_ON)
  /* Initilization Port module */
  IoHwAb_DigDirInit();
  #endif /* (IOHWAB_USE_DIG_DIR == STD_ON) */

  #if (IOHWAB_USE_IO_MAN == STD_ON)
  /* Initialization of IO functions first part, start switched battery */
  IoHwAb_IOMInit();
  #endif /* (IOHWAB_USE_IO_MAN == STD_ON) */
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DeInit                                       **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This function deinitializes all the IO Hardware     **
**                        Abstraction software.                               **
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
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : biostartup_Startup         **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE) IoHwAb_DeInit(void)
{
  #if (IOHWAB_USE_IO_MAN == STD_ON)
  /* Initialization of IO functions first part, start switched battery */
  IoHwAb_IOMDeInit();
  #endif /* (IOHWAB_USE_IO_MAN == STD_ON) */
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_GetVersionInfo                               **
**                                                                            **
** Service ID           : 0x10                                                **
**                                                                            **
** Description          : This function returns the version information of    **
**                        the this module.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : versioninfo                                         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    :                            **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus                             **
*******************************************************************************/
#if (IOHWAB_VERSION_INFO_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE) IoHwAb_GetVersionInfo(P2VAR(Std_VersionInfoType,
    AUTOMATIC,
    IOHWAB_APPL_DATA) versioninfo)
{
  /* Check whether version information is equal to NULL */
  if (IOHWAB_NULL_PTR == versioninfo)
  {
    #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
      (uint8)IOHWAB_GETVERSIONINFO_SID, (uint8)IOHWAB_E_DET_WRONG_PARAM);
    #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
    #if (IOHWAB_USE_DEM_EVENT == STD_ON)
    Dem_ReportErrorStatus(IOHWAB_E_WRONG_PARAM, DEM_EVENT_STATUS_FAILED);
    #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
  }
  else
  {
    /* Copy the vendor ID */
    versioninfo->vendorID = (uint16)IOHWAB_VENDOR_ID;

    /* Copy the module ID */
    versioninfo->moduleID = (uint16)IOHWAB_MODULE_ID;

    /* Copy software major version */
    versioninfo->sw_major_version = (uint8)IOHWAB_SW_MAJOR_VERSION;

    /* Copy software minor version */
    versioninfo->sw_minor_version = (uint8)IOHWAB_SW_MINOR_VERSION;

    /* Copy software patch version */
    versioninfo->sw_patch_version = (uint8)IOHWAB_SW_PATCH_VERSION;
  }
}                                 /* End of IpduM_GetVersionInfo */
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (IOHWAB_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
