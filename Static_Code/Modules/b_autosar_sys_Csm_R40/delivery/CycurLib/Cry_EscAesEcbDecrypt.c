/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_EscAesEcbDecrypt.c                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Escrypt AES - ECB Decrypt Interface     **
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
** 1.0.8     09-Aug-2016   Sinil        Redmine #5693, #5695                  **
** 1.0.7     12-Jul-2016   Sinil        Redmine #5514                         **
** 1.0.6     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.5     16-May-2016   Sinil        Redmine #4903                         **
** 1.0.4     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.3     02-May-2016   Sinil        Redmine #4607                         **
** 1.0.2     05-Jan-2016   Sinil        Use const macro                       **
** 1.0.1     02-Dec-2015   Sinil        1. Fix to process multi blocks        **
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
/* Header File for Escrypt AES ECB */
#include "Cry_EscAesEcbDecrypt.h"
/* Symmetric Interface */
#if (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON)
#if (CSM_SYMBLOCK_ESCAESECBDECRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "aes_ecb.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry EscAesEcbDecrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Stores decryption key pointer in Escrypt AES ECB */
  const Csm_SymKeyType* pKeyPtr;
  /* Stores ciphered data pointer used for decryption in Escrypt AES ECB */
  const uint8* pCipherTextPtr;
  /* Data length of the ciphered data used for decryption */
  uint32 ulCipherTextLength;
  /* Stores plain data pointer used for encryption in Escrypt AES ECB */
  uint8* pPlainTextPtr;
  /* Data length of the plain data used for encryption */
  uint32* pPlainTextLengthPtr;
} Cry_EscAesEcbDecryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* AES primitive library context */
static EscAesEcb_ContextT Cry_GddEscAesEcbDecryptContext;

/* Global structure variable for Escrypt AES ECB transfer buffer */
static Cry_EscAesEcbDecryptTransferBuffer Cry_GddEscAesEcbDecryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_EscAesEcbDecryptInit                              **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the AES module.              **
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
** Remarks            : Global Variable(s):  Cry_GddEscAesEcbDecryptTb        **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_EscAesEcbDecryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddEscAesEcbDecryptTb.ucJobState = NO_JOB;
  Cry_GddEscAesEcbDecryptTb.pKeyPtr = NULL_PTR;
  Cry_GddEscAesEcbDecryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddEscAesEcbDecryptTb.ulCipherTextLength = CSM_ZERO;
  Cry_GddEscAesEcbDecryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddEscAesEcbDecryptTb.pPlainTextLengthPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddEscAesEcbDecryptContext, 0x00, sizeof(EscAesEcb_ContextT));
}

