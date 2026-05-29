/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeHsmHmacSha256Generate.c                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HAE HSM HAMC SHA256 Generate Interface  **
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
/* Header File for HAE HSM HMAC SHA256 Generate */
#include "Cry_HaeHsmHmacSha256Generate.h"
/* Mac Interface */
#if (CSM_MAC_GENERATE_STATUS == STD_ON)
#if (CSM_MAC_HAEHSMHMACSHA256GENERATE == STD_ON)
#include "Csm_Cbk.h"
#include "HSM_Hae.h"
#include "Hsm_HostAPI.h"
#include "CryptoService_Hash.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HaeHsmHmacSha256Generate Transfer buffer*/
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
} Cry_HaeHsmHmacSha256GenerateTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static HSMAPI_CTX_t Cry_GddHaeHsmHmacSha256GenerateContext;

static Cry_HaeHsmHmacSha256GenerateTransferBuffer Cry_GddHaeHsmHmacSha256GenerateTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeHsmHmacSha256GenerateInit                      **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the HAE HSM HMAC SHA256      **
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
** Remarks            : Global Variable(s)  :                                 **
**                      Cry_GddHaeHsmHmacSha256GenerateTb,                    **
**                      Cry_GddHaeHsmHmacSha256GenerateContext,               **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeHsmHmacSha256GenerateInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeHsmHmacSha256GenerateTb.ucJobState = NO_JOB;
  Cry_GddHaeHsmHmacSha256GenerateTb.pKeyPtr = NULL_PTR;
  Cry_GddHaeHsmHmacSha256GenerateTb.pDataPtr = NULL_PTR;
  Cry_GddHaeHsmHmacSha256GenerateTb.ulDataLength = CSM_ZERO;
  Cry_GddHaeHsmHmacSha256GenerateTb.pResultPtr = NULL_PTR;
  Cry_GddHaeHsmHmacSha256GenerateTb.pResultLengthPtr = NULL_PTR;
  Cry_GddHaeHsmHmacSha256GenerateTb.blTruncationIsAllowed = CSM_FALSE;

  (void)memset((void*)&Cry_GddHaeHsmHmacSha256GenerateContext, 0x00,
    sizeof(HSMAPI_CTX_t));
}

