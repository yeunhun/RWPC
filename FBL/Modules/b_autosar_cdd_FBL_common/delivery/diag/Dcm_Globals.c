/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dcm_Globals.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file provides global variable declarations for Dcm       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.22.0    09-Nov-2021   JYS          Redmine #29462, #33131                **
** 1.21.0    27-Sep-2021   JYS          Redmine #29449                        **
** 1.13.0.0  05-Apr-2020   JYS          Redmine #29188                        **
** 1.0.2     05-Nov-2020   JYS          Redmine #26443                        **
** 1.0.1     06-Dec-2019   Sinil        Redmine #20402                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm_Globals.h"


/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#define BTL_START_SEC_VAR_NO_INIT
#include "Btl_MemMap.h"

/* Maintains current Session */
Dcm_SesCtrlType Dcm_Gdt_CurrentSession;

/* Maintains current Security Level */
Dcm_SecLevelType Dcm_Gdt_SecurityLevel;

/* Buffers maintained by Dcm */
/* Redmine #33131 To align TransferData patch size + U2 */
uint8 Dcm_Gau8_RxBufferRaw[DCM_MAX_RX_BUFFER_SIZE+2U];

uint8* Dcm_Gau8_RxBuffer = &Dcm_Gau8_RxBufferRaw[2U];

uint8 Dcm_Gau8_TxBuffer[DCM_MAX_TX_BUFFER_SIZE];

uint8 Dcm_Gau8_TPReqBuffer[DCM_TPRX_BUFFER_SIZE];

uint8 Dcm_Gau8_ResponseBuf[DCM_RESP_BUFFER_SIZE];

uint8 Dcm_Gau8_MetaDataBuffer[DCM_REVISED_SECUREFLASHING_METADATA_LENGTH];

/* Holds count of Response Pending responses send */
uint8 Dcm_Gu8_MaxNoOfRespPend;

/* Holds current requested Service Id */
uint8 Dcm_Gu8_SID;

uint8 Dcm_Gu8_SessionTableIndex;

#if (DCM_LINKCONTROL_SERVICE == STD_ON)
/* Maintains Link Control Verification */
boolean Dcm_Gbl_LinkCtrlVrfySuccess;
#endif

/* Global variables used to maintain states during processing of
 * Security Access service
 */
uint8 Dcm_Gu8_ExpSecKeyNo;

uint8 Dcm_Gu8_SecAccessAttempt;

uint8 Dcm_Gu8_SecAccessMaxAttDelay;

/* Global variables used to maintain states during processing new request */
uint8            Dcm_Gu8_ActiveRxPduId;

uint8            Dcm_Gu8_ActiveTxPduId;

uint16           Dcm_Gu16_RequestLength;

uint16           Dcm_Gu16_TxLength;

boolean          Dcm_Gbl_WaitForEcuReset;

boolean          Dcm_Gbl_NegRespState;

PduIdType        Dcm_Gdt_DcmTxConfPduId;

Dcm_OpStatusType Dcm_Gdt_OpStatus;

/* Holds Pending state during processing new request */
boolean Dcm_Gbl_ReqProcPending;

/* Holds Pending transmit state until confirmation of NRC transmit is called */
boolean Dcm_Gbl_IsConfirmedPending;

/* Holds value of different session timers */
Dcm_DiagTimerType Dcm_Gst_CurrentTimingValue;

/* Holds Timer value for the Access timing Parameter Service */
Dcm_DiagTimerType Dcm_Gdt_AcsTimingValue;

/* Holds message context */
Dcm_MsgContextType Dcm_Gdt_MsgContext;

Dcm_MsgContextType *Dcm_Gpt_MsgContext;

/* Global Variable to store the status of the timer */
Dcm_TimerAct_Etyp Dcm_Gen_ActiveTimer;

uint16 Dcm_Gu16_Timer;

uint32 Dcm_Gu32_SecDelayTimer;

uint8 Dcm_Gu8_SecurityAccessType;

uint16 Dcm_Gu16_CurrentRoutineId;

/* Global variables used to maintain values during processing download
 * request
 */
uint32 Dcm_Gu32_DLMemAddress;

uint32 Dcm_Gu32_DLMemSize;

uint16 Dcm_Gu16_BlockLength;

uint8  Dcm_Gu8_DataFormatId;

/* Global variables used to maintain values during processing Transfer Data */
uint32 Dcm_Gu32_PreviousBlkRxdLen;

uint32 Dcm_Gu32_NumOfBytesToBeTransfered;

uint8* Dcm_Gu8_WriteMemData;

uint8  Dcm_Gu8_BlockSeqCounter;

uint8  Dcm_Gu8_BlockSeqCounterRecvd;

#if (FBL_DIAG_TRANSFERDATA_CHUNK_MODE == STD_ON)
uint8  Dcm_Gdt_TDReqSequence;
#endif /* FBL_DIAG_TRANSFERDATA_CHUNK_MODE */

boolean Dcm_Gbl_BlockSeqCounterRollOver;

boolean Dcm_Gbl_DownloadActive;

boolean Dcm_Gbl_TDSendNegResp;

Dcm_MetaDataState_Etyp Dcm_Gdt_MetaDataState;

uint8 Dcm_Gu8_MetaDataPos;

/* Holds Negative response code */
Dcm_NegativeResponseCodeType Dcm_Gdt_NegRespError;

/* Queued implementation related */
Dcm_QueuedReqState_Etyp Dcm_Gen_ProcessQueuedReq;

Dcm_QueueMsg_Styp Dcm_Gast_ReqQueue[DCM_MAX_RX_QUEUE_ALLOWED];

uint16  Dcm_Gu16_BusyBufferStartPos;

uint16  Dcm_Gu16_BusyBufferEndPos;

uint8   Dcm_Gu8_ReqProcIndex;

uint8   Dcm_Gu8_ReqFillIndex;

uint8   Dcm_Gu8_InQueueIdx;

uint8   Dcm_Gu8_OutQueueIdx;

boolean Dcm_Gbl_ChangeToIdle;

#define BTL_STOP_SEC_VAR_NO_INIT
#include "Btl_MemMap.h"

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
