/*-----------------------------------------------------------------------------
* Hyundai-AutoEver Cryptography Library
* Copyright (c) 2015-2016 Hyundai-AutoEver all rights reserved.
------------------------------------------------------------------------------*/
/**
* \file     Hmg_Sha256.h
* \date     Jan. 2016.
* \version  1.6.0
* \author   Hyundai_Autoever Automotive Security Techology Team
* \brief    Sha256(Secure Hash Algorithm) implementation
* \see      FIPS PUB 180-4(August, 2015)
*/


/* DEFINE TO PREVENT RECURSIVE INCLUSION -------------------------------------*/
#ifndef HMG_SHA256_H_
#define HMG_SHA256_H_

/* INCLUDES ------------------------------------------------------------------*/

#include "Hmg_Common.h"

#ifdef  __cplusplus
extern "C" {
#endif

/* EXPORTED DEFINE -----------------------------------------------------------*/

/** Length of hash block in byte. */
#define HMG_SHA224_BLOCK_SIZE           64U
#define HMG_SHA256_BLOCK_SIZE           64U

/** Length of digest in byte. */
#define HMG_SHA224_DIGEST_SIZE          28U
#define HMG_SHA256_DIGEST_SIZE          32U

/* EXPORTED MACRO  -----------------------------------------------------------*/
/* EXPORTED TYPES  -----------------------------------------------------------*/

/** \brief Context for Sha256 */
typedef struct ctSha256Ctx{
    uint32  hash[HMG_SHA256_DIGEST_SIZE / 4U];          /**< Hash values H(n)                               */
    uint32  block[HMG_SHA256_BLOCK_SIZE / 4U];          /**< Current block                                  */
    uint32  blockLen;                                   /**< Number of bytes in block used                  */
    uint32  dataLenLow;                                 /**< Total length of the message in byte            */
    uint32  dataLenHigh;                                /**< Total length of the message in byte over 2^32  */
} HmgSha256Ctx;

/** \brief Context for Sha224 */
typedef HmgSha256Ctx HmgSha224Ctx;

/* EXPORTED VARIABLES  -------------------------------------------------------*/
/* EXPORTED FUNCTIONS  -------------------------------------------------------*/


#ifdef HMG_ENABLE_HASH_SHA256
/** \brief  Sha256 start.
*
* initializes sha values.
* \param[inout] sha256Ctx   context of Sha256
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha256Start(
    HMG_INOUT   HmgSha256Ctx* sha256Ctx
    );

/** \brief  Sha256 Update.
*
* updates hash context for a block of data
* \param[inout] sha256Ctx   context of Sha256
* \param[in]    data        input data
* \param[in]    dataLen     input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha256Update(
    HMG_INOUT   HmgSha256Ctx* sha256Ctx,
    HMG_IN      uint8*      data,
    HMG_IN      uint32      dataLen
    );

/** \brief  Sha256 Finish.
*
* digest the final data and ganerates hash value.
* \param[inout] sha256Ctx   context of Sha256
* \param[out]   hmacValue   output hash value
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha256Finish(
    HMG_INOUT   HmgSha256Ctx* sha256Ctx,
    HMG_OUT     uint8       digest[]
    );

/** \brief  Sha256 calculation.
*
* Calculate sha1 for the input data
* \param[out]   digest      output hash value
* \param[in]    data        input data
* \param[in]    dataLen     input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha256(
    HMG_OUT     uint8       digest[],
    HMG_IN      uint8*      data,
    HMG_IN      uint32      dataLen
    );

#endif
#ifdef HMG_ENABLE_HASH_SHA224

/** \brief  Sha224 start.
*
* initializes sha values.
* \param[inout] sha224Ctx   context of Sha224
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha224Start(
    HMG_INOUT   HmgSha224Ctx*   sha224Ctx
    );

/** \brief  Sha224 Update.
*
* updates hash context for a block of data
* \param[inout] sha224Ctx   context of Sha224
* \param[in]    data        input data
* \param[in]    dataLen     input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha224Update(
    HMG_INOUT   HmgSha224Ctx* sha224Ctx,
    HMG_IN      uint8*      data,
    HMG_IN      uint32      dataLen
    );

/** \brief  Sha224 Finish.
*
* digest the final data and ganerates hash value.
* \param[inout] sha224Ctx   context of Sha224
* \param[out]   hmacValue   output hash value
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha224Finish(
    HMG_INOUT   HmgSha224Ctx* sha224Ctx,
    HMG_OUT     uint8       digest[]
    );

/** \brief  Sha224 calculation.
*
* Calculate sha1 for the input data
* \param[out]   digest      output hash value
* \param[in]    data        input data
* \param[in]    dataLen     input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha224(
    HMG_OUT     uint8       digest[],
    HMG_IN      uint8*      data,
    HMG_IN      uint32      dataLen
    );
#endif

#ifdef  __cplusplus
}
#endif

#endif
