/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeHsmAesCbcEncrypt.c                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Autoever AES - CBC Encrypt Interface    **
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
** 1.0.0     20-Mar-2020   JaeHyun      Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:5.1  [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for Autoever AES CBC */
#include "Cry_HaeHsmAesCbcEncrypt.h"
/* Symmetric Interface */
#if (CSM_SYM_ENCRYPT_STATUS == STD_ON)
#if (CSM_SYM_HAEHSMAESCBCENCRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "HSM_Hae.h"
#include "Hsm_HostAPI.h"
#include "CryptoService_Aes.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HaeAesCbcEncrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Stores encryption key pointer in Autoever AES CBC */
  const Csm_SymKeyType* pKeyPtr;
  /* Stores plain data pointer used for encryption in Autoever AES CBC */
  const uint8* pPlainTextPtr;
  /* Data length of the plain data used for encryption */
  uint32 ulPlainTextLength;
  const uint8* pInitVectorPtr;
  uint32 ulInitVectorLength;
  /* Stores ciphered data pointer used for encryption in Autoever AES CBC */
  uint8* pCipherTextPtr;
  /* Pointer of ciphered data length */
  uint32* pCipherTextLengthPtr;
} Cry_HaeHsmAesCbcEncryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

static uint8 Cry_GaaHaeHsmAesCbcEncryptIV[HSM_AES128_KEY_LEN];

#define CSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"

static uint16 Cry_GusHaeHsmAesCbcEncryptKeyNum;

#define CSM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* AES primitive library context */
static HSMAPI_CTX_t Cry_GddHaeHsmAesCbcEncryptContext;

/* Global structure variable for Autoever AES CBC transfer buffer */
static Cry_HaeHsmAesCbcEncryptTransferBuffer Cry_GddHaeHsmAesCbcEncryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeHsmAesCbcEncryptInit                              **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the AES module.              **
**                      All the Global variables will be initialized after    **
**                      the successful completion of this API.                **
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
** Remarks            : Global Variable(s):  Cry_GddHaeHsmAesCbcEncryptTb        **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeHsmAesCbcEncryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeHsmAesCbcEncryptTb.ucJobState = NO_JOB;
  Cry_GddHaeHsmAesCbcEncryptTb.pKeyPtr = NULL_PTR;
  Cry_GddHaeHsmAesCbcEncryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddHaeHsmAesCbcEncryptTb.ulPlainTextLength = CSM_ZERO;
  Cry_GddHaeHsmAesCbcEncryptTb.pInitVectorPtr = NULL_PTR;
  Cry_GddHaeHsmAesCbcEncryptTb.ulInitVectorLength = CSM_ZERO;
  Cry_GddHaeHsmAesCbcEncryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddHaeHsmAesCbcEncryptTb.pCipherTextLengthPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddHaeHsmAesCbcEncryptContext, 0x00, sizeof(HSMAPI_CTX_t));
  (void)memset((void*)&Cry_GaaHaeHsmAesCbcEncryptIV, 0x00, sizeof(Cry_GaaHaeHsmAesCbcEncryptIV));

  Cry_GusHaeHsmAesCbcEncryptKeyNum = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_HaeHsmAesCbcEncryptStart                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Autoever AES CBC, so that AES is able **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeHsmAesCbcEncryptMainFunction() can process      **
