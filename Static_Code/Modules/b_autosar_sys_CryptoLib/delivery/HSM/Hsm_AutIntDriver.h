/*******************************************************************************
**                                                                            **
**  (C) 2017~2018 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Hsm_AutIntDriver.h                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Hsm (Hardware Security Module)                                **
**                                                                            **
**  PURPOSE   : Header file for HSM                                           **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.1.0     09-Aug-2018   Sinil        Redmine #13647                        **
** 1.0.4     09-May-2018   Sinil        Redmine #12626                        **
** 1.0.3     27-Apr-2018   Sinil        Redmine #12516                        **
** 1.0.2     17-Apr-2018   Sinil        Redmine #12345                        **
** 1.0.1     19-Mar-2018   Sinil        Redmine #11932                        **
** 1.0.0     16-Feb-2017   Sinil        Initial version                       **
*******************************************************************************/

#ifndef HSM_AUTINTDRIVER_H
#define HSM_AUTINTDRIVER_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Hsm_AutTypes.h"

#if ((CRYPTOLIB_SUPORT_HSM_SPC58X == STD_ON) || (CRYPTOLIB_SUPORT_HSM_ICUM == STD_ON))
#include "Hsm_HAETypes.h"

/*******************************************************************************
**                      Enumerations                                          **
*******************************************************************************/
typedef enum
{
  HSM_AES_ECB_MODE = 0x01U,
  HSM_AES_CBC_MODE = 0x02U,
  HSM_AES_CTR_MODE = 0x03U,
  HSM_AES_OFB_MODE = 0x04U,
} Hsm_AesModeType;

typedef enum
{
  HSM_DC_ENABLE_HSM_DEBUG   = 0x01U,
  HSM_DC_DISABLE_HSM_DEBUG  = 0x02U,
  HSM_DC_ENABLE_HOST_DEBUG  = 0x04U,
  HSM_DC_DISABLE_HOST_DEBUG = 0x08U,
} Hsm_DebugControlType;

/*******************************************************************************
**                      Defines                                               **
*******************************************************************************/
#define HSM_AES_KEY_BYTE_SIZE                           ((uint32)(16))
#define HSM_RSA_KEY_BYTE_SIZE                           ((uint32)(256))
#define HSM_ECC_KEY_BYTE_SIZE                           ((uint32)(32))

#define HSM_AES_BLOCK_BYTE_SIZE                         (16)

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
extern void Hsm_RunChorusHsmCore(void);

extern Hsm_ErrType Hsm_Init(void);

/* Hash */
extern Hsm_ErrType Hsm_Sha1Init(boolean blAsync, Hsm_CallbackPtr pCallback);
extern Hsm_ErrType Hsm_Sha1Update(boolean blAsync, Hsm_CallbackPtr pCallback,
  const uint8* pData, uint32 ulDataLength);
extern Hsm_ErrType Hsm_Sha1Finish(boolean blAsync, Hsm_CallbackPtr pCallback,
  uint8* pResult, uint32 ulResultLength);
extern Hsm_ErrType Hsm_Sha256Init(boolean blAsync, Hsm_CallbackPtr pCallback);
extern Hsm_ErrType Hsm_Sha256Update(boolean blAsync, Hsm_CallbackPtr pCallback,
  const uint8* pData, uint32 ulDataLength);
extern Hsm_ErrType Hsm_Sha256Finish(boolean blAsync, Hsm_CallbackPtr pCallback,
  uint8* pResult, uint32 ulResultLength);

/* Mac */
extern Hsm_ErrType Hsm_AesCmacInit(boolean blAsync, Hsm_CallbackPtr pCallback,
  Hsm_DataType ddDataType, Hsm_DataIDType ddDataID, boolean blGen);
extern Hsm_ErrType Hsm_AesCmacUpdate(boolean blAsync, Hsm_CallbackPtr pCallback,
  const uint8* pData, uint32 ulDataLength, boolean blGen);
extern Hsm_ErrType Hsm_AesCmacFinish(boolean blAsync, Hsm_CallbackPtr pCallback,
  uint8* pMac, uint32 ulMacLength, uint8* pVerifyResult, boolean blGen);
