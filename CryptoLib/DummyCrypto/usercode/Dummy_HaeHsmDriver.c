/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dummy_HaeHsmDriver.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Dummy HAE HSM Driver library                                  **
**                                                                            **
**  PURPOSE   : Source file for dummy code                                    **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0.0   18-Jul-2019   Sinil        Initial version                       **
** 1.0.1.0   03-Nov-2020   JaeHyun      Sync with HSM 2.3.0                   **
*******************************************************************************/

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Dummy_HaeHsmDriver.h"

/*******************************************************************************
**                        Global Function Definitions                         **
*******************************************************************************/
/* CryptoService_Aes.h */
Std_ReturnType HSM_AesEncStart(HSMAPI_CTX_t *aesCtx, AES_MODE aesMode, UINT16 aesKeyNum, const UINT8 *ivBuff)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_AesEncUpdate(const HSMAPI_CTX_t *aesCtx, const UINT8 *plain, UINT32 plainLen)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_AesEncFinish(const HSMAPI_CTX_t *aesCtx)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_AesDecStart(HSMAPI_CTX_t *aesCtx, AES_MODE aesMode, UINT16 aesKeyNum, const UINT8 *ivBuff)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_AesDecUpdate(const HSMAPI_CTX_t *aesCtx, const UINT8 *cipher, UINT32 cipherLen)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_AesDecFinish(const HSMAPI_CTX_t *aesCtx)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_AesCmacStart(HSMAPI_CTX_t *aesCmacCtx, UINT16 aesCmacKeyNum, UINT32 totalMsgLen)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_AesCmacUpdate(const HSMAPI_CTX_t *aesCmacCtx, const UINT8 *data, UINT32 dataLen)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_AesCmacFinish(const HSMAPI_CTX_t *aesCmacCtx, UINT8 *digest)
{
  return E_NOT_OK;
}


/* CryptoService_Ecc.h */
Std_ReturnType HSM_EccEcdsaSignStart(HSMAPI_CTX_t *eccCtx, UINT16 eccKeyNum)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_EccEcdsaSignUpdate(const HSMAPI_CTX_t *eccCtx, const UINT8 *digest, const UINT8 *secretNumber)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_EccEcdsaSignFinish(const HSMAPI_CTX_t *eccCtx, ECC_ECDSA_SIGN_t *sign)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_EccEcdsaVerifyStart(HSMAPI_CTX_t *eccCtx, UINT16 eccKeyNum)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_EccEcdsaVerifyUpdate(const HSMAPI_CTX_t *eccCtx, const UINT8 *digest, const ECC_ECDSA_SIGN_t *sign)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_EccEcdsaVerifyFinish(const HSMAPI_CTX_t *eccCtx, UINT8 *result)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_EccEcdhStart(HSMAPI_CTX_t *eccCtx, UINT16 eccKeyNum)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_EccEcdhUpdate(const HSMAPI_CTX_t *eccCtx, const ECC_PUBLICKEY_t *pubkeyOtherSide)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_EccEcdhFinish(const HSMAPI_CTX_t *eccCtx, UINT8 *secretValue)
{
  return E_NOT_OK;
}


/* CryptoService_Hash.h */
Std_ReturnType HSM_Sha160Start(HSMAPI_CTX_t *sha160Ctx)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_Sha160Update(const HSMAPI_CTX_t *sha160Ctx, const UINT8 *data, UINT32 dataLen)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_Sha160Finish(const HSMAPI_CTX_t *sha160Ctx, UINT8 *digest)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_Sha256Start(HSMAPI_CTX_t *sha256Ctx)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_Sha256Update(const HSMAPI_CTX_t *sha256Ctx, const UINT8 *data, UINT32 dataLen)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_Sha256Finish(const HSMAPI_CTX_t *sha256Ctx, UINT8 *digest)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_HmacSha256Start(HSMAPI_CTX_t *hmacSha256Ctx, UINT16 keyNum)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_HmacSha256Update(const HSMAPI_CTX_t *hmacSha256Ctx, const UINT8 *data, UINT32 dataLen)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_HmacSha256Finish(const HSMAPI_CTX_t *hmacSha256Ctx, UINT8 *digest)
{
  return E_NOT_OK;
}


