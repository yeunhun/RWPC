/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeRsaDecrypt.c                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Autoever RSA Decrypt Interface          **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 2.6.3.0   24-Mar-2021   TamTV6       Redmine #18165                        **
** 2.6.1.0   08-Oct-2020   JaeHyun      Redmine #25964                        **
** 1.0.1     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.0     13-Feb-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for Autoever RSA */
#include "Cry_HaeRsaDecrypt.h"
/* Asymmetric Interface */
#if (CSM_ASYM_DECRYPT_STATUS == STD_ON)
#if (CSM_ASYM_HAERSADECRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "Hmg_Rsa.h"
#include "string.h"
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HaeRsaDecrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Stores decryption key pointer in Autoever RSA */
  const Csm_AsymPrivateKeyType* pPrivateKeyPtr;
  /* Stores ciphered data pointer used for decryption in Autoever RSA */
  const uint8* pCipherTextPtr;
  /* Data length of the ciphered data used for decryption */
  uint32 ulCipherTextLength;
  /* Stores plain data pointer used for encryption in Autoever RSA */
  uint8* pPlainTextPtr;
  /* Data length of the plain data used for encryption */
  uint32* pPlainTextLengthPtr;
} Cry_HaeRsaDecryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

static uint8 Cry_GaaHaeRsaEncryptPrivatekeyModulus[HMG_RSA_BYTES_SIZE];
static uint8 Cry_GaaHaeRsaEncryptPrivatekeyExponent[HMG_RSA_BYTES_SIZE];

#define CSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static HmgRsaPrivatekey Cry_GddHaeRsaDecryptPrivatekey;

/* Global structure variable for Autoever RSA transfer buffer */
static Cry_HaeRsaDecryptTransferBuffer Cry_GddHaeRsaDecryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeRsaDecryptInit                                 **
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
** Remarks            : Global Variable(s):  Cry_GddHaeRsaDecryptTb           **
**                                                                            **
**                     Function(s) invoked: None                              **
**                                                                            **
*******************************************************************************/
void Cry_HaeRsaDecryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeRsaDecryptTb.ucJobState = NO_JOB;
  Cry_GddHaeRsaDecryptTb.pPrivateKeyPtr = NULL_PTR;
  Cry_GddHaeRsaDecryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddHaeRsaDecryptTb.ulCipherTextLength = CSM_ZERO;
  Cry_GddHaeRsaDecryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddHaeRsaDecryptTb.pPlainTextLengthPtr = NULL_PTR;

  (void)memset((void*)&Cry_GaaHaeRsaEncryptPrivatekeyModulus, 0x00, HMG_RSA_BYTES_SIZE);
  (void)memset((void*)&Cry_GaaHaeRsaEncryptPrivatekeyExponent, 0x00, HMG_RSA_BYTES_SIZE);

  Cry_GddHaeRsaDecryptPrivatekey.modulus = Cry_GaaHaeRsaEncryptPrivatekeyModulus;
  Cry_GddHaeRsaDecryptPrivatekey.exponent = Cry_GaaHaeRsaEncryptPrivatekeyExponent;
}

