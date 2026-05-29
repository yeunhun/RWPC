/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: AppIf.h                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file provides function headers for Application           **
**              interface in Bootloader                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef APPIF_H
#define APPIF_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "Dcm_PCTypes.h"
#include "Fbl_Cfg.h"

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_PJS_CODE
#include "Btl_MemMap.h"

extern Std_ReturnType AppIf_CheckApplValid(void);

extern Std_ReturnType AppIf_CheckExtProgRequest(void);

extern Std_ReturnType AppIf_CheckStayInBoot(void);

extern uint32 AppIf_IndicateStayInBoot(void);

extern void AppIf_ClearStayInBoot(void);

extern void AppIf_CallAppl(void);

extern void AppIf_SetProgConditions(const Fbl_SharedCommonRAM* Lpst_ProgConditions);

extern Std_ReturnType AppIf_GetProgConditions(Fbl_SharedCommonRAM* Lpst_ProgConditions);

#define BTL_STOP_SEC_PJS_CODE
#include "Btl_MemMap.h"

#endif /* APPIF_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
