/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Csm_AsymKeyExtract.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CSM Asymmetric Key Extraction Interface     **
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

#if ((CSM_ASYM_PUBLIC_KEY_EXTRACT_STATUS == STD_ON) || (CSM_ASYM_PRIVATE_KEY_EXTRACT_STATUS == STD_ON))
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (CSM_ASYM_PUBLIC_KEY_EXTRACT_STATUS == STD_ON) /* AsymmPubKeyExtract */
/* Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveAsymPublicKeyExtractService Csm_GddActiveAsymPublicKeyExtractService;
#endif /* (CSM_ASYM_PUBLIC_KEY_EXTRACT_STATUS == STD_ON) */

#if (CSM_ASYM_PRIVATE_KEY_EXTRACT_STATUS == STD_ON) /* AsymmPrivKeyExtract */
/* Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveAsymPrivateKeyExtractService Csm_GddActiveAsymPrivateKeyExtractService;
#endif /* (CSM_ASYM_PRIVATE_KEY_EXTRACT_STATUS == STD_ON) */

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
#if (CSM_ASYM_PUBLIC_KEY_EXTRACT_STATUS == STD_ON) /* AsymmPubKeyExtract */
/*******************************************************************************
** Function Name        : Csm_AsymPublicKeyExtractStart                       **
**                                                                            **
** Service ID           : 0x35                                                **
**                                                                            **
** Description          : This function will initialize the Asymmetrical      **
**                        public key extraction service of the CSM module.    **
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
**                        CSM_E_BUSY: service state is already "active"       **
**                                                                            **
** Preconditions        : CSM should have been initialized                    **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                                   Csm_GddActiveAsymPublicKeyExtractService **
**                                   Csm_GaaAsymPublicKeyExtractConfigType    **
**                        Function(s) invoked: Cry_<Primitive>Start           **
*******************************************************************************/
Std_ReturnType Csm_AsymPublicKeyExtractStart(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  /* Checking for CSM initialization */
  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_ASYMPUBLICKEYEXTRACTSTART_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Checking for Service Validation based on the configuration id  */
    if (cfgId >= CSM_ASYM_PUBLIC_KEY_EXTRACT_CFGID_LIMIT)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_ASYMPUBLICKEYEXTRACTSTART_SID, CSM_E_PARAM_METHOD_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveAsymPublicKeyExtractService.ucServiceState
      & CSM_ASYM_PUBLIC_KEY_EXTRACT_IDLE) != CSM_ASYM_PUBLIC_KEY_EXTRACT_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    Csm_GddActiveAsymPublicKeyExtractService.ucServiceState =
      CSM_ASYM_PUBLIC_KEY_EXTRACT_START;

    /* Fetching service configuration as updated during initial configuration */
    Csm_GddActiveAsymPublicKeyExtractService.pActiveServiceConfig =
      &Csm_GaaAsymPublicKeyExtractConfigType[cfgId];

    /* invoking primitive start function */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveAsymPublicKeyExtractService.
      pActiveServiceConfig->PrimitiveStartFct(
      (void*)Csm_GddActiveAsymPublicKeyExtractService.
      pActiveServiceConfig->PrimitiveConfigPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveAsymPublicKeyExtractService.pActiveServiceConfig->
        CallbackFct == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Setting the service state to active upon success */
          Csm_GddActiveAsymPublicKeyExtractService.ucServiceState =
            CSM_ASYM_PUBLIC_KEY_EXTRACT_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveAsymPublicKeyExtractService.ucServiceState =
            CSM_ASYM_PUBLIC_KEY_EXTRACT_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveAsymPublicKeyExtractService.pActiveServiceConfig->
          PrimitiveMainFct != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(
            Csm_GddActiveAsymPublicKeyExtractService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_AsymPublicKeyExtractUpdate                      **
**                                                                            **
** Service ID           : 0x36                                                **
**                                                                            **
** Description          : This function shall be used to feed the input data  **
**                        asymmetrical public key extraction service          **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, dataPtr, dataLength                          **
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
** Preconditions        : CSM Asymmetrical Key Extraction interface should    **
**                        have been initialized                               **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                                   Csm_GddActiveAsymPublicKeyExtractService **
**                        Function(s) invoked : Cry_<Primitive>Update         **
*******************************************************************************/
Std_ReturnType Csm_AsymPublicKeyExtractUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  /* Verifying the Null pointer */
  if (dataPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_ASYMPUBLICKEYEXTRACTUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    if (dataLength == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_ASYMPUBLICKEYEXTRACTUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveAsymPublicKeyExtractService.ucServiceState
      & CSM_ASYM_PUBLIC_KEY_EXTRACT_START) == CSM_ASYM_PUBLIC_KEY_EXTRACT_START)
      || ((Csm_GddActiveAsymPublicKeyExtractService.ucServiceState
      & CSM_ASYM_PUBLIC_KEY_EXTRACT_UPDATE) == CSM_ASYM_PUBLIC_KEY_EXTRACT_UPDATE)
      || ((Csm_GddActiveAsymPublicKeyExtractService.ucServiceState
      & CSM_ASYM_PUBLIC_KEY_EXTRACT_FINISH) == CSM_ASYM_PUBLIC_KEY_EXTRACT_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveAsymPublicKeyExtractService.ucServiceState
      & CSM_ASYM_PUBLIC_KEY_EXTRACT_ACTIVE) != CSM_ASYM_PUBLIC_KEY_EXTRACT_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_ASYMPUBLICKEYEXTRACTUPDATE_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to UPDATE */
    Csm_GddActiveAsymPublicKeyExtractService.ucServiceState =
      CSM_ASYM_PUBLIC_KEY_EXTRACT_UPDATE;

    /* Calling the primitive update function */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveAsymPublicKeyExtractService.
      pActiveServiceConfig->PrimitiveUpdateFct(cfgId, dataPtr, dataLength);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveAsymPublicKeyExtractService.pActiveServiceConfig->
        CallbackFct == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Setting the service state to active upon success */
          Csm_GddActiveAsymPublicKeyExtractService.ucServiceState =
            CSM_ASYM_PUBLIC_KEY_EXTRACT_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveAsymPublicKeyExtractService.ucServiceState =
            CSM_ASYM_PUBLIC_KEY_EXTRACT_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveAsymPublicKeyExtractService.pActiveServiceConfig->
          PrimitiveMainFct != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveAsymPublicKeyExtractService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_AsymPublicKeyExtractFinish                      **
**                                                                            **
** Service ID           : 0x37                                                **
**                                                                            **
** Description          : This function will be used to finish the            **
**                        asymmetrical public key extraction service.         **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId                                               **
**                                                                            **
** InOut parameter      : keyPtr                                              **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        E_NOT_OK: service state is "idle"                   **
**                                                                            **
** Preconditions        : CSM Asymmetrical Key Extraction interface should    **
**                        have been initialized                               **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                                   Csm_GddActiveAsymPublicKeyExtractService **
**                        Function(s) invoked : Cry_<Primitive>Finish         **
*******************************************************************************/
Std_ReturnType Csm_AsymPublicKeyExtractFinish(Csm_ConfigIdType cfgId,
  Csm_AsymPublicKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  if (keyPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_ASYMPUBLICKEYEXTRACTFINISH_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveAsymPublicKeyExtractService.ucServiceState
      & CSM_ASYM_PUBLIC_KEY_EXTRACT_START) == CSM_ASYM_PUBLIC_KEY_EXTRACT_START)
      || ((Csm_GddActiveAsymPublicKeyExtractService.ucServiceState
      & CSM_ASYM_PUBLIC_KEY_EXTRACT_UPDATE) == CSM_ASYM_PUBLIC_KEY_EXTRACT_UPDATE)
      || ((Csm_GddActiveAsymPublicKeyExtractService.ucServiceState
      & CSM_ASYM_PUBLIC_KEY_EXTRACT_FINISH) == CSM_ASYM_PUBLIC_KEY_EXTRACT_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveAsymPublicKeyExtractService.ucServiceState
      & CSM_ASYM_PUBLIC_KEY_EXTRACT_ACTIVE) != CSM_ASYM_PUBLIC_KEY_EXTRACT_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_ASYMPUBLICKEYEXTRACTFINISH_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to FINISH */
    Csm_GddActiveAsymPublicKeyExtractService.ucServiceState =
      CSM_ASYM_PUBLIC_KEY_EXTRACT_FINISH;

    /* Calling the primitive finish function */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveAsymPublicKeyExtractService.
      pActiveServiceConfig->PrimitiveFinishFct(cfgId, keyPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveAsymPublicKeyExtractService.pActiveServiceConfig->
        CallbackFct == NULL_PTR)
      {
        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveAsymPublicKeyExtractService.ucServiceState
          = CSM_ASYM_PUBLIC_KEY_EXTRACT_IDLE;
      }
      else
      {
        if (Csm_GddActiveAsymPublicKeyExtractService.pActiveServiceConfig->
          PrimitiveMainFct != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveAsymPublicKeyExtractService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_AsymPublicKeyExtractCallbackNotification        **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in the configuration of Asymmetrical Public   **
**                        Key Extraction service with the argument given by   **
**                        "Result".                                           **
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
**                            Csm_GddActiveAsymPublicKeyExtractService        **
*******************************************************************************/
void Csm_AsymPublicKeyExtractCallbackNotification(Std_ReturnType ddResult)
{
  switch (ddResult)
  {
  case CSM_E_BUSY:
    /* Do nothing */
    break;

  case E_OK:
    switch (Csm_GddActiveAsymPublicKeyExtractService.ucServiceState)
    {
    case CSM_ASYM_PUBLIC_KEY_EXTRACT_START:
    case CSM_ASYM_PUBLIC_KEY_EXTRACT_UPDATE:
      /* State is set to ACTIVE upon success */
      Csm_GddActiveAsymPublicKeyExtractService.ucServiceState
        = CSM_ASYM_PUBLIC_KEY_EXTRACT_ACTIVE;
      break;

    case CSM_ASYM_PUBLIC_KEY_EXTRACT_FINISH:
      /* Setting the service state to idle irrespective of the result */
      Csm_GddActiveAsymPublicKeyExtractService.ucServiceState
        = CSM_ASYM_PUBLIC_KEY_EXTRACT_IDLE;
      break;

    default:
      /* Do nothing */
      break;
    }
    break;

  default:
    switch (Csm_GddActiveAsymPublicKeyExtractService.ucServiceState)
    {
    case CSM_ASYM_PUBLIC_KEY_EXTRACT_START:
    case CSM_ASYM_PUBLIC_KEY_EXTRACT_UPDATE:
    case CSM_ASYM_PUBLIC_KEY_EXTRACT_FINISH:
      break;

    default:
      /* Do nothing */
      break;
    }

    /* state is set to IDLE upon Failure */
    Csm_GddActiveAsymPublicKeyExtractService.ucServiceState
      = CSM_ASYM_PUBLIC_KEY_EXTRACT_IDLE;
    break;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveAsymPublicKeyExtractService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveAsymPublicKeyExtractService.pActiveServiceConfig->
      CallbackFct(ddResult);
  }
}

/*******************************************************************************
** Function Name        : Csm_AsymPublicKeyExtractServiceFinishNotification   **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function shall set the state of the Asymmetric **
**                        Public Key Extraction service to "idle".            **
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
**                            Csm_GddActiveAsymPublicKeyExtractService        **
**                        Function(s) invoked: None                           **
*******************************************************************************/
void Csm_AsymPublicKeyExtractServiceFinishNotification(void)
{
  /* Setting the state to IDLE */
  Csm_GddActiveAsymPublicKeyExtractService.ucServiceState =
    CSM_ASYM_PUBLIC_KEY_EXTRACT_IDLE;
}

boolean Csm_AsymPublicKeyExtractServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveAsymPublicKeyExtractService.pActiveServiceConfig->
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
#endif /* (CSM_ASYM_PUBLIC_KEY_EXTRACT_STATUS == STD_ON) */

#if (CSM_ASYM_PRIVATE_KEY_EXTRACT_STATUS == STD_ON) /* AsymmPrivKeyExtract */
/*******************************************************************************
** Function Name        : Csm_AsymPrivateKeyExtractStart                      **
**                                                                            **
** Service ID           : 0x38                                                **
**                                                                            **
** Description          : This function will initialize the  asymmetrical     **
**                        private key extraction service of the CSM module.   **
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
**                        CSM_E_BUSY: service state is already "active"       **
**                                                                            **
** Preconditions        : CSM should have been initialized                    **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                                  Csm_GddActiveAsymPrivateKeyExtractService **
**                                  Csm_GaaAsymPrivateKeyExtractConfigType    **
**                        Function(s) invoked: Cry_<Primitive>Start           **
**                        Csm_FunctionPush                                    **
*******************************************************************************/
Std_ReturnType Csm_AsymPrivateKeyExtractStart(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  /* Checking for CSM initialization */
  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_ASYMPRIVATEKEYEXTRACTSTART_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Checking for Service Validation based on the configuration id  */
    if (cfgId >= CSM_ASYM_PRIVATE_KEY_EXTRACT_CFGID_LIMIT)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_ASYMPRIVATEKEYEXTRACTSTART_SID, CSM_E_PARAM_METHOD_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState
      & CSM_ASYM_PRIVATE_KEY_EXTRACT_IDLE) != CSM_ASYM_PRIVATE_KEY_EXTRACT_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState =
      CSM_ASYM_PRIVATE_KEY_EXTRACT_START;

    /* Fetching service configuration as updated during initial configuration */
    Csm_GddActiveAsymPrivateKeyExtractService.pActiveServiceConfig =
      &Csm_GaaAsymPrivateKeyExtractConfigType[cfgId];

    /* invoking primitive start function */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveAsymPrivateKeyExtractService.
      pActiveServiceConfig->PrimitiveStartFct(
      (void*)Csm_GddActiveAsymPrivateKeyExtractService.
      pActiveServiceConfig->PrimitiveConfigPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveAsymPrivateKeyExtractService.pActiveServiceConfig->
        CallbackFct == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Setting the service state to active upon success */
          Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState =
            CSM_ASYM_PRIVATE_KEY_EXTRACT_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState =
            CSM_ASYM_PRIVATE_KEY_EXTRACT_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveAsymPrivateKeyExtractService.pActiveServiceConfig->
          PrimitiveMainFct != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(
            Csm_GddActiveAsymPrivateKeyExtractService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_AsymPrivateKeyExtractUpdate                     **
**                                                                            **
** Service ID           : 0x39                                                **
**                                                                            **
** Description          : This function shall be used to feed the input data  **
**                        to asymmetrical private key extraction service      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, dataPtr, dataLength                          **
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
** Preconditions        : CSM Asymmetrical Key Extraction interface should    **
**                        have been initialized                               **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        Csm_GddActiveAsymPrivateKeyExtractService           **
**                                                                            **
**                        Function(s) invoked : Cry_<Primitive>Update         **
*******************************************************************************/
Std_ReturnType Csm_AsymPrivateKeyExtractUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  /* Verifying the Null pointer */
  if (dataPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_ASYMPRIVATEKEYEXTRACTUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    if (dataLength == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_ASYMPRIVATEKEYEXTRACTUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState
      & CSM_ASYM_PRIVATE_KEY_EXTRACT_START) == CSM_ASYM_PRIVATE_KEY_EXTRACT_START)
      || ((Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState
      & CSM_ASYM_PRIVATE_KEY_EXTRACT_UPDATE) == CSM_ASYM_PRIVATE_KEY_EXTRACT_UPDATE)
      || ((Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState
      & CSM_ASYM_PRIVATE_KEY_EXTRACT_FINISH) == CSM_ASYM_PRIVATE_KEY_EXTRACT_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState
      & CSM_ASYM_PRIVATE_KEY_EXTRACT_ACTIVE) != CSM_ASYM_PRIVATE_KEY_EXTRACT_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_ASYMPRIVATEKEYEXTRACTUPDATE_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to UPDATE */
    Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState =
      CSM_ASYM_PRIVATE_KEY_EXTRACT_UPDATE;

    /* Calling the primitive update function */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveAsymPrivateKeyExtractService.
      pActiveServiceConfig->PrimitiveUpdateFct(cfgId, dataPtr, dataLength);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveAsymPrivateKeyExtractService.pActiveServiceConfig->
        CallbackFct == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Setting the service state to active upon success */
          Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState =
            CSM_ASYM_PRIVATE_KEY_EXTRACT_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState =
            CSM_ASYM_PRIVATE_KEY_EXTRACT_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveAsymPrivateKeyExtractService.pActiveServiceConfig->
          PrimitiveMainFct != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveAsymPrivateKeyExtractService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_AsymPrivateKeyExtractFinish                     **
**                                                                            **
** Service ID           : 0x3a                                                **
**                                                                            **
** Description          : This function will be used to finish the            **
**                        asymmetrical private key extraction service.        **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId                                               **
**                                                                            **
** InOut parameter      : keyPtr                                              **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        E_NOT_OK: service state is "idle"                   **
**                                                                            **
** Preconditions        : CSM Asymmetrical Key Extraction interface should    **
**                        have been initialized                               **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        Csm_GddActiveAsymPrivateKeyExtractService           **
**                        Function(s) invoked : Cry_<Primitive>Finish         **
*******************************************************************************/
Std_ReturnType Csm_AsymPrivateKeyExtractFinish(Csm_ConfigIdType cfgId,
  Csm_AsymPrivateKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  if (keyPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_ASYMPRIVATEKEYEXTRACTFINISH_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState
      & CSM_ASYM_PRIVATE_KEY_EXTRACT_START) == CSM_ASYM_PRIVATE_KEY_EXTRACT_START)
      || ((Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState
      & CSM_ASYM_PRIVATE_KEY_EXTRACT_UPDATE) == CSM_ASYM_PRIVATE_KEY_EXTRACT_UPDATE)
      || ((Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState
      & CSM_ASYM_PRIVATE_KEY_EXTRACT_FINISH) == CSM_ASYM_PRIVATE_KEY_EXTRACT_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState
      & CSM_ASYM_PRIVATE_KEY_EXTRACT_ACTIVE) != CSM_ASYM_PRIVATE_KEY_EXTRACT_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_ASYMPRIVATEKEYEXTRACTFINISH_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to FINISH */
    Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState =
      CSM_ASYM_PRIVATE_KEY_EXTRACT_FINISH;

    /* Calling the primitive finish function */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveAsymPrivateKeyExtractService.
      pActiveServiceConfig->PrimitiveFinishFct(cfgId, keyPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveAsymPrivateKeyExtractService.pActiveServiceConfig->
        CallbackFct == NULL_PTR)
      {
        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState
          = CSM_ASYM_PRIVATE_KEY_EXTRACT_IDLE;
      }
      else
      {
        if (Csm_GddActiveAsymPrivateKeyExtractService.pActiveServiceConfig->
          PrimitiveMainFct != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveAsymPrivateKeyExtractService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_AsymPrivateKeyExtractCallbackNotification       **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in configuration of Asymmetrical Private Key  **
**                        Extraction service with argument given by "Result". **
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
**                           Csm_GddActiveAsymPrivateKeyExtractService        **
*******************************************************************************/
void Csm_AsymPrivateKeyExtractCallbackNotification(Std_ReturnType ddResult)
{
  switch (ddResult)
  {
  case CSM_E_BUSY:
    /* Do nothing */
    break;

  case E_OK:
    switch (Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState)
    {
    case CSM_ASYM_PRIVATE_KEY_EXTRACT_START:
    case CSM_ASYM_PRIVATE_KEY_EXTRACT_UPDATE:
      /* State is set to ACTIVE upon success */
      Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState
        = CSM_ASYM_PRIVATE_KEY_EXTRACT_ACTIVE;
      break;

    case CSM_ASYM_PRIVATE_KEY_EXTRACT_FINISH:
      /* Setting the service state to idle irrespective of the result */
      Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState
        = CSM_ASYM_PRIVATE_KEY_EXTRACT_IDLE;
      break;

    default:
      /* Do nothing */
      break;
    }
    break;

  default:
    switch (Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState)
    {
    case CSM_ASYM_PRIVATE_KEY_EXTRACT_START:
    case CSM_ASYM_PRIVATE_KEY_EXTRACT_UPDATE:
    case CSM_ASYM_PRIVATE_KEY_EXTRACT_FINISH:
      break;

    default:
      /* Do nothing */
      break;
    }

    /* state is set to IDLE upon Failure */
    Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState
      = CSM_ASYM_PRIVATE_KEY_EXTRACT_IDLE;
    break;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveAsymPrivateKeyExtractService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveAsymPrivateKeyExtractService.pActiveServiceConfig->
      CallbackFct(ddResult);
  }
}

/*******************************************************************************
** Function Name        : Csm_AsymPrivateKeyExtractServiceFinishNotification  **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function shall set the state of Asymmetrical   **
**                        Private Key Extraction service to "idle".           **
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
**                           Csm_GddActiveAsymPrivateKeyExtractService        **
**                        Function(s) invoked: None                           **
*******************************************************************************/
void Csm_AsymPrivateKeyExtractServiceFinishNotification(void)
{
  /* Setting the state to IDLE */
  Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState =
    CSM_ASYM_PRIVATE_KEY_EXTRACT_IDLE;
}

boolean Csm_AsymPrivateKeyExtractServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveAsymPrivateKeyExtractService.pActiveServiceConfig->
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
#endif /* (CSM_ASYM_PRIVATE_KEY_EXTRACT_STATUS == STD_ON) */

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* ((CSM_ASYM_PUBLIC_KEY_EXTRACT_STATUS == STD_ON) || (CSM_ASYM_PRIVATE_KEY_EXTRACT_STATUS == STD_ON)) */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
