/*-----------------------------------------------------------------------------
* Hyundai-AutoEver Cryptography Library
* Copyright (c) 2015-2016 Hyundai-AutoEver all rights reserved.
------------------------------------------------------------------------------*/
/**
* \file     Hmg_Pkcs1.h
* \date     Jan. 2016.
* \version  1.6.0
* \author   Hyundai_Autoever Automotive Security Techology Team
* \brief    RSA pkcs1 2048bit implementation
* \see
*
*/

/* DEFINE TO PREVENT RECURSIVE INCLUSION -------------------------------------*/
#ifndef HMG_PKCS1_H_
#define HMG_PKCS1_H_

/* INCLUDES ------------------------------------------------------------------*/
#include "Hmg_Rsa.h"
#include "Hmg_Sha160.h"
#include "Hmg_Sha256.h"
#include "Hmg_Sha512.h"

#ifdef  __cplusplus
extern "C" {
#endif

/* EXPORTED DEFINE -----------------------------------------------------------*/

/** Type of the hash function: hashAlgorithm */
#define HMG_SHA_160         (1U)
#define HMG_SHA_224         (2U)
#define HMG_SHA_256         (3U)
#define HMG_SHA_384         (4U)
#define HMG_SHA_512         (5U)
#define HMG_SHA_512_224     (6U)
#define HMG_SHA_512_256     (7U)

    /* EXPORTED MACRO  -----------------------------------------------------------*/
    /* EXPORTED TYPES  -----------------------------------------------------------*/

#define HMG_SRAND(s)    Hmg_Srand(s)
#define HMG_RAND        Hmg_rand();

    void Hmg_Srand(uint32 seed);
    uint32 Hmg_rand(void);



    /** \brief  PKCS#1Pss Sign & Verify context
    *
    * \param[in]    pDigest         hashed text
    * \param[in]    hashAlgorithm   hash algorithm
    * \param[in]    pSalt           salt text( if Pss Verify, this value not used)
    * \param[in]    sLen            salt text length
    */
    typedef struct ctPkcs1PssCtx {
        uint8* pDigest;
        uint32 hashAlgorithm;
        uint8* pSalt;
        uint32 sLen;
    } HmgPkcs1PssCtx;


    /** \brief  PKCS#1OAEP ENC & DEC context
    *
    * \param[in]    pLabel          optional label to be associated with the message (default = empty)
    * \param[in]    labelLen        label length
    * \param[in]    pSeed           seed input ( if DEC, pSeed is not used)
    * \param[in]    hashAlgorithm   hash algorithm used for label (if label is provided)
    */
    typedef struct ctPkcs1OaepCtx {
        uint8* pLabel;
        uint32 labelLen;
        uint8* pSeed;
        uint32 hashAlgorithm;
    } HmgPkcs1OaepCtx;


    /* EXPORTED VARIABLES  -------------------------------------------------------*/
    /* EXPORTED FUNCTIONS  -------------------------------------------------------*/

#ifdef HMG_ENABLE_RSASSA_PKCS1V15
    /** \brief  RSA PKCS1V1.5 sign generate.
    *
    * calculates modular exponent using private key D
    *   calculate, (signed text) = (encoding text EM) ^ (private exponent) mod (modular N).
    *       EM = 0x00 || 0x01 || PS || 0x00 || T.
    *       PS = 0xff ff ff ff ..... (length : emLen - tLen - 3)
    *       DER encoding T =
    *           SHA - 1      : (0x)30 21 30 09 06 05 2b 0e 03 02 1a 05 00 04 14 || H(20-bytes).
    *           SHA - 256    : (0x)30 31 30 0d 06 09 60 86 48 01 65 03 04 02 01 05 00 04 20 || H(32-bytes).
    *           SHA - 512    : (0x)30 51 30 0d 06 09 60 86 48 01 65 03 04 02 03 05 00 04 40 || H(64-bytes).
    *           SHA - 224    : (0x)30 2d 30 0d 06 09 60 86 48 01 65 03 04 02 04 05 00 04 1c || H(28-bytes).
    *           SHA - 384    : (0x)30 41 30 0d 06 09 60 86 48 01 65 03 04 02 02 05 00 04 30 || H(48-bytes).
    *           SHA - 512/224: (0x)30 2d 30 0d 06 09 60 86 48 01 65 03 04 02 05 05 00 04 1c || H(28-bytes).
    *           SHA - 512/256: (0x)30 31 30 0d 06 09 60 86 48 01 65 03 04 02 06 05 00 04 20 || H(48-bytes).
    *
    *   if n = p*q, use CRT mode for the operation.
    *   and, keypair->e is not used.
    * \param[out]   pSign           signed text
    * \param[in]    pDigest         hashed text
    * \param[in]    hashAlgorithm   hash algorithm
    * \param[in]    HmgRsaPrivatekey    rsa privatekey struct
    * \return       success or failure
    * \see
    */
    extern boolean Hmg_RsaPkcs1v15Sign(
        HMG_OUT uint8 pSign[],
        HMG_IN  uint8* pDigest,
        HMG_IN uint32 hashAlgorithm,
        HMG_IN HmgRsaPrivatekey* privatekey
        );


    /** \brief  RSA PKCS1V1.5 sign verify.
    *
    * calculates modular exponent using public key E(uint32)
    *   calculate, (calculated text EC) = (signed text EM) ^ (public exponent) mod (modular N).
    *   verify signiture, compare data EC with pkcs1v15 encoding data.
    *
    *   and, keypair->d is not used.
    * \param[out]   pCM  calcuated text
    * \param[in]    pEM  plain text
    * \param[in]    HmgRsaPublickey rsa publickey struct
    * \return       success or failure
    * \see
    */
    extern boolean Hmg_RsaPkcs1v15Verify(
        HMG_IN uint8 pSign[],
        HMG_IN uint8* pDigest,
        HMG_IN uint32 hashAlgorithm,
        HMG_IN HmgRsaPublickey* publickey
        );

#endif
#ifdef HMG_ENABLE_RSASSA_PKCS1PSS
    /** \brief  RSA PKCS1Pss sign generate.
    *
    * calculates modular exponent using private key D
    *   calculate, (signed text) = (encoding text EM) ^ (private exponent) mod (modular N).
    *       EMSA-PSS encode described in RFC 3447, section 8.1.1
    *       EM = maskedDB || H || 0xbc
    *       maskedDB = DB xor MGF(H)
    *       H  = Hash(M')
    *       M' = padding1 || mHash || salt (padding1 = 0x 00 00 00 00 00 00 00 00)
    *       DB = padding2 || salt          (padding2 = 0x 00 00 ....00 01)
    *       mHash = H(Message)
    *       emBits = modBits - 1 (see RFC 3447, section 8.1.1)
    *
    *   if n = p*q, use CRT mode for the operation.
    *   and, keypair->e is not used.
    * \param[out]   pSign           signed text
    * \param[in]    pssCtx          Pss context struct
    * \param[in]    privatekey      rsa private key struct
    * \return       success or failure
    * \see
    */
    extern boolean Hmg_RsaPkcs1PssSign(
        HMG_OUT uint8 pSign[],
        HMG_IN HmgPkcs1PssCtx* pssCtx,
        HMG_IN HmgRsaPrivatekey* privatekey
        );


    /** \brief  RSA PKCS1Pss sign verify.
    *
    * calculates modular exponent using public key E(uint32)
    *   calculate, (encoding text EC) = (signed text EM) ^ (public exponent) mod (modular N).
    *   verify signiture, compare data EC with PSS encoding data.
    *       EMSA-PSS encode described in RFC 3447, section 8.1.2
    *
    *   and, keypair->d is not used.
    * \param[in]    pSign           signed text
    * \param[in]    pssCtx          Pss context struct
    * \param[in]    keypair         rsa keypair struct
    * \return       success or failure
    * \see
    */
    extern boolean Hmg_RsaPkcs1PssVerify(
        HMG_IN uint8 pSign[],
        HMG_IN HmgPkcs1PssCtx* pssCtx,
        HMG_IN HmgRsaPublickey* publickey
        );

#endif
#ifdef  HMG_ENABLE_RSAES_PKCS1V15

    /** \brief  RSA PKCS#1 Version 1.5 Encryption.
    * calculates modular exponent using public key E(uint32)
    * calculate, (calculated ciphertext EC) = (encoded message EM) ^ (public exponent) mod (modular N).
    * RSAES-PKCS1-v1_5 encode described in RFC 3447, section 7.2.1
    * EM = 0x00 || 0x02 || PS || 0x00 || M
    * PS is non-zero octets of pseudo random string more than 8 length
    *
    * \param[out]   cipher      ciphertext output
    * \param[in]    msg         plaintext input
    * \param[in]    mLen        plaintext length
    * \param[in]    publickey   RSA public key used for encryption
    * \return       success, failure, or invalid length
    * \see
    */
extern boolean Hmg_RsaPkcs1v15Encrypt(
    HMG_OUT uint8 cipher[],
    HMG_IN uint8* msg,
    HMG_IN uint32 mLen,
    HMG_IN HmgRsaPublickey* publickey
    );


    /** \brief  RSA PKCS#1 Version 1.5 Decryption.
    * calculates modular exponent using private key D
    * calculate, (encoded text EM) = (ciphertext) ^ (private exponent) mod (modular N).
    * RSAES-PKCS1-v1_5 encode described in RFC 3447, section 7.2.2
    * EM = 0x00 || 0x02 || PS || 0x00 || M
    * PS is non-zero octets of pseudo random string more than 8 length
    * finally returns the message M and its length
    *
    * \param[out]   msg         plaintext output
    * \param[out]   mLen        plaintext length
    * \param[in]    cipher      ciphertext to be decrypted
    * \param[in]    privatekey  RSA private key used for decryption
    * \return       success, failure, or invalid length
    * \see
    */
    extern boolean Hmg_RsaPkcs1v15Decrypt(
        HMG_OUT uint8* msg,
        HMG_OUT uint32* mLen,
        HMG_IN uint8 cipher[],
        HMG_IN HmgRsaPrivatekey* privatekey
        );
#endif
#ifdef HMG_ENABLE_RSAES_PKCS1OEAP


    /** \brief  RSA PKCS#1 OAEP Encryption.
    *
    * calculates modular exponent using public key E
    * calculate, (ciphertext) = (encoding text EM) ^ (public key exponent) mod (modular N).
    *   RSAES-OAEP encryption described in RFC 3447, section 7.1.1
    *   DB = lHash || PS || 0x01 || M
    *   dbMask = MGF(seed, k-hLen-1)
    *   maskedDB = DB ^ dbMask
    *   seedMask = MGF(maskedDB, hLen)
    *   maskedSeed = seed ^ seedMask
    *   EM = 0x00 || maskedSeed || maskedDB.
    *
    * \param[out]   cipher          ciphertext output
    * \param[in]    msg             plaintext input
    * \param[in]    mLen            plaintext length
    * \param[in]    publickey   RSA public key used for encryption
    * \return       success, invalid value, or invalid length
    * \see
    */
    extern boolean Hmg_RsaPkcs1OaepEncrypt(
        HMG_OUT uint8 cipher[],
        HMG_IN  uint8* msg,
        HMG_IN uint32 mLen,
        HMG_IN HmgPkcs1OaepCtx *oaepCtx,
        HMG_IN HmgRsaPublickey* publickey
        );

    /** \brief  RSA PKCS#1 OAEP Decryption.
    *
    * calculates modular exponent using private key D
    * calculate, (encoded text EM) = (ciphertext) ^ (private exponent) mod (modular N).
    *   RSAES-OAEP decryption described in RFC 3447, section 7.1.2
    *   EM = Y || maskedSeed || maskedDB
    *   seedMask = MGF(maskedDB, hLen)
    *   seed = maskedSeed ^ seedMask
    *   dbMask = MGF(seed, k-hLen-1)
    *   DB = maskedDB ^ dbMask
    *   DB = lHash' || PS || 0x01 || M
    *
    * \param[out]   msg             plaintext output
    * \param[out]   mLen            plaintext length
    * \param[in]    cipher          ciphertext to be decrypted
    * \param[in]    privatekey      RSA private key used for decryption
    * \return       success, invalid value, or invalid length
    * \see
    */
    extern boolean Hmg_RsaPkcs1OaepDecrypt(
        HMG_OUT uint8* msg,
        HMG_OUT uint32* mLen,
        HMG_IN  uint8 cipher[],
        HMG_IN HmgPkcs1OaepCtx *oaepCtx,
        HMG_IN HmgRsaPrivatekey* privatekey
        );

#endif




#ifdef HMG_ENABLE_SLICE

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

#endif //HMG_ENABLE_SLICE



#ifdef  __cplusplus
}
#endif
#endif
