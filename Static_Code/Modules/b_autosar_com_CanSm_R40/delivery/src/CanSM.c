/*******************************************************************************
**  (C) 2021 HYUNDAI  AUTOEVER Co., Ltd.								      **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanSM_Init.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : Provision of initialization and its functionality.            **
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
** 1.12.4    12-Jan-2021   SM Kwon        #27641                              **
** 1.12.3    26-Nov-2020   SM Kwon        #25247                              **
** 1.12.0    30-May-2019   SM Kwon        #17202                              **
** 1.11.0    23-Oct-2018   Lim Jong Sun   #14496                              **
** 1.10.3    06-Feb-2018   Lim Jong Sun   #11551                              **
** 1.10.1    23-Mar-2017   Lim Jong Sun   #7877                               **
** 1.10.0    27-Oct-2016   Lim Jong Sun   #7048, #7076                        **
** 1.9.10    24-Jun-2016   Lim Jong Sun   #5314                               **
** 1.9.9     19-May-2016   Lim Jong Sun   #4509                               **
** 1.9.7     19-Jan-2015   Lim Jong Sun   #3905                               **
** 1.0.2     02-Jul-2015   Lim Jong Sun   #2831                               **
** 1.0.1     26-May-2014   Lim Jong Sun   #703                                **     
** 1.0.0     21-Mar-2013   Lim Jong Sun   Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanSM.h"                /* Inclusion of CanSM header */
#include "CanSM_InternalTypes.h"        /* CanSM PCTypes header file */
#if (STD_ON == CANSM_DEM_STATUS)
#include "Dem.h"                  /* Dem header file */
#endif
#if (STD_ON == CANSM_DEV_ERROR_DETECT)
#include "Det.h"                  /* Det header file */
#endif
#include "CanIf.h"                /* CanIf header file */
#include "ComM.h"                 /* ComM header file */
#include "ComM_BusSM.h"           /* ComM_BusSM header file */
#if (STD_ON == CANSM_PN_AVAILABILITY)
#include "CanNm.h"                /* CanNm header file */
#endif
#include "SchM_CanSM.h"           /* SchM Header File*/
#include "CanSM_Ram.h"            /* CanSM_Ram header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANSM_C_AR_RELEASE_MAJOR_VERSION       4
#define CANSM_C_AR_RELEASE_MINOR_VERSION       0
#define CANSM_C_AR_RELEASE_REVISION_VERSION    3

/* CANSM software version information */
#define CANSM_C_SW_MAJOR_VERSION               1
#define CANSM_C_SW_MINOR_VERSION               12

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* CanSM version check */
#if (CANSM_AR_RELEASE_MAJOR_VERSION != CANSM_C_AR_RELEASE_MAJOR_VERSION )
#error "CanSM_Version.c : Mismatch in Specification Major Version"
#endif

#if (CANSM_AR_RELEASE_MINOR_VERSION != CANSM_C_AR_RELEASE_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Minor Version"
#endif

#if (CANSM_AR_RELEASE_REVISION_VERSION != CANSM_C_AR_RELEASE_REVISION_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Patch Version"
#endif

#if (CANSM_SW_MAJOR_VERSION != CANSM_C_SW_MAJOR_VERSION)
#error "CanSM_Version.c : Mismatch in Major Version"
#endif

