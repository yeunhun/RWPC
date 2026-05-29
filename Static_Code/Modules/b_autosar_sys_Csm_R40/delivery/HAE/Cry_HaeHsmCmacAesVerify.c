/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeHsmCmacAesVerify.c                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HAE HSM CMAC AES Verify Interface       **
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
/* Header File for HAE HSM CMAC AES Verify */
#include "Cry_HaeHsmCmacAesVerify.h"
/* Mac Interface */
#if (CSM_MAC_VERIFY_STATUS == STD_ON)
#if (CSM_MAC_HAEHSMCMACAESVERIFY == STD_ON)
#include "Csm_Cbk.h"
#include "HSM_Hae.h"
#include "Hsm_HostAPI.h"
#include "CryptoService_Aes.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HaeHsmCmacAesVerify Transfer buffer*/
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
} Cry_HaeHsmCmacAesVerifyTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"

static uint16 Cry_GusHaeHsmCmacAesVerifyKeyNum;

#define CSM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static HSMAPI_CTX_t Cry_GddHaeHsmCmacAesVerifyContext;

static Cry_HaeHsmCmacAesVerifyTransferBuffer Cry_GddHaeHsmCmacAesVerifyTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeHsmCmacAesVerifyInit                           **
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
**                      Cry_GddHaeHsmCmacAesVerifyTb,                         **
**                      Cry_GddHaeHsmCmacAesVerifyContext,                    **
**                      Cry_GusHaeHsmCmacAesVerifyKeyNum                      **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeHsmCmacAesVerifyInit(void)
{
  Cry_GddHaeHsmCmacAesVerifyTb.ucJobState = NO_JOB;
  Cry_GddHaeHsmCmacAesVerifyTb.pKeyPtr = NULL_PTR;
  Cry_GddHaeHsmCmacAesVerifyTb.pDataPtr = NULL_PTR;
  Cry_GddHaeHsmCmacAesVerifyTb.ulDataLength = CSM_ZERO;
  Cry_GddHaeHsmCmacAesVerifyTb.pMacPtr = NULL_PTR;
  Cry_GddHaeHsmCmacAesVerifyTb.ulMacLength = CSM_ZERO;
  Cry_GddHaeHsmCmacAesVerifyTb.pResultPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddHaeHsmCmacAesVerifyContext, 0x00,
    sizeof(HSMAPI_CTX_t));

  Cry_GusHaeHsmCmacAesVerifyKeyNum = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_HaeHsmCmacAesVerifyStart                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HAE HSM CMAC AES, so that if is      **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeHsmCmacAesVerifyMainFunction() can process   **
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
**                        Cry_GddHaeHsmCmacAesVerifyTb,                       **
**                        Cry_GusHaeHsmCmacAesVerifyKeyNum                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_HaeHsmCmacAesVerifyInit,                        **
**                        Csm_MacVerifyServiceHasCallback                     **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmCmacAesVerifyStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  uint16 LusKeyNum;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaeHsmCmacAesVerifyTb.ucJobState)
  {
    Cry_HaeHsmCmacAesVerifyInit();

    Cry_GddHaeHsmCmacAesVerifyTb.ucJobState = JOB_START;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
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
        Cry_GusHaeHsmCmacAesVerifyKeyNum = LusKeyNum;

        Cry_GddHaeHsmCmacAesVerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHsmCmacAesVerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeHsmCmacAesVerifyTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_HaeHsmCmacAesVerifyUpdate                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the HAE HSM  **
**                        CMAC AES                                            **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmCmacAesVerifyMainFunction() can process   **
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
**                        Cry_GddHaeHsmCmacAesVerifyTb,                       **
**                        Cry_GddHaeHsmCmacAesVerifyContext,                  **
**                        Cry_GusHaeHsmCmacAesVerifyKeyNum                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacVerifyServiceHasCallback,                    **
**                        HSM_AesCmacStart, HSM_AesCmacUpdate, HSM_WaitResp,   **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmCmacAesVerifyUpdate(Csm_ConfigIdType cfgId,
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

  if (JOB_DONE == Cry_GddHaeHsmCmacAesVerifyTb.ucJobState)
  {
    Cry_GddHaeHsmCmacAesVerifyTb.ucJobState = JOB_UPDATE;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      LddReturnValue = HSM_AesCmacStart(&Cry_GddHaeHsmCmacAesVerifyContext,
        Cry_GusHaeHsmCmacAesVerifyKeyNum, dataLength);

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
          LddReturnValue = HSM_AesCmacUpdate(&Cry_GddHaeHsmCmacAesVerifyContext,
            &LpData[LulTextIndex], LulTxLength);

          if (LddReturnValue == E_OK)
          {
            LulTimeout = CSM_ZERO;
            do
            {
              LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmCmacAesVerifyContext.jobId);
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
              (void)HSM_CancelJob(Cry_GddHaeHsmCmacAesVerifyContext.jobId);
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
        Cry_GddHaeHsmCmacAesVerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHsmCmacAesVerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeHsmCmacAesVerifyTb.pDataPtr = dataPtr;

      Cry_GddHaeHsmCmacAesVerifyTb.ulDataLength = dataLength;
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
** Function Name        : Cry_HaeHsmCmacAesVerifyFinish                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the HAE HSM **
**                        CMAC AES computation and store the result into      **
**                        the memory location given                           **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmCmacAesVerifyMainFunction() can finish the**
**                        computation and store the result in the memory      **
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
**                        Cry_GddHaeHsmCmacAesVerifyTb,                       **
**                        Cry_GddHaeHsmCmacAesVerifyContext                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacVerifyServiceHasCallback,                    **
**                        HSM_AesCmacFinish                                   **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmCmacAesVerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* MacPtr, uint32 MacLength, Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;
  uint8 LaaCmacAesDigest[HSM_AES128_CMAC_LEN];
  uint32 LulIndex;
  uint32 LulMacLength;
  boolean LblResult;

  LddReturnValue = E_OK;
  LulMacLength = MacLength;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaeHsmCmacAesVerifyTb.ucJobState)
  {
    Cry_GddHaeHsmCmacAesVerifyTb.ucJobState = JOB_FINISH;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      (void)memset((void*)&LaaCmacAesDigest, 0x00, sizeof(LaaCmacAesDigest));

      LddReturnValue = HSM_AesCmacFinish(
        &Cry_GddHaeHsmCmacAesVerifyContext, LaaCmacAesDigest);

      if (LddReturnValue == E_OK)
      {
        if (LulMacLength > HSM_AES128_CMAC_LEN * CSM_EIGHT)
        {
          LulMacLength = HSM_AES128_CMAC_LEN * CSM_EIGHT;
        }

        LblResult = CSM_TRUE;
        /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "The length is checked" */
        for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength / CSM_EIGHT); LulIndex++)
        {
          /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          if (MacPtr[LulIndex] != LaaCmacAesDigest[LulIndex])
          {
            LblResult = CSM_FALSE;
            break;
          }
        }
        if ((LblResult == CSM_TRUE)
          && ((LulMacLength % CSM_EIGHT) > CSM_ZERO) )
        {
          for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength % CSM_EIGHT); LulIndex++)
          {
            /* polyspace +3 MISRA-C3:D4.14 RTE:IDP [Justified:Low] "The pointer is checked" */
	          /* polyspace +3 RTE:OBAI [Justified:Low] "No Impact of this rule violation" */
	          /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
            if ((MacPtr[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE)))
              != (LaaCmacAesDigest[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE))))
            {
              LblResult = CSM_FALSE;
              break;
            }
          }
        }

        if (LblResult == CSM_TRUE)
        {
          /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
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
        HSM_HaeGetErrorCode();
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeHsmCmacAesVerifyTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaeHsmCmacAesVerifyTb.pMacPtr = MacPtr;
      Cry_GddHaeHsmCmacAesVerifyTb.ulMacLength = MacLength;
      Cry_GddHaeHsmCmacAesVerifyTb.pResultPtr = resultPtr;
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
** Function Name        : Cry_HaeHsmCmacAesVerifyMainFunction                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_MacVerifyCallbackNotification() with the        **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_HaeHsmCmacAesVerifyStart() or                   **
**                        Cry_HaeHsmCmacAesVerifyUpdate(). For                **
**                        Cry_HaeHsmCmacAesVerifyFinish invocation of         **
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
**                        Cry_GddHaeHsmCmacAesVerifyTb,                       **
**                        Cry_GddHaeHsmCmacAesVerifyContext,                  **
**                        Cry_GusHaeHsmCmacAesVerifyKeyNum                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        HSM_AesCmacStart, HSM_AesCmacUpdate, HSM_WaitResp,   **
**                        HSM_AesCmacFinish,                                  **
**                        Csm_MacVerifyCallbackNotification,                  **
**                        Csm_MacVerifyServiceFinishNotification              **
*******************************************************************************/
void Cry_HaeHsmCmacAesVerifyMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  uint16 LusKeyNum;
  uint32 LulTimeout;
  uint32 LulRemainingLength;
  uint32 LulTxLength;
  const uint8* LpData;
  uint8 LaaCmacAesDigest[HSM_AES128_CMAC_LEN];
  uint32 LulIndex;
  uint32 LulMacLength;
  boolean LblResult;
  uint32 LulTextIndex;

  LddReturnValue = E_OK;
  LulTextIndex = CSM_ZERO;

  switch (Cry_GddHaeHsmCmacAesVerifyTb.ucJobState)
  {
  case JOB_START:
    LusKeyNum = CSM_ZERO;
    /* polyspace +11 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +10 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddHaeHsmCmacAesVerifyTb.pKeyPtr->length == CSM_ONE)
    {
      LusKeyNum = Cry_GddHaeHsmCmacAesVerifyTb.pKeyPtr->data[CSM_ZERO];
    }
    else if (Cry_GddHaeHsmCmacAesVerifyTb.pKeyPtr->length == CSM_TWO)
    {
      LusKeyNum = Cry_GddHaeHsmCmacAesVerifyTb.pKeyPtr->data[CSM_ZERO];
      /* polyspace +1 MISRA-C3:10.6,10.7,12.2 [Justified:Low] "No Impact of this rule violation" */
      LusKeyNum |= (Cry_GddHaeHsmCmacAesVerifyTb.pKeyPtr->data[CSM_ONE]) << 8;
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GusHaeHsmCmacAesVerifyKeyNum = LusKeyNum;

      Cry_GddHaeHsmCmacAesVerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHsmCmacAesVerifyTb.ucJobState = NO_JOB;
    }

    Csm_MacVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    /* polyspace +4 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +3 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    LddReturnValue = HSM_AesCmacStart(&Cry_GddHaeHsmCmacAesVerifyContext,
      Cry_GddHaeHsmCmacAesVerifyTb.pKeyPtr->data[CSM_ZERO],
      Cry_GddHaeHsmCmacAesVerifyTb.ulDataLength);

    if (LddReturnValue == E_OK)
    {
      LddReturnValue = E_NOT_OK;

      LulRemainingLength = Cry_GddHaeHsmCmacAesVerifyTb.ulDataLength;
      LpData = Cry_GddHaeHsmCmacAesVerifyTb.pDataPtr;

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
	      /* polyspace +2 MISRA-C3:11.8 [Justified:Low] "No Impact of this rule violation" */
        LddReturnValue = HSM_AesCmacUpdate(&Cry_GddHaeHsmCmacAesVerifyContext,
          &LpData[LulTextIndex], LulTxLength);

        if (LddReturnValue == E_OK)
        {
          LulTimeout = CSM_ZERO;
          do
          {
            LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmCmacAesVerifyContext.jobId);
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
            (void)HSM_CancelJob(Cry_GddHaeHsmCmacAesVerifyContext.jobId);
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
      Cry_GddHaeHsmCmacAesVerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHsmCmacAesVerifyTb.ucJobState = NO_JOB;
    }

    Csm_MacVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    (void)memset((void*)&LaaCmacAesDigest, 0x00, sizeof(LaaCmacAesDigest));

    LddReturnValue = HSM_AesCmacFinish(
      &Cry_GddHaeHsmCmacAesVerifyContext, LaaCmacAesDigest);

    if (LddReturnValue == E_OK)
    {
      LulMacLength = Cry_GddHaeHsmCmacAesVerifyTb.ulMacLength;
      LpData = Cry_GddHaeHsmCmacAesVerifyTb.pMacPtr;

      if (LulMacLength > HSM_AES128_CMAC_LEN * CSM_EIGHT)
      {
        LulMacLength = HSM_AES128_CMAC_LEN * CSM_EIGHT;
      }

      LblResult = CSM_TRUE;
      for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength / CSM_EIGHT); LulIndex++)
      {
	/* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
	/* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
        if (LpData[LulIndex] != LaaCmacAesDigest[LulIndex])
        {
          LblResult = CSM_FALSE;
          break;
        }
      }
      if ((LblResult == CSM_TRUE)
        && ((LulMacLength % CSM_EIGHT) > CSM_ZERO) )
      {
        for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength % CSM_EIGHT); LulIndex++)
        {
	  /* polyspace +4 RTE:OBAI [Justified:Low] "No Impact of this rule violation" */
	  /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
	  /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
          if ((LpData[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE)))
            != (LaaCmacAesDigest[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE))))
          {
            LblResult = CSM_FALSE;
            break;
          }
        }
      }
      /* polyspace +9 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
      /* polyspace +8 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
      if (LblResult == CSM_TRUE)
      {
        *(Cry_GddHaeHsmCmacAesVerifyTb.pResultPtr) = CSM_E_VER_OK;
      }
      else
      {
        *(Cry_GddHaeHsmCmacAesVerifyTb.pResultPtr) = CSM_E_VER_NOT_OK;
      }
    }
    else
    {
      LddReturnValue = E_NOT_OK;
      HSM_HaeGetErrorCode();
    }

    Cry_GddHaeHsmCmacAesVerifyTb.ucJobState = NO_JOB;

    Csm_MacVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    Csm_MacVerifyServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_MAC_HAEHSMCMACAESVERIFY == STD_ON) */
#endif /* (CSM_MAC_VERIFY_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
