/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dcm_Internal.h                                                **
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
** 1.21.0    27-Sep-2021   JYS          Redmine #29449                        **
** 1.15.1.0  17-May-2021   SK Park      Redmine #29359                        **
** 1.0.2     06-Nov-2020   JYS          Redmine #26489                        **
** 1.0.1     06-Dec-2019   Sinil        Redmine #20402                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef DCM_INTERNAL_H
#define DCM_INTERNAL_H

/*******************************************************************************
**                           Included header files                            **
*******************************************************************************/
#include "Dcm_PCTypes.h"
#include "Dcm_Globals.h"

/*******************************************************************************
**                           Function Prototypes                              **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

extern void Dcm_ExternalSetNegResponse
  (const Dcm_MsgContextType *Lpst_MsgContext,
  Dcm_NegativeResponseCodeType Ldt_ErrorCode);
  
extern void Dcm_ExternalProcessingDone (Dcm_MsgContextType *Lpst_MsgContext);

extern void Dcm_DsdIndication(PduIdType  Ldt_RxPduId);

extern void  Dcm_DsdConfirmation(NotifResultType Ldt_Result);

extern void Dcm_DslTransmit(void);

extern void Dcm_DslNRCTransmit(void);

extern void Dcm_DslS3TimerReset(void);

extern Std_ReturnType Dcm_DsdSesSuprtCheck(const uint8 Lu8_SuprtMask);

extern Std_ReturnType Dcm_DsdSecLevlCheck(const uint8 Lu8_SuprtMask);

#if (DCM_DIAGSESSIONCONTROL_SERVICE == STD_ON)
extern void Dcm_DcmDiagnosticSessionControl
  (Dcm_MsgContextType *Lpst_MsgContext);
#endif

#if (DCM_ECURESET_SERVICE == STD_ON)
extern void Dcm_DcmECUResetService(Dcm_MsgContextType *Lpst_MsgContext);
#endif

#if (DCM_TESTERPRESENT_SERVICE == STD_ON)
extern void Dcm_DcmTesterPresent(Dcm_MsgContextType *Lpst_MsgContext);
#endif

#if (DCM_SECURITYACCESS_SERVICE == STD_ON)
extern void Dcm_DcmSecurityAccess(Dcm_MsgContextType *Lpst_MsgContext);
#endif

#if (DCM_READDATABYID_SERVICE == STD_ON)
extern void Dcm_DcmReadDataByIdentifier(Dcm_MsgContextType *Lpst_MsgContext);

extern void Dcm_DspReadDIDValue
  (Dcm_MsgContextType *Lpst_MsgContext, uint8 Lu8_DIDIndex);
#endif

#if (DCM_WRITEDATABYID_SERVICE == STD_ON)
extern void Dcm_DcmWriteDataByIdentifier(Dcm_MsgContextType *Lpst_MsgContext);

extern void Dcm_DspWriteDIDValue
  (Dcm_MsgContextType *Lpst_MsgContext, uint8 Lu8_DIDIndex);
#endif

#if (DCM_ROUTINECONTROL_SERVICE == STD_ON)
extern void Dcm_DcmRoutineControl(Dcm_MsgContextType *Lpst_MsgContext);
#endif

#if (DCM_REQUESTDOWNLOAD_SERVICE == STD_ON)
extern void Dcm_DcmRequestDownload(Dcm_MsgContextType *Lpst_MsgContext);
#endif

#if (DCM_TRANSFERDATA_SERVICE == STD_ON)
extern void Dcm_DcmTransferData(Dcm_MsgContextType *Lpst_MsgContext);
#endif

#if (DCM_TRANSFERDATA_SERVICE == STD_ON)
#if (FBL_DIAG_TRANSFERDATA_CHUNK_MODE == STD_ON)
extern void Dcm_DspProcessTransferData_CF
  (uint16 Lu16_MemorySize, const uint8* Lpu8_WriteData);
#endif /* FBL_DIAG_TRANSFERDATA_CHUNK_MODE */
#endif

#if (DCM_REQTRANSFEREXIT_SERVICE == STD_ON)
extern void Dcm_DcmRequestTransferExit(Dcm_MsgContextType *Lpst_MsgContext);
#endif

#if (DCM_LINKCONTROL_SERVICE == STD_ON)
extern void Dcm_DcmLinkControl(Dcm_MsgContextType *Lpst_MsgContext);
#endif

#if (DCM_COMMUNICATIONCONTROL_SERVICE == STD_ON)
extern void Dcm_DcmCommControl(Dcm_MsgContextType *Lpst_MsgContext);
#endif

#if (DCM_CONTROLDTCSETTING_SERVICE == STD_ON)
extern void Dcm_DcmCtrlDTCSettings(Dcm_MsgContextType *Lpst_MsgContext);
#endif

#if (DCM_ACCESSTIMINGPARAMETERS_SERVICE == STD_ON)
extern void Dcm_DcmAccessTimingParameters(Dcm_MsgContextType *Lpst_MsgContext);
#endif

extern void Dcm_DspConfirmation
  (Dcm_IdContextType Ldt_IdContext,
  PduIdType Ldt_RxPduId,
  Dcm_ConfirmationStatusType Ldt_Status);
  
extern uint8 Dcm_GetFillQueueIdx(uint16 Lu16_MsgLength);

extern uint8 Dcm_GetProcQueueIdx(void);

extern void Dcm_ClearProcQueue(uint8 Lu8_QueueIdx);

extern void Dcm_ClearAllProcQueue(void);

extern uint8 Dcm_SearchSessionCfgTableIdx(const uint8 Lu8_SubFuncID);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* DCM_INTERNAL_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
