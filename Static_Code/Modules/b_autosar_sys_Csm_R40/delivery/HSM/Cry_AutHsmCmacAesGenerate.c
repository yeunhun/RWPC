/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmCmacAesGenerate.c                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HSM CMAC AES Generate Interface         **
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
/* Header File for HSM CMAC AES Generate */
#include "Cry_AutHsmCmacAesGenerate.h"
/* Mac Interface */
#if (CSM_MAC_GENERATE_STATUS == STD_ON)
#if (CSM_MAC_AUTHSMCMACAESGENERATE == STD_ON)
#include "Csm_Cbk.h"
#include "Hsm_AutIntDriver.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HSMCmacAesGenerate Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_SymKeyType* pKeyPtr;
  const uint8* pDataPtr;
  uint32 ulDataLength;
  uint8* pResultPtr;
  uint32* pResultLengthPtr;
  boolean blTruncationIsAllowed;
} Cry_AutHsmCmacAesGenerateTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Hsm_DataType Cry_GddAutHsmCmacAesGenDataType;

static Hsm_DataIDType Cry_GddAutHsmCmacAesGenDataIDType;

/* Global variable for HSM CMAC AES transfer buffer structure */
static Cry_AutHsmCmacAesGenerateTransferBuffer Cry_GddAutHsmCmacAesGenerateTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/
static void Cry_AutHsmCmacAesGenerateCallback(Hsm_ErrType ddRet);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutHsmCmacAesGenerateInit                         **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the HSM CMAC AES             **
**                      module. All the Global variables will be initialized  **
**                      after the successful completion of this API.          **
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
**                      Cry_GddAutHsmCmacAesGenerateTb                        **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutHsmCmacAesGenerateInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutHsmCmacAesGenerateTb.ucJobState = NO_JOB;
  Cry_GddAutHsmCmacAesGenerateTb.pKeyPtr = NULL_PTR;
  Cry_GddAutHsmCmacAesGenerateTb.pDataPtr = NULL_PTR;
  Cry_GddAutHsmCmacAesGenerateTb.ulDataLength = CSM_ZERO;
  Cry_GddAutHsmCmacAesGenerateTb.pResultPtr = NULL_PTR;
  Cry_GddAutHsmCmacAesGenerateTb.pResultLengthPtr = NULL_PTR;
  Cry_GddAutHsmCmacAesGenerateTb.blTruncationIsAllowed = CSM_FALSE;

  Cry_GddAutHsmCmacAesGenDataType = HSM_DATA_INVALID_KEY;
  Cry_GddAutHsmCmacAesGenDataIDType = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutHsmCmacAesGenerateStart                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM CMAC AES, so that it is          **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutHsmCmacAesGenerateMainFunction() can         **
**                        process initialisation                              **
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
**                        Cry_GddAutHsmCmacAesGenerateTb                      **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutHsmCmacAesGenerateInit,                      **
**                        Csm_MacGenerateServiceHasCallback,                  **
**                        Hsm_AesCmacInit                                     **
*******************************************************************************/
Std_ReturnType Cry_AutHsmCmacAesGenerateStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddAutHsmCmacAesGenerateTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutHsmCmacAesGenerateInit();

    /* Set the job state to JOB_START */
    Cry_GddAutHsmCmacAesGenerateTb.ucJobState = JOB_START;

    LblAsync = Csm_MacGenerateServiceHasCallback();

    if (LblAsync == CSM_FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        Cry_GddAutHsmCmacAesGenDataType = HSM_DATA_AES_KEY;
        Cry_GddAutHsmCmacAesGenDataIDType = (Hsm_DataIDType)(keyPtr->data[0]);
        LddErr = HSM_NO_ERROR;
      }
      else if (keyPtr->length == HSM_AES_KEY_BYTE_SIZE)
      {
        Cry_GddAutHsmCmacAesGenDataType = HSM_DATA_AES_RAM_KEY;
        Cry_GddAutHsmCmacAesGenDataIDType = CSM_SIX;

        LddErr = Hsm_LoadRamKey(HSM_DATA_AES_RAM_KEY, CSM_SIX,
          keyPtr->length, (const uint8*)(keyPtr->data));
      }
      else
      {
        LddErr = HSM_KEY_INVALID_ERROR;
      }

      if (LddErr == HSM_NO_ERROR)
      {
        LddErr = Hsm_AesCmacInit(LblAsync, NULL_PTR,
          Cry_GddAutHsmCmacAesGenDataType, Cry_GddAutHsmCmacAesGenDataIDType,
          CSM_TRUE);
      }

      if (LddErr == HSM_NO_ERROR)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmCmacAesGenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmCmacAesGenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmCmacAesGenerateTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_AutHsmCmacAesGenerateUpdate                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the HSM      **
