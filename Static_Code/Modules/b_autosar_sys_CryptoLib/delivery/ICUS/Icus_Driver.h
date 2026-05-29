/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Icus_Driver.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Hsm (Hardware Security Module)                                **
**                                                                            **
**  PURPOSE   : Header file for F1K ICUS                                      **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.3     20-May-2019   Sinil        Redmine #17571                        **
** 1.0.2     28-Mar-2019   Sinil        Redmine #16794, #17130                **
** 1.0.1     21-Dec-2018   Sinil        Redmine #15254                        **
** 1.0.0     16-Feb-2017   Sinil        Initial version                       **
*******************************************************************************/

#ifndef ICUS_DRIVER_H
#define ICUS_DRIVER_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "CryptoLib_Cfg.h"

#if (CRYPTOLIB_SUPORT_HSM_ICUS == STD_ON)
/*******************************************************************************
**                      Enumerations                                          **
*******************************************************************************/
/**
  Command
  SHE 표준 참조
*/
typedef enum
{
  /**  This command encrypts an integer multiple (n) of 128 bits of plain text
    in ECB mode of AES */
  CMD_ENC_ECB                                           = 0x0001U,
  /**  This command encrypts an integer multiple (n) of 128 bits of plain text
    in CBC mode of AES */
  CMD_ENC_CBC                                           = 0x0002U,
  /**  This command decrypts an integer multiple (n) of 128 bits of cipher text
    in ECB mode of AES */
  CMD_DEC_ECB                                           = 0x0003U,
  /**  This command decrypts an integer multiple (n) of 128 bits of cipher text
    in CBC mode of AES */
  CMD_DEC_CBC                                           = 0x0004U,
  /**  This command generates MAC of the message with the specified bit length
    of the message */
  CMD_GENERATE_MAC                                      = 0x0005U,
  /**  This command generates MAC of the message with the specified bit length
    of the message and verifies the MAC for the number of the bits specified
    MAC length */
  CMD_VERIFY_MAC                                        = 0x0007U,
  /**  This command updates a key */
  CMD_LOAD_KEY                                          = 0x0008U,
  /**  This command registers the plain text key in the RAM_KEY memory slot */
  CMD_LOAD_PLAIN_KEY                                    = 0x0009U,
  /**  This command exports the data in the RAM_KEY memory slot in a secure format.
    This command can only output RAM_KEY values that have been registered by
    CMD_LOAD_PLAIN_KEY */
  CMD_EXPORT_RAM_KEY                                    = 0x000AU,
  /**  This command generates a seed of a random number from the TRNG */
  CMD_INIT_RNG                                          = 0x000BU,
  /**  This command extends the seed of the pseudo-random number by 128 bits of
    entropy */
  CMD_EXTEND_SEED                                       = 0x000CU,
  /**  This command outputs a 128-bit random number. At the same time, it updates
    the seed of the pseudo-random number */
  CMD_RND                                               = 0x000DU,
  /**  When BOOT_MAC_KEY and BOOT_MAC are registered, this command checks if the
    MAC of the data provided as input matches the BOOT_MAC value. If BOOT_MAC
    slot is empty, a generated BOOT_MAC value is registerd in the BOOT_MAC slot */
  CMD_SECURE_BOOT                                       = 0x000EU,
  /**  This command sets the BOOT_FINISHED flag in the ICUS status register,
    and clears the BOOT_OK flag */
  CMD_BOOT_FAILUERE                                     = 0x0020U,
  /**  This command sets the BOOT_FINISHED flag in the ICUS status register */
  CMD_BOOT_OK                                           = 0x0021U,
  /**  This command calculates the MAC of CHALLENGE, UID and SREG by using
    MASTER_ECU_KEY on the ICUS side based on the CHALLENGE value conveyed from
    the CPU and returns it with a 120-bit UID and 8-bit SREG */
  CMD_GET_ID                                            = 0x0022U,
  /**  This comamnd verifies the autentication MAC value (AUTHORIZATION) against
    a 128-bit random number (CHALLENGE). If the MAC value is correct, the
    INT_DEBUGGER flag in the ICUS status register is set and all the keys
    registered in RAM_KEY and NVM are cleared. It alse clears the RND_INIT
    flag in the ICUS status register */
  CMD_DEBUG                                             = 0x0023U,
  /**  This command cancels command processing and clears the BUSY flag in the
    ICUS status register */
  CMD_CANCEL                                            = 0x003FU
} Icus_CmdType;

