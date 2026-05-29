/*============================================================================*/
/*                     HYUNDAI AUTRON SOFTWARE GROUP                          */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================

* %name:              OsekNm.h %
* %instance:          xar_1 %
* %version:           1.2 %
* %created_by:        ca027 %

* %date_created:      2014/04/07 14:46:25 %
*=============================================================================*/
/* DESCRIPTION : header file for OSEK NM                                      */
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/* Provision of AUTOSAR OSEKNM Types and extern datatypes for OsekNm module     */
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
/* 1.4.2     | 08/Mar/2019 | #16398                        | JeongSu Lim      */
/* 1.5.0     | 13/May/2020 | #21188                        | JeongSu Lim      */
/* 1.5.1     | 27/Nov/2020 | #26628                        | Saemi Kwon       */
/*============================================================================*/




#ifndef OSEKNM_H
#define OSEKNM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "OsekNm_Cfg.h"           /* Configuration header file */
#include "Std_Types.h"         /* Standard type header */
#include "ComStack_Types.h"
#include "OsekNm_PCTypes.h"     /* OsekNm type definitions header */
#include "NmStack_Types.h"      /* Nm Interface type definitions header */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define OSEKNM_AR_MAJOR_VERSION  4
#define OSEKNM_AR_MINOR_VERSION  0
#define OSEKNM_AR_PATCH_VERSION  3

/* OSEKNM software version information */
#define OSEKNM_SW_MAJOR_VERSION  1
#define OSEKNM_SW_MINOR_VERSION  6
#define OSEKNM_SW_PATCH_VERSION  0

/*******************************************************************************
**                      Macro Definitions                                     **
*******************************************************************************/
/* polyspace-begin MISRA-C3:D4.9 [Not a defect:Justified] "Use function like-macro for removing unused argument compiler warning" */
#define OSEKNM_UNUSED(x)                          do { \
                                                    if((uint32)(x) != \
                                                    (uint32)OSEKNM_ZERO) {} \
                                                  } while(0)

/* API Service Ids */

/* Service id for OsekNm_Init */
#define OSEKNM_INIT_SID                        ((uint8)0x01)

/* Service id for OsekNm_SetUserData */
#define OSEKNM_SET_USERDATA_SID                ((uint8)0x06)

/* Service id for OsekNm_GetUserData */
#define OSEKNM_GET_USERDATA_SID                ((uint8)0x07)

/* Service id for OsekNm_GetNodeIdentifier */
#define OSEKNM_GET_NODEIDENTIFIER_SID          ((uint8)0x08)

/* Service id for OsekNm_GetLocalNodeIdentifier */
#define OSEKNM_GET_LOCALNODEIDENTIFIER_SID     ((uint8)0x09)

/* Service id for OsekNm_SetRepeatMessageBit */
#define OSEKNM_REPEAT_MESSAGEREQUEST_SID       ((uint8)0x0A)

/* Service id for OsekNm_GetPduData */
#define OSEKNM_GET_PDUDATA_SID                 ((uint8)0x15)

/* Service id for OsekNm_GetVersionInfo */
#define OSEKNM_GET_VERSIONINFO_SID             ((uint8)0x14)

/* Service id for OsekNm_MainFunction */
#define OSEKNM_MAINFUNCTION_SID                ((uint8)0x13)

/* Service id for OsekNm_TxConfirmation */
#define OSEKNM_TX_CONFIRMATION_SID             ((uint8)0x0F)

/* Service id for OsekNm_RxIndication */
#define OSEKNM_RX_INDICATION_SID               ((uint8)0x10)

/* Service id for OsekNm_StartTransmission */
#define OSEKNM_START_TRANSMISSION_SID          ((uint8)0x02)

/* Service id for OsekNm_StopTransmission */
#define OSEKNM_STOP_TRANSMISSION_SID           ((uint8)0x03)

