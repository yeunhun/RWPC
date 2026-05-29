/**
 * \file    Hmg_Aes.h
 * \author  Hyundai Autoever Automotive Security Techology Team
 * \brief   AES(Advanced Encryption Standard)-Rijndael encryption implementat
 * \see     FIPS PUB 197
*/

/* DEFINE TO PREVENT RECURSIVE INCLUSION -------------------------------------*/

#ifndef HMG_AES_H_
#define HMG_AES_H_

/* INCLUDES ------------------------------------------------------------------*/

#include "Hmg_Common.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/* EXPORTED DEFINE -----------------------------------------------------------*/


/*  This provides speed optimisation opportunities if 32-bit word
    operations are available
*/
#define HMG_AES_N_BLOCK                 16U
#define HMG_AES_N_ROUND                 14U
#define HMG_AES_CMAC_TAG_LEN            16U
/* EXPORTED MACRO  -----------------------------------------------------------*/
/* EXPORTED TYPES  -----------------------------------------------------------*/

/** \brief AES context structure */
    typedef struct ctAesCtx
    {
        uint8 round;    /**< rounds: 10/12/14 decided from key size */
        uint8 opmode;   /**< if cbcmode set on, only final output is return */
        uint8 dummy1;
        uint8 dummy2;
        uint32 ksch[(HMG_AES_N_ROUND + 2U) * 4]; /**< key scheduling */
    } HmgAeskeyCtx;

    /** \brief  AES CCM mode context
    *
    * \param[in]    key         key input to be encrypted or decrypted
    * \param[in]    keyLen      key input length
    * \param[in]    data        data input to be encrypted or decrypted
    * \param[in]    dataLen     data input length
    * \param[in]    adata       Associated Data
    * \param[in]    adataLen    Associated Data length
    * \param[in]    nonce       Nonce input
    * \param[in]    nonceLen    Nonce length
    * \param[in]    tagLen      Tag length(MAC length)
    */
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



#define HMG_GCM_TAG_SIZE    16U
#define HMG_GCM_MAX_LEN     0x1FFFFFFFU /* 536,870,911 <= max bit length = 2^32 - 1 <== byte length: 2^32 / 8 */

    /** \brief  AES GCM mode context
    *
    * \param[in]    key         key input to be encrypted or decrypted
    * \param[in]    keyLen      key input length
    * \param[in]    data        data input to be encrypted or decrypted
    * \param[in]    dataLen     data input length
    * \param[in]    iv          initial vector Data
    * \param[in]    ivLen       initial vector Data length
    * \param[in]    add         Additional Data
    * \param[in]    addLen      Additional Data length
    */
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




    /** \brief  AES CMAC mode context */
    typedef struct ctAesCmacCtx {
        HmgAeskeyCtx aesCtx;
        uint8 macData[HMG_AES_N_BLOCK];
        uint8 block[HMG_AES_N_BLOCK];
        uint32 blockLen;
        uint32 totalLen;
    } HmgAesCmacCtx;


    /** \brief  AES XTS mode context
    *
    * \param[in]    key1            key context1 for aes-xts
    * \param[in]    key2            key context2 for aes-xts
    */
    typedef struct ctAesXtsCtx {
        HmgAeskeyCtx keySet1;
        HmgAeskeyCtx keySet2;
    } HmgAesXtsCtx;


/** \brief AES OFB context structure */
typedef struct stHmgAesOfbCtx
{
    HmgAeskeyCtx aeskey;
    uint8 buff[HMG_AES_N_BLOCK];
    uint8 block[HMG_AES_N_BLOCK];
    uint32 blockLen;
    uint32 totalLen;
} HmgAesOfbCtx;

    /****************************************************************************/

    typedef struct stHmgAesCtrCtx
    {
        HmgAeskeyCtx aeskey;
        uint8 iv[HMG_AES_N_BLOCK];
        uint8 block[HMG_AES_N_BLOCK];
        uint32 blockLen;
        uint32 totalLen;
    } HmgAesCtrCtx;


    boolean Hmg_AesCtrStart(
        HMG_INOUT HmgAesCtrCtx* aesCtrCtx,
        HMG_IN uint8 iv[],
        HMG_IN uint8 key[],
        HMG_IN uint8 keyLen
        );

    boolean Hmg_AesCtrUpdate(
        HMG_INOUT HmgAesCtrCtx* aesCtrCtx,
        HMG_OUT uint8* out,
        HMG_IN uint8* in,
        HMG_IN uint32 inLen
        );

    boolean Hmg_AesCtrFinish(
        HMG_INOUT HmgAesCtrCtx* aesCtrCtx,
        HMG_OUT uint32* totalLen
        );

    /****************************************************************************/


