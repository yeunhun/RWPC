/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CSEc_Driver.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Hsm (Hardware Security Module)                                **
**                                                                            **
**  PURPOSE   : Header file for S32K CSEc                                     **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     13-May-2019   Sinil        Initial version                       **
*******************************************************************************/

/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:2.5 [Not a defect:Low] "Can be used as per configuration" */
/* polyspace-begin MISRA2012:D4.8 [Not a defect:Low] "False detection" */
/* polyspace-begin MISRA2012:D4.5 [Not a defect:Low] "No Impact of this rule violation" */

#ifndef CSEC_DRIVER_H
#define CSEC_DRIVER_H
/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Std_Types.h"
#include "CryptoLib_Cfg.h"

#if (CRYPTOLIB_SUPORT_HSM_CSEC == STD_ON)
#define CSEC_NO_FLASH_KEYS                              (0U)
#define CSEC_5_FLASH_KEYS                               (1U)
#define CSEC_10_FLASH_KEYS                              (2U)
#define CSEC_20_FLASH_KEYS                              (3U)

#define CSEC_FLASH_KEY_VERIFY_ONLY_DISABLED             (0U)
#define CSEC_FLASH_KEY_VERIFY_ONLY_ENABLED              (1U)

#define CSEC_FLEXRAM_LOADED_EEPROM_DATA                 (0U)
#define CSEC_FLEXRAM_NOT_LOADED                         (1U)

#define CSEC_EEPROM_DATA_SET_SIZE_0B                    (0U)
#define CSEC_EEPROM_DATA_SET_SIZE_2KB                   (1U)
#define CSEC_EEPROM_DATA_SET_SIZE_4KB                   (2U)

#define CSEC_EEPROM_BACKUP_SIZE_0B                      (0U)
#define CSEC_EEPROM_BACKUP_SIZE_24KB                    (1U)
#define CSEC_EEPROM_BACKUP_SIZE_32KB                    (2U)
#define CSEC_EEPROM_BACKUP_SIZE_48KB                    (3U)
#define CSEC_EEPROM_BACKUP_SIZE_64KB                    (4U)

#define CSEC_SECURE_BOOT_NONE                           (0U)
#define CSEC_SECURE_BOOT_SERIAL                         (1U)
#define CSEC_SECURE_BOOT_PARALLEL                       (2U)
#define CSEC_SECURE_BOOT_STRICT                         (3U)

/* Temporary */
#define CSEC_MODULE_ID                                  ((uint16)255)

/* AUTOSAR module instance identification */
#define CSEC_INSTANCE_ID                                ((uint8)0U)

/*******************************************************************************
**                                Defines                                     **
*******************************************************************************/
#define CSEC_BLOCK_BYTE_LENGTH                          (16U)
#define CSEC_BLOCK_BIT_LENGTH                           (128U)

#define CSEC_FALSE                                      ((boolean)0)
#define CSEC_TRUE                                       ((boolean)1)

#define CSEC_ZERO                                       (0U)
#define CSEC_ONE                                        (1U)
#define CSEC_TWO                                        (2U)
#define CSEC_THREE                                      (3U)
#define CSEC_FOUR                                       (4U)
#define CSEC_SIX                                        (6U)
#define CSEC_SEVEN                                      (7U)
#define CSEC_EIGHT                                      (8U)
#define CSEC_ONE_SIX                                    (16U)
#define CSEC_TWO_FOUR                                   (24U)

#define CSEC_MAX_ERROR_COUNT                            (5U)

/**
* @brief          Development error codes (passed to DET).
*/
#if (CRYPTOLIB_ENABLE_DEV_INFO == STD_ON)
/**
* @brief   Csec_Init shall report this error is the hardware is not initialized.
* */
#define CSEC_E_HW_UNINIT                                ((uint8)0x00U)

/**
* @brief   Error reported if the pointer parameter is invalid (NULL_PTR)
* */
#define CSEC_E_PARAM_POINTER                            ((uint8)0x01U)

/**
* @brief   Invalid length of data. For encryption/decryption functions,
*          length should be smaller than 1048560 bytes and divisible with 16.
* */
#define CSEC_E_PARAM_LENGTH                             ((uint8)0x02U)
#endif

