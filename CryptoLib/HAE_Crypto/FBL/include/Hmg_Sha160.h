/*-----------------------------------------------------------------------------
* Hyundai-AutoEver Cryptography Library
* Copyright (c) 2015-2016 Hyundai-AutoEver all rights reserved.
------------------------------------------------------------------------------*/
/**
* \file     Hmg_Sha160.h
* \date     Jan. 2016.
* \version  1.6.0
* \author   Hyundai_Autoever Automotive Security Techology Team
* \brief    sha160(Secure Hash Algorithm) implementation
* \see      FIPS PUB 180-4(August, 2015)
*/

/* DEFINE TO PREVENT RECURSIVE INCLUSION -------------------------------------*/
#ifndef HMG_SHA160_H_
#define HMG_SHA160_H_

/* INCLUDES ------------------------------------------------------------------*/
#include "Hmg_Common.h"

#ifdef  __cplusplus
extern "C" {
#endif

/* EXPORTED DEFINE -----------------------------------------------------------*/

/** Length of hash block in byte. */
#define HMG_SHA160_BLOCK_SIZE       64U
/** Length of digest in byte. */
#define HMG_SHA160_DIGEST_SIZE      20U

/* EXPORTED MACRO  -----------------------------------------------------------*/
/* EXPORTED TYPES  -----------------------------------------------------------*/

/** \brief Context for Sha1 */
typedef struct ctSha160Ctx{
    uint32 hash[HMG_SHA160_DIGEST_SIZE / 4U];           /**< Hash values H(n)                               */
    uint32 block[HMG_SHA160_BLOCK_SIZE / 4U];           /**< Current block                                  */
    uint32 blockLen;                                    /**< Number of bytes in block used                  */
    uint32 dataLenLow;                                  /**< Total length of the message in byte            */
    uint32 dataLenHigh;                                 /**< Total length of the message in byte over 2^32  */
} HmgSha160Ctx;


/* EXPORTED VARIABLES  -------------------------------------------------------*/
/* EXPORTED FUNCTIONS  -------------------------------------------------------*/

#ifdef HMG_ENABLE_HASH_SHA160
/** \brief  Sha160 start.
*
* initializes sha values.
* \param[inout] sha160Ctx   context of Sha160
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha160Start(
    HMG_INOUT   HmgSha160Ctx*   sha160Ctx
    );

/** \brief  Sha1 Update.
*
* updates hash context for a block of data
* \param[inout] sha160Ctx       context of Sha160
* \param[in]    data        input data
* \param[in]    dataLen     input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha160Update(
    HMG_INOUT   HmgSha160Ctx*   sha160Ctx,
    HMG_IN      uint8*      data,
    HMG_IN      uint32      dataLen
    );

/** \brief  Sha1 Finish.
*
* digest the final data and ganerates hash value.
* \param[inout] sha160Ctx       context of Sha160
* \param[out]   hmacValue   output hash value
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha160Finish(
    HMG_INOUT   HmgSha160Ctx*   sha160Ctx,
    HMG_OUT     uint8       digest[]
    );

/** \brief  Sha1 calculation.
*
* Calculate sha1 for the input data
* \param[out]   digest      output hash value
* \param[in]    data        input data
* \param[in]    dataLen     input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha160(
    HMG_OUT     uint8       digest[],
    HMG_IN      uint8*      data,
    HMG_IN      uint32      dataLen
    );

#endif

#ifdef  __cplusplus
}
#endif

#endif
