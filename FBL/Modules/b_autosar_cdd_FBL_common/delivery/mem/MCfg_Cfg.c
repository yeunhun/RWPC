/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: MCfg_Cfg.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Configuration for MCfg                                        **
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

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
/* Header file inclusion for flash configuration configuration data */
#include "MCfg_Cfg.h"
#include "Fbl_Config.h"

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/
#define BTL_START_SEC_CONST
#include "Btl_MemMap.h"

/* Physical memory address to logical block mapping of the Flash memory */ 
const MCfg_MemBlkTab_Styp MCfg_Kast_MemBlockTable[FBL_NUM_OF_MEM_BLOCKS] =
{
  /*
   * Start_address  Block_Size    Permission
   */
  {
    /* 128 KB BTL NO RWE */
    FBL_START_ADDR,
    (FBL_END_ADDR - FBL_START_ADDR + 1U),
    (Mem_AccessType)(MEM_ACT_TYPE_BLOCKED),
    MCFG_BTL_SW_BLK_MASK
  },
  #if (FBL_NUM_OF_MEM_BLOCKS >= 2)
  {
    MAIN_SW_START_ADDR,
    (MAIN_SW_END_ADDR - MAIN_SW_START_ADDR + 1U),
    (Mem_AccessType)(MEM_ACT_TYPE_WRITE | MEM_ACT_TYPE_ERASE),
    MCFG_APP_SW_BLK_MASK
  },
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 2) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 3)
  {
    ASW2_START_ADDR,
    (ASW2_END_ADDR - ASW2_START_ADDR + 1U),
    (Mem_AccessType)(MEM_ACT_TYPE_WRITE | MEM_ACT_TYPE_ERASE),
    MCFG_APP_SW2_BLK_MASK
  },
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 3) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 4)
  {
    ASW3_START_ADDR,
    (ASW3_END_ADDR - ASW3_START_ADDR + 1U),
    (Mem_AccessType)(MEM_ACT_TYPE_WRITE | MEM_ACT_TYPE_ERASE),
    MCFG_APP_SW3_BLK_MASK
  },
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 4) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 5)
  {
    ASW4_START_ADDR,
    (ASW4_END_ADDR - ASW4_START_ADDR + 1U),
    (Mem_AccessType)(MEM_ACT_TYPE_WRITE | MEM_ACT_TYPE_ERASE),
    MCFG_APP_SW4_BLK_MASK
  },
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 5) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 6)
  {
    ASW5_START_ADDR,
    (ASW5_END_ADDR - ASW5_START_ADDR + 1U),
    (Mem_AccessType)(MEM_ACT_TYPE_WRITE | MEM_ACT_TYPE_ERASE),
    MCFG_APP_SW5_BLK_MASK
  },
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 6) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 7)
  {
    ASW6_START_ADDR,
    (ASW6_END_ADDR - ASW6_START_ADDR + 1U),
    (Mem_AccessType)(MEM_ACT_TYPE_WRITE | MEM_ACT_TYPE_ERASE),
    MCFG_APP_SW6_BLK_MASK
  },
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 7) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 8)
  {
    ASW7_START_ADDR,
    (ASW7_END_ADDR - ASW7_START_ADDR + 1U),
    (Mem_AccessType)(MEM_ACT_TYPE_WRITE | MEM_ACT_TYPE_ERASE),
    MCFG_APP_SW7_BLK_MASK
  },
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 8) */
};
  
