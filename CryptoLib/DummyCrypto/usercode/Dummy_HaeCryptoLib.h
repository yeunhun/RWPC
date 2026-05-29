/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dummy_HaeCryptoLib.h                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Dummy CryptoLib library                                       **
**                                                                            **
**  PURPOSE   : Header file for dummy code                                    **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.1     18-Nov-2019   Sinil        Redmine #20294                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef DUMMY_HAECRYPTOLIB_H
#define DUMMY_HAECRYPTOLIB_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
/* Hmg_Common.h */
/** BOOL value true. */
#define HMG_SUCCESS			(0U)
/** BOOL value False. */
#define HMG_FAILURE			(1U)
/** Error type invalid value  */
#define HMG_NO_FUNCTION		(2U)
/** Error type invalid value  */
#define HMG_INVALID_VALUE	(3U)
/** Error type invalid length  */
#define HMG_INVALID_LENGTH	(4U)
/** BOOL value working fuction. */
#define HMG_WORK_SLICING	(5U)

#define HMG_NULL	(void *)0

/** \brief Parameter Prefix Type*/
#ifndef HMG_IN
/** parameter Input */
#define HMG_IN const
#endif
#ifndef HMG_OUT	
/** parameter Output */
#define HMG_OUT	
#endif
#ifndef HMG_INOUT
/** parameter Inout */
#define HMG_INOUT	
#endif

/* Hmg_Config.h */
#define HMG_RSA_BIT_SIZE 2048U 				/* rsa algorithm bit length size */

/* Hmg_Aes.h */
#define HMG_AES_N_BLOCK					16U
#define HMG_AES_N_ROUND					14U
#define HMG_AES_CMAC_TAG_LEN			16U
#define HMG_GCM_TAG_SIZE	16U

/* Hmg_Ecc.h */
#define HMG_ECC_BYTES_SIZE		 32U
#define HMG_ECC_WORDS_SIZE		  8U

/* Hmg_Ecies.h */
#define HMG_ECIES_TAG_BYTES			16U
#define HMG_ECIES_MSG_MAX_BYTES		32U

/* Hmg_Sha160.h */
/** Length of hash block in byte. */
#define HMG_SHA160_BLOCK_SIZE		64U
/** Length of digest in byte. */
#define HMG_SHA160_DIGEST_SIZE		20U

/* Hmg_Sha256.h */
/** Length of hash block in byte. */
#define HMG_SHA256_BLOCK_SIZE			64U
/** Length of digest in byte. */
#define HMG_SHA256_DIGEST_SIZE			32U
#define HMG_SHA224_DIGEST_SIZE			28U

/* Hmg_Rsa.h */
/** \brief rsa algorithm byte length size */
#define HMG_RSA_BYTES_SIZE  (HMG_RSA_BIT_SIZE / 8U)
/** \brief rsa algorithm Dword length size */
#define HMG_RSA_DWORD_SIZE (HMG_RSA_BIT_SIZE / 32U)

/* Hmg_Pkcs1.h */
#define HMG_SHA_160			(1U)
#define HMG_SHA_224			(2U)
#define HMG_SHA_256			(3U)
#define HMG_SHA_384			(4U)
#define HMG_SHA_512			(5U)
#define HMG_SHA_512_224		(6U)
#define HMG_SHA_512_256		(7U)

//#define HMG_SRAND(s)	Hmg_Srand(s)
//#define HMG_RAND		Hmg_rand()

//void Hmg_Srand(uint32 seed);
//uint32 Hmg_rand(void);

/* Hmg_Prng.h */
/** \brief Entropy length for Hmg_PrngReseed */
#define HMG_ENTROPY_LEN		16u
/** \brief Rand key size in prng context */
#define HMG_RND_KEY_SIZE	32u
/** \brief State size in prng context */
#define HMG_RND_STATE_SIZE	16u

/* Hmg_Config.h */
#define HMG_ENABLE_SLICE

/*Hmg_Sha512.h*/
#define HMG_SHA512_DIGEST_SIZE			 64U

/*******************************************************************************
**                                Data Types                                  **
*******************************************************************************/
/* Hmg_Common.h */
#ifndef uint8_defined
	typedef unsigned char		uint8;
	#define uint8_defined
#endif

#ifndef uint16_defined
	typedef unsigned short		uint16;
	#define uint16_defined