/*******************************************************************************
** Function Name        : Cry_HaeRsaDecryptStart                              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Autoever RSA, so that RSA is able    **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeRsaDecryptMainFunction() can process         **
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
**                        Cry_GddHaeRsaDecryptTb                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_HaeRsaDecryptInit                               **
*******************************************************************************/
Std_ReturnType Cry_HaeRsaDecryptStart(const void* cfgPtr,
  const Csm_AsymPrivateKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddHaeRsaDecryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_HaeRsaDecryptInit();

    Cry_GddHaeRsaDecryptTb.ucJobState = JOB_START;

    if (Csm_AsymDecryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length != (HMG_RSA_BYTES_SIZE * CSM_TWO))
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        (void)memcpy((void*)&Cry_GaaHaeRsaEncryptPrivatekeyModulus[0U],
          (const void*)keyPtr->data,
          HMG_RSA_BYTES_SIZE);
        (void)memcpy((void*)&Cry_GaaHaeRsaEncryptPrivatekeyExponent[0U],
          (const void*)(&(keyPtr->data[HMG_RSA_BYTES_SIZE])),
          HMG_RSA_BYTES_SIZE);

        Cry_GddHaeRsaDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeRsaDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeRsaDecryptTb.pPrivateKeyPtr = keyPtr;
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
** Function Name        : Cry_HaeRsaDecryptUpdate                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the RSA      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeRsaDecryptMainFunction() can process the     **
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
**                        Cry_GddHaeRsaDecryptTb                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_RsaModExponentLong, Hmg_SetCallbackFunc         **
*******************************************************************************/
Std_ReturnType Cry_HaeRsaDecryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* cipherTextPtr, uint32 cipherTextLength, uint8* plainTextPtr,
  uint32* plainTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LaaPlainText[HMG_RSA_BYTES_SIZE];

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddHaeRsaDecryptTb.ucJobState)
  {
    Cry_GddHaeRsaDecryptTb.ucJobState = JOB_UPDATE;

    if (Csm_AsymDecryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*plainTextLengthPtr > HMG_RSA_BYTES_SIZE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        (void)memset((void*)LaaPlainText, 0x00, sizeof(LaaPlainText));

        #ifdef HMG_ENABLE_CALLBACK
        Hmg_SetCallbackFunc(NULL_PTR);
        #endif

        LblReturnValue = Hmg_RsaModExponentLong(LaaPlainText,
          cipherTextPtr,
          &Cry_GddHaeRsaDecryptPrivatekey);

        if (LblReturnValue == CSM_TRUE)
        {
          LddReturnValue = E_NOT_OK;
        }
        else
        {
          /* polyspace +1 MISRA-C3:D4.11 RTE:STD_LIB [Justified:Low] "The input is checked" */
          (void)memcpy((void*)plainTextPtr, (const void*)LaaPlainText, *plainTextLengthPtr);
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeRsaDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeRsaDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeRsaDecryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddHaeRsaDecryptTb.ulCipherTextLength = cipherTextLength;
      Cry_GddHaeRsaDecryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddHaeRsaDecryptTb.pPlainTextLengthPtr = plainTextLengthPtr;
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
** Function Name        : Cry_HaeRsaDecryptFinish                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the RSA     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeRsaDecryptMainFunction() can finish the      **
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
**                        Cry_GddHaeRsaDecryptTb                              **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
Std_ReturnType Cry_HaeRsaDecryptFinish(Csm_ConfigIdType cfgId,
  uint8* plainTextPtr, uint32* plainTextLengthPtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);
  CSM_PARAM_UNUSED_PTR(plainTextPtr);
  CSM_PARAM_UNUSED_PTR(plainTextLengthPtr);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddHaeRsaDecryptTb.ucJobState)
  {
    Cry_GddHaeRsaDecryptTb.ucJobState = JOB_FINISH;

    if (Csm_AsymDecryptServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeRsaDecryptTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_HaeRsaDecryptMainFunction                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_AsymDecryptCallbackNotification() with the      **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by Cry_HaeRsaDecryptStart()      **
**                        or Cry_HaeRsaDecryptUpdate(). For                   **
**                        Cry_HaeRsaDecryptFinish invocation of               **
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
**                        Cry_GddHaeRsaDecryptTb                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_AsymDecryptCallbackNotification,                **
**                        Hmg_RsaModExponentLong, Hmg_SetCallbackFunc,        **
**                        Csm_AsymDecryptServiceFinishNotification            **
*******************************************************************************/
void Cry_HaeRsaDecryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LaaPlainText[HMG_RSA_BYTES_SIZE];

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddHaeRsaDecryptTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddHaeRsaDecryptTb.pPrivateKeyPtr->length
      != (HMG_RSA_BYTES_SIZE * CSM_TWO))
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      (void)memcpy((void*)Cry_GaaHaeRsaEncryptPrivatekeyModulus,
        (const void*)(Cry_GddHaeRsaDecryptTb.pPrivateKeyPtr->data),
        HMG_RSA_BYTES_SIZE);
      (void)memcpy((void*)Cry_GaaHaeRsaEncryptPrivatekeyExponent,
        (const void*)(&(Cry_GddHaeRsaDecryptTb.pPrivateKeyPtr->data[HMG_RSA_BYTES_SIZE])),
        HMG_RSA_BYTES_SIZE);

      Cry_GddHaeRsaDecryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeRsaDecryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_AsymDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (*(Cry_GddHaeRsaDecryptTb.pPlainTextLengthPtr) > HMG_RSA_BYTES_SIZE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      (void)memset((void*)LaaPlainText, 0x00, sizeof(LaaPlainText));

      #ifdef HMG_ENABLE_CALLBACK
      Hmg_SetCallbackFunc(NULL_PTR);
      #endif

      LblReturnValue = Hmg_RsaModExponentLong(LaaPlainText,
        Cry_GddHaeRsaDecryptTb.pCipherTextPtr,
        &Cry_GddHaeRsaDecryptPrivatekey);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }
      else
      {
        /* polyspace +3 MISRA-C3:D4.11 [Justified:Low] "No Impact of this rule violation" */
	      /* polyspace +3 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
	      /* polyspace +2 RTE:STD_LIB [Justified:Low] "No Impact of this rule violation" */
        (void)memcpy((void*)Cry_GddHaeRsaDecryptTb.pPlainTextPtr,
          (const void*)LaaPlainText, *(Cry_GddHaeRsaDecryptTb.pPlainTextLengthPtr));
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeRsaDecryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeRsaDecryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_AsymDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaeRsaDecryptTb.ucJobState = NO_JOB;

    /* Notify respective Service about the completion of the task */
    Csm_AsymDecryptCallbackNotification(LddReturnValue);
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

#endif /* (CSM_ASYM_HAERSADECRYPT == STD_ON) */
#endif /* (CSM_ASYM_DECRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