/** 
  Error 상태
  SHE 표준 참조
*/
typedef enum
{
  /**  Normal end */
  ERC_NO_ERROR                                          = 0x0000U,
  /** 
    CMD_SECURE_BOOT
    - After execution of CMD_SECURE_BOOT, the command is re-executed
    - After return from STOP mode, CMD_SECURE_BOOT was executed OP_NSBF_PSM
      in OPBT9 was 1
    - After return from STOP mode, CMD_SECURE_BOOT was re-executed OP_BCLR_PSM
      in OPBT9 was 0
  */
  ERC_SEQUENCE_ERROR                                    = 0x0001U,
  /** 
    CMD_ENC_ECB/CMD_DEC_ECB, CMD_ENC_CBC/CMD_DEC_CBC, CMD_GENERATE_MAC/CMD_VERIFY_MAC
    - The BOOT_PROTECTION flag of the key to be used was 1 while CMD_SECURE_BOOT
      was not done
    - CMD_SECURE_BOOT was executed while BOOT_FINISHED and BOOT_OK in the ICUS
      status register were 1 and 0 respectively, and when the BOOT_PROTECTION
      flag of the key to be used was 1
    - The DEBUGGER_PROTECTION flag of the key to be used was 1 while EXT_DEBUGGER
      in the ICUS status register was 1
    CMD_LOAD_KEY
    - When RAM_KEY was registerd, while CMD_SECURE_BOOT was not executed, and
      when the BOOT_PROTECTION flag of the AuthID key was 1
    - When RAM_KEY was registerd, while BOOT_FINISHED and BOOT_OK in the ICUS
      status register were 1 and 0 respectively, and when the BOOT_PROTECTION
      flag of the AuthID key was 1
    - When RAM_KEY is registered, the DEBUGGER_PROTECTION flag of the AuthID
      key was 1 while EXT_DEBUGGER in the ICUS status register was 1
    CMD_EXPORT_RAM_KEY
    - The BOOT_PROTECTION flag of MASTER_ECU_KEY was 1 while CMD_SECURE_BOOT
      was not done
    - CMD_SECURE_BOOT was executed while BOOT_FINISHED and BOOT_OK in the ICUS
      status register were 1 and 0 respectively, and when the BOOT_PROTECTION
      flag of the key to be used was 1
    - The DEBUGGER_PROTECTION flag of MASTER_ECU_KEY was 1 while EXT_DEBUGGER
      in the ICUS status register was 1
    CMD_SECURE_BOOT
    - The DEBUGGER_PROTECTION flag in BOOT_MAC_KEY or BOOT_MAC was 1 while
      EXT_DEBUGGER in the ICUS status register was 1
  */
  ERC_KEY_NOT_AVAILABLE                                 = 0x0002U,
  /** 
    CMD_ENC_ECB/CMD_DEC_ECB, CMD_ENC_CBC/CMD_DEC_CBC
    - The value specified by KEYID has not been defined
    - A key other than KEY_<n> or RAM_KEY was specified
    - A key where KEY_USAGE of KEY_FLAG is 1 was specified
    CMD_GENERATE_MAC
    - The value specified by KEYID has not been defined
    - A key other than KEY_<n> or RAM_KEY was specified
    - A key where KEY_USAGE of KEY_FLAG is 0 was specified
    - A key where CMAC_USAGE of KEY_FLAG is 1 was specified
    CMD_VERIFY_MAC
    - The value specified by KEYID has not been defined
    - A key other than KEY_<n>, RAM_KEY or BOOT_MAC_KEY was specified
    - A key where KEY_USAGE of KEY_FLAG is 0 was specified
    CMD_LOAD_KEY
    - A problem occured in specifying the AuthID value for the ID value
      when M1 was specified
    CMD_EXPORT_RAM_KEY
    - The registered RAM_KEY was registered by the CMD_LOAD_KEY command
  */
  ERC_KEY_INVALID                                       = 0x0004U,
  /** 
    CMD_ENC_ECB/CMD_DEC_ECB, CMD_ENC_CBC/CMD_DEC_CBC, CMD_GENERATE_MAC
    - The specified KEY_<n> or RAM_KEY is empty
    CMD_VERIFY_MAC
    - The specified KEY_<n>, RAM_KEY or BOOT_MAC_KEY is empty
    CMD_LOAD_KEY
    - The key indicated by AuthID value specified in M1 was empty, except when
      the ID value and the AuthID value are the same
    CMD_EXPORT_RAM_KEY
    - RAM_KEY was empty
    CMD_DEBUG
    - MASTER_ECU_KEY was empty
  */
  ERC_KEY_EMPTY                                         = 0x0008U,
  /** 
    CMD_SECURE_BOOT
    - BOOT_MAC_KEY was empty
    CMD_BOOT_FAILURE, CMD_BOOT_OK
    - This command was executed while the ICUS status register did not satisfy
      the condition SECURE_BOOT = 1 & BOOT_OK = 1 & BOOT_FINISHED = 0
  */
  ERC_NO_SECURE_BOOT                                    = 0x0010U,
  /** 
    CMD_LOAD_KEY
    - A key has already been written to the memory slot to be updated, and the
      WRITE_PROTECTION flag of the key is 1
    CMD_DEBUG
    - Among all the keys that have been registered in NVM, the WRITE_PROTECTION
      flag for any of them is 1
  */
  ERC_KEY_WRITE_PROTECTED                               = 0x0020U,
  /** 
    CMD_LOAD_KEY
    - M3 did not match the result of MAC calculation for M1 and M2
    - The specified UID value did not match the UID value of the device
    - The UID value in M1 is specified as a Wildcard UID, but the DISABLE_WILDCARD
      flag of the key to be updated is 1
    - A key has already been written to the memory slot to be updated, but the
      Counter value of the key is greater then or equal to the Counter value
      specified in M2
    - Any value except 0 is set to the counter value or KEY_FLAG specified in
      M2 when RAM_KEY is registered
  */
  ERC_KEY_UPDATE_ERROR                                  = 0x0040U,
  /** 
    CMD_EXTEND_SEED, CMD_RND
    - RND_INIT in the ICUS status register is 0
    CMD_DEBUG
    - This command was executed while RND_INIT in the ICUS status register was 0
  */
  ERC_RNG_SEED                                          = 0x0080U,
  /** 
    CMD_DEBUG
    - The specified AUTHORIZATION value is not correct
  */
  ERC_NO_DEBUGGING                                      = 0x0100U,
  /** 
    CMD_ENC_ECB/CMD_DEC_ECB, CMD_ENC_CBC/CMD_DEC_CBC, CMD_GENERATE_MAC/CMD_VERIFY_MAC,
    CMD_LOAD_KEY, CMD_LOAD_PLAIN_KEY, CMD_EXPORT_RAM_KEY,
    CMD_INT_RNG, CMD_EXTEND_SEED, CMD_RND,
    CMD_SECURE_BOOT, CMD_BOOT_FAILURE, CMD_BOOT_OK,
    CMD_GET_ID, CMD_DEBUG
    - The ICUS was processing a command when this command was set
  */
  ERC_BUSY                                              = 0x0200U,
  /** 
    CMD_ENC_ECB/CMD_DEC_ECB, CMD_ENC_CBC/CMD_DEC_CBC, CMD_GENERATE_MAC/CMD_VERIFY_MAC,
    CMD_LOAD_KEY, CMD_EXPORT_RAM_KEY, CMD_GET_ID
    - An ECC error occured due to a read access to the data flash memory by ICUS
    - An ECC error notification occurred due to a read access th the internal
      RAM of the ICUS
    CMD_LOAD_PLAIN_KEY, CMD_INT_RNG, CMD_EXTEND_SEED, CMD_RND
    - An ECC error notification occurred due to a read access th the internal
      RAM of the ICUS
    CMD_SECURE_BOOT, CMD_DEBUG
    - An error occurred while data was being written to a memory slot
    - An ECC error occured due to a read access to the data flash memory by ICUS
    - An ECC error notification occurred due to a read access th the internal
      RAM of the ICUS
  */
  ERC_MEMORY_FAILURE                                    = 0x0400U,
  /** 
    CMD_ENC_ECB/CMD_DEC_ECB
    - The ICUS data transfer number register was 0 or 1 when this command was set
    CMD_VERIFY_MAC
    - OP_MIN_ML_NV in OPBT9 is 0, and except under the following condition
      The number of bits of MAC's length >= the number of bits specified as the
      minumum MAC_LENGTH value by setting OPBT9
    CMD_INIT_RNG
    - When self-diagnosis test fails while the AIS32EN bit of ICUS command
      register is set to 1
    CMD_SECURE_BOOT
    - The specified value of SIZE was 0 byte
  */
  ERC_GENERAL_ERROR                                     = 0x0800U,
  ERC_TIMEOUT_ERROR                                     = 0x0A00U,
} Icus_ErrType;

