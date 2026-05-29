/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Com_Filter.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision filter functions and their functionality.           **
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
** 2.7.4     19-Aug-2021   SM Kwon     Internal Redmine #30091                **
** 2.7.1     07-Jan-2021   SM Kwon     Internal Redmine #27557                **
** 2.6.0     10-Sep-2020   SM Kwon     Internal Redmine #25250                **
** 2.4.0     25-Jan-2019   SM Kwon     Internal Redmine #14789                **
** 2.2.3     08-Dec-2017   Chan Kim    Internal Redmine #10849, #10851        **
** 2.2.0     16-Apr-2017   Chan Kim    Internal Redmine #7525                 **
** 2.1.7     30-Nov-2016   Chan Kim    Internal Redmine #6807                 **
** 2.1.4     26-Jul-2016   Chan Kim    Internal Redmine #5687                 **
** 2.1.1     20-Jun-2016   Chan Kim    Internal Redmine #5265                 **
** 2.1.0     25-May-2016   Chan Kim    Internal Redmine #4998                 **
** 2.0.3     24-Nov-2015   Chan Kim    Internal Redmine #3544, #3535          **
** 1.0.11    03-Mar-2014   Chan Kim    Internal Redmine #642                  **
** 1.0.0     29-Apr-2013   Autron      Initial Version                        **
*******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Com.h"          /* Com header file */
#include "Com_Filter.h"   /* Com Filter header file */
#include "SchM_Com.h"     /* Scheduler Manager Com header file */
#if (COM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"          /* Det header file */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define COM_FILTER_C_AR_RELEASE_MAJOR_VERSION       4
#define COM_FILTER_C_AR_RELEASE_MINOR_VERSION       0
#define COM_FILTER_C_AR_RELEASE_REVISION_VERSION    3

/* Software Version Information */
#define COM_FILTER_C_SW_MAJOR_VERSION  2
#define COM_FILTER_C_SW_MINOR_VERSION  7

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (COM_AR_RELEASE_MAJOR_VERSION != COM_FILTER_C_AR_RELEASE_MAJOR_VERSION)
  #error "Com_Filter.c : Mismatch in Com Specification Major Version"
#endif

#if (COM_AR_RELEASE_MINOR_VERSION != COM_FILTER_C_AR_RELEASE_MINOR_VERSION)
  #error "Com_Filter.c : Mismatch in Com Specification Minor Version"
#endif

#if(COM_AR_RELEASE_REVISION_VERSION != COM_FILTER_C_AR_RELEASE_REVISION_VERSION)
  #error "Com_Filter.c : Mismatch in Com Specification Revision Version"
#endif

#if (COM_SW_MAJOR_VERSION != COM_FILTER_C_SW_MAJOR_VERSION)
  #error "Com_Filter.c : Mismatch in Com Software Major Version"
#endif

#if (COM_SW_MINOR_VERSION != COM_FILTER_C_SW_MINOR_VERSION)
  #error "Com_Filter.c : Mismatch in Com Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if(COM_FILTER_USED == STD_ON)
/* polyspace:begin <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
/* polyspace-begin MISRA-C3:D4.14 [Not a defect: Justify with annotations] "Function call depends on the configured Filter values" */
/* polyspace-begin MISRA-C3:18.1 [Not a defect: Justify with annotations] "Genderated array index in range" */
/* polyspace-begin MISRA-C3:11.5 [Not a defect: Justify with annotations] "Conversion perform pointer to object" */
/* polyspace-begin RTE:OVFL [Not a defect: Justify with annotations] "Overflow can not occur" */
/* polyspace-begin RTE:NIV [Not a defect: Justify with annotations] "Initialized variable" */
/* polyspace-begin RTE:IDP [Not a defect: Justify with annotations] "Configured memory access index" */
/*******************************************************************************
** Function Name        : Com_FNever                                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function never allows to pass any signal and   **
**                        always return false.                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_FNever
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  COM_UNUSED_PTR(LpSigDataPtr);
  COM_UNUSED_PTR(LpFilter);
  COM_UNUSED(ActivateCode);
  /* Return filter result */
  return (COM_FALSE);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_FMaskedNewEqualsX_8                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 8 bit   **
