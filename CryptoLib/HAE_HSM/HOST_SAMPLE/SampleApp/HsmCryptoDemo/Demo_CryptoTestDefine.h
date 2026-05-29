/*
 * Demo_CryptoTestDefine.h
 *
 */
#ifndef DEMO_CRYPTO_TEST_DEFINE_H_
#define DEMO_CRYPTO_TEST_DEFINE_H_

#include "Cfg_App.h"
/*
* Cfg_App.h include below options
* #define EXTENDED_TEST_VECTOR
* #define WAIT_RESP_TIMEOUT 300000000 // 15sec
*/
#include "CryptoService_Aes.h"
#include "CryptoService_Ecc.h"
#include "CryptoService_RsaPkcs1.h"

#if defined(__GHS__)
#pragma ghs startdata
#endif

/******************************************************************************/
/*                             AES TEST Vector                           */
/******************************************************************************/

typedef struct HSM_AES_TestVector
{
	AES_MODE mode;
	UINT16 keyNum;
	UINT32 mLen;
	UINT8 iv[16];
	UINT8 plain[160];
	UINT8 cipher[160];
} HSM_AES_TestVector;

#if defined(__TASKING__)
#pragma section farrom "HSM_TEST_VECTOR"
#endif
#if defined(__GHS__)
#pragma ghs section rodata="HSM_TEST_VECTOR"
#pragma alignvar(4)
#endif

extern const HSM_AES_TestVector g_hsmEcbNistTv;
extern const HSM_AES_TestVector g_hsmEcbTv;
extern const HSM_AES_TestVector g_hsmCbcNistTv;
extern const HSM_AES_TestVector g_hsmCbcTv;
extern const HSM_AES_TestVector g_hsmCtrNistTv;
extern const HSM_AES_TestVector g_hsmCtrTv;
extern const HSM_AES_TestVector g_hsmOfbNistTv;
extern const HSM_AES_TestVector g_hsmOfbTv;

#if defined(__TASKING__)
#pragma section farrom restore
#endif
#if defined(__GHS__)
#pragma ghs section rodata=default
#endif

/******************************************************************************/
/*                             AES-CMAC TEST Vector                           */
/******************************************************************************/
typedef struct HSM_AES_CMAC_TestVector
{
	UINT16 keyNum;
	UINT32 mLen;
	UINT8 *msg;
	UINT8 digest[HSM_AES128_CMAC_LEN];
	UINT32 digestLen;
} HSM_AES_CMAC_TestVector;

#if defined(__TASKING__)
#pragma section farrom "HSM_TEST_VECTOR"
#endif
#if defined(__GHS__)
#pragma ghs section rodata="HSM_TEST_VECTOR"
#pragma alignvar(4)
#endif

extern const HSM_AES_CMAC_TestVector g_aesCmacTv1;
#ifdef EXTENDED_TEST_VECTOR
extern const HSM_AES_CMAC_TestVector g_aesCmacTv2;
extern const HSM_AES_CMAC_TestVector g_aesCmacTv3;
extern const HSM_AES_CMAC_TestVector g_aesCmacTv4;
extern const HSM_AES_CMAC_TestVector g_aesCmacTv5;
extern const HSM_AES_CMAC_TestVector g_aesCmacFailTv1;
extern const HSM_AES_CMAC_TestVector g_aesCmacFailTv2;
extern const HSM_AES_CMAC_TestVector g_aesCmacFailTv3;
#endif
extern const HSM_AES_CMAC_TestVector g_aesCmacTempTv;
extern const HSM_AES_CMAC_TestVector g_aesCmacUdkTv;

#if defined(__TASKING__)
#pragma section farrom restore
#endif
#if defined(__GHS__)
#pragma ghs section rodata=default
#endif
/******************************************************************************/
/*                             SHA256 TEST Vector                             */
/******************************************************************************/
typedef struct HSM_Hash_TestVector
{
	UINT32 mLen;
	UINT8 *msg;
	UINT8 digest[SHA256_DIGEST_SIZE];
} HSM_Hash_TestVector;

#if defined(__TASKING__)
#pragma section farrom "HSM_TEST_VECTOR"
#endif
#if defined(__GHS__)
#pragma ghs section rodata="HSM_TEST_VECTOR"
#pragma alignvar(4)
#endif