/** 
  Key ID
  SHE 표준 참조
*/
typedef enum
{
  /**  This key is unique the the device. This key information is not open
    to the user. This key is used to register and acquire RAM_KEY */
  SECRET_KEY                                            = 0x00U,
  /**  This key is the property of the owner of the device is used to erase,
    register and update other keys to be stored in the device */
  MASTER_ECU_KEY                                        = 0x01U,
  /**  This key is used for the secure boot function. Writing this key enables
    the secure boot function. This key can also be used by the MAC verification
    command (CMD_VERIFY_MAC) */
  BOOT_MAC_KEY                                          = 0x02U,
  /**  BOOT_MAC is the MAC value of the boot code to be verified at the time of
    secure booting. Although it is not used as a key, its value is managed
    and handled in the same way as the NVM keys.
    If BOOT_MAC has not been set at the initial startup of secure booting,
    the MAC for the given boot code memory block is calculated and stored
    in the memory slot as BOOT_MAC. After that, at the startup of secure
    booting, the MAC value calculated from the given boot code memory block
    is compared with the registerd BOOT_MAC, and the result of comparison
    is indicated in the ICUS status register */
  BOOT_MAC                                              = 0x03U,
  /** These keys are used to encrypt and decrypt data and to generate and verify
    the message authentication code (MAC). The intended usage of these keys is
    specified by the KEY_USASE flag and the CMAC_USAGE flag in KEY_FLAG for the
    given key.
    n represents any number from 1 to 20. */
  KEY_1                                                 = 0x04U,
  KEY_2                                                 = 0x05U,
  KEY_3                                                 = 0x06U,
  KEY_4                                                 = 0x07U,
  KEY_5                                                 = 0x08U,
  KEY_6                                                 = 0x09U,
  KEY_7                                                 = 0x0AU,
  KEY_8                                                 = 0x0BU,
  KEY_9                                                 = 0x0CU,
  KEY_10                                                = 0x0DU,
  KEY_11                                                = 0x14U,
  KEY_12                                                = 0x15U,
  KEY_13                                                = 0x16U,
  KEY_14                                                = 0x17U,
  KEY_15                                                = 0x18U,
  KEY_16                                                = 0x19U,
  KEY_17                                                = 0x1AU,
  KEY_18                                                = 0x1BU,
  KEY_19                                                = 0x1CU,
  KEY_20                                                = 0x1DU,
  /** This key is used to encrypt and decrypt data and to generate
    and verify a MAC. This key does not have KEY_FLAG, so specifying
    the intended use of this key is not necessary */
  RAM_KEY                                               = 0x0EU,
  /** Wrong key index */
  INVALID_KEY                                           = 0xFFU,
} Icus_KeyIDType;

