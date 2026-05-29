/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutCsecCommon.c                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Interface                               **
**                - CSEC Common                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 2.6.3.0   24-Mar-2021   TamTV6       Redmine #18165                        **
** 1.0.0     27-May-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Cry_AutCsecCommon.h"
#if ((CSM_RANDOM_SEED_STATUS == STD_ON) && (CSM_RANDOM_AUTCSECRANDOMSEED == STD_ON)) \
  || ((CSM_RANDOM_GENERATE_STATUS == STD_ON) && (CSM_RANDOM_AUTCSECRANDOMGENERATE == STD_ON)) \
  || ((CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON) && (CSM_SYMBLOCK_AUTCSECAESECBENCRYPT == STD_ON)) \
  || ((CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON) && (CSM_SYMBLOCK_AUTCSECAESECBDECRYPT == STD_ON)) \
  || ((CSM_SYM_ENCRYPT_STATUS == STD_ON) && (CSM_SYM_AUTCSECAESCBCENCRYPT == STD_ON)) \
  || ((CSM_SYM_DECRYPT_STATUS == STD_ON) && (CSM_SYM_AUTCSECAESCBCDECRYPT == STD_ON)) \
  || ((CSM_MAC_GENERATE_STATUS == STD_ON) && (CSM_MAC_AUTCSECCMACAESGENERATE == STD_ON)) \
  || ((CSM_MAC_VERIFY_STATUS == STD_ON) && (CSM_MAC_AUTCSECCMACAESVERIFY == STD_ON))
#include "Csm_Cbk.h"
#include "Csec_Driver.h"
#include "string.h"

#if (CRYPTOLIB_SUPORT_HSM_CSEC == STD_ON)
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if (CSM_RANDOM_AUTCSECRANDOMSEED == STD_ON)
/* Cry AutCsecRandom Seed Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const uint8* pSeedPtr;
  uint32 ulSeedLength;
} Cry_AutCsecRandomSeedTransferBuffer;
#endif

#if (CSM_RANDOM_AUTCSECRANDOMGENERATE == STD_ON)
/* Cry AutCsecRandom Generate Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Pointer of result */
  uint8* pResultPtr;
  /* Length of result */
  uint32 ulResultLength;
} Cry_AutCsecRandomGenerateTransferBuffer;
#endif

#if (CSM_SYMBLOCK_AUTCSECAESECBENCRYPT == STD_ON)
/* Cry AutCsecAesEcbEncrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_SymKeyType* pKeyPtr;
  const uint8* pPlainTextPtr;
  uint32 ulPlainTextLength;
  uint8* pCipherTextPtr;
  uint32* pCipherTextLengthPtr;
} Cry_AutCsecAesEcbEncryptTransferBuffer;
#endif

#if (CSM_SYMBLOCK_AUTCSECAESECBDECRYPT == STD_ON)
/* Cry AutCsecAesEcbDecrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_SymKeyType* pKeyPtr;
  const uint8* pCipherTextPtr;
  uint32 ulCipherTextLength;
  uint8* pPlainTextPtr;
  uint32* pPlainTextLengthPtr;
} Cry_AutCsecAesEcbDecryptTransferBuffer;
#endif

#if (CSM_SYM_AUTCSECAESCBCENCRYPT == STD_ON)
/* Cry AutCsecAesCbcEncrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_SymKeyType* pKeyPtr;
  const uint8* pPlainTextPtr;
  uint32 ulPlainTextLength;
  const uint8* pInitVectorPtr;
  uint32 ulInitVectorDataLen;
  uint8* pCipherTextPtr;
  uint32* pCipherTextLengthPtr;
} Cry_AutCsecAesCbcEncryptTransferBuffer;
#endif

#if (CSM_SYM_AUTCSECAESCBCDECRYPT == STD_ON)
/* Cry AutCsecAesCbcDecrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_SymKeyType* pKeyPtr;
  const uint8* pCipherTextPtr;
  uint32 ulCipherTextLength;
  const uint8* pInitVectorPtr;
  uint32 InitVectorLength;
  uint8* pPlainTextPtr;
  uint32* pPlainTextLengthPtr;
} Cry_AutCsecAesCbcDecryptTransferBuffer;
#endif

#if (CSM_MAC_AUTCSECCMACAESGENERATE == STD_ON)
/* Cry AutCsecCmacAesGenerate Transfer buffer*/
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
} Cry_AutCsecCmacAesGenerateTransferBuffer;
#endif

#if (CSM_MAC_AUTCSECCMACAESVERIFY == STD_ON)
/* Cry AutCsecCmacAesVerify Transfer buffer*/
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
} Cry_AutCsecCmacAesVerifyTransferBuffer;
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (CSM_RANDOM_AUTCSECRANDOMSEED == STD_ON)
/* Structure variable for AutCsecRandom Seed transfer buffer */
static Cry_AutCsecRandomSeedTransferBuffer Cry_GddAutCsecRandomSeedTb;
#endif

#if (CSM_RANDOM_AUTCSECRANDOMGENERATE == STD_ON)
/* Structure variable for AutCsecRandom Generate transfer buffer */
static Cry_AutCsecRandomGenerateTransferBuffer Cry_GddAutCsecRandomGenerateTb;
#endif

#if (CSM_SYMBLOCK_AUTCSECAESECBENCRYPT == STD_ON)
static Csec_KeyIDType Cry_GddAutCsecAesEcbEncKeyId;

/* Global structure variable for CSEC AES ECB transfer buffer */
static Cry_AutCsecAesEcbEncryptTransferBuffer Cry_GddAutCsecAesEcbEncryptTb;
#endif

#if (CSM_SYMBLOCK_AUTCSECAESECBDECRYPT == STD_ON)
static Csec_KeyIDType Cry_GddAutCsecAesEcbDecKeyId;

/* Global structure variable for CSEC AES ECB transfer buffer */
static Cry_AutCsecAesEcbDecryptTransferBuffer Cry_GddAutCsecAesEcbDecryptTb;
#endif

#if (CSM_SYM_AUTCSECAESCBCENCRYPT == STD_ON)
static Csec_KeyIDType Cry_GddAutCsecAesCbcEncKeyId;

/* Global structure variable for CSEC AES CBC transfer buffer */
static Cry_AutCsecAesCbcEncryptTransferBuffer Cry_GddAutCsecAesCbcEncryptTb;
#endif

#if (CSM_SYM_AUTCSECAESCBCDECRYPT == STD_ON)
static Csec_KeyIDType Cry_GddAutCsecAesCbcDecKeyId;

/* Global structure variable for CSEC AES CBC transfer buffer */
static Cry_AutCsecAesCbcDecryptTransferBuffer Cry_GddAutCsecAesCbcDecryptTb;
#endif

#if (CSM_MAC_AUTCSECCMACAESGENERATE == STD_ON)
static Csec_KeyIDType Cry_GddAutCsecCmacAesGenKeyId;

/* Global variable for CSEC CMAC AES transfer buffer structure */
static Cry_AutCsecCmacAesGenerateTransferBuffer Cry_GddAutCsecCmacAesGenerateTb;
#endif

#if (CSM_MAC_AUTCSECCMACAESVERIFY == STD_ON)
static Csec_KeyIDType Cry_GddAutCsecCmacAesVerKeyId;

/* Global variable for CSEC CMAC AES transfer buffer structure */
static Cry_AutCsecCmacAesVerifyTransferBuffer Cry_GddAutCsecCmacAesVerifyTb;
#endif

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

#if (CSM_SYM_AUTCSECAESCBCENCRYPT == STD_ON)
static uint8 Cry_GaaAutCsecAesCbcEncInitVector[CSEC_BLOCK_BYTE_LENGTH];
#endif

#if (CSM_SYM_AUTCSECAESCBCDECRYPT == STD_ON)
static uint8 Cry_GaaAutCsecAesCbcDecInitVector[CSEC_BLOCK_BYTE_LENGTH];
#endif

#if (CSM_MAC_AUTCSECCMACAESGENERATE == STD_ON)
static uint8 Cry_GaaAutCsecCmacAesGenDigest[CSEC_BLOCK_BYTE_LENGTH];
#endif

#if (CSM_MAC_AUTCSECCMACAESVERIFY == STD_ON)
static uint8 Cry_GaaAutCsecCmacAesVerDigest[CSEC_BLOCK_BYTE_LENGTH];
#endif

#define CSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

