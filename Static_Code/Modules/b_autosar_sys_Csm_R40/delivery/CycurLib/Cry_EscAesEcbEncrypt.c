/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_EscAesEcbEncrypt.c                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Escrypt AES - ECB Encrypt Interface     **
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
#include "Cry_EscAesEcbEncrypt.h"
/* Symmetric Interface */
#if (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON)
#if (CSM_SYMBLOCK_ESCAESECBENCRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "aes_ecb.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry EscAesEcbEncrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Stores encryption key pointer in Escrypt AES ECB */
  const Csm_SymKeyType* pKeyPtr;
  /* Stores plain data pointer used for encryption in Escrypt AES ECB */
  const uint8* pPlainTextPtr;
  /* Data length of the plain data used for encryption */
  uint32 ulPlainTextLength;
  /* Stores ciphered data pointer used for encryption in Escrypt AES ECB */
  uint8* pCipherTextPtr;
  /* Pointer of ciphered data length */
  uint32* pCipherTextLengthPtr;
} Cry_EscAesEcbEncryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* AES primitive library context */
static EscAesEcb_ContextT Cry_GddEscAesEcbEncryptContext;

/* Global structure variable for Escrypt AES ECB transfer buffer */
static Cry_EscAesEcbEncryptTransferBuffer Cry_GddEscAesEcbEncryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_EscAesEcbEncryptInit                              **
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
** Remarks            : Global Variable(s):  Cry_GddEscAesEcbEncryptTb        **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_EscAesEcbEncryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddEscAesEcbEncryptTb.ucJobState = NO_JOB;
  Cry_GddEscAesEcbEncryptTb.pKeyPtr = NULL_PTR;
  Cry_GddEscAesEcbEncryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddEscAesEcbEncryptTb.ulPlainTextLength = CSM_ZERO;
  Cry_GddEscAesEcbEncryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddEscAesEcbEncryptTb.pCipherTextLengthPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddEscAesEcbEncryptContext, 0x00, sizeof(EscAesEcb_ContextT));
}