/*******************************************************************************
** Function Name        : Cry_HaeHsmHmacSha256GenerateStart                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HAE HSM HMAC SHA256, so that it is   **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeHsmHmacSha256GenerateMainFunction() can      **
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
**                        Cry_GddHaeHsmHmacSha256GenerateTb,                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        HSM_HmacSha256Start,                                **
**                        Cry_HaeHsmHmacSha256GenerateInit,                   **
**                        Csm_MacGenerateServiceHasCallback                   **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmHmacSha256GenerateStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  uint16 LusKeyNum;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaeHsmHmacSha256GenerateTb.ucJobState)
  {
    Cry_HaeHsmHmacSha256GenerateInit();

    Cry_GddHaeHsmHmacSha256GenerateTb.ucJobState = JOB_START;

    if (Csm_MacGenerateServiceHasCallback() == FALSE)
    {
      LusKeyNum = CSM_ZERO;
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        LusKeyNum = keyPtr->data[CSM_ZERO];
      }
      else if (keyPtr->length == CSM_TWO)
      {
        LusKeyNum = keyPtr->data[CSM_ZERO];
        /* polyspace +1 MISRA-C3:10.6,10.7,12.2 [Justified:Low] "No Impact of this rule violation" */
	      LusKeyNum |= (keyPtr->data[CSM_ONE]) << 8;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LddReturnValue = HSM_HmacSha256Start(
          &Cry_GddHaeHsmHmacSha256GenerateContext,
          LusKeyNum);

        if (LddReturnValue != E_OK)
        {
          LddReturnValue = E_NOT_OK;
          HSM_HaeGetErrorCode();
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeHsmHmacSha256GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHsmHmacSha256GenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeHsmHmacSha256GenerateTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_HaeHsmHmacSha256GenerateUpdate                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the HAE HSM  **
**                        HMAC SHA256                                         **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmHmacSha256GenerateMainFunction() can      **
**                        process the input data                              **
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
**                        Cry_GddHaeHsmHmacSha256GenerateTb,                  **
**                        Cry_GddHaeHsmHmacSha256GenerateContext              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacGenerateServiceHasCallback,                  **
**                        HSM_HmacSha256Update, HSM_WaitResp,                 **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmHmacSha256GenerateUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
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

  if (JOB_DONE == Cry_GddHaeHsmHmacSha256GenerateTb.ucJobState)
  {
    Cry_GddHaeHsmHmacSha256GenerateTb.ucJobState = JOB_UPDATE;

    if (Csm_MacGenerateServiceHasCallback() == FALSE)
    {
      LddReturnValue = E_NOT_OK;

      LulRemainingLength = dataLength;
      LpData = dataPtr;
      /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "The length is checked" */
      while (LulRemainingLength > CSM_ZERO)
      {
        if (LulRemainingLength > HSM_HAE_SHA256_MAX_LENGTH)
        {
          LulTxLength = HSM_HAE_SHA256_MAX_LENGTH;
        }
        else
        {
          LulTxLength = LulRemainingLength;
        }
        /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        LddReturnValue = HSM_HmacSha256Update(&Cry_GddHaeHsmHmacSha256GenerateContext,
          &LpData[LulTextIndex], LulTxLength);

        if (LddReturnValue == E_OK)
        {
      	  LulTimeout = CSM_ZERO;
          do
          {
            LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmHmacSha256GenerateContext.jobId);
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
            (void)HSM_CancelJob(Cry_GddHaeHsmHmacSha256GenerateContext.jobId);
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
        Cry_GddHaeHsmHmacSha256GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHsmHmacSha256GenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeHsmHmacSha256GenerateTb.pDataPtr = dataPtr;
      Cry_GddHaeHsmHmacSha256GenerateTb.ulDataLength = dataLength;
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
** Function Name        : Cry_HaeHsmHmacSha256GenerateFinish                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the HAE HSM **
**                        HMAC SHA256 computation and store the result into   **
**                        the memory location given                           **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmHmacSha256GenerateMainFunction() can      **
**                        finish the computation and store the result in the  **
**                        memory location given                               **
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
**                        Cry_GddHaeHsmHmacSha256GenerateTb,                  **
**                        Cry_GddHaeHsmHmacSha256GenerateContext              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacGenerateServiceHasCallback,                  **
**                        HSM_HmacSha256Finish                                **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmHmacSha256GenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed)
{
  Std_ReturnType LddReturnValue;
  uint8 LaaHmacSha256Digest[SHA256_DIGEST_SIZE];
  uint32 LulIndex;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaeHsmHmacSha256GenerateTb.ucJobState)
  {
    Cry_GddHaeHsmHmacSha256GenerateTb.ucJobState = JOB_FINISH;

    if (Csm_MacGenerateServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if ((*resultLengthPtr < SHA256_DIGEST_SIZE)
        && (TruncationIsAllowed != CSM_TRUE))
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        (void)memset((void*)&LaaHmacSha256Digest, 0x00, sizeof(LaaHmacSha256Digest));

        LddReturnValue = HSM_HmacSha256Finish(
          &Cry_GddHaeHsmHmacSha256GenerateContext, LaaHmacSha256Digest);

        if (LddReturnValue == E_OK)
        {
          *resultLengthPtr = (*resultLengthPtr < SHA256_DIGEST_SIZE)
            ? *resultLengthPtr : SHA256_DIGEST_SIZE;

          for (LulIndex = CSM_ZERO; LulIndex < *resultLengthPtr; LulIndex++)
          {
            /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
            resultPtr[LulIndex] = LaaHmacSha256Digest[LulIndex];
          }
        }
        else
        {
          LddReturnValue = E_NOT_OK;
          HSM_HaeGetErrorCode();
        }
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeHsmHmacSha256GenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaeHsmHmacSha256GenerateTb.pResultPtr = resultPtr;
      Cry_GddHaeHsmHmacSha256GenerateTb.pResultLengthPtr = resultLengthPtr;
      Cry_GddHaeHsmHmacSha256GenerateTb.blTruncationIsAllowed = TruncationIsAllowed;
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
** Function Name        : Cry_HaeHsmHmacSha256GenerateMainFunction            **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_MacGenerateCallbackNotification() with the      **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_HaeHsmHmacSha256GenerateStart() or              **
**                        Cry_HaeHsmHmacSha256GenerateUpdate(). For           **
**                        Cry_HaeHsmHmacSha256GenerateFinish invocation of    **
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
**                        Cry_GddHaeHsmHmacSha256GenerateTb,                  **
**                        Cry_GddHaeHsmHmacSha256GenerateContext              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        HSM_HmacSha256Start, HSM_HmacSha256Update,          **
**                        HSM_WaitResp,                                       **
**                        HSM_HmacSha256Finish,                               **
**                        Csm_MacGenerateCallbackNotification,                **
**                        Csm_MacGenerateServiceFinishNotification            **
*******************************************************************************/
void Cry_HaeHsmHmacSha256GenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  uint16 LusKeyNum;
	uint32 LulTimeout;
	uint32 LulRemainingLength;
	uint32 LulTxLength;
	const uint8* LpData;
  uint8 LaaHmacSha256Digest[SHA256_DIGEST_SIZE];
  uint32 LulIndex;
  uint32 LulTextIndex;

  LddReturnValue = E_OK;
  LulTextIndex = CSM_ZERO;

  switch (Cry_GddHaeHsmHmacSha256GenerateTb.ucJobState)
  {
  case JOB_START:
    LusKeyNum = CSM_ZERO;
    /* polyspace +11 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +10 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddHaeHsmHmacSha256GenerateTb.pKeyPtr->length == CSM_ONE)
    {
      LusKeyNum = Cry_GddHaeHsmHmacSha256GenerateTb.pKeyPtr->data[CSM_ZERO];
    }
    else if (Cry_GddHaeHsmHmacSha256GenerateTb.pKeyPtr->length == CSM_TWO)
    {
      LusKeyNum = Cry_GddHaeHsmHmacSha256GenerateTb.pKeyPtr->data[CSM_ZERO];
      /* polyspace +1 MISRA-C3:10.6,10.7,12.2 [Justified:Low] "No Impact of this rule violation" */
      LusKeyNum |= (Cry_GddHaeHsmHmacSha256GenerateTb.pKeyPtr->data[CSM_ONE]) << 8;
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LddReturnValue = HSM_HmacSha256Start(
        &Cry_GddHaeHsmHmacSha256GenerateContext,
        LusKeyNum);

      if (LddReturnValue != E_OK)
      {
        LddReturnValue = E_NOT_OK;
        HSM_HaeGetErrorCode();
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeHsmHmacSha256GenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHsmHmacSha256GenerateTb.ucJobState = NO_JOB;
    }

    Csm_MacGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LddReturnValue = E_NOT_OK;

    LulRemainingLength = Cry_GddHaeHsmHmacSha256GenerateTb.ulDataLength;
    LpData = Cry_GddHaeHsmHmacSha256GenerateTb.pDataPtr;

    while (LulRemainingLength > CSM_ZERO)
    {
      if (LulRemainingLength > HSM_HAE_SHA256_MAX_LENGTH)

      {
        LulTxLength = HSM_HAE_SHA256_MAX_LENGTH;
      }
      else
      {
        LulTxLength = LulRemainingLength;
      }

      LddReturnValue = HSM_HmacSha256Update(&Cry_GddHaeHsmHmacSha256GenerateContext,
        &LpData[LulTextIndex], LulTxLength);

      if (LddReturnValue == E_OK)
      {
    	  LulTimeout = CSM_ZERO;
        do
        {
          LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmHmacSha256GenerateContext.jobId);
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
          (void)HSM_CancelJob(Cry_GddHaeHsmHmacSha256GenerateContext.jobId);
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
      Cry_GddHaeHsmHmacSha256GenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHsmHmacSha256GenerateTb.ucJobState = NO_JOB;
    }

    Csm_MacGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if ((*(Cry_GddHaeHsmHmacSha256GenerateTb.pResultLengthPtr) < SHA256_DIGEST_SIZE)
      && (Cry_GddHaeHsmHmacSha256GenerateTb.blTruncationIsAllowed != CSM_TRUE))
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      (void)memset((void*)&LaaHmacSha256Digest, 0x00, sizeof(LaaHmacSha256Digest));

      LddReturnValue = HSM_HmacSha256Finish(
        &Cry_GddHaeHsmHmacSha256GenerateContext, LaaHmacSha256Digest);

      if (LddReturnValue == E_OK)
      {
        *(Cry_GddHaeHsmHmacSha256GenerateTb.pResultLengthPtr)
          = (*(Cry_GddHaeHsmHmacSha256GenerateTb.pResultLengthPtr) < SHA256_DIGEST_SIZE)
          ? *(Cry_GddHaeHsmHmacSha256GenerateTb.pResultLengthPtr) : SHA256_DIGEST_SIZE;

        for (LulIndex = CSM_ZERO;
          LulIndex < *(Cry_GddHaeHsmHmacSha256GenerateTb.pResultLengthPtr); LulIndex++)
        {
	  /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
	  /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
          (Cry_GddHaeHsmHmacSha256GenerateTb.pResultPtr)[LulIndex]
            = LaaHmacSha256Digest[LulIndex];
        }
      }
      else
      {
        LddReturnValue = E_NOT_OK;
        HSM_HaeGetErrorCode();
      }
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaeHsmHmacSha256GenerateTb.ucJobState = NO_JOB;

    Csm_MacGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    Csm_MacGenerateServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_MAC_HAEHSMHMACSHA256GENERATE == STD_ON) */
#endif /* (CSM_MAC_GENERATE_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
