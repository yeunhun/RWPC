/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dummy_HaeCryptoLib.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Dummy CryptoLib library                                       **
**                                                                            **
**  PURPOSE   : Source file for dummy code                                    **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
/* CryptoLib library dummy header file */
#include "Dummy_HaeCryptoLib.h"

/*******************************************************************************
**                        Global Function Definitions                         **
*******************************************************************************/
/* APIs that should not be used when using actual libraries */
/* Dummy function definitions in the CryptoLib library API commonly used in RTSW and FBL */

/* Hmg_Common.h */
uint32 Hmg_GetVersionInfo()
{
  return 0;
}
void Hmg_SetCallbackFunc(Hmg_CallbackFunc callbackFunc)
{
}
void Hmg_ExecCallback(void)
{
}

/* Hmg_Aes.h */
boolean Hmg_AesSetKey(
  HMG_OUT HmgAeskeyCtx* aesCtx,
  HMG_IN uint8* key,
  HMG_IN uint8 keylen
  )
{
  return HMG_FAILURE;
}

boolean Hmg_AesEcbEnc(
  HMG_INOUT HmgAeskeyCtx* aesCtx,
  HMG_OUT uint8* cipher,
  HMG_IN uint8* plain,
  HMG_IN uint32 plainLen
  )
{
  return HMG_FAILURE;
}
boolean Hmg_AesEcbDec(
  HMG_INOUT HmgAeskeyCtx* aesCtx,
  HMG_OUT uint8* plain,
  HMG_IN uint8* cipher,
  HMG_IN uint32 cipherLen
  )
{
  return HMG_FAILURE;
}

boolean Hmg_AesCbcEnc(
  HMG_INOUT HmgAeskeyCtx* aesCtx,
  HMG_INOUT uint8 iv[],
  HMG_OUT uint8* cipher,
  HMG_IN uint8* plain,
  HMG_IN uint32 plainLen
  )
{
  return HMG_FAILURE;
}
boolean Hmg_AesCbcDec(
  HMG_INOUT HmgAeskeyCtx* aesCtx,
  HMG_INOUT uint8 iv[],
  HMG_OUT uint8* plain,
  HMG_IN uint8* cipher,
  HMG_IN uint32 cipherLen
  )
{
  return HMG_FAILURE;
}

boolean Hmg_AesCtrStart(
	HMG_INOUT HmgAesCtrCtx* aesCtrCtx,
	HMG_IN uint8 iv[],
	HMG_IN uint8 key[],
	HMG_IN uint8 keyLen
	)
{
  return HMG_FAILURE;
}
boolean Hmg_AesCtrUpdate(
	HMG_INOUT HmgAesCtrCtx* aesCtrCtx,
	HMG_OUT uint8* out,
	HMG_IN uint8* in,
	HMG_IN uint32 inLen
	)
{
  return HMG_FAILURE;
}
boolean Hmg_AesCtrFinish(
	HMG_INOUT HmgAesCtrCtx* aesCtrCtx,
	HMG_OUT uint32* totalLen
	)
{
  return HMG_FAILURE;
}
boolean Hmg_AesCtr(
  HMG_INOUT HmgAeskeyCtx* aesCtx,
  HMG_INOUT uint8 iv[],
  HMG_OUT uint8* out,
  HMG_IN uint8* in,
  HMG_IN uint32 inLen
  )
{
  return HMG_FAILURE;
}