void Cry_AutCsecInit(Cry_AutCsecAlgorithmType algorithm)
{
  switch (algorithm)
  {
  #if (CSM_RANDOM_AUTCSECRANDOMSEED == STD_ON)
  case CRY_AUTCSEC_RANDOMSEED:
    /* Initialize the module data variables to default values */
    Cry_GddAutCsecRandomSeedTb.ucJobState = NO_JOB;
    Cry_GddAutCsecRandomSeedTb.pSeedPtr = NULL_PTR;
    Cry_GddAutCsecRandomSeedTb.ulSeedLength = CSM_ZERO;
    break;
  #endif

  #if (CSM_RANDOM_AUTCSECRANDOMGENERATE == STD_ON)
  case CRY_AUTCSEC_RANDOMGENERATE:
    /* Initialize the module data variables to default values */
    Cry_GddAutCsecRandomGenerateTb.ucJobState = NO_JOB;
    Cry_GddAutCsecRandomGenerateTb.pResultPtr = NULL_PTR;
    Cry_GddAutCsecRandomGenerateTb.ulResultLength = CSM_ZERO;
    break;
  #endif

  #if (CSM_SYMBLOCK_AUTCSECAESECBENCRYPT == STD_ON)
  case CRY_AUTCSEC_AESECBENC:
    /* Initialize the module data variables to default values */
    Cry_GddAutCsecAesEcbEncryptTb.ucJobState = NO_JOB;
    Cry_GddAutCsecAesEcbEncryptTb.pKeyPtr = NULL_PTR;
    Cry_GddAutCsecAesEcbEncryptTb.pPlainTextPtr = NULL_PTR;
    Cry_GddAutCsecAesEcbEncryptTb.ulPlainTextLength = CSM_ZERO;
    Cry_GddAutCsecAesEcbEncryptTb.pCipherTextPtr = NULL_PTR;
    Cry_GddAutCsecAesEcbEncryptTb.pCipherTextLengthPtr = NULL_PTR;

    Cry_GddAutCsecAesEcbEncKeyId = CSEC_INVALID_KEY;
    break;
  #endif

  #if (CSM_SYMBLOCK_AUTCSECAESECBDECRYPT == STD_ON)
  case CRY_AUTCSEC_AESECBDEC:
    /* Initialize the module data variables to default values */
    Cry_GddAutCsecAesEcbDecryptTb.ucJobState = NO_JOB;
    Cry_GddAutCsecAesEcbDecryptTb.pKeyPtr = NULL_PTR;
    Cry_GddAutCsecAesEcbDecryptTb.pCipherTextPtr = NULL_PTR;
    Cry_GddAutCsecAesEcbDecryptTb.ulCipherTextLength = CSM_ZERO;
    Cry_GddAutCsecAesEcbDecryptTb.pPlainTextPtr = NULL_PTR;
    Cry_GddAutCsecAesEcbDecryptTb.pPlainTextLengthPtr = NULL_PTR;

    Cry_GddAutCsecAesEcbDecKeyId = CSEC_INVALID_KEY;
    break;
  #endif

  #if (CSM_SYM_AUTCSECAESCBCENCRYPT == STD_ON)
  case CRY_AUTCSEC_AESCBCENC:
    /* Initialize the module data variables to default values */
    Cry_GddAutCsecAesCbcEncryptTb.ucJobState = NO_JOB;
    Cry_GddAutCsecAesCbcEncryptTb.pKeyPtr = NULL_PTR;
    Cry_GddAutCsecAesCbcEncryptTb.pPlainTextPtr = NULL_PTR;
    Cry_GddAutCsecAesCbcEncryptTb.ulPlainTextLength = CSM_ZERO;
    Cry_GddAutCsecAesCbcEncryptTb.pInitVectorPtr = NULL_PTR;
    Cry_GddAutCsecAesCbcEncryptTb.ulInitVectorDataLen = CSM_ZERO;
    Cry_GddAutCsecAesCbcEncryptTb.pCipherTextPtr = NULL_PTR;
    Cry_GddAutCsecAesCbcEncryptTb.pCipherTextLengthPtr = NULL_PTR;

    (void)memset((void*)Cry_GaaAutCsecAesCbcEncInitVector, 0x00, CSEC_BLOCK_BYTE_LENGTH);

    Cry_GddAutCsecAesCbcEncKeyId = CSEC_INVALID_KEY;
    break;
  #endif

  #if (CSM_SYM_AUTCSECAESCBCDECRYPT == STD_ON)
  case CRY_AUTCSEC_AESCBCDEC:
    /* Initialize the module data variables to default values */
    Cry_GddAutCsecAesCbcDecryptTb.ucJobState = NO_JOB;
    Cry_GddAutCsecAesCbcDecryptTb.pKeyPtr = NULL_PTR;
    Cry_GddAutCsecAesCbcDecryptTb.pCipherTextPtr = NULL_PTR;
    Cry_GddAutCsecAesCbcDecryptTb.ulCipherTextLength = CSM_ZERO;
    Cry_GddAutCsecAesCbcDecryptTb.pInitVectorPtr = NULL_PTR;
    Cry_GddAutCsecAesCbcDecryptTb.InitVectorLength = CSM_ZERO;
    Cry_GddAutCsecAesCbcDecryptTb.pPlainTextPtr = NULL_PTR;
    Cry_GddAutCsecAesCbcDecryptTb.pPlainTextLengthPtr = NULL_PTR;

    (void)memset((void*)Cry_GaaAutCsecAesCbcDecInitVector, 0x00, CSEC_BLOCK_BYTE_LENGTH);

    Cry_GddAutCsecAesCbcDecKeyId = CSEC_INVALID_KEY;
    break;
  #endif

  #if (CSM_MAC_AUTCSECCMACAESGENERATE == STD_ON)
  case CRY_AUTCSEC_CMACAESGEN:
    /* Initialize the module data variables to default values */
    Cry_GddAutCsecCmacAesGenerateTb.ucJobState = NO_JOB;
    Cry_GddAutCsecCmacAesGenerateTb.pKeyPtr = NULL_PTR;
    Cry_GddAutCsecCmacAesGenerateTb.pDataPtr = NULL_PTR;
    Cry_GddAutCsecCmacAesGenerateTb.ulDataLength = CSM_ZERO;
    Cry_GddAutCsecCmacAesGenerateTb.pResultPtr = NULL_PTR;
    Cry_GddAutCsecCmacAesGenerateTb.pResultLengthPtr = NULL_PTR;
    Cry_GddAutCsecCmacAesGenerateTb.blTruncationIsAllowed = CSM_FALSE;

    (void)memset((void*)Cry_GaaAutCsecCmacAesGenDigest, 0x00, CSEC_BLOCK_BYTE_LENGTH);

    Cry_GddAutCsecCmacAesGenKeyId = CSEC_INVALID_KEY;
    break;
  #endif

  #if (CSM_MAC_AUTCSECCMACAESVERIFY == STD_ON)
  case CRY_AUTCSEC_CMACASEVER:
    /* Initialize the module data variables to default values */
    Cry_GddAutCsecCmacAesVerifyTb.ucJobState = NO_JOB;
    Cry_GddAutCsecCmacAesVerifyTb.pKeyPtr = NULL_PTR;
    Cry_GddAutCsecCmacAesVerifyTb.pDataPtr = NULL_PTR;
    Cry_GddAutCsecCmacAesVerifyTb.ulDataLength = CSM_ZERO;
    Cry_GddAutCsecCmacAesVerifyTb.pMacPtr = NULL_PTR;
    Cry_GddAutCsecCmacAesVerifyTb.ulMacLength = CSM_ZERO;
    Cry_GddAutCsecCmacAesVerifyTb.pResultPtr = NULL_PTR;

    (void)memset((void*)Cry_GaaAutCsecCmacAesVerDigest, 0x00, CSEC_BLOCK_BYTE_LENGTH);

    Cry_GddAutCsecCmacAesVerKeyId = CSEC_INVALID_KEY;
    break;
  #endif
  /* polyspace +1 RTE:UNR [Justified:Low] "No Impact of this rule violation " */
  default:
    /* Do nothing */
    break;
  }
}

