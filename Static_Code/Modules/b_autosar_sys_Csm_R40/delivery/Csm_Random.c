/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Csm_Random.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of Random Interface                            **
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
** 2.6.1.0   08-Oct-2020   JaeHyun      Redmine #25964                        **
** 1.2.5     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.2.4     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.2.3     09-Aug-2018   Sinil        Redmine #13650                        **
** 1.2.2     19-Mar-2018   Sinil        Redmine #11930                        **
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
/* polyspace-begin MISRA2012:2.1,14.3 [Justified:Low] "No Impact of this rule violation" */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm.h"                  /* Header file for function prototypes */
#include "Rte_Csm.h"
#if (CSM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                  /* Header file for DET */
#endif

#if ((CSM_RANDOM_SEED_STATUS == STD_ON) || (CSM_RANDOM_GENERATE_STATUS == STD_ON))
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (CSM_RANDOM_SEED_STATUS == STD_ON)
/* Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveRandomSeedService Csm_GddActiveRandomSeedService;
#endif /* (CSM_RANDOM_SEED_STATUS == STD_ON) */

#if (CSM_RANDOM_GENERATE_STATUS == STD_ON)
/* Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveRandomGenerateService Csm_GddActiveRandomGenerateService;
#endif /* (CSM_RANDOM_SEED_STATUS == STD_ON) */

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
#if (CSM_RANDOM_SEED_STATUS == STD_ON)
/*******************************************************************************
** Function Name        : Csm_RandomSeedStart                                 **
**                                                                            **
** Service ID           : 0x0c                                                **
**                                                                            **
** Description          : This function initializes the Random Seed service   **
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
** Remarks              : Global Variable(s): Csm_GddActiveRandomSeedService, **
**                                            Csm_GaaRandomSeedConfigType     **
**                        Function(s) invoked : Cry_<Primitive>Start,         **
**                        Csm_FunctionPush, Det_ReportError                   **
*******************************************************************************/
Std_ReturnType Csm_RandomSeedStart(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  /* Checking for CSM initialization */
  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_RANDOMSEEDSTART_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Checking for Service Validation based on the configuration id  */
    if (cfgId >= Csm_GddRandomSeedCfgidLimit)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_RANDOMSEEDSTART_SID, CSM_E_PARAM_METHOD_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveRandomSeedService.ucServiceState & CSM_RANDOM_SEED_IDLE)
      != CSM_RANDOM_SEED_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* updating the state to service start */
    Csm_GddActiveRandomSeedService.ucServiceState = CSM_RANDOM_SEED_START;

    /* Fetching service configuration as updated during initial configuration */
    Csm_GddActiveRandomSeedService.pActiveServiceConfig =
      &Csm_GaaRandomSeedConfigType[cfgId];
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveRandomSeedService.pActiveServiceConfig->
      PrimitiveStartFct((void*)Csm_GddActiveRandomSeedService.
      pActiveServiceConfig->PrimitiveConfigPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveRandomSeedService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Setting the service state to active upon success */
          Csm_GddActiveRandomSeedService.ucServiceState = CSM_RANDOM_SEED_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveRandomSeedService.ucServiceState = CSM_RANDOM_SEED_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveRandomSeedService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveRandomSeedService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_RandomSeedUpdate                                **
**                                                                            **
** Service ID           : 0x0d                                                **
**                                                                            **
** Description          : This function provide the input data to the Random  **
**                        Seed service. It calls Cry_<Primitive>Update of the **
**                        primitive identified by the stored configuration    **
**                        information and return the value returned by that   **
**                        function                                            **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, seedPtr, seedLength                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        E_NOT_OK: service state is "idle"                   **
** Preconditions        : CSM Random interface should have been initialized   **
**                                                                            **
** Remarks              : Global Variable(s): Csm_GddActiveRandomSeedService  **
**                                                                            **
**                        Function(s) invoked : Cry_<Primitive>Update,        **
**                                              Det_ReportError               **
*******************************************************************************/
Std_ReturnType Csm_RandomSeedUpdate(Csm_ConfigIdType cfgId,
  const uint8* seedPtr, uint32 seedLength)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  /* Verifying the Null pointer */
  if (seedPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_RANDOMSEEDUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    if (seedLength == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_RANDOMSEEDUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveRandomSeedService.ucServiceState & CSM_RANDOM_SEED_START)
      == CSM_RANDOM_SEED_START)
      || ((Csm_GddActiveRandomSeedService.ucServiceState & CSM_RANDOM_SEED_UPDATE)
      == CSM_RANDOM_SEED_UPDATE)
      || ((Csm_GddActiveRandomSeedService.ucServiceState & CSM_RANDOM_SEED_FINISH)
      == CSM_RANDOM_SEED_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveRandomSeedService.ucServiceState & CSM_RANDOM_SEED_ACTIVE)
      != CSM_RANDOM_SEED_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_RANDOMSEEDUPDATE_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to UPDATE */
    Csm_GddActiveRandomSeedService.ucServiceState = CSM_RANDOM_SEED_UPDATE;

    /* Calling the primitive update function */
    /* polyspace-begin MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveRandomSeedService.pActiveServiceConfig->
      PrimitiveUpdateFct(cfgId, seedPtr, seedLength);
    /* polyspace-end MISRA-C3:18.1 RTE:IDP RTE:COR */

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveRandomSeedService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Setting the service state to active upon success */
          Csm_GddActiveRandomSeedService.ucServiceState = CSM_RANDOM_SEED_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveRandomSeedService.ucServiceState = CSM_RANDOM_SEED_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveRandomSeedService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveRandomSeedService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_RandomSeedFinish                                **
**                                                                            **
** Service ID           : 0x0e                                                **
**                                                                            **
** Description          : This function will not be doing any computation.    **
**                        The actual computation will be done in              **
**                        Csm_Randomgenerate()                                **
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
** Preconditions        : CSM Random Seed update should have been             **
**                        successfuly completed                               **
**                                                                            **
** Remarks              : Global Variable(s): Csm_GddActiveRandomSeedService  **
**                                                                            **
**                        Function(s) invoked : Cry_<Primitive>Finish,        **
**                                              Det_ReportError               **
*******************************************************************************/
Std_ReturnType Csm_RandomSeedFinish(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  /* Checking whether the service is initialized or not */
  if (((Csm_GddActiveRandomSeedService.ucServiceState
    & CSM_RANDOM_SEED_START) == CSM_RANDOM_SEED_START)
    || ((Csm_GddActiveRandomSeedService.ucServiceState
    & CSM_RANDOM_SEED_UPDATE) == CSM_RANDOM_SEED_UPDATE)
    || ((Csm_GddActiveRandomSeedService.ucServiceState
    & CSM_RANDOM_SEED_FINISH) == CSM_RANDOM_SEED_FINISH))
  {
    LddReturnValue = CSM_E_BUSY;
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveRandomSeedService.ucServiceState
      & CSM_RANDOM_SEED_ACTIVE) != CSM_RANDOM_SEED_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_RANDOMSEEDFINISH_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to FINISH */
    Csm_GddActiveRandomSeedService.ucServiceState = CSM_RANDOM_SEED_FINISH;

    /* Calling the primitive finish function */
    /* polyspace-begin MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveRandomSeedService.pActiveServiceConfig->
      PrimitiveFinishFct(cfgId);
    /* polyspace-end MISRA-C3:18.1 RTE:IDP RTE:COR */

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveRandomSeedService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveRandomSeedService.ucServiceState = CSM_RANDOM_SEED_IDLE;
      }
      else
      {
        if (Csm_GddActiveRandomSeedService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveRandomSeedService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_RandomSeedCallbackNotification                  **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in the configuration of the service Random    **
**                        Seed with the argument given by "Result".           **
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
** Remarks              : Global Variable(s): Csm_GddActiveRandomSeedService  **
*******************************************************************************/
void Csm_RandomSeedCallbackNotification(Std_ReturnType ddResult)
{
  if (ddResult == E_OK)
  {
    switch (Csm_GddActiveRandomSeedService.ucServiceState)
    {
    case CSM_RANDOM_SEED_START:
    case CSM_RANDOM_SEED_UPDATE:
      /* State is set to ACTIVE upon success */
      Csm_GddActiveRandomSeedService.ucServiceState = CSM_RANDOM_SEED_ACTIVE;
      break;

    case CSM_RANDOM_SEED_FINISH:
      /* Setting the service state to idle irrespective of the result */
      Csm_GddActiveRandomSeedService.ucServiceState = CSM_RANDOM_SEED_IDLE;
      break;

    default:
      /* Do nothing */
      break;
    }
  }
  else
  {
    switch (Csm_GddActiveRandomSeedService.ucServiceState)
    {
    case CSM_RANDOM_SEED_START:
    case CSM_RANDOM_SEED_UPDATE:
    case CSM_RANDOM_SEED_FINISH:
      break;

    default:
      /* Do nothing */
      break;
    }

    /* state is set to IDLE upon Failure */
    Csm_GddActiveRandomSeedService.ucServiceState = CSM_RANDOM_SEED_IDLE;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveRandomSeedService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveRandomSeedService.pActiveServiceConfig->CallbackFct(ddResult);
  }
}

/*******************************************************************************
** Function Name        : Csm_RandomSeedServiceFinishNotification             **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function shall set the state of the Random     **
**                        Seed service to "idle".                             **
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
** Remarks              : Global Variable(s): Csm_GddActiveRandomSeedService  **
**                                                                            **
**                        Function(s) invoked: None                           **
*******************************************************************************/
void Csm_RandomSeedServiceFinishNotification(void)
{
  /* Setting the state to IDLE */
  Csm_GddActiveRandomSeedService.ucServiceState = CSM_RANDOM_SEED_IDLE;
}

boolean Csm_RandomSeedServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveRandomSeedService.pActiveServiceConfig->CallbackFct
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
#endif /* (CSM_RANDOM_SEED_STATUS == STD_ON) */

#if (CSM_RANDOM_GENERATE_STATUS == STD_ON)
/*******************************************************************************
** Function Name        : Csm_RandomGenerate                                  **
**                                                                            **
** Service ID           : 0x0f                                                **
**                                                                            **
** Description          : This function start the random number generation    **
**                        service of the CSM module. It will store the        **
**                        configuration information as identified by cfgId and**
**                        will call the corresponding Cry_<primitive>()       **
**                        provided the service state is not "active" and      **
**                        shall return the value returned by that function    **
**                        and set the service state to "active"               **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, resultLength                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : resultPtr                                           **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy   **
**                        of random number generator is exhausted             **
**                        CSM_E_BUSY: service state is already "active"       **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        Csm_GddActiveRandomGenerateService,                 **
**                        Csm_GaaRandomGenerateConfigType                     **
**                        Function(s) invoked : Cry_<Primitive>,              **
**                        Csm_FunctionPush, Det_ReportError                   **
*******************************************************************************/
Std_ReturnType Csm_RandomGenerate(Csm_ConfigIdType cfgId, uint8* resultPtr,
  uint32 resultLength)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  /* Checking for CSM initialization */
  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_RANDOMGENERATE_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  /* Verifying the Null pointer */
  if (resultPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_RANDOMGENERATE_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    if (resultLength == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_RANDOMGENERATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveRandomGenerateService.ucServiceState & CSM_RANDOM_GENERATE_IDLE)
      != CSM_RANDOM_GENERATE_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* updating the state to service start */
    Csm_GddActiveRandomGenerateService.ucServiceState =
      CSM_RANDOM_GENERATE_ACTIVE;

    /* Fetching service configuration as updated during initial configuration */
    Csm_GddActiveRandomGenerateService.pActiveServiceConfig =
      &Csm_GaaRandomGenerateConfigType[cfgId];

    /* invoking primitive function */
    /* polyspace +4 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    /* polyspace +6 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +6 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    LddReturnValue = Csm_GddActiveRandomGenerateService.
      pActiveServiceConfig->PrimitiveFct(
      (void*)Csm_GddActiveRandomGenerateService.
      pActiveServiceConfig->PrimitiveConfigPtr, resultPtr, resultLength);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveRandomGenerateService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        #if (CSM_DEV_ERROR_DETECT == STD_ON)
        if (LddReturnValue == CSM_E_SMALL_BUFFER)
        {
          (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
            CSM_RANDOMGENERATE_SID, CSM_E_BUFFER_TOO_SMALL);
        }
        #endif

        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveRandomGenerateService.ucServiceState =
          CSM_RANDOM_GENERATE_IDLE;
      }
      else
      {
        if (Csm_GddActiveRandomGenerateService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveRandomGenerateService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_RandomGenerateCallbackNotification              **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in the configuration of the service Random    **
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
** Remarks              : Global Variable(s):                                 **
**                        Csm_GddActiveRandomGenerateService                  **
*******************************************************************************/
void Csm_RandomGenerateCallbackNotification(Std_ReturnType ddResult)
{
  switch (ddResult)
  {
  case CSM_E_BUSY:
    /* Do nothing. Previous request result will be returned */
    break;

  case CSM_E_SMALL_BUFFER:
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_RANDOMGENERATE_SID, CSM_E_BUFFER_TOO_SMALL);
    #endif

    /* Setting the service state to idle irrespective of the result */
    Csm_GddActiveRandomGenerateService.ucServiceState =
      CSM_RANDOM_GENERATE_IDLE;
    break;

  default:
    /* Setting the service state to idle irrespective of the result */
    Csm_GddActiveRandomGenerateService.ucServiceState =
      CSM_RANDOM_GENERATE_IDLE;
    break;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveRandomGenerateService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveRandomGenerateService.pActiveServiceConfig->CallbackFct(ddResult);
  }
}

boolean Csm_RandomGenerateServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveRandomGenerateService.pActiveServiceConfig->CallbackFct
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
#endif /* (CSM_RANDOM_GENERATE_STATUS == STD_ON) */

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* ((CSM_RANDOM_SEED_STATUS == STD_ON) || (CSM_RANDOM_GENERATE_STATUS == STD_ON)) */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:2.1,14.3 [Justified:Low] "No Impact of this rule violation" */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
