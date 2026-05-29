/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_EscAesCbcEncrypt.c                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Escrypt AES - CBC Encrypt Interface     **
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
** 1.0.8     21-Sep-2016   Sinil        Redmine #5554, #6128                  **
** 1.0.7     09-Aug-2016   Sinil        Redmine #5693                         **
** 1.0.6     12-Jul-2016   Sinil        Redmine #5514                         **
** 1.0.5     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.4     16-May-2016   Sinil        Redmine #4903                         **
** 1.0.3     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.2     02-May-2016   Sinil        Redmine #4607                         **
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
/* Header File for Escrypt AES CBC */
#include "Cry_EscAesCbcEncrypt.h"
/* Symmetric Interface */
#if (CSM_SYM_ENCRYPT_STATUS == STD_ON)
#if (CSM_SYM_ESCAESCBCENCRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "aes_cbc.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry EscAesCbcEncrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_SymKeyType* pKeyPtr;
  const uint8* pPlainTextPtr;
  uint32 ulPlainTextLength;
  const uint8* pInitVectorPtr;
  uint32 ulInitVectorLength;
  uint8* pCipherTextPtr;
  uint32* pCipherTextLengthPtr;
} Cry_EscAesCbcEncryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* AES primitive library context */
static EscAesCbc_ContextT Cry_GddEscAesCbcEncryptContext;

/* Global structure variable for Escrypt AES CBC transfer buffer */
static Cry_EscAesCbcEncryptTransferBuffer Cry_GddEscAesCbcEncryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_EscAesCbcEncryptInit                              **
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
** Remarks            : Global Variable(s):  Cry_GddEscAesCbcEncryptTb        **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_EscAesCbcEncryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddEscAesCbcEncryptTb.ucJobState = NO_JOB;
  Cry_GddEscAesCbcEncryptTb.pKeyPtr = NULL_PTR;
  Cry_GddEscAesCbcEncryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddEscAesCbcEncryptTb.ulPlainTextLength = CSM_ZERO;
  Cry_GddEscAesCbcEncryptTb.pInitVectorPtr = NULL_PTR;
  Cry_GddEscAesCbcEncryptTb.ulInitVectorLength = CSM_ZERO;
  Cry_GddEscAesCbcEncryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddEscAesCbcEncryptTb.pCipherTextLengthPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddEscAesCbcEncryptContext, 0x00, sizeof(EscAesCbc_ContextT));
}