boolean Hmg_AesCmacStart(
  HMG_INOUT HmgAesCmacCtx *cmacCtx,
  HMG_IN uint8 *key,
  HMG_IN uint8  keyLen
  )
{
  return HMG_FAILURE;
}
boolean Hmg_AesGcmEnc(
	HMG_OUT uint8 *cipher,
	HMG_OUT uint8 tag[HMG_GCM_TAG_SIZE],
	HMG_IN HmgAesGcmCtx *gcmCtx
	)
{
  return HMG_FAILURE;
}
boolean Hmg_AesGcmDec(
	HMG_OUT uint8 *plain,
	HMG_IN uint8 tag[HMG_GCM_TAG_SIZE],
	HMG_IN HmgAesGcmCtx *gcmCtx
	)
{
  return HMG_FAILURE;
}
boolean Hmg_AesCmacUpdate(
  HMG_INOUT HmgAesCmacCtx *cmacCtx,
  HMG_IN uint8 *msg,
  HMG_IN uint32 msgLen
  )
{
  return HMG_FAILURE;
}
boolean Hmg_AesCmacFinish(
  HMG_INOUT HmgAesCmacCtx *cmacCtx,
  HMG_OUT uint8 tag[16]
  )
{
  return HMG_FAILURE;
}
boolean Hmg_AesCmac(
  HMG_OUT uint8 tag[HMG_AES_CMAC_TAG_LEN],
  HMG_IN uint8 *key,
  HMG_IN uint8 keyLen,
  HMG_IN uint8 *msg,
  HMG_IN uint32 msgLen
  )
{
  return HMG_FAILURE;
}

/* Hmg_Ecc.h */
 boolean Hmg_EcckeyGenerate(
	HMG_OUT HmgEcPublickey*	publickey,
	HMG_IN  uint8			privatekey[]
	)
 {
   return HMG_FAILURE;
 }
boolean Hmg_EccEcdhStart(
	HMG_INOUT HmgEccSliceCtx* Ecc_ctx,
	HMG_IN uint8* privatekeyA,
	HMG_IN HmgEcPublickey* publickeyB
	)
{
  return HMG_FAILURE;
}
boolean Hmg_EccEcdhUpdate(
	HMG_INOUT HmgEccSliceCtx* Ecc_ctx
	)
{
  return HMG_FAILURE;
}
boolean Hmg_EccEcdhFinish(
	HMG_INOUT HmgEccSliceCtx* Ecc_ctx,
	HMG_OUT uint8* secretValue
	)
{
  return HMG_FAILURE;
}
boolean Hmg_EccEcdh(
	HMG_OUT uint8			secretValue[],
	HMG_IN	uint8			privatekeyA[],
	HMG_IN	HmgEcPublickey*	publickeyB
	)
{
  return HMG_FAILURE;
}

boolean Hmg_EccEcdsaSignStart(
	HMG_INOUT HmgEccSliceCtx* Ecc_ctx,
	HMG_IN	uint8* secretNumber
	)
{
  return HMG_FAILURE;
}
boolean Hmg_EccEcdsaSignUpdate(
	HMG_INOUT HmgEccSliceCtx* Ecc_ctx
	)
{
  return HMG_FAILURE;
}
boolean Hmg_EccEcdsaSignFinish(
	HMG_INOUT HmgEccSliceCtx* Ecc_ctx,
	HMG_OUT HmgEcdsaSign* signature,
	HMG_IN  uint8* hashedMessage,
	HMG_IN	uint8* privatekey
	)
{
  return HMG_FAILURE;
}
boolean Hmg_EccEcdsaSign(
  HMG_OUT HmgEcdsaSign*   signature,
  HMG_IN  uint8     hashedMessage[],
  HMG_IN  uint8     secretNumber[],
  HMG_IN  uint8     privatekey[]
  )
{
  return HMG_FAILURE;
}

boolean Hmg_EccEcdsaVerifyStart(
	HMG_INOUT HmgEccSliceCtx* Ecc_ctx,
	HMG_IN HmgEcdsaSign* signature,
	HMG_IN uint8* hashedMessage,
	HMG_IN HmgEcPublickey* publickey
	)
{
  return HMG_FAILURE;
}
boolean Hmg_EccEcdsaVerifyUpdate(
	HMG_INOUT HmgEccSliceCtx* Ecc_ctx
	)
{
  return HMG_FAILURE;
}
boolean Hmg_EccEcdsaVerifyFinish(
	HMG_INOUT HmgEccSliceCtx* Ecc_ctx
	)
{
  return HMG_FAILURE;
}
boolean Hmg_EccEcdsaVerify(
	HMG_IN HmgEcdsaSign*	signature,
	HMG_IN uint8			hashedMessage[],
	HMG_IN HmgEcPublickey*	publickey
	)
{
  return HMG_FAILURE;
}