#endif

#ifndef uint32_defined
  typedef unsigned long       uint32;
	#define uint32_defined
#endif

#ifndef boolean_defined
  typedef unsigned char       boolean;
  #define boolean_defined
#endif

typedef void (*Hmg_CallbackFunc)(void);

/*******************************************************************************
**                               Enumerations                                 **
*******************************************************************************/

/*******************************************************************************
**                                Structures                                  **
*******************************************************************************/
/* Hmg_Aes.h */
/** \brief AES context structure */

typedef struct ctAesCtx
{
	uint8 round;	/**< rounds: 10/12/14 decided from key size */
	uint8 opmode;	/**< if cbcmode set on, only final output is return */
	uint8 dummy1;
	uint8 dummy2;
	uint8 ksch[(HMG_AES_N_ROUND + 2U) * (HMG_AES_N_BLOCK)];	/**< key scheduling */
} HmgAeskeyCtx;

typedef struct ctAesCcmCtx {
	uint8 *key;
	uint8 keyLen;
	uint8 *data;
	uint32 dataLen;
	uint8 *assdata;
	uint32 assdataLen;
	uint8 *nonce;
	uint32 nonceLen;
	uint32 tagLen;
} HmgAesCcmCtx;

/** \brief  AES CMAC mode context */
typedef struct ctAesCmacCtx {
	HmgAeskeyCtx aesCtx;
	uint8 macData[HMG_AES_N_BLOCK];
	uint8 block[HMG_AES_N_BLOCK];
	uint32 blockLen;
	uint32 totalLen;
} HmgAesCmacCtx;
typedef struct stHmgAesCtrCtx
{
	HmgAeskeyCtx aeskey;
	uint8 iv[HMG_AES_N_BLOCK];
	uint8 block[HMG_AES_N_BLOCK];
	uint32 blockLen;
	uint32 totalLen;
} HmgAesCtrCtx;
typedef struct ctAesXtsCtx {
	HmgAeskeyCtx keySet1;
	HmgAeskeyCtx keySet2;
} HmgAesXtsCtx;


/* Hmg_Ecc.h */
typedef struct ctEcPublickey{
	uint8 *x;	/**<  Pointer to x */
	uint8 *y;	/**<  Pointer to y */
} HmgEcPublickey;
typedef struct ctEcdsaSign{
  uint8 *r; /**<  Bytes to r */
  uint8 *s; /**<  Bytes to s */
} HmgEcdsaSign;
typedef struct ctEcPoint{
	uint32 x[HMG_ECC_WORDS_SIZE + 1U];
	uint32 y[HMG_ECC_WORDS_SIZE + 1U];
	uint32 z[HMG_ECC_WORDS_SIZE + 1U];
} HmgEcPoint;
typedef struct ctEccSliceCtx{
	uint32  buff_c1[HMG_ECC_WORDS_SIZE + 1U];
	uint32  buff_c2[HMG_ECC_WORDS_SIZE + 1U];
	uint32  buff_c3[HMG_ECC_WORDS_SIZE + 1U];
	HmgEcPoint buff_dst;
	HmgEcPoint buff_src;
	HmgEcPoint buff_tmp;
	uint32 counter;
} HmgEccSliceCtx;

/* Hmg_Ecies.h */
typedef struct {
	const	HmgEcPublickey* pubKey;
	uint32	encMsgLen;
	uint8	encMsg[HMG_ECIES_MSG_MAX_BYTES];
	uint8	macTag[HMG_ECIES_TAG_BYTES];
} HmgEcies_sPDU;

/* Hmg_Sha160.h */
/** \brief Context for Sha1 */
typedef struct ctSha160Ctx{
	uint32 hash[HMG_SHA160_DIGEST_SIZE / 4U];			/**< Hash values H(n)	 							*/
	uint32 block[HMG_SHA160_BLOCK_SIZE / 4U];			/**< Current block									*/
	uint32 blockLen;									/**< Number of bytes in block used					*/
	uint32 dataLenLow;									/**< Total length of the message in byte			*/
} HmgSha160Ctx;

