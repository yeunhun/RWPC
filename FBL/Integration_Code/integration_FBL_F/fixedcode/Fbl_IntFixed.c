/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fbl_IntFixed.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Application interface in FBL                                  **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.2.0    16-Jul-2021   Sungwook     #29464                                **
** 1.0.0     23-Dec-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Fbl_AppIf.h"
#include "Fbl_Cfg.h"

/*******************************************************************************
**                        Global Function Definition                          **
*******************************************************************************/
#define BTL_START_SEC_USER_CODE
#include "Btl_MemMap.h"

uint32 Fbl_GetMainSwEntryPointAddress(void)
{
  Fbl_SwEntryPointType Ldt_SwEntryPoint;
  uint32 Lu32_EntryPointAddress;

  Ldt_SwEntryPoint = Fbl_SelectEntryPoint();

  switch (Ldt_SwEntryPoint)
  {
  /* Partition A RTSW 모드 동작 */
  case FBL_SW_ENTRY_POINT_1:
    Lu32_EntryPointAddress = FBL_MAIN_SW_ENTRY_ADDRESS_1;
    break;

  case FBL_SW_ENTRY_POINT_2:
    #if (FBL_MEMORY_SWAP_ENABLE == STD_ON)
    /* 메모리 이중화 기능 적용 */

    #if ((FBL_SUPPORT_MCU == FBL_MCU_TC38X) || (FBL_SUPPORT_MCU == FBL_MCU_TC39X) || \
		(FBL_SUPPORT_MCU == FBL_MCU_TC36X) || (FBL_SUPPORT_MCU == FBL_MCU_TC37X))

    /* HW MEMORY SWAP 기능이 지원되는 MCU */
    /* RTSW 모드 */
    Lu32_EntryPointAddress = FBL_MAIN_SW_ENTRY_ADDRESS_1;

    #else /* ((FBL_SUPPORT_MCU == FBL_MCU_TC38X) || (FBL_SUPPORT_MCU == FBL_MCU_TC39X) || \
    			(FBL_SUPPORT_MCU == FBL_MCU_TC36X) || (FBL_SUPPORT_MCU == FBL_MCU_TC37X)) */

    /* HW MEMORY SWAP 기능이 지원되지 않는 MCU */
    /* Partition B RTSW 모드 동작 */
    Lu32_EntryPointAddress = FBL_MAIN_SW_ENTRY_ADDRESS_2;

    #endif /* ((FBL_SUPPORT_MCU == FBL_MCU_TC38X) || (FBL_SUPPORT_MCU == FBL_MCU_TC39X) || \
    			(FBL_SUPPORT_MCU == FBL_MCU_TC36X) || (FBL_SUPPORT_MCU == FBL_MCU_TC37X)) */
    
    #else /* (FBL_MEMORY_SWAP_ENABLE == STD_ON) */

    /* 메모리 이중화 기능 미적용 */
    Lu32_EntryPointAddress = FBL_MAIN_SW_ENTRY_ADDRESS_1;
    
    #endif /* (FBL_MEMORY_SWAP_ENABLE == STD_ON) */

    break;

  /* FBL 모드로 동작 */
  case FBL_SW_NO_RTSW:
  default:
    Lu32_EntryPointAddress = 0UL;
    break;
  }

  return Lu32_EntryPointAddress;
}

#define BTL_STOP_SEC_USER_CODE
#include "Btl_MemMap.h"

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