**                        CMAC AES                                            **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmCmacAesGenerateMainFunction() can process **
**                        the input data                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, dataPtr, dataLength                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
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
**                        Cry_GddAutHsmCmacAesGenerateTb                      **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacGenerateServiceHasCallback, Hsm_AesCmacUpdate**
*******************************************************************************/
Std_ReturnType Cry_AutHsmCmacAesGenerateUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutHsmCmacAesGenerateTb.ucJobState)
  {
    /* Set the job state to JOB_UPDATE */
    Cry_GddAutHsmCmacAesGenerateTb.ucJobState = JOB_UPDATE;

    LblAsync = Csm_MacGenerateServiceHasCallback();

    if (LblAsync == CSM_FALSE)
    {
      LddErr = Hsm_AesCmacUpdate(LblAsync, NULL_PTR, dataPtr, dataLength,
        CSM_TRUE);

      if (LddErr == HSM_NO_ERROR)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmCmacAesGenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmCmacAesGenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmCmacAesGenerateTb.pDataPtr = dataPtr;
      Cry_GddAutHsmCmacAesGenerateTb.ulDataLength = dataLength;
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
** Function Name        : Cry_AutHsmCmacAesGenerateFinish                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the HSM     **
**                        CMAC AES computation and store the result into      **
**                        the memory location given                           **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmCmacAesGenerateMainFunction() can finish  **
**                        the computation and store the result in the memory  **
**                        location given                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, TruncationIsAllowed                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        CSM_E_SMALL_BUFFER: provided buffer is too small to **
**                                            store the result                **
**                                                                            **
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddAutHsmCmacAesGenerateTb                      **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacGenerateServiceHasCallback,                  **
**                        Hsm_AesCmacFinish                                   **
*******************************************************************************/
Std_ReturnType Cry_AutHsmCmacAesGenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutHsmCmacAesGenerateTb.ucJobState)
  {
    /* Set the job state to JOB_FINISH */
    Cry_GddAutHsmCmacAesGenerateTb.ucJobState = JOB_FINISH;

    LblAsync = Csm_MacGenerateServiceHasCallback();

    if (LblAsync == CSM_FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if ((*resultLengthPtr < HSM_AES_BLOCK_BYTE_SIZE)
        && (TruncationIsAllowed != CSM_TRUE))
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        LddErr = Hsm_AesCmacFinish(LblAsync, NULL_PTR,
          resultPtr, *resultLengthPtr, NULL_PTR, CSM_TRUE);

        if (LddErr != HSM_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      /* reset the state back to NO_JOB */
      Cry_GddAutHsmCmacAesGenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddAutHsmCmacAesGenerateTb.pResultPtr = resultPtr;
      Cry_GddAutHsmCmacAesGenerateTb.pResultLengthPtr = resultLengthPtr;
      Cry_GddAutHsmCmacAesGenerateTb.blTruncationIsAllowed = TruncationIsAllowed;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmCmacAesGenerateCallback                   **
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
**                        Cry_GddAutHsmCmacAesGenerateTb                      **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacGenerateCallbackNotification,                **
**                        Csm_MacGenerateServiceFinishNotification            **
*******************************************************************************/
static void Cry_AutHsmCmacAesGenerateCallback(Hsm_ErrType ddRet)
{
  Std_ReturnType LddReturnValue;

  if (ddRet == HSM_BUSY)
  {
    LddReturnValue = CSM_E_BUSY;

    Csm_MacGenerateCallbackNotification(LddReturnValue);
  }
  else
  {
    LddReturnValue = E_OK;

    switch (Cry_GddAutHsmCmacAesGenerateTb.ucJobState)
    {
    case JOB_START:
    case JOB_UPDATE:
      if (ddRet == HSM_NO_ERROR)
      {
        Cry_GddAutHsmCmacAesGenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* task failure move job state to NO_JOB */
        Cry_GddAutHsmCmacAesGenerateTb.ucJobState = NO_JOB;
      }
      Csm_MacGenerateCallbackNotification(LddReturnValue);
      break;

    case JOB_FINISH:
      if (ddRet != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
      Cry_GddAutHsmCmacAesGenerateTb.ucJobState = NO_JOB;
      Csm_MacGenerateCallbackNotification(LddReturnValue);
      break;

    default:
      Csm_MacGenerateServiceFinishNotification();
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : Cry_AutHsmCmacAesGenerateMainFunction               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_MacGenerateCallbackNotification() with the      **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_AutHsmCmacAesGenerateStart() or                 **
**                        Cry_AutHsmCmacAesGenerateUpdate(). For              **
**                        Cry_AutHsmCmacAesGenerateFinish invocation of       **
**                        Csm_MacGenerateCallbackNotification()               **
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
**                        Cry_GddAutHsmCmacAesGenerateTb                      **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hsm_AesCmacInit                                     **
**                        Hsm_AesCmacUpdate                                   **
**                        Hsm_AesCmacFinish                                   **
**                        Csm_MacGenerateCallbackNotification                 **
**                        Csm_MacGenerateServiceFinishNotification            **
*******************************************************************************/
void Cry_AutHsmCmacAesGenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  Hsm_CallbackPtr LpCallback;

  LddReturnValue = E_OK;

  LpCallback = &Cry_AutHsmCmacAesGenerateCallback;

  switch (Cry_GddAutHsmCmacAesGenerateTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddAutHsmCmacAesGenerateTb.pKeyPtr->length == CSM_ONE)
    {
      Cry_GddAutHsmCmacAesGenDataType = HSM_DATA_AES_KEY;
      Cry_GddAutHsmCmacAesGenDataIDType
        = (Hsm_DataIDType)(Cry_GddAutHsmCmacAesGenerateTb.pKeyPtr->data[0]);
      LddErr = HSM_NO_ERROR;
    }
    else if (Cry_GddAutHsmCmacAesGenerateTb.pKeyPtr->length == HSM_AES_KEY_BYTE_SIZE)
    {
      Cry_GddAutHsmCmacAesGenDataType = HSM_DATA_AES_RAM_KEY;
      Cry_GddAutHsmCmacAesGenDataIDType = CSM_SIX;

      LddErr = Hsm_LoadRamKey(HSM_DATA_AES_RAM_KEY, CSM_SIX,
        Cry_GddAutHsmCmacAesGenerateTb.pKeyPtr->length,
        (const uint8*)(Cry_GddAutHsmCmacAesGenerateTb.pKeyPtr->data));
    }
    else
    {
      LddErr = HSM_KEY_INVALID_ERROR;
    }

    if (LddErr == HSM_NO_ERROR)
    {
      LddErr = Hsm_AesCmacInit(CSM_TRUE, LpCallback,
        Cry_GddAutHsmCmacAesGenDataType, Cry_GddAutHsmCmacAesGenDataIDType,
        CSM_TRUE);
    }

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmCmacAesGenerateTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_MacGenerateCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_UPDATE:
    LddErr = Hsm_AesCmacUpdate(CSM_TRUE, LpCallback,
      Cry_GddAutHsmCmacAesGenerateTb.pDataPtr,
      Cry_GddAutHsmCmacAesGenerateTb.ulDataLength, CSM_TRUE);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmCmacAesGenerateTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_MacGenerateCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_FINISH:
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if ((*(Cry_GddAutHsmCmacAesGenerateTb.pResultLengthPtr) < HSM_AES_BLOCK_BYTE_SIZE)
      && (Cry_GddAutHsmCmacAesGenerateTb.blTruncationIsAllowed != CSM_TRUE))
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      LddErr = Hsm_AesCmacFinish(CSM_TRUE, LpCallback,
        Cry_GddAutHsmCmacAesGenerateTb.pResultPtr,
        *(Cry_GddAutHsmCmacAesGenerateTb.pResultLengthPtr), NULL_PTR, CSM_TRUE);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue != E_OK)
    {
      /* reset the state back to NO_JOB */
      Cry_GddAutHsmCmacAesGenerateTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_MacGenerateCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_MacGenerateServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_MAC_AUTHSMCMACAESGENERATE == STD_ON) */
#endif /* (CSM_MAC_GENERATE_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