extern const HSM_Hash_TestVector g_sha256Tv1;
#ifdef EXTENDED_TEST_VECTOR
extern const HSM_Hash_TestVector g_sha256Tv2;
extern const HSM_Hash_TestVector g_sha256Tv3;
extern const HSM_Hash_TestVector g_sha256Tv4;
extern const HSM_Hash_TestVector g_sha256Tv5;
extern const HSM_Hash_TestVector g_sha256FailTv1;
#endif

#if defined(__TASKING__)
#pragma section farrom restore
#endif
#if defined(__GHS__)
#pragma ghs section rodata=default
#endif

/******************************************************************************/
/*                             SHA256 TEST Vector                             */
/******************************************************************************/
#if defined(__TASKING__)
#pragma section farrom "HSM_TEST_VECTOR"
#endif
#if defined(__GHS__)
#pragma ghs section rodata="HSM_TEST_VECTOR"
#pragma alignvar(4)
#endif

extern const HSM_Hash_TestVector g_sha160Tv1;
#ifdef EXTENDED_TEST_VECTOR
extern const HSM_Hash_TestVector g_sha160Tv2;
extern const HSM_Hash_TestVector g_sha160Tv3;
extern const HSM_Hash_TestVector g_sha160Tv4;
extern const HSM_Hash_TestVector g_sha160Tv5;
extern const HSM_Hash_TestVector g_sha160FailTv1;
#endif

#if defined(__TASKING__)
#pragma section farrom restore
#endif
#if defined(__GHS__)
#pragma ghs section rodata=default
#endif
/******************************************************************************/
/*                               HMAC-SHA256 TEST Vector                      */
/******************************************************************************/

typedef struct HSM_Hash_HMAC_TestVector
{
	UINT16 keyNum;
	UINT32 mLen;
	UINT8 *msg;
	UINT8 digest[SHA256_DIGEST_SIZE];
} HSM_Hash_HMAC_TestVector;

#if defined(__TASKING__)
#pragma section farrom "HSM_TEST_VECTOR"
#endif
#if defined(__GHS__)
#pragma ghs section rodata="HSM_TEST_VECTOR"
#pragma alignvar(4)
#endif

extern const HSM_Hash_HMAC_TestVector g_hmacSha256Tv1;
#ifdef EXTENDED_TEST_VECTOR
extern const HSM_Hash_HMAC_TestVector g_hmacSha256Tv2;
extern const HSM_Hash_HMAC_TestVector g_hmacSha256Tv3;
extern const HSM_Hash_HMAC_TestVector g_hmacSha256Tv4;
extern const HSM_Hash_HMAC_TestVector g_hmacSha256Tv5;
extern const HSM_Hash_HMAC_TestVector g_hmacSha256FailTv1;
extern const HSM_Hash_HMAC_TestVector g_hmacSha256FailTv2;
extern const HSM_Hash_HMAC_TestVector g_hmacSha256FailTv3;
#endif
#if defined(__TASKING__)
#pragma section farrom restore
#endif
#if defined(__GHS__)
#pragma ghs section rodata=default
#endif

/******************************************************************************/
/*                       		PBKDF2 TEST Vector      	                  */
/******************************************************************************/
#define PBKDF2_MAX_OUTPUT_BUFFER_SIZE 1024
#define PBKDF2_MAX_INPUT_BUFFER_SIZE 504

typedef struct
 {
	 UINT16 keyNum;
	 UINT8 password[PBKDF2_MAX_INPUT_BUFFER_SIZE];
	 UINT32 pLen;
	 UINT8 salt[PBKDF2_MAX_INPUT_BUFFER_SIZE];
	 UINT32 sLen;
	 UINT32 cnt;
	 UINT8 dk[PBKDF2_MAX_OUTPUT_BUFFER_SIZE];
	 UINT32 dkLen;
 }Hmg_Pbkdf2_TestVector;


