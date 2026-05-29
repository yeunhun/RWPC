/*-----------------------------------------------------------------------------
* Hyundai-AutoEver Cryptography Library
* Copyright (c) 2015-2016 Hyundai-AutoEver all rights reserved.
------------------------------------------------------------------------------*/
/**
* \file     Hmg_HDrbg.h
* \date     April. 2017.
* \version  1.6.0
* \author   Hyundai_Autoever Automotive Security Techology Team
* \brief    Hash Drbg implementation
* \see
*
*/
#ifndef HMG_HDRBG_H_
#define HMG_HDRBG_H_

#include "Hmg_Common.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define HMG_HDRBG_RESEED_INTERVAL   65535U // 65535(2^16-1) or 0
#define HMG_HDRBG_INPUT_LEN         55U // entropy: 440 bits, nonce: 440 bits
#define HMG_HDRBG_WORKING_STATE_LEN 55U //440 bits, 55 bytes
#define HMG_HDRBG_BYTES_OF_V        55U
#define HMG_HDRBG_BYTES_OF_C        55U

/* Hash_DRBG with SHA256 context */
typedef struct
{
    uint8 V[HMG_HDRBG_BYTES_OF_V];
    uint8 C[HMG_HDRBG_BYTES_OF_C];
    uint32 reseed_counter;
    boolean PredictionResistance;
} HmgHdrbgSha256Ctx;



#ifdef HMG_ENABLE_HDRBG
/**
* @brief Hmg_Hashdrbg_Sha256_Init
*
* Initialization ctx, using entropy, nonce, and persn(personalisation string)
* Creation: the initial values for V, C, and reseed_counter
*
* @param[inout] ctx struct of working_state
* @param[in] entropy Entropy
* @param[in] nentropy length of Entropy
* @param[in] nonce
* @param[in] nnonce length of nonce
* @param[in] persn Personalized string
* @param[in] npersn length of Personalized string
*/
boolean Hmg_Hashdrbg_Sha256_Init(
    HMG_INOUT HmgHdrbgSha256Ctx *ctx,
    HMG_IN uint8 *entropy,  HMG_IN uint32 nentropy,
    HMG_IN uint8 *nonce,    HMG_IN uint32 nnonce,
    HMG_IN uint8 *persn,    HMG_IN uint32 npersn,
    HMG_IN boolean PredictionResistance
    );


/**
* @brief Hmg_Hashdrbg_Sha256_gen_additional
*
* Output(Random Bits) Generation function with additional input
* Generation: pseudo-random output into 'out'
* if return value is HMG_FAILURE, you have to do Hmg_Hashdrbg_Sha256_Reseed.
*
* @param[inout] ctx struct of working_state
* @param[out] buffer of result(Random Bits)
* @param[in] nout length of result
* @param[in] entropy Entropy
* @param[in] nentropy length of Entropy
* @param[in] addnl additional_input
* @param[in] naddnl length of additional_input
*/
boolean Hmg_Hashdrbg_Sha256_Gen(
    HMG_INOUT HmgHdrbgSha256Ctx *ctx,
    HMG_OUT uint8 *out,     HMG_IN uint32 nout,
    HMG_IN uint8 *entropy,  HMG_IN uint32 nentropy,
    HMG_IN uint8 *addnl,    HMG_IN uint32 naddnl
    );

/**
* @brief Hmg_Hashdrbg_Sha256_Reseed
*
* Reseed function
* Creation: the new values for V, C, and reseed_counter
*
* @param[inout] ctx struct of working_state
* @param[in] entropy Entropy
* @param[in] nentropy length of Entropy
* @param[in] addnl additional_input
* @param[in] naddnl length of additional_input
*/
void Hmg_Hashdrbg_Sha256_Reseed(
    HMG_INOUT HmgHdrbgSha256Ctx *ctx,
    HMG_IN uint8 *entropy,  HMG_IN uint32 nentropy,
    HMG_IN uint8 *addnl,    HMG_IN uint32 naddnl
    );
#endif

#ifdef  __cplusplus
}
#endif

#endif
