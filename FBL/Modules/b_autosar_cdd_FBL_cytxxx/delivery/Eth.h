/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Eth.h                                                         **
**                                                                            **
**  TARGET    : CYTXXX                                                        **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides functions required in Ethernet driver                **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef ETH_H
#define ETH_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Eth_Types.h"
#include "Eth_Cfg.h"

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_PJS_CODE
#include "Btl_MemMap.h"

extern void Eth_Init(void);

extern Std_ReturnType Eth_SetPhysAddr(const uint8* Lpu8_PhysAddrPtr);

extern Std_ReturnType Eth_GetPhysAddr(uint8* Lpu8_PhysAddrPtr);

extern Std_ReturnType Eth_Transmit(const uint8* Lpu8_InputData, uint16 Lu16_Length);

extern Std_ReturnType Eth_Receive(Eth_RxStatus_Etyp* Lpdt_RxStatusPtr,
  uint8* Lpu8_RxBufAddr, uint16* Lpu16_Length);

extern void Eth_Deinit(void);

extern boolean Eth_CheckLinkStatus(void);

#define BTL_STOP_SEC_PJS_CODE
#include "Btl_MemMap.h"

#endif /* ETH_H */


/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */


/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
