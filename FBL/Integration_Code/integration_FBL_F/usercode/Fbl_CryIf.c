/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fbl_CryIf.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file is crypto interface layer for calling several       **
**              crypto libraries. This file is not dependent on each library  **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     12-Mar-2021   JHLim        Initial version                       **
*******************************************************************************/


/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Fbl_CryIf.h"
#include "Sec_SeedKey.h"
#include "WdgIf.h"
/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/


/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
  
#define BTL_START_SEC_USER_CODE
#include "Btl_MemMap.h"

void CryIf_PrngInit(void)
{
  #if ((FBL_SECURITY_ACCESS_LEVEL != FBL_SA_SEEDKEY) && (FBL_SUPPORT_HSM == FBL_HSM_NONE))
  Crypto_Hae_PrngInit();
  #endif
}

void CryIf_PrngReseed(uint8* entropy)
{
  /*Using Hae_CryptoLib PRNG when No HSM && NO SeedKey*/
  #if ((FBL_SECURITY_ACCESS_LEVEL != FBL_SA_SEEDKEY) && (FBL_SUPPORT_HSM == FBL_HSM_NONE))
  Crypto_Hae_PrngReseed(entropy);
  #endif
}

boolean CryIf_PrngGetRand(uint8* randomNumberBuffer,
  const uint32 randomNumberLength)
{
  boolean Lbl_RetCrypto = 1U; /* SEEDKEY_FAIL */
  #if (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SEEDKEY)
  /*Using internal timer tick, Target : SeedKey*/
  Lbl_RetCrypto = Crypto_Aut_Rand(randomNumberBuffer,randomNumberLength);
  #elif (FBL_SUPPORT_HSM == FBL_HSM_NONE)
  /*Using Hae-CryptoLib's PRNG when HSM is not applied, Target : Advanced SeedKey & SecureAccess */
  Lbl_RetCrypto = Crypto_Hae_PrngGetRand(randomNumberBuffer,randomNumberLength);
  #elif (FBL_SUPPORT_HSM == FBL_HSM_AUTHSM_1_0)
  /*Using HSM PRNG(First seed is TRNG) when AutHSM1.0 is applied, Target : Advanced SeedKey & SecureAccess */
  Lbl_RetCrypto = Crypto_AutHsm_PrngGetRand(randomNumberBuffer,randomNumberLength);
  #elif (FBL_SUPPORT_HSM == FBL_HSM_HAEHSM_2_0)
  /*Using HSM PRNG(First seed is TRNG) when HaeHSM2.0 is applied, Target : Advanced SeedKey & SecureAccess */
  Lbl_RetCrypto = Crypto_HaeHsm_PrngGetRand(randomNumberBuffer,randomNumberLength);
  #else
  #error "CryIf : Error occur in Security Access RNG";
  #endif
  return Lbl_RetCrypto;
}

boolean CryIf_KeyGenerate(uint8* seed, uint8* key)
{
  boolean Lbl_RetCrypto = 1U; /* SEEDKEY_FAIL */
  #if (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SEEDKEY)
  Lbl_RetCrypto = Sec_SeedKeyGenerate(seed,key);
  #elif (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_ADVANCED_SEEDKEY)
  Lbl_RetCrypto = Crypto_HaeAdv_ASKKeyGenerate(seed,key);
  #endif
  
  return Lbl_RetCrypto;
}

boolean CryIf_Sha(uint32 hashAlgorithm, const uint8* data,
  uint32 dataLength, uint8* digest)
{
  boolean Lbl_RetCrypto = 1U; /* HMG_FAILURE */

  Lbl_RetCrypto = Crypto_Hae_Sha(
		      hashAlgorithm,
		      data,
			    dataLength,
			    digest);

  return Lbl_RetCrypto;
}

boolean CryIf_ShaStart(uint32 hashAlgorithm)
{
  boolean Lbl_RetCrypto = 1U; /* HMG_FAILURE */

  Lbl_RetCrypto = Crypto_Hae_ShaStart(hashAlgorithm);

  return Lbl_RetCrypto;
}

boolean CryIf_ShaUpdate(uint32 hashAlgorithm,
  const uint8* data, uint32 dataLength)
{
  boolean Lbl_RetCrypto = 1U; /* HMG_FAILURE */

  Lbl_RetCrypto = Crypto_Hae_ShaUpdate(hashAlgorithm, data, dataLength);

  return Lbl_RetCrypto;
}

boolean CryIf_ShaFinish(uint32 hashAlgorithm, uint8* digest)
{
  boolean Lbl_RetCrypto = 1U; /* HMG_FAILURE */

  Lbl_RetCrypto = Crypto_Hae_ShaFinish(hashAlgorithm, digest);

  return Lbl_RetCrypto;
}

