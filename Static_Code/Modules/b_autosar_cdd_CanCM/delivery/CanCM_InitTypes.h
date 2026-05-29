/*============================================================================*/
/*                     HYUNDAI AUTOEVER SOFTWARE GROUP                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================
 * C Source:         %CanCM_InitTypes.h%
 * Instance:         RPL_1
 * %version:         0.9.2 %
 * %created_by:      ca027 %
 * %date_created:    2014/02/03 16:19:37 %
 *============================================================================*/
/* DESCRIPTION : AUTOSAR CAN Communication Manager                            */
/*============================================================================*/
/* FUNCTION COMMENT : Header file for CanCM Type Definitions                  */
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
/* 1.0.0     | 09/Jun/2014 |   #1008                       |  Kyung-Tae Kim   */
/*----------------------------------------------------------------------------*/
/* 1.0.1     | 16/Mar/2015 |   #2335                       |  Kyung-Tae Kim   */
/*----------------------------------------------------------------------------*/
/* 1.0.2     | 02/Apr/2015 |   #2413                       |  Kyung-Tae Kim   */
/*----------------------------------------------------------------------------*/
/* 1.1       | 20/Apr/2015 |   #2500                        |  Kyung-Tae Kim  */
/*----------------------------------------------------------------------------*/
/* 1.2       | 20/Jul/2015 |   #2554                        |  Kyung-Tae Kim  */
/*----------------------------------------------------------------------------*/
/* 1.2.1     | 26/Aug/2015 |   #2997                        |  Kyung-Tae Kim  */
/*----------------------------------------------------------------------------*/
/* 1.2.2     | 16/Sep/2015 |   #3155                        |  Kyung-Tae Kim  */
/*----------------------------------------------------------------------------*/
/* 1.2.3     | 21/Sep/2015 |   #2720                        |  Kyung-Tae Kim  */
/*----------------------------------------------------------------------------*/
/* 1.5.11    | 22/Aug/2017 |   #9277 #4972                  |  Kyung-Tae Kim  */
/*----------------------------------------------------------------------------*/
/* 1.5.13    | 13/Feb/2019 |   #15997                       |  Jeong-Su Lim   */
/*----------------------------------------------------------------------------*/
/* 1.5.16    | 31/Aug/2021 |   #31834                       |  Seung-jae Kim  */
/*============================================================================*/

#ifndef CANCM_INIT_TYPES_H
#define CANCM_INIT_TYPES_H
#if (STD_ON == CANCM_DEM_STATUS)
#include "Dem.h"
#endif
#include "Std_Types.h"         /* Standard type header */
#include "ComStack_Types.h"

/* AUTOSAR specification version information */
#define CANCM_PCTYPES_AR_MAJOR_VERSION   (4)
#define CANCM_PCTYPES_AR_MINOR_VERSION   (0)
#define CANCM_PCTYPES_AR_PATCH_VERSION   (3)

/* File version information */
#define CANCM_PCTYPES_SW_MAJOR_VERSION   (1)
#define CANCM_PCTYPES_SW_MINOR_VERSION   (5)



typedef struct 
{
  /* voltage range */
  uint16 ddAbnormalUpper;
  uint16 ddAbnormalLower;
  uint16 ddCriticalUpper;
  uint16 ddCriticalLower;
  uint16 ddHysteresis;
  
  /* timing parameters */
  uint16 ddActivationTime;
  uint16 ddDelayTimeCritical;
  uint16 ddTimeoutStartTime;
  uint8 ucComMChannelId;
  uint8 ucChannelId;
  #if (STD_ON == CANCM_DEM_STATUS)  
  Dem_EventIdType ddEventId;
  #endif
  uint8 ucCanIfCtrlId;
  #if  (STD_ON == CANCM_WAKEUP_SUPPORT)
  EcuM_WakeupSourceType ddWakSrc;
  IoHwAb_IndexType ddWakPin;
  #endif
} Tdd_CanCM_ChannelConfig;

/*  polyspace:begin<MISRA-C:18.4:Not a defect:Justify with annotations>
    No Impact of this rule violation                                          */
typedef union
{
  struct
  {
    /*
     * Check if the bit access is little endian and define the bit fields
     * accordingly
     */
  #if (CPU_BIT_ORDER == LSB_FIRST)
    unsigned int ucUnused:2;
    unsigned int ucNmDisabled :1;
    unsigned int ucWakEvt:1;
    unsigned int ucWakChkEnabled :1;
    unsigned int ucTxDisabled :1;
    unsigned int ucDtcDisabled:1;
    unsigned int ucVolFailed:1;
  #else
    unsigned int ucVolFailed:1;
    unsigned int ucDtcDisabled:1;
    unsigned int ucTxDisabled :1;
    unsigned int ucWakChkEnabled :1;
    unsigned int ucWakEvt :1;
    unsigned int ucNmDisabled :1;
    unsigned int ucUnused:2;
  #endif
  }ddBitByteRecord;

  uint8 ucMaskByte;
  
}Tun_CanCMFlagStatus;
/*  polyspace:end<MISRA-C:18.4:Not a defect:Justify with annotations>
    No Impact of this rule violation                                          */

typedef enum
{
  CANCM_COMM_STAT_INACTIVE        = 0,
  CANCM_COMM_STAT_START           = 1,
  CANCM_COMM_STAT_ACTIVE          = 2,
  CANCM_COMM_STAT_SHUTDOWN        = 3,
  CANCM_COMM_STAT_UNDEFINED       = 4
} CanCM_CommStatType;

typedef enum
{
  CANCM_VOL_MODE_NORMAL           = 0,
  CANCM_VOL_MODE_ABNORMAL         = 1,
  CANCM_VOL_MODE_CRITICAL         = 2,
  CANCM_VOL_MODE_UNDEFINED        = 3
} CanCM_VolModType;


enum
{
  CANCM_COMM_STAT_TX_DISABLED                   = 0,
  CANCM_COMM_STAT_TX_ENABLED                    = 1,
};

enum
{
  CANCM_COMM_STAT_RX_DISABLED                  = 0,
  CANCM_COMM_STAT_RX_ENABLED_DM_ENABLED        = 1,
  CANCM_COMM_STAT_RX_ENABLED_DM_DISABLED       = 2,
};

typedef uint8 CanCM_ChannelType;

#endif
