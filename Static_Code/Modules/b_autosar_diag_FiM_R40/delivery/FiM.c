/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: FiM.c                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Function Inhibition Manager Module                    **
**                                                                            **
**  PURPOSE   : Provision of FiM APIs                                         **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By            Description                          **
********************************************************************************
** 1.1.0     30-09-2016    Youngjin Yun  Redmine #3280                        **
**                                                                            **
** 1.0.6     14-01-2016    Youngjin Yun  Redmine #2386                        **
**                                                                            **
** 1.0.2     14-01-2013    Autron        Initial version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "FiM.h"                     /* FiM Header File */
#include "Dem.h"                     /* Dem Header File */
#include "SchM_FiM.h"                /* SchM Header File */
#include "Rte_FiM.h"                 /* Rte Header File */
#if (FIM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                     /* Det header file */
#endif
#include "FiM_InternalFunc.h"        /* Internal Func header file */

/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "Not a defect" */
/*******************************************************************************
**                           Global Data                                      **
*******************************************************************************/
#define FIM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Define the mask value for each type of MASK */
CONST(uint8, FIM_CONST) FiM_GaaMaskValues[FIM_FOUR] =
{
   FIM_MASK_LAST_FAILED,
   FIM_MASK_NOT_TESTED,
   FIM_MASK_TESTED,
   FIM_MASK_TESTED_AND_FAILED
};

#define FIM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


#define FIM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Define the expected result for each type of MASK */
CONST(uint8, FIM_CONST) FiM_GaaExpMaskedResult[FIM_FOUR] =
{
   FIM_EXP_STS_LAST_FAILED,
   FIM_EXP_STS_NOT_TESTED,
   FIM_EXP_STS_TESTED,
   FIM_EXP_STS_TESTED_AND_FAILED
};

#define FIM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/*
  MISRA Rule         : 19.4
  Message            : C macros shall only expand to a braced initialiser,
                       a constant, a parenthesised expression, a type
                       qualifier, a storage class specifier, or a do-while-zero
                       construct.
  Reason             : To avoid Compilation Warning "Dead Assignment to
                       LddReturn" FIM_RETURN_VALUE macro is defined.
  Verification       : However, part of the code is
                       verified manually and it is not
                       having any impact.
*/


/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define FIM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : FiM_Init                                            **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This service shall initialize the permission states **
**                        of the FIDs based on the event data of the Dem.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : FiMConfigPtr                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        FiM_GblInitStatus                                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        FiM_CalcAllFidsPermissions,                         **
**                        Det_ReportError                                     **
*******************************************************************************/
FUNC(void,FIM_CODE)FiM_Init
  (P2CONST(FiM_ConfigType, AUTOMATIC, FIM_APPL_CONST)FiMConfigPtr)
{
  FiM_FidsSizeType LddFid;
  
  FiM_GblInitStatus = FIM_NOT_INITIALIZED;  

  /* Enter Data Protection */
  SchM_Enter_FiM_REQUEST_FID_PROTECTION();

  /* Reset FID counters for all the configured Fids */
  for(LddFid = 0U; LddFid < Fim_Total_Num_Of_Fids; LddFid++)
  {
    FiM_GaaFidInhibitCounter[LddFid] = 0U;
   /* Clear permission state */
    FiM_GaaFidPermissionState[LddFid] = FIM_FALSE;    
  }

  /* Exit Data Protection*/
  SchM_Exit_FiM_REQUEST_FID_PROTECTION();
  

  if(FiMConfigPtr != NULL_PTR)
  {
    /* To avoid compilation and Misra warning */
  }
}