/**
* @brief API service ID for Csec_Init function
* @details Parameter used for DET when raising an error from the Csec_Init() function
* */
#define CSEC_INIT_ID                                    ((uint8)0x00U)
/**
* @brief API service ID for Csec_EncEcb function
* @details Parameter used for DET when raising an error from the Csec_EncEcb() function
* */
#define CSEC_ENCECB_ID                                  ((uint8)0x01U)
/**
* @brief API service ID for Csec_DecEcb function
* @details Parameter used for DET when raising an error from the Csec_DecEcb() function
* */
#define CSEC_DECECB_ID                                  ((uint8)0x02U)
/**
* @brief API service ID for Csec_EncCbc function
* @details Parameter used for DET when raising an error from the Csec_EncCbc() function
* */
#define CSEC_ENCCBC_ID                                  ((uint8)0x03U)
/**
* @brief API service ID for Csec_DecCbc function
* @details Parameter used for DET when raising an error from the Csec_DecCbc() function
* */
#define CSEC_DECCBC_ID                                  ((uint8)0x04U)
/**
* @brief API service ID for Csec_GenerateMac function
* @details Parameter used for DET when raising an error from the Csec_GenerateMac() function
* */
#define CSEC_GENERATEMAC_ID                             ((uint8)0x05U)
/**
* @brief API service ID for Csec_VerifyMac function
* @details Parameter used for DET when raising an error from the Csec_VerifyMac() function
* */
#define CSEC_VERIFYMAC_ID                               ((uint8)0x06U)
/**
* @brief API service ID for Csec_LoadKey function
* @details Parameter used for DET when raising an error from the Csec_LoadKey() function
* */
#define CSEC_LOADKEY_ID                                 ((uint8)0x09U)
/**
* @brief API service ID for Csec_LoadPlainKey function
* @details Parameter used for DET when raising an error from the Csec_LoadPlainKey() function
* */
#define CSEC_LOADPLAINKEY_ID                            ((uint8)0x0AU)
/**
* @brief API service ID for Csec_ExportRamKey function
* @details Parameter used for DET when raising an error from the Csec_ExportRamKey() function
* */
#define CSEC_EXPORTRAMKEY_ID                            ((uint8)0x0BU)
/**
* @brief API service ID for Csec_ExtendSeed function
* @details Parameter used for DET when raising an error from the Csec_ExtendSeed() function
* */
#define CSEC_EXTENDSEED_ID                              ((uint8)0x0DU)
/**
* @brief API service ID for Csec_Rnd function
* @details Parameter used for DET when raising an error from the Csec_Rnd() function
* */
#define CSEC_RND_ID                                     ((uint8)0x0EU)
/**
* @brief API service ID for Csec_GetUID function
* @details Parameter used for DET when raising an error from the Csec_GetUID() function
* */
#define CSEC_GETUID_ID                                  ((uint8)0x13U)
/**
* @brief API service ID for Csec_DbgChal function
* @details Parameter used for DET when raising an error from the Csec_DbgChal() function
* */
#define CSEC_DBGCHAL_ID                                 ((uint8)0x14U)
/**
* @brief API service ID for Csec_DbgAuth function
* @details Parameter used for DET when raising an error from the Csec_DbgAuth() function
* */
#define CSEC_DBGAUTH_ID                                 ((uint8)0x15U)
/**
* @brief API service ID for Csec_MPCompress function
* @details Parameter used for DET when raising an error from the Csec_MPCompress() function
* */
#define CSEC_MPCOMPRESS_ID                              ((uint8)0x16U)
/**
* @brief API service ID for Csec_GenerateProtectedKey function
* @details Parameter used for DET when raising an error from the Csec_GenerateProtectedKey() function
* */
#define CSEC_GENERATE_PROTECTED_KEY_ID                  ((uint8)0x17U)
/**
* @brief API service ID for Csec_VerifyProtectedKey function
* @details Parameter used for DET when raising an error from the Csec_VerifyProtectedKey() function
* */
#define CSEC_VERIFY_PROTECTED_KEY_ID                    ((uint8)0x18U)

/*******************************************************************************
**                               Enumerations                                 **
*******************************************************************************/
/**
* @brief          Csec_CmdType
* @details        These are the CSEc commands; they follow the same values
*                 as the SHE command definition.
*/
typedef enum
{
  CSEC_CMD_ENC_ECB                = 0x01, /**< @brief AES-128 encryption in ECB mode */
  CSEC_CMD_ENC_CBC                = 0x02, /**< @brief AES-128 encryption in CBC mode */
  CSEC_CMD_DEC_ECB                = 0x03, /**< @brief AES-128 decryption in ECB mode */
  CSEC_CMD_DEC_CBC                = 0x04, /**< @brief AES-128 decryption in CBC mode */
  CSEC_CMD_GENERATE_MAC           = 0x05, /**< @brief AES-128 based CMAC generation */
  CSEC_CMD_VERIFY_MAC             = 0x06, /**< @brief AES-128 based CMAC verification */
  CSEC_CMD_LOAD_KEY               = 0x07, /**< @brief Internal key update */
  CSEC_CMD_LOAD_PLAIN_KEY         = 0x08, /**< @brief RAM key update */
  CSEC_CMD_EXPORT_RAM_KEY         = 0x09, /**< @brief RAM key export */
  CSEC_CMD_INIT_RNG               = 0x0A, /**< @brief PRNG initialization */
  CSEC_CMD_EXTEND_SEED            = 0x0B, /**< @brief PRNG seed entropy extension */
  CSEC_CMD_RND                    = 0x0C, /**< @brief Random number generation */
  CSEC_CMD_BOOT_FAILURE           = 0x0E, /**< @brief Imporse sanction during invalid boot */
  CSEC_CMD_BOOT_OK                = 0x0F, /**< @brief Finish boot verification */
  CSEC_CMD_GET_ID                 = 0x10, /**< @brief Get UID */
  CSEC_CMD_BOOT_DEFINE            = 0x11, /**< @brief Secure boot configuration */
  CSEC_CMD_DBG_CHAL               = 0x12, /**< @brief Get debug challenge */
  CSEC_CMD_DBG_AUTH               = 0x13, /**< @brief Debug authentication */
  CSEC_CMD_MP_COMPRESS            = 0x16  /**< @brief Miyaguchi-Preneel compression */
} Csec_CmdType;

