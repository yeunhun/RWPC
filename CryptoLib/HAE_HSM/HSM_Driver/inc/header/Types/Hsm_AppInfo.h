/*!
  @file Hsm_AppInfo.h
  @brief HSM application type definition header file
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef HSM_APPINFO_H_
#define HSM_APPINFO_H_

#include "Hsm_Types.h"

#define HSM_MAX_FTD_TARGET_SEG_NUM (4u)
#define HSM_MAX_FTD_TARGET_NUM (6u)
#define HSM_FTD_STOP_PW_BYTE_LEN (8u)
#define HSM_FTD_STOP_PW_WORD_LEN (HSM_FTD_STOP_PW_BYTE_LEN / 4u)
#define HSM_CERTIFICATE_BYTE_LEN (600u)
#define HSM_SIGNATURE_BYTE_LEN (256u)

typedef enum
{
	FTD_TARGET_INIT = 0u,
	FTD_TARGET_0 = 1u,
	FTD_TARGET_1 = 2u,
	FTD_TARGET_2 = 3u,
	FTD_TARGET_3 = 4u,
	FTD_TARGET_4 = 5u,
	FTD_TARGET_5 = 6u,
} FTD_TARGET_NUM_t;

typedef enum
{ //HSM-Driver Sync Need
	HSM_FTD_INITIALIZING = 0,                           /*!< Initializing */
	HSM_FTD_FAIL = 1,                                   /*!< Operation Fail */
	HSM_FTD_DISABLE = 2,                                /*!< Disable */
	HSM_FTD_STOP = 3,                                   /*!< Stop */
	HSM_FTD_ACTIVATED_WAIT_RUN = 4,                     /*!< Waiting for integrity check */
	HSM_FTD_ACTIVATED_TEMP_STOP = 5,                    /*!< User temporary stop */
	HSM_FTD_ACTIVATED_RUNNING = 6,                      /*!< Integrity check in progress */
	HSM_FTD_NOT_PERFORMED = 12,                         /*!< FTD Not Set (Initial Value) */
	HSM_FTD_STATE_ENUM_SET_UINT32 = 0x7FFFFFFF,
} HSM_FTD_RUN_STATE_t;

typedef enum
{ //HSM-Password verification
	HSM_PASSWORD_VERIFY_DISABLE = 0,
	HSM_PASSWORD_VERIFY_ENABLE = 1,
	HSM_PASSWORD_VERIFY_INVALID_LENGTH = 2,
	HSM_PASSWORD_VERIFY_FAIL = 3,
	HSM_PASSWORD_VERIFY_INVALID_PASSWORD = 4,
	HSM_PASSWORD_VERIFY_NOT_SUPPORTED = 5,
	HSM_PASSWORD_VERIFY_SUCCESS = 6,
	HSM_PASSWORD_STATE_ENUM_SET_UINT32 = 0x7FFFFFFF,
} HSM_PASSWORD_VERIFY_STATE_t; //hsm password verify state

typedef enum
{ //HSM-Driver Sync Need
	HSM_DEBUG_PROTECTION_DISABLE = 0,                   /*!< SECURE DEBUG Disable */
	HSM_DEBUG_PROTECTION_ENABLE = 1,                    /*!< SECURE DEBUG Enable */
	HSM_DEBUG_PROTECTION_TEMP_STOP = 2,                 /*!< SECURE DEBUG Pause */
	HSM_DEBUG_PROTECTION_UNLOCK_FAIL = 3,               /*!< SECURE DEBUG Unlock Fail */
	HSM_DEBUG_PROTECTION_UNLOCK_FAIL_PASSWORD = 4,      /*!< SECURE DEBUG Password verification Fail */
	HSM_DEBUG_PROTECTION_NOT_SUPPORTED = 5,             /*!< SEUCRE DEBUG Unlock function not available */
	HSM_DEBUG_STATE_ENUM_SET_UINT32 = 0x7FFFFFFF,
} HSM_SECUREDEBUG_STATE_t; //hsm secure debug unlock state

