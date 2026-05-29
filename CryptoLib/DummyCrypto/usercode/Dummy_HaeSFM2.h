/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dummy_HaeSFM2.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Dummy HAE library                                             **
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
** 1.0.1.0   03-Nov-2020   JaeHyun      Delete VERSION_INFO                   **
**                                     (Duplicate with ASK Lib)               **
*******************************************************************************/

#ifndef DUMMY_HAESFM2_H
#define DUMMY_HAESFM2_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#define HAC_ECC_BYTES_SIZE 32U
#define SECUREFLASH_RSA_PUBLICKEY_BYTES	256U

/*******************************************************************************
**                                Data Types                                  **
*******************************************************************************/
#ifndef uint8_defined
	typedef unsigned char		uint8;
	#define uint8_defined
#endif

#ifndef uint16_defined
  typedef unsigned long       uint16;
	#define uint16_defined
#endif

#ifndef uint32_defined
  typedef unsigned long       uint32;
	#define uint32_defined
#endif

typedef void(*SecureFlash_Callback)(void);

typedef uint8 SecureFlash_SignBuff;


/*******************************************************************************
**                               Enumerations                                 **
*******************************************************************************/
/* HKMC_SecureFlash2.h */
typedef enum {
	RT_SUCCESS=0,
	RT_FAIL,	
}SecureFlash_RT;

/*******************************************************************************
**                                Structures                                  **
*******************************************************************************/

typedef struct {
	uint8 modulus[SECUREFLASH_RSA_PUBLICKEY_BYTES];
	uint32 exponet;
} SecureFlash_PublicKey;

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
extern SecureFlash_RT SecureFlash_DecryptStart(
  uint8* iv, const uint8* decKey, const uint8 decKeyLen,
  const uint8* macOfDecKey, const uint8* macKey, const uint8 macKeyLen);
extern SecureFlash_RT SecureFlash_DecryptUpdate(
  uint8* out, const uint8* in, const uint32 inLen);
extern SecureFlash_RT SecureFlash_DecryptFinish(uint32* totalLen);

extern SecureFlash_RT SecureFlash_VerifyStart(void);
extern SecureFlash_RT SecureFlash_VerifyUpdate(
  const uint8* payload, const uint32 length);
extern SecureFlash_RT SecureFlash_VerifyFinish(
  const SecureFlash_PublicKey* pubKey, const SecureFlash_SignBuff* sigBuff);

extern uint32 SecureFlash_GetVersionInfo(void);

extern SecureFlash_RT SecureFlash_SetCallback(const SecureFlash_Callback cbFunc);

#endif /* DUMMY_HAESFM2_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