/**
* @brief          Csec_ErrType
* @details        This type defines a predefined bitfield.
*                 The bitfield provides one bit for each error code, as per SHE specification.
*/
typedef enum
{
  CSEC_ERC_NO_ERROR               = 0x0001, /**< @brief No error has occurred and the command will be executed. */
  CSEC_ERC_SEQUENCE_ERROR         = 0x0002, /**< @brief The sequence of commands or subcommands is out of sequence. */
  CSEC_ERC_KEY_NOT_AVAILABLE      = 0x0004, /**< @brief key has DBG Attached flag and debugger is active */
  CSEC_ERC_KEY_INVALID            = 0x0008, /**< @brief A function is called to perform an operation with a key that is not allowed for the given operation. */
  CSEC_ERC_KEY_EMPTY              = 0x0010, /**< @brief Key slot is empty (not initialized)/not present or higher slot (not partitioned) */
  CSEC_ERC_NO_SECURE_BOOT         = 0x0020, /**< @brief N/A for FTFC - BOOT_DEFINE once configured, will automatically run secure boot */
  CSEC_ERC_KEY_WRITE_PROTECTED    = 0x0040, /**< @brief A key update is attempted on a write protected key slot or the debugger is started while a key is write-protected. */
  CSEC_ERC_KEY_UPDATE_ERROR       = 0x0080, /**< @brief A key update did not succeed due to errors in verification of the messages. */
  CSEC_ERC_RNG_SEED               = 0x0100, /**< @brief The PRNG seed has not yet been initialized. (CSESTAT[RIN] != 1) */
  CSEC_ERC_NO_DEBUGGING           = 0x0200, /**< @brief Internal debugging is not possible because the authentication did not succeed. */
  CSEC_ERC_MEMORY_FAILURE         = 0x0400, /**< @brief General memory technology failure (multi-bit ECC error, common fault detection) */
  CSEC_ERC_GENERAL_ERROR          = 0x0800, /**< @brief Detected error that is not covered by the other error codes (Example: null pointer received, FuncID is not valid, message length invalid,
                                                        for pointer method GENERATE_MAC is the message length would cause the sequence to cross a read partition boundary )    */
  CSEC_ERC_BUSY                   = 0x1000  /**< @brief Detected error that another command is in progress */
} Csec_ErrType;

/**
* @brief          Csec_KeyIDType
* @details        This type specifies the key slot used to implement
*                 a requested cryptographic operation.
*/
typedef enum
{
  CSEC_SECRET_KEY                 = 0x00, /**< @brief Unique secret key */
  CSEC_MASTER_ECU_KEY             = 0x01, /**< @brief Used for updating other memory slots */
  CSEC_BOOT_MAC_KEY               = 0x02, /**< @brief Used by the secure booting mechanism to verify the authenticity of the software */
  CSEC_BOOT_MAC                   = 0x03, /**< @brief Stores the MAC of the Bootloader for the secure booting mechanism */
  CSEC_KEY_1                      = 0x04, /**< @brief User key 1 */
  CSEC_KEY_2                      = 0x05, /**< @brief User key 2 */
  CSEC_KEY_3                      = 0x06, /**< @brief User key 3 */
  CSEC_KEY_4                      = 0x07, /**< @brief User key 4 */
  CSEC_KEY_5                      = 0x08, /**< @brief User key 5 */
  CSEC_KEY_6                      = 0x09, /**< @brief User key 6 */
  CSEC_KEY_7                      = 0x0A, /**< @brief User key 7 */
  CSEC_KEY_8                      = 0x0B, /**< @brief User key 8 */
  CSEC_KEY_9                      = 0x0C, /**< @brief User key 9 */
  CSEC_KEY_10                     = 0x0D, /**< @brief User key 10 */
  CSEC_RAM_KEY                    = 0x0F, /**< @brief A volatile key that can be used for arbitrary operations */
  CSEC_KEY_11                     = 0x14, /**< @brief User key 11 */
  CSEC_KEY_12                     = 0x15, /**< @brief User key 12 */
  CSEC_KEY_13                     = 0x16, /**< @brief User key 13 */
  CSEC_KEY_14                     = 0x17, /**< @brief User key 14 */
  CSEC_KEY_15                     = 0x18, /**< @brief User key 15 */
  CSEC_KEY_16                     = 0x19, /**< @brief User key 16 */
  CSEC_KEY_17                     = 0x1A, /**< @brief User key 17 */
  CSEC_INVALID_KEY                = 0xFF, /**< @brief Wrong key index */
} Csec_KeyIDType;

