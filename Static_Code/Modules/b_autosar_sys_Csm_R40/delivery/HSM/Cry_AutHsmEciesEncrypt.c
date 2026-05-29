/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmEciesEncrypt.c                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HSM ECIES Encrypt Interface             **
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
** 1.0.3     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.2     17-Apr-2018   Sinil        Redmine #12350 ,#12351                **
** 1.0.1     13-Nov-2017   Sinil        Redmine #10574                        **
** 1.0.0     18-Apr-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for HSM ECIES */
#include "Cry_AutHsmEciesEncrypt.h"
/* Asymmetric Interface */
#if (CSM_ASYM_ENCRYPT_STATUS == STD_ON)
#if (CSM_ASYM_AUTHSMECIESENCRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "Hsm_AutIntDriver.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HsmEciesEncrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_AsymPublicKeyType* pPublicKeyPtr;
  const uint8* pPlainTextPtr;
  uint32 ulPlainTextLength;
  uint8* pCipherTextPtr;
  uint32* pCipherTextLengthPtr;
} Cry_AutHsmEciesEncryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Hsm_DataType Cry_GddAutHsmEciesEncPrivateADataType;
static Hsm_DataType Cry_GddAutHsmEciesEncPublicADataType;
static Hsm_DataType Cry_GddAutHsmEciesEncPublicBDataType;

static Hsm_DataIDType Cry_GddAutHsmEciesEncPrivateADataIDType;
static Hsm_DataIDType Cry_GddAutHsmEciesEncPublicADataIDType;
static Hsm_DataIDType Cry_GddAutHsmEciesEncPublicBDataIDType;

/* Global structure variable for HSM ECIES transfer buffer */
static Cry_AutHsmEciesEncryptTransferBuffer Cry_GddAutHsmEciesEncryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/
static void Cry_AutHsmEciesEncryptCallback(Hsm_ErrType ddRet);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutHsmEciesEncryptInit                            **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the ECIES module.            **
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
** Remarks            : Global Variable(s):                                   **
**                      Cry_GddAutHsmEciesEncryptTb                           **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutHsmEciesEncryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutHsmEciesEncryptTb.ucJobState = NO_JOB;
  Cry_GddAutHsmEciesEncryptTb.pPublicKeyPtr = NULL_PTR;
  Cry_GddAutHsmEciesEncryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddAutHsmEciesEncryptTb.ulPlainTextLength = CSM_ZERO;
  Cry_GddAutHsmEciesEncryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddAutHsmEciesEncryptTb.pCipherTextLengthPtr = NULL_PTR;

  Cry_GddAutHsmEciesEncPrivateADataType = HSM_DATA_INVALID_KEY;
  Cry_GddAutHsmEciesEncPublicADataType = HSM_DATA_INVALID_KEY;
  Cry_GddAutHsmEciesEncPublicBDataType = HSM_DATA_INVALID_KEY;

  Cry_GddAutHsmEciesEncPrivateADataIDType = CSM_ZERO;
  Cry_GddAutHsmEciesEncPublicADataIDType = CSM_ZERO;
  Cry_GddAutHsmEciesEncPublicBDataIDType = CSM_ZERO;

}

