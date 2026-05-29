/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fbl_Dcmpr.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Header file for Dcmpr.c                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef FBL_DCMPR_H
#define FBL_DCMPR_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Platform_Types.h"

/*******************************************************************************
**                               Enumerations                                 **
*******************************************************************************/

typedef enum
{
  FBL_DECOMP_IDLE,
  FBL_DECOMP_BLOCK_REMAINED,
  FBL_DECOMP_BLOCK_FINISHED,
  FBL_DECOMP_BLOCK_ALL_FINISHED,
  FBL_DECOMP_BLOCK_ERROR
} Stm_Decomp_Status_Etyp;


/*******************************************************************************
**                                Structures                                  **
*******************************************************************************/
typedef struct
{
  /* Flag to determine start of decompression */
  boolean bl_first;

  /* One byte value with compressionMethod(0xF0) and encryptingMethod(0x0F) */
  uint8 Lu8_dataFormatIdentifier;

  /* The length of the entire compressed input data */
  uint32 u32_totalInputDataLength;
} Fbl_DecompDataContext;

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_USER_CODE
#include "Btl_MemMap.h"

extern Fbl_DecompDataContext Fbl_GstDecompressContext;
extern void Fbl_DecompressInit(uint8 Lu8_DataFormatIdentifier,
  uint32 Lu32_TotalInputDataLength);

extern Std_ReturnType Fbl_DecompExpandData(const uint8* Lpu8_SourceDataPtr,
  uint32 Lu32_Length, uint32 Lu32_TargetAddr);

#define BTL_STOP_SEC_USER_CODE
#include "Btl_MemMap.h"

#endif /* FBL_DCMPR_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
