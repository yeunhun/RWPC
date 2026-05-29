/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTOEVER Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: PduR_Grp.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Provision of Enabling and Disabling Routing path groups       **
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
** 2.4.0     06-Sep-2019   HM Shin     #18909                                 **
** 2.3.0     22-Aug-2019   JS Lim      #18336                                 **
** 2.2.0     01-Feb-2017   Chan Kim    Redmine #6922                          **
** 2.1.0     17-Jun-2016   Chan Kim    Redmine #5190                          **
** 2.0.3     24-Nov-2015   Chan Kim    Redmine #3545, #4519                   **
** 2.0.0     11-Aug-2015   Chan Kim    Redmine #2949                          **
** 1.0.7     10-Jun-2013   Chan Kim    Change code for release Library        **
** 1.0.0     29-Apr-2013   Autoever      Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "PduR.h"
#include "SchM_PduR.h"            /* Schm header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define PDUR_GRP_C_AR_RELEASE_MAJOR_VERSION     4
#define PDUR_GRP_C_AR_RELEASE_MINOR_VERSION     0
#define PDUR_GRP_C_AR_RELEASE_REVISION_VERSION  3

/* Software Version Information */
#define PDUR_GRP_C_SW_MAJOR_VERSION            2
#define PDUR_GRP_C_SW_MINOR_VERSION            9
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (PDUR_AR_RELEASE_MAJOR_VERSION != PDUR_GRP_C_AR_RELEASE_MAJOR_VERSION)
  #error "PduR_Grp.c : Mismatch in Specification  Major Version"
#endif
#if (PDUR_AR_RELEASE_MINOR_VERSION != PDUR_GRP_C_AR_RELEASE_MINOR_VERSION)
  #error "PduR_Grp.c : Mismatch in Specification  Minor Version"
#endif
#if (PDUR_AR_RELEASE_REVISION_VERSION != \
  PDUR_GRP_C_AR_RELEASE_REVISION_VERSION)
  #error "PduR_Grp.c : Mismatch in Specification Revision Version"
#endif
#if (PDUR_SW_MAJOR_VERSION != PDUR_GRP_C_SW_MAJOR_VERSION)
  #error "PduR_Grp.c : Mismatch in Software Major Version"
#endif
#if (PDUR_SW_MINOR_VERSION != PDUR_GRP_C_SW_MINOR_VERSION)
  #error "PduR_Grp.c : Mismatch in Software Minor Version"
#endif
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : PduR_EnableRouting                                  **
**                                                                            **
** Service ID           : 0xF3                                                **
**                                                                            **
** Description          : This Service initializes PDU Routing path groups    **
**                        If the configuration parameter                      **
**                        PDUR_ROUTINGPATH_GROUP_SUPPORT is enabled this      **
**                        service shall be realized as an empty function-like **
**                        macro                                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : PduR_RoutingPathGroupIdType id                      **
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
**                        PduR_GulGroupMaskValue, PduR_GblInitStatus,         **
**                        PduR_Max_RoutingPath_Group_ID                       **
**                                                                            **
** Function(s) invoked  : Det_ReportError(),                                  **
**                        SchM_Enter_PduR_GROUP_STATUS_PROTECTION_AREA(),     **
**                        SchM_Exit_PduR_GROUP_STATUS_PROTECTION_AREA()		  **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
FUNC(void, PDUR_VAR) PduR_EnableRouting(PduR_RoutingPathGroupIdType id )
{
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  boolean LblErrorFlag;
  LblErrorFlag = TRUE;
  if ((boolean)PDUR_UNINITIALIZED == PduR_GblInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      PDUR_ENABLE_ROUTING_SID, PDUR_E_INVALID_REQUEST);
    /* Set the return value to True */
    LblErrorFlag = (boolean)FALSE;
  } /* End of if (PDUR_UNINITIALIZED == PduR_GblInitStatus) */
  else
  {
    /* Check whether the Group Id Is present */
    if (id > (PduR_RoutingPathGroupIdType)PduR_Max_RoutingPath_Group_ID)
    {
      /* Report to DET */
      (void)Det_ReportError (PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        PDUR_ENABLE_ROUTING_SID, PDUR_E_ROUTING_PATH_GROUP_ID_INVALID);
      LblErrorFlag = (boolean)FALSE;
    }
  }

  /* Check whether any development errors are detected */
  if((boolean)TRUE == LblErrorFlag)
  #endif /* #PDUR_DEV_ERROR_DETECT = STD_ON) */
  {
    uint16 LusBytePos = 0;
    uint8 LucBitPos = 0;

    LusBytePos = (id >> 3);
    LucBitPos = (uint8)(id % 8);
    
    /* Disable relevant interrupts */
    SchM_Enter_PduR_GROUP_STATUS_PROTECTION_AREA();

    /*Enable the routing path group*/
    /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid to 'Unreachable code' of the polyspace */
    if ((uint16)PDUR_ROUTINGPATH_GROUP_ARRAY_SIZE > LusBytePos)
    {
      PduR_GaaRoutingPathGroupRam[LusBytePos] |= (uint8)((uint8)1 << LucBitPos);
    }

    /* Enable relevant interrupts */
    SchM_Exit_PduR_GROUP_STATUS_PROTECTION_AREA();
  }
} /* End of PduR_EnableRouting(PduR_RoutingPathGroupIdType id ) */

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