/*******************************************************************************
** Function Name        : Cry_EscAesEcbEncryptStart                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Escrypt AES ECB, so that AES is able **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_EscAesEcbEncryptMainFunction() can process      **
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
**                        Cry_GddEscAesEcbEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_EscAesEcbEncryptInit, EscAesEcb_Init            **
*******************************************************************************/
Std_ReturnType Cry_EscAesEcbEncryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddEscAesEcbEncryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_EscAesEcbEncryptInit();

    Cry_GddEscAesEcbEncryptTb.ucJobState = JOB_START;

    if (Csm_SymBlockEncryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length != EscAes_KEY_BYTES)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LblReturnValue = EscAesEcb_Init(&Cry_GddEscAesEcbEncryptContext,
          (const uint8*)((const void*)(keyPtr->data)));

        if (LblReturnValue == CSM_TRUE)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscAesEcbEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscAesEcbEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscAesEcbEncryptTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_EscAesEcbEncryptUpdate                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the AES      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscAesEcbEncryptMainFunction() can process the  **
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
**                        Cry_GddEscAesEcbEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscAesEcb_Encrypt                                   **
*******************************************************************************/
Std_ReturnType Cry_EscAesEcbEncryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* plainTextPtr, uint32 plainTextLength, uint8* cipherTextPtr,
  uint32* cipherTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddEscAesEcbEncryptTb.ucJobState)
  {
    Cry_GddEscAesEcbEncryptTb.ucJobState = JOB_UPDATE;

    if (Csm_SymBlockEncryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*cipherTextLengthPtr < plainTextLength)
      {
        /* Buffer size is invalid */
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if ((plainTextLength < EscAes_KEY_BYTES)
        || ((plainTextLength % EscAes_KEY_BYTES) != CSM_ZERO))
      {
        /* plainTextLength should be multiples of 16 */
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        *cipherTextLengthPtr = CSM_ZERO;
        /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The array length is checked" */
        for (LulIndex = CSM_ZERO;
          LulIndex < (plainTextLength / EscAes_KEY_BYTES); LulIndex++)
        {
          /* polyspace +3 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          LblReturnValue = EscAesEcb_Encrypt(&Cry_GddEscAesEcbEncryptContext,
            &(plainTextPtr[EscAes_KEY_BYTES * LulIndex]),
            &(cipherTextPtr[EscAes_KEY_BYTES * LulIndex]));

          if (LblReturnValue != CSM_TRUE)
          {
            *cipherTextLengthPtr += EscAes_KEY_BYTES;
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
        Cry_GddEscAesEcbEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscAesEcbEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscAesEcbEncryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddEscAesEcbEncryptTb.ulPlainTextLength = plainTextLength;
      Cry_GddEscAesEcbEncryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddEscAesEcbEncryptTb.pCipherTextLengthPtr = cipherTextLengthPtr;
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
** Function Name        : Cry_EscAesEcbEncryptFinish                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the AES     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscAesEcbEncryptMainFunction() can finish the   **
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
**                        Cry_GddEscAesEcbEncryptTb                           **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
Std_ReturnType Cry_EscAesEcbEncryptFinish(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddEscAesEcbEncryptTb.ucJobState)
  {
    /* Set the job state to JOB_FINISH */
    Cry_GddEscAesEcbEncryptTb.ucJobState = JOB_FINISH;

    if (Csm_SymBlockEncryptServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddEscAesEcbEncryptTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_EscAesEcbEncryptMainFunction                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SymBlockEncryptCallbackNotification() with the  **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by Cry_EscAesEcbEncryptStart()   **
**                        or Cry_EscAesEcbEncryptUpdate(). For                **
**                        Cry_EscAesEcbEncryptFinish invocation of            **
**                        Csm_SymBlockEncryptCallbackNotification()           **
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
**                        Cry_GddEscAesEcbEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscAesEcb_Init,                                     **
**                        EscAesEcb_Encrypt,                                  **
**                        Csm_SymBlockEncryptCallbackNotification,            **
**                        Csm_SymBlockEncryptServiceFinishNotification        **
*******************************************************************************/
void Cry_EscAesEcbEncryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddEscAesEcbEncryptTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (Cry_GddEscAesEcbEncryptTb.pKeyPtr->length != EscAes_KEY_BYTES)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LblReturnValue = EscAesEcb_Init(&Cry_GddEscAesEcbEncryptContext,
        (const uint8*)((const void*)(Cry_GddEscAesEcbEncryptTb.pKeyPtr->data)));

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscAesEcbEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscAesEcbEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymBlockEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (*(Cry_GddEscAesEcbEncryptTb.pCipherTextLengthPtr)
      < Cry_GddEscAesEcbEncryptTb.ulPlainTextLength)
    {
      /* Buffer size is invalid */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if ((Cry_GddEscAesEcbEncryptTb.ulPlainTextLength < EscAes_KEY_BYTES)
      || ((Cry_GddEscAesEcbEncryptTb.ulPlainTextLength % EscAes_KEY_BYTES) != CSM_ZERO))
    {
      /* plainTextLength should be multiples of 16 */
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      *(Cry_GddEscAesEcbEncryptTb.pCipherTextLengthPtr) = CSM_ZERO;

      for (LulIndex = CSM_ZERO; LulIndex <
        (Cry_GddEscAesEcbEncryptTb.ulPlainTextLength / EscAes_KEY_BYTES);
        LulIndex++)
      {
        LblReturnValue = EscAesEcb_Encrypt(&Cry_GddEscAesEcbEncryptContext,
          &(Cry_GddEscAesEcbEncryptTb.pPlainTextPtr[EscAes_KEY_BYTES * LulIndex]),
          &(Cry_GddEscAesEcbEncryptTb.pCipherTextPtr[EscAes_KEY_BYTES * LulIndex]));

        if (LblReturnValue != CSM_TRUE)
        {
          *(Cry_GddEscAesEcbEncryptTb.pCipherTextLengthPtr)
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
      Cry_GddEscAesEcbEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscAesEcbEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymBlockEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddEscAesEcbEncryptTb.ucJobState = NO_JOB;

    /* Notify respective Service about the completion of the task */
    Csm_SymBlockEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_SymBlockEncryptServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_SYMBLOCK_ESCAESECBENCRYPT == STD_ON) */
#endif /* (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
