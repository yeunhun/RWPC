/*******************************************************************************
**                                                                            **
**  (C) 2020~21 HYUNDAI AUTRON Co., Ltd.                                      **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Can.h                                                         **
**                                                                            **
**  TARGET    : CYTXXX                                                        **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file provides all the API for flash driver               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision    Date          By           Description                         **
********************************************************************************
** 1.1.0.0     23-Feb-2021   JHLim        Redmine #23964                      **
** 1.0.0       10-April-2020 JaeHyun      Initial version                     **
*******************************************************************************/

#ifndef CAN_H
#define CAN_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Can_GeneralTypes.h"
#include "Std_Types.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_PJS_CODE
#include "Btl_MemMap.h"
extern void Can_Init(void);
#define BTL_STOP_SEC_PJS_CODE
#include "Btl_MemMap.h"

#define BTL_START_SEC_PJS_CODE
#include "Btl_MemMap.h"
extern Std_ReturnType Can_Write(Can_HwHandleType Ldt_Hth,
  const Can_PduType* Ldt_PduInfo);
#define BTL_STOP_SEC_PJS_CODE
#include "Btl_MemMap.h"

#define BTL_START_SEC_PJS_CODE
#include "Btl_MemMap.h"
extern void Can_MainFunction_Read(void);
#define BTL_STOP_SEC_PJS_CODE
#include "Btl_MemMap.h"

#define BTL_START_SEC_PJS_CODE
#include "Btl_MemMap.h"
extern void Can_MainFunction_Write(void);
#define BTL_STOP_SEC_PJS_CODE
#include "Btl_MemMap.h"

#define BTL_START_SEC_PJS_CODE
#include "Btl_MemMap.h"
extern void Can_MainFunction_BusOff(void);
#define BTL_STOP_SEC_PJS_CODE
#include "Btl_MemMap.h"

#endif /* CAN_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/

