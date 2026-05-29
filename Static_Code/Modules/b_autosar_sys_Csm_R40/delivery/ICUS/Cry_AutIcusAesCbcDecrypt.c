/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutIcusAesCbcDecrypt.c                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY ICUS AES - CBC Decrypt Interface        **
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
/* Header File for ICUS AES CBC */
#include "Cry_AutIcusAesCbcDecrypt.h"
/* Symmetric Interface */
#if (CSM_SYM_DECRYPT_STATUS == STD_ON)
#if (CSM_SYM_AUTICUSAESCBCDECRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "Icus_Driver.h"
#include "Icus_IntDriver.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry AutIcusAesCbcDecrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_SymKeyType* pKeyPtr;
  const uint8* pCipherTextPtr;
  uint32 ulCipherTextLength;
  const uint8* pInitVectorPtr;
  uint32 InitVectorLength;
  uint8* pPlainTextPtr;
  uint32* pPlainTextLengthPtr;
} Cry_AutIcusAesCbcDecryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_32
#include "MemMap.h"

static uint32 Cry_GulAutIcusAesCbcDecKeyLength;

#define CSM_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

static uint8 Cry_GaaAutIcusAesCbcDecInitVector[ICUS_BLOCK_BYTE_LENGTH];

#define CSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Icus_KeyIDType Cry_GddAutIcusAesCbcDecKeyId;

static const uint8* Cry_GpAutIcusAesCbcDecKeyData;

/* Global structure variable for ICUS AES CBC transfer buffer */
static Cry_AutIcusAesCbcDecryptTransferBuffer Cry_GddAutIcusAesCbcDecryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutIcusAesCbcDecryptInit                          **
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
**                      Cry_GddAutIcusAesCbcDecryptTb,                        **
**                      Cry_GaaAutIcusAesCbcDecInitVector                     **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutIcusAesCbcDecryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutIcusAesCbcDecryptTb.ucJobState = NO_JOB;
  Cry_GddAutIcusAesCbcDecryptTb.pKeyPtr = NULL_PTR;
  Cry_GddAutIcusAesCbcDecryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddAutIcusAesCbcDecryptTb.ulCipherTextLength = CSM_ZERO;
  Cry_GddAutIcusAesCbcDecryptTb.pInitVectorPtr = NULL_PTR;
  Cry_GddAutIcusAesCbcDecryptTb.InitVectorLength = CSM_ZERO;
  Cry_GddAutIcusAesCbcDecryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddAutIcusAesCbcDecryptTb.pPlainTextLengthPtr = NULL_PTR;

  (void)memset((void*)Cry_GaaAutIcusAesCbcDecInitVector, 0x00, ICUS_BLOCK_BYTE_LENGTH);

  Cry_GulAutIcusAesCbcDecKeyLength = CSM_ZERO;
  Cry_GddAutIcusAesCbcDecKeyId = INVALID_KEY;
  Cry_GpAutIcusAesCbcDecKeyData = NULL_PTR;
}