/* CryptoService_Pbkdf2.h */
Std_ReturnType HSM_Pbkdf2Start(HSMAPI_CTX_t *pbkdf2Ctx, UINT16 pbkdf2KeyNum)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_Pbkdf2Update(const HSMAPI_CTX_t *pbkdf2Ctx, UINT16 pbkdf2KeyNum, UINT32 dkLen, const UINT8 *password, UINT32 pLen, const UINT8 *salt, UINT32 sLen, UINT32 icount)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_Pbkdf2Finish(const HSMAPI_CTX_t *pbkdf2Ctx, UINT32 dkLen, UINT8 *derivedKey)
{
  return E_NOT_OK;
}


/* CryptoService_RsaPkcs1.h */
Std_ReturnType HSM_RsaPkcs1v15SignStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1v15SignUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *digest)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1v15SignFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *sign)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1v15VerifyStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1v15VerifyUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *digest, const UINT8 *sign)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1v15Sha160VerifyUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *digest, const UINT8 *sign)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1v15VerifyFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *verifyResult)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1v15EncStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1v15EncUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *msg, UINT32 msgLen)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1v15EncFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *cipher)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1v15DecStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1v15DecUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *cipher)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1v15DecFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *msg, UINT32 *msgLen)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1PssSignStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1PssSignUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *digest, const UINT8 *salt, UINT32 saltLen)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1PssSignFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *sign)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1PssVerifyStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1PssVerifyUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *digest, const UINT8 *sign, UINT32 saltLen)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1PssVerifyFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *result)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1oaepEncStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1oaepEncUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *msg, UINT32 msgLen, const UINT8 *label, UINT32 labelLen, const UINT8 *seed)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1oaepEncFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *cipher)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1oaepDecStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1oaepDecUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *cipher, const UINT8 *label, UINT32 labelLen)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs1oaepDecFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *msg, UINT32 *msgLen)
{
  return E_NOT_OK;
}


/* CryptoService_RsaPkcs3.h */
Std_ReturnType HSM_RsaPkcs3DHKeypairGenStart(HSMAPI_CTX_t *pkcs3Ctx)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs3DHKeypairGenUpdate(const HSMAPI_CTX_t *pkcs3Ctx, const UINT8 *privValue, const UINT8 *baseG, const UINT8 *primeP)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs3DHKeypairGenFinish(const HSMAPI_CTX_t *pkcs3Ctx, UINT8 *publicValue, UINT8 *privateValue)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs3DHSharedValueGenStart(HSMAPI_CTX_t *pkcs3Ctx)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs3DHSharedValueGenUpdate(const HSMAPI_CTX_t *pkcs3Ctx, const UINT8 *publicValue, const UINT8 *privateValue, const UINT8 *primeP)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_RsaPkcs3DHSharedValueGenFinish(const HSMAPI_CTX_t *pkcs3Ctx, UINT8 *secretValue)
{
  return E_NOT_OK;
}


/* Hsm_HostAPI.h */
Std_ReturnType HSM_DriverInitialize(void)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_EnableService(UINT32 conf, UINT32 priority)
{
  return E_NOT_OK;
}
void HSM_IrqHandler(void)
{
}
UINT32 HSM_GetLastErrorCode(void)
{
  return 0xFFFF;
}
Std_ReturnType HSM_WaitResp(UINT16 jobId)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_ReadRxBuff(UINT16 jobId, UINT32 count, UINT8 *data)
{
  return E_NOT_OK;
}
UINT32 HSM_GetMaxTranSizeByte(void)
{
  return 0UL;
}
Std_ReturnType HSM_CancelJob(UINT16 jobId)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_GetMcuUid(UINT8 *uid)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_GetVersionInfo(HSM_VERSION_CTX_t *version)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_GetAllSecurityInfo(HSM_SECURITY_INFO_t *info)
{
  return E_NOT_OK;
}
BOOL HSM_CheckHsmTempStopState(void)
{
  return 0;
}
Std_ReturnType HSM_TempStop(void)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_Restart(void)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_FactoryHsmConfigurationLock(void)
{
  return E_NOT_OK;
}
void HSM_DisableInterruptService(void)
{
}
void HSM_SetCallbackFuncWaitCount(UINT32 waitCount)
{
}
Std_ReturnType HSM_Sleep(void)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_Wakeup(void)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_SetWakeupTrigger(const UINT16 *list, UINT16 idxNum)
{
  return E_NOT_OK;
}
BOOL HSM_IsSleepStatus(void)
{
  return 0;
}
Std_ReturnType HSM_StartUsingDFlash(void)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_FinishUsingDFlash(void)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_SetHsmHandlerIrqN(UINT8 irqN)
{
  return E_NOT_OK;
}
 Std_ReturnType HSM_ClearWakeupTrigger(void)
{
  return E_NOT_OK;
}
void HSM_SetApiWaitRespTime(UINT32 ms)
{
}
Std_ReturnType HSM_ChallengeRequest(UINT8 *ChallengeValue)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_ResponseForward(UINT8 *ResponseValue)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_GetConfigurationLockState(HSM_CONFIG_LOCK_STATE_t *state)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_SetIdAuthentication(const UINT32 *idAuth)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_SetInterruptConfig(UINT32 coreNum, UINT32 priority)
{
  return E_NOT_OK;
}