/* EXPORTED VARIABLES  -------------------------------------------------------*/
/* EXPORTED FUNCTIONS  -------------------------------------------------------*/

/** \brief  AES key expansion.
*
* Generates key expansion used for AES Encrypt or decrypt fuctions.
* \param[out]   aesCtx      key expansion output for AES CBC mode operation
* \param[in]    key         AES key
* \param[in]    keyLen      AES key length (valid inputs are 16, 24 and 32 (bytes))
* \return       success or failure
* \see
*/
boolean Hmg_AesSetKey(
    HMG_OUT HmgAeskeyCtx* aesCtx,
    HMG_IN uint8* key,
    HMG_IN uint8 keylen
    );


#ifdef HMG_ENABLE_AES_ECB
/** \brief  AES ECB mode Encryption
*
* Generate ciphertext with ECB(Electronic Codebook) mode on AES.
* \param[inout] aesCtx      key expansion value
* \param[out]   cipher      Encrypted ciphertext output
* \param[in]    plain       Plaintext input to be encrypted
* \param[in]    plainLen    Plaintext length
* \return       success or failure
* \see          Hmg_AesKeySet, Hmg_AesEnc()
*/
boolean Hmg_AesEcbEnc(
    HMG_INOUT HmgAeskeyCtx* aesCtx,
    HMG_OUT uint8* cipher,
    HMG_IN uint8* plain,
    HMG_IN uint32 plainLen
    );


/** \brief  AES ECB mode Decryption
*
* Generate Plaintext with ECB(Electronic Codebook) mode on AES.
* \param[inout] aesCtx      key expansion value
* \param[out]   plain       decrypted plaintext output
* \param[in]    cipher      ciphertext input to be decrypted
* \param[in]    cipherLen   ciphertext length
* \return       success or failure
* \see          Hmg_AesKeySet, Hmg_AesDec()
*/
boolean Hmg_AesEcbDec(
    HMG_INOUT HmgAeskeyCtx* aesCtx,
    HMG_OUT uint8* plain,
    HMG_IN uint8* cipher,
    HMG_IN uint32 cipherLen
    );
#endif

#ifdef HMG_ENABLE_AES_CBC

/** \brief  AES CBC mode Encryption
*
* Generate ciphertext with CBC(Cipher Block Chaining) mode on AES.
* \param[inout] aesCtx      key expansion value and initial vector value
* \param[inout] ivec        initial vector
* \param[out]   cipher      Encrypted ciphertext output
* \param[in]    plain       Plaintext input to be encrypted
* \param[in]    plainLen    Plaintext length
* \return       success or failure
* \see          Hmg_AesKeySet(), Hmg_AesEnc()
*/
boolean Hmg_AesCbcEnc(
    HMG_INOUT HmgAeskeyCtx* aesCtx,
    HMG_INOUT uint8 iv[],
    HMG_OUT uint8* cipher,
    HMG_IN uint8* plain,
    HMG_IN uint32 plainLen
    );

/** \brief  AES CBC mode Decryption
*
* Generate Plaintext with CBC(Cipher Block Chaining) mode on AES.
* \param[inout] aesCtx      key expansion value and initial vector value
* \param[inout] ivec        initial vector
* \param[out]   plain       decrypted plaintext output
* \param[in]    cipher      ciphertext input to be decrypted
* \param[in]    cipherLen   ciphertext length
* \return       success or failure
* \see          Hmg_AesCbcKeySet, Hmg_AesKeySet, Hmg_AesDec()
*/
boolean Hmg_AesCbcDec(
    HMG_INOUT HmgAeskeyCtx* aesCtx,
    HMG_INOUT uint8 iv[],
    HMG_OUT uint8* plain,
    HMG_IN uint8* cipher,
    HMG_IN uint32 cipherLen
    );
#endif

