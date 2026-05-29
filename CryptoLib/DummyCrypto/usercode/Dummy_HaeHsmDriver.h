/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dummy_HaeHsmDriver.h                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Dummy HAE HSM Driver library                                  **
**                                                                            **
**  PURPOSE   : Header file for dummy code                                    **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0.0   18-Jul-2019   Sinil        Initial version                       **
** 1.0.1.0   03-Nov-2020   JaeHyun      Sync with HSM 2.3.0                   **
*******************************************************************************/

#ifndef DUMMY_HAEHSMDRIVER_H
#define DUMMY_HAEHSMDRIVER_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
/* Hsm_Types.h */
#ifndef UINT64
/** 64 bit unsigned integer. */
#define UINT64 unsigned long long /*           0 .. 18446744073709551615, */
#endif

#ifndef UINT32
/** 32 bit unsigned integer. */
#define UINT32 unsigned long /*           0 .. 4294967295, */
#endif

#ifndef UINT16
/** 16 bit unsigned integer. */
#define UINT16 unsigned short /*           0 .. 65535,*/
#endif

#ifndef UINT8
/** 8 bit unsigned integer. */
#define UINT8 unsigned char /*           0 .. 255, 0xff             */
#endif

#ifndef SINT8
#define SINT8 signed char /*        -128 .. +127(7F) */
#endif

#ifndef SINT16
#define SINT16 signed short /*      -32768 .. +32767 (0x7FFF)*/
#endif

#ifndef SINT32
#define SINT32 signed long /* -2147483648 .. +2147483647(0x7FFF FFFF)     */
#endif

#ifndef BOOL
#define BOOL unsigned char /* -2147483648 .. +2147483647(0x7FFF FFFF)     */
#endif

#ifndef VUINT32
#define VUINT32 volatile unsigned long // -2147483648 .. +2147483647(0x7FFF FFFF)
#endif

#ifndef VUINT8
#define VUINT8 volatile unsigned char //0 .. 255, 0xff
#endif

#ifndef VUINT16
#define VUINT16 volatile unsigned short //0 .. 65535,
#endif

#ifndef ARR_SIZE
#define ARR_SIZE
#define ARR_SIZE_1024 (1024u)
#define ARR_SIZE_32 (32u)
#define ARR_SIZE_16 (16u)
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef FALSE
#define FALSE 0U
#endif

#ifndef TRUE
#define TRUE 1U
#endif

/* All errors of API services */
#if defined(STATUSTYPEDEFINED)
/* another AUTOSAR component has already defined the status type */
#else
#define STATUSTYPEDEFINED
#define Std_ReturnType					UINT8
#define E_OK 							((UINT8)0x00)
#define E_NOT_OK 						((UINT8)0x01)
#endif
#define HSM_E_BUSY  					((UINT8)0x02)
#define HSM_E_WAIT  					((UINT8)0x03)
#define HSM_E_WRONG_SEQ  				((UINT8)0x04)
#define HSM_E_NOT_SUPPORTED  			((UINT8)0x05)
#define HSM_E_LENGTH_NOT_VALID  		((UINT8)0x06)
#define HSM_E_VALUE_NOT_VALID			((UINT8)0x07)
#define HSM_E_KEY_NOT_VALID				((UINT8)0x08)


/* Hsm_AppInfo.h */
#define HSM_MAX_FTD_TARGET_SEG_NUM (4u)
#define HSM_MAX_FTD_TARGET_NUM (6u)
#define HSM_FTD_STOP_PW_BYTE_LEN (8u)
#define HSM_FTD_STOP_PW_WORD_LEN (HSM_FTD_STOP_PW_BYTE_LEN / 4u)
#define HSM_CERTIFICATE_BYTE_LEN (600u)
#define HSM_SIGNATURE_BYTE_LEN (256u)


/* Hsm_KeyTypes.h */
#define AES_BYTE_SIZE   16
#define RSA_BYTE_SIZE   256
#define ECC_BYTE_SIZE   32


/* CryptoService_Def.h */
#define HSM_AES128_KEY_LEN  (16) //byte -- > 128bit
#define HSM_AES128_CMAC_LEN (16) //byte -- > 128bit

#define NIST_CURVE_P256r1 256U
#define ECC_CURVE_TYPE NIST_CURVE_P256r1

