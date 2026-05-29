/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Csm_Mac.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of MAC Interface                               **
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
** 1.0.6     09-Aug-2016   Sinil        Redmine #5693, #5694, #5760           **
** 1.0.5     12-Jul-2016   Sinil        Redmine #5514                         **
** 1.0.4     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.3     16-May-2016   Sinil        Redmine #4903                         **
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

#if ((CSM_MAC_GENERATE_STATUS == STD_ON) || (CSM_MAC_VERIFY_STATUS == STD_ON))
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (CSM_MAC_GENERATE_STATUS == STD_ON)
/* Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveMacGenerateService Csm_GddActiveMacGenerateService;
#endif /* (CSM_MAC_GENERATE_STATUS == STD_ON) */

#if (CSM_MAC_VERIFY_STATUS == STD_ON)
/* Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveMacVerifyService Csm_GddActiveMacVerifyService;
#endif /* (CSM_MAC_VERIFY_STATUS == STD_ON) */

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
#if (CSM_MAC_GENERATE_STATUS == STD_ON)
/*******************************************************************************
** Function Name        : Csm_MacGenerateStart                                **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : This function initializes the MAC Generate service  **
**                        of CSM module. It will store the configuration      **
**                        information as identified by cfgId and will call    **
**                        the corresponding Cry_<primitive>Start() provided   **
**                        the service state is not "active" and shall return  **
**                        the value returned by that function and set the     **
**                        service state to "active"                           **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, keyPtr                                       **
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
** Remarks              : Global Variable(s): Csm_GddActiveMacGenerateService **
**                                            Csm_GaaMacGenerateConfigType    **
**                                                                            **
**                        Function(s) invoked : Cry_<Primitive>Start,         **
**                        Csm_FunctionPush, Det_ReportError                   **
*******************************************************************************/
Std_ReturnType Csm_MacGenerateStart(Csm_ConfigIdType cfgId,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  /* Checking for CSM initialization */
  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_MACGENERATESTART_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Checking for Service Validation based on the configuration id  */
    if (cfgId >= Csm_GddMacGenerateCfgidLimit)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_MACGENERATESTART_SID, CSM_E_PARAM_METHOD_INVALID);
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
        CSM_MACGENERATESTART_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "No Impact of this rule violation" */
    if (keyPtr->length == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_MACGENERATESTART_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveMacGenerateService.ucServiceState
      & CSM_MAC_GENERATE_IDLE) != CSM_MAC_GENERATE_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* updating the state to service start */
    Csm_GddActiveMacGenerateService.ucServiceState = CSM_MAC_GENERATE_START;

    /* Fetching service configuration as updated during initial configuration */
    Csm_GddActiveMacGenerateService.pActiveServiceConfig =
      &Csm_GaaMacGenerateConfigType[cfgId];

    /* invoking primitive start function */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveMacGenerateService.
      pActiveServiceConfig->PrimitiveStartFct(
      (void*)Csm_GddActiveMacGenerateService.
      pActiveServiceConfig->PrimitiveConfigPtr, keyPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveMacGenerateService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Setting the service state to active upon success */
          Csm_GddActiveMacGenerateService.ucServiceState = CSM_MAC_GENERATE_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveMacGenerateService.ucServiceState = CSM_MAC_GENERATE_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveMacGenerateService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveMacGenerateService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_MacGenerateUpdate                               **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : This function provide the input data to the MAC     **
**                        Generate service. It calls Cry_<Primitive>Update    **
**                        of the primitive identified by the stored           **
**                        configuration information and return the value      **
**                        returned by that function                           **
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
** Preconditions        : CSM MAC interface should have been initialized      **
**                                                                            **
** Remarks              : Global Variable(s): Csm_GddActiveMacGenerateService **
**                                                                            **
**                        Function(s) invoked : Cry_<Primitive>Update,        **
**                        Det_ReportError                                     **
*******************************************************************************/
Std_ReturnType Csm_MacGenerateUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  /* Verifying the Null pointer */
  if (dataPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_MACGENERATEUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
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
        CSM_MACGENERATEUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveMacGenerateService.ucServiceState
      & CSM_MAC_GENERATE_START) == CSM_MAC_GENERATE_START)
      || ((Csm_GddActiveMacGenerateService.ucServiceState
      & CSM_MAC_GENERATE_UPDATE) == CSM_MAC_GENERATE_UPDATE)
      || ((Csm_GddActiveMacGenerateService.ucServiceState
      & CSM_MAC_GENERATE_FINISH) == CSM_MAC_GENERATE_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveMacGenerateService.ucServiceState
      & CSM_MAC_GENERATE_ACTIVE) != CSM_MAC_GENERATE_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_MACGENERATEUPDATE_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to UPDATE */
    Csm_GddActiveMacGenerateService.ucServiceState = CSM_MAC_GENERATE_UPDATE;

    /* Calling the primitive update function */
    /* polyspace-begin MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveMacGenerateService.pActiveServiceConfig->
      PrimitiveUpdateFct(cfgId, dataPtr, dataLength);
    /* polyspace-end MISRA-C3:18.1 RTE:IDP RTE:COR */

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveMacGenerateService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Set the Service State to CSM_MAC_GENERATE_ACTIVE */
          Csm_GddActiveMacGenerateService.ucServiceState =
            CSM_MAC_GENERATE_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveMacGenerateService.ucServiceState = CSM_MAC_GENERATE_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveMacGenerateService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveMacGenerateService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_MacGenerateFinish                               **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : This function will be used to finish the MAC        **
