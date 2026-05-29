/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmAesEcbEncrypt.c                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HSM AES - ECB Encrypt Interface         **
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
** 1.0.3     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.2     22-Feb-2019   Sinil        Redmine #16157                        **
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
/* Header File for HSM AES ECB */
#include "Cry_AutHsmAesEcbEncrypt.h"
/* Symmetric Interface */
#if (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON)
#if (CSM_SYMBLOCK_AUTHSMAESECBENCRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "Hsm_AutIntDriver.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HSMAesEcbEncrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_SymKeyType* pKeyPtr;
  const uint8* pPlainTextPtr;
  uint32 ulPlainTextLength;
  uint8* pCipherTextPtr;
  uint32* pCipherTextLengthPtr;
} Cry_AutHsmAesEcbEncryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Hsm_DataType Cry_GddAutHsmAesEcbEncDataType;

static Hsm_DataIDType Cry_GddAutHsmAesEcbEncDataIDType;

/* Global structure variable for HSM AES ECB transfer buffer */
static Cry_AutHsmAesEcbEncryptTransferBuffer Cry_GddAutHsmAesEcbEncryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/
static void Cry_AutHsmAesEcbEncryptCallback(Hsm_ErrType ddRet);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutHsmAesEcbEncryptInit                           **
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
**                      Cry_GddAutHsmAesEcbEncryptTb                          **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutHsmAesEcbEncryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutHsmAesEcbEncryptTb.ucJobState = NO_JOB;
  Cry_GddAutHsmAesEcbEncryptTb.pKeyPtr = NULL_PTR;
  Cry_GddAutHsmAesEcbEncryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddAutHsmAesEcbEncryptTb.ulPlainTextLength = CSM_ZERO;
  Cry_GddAutHsmAesEcbEncryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddAutHsmAesEcbEncryptTb.pCipherTextLengthPtr = NULL_PTR;

  Cry_GddAutHsmAesEcbEncDataType = HSM_DATA_INVALID_KEY;
  Cry_GddAutHsmAesEcbEncDataIDType = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutHsmAesEcbEncryptStart                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM AES ECB, so that AES is able     **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutHsmAesEcbEncryptMainFunction() can process   **
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
**                        Cry_GddAutHsmAesEcbEncryptTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutHsmAesEcbEncryptInit,                        **
**                        Csm_SymBlockEncryptServiceHasCallback,              **
**                        Hsm_AesEncInit                                      **
*******************************************************************************/
Std_ReturnType Cry_AutHsmAesEcbEncryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutHsmAesEcbEncryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutHsmAesEcbEncryptInit();

    /* Set the job state to JOB_START */
    Cry_GddAutHsmAesEcbEncryptTb.ucJobState = JOB_START;

    LblAsync = Csm_SymBlockEncryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        Cry_GddAutHsmAesEcbEncDataType = HSM_DATA_AES_KEY;
        Cry_GddAutHsmAesEcbEncDataIDType = (Hsm_DataIDType)(keyPtr->data[0]);
        LddErr = HSM_NO_ERROR;
      }
      else if (keyPtr->length == HSM_AES_KEY_BYTE_SIZE)
      {
        Cry_GddAutHsmAesEcbEncDataType = HSM_DATA_AES_RAM_KEY;
        Cry_GddAutHsmAesEcbEncDataIDType = CSM_ZERO;

        LddErr = Hsm_LoadRamKey(HSM_DATA_AES_RAM_KEY, CSM_ZERO, keyPtr->length,
          (const uint8*)(keyPtr->data));
      }
      else
      {
        LddErr = HSM_KEY_INVALID_ERROR;
      }

      if (LddErr == HSM_NO_ERROR)
      {
        LddErr = Hsm_AesEncInit(LblAsync, NULL_PTR,
          Cry_GddAutHsmAesEcbEncDataType, Cry_GddAutHsmAesEcbEncDataIDType,
          HSM_AES_ECB_MODE, NULL_PTR);
      }

      if (LddErr == HSM_NO_ERROR)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmAesEcbEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmAesEcbEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmAesEcbEncryptTb.pKeyPtr = keyPtr;
    }
  }
  else
  {
    /* Other job is still processing, return CSM_E_BUSY */
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmAesEcbEncryptUpdate                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the AES      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmAesEcbEncryptMainFunction() can process   **
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
**                        Cry_GddAutHsmAesEcbEncryptTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymBlockEncryptServiceHasCallback,              **
**                        Hsm_AesEncUpdate                                    **
*******************************************************************************/
Std_ReturnType Cry_AutHsmAesEcbEncryptUpdate(Csm_ConfigIdType cfgId,
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
  if (JOB_DONE == Cry_GddAutHsmAesEcbEncryptTb.ucJobState)
  {
    /* Set the job state to JOB_UPDATE */
    Cry_GddAutHsmAesEcbEncryptTb.ucJobState = JOB_UPDATE;

    LblAsync = Csm_SymBlockEncryptServiceHasCallback();

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
        LddErr = Hsm_AesEncUpdate(LblAsync, NULL_PTR, HSM_AES_ECB_MODE,
          plainTextPtr, plainTextLength, cipherTextPtr, cipherTextLengthPtr);

        if (LddErr != HSM_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmAesEcbEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmAesEcbEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmAesEcbEncryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddAutHsmAesEcbEncryptTb.ulPlainTextLength = plainTextLength;
      Cry_GddAutHsmAesEcbEncryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddAutHsmAesEcbEncryptTb.pCipherTextLengthPtr = cipherTextLengthPtr;
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
** Function Name        : Cry_AutHsmAesEcbEncryptFinish                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the AES     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmAesEcbEncryptMainFunction() can finish the**
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
**                        Cry_GddAutHsmAesEcbEncryptTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymBlockEncryptServiceHasCallback               **
*******************************************************************************/
Std_ReturnType Cry_AutHsmAesEcbEncryptFinish(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutHsmAesEcbEncryptTb.ucJobState)
  {
    /* Set the job state to JOB_FINISH */
    Cry_GddAutHsmAesEcbEncryptTb.ucJobState = JOB_FINISH;

    LblAsync = Csm_SymBlockEncryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      LddErr = Hsm_AesEncFinish(LblAsync, NULL_PTR, HSM_AES_ECB_MODE);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }

      /* reset the state back to NO_JOB */
      Cry_GddAutHsmAesEcbEncryptTb.ucJobState = NO_JOB;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmAesEcbEncryptCallback                     **
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
**                        Cry_GddAutHsmAesEcbEncryptTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymBlockEncryptCallbackNotification,            **
**                        Csm_SymBlockEncryptServiceFinishNotification        **
*******************************************************************************/
static void Cry_AutHsmAesEcbEncryptCallback(Hsm_ErrType ddRet)
{
  Std_ReturnType LddReturnValue;

  if (ddRet == HSM_BUSY)
  {
    LddReturnValue = CSM_E_BUSY;

    Csm_SymBlockEncryptCallbackNotification(LddReturnValue);
  }
  else
  {
    LddReturnValue = E_OK;

    switch (Cry_GddAutHsmAesEcbEncryptTb.ucJobState)
    {
    case JOB_START:
    case JOB_UPDATE:
      if (ddRet == HSM_NO_ERROR)
      {
        Cry_GddAutHsmAesEcbEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* task failure move job state to NO_JOB */
        Cry_GddAutHsmAesEcbEncryptTb.ucJobState = NO_JOB;
      }
      Csm_SymBlockEncryptCallbackNotification(LddReturnValue);
      break;

    case JOB_FINISH:
      if (ddRet != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
      Cry_GddAutHsmAesEcbEncryptTb.ucJobState = NO_JOB;
      Csm_SymBlockEncryptCallbackNotification(LddReturnValue);
      break;

    default:
      Csm_SymBlockEncryptServiceFinishNotification();
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : Cry_AutHsmAesEcbEncryptMainFunction                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SymBlockEncryptCallbackNotification() with the  **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by Cry_AutHsmAesEcbEncryptStart()**
**                        or Cry_AutHsmAesEcbEncryptUpdate(). For             **
**                        Cry_AutHsmAesEcbEncryptFinish invocation of         **
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
**                        Cry_GddAutHsmAesEcbEncryptTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        AutHsmAesEcb_Init,                                  **
**                        AutHsmAesEcb_Encrypt,                               **
**                        Csm_SymBlockEncryptCallbackNotification,            **
**                        Csm_SymBlockEncryptServiceFinishNotification        **
*******************************************************************************/
void Cry_AutHsmAesEcbEncryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  Hsm_CallbackPtr LpCallback;

  LddReturnValue = E_OK;

  LpCallback = &Cry_AutHsmAesEcbEncryptCallback;

  switch (Cry_GddAutHsmAesEcbEncryptTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddAutHsmAesEcbEncryptTb.pKeyPtr->length == CSM_ONE)
    {
      Cry_GddAutHsmAesEcbEncDataType = HSM_DATA_AES_KEY;
      Cry_GddAutHsmAesEcbEncDataIDType
        = (Hsm_DataIDType)(Cry_GddAutHsmAesEcbEncryptTb.pKeyPtr->data[0]);
      LddErr = HSM_NO_ERROR;
    }
    else if (Cry_GddAutHsmAesEcbEncryptTb.pKeyPtr->length == HSM_AES_KEY_BYTE_SIZE)
    {
      Cry_GddAutHsmAesEcbEncDataType = HSM_DATA_AES_RAM_KEY;
      Cry_GddAutHsmAesEcbEncDataIDType = CSM_ZERO;

      LddErr = Hsm_LoadRamKey(HSM_DATA_AES_RAM_KEY, CSM_ZERO,
        Cry_GddAutHsmAesEcbEncryptTb.pKeyPtr->length,
        (const uint8*)(Cry_GddAutHsmAesEcbEncryptTb.pKeyPtr->data));
    }
    else
    {
      LddErr = HSM_KEY_INVALID_ERROR;
    }

    if (LddErr == HSM_NO_ERROR)
    {
      LddErr = Hsm_AesEncInit(CSM_TRUE, LpCallback,
        Cry_GddAutHsmAesEcbEncDataType, Cry_GddAutHsmAesEcbEncDataIDType,
        HSM_AES_ECB_MODE, NULL_PTR);
    }

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmAesEcbEncryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_SymBlockEncryptCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_UPDATE:
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddAutHsmAesEcbEncryptTb.ulPlainTextLength
      > *(Cry_GddAutHsmAesEcbEncryptTb.pCipherTextLengthPtr))
    {
      /* Buffer size is invalid */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if ((Cry_GddAutHsmAesEcbEncryptTb.ulPlainTextLength < HSM_AES_BLOCK_BYTE_SIZE)
      || ((Cry_GddAutHsmAesEcbEncryptTb.ulPlainTextLength % HSM_AES_BLOCK_BYTE_SIZE) != CSM_ZERO))
    {
      /* Data size is invalid */
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LddErr = Hsm_AesEncUpdate(CSM_TRUE, LpCallback, HSM_AES_ECB_MODE,
        Cry_GddAutHsmAesEcbEncryptTb.pPlainTextPtr,
        Cry_GddAutHsmAesEcbEncryptTb.ulPlainTextLength,
        Cry_GddAutHsmAesEcbEncryptTb.pCipherTextPtr,
        Cry_GddAutHsmAesEcbEncryptTb.pCipherTextLengthPtr);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue != E_OK)
    {
      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmAesEcbEncryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_SymBlockEncryptCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_FINISH:
    LddErr = Hsm_AesEncFinish(CSM_TRUE, LpCallback, HSM_AES_ECB_MODE);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue != E_OK)
    {
      /* reset the state back to NO_JOB */
      Cry_GddAutHsmAesEcbEncryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_SymBlockEncryptCallbackNotification(LddReturnValue);
    }
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

#endif /* (CSM_SYMBLOCK_AUTHSMAESECBENCRYPT == STD_ON) */
#endif /* (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
