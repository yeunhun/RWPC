/*============================================================================*/
/*                     HYUNDAI AUTOEVER SOFTWARE GROUP                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================
 * C Source:         %CanCM_Cbk.h%
 * Instance:         RPL_1
 * %version:         0.9.2 %
 * %created_by:      ca027 %
 * %date_created:    2013/07/08 15:58:01 %
 *============================================================================*/
/* DESCRIPTION : AUTOSAR CAN Communication Manager                            */
/*============================================================================*/
/* FUNCTION COMMENT : Definition for CanCM main functions                     */
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
/* 0.9.1     | 8/Jul/2013  |   xar~150 / xar~623           |  Kyung-Tae Kim   */
/* - Initial Creation                                                         */
/*----------------------------------------------------------------------------*/
/* 1.0       | 14/May/2014 |   #921                         |  Kyung-Tae Kim  */
/*----------------------------------------------------------------------------*/
/* 1.0.1     | 13/Apr/2015 |   #247                         |  Kyung-Tae Kim  */
/*----------------------------------------------------------------------------*/
/* 1.5.13    | 13/Feb/2019 |   #15997                       |  Jeong-Su Lim   */
/*----------------------------------------------------------------------------*/
/* 1.5.16    | 31/Aug/2021 |   #31834                       |  Seung-Jae Kim  */
/*============================================================================*/
#ifndef CANCM_CBK_H
#define CANCM_CBK_H

#include "CanCM.h"
#include "ComM.h"

/* Everything else goes here */
extern FUNC(void, CANCM_CODE) CanCM_ComModeIndication (
  NetworkHandleType ComMChannelId,
  ComM_ModeType comm_state);

#endif
