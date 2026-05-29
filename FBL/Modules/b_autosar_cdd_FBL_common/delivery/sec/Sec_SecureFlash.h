/*******************************************************************************
**                                                                            **
**  (C) 2019~2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Sec_SecureFlash.h                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Header file for Secure flashing check                         **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.23.0    27-Dec-2021   JH Lim       R40-Redmine #31776                    **
** 1.19.0.0  27-Jul-2021   JYS          Redmine #29489                        **
** 1.0.2     07-Feb-2020   Sinil        Redmine #21604                        **
** 1.0.1     06-Dec-2019   Sinil        Redmine #20402                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef SEC_SECUREFLASH_H
#define SEC_SECUREFLASH_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "Dcm_Types.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
/* Instance id */
#define SF_INSTANCE_ID                                                ((uint8)0)
/*******************************************************************************
**                     Callback Notifications                                 **
*******************************************************************************/

/* Service Id of Secure flash mainfunction */
#define SF_MAIN_FUNCTION_SID                                       ((uint8)0x00)
/*******************************************************************************
**                      DET ERROR CODES                                       **
*******************************************************************************/
/* SecureFlashIndex Failed */
#define SF_E_SFINDEX                                               ((uint8)0x00)

/* DeriveSecureFlashKey Failed */
#define SF_E_DERIVESFKEY                                           ((uint8)0x01)

/* CRC verification/module validity Failed */
#define SF_E_CRCVERIFICATION                                       ((uint8)0x02)

/* Signature Verification Failed */
#define SF_E_CHECKFLASHIMAGE                                       ((uint8)0x03)

/* Read Signature Failed */
#define SF_E_READSIGNATURE                                         ((uint8)0x04)

/* Write SecurityKey Failed */
#define SF_E_WRITE_SK                                              ((uint8)0x05)

/* Secure Flash state Failed */
#define SF_E_SFSTATECHECK                                          ((uint8)0x06)

/* Secure Flash Version Failed */
#define SF_E_SFVERSIONCHECK                                        ((uint8)0x07)

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

extern Std_ReturnType Signature_CheckDelimiter(const uint8* Ldt_TargetAddress,
  Mem_SizeType Ldt_Length);

extern void Sec_SecureFlashInit(void);

extern Std_ReturnType Sec_SecureFlashCheckStart(uint8 Lu8_BlockId,
  Dcm_NegativeResponseCodeType *Lpdt_ErrorCode,
  Dcm_OpStatusType Ldt_OpStatus);

extern Std_ReturnType Sec_SecureFlashDeriveKey(const uint8* Lpu8_MetaDataBuffer,
  Dcm_NegativeResponseCodeType *Lpdt_ErrorCode,
  Dcm_OpStatusType Ldt_OpStatus);

extern Std_ReturnType Sec_SecureFlashDecryptStart(void);

extern Std_ReturnType Sec_SecureFlashDecryptUpdate(const uint8* Lpu8_InputData,
  uint8* Lpu8_OutputData, uint32 Lu32_DataLength);

extern Std_ReturnType Sec_SecureFlashDecryptFinish(uint32* Lpu32_TotalLength);

extern Std_ReturnType Sec_SecureFlashCheckGetStatus(
  uint16* Lpu16_Data,
  Dcm_NegativeResponseCodeType* Lpdt_ErrorCode);

extern void Sec_SecureFlashMainFunction(void);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* SEC_SECUREFLASH_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
