/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutIcusAesEcbDecrypt.c                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY ICUS AES - ECB Decrypt Interface        **
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
** 1.0.2     19-Apr-2019   Sinil        Redmine #17138                        **
** 1.0.1     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.0     14-Feb-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for ICUS AES ECB */
#include "Cry_AutIcusAesEcbDecrypt.h"
/* Symmetric Interface */
#if (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON)
#if (CSM_SYMBLOCK_AUTICUSAESECBDECRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "Icus_Driver.h"
#include "Icus_IntDriver.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry AutIcusAesEcbDecrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_SymKeyType* pKeyPtr;
  const uint8* pCipherTextPtr;
  uint32 ulCipherTextLength;
  uint8* pPlainTextPtr;
  uint32* pPlainTextLengthPtr;
} Cry_AutIcusAesEcbDecryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_32
#include "MemMap.h"

static uint32 Cry_GulAutIcusAesEcbDecKeyLength;

#define CSM_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Icus_KeyIDType Cry_GddAutIcusAesEcbDecKeyId;

static const uint8* Cry_GpAutIcusAesEcbDecKeyData;

/* Global structure variable for ICUS AES ECB transfer buffer */
static Cry_AutIcusAesEcbDecryptTransferBuffer Cry_GddAutIcusAesEcbDecryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutIcusAesEcbDecryptInit                          **
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
** Remarks            : Global Variable(s):                                   **
**                      Cry_GddAutIcusAesEcbDecryptTb                         **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutIcusAesEcbDecryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutIcusAesEcbDecryptTb.ucJobState = NO_JOB;
  Cry_GddAutIcusAesEcbDecryptTb.pKeyPtr = NULL_PTR;
  Cry_GddAutIcusAesEcbDecryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddAutIcusAesEcbDecryptTb.ulCipherTextLength = CSM_ZERO;
  Cry_GddAutIcusAesEcbDecryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddAutIcusAesEcbDecryptTb.pPlainTextLengthPtr = NULL_PTR;

  Cry_GulAutIcusAesEcbDecKeyLength = CSM_ZERO;
  Cry_GddAutIcusAesEcbDecKeyId = INVALID_KEY;
  Cry_GpAutIcusAesEcbDecKeyData = NULL_PTR;
}