/* Service id for OsekNm_StartBusLoadReduction */
#define OSEKNM_START_BUSLOADREDUCTION_SID      ((uint8)0x04)

/* Service id for OsekNm_StopBusLoadReduction */
#define OSEKNM_STOP_BUSLOADREDUCTION_SID       ((uint8)0x05)

/* Service id for OsekNm_TriggerTransmission */
#define OSEKNM_TRIGGER_TRANSMISSION_SID        ((uint8)0x0E)

/* Service id for OsekNm_PassiveStartUp */
#define OSEKNM_PASSIVE_STARTUP_SID             ((uint8)0x01)

/* Service id for OsekNm_NetworkRequest */
#define OSEKNM_NETWORK_REQUEST_SID             ((uint8)0x02)

/* Service id for OsekNm_NetworkRelease */
#define OSEKNM_NETWORK_RELEASE_SID             ((uint8)0x03)

/* Service id for OsekNm_DisableCommunication */
#define OSEKNM_DISABLE_COMMUNICATION_SID       ((uint8)0x0C)

/* Service id for OsekNm_EnableCommunication */
#define OSEKNM_ENABLE_COMMUNICATION_SID        ((uint8)0x0D)

/* Service id for OsekNm_GetState */
#define OSEKNM_GET_STATE_SID                   ((uint8)0x0B)

/* Service id for OsekNm_RequestBusSynchronization */
#define OSEKNM_REQUEST_BUSSYNCHRONIZATION_SID  ((uint8)0xC0)

/* Service id for OsekNm_CheckRemoteSleepIndication */
#define OSEKNM_CHECK_REMOTESLEEPINDICATION_SID ((uint8)0xD0)


/* Service id for OsekNm_RepeatMessageBitIndication */
#define OSEKNM_REPEATMESSAGEBITINDICATION_SID  ((uint8)0xE2)

/* Service id for OsekNm_TxTimeoutException */
#define OSEKNM_TXTIMEOUTEXCEPTION_SID          ((uint8)0xE3)

/* Service id for OsekNm_ControllerBusOff */
#define OSEKNM_CTRL_BUSOFF_SID                 ((uint8)0xE4)

/* Service id for OsekNm_CompareConfiguration */
#define OSEKNM_COMPARE_CONFIGURATION_SID       ((uint8)0xE5)

/* Service id for OsekNm_GetConfiguration */
#define OSEKNM_GET_CONFIGURATION_SID           ((uint8)0xE6)


/* DET Error Codes */
#define OSEKE_NO_INIT                         ((uint8)0x01)
#define OSEKE_INVALID_CHANNEL                 ((uint8)0x02)
#define OSEKE_INVALID_NM_CHANNEL              ((uint8)0x04)
#define OSEKE_DEV_NETWORK_TIMEOUT             ((uint8)0x11)
#define OSEKE_NULL_POINTER                    ((uint8)0x13)
#define OSEKE_NETWORK_TIMEOUT                 ((uint8)0x20)
#define OSEKE_CANIF_TRANSMIT_ERROR            ((uint8)0x21)
#define OSEKE_INVALID_PARAM                   ((uint8)0x22)

/* Module id */
#define OSEKNM_MODULE_ID                       ((uint16)0x1E)

/* Vendor id */
#define OSEKNM_VENDOR_ID                       ((uint8)39)


#define OSEKNM_INDEX_NODE                     ((uint8)0)
#define OSEKNM_INDEX_CMD                      ((uint8)1)
#define OSEKNM_INDEX_USERDATA_0               ((uint8)2)
#define OSEKNM_INDEX_USERDATA_1               ((uint8)3)
#define OSEKNM_INDEX_USERDATA_2               ((uint8)4)
#define OSEKNM_INDEX_USERDATA_3               ((uint8)5)
#define OSEKNM_INDEX_USERDATA_4               ((uint8)6)
#define OSEKNM_INDEX_USERDATA_5               ((uint8)7)