/*******************************************************************************
** Function Name        : PduR_DisableRouting                                 **
**                                                                            **
** Service ID           : 0xF4                                                **
**                                                                            **
** Description          : This Service Disables PDU Routing path groups If the**
**                        configuration parameter                             **
**                        PDUR_ROUTINGPATH_GROUP_SUPPORT is enabled this      **
**                        service shall be realized as an empty function-like **
**                        macro                                               **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : PduR_RoutingPathGroupIdType id                      **
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
**                        PduR_GulGroupMaskValue, PduR_GblInitStatus,         **
**                        PduR_Max_RoutingPath_Group_ID                       **
**                                                                            **
** Function(s) invoked  : Det_ReportError(),                                  **
**                        SchM_Enter_PduR_GROUP_STATUS_PROTECTION_AREA(),     **
**                        SchM_Exit_PduR_GROUP_STATUS_PROTECTION_AREA()		  **              
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)

#define PDUR_START_SEC_CODE
#include "MemMap.h"

FUNC(void, PDUR_VAR) PduR_DisableRouting(PduR_RoutingPathGroupIdType id)
{
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  boolean LblErrorFlag;
  LblErrorFlag = TRUE;
  if ((boolean)PDUR_UNINITIALIZED == PduR_GblInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      PDUR_DISABLE_ROUTING_SID, PDUR_E_INVALID_REQUEST);
    /* Set the return value to FALSE */
    LblErrorFlag = (boolean)FALSE;
  } /* End of if (PDUR_UNINITIALIZED == PduR_GblInitStatus) */
  else
  {
    /* Check whether the Group Id Is present */
    if (id > (PduR_RoutingPathGroupIdType)PduR_Max_RoutingPath_Group_ID)
    {
      /* Report to DET */
      (void)Det_ReportError (PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        PDUR_DISABLE_ROUTING_SID, PDUR_E_ROUTING_PATH_GROUP_ID_INVALID);
      LblErrorFlag = (boolean)FALSE;
    }
  }
  /* Check whether any development errors are detected */
  if((boolean)TRUE == LblErrorFlag)
  #endif  /* #if(PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    uint16 LusBytePos = 0;
    uint8 LucBitPos = 0;
  
    LusBytePos = (id >> 3);
    LucBitPos = (uint8)(id % 8);
    
    /* Disable relevant interrupts */
    SchM_Enter_PduR_GROUP_STATUS_PROTECTION_AREA();

    /*Disable the routing path group*/
    /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid to 'Unreachable code' of the polyspace */
    if ((uint16)PDUR_ROUTINGPATH_GROUP_ARRAY_SIZE > LusBytePos)
    {
      PduR_GaaRoutingPathGroupRam[LusBytePos] &= (uint8)(~(uint8)((uint8)1 << LucBitPos));
    }

    /* Enable relevant interrupts */
    SchM_Exit_PduR_GROUP_STATUS_PROTECTION_AREA();
  }
} /* End of PduR_DisableRouting(PduR_RoutingPathGroupIdType id) */

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

/*******************************************************************************
** Function Name        : PduR_GetRoutingGroupStatus                          **
**                                                                            **
** Service ID           : 0xF3                                                **
**                                                                            **
** Description          : This Service initializes PDU Routing path groups    **
**                        If the configuration parameter                      **
**                        PDUR_ROUTINGPATH_GROUP_SUPPORT is enabled this      **
**                        service shall be realized as an empty function-like **
**                        macro                                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : PduR_RoutingPathGroupIdType id                      **
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
**                        PduR_GulGroupMaskValue, PduR_GblInitStatus,         **
**                        PduR_Max_RoutingPath_Group_ID                       **
**                                                                            **
** Function(s) invoked  : Det_ReportError(),                                  **
**                        SchM_Enter_PduR_GROUP_STATUS_PROTECTION_AREA(),     **
**                        SchM_Exit_PduR_GROUP_STATUS_PROTECTION_AREA()		  **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
FUNC(void, PDUR_VAR) PduR_GetRoutingPathGroupStatus(PduR_RoutingPathGroupIdType id, P2VAR(uint8, AUTOMATIC, PDUR_VAR) pStatus)
{
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  boolean LblErrorFlag;
  LblErrorFlag = TRUE;
  if ((boolean)PDUR_UNINITIALIZED == PduR_GblInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      PDUR_ENABLE_ROUTING_SID, PDUR_E_INVALID_REQUEST);
    /* Set the return value to True */
    LblErrorFlag = (boolean)FALSE;
  } /* End of if (PDUR_UNINITIALIZED == PduR_GblInitStatus) */
  else
  {
    /* Check whether the Group Id Is present */
    if (id > (PduR_RoutingPathGroupIdType)PduR_Max_RoutingPath_Group_ID)
    {
      /* Report to DET */
      (void)Det_ReportError (PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        PDUR_ENABLE_ROUTING_SID, PDUR_E_ROUTING_PATH_GROUP_ID_INVALID);
      LblErrorFlag = (boolean)FALSE;
    }
  }

  /* Check whether any development errors are detected */
  if((boolean)TRUE == LblErrorFlag)
  #endif /* #PDUR_DEV_ERROR_DETECT = STD_ON) */
  {
    /* Disable relevant interrupts */
    SchM_Enter_PduR_GROUP_STATUS_PROTECTION_AREA();
    /*Enable the routing path group*/
    if ((uint8)PDUR_ZERO == (PduR_GaaRoutingPathGroupRam[id >> 3] & ((uint8)1 << (uint8)(id % 8))))
    {
      /* polyspace<MISRA-C3:D4.14 :: Not a defect Justified> Pointer is not a NULL and valid */	
      *pStatus = (uint8)PDUR_ROUTING_DISABLED;
    }
    else
    {
      /* polyspace<MISRA-C3:D4.14 :: Not a defect Justified> Pointer is not a NULL and valid */
      *pStatus = (uint8)PDUR_ROUTING_ENABLED;
    }
    /* Enable relevant interrupts */
    SchM_Exit_PduR_GROUP_STATUS_PROTECTION_AREA();
  }
} /* End of PduR_EnableRouting(PduR_RoutingPathGroupIdType id ) */

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
