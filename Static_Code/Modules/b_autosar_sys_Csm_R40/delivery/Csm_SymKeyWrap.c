/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Csm_SymKeyWrap.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CSM Symmetric Key Wrapping Interface using  **
**              Symmetric and Asymmetric wrapping keys                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 2.6.3.0   24-Mar-2021   TamTV6       Redmine #18165                        **
** 1.2.2     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.2.1     21-Sep-2017   Sinil        Redmine #10038                        **
** 1.2.0     27-Feb-2017   Sinil        Redmine #7650, #7672                  **
** 1.1.0     11-Jan-2017   Sinil        Redmine #7198                         **
** 1.0.5     09-Aug-2016   Sinil        Redmine #5693, #5694, #5760           **
** 1.0.4     12-Jul-2016   Sinil        Redmine #5514                         **
** 1.0.3     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.2     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.1     02-Dec-2015   Sinil        Memory section changed                **
** 1.0.0     01-Jan-2013   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm.h"                  /* Header file for function prototypes */
#include "Rte_Csm.h"
#if (CSM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                  /* Header file for DET */
#endif

#if ((CSM_SYM_KEY_WRAP_SYM_STATUS == STD_ON) || (CSM_SYM_KEY_WRAP_ASYM_STATUS == STD_ON))
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (CSM_SYM_KEY_WRAP_SYM_STATUS == STD_ON) /* Symmetric Wrapping Key */
/* Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveSymKeyWrapSymService Csm_GddActiveSymKeyWrapSymService;
#endif /* (CSM_SYM_KEY_WRAP_SYM_STATUS == STD_ON) */

