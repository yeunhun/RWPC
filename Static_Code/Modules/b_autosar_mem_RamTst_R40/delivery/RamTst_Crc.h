/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Ram_Crc.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Ram Test Module Internal file to calculate CRC                **
**                                                                            **
**  PURPOSE   : Provision of API Prototype Declarations                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By                Description                      **
********************************************************************************
** 1.3.2     30-Dec-2020   CY Song          RedMine #27378                    **
** 1.2.3     05-Oct-2015   CY Song          Change parameter name             **
** 1.0.0     07-Jun-2013   CY Song          Initial Version                   **
*******************************************************************************/
#ifndef RAMTST_CRC_H
#define RAMTST_CRC_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "RamTst_CrcTypes.h"               /* Crc Type Definition Header File */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Not a defect:Low] "It is implemented according to autosar specification" */
/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/
#if(RAMTST_CRC_8_SUPPORT == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, RAMTST_CODE) RamTst_CalculateCRC8
(P2CONST(uint8, RAMTST_CONST, RAMTST_APPL_CONST)RamTst_DataPtr,
uint32 RamTst_Length, uint8 RamTst_CrcStartValue8,
                                                 boolean RamTst_CrcIsFirstCall);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(RAMTST_CRC_8H2F_SUPPORT == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, RAMTST_CODE) RamTst_CalculateCRC8H2F
(P2CONST(uint8, RAMTST_CONST, RAMTST_APPL_CONST)RamTst_DataPtr,
uint32 RamTst_Length, uint8 RamTst_CrcStartValue8H2F,
                                                 boolean RamTst_CrcIsFirstCall);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(RAMTST_CRC_16_SUPPORT == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint16, RAMTST_CODE) RamTst_CalculateCRC16
  (P2CONST(uint8, RAMTST_CONST, RAMTST_APPL_CONST)RamTst_DataPtr,
  uint32 RamTst_Length, uint16 RamTst_CrcStartValue16,
                                                 boolean RamTst_CrcIsFirstCall);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(RAMTST_CRC_32_SUPPORT == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint32, RAMTST_CODE) RamTst_CalculateCRC32
  (P2CONST(uint8, RAMTST_CONST, RAMTST_APPL_CONST)RamTst_DataPtr,
  uint32 RamTst_Length, uint32 RamTst_CrcStartValue32,
                                                 boolean RamTst_CrcIsFirstCall);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* polyspace-end MISRA-C3:20.1 [Not a defect:Low] "It is implemented according to autosar specification" */

#endif  /* RAMTST_CRC_H */

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
