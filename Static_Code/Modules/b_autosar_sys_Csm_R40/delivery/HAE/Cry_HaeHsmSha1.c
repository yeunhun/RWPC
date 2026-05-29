/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeHsmSha1.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Interface                               **
**                - HAE HSM Sha1                                              **
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
** 1.0.3     04-Dec-2019   Sinil        Redmine #20495                        **
** 1.0.2     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.1     17-Apr-2018   Sinil        Redmine #12352                        **
** 1.0.0     09-Aug-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for HAE HSM Sha1 */
#include "Cry_HaeHsmSha1.h"
/* Hash Interface */
#if (CSM_HASH_STATUS == STD_ON)
#if (CSM_HASH_HAEHSMSHA1 == STD_ON)
#include "Csm_Cbk.h"
#include "HSM_Hae.h"
#include "Hsm_HostAPI.h"
#include "CryptoService_Hash.h"
#include "string.h"
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HaeHsmSha1 Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const uint8* pDataPtr;
  uint32 ulDataLength;
  uint8* pResultPtr;
  uint32* pResultLengthPtr;
  boolean blTruncationIsAllowed;
} Cry_HaeHsmSha1TransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static HSMAPI_CTX_t Cry_GddHaeHsmSha1Context;

static Cry_HaeHsmSha1TransferBuffer Cry_GddHaeHsmSha1Tb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeHsmSha1Init                                    **
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
** Remarks            : Global Variable(s)  :                                 **
**                      Cry_GddHaeHsmSha1Tb,                                  **
**                      Cry_GddHaeHsmSha1Context                              **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeHsmSha1Init(void)
{
  Cry_GddHaeHsmSha1Tb.ucJobState = NO_JOB;
  Cry_GddHaeHsmSha1Tb.pDataPtr = NULL_PTR;
  Cry_GddHaeHsmSha1Tb.ulDataLength = CSM_ZERO;
  Cry_GddHaeHsmSha1Tb.pResultPtr = NULL_PTR;
  Cry_GddHaeHsmSha1Tb.pResultLengthPtr = NULL_PTR;
  Cry_GddHaeHsmSha1Tb.blTruncationIsAllowed = CSM_FALSE;

  (void)memset((void*)&Cry_GddHaeHsmSha1Context, 0x00, sizeof(HSMAPI_CTX_t));
}

