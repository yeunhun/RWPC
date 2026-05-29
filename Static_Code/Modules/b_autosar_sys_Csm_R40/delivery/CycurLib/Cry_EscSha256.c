/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_EscSha256.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Escrypt Sha256 Interface                **
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
** 1.0.1     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.0     18-Apr-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for Escrypt Sha256 */
#include "Cry_EscSha256.h"
/* Hash Interface */
#if (CSM_HASH_STATUS == STD_ON)
#if (CSM_HASH_ESCSHA256 == STD_ON)
#include "Csm_Cbk.h"
#include "sha_256.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry EscSha256 Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Stores raw data pointer used for Escrypt Sha256 Computation */
  const uint8* pDataPtr;
  /* Data length of the data used for Escrypt Sha256 Computation */
  uint32 ulDataLength;
  /* Stores result data pointer used for Escrypt Sha256 Computation */
  uint8* pResultPtr;
  /* Pointer of result data length */
  uint32* pResultLengthPtr;
} Cry_EscSha256TransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* SHA256 context structure */
static EscSha256_ContextT Cry_GddEscSha256Context;

/* Global pointer to variable for Escrypt Sha256 transfer buffer structure */
static Cry_EscSha256TransferBuffer Cry_GddEscSha256Tb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_EscSha256Init                                     **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the transfer buffer of the   **
**                      SHA256 module. All module Global variables will be    **
**                      initialized after successful completion of this API.  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
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
** Remarks            : Global Variable(s): Cry_GddEscSha256Tb                **
**                                                                            **
**                     Function(s) invoked: None                              **
**                                                                            **
*******************************************************************************/
void Cry_EscSha256Init(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddEscSha256Tb.ucJobState = NO_JOB;
  Cry_GddEscSha256Tb.pDataPtr = NULL_PTR;
  Cry_GddEscSha256Tb.ulDataLength = CSM_ZERO;
  Cry_GddEscSha256Tb.pResultPtr = NULL_PTR;
  Cry_GddEscSha256Tb.pResultLengthPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddEscSha256Context, 0x00, sizeof(EscSha256_ContextT));
}

