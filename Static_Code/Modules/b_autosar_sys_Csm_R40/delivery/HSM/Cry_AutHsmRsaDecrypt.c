/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmRsaDecrypt.c                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HSM RSA Decrypt Interface               **
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
** 1.0.3     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.2     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.1     17-Apr-2018   Sinil        Redmine #12351                        **
** 1.0.0     18-Apr-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for HSM RSA */
#include "Cry_AutHsmRsaDecrypt.h"
/* Asymmetric Interface */
#if (CSM_ASYM_DECRYPT_STATUS == STD_ON)
#if (CSM_ASYM_AUTHSMRSADECRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "Hsm_AutIntDriver.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HsmRsaDecrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_AsymPrivateKeyType* pPrivateKeyPtr;
  const uint8* pCipherTextPtr;
  uint32 ulCipherTextLength;
  uint8* pPlainTextPtr;
  uint32* pPlainTextLengthPtr;
} Cry_AutHsmRsaDecryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Hsm_DataType Cry_GddAutHsmRsaDecDataType;

static Hsm_DataIDType Cry_GddAutHsmRsaDecDataIDType;

/* Global structure variable for HSM RSA transfer buffer */
static Cry_AutHsmRsaDecryptTransferBuffer Cry_GddAutHsmRsaDecryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/
static void Cry_AutHsmRsaDecryptCallback(Hsm_ErrType ddRet);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutHsmRsaDecryptInit                              **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the RSA module.              **
**                      All the Global variables will be initialized after    **
**                      the successful completion of this API.                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non-Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s):                                   **
**                      Cry_GddAutHsmRsaDecryptTb                             **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutHsmRsaDecryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutHsmRsaDecryptTb.ucJobState = NO_JOB;
  Cry_GddAutHsmRsaDecryptTb.pPrivateKeyPtr = NULL_PTR;
  Cry_GddAutHsmRsaDecryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddAutHsmRsaDecryptTb.ulCipherTextLength = CSM_ZERO;
  Cry_GddAutHsmRsaDecryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddAutHsmRsaDecryptTb.pPlainTextLengthPtr = NULL_PTR;

  Cry_GddAutHsmRsaDecDataType = HSM_DATA_INVALID_KEY;
  Cry_GddAutHsmRsaDecDataIDType = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutHsmRsaDecryptStart                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM RSA, so that RSA is able         **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutHsmRsaDecryptMainFunction() can process      **
