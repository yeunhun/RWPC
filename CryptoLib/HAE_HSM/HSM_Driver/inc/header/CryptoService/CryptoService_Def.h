/*!
  @file CryptoService_Def.h
  @brief Crypto service definitions
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
  @note DO NOT CHANGE THESE DEFINITION VALUES 
*/
#ifndef CRYPTOSERVICE_RSA_PKCS_DEF_H_
#define CRYPTOSERVICE_RSA_PKCS_DEF_H_

/******************************************************************************/
/*                                    AES Define                              */
/******************************************************************************/
#define HSM_AES128_KEY_LEN  (16)                    /*!< AES128 key byte length -- > 128bit */
#define HSM_AES128_CMAC_LEN (16)                    /*!< AES128 CMAC byte length -- > 128bit */

/******************************************************************************/
/*                                    Ecc Define                              */
/******************************************************************************/
/* Size of WORD and BYTE of Ecc curve */
#define ECC_WORDS_SIZE 8U                           /*!< ECC word size */
#define ECC_BYTES_SIZE 32U                          /*!< ECC byte size */

/******************************************************************************/
/*                                    Hash Define                             */
/******************************************************************************/
#define SHA160_DIGEST_SIZE 20U                      /*!< SHA160 digest byte size */
#define SHA256_DIGEST_SIZE 32U                      /*!< SHA256 digest byte size */

/******************************************************************************/
/*                                    RSA Define                              */
/******************************************************************************/
#define HAC_RSA_BIT_SIZE 2048U                      /*!< RSA bit size */
#define HAC_RSA_BYTES_SIZE (HAC_RSA_BIT_SIZE / 8U)  /*!< RSA byte size */

#endif /* CRYPTOSERVICE_RSA_PKCS_DEF_H_ */
