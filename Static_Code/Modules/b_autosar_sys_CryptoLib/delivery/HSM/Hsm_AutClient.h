/*******************************************************************************
**                                                                            **
**  (C) 2017~2018 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Hsm_AutClient.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Hsm (Hardware Security Module)                                **
**                                                                            **
**  PURPOSE   : Header file for HSM                                           **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.1.0     09-Aug-2018   Sinil        Redmine #13647                        **
** 1.0.1     27-Apr-2018   Sinil        Redmine #12516                        **
** 1.0.0     16-Feb-2017   Sinil        Initial version                       **
*******************************************************************************/

#ifndef HSM_AUTCLIENT_H
#define HSM_AUTCLIENT_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Hsm_AutTypes.h"

#if ((CRYPTOLIB_SUPORT_HSM_SPC58X == STD_ON) || (CRYPTOLIB_SUPORT_HSM_ICUM == STD_ON))
/*******************************************************************************
**                      Enumerations                                          **
*******************************************************************************/
typedef enum
{
  HSM_CMD_NO_CMD                            = 0U,

  /* Hash */
  HSM_CMD_SHA160_INIT,                      /* 1 */
  HSM_CMD_SHA160_UPDATE,                    /* 2 */
  HSM_CMD_SHA160_FINISH,                    /* 3 */
  HSM_CMD_SHA256_INIT,                      /* 4 */
  HSM_CMD_SHA256_UPDATE,                    /* 5 */
  HSM_CMD_SHA256_FINISH,                    /* 6 */

  /* Mac */
  HSM_CMD_AES_CMAC_GEN_INIT,                /* 7 */
  HSM_CMD_AES_CMAC_GEN_UPDATE,              /* 8 */
  HSM_CMD_AES_CMAC_GEN_FINISH,              /* 9 */
  HSM_CMD_AES_CMAC_VER_INIT,                /* 10 */
  HSM_CMD_AES_CMAC_VER_UPDATE,              /* 11 */
  HSM_CMD_AES_CMAC_VER_FINISH,              /* 12 */
  HSM_CMD_HMAC_SHA160_GEN_INIT,             /* 13 */
  HSM_CMD_HMAC_SHA160_GEN_UPDATE,           /* 14 */
  HSM_CMD_HMAC_SHA160_GEN_FINISH,           /* 15 */
  HSM_CMD_HMAC_SHA160_VER_INIT,             /* 16 */
  HSM_CMD_HMAC_SHA160_VER_UPDATE,           /* 17 */
  HSM_CMD_HMAC_SHA160_VER_FINISH,           /* 18 */
  HSM_CMD_HMAC_SHA256_GEN_INIT,             /* 19 */
  HSM_CMD_HMAC_SHA256_GEN_UPDATE,           /* 20 */
  HSM_CMD_HMAC_SHA256_GEN_FINISH,           /* 21 */
  HSM_CMD_HMAC_SHA256_VER_INIT,             /* 22 */
  HSM_CMD_HMAC_SHA256_VER_UPDATE,           /* 23 */
  HSM_CMD_HMAC_SHA256_VER_FINISH,           /* 24 */

  /* Random */
  HSM_CMD_TRNG_GEN,                         /* 25 */
  HSM_CMD_PRNG_GEN,                         /* 26 */

  /* Symmetric */
  HSM_CMD_AES_ENC_INIT,                     /* 27 */
  HSM_CMD_AES_ENC_UPDATE,                   /* 28 */
  HSM_CMD_AES_ENC_FINISH,                   /* 29 */
  HSM_CMD_AES_DEC_INIT,                     /* 30 */
  HSM_CMD_AES_DEC_UPDATE,                   /* 31 */
  HSM_CMD_AES_DEC_FINISH,                   /* 32 */

  /* Asymmetric */
  HSM_CMD_RSA_ENC_INIT,                     /* 33 */
  HSM_CMD_RSA_ENC_UPDATE,                   /* 34 */
  HSM_CMD_RSA_ENC_FINISH,                   /* 35 */
  HSM_CMD_RSA_DEC_INIT,                     /* 36 */
  HSM_CMD_RSA_DEC_UPDATE,                   /* 37 */
  HSM_CMD_RSA_DEC_FINISH,                   /* 38 */
  HSM_CMD_ECIES_ENC_INIT,                   /* 39 */
  HSM_CMD_ECIES_ENC_UPDATE,                 /* 40 */
  HSM_CMD_ECIES_ENC_FINISH,                 /* 41 */
  HSM_CMD_ECIES_DEC_INIT,                   /* 42 */
  HSM_CMD_ECIES_DEC_UPDATE,                 /* 43 */
  HSM_CMD_ECIES_DEC_FINISH,                 /* 44 */

  /* Signature */
  HSM_CMD_PKCS1_V15_GEN_INIT,               /* 45 */
  HSM_CMD_PKCS1_V15_GEN_UPDATE,             /* 46 */
  HSM_CMD_PKCS1_V15_GEN_FINISH,             /* 47 */
  HSM_CMD_PKCS1_V15_VER_INIT,               /* 48 */
  HSM_CMD_PKCS1_V15_VER_UPDATE,             /* 49 */
  HSM_CMD_PKCS1_V15_VER_FINISH,             /* 50 */
  HSM_CMD_PKCS1_PSS_GEN_INIT,               /* 51 */
  HSM_CMD_PKCS1_PSS_GEN_UPDATE,             /* 52 */
  HSM_CMD_PKCS1_PSS_GEN_FINISH,             /* 53 */
  HSM_CMD_PKCS1_PSS_VER_INIT,               /* 54 */
  HSM_CMD_PKCS1_PSS_VER_UPDATE,             /* 55 */
  HSM_CMD_PKCS1_PSS_VER_FINISH,             /* 56 */
  HSM_CMD_ECDSA_GEN_INIT,                   /* 57 */
  HSM_CMD_ECDSA_GEN_UPDATE,                 /* 58 */
  HSM_CMD_ECDSA_GEN_FINISH,                 /* 59 */
  HSM_CMD_ECDSA_VER_INIT,                   /* 60 */
  HSM_CMD_ECDSA_VER_UPDATE,                 /* 61 */
  HSM_CMD_ECDSA_VER_FINISH,                 /* 62 */

  /* Key Derivation */
  HSM_CMD_PBKDF2_INIT,                      /* 63 */
  HSM_CMD_PBKDF2_UPDATE,                    /* 64 */
  HSM_CMD_PBKDF2_FINISH,                    /* 65 */

  /* Key Exchange */
  HSM_CMD_ECDH_INIT,                        /* 66 */
  HSM_CMD_ECDH_UPDATE,                      /* 67 */
  HSM_CMD_ECDH_FINISH,                      /* 68 */

  /* Secure Data */
  HSM_CMD_LOAD_DATA,                        /* 69 */
  HSM_CMD_LOAD_RAM_KEY,                     /* 70 */
  HSM_CMD_CHECK_SECURE_DATA,                /* 71 */

  /* Secure Boot */
  HSM_CMD_ENABLE_SECURE_BOOT,               /* 72 */
  HSM_CMD_GET_SECURE_BOOT_STATUS,           /* 73 */

  /* Secure Debug */
  HSM_CMD_ENABLE_SECURE_DEBUG,              /* 74 */
  HSM_CMD_CONTROL_DEBUG,                    /* 75 */
  HSM_CMD_DEBUG_STATUS,                     /* 76 */

  HSM_CMD_SHARED_MEM,                       /* 77 */

  HSM_CMD_CONTROL_PIT,                      /* 78 */
  HSM_CMD_CONTROL_FLASH,                    /* 79 */

  #if (CRYPTOLIB_SUPPORT_HSM_SPC58X_IAU == STD_ON)
  HSM_CMD_CUSTOM_IAU_EXPORT_DATA,
  HSM_CMD_CUSTOM_IAU_PINNING_CHECK,
  HSM_CMD_CUSTOM_IAU_GEN_SEED_SC,
  HSM_CMD_CUSTOM_IAU_KDF,
  #endif

  HSM_CMD_MAX
} Hsm_CmdType;