/* Hmg_Sha256.h */
/** \brief Context for Sha256 */
typedef struct ctSha256Ctx{
	uint32	hash[HMG_SHA256_DIGEST_SIZE / 4U];			/**< Hash values H(n)	 			*/
	uint32	block[HMG_SHA256_BLOCK_SIZE / 4U];			/**< Current block					*/
	uint32	blockLen;								/**< Number of bytes in block used	*/
	uint32	dataLenLow;								/**< Total length of the message in byte	*/
	/** uint32	dataLenHigh;							< Total length of the message in byte over 2^32	*/
} HmgSha256Ctx;

/*Hmg_Aes.h*/
typedef struct ctAesGcmCtx {
	uint8 *key;
	uint8 keyLen;
	uint8 *iv;
	uint32 ivLen;
	uint8 *data;
	uint32 dataLen;
	uint8 *aad;
	uint32 aadLen;
} HmgAesGcmCtx;

/* Hmg_HmacSha160.h */
/** \brief Context for HmacSha160 */
typedef struct ctHmacSha160Ctx
{
	HmgSha160Ctx HashCTX;					/**< context of Sha1					*/
	uint8	okeypad[HMG_SHA160_BLOCK_SIZE];	/**< Outer pad(the byte 0x5c repeated)	*/
} HmgHmacSha160Ctx;

/* Hmg_HmacSha256.h */
/** \brief Context for HmacSha256 */

typedef struct ctHmacSha256Ctx
{
	HmgSha256Ctx HashCTX;					/**< context of Sha256					*/
	uint8	okeypad[HMG_SHA256_BLOCK_SIZE];	/**< Outer pad(the byte 0x5c repeated)	*/
} HmgHmacSha256Ctx;
/** \brief Context for HmacSha224 */
typedef HmgHmacSha256Ctx HmgHmacSha224Ctx;
/* Hmg_Rsa.h */
/** \brief Rsa privatekey struct  */
typedef struct{
	uint8 *modulus;		/**< RSA public modulus n = p * q						*/
	uint8 *exponent;	/**< RSA private exponent d = e^(-1) mod (p-1)*(q-1)	*/
} HmgRsaPrivatekey;
/** \brief Rsa public key struct  */
typedef struct{
	uint8 *modulus;		/**< RSA public modulus n = p * q						*/
	uint32 exponent;	/**< RSA public exponent e								*/
} HmgRsaPublickey;
/** \brief Rsa buffer struct for SLICE */
typedef struct{
	uint32 buff_dst[HMG_RSA_DWORD_SIZE + 1U];
	uint32 buff_src[HMG_RSA_DWORD_SIZE + 1U];
	uint32 buff_mod[HMG_RSA_DWORD_SIZE + 1U];
	uint32 buff_mul[(HMG_RSA_DWORD_SIZE + 1U) * 2U];
	uint32 nprimez;
	uint32 counter;
	uint8  pubExp[4];
	uint8* pExp;
	uint32 emLen;
} HmgRsaSliceCtx;

/* Hmg_Prng.h */
/** \brief Context for Hmg PRNG */
typedef struct ctPrngCtx{
	uint8 state[HMG_RND_STATE_SIZE];
	uint8 rndkey[HMG_RND_KEY_SIZE];
	uint32 reseedCnt;
} HmgPrngCtx;

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
/* Hmg_Common.h */
extern uint32 Hmg_GetVersionInfo();
extern void Hmg_SetCallbackFunc(Hmg_CallbackFunc callbackFunc);
extern void Hmg_ExecCallback(void);

/* Hmg_Aes.h */

extern boolean Hmg_AesSetKey(
  HMG_OUT HmgAeskeyCtx* aesCtx,
  HMG_IN uint8* key,
  HMG_IN uint8 keylen
  );

extern boolean Hmg_AesEcbEnc(
  HMG_INOUT HmgAeskeyCtx* aesCtx,
  HMG_OUT uint8* cipher,
  HMG_IN uint8* plain,
  HMG_IN uint32 plainLen
  );
extern boolean Hmg_AesEcbDec(
  HMG_INOUT HmgAeskeyCtx* aesCtx,
  HMG_OUT uint8* plain,
  HMG_IN uint8* cipher,
  HMG_IN uint32 cipherLen
  );

extern boolean Hmg_AesCbcEnc(
  HMG_INOUT HmgAeskeyCtx* aesCtx,
  HMG_INOUT uint8 iv[],
  HMG_OUT uint8* cipher,
  HMG_IN uint8* plain,
  HMG_IN uint32 plainLen
  );
