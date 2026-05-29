/*!
  @file Hsm_KeyTypes.h
  @brief HSM key type header file
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef HSM_KEY_TYPES_H_
#define HSM_KEY_TYPES_H_

#include "Hsm_Types.h"

#define AES_BYTE_SIZE   16
#define RSA_BYTE_SIZE   256
#define ECC_BYTE_SIZE   32

typedef struct Rsa_Keypair_t_
{
    UINT8 mod[RSA_BYTE_SIZE];                   /*!< RSA Modulus value to be stored in UDK area */
    UINT8 priExp[RSA_BYTE_SIZE];                /*!< RSA Exponent value to be stored in UDK area */
} Rsa_Keypair_t;

typedef struct Ecc_Keypair_t_
{
    UINT8 prikey[ECC_BYTE_SIZE];                /*!< ECC private key to store in UDK area */
    UINT8 pubkeyX[ECC_BYTE_SIZE];               /*!< ECC public key X to store in UDK area */
    UINT8 pubkeyY[ECC_BYTE_SIZE];               /*!< ECC public key Y to store in UDK area */
} Ecc_Keypair_t;

typedef enum
{
    AES_KEY = 0u,
    RSA_KEY,
    ECC_KEY
} KEY_TYPE;

#endif /* HSM_KEY_TYPES_H_ */
