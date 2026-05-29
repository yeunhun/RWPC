/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTOEVER Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: PduR_Init.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Provision of Initialization and version control functionality **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 2.6.0     03-Nov-2020   HM Shin     #24937                                 **
** 2.2.0     01-Feb-2017   Chan Kim    Redmine #6922                          **
** 2.1.0     17-Jun-2016   Chan Kim    Redmine #5190                          **
** 2.0.8     10-Jun-2016   Chan Kim    Redmine #5143                          **
** 2.0.4     19-Feb-2016   Chan Kim    Redmine #3813                          **
** 2.0.3     24-Nov-2015   Chan Kim    Redmine #3545, #4519                   **
** 2.0.0     11-Aug-2015   Chan Kim    Redmine #2949                          **
** 1.0.0     29-Apr-2013   Autoever      Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "PduR.h"                /* PDU Router RAM header */
#include "SchM_PduR.h"           /* SchM header */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : PduR_Init                                           **
**                                                                            **
** Service ID           : 0xF0                                                **
**                                                                            **
** Description          : This Service initializes PDU Router initialization. **
**                        If the configuration parameter                      **
**                        PDUR_ZERO_COST_OPERATION is enabled this service    **
**                        shall be realized as an empty function-like macro.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : PduR_PBConfigType *ConfigPtr                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        PduR_GblInitStatus, PduR_GulGroupMaskValue          **
**                        PduR_Group_Mask_Value                               **
**                                                                            **
** Function(s) invoked  : None                                                **
**                                                                            **
*******************************************************************************/
/* Requirement PDUR334 */
#define PDUR_START_SEC_CODE
#include "MemMap.h"
FUNC(void, PDUR_CODE) PduR_Init(P2CONST(PduR_PBConfigType, AUTOMATIC,
    PDUR_APPL_CONST) ConfigPtr)
{
  #if(PDUR_FIFO_BUFFER_INDEX_COUNT > PDUR_ZERO)
  #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)  
  uint16 LusLoopIndex;
  for(LusLoopIndex = PDUR_ZERO; LusLoopIndex < PduR_FIFO_Buffer_Index_Count;
  LusLoopIndex++)
  {
    PduR_GaaFifoBuffer[LusLoopIndex].ucRead = PDUR_ZERO;
    PduR_GaaFifoBuffer[LusLoopIndex].ucWrite = PDUR_ZERO;
    PduR_GaaFifoBuffer[LusLoopIndex].ucDepth = PDUR_ZERO;        
  }
  #endif
  #endif


  #if (PDUR_ZERO_COST_OPERATION == STD_OFF)

  /* Minimum routing feature is not implemented as per Autosar Bugzilla No
   35676 - The PDU Router module shall consist of two states, PDUR_UNINIT and
   PDUR_ONLINE*/
  /* Set the InitStatus to PDUR_INITIALIZED */
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  PduR_GblInitStatus = (boolean)PDUR_ONLINE;
  #endif /* End of #if (PDUR_DEV_ERROR_DETECT == STD_ON) */

  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  #if (PDUR_ROUTINGPATH_GROUP_ARRAY_SIZE > PDUR_ZERO)
  /* polyspace +2 MISRA-C3:D4.11, RTE:STD_LIB [Not a defect: Justify with annotations] "Valid arguments are passed" */
  memcpy(PduR_GaaRoutingPathGroupRam, PduR_GaaRoutingPathGroup, PDUR_ROUTINGPATH_GROUP_ARRAY_SIZE);
  #endif
  #endif

  #endif /* End of #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */
  /* To avoid Compiler warning since "ConfigPtr" is not used in the function */
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid to 'Unreachable code' of the polyspace */
  PDUR_UNUSED_PTR(ConfigPtr);

} /* End of PduR_Init(P2CONST(PduR_PBConfigType, AUTOMATIC, PDUR_CONST)
   *ConfigPtr) */

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : PduR_GetVersionInfo                                 **
**                                                                            **
** Service ID           : 0xF1                                                **
**                                                                            **
** Description          : This service returns the version information of     **
**                        this module.                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Std_VersionInfoType *versioninfo                    **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        None                                                **
**                                                                            **
** Function(s) invoked :  Det_ReportError()                                   **
**                                                                            **
*******************************************************************************/
/* Requirement PDUR338 */
#if (PDUR_VERSION_INFO_API == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
FUNC(void, PDUR_CODE) PduR_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC,
    PDUR_APPL_DATA) versioninfo)
{
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  /* Check whether Version Information is equal to Null Ptr */
  if (NULL_PTR == versioninfo)
  {
    /* Report to DET  */
    (void)(Det_ReportError(PDUR_MODULE_ID, PDUR_ZERO, PDUR_GET_VERSION_SID,
      PDUR_E_NULL_POINTER));
  }
  else
  #endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Requirement PDUR234 - PduR_GetVersionInfo shall return the version
    information of this module in the passed argument *versionInfo*/
    /* Copy the vendor Id */
    versioninfo->vendorID = PDUR_VENDOR_ID;
    /* Copy the module Id */
    versioninfo->moduleID = PDUR_MODULE_ID;
    /* Copy Software Major Version */
    versioninfo->sw_major_version = PDUR_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    versioninfo->sw_minor_version = PDUR_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    versioninfo->sw_patch_version = PDUR_SW_PATCH_VERSION;
  }
} /* End of PduR_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC,
   *PDUR_APPL_DATA) versioninfo) */

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