/*
  Key Flag
  SHE 표준 참조
*/
typedef enum
{
  /** All restrictions are not set */
  ALL_ENABLED                                           = 0x00U,
  /** (CU) If this flag is set, the key cannot be used to execute CMD_GENERATE_MAC command */
  CMAC_USAGE                                            = 0x01U,
  /** (DWC) If this flag is set, key update by the wildcard UID is disabled */
  DISABLE_WILDCARD                                      = 0x02U,
  /** (KU) If this flag is set, the key cannot be used with the CMD_ENC_ECB/CMD_DEC_ECB and
    CMD_ENC_CBC/CMD_DEC_CBC commands, but can be used with the CMD_GENERATE_MAC/CMD_VERIFY_MAC commands.
    However, the latter also depends on the setting of the CMAC_USAGE flag */
  KEY_USAGE                                             = 0x04U,
  /** (DP) If this flag is set, the key cannont be used when the EXT_DEBUGGER bit in the ICUS status
    register is 1 */
  DEBUGGER_PROTECTION                                   = 0x08U,
  /** (BP) If this flag is set, the key cannont be used when CMD_SECURE_BOOT is not executed,
    or BOOT_OK and BOOT_FINISHED in the ICUS0ICRSTS register are set to 0 and respectively */
  BOOT_PROTECTION                                       = 0x10U,
  /** (WP) If this flag is set, rewriting and erasing of the key are disabled.
    This flag cannot be cleared once it has been set */
  WRITE_PROTECTION                                      = 0x20U,
} Icus_KeyFlagType;

/*
  내부 상태
  SHE 표준 참조
*/
typedef enum
{
  /** While command execution is started */
  BUSY                                                  = 0x01U,
  /** Checking the validity of BOOT_MAC_KEY after CMD_SECURE_BOOT is executed */
  SECURE_BOOT                                           = 0x02U,
  /** CMD_SECURE_BOOT is executed without BOOT_MAC and when registration of
    BOOT_MAC is completed */
  BOOT_INIT                                             = 0x04U,
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
  BOOT_FINISHED                                         = 0x08U,
  /** Execution of CMD_SECURE_BOOT is successfully completed and comparison with
    BOOT_MAC registered */
  BOOT_OK                                               = 0x10U,
  /** Execution of CMD_INIT_RNG is successfully completed */
  RND_INIT                                              = 0x20U,
  /** A debug interface is used */
  EXT_DEBUGGER                                          = 0x40U,
  /** Execution of CMD_DEBUG is successfully completed */
  INT_DEBUGGER                                          = 0x80U,
} Icus_StatusType;

/*******************************************************************************
**                      Defines                                               **
*******************************************************************************/
#define ICUS_BLOCK_BYTE_LENGTH                          (16U)
#define ICUS_BLOCK_BIT_LENGTH                           (128U)

#define ICUS_RND_SEED_BYTE_LENGTH                       (4U)
#define ICUS_RND_GEN_BYTE_LENGTH                        (4U)

#define ICUS_FALSE                                      (0)
#define ICUS_TRUE                                       (1)

#define ICUS_ZERO                                       (0x00U)
#define ICUS_ONE                                        (0x01U)
#define ICUS_TWO                                        (0x02U)
#define ICUS_THREE                                      (0x03U)
#define ICUS_FOUR                                       (0x04U)
#define ICUS_FIVE                                       (0x05U)
#define ICUS_SIX                                        (0x06U)
#define ICUS_SEVEN                                      (0x07U)
#define ICUS_EIGHT                                      (0x08U)
#define ICUS_ONE_SIX                                    (0x10U)
#define ICUS_TWO_FOUR                                   (0x18U)
#define ICUS_THREE_TWO                                  (0x20U)

#define ICUS_MAX_ERROR_COUNT                            (5U)

