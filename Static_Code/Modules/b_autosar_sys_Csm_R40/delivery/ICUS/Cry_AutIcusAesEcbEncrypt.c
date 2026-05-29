/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutIcusAesEcbEncrypt.c                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY ICUS AES - ECB Encrypt Interface        **
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
#include "Cry_AutIcusAesEcbEncrypt.h"
/* Symmetric Interface */
#if (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON)
#if (CSM_SYMBLOCK_AUTICUSAESECBENCRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "Icus_Driver.h"
#include "Icus_IntDriver.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry AutIcusAesEcbEncrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_SymKeyType* pKeyPtr;
  const uint8* pPlainTextPtr;
  uint32 ulPlainTextLength;
  uint8* pCipherTextPtr;
  uint32* pCipherTextLengthPtr;
} Cry_AutIcusAesEcbEncryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_32
#include "MemMap.h"

static uint32 Cry_GulAutIcusAesEcbEncKeyLength;

#define CSM_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Icus_KeyIDType Cry_GddAutIcusAesEcbEncKeyId;

static const uint8* Cry_GpAutIcusAesEcbEncKeyData;

/* Global structure variable for ICUS AES ECB transfer buffer */
static Cry_AutIcusAesEcbEncryptTransferBuffer Cry_GddAutIcusAesEcbEncryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutIcusAesEcbEncryptInit                          **
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
** Remarks            : Global Variable(s):  Cry_GddAutIcusAesEcbEncryptTb    **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutIcusAesEcbEncryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutIcusAesEcbEncryptTb.ucJobState = NO_JOB;
  Cry_GddAutIcusAesEcbEncryptTb.pKeyPtr = NULL_PTR;
  Cry_GddAutIcusAesEcbEncryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddAutIcusAesEcbEncryptTb.ulPlainTextLength = CSM_ZERO;
  Cry_GddAutIcusAesEcbEncryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddAutIcusAesEcbEncryptTb.pCipherTextLengthPtr = NULL_PTR;

  Cry_GulAutIcusAesEcbEncKeyLength = CSM_ZERO;
  Cry_GddAutIcusAesEcbEncKeyId = INVALID_KEY;
  Cry_GpAutIcusAesEcbEncKeyData = NULL_PTR;
}

