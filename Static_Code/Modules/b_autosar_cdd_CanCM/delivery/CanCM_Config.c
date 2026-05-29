/*============================================================================*/
/*                        HYUNDAI AUTOEVER SOFTWARE GROUP                     */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* %name:              CanIf_Config.c %
* %instance:          xar_1 %
* %version:           1.0 %
* %created_by:        ca027 %
* %date_created:     2015/11/11 16:05:50 %
*=============================================================================*/
/* DESCRIPTION : c source file of CanCM module                                */
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/*  Provision of variables of which value is set at link time                 */
/*                                                                            */
/*============================================================================*/
/* COPYRIGHT (C) HYUNDAI AUTOEVER 2012                                        */
/* AUTOMOTIVE ELECTRONICS                                                     */
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
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/* 1.0       | 11/Nov/2015 |    #3196                      | Kyung Tae Kim    */
/*----------------------------------------------------------------------------*/
/* 1.2       | 11/Nov/2015 |    #3555                      | Kyung Tae Kim    */
/*----------------------------------------------------------------------------*/
/* 1.2.1     | 22/Feb/2016 |    #3815                      | Kyung Tae Kim    */
/*----------------------------------------------------------------------------*/
/* 1.2.2     | 10/Jun/2016 |    #5027                      | Kyung Tae Kim    */
/*----------------------------------------------------------------------------*/
/* 1.5.16    | 31/Aug/2021 |    #31834                     | Seung Jae Kim    */
/*============================================================================*/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanCM_PCTypes.h"

#define CANCM_START_SEC_CONST_8
#include "MemMap.h"
CONST(uint8, CANCM_CONST) CanCM_GddNumOfAdcGrp = CANCM_NUMBER_OF_ADC_GROUPS;
CONST(uint8, CANCM_CONST) CanCM_GucFiltConst = CANCM_FILTERING_CONSTANT;
#define CANCM_STOP_SEC_CONST_8
#include "MemMap.h"