/** Size of WORD and BYTE of Ecc curve */
#if (ECC_CURVE_TYPE == NIST_CURVE_P256r1)
#define ECC_WORDS_SIZE 8U
#define ECC_BYTES_SIZE 32U
#endif

#define SHA160_DIGEST_SIZE 20U
#define SHA256_DIGEST_SIZE 32U

#define HAC_RSA_BIT_SIZE 2048U
#define HAC_RSA_BYTES_SIZE (HAC_RSA_BIT_SIZE / 8U)


/* SecurityApp_ProactiveDataProtection.h */
#define HSM_MAX_PDP_SEG_NUM   4


/* SecurityApp_FeatureOnDemand.h */
#define FOD_NUMBER_OF_SET (10u)

#define FOD_VERSION_LEN 1
#define FOD_CERT_SN_LEN 4
#define FOD_CERT_TAG_LEN 1
#define FOD_CERT_VIN_LEN 17
#define FOD_CERT_EID_LEN 2
#define FOD_CERT_FV_LEN 4
#define FOD_CERT_SP_LEN 16
#define FOD_CERT_ISSUER_LEN 1
#define FOD_CERT_ORDERID_LEN 4
#define FOD_CERT_ISSUEDDATE_LEN 8
#define FOD_CERT_EFFECTIVEDATE_LEN 8
#define FOD_CERT_EXPIREDDATE_LEN 8
#define FOD_CERT_RESERVED_LEN 22

/*
* FoDCert Size = 96 Byte
*/
typedef struct {
    UINT8 version[FOD_VERSION_LEN];
	UINT8 serialNumber[FOD_CERT_SN_LEN];
	UINT8 tag[FOD_CERT_TAG_LEN];
	UINT8 vin[FOD_CERT_VIN_LEN];
	UINT8 eId[FOD_CERT_EID_LEN];
	UINT8 fv[FOD_CERT_FV_LEN];
	UINT8 sP[FOD_CERT_SP_LEN];
	UINT8 issuer[FOD_CERT_ISSUER_LEN];
	UINT8 orderId[FOD_CERT_ORDERID_LEN];
	UINT8 issuedDate[FOD_CERT_ISSUEDDATE_LEN];
	UINT8 effectiveDate[FOD_CERT_EFFECTIVEDATE_LEN];
	UINT8 expiredDate[FOD_CERT_EXPIREDDATE_LEN];
    UINT8 reserved[FOD_CERT_RESERVED_LEN];
} FoDCert;

typedef enum
{ //HSM-Driver Sync Need
    HSM_FOD_INIT = 0,
    HSM_FOD_READY,
    HSM_FOD_NOT_PERFORMED,
    HSM_FOD_SUCCESS,
    HSM_FOD_HEADER_ERR,
    HSM_FOD_CMAC_GEN_FAIL,
    HSM_FOD_CMAC_FAIL,
    HSM_FOD_DECRYPT_FAIL,
    HSM_FOD_XOR_SUM_FAIL,
    HSM_FOD_SIGN_FAIL,
    HSM_FOD_WR_INFO_FAIL,
    HSM_FOD_LOAD_INFO_FAIL,
    HSM_FOD_CERT_NOT_FOUND,
    HSM_FOD_FULLED,
	HSM_FOD_STATE_ENUM_SET_UINT32 = 0x7FFFFFFF,
} HSM_FOD_ERR_STATE_t;

/*******************************************************************************
**                               Enumerations                                 **
*******************************************************************************/
/* Hsm_Types.h */
typedef enum
{
  HSM_VERIFY_SUCCESS = 0,
  HSM_VERIFY_FAILURE
} HSM_VERIFY_RT;

