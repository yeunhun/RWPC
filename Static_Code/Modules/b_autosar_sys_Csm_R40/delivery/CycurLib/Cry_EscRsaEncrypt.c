/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_EscRsaEncrypt.c                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Escrypt RSA Encrypt Interface           **
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
** 1.2.1     21-Sep-2017   Sinil        Redmine #10040                        **
** 1.2.0     27-Feb-2017   Sinil        Redmine #7650, #7672                  **
** 1.1.0     11-Jan-2017   Sinil        Redmine #7198, #7323                  **
** 1.0.9     21-Sep-2016   Sinil        Redmine #5554, #6128                  **
** 1.0.8     09-Aug-2016   Sinil        Redmine #5693, #5747                  **
** 1.0.7     12-Jul-2016   Sinil        Redmine #5514, #5540                  **
** 1.0.6     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.5     16-May-2016   Sinil        Redmine #4903                         **
** 1.0.4     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.3     02-May-2016   Sinil        Redmine #4607                         **
** 1.0.2     31-Dec-2015   Sinil        Adjust changed stucture               **
** 1.0.1     02-Dec-2015   Sinil        1. Crypto api changed                 **
**                                      2. Memory section changed             **
** 1.0.0     01-Jan-2013   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for Escrypt RSA */
#include "Cry_EscRsaEncrypt.h"
/* Asymmetric Interface */
#if (CSM_ASYM_ENCRYPT_STATUS == STD_ON)
#if (CSM_ASYM_ESCRSAENCRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "callback.h"
#include "rsa.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry EscRsaEncrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Stores encryption key pointer in Escrypt RSA */
  const Csm_AsymPublicKeyType* pPublicKeyPtr;
  /* Stores plain data pointer used for encryption in Escrypt RSA */
  const uint8* pPlainTextPtr;
  /* Data length of the plain data used for encryption */
  uint32 ulPlainTextLength;
  /* Stores ciphered data pointer used for encryption in Escrypt RSA */
  uint8* pCipherTextPtr;
  /* Pointer of ciphered data length */
  uint32* pCipherTextLengthPtr;
} Cry_EscRsaEncryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Global structure variable for Escrypt RSA transfer buffer */
static Cry_EscRsaEncryptTransferBuffer Cry_GddEscRsaEncryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_EscRsaEncryptInit                                 **
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
** Remarks            : Global Variable(s):  Cry_GddEscRsaEncryptTb           **
**                                                                            **
**                     Function(s) invoked: None                              **
**                                                                            **
*******************************************************************************/
void Cry_EscRsaEncryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddEscRsaEncryptTb.ucJobState = NO_JOB;
  Cry_GddEscRsaEncryptTb.pPublicKeyPtr = NULL_PTR;
  Cry_GddEscRsaEncryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddEscRsaEncryptTb.ulPlainTextLength = CSM_ZERO;
  Cry_GddEscRsaEncryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddEscRsaEncryptTb.pCipherTextLengthPtr = NULL_PTR;
}

