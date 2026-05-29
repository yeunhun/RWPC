/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: RomTst.h                                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR ROMTST                                                **
**                                                                            **
**  PURPOSE   : Rom Test API Functionality                                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By       Description                               **
********************************************************************************
** 1.0.0     16-May-2016   JS Park    RedMine #5149                           **
********************************************************************************
** 1.1.0     12-Feb-2017   JS Park    RedMine #7473                           **
********************************************************************************
** 1.2.3     30-Dec-2020   YJ Yun     RedMine #27410                          **
********************************************************************************
** 1.4.0     22-Nov-2021   JH Lim     RedMine #31510, #33116                  **
********************************************************************************
** 1.4.1     24-Dec-2021   JH Lim     RedMine #33330                          **
*******************************************************************************/

#ifndef ROMTST_H
#define ROMTST_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "RomTst_Cfg.h"
#include "RomTst_api.h"
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* Definition macro */
#define ROMTST_LOWPOWER_PREVENT          (0x00U)
#define ROMTST_LOWPOWER_ALLOW            (0x01U)
#define ROMTST_CRCTB_LENGTH              (256U)
#define ROMTST_ZERO                      (0U)
#define ROMTST_ONE                       (1U)
#define ROMTST_TWO                       (2U)
#define ROMTST_THREE                     (3U)
#define ROMTST_FOUR                      (4U)
#define ROMTST_EIGHT                     (8U)

/* Default value for CRC area */
#define ROMTST_NUM_OF_CRC_AREA_NOT_FILL             (0xFFFFU)
/* Default value for CRC address info area */
#define ROMTST_ADDR_INFO_NOT_FILL                   (0xFFFFFFFFUL)
/* Macro for calculate the length of ROM data to be calculated */
/* polyspace-begin CERT-C:PRE00-C MISRA-C3:D4.9 [Justified:Low] "This macro used to calculate a subtraction like andAddr minus startAddr" */
#define ROMTST_GET_DATA_LENGTH(startAddr, endAddr)  (((RomTst_AddressType)endAddr - (RomTst_AddressType)startAddr) + 1UL)
/* polyspace-end CERT-C:PRE00-C MISRA-C3:D4.9 [Justified:Low] "This macro used to calculate a subtraction like andAddr minus startAddr" */
#define ROMTST_MASK_ONE_BYTE                        (0xFFU)

#if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
#define ROMTST_CRC_INIT_VALUE_LOWBYTE_POS           (8U)
#define ROMTST_CRC_INIT_VALUE_HIGHBYTE_POS          (9U)
#else
#define ROMTST_CRC_INIT_VALUE_LOWBYTE_POS           (9U)
#define ROMTST_CRC_INIT_VALUE_HIGHBYTE_POS          (8U)
#endif /* end of if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST) */

/* polyspace-begin CERT-C:PRE00-C ISO-17961:intptrconv MISRA-C3:11.4,D4.9 [Justified:Low] "Casting a fixed address point to the address which CRC initial value be located" */
#define ROMTST_GET_LOW_BYTE_CRC_INIT_VALUE(CrcAddrPtr)  ((uint8) *((uint8 *)(((RomTst_AddressType)CrcAddrPtr) - \
  ROMTST_CRC_INIT_VALUE_LOWBYTE_POS)))
#define ROMTST_GET_HIGH_BYTE_CRC_INIT_VALUE(CrcAddrPtr) ((uint8) *((uint8 *)(((RomTst_AddressType)CrcAddrPtr) - \
  ROMTST_CRC_INIT_VALUE_HIGHBYTE_POS)))
/* polyspace-end CERT-C:PRE00-C ISO-17961:intptrconv MISRA-C3:11.4,D4.9 [Justified:Low] "Casting a fixed address point to the address which CRC initial value be located" */

typedef struct
{
  uint32 StartAddr;     /* Start address */
  uint32 EndAddr;       /* End address */
} RomTst_TestBlockAddressType;

typedef struct
{
  uint16 CrcValue;                          /* CRC value pre-calculated */
  uint16 NumberOfCrcAreas;                  /* Number of Crc Area to be defined */
  RomTst_TestBlockAddressType CrcArea[1U];  /* The size of this structure is not relevant. */
  /* The real size is given by NumberOfCrcAreas */
} RomTst_CrcAreaType;

/* RomTst_CodeFlashIdType: Crc area enumeration */
typedef enum
{
  /* SW redundancy applied MCU
   * - Partition A RTSW mode
   * HW redundancy applied MCU
   * - RTSW mode
   */
  ROMTST_CODE_FLASH_ID_1 = 1U,
  /* SW redundancy applied MCU
   * - Partition B RTSW mode
   * HW redundancy applied MCU
   * - unused
   */
  ROMTST_CODE_FLASH_ID_2
} RomTst_CodeFlashIdType;

/* RomTst_TestBlockType: Crc area informations of test block */
typedef struct
{
  RomTst_CrcAreaType *CrcArea1;
  RomTst_CrcAreaType *CrcArea2;
} RomTst_TestBlockType;

/* RomTst_ConfigType: RomTst blocks config informations */
typedef struct
{
  /* Pointer to Foreground test block */
  P2CONST(RomTst_TestBlockType, AUTOMATIC, AUTOMATIC) TestBlockFgnd;
  /* Number of foreground test blocks */
  uint8 NumOfTestBlockFgnd;
  /* Pointer to Background test block */
  P2CONST(RomTst_TestBlockType, AUTOMATIC, AUTOMATIC) TestBlockBgnd;
  /* Number of background test blocks */
  uint8 NumOfTestBlockBgnd;
} RomTst_ConfigType;

typedef uint32  RomTst_AddressType;
typedef uint8   RomTst_StartResultType;
typedef uint8   RomTst_StatusType;

extern CONST(RomTst_ConfigType, ROMTST_CONST) RomTst_Config[1U];
extern CONST(RomTst_CrcAreaType, ROMTST_VAR_INIT) RomTst_MemChkCrcArea;
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/* polyspace-begin MISRA-C3:8.5 [Justified:Low] "Declare functions prototype" */
extern FUNC(RomTst_StartResultType, ROMTST_CODE) RomTst_Start(void);
extern FUNC(void, ROMTST_CODE) RomTst_Init(void);
extern FUNC(RomTst_StatusType, ROMTST_CODE) RomTst_GetStatus(void);
extern FUNC(void, ROMTST_CODE) RomTst_Rtm_Perform(void);

#if (ROMTST_OTA_SUPPORT == STD_ON)
extern FUNC(RomTst_CodeFlashIdType, ROMTST_CODE) RomTst_GetActiveCodeFlashId(void);
#endif

#if (ROMTST_TEST_COMPLETED_NOTIFICATION_SUPPORTED == STD_ON)
extern FUNC(void, ROMTST_CODE) ROMTST_TEST_COMPLETED_NOTIFICATION(void);
#endif
/* polyspace-end MISRA-C3:8.5 [Justified:Low] "Declare functions prototype" */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
#endif /*__ROMTST_H__ */
