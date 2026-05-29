/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Sec_Seedkey.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides function prototype of SeedKey alrorithm              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef SEC_SEEDKEY_H
#define SEC_SEEDKEY_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

extern boolean Sec_SeedKeyGenerate(uint8* pSeed, uint8* pSeedKey);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* SEC_SEEDKEY_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