extern boolean Hmg_AesCbcDec(
  HMG_INOUT HmgAeskeyCtx* aesCtx,
  HMG_INOUT uint8 iv[],
  HMG_OUT uint8* plain,
  HMG_IN uint8* cipher,
  HMG_IN uint32 cipherLen
  );

extern boolean Hmg_AesCtrStart(
	HMG_INOUT HmgAesCtrCtx* aesCtrCtx,
	HMG_IN uint8 iv[],
	HMG_IN uint8 key[],
	HMG_IN uint8 keyLen
	);
extern boolean Hmg_AesCtrUpdate(
	HMG_INOUT HmgAesCtrCtx* aesCtrCtx,
	HMG_OUT uint8* out,
	HMG_IN uint8* in,
	HMG_IN uint32 inLen
	);
extern boolean Hmg_AesCtrFinish(
	HMG_INOUT HmgAesCtrCtx* aesCtrCtx,
	HMG_OUT uint32* totalLen
	);
extern boolean Hmg_AesCtr(
  HMG_INOUT HmgAeskeyCtx* aesCtx,
  HMG_INOUT uint8 iv[],
  HMG_OUT uint8* out,
  HMG_IN uint8* in,
  HMG_IN uint32 inLen
  );
extern boolean Hmg_AesCcmEnc(
	HMG_OUT uint8* cipher,
	HMG_OUT uint32* cipherLen,
	HMG_IN HmgAesCcmCtx *ccmCtx
	);
extern boolean Hmg_AesCcmDec(
	HMG_OUT uint8* plain,
	HMG_OUT uint32* plainLen,
	HMG_IN HmgAesCcmCtx *ccmCtx
	);	
extern boolean Hmg_AesCmacStart(
  HMG_INOUT HmgAesCmacCtx *cmacCtx,
  HMG_IN uint8 *key,
  HMG_IN uint8  keyLen
  );
extern boolean Hmg_AesCmacUpdate(
  HMG_INOUT HmgAesCmacCtx *cmacCtx,
  HMG_IN uint8 *msg,
  HMG_IN uint32 msgLen
  );
extern boolean Hmg_AesCmacFinish(
  HMG_INOUT HmgAesCmacCtx *cmacCtx,
  HMG_OUT uint8 tag[16]
  );
extern boolean Hmg_AesCmac(
  HMG_OUT uint8 tag[HMG_AES_CMAC_TAG_LEN],
  HMG_IN uint8 *key,
  HMG_IN uint8 keyLen,
  HMG_IN uint8 *msg,
  HMG_IN uint32 msgLen
  );
extern boolean Hmg_AesGcmEnc(
	HMG_OUT uint8 *cipher,
	HMG_OUT uint8 tag[HMG_GCM_TAG_SIZE],
	HMG_IN HmgAesGcmCtx *gcmCtx
	);
extern boolean Hmg_AesGcmDec(
	HMG_OUT uint8 *plain,
	HMG_IN uint8 tag[HMG_GCM_TAG_SIZE],
	HMG_IN HmgAesGcmCtx *gcmCtx
	);


/* Hmg_Ecc.h */
extern boolean Hmg_EcckeyGenerate(
	HMG_OUT HmgEcPublickey*	publickey,
	HMG_IN  uint8			privatekey[]
	);

extern boolean Hmg_EccEcdhStart(
	HMG_INOUT HmgEccSliceCtx* Ecc_ctx,
	HMG_IN uint8* privatekeyA,
	HMG_IN HmgEcPublickey* publickeyB
	);
extern boolean Hmg_EccEcdhUpdate(
	HMG_INOUT HmgEccSliceCtx* Ecc_ctx
	);
extern boolean Hmg_EccEcdhFinish(
	HMG_INOUT HmgEccSliceCtx* Ecc_ctx,
	HMG_OUT uint8* secretValue
	);
extern boolean Hmg_EccEcdh(
	HMG_OUT uint8			secretValue[],
	HMG_IN	uint8			privatekeyA[],
	HMG_IN	HmgEcPublickey*	publickeyB
	);

extern boolean Hmg_EccEcdsaSignStart(
	HMG_INOUT HmgEccSliceCtx* Ecc_ctx,
	HMG_IN	uint8* secretNumber
	);
