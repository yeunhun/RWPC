/*******************************************************************************
**                                                                            **
**  (C) 2016~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_EscHmacSha256Generate.c                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Escrypt HMAC SHA256 Generate Interface  **
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
** 1.2.2     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.2.1     21-Sep-2017   Sinil        Redmine #10040                        **
** 1.2.0     27-Feb-2017   Sinil        Redmine #7650, #7672                  **
** 1.1.0     11-Jan-2017   Sinil        Redmine #7198, #7323                  **
** 1.0.1     28-Sep-2016   Sinil        #6128                                 **
** 1.0.0     27-Sep-2016   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:D4.5 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for Escrypt HMAC SHA256 Generate */
#include "Cry_EscHmacSha256Generate.h"
/* Mac Interface */
#if (CSM_MAC_GENERATE_STATUS == STD_ON)
#if (CSM_MAC_ESCHMACSHA256GENERATE == STD_ON)
#include "Csm_Cbk.h"
#include "hmac_sha_2.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry EscHmacSha256Generate Transfer buffer*/
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
} Cry_EscHmacSha256GenerateTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Escrypt HMAC SHA256 primitive library context */
static EscHmacSha256_ContextT Cry_GddEscHmacSha256GenerateContext;

/* Global variable for Escrypt HMAC SHA256 transfer buffer structure */
static Cry_EscHmacSha256GenerateTransferBuffer Cry_GddEscHmacSha256GenerateTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_EscHmacSha256GenerateInit                         **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the Escrypt HMAC SHA256      **
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
** Remarks            : Global Variable(s):  Cry_GddEscHmacSha256GenerateTb   **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_EscHmacSha256GenerateInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddEscHmacSha256GenerateTb.ucJobState = NO_JOB;
  Cry_GddEscHmacSha256GenerateTb.pKeyPtr = NULL_PTR;
  Cry_GddEscHmacSha256GenerateTb.pDataPtr = NULL_PTR;
  Cry_GddEscHmacSha256GenerateTb.ulDataLength = CSM_ZERO;
  Cry_GddEscHmacSha256GenerateTb.pResultPtr = NULL_PTR;
  Cry_GddEscHmacSha256GenerateTb.pResultLengthPtr = NULL_PTR;
  Cry_GddEscHmacSha256GenerateTb.blTruncationIsAllowed = CSM_FALSE;

  (void)memset((void*)&Cry_GddEscHmacSha256GenerateContext, 0x00,
    sizeof(EscHmacSha256_ContextT));
}

