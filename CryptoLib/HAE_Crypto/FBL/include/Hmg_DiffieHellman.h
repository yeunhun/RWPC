/*-----------------------------------------------------------------------------
* Hyundai-AutoEver Cryptography Library
* Copyright (c) 2015-2016 Hyundai-AutoEver all rights reserved.
------------------------------------------------------------------------------*/
/**
* \file     Hmg_DiffieHellman.h
* \date     Dec. 2016.
* \version  1.6.0
* \author   Hyundai_Autoever Automotive Security Techology Team
* \brief:   PKCS #3 (Diffie-Hellman Key sharing)

* \see
*
*/

/* DEFINE TO PREVENT RECURSIVE INCLUSION -------------------------------------*/
#ifndef HMG_DIFFIE_HELLMAN_H_
#define HMG_DIFFIE_HELLMAN_H_

/* INCLUDES ------------------------------------------------------------------*/
#include "Hmg_Prng.h"
#include "Hmg_Rsa.h"

/* EXPORTED DEFINE -----------------------------------------------------------*/
#ifdef  __cplusplus
extern "C" {
#endif

#define HMG_DH_BYTES_SIZE HMG_RSA_BYTES_SIZE

    /* EXPORTED MACRO  -----------------------------------------------------------*/
    /* EXPORTED TYPES  -----------------------------------------------------------*/
    /* EXPORTED VARIABLES  -------------------------------------------------------*/
    /* EXPORTED FUNCTIONS  -------------------------------------------------------*/

#ifdef HMG_ENABLE_DH
    /** \brief  Diffie-Hellman Key generator.
    *
    * calculates modular exponent using prime P and base G
    *   calculate, (public Value) = (base G) ^ (private Value exponent) mod (modular primeP).
    *       if prngCtx is NULL, this fuction use input privateValue.
    *       if baseG is NULL, this fuction use default baseG.
    *       if primeP is NULL, this fuction use default prime P.
    *       before call this fuction, prngCtx must be prepered by Hmg_PrngInit and Hmg_PrngReseed for random private value(key)
    *
    * \param[inout] prngCtx         prng random value context
    * \param[out]   publicValue     diffie-hellman public value(key)
    * \param[out]   privateValue    diffie-hellman private value(key)
    * \param[in]    baseG           diffie-hellman base G
    * \param[in]    primeP          diffie-hellman modular prime
    * \return       success or failure
    * \see
    */
    extern boolean Hmg_DiffieHellmanKeypairGen(
        HMG_INOUT  HmgPrngCtx* prngCtx,
        HMG_OUT uint8 publicValue[],
        HMG_INOUT uint8 privateValue[],
        HMG_IN  uint8 baseG[],
        HMG_IN  uint8 primeP[]
        );

    /** \brief  Diffie-Hellman secret value generator.
    *
    * calculates modular exponent using prime P and other's public value(key)
    *   calculate, (secret value) = (other's public value) ^ (my private Value exponent) mod (modular primeP).
    *       if prime P is NULL, this fuction use default prime P.
    *
    * \param[out]   secretValue     diffie-hellman secret(result) value
    * \param[in]    publicValue     diffie-hellman other's public value(key)
    * \param[in]    privateValue    diffie-hellman my private value(key)
    * \param[in]    primeP          diffie-hellman modular prime
    * \return       success or failure
    * \see
    */
    extern boolean Hmg_DiffieHellmanSharedvalueGen(
        HMG_OUT uint8 secretValue[],
        HMG_IN  uint8 publicValue[],
        HMG_IN  uint8 privateValue[],
        HMG_IN  uint8 primeP[]
        );

#endif

#ifdef  __cplusplus
}
#endif

#endif //HMG_DIFFIE_HELLMAN_H_