//driver only err code
//you can add items freely
typedef enum
{
  HSM_ERR_NOERROR = 0,
  HSM_ERR_TIMEOUT = 0xA1,
  HSM_ERR_INVALID_KEY_NUM,
  HSM_ERR_INVALID_INPUT_LENGTH,
  HSM_ERR_INVALID_VALUE,
  HSM_ERR_INVALID_JOBID,
  HSM_ERR_WRONG_SEQ,
  HSM_ERR_NO_FUNCTION,
  HSM_ERR_FAIL,
  HSM_ERR_UNKOWN = 0xAF,

  /* Initialize Error Code */
  HSM_ERR_INIT_FAIL_SET_HSM_INIT_DONE = 0x0A00,
  HSM_ERR_INIT_FAIL_GET_INITIALIZE_VALUE,
  HSM_ERR_INIT_HOSTBUFFER_CHECK_ERROR,
  HSM_ERR_INIT_HSMBUFFER_CHECK_ERROR, 
  HSM_ERR_INIT_SEND_INIT_MSG_TIMEOUT,
  HSM_ERR_INIT_GET_WRONG_RESP,

  /* Spinlock Error Code */
  HSM_ERR_SPINLOCK_FAILED_GET_GLOBAL_ID = 0x0B00,
  HSM_ERR_SPINLOCK_FAILED_GET_API_ID = 0x0B01,
  HSM_ERR_SPINLOCK_INVALID_SPINLOCK_ID = 0x0B02,
  HSM_ERR_SPINLOCK_HOSTBUFF_NOT_READ_YET = 0x0B03,
  HSM_ERR_SPINLOCK_TIMEOUT = 0x0B04,

  /* Tasklock Error Code */
  HSM_ERR_TASKLOCK_FAILED_GET_TASKLOCK = 0x0C00,
  HSM_ERR_TASKLOCK_INVALID_TASK_PRIORITY = 0x0C01,

  /* Read Buffer Error Code */
  HSM_ERR_READ_BUFFER_INVALID_POINTER = 0x0D00,
} HSM_ERROR_CODE;


/* Hsm_AppInfo.h */
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
	HSM_FTD_INITIALIZING = 0,
	HSM_FTD_FAIL = 1,
	HSM_FTD_DISABLE = 2,
	HSM_FTD_STOP = 3,
	HSM_FTD_ACTIVATED_WAIT_RUN = 4,
	HSM_FTD_ACTIVATED_TEMP_STOP = 5,
	HSM_FTD_ACTIVATED_RUNNING = 6,
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
	HSM_DEBUG_PROTECTION_DISABLE = 0,
	HSM_DEBUG_PROTECTION_ENABLE = 1,
	HSM_DEBUG_PROTECTION_TEMP_STOP = 2,
	HSM_DEBUG_PROTECTION_UNLOCK_FAIL = 3,
	HSM_DEBUG_PROTECTION_UNLOCK_FAIL_PASSWORD = 4,
	HSM_DEBUG_PROTECTION_UNLOCK_FAIL_NOT_SUPPORTED = 5,
	HSM_DEBUG_STATE_ENUM_SET_UINT32 = 0x7FFFFFFF,
} HSM_SECUREDEBUG_STATE_t; //hsm secure debug unlock state

typedef enum
{ //HSM-Driver Sync Need
	HSM_SECUREBOOT_INIT = 0,
	HSM_SECUREBOOT_DISABLE = 1,
	HSM_SECUREBOOT_ENABLE = 2,
	HSM_SECUREBOOT_SUCCESS = 3,
	HSM_SECUREBOOT_HEADER_ERR = 4,
	HSM_SECUREBOOT_INVALID_CMAC = 5,
	HSM_SECUREBOOT_CMAC_GEN_FAIL = 6,
	HSM_SECUREBOOT_HASH_GEN_FAIL = 7,
	HSM_SECUREBOOT_DECRYPT_FAIL = 8,
	HSM_SECUREBOOT_XOR_SUM_FAIL = 9,
	HSM_SECUREBOOT_SIGN_VERIFY_FAIL = 10,
	HSM_SECUREBOOT_WR_INFO_FAIL = 11,
	HSM_SECUREBOOT_NOT_PERFORMED = 12,
	HSM_SECUREBOOT_STATE_ENUM_SET_UINT32 = 0x7FFFFFFF,
} HSM_SECUREBOOT_STATE_t;

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

/* Hsm_KeyTypes.h */
typedef enum
{
  AES_KEY = 0u,
  RSA_KEY,
  ECC_KEY
} KEY_TYPE;


/* CryptoService_Aes.h */
typedef enum
{
  HSM_AES_ECB_MODE,
  HSM_AES_CBC_MODE,
  HSM_AES_CTR_MODE,
  HSM_AES_OFB_MODE
} AES_MODE;

/*******************************************************************************
**                                Data Types                                  **
*******************************************************************************/
/* Hsm_Types.h */
/** Type for callback function */
typedef void (*HSM_CallbackFunc)(void);