/*******************************************************************************
** Function Name        : Cry_AutIcusAesEcbEncryptStart                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of ICUS AES ECB, so that AES is able    **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutIcusAesEcbEncryptMainFunction() can process  **
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
**                        Cry_GddAutIcusAesEcbEncryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutIcusAesEcbEncryptInit,                       **
**                        Csm_SymBlockEncryptServiceHasCallback,              **
**                        Icus_LoadPlainKey                                   **
*******************************************************************************/
Std_ReturnType Cry_AutIcusAesEcbEncryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  Icus_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutIcusAesEcbEncryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutIcusAesEcbEncryptInit();

    Cry_GddAutIcusAesEcbEncryptTb.ucJobState = JOB_START;

    if (Csm_SymBlockEncryptServiceHasCallback() == FALSE)
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
          Cry_GulAutIcusAesEcbEncKeyLength = CSM_ONE;
          /* polyspace +2 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
          Cry_GddAutIcusAesEcbEncKeyId = (Icus_KeyIDType)(keyPtr->data[0]);
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }
      else if (keyPtr->length == ICUS_BLOCK_BYTE_LENGTH)
      {
        /* Raw Key */
        Cry_GulAutIcusAesEcbEncKeyLength = ICUS_BLOCK_BYTE_LENGTH;
        Cry_GddAutIcusAesEcbEncKeyId = RAM_KEY;
        Cry_GpAutIcusAesEcbEncKeyData = (const uint8*)((const void*)(keyPtr->data));
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        if (Cry_GulAutIcusAesEcbEncKeyLength == ICUS_BLOCK_BYTE_LENGTH)
        {
          LddErr = Icus_LoadPlainKey(Cry_GpAutIcusAesEcbEncKeyData);

          if (LddErr != ERC_NO_ERROR)
          {
            LddReturnValue = E_NOT_OK;
          }
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutIcusAesEcbEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutIcusAesEcbEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutIcusAesEcbEncryptTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_AutIcusAesEcbEncryptUpdate                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the AES      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutIcusAesEcbEncryptMainFunction() can process  **
**                        the input                                           **
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
**                        Cry_GddAutIcusAesEcbEncryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymBlockEncryptServiceHasCallback, Icus_EncEcb  **
*******************************************************************************/
Std_ReturnType Cry_AutIcusAesEcbEncryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* plainTextPtr, uint32 plainTextLength, uint8* cipherTextPtr,
  uint32* cipherTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  Icus_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutIcusAesEcbEncryptTb.ucJobState)
  {
    Cry_GddAutIcusAesEcbEncryptTb.ucJobState = JOB_UPDATE;

    if (Csm_SymBlockEncryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*cipherTextLengthPtr < plainTextLength)
      {
        /* Buffer size is invalid */
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if ((plainTextLength < ICUS_BLOCK_BYTE_LENGTH)
        || ((plainTextLength % ICUS_BLOCK_BYTE_LENGTH) != CSM_ZERO))
      {
        /* plainTextLength should be multiples of 16 */
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        *cipherTextLengthPtr = CSM_ZERO;

        LddErr = Icus_EncEcb(Cry_GddAutIcusAesEcbEncKeyId,
          (plainTextLength / ICUS_BLOCK_BYTE_LENGTH),
          plainTextPtr, cipherTextPtr);

        /* Verify the return value */
        if (LddErr == ERC_NO_ERROR)
        {
          *cipherTextLengthPtr = (plainTextLength / ICUS_BLOCK_BYTE_LENGTH)
            * ICUS_BLOCK_BYTE_LENGTH;
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutIcusAesEcbEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutIcusAesEcbEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutIcusAesEcbEncryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddAutIcusAesEcbEncryptTb.ulPlainTextLength = plainTextLength;
      Cry_GddAutIcusAesEcbEncryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddAutIcusAesEcbEncryptTb.pCipherTextLengthPtr = cipherTextLengthPtr;
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
** Function Name        : Cry_AutIcusAesEcbEncryptFinish                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the AES     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutIcusAesEcbEncryptMainFunction() can finish   **
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
**                        Cry_GddAutIcusAesEcbEncryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymBlockEncryptServiceHasCallback               **
*******************************************************************************/
Std_ReturnType Cry_AutIcusAesEcbEncryptFinish(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutIcusAesEcbEncryptTb.ucJobState)
  {
    Cry_GddAutIcusAesEcbEncKeyId = INVALID_KEY;

    Cry_GddAutIcusAesEcbEncryptTb.ucJobState = JOB_FINISH;

    if (Csm_SymBlockEncryptServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutIcusAesEcbEncryptTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_AutIcusAesEcbEncryptMainFunction                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SymBlockEncryptCallbackNotification() with the  **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_AutIcusAesEcbEncryptStart()                     **
**                        or Cry_AutIcusAesEcbEncryptUpdate(). For            **
**                        Cry_AutIcusAesEcbEncryptFinish invocation of        **
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
**                        Cry_GddAutIcusAesEcbEncryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Icus_LoadPlainKey, Icus_EncEcb,                     **
**                        Csm_SymBlockEncryptCallbackNotification,            **
**                        Csm_SymBlockEncryptServiceFinishNotification        **
*******************************************************************************/
void Cry_AutIcusAesEcbEncryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Icus_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* State machine of AES job processing */
  switch (Cry_GddAutIcusAesEcbEncryptTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (Cry_GddAutIcusAesEcbEncryptTb.pKeyPtr->length == CSM_ONE)
    {
      /* Pre-Shared Key */
      if ((((Cry_GddAutIcusAesEcbEncryptTb.pKeyPtr->data[0]) >= (uint8)KEY_1)
        && ((Cry_GddAutIcusAesEcbEncryptTb.pKeyPtr->data[0]) <= (uint8)KEY_10))
        || (((Cry_GddAutIcusAesEcbEncryptTb.pKeyPtr->data[0]) >= (uint8)KEY_11)
        && ((Cry_GddAutIcusAesEcbEncryptTb.pKeyPtr->data[0]) <= (uint8)KEY_20)))
      {
        Cry_GulAutIcusAesEcbEncKeyLength = CSM_ONE;
        /* polyspace +2 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
        Cry_GddAutIcusAesEcbEncKeyId
          = (Icus_KeyIDType)(Cry_GddAutIcusAesEcbEncryptTb.pKeyPtr->data[0]);
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }
    else if (Cry_GddAutIcusAesEcbEncryptTb.pKeyPtr->length == ICUS_BLOCK_BYTE_LENGTH)
    {
      /* Raw Key */
      Cry_GulAutIcusAesEcbEncKeyLength = ICUS_BLOCK_BYTE_LENGTH;
      Cry_GddAutIcusAesEcbEncKeyId = RAM_KEY;
      Cry_GpAutIcusAesEcbEncKeyData
        = (const uint8*)((const void*)(Cry_GddAutIcusAesEcbEncryptTb.pKeyPtr->data));
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      if (Cry_GulAutIcusAesEcbEncKeyLength == ICUS_BLOCK_BYTE_LENGTH)
      {
        LddErr = Icus_LoadPlainKey(Cry_GpAutIcusAesEcbEncKeyData);

        if (LddErr != ERC_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutIcusAesEcbEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutIcusAesEcbEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymBlockEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (*(Cry_GddAutIcusAesEcbEncryptTb.pCipherTextLengthPtr)
      < Cry_GddAutIcusAesEcbEncryptTb.ulPlainTextLength)
    {
      /* Buffer size is invalid */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if ((Cry_GddAutIcusAesEcbEncryptTb.ulPlainTextLength < ICUS_BLOCK_BYTE_LENGTH)
      || ((Cry_GddAutIcusAesEcbEncryptTb.ulPlainTextLength % ICUS_BLOCK_BYTE_LENGTH) != CSM_ZERO))
    {
      /* plainTextLength should be multiples of 16 */
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      *(Cry_GddAutIcusAesEcbEncryptTb.pCipherTextLengthPtr) = CSM_ZERO;

      LddErr = Icus_EncEcb(Cry_GddAutIcusAesEcbEncKeyId,
        (Cry_GddAutIcusAesEcbEncryptTb.ulPlainTextLength / ICUS_BLOCK_BYTE_LENGTH),
        Cry_GddAutIcusAesEcbEncryptTb.pPlainTextPtr,
        Cry_GddAutIcusAesEcbEncryptTb.pCipherTextPtr);

      /* Verify the return value */
      if (LddErr == ERC_NO_ERROR)
      {
        *(Cry_GddAutIcusAesEcbEncryptTb.pCipherTextLengthPtr)
          = (Cry_GddAutIcusAesEcbEncryptTb.ulPlainTextLength / ICUS_BLOCK_BYTE_LENGTH)
            * ICUS_BLOCK_BYTE_LENGTH;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutIcusAesEcbEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutIcusAesEcbEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymBlockEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    Cry_GddAutIcusAesEcbEncKeyId = INVALID_KEY;

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddAutIcusAesEcbEncryptTb.ucJobState = NO_JOB;

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

#endif /* (CSM_SYMBLOCK_AUTICUSAESECBENCRYPT == STD_ON) */
#endif /* (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
