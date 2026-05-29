/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutIcusCmacAesVerify.c                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY ICUS CMAC AES Verify Interface          **
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
/* Header File for ICUS CMAC AES Verify */
#include "Cry_AutIcusCmacAesVerify.h"
/* Mac Interface */
#if (CSM_MAC_VERIFY_STATUS == STD_ON)
#if (CSM_MAC_AUTICUSCMACAESVERIFY == STD_ON)
#include "Csm_Cbk.h"
#include "Icus_Driver.h"
#include "Icus_IntDriver.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry AutIcusCmacAesVerify Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_SymKeyType* pKeyPtr;
  const uint8* pDataPtr;
  uint32 ulDataLength;
  const uint8* pMacPtr;
  uint32 ulMacLength;
  Csm_VerifyResultType* pResultPtr;
} Cry_AutIcusCmacAesVerifyTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

boolean Cry_GblAutIcusCmacAesVerInternalStarted;

#define CSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Icus_KeyIDType Cry_GddAutIcusCmacAesVerKeyId;

/* Global variable for ICUS CMAC AES transfer buffer structure */
static Cry_AutIcusCmacAesVerifyTransferBuffer Cry_GddAutIcusCmacAesVerifyTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutIcusCmacAesVerifyInit                          **
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
** Remarks            : Global Variable(s):  Cry_GddAutIcusCmacAesVerifyTb    **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutIcusCmacAesVerifyInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutIcusCmacAesVerifyTb.ucJobState = NO_JOB;
  Cry_GddAutIcusCmacAesVerifyTb.pKeyPtr = NULL_PTR;
  Cry_GddAutIcusCmacAesVerifyTb.pDataPtr = NULL_PTR;
  Cry_GddAutIcusCmacAesVerifyTb.ulDataLength = CSM_ZERO;
  Cry_GddAutIcusCmacAesVerifyTb.pMacPtr = NULL_PTR;
  Cry_GddAutIcusCmacAesVerifyTb.ulMacLength = CSM_ZERO;
  Cry_GddAutIcusCmacAesVerifyTb.pResultPtr = NULL_PTR;
  Cry_GblAutIcusCmacAesVerInternalStarted = CSM_FALSE;
  Cry_GddAutIcusCmacAesVerKeyId = INVALID_KEY;
}

/*******************************************************************************
** Function Name        : Cry_AutIcusCmacAesVerifyStart                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of ICUS CMAC AES, so that if is         **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutIcusCmacAesVerifyMainFunction() can process  **
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
**                        Cry_GddAutIcusCmacAesVerifyTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutIcusCmacAesVerifyInit,                       **
**                        Csm_MacVerifyServiceHasCallback,                    **
**                        Icus_LoadPlainKey                                   **
*******************************************************************************/
Std_ReturnType Cry_AutIcusCmacAesVerifyStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  Icus_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutIcusCmacAesVerifyTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutIcusCmacAesVerifyInit();

    Cry_GddAutIcusCmacAesVerifyTb.ucJobState = JOB_START;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
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
          /* polyspace +2 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
          Cry_GddAutIcusCmacAesVerKeyId = (Icus_KeyIDType)(keyPtr->data[0]);
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }
      else if (keyPtr->length == ICUS_BLOCK_BYTE_LENGTH)
      {
        /* Raw Key */
        Cry_GddAutIcusCmacAesVerKeyId = RAM_KEY;
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
        Cry_GddAutIcusCmacAesVerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutIcusCmacAesVerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutIcusCmacAesVerifyTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_AutIcusCmacAesVerifyUpdate                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the ICUS     **
