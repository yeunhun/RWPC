/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmAesCbcEncrypt.c                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HSM AES - CBC Encrypt Interface         **
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
** 1.0.2     17-Apr-2018   Sinil        Redmine #12351                        **
** 1.0.1     19-Mar-2018   Sinil        Redmine #11987                        **
** 1.0.0     18-Apr-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for HSM AES CBC */
#include "Cry_AutHsmAesCbcEncrypt.h"
/* Symmetric Interface */
#if (CSM_SYM_ENCRYPT_STATUS == STD_ON)
#if (CSM_SYM_AUTHSMAESCBCENCRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "Hsm_AutIntDriver.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HSMAesCbcEncrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const uint8* pInitVectorPtr;
  uint32 ulInitVectorLength;
  const Csm_SymKeyType* pKeyPtr;
  const uint8* pPlainTextPtr;
  uint32 ulPlainTextLength;
  uint8* pCipherTextPtr;
  uint32* pCipherTextLengthPtr;
} Cry_AutHsmAesCbcEncryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Hsm_DataType Cry_GddAutHsmAesCbcEncDataType;

static Hsm_DataIDType Cry_GddAutHsmAesCbcEncDataIDType;

/* Global structure variable for HSM AES CBC transfer buffer */
static Cry_AutHsmAesCbcEncryptTransferBuffer Cry_GddAutHsmAesCbcEncryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/
static void Cry_AutHsmAesCbcEncryptCallback(Hsm_ErrType ddRet);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutHsmAesCbcEncryptInit                           **
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
**                      Cry_GddAutHsmAesCbcEncryptTb                          **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutHsmAesCbcEncryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutHsmAesCbcEncryptTb.ucJobState = NO_JOB;
  Cry_GddAutHsmAesCbcEncryptTb.pInitVectorPtr = NULL_PTR;
  Cry_GddAutHsmAesCbcEncryptTb.ulInitVectorLength = CSM_ZERO;
  Cry_GddAutHsmAesCbcEncryptTb.pKeyPtr = NULL_PTR;
  Cry_GddAutHsmAesCbcEncryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddAutHsmAesCbcEncryptTb.ulPlainTextLength = CSM_ZERO;
  Cry_GddAutHsmAesCbcEncryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddAutHsmAesCbcEncryptTb.pCipherTextLengthPtr = NULL_PTR;

  Cry_GddAutHsmAesCbcEncDataType = HSM_DATA_INVALID_KEY;
  Cry_GddAutHsmAesCbcEncDataIDType = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutHsmAesCbcEncryptStart                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM AES CBC, so that AES is able     **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutHsmAesCbcEncryptMainFunction() can process   **
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
**                        Cry_GddAutHsmAesCbcEncryptTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutHsmAesCbcEncryptInit,                        **
**                        Csm_SymEncryptServiceHasCallback,                   **
**                        Hsm_AesEncInit                                      **
*******************************************************************************/
Std_ReturnType Cry_AutHsmAesCbcEncryptStart(const void* cfgPtr,
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
  if (NO_JOB == Cry_GddAutHsmAesCbcEncryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutHsmAesCbcEncryptInit();

    /* Set the job state to JOB_START */
    Cry_GddAutHsmAesCbcEncryptTb.ucJobState = JOB_START;

    LblAsync = Csm_SymEncryptServiceHasCallback();

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
          Cry_GddAutHsmAesCbcEncDataType = HSM_DATA_AES_KEY;
          Cry_GddAutHsmAesCbcEncDataIDType = (Hsm_DataIDType)(keyPtr->data[0]);
          LddErr = HSM_NO_ERROR;
        }
        else if (keyPtr->length == HSM_AES_KEY_BYTE_SIZE)
        {
          Cry_GddAutHsmAesCbcEncDataType = HSM_DATA_AES_RAM_KEY;
          Cry_GddAutHsmAesCbcEncDataIDType = CSM_TWO;

          LddErr = Hsm_LoadRamKey(HSM_DATA_AES_RAM_KEY, CSM_TWO, keyPtr->length,
            (const uint8*)(keyPtr->data));
        }
        else
        {
          LddErr = HSM_KEY_INVALID_ERROR;
        }

        if (LddErr == HSM_NO_ERROR)
        {
          LddErr = Hsm_AesEncInit(LblAsync, NULL_PTR,
            Cry_GddAutHsmAesCbcEncDataType, Cry_GddAutHsmAesCbcEncDataIDType,
            HSM_AES_CBC_MODE, InitVectorPtr);
        }

        if (LddErr != HSM_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmAesCbcEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmAesCbcEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmAesCbcEncryptTb.pKeyPtr = keyPtr;
      Cry_GddAutHsmAesCbcEncryptTb.pInitVectorPtr = InitVectorPtr;
      Cry_GddAutHsmAesCbcEncryptTb.ulInitVectorLength = InitVectorLength;
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
** Function Name        : Cry_AutHsmAesCbcEncryptUpdate                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the AES      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmAesCbcEncryptMainFunction() can process   **
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
**                        Cry_GddAutHsmAesCbcEncryptTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymEncryptServiceHasCallback, Hsm_AesEncUpdate  **
*******************************************************************************/
Std_ReturnType Cry_AutHsmAesCbcEncryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* plainTextPtr, uint32 plainTextLength, uint8* cipherTextPtr,
  uint32* cipherTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutHsmAesCbcEncryptTb.ucJobState)
  {
    /* Set the job state to JOB_UPDATE */
    Cry_GddAutHsmAesCbcEncryptTb.ucJobState = JOB_UPDATE;

    LblAsync = Csm_SymEncryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (plainTextLength > *cipherTextLengthPtr)
      {
        /* Buffer size is invalid */
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if ((plainTextLength < HSM_AES_BLOCK_BYTE_SIZE)
        || ((plainTextLength % HSM_AES_BLOCK_BYTE_SIZE) != CSM_ZERO))
      {
        /* Data size is invalid */
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LddErr = Hsm_AesEncUpdate(LblAsync, NULL_PTR, HSM_AES_CBC_MODE,
          plainTextPtr, plainTextLength, cipherTextPtr, cipherTextLengthPtr);

        if (LddErr != HSM_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmAesCbcEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmAesCbcEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmAesCbcEncryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddAutHsmAesCbcEncryptTb.ulPlainTextLength = plainTextLength;
      Cry_GddAutHsmAesCbcEncryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddAutHsmAesCbcEncryptTb.pCipherTextLengthPtr = cipherTextLengthPtr;
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
** Function Name        : Cry_AutHsmAesCbcEncryptFinish                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the AES     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmAesCbcEncryptMainFunction() can finish the**
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
**                        Cry_GddAutHsmAesCbcEncryptTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymEncryptServiceHasCallback                    **
*******************************************************************************/
Std_ReturnType Cry_AutHsmAesCbcEncryptFinish(Csm_ConfigIdType cfgId,
  uint8* cipherTextPtr, uint32* cipherTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);
  CSM_PARAM_UNUSED_PTR(cipherTextPtr);
  CSM_PARAM_UNUSED_PTR(cipherTextLengthPtr);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutHsmAesCbcEncryptTb.ucJobState)
  {
    /* Set the job state to JOB_FINISH */
    Cry_GddAutHsmAesCbcEncryptTb.ucJobState = JOB_FINISH;

    LblAsync = Csm_SymEncryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      LddErr = Hsm_AesEncFinish(LblAsync, NULL_PTR, HSM_AES_CBC_MODE);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }

      /* reset the state back to NO_JOB */
      Cry_GddAutHsmAesCbcEncryptTb.ucJobState = NO_JOB;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmAesCbcEncryptCallback                     **
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
**                        Cry_GddAutHsmAesCbcEncryptTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymEncryptCallbackNotification,                 **
**                        Csm_SymEncryptServiceFinishNotification             **
*******************************************************************************/
static void Cry_AutHsmAesCbcEncryptCallback(Hsm_ErrType ddRet)
{
  Std_ReturnType LddReturnValue;

  if (ddRet == HSM_BUSY)
  {
    LddReturnValue = CSM_E_BUSY;

    Csm_SymEncryptCallbackNotification(LddReturnValue);
  }
  else
  {
    LddReturnValue = E_OK;

    switch (Cry_GddAutHsmAesCbcEncryptTb.ucJobState)
    {
    case JOB_START:
    case JOB_UPDATE:
      if (ddRet == HSM_NO_ERROR)
      {
        Cry_GddAutHsmAesCbcEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* task failure move job state to NO_JOB */
        Cry_GddAutHsmAesCbcEncryptTb.ucJobState = NO_JOB;
      }
      Csm_SymEncryptCallbackNotification(LddReturnValue);
      break;

    case JOB_FINISH:
      if (ddRet != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
      Cry_GddAutHsmAesCbcEncryptTb.ucJobState = NO_JOB;
      Csm_SymEncryptCallbackNotification(LddReturnValue);
      break;

    default:
      Csm_SymEncryptServiceFinishNotification();
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : Cry_AutHsmAesCbcEncryptMainFunction                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SymEncryptCallbackNotification() with the       **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by Cry_AutHsmAesCbcEncryptStart()**
**                        or Cry_AutHsmAesCbcEncryptUpdate(). For             **
**                        Cry_AutHsmAesCbcEncryptFinish invocation of         **
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
**                        Cry_GddAutHsmAesCbcEncryptTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        AutHsmAesCbc_Init,                                  **
**                        AutHsmAesCbc_Encrypt,                               **
**                        Csm_SymEncryptCallbackNotification,                 **
**                        Csm_SymEncryptServiceFinishNotification             **
*******************************************************************************/
void Cry_AutHsmAesCbcEncryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  Hsm_CallbackPtr LpCallback;

  LddReturnValue = E_OK;

  LpCallback = &Cry_AutHsmAesCbcEncryptCallback;

  switch (Cry_GddAutHsmAesCbcEncryptTb.ucJobState)
  {
  case JOB_START:
    if (Cry_GddAutHsmAesCbcEncryptTb.ulInitVectorLength
      != HSM_AES_BLOCK_BYTE_SIZE)
    {
      /* report E_NOT_OK */
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
      if (Cry_GddAutHsmAesCbcEncryptTb.pKeyPtr->length == CSM_ONE)
      {
        Cry_GddAutHsmAesCbcEncDataType = HSM_DATA_AES_KEY;
        Cry_GddAutHsmAesCbcEncDataIDType
          = (Hsm_DataIDType)(Cry_GddAutHsmAesCbcEncryptTb.pKeyPtr->data[0]);
        LddErr = HSM_NO_ERROR;
      }
      else if (Cry_GddAutHsmAesCbcEncryptTb.pKeyPtr->length == HSM_AES_KEY_BYTE_SIZE)
      {
        Cry_GddAutHsmAesCbcEncDataType = HSM_DATA_AES_RAM_KEY;
        Cry_GddAutHsmAesCbcEncDataIDType = CSM_TWO;

        LddErr = Hsm_LoadRamKey(HSM_DATA_AES_RAM_KEY, CSM_TWO,
          Cry_GddAutHsmAesCbcEncryptTb.pKeyPtr->length,
          (const uint8*)(Cry_GddAutHsmAesCbcEncryptTb.pKeyPtr->data));
      }
      else
      {
        LddErr = HSM_KEY_INVALID_ERROR;
      }

      if (LddErr == HSM_NO_ERROR)
      {
        LddErr = Hsm_AesEncInit(CSM_TRUE, LpCallback,
          Cry_GddAutHsmAesCbcEncDataType, Cry_GddAutHsmAesCbcEncDataIDType,
          HSM_AES_CBC_MODE, Cry_GddAutHsmAesCbcEncryptTb.pInitVectorPtr);
      }

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue != E_OK)
    {
      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmAesCbcEncryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_SymEncryptCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_UPDATE:
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddAutHsmAesCbcEncryptTb.ulPlainTextLength
      > *(Cry_GddAutHsmAesCbcEncryptTb.pCipherTextLengthPtr))
    {
      /* Buffer size is invalid */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if ((Cry_GddAutHsmAesCbcEncryptTb.ulPlainTextLength < HSM_AES_BLOCK_BYTE_SIZE)
      || ((Cry_GddAutHsmAesCbcEncryptTb.ulPlainTextLength % HSM_AES_BLOCK_BYTE_SIZE) != CSM_ZERO))
    {
      /* Data size is invalid */
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LddErr = Hsm_AesEncUpdate(CSM_TRUE, LpCallback, HSM_AES_CBC_MODE,
        Cry_GddAutHsmAesCbcEncryptTb.pPlainTextPtr,
        Cry_GddAutHsmAesCbcEncryptTb.ulPlainTextLength,
        Cry_GddAutHsmAesCbcEncryptTb.pCipherTextPtr,
        Cry_GddAutHsmAesCbcEncryptTb.pCipherTextLengthPtr);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue != E_OK)
    {
      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmAesCbcEncryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_SymEncryptCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_FINISH:
    LddErr = Hsm_AesEncFinish(CSM_TRUE, LpCallback, HSM_AES_CBC_MODE);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue != E_OK)
    {
      /* reset the state back to NO_JOB */
      Cry_GddAutHsmAesCbcEncryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_SymEncryptCallbackNotification(LddReturnValue);
    }
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

#endif /* (CSM_SYM_AUTHSMAESCBCENCRYPT == STD_ON) */
#endif /* (CSM_SYM_ENCRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