/*******************************************************************************
**                      Structures                                            **
*******************************************************************************/
typedef struct
{
  /** 128 bits : UID (120 bit) + ID (4 bit) + AuthID (4 bit) */
  uint8 M1[ICUS_BLOCK_BYTE_LENGTH];
  /** 256 bits : ENC[CBC, K1, IV = 0] (Counter (28 bit) + KEY_FLAG (6 bit) + "0 ... 0" (94 bit) + KEY_ID (128 bit)) */
  uint8 M2[ICUS_BLOCK_BYTE_LENGTH * ICUS_TWO];
  /** 128 bits : CMAC[K2] (M1 | M2) */
  uint8 M3[ICUS_BLOCK_BYTE_LENGTH];
  /** 256 bits : UID (120 bit) + ID (4 bit) + AuthID (4 bit) + ENC[ECB, K3] (Counter (28 bit) + "1" + "0 ... 0" (99 bit)) */
  uint8 M4[ICUS_BLOCK_BYTE_LENGTH * ICUS_TWO];
  /** 128 bits : CMAC[K4] (M4) */
  uint8 M5[ICUS_BLOCK_BYTE_LENGTH];
} Icus_ProtectedKey;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/** Error log */
extern Icus_ErrType Icus_GddLastError[ICUS_MAX_ERROR_COUNT];

/** Error log count */
extern uint32 Icus_GulErrorCount;

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/***************************************************************************//**
 * @details   AES-128 ECB(Electronic Code Block) 모드 암호화 수행
 *            평문 : 128-bit 배수의 블럭
 *            암호문 : 128-bit 배수의 블럭
 * @param     [in]  ddKeyId               AES ECB 모드 암호화시 사용할 Key ID
 *                                        KEY_<n>, RAM_KEY
 * @param     [in]  ulNumBlocks           입력에 사용되는 128-bit 평문 블럭 개수
 * @param     [in]  pPlainBlock           평문 블럭 버퍼 포인터
 * @param     [out] pCipherBlock          암호문 블럭 버퍼 포인터
 * @return    Icus_ErrType                기능 수행 결과
 * @remark    입출력 데이터는 반드시 128-bit 의 배수여야 한다
 ******************************************************************************/
extern Icus_ErrType Icus_EncEcb(Icus_KeyIDType ddKeyId, uint32 ulNumBlocks,
  const uint8* pPlainBlock, uint8* pCipherBlock);

/***************************************************************************//**
 * @details   AES-128 ECB(Electronic Code Block) 모드 복호화 수행
 *            암호문 : 128-bit 배수의 블럭
 *            평문 : 128-bit 배수의 블럭
 * @param     [in]  ddKeyId               AES ECB 모드 복호화시 사용할 Key ID
 *                                        KEY_<n>, RAM_KEY
 * @param     [in]  ulNumBlocks           입력에 사용되는 128-bit 암호문 블럭 개수
 * @param     [in]  pCipherBlock          암호문 블럭 버퍼 포인터
 * @param     [out] pPlainBlock           평문 블럭 버퍼 포인터
 * @return    Icus_ErrType                기능 수행 결과
 * @remark    입출력 데이터는 반드시 128-bit 의 배수여야 한다
 ******************************************************************************/
extern Icus_ErrType Icus_DecEcb(Icus_KeyIDType ddKeyId, uint32 ulNumBlocks,
  const uint8* pCipherBlock, uint8* pPlainBlock);

/***************************************************************************//**
 * @details   AES-128 CBC(Cipher Block Chaining) 모드 암호화 수행
 *            평문 : 128-bit 배수의 블럭
 *            암호문 : 128-bit 배수의 블럭
 * @param     [in]  ddKeyId               AES CBC 모드 암호화시 사용할 Key ID
 *                                        KEY_<n>, RAM_KEY
 * @param     [in]  ulNumBlocks           입력에 사용되는 128-bit 평문 블럭 개수
 * @param     [in]  pPlainBlock           평문 블럭 버퍼 포인터
 * @param     [in]  pIVBlock              Initialization Vector 버퍼(128-bit) 포인터
 * @param     [out] pCipherBlock          암호문 블럭 버퍼 포인터
 * @return    Icus_ErrType                기능 수행 결과
 * @remark    입출력 데이터는 반드시 128-bit 의 배수여야 한다
 ******************************************************************************/
extern Icus_ErrType Icus_EncCbc(Icus_KeyIDType ddKeyId, uint32 ulNumBlocks,
  const uint8* pPlainBlock, uint8* pCipherBlock, const uint8* pIVBlock);

/***************************************************************************//**
 * @details   AES-128 CBC(Cipher Block Chaining) 모드 복호화 수행
 *            암호문 : 128-bit 배수의 블럭
 *            평문 : 128-bit 배수의 블럭
 * @param     [in]  ddKeyId               AES CBC 모드 복호화시 사용할 Key ID
 *                                        KEY_<n>, RAM_KEY
 * @param     [in]  ulNumBlocks           입력에 사용되는 128-bit 암호문 블럭 개수
 * @param     [in]  pCipherBlock          암호문 블럭 버퍼 포인터
 * @param     [in]  pIVBlock              Initialization Vector 버퍼(128-bit) 포인터
 * @param     [out] pPlainBlock           평문 블럭 버퍼 포인터
 * @return    Icus_ErrType                기능 수행 결과
 * @remark    입출력 데이터는 반드시 128-bit 의 배수여야 한다
 ******************************************************************************/
