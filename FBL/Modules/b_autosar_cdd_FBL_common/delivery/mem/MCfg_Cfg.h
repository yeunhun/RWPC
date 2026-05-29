/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Sec.h                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Flash memory configuration                                    **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.2     09-Sep-2020   JYS          Redmine #25546                        **
** 1.0.1     29-Jul-2020   JYS          Redmine #24231                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef MCFG_CFG_H
#define MCFG_CFG_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
/* Header file inclusion for standard types */
#include "Btl.h"
#include "Fbl_Cfg.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
/* Macro when status is erased */
#define MCFG_STS_ERASED                                                  (0x55U)

/* Macro when status is not erased */
#define MCFG_STS_NOT_ERASED                                              (0xAAU)

/* Bootloader software block */
#define MCFG_BTL_SW_BLK_MASK                                      ((uint8)0x01U)

/* Application software block */
#define MCFG_APP_SW_BLK_MASK                                      ((uint8)0x02U)

#define MCFG_APP_SW2_BLK_MASK                                     ((uint8)0x04U)

#define MCFG_APP_SW3_BLK_MASK                                     ((uint8)0x08U)

#define MCFG_APP_SW4_BLK_MASK                                     ((uint8)0x10U)

#define MCFG_APP_SW5_BLK_MASK                                     ((uint8)0x20U)

#define MCFG_APP_SW6_BLK_MASK                                     ((uint8)0x40U)

#define MCFG_APP_SW7_BLK_MASK                                     ((uint8)0x80U)

/* Bootloader software block identifier */
#define MCFG_BTL_SW_BLK_ID                                        ((uint8)0x00U)

/* Application software block identifier */
#define MCFG_APP_SW_BLK_ID                                        ((uint8)0x01U)

#define MCFG_TOTAL_BLK_COUNT_ONE                                  ((uint8)0x01U) 

/*******************************************************************************
**                                Structures                                  **
*******************************************************************************/
/* Data type for flash configuration table */
typedef struct
{
  /* Memory block starting address */
  uint32 u32_MemBlkAddr;

  /* Memory block size */
  uint32 u32_MemBlkSize;

  /* Permission on the Memory block */
  Mem_AccessType dt_MemBlkActType;

  /* Logical block Mask */
  uint8 u8_LogBlkMask;
} MCfg_MemBlkTab_Styp;
 
/* Input index mapping to the logical block number */
typedef struct
{
  /* No of logical block element */
  uint8 u8_NoOfLogBlk;

  /* Logical block identifier */
  uint8 u8_LogBlkId;

  /* Logical blocks available for ID */
  uint8 u8_RsltntLogBlkMask;

} MCfg_IndexToLogBlkMap_Styp; 

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/
#define BTL_START_SEC_CONST
#include "Btl_MemMap.h"

/* External declaration of the flash configuration table */
extern const MCfg_MemBlkTab_Styp MCfg_Kast_MemBlockTable[FBL_NUM_OF_MEM_BLOCKS];

/* Table for mapping of block index to logical block */
extern const MCfg_IndexToLogBlkMap_Styp
  MCfg_Kast_IndexToLogBlkMap[FBL_NUM_OF_MEM_BLOCKS];

/* Table for logical block information */
extern const uint8 MCfg_Kau8_LogicBlk[FBL_NUM_OF_MEM_BLOCKS];
 
#define BTL_STOP_SEC_CONST
#include "Btl_MemMap.h"

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_PJS_CODE
#include "Btl_MemMap.h"

/* Declaration of the MCfg_AddressLengthAlignmentCheck */
Std_ReturnType MCfg_AddressLengthAlignmentCheck(
  uint32 Lu32_TargetAddress,
  uint32 Lu32_Length,
  Mem_AccessType Ldt_AccessType
);

#define BTL_STOP_SEC_PJS_CODE
#include "Btl_MemMap.h"

#endif /* MCFG_CFG_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
