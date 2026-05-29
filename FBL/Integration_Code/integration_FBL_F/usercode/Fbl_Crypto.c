/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fbl_Crypto.c                                                  **
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

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Fbl_Crypto.h"
#include "Util.h"

#if (FBL_USE_HAESWLIB_PRNG == STD_ON)
#include "Hmg_Prng.h"
#endif

#if (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SEEDKEY)
#include "Sec_Seedkey.h"
#elif (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_ADVANCED_SEEDKEY)
#include "HKMC_ASK_Server.h"
#endif

#if (FBL_USE_SHA160 == STD_ON)
#include "Hmg_Sha160.h"
#endif
#if (FBL_USE_SHA256 == STD_ON)
#include "Hmg_Sha256.h"
#endif
#if (FBL_USE_SECURE_FLASH == STD_ON) || (FBL_USE_SECURE_ACCESS == STD_ON)
#include "Hmg_Pkcs1.h"
#endif

#if (FBL_USE_HAE_HSM == STD_ON)
#include "Hsm_HostAPI.h"
#include "CryptoService_Pbkdf2.h"
#include "SecurityApp_Rng.h"
#include "WdgIf.h"
#endif

#if (FBL_USE_AUT_HSM == STD_ON)
#include "Hsm_AutIntDriver.h"
#endif

#if (FBL_SECURE_FLASH_VERSION == FBL_SF_VER_2_0)
#include "HKMC_SecureFlash2.h"
#endif

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#define HAE_HSM_WAIT_RESP_TIMEOUT                                     (5000000U)

/*******************************************************************************
**                              Check Validity                                **
*******************************************************************************/

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/
#define BTL_START_SEC_VAR_INIT
#include "Btl_MemMap.h"
#if (FBL_USE_HSM == STD_ON)
boolean Sec_Gbl_HsmInitialized = FALSE;
boolean Sec_Gbl_HsmTempStop = FALSE;
#endif

#define BTL_STOP_SEC_VAR_INIT
#include "Btl_MemMap.h"

#define BTL_START_SEC_SVAR_NO_INIT
#include "Btl_MemMap.h"

#if (FBL_USE_HAESWLIB_PRNG == STD_ON)
static HmgPrngCtx Sec_Gdt_HaePrngCtx;
#endif

#if (FBL_USE_SECURE_FLASH == STD_ON) || (FBL_USE_SECURE_ACCESS == STD_ON) 
static HmgRsaSliceCtx Sec_Gdt_HmgRsaSliceCtx;
#endif

#if (FBL_USE_SHA160 == STD_ON)
static HmgSha160Ctx Sec_Gdt_HmgSha160Ctx;
#endif

#if (FBL_USE_SHA256 == STD_ON)
static HmgSha256Ctx Sec_Gdt_HmgSha256Ctx;
#endif

#define BTL_STOP_SEC_SVAR_NO_INIT
#include "Btl_MemMap.h"


#define BTL_START_SEC_USER_CODE
#include "Btl_MemMap.h"

boolean Crypto_Aut_Rand(uint8* randomNumberBuffer,
  const uint32 randomNumberLength)
{
  boolean Lbl_RetCrypto = 1U; /* SEEDKEY_FAIL */
  uint32 Lu32_UtilRandomNumber;
  uint8 Lau8_RandomNumber[SEC_SEEDKEY_SEED_LEN]={0,};
  if (randomNumberBuffer != NULL)
  {
    /* Length of seed must be 4-Byte */
    if (randomNumberLength == SEC_SEEDKEY_SEED_LEN)  
    {
      Lu32_UtilRandomNumber = Util_GetRandomNo(0xFFFFFFFFUL);
      Util_32To8by4(Lu32_UtilRandomNumber, &Lau8_RandomNumber[0]);
      Lu32_UtilRandomNumber = Util_GetRandomNo(0xFFFFFFFFUL);
      Util_32To8by4(Lu32_UtilRandomNumber, &Lau8_RandomNumber[4]);

      (void)Util_Memcpy(randomNumberBuffer,Lau8_RandomNumber,SEC_SEEDKEY_SEED_LEN);

      Lbl_RetCrypto = 0U; /* SEED_OK */
    }
   }

  return Lbl_RetCrypto;
}

