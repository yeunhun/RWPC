/*============================================================================*/
/*                     HYUNDAI AUTOEVER SOFTWARE GROUP                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================
 * C Source:         %CanCM.h%
 * Instance:         RPL_1
 * %version:         0.9.2 %
 * %created_by:      ca027 %
 * %date_created:    2014/02/03 17:14:33 %
 *============================================================================*/
/* DESCRIPTION : AUTOSAR CAN Communication Manager                            */
/*============================================================================*/
/* FUNCTION COMMENT : Declaration for CanCM main functions                     */
/*============================================================================*/
/* COPYRIGHT (C) HYUNDAI AUTOEVER 2013                                        */
/* ALL RIGHTS RESERVED                                                        */
/*                                                                            */
/* The reproduction, transmission, or use of this document or its content is  */
/* not permitted without express written authority. Offenders will be liable  */
/* for damages.                                                               */
/* All rights, including rights created by patent grant or registration of a  */
/* utility model or design, are reserved.                                     */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |   CR ID / TASK ID             |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/* 0.9       | 8/Jul/2013  |   xar~150 / xar~623           |  Kyung-Tae Kim   */
/* - Initial Creation                                                         */
/*----------------------------------------------------------------------------*/
/* 0.9.1     | 25/Sep/2013 |   xar~150 / xar~623           |  Kyung-Tae Kim   */
/* - addition : APIs                                                          */
/*----------------------------------------------------------------------------*/
/* 1.0       | 20/Apr/2015 |   #2500                        |  Kyung-Tae Kim  */
/*----------------------------------------------------------------------------*/
/* 1.1.1     | 21/Sep/2015 |   #2720                        |  Kyung-Tae Kim  */
/*----------------------------------------------------------------------------*/
/* 1.1.2     | 21/Sep/2015 |   #3515                        |  Kyung-Tae Kim  */
/*----------------------------------------------------------------------------*/
/* 1.1.3     | 14/Jun/2015 |   #5027                        |  Kyung-Tae Kim  */
/*----------------------------------------------------------------------------*/
/* 1.5.12    | 21/Dec/2017 |   #10378                       |  Kyung-Tae Kim  */
/*----------------------------------------------------------------------------*/
/* 1.5.12.1  | 24/Aug/2018 |   #13761                       |  Jeong-Su Lim   */
/*----------------------------------------------------------------------------*/
/* 1.5.13    | 13/Feb/2019 |   #15997                       |  Jeong-Su Lim   */
/*----------------------------------------------------------------------------*/
/* 1.5.15    | 12/Jan/2021 |   #27561                       |  Seung-Jae Kim  */
/*----------------------------------------------------------------------------*/
/* 1.5.16    | 31/Aug/2021 |   #31834                       |  Seung-Jae Kim  */
/*============================================================================*/
#ifndef CANCM_H
#define CANCM_H


#include "CanCM_Cfg.h"           /* Configuration header file */
#if  (STD_ON == CANCM_WAKEUP_SUPPORT)
#include "EcuM.h"
#endif

#if (STD_ON == CANCM_DEM_STATUS)
  #include "Dem.h"
#endif

#include "IoHwAb_Cfg.h"
#include "Std_Types.h"         /* Standard type header */
#include "ComStack_Types.h"
#include "CanCM_InitTypes.h"

/* Service ID for CanCM_MainFunction */
#define CANCM_MAINFUNCTION_SID                (0x02U)
#define CANCM_COMMODEINDICATION_SID           (0x03U)
#define CANCM_GETCURRENTVOLTAGEMODE_SID       (0x04U)
#define CANCM_GETCURRENTNETWORKSTATE_SID      (0x05U)

#define CANCM_MODULE_ID                       ((uint16)59)
#define CANCM_INSTANCE_ID                     (0x00U)


#define CANCM_ZERO            ((uint8)0x0)
#define CANCM_ONE             ((uint8)0x1)
#define CANCM_TWO             ((uint8)0x2)
#define CANCM_EIGHT           ((uint8)0x8)
#define CANCM_INVALID         ((uint16)0xFFFF)
#define CANCM_INVALID_CHANNEL ((uint8)0xFF)

#define CANCM_INITIALISED     (0x01U)
#define CANCM_UNINITIALISED   (0x00U)

/* DET error reported when module is unintialized */
#define CANCM_E_UNINIT                 ((uint8)31)
#define CANCM_E_READBATTERYFAIL        ((uint8)32)
#define CANCM_E_INVALID_REQUEST        ((uint8)33)

/*  polyspace:begin<MISRA-C:19.7:Not a defect:Justify with annotations>
    No Impact of this rule violation                                          */
/* polyspace:begin MISRA-C3:D4.9 [Not a defect:Justified] "No Impact of this rule violations." */
#define CanCMBswmMTxInd(chid)    ((uint16)((uint16)(chid) << CANCM_EIGHT) + 0xF0)
#define CanCMBswmMRxInd(chid)    ((uint16)((uint16)(chid) << CANCM_EIGHT) + 0xF1)
#define CanCMBswmMVolInd(chid)   ((uint16)((uint16)(chid) << CANCM_EIGHT) + 0xF2)
/* polyspace:end MISRA-C3:D4.9 [Not a defect:Justified] "No Impact of this rule violations." */

/*
#define CanCMBswmMTxInd(chid)    ((((uint16)(chid)) << CANCM_EIGHT) + ((uint16)0xF0))
#define CanCMBswmMRxInd(chid)    ((((uint16)(chid)) << CANCM_EIGHT) + ((uint16)0xF1))
#define CanCMBswmMVolInd(chid)   ((((uint16)(chid)) << CANCM_EIGHT) + ((uint16)0xF2))
*/
/*  polyspace:end<MISRA-C:19.7:Not a defect:Justify with annotations>
    No Impact of this rule violation     */
    
extern FUNC(void, CANCM_CODE) CanCM_Init(void);

/* polyspace +1 MISRA-C3:8.5 [Not a defect:Justfied] "No impact of this rule" */
extern FUNC(void, CANCM_CODE) CanCM_MainFunction(void);

extern FUNC(Std_ReturnType, CANCM_CODE) CanCM_GetCurrentNetworkState(
  NetworkHandleType CanCmChannelId,
  P2VAR(CanCM_CommStatType, AUTOMATIC, CANCM_APPL_DATA) CommStatPtr);
  
extern FUNC(void, CANCM_CODE) CanCM_GetVoltageFailCount(
  P2VAR(uint16, AUTOMATIC, CANCM_APPL_DATA) CountPtr);
  
extern FUNC(Std_ReturnType , CANCM_CODE) CanCM_GetCurrentVoltageMode(
  CanCM_ChannelType CanCmChannelId,
  P2VAR(CanCM_VolModType, AUTOMATIC, CANCM_APPL_DATA) VolModePtr);

#if  (STD_ON == CANCM_WAKEUP_SUPPORT)
extern FUNC(void, CANCM_CODE) CanCM_CheckWakeup(EcuM_WakeupSourceType source);
#endif

#endif
