/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmAesCtrDecrypt.c                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HSM AES - CTR Decrypt Interface         **
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
** 2.6.1.0   08-Oct-2020   JaeHyun      Redmine #25964                        **
** 1.0.4     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.3     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.2     15-May-2018   Sinil        Redmine #12729                        **
** 1.0.1     17-Apr-2018   Sinil        Redmine #12351                        **
** 1.0.0     18-Apr-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for HSM AES CTR */
#include "Cry_AutHsmAesCtrDecrypt.h"
/* Symmetric Interface */
#if (CSM_SYM_DECRYPT_STATUS == STD_ON)
#if (CSM_SYM_AUTHSMAESCTRDECRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "Hsm_AutIntDriver.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HSMAesCtrDecrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const uint8* pInitVectorPtr;
  uint32 ulInitVectorLength;
  const Csm_SymKeyType* pKeyPtr;
  const uint8* pCipherTextPtr;
  uint32 ulCipherTextLength;
  uint8* pPlainTextPtr;
  uint32* pPlainTextLengthPtr;
} Cry_AutHsmAesCtrDecryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Hsm_DataType Cry_GddAutHsmAesCtrDecDataType;

static Hsm_DataIDType Cry_GddAutHsmAesCtrDecDataIDType;

/* Global structure variable for HSM AES CTR transfer buffer */
static Cry_AutHsmAesCtrDecryptTransferBuffer Cry_GddAutHsmAesCtrDecryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/
static void Cry_AutHsmAesCtrDecryptCallback(Hsm_ErrType ddRet);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutHsmAesCtrDecryptInit                           **
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
**                      Cry_GddAutHsmAesCtrDecryptTb                          **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutHsmAesCtrDecryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutHsmAesCtrDecryptTb.ucJobState = NO_JOB;
  Cry_GddAutHsmAesCtrDecryptTb.pInitVectorPtr = NULL_PTR;
  Cry_GddAutHsmAesCtrDecryptTb.ulInitVectorLength = CSM_ZERO;
  Cry_GddAutHsmAesCtrDecryptTb.pKeyPtr = NULL_PTR;
  Cry_GddAutHsmAesCtrDecryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddAutHsmAesCtrDecryptTb.ulCipherTextLength = CSM_ZERO;
  Cry_GddAutHsmAesCtrDecryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddAutHsmAesCtrDecryptTb.pPlainTextLengthPtr = NULL_PTR;

  Cry_GddAutHsmAesCtrDecDataType = HSM_DATA_INVALID_KEY;
  Cry_GddAutHsmAesCtrDecDataIDType = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutHsmAesCtrDecryptStart                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM AES CTR, so that AES is able     **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutHsmAesCtrDecryptMainFunction() can process   **
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
**                        Cry_GddAutHsmAesCtrDecryptTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutHsmAesCtrDecryptInit,                        **
**                        Csm_SymDecryptServiceHasCallback,                   **
**                        Hsm_AesDecInit                                      **
*******************************************************************************/
Std_ReturnType Cry_AutHsmAesCtrDecryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr, const uint8* InitVectorPtr,
  uint32 InitVectorLength)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutHsmAesCtrDecryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutHsmAesCtrDecryptInit();

    /* Set the job state to JOB_START */
    Cry_GddAutHsmAesCtrDecryptTb.ucJobState = JOB_START;

    LblAsync = Csm_SymDecryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      if (InitVectorLength != HSM_AES_BLOCK_BYTE_SIZE)
      {
        /* report E_NOT_OK */
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        if (keyPtr->length == CSM_ONE)
        {
          Cry_GddAutHsmAesCtrDecDataType = HSM_DATA_AES_KEY;
          Cry_GddAutHsmAesCtrDecDataIDType = (Hsm_DataIDType)(keyPtr->data[0]);
          LddErr = HSM_NO_ERROR;
        }
        else if (keyPtr->length == HSM_AES_KEY_BYTE_SIZE)
        {
          Cry_GddAutHsmAesCtrDecDataType = HSM_DATA_AES_RAM_KEY;
          Cry_GddAutHsmAesCtrDecDataIDType = CSM_FIVE;

          LddErr = Hsm_LoadRamKey(HSM_DATA_AES_RAM_KEY, CSM_FIVE,
            keyPtr->length, (const uint8*)(keyPtr->data));
        }
        else
        {
          LddErr = HSM_KEY_INVALID_ERROR;
        }

        if (LddErr == HSM_NO_ERROR)
        {
          LddErr = Hsm_AesDecInit(LblAsync, NULL_PTR,
            Cry_GddAutHsmAesCtrDecDataType, Cry_GddAutHsmAesCtrDecDataIDType,
            HSM_AES_CTR_MODE, InitVectorPtr);
        }

        if (LddErr != HSM_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmAesCtrDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmAesCtrDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmAesCtrDecryptTb.pKeyPtr = keyPtr;
      Cry_GddAutHsmAesCtrDecryptTb.pInitVectorPtr = InitVectorPtr;
      Cry_GddAutHsmAesCtrDecryptTb.ulInitVectorLength = InitVectorLength;
    }
  }
  else
  {
    /* Job process still not complete, return CSM_E_BUSY */
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmAesCtrDecryptUpdate                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the AES      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmAesCtrDecryptMainFunction() can process   **
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
**                        Cry_GddAutHsmAesCtrDecryptTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymDecryptServiceHasCallback, Hsm_AesDecUpdate  **
*******************************************************************************/
Std_ReturnType Cry_AutHsmAesCtrDecryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* cipherTextPtr, uint32 cipherTextLength, uint8* plainTextPtr,
  uint32* plainTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddAutHsmAesCtrDecryptTb.ucJobState)
  {
    Cry_GddAutHsmAesCtrDecryptTb.ucJobState = JOB_UPDATE;

    LblAsync = Csm_SymDecryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (cipherTextLength > *plainTextLengthPtr)
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        LddErr = Hsm_AesDecUpdate(LblAsync, NULL_PTR, HSM_AES_CTR_MODE,
          cipherTextPtr, cipherTextLength, plainTextPtr, plainTextLengthPtr);

        if (LddErr != HSM_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutHsmAesCtrDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutHsmAesCtrDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmAesCtrDecryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddAutHsmAesCtrDecryptTb.ulCipherTextLength = cipherTextLength;
      Cry_GddAutHsmAesCtrDecryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddAutHsmAesCtrDecryptTb.pPlainTextLengthPtr = plainTextLengthPtr;
    }
  }
  else
  {
    /* Job process still not complete, return CSM_E_BUSY */
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmAesCtrDecryptFinish                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the AES     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmAesCtrDecryptMainFunction() can finish the**
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
**                        Cry_GddAutHsmAesCtrDecryptTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymDecryptServiceHasCallback                    **
*******************************************************************************/
Std_ReturnType Cry_AutHsmAesCtrDecryptFinish(Csm_ConfigIdType cfgId,
  uint8* plainTextPtr, uint32* plainTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);
  CSM_PARAM_UNUSED_PTR(plainTextPtr);
  CSM_PARAM_UNUSED_PTR(plainTextLengthPtr);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutHsmAesCtrDecryptTb.ucJobState)
  {
    /* Set the job state to JOB_FINISH */
    Cry_GddAutHsmAesCtrDecryptTb.ucJobState = JOB_FINISH;

    LblAsync = Csm_SymDecryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      LddErr = Hsm_AesDecFinish(LblAsync, NULL_PTR, HSM_AES_CTR_MODE);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }

      Cry_GddAutHsmAesCtrDecryptTb.ucJobState = NO_JOB;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmAesCtrDecryptCallback                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : TBD                                                 **
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
**                        Cry_GddAutHsmAesCtrDecryptTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymDecryptCallbackNotification,                 **
**                        Csm_SymDecryptServiceFinishNotification             **
*******************************************************************************/
static void Cry_AutHsmAesCtrDecryptCallback(Hsm_ErrType ddRet)
{
  Std_ReturnType LddReturnValue;

  if (ddRet == HSM_BUSY)
  {
    LddReturnValue = CSM_E_BUSY;

    Csm_SymDecryptCallbackNotification(LddReturnValue);
  }
  else
  {
    LddReturnValue = E_OK;

    switch (Cry_GddAutHsmAesCtrDecryptTb.ucJobState)
    {
    case JOB_START:
    case JOB_UPDATE:
      if (ddRet == HSM_NO_ERROR)
      {
        Cry_GddAutHsmAesCtrDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* task failure move job state to NO_JOB */
        Cry_GddAutHsmAesCtrDecryptTb.ucJobState = NO_JOB;
      }
      Csm_SymDecryptCallbackNotification(LddReturnValue);
      break;

    case JOB_FINISH:
      if (ddRet != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
      Cry_GddAutHsmAesCtrDecryptTb.ucJobState = NO_JOB;
      Csm_SymDecryptCallbackNotification(LddReturnValue);
      break;

    default:
      Csm_SymDecryptServiceFinishNotification();
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : Cry_AutHsmAesCtrDecryptMainFunction                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SymDecryptCallbackNotification() with the       **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by Cry_AutHsmAesCtrDecryptStart()**
**                        or Cry_AutHsmAesCtrDecryptUpdate(). For             **
**                        Cry_AutHsmAesCtrDecryptFinish invocation of         **
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
**                        Cry_GddAutHsmAesCtrDecryptTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        AutHsmAesCtr_Init,                                  **
**                        AutHsmAesCtr_Decrypt,                               **
**                        Csm_SymDecryptCallbackNotification,                 **
**                        Csm_SymDecryptServiceFinishNotification             **
*******************************************************************************/
void Cry_AutHsmAesCtrDecryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  Hsm_CallbackPtr LpCallback;

  LddReturnValue = E_OK;

  LpCallback = &Cry_AutHsmAesCtrDecryptCallback;

  switch (Cry_GddAutHsmAesCtrDecryptTb.ucJobState)
  {
  case JOB_START:
    if (Cry_GddAutHsmAesCtrDecryptTb.ulInitVectorLength
      != HSM_AES_BLOCK_BYTE_SIZE)
    {
      /* report E_NOT_OK */
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
      if (Cry_GddAutHsmAesCtrDecryptTb.pKeyPtr->length == CSM_ONE)
      {
        Cry_GddAutHsmAesCtrDecDataType = HSM_DATA_AES_KEY;
        Cry_GddAutHsmAesCtrDecDataIDType
          = (Hsm_DataIDType)(Cry_GddAutHsmAesCtrDecryptTb.pKeyPtr->data[0]);
        LddErr = HSM_NO_ERROR;
      }
      else if (Cry_GddAutHsmAesCtrDecryptTb.pKeyPtr->length == HSM_AES_KEY_BYTE_SIZE)
      {
        Cry_GddAutHsmAesCtrDecDataType = HSM_DATA_AES_RAM_KEY;
        Cry_GddAutHsmAesCtrDecDataIDType = CSM_FIVE;

        LddErr = Hsm_LoadRamKey(HSM_DATA_AES_RAM_KEY, CSM_FIVE,
          Cry_GddAutHsmAesCtrDecryptTb.pKeyPtr->length,
          (const uint8*)(Cry_GddAutHsmAesCtrDecryptTb.pKeyPtr->data));
      }
      else
      {
        LddErr = HSM_KEY_INVALID_ERROR;
      }

      if (LddErr == HSM_NO_ERROR)
      {
        LddErr = Hsm_AesDecInit(CSM_TRUE, LpCallback,
          Cry_GddAutHsmAesCtrDecDataType, Cry_GddAutHsmAesCtrDecDataIDType,
          HSM_AES_CTR_MODE, Cry_GddAutHsmAesCtrDecryptTb.pInitVectorPtr);
      }

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue != E_OK)
    {
      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmAesCtrDecryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_SymDecryptCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_UPDATE:
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddAutHsmAesCtrDecryptTb.ulCipherTextLength
      > *(Cry_GddAutHsmAesCtrDecryptTb.pPlainTextLengthPtr))
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      LddErr = Hsm_AesDecUpdate(CSM_TRUE, LpCallback, HSM_AES_CTR_MODE,
        Cry_GddAutHsmAesCtrDecryptTb.pCipherTextPtr,
        Cry_GddAutHsmAesCtrDecryptTb.ulCipherTextLength,
        Cry_GddAutHsmAesCtrDecryptTb.pPlainTextPtr,
        Cry_GddAutHsmAesCtrDecryptTb.pPlainTextLengthPtr);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue != E_OK)
    {
      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmAesCtrDecryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_SymDecryptCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_FINISH:
    LddErr = Hsm_AesDecFinish(CSM_TRUE, LpCallback, HSM_AES_CTR_MODE);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue != E_OK)
    {
      /* reset the state back to NO_JOB */
      Cry_GddAutHsmAesCtrDecryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_SymDecryptCallbackNotification(LddReturnValue);
    }
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

#endif /* (CSM_SYM_AUTHSMAESCTRDECRYPT == STD_ON) */
#endif /* (CSM_SYM_DECRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