**                        Generate service by calling Cry_<Primitive>Finish   **
**                        as identified by stored configuration information   **
**                        and returns the value returned by that function     **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, TruncationIsAllowed                          **
**                                                                            **
** InOut parameter      : resultLengthPtr                                     **
**                                                                            **
** Output Parameters    : resultPtr                                           **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        CSM_E_SMALL_BUFFER: the provided buffer is too      **
**                        small to store the result, and truncation was not   **
**                        allowed                                             **
**                        E_NOT_OK: service state is "idle"                   **
**                                                                            **
** Preconditions        : CSM MAC interface should have been initialized      **
**                                                                            **
** Remarks              : Global Variable(s): Csm_GddActiveMacGenerateService **
**                                                                            **
**                        Function(s) invoked : Cry_<Primitive>Finish,        **
**                        Det_ReportError                                     **
*******************************************************************************/
Std_ReturnType Csm_MacGenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  /* Verifying the Null pointer */
  if (resultPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_MACGENERATEFINISH_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Verifying the Null pointer */
    if (resultLengthPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_MACGENERATEFINISH_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "No Impact of this rule violation" */
    if (*resultLengthPtr == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_MACGENERATEFINISH_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveMacGenerateService.ucServiceState
      & CSM_MAC_GENERATE_START) == CSM_MAC_GENERATE_START)
      || ((Csm_GddActiveMacGenerateService.ucServiceState
      & CSM_MAC_GENERATE_UPDATE) == CSM_MAC_GENERATE_UPDATE)
      || ((Csm_GddActiveMacGenerateService.ucServiceState
      & CSM_MAC_GENERATE_FINISH) == CSM_MAC_GENERATE_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveMacGenerateService.ucServiceState
      & CSM_MAC_GENERATE_ACTIVE) != CSM_MAC_GENERATE_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_MACGENERATEFINISH_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to FINISH */
    Csm_GddActiveMacGenerateService.ucServiceState =
      CSM_MAC_GENERATE_FINISH;

    /* Calling the primitive finish function */
    /* polyspace-begin MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveMacGenerateService.pActiveServiceConfig->
      PrimitiveFinishFct(cfgId, resultPtr, resultLengthPtr, TruncationIsAllowed);
    /* polyspace-end MISRA-C3:18.1 RTE:IDP RTE:COR */

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveMacGenerateService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        #if (CSM_DEV_ERROR_DETECT == STD_ON)
        if (LddReturnValue == CSM_E_SMALL_BUFFER)
        {
          (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
            CSM_MACGENERATEFINISH_SID, CSM_E_BUFFER_TOO_SMALL);
        }
        #endif

        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveMacGenerateService.ucServiceState = CSM_MAC_GENERATE_IDLE;
      }
      else
      {
        if (Csm_GddActiveMacGenerateService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveMacGenerateService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_MacGenerateCallbackNotification                 **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in the configuration of the service Mac       **
**                        Generate with the argument given by "Result".       **
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
** Remarks              : Global Variable(s): Csm_GddActiveMacGenerateService **
**                                                                            **
**                        Function(s) invoked: Det_ReportError                **
*******************************************************************************/
void Csm_MacGenerateCallbackNotification(Std_ReturnType ddResult)
{
  switch (ddResult)
  {
  case CSM_E_BUSY:
    /* Do nothing */
    break;

  case E_OK:
    switch (Csm_GddActiveMacGenerateService.ucServiceState)
    {
    case CSM_MAC_GENERATE_START:
    case CSM_MAC_GENERATE_UPDATE:
      /* State is set to ACTIVE upon success */
      Csm_GddActiveMacGenerateService.ucServiceState = CSM_MAC_GENERATE_ACTIVE;
      break;

    case CSM_MAC_GENERATE_FINISH:
      /* Setting the service state to idle irrespective of the result */
      Csm_GddActiveMacGenerateService.ucServiceState = CSM_MAC_GENERATE_IDLE;
      break;

    default:
      /* Do nothing */
      break;
    }
    break;

  default:
    switch (Csm_GddActiveMacGenerateService.ucServiceState)
    {
    case CSM_MAC_GENERATE_START:
    case CSM_MAC_GENERATE_UPDATE:
      break;

    case CSM_MAC_GENERATE_FINISH:
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      if (ddResult == CSM_E_SMALL_BUFFER)
      {
        (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
          CSM_MACGENERATEFINISH_SID, CSM_E_BUFFER_TOO_SMALL);
      }
      #endif
      break;

    default:
      /* Do nothing */
      break;
    }

    /* state is set to IDLE upon Failure */
    Csm_GddActiveMacGenerateService.ucServiceState = CSM_MAC_GENERATE_IDLE;
    break;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveMacGenerateService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveMacGenerateService.pActiveServiceConfig->
      CallbackFct(ddResult);
  }
}

/*******************************************************************************
** Function Name        : Csm_MacGenerateServiceFinishNotification            **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function shall set the state of the MAC        **
**                        Generate service to "idle".                         **
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
** Remarks              : Global Variable(s): Csm_GddActiveMacGenerateService **
**                                                                            **
**                        Function(s) invoked: None                           **
*******************************************************************************/
void Csm_MacGenerateServiceFinishNotification(void)
{
  /* Setting the state to IDLE */
  Csm_GddActiveMacGenerateService.ucServiceState = CSM_MAC_GENERATE_IDLE;
}

boolean Csm_MacGenerateServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveMacGenerateService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    LblHasCallback = TRUE;
  }
  else
  {
    LblHasCallback = FALSE;
  }

  return LblHasCallback;
}
#endif /* (CSM_MAC_GENERATE_STATUS == STD_ON) */