/*******************************************************************************
**                                Structures                                  **
*******************************************************************************/
/* Hsm_Types.h */
typedef struct
{
  UINT16 jobId;
  UINT16 taskPriority;
  UINT16 mode; // only used in AES Crypto Service
} HSMAPI_CTX_t;

typedef enum
{
  SYNC_MODE = 1,
  ASYNC_MODE = 2
} COM_MODE;

typedef struct
{
  UINT16 cmd;
  UINT16 taskPriority;
  UINT16 jobId;
  COM_MODE synchMode;
  UINT8 *sendData;
  UINT32 sendDataLength;
  UINT8 *recvData;
  UINT32 recvDataLength;
} HSM_REQ_INFO_t;

/* Hsm_AppInfo.h */

typedef struct
{
    UINT32 signKeyNum;
    UINT8 sign[HSM_SIGNATURE_BYTE_LEN];
} HSM_SIGN_t;

typedef struct
{ //must be sync with hsm-host
  UINT32 startAddr;
  UINT32 size;
} HSM_FTD_SEGMENT_t;

typedef struct
{ //must be sync with hsm-host
  UINT32 targetIndex;
  UINT16 signKeyNum;
  UINT16 cmacKeyNum;
  UINT32 signAddr;
  UINT32 segmentNum;
  HSM_FTD_SEGMENT_t segInfo[HSM_MAX_FTD_TARGET_SEG_NUM];
} HSM_FTD_TARGET_t;

typedef struct
{ //must be sync with hsm-host
  UINT32 totalTargetNum;
  UINT32 stopPassword[HSM_FTD_STOP_PW_WORD_LEN];
  HSM_FTD_TARGET_t target[HSM_MAX_FTD_TARGET_NUM];
} HSM_FTD_CONFIG_t;

typedef struct
{
  UINT32 totalTargetNum;
  UINT32 failCountHistory[HSM_MAX_FTD_TARGET_NUM];
} HSM_FTD_LOG_t;

typedef struct
{
  HSM_FTD_RUN_STATE_t status;
  UINT32 totalTargetNum;
  UINT32 failCountAfterPwOn[HSM_MAX_FTD_TARGET_NUM];
  UINT32 okCountAfterPwOn[HSM_MAX_FTD_TARGET_NUM];
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
  HSM_SECUREBOOT_STATE_t secureBootState;
  HSM_FTD_RUN_STATE_t fwTamperDetectionState;
  HSM_SECUREDEBUG_STATE_t secureDebugState;
} HSM_SECURITY_INFO_t;

typedef struct
{
  /*오토에버 고유문자*/
  UINT16 vendorID;
  /*오토에버 HSM 모듈 ID*/
  UINT16 moduleID;
  /*오토에버 HSM 인스턴스 ID (Reserved)*/
  UINT8 instanceID;
  /* HSM 프레임워크 펌웨어 버전*/
  UINT8 hsmMajorVersion;
  UINT8 hsmMinorVersion;
  UINT8 hsmPatchVersion;
  /* 드라이버 버전*/
  UINT8 driverMajorVersion;
  UINT8 driverMinorVersion;
  UINT8 driverPatchVersion;
} HSM_VERSION_CTX_t;

typedef enum
{	
  HSM_CONFIG_LOCK_DISABLE = 0,	
  HSM_CONFIG_LOCK_ENABLE = 1,	
  HSM_CONFIG_LOCK_ENUM_SET_UINT32 = 0x7FFFFFFF,
} HSM_CONFIG_LOCK_STATE_t;

/* Hsm_KeyTypes.h */
typedef struct Rsa_Keypair_t_
{
  UINT8 mod[RSA_BYTE_SIZE]; // n
  UINT8 priExp[RSA_BYTE_SIZE]; // d
} Rsa_Keypair_t;

typedef struct Ecc_Keypair_t_
{
  UINT8 prikey[ECC_BYTE_SIZE];
  UINT8 pubkeyX[ECC_BYTE_SIZE];
  UINT8 pubkeyY[ECC_BYTE_SIZE];
} Ecc_Keypair_t;


/* CryptoService_Ecc.h */
typedef struct
{
  UINT8 r[ECC_BYTES_SIZE]; /**<  Bytes to r */
  UINT8 s[ECC_BYTES_SIZE]; /**<  Bytes to s */
} ECC_ECDSA_SIGN_t;