/**
* @brief          Csec_BootFlavorType
* @details        This type specifies a boot method.
*/
typedef enum
{
  CSEC_BOOT_STRICT                = 0x00, /**< @brief Strict Sequential Boot Mode */
  CSEC_BOOT_SERIAL                = 0x01, /**< @brief Serial Boot Mode */
  CSEC_BOOT_PARALLEL              = 0x02, /**< @brief Parallel Boot Mode */
  CSEC_BOOT_NOT_DEFINED           = 0x03  /**< @brief No boot defined */
} Csec_BootFlavorType;

/**
* @brief          Csec_KeyFlagType
* @details        This type specifies key attributes.
*/
typedef enum
{
  /** All restrictions are not set */
  CSEC_ALL_ENABLED                                      = 0x00U,
  /** If this flag is set, the key cannot be used to execute CMD_GENERATE_MAC command */
  CSEC_DISABLE_WILDCARD                                 = 0x01U,
  /** If this flag is set, the key cannot be used with the CMD_ENC_ECB/CMD_DEC_ECB and
    CMD_ENC_CBC/CMD_DEC_CBC commands, but can be used with the CMD_GENERATE_MAC/CMD_VERIFY_MAC commands */
  CSEC_KEY_USAGE                                        = 0x02U,
  /** If this flag is set, the key cannont be used when the EXT_DEBUGGER bit in the ICUS status
    register is 1 */
  CSEC_DEBUGGER_PROTECTION                              = 0x04U,
  /** If this flag is set, the key cannont be used when CMD_SECURE_BOOT is not executed,
    or BOOT_OK and BOOT_FINISHED in the SREG register are set to 0 and respectively */
  CSEC_BOOT_PROTECTION                                  = 0x08U,
  /** If this flag is set, rewriting and erasing of the key are disabled.
    This flag cannot be cleared once it has been set */
  CSEC_WRITE_PROTECTION                                 = 0x10U,
  /** If this flag is set, the associated memory key slot will be treated as invalid
    by the CMD_GENERATE_MAC command (only valid for CMD_VERIFY_MAC).
    The VERIFY_ONLY attribute has no effect if KEY_USAGE == 0 */
  CSEC_VERIFY_ONLY                                      = 0x20U,
} Csec_KeyFlagType; /* polyspace MISRA2012:2.3 [Justified:Low] "User can use this data type" */

/**
* @brief          Csec_StatusType
* @details        This type defines a predefined bitfield.
*                 The bitfield provides one bit for each status code, as per SHE specification.
*/
typedef enum
{
  /** While command execution is started */
  CSEC_BUSY                                             = 0x01U,
  /** Checking the validity of BOOT_MAC_KEY after CMD_SECURE_BOOT is executed */
  CSEC_SECURE_BOOT                                      = 0x02U,
  /** CMD_SECURE_BOOT is executed without BOOT_MAC and when registration of
    BOOT_MAC is completed */
  CSEC_BOOT_INIT                                        = 0x04U,
  /** SECURE_BOOT = 1, BOOT_FINISHED = 0, and BOOT_OK = 1 and when
    CMD_BOOT_OK or CMD_BOOT_FAILURE is executed.
     CMD_SECURE_BOOT is executed and if its value does not match that of
    BOOT_MAC
     CMD_SECURE_BOOT is executed without BOOT_MAC and if BOOT_MAC_KEY is
    successfully registered
     CMD_SECURE_BOOT is executed and if ERC_KEY_NOT_AVAILABLE, ERC_MEMORY_FAILURE,
    or ERC_GENERAL_ERROR occurs during the execution of the command
     CMD_CANCEL is issued during execution of CMD_SECURE_BOOT and processing
    of the command is cancelled */
  CSEC_BOOT_FINISHED                                    = 0x08U,
  /** Execution of CMD_SECURE_BOOT is successfully completed and comparison with
    BOOT_MAC registered */
  CSEC_BOOT_OK                                          = 0x10U,
  /** Execution of CMD_INIT_RNG is successfully completed */
  CSEC_RND_INIT                                         = 0x20U,
  /** A debug interface is used */
  CSEC_EXT_DEBUGGER                                     = 0x40U,
  /** Execution of CMD_DEBUG is successfully completed */
  CSEC_INT_DEBUGGER                                     = 0x80U,
} Csec_StatusType;

