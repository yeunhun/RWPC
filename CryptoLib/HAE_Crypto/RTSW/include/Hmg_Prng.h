/*-----------------------------------------------------------------------------
* Hyundai-AutoEver Cryptography Library
* Copyright (c) 2015-2016 Hyundai-AutoEver all rights reserved.
------------------------------------------------------------------------------*/
/**
* \file     Hmg_Prng.h
* \date     Oct. 2016.
* \version  1.6.0
* \author   Hyundai Autoever Automotive Security Techology Team
* \brief    PRNG(Pseduo Random Number Generator) implementation
* \see
*/

/* DEFINE TO PREVENT RECURSIVE INCLUSION -------------------------------------*/

#ifndef HMG_PRNG_H_
#define HMG_PRNG_H_

/* INCLUDES ------------------------------------------------------------------*/

#include "Hmg_Common.h"
#include "Hmg_Aes.h"
#include "Hmg_Sha256.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/* EXPORTED DEFINE -----------------------------------------------------------*/

/** \brief Entropy length for Hmg_PrngReseed */
#define HMG_ENTROPY_LEN     16u

/** \brief Maximum length to generate random numbers at once */
#define HMG_RND_MAX_LEN     0x000FFFFFu /* 65536 * 16 = 1048576 */

/** \brief Rand key size in prng context */
#define HMG_RND_KEY_SIZE    32u

/** \brief State size in prng context */
#define HMG_RND_STATE_SIZE  16u

/** \brief Reseed period: user should reseed if reseedCnt reached to the period */
#define HMG_RESEED_PERIOD   100000u


/* EXPORTED MACRO  -----------------------------------------------------------*/

/* EXPORTED TYPES  -----------------------------------------------------------*/

/** \brief Context for Hmg PRNG */
typedef struct ctPrngCtx{
    uint8 state[HMG_RND_STATE_SIZE];
    uint8 rndkey[HMG_RND_KEY_SIZE];
    uint32 reseedCnt;
} HmgPrngCtx;

/* EXPORTED VARIABLES  -------------------------------------------------------*/

/* EXPORTED FUNCTIONS  -------------------------------------------------------*/


#ifdef HMG_ENABLE_PRNG
/** \brief  PRNG initialization
*
* initializes prng context.
* \param[out]   hpc context of PRNG
* \return       void
* \see          Hmg_PrngReseed, Hmg_PrngGetRand
*/
void Hmg_PrngInit(
    HMG_INOUT HmgPrngCtx *hpc
    );

/** \brief  PRNG Reseed
*
* Reseed from user-input entropy(User must set entropy from entropy sources).
* \param[inout] hpc     context of PRNG
* \param[in]    entropy seed input for generating randoms
* \return       void
* \see          Hmg_PrngInit, Hmg_PrngGetRand
*/
void Hmg_PrngReseed(
    HMG_INOUT HmgPrngCtx *hpc,
    HMG_IN uint8 entropy[HMG_ENTROPY_LEN]
    );

/** \brief  Get pseudo random numbers
*
* Generate and return random numbers based on PRNG context values and entropy.
* if return value is HMG_FAILURE, you have to do Hmg_Hashdrbg_Sha256_Reseed.

* \param[inout] hpc     context of HmacSha1
* \param[in]    len     length of random numbers
* \param[out]   rndout  output of random numbers with len
* \return       HMG_SUCCESS/HMG_FAILURE/HMG_INVALID_VALUE/HMG_INVALID_LENGTH.
* \see          Hmg_PrngInint, Hmg_PrngReseed
*/

boolean Hmg_PrngGetRand(
    HMG_INOUT HmgPrngCtx *hpc,
    HMG_OUT uint8   *rndout,
    HMG_IN  uint32  len
    );
#endif

#if defined(__cplusplus)
}
#endif

#endif