#if (CSM_MAC_VERIFY_STATUS == STD_ON)
/*******************************************************************************
** Function Name        : Csm_MacVerifyStart                                  **
**                                                                            **
** Service ID           : 0x09                                                **
**                                                                            **
** Description          : This function initializes the MAC verify service of **
**                        CSM module. It will store the configuration         **
**                        information as identified by cfgId and will call the**
**                        corresponding Cry_<primitive>Start() provided the   **
**                        service state is not "active" and shall return the  **
**                        value returned by that function and set the service **
**                        state to "active"                                   **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, keyPtr                                       **
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
** Remarks              : Global Variable(s): Csm_GddActiveMacVerifyService   **
**                                            Csm_GaaMacVerifyConfigType      **
**                        Function(s) invoked : Cry_<Primitive>Start,         **
**                        Csm_FunctionPush, Det_ReportError                   **
*******************************************************************************/
Std_ReturnType Csm_MacVerifyStart(Csm_ConfigIdType cfgId,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  /* Checking for CSM initialization */
  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_MACVERIFYSTART_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Checking for Service Validation based on the configuration id  */
    if (cfgId >= Csm_GddMacVerifyCfgidLimit)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_MACVERIFYSTART_SID, CSM_E_PARAM_METHOD_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Verifying the NULL pointer */
    if (keyPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_MACVERIFYSTART_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "No Impact of this rule violation" */
    if (keyPtr->length == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_MACVERIFYSTART_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveMacVerifyService.ucServiceState
      & CSM_MAC_VERIFY_IDLE) != CSM_MAC_VERIFY_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* updating the state to service start */
    Csm_GddActiveMacVerifyService.ucServiceState = CSM_MAC_VERIFY_START;

    /* Fetching service configuration as updated during initial configuration */
    Csm_GddActiveMacVerifyService.pActiveServiceConfig =
      &Csm_GaaMacVerifyConfigType[cfgId];

    /* invoking primitive start function */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveMacVerifyService.
      pActiveServiceConfig->PrimitiveStartFct(
      (void*)Csm_GddActiveMacVerifyService.pActiveServiceConfig->
      PrimitiveConfigPtr, keyPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveMacVerifyService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Set the Service State to CSM_MAC_VERIFY_ACTIVE */
          Csm_GddActiveMacVerifyService.ucServiceState = CSM_MAC_VERIFY_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveMacVerifyService.ucServiceState = CSM_MAC_VERIFY_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveMacVerifyService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveMacVerifyService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_MacVerifyUpdate                                 **
**                                                                            **
** Service ID           : 0x0a                                                **
**                                                                            **
** Description          : This function provide the input data to the MAC     **
**                        verification service. It calls Cry_<Primitive>Update**
**                        of the primitive identified by the stored           **
**                        configuration information and return the value      **
**                        returned by that function                           **
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
** Preconditions        : CSM MAC interface should have been initialized      **
**                                                                            **
** Remarks              : Global Variable(s): Csm_GddActiveMacVerifyService   **
**                                                                            **
**                        Function(s) invoked : Cry_<Primitive>Update,        **
**                        Det_ReportError                                     **
*******************************************************************************/
Std_ReturnType Csm_MacVerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  /* Verifying the Null pointer */
  if (dataPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_MACVERIFYUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
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
        CSM_MACVERIFYUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveMacVerifyService.ucServiceState
      & CSM_MAC_VERIFY_START) == CSM_MAC_VERIFY_START)
      || ((Csm_GddActiveMacVerifyService.ucServiceState
      & CSM_MAC_VERIFY_UPDATE) == CSM_MAC_VERIFY_UPDATE)
      || ((Csm_GddActiveMacVerifyService.ucServiceState
      & CSM_MAC_VERIFY_FINISH) == CSM_MAC_VERIFY_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveMacVerifyService.ucServiceState
      & CSM_MAC_VERIFY_ACTIVE) != CSM_MAC_VERIFY_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_MACVERIFYUPDATE_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to UPDATE */
    Csm_GddActiveMacVerifyService.ucServiceState = CSM_MAC_VERIFY_UPDATE;

    /* Calling the primitive update function */
    /* polyspace-begin MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveMacVerifyService.pActiveServiceConfig->
      PrimitiveUpdateFct(cfgId, dataPtr, dataLength);
    /* polyspace-end MISRA-C3:18.1 RTE:IDP RTE:COR */

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveMacVerifyService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Set the Service State to CSM_MAC_VERIFY_ACTIVE */
          Csm_GddActiveMacVerifyService.ucServiceState = CSM_MAC_VERIFY_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveMacVerifyService.ucServiceState = CSM_MAC_VERIFY_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveMacVerifyService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveMacVerifyService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_MacVerifyFinish                                 **
**                                                                            **
** Service ID           : 0x0b                                                **
**                                                                            **
** Description          : This function will be used to finish the MAC verify **
**                        service by calling Cry_<Primitive>Finish as         **
**                        identified by the stored configuration information  **
**                        and returns the value returned by that function     **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, MacPtr, MacLength                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : resultPtr                                           **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        E_NOT_OK: service state is "idle"                   **
**                                                                            **
** Preconditions        : CSM MAC interface should have been initialized      **
**                                                                            **
** Remarks              : Global Variable(s): Csm_GddActiveMacVerifyService   **
**                                                                            **
**                        Function(s) invoked : Cry_<Primitive>Finish,        **
**                        Det_ReportError                                     **
*******************************************************************************/
Std_ReturnType Csm_MacVerifyFinish(Csm_ConfigIdType cfgId, const uint8* MacPtr,
  uint32 MacLength, Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  /* Verifying the Null pointer */
  if (MacPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_MACVERIFYFINISH_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    if (MacLength == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_MACVERIFYFINISH_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Verifying the Null pointer */
    if (resultPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_MACVERIFYFINISH_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveMacVerifyService.ucServiceState
      & CSM_MAC_VERIFY_START) == CSM_MAC_VERIFY_START)
      || ((Csm_GddActiveMacVerifyService.ucServiceState
      & CSM_MAC_VERIFY_UPDATE) == CSM_MAC_VERIFY_UPDATE)
      || ((Csm_GddActiveMacVerifyService.ucServiceState
      & CSM_MAC_VERIFY_FINISH) == CSM_MAC_VERIFY_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveMacVerifyService.ucServiceState & CSM_MAC_VERIFY_ACTIVE)
      != CSM_MAC_VERIFY_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_MACVERIFYFINISH_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to FINISH */
    Csm_GddActiveMacVerifyService.ucServiceState = CSM_MAC_VERIFY_FINISH;

    /* Calling the primitive finish function with Truncation allowed */
    /* polyspace-begin MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveMacVerifyService.pActiveServiceConfig->
      PrimitiveFinishFct(cfgId, MacPtr, MacLength, resultPtr);
    /* polyspace-end MISRA-C3:18.1 RTE:IDP RTE:COR */

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveMacVerifyService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveMacVerifyService.ucServiceState = CSM_MAC_VERIFY_IDLE;
      }
      else
      {
        if (Csm_GddActiveMacVerifyService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveMacVerifyService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_MacVerifyCallbackNotification                   **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in the configuration of the service MAC       **
**                        Verify with the argument given by "Result".         **
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
** Remarks              : Global Variable(s): Csm_GddActiveMacVerifyService   **
*******************************************************************************/
void Csm_MacVerifyCallbackNotification(Std_ReturnType ddResult)
{
  switch (ddResult)
  {
  case CSM_E_BUSY:
    /* Do nothing */
    break;

  case E_OK:
    switch (Csm_GddActiveMacVerifyService.ucServiceState)
    {
    case CSM_MAC_VERIFY_START:
    case CSM_MAC_VERIFY_UPDATE:
      /* State is set to ACTIVE upon success */
      Csm_GddActiveMacVerifyService.ucServiceState = CSM_MAC_VERIFY_ACTIVE;
      break;

    case CSM_MAC_VERIFY_FINISH:
      /* Setting the service state to idle irrespective of the result */
      Csm_GddActiveMacVerifyService.ucServiceState = CSM_MAC_VERIFY_IDLE;
      break;

    default:
      /* Do nothing */
      break;
    }
    break;

  default:
    /* state is set to IDLE upon failure */
    Csm_GddActiveMacVerifyService.ucServiceState = CSM_MAC_VERIFY_IDLE;
    break;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveMacVerifyService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveMacVerifyService.pActiveServiceConfig->CallbackFct(ddResult);
  }
}

/*******************************************************************************
** Function Name        : Csm_MacVerifyServiceFinishNotification              **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function shall set the state of the MAC        **
**                        Verify service to "idle".                           **
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
** Remarks              : Global Variable(s): Csm_GddActiveMacVerifyService   **
**                                                                            **
**                        Function(s) invoked: None                           **
*******************************************************************************/
void Csm_MacVerifyServiceFinishNotification(void)
{
  /* Setting the state to IDLE */
  Csm_GddActiveMacVerifyService.ucServiceState = CSM_MAC_VERIFY_IDLE;
}

boolean Csm_MacVerifyServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveMacVerifyService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    LblHasCallback = TRUE;
  }
  else
  {
    LblHasCallback = FALSE;
  }

  return LblHasCallback;
}
#endif /* (CSM_MAC_VERIFY_STATUS == STD_ON) */

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* ((CSM_MAC_GENERATE_STATUS == STD_ON) || (CSM_MAC_VERIFY_STATUS == STD_ON)) */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