**                        initialisation                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgPtr, keyPtr, InitVectorPtr, InitVectorLength     **
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
**                        Cry_GddHaeHsmAesCbcEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_HaeHsmAesCbcEncryptInit, Hmg_AesSetKey             **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmAesCbcEncryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr, const uint8* InitVectorPtr,
  uint32 InitVectorLength)
{
  Std_ReturnType LddReturnValue;
  uint16 LusKeyNum;
  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddHaeHsmAesCbcEncryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_HaeHsmAesCbcEncryptInit();

    Cry_GddHaeHsmAesCbcEncryptTb.ucJobState = JOB_START;

    if (Csm_SymEncryptServiceHasCallback() == FALSE)
    {
      if (InitVectorLength != HSM_AES128_KEY_LEN)
      {
        /* The length of init vector should be 16 */
        LddReturnValue = E_NOT_OK;
      }

      else
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
          Cry_GusHaeHsmAesCbcEncryptKeyNum = LusKeyNum;
          /* polyspace +1 MISRA-C3:D4.11 RTE:STD_LIB [Justified:Low] "The input is checked" */
          (void)memcpy((void*)Cry_GaaHaeHsmAesCbcEncryptIV, \
            (const void*)InitVectorPtr, InitVectorLength);
          Cry_GddHaeHsmAesCbcEncryptTb.ucJobState = JOB_DONE;
        }
        else
        {
          Cry_GddHaeHsmAesCbcEncryptTb.ucJobState = NO_JOB;
        }
      }
    }
    else
    {
      Cry_GddHaeHsmAesCbcEncryptTb.pKeyPtr = keyPtr;
      Cry_GddHaeHsmAesCbcEncryptTb.pInitVectorPtr = InitVectorPtr;
      Cry_GddHaeHsmAesCbcEncryptTb.ulInitVectorLength = InitVectorLength;
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
** Function Name        : Cry_HaeHsmAesCbcEncryptUpdate                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the AES      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmAesCbcEncryptMainFunction() can process the  **
**                        input                                               **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, cipherTextPtr, cipherTextLength              **
**                                                                            **
** InOut parameter      : plainTextLengthPtr                                  **
**                                                                            **
** Output Parameters    : plainTextPtr                                        **
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
**                        Cry_GddHaeHsmAesCbcEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_AesCbcDec                                       **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmAesCbcEncryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* plainTextPtr, uint32 plainTextLength, uint8* cipherTextPtr,
  uint32* cipherTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  uint32 LulTimeout;
  uint32 LulTxLength;
  const uint8* LpPlainText;
  uint8* LpCipherText;
  uint32 LulTextIndex;
  uint32 LulRemainingLength;

  LpPlainText = plainTextPtr;
  LpCipherText = cipherTextPtr;
  LulTextIndex = CSM_ZERO;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddHaeHsmAesCbcEncryptTb.ucJobState)
  {
    Cry_GddHaeHsmAesCbcEncryptTb.ucJobState = JOB_UPDATE;

    if (Csm_SymEncryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*cipherTextLengthPtr < plainTextLength)
      {
        /* Buffer size is invalid */
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if ((plainTextLength < HSM_AES128_KEY_LEN)
      || ((plainTextLength % HSM_AES128_KEY_LEN) != CSM_ZERO))
      {
        /* cipherTextLength should be multiples of 16 */
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {

        LddReturnValue = HSM_AesEncStart(&Cry_GddHaeHsmAesCbcEncryptContext,
            HSM_AES_CBC_MODE, Cry_GusHaeHsmAesCbcEncryptKeyNum, Cry_GaaHaeHsmAesCbcEncryptIV);

        if (LddReturnValue == E_OK)
        {
          LddReturnValue = E_NOT_OK;

          LulRemainingLength = plainTextLength;
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
            LddReturnValue = HSM_AesEncUpdate(&Cry_GddHaeHsmAesCbcEncryptContext,
              &LpPlainText[LulTextIndex], LulTxLength);

            if (LddReturnValue == E_OK)
            {
              LulTimeout = CSM_ZERO;
              do
              {
                LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmAesCbcEncryptContext.jobId);
                LulTimeout++;
              } while ((LddReturnValue == HSM_E_WAIT) && (LulTimeout < CRYPTOLIB_HAE_HSM_TIMEOUT));

              if (LddReturnValue == E_OK)
              {
                /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
                if (HSM_ReadRxBuff(Cry_GddHaeHsmAesCbcEncryptContext.jobId,LulTxLength,&LpCipherText[LulTextIndex]) != E_OK)
                {
                  LddReturnValue = E_NOT_OK;
                }
                else
                {
                  LulRemainingLength -= LulTxLength;
                  LulTextIndex += LulTxLength;
                }
              }
              else
              {
                LulRemainingLength = CSM_ZERO;
                (void)HSM_CancelJob(Cry_GddHaeHsmAesCbcEncryptContext.jobId);
              }
            }
            else
            {
              LulRemainingLength = CSM_ZERO;
            }
          }
        }
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue != E_OK)
      {
        LddReturnValue = E_NOT_OK;
        HSM_HaeGetErrorCode();
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeHsmAesCbcEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHsmAesCbcEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeHsmAesCbcEncryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddHaeHsmAesCbcEncryptTb.ulPlainTextLength = plainTextLength;
      Cry_GddHaeHsmAesCbcEncryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddHaeHsmAesCbcEncryptTb.pCipherTextLengthPtr = cipherTextLengthPtr;
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
** Function Name        : Cry_HaeHsmAesCbcEncryptFinish                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the AES     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmAesCbcEncryptMainFunction() can finish the   **
**                        computation and store the result in the memory      **
**                        location given                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                                                                            **
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddHaeHsmAesCbcEncryptTb                           **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmAesCbcEncryptFinish(Csm_ConfigIdType cfgId,
  uint8* cipherTextPtr, uint32* cipherTextLengthPtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);
  CSM_PARAM_UNUSED_PTR(cipherTextPtr);
  CSM_PARAM_UNUSED_PTR(cipherTextLengthPtr);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddHaeHsmAesCbcEncryptTb.ucJobState)
  {
    Cry_GddHaeHsmAesCbcEncryptTb.ucJobState = JOB_FINISH;

    if (Csm_SymEncryptServiceHasCallback() == FALSE)
    {
      LddReturnValue = HSM_AesEncFinish(&Cry_GddHaeHsmAesCbcEncryptContext);

      if (LddReturnValue != E_OK)
      {
        LddReturnValue = E_NOT_OK;
        HSM_HaeGetErrorCode();
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeHsmAesCbcEncryptTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_HaeHsmAesCbcEncryptMainFunction                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SymEncryptCallbackNotification() with the       **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by Cry_HaeHsmAesCbcEncryptStart()   **
**                        or Cry_HaeHsmAesCbcEncryptUpdate(). For                **
**                        Cry_HaeHsmAesCbcEncryptFinish invocation of            **
**                        Csm_SymEncryptCallbackNotification()                **
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
**                        Cry_GddHaeHsmAesCbcEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_AesSetKey,                                      **
**                        Hmg_AesCbcDec,                                      **
**                        Csm_SymEncryptCallbackNotification,                 **
**                        Csm_SymEncryptServiceFinishNotification             **
*******************************************************************************/
void Cry_HaeHsmAesCbcEncryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  uint16 LusKeyNum;
  uint32 LulTimeout;
  uint32 LulTxLength;
  const uint8* LpPlainText;
  uint8* LpCipherText;
  uint32 LulTextIndex;
  uint32 LulRemainingLength;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddHaeHsmAesCbcEncryptTb.ucJobState)
  {
  case JOB_START:
   LusKeyNum = CSM_ZERO;
    /* polyspace +11 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +10 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddHaeHsmAesCbcEncryptTb.pKeyPtr->length == CSM_ONE)
    {
      LusKeyNum = Cry_GddHaeHsmAesCbcEncryptTb.pKeyPtr->data[CSM_ZERO];
    }
    else if (Cry_GddHaeHsmAesCbcEncryptTb.pKeyPtr->length == CSM_TWO)
    {
      LusKeyNum = Cry_GddHaeHsmAesCbcEncryptTb.pKeyPtr->data[CSM_ZERO];
      /* polyspace +1 MISRA-C3:10.6,10.7,12.2 [Justified:Low] "No Impact of this rule violation" */
      LusKeyNum |= (Cry_GddHaeHsmAesCbcEncryptTb.pKeyPtr->data[CSM_ONE]) << 8;
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GusHaeHsmAesCbcEncryptKeyNum = LusKeyNum;
      Cry_GddHaeHsmAesCbcEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHsmAesCbcEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:

    LpPlainText = Cry_GddHaeHsmAesCbcEncryptTb.pPlainTextPtr;
    LpCipherText = Cry_GddHaeHsmAesCbcEncryptTb.pCipherTextPtr;
    LulTextIndex = CSM_ZERO;

    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (*(Cry_GddHaeHsmAesCbcEncryptTb.pCipherTextLengthPtr) < Cry_GddHaeHsmAesCbcEncryptTb.ulPlainTextLength)
    {
      /* Buffer size is invalid */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if ((Cry_GddHaeHsmAesCbcEncryptTb.ulPlainTextLength < HSM_AES128_KEY_LEN)
    || ((Cry_GddHaeHsmAesCbcEncryptTb.ulPlainTextLength % HSM_AES128_KEY_LEN) != CSM_ZERO))
    {
      /* cipherTextLength should be multiples of 16 */
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {

      LddReturnValue = HSM_AesEncStart(&Cry_GddHaeHsmAesCbcEncryptContext,
         HSM_AES_CBC_MODE, Cry_GusHaeHsmAesCbcEncryptKeyNum, Cry_GaaHaeHsmAesCbcEncryptIV);

      if (LddReturnValue == E_OK)
      {
        LddReturnValue = E_NOT_OK;
        LulRemainingLength = Cry_GddHaeHsmAesCbcEncryptTb.ulPlainTextLength;

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

          LddReturnValue = HSM_AesEncUpdate(&Cry_GddHaeHsmAesCbcEncryptContext,
            &LpPlainText[LulTextIndex], LulTxLength);

          if (LddReturnValue == E_OK)
          {
            LulTimeout = CSM_ZERO;
            do
            {
              LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmAesCbcEncryptContext.jobId);
              LulTimeout++;
            } while ((LddReturnValue == HSM_E_WAIT) && (LulTimeout < CRYPTOLIB_HAE_HSM_TIMEOUT));

            if (LddReturnValue == E_OK)
            {
              if (HSM_ReadRxBuff(Cry_GddHaeHsmAesCbcEncryptContext.jobId,LulTxLength,&LpCipherText[LulTextIndex]) != E_OK)
              {
                LddReturnValue = E_NOT_OK;
              }
              else
              {
                LulRemainingLength -= LulTxLength;
                LulTextIndex += LulTxLength;
              }
            }
            else
            {
              LulRemainingLength = CSM_ZERO;
              (void)HSM_CancelJob(Cry_GddHaeHsmAesCbcEncryptContext.jobId);
            }
          }
          else
          {
            LulRemainingLength = CSM_ZERO;
          }
        }
      }
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue != E_OK)
    {
      LddReturnValue = E_NOT_OK;
      HSM_HaeGetErrorCode();
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeHsmAesCbcEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHsmAesCbcEncryptTb.ucJobState = NO_JOB;
    }

    Csm_SymEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:

    LddReturnValue = HSM_AesEncFinish(&Cry_GddHaeHsmAesCbcEncryptContext);

    if (LddReturnValue != E_OK)
    {
       LddReturnValue = E_NOT_OK;
       HSM_HaeGetErrorCode();
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaeHsmAesCbcEncryptTb.ucJobState = NO_JOB;
    Csm_SymEncryptCallbackNotification(LddReturnValue);
    break;


  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_SymEncryptServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_SYM_HAEHSMAESCBCENCRYPT == STD_ON) */
#endif /* (CSM_SYM_ENCRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

