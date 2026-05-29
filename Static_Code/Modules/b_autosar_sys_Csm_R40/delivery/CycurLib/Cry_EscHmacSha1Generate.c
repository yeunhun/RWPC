/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_EscHmacSha1Generate.c                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Escrypt HMAC SHA1 Generate Interface    **
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
** 1.0.10    21-Sep-2016   Sinil        Redmine #5554, #6128                  **
** 1.0.7     09-Aug-2016   Sinil        Redmine #5693, #5747                  **
** 1.0.6     12-Jul-2016   Sinil        Redmine #5514                         **
** 1.0.5     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.4     16-May-2016   Sinil        Redmine #4903                         **
** 1.0.3     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.2     02-May-2016   Sinil        Redmine #4607                         **
** 1.0.1     02-Dec-2015   Sinil        Memory section changed                **
** 1.0.0     01-Jan-2013   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:D4.5 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for Escrypt HMAC SHA1 Generate */
#include "Cry_EscHmacSha1Generate.h"
/* Mac Interface */
#if (CSM_MAC_GENERATE_STATUS == STD_ON)
#if (CSM_MAC_ESCHMACSHA1GENERATE == STD_ON)
#include "Csm_Cbk.h"
#include "hmac_sha_1.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry EscHmacSha1Generate Transfer buffer*/
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
} Cry_EscHmacSha1GenerateTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Escrypt HMAC SHA1 primitive library context */
static EscHmacSha1_ContextT Cry_GddEscHmacSha1GenerateContext;

/* Global variable for Escrypt HMAC SHA1 transfer buffer structure */
static Cry_EscHmacSha1GenerateTransferBuffer Cry_GddEscHmacSha1GenerateTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_EscHmacSha1GenerateInit                           **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the Escrypt HMAC SHA1        **
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
** Remarks            : Global Variable(s):  Cry_GddEscHmacSha1GenerateTb     **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_EscHmacSha1GenerateInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddEscHmacSha1GenerateTb.ucJobState = NO_JOB;
  Cry_GddEscHmacSha1GenerateTb.pKeyPtr = NULL_PTR;
  Cry_GddEscHmacSha1GenerateTb.pDataPtr = NULL_PTR;
  Cry_GddEscHmacSha1GenerateTb.ulDataLength = CSM_ZERO;
  Cry_GddEscHmacSha1GenerateTb.pResultPtr = NULL_PTR;
  Cry_GddEscHmacSha1GenerateTb.pResultLengthPtr = NULL_PTR;
  Cry_GddEscHmacSha1GenerateTb.blTruncationIsAllowed = CSM_FALSE;

  (void)memset((void*)&Cry_GddEscHmacSha1GenerateContext, 0x00,
    sizeof(EscHmacSha1_ContextT));
}