/*******************************************************************************
** Function Name        : Cry_EscAesEcbDecryptStart                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Escrypt AES ECB, so that AES is able **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_EscAesEcbDecryptMainFunction() can process      **
**                        initialisation                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgPtr, keyPtr, InitVectorPtr, InitVectorLength     **
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
**                        Cry_GddEscAesEcbDecryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_EscAesEcbDecryptInit, EscAesEcb_Init            **
*******************************************************************************/
Std_ReturnType Cry_EscAesEcbDecryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddEscAesEcbDecryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_EscAesEcbDecryptInit();

    Cry_GddEscAesEcbDecryptTb.ucJobState = JOB_START;

    if (Csm_SymBlockDecryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length != EscAes_KEY_BYTES)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LblReturnValue = EscAesEcb_Init(&Cry_GddEscAesEcbDecryptContext,
          (const uint8*)((const void*)(keyPtr->data)));

        if (LblReturnValue == CSM_TRUE)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscAesEcbDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscAesEcbDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscAesEcbDecryptTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_EscAesEcbDecryptUpdate                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the AES      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscAesEcbDecryptMainFunction() can process the  **
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
**                        Cry_GddEscAesEcbDecryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscAesEcb_Decrypt                                   **
*******************************************************************************/
Std_ReturnType Cry_EscAesEcbDecryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* cipherTextPtr, uint32 cipherTextLength, uint8* plainTextPtr,
  uint32 *plainTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddEscAesEcbDecryptTb.ucJobState)
  {
    Cry_GddEscAesEcbDecryptTb.ucJobState = JOB_UPDATE;

    if (Csm_SymBlockDecryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*plainTextLengthPtr < cipherTextLength)
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if ((cipherTextLength < EscAes_KEY_BYTES)
        || ((cipherTextLength % EscAes_KEY_BYTES) != CSM_ZERO))
      {
        /* cipherTextLength should be multiples of 16 */
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        *plainTextLengthPtr = CSM_ZERO;

        /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The length is checked" */
        for (LulIndex = CSM_ZERO;
          LulIndex < (cipherTextLength / EscAes_KEY_BYTES); LulIndex++)
        {
          /* polyspace +3 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          LblReturnValue = EscAesEcb_Decrypt(&Cry_GddEscAesEcbDecryptContext,
            &(cipherTextPtr[EscAes_KEY_BYTES * LulIndex]),
            &(plainTextPtr[EscAes_KEY_BYTES * LulIndex]));

          if (LblReturnValue != CSM_TRUE)
          {
            *plainTextLengthPtr += EscAes_KEY_BYTES;
          }
          else
          {
            LddReturnValue = E_NOT_OK;
            break;
          }
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscAesEcbDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscAesEcbDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscAesEcbDecryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddEscAesEcbDecryptTb.ulCipherTextLength = cipherTextLength;
      Cry_GddEscAesEcbDecryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddEscAesEcbDecryptTb.pPlainTextLengthPtr = plainTextLengthPtr;
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
** Function Name        : Cry_EscAesEcbDecryptFinish                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the AES     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscAesEcbDecryptMainFunction() can finish the   **
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
**                        Cry_GddEscAesEcbDecryptTb                           **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
Std_ReturnType Cry_EscAesEcbDecryptFinish(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddEscAesEcbDecryptTb.ucJobState)
  {
    Cry_GddEscAesEcbDecryptTb.ucJobState = JOB_FINISH;

    if (Csm_SymBlockDecryptServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddEscAesEcbDecryptTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_EscAesEcbDecryptMainFunction                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SymBlockDecryptCallbackNotification() with the  **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by Cry_EscAesEcbDecryptStart()   **
**                        or Cry_EscAesEcbDecryptUpdate(). For                **
**                        Cry_EscAesEcbDecryptFinish invocation of            **
**                        Csm_SymBlockDecryptCallbackNotification()           **
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
** Preconditions        : Primitive should have been successfuly initialized **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddEscAesEcbDecryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscAesEcb_Init                                      **
**                        EscAesEcb_Decrypt                                   **
**                        Csm_SymBlockDecryptCallbackNotification,            **
**                        Csm_SymBlockDecryptServiceFinishNotification        **
*******************************************************************************/
void Cry_EscAesEcbDecryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddEscAesEcbDecryptTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (Cry_GddEscAesEcbDecryptTb.pKeyPtr->length != EscAes_KEY_BYTES)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LblReturnValue = EscAesEcb_Init(&Cry_GddEscAesEcbDecryptContext,
        (const uint8*)((const void*)(Cry_GddEscAesEcbDecryptTb.pKeyPtr->data)));

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscAesEcbDecryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscAesEcbDecryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymBlockDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (*(Cry_GddEscAesEcbDecryptTb.pPlainTextLengthPtr)
      < Cry_GddEscAesEcbDecryptTb.ulCipherTextLength)
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if ((Cry_GddEscAesEcbDecryptTb.ulCipherTextLength < EscAes_KEY_BYTES)
      || ((Cry_GddEscAesEcbDecryptTb.ulCipherTextLength % EscAes_KEY_BYTES) != CSM_ZERO))
    {
      /* cipherTextLength should be multiples of 16 */
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      *(Cry_GddEscAesEcbDecryptTb.pPlainTextLengthPtr) = CSM_ZERO;

      for (LulIndex = CSM_ZERO; LulIndex < (Cry_GddEscAesEcbDecryptTb.ulCipherTextLength
        / EscAes_KEY_BYTES); LulIndex++)
      {
        LblReturnValue = EscAesEcb_Decrypt(&Cry_GddEscAesEcbDecryptContext,
          &(Cry_GddEscAesEcbDecryptTb.pCipherTextPtr[EscAes_KEY_BYTES * LulIndex]),
          &(Cry_GddEscAesEcbDecryptTb.pPlainTextPtr[EscAes_KEY_BYTES * LulIndex]));

        if (LblReturnValue != CSM_TRUE)
        {
          *(Cry_GddEscAesEcbDecryptTb.pPlainTextLengthPtr)
            += EscAes_KEY_BYTES;
        }
        else
        {
          LddReturnValue = E_NOT_OK;
          break;
        }
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscAesEcbDecryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscAesEcbDecryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymBlockDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddEscAesEcbDecryptTb.ucJobState = NO_JOB;

    /* Notify respective Service about the completion of the task */
    Csm_SymBlockDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_SymBlockDecryptServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_SYMBLOCK_ESCAESECBDECRYPT == STD_ON) */
#endif /* (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
