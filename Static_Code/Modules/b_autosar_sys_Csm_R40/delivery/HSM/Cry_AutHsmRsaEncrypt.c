/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmRsaEncrypt.c                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HSM RSA Encrypt Interface               **
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
#include "Cry_AutHsmRsaEncrypt.h"
/* Asymmetric Interface */
#if (CSM_ASYM_ENCRYPT_STATUS == STD_ON)
#if (CSM_ASYM_AUTHSMRSAENCRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "Hsm_AutIntDriver.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HsmRsaEncrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_AsymPublicKeyType* pPublicKeyPtr;
  const uint8* pPlainTextPtr;
  uint32 ulPlainTextLength;
  uint8* pCipherTextPtr;
  uint32* pCipherTextLengthPtr;
} Cry_AutHsmRsaEncryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Hsm_DataType Cry_GddAutHsmRsaEncDataType;

static Hsm_DataIDType Cry_GddAutHsmRsaEncDataIDType;

/* Global structure variable for HSM RSA transfer buffer */
static Cry_AutHsmRsaEncryptTransferBuffer Cry_GddAutHsmRsaEncryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/
static void Cry_AutHsmRsaEncryptCallback(Hsm_ErrType ddRet);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutHsmRsaEncryptInit                              **
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
**                      Cry_GddAutHsmRsaEncryptTb                             **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutHsmRsaEncryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutHsmRsaEncryptTb.ucJobState = NO_JOB;
  Cry_GddAutHsmRsaEncryptTb.pPublicKeyPtr = NULL_PTR;
  Cry_GddAutHsmRsaEncryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddAutHsmRsaEncryptTb.ulPlainTextLength = CSM_ZERO;
  Cry_GddAutHsmRsaEncryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddAutHsmRsaEncryptTb.pCipherTextLengthPtr = NULL_PTR;

  Cry_GddAutHsmRsaEncDataType = HSM_DATA_INVALID_KEY;
  Cry_GddAutHsmRsaEncDataIDType = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutHsmRsaEncryptStart                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM RSA, so that RSA is able         **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutHsmRsaEncryptMainFunction() can process      **
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
**                        Cry_GddAutHsmRsaEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutHsmRsaEncryptInit                            **
*******************************************************************************/
Std_ReturnType Cry_AutHsmRsaEncryptStart(const void* cfgPtr,
  const Csm_AsymPublicKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutHsmRsaEncryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutHsmRsaEncryptInit();

    /* Set the job state to JOB_START */
    Cry_GddAutHsmRsaEncryptTb.ucJobState = JOB_START;

    LblAsync = Csm_AsymEncryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        Cry_GddAutHsmRsaEncDataType = HSM_DATA_RSA_PUBLIC_KEY;
        Cry_GddAutHsmRsaEncDataIDType = (Hsm_DataIDType)(keyPtr->data[0]);
        LddErr = HSM_NO_ERROR;
      }
      else if ((keyPtr->length == HSM_RSA_KEY_BYTE_SIZE) \
        || (keyPtr->length == (HSM_RSA_KEY_BYTE_SIZE + CSM_FOUR)))
      {
        Cry_GddAutHsmRsaEncDataType = HSM_DATA_RSA_RAM_PUBLIC_KEY;
        Cry_GddAutHsmRsaEncDataIDType = CSM_ZERO;

        LddErr = Hsm_LoadRamKey(HSM_DATA_RSA_RAM_PUBLIC_KEY, CSM_ZERO,
          keyPtr->length, (const uint8*)(keyPtr->data));
      }
      else
      {
        LddErr = HSM_KEY_INVALID_ERROR;
      }

      if (LddErr == HSM_NO_ERROR)
      {
        LddErr = Hsm_RsaEncInit(LblAsync, NULL_PTR,
          Cry_GddAutHsmRsaEncDataType, Cry_GddAutHsmRsaEncDataIDType);
      }

      if (LddErr == HSM_NO_ERROR)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmRsaEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmRsaEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmRsaEncryptTb.pPublicKeyPtr = keyPtr;
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
** Function Name        : Cry_AutHsmRsaEncryptUpdate                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the RSA      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmRsaEncryptMainFunction() can process the  **
**                        input                                               **
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
**                        small to store the result                           **
**                                                                            **
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddAutHsmRsaEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        HsmRsa_ModExp                                       **
*******************************************************************************/
Std_ReturnType Cry_AutHsmRsaEncryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* plainTextPtr, uint32 plainTextLength, uint8* cipherTextPtr,
  uint32* cipherTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutHsmRsaEncryptTb.ucJobState)
  {
    /* Set the job state to JOB_UPDATE */
    Cry_GddAutHsmRsaEncryptTb.ucJobState = JOB_UPDATE;

    LblAsync = Csm_AsymEncryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*cipherTextLengthPtr < HSM_RSA_KEY_BYTE_SIZE)
      {
        /* Buffer size is invalid */
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        LddErr = Hsm_RsaEncUpdate(LblAsync, NULL_PTR,
          plainTextPtr, plainTextLength, cipherTextPtr, cipherTextLengthPtr);

        if (LddErr != HSM_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmRsaEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmRsaEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmRsaEncryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddAutHsmRsaEncryptTb.ulPlainTextLength = plainTextLength;
      Cry_GddAutHsmRsaEncryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddAutHsmRsaEncryptTb.pCipherTextLengthPtr = cipherTextLengthPtr;
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
** Function Name        : Cry_AutHsmRsaEncryptFinish                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the RSA     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmRsaEncryptMainFunction() can finish the   **
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
**                        Cry_GddAutHsmRsaEncryptTb                           **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
Std_ReturnType Cry_AutHsmRsaEncryptFinish(Csm_ConfigIdType cfgId,
  uint8* cipherTextPtr, uint32* cipherTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);
  CSM_PARAM_UNUSED_PTR(cipherTextPtr);
  CSM_PARAM_UNUSED_PTR(cipherTextLengthPtr);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutHsmRsaEncryptTb.ucJobState)
  {
    /* Set the job state to JOB_FINISH */
    Cry_GddAutHsmRsaEncryptTb.ucJobState = JOB_FINISH;

    LblAsync = Csm_AsymEncryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      LddErr = Hsm_RsaEncFinish(LblAsync, NULL_PTR);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }

      /* reset the state back to NO_JOB */
      Cry_GddAutHsmRsaEncryptTb.ucJobState = NO_JOB;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmRsaEncryptCallback                        **
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
**                        Cry_GddAutHsmRsaEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_AsymEncryptCallbackNotification,                **
**                        Csm_AsymEncryptServiceFinishNotification            **
*******************************************************************************/
static void Cry_AutHsmRsaEncryptCallback(Hsm_ErrType ddRet)
{
  Std_ReturnType LddReturnValue;

  if (ddRet == HSM_BUSY)
  {
    LddReturnValue = CSM_E_BUSY;

    Csm_AsymEncryptCallbackNotification(LddReturnValue);
  }
  else
  {
    LddReturnValue = E_OK;

    switch (Cry_GddAutHsmRsaEncryptTb.ucJobState)
    {
    case JOB_START:
    case JOB_UPDATE:
      if (ddRet == HSM_NO_ERROR)
      {
        Cry_GddAutHsmRsaEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* task failure move job state to NO_JOB */
        Cry_GddAutHsmRsaEncryptTb.ucJobState = NO_JOB;
      }
      Csm_AsymEncryptCallbackNotification(LddReturnValue);
      break;

    case JOB_FINISH:
      if (ddRet != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
      Cry_GddAutHsmRsaEncryptTb.ucJobState = NO_JOB;
      Csm_AsymEncryptCallbackNotification(LddReturnValue);
      break;

    default:
      Csm_AsymEncryptServiceFinishNotification();
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : Cry_AutHsmRsaEncryptMainFunction                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_AsymEncryptCallbackNotification() with the      **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by Cry_AutHsmRsaEncryptStart()   **
**                        or Cry_AutHsmRsaEncryptUpdate(). For                **
**                        Cry_AutHsmRsaEncryptFinish invocation of            **
**                        Csm_AsymEncryptCallbackNotification()               **
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
**                        Cry_GddAutHsmRsaEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_AsymEncryptCallbackNotification,                **
**                        AutHsmRsa_ModExp, EscCallback_setFunction,          **
**                        Csm_AsymEncryptServiceFinishNotification            **
*******************************************************************************/
void Cry_AutHsmRsaEncryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  Hsm_CallbackPtr LpCallback;

  LddReturnValue = E_OK;

  LpCallback = &Cry_AutHsmRsaEncryptCallback;

  switch (Cry_GddAutHsmRsaEncryptTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddAutHsmRsaEncryptTb.pPublicKeyPtr->length == CSM_ONE)
    {
      Cry_GddAutHsmRsaEncDataType = HSM_DATA_RSA_PUBLIC_KEY;
      Cry_GddAutHsmRsaEncDataIDType
        = (Hsm_DataIDType)(Cry_GddAutHsmRsaEncryptTb.pPublicKeyPtr->data[0]);
      LddErr = HSM_NO_ERROR;
    }
    else if ((Cry_GddAutHsmRsaEncryptTb.pPublicKeyPtr->length == HSM_RSA_KEY_BYTE_SIZE) \
      || (Cry_GddAutHsmRsaEncryptTb.pPublicKeyPtr->length == (HSM_RSA_KEY_BYTE_SIZE + CSM_FOUR)))
    {
      Cry_GddAutHsmRsaEncDataType = HSM_DATA_RSA_RAM_PUBLIC_KEY;
      Cry_GddAutHsmRsaEncDataIDType = CSM_ZERO;

      LddErr = Hsm_LoadRamKey(HSM_DATA_RSA_RAM_PUBLIC_KEY, CSM_ZERO,
        Cry_GddAutHsmRsaEncryptTb.pPublicKeyPtr->length,
        (const uint8*)(Cry_GddAutHsmRsaEncryptTb.pPublicKeyPtr->data));
    }
    else
    {
      LddErr = HSM_KEY_INVALID_ERROR;
    }

    if (LddErr == HSM_NO_ERROR)
    {
      LddErr = Hsm_RsaEncInit(CSM_TRUE, LpCallback,
        Cry_GddAutHsmRsaEncDataType, Cry_GddAutHsmRsaEncDataIDType);
    }

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue != E_OK)
    {
      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmRsaEncryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_AsymEncryptCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_UPDATE:
    /* polyspace +1 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (*(Cry_GddAutHsmRsaEncryptTb.pCipherTextLengthPtr) < HSM_RSA_KEY_BYTE_SIZE)
    {
      /* Buffer size is invalid */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      LddErr = Hsm_RsaEncUpdate(CSM_TRUE, LpCallback,
        Cry_GddAutHsmRsaEncryptTb.pPlainTextPtr,
        Cry_GddAutHsmRsaEncryptTb.ulPlainTextLength,
        Cry_GddAutHsmRsaEncryptTb.pCipherTextPtr,
        Cry_GddAutHsmRsaEncryptTb.pCipherTextLengthPtr);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue != E_OK)
    {
      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmRsaEncryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_AsymEncryptCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_FINISH:
    LddErr = Hsm_RsaEncFinish(CSM_TRUE, LpCallback);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      /* reset the state back to NO_JOB */
      Cry_GddAutHsmRsaEncryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_AsymEncryptCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_AsymEncryptServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_ASYM_AUTHSMRSAENCRYPT == STD_ON) */
#endif /* (CSM_ASYM_ENCRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
