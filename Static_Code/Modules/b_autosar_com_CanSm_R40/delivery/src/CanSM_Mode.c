/*******************************************************************************
**  (C) 2021 HYUNDAI  AUTOEVER Co., Ltd.								                      **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanSM_Mode.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : Provision of the funtionality of CanSM_GetCurrentComMode()    **
**              and CanSM_RequestComMode()                                    **
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
** 1.12.5    27-Dec-2021   SM Kwon        #33358                              **
** 1.12.4    12-Jan-2021   SM Kwon        #27641                              **
** 1.12.3    25-Nov-2020   SM Kwon        #25247                              **
** 1.12.1    22-Aug-2019   SM Kwon        #18962                              **
** 1.12.0    30-May-2019   SM Kwon        #17202                              **
** 1.11.0    23-Oct-2018   Lim Jong Sun   #14496                              **
** 1.10.0    27-Oct-2016   Lim Jong Sun   #7076                               **
** 1.9.11    18-Jul-2016   Lim Jong Sun   #5557                               **
** 1.9.8     25-Apr-2016   Lim Jong Sun   #4734                               **
** 1.9.7     19-Jan-2015   Lim Jong Sun   #3905 ,#4075                        **
** 1.9.4     28-Aug-2015   Lim Jong Sun   #2525                               **
** 1.0.0     21-Mar-2013   Lim Jong Sun   Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanSM_InternalTypes.h"        /* CanSM PCTypes header file */
#include "CanSM_Internal.h"       /* CanSM_Main header */
#include "CanSM_Ram.h"            /* CanSM_Ram header file */
#include "CanSM_ComM.h"           /* CanSM_ComM header */
#include "CanSM_Error.h"          /* CanSM_Error header */  
#if (STD_ON == CANSM_DEV_ERROR_DETECT)
#include "Det.h"                  /* Det header file */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANSM_MODE_C_RELEASE_MAJOR_VERSION       4
#define CANSM_MODE_C_RELEASE_MINOR_VERSION       0
#define CANSM_MODE_C_RELEASE_REVISION_VERSION    3

/* CANSM software version information */
#define CANSM_MODE_C_SW_MAJOR_VERSION            1
#define CANSM_MODE_C_SW_MINOR_VERSION            12

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* CanSM version check */
#if (CANSM_AR_RELEASE_MAJOR_VERSION != CANSM_MODE_C_RELEASE_MAJOR_VERSION )
#error "CanSM_Version.c : Mismatch in Specification Major Version"
#endif

#if (CANSM_AR_RELEASE_MINOR_VERSION != CANSM_MODE_C_RELEASE_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Minor Version"
#endif

#if (CANSM_AR_RELEASE_REVISION_VERSION != CANSM_MODE_C_RELEASE_REVISION_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Patch Version"
#endif

#if (CANSM_SW_MAJOR_VERSION != CANSM_MODE_C_SW_MAJOR_VERSION)
#error "CanSM_Version.c : Mismatch in Major Version"
#endif

#if (CANSM_SW_MINOR_VERSION != CANSM_MODE_C_SW_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Minor Version"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* polyspace:begin <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
/* extern for CanSM_GetCurrentComModeDetCheck */
#define CANSM_START_SEC_CODE
#include "MemMap.h"/* Memmap header file */
static FUNC(Std_ReturnType, CANSM_CODE) CanSM_GetCurrentComModeDetCheck(
  NetworkHandleType NetworkHandle, P2VAR(ComM_ModeType, AUTOMATIC,
    CANSM_APPL_DATA) ComM_ModePtr);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"/* Memmap header file */

/* extern for CanSM_GetCurrentComModeDetCheck */
#define CANSM_START_SEC_CODE
#include "MemMap.h"/* Memmap header file */
static FUNC(Std_ReturnType, CANSM_CODE) CanSM_RequestComModeDetCheck
                    (NetworkHandleType  NetworkHandle, ComM_ModeType ComM_Mode);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"/* Memmap header file */

