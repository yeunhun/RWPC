/*-----------------------------------------------------------------------------
* Hyundai-AutoEver Cryptography Library
* Copyright (c) 2015-2016 Hyundai-AutoEver all rights reserved.
------------------------------------------------------------------------------*/
/**
* \file     Hmg_HmacSha512.h
* \date     Jan. 2016.
* \version  1.6.0
* \author   Hyundai_Autoever Automotive Security Techology Team
* \brief    HMAC(The Keyed-Hash Message Authentication Code)-sha512 implementation
* \see      FIPS PUB 198(March 6, 2002)
*/
/* DEFINE TO PREVENT RECURSIVE INCLUSION -------------------------------------*/
#ifndef HMG_HMAC_SHA512_H_
#define HMG_HMAC_SHA512_H_

/* INCLUDES ------------------------------------------------------------------*/
#include "Hmg_Sha512.h"

#define HMG_HMAC_SHA384_DIGEST_SIZE HMG_SHA384_DIGEST_SIZE
#define HMG_HMAC_SHA512_DIGEST_SIZE HMG_SHA512_DIGEST_SIZE

#ifdef  __cplusplus
extern "C" {
#endif

/* EXPORTED DEFINE -----------------------------------------------------------*/
/* EXPORTED MACRO  -----------------------------------------------------------*/
/* EXPORTED TYPES  -----------------------------------------------------------*/

/** \brief Context for HmacSha512 */
typedef struct ctHmacSha512Ctx
{
    HmgSha512Ctx HashCTX;                       /**< context of Sha512                  */
    uint8   okeypad[HMG_SHA512_BLOCK_SIZE];     /**< Outer pad(the byte 0x5c repeated)  */
} HmgHmacSha512Ctx;

/** \brief Context for HmacSha384 */
typedef HmgHmacSha512Ctx HmgHmacSha384Ctx;

/* EXPORTED VARIABLES  -------------------------------------------------------*/
/* EXPORTED FUNCTIONS  -------------------------------------------------------*/

#ifdef HMG_ENABLE_HMAC_SHA384
/** \brief  HmacSha384 start.
*
* initializes Hmac values.
* \param[inout] HmacSha384Ctx   context of HmacSha384
* \param[in]    key             Hmac key
* \param[in]    keyLen          Hmac key length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see          Hmg_Sha384Start, Hmg_Sha384Update, Hmg_Sha384Finish()
*/
extern boolean Hmg_HmacSha384Start(
    HMG_INOUT   HmgHmacSha384Ctx*   HmacSha384Ctx,
    HMG_IN      uint8*              key,
    HMG_IN      uint32              keyLen
    );

/** \brief  HmacSha384 Update.
*
* updates hash context for a block of data
* \param[inout] HmacSha384Ctx   context of HmacSha384
* \param[in]    data            input data
* \param[in]    dataLen         input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see          Hmg_Sha384Update()
*/
extern boolean Hmg_HmacSha384Update(
    HMG_INOUT   HmgHmacSha384Ctx*   HmacSha384Ctx,
    HMG_IN      uint8*              data,
    HMG_IN      uint32              dataLen
    );

/** \brief  HmacSha384 Finish.
*
* digest the final data and ganerates Hmac value.
* \param[inout] HmacSha384Ctx   context of HmacSha384
* \param[out]   hmacValue       output Hmac value
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see          Hmg_Sha384Start, Hmg_Sha384Update, Hmg_Sha384Finish()
*/
extern boolean Hmg_HmacSha384Finish(
    HMG_INOUT   HmgHmacSha384Ctx*   HmacSha384Ctx,
    HMG_OUT     uint8               hmacValue[]
    );

/** \brief  HmacSha384 calculation.
*
* Calculate Hmac sha1 for the input data
* \param[out]   hmacValue   output Hmac value
* \param[in]    key         Hmac key
* \param[in]    keyLen      Hmac key length
* \param[in]    data        input data
* \param[in]    dataLen     input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see          Hmg_HmacSha384Start, Hmg_HmacSha384Update, Hmg_HmacSha384Finish()
*/
extern boolean Hmg_HmacSha384(
    HMG_OUT uint8   hmacValue[],
    HMG_IN  uint8*  key,
    HMG_IN  uint32  keyLen,
    HMG_IN  uint8*  data,
    HMG_IN  uint32  dataLen
    );

#endif

#ifdef HMG_ENABLE_HMAC_SHA512

/** \brief  HmacSha512 start.
*
* initializes Hmac values.
* \param[inout] HmacSha512Ctx   context of HmacSha512
* \param[in]    key             Hmac key
* \param[in]    keyLen          Hmac key length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see          Hmg_Sha512Start, Hmg_Sha512Update, Hmg_Sha512Finish()
*/
extern boolean Hmg_HmacSha512Start(
    HMG_INOUT   HmgHmacSha512Ctx*   HmacSha512Ctx,
    HMG_IN      uint8*              key,
    HMG_IN      uint32              keyLen
    );


/** \brief  HmacSha512 Update.
*
* updates hash context for a block of data
* \param[inout] HmacSha512Ctx   context of HmacSha512
* \param[in]    data            input data
* \param[in]    dataLen         input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see          Hmg_Sha512Update()
*/
extern boolean Hmg_HmacSha512Update(
    HMG_INOUT   HmgHmacSha512Ctx*   HmacSha512Ctx,
    HMG_IN      uint8*              data,
    HMG_IN      uint32              dataLen
    );

/** \brief  HmacSha512 Finish.
*
* digest the final data and ganerates Hmac value.
* \param[inout] HmacSha512Ctx   context of HmacSha512
* \param[out]   hmacValue       output Hmac value
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see          Hmg_Sha512Start, Hmg_Sha512Update, Hmg_Sha512Finish()
*/
extern boolean Hmg_HmacSha512Finish(
    HMG_INOUT   HmgHmacSha512Ctx*   HmacSha512Ctx,
    HMG_OUT     uint8               hmacValue[]
    );

/** \brief  HmacSha512 calculation.
*
* Calculate Hmac sha1 for the input data
* \param[out]   hmacValue   output Hmac value
* \param[in]    key         Hmac key
* \param[in]    keyLen      Hmac key length
* \param[in]    data        input data
* \param[in]    dataLen     input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see          Hmg_HmacSha512Start, Hmg_HmacSha512Update, Hmg_HmacSha512Finish()
*/
extern boolean Hmg_HmacSha512(
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
