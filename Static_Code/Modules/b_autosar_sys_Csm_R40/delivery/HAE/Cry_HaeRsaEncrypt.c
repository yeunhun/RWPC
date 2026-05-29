/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeRsaEncrypt.c                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Autoever RSA Encrypt Interface          **
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
#include "Cry_HaeRsaEncrypt.h"
/* Asymmetric Interface */
#if (CSM_ASYM_ENCRYPT_STATUS == STD_ON)
#if (CSM_ASYM_HAERSAENCRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "Hmg_Rsa.h"
#include "string.h"
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HaeRsaEncrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Stores encryption key pointer in Autoever RSA */
  const Csm_AsymPublicKeyType* pPublicKeyPtr;
  /* Stores plain data pointer used for encryption in Autoever RSA */
  const uint8* pPlainTextPtr;
  /* Data length of the plain data used for encryption */
  uint32 ulPlainTextLength;
  /* Stores ciphered data pointer used for encryption in Autoever RSA */
  uint8* pCipherTextPtr;
  /* Pointer of ciphered data length */
  uint32* pCipherTextLengthPtr;
} Cry_HaeRsaEncryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

static uint8 Cry_GaaHaeRsaEncryptPublickeyModulus[HMG_RSA_BYTES_SIZE];

#define CSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static HmgRsaPublickey Cry_GddHaeRsaEncryptPublickey;

