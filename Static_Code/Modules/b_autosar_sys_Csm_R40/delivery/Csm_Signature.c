/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Csm_Signature.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of Signature Interface                         **
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
** 1.0.7     09-Aug-2016   Sinil        Redmine #5693, #5694, #5760           **
** 1.0.6     12-Jul-2016   Sinil        Redmine #5514                         **
** 1.0.5     13-Jun-2016   Sinil        Redmine #4900                         **
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

#if ((CSM_SIGNATURE_GENERATE_STATUS == STD_ON) || (CSM_SIGNATURE_VERIFY_STATUS == STD_ON))
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (CSM_SIGNATURE_GENERATE_STATUS == STD_ON)
/* Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveSignatureGenerateService Csm_GddActiveSignatureGenerateService;
#endif /* (CSM_SIGNATURE_GENERATE_STATUS == STD_ON) */

#if (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)
/* Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveSignatureVerifyService Csm_GddActiveSignatureVerifyService;
#endif /* (CSM_SIGNATURE_VERIFY_STATUS == STD_ON) */

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
#if (CSM_SIGNATURE_GENERATE_STATUS == STD_ON)
/*******************************************************************************
** Function Name        : Csm_SignatureGenerateStart                          **
**                                                                            **
** Service ID           : 0x22                                                **
**                                                                            **
** Description          : This function initializes the signature generation  **
**                        service of CSM module.                              **
**                        It will store the configuration information as      **
**                        identified by cfgId and will call the corresponding **
**                        Cry_<primitive>Start() provided the service state is**
**                        not "active" and shall return the value returned by **
**                        that function and set the service state to "active".**
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
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        Csm_GddActiveSignatureGenerateService               **
**                        Csm_GaaSignatureGenerateConfigType                  **
**                                                                            **
**                        Function(s) invoked : Cry_<Primitive>Start,         **
**                        Csm_FunctionPush, Det_ReportError                   **
*******************************************************************************/
Std_ReturnType Csm_SignatureGenerateStart(Csm_ConfigIdType cfgId,
  const Csm_AsymPrivateKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_SIGNATUREGENERATESTART_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if Invalid cryptographic method is invoked for selected service */
    if (cfgId >= Csm_GddSignatureGenerateCfgidLimit)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SIGNATUREGENERATESTART_SID, CSM_E_PARAM_METHOD_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the keyPtr is NULL_PTR */
    if (keyPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SIGNATUREGENERATESTART_SID, CSM_E_PARAM_PTR_INVALID);
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
        CSM_SIGNATUREGENERATESTART_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveSignatureGenerateService.ucServiceState
      & CSM_SIGNATURE_GENERATE_IDLE) != CSM_SIGNATURE_GENERATE_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Set the Service state to CSM_SIGNATURE_GENERATE_START */
    Csm_GddActiveSignatureGenerateService.ucServiceState =
      CSM_SIGNATURE_GENERATE_START;

    /* Assign appropriate config address to the Active Service pointer */
    Csm_GddActiveSignatureGenerateService.pActiveServiceConfig =
      &Csm_GaaSignatureGenerateConfigType[cfgId];

    /*
     * Invoke respective primitive start function
     * argument will be provided by the Signatureal Block configuration
     */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveSignatureGenerateService.
      pActiveServiceConfig->PrimitiveStartFct(
      (void*)Csm_GddActiveSignatureGenerateService.pActiveServiceConfig->
      PrimitiveConfigPtr, keyPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveSignatureGenerateService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Set the Service State to CSM_SIGNATURE_GENERATE_ACTIVE */
          Csm_GddActiveSignatureGenerateService.ucServiceState
            = CSM_SIGNATURE_GENERATE_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveSignatureGenerateService.ucServiceState
            = CSM_SIGNATURE_GENERATE_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveSignatureGenerateService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveSignatureGenerateService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_SignatureGenerateUpdate                         **
**                                                                            **
** Service ID           : 0x23                                                **
**                                                                            **
** Description          : This function is used to feed the symmetrical block **
**                        encryption service with the input data. It calls    **
**                        Cry_<Primitive>Update of the primitive identified   **
**                        by the stored configuration information and return  **
**                        the value returned by that function.                **
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
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        Csm_GddActiveSignatureGenerateService               **
**                                                                            **
**                        Function(s) invoked : Cry_<Primitive>Update,        **
**                        Det_ReportError                                     **
*******************************************************************************/
Std_ReturnType Csm_SignatureGenerateUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if the input pointer is NULL */
  if (dataPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_SIGNATUREGENERATEUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
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
        CSM_SIGNATUREGENERATEUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveSignatureGenerateService.ucServiceState
      & CSM_SIGNATURE_GENERATE_START) == CSM_SIGNATURE_GENERATE_START)
      || ((Csm_GddActiveSignatureGenerateService.ucServiceState
      & CSM_SIGNATURE_GENERATE_UPDATE) == CSM_SIGNATURE_GENERATE_UPDATE)
      || ((Csm_GddActiveSignatureGenerateService.ucServiceState
      & CSM_SIGNATURE_GENERATE_FINISH) == CSM_SIGNATURE_GENERATE_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveSignatureGenerateService.ucServiceState
      & CSM_SIGNATURE_GENERATE_ACTIVE) != CSM_SIGNATURE_GENERATE_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SIGNATUREGENERATEUPDATE_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to UPDATE */
    Csm_GddActiveSignatureGenerateService.ucServiceState =
      CSM_SIGNATURE_GENERATE_UPDATE;

    /* Invoke respective primitive Update function */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveSignatureGenerateService.
      pActiveServiceConfig->PrimitiveUpdateFct(cfgId, dataPtr, dataLength);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveSignatureGenerateService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Set the Service State to CSM_SIGNATURE_GENERATE_ACTIVE */
          Csm_GddActiveSignatureGenerateService.ucServiceState =
            CSM_SIGNATURE_GENERATE_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveSignatureGenerateService.ucServiceState
            = CSM_SIGNATURE_GENERATE_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveSignatureGenerateService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveSignatureGenerateService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_SignatureGenerateFinish                         **
