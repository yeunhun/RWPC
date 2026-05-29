/*******************************************************************************
**                                                                            **
**  (C) 2013~2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Csm_KeyDerive.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of Key Derivation Function Interface           **
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
** 1.2.5     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.2.4     06-Jan-2020   Sinil        Redmine #21000                        **
** 1.2.3     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.2.2     10-May-2018   Sinil        Redmine #10635                        **
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

#if ((CSM_KEY_DERIVATION_STATUS == STD_ON) || (CSM_KEY_DERIVATION_SYM_KEY_STATUS == STD_ON))
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (CSM_KEY_DERIVATION_STATUS == STD_ON) /* Key Derivation interface */
/* Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveKeyDeriveService Csm_GddActiveKeyDeriveService;
#endif /* (CSM_KEY_DERIVATION_STATUS == STD_ON) */

#if (CSM_KEY_DERIVATION_SYM_KEY_STATUS == STD_ON) /* KeyDeriveSymKey */
/* Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveKeyDeriveSymKeyService Csm_GddActiveKeyDeriveSymKeyService;
#endif /* (CSM_KEY_DERIVATION_SYM_KEY_STATUS == STD_ON) */

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
#if (CSM_KEY_DERIVATION_STATUS == STD_ON) /* Key Derivation interface */
/*******************************************************************************
** Function Name        : Csm_KeyDeriveStart                                  **
**                                                                            **
** Service ID           : 0x2B                                                **
**                                                                            **
** Description          : This function initializes the key derivation service**
**                        of CSM module.                                      **
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
** Input Parameters     : cfgId, keyLength, iterations                        **
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
** Remarks              : Global Variable(s)  : Csm_GddActiveKeyDeriveService **
**                                              Csm_GaaKeyDeriveConfigType    **
**                        Function(s) invoked : Cry_<Primitive>Start,         **
**                                              Csm_FunctionPush              **
*******************************************************************************/
Std_ReturnType Csm_KeyDeriveStart(Csm_ConfigIdType cfgId, uint32 keyLength,
  uint32 iterations)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if CSM module is initialized */
  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_KEYDERIVESTART_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if Invalid cryptographic method is invoked for selected service */
    if (cfgId >= CSM_KEY_DERIVE_CFGID_LIMIT)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYDERIVESTART_SID, CSM_E_PARAM_METHOD_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  /* Use to determine whether to use PSK
     KeyLength is used for pbkdf2KeyNum to maintain consistency with Autoever HSM
     0 : Use user password
     value other than 0 : Use PSK
     Related algorithm : AutHsmPbkdf2 */
  #if 0
  if (LddReturnValue == E_OK)
  {
    /* Check for invalid key type for selected service */
    if (keyLength == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYDERIVESTART_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }
  #endif

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    if (iterations == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYDERIVESTART_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveKeyDeriveService.ucServiceState
      & CSM_KEY_DERIVE_IDLE) != CSM_KEY_DERIVE_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Set the Service state to CSM_KEY_DERIVE_START */
    Csm_GddActiveKeyDeriveService.ucServiceState = CSM_KEY_DERIVE_START;

    /* Assign appropriate config address to the Active Service pointer */
    Csm_GddActiveKeyDeriveService.pActiveServiceConfig =
      &Csm_GaaKeyDeriveConfigType[cfgId];

    /*
     * Invoke respective primitive start function
     * argument will be provided by the Symmetrical Block configuration
     */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveKeyDeriveService.pActiveServiceConfig->
      PrimitiveStartFct(
      (void*)Csm_GddActiveKeyDeriveService.pActiveServiceConfig->
      PrimitiveConfigPtr, keyLength, iterations);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveKeyDeriveService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Set the Service State to CSM_KEY_DERIVE_ACTIVE */
          Csm_GddActiveKeyDeriveService.ucServiceState = CSM_KEY_DERIVE_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveKeyDeriveService.ucServiceState
            = CSM_KEY_DERIVE_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveKeyDeriveService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the primitive main function onto the Main Function stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveKeyDeriveService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_KeyDeriveUpdate                                 **
**                                                                            **
** Service ID           : 0x2C                                                **
**                                                                            **
** Description          : This function is used to feed the KeyDerive         **
**                        calculation service with the input data. It calls   **
**                        Cry_<Primitive>Update of the primitive identified   **
**                        by the stored configuration information and return  **
**                        the value returned by that function.                **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, passwordPtr, passwordLength, saltPtr,        **
**                        saltLength                                          **
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
** Remarks              : Global Variable(s)  : Csm_GddActiveKeyDeriveService **
**                                                                            **
**                        Function(s) invoked : Cry_<Primitive>Update,        **
*******************************************************************************/
Std_ReturnType Csm_KeyDeriveUpdate(Csm_ConfigIdType cfgId,
  const uint8* passwordPtr, uint32 passwordLength, const uint8* saltPtr,
  uint32 saltLength)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  /* Use to determine whether to use PSK
     Using PSK : passwordPtr and passwordLength are not used
     Not using PSK : passwordPtr and passwordLength are used.
       The validity of passwordPtr and passwordLength is verified
       by the primitive algorithm
     Related algorithm : AutHsmPbkdf2 */
  #if 0
  /* Check if the password pointer is NULL_PTR */
  if (passwordPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_KEYDERIVEUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    if (passwordLength == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYDERIVEUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }
  #endif

  /* polyspace +2 MISRA-C3:14.3 [Justified:Low] "No Impact of this rule violation" */
  /* polyspace +1 DEFECT:USELESS_IF RTE:UNR [Justified:Low] "This code can be reached depending on the configuration" */
  if (LddReturnValue == E_OK)
  {
    /* Check if the salt pointer is NULL_PTR */
    if (saltPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYDERIVEUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    if (saltLength == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYDERIVEUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveKeyDeriveService.ucServiceState
      & CSM_KEY_DERIVE_START) == CSM_KEY_DERIVE_START)
      || ((Csm_GddActiveKeyDeriveService.ucServiceState
      & CSM_KEY_DERIVE_UPDATE) == CSM_KEY_DERIVE_UPDATE)
      || ((Csm_GddActiveKeyDeriveService.ucServiceState
      & CSM_KEY_DERIVE_FINISH) == CSM_KEY_DERIVE_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveKeyDeriveService.ucServiceState
      & CSM_KEY_DERIVE_ACTIVE) != CSM_KEY_DERIVE_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYDERIVEUPDATE_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to UPDATE */
    Csm_GddActiveKeyDeriveService.ucServiceState = CSM_KEY_DERIVE_UPDATE;

    /* Invoke respective primitive Update function */
    /* polyspace-begin MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveKeyDeriveService.pActiveServiceConfig->
      PrimitiveUpdateFct(cfgId, passwordPtr, passwordLength, saltPtr,
      saltLength);
    /* polyspace-end MISRA-C3:18.1 RTE:IDP RTE:COR */

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveKeyDeriveService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Set the Service State to CSM_KEY_DERIVE_ACTIVE */
          Csm_GddActiveKeyDeriveService.ucServiceState = CSM_KEY_DERIVE_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveKeyDeriveService.ucServiceState
            = CSM_KEY_DERIVE_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveKeyDeriveService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveKeyDeriveService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_KeyDeriveFinish                                 **
**                                                                            **
** Service ID           : 0x2D                                                **
**                                                                            **
** Description          : This function used to finish the KeyDerive          **
**                        calculation service. Generate service by calling    **
**                        Cry_<Primitive>Finish as identified by stored       **
**                        configuration information and returns the value     **
**                        returned by that function.                          **
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
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Csm_GddActiveKeyDeriveService **
**                        Function(s) invoked : Cry_<Primitive>Finish         **
*******************************************************************************/
Std_ReturnType Csm_KeyDeriveFinish(Csm_ConfigIdType cfgId,
  Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if the result pointer is NULL_PTR */
  if (keyPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_KEYDERIVEFINISH_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveKeyDeriveService.ucServiceState
      & CSM_KEY_DERIVE_START) == CSM_KEY_DERIVE_START)
      || ((Csm_GddActiveKeyDeriveService.ucServiceState
      & CSM_KEY_DERIVE_UPDATE) == CSM_KEY_DERIVE_UPDATE)
      || ((Csm_GddActiveKeyDeriveService.ucServiceState
      & CSM_KEY_DERIVE_FINISH) == CSM_KEY_DERIVE_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveKeyDeriveService.ucServiceState
      & CSM_KEY_DERIVE_ACTIVE) != CSM_KEY_DERIVE_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYDERIVEFINISH_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to FINISH */
    Csm_GddActiveKeyDeriveService.ucServiceState = CSM_KEY_DERIVE_FINISH;

    /* Invoke respective primitive Finish function */
    /* polyspace-begin MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveKeyDeriveService.pActiveServiceConfig->
      PrimitiveFinishFct(cfgId, keyPtr);
    /* polyspace-end MISRA-C3:18.1 RTE:IDP RTE:COR */

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveKeyDeriveService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveKeyDeriveService.ucServiceState = CSM_KEY_DERIVE_IDLE;
      }
      else
      {
        if (Csm_GddActiveKeyDeriveService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveKeyDeriveService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_KeyDeriveCallbackNotification                   **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in the configuration of Key Derive            **
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
**                               Csm_GddActiveKeyDeriveService                **
*******************************************************************************/
void Csm_KeyDeriveCallbackNotification(Std_ReturnType ddResult)
{
  switch (ddResult)
  {
  case CSM_E_BUSY:
    /* Do nothing */
    break;

  case E_OK:
    switch (Csm_GddActiveKeyDeriveService.ucServiceState)
    {
    case CSM_KEY_DERIVE_START:
    case CSM_KEY_DERIVE_UPDATE:
      /* State is set to ACTIVE upon success */
      Csm_GddActiveKeyDeriveService.ucServiceState = CSM_KEY_DERIVE_ACTIVE;
      break;

    case CSM_KEY_DERIVE_FINISH:
      /* Setting the service state to idle irrespective of the result */
      Csm_GddActiveKeyDeriveService.ucServiceState = CSM_KEY_DERIVE_IDLE;
      break;

    default:
      /* Do nothing */
      break;
    }
    break;

  default:
    switch (Csm_GddActiveKeyDeriveService.ucServiceState)
    {
    case CSM_KEY_DERIVE_START:
    case CSM_KEY_DERIVE_UPDATE:
    case CSM_KEY_DERIVE_FINISH:
      break;

    default:
      /* Do nothing */
      break;
    }

    /* state is set to IDLE upon Failure */
    Csm_GddActiveKeyDeriveService.ucServiceState = CSM_KEY_DERIVE_IDLE;
    break;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveKeyDeriveService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveKeyDeriveService.pActiveServiceConfig->CallbackFct(ddResult);
  }
}

/*******************************************************************************
** Function Name        : Csm_KeyDeriveServiceFinishNotification              **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function shall set the state of Key Derive     **
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
**                               Csm_GddActiveKeyDeriveService                **
**                        Function(s) invoked: None                           **
*******************************************************************************/
void Csm_KeyDeriveServiceFinishNotification(void)
{
  /* Setting the state to IDLE */
  Csm_GddActiveKeyDeriveService.ucServiceState = CSM_KEY_DERIVE_IDLE;
}

boolean Csm_KeyDeriveServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveKeyDeriveService.pActiveServiceConfig->
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
#endif /* (CSM_KEY_DERIVATION_STATUS == STD_ON) */

#if (CSM_KEY_DERIVATION_SYM_KEY_STATUS == STD_ON) /* KeyDeriveSymKey */
/*******************************************************************************
** Function Name        : Csm_KeyDeriveSymKey                                 **
**                                                                            **
** Service ID           : 0x4C                                                **
**                                                                            **
** Description          : This function initializes the key derivation service**
**                        of CSM module.                                      **
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
** Input Parameters     : cfgId, baseKeyPtr, customisationValPtr,             **
**                        customisationValLength                              **
**                                                                            **
** InOut parameter      : derivedKeyPtr                                       **
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
** Remarks              : Global Variable(s)  :                               **
**                                        Csm_GaaKeyDeriveSymKeyConfigType    **
**                                        Csm_GddActiveKeyDeriveSymKeyService **
**                        Function(s) invoked : Cry_<Primitive>,              **
**                                              Csm_FunctionPush              **
*******************************************************************************/
Std_ReturnType Csm_KeyDeriveSymKey(Csm_ConfigIdType cfgId,
  const Csm_SymKeyType* baseKeyPtr, const uint8* customisationValPtr,
  uint32 customisationValLength, Csm_SymKeyType* derivedKeyPtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if CSM module is initialized */
  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_KEYDERIVESYMKEY_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if Invalid cryptographic method is invoked for selected service */
    if (cfgId >= CSM_KEY_DERIVE_SYMKEY_CFGID_LIMIT)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYDERIVESYMKEY_SID, CSM_E_PARAM_METHOD_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the baseKeyPtr is NULL_PTR */
    if (baseKeyPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYDERIVESYMKEY_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (baseKeyPtr->length == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYDERIVESYMKEY_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the derivedKeyPtr is NULL_PTR */
    if (derivedKeyPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYDERIVESYMKEY_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (derivedKeyPtr->length == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYDERIVESYMKEY_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the Customization value pointer is NULL_PTR */
    if (customisationValPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYDERIVESYMKEY_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    if (customisationValLength == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYDERIVESYMKEY_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveKeyDeriveSymKeyService.ucServiceState
      & CSM_KEY_DERIVE_SYMKEY_IDLE) != CSM_KEY_DERIVE_SYMKEY_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Set the Service state to ACTIVE */
    Csm_GddActiveKeyDeriveSymKeyService.ucServiceState =
      CSM_KEY_DERIVE_SYMKEY_ACTIVE;

    /* Assign appropriate config address to the Active Service pointer */
    Csm_GddActiveKeyDeriveSymKeyService.pActiveServiceConfig =
      &Csm_GaaKeyDeriveSymKeyConfigType[cfgId];

    /*
     * Invoke respective primitive start function
     * argument will be provided by the Symmetrical Block configuration
     */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveKeyDeriveSymKeyService.pActiveServiceConfig->
      PrimitiveFct(
      (void*)Csm_GddActiveKeyDeriveSymKeyService.pActiveServiceConfig->
      PrimitiveConfigPtr, baseKeyPtr, customisationValPtr,
      customisationValLength, derivedKeyPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveKeyDeriveSymKeyService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveKeyDeriveSymKeyService.ucServiceState =
          CSM_KEY_DERIVE_SYMKEY_IDLE;
      }
      else
      {
        if (Csm_GddActiveKeyDeriveSymKeyService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the primitive main function onto the Main Function stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveKeyDeriveSymKeyService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_KeyDeriveSymKeyCallbackNotification             **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in the configuration of Key Derive            **
**                        Symmetrical Key service with the argument given by  **
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
**                               Csm_GddActiveKeyDeriveSymKeyService          **
**                        Function(s) invoked:                                **
*******************************************************************************/
void Csm_KeyDeriveSymKeyCallbackNotification(Std_ReturnType ddResult)
{
  switch (ddResult)
  {
  case CSM_E_BUSY:
    /* Do nothing. Previous request result will be returned */
    break;

  default:
    /* Setting the service state to idle irrespective of the result */
    Csm_GddActiveKeyDeriveSymKeyService.ucServiceState =
      CSM_KEY_DERIVE_SYMKEY_IDLE;
    break;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveKeyDeriveSymKeyService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveKeyDeriveSymKeyService.pActiveServiceConfig->CallbackFct(ddResult);
  }
}

/*******************************************************************************
** Function Name        : Csm_KeyDeriveSymKeyServiceFinishNotification        **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function shall set the state of Key Derive     **
**                        Symmetrical Key service to "idle".                  **
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
**                               Csm_GddActiveKeyDeriveSymKeyService          **
**                        Function(s) invoked: None                           **
*******************************************************************************/
void Csm_KeyDeriveSymKeyServiceFinishNotification(void)
{
  /* Setting the state to IDLE */
  Csm_GddActiveKeyDeriveSymKeyService.ucServiceState =
    CSM_KEY_DERIVE_SYMKEY_IDLE;
}

boolean Csm_KeyDeriveSymKeyServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveKeyDeriveSymKeyService.pActiveServiceConfig->
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
#endif /* (CSM_KEY_DERIVATION_SYM_KEY_STATUS == STD_ON) */

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* ((CSM_KEY_DERIVATION_STATUS == STD_ON) || (CSM_KEY_DERIVATION_SYM_KEY_STATUS == STD_ON)) */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