extern Hsm_ErrType Hsm_HmacSha160Init(boolean blAsync, Hsm_CallbackPtr pCallback,
  const uint8* pKey, uint32 ulKeyLength, boolean blGen);
extern Hsm_ErrType Hsm_HmacSha160Update(boolean blAsync, Hsm_CallbackPtr pCallback,
  const uint8* pData, uint32 ulDataLength, boolean blGen);
extern Hsm_ErrType Hsm_HmacSha160Finish(boolean blAsync, Hsm_CallbackPtr pCallback,
  uint8* pMac, uint32 ulMacLength, uint8* pVerifyResult, boolean blGen);
extern Hsm_ErrType Hsm_HmacSha256Init(boolean blAsync, Hsm_CallbackPtr pCallback,
  const uint8* pKey, uint32 ulKeyLength, boolean blGen);
extern Hsm_ErrType Hsm_HmacSha256Update(boolean blAsync, Hsm_CallbackPtr pCallback,
  const uint8* pData, uint32 ulDataLength, boolean blGen);
extern Hsm_ErrType Hsm_HmacSha256Finish(boolean blAsync, Hsm_CallbackPtr pCallback,
  uint8* pMac, uint32 ulMacLength, uint8* pVerifyResult, boolean blGen);

/* Random */
extern Hsm_ErrType Hsm_TrngGen(boolean blAsync, Hsm_CallbackPtr pCallback,
  uint8* pRandom, uint32 ulLength);
extern Hsm_ErrType Hsm_PrngGen(boolean blAsync, Hsm_CallbackPtr pCallback,
  uint8* pRandom, uint32 ulLength);

/* Symmetric */
extern Hsm_ErrType Hsm_AesEncInit(boolean blAsync, Hsm_CallbackPtr pCallback,
  Hsm_DataType ddDataType, Hsm_DataIDType ddDataID, Hsm_AesModeType ddAesMode,
  const uint8* pInitVector);
extern Hsm_ErrType Hsm_AesEncUpdate(boolean blAsync, Hsm_CallbackPtr pCallback,
  Hsm_AesModeType ddAesMode, const uint8* pPlainText, uint32 ulPlainTextLength,
  uint8* pCipherText, uint32* pCipherTextLength);
extern Hsm_ErrType Hsm_AesEncFinish(boolean blAsync, Hsm_CallbackPtr pCallback,
  Hsm_AesModeType ddAesMode);
extern Hsm_ErrType Hsm_AesDecInit(boolean blAsync, Hsm_CallbackPtr pCallback,
  Hsm_DataType ddDataType, Hsm_DataIDType ddDataID, Hsm_AesModeType ddAesMode,
  const uint8* pInitVector);
extern Hsm_ErrType Hsm_AesDecUpdate(boolean blAsync, Hsm_CallbackPtr pCallback,
  Hsm_AesModeType ddAesMode, const uint8* pCipherText, uint32 ulCipherTextLength,
  uint8* pPlainText, uint32* pPlainTextLength);
extern Hsm_ErrType Hsm_AesDecFinish(boolean blAsync, Hsm_CallbackPtr pCallback,
  Hsm_AesModeType ddAesMode);

/* Asymmetric */
extern Hsm_ErrType Hsm_RsaEncInit(boolean blAsync, Hsm_CallbackPtr pCallback,
  Hsm_DataType ddDataType, Hsm_DataIDType ddDataID);
extern Hsm_ErrType Hsm_RsaEncUpdate(boolean blAsync, Hsm_CallbackPtr pCallback,
  const uint8* pPlainText, uint32 ulPlainTextLength,
  uint8* pCipherText, uint32* pCipherTextLength);
extern Hsm_ErrType Hsm_RsaEncFinish(boolean blAsync, Hsm_CallbackPtr pCallback);
extern Hsm_ErrType Hsm_RsaDecInit(boolean blAsync, Hsm_CallbackPtr pCallback,
  Hsm_DataType ddDataType, Hsm_DataIDType ddDataID);
extern Hsm_ErrType Hsm_RsaDecUpdate(boolean blAsync, Hsm_CallbackPtr pCallback,
  const uint8* pCipherText, uint32 ulCipherTextLength,
  uint8* pPlainText, uint32* pPlainTextLength);