/*******************************************************************************
** Function Name        : Cry_EscHmacSha256GenerateStart                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Escrypt HMAC SHA256, so that it is   **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_EscHmacSha256GenerateMainFunction() can         **
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
**                        Cry_GddEscHmacSha256GenerateTb                      **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscHmacSha256_Init                                  **
*******************************************************************************/
Std_ReturnType Cry_EscHmacSha256GenerateStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddEscHmacSha256GenerateTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_EscHmacSha256GenerateInit();

    Cry_GddEscHmacSha256GenerateTb.ucJobState = JOB_START;

    if (Csm_MacGenerateServiceHasCallback() == FALSE)
    {
      /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      LblReturnValue = EscHmacSha256_Init(&Cry_GddEscHmacSha256GenerateContext,
        (const uint8*)((const void*)(keyPtr->data)), keyPtr->length);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscHmacSha256GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscHmacSha256GenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscHmacSha256GenerateTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_EscHmacSha256GenerateUpdate                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Escrypt  **
**                        HMAC SHA256                                         **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscHmacSha256GenerateMainFunction() can process **
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
**                        Cry_GddEscHmacSha256GenerateTb                      **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscHmacSha256_Update                                **
*******************************************************************************/
Std_ReturnType Cry_EscHmacSha256GenerateUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddEscHmacSha256GenerateTb.ucJobState)
  {
    Cry_GddEscHmacSha256GenerateTb.ucJobState = JOB_UPDATE;

    if (Csm_MacGenerateServiceHasCallback() == FALSE)
    {
      LblReturnValue = EscHmacSha256_Update(&Cry_GddEscHmacSha256GenerateContext,
        dataPtr, dataLength);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscHmacSha256GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscHmacSha256GenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscHmacSha256GenerateTb.pDataPtr = dataPtr;
      Cry_GddEscHmacSha256GenerateTb.ulDataLength = dataLength;
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
** Function Name        : Cry_EscHmacSha256GenerateFinish                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Escrypt **
**                        HMAC SHA256 computation and store the result into   **
**                        the memory location given                           **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscHmacSha256GenerateMainFunction() can finish  **
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
**                        Cry_GddEscHmacSha256GenerateTb                      **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscHmacSha256_Finish                                **
*******************************************************************************/
Std_ReturnType Cry_EscHmacSha256GenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LaaSha256Digest[EscSha256_DIGEST_LEN];
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddEscHmacSha256GenerateTb.ucJobState)
  {
    Cry_GddEscHmacSha256GenerateTb.ucJobState = JOB_FINISH;

    if (Csm_MacGenerateServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if ((*resultLengthPtr < EscSha256_DIGEST_LEN)
        && (TruncationIsAllowed != CSM_TRUE))
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        (void)memset((void*)&LaaSha256Digest, 0x00, sizeof(LaaSha256Digest));

        LblReturnValue = EscHmacSha256_Finish(&Cry_GddEscHmacSha256GenerateContext,
          LaaSha256Digest);

        if (LblReturnValue != CSM_TRUE)
        {
          *resultLengthPtr = (*resultLengthPtr < EscSha256_DIGEST_LEN)
            ? (*resultLengthPtr) : EscSha256_DIGEST_LEN;

          for (LulIndex = CSM_ZERO; LulIndex < *resultLengthPtr; LulIndex++)
          {
            /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
            resultPtr[LulIndex] = LaaSha256Digest[LulIndex];
          }
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddEscHmacSha256GenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddEscHmacSha256GenerateTb.pResultPtr = resultPtr;
      Cry_GddEscHmacSha256GenerateTb.pResultLengthPtr = resultLengthPtr;
      Cry_GddEscHmacSha256GenerateTb.blTruncationIsAllowed = TruncationIsAllowed;
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
** Function Name        : Cry_EscHmacSha256GenerateMainFunction               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_MacGenerateCallbackNotification() with the      **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_EscHmacSha256GenerateStart() or                 **
**                        Cry_EscHmacSha256GenerateUpdate(). For              **
**                        Cry_EscHmacSha256GenerateFinish invocation of       **
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
**                        Cry_GddEscHmacSha256GenerateTb                      **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscHmacSha256_Init                                  **
**                        EscHmacSha256_Update                                **
**                        EscHmacSha256_Finish                                **
**                        Csm_MacGenerateCallbackNotification                 **
**                        Csm_MacGenerateServiceFinishNotification            **
*******************************************************************************/
void Cry_EscHmacSha256GenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LaaSha256Digest[EscSha256_DIGEST_LEN];
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddEscHmacSha256GenerateTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +3 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    LblReturnValue = EscHmacSha256_Init(&Cry_GddEscHmacSha256GenerateContext,
      (const uint8*)((const void*)(Cry_GddEscHmacSha256GenerateTb.pKeyPtr->data)),
      Cry_GddEscHmacSha256GenerateTb.pKeyPtr->length);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscHmacSha256GenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscHmacSha256GenerateTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LblReturnValue = EscHmacSha256_Update(&Cry_GddEscHmacSha256GenerateContext,
      Cry_GddEscHmacSha256GenerateTb.pDataPtr,
      Cry_GddEscHmacSha256GenerateTb.ulDataLength);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscHmacSha256GenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscHmacSha256GenerateTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if ((*(Cry_GddEscHmacSha256GenerateTb.pResultLengthPtr) < EscSha256_DIGEST_LEN)
      && (Cry_GddEscHmacSha256GenerateTb.blTruncationIsAllowed != CSM_TRUE))
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      (void)memset((void*)&LaaSha256Digest, 0x00, sizeof(LaaSha256Digest));

      LblReturnValue = EscHmacSha256_Finish(&Cry_GddEscHmacSha256GenerateContext,
        LaaSha256Digest);

      if (LblReturnValue != CSM_TRUE)
      {
        *(Cry_GddEscHmacSha256GenerateTb.pResultLengthPtr) =
          (*(Cry_GddEscHmacSha256GenerateTb.pResultLengthPtr) < EscSha256_DIGEST_LEN)
          ? (*(Cry_GddEscHmacSha256GenerateTb.pResultLengthPtr))
          : EscSha256_DIGEST_LEN;

        for (LulIndex = CSM_ZERO;
          LulIndex < *(Cry_GddEscHmacSha256GenerateTb.pResultLengthPtr); LulIndex++)
        {
          /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          Cry_GddEscHmacSha256GenerateTb.pResultPtr[LulIndex]
            = LaaSha256Digest[LulIndex];
        }
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddEscHmacSha256GenerateTb.ucJobState = NO_JOB;

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

#endif /* (CSM_MAC_ESCHMACSHA256GENERATE == STD_ON) */
#endif /* (CSM_MAC_GENERATE_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:D4.5 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