typedef enum
{ //HSM-Driver Sync Need
	HSM_SECUREBOOT_INIT = 0,                            /*!< Initialization */
	HSM_SECUREBOOT_DISABLE = 1,                         /*!< Disable */
	HSM_SECUREBOOT_ENABLE = 2,                          /*!< Enable */
	HSM_SECUREBOOT_SUCCESS = 3,                         /*!< Bootloader integrity verification success */
	HSM_SECUREBOOT_HEADER_ERR = 4,                      /*!< Table header, footer error */
	HSM_SECUREBOOT_INVALID_CMAC = 5,                    /*!< Bootloader integrity verification fail */
	HSM_SECUREBOOT_CMAC_GEN_FAIL = 6,                   /*!< MAC generation failure for integrity verification */
	HSM_SECUREBOOT_HASH_GEN_FAIL = 7,                   /*!< Hash generation failed when verifying the firmware signature */
	HSM_SECUREBOOT_DECRYPT_FAIL = 8,                    /*!< Encrypted table decryption failed */
	HSM_SECUREBOOT_XOR_SUM_FAIL = 9,                    /*!< XOR Value Verification fail */
	HSM_SECUREBOOT_SIGN_VERIFY_FAIL = 10,               /*!< Signature verification fail */
	HSM_SECUREBOOT_WR_INFO_FAIL = 11,                   /*!< Table write fail */
	HSM_SECUREBOOT_NOT_PERFORMED = 12,                  /*!< Secure Boot not working */
	HSM_SECUREBOOT_STATE_ENUM_SET_UINT32 = 0x7FFFFFFF,
} HSM_SECUREBOOT_STATE_t;

#if 0 	// Not used
typedef enum
{ //HSM-Driver Sync Need
	PFLASH_PROTECTION_DISABLE = 0,
	PFLASH_PROTECTION_ENABLE = 1,
	PFLASH_PROTECTION_UNLOCK_OK = 2,
	PFLASH_PROTECTION_UNLOCK_FAIL = 3,
	PFLASH_PROTECTION_UNLOCK_FAIL_PASSWORD = 4,
	PFLASH_PROTECTION_UNLOCK_FAIL_PASSWORD_LENGTH = 5,
	PFLASH_PROTECTION_ENUM_SET_UINT32 = 0x7FFFFFFF,
} HSM_PFLASH_PROTECTION_STATE_t;

typedef enum
{ //HSM-Driver Sync Need
	PFLASH_WRITE_ERASE_PERMANENT_UNLOCK = 0,
	PFLASH_WRITE_ERASE_TEMP_UNLOCK = 1,
	PFLASH_WRITE_ERASE_LOCK = 2,
	PFLASH_WRITE_ERASE_STATE_ENUM_SET_UINT32 = 0x7FFFFFFF,
} HSM_PFLASH_WRITE_LOCK_STATE_t;
#endif

#if 0 	// Not used
typedef enum
{
	SECURITY_CONFIRM_INIT = 0,
	SECURE_DEBUG_NOT_ACTIVATED = 1,
	SECURE_BOOT_TABLE_NOT_EXIST = 2,
	FW_TAMPER_DETECTION_TABLE_NOT_EXIST = 3,
	HSM_PFLASH_OTP_ACTIVATION_FAIL = 4,
	FLASH_WRITE_OPERATION_FAIL = 5,
	SECURITY_CONFIRM_SUCCESS = 6,
	SECURITY_CONFIRM_STATE_ENUM_SET_UINT32 = 0x7FFFFFFF,
} HSM_SECURITY_CONFIRM_STATE_t;
#endif

typedef enum
{
	HSM_CONFIG_LOCK_DISABLE = 0,
	HSM_CONFIG_LOCK_ENABLE = 1,
	HSM_CONFIG_LOCK_ENUM_SET_UINT32 = 0x7FFFFFFF,
} HSM_CONFIG_LOCK_STATE_t;

typedef struct
{
    UINT32 signKeyNum;                                  /*!< FoD Cert Signature Verification Public Key Index */
    UINT8 sign[HSM_SIGNATURE_BYTE_LEN];                 /*!< FoD Cert ECC Signature */
} HSM_SIGN_t;

typedef struct
{ //must be sync with hsm-host
	UINT32 startAddr;                                   /*!< The starting address of the segment comprising the target */
	UINT32 size;                                        /*!< The size of the segments that make up the target */
} HSM_FTD_SEGMENT_t;

