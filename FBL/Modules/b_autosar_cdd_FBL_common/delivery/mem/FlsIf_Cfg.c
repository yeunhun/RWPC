/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: FlsIf_Cfg.c                                                   **
**                                                                            **
**  TARGET    : TC3XX                                                         **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides configuration info for FlsIf                         **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.17.0.0  16-Jul-2021   Sungwook     Redmine #29464                        **
** 1.12.0.0  12-Mar-2021   JHLim        Redmine #23964                        **
** 1.0.3     11-Aug-2020   JYS          Redmine #23962                        **
** 1.0.2     29-Jul-2020   JYS          Redmine #24231                        **
** 1.0.1     10-Apr-2020   JaeHyun      Redmine #22713                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "FlsIf.h"
#include "FlsIf_Cfg.h"
#include "Fbl_Cfg.h"

/*******************************************************************************
**                           Macro Definition                                 **
*******************************************************************************/
#define FLSIF_CFLASH_START_ADD                      ((uint32)MAIN_SW_START_ADDR)

#define FLSIF_CFLASH_END_ADD                          ((uint32)MAIN_SW_END_ADDR)

#if ((FBL_SUPPORT_MCU == FBL_MCU_TC23X) || (FBL_SUPPORT_MCU == FBL_MCU_TC29X) || \
	(FBL_SUPPORT_MCU == FBL_MCU_TC38X) || (FBL_SUPPORT_MCU == FBL_MCU_TC39X) || \
	(FBL_SUPPORT_MCU == FBL_MCU_TC36X) || (FBL_SUPPORT_MCU == FBL_MCU_TC37X) || \
	(FBL_SUPPORT_MCU == FBL_MCU_TC33X))
#define FLSIF_CFLASH_ALIGNED_SIZE                                         (256u)
#elif (FBL_SUPPORT_MCU == FBL_MCU_SPC58X)
#define FLSIF_CFLASH_ALIGNED_SIZE                                         (128u)
#elif (FBL_SUPPORT_MCU == FBL_MCU_RH850F1KM)
#define FLSIF_CFLASH_ALIGNED_SIZE                                         (256u)
#elif (FBL_SUPPORT_MCU == FBL_MCU_CYTXXX)
#define FLSIF_CFLASH_ALIGNED_SIZE                                         (256u)
#endif
#define FLSIF_CFLASH_BLK_ERASE_SIZE                                      (0x01u)

/*******************************************************************************
**                        Global Definition                                   **
*******************************************************************************/
#define BTL_START_SEC_CONST
#include "Btl_MemMap.h"

const FlsIf_DrvMemoryMap_Styp FlsIf_Kast_DrvMemoryMap[FBL_NUM_OF_MEM_BLOCKS] =
{
  {
    FLSIF_CFLASH_HEADER_ADDRESS,
    FLSIF_CFLASH_START_ADD,
    FLSIF_CFLASH_END_ADD,
    FLSIF_CFLASH_ALIGNED_SIZE,
    FLSIF_CFLASH_BLK_ERASE_SIZE
  },
  #if (FBL_NUM_OF_MEM_BLOCKS >= 3)
  {
    FLSIF_CFLASH_HEADER_ADDRESS,
    ASW2_START_ADDR,
    ASW2_END_ADDR,
    FLSIF_CFLASH_ALIGNED_SIZE,
    FLSIF_CFLASH_BLK_ERASE_SIZE
  },
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 3) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 4)
  {
    FLSIF_CFLASH_HEADER_ADDRESS,
    ASW3_START_ADDR,
    ASW3_END_ADDR,
    FLSIF_CFLASH_ALIGNED_SIZE,
    FLSIF_CFLASH_BLK_ERASE_SIZE
  },
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 4) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 5)
  {
    FLSIF_CFLASH_HEADER_ADDRESS,
    ASW4_START_ADDR,
    ASW4_END_ADDR,
    FLSIF_CFLASH_ALIGNED_SIZE,
    FLSIF_CFLASH_BLK_ERASE_SIZE
  },
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 5) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 6)
  {
    FLSIF_CFLASH_HEADER_ADDRESS,
    ASW5_START_ADDR,
    ASW5_END_ADDR,
    FLSIF_CFLASH_ALIGNED_SIZE,
    FLSIF_CFLASH_BLK_ERASE_SIZE
  },
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 6) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 7)
  {
    FLSIF_CFLASH_HEADER_ADDRESS,
    ASW6_START_ADDR,
    ASW6_END_ADDR,
    FLSIF_CFLASH_ALIGNED_SIZE,
    FLSIF_CFLASH_BLK_ERASE_SIZE
  },
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 7) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 8)
  {
    FLSIF_CFLASH_HEADER_ADDRESS,
    ASW7_START_ADDR,
    ASW7_END_ADDR,
    FLSIF_CFLASH_ALIGNED_SIZE,
    FLSIF_CFLASH_BLK_ERASE_SIZE
  },
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 8) */
};

#define BTL_STOP_SEC_CONST
#include "Btl_MemMap.h"

/*******************************************************************************
**                             End of File                                    **
*******************************************************************************/