/* Hmg_Ecies.h */
boolean Hmg_EciesEncryptStart(
  HMG_INOUT HmgEccSliceCtx* slCtx,
  HMG_IN uint8* privateKeyA,
  HMG_IN HmgEcPublickey* publicKeyB
  )
{
  return HMG_FAILURE;
}
boolean Hmg_EciesEncryptUpdate(
  HMG_INOUT HmgEccSliceCtx* slCtx
  )
{
  return HMG_FAILURE;
}
boolean Hmg_EciesEncryptFinish(
	HMG_INOUT HmgEccSliceCtx* slCtx,
	HMG_OUT HmgEcies_sPDU* sPdu,
	HMG_IN HmgEcPublickey*	publicKeyA,
	HMG_IN uint8* message,
	HMG_IN uint32 mLen,
	HMG_IN uint8* param1,
	HMG_IN uint8 encMode
	)
{
  return HMG_FAILURE;
}
boolean Hmg_EciesEncrypt(
	HMG_OUT HmgEcies_sPDU* sPdu,
	HMG_IN uint8*	privateKeyA,
	HMG_IN HmgEcPublickey* publicKeyA,
	HMG_IN HmgEcPublickey* publicKeyB,
	HMG_IN uint8*	message,
	HMG_IN uint32	mLen,
	HMG_IN uint8*	param1,
	HMG_IN uint8	encMode
	)
{
  return HMG_FAILURE;
}

boolean Hmg_EciesDecryptStart(
  HMG_INOUT HmgEccSliceCtx* slCtx,
  HMG_IN uint8* privKey,
  HMG_IN HmgEcPublickey* pubKey
  )
{
  return HMG_FAILURE;
}
boolean Hmg_EciesDecryptUpdate(
  HMG_INOUT HmgEccSliceCtx* slCtx
  )
{
  return HMG_FAILURE;
}
boolean Hmg_EciesDecryptFinish(
	HMG_INOUT HmgEccSliceCtx* slCtx, 
	HMG_OUT uint8* decMessage, 
	HMG_IN	HmgEcies_sPDU* sPdu,
	HMG_IN uint8* param1, 
	HMG_IN uint8 encMode
	)
{
  return HMG_FAILURE;
}
boolean Hmg_EciesDecrypt(
	HMG_OUT uint8*		decMessage,
	HMG_IN HmgEcies_sPDU*	sPdu,
	HMG_IN uint8*		privKey,
	HMG_IN uint8*		param1,
	HMG_IN uint8		encMode
	)
{
  return HMG_FAILURE;
}

/* Hmg_HmacSha160.h */
boolean Hmg_HmacSha160Start(
  HMG_INOUT HmgHmacSha160Ctx* HmacSha160Ctx,
  HMG_IN    uint8*      key, 
  HMG_IN    uint32      keyLen
  )
{
  return HMG_FAILURE;
} 
boolean Hmg_HmacSha160Update(
  HMG_INOUT HmgHmacSha160Ctx* HmacSha160Ctx,
  HMG_IN    uint8*      data, 
  HMG_IN    uint32      dataLen
  )
{
  return HMG_FAILURE;
}
boolean Hmg_HmacSha160Finish(
  HMG_INOUT HmgHmacSha160Ctx* HmacSha160Ctx,
  HMG_OUT uint8 hmacValue[]
  )
{
  return HMG_FAILURE;
}
boolean Hmg_HmacSha160(
	HMG_OUT uint8 hmacValue[],
	HMG_IN uint8* key,
	HMG_IN uint32 keyLen,
	HMG_IN uint8* data,
	HMG_IN uint32 dataLen
	)
{
  return HMG_FAILURE;
}

/* Hmg_HmacSha256.h */

