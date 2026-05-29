/*-----------------------------------------------------------------------------
* Hyundai-AutoEver Cryptography Library
* Copyright (c) 2015-2016 Hyundai-AutoEver all rights reserved.
------------------------------------------------------------------------------*/
/**
* \file     Hmg_Sha512.h
* \date     Jan. 2016.
* \version  1.6.0
* \author   Hyundai_Autoever Automotive Security Techology Team
* \brief    Sha512(Secure Hash Algorithm) implementation
* \see      FIPS PUB 180-4(August, 2015)
*/

/* DEFINE TO PREVENT RECURSIVE INCLUSION -------------------------------------*/
#ifndef HMG_SHA512_H_
#define HMG_SHA512_H_

/* INCLUDES ------------------------------------------------------------------*/

#include "Hmg_Common.h"

#ifdef  __cplusplus
extern "C" {
#endif

/** Length of hash block in byte. */
#define HMG_SHA384_BLOCK_SIZE           128U
#define HMG_SHA512_BLOCK_SIZE           128U

/** Length of digest in byte. */
#define HMG_SHA384_DIGEST_SIZE           48U
#define HMG_SHA512_DIGEST_SIZE           64U


/* EXPORTED MACRO  -----------------------------------------------------------*/

/* EXPORTED TYPES  -----------------------------------------------------------*/

/** \brief Context for Sha512 */
typedef struct ctSha512Ctx
{
    uint64  hash[HMG_SHA512_DIGEST_SIZE / 8U];              /**< Hash values H(n)                               */
    uint64  block[HMG_SHA512_BLOCK_SIZE / 8U];              /**< Current block                                  */
    uint32  blockLen;                                           /**< Number of bytes in block used                  */
    uint64  dataLenLow;                                         /**< Total length of the message in byte            */
    /*uint64    hlen;                               */          /**< Number of bytes in block used                  */
} HmgSha512Ctx;

/** \brief Context for Sha384 */
typedef HmgSha512Ctx HmgSha384Ctx;

/* EXPORTED VARIABLES  -------------------------------------------------------*/
/* EXPORTED FUNCTIONS  -------------------------------------------------------*/


#ifdef HMG_ENABLE_HASH_SHA512
/** \brief  Sha512 start.
*
* initializes sha values.
* \param[inout] Sha512Ctx   context of Sha512
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha512Start(
    HMG_INOUT   HmgSha512Ctx* sha512Ctx
    );

/** \brief  Sha512 Update.
*
* updates hash context for a block of data
* \param[inout] Sha512Ctx       context of Sha512
* \param[in]    data        input data
* \param[in]    dataLen     input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha512Update(
    HMG_INOUT   HmgSha512Ctx* sha512Ctx,
    HMG_IN      uint8*      data,
    HMG_IN      uint32      dataLen
    );


/** \brief  Sha512 Finish.
*
* digest the final data and ganerates hash value.
* \param[inout] Sha512Ctx       context of Sha512
* \param[out]   hmacValue   output hash value
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha512Finish(
    HMG_INOUT   HmgSha512Ctx* sha512Ctx,
    HMG_OUT     uint8       digest[]
    );

/** \brief  Sha512 calculation.
*
* Calculate Sha512 for the input data
* \param[out]   digest      output hash value
* \param[in]    data        input data
* \param[in]    dataLen     input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha512(
    HMG_OUT     uint8       digest[],
    HMG_IN      uint8*      data,
    HMG_IN      uint32      dataLen
    );


#endif
#ifdef HMG_ENABLE_HASH_SHA384

/** \brief  Sha384 start.
*
* initializes sha values.
* \param[inout] Sha384Ctx   context of Sha384
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha384Start(
    HMG_INOUT   HmgSha384Ctx* sha384Ctx
    );

/** \brief  Sha384 Update.
*
* updates hash context for a block of data
* \param[inout] Sha384Ctx       context of Sha384
* \param[in]    data        input data
* \param[in]    dataLen     input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha384Update(
    HMG_INOUT   HmgSha384Ctx* sha384Ctx,
    HMG_IN      uint8*      data,
    HMG_IN      uint32      dataLen
    );

/** \brief  Sha384 Finish.
*
* digest the final data and ganerates hash value.
* \param[inout] Sha384Ctx       context of Sha384
* \param[out]   hmacValue   output hash value
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha384Finish(
    HMG_INOUT   HmgSha384Ctx* sha384Ctx,
    HMG_OUT     uint8       digest[]
    );

/** \brief  Sha384 calculation.
*
* Calculate Sha384 for the input data
* \param[out]   digest      output hash value
* \param[in]    data        input data
* \param[in]    dataLen     input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha384(
    HMG_OUT     uint8       digest[],
    HMG_IN      uint8*      data,
    HMG_IN      uint32      dataLen
    );
#endif
#ifdef HMG_ENABLE_HASH_SHA512_224

/** \brief  Sha512_224 start.
*
* initializes sha values.
* \param[inout] Sha512Ctx   context of Sha512
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha512_224Start(
    HMG_INOUT   HmgSha512Ctx* sha512Ctx
    );

/** \brief  Sha512_224 Update.
*
* updates hash context for a block of data
* \param[inout] Sha512Ctx       context of Sha512
* \param[in]    data        input data
* \param[in]    dataLen     input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha512_224Update(
    HMG_INOUT   HmgSha512Ctx* sha512Ctx,
    HMG_IN      uint8*      data,
    HMG_IN      uint32      dataLen
    );


/** \brief  Sha512_224 Finish.
*
* digest the final data and ganerates hash value.
* \param[inout] Sha512Ctx       context of Sha512
* \param[out]   hmacValue   output hash value
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha512_224Finish(
    HMG_INOUT   HmgSha512Ctx* sha512Ctx,
    HMG_OUT     uint8       digest[]
    );

/** \brief  Sha512_224 calculation.
*
* Calculate Sha512_224 for the input data
* \param[out]   digest      output hash value
* \param[in]    data        input data
* \param[in]    dataLen     input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha512_224(
    HMG_OUT     uint8       digest[],
    HMG_IN      uint8*      data,
    HMG_IN      uint32      dataLen
    );

#endif
#ifdef HMG_ENABLE_HASH_SHA512_256
/** \brief  Sha512_256 start.
*
* initializes sha values.
* \param[inout] Sha512Ctx       context of Sha512
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha512_256Start(
    HMG_INOUT   HmgSha512Ctx* sha512Ctx
    );


/** \brief  Sha512_256 Update.
*
* updates hash context for a block of data
* \param[inout] Sha512Ctx       context of Sha512
* \param[in]    data            input data
* \param[in]    dataLen         input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha512_256Update(
    HMG_INOUT   HmgSha512Ctx* sha512Ctx,
    HMG_IN      uint8*      data,
    HMG_IN      uint32      dataLen
    );


/** \brief  Sha512_256 Finish.
*
* digest the final data and ganerates hash value.
* \param[inout] Sha512Ctx       context of Sha512
* \param[out]   hmacValue       output hash value
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha512_256Finish(
    HMG_INOUT   HmgSha512Ctx* sha512Ctx,
    HMG_OUT     uint8       digest[]
    );

/** \brief  Sha512_256 calculation.
*
* Calculate Sha512_256 for the input data
* \param[out]   digest      output hash value
* \param[in]    data        input data
* \param[in]    dataLen     input data length
* \return       HMG_SUCCESS or HMG_FAILURE.
* \see
*/
extern boolean Hmg_Sha512_256(
    HMG_OUT     uint8       digest[],
    HMG_IN      uint8*      data,
    HMG_IN      uint32      dataLen
    );
#endif
#ifdef  __cplusplus
}
#endif
#endif