typedef struct
{
  UINT8 x[ECC_BYTES_SIZE]; /**<  Pointer to x */
  UINT8 y[ECC_BYTES_SIZE]; /**<  Pointer to y */
} ECC_PUBLICKEY_t;


/* SecurityApp_ProactiveDataProtection.h */
typedef struct
{
    UINT32 startAddr;
    UINT32 size;
} HSM_PDP_SEGMENT_t;

typedef struct
{
    UINT16 cmacKeyNum;
    UINT16 segmentNum;
    HSM_PDP_SEGMENT_t segInfo[HSM_MAX_PDP_SEG_NUM];
} HSM_PDP_CONFIG_t;


/* SecurityApp_Rng.h */
typedef struct
{
	UINT16 jobId;
	UINT32 count;
	UINT16 osTask;
} HSMAPI_TRNG_CTX_t;


/* SecurityApp_SecureBoot.h */
typedef struct
{
  UINT16 cmacKeyNum;
  UINT32 bootStartAddr;
  UINT32 bootSize;
  UINT32 signStartAddr;
  UINT16 signKeyNum;
} HSM_SB_CONFIG_t;

///Dual Bank
typedef struct
{
    UINT32 bootStartAddrBankA;
    UINT32 bootSizeBankA;
    UINT32 bootStartAddrBankB;
    UINT32 bootSizeBankB;
    UINT16 cmacKeyNum;
} HSM_SB_DUAL_CONFIG_t;

typedef struct
{
    UINT32 bootStartAddrBankA;
    UINT32 bootSizeBankA;
    UINT32 bootStartAddrBankB;
    UINT32 bootSizeBankB;
    UINT16 cmacKeyNum;
    UINT16 signKeyNum;
    UINT32 signStartAddr;
} HSM_SB_MAC_DUALBANK_CONFIG_t;





/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
/* CryptoService_Aes.h */
extern Std_ReturnType HSM_AesEncStart(HSMAPI_CTX_t *aesCtx, AES_MODE aesMode, UINT16 aesKeyNum, const UINT8 *ivBuff);
extern Std_ReturnType HSM_AesEncUpdate(const HSMAPI_CTX_t *aesCtx, const UINT8 *plain, UINT32 plainLen);
extern Std_ReturnType HSM_AesEncFinish(const HSMAPI_CTX_t *aesCtx);
extern Std_ReturnType HSM_AesDecStart(HSMAPI_CTX_t *aesCtx, AES_MODE aesMode, UINT16 aesKeyNum, const UINT8 *ivBuff);
extern Std_ReturnType HSM_AesDecUpdate(const HSMAPI_CTX_t *aesCtx, const UINT8 *cipher, UINT32 cipherLen);
extern Std_ReturnType HSM_AesDecFinish(const HSMAPI_CTX_t *aesCtx);
extern Std_ReturnType HSM_AesCmacStart(HSMAPI_CTX_t *aesCmacCtx, UINT16 aesCmacKeyNum, UINT32 totalMsgLen);
extern Std_ReturnType HSM_AesCmacUpdate(const HSMAPI_CTX_t *aesCmacCtx, const UINT8 *data, UINT32 dataLen);
extern Std_ReturnType HSM_AesCmacFinish(const HSMAPI_CTX_t *aesCmacCtx, UINT8 *digest);


/* CryptoService_Ecc.h */
extern Std_ReturnType HSM_EccEcdsaSignStart(HSMAPI_CTX_t *eccCtx, UINT16 eccKeyNum);
extern Std_ReturnType HSM_EccEcdsaSignUpdate(const HSMAPI_CTX_t *eccCtx, const UINT8 *digest, const UINT8 *secretNumber);
extern Std_ReturnType HSM_EccEcdsaSignFinish(const HSMAPI_CTX_t *eccCtx, ECC_ECDSA_SIGN_t *sign);
extern Std_ReturnType HSM_EccEcdsaVerifyStart(HSMAPI_CTX_t *eccCtx, UINT16 eccKeyNum);
extern Std_ReturnType HSM_EccEcdsaVerifyUpdate(const HSMAPI_CTX_t *eccCtx, const UINT8 *digest, const ECC_ECDSA_SIGN_t *sign);
extern Std_ReturnType HSM_EccEcdsaVerifyFinish(const HSMAPI_CTX_t *eccCtx, UINT8 *result);
extern Std_ReturnType HSM_EccEcdhStart(HSMAPI_CTX_t *eccCtx, UINT16 eccKeyNum);
extern Std_ReturnType HSM_EccEcdhUpdate(const HSMAPI_CTX_t *eccCtx, const ECC_PUBLICKEY_t *pubkeyOtherSide);
extern Std_ReturnType HSM_EccEcdhFinish(const HSMAPI_CTX_t *eccCtx, UINT8 *secretValue);


