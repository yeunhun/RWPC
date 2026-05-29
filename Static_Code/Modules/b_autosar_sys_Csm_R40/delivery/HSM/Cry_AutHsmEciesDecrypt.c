/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmEciesDecrypt.c                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HSM ECIES Decrypt Interface             **
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
** 2.6.1.0   08-Oct-2020   JaeHyun      Redmine #25964                        **
** 1.0.4     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.3     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.2     17-Apr-2018   Sinil        Redmine #12350 ,#12351                **
** 1.0.1     13-Nov-2017   Sinil        Redmine #10574                        **
** 1.0.0     18-Apr-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for HSM ECIES */
#include "Cry_AutHsmEciesDecrypt.h"
/* Asymmetric Interface */
#if (CSM_ASYM_DECRYPT_STATUS == STD_ON)
#if (CSM_ASYM_AUTHSMECIESDECRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "Hsm_AutIntDriver.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HsmEciesDecrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_AsymPrivateKeyType* pPrivateKeyPtr;
  const uint8* pCipherTextPtr;
  uint32 ulCipherTextLength;
  uint8* pPlainTextPtr;
  uint32* pPlainTextLengthPtr;
} Cry_AutHsmEciesDecryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Hsm_DataType Cry_GddAutHsmEciesDecDataType;

static Hsm_DataIDType Cry_GddAutHsmEciesDecDataIDType;

/* Global structure variable for HSM ECIES transfer buffer */
static Cry_AutHsmEciesDecryptTransferBuffer Cry_GddAutHsmEciesDecryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/
static void Cry_AutHsmEciesDecryptCallback(Hsm_ErrType ddRet);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutHsmEciesDecryptInit                            **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the ECIES module.            **
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
**                      Cry_GddAutHsmEciesDecryptTb                           **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutHsmEciesDecryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutHsmEciesDecryptTb.ucJobState = NO_JOB;
  Cry_GddAutHsmEciesDecryptTb.pPrivateKeyPtr = NULL_PTR;
  Cry_GddAutHsmEciesDecryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddAutHsmEciesDecryptTb.ulCipherTextLength = CSM_ZERO;
  Cry_GddAutHsmEciesDecryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddAutHsmEciesDecryptTb.pPlainTextLengthPtr = NULL_PTR;

  Cry_GddAutHsmEciesDecDataType = HSM_DATA_INVALID_KEY;
  Cry_GddAutHsmEciesDecDataIDType = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutHsmEciesDecryptStart                         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM ECIES, so that ECIES is able     **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutHsmEciesDecryptMainFunction() can process    **
