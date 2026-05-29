/*
 * LibSecure.h
 *
 *  Created on: 2019. 10. 16.
 *      Author: HAE
 */

#ifndef HKMC_SECURE_FLASH2_H_
#define HKMC_SECURE_FLASH2_H_

#define AES_N_BLOCK 16

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef uint32_defined
/** 32 bit unsigned integer. */
typedef unsigned long uint32;
#define uint32_defined
#endif

#ifndef uint16_defined
/** 16 bit unsigned integer. */
typedef unsigned short uint16;
#define uint16_defined
#endif

#ifndef uint8_defined
/** 8 bit unsigned integer. */
typedef unsigned char uint8;
#define uint8_defined
#endif

typedef void(*SecureFlash_Callback)(void);

#define SECUREFLASH_RSA_PUBLICKEY_BYTES	256U
typedef struct {
	uint8 modulus[SECUREFLASH_RSA_PUBLICKEY_BYTES];
	uint32 exponet;
} SecureFlash_PublicKey;
typedef uint8 SecureFlash_SignBuff;

typedef enum {
	RT_SUCCESS=0,
	RT_FAIL=1,	
	RT_FAIL_MAC=2,
}SecureFlash_RT;

extern SecureFlash_RT SecureFlash_DecryptStart(const uint8* iv, const uint8* firmwareKey, const uint8 firmwareKeyLen, const uint8* macOfFirmwareKey, const uint8* macKey, const uint8 macKeyLen);
extern SecureFlash_RT SecureFlash_DecryptUpdate(uint8* out, const uint8* in, const uint32 inLen);
extern SecureFlash_RT SecureFlash_DecryptFinish(uint32* totalLen);

extern SecureFlash_RT SecureFlash_VerifyStart(void);
extern SecureFlash_RT SecureFlash_VerifyUpdate(const uint8* payload, const uint32 length);
extern SecureFlash_RT SecureFlash_VerifyFinish(const SecureFlash_PublicKey* pubKey, const SecureFlash_SignBuff* sigBuff);

extern SecureFlash_RT SecureFlash_HashStart(void);
extern SecureFlash_RT SecureFlash_HashUpdate(const uint8* payload, const uint32 length);
extern SecureFlash_RT SecureFlash_HashFinish(uint8* digest);

extern uint32 SecureFlash_GetVersionInfo(void);
extern SecureFlash_RT SecureFlash_SetCallback(const SecureFlash_Callback cbFunc);


#ifdef  __cplusplus
}
#endif

#endif /* HKMC_SECURE_FLASH2_H_ */