#if (CSM_RANDOM_AUTCSECRANDOMSEED == STD_ON)
/*******************************************************************************
** Function Name        : Cry_AutCsecRandomSeedStart                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Autron Random Seed, so that it is    **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        configuration provided in the arguments so that     **
**                        Cry_AutCsecRandomSeedMainFunction() can process     **
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
** Remarks              : Global Variable(s): Cry_GddAutCsecRandomSeedTb      **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Cry_AutCsecRandomSeedInit, Csec_InitRnd,            **
**                        Csm_RandomSeedServiceHasCallback                    **
*******************************************************************************/
Std_ReturnType Cry_AutCsecRandomSeedStart(const void* cfgPtr)
{
  Std_ReturnType LddReturnValue;
  Csec_ErrType LddErr;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddAutCsecRandomSeedTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutCsecInit(CRY_AUTCSEC_RANDOMSEED);

    Cry_GddAutCsecRandomSeedTb.ucJobState = JOB_START;

    if (Csm_RandomSeedServiceHasCallback() == FALSE)
    {
      LddErr = Csec_InitRnd();

      if (LddErr != CSEC_ERC_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutCsecRandomSeedTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutCsecRandomSeedTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_AutCsecRandomSeedUpdate                         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Autron   **
**                        Random Seed                                         **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutCsecRandomSeedMainFunction() can process     **
**                        input data                                          **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, seedPtr, seedLength                          **
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
** Remarks              : Global Variable(s): Cry_GddAutCsecRandomSeedTb      **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_RandomSeedServiceHasCallback, Csec_ExtendSeed   **
*******************************************************************************/
Std_ReturnType Cry_AutCsecRandomSeedUpdate(Csm_ConfigIdType cfgId,
  const uint8* seedPtr, uint32 seedLength)
{
  Std_ReturnType LddReturnValue;
  Csec_ErrType LddErr;

  /* Setting the default return value */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutCsecRandomSeedTb.ucJobState)
  {
    Cry_GddAutCsecRandomSeedTb.ucJobState = JOB_UPDATE;

    if (Csm_RandomSeedServiceHasCallback() == FALSE)
    {
      if (seedLength != CSEC_BLOCK_BYTE_LENGTH)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LddErr = Csec_ExtendSeed(seedPtr);

        if (LddErr != CSEC_ERC_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutCsecRandomSeedTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutCsecRandomSeedTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutCsecRandomSeedTb.pSeedPtr = seedPtr;
      Cry_GddAutCsecRandomSeedTb.ulSeedLength = seedLength;
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
** Function Name        : Cry_AutCsecRandomSeedFinish                         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function will not be doing any computation.    **
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
**                        CSM_E_BUSY: service state is already "active"       **
**                                                                            **
** Preconditions        : Primitive should have been successfully initialized **
**                                                                            **
** Remarks              : Global Variable(s): Cry_GddAutCsecRandomSeedTb      **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Csm_RandomSeedServiceHasCallback                    **
*******************************************************************************/
Std_ReturnType Cry_AutCsecRandomSeedFinish(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutCsecRandomSeedTb.ucJobState)
  {
    Cry_GddAutCsecRandomSeedTb.ucJobState = JOB_FINISH;

    if (Csm_RandomSeedServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutCsecRandomSeedTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_AutCsecRandomSeedMainFunction                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_RandomSeedCallbackNotification() with correct   **
**                        return value once the main function has completely  **
**                        processed the cryptographic                         **
**                        functions demanded by Cry_AutCsecRandomSeedStart()  **
**                        or Cry_AutCsecRandomSeedUpdate(). For               **
**                        Cry_AutCsecRandomSeedFinish invocation of           **
**                        Csm_RandomSeedCallbackNotification()                **
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
** Preconditions        : Primitive should have been initialized              **
**                                                                            **
** Remarks              : Global Variable(s): Cry_GddAutCsecRandomSeedTb      **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Csm_RandomSeedCallbackNotification,                 **
**                        Csec_InitRnd, Csec_ExtendSeed                       **
**                        Csm_RandomSeedServiceFinishNotification             **
*******************************************************************************/
void Cry_AutCsecRandomSeedMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Csec_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* State machine of AutCsecRandom job processing */
  switch (Cry_GddAutCsecRandomSeedTb.ucJobState)
  {
  case JOB_START:
    LddErr = Csec_InitRnd();

    if (LddErr != CSEC_ERC_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutCsecRandomSeedTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutCsecRandomSeedTb.ucJobState = NO_JOB;
    }

    /* Callback notification will be invoking the application callback */
    Csm_RandomSeedCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    if (Cry_GddAutCsecRandomSeedTb.ulSeedLength != CSEC_BLOCK_BYTE_LENGTH)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LddErr = Csec_ExtendSeed(Cry_GddAutCsecRandomSeedTb.pSeedPtr);

      if (LddErr != CSEC_ERC_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutCsecRandomSeedTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutCsecRandomSeedTb.ucJobState = NO_JOB;
    }

    /* Callback notification will be invoking the application callback */
    Csm_RandomSeedCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddAutCsecRandomSeedTb.ucJobState = NO_JOB;

    /* Callback notification will be invoking the application callback */
    Csm_RandomSeedCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_RandomSeedServiceFinishNotification();
    break;
  }
}
#endif

#if (CSM_RANDOM_AUTCSECRANDOMGENERATE == STD_ON)
/*******************************************************************************
** Function Name        : Cry_AutCsecRandomGenerate                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function processes the cryptographic primitive **
**                        with the given input data and store the result in   **
**                        the memory location given.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : cfgPtr, resultLength                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : resultPtr                                           **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy   **
**                        of random number generator is exhausted             **
**                                                                            **
** Preconditions        : Seed should have been generated                     **
**                                                                            **
** Remarks              : Global Variable(s): None                            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutCsecRandomGenerateInit,                      **
**                        Csm_RandomGenerateServiceHasCallback, Csec_Rnd      **
*******************************************************************************/
Std_ReturnType Cry_AutCsecRandomGenerate(const void* cfgPtr, uint8* resultPtr,
  uint32 resultLength)
{
  Std_ReturnType LddReturnValue;
  uint32 LulIndex, LulBufferIndex, LulRemainLength, LulCopyBytes;
  uint8 LaaRnd[CSEC_BLOCK_BYTE_LENGTH];
  Csec_ErrType LddErr;

  /* Setting Default return value */
  LddReturnValue = E_OK;
  (void)memset((void*)LaaRnd, 0x00, CSEC_BLOCK_BYTE_LENGTH);

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddAutCsecRandomGenerateTb.ucJobState)
  {
    Cry_AutCsecInit(CRY_AUTCSEC_RANDOMGENERATE);

    Cry_GddAutCsecRandomGenerateTb.ucJobState = JOB_START;

    if (Csm_RandomGenerateServiceHasCallback() == FALSE)
    {
      LulBufferIndex = CSM_ZERO;
      LulRemainLength = resultLength;
      do
      {
        LddErr = Csec_Rnd(LaaRnd);

        if (LddErr == CSEC_ERC_NO_ERROR)
        {
          if (LulRemainLength >= CSEC_BLOCK_BYTE_LENGTH)
          {
            LulCopyBytes = CSEC_BLOCK_BYTE_LENGTH;
          }
          else
          {
            LulCopyBytes = LulRemainLength;
          }
          /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "The array length is checked" */
          for (LulIndex = CSM_ZERO; LulIndex < LulCopyBytes; LulIndex++)
          {
            /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
            resultPtr[LulBufferIndex + LulIndex] = LaaRnd[LulIndex];
          }
          LulBufferIndex = LulBufferIndex + LulCopyBytes;
          LulRemainLength = LulRemainLength - LulCopyBytes;
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      } while ((LddReturnValue == E_OK) && (LulRemainLength > CSM_ZERO));

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutCsecRandomGenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddAutCsecRandomGenerateTb.pResultPtr = resultPtr;
      Cry_GddAutCsecRandomGenerateTb.ulResultLength = resultLength;
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
** Function Name        : Cry_AutCsecRandomGenerateMainFunction               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_RandomGenerateCallbackNotification()            **
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
** Preconditions        : Primitive should have been initialized              **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        Cry_GddAutCsecRandomGenerateTb                      **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Csec_Rnd, Csm_RandomGenerateCallbackNotification
*******************************************************************************/
void Cry_AutCsecRandomGenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  uint32 LulIndex, LulBufferIndex, LulRemainLength, LulCopyBytes;;
  uint8 LaaRnd[CSEC_BLOCK_BYTE_LENGTH];
  Csec_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;
  LulBufferIndex = CSM_ZERO;
  LulRemainLength = Cry_GddAutCsecRandomGenerateTb.ulResultLength;
  (void)memset((void*)LaaRnd, 0x00, CSEC_BLOCK_BYTE_LENGTH);

  do
  {
    LddErr = Csec_Rnd(LaaRnd);

    if (LddErr == CSEC_ERC_NO_ERROR)
    {
      if (LulRemainLength >= CSEC_BLOCK_BYTE_LENGTH)
      {
        LulCopyBytes = CSEC_BLOCK_BYTE_LENGTH;
      }
      else
      {
        LulCopyBytes = LulRemainLength;
      }

      for (LulIndex = CSM_ZERO; LulIndex < LulCopyBytes; LulIndex++)
      {
        /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        Cry_GddAutCsecRandomGenerateTb.pResultPtr[LulBufferIndex + LulIndex] = LaaRnd[LulIndex];
      }
      LulBufferIndex = LulBufferIndex + LulCopyBytes;
      LulRemainLength = LulRemainLength - LulCopyBytes;
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }
  } while ((LddReturnValue == E_OK) && (LulRemainLength > CSM_ZERO));

  /* Update job state to NO_JOB irrespective of the result */
  Cry_GddAutCsecRandomGenerateTb.ucJobState = NO_JOB;

  /* Callback notification will be invoking the application callback */
  Csm_RandomGenerateCallbackNotification(LddReturnValue);
}
#endif

#if (CSM_SYMBLOCK_AUTCSECAESECBENCRYPT == STD_ON)
/*******************************************************************************
** Function Name        : Cry_AutCsecAesEcbEncryptStart                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of CSEC AES ECB, so that AES is able    **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutCsecAesEcbEncryptMainFunction() can process  **
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
**                        Cry_GddAutCsecAesEcbEncryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutCsecAesEcbEncryptInit,                       **
**                        Csm_SymBlockEncryptServiceHasCallback,              **
**                        Csec_LoadPlainKey                                   **
*******************************************************************************/
Std_ReturnType Cry_AutCsecAesEcbEncryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  Csec_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutCsecAesEcbEncryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutCsecInit(CRY_AUTCSEC_AESECBENC);

    Cry_GddAutCsecAesEcbEncryptTb.ucJobState = JOB_START;

    if (Csm_SymBlockEncryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        /* Pre-Shared Key */
        if ((((keyPtr->data[0]) >= (uint8)CSEC_KEY_1) && \
          ((keyPtr->data[0]) <= (uint8)CSEC_KEY_10)) \
          || (((keyPtr->data[0]) >= (uint8)CSEC_KEY_11) && \
            ((keyPtr->data[0]) <= (uint8)CSEC_KEY_17)))
        {
          /* polyspace +1 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
          Cry_GddAutCsecAesEcbEncKeyId = (Csec_KeyIDType)(keyPtr->data[0]);
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }
      else if (keyPtr->length == CSEC_BLOCK_BYTE_LENGTH)
      {
        /* Raw Key */
        Cry_GddAutCsecAesEcbEncKeyId = CSEC_RAM_KEY;
        LddErr = Csec_LoadPlainKey((const uint8*)((const void*)(keyPtr->data)));
        if (LddErr != CSEC_ERC_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutCsecAesEcbEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutCsecAesEcbEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutCsecAesEcbEncryptTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_AutCsecAesEcbEncryptUpdate                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the AES      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutCsecAesEcbEncryptMainFunction() can process  **
**                        the input                                           **
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
**                        Cry_GddAutCsecAesEcbEncryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymBlockEncryptServiceHasCallback, Csec_EncEcb  **
*******************************************************************************/
Std_ReturnType Cry_AutCsecAesEcbEncryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* plainTextPtr, uint32 plainTextLength, uint8* cipherTextPtr,
  uint32* cipherTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  Csec_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutCsecAesEcbEncryptTb.ucJobState)
  {
    Cry_GddAutCsecAesEcbEncryptTb.ucJobState = JOB_UPDATE;

    if (Csm_SymBlockEncryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*cipherTextLengthPtr < plainTextLength)
      {
        /* Buffer size is invalid */
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if ((plainTextLength < CSEC_BLOCK_BYTE_LENGTH)
        || ((plainTextLength % CSEC_BLOCK_BYTE_LENGTH) != CSM_ZERO))
      {
        /* plainTextLength should be multiples of 16 */
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        *cipherTextLengthPtr = CSM_ZERO;

        LddErr = Csec_EncEcb(Cry_GddAutCsecAesEcbEncKeyId,
          plainTextLength, plainTextPtr, cipherTextPtr);

        /* Verify the return value */
        if (LddErr == CSEC_ERC_NO_ERROR)
        {
          *cipherTextLengthPtr = plainTextLength;
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutCsecAesEcbEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutCsecAesEcbEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutCsecAesEcbEncryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddAutCsecAesEcbEncryptTb.ulPlainTextLength = plainTextLength;
      Cry_GddAutCsecAesEcbEncryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddAutCsecAesEcbEncryptTb.pCipherTextLengthPtr = cipherTextLengthPtr;
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
** Function Name        : Cry_AutCsecAesEcbEncryptFinish                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the AES     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutCsecAesEcbEncryptMainFunction() can finish   **
**                        the computation and store the result in the memory  **
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
**                        Cry_GddAutCsecAesEcbEncryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymBlockEncryptServiceHasCallback               **
*******************************************************************************/
Std_ReturnType Cry_AutCsecAesEcbEncryptFinish(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutCsecAesEcbEncryptTb.ucJobState)
  {
    Cry_GddAutCsecAesEcbEncKeyId = CSEC_INVALID_KEY;

    Cry_GddAutCsecAesEcbEncryptTb.ucJobState = JOB_FINISH;

    if (Csm_SymBlockEncryptServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutCsecAesEcbEncryptTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_AutCsecAesEcbEncryptMainFunction                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SymBlockEncryptCallbackNotification() with the  **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_AutCsecAesEcbEncryptStart()                     **
**                        or Cry_AutCsecAesEcbEncryptUpdate(). For            **
**                        Cry_AutCsecAesEcbEncryptFinish invocation of        **
**                        Csm_SymBlockEncryptCallbackNotification()           **
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
**                        Cry_GddAutCsecAesEcbEncryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csec_LoadPlainKey, Csec_EncEcb,                     **
**                        Csm_SymBlockEncryptCallbackNotification,            **
**                        Csm_SymBlockEncryptServiceFinishNotification        **
*******************************************************************************/
void Cry_AutCsecAesEcbEncryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Csec_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* State machine of AES job processing */
  switch (Cry_GddAutCsecAesEcbEncryptTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (Cry_GddAutCsecAesEcbEncryptTb.pKeyPtr->length == CSM_ONE)
    {
      /* Pre-Shared Key */
      if ((((Cry_GddAutCsecAesEcbEncryptTb.pKeyPtr->data[0]) >= (uint8)CSEC_KEY_1)
        && ((Cry_GddAutCsecAesEcbEncryptTb.pKeyPtr->data[0]) <= (uint8)CSEC_KEY_10))
        || (((Cry_GddAutCsecAesEcbEncryptTb.pKeyPtr->data[0]) >= (uint8)CSEC_KEY_11)
        && ((Cry_GddAutCsecAesEcbEncryptTb.pKeyPtr->data[0]) <= (uint8)CSEC_KEY_17)))
      {
        /* polyspace +2 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
        Cry_GddAutCsecAesEcbEncKeyId
          = (Csec_KeyIDType)(Cry_GddAutCsecAesEcbEncryptTb.pKeyPtr->data[0]);
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }
    else if (Cry_GddAutCsecAesEcbEncryptTb.pKeyPtr->length == CSEC_BLOCK_BYTE_LENGTH)
    {
      /* Raw Key */
      Cry_GddAutCsecAesEcbEncKeyId = CSEC_RAM_KEY;
      LddErr = Csec_LoadPlainKey(
        (const uint8*)((const void*)(Cry_GddAutCsecAesEcbEncryptTb.pKeyPtr->data)));
      if (LddErr != CSEC_ERC_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutCsecAesEcbEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutCsecAesEcbEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymBlockEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (*(Cry_GddAutCsecAesEcbEncryptTb.pCipherTextLengthPtr)
      < Cry_GddAutCsecAesEcbEncryptTb.ulPlainTextLength)
    {
      /* Buffer size is invalid */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if ((Cry_GddAutCsecAesEcbEncryptTb.ulPlainTextLength < CSEC_BLOCK_BYTE_LENGTH)
      || ((Cry_GddAutCsecAesEcbEncryptTb.ulPlainTextLength % CSEC_BLOCK_BYTE_LENGTH) != CSM_ZERO))
    {
      /* plainTextLength should be multiples of 16 */
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      *(Cry_GddAutCsecAesEcbEncryptTb.pCipherTextLengthPtr) = CSM_ZERO;

      LddErr = Csec_EncEcb(Cry_GddAutCsecAesEcbEncKeyId,
        Cry_GddAutCsecAesEcbEncryptTb.ulPlainTextLength,
        Cry_GddAutCsecAesEcbEncryptTb.pPlainTextPtr,
        Cry_GddAutCsecAesEcbEncryptTb.pCipherTextPtr);

      /* Verify the return value */
      if (LddErr == CSEC_ERC_NO_ERROR)
      {
        *(Cry_GddAutCsecAesEcbEncryptTb.pCipherTextLengthPtr)
          = Cry_GddAutCsecAesEcbEncryptTb.ulPlainTextLength;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutCsecAesEcbEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutCsecAesEcbEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymBlockEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    Cry_GddAutCsecAesEcbEncKeyId = CSEC_INVALID_KEY;

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddAutCsecAesEcbEncryptTb.ucJobState = NO_JOB;

    /* Notify respective Service about the completion of the task */
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
#endif

#if (CSM_SYMBLOCK_AUTCSECAESECBDECRYPT == STD_ON)
/*******************************************************************************
** Function Name        : Cry_AutCsecAesEcbDecryptStart                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of CSEC AES ECB, so that AES is able    **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutCsecAesEcbDecryptMainFunction() can process  **
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
**                        Cry_GddAutCsecAesEcbDecryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutCsecAesEcbDecryptInit,                       **
**                        Csm_SymBlockDecryptServiceHasCallback,              **
**                        Csec_LoadPlainKey                                   **
*******************************************************************************/
Std_ReturnType Cry_AutCsecAesEcbDecryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  Csec_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutCsecAesEcbDecryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutCsecInit(CRY_AUTCSEC_AESECBDEC);

    Cry_GddAutCsecAesEcbDecryptTb.ucJobState = JOB_START;

    if (Csm_SymBlockDecryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        /* Pre-Shared Key */
        if ((((keyPtr->data[0]) >= (uint8)CSEC_KEY_1) && \
            ((keyPtr->data[0]) <= (uint8)CSEC_KEY_10)) \
          || (((keyPtr->data[0]) >= (uint8)CSEC_KEY_11) && \
            ((keyPtr->data[0]) <= (uint8)CSEC_KEY_17)))
        {
          /* polyspace +1 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
          Cry_GddAutCsecAesEcbDecKeyId = (Csec_KeyIDType)(keyPtr->data[0]);
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }
      else if (keyPtr->length == CSEC_BLOCK_BYTE_LENGTH)
      {
        /* Raw Key */
        Cry_GddAutCsecAesEcbDecKeyId = CSEC_RAM_KEY;
        LddErr = Csec_LoadPlainKey((const uint8*)((const void*)(keyPtr->data)));
        if (LddErr != CSEC_ERC_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutCsecAesEcbDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutCsecAesEcbDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutCsecAesEcbDecryptTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_AutCsecAesEcbDecryptUpdate                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the AES      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutCsecAesEcbDecryptMainFunction() can process  **
**                        the input                                           **
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
**                        Cry_GddAutCsecAesEcbDecryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymBlockDecryptServiceHasCallback, Csec_DecEcb  **
*******************************************************************************/
Std_ReturnType Cry_AutCsecAesEcbDecryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* cipherTextPtr, uint32 cipherTextLength, uint8* plainTextPtr,
  uint32* plainTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  Csec_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutCsecAesEcbDecryptTb.ucJobState)
  {
    /* Set the job state to JOB_UPDATE */
    Cry_GddAutCsecAesEcbDecryptTb.ucJobState = JOB_UPDATE;

    if (Csm_SymBlockDecryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*plainTextLengthPtr < cipherTextLength)
      {
        /* Buffer size is invalid */
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if ((cipherTextLength < CSEC_BLOCK_BYTE_LENGTH)
        || ((cipherTextLength % CSEC_BLOCK_BYTE_LENGTH) != CSM_ZERO))
      {
        /* cipherTextLength should be multiples of 16 */
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        *plainTextLengthPtr = CSM_ZERO;

        LddErr = Csec_DecEcb(Cry_GddAutCsecAesEcbDecKeyId,
          cipherTextLength, cipherTextPtr, plainTextPtr);

        if (LddErr == CSEC_ERC_NO_ERROR)
        {
          *plainTextLengthPtr = cipherTextLength;
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutCsecAesEcbDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutCsecAesEcbDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutCsecAesEcbDecryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddAutCsecAesEcbDecryptTb.ulCipherTextLength = cipherTextLength;
      Cry_GddAutCsecAesEcbDecryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddAutCsecAesEcbDecryptTb.pPlainTextLengthPtr = plainTextLengthPtr;
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
** Function Name        : Cry_AutCsecAesEcbDecryptFinish                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the AES     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutCsecAesEcbDecryptMainFunction() can finish   **
**                        the computation and store the result in the memory  **
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
**                        Cry_GddAutCsecAesEcbDecryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymBlockDecryptServiceHasCallback               **
*******************************************************************************/
Std_ReturnType Cry_AutCsecAesEcbDecryptFinish(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutCsecAesEcbDecryptTb.ucJobState)
  {
    Cry_GddAutCsecAesEcbDecKeyId = CSEC_INVALID_KEY;

    Cry_GddAutCsecAesEcbDecryptTb.ucJobState = JOB_FINISH;

    if (Csm_SymBlockDecryptServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutCsecAesEcbDecryptTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_AutCsecAesEcbDecryptMainFunction                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SymBlockDecryptCallbackNotification() with the  **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_AutCsecAesEcbDecryptStart()                     **
**                        or Cry_AutCsecAesEcbDecryptUpdate(). For            **
**                        Cry_AutCsecAesEcbDecryptFinish invocation of        **
**                        Csm_SymBlockDecryptCallbackNotification()           **
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
**                        Cry_GddAutCsecAesEcbDecryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csec_LoadPlainKey, Csec_DecEcb,                     **
**                        Csm_SymBlockDecryptCallbackNotification,            **
**                        Csm_SymBlockDecryptServiceFinishNotification        **
*******************************************************************************/
void Cry_AutCsecAesEcbDecryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Csec_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddAutCsecAesEcbDecryptTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (Cry_GddAutCsecAesEcbDecryptTb.pKeyPtr->length == CSM_ONE)
    {
      /* Pre-Shared Key */
      if ((((Cry_GddAutCsecAesEcbDecryptTb.pKeyPtr->data[0]) >= (uint8)CSEC_KEY_1)
        && ((Cry_GddAutCsecAesEcbDecryptTb.pKeyPtr->data[0]) <= (uint8)CSEC_KEY_10))
        || (((Cry_GddAutCsecAesEcbDecryptTb.pKeyPtr->data[0]) >= (uint8)CSEC_KEY_11)
        && ((Cry_GddAutCsecAesEcbDecryptTb.pKeyPtr->data[0]) <= (uint8)CSEC_KEY_17)))
      {
        /* polyspace +2 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
        Cry_GddAutCsecAesEcbDecKeyId
          = (Csec_KeyIDType)(Cry_GddAutCsecAesEcbDecryptTb.pKeyPtr->data[0]);
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }
    else if (Cry_GddAutCsecAesEcbDecryptTb.pKeyPtr->length == CSEC_BLOCK_BYTE_LENGTH)
    {
      /* Raw Key */
      Cry_GddAutCsecAesEcbDecKeyId = CSEC_RAM_KEY;
      LddErr = Csec_LoadPlainKey(
        (const uint8*)((const void*)(Cry_GddAutCsecAesEcbDecryptTb.pKeyPtr->data)));
      if (LddErr != CSEC_ERC_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutCsecAesEcbDecryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutCsecAesEcbDecryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymBlockDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (*(Cry_GddAutCsecAesEcbDecryptTb.pPlainTextLengthPtr)
      < Cry_GddAutCsecAesEcbDecryptTb.ulCipherTextLength)
    {
      /* Buffer size is invalid */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if ((Cry_GddAutCsecAesEcbDecryptTb.ulCipherTextLength < CSEC_BLOCK_BYTE_LENGTH)
      || ((Cry_GddAutCsecAesEcbDecryptTb.ulCipherTextLength % CSEC_BLOCK_BYTE_LENGTH) != CSM_ZERO))
    {
      /* cipherTextLength should be multiples of 16 */
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      *(Cry_GddAutCsecAesEcbDecryptTb.pPlainTextLengthPtr) = CSM_ZERO;

      LddErr = Csec_DecEcb(Cry_GddAutCsecAesEcbDecKeyId,
        Cry_GddAutCsecAesEcbDecryptTb.ulCipherTextLength,
        Cry_GddAutCsecAesEcbDecryptTb.pCipherTextPtr,
        Cry_GddAutCsecAesEcbDecryptTb.pPlainTextPtr);

      /* Verify the return value */
      if (LddErr == CSEC_ERC_NO_ERROR)
      {
        *(Cry_GddAutCsecAesEcbDecryptTb.pPlainTextLengthPtr)
          = Cry_GddAutCsecAesEcbDecryptTb.ulCipherTextLength;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutCsecAesEcbDecryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutCsecAesEcbDecryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymBlockDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    Cry_GddAutCsecAesEcbDecKeyId = CSEC_INVALID_KEY;

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddAutCsecAesEcbDecryptTb.ucJobState = NO_JOB;

    /* Notify respective Service about the completion of the task */
    Csm_SymBlockDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_SymBlockDecryptServiceFinishNotification();
    break;
  }
}
#endif

#if (CSM_SYM_AUTCSECAESCBCENCRYPT == STD_ON)
/*******************************************************************************
** Function Name        : Cry_AutCsecAesCbcEncryptStart                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of CSEC AES CBC, so that AES is able    **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutCsecAesCbcEncryptMainFunction() can process  **
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
**                        Cry_GddAutCsecAesCbcEncryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutCsecAesCbcEncryptInit,                       **
**                        Csm_SymEncryptServiceHasCallback,                   **
**                        Csec_LoadPlainKey                                   **
*******************************************************************************/
Std_ReturnType Cry_AutCsecAesCbcEncryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr, const uint8* InitVectorPtr,
  uint32 InitVectorLength)
{
  Std_ReturnType LddReturnValue;
  Csec_ErrType LddErr;
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutCsecAesCbcEncryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutCsecInit(CRY_AUTCSEC_AESCBCENC);

    Cry_GddAutCsecAesCbcEncryptTb.ucJobState = JOB_START;

    if (Csm_SymEncryptServiceHasCallback() == FALSE)
    {
      if (InitVectorLength != CSEC_BLOCK_BYTE_LENGTH)
      {
        LddReturnValue = E_NOT_OK;
      }
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        /* Pre-Shared Key */
        if ((((keyPtr->data[0]) >= (uint8)CSEC_KEY_1) && \
           ((keyPtr->data[0]) <= (uint8)CSEC_KEY_10))
          || (((keyPtr->data[0]) >= (uint8)CSEC_KEY_11) && \
            ((keyPtr->data[0]) <= (uint8)CSEC_KEY_17)))
        {
          /* polyspace +1 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
          Cry_GddAutCsecAesCbcEncKeyId = (Csec_KeyIDType)(keyPtr->data[0]);
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }
      else if (keyPtr->length == CSEC_BLOCK_BYTE_LENGTH)
      {
        /* Raw Key */
        Cry_GddAutCsecAesCbcEncKeyId = CSEC_RAM_KEY;
        LddErr = Csec_LoadPlainKey((const uint8*)((const void*)(keyPtr->data)));
        if (LddErr != CSEC_ERC_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        for (LulIndex = CSM_ZERO; LulIndex < CSEC_BLOCK_BYTE_LENGTH; LulIndex++)
        {
          /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          Cry_GaaAutCsecAesCbcEncInitVector[LulIndex] = InitVectorPtr[LulIndex];
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutCsecAesCbcEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutCsecAesCbcEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutCsecAesCbcEncryptTb.pKeyPtr = keyPtr;
      Cry_GddAutCsecAesCbcEncryptTb.pInitVectorPtr = InitVectorPtr;
      Cry_GddAutCsecAesCbcEncryptTb.ulInitVectorDataLen = InitVectorLength;
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
** Function Name        : Cry_AutCsecAesCbcEncryptUpdate                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the AES      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutCsecAesCbcEncryptMainFunction() can process  **
**                        the input                                           **
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
**                        Cry_GddAutCsecAesCbcEncryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymEncryptServiceHasCallback, Csec_EncCbc       **
*******************************************************************************/
Std_ReturnType Cry_AutCsecAesCbcEncryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* plainTextPtr, uint32 plainTextLength, uint8* cipherTextPtr,
  uint32* cipherTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  Csec_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutCsecAesCbcEncryptTb.ucJobState)
  {
    Cry_GddAutCsecAesCbcEncryptTb.ucJobState = JOB_UPDATE;

    if (Csm_SymEncryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*cipherTextLengthPtr < plainTextLength)
      {
        /* Buffer size is invalid */
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if ((plainTextLength < CSEC_BLOCK_BYTE_LENGTH)
        || ((plainTextLength % CSEC_BLOCK_BYTE_LENGTH) != CSM_ZERO))
      {
        /* plainTextLength should be multiples of 16 */
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        *cipherTextLengthPtr = CSM_ZERO;

        LddErr = Csec_EncCbc(Cry_GddAutCsecAesCbcEncKeyId,
          plainTextLength, plainTextPtr, cipherTextPtr,
          Cry_GaaAutCsecAesCbcEncInitVector);

        if (LddErr == CSEC_ERC_NO_ERROR)
        {
          *cipherTextLengthPtr = plainTextLength;
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutCsecAesCbcEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutCsecAesCbcEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutCsecAesCbcEncryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddAutCsecAesCbcEncryptTb.ulPlainTextLength = plainTextLength;
      Cry_GddAutCsecAesCbcEncryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddAutCsecAesCbcEncryptTb.pCipherTextLengthPtr = cipherTextLengthPtr;
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
** Function Name        : Cry_AutCsecAesCbcEncryptFinish                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the AES     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutCsecAesCbcEncryptMainFunction() can finish   **
**                        thecomputation and store the result in the memory   **
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
**                        Cry_GddAutCsecAesCbcEncryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymEncryptServiceHasCallback                    **
*******************************************************************************/
Std_ReturnType Cry_AutCsecAesCbcEncryptFinish(Csm_ConfigIdType cfgId,
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
  if (JOB_DONE == Cry_GddAutCsecAesCbcEncryptTb.ucJobState)
  {
    Cry_GddAutCsecAesCbcEncKeyId = CSEC_INVALID_KEY;

    Cry_GddAutCsecAesCbcEncryptTb.ucJobState = JOB_FINISH;

    if (Csm_SymEncryptServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutCsecAesCbcEncryptTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_AutCsecAesCbcEncryptMainFunction                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SymEncryptCallbackNotification() with the       **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_AutCsecAesCbcEncryptStart()                     **
**                        or Cry_AutCsecAesCbcEncryptUpdate(). For            **
**                        Cry_AutCsecAesCbcEncryptFinish invocation of        **
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
**                        Cry_GddAutCsecAesCbcEncryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csec_LoadPlainKey, Csec_EncCbc,                     **
**                        Csm_SymEncryptCallbackNotification,                 **
**                        Csm_SymEncryptServiceFinishNotification             **
*******************************************************************************/
void Cry_AutCsecAesCbcEncryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Csec_ErrType LddErr;
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddAutCsecAesCbcEncryptTb.ucJobState)
  {
  case JOB_START:
    if (Cry_GddAutCsecAesCbcEncryptTb.ulInitVectorDataLen != CSEC_BLOCK_BYTE_LENGTH)
    {
      LddReturnValue = E_NOT_OK;
    }
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (Cry_GddAutCsecAesCbcEncryptTb.pKeyPtr->length == CSM_ONE)
    {
      /* Pre-Shared Key */
      if ((((Cry_GddAutCsecAesCbcEncryptTb.pKeyPtr->data[0]) >= (uint8)CSEC_KEY_1)
        && ((Cry_GddAutCsecAesCbcEncryptTb.pKeyPtr->data[0]) <= (uint8)CSEC_KEY_10))
        || (((Cry_GddAutCsecAesCbcEncryptTb.pKeyPtr->data[0]) >= (uint8)CSEC_KEY_11)
          && ((Cry_GddAutCsecAesCbcEncryptTb.pKeyPtr->data[0]) <= (uint8)CSEC_KEY_17)))
      {
        /* polyspace +2 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
        Cry_GddAutCsecAesCbcEncKeyId
          = (Csec_KeyIDType)(Cry_GddAutCsecAesCbcEncryptTb.pKeyPtr->data[0]);
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }
    else if (Cry_GddAutCsecAesCbcEncryptTb.pKeyPtr->length == CSEC_BLOCK_BYTE_LENGTH)
    {
      /* Raw Key */
      Cry_GddAutCsecAesCbcEncKeyId = CSEC_RAM_KEY;
      LddErr = Csec_LoadPlainKey(
        (const uint8*)((const void*)(Cry_GddAutCsecAesCbcEncryptTb.pKeyPtr->data)));
      if (LddErr != CSEC_ERC_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      for (LulIndex = CSM_ZERO; LulIndex < CSEC_BLOCK_BYTE_LENGTH; LulIndex++)
      {
        /* polyspace +2 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        Cry_GaaAutCsecAesCbcEncInitVector[LulIndex]
          = Cry_GddAutCsecAesCbcEncryptTb.pInitVectorPtr[LulIndex];
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutCsecAesCbcEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutCsecAesCbcEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (*(Cry_GddAutCsecAesCbcEncryptTb.pCipherTextLengthPtr)
      < Cry_GddAutCsecAesCbcEncryptTb.ulPlainTextLength)
    {
      /* Buffer size is invalid */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if ((Cry_GddAutCsecAesCbcEncryptTb.ulPlainTextLength < CSEC_BLOCK_BYTE_LENGTH)
      || ((Cry_GddAutCsecAesCbcEncryptTb.ulPlainTextLength % CSEC_BLOCK_BYTE_LENGTH) != CSM_ZERO))
    {
      /* plainTextLength should be multiples of 16 */
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      *(Cry_GddAutCsecAesCbcEncryptTb.pCipherTextLengthPtr) = CSM_ZERO;

      LddErr = Csec_EncCbc(Cry_GddAutCsecAesCbcEncKeyId,
        Cry_GddAutCsecAesCbcEncryptTb.ulPlainTextLength,
        Cry_GddAutCsecAesCbcEncryptTb.pPlainTextPtr,
        Cry_GddAutCsecAesCbcEncryptTb.pCipherTextPtr,
        Cry_GaaAutCsecAesCbcEncInitVector);

      if (LddErr == CSEC_ERC_NO_ERROR)
      {
        *(Cry_GddAutCsecAesCbcEncryptTb.pCipherTextLengthPtr)
          = Cry_GddAutCsecAesCbcEncryptTb.ulPlainTextLength;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutCsecAesCbcEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutCsecAesCbcEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    Cry_GddAutCsecAesCbcEncKeyId = CSEC_INVALID_KEY;

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddAutCsecAesCbcEncryptTb.ucJobState = NO_JOB;

    /* Notify respective Service about the completion of the task */
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
#endif

#if (CSM_SYM_AUTCSECAESCBCDECRYPT == STD_ON)
/*******************************************************************************
** Function Name        : Cry_AutCsecAesCbcDecryptStart                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of CSEC AES CBC, so that AES is able    **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutCsecAesCbcDecryptMainFunction() can process  **
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
**                        Cry_GddAutCsecAesCbcDecryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutCsecAesCbcDecryptInit,                       **
**                        Csm_SymDecryptServiceHasCallback,                   **
**                        Csec_LoadPlainKey                                   **
*******************************************************************************/
Std_ReturnType Cry_AutCsecAesCbcDecryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr, const uint8* InitVectorPtr,
  uint32 InitVectorLength)
{
  Std_ReturnType LddReturnValue;
  Csec_ErrType LddErr;
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutCsecAesCbcDecryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutCsecInit(CRY_AUTCSEC_AESCBCDEC);

    /* Set the job state to JOB_START */
    Cry_GddAutCsecAesCbcDecryptTb.ucJobState = JOB_START;

    if (Csm_SymDecryptServiceHasCallback() == FALSE)
    {
      if (InitVectorLength != CSEC_BLOCK_BYTE_LENGTH)
      {
        LddReturnValue = E_NOT_OK;
      }
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        /* Pre-Shared Key */
        if ((((keyPtr->data[0]) >= (uint8)CSEC_KEY_1) && \
              ((keyPtr->data[0]) <= (uint8)CSEC_KEY_10))
          || (((keyPtr->data[0]) >= (uint8)CSEC_KEY_11) && \
             ((keyPtr->data[0]) <= (uint8)CSEC_KEY_17)))
        {
          /* polyspace +2 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
          Cry_GddAutCsecAesCbcDecKeyId = (Csec_KeyIDType)(keyPtr->data[0]);
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }
      else if (keyPtr->length == CSEC_BLOCK_BYTE_LENGTH)
      {
        /* Raw Key */
        Cry_GddAutCsecAesCbcDecKeyId = CSEC_RAM_KEY;
        LddErr = Csec_LoadPlainKey((const uint8*)((const void*)(keyPtr->data)));
        if (LddErr != CSEC_ERC_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        for (LulIndex = CSM_ZERO; LulIndex < CSEC_BLOCK_BYTE_LENGTH; LulIndex++)
        {
          /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          Cry_GaaAutCsecAesCbcDecInitVector[LulIndex] = InitVectorPtr[LulIndex];
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutCsecAesCbcDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutCsecAesCbcDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutCsecAesCbcDecryptTb.pKeyPtr = keyPtr;
      Cry_GddAutCsecAesCbcDecryptTb.pInitVectorPtr = InitVectorPtr;
      Cry_GddAutCsecAesCbcDecryptTb.InitVectorLength = InitVectorLength;
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
** Function Name        : Cry_AutCsecAesCbcDecryptUpdate                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the AES      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutCsecAesCbcDecryptMainFunction() can process  **
**                        the input                                           **
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
**                        Cry_GddAutCsecAesCbcDecryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymDecryptServiceHasCallback, Csec_DecCbc       **
*******************************************************************************/
Std_ReturnType Cry_AutCsecAesCbcDecryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* cipherTextPtr, uint32 cipherTextLength, uint8* plainTextPtr,
  uint32* plainTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  Csec_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutCsecAesCbcDecryptTb.ucJobState)
  {
    Cry_GddAutCsecAesCbcDecryptTb.ucJobState = JOB_UPDATE;

    if (Csm_SymDecryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*plainTextLengthPtr < cipherTextLength)
      {
        /* Buffer size is invalid */
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if ((cipherTextLength < CSEC_BLOCK_BYTE_LENGTH)
        || ((cipherTextLength % CSEC_BLOCK_BYTE_LENGTH) != CSM_ZERO))
      {
        /* cipherTextLength should be multiples of 16 */
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        *plainTextLengthPtr = CSM_ZERO;

        LddErr = Csec_DecCbc(Cry_GddAutCsecAesCbcDecKeyId,
          cipherTextLength, cipherTextPtr, plainTextPtr,
          Cry_GaaAutCsecAesCbcDecInitVector);

        if (LddErr == CSEC_ERC_NO_ERROR)
        {
          *plainTextLengthPtr = cipherTextLength;
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutCsecAesCbcDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutCsecAesCbcDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutCsecAesCbcDecryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddAutCsecAesCbcDecryptTb.ulCipherTextLength = cipherTextLength;
      Cry_GddAutCsecAesCbcDecryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddAutCsecAesCbcDecryptTb.pPlainTextLengthPtr = plainTextLengthPtr;
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
** Function Name        : Cry_AutCsecAesCbcDecryptFinish                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the AES     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutCsecAesCbcDecryptMainFunction() can finish   **
**                        the computation and store the result in the memory  **
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
**                        Cry_GddAutCsecAesCbcDecryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SymDecryptServiceHasCallback                    **
*******************************************************************************/
Std_ReturnType Cry_AutCsecAesCbcDecryptFinish(Csm_ConfigIdType cfgId,
  uint8* plainTextPtr, uint32* plainTextLengthPtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);
  CSM_PARAM_UNUSED_PTR(plainTextPtr);
  CSM_PARAM_UNUSED_PTR(plainTextLengthPtr);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutCsecAesCbcDecryptTb.ucJobState)
  {
    Cry_GddAutCsecAesCbcDecKeyId = CSEC_INVALID_KEY;

    Cry_GddAutCsecAesCbcDecryptTb.ucJobState = JOB_FINISH;

    if (Csm_SymDecryptServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutCsecAesCbcDecryptTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_AutCsecAesCbcDecryptMainFunction                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SymDecryptCallbackNotification() with the       **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_AutCsecAesCbcDecryptStart()                     **
**                        or Cry_AutCsecAesCbcDecryptUpdate(). For            **
**                        Cry_AutCsecAesCbcDecryptFinish invocation of        **
**                        Csm_SymDecryptCallbackNotification()                **
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
**                        Cry_GddAutCsecAesCbcDecryptTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csec_LoadPlainKey, Csec_DecCbc,                     **
**                        Csm_SymDecryptCallbackNotification,                 **
**                        Csm_SymDecryptServiceFinishNotification             **
*******************************************************************************/
void Cry_AutCsecAesCbcDecryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Csec_ErrType LddErr;
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddAutCsecAesCbcDecryptTb.ucJobState)
  {
  case JOB_START:
    if (Cry_GddAutCsecAesCbcDecryptTb.InitVectorLength != CSEC_BLOCK_BYTE_LENGTH)
    {
      LddReturnValue = E_NOT_OK;
    }
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (Cry_GddAutCsecAesCbcDecryptTb.pKeyPtr->length == CSM_ONE)
    {
      /* Pre-Shared Key */
      if ((((Cry_GddAutCsecAesCbcDecryptTb.pKeyPtr->data[0]) >= (uint8)CSEC_KEY_1)
        && ((Cry_GddAutCsecAesCbcDecryptTb.pKeyPtr->data[0]) <= (uint8)CSEC_KEY_10))
        || (((Cry_GddAutCsecAesCbcDecryptTb.pKeyPtr->data[0]) >= (uint8)CSEC_KEY_11)
          && ((Cry_GddAutCsecAesCbcDecryptTb.pKeyPtr->data[0]) <= (uint8)CSEC_KEY_17)))
      {
        /* polyspace +2 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
        Cry_GddAutCsecAesCbcDecKeyId
          = (Csec_KeyIDType)(Cry_GddAutCsecAesCbcDecryptTb.pKeyPtr->data[0]);
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }
    else if (Cry_GddAutCsecAesCbcDecryptTb.pKeyPtr->length == CSEC_BLOCK_BYTE_LENGTH)
    {
      /* Raw Key */
      Cry_GddAutCsecAesCbcDecKeyId = CSEC_RAM_KEY;
      LddErr = Csec_LoadPlainKey(
        (const uint8*)((const void*)(Cry_GddAutCsecAesCbcDecryptTb.pKeyPtr->data)));
      if (LddErr != CSEC_ERC_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      for (LulIndex = CSM_ZERO; LulIndex < CSEC_BLOCK_BYTE_LENGTH; LulIndex++)
      {
        /* polyspace +2 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        Cry_GaaAutCsecAesCbcDecInitVector[LulIndex]
          = Cry_GddAutCsecAesCbcDecryptTb.pInitVectorPtr[LulIndex];
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutCsecAesCbcDecryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutCsecAesCbcDecryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (*(Cry_GddAutCsecAesCbcDecryptTb.pPlainTextLengthPtr)
      < Cry_GddAutCsecAesCbcDecryptTb.ulCipherTextLength)
    {
      /* Buffer size is invalid */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if ((Cry_GddAutCsecAesCbcDecryptTb.ulCipherTextLength < CSEC_BLOCK_BYTE_LENGTH)
      || ((Cry_GddAutCsecAesCbcDecryptTb.ulCipherTextLength % CSEC_BLOCK_BYTE_LENGTH) != CSM_ZERO))
    {
      /* cipherTextLength should be multiples of 16 */
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      *(Cry_GddAutCsecAesCbcDecryptTb.pPlainTextLengthPtr) = CSM_ZERO;

      LddErr = Csec_DecCbc(Cry_GddAutCsecAesCbcDecKeyId,
        Cry_GddAutCsecAesCbcDecryptTb.ulCipherTextLength,
        Cry_GddAutCsecAesCbcDecryptTb.pCipherTextPtr,
        Cry_GddAutCsecAesCbcDecryptTb.pPlainTextPtr,
        Cry_GaaAutCsecAesCbcDecInitVector);

      if (LddErr == CSEC_ERC_NO_ERROR)
      {
        *(Cry_GddAutCsecAesCbcDecryptTb.pPlainTextLengthPtr)
          = Cry_GddAutCsecAesCbcDecryptTb.ulCipherTextLength;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutCsecAesCbcDecryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutCsecAesCbcDecryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddAutCsecAesCbcDecryptTb.ucJobState = NO_JOB;

    /* Notify respective Service about the completion of the task */
    Csm_SymDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_SymDecryptServiceFinishNotification();
    break;
  }
}
#endif

#if (CSM_MAC_AUTCSECCMACAESGENERATE == STD_ON)
/*******************************************************************************
** Function Name        : Cry_AutCsecCmacAesGenerateStart                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of CSEC CMAC AES, so that it is         **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutCsecCmacAesGenerateMainFunction() can        **
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
**                        Cry_GddAutCsecCmacAesGenerateTb                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutCsecCmacAesGenerateInit,                     **
**                        Csm_MacGenerateServiceHasCallback,                  **
**                        Csec_LoadPlainKey                                   **
*******************************************************************************/
Std_ReturnType Cry_AutCsecCmacAesGenerateStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  Csec_ErrType LddErr;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddAutCsecCmacAesGenerateTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutCsecInit(CRY_AUTCSEC_CMACAESGEN);

    /* Set the job state to JOB_START */
    Cry_GddAutCsecCmacAesGenerateTb.ucJobState = JOB_START;

    if (Csm_MacGenerateServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        /* Pre-Shared Key */
        if ((((keyPtr->data[0]) >= (uint8)CSEC_KEY_1) && \
           ((keyPtr->data[0]) <= (uint8)CSEC_KEY_10)) \
          || (((keyPtr->data[0]) >= (uint8)CSEC_KEY_11) && \
            ((keyPtr->data[0]) <= (uint8)CSEC_KEY_17)))
        {
          /* polyspace +2 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
          Cry_GddAutCsecCmacAesGenKeyId = (Csec_KeyIDType)(keyPtr->data[0]);
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }
      else if (keyPtr->length == CSEC_BLOCK_BYTE_LENGTH)
      {
        /* Raw Key */
        Cry_GddAutCsecCmacAesGenKeyId = CSEC_RAM_KEY;
        LddErr = Csec_LoadPlainKey((const uint8*)((const void*)(keyPtr->data)));
        if (LddErr != CSEC_ERC_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutCsecCmacAesGenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutCsecCmacAesGenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutCsecCmacAesGenerateTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_AutCsecCmacAesGenerateUpdate                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the CSEC     **
**                        CMAC AES                                            **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutCsecCmacAesGenerateMainFunction() can process**
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
**                        Cry_GddAutCsecCmacAesGenerateTb                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacGenerateServiceHasCallback, Csec_GenerateMac **
*******************************************************************************/
Std_ReturnType Cry_AutCsecCmacAesGenerateUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  Csec_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutCsecCmacAesGenerateTb.ucJobState)
  {
    Cry_GddAutCsecCmacAesGenerateTb.ucJobState = JOB_UPDATE;

    if (Csm_MacGenerateServiceHasCallback() == FALSE)
    {
      LddErr = Csec_GenerateMac(Cry_GddAutCsecCmacAesGenKeyId,
        dataPtr, dataLength * CSM_EIGHT, Cry_GaaAutCsecCmacAesGenDigest);
      if (LddErr != CSEC_ERC_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutCsecCmacAesGenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutCsecCmacAesGenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutCsecCmacAesGenerateTb.pDataPtr = dataPtr;
      Cry_GddAutCsecCmacAesGenerateTb.ulDataLength = dataLength;
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
** Function Name        : Cry_AutCsecCmacAesGenerateFinish                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the CSEC    **
**                        CMAC AES computation and store the result into      **
**                        the memory location given                           **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutCsecCmacAesGenerateMainFunction() can finish **
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
**                        Cry_GddAutCsecCmacAesGenerateTb                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacGenerateServiceHasCallback,                  **
**                        Csec_GenerateMacFinish                              **
*******************************************************************************/
Std_ReturnType Cry_AutCsecCmacAesGenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed)
{
  Std_ReturnType LddReturnValue;
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutCsecCmacAesGenerateTb.ucJobState)
  {
    Cry_GddAutCsecCmacAesGenerateTb.ucJobState = JOB_FINISH;

    if (Csm_MacGenerateServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if ((*resultLengthPtr < CSEC_BLOCK_BYTE_LENGTH)
        && (TruncationIsAllowed != CSM_TRUE))
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        *resultLengthPtr = (*resultLengthPtr < CSEC_BLOCK_BYTE_LENGTH)
          ? (*resultLengthPtr) : CSEC_BLOCK_BYTE_LENGTH;

        for (LulIndex = CSM_ZERO; LulIndex < *resultLengthPtr; LulIndex++)
        {
          /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          resultPtr[LulIndex] = Cry_GaaAutCsecCmacAesGenDigest[LulIndex];
        }
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutCsecCmacAesGenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddAutCsecCmacAesGenerateTb.pResultPtr = resultPtr;
      Cry_GddAutCsecCmacAesGenerateTb.pResultLengthPtr = resultLengthPtr;
      Cry_GddAutCsecCmacAesGenerateTb.blTruncationIsAllowed = TruncationIsAllowed;
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
** Function Name        : Cry_AutCsecCmacAesGenerateMainFunction              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_MacGenerateCallbackNotification() with the      **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_AutCsecCmacAesGenerateStart() or                **
**                        Cry_AutCsecCmacAesGenerateUpdate(). For             **
**                        Cry_AutCsecCmacAesGenerateFinish invocation of      **
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
**                        Cry_GddAutCsecCmacAesGenerateTb                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csec_LoadPlainKey, Csec_GenerateMac,                **
**                        Csec_GenerateMacFinish,                             **
**                        Csm_MacGenerateCallbackNotification,                **
**                        Csm_MacGenerateServiceFinishNotification            **
*******************************************************************************/
void Cry_AutCsecCmacAesGenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Csec_ErrType LddErr;
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* State machine of CSEC CMAC AES job processing */
  switch (Cry_GddAutCsecCmacAesGenerateTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (Cry_GddAutCsecCmacAesGenerateTb.pKeyPtr->length == CSM_ONE)
    {
      /* Pre-Shared Key */
      if ((((Cry_GddAutCsecCmacAesGenerateTb.pKeyPtr->data[0]) >= (uint8)CSEC_KEY_1)
        && ((Cry_GddAutCsecCmacAesGenerateTb.pKeyPtr->data[0]) <= (uint8)CSEC_KEY_10))
        || (((Cry_GddAutCsecCmacAesGenerateTb.pKeyPtr->data[0]) >= (uint8)CSEC_KEY_11)
          && ((Cry_GddAutCsecCmacAesGenerateTb.pKeyPtr->data[0]) <= (uint8)CSEC_KEY_17)))
      {
        /* polyspace +2 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
        Cry_GddAutCsecCmacAesGenKeyId
          = (Csec_KeyIDType)(Cry_GddAutCsecCmacAesGenerateTb.pKeyPtr->data[0]);
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }
    else if (Cry_GddAutCsecCmacAesGenerateTb.pKeyPtr->length == CSEC_BLOCK_BYTE_LENGTH)
    {
      /* Raw Key */
      Cry_GddAutCsecCmacAesGenKeyId = CSEC_RAM_KEY;
      LddErr = Csec_LoadPlainKey(
        (const uint8*)((const void*)(Cry_GddAutCsecCmacAesGenerateTb.pKeyPtr->data)));
      if (LddErr != CSEC_ERC_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutCsecCmacAesGenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutCsecCmacAesGenerateTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LddErr = Csec_GenerateMac(Cry_GddAutCsecCmacAesGenKeyId,
      Cry_GddAutCsecCmacAesGenerateTb.pDataPtr,
      Cry_GddAutCsecCmacAesGenerateTb.ulDataLength * CSM_EIGHT,
      Cry_GaaAutCsecCmacAesGenDigest);
    if (LddErr != CSEC_ERC_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutCsecCmacAesGenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutCsecCmacAesGenerateTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if ((*(Cry_GddAutCsecCmacAesGenerateTb.pResultLengthPtr) < CSEC_BLOCK_BYTE_LENGTH)
      && (Cry_GddAutCsecCmacAesGenerateTb.blTruncationIsAllowed != CSM_TRUE))
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      *(Cry_GddAutCsecCmacAesGenerateTb.pResultLengthPtr)
        = (*(Cry_GddAutCsecCmacAesGenerateTb.pResultLengthPtr) < CSEC_BLOCK_BYTE_LENGTH)
        ? (*(Cry_GddAutCsecCmacAesGenerateTb.pResultLengthPtr)) : CSEC_BLOCK_BYTE_LENGTH;

      for (LulIndex = CSM_ZERO;
        LulIndex < *(Cry_GddAutCsecCmacAesGenerateTb.pResultLengthPtr); LulIndex++)
      {
        /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        Cry_GddAutCsecCmacAesGenerateTb.pResultPtr[LulIndex]
          = Cry_GaaAutCsecCmacAesGenDigest[LulIndex];
      }
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddAutCsecCmacAesGenerateTb.ucJobState = NO_JOB;

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
#endif

#if (CSM_MAC_AUTCSECCMACAESVERIFY == STD_ON)
/*******************************************************************************
** Function Name        : Cry_AutCsecCmacAesVerifyStart                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of CSEC CMAC AES, so that if is         **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutCsecCmacAesVerifyMainFunction() can process  **
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
**                        Cry_GddAutCsecCmacAesVerifyTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutCsecCmacAesVerifyInit,                       **
**                        Csm_MacVerifyServiceHasCallback,                    **
**                        Csec_LoadPlainKey                                   **
*******************************************************************************/
Std_ReturnType Cry_AutCsecCmacAesVerifyStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  Csec_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutCsecCmacAesVerifyTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutCsecInit(CRY_AUTCSEC_CMACASEVER);

    Cry_GddAutCsecCmacAesVerifyTb.ucJobState = JOB_START;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        /* Pre-Shared Key */
        if ((((keyPtr->data[0]) >= (uint8)CSEC_KEY_1) && ((keyPtr->data[0]) <= (uint8)CSEC_KEY_10))
          || (((keyPtr->data[0]) >= (uint8)CSEC_KEY_11) && ((keyPtr->data[0]) <= (uint8)CSEC_KEY_17)))
        {
          /* polyspace +1 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
          Cry_GddAutCsecCmacAesVerKeyId = (Csec_KeyIDType)(keyPtr->data[0]);
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }
      else if (keyPtr->length == CSEC_BLOCK_BYTE_LENGTH)
      {
        /* Raw Key */
        Cry_GddAutCsecCmacAesVerKeyId = CSEC_RAM_KEY;
        LddErr = Csec_LoadPlainKey((const uint8*)((const void*)(keyPtr->data)));
        if (LddErr != CSEC_ERC_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutCsecCmacAesVerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutCsecCmacAesVerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutCsecCmacAesVerifyTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_AutCsecCmacAesVerifyUpdate                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the CSEC     **
**                        CMAC AES                                            **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutCsecCmacAesVerifyMainFunction() can process  **
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
**                        Cry_GddAutCsecCmacAesVerifyTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacVerifyServiceHasCallback, Csec_VerifyMac     **
*******************************************************************************/
Std_ReturnType Cry_AutCsecCmacAesVerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  Csec_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutCsecCmacAesVerifyTb.ucJobState)
  {
    /* Set the job state to JOB_UPDATE */
    Cry_GddAutCsecCmacAesVerifyTb.ucJobState = JOB_UPDATE;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      LddErr = Csec_GenerateMac(Cry_GddAutCsecCmacAesVerKeyId,
        dataPtr, dataLength * CSM_EIGHT, Cry_GaaAutCsecCmacAesVerDigest);
      if (LddErr != CSEC_ERC_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutCsecCmacAesVerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutCsecCmacAesVerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutCsecCmacAesVerifyTb.pDataPtr = dataPtr;
      Cry_GddAutCsecCmacAesVerifyTb.ulDataLength = dataLength;
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
** Function Name        : Cry_AutCsecCmacAesVerifyFinish                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the CSEC    **
**                        CMAC AES computation and store the result into      **
**                        the memory location given                           **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutCsecCmacAesVerifyMainFunction() can finish   **
**                        the computation and store the result in the memory  **
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
**                        Cry_GddAutCsecCmacAesVerifyTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacVerifyServiceHasCallback,                    **
**                        Csec_VerifyMacFinish                                **
*******************************************************************************/
Std_ReturnType Cry_AutCsecCmacAesVerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* MacPtr, uint32 MacLength, Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;
  uint32 LulIndex;
  Csm_VerifyResultType LddVerifyResult;
  uint32 LulMacLength;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutCsecCmacAesVerifyTb.ucJobState)
  {
    Cry_GddAutCsecCmacAesVerifyTb.ucJobState = JOB_FINISH;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      LulMacLength = MacLength;
      LddVerifyResult = CSM_E_VER_OK;
      if (LulMacLength > CSEC_BLOCK_BYTE_LENGTH * CSM_EIGHT)
      {
        LulMacLength = CSEC_BLOCK_BYTE_LENGTH * CSM_EIGHT;
      }

      /* Comparing the two MACs */
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The array length is checked" */
      for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength / CSM_EIGHT); LulIndex++)
      {
        /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        if (MacPtr[LulIndex] != Cry_GaaAutCsecCmacAesVerDigest[LulIndex])
        {
          LddVerifyResult = CSM_E_VER_NOT_OK;
          break;
        }
      }
      if ((LddVerifyResult == CSM_E_VER_OK)  && ((LulMacLength % CSM_EIGHT) > CSM_ZERO) )
      {
        for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength % CSM_EIGHT); LulIndex++)
        {
          /* polyspace +4 MISRA-C3:18.1 RTE:IDP RTE:OBAI [Justified:Low] "The array index is checked" */
          /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          if ((MacPtr[LulMacLength / CSM_EIGHT]
            & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE)))
            != (Cry_GaaAutCsecCmacAesVerDigest[LulMacLength / CSM_EIGHT]
             & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE))))
          {
            LddVerifyResult = CSM_E_VER_NOT_OK;
            break;
          }
        }
      }
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      *resultPtr = LddVerifyResult;
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutCsecCmacAesVerifyTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddAutCsecCmacAesVerifyTb.pMacPtr = MacPtr;
      Cry_GddAutCsecCmacAesVerifyTb.ulMacLength = MacLength;
      Cry_GddAutCsecCmacAesVerifyTb.pResultPtr = resultPtr;
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
** Function Name        : Cry_AutCsecCmacAesVerifyMainFunction                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_MacVerifyCallbackNotification() with the        **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_AutCsecCmacAesVerifyStart() or                  **
**                        Cry_AutCsecCmacAesVerifyUpdate(). For               **
**                        Cry_AutCsecCmacAesVerifyFinish invocation of        **
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
**                        Cry_GddAutCsecCmacAesVerifyTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csec_LoadPlainKey, Csec_VerifyMac,                  **
**                        Csec_VerifyMacFinish,                               **
**                        Csm_MacVerifyCallbackNotification,                  **
**                        Csm_MacVerifyServiceFinishNotification              **
*******************************************************************************/
void Cry_AutCsecCmacAesVerifyMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Csec_ErrType LddErr;
  uint32 LulIndex;
  Csm_VerifyResultType LddVerifyResult;
  uint32 LulMacLength;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* State machine of CSEC CMAC AES job processing */
  switch (Cry_GddAutCsecCmacAesVerifyTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (Cry_GddAutCsecCmacAesVerifyTb.pKeyPtr->length == CSM_ONE)
    {
      /* Pre-Shared Key */
      if ((((Cry_GddAutCsecCmacAesVerifyTb.pKeyPtr->data[0]) >= (uint8)CSEC_KEY_1)
        && ((Cry_GddAutCsecCmacAesVerifyTb.pKeyPtr->data[0]) <= (uint8)CSEC_KEY_10))
        || (((Cry_GddAutCsecCmacAesVerifyTb.pKeyPtr->data[0]) >= (uint8)CSEC_KEY_11)
        && ((Cry_GddAutCsecCmacAesVerifyTb.pKeyPtr->data[0]) <= (uint8)CSEC_KEY_17)))
      {
        /* polyspace +2 MISRA-C3:10.5 [Justified:Low] "No Impact of this rule violation" */
        Cry_GddAutCsecCmacAesVerKeyId
          = (Csec_KeyIDType)(Cry_GddAutCsecCmacAesVerifyTb.pKeyPtr->data[0]);
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }
    else if (Cry_GddAutCsecCmacAesVerifyTb.pKeyPtr->length == CSEC_BLOCK_BYTE_LENGTH)
    {
      /* Raw Key */
      Cry_GddAutCsecCmacAesVerKeyId = CSEC_RAM_KEY;
      LddErr = Csec_LoadPlainKey(
        (const uint8*)((const void*)(Cry_GddAutCsecCmacAesVerifyTb.pKeyPtr->data)));
      if (LddErr != CSEC_ERC_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutCsecCmacAesVerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutCsecCmacAesVerifyTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LddErr = Csec_GenerateMac(Cry_GddAutCsecCmacAesVerKeyId,
      Cry_GddAutCsecCmacAesVerifyTb.pDataPtr,
      Cry_GddAutCsecCmacAesVerifyTb.ulDataLength * CSM_EIGHT,
      Cry_GaaAutCsecCmacAesVerDigest);
    if (LddErr != CSEC_ERC_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutCsecCmacAesVerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutCsecCmacAesVerifyTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    LulMacLength = Cry_GddAutCsecCmacAesVerifyTb.ulMacLength;
    LddVerifyResult = CSM_E_VER_OK;
    if (LulMacLength > CSEC_BLOCK_BYTE_LENGTH * CSM_EIGHT)
    {
      LulMacLength = CSEC_BLOCK_BYTE_LENGTH * CSM_EIGHT;
    }

    /* Comparing the two MACs */
    for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength / CSM_EIGHT); LulIndex++)
    {
      /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (Cry_GddAutCsecCmacAesVerifyTb.pMacPtr[LulIndex]
        != Cry_GaaAutCsecCmacAesVerDigest[LulIndex])
      {
        LddVerifyResult = CSM_E_VER_NOT_OK;
        break;
      }
    }
    if ((LddVerifyResult == CSM_E_VER_OK) && ((LulMacLength % CSM_EIGHT) > CSM_ZERO) )
    {
      for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength % CSM_EIGHT); LulIndex++)
      {
        /* polyspace-begin MISRA-C3:18.1 RTE:IDP RTE:OBAI [Justified:Low] "The pointer is checked" */
        if ((Cry_GddAutCsecCmacAesVerifyTb.pMacPtr[LulMacLength / CSM_EIGHT]
          & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE)))
          != (Cry_GaaAutCsecCmacAesVerDigest[LulMacLength / CSM_EIGHT]
           & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE))))
        {
          LddVerifyResult = CSM_E_VER_NOT_OK;
          break;
        }
        /* polyspace-end MISRA-C3:18.1 RTE:IDP RTE:OBAI */
      }
    }
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    *(Cry_GddAutCsecCmacAesVerifyTb.pResultPtr) = LddVerifyResult;
    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddAutCsecCmacAesVerifyTb.ucJobState = NO_JOB;

    /* Notify respective Service about the completion of the task */
    Csm_MacVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_MacVerifyServiceFinishNotification();
    break;
  }
}
#endif

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CRYPTOLIB_SUPORT_HSM_CSEC == STD_ON) */

#endif

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
