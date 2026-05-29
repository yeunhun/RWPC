/*******************************************************************************
**                                                                            **
**  (C) 2015~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_EscSha1.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Escrypt Sha1 Interface                  **
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
** 1.1.0     11-Jan-2017   Sinil        Redmine #7198                         **
** 1.0.8     21-Sep-2016   Sinil        Redmine #5554, #6128                  **
** 1.0.7     09-Aug-2016   Sinil        Redmine #5693                         **
** 1.0.6     12-Jul-2016   Sinil        Redmine #5514                         **
** 1.0.5     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.4     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.3     02-May-2016   Sinil        Redmine #4607                         **
** 1.0.2     02-Dec-2015   Sinil        1. Using common library in FBL        **
**                                      2. Memory section changed             **
** 1.0.1     10-Nov-2015   Sinil        Using common library in FBL           **
** 1.0.0     10-Mar-2015   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for Escrypt Sha1 */
#include "Cry_EscSha1.h"
/* Hash Interface */
#if (CSM_HASH_STATUS == STD_ON)
#if (CSM_HASH_ESCSHA1 == STD_ON)
#include "Csm_Cbk.h"
#include "sha_1.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry EscSha1 Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const uint8* pDataPtr;
  uint32 ulDataLength;
  uint8* pResultPtr;
  uint32* pResultLengthPtr;
  boolean blTruncationIsAllowed;
} Cry_EscSha1TransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* SHA1 context structure */
static EscSha1_ContextT Cry_GddEscSha1Context;

/* Global pointer to variable for Escrypt Sha1 transfer buffer structure */
static Cry_EscSha1TransferBuffer Cry_GddEscSha1Tb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_EscSha1Init                                       **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the transfer buffer of the   **
**                      SHA1 module. All module Global variables will be      **
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
** Remarks            : Global Variable(s): Cry_GddEscSha1Tb                  **
**                                                                            **
**                     Function(s) invoked: None                              **
**                                                                            **
*******************************************************************************/
void Cry_EscSha1Init(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddEscSha1Tb.ucJobState = NO_JOB;
  Cry_GddEscSha1Tb.pDataPtr = NULL_PTR;
  Cry_GddEscSha1Tb.ulDataLength = CSM_ZERO;
  Cry_GddEscSha1Tb.pResultPtr = NULL_PTR;
  Cry_GddEscSha1Tb.pResultLengthPtr = NULL_PTR;
  Cry_GddEscSha1Tb.blTruncationIsAllowed = CSM_FALSE;

  (void)memset((void*)&Cry_GddEscSha1Context, 0x00, sizeof(EscSha1_ContextT));
}