#if (CANSM_SW_MINOR_VERSION != CANSM_C_SW_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Minor Version"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : CanSM_Init                                          **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This function initializes internal and external     **
**                        interfaces and variables of the CANSM Module for    **
**                        further processing.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ConfigPtr                                           **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_GaaNetwork              **
**                                              CanSM_GblInitStatus           **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
FUNC(void, CANSM_CODE) CanSM_Init(P2CONST(CanSM_ConfigType, AUTOMATIC,
    CANSM_APPL_CONST) ConfigPtr)
{
  NetworkHandleType LddCanSmNwIndex;
  CanSM_ConfigType LddSelectedConfig;

  /* #7877 - Add Feature */
  #if (STD_ON == CANSM_DEM_STATUS)
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;
  #endif

  if(ConfigPtr != NULL_PTR)
  { 
    /* polyspace<MISRA-C3:D4.14 : Not a defect: Justified> Pointer is not a NULL and valid */
    LddSelectedConfig = *ConfigPtr;
  }
  else
  {
    LddSelectedConfig = CanSM_GaaConfig[0];
  }

  CanSm_GucSelectedConfigIdx = LddSelectedConfig.ucConfigIdx;
  CanSm_GddModeReqRepeatTime = LddSelectedConfig.ddModeReqRptTime;
  CanSm_GucModeReqMax = LddSelectedConfig.ucModeReqRptMax;
  CanSM_GpStaticNw = LddSelectedConfig.pStaticNetwork;
    
  LddCanSmNwIndex = (NetworkHandleType)CANSM_NUMBER_OF_NETWORKS;

  /* Loop for all the networks */
  /* #7877 - do ~ while --> while */
  while ((NetworkHandleType)CANSM_ZERO != LddCanSmNwIndex)
  {
    /* Decrement the network index */
    LddCanSmNwIndex = LddCanSmNwIndex - (CANSM_ONE);
	  /* #7877 - Add Feature */
    #if (STD_ON == CANSM_DEM_STATUS)
    /* Get the address of CanSM_GaaStaticNetwork to local pointer */
    LpStaticNetwork = &CanSM_GpStaticNw[LddCanSmNwIndex];
    #endif
    /* Initialize the ModeStatus as Zero */
    CanSM_GaaNetwork[LddCanSmNwIndex].ucModeStatus = CANSM_ZERO;
    /* Initialize busOffCounter as Zero*/
    CanSM_GaaNetwork[LddCanSmNwIndex].ddBusOffCounter =
      (CanSM_BusOffCntType)CANSM_ZERO;
    /* Initialize Internal SubState as Zero*/
    CanSM_GaaNetwork[LddCanSmNwIndex].ucCanSMNWIntSubState = CANSM_ZERO;
    /* Initialize Controller Count as Zero*/
    CanSM_GaaNetwork[LddCanSmNwIndex].ucCanSMCtrlCount = CANSM_ZERO;
    /* Initialize Mode Request Repetition Max Count as Zero */
    CanSM_GaaNetwork[LddCanSmNwIndex].ucCanSMModeReqReptMax =
      (uint8)CanSm_GucModeReqMax;
    /* Initialize Mode Request Repetition Time Count as Zero */
    CanSM_GaaNetwork[LddCanSmNwIndex].ddCanSMModeReqReptTime =
      (CanSM_TimerType)CanSm_GddModeReqRepeatTime;
	
    /* Initialize Bus Off Repetition Count Flag */
    /* Bug #703 - Add to check duplicate Bus off Event while Bus Off Recovery */
  	CanSM_GaaNetwork[LddCanSmNwIndex].ucBusOffRep = CANSM_ZERO;

    #if (STD_ON == CANSM_DEM_STATUS)
  	if(LpStaticNetwork->ddModeEventId != CANSM_DEM_NO_EVENT){
      /* Report the error to DEM with event id and DEM_EVENT_STATUS_PASSED */
      Dem_ReportErrorStatus
        (LpStaticNetwork->ddModeEventId, (Dem_EventStatusType)DEM_EVENT_STATUS_PASSED);
  	}
    #endif
  }

  #if (STD_ON == CANSM_DEV_ERROR_DETECT)
  /* Set the init state to  CANSM_INITED */
  CanSM_GblInitStatus = (boolean)CANSM_INITED;
  #endif  
} /* End of CanSM_Init(P2CONST(CanSM_ConfigType, AUTOMATIC, CANSM_APPL_CONST)
   *ConfigPtr) */
/* polyspace:end <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_GetVersionInfo                                **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This service returns the version information of     **
**                        this module.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** Output Parameters    : Std_VersionInfoType *versioninfo                    **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/
#if (STD_ON == CANSM_VERSION_INFO_API)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_GetVersionInfo(P2VAR(Std_VersionInfoType,
    AUTOMATIC, CANSM_APPL_DATA) versionInfo)
{
  #if (STD_ON == CANSM_DEV_ERROR_DETECT)
  Std_ReturnType LddResult;
  LddResult = (Std_ReturnType)E_OK;

  /* Check whether Version Information is equal to Null Ptr */
  CANSM_CHECK_INVALID_POINTER(LddResult, versionInfo,
    CANSMSERVICEID_GETVERSIONINFO);

  if ((Std_ReturnType)E_OK == LddResult)
  #endif
  {
    /* polyspace-begin MISRA-C3:D4.14 [Not a defect:Justified] "Pointer is not a NULL and valid" */
    /* Copy the vendor Id */
    versionInfo->vendorID = CANSM_VENDOR_ID;

    /* Copy the module Id */
    versionInfo->moduleID = CANSM_MODULE_ID;

    /* Copy Software Major Version */
    versionInfo->sw_major_version = (uint8)CANSM_SW_MAJOR_VERSION;

    /* Copy Software Minor Version */
    versionInfo->sw_minor_version = (uint8)CANSM_SW_MINOR_VERSION;
    /* polyspace-end MISRA-C3:D4.14 [Not a defect:Justified] "Pointer is not a NULL and valid" */
  }
} /* End of CanSM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC,
   *CANSM_APPL_DATA) versionInfo) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANSM_VERSION_INFO_API) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