#define OSEKNM_SHIFT_SLEEPACK                 ((uint8)5)
#define OSEKNM_SHIFT_SLEEPIND                 ((uint8)4)


#define OSEKNM_FALSE                          ((uint8)0x00)
#define OSEKNM_TRUE                           ((uint8)0x01)
#define OSEKNM_INACTIVE_CHANNEL               ((uint8)0xFF)

#define OSEKNM_USER_DATA_LENGTH        ((uint8)0x06)
#define OSEKNM_USER_DATA_START_INDEX   ((uint8)0x02)
#define OSEKNM_NM_PDU_LENGTH           ((uint8)0x08)

/* merged from OsekNm */
/* OsekNm network states */
#define OSEKNM_REQUESTED            ((uint8)0x01)
#define OSEKNM_RELEASED             ((uint8)0x00)

#define OSEKNM_ZERO                 ((uint8)0x00)
#define OSEKNM_ONE                  ((uint8)0x01)
#define OSEKNM_THREE                ((uint8)0x03)
	

#define OSEKNM_NUMBER_OF_TIMERS     ((uint8)0x04)

#define OSEKNM_ENABLED              ((uint8)0x01)
#define OSEKNM_DISABLED             ((uint8)0x00)
#define OSEKNM_SET                  ((uint8)0x01)
#define OSEKNM_RESET                ((uint8)0x00)

/* NM message data access macro */
#define NM_CMD_MSK              ((uint8)0x0F)
#define NM_SLEEPIND_MASK        ((uint8)0x01)
#define NM_SLEEPACK_MASK        ((uint8)0x02)
#define NM_ADDRESS_MASK         ((uint16)0x3FF)

#define OSEKNM_NWCFG_ARRAY_SIZE   ((uint8)0x04)
#define OSEKNM_NWCFG_BIT_SIZE     ((uint8)0x20)    

#define NmRxSleepIndStat(ch)      (OsekNm_GunRxFlagStatus[(ch)].ddBitByteRecord.ucRxSleepInd)
#define NmRxNmMessageRecv(ch)     (OsekNm_GunRxFlagStatus[(ch)].ddBitByteRecord.ucRxNmMsgRecv)
#define NmRxRmtSleepInd(ch)       (OsekNm_GunRxFlagStatus[(ch)].ddBitByteRecord.ucRxRmtSleepInd)
#define NmRxRmtSleepIndNotif(ch)  (OsekNm_GunRxFlagStatus[(ch)].ddBitByteRecord.ucRxRmtSleepIndNotif)

#define NmTxSleepAckStat(ch)      (OsekNm_GunTxFlagStatus[(ch)].ddBitByteRecord.ucTxSleepAck)
#define NmTxLimphomeConf(ch)      (OsekNm_GunTxFlagStatus[(ch)].ddBitByteRecord.ucTxLimphomeConfirm)
#define NmTxRequest(ch)           (OsekNm_GunTxFlagStatus[(ch)].ddBitByteRecord.ucTxRequest)
#define NmTxWaitConfirm(ch)       (OsekNm_GunTxFlagStatus[(ch)].ddBitByteRecord.ucTxWaitConfirm)

#define NmSkippedOver(ch)         (OsekNm_GunInternFlagStatus[(ch)].ddBitByteRecord.ucSkippedOver)
#define NmWaitRing(ch)            (OsekNm_GunInternFlagStatus[(ch)].ddBitByteRecord.ucWaitRing)
#define NmRingToSend(ch)          (OsekNm_GunInternFlagStatus[(ch)].ddBitByteRecord.ucRingToSend)
#define NmRingStable(ch)          (OsekNm_GunInternFlagStatus[(ch)].ddBitByteRecord.ucRingStable)
#define NmSleepCancel(ch)         (OsekNm_GunInternFlagStatus[(ch)].ddBitByteRecord.ucSleepCancel)
#define NmWakeup(ch)              (OsekNm_GunInternFlagStatus[(ch)].ddBitByteRecord.ucWakeupByNm)

