/*-----------------------------------------------------------------------------
* Hyundai-AutoEver Cryptography Library
* Copyright (c) 2015-2016 Hyundai-AutoEver all rights reserved.
------------------------------------------------------------------------------*/
/**
* \file     Hmg_HmacSha256.h
* \date     Jan. 2016.
* \version  1.6.0
* \author   Hyundai_Autoever Automotive Security Techology Team
* \brief    HMAC(The Keyed-Hash Message Authentication Code)-sha256 implementation
* \see      FIPS PUB 198(March 6, 2002)
*/

/* DEFINE TO PREVENT RECURSIVE INCLUSION -------------------------------------*/
#ifndef HMG_HMAC_SHA256_H_
#define HMG_HMAC_SHA256_H_

/* INCLUDES ------------------------------------------------------------------*/
#include "Hmg_Sha256.h"

#define HMG_HMAC_SHA224_DIGEST_SIZE HMG_SHA224_DIGEST_SIZE
#define HMG_HMAC_SHA256_DIGEST_SIZE HMG_SHA256_DIGEST_SIZE

#ifdef  __cplusplus
extern "C" {
#endif

/* EXPORTED DEFINE -----------------------------------------------------------*/
/* EXPORTED MACRO  -----------------------------------------------------------*/
/* EXPORTED TYPES  -----------------------------------------------------------*/

/** \brief Context for HmacSha256 */
typedef struct ctHmacSha256Ctx
{
    HmgSha256Ctx HashCTX;                   /**< context of Sha256                  */
    uint8   okeypad[HMG_SHA256_BLOCK_SIZE]; /**< Outer pad(the byte 0x5c repeated)  */
} HmgHmacSha256Ctx;

/** \brief Context for HmacSha224 */
typedef HmgHmacSha256Ctx HmgHmacSha224Ctx;

/* EXPORTED VARIABLES  -------------------------------------------------------*/
/* EXPORTED FUNCTIONS  -------------------------------------------------------*/

#ifdef HMG_ENABLE_HMAC_SHA224
/** \brief  HmacSha224 start.
*
* initializes Hmac values.
* \param[inout] HmacSha224Ctx   context of HmacSha224
* \param[in]    key             Hmac key
* \param[in]    keyLen          Hmac key length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see          Hmg_Sha224Start, Hmg_Sha224Update, Hmg_Sha224Finish()
*/
extern boolean Hmg_HmacSha224Start(
    HMG_INOUT   HmgHmacSha224Ctx*   HmacSha224Ctx,
    HMG_IN      uint8*              key,
    HMG_IN      uint32              keyLen
    );

/** \brief  HmacSha224 Update.
*
* updates hash context for a block of data
* \param[inout] HmacSha224Ctx   context of HmacSha224
* \param[in]    data            input data
* \param[in]    dataLen         input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see          Hmg_Sha224Update()
*/
extern boolean Hmg_HmacSha224Update(
    HMG_INOUT   HmgHmacSha224Ctx*   HmacSha224Ctx,
    HMG_IN      uint8*              data,
    HMG_IN      uint32              dataLen
    );

/** \brief  HmacSha224 Finish.
*
* digest the final data and ganerates Hmac value.
* \param[inout] HmacSha224Ctx   context of HmacSha224
* \param[out]   hmacValue       output Hmac value
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see          Hmg_Sha224Start, Hmg_Sha224Update, Hmg_Sha224Finish()
*/
extern boolean Hmg_HmacSha224Finish(
    HMG_INOUT   HmgHmacSha224Ctx*   HmacSha224Ctx,
    HMG_OUT     uint8               hmacValue[]
    );

/** \brief  HmacSha224 calculation.
*
* Calculate Hmac sha1 for the input data
* \param[out]   hmacValue   output Hmac value
* \param[in]    key         Hmac key
* \param[in]    keyLen      Hmac key length
* \param[in]    data        input data
* \param[in]    dataLen     input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see          Hmg_HmacSha224Start, Hmg_HmacSha224Update, Hmg_HmacSha224Finish()
*/
extern boolean Hmg_HmacSha224(
    HMG_OUT uint8   hmacValue[],
    HMG_IN  uint8*  key,
    HMG_IN  uint32  keyLen,
    HMG_IN  uint8*  data,
    HMG_IN  uint32  dataLen
    );

#endif
#ifdef HMG_ENABLE_HMAC_SHA256
/** \brief  HmacSha256 start.
*
* initializes Hmac values.
* \param[inout] HmacSha256Ctx   context of HmacSha256
* \param[in]    key             Hmac key
* \param[in]    keyLen          Hmac key length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see          Hmg_Sha256Start, Hmg_Sha256Update, Hmg_Sha256Finish()
*/
extern boolean Hmg_HmacSha256Start(
    HMG_INOUT   HmgHmacSha256Ctx*   HmacSha256Ctx,
    HMG_IN      uint8*              key,
    HMG_IN      uint32              keyLen
    );

/** \brief  HmacSha256 Update.
*
* updates hash context for a block of data
* \param[inout] HmacSha256Ctx   context of HmacSha256
* \param[in]    data            input data
* \param[in]    dataLen         input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see          Hmg_Sha256Update()
*/
extern boolean Hmg_HmacSha256Update(
    HMG_INOUT HmgHmacSha256Ctx*     HmacSha256Ctx,
    HMG_IN      uint8*              data,
    HMG_IN      uint32              dataLen
    );

/** \brief  HmacSha256 Finish.
*
* digest the final data and ganerates Hmac value.
* \param[inout] HmacSha256Ctx   context of HmacSha256
* \param[out]   hmacValue       output Hmac value
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see          Hmg_Sha256Start, Hmg_Sha256Update, Hmg_Sha256Finish()
*/
extern boolean Hmg_HmacSha256Finish(
    HMG_INOUT   HmgHmacSha256Ctx*   HmacSha256Ctx,
    HMG_OUT     uint8               hmacValue[]
    );

/** \brief  HmacSha256 calculation.
*
* Calculate Hmac sha1 for the input data
* \param[out]   hmacValue   output Hmac value
* \param[in]    key         Hmac key
* \param[in]    keyLen      Hmac key length
* \param[in]    data        input data
* \param[in]    dataLen     input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see          Hmg_HmacSha256Start, Hmg_HmacSha256Update, Hmg_HmacSha256Finish()
*/
extern boolean Hmg_HmacSha256(
    HMG_OUT uint8   hmacValue[],
    HMG_IN  uint8*  key,
    HMG_IN  uint32  keyLen,
    HMG_IN  uint8*  data,
    HMG_IN  uint32  dataLen
    );

#endif

#ifdef  __cplusplus
}
#endif

#endif