/* Hmg_HmacSha256.h */
boolean Hmg_HmacSha224Start(
	HMG_INOUT	HmgHmacSha224Ctx*	HmacSha224Ctx,
	HMG_IN		uint8*				key,
	HMG_IN		uint32				keyLen
	)
{
  return HMG_FAILURE;
}
boolean Hmg_HmacSha224Update(
	HMG_INOUT	HmgHmacSha224Ctx*	HmacSha224Ctx,
	HMG_IN		uint8*				data,
	HMG_IN		uint32				dataLen
	)
{
  return HMG_FAILURE;
}
boolean Hmg_HmacSha224Finish(
	HMG_INOUT	HmgHmacSha224Ctx*	HmacSha224Ctx,
	HMG_OUT		uint8				hmacValue[]
	)
{
  return HMG_FAILURE;
}
boolean Hmg_HmacSha256Start(
  HMG_INOUT HmgHmacSha256Ctx* HmacSha256Ctx,
  HMG_IN    uint8*        key,
  HMG_IN    uint32        keyLen
  )
{
  return HMG_FAILURE;
}
boolean Hmg_HmacSha256Update(
  HMG_INOUT HmgHmacSha256Ctx*   HmacSha256Ctx,
  HMG_IN    uint8*        data,
  HMG_IN    uint32        dataLen
  )
{
  return HMG_FAILURE;
}
boolean Hmg_HmacSha256Finish(
  HMG_INOUT HmgHmacSha256Ctx* HmacSha256Ctx,
  HMG_OUT   uint8       hmacValue[]
  )
{
  return HMG_FAILURE;
}
boolean Hmg_HmacSha256(
	HMG_OUT uint8	hmacValue[],
	HMG_IN	uint8*	key,
	HMG_IN	uint32	keyLen,
	HMG_IN	uint8*	data,
	HMG_IN	uint32	dataLen
	)
{
  return HMG_FAILURE;
}

/* Hmg_Pbkdf2.h */
boolean Hmg_PBKDF2(
	HMG_OUT uint8 *derivedkey,
	HMG_IN uint32 dkLen,
	HMG_IN uint8 *password,
	HMG_IN uint32 pLen,
	HMG_IN uint8 *salt,
	HMG_IN uint32 sLen,
	HMG_IN uint32 icount
	)
{
  return HMG_FAILURE;
}

/* Hmg_Pkcs1.h */
//void Hmg_Srand(uint32 seed)
//{
//	return;
//}
//uint32 Hmg_rand(void)
//{
//	return 0;
//}

boolean Hmg_RsaPkcs1v15SignStart(
  HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
  HMG_IN  uint8* pDigest,
  HMG_IN uint32 hashAlgorithm,
  HMG_IN HmgRsaPrivatekey* privatekey
  )
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1v15SignUpdate(
  HMG_INOUT HmgRsaSliceCtx* rsa_ctx
  )
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1v15SignFinish(
  HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
  HMG_OUT uint8* pSign
  )
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1v15Sign(
  HMG_OUT uint8 pSign[],
  HMG_IN  uint8* pDigest,
  HMG_IN uint32 hashAlgorithm,
  HMG_IN HmgRsaPrivatekey* privatekey
  )
{
  return HMG_FAILURE;
}

boolean Hmg_RsaPkcs1v15VerifyStart(
  HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
  HMG_IN uint8* pSign,
  HMG_IN HmgRsaPublickey* publickey
  )
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1v15VerifyUpdate(
  HMG_INOUT HmgRsaSliceCtx* rsa_ctx
  )
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1v15VerifyFinish(
  HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
  HMG_IN uint8* pDigest,
  HMG_IN uint32 hashAlgorithm
  )
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1v15Verify(
  HMG_IN uint8 pSign[],
  HMG_IN uint8* pDigest,
  HMG_IN uint32 hashAlgorithm,
  HMG_IN HmgRsaPublickey* publickey
  )
{
  return HMG_FAILURE;
}

