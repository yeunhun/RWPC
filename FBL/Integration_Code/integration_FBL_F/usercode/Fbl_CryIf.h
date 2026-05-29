/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fbl_CryIf.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Variable and functions affected when creating a library       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     12-Mar-2021   JHLim        Initial version                       **
*******************************************************************************/

#ifndef FBL_CRYIF_H
#define FBL_CRYIF_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Fbl_Config.h"
#include "Fbl_Crypto.h"
/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/

/******************************************************************************
**                        Global Function Declaration                        **
*******************************************************************************/
  
#define BTL_START_SEC_USER_CODE
#include "Btl_MemMap.h"

extern void CryIf_PrngInit(void);

extern void CryIf_PrngReseed(uint8* entropy);

extern boolean CryIf_PrngGetRand(uint8* randomNumberBuffer,
  const uint32 randomNumberLength);

extern boolean CryIf_KeyGenerate(uint8* seed, uint8* key);

extern boolean CryIf_Sha(uint32 hashAlgorithm, const uint8* data,
  uint32 dataLength, uint8* digest);

extern boolean CryIf_ShaStart(uint32 hashAlgorithm);

extern boolean CryIf_ShaUpdate(uint32 hashAlgorithm,
  const uint8* data, uint32 dataLength);
  
extern boolean CryIf_ShaFinish(uint32 hashAlgorithm, uint8* digest);

extern boolean CryIf_RsaPkcs1v15VerifyStart(const uint8* signature,
  const uint8* modulus, uint32 exponent);
  
extern boolean CryIf_RsaPkcs1v15VerifyUpdate(void);

extern boolean CryIf_RsaPkcs1v15VerifyFinish(uint32 hashAlgorithm,
  const uint8* digset);

extern Std_ReturnType CryIf_SFDecryptStart(uint8* iv, const uint8* decKey,
  const uint8 decKeyLen, const uint8* macOfDecKey, const uint8* macKey,
  const uint8 macKeyLen);

extern Std_ReturnType CryIf_SFDecryptUpdate(uint8* out, const uint8* in,
  const uint32 inLen);

extern Std_ReturnType CryIf_SFDecryptFinish(uint32* totalLen);

extern Std_ReturnType CryIf_SFVerifyStart(void);

extern Std_ReturnType CryIf_SFVerifyUpdate(const uint8* payload, uint32 length);

extern Std_ReturnType CryIf_SFVerifyFinish(uint8* modulus, uint32 exponent,
  uint8* sigBuff);

extern Std_ReturnType CryIf_HsmInit(void);

extern Std_ReturnType CryIf_HsmTempStop(void);

extern Std_ReturnType CryIf_HsmRestart(void);

extern Std_ReturnType CryIf_DeriveKey(uint16 pskIndex, uint32 dkLen,
  const uint8* password, uint32 pLen, const uint8* salt, uint32 sLen,
  uint32 icount, uint8* dk);
  
#define BTL_STOP_SEC_USER_CODE
#include "Btl_MemMap.h"

#endif /* FBL_CRYIF_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
