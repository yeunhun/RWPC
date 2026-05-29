/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CSEc_Config.h                                                 **
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

#ifndef CSEC_CONFIG_H
#define CSEC_CONFIG_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
**                       Global Data                                          **
*******************************************************************************/
extern const uint32 Csec_TimeOutDuration;

extern const uint8 Csec_FlashKeySize;

extern const uint8 Csec_SecurityFlagExtension;

extern const uint8 Csec_FlexRAMLoadOption;

extern const uint8 Csec_EepromDataSetSize;

extern const uint8 Csec_EepromBackupSize;

extern const uint8 Csec_SecureBootApply;

extern const uint32 Csec_SecureBootSize;

extern const uint8 Csec_SecureBootFlavor;

#endif /* CSEC_CONFIG_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
