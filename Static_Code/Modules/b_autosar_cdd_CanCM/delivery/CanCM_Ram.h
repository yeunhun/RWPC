/*============================================================================*/
/*                     HYUNDAI AUTOEVER SOFTWARE GROUP                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================
 * C Source:         %CanCM_Ram.c%
 * Instance:         RPL_1
 * %version:         0.9.2 %
 * %created_by:      ca027 %
 * %date_created:    2014/02/03 17:24:01 %
 *============================================================================*/
/* DESCRIPTION : AUTOSAR CAN Communication Manager                            */
/*============================================================================*/
/* FUNCTION COMMENT : Declaration for CanCM global variables                   */
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
/* 1.0.0     | 04/Feb/2014 |   xar~150 / xar~623           |  Kyung-Tae Kim   */
/*----------------------------------------------------------------------------*/
/* 1.0.1     | 14/Jun/2016 |   #5027                       |  Kyung-Tae Kim   */
/*----------------------------------------------------------------------------*/
/* 1.5.15    | 12/Jan/2021 |   #27561                      |  Seung-Jae Kim   */
/*----------------------------------------------------------------------------*/
/* 1.5.16    | 31/Aug/2021 |   #31834                      |  Seung-Jae Kim   */
/*============================================================================*/

#ifndef CANCM_RAM_H
#define CANCM_RAM_H

#include "CanCM.h"             /* CanCM main header file */
#include "CanCM_InitTypes.h"   /* CanCM type definition header file */

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*  polyspace:begin<MISRA-C:8.12:Not a defect:Justify with annotations>No Impact of this rule violation(Array size will fixed in linking time)   */    

/* Global array saving previous battery voltage value */
/* polyspace +1 MISRA-C3:8.6 [Not a defect:Justified] "No impact of this rule violation" */
extern VAR(uint16, CANCM_VAR_NOINIT) CanCM_GaaCanCMAdcGroupVal[];
/* Global Variable for Current Voltage Mode*/
extern VAR(CanCM_VolModType, CANCM_VAR_NOINIT) 
       CanCM_GddVolMod[];
/* Global Variable for Current Communication State*/
extern VAR(CanCM_CommStatType, CANCM_VAR_NOINIT) 
       CanCM_GddCommStat[];
/* Global Variable for Network Activation Timer Counter */
extern VAR(uint16, CANCM_VAR_NOINIT) 
       CanCM_GddNTimerCounter[];
/* Global Variable for Voltage Error Timer Counter */
extern VAR(uint16, CANCM_VAR_NOINIT) 
       CanCM_GddETimerCounter[];
/* Global Variable for Reception DM Start Timer Counter */
extern VAR(uint16, CANCM_VAR_NOINIT) 
       CanCM_GddRTimerCounter[];
/* Global Variable for Battery Voltage */
extern VAR(uint16, CANCM_VAR_NOINIT) CanCM_GddBatVol;
/* Global Variable for Internal Status */
extern VAR(Tun_CanCMFlagStatus, CANCM_VAR_NOINIT)  
       CanCM_GunFlagStatus[];

/*  polyspace:end<MISRA-C:8.12:Not a defect:Justify with annotations>No Impact of this rule violation(Array size will fixed in linking time)   */    

#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* Global Variable for Battery Voltage Fail Count */
extern VAR(uint16, CANCM_VAR_NOINIT) CanCM_GddBatVolFailCnt;
extern VAR(uint16, CANCM_VAR_NOINIT) CanCM_GusAdcSampleCnt;
#define CANCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#if (STD_ON == CANCM_DEV_ERROR_DETECT)
#define CANCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to store Initialization status of CanCM */
extern VAR (boolean, CANCM_VAR_NOINIT) CanCM_GblCanCMStatus;

#define CANCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif


#endif