void Crypto_Hae_PrngInit(void)
{
  #if (FBL_USE_HAESWLIB_PRNG == STD_ON)
  /* Autoever PRNG initialization */
  Hmg_PrngInit(&Sec_Gdt_HaePrngCtx);
  #endif
}

void Crypto_Hae_PrngReseed(uint8* entropy)
{
  #if (FBL_USE_HAESWLIB_PRNG == STD_ON)
  Hmg_PrngReseed(&Sec_Gdt_HaePrngCtx, entropy);
  #endif
}

boolean Crypto_Hae_PrngGetRand(uint8* randomNumberBuffer,
  const uint32 randomNumberLength)
{
  boolean Lbl_RetCrypto = 1U; /* HMG_FAILURE */
  #if (FBL_USE_HAESWLIB_PRNG == STD_ON)
  Lbl_RetCrypto = Hmg_PrngGetRand(&Sec_Gdt_HaePrngCtx,
    randomNumberBuffer, randomNumberLength);
  #endif
  return Lbl_RetCrypto;
}

boolean Crypto_HaeAdv_ASKKeyGenerate(uint8* seed, uint8* key)
{
  boolean Lbl_RetCrypto = 1U; /* SEEDKEY_FAIL */
  #if (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_ADVANCED_SEEDKEY)
  Lbl_RetCrypto = (boolean)ASK_KeyGenerate((const uint8*)seed, key);
  #endif
  return Lbl_RetCrypto;
}

boolean Crypto_Hae_Sha(uint32 hashAlgorithm, const uint8* data,
  uint32 dataLength, uint8* digest)
{
  boolean Lbl_RetCrypto = 1U; /* HMG_FAILURE */

  if (hashAlgorithm == FBL_SA_HASH_SHA160)
  {
    #if (FBL_USE_SHA160 == STD_ON)
    Lbl_RetCrypto = Hmg_Sha160(digest, data, dataLength);
    #endif
  }
  else if (hashAlgorithm == FBL_SA_HASH_SHA256)
  {
    #if (FBL_USE_SHA256 == STD_ON)
    Lbl_RetCrypto = Hmg_Sha256(digest, data, dataLength);
    #endif
  }
  else
  {
  }
  return Lbl_RetCrypto;
}

boolean Crypto_Hae_ShaStart(uint32 hashAlgorithm)
{
  boolean Lbl_RetCrypto = 1U; /* HMG_FAILURE */

  if (hashAlgorithm == FBL_SA_HASH_SHA160)
  {
    #if (FBL_USE_SHA160 == STD_ON)
    Lbl_RetCrypto = Hmg_Sha160Start(&Sec_Gdt_HmgSha160Ctx);
    #endif
  }
  else if (hashAlgorithm == FBL_SA_HASH_SHA256)
  {
    #if (FBL_USE_SHA256 == STD_ON)
    Lbl_RetCrypto = Hmg_Sha256Start(&Sec_Gdt_HmgSha256Ctx);
    #endif
  }
  else
  {
  }

  return Lbl_RetCrypto;
}

boolean Crypto_Hae_ShaUpdate(uint32 hashAlgorithm, const uint8* data, 
  uint32 dataLength)
{
  boolean Lbl_RetCrypto = 1U; /* HMG_FAILURE */

  if (hashAlgorithm == FBL_SA_HASH_SHA160)
  {
    #if (FBL_USE_SHA160 == STD_ON)
    Lbl_RetCrypto = Hmg_Sha160Update(&Sec_Gdt_HmgSha160Ctx,
      data, dataLength);
    #endif
  }
  else if (hashAlgorithm == FBL_SA_HASH_SHA256)
  {
    #if (FBL_USE_SHA256 == STD_ON)
    Lbl_RetCrypto = Hmg_Sha256Update(&Sec_Gdt_HmgSha256Ctx,
      data, dataLength);
    #endif
  }
  else
  {
  }

  return Lbl_RetCrypto;
}

