/*============================================================================*/
/*                     HYUNDAI AUTRON SOFTWARE GROUP                          */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================
* %name:              OsekNm_PCTypes.h %
* %instance:          xar_1 %
* %version:           1.1.3 %
* %created_by:        ca027 %

* %date_created:      2014/04/03 19:19:25 %
*=============================================================================*/
/* DESCRIPTION : header file for OSEK NM                                      */
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/* Provision of the structure definitions for OsekNm module                   */
/*                                                                            */
/*============================================================================*/
/* COPYRIGHT (C) HYUNDAI AUTRON 2012                                          */
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
/* 1.0.0     | 16/May/2011 | Initial Creation              | Kyung Tae Kim    */
/* 1.4.0     | 28/Dec/2018 | #15280                        | JeongSu Lim      */
/* 1.5.0     | 13/May/2020 | #21188                        | JeongSu Lim      */
/* 1.5.1     | 27/Nov/2020 | #26628                        | Saemi Kwon       */
/* 1.6.0     | 20/Jan/2021 | #27588                        | Saemi Kwon       */
/*============================================================================*/

#ifndef OSEKNM_PCTYPES_H
#define OSEKNM_PCTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "OsekNm.h"         /* OSEKNM APIs header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define OSEKNM_PCTYPES_AR_MAJOR_VERSION   4
#define OSEKNM_PCTYPES_AR_MINOR_VERSION   0
#define OSEKNM_PCTYPES_AR_PATCH_VERSION   3

/* File version information */
#define OSEKNM_PCTYPES_SW_MAJOR_VERSION   1
#define OSEKNM_PCTYPES_SW_MINOR_VERSION   6

/*******************************************************************************
**                      MACRO Definitions                                     **
*******************************************************************************/
#define OSEKNM_EIGHT                ((uint8)0x08)
#define OSEKNM_INVALID_ID           0xFFFF
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* For network configuration feature */
typedef uint32 NetworkConfigurationType;

/* For pointer calculation */
typedef signed int OsekNm_PtrSize;
/* Structure for OsekNm Channel Config Type */
typedef struct 
{
  /* L-PDU handle of the NM PDU to be transmitted by CanIf_Transmit */
  PduIdType ddTxPduId;
  uint16 usTimeoutMax;
  uint16 usTimeoutError;
  uint16 usTimeoutWaitSleep;
  uint16 usTimeoutTyp;
  /* Channel identifier configured for the respective instance of the NM */
  NetworkHandleType ddNmChannelId;
  /* OsekNm Channel Node ID */
  uint8 ucNodeId;
  /* CAN Controller Id */
  uint8 ucControllerId;
  /*OsekNm Tx Pdu Id*/
  PduIdType ddOsekNmTxPduId;
}Tdd_OsekNm_ChannelConfig;

/* OSEK NM */
typedef enum
{
  OSEKNM_STATE_UNINIT            = 0,
  OSEKNM_STATE_RESET             = 1,
  OSEKNM_STATE_NORMAL            = 2,
  OSEKNM_STATE_LIMPHOME          = 3
} OsekNm_StateType;

typedef enum
{
  OSEKNM_MODE_UNINIT             = 0,
  OSEKNM_MODE_AWAKE              = 1,             
  OSEKNM_MODE_PREPARE_SLEEP      = 2,     
  OSEKNM_MODE_WAIT_SLEEP         = 3,        
  OSEKNM_MODE_BUS_SLEEP          = 4
} OsekNm_ModeType;

/* polyspace-begin MISRA-C3:19.2 [Not a defect:Justified] "No Impact of this rule violation" */
typedef union
{
  struct
  {
    /*
     * Check if the bit access is little endian and define the bit fields
     * accordingly
     */
    #if (BITFIELD_ORDER == LSB_FIRST)
    unsigned int ucUnused:2;
    unsigned int ucWakeupByNm:1;
    unsigned int ucSleepCancel:1;
	  unsigned int ucRingStable:1;
    unsigned int ucRingToSend:1;
    unsigned int ucWaitRing:1;
    unsigned int ucSkippedOver:1;
    #else
    unsigned int ucSkippedOver:1;
    unsigned int ucWaitRing:1;
    unsigned int ucRingToSend:1;
	  unsigned int ucRingStable:1;
	  unsigned int ucSleepCancel:1;
    unsigned int ucWakeupByNm:1;
    unsigned int ucUnused:2;
    #endif
  }ddBitByteRecord;

  uint8 ucMaskByte;

}Tun_OsekNmInternFlagStatus;

typedef union
{
  struct
  {
    /*
     * Check if the bit access is little endian and define the bit fields
     * accordingly
     */
    #if (BITFIELD_ORDER == LSB_FIRST)
    unsigned int ucUnused:4;
    unsigned int ucRxNmMsgRecv:1;
    unsigned int ucRxSleepInd:1;
	  unsigned int ucRxRmtSleepInd:1;
	  unsigned int ucRxRmtSleepIndNotif:1;
    #else
	  unsigned int ucRxRmtSleepIndNotif:1;
	  unsigned int ucRxRmtSleepInd:1;
	  unsigned int ucRxSleepInd:1;
	  unsigned int ucRxNmMsgRecv:1;
	  unsigned int ucUnused:4;
    #endif
  }ddBitByteRecord;

  uint8 ucMaskByte;

}Tun_OsekNmRxFlagStatus;

