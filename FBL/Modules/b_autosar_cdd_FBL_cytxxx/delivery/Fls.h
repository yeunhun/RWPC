/*******************************************************************************
**                                                                            **
**  (C) 2020 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fls.h                                                         **
**                                                                            **
**  TARGET    : CYTXXX                                                        **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Header file for Fls.c                                         **
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

#ifndef FLS_H
#define FLS_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Fls_Cfg.h"
#include "Btl.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#define FLS_VERSION_INTERFACE                                     ((uint8)0x01u)
#define FLS_VERSION_MASKTYPE                                      ((uint8)0x01u)
#define FLS_VERSION_MCUTYPE                                       ((uint8)0x01u)

/* Software version information - only an example!!! */
/* Major version number / interface */
#define FLS_VERSION_MAJOR                                                (0x01u)
/* Minor version number / internal */
#define FLS_VERSION_MINOR                                                (0x00u)
/* Patch version number / dt_PatchLevel */
#define FLS_VERSION_PATCH                                                (0x00u)
#define FLS_SET                                                          (0x01U)
#define FLS_CLEAR                                                        (0x00U)

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/
#define BTL_FLS_START_SEC_HEADER
#include "Btl_MemMap.h"

extern const Mem_Header_Styp Fls_Kst_CodeFlashHeader;

#define BTL_FLS_STOP_SEC_HEADER
#include "Btl_MemMap.h"

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_FLS_START_SEC_CODE
#include "Btl_MemMap.h"

extern void Fls_Init(Mem_Param_Styp *Lpst_FlashParam);

extern void Fls_DeInit(Mem_Param_Styp *Lpst_FlashParam);

extern void Fls_Write(Mem_Param_Styp *Lpst_FlashParam);

extern void Fls_Erase(Mem_Param_Styp* Lpst_FlashParam);

#define BTL_FLS_STOP_SEC_CODE
#include "Btl_MemMap.h"

#endif /* FLS_H */
/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/