boolean Crypto_Hae_ShaFinish(uint32 hashAlgorithm, uint8* digest)
{
  boolean Lbl_RetCrypto = 1U; /* HMG_FAILURE */

  if (hashAlgorithm == FBL_SA_HASH_SHA160)
  {
    #if (FBL_USE_SHA160 == STD_ON)
    Lbl_RetCrypto = Hmg_Sha160Finish(&Sec_Gdt_HmgSha160Ctx, digest);
    #endif
  }
  else if (hashAlgorithm == FBL_SA_HASH_SHA256)
  {
    #if (FBL_USE_SHA256 == STD_ON)
    Lbl_RetCrypto = Hmg_Sha256Finish(&Sec_Gdt_HmgSha256Ctx, digest);
    #endif
  }
  else
  {
  }

  return Lbl_RetCrypto;
}


boolean Crypto_Hae_RsaPkcs1v15VerifyStart(const uint8* signature,
  const uint8* modulus, uint32 exponent)
{
  boolean Lbl_RetCrypto = 1U; /* HMG_FAILURE */

  #if (FBL_USE_SECURE_FLASH == STD_ON) || (FBL_USE_SECURE_ACCESS == STD_ON)
  HmgRsaPublickey Ldt_HmgRsaPublicKey;

  Ldt_HmgRsaPublicKey.modulus = (uint8*)modulus;
  Ldt_HmgRsaPublicKey.exponent = exponent;
  
  Lbl_RetCrypto = Hmg_RsaPkcs1v15VerifyStart(&Sec_Gdt_HmgRsaSliceCtx,
    (uint8*)signature,
    &Ldt_HmgRsaPublicKey);
  #endif

  return Lbl_RetCrypto;
}

boolean Crypto_Hae_RsaPkcs1v15VerifyUpdate(void)
{
  boolean Lbl_RetCrypto = 1U; /* HMG_FAILURE */
  #if (FBL_USE_SECURE_FLASH == STD_ON) || (FBL_USE_SECURE_ACCESS == STD_ON)
  Lbl_RetCrypto = Hmg_RsaPkcs1v15VerifyUpdate(&Sec_Gdt_HmgRsaSliceCtx);
  #endif
  return Lbl_RetCrypto;
}

boolean Crypto_Hae_RsaPkcs1v15VerifyFinish(uint32 hashAlgorithm, const uint8* digset)
{
  boolean Lbl_RetCrypto = 1U; /* HMG_FAILURE */

  #if (FBL_USE_SECURE_FLASH == STD_ON) || (FBL_USE_SECURE_ACCESS == STD_ON)
  if (hashAlgorithm == FBL_SA_HASH_SHA160)
  {
    #if (FBL_USE_SHA160 == STD_ON)
    Lbl_RetCrypto = Hmg_RsaPkcs1v15VerifyFinish(&Sec_Gdt_HmgRsaSliceCtx,
      (uint8*)digset, HMG_SHA_160);
    #endif
  }
  else if (hashAlgorithm == FBL_SA_HASH_SHA256)
  {
    #if (FBL_USE_SHA256 == STD_ON)
    Lbl_RetCrypto = Hmg_RsaPkcs1v15VerifyFinish(&Sec_Gdt_HmgRsaSliceCtx,
      (uint8*)digset, HMG_SHA_256);
    #endif
  }
  else
  {
  }
  #endif

  return Lbl_RetCrypto;
}

Std_ReturnType Crypto_HaeSfm2_SFDecryptStart(uint8* iv, const uint8* decKey,
  const uint8 decKeyLen, const uint8* macOfDecKey, const uint8* macKey,
  const uint8 macKeyLen)
{
  Std_ReturnType Ldt_ReturnValue = E_NOT_OK;
  #if (FBL_SECURE_FLASH_VERSION == FBL_SF_VER_2_0)
  if (SecureFlash_DecryptStart(iv, decKey, decKeyLen,
    macOfDecKey, macKey, macKeyLen) == RT_SUCCESS)
  {
    Ldt_ReturnValue = E_OK;
  }
  #endif
  return Ldt_ReturnValue;
}

Std_ReturnType Crypto_HaeSfm2_SFDecryptUpdate(uint8* out, const uint8* in,
  const uint32 inLen)
{
  Std_ReturnType Ldt_ReturnValue = E_NOT_OK;
  #if (FBL_SECURE_FLASH_VERSION == FBL_SF_VER_2_0)
  if (SecureFlash_DecryptUpdate(out, in, inLen) == RT_SUCCESS)
  {
    Ldt_ReturnValue = E_OK;
  }
  #endif
  return Ldt_ReturnValue;
}