extern Hsm_ErrType Hsm_RsaDecFinish(boolean blAsync, Hsm_CallbackPtr pCallback);
extern Hsm_ErrType Hsm_EciesEncInit(boolean blAsync, Hsm_CallbackPtr pCallback,
  Hsm_DataType ddPrivateKeyADataType, Hsm_DataIDType ddPrivateKeyADataID,
  Hsm_DataType ddPublicKeyADataType, Hsm_DataIDType ddPublicKeyADataID,
  Hsm_DataType ddPublicKeyBDataType, Hsm_DataIDType ddPublicKeyBDataID);
extern Hsm_ErrType Hsm_EciesEncUpdate(boolean blAsync, Hsm_CallbackPtr pCallback,
  uint8* pMessage, uint32 ulMessageLength, uint8* pParam1, uint8 ucEncMode,
  void* pPdu);
extern Hsm_ErrType Hsm_EciesEncFinish(boolean blAsync, Hsm_CallbackPtr pCallback);
extern Hsm_ErrType Hsm_EciesDecInit(boolean blAsync, Hsm_CallbackPtr pCallback,
  Hsm_DataType ddDataType, Hsm_DataIDType ddDataID);
extern Hsm_ErrType Hsm_EciesDecUpdate(boolean blAsync, Hsm_CallbackPtr pCallback,
  void* pPdu, const uint8* pParam1, uint8 ucEncMode, uint8* pPlainText);
extern Hsm_ErrType Hsm_EciesDecFinish(boolean blAsync, Hsm_CallbackPtr pCallback);

/* Signature */
extern Hsm_ErrType Hsm_Pkcs1v15GenInit(boolean blAsync,
  Hsm_CallbackPtr pCallback, Hsm_DataType ddDataType, Hsm_DataIDType ddDataID);
extern Hsm_ErrType Hsm_Pkcs1v15GenUpdate(boolean blAsync,
  Hsm_CallbackPtr pCallback, const uint8* pData, uint32 ulDataLength,
  uint32 ulHashType);
extern Hsm_ErrType Hsm_Pkcs1v15GenFinish(boolean blAsync,
  Hsm_CallbackPtr pCallback, uint8* pResult, uint32* pResultLength);
extern Hsm_ErrType Hsm_Pkcs1v15VerInit(boolean blAsync,
  Hsm_CallbackPtr pCallback, Hsm_DataType ddDataType, Hsm_DataIDType ddDataID);
extern Hsm_ErrType Hsm_Pkcs1v15VerUpdate(boolean blAsync,
  Hsm_CallbackPtr pCallback, const uint8* pData,
  uint32 ulDataLength, uint32 ulHashType);
extern Hsm_ErrType Hsm_Pkcs1v15VerFinish(boolean blAsync,
  Hsm_CallbackPtr pCallback, const uint8* pSignature, uint32 ulSignatureLength,
  uint8* pResult);
extern Hsm_ErrType Hsm_Pkcs1PssGenInit(boolean blAsync,
  Hsm_CallbackPtr pCallback, Hsm_DataType ddDataType, Hsm_DataIDType ddDataID);
extern Hsm_ErrType Hsm_Pkcs1PssGenUpdate(boolean blAsync,
  Hsm_CallbackPtr pCallback, const uint8* pData, uint32 ulDataLength,
  uint32 ulHashType, const uint8* pSalt, uint32 ulSaltLength);
extern Hsm_ErrType Hsm_Pkcs1PssGenFinish(boolean blAsync,
  Hsm_CallbackPtr pCallback, uint8* pResult, uint32* pResultLength);
extern Hsm_ErrType Hsm_Pkcs1PssVerInit(boolean blAsync,
  Hsm_CallbackPtr pCallback, Hsm_DataType ddDataType, Hsm_DataIDType ddDataID);
extern Hsm_ErrType Hsm_Pkcs1PssVerUpdate(boolean blAsync,
  Hsm_CallbackPtr pCallback, const uint8* pData,
  uint32 ulDataLength, uint32 ulHashType, uint32 ulSaltLength);