extern boolean Hmg_EccEcdsaSignUpdate(
	HMG_INOUT HmgEccSliceCtx* Ecc_ctx
	);
extern boolean Hmg_EccEcdsaSignFinish(
	HMG_INOUT HmgEccSliceCtx* Ecc_ctx,
	HMG_OUT HmgEcdsaSign* signature,
	HMG_IN  uint8* hashedMessage,
	HMG_IN	uint8* privatekey
	);
extern boolean Hmg_EccEcdsaSign(
  HMG_OUT HmgEcdsaSign*   signature,
  HMG_IN  uint8     hashedMessage[],
  HMG_IN  uint8     secretNumber[],
  HMG_IN  uint8     privatekey[]
  );

extern boolean Hmg_EccEcdsaVerifyStart(
	HMG_INOUT HmgEccSliceCtx* Ecc_ctx,
	HMG_IN HmgEcdsaSign* signature,
	HMG_IN uint8* hashedMessage,
	HMG_IN HmgEcPublickey* publickey
	);
extern boolean Hmg_EccEcdsaVerifyUpdate(
	HMG_INOUT HmgEccSliceCtx* Ecc_ctx
	);
extern boolean Hmg_EccEcdsaVerifyFinish(
	HMG_INOUT HmgEccSliceCtx* Ecc_ctx
	);
extern boolean Hmg_EccEcdsaVerify(
	HMG_IN HmgEcdsaSign*	signature,
	HMG_IN uint8			hashedMessage[],
	HMG_IN HmgEcPublickey*	publickey
	);

/* Hmg_Ecies.h */
extern boolean Hmg_EciesEncryptStart(
  HMG_INOUT HmgEccSliceCtx* slCtx,
  HMG_IN uint8* privateKeyA,
  HMG_IN HmgEcPublickey* publicKeyB
  );
extern boolean Hmg_EciesEncryptUpdate(
  HMG_INOUT HmgEccSliceCtx* slCtx
  );
extern boolean Hmg_EciesEncryptFinish(
	HMG_INOUT HmgEccSliceCtx* slCtx,
	HMG_OUT HmgEcies_sPDU* sPdu,
	HMG_IN HmgEcPublickey*	publicKeyA,
	HMG_IN uint8* message,
	HMG_IN uint32 mLen,
	HMG_IN uint8* param1,
	HMG_IN uint8 encMode
	);
extern boolean Hmg_EciesEncrypt(
	HMG_OUT HmgEcies_sPDU* sPdu,
	HMG_IN uint8*	privateKeyA,
	HMG_IN HmgEcPublickey* publicKeyA,
	HMG_IN HmgEcPublickey* publicKeyB,
	HMG_IN uint8*	message,
	HMG_IN uint32	mLen,
	HMG_IN uint8*	param1,
	HMG_IN uint8	encMode
	);

extern boolean Hmg_EciesDecryptStart(
  HMG_INOUT HmgEccSliceCtx* slCtx,
  HMG_IN uint8* privKey,
  HMG_IN HmgEcPublickey* pubKey
  );
extern boolean Hmg_EciesDecryptUpdate(
  HMG_INOUT HmgEccSliceCtx* slCtx
  );
extern boolean Hmg_EciesDecryptFinish(
	HMG_INOUT HmgEccSliceCtx* slCtx, 
	HMG_OUT uint8* decMessage, 
	HMG_IN	HmgEcies_sPDU* sPdu,
	HMG_IN uint8* param1, 
	HMG_IN uint8 encMode
	);
extern boolean Hmg_EciesDecrypt(
	HMG_OUT uint8*		decMessage,
	HMG_IN HmgEcies_sPDU*	sPdu,
	HMG_IN uint8*		privKey,
	HMG_IN uint8*		param1,
	HMG_IN uint8		encMode
	);

/* Hmg_HmacSha160.h */
extern boolean Hmg_HmacSha160Start(
  HMG_INOUT HmgHmacSha160Ctx* HmacSha160Ctx,
  HMG_IN    uint8*      key, 
  HMG_IN    uint32      keyLen
  );
extern boolean Hmg_HmacSha160Update(
  HMG_INOUT HmgHmacSha160Ctx* HmacSha160Ctx,
  HMG_IN    uint8*      data, 
  HMG_IN    uint32      dataLen
  );