#if (CSM_SYM_KEY_WRAP_ASYM_STATUS == STD_ON) /* Asymmetric Wrapping Key */
/* Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveSymKeyWrapAsymService Csm_GddActiveSymKeyWrapAsymService;
#endif /* (CSM_SYM_KEY_WRAP_ASYM_STATUS == STD_ON) */

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
#if (CSM_SYM_KEY_WRAP_SYM_STATUS == STD_ON) /* Symmetric Wrapping Key */
/*******************************************************************************
** Function Name        : Csm_SymKeyWrapSymStart                              **
**                                                                            **
** Service ID           : 0x40                                                **
**                                                                            **
** Description          : This function will initialize the symmetrical key   **
**                        wrapping service of the CSM module. It will be      **
**                        using symmetric keys for wrapping the symmetric key **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, keyPtr, wrappingKeyPtr                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        CSM_E_BUSY: service state is already "active"       **
**                                                                            **
** Preconditions        : CSM should have been initialized                    **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                                        Csm_GddActiveSymKeyWrapSymService,  **
**                                        Csm_GaaSymKeyWrapSymConfigType      **
**                        Function(s) invoked: Cry_<Primitive>Start,          **
**                        Csm_FunctionPush                                    **
*******************************************************************************/
Std_ReturnType Csm_SymKeyWrapSymStart(Csm_ConfigIdType cfgId,
  const Csm_SymKeyType* keyPtr, const Csm_SymKeyType* wrappingKeyPtr)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  /* Checking for CSM initialization */
  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_SYMKEYWRAPSYMSTART_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Checking for Service Validation based on the configuration id  */
    if (cfgId >= CSM_SYM_KEY_WRAP_SYM_CFGID_LIMIT)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMKEYWRAPSYMSTART_SID, CSM_E_PARAM_METHOD_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Verifying the Null pointer */
    if (keyPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMKEYWRAPSYMSTART_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (keyPtr->length == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMKEYWRAPSYMSTART_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (wrappingKeyPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMKEYWRAPSYMSTART_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (wrappingKeyPtr->length == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMKEYWRAPSYMSTART_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveSymKeyWrapSymService.ucServiceState
      & CSM_SYM_KEY_WRAP_SYM_IDLE) != CSM_SYM_KEY_WRAP_SYM_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* updating the state to service start */
    Csm_GddActiveSymKeyWrapSymService.ucServiceState =
      CSM_SYM_KEY_WRAP_SYM_START;

    /* Fetching service configuration as updated during initial configuration */
    Csm_GddActiveSymKeyWrapSymService.pActiveServiceConfig = \
      &Csm_GaaSymKeyWrapSymConfigType[cfgId];

    /*
     * invoking primitive start function
     * Will be using AES primitive for the Symmetrical Wrapping
     * InitVector is NULL and InitVectorLength is 0 as they will not be used
     */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveSymKeyWrapSymService.
      pActiveServiceConfig->PrimitiveStartFct(
      (void*)Csm_GddActiveSymKeyWrapSymService.
      pActiveServiceConfig->PrimitiveConfigPtr, keyPtr,
      wrappingKeyPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveSymKeyWrapSymService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Setting the service state to active upon success */
          Csm_GddActiveSymKeyWrapSymService.ucServiceState =
            CSM_SYM_KEY_WRAP_SYM_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveSymKeyWrapSymService.ucServiceState =
            CSM_SYM_KEY_WRAP_SYM_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveSymKeyWrapSymService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveSymKeyWrapSymService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_SymKeyWrapSymUpdate                             **
**                                                                            **
** Service ID           : 0x41                                                **
**                                                                            **
** Description          : This function retrieve the result of the key        **
**                        wrapping operation from the symmetrical key         **
**                        wrapping service                                    **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId                                               **
**                                                                            **
** InOut parameter      : dataLengthPtr                                       **
**                                                                            **
** Output Parameters    : dataPtr                                             **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        E_NOT_OK: service state is "idle"                   **
**                                                                            **
** Preconditions        : CSM Symmetrical Key Wrap interface should have been **
**                        initialized                                         **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                                        Csm_GddActiveSymKeyWrapSymService   **
**                        Function(s) invoked: Cry_<Primitive>Update          **
*******************************************************************************/
Std_ReturnType Csm_SymKeyWrapSymUpdate(Csm_ConfigIdType cfgId, uint8* dataPtr,
  uint32* dataLengthPtr)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  /* Verifying the Null pointer */
  if (dataPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_SYMKEYWRAPSYMUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    if (dataLengthPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMKEYWRAPSYMUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (*dataLengthPtr == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMKEYWRAPSYMUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveSymKeyWrapSymService.ucServiceState
      & CSM_SYM_KEY_WRAP_SYM_START) == CSM_SYM_KEY_WRAP_SYM_START)
      || ((Csm_GddActiveSymKeyWrapSymService.ucServiceState
      & CSM_SYM_KEY_WRAP_SYM_UPDATE) == CSM_SYM_KEY_WRAP_SYM_UPDATE)
      || ((Csm_GddActiveSymKeyWrapSymService.ucServiceState
      & CSM_SYM_KEY_WRAP_SYM_FINISH) == CSM_SYM_KEY_WRAP_SYM_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveSymKeyWrapSymService.ucServiceState
      & CSM_SYM_KEY_WRAP_SYM_ACTIVE) != CSM_SYM_KEY_WRAP_SYM_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMKEYWRAPSYMUPDATE_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to UPDATE */
    Csm_GddActiveSymKeyWrapSymService.ucServiceState =
      CSM_SYM_KEY_WRAP_SYM_UPDATE;

    /* Calling the primitive update function */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveSymKeyWrapSymService.
      pActiveServiceConfig->PrimitiveUpdateFct(cfgId, dataPtr, dataLengthPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveSymKeyWrapSymService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Setting the service state to active upon success */
          Csm_GddActiveSymKeyWrapSymService.ucServiceState =
            CSM_SYM_KEY_WRAP_SYM_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveSymKeyWrapSymService.ucServiceState =
            CSM_SYM_KEY_WRAP_SYM_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveSymKeyWrapSymService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveSymKeyWrapSymService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_SymKeyWrapSymFinish                             **
**                                                                            **
** Service ID           : 0x42                                                **
**                                                                            **
** Description          : This function will be used to finish the            **
**                        symmetrical key wrapping service.                   **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        E_NOT_OK: service state is "idle"                   **
**                                                                            **
** Preconditions        : CSM Symmetrical Key Wrap interface should have been **
**                        initialized                                         **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                                          Csm_GddActiveSymKeyWrapSymService **
**                        Function(s) invoked: Cry_<Primitive>Finish          **
*******************************************************************************/
Std_ReturnType Csm_SymKeyWrapSymFinish(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  if (((Csm_GddActiveSymKeyWrapSymService.ucServiceState
    & CSM_SYM_KEY_WRAP_SYM_START) == CSM_SYM_KEY_WRAP_SYM_START)
    || ((Csm_GddActiveSymKeyWrapSymService.ucServiceState
    & CSM_SYM_KEY_WRAP_SYM_UPDATE) == CSM_SYM_KEY_WRAP_SYM_UPDATE)
    || ((Csm_GddActiveSymKeyWrapSymService.ucServiceState
    & CSM_SYM_KEY_WRAP_SYM_FINISH) == CSM_SYM_KEY_WRAP_SYM_FINISH))
  {
    LddReturnValue = CSM_E_BUSY;
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveSymKeyWrapSymService.ucServiceState
      & CSM_SYM_KEY_WRAP_SYM_ACTIVE) != CSM_SYM_KEY_WRAP_SYM_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMKEYWRAPSYMFINISH_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to FINISH */
    Csm_GddActiveSymKeyWrapSymService.ucServiceState =
      CSM_SYM_KEY_WRAP_SYM_FINISH;

    /* Calling the primitive finish function */
    /* polyspace-begin MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveSymKeyWrapSymService.pActiveServiceConfig->
      PrimitiveFinishFct(cfgId);
    /* polyspace-end MISRA-C3:18.1 RTE:IDP RTE:COR */

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveSymKeyWrapSymService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveSymKeyWrapSymService.ucServiceState
          = CSM_SYM_KEY_WRAP_SYM_IDLE;
      }
      else
      {
        if (Csm_GddActiveSymKeyWrapSymService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveSymKeyWrapSymService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_SymKeyWrapSymCallbackNotification               **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in the configuration of Symmetrical Key       **
**                        Wrapping with Symmetrical key service with the      **
**                        argument given by "Result".                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : ddResult                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        Csm_GddActiveSymKeyWrapSymService                   **
*******************************************************************************/
void Csm_SymKeyWrapSymCallbackNotification(Std_ReturnType ddResult)
{
  switch (ddResult)
  {
  case CSM_E_BUSY:
    /* Do nothing */
    break;

  case E_OK:
    switch (Csm_GddActiveSymKeyWrapSymService.ucServiceState)
    {
    case CSM_SYM_KEY_WRAP_SYM_START:
    case CSM_SYM_KEY_WRAP_SYM_UPDATE:
      /* State is set to ACTIVE upon success */
      Csm_GddActiveSymKeyWrapSymService.ucServiceState
        = CSM_SYM_KEY_WRAP_SYM_ACTIVE;
      break;

    case CSM_SYM_KEY_WRAP_SYM_FINISH:
      /* Setting the service state to idle irrespective of the result */
      Csm_GddActiveSymKeyWrapSymService.ucServiceState
        = CSM_SYM_KEY_WRAP_SYM_IDLE;
      break;

    default:
      /* Do nothing */
      break;
    }
    break;

  default:
    switch (Csm_GddActiveSymKeyWrapSymService.ucServiceState)
    {
    case CSM_SYM_KEY_WRAP_SYM_START:
    case CSM_SYM_KEY_WRAP_SYM_UPDATE:
    case CSM_SYM_KEY_WRAP_SYM_FINISH:
      break;

    default:
      /* Do nothing */
      break;
    }

    /* state is set to IDLE upon Failure */
    Csm_GddActiveSymKeyWrapSymService.ucServiceState
      = CSM_SYM_KEY_WRAP_SYM_IDLE;
    break;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveSymKeyWrapSymService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveSymKeyWrapSymService.pActiveServiceConfig->CallbackFct(ddResult);
  }
}

/*******************************************************************************
** Function Name        : Csm_SymKeyWrapSymServiceFinishNotification          **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function shall set the state of Symmetrical    **
**                        Key Wrapping with Symmetrical Key service to "idle".**
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
** Remarks              : Global Variable(s):                                 **
**                                   Csm_GddActiveSymKeyWrapSymService        **
**                        Function(s) invoked: None                           **
*******************************************************************************/
void Csm_SymKeyWrapSymServiceFinishNotification(void)
{
  /* Setting the state to IDLE */
  Csm_GddActiveSymKeyWrapSymService.ucServiceState = CSM_SYM_KEY_WRAP_SYM_IDLE;
}

boolean Csm_SymKeyWrapSymServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveSymKeyWrapSymService.pActiveServiceConfig->
    CallbackFct != NULL_PTR)
  {
    LblHasCallback = TRUE;
  }
  else
  {
    LblHasCallback = FALSE;
  }

  return LblHasCallback;
}
#endif /* (CSM_SYM_KEY_WRAP_SYM_STATUS == STD_ON) */

#if (CSM_SYM_KEY_WRAP_ASYM_STATUS == STD_ON)
/*******************************************************************************
** Function Name        : Csm_SymKeyWrapAsymStart                             **
**                                                                            **
** Service ID           : 0x43                                                **
**                                                                            **
** Description          : This function will initialize the  symmetrical key  **
**                        wrapping service of the CSM module. It will be      **
**                        using asymmetric keys for wrapping the symmetric    **
**                        structure                                           **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, keyPtr, wrappingKeyPtr                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        CSM_E_BUSY: service state is already "active"       **
**                                                                            **
** Preconditions        : CSM should have been initialized                    **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                                        Csm_GddActiveSymKeyWrapAsymService, **
**                                        Csm_GaaSymKeyWrapAsymConfigType     **
**                        Function(s) invoked: Cry_<Primitive>Start,          **
**                        Csm_FunctionPush                                    **
*******************************************************************************/
Std_ReturnType Csm_SymKeyWrapAsymStart(Csm_ConfigIdType cfgId,
  const Csm_SymKeyType* keyPtr, const Csm_AsymPublicKeyType* wrappingKeyPtr)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  /* Checking for CSM initialization */
  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_SYMKEYWRAPASYMSTART_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Checking for Service Validation based on the configuration id  */
    if (cfgId >= CSM_SYM_KEY_WRAP_ASYM_CFGID_LIMIT)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMKEYWRAPASYMSTART_SID, CSM_E_PARAM_METHOD_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Verifying the Null pointer */
    if (keyPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMKEYWRAPASYMSTART_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (keyPtr->length == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMKEYWRAPASYMSTART_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (wrappingKeyPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMKEYWRAPASYMSTART_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (wrappingKeyPtr->length == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMKEYWRAPASYMSTART_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveSymKeyWrapAsymService.ucServiceState
      & CSM_SYM_KEY_WRAP_ASYM_IDLE) != CSM_SYM_KEY_WRAP_ASYM_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* updating the state to service start */
    Csm_GddActiveSymKeyWrapAsymService.ucServiceState =
      CSM_SYM_KEY_WRAP_ASYM_START;

    /* Fetching service configuration as updated during initial configuration */
    Csm_GddActiveSymKeyWrapAsymService.pActiveServiceConfig = \
      &Csm_GaaSymKeyWrapAsymConfigType[cfgId];

    /*
     * invoking primitive start function
     * Will be using RSA primitive for the Asymmetrical Wrapping
     */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveSymKeyWrapAsymService.
      pActiveServiceConfig->PrimitiveStartFct(
      (void*)Csm_GddActiveSymKeyWrapAsymService.
      pActiveServiceConfig->PrimitiveConfigPtr, keyPtr,
      wrappingKeyPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveSymKeyWrapAsymService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Setting the service state to active upon success */
          Csm_GddActiveSymKeyWrapAsymService.ucServiceState =
            CSM_SYM_KEY_WRAP_ASYM_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveSymKeyWrapAsymService.ucServiceState =
            CSM_SYM_KEY_WRAP_ASYM_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveSymKeyWrapAsymService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveSymKeyWrapAsymService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_SymKeyWrapAsymUpdate                            **
**                                                                            **
** Service ID           : 0x44                                                **
**                                                                            **
** Description          : This function retrieve the result of the key        **
**                        wrapping operation from the symmetrical key         **
**                        wrapping service                                    **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId                                               **
**                                                                            **
** InOut parameter      : dataLengthPtr                                       **
**                                                                            **
** Output Parameters    : dataPtr                                             **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        E_NOT_OK: service state is "idle"                   **
**                                                                            **
** Preconditions        : CSM Symmetrical Key Wrap interface should have been **
**                        initialized                                         **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                                        Csm_GddActiveSymKeyWrapAsymService  **
**                        Function(s) invoked: Cry_<Primitive>Update          **
*******************************************************************************/
Std_ReturnType Csm_SymKeyWrapAsymUpdate(Csm_ConfigIdType cfgId, uint8* dataPtr,
  uint32* dataLengthPtr)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  /* Verifying the Null pointer */
  if (dataPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_SYMKEYWRAPASYMUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    if (dataLengthPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMKEYWRAPASYMUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (*dataLengthPtr == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMKEYWRAPASYMUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveSymKeyWrapAsymService.ucServiceState
      & CSM_SYM_KEY_WRAP_ASYM_START) == CSM_SYM_KEY_WRAP_ASYM_START)
      || ((Csm_GddActiveSymKeyWrapAsymService.ucServiceState
      & CSM_SYM_KEY_WRAP_ASYM_UPDATE) == CSM_SYM_KEY_WRAP_ASYM_UPDATE)
      || ((Csm_GddActiveSymKeyWrapAsymService.ucServiceState
      & CSM_SYM_KEY_WRAP_ASYM_FINISH) == CSM_SYM_KEY_WRAP_ASYM_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveSymKeyWrapAsymService.ucServiceState
      & CSM_SYM_KEY_WRAP_ASYM_ACTIVE) != CSM_SYM_KEY_WRAP_ASYM_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMKEYWRAPASYMUPDATE_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to UPDATE */
    Csm_GddActiveSymKeyWrapAsymService.ucServiceState =
      CSM_SYM_KEY_WRAP_ASYM_UPDATE;

    /*
     * Calling the primitive update function
     * Will be using RSA primitive for the Asymmetrical Wrapping
     */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveSymKeyWrapAsymService.
      pActiveServiceConfig->PrimitiveUpdateFct(cfgId, dataPtr, dataLengthPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveSymKeyWrapAsymService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Setting the service state to active upon success */
          Csm_GddActiveSymKeyWrapAsymService.ucServiceState =
            CSM_SYM_KEY_WRAP_ASYM_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveSymKeyWrapAsymService.ucServiceState =
            CSM_SYM_KEY_WRAP_ASYM_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveSymKeyWrapAsymService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveSymKeyWrapAsymService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_SymKeyWrapAsymFinish                            **
**                                                                            **
** Service ID           : 0x45                                                **
**                                                                            **
** Description          : This function will be used to finish the            **
**                        symmetrical key wrapping service.                   **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        E_NOT_OK: service state is "idle"                   **
**                                                                            **
** Preconditions        : CSM Symmetrical Key Wrap interface should have been **
**                        initialized                                         **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                                         Csm_GddActiveSymKeyWrapAsymService **
**                        Function(s) invoked: Cry_<Primitive>Finish          **
*******************************************************************************/
Std_ReturnType Csm_SymKeyWrapAsymFinish(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  if (((Csm_GddActiveSymKeyWrapAsymService.ucServiceState
    & CSM_SYM_KEY_WRAP_ASYM_START) == CSM_SYM_KEY_WRAP_ASYM_START)
    || ((Csm_GddActiveSymKeyWrapAsymService.ucServiceState
    & CSM_SYM_KEY_WRAP_ASYM_UPDATE) == CSM_SYM_KEY_WRAP_ASYM_UPDATE)
    || ((Csm_GddActiveSymKeyWrapAsymService.ucServiceState
    & CSM_SYM_KEY_WRAP_ASYM_FINISH) == CSM_SYM_KEY_WRAP_ASYM_FINISH))
  {
    LddReturnValue = CSM_E_BUSY;
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveSymKeyWrapAsymService.ucServiceState
      & CSM_SYM_KEY_WRAP_ASYM_ACTIVE) != CSM_SYM_KEY_WRAP_ASYM_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMKEYWRAPASYMFINISH_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to FINISH */
    Csm_GddActiveSymKeyWrapAsymService.ucServiceState =
      CSM_SYM_KEY_WRAP_ASYM_FINISH;

    /*
     * Calling the primitive finish function
     * Will be using RSA primitive for the Asymmetrical Wrapping
     */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveSymKeyWrapAsymService.
      pActiveServiceConfig->PrimitiveFinishFct(cfgId);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveSymKeyWrapAsymService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveSymKeyWrapAsymService.ucServiceState
          = CSM_SYM_KEY_WRAP_ASYM_IDLE;
      }
      else
      {
        if (Csm_GddActiveSymKeyWrapAsymService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveSymKeyWrapAsymService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_SymKeyWrapAsymCallbackNotification              **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in the configuration of Symmetrical Key       **
**                        Wrapping with Asymmetrical Key service with the     **
**                        Hash  argument given by "Result".                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : ddResult                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        Csm_GddActiveSymKeyWrapAsymService                  **
*******************************************************************************/
void Csm_SymKeyWrapAsymCallbackNotification(Std_ReturnType ddResult)
{
  switch (ddResult)
  {
  case CSM_E_BUSY:
    /* Do nothing */
    break;

  case E_OK:
    switch (Csm_GddActiveSymKeyWrapAsymService.ucServiceState)
    {
    case CSM_SYM_KEY_WRAP_ASYM_START:
    case CSM_SYM_KEY_WRAP_ASYM_UPDATE:
      /* State is set to ACTIVE upon success */
      Csm_GddActiveSymKeyWrapAsymService.ucServiceState
        = CSM_SYM_KEY_WRAP_ASYM_ACTIVE;
      break;

    case CSM_SYM_KEY_WRAP_ASYM_FINISH:
      /* Setting the service state to idle irrespective of the result */
      Csm_GddActiveSymKeyWrapAsymService.ucServiceState
        = CSM_SYM_KEY_WRAP_ASYM_IDLE;
      break;

    default:
      /* Do nothing */
      break;
    }
    break;

  default:
    switch (Csm_GddActiveSymKeyWrapAsymService.ucServiceState)
    {
    case CSM_SYM_KEY_WRAP_ASYM_START:
    case CSM_SYM_KEY_WRAP_ASYM_UPDATE:
    case CSM_SYM_KEY_WRAP_ASYM_FINISH:
      break;

    default:
      /* Do nothing */
      break;
    }

    /* state is set to IDLE upon Failure */
    Csm_GddActiveSymKeyWrapAsymService.ucServiceState
      = CSM_SYM_KEY_WRAP_ASYM_IDLE;
    break;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveSymKeyWrapAsymService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveSymKeyWrapAsymService.pActiveServiceConfig->CallbackFct(ddResult);
  }
}

/*******************************************************************************
** Function Name        : Csm_SymKeyWrapAsymServiceFinishNotification         **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function shall set state of Symmetrical Key    **
**                        Wrapping with Asymmetrical Key service to "idle".   **
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
** Remarks              : Global Variable(s):                                 **
**                                  Csm_GddActiveSymKeyWrapAsymService        **
**                        Function(s) invoked: None                           **
*******************************************************************************/
void Csm_SymKeyWrapAsymServiceFinishNotification(void)
{
  /* Setting the state to IDLE */
  Csm_GddActiveSymKeyWrapAsymService.ucServiceState =
    CSM_SYM_KEY_WRAP_ASYM_IDLE;
}

boolean Csm_SymKeyWrapAsymServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveSymKeyWrapAsymService.pActiveServiceConfig->
    CallbackFct != NULL_PTR)
  {
    LblHasCallback = TRUE;
  }
  else
  {
    LblHasCallback = FALSE;
  }

  return LblHasCallback;
}
#endif /* (CSM_SYM_KEY_WRAP_ASYM_STATUS == STD_ON) */

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* ((CSM_SYM_KEY_WRAP_SYM_STATUS == STD_ON) || (CSM_SYM_KEY_WRAP_ASYM_STATUS == STD_ON)) */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
