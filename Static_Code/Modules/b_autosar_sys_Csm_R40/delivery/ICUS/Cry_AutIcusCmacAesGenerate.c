/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutIcusCmacAesGenerate.c                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY ICUS CMAC AES Generate Interface        **
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
/* Header File for ICUS CMAC AES Generate */
#include "Cry_AutIcusCmacAesGenerate.h"
/* Mac Interface */
#if (CSM_MAC_GENERATE_STATUS == STD_ON)
#if (CSM_MAC_AUTICUSCMACAESGENERATE == STD_ON)
#include "Csm_Cbk.h"
#include "Icus_Driver.h"
#include "Icus_IntDriver.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry AutIcusCmacAesGenerate Transfer buffer*/
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
} Cry_AutIcusCmacAesGenerateTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

boolean Cry_GblAutIcusCmacAesGenInternalStarted;

#define CSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Icus_KeyIDType Cry_GddAutIcusCmacAesGenKeyId;

/* Global variable for ICUS CMAC AES transfer buffer structure */
static Cry_AutIcusCmacAesGenerateTransferBuffer Cry_GddAutIcusCmacAesGenerateTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutIcusCmacAesGenerateInit                        **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the ICUS CMAC AES            **
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
** Remarks            : Global Variable(s):  Cry_GddAutIcusCmacAesGenerateTb  **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutIcusCmacAesGenerateInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutIcusCmacAesGenerateTb.ucJobState = NO_JOB;
  Cry_GddAutIcusCmacAesGenerateTb.pKeyPtr = NULL_PTR;
  Cry_GddAutIcusCmacAesGenerateTb.pDataPtr = NULL_PTR;
  Cry_GddAutIcusCmacAesGenerateTb.ulDataLength = CSM_ZERO;
  Cry_GddAutIcusCmacAesGenerateTb.pResultPtr = NULL_PTR;
  Cry_GddAutIcusCmacAesGenerateTb.pResultLengthPtr = NULL_PTR;
  Cry_GddAutIcusCmacAesGenerateTb.blTruncationIsAllowed = CSM_FALSE;

  Cry_GblAutIcusCmacAesGenInternalStarted = CSM_FALSE;
  Cry_GddAutIcusCmacAesGenKeyId = INVALID_KEY;
}

