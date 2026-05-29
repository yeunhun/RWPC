/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Csm_SymKeyExtract.c                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CSM symmetric Key Extraction Interface      **
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

#if (CSM_SYM_KEY_EXTRACT_STATUS == STD_ON)
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveSymKeyExtractService Csm_GddActiveSymKeyExtractService;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Csm_SymKeyExtractStart                              **
**                                                                            **
** Service ID           : 0x32                                                **
**                                                                            **
** Description          : This function will initialize the symmetrical       **
**                        key extraction service of the CSM module.           **
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
**                                         Csm_GddActiveSymKeyExtractService  **
**                                         Csm_GaaSymKeyExtractConfigType     **
**                        Function(s) invoked: Cry_<Primitive>Start,          **
**                        Csm_FunctionPush                                    **
*******************************************************************************/
Std_ReturnType Csm_SymKeyExtractStart(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  /* Checking for CSM initialization */
  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_SYMKEYEXTRACTSTART_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Checking for Service Validation based on the configuration id  */
    if (cfgId >= CSM_SYM_KEY_EXTRACT_CFGID_LIMIT)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMKEYEXTRACTSTART_SID, CSM_E_PARAM_METHOD_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveSymKeyExtractService.ucServiceState
      & CSM_SYM_KEY_EXTRACT_IDLE) != CSM_SYM_KEY_EXTRACT_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    Csm_GddActiveSymKeyExtractService.ucServiceState =
      CSM_SYM_KEY_EXTRACT_START;

    /* Fetching service configuration as updated during initial configuration */
    Csm_GddActiveSymKeyExtractService.pActiveServiceConfig = \
      &Csm_GaaSymKeyExtractConfigType[cfgId];

    /*
     * invoking primitive start function
     * Will be using AES primitive for the Symmetrical Wrapping
     * InitVector is NULL and InitVectorLength is 0 as they will not be used
     */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveSymKeyExtractService.
      pActiveServiceConfig->PrimitiveStartFct(
      (void *)Csm_GddActiveSymKeyExtractService.
      pActiveServiceConfig->PrimitiveConfigPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveSymKeyExtractService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Setting the service state to active upon success */
          Csm_GddActiveSymKeyExtractService.ucServiceState =
            CSM_SYM_KEY_EXTRACT_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveSymKeyExtractService.ucServiceState =
            CSM_SYM_KEY_EXTRACT_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveSymKeyExtractService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveSymKeyExtractService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_SymKeyExtractUpdate                             **
**                                                                            **
** Service ID           : 0x33                                                **
**                                                                            **
** Description          : This function shall be used to feed the input data  **
**                        symmetrical key extraction service                  **
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
** Preconditions        : CSM Symmetrical Key Extraction interface should     **
**                        have been initialized                               **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                                          Csm_GddActiveSymKeyExtractService **
**                        Function(s) invoked : Cry_<Primitive>Update         **
*******************************************************************************/
Std_ReturnType Csm_SymKeyExtractUpdate(Csm_ConfigIdType cfgId,
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
      CSM_SYMKEYEXTRACTUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
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
        CSM_SYMKEYEXTRACTUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveSymKeyExtractService.ucServiceState
      & CSM_SYM_KEY_EXTRACT_START) == CSM_SYM_KEY_EXTRACT_START)
      || ((Csm_GddActiveSymKeyExtractService.ucServiceState
      & CSM_SYM_KEY_EXTRACT_UPDATE) == CSM_SYM_KEY_EXTRACT_UPDATE)
      || ((Csm_GddActiveSymKeyExtractService.ucServiceState
      & CSM_SYM_KEY_EXTRACT_FINISH) == CSM_SYM_KEY_EXTRACT_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveSymKeyExtractService.ucServiceState
      & CSM_SYM_KEY_EXTRACT_ACTIVE) != CSM_SYM_KEY_EXTRACT_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMKEYEXTRACTUPDATE_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to UPDATE */
    Csm_GddActiveSymKeyExtractService.ucServiceState =
      CSM_SYM_KEY_EXTRACT_UPDATE;

    /* Calling the primitive update function */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveSymKeyExtractService.
      pActiveServiceConfig->PrimitiveUpdateFct(cfgId, dataPtr, dataLength);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveSymKeyExtractService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Setting the service state to active upon success */
          Csm_GddActiveSymKeyExtractService.ucServiceState =
            CSM_SYM_KEY_EXTRACT_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveSymKeyExtractService.ucServiceState =
            CSM_SYM_KEY_EXTRACT_ACTIVE;
        }
      }
      else
      {
        if (Csm_GddActiveSymKeyExtractService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveSymKeyExtractService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_SymKeyExtractFinish                             **
**                                                                            **
** Service ID           : 0x34                                                **
**                                                                            **
** Description          : This function will be used to finish the            **
**                        symmetrical key extraction service.                 **
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
** Preconditions        : CSM Symmetrical Key Extraction interface should     **
**                        have been initialized                               **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                                          Csm_GddActiveSymKeyExtractService **
**                        Function(s) invoked: Cry_<Primitive>Finish          **
*******************************************************************************/
Std_ReturnType Csm_SymKeyExtractFinish(Csm_ConfigIdType cfgId,
  Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  /* Verifying the Null pointer */
  if (keyPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_SYMKEYEXTRACTFINISH_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveSymKeyExtractService.ucServiceState
      & CSM_SYM_KEY_EXTRACT_START) == CSM_SYM_KEY_EXTRACT_START)
      || ((Csm_GddActiveSymKeyExtractService.ucServiceState
      & CSM_SYM_KEY_EXTRACT_UPDATE) == CSM_SYM_KEY_EXTRACT_UPDATE)
      || ((Csm_GddActiveSymKeyExtractService.ucServiceState
      & CSM_SYM_KEY_EXTRACT_FINISH) == CSM_SYM_KEY_EXTRACT_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveSymKeyExtractService.ucServiceState
      & CSM_SYM_KEY_EXTRACT_ACTIVE) != CSM_SYM_KEY_EXTRACT_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMKEYEXTRACTFINISH_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to FINISH */
    Csm_GddActiveSymKeyExtractService.ucServiceState =
      CSM_SYM_KEY_EXTRACT_FINISH;

    /* Calling the primitive finish function */
    /* polyspace-begin MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveSymKeyExtractService.pActiveServiceConfig->
      PrimitiveFinishFct(cfgId, keyPtr);
    /* polyspace-end MISRA-C3:18.1 RTE:IDP RTE:COR */

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveSymKeyExtractService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveSymKeyExtractService.ucServiceState
          = CSM_SYM_KEY_EXTRACT_IDLE;
      }
      else
      {
        if (Csm_GddActiveSymKeyExtractService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveSymKeyExtractService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_SymKeyExtractCallbackNotification               **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in the configuration of Symmetrical Key       **
**                        Extract service with argument given by "Result".    **
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
**                        Csm_GddActiveSymKeyExtractService                   **
*******************************************************************************/
void Csm_SymKeyExtractCallbackNotification(Std_ReturnType ddResult)
{
  switch (ddResult)
  {
  case CSM_E_BUSY:
    /* Do nothing */
    break;

  case E_OK:
    switch (Csm_GddActiveSymKeyExtractService.ucServiceState)
    {
    case CSM_SYM_KEY_EXTRACT_START:
    case CSM_SYM_KEY_EXTRACT_UPDATE:
      /* State is set to ACTIVE upon success */
      Csm_GddActiveSymKeyExtractService.ucServiceState
        = CSM_SYM_KEY_EXTRACT_ACTIVE;
      break;

    case CSM_SYM_KEY_EXTRACT_FINISH:
      /* Setting the service state to idle irrespective of the result */
      Csm_GddActiveSymKeyExtractService.ucServiceState
        = CSM_SYM_KEY_EXTRACT_IDLE;
      break;

    default:
      /* Do nothing */
      break;
    }
    break;

  default:
    switch (Csm_GddActiveSymKeyExtractService.ucServiceState)
    {
    case CSM_SYM_KEY_EXTRACT_START:
    case CSM_SYM_KEY_EXTRACT_UPDATE:
    case CSM_SYM_KEY_EXTRACT_FINISH:
      break;

    default:
      /* Do nothing */
      break;
    }

    /* state is set to IDLE upon Failure */
    Csm_GddActiveSymKeyExtractService.ucServiceState
      = CSM_SYM_KEY_EXTRACT_IDLE;
    break;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveSymKeyExtractService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveSymKeyExtractService.pActiveServiceConfig->CallbackFct(ddResult);
  }
}

/*******************************************************************************
** Function Name        : Csm_SymKeyExtractServiceFinishNotification          **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function shall set the state of the Symmetrical**
**                        Key Extractaction service to "idle".                **
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
**                                   Csm_GddActiveSymKeyExtractService        **
**                        Function(s) invoked: None                           **
*******************************************************************************/
void Csm_SymKeyExtractServiceFinishNotification(void)
{
  /* Setting the state to IDLE */
  Csm_GddActiveSymKeyExtractService.ucServiceState = CSM_SYM_KEY_EXTRACT_IDLE;
}

boolean Csm_SymKeyExtractServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveSymKeyExtractService.pActiveServiceConfig->
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

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_SYM_KEY_EXTRACT_STATUS == STD_ON) */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