/*******************************************************************************
**                                 Structures                                 **
*******************************************************************************/
typedef struct
{
  /** M1 : message containing the UID, Key ID and Authentication Key ID
      128 bits : UID (120 bit) + ID (4 bit) + AuthID (4 bit) */
  uint8 M1[CSEC_BLOCK_BYTE_LENGTH];
  /** M2 : message containing the new security flags, counter value and the key value,
           all encrypted using a derived key generated from the Authentication Key
      256 bits : ENC[CBC, K1, IV = 0] (Counter (28 bit) + KEY_FLAG (5 or 6 bit) + "0 ... 0" (94 or 95 bit) + KEY_ID (128 bit)) */
  uint8 M2[CSEC_BLOCK_BYTE_LENGTH * CSEC_TWO];
  /** M3 : message containing a MAC generated over messages M1 and M2
      128 bits : CMAC[K2] (M1 | M2) */
  uint8 M3[CSEC_BLOCK_BYTE_LENGTH];
  /** M4 : the computed verification message is stored
      256 bits : UID (120 bit) + ID (4 bit) + AuthID (4 bit) + ENC[ECB, K3] (Counter (28 bit) + "1" + "0 ... 0" (99 bit)) */
  uint8 M4[CSEC_BLOCK_BYTE_LENGTH * CSEC_TWO];
  /** M5 : the computed verification message is stored
      128 bits : CMAC[K4] (M4) */
  uint8 M5[CSEC_BLOCK_BYTE_LENGTH];
} Csec_ProtectedKey;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if (CRYPTOLIB_ENABLE_DEV_INFO == STD_ON)
/** Error log */
extern Csec_ErrType Csec_LastError[CSEC_MAX_ERROR_COUNT];

/** Error log count */
extern uint32 Csec_ErrorCount;
#endif

/*******************************************************************************
**                      External Function Prototypes                          **
*******************************************************************************/
#define CSEC_START_SEC_CODE
#include "Csec_MemMap.h"

/***************************************************************************//**
* @brief        Performs the initialization of the CSEc driver.
* @details      This function initializes the CSEc driver. If the hardware is not initialized,
*               the function shall report CSEC_E_HW_UNINIT to the DET.
* @return       void
* @pre          Hardware must be initialized.
 ******************************************************************************/
extern Csec_ErrType Csec_Init(void);

/***************************************************************************//**
* @brief        Performs AES-128 encryption in ECB mode.
* @details      This function performs the AES-128 encryption in ECB mode of the input plaintext buffer.
*               It operates under the assumption that the plaintext length is a multiple of 16 bytes.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
* @param[in]    keyID             KeyID used to perform the cryptographic operation
* @param[in]    plainTextLength   Number of bytes of plain text message to be encrypted; should be smalled than 1048560 bytes
* @param[in]    plainTextPtr      Pointer to the plain text buffer to be encrypted
* @param[out]   cipherTextPtr     Pointer to the cipher text buffer. The buffer shall have the same
*                                 size as the plain text buffer.
* @return       Csec_ErrType      Error Code after command execution. Output parameter is valid if
*                                 the error code is CSEC_ERC_NO_ERROR.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
 ******************************************************************************/
extern Csec_ErrType Csec_EncEcb(Csec_KeyIDType keyID, uint32 plainTextLength,
  const uint8* plainTextPtr, uint8* cipherTextPtr);

/***************************************************************************//**
* @brief        Performs AES-128 decryption in ECB mode.
* @details      This function performs the AES-128 decryption in ECB mode of the input ciphertext buffer.
*               It operates under the assumption that the ciphertext length is a multiple of 16 bytes.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
* @param[in]    keyID             KeyID used to perform the cryptographic operation
* @param[in]    cipherTextLength  Number of bytes of cipher text message to be decrypted;  should be smalled than 1048560 bytes
* @param[in]    cipherTextPtr     Pointer to the cipher text buffer
* @param[out]   plainTextPtr      Pointer to the plain text buffer. The buffer shall have the same
*                                 size as the cipher text buffer.
* @return       Csec_ErrType      Error Code after command execution. Output parameter is valid if
*                                 the error code is CSEC_ERC_NO_ERROR.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
 ******************************************************************************/
extern Csec_ErrType Csec_DecEcb(Csec_KeyIDType keyID, uint32 cipherTextLength,
  const uint8* cipherTextPtr, uint8* plainTextPtr);

/***************************************************************************//**
* @brief        Performs AES-128 encryption in CBC mode.
* @details      This function performs the AES-128 encryption in CBC mode of the input plaintext buffer.
*               It operates under the assumption that the plaintext length is a multiple of 16 bytes.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
* @param[in]    keyID             KeyID used to perform the cryptographic operation
* @param[in]    plainTextLength   Number of bytes of plain text message to be encrypted;  should be smalled than 1048560 bytes
* @param[in]    plainTextPtr      Pointer to the plain text buffer
* @param[in]    ivPtr             Pointer to the initialization vector buffer
* @param[out]   cipherTextPtr     Pointer to the cipher text buffer. The buffer shall have the same
*                                 size as the plain text buffer.
* @return       Csec_ErrType      Error Code after command execution. Output parameter is valid if
*                                 the error code is CSEC_ERC_NO_ERROR.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
 ******************************************************************************/
extern Csec_ErrType Csec_EncCbc(Csec_KeyIDType keyID, uint32 plainTextLength,
  const uint8* plainTextPtr, uint8* cipherTextPtr, const uint8* ivPtr);