extern boolean Hmg_HmacSha160Finish(
  HMG_INOUT HmgHmacSha160Ctx* HmacSha160Ctx,
  HMG_OUT uint8 hmacValue[]
  );
extern boolean Hmg_HmacSha160(
	HMG_OUT uint8 hmacValue[],
	HMG_IN uint8* key,
	HMG_IN uint32 keyLen,
	HMG_IN uint8* data,
	HMG_IN uint32 dataLen
	);

/* Hmg_HmacSha256.h */
extern boolean Hmg_HmacSha224Start(
	HMG_INOUT	HmgHmacSha224Ctx*	HmacSha224Ctx,
	HMG_IN		uint8*				key,
	HMG_IN		uint32				keyLen
	);
extern boolean Hmg_HmacSha224Update(
	HMG_INOUT	HmgHmacSha224Ctx*	HmacSha224Ctx,
	HMG_IN		uint8*				data,
	HMG_IN		uint32				dataLen
	);
extern boolean Hmg_HmacSha224Finish(
	HMG_INOUT	HmgHmacSha224Ctx*	HmacSha224Ctx,
	HMG_OUT		uint8				hmacValue[]
	);
extern boolean Hmg_HmacSha256Start(
  HMG_INOUT HmgHmacSha256Ctx* HmacSha256Ctx,
  HMG_IN    uint8*        key,
  HMG_IN    uint32        keyLen
  );
extern boolean Hmg_HmacSha256Update(
  HMG_INOUT HmgHmacSha256Ctx*   HmacSha256Ctx,
  HMG_IN    uint8*        data,
  HMG_IN    uint32        dataLen
  );
extern boolean Hmg_HmacSha256Finish(
  HMG_INOUT HmgHmacSha256Ctx* HmacSha256Ctx,
  HMG_OUT   uint8       hmacValue[]
  );
extern boolean Hmg_HmacSha256(
	HMG_OUT uint8	hmacValue[],
	HMG_IN	uint8*	key,
	HMG_IN	uint32	keyLen,
	HMG_IN	uint8*	data,
	HMG_IN	uint32	dataLen
	);

/* Hmg_Pbkdf2.h */
extern boolean Hmg_PBKDF2(
	HMG_OUT uint8 *derivedkey,
	HMG_IN uint32 dkLen,
	HMG_IN uint8 *password,
	HMG_IN uint32 pLen,
	HMG_IN uint8 *salt,
	HMG_IN uint32 sLen,
	HMG_IN uint32 icount
	);

/* Hmg_Pkcs1.h */
typedef struct ctPkcs1PssCtx {
	uint8* pDigest;
	uint32 hashAlgorithm;
	uint8* pSalt;
	uint32 sLen;
} HmgPkcs1PssCtx;

typedef struct ctPkcs1OaepCtx {
		uint8* pLabel;
		uint32 labelLen;
		uint8* pSeed;
		uint32 hashAlgorithm;
	} HmgPkcs1OaepCtx;
	
extern boolean Hmg_RsaPkcs1v15SignStart(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_IN  uint8* pDigest,
	HMG_IN uint32 hashAlgorithm,
	HMG_IN HmgRsaPrivatekey* privatekey
	);
extern boolean Hmg_RsaPkcs1v15SignUpdate(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx
	);
extern boolean Hmg_RsaPkcs1v15SignFinish(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_OUT uint8* pSign
	);
extern boolean Hmg_RsaPkcs1v15Sign(
	HMG_OUT uint8 pSign[],
	HMG_IN  uint8* pDigest,
	HMG_IN uint32 hashAlgorithm,
	HMG_IN HmgRsaPrivatekey* privatekey
	);

extern boolean Hmg_RsaPkcs1v15VerifyStart(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_IN uint8* pSign,
	HMG_IN HmgRsaPublickey* publickey
	);
extern boolean Hmg_RsaPkcs1v15VerifyUpdate(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx
	);
extern boolean Hmg_RsaPkcs1v15VerifyFinish(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_IN uint8* pDigest,
	HMG_IN uint32 hashAlgorithm
	);
extern boolean Hmg_RsaPkcs1v15Verify(
  HMG_IN uint8 pSign[],
  HMG_IN uint8* pDigest,
  HMG_IN uint32 hashAlgorithm,
  HMG_IN HmgRsaPublickey* publickey
  );
