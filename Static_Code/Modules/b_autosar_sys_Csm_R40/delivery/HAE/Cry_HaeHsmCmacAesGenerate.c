/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeHsmCmacAesGenerate.c                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HAE HSM CMAC AES Generate Interface     **
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
** 2.6.1.0   05-Oct-2020   JaeHyun      Redmine #25347, #25964                **
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
/* Header File for HAE HSM CMAC AES Generate */
#include "Cry_HaeHsmCmacAesGenerate.h"
/* Mac Interface */
#if (CSM_MAC_GENERATE_STATUS == STD_ON)
#if (CSM_MAC_HAEHSMCMACAESGENERATE == STD_ON)
#include "Csm_Cbk.h"
#include "HSM_Hae.h"
#include "Hsm_HostAPI.h"
#include "CryptoService_Aes.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HaeHsmCmacAesGenerate Transfer buffer*/
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
} Cry_HaeHsmCmacAesGenerateTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"

static uint16 Cry_GusHaeHsmCmacAesGenerateKeyNum;

#define CSM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static HSMAPI_CTX_t Cry_GddHaeHsmCmacAesGenerateContext;

static Cry_HaeHsmCmacAesGenerateTransferBuffer Cry_GddHaeHsmCmacAesGenerateTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeHsmCmacAesGenerateInit                         **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the HAE HSM CMAC AES         **
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
**                      Cry_GddHaeHsmCmacAesGenerateTb,                       **
**                      Cry_GddHaeHsmCmacAesGenerateContext,                  **
**                      Cry_GusHaeHsmCmacAesGenerateKeyNum                    **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeHsmCmacAesGenerateInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeHsmCmacAesGenerateTb.ucJobState = NO_JOB;
  Cry_GddHaeHsmCmacAesGenerateTb.pKeyPtr = NULL_PTR;
  Cry_GddHaeHsmCmacAesGenerateTb.pDataPtr = NULL_PTR;
  Cry_GddHaeHsmCmacAesGenerateTb.ulDataLength = CSM_ZERO;
  Cry_GddHaeHsmCmacAesGenerateTb.pResultPtr = NULL_PTR;
  Cry_GddHaeHsmCmacAesGenerateTb.pResultLengthPtr = NULL_PTR;
  Cry_GddHaeHsmCmacAesGenerateTb.blTruncationIsAllowed = CSM_FALSE;

  (void)memset((void*)&Cry_GddHaeHsmCmacAesGenerateContext, 0x00,
    sizeof(HSMAPI_CTX_t));

  Cry_GusHaeHsmCmacAesGenerateKeyNum = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_HaeHsmCmacAesGenerateStart                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HAE HSM CMAC AES, so that it is      **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeHsmCmacAesGenerateMainFunction() can         **
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
**                        Cry_GddHaeHsmCmacAesGenerateTb,                     **
**                        Cry_GusHaeHsmCmacAesGenerateKeyNum                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_HaeHsmCmacAesGenerateInit,                      **
**                        Csm_MacGenerateServiceHasCallback                   **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmCmacAesGenerateStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  uint16 LusKeyNum;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaeHsmCmacAesGenerateTb.ucJobState)
  {
    Cry_HaeHsmCmacAesGenerateInit();

    Cry_GddHaeHsmCmacAesGenerateTb.ucJobState = JOB_START;

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
        Cry_GusHaeHsmCmacAesGenerateKeyNum = LusKeyNum;

        Cry_GddHaeHsmCmacAesGenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHsmCmacAesGenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeHsmCmacAesGenerateTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_HaeHsmCmacAesGenerateUpdate                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the HAE HSM  **
**                        CMAC AES                                            **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmCmacAesGenerateMainFunction() can process **
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
**                        Cry_GddHaeHsmCmacAesGenerateTb,                     **
**                        Cry_GddHaeHsmCmacAesGenerateContext,                **
**                        Cry_GusHaeHsmCmacAesGenerateKeyNum                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacGenerateServiceHasCallback,                  **
**                        HSM_AesCmacStart, HSM_AesCmacUpdate, HSM_WaitResp,   **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmCmacAesGenerateUpdate(Csm_ConfigIdType cfgId,
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

  if (JOB_DONE == Cry_GddHaeHsmCmacAesGenerateTb.ucJobState)
  {
    Cry_GddHaeHsmCmacAesGenerateTb.ucJobState = JOB_UPDATE;

    if (Csm_MacGenerateServiceHasCallback() == FALSE)
    {
      LddReturnValue = HSM_AesCmacStart(&Cry_GddHaeHsmCmacAesGenerateContext,
        Cry_GusHaeHsmCmacAesGenerateKeyNum, dataLength);

      if (LddReturnValue == E_OK)
      {
        LddReturnValue = E_NOT_OK;

        LulRemainingLength = dataLength;
        LpData = dataPtr;
        /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The length is checked" */
        while (LulRemainingLength > CSM_ZERO)
        {
          if (LulRemainingLength > HSM_HAE_AES_MAX_LENGTH)
          {
            LulTxLength = HSM_HAE_AES_MAX_LENGTH;
          }
          else
          {
            LulTxLength = LulRemainingLength;
          }

          /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          LddReturnValue = HSM_AesCmacUpdate(&Cry_GddHaeHsmCmacAesGenerateContext,
            &LpData[LulTextIndex], LulTxLength);

          if (LddReturnValue == E_OK)
          {
            LulTimeout = CSM_ZERO;
            do
            {
              LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmCmacAesGenerateContext.jobId);
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
              (void)HSM_CancelJob(Cry_GddHaeHsmCmacAesGenerateContext.jobId);
            }
          }
          else
          {
            LulRemainingLength = CSM_ZERO;
          }
        }
      }

      if (LddReturnValue != E_OK)
      {
        LddReturnValue = E_NOT_OK;
        HSM_HaeGetErrorCode();
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeHsmCmacAesGenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHsmCmacAesGenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeHsmCmacAesGenerateTb.pDataPtr = dataPtr;
      Cry_GddHaeHsmCmacAesGenerateTb.ulDataLength = dataLength;
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
** Function Name        : Cry_HaeHsmCmacAesGenerateFinish                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the HAE HSM **
**                        CMAC AES computation and store the result into      **
**                        the memory location given                           **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmCmacAesGenerateMainFunction() can finish  **
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
**                        Cry_GddHaeHsmCmacAesGenerateTb,                     **
**                        Cry_GddHaeHsmCmacAesGenerateContext                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacGenerateServiceHasCallback,                  **
**                        HSM_AesCmacFinish                                   **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmCmacAesGenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed)
{
  Std_ReturnType LddReturnValue;
  uint8 LaaCmacAesDigest[HSM_AES128_CMAC_LEN];
  uint32 LulIndex;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaeHsmCmacAesGenerateTb.ucJobState)
  {
    Cry_GddHaeHsmCmacAesGenerateTb.ucJobState = JOB_FINISH;

    if (Csm_MacGenerateServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if ((*resultLengthPtr < HSM_AES128_CMAC_LEN)
        && (TruncationIsAllowed != CSM_TRUE))
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        (void)memset((void*)&LaaCmacAesDigest, 0x00, sizeof(LaaCmacAesDigest));

        LddReturnValue = HSM_AesCmacFinish(
          &Cry_GddHaeHsmCmacAesGenerateContext, LaaCmacAesDigest);

        if (LddReturnValue == E_OK)
        {
          *resultLengthPtr = (*resultLengthPtr < HSM_AES128_CMAC_LEN)
            ? *resultLengthPtr : HSM_AES128_CMAC_LEN;

          for (LulIndex = CSM_ZERO; LulIndex < *resultLengthPtr; LulIndex++)
          {
            /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
            resultPtr[LulIndex] = LaaCmacAesDigest[LulIndex];
          }
        }
        else
        {
          LddReturnValue = E_NOT_OK;
          HSM_HaeGetErrorCode();
        }
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeHsmCmacAesGenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaeHsmCmacAesGenerateTb.pResultPtr = resultPtr;
      Cry_GddHaeHsmCmacAesGenerateTb.pResultLengthPtr = resultLengthPtr;
      Cry_GddHaeHsmCmacAesGenerateTb.blTruncationIsAllowed = TruncationIsAllowed;
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
** Function Name        : Cry_HaeHsmCmacAesGenerateMainFunction               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_MacGenerateCallbackNotification() with the      **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_HaeHsmCmacAesGenerateStart() or                 **
**                        Cry_HaeHsmCmacAesGenerateUpdate(). For              **
**                        Cry_HaeHsmCmacAesGenerateFinish invocation of       **
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
**                        Cry_GddHaeHsmCmacAesGenerateTb,                     **
**                        Cry_GddHaeHsmCmacAesGenerateContext,                **
**                        Cry_GusHaeHsmCmacAesGenerateKeyNum                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        HSM_AesCmacStart, HSM_AesCmacUpdate, HSM_WaitResp,   **
**                        HSM_AesCmacFinish,                                  **
**                        Csm_MacGenerateCallbackNotification,                **
**                        Csm_MacGenerateServiceFinishNotification            **
*******************************************************************************/
void Cry_HaeHsmCmacAesGenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  uint16 LusKeyNum;
  uint32 LulTimeout;
  uint32 LulRemainingLength;
  uint32 LulTxLength;
  const uint8* LpData;
  uint8 LaaCmacAesDigest[HSM_AES128_CMAC_LEN];
  uint32 LulIndex;
  uint32 LulTextIndex;

  LddReturnValue = E_OK;
  LulTextIndex = CSM_ZERO;

  switch (Cry_GddHaeHsmCmacAesGenerateTb.ucJobState)
  {
  case JOB_START:
    LusKeyNum = CSM_ZERO;
    /* polyspace +11 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +10 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddHaeHsmCmacAesGenerateTb.pKeyPtr->length == CSM_ONE)
    {
      LusKeyNum = Cry_GddHaeHsmCmacAesGenerateTb.pKeyPtr->data[CSM_ZERO];
    }
    else if (Cry_GddHaeHsmCmacAesGenerateTb.pKeyPtr->length == CSM_TWO)
    {
      LusKeyNum = Cry_GddHaeHsmCmacAesGenerateTb.pKeyPtr->data[CSM_ZERO];
      /* polyspace +1 MISRA-C3:10.6,10.7,12.2 [Justified:Low] "No Impact of this rule violation" */
      LusKeyNum |= (Cry_GddHaeHsmCmacAesGenerateTb.pKeyPtr->data[CSM_ONE]) << 8;
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GusHaeHsmCmacAesGenerateKeyNum = LusKeyNum;

      Cry_GddHaeHsmCmacAesGenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHsmCmacAesGenerateTb.ucJobState = NO_JOB;
    }

    Csm_MacGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LddReturnValue = HSM_AesCmacStart(&Cry_GddHaeHsmCmacAesGenerateContext,
      Cry_GusHaeHsmCmacAesGenerateKeyNum,
      Cry_GddHaeHsmCmacAesGenerateTb.ulDataLength);

    if (LddReturnValue == E_OK)
    {
      LddReturnValue = E_NOT_OK;

      LulRemainingLength = Cry_GddHaeHsmCmacAesGenerateTb.ulDataLength;
      LpData = Cry_GddHaeHsmCmacAesGenerateTb.pDataPtr;

      while (LulRemainingLength > CSM_ZERO)
      {
        if (LulRemainingLength > HSM_HAE_AES_MAX_LENGTH)
        {
          LulTxLength = HSM_HAE_AES_MAX_LENGTH;
        }
        else
        {
          LulTxLength = LulRemainingLength;
        }

        LddReturnValue = HSM_AesCmacUpdate(&Cry_GddHaeHsmCmacAesGenerateContext,
          &LpData[LulTextIndex], LulTxLength);

        if (LddReturnValue == E_OK)
        {
          LulTimeout = CSM_ZERO;
          do
          {
            LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmCmacAesGenerateContext.jobId);
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
            (void)HSM_CancelJob(Cry_GddHaeHsmCmacAesGenerateContext.jobId);
          }
        }
        else
        {
          LulRemainingLength = CSM_ZERO;
        }
      }
    }

    if (LddReturnValue != E_OK)
    {
      LddReturnValue = E_NOT_OK;
      HSM_HaeGetErrorCode();
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeHsmCmacAesGenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHsmCmacAesGenerateTb.ucJobState = NO_JOB;
    }

    Csm_MacGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if ((*(Cry_GddHaeHsmCmacAesGenerateTb.pResultLengthPtr) < HSM_AES128_CMAC_LEN)
      && (Cry_GddHaeHsmCmacAesGenerateTb.blTruncationIsAllowed != CSM_TRUE))
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      (void)memset((void*)&LaaCmacAesDigest, 0x00, sizeof(LaaCmacAesDigest));

      LddReturnValue = HSM_AesCmacFinish(
        &Cry_GddHaeHsmCmacAesGenerateContext, LaaCmacAesDigest);

      if (LddReturnValue == E_OK)
      {
        *(Cry_GddHaeHsmCmacAesGenerateTb.pResultLengthPtr)
          = (*(Cry_GddHaeHsmCmacAesGenerateTb.pResultLengthPtr) < HSM_AES128_CMAC_LEN)
          ? *(Cry_GddHaeHsmCmacAesGenerateTb.pResultLengthPtr) : HSM_AES128_CMAC_LEN;

        for (LulIndex = CSM_ZERO;
          LulIndex < *(Cry_GddHaeHsmCmacAesGenerateTb.pResultLengthPtr); LulIndex++)
        {
	  /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
	  /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
          Cry_GddHaeHsmCmacAesGenerateTb.pResultPtr[LulIndex]
            = LaaCmacAesDigest[LulIndex];
        }
      }
      else
      {
        LddReturnValue = E_NOT_OK;
        HSM_HaeGetErrorCode();
      }
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaeHsmCmacAesGenerateTb.ucJobState = NO_JOB;

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

#endif /* (CSM_MAC_HAEHSMCMACAESGENERATE == STD_ON) */
#endif /* (CSM_MAC_GENERATE_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
