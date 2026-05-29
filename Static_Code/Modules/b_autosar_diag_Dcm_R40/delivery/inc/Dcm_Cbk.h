/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE: Dcm_Cbk.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_Cbk                                          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By              Description                        **
********************************************************************************
** 2.3.2.0   05-Nov-2020   EunKyung Kim    #26432                             **
**                                                                            **
** 1.0.1     16-07-2019    Y.S     Jeon    #2212                              **
**                                                                            **
** 1.0.0     09-01-2013    Autron          Initial Version                    **
*******************************************************************************/

/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */
#ifndef DCM_CBK_H
#define DCM_CBK_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* polyspace +2 MISRA-C3:2.5 [Justified:Low] "Not a defect" */
#define DCM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                        Interface for PDU Router                            **
*******************************************************************************/
extern FUNC(void, DCM_APPL_CODE) Dcm_TpRxIndication(
  PduIdType DcmRxPduId, NotifResultType Result);

extern FUNC(BufReq_ReturnType, DCM_APPL_CODE) Dcm_CopyTxData(
  PduIdType DcmTxPduId,
  P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_CONST) PduInfoPtr,
  P2VAR(RetryInfoType, AUTOMATIC, DCM_APPL_DATA) RetryInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) TxDataCntPtr);

extern FUNC(void, DCM_APPL_CODE) Dcm_TpTxConfirmation(
  PduIdType DcmTxPduId, NotifResultType Result);

extern FUNC(BufReq_ReturnType, DCM_APPL_CODE) Dcm_StartOfReception(
  PduIdType DcmRxPduId, 
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) LpPduInfoPtr, 
  PduLengthType TpSduLength,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr);

extern FUNC(BufReq_ReturnType, DCM_APPL_CODE) Dcm_CopyRxData(
  PduIdType DcmRxPduId,
  P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_CONST) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr);

/*******************************************************************************
**                       Interface for Communication Manager                  **
*******************************************************************************/

extern FUNC(void, DCM_APPL_CODE) Dcm_ComM_NoComModeEntered(uint8 NetworkId);

extern FUNC(void, DCM_APPL_CODE) Dcm_ComM_SilentComModeEntered(uint8 NetworkId);

extern FUNC(void, DCM_APPL_CODE) Dcm_ComM_FullComModeEntered(uint8 NetworkId);

/* polyspace +3 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
/* polyspace +2 MISRA-C3:2.5 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* DCM_CBK_H */
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