extern boolean Hmg_RsaPkcs1PssSignStart(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_IN HmgPkcs1PssCtx* pssCtx,
	HMG_IN HmgRsaPrivatekey* privatekey
	);

extern boolean Hmg_RsaPkcs1PssSignUpdate(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx
	);

extern boolean Hmg_RsaPkcs1PssSignFinish(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_OUT uint8* pSign
	);
extern boolean Hmg_RsaPkcs1PssSign(
	HMG_OUT uint8 pSign[],
	HMG_IN HmgPkcs1PssCtx* pssCtx,
	HMG_IN HmgRsaPrivatekey* privatekey
	);
extern boolean Hmg_RsaPkcs1PssVerifyStart(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_IN uint8* pSign,
	HMG_IN HmgRsaPublickey* publickey
	);
extern boolean Hmg_RsaPkcs1PssVerifyUpdate(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx
	);
extern boolean Hmg_RsaPkcs1PssVerifyFinish(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_IN HmgPkcs1PssCtx* pssCtx
	);
extern boolean Hmg_RsaPkcs1PssVerify(
	HMG_IN uint8 pSign[],
	HMG_IN HmgPkcs1PssCtx* pssCtx,
	HMG_IN HmgRsaPublickey* publickey
	);

extern boolean Hmg_RsaPkcs1v15EncryptStart(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_IN uint8* msg,
	HMG_IN uint32 mLen,
	HMG_IN HmgRsaPublickey* publickey
	);
extern boolean Hmg_RsaPkcs1v15EncryptUpdate(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx
	);
extern boolean Hmg_RsaPkcs1v15EncryptFinish(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_OUT uint8* cipher
	);
extern boolean Hmg_RsaPkcs1v15Encrypt(
	HMG_OUT uint8 cipher[],
	HMG_IN uint8* msg,
	HMG_IN uint32 mLen,
	HMG_IN HmgRsaPublickey* publickey
	);
extern boolean Hmg_RsaPkcs1v15DecryptStart(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_IN uint8* cipher,
	HMG_IN HmgRsaPrivatekey* privatekey
	);
extern boolean Hmg_RsaPkcs1v15DecryptUpdate(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx
	);
extern boolean Hmg_RsaPkcs1v15DecryptFinish(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_OUT uint8* msg,
	HMG_OUT uint32* mLen
	);
extern boolean Hmg_RsaPkcs1v15Decrypt(
	HMG_OUT uint8* msg,
	HMG_OUT uint32* mLen,
	HMG_IN uint8 cipher[],
	HMG_IN HmgRsaPrivatekey* privatekey
	);

extern boolean Hmg_RsaPkcs1OaepEncryptStart(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_IN  uint8* msg,
	HMG_IN uint32 mLen,
	HMG_IN HmgPkcs1OaepCtx *oaepCtx,
	HMG_IN HmgRsaPublickey* publickey
	);
extern boolean Hmg_RsaPkcs1OaepEncryptUpdate(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx
	);
extern boolean Hmg_RsaPkcs1OaepEncryptFinish(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_OUT uint8* cipher
	);

extern boolean Hmg_RsaPkcs1OaepDecryptStart(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_IN  uint8* cipher,
	HMG_IN HmgRsaPrivatekey* privatekey
	);
extern boolean Hmg_RsaPkcs1OaepDecryptUpdate(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx
	);
extern boolean Hmg_RsaPkcs1OaepDecryptFinish(
	HMG_INOUT HmgRsaSliceCtx* rsa_ctx,
	HMG_OUT uint8* msg,
	HMG_OUT uint32* mLen,
	HMG_IN HmgPkcs1OaepCtx *oaepCtx
	);
extern boolean Hmg_RsaPkcs1OaepDecrypt(
	HMG_OUT uint8* msg,
	HMG_OUT uint32* mLen,
	HMG_IN  uint8 cipher[],
	HMG_IN HmgPkcs1OaepCtx *oaepCtx,
	HMG_IN HmgRsaPrivatekey* privatekey
	);
extern boolean Hmg_RsaPkcs1OaepEncrypt(
	HMG_OUT uint8 cipher[],
	HMG_IN  uint8* msg,
	HMG_IN uint32 mLen,
	HMG_IN HmgPkcs1OaepCtx *oaepCtx,
	HMG_IN HmgRsaPublickey* publickey
	);

