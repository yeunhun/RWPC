/*******************************************************************************
**                                                                            **
**  (C) 2017~2018 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Hsm_AutTypes.h                                                **
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
** 1.2.0     09-Aug-2018   Sinil        Redmine #13647                        **
** 1.1.2     17-Apr-2018   Sinil        Redmine #12345, #12347                **
** 1.1.1     19-Mar-2018   Sinil        Redmine #11932, #11989                **
** 1.1.0     27-Oct-2017   Sinil        Redmine #10376                        **
** 1.0.0     16-Feb-2017   Sinil        Initial version                       **
*******************************************************************************/

#ifndef HSM_AUTTYPES_H
#define HSM_AUTTYPES_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CryptoLib_Cfg.h"
#include "Std_Types.h"

#if ((CRYPTOLIB_SUPORT_HSM_SPC58X == STD_ON) || (CRYPTOLIB_SUPORT_HSM_ICUM == STD_ON))
/*******************************************************************************
**                      Defines                                               **
*******************************************************************************/
#ifndef CRYPTOLIB_SUPPORT_HSM_SPC58X_IAU
#define CRYPTOLIB_SUPPORT_HSM_SPC58X_IAU                (STD_OFF)
#endif

#if (CRYPTOLIB_SUPPORT_HSM_SPC58X_IAU == STD_ON)
#define HSM_DATA_CUSTOM_IAU_KEY                         (100U)
#endif

/*******************************************************************************
**                      Enumerations                                          **
*******************************************************************************/
typedef enum
{
  HSM_DATA_INVALID_KEY                      = 0x00U,
  HSM_DATA_AES_KEY                          = 0x01U,
  HSM_DATA_RSA_PUBLIC_KEY                   = 0x02U,
  HSM_DATA_RSA_PRIVATE_KEY                  = 0x03U,
  HSM_DATA_ECC_PUBLIC_KEY                   = 0x04U,
  HSM_DATA_ECC_PRIVATE_KEY                  = 0x05U,
  HSM_DATA_AES_RAM_KEY                      = 0x11U,
  HSM_DATA_RSA_RAM_PUBLIC_KEY               = 0x12U,
  HSM_DATA_RSA_RAM_PRIVATE_KEY              = 0x13U,
  HSM_DATA_ECC_RAM_PUBLIC_KEY               = 0x14U,
  HSM_DATA_ECC_RAM_PRIVATE_KEY              = 0x15U,
  #if (CRYPTOLIB_SUPPORT_HSM_SPC58X_IAU == STD_ON)
  HSM_DATA_CUSTOM_IAU_PUBLIC_KEY            = 0x21U,
  HSM_DATA_CUSTOM_IAU_PRIVATE_KEY           = 0x22U,
  HSM_DATA_CUSTOM_IAU_CERT                  = 0x23U,
  HSM_DATA_CUSTOM_IAU_UID                   = 0x24U,
  HSM_DATA_CUSTOM_IAU_DEFAULT_ISK           = 0x25U,
  #endif
} Hsm_DataType;

typedef enum
{
  HSM_NO_ERROR                              = 0x00U,
  HSM_BUSY                                  = 0x01U,
  HSM_NO_INITIALIZED_ERROR                  = 0x02U,
  HSM_RNG_NO_INITIALIZED_ERROR              = 0x03U,
  HSM_SHARED_MEM_ERROR                      = 0x04U,
  HSM_INVALID_COMMAND                       = 0x05U,
  HSM_PARAMETER_ERROR                       = 0x06U,
  HSM_CRYPTO_EXEC_ERROR                     = 0x07U,
  HSM_RNG_RESEED_ERROR                      = 0x08U,
  HSM_TIMEOUT_ERROR                         = 0x09U,
  HSM_MEMORY_FAILURE                        = 0x0AU,
  HSM_FLASH_ERROR                           = 0x0BU,
  HSM_KEY_INVALID_ERROR                     = 0x0CU,
  HSM_KEY_EMPTY_ERROR                       = 0x0DU,
  HSM_SECURE_BOOT_FAILED                    = 0x0EU,
  HSM_NO_DEBUGGING                          = 0x0FU,
  HSM_WRONG_SEQUENCE                        = 0x10U,
} Hsm_ErrType;

/* Secure Boot Status */
typedef enum
{
  HSM_SECURE_BOOT_NOT_TESTED                = 0x00U,
  HSM_SECURE_BOOT_COMPARE_SUCCESS           = 0x01U,
  HSM_SECURE_BOOT_COMPARE_FAILED            = 0x02U,
  HSM_SECURE_BOOT_NO_BOOT_MAC_KEY_FAILED    = 0x03U,
  HSM_SECURE_BOOT_KEY_LOAD_FAILED           = 0x04U,
  HSM_SECURE_BOOT_MAC_LOAD_FAILED           = 0x05U,
  HSM_SECURE_BOOT_MAC_COMPUTE_FAILED        = 0x06U,
} HSM_SecureBootStatusType;

typedef uint32 Hsm_DataIDType;
typedef void (*Hsm_CallbackPtr)(Hsm_ErrType ddRet);

#endif /* ((CRYPTOLIB_SUPORT_HSM_SPC58X == STD_ON) || (CRYPTOLIB_SUPORT_HSM_ICUM == STD_ON)) */

/*******************************************************************************
**                                  Defines                                   **
*******************************************************************************/
#define HSM_FALSE                                       (0)
#define HSM_TRUE                                        (1)

#define HSM_NULL                                        (0)
#define HSM_NULL_PTR                                    ((void *)0)

#define HSM_ZERO                                        (0x00U)
#define HSM_ONE                                         (0x01U)
#define HSM_TWO                                         (0x02U)
#define HSM_THREE                                       (0x03U)
#define HSM_FOUR                                        (0x04U)
#define HSM_FIVE                                        (0x05U)
#define HSM_SIX                                         (0x06U)
#define HSM_EIGHT                                       (0x08U)
#define HSM_ONE_SIX                                     (0x10U)
#define HSM_THREE_TWO                                   (0x20U)

#endif /* HSM_AUTTYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
