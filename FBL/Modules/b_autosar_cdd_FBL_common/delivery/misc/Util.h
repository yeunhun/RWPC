/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Util.h                                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Header file for Util.c                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef UTIL_H
#define UTIL_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "Util_Cfg.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#if (BTL_USE_STDLIB == STD_OFF)
#define memcpy(Lpu8_Target, Lpu8_SourcePtr, Lu16_Length)     \
  Util_Memcpy(Lpu8_Target,Lpu8_SourcePtr, Lu16_Length)

#define memcmp(Lpu8_TargetPtr, Lpu8_SourcePtr, Lu16_Length)  \
  Util_Memcmp(Lpu8_TargetPtr, Lpu8_SourcePtr, Lu16_Length)

#define memset(Lpu8_TargetPtr, Lu8_FillerValue, Lu16_Length) \
  Util_Memset(Lpu8_TargetPtr, Lu8_FillerValue, Lu16_Length)

#define strlen(Lps8_Ptr) Util_Strlen(Lps8_Ptr)

#define strncmp(Lps8_Str1, Lps8_Str2, Lu16_Length)           \
  Util_Strncmp(Lps8_Str1, Lps8_Str2, Lu16_Length)
#endif /* (BTL_USE_STDLIB == STD_OFF)*/

/*******************************************************************************
**                               Enumerations                                 **
*******************************************************************************/
#if (BTL_DEBUG == STD_ON)
typedef enum
{
  UTIL_TIMECHK_TIMER0,
  UTIL_TIMECHK_TIMER1,
  UTIL_TIMECHK_TIMER2,
  UTIL_TIMECHK_TIMER3,
  UTIL_TIMECHK_TIMER4,
  UTIL_TIMECHK_TIMER5,
  UTIL_TIMECHK_TIMER6,
  UTIL_TIMECHK_TIMER7,
  UTIL_TIMECHK_TIMER8,
  UTIL_TIMECHK_TIMER9,
  UTIL_TIMECHK_TIMER10,
  UTIL_TIMECHK_TIMER11,
  UTIL_TIMECHK_TIMER12,
  UTIL_TIMECHK_TIMER13,
  UTIL_TIMECHK_TIMER14,
  UTIL_TIMECHK_TIMER15
}Util_Timer_Etyp;
#endif /*(BTL_DEBUG == STD_ON)*/

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

extern uint32 Util_8by4To32(const uint8* pData);

extern void Util_32To8by4(const uint32 ulValue, uint8* pData);

extern Std_ReturnType Util_Memcpy(uint8* Lpu8_Target, const uint8* Lpu8_SourcePtr,
  uint32 Lu32_Length);
  
extern Std_ReturnType Util_Memcmp(const uint8* Lpu8_TargetPtr, const uint8* Lpu8_SourcePtr,
  uint16 Lu16_Length);
  
extern Std_ReturnType Util_Memset(uint8* Lpu8_TargetPtr, const uint8  Lu8_FillerValue,
  uint16 Lu16_Length);
  
extern Std_ReturnType Util_Memclr(uint8* Lpu8_TargetPtr, uint16 Lu16_Length);
  
extern uint32 Util_Strlen(const uint8* Lps8_Ptr);

extern uint32 Util_Strncmp(const uint8* Lps8_Str1, const uint8* Lps8_Str2, uint16 Lu16_Length);
  
extern uint32 Util_GetRandomNo(uint32 Lu32_MaxValue);

#if (BTL_DEBUG == STD_ON)

extern void Util_StaticTrace(const uint8* Lpu8_TraceDataPtr);

extern void Util_DynamicTrace(uint8 Lu8_Identifier,const uint8* Lpu8_TraceDataPtr,
  uint8 Lu8_Length);
  
extern Std_ReturnType Util_TimeChkGetTime(Util_Timer_Etyp Len_Timer, uint32* Lpu32_Time);

extern Std_ReturnType Util_TimeChkHold(Util_Timer_Etyp Len_Timer);

extern Std_ReturnType Util_TimeChkRelease(Util_Timer_Etyp Len_Timer);

#if (UTIL_MINIMAL_IMPLEMENTATION == STD_OFF)

extern Std_ReturnType Util_TimeChkSetTime(Util_Timer_Etyp Len_Timer, uint32 Lu32_SetTime);

#endif

extern Std_ReturnType Util_TimeChkStart(Util_Timer_Etyp Len_Timer);

extern Std_ReturnType Util_TimeChkStop(Util_Timer_Etyp  Len_Timer);

#endif /*(BTL_DEBUG == STD_ON)*/

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* UTIL_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
