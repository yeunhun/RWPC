/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Btl_LinkerSymbols.h                                           **
**                                                                            **
**  TARGET    : TC3XX                                                         **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides linker address tags                                  **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef BTL_LINKERSYMBOLS_H
#define BTL_LINKERSYMBOLS_H

/*******************************************************************************
**                           Macro Definition                                 **
*******************************************************************************/
#define Syst_Gau32_BTLResetSaveData              LD_BTL_RS_ADDR
#define Syst_Gpu32_BTLResetSaveDataSize          LD_BTL_RS_SIZE
#define Syst_Gau32_BTL_APPLResetSaveData         LD_BTL_APPIF_RS_ADDR
#define Syst_Gpu32_BTL_APPLResetSaveDataSize     LD_BTL_APPIF_RS_SIZE

#define FlsIf_Kst_CodeFlsHeader                  FLS_COPY_DEST
#define FlsIf_Ku8_CodeFlsRomCopy                 FLS_COPY_SRC
#define FlsIf_Kpu32_FlsDrvSize                   FLS_COPY_SIZE

#endif /* BTL_LINKERSYMBOLS_H */

/*******************************************************************************
**                    End of File                                             **
*******************************************************************************/
