/*******************************************************************************
**                                                                            **
**  (C) 2019~2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dcm_PCTypes.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file contains type definitions for Dcm                   **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.10.0.0  07-Feb-2021   JYS          Redmine #28298 #27968                 **
** 1.0.3     06-Nov-2020   JYS          Redmine #26489                        **
** 1.0.2     07-Feb-2020   Sinil        Redmine #21594                        **
** 1.0.1     06-Dec-2019   Sinil        Redmine #20402                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef DCM_PCTYPES_H
#define DCM_PCTYPES_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Dcm_Types.h"

/*******************************************************************************
**                                Structures                                  **
*******************************************************************************/
typedef struct
{
  uint32 u32_TesterSourceAddr;    /* Tester address of the active Rx PduId */
  uint8  u8_Sid;                  /* Active Service Identifier */
  uint8  u8_SubFncId;             /* Active Sub function Id */
  uint8  u8_ResponseRequired;     /* Response has to be sent by BTL or Appl */
  uint8  u8_SecLvInfo;            /* Active Security */
  uint8  u8_SecAccessInvalidCount; /* Reprogramming of ECU requested or not */
  uint8  u8_ApplUpdated;           /* Application has to be updated or not */

}Dcm_ProgCond_Styp;

typedef struct
{
  /* Selected configuration,allows up to 8 configured variants */
  uint8  u8_ConfigSetId;

}Dcm_ConfigType_Styp;

typedef struct
{
  /* Referred TxPduId configured for a particular RxPduId */
  PduIdType dt_TxPduId;
  /* Request message copied for the PduId */
  uint16 u16_RxCopiedLength;
  /* Response message copied for the PduId */
  uint16 u16_TxCopiedLength;
  /* TxCOnfirmation PduId */
  uint16 u16_TxConfirmationPduId;
  /* Tester source address configured per protocol and provided
   * for the jump to Bootloader
   */
  uint16 u16_ProRxTesterSrcAddr;
  /* Rx address type */
  uint8 u8_RxAddrType;
}Dcm_PduIdTable_Styp;

typedef struct
{
  /* Look-Up Table id */
  uint8 u8_LookUpTableID;

  /* The corresponding mask */
  uint8 u8_Mask;

  /* Security level */
  uint8 u8_SecurityLevel;

} Dcm_LookUpTable_Styp;

typedef struct
{
  /* Sub function Id */
  uint16 u16_SubFunctionID;

  /* The Addressing Modes for the service to be supported */
  uint8 u8_AddrModeSupportMask;

  /* The sessions where the Sub Function shall be supported */
  uint8 u8_SessionSupportMask;

  /* The security levels where the sub function shall be supported */
  uint8 u8_SecLevelMask;

} Dcm_SubServiceConfig_Styp;


typedef struct
{
  /* Function pointer */
  void (*pDiagServiceFnc)(Dcm_MsgContextType *Lpst_MsgContext);

  /* Service ID */
  uint8 u8_ServiceId;

  /* Minimum request length */
  uint8 u8_MinReqLength;

  /* The Addressing Modes for the service to be supported */
  uint8 u8_AddrModeSupportMask;

  /* The sessions where the service shall be supported */
  uint8 u8_SessionSupportMask;

  /* The security levels where the service shall be supported */
  uint8 u8_SecLevelMask;

  /* Sub function available */
  boolean bl_SubFuncAvailable;

  /* Sub function Count */
  uint8 u8_SubFncCount;

  /* Sub function Identifier size */
  uint8 u8_SubFncIDSize;

  /* Sub function Ref */
  const Dcm_SubServiceConfig_Styp* pdt_SubFuncRef;

} Dcm_SIDConfig_Styp;

/* Structure for Diagnostics Sessions */
typedef struct
{
  /* P2 Server Maximum Timing */
  uint16 u16_SesP2ServerMax;
  /* P2* Server Maximum Timing */
  uint16 u16_SesP2StrServerMax;
  /* Session level value */
  Dcm_SesCtrlType dt_SessionLevel;
  /* Diagnostic session used for jump to Bootloader */
  Dcm_SessionForBootType u8_SesForBootLevel;
} Dcm_SessionConfig_Styp;

typedef struct
{
  /* Security level value */
  Dcm_SecLevelType dt_SecLevel;

  /* Size of security key */
  uint32 u32_SizeOfKey;

  /* Size of security seed */
  uint32 u32_SizeOfSeed;

  /* Delay time after failed security access */
  uint16 u16_SecDelayInvKey;

  /* Number of security accesses after which delay time is activated */
  uint8 u8_SecNumMaxAttDelay;

  /* Seed Request Max Length */
  uint16 u16_SeedRequestMaxLength;

} Dcm_SecurityLevConfig_Styp;

typedef struct
{
  /* DID Number */
  uint16 u16_DIDNumber;

  /* Size of DID */
  uint8 u8_SizeOfDID;

} Dcm_DspDIDConfig_Styp;

typedef struct
{
  /* DID Number */
  uint16 u16_RID;

  /* the security levels where the service shall be supported */
  uint8 u8_SecLevelMask;

  /* The sessions where the service shall be supported */
  uint8 u8_SessionSupportMask;

  /* Exact message length for this routine start request */
  uint8 u8_ReqMsgLenStart;

  /* Exact message length for this routine request result */
  uint8 u8_ReqMsgLenReqRes;

  /* Exact message length for this routine stop request */
  uint8 u8_ReqMsgLenStop;

} Dcm_DspRIDConfig_Styp;

/*******************************************************************************
**                               Enumerations                                 **
*******************************************************************************/
typedef enum
{
  DCM_TIMER_INACTIVE,
  DCM_P2SERVER_TIMER,
  DCM_P2SERVER_STAR_TIMER,
  DCM_S3SERVER_TIMER
} Dcm_TimerAct_Etyp;

typedef enum
{
  QUEUE_EMPTY,
  QUEUE_BUSY,
  QUEUE_COMPLETE
} Dcm_QueueSts_Etyp;

typedef enum
{
  DCM_REQ_IDLE = DCM_ZERO,
  DCM_REQ_BUSY,
  DCM_REQ_TD_BUSY,
  DCM_REQ_STOPPED
} Dcm_QueuedReqState_Etyp;

typedef struct
{
  uint16 u16_MsgStartPos;
  uint16 u16_MsgLength;
  uint16 u16_UsedLength;
  Dcm_QueueSts_Etyp en_InSts;
  Dcm_QueueSts_Etyp en_OutSts;
} Dcm_QueueMsg_Styp;

typedef enum
{
  DCM_MD_NO_NEED = DCM_ZERO,
  DCM_MD_NEED,
  DCM_MD_RECEIVED,
  DCM_MD_FINISHED
} Dcm_MetaDataState_Etyp;

#endif /* DCM_PCTYPES_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