/*Hmg_DiffieHellman.h*/
extern boolean Hmg_DiffieHellmanKeypairGen(
	HMG_INOUT  HmgPrngCtx* prngCtx,
	HMG_OUT uint8 publicValue[],
	HMG_INOUT uint8 privateValue[],
	HMG_IN  uint8 baseG[],
	HMG_IN  uint8 primeP[]
	);
extern boolean Hmg_DiffieHellmanSharedvalueGen(
	HMG_OUT uint8 secretValue[],
	HMG_IN  uint8 publicValue[],
	HMG_IN  uint8 privateValue[],
	HMG_IN  uint8 primeP[]
	);


/* Hmg_Prng.h */
extern void Hmg_PrngInit(
  HMG_INOUT HmgPrngCtx *hpc
  );
extern void Hmg_PrngReseed(
  HMG_INOUT HmgPrngCtx *hpc,
  HMG_IN uint8 entropy[HMG_ENTROPY_LEN]
  );
extern boolean Hmg_PrngGetRand(
  HMG_INOUT HmgPrngCtx *hpc,
  HMG_OUT uint8 *rndout,
  HMG_IN  uint32  len
  );

/* Hmg_Rsa.h */
extern boolean Hmg_RsaModExponentLongStart(
  HMG_INOUT HmgRsaSliceCtx* rsaCtx,
  HMG_IN uint8* pEM,
  HMG_IN HmgRsaPrivatekey* Privatekey
  );
extern boolean Hmg_RsaModExponentLongUpdate(
  HMG_INOUT HmgRsaSliceCtx* rsaCtx
  );
extern boolean Hmg_RsaModExponentLongFinish(
  HMG_INOUT HmgRsaSliceCtx* rsaCtx,
  HMG_OUT uint8* pCM
  );
extern boolean Hmg_RsaModExponentLong(
  HMG_OUT uint8 pCM[],
  HMG_IN uint8 pEM[],
  HMG_IN HmgRsaPrivatekey* Privatekey
  );

extern boolean Hmg_RsaModExponentStart(
  HMG_INOUT HmgRsaSliceCtx *rsaCtx,
  HMG_IN uint8* pEM,
  HMG_IN HmgRsaPublickey* Publickey
  );
extern boolean Hmg_RsaModExponentUpdate(
  HMG_INOUT HmgRsaSliceCtx *rsaCtx
  );
extern boolean Hmg_RsaModExponentFinish(
  HMG_INOUT HmgRsaSliceCtx *rsaCtx,
  HMG_OUT uint8* pCM
  );
extern boolean Hmg_RsaModExponent(
  HMG_OUT uint8 pCM[],
  HMG_IN uint8 pEM[],
  HMG_IN HmgRsaPublickey* Publickey
  );

/* Hmg_Sha160.h */
extern boolean Hmg_Sha160Start(
  HMG_INOUT HmgSha160Ctx* sha160Ctx
  );
extern boolean Hmg_Sha160Update(
  HMG_INOUT HmgSha160Ctx* sha160Ctx, 
  HMG_IN    uint8*    data, 
  HMG_IN    uint32    dataLen
  );
extern boolean Hmg_Sha160Finish(
  HMG_INOUT HmgSha160Ctx* sha160Ctx,
  HMG_OUT   uint8   digest[]
  );
extern boolean Hmg_Sha160(
	HMG_OUT		uint8		digest[],
	HMG_IN		uint8*		data,
	HMG_IN		uint32		dataLen
	);

/* Hmg_Sha256.h */
extern boolean Hmg_Sha256Start(
  HMG_INOUT HmgSha256Ctx* sha256Ctx
  );
extern boolean Hmg_Sha256Update(
  HMG_INOUT HmgSha256Ctx* sha256Ctx,
  HMG_IN    uint8*    data,
  HMG_IN    uint32    dataLen
  );
extern boolean Hmg_Sha256Finish(
  HMG_INOUT HmgSha256Ctx* sha256Ctx,
  HMG_OUT   uint8   digest[]
  );
extern boolean Hmg_Sha256(
	HMG_OUT		uint8		digest[],
	HMG_IN		uint8*		data,
	HMG_IN		uint32		dataLen
	);



#endif /* DUMMY_HAECRYPTOLIB_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
