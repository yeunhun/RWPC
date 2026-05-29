/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dcm_Globals.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Header file for Dcm_Globals.c                                 **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.23.1.0  06-Jun-2022   JSCHOI       Redmine #36032                        **
** 1.22.0    09-Nov-2021   JYS          Redmine #29462, #33131                **
** 1.21.0    27-Sep-2021   JYS          Redmine #29449                        **
** 1.13.0.0  05-Apr-2020   JYS          Redmine #29188                        **
** 1.0.2     05-Nov-2020   JYS          Redmine #26443                        **
** 1.0.1     06-Dec-2019   Sinil        Redmine #20402                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef DCM_GLOBALS_H
#define DCM_GLOBALS_H

/*******************************************************************************
**                         Header File Include Section                        **
*******************************************************************************/
#include "Dcm_Cfg.h"
#include "Dcm_PCTypes.h"

/*******************************************************************************
**                Global Variable Extern Declaration                          **
*******************************************************************************/
#define BTL_START_SEC_VAR_NO_INIT
#include "Btl_MemMap.h"

/* Maintains current Session */
extern Dcm_SesCtrlType Dcm_Gdt_CurrentSession;

#if (DCM_LINKCONTROL_SERVICE == STD_ON)
/* Maintains Link Control Verification */
extern boolean Dcm_Gbl_LinkCtrlVrfySuccess;
#endif

/* Maintains current Security Level */
extern Dcm_SecLevelType  Dcm_Gdt_SecurityLevel;

/* Buffers maintained by Dcm */
extern uint8* Dcm_Gau8_RxBuffer;

extern uint8 Dcm_Gau8_TxBuffer[DCM_MAX_TX_BUFFER_SIZE];

extern uint8 Dcm_Gau8_TPReqBuffer[DCM_TPRX_BUFFER_SIZE];

extern uint8 Dcm_Gau8_ResponseBuf[DCM_RESP_BUFFER_SIZE];

extern uint8 Dcm_Gau8_MetaDataBuffer[DCM_REVISED_SECUREFLASHING_METADATA_LENGTH];

/* Global Variable to store the status of the timer */
extern Dcm_TimerAct_Etyp Dcm_Gen_ActiveTimer;

extern uint16 Dcm_Gu16_Timer;

extern uint32 Dcm_Gu32_SecDelayTimer;

/* Holds count of Response Pending responses send */
extern uint8 Dcm_Gu8_MaxNoOfRespPend;

/* Holds current requested Service Id */
extern uint8 Dcm_Gu8_SID;

extern uint8 Dcm_Gu8_SessionTableIndex;

/* Global variables used to maintain states during processing of Security Access
 * service
 */
extern uint8 Dcm_Gu8_ExpSecKeyNo;

extern uint8 Dcm_Gu8_SecAccessAttempt;

extern uint8 Dcm_Gu8_SecAccessMaxAttDelay;

/* Global variables used to maintain states during processing new request */
extern uint8            Dcm_Gu8_ActiveRxPduId;

extern uint8            Dcm_Gu8_ActiveTxPduId;

extern uint16           Dcm_Gu16_RequestLength;

extern uint16           Dcm_Gu16_TxLength;

extern boolean          Dcm_Gbl_WaitForEcuReset;

extern boolean          Dcm_Gbl_NegRespState;

extern PduIdType        Dcm_Gdt_DcmTxConfPduId;

extern Dcm_OpStatusType Dcm_Gdt_OpStatus;

/* Holds Pending state during processing new request */
extern boolean Dcm_Gbl_ReqProcPending;

/* Holds Pending transmit state until confirmation of NRC transmit is called */
extern boolean Dcm_Gbl_IsConfirmedPending;

extern Dcm_NegativeResponseCodeType Dcm_Gdt_NegRespError;

extern Dcm_DiagTimerType Dcm_Gst_CurrentTimingValue;

extern Dcm_DiagTimerType Dcm_Gdt_AcsTimingValue;

extern Dcm_MsgContextType Dcm_Gdt_MsgContext;

extern Dcm_MsgContextType *Dcm_Gpt_MsgContext;

extern uint8 Dcm_Gu8_SecurityAccessType;

extern uint16 Dcm_Gu16_CurrentRoutineId;

extern uint32 Dcm_Gu32_DLMemAddress;

extern uint32 Dcm_Gu32_DLMemSize;

extern uint16 Dcm_Gu16_BlockLength;

extern uint8  Dcm_Gu8_DataFormatId;

extern uint32  Dcm_Gu32_NumOfBytesToBeTransfered;

extern uint32  Dcm_Gu32_PreviousBlkRxdLen;

extern uint8  *Dcm_Gu8_WriteMemData;

extern uint8   Dcm_Gu8_BlockSeqCounter;

extern uint8   Dcm_Gu8_BlockSeqCounterRecvd;

#if (FBL_DIAG_TRANSFERDATA_CHUNK_MODE == STD_ON)
extern uint8   Dcm_Gdt_TDReqSequence;
#endif /* FBL_DIAG_TRANSFERDATA_CHUNK_MODE */

extern boolean Dcm_Gbl_BlockSeqCounterRollOver;

