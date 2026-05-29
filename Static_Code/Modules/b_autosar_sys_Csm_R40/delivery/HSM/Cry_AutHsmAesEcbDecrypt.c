/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmAesEcbDecrypt.c                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HSM AES - ECB Decrypt Interface         **
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
#include "Cry_AutHsmAesEcbDecrypt.h"
/* Symmetric Interface */
#if (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON)
#if (CSM_SYMBLOCK_AUTHSMAESECBDECRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "Hsm_AutIntDriver.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HSMAesEcbDecrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_SymKeyType* pKeyPtr;
  const uint8* pCipherTextPtr;
  uint32 ulCipherTextLength;
  uint8* pPlainTextPtr;
  uint32* pPlainTextLengthPtr;
} Cry_AutHsmAesEcbDecryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Hsm_DataType Cry_GddAutHsmAesEcbDecDataType;

static Hsm_DataIDType Cry_GddAutHsmAesEcbDecDataIDType;

/* Global structure variable for HSM AES ECB transfer buffer */
static Cry_AutHsmAesEcbDecryptTransferBuffer Cry_GddAutHsmAesEcbDecryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/
static void Cry_AutHsmAesEcbDecryptCallback(Hsm_ErrType ddRet);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutHsmAesEcbDecryptInit                           **
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
**                      Cry_GddAutHsmAesEcbDecryptTb                          **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutHsmAesEcbDecryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutHsmAesEcbDecryptTb.ucJobState = NO_JOB;
  Cry_GddAutHsmAesEcbDecryptTb.pKeyPtr = NULL_PTR;
  Cry_GddAutHsmAesEcbDecryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddAutHsmAesEcbDecryptTb.ulCipherTextLength = CSM_ZERO;
  Cry_GddAutHsmAesEcbDecryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddAutHsmAesEcbDecryptTb.pPlainTextLengthPtr = NULL_PTR;

  Cry_GddAutHsmAesEcbDecDataType = HSM_DATA_INVALID_KEY;
  Cry_GddAutHsmAesEcbDecDataIDType = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutHsmAesEcbDecryptStart                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM AES ECB, so that AES is able     **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutHsmAesEcbDecryptMainFunction() can process   **
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
**                        Cry_GddAutHsmAesEcbDecryptTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutHsmAesEcbDecryptInit,                        **
**                        Csm_SymBlockDecryptServiceHasCallback,              **
**                        Hsm_AesDecInit                                      **
*******************************************************************************/
Std_ReturnType Cry_AutHsmAesEcbDecryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutHsmAesEcbDecryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutHsmAesEcbDecryptInit();

    /* Set the job state to JOB_START */
    Cry_GddAutHsmAesEcbDecryptTb.ucJobState = JOB_START;

    LblAsync = Csm_SymBlockDecryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        Cry_GddAutHsmAesEcbDecDataType = HSM_DATA_AES_KEY;
        Cry_GddAutHsmAesEcbDecDataIDType = (Hsm_DataIDType)(keyPtr->data[0]);
        LddErr = HSM_NO_ERROR;
      }
      else if (keyPtr->length == HSM_AES_KEY_BYTE_SIZE)
      {
        Cry_GddAutHsmAesEcbDecDataType = HSM_DATA_AES_RAM_KEY;
        Cry_GddAutHsmAesEcbDecDataIDType = CSM_ONE;

        LddErr = Hsm_LoadRamKey(HSM_DATA_AES_RAM_KEY, CSM_ONE, keyPtr->length,
          (const uint8*)(keyPtr->data));
      }
      else
      {
        LddErr = HSM_KEY_INVALID_ERROR;
      }

      if (LddErr == HSM_NO_ERROR)
      {
        LddErr = Hsm_AesDecInit(LblAsync, NULL_PTR,
          Cry_GddAutHsmAesEcbDecDataType, Cry_GddAutHsmAesEcbDecDataIDType,
          HSM_AES_ECB_MODE, NULL_PTR);
      }

      if (LddErr == HSM_NO_ERROR)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmAesEcbDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmAesEcbDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmAesEcbDecryptTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_AutHsmAesEcbDecryptUpdate                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the AES      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmAesEcbDecryptMainFunction() can process   **
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
**                        Cry_GddAutHsmAesEcbDecryptTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymBlockDecryptServiceHasCallback,              **
**                        Hsm_AesDecUpdate                                    **
*******************************************************************************/
Std_ReturnType Cry_AutHsmAesEcbDecryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* cipherTextPtr, uint32 cipherTextLength, uint8* plainTextPtr,
  uint32* plainTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutHsmAesEcbDecryptTb.ucJobState)
  {
    /* Set the job state to JOB_UPDATE */
    Cry_GddAutHsmAesEcbDecryptTb.ucJobState = JOB_UPDATE;

    LblAsync = Csm_SymBlockDecryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (cipherTextLength > *plainTextLengthPtr)
      {
        /* Buffer size is invalid */
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if ((cipherTextLength < HSM_AES_BLOCK_BYTE_SIZE)
        || ((cipherTextLength % HSM_AES_BLOCK_BYTE_SIZE) != CSM_ZERO))
      {
        /* Data size is invalid */
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LddErr = Hsm_AesDecUpdate(LblAsync, NULL_PTR, HSM_AES_ECB_MODE,
          cipherTextPtr, cipherTextLength, plainTextPtr, plainTextLengthPtr);

        if (LddErr != HSM_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmAesEcbDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmAesEcbDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmAesEcbDecryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddAutHsmAesEcbDecryptTb.ulCipherTextLength = cipherTextLength;
      Cry_GddAutHsmAesEcbDecryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddAutHsmAesEcbDecryptTb.pPlainTextLengthPtr = plainTextLengthPtr;
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
** Function Name        : Cry_AutHsmAesEcbDecryptFinish                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the AES     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmAesEcbDecryptMainFunction() can finish the**
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
**                        Cry_GddAutHsmAesEcbDecryptTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymBlockDecryptServiceHasCallback               **
*******************************************************************************/
Std_ReturnType Cry_AutHsmAesEcbDecryptFinish(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutHsmAesEcbDecryptTb.ucJobState)
  {
    /* Set the job state to JOB_FINISH */
    Cry_GddAutHsmAesEcbDecryptTb.ucJobState = JOB_FINISH;

    LblAsync = Csm_SymBlockDecryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      LddErr = Hsm_AesDecFinish(LblAsync, NULL_PTR, HSM_AES_ECB_MODE);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }

      Cry_GddAutHsmAesEcbDecryptTb.ucJobState = NO_JOB;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmAesEcbDecryptCallback                     **
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
**                        Cry_GddAutHsmAesEcbDecryptTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymBlockDecryptCallbackNotification,            **
**                        Csm_SymBlockDecryptServiceFinishNotification        **
*******************************************************************************/
static void Cry_AutHsmAesEcbDecryptCallback(Hsm_ErrType ddRet)
{
  Std_ReturnType LddReturnValue;

  if (ddRet == HSM_BUSY)
  {
    LddReturnValue = CSM_E_BUSY;

    Csm_SymBlockDecryptCallbackNotification(LddReturnValue);
  }
  else
  {
    LddReturnValue = E_OK;

    switch (Cry_GddAutHsmAesEcbDecryptTb.ucJobState)
    {
    case JOB_START:
    case JOB_UPDATE:
      if (ddRet == HSM_NO_ERROR)
      {
        Cry_GddAutHsmAesEcbDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* task failure move job state to NO_JOB */
        Cry_GddAutHsmAesEcbDecryptTb.ucJobState = NO_JOB;
      }
      Csm_SymBlockDecryptCallbackNotification(LddReturnValue);
      break;

    case JOB_FINISH:
      if (ddRet != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
      Cry_GddAutHsmAesEcbDecryptTb.ucJobState = NO_JOB;
      Csm_SymBlockDecryptCallbackNotification(LddReturnValue);
      break;

    default:
      Csm_SymBlockDecryptServiceFinishNotification();
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : Cry_AutHsmAesEcbDecryptMainFunction                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SymBlockDecryptCallbackNotification() with the  **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by Cry_AutHsmAesEcbDecryptStart()**
**                        or Cry_AutHsmAesEcbDecryptUpdate(). For             **
**                        Cry_AutHsmAesEcbDecryptFinish invocation of         **
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
**                        Cry_GddAutHsmAesEcbDecryptTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        AutHsmAesEcb_Init,                                  **
**                        AutHsmAesEcb_Decrypt,                               **
**                        Csm_SymBlockDecryptCallbackNotification,            **
**                        Csm_SymBlockDecryptServiceFinishNotification        **
*******************************************************************************/
void Cry_AutHsmAesEcbDecryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  Hsm_CallbackPtr LpCallback;

  LddReturnValue = E_OK;

  LpCallback = &Cry_AutHsmAesEcbDecryptCallback;

  switch (Cry_GddAutHsmAesEcbDecryptTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddAutHsmAesEcbDecryptTb.pKeyPtr->length == CSM_ONE)
    {
      Cry_GddAutHsmAesEcbDecDataType = HSM_DATA_AES_KEY;
      Cry_GddAutHsmAesEcbDecDataIDType
        = (Hsm_DataIDType)(Cry_GddAutHsmAesEcbDecryptTb.pKeyPtr->data[0]);
      LddErr = HSM_NO_ERROR;
    }
    else if (Cry_GddAutHsmAesEcbDecryptTb.pKeyPtr->length == HSM_AES_KEY_BYTE_SIZE)
    {
      Cry_GddAutHsmAesEcbDecDataType = HSM_DATA_AES_RAM_KEY;
      Cry_GddAutHsmAesEcbDecDataIDType = CSM_ONE;

      LddErr = Hsm_LoadRamKey(HSM_DATA_AES_RAM_KEY, CSM_ONE,
        Cry_GddAutHsmAesEcbDecryptTb.pKeyPtr->length,
        (const uint8*)(Cry_GddAutHsmAesEcbDecryptTb.pKeyPtr->data));
    }
    else
    {
      LddErr = HSM_KEY_INVALID_ERROR;
    }

    if (LddErr == HSM_NO_ERROR)
    {
      LddErr = Hsm_AesDecInit(CSM_TRUE, LpCallback,
        Cry_GddAutHsmAesEcbDecDataType, Cry_GddAutHsmAesEcbDecDataIDType,
        HSM_AES_ECB_MODE, NULL_PTR);
    }

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmAesEcbDecryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_SymBlockDecryptCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_UPDATE:
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddAutHsmAesEcbDecryptTb.ulCipherTextLength
      > *(Cry_GddAutHsmAesEcbDecryptTb.pPlainTextLengthPtr))
    {
      /* Buffer size is invalid */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if ((Cry_GddAutHsmAesEcbDecryptTb.ulCipherTextLength < HSM_AES_BLOCK_BYTE_SIZE)
      || ((Cry_GddAutHsmAesEcbDecryptTb.ulCipherTextLength % HSM_AES_BLOCK_BYTE_SIZE) != CSM_ZERO))
    {
      /* Data size is invalid */
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LddErr = Hsm_AesDecUpdate(CSM_TRUE, LpCallback, HSM_AES_ECB_MODE,
        Cry_GddAutHsmAesEcbDecryptTb.pCipherTextPtr,
        Cry_GddAutHsmAesEcbDecryptTb.ulCipherTextLength,
        Cry_GddAutHsmAesEcbDecryptTb.pPlainTextPtr,
        Cry_GddAutHsmAesEcbDecryptTb.pPlainTextLengthPtr);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue != E_OK)
    {
      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmAesEcbDecryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_SymBlockDecryptCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_FINISH:
    LddErr = Hsm_AesDecFinish(CSM_TRUE, LpCallback, HSM_AES_ECB_MODE);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue != E_OK)
    {
      /* reset the state back to NO_JOB */
      Cry_GddAutHsmAesEcbDecryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_SymBlockDecryptCallbackNotification(LddReturnValue);
    }
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

#endif /* (CSM_SYMBLOCK_AUTHSMAESECBDECRYPT == STD_ON) */
#endif /* (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