/***************************************************************************//**
* @brief        Performs AES-128 decryption in CBC mode.
* @details      This function performs the AES-128 decryption in CBC mode of the input ciphertext buffer.
*               It operates under the assumption that the ciphertext length is a multiple of 16 bytes.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
* @param[in]    keyID             KeyID used to perform the cryptographic operation
* @param[in]    cipherTextLength  Number of bytes of cipher text message to be decrypted;  should be smalled than 1048560 bytes
* @param[in]    cipherTextPtr     Pointer to the cipher text buffer
* @param[in]    ivPtr             Pointer to the initialization vector buffer
* @param[out]   plainTextPtr      Pointer to the plain text buffer. The buffer shall have the same
*                                 size as the cipher text buffer.
* @return       Csec_ErrType      Error Code after command execution. Output parameter is valid if
*                                 the error code is CSEC_ERC_NO_ERROR.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
 ******************************************************************************/
extern Csec_ErrType Csec_DecCbc(Csec_KeyIDType keyID, uint32 cipherTextLength,
  const uint8* cipherTextPtr, uint8* plainTextPtr, const uint8* ivPtr);

/***************************************************************************//**
* @brief        Calculates the MAC of a given message using CMAC with AES-128.
* @details      This function calculates the MAC of a given message based on CMAC with the 128-bit Advanced Encryption Standard.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
* @param[in]    keyID             KeyID used to perform the cryptographic operation
* @param[in]    dataPtr           Pointer to the message buffer
* @param[in]    dataLength        Number of bits of message on which CMAC is to be computed
* @param[out]   macPtr            Pointer to the 128-bit buffer containing the result of the CMAC generation
* @return       Csec_ErrType      Error Code after command execution. Output parameter is valid if
*                                 the error code is CSEC_ERC_NO_ERROR.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
 ******************************************************************************/
extern Csec_ErrType Csec_GenerateMac(Csec_KeyIDType keyID, const uint8* dataPtr,
  uint32 dataLength, uint8* macPtr);

/***************************************************************************//**
* @brief        Calculates the MAC of a given message using CMAC with AES-128.
* @details      This function verifies the MAC of of a given message based on CMAC with the 128-bit Advanced Encryption Standard.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
* @param[in]    keyID             KeyID used to perform the cryptographic operation
* @param[in]    dataPtr           Pointer to the message buffer
* @param[in]    dataLength        Number of bits of message on which CMAC is to be computed
* @param[in]    macLength         Number of bits of the CMAC to be compared. A macLength value of zero indicates that
*                                 all 128-bits are to be compared.
* @param[in]    macRefPtr         Pointer to the buffer containing the CMAC to be verified.
* @param[out]   statusPtr         Status of the MAC verification command
*                                 (true: verification operation passed; false: verification operation failed)
* @return       Csec_ErrType      Error Code after command execution. Output parameter is valid if
*                                 the error code is CSEC_ERC_NO_ERROR.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
 ******************************************************************************/
extern Csec_ErrType Csec_VerifyMac(Csec_KeyIDType keyID, const uint8* dataPtr,
  uint32 dataLength, uint8 macLength, const uint8* macRefPtr, boolean* statusPtr);

/***************************************************************************//**
* @brief        Updates an internal key per the SHE specification.
* @details      The function updates an internal key per the SHE specification.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
* @param[in]    keyID             The ID of the key to be updated.
* @param[in]    protectedKeyPtr   Pointer to the M1 ... M5 structure.
* @return       Csec_ErrType      Error Code after command execution. Output parameters are valid if
*                                 the error code is CSEC_ERC_NO_ERROR.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
 ******************************************************************************/
extern Csec_ErrType Csec_LoadKey(Csec_KeyIDType keyID,
  Csec_ProtectedKey* protectedKeyPtr);

/***************************************************************************//**
* @brief        Updates the RAM key memory slot with a 128-bit plaintext.
* @details      The function updates the RAM key memory slot with a 128-bit plaintext. The key is loaded without the
*               encryption and verification of the key, i.e. the key is handed over in plaintext.
*               A plain key can only be loaded into the RAM_KEY slot.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
* @param[in]    keyPtr            Pointer to the 128-bit buffer containing the key that needs to be copied in RAM_KEY slot.
* @return       Csec_ErrType      Error Code after command execution.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
 ******************************************************************************/
extern Csec_ErrType Csec_LoadPlainKey(const uint8* keyPtr);

/***************************************************************************//**
* @brief        Exports the RAM_KEY into a format protected by SECRET_KEY.
* @details      The function exports the RAM_KEY into a format protected by SECRET_KEY. Only keys loaded with the
*               CMD_LOAD_PLAIN_KEY command may be exported. The output messages are compatible with the messages used for LOAD_KEY.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
* @param[in]    protectedKeyPtr   Pointer to the M1 ... M5 structure.
* @return       Csec_ErrType      Error Code after command execution. Output parameters are valid if
*                                 the error code is CSEC_ERC_NO_ERROR.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
 ******************************************************************************/
