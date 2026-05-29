/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dummy_HaeASK.c                                                **
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
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
/* CryptoLib library dummy header file */
#include "Dummy_HaeASK.h"

/*******************************************************************************
**                        Global Function Definitions                         **
*******************************************************************************/
/* APIs that should not be used when using actual libraries */
/* Dummy function definitions in the CryptoLib library API commonly used in RTSW and FBL */
SEEDKEY_RT ASK_KeyGenerate(const BYTE *seed_buffer_8byte, BYTE *key_buffer_8byte)
{
  return SEEDKEY_FAIL;
}

SEEDKEY_RT ASK_Rand8ByteGenerate(BYTE *seed_buffer_8byte)
{
  return SEEDKEY_FAIL;
}

void ASK_RandInit(unsigned long rand_seed)
{
}

void vGetVersionInfo(VERSION_INFO *pVersionInfo)
{
}

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