/*******************************************************************************
** Function Name        : Cry_AutHsmEciesEncryptStart                         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM ECIES, so that ECIES is able     **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutHsmEciesEncryptMainFunction() can process    **
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
**                        Cry_GddAutHsmEciesEncryptTb                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutHsmEciesEncryptInit                          **
*******************************************************************************/
Std_ReturnType Cry_AutHsmEciesEncryptStart(const void* cfgPtr,
  const Csm_AsymPublicKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;
  const Csm_AutHsmEciesEncryptKeyType* LpEncryptKey;
  const uint8* pLength;
  const uint8* pPrivateKeyA;
  const uint8* pPublicKeyA;
  const uint8* pPublicKeyB;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutHsmEciesEncryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutHsmEciesEncryptInit();

    /* Set the job state to JOB_START */
    Cry_GddAutHsmEciesEncryptTb.ucJobState = JOB_START;

    LblAsync = Csm_AsymEncryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length <= ((HSM_ECC_KEY_BYTE_SIZE * CSM_FIVE) + CSM_FOUR))
      {
        /* polyspace +1 MISRA-C3:11.3 [Justified:Low] "No Impact of this rule violation" */
        LpEncryptKey = (const Csm_AutHsmEciesEncryptKeyType*)(keyPtr->data);

        pLength = LpEncryptKey->length;
        pPrivateKeyA = LpEncryptKey->privateKeyA;
        pPublicKeyA = LpEncryptKey->publicKeyA;
        pPublicKeyB = LpEncryptKey->publicKeyB;

        if (pLength[CSM_ZERO] == CSM_ONE)
        {
          #if (CRYPTOLIB_SUPPORT_HSM_SPC58X_IAU == STD_ON)
          if (pPrivateKeyA[CSM_ZERO] == HSM_DATA_CUSTOM_IAU_KEY)
          {
            Cry_GddAutHsmEciesEncPrivateADataType = HSM_DATA_CUSTOM_IAU_PRIVATE_KEY;
            Cry_GddAutHsmEciesEncPrivateADataIDType = (Hsm_DataIDType)HSM_DATA_CUSTOM_IAU_KEY;
          }
          else
          #endif
          {
            Cry_GddAutHsmEciesEncPrivateADataType = HSM_DATA_ECC_PRIVATE_KEY;
            Cry_GddAutHsmEciesEncPrivateADataIDType = (Hsm_DataIDType)(pPrivateKeyA[CSM_ZERO]);
          }
          LddErr = HSM_NO_ERROR;
        }
        else if (pLength[CSM_ZERO] == HSM_ECC_KEY_BYTE_SIZE)
        {
          Cry_GddAutHsmEciesEncPrivateADataType = HSM_DATA_ECC_RAM_PRIVATE_KEY;
          Cry_GddAutHsmEciesEncPrivateADataIDType = CSM_ZERO;

          LddErr = Hsm_LoadRamKey(HSM_DATA_ECC_RAM_PRIVATE_KEY, CSM_ZERO,
            pLength[CSM_ZERO], pPrivateKeyA);
        }
        else
        {
          LddErr = HSM_KEY_INVALID_ERROR;
        }

        if (LddErr == HSM_NO_ERROR)
        {
          if (pLength[CSM_ONE] == CSM_ONE)
          {
            #if (CRYPTOLIB_SUPPORT_HSM_SPC58X_IAU == STD_ON)
            if (pPublicKeyA[CSM_ZERO] == HSM_DATA_CUSTOM_IAU_KEY)
            {
              Cry_GddAutHsmEciesEncPublicADataType = HSM_DATA_CUSTOM_IAU_PUBLIC_KEY;
              Cry_GddAutHsmEciesEncPublicADataIDType = (Hsm_DataIDType)HSM_DATA_CUSTOM_IAU_KEY;
            }
            else
            #endif
            {
              Cry_GddAutHsmEciesEncPublicADataType = HSM_DATA_ECC_PUBLIC_KEY;
              Cry_GddAutHsmEciesEncPublicADataIDType = (Hsm_DataIDType)(pPublicKeyA[CSM_ZERO]);
            }
            LddErr = HSM_NO_ERROR;
          }
          else if (pLength[CSM_ONE] == (HSM_ECC_KEY_BYTE_SIZE * CSM_TWO))
          {
            Cry_GddAutHsmEciesEncPublicADataType = HSM_DATA_ECC_RAM_PUBLIC_KEY;
            Cry_GddAutHsmEciesEncPublicADataIDType = CSM_ZERO;

            LddErr = Hsm_LoadRamKey(HSM_DATA_ECC_RAM_PUBLIC_KEY, CSM_ZERO,
              pLength[CSM_ONE], pPublicKeyA);
          }
          else
          {
            LddErr = HSM_KEY_INVALID_ERROR;
          }
        }

        if (LddErr == HSM_NO_ERROR)
        {
          if (pLength[CSM_TWO] == CSM_ONE)
          {
            Cry_GddAutHsmEciesEncPublicBDataType = HSM_DATA_ECC_PUBLIC_KEY;
            Cry_GddAutHsmEciesEncPublicBDataIDType = (Hsm_DataIDType)(pPublicKeyB[CSM_ZERO]);
            LddErr = HSM_NO_ERROR;
          }
          else if (pLength[CSM_TWO] == (HSM_ECC_KEY_BYTE_SIZE * CSM_TWO))
          {
            Cry_GddAutHsmEciesEncPublicBDataType = HSM_DATA_ECC_RAM_PUBLIC_KEY;
            Cry_GddAutHsmEciesEncPublicBDataIDType = CSM_ONE;

            LddErr = Hsm_LoadRamKey(HSM_DATA_ECC_RAM_PUBLIC_KEY, CSM_ONE,
              pLength[CSM_TWO], pPublicKeyB);
          }
          else
          {
            LddErr = HSM_KEY_INVALID_ERROR;
          }
        }
      }
      else
      {
        LddErr = HSM_KEY_INVALID_ERROR;
      }

      if (LddErr == HSM_NO_ERROR)
      {
        LddErr = Hsm_EciesEncInit(LblAsync, NULL_PTR,
          Cry_GddAutHsmEciesEncPrivateADataType, Cry_GddAutHsmEciesEncPrivateADataIDType,
          Cry_GddAutHsmEciesEncPublicADataType, Cry_GddAutHsmEciesEncPublicADataIDType,
          Cry_GddAutHsmEciesEncPublicBDataType, Cry_GddAutHsmEciesEncPublicBDataIDType);
      }

      if (LddErr == HSM_NO_ERROR)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmEciesEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmEciesEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmEciesEncryptTb.pPublicKeyPtr = keyPtr;
    }
  }
  else
  {
    /* Other job is still processing, return CSM_E_BUSY */
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmEciesEncryptUpdate                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the ECIES    **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmEciesEncryptMainFunction() can process the**
**                        input                                               **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, plainTextPtr, plainTextLength                **
**                                                                            **
** InOut parameter      : cipherTextLengthPtr                                 **
**                                                                            **
** Output Parameters    : cipherTextPtr                                       **
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
**                        Cry_GddAutHsmEciesEncryptTb                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        HsmEcies_ModExp                                     **
*******************************************************************************/
Std_ReturnType Cry_AutHsmEciesEncryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* plainTextPtr, uint32 plainTextLength, uint8* cipherTextPtr,
  uint32* cipherTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;
  const Csm_AutHsmEciesEncryptDataType* LpEncryptData;
  Csm_AutHsmEciesPduType* LpPdu;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);
  CSM_PARAM_UNUSED(plainTextLength);
  CSM_PARAM_UNUSED_PTR(cipherTextLengthPtr);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutHsmEciesEncryptTb.ucJobState)
  {
    /* Set the job state to JOB_UPDATE */
    Cry_GddAutHsmEciesEncryptTb.ucJobState = JOB_UPDATE;

    LblAsync = Csm_AsymEncryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +2 MISRA-C3:11.3 [Justified:Low] "No Impact of this rule violation" */
      LpEncryptData = (const Csm_AutHsmEciesEncryptDataType*)plainTextPtr;
      LpPdu = (Csm_AutHsmEciesPduType*)cipherTextPtr;
      /* polyspace +3 MISRA-C3:18.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
      /* polyspace +4 MISRA-C3:11.8 MISRA-C3:D4.14 [Justified:Low] "No Impact of this rule violation" */
      LddErr = Hsm_EciesEncUpdate(LblAsync, NULL_PTR,
        (uint8*)(LpEncryptData->pMessage), LpEncryptData->ulMessageLength,
        (uint8*)(LpEncryptData->pParam1), LpEncryptData->ucEncMode,
        (void*)LpPdu);

      if (LddErr == HSM_NO_ERROR)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmEciesEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmEciesEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmEciesEncryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddAutHsmEciesEncryptTb.ulPlainTextLength = plainTextLength;
      Cry_GddAutHsmEciesEncryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddAutHsmEciesEncryptTb.pCipherTextLengthPtr = cipherTextLengthPtr;
    }
  }
  else
  {
    /* Job process still not complete, return CSM_E_BUSY */
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmEciesEncryptFinish                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the ECIES   **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmEciesEncryptMainFunction() can finish the **
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
**                        Cry_GddAutHsmEciesEncryptTb                         **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
Std_ReturnType Cry_AutHsmEciesEncryptFinish(Csm_ConfigIdType cfgId,
  uint8* cipherTextPtr, uint32* cipherTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);
  CSM_PARAM_UNUSED_PTR(cipherTextPtr);
  CSM_PARAM_UNUSED_PTR(cipherTextLengthPtr);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutHsmEciesEncryptTb.ucJobState)
  {
    /* Set the job state to JOB_FINISH */
    Cry_GddAutHsmEciesEncryptTb.ucJobState = JOB_FINISH;

    LblAsync = Csm_AsymEncryptServiceHasCallback();

    if (LblAsync == FALSE)
    {
      LddErr = Hsm_EciesEncFinish(LblAsync, NULL_PTR);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }

      /* reset the state back to NO_JOB */
      Cry_GddAutHsmEciesEncryptTb.ucJobState = NO_JOB;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmEciesEncryptCallback                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : TBD                                                 **
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
**                        Cry_GddAutHsmEciesEncryptTb                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_AsymEncryptCallbackNotification,                **
**                        Csm_AsymEncryptServiceFinishNotification            **
*******************************************************************************/
static void Cry_AutHsmEciesEncryptCallback(Hsm_ErrType ddRet)
{
  Std_ReturnType LddReturnValue;

  if (ddRet == HSM_BUSY)
  {
    LddReturnValue = CSM_E_BUSY;

    Csm_AsymEncryptCallbackNotification(LddReturnValue);
  }
  else
  {
    LddReturnValue = E_OK;

    switch (Cry_GddAutHsmEciesEncryptTb.ucJobState)
    {
    case JOB_START:
    case JOB_UPDATE:
      if (ddRet == HSM_NO_ERROR)
      {
        Cry_GddAutHsmEciesEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* task failure move job state to NO_JOB */
        Cry_GddAutHsmEciesEncryptTb.ucJobState = NO_JOB;
      }
      Csm_AsymEncryptCallbackNotification(LddReturnValue);
      break;

    case JOB_FINISH:
      if (ddRet != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
      Cry_GddAutHsmEciesEncryptTb.ucJobState = NO_JOB;
      Csm_AsymEncryptCallbackNotification(LddReturnValue);
      break;

    default:
      Csm_AsymEncryptServiceFinishNotification();
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : Cry_AutHsmEciesEncryptMainFunction                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_AsymEncryptCallbackNotification() with the      **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by Cry_AutHsmEciesEncryptStart() **
**                        or Cry_AutHsmEciesEncryptUpdate(). For              **
**                        Cry_AutHsmEciesEncryptFinish invocation of          **
**                        Csm_AsymEncryptCallbackNotification()               **
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
**                        Cry_GddAutHsmEciesEncryptTb                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_AsymEncryptCallbackNotification,                **
**                        AutHsmEcies_ModExp, EscCallback_setFunction,        **
**                        Csm_AsymEncryptServiceFinishNotification            **
*******************************************************************************/
void Cry_AutHsmEciesEncryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  Hsm_CallbackPtr LpCallback;
  const Csm_AutHsmEciesEncryptKeyType* LpEncryptKey;
  const uint8* pLength;
  const uint8* pPrivateKeyA;
  const uint8* pPublicKeyA;
  const uint8* pPublicKeyB;
  const Csm_AutHsmEciesEncryptDataType* LpEncryptData;
  Csm_AutHsmEciesPduType* LpPdu;

  LpCallback = &Cry_AutHsmEciesEncryptCallback;

  switch (Cry_GddAutHsmEciesEncryptTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +6 MISRA-C3:11.3,18.1,D4.1 [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddAutHsmEciesEncryptTb.pPublicKeyPtr->length
      <= ((HSM_ECC_KEY_BYTE_SIZE * CSM_FIVE) + CSM_FOUR))
    {
      LpEncryptKey = (const Csm_AutHsmEciesEncryptKeyType*)
        (Cry_GddAutHsmEciesEncryptTb.pPublicKeyPtr->data);

      pLength = LpEncryptKey->length;
      pPrivateKeyA = LpEncryptKey->privateKeyA;
      pPublicKeyA = LpEncryptKey->publicKeyA;
      pPublicKeyB = LpEncryptKey->publicKeyB;

      if (pLength[CSM_ZERO] == CSM_ONE)
      {
        #if (CRYPTOLIB_SUPPORT_HSM_SPC58X_IAU == STD_ON)
        if (pPrivateKeyA[CSM_ZERO] == HSM_DATA_CUSTOM_IAU_KEY)
        {
          Cry_GddAutHsmEciesEncPrivateADataType = HSM_DATA_CUSTOM_IAU_PRIVATE_KEY;
          Cry_GddAutHsmEciesEncPrivateADataIDType = (Hsm_DataIDType)HSM_DATA_CUSTOM_IAU_KEY;
        }
        else
        #endif
        {
          Cry_GddAutHsmEciesEncPrivateADataType = HSM_DATA_ECC_PRIVATE_KEY;
          Cry_GddAutHsmEciesEncPrivateADataIDType = (Hsm_DataIDType)(pPrivateKeyA[CSM_ZERO]);
        }
        LddErr = HSM_NO_ERROR;
      }
      else if (pLength[CSM_ZERO] == HSM_ECC_KEY_BYTE_SIZE)
      {
        Cry_GddAutHsmEciesEncPrivateADataType = HSM_DATA_ECC_RAM_PRIVATE_KEY;
        Cry_GddAutHsmEciesEncPrivateADataIDType = CSM_ZERO;

        LddErr = Hsm_LoadRamKey(HSM_DATA_ECC_RAM_PRIVATE_KEY, CSM_ZERO,
          pLength[CSM_ZERO], pPrivateKeyA);
      }
      else
      {
        LddErr = HSM_KEY_INVALID_ERROR;
      }

      if (LddErr == HSM_NO_ERROR)
      {
        if (pLength[CSM_ONE] == CSM_ONE)
        {
          #if (CRYPTOLIB_SUPPORT_HSM_SPC58X_IAU == STD_ON)
          if (pPublicKeyA[CSM_ZERO] == HSM_DATA_CUSTOM_IAU_KEY)
          {
            Cry_GddAutHsmEciesEncPublicADataType = HSM_DATA_CUSTOM_IAU_PUBLIC_KEY;
            Cry_GddAutHsmEciesEncPublicADataIDType = (Hsm_DataIDType)HSM_DATA_CUSTOM_IAU_KEY;
          }
          else
          #endif
          {
            Cry_GddAutHsmEciesEncPublicADataType = HSM_DATA_ECC_PUBLIC_KEY;
            Cry_GddAutHsmEciesEncPublicADataIDType = (Hsm_DataIDType)(pPublicKeyA[CSM_ZERO]);
          }
          LddErr = HSM_NO_ERROR;
        }
        else if (pLength[CSM_ONE] == (HSM_ECC_KEY_BYTE_SIZE * CSM_TWO))
        {
          Cry_GddAutHsmEciesEncPublicADataType = HSM_DATA_ECC_RAM_PUBLIC_KEY;
          Cry_GddAutHsmEciesEncPublicADataIDType = CSM_ZERO;

          LddErr = Hsm_LoadRamKey(HSM_DATA_ECC_RAM_PUBLIC_KEY, CSM_ZERO,
            pLength[CSM_ONE], pPublicKeyA);
        }
        else
        {
          LddErr = HSM_KEY_INVALID_ERROR;
        }
      }

      if (LddErr == HSM_NO_ERROR)
      {
        if (pLength[CSM_TWO] == CSM_ONE)
        {
          Cry_GddAutHsmEciesEncPublicBDataType = HSM_DATA_ECC_PUBLIC_KEY;
          Cry_GddAutHsmEciesEncPublicBDataIDType = (Hsm_DataIDType)(pPublicKeyB[CSM_ZERO]);
          LddErr = HSM_NO_ERROR;
        }
        else if (pLength[CSM_TWO] == (HSM_ECC_KEY_BYTE_SIZE * CSM_TWO))
        {
          Cry_GddAutHsmEciesEncPublicBDataType = HSM_DATA_ECC_RAM_PUBLIC_KEY;
          Cry_GddAutHsmEciesEncPublicBDataIDType = CSM_ONE;

          LddErr = Hsm_LoadRamKey(HSM_DATA_ECC_RAM_PUBLIC_KEY, CSM_ONE,
            pLength[CSM_TWO], pPublicKeyB);
        }
        else
        {
          LddErr = HSM_KEY_INVALID_ERROR;
        }
      }
    }
    else
    {
      LddErr = HSM_KEY_INVALID_ERROR;
    }

    if (LddErr == HSM_NO_ERROR)
    {
      LddErr = Hsm_EciesEncInit(CSM_TRUE, LpCallback,
        Cry_GddAutHsmEciesEncPrivateADataType, Cry_GddAutHsmEciesEncPrivateADataIDType,
        Cry_GddAutHsmEciesEncPublicADataType, Cry_GddAutHsmEciesEncPublicADataIDType,
        Cry_GddAutHsmEciesEncPublicBDataType, Cry_GddAutHsmEciesEncPublicBDataIDType);
    }

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmEciesEncryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_AsymEncryptCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_UPDATE:
    /* polyspace +3 MISRA-C3:11.3,11.8 [Justified:Low] "No Impact of this rule violation" */
    LpEncryptData = (const Csm_AutHsmEciesEncryptDataType*)
      Cry_GddAutHsmEciesEncryptTb.pPlainTextPtr;
    LpPdu = (Csm_AutHsmEciesPduType*)Cry_GddAutHsmEciesEncryptTb.pCipherTextPtr;

    /* polyspace-begin MISRA-C3:18.1,11.8,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    LddErr = Hsm_EciesEncUpdate(CSM_TRUE, LpCallback,
      (uint8*)(LpEncryptData->pMessage), LpEncryptData->ulMessageLength,
      (uint8*)(LpEncryptData->pParam1), LpEncryptData->ucEncMode,
      (void*)LpPdu);
    /* polyspace-end MISRA-C3:18.1,11.8,D4.1 RTE:IDP */

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmEciesEncryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_AsymEncryptCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_FINISH:
    LddErr = Hsm_EciesEncFinish(CSM_TRUE, LpCallback);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      /* reset the state back to NO_JOB */
      Cry_GddAutHsmEciesEncryptTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_AsymEncryptCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_AsymEncryptServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_ASYM_AUTHSMECIESENCRYPT == STD_ON) */
#endif /* (CSM_ASYM_ENCRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