typedef struct
{ //must be sync with hsm-host
	UINT32 targetIndex;                                 /*!< Target number to set, target number starts from 0 */
	UINT16 signKeyNum;                                  /*!< Public key number for signature verification (When using aSIMS, enter 1 / When using FST, enter the usage number) */
	UINT16 cmacKeyNum;                                  /*!< Symmetric key number to generate target MAC value (Use among Tier PSK #101~#105) */
	UINT32 signAddr;                                    /*!< The target's signature address */
	UINT32 segmentNum;                                  /*!< Number of segments constituting the target */
	HSM_FTD_SEGMENT_t segInfo[HSM_MAX_FTD_TARGET_SEG_NUM];  /*!< Segments information */
} HSM_FTD_TARGET_t;

typedef struct
{ //must be sync with hsm-host
	UINT32 totalTargetNum;                              /*!< Total number of targets set in FTD */
	UINT32 stopPassword[HSM_FTD_STOP_PW_WORD_LEN];      /*!< Password to use when FTD is paused (8-Byte) */
	HSM_FTD_TARGET_t target[HSM_MAX_FTD_TARGET_NUM];    /*!< Each target setting */
} HSM_FTD_CONFIG_t;

typedef struct
{
	UINT32 totalTargetNum;                              /*!< Total number of targets set in FTD */
	UINT32 failCountHistory[HSM_MAX_FTD_TARGET_NUM];    /*!< Failure log by target. */
} HSM_FTD_LOG_t;

typedef struct
{
	HSM_FTD_RUN_STATE_t status;                         /*!< Operation status */
	UINT32 totalTargetNum;                              /*!< Total number of targets set in FTD */
	UINT32 failCountAfterPwOn[HSM_MAX_FTD_TARGET_NUM];  /*!< Number of integrity check failures per target since power was applied. Not log */
	UINT32 okCountAfterPwOn[HSM_MAX_FTD_TARGET_NUM];    /*!< Number of integrity check success per target since power was applied. Not log */
} HSM_FTD_STATE_t;

typedef struct
{ //must be sync with hsm-host
	UINT32 pubKeyNum;
	UINT8 cert[HSM_CERTIFICATE_BYTE_LEN];
} HSM_CSAC_CERT_VERIFY_UPDATE_INPUT_t;

typedef struct
{ //must be sync with hsm-host
	UINT32 sfAddr;
	UINT32 sfLength;
} HSM_SF_PUSH_DATA_INPUT_t;

typedef struct
{ //must be sync with hsm-host
	UINT32 pubKeyNum;
	UINT8 sigBuff[HSM_SIGNATURE_BYTE_LEN];
} HSM_SF_VERIFY_DATA_INPUT_t;

typedef struct
{
    HSM_SECUREBOOT_STATE_t secureBootState;     /*!< Secure Boot Status information */
    HSM_FTD_RUN_STATE_t fwTamperDetectionState; /*!< Fw Tamper Detection Status information */
    HSM_SECUREDEBUG_STATE_t secureDebugState;   /*!< Secure Debug Status information */
} HSM_SECURITY_INFO_t;

typedef struct
{
	/*오토에버 고유문자*/
	UINT16 vendorID;                            /*!< HAE Unique characters */
	/*오토에버 HSM 모듈 ID*/
	UINT16 moduleID;                            /*!< HAE HSM module ID */
	/*오토에버 HSM 인스턴스 ID (Reserved)*/
	UINT8 instanceID;                           /*!< HAE HSM instance ID */
	/* HSM 프레임워크 펌웨어 버전*/
	UINT8 hsmMajorVersion;                      /*!< HSM Framework Firmware version (Major) */
	UINT8 hsmMinorVersion;                      /*!< HSM Framework Firmware version (Minor) */
	UINT8 hsmPatchVersion;                      /*!< HSM Framework Firmware version (Patch) */
	/* 드라이버 버전*/
	UINT8 driverMajorVersion;                   /*!< HSM Driver version (Major) */
	UINT8 driverMinorVersion;                   /*!< HSM Driver version (Minor) */
	UINT8 driverPatchVersion;                   /*!< HSM Driver version (Patch) */
} HSM_VERSION_CTX_t;

#endif /* HSM_APPINFO_H_ */