**                        whose masked value is equal to specific value.      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_FMaskedNewEqualsX_8
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST) LpMaskedEqualsX;
  boolean LblFilterResult;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;

  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {

    /* Get the pointer to Com_FilterMaskedNew filter structure */
    LpMaskedEqualsX =
         (P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)) LpFilter;
    /* Check whether "new value & mask == pX" */
    if((uint8)(LpMaskedEqualsX->slX)
      == ((uint8)(LpMaskedEqualsX->ulFilterMask) &
                   ((*(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr))))
    {
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }

  }
  /* Return filter result */
  return (LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FMaskedNewEqualsX_16                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 16 bit  **
**                        whose masked value is equal to specific value.      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_FMaskedNewEqualsX_16
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST) LpMaskedEqualsX;
  boolean LblFilterResult;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {

    /* Get the pointer to Com_FilterMaskedNew filter structure */
    LpMaskedEqualsX =
         (P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)) LpFilter;
    /* Check whether "new value & mask == pX" */
    if((uint16)(LpMaskedEqualsX->slX)
      == ((uint16)(LpMaskedEqualsX->ulFilterMask) &
                  ((*(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSigDataPtr))))
    {
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* Return filter result */
  return (LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FMaskedNewEqualsX_32                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 32 bit  **
**                        whose masked value is equal to specific value.      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FMaskedNewEqualsX_32
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST) LpMaskedEqualsX;
  boolean LblFilterResult;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* Get the pointer to Com_FilterMaskedNew filter structure */
    LpMaskedEqualsX =
         (P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)) LpFilter;
    /* Check whether "new_value & mask == pX" */
    if((uint32)(LpMaskedEqualsX->slX)
      == ((uint32)(LpMaskedEqualsX->ulFilterMask)&
                  ((*(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSigDataPtr))))
    {
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* Return filter result */
  return (LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FMaskedNewDiffersX_8                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 8 bit   **
**                        whose masked value is not equal to specific value.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FMaskedNewDiffersX_8
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST) LpMaskedNewDiffersX;
  boolean LblFilterResult;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* Get the pointer to Com_FilterMaskedNew filter structure */
    LpMaskedNewDiffersX =
         (P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)) LpFilter;
    /* Check whether "new_value & mask != pX" */
    if((((uint8)(LpMaskedNewDiffersX->ulFilterMask)) &
               ((*(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr)))
                                         != (uint8)(LpMaskedNewDiffersX->slX))
    {
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* Return filter result */
  return (LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FMaskedNewDiffersX_16                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 16 bit  **
**                        whose masked value is not equal to specific value.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FMaskedNewDiffersX_16
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST) LpMaskedNewDiffersX;
  boolean LblFilterResult;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {

    /* Get the pointer to Com_FilterMaskedNew filter structure */
    LpMaskedNewDiffersX =
         (P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)) LpFilter;
    /* Check whether "new_value & mask != pX" */
    if((((uint16)(LpMaskedNewDiffersX->ulFilterMask)) &
            ((*(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSigDataPtr)))
                                      != (uint16)(LpMaskedNewDiffersX->slX))
    {
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }

  }
  /* Return filter result */
  return (LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FMaskedNewDiffersX_32                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 32 bit  **
**                        whose masked value is not equal to specific value.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FMaskedNewDiffersX_32
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST) LpMaskedNewDiffersX;
  boolean LblFilterResult;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* Get the pointer to Com_FilterMaskedNew filter structure */
    LpMaskedNewDiffersX =
         (P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)) LpFilter;
    /* Check whether "new_value & mask != pX" */
    if((((uint32)(LpMaskedNewDiffersX->ulFilterMask)) &
            ((*(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSigDataPtr)))
                                      != (uint32)(LpMaskedNewDiffersX->slX))
    {
      /* Set the filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* Return filter result */
  return (LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FMaskedNewDiffersMaskedOld_8                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 8 bit   **
**                        when the masked value has changed.                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FMaskedNewDiffersMaskedOld_8
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)
                                                    LpMaskedNewDiffersMaskedOld;
  boolean LblFilterResult;
  /* Get the pointer to Com_FilterMaskedNew filter structure */
  LpMaskedNewDiffersMaskedOld =
       (P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)) LpFilter;

  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  if(ActivateCode == COM_ZERO)
  {
	  /* Check whether "new_value & mask != old_value & mask" */
	  if((*(LpMaskedNewDiffersMaskedOld->pFilterActivated) == COM_INVALID_PARAM) ||
	  (((uint8)(LpMaskedNewDiffersMaskedOld->ulFilterMask) &
               (*(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr))
                    != ((uint8)(LpMaskedNewDiffersMaskedOld->ulFilterMask) &
                             (*(P2CONST(uint8, AUTOMATIC, COM_CONST))
                             (LpMaskedNewDiffersMaskedOld->pSignalBuffer)))))
	  {
	    /* Copy the signal data to signal buffer */
	    (*(P2VAR(uint8, AUTOMATIC, COM_VAR))
                             (LpMaskedNewDiffersMaskedOld->pSignalBuffer)) =
               (*(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr);
	    /* Set filter result to true */
	    LblFilterResult = COM_TRUE;
	    /* Set activate status as normal */
	    *(LpMaskedNewDiffersMaskedOld->pFilterActivated) = COM_ZERO;
	  }
  }
  else
  {
  	*(LpMaskedNewDiffersMaskedOld->pFilterActivated) = COM_INVALID_PARAM;
  }
  /* Return filter result */
  return (LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FMaskedNewDiffersMaskedOld_16                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 16 bit  **
**                        when the masked value has changed.                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FMaskedNewDiffersMaskedOld_16
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)
                                                    LpMaskedNewDiffersMaskedOld;
  boolean LblFilterResult;
  /* Get the pointer to Com_FilterMaskedNew filter structure */
  LpMaskedNewDiffersMaskedOld =
  (P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  if(ActivateCode == COM_ZERO)
  {
	  /* Check whether "new_value & mask != old_value & mask" */
	  if((*(LpMaskedNewDiffersMaskedOld->pFilterActivated) == COM_INVALID_PARAM)
      || (((uint16)(LpMaskedNewDiffersMaskedOld->ulFilterMask) &
      (*(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSigDataPtr))
           != ((uint16)(LpMaskedNewDiffersMaskedOld->ulFilterMask) &
                    (*(P2CONST(uint16, AUTOMATIC, COM_CONST))
                     (LpMaskedNewDiffersMaskedOld->pSignalBuffer)))))
	  {
	    /* Copy the signal data to signal buffer */
	    (*(P2VAR(uint16, AUTOMATIC, COM_VAR))
                           (LpMaskedNewDiffersMaskedOld->pSignalBuffer)) =
            (*(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSigDataPtr);
	    /* Set filter result to true */
	    LblFilterResult = COM_TRUE;
	  }
  }
  else
  {
  	*(LpMaskedNewDiffersMaskedOld->pFilterActivated) = COM_INVALID_PARAM;
  }
  /* Return filter result */
  return (LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FMaskedNewDiffersMaskedOld_32                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 32 bit  **
**                        when the masked value has changed.                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FMaskedNewDiffersMaskedOld_32
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)
                                                    LpMaskedNewDiffersMaskedOld;
  boolean LblFilterResult;
  /* Get the pointer to Com_FilterMaskedNew filter structure */
  LpMaskedNewDiffersMaskedOld =
       (P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  if(ActivateCode == COM_ZERO)
  {
	  /* Check whether "new_value & mask != old_value & mask" */
	  if((*(LpMaskedNewDiffersMaskedOld->pFilterActivated) == COM_INVALID_PARAM)
    || (((uint32)(LpMaskedNewDiffersMaskedOld->ulFilterMask) &
              (*(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSigDataPtr))
                   != ((uint32)(LpMaskedNewDiffersMaskedOld->ulFilterMask) &
                            (*(P2CONST(uint32, AUTOMATIC, COM_CONST))
                             (LpMaskedNewDiffersMaskedOld->pSignalBuffer)))))
	  {
	    /* Copy the signal data to signal buffer */
	    (*(P2VAR(uint32, AUTOMATIC, COM_VAR))
                             (LpMaskedNewDiffersMaskedOld->pSignalBuffer)) =
              (*(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSigDataPtr);
	    /* Set filter result to true */
	    LblFilterResult = COM_TRUE;
	  }
  }
  else
  {
  	*(LpMaskedNewDiffersMaskedOld->pFilterActivated) = COM_INVALID_PARAM;
  }
  /* Return filter result*/
  return (LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsWithin_u8                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 8 bit   **
**                        and type unsigned whose value lies within defined   **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsWithin_u8
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)
                                                                  LpNewIsWithin;
  uint8 LucData;
  boolean LblFilterResult;
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsWithin =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* Get the signal data to local variable */
    LucData = *(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether min <= new_value <= max */
    if(((((uint8)(LpNewIsWithin->slMin)) <=  LucData) &&
                        (LucData <= ((uint8)(LpNewIsWithin->slMax)))))
    {
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* Return filter result */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsWithin_s8                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 8 bit   **
**                        and type signed whose value lies within defined     **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsWithin_s8
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsWithin;
  sint8 LscData;
  boolean LblFilterResult;
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsWithin =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* Get the signal data to local variable */
    LscData = *(P2CONST(sint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether min <= new_value <= max */
    if(((((sint8)(LpNewIsWithin->slMin)) <=  LscData) &&
                          (LscData <= (sint8)(LpNewIsWithin->slMax))) )
    {
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* Return filter result */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsWithin_u16                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 16 bit  **
**                        and type unsigned whose value lies within defined   **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsWithin_u16
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsWithin;
  uint16 LusData;
  boolean LblFilterResult;
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsWithin =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* Get the signal data to local variable */
    LusData = *(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether min <= new_value <= max */
    if(((((uint16)(LpNewIsWithin->slMin)) <=  LusData) &&
                         (LusData <= ((uint16)(LpNewIsWithin->slMax)))))
    {
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* return filter result */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsWithin_s16                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 16 bit  **
**                        and type signed whose value lies within defined     **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsWithin_s16
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsWithin;
  sint16 LssData;
  boolean LblFilterResult;
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsWithin =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* Get the signal data to local variable */
    LssData = *(P2CONST(sint16, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether min <= new_value <= max */
    if(((((sint16)(LpNewIsWithin->slMin)) <=  LssData) &&
                         (LssData <= (sint16)(LpNewIsWithin->slMax))))
    {
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* Return filter result */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsWithin_u32                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 32 bit  **
**                        and type unsigned whose value lies within defined   **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsWithin_u32
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsWithin;
  uint32 LulData;
  boolean LblFilterResult;
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsWithin =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* Get the signal data to local variable */
    LulData = *(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether min <= new_value <= max */
    if(((((uint32)(LpNewIsWithin->slMin)) <=  LulData) &&
                         (LulData <= (uint32)(LpNewIsWithin->slMax))))
    {
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* Return filter result */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsWithin_s32                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 32 bit  **
**                        and type signed whose value lies within defined     **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsWithin_s32
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsWithin;
  sint32 LslData;
  boolean LblFilterResult;
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsWithin =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* Get the signal data to local variable */
    LslData = *(P2CONST(sint32, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether min <= new_value <= max */
    if((((LpNewIsWithin->slMin) <=  LslData) &&
                                 (LslData <= (LpNewIsWithin->slMax))))
    {

      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* Return filter result */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsOutside_u8                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 8 bit   **
**                        and type unsigned whose value lies outside defined  **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsOutside_u8
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsOutside;
  uint8 LucData;
  boolean LblFilterResult;
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsOutside =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {

    /* Get the signal data to local variable */
    LucData = *(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether new value < min or new value > max */
    if((((uint8)(LpNewIsOutside->slMin) >  LucData) ||
        (LucData > (uint8)(LpNewIsOutside->slMax))))
    {

      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* Return filter result */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsOutside_s8                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 8 bit   **
**                        and type signed whose value lies outside defined    **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsOutside_s8
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsOutside;
  sint8 LscData;
  boolean LblFilterResult;
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsOutside =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* Get the signal data to local variable */
    LscData = *(P2CONST(sint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether new value < min or new value > max */
    if((((sint8)(LpNewIsOutside->slMin) >  LscData) ||
                          (LscData > (sint8)(LpNewIsOutside->slMax))))
    {

      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* Return filter result */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsOutside_u16                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 16 bit  **
**                        and type unsigned whose value lies outside defined  **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsOutside_u16
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsOutside;
  uint16 LusData;
  boolean LblFilterResult;
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsOutside =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* Get the signal data to local variable */
    LusData = *(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether new value < min or new value > max */
    if((((uint16)(LpNewIsOutside->slMin) >  LusData) ||
                         (LusData > (uint16)(LpNewIsOutside->slMax))))
    {
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* Return filter result */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsOutside_s16                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 16 bit  **
**                        and type signed whose value lies outside defined    **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsOutside_s16
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsOutside;
  sint16 LssData;
  boolean LblFilterResult;
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsOutside =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* Get the signal data to local variable */
    LssData = *(P2CONST(sint16, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether new value < min or new value > max */
    if((((sint16)(LpNewIsOutside->slMin) >  LssData) ||
                         (LssData > (sint16)(LpNewIsOutside->slMax))))
    {

      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
   /* Return filter result */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsOutside_u32                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 32 bit  **
**                        and type unsigned whose value lies outside defined  **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsOutside_u32
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsOutside;
  uint32 LulData;
  boolean LblFilterResult;
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsOutside =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* Get the signal data to local variable */
    LulData = *(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether new value < min or new value > max */
    if((((uint32)(LpNewIsOutside->slMin) >  LulData) ||
                         (LulData > (uint32)(LpNewIsOutside->slMax))))
    {
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* Return filter result */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsOutside_s32                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 32 bit  **
**                        and type signed whose value lies outside defined    **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsOutside_s32
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsOutside;
  sint32 LslData;
  boolean LblFilterResult;
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsOutside =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* Get the signal data to local variable */
    LslData = *(P2CONST(sint32, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether new value < min or new value > max */
    if((((LpNewIsOutside->slMin) >  LslData) ||
                                 (LslData > (LpNewIsOutside->slMax))))
    {
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* Return filter result */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FOneEveryN                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is Com internal function. This function passes **
**                        a signal once every N signal occurrences. Each time **
**                        the signal is received or transmitted, occurrence   **
**                        is incremented by 1 after filtering. Length of      **
**                        occurrence is 8 bit.                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_FOneEveryN
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode)
{
  P2VAR(uint16, AUTOMATIC, COM_VAR) LpCounter;
  P2CONST(Com_FilterOneEveryN, AUTOMATIC, COM_CONST) LpOneEveryN;
  boolean LblFilterResult;
  /* Get the pointer to Com_FilterOneEveryN filter structure*/
  LpOneEveryN =
      (P2CONST(Com_FilterOneEveryN, AUTOMATIC, COM_CONST)) LpFilter;
  /* Get the pointer to counter */
  LpCounter = LpOneEveryN->pCounter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* Pass message once every N */
    if((*LpCounter)  == (LpOneEveryN->usOffset))
    {
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
    /* Increment the counter */
    (*LpCounter)++;
    /* Check whether counter is equal to period */
    if((*LpCounter)  == ((LpOneEveryN->usPeriod)))
    {
      /* Reset the counter to zero */
      *LpCounter = (uint16)COM_ZERO;
    }
  }
  COM_UNUSED_PTR(LpSigDataPtr);
  /* Return filter result */
  return (LblFilterResult);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#endif /*#if(COM_FILTER_USED == STD_ON)*/
/* polyspace-end MISRA-C3:D4.14 [Not a defect: Justify with annotations]  */
/* polyspace-end MISRA-C3:18.1 [Not a defect: Justify with annotations]  */
/* polyspace-end MISRA-C3:11.5 [Not a defect: Justify with annotations]  */
/* polyspace-end RTE:OVFL [Not a defect: Justify with annotations] */
/* polyspace-end RTE:NIV [Not a defect: Justify with annotations]  */
/* polyspace-end RTE:IDP [Not a defect: Justify with annotations]  */
/* polyspace:end <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
