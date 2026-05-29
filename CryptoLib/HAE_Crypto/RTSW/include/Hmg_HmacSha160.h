/*-----------------------------------------------------------------------------
* Hyundai-AutoEver Cryptography Library
* Copyright (c) 2015-2016 Hyundai-AutoEver all rights reserved.
------------------------------------------------------------------------------*/
/**
* \file     Hmg_HmacSha160.h
* \date     Jan. 2016.
* \version  1.6.0
* \author   Hyundai_Autoever Automotive Security Techology Team
* \brief    HMAC(The Keyed-Hash Message Authentication Code)-sha1 implementation
* \see      FIPS PUB 198(March 6, 2002)
*/

/* DEFINE TO PREVENT RECURSIVE INCLUSION -------------------------------------*/
#ifndef HMG_HMAC_SHA160_H_
#define HMG_HMAC_SHA160_H_

/* INCLUDES ------------------------------------------------------------------*/
#include "Hmg_Sha160.h"

#define HMG_HMAC_SHA160_DIGEST_SIZE HMG_SHA160_DIGEST_SIZE

#ifdef  __cplusplus
extern "C" {
#endif

/* EXPORTED DEFINE -----------------------------------------------------------*/
/* EXPORTED MACRO  -----------------------------------------------------------*/
/* EXPORTED TYPES  -----------------------------------------------------------*/


/** \brief Context for HmacSha160 */
typedef struct ctHmacSha160Ctx
{
    HmgSha160Ctx HashCTX;                   /**< context of Sha1                    */
    uint8   okeypad[HMG_SHA160_BLOCK_SIZE]; /**< Outer pad(the byte 0x5c repeated)  */
} HmgHmacSha160Ctx;

/* EXPORTED VARIABLES  -------------------------------------------------------*/
/* EXPORTED FUNCTIONS  -------------------------------------------------------*/

#ifdef HMG_ENABLE_HMAC_SHA160
/** \brief  HmacSha160 start.
*
* initializes Hmac values.
* \param[inout] HmacSha160Ctx   context of HmacSha1
* \param[in]    key         Hmac key
* \param[in]    keyLen      Hmac key length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see          Hmg_Sha160Start, Hmg_Sha160Update, Hmg_Sha160Finish()
*/
extern boolean Hmg_HmacSha160Start(
    HMG_INOUT   HmgHmacSha160Ctx*   HmacSha160Ctx,
    HMG_IN      uint8*          key,
    HMG_IN      uint32          keyLen
    );

/** \brief  HmacSha160 Update.
*
* updates hash context for a block of data
* \param[inout] HmacSha160Ctx   context of HmacSha1
* \param[in]    data        input data
* \param[in]    dataLen     input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see          Hmg_Sha160Update()
*/
extern boolean Hmg_HmacSha160Update(
    HMG_INOUT   HmgHmacSha160Ctx*   HmacSha160Ctx,
    HMG_IN      uint8*          data,
    HMG_IN      uint32          dataLen
    );

/** \brief  HmacSha160 Finish.
*
* digest the final data and ganerates Hmac value.
* \param[inout] HmacSha160Ctx   context of HmacSha1
* \param[out]   hmacValue   output Hmac value
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see          Hmg_Sha160Start, Hmg_Sha160Update, Hmg_Sha160Finish()
*/
extern boolean Hmg_HmacSha160Finish(
    HMG_INOUT HmgHmacSha160Ctx* HmacSha160Ctx,
    HMG_OUT uint8 hmacValue[]
    );

/** \brief  HmacSha1 calculation.
*
* Calculate Hmac sha1 for the input data
* \param[out]   hmacValue   output Hmac value
* \param[in]    key         Hmac key
* \param[in]    keyLen      Hmac key length
* \param[in]    data        input data
* \param[in]    dataLen     input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see          Hmg_HmacSha1Start, Hmg_HmacSha1Update, Hmg_HmacSha1Finish()
*/
extern boolean Hmg_HmacSha160(
    HMG_OUT uint8 hmacValue[],
    HMG_IN uint8* key,
    HMG_IN uint32 keyLen,
    HMG_IN uint8* data,
    HMG_IN uint32 dataLen
    );
#endif //HMG_ENABLE_HMAC_SHA160

#ifdef  __cplusplus
}
#endif

#endif //HMG_HMAC_SHA160_H_