extern boolean Hmg_RsaPkcs1PssSignStart(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_IN HmgPkcs1PssCtx* pssCtx,
	HMG_IN HmgRsaPrivatekey* privatekey
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1PssSignUpdate(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1PssSignFinish(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_OUT uint8* pSign
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1PssSign(
	HMG_OUT uint8 pSign[],
	HMG_IN HmgPkcs1PssCtx* pssCtx,
	HMG_IN HmgRsaPrivatekey* privatekey
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1PssVerifyStart(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_IN uint8* pSign,
	HMG_IN HmgRsaPublickey* publickey
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1PssVerifyUpdate(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1PssVerifyFinish(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_IN HmgPkcs1PssCtx* pssCtx
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1PssVerify(
	HMG_IN uint8 pSign[],
	HMG_IN HmgPkcs1PssCtx* pssCtx,
	HMG_IN HmgRsaPublickey* publickey
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1v15EncryptStart(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_IN uint8* msg,
	HMG_IN uint32 mLen,
	HMG_IN HmgRsaPublickey* publickey
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1v15EncryptUpdate(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1v15EncryptFinish(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_OUT uint8* cipher
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1v15Encrypt(
	HMG_OUT uint8 cipher[],
	HMG_IN uint8* msg,
	HMG_IN uint32 mLen,
	HMG_IN HmgRsaPublickey* publickey
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1v15DecryptStart(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_IN uint8* cipher,
	HMG_IN HmgRsaPrivatekey* privatekey
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1v15DecryptUpdate(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1v15DecryptFinish(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_OUT uint8* msg,
	HMG_OUT uint32* mLen
	)
{
  return HMG_FAILURE;
}
extern boolean Hmg_RsaPkcs1v15Decrypt(
	HMG_OUT uint8* msg,
	HMG_OUT uint32* mLen,
	HMG_IN uint8 cipher[],
	HMG_IN HmgRsaPrivatekey* privatekey
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1OaepEncryptStart(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_IN  uint8* msg,
	HMG_IN uint32 mLen,
	HMG_IN HmgPkcs1OaepCtx *oaepCtx,
	HMG_IN HmgRsaPublickey* publickey
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1OaepEncryptUpdate(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1OaepEncryptFinish(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_OUT uint8* cipher
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1OaepEncrypt(
	HMG_OUT uint8 cipher[],
	HMG_IN  uint8* msg,
	HMG_IN uint32 mLen,
	HMG_IN HmgPkcs1OaepCtx *oaepCtx,
	HMG_IN HmgRsaPublickey* publickey
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1OaepDecryptStart(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_IN  uint8* cipher,
	HMG_IN HmgRsaPrivatekey* privatekey
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1OaepDecryptUpdate(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1OaepDecryptFinish(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_OUT uint8* msg,
	HMG_OUT uint32* mLen,
	HMG_IN HmgPkcs1OaepCtx *oaepCtx
	)
{
  return HMG_FAILURE;
}
boolean Hmg_RsaPkcs1OaepDecrypt(
	HMG_OUT uint8* msg,
	HMG_OUT uint32* mLen,
	HMG_IN  uint8 cipher[],
	HMG_IN HmgPkcs1OaepCtx *oaepCtx,
	HMG_IN HmgRsaPrivatekey* privatekey
	)
{
  return HMG_FAILURE;
}
/*Hmg_DiffieHellman.h*/
boolean Hmg_DiffieHellmanKeypairGen(
	HMG_INOUT  HmgPrngCtx* prngCtx,
	HMG_OUT uint8 publicValue[],
	HMG_INOUT uint8 privateValue[],
	HMG_IN  uint8 baseG[],
	HMG_IN  uint8 primeP[]
	)
{
  return HMG_FAILURE;
}
boolean Hmg_DiffieHellmanSharedvalueGen(
	HMG_OUT uint8 secretValue[],
	HMG_IN  uint8 publicValue[],
	HMG_IN  uint8 privateValue[],
	HMG_IN  uint8 primeP[]
	)
{
  return HMG_FAILURE;
}

/* Hmg_Prng.h */
void Hmg_PrngInit(
  HMG_INOUT HmgPrngCtx *hpc
  )
{
}
void Hmg_PrngReseed(
  HMG_INOUT HmgPrngCtx *hpc,
  HMG_IN uint8 entropy[HMG_ENTROPY_LEN]
  )
{
}
boolean Hmg_PrngGetRand(
  HMG_INOUT HmgPrngCtx *hpc,
  HMG_OUT uint8 *rndout,
  HMG_IN  uint32  len
  )
{
  return HMG_FAILURE;
}

/* Hmg_Rsa.h */
boolean Hmg_RsaModExponentLongStart(
  HMG_INOUT HmgRsaSliceCtx* rsaCtx,
  HMG_IN uint8* pEM,
  HMG_IN HmgRsaPrivatekey* Privatekey
  )
{
  return HMG_FAILURE;
}
boolean Hmg_RsaModExponentLongUpdate(
  HMG_INOUT HmgRsaSliceCtx* rsaCtx
  )
{
  return HMG_FAILURE;
}
boolean Hmg_RsaModExponentLongFinish(
  HMG_INOUT HmgRsaSliceCtx* rsaCtx,
  HMG_OUT uint8* pCM
  )
{
  return HMG_FAILURE;
}
boolean Hmg_RsaModExponentLong(
  HMG_OUT uint8 pCM[],
  HMG_IN uint8 pEM[],
  HMG_IN HmgRsaPrivatekey* Privatekey
  )
{
  return HMG_FAILURE;
}

boolean Hmg_RsaModExponentStart(
  HMG_INOUT HmgRsaSliceCtx *rsaCtx,
  HMG_IN uint8* pEM,
  HMG_IN HmgRsaPublickey* Publickey
  )
{
  return HMG_FAILURE;
}
boolean Hmg_RsaModExponentUpdate(
  HMG_INOUT HmgRsaSliceCtx *rsaCtx
  )
{
  return HMG_FAILURE;
}
boolean Hmg_RsaModExponentFinish(
  HMG_INOUT HmgRsaSliceCtx *rsaCtx,
  HMG_OUT uint8* pCM
  )
{
  return HMG_FAILURE;
}
boolean Hmg_RsaModExponent(
  HMG_OUT uint8 pCM[],
  HMG_IN uint8 pEM[],
  HMG_IN HmgRsaPublickey* Publickey
  )
{
  return HMG_FAILURE;
}

/* Hmg_Sha160.h */
boolean Hmg_Sha160Start(
  HMG_INOUT HmgSha160Ctx* sha160Ctx
  )
{
  return HMG_FAILURE;
}
boolean Hmg_Sha160Update(
  HMG_INOUT HmgSha160Ctx* sha160Ctx, 
  HMG_IN    uint8*    data, 
  HMG_IN    uint32    dataLen
  )
{
  return HMG_FAILURE;
}
boolean Hmg_Sha160Finish(
  HMG_INOUT HmgSha160Ctx* sha160Ctx,
  HMG_OUT   uint8   digest[]
  )
{
  return HMG_FAILURE;
}
boolean Hmg_Sha160(
	HMG_OUT		uint8		digest[],
	HMG_IN		uint8*		data,
	HMG_IN		uint32		dataLen
	)
{
  return HMG_FAILURE;
}

/* Hmg_Sha256.h */
boolean Hmg_Sha256Start(
  HMG_INOUT HmgSha256Ctx* sha256Ctx
  )
{
  return HMG_FAILURE;
}
boolean Hmg_Sha256Update(
  HMG_INOUT HmgSha256Ctx* sha256Ctx,
  HMG_IN    uint8*    data,
  HMG_IN    uint32    dataLen
  )
{
  return HMG_FAILURE;
}
boolean Hmg_Sha256Finish(
  HMG_INOUT HmgSha256Ctx* sha256Ctx,
  HMG_OUT   uint8   digest[]
  )
{
  return HMG_FAILURE;
}
boolean Hmg_Sha256(
	HMG_OUT		uint8		digest[],
	HMG_IN		uint8*		data,
	HMG_IN		uint32		dataLen
	)
{
  return HMG_FAILURE;
}

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
