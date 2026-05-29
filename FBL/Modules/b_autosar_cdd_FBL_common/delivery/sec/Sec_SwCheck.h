/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Sec_SwCheck.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : CRC, ID-based sw integrity check function header file         **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.19.0    30-Jul-2021   JYS          Redmine #29874                        **
** 1.12.0.0  12-Mar-2021   JHLim        Redmine #24088, #23964                **
** 1.9.1.0   23-Jan-2021   JYS          Redmine #27914                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef SEC_SWCHECK_H
#define SEC_SWCHECK_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "Fbl_Cfg.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
/* Sec module error list */
#define SEC_E_HW_FAILURE                                                    (1U)
#define SEC_E_SW_FAILURE                                                    (2U)
#define SEC_E_ALIGN_ERROR                                                   (3U)
#define SEC_E_FORBIDDEN                                                     (4U)
#define SEC_E_OUT_OF_RANGE                                                  (5U)
#define SEC_E_TOOLBOX_NOT_LOADED                                            (6U)
#define SEC_E_INVALID_PARAMETER                                             (7U)
#define SEC_E_BAD_CRC                                                       (8U)
#define SEC_E_INCOMPATIBLE                                                  (9U)
#define SEC_E_EEPROM_ERROR                                                 (10U)
#define SEC_E_NOT_ENOUGH_MEM                                               (11U)
#define SEC_E_BUSY                                                         (12U)
#define SEC_E_SEC_ACCESS_DENIED                                            (13U)

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

extern Std_ReturnType Sec_CheckModuleValidity(uint8 moduleId);
extern const Fbl_SwModule* Sec_GetSoftwareModuleById(const uint8 swModuleId);
extern const Fbl_SwModuleSubInfo* Sec_GetSoftwareModuleSubInfoById(const uint8 swModuleId);
extern uint8 Sec_GetSoftwareModuleBlkByUnit(const uint32 swUnit);
extern const Fbl_BlockArea* Sec_GetSwMemBlkArea(void);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* SEC_SWCHECK_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