**                                                                            **
** Service ID           : 0x24                                                **
**                                                                            **
** Description          : This function used to finish the signature          **
**                        generation service. Signatures are generated by     **
**                        calling Cry_<Primitive>Finish as identified by      **
**                        stored configuration information and returns the    **
**                        value returned by that function.                    **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId                                               **
**                                                                            **
** InOut parameter      : resultLengthPtr                                     **
**                                                                            **
** Output Parameters    : resultPtr                                           **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        E_NOT_OK: service state is "idle"                   **
**                        CSM_E_SMALL_BUFFER: provided buffer is too small to **
**                                            store the result                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        Csm_GddActiveSignatureGenerateService               **
**                                                                            **
**                        Function(s) invoked : Cry_<Primitive>Finish,        **
**                        Det_ReportError, Det_ReportError                    **
*******************************************************************************/
Std_ReturnType Csm_SignatureGenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if the result pointer is NULL */
  if (resultPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_SIGNATUREGENERATEFINISH_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the result length pointer is NULL */
    if (resultLengthPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SIGNATUREGENERATEFINISH_SID, CSM_E_PARAM_PTR_INVALID);
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
        CSM_SIGNATUREGENERATEFINISH_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveSignatureGenerateService.ucServiceState
      & CSM_SIGNATURE_GENERATE_START) == CSM_SIGNATURE_GENERATE_START)
      || ((Csm_GddActiveSignatureGenerateService.ucServiceState
      & CSM_SIGNATURE_GENERATE_UPDATE) == CSM_SIGNATURE_GENERATE_UPDATE)
      || ((Csm_GddActiveSignatureGenerateService.ucServiceState
      & CSM_SIGNATURE_GENERATE_FINISH) == CSM_SIGNATURE_GENERATE_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveSignatureGenerateService.ucServiceState
      & CSM_SIGNATURE_GENERATE_ACTIVE) != CSM_SIGNATURE_GENERATE_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SIGNATUREGENERATEFINISH_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to FINISH */
    Csm_GddActiveSignatureGenerateService.ucServiceState =
      CSM_SIGNATURE_GENERATE_FINISH;

    /* Invoke respective primitive Finish function */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveSignatureGenerateService.
      pActiveServiceConfig->PrimitiveFinishFct(cfgId, resultPtr,
      resultLengthPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveSignatureGenerateService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        #if (CSM_DEV_ERROR_DETECT == STD_ON)
        if (LddReturnValue == CSM_E_SMALL_BUFFER)
        {
          (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
            CSM_SIGNATUREGENERATEFINISH_SID, CSM_E_BUFFER_TOO_SMALL);
        }
        #endif

        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveSignatureGenerateService.ucServiceState
          = CSM_SIGNATURE_GENERATE_IDLE;
      }
      else
      {
        if (Csm_GddActiveSignatureGenerateService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveSignatureGenerateService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_SignatureGenerateCallbackNotification           **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in the configuration of Signature Generate    **
**                        service with the argument given by "Result".        **
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
**                        Csm_GddActiveSignatureGenerateService               **
**                                                                            **
**                        Function(s) invoked: Det_ReportError               **
*******************************************************************************/
void Csm_SignatureGenerateCallbackNotification(Std_ReturnType ddResult)
{
  switch (ddResult)
  {
  case CSM_E_BUSY:
    /* Do nothing */
    break;

  case E_OK:
    switch (Csm_GddActiveSignatureGenerateService.ucServiceState)
    {
    case CSM_SIGNATURE_GENERATE_START:
    case CSM_SIGNATURE_GENERATE_UPDATE:
      /* State is set to ACTIVE upon success */
      Csm_GddActiveSignatureGenerateService.ucServiceState
        = CSM_SIGNATURE_GENERATE_ACTIVE;
      break;

    case CSM_SIGNATURE_GENERATE_FINISH:
      /* Setting the service state to idle irrespective of the result */
      Csm_GddActiveSignatureGenerateService.ucServiceState
        = CSM_SIGNATURE_GENERATE_IDLE;
      break;

    default:
      /* Do nothing */
      break;
    }
    break;

  default:
    switch (Csm_GddActiveSignatureGenerateService.ucServiceState)
    {
    case CSM_SIGNATURE_GENERATE_START:
    case CSM_SIGNATURE_GENERATE_UPDATE:
      break;

    case CSM_SIGNATURE_GENERATE_FINISH:
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      if (ddResult == CSM_E_SMALL_BUFFER)
      {
        (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
          CSM_SIGNATUREGENERATEFINISH_SID, CSM_E_BUFFER_TOO_SMALL);
      }
      #endif
      break;

    default:
      /* Do nothing */
      break;
    }

    /* state is set to IDLE upon Failure */
    Csm_GddActiveSignatureGenerateService.ucServiceState
      = CSM_SIGNATURE_GENERATE_IDLE;
    break;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveSignatureGenerateService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveSignatureGenerateService.pActiveServiceConfig->
      CallbackFct(ddResult);
  }
}

/*******************************************************************************
** Function Name        : Csm_SignatureGenerateServiceFinishNotification      **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function shall set the state of Signature      **
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
** Remarks              : Global Variable(s):                                 **
**                        Csm_GddActiveSignatureGenerateService               **
**                                                                            **
**                        Function(s) invoked: None                           **
*******************************************************************************/
void Csm_SignatureGenerateServiceFinishNotification(void)
{
  /* Setting the state to IDLE */
  Csm_GddActiveSignatureGenerateService.ucServiceState =
    CSM_SIGNATURE_GENERATE_IDLE;
}

boolean Csm_SignatureGenerateServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveSignatureGenerateService.pActiveServiceConfig->CallbackFct
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
#endif /* (CSM_SIGNATURE_GENERATE_STATUS == STD_ON) */

#if (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)
/*******************************************************************************
** Function Name        : Csm_SignatureVerifyStart                            **
**                                                                            **
** Service ID           : 0x25                                                **
**                                                                            **
** Description          : This function initializes the signature verification**
**                        service of CSM module. It will store the            **
**                        configuration information identified by "cfgId" and **
**                        will call the corresponding Cry_<primitive>Start()  **
**                        provided the service state is not "active" and shall**
**                        return the value returned by that function and set  **
**                        the service state to "active".                      **
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
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        Csm_GaaSignatureVerifyConfigType                    **
**                        Csm_GddActiveSignatureVerifyService                 **
**                                                                            **
**                        Function(s) invoked : Cry_<Primitive>Start,         **
**                        Csm_FunctionPush, Det_ReportError                   **
*******************************************************************************/
Std_ReturnType Csm_SignatureVerifyStart(Csm_ConfigIdType cfgId,
  const Csm_AsymPublicKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if CSM module is initialized */
  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_SIGNATUREVERIFYSTART_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if Invalid cryptographic method is invoked for selected service */
    if (cfgId >= Csm_GddSignatureVerifyCfgidLimit)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SIGNATUREVERIFYSTART_SID, CSM_E_PARAM_METHOD_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the keyPtr is NULL */
    if (keyPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SIGNATUREVERIFYSTART_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid key type for selected service */
    /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "No Impact of this rule violation" */
    if (keyPtr->length == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SIGNATUREVERIFYSTART_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveSignatureVerifyService.ucServiceState
      & CSM_SIGNATURE_VERIFY_IDLE) != CSM_SIGNATURE_VERIFY_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Set the Service state to CSM_SIGNATURE_VERIFY_START */
    Csm_GddActiveSignatureVerifyService.ucServiceState =
      CSM_SIGNATURE_VERIFY_START;

    /* Assign appropriate config address to the Active Service pointer */
    Csm_GddActiveSignatureVerifyService.pActiveServiceConfig =
      &Csm_GaaSignatureVerifyConfigType[cfgId];

    /*
     * Invoke respective primitive start function
     * argument will be provided by the signature verify configuration
     */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveSignatureVerifyService.
      pActiveServiceConfig->PrimitiveStartFct(
      (void*)Csm_GddActiveSignatureVerifyService.pActiveServiceConfig->
      PrimitiveConfigPtr, keyPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveSignatureVerifyService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Set the Service State to CSM_SIGNATURE_VERIFY_ACTIVE */
          Csm_GddActiveSignatureVerifyService.ucServiceState
            = CSM_SIGNATURE_VERIFY_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveSignatureVerifyService.ucServiceState
            = CSM_SIGNATURE_VERIFY_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveSignatureVerifyService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveSignatureVerifyService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_SignatureVerifyUpdate                           **
**                                                                            **
** Service ID           : 0x26                                                **
**                                                                            **
** Description          : This function is used to feed the signature         **
**                        verification service with the input data. It calls  **
**                        Cry_<Primitive>Update of the primitive identified   **
**                        by the stored configuration information and return  **
**                        the value returned by that function.                **
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
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        Csm_GddActiveSignatureVerifyService                 **
**                                                                            **
**                        Function(s) invoked : Cry_<Primitive>Update,        **
**                        Det_ReportError                                     **
*******************************************************************************/
Std_ReturnType Csm_SignatureVerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if the input pointer is NULL */
  if (dataPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_SIGNATUREVERIFYUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
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
        CSM_SIGNATUREVERIFYUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveSignatureVerifyService.ucServiceState
      & CSM_SIGNATURE_VERIFY_START) == CSM_SIGNATURE_VERIFY_START)
      || ((Csm_GddActiveSignatureVerifyService.ucServiceState
      & CSM_SIGNATURE_VERIFY_UPDATE) == CSM_SIGNATURE_VERIFY_UPDATE)
      || ((Csm_GddActiveSignatureVerifyService.ucServiceState
      & CSM_SIGNATURE_VERIFY_FINISH) == CSM_SIGNATURE_VERIFY_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveSignatureVerifyService.ucServiceState
      & CSM_SIGNATURE_VERIFY_ACTIVE) != CSM_SIGNATURE_VERIFY_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SIGNATUREVERIFYUPDATE_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to UPDATE */
    Csm_GddActiveSignatureVerifyService.ucServiceState =
      CSM_SIGNATURE_VERIFY_UPDATE;

    /* Invoke respective primitive Update function */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveSignatureVerifyService.
      pActiveServiceConfig->PrimitiveUpdateFct(cfgId, dataPtr, dataLength);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveSignatureVerifyService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Set the Service State to CSM_SIGNATURE_VERIFY_ACTIVE */
          Csm_GddActiveSignatureVerifyService.ucServiceState =
            CSM_SIGNATURE_VERIFY_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveSignatureVerifyService.ucServiceState
            = CSM_SIGNATURE_VERIFY_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveSignatureVerifyService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveSignatureVerifyService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_SignatureVerifyFinish                           **
**                                                                            **
** Service ID           : 0x27                                                **
**                                                                            **
** Description          : This function will be used to finish the signature  **
**                        verification service by calling the                 **
**                        Cry_<Primitive>Finish as identified by the stored   **
**                        stored configuration information and returns the    **
**                        value returned by that function                     **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, signaturePtr, signatureLength                **
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
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        Csm_GddActiveSignatureVerifyService                 **
**                                                                            **
**                        Function(s) invoked : Cry_<Primitive>Finish,        **
**                        Det_ReportError                                     **
*******************************************************************************/
Std_ReturnType Csm_SignatureVerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* signaturePtr, uint32 signatureLength,
  Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if the signature pointer is NULL_PTR */
  if (signaturePtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_SIGNATUREVERIFYFINISH_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    if (signatureLength == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SIGNATUREVERIFYFINISH_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the result pointer is NULL */
    if (resultPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SIGNATUREVERIFYFINISH_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveSignatureVerifyService.ucServiceState
      & CSM_SIGNATURE_VERIFY_START) == CSM_SIGNATURE_VERIFY_START)
      || ((Csm_GddActiveSignatureVerifyService.ucServiceState
      & CSM_SIGNATURE_VERIFY_UPDATE) == CSM_SIGNATURE_VERIFY_UPDATE)
      || ((Csm_GddActiveSignatureVerifyService.ucServiceState
      & CSM_SIGNATURE_VERIFY_FINISH) == CSM_SIGNATURE_VERIFY_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveSignatureVerifyService.ucServiceState
      & CSM_SIGNATURE_VERIFY_ACTIVE) != CSM_SIGNATURE_VERIFY_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SIGNATUREVERIFYFINISH_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to FINISH */
    Csm_GddActiveSignatureVerifyService.ucServiceState =
      CSM_SIGNATURE_VERIFY_FINISH;

    /* Invoke respective primitive Finish function */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveSignatureVerifyService.
      pActiveServiceConfig->PrimitiveFinishFct(cfgId, signaturePtr,
      signatureLength, resultPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveSignatureVerifyService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveSignatureVerifyService.ucServiceState
          = CSM_SIGNATURE_VERIFY_IDLE;
      }
      else
      {
        if (Csm_GddActiveSignatureVerifyService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveSignatureVerifyService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_SignatureVerifyCallbackNotification             **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in the configuration of Signature Verify      **
**                        service with the argument given by "Result".        **
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
**                        Csm_GddActiveSignatureVerifyService                 **
*******************************************************************************/
void Csm_SignatureVerifyCallbackNotification(Std_ReturnType ddResult)
{
  switch (ddResult)
  {
  case CSM_E_BUSY:
    /* Do nothing */
    break;

  case E_OK:
    switch (Csm_GddActiveSignatureVerifyService.ucServiceState)
    {
    case CSM_SIGNATURE_VERIFY_START:
    case CSM_SIGNATURE_VERIFY_UPDATE:
      /* State is set to ACTIVE upon success */
      Csm_GddActiveSignatureVerifyService.ucServiceState
        = CSM_SIGNATURE_VERIFY_ACTIVE;
      break;

    case CSM_SIGNATURE_VERIFY_FINISH:
      /* Setting the service state to idle irrespective of the result */
      Csm_GddActiveSignatureVerifyService.ucServiceState
        = CSM_SIGNATURE_VERIFY_IDLE;
      break;

    default:
      /* Do nothing */
      break;
    }
    break;

  default:
    switch (Csm_GddActiveSignatureVerifyService.ucServiceState)
    {
    case CSM_SIGNATURE_VERIFY_START:
    case CSM_SIGNATURE_VERIFY_UPDATE:
      break;

    case CSM_SIGNATURE_VERIFY_FINISH:
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      if (ddResult == CSM_E_SMALL_BUFFER)
      {
        (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
          CSM_SIGNATUREVERIFYFINISH_SID, CSM_E_BUFFER_TOO_SMALL);
      }
      #endif
      break;

    default:
      /* Do nothing */
      break;
    }

    /* state is set to IDLE upon Failure */
    Csm_GddActiveSignatureVerifyService.ucServiceState
      = CSM_SIGNATURE_VERIFY_IDLE;
    break;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveSignatureVerifyService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveSignatureVerifyService.pActiveServiceConfig->
      CallbackFct(ddResult);
  }
}

/*******************************************************************************
** Function Name        : Csm_SignatureVerifyServiceFinishNotification        **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function shall set the state of Signature      **
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
** Remarks              : Global Variable(s):                                 **
**                        Csm_GddActiveSignatureVerifyService                 **
**                                                                            **
**                        Function(s) invoked: None                           **
*******************************************************************************/
void Csm_SignatureVerifyServiceFinishNotification(void)
{
  /* Setting the state to IDLE */
  Csm_GddActiveSignatureVerifyService.ucServiceState =
    CSM_SIGNATURE_VERIFY_IDLE;
}

boolean Csm_SignatureVerifyServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveSignatureVerifyService.pActiveServiceConfig->CallbackFct
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
#endif /* (CSM_SIGNATURE_VERIFY_STATUS == STD_ON) */

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* ((CSM_SIGNATURE_GENERATE_STATUS == STD_ON) || (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)) */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