extern Icus_ErrType Icus_DecCbc(Icus_KeyIDType ddKeyId, uint32 ulNumBlocks,
  const uint8* pCipherBlock, uint8* pPlainBlock, const uint8* pIVBlock);

/***************************************************************************//**
 * @details   AES-128 기반 Cipher-based Message Authentication Code 생성 수행
 * @param     [in]  ddKeyId               CMAC-AES 생성 수행시 사용할 Key ID
 *                                        KEY_<n>, RAM_KEY
 * @param     [in]  ulTotalMsgBitLength   메세지 데이터 전체 bit 단위 길이
 * @param     [in]  pMsgBlock             메세지 데이터 버퍼 포인터
 * @param     [in]  ulMacByteLength       원하는 결과 MAC 값의 byte 단위 길이
 * @param     [out] pMac                  MAC 버퍼 포인터
 * @return    Icus_ErrType                기능 수행 결과
 ******************************************************************************/
extern Icus_ErrType Icus_GenerateMac(Icus_KeyIDType ddKeyId,
  uint32 ulTotalMsgBitLength, const uint8* pMsgBlock,
  uint32 ulMacByteLength
, uint8* pMac);

/***************************************************************************//**
 * @details   AES-128 기반 Cipher-based Message Authentication Code 검증 수행
 * @param     [in]  ddKeyId       CMAC-AES 검증 수행시 사용할 Key ID
 *                                KEY_<n>, RAM_KEY
 * @param     [in]  ulTotalMsgBitLength   메세지 데이터 전체 bit 단위 길이
 * @param     [in]  pMsgBlock             메세지 데이터 버퍼 포인터
 * @param     [in]  ulMacBitLength        검증에 사용할 MAC 값의 bit 단위 길이
 * @param     [in]  pMac                  MAC 버퍼 포인터
 * @param     [out] pblResult             검증 결과 버퍼 포인터
 * @return    Icus_ErrType                기능 수행 결과
 ******************************************************************************/
extern Icus_ErrType Icus_VerifyMac(Icus_KeyIDType ddKeyId,
  uint32 ulTotalMsgBitLength, const uint8* pMsgBlock,
  uint32 ulMacBitLength
, const uint8* pMac, boolean* pblResult);

/***************************************************************************//**
 * @details   TRNG 로 PRNG 의 seed 를 공급한다
 *            TRNG 의 AIS31 표준에 따른 난수성을 보장하기 위해
 *            최초 CMD_INIT_RNG 수행시 상당한 수행시간(최대 2248/fPCLK + 120000 us) 이 걸린다
 * @return    Icus_ErrType                기능 수행 결과
 * @remark    reset 이후 CMD_RND 사용 전에 반드시 CMD_INIT_RNG 가 한 번 호출되었어야 한다
 ******************************************************************************/
extern Icus_ErrType Icus_InitRnd(void);

/***************************************************************************//**
 * @details   128-bit 입력 entropy 로 PRNG 의 seed 를 확장한다
 * @param     [in]  ulSeed                128-bit entropy
 * @return    Icus_ErrType                기능 수행 결과
 * @remark    reset 이후 CMD_EXTEND_SEED 사용 전에 반드시 CMD_INIT_RNG 가 한 번 호출되었어야 한다
 ******************************************************************************/
extern Icus_ErrType Icus_ExtendSeed(uint32 ulSeed);

/***************************************************************************//**
 * @details   128-bit 난수를 생성한다
 *            동시에 내부 PRNG 의 seed 를 업데이트한다
 * @param     [out] pRnd                  난수 버퍼 포인터
 * @return    Icus_ErrType                기능 수행 결과
 * @remark    reset 이후 CMD_RND 사용 전에 반드시 CMD_INIT_RNG 가 한 번 호출되었어야 한다
 ******************************************************************************/
extern Icus_ErrType Icus_Rnd(uint32* pRnd);