extern boolean Dcm_Gbl_DownloadActive;

extern boolean Dcm_Gbl_TDSendNegResp;

extern Dcm_MetaDataState_Etyp Dcm_Gdt_MetaDataState;

extern uint8 Dcm_Gu8_MetaDataPos;

/* Queued implementation related */
extern Dcm_QueuedReqState_Etyp Dcm_Gen_ProcessQueuedReq;

extern uint8 Dcm_Gu8_ReqProcIndex;

extern uint8 Dcm_Gu8_ReqFillIndex;

extern boolean Dcm_Gbl_ChangeToIdle;

extern uint16 Dcm_Gu16_BusyBufferStartPos;

extern uint16 Dcm_Gu16_BusyBufferEndPos;

extern uint8 Dcm_Gu8_InQueueIdx;

extern uint8 Dcm_Gu8_OutQueueIdx;

extern Dcm_QueueMsg_Styp  Dcm_Gast_ReqQueue[DCM_MAX_RX_QUEUE_ALLOWED];

#define BTL_STOP_SEC_VAR_NO_INIT
#include "Btl_MemMap.h"

#define BTL_START_SEC_VAR_INIT
#include "Btl_MemMap.h"

extern Dcm_PduIdTable_Styp Dcm_Gast_PduIdConfigTab[DCM_PDUID_COUNT];

#define BTL_STOP_SEC_VAR_INIT
#include "Btl_MemMap.h"


#define BTL_START_SEC_CONST
#include "Btl_MemMap.h"

#if (DCM_SECURITYACCESS_SERVICE == STD_ON)

extern const Dcm_LookUpTable_Styp Dcm_Kast_SecMaskList[DCM_MAX_SEC_LEVEL_COUNT];

extern const Dcm_SubServiceConfig_Styp
  Dcm_Gast_SecAccessSubFunc[DCM_MAX_SEC_SUBFUNC_COUNT];
  
extern const Dcm_SecurityLevConfig_Styp
  Dcm_Kast_SecurityLevConfig[DCM_SUPPORTED_SEC_LEVEL_COUNT];
#endif

#if (DCM_DIAGSESSIONCONTROL_SERVICE == STD_ON)
extern const Dcm_LookUpTable_Styp Dcm_Kast_SesMaskList[DCM_MAX_SESSION_COUNT];

extern const Dcm_SubServiceConfig_Styp
  Dcm_Kast_SesCtrlSubFunc[DCM_MAX_SESSION_COUNT];
#endif

extern const uint8 Dcm_Kau8_RxPduIdMaskList[DCM_PDUID_COUNT];

#if (DCM_ECURESET_SERVICE == STD_ON)
extern const Dcm_SubServiceConfig_Styp
  Dcm_Kast_ECUResetSubFunc[DCM_MAX_RESET_TYPE_COUNT];
#endif

#if (DCM_TESTERPRESENT_SERVICE == STD_ON)
extern const Dcm_SubServiceConfig_Styp Dcm_Kast_TesterPresentSubFunc[DCM_ONE];
#endif

#if (DCM_READDATABYID_SERVICE == STD_ON)
extern const Dcm_DspDIDConfig_Styp Dcm_Kast_DIDConfig[DCM_MAX_DID_COUNT];
#endif


#if (DCM_WRITEDATABYID_SERVICE == STD_ON)
extern const Dcm_SubServiceConfig_Styp
  Dcm_Kast_WriteDIDSubFunc[DCM_WRITE_DID_COUNT];
#endif

#if (DCM_ROUTINECONTROL_SERVICE == STD_ON)
extern const Dcm_SubServiceConfig_Styp
  Dcm_Kast_RoutineCtrlSubFunc[DCM_ONE];
#endif

extern const Dcm_DspRIDConfig_Styp Dcm_Kast_RIDConfig[DCM_MAX_RID_COUNT];

#if (DCM_LINKCONTROL_SERVICE == STD_ON)
extern const Dcm_SubServiceConfig_Styp Dcm_Kast_LinkCtrlSubFunc[DCM_THREE];
#endif

#if (DCM_COMMUNICATIONCONTROL_SERVICE == STD_ON)
extern const Dcm_SubServiceConfig_Styp Dcm_Kast_CommCtrlSubFunc[DCM_FOUR];
#endif

#if (DCM_CONTROLDTCSETTING_SERVICE == STD_ON)
extern const Dcm_SubServiceConfig_Styp Dcm_Kast_CtrlDTCSettingsSubFunc[DCM_TWO];
#endif

#if (DCM_ACCESSTIMINGPARAMETERS_SERVICE == STD_ON)
extern const Dcm_SubServiceConfig_Styp
  Dcm_Kast_AccessTimingParamSubFunc[DCM_ONE];
#endif

extern const Dcm_SIDConfig_Styp Dcm_Kast_SIdConfig[DCM_MAX_SERVICE_COUNT];

extern const Dcm_SessionConfig_Styp
  Dcm_Kast_SessionConfigTable[DCM_MAX_SESSION_COUNT];

#define BTL_STOP_SEC_CONST
#include "Btl_MemMap.h"

#endif /* DCM_GLOBALS_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