Std_ReturnType Crypto_HaeSfm2_SFDecryptFinish(uint32* totalLen)
{
  Std_ReturnType Ldt_ReturnValue = E_NOT_OK;
  #if (FBL_SECURE_FLASH_VERSION == FBL_SF_VER_2_0)
  if (SecureFlash_DecryptFinish(totalLen) == RT_SUCCESS)
  {
    Ldt_ReturnValue = E_OK;
  }
  #endif
  return Ldt_ReturnValue;
}

Std_ReturnType Crypto_HaeHsm_DriverInitialize(void)
{
  Std_ReturnType Ldt_ReturnValue = E_NOT_OK;
  #if (FBL_USE_HAE_HSM == STD_ON)
  /*The HSM mode should be chagned to polling mode (See HSM 2.0 Target Manual)*/
  HSM_DisableInterruptService();
  Ldt_ReturnValue = HSM_DriverInitialize();
  if(Ldt_ReturnValue == E_OK)
  {
    Sec_Gbl_HsmInitialized=TRUE;
  }
  #endif
  return Ldt_ReturnValue;
}

Std_ReturnType Crypto_AutHsm_DriverInitialize(void)
{
  Std_ReturnType Ldt_ReturnValue = E_NOT_OK;
  #if (FBL_USE_AUT_HSM == STD_ON)
  Ldt_ReturnValue= Hsm_Init();
  if(Ldt_ReturnValue == E_OK)
  {
    Sec_Gbl_HsmInitialized=TRUE;
  }
  #endif
  return Ldt_ReturnValue;
}

Std_ReturnType Crypto_HaeHsm_TempStop(void)
{
  Std_ReturnType Ldt_ReturnValue = E_NOT_OK;
  #if (FBL_USE_HAE_HSM == STD_ON)
  if(Sec_Gbl_HsmInitialized == TRUE)
  {
    if(HSM_CheckHsmTempStopState() == TRUE)
    {
      Ldt_ReturnValue = E_OK;
    }
    else
    {
      Ldt_ReturnValue = HSM_TempStop();
    }
  }
  #endif
  return Ldt_ReturnValue;
}

Std_ReturnType Crypto_HaeHsm_Restart(void)
{
  Std_ReturnType Ldt_ReturnValue = E_NOT_OK;
  #if (FBL_USE_HAE_HSM == STD_ON)
  if(Sec_Gbl_HsmInitialized == TRUE)
  {
    Ldt_ReturnValue = HSM_Restart();
  }
  #endif
  return Ldt_ReturnValue;
}

Std_ReturnType Crypto_AutHsm_TempStop(void)
{
  Std_ReturnType Ldt_ReturnValue = E_NOT_OK;
  #if (FBL_USE_AUT_HSM == STD_ON)
  if(Sec_Gbl_HsmInitialized == TRUE)
  {
    #if (FBL_SUPPORT_MCU == FBL_MCU_SPC58X)
    Ldt_ReturnValue = Hsm_ControlPIT(HSM_FALSE);
    #elif (FBL_SUPPORT_MCU == FBL_MCU_RH850F1KM)
    Ldt_ReturnValue = Hsm_ControlForFlash(HSM_TRUE);
    #endif
  }  
  #endif
  return Ldt_ReturnValue;
}

Std_ReturnType Crypto_AutHsm_Restart(void)
{
  Std_ReturnType Ldt_ReturnValue = E_NOT_OK;
  #if (FBL_USE_AUT_HSM == STD_ON)
  if(Sec_Gbl_HsmInitialized == TRUE)
  {
    #if (FBL_SUPPORT_MCU == FBL_MCU_SPC58X)
    Ldt_ReturnValue = Hsm_ControlPIT(HSM_TRUE);
    #elif (FBL_SUPPORT_MCU == FBL_MCU_RH850F1KM)
    Ldt_ReturnValue = Hsm_ControlForFlash(HSM_FALSE);
    #endif
  }
  #endif
  return Ldt_ReturnValue;
}