/***************************************************************************//**
 * @details   CMD_LOAD_KEY 호출시 input 인 M1, M2, M3 를 생성하기 위한 API
 *            입력 받은 ddKeyId, pKey, ddAuthId, pAuthKey, ulCounter, ucKeyFlag 기반으로
 *            pProtectedKey 맴버 중 M1, M2, M3 를 생성한다
 *            M1, M2, M3 계산과정에 필요한 K1, K2 는 Miyaguchi-Preneel compression algorithm 의
 *            KDF(Key Derivation Function) 로 내부에서 생성하여 적용
 *
 *            K1 = KDF(KEY[AuthID], KEY_UPDATE_ENC_C)
 *            K2 = KDF(KEY[AuthID], KEY_UPDATE_MAC_C)
 *
 *            M1(128 bits) = UID(120 bit) + ID(4 bit) + AuthID(4 bit)
 *            M2(256 bits) = ENC[CBC, K1, IV = 0] (Counter(28 bit) + KEY_FLAG(6 bit) + "0 ... 0"(94 bit) + KEY_ID(128 bit))
 *            M3(128 bits) = CMAC[K2](M1 | M2)
 *
 *            등록/업데이트 대상 Key ID 와 AuthKey ID 관계
 *                Key ID          AuthKey ID
 *            MASTER_ECU_KEY : MASTER_ECU_KEY
 *            BOOT_MAC_KEY   : MASTER_ECU_KEY, BOOT_MAC_KEY
 *            BOOT_MAC       : MASTER_ECU_KEY, BOOT_MAC_KEY
 *            KEY_<n>        : MASTER_ECU_KEY, KEY_<n> (*2)
 *            RAM_KEY        : SECRET_KEY (*1), KEY_<n>
 *            Note 1. Only used when registering M1 to M3 that are acquired by the CMD_EXPORT_RAM_KEY command
 *            Note 2. Only used when ID = AuthID
 *
 *            Counter 는 28 bit 길이의 값으로 replay attack 을 방지하고자 사용된다
 *            Key 등록시 counter 값은 ICUS 내부에 저장되며 Key 업데이트 시 이전에 저장된 값보다 반드시 큰 값이 제공되어야 한다
 *            미등록된 Key 의 counter 는 0 이기 때문에 최초 Key 등록시에는 반드시 1 보다 큰 값이 제공되야 한다
 *
 *            KeyFlag 는 등록/업데이트되는 Key 의 특성을 설정
 *            Icus_KeyFlagType 항목 설명을 참조한다
 *
 * @param     [in]  ddKeyId               등록/업데이트 대상 Key ID
 *                                        MASTER_ECU_KEY, BOOT_MAC_KEY,
 *                                        BOOT_MAC, KEY_<n>, RAM_KEY
 * @param     [in]  pKey                  등록/업데이트 대상 버퍼 포인터
 * @param     [in]  ddAuthId              등록/업데이트 대상 Key 의 AuthKey ID
 * @param     [in]  pAuthKey              AuthKey 버퍼 포인터
 * @param     [in]  ulCounter             등록/업데이트 대상 Key 의 신규 counter 값
 * @param     [in]  ucKeyFlag             등록/업데이트 대상 Key 의 flag 특성 정보
 * @param     [out]  pProtectedKey        M1, M2, M3 : 입력된 정보 기반으로 생성된 message
 *                                        M4, M5 : 미사용
 * @return    Icus_ErrType                기능 수행 결과
 ******************************************************************************/
extern Icus_ErrType Icus_GenerateProtectedKey(Icus_KeyIDType ddKeyId,
  const uint8* pKey, Icus_KeyIDType ddAuthId, const uint8* pAuthKey,
  uint32 ulCounter, uint8 ucKeyFlag, Icus_ProtectedKey* pProtectedKey);

/***************************************************************************//**
 * @details   CMD_LOAD_KEY 호출후 output 인 M4, M5 를 검증하기 위한 API
 *            입력 받은 ddKeyId, pKey, ddAuthId, ulCounter, ucKeyFlag 기반으로
 *            M4, M5 를 생성하여 입력받은 pProtectedKey 의 M4, M5 를 검증한다.
 *            M4, M5 계산과정에 필요한 K3, K4 는 Miyaguchi-Preneel compression algorithm 의
 *            KDF(Key Derivation Function) 로 내부에서 생성하여 적용
 *
 *            K3 = KDF(KEY[ID], KEY_UPDATE_ENC_C)
 *            K4 = KDF(KEY[ID], KEY_UPDATE_MAC_C)
 *
 *            M4(256 bits) = UID(120 bit) + ID(4 bit) + AuthID(4 bit) + ENC[ECB, K3](Counter(28 bit) + "1" + "0 ... 0"(99 bit))
 *            M5(128 bits) = CMAC[K4](M4)
 *
 * @param     [in]  ddKeyId               검증 대상 Key ID
 * @param     [in]  pKey                  검증 대상 버퍼 포인터
 * @param     [in]  ddAuthId              검증 대상 Key 의 AuthKey ID
 * @param     [in]  ulCounter             검증 대상 Key 의 등록된 counter 값
 * @param     [in]  pProtectedKey         M1, M2, M3 : 미사용
 *                                        M4, M5 : 검증에 사용
 * @param     [out]  pResult              입력받은 M4, M5 가
 *                                        valid 할 경우 ICUS_TRUE,
 *                                        invalid 할 경우 ICUS_FALSE 리턴
 * @return    Icus_ErrType                기능 수행 결과
 ******************************************************************************/
extern Icus_ErrType Icus_VerifyProtectedKey(Icus_KeyIDType ddKeyId,
  const uint8* pKey, Icus_KeyIDType ddAuthId, uint32 ulCounter,
  const Icus_ProtectedKey* pProtectedKey, boolean* pResult);

/***************************************************************************//**
 * @details   유도된 M1, M2, M3 로 ICUS 내부 Key 를 등록/업데이트 한다
              pProtectedKey 의 M4, M5 는 Key 등록 절차를 검증(Icus_VerifyProtectedKey)하는데 쓰인다
 * @param     [in]  ddKeyId               등록/업데이트 대상 Key ID
 *                                        SECRET_KEY, MASTER_ECU_KEY, BOOT_MAC_KEY,
 *                                        BOOT_MAC, KEY_<n>, RAM_KEY
 * @param     [inout]  pProtectedKey      M1, M2, M3 는 input, M4, M5 는 output
 * @return    Icus_ErrType                기능 수행 결과
 ******************************************************************************/