/* CryptoService_Hash.h */
extern Std_ReturnType HSM_Sha160Start(HSMAPI_CTX_t *sha160Ctx);
extern Std_ReturnType HSM_Sha160Update(const HSMAPI_CTX_t *sha160Ctx, const UINT8 *data, UINT32 dataLen);
extern Std_ReturnType HSM_Sha160Finish(const HSMAPI_CTX_t *sha160Ctx, UINT8 *digest);
extern Std_ReturnType HSM_Sha256Start(HSMAPI_CTX_t *sha256Ctx);
extern Std_ReturnType HSM_Sha256Update(const HSMAPI_CTX_t *sha256Ctx, const UINT8 *data, UINT32 dataLen);
extern Std_ReturnType HSM_Sha256Finish(const HSMAPI_CTX_t *sha256Ctx, UINT8 *digest);
extern Std_ReturnType HSM_HmacSha256Start(HSMAPI_CTX_t *hmacSha256Ctx, UINT16 keyNum);
extern Std_ReturnType HSM_HmacSha256Update(const HSMAPI_CTX_t *hmacSha256Ctx, const UINT8 *data, UINT32 dataLen);
extern Std_ReturnType HSM_HmacSha256Finish(const HSMAPI_CTX_t *hmacSha256Ctx, UINT8 *digest);


/* CryptoService_Pbkdf2.h */
extern Std_ReturnType HSM_Pbkdf2Start(HSMAPI_CTX_t *pbkdf2Ctx, UINT16 pbkdf2KeyNum);
extern Std_ReturnType HSM_Pbkdf2Update(const HSMAPI_CTX_t *pbkdf2Ctx, UINT16 pbkdf2KeyNum, UINT32 dkLen, const UINT8 *password, UINT32 pLen, const UINT8 *salt, UINT32 sLen, UINT32 icount);
extern Std_ReturnType HSM_Pbkdf2Finish(const HSMAPI_CTX_t *pbkdf2Ctx, UINT32 dkLen, UINT8 *derivedKey);


/* CryptoService_RsaPkcs1.h */
extern Std_ReturnType HSM_RsaPkcs1v15SignStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum);
extern Std_ReturnType HSM_RsaPkcs1v15SignUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *digest);
extern Std_ReturnType HSM_RsaPkcs1v15SignFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *sign);
extern Std_ReturnType HSM_RsaPkcs1v15VerifyStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum);
extern Std_ReturnType HSM_RsaPkcs1v15VerifyUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *digest, const UINT8 *sign);
extern Std_ReturnType HSM_RsaPkcs1v15Sha160VerifyUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *digest, const UINT8 *sign);
extern Std_ReturnType HSM_RsaPkcs1v15VerifyFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *verifyResult);
extern Std_ReturnType HSM_RsaPkcs1v15EncStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum);
extern Std_ReturnType HSM_RsaPkcs1v15EncUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *msg, UINT32 msgLen);
extern Std_ReturnType HSM_RsaPkcs1v15EncFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *cipher);
extern Std_ReturnType HSM_RsaPkcs1v15DecStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum);
extern Std_ReturnType HSM_RsaPkcs1v15DecUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *cipher);
extern Std_ReturnType HSM_RsaPkcs1v15DecFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *msg, UINT32 *msgLen);
extern Std_ReturnType HSM_RsaPkcs1PssSignStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum);
extern Std_ReturnType HSM_RsaPkcs1PssSignUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *digest, const UINT8 *salt, UINT32 saltLen);
extern Std_ReturnType HSM_RsaPkcs1PssSignFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *sign);
extern Std_ReturnType HSM_RsaPkcs1PssVerifyStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum);
extern Std_ReturnType HSM_RsaPkcs1PssVerifyUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *digest, const UINT8 *sign, UINT32 saltLen);
extern Std_ReturnType HSM_RsaPkcs1PssVerifyFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *result);
extern Std_ReturnType HSM_RsaPkcs1oaepEncStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum);
extern Std_ReturnType HSM_RsaPkcs1oaepEncUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *msg, UINT32 msgLen, const UINT8 *label, UINT32 labelLen, const UINT8 *seed);
extern Std_ReturnType HSM_RsaPkcs1oaepEncFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *cipher);
extern Std_ReturnType HSM_RsaPkcs1oaepDecStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum);
extern Std_ReturnType HSM_RsaPkcs1oaepDecUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *cipher, const UINT8 *label, UINT32 labelLen);
extern Std_ReturnType HSM_RsaPkcs1oaepDecFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *msg, UINT32 *msgLen);


