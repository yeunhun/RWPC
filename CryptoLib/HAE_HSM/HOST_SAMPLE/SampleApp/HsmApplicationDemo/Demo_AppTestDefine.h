/*
 * Demo_AppTestDefine.h
 *
 */
#ifndef DEMO_APP_TEST_DEFINE_H_
#define DEMO_APP_TEST_DEFINE_H_

#include "Cfg_App.h"
/*
* Cfg_App.h include below options
* #define EXTENDED_TEST_VECTOR
* #define WAIT_RESP_TIMEOUT 300000000 // 15sec
*/

#include "CryptoService_Def.h"
#include "SecurityApp_SecureBoot.h"
#include "SecurityApp_FwTamperDetection.h"
#include "SecurityApp_SecureDebug.h"
#include "SecurityApp_KeyManagement.h"
#include "SecurityApp_ProactiveDataProtection.h"
#include "SecurityApp_FeatureOnDemand.h"

#if defined(__GHS__)
#pragma ghs startdata
#endif

/******************************************************************************/
/* 				Secure App-Secure Boot TEST Vector				              */
/******************************************************************************/
typedef struct HSM_SECURE_BOOT_TestVector_t
{
	HSM_SB_CONFIG_t sbConfig;
} HSM_SECURE_BOOT_TestVector_t;

#if defined(TRAVEO2_SERIES)
typedef struct HSM_SECURE_BOOT_DUALBANK_TestVector_t
{
	HSM_SB_DUAL_CONFIG_t sbConfig;
} HSM_SECURE_BOOT_DUALBANK_TestVector_t;

typedef struct HSM_SECURE_BOOT_MAC_DUALBANK_TestVector_t
{
	HSM_SB_MAC_DUALBANK_CONFIG_t sbConfig;
} HSM_SECURE_BOOT_MAC_DUALBANK_TestVector_t;
#endif

extern HSM_SECURE_BOOT_TestVector_t g_HsmSecureBootTv; //Default Test

#if defined(TRAVEO2_SERIES)
extern const HSM_SECURE_BOOT_DUALBANK_TestVector_t g_HsmSecureBootDualBankTv1; //Default Dual Bank SB Enable Test
extern const HSM_SECURE_BOOT_DUALBANK_TestVector_t g_HsmSecureBootDualBankTv2; //Default Dual Bank SB Enable Test
extern const HSM_SECURE_BOOT_DUALBANK_TestVector_t g_HsmSecureBootDualBankTv3; //Default Dual Bank SB Enable Test
extern const HSM_SECURE_BOOT_DUALBANK_TestVector_t g_HsmSecureBootDualBankFailTv1; //Default Dual Bank SB Enable Test
extern const HSM_SECURE_BOOT_DUALBANK_TestVector_t g_HsmSecureBootDualBankFailTv2; //Default Dual Bank SB Enable Test

extern const HSM_SECURE_BOOT_MAC_DUALBANK_TestVector_t g_HsmSecureBootMACDualBankTv1; //Default Dual Bank MAC Update Test
extern const HSM_SECURE_BOOT_MAC_DUALBANK_TestVector_t g_HsmSecureBootMACDualBankFailTv1; //Default Dual Bank MAC Update Test
extern const HSM_SECURE_BOOT_MAC_DUALBANK_TestVector_t g_HsmSecureBootMACDualBankFailTv2; //Default Dual Bank MAC Update Test
extern const HSM_SECURE_BOOT_MAC_DUALBANK_TestVector_t g_HsmSecureBootMACDualBankFailTv3; //Default Dual Bank MAC Update Test
extern const HSM_SECURE_BOOT_MAC_DUALBANK_TestVector_t g_HsmSecureBootMACDualBankFailTv4; //Default Dual Bank MAC Update Test
extern const HSM_SECURE_BOOT_MAC_DUALBANK_TestVector_t g_HsmSecureBootMACDualBankFailTv5; //Default Dual Bank MAC Update Test
extern const HSM_SECURE_BOOT_MAC_DUALBANK_TestVector_t g_HsmSecureBootMACDualBankFailTv6; //Default Dual Bank MAC Update Test
extern const HSM_SECURE_BOOT_MAC_DUALBANK_TestVector_t g_HsmSecureBootMACDualBankFailTv7; //Default Dual Bank MAC Update Test
#endif