extern Icus_ErrType Icus_LoadKey(Icus_KeyIDType ddKeyId,
  Icus_ProtectedKey* pProtectedKey);

/***************************************************************************//**
 * @details   평문 Key 값을 ICU_RAM_KEY 에 등록한다
 * @param     [in]  pInput                평문 형태의 16 바이트 버퍼 포인터
 * @return    Icus_ErrType                기능 수행 결과
 ******************************************************************************/
extern Icus_ErrType Icus_LoadPlainKey(const uint8* pInput);

/***************************************************************************//**
 * @details   CMD_LOAD_PLAIN_KEY 로 RAM_KEY 에 등록한 데이터를
 *            M1, M2, M3, M4, M5 형태로 추출한다
 * @param     [out] pProtectedKey         추출된 M1, M2, M3, M4, M5 를 저장할 버퍼 포인터
 * @return    Icus_ErrType                기능 수행 결과
 * @remark    RAM_KEY slot 이 비어 있거나 RAM_KEY 를 CMD_LOAD_KEY 로 등록한 경우 에러가 발생한다
 ******************************************************************************/
extern Icus_ErrType Icus_ExportRamKey(Icus_ProtectedKey* pProtectedKey);

/***************************************************************************//**
 * @details   Secure Boot 기능을 수행한다
 *            BOOT_MAC_KEY, BOOT_MAC 이 등록된 상태에서는 pAddress 주소부터
 *            ulByteSize 블럭의 MAC 값을 계산하여 BOOT_MAC 값과 일치하는지 비교한다
 *            BOOT_MAC slot 이 비어 있는 경우 생성된 MAC 값을 BOOT_MAC slot 에 등록한다
 * @param     [in]  ulByteSize            Secure Boot 대상 byte 크기(0 보다 큰 값)
 * @param     [in]  pAddress              Secure Boot 대상 시작 주소
 * @return    Icus_ErrType                기능 수행 결과
 * @remark    Reset 이후 단 한번만 호출 가능하다
 ******************************************************************************/
extern Icus_ErrType Icus_SecureBoot(const uint32 ulByteSize,
  const uint8* pAddress);

/***************************************************************************//**
 * @details   ICUS 내부 상태 값 중 BOOT_FINISHED flag 를 1 로, BOOT_OK flag 를 0 으로 셋팅한다
 * @return    Icus_ErrType                기능 수행 결과
 * @remark    ICUS 내부 상태가 SECURE_BOOT = 1 & BOOT_FINISHED = 0 & BOOT_OK = 1 인 조건을 만족해야 한다
 ******************************************************************************/
extern Icus_ErrType Icus_BootFailure(void);

/***************************************************************************//**
 * @details   ICUS 내부 상태 값 중 BOOT_FINISHED flag 를 1 로 셋팅한다
 * @return    Icus_ErrType                기능 수행 결과
 * @remark    ICUS 내부 상태가 SECURE_BOOT = 1 & BOOT_FINISHED = 0 & BOOT_OK = 1 인 조건을 만족해야 한다
 ******************************************************************************/
extern Icus_ErrType Icus_BootOk(void);

/***************************************************************************//**
 * @details   ICUS 내부 상태 값인 SREG 값을 얻는다
 * @param     [out] pStatus               ICUS 내부 상태값 버퍼 포인터
 * @return    Icus_ErrType                기능 수행 결과
 ******************************************************************************/
extern Icus_ErrType Icus_GetStatus(Icus_StatusType* pStatus);

/***************************************************************************//**
 * @details   Device 의 UID(120 bit), SREG(8 bit) 를 추출한다
 * @param     [out] pUID                  UID + SREG 버퍼(128 bits) 포인터
 * @return    Icus_ErrType                기능 수행 결과
 ******************************************************************************/
extern Icus_ErrType Icus_GetUID(uint8* pUID);

/***************************************************************************//**
 * @details   현재 진행중인 command 를 취소한다
 * @return    Icus_ErrType                기능 수행 결과
 ******************************************************************************/
extern Icus_ErrType Icus_Cancel(void);

/***************************************************************************//**
 * @details   ICUS 에 저장된 모든 NVM Key, RAM_KEY 를 지운다
 * @param     [in]  pMasterKey            MASTER_ECU_KEY 로 등록된 Key 의 raw key 값 버퍼 포인터
 * @return    Icus_ErrType                기능 수행 결과
 * @remark    MASTER_ECU_KEY 로 ICUS 에 사전에 등록된 Key 값과 동일한 pMasterKey 값이
              인자로 입력되어야 Icus_Debug 수행을 성공한다
 ******************************************************************************/
extern Icus_ErrType Icus_Debug(const uint8* pMasterKey);

#endif

#endif /* ICUS_DRIVER_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