/*******************************************************************************
** Function Name        : Cry_AutIcusAesCbcDecryptStart                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of ICUS AES CBC, so that AES is able   **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutIcusAesCbcDecryptMainFunction() can process  **
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
**                        Cry_GddAutIcusAesCbcDecryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutIcusAesCbcDecryptInit,                       **
**                        Csm_SymDecryptServiceHasCallback,                   **
**                        Icus_LoadPlainKey                                   **
*******************************************************************************/
Std_ReturnType Cry_AutIcusAesCbcDecryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr, const uint8* InitVectorPtr,
  uint32 InitVectorLength)
{
  Std_ReturnType LddReturnValue;
  Icus_ErrType LddErr;
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutIcusAesCbcDecryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutIcusAesCbcDecryptInit();

    /* Set the job state to JOB_START */
    Cry_GddAutIcusAesCbcDecryptTb.ucJobState = JOB_START;

    if (Csm_SymDecryptServiceHasCallback() == FALSE)
    {
      if (InitVectorLength != ICUS_BLOCK_BYTE_LENGTH)
      {
        LddReturnValue = E_NOT_OK;
      }
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        /* Pre-Shared Key */
        if ((((keyPtr->data[0]) >= (uint8)KEY_1) && \
           ((keyPtr->data[0]) <= (uint8)KEY_10)) \
          || (((keyPtr->data[0]) >= (uint8)KEY_11) && \
            ((keyPtr->data[0]) <= (uint8)KEY_20)))
        {
          Cry_GulAutIcusAesCbcDecKeyLength = CSM_ONE;
          /* polyspace +1 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
          Cry_GddAutIcusAesCbcDecKeyId = (Icus_KeyIDType)(keyPtr->data[0]);
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }
      else if (keyPtr->length == ICUS_BLOCK_BYTE_LENGTH)
      {
        /* Raw Key */
        Cry_GulAutIcusAesCbcDecKeyLength = ICUS_BLOCK_BYTE_LENGTH;
        Cry_GddAutIcusAesCbcDecKeyId = RAM_KEY;
        Cry_GpAutIcusAesCbcDecKeyData = (const uint8*)((const void*)(keyPtr->data));
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        for (LulIndex = CSM_ZERO; LulIndex < ICUS_BLOCK_BYTE_LENGTH; LulIndex++)
        {
          /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          Cry_GaaAutIcusAesCbcDecInitVector[LulIndex] = InitVectorPtr[LulIndex];
        }

        if (Cry_GulAutIcusAesCbcDecKeyLength == ICUS_BLOCK_BYTE_LENGTH)
        {
          LddErr = Icus_LoadPlainKey(Cry_GpAutIcusAesCbcDecKeyData);

          if (LddErr != ERC_NO_ERROR)
          {
            LddReturnValue = E_NOT_OK;
          }
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutIcusAesCbcDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutIcusAesCbcDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutIcusAesCbcDecryptTb.pKeyPtr = keyPtr;
      Cry_GddAutIcusAesCbcDecryptTb.pInitVectorPtr = InitVectorPtr;
      Cry_GddAutIcusAesCbcDecryptTb.InitVectorLength = InitVectorLength;
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
** Function Name        : Cry_AutIcusAesCbcDecryptUpdate                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the AES      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutIcusAesCbcDecryptMainFunction() can process  **
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
**                        Cry_GddAutIcusAesCbcDecryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymDecryptServiceHasCallback, Icus_DecCbc       **
*******************************************************************************/
Std_ReturnType Cry_AutIcusAesCbcDecryptUpdate(Csm_ConfigIdType cfgId,
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
  if (JOB_DONE == Cry_GddAutIcusAesCbcDecryptTb.ucJobState)
  {
    Cry_GddAutIcusAesCbcDecryptTb.ucJobState = JOB_UPDATE;

    if (Csm_SymDecryptServiceHasCallback() == FALSE)
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

        LddErr = Icus_DecCbc(Cry_GddAutIcusAesCbcDecKeyId,
          (cipherTextLength / ICUS_BLOCK_BYTE_LENGTH),
          cipherTextPtr, plainTextPtr, Cry_GaaAutIcusAesCbcDecInitVector);

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
        Cry_GddAutIcusAesCbcDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutIcusAesCbcDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutIcusAesCbcDecryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddAutIcusAesCbcDecryptTb.ulCipherTextLength = cipherTextLength;
      Cry_GddAutIcusAesCbcDecryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddAutIcusAesCbcDecryptTb.pPlainTextLengthPtr = plainTextLengthPtr;
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
** Function Name        : Cry_AutIcusAesCbcDecryptFinish                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the AES     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutIcusAesCbcDecryptMainFunction() can finish   **
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
**                        Cry_GddAutIcusAesCbcDecryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymDecryptServiceHasCallback                    **
*******************************************************************************/
Std_ReturnType Cry_AutIcusAesCbcDecryptFinish(Csm_ConfigIdType cfgId,
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
  if (JOB_DONE == Cry_GddAutIcusAesCbcDecryptTb.ucJobState)
  {
    Cry_GddAutIcusAesCbcDecKeyId = INVALID_KEY;

    Cry_GddAutIcusAesCbcDecryptTb.ucJobState = JOB_FINISH;

    if (Csm_SymDecryptServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutIcusAesCbcDecryptTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_AutIcusAesCbcDecryptMainFunction                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SymDecryptCallbackNotification() with the       **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_AutIcusAesCbcDecryptStart()                     **
**                        or Cry_AutIcusAesCbcDecryptUpdate(). For            **
**                        Cry_AutIcusAesCbcDecryptFinish invocation of        **
**                        Csm_SymDecryptCallbackNotification()                **
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
**                        Cry_GddAutIcusAesCbcDecryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Icus_LoadPlainKey, Icus_DecCbc,                     **
**                        Csm_SymDecryptCallbackNotification,                 **
**                        Csm_SymDecryptServiceFinishNotification             **
*******************************************************************************/
void Cry_AutIcusAesCbcDecryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Icus_ErrType LddErr;
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddAutIcusAesCbcDecryptTb.ucJobState)
  {
  case JOB_START:
    if (Cry_GddAutIcusAesCbcDecryptTb.InitVectorLength != ICUS_BLOCK_BYTE_LENGTH)
    {
      LddReturnValue = E_NOT_OK;
    }
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (Cry_GddAutIcusAesCbcDecryptTb.pKeyPtr->length == CSM_ONE)
    {
      /* Pre-Shared Key */
      if ((((Cry_GddAutIcusAesCbcDecryptTb.pKeyPtr->data[0]) >= (uint8)KEY_1)
        && ((Cry_GddAutIcusAesCbcDecryptTb.pKeyPtr->data[0]) <= (uint8)KEY_10))
        || (((Cry_GddAutIcusAesCbcDecryptTb.pKeyPtr->data[0]) >= (uint8)KEY_11)
          && ((Cry_GddAutIcusAesCbcDecryptTb.pKeyPtr->data[0]) <= (uint8)KEY_20)))
      {
        Cry_GulAutIcusAesCbcDecKeyLength = CSM_ONE;
        /* polyspace +2 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
        Cry_GddAutIcusAesCbcDecKeyId
          = (Icus_KeyIDType)(Cry_GddAutIcusAesCbcDecryptTb.pKeyPtr->data[0]);
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }
    else if (Cry_GddAutIcusAesCbcDecryptTb.pKeyPtr->length == ICUS_BLOCK_BYTE_LENGTH)
    {
      /* Raw Key */
      Cry_GulAutIcusAesCbcDecKeyLength = ICUS_BLOCK_BYTE_LENGTH;
      Cry_GddAutIcusAesCbcDecKeyId = RAM_KEY;
      Cry_GpAutIcusAesCbcDecKeyData
        = (const uint8*)((const void*)(Cry_GddAutIcusAesCbcDecryptTb.pKeyPtr->data));
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      for (LulIndex = CSM_ZERO; LulIndex < ICUS_BLOCK_BYTE_LENGTH; LulIndex++)
      {
        /* polyspace +2 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        Cry_GaaAutIcusAesCbcDecInitVector[LulIndex]
          = Cry_GddAutIcusAesCbcDecryptTb.pInitVectorPtr[LulIndex];
      }

      if (Cry_GulAutIcusAesCbcDecKeyLength == ICUS_BLOCK_BYTE_LENGTH)
      {
        LddErr = Icus_LoadPlainKey(Cry_GpAutIcusAesCbcDecKeyData);

        if (LddErr != ERC_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutIcusAesCbcDecryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutIcusAesCbcDecryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (*(Cry_GddAutIcusAesCbcDecryptTb.pPlainTextLengthPtr)
      < Cry_GddAutIcusAesCbcDecryptTb.ulCipherTextLength)
    {
      /* Buffer size is invalid */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if ((Cry_GddAutIcusAesCbcDecryptTb.ulCipherTextLength < ICUS_BLOCK_BYTE_LENGTH)
      || ((Cry_GddAutIcusAesCbcDecryptTb.ulCipherTextLength % ICUS_BLOCK_BYTE_LENGTH) != CSM_ZERO))
    {
      /* cipherTextLength should be multiples of 16 */
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      *(Cry_GddAutIcusAesCbcDecryptTb.pPlainTextLengthPtr) = CSM_ZERO;

      LddErr = Icus_DecCbc(Cry_GddAutIcusAesCbcDecKeyId,
        (Cry_GddAutIcusAesCbcDecryptTb.ulCipherTextLength / ICUS_BLOCK_BYTE_LENGTH),
        Cry_GddAutIcusAesCbcDecryptTb.pCipherTextPtr,
        Cry_GddAutIcusAesCbcDecryptTb.pPlainTextPtr,
        Cry_GaaAutIcusAesCbcDecInitVector);

      if (LddErr == ERC_NO_ERROR)
      {
        *(Cry_GddAutIcusAesCbcDecryptTb.pPlainTextLengthPtr)
          = (Cry_GddAutIcusAesCbcDecryptTb.ulCipherTextLength / ICUS_BLOCK_BYTE_LENGTH)
          * ICUS_BLOCK_BYTE_LENGTH;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutIcusAesCbcDecryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutIcusAesCbcDecryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddAutIcusAesCbcDecryptTb.ucJobState = NO_JOB;

    /* Notify respective Service about the completion of the task */
    Csm_SymDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_SymDecryptServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_SYM_AUTICUSAESCBCDECRYPT == STD_ON) */
#endif /* (CSM_SYM_DECRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