/*******************************************************************************
** Function Name        : FiM_DemTriggerOnEventStatus                         **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : This service shall be provided by the Dem in order  **
**                        to call FiM upon event status change                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EventId                                             **
**                        EventStatusOld                                      **
**                        EventStatusNew                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        FiM_GblInitStatus, FiM_GaaEventInfo,                **
**                        FiM_GaaFunctionIdMask, FiM_GaaMaskValues,           **
**                        FiM_GaaExpMaskedResult, FiM_GaaFidInhibitCounter,   **
**                        FiM_GaaFidPermissionState                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError, FiM_EventIdBinarySearch,           **
**                        SchM_Enter_FiM_REQUEST_EVENTID_PROTECTION,          **
**                        SchM_Exit_FiM_REQUEST_EVENTID_PROTECTION            **
*******************************************************************************/
/* Check if FIM_EVENT_UPDATE_TRIGGERED_BY_DEM == STD_ON */
#if (FIM_EVENT_UPDATE_TRIGGERED_BY_DEM == STD_ON)
FUNC(void, FIM_CODE) FiM_DemTriggerOnEventStatus
/* polyspace<MISRA-C:5.6:Not a defect:Justify with annotations> EventId : AUTOSAR Standard */
 (Dem_EventIdType EventId, Dem_EventStatusExtendedType EventStatusOld,
  Dem_EventStatusExtendedType EventStatusNew)
{
  FiM_FidsSizeType LddFidCount;
  FiM_FidsSizeType LddNoOfFids;
  FiM_FidsSizeType LddFidArrayIndex;
  FiM_EventFidLinkType LddEventFidLink;
  FiM_EventsSizeType LddEventArrayIndex = (FiM_EventsSizeType)0x00;
  uint8 LucInhMask;
  boolean LblEventExists;

  #if (FIM_DEV_ERROR_DETECT == STD_ON)
  boolean LblDevErrorFlag;

  LblDevErrorFlag = FIM_FALSE;
  /* Check if the FiM Module is initialized */
  if(FiM_GblInitStatus != FIM_INITIALIZED)
  {
    /* Report to DET indicating WrongTriggerOnEvent */
    (void)Det_ReportError(FIM_MODULE_ID, FIM_INSTANCE_ID,
      FIM_DEMTRIGGERONEVENTSTATUS_SID, FIM_E_WRONG_TRIGGER_ON_EVENT);

    /* Set the development error flag */
    LblDevErrorFlag = FIM_TRUE;
  }

  /* Check if the Event Status is valid or not */
  if(EventStatusOld == EventStatusNew)
  {
    /* Report to DET indicating Wrong event status */
    (void)Det_ReportError(FIM_MODULE_ID, FIM_INSTANCE_ID,
    FIM_DEMTRIGGERONEVENTSTATUS_SID, FIM_E_INVALID_EVENTSTATUSEXTENDEDTYPE);

    /* Set the development error flag */
    LblDevErrorFlag = FIM_TRUE;
  }

  /* Check if No Development errors occurred */
  if(LblDevErrorFlag == FIM_FALSE)
  #endif
  {
     /* Check whether EventId is in the configured range - use binary search */
    LblEventExists = FiM_EventIdSearch(EventId, &LddEventArrayIndex);
 
    /* Requested Event Id is found in FIM configuration */
    if(LblEventExists == FIM_TRUE)
    {

      /* Starting Index of configured FID Inhibition Mask Structure */
      LddEventFidLink = FiM_GaaEventInfo[LddEventArrayIndex].ddFidArrayIndex;

      /* Get Number of FIDs */
      LddNoOfFids = FiM_GaaEventInfo[LddEventArrayIndex].ddNumberOfFids;

      /* Data Protection ON */
      SchM_Enter_FiM_REQUEST_EVENTID_PROTECTION();

      /* Checking Inhibition Mask of all the FIDs Configured for that EventId */
      for(LddFidCount = FIM_ZERO; LddFidCount < LddNoOfFids; LddFidCount++)
      {
        /* Fid Inhibition Mask */
        LucInhMask =
        FiM_GaaFunctionIdMask[LddEventFidLink].ucInhibitionMask;

        LddFidArrayIndex = FiM_GaaFunctionIdMask[LddEventFidLink].ddFidIndex;

        /* Check if there is a change in the required mask bits */
        if((EventStatusOld & FiM_GaaMaskValues[LucInhMask]) !=
          (EventStatusNew & FiM_GaaMaskValues[LucInhMask]))
        {
          /* Check if the changed status match with configured mask */
          if((EventStatusNew & FiM_GaaMaskValues[LucInhMask]) ==
            FiM_GaaExpMaskedResult[LucInhMask])
          {
            /* Increment Counter */
            FiM_GaaFidInhibitCounter[LddFidArrayIndex]++;

            /* Set Fid Status */
            FiM_GaaFidPermissionState[LddFidArrayIndex] = FIM_FALSE;
          }
          else
          {
            /* Check Fid counter is non ZERO */
            if(FiM_GaaFidInhibitCounter[LddFidArrayIndex] > FIM_ZERO)
            {
              FiM_GaaFidInhibitCounter[LddFidArrayIndex]--;

              /* If counter reaches ZERO, change FID status */
              if (FiM_GaaFidInhibitCounter[LddFidArrayIndex] == FIM_ZERO)
              {
                FiM_GaaFidPermissionState[LddFidArrayIndex] = FIM_TRUE;
              }
            }
          } /* End of else */
        } /* if( (EventStatusOld & FiM_GaaMaskValues[LucInhMask]) ... */

        /* Move to the next Fid linked to this event */
        LddEventFidLink++;
      } /* for(LddFidCount = FIM_ZERO; ... */

      /* Data Protection OFF */
      SchM_Exit_FiM_REQUEST_EVENTID_PROTECTION();
    } /* if(LblEventExists == FIM_TRUE) */
    /* TODO 
     * [SWS_Fim_00057]  If  development  error detection for the module  FiM  is enabled: 
     * the function FiM_DemTriggerOnEventStatus shall perform a plausibility check on the  EventId.  
     * If  the  requested  EventId  is  not  existing  in  the  Dem  configuration,  the 
     * function  shall  raise  the  development  error  FIM_E_EVENTID_OUT_OF_RANGE.
    else
    {      
      #if (FIM_DEV_ERROR_DETECT == STD_ON)
       (void)Det_ReportError(FIM_MODULE_ID, FIM_INSTANCE_ID,
        FIM_DEMTRIGGERONEVENTSTATUS_SID, FIM_E_INVALID_EVENTID);
      #endif
    }
    */
  } /* if(LblDevErrorFlag == FIM_FALSE) */
}
#endif /* (FIM_EVENT_UPDATE_TRIGGERED_BY_DEM == STD_ON) */

