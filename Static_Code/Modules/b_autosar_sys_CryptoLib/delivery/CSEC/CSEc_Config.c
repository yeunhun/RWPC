/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CSEc_Config.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Hsm (Hardware Security Module)                                **
**                                                                            **
**  PURPOSE   : Implementation file for S32K CSEc                             **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     13-May-2019   Sinil        Initial version                       **
*******************************************************************************/

/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CSEc_Config.h"
#include "CSEc_Driver.h"

/*******************************************************************************
**                       Global Data                                          **
*******************************************************************************/
#if (CRYPTOLIB_SUPORT_HSM_CSEC == STD_ON)
#define CSEC_START_SEC_CONST_32
#include "Csec_MemMap.h"

/* CSEC_TIMEOUT_DURATION */
const uint32 Csec_TimeOutDuration = CSEC_TIMEOUT_DURATION;

/* CSEC_SECURE_BOOT_SIZE */
const uint32 Csec_SecureBootSize = CSEC_SECURE_BOOT_SIZE;

#define CSEC_STOP_SEC_CONST_32
#include "Csec_MemMap.h"

#define CSEC_START_SEC_CONST_8
#include "Csec_MemMap.h"

/* CSEC_FLASH_KEY_SIZE */
const uint8 Csec_FlashKeySize = CSEC_FLASH_KEY_SIZE;

/* CSEC_SECURITY_FLAG_EXTENSION */
const uint8 Csec_SecurityFlagExtension = CSEC_SECURITY_FLAG_EXTENSION;

/* CSEC_FLEXRAM_LOAD_OPTION */
const uint8 Csec_FlexRAMLoadOption = CSEC_FLEXRAM_LOAD_OPTION;

/* CSEC_EEPROM_DATA_SET_SIZE */
const uint8 Csec_EepromDataSetSize = CSEC_EEPROM_DATA_SET_SIZE;

/* CSEC_EEPROM_BACKUP_SIZE */
const uint8 Csec_EepromBackupSize = CSEC_EEPROM_BACKUP_SIZE;

/* CSEC_SECURE_BOOT_APPLY */
const uint8 Csec_SecureBootApply = CSEC_SECURE_BOOT_APPLY;

/* CSEC_SECURE_BOOT_FLAVOR */
const uint8 Csec_SecureBootFlavor = CSEC_SECURE_BOOT_FLAVOR;

#define CSEC_STOP_SEC_CONST_8
#include "Csec_MemMap.h"
#endif

/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