#if defined(__TASKING__)
#pragma section farrom "HSM_TEST_VECTOR"
#endif
#if defined(__GHS__)
#pragma ghs section rodata="HSM_TEST_VECTOR"
#endif
extern const HSM_SECURE_BOOT_TestVector_t g_HsmSecureBootTv1; //Success Test 1 : Default. CMAC Key #405 / Sign Key #401
extern const HSM_SECURE_BOOT_TestVector_t g_HsmSecureBootTv2; //Success Test 2 : Key Change. CMAC Key #404 / Sign Key #402
extern const HSM_SECURE_BOOT_TestVector_t g_HsmSecureBootTv3; //Success Test 3 : Not Complete Word Size Rom(Rom Size 63Byte). CMAC Key #405  / Sign Key #401
extern const HSM_SECURE_BOOT_TestVector_t g_HsmSecureBootTv4; //Success Test 4 : Mass Size Rom. CMAC Key #405  / Sign Key #401
extern const HSM_SECURE_BOOT_TestVector_t g_HsmSecureBootTv5; //Success Test 5 : Mass Size Rom 32K. CMAC Key #405  / Sign Key #401
extern const HSM_SECURE_BOOT_TestVector_t g_HsmSecureBootTv6; //Success Test 6 : Mass Size Rom 64k. CMAC Key #405  / Sign Key #401
extern const HSM_SECURE_BOOT_TestVector_t g_HsmSecureBootTv7; //Success Test 7 : Mass Size Rom 512k. CMAC Key #405  / Sign Key #401
extern const HSM_SECURE_BOOT_TestVector_t g_HsmSecureBootFailTv1; //Fail Test 1 : Invalid BootSize
extern const HSM_SECURE_BOOT_TestVector_t g_HsmSecureBootFailTv2; //Fail Test 2 : Invalid Sign Address bootStartAddr==signStartAddr
extern const HSM_SECURE_BOOT_TestVector_t g_HsmSecureBootFailTv3; //Fail Test 3 : Invalid Cmac Key Index
extern const HSM_SECURE_BOOT_TestVector_t g_HsmSecureBootFailTv4; //Fail Test 4 : Invalid Sign Key Index
extern const HSM_SECURE_BOOT_TestVector_t g_HsmSecureBootFailTv5; //Fail Test 5 : Invalid Sign
#if defined(__TASKING__)
#pragma section farrom restore
#endif
#if defined(__GHS__)
#pragma ghs section rodata=default
#endif

/******************************************************************************/
/*	   			Secure App-Firmware Tamper Detection TEST Vector		      */
/******************************************************************************/
typedef struct HSM_FTD_SEG_TestVector_t
{
	UINT32 size;
	UINT32 startAddr;
} HSM_FTD_SEG_TestVector_t;

typedef struct HSM_FTD_TARGET_testVector_t
{
	HSM_FTD_TARGET_t ftdUpdateInfo;
	UINT8 *mac;
} HSM_FTD_TARGET_testVector_t;

typedef struct HSM_FTD_CONFIG_TestVector_t
{
	HSM_FTD_CONFIG_t ftdConfig;
	UINT8 *targetMac[6];
} HSM_FTD_CONFIG_TestVector_t;

typedef struct HSM_FTD_TEMP_STOP_TestVector_t
{
	UINT32 stopPassword[HSM_FTD_STOP_PW_WORD_LEN];
	UINT32 stopPasswordByteLen;
} HSM_FTD_TEMP_STOP_TestVector_t;

