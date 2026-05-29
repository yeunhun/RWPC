/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Csm_AsymKeyWrap.c                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CSM Asymmetric Key Wrapping Interface using **
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

#if ((CSM_ASYM_KEY_WRAP_SYM_STATUS == STD_ON) || (CSM_ASYM_KEY_WRAP_ASYM_STATUS == STD_ON))
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (CSM_ASYM_KEY_WRAP_SYM_STATUS == STD_ON) /* Symmetric Wrapping Key */
/* Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveAsymPrivateKeyWrapSymService Csm_GddActiveAsymPrivateKeyWrapSymService;
#endif /* (CSM_ASYM_KEY_WRAP_SYM_STATUS == STD_ON) */

#if (CSM_ASYM_KEY_WRAP_ASYM_STATUS == STD_ON) /* Asymmetric Wrapping Key */
/* Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveAsymPrivateKeyWrapAsymService Csm_GddActiveAsymPrivateKeyWrapAsymService;
#endif /* (CSM_ASYM_KEY_WRAP_ASYM_STATUS == STD_ON) */

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
#if (CSM_ASYM_KEY_WRAP_SYM_STATUS == STD_ON) /* Symmetric Wrapping Key */
/*******************************************************************************
** Function Name        : Csm_AsymPrivateKeyWrapSymStart                      **
**                                                                            **
** Service ID           : 0x46                                                **
**                                                                            **
** Description          : This function will initialize the asymmetrical key  **
**                        wrapping service of the CSM module. It will be      **
**                        using symmetric keys for wrapping the Asymmetric    **
**                        key structure                                       **
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
**                        Csm_GddActiveAsymPrivateKeyWrapSymService,          **
**                        Csm_GaaAsymPrivateKeyWrapSymConfigType              **
**                                                                            **
**                        Function(s) invoked: Cry_<Primitive>Start           **
**                        Csm_FunctionPush                                    **
*******************************************************************************/
Std_ReturnType Csm_AsymPrivateKeyWrapSymStart(Csm_ConfigIdType cfgId,
  const Csm_AsymPrivateKeyType* keyPtr, const Csm_SymKeyType* wrappingKeyPtr)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  /* Checking for CSM initialization */
  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_ASYMPRIVATEKEYWRAPSYMSTART_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Checking for Service Validation based on the configuration id  */
    if (cfgId >= CSM_ASYM_KEY_WRAP_SYM_CFGID_LIMIT)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_ASYMPRIVATEKEYWRAPSYMSTART_SID, CSM_E_PARAM_METHOD_INVALID);
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
        CSM_ASYMPRIVATEKEYWRAPSYMSTART_SID, CSM_E_PARAM_PTR_INVALID);
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
        CSM_ASYMPRIVATEKEYWRAPSYMSTART_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Verifying the Null pointer */
    if (wrappingKeyPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_ASYMPRIVATEKEYWRAPSYMSTART_SID, CSM_E_PARAM_PTR_INVALID);
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
        CSM_ASYMPRIVATEKEYWRAPSYMSTART_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState
      & CSM_ASYM_PRIVATE_KEY_WRAP_SYM_IDLE) != CSM_ASYM_PRIVATE_KEY_WRAP_SYM_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* updating the state to service start */
    Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState =
      CSM_ASYM_PRIVATE_KEY_WRAP_SYM_START;

    /* Fetching service configuration */
    Csm_GddActiveAsymPrivateKeyWrapSymService.pActiveServiceConfig =
      &Csm_GaaAsymPrivateKeyWrapSymConfigType[cfgId];

    /*
     * invoking primitive start function
     * Will be using AES primitive for the Symmetrical Wrapping
     * InitVector is NULL and InitVectorLength is 0 as they will not be used
     */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveAsymPrivateKeyWrapSymService.
      pActiveServiceConfig->PrimitiveStartFct(
      (void*)Csm_GddActiveAsymPrivateKeyWrapSymService.
      pActiveServiceConfig->PrimitiveConfigPtr, keyPtr, wrappingKeyPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveAsymPrivateKeyWrapSymService.pActiveServiceConfig->
        CallbackFct == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Setting the service state to active upon success */
          Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState =
            CSM_ASYM_PRIVATE_KEY_WRAP_SYM_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState =
            CSM_ASYM_PRIVATE_KEY_WRAP_SYM_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveAsymPrivateKeyWrapSymService.pActiveServiceConfig->
          PrimitiveMainFct != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(
            Csm_GddActiveAsymPrivateKeyWrapSymService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_AsymPrivateKeyWrapSymUpdate                     **
**                                                                            **
** Service ID           : 0x47                                                **
**                                                                            **
** Description          : This function retrieve the result of the key        **
**                        wrapping operation from the asymmetrical key        **
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
** Preconditions        : CSM Asymmetrical Key Wrap interface should have     **
**                        been initialized                                    **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        Csm_GddActiveAsymPrivateKeyWrapSymService           **
**                        Function(s) invoked: Cry_<Primitive>Update          **
*******************************************************************************/
Std_ReturnType Csm_AsymPrivateKeyWrapSymUpdate(Csm_ConfigIdType cfgId,
  uint8* dataPtr, uint32* dataLengthPtr)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  /* Verifying the Null pointer */
  if (dataPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_ASYMPRIVATEKEYWRAPSYMUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    if (dataLengthPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_ASYMPRIVATEKEYWRAPSYMUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
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
        CSM_ASYMPRIVATEKEYWRAPSYMUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState
      & CSM_ASYM_PRIVATE_KEY_WRAP_SYM_START) == CSM_ASYM_PRIVATE_KEY_WRAP_SYM_START)
      || ((Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState
      & CSM_ASYM_PRIVATE_KEY_WRAP_SYM_UPDATE) == CSM_ASYM_PRIVATE_KEY_WRAP_SYM_UPDATE)
      || ((Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState
      & CSM_ASYM_PRIVATE_KEY_WRAP_SYM_FINISH) == CSM_ASYM_PRIVATE_KEY_WRAP_SYM_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState
      & CSM_ASYM_PRIVATE_KEY_WRAP_SYM_ACTIVE) != CSM_ASYM_PRIVATE_KEY_WRAP_SYM_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_ASYMPRIVATEKEYWRAPSYMUPDATE_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to UPDATE */
    Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState =
      CSM_ASYM_PRIVATE_KEY_WRAP_SYM_UPDATE;

    /* Invoke respective primitive Update function */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveAsymPrivateKeyWrapSymService.
      pActiveServiceConfig->PrimitiveUpdateFct(cfgId, dataPtr, dataLengthPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveAsymPrivateKeyWrapSymService.pActiveServiceConfig->
        CallbackFct == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Setting the service state to active upon success */
          Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState =
            CSM_ASYM_PRIVATE_KEY_WRAP_SYM_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState =
            CSM_ASYM_PRIVATE_KEY_WRAP_SYM_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveAsymPrivateKeyWrapSymService.pActiveServiceConfig->
          PrimitiveMainFct != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(
            Csm_GddActiveAsymPrivateKeyWrapSymService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_AsymPrivateKeyWrapSymFinish                     **
**                                                                            **
** Service ID           : 0x48                                                **
**                                                                            **
** Description          : This function will be used to finish the            **
**                        asymmetrical key wrapping service.                  **
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
** Preconditions        : CSM Asymmetrical Key Wrap interface should have     **
**                        been initialized                                    **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        Csm_GddActiveAsymPrivateKeyWrapSymService           **
**                        Function(s) invoked: Cry_<Primitive>Finish          **
*******************************************************************************/
Std_ReturnType Csm_AsymPrivateKeyWrapSymFinish(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  if (((Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState
    & CSM_ASYM_PRIVATE_KEY_WRAP_SYM_START) == CSM_ASYM_PRIVATE_KEY_WRAP_SYM_START)
    || ((Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState
    & CSM_ASYM_PRIVATE_KEY_WRAP_SYM_UPDATE) == CSM_ASYM_PRIVATE_KEY_WRAP_SYM_UPDATE)
    || ((Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState
    & CSM_ASYM_PRIVATE_KEY_WRAP_SYM_FINISH) == CSM_ASYM_PRIVATE_KEY_WRAP_SYM_FINISH))
  {
    LddReturnValue = CSM_E_BUSY;
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState
      & CSM_ASYM_PRIVATE_KEY_WRAP_SYM_ACTIVE) != CSM_ASYM_PRIVATE_KEY_WRAP_SYM_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_ASYMPRIVATEKEYWRAPSYMFINISH_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to FINISH */
    Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState =
      CSM_ASYM_PRIVATE_KEY_WRAP_SYM_FINISH;

    /*
     * Calling the primitive finish function
     * Will be using AES primitive for the Symmetrical Wrapping
     */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveAsymPrivateKeyWrapSymService.
      pActiveServiceConfig->PrimitiveFinishFct(cfgId);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveAsymPrivateKeyWrapSymService.pActiveServiceConfig->
        CallbackFct == NULL_PTR)
      {
        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState
          = CSM_ASYM_PRIVATE_KEY_WRAP_SYM_IDLE;
      }
      else
      {
        if (Csm_GddActiveAsymPrivateKeyWrapSymService.pActiveServiceConfig->
          PrimitiveMainFct != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(
            Csm_GddActiveAsymPrivateKeyWrapSymService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_AsymPrivateKeyWrapSymCallbackNotification       **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in the configuration of Asymmetrical Private  **
**                        Key Wrapping with Symmetrical Key service with the  **
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
**                           Csm_GddActiveAsymPrivateKeyWrapSymService        **
*******************************************************************************/
void Csm_AsymPrivateKeyWrapSymCallbackNotification(Std_ReturnType ddResult)
{
  switch (ddResult)
  {
  case CSM_E_BUSY:
    /* Do nothing */
    break;

  case E_OK:
    switch (Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState)
    {
    case CSM_ASYM_PRIVATE_KEY_WRAP_SYM_START:
    case CSM_ASYM_PRIVATE_KEY_WRAP_SYM_UPDATE:
      /* State is set to ACTIVE upon success */
      Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState
        = CSM_ASYM_PRIVATE_KEY_WRAP_SYM_ACTIVE;
      break;

    case CSM_ASYM_PRIVATE_KEY_WRAP_SYM_FINISH:
      /* Setting the service state to idle irrespective of the result */
      Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState
        = CSM_ASYM_PRIVATE_KEY_WRAP_SYM_IDLE;
      break;

    default:
      /* Do nothing */
      break;
    }
    break;

  default:
    switch (Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState)
    {
    case CSM_ASYM_PRIVATE_KEY_WRAP_SYM_START:
    case CSM_ASYM_PRIVATE_KEY_WRAP_SYM_UPDATE:
    case CSM_ASYM_PRIVATE_KEY_WRAP_SYM_FINISH:
      break;

    default:
      /* Do nothing */
      break;
    }

    /* state is set to IDLE upon Failure */
    Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState
      = CSM_ASYM_PRIVATE_KEY_WRAP_SYM_IDLE;
    break;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveAsymPrivateKeyWrapSymService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveAsymPrivateKeyWrapSymService.pActiveServiceConfig->
      CallbackFct(ddResult);
  }
}

/*******************************************************************************
** Function Name        : Csm_AsymPrivateKeyWrapSymServiceFinishNotification  **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function shall set the state of the Asymmetric **
**                        Private Key Wrapping with Symmetrical Keys service  **
**                        to "idle".                                          **
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
**                           Csm_GddActiveAsymPrivateKeyWrapSymService        **
**                        Function(s) invoked: None                           **
*******************************************************************************/
void Csm_AsymPrivateKeyWrapSymServiceFinishNotification(void)
{
  /* Setting the state to IDLE */
  Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState =
    CSM_ASYM_PRIVATE_KEY_WRAP_SYM_IDLE;
}

boolean Csm_AsymPrivateKeyWrapSymServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveAsymPrivateKeyWrapSymService.pActiveServiceConfig->
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
#endif /* (CSM_ASYM_KEY_WRAP_SYM_STATUS == STD_ON) */

#if (CSM_ASYM_KEY_WRAP_ASYM_STATUS == STD_ON) /* Asymmetric Wrapping Key */
/*******************************************************************************
** Function Name        : Csm_AsymPrivateKeyWrapAsymStart                     **
**                                                                            **
** Service ID           : 0x49                                                **
**                                                                            **
** Description          : This function will initialize the asymmetrical key  **
**                        wrapping service of the CSM module. It will be      **
**                        using asymmetric keys for wrapping the Asymmetric   **
**                        key structure                                       **
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
** Remarks              : Global Variable(s): ddKeyPtr,                       **
**                        Csm_GddActiveAsymPrivateKeyWrapAsymService,         **
**                        Csm_GaaAsymPrivateKeyWrapAsymConfigType             **
**                                                                            **
**                        Function(s) invoked: Cry_<Primitive>Start,          **
**                        Csm_FunctionPush                                    **
*******************************************************************************/
Std_ReturnType Csm_AsymPrivateKeyWrapAsymStart(Csm_ConfigIdType cfgId,
  const Csm_AsymPrivateKeyType* keyPtr,
  const Csm_AsymPublicKeyType* wrappingKeyPtr)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  /* Checking for CSM initialization */
  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_ASYMPRIVATEKEYWRAPASYMSTART_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Checking for Service Validation based on the configuration id  */
    if (cfgId >= CSM_ASYM_KEY_WRAP_ASYM_CFGID_LIMIT)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_ASYMPRIVATEKEYWRAPASYMSTART_SID, CSM_E_PARAM_METHOD_INVALID);
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
        CSM_ASYMPRIVATEKEYWRAPASYMSTART_SID, CSM_E_PARAM_PTR_INVALID);
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
        CSM_ASYMPRIVATEKEYWRAPASYMSTART_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Verifying the Null pointer */
    if (wrappingKeyPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_ASYMPRIVATEKEYWRAPASYMSTART_SID, CSM_E_PARAM_PTR_INVALID);
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
        CSM_ASYMPRIVATEKEYWRAPASYMSTART_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState
      & CSM_ASYM_PRIVATE_KEY_WRAP_SYM_IDLE) != CSM_ASYM_PRIVATE_KEY_WRAP_SYM_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* updating the state to service start */
    Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState =
      CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_START;

    /* Fetching service configuration as updated during initial configuration */
    Csm_GddActiveAsymPrivateKeyWrapAsymService.pActiveServiceConfig =
      &Csm_GaaAsymPrivateKeyWrapAsymConfigType[cfgId];

    /*
     * invoking primitive start function
     * Will be using RSA primitive for the Asymmetrical Wrapping
     */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveAsymPrivateKeyWrapAsymService.
      pActiveServiceConfig->PrimitiveStartFct(
      (void*)Csm_GddActiveAsymPrivateKeyWrapAsymService.
      pActiveServiceConfig->PrimitiveConfigPtr, keyPtr, wrappingKeyPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveAsymPrivateKeyWrapAsymService.pActiveServiceConfig->
        CallbackFct == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Setting the service state to active upon success */
          Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState =
            CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState =
            CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveAsymPrivateKeyWrapAsymService.pActiveServiceConfig->
          PrimitiveMainFct != NULL_PTR)
        {
          LddReturnValue =
            Csm_FunctionPush(Csm_GddActiveAsymPrivateKeyWrapAsymService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_AsymPrivateKeyWrapAsymUpdate                    **
**                                                                            **
** Service ID           : 0x4a                                                **
**                                                                            **
** Description          : This function retrieve the result of the key        **
**                        wrapping operation from the asymmetrical key        **
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
** Preconditions        : CSM Asymmetrical Key Wrap interface should have     **
**                        been initialized                                    **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        Csm_GddActiveAsymPrivateKeyWrapAsymService          **
**                                                                            **
**                        Function(s) invoked: Cry_<Primitive>Update          **
*******************************************************************************/
Std_ReturnType Csm_AsymPrivateKeyWrapAsymUpdate(Csm_ConfigIdType cfgId,
  uint8* dataPtr, uint32* dataLengthPtr)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  /* Verifying the Null pointer */
  if (dataPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_ASYMPRIVATEKEYWRAPASYMUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Verifying the Null pointer */
    if (dataLengthPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_ASYMPRIVATEKEYWRAPASYMUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
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
        CSM_ASYMPRIVATEKEYWRAPASYMUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState
      & CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_START) == CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_START)
      || ((Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState
      & CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_UPDATE) == CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_UPDATE)
      || ((Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState
      & CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_FINISH) == CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState
      & CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_ACTIVE) != CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_ASYMPRIVATEKEYWRAPASYMUPDATE_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to UPDATE */
    Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState =
      CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_UPDATE;

    /*
     * Calling the primitive update function
     * Will be using RSA primitive for the Asymmetrical Wrapping
     */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveAsymPrivateKeyWrapAsymService.
      pActiveServiceConfig->PrimitiveUpdateFct(cfgId, dataPtr, dataLengthPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveAsymPrivateKeyWrapAsymService.pActiveServiceConfig->
        CallbackFct == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Setting the service state to active upon success */
          Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState =
            CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState =
            CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveAsymPrivateKeyWrapAsymService.pActiveServiceConfig->
          PrimitiveMainFct != NULL_PTR)
        {
          LddReturnValue =
            Csm_FunctionPush(Csm_GddActiveAsymPrivateKeyWrapAsymService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_AsymPrivateKeyWrapAsymFinish                    **
**                                                                            **
** Service ID           : 0x4b                                                **
**                                                                            **
** Description          : This function will be used to finish the            **
**                        asymmetrical key wrapping service.                  **
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
** Preconditions        : CSM Asymmetrical Key Wrap interface should have     **
**                        been initialized                                    **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        Csm_GddActiveAsymPrivateKeyWrapAsymService          **
**                                                                            **
**                        Function(s) invoked: Cry_<Primitive>Finish          **
*******************************************************************************/
Std_ReturnType Csm_AsymPrivateKeyWrapAsymFinish(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  if (((Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState
    & CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_START) == CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_START)
    || ((Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState
    & CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_UPDATE) == CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_UPDATE)
    || ((Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState
    & CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_FINISH) == CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_FINISH))
  {
    LddReturnValue = CSM_E_BUSY;
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState
      & CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_ACTIVE) != CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_ASYMPRIVATEKEYWRAPASYMFINISH_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to FINISH */
    Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState =
      CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_FINISH;

    /*
     * Calling the primitive finish function
     * Will be using RSA primitive for the Asymmetrical Wrapping
     */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveAsymPrivateKeyWrapAsymService.
      pActiveServiceConfig->PrimitiveFinishFct(cfgId);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveAsymPrivateKeyWrapAsymService.pActiveServiceConfig->
        CallbackFct == NULL_PTR)
      {
        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState
          = CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_IDLE;
      }
      else
      {
        if (Csm_GddActiveAsymPrivateKeyWrapAsymService.pActiveServiceConfig->
          PrimitiveMainFct != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveAsymPrivateKeyWrapAsymService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_AsymPrivateKeyWrapAsymCallbackNotification      **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in the configuration of Asymmetrical Private  **
**                        Key Wrapping with Asymmetric Key service with the   **
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
**                          Csm_GddActiveAsymPrivateKeyWrapAsymService        **
*******************************************************************************/
void Csm_AsymPrivateKeyWrapAsymCallbackNotification(Std_ReturnType ddResult)
{
  switch (ddResult)
  {
  case CSM_E_BUSY:
    /* Do nothing */
    break;

  case E_OK:
    switch (Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState)
    {
    case CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_START:
    case CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_UPDATE:
      /* State is set to ACTIVE upon success */
      Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState
        = CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_ACTIVE;
      break;

    case CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_FINISH:
      /* Setting the service state to idle irrespective of the result */
      Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState
        = CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_IDLE;
      break;

    default:
      /* Do nothing */
      break;
    }
    break;

  default:
    switch (Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState)
    {
    case CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_START:
    case CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_UPDATE:
    case CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_FINISH:
      break;

    default:
      /* Do nothing */
      break;
    }

    /* state is set to IDLE upon Failure */
    Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState
      = CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_IDLE;
    break;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveAsymPrivateKeyWrapAsymService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveAsymPrivateKeyWrapAsymService.pActiveServiceConfig->
      CallbackFct(ddResult);
  }
}

/*******************************************************************************
** Function Name        : Csm_AsymPrivateKeyWrapAsymServiceFinishNotification **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function shall set the state of the Asymmetric **
**                        Private Key Wrapping with Asymmetric Key            **
**                        service to "idle".                                  **
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
**                          Csm_GddActiveAsymPrivateKeyWrapAsymService        **
**                        Function(s) invoked: None                           **
*******************************************************************************/
void Csm_AsymPrivateKeyWrapAsymServiceFinishNotification(void)
{
  /* Setting the state to IDLE */
  Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState =
    CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_IDLE;
}

boolean Csm_AsymPrivateKeyWrapAsymServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveAsymPrivateKeyWrapAsymService.pActiveServiceConfig->
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
#endif /* (CSM_ASYM_KEY_WRAP_ASYM_STATUS == STD_ON) */

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* ((CSM_ASYM_KEY_WRAP_SYM_STATUS == STD_ON) || (CSM_ASYM_KEY_WRAP_ASYM_STATUS == STD_ON)) */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