#if defined(__TASKING__)
#pragma section farrom "HSM_TEST_VECTOR"
#endif
#if defined(__GHS__)
#pragma ghs section rodata="HSM_TEST_VECTOR"
#pragma alignvar(4)
#endif
extern const Hmg_Pbkdf2_TestVector g_kdfTv1;
extern const Hmg_Pbkdf2_TestVector g_kdfTv2;
extern const Hmg_Pbkdf2_TestVector g_kdfTv3;
extern const Hmg_Pbkdf2_TestVector g_kdfTv4;
extern const Hmg_Pbkdf2_TestVector g_kdfTv5;
extern const Hmg_Pbkdf2_TestVector g_kdfTv6;
#if defined(__TASKING__)
#pragma section farrom restore
#endif
#if defined(__GHS__)
#pragma ghs section rodata=default
#endif

/******************************************************************************/
/*                        RSA PKCS1 v1.5-SIGN TEST Vector                      */
/******************************************************************************/
typedef struct HSM_Rsa_Pkcs1_v15_Sign_TestVector
{
	UINT16 keyNum;
	UINT32 digestLen;
	UINT8 digest[SHA256_DIGEST_SIZE];
	UINT8 sign[HAC_RSA_BYTES_SIZE];
} HSM_Rsa_Pkcs1_v15_Sign_TestVector;

extern HSM_Rsa_Pkcs1_v15_Sign_TestVector g_pkcs1v15SignTv;
#if defined(__TASKING__)
#pragma section farrom "HSM_TEST_VECTOR"
#endif
#if defined(__GHS__)
#pragma ghs section rodata="HSM_TEST_VECTOR"
#pragma alignvar(4)
#endif
#ifdef EXTENDED_TEST_VECTOR
extern const HSM_Rsa_Pkcs1_v15_Sign_TestVector g_pkcs1v15SignTv1;
extern const HSM_Rsa_Pkcs1_v15_Sign_TestVector g_pkcs1v15SignTv2;
extern const HSM_Rsa_Pkcs1_v15_Sign_TestVector g_pkcs1v15SignTv3;
extern const HSM_Rsa_Pkcs1_v15_Sign_TestVector g_pkcs1v15SignTv4;
extern const HSM_Rsa_Pkcs1_v15_Sign_TestVector g_pkcs1v15SignTv5;
extern const HSM_Rsa_Pkcs1_v15_Sign_TestVector g_pkcs1v15SignFailTv1;
extern const HSM_Rsa_Pkcs1_v15_Sign_TestVector g_pkcs1v15SignFailTv2;
#endif
#if defined(__TASKING__)
#pragma section farrom restore
#endif
#if defined(__GHS__)
#pragma ghs section rodata=default
#endif
/******************************************************************************/
/*                   RSA PKCS1 v1.5 SHA1-VERIFY TEST Vector                   */
/******************************************************************************/

extern HSM_Rsa_Pkcs1_v15_Sign_TestVector g_pkcs1v15Sha160VerifyTv;
extern HSM_Rsa_Pkcs1_v15_Sign_TestVector g_pkcs1v15Sha160VerifyTv1;

/******************************************************************************/
/*                        RSA PKCS1 PSS-SIGN TEST Vector                      */
/******************************************************************************/
typedef struct HSM_Rsa_Pkcs1_Pss_Sign_TestVector
{
	UINT16 keyNum;
	UINT32 digestLen;
	UINT8 digest[SHA256_DIGEST_SIZE];
	UINT8 saltLen;
	UINT8 salt[HAC_RSA_BYTES_SIZE];
	UINT8 sign[HAC_RSA_BYTES_SIZE];
} HSM_Rsa_Pkcs1_Pss_Sign_TestVector;

