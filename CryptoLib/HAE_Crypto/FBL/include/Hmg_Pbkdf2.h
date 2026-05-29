/*-----------------------------------------------------------------------------
* Hyundai-AutoEver Cryptography Library
* Copyright (c) 2015-2016 Hyundai-AutoEver all rights reserved.
------------------------------------------------------------------------------*/
/**
* \file     Hmg_Pbkdf2.h
* \date     Jan. 2016.
* \version  1.6.0
* \author   Hyundai_Autoever Automotive Security Techology Team
* \brief    Password based Key derivation function implementation
* \see
*
*/
#ifndef HMG_PBKDF_H_
#define HMG_PBKDF_H_

#include "Hmg_Common.h"

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef HMG_ENABLE_PBKDF2
//PKCS #5 PBKDF2 function

/**
* @brief PBKDF2 (Password Based Key Derivation Function 2)
*
* PBKDF2 applies a pseudorandom function to derive keys.
* The length of the derived key is essentially unbounded.
*
* @param[out] dk Derived key
* @param[in] dkLen Intended length in octets of the derived key
* @param[in] password, an octet string
* @param[in] pLen Length in octets of password
* @param[in] salt, an octet string
* @param[in] sLen Length in octets of salt
* @param[in] c Iteration count
*
* @return boolean
*/
extern boolean Hmg_PBKDF2(
    HMG_OUT uint8 *derivedkey,
    HMG_IN uint32 dkLen,
    HMG_IN uint8 *password,
    HMG_IN uint32 pLen,
    HMG_IN uint8 *salt,
    HMG_IN uint32 sLen,
    HMG_IN uint32 icount
    );
#endif //HMG_ENABLE_PBKDF2

#endif //HMG_PBKDF_H_