/* SecurityApp_FwTamperDetection.h */
Std_ReturnType HSM_FwTamperDetectionStatus(HSM_FTD_STATE_t *state)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_FwTamperDetectionLog(HSM_FTD_LOG_t *ftdLog)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_FwTamperDetectionTempStop(const UINT8 *password, UINT32 pwByteLen, HSM_PASSWORD_VERIFY_STATE_t *errState)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_FwTamperDetectionRestart(void)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_FwTamperDetectionConfig(const HSM_FTD_CONFIG_t *ftdConfig, HSM_CallbackFunc cbFunc)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_FwTamperDetectionUpdtTarget(const HSM_FTD_TARGET_t *ftdTarget, HSM_CallbackFunc cbFunc)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_FactoryFwTamperDetectionEnable(const HSM_FTD_CONFIG_t *ftdConfig, HSM_CallbackFunc cbFunc)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_FactoryFwTamperDetectionDisable(void)
{
  return E_NOT_OK;
}


/* SecurityApp_KeyManagement.h */
Std_ReturnType HSM_KeyManagementSetAesKey(const UINT16 keyIndex, UINT8* key, UINT16 keyLock)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_KeyManagementSetRsaKey(const UINT16 keyIndex, Rsa_Keypair_t* key, UINT16 keyLock)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_KeyManagementSetEccKey(const UINT16 keyIndex, Ecc_Keypair_t* key, UINT16 keyLock)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_KeyManagementValidateKey(KEY_TYPE keyType, const UINT16 keyIndex)
{
  return E_NOT_OK;
}


/* SecurityApp_ProactiveDataProtection.h */
Std_ReturnType HSM_PDPConfig(HSM_PDP_CONFIG_t* pdpConfig)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_PDPDataUpdate(void)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_PDPDataVerify(void)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_PDPDisable(void)
{
  return E_NOT_OK;
}


/* SecurityApp_Rng.h */
Std_ReturnType HSM_TrueRandomGenerate(UINT8 *randValue, UINT32 len)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_PseudoRandomGenerate(UINT8 *randValue, UINT32 len)
{
  return E_NOT_OK;
}


/* SecurityApp_SecureBoot.h */
Std_ReturnType HSM_SecureBootResult(HSM_SECUREBOOT_STATE_t *state)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_SecureBootMacUpdate(const HSM_SB_CONFIG_t *sbConfig)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_FactorySecureBootEnable(const HSM_SB_CONFIG_t *sbConfig)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_FactorySecureBootDisable(void)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_FactorySecureBootEnableDualBank(const HSM_SB_DUAL_CONFIG_t *sbConfig)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_SecureBootMacUpdateDualBank(const HSM_SB_MAC_DUALBANK_CONFIG_t *sbConfig)
{
  return E_NOT_OK;
}

/* SecurityApp_SecureDebug.h */
Std_ReturnType HSM_FactoryDebuggerProtectionEnable(const UINT8 *password, UINT32 pwByteLen)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_FactoryDebuggerProtectionTempStop(const UINT8 *password, UINT32 pwByteLen, HSM_SECUREDEBUG_STATE_t *debugState)
{
  return E_NOT_OK;
}

/* SecurityApp_FeatureOnDemand.h */
Std_ReturnType HSM_FeatureOnDemandCertStore(const FoDCert *fodCert, const HSM_SIGN_t *signInfo, HSM_FOD_ERR_STATE_t* errState)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_FeatureOnDemandCertDelete(const FoDCert *fodCert, const HSM_SIGN_t *signInfo, HSM_FOD_ERR_STATE_t* errState)
{
  return E_NOT_OK;
}
Std_ReturnType HSM_FeatureOnDemandGetCertList(FoDCert fodCertList[], UINT32 *numOfFodCert, HSM_FOD_ERR_STATE_t* errState)
{
  return E_NOT_OK;
}
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