boolean CryIf_RsaPkcs1v15VerifyStart(const uint8* signature,
  const uint8* modulus, uint32 exponent)
{
  boolean Lbl_RetCrypto = 1U; /* HMG_FAILURE */

  Lbl_RetCrypto= Crypto_Hae_RsaPkcs1v15VerifyStart(signature,modulus,exponent);
  
  return Lbl_RetCrypto;
}

boolean CryIf_RsaPkcs1v15VerifyUpdate(void)
{
  boolean Lbl_RetCrypto = 1U; /* HMG_FAILURE */

  Lbl_RetCrypto= Crypto_Hae_RsaPkcs1v15VerifyUpdate();
  
  return Lbl_RetCrypto;
}

boolean CryIf_RsaPkcs1v15VerifyFinish(uint32 hashAlgorithm, const uint8* digset)
{
  boolean Lbl_RetCrypto = 1U; /* HMG_FAILURE */

  Lbl_RetCrypto = Crypto_Hae_RsaPkcs1v15VerifyFinish(hashAlgorithm, digset);
   
  return Lbl_RetCrypto;
}

Std_ReturnType CryIf_SFDecryptStart(uint8* iv, const uint8* decKey,
  const uint8 decKeyLen, const uint8* macOfDecKey, const uint8* macKey,
  const uint8 macKeyLen)
{
  Std_ReturnType Ldt_ReturnValue = E_NOT_OK;

  Ldt_ReturnValue = Crypto_HaeSfm2_SFDecryptStart(iv,decKey,decKeyLen,macOfDecKey,macKey,macKeyLen);
  
  return Ldt_ReturnValue;
}

Std_ReturnType CryIf_SFDecryptUpdate(uint8* out, const uint8* in,
  const uint32 inLen)
{
  Std_ReturnType Ldt_ReturnValue = E_NOT_OK;

  Ldt_ReturnValue = Crypto_HaeSfm2_SFDecryptUpdate(out,in,inLen);
  
  return Ldt_ReturnValue;
}

Std_ReturnType CryIf_SFDecryptFinish(uint32* totalLen)
{
  Std_ReturnType Ldt_ReturnValue = E_NOT_OK;

  Ldt_ReturnValue = Crypto_HaeSfm2_SFDecryptFinish(totalLen);
 
  return Ldt_ReturnValue;
}

Std_ReturnType CryIf_HsmInit(void)
{
  Std_ReturnType Ldt_ReturnValue = E_NOT_OK;
  #if (FBL_USE_HAE_HSM == STD_ON)
  Ldt_ReturnValue = Crypto_HaeHsm_DriverInitialize();
  #elif (FBL_USE_AUT_HSM == STD_ON)
  Ldt_ReturnValue = Crypto_AutHsm_DriverInitialize();
  #endif
  return Ldt_ReturnValue;
}

Std_ReturnType CryIf_HsmTempStop(void)
{
  Std_ReturnType Ldt_ReturnValue = E_NOT_OK;
  #if (FBL_USE_HAE_HSM == STD_ON)
  Ldt_ReturnValue = Crypto_HaeHsm_TempStop();
  #elif (FBL_USE_AUT_HSM == STD_ON)
  Ldt_ReturnValue = Crypto_AutHsm_TempStop();
  #endif
  return Ldt_ReturnValue;
}

Std_ReturnType CryIf_HsmRestart(void)
{
  Std_ReturnType Ldt_ReturnValue = E_NOT_OK;
  #if (FBL_USE_HAE_HSM == STD_ON)
  Ldt_ReturnValue = Crypto_HaeHsm_Restart();
  #elif (FBL_USE_AUT_HSM == STD_ON)
  Ldt_ReturnValue = Crypto_AutHsm_Restart();
  #endif
  return Ldt_ReturnValue;
}

Std_ReturnType CryIf_DeriveKey(uint16 pskIndex, uint32 dkLen,
  const uint8* password, uint32 pLen, const uint8* salt, uint32 sLen,
  uint32 icount, uint8* dk)
{
  Std_ReturnType Ldt_ReturnValue = E_NOT_OK;
  #if (FBL_USE_HAE_HSM == STD_ON)
  Ldt_ReturnValue = Crypto_HaeHsm_DeriveKey(pskIndex, dkLen,
  password, pLen, salt, sLen, icount, dk);
  #elif (FBL_USE_AUT_HSM == STD_ON)
  Ldt_ReturnValue = Crypto_AutHsm_DeriveKey(pskIndex, dkLen,
  password, pLen, salt, sLen, icount, dk);
  #endif
  return Ldt_ReturnValue;
}

#define BTL_STOP_SEC_USER_CODE
#include "Btl_MemMap.h"

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
