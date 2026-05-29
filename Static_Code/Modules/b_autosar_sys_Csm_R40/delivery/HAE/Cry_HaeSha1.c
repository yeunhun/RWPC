/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeSha1.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Autoever Sha160 Interface               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 2.6.3.0   24-Mar-2021   TamTV6       Redmine #18165                        **
** 2.6.1.0   08-Oct-2020   JaeHyun      Redmine #25964                        **
** 1.0.1     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.0     12-Feb-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for Autoever Sha160 */
#include "Cry_HaeSha1.h"
/* Hash Interface */
#if (CSM_HASH_STATUS == STD_ON)
#if (CSM_HASH_HAESHA1 == STD_ON)
#include "Csm_Cbk.h"
#include "Hmg_Sha160.h"
#include "string.h"
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HaeSha160 Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const uint8* pDataPtr;
  uint32 ulDataLength;
  uint8* pResultPtr;
  uint32* pResultLengthPtr;
  boolean blTruncationIsAllowed;
} Cry_HaeSha160TransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* SHA160 context structure */
static HmgSha160Ctx Cry_GddHaeSha160Context;

/* Global pointer to variable for Autoever Sha160 transfer buffer structure */
static Cry_HaeSha160TransferBuffer Cry_GddHaeSha160Tb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeSha1Init                                       **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the transfer buffer of the   **
**                      SHA160 module. All module Global variables will be    **
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
** Remarks            : Global Variable(s): Cry_GddHaeSha160Tb                **
**                                                                            **
**                     Function(s) invoked: None                              **
**                                                                            **
*******************************************************************************/
void Cry_HaeSha1Init(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeSha160Tb.ucJobState = NO_JOB;
  Cry_GddHaeSha160Tb.pDataPtr = NULL_PTR;
  Cry_GddHaeSha160Tb.ulDataLength = CSM_ZERO;
  Cry_GddHaeSha160Tb.pResultPtr = NULL_PTR;
  Cry_GddHaeSha160Tb.pResultLengthPtr = NULL_PTR;
  Cry_GddHaeSha160Tb.blTruncationIsAllowed = CSM_FALSE;

  (void)memset((void*)&Cry_GddHaeSha160Context, 0x00, sizeof(HmgSha160Ctx));
}