/*******************************************************************************
** Function Name        : Cry_EscRsaEncryptStart                              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Escrypt RSA, so that RSA is able     **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_EscRsaEncryptMainFunction() can process         **
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
**                        Cry_GddEscRsaEncryptTb                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_EscRsaEncryptInit                               **
*******************************************************************************/
Std_ReturnType Cry_EscRsaEncryptStart(const void* cfgPtr,
  const Csm_AsymPublicKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddEscRsaEncryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_EscRsaEncryptInit();

    Cry_GddEscRsaEncryptTb.ucJobState = JOB_START;

    if (Csm_AsymEncryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length != sizeof(Csm_EscRsaPublicKeyType))
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscRsaEncryptTb.pPublicKeyPtr = keyPtr;

        Cry_GddEscRsaEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscRsaEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscRsaEncryptTb.pPublicKeyPtr = keyPtr;
    }
  }
  else
  {
    /* Job is busy in processing other job, set the return value to CSM_E_BUSY */
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_EscRsaEncryptUpdate                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the RSA      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscRsaEncryptMainFunction() can process the     **
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
**                        Cry_GddEscRsaEncryptTb                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscRsa_ModExp, EscCallback_setFunction              **
*******************************************************************************/
Std_ReturnType Cry_EscRsaEncryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* plainTextPtr, uint32 plainTextLength, uint8* cipherTextPtr,
  uint32* cipherTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  const Csm_EscRsaPublicKeyType* LpEscRsaPubKey;
  uint8 LaaPlainText[EscRsa_KEY_BYTES];

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddEscRsaEncryptTb.ucJobState)
  {
    Cry_GddEscRsaEncryptTb.ucJobState = JOB_UPDATE;

    if (Csm_AsymEncryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*cipherTextLengthPtr < EscRsa_KEY_BYTES)
      {
        /* Result buffer too small to store the result */
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }
      else if (plainTextLength > EscRsa_KEY_BYTES)
      {
        /* Plaintext length must not bigger than RSA key size */
        LddReturnValue = E_NOT_OK;
      }
      else
      {
        LpEscRsaPubKey = (const Csm_EscRsaPublicKeyType*)
          ((const void*)(Cry_GddEscRsaEncryptTb.pPublicKeyPtr->data));

        (void)memset((void*)LaaPlainText, 0x00, sizeof(LaaPlainText));
        /* polyspace +1 MISRA-C3:D4.11 RTE:STD_LIB [Justified:Low] "The input is checked" */
        (void)memcpy((void*)LaaPlainText, (const void*)plainTextPtr, plainTextLength);

        EscCallback_setFunction(NULL_PTR);
        /* polyspace +3 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        LblReturnValue = EscRsa_ModExp(LaaPlainText,
          LpEscRsaPubKey->modulus,
          LpEscRsaPubKey->exponent,
          cipherTextPtr);

        if (LblReturnValue == CSM_TRUE)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscRsaEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscRsaEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscRsaEncryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddEscRsaEncryptTb.ulPlainTextLength = plainTextLength;
      Cry_GddEscRsaEncryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddEscRsaEncryptTb.pCipherTextLengthPtr = cipherTextLengthPtr;
    }
  }
  else
  {
    /* Job process is still not complete, return CSM_E_BUSY */
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_EscRsaEncryptFinish                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the RSA     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscRsaEncryptMainFunction() can finish the      **
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
**                        Cry_GddEscRsaEncryptTb                              **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
Std_ReturnType Cry_EscRsaEncryptFinish(Csm_ConfigIdType cfgId,
  uint8* cipherTextPtr, uint32* cipherTextLengthPtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);
  CSM_PARAM_UNUSED_PTR(cipherTextPtr);
  CSM_PARAM_UNUSED_PTR(cipherTextLengthPtr);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddEscRsaEncryptTb.ucJobState)
  {
    Cry_GddEscRsaEncryptTb.ucJobState = JOB_FINISH;

    if (Csm_AsymEncryptServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddEscRsaEncryptTb.ucJobState = NO_JOB;
    }
  }
  else
  {
    /* Job process is still not complete, return CSM_E_BUSY */
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_EscRsaEncryptMainFunction                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_AsymEncryptCallbackNotification() with the      **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by Cry_EscRsaEncryptStart()      **
**                        or Cry_EscRsaEncryptUpdate(). For                   **
**                        Cry_EscRsaEncryptFinish invocation of               **
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
**                        Cry_GddEscRsaEncryptTb                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_AsymEncryptCallbackNotification,                **
**                        EscRsa_ModExp, EscCallback_setFunction,             **
**                        Csm_AsymEncryptServiceFinishNotification            **
*******************************************************************************/
void Cry_EscRsaEncryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  const Csm_EscRsaPublicKeyType* LpEscRsaPubKey;
  uint8 LaaPlainText[EscRsa_KEY_BYTES];

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* State machine of RSA job processing */
  switch (Cry_GddEscRsaEncryptTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (Cry_GddEscRsaEncryptTb.pPublicKeyPtr->length
      != sizeof(Csm_EscRsaPublicKeyType))
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscRsaEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscRsaEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_AsymEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (*(Cry_GddEscRsaEncryptTb.pCipherTextLengthPtr) < EscRsa_KEY_BYTES)
    {
      /* Result buffer too small to store the result */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }
    else if (Cry_GddEscRsaEncryptTb.ulPlainTextLength > EscRsa_KEY_BYTES)
    {
      /* Plaintext length must not bigger than RSA key size */
      LddReturnValue = E_NOT_OK;
    }
    else
    {
      LpEscRsaPubKey = (const Csm_EscRsaPublicKeyType*)
        ((const void*)(Cry_GddEscRsaEncryptTb.pPublicKeyPtr->data));

      (void)memset((void*)LaaPlainText, 0x00, sizeof(LaaPlainText));
      /* polyspace +1 MISRA-C3:D4.11 RTE:STD_LIB [Justified:Low] "The input is checked" */
      memcpy((void*)LaaPlainText, (const void*)(Cry_GddEscRsaEncryptTb.pPlainTextPtr),
        Cry_GddEscRsaEncryptTb.ulPlainTextLength);

      EscCallback_setFunction(NULL_PTR);
      /* polyspace +3 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      LblReturnValue = EscRsa_ModExp(LaaPlainText,
        LpEscRsaPubKey->modulus,
        LpEscRsaPubKey->exponent,
        Cry_GddEscRsaEncryptTb.pCipherTextPtr);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscRsaEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscRsaEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_AsymEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddEscRsaEncryptTb.ucJobState = NO_JOB;

    /* Notify respective Service about the completion of the task */
    Csm_AsymEncryptCallbackNotification(LddReturnValue);
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

#endif /* (CSM_ASYM_ESCRSAENCRYPT == STD_ON) */
#endif /* (CSM_ASYM_ENCRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