extern HSM_Rsa_Pkcs1_Pss_Sign_TestVector g_pkcs1PssSignTv;
#if defined(__TASKING__)
#pragma section farrom "HSM_TEST_VECTOR"
#endif
#if defined(__GHS__)
#pragma ghs section rodata="HSM_TEST_VECTOR"
#pragma alignvar(4)
#endif
#ifdef EXTENDED_TEST_VECTOR
extern const HSM_Rsa_Pkcs1_Pss_Sign_TestVector g_pkcs1PssSignTv1;
extern const HSM_Rsa_Pkcs1_Pss_Sign_TestVector g_pkcs1PssSignTv2;
extern const HSM_Rsa_Pkcs1_Pss_Sign_TestVector g_pkcs1PssSignTv3;
extern const HSM_Rsa_Pkcs1_Pss_Sign_TestVector g_pkcs1PssSignTv4;
extern const HSM_Rsa_Pkcs1_Pss_Sign_TestVector g_pkcs1PssSignTv5;
extern const HSM_Rsa_Pkcs1_Pss_Sign_TestVector g_pkcs1PssSignFailTv1;
extern const HSM_Rsa_Pkcs1_Pss_Sign_TestVector g_pkcs1PssSignFailTv2;
#endif
#if defined(__TASKING__)
#pragma section farrom restore
#endif
#if defined(__GHS__)
#pragma ghs section rodata=default
#endif
/******************************************************************************/
/*                       RSA PKCS1 v1.5-ENC TEST Vector                       */
/******************************************************************************/
typedef struct _HSM_Rsa_Pkcs1_v15_Enc_TestVector
{
	UINT16 keyNum;
	UINT32 mLen;
	UINT8 msg[HAC_RSA_BYTES_SIZE];
	UINT8 cipher[HAC_RSA_BYTES_SIZE];
} HSM_Rsa_Pkcs1_v15_Enc_TestVector;

extern HSM_Rsa_Pkcs1_v15_Enc_TestVector g_pkcs1v15EncTv;
extern HSM_Rsa_Pkcs1_v15_Enc_TestVector g_pkcs1v15DecTv;
#if defined(__TASKING__)
#pragma section farrom "HSM_TEST_VECTOR"
#endif
#if defined(__GHS__)
#pragma ghs section rodata="HSM_TEST_VECTOR"
#pragma alignvar(4)
#endif
#ifdef EXTENDED_TEST_VECTOR
extern const HSM_Rsa_Pkcs1_v15_Enc_TestVector g_pkcs1v15EncTv1;
extern const HSM_Rsa_Pkcs1_v15_Enc_TestVector g_pkcs1v15EncTv2;
extern const HSM_Rsa_Pkcs1_v15_Enc_TestVector g_pkcs1v15EncFailTv1;
#endif
#if defined(__TASKING__)
#pragma section farrom restore
#endif
#if defined(__GHS__)
#pragma ghs section rodata=default
#endif

/******************************************************************************/
/*                       RSA PKCS1 OAEP-ENC TEST Vector                       */
/******************************************************************************/
typedef struct _HSM_Rsa_Pkcs1_Oaep_Enc_TestVector
{
	UINT16 keyNum;
	UINT32 mLen;
	UINT8 msg[HAC_RSA_BYTES_SIZE];
	UINT8 seed[SHA256_DIGEST_SIZE];
	UINT8 cipher[HAC_RSA_BYTES_SIZE];
} HSM_Rsa_Pkcs1_Oaep_Enc_TestVector;

extern HSM_Rsa_Pkcs1_Oaep_Enc_TestVector g_pkcs1oaepEncTv;
#if defined(__TASKING__)
#pragma section farrom "HSM_TEST_VECTOR"
#endif
#if defined(__GHS__)
#pragma ghs section rodata="HSM_TEST_VECTOR"
#pragma alignvar(4)
#endif
#ifdef EXTENDED_TEST_VECTOR
extern const HSM_Rsa_Pkcs1_Oaep_Enc_TestVector g_pkcs1oaepEncTv1;
extern const HSM_Rsa_Pkcs1_Oaep_Enc_TestVector g_pkcs1oaepEncTv2;
extern const HSM_Rsa_Pkcs1_Oaep_Enc_TestVector g_pkcs1oaepEncFailTv1;
#endif
#if defined(__TASKING__)
#pragma section farrom restore
#endif
#if defined(__GHS__)
#pragma ghs section rodata=default
#endif
/******************************************************************************/
/*			           RSA PKCS3 DiffieHellman TEST Vector           	   	  */
/******************************************************************************/
typedef struct _HSM_Rsa_Pkcs3_DiffieHellman_TestVector
{
	UINT8 dh_prime[HAC_RSA_BYTES_SIZE];
	UINT8 dh_base[HAC_RSA_BYTES_SIZE];
	UINT8 xa[HAC_RSA_BYTES_SIZE];
	UINT8 xb[HAC_RSA_BYTES_SIZE];
	UINT8 yb[HAC_RSA_BYTES_SIZE];
	UINT8 ya[HAC_RSA_BYTES_SIZE];
} HSM_Rsa_Pkcs3_DiffieHellman_TestVector;