#ifdef HMG_ENABLE_AES_OFB

/** \brief  AES OFB mode Operation.  version 1.7.0
*
* Generate ciphertext with OFB mode on AES.
* \param[inout] aesCtx      expanded key and initial vector value
* \param[inout] ivec        initial vector
* \param[out]   out     Encrypted ciphertext output
* \param[in]    in      Plaintext input to be encrypted
* \param[in]    inLen   Plaintext length
* \return       success or failure
* \see          Hmg_AesEnc()
*/
boolean Hmg_AesOfb(
    HMG_IN HmgAeskeyCtx* aesCtx,
    HMG_IN uint8 iv[],
    HMG_OUT uint8* out,
    HMG_IN uint8* in,
    HMG_IN uint32 inLen
    );

boolean Hmg_AesOfbStart(
    HMG_INOUT HmgAesOfbCtx* aesOfbCtx,
    HMG_IN uint8 iv[],
    HMG_IN uint8 key[],
    HMG_IN uint8 keyLen
    );

boolean Hmg_AesOfbUpdate(
    HMG_INOUT HmgAesOfbCtx* aesOfbCtx,
    HMG_OUT uint8* out,
    HMG_IN uint8* in,
    HMG_IN uint32 inLen
    );

boolean Hmg_AesOfbFinish(
    HMG_IN HmgAesOfbCtx* aesOfbCtx,
    HMG_OUT uint32* totalLen
    );
#endif

#ifdef HMG_ENABLE_AES_CTR
/** \brief  AES CTR mode Operation.
*
* Generate ciphertext with CTR(Counter) mode on AES.
* \param[inout] aesCtx      expanded key and initial vector value
* \param[inout] ivec        initial vector
* \param[out]   out     Encrypted ciphertext output
* \param[in]    in      Plaintext input to be encrypted
* \param[in]    inLen   Plaintext length
* \return       success or failure
* \see          Hmg_AesEnc()
*/
boolean Hmg_AesCtr(
    HMG_INOUT HmgAeskeyCtx* aesCtx,
    HMG_INOUT uint8 iv[],
    HMG_OUT uint8* out,
    HMG_IN uint8* in,
    HMG_IN uint32 inLen
    );
#endif


#ifdef HMG_ENABLE_AES_CCM

/** \brief  AES CCM mode Encryption
*
* Generate ciphertext with CCM(Counter with Cipher Block Chaining-Message Authentication Code) mode on AES.
* \param[in]    ccmCtx      key expansion value and initial vector value
* \param[out]   cipher      Encrypted ciphertext output
* \param[out]   cipherLen   Encrypted ciphertext output Length(plainLen + tagLen)

* \return       success or failure
* \see          Hmg_AesKeySet, Hmg_AesCbcEnc, Hmg_AesCtr()
*/
boolean Hmg_AesCcmEnc(
    HMG_OUT uint8* cipher,
    HMG_OUT uint32* cipherLen,
    HMG_IN HmgAesCcmCtx *ccmCtx
    );

/** \brief  AES CCM mode Encryption
*
* Generate plaintext and check validation with CCM(Counter with Cipher Block Chaining-Message Authentication Code) mode on AES.
* \param[inout] aesCtx      key expansion value and initial vector value
* \param[out]   plain       Decrypted plaintext output
* \param[out]   plainLen    Decrypted plaintext output Length(cipherLen - tagLen)
* \see          Hmg_AesKeySet, Hmg_AesCbcEnc, Hmg_AesCtr()
*/
boolean Hmg_AesCcmDec(
    HMG_OUT uint8* plain,
    HMG_OUT uint32* plainLen,
    HMG_IN HmgAesCcmCtx *ccmCtx
    );

#endif

#ifdef HMG_ENABLE_AES_CBCMAC
/** \brief  AES Cbcmac(CBC-MAC)
*
* Generate CBC-MAC mode on AES.
* \param[out]   tag         MAC data output
* \param[in]    key         16, 24, 32 bytes symmetric key
* \param[in]    keyLen      symmetric key length
* \param[in]    msg         Message input to be digested
* \param[in]    msgLen      Message length
* \return       success or failure
* \see          Hmg_AesKeySet, Hmg_AesCbcEnc
*/
boolean Hmg_AesCbcmac(
    HMG_OUT uint8 *tag,
    HMG_IN uint8 *key,
    HMG_IN uint8 keyLen,
    HMG_IN uint8 *msg,
    HMG_IN uint32 msgLen
    );