/* Table for logical block index to logical block id and logical block mask */
const MCfg_IndexToLogBlkMap_Styp MCfg_Kast_IndexToLogBlkMap[FBL_NUM_OF_MEM_BLOCKS] =
{
  {MCFG_TOTAL_BLK_COUNT_ONE, MCFG_BTL_SW_BLK_ID, MCFG_BTL_SW_BLK_MASK },
  #if (FBL_NUM_OF_MEM_BLOCKS >= 2)
  {MCFG_TOTAL_BLK_COUNT_ONE, MCFG_APP_SW_BLK_ID, MCFG_APP_SW_BLK_MASK },
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 2) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 3)
  {MCFG_TOTAL_BLK_COUNT_ONE, 2, MCFG_APP_SW2_BLK_MASK },
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 3) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 4)
  {MCFG_TOTAL_BLK_COUNT_ONE, 3, MCFG_APP_SW3_BLK_MASK },
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 4) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 5)
  {MCFG_TOTAL_BLK_COUNT_ONE, 4, MCFG_APP_SW4_BLK_MASK },
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 5) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 6)
  {MCFG_TOTAL_BLK_COUNT_ONE, 5, MCFG_APP_SW5_BLK_MASK },
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 6) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 7)
  {MCFG_TOTAL_BLK_COUNT_ONE, 6, MCFG_APP_SW6_BLK_MASK },
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 7) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 8)
  {MCFG_TOTAL_BLK_COUNT_ONE, 7, MCFG_APP_SW7_BLK_MASK },
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 8) */
}; 
 
/* Table for logical block memory mask */
const uint8 MCfg_Kau8_LogicBlk[FBL_NUM_OF_MEM_BLOCKS] =
{
  MCFG_BTL_SW_BLK_MASK,
  #if (FBL_NUM_OF_MEM_BLOCKS >= 2)
  MCFG_APP_SW_BLK_MASK,
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 2) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 3)
  MCFG_APP_SW2_BLK_MASK,
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 3) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 4)
  MCFG_APP_SW3_BLK_MASK,
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 4) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 5)
  MCFG_APP_SW4_BLK_MASK,
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 5) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 6)
  MCFG_APP_SW5_BLK_MASK,
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 6) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 7)
  MCFG_APP_SW6_BLK_MASK,
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 7) */
  #if (FBL_NUM_OF_MEM_BLOCKS >= 8)
  MCFG_APP_SW7_BLK_MASK,
  #endif /* (FBL_NUM_OF_MEM_BLOCKS >= 8) */
}; 

#define BTL_STOP_SEC_CONST
#include "Btl_MemMap.h"

/*******************************************************************************
**                        Global Function Definition                          **
*******************************************************************************/
#define BTL_START_SEC_PJS_CODE
#include "Btl_MemMap.h"

/***********************************************************************************************************************
** Function Name        : MCfg_AddressLengthAlignmentCheck                                                            **
**                                                                                                                    **
** Description          : This function checks the alignment of the target address and the length and returns the     **
**                        result accordingly                                                                          **
**                                                                                                                    **
** Sync/Async           : Synchronous                                                                                 **
**                                                                                                                    **
** Reentrancy           : Non Reentrant                                                                               **
**                                                                                                                    **
** Input Parameters     : Lu32_TargetAddress - Address for alignment check                                            **
**                        Ldt_AccessType                                                                              **
**                        Lu32_Length - Address range which is to be checked for alignment                            **
**                                                                                                                    **
** InOut parameter      : None                                                                                        **
**                                                                                                                    **
** Output Parameters    : None                                                                                        **
**                                                                                                                    **
** Return parameter     : Std_ReturnType                                                                              **
**                                                                                                                    **
** Preconditions        : MCfg_Init should be called before calling this function                                     **
**                                                                                                                    **
***********************************************************************************************************************/
Std_ReturnType MCfg_AddressLengthAlignmentCheck(
  uint32 Lu32_TargetAddress,
  uint32 Lu32_Length,
  Mem_AccessType Ldt_AccessType
)
{
  /* Initialize the local variable for holding the return value */
  Std_ReturnType Ldt_ReturnVal;

  /* For unused variables. */
  UNUSED(Ldt_AccessType);

  /* Check for the address alignment */
  if(STD_CLEAR != (Lu32_TargetAddress % Fbl_Gu32_FlashAlignment))
  {
    /* Update the return value of the function with E_OK */
    Ldt_ReturnVal = E_NOT_OK;
  }
  else if(STD_CLEAR != (Lu32_Length % Fbl_Gu32_FlashAlignment))
  {
    Ldt_ReturnVal = E_NOT_OK;
  }
  else
  {
    Ldt_ReturnVal = E_OK;
  }

  /* Return the updated value of the function */
  return Ldt_ReturnVal;
}

#define BTL_STOP_SEC_PJS_CODE
#include "Btl_MemMap.h"

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