/* Global structure variable for Autoever RSA transfer buffer */
static Cry_HaeRsaEncryptTransferBuffer Cry_GddHaeRsaEncryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeRsaEncryptInit                                 **
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
** Remarks            : Global Variable(s):  Cry_GddHaeRsaEncryptTb           **
**                                                                            **
**                     Function(s) invoked: None                              **
**                                                                            **
*******************************************************************************/
void Cry_HaeRsaEncryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeRsaEncryptTb.ucJobState = NO_JOB;
  Cry_GddHaeRsaEncryptTb.pPublicKeyPtr = NULL_PTR;
  Cry_GddHaeRsaEncryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddHaeRsaEncryptTb.ulPlainTextLength = CSM_ZERO;
  Cry_GddHaeRsaEncryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddHaeRsaEncryptTb.pCipherTextLengthPtr = NULL_PTR;

  (void)memset((void*)&Cry_GaaHaeRsaEncryptPublickeyModulus, 0x00, HMG_RSA_BYTES_SIZE);

  Cry_GddHaeRsaEncryptPublickey.modulus = Cry_GaaHaeRsaEncryptPublickeyModulus;
  Cry_GddHaeRsaEncryptPublickey.exponent = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_HaeRsaEncryptStart                              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Autoever RSA, so that RSA is able    **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeRsaEncryptMainFunction() can process         **
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
**                        Cry_GddHaeRsaEncryptTb                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_HaeRsaEncryptInit                               **
*******************************************************************************/
Std_ReturnType Cry_HaeRsaEncryptStart(const void* cfgPtr,
  const Csm_AsymPublicKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddHaeRsaEncryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_HaeRsaEncryptInit();

    Cry_GddHaeRsaEncryptTb.ucJobState = JOB_START;

    if (Csm_AsymEncryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length != (HMG_RSA_BYTES_SIZE + sizeof(uint32)))
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        (void)memcpy((void*)&Cry_GaaHaeRsaEncryptPublickeyModulus[0U],
          (const void*)(keyPtr->data),
          HMG_RSA_BYTES_SIZE);

        Cry_GddHaeRsaEncryptPublickey.exponent
          #if (defined(HIGH_BYTE_FIRST) && (CPU_BYTE_ORDER == HIGH_BYTE_FIRST))
          = ((uint32)(keyPtr->data[HMG_RSA_BYTES_SIZE]) << 24)
          + ((uint32)(keyPtr->data[HMG_RSA_BYTES_SIZE + 1]) << 16)
          + ((uint32)(keyPtr->data[HMG_RSA_BYTES_SIZE + 2]) << 8)
          + (uint32)(keyPtr->data[HMG_RSA_BYTES_SIZE + 3]);
          #else
          = (uint32)(keyPtr->data[HMG_RSA_BYTES_SIZE])
          + ((uint32)(keyPtr->data[HMG_RSA_BYTES_SIZE + 1]) << 8)
          + ((uint32)(keyPtr->data[HMG_RSA_BYTES_SIZE + 2]) << 16)
          + ((uint32)(keyPtr->data[HMG_RSA_BYTES_SIZE + 3]) << 24);
          #endif

        Cry_GddHaeRsaEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeRsaEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeRsaEncryptTb.pPublicKeyPtr = keyPtr;
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
** Function Name        : Cry_HaeRsaEncryptUpdate                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the RSA      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeRsaEncryptMainFunction() can process the     **
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
**                        Cry_GddHaeRsaEncryptTb                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_RsaModExponent, Hmg_SetCallbackFunc             **
*******************************************************************************/
Std_ReturnType Cry_HaeRsaEncryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* plainTextPtr, uint32 plainTextLength, uint8* cipherTextPtr,
  uint32* cipherTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LaaPlainText[HMG_RSA_BYTES_SIZE];

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddHaeRsaEncryptTb.ucJobState)
  {
    Cry_GddHaeRsaEncryptTb.ucJobState = JOB_UPDATE;

    if (Csm_AsymEncryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*cipherTextLengthPtr < HMG_RSA_BYTES_SIZE)
      {
        /* Result buffer too small to store the result */
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }
      else if (plainTextLength > HMG_RSA_BYTES_SIZE)
      {
        /* Plaintext length must not bigger than RSA key size */
        LddReturnValue = E_NOT_OK;
      }
      else
      {
        /* polyspace +3 MISRA-C3:D4.11 RTE:STD_LIB [Justified:Low] "The input is checked" */
	      /* polyspace +3 MISRA-C3:18.1,D4.1,D4.11,21.15 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
        (void)memset((void*)LaaPlainText, 0x00, sizeof(LaaPlainText));
        (void)memcpy((void*)LaaPlainText, (const void*)plainTextPtr, plainTextLength);

        #ifdef HMG_ENABLE_CALLBACK
        Hmg_SetCallbackFunc(NULL_PTR);
        #endif

        LblReturnValue = Hmg_RsaModExponent(cipherTextPtr,
          LaaPlainText,
          &Cry_GddHaeRsaEncryptPublickey);

        if (LblReturnValue == CSM_TRUE)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeRsaEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeRsaEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeRsaEncryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddHaeRsaEncryptTb.ulPlainTextLength = plainTextLength;
      Cry_GddHaeRsaEncryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddHaeRsaEncryptTb.pCipherTextLengthPtr = cipherTextLengthPtr;
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
** Function Name        : Cry_HaeRsaEncryptFinish                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the RSA     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeRsaEncryptMainFunction() can finish the      **
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
**                        Cry_GddHaeRsaEncryptTb                              **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
Std_ReturnType Cry_HaeRsaEncryptFinish(Csm_ConfigIdType cfgId,
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
  if (JOB_DONE == Cry_GddHaeRsaEncryptTb.ucJobState)
  {
    Cry_GddHaeRsaEncryptTb.ucJobState = JOB_FINISH;

    if (Csm_AsymEncryptServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeRsaEncryptTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_HaeRsaEncryptMainFunction                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_AsymEncryptCallbackNotification() with the      **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by Cry_HaeRsaEncryptStart()      **
**                        or Cry_HaeRsaEncryptUpdate(). For                   **
**                        Cry_HaeRsaEncryptFinish invocation of               **
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
**                        Cry_GddHaeRsaEncryptTb                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_AsymEncryptCallbackNotification,                **
**                        Hmg_RsaModExponent, Hmg_SetCallbackFunc,            **
**                        Csm_AsymEncryptServiceFinishNotification            **
*******************************************************************************/
void Cry_HaeRsaEncryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LaaPlainText[HMG_RSA_BYTES_SIZE];

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* State machine of RSA job processing */
  switch (Cry_GddHaeRsaEncryptTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddHaeRsaEncryptTb.pPublicKeyPtr->length
      != (HMG_RSA_BYTES_SIZE + sizeof(uint32)))
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      (void)memcpy((void*)Cry_GaaHaeRsaEncryptPublickeyModulus,
        (const void*)(Cry_GddHaeRsaEncryptTb.pPublicKeyPtr->data),
        HMG_RSA_BYTES_SIZE);

      Cry_GddHaeRsaEncryptPublickey.exponent
        #if (defined(HIGH_BYTE_FIRST) && (CPU_BYTE_ORDER == HIGH_BYTE_FIRST))
        = ((uint32)(Cry_GddHaeRsaEncryptTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE]) << 24)
        + ((uint32)(Cry_GddHaeRsaEncryptTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE + 1]) << 16)
        + ((uint32)(Cry_GddHaeRsaEncryptTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE + 2]) << 8)
        + (uint32)(Cry_GddHaeRsaEncryptTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE + 3]);
        #else
        = (uint32)(Cry_GddHaeRsaEncryptTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE])
        + ((uint32)(Cry_GddHaeRsaEncryptTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE + 1]) << 8)
        + ((uint32)(Cry_GddHaeRsaEncryptTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE + 2]) << 16)
        + ((uint32)(Cry_GddHaeRsaEncryptTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE + 3]) << 24);
        #endif

      Cry_GddHaeRsaEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeRsaEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_AsymEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (*(Cry_GddHaeRsaEncryptTb.pCipherTextLengthPtr) < HMG_RSA_BYTES_SIZE)
    {
      /* Result buffer too small to store the result */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }
    else if (Cry_GddHaeRsaEncryptTb.ulPlainTextLength > HMG_RSA_BYTES_SIZE)
    {
      /* Plaintext length must not bigger than RSA key size */
      LddReturnValue = E_NOT_OK;
    }
    else
    {
      /* polyspace +4 MISRA-C3:D4.11 [Justified:Low] "No Impact of this rule violation" */
      /* polyspace +3 MISRA-C3:18.1,D4.1,D4.11,21.15 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
      /* polyspace +2 RTE:STD_LIB [Justified:Low] "No Impact of this rule violation" */
      (void)memset((void*)LaaPlainText, 0x00, sizeof(LaaPlainText));
      (void)memcpy((void*)LaaPlainText, (const void*)Cry_GddHaeRsaEncryptTb.pPlainTextPtr,
        Cry_GddHaeRsaEncryptTb.ulPlainTextLength);

      #ifdef HMG_ENABLE_CALLBACK
      Hmg_SetCallbackFunc(NULL_PTR);
      #endif

      LblReturnValue = Hmg_RsaModExponent(Cry_GddHaeRsaEncryptTb.pCipherTextPtr,
        LaaPlainText, &Cry_GddHaeRsaEncryptPublickey);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeRsaEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeRsaEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_AsymEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaeRsaEncryptTb.ucJobState = NO_JOB;

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

#endif /* (CSM_ASYM_HAERSAENCRYPT == STD_ON) */
#endif /* (CSM_ASYM_ENCRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