/*******************************************************************************
** Function Name        : FiM_MainFunction                                    **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : This service shall initialize the permission states **
**                        of the FIDs based on the event data of the Dem when **
**                        pre-compile option FIM_EVENT_UPDATE_TRIGGERED_BY_DEM**
**                        is STD_OFF                                          **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
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
** Remarks              : Global Variable(s)  :                               **
**                        FiM_GblInitStatus                                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError, FiM_CalcAllFidsPermissions         **
*******************************************************************************/
FUNC(void, FIM_CODE)FiM_MainFunction(void)
{
  #if(FIM_EVENT_UPDATE_TRIGGERED_BY_DEM == STD_OFF)
  #if(FIM_DEV_ERROR_DETECT == STD_ON)
  if(FiM_GblInitStatus != FIM_INITIALIZED)
  {
    /* Report to DET indicating FiM uninitialized */
    (void)Det_ReportError(FIM_MODULE_ID, FIM_INSTANCE_ID, FIM_MAINFUNCTION_SID,
    FIM_E_UNINIT);
  }
  else
  #endif
  {
    /*
     * Calculate all the configured Fid inhibition status.
     * Return value is not used
     */
    (void)FiM_CalcAllFidsPermissions();
  }
  #endif /* #if(FIM_EVENT_UPDATE_TRIGGERED_BY_DEM == STD_OFF) */
}