extern Hsm_ErrType Hsm_Pkcs1PssVerFinish(boolean blAsync,
  Hsm_CallbackPtr pCallback, const uint8* pSignature, uint32 ulSignatureLength,
  uint8* pResult);
extern Hsm_ErrType Hsm_EcdsaGenInit(boolean blAsync,
  Hsm_CallbackPtr pCallback, Hsm_DataType ddDataType, Hsm_DataIDType ddDataID);
extern Hsm_ErrType Hsm_EcdsaGenUpdate(boolean blAsync,
  Hsm_CallbackPtr pCallback, const uint8* pData, uint32 ulDataLength,
  uint32 ulHashType, const uint8* pSecretNumber, uint32 ulSecretNumberLength);
extern Hsm_ErrType Hsm_EcdsaGenFinish(boolean blAsync,
  Hsm_CallbackPtr pCallback, uint8* pSignatureR, uint8* pSignatureS,
  uint32* pSignatureLength);
extern Hsm_ErrType Hsm_EcdsaVerInit(boolean blAsync,
  Hsm_CallbackPtr pCallback, Hsm_DataType ddDataType, Hsm_DataIDType ddDataID);
extern Hsm_ErrType Hsm_EcdsaVerUpdate(boolean blAsync,
  Hsm_CallbackPtr pCallback, const uint8* pData, uint32 ulDataLength,
  uint32 ulHashType);
extern Hsm_ErrType Hsm_EcdsaVerFinish(boolean blAsync,
  Hsm_CallbackPtr pCallback, const uint8* pSignatureR, const uint8* pSignatureS,
  uint32 ulSignatureLength, uint8* pResult);

/* Key Derivation */
extern Hsm_ErrType Hsm_Pbkdf2Init(boolean blAsync,
  Hsm_CallbackPtr pCallback, uint32 ulKeyLength, uint32 ulIterations);
extern Hsm_ErrType Hsm_Pbkdf2Update(boolean blAsync,
  Hsm_CallbackPtr pCallback, const uint8* pPasswordPtr, uint32 ulPasswordLength,
  const uint8* pSaltPtr, uint32 ulSaltLength);
extern Hsm_ErrType Hsm_Pbkdf2Finish(boolean blAsync,
  Hsm_CallbackPtr pCallback, uint8* pDerivedKey, uint32 ulDerivedKeyLength);

/* Key Exchange */
extern Hsm_ErrType Hsm_EcdhInit(boolean blAsync,
  Hsm_CallbackPtr pCallback, Hsm_DataType ddDataType, Hsm_DataIDType ddDataID);
extern Hsm_ErrType Hsm_EcdhUpdate(boolean blAsync,
  Hsm_CallbackPtr pCallback, Hsm_DataType ddDataType, Hsm_DataIDType ddDataID);
extern Hsm_ErrType Hsm_EcdhFinish(boolean blAsync,
  Hsm_CallbackPtr pCallback, uint8* pSharedSecret, uint32 ulSharedSecretLength);

/* Secure Data */
extern Hsm_ErrType Hsm_LoadData(Hsm_DataType ddDataType,
  Hsm_DataIDType ddDataID, uint32 ulDataLength, uint8* pRawData);
extern Hsm_ErrType Hsm_LoadRamKey(Hsm_DataType ddDataType,
  Hsm_DataIDType ddDataID, uint32 ulKeyLength, const uint8* pRawData);
extern Hsm_ErrType Hsm_CheckSecureData(Hsm_DataType ddDataType,
  Hsm_DataIDType ddDataID);

/* Secure Debug */
extern Hsm_ErrType Hsm_EnableSecureDebug(void);
extern Hsm_ErrType Hsm_ControlDebug(Hsm_DebugControlType ddControl);
extern Hsm_ErrType Hsm_DebugStatus(boolean* pHsmDebugEnabled,
  boolean* pHostDebugEnabled);

/* Control for flash */
extern Hsm_ErrType Hsm_ControlPIT(boolean blStart);
extern Hsm_ErrType Hsm_ControlForFlash(boolean blStart);

#endif /* ((CRYPTOLIB_SUPORT_HSM_SPC58X == STD_ON) || (CRYPTOLIB_SUPORT_HSM_ICUM == STD_ON)) */

#endif /* HSM_AUTINTDRIVER_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
