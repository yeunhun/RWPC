/*-----------------------------------------------------------------------------
* Hyundai-AutoEver Cryptography Library
* Copyright (c) 2015-2016 Hyundai-AutoEver all rights reserved.
------------------------------------------------------------------------------*/
/**
* \file     Hmg_Ecies.h
* \date     April. 2017.
* \version  1.6.0
* \author   Hyundai_Autoever Automotive Security Techology Team
* \brief    ECIES implementation
* \see
*
*/


#ifndef HMG_ECIES_H_
#define HMG_ECIES_H_

/* INCLUDES ------------------------------------------------------------------*/
#include "Hmg_Common.h"
#include "Hmg_Ecc.h"
#include "Hmg_Sha256.h"

#ifdef  __cplusplus
extern "C" {
#endif

/* EXPORTED DEFINE -----------------------------------------------------------*/

/* Sizes of elements - sizes over 32 bytes may cause buffer overflows */
#define HMG_ECIES_TAG_BYTES         16U
#define HMG_ECIES_DIGEST_BYTES      HMG_SHA256_DIGEST_SIZE  /* Output size of HMAC HASH*/
#define HMG_ECIES_KEY_BYTES         16U
#define HMG_ECIES_PARAM_BYTES       32U
#define HMG_ECIES_SECRET_BYTES      32U
#define HMG_ECIES_MSG_MAX_BYTES     32U


/* Perform validation on public keys before ECSVCP */
#define HMG_ECIES_VALIDATE_KEY

/* Encryption mode, specified when calling ECIES functions */
#define HMG_ECIES_XOR_ENC   1U /* KDF output XOR as stream cipher*/
#define HMG_ECIES_AES_CTR   2U /* AES_CTR_IV0 [ephemeral Key (see SEC1)]*/
#define HMG_ECIES_AES_CBC   3U /* AES_CBC_IV0*/




/* EXPORTED TYPES  -----------------------------------------------------------*/

typedef struct {
    const   HmgEcPublickey* pubKey;
    uint32  encMsgLen;
    uint8   encMsg[HMG_ECIES_MSG_MAX_BYTES];
    uint8   macTag[HMG_ECIES_TAG_BYTES];
} HmgEcies_sPDU;


/* EXPORTED FUNCTIONS---------------------------------------------------------*/

#ifdef HMG_ENABLE_ECC_ECIES
/*  \brief ECIES Encryption as used in IEEE 1609.2-2016
*   \param[out] sPdu            Secured protocol data unit
*   \param[in]  uint8*          Sender private key (used to calculate ECSVSP)
*   \param[in]  ECC_Publickey*  Sender ephemeral public key (V, attached to output)
*   \param[in]  ECC_Publickey*  Receiver public key (used to calculate ECSVDP)
*   \param[in]  uint8*          Message to be encrypted
*   \param[in]  uint32          length of message (must be 16 for XOR, a multiple of 16 for CBC)
*   \param[in]  uint8*          P1, used to calculate KDF, should be output of SHA256
*   \param[in]  uint8           encryption mode, either HMG_ECIES_AES_CTR, HMG_AES_CBC HMG_ECIES_XOR_ENC
*   \return HMG_SUCCESS, HMG_NO_FUNCTION, HMG_INVALID_VALUE, HMG_INVALID_LENGTH or HMG_FAILURE */
boolean Hmg_EciesEncrypt(
    HMG_OUT HmgEcies_sPDU* sPdu,
    HMG_IN uint8*   privateKeyA,
    HMG_IN HmgEcPublickey* publicKeyA,
    HMG_IN HmgEcPublickey* publicKeyB,
    HMG_IN uint8*   message,
    HMG_IN uint32   mLen,
    HMG_IN uint8*   param1,
    HMG_IN uint8    encMode
    );





/*  \brief ECIES Decryption as used in IEEE 1609.2-2016
*   \param[out] uint8*          Decrypted message
*   \param[in]  uint8*          Sender private key (used to calculate ECSVSP)
*   \param[in]  ECC_Publickey*  Sender ephemeral public key (V, attached to output)
*   \param[in]  sPdu            Secured protocol data unit
*   \param[in]  uint8*          Message to be encrypted
*   \param[in]  uint8*          P1, used to calculate KDF, should be output of SHA256
*   \param[in]  uint8           encryption mode, either HMG_ECIES_AES_CTR or HMG_ECIES_XOR_ENC
*   \return HMG_SUCCESS, HMG_NO_FUNCTION, HMG_INVALID_VALUE, HMG_INVALID_LENGTH or HMG_FAILURE
*   if HMAC check fails, output is HMG_INVALID_VALUE. */
boolean Hmg_EciesDecrypt(
    HMG_OUT uint8*      decMessage,
    HMG_IN HmgEcies_sPDU*   sPdu,
    HMG_IN uint8*       privKey,
    HMG_IN uint8*       param1,
    HMG_IN uint8        encMode
    );

#endif


#ifdef HMG_ENABLE_SLICE /* if ECC slicing is enabled */

/* \brief separate the calculation of ECSVDP into HMG_SLICE_ECC number of slices*/
/* Requires an additional 436 bytes of memory and is slightly slower*/
boolean Hmg_EciesEncryptStart(HMG_INOUT HmgEccSliceCtx* slCtx, HMG_IN uint8* privateKeyA, HMG_IN HmgEcPublickey* publicKeyB);
boolean Hmg_EciesEncryptUpdate(HMG_INOUT HmgEccSliceCtx* slCtx);
boolean Hmg_EciesEncryptFinish(
    HMG_INOUT HmgEccSliceCtx* slCtx,
    HMG_OUT HmgEcies_sPDU* sPdu,
    HMG_IN HmgEcPublickey*  publicKeyA,
    HMG_IN uint8* message,
    HMG_IN uint32 mLen,
    HMG_IN uint8* param1,
    HMG_IN uint8 encMode
    );



/* \brief separate the calculation of ECSVDP into HMG_SLICE_ECC number of slices*/
/* Requires an additional 436 bytes of memory and is slightly slower*/
boolean Hmg_EciesDecryptStart(HMG_INOUT HmgEccSliceCtx* slCtx, HMG_IN uint8* privKey, HMG_IN HmgEcPublickey* pubKey);
boolean Hmg_EciesDecryptUpdate(HMG_INOUT HmgEccSliceCtx* slCtx);
boolean Hmg_EciesDecryptFinish(
    HMG_INOUT HmgEccSliceCtx* slCtx,
    HMG_OUT uint8* decMessage,
    HMG_IN  HmgEcies_sPDU* sPdu,
    HMG_IN uint8* param1,
    HMG_IN uint8 encMode);

#endif //HMG_ENABLE_SLICE

#ifdef  __cplusplus
}
#endif

#endif //HMG_ECIES_H_
