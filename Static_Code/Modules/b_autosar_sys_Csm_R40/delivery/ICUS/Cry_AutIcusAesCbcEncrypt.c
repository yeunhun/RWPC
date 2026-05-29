/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutIcusAesCbcEncrypt.c                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY ICUS AES - CBC Encrypt Interface        **
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
#include "Cry_AutIcusAesCbcEncrypt.h"
/* Symmetric Interface */
#if (CSM_SYM_ENCRYPT_STATUS == STD_ON)
#if (CSM_SYM_AUTICUSAESCBCENCRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "Icus_Driver.h"
#include "Icus_IntDriver.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry AutIcusAesCbcEncrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_SymKeyType* pKeyPtr;
  const uint8* pPlainTextPtr;
  uint32 ulPlainTextLength;
  const uint8* pInitVectorPtr;
  uint32 ulInitVectorDataLen;
  uint8* pCipherTextPtr;
  uint32* pCipherTextLengthPtr;
} Cry_AutIcusAesCbcEncryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_32
#include "MemMap.h"

static uint32 Cry_GulAutIcusAesCbcEncKeyLength;

#define CSM_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

static uint8 Cry_GaaAutIcusAesCbcEncInitVector[ICUS_BLOCK_BYTE_LENGTH];

#define CSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Icus_KeyIDType Cry_GddAutIcusAesCbcEncKeyId;

static const uint8* Cry_GpAutIcusAesCbcEncKeyData;

/* Global structure variable for ICUS AES CBC transfer buffer */
static Cry_AutIcusAesCbcEncryptTransferBuffer Cry_GddAutIcusAesCbcEncryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutIcusAesCbcEncryptInit                          **
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
**                      Cry_GddAutIcusAesCbcEncryptTb,                        **
**                      Cry_GaaAutIcusAesCbcEncInitVector                     **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutIcusAesCbcEncryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutIcusAesCbcEncryptTb.ucJobState = NO_JOB;
  Cry_GddAutIcusAesCbcEncryptTb.pKeyPtr = NULL_PTR;
  Cry_GddAutIcusAesCbcEncryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddAutIcusAesCbcEncryptTb.ulPlainTextLength = CSM_ZERO;
  Cry_GddAutIcusAesCbcEncryptTb.pInitVectorPtr = NULL_PTR;
  Cry_GddAutIcusAesCbcEncryptTb.ulInitVectorDataLen = CSM_ZERO;
  Cry_GddAutIcusAesCbcEncryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddAutIcusAesCbcEncryptTb.pCipherTextLengthPtr = NULL_PTR;

  (void)memset((void*)Cry_GaaAutIcusAesCbcEncInitVector, 0x00, ICUS_BLOCK_BYTE_LENGTH);

  Cry_GulAutIcusAesCbcEncKeyLength = CSM_ZERO;
  Cry_GddAutIcusAesCbcEncKeyId = INVALID_KEY;
  Cry_GpAutIcusAesCbcEncKeyData = NULL_PTR;
}

