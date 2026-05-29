/*============================================================================*/
/*                     HYUNDAI AUTOEVER SOFTWARE GROUP                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================
 * C Source:         %CanCM_PCTypes.h%
 * Instance:         RPL_1
 * %version:         1.0 %
 * %created_by:      ca027 %
 * %date_created:    2014/01/21 19:18:42 %
 *============================================================================*/
/* DESCRIPTION : AUTOSAR CAN Communication Manager                            */
/*============================================================================*/
/* FUNCTION COMMENT : Declarations for CanCM const parameters                 */
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
/* 1.0       | 14/May/2014 |   #921                        |  Kyung-Tae Kim   */
/*----------------------------------------------------------------------------*/
/* 1.0.1     | 13/Apr/2015 |   #247                         |  Kyung-Tae Kim  */
/*----------------------------------------------------------------------------*/
/* 1.0.2     | 11/Nov/2015 |   #3196                         |  Kyung-Tae Kim */
/*----------------------------------------------------------------------------*/
/* 1.0.3     | 22/Feb/2016 |   #3815                       | Kyung Tae Kim    */
/*----------------------------------------------------------------------------*/
/* 1.0.4     | 10/Jun/2016 |   #5027                       | Kyung Tae Kim    */
/*----------------------------------------------------------------------------*/
/* 1.5.12.1  | 24/Aug/2018 |   #13761                       |  Jeong-Su Lim   */
/*----------------------------------------------------------------------------*/
/* 1.5.13    | 13/Feb/2019 |   #15997                       |  Jeong-Su Lim   */
/*----------------------------------------------------------------------------*/
/* 1.5.15    | 12/Jan/2021 |   #27561                       |  Seung-Jae Kim  */
/*----------------------------------------------------------------------------*/
/* 1.5.16    | 31/Aug/2021 |   #31834                       |  Seung-Jae Kim  */
/*============================================================================*/
#ifndef CANCM_PCTYPES_H
#define CANCM_PCTYPES_H

#include "CanCM.h"
#include "ComM_Cfg.h"

#define CANCM_FALSE                                         0x00U
#define CANCM_TRUE                                          0x01U

#define CANCM_ADC_SAMPLE_MOD        ((uint8)0x02)

#define CANCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* polyspace-begin MISRA-C3:8.6 [Not a defect:Justified] "No impact of this rule violation" */
/* Global Structure Array for Channel Configuration */
extern CONST(Tdd_CanCM_ChannelConfig, CANCM_CONST) 
  CanCM_GaaChannelConfig[CANCM_NUMBER_OF_CHANNELS];
  
/* Global Array for Channel index mapping with ComM Channel Id */
extern CONST(NetworkHandleType, CANCM_CONST) 
  CanCM_GaaCanCMComMChannelMap[COMM_TOTAL_CHANNELS];
    
/* Global Array for Adc group Ids */
/*  polyspace<MISRA-C:8.12:Not a defect:Justify with annotations>               
    No Impact of this rule violation(Array size will fixed in linking time)   */
extern CONST(IoHwAb_IndexType, CANCM_CONST) CanCM_GaaCanCMAdcGroup[];
/* polyspace-end MISRA-C3:8.6 [Not a defect:Justified] "No impact of this rule violation" */

#define CANCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_CONST_8
#include "MemMap.h"
/* Global variable for number of ADC groups */
extern CONST(uint8, CANCM_CONST) CanCM_GddNumOfAdcGrp;
/* Global variable for filtering constant */
extern CONST(uint8, CANCM_CONST) CanCM_GucFiltConst;
#define CANCM_STOP_SEC_CONST_8
#include "MemMap.h"
#endif