#if defined(__TASKING__)
#pragma section farrom "HSM_TEST_VECTOR"
#endif
#if defined(__GHS__)
#pragma ghs section rodata="HSM_TEST_VECTOR"
#endif
extern const HSM_FTD_CONFIG_TestVector_t g_HsmFtdConfigTv1; //Success Test 1: CMAC Key $405 / Sign Key #401 Target6-Segment4
extern const HSM_FTD_CONFIG_TestVector_t g_HsmFtdConfigTv2;	//Success Test 2 : Target change. Total target : 1
extern const HSM_FTD_CONFIG_TestVector_t g_HsmFtdConfigTv3; //Success Test 3 : CMAC Key Change #404. Target1-Segment1
extern const HSM_FTD_CONFIG_TestVector_t g_HsmFtdConfigTv4; //Success Test 4 : Sign Key Change #402 Target1-Segment1
extern const HSM_FTD_CONFIG_TestVector_t g_HsmFtdConfigTv5; //Success Test 5 : LARGE SIZE (32Kb)
extern const HSM_FTD_CONFIG_TestVector_t g_HsmFtdConfigTv6; //Success Test 6 : LARGE SIZE (64Kb)
extern const HSM_FTD_CONFIG_TestVector_t g_HsmFtdConfigTv7; //Success Test 7 : LARGE SIZE (512Kb)
extern const HSM_FTD_CONFIG_TestVector_t g_HsmFtdConfigTv8; //Success Test 8 : LARGE SIZE (1.5M, 64k*6*4 = 1536Kb)
extern const HSM_FTD_CONFIG_TestVector_t g_HsmFtdConfigFailTv1;	//Fail Test 1 : Invalid Segment Size
extern const HSM_FTD_CONFIG_TestVector_t g_HsmFtdConfigFailTv2;	//Fail Test 2 : Invalid Segment Number
extern const HSM_FTD_CONFIG_TestVector_t g_HsmFtdConfigFailTv3;	//Fail Test 3 : Invalid Total Target Num
extern const HSM_FTD_CONFIG_TestVector_t g_HsmFtdConfigFailTv4;	//Fail Test 4 : Invalid Target Index
extern const HSM_FTD_CONFIG_TestVector_t g_HsmFtdConfigFailTv5;	//Fail Test 5 : Invalid CMAC Key Index
extern const HSM_FTD_CONFIG_TestVector_t g_HsmFtdConfigFailTv6;	//Fail Test 6 : Invalid Sign Key Index
extern const HSM_FTD_CONFIG_TestVector_t g_HsmFtdConfigFailTv7;	//Fail Test 7 : Target3 Sign Error

extern const HSM_FTD_TARGET_testVector_t g_HsmFtdUpdtTargetTv1;	//Success Test 1 : Target0 Update. Target1-Segment4 ROM0423 / CMAC Key #405, Sign Key #401
extern const HSM_FTD_TARGET_testVector_t g_HsmFtdUpdtTargetTv2;	//Success Test 2 : CMAC Key Change #404 Target1-Segment4 ROM0423
extern const HSM_FTD_TARGET_testVector_t g_HsmFtdUpdtTargetTv3;	//Success Test 3 : Sign Key #402 Target1-Segment1
extern const HSM_FTD_TARGET_testVector_t g_HsmFtdUpdtTargetTv4;	//Success Test 4 : Target1-Segment4 ROM0123
extern const HSM_FTD_TARGET_testVector_t g_HsmFtdUpdtTargetTv5;	//Success Test 5 : Target1-Segment3 ROM234
extern const HSM_FTD_TARGET_testVector_t g_HsmFtdUpdtTargetTv6;	//Success Test 6 : Target5 Update ROM0123
extern const HSM_FTD_TARGET_testVector_t g_HsmFtdUpdtTargetTv7;	//Success Test 7 : Taget1 update #404 Target1-Segment1
extern const HSM_FTD_TARGET_testVector_t g_HsmFtdUpdtTargetTv8;	//Success Test 8 : Taget2 update #404 Target1-Segment1
extern const HSM_FTD_TARGET_testVector_t g_HsmFtdUpdtTargetTv9;	//Success Test 9 : Taget3 update #404 Target1-Segment1
extern const HSM_FTD_TARGET_testVector_t g_HsmFtdUpdtTargetTv10;//Success Test 10 : Taget4 update #404 Target1-Segment1
extern const HSM_FTD_TARGET_testVector_t g_HsmFtdUpdtTargetTv11;//Success Test 11 : Taget5 update #404 Target1-Segment1
extern const HSM_FTD_TARGET_testVector_t g_HsmFtdUpdtTargetTv12;//Success Test 12 : Taget0 update #404 Target1-Segment1(32KB)
extern const HSM_FTD_TARGET_testVector_t g_HsmFtdUpdtTargetTv13;//Success Test 12 : Taget0 update #404 Target1-Segment1(64KB)
extern const HSM_FTD_TARGET_testVector_t g_HsmFtdUpdtTargetTv14;//Success Test 13 : Taget0 update #404 Target1-Segment1(512KB)
extern const HSM_FTD_TARGET_testVector_t g_HsmFtdUpdtTargetFailTv1;	//Fail Test 1 : Invalid Segment Size
extern const HSM_FTD_TARGET_testVector_t g_HsmFtdUpdtTargetFailTv2;	//Fail Test 2 : Invalid Segment Number
extern const HSM_FTD_TARGET_testVector_t g_HsmFtdUpdtTargetFailTv3;	//Fail Test 3 : Invalid Target Index
extern const HSM_FTD_TARGET_testVector_t g_HsmFtdUpdtTargetFailTv4;	//Fail Test 4 : Invalid Target Index (Target not set)
extern const HSM_FTD_TARGET_testVector_t g_HsmFtdUpdtTargetFailTv5;	//Fail Test 5 : Invalid CMAC Key Index
extern const HSM_FTD_TARGET_testVector_t g_HsmFtdUpdtTargetFailTv6;	//Fail Test 6 : Invalid Sign Key Index
extern const HSM_FTD_TARGET_testVector_t g_HsmFtdUpdtTargetFailTv7;	//Fail Test 7 : Invalid Sign