/* CryptoService_RsaPkcs3.h */
extern Std_ReturnType HSM_RsaPkcs3DHKeypairGenStart(HSMAPI_CTX_t *pkcs3Ctx);
extern Std_ReturnType HSM_RsaPkcs3DHKeypairGenUpdate(const HSMAPI_CTX_t *pkcs3Ctx, const UINT8 *privValue, const UINT8 *baseG, const UINT8 *primeP);
extern Std_ReturnType HSM_RsaPkcs3DHKeypairGenFinish(const HSMAPI_CTX_t *pkcs3Ctx, UINT8 *publicValue, UINT8 *privateValue);
extern Std_ReturnType HSM_RsaPkcs3DHSharedValueGenStart(HSMAPI_CTX_t *pkcs3Ctx);
extern Std_ReturnType HSM_RsaPkcs3DHSharedValueGenUpdate(const HSMAPI_CTX_t *pkcs3Ctx, const UINT8 *publicValue, const UINT8 *privateValue, const UINT8 *primeP);
extern Std_ReturnType HSM_RsaPkcs3DHSharedValueGenFinish(const HSMAPI_CTX_t *pkcs3Ctx, UINT8 *secretValue);


/* Hsm_HostAPI.h */

extern Std_ReturnType HSM_DriverInitialize(void);
extern Std_ReturnType HSM_EnableService(UINT32 conf, UINT32 priority);
extern void HSM_IrqHandler(void);
extern UINT32 HSM_GetLastErrorCode(void);
extern Std_ReturnType HSM_WaitResp(UINT16 jobId);
extern Std_ReturnType HSM_ReadRxBuff(UINT16 jobId, UINT32 count, UINT8 *data);
extern UINT32 HSM_GetMaxTranSizeByte(void);
extern Std_ReturnType HSM_CancelJob(UINT16 jobId);
extern Std_ReturnType HSM_GetMcuUid(UINT8 *uid);
extern Std_ReturnType HSM_GetVersionInfo(HSM_VERSION_CTX_t *version);
extern Std_ReturnType HSM_GetAllSecurityInfo(HSM_SECURITY_INFO_t *info);
extern Std_ReturnType HSM_TempStop(void);
extern Std_ReturnType HSM_Restart(void);
extern BOOL HSM_CheckHsmTempStopState(void);
extern Std_ReturnType HSM_FactoryHsmConfigurationLock(void);
extern void HSM_DisableInterruptService(void);
extern void HSM_SetCallbackFuncWaitCount(UINT32 waitCount);
extern Std_ReturnType HSM_Sleep(void);
extern Std_ReturnType HSM_Wakeup(void);
extern Std_ReturnType HSM_SetWakeupTrigger(const UINT16 *list, UINT16 idxNum);
extern BOOL HSM_IsSleepStatus(void);
extern Std_ReturnType HSM_StartUsingDFlash(void);
extern Std_ReturnType HSM_FinishUsingDFlash(void);
extern Std_ReturnType HSM_SetHsmHandlerIrqN(UINT8 irqN);
extern Std_ReturnType HSM_ClearWakeupTrigger(void);
extern void HSM_SetApiWaitRespTime(UINT32 ms); 
extern Std_ReturnType HSM_ChallengeRequest(UINT8 *ChallengeValue);
extern Std_ReturnType HSM_ResponseForward(UINT8 *ResponseValue);
extern Std_ReturnType HSM_GetConfigurationLockState(HSM_CONFIG_LOCK_STATE_t *state);
extern Std_ReturnType HSM_SetIdAuthentication(const UINT32 *idAuth);
extern Std_ReturnType HSM_SetInterruptConfig(UINT32 coreNum, UINT32 priority);