extern Csec_ErrType Csec_ExportRamKey(Csec_ProtectedKey* protectedKeyPtr);

/***************************************************************************//**
* @brief        Initializes the seed and derives a key for the PRNG.
* @details      This function initializes the seed and derives a key for the PRNG.
*               The function must be called before CMD_RND after every power cycle or reset.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
* @return       Csec_ErrType      Error Code after command execution. The error code CSEC_ERC_NO_ERROR
*                                 specifies that the command will execute.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
 ******************************************************************************/
extern Csec_ErrType Csec_InitRnd(void);

/***************************************************************************//**
* @brief        Extends the seed of the PRNG by compressing the former seed value and the supplied entropy into a new seed.
* @details      This function extends the seed of the PRNG by compressing the former seed value and the supplied
*               entropy into a new seed which will be used to generate the following random numbers. The random number
*               generator has to be initialized by Csec_InitRnd() before the seed can be extended.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
* @param[in]    entropyPtr        Pointer to a 128-bit buffer containing the entropy
* @return       Csec_ErrType      Error Code after command execution. The error code CSEC_ERC_NO_ERROR
*                                 specifies that the command will execute.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
 ******************************************************************************/
extern Csec_ErrType Csec_ExtendSeed(const uint8* entropyPtr);

/***************************************************************************//**
* @brief        Generates a vector of 128 random bits.
* @details      The function returns a vector of 128 random bits. The random number generator has to be
*               initialized by Csec_InitRnd() before random numbers can be supplied.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
* @param[out]   rndPtr            Pointer to a 128-bit buffer where the generated random number is to be stored
* @return       Csec_ErrType      Error Code after command execution. Output parameter is valid if the error
*                                 code is CSEC_NO_ERROR.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
 ******************************************************************************/
extern Csec_ErrType Csec_Rnd(uint8* rndPtr);

/***************************************************************************//**
* @brief        Signals a failure detected during later stages of the boot process.
* @details      This function is called during later stages of the boot process to detect a failure.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
* @return       Csec_ErrType      Error Code after command execution.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
 ******************************************************************************/
extern Csec_ErrType Csec_BootFailure(void);

/***************************************************************************//**
* @brief        Marks a successful boot verification during later stages of the boot process.
* @details      The function is called during later stages of the boot process to mark the successful
*               boot verification.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
* @return       Csec_ErrType      Error Code after command execution.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
 ******************************************************************************/
extern Csec_ErrType Csec_BootOk(void);

/***************************************************************************//**
* @brief        Implements an extension of the SHE standard to define both the user boot size and boot method.
* @details      The function implements an extension of the SHE standard to define both the user boot
*               size and boot method.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
*               During parallel boot operation FLASH_CLK must be the default FIRC_CLK and should not be changed until boot operation is complete.
* @param[in]    bootSize          Number of blocks of 128-bit data to check on boot. Maximum size is 512kBytes.
* @param[in]    bootMethod        The boot method
* @return       Csec_ErrType      Error Code after command execution.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
 ******************************************************************************/
extern Csec_ErrType Csec_BootDefine(uint32 bootSize, Csec_BootFlavorType bootMethod);

/***************************************************************************//**
* @brief        Returns the content of the status register.
* @details      The function shall return the content of the status register.
* @return       Csec_StatusType     Value of the status register.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
 ******************************************************************************/
extern Csec_StatusType Csec_GetStatus(void);

/***************************************************************************//**
* @brief        Returns the identity (UID) and the value of the status register protected by a MAC over
*               a challenge and the data.
* @details      This function returns the identity (UID) and the value of the status register protected by
*               a MAC over a challenge and the data.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
* @param[in]    challengePtr      Pointer to the 128-bit buffer containing the challenge data
* @param[out]   sregPtr           Value of the status register
* @param[out]   uidPtr            Pointer to 120-bit buffer where the UID will be stored
* @param[out]   macPtr            Pointer to the 128 bit buffer where the MAC generated over the challenge,
*                                 UID and status will be stored.
* @return       Csec_ErrType      Error Code after command execution.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
 ******************************************************************************/
extern Csec_ErrType Csec_GetUID(const uint8* challengePtr, uint8* sregPtr,
  uint8* uidPtr, uint8* macPtr);

/***************************************************************************//**
* @brief        Generates a random number used to generate an authorization request.
* @details      This function is used to obtain a random number which the user will use, along with the
*               MASTER_ECU_KEY and UID, to generate an authorization request.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
* @param[out]   challengePtr      Pointer to the 128-bit buffer whre the challenge data will be stored.
* @return       Csec_ErrType      Error Code after command execution.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
*******************************************************************************/
extern Csec_ErrType Csec_DbgChal(uint8* challengePtr);

/***************************************************************************//**
* @brief        Erases all keys (actual and outdated) stored in NVM Memory.
* @details      This function erases all keys (actual and outdated) stored in NVM Memory if the authorization
*               is confirmed by CSEc.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
* @param[in]    authorizationPtr  Pointer to the 128-bit buffer containing the authorization value
* @return       Csec_ErrType      Error Code after command execution.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
*******************************************************************************/
extern Csec_ErrType Csec_DbgAuth(const uint8* authorizationPtr);