extern const HSM_FTD_TEMP_STOP_TestVector_t g_HsmFtdTempStopTv1;
extern const HSM_FTD_TEMP_STOP_TestVector_t g_HsmFtdTempStopFailTv1; //Fail Test 1: password length error
extern const HSM_FTD_TEMP_STOP_TestVector_t g_HsmFtdTempStopFailTv2; //Fail Test 2: password error

#if defined(__TASKING__)
#pragma section farrom restore
#endif
#if defined(__GHS__)
#pragma ghs section rodata=default
#endif
/******************************************************************************/
/* 			Secure App-Proactive Data Protection TEST Vector	              */
/******************************************************************************/
typedef struct HSM_PROACTIVE_DATA_PROTECTION_TestVector_t
{
	HSM_PDP_CONFIG_t pdpConfig;
} HSM_PROACTIVE_DATA_PROTECTION_TestVector_t;


#if defined(__TASKING__)
#pragma section farrom "HSM_TEST_VECTOR"
#endif
#if defined(__GHS__)
#pragma ghs section rodata="HSM_TEST_VECTOR"
#endif

extern const HSM_PROACTIVE_DATA_PROTECTION_TestVector_t g_HsmPdpTv1;  //Success Test 1 : KeyNum = 405, SegmentNum = 4, ROM0, ROM1, ROM2, ROM3 
extern const HSM_PROACTIVE_DATA_PROTECTION_TestVector_t g_HsmPdpTv2;  //Success Test 2 : KeyNum = 404, SegmentNum = 3, ROM0, ROM1, ROM2, ROM3 입력. SegmentNum이 3이므로 HSM Dflash에는 ROM2까지만 저장되고 ROM은 저장되지 않음.
extern const HSM_PROACTIVE_DATA_PROTECTION_TestVector_t g_HsmPdpFailTv1; //Fail Test 1 : Invalid Data  SegmentNum = 3, ROM0만 입력 SegmentNum이 3이지만 실제로 입력된 갯수는 1개이므로 드라이버에서 E_NOT_OK 리턴.
extern const HSM_PROACTIVE_DATA_PROTECTION_TestVector_t g_HsmPdpFailTv2; //Fail Test 2 : Invalid Segment Num
extern const HSM_PROACTIVE_DATA_PROTECTION_TestVector_t g_HsmPdpFailTv3; //Fail Test 3 : Invalid CMAC Key Index 0
extern const HSM_PROACTIVE_DATA_PROTECTION_TestVector_t g_HsmPdpFailTv4; //Fail Test 4 : Invalid CMAC Key Index 303
#if defined(__TASKING__)
#pragma section farrom restore
#endif
#if defined(__GHS__)
#pragma ghs section rodata=default
#endif

