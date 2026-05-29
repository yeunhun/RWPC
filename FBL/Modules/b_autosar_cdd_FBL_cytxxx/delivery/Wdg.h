/*******************************************************************************
**                                                                            **
**  (C) 2020~21 HYUNDAI AUTRON Co., Ltd.                                      **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Wdg.h                                                         **
**                                                                            **
**  TARGET    : CYTXXX                                                        **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Header file for Wdg.c                                         **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision    Date          By           Description                         **
********************************************************************************
** 1.1.0.0     23-Feb-2021   JHLim        Redmine #23964                      **
** 1.0.0       10-April-2020 JaeHyun      Initial version                     **
*******************************************************************************/

#ifndef WDG_H
#define WDG_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "Platform_Types.h"

/*******************************************************************************
**                                Structures                                  **
*******************************************************************************/
typedef struct
{
  uint16 u16_Password;
  uint16 u16_Reload;
} Wdg_Config_Styp;

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_PJS_CODE
#include "Btl_MemMap.h"

extern void Wdg_Init(uint32 Lu32_TimeoutTime);

extern void Wdg_DeInit(void);

extern void Wdg_Disable(void);

extern void Wdg_SetTimeOutTime(uint32 Lu32_TimeoutTime);

#define BTL_STOP_SEC_PJS_CODE
#include "Btl_MemMap.h"

#define BTL_START_SEC_WDG_RAM_CODE
#include "Btl_MemMap.h"

extern void Wdg_Trigger(void);

#define BTL_STOP_SEC_WDG_RAM_CODE
#include "Btl_MemMap.h"

#endif /* WDG_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/

