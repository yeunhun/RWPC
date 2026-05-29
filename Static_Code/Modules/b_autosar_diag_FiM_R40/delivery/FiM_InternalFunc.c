/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: FiM_InternalFunc.c                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Function Inhibition Manager Module                    **
**                                                                            **
**  PURPOSE   : Provision of EventId, FID Binary Search and calculation of    **
**              FID Permission Functionality                                  **
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
** 1.0.5     24-Feb-2018   EK Kim        Changes made As per Redmine #11732   **
**                                                                            **
** 1.0.4     14-Feb-2013   Udaykumar B   Msn in SchM Data Protection API's    **
**                                       is updated to fix integration issue  **
**                                                                            **
** 1.0.3     26-Nov-2012   Udaykumar B   FiM_EventIdLinearSearch,             **
**                                       FiM_FidLinearSearch API's are added  **
**                                       to implement linear search           **
**                                       functionality and types of LddHigh,  **
**                                       LddLow, LddMiddle are corrected in   **
**                                       FiM_FidBinarySearch API              **
**                                                                            **
** 1.0.2     21-Nov-2012   Udaykumar B   Revision History is updated          **
**                                                                            **
** 1.0.1     17-Nov-2012   Udaykumar B   file inclusion is updated to include **
**                                       only Dem.h file                      **
**                                                                            **
** 1.0.0     01-Nov-2012   Autron        Initial version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "FiM.h"                  /* FiM Header File */
#include "SchM_FiM.h"             /* SchM Header File */
#include "FiM_InternalFunc.h"     /* Internal Func header file */
#include "Dem.h"                  /* Dem Header File */

/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/*******************************************************************************
**                           Global Data                                      **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
static FUNC(void, FIM_CODE)FiM_CalcFidPermission(
FiM_EventFidLinkType LddFirstEventFidLink,
Dem_EventStatusExtendedType LddEventStatusExtended,
FiM_EventsSizeType LddEvent
);

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define FIM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : FiM_CalcAllFidsPermissions                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Calculation of FID permission for all the configured**
**                        FIDs                                                **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non - Reentrant                                     **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        FiM_GaaFidInhibitCounter, FiM_GaaEventInfo,         **
**                        FiM_GaaFidPermissionState                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Dem_GetEventStatus, FiM_CalcFidPermission           **
*******************************************************************************/
FUNC(Std_ReturnType, FIM_CODE) FiM_CalcAllFidsPermissions(void)
{
  Dem_EventIdType LddEventId;
  FiM_EventFidLinkType LddFirstEventFidLink;
  FiM_EventsSizeType LddEvent;
  FiM_FidsSizeType LddFid;
  Dem_EventStatusExtendedType LddEventStatusExtended = (Dem_EventStatusExtendedType)0x00;
  Std_ReturnType LddDemReturn;
  Std_ReturnType LddReturn;

  /* Deafult return */
  LddReturn = E_OK;

  /* Reset FID counters for all the configured Fids */
  for(LddFid = FIM_ZERO; LddFid < Fim_Total_Num_Of_Fids; LddFid++)
  {
    FiM_GaaFidInhibitCounter[LddFid] = FIM_ZERO;
  }

  /*
   * Loop for all configured Events, to update the inhibition counters for all
   * FIDs
   */
  for(LddEvent = FIM_ZERO; LddEvent < Fim_Total_Num_Of_Dem_Events; LddEvent++)
  {
    /* Get the EventId */
    LddEventId = FiM_GaaEventInfo[LddEvent].ddEventId;

    /* Index of configured FID Inhibition Mask Structure */
    LddFirstEventFidLink = FiM_GaaEventInfo[LddEvent].ddFidArrayIndex;

    /* Get the Event Status of the configured EventId */
    LddDemReturn = Dem_GetEventStatus(LddEventId, &LddEventStatusExtended);

    if(LddDemReturn == E_OK)
    {
      /* Update the counters for all the FIDs linked to this Event */
      FiM_CalcFidPermission(LddFirstEventFidLink, LddEventStatusExtended,
        LddEvent);
    }
    /* This loop is used only during initialization and DET is enabled */
    #if(FIM_DEV_ERROR_DETECT == STD_ON)
    else
    {
      LddReturn = E_NOT_OK;
    }
    #endif
  } /* for(LddEvent = FIM_ZERO; ... */

  /* Enter Data Protection */
  SchM_Enter_FiM_REQUEST_FID_PROTECTION();

  /* For all configured FIDs */
  for(LddFid = FIM_ZERO; LddFid < Fim_Total_Num_Of_Fids; LddFid++)
  {
    if(FiM_GaaFidInhibitCounter[LddFid] > FIM_ZERO)
    {
      /* Inhibit the permission */
      FiM_GaaFidPermissionState[LddFid] = FIM_FALSE;
    }
    else
    {
      /* Clear permission state */
      FiM_GaaFidPermissionState[LddFid] = FIM_TRUE;
    }
  }
  /* Exit Data Protection*/
  SchM_Exit_FiM_REQUEST_FID_PROTECTION();
  return(LddReturn);
}


/*******************************************************************************
** Function Name        : FiM_CalcFidPermission                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Calculation of FID permission for the FIDs related  **
**                        to one Event.                                       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non - Reentrant                                     **
**                                                                            **
** Input Parameters     : FiM_EventFidLinkType LddFirstEventFidLink,          **
**                        Dem_EventStatusExtendedType LddEventStatusExtended, **
**                        FiM_EventsSizeType LddEvent                         **
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
**                        FiM_GaaFidInhibitCounter, FiM_GaaFunctionIdMask,    **
**                        FiM_GaaEventInfo, FiM_GaaMaskValues,                **
**                        FiM_GaaExpMaskedResult, FiM_GaaFidPermissionState   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        None                                                **
*******************************************************************************/
static FUNC(void, FIM_CODE) FiM_CalcFidPermission (FiM_EventFidLinkType
  LddFirstEventFidLink, Dem_EventStatusExtendedType LddEventStatusExtended,
  FiM_EventsSizeType LddEvent)
{
  FiM_FidsSizeType LddFidArrayIndex;
  FiM_EventFidLinkType LddEventFidLink;
  FiM_FidsSizeType LddFid;
  uint8 LucFidMask;

  LddEventFidLink = LddFirstEventFidLink;

  /* Checking Inhibition Mask of all the FIDs Configured for that EventId */
  for(LddFid = FIM_ZERO; LddFid < FiM_GaaEventInfo[LddEvent].ddNumberOfFids;
    LddFid++)
  {
    /* Fid Inhibition Mask */
    LucFidMask = FiM_GaaFunctionIdMask[LddEventFidLink].ucInhibitionMask;

    LddFidArrayIndex = FiM_GaaFunctionIdMask[LddEventFidLink].ddFidIndex;

    /* Check if the changed status match with configured mask */
    if((LddEventStatusExtended & FiM_GaaMaskValues[LucFidMask]) ==
      FiM_GaaExpMaskedResult[LucFidMask])
    {
      /* Increment Counter */
      FiM_GaaFidInhibitCounter[LddFidArrayIndex]++;
      FiM_GaaFidPermissionState[LddFidArrayIndex] = FIM_FALSE;
    }
    /* Move to next Fid of the Event */
    LddEventFidLink++;
  } /* for(LddFid = FIM_ZERO; ... */
}

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define FIM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