/*******************************************************************************
** Function Name        : Cry_EscAesCbcEncryptStart                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Escrypt AES CBC, so that AES is able **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_EscAesCbcEncryptMainFunction() can process      **
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
**                        Cry_GddEscAesCbcEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_EscAesCbcEncryptInit, EscAesCbc_Init            **
*******************************************************************************/
Std_ReturnType Cry_EscAesCbcEncryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr, const uint8* InitVectorPtr,
  uint32 InitVectorLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddEscAesCbcEncryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_EscAesCbcEncryptInit();

    Cry_GddEscAesCbcEncryptTb.ucJobState = JOB_START;

    if (Csm_SymEncryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if ((keyPtr->length != EscAes_KEY_BYTES)
        || (InitVectorLength != EscAes_IV_BYTES))
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LblReturnValue = EscAesCbc_Init(&Cry_GddEscAesCbcEncryptContext,
          (const uint8*)((const void*)(keyPtr->data)), InitVectorPtr);

        if (LblReturnValue == CSM_TRUE)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscAesCbcEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscAesCbcEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscAesCbcEncryptTb.pKeyPtr = keyPtr;
      Cry_GddEscAesCbcEncryptTb.pInitVectorPtr = InitVectorPtr;
      Cry_GddEscAesCbcEncryptTb.ulInitVectorLength = InitVectorLength;
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
** Function Name        : Cry_EscAesCbcEncryptUpdate                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the AES      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscAesCbcEncryptMainFunction() can process the  **
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
**                        Cry_GddEscAesCbcEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscAesCbc_Encrypt                                   **
*******************************************************************************/
Std_ReturnType Cry_EscAesCbcEncryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* plainTextPtr, uint32 plainTextLength, uint8* cipherTextPtr,
  uint32* cipherTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddEscAesCbcEncryptTb.ucJobState)
  {
    Cry_GddEscAesCbcEncryptTb.ucJobState = JOB_UPDATE;

    if (Csm_SymEncryptServiceHasCallback() == FALSE)
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

        LblReturnValue = EscAesCbc_Encrypt(&Cry_GddEscAesCbcEncryptContext,
          plainTextPtr, cipherTextPtr, plainTextLength);

        if (LblReturnValue != CSM_TRUE)
        {
          *cipherTextLengthPtr = plainTextLength;
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscAesCbcEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscAesCbcEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscAesCbcEncryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddEscAesCbcEncryptTb.ulPlainTextLength = plainTextLength;
      Cry_GddEscAesCbcEncryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddEscAesCbcEncryptTb.pCipherTextLengthPtr = cipherTextLengthPtr;
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
** Function Name        : Cry_EscAesCbcEncryptFinish                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the AES     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscAesCbcEncryptMainFunction() can finish the   **
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
**                        Cry_GddEscAesCbcEncryptTb                           **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
Std_ReturnType Cry_EscAesCbcEncryptFinish(Csm_ConfigIdType cfgId,
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
  if (JOB_DONE == Cry_GddEscAesCbcEncryptTb.ucJobState)
  {
    Cry_GddEscAesCbcEncryptTb.ucJobState = JOB_FINISH;

    if (Csm_SymEncryptServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddEscAesCbcEncryptTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_EscAesCbcEncryptMainFunction                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SymEncryptCallbackNotification() with the       **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by Cry_EscAesCbcEncryptStart()   **
**                        or Cry_EscAesCbcEncryptUpdate(). For                **
**                        Cry_EscAesCbcEncryptFinish invocation of            **
**                        Csm_SymEncryptCallbackNotification()                **
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
**                        Cry_GddEscAesCbcEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscAesCbc_Init,                                     **
**                        EscAesCbc_Encrypt,                                  **
**                        Csm_SymEncryptCallbackNotification,                 **
**                        Csm_SymEncryptServiceFinishNotification             **
*******************************************************************************/
void Cry_EscAesCbcEncryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddEscAesCbcEncryptTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if ((Cry_GddEscAesCbcEncryptTb.pKeyPtr->length != EscAes_KEY_BYTES)
      || (Cry_GddEscAesCbcEncryptTb.ulInitVectorLength != EscAes_IV_BYTES))
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LblReturnValue = EscAesCbc_Init(
        &Cry_GddEscAesCbcEncryptContext,
        (const uint8*)((const void*)(Cry_GddEscAesCbcEncryptTb.pKeyPtr->data)),
        Cry_GddEscAesCbcEncryptTb.pInitVectorPtr);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscAesCbcEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscAesCbcEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (*(Cry_GddEscAesCbcEncryptTb.pCipherTextLengthPtr)
      < Cry_GddEscAesCbcEncryptTb.ulPlainTextLength)
    {
      /* Buffer size is invalid */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if ((Cry_GddEscAesCbcEncryptTb.ulPlainTextLength < EscAes_KEY_BYTES)
      || ((Cry_GddEscAesCbcEncryptTb.ulPlainTextLength % EscAes_KEY_BYTES) != CSM_ZERO))
    {
      /* plainTextLength should be multiples of 16 */
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      *(Cry_GddEscAesCbcEncryptTb.pCipherTextLengthPtr) = CSM_ZERO;

      LblReturnValue = EscAesCbc_Encrypt(&Cry_GddEscAesCbcEncryptContext,
        Cry_GddEscAesCbcEncryptTb.pPlainTextPtr,
        Cry_GddEscAesCbcEncryptTb.pCipherTextPtr,
        Cry_GddEscAesCbcEncryptTb.ulPlainTextLength);

      if (LblReturnValue != CSM_TRUE)
      {
        *(Cry_GddEscAesCbcEncryptTb.pCipherTextLengthPtr)
          = Cry_GddEscAesCbcEncryptTb.ulPlainTextLength;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscAesCbcEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscAesCbcEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddEscAesCbcEncryptTb.ucJobState = NO_JOB;

    /* Notify respective Service about the completion of the task */
    Csm_SymEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_SymEncryptServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_SYM_ESCAESCBCENCRYPT == STD_ON) */
#endif /* (CSM_SYM_ENCRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