typedef enum
{
  HSM_CAT_SYSTEM                            = 0,
  HSM_CAT_HASH                              = 1,   
  HSM_CAT_MAC_GEN                           = 2,
  HSM_CAT_MAC_VER                           = 3,
  HSM_CAT_RANDOM                            = 4,
  HSM_CAT_SYM_ENC                           = 5,
  HSM_CAT_SYM_DEC                           = 6,
  HSM_CAT_ASYM_ENC                          = 7,
  HSM_CAT_ASYM_DEC                          = 8,
  HSM_CAT_SIG_GEN                           = 9,
  HSM_CAT_SIG_VER                           = 10,
  HSM_CAT_KEY_DERIVE                        = 11,
  HSM_CAT_KEY_CALC                          = 12,
  HSM_CAT_CUSTOM1                           = 13,
  HSM_CAT_CUSTOM2                           = 14,
  HSM_CAT_MAX                               = 15,
} Hsm_CmdCategoryType;

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
extern Hsm_ErrType Hsm_SendCmd(Hsm_CmdType ddCmd, boolean blAsync,
  Hsm_CallbackPtr pCallback, uint32 P1, uint32 P2, uint32 P3, uint32 P4,
  uint32 P5, uint32 P6, Hsm_CmdCategoryType ddCat);

extern Hsm_ErrType Hsm_Ready(void);

#endif /* ((CRYPTOLIB_SUPORT_HSM_SPC58X == STD_ON) || (CRYPTOLIB_SUPORT_HSM_ICUM == STD_ON)) */

#endif /* HSM_AUTCLIENT_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