Std_ReturnType Crypto_HaeHsm_PrngGetRand(uint8* randomNumberBuffer,
  const uint32 randomNumberLength)
{
  Std_ReturnType Ldt_ReturnValue = E_NOT_OK;
  #if (FBL_USE_HAE_HSM == STD_ON)
  if(Sec_Gbl_HsmInitialized == TRUE)
  {
    /*The HSM internally uses the TRNG seed as the initial seed of PRNG*/
    Ldt_ReturnValue = HSM_PseudoRandomGenerate(randomNumberBuffer, randomNumberLength);
  }
  #endif
  return Ldt_ReturnValue;
}

Std_ReturnType Crypto_AutHsm_PrngGetRand(uint8* randomNumberBuffer,
  const uint32 randomNumberLength)
{
  Std_ReturnType Ldt_ReturnValue = E_NOT_OK;
  #if (FBL_USE_AUT_HSM == STD_ON)
  if(Sec_Gbl_HsmInitialized == TRUE)
  {
    /*The HSM internally uses the TRNG seed as the initial seed of PRNG*/
    Ldt_ReturnValue = Hsm_PrngGen(FALSE, NULL, randomNumberBuffer, randomNumberLength);
  }
  #endif
  return Ldt_ReturnValue;
}

Std_ReturnType Crypto_HaeHsm_DeriveKey(uint16 pskIndex, uint32 dkLen,
  const uint8* password, uint32 pLen, const uint8* salt, uint32 sLen,
  uint32 icount, uint8* dk)
{
  Std_ReturnType Ldt_ReturnValue = E_NOT_OK;
  #if (FBL_USE_HAE_HSM == STD_ON)
  HSMAPI_CTX_t Ldt_HsmPbkdf2Ctx;
	uint32 Lu32_Timeout;
	
  if(Sec_Gbl_HsmInitialized == TRUE)
  {
    if (HSM_Pbkdf2Start(&Ldt_HsmPbkdf2Ctx, pskIndex) == E_OK)
    {
      if (HSM_Pbkdf2Update(&Ldt_HsmPbkdf2Ctx,
        pskIndex, dkLen, password, pLen, salt, sLen, icount) == E_OK)
      {
        Lu32_Timeout = 0;
        do
        {
          Ldt_ReturnValue = HSM_WaitResp(Ldt_HsmPbkdf2Ctx.jobId);
          if (Ldt_ReturnValue != HSM_E_WAIT)
          {
            break;
          }
          else
          {
            /* Trigger watchdog */
            WdgIf_SchdTrigger(WDGIF_LONG_TRIGGER);
          }
          Lu32_Timeout++;
        } while (Lu32_Timeout < HAE_HSM_WAIT_RESP_TIMEOUT);

        if (Ldt_ReturnValue == E_OK)
        {
          Ldt_ReturnValue = HSM_Pbkdf2Finish(&Ldt_HsmPbkdf2Ctx, dkLen, dk);
        }
        else
        {
          HSM_CancelJob(Ldt_HsmPbkdf2Ctx.jobId);
        }
      }
    }
  }
  #endif
  return Ldt_ReturnValue;
}

Std_ReturnType Crypto_AutHsm_DeriveKey(uint16 pskIndex, uint32 dkLen,
  const uint8* password, uint32 pLen, const uint8* salt, uint32 sLen,
  uint32 icount, uint8* dk)
{
  Std_ReturnType Ldt_ReturnValue = E_NOT_OK;
  #if (FBL_USE_AUT_HSM == STD_ON)
  Hsm_ErrType LddRetHsm;
  LddRetHsm = Hsm_Pbkdf2Init(FALSE, NULL_PTR, pskIndex, icount);
  
  if(Sec_Gbl_HsmInitialized == TRUE)
  {
    if (LddRetHsm == HSM_NO_ERROR)
    {
      LddRetHsm = Hsm_Pbkdf2Update(FALSE, NULL_PTR,
        NULL_PTR,
        0,
        salt,
        sLen);
    }

    if (LddRetHsm == HSM_NO_ERROR)
    {
      LddRetHsm = Hsm_Pbkdf2Finish(FALSE, NULL_PTR,
        dk,
        dkLen);
    }

    if (LddRetHsm == HSM_NO_ERROR)
    {
      Ldt_ReturnValue = E_OK;
    }
  }
  #endif
  return Ldt_ReturnValue;
}


#define BTL_STOP_SEC_USER_CODE
#include "Btl_MemMap.h"

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
