/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Csm_Sym.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of Symmetrical Interface                       **
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

#if ((CSM_SYM_ENCRYPT_STATUS == STD_ON) || (CSM_SYM_DECRYPT_STATUS == STD_ON))
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (CSM_SYM_ENCRYPT_STATUS == STD_ON)
/* Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveSymEncryptService Csm_GddActiveSymEncryptService;
#endif /* (CSM_SYM_ENCRYPT_STATUS == STD_ON) */

#if (CSM_SYM_DECRYPT_STATUS == STD_ON)
/* Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveSymDecryptService Csm_GddActiveSymDecryptService;
#endif /* (CSM_SYM_DECRYPT_STATUS == STD_ON) */

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
#if (CSM_SYM_ENCRYPT_STATUS == STD_ON)
/*******************************************************************************
** Function Name        : Csm_SymEncryptStart                                 **
**                                                                            **
** Service ID           : 0x16                                                **
**                                                                            **
** Description          : This function initializes the symmetrical encrypt   **
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
** Input Parameters     : cfgId, keyPtr, InitVectorPtr, InitVectorLength      **
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
** Remarks              : Global Variable(s)  :                               **
**                                           Csm_GddActiveSymEncryptService   **
**                                           Csm_GaaSymEncryptConfigType      **
**                        Function(s) invoked : Cry_<Primitive>Start,         **
**                        Csm_FunctionPush                                    **
*******************************************************************************/
Std_ReturnType Csm_SymEncryptStart(Csm_ConfigIdType cfgId,
  const Csm_SymKeyType* keyPtr, const uint8* InitVectorPtr,
  uint32 InitVectorLength)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  /* Check if CSM module is initialized */
  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_SYMENCRYPTSTART_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if Invalid cryptographic method is invoked for selected service */
    if (cfgId >= Csm_GddSymEncryptCfgidLimit)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMENCRYPTSTART_SID, CSM_E_PARAM_METHOD_INVALID);
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
        CSM_SYMENCRYPTSTART_SID, CSM_E_PARAM_PTR_INVALID);
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
        CSM_SYMENCRYPTSTART_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the InitVectorPtr is NULL */
    if (InitVectorPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMENCRYPTSTART_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    if (InitVectorLength == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMENCRYPTSTART_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveSymEncryptService.ucServiceState
      & CSM_SYM_ENCRYPT_IDLE) != CSM_SYM_ENCRYPT_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Set the Service state to CSM_SYM_ENCRYPT_START */
    Csm_GddActiveSymEncryptService.ucServiceState = CSM_SYM_ENCRYPT_START;

    /* Assign appropriate config address to the Active Service pointer */
    Csm_GddActiveSymEncryptService.pActiveServiceConfig =
      &Csm_GaaSymEncryptConfigType[cfgId];

    /*
     * Invoke respective primitive start function
     * argument will be provided by the Symmetrical Block configuration
     */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveSymEncryptService.pActiveServiceConfig->
      PrimitiveStartFct((void*)Csm_GddActiveSymEncryptService.
      pActiveServiceConfig->PrimitiveConfigPtr, keyPtr, InitVectorPtr,
      InitVectorLength);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveSymEncryptService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Setting the service state to active upon success */
          Csm_GddActiveSymEncryptService.ucServiceState
            = CSM_SYM_ENCRYPT_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveSymEncryptService.ucServiceState =
            CSM_SYM_ENCRYPT_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveSymEncryptService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveSymEncryptService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_SymEncryptUpdate                                **
**                                                                            **
** Service ID           : 0x17                                                **
**                                                                            **
** Description          : This function is used to feed the symmetrical       **
**                        encryption service with the input data. It calls    **
**                        Cry_<Primitive>Update of the primitive identified   **
**                        by the stored configuration information and return  **
**                        the value returned by that function.                **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, plainTextPtr, plainTextLength                **
**                                                                            **
** InOut parameter      : cipherTextLengthPtr                                 **
**                                                                            **
** Output Parameters    : cipherTextPtr                                       **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        CSM_E_SMALL_BUFFER: the provided buffer is too      **
**                                               small to store the result.   **
**                        E_NOT_OK: service state is "idle"                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                           Csm_GddActiveSymEncryptService   **
**                        Function(s) invoked : Cry_<Primitive>Update         **
**                        Det_ReportError                                     **
*******************************************************************************/
Std_ReturnType Csm_SymEncryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* plainTextPtr, uint32 plainTextLength, uint8* cipherTextPtr,
  uint32* cipherTextLengthPtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if the input pointer is NULL */
  if (plainTextPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_SYMENCRYPTUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    if (plainTextLength == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMENCRYPTUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the result pointer is NULL */
    if (cipherTextPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMENCRYPTUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the result length pointer is NULL */
    if (cipherTextLengthPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMENCRYPTUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "No Impact of this rule violation" */
    if (*cipherTextLengthPtr == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMENCRYPTUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveSymEncryptService.ucServiceState
      & CSM_SYM_ENCRYPT_START) == CSM_SYM_ENCRYPT_START)
      || ((Csm_GddActiveSymEncryptService.ucServiceState
      & CSM_SYM_ENCRYPT_UPDATE) == CSM_SYM_ENCRYPT_UPDATE)
      || ((Csm_GddActiveSymEncryptService.ucServiceState
      & CSM_SYM_ENCRYPT_FINISH) == CSM_SYM_ENCRYPT_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveSymEncryptService.ucServiceState
      & CSM_SYM_ENCRYPT_ACTIVE) != CSM_SYM_ENCRYPT_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMENCRYPTUPDATE_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to UPDATE */
    Csm_GddActiveSymEncryptService.ucServiceState = CSM_SYM_ENCRYPT_UPDATE;

    /* Invoke respective primitive Update function */
    /* polyspace-begin MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveSymEncryptService.pActiveServiceConfig->
      PrimitiveUpdateFct(cfgId, plainTextPtr, plainTextLength,
      cipherTextPtr, cipherTextLengthPtr);
    /* polyspace-end MISRA-C3:18.1 RTE:IDP RTE:COR */

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveSymEncryptService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Set the Service State to CSM_MAC_GENERATE_ACTIVE */
          Csm_GddActiveSymEncryptService.ucServiceState = CSM_SYM_ENCRYPT_ACTIVE;
        }
        else
        {
          #if (CSM_DEV_ERROR_DETECT == STD_ON)
          if (LddReturnValue == CSM_E_SMALL_BUFFER)
          {
            (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
              CSM_SYMENCRYPTUPDATE_SID, CSM_E_BUFFER_TOO_SMALL);
          }
          #endif

          /* Setting the service state to idle upon failure */
          Csm_GddActiveSymEncryptService.ucServiceState = CSM_SYM_ENCRYPT_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveSymEncryptService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveSymEncryptService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_SymEncryptFinish                                **
**                                                                            **
** Service ID           : 0x18                                                **
**                                                                            **
** Description          : This function used to finish the symmetrical        **
**                        encryption service. Generate service by calling     **
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
** InOut parameter      : cipherTextLengthPtr                                 **
**                                                                            **
** Output Parameters    : cipherTextPtr                                       **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        E_NOT_OK: service state is "idle"                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                           Csm_GddActiveSymEncryptService   **
**                        Function(s) invoked : Cry_<Primitive>Finish         **
*******************************************************************************/
Std_ReturnType Csm_SymEncryptFinish(Csm_ConfigIdType cfgId,
  uint8* cipherTextPtr, uint32* cipherTextLengthPtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if the result pointer is NULL */
  if (cipherTextPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_SYMENCRYPTFINISH_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the result length pointer is NULL */
    if (cipherTextLengthPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMENCRYPTFINISH_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "No Impact of this rule violation" */
    if (*cipherTextLengthPtr == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMENCRYPTFINISH_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveSymEncryptService.ucServiceState
      & CSM_SYM_ENCRYPT_START) == CSM_SYM_ENCRYPT_START)
      || ((Csm_GddActiveSymEncryptService.ucServiceState
      & CSM_SYM_ENCRYPT_UPDATE) == CSM_SYM_ENCRYPT_UPDATE)
      || ((Csm_GddActiveSymEncryptService.ucServiceState
      & CSM_SYM_ENCRYPT_FINISH) == CSM_SYM_ENCRYPT_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveSymEncryptService.ucServiceState
      & CSM_SYM_ENCRYPT_ACTIVE) != CSM_SYM_ENCRYPT_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMENCRYPTFINISH_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to FINISH */
    Csm_GddActiveSymEncryptService.ucServiceState = CSM_SYM_ENCRYPT_FINISH;

    /* Invoke respective primitive Finish function */
    /* polyspace-begin MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveSymEncryptService.pActiveServiceConfig->
      PrimitiveFinishFct(cfgId, cipherTextPtr, cipherTextLengthPtr);
    /* polyspace-end MISRA-C3:18.1 RTE:IDP RTE:COR */

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveSymEncryptService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveSymEncryptService.ucServiceState = CSM_SYM_ENCRYPT_IDLE;
      }
      else
      {
        if (Csm_GddActiveSymEncryptService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveSymEncryptService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_SymEncryptCallbackNotification                  **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in the configuration of the service           **
**                        Symmetrical Encryption with the argument            **
**                        given by "Result".                                  **
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
**                        Csm_GddActiveSymEncryptService                      **
**                                                                            **
**                        Function(s) invoked: Det_ReportError                **
*******************************************************************************/
void Csm_SymEncryptCallbackNotification(Std_ReturnType ddResult)
{
  switch (ddResult)
  {
  case CSM_E_BUSY:
    /* Do nothing */
    break;

  case E_OK:
    switch (Csm_GddActiveSymEncryptService.ucServiceState)
    {
    case CSM_SYM_ENCRYPT_START:
    case CSM_SYM_ENCRYPT_UPDATE:
      /* State is set to ACTIVE upon success */
      Csm_GddActiveSymEncryptService.ucServiceState = CSM_SYM_ENCRYPT_ACTIVE;
      break;

    case CSM_SYM_ENCRYPT_FINISH:
      /* Setting the service state to idle irrespective of the result */
      Csm_GddActiveSymEncryptService.ucServiceState = CSM_SYM_ENCRYPT_IDLE;
      break;

    default:
      /* Do nothing */
      break;
    }
    break;

  default:
    switch (Csm_GddActiveSymEncryptService.ucServiceState)
    {
    case CSM_SYM_ENCRYPT_START:
    case CSM_SYM_ENCRYPT_FINISH:
      break;

    case CSM_SYM_ENCRYPT_UPDATE:
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      if (ddResult == CSM_E_SMALL_BUFFER)
      {
        (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
          CSM_SYMENCRYPTUPDATE_SID, CSM_E_BUFFER_TOO_SMALL);
      }
      #endif
      break;

    default:
      /* Do nothing */
      break;
    }

    /* state is set to IDLE upon failure */
    Csm_GddActiveSymEncryptService.ucServiceState = CSM_SYM_ENCRYPT_IDLE;
    break;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveSymEncryptService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveSymEncryptService.pActiveServiceConfig->
      CallbackFct(ddResult);
  }
}

/*******************************************************************************
** Function Name        : Csm_SymEncryptServiceFinishNotification             **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function shall set the state of the            **
**                        Symmetrical Encryption service to "idle".           **
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
**                        Csm_GddActiveSymEncryptService                      **
**                                                                            **
**                        Function(s) invoked: None                           **
*******************************************************************************/
void Csm_SymEncryptServiceFinishNotification(void)
{
  /* Setting the state to IDLE */
  Csm_GddActiveSymEncryptService.ucServiceState = CSM_SYM_ENCRYPT_IDLE;
}

boolean Csm_SymEncryptServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveSymEncryptService.pActiveServiceConfig->CallbackFct
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
#endif /* (CSM_SYM_ENCRYPT_STATUS == STD_ON) */

#if (CSM_SYM_DECRYPT_STATUS == STD_ON)
/*******************************************************************************
** Function Name        : Csm_SymDecryptStart                                 **
**                                                                            **
** Service ID           : 0x19                                                **
**                                                                            **
** Description          : This function initializes the symmetrical decrypt   **
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
** Input Parameters     : cfgId, keyPtr, InitVectorPtr, InitVectorLength      **
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
** Remarks              : Global Variable(s)  :                               **
**                                           Csm_GddActiveSymDecryptService   **
**                                           Csm_GaaSymDecryptConfigType      **
**                        Function(s) invoked : Cry_<Primitive>Start,         **
**                        Csm_FunctionPush                                    **
*******************************************************************************/
Std_ReturnType Csm_SymDecryptStart(Csm_ConfigIdType cfgId,
  const Csm_SymKeyType* keyPtr, const uint8* InitVectorPtr,
  uint32 InitVectorLength)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if CSM module is initialized */
  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_SYMDECRYPTSTART_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if Invalid cryptographic method is invoked for selected service */
    if (cfgId >= Csm_GddSymDecryptCfgidLimit)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMDECRYPTSTART_SID, CSM_E_PARAM_METHOD_INVALID);
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
        CSM_SYMDECRYPTSTART_SID, CSM_E_PARAM_PTR_INVALID);
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
        CSM_SYMDECRYPTSTART_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the InitVectorPtr is NULL_PTR */
    if (InitVectorPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMDECRYPTSTART_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    if (InitVectorLength == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMDECRYPTSTART_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveSymDecryptService.ucServiceState
      & CSM_SYM_DECRYPT_IDLE) != CSM_SYM_DECRYPT_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Set the Service state to CSM_SYM_DECRYPT_START */
    Csm_GddActiveSymDecryptService.ucServiceState = CSM_SYM_DECRYPT_START;

    /* Assign appropriate config address to the Active Service pointer */
    Csm_GddActiveSymDecryptService.pActiveServiceConfig =
      &Csm_GaaSymDecryptConfigType[cfgId];

    /*
     * Invoke respective primitive start function
     * argument will be provided by the Symmetrical Block configuration
     */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveSymDecryptService.pActiveServiceConfig->
      PrimitiveStartFct((void*)Csm_GddActiveSymDecryptService.
      pActiveServiceConfig->PrimitiveConfigPtr, keyPtr, InitVectorPtr,
      InitVectorLength);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveSymDecryptService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Set the Service State to CSM_SYM_DECRYPT_ACTIVE */
          Csm_GddActiveSymDecryptService.ucServiceState
            = CSM_SYM_DECRYPT_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveSymDecryptService.ucServiceState
            = CSM_SYM_DECRYPT_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveSymDecryptService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveSymDecryptService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_SymDecryptUpdate                                **
**                                                                            **
** Service ID           : 0x1A                                                **
**                                                                            **
** Description          : This function is used to feed the symmetrical       **
**                        decryption service with the input data. It calls    **
**                        Cry_<Primitive>Update of the primitive identified   **
**                        by the stored configuration information and return  **
**                        the value returned by that function.                **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, cipherTextPtr, cipherTextLength              **
**                                                                            **
** InOut parameter      : plainTextLengthPtr                                  **
**                                                                            **
** Output Parameters    : plainTextPtr                                        **
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
** Remarks              : Global Variable(s)  :                               **
**                                           Csm_GddActiveSymDecryptService   **
**                        Function(s) invoked : Cry_<Primitive>Update         **
**                        Det_ReportError                                     **
*******************************************************************************/
Std_ReturnType Csm_SymDecryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* cipherTextPtr, uint32 cipherTextLength, uint8* plainTextPtr,
  uint32* plainTextLengthPtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if the input pointer is NULL */
  if (cipherTextPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_SYMDECRYPTUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    if (cipherTextLength == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMDECRYPTUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the result pointer is NULL */
    if (plainTextPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMDECRYPTUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the result length pointer is NULL */
    if (plainTextLengthPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMDECRYPTUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "No Impact of this rule violation" */
    if (*plainTextLengthPtr == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMDECRYPTUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveSymDecryptService.ucServiceState
      & CSM_SYM_DECRYPT_START) == CSM_SYM_DECRYPT_START)
      || ((Csm_GddActiveSymDecryptService.ucServiceState
      & CSM_SYM_DECRYPT_UPDATE) == CSM_SYM_DECRYPT_UPDATE)
      || ((Csm_GddActiveSymDecryptService.ucServiceState
      & CSM_SYM_DECRYPT_FINISH) == CSM_SYM_DECRYPT_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveSymDecryptService.ucServiceState
      & CSM_SYM_DECRYPT_ACTIVE) != CSM_SYM_DECRYPT_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMDECRYPTUPDATE_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to UPDATE */
    Csm_GddActiveSymDecryptService.ucServiceState = CSM_SYM_DECRYPT_UPDATE;

    /* Invoke respective primitive Update function */
    /* polyspace-begin MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveSymDecryptService.pActiveServiceConfig->
      PrimitiveUpdateFct(cfgId, cipherTextPtr, cipherTextLength,
      plainTextPtr, plainTextLengthPtr);
    /* polyspace-end MISRA-C3:18.1 RTE:IDP RTE:COR */

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveSymDecryptService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Set the Service State to CSM_SYM_DECRYPT_ACTIVE */
          Csm_GddActiveSymDecryptService.ucServiceState = CSM_SYM_DECRYPT_ACTIVE;
        }
        else
        {
          #if (CSM_DEV_ERROR_DETECT == STD_ON)
          if (LddReturnValue == CSM_E_SMALL_BUFFER)
          {
            (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
              CSM_SYMDECRYPTUPDATE_SID, CSM_E_BUFFER_TOO_SMALL);
          }
          #endif

          /* Setting the service state to idle upon failure */
          Csm_GddActiveSymDecryptService.ucServiceState = CSM_SYM_DECRYPT_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveSymDecryptService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveSymDecryptService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_SymDecryptFinish                                **
**                                                                            **
** Service ID           : 0x1B                                                **
**                                                                            **
** Description          : This function will be used to finish the symmetrical**
**                        decryption service by calling Cry_<Primitive>Finish **
**                        as identified by the stored stored configuration    **
**                        information and returns the value returned by that  **
**                        function.                                           **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId                                               **
**                                                                            **
** InOut parameter      : plainTextLengthPtr                                  **
**                                                                            **
** Output Parameters    : plainTextPtr                                        **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        E_NOT_OK: service state is "idle"                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                           Csm_GddActiveSymDecryptService   **
**                        Function(s) invoked : Cry_<Primitive>Finish         **
*******************************************************************************/
Std_ReturnType Csm_SymDecryptFinish(Csm_ConfigIdType cfgId,
  uint8* plainTextPtr, uint32* plainTextLengthPtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if the result pointer is NULL_PTR */
  if (plainTextPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_SYMDECRYPTFINISH_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the result length pointer is NULL_PTR */
    if (plainTextLengthPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMDECRYPTFINISH_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "No Impact of this rule violation" */
    if (*plainTextLengthPtr == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMDECRYPTFINISH_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveSymDecryptService.ucServiceState
      & CSM_SYM_DECRYPT_START) == CSM_SYM_DECRYPT_START)
      || ((Csm_GddActiveSymDecryptService.ucServiceState
      & CSM_SYM_DECRYPT_UPDATE) == CSM_SYM_DECRYPT_UPDATE)
      || ((Csm_GddActiveSymDecryptService.ucServiceState
      & CSM_SYM_DECRYPT_FINISH) == CSM_SYM_DECRYPT_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveSymDecryptService.ucServiceState
      & CSM_SYM_DECRYPT_ACTIVE) != CSM_SYM_DECRYPT_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_SYMDECRYPTFINISH_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to FINISH */
    Csm_GddActiveSymDecryptService.ucServiceState = CSM_SYM_DECRYPT_FINISH;

    /* Invoke respective primitive Finish function */
    /* polyspace-begin MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveSymDecryptService.pActiveServiceConfig->
      PrimitiveFinishFct(cfgId, plainTextPtr, plainTextLengthPtr);
    /* polyspace-end MISRA-C3:18.1 RTE:IDP RTE:COR */

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveSymDecryptService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveSymDecryptService.ucServiceState = CSM_SYM_DECRYPT_IDLE;
      }
      else
      {
        if (Csm_GddActiveSymDecryptService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveSymDecryptService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_SymDecryptCallbackNotification                  **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in the configuration of the service           **
**                        Symmetrical Decryption with the argument            **
**                        given by "Result".                                  **
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
**                        Csm_GddActiveSymDecryptService                      **
**                        Function(s) invoked: Det_ReportError                **
*******************************************************************************/
void Csm_SymDecryptCallbackNotification(Std_ReturnType ddResult)
{
  switch (ddResult)
  {
  case CSM_E_BUSY:
    /* Do nothing */
    break;

  case E_OK:
    switch (Csm_GddActiveSymDecryptService.ucServiceState)
    {
    case CSM_SYM_DECRYPT_START:
    case CSM_SYM_DECRYPT_UPDATE:
      /* State is set to ACTIVE upon success */
      Csm_GddActiveSymDecryptService.ucServiceState = CSM_SYM_DECRYPT_ACTIVE;
      break;

    case CSM_SYM_DECRYPT_FINISH:
      /* Setting the service state to idle irrespective of the result */
      Csm_GddActiveSymDecryptService.ucServiceState = CSM_SYM_DECRYPT_IDLE;
      break;

    default:
      /* Do nothing */
      break;
    }
    break;

  default:
    switch (Csm_GddActiveSymDecryptService.ucServiceState)
    {
    case CSM_SYM_DECRYPT_START:
    case CSM_SYM_DECRYPT_FINISH:
      break;

    case CSM_SYM_DECRYPT_UPDATE:
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      if (ddResult == CSM_E_SMALL_BUFFER)
      {
        (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
          CSM_SYMDECRYPTUPDATE_SID, CSM_E_BUFFER_TOO_SMALL);
      }
      #endif
      break;

    default:
      /* Do nothing */
      break;
    }

    /* state is set to IDLE upon Failure */
    Csm_GddActiveSymDecryptService.ucServiceState = CSM_SYM_DECRYPT_IDLE;
    break;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveSymDecryptService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveSymDecryptService.pActiveServiceConfig->
      CallbackFct(ddResult);
  }
}

/*******************************************************************************
** Function Name        : Csm_SymDecryptServiceFinishNotification             **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function shall set the state of the            **
**                        Symmetrical Decryption service to "idle".           **
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
**                        Csm_GddActiveSymDecryptService                      **
**                                                                            **
**                        Function(s) invoked: None                           **
*******************************************************************************/
void Csm_SymDecryptServiceFinishNotification(void)
{
  /* Setting the state to IDLE */
  Csm_GddActiveSymDecryptService.ucServiceState = CSM_SYM_DECRYPT_IDLE;
}

boolean Csm_SymDecryptServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveSymDecryptService.pActiveServiceConfig->CallbackFct
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
#endif /* (CSM_SYM_DECRYPT_STATUS == STD_ON) */

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* ((CSM_SYM_ENCRYPT_STATUS == STD_ON) || (CSM_SYM_DECRYPT_STATUS == STD_ON)) */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
