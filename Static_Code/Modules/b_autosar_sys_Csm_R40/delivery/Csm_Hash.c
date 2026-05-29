/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Csm_Hash.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of Hash Interface                              **
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

#if (CSM_HASH_STATUS == STD_ON)
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveHashService Csm_GddActiveHashService;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Csm_HashStart                                       **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This function initializes the hash service of CSM   **
**                        module. It will store the configuration information **
**                        as identified by cfgId and will call the            **
**                        corresponding Cry_<primitive>Start() provided the   **
**                        service state is not "active" and shall return the  **
**                        value returned by that function and set the service **
**                        state to "active"                                   **
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
** Remarks              : Global Variable(s)  : Csm_GddActiveHashService,     **
**                                              Csm_GaaHashConfigType         **
**                        Function(s) invoked : Cry_<Primitive>Start,         **
**                                              Csm_FunctionPush,             **
**                                              Det_ReportError               **
*******************************************************************************/
Std_ReturnType Csm_HashStart(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Initializing the variable with E_OK */
  LddReturnValue = E_OK;

  /* Checking for CSM initialization */
  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_HASHSTART_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Checking for Service Validation based on the configuration id  */
    if (cfgId >= Csm_GddHashCfgidLimit)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_HASHSTART_SID, CSM_E_PARAM_METHOD_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveHashService.ucServiceState & CSM_HASH_IDLE)
      != CSM_HASH_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* updating the state to service start */
    Csm_GddActiveHashService.ucServiceState = CSM_HASH_START;

    /* Fetching service configuration as updated during initial configuration */
    Csm_GddActiveHashService.pActiveServiceConfig =
      &Csm_GaaHashConfigType[cfgId];

    /* invoking primitive start function */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveHashService.pActiveServiceConfig->
      PrimitiveStartFct((void*)Csm_GddActiveHashService.
      pActiveServiceConfig->PrimitiveConfigPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveHashService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Setting the service state to active upon success */
          Csm_GddActiveHashService.ucServiceState = CSM_HASH_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveHashService.ucServiceState = CSM_HASH_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveHashService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveHashService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_HashUpdate                                      **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : This function provide the input data to the hash    **
**                        service. It calls Cry_<Primitive>Update of the      **
**                        primitive identified by the stored configuration    **
**                        information and return the value returned by that   **
**                        function                                            **
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
** Preconditions        : CSM Hash interface should have been initialized     **
**                                                                            **
** Remarks              : Global Variable(s)  : Csm_GddActiveHashService,     **
**                                                                            **
**                        Function(s) invoked : Cry_<Primitive>Update,        **
**                                              Det_ReportError               **
*******************************************************************************/
Std_ReturnType Csm_HashUpdate(Csm_ConfigIdType cfgId, const uint8* dataPtr,
  uint32 dataLength)
{
  Std_ReturnType LddReturnValue;

  /* Initializing the variable with E_OK */
  LddReturnValue = E_OK;

  /* Verifying the Null pointer */
  if (dataPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_HASHUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
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
        CSM_HASHUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveHashService.ucServiceState & CSM_HASH_START)
      == CSM_HASH_START)
      || ((Csm_GddActiveHashService.ucServiceState & CSM_HASH_UPDATE)
      == CSM_HASH_UPDATE)
      || ((Csm_GddActiveHashService.ucServiceState & CSM_HASH_FINISH)
      == CSM_HASH_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveHashService.ucServiceState & CSM_HASH_ACTIVE)
      != CSM_HASH_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_HASHUPDATE_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to UPDATE */
    Csm_GddActiveHashService.ucServiceState = CSM_HASH_UPDATE;

    /* Calling the primitive update function */
    /* polyspace-begin MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveHashService.pActiveServiceConfig->
      PrimitiveUpdateFct(cfgId, dataPtr, dataLength);
    /* polyspace-end MISRA-C3:18.1 RTE:IDP RTE:COR */

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveHashService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Setting the service state to active upon success */
          Csm_GddActiveHashService.ucServiceState = CSM_HASH_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveHashService.ucServiceState = CSM_HASH_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveHashService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveHashService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_HashFinish                                      **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : This function will be used to finish the hash       **
**                        service by calling Cry_<Primitive>Finish as         **
**                        identified by the stored configuration information  **
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
** Preconditions        : CSM Hash interface should have been initialized     **
**                                                                            **
** Remarks              : Global Variable(s)  : Csm_GddActiveHashService      **
**                                                                            **
**                        Function(s) invoked : Cry_<Primitive>Finish,        **
**                                              Det_ReportError,              **
**                                              Csm_HashFinishDet             **
*******************************************************************************/
Std_ReturnType Csm_HashFinish(Csm_ConfigIdType cfgId, uint8* resultPtr,
  uint32* resultLengthPtr, boolean TruncationIsAllowed)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  /* Verifying the Null pointer */
  if (resultPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_HASHFINISH_SID, CSM_E_PARAM_PTR_INVALID);
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
        CSM_HASHFINISH_SID, CSM_E_PARAM_PTR_INVALID);
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
        CSM_HASHFINISH_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveHashService.ucServiceState & CSM_HASH_START)
      == CSM_HASH_START)
      || ((Csm_GddActiveHashService.ucServiceState & CSM_HASH_UPDATE)
      == CSM_HASH_UPDATE)
      || ((Csm_GddActiveHashService.ucServiceState & CSM_HASH_FINISH)
      == CSM_HASH_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveHashService.ucServiceState & CSM_HASH_ACTIVE)
      != CSM_HASH_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_HASHFINISH_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to FINISH */
    Csm_GddActiveHashService.ucServiceState = CSM_HASH_FINISH;

    /* Calling the primitive finish function */
    /* polyspace-begin MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveHashService.pActiveServiceConfig->
      PrimitiveFinishFct(cfgId, resultPtr, resultLengthPtr,
      TruncationIsAllowed);
    /* polyspace-end MISRA-C3:18.1 RTE:IDP RTE:COR */

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveHashService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        #if (CSM_DEV_ERROR_DETECT == STD_ON)
        if (LddReturnValue == CSM_E_SMALL_BUFFER)
        {
          (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
            CSM_HASHFINISH_SID, CSM_E_BUFFER_TOO_SMALL);
        }
        #endif

        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveHashService.ucServiceState = CSM_HASH_IDLE;
      }
      else
      {
        if (Csm_GddActiveHashService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveHashService.
            pActiveServiceConfig->PrimitiveMainFct);
        }

}
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_HashCallbackNotification                        **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in the configuration of the service           **
**                        Hash with the argument given by "Result".           **
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
** Remarks              : Global Variable(s): Csm_GddActiveHashService        **
**                                                                            **
**                        Function(s) invoked: Det_ReportError                **
*******************************************************************************/
void Csm_HashCallbackNotification(Std_ReturnType ddResult)
{
  switch (ddResult)
  {
  case CSM_E_BUSY:
    /* Do nothing */
    break;

  case E_OK:
    switch (Csm_GddActiveHashService.ucServiceState)
    {
    case CSM_HASH_START:
    case CSM_HASH_UPDATE:
      /* State is set to ACTIVE upon success */
      Csm_GddActiveHashService.ucServiceState = CSM_HASH_ACTIVE;
      break;

    case CSM_HASH_FINISH:
      /* Setting the service state to idle irrespective of the result */
      Csm_GddActiveHashService.ucServiceState = CSM_HASH_IDLE;
      break;

    default:
      /* Do nothing */
      break;
    }
    break;

  default:
    switch (Csm_GddActiveHashService.ucServiceState)
    {
    case CSM_HASH_START:
    case CSM_HASH_UPDATE:
      break;

    case CSM_HASH_FINISH:
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      if (ddResult == CSM_E_SMALL_BUFFER)
      {
        (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
          CSM_HASHFINISH_SID, CSM_E_BUFFER_TOO_SMALL);
      }
      #endif
      break;

    default:
      /* Do nothing */
      break;
    }

    /* state is set to IDLE upon Failure */
    Csm_GddActiveHashService.ucServiceState = CSM_HASH_IDLE;
    break;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveHashService.pActiveServiceConfig->CallbackFct != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveHashService.pActiveServiceConfig->CallbackFct(ddResult);
  }
}

/*******************************************************************************
** Function Name        : Csm_HashServiceFinishNotification                   **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function shall set the state of the hash       **
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
** Remarks              : Global Variable(s): Csm_GddActiveHashService        **
**                                                                            **
**                        Function(s) invoked: None                           **
*******************************************************************************/
void Csm_HashServiceFinishNotification(void)
{
  /* Setting the state to IDLE */
  Csm_GddActiveHashService.ucServiceState = CSM_HASH_IDLE;
}

boolean Csm_HashServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveHashService.pActiveServiceConfig->CallbackFct != NULL_PTR)
  {
    LblHasCallback = TRUE;
  }
  else
  {
    LblHasCallback = FALSE;
  }

  return LblHasCallback;
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_HASH_STATUS == STD_ON) */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:2.1,14.3 [Justified:Low] "No Impact of this rule violation" */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