**                        initialisation                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgPtr, keyPtr                                      **
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
**                        Cry_GddAutHsmEciesDecryptTb                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutHsmEciesDecryptInit                          **
*******************************************************************************/
Std_ReturnType Cry_AutHsmEciesDecryptStart(const void* cfgPtr,
  const Csm_AsymPrivateKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutHsmEciesDecryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutHsmEciesDecryptInit();

    /* Set the job state to JOB_START */
    Cry_GddAutHsmEciesDecryptTb.ucJobState = JOB_START;

    LblAsync = Csm_AsymDecryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        #if (CRYPTOLIB_SUPPORT_HSM_SPC58X_IAU == STD_ON)
        if (keyPtr->data[0] == HSM_DATA_CUSTOM_IAU_KEY)
        {
          Cry_GddAutHsmEciesDecDataType = HSM_DATA_CUSTOM_IAU_PRIVATE_KEY;
          Cry_GddAutHsmEciesDecDataIDType = (Hsm_DataIDType)HSM_DATA_CUSTOM_IAU_KEY;
        }
        else
        #endif
        {
          Cry_GddAutHsmEciesDecDataType = HSM_DATA_ECC_PRIVATE_KEY;
          Cry_GddAutHsmEciesDecDataIDType = (Hsm_DataIDType)(keyPtr->data[0]);
        }
        LddErr = HSM_NO_ERROR;
      }
      else if (keyPtr->length == (HSM_ECC_KEY_BYTE_SIZE))
      {
        Cry_GddAutHsmEciesDecDataType = HSM_DATA_ECC_RAM_PRIVATE_KEY;
        Cry_GddAutHsmEciesDecDataIDType = CSM_ONE;

        LddErr = Hsm_LoadRamKey(HSM_DATA_ECC_RAM_PRIVATE_KEY, CSM_ONE,
          keyPtr->length, (const uint8*)(keyPtr->data));
      }
      else
      {
        LddErr = HSM_KEY_INVALID_ERROR;
      }

      if (LddErr == HSM_NO_ERROR)
      {
        LddErr = Hsm_EciesDecInit(LblAsync, NULL_PTR,
          Cry_GddAutHsmEciesDecDataType, Cry_GddAutHsmEciesDecDataIDType);
      }

      if (LddErr == HSM_NO_ERROR)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmEciesDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmEciesDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmEciesDecryptTb.pPrivateKeyPtr = keyPtr;
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
** Function Name        : Cry_AutHsmEciesDecryptUpdate                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the ECIES    **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmEciesDecryptMainFunction() can process the**
**                        input                                               **
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
**                        Cry_GddAutHsmEciesDecryptTb                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        HsmEcies_ModExpLong                                 **
*******************************************************************************/
Std_ReturnType Cry_AutHsmEciesDecryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* cipherTextPtr, uint32 cipherTextLength, uint8* plainTextPtr,
  uint32* plainTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;
  const Csm_AutHsmEciesDecryptDataType* LpDecryptData;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);
  CSM_PARAM_UNUSED(cipherTextLength);
  CSM_PARAM_UNUSED_PTR(plainTextLengthPtr);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutHsmEciesDecryptTb.ucJobState)
  {
    /* Set the job state to JOB_UPDATE */
    Cry_GddAutHsmEciesDecryptTb.ucJobState = JOB_UPDATE;

    LblAsync = Csm_AsymDecryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:11.3 [Justified:Low] "No Impact of this rule violation" */
      LpDecryptData = (const Csm_AutHsmEciesDecryptDataType*)cipherTextPtr;
      /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      LddErr = Hsm_EciesDecUpdate(LblAsync, NULL_PTR,
        (void*)(LpDecryptData->pPdu), LpDecryptData->pParam1,
        LpDecryptData->ucEncMode, plainTextPtr);

      if (LddErr == HSM_NO_ERROR)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmEciesDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmEciesDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmEciesDecryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddAutHsmEciesDecryptTb.ulCipherTextLength = cipherTextLength;
      Cry_GddAutHsmEciesDecryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddAutHsmEciesDecryptTb.pPlainTextLengthPtr = plainTextLengthPtr;
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
** Function Name        : Cry_AutHsmEciesDecryptFinish                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the ECIES   **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmEciesDecryptMainFunction() can finish the **
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
**                        Cry_GddAutHsmEciesDecryptTb                         **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
Std_ReturnType Cry_AutHsmEciesDecryptFinish(Csm_ConfigIdType cfgId,
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
  if (JOB_DONE == Cry_GddAutHsmEciesDecryptTb.ucJobState)
  {
    /* Set the job state to JOB_FINISH */
    Cry_GddAutHsmEciesDecryptTb.ucJobState = JOB_FINISH;

    LblAsync = Csm_AsymDecryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      LddErr = Hsm_EciesDecFinish(LblAsync, NULL_PTR);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }

      /* reset the state back to NO_JOB */
      Cry_GddAutHsmEciesDecryptTb.ucJobState = NO_JOB;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmEciesDecryptCallback                      **
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
**                        Cry_GddAutHsmEciesDecryptTb                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_AsymDecryptCallbackNotification,                **
**                        Csm_AsymDecryptServiceFinishNotification            **
*******************************************************************************/
static void Cry_AutHsmEciesDecryptCallback(Hsm_ErrType ddRet)
{
  Std_ReturnType LddReturnValue;

  if (ddRet == HSM_BUSY)
  {
    LddReturnValue = CSM_E_BUSY;

    Csm_AsymDecryptCallbackNotification(LddReturnValue);
  }
  else
  {
    LddReturnValue = E_OK;

    switch (Cry_GddAutHsmEciesDecryptTb.ucJobState)
    {
    case JOB_START:
    case JOB_UPDATE:
      if (ddRet == HSM_NO_ERROR)
      {
        Cry_GddAutHsmEciesDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* task failure move job state to NO_JOB */
        Cry_GddAutHsmEciesDecryptTb.ucJobState = NO_JOB;
      }
      Csm_AsymDecryptCallbackNotification(LddReturnValue);
      break;

    case JOB_FINISH:
      if (ddRet != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
      Cry_GddAutHsmEciesDecryptTb.ucJobState = NO_JOB;
      Csm_AsymDecryptCallbackNotification(LddReturnValue);
      break;

    default:
      Csm_AsymDecryptServiceFinishNotification();
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : Cry_AutHsmEciesDecryptMainFunction                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_AsymDecryptCallbackNotification() with the      **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by Cry_AutHsmEciesDecryptStart() **
**                        or Cry_AutHsmEciesDecryptUpdate(). For              **
**                        Cry_AutHsmEciesDecryptFinish invocation of          **
**                        Csm_AsymDecryptCallbackNotification()               **
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
**                        Cry_GddAutHsmEciesDecryptTb                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_AsymDecryptCallbackNotification,                **
**                        AutHsmEcies_ModExpLong, EscCallback_setFunction,    **
**                        Csm_AsymDecryptServiceFinishNotification            **
*******************************************************************************/
void Cry_AutHsmEciesDecryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  Hsm_CallbackPtr LpCallback;
  const Csm_AutHsmEciesDecryptDataType* LpDecryptData;

  LpCallback = &Cry_AutHsmEciesDecryptCallback;

  switch (Cry_GddAutHsmEciesDecryptTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +1 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddAutHsmEciesDecryptTb.pPrivateKeyPtr->length == CSM_ONE)
    {
      #if (CRYPTOLIB_SUPPORT_HSM_SPC58X_IAU == STD_ON)
      if (Cry_GddAutHsmEciesDecryptTb.pPrivateKeyPtr->data[0] == HSM_DATA_CUSTOM_IAU_KEY)
      {
        Cry_GddAutHsmEciesDecDataType = HSM_DATA_CUSTOM_IAU_PRIVATE_KEY;
        Cry_GddAutHsmEciesDecDataIDType = (Hsm_DataIDType)HSM_DATA_CUSTOM_IAU_KEY;
      }
      else
      #endif
      {
        Cry_GddAutHsmEciesDecDataType = HSM_DATA_ECC_PRIVATE_KEY;
        Cry_GddAutHsmEciesDecDataIDType
          = (Hsm_DataIDType)(Cry_GddAutHsmEciesDecryptTb.pPrivateKeyPtr->data[0]);
      }
      LddErr = HSM_NO_ERROR;
    }
    else if (Cry_GddAutHsmEciesDecryptTb.pPrivateKeyPtr->length == (HSM_ECC_KEY_BYTE_SIZE))
    {
      Cry_GddAutHsmEciesDecDataType = HSM_DATA_ECC_RAM_PRIVATE_KEY;
      Cry_GddAutHsmEciesDecDataIDType = CSM_ONE;

      LddErr = Hsm_LoadRamKey(HSM_DATA_ECC_RAM_PRIVATE_KEY, CSM_ONE,
        Cry_GddAutHsmEciesDecryptTb.pPrivateKeyPtr->length,
        (const uint8*)(Cry_GddAutHsmEciesDecryptTb.pPrivateKeyPtr->data));
    }
    else
    {
      LddErr = HSM_KEY_INVALID_ERROR;
    }

    if (LddErr == HSM_NO_ERROR)
    {
      LddErr = Hsm_EciesDecInit(CSM_TRUE, LpCallback,
        Cry_GddAutHsmEciesDecDataType, Cry_GddAutHsmEciesDecDataIDType);
    }

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmEciesDecryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_AsymDecryptCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_UPDATE:
    /* polyspace +2 MISRA-C3:11.3 [Justified:Low] "No Impact of this rule violation" */
    LpDecryptData = (const Csm_AutHsmEciesDecryptDataType*)
      Cry_GddAutHsmEciesDecryptTb.pCipherTextPtr;
    /* polyspace +3 MISRA-C3:18.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +3 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    LddErr = Hsm_EciesDecUpdate(CSM_TRUE, LpCallback,
      (void*)(LpDecryptData->pPdu), LpDecryptData->pParam1,
      LpDecryptData->ucEncMode, Cry_GddAutHsmEciesDecryptTb.pPlainTextPtr);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmEciesDecryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_AsymDecryptCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_FINISH:
    LddErr = Hsm_EciesDecFinish(CSM_TRUE, LpCallback);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutHsmEciesDecryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_AsymDecryptCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_AsymDecryptServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_ASYM_AUTHSMECIESDECRYPT == STD_ON) */
#endif /* (CSM_ASYM_DECRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
