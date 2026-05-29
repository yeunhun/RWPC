/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeHsmAesEcbEncrypt.c                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Autoever AES - ECB Encrypt Interface    **
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
** 1.0.0     3-Apr-2020    JaeHyun      Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for Autoever AES ECB */
#include "Cry_HaeHsmAesEcbEncrypt.h"
/* Symmetric Interface */
#if (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON)
#if (CSM_SYMBLOCK_HAEHSMAESECBENCRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "HSM_Hae.h"
#include "Hsm_HostAPI.h"
#include "CryptoService_Aes.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HaeAesEcbEncrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Stores encryption key pointer in Autoever AES ECB */
  const Csm_SymKeyType* pKeyPtr;
  /* Stores plain data pointer used for encryption in Autoever AES ECB */
  const uint8* pPlainTextPtr;
  /* Data length of the plain data used for encryption */
  uint32 ulPlainTextLength;
  /* Stores ciphered data pointer used for encryption in Autoever AES ECB */
  uint8* pCipherTextPtr;
  /* Pointer of ciphered data length */
  uint32* pCipherTextLengthPtr;
} Cry_HaeHsmAesEcbEncryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define CSM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"

static uint16 Cry_GusHaeHsmAesEcbEncryptKeyNum;

#define CSM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* AES primitive library context */
static HSMAPI_CTX_t Cry_GddHaeHsmAesEcbEncryptContext;