/* Macro for accessing Tx NM PDU */ 
#define NmTxPduSleepAck(ch)   (OsekNm_GaaTxPduData[(ch)].ddBitByteRecord.ucSleepAck)
#define NmTxPduDestAddr(ch)   (OsekNm_GaaTxPduData[(ch)].ddBitByteRecord.ucDestAddr)
#define NmTxPduSleepInd(ch)   (OsekNm_GaaTxPduData[(ch)].ddBitByteRecord.ucSleepInd)
#define NmTxPduCmd(ch)        (OsekNm_GaaTxPduData[(ch)].ddBitByteRecord.ucCmd)
#define NmTxPduDataPtr(ch)    (OsekNm_GaaTxPduData[(ch)].ucMaskByte)
#define NmTxPduUserData0(ch) (OsekNm_GaaTxPduData[(ch)].ucMaskByte[2])
#define NmTxPduUserData1(ch) (OsekNm_GaaTxPduData[(ch)].ucMaskByte[3])
#define NmTxPduUserData2(ch) (OsekNm_GaaTxPduData[(ch)].ucMaskByte[4])
#define NmTxPduUserData3(ch) (OsekNm_GaaTxPduData[(ch)].ucMaskByte[5])
#define NmTxPduUserData4(ch) (OsekNm_GaaTxPduData[(ch)].ucMaskByte[6])
#define NmTxPduUserData5(ch) (OsekNm_GaaTxPduData[(ch)].ucMaskByte[7])

/* Macro for accessing Rx NM PDU */ 
#define NmRxPduSleepAck(ch)   (OsekNm_GaaRxPduData[(ch)].ddBitByteRecord.ucSleepAck)
#define NmRxPduDestAddr(ch)   (OsekNm_GaaRxPduData[(ch)].ddBitByteRecord.ucDestAddr)
#define NmRxPduSleepInd(ch)   (OsekNm_GaaRxPduData[(ch)].ddBitByteRecord.ucSleepInd)
#define NmRxPduCmd(ch)        (OsekNm_GaaRxPduData[(ch)].ddBitByteRecord.ucCmd)
#define NmRxPduDataPtr(ch)    (OsekNm_GaaRxPduData[(ch)].ucMaskByte)

#define NmRxPduUserData0(ch) (OsekNm_GaaRxPduData[(ch)].ucMaskByte[2])
#define NmRxPduUserData1(ch) (OsekNm_GaaRxPduData[(ch)].ucMaskByte[3])
#define NmRxPduUserData2(ch) (OsekNm_GaaRxPduData[(ch)].ucMaskByte[4])
#define NmRxPduUserData3(ch) (OsekNm_GaaRxPduData[(ch)].ucMaskByte[5])
#define NmRxPduUserData4(ch) (OsekNm_GaaRxPduData[(ch)].ucMaskByte[6])
#define NmRxPduUserData5(ch) (OsekNm_GaaRxPduData[(ch)].ucMaskByte[7])

/* NM message types */
#define OSEKNM_ALIVE     ((uint8)1)
#define OSEKNM_RING      ((uint8)2)
#define OSEKNM_LIMPHOME  ((uint8)4)

/* Default user data */
#define OSEKNM_USER_DATA_DEFAULT_0        ((uint8)0x00)
#define OSEKNM_USER_DATA_DEFAULT_1        ((uint8)0x00)
#define OSEKNM_USER_DATA_DEFAULT_2        ((uint8)0x00)
#define OSEKNM_USER_DATA_DEFAULT_3        ((uint8)0x00)
#define OSEKNM_USER_DATA_DEFAULT_4        ((uint8)0xFF)
#define OSEKNM_USER_DATA_DEFAULT_5        ((uint8)0xFF)