/***************************************************************************//**
* @brief        Provides Miyaguchi-Preneel compression.
* @details      This function accesses a Miyaguchi-Preneel compression feature
*               within the CSEc feature set to compress the given messages.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
* @param[in]    dataPtr           Pointer to the messages to be compressed. Messages must be pre-processed
*                                 per SHE specification if they do not already meet the full 128-bit block
*                                 size requirement.
* @param[in]    messageLength     The number of 128-bit messages to be compressed
* @param[out]   compressPtr       Pointer to the 128 bit buffer storing the compressed data
* @return       Csec_ErrType      Error Code after command execution. Output parameter is valid if
*                                 the error code is CSEC_ERC_NO_ERROR.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
*******************************************************************************/
extern Csec_ErrType Csec_MPCompress(const uint8* dataPtr, uint16 messageLength,
  uint8* compressPtr);

/***************************************************************************//**
* @brief        Perform the challenge & response procedure to erase all keys (actual and outdated) stored in NVM Memory 
* @details      This function deletes all keys in NVM memory by performing random number generation,
*               UID acquisition and autorization generation.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
* @param[in]    masterEcuKeyPtr   Pointer to the raw MASTER_ECU_KEY buffer
* @return       Csec_ErrType      Error Code after command execution.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
*******************************************************************************/
extern Csec_ErrType Csec_Debug(const uint8* masterEcuKeyPtr);

/***************************************************************************//**
* @brief        Genrate M1, M2 and M3
* @details      This function generates M1, M2 and M3 based on input Key ID,
*               Key value, AuthKey ID, AuthKey value, Counter and KeyFlag information.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
* @param[in]    keyID             Key ID to be registered / updated
* @param[in]    keyPtr            Pointer to the target key buffer to be registered / updated
* @param[in]    authID            AuthKey ID of target key to be registered / updated
* @param[in]    authKeyPtr        Pointer to the AuthKey buffer of target key to be registered / updated
* @param[in]    counter           New counter value of registered /updated key
* @param[in]    keyFlag           Flag information of registered / updated key
* @param[out]   protectedKeyPtr   Pointer to protected key buffer which has M1, M2 and M3
* @return       Csec_ErrType      Error Code after command execution.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
*******************************************************************************/
extern Csec_ErrType Csec_GenerateProtectedKey(Csec_KeyIDType keyID,
  const uint8* keyPtr, Csec_KeyIDType authID, const uint8* authKeyPtr,
  uint32 counter, Csec_KeyFlagType keyFlag, Csec_ProtectedKey* protectedKeyPtr);

/***************************************************************************//**
* @brief        Verify M4 and M5
* @details      This function verifies M4 and M5 which was generated while loading a key.
*               This function does not work for VLRP (Very Low Power) and HSRUN (High Speed Run) modes.
* @param[in]    keyID             Key ID which was registered / updated
* @param[in]    keyPtr            Pointer to the target key buffer which was registered / updated
* @param[in]    authID            AuthKey ID of target key which was registered / updated
* @param[in]    counter           Counter value which was registered / updated
* @param[in]    protectedKeyPtr   Pointer to protected key buffer which has M4 and M5
* @param[out]   resultPtr         Status of the verification
*                                 (true: verification operation passed; false: verification operation failed)
* @return       Csec_ErrType      Error Code after command execution.
* @pre          Driver must be initialized (FCNFG[RAMRDY] == 0 and FCNFG[EEERDY] == 1).
*******************************************************************************/
extern Csec_ErrType Csec_VerifyProtectedKey(Csec_KeyIDType keyID,
  const uint8* keyPtr, Csec_KeyIDType authID, uint32 counter,
  const Csec_ProtectedKey* protectedKeyPtr, boolean* resultPtr);

#define CSEC_STOP_SEC_CODE
#include "Csec_MemMap.h"

#define CSEC_START_SEC_RAMCODE
#include "Csec_MemMap.h"

/***************************************************************************//**
* @brief        Apply CSEc configurations
* @details      This function enables CSEc while applying CSEc configuration
*               (non volatile key size, security flag extension, FlexRAM load option,
*               EEPROM data set size, FlexNVM partition).
* @return       Csec_StatusType     Value of the status register.
*******************************************************************************/
extern Csec_ErrType Csec_ConfigureCSEc(void);

#define CSEC_STOP_SEC_RAMCODE
#include "Csec_MemMap.h"

#endif /* (CRYPTOLIB_SUPORT_HSM_CSEC == STD_ON) */

#endif /* CSEC_DRIVER_H */

/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:2.5 [Not a defect:Low] "Can be used as per configuration" */
/* polyspace-end MISRA2012:D4.8 [Not a defect:Low] "False detection" */
/* polyspace-end MISRA2012:D4.5 [Not a defect:Low] "No Impact of this rule violation" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