/*******************************************************************************
** Function Name        : Cry_AutIcusCmacAesGenerateStart                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of ICUS CMAC AES, so that it is         **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutIcusCmacAesGenerateMainFunction() can        **
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
**                        Cry_GddAutIcusCmacAesGenerateTb                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutIcusCmacAesGenerateInit,                     **
**                        Csm_MacGenerateServiceHasCallback,                  **
**                        Icus_LoadPlainKey                                   **
*******************************************************************************/
Std_ReturnType Cry_AutIcusCmacAesGenerateStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  Icus_ErrType LddErr;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddAutIcusCmacAesGenerateTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutIcusCmacAesGenerateInit();

    /* Set the job state to JOB_START */
    Cry_GddAutIcusCmacAesGenerateTb.ucJobState = JOB_START;

    if (Csm_MacGenerateServiceHasCallback() == FALSE)
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
          /* polyspace +1 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
          Cry_GddAutIcusCmacAesGenKeyId = (Icus_KeyIDType)(keyPtr->data[0]);
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }
      else if (keyPtr->length == ICUS_BLOCK_BYTE_LENGTH)
      {
        /* Raw Key */
        Cry_GddAutIcusCmacAesGenKeyId = RAM_KEY;
        LddErr = Icus_LoadPlainKey((const uint8*)((const void*)(keyPtr->data)));
        if (LddErr != ERC_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutIcusCmacAesGenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutIcusCmacAesGenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutIcusCmacAesGenerateTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_AutIcusCmacAesGenerateUpdate                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the ICUS     **
**                        CMAC AES                                            **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutIcusCmacAesGenerateMainFunction() can process**
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
**                        Cry_GddAutIcusCmacAesGenerateTb                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacGenerateServiceHasCallback, Icus_GenerateMac **
*******************************************************************************/
Std_ReturnType Cry_AutIcusCmacAesGenerateUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  Icus_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutIcusCmacAesGenerateTb.ucJobState)
  {
    Cry_GddAutIcusCmacAesGenerateTb.ucJobState = JOB_UPDATE;

    if (Csm_MacGenerateServiceHasCallback() == FALSE)
    {
      if (Cry_GblAutIcusCmacAesGenInternalStarted == CSM_FALSE)
      {
        LddErr = Icus_GenerateMacStart(Cry_GddAutIcusCmacAesGenKeyId,
          dataLength * CSM_EIGHT);

        if (LddErr == ERC_NO_ERROR)
        {
          Cry_GblAutIcusCmacAesGenInternalStarted = CSM_TRUE;

          LddErr = Icus_GenerateMacUpdate(dataPtr, dataLength * CSM_EIGHT);
        }
      }
      else
      {
        LddErr = Icus_GenerateMacUpdate(dataPtr, dataLength * CSM_EIGHT);
      }

      if (LddErr != ERC_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutIcusCmacAesGenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutIcusCmacAesGenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutIcusCmacAesGenerateTb.pDataPtr = dataPtr;
      Cry_GddAutIcusCmacAesGenerateTb.ulDataLength = dataLength;
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
** Function Name        : Cry_AutIcusCmacAesGenerateFinish                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the ICUS    **
**                        CMAC AES computation and store the result into      **
**                        the memory location given                           **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutIcusCmacAesGenerateMainFunction() can finish **
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
**                        Cry_GddAutIcusCmacAesGenerateTb                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacGenerateServiceHasCallback,                  **
**                        Icus_GenerateMacFinish                              **
*******************************************************************************/
Std_ReturnType Cry_AutIcusCmacAesGenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed)
{
  Std_ReturnType LddReturnValue;
  Icus_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutIcusCmacAesGenerateTb.ucJobState)
  {
    Cry_GddAutIcusCmacAesGenerateTb.ucJobState = JOB_FINISH;

    if (Csm_MacGenerateServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if ((*resultLengthPtr < ICUS_BLOCK_BYTE_LENGTH)
        && (TruncationIsAllowed != CSM_TRUE))
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (Cry_GblAutIcusCmacAesGenInternalStarted == CSM_FALSE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LddErr = Icus_GenerateMacFinish(resultPtr, *resultLengthPtr);

        if (LddErr != ERC_NO_ERROR)
        {
          *resultLengthPtr = CSM_ZERO;

          LddReturnValue = E_NOT_OK;
        }
      }

      Cry_GblAutIcusCmacAesGenInternalStarted = CSM_FALSE;

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutIcusCmacAesGenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddAutIcusCmacAesGenerateTb.pResultPtr = resultPtr;
      Cry_GddAutIcusCmacAesGenerateTb.pResultLengthPtr = resultLengthPtr;
      Cry_GddAutIcusCmacAesGenerateTb.blTruncationIsAllowed = TruncationIsAllowed;
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
** Function Name        : Cry_AutIcusCmacAesGenerateMainFunction              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_MacGenerateCallbackNotification() with the      **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_AutIcusCmacAesGenerateStart() or                **
**                        Cry_AutIcusCmacAesGenerateUpdate(). For             **
**                        Cry_AutIcusCmacAesGenerateFinish invocation of      **
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
**                        Cry_GddAutIcusCmacAesGenerateTb                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Icus_LoadPlainKey, Icus_GenerateMac,                **
**                        Icus_GenerateMacFinish,                             **
**                        Csm_MacGenerateCallbackNotification,                **
**                        Csm_MacGenerateServiceFinishNotification            **
*******************************************************************************/
void Cry_AutIcusCmacAesGenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Icus_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* State machine of ICUS CMAC AES job processing */
  switch (Cry_GddAutIcusCmacAesGenerateTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (Cry_GddAutIcusCmacAesGenerateTb.pKeyPtr->length == CSM_ONE)
    {
      /* Pre-Shared Key */
      if ((((Cry_GddAutIcusCmacAesGenerateTb.pKeyPtr->data[0]) >= (uint8)KEY_1)
        && ((Cry_GddAutIcusCmacAesGenerateTb.pKeyPtr->data[0]) <= (uint8)KEY_10))
        || (((Cry_GddAutIcusCmacAesGenerateTb.pKeyPtr->data[0]) >= (uint8)KEY_11)
          && ((Cry_GddAutIcusCmacAesGenerateTb.pKeyPtr->data[0]) <= (uint8)KEY_20)))
      {
        /* polyspace +2 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
        Cry_GddAutIcusCmacAesGenKeyId
          = (Icus_KeyIDType)(Cry_GddAutIcusCmacAesGenerateTb.pKeyPtr->data[0]);
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }
    else if (Cry_GddAutIcusCmacAesGenerateTb.pKeyPtr->length == ICUS_BLOCK_BYTE_LENGTH)
    {
      /* Raw Key */
      Cry_GddAutIcusCmacAesGenKeyId = RAM_KEY;
      LddErr = Icus_LoadPlainKey(
        (const uint8*)((const void*)(Cry_GddAutIcusCmacAesGenerateTb.pKeyPtr->data)));

      if (LddErr != ERC_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutIcusCmacAesGenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutIcusCmacAesGenerateTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    if (Cry_GblAutIcusCmacAesGenInternalStarted == CSM_FALSE)
    {
      LddErr = Icus_GenerateMacStart(Cry_GddAutIcusCmacAesGenKeyId,
        Cry_GddAutIcusCmacAesGenerateTb.ulDataLength * CSM_EIGHT);

      if (LddErr == ERC_NO_ERROR)
      {
        Cry_GblAutIcusCmacAesGenInternalStarted = CSM_TRUE;

        LddErr = Icus_GenerateMacUpdate(Cry_GddAutIcusCmacAesGenerateTb.pDataPtr,
          Cry_GddAutIcusCmacAesGenerateTb.ulDataLength * CSM_EIGHT);
      }
    }
    else
    {
      LddErr = Icus_GenerateMacUpdate(Cry_GddAutIcusCmacAesGenerateTb.pDataPtr,
        Cry_GddAutIcusCmacAesGenerateTb.ulDataLength * CSM_EIGHT);
    }

    if (LddErr != ERC_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutIcusCmacAesGenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutIcusCmacAesGenerateTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if ((*(Cry_GddAutIcusCmacAesGenerateTb.pResultLengthPtr) < ICUS_BLOCK_BYTE_LENGTH)
      && (Cry_GddAutIcusCmacAesGenerateTb.blTruncationIsAllowed != CSM_TRUE))
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (Cry_GblAutIcusCmacAesGenInternalStarted == CSM_FALSE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LddErr = Icus_GenerateMacFinish(Cry_GddAutIcusCmacAesGenerateTb.pResultPtr,
        *(Cry_GddAutIcusCmacAesGenerateTb.pResultLengthPtr));

      if (LddErr != ERC_NO_ERROR)
      {
        *(Cry_GddAutIcusCmacAesGenerateTb.pResultLengthPtr) = CSM_ZERO;

        LddReturnValue = E_NOT_OK;
      }
    }

    Cry_GblAutIcusCmacAesGenInternalStarted = CSM_FALSE;

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddAutIcusCmacAesGenerateTb.ucJobState = NO_JOB;

    /* Notify respective Service about the completion of the task */
    Csm_MacGenerateCallbackNotification(LddReturnValue);
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

#endif /* (CSM_MAC_AUTICUSCMACAESGENERATE == STD_ON) */
#endif /* (CSM_MAC_GENERATE_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