/*******************************************************************************
** Function Name        : CanSM_GetCurrentComMode                             **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This service puts out the current communication     **
**                        mode for the network handle to the pointer of type  **
**                        ComM_ModeType.                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
**  Re-entrancy         : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType NetworkHandle,                    **
**                        ComM_ModeType *ComM_ModePtr                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK/E_NOT_OK                                       **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_GaaNetwork              **
**                                              CanSM_GaaInternalNetwork      **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_GetCurrentComMode(NetworkHandleType
  NetworkHandle, P2VAR(ComM_ModeType, AUTOMATIC,
    CANSM_APPL_DATA) ComM_ModePtr)
{
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  NetworkHandleType LddNetworkHandle;
  Std_ReturnType LddResult;
  uint8 LucModeStatus;
  #if (STD_OFF == CANSM_DEV_ERROR_DETECT)
  LddResult = (uint8)E_OK;
  #endif
  #if (STD_ON == CANSM_DEV_ERROR_DETECT)
  LddResult = CanSM_GetCurrentComModeDetCheck(NetworkHandle, ComM_ModePtr);
  if ((uint8)E_OK == LddResult)
  #endif
  {
    /* load the internal network value from map array */
    /* polyspace +1 MISRA-C3:D4.14,18.1, RTE:OBAI [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
    LddNetworkHandle = CanSM_GaaInternalNetwork[CanSm_GucSelectedConfigIdx][NetworkHandle];

    /* Get the address of CanSM_GaaNetwork to local pointer */
    LpNetwork = &CanSM_GaaNetwork[LddNetworkHandle];

    /* Get the current mode status */
    /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Generated array index in range" */
    LucModeStatus = LpNetwork->ucModeStatus;

    switch (LucModeStatus)
    {
      /* Current network mode is COMM_NO_COMMUNICATION */
      /* polyspace-begin MISRA-C3:D4.14 [Not a defect:Justified] "Pointer is not a NULL and valid" */
      case CANSM_NOCOMMUNICATION:
      case CANSM_NOTOFULLCOMMREQUESTED:
      case CANSM_DEINITPNNOTSUPPORTED:
      case CANSM_DEINITPNSUPPORTED:
        *ComM_ModePtr = (ComM_ModeType)COMM_NO_COMMUNICATION;

        /* MISRA Rule   : D4.14
         *   Message      : Dereferencing pointer value that is apparently NULL.
         *   Reason       : The pointer gets the current state of the network,
         *                  which is COMM_NO_COMMUNICATION ( value = 0)
         *   Verification : However, part of the code is verified manually
         *                  and it is not having any impact.
         */
        break;

      /* Current network mode is COMM_SILENT_COMMUNICATION */
      case CANSM_SILENTCOMMUNICATION:
      case CANSM_SILENTTOFULLCOMMREQUESTED:
      case CANSM_BORSTART:
      case CANSM_BORWAIT:
        *ComM_ModePtr = (ComM_ModeType)COMM_SILENT_COMMUNICATION;
        break;

      /* Current network mode is COMM_FULL_COMMUNICATION */
      default:
        *ComM_ModePtr = (ComM_ModeType)COMM_FULL_COMMUNICATION;
        break;
      /* polyspace-end MISRA-C3:D4.14 [Not a defect:Justified] "Pointer is not a NULL and valid" */	
    } /* End of switch (LucModeStatus) */
  } /* End of if ((Std_ReturnType)E_OK == LddResult) */
  return (LddResult);
} /*End of CanSM_GetCurrentComMode*/

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_RequestComMode                                **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : This service stores the requested                   **
**                        communication mode for the network handle and shall **
**                        execute the corresponding network mode state        **
**                        machine.                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType NetworkHandle                     **
**                        ComM_ModeType ComM_Mode                             **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK/E_NOT_OK                                       **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_GaaInternalNetwork[CanSm_GucSelectedConfigIdx]      **
**                                              CanSM_GpStaticNw              **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_RequestComMode(NetworkHandleType
  NetworkHandle, ComM_ModeType ComM_Mode)
{
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  #if (STD_OFF == CANSM_SINGLE_NW_CHANNEL)
  NetworkHandleType LddNetworkHandle;
  #endif
  Std_ReturnType LddResult;
  #if ((STD_OFF == CANSM_DEV_ERROR_DETECT) && \
  (STD_ON == CANSM_SINGLE_NW_CHANNEL))
  CANSM_UNUSED(NetworkHandle);
  #endif
  #if (STD_OFF == CANSM_DEV_ERROR_DETECT)
  LddResult = (uint8)E_OK;
  #else
  LddResult = CanSM_RequestComModeDetCheck(NetworkHandle, ComM_Mode);

  if ((uint8)E_OK == LddResult)
  #endif /* End of if (STD_ON == CANSM_DEV_ERROR_DETECT) */
  {
    #if (STD_OFF == CANSM_SINGLE_NW_CHANNEL)
    /* Load the network handle in the local variable */
    /* polyspace +1 MISRA-C3:D4.14,18.1, RTE:OBAI [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
    LddNetworkHandle = CanSM_GaaInternalNetwork[CanSm_GucSelectedConfigIdx][NetworkHandle];
    #endif
    /* Load the address of Network in local variable */
    LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];

    /* Enter Protection Area */
    SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

    /* Load network internal state to local variable */
    /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Generated array index in range" */
    LpNetwork->ucReqModeStatus = (uint8)ComM_Mode;

    /* Exit Protection area */
    SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
  }
  return (LddResult);
} /*End of CanSM_RequestComMode*/

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_GetCurrentComModeDetCheck                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service performs the Det check for API         **
**                        CanSM_GetCurrentComMode.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType NetworkHandle                     **
**                        ComM_ModeType ComM_Mode                             **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK/E_NOT_OK                                       **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_GblInitStatus           **
**                                              CanSM_GaaInternalNetwork      **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
#if (STD_ON == CANSM_DEV_ERROR_DETECT)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, CANSM_CODE)
CanSM_GetCurrentComModeDetCheck(NetworkHandleType NetworkHandle, P2VAR(
    ComM_ModeType, AUTOMATIC, CANSM_VAR) ComM_ModePtr)
{
  NetworkHandleType LddNetworkHandle;
  Std_ReturnType LddResult;

  LddResult = (uint8)E_OK;

  /* Report the error to DET with CANSM_E_UNINIT */
  CANSM_INITED_DET_CHECK(LddResult, CANSMSERVICEID_GETCURRENTCOMMODE);

  /* Check if CanSM is greater than last network handle */
  CANSM_CHECK_INVALID_NETWORK(LddResult, NetworkHandle,
                                               CANSMSERVICEID_GETCURRENTCOMMODE);
  
  if ((Std_ReturnType)E_OK == LddResult)
  {
    /* polyspace +2 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
    /* load the internal network value from map array */
    LddNetworkHandle = CanSM_GaaInternalNetwork[CanSm_GucSelectedConfigIdx][NetworkHandle];
    /* Check if network handle is Invalid */
    CANSM_CHECK_INVALID_NETWORK_HANDLE(LddResult, LddNetworkHandle,
      CANSMSERVICEID_GETCURRENTCOMMODE);
  }else
  {
    
  }
  if ((Std_ReturnType)E_OK == LddResult)
  {
    /* Check if the pointer is NULL pointer */
    CANSM_CHECK_INVALID_POINTER(LddResult, ComM_ModePtr,
      CANSMSERVICEID_GETCURRENTCOMMODE);
  }
  else
  {
   
  }
  return (LddResult);
} /*End Of CanSM_GetCurrentComModeDetCheck*/

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANSM_DEV_ERROR_DETECT) */
/*******************************************************************************
** Function Name        : CanSM_RequestComModeDetCheck                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service performs the Det check for API         **
**                        CanSM_RequestComMode.                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType NetworkHandle                     **
**                        ComM_ModeType ComM_Mode                             **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK/E_NOT_OK                                       **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_GblInitStatus           **
**                                              CanSM_GaaInternalNetwork      **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
#if (STD_ON == CANSM_DEV_ERROR_DETECT)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, CANSM_CODE) CanSM_RequestComModeDetCheck
                     (NetworkHandleType  NetworkHandle, ComM_ModeType ComM_Mode)
{
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  NetworkHandleType LddNetworkHandle;
  Std_ReturnType LddResult;
  uint8 LucModeStatus;
  LddResult = (uint8)E_OK;

  /* Report the error to DET with CANSM_E_UNINIT */
  CANSM_INITED_DET_CHECK(LddResult, CANSMSERVICEID_REQCOMMODE);

  /* Check if CanSM is greater than last network handle */
  CANSM_CHECK_INVALID_NETWORK(LddResult, NetworkHandle,
    CANSMSERVICEID_REQCOMMODE);

  if ((uint8)E_OK == LddResult)
  {
    /* polyspace +2 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
    /* Load the network handle in the local variable */
    LddNetworkHandle = CanSM_GaaInternalNetwork[CanSm_GucSelectedConfigIdx][NetworkHandle];

    #if(CANSM_INVALID_NW_IN_INTERNAL_NW == STD_ON)
    /* Check if network handle is Invalid */
    CANSM_CHECK_INVALID_NETWORK_HANDLE(LddResult, LddNetworkHandle,
      CANSMSERVICEID_REQCOMMODE);
    /* polyspace +1 MISRA-C3:14.3, DEFECT:USELESS_IF [Not a defect:Justified] "condition will be executed based on the configured values" */	
    if ((uint8)E_OK == LddResult)
    #endif
    {
    
      /* Load the address of Network in local variable */
      LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];

      /* Load the current staus of the network */
      LucModeStatus = LpNetwork->ucModeStatus;

      /* Check if requested Mode is Correct */
      CANSM_INVALID_COMM_REQUEST_DET_CHECK(LddResult, ComM_Mode, LucModeStatus,
        CANSMSERVICEID_REQCOMMODE);

      /* Check if Network mode is requested during pending indication */
      CANSM_CHECK_WAIT_MODE_INDICATION(LddResult, LucModeStatus,
                                                    CANSMSERVICEID_REQCOMMODE);
    }
  }
  return (LddResult);
} /*End Of CanSM_RequestComModeDetCheck*/

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANSM_DEV_ERROR_DETECT) */
/* polyspace:end <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