#endif

#ifdef HMG_ENABLE_AES_CMAC


/** \brief  AES Cmac Start(CBC message Authentication code)
*
* Init CMAC mode on AES.
* \param[in]    HmgAesCmacCtx       CMAC data Context
* \param[in]    key         16, 24, 32 bytes symmetric key
* \param[in]    keyLen      symmetric key length
* \return       success or failure
* \see          Hmg_AesCmac()
*/
boolean Hmg_AesCmacStart(
    HMG_INOUT HmgAesCmacCtx *cmacCtx,
    HMG_IN uint8 *key,
    HMG_IN uint8  keyLen
    );

/** \brief  AES Cmac Update(CBC message Authentication code)
*
* Update CMAC Data on AES.
* \param[in]    cmacCtx     CMAC data Context
* \param[in]    msg         Message input to be digested
* \param[in]    msgLen      Message length
* \return       success or failure
* \see          Hmg_AesCmac()
*/
boolean Hmg_AesCmacUpdate(
    HMG_INOUT HmgAesCmacCtx *cmacCtx,
    HMG_IN uint8 *msg,
    HMG_IN uint32 msgLen
    );

/** \brief  AES Cmac Finish(CBC message Authentication code)
*
* Generate CMAC mode on AES.
* \param[in]    cmacCtx     CMAC data Context
* \param[out]   tag         MAC data output
* \return       success or failure
* \see          Hmg_AesCmac()
*/
boolean Hmg_AesCmacFinish(
    HMG_INOUT HmgAesCmacCtx *cmacCtx,
    HMG_OUT uint8 tag[16]
    );



/** \brief  AES Cmac(CBC message Authentication code)
*
* Generate CMAC mode on AES.
* \param[out]   tag         MAC data output
* \param[in]    key         16, 24, 32 bytes symmetric key
* \param[in]    keyLen      symmetric key length
* \param[in]    msg         Message input to be digested
* \param[in]    msgLen      Message length
* \return       success or failure
* \see          Hmg_AesKeySet, Hmg_AesCbcEnc, Hmg_AesCtr()
*/
boolean Hmg_AesCmac(
    HMG_OUT uint8 tag[HMG_AES_CMAC_TAG_LEN],
    HMG_IN uint8 *key,
    HMG_IN uint8 keyLen,
    HMG_IN uint8 *msg,
    HMG_IN uint32 msgLen
    );


#endif

#ifdef HMG_ENABLE_AES_GCM


/** \brief  AES GMC Encryption
* \param[out]   cipher      Encrypted ciphertext output
* \param[out]   tag         tag data output
* \param[in]    gcmCtx      The AES GCM mode input data context.
* \return       success or failure
*/
boolean Hmg_AesGcmEnc(
    HMG_OUT uint8 *cipher,
    HMG_OUT uint8 tag[HMG_GCM_TAG_SIZE],
    HMG_IN HmgAesGcmCtx *gcmCtx
    );

/** \brief  AES GMC Decryption
* \param[out]   plain       Encrypted plaintext output
* \param[in]    tag         tag data input
* \param[in]    gcmCtx      The AES GCM mode input data context.
* \return       success or failure
*/
boolean Hmg_AesGcmDec(
    HMG_OUT uint8 *plain,
    HMG_IN uint8 tag[HMG_GCM_TAG_SIZE],
    HMG_IN HmgAesGcmCtx *gcmCtx
    );

/** \brief  AES GMC Decryption
* \param[out]   plain       Encrypted plaintext output
* \param[in]    tag         tag data input
* \param[in]    taglen      tag data length input
* \param[in]    gcmCtx      The AES GCM mode input data context.
* \return       success or failure
*/
boolean Hmg_AesGcmDec_ext(
    HMG_OUT uint8 *plain,
    HMG_IN uint8 *tag,
    HMG_IN uint32 taglen,
    HMG_IN HmgAesGcmCtx *gcmCtx
    );

