/*******************************************************************************
**                                                                            **
**  (C) 2019~2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: WdgIf.h                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Header file for WdgIf.c                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.1     07-Feb-2020   Sinil        Redmine #21592                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef WDGIF_H
#define WDGIF_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#define WDGIF_LONG_TRIGGER                                                   1u
#define WDGIF_SHORT_TRIGGER                                                  2u
#define WDGIF_ZERO                                                           0u

/*******************************************************************************
**                              Type Definition                               **
*******************************************************************************/
typedef void (*WdgIf_pf_Schd_Type)(void);
typedef void (*Mem_WD_Trigger_Type)(uint8);

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
extern void WdgIf_Ram_SchdTrigger(uint8 Lu8_TrigType);

extern void WdgIf_Init(void);

extern void WdgIf_DeInit(void);

extern void WdgIf_Trigger(void);

extern void WdgIf_SetTimeoutTime(uint32 Lu32_TimeoutTime);

extern void WdgIf_SetTimeoutDefault(void);

extern void WdgIf_ForceReset(void);


extern void WdgIf_SchdTrigger(uint8 Lu8_TrigType);

#endif /* WDGIF_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
