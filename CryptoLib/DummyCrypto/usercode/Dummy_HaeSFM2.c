/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dummy_HaeSFM2.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Dummy HAE library                                             **
**                                                                            **
**  PURPOSE   : Source file for dummy code                                    **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0.0   18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
/* CryptoLib library dummy header file */
#include "Dummy_HaeSFM2.h"

/*******************************************************************************
**                        Global Function Definitions                         **
*******************************************************************************/
/* APIs that should not be used when using actual libraries */
/* Dummy function definitions in the SFM2 library API commonly used in RTSW and FBL */
SecureFlash_RT SecureFlash_DecryptStart(
  uint8* iv, const uint8* decKey, const uint8 decKeyLen,
  const uint8* macOfDecKey, const uint8* macKey, const uint8 macKeyLen)
{
  return RT_FAIL;
}

SecureFlash_RT SecureFlash_DecryptUpdate(
  uint8* out, const uint8* in, const uint32 inLen)
{
  return RT_FAIL;
}

SecureFlash_RT SecureFlash_DecryptFinish(uint32* totalLen)
{
  return RT_FAIL;
}

SecureFlash_RT SecureFlash_VerifyStart(void)
{
  return RT_FAIL;
}

SecureFlash_RT SecureFlash_VerifyUpdate(
  const uint8* payload, const uint32 length)
{
  return RT_FAIL;
}

SecureFlash_RT SecureFlash_VerifyFinish(
  const SecureFlash_PublicKey* pubKey, const SecureFlash_SignBuff* sigBuff)
{
  return RT_FAIL;
}

uint32 SecureFlash_GetVersionInfo(void)
{
  return 0;
}

SecureFlash_RT SecureFlash_SetCallback(const SecureFlash_Callback cbFunc)
{
  return RT_FAIL;
}

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