/*******************************************************************************
** Function Name        : Cry_HaeSha1Start                                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of SHA160, so that SHA160 is able to    **
**                        process the input data                              **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeSha1MainFunction() can process               **
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
** Remarks              : Global Variable(s): Cry_GddHaeSha160Tb              **
**                        Function(s) invoked: Cry_HaeSha1Init, Hmg_Sha160Start  **
*******************************************************************************/
Std_ReturnType Cry_HaeSha1Start(const void* cfgPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaeSha160Tb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_HaeSha1Init();

    Cry_GddHaeSha160Tb.ucJobState = JOB_START;

    if (Csm_HashServiceHasCallback() == FALSE)
    {
      LblReturnValue = Hmg_Sha160Start(&Cry_GddHaeSha160Context);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeSha160Tb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeSha160Tb.ucJobState = NO_JOB;
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
** Function Name        : Cry_HaeSha1Update                                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the SHA160   **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeSha1MainFunction() can process the input     **
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
** Remarks              : Global Variable(s): Cry_GddHaeSha160Tb              **
**                        Function(s) invoked : Hmg_Sha160Update              **
*******************************************************************************/
Std_ReturnType Cry_HaeSha1Update(Csm_ConfigIdType cfgId, const uint8* dataPtr,
  uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Setting the default return value */
  LddReturnValue = E_OK;

  /* Mark the unused parameter */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddHaeSha160Tb.ucJobState)
  {
    Cry_GddHaeSha160Tb.ucJobState = JOB_UPDATE;

    if (Csm_HashServiceHasCallback() == FALSE)
    {
      LblReturnValue = Hmg_Sha160Update(&Cry_GddHaeSha160Context,
        dataPtr, dataLength);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeSha160Tb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeSha160Tb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeSha160Tb.pDataPtr = dataPtr;
      Cry_GddHaeSha160Tb.ulDataLength = dataLength;
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
** Function Name        : Cry_HaeSha1Finish                                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the SHA160  **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeSha1MainFunction() can finish the            **
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
** Remarks              : Global Variable(s): Cry_GddHaeSha160Tb              **
**                        Function(s) invoked : Hmg_Sha160Finish              **
*******************************************************************************/
Std_ReturnType Cry_HaeSha1Finish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  /* Buffer for storing the result locally */
  uint8 LaaSha160ResultBuffer[HMG_SHA160_DIGEST_SIZE];
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & module is ready to finish */
  if (JOB_DONE == Cry_GddHaeSha160Tb.ucJobState)
  {
    Cry_GddHaeSha160Tb.ucJobState = JOB_FINISH;

    if (Csm_HashServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if ((*resultLengthPtr < HMG_SHA160_DIGEST_SIZE)
        && (TruncationIsAllowed != CSM_TRUE))
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        (void)memset((void*)&LaaSha160ResultBuffer, 0x00, sizeof(LaaSha160ResultBuffer));

        LblReturnValue = Hmg_Sha160Finish(&Cry_GddHaeSha160Context,
          LaaSha160ResultBuffer);

        if (LblReturnValue != CSM_TRUE)
        {
          /* Update the length of the result buffer */
          *resultLengthPtr = (*resultLengthPtr < HMG_SHA160_DIGEST_SIZE)
            ? *resultLengthPtr : HMG_SHA160_DIGEST_SIZE;

          /* Copy the result to the OUT buffer */
          for (LulIndex = CSM_ZERO; LulIndex < *resultLengthPtr; LulIndex++)
          {
            /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
            resultPtr[LulIndex] = LaaSha160ResultBuffer[LulIndex];
          }
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeSha160Tb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaeSha160Tb.pResultPtr = resultPtr;
      Cry_GddHaeSha160Tb.pResultLengthPtr = resultLengthPtr;
      Cry_GddHaeSha160Tb.blTruncationIsAllowed = TruncationIsAllowed;
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
** Function Name        : Cry_HaeSha1MainFunction                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_HashCallbackNotification() with the correct     **
**                        return valueonce the main function has completely   **
**                        processed the cryptographic                         **
**                        functions demanded by Cry_HaeSha1Start() or         **
**                        Cry_HaeSha1Update(). For Cry_HaeSha1Finish          **
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
** Remarks              : Global Variable(s): Cry_GddHaeSha160Tb              **
**                                                                            **
**                        Function(s) invoked: Csm_HashCallbackNotification   **
**                                          Csm_HashServiceFinishNotification **
**                                          Hmg_Sha160Start, Hmg_Sha160Update,**
**                                          Hmg_Sha160Finish                  **
*******************************************************************************/
void Cry_HaeSha1MainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  /* Buffer for storing the result locally */
  uint8 LaaSha160ResultBuffer[HMG_SHA160_DIGEST_SIZE];
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddHaeSha160Tb.ucJobState)
  {
  case JOB_START:
    LblReturnValue = Hmg_Sha160Start(&Cry_GddHaeSha160Context);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeSha160Tb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeSha160Tb.ucJobState = NO_JOB;
    }

    /* Callback notification will be invoking the application callback */
    Csm_HashCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LblReturnValue = Hmg_Sha160Update(&Cry_GddHaeSha160Context,
      Cry_GddHaeSha160Tb.pDataPtr, Cry_GddHaeSha160Tb.ulDataLength);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeSha160Tb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeSha160Tb.ucJobState = NO_JOB;
    }

    /* Callback notification will be invoking the application callback */
    Csm_HashCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if ((*(Cry_GddHaeSha160Tb.pResultLengthPtr) < HMG_SHA160_DIGEST_SIZE)
      && (Cry_GddHaeSha160Tb.blTruncationIsAllowed != CSM_TRUE))
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      (void)memset((void*)&LaaSha160ResultBuffer, 0x00, sizeof(LaaSha160ResultBuffer));

      LblReturnValue = Hmg_Sha160Finish(
        &Cry_GddHaeSha160Context, LaaSha160ResultBuffer);

      if (LblReturnValue != CSM_TRUE)
      {
        *(Cry_GddHaeSha160Tb.pResultLengthPtr)
          = (*(Cry_GddHaeSha160Tb.pResultLengthPtr) < HMG_SHA160_DIGEST_SIZE)
          ? *(Cry_GddHaeSha160Tb.pResultLengthPtr) : HMG_SHA160_DIGEST_SIZE;

        for (LulIndex = CSM_ZERO; LulIndex < *(Cry_GddHaeSha160Tb.pResultLengthPtr);
          LulIndex++)
        {
	  /* polyspace +2 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
	  /* polyspace +1 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
          Cry_GddHaeSha160Tb.pResultPtr[LulIndex] = LaaSha160ResultBuffer[LulIndex];
        }
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaeSha160Tb.ucJobState = NO_JOB;

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

#endif /* (CSM_HASH_HAESHA1 == STATUS_ON) */
#endif /* (CSM_HASH_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