/* SecurityApp_FwTamperDetection.h */
extern Std_ReturnType HSM_FwTamperDetectionStatus(HSM_FTD_STATE_t *state);
extern Std_ReturnType HSM_FwTamperDetectionLog(HSM_FTD_LOG_t *ftdLog);
extern Std_ReturnType HSM_FwTamperDetectionTempStop(const UINT8 *password, UINT32 pwByteLen, HSM_PASSWORD_VERIFY_STATE_t *errState);
extern Std_ReturnType HSM_FwTamperDetectionRestart(void);
extern Std_ReturnType HSM_FwTamperDetectionConfig(const HSM_FTD_CONFIG_t *ftdConfig, HSM_CallbackFunc cbFunc);
extern Std_ReturnType HSM_FwTamperDetectionUpdtTarget(const HSM_FTD_TARGET_t *ftdTarget, HSM_CallbackFunc cbFunc);
extern Std_ReturnType HSM_FactoryFwTamperDetectionEnable(const HSM_FTD_CONFIG_t *ftdConfig, HSM_CallbackFunc cbFunc);
extern Std_ReturnType HSM_FactoryFwTamperDetectionDisable(void);


/* SecurityApp_KeyManagement.h */
extern Std_ReturnType HSM_KeyManagementSetAesKey(const UINT16 keyIndex, UINT8* key, UINT16 keyLock);
extern Std_ReturnType HSM_KeyManagementSetRsaKey(const UINT16 keyIndex, Rsa_Keypair_t* key, UINT16 keyLock);
extern Std_ReturnType HSM_KeyManagementSetEccKey(const UINT16 keyIndex, Ecc_Keypair_t* key, UINT16 keyLock);
extern Std_ReturnType HSM_KeyManagementValidateKey(KEY_TYPE keyType, const UINT16 keyIndex);


/* SecurityApp_ProactiveDataProtection.h */
extern Std_ReturnType HSM_PDPConfig(HSM_PDP_CONFIG_t* pdpConfig);
extern Std_ReturnType HSM_PDPDataUpdate(void);
extern Std_ReturnType HSM_PDPDataVerify(void);
extern Std_ReturnType HSM_PDPDisable(void);


/* SecurityApp_Rng.h */
extern Std_ReturnType HSM_TrueRandomGenerate(UINT8 *randValue, UINT32 len);
extern Std_ReturnType HSM_PseudoRandomGenerate(UINT8 *randValue, UINT32 len);


/* SecurityApp_SecureBoot.h */
extern Std_ReturnType HSM_SecureBootResult(HSM_SECUREBOOT_STATE_t *state);
extern Std_ReturnType HSM_SecureBootMacUpdate(const HSM_SB_CONFIG_t *sbConfig);
extern Std_ReturnType HSM_FactorySecureBootEnable(const HSM_SB_CONFIG_t *sbConfig);
extern Std_ReturnType HSM_FactorySecureBootDisable(void);


/* SecurityApp_SecureDebug.h */
extern Std_ReturnType HSM_FactoryDebuggerProtectionEnable(const UINT8 *password, UINT32 pwByteLen);
extern Std_ReturnType HSM_FactoryDebuggerProtectionTempStop(const UINT8 *password, UINT32 pwByteLen, HSM_SECUREDEBUG_STATE_t *debugState);
extern Std_ReturnType HSM_FactorySecureBootEnableDualBank(const HSM_SB_DUAL_CONFIG_t *sbConfig);
extern Std_ReturnType HSM_SecureBootMacUpdateDualBank(const HSM_SB_MAC_DUALBANK_CONFIG_t *sbConfig);

/* SecurityApp_FeatureOnDemand.h */
extern Std_ReturnType HSM_FeatureOnDemandCertStore(const FoDCert *fodCert, const HSM_SIGN_t *signInfo, HSM_FOD_ERR_STATE_t* errState);
extern Std_ReturnType HSM_FeatureOnDemandCertDelete(const FoDCert *fodCert, const HSM_SIGN_t *signInfo, HSM_FOD_ERR_STATE_t* errState);
extern Std_ReturnType HSM_FeatureOnDemandGetCertList(FoDCert fodCertList[], UINT32 *numOfFodCert, HSM_FOD_ERR_STATE_t* errState);

#endif /* DUMMY_HAEHSMDRIVER_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