/*******************************************************************************
** Function Name        : Cry_EscSha1Start                                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of SHA1, so that SHA1 is able to        **
**                        process the input data                              **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_EscSha1MainFunction() can process               **
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
** Remarks              : Global Variable(s): Cry_GddEscSha1Tb                **
**                        Function(s) invoked: Cry_EscSha1Init, EscSha1_Init  **
*******************************************************************************/
Std_ReturnType Cry_EscSha1Start(const void* cfgPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddEscSha1Tb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_EscSha1Init();

    Cry_GddEscSha1Tb.ucJobState = JOB_START;

    if (Csm_HashServiceHasCallback() == FALSE)
    {
      LblReturnValue = EscSha1_Init(&Cry_GddEscSha1Context);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscSha1Tb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscSha1Tb.ucJobState = NO_JOB;
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
** Function Name        : Cry_EscSha1Update                                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the SHA1     **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscSha1MainFunction() can process the input     **
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
** Remarks              : Global Variable(s): Cry_GddEscSha1Tb                **
**                        Function(s) invoked : EscSha1_Update                **
*******************************************************************************/
Std_ReturnType Cry_EscSha1Update(Csm_ConfigIdType cfgId, const uint8* dataPtr,
  uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Setting the default return value */
  LddReturnValue = E_OK;

  /* Mark the unused parameter */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddEscSha1Tb.ucJobState)
  {
    Cry_GddEscSha1Tb.ucJobState = JOB_UPDATE;

    if (Csm_HashServiceHasCallback() == FALSE)
    {
      LblReturnValue = EscSha1_Update(&Cry_GddEscSha1Context,
        dataPtr, dataLength);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscSha1Tb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscSha1Tb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscSha1Tb.pDataPtr = dataPtr;
      Cry_GddEscSha1Tb.ulDataLength = dataLength;
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
** Function Name        : Cry_EscSha1Finish                                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the SHA1    **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscSha1MainFunction() can finish the            **
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
** Remarks              : Global Variable(s): Cry_GddEscSha1Tb                **
**                        Function(s) invoked : EscSha1_Finish                **
*******************************************************************************/
Std_ReturnType Cry_EscSha1Finish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  /* Buffer for storing the result locally */
  uint8 LaaSha1ResultBuffer[EscSha1_DIGEST_LEN];
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & module is ready to finish */
  if (JOB_DONE == Cry_GddEscSha1Tb.ucJobState)
  {
    Cry_GddEscSha1Tb.ucJobState = JOB_FINISH;

    if (Csm_HashServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if ((*resultLengthPtr < EscSha1_DIGEST_LEN)
        && (TruncationIsAllowed != CSM_TRUE))
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        (void)memset((void*)&LaaSha1ResultBuffer, 0x00, sizeof(LaaSha1ResultBuffer));

        LblReturnValue = EscSha1_Finish(&Cry_GddEscSha1Context,
          LaaSha1ResultBuffer);

        if (LblReturnValue != CSM_TRUE)
        {
          /* Update the length of the result buffer */
          *resultLengthPtr = (*resultLengthPtr < EscSha1_DIGEST_LEN)
            ? *resultLengthPtr : EscSha1_DIGEST_LEN;

          /* Copy the result to the OUT buffer */
          for (LulIndex = CSM_ZERO; LulIndex < *resultLengthPtr; LulIndex++)
          {
            /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
            resultPtr[LulIndex] = LaaSha1ResultBuffer[LulIndex];
          }
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddEscSha1Tb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddEscSha1Tb.pResultPtr = resultPtr;
      Cry_GddEscSha1Tb.pResultLengthPtr = resultLengthPtr;
      Cry_GddEscSha1Tb.blTruncationIsAllowed = TruncationIsAllowed;
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
** Function Name        : Cry_EscSha1MainFunction                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_HashCallbackNotification() with the correct     **
**                        return valueonce the main function has completely   **
**                        processed the cryptographic                         **
**                        functions demanded by Cry_EscSha1Start() or         **
**                        Cry_EscSha1Update(). For Cry_EscSha1Finish          **
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
** Remarks              : Global Variable(s): Cry_GddEscSha1Tb                **
**                                                                            **
**                        Function(s) invoked: Csm_HashCallbackNotification   **
**                                          Csm_HashServiceFinishNotification **
**                                          EscSha1_Init, EscSha1_Update,     **
**                                          EscSha1_Finish                    **
*******************************************************************************/
void Cry_EscSha1MainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  /* Buffer for storing the result locally */
  uint8 LaaSha1ResultBuffer[EscSha1_DIGEST_LEN];
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddEscSha1Tb.ucJobState)
  {
  case JOB_START:
    LblReturnValue = EscSha1_Init(&Cry_GddEscSha1Context);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscSha1Tb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscSha1Tb.ucJobState = NO_JOB;
    }

    /* Callback notification will be invoking the application callback */
    Csm_HashCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LblReturnValue = EscSha1_Update(&Cry_GddEscSha1Context,
      Cry_GddEscSha1Tb.pDataPtr, Cry_GddEscSha1Tb.ulDataLength);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscSha1Tb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscSha1Tb.ucJobState = NO_JOB;
    }

    /* Callback notification will be invoking the application callback */
    Csm_HashCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if ((*(Cry_GddEscSha1Tb.pResultLengthPtr) < EscSha1_DIGEST_LEN)
      && (Cry_GddEscSha1Tb.blTruncationIsAllowed != CSM_TRUE))
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      (void)memset((void*)&LaaSha1ResultBuffer, 0x00, sizeof(LaaSha1ResultBuffer));

      LblReturnValue = EscSha1_Finish(
        &Cry_GddEscSha1Context, LaaSha1ResultBuffer);

      if (LblReturnValue != CSM_TRUE)
      {
        *(Cry_GddEscSha1Tb.pResultLengthPtr)
          = (*(Cry_GddEscSha1Tb.pResultLengthPtr) < EscSha1_DIGEST_LEN)
          ? *(Cry_GddEscSha1Tb.pResultLengthPtr) : EscSha1_DIGEST_LEN;

        for (LulIndex = CSM_ZERO; LulIndex < *(Cry_GddEscSha1Tb.pResultLengthPtr);
          LulIndex++)
        {
          /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          Cry_GddEscSha1Tb.pResultPtr[LulIndex] = LaaSha1ResultBuffer[LulIndex];
        }
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddEscSha1Tb.ucJobState = NO_JOB;

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

#endif /* (CSM_HASH_ESCSHA1 == STATUS_ON) */
#endif /* (CSM_HASH_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
