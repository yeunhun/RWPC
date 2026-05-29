/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fbl_Crypto.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : The crypto library is called directly from this file.         **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     12-Mar-2021   JHLim        Initial version                       **
*******************************************************************************/

#ifndef FBL_CRYPTO_H
#define FBL_CRYPTO_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Fbl_Config.h"
/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/


#define BTL_START_SEC_USER_CODE
#include "Btl_MemMap.h"

extern boolean Crypto_Aut_Rand(uint8* randomNumberBuffer,
  const uint32 randomNumberLength);
  
extern void Crypto_Hae_PrngInit(void);

extern void Crypto_Hae_PrngReseed(uint8* entropy);

extern boolean Crypto_Hae_PrngGetRand(uint8* randomNumberBuffer,
  const uint32 randomNumberLength);

extern boolean Crypto_HaeHsm_PrngGetRand(uint8* randomNumberBuffer,
  const uint32 randomNumberLength);

extern boolean Crypto_AutHsm_PrngGetRand(uint8* randomNumberBuffer,
  const uint32 randomNumberLength);
  
extern boolean Crypto_HaeAdv_ASKKeyGenerate(uint8* seed, uint8* key);

extern boolean Crypto_Hae_Sha(uint32 hashAlgorithm, const uint8* data,
  uint32 dataLength, uint8* digest);
  
extern boolean Crypto_Hae_ShaStart(uint32 hashAlgorithm);

extern boolean Crypto_Hae_ShaUpdate(uint32 hashAlgorithm, 
  const uint8* data, uint32 dataLength);
  
extern boolean Crypto_Hae_ShaFinish(uint32 hashAlgorithm, uint8* digest);

extern boolean Crypto_Hae_RsaPkcs1v15VerifyStart(const uint8* signature,
  const uint8* modulus, uint32 exponent);
  
extern boolean Crypto_Hae_RsaPkcs1v15VerifyUpdate(void);

extern boolean Crypto_Hae_RsaPkcs1v15VerifyFinish( uint32 hashAlgorithm,
  const uint8* digset);

extern Std_ReturnType Crypto_HaeSfm2_SFDecryptStart(uint8* iv, const uint8* decKey,
  const uint8 decKeyLen, const uint8* macOfDecKey, const uint8* macKey,
  const uint8 macKeyLen);

extern Std_ReturnType Crypto_HaeSfm2_SFDecryptUpdate(uint8* out, const uint8* in,
  const uint32 inLen);

extern Std_ReturnType Crypto_HaeSfm2_SFDecryptFinish(uint32* totalLen);

extern Std_ReturnType Crypto_HaeSfm2_SFVerifyStart(void);

extern Std_ReturnType Crypto_HaeSfm2_SFVerifyUpdate(const uint8* payload, uint32 length);

extern Std_ReturnType Crypto_HaeSfm2_SFVerifyFinish(uint8* modulus, uint32 exponent,
  uint8* sigBuff);

extern Std_ReturnType Crypto_HaeHsm_DriverInitialize(void);

extern Std_ReturnType Crypto_AutHsm_DriverInitialize(void);

extern Std_ReturnType Crypto_HaeHsm_TempStop(void);

extern Std_ReturnType Crypto_HaeHsm_Restart(void);

extern Std_ReturnType Crypto_AutHsm_TempStop(void);

extern Std_ReturnType Crypto_AutHsm_Restart(void);

extern Std_ReturnType Crypto_HaeHsm_PrngGetRand(uint8* randomNumberBuffer,
  const uint32 randomNumberLength);

extern Std_ReturnType Crypto_HaeHsm_DeriveKey(uint16 pskIndex, uint32 dkLen,
  const uint8* password, uint32 pLen, const uint8* salt, uint32 sLen,
  uint32 icount, uint8* dk);

extern Std_ReturnType Crypto_AutHsm_DeriveKey(uint16 pskIndex, uint32 dkLen,
  const uint8* password, uint32 pLen, const uint8* salt, uint32 sLen,
  uint32 icount, uint8* dk);

  
#define BTL_STOP_SEC_USER_CODE
#include "Btl_MemMap.h"

#endif /* FBL_CRYPTO_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
