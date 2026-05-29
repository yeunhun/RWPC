/*============================================================================*/
/*                     HYUNDAI AUTOEVER SOFTWARE GROUP                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================
 * C Source:         %CanCM_Ram.c%
 * Instance:         RPL_1
 * %version:         0.9.2 %
 * %created_by:      ca027 %
 * %date_created:    2014/02/03 17:24:00 %
 *============================================================================*/
/* DESCRIPTION : AUTOSAR CAN Communication Manager                            */
/*============================================================================*/
/* FUNCTION COMMENT : Definition for CanCM global variables                   */
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
/* 0.9.1     | 25/Oct/2013 |   xar~150 / xar~623           |  Kyung-Tae Kim   */
/*----------------------------------------------------------------------------*/
/* 1.0.0     | 04/Feb/2014 |   xar~150 / xar~623           |  Kyung-Tae Kim   */
/*----------------------------------------------------------------------------*/
/* 1.5.15    | 31/Aug/2021 |   #31834                      |  Seung-Jae Kim   */
/*============================================================================*/


#include "CanCM.h"
#include "CanCM_Ram.h"

#define CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global Variable for Current Voltage Mode*/
VAR(CanCM_VolModType, CANCM_VAR_NOINIT) CanCM_GddVolMod[CANCM_NUMBER_OF_CHANNELS];
/* Global Variable for Current Communication State*/
VAR(CanCM_CommStatType, CANCM_VAR_NOINIT) CanCM_GddCommStat[CANCM_NUMBER_OF_CHANNELS];
/* Global Variable for Network Activation Timer Counter */
VAR(uint16, CANCM_VAR_NOINIT) CanCM_GddNTimerCounter[CANCM_NUMBER_OF_CHANNELS];
/* Global Variable for Voltage Error Timer Counter */
VAR(uint16, CANCM_VAR_NOINIT) CanCM_GddETimerCounter[CANCM_NUMBER_OF_CHANNELS];
/* Global Variable for Reception DM Start Timer Counter */
VAR(uint16, CANCM_VAR_NOINIT) CanCM_GddRTimerCounter[CANCM_NUMBER_OF_CHANNELS];
/* Global Variable for Internal Status */
VAR(Tun_CanCMFlagStatus, CANCM_VAR_NOINIT)  CanCM_GunFlagStatus[CANCM_NUMBER_OF_CHANNELS];
/* Global Variable for Battery Voltage */
VAR(uint16, CANCM_VAR_NOINIT) CanCM_GddBatVol;

#define CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* Global Variable for Battery Voltage Fail Count */
VAR(uint16, CANCM_VAR_NOINIT) CanCM_GddBatVolFailCnt;
/* Global Variable for ADC sampling period */
VAR(uint16, CANCM_VAR_NOINIT) CanCM_GusAdcSampleCnt;

#define CANCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#if (STD_ON == CANCM_DEV_ERROR_DETECT)
#define CANCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to store Initialization status of CanCM */
VAR (boolean, CANCM_VAR_NOINIT) CanCM_GblCanCMStatus;

#define CANCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif
