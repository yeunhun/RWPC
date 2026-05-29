/*******************************************************************************
**                                                                            **
**  (C) 2019~2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Syst.h                                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Header file for Syst.c. This file provides function           **
**              declarations for the hardware specific modules like timer and **
**              functionality will be changed according to the respective     **
**              hardware                                                      **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.17.0.0  16-Jul-2021   Sungwook     Redmine #29464                        **
** 1.0.3     29-Jul-2020   JYS          Redmine #24231                        **
** 1.0.2     02-Jul-2020   EK.KIM       Redmine #23953, #23954                **
** 1.0.1     07-Feb-2020   Sinil        Redmine #21603                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef SYST_H
#define SYST_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "Mcu.h"

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_PJS_CODE
#include "Btl_MemMap.h"

extern Std_ReturnType Syst_IsWarmStart(void);

extern void Syst_PreInit(void);

extern void Syst_BtlSpecificInit(void);

extern void Syst_BtlSpecificDeInit(void);

extern void Syst_PrepareForApplEntry(void);

extern void Syst_PreMcuInit(void);

extern void Syst_TimerInit(void);

extern void Syst_TimerDeInit(void);

extern Std_ReturnType Syst_TimerGetTime(uint32* Lpu32_TimerValue);

extern uint32 Syst_TimerGetTimeuSec(void);

extern uint32 Syst_TimerGetTimeDiffuSec(const uint32 Lu32_LastTime);

extern uint32 Syst_TimerGetTimemSec(void);

extern uint32 Syst_TimerGetTimeDiffmSec(const uint32 Lu32_LastTime);

extern Std_ReturnType Syst_IndicateReset(void);

extern void Syst_ExecuteReset(void);

extern Std_ReturnType Syst_GetResetReqResult(void);

extern void Syst_MainFunction(void);

extern Std_StatusType Syst_GetStatus(void);

#if ((FBL_SUPPORT_MCU == FBL_MCU_TC38X) || (FBL_SUPPORT_MCU == FBL_MCU_TC39X) || \
		(FBL_SUPPORT_MCU == FBL_MCU_TC36X) || (FBL_SUPPORT_MCU == FBL_MCU_TC37X) || \
		(FBL_SUPPORT_MCU == FBL_MCU_TC33X))
extern void Syst_PortSetPinPadDriver(uint8 Lu8_Port, uint8 Lu8_PinIndex,
  Syst_PortPadDriver_Etyp Len_PadDriver);

extern void Syst_PortSetPinModeInput(uint8 Lu8_PortNum, uint8 Lu8_PinIndex,
  Syst_PortInMode_Etyp Len_Mode);

extern void Syst_PortSetPinModeOutput(uint8 Lu8_PortNum, uint8 Lu8_PinIndex,
  Syst_PortOutputMode_Etyp Len_Mode, Syst_PortOutIdx_Etyp Len_Index);
#endif
  
#define BTL_STOP_SEC_PJS_CODE
#include "Btl_MemMap.h"

#endif /* SYST_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