**                        CMAC AES                                            **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutIcusCmacAesVerifyMainFunction() can process  **
**                        the input                                           **
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
**                        Cry_GddAutIcusCmacAesVerifyTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacVerifyServiceHasCallback, Icus_VerifyMac     **
*******************************************************************************/
Std_ReturnType Cry_AutIcusCmacAesVerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  Icus_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutIcusCmacAesVerifyTb.ucJobState)
  {
    /* Set the job state to JOB_UPDATE */
    Cry_GddAutIcusCmacAesVerifyTb.ucJobState = JOB_UPDATE;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      if (Cry_GblAutIcusCmacAesVerInternalStarted == CSM_FALSE)
      {
        LddErr = Icus_VerifyMacStart(Cry_GddAutIcusCmacAesVerKeyId,
          dataLength * CSM_EIGHT);

        if (LddErr == ERC_NO_ERROR)
        {
          Cry_GblAutIcusCmacAesVerInternalStarted = CSM_TRUE;

          LddErr = Icus_VerifyMacUpdate(dataPtr, dataLength * CSM_EIGHT);
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
        Cry_GddAutIcusCmacAesVerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutIcusCmacAesVerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutIcusCmacAesVerifyTb.pDataPtr = dataPtr;
      Cry_GddAutIcusCmacAesVerifyTb.ulDataLength = dataLength;
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
** Function Name        : Cry_AutIcusCmacAesVerifyFinish                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the ICUS    **
**                        CMAC AES computation and store the result into      **
**                        the memory location given                           **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutIcusCmacAesVerifyMainFunction() can finish   **
**                        the computation and store the result in the memory  **
**                        location given                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, MacPtr, MacLength                            **
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
**                        Cry_GddAutIcusCmacAesVerifyTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacVerifyServiceHasCallback,                    **
**                        Icus_VerifyMacFinish                                **
*******************************************************************************/
Std_ReturnType Cry_AutIcusCmacAesVerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* MacPtr, uint32 MacLength, Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;
  Icus_ErrType LddErr;
  boolean LblResult;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutIcusCmacAesVerifyTb.ucJobState)
  {
    Cry_GddAutIcusCmacAesVerifyTb.ucJobState = JOB_FINISH;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      if (Cry_GblAutIcusCmacAesVerInternalStarted == CSM_FALSE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LblResult = CSM_FALSE;
        LddErr = Icus_VerifyMacFinish(MacLength, MacPtr, &LblResult);

        if (LddErr == ERC_NO_ERROR)
        {
          if (LblResult == CSM_TRUE)
          {
            /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
            *resultPtr = CSM_E_VER_OK;
          }
          else
          {
            /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
            *resultPtr = CSM_E_VER_NOT_OK;
          }
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      Cry_GblAutIcusCmacAesVerInternalStarted = CSM_FALSE;

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutIcusCmacAesVerifyTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddAutIcusCmacAesVerifyTb.pMacPtr = MacPtr;
      Cry_GddAutIcusCmacAesVerifyTb.ulMacLength = MacLength;
      Cry_GddAutIcusCmacAesVerifyTb.pResultPtr = resultPtr;
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
** Function Name        : Cry_AutIcusCmacAesVerifyMainFunction                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_MacVerifyCallbackNotification() with the        **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_AutIcusCmacAesVerifyStart() or                  **
**                        Cry_AutIcusCmacAesVerifyUpdate(). For               **
**                        Cry_AutIcusCmacAesVerifyFinish invocation of        **
**                        Csm_MacVerifyCallbackNotification()                 **
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
**                        Cry_GddAutIcusCmacAesVerifyTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Icus_LoadPlainKey, Icus_VerifyMac,                  **
**                        Icus_VerifyMacFinish,                               **
**                        Csm_MacVerifyCallbackNotification,                  **
**                        Csm_MacVerifyServiceFinishNotification              **
*******************************************************************************/
void Cry_AutIcusCmacAesVerifyMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Icus_ErrType LddErr;
  boolean LblResult;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* State machine of ICUS CMAC AES job processing */
  switch (Cry_GddAutIcusCmacAesVerifyTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (Cry_GddAutIcusCmacAesVerifyTb.pKeyPtr->length == CSM_ONE)
    {
      /* Pre-Shared Key */
      if ((((Cry_GddAutIcusCmacAesVerifyTb.pKeyPtr->data[0]) >= (uint8)KEY_1)
        && ((Cry_GddAutIcusCmacAesVerifyTb.pKeyPtr->data[0]) <= (uint8)KEY_10))
        || (((Cry_GddAutIcusCmacAesVerifyTb.pKeyPtr->data[0]) >= (uint8)KEY_11)
        && ((Cry_GddAutIcusCmacAesVerifyTb.pKeyPtr->data[0]) <= (uint8)KEY_20)))
      {
        /* polyspace +2 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
        Cry_GddAutIcusCmacAesVerKeyId
          = (Icus_KeyIDType)(Cry_GddAutIcusCmacAesVerifyTb.pKeyPtr->data[0]);
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }
    else if (Cry_GddAutIcusCmacAesVerifyTb.pKeyPtr->length == ICUS_BLOCK_BYTE_LENGTH)
    {
      /* Raw Key */
      Cry_GddAutIcusCmacAesVerKeyId = RAM_KEY;
      LddErr = Icus_LoadPlainKey(
        (const uint8*)((const void*)(Cry_GddAutIcusCmacAesVerifyTb.pKeyPtr->data)));

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
      Cry_GddAutIcusCmacAesVerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutIcusCmacAesVerifyTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    if (Cry_GblAutIcusCmacAesVerInternalStarted == CSM_FALSE)
    {
      LddErr = Icus_VerifyMacStart(Cry_GddAutIcusCmacAesVerKeyId,
        Cry_GddAutIcusCmacAesVerifyTb.ulDataLength * CSM_EIGHT);

      if (LddErr == ERC_NO_ERROR)
      {
        Cry_GblAutIcusCmacAesVerInternalStarted = CSM_TRUE;

        LddErr = Icus_VerifyMacUpdate(Cry_GddAutIcusCmacAesVerifyTb.pDataPtr,
          Cry_GddAutIcusCmacAesVerifyTb.ulDataLength * CSM_EIGHT);
      }
    }
    else
    {
      LddErr = Icus_GenerateMacUpdate(Cry_GddAutIcusCmacAesVerifyTb.pDataPtr,
        Cry_GddAutIcusCmacAesVerifyTb.ulDataLength * CSM_EIGHT);
    }

    if (LddErr != ERC_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutIcusCmacAesVerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutIcusCmacAesVerifyTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    if (Cry_GblAutIcusCmacAesVerInternalStarted == CSM_FALSE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LblResult = CSM_FALSE;
      LddErr = Icus_VerifyMacFinish(Cry_GddAutIcusCmacAesVerifyTb.ulMacLength,
        Cry_GddAutIcusCmacAesVerifyTb.pMacPtr, &LblResult);

      if (LddErr == ERC_NO_ERROR)
      {
        if (LblResult == CSM_TRUE)
        {
          /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          *(Cry_GddAutIcusCmacAesVerifyTb.pResultPtr) = CSM_E_VER_OK;
        }
        else
        {
          /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          *(Cry_GddAutIcusCmacAesVerifyTb.pResultPtr) = CSM_E_VER_NOT_OK;
        }
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    Cry_GblAutIcusCmacAesVerInternalStarted = CSM_FALSE;

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddAutIcusCmacAesVerifyTb.ucJobState = NO_JOB;

    /* Notify respective Service about the completion of the task */
    Csm_MacVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_MacVerifyServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_MAC_AUTICUSCMACAESVERIFY == STD_ON) */
#endif /* (CSM_MAC_VERIFY_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