/*******************************************************************************
** Function Name        : Cry_AutIcusAesEcbDecryptStart                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of ICUS AES ECB, so that AES is able    **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutIcusAesEcbDecryptMainFunction() can process  **
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
**                        Cry_GddAutIcusAesEcbDecryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutIcusAesEcbDecryptInit,                       **
**                        Csm_SymBlockDecryptServiceHasCallback,              **
**                        Icus_LoadPlainKey                                   **
*******************************************************************************/
Std_ReturnType Cry_AutIcusAesEcbDecryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  Icus_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutIcusAesEcbDecryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutIcusAesEcbDecryptInit();

    Cry_GddAutIcusAesEcbDecryptTb.ucJobState = JOB_START;

    if (Csm_SymBlockDecryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        /* Pre-Shared Key */
        if ((((keyPtr->data[0]) >= (uint8)KEY_1) && \
            ((keyPtr->data[0]) <= (uint8)KEY_10)) \
          || (((keyPtr->data[0]) >= (uint8)KEY_11) && \
            ((keyPtr->data[0]) <= (uint8)KEY_20)))
        {
          Cry_GulAutIcusAesEcbDecKeyLength = CSM_ONE;
          /* polyspace +2 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
          Cry_GddAutIcusAesEcbDecKeyId = (Icus_KeyIDType)(keyPtr->data[0]);
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }
      else if (keyPtr->length == ICUS_BLOCK_BYTE_LENGTH)
      {
        /* Raw Key */
        Cry_GulAutIcusAesEcbDecKeyLength = ICUS_BLOCK_BYTE_LENGTH;
        Cry_GddAutIcusAesEcbDecKeyId = RAM_KEY;
        Cry_GpAutIcusAesEcbDecKeyData = (const uint8*)((const void*)(keyPtr->data));
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        if (Cry_GulAutIcusAesEcbDecKeyLength == ICUS_BLOCK_BYTE_LENGTH)
        {
          LddErr = Icus_LoadPlainKey(Cry_GpAutIcusAesEcbDecKeyData);

          if (LddErr != ERC_NO_ERROR)
          {
            LddReturnValue = E_NOT_OK;
          }
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutIcusAesEcbDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutIcusAesEcbDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutIcusAesEcbDecryptTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_AutIcusAesEcbDecryptUpdate                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the AES      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutIcusAesEcbDecryptMainFunction() can process  **
**                        the input                                           **
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
**                        Cry_GddAutIcusAesEcbDecryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymBlockDecryptServiceHasCallback, Icus_DecEcb  **
*******************************************************************************/
Std_ReturnType Cry_AutIcusAesEcbDecryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* cipherTextPtr, uint32 cipherTextLength, uint8* plainTextPtr,
  uint32* plainTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  Icus_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutIcusAesEcbDecryptTb.ucJobState)
  {
    /* Set the job state to JOB_UPDATE */
    Cry_GddAutIcusAesEcbDecryptTb.ucJobState = JOB_UPDATE;

    if (Csm_SymBlockDecryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*plainTextLengthPtr < cipherTextLength)
      {
        /* Buffer size is invalid */
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if ((cipherTextLength < ICUS_BLOCK_BYTE_LENGTH)
        || ((cipherTextLength % ICUS_BLOCK_BYTE_LENGTH) != CSM_ZERO))
      {
        /* cipherTextLength should be multiples of 16 */
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        *plainTextLengthPtr = CSM_ZERO;

        LddErr = Icus_DecEcb(Cry_GddAutIcusAesEcbDecKeyId,
          (cipherTextLength / ICUS_BLOCK_BYTE_LENGTH),
          cipherTextPtr, plainTextPtr);

        if (LddErr == ERC_NO_ERROR)
        {
          *plainTextLengthPtr = (cipherTextLength / ICUS_BLOCK_BYTE_LENGTH)
            * ICUS_BLOCK_BYTE_LENGTH;
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutIcusAesEcbDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutIcusAesEcbDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutIcusAesEcbDecryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddAutIcusAesEcbDecryptTb.ulCipherTextLength = cipherTextLength;
      Cry_GddAutIcusAesEcbDecryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddAutIcusAesEcbDecryptTb.pPlainTextLengthPtr = plainTextLengthPtr;
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
** Function Name        : Cry_AutIcusAesEcbDecryptFinish                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the AES     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutIcusAesEcbDecryptMainFunction() can finish   **
**                        the computation and store the result in the memory  **
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
**                        Cry_GddAutIcusAesEcbDecryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymBlockDecryptServiceHasCallback               **
*******************************************************************************/
Std_ReturnType Cry_AutIcusAesEcbDecryptFinish(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutIcusAesEcbDecryptTb.ucJobState)
  {
    Cry_GddAutIcusAesEcbDecKeyId = INVALID_KEY;

    Cry_GddAutIcusAesEcbDecryptTb.ucJobState = JOB_FINISH;

    if (Csm_SymBlockDecryptServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutIcusAesEcbDecryptTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_AutIcusAesEcbDecryptMainFunction                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SymBlockDecryptCallbackNotification() with the  **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_AutIcusAesEcbDecryptStart()                     **
**                        or Cry_AutIcusAesEcbDecryptUpdate(). For            **
**                        Cry_AutIcusAesEcbDecryptFinish invocation of        **
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
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddAutIcusAesEcbDecryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Icus_LoadPlainKey, Icus_DecEcb,                     **
**                        Csm_SymBlockDecryptCallbackNotification,            **
**                        Csm_SymBlockDecryptServiceFinishNotification        **
*******************************************************************************/
void Cry_AutIcusAesEcbDecryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Icus_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddAutIcusAesEcbDecryptTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (Cry_GddAutIcusAesEcbDecryptTb.pKeyPtr->length == CSM_ONE)
    {
      /* Pre-Shared Key */
      if ((((Cry_GddAutIcusAesEcbDecryptTb.pKeyPtr->data[0]) >= (uint8)KEY_1)
        && ((Cry_GddAutIcusAesEcbDecryptTb.pKeyPtr->data[0]) <= (uint8)KEY_10))
        || (((Cry_GddAutIcusAesEcbDecryptTb.pKeyPtr->data[0]) >= (uint8)KEY_11)
        && ((Cry_GddAutIcusAesEcbDecryptTb.pKeyPtr->data[0]) <= (uint8)KEY_20)))
      {
        Cry_GulAutIcusAesEcbDecKeyLength = CSM_ONE;
        /* polyspace +2 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
        Cry_GddAutIcusAesEcbDecKeyId
          = (Icus_KeyIDType)(Cry_GddAutIcusAesEcbDecryptTb.pKeyPtr->data[0]);
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }
    else if (Cry_GddAutIcusAesEcbDecryptTb.pKeyPtr->length == ICUS_BLOCK_BYTE_LENGTH)
    {
      /* Raw Key */
      Cry_GulAutIcusAesEcbDecKeyLength = ICUS_BLOCK_BYTE_LENGTH;
      Cry_GddAutIcusAesEcbDecKeyId = RAM_KEY;
      Cry_GpAutIcusAesEcbDecKeyData
        = (const uint8*)((const void*)(Cry_GddAutIcusAesEcbDecryptTb.pKeyPtr->data));
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      if (Cry_GulAutIcusAesEcbDecKeyLength == ICUS_BLOCK_BYTE_LENGTH)
      {
        LddErr = Icus_LoadPlainKey(Cry_GpAutIcusAesEcbDecKeyData);

        if (LddErr != ERC_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutIcusAesEcbDecryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutIcusAesEcbDecryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymBlockDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (*(Cry_GddAutIcusAesEcbDecryptTb.pPlainTextLengthPtr)
      < Cry_GddAutIcusAesEcbDecryptTb.ulCipherTextLength)
    {
      /* Buffer size is invalid */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if ((Cry_GddAutIcusAesEcbDecryptTb.ulCipherTextLength < ICUS_BLOCK_BYTE_LENGTH)
      || ((Cry_GddAutIcusAesEcbDecryptTb.ulCipherTextLength % ICUS_BLOCK_BYTE_LENGTH) != CSM_ZERO))
    {
      /* cipherTextLength should be multiples of 16 */
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      *(Cry_GddAutIcusAesEcbDecryptTb.pPlainTextLengthPtr) = CSM_ZERO;

      LddErr = Icus_DecEcb(Cry_GddAutIcusAesEcbDecKeyId,
        (Cry_GddAutIcusAesEcbDecryptTb.ulCipherTextLength / ICUS_BLOCK_BYTE_LENGTH),
        Cry_GddAutIcusAesEcbDecryptTb.pCipherTextPtr,
        Cry_GddAutIcusAesEcbDecryptTb.pPlainTextPtr);

      /* Verify the return value */
      if (LddErr == ERC_NO_ERROR)
      {
        *(Cry_GddAutIcusAesEcbDecryptTb.pPlainTextLengthPtr)
          = (Cry_GddAutIcusAesEcbDecryptTb.ulCipherTextLength / ICUS_BLOCK_BYTE_LENGTH)
            * ICUS_BLOCK_BYTE_LENGTH;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutIcusAesEcbDecryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutIcusAesEcbDecryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymBlockDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    Cry_GddAutIcusAesEcbDecKeyId = INVALID_KEY;

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddAutIcusAesEcbDecryptTb.ucJobState = NO_JOB;

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

#endif /* (CSM_SYMBLOCK_AUTICUSAESECBDECRYPT == STD_ON) */
#endif /* (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