#if defined(__TASKING__)
#pragma section farrom "HSM_TEST_VECTOR"
#endif
#if defined(__GHS__)
#pragma ghs section rodata="HSM_TEST_VECTOR"
#pragma alignvar(4)
#endif
extern const HSM_Rsa_Pkcs3_DiffieHellman_TestVector g_pkcs3DiffieHellmanTv;
#if defined(__TASKING__)
#pragma section farrom restore
#endif
#if defined(__GHS__)
#pragma ghs section rodata=default
#endif
/******************************************************************************/
/*                           ECC ECDSA-SIGN TEST Vector                       */
/******************************************************************************/
typedef struct _HSM_Ecc_Ecdsa_TestVector
{
	UINT16 keyNum;
	UINT8 digest[ECC_BYTES_SIZE];
	UINT8 secret[ECC_BYTES_SIZE];
	ECC_ECDSA_SIGN_t sign;
} HSM_Ecc_Ecdsa_TestVector;

#if defined(__TASKING__)
#pragma section farrom "HSM_TEST_VECTOR"
#endif
#if defined(__GHS__)
#pragma ghs section rodata="HSM_TEST_VECTOR"
#pragma alignvar(4)
#endif
extern const HSM_Ecc_Ecdsa_TestVector g_eccEcdsaTv1;
extern const HSM_Ecc_Ecdsa_TestVector g_eccEcdsaTv2;
extern const HSM_Ecc_Ecdsa_TestVector g_eccEcdsaFailTv1;
extern const HSM_Ecc_Ecdsa_TestVector g_eccEcdsaFailTv2;
#if defined(__TASKING__)
#pragma section farrom restore
#endif
#if defined(__GHS__)
#pragma ghs section rodata=default
#endif
/******************************************************************************/
/*                        ECC ECDH-Key Exchange TEST Vector                   */
/******************************************************************************/
typedef struct HSM_Ecc_Ecdh_TestVector
{
	UINT16 keyNum;
	ECC_PUBLICKEY_t pubkeyOtherSide;
	UINT8 secretValue[ECC_BYTES_SIZE];
} HSM_Ecc_Ecdh_TestVector;

#if defined(__TASKING__)
#pragma section farrom "HSM_TEST_VECTOR"
#endif
#if defined(__GHS__)
#pragma ghs section rodata="HSM_TEST_VECTOR"
#pragma alignvar(4)
#endif
extern const HSM_Ecc_Ecdh_TestVector g_eccEcdhTv1;
extern const HSM_Ecc_Ecdh_TestVector g_eccEcdhTv2;
extern const HSM_Ecc_Ecdh_TestVector g_eccEcdhFailTv1;
extern const HSM_Ecc_Ecdh_TestVector g_eccEcdhFailTv2;
#if defined(__TASKING__)
#pragma section farrom restore
#endif
#if defined(__GHS__)
#pragma ghs section rodata=default
#endif

/******************************************************************************/
/*                        RNG TEST Vector                  					  */
/******************************************************************************/
typedef struct {
	UINT8 *randValue;
    UINT32 len;
} HSM_RNG_TestVector;

#if defined(__TASKING__)
#pragma section farrom "HSM_TEST_VECTOR"
#endif
#if defined(__GHS__)
#pragma ghs section rodata="HSM_TEST_VECTOR"
#pragma alignvar(4)
#endif
extern const HSM_RNG_TestVector g_rngTv1;
extern const HSM_RNG_TestVector g_rngTv2;
extern const HSM_RNG_TestVector g_rngFailTv1;
extern const HSM_RNG_TestVector g_rngFailTv2;
extern const HSM_RNG_TestVector g_rngFailTv3;
#if defined(__TASKING__)
#pragma section farrom restore
#endif
#if defined(__GHS__)
#pragma ghs section rodata=default
#endif

#if defined(__GHS__)
#pragma ghs enddata
#endif

#endif /* DEMO_CRYPTO_TEST_DEFINE_H_ */
