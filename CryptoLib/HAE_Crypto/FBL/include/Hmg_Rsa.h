/*-----------------------------------------------------------------------------
* Hyundai-AutoEver Cryptography Library
* Copyright (c) 2015-2016 Hyundai-AutoEver all rights reserved.
------------------------------------------------------------------------------*/
/**
* \file     Hmg_Rsa.h
* \date     Jan. 2016.
* \version  1.6.0
* \author   Hyundai_Autoever Automotive Security Techology Team
* \brief    RSA 2048bit implementation
* \see
*
*/
/* DEFINE TO PREVENT RECURSIVE INCLUSION -------------------------------------*/
#ifndef HMG_RSA_H_
#define HMG_RSA_H_

/* INCLUDES ------------------------------------------------------------------*/
#include "Hmg_Common.h"

#ifdef  __cplusplus
extern "C" {
#endif
/* EXPORTED DEFINE -----------------------------------------------------------*/

/** \brief rsa algorithm byte length size */
#define HMG_RSA_BYTES_SIZE  (HMG_RSA_BIT_SIZE / 8U)

/** \brief rsa algorithm Dword length size */
#define HMG_RSA_DWORD_SIZE (HMG_RSA_BIT_SIZE / 32U)

/* EXPORTED MACRO  -----------------------------------------------------------*/
/* EXPORTED TYPES  -----------------------------------------------------------*/

/** \brief Rsa privatekey struct  */
    typedef struct{
        uint8 *modulus;     /**< RSA public modulus n = p * q                       */
        uint8 *exponent;    /**< RSA private exponent d = e^(-1) mod (p-1)*(q-1)    */
#ifdef HMG_RSA_USE_CRT
        uint8  *p;          /**< RSA private first prime p (used for CRT)           */
        uint8  *q;          /**< RSA private second prime q (used for CRT)          */
        uint8 *dp;          /**< RSA private d mod (p-1) (used for CRT)             */
        uint8 *dq;          /**< RSA private d mod (q-1) (used for CRT)             */
        uint8 *qinv;        /**< RSA private q^(-1) mod p (used for CRT)            */
        uint8 crt_Flag;     /**< RSA CRT method flag, crt_Flag =1 means use CRT mode)*/
#endif
    } HmgRsaPrivatekey;

    /** \brief Rsa public key struct  */
    typedef struct{
        uint8 *modulus;     /**< RSA public modulus n = p * q                       */
        uint32 exponent;    /**< RSA public exponent e                              */
    } HmgRsaPublickey;

    /* EXPORTED VARIABLES  -------------------------------------------------------*/
    /* EXPORTED FUNCTIONS  -------------------------------------------------------*/
    /* EXPORTED VARIABLES  -------------------------------------------------------*/
    /* EXPORTED FUNCTIONS  -------------------------------------------------------*/

#ifdef HMG_ENABLE_RSA_MODEXP
    /** \brief  calculate modular exponent(public E).
    *
    * calculates modular exponent using public key E(uint32)
    *   calculate, (calculated text EC) = (plain text EM) ^ (public exponent) mod (modular N).
    *   and, keypair->d is not used.
    * \param[out]   pCM  calcuated text
    * \param[in]    pEM  plain text
    * \param[in]    keypair  rsa keypair struct
    * \return       success or failure
    * \see
    */
    extern boolean Hmg_RsaModExponent(
        HMG_OUT uint8 pCM[],
        HMG_IN uint8 pEM[],
        HMG_IN HmgRsaPublickey* Publickey
        );

    /** \brief  calculate modular exponent(private D).
    *
    * calculates modular exponent using private key D
    *   calculate, (calculated text EC) = (plain text EM) ^ (private exponent) mod (modular N).
    *   if n = p*q, use CRT mode for the operation.
    *   and, keypair->e is not used.
    * \param[out]   pCM  calcuated text
    * \param[in]    pEM  plain text
    * \param[in]    keypair  rsa keypair struct
    * \return       success or failure
    * \see
    */
    extern boolean Hmg_RsaModExponentLong(
        HMG_OUT uint8 pCM[],
        HMG_IN uint8 pEM[],
        HMG_IN HmgRsaPrivatekey* Privatekey
        );

#ifdef HMG_RSA_USE_CRT
    extern boolean Hmg_RsaModExponentLongCRT(
        HMG_OUT uint8 pCM[],
        HMG_IN uint8 pEM[],
        HMG_IN HmgRsaPrivatekey* Privatekey
        );
#endif
#endif



    /** \brief Rsa buffer struct for SLICE */
    typedef struct{
        uint32 buff_dst[HMG_RSA_DWORD_SIZE + 1U];
        uint32 buff_src[HMG_RSA_DWORD_SIZE + 1U];
        uint32 buff_mod[HMG_RSA_DWORD_SIZE + 1U];
        uint32 buff_mul[(HMG_RSA_DWORD_SIZE + 1U) * 2U];
        uint32 nprimez;
        uint32 counter;
        uint8  pubExp[4];
        uint8* pExp;
        uint32 emLen;
    } HmgRsaSliceCtx;


#ifdef HMG_ENABLE_SLICE
    extern boolean Hmg_RsaModExponentLongStart(HMG_INOUT HmgRsaSliceCtx* rsaCtx, HMG_IN uint8* pEM, HMG_IN HmgRsaPrivatekey* Privatekey);
    extern boolean Hmg_RsaModExponentLongUpdate(HMG_INOUT HmgRsaSliceCtx* rsaCtx);
    extern boolean Hmg_RsaModExponentLongFinish(HMG_INOUT HmgRsaSliceCtx* rsaCtx, HMG_OUT uint8* pCM);

    extern boolean Hmg_RsaModExponentStart(HMG_INOUT HmgRsaSliceCtx *rsaCtx, HMG_IN uint8* pEM, HMG_IN HmgRsaPublickey* Publickey);
    extern boolean Hmg_RsaModExponentUpdate(HMG_INOUT HmgRsaSliceCtx *rsaCtx);
    extern boolean Hmg_RsaModExponentFinish(HMG_INOUT HmgRsaSliceCtx *rsaCtx, HMG_OUT uint8* pCM);
#endif //HMG_ENABLE_SLICE

#ifdef  __cplusplus
}
#endif

#endif
