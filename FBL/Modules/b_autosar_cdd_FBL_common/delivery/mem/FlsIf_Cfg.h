/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: FlsIf_Cfg.h                                                   **
**                                                                            **
**  TARGET    : TC3XX                                                         **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file provides configuration for FlsIf                    **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.2     23-Sep-2020   JYS          Redmine #25801                        **
** 1.0.1     29-Jul-2020   JYS          Redmine #24231                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef FLSIF_CFG_H
#define FLSIF_CFG_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "Btl_LinkerSymbols.h"
#include "WdgIf.h"
#include "Fls.h"

/*******************************************************************************
**                           Data Types                                       **
*******************************************************************************/
typedef struct {
  const Mem_Header_Styp * pst_FlsHeader;
  Mem_PositionType        dt_StartAddress;
  Mem_PositionType        dt_EndAddress;
  Mem_SizeType            dt_AlignedSize;
  Mem_SizeType            dt_EraseSize;
} FlsIf_DrvMemoryMap_Styp;

/*******************************************************************************
**                           Macro Definition                                 **
*******************************************************************************/
/* Major version number / interface */
#define FLSIF_VERSION_MAJOR                                              (0x01u)
/* Minor version number / internal */
#define FLSIF_VERSION_MINOR                                              (0x00u)
/* Bugfix / dt_PatchLevel */
#define FLSIF_VERSION_PATCH                                              (0x00u)

/*******************************************************************************
**                        FCL ROM TO RAM Address                              **
*******************************************************************************/
#define FLSIF_CFLS_ROM_ADDRESS              ((uint8 *)&FlsIf_Ku8_CodeFlsRomCopy)
#define FLSIF_CFLS_RAM_ADDRESS               ((uint8 *)&FlsIf_Kst_CodeFlsHeader)
#define FLSIF_CFLS_SIZE                        ((uint32)&FlsIf_Kpu32_FlsDrvSize)

/*******************************************************************************
**                     FLASH DRIVER INITIALIZE PARAMETER                      **
*******************************************************************************/
#define FLSIF_SYSTEM_FREQUENCY                                            (160u)
#define FLSIF_AUTH_ID_0                                            (0XFFFFFFFFu)
#define FLSIF_AUTH_ID_1                                            (0XFFFFFFFFu)
#define FLSIF_AUTH_ID_2                                            (0XFFFFFFFFu)
#define FLSIF_AUTH_ID_3                                            (0XFFFFFFFFu)
#define FLSIF_WDG_TRIGGER_FUNC                           (WdgIf_Ram_SchdTrigger)

/* Support for CFLASH and DFLASH support macros */
#define FLSIF_USE_DFLASH                                                 STD_OFF
#define FLSIF_USE_CFLASH                                                  STD_ON
#define FLSIF_ADDR_ALIGN_LEN_VALIDATION                                  STD_OFF
#define FLSIF_DFLASH_HEADER_ADDRESS                                         NULL
#define FLSIF_DFLS_VERSION                                        ((uint8)0x01u)
#define FLSIF_DFLS_MASKTYPE                                       ((uint8)0x01u)
#define FLSIF_DFLS_CPUTYPE                                        ((uint8)0x01u)
#define FLSIF_CFLASH_HEADER_ADDRESS   \
  ((const Mem_Header_Styp *)&Fls_Kst_CodeFlashHeader)
#define FLSIF_CFLS_VERSION                                        ((uint8)0x01u)
#define FLSIF_CFLS_MASKTYPE                                       ((uint8)0x01u)
#define FLSIF_CFLS_CPUTYPE                                        ((uint8)0x01u)

/*******************************************************************************
**                        Structure Definition                                **
********************************************************************************
- None
*******************************************************************************/

 /******************************************************************************
 **                          GLOBAL Externs                                   **
 ******************************************************************************/
#define BTL_START_SEC_CONST
#include "Btl_MemMap.h"

extern const FlsIf_DrvMemoryMap_Styp
  FlsIf_Kast_DrvMemoryMap[FBL_NUM_OF_MEM_BLOCKS];
  
#define BTL_STOP_SEC_CONST
#include "Btl_MemMap.h"

extern const uint32 * FlsIf_Kpu32_FlsDrvSize;
extern const uint8 FlsIf_Ku8_CodeFlsRomCopy;
extern const Mem_Header_Styp  FlsIf_Kst_CodeFlsHeader;

#endif /* FLSIF_CFG_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