/*******************************************************************************
** Function Name        : Cry_HaeHsmSha1Start                                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of SHA1, so that SHA1 is able to        **
**                        process the input data                              **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeHsmSha1MainFunction() can process            **
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
** Remarks              : Global Variable(s): Cry_GddHaeHsmSha1Tb             **
**                        Function(s) invoked :                               **
**                        Cry_HaeHsmSha1Init, HSM_Sha160Start                 **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmSha1Start(const void* cfgPtr)
{
  Std_ReturnType LddReturnValue;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaeHsmSha1Tb.ucJobState)
  {
    Cry_HaeHsmSha1Init();

    Cry_GddHaeHsmSha1Tb.ucJobState = JOB_START;

    if (Csm_HashServiceHasCallback() == FALSE)
    {
      LddReturnValue = HSM_Sha160Start(&Cry_GddHaeHsmSha1Context);

      if (LddReturnValue != E_OK)
      {
        LddReturnValue = E_NOT_OK;
        HSM_HaeGetErrorCode();
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeHsmSha1Tb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHsmSha1Tb.ucJobState = NO_JOB;
      }
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
** Function Name        : Cry_HaeHsmSha1Update                                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the SHA1     **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmSha1MainFunction() can process the input  **
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
** Remarks              : Global Variable(s): Cry_GddHaeHsmSha1Tb             **
**                        Function(s) invoked :                               **
**                        HSM_Sha160Update, HSM_WaitResp,                     **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmSha1Update(Csm_ConfigIdType cfgId, const uint8* dataPtr,
  uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
	uint32 LulTimeout;
	uint32 LulRemainingLength;
	uint32 LulTxLength;
	const uint8* LpData;
  uint32 LulTextIndex;

  LddReturnValue = E_OK;
  LulTextIndex = CSM_ZERO;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaeHsmSha1Tb.ucJobState)
  {
    Cry_GddHaeHsmSha1Tb.ucJobState = JOB_UPDATE;

    if (Csm_HashServiceHasCallback() == FALSE)
    {
      LddReturnValue = E_NOT_OK;

      LulRemainingLength = dataLength;
      LpData = dataPtr;
      /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "The length is checked" */
      while (LulRemainingLength > CSM_ZERO)
      {
        if (LulRemainingLength > HSM_HAE_SHA1_MAX_LENGTH)
        {
          LulTxLength = HSM_HAE_SHA1_MAX_LENGTH;
        }
        else
        {
          LulTxLength = LulRemainingLength;
        }
        /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        LddReturnValue = HSM_Sha160Update(&Cry_GddHaeHsmSha1Context,
          &LpData[LulTextIndex], LulTxLength);

        if (LddReturnValue == E_OK)
        {
      	  LulTimeout = CSM_ZERO;
          do
          {
            LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmSha1Context.jobId);
            LulTimeout++;
          } while ((LddReturnValue == HSM_E_WAIT) && (LulTimeout < CRYPTOLIB_HAE_HSM_TIMEOUT));

          if (LddReturnValue == E_OK)
          {
            LulRemainingLength -= LulTxLength;
            LulTextIndex += LulTxLength;
          }
          else
          {
            LulRemainingLength = CSM_ZERO;
            (void)HSM_CancelJob(Cry_GddHaeHsmSha1Context.jobId);
          }
        }
        else
        {
          LulRemainingLength = CSM_ZERO;
        }
      }

      if (LddReturnValue != E_OK)
      {
        LddReturnValue = E_NOT_OK;
        HSM_HaeGetErrorCode();
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeHsmSha1Tb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHsmSha1Tb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeHsmSha1Tb.pDataPtr = dataPtr;
      Cry_GddHaeHsmSha1Tb.ulDataLength = dataLength;
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
** Function Name        : Cry_HaeHsmSha1Finish                                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the SHA1    **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmSha1MainFunction() can finish the         **
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
** Remarks              : Global Variable(s): Cry_GddHaeHsmSha1Tb             **
**                        Function(s) invoked : HSM_Sha160Finish              **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmSha1Finish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed)
{
  Std_ReturnType LddReturnValue;
  uint8 LaaSha1ResultBuffer[SHA160_DIGEST_SIZE];
  uint32 LulIndex;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaeHsmSha1Tb.ucJobState)
  {
    Cry_GddHaeHsmSha1Tb.ucJobState = JOB_FINISH;

    if (Csm_HashServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if ((*resultLengthPtr < SHA160_DIGEST_SIZE)
        && (TruncationIsAllowed != CSM_TRUE))
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        (void)memset((void*)&LaaSha1ResultBuffer, 0x00, sizeof(LaaSha1ResultBuffer));

        LddReturnValue = HSM_Sha160Finish(
          &Cry_GddHaeHsmSha1Context, LaaSha1ResultBuffer);

        if (LddReturnValue == E_OK)
        {
          *resultLengthPtr = (*resultLengthPtr < SHA160_DIGEST_SIZE)
            ? *resultLengthPtr : SHA160_DIGEST_SIZE;

          for (LulIndex = CSM_ZERO; LulIndex < *resultLengthPtr; LulIndex++)
          {
            /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
            resultPtr[LulIndex] = LaaSha1ResultBuffer[LulIndex];
          }
        }
        else
        {
          LddReturnValue = E_NOT_OK;
          HSM_HaeGetErrorCode();
        }
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeHsmSha1Tb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaeHsmSha1Tb.pResultPtr = resultPtr;
      Cry_GddHaeHsmSha1Tb.pResultLengthPtr = resultLengthPtr;
      Cry_GddHaeHsmSha1Tb.blTruncationIsAllowed = TruncationIsAllowed;
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
** Function Name        : Cry_HaeHsmSha1MainFunction                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_HashCallbackNotification() with the correct     **
**                        return valueonce the main function has completely   **
**                        processed the cryptographic                         **
**                        functions demanded by Cry_HaeHsmSha1Start() or      **
**                        Cry_HaeHsmSha1Update(). For Cry_HaeHsmSha1Finish    **
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
** Remarks              : Global Variable(s): Cry_GddHaeHsmSha1Tb             **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_HashCallbackNotification,                       **
**                        Csm_HashServiceFinishNotification,                  **
**                        HSM_Sha160Start, HSM_Sha160Update, HSM_WaitResp,     **
**                        HSM_Sha160Finish                                    **
*******************************************************************************/
void Cry_HaeHsmSha1MainFunction(void)
{
  Std_ReturnType LddReturnValue;
	uint32 LulTimeout;
	uint32 LulRemainingLength;
	uint32 LulTxLength;
	const uint8* LpData;
  uint8 LaaSha1ResultBuffer[SHA160_DIGEST_SIZE];
  uint32 LulIndex;
  uint32 LulTextIndex;

  LddReturnValue = E_OK;
  LulTextIndex = CSM_ZERO;

  switch (Cry_GddHaeHsmSha1Tb.ucJobState)
  {
  case JOB_START:
    LddReturnValue = HSM_Sha160Start(&Cry_GddHaeHsmSha1Context);

    if (LddReturnValue != E_OK)
    {
      LddReturnValue = E_NOT_OK;
      HSM_HaeGetErrorCode();
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeHsmSha1Tb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHsmSha1Tb.ucJobState = NO_JOB;
    }

    Csm_HashCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LulRemainingLength = Cry_GddHaeHsmSha1Tb.ulDataLength;
    LpData = Cry_GddHaeHsmSha1Tb.pDataPtr;

    while (LulRemainingLength > CSM_ZERO)
    {
      if (LulRemainingLength > HSM_HAE_SHA1_MAX_LENGTH)

{
        LulTxLength = HSM_HAE_SHA1_MAX_LENGTH;
      }
      else
      {
        LulTxLength = LulRemainingLength;
      }
      /* polyspace +2 MISRA-C3:11.8 [Justified:Low] "No Impact of this rule violation" */
      LddReturnValue = HSM_Sha160Update(&Cry_GddHaeHsmSha1Context,
        &LpData[LulTextIndex], LulTxLength);

      if (LddReturnValue == E_OK)
      {
    	  LulTimeout = CSM_ZERO;
        do
        {
          LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmSha1Context.jobId);
          LulTimeout++;
        } while ((LddReturnValue == HSM_E_WAIT) && (LulTimeout < CRYPTOLIB_HAE_HSM_TIMEOUT));

        if (LddReturnValue == E_OK)
        {
          LulRemainingLength -= LulTxLength;
          LulTextIndex += LulTxLength;
        }
        else
        {
          LulRemainingLength = CSM_ZERO;
          (void)HSM_CancelJob(Cry_GddHaeHsmSha1Context.jobId);
        }
      }
      else
      {
        LulRemainingLength = CSM_ZERO;
      }
    }

    if (LddReturnValue != E_OK)
    {
      LddReturnValue = E_NOT_OK;
      HSM_HaeGetErrorCode();
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeHsmSha1Tb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHsmSha1Tb.ucJobState = NO_JOB;
    }

    Csm_HashCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if ((*(Cry_GddHaeHsmSha1Tb.pResultLengthPtr) < SHA160_DIGEST_SIZE)
      && (Cry_GddHaeHsmSha1Tb.blTruncationIsAllowed != CSM_TRUE))
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      (void)memset((void*)&LaaSha1ResultBuffer, 0x00, sizeof(LaaSha1ResultBuffer));

      LddReturnValue = HSM_Sha160Finish(
        &Cry_GddHaeHsmSha1Context, LaaSha1ResultBuffer);

      if (LddReturnValue == E_OK)
      {
        *(Cry_GddHaeHsmSha1Tb.pResultLengthPtr)
          = (*(Cry_GddHaeHsmSha1Tb.pResultLengthPtr) < SHA160_DIGEST_SIZE)
            ? *(Cry_GddHaeHsmSha1Tb.pResultLengthPtr) : SHA160_DIGEST_SIZE;

        for (LulIndex = CSM_ZERO;
          LulIndex < *(Cry_GddHaeHsmSha1Tb.pResultLengthPtr); LulIndex++)
        {
	  /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
	  /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
          Cry_GddHaeHsmSha1Tb.pResultPtr[LulIndex]
            = LaaSha1ResultBuffer[LulIndex];
        }
      }
      else
      {
        LddReturnValue = E_NOT_OK;
        HSM_HaeGetErrorCode();
      }
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaeHsmSha1Tb.ucJobState = NO_JOB;

    Csm_HashCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    Csm_HashServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_HASH_HAEHSMSHA1 == STATUS_ON) */
#endif /* (CSM_HASH_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