/*******************************************************************************
** Function Name        : Cry_EscSha256Start                                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of SHA256, so that SHA256 is able to    **
**                        process the input data                              **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_EscSha256MainFunction() can process             **
**                        initialisation                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgPtr                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        CSM_E_BUSY: service state is already "active"       **
**                                                                            **
** Preconditions        : CSM should have been initialized                    **
**                                                                            **
** Remarks              : Global Variable(s): Cry_GddEscSha256Tb              **
**                        Function(s) invoked: Cry_EscSha256Init,             **
**                        EscSha256_Init                                      **
*******************************************************************************/
Std_ReturnType Cry_EscSha256Start(const void* cfgPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddEscSha256Tb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_EscSha256Init();

    Cry_GddEscSha256Tb.ucJobState = JOB_START;

    if (Csm_HashServiceHasCallback() == FALSE)
    {
      LblReturnValue = EscSha256_Init(&Cry_GddEscSha256Context);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscSha256Tb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscSha256Tb.ucJobState = NO_JOB;
      }
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
** Function Name        : Cry_EscSha256Update                                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the SHA256   **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscSha256MainFunction() can process the input   **
**                        data                                                **
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
**                        CSM_E_BUSY: service state is already "active"       **
**                                                                            **
** Preconditions        : Primitive should have been successfully initialized **
**                                                                            **
** Remarks              : Global Variable(s): Cry_GddEscSha256Tb              **
**                        Function(s) invoked : EscSha256_Update              **
*******************************************************************************/
Std_ReturnType Cry_EscSha256Update(Csm_ConfigIdType cfgId, const uint8* dataPtr,
  uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Setting the default return value */
  LddReturnValue = E_OK;

  /* Mark the unused parameter */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddEscSha256Tb.ucJobState)
  {
    Cry_GddEscSha256Tb.ucJobState = JOB_UPDATE;

    if (Csm_HashServiceHasCallback() == FALSE)
    {
      LblReturnValue = EscSha256_Update(&Cry_GddEscSha256Context,
        dataPtr, dataLength);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscSha256Tb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscSha256Tb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscSha256Tb.pDataPtr = dataPtr;
      Cry_GddEscSha256Tb.ulDataLength = dataLength;
    }
  }
  else
  {
    /* Job process is still not complete, return CSM_E_BUSY */
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_EscSha256Finish                                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the SHA256  **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscSha256MainFunction() can finish the          **
**                        computation and store the result in the memory      **
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
**                        CSM_E_BUSY: service state is already "active"       **
**                        CSM_E_SMALL_BUFFER: provided buffer is too small to **
**                                            store the result                **
**                                                                            **
** Preconditions        : Primitive should have been successfully initialized **
**                                                                            **
** Remarks              : Global Variable(s): Cry_GddEscSha256Tb              **
**                        Function(s) invoked : EscSha256_Finish              **
*******************************************************************************/
Std_ReturnType Cry_EscSha256Finish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  /* Buffer for storing the result locally */
  uint8 LaaSha256ResultBuffer[EscSha256_DIGEST_LEN];
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & module is ready to finish */
  if (JOB_DONE == Cry_GddEscSha256Tb.ucJobState)
  {
    /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if ((*resultLengthPtr < EscSha256_DIGEST_LEN)
      && (TruncationIsAllowed != CSM_TRUE))
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      /* Set the job state to JOB_FINISH */
      Cry_GddEscSha256Tb.ucJobState = JOB_FINISH;

      if (Csm_HashServiceHasCallback() == FALSE)
      {
        (void)memset((void*)&LaaSha256ResultBuffer, 0x00, sizeof(LaaSha256ResultBuffer));

        LblReturnValue = EscSha256_Finish(&Cry_GddEscSha256Context,
          LaaSha256ResultBuffer);

        if (LblReturnValue != CSM_TRUE)
        {
          /* Update the length of the result buffer */
          *resultLengthPtr = (*resultLengthPtr < EscSha256_DIGEST_LEN)
            ? *resultLengthPtr : EscSha256_DIGEST_LEN;

          /* Copy the result to the OUT buffer */
          for (LulIndex = CSM_ZERO; LulIndex < *resultLengthPtr; LulIndex++)
          {
            /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
            resultPtr[LulIndex] = LaaSha256ResultBuffer[LulIndex];
          }
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }

        /* Update job state to NO_JOB irrespective of the result */
        Cry_GddEscSha256Tb.ucJobState = NO_JOB;
      }
      else
      {
        Cry_GddEscSha256Tb.pResultPtr = resultPtr;
        Cry_GddEscSha256Tb.pResultLengthPtr = resultLengthPtr;
      }
    }
    else
    {
      Cry_GddEscSha256Tb.ucJobState = NO_JOB;
    }
  }
  else
  {
    /* Job process is still not complete, return CSM_E_BUSY */
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_EscSha256MainFunction                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_HashCallbackNotification() with the correct     **
**                        return valueonce the main function has completely   **
**                        processed the cryptographic                         **
**                        functions demanded by Cry_EscSha256Start() or       **
**                        Cry_EscSha256Update(). For Cry_EscSha256Finish      **
**                        invocation of Csm_HashCallbackNotification()        **
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
** Remarks              : Global Variable(s): Cry_GddEscSha256Tb              **
**                                                                            **
**                        Function(s) invoked: Csm_HashCallbackNotification   **
**                                          Csm_HashServiceFinishNotification **
**                                          EscSha256_Init, EscSha256_Update, **
**                                          EscSha256_Finish                  **
*******************************************************************************/
void Cry_EscSha256MainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Buffer for storing the result locally */
  uint8 LaaSha256ResultBuffer[EscSha256_DIGEST_LEN];
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddEscSha256Tb.ucJobState)
  {
  case JOB_START:
    LblReturnValue = EscSha256_Init(&Cry_GddEscSha256Context);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscSha256Tb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscSha256Tb.ucJobState = NO_JOB;
    }

    /* Callback notification will be invoking the application callback */
    Csm_HashCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LblReturnValue = EscSha256_Update(&Cry_GddEscSha256Context,
      Cry_GddEscSha256Tb.pDataPtr, Cry_GddEscSha256Tb.ulDataLength);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscSha256Tb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscSha256Tb.ucJobState = NO_JOB;
    }

    /* Callback notification will be invoking the application callback */
    Csm_HashCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    (void)memset((void*)&LaaSha256ResultBuffer, 0x00, sizeof(LaaSha256ResultBuffer));

    LblReturnValue = EscSha256_Finish(&Cry_GddEscSha256Context,
      LaaSha256ResultBuffer);

    if (LblReturnValue != CSM_TRUE)
    {
      /* Update the length of the result buffer */
      /* polyspace +2 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      *(Cry_GddEscSha256Tb.pResultLengthPtr)
        = (*(Cry_GddEscSha256Tb.pResultLengthPtr) < EscSha256_DIGEST_LEN)
        ? *(Cry_GddEscSha256Tb.pResultLengthPtr) : EscSha256_DIGEST_LEN;

      /* Copy the result to the OUT buffer */
      for (LulIndex = CSM_ZERO; LulIndex < *(Cry_GddEscSha256Tb.pResultLengthPtr);
        LulIndex++)
      {
        /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        Cry_GddEscSha256Tb.pResultPtr[LulIndex] = LaaSha256ResultBuffer[LulIndex];
      }
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddEscSha256Tb.ucJobState = NO_JOB;

    /* Service Finish notification will set the state to IDLE */
    Csm_HashServiceFinishNotification();

    /* Callback notification will be invoking the application callback */
    Csm_HashCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_HashServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_HASH_ESCSHA256 == STATUS_ON) */
#endif /* (CSM_HASH_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
