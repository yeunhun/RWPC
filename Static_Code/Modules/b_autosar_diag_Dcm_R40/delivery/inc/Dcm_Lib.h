/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE: Dcm_Lib.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_Lib                                          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By                Description                      **
********************************************************************************
** 2.3.2.0   05-Nov-2020   EunKyung Kim    #26432                             **
**                                                                            **
** 1.0.1     12-09-2018    Y.S     Jeon      #13032                           **
**                                                                            **
** 1.0.0     25-05-2016    Sungeol Baek      Initial Version                  **
*******************************************************************************/

#ifndef DCM_LIB_H
#define DCM_LIB_H

#define DCM_START_SEC_CODE
#include "MemMap.h"

#if(DCM_DSP_DIAG_SESSION_SERVICE == STD_ON)
extern Std_ReturnType Dcm_ChkSessionLevel(Dcm_SesCtrlType ucSessionLevel);
#endif

extern Std_ReturnType Dcm_ChkSuppressPosResponse(P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) LpRxData, Dcm_MsgLenType MsgDataLen);

#if(DCM_DSP_SECURITY_SERVICE == STD_ON)
extern void Dcm_ChkSecAccessCntInc(uint8* FailedSecurityAccessCount, uint8 SecNumMaxAttDelay);

#if((DCM_STANDARD_SUPPORT == DCM_ES96590_SUPPORT) || (DCM_STANDARD_SUPPORT == DCM_QZN04_SUPPORT))
extern void Dcm_ChkSecAccessCntDec(uint8* LpFailedSecurityAccessCount);
#endif

extern Std_ReturnType Dcm_SetSecAccessCntInc(uint8* LpFailedSecurityAccessCount, 
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2CONST(Dcm_SecurityLevConfigType, AUTOMATIC, DCM_APPL_CONST) LpSecData);


extern void Dcm_SetSecAccessCntDec(uint8* LpFailedSecurityAccessCount, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pNegRespError,
  P2CONST(Dcm_SecurityLevConfigType, AUTOMATIC, DCM_APPL_CONST) LpSecData);
#endif

extern FUNC(void, DCM_CODE) Dcm_DspInternal_DcmEnableNormalMsgTransmission(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

extern FUNC(void, DCM_CODE) Dcm_DspInternal_DcmStopDiagnosticSession(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* DCM_LIB_H */

