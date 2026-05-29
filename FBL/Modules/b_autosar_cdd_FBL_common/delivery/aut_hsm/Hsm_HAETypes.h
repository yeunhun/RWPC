/*******************************************************************************
**                                                                            **
**  (C) 2017 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Hsm_HaeTypes.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Hsm (Hardware Security Module)                                **
**                                                                            **
**  PURPOSE   : Header file for HSM                                           **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     16-Feb-2017   Sinil        Initial version                       **
*******************************************************************************/

#ifndef HSM_HAETYPES_H
#define HSM_HAETYPES_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
**                      Defines                                               **
*******************************************************************************/
#define HAE_SHA160_DIGEST_SIZE			                    (20U)
#define HAE_SHA256_DIGEST_SIZE			                    (32U)

#define HAE_RSA_BYTES_SIZE			                        (256U)

#define HAE_SHA160                                      (0x01U)
#define HAE_SHA224	                                    (0x02U)
#define HAE_SHA256	                                    (0x03U)
#define HAE_SHA384	                                    (0x04U)
#define HAE_SHA512	                                    (0x05U)
#define HAE_SHA512224	                                  (0x06U)
#define HAE_SHA512256	                                  (0x07U)
#define HAE_SHA160_CALCULATED                           (0x11U)
#define HAE_SHA224_CALCULATED                           (0x12U)
#define HAE_SHA256_CALCULATED                           (0x13U)
#define HAE_SHA384_CALCULATED                           (0x14U)
#define HAE_SHA512_CALCULATED                           (0x15U)
#define HAE_SHA512224_CALCULATED                        (0x16U)
#define HAE_SHA512256_CALCULATED                        (0x17U)

#define HAE_ECIES_XOR_ENC                               (1U)
#define HAE_ECIES_AES_CTR                               (2U)
#define HAE_ECIES_AES_CBC                               (3U)

/*******************************************************************************
**                      Structures                                            **
*******************************************************************************/
typedef struct
{
  uint8 modulus[HAE_RSA_BYTES_SIZE];
  uint8 exponent[HAE_RSA_BYTES_SIZE];
} Hsm_RsaPrivateKey;

typedef struct
{
  uint8 modulus[HAE_RSA_BYTES_SIZE];
  uint32 exponent;
} Hsm_RsaPublicKey;

#endif /* HSM_HAETYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