typedef union
{
  struct
  {
    /*
     * Check if the bit access is little endian and define the bit fields
     * accordingly
     */
    #if (BITFIELD_ORDER == LSB_FIRST)
    unsigned int ucUnused:4;
    unsigned int ucTxWaitConfirm:1;
    unsigned int ucTxRequest:1;
    unsigned int ucTxLimphomeConfirm:1;
    unsigned int ucTxSleepAck:1;
    #else
    unsigned int ucTxSleepAck:1;
    unsigned int ucTxLimphomeConfirm:1;
    unsigned int ucTxRequest:1;
    unsigned int ucTxWaitConfirm:1;
    unsigned int ucUnused:4;
    #endif
  }ddBitByteRecord;

  uint8 ucMaskByte;

}Tun_OsekNmTxFlagStatus;

typedef union
{
  uint8 ucMaskByte[OSEKNM_EIGHT];

  #if (BITFIELD_ORDER == MSB_FIRST)
  struct
  {
    unsigned int ucDestAddr          :8;   /* bit  7...0 ;           byte 0   */
    unsigned int ucUnused1           :2;
    unsigned int ucSleepAck          :1;   /* bit 13     ; bit 5              */
    unsigned int ucSleepInd          :1;   /* bit 12     ; bit 4              */
    unsigned int ucUnused2           :1;
    unsigned int ucCmd               :3;   /* bit 11...8 ; bit 3...0 byte 1   */
  }ddBitByteRecord;
  #elif (BITFIELD_ORDER == LSB_FIRST )
  struct
  {
    unsigned int ucDestAddr          :8;   /* bit  7...0 ;           byte 0   */
    unsigned int ucCmd               :3;   /* bit 11...8 ; bit 3...0 byte 1   */
    unsigned int ucUnused2           :1;
    unsigned int ucSleepInd          :1;   /* bit 12     ; bit 4              */
    unsigned int ucSleepAck          :1;   /* bit 13     ; bit 5              */
    unsigned int ucUnused1           :2;
  }ddBitByteRecord;
    #else
      #error "Missing bit order for typedef Tun_OsekNmPduType!"
    #endif
}Tun_OsekNmPduType;

typedef struct
{
  P2FUNC(void, OSEKNM_CALLOUT_CODE, pTxNmPduCallout)
  	(PduIdType PduId, P2CONST(PduInfoType, AUTOMATIC, OSEKNM_CONST) PduInfoPtr);
}OsekNm_TxNmPduCallOut;

/* polyspace-END MISRA-C3:19.2 [Not a defect:Justified] "No Impact of this rule violation" */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define OSEKNM_START_SEC_CONST_8
#include "MemMap.h"

extern CONST(uint8, OSEKNM_CONST) OsekNm_GddNumberOfRxPdu;

#define OSEKNM_STOP_SEC_CONST_8
#include "MemMap.h"


#define OSEKNM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* polyspace-begin MISRA-C3:8.11 [Not a defect:Justified] "No Impact of this rule violation(Array size will fixed in linking time)" */
/* Extern definition for Channel Map array for mapping active and inactive channels */
extern CONST(NetworkHandleType, OSEKNM_CONST) 
                     OsekNm_GaaInternalChannelMap[OSEKNM_MAX_NM_CHANNEL_ID + 1];

extern CONST(NetworkHandleType, OSEKNM_CONST) 
                  OsekNm_GaaOsekNmCanIfChannelMap[OSEKNM_MAX_CANIF_CTRL_ID + 1];

extern CONST(NetworkHandleType, OSEKNM_CONST) 
                      OsekNm_GaaOsekNmRxPduIdChannelMap[];

extern CONST(NetworkHandleType, OSEKNM_CONST) 
                   OsekNm_GaaOsekNmTxPduIdChannelMap[];

/* Extern definition for Channel configuration information array (for all active channels)  */
extern CONST(Tdd_OsekNm_ChannelConfig, OSEKNM_CONST)
                             OsekNm_GaaChannelConfig[OSEKNM_NUMBER_OF_CHANNELS];


#define OSEKNM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if(OSEKNM_TX_NM_PDU_CALLOUT_SUPPORT == STD_ON)
#define OSEKNM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for Tx Nm Pdu Callout structure */
extern CONST(OsekNm_TxNmPduCallOut, OSEKNM_CONST) OsekNm_GaaOsekNmTxNmPduCallout[];
#define OSEKNM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/* polyspace-END MISRA-C3:8.11 [Not a defect:Justified] "No Impact of this rule violation(Array size will fixed in linking time)" */
#endif /* OSEKNM_PCTYPES_H */

/*******************************************************************************
**                          END OF FILE                                       **
*******************************************************************************/