/*******************************************************************************
** Function Name        : FiM_DemInit                                         **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This service shall re-initialize the permission     **
**                        states of the FIDs based on the event data of the   **
**                        Dem.                                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
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
** Remarks              : Global Variable(s)  :                               **
**                        FiM_GblInitStatus                                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError, FiM_CalcAllFidsPermissions         **
*******************************************************************************/
FUNC(void, FIM_CODE)FiM_DemInit(void)
{

  /*
   * Calculate all the configured Fid inhibition status.
   * Return value is not used
   */
  #if (FIM_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LddReturn;
  
  LddReturn = FiM_CalcAllFidsPermissions();
  if(LddReturn == E_OK)
  {
    FiM_GblInitStatus = FIM_INITIALIZED;
  }
  else
  {
    /* Report to DET that FiM is not successfully initialized */
    (void)Det_ReportError(FIM_MODULE_ID, FIM_INSTANCE_ID,
      FIM_INIT_SID, FIM_E_INIT_NOT_SUCCESS);
  }
  #else
  (void)FiM_CalcAllFidsPermissions();
  FiM_GblInitStatus = FIM_INITIALIZED;
  #endif     
}

/*******************************************************************************
** Function Name        : FiM_GetFunctionPermission                           **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This service is used for reporting the permission   **
**                        state of FID to the SWC.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : FiM_FunctionIdType FID                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : boolean *Permission                                 **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        FiM_GblInitStatus, FiM_GaaFidPermissionState        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        FiM_FidBinarySearch,                                **
**                        SchM_Enter_FiM_REQUEST_FID_PROTECTION,              **
**                        SchM_Exit_FiM_REQUEST_FID_PROTECTION                **
*******************************************************************************/
FUNC(Std_ReturnType, FIM_CODE) FiM_GetFunctionPermission(
  FiM_FunctionIdType FID, P2VAR(boolean, AUTOMATIC, FIM_APPL_DATA)Permission)
{
  FiM_FidsSizeType LddFidArrayIndex;

  Std_ReturnType LddReturn = E_NOT_OK;

  /* [SWS_Fim_00104] 
   * FiM_GetFunctionPermission  shall  not  be  used  before  full 
   * initialization of FIM (Fim_DemInit).  */

  /*check for the FIM_DEV_ERROR_DETECT == STD_ON */
  
  /* Check whether the module is initialized or not */
  if (FiM_GblInitStatus != FIM_INITIALIZED)
  {
    #if(FIM_DEV_ERROR_DETECT == STD_ON)  
    /* Report to DET indicating wrong permission request */
    (void)Det_ReportError(FIM_MODULE_ID, FIM_INSTANCE_ID,
      FIM_GETFUNCTIONPERMISSION_SID, FIM_E_WRONG_PERMISSION_REQ);
    #endif
  }
  #if(FIM_DEV_ERROR_DETECT == STD_ON)  
  /* Check if Permission pointer is equal to Null */
  else if(Permission == NULL_PTR)
  {
    /* Report to DET indicating Invalid Pointer */
    (void)Det_ReportError(FIM_MODULE_ID, FIM_INSTANCE_ID,
      FIM_GETFUNCTIONPERMISSION_SID, FIM_E_INVALID_POINTER);
  }
  #endif  
  else
  {
    *Permission = FIM_FALSE;  

    /* Check if FID is within the configured range */
    if (FIM_TRUE == FiM_FidSearch(FID, &LddFidArrayIndex))
    {
      /* Data Protection ON */
      SchM_Enter_FiM_REQUEST_FID_PROTECTION();

      /* Get Permission Status */
      *Permission = FiM_GaaFidPermissionState[LddFidArrayIndex];
      /*
        MISRA Rule : 1.2
        Message       : Dereferencing pointer value that is apparently NULL.
        Reason        : Permission is checked and verified when DET
                        is switched OFF.
        Verification  : However, part of the code is verified manually
                        and it is not having any impact.
      */
      /* Data Protection OFF */
      SchM_Exit_FiM_REQUEST_FID_PROTECTION();

      LddReturn = E_OK;
    }
  }

  return LddReturn;
}

#define FIM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