/* Global structure variable for Autoever AES ECB transfer buffer */
static Cry_HaeHsmAesEcbEncryptTransferBuffer Cry_GddHaeHsmAesEcbEncryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeHsmAesEcbEncryptInit                              **
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
** Remarks            : Global Variable(s):  Cry_GddHaeHsmAesEcbEncryptTb        **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeHsmAesEcbEncryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeHsmAesEcbEncryptTb.ucJobState = NO_JOB;
  Cry_GddHaeHsmAesEcbEncryptTb.pKeyPtr = NULL_PTR;
  Cry_GddHaeHsmAesEcbEncryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddHaeHsmAesEcbEncryptTb.ulPlainTextLength = CSM_ZERO;
  Cry_GddHaeHsmAesEcbEncryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddHaeHsmAesEcbEncryptTb.pCipherTextLengthPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddHaeHsmAesEcbEncryptContext, 0x00, sizeof(HSMAPI_CTX_t));

  Cry_GusHaeHsmAesEcbEncryptKeyNum = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_HaeHsmAesEcbEncryptStart                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Autoever AES ECB, so that AES is able **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeHsmAesEcbEncryptMainFunction() can process      **
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
**                        Cry_GddHaeHsmAesEcbEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_HaeHsmAesEcbEncryptInit, Hmg_AesSetKey             **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmAesEcbEncryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  uint16 LusKeyNum;
  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddHaeHsmAesEcbEncryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_HaeHsmAesEcbEncryptInit();

    Cry_GddHaeHsmAesEcbEncryptTb.ucJobState = JOB_START;

    if (Csm_SymBlockEncryptServiceHasCallback() == FALSE)
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
          Cry_GusHaeHsmAesEcbEncryptKeyNum = LusKeyNum;
          Cry_GddHaeHsmAesEcbEncryptTb.ucJobState = JOB_DONE;
        }
        else
        {
          Cry_GddHaeHsmAesEcbEncryptTb.ucJobState = NO_JOB;
        }

    }
    else
    {
      Cry_GddHaeHsmAesEcbEncryptTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_HaeHsmAesEcbEncryptUpdate                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the AES      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmAesEcbEncryptMainFunction() can process the  **
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
**                        Cry_GddHaeHsmAesEcbEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_AesEcbDec                                       **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmAesEcbEncryptUpdate(Csm_ConfigIdType cfgId,
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
  if (JOB_DONE == Cry_GddHaeHsmAesEcbEncryptTb.ucJobState)
  {
    Cry_GddHaeHsmAesEcbEncryptTb.ucJobState = JOB_UPDATE;

    if (Csm_SymBlockEncryptServiceHasCallback() == FALSE)
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

        LddReturnValue = HSM_AesEncStart(&Cry_GddHaeHsmAesEcbEncryptContext,
            HSM_AES_ECB_MODE, Cry_GusHaeHsmAesEcbEncryptKeyNum, NULL_PTR);

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
            LddReturnValue = HSM_AesEncUpdate(&Cry_GddHaeHsmAesEcbEncryptContext,
              &LpPlainText[LulTextIndex], LulTxLength);

            if (LddReturnValue == E_OK)
            {
              LulTimeout = CSM_ZERO;
              do
              {
                LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmAesEcbEncryptContext.jobId);
                LulTimeout++;
              } while ((LddReturnValue == HSM_E_WAIT) && (LulTimeout < CRYPTOLIB_HAE_HSM_TIMEOUT));

              if (LddReturnValue == E_OK)
              {
                /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
                if (HSM_ReadRxBuff(Cry_GddHaeHsmAesEcbEncryptContext.jobId,LulTxLength,&LpCipherText[LulTextIndex]) != E_OK)
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
                (void)HSM_CancelJob(Cry_GddHaeHsmAesEcbEncryptContext.jobId);
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
        Cry_GddHaeHsmAesEcbEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHsmAesEcbEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeHsmAesEcbEncryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddHaeHsmAesEcbEncryptTb.ulPlainTextLength = plainTextLength;
      Cry_GddHaeHsmAesEcbEncryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddHaeHsmAesEcbEncryptTb.pCipherTextLengthPtr = cipherTextLengthPtr;
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
** Function Name        : Cry_HaeHsmAesEcbEncryptFinish                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the AES     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmAesEcbEncryptMainFunction() can finish the   **
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
**                        Cry_GddHaeHsmAesEcbEncryptTb                           **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmAesEcbEncryptFinish(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddHaeHsmAesEcbEncryptTb.ucJobState)
  {
    Cry_GddHaeHsmAesEcbEncryptTb.ucJobState = JOB_FINISH;

    if (Csm_SymBlockEncryptServiceHasCallback() == FALSE)
    {
      LddReturnValue = HSM_AesEncFinish(&Cry_GddHaeHsmAesEcbEncryptContext);

      if (LddReturnValue != E_OK)
      {
        LddReturnValue = E_NOT_OK;
        HSM_HaeGetErrorCode();
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeHsmAesEcbEncryptTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_HaeHsmAesEcbEncryptMainFunction                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SymBlockEncryptCallbackNotification() with the       **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by Cry_HaeHsmAesEcbEncryptStart()   **
**                        or Cry_HaeHsmAesEcbEncryptUpdate(). For                **
**                        Cry_HaeHsmAesEcbEncryptFinish invocation of            **
**                        Csm_SymBlockEncryptCallbackNotification()                **
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
**                        Cry_GddHaeHsmAesEcbEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_AesSetKey,                                      **
**                        Hmg_AesEcbDec,                                      **
**                        Csm_SymBlockEncryptCallbackNotification,                 **
**                        Csm_SymBlockEncryptServiceFinishNotification             **
*******************************************************************************/
void Cry_HaeHsmAesEcbEncryptMainFunction(void)
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

  switch (Cry_GddHaeHsmAesEcbEncryptTb.ucJobState)
  {
  case JOB_START:
   LusKeyNum = CSM_ZERO;

    /* polyspace +11 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +10 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddHaeHsmAesEcbEncryptTb.pKeyPtr->length == CSM_ONE)
    {
      LusKeyNum = Cry_GddHaeHsmAesEcbEncryptTb.pKeyPtr->data[CSM_ZERO];
    }
    else if (Cry_GddHaeHsmAesEcbEncryptTb.pKeyPtr->length == CSM_TWO)
    {
      LusKeyNum = Cry_GddHaeHsmAesEcbEncryptTb.pKeyPtr->data[CSM_ZERO];
      /* polyspace +1 MISRA-C3:10.6,10.7,12.2 [Justified:Low] "No Impact of this rule violation" */
      LusKeyNum |= (Cry_GddHaeHsmAesEcbEncryptTb.pKeyPtr->data[CSM_ONE]) << 8;
    }
   else
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GusHaeHsmAesEcbEncryptKeyNum = LusKeyNum;
      Cry_GddHaeHsmAesEcbEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHsmAesEcbEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymBlockEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LpPlainText = Cry_GddHaeHsmAesEcbEncryptTb.pPlainTextPtr;
    LpCipherText = Cry_GddHaeHsmAesEcbEncryptTb.pCipherTextPtr;
    LulTextIndex = CSM_ZERO;

    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (*(Cry_GddHaeHsmAesEcbEncryptTb.pCipherTextLengthPtr) < Cry_GddHaeHsmAesEcbEncryptTb.ulPlainTextLength)
    {
      /* Buffer size is invalid */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if ((Cry_GddHaeHsmAesEcbEncryptTb.ulPlainTextLength < HSM_AES128_KEY_LEN)
    || ((Cry_GddHaeHsmAesEcbEncryptTb.ulPlainTextLength % HSM_AES128_KEY_LEN) != CSM_ZERO))
    {
      /* cipherTextLength should be multiples of 16 */
      LddReturnValue = E_NOT_OK;
    }
    if (LddReturnValue == E_OK)
	  {

  		LddReturnValue = HSM_AesEncStart(&Cry_GddHaeHsmAesEcbEncryptContext,
  			HSM_AES_ECB_MODE, Cry_GusHaeHsmAesEcbEncryptKeyNum, NULL_PTR);

  		if (LddReturnValue == E_OK)
  		{
        LddReturnValue = E_NOT_OK;
        LulRemainingLength = Cry_GddHaeHsmAesEcbEncryptTb.ulPlainTextLength;

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

    			LddReturnValue = HSM_AesEncUpdate(&Cry_GddHaeHsmAesEcbEncryptContext,
    			  &LpPlainText[LulTextIndex], LulTxLength);

    			if (LddReturnValue == E_OK)
    			{
    			  LulTimeout = CSM_ZERO;
    			  do
    			  {
      				LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmAesEcbEncryptContext.jobId);
      				LulTimeout++;
    			  } while ((LddReturnValue == HSM_E_WAIT) && (LulTimeout < CRYPTOLIB_HAE_HSM_TIMEOUT));

    			  if (LddReturnValue == E_OK)
    			  {
      				if (HSM_ReadRxBuff(Cry_GddHaeHsmAesEcbEncryptContext.jobId,LulTxLength,&LpCipherText[LulTextIndex]) != E_OK)
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
      				(void)HSM_CancelJob(Cry_GddHaeHsmAesEcbEncryptContext.jobId);
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
      Cry_GddHaeHsmAesEcbEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHsmAesEcbEncryptTb.ucJobState = NO_JOB;
    }

    Csm_SymBlockEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:

    LddReturnValue = HSM_AesEncFinish(&Cry_GddHaeHsmAesEcbEncryptContext);

    if (LddReturnValue != E_OK)
    {
       LddReturnValue = E_NOT_OK;
       HSM_HaeGetErrorCode();
    }


    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaeHsmAesEcbEncryptTb.ucJobState = NO_JOB;
    Csm_SymBlockEncryptCallbackNotification(LddReturnValue);
    break;


  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_SymBlockEncryptServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_SYM_BLOCK_HAEHSMAESECBENCRYPT == STD_ON) */
#endif /* (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