/******************************************************************************/
/* 				    Secure App-Key Management TEST Vector 		              */
/******************************************************************************/
typedef struct HSM_KEY_MANAGEMENT_AES_TestVector_t
{
	UINT16 keyIndex;
	UINT8 *aesKeyConfig;
	UINT16 keyLock;
} HSM_KEY_MANAGEMENT_AES_TestVector_t;

typedef struct HSM_KEY_MANAGEMENT_RSA_TestVector_t
{
	UINT16 keyIndex;
	Rsa_Keypair_t *rsaKeyConfig;
	UINT16 keyLock;
} HSM_KEY_MANAGEMENT_RSA_TestVector_t;

typedef struct HSM_KEY_MANAGEMENT_ECC_TestVector_t
{
	UINT16 keyIndex;
	Ecc_Keypair_t *eccKeyConfig;
	UINT16 keyLock;
} HSM_KEY_MANAGEMENT_ECC_TestVector_t;

typedef struct {
    KEY_TYPE keyType;
    UINT16 keyIndex;
} HSM_KEY_MANAGEMENT_VALIDATE_TestVector_t;

#if defined(__TASKING__)
#pragma section farrom "HSM_TEST_VECTOR"
#endif
#if defined(__GHS__)
#pragma ghs section rodata="HSM_TEST_VECTOR"
#endif

extern const HSM_KEY_MANAGEMENT_AES_TestVector_t g_HsmKmAesTv1;
extern const HSM_KEY_MANAGEMENT_AES_TestVector_t g_HsmKmAesTv2;
extern const HSM_KEY_MANAGEMENT_AES_TestVector_t g_HsmKmAesTv3;
extern const HSM_KEY_MANAGEMENT_AES_TestVector_t g_HsmKmAesTv4;
extern const HSM_KEY_MANAGEMENT_AES_TestVector_t g_HsmKmAesTv5;
extern const HSM_KEY_MANAGEMENT_AES_TestVector_t g_HsmKmAesTv6;
extern const HSM_KEY_MANAGEMENT_AES_TestVector_t g_HsmKmAesTv7;
extern const HSM_KEY_MANAGEMENT_AES_TestVector_t g_HsmKmAesTv8;
extern const HSM_KEY_MANAGEMENT_AES_TestVector_t g_HsmKmAesTv9;
extern const HSM_KEY_MANAGEMENT_AES_TestVector_t g_HsmKmAesTv10;
extern const HSM_KEY_MANAGEMENT_AES_TestVector_t g_HsmKmAesFailTv1;
extern const HSM_KEY_MANAGEMENT_AES_TestVector_t g_HsmKmAesFailTv2;
extern const HSM_KEY_MANAGEMENT_AES_TestVector_t g_HsmKmAesFailTv3;
extern const HSM_KEY_MANAGEMENT_AES_TestVector_t g_HsmKmAesFailTv4;
extern const HSM_KEY_MANAGEMENT_AES_TestVector_t g_HsmKmAesTempTv1;
extern const HSM_KEY_MANAGEMENT_AES_TestVector_t g_HsmKmAesTempTv2;
extern const HSM_KEY_MANAGEMENT_AES_TestVector_t g_HsmKmAesTempTv3;
extern const HSM_KEY_MANAGEMENT_AES_TestVector_t g_HsmKmAesTempTv4;

extern const HSM_KEY_MANAGEMENT_RSA_TestVector_t g_HsmKmRsaTv1;
extern const HSM_KEY_MANAGEMENT_RSA_TestVector_t g_HsmKmRsaTv2;
extern const HSM_KEY_MANAGEMENT_RSA_TestVector_t g_HsmKmRsaFailTv1;
extern const HSM_KEY_MANAGEMENT_RSA_TestVector_t g_HsmKmRsaFailTv2;
extern const HSM_KEY_MANAGEMENT_RSA_TestVector_t g_HsmKmRsaFailTv3;
extern const HSM_KEY_MANAGEMENT_RSA_TestVector_t g_HsmKmRsaFailTv4;
extern const HSM_KEY_MANAGEMENT_RSA_TestVector_t g_HsmKmRsaTempTv1;
extern const HSM_KEY_MANAGEMENT_RSA_TestVector_t g_HsmKmRsaTempTv2;

