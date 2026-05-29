/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Port.h                                                        **
**                                                                            **
**  TARGET    : CYTXXX                                                        **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides functions required in Port driver                    **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision    Date          By           Description                         **
********************************************************************************
** 1.3.0       07-Jun-2021   VuPH6        Redmine #28436                      **
** 1.2.0       10-May-2021   JHLim        #28951                              **
** 1.1.0.0     23-Feb-2021   JHLim        Redmine #23964                      **
** 1.0.0       10-April-2020 JaeHyun      Initial version                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef PORT_H
#define PORT_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Std_Types.h"
#include "Fbl_Cfg.h"
/*******************************************************************************
**                               Type Definition                              **
*******************************************************************************/
typedef struct
{
  uint32 ul_Port;
  uint32 ul_Pin;
} CY_PORTPIN;


/*******************************************************************************
**                               Macro Definition                             **
*******************************************************************************/
#define P2_1_CAN0_0_RX	                                                      0U
#define P8_1_CAN0_0_RX	                                                      1U
#define P0_3_CAN0_1_RX	                                                      2U
#define P4_4_CAN0_1_RX	                                                      3U
#define P6_3_CAN0_2_RX	                                                      4U
#define P12_1_CAN0_2_RX	                                                      5U
#define P3_1_CAN0_3_RX	                                                      6U
#define P14_1_CAN1_0_RX	                                                      7U
#define P23_1_CAN1_0_RX	                                                      8U
#define P17_1_CAN1_1_RX	                                                      9U
#define P22_1_CAN1_1_RX	                                                     10U
#define P18_7_CAN1_2_RX	                                                     11U
#define P20_4_CAN1_2_RX	                                                     12U
#define P15_1_CAN1_3_RX	                                                     13U
#define P19_1_CAN1_3_RX	                                                     14U
#if((FBL_MCU_NAME == CYT3BBXX) || (FBL_MCU_NAME == CYT4BBXX) || (FBL_MCU_NAME == CYT4BFXX))
/* TV-II-B-H*/
#define P3_7_CAN1_2_RX	                                                     15U
#define P12_5_CAN1_1_RX	                                                     16U
#define P30_3_CAN1_3_RX	                                                     17U
#if(FBL_MCU_NAME == CYT4BFXX)
/* CYT4BFXX */
#define P7_4_CAN0_4_RX	                                                     18U
#define P20_7_CAN1_4_RX	                                                     19U
#define P32_7_CAN1_4_RX	                                                     20U
#endif /* TV-II-B-H*/
#endif /* CYT4BFXX */

#define P2_0_CAN0_0_TX	                                                      0U
#define P8_0_CAN0_0_TX	                                                      1U
#define P0_2_CAN0_1_TX	                                                      2U
#define P4_3_CAN0_1_TX	                                                      3U
#define P6_2_CAN0_2_TX	                                                      4U
#define P12_0_CAN0_2_TX	                                                      5U
#define P3_0_CAN0_3_TX	                                                      6U
#define P14_0_CAN1_0_TX	                                                      7U
#define P23_0_CAN1_0_TX	                                                      8U
#define P17_0_CAN1_1_TX	                                                      9U
#define P22_0_CAN1_1_TX	                                                     10U
#define P18_6_CAN1_2_TX	                                                     11U
#define P23_0_CAN1_2_TX	                                                     12U
#define P15_0_CAN1_3_TX	                                                     13U
#define P19_0_CAN1_3_TX	                                                     14U
#if((FBL_MCU_NAME == CYT3BBXX) || (FBL_MCU_NAME == CYT4BBXX) || (FBL_MCU_NAME == CYT4BFXX))
/* TV-II-B-H*/
#define P3_6_CAN1_2_TX	                                                     15U
#define P12_4_CAN1_1_TX	                                                     16U
#define P21_5_CAN1_1_TX	                                                     17U
#define P30_2_CAN1_3_TX	                                                     18U
#if(FBL_MCU_NAME == CYT4BFXX)
/* CYT4BFXX */
#define P7_3_CAN0_4_TX	                                                     19U
#define P20_6_CAN1_4_TX	                                                     20U
#define P32_6_CAN1_4_TX	                                                     21U
#endif /* TV-II-B-H*/
#endif /* CYT4BFXX */

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_PJS_CODE
#include "Btl_MemMap.h"

extern void Port_Init(void);

#define BTL_STOP_SEC_PJS_CODE
#include "Btl_MemMap.h"

#define BTL_START_SEC_PJS_CODE
#include "Btl_MemMap.h"

extern void Fbl_Gpio_Init(uint32 portNum, uint32 pinNum,
  uint32 hsiomMode, uint32 dmMode, uint32 portpinVal, uint32 portpinMode);

#define BTL_STOP_SEC_PJS_CODE
#include "Btl_MemMap.h"

#endif /* PORT_H */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