/* Normal user data */
#define OSEKNM_USER_DATA_NORMAL_0        ((uint8)0x00)
#define OSEKNM_USER_DATA_NORMAL_1        ((uint8)0x00)
#define OSEKNM_USER_DATA_NORMAL_2        ((uint8)0x00)
#define OSEKNM_USER_DATA_NORMAL_3        ((uint8)0x00)
#define OSEKNM_USER_DATA_NORMAL_4        ((uint8)0xFF)
#define OSEKNM_USER_DATA_NORMAL_5        ((uint8)0xFF)

/* Maximum count for Limphome */
#define OSEKNM_TX_LIMIT ((uint8)8)
#define OSEKNM_RX_LIMIT ((uint8)4)

/* polyspace-end MISRA-C3:D4.9 [Not a defect:Justified] "Use function like-macro for removing unused argument compiler warning" */
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/


/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define OSEKNM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, OSEKNM_CODE) OsekNm_Init(void);

#if (OSEKNM_VERSION_INFO_API == STD_ON)
extern FUNC(void, OSEKNM_CODE) OsekNm_GetVersionInfo
              (P2VAR(Std_VersionInfoType, AUTOMATIC, OSEKNM_APPL_DATA) versionInfo);
#endif

#if(OSEKNM_USER_DATA_ENABLED == STD_ON) 
extern FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_SetUserData 
                  (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle,
                   CONSTP2CONST(uint8, AUTOMATIC, OSEKNM_APPL_CONST) nmUserDataPtr);
#endif
            
#if (OSEKNM_USER_DATA_ENABLED == STD_ON)
extern FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_GetUserData 
                  (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle,
                     CONSTP2VAR(uint8, AUTOMATIC, OSEKNM_APPL_DATA) nmUserDataPtr);
#endif

extern FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_GetLocalNodeIdentifier
                  (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle,
                      CONSTP2VAR(uint8, AUTOMATIC, OSEKNM_APPL_DATA) nmNodeIdPtr);

extern FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_GetNodeIdentifier
                  (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle,
                      CONSTP2VAR(uint8, AUTOMATIC, OSEKNM_APPL_DATA) nmNodeIdPtr);

extern FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_PassiveStartUp
                  (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle);
           
extern FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_NetworkRequest
                  (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle);

extern FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_NetworkRelease
                  (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle);

#if(OSEKNM_COM_CONTROL_ENABLED == STD_ON)
extern FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_DisableCommunication
                  (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle);
#endif

#if(OSEKNM_COM_CONTROL_ENABLED == STD_ON)
extern FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_EnableCommunication
                  (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle);
#endif


extern FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_GetPduData
                   (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle, 
                      CONSTP2VAR(uint8, AUTOMATIC, OSEKNM_APPL_DATA) nmPduDataPtr);

extern FUNC (Std_ReturnType, OSEKNM_CODE) OsekNm_GetState
                  (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle,
                  CONSTP2VAR(Nm_StateType, AUTOMATIC, OSEKNM_APPL_DATA) nmStatePtr,
                    CONSTP2VAR(Nm_ModeType, AUTOMATIC, OSEKNM_APPL_DATA) nmModePtr);

#if(OSEKNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON)
extern FUNC (Std_ReturnType, OSEKNM_CODE) OsekNm_RequestBusSynchronization
                  (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle);
#endif

#if(OSEKNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
extern FUNC (Std_ReturnType, OSEKNM_CODE) OsekNm_CheckRemoteSleepIndication
             (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle,
             CONSTP2VAR(boolean, AUTOMATIC, OSEKNM_APPL_DATA) nmRemoteSleepIndPtr);
#endif                

extern FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_RepeatMessageRequest
                   (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle);
                   

/* For network configuration feature */
extern FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_GetConfiguration
 (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle,
 CONSTP2VAR(NetworkConfigurationType, AUTOMATIC, OSEKNM_APPL_DATA) NwConfigPtr);
 

#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"

#endif  /* OSEKNM_H */

/*******************************************************************************
**                          END OF FILE                                       **
*******************************************************************************/