extern const HSM_KEY_MANAGEMENT_ECC_TestVector_t g_HsmKmEccTv1;
extern const HSM_KEY_MANAGEMENT_ECC_TestVector_t g_HsmKmEccTv2;
extern const HSM_KEY_MANAGEMENT_ECC_TestVector_t g_HsmKmEccFailTv1;
extern const HSM_KEY_MANAGEMENT_ECC_TestVector_t g_HsmKmEccFailTv2;
extern const HSM_KEY_MANAGEMENT_ECC_TestVector_t g_HsmKmEccFailTv3;
extern const HSM_KEY_MANAGEMENT_ECC_TestVector_t g_HsmKmEccFailTv4;
extern const HSM_KEY_MANAGEMENT_ECC_TestVector_t g_HsmKmEccTempTv1;
extern const HSM_KEY_MANAGEMENT_ECC_TestVector_t g_HsmKmEccTempTv2;
#if defined(__TASKING__)
#pragma section farrom restore
#endif
#if defined(__GHS__)
#pragma ghs section rodata=default
#endif


/******************************************************************************/
/* 				    Secure App- Feature On Demand TEST Vector 		          */
/******************************************************************************/
typedef struct HSM_FOD_TestVector_t
{
	FoDCert fodCert;
	HSM_SIGN_t eccSignInfo;
    UINT8 UserFV[FOD_CERT_FV_LEN];  /* Use Rev1 API */
} HSM_FOD_TestVector_t;

#if defined(__TASKING__)
#pragma section farrom "HSM_TEST_VECTOR"
#endif
#if defined(__GHS__)
#pragma ghs section rodata="HSM_TEST_VECTOR"
#endif

extern const HSM_FOD_TestVector_t g_HsmFoDTv1; //Success Test 1 : FoDCert Activate(TestKey#401)
extern const HSM_FOD_TestVector_t g_HsmFoDTv2; //Success Test 2 : FoDCert Deactivate(aSIMSKey#1)
extern const HSM_FOD_TestVector_t g_HsmFoDTv3; //Success Test 3 : FoDCert Activate(TestKey#401)
extern const HSM_FOD_TestVector_t g_HsmFoDTv4; //Success Test 4 : FoDCert Decctivate(aSIMSKey#1)

#if defined(__TASKING__)
#pragma section farrom restore
#endif
#if defined(__GHS__)
#pragma ghs section rodata=default
#endif

/******************************************************************************/
/* 			   			Secure App-Etc TEST Vector				          	  */
/******************************************************************************/
#define MCU_UNIQUE_ID_LEN (16u)
#define MCU_UNIQUE_ID_WORD_LEN (MCU_UNIQUE_ID_LEN/4u)

/******************************************************************************/
/* 				Secure App-Secure Debug TEST Vector				              */
/******************************************************************************/
typedef struct HSM_Secure_Debug_TestVector_t
{
	UINT32 password[8];
	UINT32 pwByteLen;
} HSM_Secure_Debug_TestVector_t;

extern HSM_Secure_Debug_TestVector_t g_HsmSecureDebugTv;
extern HSM_Secure_Debug_TestVector_t g_HsmSecureDebugTv2;
extern HSM_Secure_Debug_TestVector_t g_HsmSecureDebugTv3;

/******************************************************************************/
/* 				Secure App-Secure Password TEST Vector	              */
/******************************************************************************/

#define UCB_PASS_WORD (8u) //4*8 = 32byte
typedef struct HSM_Password_Verify_TestVector_t
{
	UINT32 password[UCB_PASS_WORD];
	UINT32 pwByteLen;
} Password_TestVector_t;

extern Password_TestVector_t g_PasswordTv;
extern Password_TestVector_t g_PasswordTv2;
extern Password_TestVector_t g_PasswordTv3;

#if defined(__GHS__)
#pragma ghs enddata
#endif

#endif /* DEMO_APP_TEST_DEFINE_H_ */