/*******************************************************************************
** Function Name        : Cry_AutIcusAesCbcEncryptStart                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of ICUS AES CBC, so that AES is able    **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutIcusAesCbcEncryptMainFunction() can process  **
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
**                        Cry_GddAutIcusAesCbcEncryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutIcusAesCbcEncryptInit,                       **
**                        Csm_SymEncryptServiceHasCallback,                   **
**                        Icus_LoadPlainKey                                   **
*******************************************************************************/
Std_ReturnType Cry_AutIcusAesCbcEncryptStart(const void* cfgPtr,
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
  if (NO_JOB == Cry_GddAutIcusAesCbcEncryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutIcusAesCbcEncryptInit();

    Cry_GddAutIcusAesCbcEncryptTb.ucJobState = JOB_START;

    if (Csm_SymEncryptServiceHasCallback() == FALSE)
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
          Cry_GulAutIcusAesCbcEncKeyLength = CSM_ONE;
          /* polyspace +1 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
          Cry_GddAutIcusAesCbcEncKeyId = (Icus_KeyIDType)(keyPtr->data[0]);
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }
      else if (keyPtr->length == ICUS_BLOCK_BYTE_LENGTH)
      {
        /* Raw Key */
        Cry_GulAutIcusAesCbcEncKeyLength = ICUS_BLOCK_BYTE_LENGTH;
        Cry_GddAutIcusAesCbcEncKeyId = RAM_KEY;
        Cry_GpAutIcusAesCbcEncKeyData = (const uint8*)((const void*)(keyPtr->data));
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
          Cry_GaaAutIcusAesCbcEncInitVector[LulIndex] = InitVectorPtr[LulIndex];
        }

        if (Cry_GulAutIcusAesCbcEncKeyLength == ICUS_BLOCK_BYTE_LENGTH)
        {
          LddErr = Icus_LoadPlainKey(Cry_GpAutIcusAesCbcEncKeyData);

          if (LddErr != ERC_NO_ERROR)
          {
            LddReturnValue = E_NOT_OK;
          }
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutIcusAesCbcEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutIcusAesCbcEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutIcusAesCbcEncryptTb.pKeyPtr = keyPtr;
      Cry_GddAutIcusAesCbcEncryptTb.pInitVectorPtr = InitVectorPtr;
      Cry_GddAutIcusAesCbcEncryptTb.ulInitVectorDataLen = InitVectorLength;
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
** Function Name        : Cry_AutIcusAesCbcEncryptUpdate                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the AES      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutIcusAesCbcEncryptMainFunction() can process  **
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
**                        Cry_GddAutIcusAesCbcEncryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymEncryptServiceHasCallback, Icus_EncCbc       **
*******************************************************************************/
Std_ReturnType Cry_AutIcusAesCbcEncryptUpdate(Csm_ConfigIdType cfgId,
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
  if (JOB_DONE == Cry_GddAutIcusAesCbcEncryptTb.ucJobState)
  {
    Cry_GddAutIcusAesCbcEncryptTb.ucJobState = JOB_UPDATE;

    if (Csm_SymEncryptServiceHasCallback() == FALSE)
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

        LddErr = Icus_EncCbc(Cry_GddAutIcusAesCbcEncKeyId,
          (plainTextLength / ICUS_BLOCK_BYTE_LENGTH),
          plainTextPtr, cipherTextPtr, Cry_GaaAutIcusAesCbcEncInitVector);

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
        Cry_GddAutIcusAesCbcEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutIcusAesCbcEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutIcusAesCbcEncryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddAutIcusAesCbcEncryptTb.ulPlainTextLength = plainTextLength;
      Cry_GddAutIcusAesCbcEncryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddAutIcusAesCbcEncryptTb.pCipherTextLengthPtr = cipherTextLengthPtr;
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
** Function Name        : Cry_AutIcusAesCbcEncryptFinish                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the AES     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutIcusAesCbcEncryptMainFunction() can finish   **
**                        thecomputation and store the result in the memory   **
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
**                        Cry_GddAutIcusAesCbcEncryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymEncryptServiceHasCallback                    **
*******************************************************************************/
Std_ReturnType Cry_AutIcusAesCbcEncryptFinish(Csm_ConfigIdType cfgId,
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
  if (JOB_DONE == Cry_GddAutIcusAesCbcEncryptTb.ucJobState)
  {
    Cry_GddAutIcusAesCbcEncKeyId = INVALID_KEY;

    Cry_GddAutIcusAesCbcEncryptTb.ucJobState = JOB_FINISH;

    if (Csm_SymEncryptServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutIcusAesCbcEncryptTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_AutIcusAesCbcEncryptMainFunction                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SymEncryptCallbackNotification() with the       **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_AutIcusAesCbcEncryptStart()                     **
**                        or Cry_AutIcusAesCbcEncryptUpdate(). For            **
**                        Cry_AutIcusAesCbcEncryptFinish invocation of        **
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
**                        Cry_GddAutIcusAesCbcEncryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Icus_LoadPlainKey, Icus_EncCbc,                     **
**                        Csm_SymEncryptCallbackNotification,                 **
**                        Csm_SymEncryptServiceFinishNotification             **
*******************************************************************************/
void Cry_AutIcusAesCbcEncryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Icus_ErrType LddErr;
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddAutIcusAesCbcEncryptTb.ucJobState)
  {
  case JOB_START:
    if (Cry_GddAutIcusAesCbcEncryptTb.ulInitVectorDataLen != ICUS_BLOCK_BYTE_LENGTH)
    {
      LddReturnValue = E_NOT_OK;
    }
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (Cry_GddAutIcusAesCbcEncryptTb.pKeyPtr->length == CSM_ONE)
    {
      /* Pre-Shared Key */
      if ((((Cry_GddAutIcusAesCbcEncryptTb.pKeyPtr->data[0]) >= (uint8)KEY_1)
        && ((Cry_GddAutIcusAesCbcEncryptTb.pKeyPtr->data[0]) <= (uint8)KEY_10))
        || (((Cry_GddAutIcusAesCbcEncryptTb.pKeyPtr->data[0]) >= (uint8)KEY_11)
          && ((Cry_GddAutIcusAesCbcEncryptTb.pKeyPtr->data[0]) <= (uint8)KEY_20)))
      {
        Cry_GulAutIcusAesCbcEncKeyLength = CSM_ONE;
        /* polyspace +2 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
        Cry_GddAutIcusAesCbcEncKeyId
          = (Icus_KeyIDType)(Cry_GddAutIcusAesCbcEncryptTb.pKeyPtr->data[0]);
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }
    else if (Cry_GddAutIcusAesCbcEncryptTb.pKeyPtr->length == ICUS_BLOCK_BYTE_LENGTH)
    {
      /* Raw Key */
      Cry_GulAutIcusAesCbcEncKeyLength = ICUS_BLOCK_BYTE_LENGTH;
      Cry_GddAutIcusAesCbcEncKeyId = RAM_KEY;
      Cry_GpAutIcusAesCbcEncKeyData
        = (const uint8*)((const void*)(Cry_GddAutIcusAesCbcEncryptTb.pKeyPtr->data));
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
        Cry_GaaAutIcusAesCbcEncInitVector[LulIndex]
          = Cry_GddAutIcusAesCbcEncryptTb.pInitVectorPtr[LulIndex];
      }

      if (Cry_GulAutIcusAesCbcEncKeyLength == ICUS_BLOCK_BYTE_LENGTH)
      {
        LddErr = Icus_LoadPlainKey(Cry_GpAutIcusAesCbcEncKeyData);

        if (LddErr != ERC_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutIcusAesCbcEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutIcusAesCbcEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (*(Cry_GddAutIcusAesCbcEncryptTb.pCipherTextLengthPtr)
      < Cry_GddAutIcusAesCbcEncryptTb.ulPlainTextLength)
    {
      /* Buffer size is invalid */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if ((Cry_GddAutIcusAesCbcEncryptTb.ulPlainTextLength < ICUS_BLOCK_BYTE_LENGTH)
      || ((Cry_GddAutIcusAesCbcEncryptTb.ulPlainTextLength % ICUS_BLOCK_BYTE_LENGTH) != CSM_ZERO))
    {
      /* plainTextLength should be multiples of 16 */
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      *(Cry_GddAutIcusAesCbcEncryptTb.pCipherTextLengthPtr) = CSM_ZERO;

      LddErr = Icus_EncCbc(Cry_GddAutIcusAesCbcEncKeyId,
        (Cry_GddAutIcusAesCbcEncryptTb.ulPlainTextLength / ICUS_BLOCK_BYTE_LENGTH),
        Cry_GddAutIcusAesCbcEncryptTb.pPlainTextPtr,
        Cry_GddAutIcusAesCbcEncryptTb.pCipherTextPtr,
        Cry_GaaAutIcusAesCbcEncInitVector);

      if (LddErr == ERC_NO_ERROR)
      {
        *(Cry_GddAutIcusAesCbcEncryptTb.pCipherTextLengthPtr)
          = (Cry_GddAutIcusAesCbcEncryptTb.ulPlainTextLength / ICUS_BLOCK_BYTE_LENGTH)
          * ICUS_BLOCK_BYTE_LENGTH;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutIcusAesCbcEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutIcusAesCbcEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    Cry_GddAutIcusAesCbcEncKeyId = INVALID_KEY;

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddAutIcusAesCbcEncryptTb.ucJobState = NO_JOB;

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

#endif /* (CSM_SYM_AUTICUSAESCBCENCRYPT == STD_ON) */
#endif /* (CSM_SYM_ENCRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