/*******************************************************************************
** Function Name        : Cry_EscHmacSha1GenerateStart                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Escrypt HMAC SHA1, so that it is     **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_EscHmacSha1GenerateMainFunction() can           **
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
**                        Cry_GddEscHmacSha1GenerateTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscHmacSha1_Init, Cry_EscHmacSha1GenerateInit       **
*******************************************************************************/
Std_ReturnType Cry_EscHmacSha1GenerateStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddEscHmacSha1GenerateTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_EscHmacSha1GenerateInit();

    Cry_GddEscHmacSha1GenerateTb.ucJobState = JOB_START;

    if (Csm_MacGenerateServiceHasCallback() == FALSE)
    {
      /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      LblReturnValue = EscHmacSha1_Init(&Cry_GddEscHmacSha1GenerateContext,
        (const uint8*)((const void*)(keyPtr->data)), keyPtr->length);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscHmacSha1GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscHmacSha1GenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscHmacSha1GenerateTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_EscHmacSha1GenerateUpdate                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Escrypt  **
**                        HMAC SHA1                                           **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscHmacSha1GenerateMainFunction() can process   **
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
**                        Cry_GddEscHmacSha1GenerateTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscHmacSha1_Update                                  **
*******************************************************************************/
Std_ReturnType Cry_EscHmacSha1GenerateUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddEscHmacSha1GenerateTb.ucJobState)
  {
    Cry_GddEscHmacSha1GenerateTb.ucJobState = JOB_UPDATE;

    if (Csm_MacGenerateServiceHasCallback() == FALSE)
    {
      LblReturnValue = EscHmacSha1_Update(&Cry_GddEscHmacSha1GenerateContext,
        dataPtr, dataLength);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscHmacSha1GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscHmacSha1GenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscHmacSha1GenerateTb.pDataPtr = dataPtr;
      Cry_GddEscHmacSha1GenerateTb.ulDataLength = dataLength;
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
** Function Name        : Cry_EscHmacSha1GenerateFinish                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Escrypt **
**                        HMAC SHA1 computation and store the result into the **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscHmacSha1GenerateMainFunction() can finish the**
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
**                        CSM_E_SMALL_BUFFER: provided buffer is too small to **
**                                            store the result                **
**                                                                            **
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddEscHmacSha1GenerateTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscHmacSha1_Finish                                  **
*******************************************************************************/
Std_ReturnType Cry_EscHmacSha1GenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LaaSha1Digest[EscSha1_DIGEST_LEN];
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddEscHmacSha1GenerateTb.ucJobState)
  {
    Cry_GddEscHmacSha1GenerateTb.ucJobState = JOB_FINISH;

    if (Csm_MacGenerateServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if ((*resultLengthPtr < EscSha1_DIGEST_LEN)
        && (TruncationIsAllowed != CSM_TRUE))
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        (void)memset((void*)&LaaSha1Digest, 0x00, sizeof(LaaSha1Digest));

        LblReturnValue = EscHmacSha1_Finish(&Cry_GddEscHmacSha1GenerateContext,
          LaaSha1Digest);

        if (LblReturnValue != CSM_TRUE)
        {
          *resultLengthPtr = (*resultLengthPtr < EscSha1_DIGEST_LEN)
            ? (*resultLengthPtr) : EscSha1_DIGEST_LEN;

          for (LulIndex = CSM_ZERO; LulIndex < *resultLengthPtr; LulIndex++)
          {
            /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
            resultPtr[LulIndex] = LaaSha1Digest[LulIndex];
          }
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddEscHmacSha1GenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddEscHmacSha1GenerateTb.pResultPtr = resultPtr;
      Cry_GddEscHmacSha1GenerateTb.pResultLengthPtr = resultLengthPtr;
      Cry_GddEscHmacSha1GenerateTb.blTruncationIsAllowed = TruncationIsAllowed;
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
** Function Name        : Cry_EscHmacSha1GenerateMainFunction                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_MacGenerateCallbackNotification() with the      **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_EscHmacSha1GenerateStart() or                   **
**                        Cry_EscHmacSha1GenerateUpdate(). For                **
**                        Cry_EscHmacSha1GenerateFinish invocation of         **
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
**                        Cry_GddEscHmacSha1GenerateTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscHmacSha1_Init                                    **
**                        EscHmacSha1_Update                                  **
**                        EscHmacSha1_Finish                                  **
**                        Csm_MacGenerateCallbackNotification                 **
**                        Csm_MacGenerateServiceFinishNotification            **
*******************************************************************************/
void Cry_EscHmacSha1GenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LaaSha1Digest[EscSha1_DIGEST_LEN];
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddEscHmacSha1GenerateTb.ucJobState)
  {
  case JOB_START:
  /* polyspace +3 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    LblReturnValue = EscHmacSha1_Init(&Cry_GddEscHmacSha1GenerateContext,
      (const uint8*)((const void*)(Cry_GddEscHmacSha1GenerateTb.pKeyPtr->data)),
      Cry_GddEscHmacSha1GenerateTb.pKeyPtr->length);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscHmacSha1GenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscHmacSha1GenerateTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LblReturnValue = EscHmacSha1_Update(&Cry_GddEscHmacSha1GenerateContext,
      Cry_GddEscHmacSha1GenerateTb.pDataPtr,
      Cry_GddEscHmacSha1GenerateTb.ulDataLength);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscHmacSha1GenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscHmacSha1GenerateTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if ((*(Cry_GddEscHmacSha1GenerateTb.pResultLengthPtr) < EscSha1_DIGEST_LEN)
      && (Cry_GddEscHmacSha1GenerateTb.blTruncationIsAllowed != CSM_TRUE))
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      (void)memset((void*)&LaaSha1Digest, 0x00, sizeof(LaaSha1Digest));

      LblReturnValue = EscHmacSha1_Finish(&Cry_GddEscHmacSha1GenerateContext,
        LaaSha1Digest);

      if (LblReturnValue != CSM_TRUE)
      {
        *(Cry_GddEscHmacSha1GenerateTb.pResultLengthPtr) =
          (*(Cry_GddEscHmacSha1GenerateTb.pResultLengthPtr) < EscSha1_DIGEST_LEN)
          ? (*(Cry_GddEscHmacSha1GenerateTb.pResultLengthPtr))
          : EscSha1_DIGEST_LEN;

        for (LulIndex = CSM_ZERO; LulIndex
          < *(Cry_GddEscHmacSha1GenerateTb.pResultLengthPtr); LulIndex++)
        {
          /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          Cry_GddEscHmacSha1GenerateTb.pResultPtr[LulIndex]
            = LaaSha1Digest[LulIndex];
        }
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddEscHmacSha1GenerateTb.ucJobState = NO_JOB;

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

#endif /* (CSM_MAC_ESCHMACSHA1GENERATE == STD_ON) */
#endif /* (CSM_MAC_GENERATE_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:D4.5 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