**                        initialisation                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgPtr, keyPtr                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                                                                            **
** Preconditions        : CSM should have been initialized                    **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddAutHsmRsaDecryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutHsmRsaDecryptInit                            **
*******************************************************************************/
Std_ReturnType Cry_AutHsmRsaDecryptStart(const void* cfgPtr,
  const Csm_AsymPrivateKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutHsmRsaDecryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutHsmRsaDecryptInit();

    /* Set the job state to JOB_START */
    Cry_GddAutHsmRsaDecryptTb.ucJobState = JOB_START;

    LblAsync = Csm_AsymDecryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        Cry_GddAutHsmRsaDecDataType = HSM_DATA_RSA_PRIVATE_KEY;
        Cry_GddAutHsmRsaDecDataIDType = (Hsm_DataIDType)(keyPtr->data[0]);
        LddErr = HSM_NO_ERROR;
      }
      else if (keyPtr->length == (HSM_RSA_KEY_BYTE_SIZE * CSM_TWO))
      {
        Cry_GddAutHsmRsaDecDataType = HSM_DATA_RSA_RAM_PRIVATE_KEY;
        Cry_GddAutHsmRsaDecDataIDType = CSM_ZERO;

        LddErr = Hsm_LoadRamKey(HSM_DATA_RSA_RAM_PRIVATE_KEY, CSM_ZERO,
          keyPtr->length, (const uint8*)(keyPtr->data));
      }
      else
      {
        LddErr = HSM_KEY_INVALID_ERROR;
      }

      if (LddErr == HSM_NO_ERROR)
      {
        LddErr = Hsm_RsaDecInit(LblAsync, NULL_PTR,
          Cry_GddAutHsmRsaDecDataType, Cry_GddAutHsmRsaDecDataIDType);
      }

      if (LddErr == HSM_NO_ERROR)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmRsaDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmRsaDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmRsaDecryptTb.pPrivateKeyPtr = keyPtr;
    }
  }
  else
  {
    /* Other job is still processing, return CSM_E_BUSY */
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmRsaDecryptUpdate                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the RSA      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmRsaDecryptMainFunction() can process the  **
**                        input                                               **
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
**                        CSM_E_SMALL_BUFFER: the provided buffer is too      **
**                        small to store the result                           **
**                                                                            **
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddAutHsmRsaDecryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        HsmRsa_ModExpLong                                   **
*******************************************************************************/
Std_ReturnType Cry_AutHsmRsaDecryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* cipherTextPtr, uint32 cipherTextLength, uint8* plainTextPtr,
  uint32* plainTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutHsmRsaDecryptTb.ucJobState)
  {
    /* Set the job state to JOB_UPDATE */
    Cry_GddAutHsmRsaDecryptTb.ucJobState = JOB_UPDATE;

    LblAsync = Csm_AsymDecryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      LddErr = Hsm_RsaDecUpdate(LblAsync, NULL_PTR,
        cipherTextPtr, cipherTextLength, plainTextPtr, plainTextLengthPtr);

      if (LddErr == HSM_NO_ERROR)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmRsaDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmRsaDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmRsaDecryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddAutHsmRsaDecryptTb.ulCipherTextLength = cipherTextLength;
      Cry_GddAutHsmRsaDecryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddAutHsmRsaDecryptTb.pPlainTextLengthPtr = plainTextLengthPtr;
    }
  }
  else
  {
    /* Job process still not complete, return CSM_E_BUSY */
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmRsaDecryptFinish                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the RSA     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmRsaDecryptMainFunction() can finish the   **
**                        computation and store the result in the memory      **
**                        location given                                      **
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
**                                                                            **
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddAutHsmRsaDecryptTb                           **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
Std_ReturnType Cry_AutHsmRsaDecryptFinish(Csm_ConfigIdType cfgId,
  uint8* plainTextPtr, uint32* plainTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);
  CSM_PARAM_UNUSED_PTR(plainTextPtr);
  CSM_PARAM_UNUSED_PTR(plainTextLengthPtr);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutHsmRsaDecryptTb.ucJobState)
  {
    /* Set the job state to JOB_FINISH */
    Cry_GddAutHsmRsaDecryptTb.ucJobState = JOB_FINISH;

    LblAsync = Csm_AsymDecryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      LddErr = Hsm_RsaDecFinish(LblAsync, NULL_PTR);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }

      /* reset the state back to NO_JOB */
      Cry_GddAutHsmRsaDecryptTb.ucJobState = NO_JOB;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmRsaDecryptCallback                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : TBD                                                 **
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
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddAutHsmRsaDecryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_AsymDecryptCallbackNotification,                **
**                        Csm_AsymDecryptServiceFinishNotification            **
*******************************************************************************/
static void Cry_AutHsmRsaDecryptCallback(Hsm_ErrType ddRet)
{
  Std_ReturnType LddReturnValue;

  if (ddRet == HSM_BUSY)
  {
    LddReturnValue = CSM_E_BUSY;

    Csm_AsymDecryptCallbackNotification(LddReturnValue);
  }
  else
  {
    LddReturnValue = E_OK;

    switch (Cry_GddAutHsmRsaDecryptTb.ucJobState)
    {
    case JOB_START:
    case JOB_UPDATE:
      if (ddRet == HSM_NO_ERROR)
      {
        Cry_GddAutHsmRsaDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* task failure move job state to NO_JOB */
        Cry_GddAutHsmRsaDecryptTb.ucJobState = NO_JOB;
      }
      Csm_AsymDecryptCallbackNotification(LddReturnValue);
      break;

    case JOB_FINISH:
      if (ddRet != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
      Cry_GddAutHsmRsaDecryptTb.ucJobState = NO_JOB;
      Csm_AsymDecryptCallbackNotification(LddReturnValue);
      break;

    default:
      Csm_AsymDecryptServiceFinishNotification();
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : Cry_AutHsmRsaDecryptMainFunction                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_AsymDecryptCallbackNotification() with the      **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by Cry_AutHsmRsaDecryptStart()   **
**                        or Cry_AutHsmRsaDecryptUpdate(). For                **
**                        Cry_AutHsmRsaDecryptFinish invocation of            **
**                        Csm_AsymDecryptCallbackNotification()               **
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
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddAutHsmRsaDecryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_AsymDecryptCallbackNotification,                **
**                        AutHsmRsa_ModExpLong, EscCallback_setFunction,      **
**                        Csm_AsymDecryptServiceFinishNotification            **
*******************************************************************************/
void Cry_AutHsmRsaDecryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  Hsm_CallbackPtr LpCallback;

  LddReturnValue = E_OK;

  LpCallback = &Cry_AutHsmRsaDecryptCallback;

  switch (Cry_GddAutHsmRsaDecryptTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddAutHsmRsaDecryptTb.pPrivateKeyPtr->length == CSM_ONE)
    {
      Cry_GddAutHsmRsaDecDataType = HSM_DATA_RSA_PRIVATE_KEY;
      Cry_GddAutHsmRsaDecDataIDType
        = (Hsm_DataIDType)(Cry_GddAutHsmRsaDecryptTb.pPrivateKeyPtr->data[0]);
      LddErr = HSM_NO_ERROR;
    }
    else if (Cry_GddAutHsmRsaDecryptTb.pPrivateKeyPtr->length
      == (HSM_RSA_KEY_BYTE_SIZE * CSM_TWO))
    {
      Cry_GddAutHsmRsaDecDataType = HSM_DATA_RSA_RAM_PRIVATE_KEY;
      Cry_GddAutHsmRsaDecDataIDType = CSM_ZERO;

      LddErr = Hsm_LoadRamKey(HSM_DATA_RSA_RAM_PRIVATE_KEY, CSM_ZERO,
        Cry_GddAutHsmRsaDecryptTb.pPrivateKeyPtr->length,
        (const uint8*)(Cry_GddAutHsmRsaDecryptTb.pPrivateKeyPtr->data));
    }
    else
    {
      LddErr = HSM_KEY_INVALID_ERROR;
    }

    if (LddErr == HSM_NO_ERROR)
    {
      LddErr = Hsm_RsaDecInit(CSM_TRUE, LpCallback,
        Cry_GddAutHsmRsaDecDataType, Cry_GddAutHsmRsaDecDataIDType);
    }

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue != E_OK)
    {
      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmRsaDecryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_AsymDecryptCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_UPDATE:
    LddErr = Hsm_RsaDecUpdate(CSM_TRUE, LpCallback,
      Cry_GddAutHsmRsaDecryptTb.pCipherTextPtr,
      Cry_GddAutHsmRsaDecryptTb.ulCipherTextLength,
      Cry_GddAutHsmRsaDecryptTb.pPlainTextPtr,
      Cry_GddAutHsmRsaDecryptTb.pPlainTextLengthPtr);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue != E_OK)
    {
      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmRsaDecryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_AsymDecryptCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_FINISH:
    LddErr = Hsm_RsaDecFinish(CSM_TRUE, LpCallback);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutHsmRsaDecryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_AsymDecryptCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_AsymDecryptServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_ASYM_AUTHSMRSADECRYPT == STD_ON) */
#endif /* (CSM_ASYM_DECRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