/** \brief  AES GMC Tag generatiion
* \param[out]   tag         tag data output
* \param[in]    gcmCtx      The AES GCM mode input data context.
* \return       success or failure
*/
boolean Hmg_AesGmac(
    HMG_OUT uint8 tag[HMG_GCM_TAG_SIZE],
    HMG_IN HmgAesGcmCtx *gcmCtx
    );

#endif


#ifdef HMG_ENABLE_AES_XTS


/**
Initializes the AES-XTS Context with the corresponding AES keys.

\param[out] xtsCtx The AES XTS context.
\param[in] key1 Key bytes array. Array of size HmgAes_KEY_BYTES
\param[in] key2 Key bytes array. Array of size HmgAes_KEY_BYTES.

\return TRUE on error.
*/

extern boolean Hmg_AesXtsSetkey(
    HMG_INOUT HmgAesXtsCtx* xtsCtx,
    HMG_IN uint8 key1[],
    HMG_IN uint8 key2[],
    HMG_IN uint8 keyLength
    );



/**
  Encrypts one data unit (i.e., sector).

  The context must be initialized with HacAesXts_Init.

  \param[in] xtsCtx initialized AES XTS context.
  \param[in] plain Plaintext to encrypt.
  \param[out] cipher Array to write ciphertext to.
  \param[in] length Length of plain and cipher data in bytes. Has to be at least HacAes_BLOCK_BYTES bytes.
  \param[in] tweak tweak value. Array of size HacAes_BLOCK_BYTES.

  \return TRUE on error.
  */
extern boolean Hmg_AesXtsEnc(
    HMG_INOUT HmgAesXtsCtx* xtsCtx,
    HMG_OUT uint8 *cipher,
    HMG_IN uint8 *plain,
    HMG_IN uint32 length,
    HMG_IN uint8 tweak[]
    );


/**
  Encrypts one data unit (i.e., sector) based on the sector number.

  The context must be initialized with HacAesXts_Init.

  plain pointer and cipher pointer may not overlap.

  \param[in] xtsCtx initialized AES XTS context.
  \param[in] plain Plaintext to encrypt.
  \param[out] cipher Array to write ciphertext to.
  \param[in] length Length of plain and cipher data in bytes. Has to be at least HacAes_BLOCK_BYTES bytes.
  \param[in] data_unit_number sector number.

  \return TRUE on error.
  */
extern boolean Hmg_AesXtsEncSector(
    HMG_INOUT HmgAesXtsCtx* xtsCtx,
    HMG_OUT uint8 *cipher,
    HMG_IN uint8 *plain,
    HMG_IN uint32 length,
    HMG_IN uint64 dataUnitNumber
    );



/**
  Decrypts one data unit (i.e., sector).

  The context must be initialized with HacAesXts_Init.

  \param[in] xtsCtx initialized AES XTS context.
  \param[in] cipher Ciphertext to decrypt.
  \param[out] plain Array to write plaintext to encrypt.
  \param[in] length Length of plain and cipher data in bytes. Has to be at least HacAes_BLOCK_BYTES bytes.
  \param[in] tweak tweak value. Array of size HacAes_BLOCK_BYTES.

  \return TRUE on error.
  */

extern boolean Hmg_AesXtsDec(
    HMG_INOUT HmgAesXtsCtx* xtsCtx,
    HMG_OUT uint8 *plain,
    HMG_IN uint8 *cipher,
    HMG_IN uint32 length,
    HMG_IN uint8 tweak[]
    );

/**
  Decrypts one data unit (i.e., sector) based on the sector number.

  The context must be initialized with HacAesXts_Init.

  plain pointer and cipher pointer may not overlap.

  \param[in] xtsCtx initialized AES XTS context.
  \param[in] cipher Ciphertext to decrypt.
  \param[out] plain Array to write plaintext to encrypt.
  \param[in] length Length of plain and cipher data in bytes. Has to be at least HacAes_BLOCK_BYTES bytes.
  \param[in] data_unit_number sector number.

  \return TRUE on error.
  */

extern boolean Hmg_AesXtsDecSector(
    HMG_INOUT HmgAesXtsCtx* xtsCtx,
    HMG_OUT uint8 *plain,
    HMG_IN uint8 *cipher,
    HMG_IN uint32 length,
    HMG_IN uint64 dataUnitNumber
    );
#endif


#if defined(__cplusplus)
}
#endif

#endif
