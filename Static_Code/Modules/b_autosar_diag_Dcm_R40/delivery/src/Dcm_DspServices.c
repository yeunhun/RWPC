/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE: Dcm_DspServices.c                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the definitions for UDS services           **
**              implemented by DSP layer of Dcm module                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision   Date          By                  Description                   **
********************************************************************************
** 2.3.4.0   28-Jan-2021   EunKyung Kim    #27997                             **
**                                                                            **
** 2.3.2.0   05-Nov-2020   EunKyung Kim    #26432                             **
**                                                                            **
** 1.0.27     02-28-2020    EunKyung Kim       #21551                         **
**                                                                            **
** 1.0.26     11-25-2019    EunKyung Kim       #19580                         **
**                                                                            **
** 1.0.25     18-06-2019    Y.S     Jeon       #17902                         **
**                                                                            **
** 1.0.24     09-04-2019    Y.S     Jeon       #16582                         **
**                                                                            **
** 1.0.23     09-11-2018    Y.S     Jeon       #13923                         **
**                                                                            **
** 1.0.22     12-09-2018    Y.S     Jeon       #13032  #14010                 **
**                                                                            **
** 1.0.19     18-05-2018    Y.S     Jeon       #12651                         **
**                                                                            **
** 1.0.18     10-11-2017    YoungJin Yun       #10534                         **
**                                                                            **
** 1.0.17     27-06-2017    Jin     Jung        #8647                         **
**                                                                            **
** 1.0.16     12-06-2017    Jin     Jung        #7008, #7107                  **
**                                                                            **
** 1.0.15     28-03-2017    Jin     Jung        #7631, #7807                  **
**                                                                            **
** 1.0.14     15-02-2017    Jin     Jung        #5460                         **
**                                                                            **
** 1.0.13     18-10-2016    Jin     Jung        #2467                         **
**                                                                            **
** 1.0.12     25-05-2016    Sungeol Baek        #5006                         **
**                                                                            **
** 1.0.11     03-03-2016    Sungeol Baek        #3754, RTRT reflection        **
**                                                                            **
** 1.0.10     14-11-2015    Youngjin Yun        #3486                         **
**                                                                            **
** 1.0.9      18-09-2015    YoungJin Yun        #3166                         **
**                                                                            **
** 1.0.8      10-08-2015    Youngjin Yun        #2977                         **
**                                                                            **
** 1.0.7      16-07-2015    Sungeol Baek        #2678                         **
**                                                                            **
** 1.0.6      19-06-2015    YoungJin Yun        #2718, #2693, #2692,#2691     **
**                                                                            **
** 1.0.5      29-05-2015    YoungJin Yun        #2637                         **
**                                                                            **
** 1.0.4      16-04-2015    Sungeol Baek        #2171                         **
**                                                                            **
** 1.0.3      24-03-2015    Sungeol Baek        #2370                         **
**                                                                            **
** 1.0.2      05-03-2015    YoungJin Yun        #1697, #1698                  **
**                                                                            **
** 1.0.1      26-02-2015    YoungJin Yun        #1044                         **
**                                                                            **
** 1.0.0      09-01-2013    Autron              Initial Version               **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_Ram.h"
#include "Dcm_Types.h"
#include "Dcm_DspMain.h"
#include "Dcm_DspServices.h"
#include "Rte_Dcm.h"
#include "SchM_Dcm.h"
#if (DCM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
#include "Dcm_CallOuts.h"
#include "Dem.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_DslInternal.h"
#include "BswM_Dcm.h"
#include "NvM.h"
#include "SchM_Dcm.h"
#include "Dcm_DspNonPagedDTCSubFct.h"
#include "Dcm_DspReadDTCInfo.h"
#include "Dcm_DspReadSSDTCInfo.h"
#include "Dcm_PackUnPack.h"
#include "Dcm_DspOBDServices.h"
#include "Dcm_DspOBDInternals.h"
#include "Dcm_Config.h"
#include "Dcm_Lib.h"

#include "Dcm_DspSecureServices.h"

/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:19.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:17.8 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:11.5 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:10.4 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.5 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.2 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:9.1 [Justified:Low] "Not a defect" */
/* polyspace-begin DEFECT:USELESS_WRITE [Justified:Low] "Not a defect" */
/* polyspace-begin DEFECT:UINT_CONV_OVFL [Justified:Low] "Not a defect" */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-begin CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-begin CERT-C:EXP36-C [Justified:Low] "Module do not know user data type so before using user data, pointer need to be cast" */
/*******************************************************************************
**                      STATIC MACRO                                          **
*******************************************************************************/  

#define DCM_SIG_STATE_UNDEFINE               0x00u  
#define DCM_SIG_STATE_CONDITION_CHECK_READ   0x01u
#define DCM_SIG_STATE_READ_SIGNAL            0x02u
#define DCM_SIG_STATE_READ_LEN               0x03u


#define DCM_DID_STATE_UNDEFINE               0x00u
#define DCM_DID_STATE_CONDITION_CHECK_READ   0x01u
#define DCM_DID_STATE_READ_DID               0x02u

#define DCM_READDID_STATE_READ_DID           0x01u
#define DCM_READDID_STATE_READ_DIDREF        0x02u

#define DCM_PDID_STATE_UNDEFINE              0x00u
#define DCM_PDID_STATE_VERIFICATION_PDID     0x01u
#define DCM_PDID_STATE_CONDITION_CHECK_READ  0x02u

#define DCM_NUM_FUNCPTRLIST_READDIDTYPE      ((uint8)0x05)

#if(DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON)
  #if(DCM_STANDARD_SUPPORT == DCM_ES95486_SUPPORT)
  #define DCM_LOCAL_NUM_OF_SUBREQ  (4U)
  #define DCM_LOCAL_NUM_OF_COMTYPE (3U+1U)
  /*****************************************************************************
  **                            ES96590 Specification                         **
  *****************************************************************************/
  #elif (DCM_STANDARD_SUPPORT == DCM_ES96590_SUPPORT)
  #define DCM_LOCAL_NUM_OF_SUBREQ  (4U)
  #define DCM_LOCAL_NUM_OF_COMTYPE (3U+1U)
  /*****************************************************************************
  **                            AUTOSAR Specification                         **
  *****************************************************************************/  
  #else
  #define DCM_LOCAL_NUM_OF_SUBREQ  (4U)
  #define DCM_LOCAL_NUM_OF_COMTYPE (3U+1U)
  #endif
#endif

/* polyspace-begin MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace:begin<MISRA-C:8.7:Not a defect:Justify with annotations> No Impact of this rule violation. */
/*******************************************************************************
**                      STATIC FUNCTION DECLARATIONS                          **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

#if (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
static 
FUNC(Std_ReturnType, DCM_CODE)
Dcm_DspInternal_WriteSigTypeNvMBlock(
  Dcm_OpStatusType anOpStatus,
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) anInputBuffer,
  Dcm_NegativeResponseCodeType *anOutNegRespCode);
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
static 
FUNC(Std_ReturnType, DCM_CODE)
Dcm_DspInternal_ReadSigTypeNvMBlock(
  Dcm_OpStatusType anOpStatus,
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) anOutBuffer);
#endif

#if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE)  
Dcm_DspInternal_IOControlResetToDefault(
  Dcm_OpStatusType anOpStatus,  
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,  
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA)  aNegResponceCode);  

static FUNC(Std_ReturnType, DCM_CODE)  
Dcm_DspInternal_IOControlFreezeCurrentState(
  Dcm_OpStatusType anOpStatus,  
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,  
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA)  aNegResponceCode);
  
static FUNC(Std_ReturnType, DCM_CODE)  
Dcm_DspInternal_IOControlReturnControlToECU(
    Dcm_OpStatusType anOpStatus,  
    P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,  
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA)  aNegResponceCode);

static FUNC(Std_ReturnType, DCM_CODE)  
Dcm_DspInternal_IOControlShortTermAdjustment(
  Dcm_OpStatusType anOpStatus,  
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,  
  Dcm_MsgLenType aDataLength,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) aControlOptionRecord,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA)  aNegResponceCode);   
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON))
/*    (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)) */
static 
FUNC(Std_ReturnType, DCM_CODE)
Dcm_DspInternal_GetDidInfo(
  uint16 aDidindex,
  CONST(boolean, DCM_CONST) aCfgDidRangePresent,
  P2CONST(Dcm_DIDInfoType, AUTOMATIC, DCM_APPL_CONST) *aCfgDidInfo);
#endif


#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) 
static FUNC(Std_ReturnType, DCM_CODE) 
Dcm_DspInternal_ReadDidTypeNonOBDDID(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) aMsgContext,
  uint16 aDidIndex, 
  uint16 aDidCount,
  Dcm_NegativeResponseCodeType *anOutNegRespCode);

  #if(DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON)
  static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidTypeDDDID(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) aMsgContext,
    uint16 aDIdIndex, 
    uint16 aDidCount,
    Dcm_NegativeResponseCodeType *anOutNegRespCode);
  #endif

#endif


#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))  
static 
FUNC(Dcm_DidType, DCM_CODE) 
Dcm_DspGetDIDType(
    uint16 LusDataIdentifier);  
#endif

#if(DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
static
FUNC(Std_ReturnType, DCM_CODE) 
Dcm_DspInternal_ReadDidType(
  uint16 DataIdentifier,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  Dcm_NegativeResponseCodeType *pNegRespCode);
#endif

#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
static 
FUNC(Std_ReturnType, DCM_CODE)
Dcm_DspInternal_ReadDidTypeDidRange(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
    uint16 LusDIDIndex, 
    uint16 LusDidCount,
    Dcm_NegativeResponseCodeType *pNegRespCode);
#endif

#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
static 
FUNC(Std_ReturnType, DCM_CODE)
Dcm_DspInternal_GetSizeOfDidSignal(
  Dcm_OpStatusType anOpStatus, 
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) aSignalSize);
#endif  

#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
static 
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidTypeF186(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint16 IndexOfDid, 
  uint16 LusDidCount,
  Dcm_NegativeResponseCodeType *pNegRespCode);
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) && \
     ((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
        (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
        (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON)))
static 
FUNC(Std_ReturnType, DCM_CODE) 
Dcm_DspInternal_ReadDidTypeOBDDID(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint16 LusDIDIndex, 
  uint16 LusDidCount,
  Dcm_NegativeResponseCodeType *LddErrorCode);
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) )
static 
FUNC(Std_ReturnType, DCM_CODE)
Dcm_DspInternal_ConditionCheckRead(
  Dcm_OpStatusType anOpStatus,
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) anOutNegRespCode);
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
static 
FUNC(Std_ReturnType, DCM_CODE)
Dcm_DspInternal_ReadSigType(
  Dcm_OpStatusType anOpStatus,
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) anOutputBuffer);
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) && \
    (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON))
  static 
  FUNC(Std_ReturnType, DCM_CODE)
  Dcm_DspInternal_ReadSigTypeMemory(
    Dcm_OpStatusType anOpStatus,
    uint8 MemoryIdentifier,
    uint32 MemoryAddress,
    uint32 MemorySize,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) aOutResData,
    Dcm_NegativeResponseCodeType *anOutNegRespCode);

#endif


#if(DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON)

static FUNC(void, DCM_CODE) Dcm_DspDynDefinedByDID(uint16 LusDynDIDIndex,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint8 LucMaxNumOfSourceEle, uint16 LusIDCount);

static FUNC(void, DCM_CODE) Dcm_DspDynDefinedByMemAddress
  (uint16 LusDynDIDIndex,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint8 LucMaxNumOfSourceEle, uint16 LusIDCount);

static FUNC(void, DCM_CODE) Dcm_DspClrDynDefinedDID(
  uint16 LusDynDIDIndex,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint8 Luc_TotalSourceElem);

static FUNC(boolean, DCM_CODE) Dcm_DspValidateDynDID(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpIDCount,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpDIDIndex);

#endif

#if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)

static FUNC(Std_ReturnType, DCM_CODE) 
 Dcm_DspReadData(
  Dcm_OpStatusType anOpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2CONST(Dcm_DIDParaConfig, AUTOMATIC, DCM_APPL_CONST) aCfgDid);
  

static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspConditionCheckRead(
  Dcm_OpStatusType anOpStatus, 
  P2CONST(Dcm_DIDParaConfig, AUTOMATIC, DCM_APPL_CONST) aCfgDid);


static FUNC(void, DCM_CODE) Dcm_DspCalShiftBitAndStartMask
  (uint16 LusSignalOffset,
  uint16 LusSignalSize, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)LucShiftBits,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)LucStartMask);

static FUNC(uint8, DCM_CODE) Dcm_DspCalculateEndMask(uint16 LusSignalOffset,
  uint16 LusSignalSize, boolean LblSignFlag);

static FUNC(void, DCM_CODE)
  Dcm_DspCalculateSignalPackParameters(
  P2VAR(Dcm_PackUnpackSignalData, AUTOMATIC, DCM_APPL_DATA)LpPackSignal,
  uint16 LusSignalBitPosition, uint16 LusDIDsize, uint8 LucSignalStartByte,
  boolean LblSignFlag);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE)
  Dcm_DspValidateInputOutputDid(uint16 LusDataIdentifier,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpDIDIndex );

static FUNC(uint16, DCM_CODE) Dcm_DspCalculateBitPosition
  (uint16 LusSignalOffset, uint16 LusSignalSize);

#endif

#if(DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE)
  Dcm_DspValidateWriteDID(uint16 LusDIDIndex, boolean LblDIDRangePresent);

#endif

#if((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
  (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
  (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON))
static FUNC(boolean, DCM_CODE)
Dcm_DspDIDSearch(
  uint16 aDataIdentifier,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) aDidIndex,
  P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA) aDidRangePresent);  
#endif

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspValidateDID
(uint16 LusDIDIndex, boolean LblDIDRangePresent);

#if(DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON)
static FUNC(void, DCM_CODE) 
Dcm_DspInternal_GetSizeOfDid(
  P2CONST(Dcm_DIDParaConfig, AUTOMATIC, DCM_APPL_CONST) aCfgDid,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) aMinDataLength,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) aMaxDataLength);

#if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(void, DCM_CODE)  Dcm_DspInternal_UnpackSignal(
  P2CONST(Dcm_DIDUnPackSignal, AUTOMATIC, DCM_APPL_DATA)  aCfgUnpackSignal,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) aInputBuffer,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) anOutputBuffer);
#endif

#endif


#if(DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadScalingData(
  Dcm_OpStatusType aOpStatus,
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,  
  Dcm_MsgType aOutBuffer,   
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) anOutNegRespCode);
#endif

/* polyspace +2 MISRA-C3:20.7 [Justified:Low] "Not a defect" */
#if(DCM_DSP_SECURITY_SERVICE == STD_ON)
static FUNC( P2CONST(Dcm_SecurityLevConfigType, AUTOMATIC, DCM_APPL_CONST), DCM_CODE)
Dcm_DspInternal_GetSecurityLevelCfg(
  Dcm_SecLevelType RequestedSecurityLevel,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) SecurityLevelIndex);
#endif
/* polyspace-end MISRA-C3:20.7 [Justify with annotations:Low] "Not a defect" */
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      STATIC DATA TYPES                                     **
*******************************************************************************/

/*
typedef enum {
  DCM_DYN_ID = 0,                                                    
  DCM_OBD_ID,                                                    
  DCM_NONOBD_ID,
  DCM_DIDTYPE_DIDRANGE,
  DCM_DIDTYPE_SESSION,
  DCM_DIDTYPE_NO_TYPE
} Dcm_DidType;

*/
#if(DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)

static Std_ReturnType (*Dcm_FuncPtrList_ReadDidType[DCM_NUM_FUNCPTRLIST_READDIDTYPE])(
   P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA),
   uint16,
   uint16 ,
   P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA))= {

  /* DCM_DYN_ID */
  #if(DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON)
  Dcm_DspInternal_ReadDidTypeDDDID,
  #else
  NULL_PTR,
  #endif

  /* DCM_OBD_ID */
  #if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) && \
      ((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
       (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
       (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON)))
  Dcm_DspInternal_ReadDidTypeOBDDID,                            
  #else
  NULL_PTR,
  #endif
  
  #if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
       (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON))
  /* DCM_NONOBD_ID */
  Dcm_DspInternal_ReadDidTypeNonOBDDID,

  /* DCM_DIDTYPE_DIDRANGE */
  #if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
  Dcm_DspInternal_ReadDidTypeDidRange,
  #else
  NULL_PTR,
  #endif
  Dcm_DspInternal_ReadDidTypeF186  
  
  #else

  NULL_PTR,
  NULL_PTR,
  NULL_PTR
  #endif  
};
#endif
  
/* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > pointer is not null */
/* polyspace:begin<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:begin<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
/* polyspace:begin<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Nesting of control structures to achieve better throughput. */
/* polyspace:begin<MISRA-C:13.7:Not a defect:Justify with annotations> It has not any impact. */

/*******************************************************************************
**                STATIC FUNCTION DEFINITIONS                                 **
*******************************************************************************/



/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadDidTypeF186                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x22   **
**                        to Read the requested Dynamic DID value from the    **
**                        Application.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusDIDIndex ,LucDidCount                            **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GaaDymDefinedDIDInfoType, **
**                        Dcm_GaaDymMemDIDInfoType,                           **
**                        Dcm_GblResOnPeriodicIdStatus, Dcm_GusDidReadIndex,  **
**                        Dcm_GddOpStatus, Dcm_GucRMBAMemoryIdentifier,       **
**                        Dcm_GddNegRespError, Dcm_ServicePendingStatus,      **
**                        Dcm_GaaDidReadSignalData.                           **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_START_SEC_CODE
#include "MemMap.h"
#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidTypeF186(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint16 IndexOfDid, 
  uint16 LusDidCount,
  Dcm_NegativeResponseCodeType *pNegRespCode)
{
  Std_ReturnType retVal = E_NOT_OK;
  
  if ((pMsgContext->resDataLen + 1U) <= pMsgContext->resMaxDataLen)
  {
    /* Get the active current session for F186 */
    pMsgContext->resData[pMsgContext->resDataLen] = Dcm_GddCurrentSession;            
    /* Update the Response length  */
    pMsgContext->resDataLen += 1U;

    retVal = E_OK;
  }
  else
  {
    if(NULL_PTR != pNegRespCode)
    {
      *pNegRespCode = DCM_E_RESPONSETOOLONG;
    }
  }

  DCM_UNUSED(IndexOfDid);
  DCM_UNUSED(LusDidCount);
  
  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_MemCopy                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : It is used to copy the data from  src to dest.      **
**                        module                                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : src                                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : dest                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DspInternal_MemClear(
  P2VAR(uint8,AUTOMATIC,DEM_VAR) aDest,
  CONST(uint32, DCM_CONST) aSize)
{
  uint32 i = 0U;

  if(NULL_PTR != aDest)
  {
    for (i = 0; i < aSize; i++)
    {
      aDest[i] = (uint8)0U;
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_DspInternal_MemCopy                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : It is used to copy the data from  src to dest.      **
**                        module                                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : src                                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : dest                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DspInternal_MemCopy(
  P2VAR(uint8,AUTOMATIC,DEM_VAR) aDest,
  P2CONST(uint8,AUTOMATIC,DEM_VAR) aSrc,
  CONST(uint32, DCM_CONST) aSize)
{
  uint32 i = 0U;

  if((NULL_PTR != aDest) && (NULL_PTR != aSrc))
  {
    for (i = 0; i < aSize; i++)
    {
      aDest[i] = aSrc[i];
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadSigTypeNvMBlock                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used to read NvRam block           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucBockId                                           **
**                                                                            **
** InOut parameter      : pData                                               **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Dcm_GaaDidReadSignalData      **
**                                              Dcm_GusSignalDataLoc          **
**                                                                            **
**                        Function(s) invoked : NvM_ReadBlock                 **
**                                                                            **
*******************************************************************************/
#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadSigTypeNvMBlock(
  Dcm_OpStatusType anOpStatus,
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) anOutBuffer)
{
  Std_ReturnType retVal = E_OK;
  NvM_RequestResultType RequestResult = NVM_REQ_PENDING;
  NvM_BlockIdType NvMBlockId = aCfgData->usDcmDspDataBlockIdRef;

  switch(anOpStatus)
  {    
    /* TODO : Cancel operation, FIXME */
    case DCM_CANCEL: 
      retVal = E_NOT_OK;
      break;
    case DCM_PENDING:
      retVal = NvM_GetErrorStatus(NvMBlockId, &RequestResult);
      if (E_OK == retVal)
      {
        switch(RequestResult)
        {
          case NVM_REQ_PENDING:
            retVal = DCM_E_PENDING;
            break;
            
          case NVM_REQ_OK:
            retVal = E_OK;
            break;

          default:
            retVal = E_NOT_OK;      
            break;   
        }
      }
      else
      {
        /* FIXME :
         * Retry : pending
         */
      }
      break;
    case DCM_INITIAL:
      /*Invoke NvM Api to get the data and check for return value */
      retVal = NvM_ReadBlock(NvMBlockId, anOutBuffer);
      if(retVal == E_OK)
      {
        retVal = DCM_E_PENDING;  
      }                    
      break;
    default:
      retVal = E_NOT_OK;        
      break;
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadSigTypeNvMBlock                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used to read NvRam block           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucBockId                                           **
**                                                                            **
** InOut parameter      : pData                                               **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Dcm_GaaDidReadSignalData      **
**                                              Dcm_GusSignalDataLoc          **
**                                                                            **
**                        Function(s) invoked : NvM_ReadBlock                 **
**                                                                            **
*******************************************************************************/
#if (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteSigTypeNvMBlock(
  Dcm_OpStatusType anOpStatus,
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) anInputBuffer,
  Dcm_NegativeResponseCodeType *anOutNegRespCode)
{
  Std_ReturnType retVal = E_OK;
  NvM_RequestResultType RequestResult = NVM_REQ_OK;

  if ((NULL_PTR != aCfgData) && (NULL_PTR != anInputBuffer))
  {
    switch(anOpStatus)
    {    
      /* TODO : Cancel operation, FIXME */
      case DCM_CANCEL: 
        retVal = E_NOT_OK;
        break;
        
      case DCM_PENDING:
        retVal = NvM_GetErrorStatus(aCfgData->usDcmDspDataBlockIdRef, &RequestResult);
        if (E_OK == retVal)
        {
          switch(RequestResult)
          {
            case NVM_REQ_PENDING:
              retVal = DCM_E_PENDING;
              break;
              
            case NVM_REQ_OK:
              retVal = E_OK;
              break;

            default:
              retVal = E_NOT_OK;      
              break;   
          }
        }          
        break;
        
      case DCM_INITIAL:
        /* Locking NvBlock from application */
        NvM_SetBlockLockStatus(aCfgData->usDcmDspDataBlockIdRef, DCM_FALSE);      

        retVal = NvM_WriteBlock(aCfgData->usDcmDspDataBlockIdRef, anInputBuffer);
        if(retVal == E_OK)
        {
          retVal = DCM_E_PENDING;  
        }                    
        break;
        
      default:
        retVal = E_NOT_OK;        
        break;
    }

    /* Writing operation is successful or not */
    if (DCM_E_PENDING !=  retVal)
    {
      NvM_SetBlockLockStatus(aCfgData->usDcmDspDataBlockIdRef, DCM_TRUE);
      if (E_NOT_OK ==  retVal)
      {
        /* [SWS_Dcm_00541]
         * 4.b) Otherwise (on any NvM failure) the DCM module shall trigger a negative 
         * response with NRC 0x10 (GeneralReject) */
        *anOutNegRespCode = DCM_E_GENERALREJECT; 
      }
    }
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ConditionCheckRead                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used to check the condition of data**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucDataType                                         **
**                                                                            **
** InOut parameter      : pData                                               **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
*******************************************************************************/
/* (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)) && \*/
#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ConditionCheckRead(
  Dcm_OpStatusType anOpStatus,
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) anOutNegRespCode)
{
  Std_ReturnType retVal = E_OK; 
  
  if (NULL_PTR == anOutNegRespCode)
  {
    retVal = E_NOT_OK;  
  }
  else if(NULL_PTR == aCfgData)
  {
    retVal = E_NOT_OK;
    *anOutNegRespCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    *anOutNegRespCode = DCM_E_POSITIVERESPONSE;  
  
    if (
      (aCfgData->ucDcmDspDataUsePort == DCM_USE_DATA_ASYNCH_FNC) || 
      (aCfgData->ucDcmDspDataUsePort == DCM_USE_DATA_ASYNCH_CLIENT_SERVER)
    )
    {         
      if (NULL_PTR != aCfgData->pConditionCheckReadAsync)
      {
        retVal = aCfgData->pConditionCheckReadAsync(anOpStatus, anOutNegRespCode);
      }
    }
    
    else if (
      (aCfgData->ucDcmDspDataUsePort == DCM_USE_DATA_SYNCH_FNC) || 
      (aCfgData->ucDcmDspDataUsePort == DCM_USE_DATA_SYNCH_CLIENT_SERVER)
    )
    {
      if ((anOpStatus == DCM_INITIAL) && (NULL_PTR != aCfgData->pConditionCheckReadSync))
      {
        /* As per Dcm713_Conf, 
           DCM_E_PENDING return value is not allowed 
           And OpStatus parameter is not existing in the prototype */
        retVal = aCfgData->pConditionCheckReadSync(anOutNegRespCode);
      }
    }
    else
    {
      /* retVal = E_OK */
    }
    
    /* if OpStatus is DCM_CANCEL, return value shall be ignored */  
    if (anOpStatus == DCM_CANCEL)
    {
      retVal = E_NOT_OK;
    }
  }
  
  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadSigType                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used to read data element          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucDataType                                         **
**                                                                            **
** InOut parameter      : pData                                               **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
*******************************************************************************/
/* (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)) && \ */
#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadSigType(
  Dcm_OpStatusType anOpStatus,
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) anOutputBuffer)
{
  Std_ReturnType retVal = E_NOT_OK;

  if(NULL_PTR != aCfgData)
  {
    /* if (OpStatus == DCM_CANCEL), This function shall return E_NOT_OK */
    if (
      (anOpStatus == DCM_INITIAL) ||
      (
        (
          (anOpStatus == DCM_CANCEL) || 
          (anOpStatus == DCM_PENDING)
        ) &&
        (
          (aCfgData->ucDcmDspDataUsePort == DCM_USEBLOCKID) ||
          (aCfgData->ucDcmDspDataUsePort == DCM_USE_DATA_ASYNCH_FNC) ||
          (aCfgData->ucDcmDspDataUsePort == DCM_USE_DATA_ASYNCH_CLIENT_SERVER)
        )
      )
    )
    {        
      switch(aCfgData->ucDcmDspDataUsePort)
      {
        case DCM_USEBLOCKID:
          /* possibe opstatus : initial, pending, cancel */
          retVal = Dcm_DspInternal_ReadSigTypeNvMBlock(anOpStatus, aCfgData, anOutputBuffer);
          break;
          
        case DCM_USEECUSIGNAL:
          retVal = Dcm_CfgInternal_ReadSigTypeEcuSignal(aCfgData,anOutputBuffer);
          break;
        
        case DCM_USE_DATA_ASYNCH_CLIENT_SERVER:
        case DCM_USE_DATA_ASYNCH_FNC:
         /* possibe opstatus : initial, pending, cancel */
          if (NULL_PTR != aCfgData->pReadDataAsync)
          {
            retVal = aCfgData->pReadDataAsync(anOpStatus, anOutputBuffer);
          }
          break;
          
        case DCM_USE_DATA_SYNCH_CLIENT_SERVER:
        case DCM_USE_DATA_SYNCH_FNC:
          if (NULL_PTR != aCfgData->pReadDataSync)
          {
            retVal = aCfgData->pReadDataSync(anOutputBuffer);
          }
          break;
          
        case DCM_USE_DATA_SENDER_RECEIVER:
          retVal = Dcm_CfgInternal_ReadSigTypeSenderReceiver(aCfgData, anOutputBuffer);
          break;
          
        default: 
          /* Do Nothing */
          break;
      }
    }
  }
  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadDidTypeDidRange                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used to read did range             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucDataType                                         **
**                                                                            **
** InOut parameter      : pData                                               **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
*******************************************************************************/
#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidTypeDidRange(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint16 LusDIDIndex,
  uint16 LusDidCount,
  Dcm_NegativeResponseCodeType *pNegRespCode)
{
  Std_ReturnType retVal = E_NOT_OK;
  P2VAR(Dcm_DidProcStateType, AUTOMATIC, DCM_APPL_DATA) pRdDid =
                                                           &Dcm_DidProcState[0];
  P2VAR(Dcm_DIDRangeConfig, AUTOMATIC, DCM_APPL_DATA)pDIDRangeConfig = NULL_PTR;
  uint16 sizeOfDid = 0U;
  uint16 dataIdentifier;

  pDIDRangeConfig = Dcm_CfgInternal_GetDIDRangeConfig(LusDIDIndex);

  if(NULL_PTR == pDIDRangeConfig)
  {
    /* DidRange is not configured */
    retVal = E_NOT_OK;
    *pNegRespCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {  
    dataIdentifier = pRdDid->dataId;
    *pNegRespCode = DCM_E_POSITIVERESPONSE;
    /* FIXME : length of data shall be changed to exact length instead it */
    if((pMsgContext->resDataLen + 
        pDIDRangeConfig->usDidRangeMaxDataLength) > 
        pMsgContext->resMaxDataLen)
    {
      *pNegRespCode = DCM_E_RESPONSETOOLONG;
      /* retVal = E_NOT_OK; */
    }
    else
    {  
      P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDst =
                                 &pMsgContext->resData[pMsgContext->resDataLen];

      if(NULL_PTR != pDIDRangeConfig->pDidRangeReadDidFnc)
      {
        retVal = pDIDRangeConfig->pDidRangeReadDidFnc(dataIdentifier, pDst,
                                  pRdDid->ucOpStatus, &sizeOfDid, pNegRespCode);
        if(E_OK == retVal)
        {
          pMsgContext->resDataLen += sizeOfDid;
          /* After completing the pended operation, 
           * call the next operation with OpStatus = DCM_INITIAL */
          pRdDid->ucOpStatus = DCM_INITIAL;
        }
        else if(DCM_E_PENDING == retVal)
        {
          /* Set response pending flag to True */
          DCM_SET_RDATA_PENDING_STATUS(DCM_TRUE);
        }
        else /* E_NOT_OK */
        {
          retVal = E_NOT_OK;
          *pNegRespCode = DCM_E_CONDITIONSNOTCORRECT;
        }
      }
      else
      {
        /* retVal = E_NOT_OK; */
        *pNegRespCode = DCM_E_CONDITIONSNOTCORRECT; 
      }
    }
  }

  /* if OpStatus is DCM_CANCEL, return value shall be ignored */  
  if(DCM_CANCEL == pRdDid->ucOpStatus)
  {
    retVal = E_NOT_OK;
  }

  DCM_UNUSED(LusDidCount);

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadSigTypeMemory                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used to read did (memory)          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucDataType                                         **
**                                                                            **
** InOut parameter      : pData                                               **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
*******************************************************************************/
#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) && \
    (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadSigTypeMemory(
  Dcm_OpStatusType anOpStatus,
  uint8 MemoryIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) aOutResData,
  Dcm_NegativeResponseCodeType *anOutNegRespCode)
{
  Std_ReturnType retVal = E_NOT_OK;  
  Dcm_ReturnReadMemoryType retReadMem;

  *anOutNegRespCode = DCM_E_POSITIVERESPONSE;

  /* Invoke callout Dcm_ReadMemory  */
  retReadMem = Dcm_ReadMemory(
    anOpStatus, MemoryIdentifier, MemoryAddress, MemorySize, aOutResData);
      
  if (retReadMem == DCM_READ_OK )
  {
    retVal = E_OK;
  }
  else if (retReadMem == DCM_READ_PENDING )
  {
    retVal = DCM_E_PENDING;
  }
  else if (retReadMem == DCM_READ_FORCE_RCRRP)
  {
    /* Update Dcm_GusMaxNoOfForceRespPend */
    Dcm_GusMaxNoOfForceRespPend++;    
    /* Check if Dcm_GusMaxNoOfForceRespPend reaches configured limit */
    /* 0xFF : limit threshold is unused */
    if(Dcm_GusMaxNoOfForceRespPend > (uint16)Dcm_diag_Resp_Max_Num_Respend)
    {
      Dcm_GusMaxNoOfForceRespPend = 0U;        
      /* Invoke callout Dcm_ReadMemory with OpStatus DCM_CANCEL */
      (void)Dcm_ReadMemory(
        DCM_CANCEL, MemoryIdentifier, MemoryAddress, MemorySize, &aOutResData[1U]);
        
      *anOutNegRespCode = DCM_E_GENERALREJECT;
      retVal = E_NOT_OK;
    }
    else
    {
      *anOutNegRespCode = DCM_E_RESPONSEPENDING;
      retVal = DCM_E_FORCE_RCRRP;
    }
  }
  else /* DCM_READ_FAILED : failed */
  {
    *anOutNegRespCode = DCM_E_GENERALPROGRAMMINGFAILURE;
    retVal = E_NOT_OK;
  }

  if (anOpStatus == DCM_CANCEL)
  {
    /* *pNegRespCode is ignored */
    retVal = E_NOT_OK;
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_GetSizeOfDidSignal                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used to get size of data element   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LpDataInfo                                          **
**                                                                            **
** InOut parameter      : LpSize                                              **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
*******************************************************************************/
#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
/*    (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)) */
static 
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_GetSizeOfDidSignal(
  Dcm_OpStatusType anOpStatus, 
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) aSignalSize)
{
  Std_ReturnType retVal = E_NOT_OK;
  
  if ((NULL_PTR != aSignalSize) && (NULL_PTR != aCfgData))
  {
    *aSignalSize = 0U;
    
    /* Variable size (one signal per a DID) */ 
    switch(aCfgData->ucDcmDspDataUsePort)
    {
      case DCM_USE_DATA_ASYNCH_FNC:
      case DCM_USE_DATA_ASYNCH_CLIENT_SERVER:
        if (aCfgData->pDataInfo->blDataFixedLength == DCM_FALSE)
        {    
          if (aCfgData->pReadDataLengthAsync != NULL_PTR)
          {
            /* As per Dcm796 , E_OK: this value is always returned. */
            retVal = aCfgData->pReadDataLengthAsync(anOpStatus, aSignalSize);
          } 
          /* TODO: else { DCM_REPORT_ERROR(sid,type) } */
        }
        else
        {
          *aSignalSize = (aCfgData->usDcmDspDataSize + 7)/8;
          retVal = E_OK;
        }
        break;
      case DCM_USE_DATA_SYNCH_FNC:
      case DCM_USE_DATA_SYNCH_CLIENT_SERVER: 
        if (aCfgData->pDataInfo->blDataFixedLength == DCM_FALSE)
        {    
          if (aCfgData->pReadDataLengthSync != NULL_PTR)
          {
            /* As per Dcm796 , E_OK: this value is always returned. */
            retVal = aCfgData->pReadDataLengthSync(aSignalSize);
          } 
          /* TODO: else { DCM_REPORT_ERROR(sid,type) } */
        }
        else
        {
          *aSignalSize = (aCfgData->usDcmDspDataSize + 7)/8;
          retVal = E_OK;
        }
        break;
        
       default:
        *aSignalSize = (aCfgData->usDcmDspDataSize + 7)/8;
        retVal = E_OK;
        break;
    }
  }
  
  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_GetDidInfo                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used to get size of data element   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LpDataInfo                                          **
**                                                                            **
** InOut parameter      : LpSize                                              **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
*******************************************************************************/
#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON))
/*     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)) */
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_GetDidInfo(
  uint16 aDidindex,
  CONST(boolean, DCM_CONST) aCfgDidRangePresent,
  P2CONST(Dcm_DIDInfoType, AUTOMATIC, DCM_APPL_CONST) *aCfgDidInfo)
{
  Std_ReturnType retVal = E_NOT_OK;
  P2VAR(Dcm_DIDRangeConfig, AUTOMATIC, DCM_APPL_DATA)pDIDRangeConfig = NULL_PTR;
  
  *aCfgDidInfo = NULL_PTR;
  
  if((DCM_ZERO != Dcm_Num_Of_DcmDspDidRangeConfig) &&
                                              (DCM_TRUE == aCfgDidRangePresent))
  {
    pDIDRangeConfig = Dcm_CfgInternal_GetDIDRangeConfig(aDidindex);

    /* DidRange is configured correctly */
    if (NULL_PTR != pDIDRangeConfig)  
    {   
      *aCfgDidInfo = pDIDRangeConfig->pDidInfo;
      retVal = E_OK;
    }
  }
  else
  {  
    if (aDidindex < Dcm_Num_Of_DidParaConfig)
    {
      if(Dcm_GaaDIDParaConfig[aDidindex].blDspDidUsed == DCM_TRUE)
      {
        *aCfgDidInfo = Dcm_GaaDIDParaConfig[aDidindex].pDidInfo;      
        retVal = E_OK;
      }
    }
  }

  return retVal;
}
#endif 

/*******************************************************************************
**                EXTERNAL FUNCTION DEFINITIONS                               **
*******************************************************************************/


/*******************************************************************************
** Function Name        : Dcm_DcmReadDTCInformation                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used for service(0x19) to read all **
**                        the status of server resident DTC information       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddNegRespError,           **
**                        Dcm_GucSubFunction,Dcm_GucReadGlobal,               **
**                        Dcm_GpReqResData,                                   **
**                        Dcm_GaaSubServiceIdConfig, Dcm_GpMsgContext         **
**                        Function(s) invoked : Dcm_DspRptNoOfDTC,            **
**                        Dcm_DspRptDTC, Dcm_DspRptDTCSnapshotRecIdentfn,     **
**                        Dcm_DspRptDTCSnapshotRecByDTCNum,                   **
**                        Dcm_DspRptDTCBySeverityInfo,                        **
**                        Dcm_DspRptFailedConfirmedDTCInfo,                   **
**                        Dcm_DspRptDTCFltDetCtr,                             **
**                        Dcm_ExternalProcessingDone and                      **
**                        Dcm_ExternalSetNegResponse                          **
**                                                                            **
*******************************************************************************/
#if(DCM_READDTC_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmReadDTCInformation(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType requestResult = E_OK;
  P2CONST(Dcm_SubServiceIdConfigType, AUTOMATIC, DCM_APPL_CONST) subServiceCfg;


  Dcm_GucReadGlobal = DCM_FALSE;    

  subServiceCfg = Dcm_DsdInternal_GetSubFunctionByMsgContext(pMsgContext);    
  if(NULL_PTR == subServiceCfg)
  { 
    /* Never be reached, but this code is added for MISRA-rules */  
    Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
    Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
  }
  /* External diagnostic subservice processing  */
  else if(NULL_PTR != subServiceCfg->pSubServiceFnc)
  {
    if ( (DCM_INITIAL == OpStatus) && (pMsgContext->reqDataLen > 0U))
    {
      /* @SWS_Dcm_00764 The pointer in pMsgContext shall point behind the SubFunction */  
      pMsgContext->reqData = &pMsgContext->reqData[1U];
      pMsgContext->reqDataLen--;
    }
    requestResult = subServiceCfg->pSubServiceFnc(OpStatus, pMsgContext);
  }
  /* Dcm-Internal diagnostic subservice processing  */  
  else
  {
    /* Check for the validity of length */
    if(pMsgContext->reqDataLen == subServiceCfg->ucSubFuncLength)
    {
      /*
       * Set the global variable with the sub function value, to do the
       * corresponding sub function's functionality in the function called
       */
      Dcm_GucSubFunction = subServiceCfg->ucSubServiceId;
      /*
       *Set the global variable with the response data buffer address,
       *which is to be used in the corresponding sub function invoked
       */

      Dcm_GpReqResData = pMsgContext->resData;

      /* Invoke the sub function that is requested */
      switch(Dcm_GucSubFunction)
      {
      #if(DCM_RPT_NOOFDTC == STD_ON)
      case DCM_ONE:
      case DCM_RDTCI_REPORT_NUMBEROFDTC_BY_SEVERITYMASKRECORD:
      case DCM_SEVENTEEN:
      case DCM_EIGHTTEEN:
        /* Dsp function to be invoked for subfunction values 0x01, 0x07,
            0x11 and 0x12 */
        Dcm_DspRptNoOfDTC(pMsgContext);
        break;
      #endif

      #if(DCM_RPT_DTC == STD_ON)
      case DCM_TWO:
        #if (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON)        
        Dcm_InternalTroubleCodeService = DCM_FALSE;
        if (DCM_READ_ITC_SERVICE == (pMsgContext->idContext & DCM_SID_MASK))
        {
          /* ReadITCInformation's reportITCByStatusMask 
           * supports only ITCStatusMask(0x08) */
          if (DCM_ITC_STATUS_MASK != pMsgContext->reqData[1u])
          {
            Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
            break;
          }
          else
          {
            Dcm_InternalTroubleCodeService = DCM_TRUE;
           /* No break */
          }
        }
        else
        {
          /* No break */
        }
        #endif
        /* No break */
      case DCM_TEN:
      case DCM_FIFTEEN:
      case DCM_NINETEEN:
      case DCM_TWENTYONE:
        /* Dsp function to be invoked for subfunction values 0x02, 0x0A,
            0x0F, 0x13, 0x15 */
        Dcm_DspRptDTC(pMsgContext);
        break;
      #endif

      #if(DCM_RPT_DTCSNAPSHOTREC_IDENTFN == STD_ON)
      case DCM_THREE:
        /* Dsp function to be invoked for subfunction value 0x03 */
        Dcm_DspRptDTCSnapshotRecIdentfn(pMsgContext);
        break;
      #endif

      #if((DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON) || \
      (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON))
      case DCM_RDTCI_REPORT_DTCSNAPSHOTRECORD_BY_DTCNUMBER:
      case DCM_RDTCI_REPORT_DTCEXTDATARECORD_BY_DTCNUMBER:
      case DCM_RDTCI_REPORT_MIRRORMEMORY_DTCEXTDATARECORDBY_DTCNUMBER:
        /* Dsp function to be invoked for subfunction value 0x04, 0x06, 0x10 */
        Dcm_DspRptDTCSnapshotRecByDTCNum(pMsgContext);
        break;
      #endif

      #if(DCM_RPT_DTCSNAPSHOTREC_BYSNAPSHOTNUM == STD_ON)
      case DCM_FIVE:
        /* Dsp function to be invoked for subfunction 0x05 */
        Dcm_DspRptDTCSnapshotRecByRecordNum(pMsgContext);
        break;
      #endif

      #if(DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON)
      case DCM_EIGHT:
        /* Dsp function to be invoked for subfunction values 0x08 */
        Dcm_DspRptDTCBySeverityInfo(pMsgContext);
        break;
      #endif

      #if(DCM_RPT_DTCBYSEVERITYINFOFDTC == STD_ON)
      case DCM_NINE:
        /* Dsp function to be invoked for subfunction values 0x09 */
        Dcm_DspRptDTCBySeverityInfoOfDTC(pMsgContext);
        break;
      #endif

      #if(DCM_RPT_FAILEDCONFIRMEDDTCINFO == STD_ON)
      case DCM_ELEVEN:
      case DCM_TEWELVE:
      case DCM_THIRTEEN:
      case DCM_FOURTEEN:
        /* Dsp function to be invoked for subfunction values
            0x0B, 0x0C, 0x0D, 0x0E */
        Dcm_DspRptFailedConfirmedDTCInfo(pMsgContext);
        break;
      #endif

      #if(DCM_RPT_DTC_FLT_DET_CTR == STD_ON)
      case DCM_TWENTY:
        /* Dsp function to be invoked for subfunction values 0x14 */
        Dcm_DspRptDTCFltDetCtr(pMsgContext);
        break;
      #endif
      default:
        /* Do Nothing */
        break;
      }      
    }
    else
    {
      Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    /* Dcm_GucReadGlobal set to true after Dcm_DspRptDTC is called,
     * It  means that response is NRC or fault */
    if(Dcm_GucReadGlobal == DCM_FALSE)
    {
      if (Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE)
      {
        Dcm_InternalSetNegResponse(pMsgContext, Dcm_GddNegRespError);
      }
      Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
    }    
  }
  
  return requestResult;  
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmClearDiagnosticInformation                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The ClearDiagnosticInformation service is used to   **
**                        clear the UDS Data from the error memory. This      **
**                        service executes DEM function Dem_ClearDTC with     **
**                        parameter DTCGroup equal to the value received in   **
**                        the request to remove either one DTC or a group of  **
**                        DTCs and all related information from the           **
**                        fault memory                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GulDTCValue,               **
**                        Dcm_GddNegRespError                                 **
**                        Function(s) invoked : Dcm_ExternalSetNegResponse,   **
**                        Dcm_ExternalProcessingDone,                         **
**                        Dcm_DspClearDiagInfo                                **
**                                                                            **
*******************************************************************************/
#if(DCM_DSP_CLR_DIAG_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmClearDiagnosticInformation(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;
  Tun_DcmDword32 LunDcmDword32;

  /* Update variable as DCM_ZERO */
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  
  /* Get the pointer to the request data buffer */
  LpReqResData = pMsgContext->reqData;

  /* Update 4 bytes DTC */
  LunDcmDword32.ddByte.ucLsByte      = LpReqResData[DCM_TWO];
  LunDcmDword32.ddByte.ucMidLowByte  = LpReqResData[DCM_ONE];
  LunDcmDword32.ddByte.ucMidHiByte   = LpReqResData[DCM_ZERO];
  LunDcmDword32.ddByte.ucMsByte      = DCM_ZERO;

  /* Check for the validity of length */
  if(pMsgContext->reqDataLen != DCM_THREE)
  {
    /* Update the NRC value */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  {
    #if (DCM_CLEAR_ITC_SERVICE_SUPPRT == STD_ON)
    
    Dcm_InternalTroubleCodeService = DCM_FALSE;
    if (DCM_CLEAR_ITC_SERVICE == (pMsgContext->idContext & DCM_SID_MASK))
    {
      if ((DCM_DTCGROUP_CHASSIS_GROUP != LunDcmDword32.ulLongReg32) &&
          (DCM_DTCGROUP_ALL_GROUPS != LunDcmDword32.ulLongReg32))
      {
        Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
      }
      else
      {
        Dcm_InternalTroubleCodeService = DCM_TRUE;
      }
    }

    #endif
  } 
  if (DCM_E_POSITIVERESPONSE == Dcm_GddNegRespError)
  {
    /* Invoke function */
    Dcm_GulDTCValue = LunDcmDword32.ulLongReg32;
    Dcm_DspClearDiagInfo(LunDcmDword32.ulLongReg32,pMsgContext);
  }
  else
  {
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }

  DCM_UNUSED(OpStatus);
  /* TODO: return value shall be processed */
  return E_OK;
}

/*******************************************************************************
** Function Name        : Dcm_DspClearDiagInfo                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is an internal function for service ox14 and   **
**                        shall be invoked from the main for DEM_DTC_PENDING  **
**                        conditions                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LulDTC                                              **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_PrtclTxBufStatus,          **
**                        Dcm_GddNegRespError                                 **
**                        Function(s) invoked : Dem_ClearDTC                  **
**                        Dcm_ExternalProcessingDone,                         **
**                        Dcm_ExternalSetNegResponse                          **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DspClearDiagInfo(
  uint32 LulDTC,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Dem_ReturnClearDTCType LddReturnValue;
  /* Set the Flag to false */
  Dcm_PrtclTxBufStatus.ucClearDTCStatus = DCM_FALSE;

  #if(DCM_RESPONSE_ON_EVENT_SERVICE  == STD_ON)
  /* Set the Flag when the request is 'Clear All DTCs' */
  if(LulDTC == 0xFFFFFF)
  {
    Dcm_GblRoeClearAll = DCM_TRUE;
  }
  #endif

  /* Clear All DTCs and from Primary memory */
  LddReturnValue = Dem_ClearDTC(LulDTC,
      DEM_DTC_FORMAT_UDS, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
  if(LddReturnValue == DEM_CLEAR_OK)
  {
    /* Update Response message length */
    pMsgContext->resDataLen = DCM_ZERO;

    #if(DCM_RESPONSE_ON_EVENT_SERVICE  == STD_ON)
    /* Reset the Flag */
    if(Dcm_GblRoeClearAll == DCM_TRUE)
    {
      Dcm_GblRoeClearAll = DCM_FALSE;
    }
    #endif
  }
  /* Check for wrong DTC return value */
  else if(LddReturnValue == DEM_CLEAR_WRONG_DTC)
  {
    /* Update the NRC value */
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
  }
  else if(LddReturnValue == DEM_CLEAR_WRONG_DTCORIGIN)
  {
    /* Update the NRC value */
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
  }
  /* Check for Pending return value */
  else if(LddReturnValue == DEM_CLEAR_PENDING)
  {
    Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
    /* Set the Flag for returning of DCM_E_PENDING */
    Dcm_PrtclTxBufStatus.ucClearDTCStatus = DCM_TRUE;
  }
  else
  {
    /* Update the NRC value */
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  if(Dcm_PrtclTxBufStatus.ucClearDTCStatus == DCM_FALSE)
  {
    #if (DCM_CLEAR_ITC_SERVICE_SUPPRT == STD_ON)
    /* ClearInternalTroubleCodes supports 
     * only ConditionsNotCorrect, incorrectMessageLengthOrInvalidFormat */
    if (DCM_TRUE == Dcm_InternalTroubleCodeService)
    {
      if (Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE)          
      {
        Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
      }
      Dcm_InternalTroubleCodeService = DCM_FALSE;
    }
    #endif
    
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmControlDTCSetting                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The DcmControlDTCSetting service is used to stop or **
**                        resume the setting of diagnostic trouble codes      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddNegRespError,           **
**                        Function(s) invoked : Dcm_ExternalSetNegResponse,   **
**                        Dcm_ExternalProcessingDone, Dem_EnableDTCStorage,   **
**                        Dem_DisableDTCStorage                               **
**                                                                            **
*******************************************************************************/
#if(DCM_DSP_CONTROL_DTC_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmControlDTCSetting(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2CONST(Dcm_SubServiceIdConfigType, AUTOMATIC, DCM_APPL_CONST) subServiceCfg;
  Std_ReturnType requestResult = E_OK;  

  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;

  subServiceCfg = Dcm_DsdInternal_GetSubFunctionByMsgContext(pMsgContext);    
  if(NULL_PTR == subServiceCfg)
  { 
    /* Never be reached, but this code is added for MISRA-rules */  
    Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
  }
  /* External diagnostic subservice processing  */
  else if(NULL_PTR != subServiceCfg->pSubServiceFnc)
  {
    if ((pMsgContext != NULL_PTR) && (DCM_INITIAL == OpStatus) && (pMsgContext->reqDataLen > 0U))
    {
      /* @SWS_Dcm_00764 The pointer in pMsgContext shall point behind the SubFunction */  
      pMsgContext->reqData = &pMsgContext->reqData[1U];
      pMsgContext->reqDataLen--;
    }
    requestResult = subServiceCfg->pSubServiceFnc(OpStatus, pMsgContext);
  }
  /* Internal diagnostic subservice processing  */  
  else
  {
    if ( (pMsgContext == NULL_PTR) ||  (pMsgContext->resData == NULL_PTR) || (pMsgContext->reqData == NULL_PTR) )
    { 
      Dcm_InternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
    }
    /* Check for the validity of length */
    else if(pMsgContext->reqDataLen != 1U)
    {
      Dcm_InternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);    
    }
    else
    { 
      Dem_ReturnControlDTCSettingType controlDTCSetting;    
      uint8 subFunctionId = subServiceCfg->ucSubServiceId;

      /* Enable DTC Setting */
      if (0x01 == subFunctionId)
      {
        /* Enable the storage of DTCs */
        controlDTCSetting =  Dem_EnableDTCSetting(DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_KIND_ALL_DTCS);        
        if(controlDTCSetting == DEM_CONTROL_DTC_SETTING_OK)
        {
          Dcm_GblDTCSettingDisabled = DCM_FALSE;
        }
      }
      /* Disable DTC Setting */
      else
      {
        /* Disable the storage of DTCs */
        controlDTCSetting = Dem_DisableDTCSetting(DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_KIND_ALL_DTCS);
        if(controlDTCSetting == DEM_CONTROL_DTC_SETTING_OK)
        {
          Dcm_GblDTCSettingDisabled = DCM_TRUE;
        }
      }
      
      if(controlDTCSetting != DEM_CONTROL_DTC_SETTING_OK)
      {
        /* [SWS_Dcm_00830]
         * In case of Dem_DcmDisableDTCSetting or Dem_DcmEnableDTCSetting returns 
         * DEM_CONTROL_DTC_WRONG_DTCGROUP (wrong groupOfDTC), the Dcm shall 
         * return NRC 0x31 (RequestOutOfRange).*/
        Dcm_InternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
      }
      else
      {      
        pMsgContext->resDataLen = 1U;
        pMsgContext->resData[0U] = subFunctionId; 
        
        /* [SWS_Dcm_00783]  
         * In case of Dem_DcmEnableDTCSetting returns 
         * DEM_CONTROL_DTC_SETTING_OK (see [SWS_Dcm_00304]), the DCM shall 
         * invoke a mode switch of the ModeDeclarationGroupPrototype 
         * DcmControlDTCSetting by calling SchM_Switch_<bsnp>_DcmControlDTCSetting 
         * (RTE_MODE_DcmControlDTCSetting_ENABLEDTCSETTING). 
         *
         * 
         * [SWS_Dcm_00784]
         * In case of Dem_DcmDisableDTCSetting returns 
         *  DEM_CONTROL_DTC_SETTING_OK (see [SWS_Dcm_00406] ), the DCM shall 
         *  invoke a mode switch of the ModeDeclarationGroupPrototype 
         *  DcmControlDTCSetting by calling SchM_Switch_<bsnp>_DcmControlDTCSetting 
         *  (RTE_MODE_DcmControlDTCSetting_DISABLEDTCSETTING).*/
        (void)SchM_Switch_Dcm_DcmControlDTCSetting(subFunctionId);
      }      
    }
    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);        
  }
  
  return requestResult;  
}
#endif /* #if(DCM_DSP_CONTROL_DTC_SERVICE == STD_ON) */

/*******************************************************************************
** Function Name        : Dcm_DcmDiagnosticSessionControl                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The DiagnosticSessionControl service is used to     **
**                        enable different diagnostic sessions in the server. **
**                        A diagnostic session enables a specific set of      **
**                        diagnostic services and/or functionality in the     **
**                        server                                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_GddNegRespError, Dcm_GddRxPduId,                **
**                        Dcm_GucFailedSecurityAccessCount,                   **
**                        Dcm_GaaDiagSessionConfig                            **
**                        Dcm_GaaPduIdTableConfig, Dcm_GaaProtocolConfig,     **
**                        Dcm_DiagSessionState.sessionTableIndex,             **
**                        Function(s) invoked :Dcm_DsdValidateSubServiceId,   **
**                        BswM_Dcm_RequestSessionMode, Dcm_GetSesCtrlType,    **
**                        Dcm_GetProtocolIDIndex, Dcm_ExternalSetNegResponse, **
**                        Dcm_ExternalProcessingDone                          **
**                                                                            **
*******************************************************************************/
#if(DCM_DSP_DIAG_SESSION_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmDiagnosticSessionControl(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2CONST(Dcm_SubServiceIdConfigType, AUTOMATIC, DCM_APPL_CONST) subServiceCfg;
  Std_ReturnType requestResult = E_OK;  

  Dcm_DiagSessionState.sendPendingResp = DCM_FALSE;

  subServiceCfg = Dcm_DsdInternal_GetSubFunctionByMsgContext(pMsgContext);    
  if(NULL_PTR == subServiceCfg)
  { 
    /* Never be reached, but this code is added for MISRA-rules */  
    Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
    Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
  }
  /* External diagnostic subservice processing  */
  else if(NULL_PTR != subServiceCfg->pSubServiceFnc)
  {
    if ( (DCM_INITIAL == OpStatus) && (pMsgContext->reqDataLen > 0U))
    {
      /* @SWS_Dcm_00764 The pointer in pMsgContext shall point behind the SubFunction */  
      pMsgContext->reqData = &pMsgContext->reqData[1U];
      pMsgContext->reqDataLen--;
    }
    requestResult = subServiceCfg->pSubServiceFnc(OpStatus, pMsgContext);
  }
  /* Dcm-Internal diagnostic subservice processing  */  
  else
  {
    P2CONST(Dcm_ProtocolConfig, AUTOMATIC, DCM_APPL_CONST) protocolCfg;
  
    protocolCfg = Dcm_DsdInternal_GetProcotocolByRxPduId(pMsgContext->dcmRxPduId);  
    if (NULL_PTR == protocolCfg)
    {
      /* Never be reached, but this code is added for MISRA-rules */  
      Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
      /* Det Error */
    }    
    /* Check for the validity of length (except SID) */
    else if(pMsgContext->reqDataLen != 1U)
    {
      Dcm_InternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    else
    {
      P2CONST(Dcm_DiagSessionConfigType, AUTOMATIC, DCM_APPL_CONST) sessionCfg = NULL_PTR;
      Dcm_SesCtrlType requestSession = subServiceCfg->ucSubServiceId;

      sessionCfg = Dcm_DsdInternal_GetSessionCfg(
        protocolCfg, requestSession, &Dcm_DiagSessionState.sessionTableIndex);
      
      if (NULL_PTR != sessionCfg)
      {
        /* This condition is for DMF Test.
           If you want to test, you should change this condition from 0 to 1. */
        #if 0 /*(DCM_STANDARD_SUPPORT == DCM_ES95486_SUPPORT)*/ 
        if ((DCM_PROGRAMMING_SESSION      != requestSession) &&
            (DCM_ECU_PROGRAMMING_MODE_05H != requestSession))
        {
          /* Response message length is 1 , Don't add SessionParameterRecord */
          pMsgContext->resDataLen = 1;
          pMsgContext->resData[0U] = subServiceCfg->ucSubServiceId;
        }
        else
        #endif
        {
          uint16 P2StrServerMaxTiming;
            
          /* Response message length is 5 */
          pMsgContext->resDataLen = 5U;            
          pMsgContext->resData[0U] = subServiceCfg->ucSubServiceId;
           
          /* P2 CAN_SERVER_MAX  : Range = 0~65535ms (resolution = 1) */
          pMsgContext->resData[1] = (uint8)(sessionCfg->usSesP2ServerMax >> (uint16)8);
          pMsgContext->resData[2] = (uint8)(sessionCfg->usSesP2ServerMax & (uint16)0x00ff);

          /* P2* CAN_SERVER_MAX  : Range = 0~655350ms (resolution = 10)  */
          P2StrServerMaxTiming = sessionCfg->usSesP2StrServerMax/10U;
          pMsgContext->resData[3] = (uint8)(P2StrServerMaxTiming >> (uint16)8);
          pMsgContext->resData[4] = (uint8)(P2StrServerMaxTiming & (uint16)0x00ff);
        }
          
        if ((DCM_SESSION_JUMPTOBOOTLOADER == sessionCfg->ucSesForBootLevel) || 
            (DCM_SESSION_JUMPTOSYSSUPPLIERBOOTLOADER == sessionCfg->ucSesForBootLevel)
           )
        { 
          Std_ReturnType LddReturnValue;
          P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST)LpPduIdTable;
          Dcm_SesCtrlType LucSessionLevel;
          
          if(DCM_TRUE == protocolCfg->blSendRespPendOnTransToBoot)
          {
            /**
             * [Dcm654] In case the ModeDeclarationGroupPrototype DcmEcuReset is 
             * switched to mode JUMPTOBOOTLOADER or 
             * JUMPTOSYSSUPPLIERBOOTLOADER and the configuration parameter 
             * is set to TRUE, the DCM shall trigger  DcmSendRespPendOnTransToBoot
             * transmission of NRC 0x78 - RCR-RP. 
             * In the sent confirmation of this NRC 0x78 the DCM shall trigger 
             * the mode switch of the ModeDeclarationGroupPrototype DcmEcuReset 
             * to EXECUTE.*/
         
            Dcm_DiagSessionState.sendPendingResp = DCM_TRUE;    
            Dcm_InternalSetNegResponse(pMsgContext, DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING);
          }

          LucSessionLevel = sessionCfg->ddSesCtrlLevel;
          LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GstMsgContext.dcmRxPduId];

          if(sessionCfg->ucSesForBootLevel == DCM_SESSION_JUMPTOBOOTLOADER)
          {
            /*Invoke Reset Execution of of ECU*/
            (void)SchM_Switch_Dcm_DcmEcuReset(JUMPTOBOOTLOADER);
          }
          else
          {
            (void)SchM_Switch_Dcm_DcmEcuReset(JUMPTOSYSSUPPLIERBOOTLOADER);
          }
          
          Dcm_GddProgConditions.ProtocolId = Dcm_GddProtocolId;
          Dcm_GddProgConditions.TesterSourceAddr = LpPduIdTable->ucProRxTesterSrcAddr;
          Dcm_GddProgConditions.Sid = ((Dcm_GstMsgContext.idContext) & (DCM_BIT6_AND_MASK));
          /* polyspace<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
          /* polyspace<RTE: NIV : Not a defect : No Action Planned > initialized variable */
          Dcm_GddProgConditions.SubFncId = Dcm_GstMsgContext.reqData[0U];            
          Dcm_GddProgConditions.ApplUpdated = DCM_FALSE;
          Dcm_GddProgConditions.SecLvInfo = Dcm_GddSecurityLevel;
          
          #if (DCM_STANDARD_SUPPORT == DCM_ES95486_SUPPORT)         
          LddReturnValue = Dcm_ChkSessionLevel(LucSessionLevel);

          if (LddReturnValue == E_OK)
          #else
          if (LucSessionLevel == DCM_PROGRAMMING_SESSION)
          #endif
          {
            Dcm_GddProgConditions.ReprogramingRequest = DCM_TRUE;
          }
          else
          {
            Dcm_GddProgConditions.ReprogramingRequest = DCM_FALSE;
          }

          if(DCM_TRUE == Dcm_DiagSessionState.sendPendingResp)
          {
            /*
             * When requestCottectlyReceived-ResponsePending (NRC = 78 hex) response code is used,
             * the server shall always send a final response (positive or negative)
             * independent of the suppressPosRspMsgIndicationBit value.
             */
            Dcm_GddProgConditions.ResponseRequired = DCM_TRUE;
          }
          else
          {
            Dcm_GddProgConditions.ResponseRequired = DCM_FALSE;
          }
           
          LddReturnValue = Dcm_SetProgConditions(&Dcm_GddProgConditions);
          if(LddReturnValue != E_OK)
          {
            /* Dcm SWS [Dcm715]
             * If the jump to bootloader is requested and if the call to Dcm_SetProgConditions() 
             * returns E_NOT_OK, the DCM shall not request any reset, shall not perform the jump to 
             * bootloader, and shall answer negatively to the request with NRC 0x22 (Conditions 
             * not correct)
             */

            Dcm_GddProgConditions.ReprogramingRequest = DCM_FALSE;
            (void)Dcm_SetProgConditions(&Dcm_GddProgConditions);
            
            Dcm_InternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
          }    
        }
      }
      else
      {
        /* Never be performed here,
         * Requested Session is not supported */
        Dcm_InternalSetNegResponse(pMsgContext, DCM_E_SUBFUNCTIONNOTSUPPORTED);
      }
    }
    Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
  }
  
  return requestResult;  
}
#endif

#if(DCM_DSP_STOP_DIAG_SESSION_SERVICE== STD_ON)     
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmStopDiagnosticSession(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Dcm_DspInternal_DcmStopDiagnosticSession(pMsgContext);

  DCM_UNUSED(OpStatus);
  
  return E_OK;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmSecurityAccess                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This DcmSecurityAccess provides a means to access   **
**                        data and/or diagnostic services, which have         **
**                        restricted access for security, emissions or safety **
**                        reasons                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :  NA                                                 **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_GaaTimer, Dcm_GaaSecurityLevConfig,             **
**                        Dcm_GucDspStIndex,Dcm_GddOpStatus                   **
**                        Dcm_GddNegRespError, Dcm_DspSerPgStatus             **
**                        Dcm_GucSecurSequChk,                                **
**                        Dcm_GucFailedSecurityAccessCount                    **
**                        Dcm_GaaSIdConfig, Dcm_GaaSeed,                      **
**                                           Dcm_GaaSubServiceIdConfig,       **
**                        cm_GucSubSerIdIndex, Dcm_DspServiceProcessingSts    **
**                        Function(s) invoked : Xxx_CompareKey,               **
**                        Dcm_GetSecurityLevel,                               **
**                                                                            **
*******************************************************************************/
#if(DCM_DSP_SECURITY_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmSecurityAccess(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Dcm_NegativeResponseCodeType LddErrorCode;
  Dcm_SecLevelType LddCurrentSecurityLevel;
  Std_ReturnType LddReturnValue;

  uint32 LulLoopCnt;
  uint8 LucSecLvl;

  P2CONST(Dcm_SubServiceIdConfigType, AUTOMATIC, DCM_APPL_CONST) subServiceCfg;
  Std_ReturnType requestResult = E_OK;  

  subServiceCfg = Dcm_DsdInternal_GetSubFunctionByMsgContext(pMsgContext);    
  if(NULL_PTR == subServiceCfg)
  { 
    /* Never be reached, but this code is added for MISRA-rules */  
    Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
    Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
  }
  /* External diagnostic subservice processing  */
  else if(NULL_PTR != subServiceCfg->pSubServiceFnc)
  {
    if ( (DCM_INITIAL == OpStatus) && (pMsgContext->reqDataLen > 0U))
    {
      /* @SWS_Dcm_00764 The pointer in pMsgContext shall point behind the SubFunction */  
      pMsgContext->reqData = &pMsgContext->reqData[1U];
      pMsgContext->reqDataLen--;
    }
    requestResult = subServiceCfg->pSubServiceFnc(OpStatus, pMsgContext);
  }
  /* Dcm-Internal diagnostic subservice processing  */  
  else
  {
    /* Get the security requested for the sub function */
    LucSecLvl = pMsgContext->reqData[DCM_ZERO] & DCM_SUBFUNCTION_MASK;

    /* Check if Security Delay timer is expired or not */
    if(Dcm_GaaTimer[DCM_SECURITY_TIMER] != DCM_ZERO)
    {
      Dcm_InternalSetNegResponse(pMsgContext, DCM_E_REQUIREDTIMEDELAYNOTEXPIRED);
    }
    else if (Dcm_GucDspStIndex >= Dcm_Num_Of_Security_Level_Config)
    {
      Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);    
    }
    /* Check whether the request buffer value is for key or seed */
    else if ((LucSecLvl & DCM_BIT0_AND_MASK) == DCM_ZERO) /* Compare key */
    {
      /* Check for the validity of length */
      if( (Dcm_GaaSecurityLevConfig[Dcm_GucDspStIndex].ulSizeOfKey + 1U) != pMsgContext->reqDataLen)
      {
        Dcm_InternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
      }
      /*
       * Check whether the request has sent twice or thrice without
       * maintaining the cycle of RequestSeed and Key
       */

      /* After RequestSeed is successful ,ucSecSeedReq  will be true */
      else if (Dcm_DspSerPgStatus.ucSecSeedReq == DCM_FALSE)
      {
        /* If seed has been not requested, report sequence error */
        Dcm_InternalSetNegResponse(pMsgContext, DCM_E_REQUESTSEQUENCEERROR);
      }
      else if ((Dcm_GucSecurSequChk != 0U) && (Dcm_GucSecurSequChk != LucSecLvl))
      {
        /* If seed was not requested, report sequence error */
        Dcm_InternalSetNegResponse(pMsgContext, DCM_E_REQUESTSEQUENCEERROR);
      }
      else
      {
        Dcm_GddOpStatus = DCM_INITIAL;

        LddReturnValue = Dcm_DspInternal_DcmSecurityAccess(
          DCM_INITIAL,  &Dcm_GaaSecurityLevConfig[Dcm_GucDspStIndex], 
          pMsgContext->reqData, &LddErrorCode, LucSecLvl);

        if(LddReturnValue == DCM_E_PENDING)
        {
          Dcm_DspServiceProcessingSts.ucSecCompareKeyReqPending = DCM_TRUE;

          Dcm_GddOpStatus = DCM_PENDING;
        }
        /* Check if compare key failed */
        else if(LddReturnValue != DCM_E_OK)
        {
          #if((DCM_STANDARD_SUPPORT == DCM_ES96590_SUPPORT) || \
              (DCM_STANDARD_SUPPORT == DCM_ES95486_SUPPORT) || \
              (DCM_STANDARD_SUPPORT == DCM_ES95486_50_SUPPORT) || \
              (DCM_STANDARD_SUPPORT == DCM_QZN04_SUPPORT))
          Dcm_ChkSecAccessCntInc(&Dcm_GucFailedSecurityAccessCount, 
             Dcm_GaaSecurityLevConfig[Dcm_GucDspStIndex].ucSecNumMaxAttDelay);
             
          #else
          /* Increment the security access count */
          if(Dcm_GucFailedSecurityAccessCount < DCM_MAXVALUE)
          {
            Dcm_GucFailedSecurityAccessCount++;
          }
          #endif

          /*
           * Check whether number of security accesses after which delay time
           * is activated is less than security access count value
           */          
          if(Dcm_GucFailedSecurityAccessCount < 
            Dcm_GaaSecurityLevConfig[Dcm_GucDspStIndex].ucSecNumMaxAttDelay)
          {
            Dcm_InternalSetNegResponse(pMsgContext, DCM_E_INVALIDKEY);
          }
          /* Modified by youngjin.yun, "==" ->  ">=" */
          else /* if(Dcm_GucFailedSecurityAccessCount >= (LpSecData->ucSecNumMaxAttDelay)) */
          {
            /* Report the exceeded number of attempts NRC */
            Dcm_InternalSetNegResponse(pMsgContext, DCM_E_EXCEEDNUMBEROFATTEMPTS);
            DCM_START_TIMER(DCM_SECURITY_TIMER,\
            Dcm_GaaSecurityLevConfig[Dcm_GucDspStIndex].usSecDelayInvKey);
            
            /* security delay lock is on, this routine cannot be entrant */
            #if((DCM_STANDARD_SUPPORT == DCM_ES96590_SUPPORT) || (DCM_STANDARD_SUPPORT == DCM_QZN04_SUPPORT))
            Dcm_ChkSecAccessCntDec(&Dcm_GucFailedSecurityAccessCount);
            /* Set global bit flag indicating the security seed request to FALSE */
            Dcm_DspSerPgStatus.ucSecSeedReq = DCM_FALSE;
            #else
            Dcm_GucFailedSecurityAccessCount = DCM_ZERO;
            #endif
          }        
        }
        else
        {
          /* Set the security level to the requested security level */
          DslInternal_SetSecurityLevel(Dcm_GaaSecurityLevConfig[Dcm_GucDspStIndex].ddSecLevel);

          pMsgContext->resData[0U] = LucSecLvl;
          pMsgContext->resDataLen = 1U;

          #if((DCM_STANDARD_SUPPORT != DCM_ES96590_SUPPORT) && (DCM_STANDARD_SUPPORT != DCM_QZN04_SUPPORT))
          Dcm_GucFailedSecurityAccessCount = DCM_ZERO;
          #endif

          /* Set global bit flag indicating the security seed request to FALSE */
          Dcm_DspSerPgStatus.ucSecSeedReq = DCM_FALSE;
          Dcm_GddOpStatus = DCM_INITIAL;
        }
      }
    }
    /* Request Seed */
    else
    {
      P2CONST(Dcm_SecurityLevConfigType, AUTOMATIC, DCM_APPL_CONST) 
        LpSecData = Dcm_DspInternal_GetSecurityLevelCfg(LucSecLvl, &Dcm_GucDspStIndex);
        
      if (NULL_PTR == LpSecData)
      {
        Dcm_InternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
      }
      else if (Dcm_GucDspStIndex >= Dcm_Num_Of_Security_Level_Config)
      {
        Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);    
      } 
      else
      {
        Dcm_GucSecurSequChk = LucSecLvl + 1U;
        if(pMsgContext->reqDataLen != (1U + LpSecData->ulSecurityADRSize))
        {
          Dcm_InternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        }
        else
        {
          /* Invoke Get security API */
          (void)Dcm_GetSecurityLevel(&LddCurrentSecurityLevel);          

          /**
           * Server is already unlocked 
           */
          if(((LucSecLvl + DCM_ONE)/DCM_TWO) == LddCurrentSecurityLevel)
          { 
            /* Response message length seed length + sub function */
            pMsgContext->resDataLen = LpSecData->ulSizeOfSeed + 1U;            
            pMsgContext->resData[0U] = LucSecLvl;

            LulLoopCnt = 0U;
            while(LulLoopCnt < LpSecData->ulSizeOfSeed)
            {
              pMsgContext->resData[1U + LulLoopCnt] = 0U;
              LulLoopCnt++;
            }
          }
          else
          {
            #if((DCM_STANDARD_SUPPORT == DCM_ES96590_SUPPORT) || (DCM_STANDARD_SUPPORT == DCM_QZN04_SUPPORT))
            if(DCM_TRUE == Dcm_DspSerPgStatus.ucSecSeedReq)
            {
              LddReturnValue = Dcm_SetSecAccessCntInc(&Dcm_GucFailedSecurityAccessCount, 
                                           pMsgContext, LpSecData);
            }
            else
            {
              LddReturnValue = E_OK;
            }

            if(E_OK == LddReturnValue)
            #endif
            {
              #if((DCM_STANDARD_SUPPORT == DCM_ES96590_SUPPORT) || (DCM_STANDARD_SUPPORT == DCM_QZN04_SUPPORT))
              if(Dcm_DspSerPgStatus.ucSecSeedReq == DCM_TRUE)
              {
                /* If the tester sends a consecutive "Request Seed", the request is accepted and the same seed is returned */
              }
              else
              #endif
              {
                #if (DCM_SECURITY_CRL_ENABLE == STD_ON)
                Dcm_GaaCRLLegnth = pMsgContext->reqDataLen - PLAINDATA - DCM_CERTIFICATE_SIGNATURE - 1U;
                #endif
              
                LddReturnValue = Dcm_DspInternal_DcmSecurityAccess(DCM_INITIAL, LpSecData, 
                pMsgContext->reqData, &LddErrorCode, LucSecLvl);   
              }    

              if(LddReturnValue == E_OK)
              {
                /* Response message length seed length + sub function */
                pMsgContext->resDataLen = LpSecData->ulSizeOfSeed + 1U;
                pMsgContext->resData[0U] = LucSecLvl;    
                
                LulLoopCnt = 0U;                          
                while(LulLoopCnt < LpSecData->ulSizeOfSeed)
                {
                  pMsgContext->resData[1U + LulLoopCnt] = Dcm_GaaSeed[LulLoopCnt];
                  LulLoopCnt++;
                }
                /* Set bit flag indicating the security seed request to TRUE */
                Dcm_DspSerPgStatus.ucSecSeedReq = DCM_TRUE;
              }
              else if(LddReturnValue == E_NOT_OK)
              {
                Dcm_InternalSetNegResponse(pMsgContext, LddErrorCode);
              }
              else if(LddReturnValue == DCM_E_PENDING)
              {
                Dcm_DspServiceProcessingSts.ucSecSeedReqPending = DCM_TRUE;
    
                Dcm_GddOpStatus = DCM_PENDING;
              }
              else
              {
                /* To avoid QAC warning */
              }
            }
          }
        }
      }
    }

    if((Dcm_DspServiceProcessingSts.ucSecSeedReqPending == DCM_FALSE) &&
       (Dcm_DspServiceProcessingSts.ucSecCompareKeyReqPending== DCM_FALSE))
      /* FIXME: condition is always true &&
      ((Dcm_DspSerPgStatus.ucSecSeedReq == DCM_TRUE)||
       (Dcm_DspSerPgStatus.ucSecSeedReq == DCM_FALSE))) */
    {
      Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
    }        
  }

  return requestResult;  
}
/* polyspace-begin MISRA-C3:20.7 [Justify with annotations:Low] "Not a defect" */
static FUNC(P2CONST(Dcm_SecurityLevConfigType, AUTOMATIC, DCM_APPL_CONST), DCM_CODE)
  Dcm_DspInternal_GetSecurityLevelCfg(
  Dcm_SecLevelType RequestedSecurityLevel,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) SecurityLevelIndex)
{
  P2CONST(Dcm_SecurityLevConfigType, AUTOMATIC, DCM_APPL_CONST) cfgSecurityLevel = NULL_PTR;
  uint8 secLvIdx;
  
  for (secLvIdx = 0U; secLvIdx < Dcm_Num_Of_Security_Level_Config; secLvIdx++)
  {
    if(((RequestedSecurityLevel + DCM_ONE)/DCM_TWO) == Dcm_GaaSecurityLevConfig[secLvIdx].ddSecLevel)
    {
      if (NULL_PTR != SecurityLevelIndex)
      {
        *SecurityLevelIndex = secLvIdx;
      }
      cfgSecurityLevel = &Dcm_GaaSecurityLevConfig[secLvIdx];
    }
  }

  return cfgSecurityLevel;
}
/* polyspace-end MISRA-C3:20.7 [Justify with annotations:Low] "Not a defect" */
/*******************************************************************************
** Function Name        : Dcm_DspInternal_DcmSecurityAccess                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This DcmSecurityAccess provides a means to access   **
**                        data and/or diagnostic services, which have         **
**                        restricted access for security, emissions or safety **
**                        reasons                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LpSecData, LucSecLvl                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : LpReqResData, LddErrorCode                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :Dcm_GaaSeed,                    **
**                        Dcm_GddOpStatus                                     **
**                        Function(s) invoked : Xxx_CompareKey,               **
**                        Dcm_GetSecurityLevel,                               **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE)Dcm_DspInternal_DcmSecurityAccess(
  Dcm_OpStatusType anOpStatus,
  P2CONST(Dcm_SecurityLevConfigType, AUTOMATIC, DCM_APPL_CONST) aSecData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) aReqResData,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) anOutNegRespCode,
  uint8 aSecurityLevel)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_NOT_OK;
  *anOutNegRespCode = DCM_E_POSITIVERESPONSE;

  if ((aSecurityLevel & DCM_BIT0_AND_MASK) == DCM_ZERO)
  {
    if((aSecData->ucSecurityUsePort == USE_SYNCH_CLIENT_SERVER) ||
       (aSecData->ucSecurityUsePort == USE_SYNCH_FNC))
    {
      if(NULL_PTR != aSecData->pCompareKeyFun)
      {
        LddReturnValue = aSecData->pCompareKeyFun(&aReqResData[DCM_ONE]);
      }
    }
    else if((aSecData->ucSecurityUsePort == USE_ASYNCH_CLIENT_SERVER) ||
      (aSecData->ucSecurityUsePort == USE_ASYNCH_FNC))
    {
      if(NULL_PTR != aSecData->pCompareKeyAsyncFun)
      {
        LddReturnValue = aSecData->pCompareKeyAsyncFun
                (&aReqResData[DCM_ONE], anOpStatus);
      }
    }
    else
    {
      /* Do nothing */
    }
  }
  else
  {
    if((aSecData->ucSecurityUsePort == USE_SYNCH_CLIENT_SERVER) ||
      (aSecData->ucSecurityUsePort == USE_SYNCH_FNC))
    {
      if(aSecData->ulSecurityADRSize > DCM_ZERO)
      {
        if(NULL_PTR != aSecData->pGetSeedFun)
        {
          LddReturnValue = aSecData->pGetSeedFun
              (&aReqResData[DCM_ONE], &Dcm_GaaSeed[DCM_ZERO], anOutNegRespCode);
        }
      }
      else
      {
        if(NULL_PTR != aSecData->pGetSeedFunadr)
        { 
          LddReturnValue = aSecData->pGetSeedFunadr
              (&Dcm_GaaSeed[DCM_ZERO], anOutNegRespCode);
        }
      }
    }
    else if((aSecData->ucSecurityUsePort == USE_ASYNCH_CLIENT_SERVER) ||
        (aSecData->ucSecurityUsePort == USE_ASYNCH_FNC))
    {
      if(aSecData->ulSecurityADRSize > DCM_ZERO) 
      {
        if (NULL_PTR != aSecData->pGetSeedAsyncFun)
        {
          LddReturnValue = aSecData->pGetSeedAsyncFun
          (&aReqResData[DCM_ONE], anOpStatus,
          &Dcm_GaaSeed[DCM_ZERO], anOutNegRespCode);
        }
      }
      else
      {
        if(NULL_PTR != aSecData->pGetSeedAsyncFunadr)
        {
          LddReturnValue = aSecData->pGetSeedAsyncFunadr
            (anOpStatus, &Dcm_GaaSeed[DCM_ZERO], anOutNegRespCode);
        }
      }
    }
    else
    {
      /* Det Error */
    }
  }

  if((E_NOT_OK == LddReturnValue) && (DCM_E_POSITIVERESPONSE == *anOutNegRespCode))
  {
    *anOutNegRespCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  
  return(LddReturnValue);
}
#endif /* (DCM_DSP_SECURITY_SERVICE == STD_ON) */

/*******************************************************************************
** Function Name        : Dcm_DcmTesterPresent                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The DcmTesterPresent service is used to keep one or **
**                        multiple servers in a diagnostic session different  **
**                        than the defaultSession                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GddNegRespError,          **
**                        Dcm_GddNegRespError, Dcm_GaaSIdConfig,              **
**                                           Dcm_GaaSubServiceIdConfig        **
**                        Function(s) invoked :  None                         **
**                                                                            **
*******************************************************************************/
#if(DCM_DSP_TESTER_PRESENT_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmTesterPresent(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2CONST(Dcm_SubServiceIdConfigType, AUTOMATIC, DCM_APPL_CONST) subServiceCfg;
  Std_ReturnType requestResult = E_OK;  

  subServiceCfg = Dcm_DsdInternal_GetSubFunctionByMsgContext(pMsgContext);    
  if(NULL_PTR == subServiceCfg)
  { 
    /* Never be reached, but this code is added for MISRA-rules */  
    Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
  }
  /* External diagnostic subservice processing  */
  else if(NULL_PTR != subServiceCfg->pSubServiceFnc)
  {
    if ( (DCM_INITIAL == OpStatus) && (pMsgContext->reqDataLen > 0U))
    {
      /* @SWS_Dcm_00764 The pointer in pMsgContext shall point behind the SubFunction */  
      pMsgContext->reqData = &pMsgContext->reqData[1U];
      pMsgContext->reqDataLen--;
    }
    requestResult = subServiceCfg->pSubServiceFnc(OpStatus, pMsgContext);
  }
  /* Dcm-Internal diagnostic subservice processing  */  
  else
  {
    /* Check for the validity of length */
    if(pMsgContext->reqDataLen != DCM_ONE)
    {
      Dcm_InternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);    
    }
    else
    {
      pMsgContext->resDataLen = 1U;      
      pMsgContext->resData[0U] = pMsgContext->reqData[0U];
    }
    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);    
  }

  return requestResult;  
}
#endif /* (DCM_DSP_TESTER_PRESENT_SERVICE == STD_ON) */

/*******************************************************************************
** Function Name        : Dcm_IDSearch                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function is used to get the Index of  **
**                        DID or Routine ID whenever invoked by other         **
**                        functions                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucIDType, LusDataIdentifier                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpDIDIndex                                          **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GpUDSBaseAddress          **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
   (DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
   (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) || \
   (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON) || \
   (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
   (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
   (DCM_ROUTINECONTROL_SERVICE == STD_ON) || \
   (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON))
/* polyspace<MISRA-C:8.10:Not a defect:Justify with annotations> Whether the Dcm api function is required internal or external linkage, depends on user configuration */
FUNC(boolean, DCM_CODE) Dcm_IDSearch(
  uint16 aTypeOfDid,
  uint16 aDataId,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) aOutDidIndex)
{
  P2CONST(uint16, AUTOMATIC, DCM_APPL_CONST) LpBase;
  uint16 LulIndex;
  uint16 LulMaxIDcount;
  boolean LblSearchResult = DCM_FALSE;

  if(aTypeOfDid == DCM_GET_DID)
  {
    LulMaxIDcount = Dcm_Total_Num_Of_DIDs;
  }
  else
  {
    LulMaxIDcount = Dcm_Total_Num_Of_RIDs;
  }

  LpBase = Dcm_GpUDSBaseAddress[aTypeOfDid];

  if(NULL_PTR != LpBase)
  {
    for(LulIndex = DCM_ZERO; LulIndex < LulMaxIDcount; LulIndex++)
    {
      if(aDataId == LpBase[LulIndex])
      {
        *aOutDidIndex = LulIndex;
        LblSearchResult = DCM_TRUE;
        break;
      }
    }
  }
  
  return (LblSearchResult);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmReadScalingDataByIdentifier                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Read Scaling Data by Identifier is used to      **
**                        read Scaling Data from the application.             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GddNegRespError,          **
**                        Dcm_GaaDIDParaConfig, Dcm_GddOpStatus,              **
**                        Dcm_DspServiceProcessingSts, Dcm_GusDIDIndexVal,    **
**                        Function(s) invoked : Dcm_ExternalSetNegResponse,   **
**                        Dcm_ExternalProcessingDone, Dcm_IDSearch,           **
**                        Dcm_GetSecurityLevel, Xxx_GetScalingInformation     **
**                                                                            **
*******************************************************************************/
#if(DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadScalingData(
  Dcm_OpStatusType aOpStatus,
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,  
  Dcm_MsgType aOutBuffer,   
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) anOutNegRespCode)
{
  Std_ReturnType retVal = E_NOT_OK;
  
  if ( (NULL_PTR != aCfgData) && (NULL_PTR != anOutNegRespCode))
  {
    switch(aCfgData->ucDcmDspDataUsePort)
    {
      case DCM_USE_DATA_ASYNCH_FNC:
      case DCM_USE_DATA_ASYNCH_CLIENT_SERVER:
        if (NULL_PTR != aCfgData->pGetScalingInformationAsync)
        {
           /* Invoke the ScalingInfo function with corresponding buffer for response */
          retVal = aCfgData->pGetScalingInformationAsync(
            aOpStatus, aOutBuffer, anOutNegRespCode);
        }
        break;                

      case DCM_USE_DATA_SYNCH_FNC:
      case DCM_USE_DATA_SYNCH_CLIENT_SERVER:
        if (NULL_PTR != aCfgData->pGetScalingInformationSync)
        {
          retVal = aCfgData->pGetScalingInformationSync(
            aOutBuffer , anOutNegRespCode);
        }                
        break;
       
      default :
        /* TODO : Det Error */
        break;
    }
  }
  else
  {
    /* Avoid to RTRT error */
  }

  return retVal;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmReadScalingDataByIdentifier(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;
  P2CONST(Dcm_DIDParaConfig, AUTOMATIC, DCM_APPL_CONST)LpDIDTAB;
  P2CONST(Dcm_DataInfoType, AUTOMATIC, DCM_APPL_CONST)LpScalingInfo;
  P2CONST(Dcm_DcmDspSignalconfig, AUTOMATIC, DCM_APPL_CONST)LpDcmDspSignal;
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST)LpDcmDspData;
  Dcm_NegativeResponseCodeType LddReturnVal;
  uint32 LulScalingInfosize;
  uint16 LusDataIdentifier;
  uint16 LusDIDIndex = (uint16)0x00;
  uint8 LucDataID;
  boolean LblSearchResult;

  LucDataID = DCM_ZERO;

  /* Get the pointer to the request data buffer of pMsgContext */
  LpReqResData = pMsgContext->reqData;

  /* Check fort the valid request length */
  if(pMsgContext->reqDataLen == DCM_TWO)
  {
    pMsgContext->resDataLen = DCM_ZERO;
    /* Update Identifier from the request buffer */
    LusDataIdentifier = LpReqResData[LucDataID];
    LusDataIdentifier = ((uint16)(LusDataIdentifier << DCM_EIGHT) |
      LpReqResData[LucDataID + DCM_ONE]);

    /* Check if the DID from the request is supported */
    LblSearchResult = Dcm_IDSearch(DCM_GET_DID, LusDataIdentifier,&LusDIDIndex);

    if(LblSearchResult == DCM_TRUE)
    {
      /* Invoke function to validate DID for session and security  */
      LddReturnVal = Dcm_DspValidateDID(LusDIDIndex, DCM_FALSE);
      if(LddReturnVal == DCM_E_POSITIVERESPONSE)
      {
        /* Initialise pointer to the parameters of requested DID */
        LpDIDTAB = &Dcm_GaaDIDParaConfig[LusDIDIndex];

        /*Get the position of the data defined by DcmDspDidDataRef*/
        LpDcmDspSignal = LpDIDTAB->pDcmDspSignal;

        /*Get the configuration of Data's*/
        LpDcmDspData = LpDcmDspSignal->pDcmDspData;

        LpScalingInfo = LpDcmDspData->pDataInfo;

        /* Get the Info size from the configured */
        LulScalingInfosize = LpScalingInfo->ulDataScalingInfoSize;

        if(LulScalingInfosize != DCM_ZERO)
        {
          /* Compare configured scaling size and max response buff size
          ( excluding 2 bytes id)  */
          if(LulScalingInfosize <= (pMsgContext->resMaxDataLen - DCM_TWO))           
          {            
            Std_ReturnType result;
            /* FIXME pDcmDspData[n] */
            result = Dcm_DspInternal_ReadScalingData(
              Dcm_GddOpStatus, LpDcmDspData, &pMsgContext->resData[2U], &Dcm_GddNegRespError);            
           
            if(result == DCM_E_PENDING)
            {
              Dcm_DspServiceProcessingSts.ucReadScalingDataPending = DCM_TRUE;
              Dcm_GusDIDIndexVal = LusDIDIndex;
            }            
            else if(result == E_OK)
            {                    
              pMsgContext->resData[0U] = LpReqResData[0U];       /* Update First Byte DID */
              pMsgContext->resData[1U] = LpReqResData[1U];       /* Update Second Byte DID */
              pMsgContext->resDataLen = 2U + LulScalingInfosize; /* Response message length is Calculated */
            }
            else
            {
              /* Report the Request out of range NRC */
              Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
            }
          }
        }
        else
        {
          /* Report the Request out of range NRC */
          Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
        }
      }
      else
      {
         /* Update the NRC value */
         Dcm_GddNegRespError = LddReturnVal;
      }
    }
    else
    {
      /* Report the Request out of range NRC */
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    }
  }
  else
  {
    /* Update the NRC value */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }

  
  if(Dcm_DspServiceProcessingSts.ucReadScalingDataPending == DCM_FALSE)
  {
    if (Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE)
    {
      Dcm_InternalSetNegResponse(pMsgContext, Dcm_GddNegRespError);
    }
    Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
  }

  DCM_UNUSED(OpStatus);
  /* TODO: return value shall be processed */
  return E_OK;  
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmDynamicallyDefineDataIdentifier              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This DynamicallyDefineDataIdentifier service is     **
**                        used to request dynamically define data Identifiers **
**                        that may subsequently read data by the              **
**                        ReadDataByIdentifier service                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GddNegRespError,          **
**                        Dcm_GaaDIDParaConfig,                               **
**                        Function(s) invoked :                               **
**                        Dcm_DspValidateDynDID,                              **
**                        Dcm_DspClrDynDefinedDID, Dcm_DspDynDefinedByDID,    **
**                        Dcm_DspDynDefinedByMemAddress                       **
**                                                                            **
*******************************************************************************/
#if(DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmDynamicallyDefineDataIdentifier(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;
  P2CONST(Dcm_DIDParaConfig, AUTOMATIC, DCM_APPL_CONST)LpDIDTAB;
  P2CONST(Dcm_DIDInfoType, AUTOMATIC, DCM_APPL_CONST)LpDidInfo;
  P2CONST(Dcm_DIDInfoTypeDidRead, AUTOMATIC, DCM_APPL_CONST)LpDidRead;
  uint32 LulTotReqLen;
  uint16 LusDynDIDIdentifier;
  uint16 LusIDCount = (uint16)0x00;
  uint16 LusDIDIndex = (uint16)0x00;
  uint16 LusDynDIDIndex;
  uint8 LucMaxNumOfSourceEle;
  boolean LblSearchResult;

  /* Get Data from request */
  LpReqResData = pMsgContext->reqData;
  /* Get the total request length from the request */
  LulTotReqLen = pMsgContext->reqDataLen;

  /* Get Data Identifier from the request buffer */
  DCM_GET_DATAID_FROM_REQUEST(LusDynDIDIdentifier, LpReqResData, 1U);
  
  /* Check requested data length in case of subfunction Define by identifier */
  if((LpReqResData[DCM_ZERO] == DCM_ONE) && (LulTotReqLen < DCM_SEVEN))
  {
    /* Report the incorrect message length NRC */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  /* Added by youngjin.yun, 2014-12-16
   * Check requested data length in case of subfunction Define by memory address */
  else if((LpReqResData[DCM_ZERO] == DCM_TWO) && (LulTotReqLen < DCM_SIX))
  {
    /* Report the incorrect message length NRC */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  /* Check for requested data length in case of
      subfunction Define by memory address */
  else if((LpReqResData[DCM_ZERO] == DCM_THREE) && ((LulTotReqLen == DCM_TWO) ||
      (LulTotReqLen > DCM_THREE)))
  {
    /* Report the incorrect message length NRC */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  /* Check whether Data ID is configured range or not */
  else if((LusDynDIDIdentifier < DCM_DYNAMICID_LOWER_RANGE) ||
      (LusDynDIDIdentifier > DCM_DYNAMICID_UPPER_RANGE))
  {
    /* Report the Request out of range NRC */
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
  }
  else
  {
    Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  }

  if(Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE)
  {
    /* Internal function to validate Dynamically defined Data ID */
    LblSearchResult = Dcm_DspValidateDynDID(pMsgContext, &LusIDCount,
        &LusDIDIndex);

    if(LblSearchResult == DCM_TRUE)
    {
      /* Initialize pointer to the parameters of requested DID(config) */
      LpDIDTAB = &Dcm_GaaDIDParaConfig[LusDIDIndex];
      /* Initialize pointer to get the DID information */
      LpDidInfo = LpDIDTAB->pDidInfo;
      /* Initialize pointer to get the DID Control */
      LpDidRead = LpDidInfo->pDidRead;
      /* Get configured limit of maximum number of source elements
        for a single Dynamic data identifier */
      LucMaxNumOfSourceEle = LpDidRead->ucMaxNumSourceElem;
      /* Get the index for dynamically defined DID */
      LusDynDIDIndex = LusDIDIndex - (Dcm_Total_Num_Of_Static_DID -
          Dcm_Total_Num_Of_OBD_DID);

      /* Check for subfunction clear dynamically defined data identifier */
      if(LpReqResData[DCM_ZERO] == DCM_THREE)
      {
        /* Function to clear dynamically defined data identifier */
        Dcm_DspClrDynDefinedDID(LusDynDIDIndex, pMsgContext,
            LucMaxNumOfSourceEle);
      }
      /* Check for subfunction define by identifier */
      else if(LpReqResData[DCM_ZERO] == DCM_ONE)
      {
        /* Function to define data when subfunction is
          Define data by identifier */
        Dcm_DspDynDefinedByDID(LusDynDIDIndex, pMsgContext,
            LucMaxNumOfSourceEle, LusIDCount);
      }
      /* check for subfunction define by memory address */
      else
      {
        /* Function to define data when subfunction is
          Define data by Memory Address */
        Dcm_DspDynDefinedByMemAddress(LusDynDIDIndex, pMsgContext,
            LucMaxNumOfSourceEle, LusIDCount);
      }
      if(Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE)
      {
        /* Update positive response for Clear Dynamically defined Data ID */
        if((LpReqResData[DCM_ZERO] == DCM_THREE) &&
            (LulTotReqLen == DCM_ONE))
        {
          /* Response message length is updated */
          pMsgContext->resDataLen = DCM_ONE;

          /* Update sub function */
          pMsgContext->resData[DCM_ZERO] = LpReqResData[DCM_ZERO];

        }
        /* Update positive response for subfunctions ONE and TWO */
        else
        {
          /* Response message length is updated */
          pMsgContext->resDataLen = DCM_THREE;

          /* Update sub function number */
          pMsgContext->resData[DCM_ZERO] = LpReqResData[DCM_ZERO];

          /* Update First Byte DID */
          pMsgContext->resData[DCM_ONE] = LpReqResData[DCM_ONE];

          /* Update Second Byte DID */
          pMsgContext->resData[DCM_TWO] = LpReqResData[DCM_TWO];
        }

      }
    }
  }
  /* TODO: return value shall be processed */

  DCM_UNUSED(OpStatus);
  
  return E_OK;  
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspDynDefinedByDID                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x2C   **
**                        to validate                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucMaxNumOfSourceEle, LusIDCount                    **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GaaDIDParaConfig          **
**                        Dcm_GddNegRespError, Dcm_GaaDymDefinedDIDInfoType,  **
**                        Dcm_GaaDymMemDIDInfoType                            **
**                        Function(s) invoked :                               **
**                        Dcm_IDSearch, Dcm_DsdValidateSession,               **
**                        Dcm_DsdValidateSecurity, Dcm_DsdModeRuleCheck,      **
**                        Dcm_DspClrDynDefinedDID                             **
**                                                                            **
*******************************************************************************/
#if(DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON)
static FUNC(void, DCM_CODE) Dcm_DspDynDefinedByDID(
  uint16 LusDynDIDIndex,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint8 LucMaxNumOfSourceEle, uint16 LusIDCount)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;
  P2CONST(Dcm_DIDParaConfig, AUTOMATIC, DCM_APPL_CONST)LpDIDTAB;
  P2CONST(Dcm_DIDInfoType, AUTOMATIC, DCM_APPL_CONST)LpDidInfo;
  P2CONST(Dcm_DIDInfoTypeDidRead, AUTOMATIC, DCM_APPL_CONST)LpDidRead;
  P2VAR(Dcm_DymDefinedDIDInfoType, AUTOMATIC, DCM_APPL_DATA) LpDymDIDInfo;
  P2VAR(Dcm_DymMemDIDInfoType, AUTOMATIC, DCM_APPL_DATA) LpDymMemRangeInfo;
  P2VAR(Dcm_SrcIDInfoType, AUTOMATIC, DCM_APPL_DATA) LpSrcIDInfo;
  uint16 LusIDIndex;
  uint16 LusSourceDID;
  uint16 LusDIDIndex = (uint16)0x00;
  uint16 LusStatDIDSize;
  uint16 LusDynDIDIdentifier;
  uint8 LucDataID;
  uint8 LucPosInDataRec;
  uint8 LucMemSizeVal;
  uint8 LucSourceCount;
  uint8 LucLoopVar;
  #if (DCM_MODE_RULE == STD_ON)
  uint8 LucModeIndex;
  #endif
  boolean LblSearchResult;

  LucDataID = DCM_ZERO;
  
  /* Get Data from request */
  LpReqResData = pMsgContext->reqData;
  /* Get Data Identifier from the request buffer */
  DCM_GET_DATAID_FROM_REQUEST(LusDynDIDIdentifier, LpReqResData, 1U);

  /* Loop for all Static IDs security and session check */
  for(LusIDIndex = DCM_ZERO; LusIDIndex < LusIDCount; LusIDIndex++)
  {
    /* Update Source Identifier from the request buffer */
    LusSourceDID = LpReqResData[DCM_THREE + LucDataID];
    LusSourceDID = ((uint16)(LusSourceDID << DCM_EIGHT)) | (LpReqResData[DCM_FOUR + LucDataID]);
    
    /* Check if the DID from the request is supported */
    LblSearchResult = Dcm_IDSearch(DCM_GET_DID, LusSourceDID, &LusDIDIndex);

    if((LblSearchResult == DCM_TRUE) &&
       (LusDIDIndex < Dcm_Num_Of_DidParaConfig))
    {
      uint16 minDidLength = 0u; /* dummy */    
      
      /*Initialize pointer to the parameters
        of requested DID(config)*/
      LpDIDTAB = &Dcm_GaaDIDParaConfig[LusDIDIndex];
      /*Get the configuration of Data's*/
      /* Initialize pointer to get the DID information */
      LpDidInfo = LpDIDTAB->pDidInfo;
      /* Initialize pointer to get the DID Control */
      LpDidRead = LpDidInfo->pDidRead;
      /* Get the DID size configured for the respective static ID */
      Dcm_DspInternal_GetSizeOfDid(LpDIDTAB, &minDidLength, &LusStatDIDSize);    
      /* Get the Position referred from the request */
      LucPosInDataRec = LpReqResData[DCM_FIVE + LucDataID];
      /* Get the Memory Size referred from the request */
      LucMemSizeVal = LpReqResData[DCM_SIX + LucDataID];
      
      /* Check memory size is valid or not */
      if(
        (LucPosInDataRec < 1U) ||
        ((uint16)LucPosInDataRec > LusStatDIDSize) || /* TODO: it shall be verified , uint8 > uint16 */
        ((uint16)((uint16)LucPosInDataRec + (uint16)LucMemSizeVal) > (LusStatDIDSize)))
      {
        /* Report the Request out of range NRC */
        Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
      }
      else
      {
        /* condition to check session for source identifier
          is configured or not */
        if(LpDidRead->pDidReadSession != NULL_PTR)
        {
          /* Invoke Internal function to validate
            for session of Source DID */
          LblSearchResult = Dcm_DsdValidateSession
          (LpDidRead->pDidReadSession, LpDidRead->ucDidReadSesCount);
        }
    
        if(LblSearchResult == DCM_TRUE)
        {
          /* condition to check security for source identifier
            is configured or not */
          if(LpDidRead->pDidReadSecurity != NULL_PTR)
          {
            /* Invoke Internal function for security validation */
            LblSearchResult = Dcm_DsdValidateSecurity
              (LpDidRead->pDidReadSecurity,
                LpDidRead->ucDidReadSecCount);
          }
          if(LblSearchResult == DCM_TRUE)
          {
            #if (DCM_MODE_RULE == STD_ON)
            LucModeIndex = LpDidRead->ucDIDmoderuleArrayindex;
            if(LpDidRead->blModeRuleConfigured  ==  DCM_TRUE )
            {
              LblSearchResult = Dcm_DsdModeRuleCheck(LucModeIndex);
              if(LblSearchResult == DCM_FALSE)
              {
                #if(DCM_DSP_MODE_RULE_NRC == STD_ON)
                Dcm_GddNegRespError =
                  Dcm_GaaModeRuleConfig[LucModeIndex].ucNRCType;
                #else
                /* Update Negative Response Code */
                Dcm_GddNegRespError  =  DCM_E_CONDITIONSNOTCORRECT;
                #endif
              }
            }
            if(LblSearchResult == DCM_TRUE)
            #endif
            {
              /* Next source Data identifier index */
              LucDataID = LucDataID + DCM_FOUR;
              /* No NRC was reported */
              Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
            }
          }
          else
          {
            /* Report the SecurityAccessDenied NRC */
            Dcm_GddNegRespError = DCM_E_SECURITYACCESSDENIED;
          }
        }
        else
        {
          /* Report the Request out of range NRC */
          Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
        }
      }
    }
    else
    {
      /* Report the Request out of range NRC */
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    }

    if (DCM_E_POSITIVERESPONSE != Dcm_GddNegRespError)
    {
      break;
    }
  }
  
  if(Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE)
  {
    LucDataID = DCM_ZERO;

    if(LusDynDIDIndex >= Dcm_Total_Num_Of_Dym_DID)  
    {
      /* For Misra-C check */
      Dcm_GddNegRespError = DCM_E_GENERALREJECT;
    }
    else
    {
      /* Get configured data identifier information */
      LpDymDIDInfo = &Dcm_GaaDymDefinedDIDInfoType[LusDynDIDIndex];
      /* Get configured memory range information */
      LpDymMemRangeInfo = &Dcm_GaaDymMemDIDInfoType[LusDynDIDIndex];
    
      /* update Dynamically defined DID */
      LpDymDIDInfo->usDynDid = LusDynDIDIdentifier;

      /* Current count = (LpDymDIDInfo->ucSrcIDCount + LpDymMemRangeInfo->ucMemAddressCount) 
       * Check for maximum number of source elements for a Dynamic Data ID for seeking free slot */
      if((LpDymDIDInfo->ucSrcIDCount + LpDymMemRangeInfo->ucMemAddressCount) >= LucMaxNumOfSourceEle)
      {
        /* Report the Request out of range NRC */
        Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
      }
      else
      {
        /* Set the flag to true for DID info stored */
        LpDymDIDInfo->blDidSet = DCM_TRUE;
        /* Get the Array to store the information */
        LpSrcIDInfo = LpDymDIDInfo->pSrcIDInfo;
        LucSourceCount = LpDymDIDInfo->ucSrcIDCount +
                              LpDymMemRangeInfo->ucMemAddressCount;
        if(LucSourceCount != DCM_ZERO)
        {
          /* Loop to get index of source data Information */
          for(LucLoopVar = DCM_ZERO; LucLoopVar < LucSourceCount;
            LucLoopVar++)
          {
            LpSrcIDInfo = &LpSrcIDInfo[1u];
          }
        }
        /* Loop to update source Data ID info in Dynamic Defined DID */
        for(LusIDIndex = LucSourceCount; LusIDIndex <
          (LusIDCount + LucSourceCount); LusIDIndex++)
        {
          /* Update Identifier from the request buffer */
            LusSourceDID = LpReqResData[DCM_THREE + LucDataID];
                LusSourceDID = ((uint16)(LusSourceDID << DCM_EIGHT) |
            (LpReqResData[DCM_FOUR + LucDataID]));

          /* Update the source ID */
          LpSrcIDInfo->usSrcID = LusSourceDID;

          /* Update the Position in source data record */
          LpSrcIDInfo->ucPosInSrc = LpReqResData[DCM_FIVE + LucDataID];

          /* Update the Memory size */
          LpSrcIDInfo->ucMemSize = LpReqResData[DCM_SIX + LucDataID];

          /* Update priority of source */
          LpSrcIDInfo->usPriority = LusIDIndex + DCM_ONE;

          LpSrcIDInfo = &LpSrcIDInfo[1u];

          LucDataID = LucDataID + DCM_FOUR;

          /* Check for maximum number of source elements for a Dynamic Data ID*/
          if((LpDymDIDInfo->ucSrcIDCount + LpDymMemRangeInfo->ucMemAddressCount) < LucMaxNumOfSourceEle)
          {
            /* update the static ID count */
            LpDymDIDInfo->ucSrcIDCount = LpDymDIDInfo->ucSrcIDCount + DCM_ONE;
          }
          else
          {
            /* Function to clear dynamically defined data identifier */
            Dcm_DspClrDynDefinedDID(LusDynDIDIndex, pMsgContext,
              LucMaxNumOfSourceEle);

            /* Report the Request out of range NRC */
            Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
            
            /* To break loop */
            break;
          }
        }
      }
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspDynDefinedByMemAddress                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x2C   **
**                        to validate                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucMaxNumOfSourceEle, LusIDCount                    **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GaaReadMemRngConfig       **
**                        Dcm_GddNegRespError, Dcm_GaaDymDefinedDIDInfoType,  **
**                        Dcm_GaaDymMemDIDInfoType,                           **
**                        Dcm_GucRMBAMemoryIdentifier.                        **
**                        Function(s) invoked :                               **
**                        Dcm_DsdValidateSecurity, Dcm_DsdModeRuleCheck,      **
**                        Dcm_DspClrDynDefinedDID                             **
**                                                                            **
*******************************************************************************/
#if(DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON)
static FUNC(void, DCM_CODE) Dcm_DspDynDefinedByMemAddress(
  uint16 LusDynDIDIndex,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint8 LucMaxNumOfSourceEle, uint16 LusIDCount)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;
  P2VAR(Dcm_DymDefinedDIDInfoType, AUTOMATIC, DCM_APPL_DATA) LpDymDIDInfo;
  P2VAR(Dcm_DymMemDIDInfoType, AUTOMATIC, DCM_APPL_DATA) LpDymMemRangeInfo;
  P2CONST(Dcm_ReadMemRngInfoConfigType, AUTOMATIC, DCM_APPL_CONST)
                                                                   LpReadMemRng;
  P2VAR(Dcm_MemAddInfoType, AUTOMATIC, DCM_APPL_DATA) LpSrcMemInfo;
  uint32 LulMemAddress;
  uint32 LulMemorySize;
  uint16 LusIDIndex;
  uint16 LusDynDIDIdentifier;
  uint16 LusSourceCount;
  uint8 LucMemAdrBytes;
  uint8 LucMemSizeBytes;
  uint8 LucDataID;
  uint8 LucLoopVar;

  #if (DCM_MODE_RULE == STD_ON)
  uint8 LucModeIndex;
  #endif
  boolean LblSearchResult;
  boolean LblItemFound;

  LucDataID = DCM_ZERO;
  LulMemAddress = DCM_ZERO;
  LulMemorySize = DCM_ZERO;

  /* Get Data from request */
  LpReqResData = pMsgContext->reqData;

  /* Get Data Identifier from the request buffer */
  DCM_GET_DATAID_FROM_REQUEST(LusDynDIDIdentifier, LpReqResData, 1U);

  /* Get memory address and size bytes from AddressAndLengthFormatIdentifier */
  LucMemAdrBytes = (LpReqResData[DCM_THREE] & DCM_SIG_BYTE_MASK_VALUE);
  LucMemSizeBytes = ((LpReqResData[DCM_THREE] & DCM_SIG_SIZE_MASK_VALUE) >> DCM_FOUR);

  LpReadMemRng = &Dcm_GaaReadMemRngConfig[DCM_ZERO];

  /* Loop for all Memory addresses security check */
  for(LusIDIndex = 0U; LusIDIndex < LusIDCount; LusIDIndex++)
  {
    LucLoopVar = 0U;

    do
    {
      LulMemAddress = LulMemAddress << DCM_EIGHT;
      LulMemAddress |= LpReqResData[DCM_FOUR + LucDataID + LucLoopVar];
      LucLoopVar++;
    }
    while(LucLoopVar < LucMemAdrBytes);

    LucLoopVar = 0U;
    LucDataID = LucDataID + LucMemAdrBytes;

    /*Get memory size from the request*/
    do
    {
      LulMemorySize = LulMemorySize << DCM_EIGHT;
      LulMemorySize |= LpReqResData[DCM_FOUR + LucDataID + LucLoopVar];
      LucLoopVar++;
    }
    while(LucLoopVar < LucMemSizeBytes);

    /* Inedex of next memory address and size */
    LucDataID = LucDataID  + LucMemSizeBytes;

    /* Variable To break The Loop*/
    LblItemFound = DCM_FALSE;

    /* Check Current memory is within memory Range Configures */
    for (
      LucLoopVar = 0U;
      ((LucLoopVar < Dcm_Total_Num_Read_Memory_Configured) && (LblItemFound == DCM_FALSE)); 
      LucLoopVar++
    )
    {      /* Check to get configured memory range info */
      if (
        (LulMemAddress >= LpReadMemRng->ulReadMemRngLow) &&
        ((LulMemAddress + (LulMemorySize - DCM_ONE)) <= LpReadMemRng->ulReadMemRngHigh)
      )
      {
        LblItemFound = DCM_TRUE;
      }
      else
      {
        LpReadMemRng = &LpReadMemRng[1u];
      }
    }

    if(LblItemFound == DCM_TRUE)
    {
      if(LpReadMemRng->pReadMemRngSec != NULL_PTR)
      {
        /* Invoke function for security validation */
        LblSearchResult = Dcm_DsdValidateSecurity(
          LpReadMemRng->pReadMemRngSec,
          LpReadMemRng->ucReadMemSecCount);
      }
      else
      {
        LblSearchResult = DCM_TRUE;
      }
      if(LblSearchResult == DCM_TRUE)
      {
        #if (DCM_MODE_RULE == STD_ON)
        LucModeIndex = LpReadMemRng->ucDIDmoderuleArrayindex;
        if(LpReadMemRng->blModeRuleConfigured  ==  DCM_TRUE )
        {
          LblSearchResult = Dcm_DsdModeRuleCheck(LucModeIndex);
          if(LblSearchResult == DCM_FALSE)
          {
            #if(DCM_DSP_MODE_RULE_NRC == STD_ON)
            Dcm_GddNegRespError = Dcm_GaaModeRuleConfig[LucModeIndex].ucNRCType;
            #else
            /* Update Negative Response Code */
            Dcm_GddNegRespError  =  DCM_E_CONDITIONSNOTCORRECT;
            #endif
          }
        }
        else
        {
          Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
        }
        if(LblSearchResult == DCM_TRUE)
        #endif
        {
          /* No NRC was reported */
          Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
        }
      }
      else
      {
        /* Report the Security Access Denied  NRC */
        Dcm_GddNegRespError = DCM_E_SECURITYACCESSDENIED;
      }
    }
    else
    {
      /* Report the Request out of range NRC Because Memory Address
         Not With in Specified Memory Range */
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    }

    if (DCM_E_POSITIVERESPONSE != Dcm_GddNegRespError)
    {
      break;
    }
    
    LulMemAddress = DCM_ZERO;
    LulMemorySize = DCM_ZERO;

  }
  
  if(Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE)
  {
    LucDataID = DCM_ZERO;

    if(LusDynDIDIndex >= Dcm_Total_Num_Of_Dym_DID)
    {
      /* For Misra-C check */
      Dcm_GddNegRespError = DCM_E_GENERALREJECT;
    }
    else
    {
      /* Get configured data identifier information */
      LpDymDIDInfo = &Dcm_GaaDymDefinedDIDInfoType[LusDynDIDIndex];
  
      /* Get configured memory range information */
      LpDymMemRangeInfo = &Dcm_GaaDymMemDIDInfoType[LusDynDIDIndex];
    
      /* update Dynamically defined DID */
      LpDymMemRangeInfo->usDynDid = LusDynDIDIdentifier;    
    
      /* Check for maximum number of source elements for a Dynamic Data ID for seeking free slot */
      if((LpDymDIDInfo->ucSrcIDCount + LpDymMemRangeInfo->ucMemAddressCount) >= LucMaxNumOfSourceEle)
      {
        /* Report the Request out of range NRC */
        Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
      }
      else
      {
        LusSourceCount = (uint16)LpDymDIDInfo->ucSrcIDCount +
                  (uint16)LpDymMemRangeInfo->ucMemAddressCount;

        /* Set the flag to true for DID info stored */
        LpDymMemRangeInfo->blMemAddSet = DCM_TRUE;

        /* Get the Array to store the information */
        LpSrcMemInfo = LpDymMemRangeInfo->pMemAddInfo;

        if(LusSourceCount != DCM_ZERO)
        {
          /* Loop to get index of source data Information */
          for(LucLoopVar = DCM_ZERO; LucLoopVar < LusSourceCount;
            LucLoopVar++)
          {
            LpSrcMemInfo = &LpSrcMemInfo[1u];
          }
        }
      
        /* Loop to update source Memory info in Dynamic Defined DID */
        for(LusIDIndex = LusSourceCount; LusIDIndex <
          (uint16)(LusIDCount + LusSourceCount); LusIDIndex++)
        {

          LucLoopVar = DCM_ZERO;

          do
          {
            LulMemAddress = LulMemAddress << DCM_EIGHT;
            LulMemAddress |= LpReqResData[DCM_FOUR + LucDataID + LucLoopVar];
            LucLoopVar++;
          }
          while(LucLoopVar < LucMemAdrBytes);

          LucLoopVar = DCM_ZERO;
          LucDataID = LucDataID + LucMemAdrBytes;

          /*Get memory size from the request*/
          do
          {
            LulMemorySize = LulMemorySize << DCM_EIGHT;
            LulMemorySize |= LpReqResData[DCM_FOUR + LucDataID + LucLoopVar];
            LucLoopVar++;
          }
          while(LucLoopVar < LucMemSizeBytes);

          /* Inedex of next memory address and size */
            LucDataID = LucDataID  + LucMemSizeBytes;


          /* Store Memory Identifier value */
          Dcm_GucRMBAMemoryIdentifier =
            LpReadMemRng->ucReadMemoryIdentifier;

          /* Update Memory address */
          LpSrcMemInfo->ulMemAddrs = LulMemAddress;

          /* Update Memory Size */
          LpSrcMemInfo->ulMemSize = LulMemorySize;

          /* update priority of source */
          LpSrcMemInfo->usPriority = LusIDIndex + DCM_ONE;

          LpSrcMemInfo = &LpSrcMemInfo[1u];
          /* Removed  by YoungJin Yun, 2014-10-17 , logic is duplicated */
          /* Index for next memory address */
          /* LucDataID = LucDataID + (LucMemAdrBytes + LucMemSizeBytes); */

          /* clear Dcm_GddNegRespError */
          Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;

          /* Check for maximum number of source elements for a Dynamic Data ID*/
          if((LpDymDIDInfo->ucSrcIDCount + LpDymMemRangeInfo->ucMemAddressCount) < LucMaxNumOfSourceEle)
          {
            /* update the static ID count */
            LpDymMemRangeInfo->ucMemAddressCount = LpDymMemRangeInfo->ucMemAddressCount + DCM_ONE;
          }
          else
          {
            Dcm_DspClrDynDefinedDID(LusDynDIDIndex, pMsgContext, LucMaxNumOfSourceEle);
            /* Report the Request out of range NRC */
            Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
            
            /* To break loop */
            break;
          }
          LulMemAddress = DCM_ZERO;
          LulMemorySize = DCM_ZERO;

        }
      }
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspValidateDynDID                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x2C   **
**                        to validate for subfunction and IncorrectMessage    **
**                        length.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : LpIDCount, LpDIDIndex                               **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GaaDIDParaConfig,         **
**                        Dcm_GaaAddressAndLengthFormatIds,                   **
**                        Dcm_GddNegRespError                                 **
**                        Function(s) invoked :                               **
**                        Dcm_IDSearch, Dcm_DsdValidateSession,               **
**                        Dcm_DsdValidateSecurity.                            **
**                                                                            **
*******************************************************************************/
#if(DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON)
/*  TODO TODO TODO TODO
 * Do reverse engineering
 */
static FUNC(boolean, DCM_CODE) Dcm_DspValidateDynDID(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpIDCount,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpDIDIndex)
{
  uint32 LulMaxValidLen;
  uint32 LulIdcount;
  uint16 LusDynDIDIdentifier;
  uint16 LusDIDIndex = (uint16)0x00;
  uint8 LucResult = DCM_E_POSITIVERESPONSE;

  boolean LblSearchResult;
  
  DCM_GET_DATAID_FROM_REQUEST(LusDynDIDIdentifier,pMsgContext->reqData, 1U);

  /* Check if the DID from the request is supported */
  LblSearchResult = Dcm_IDSearch(DCM_GET_DID, LusDynDIDIdentifier, &LusDIDIndex);
  if ((LusDIDIndex < Dcm_Num_Of_DidParaConfig) && (LblSearchResult == DCM_TRUE))
  {
    uint32 lenOfMemFmt = 0U;
    uint8 maxSrcElement = 0U;      
 
    if (NULL_PTR != LpDIDIndex)
    {
      *LpDIDIndex = LusDIDIndex;
    }    
    
    if (NULL_PTR != Dcm_GaaDIDParaConfig[LusDIDIndex].pDidInfo)
    {
      if (NULL_PTR != Dcm_GaaDIDParaConfig[LusDIDIndex].pDidInfo->pDidRead)
      {
        maxSrcElement = Dcm_GaaDIDParaConfig[LusDIDIndex].pDidInfo->pDidRead->ucMaxNumSourceElem;
      }
    }

    if (0U == maxSrcElement)
    {
      DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID,DCM_E_PARAM);
      LucResult = DCM_E_REQUESTOUTOFRANGE;
    }
    /**
     * 01 : defineByIdentifier */
    else if (pMsgContext->reqData[DCM_ZERO] == DCM_ONE) 
    {
      LulIdcount = ((pMsgContext->reqDataLen - DCM_THREE) / (DCM_FOUR));
      if (LulIdcount > maxSrcElement)
      {
        LucResult = DCM_E_REQUESTOUTOFRANGE;
      }
      else
      {    
        /* Validate for the Maximum length in the request
         * 4-> max x [ DID(2) + pos(1) + size(1) ] + DDDID(2)+subf(1) */
        LulMaxValidLen = (uint32)(((uint32)maxSrcElement) * (uint32)0x04) + (uint32)0x03;
        if 
        ( (pMsgContext->reqDataLen > LulMaxValidLen) || 
          (pMsgContext->reqDataLen == (uint32)0x00) ||
          (((pMsgContext->reqDataLen - (uint32)0x03) % ((uint32)0x04)) != (uint32)0x00) )      
        {
          LucResult = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
        else if (NULL_PTR != LpIDCount)
        {
          *LpIDCount = (uint16)LulIdcount;
        } 
        else
        {
          /* Do nothing */
        }
        
      }
    }
    /**
     * 02 : defineByMemoryAddress */
    else if(pMsgContext->reqData[DCM_ZERO] == DCM_TWO)
    {
      uint8 LucMemSizeBytes;    
      uint8 LucMemAdrBytes;      
      
      /* Get memory address and size bytes from requested
        Address and length format identifier */
      LucMemAdrBytes = (pMsgContext->reqData[DCM_THREE] & DCM_SIG_BYTE_MASK_VALUE);      
      LucMemSizeBytes = (uint8)((pMsgContext->reqData[DCM_THREE] & DCM_SIG_SIZE_MASK_VALUE) >> 4U);      

      lenOfMemFmt = (uint32)LucMemAdrBytes + (uint32)LucMemSizeBytes;                  
      LulMaxValidLen = ((uint32)maxSrcElement * lenOfMemFmt) + ((uint32)0x04);   
      
      if (0U == lenOfMemFmt)
      {
        LucResult = DCM_E_REQUESTOUTOFRANGE;
      }          
      else
      {
        LulIdcount = (pMsgContext->reqDataLen - (uint32)0x04) / lenOfMemFmt;                    
        if (LulIdcount > maxSrcElement)
        {
          LucResult = DCM_E_REQUESTOUTOFRANGE;
        }         
        else if ((pMsgContext->reqDataLen > LulMaxValidLen) || (pMsgContext->reqDataLen == DCM_ZERO))
        {
          LucResult = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
        else if (((pMsgContext->reqDataLen - (uint32)DCM_SIZEOF_DDID_ALF) % lenOfMemFmt) != (uint32)0U)
        {
          LucResult = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
        else
        {
          boolean LddAddrLenForIdSupported = DCM_FALSE;        
          uint8 LucLoopVar;
          
          /* Check for configured Address and length format identifier */
          for(LucLoopVar = DCM_ZERO;
              LucLoopVar < Dcm_Num_Of_Address_Length_Format_ID_Config; LucLoopVar++)
          {
            if(pMsgContext->reqData[DCM_THREE] == Dcm_GaaAddressAndLengthFormatIds[LucLoopVar])
            {
              LddAddrLenForIdSupported = DCM_TRUE;
            }
          }            
          if (LddAddrLenForIdSupported == DCM_FALSE)
          {
            LucResult = DCM_E_REQUESTOUTOFRANGE;          
          }
          else if (NULL_PTR != LpIDCount)
          {
            *LpIDCount = (uint16)LulIdcount;
          }
          else
          {
            /* Do nothing */
          } 
        }
      }
    }
    /**
     * 03: clearDynamicallyDefinedDataIdentifier */
    else  if (pMsgContext->reqData[DCM_ZERO] == DCM_THREE)
    {
      if  ((pMsgContext->reqDataLen == DCM_ZERO) || (((pMsgContext->reqDataLen - 1U) % 2U) != 0U))
      {
        /* Report the incorrect message length NRC */
        LucResult = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
      }
    }
    else
    {
      /* Requested Subfunction is not supported */
      LucResult = DCM_E_SUBFUNCTIONNOTSUPPORTED;  
    }

    if (DCM_E_POSITIVERESPONSE != LucResult)
    {
      LblSearchResult = DCM_FALSE; 
    }
    else
    {
      LblSearchResult = DCM_TRUE;      
      if(Dcm_GaaDIDParaConfig[LusDIDIndex].pDidInfo->pDidRead->pDidReadSession != NULL_PTR)
      {
        /* Invoke Internal function to validate for session of Dynamic DID */
        LblSearchResult = 
          Dcm_DsdValidateSession(
            Dcm_GaaDIDParaConfig[LusDIDIndex].pDidInfo->pDidRead->pDidReadSession,
            Dcm_GaaDIDParaConfig[LusDIDIndex].pDidInfo->pDidRead->ucDidReadSesCount);
      }
      
      if(LblSearchResult != DCM_TRUE)
      {
        LucResult = DCM_E_REQUESTOUTOFRANGE;
      }
      else
      {
        if(Dcm_GaaDIDParaConfig[LusDIDIndex].pDidInfo->pDidRead->pDidReadSecurity != NULL_PTR)
        {
          /* Invoke Internal function to validate
           for security of Dynamic DID */
          LblSearchResult = Dcm_DsdValidateSecurity
              (Dcm_GaaDIDParaConfig[LusDIDIndex].pDidInfo->pDidRead->pDidReadSecurity, 
               Dcm_GaaDIDParaConfig[LusDIDIndex].pDidInfo->pDidRead->ucDidReadSecCount);
        }
      
        if(LblSearchResult != DCM_TRUE)
        {
          /* Report the SecurityAccessDenied NRC */
          LucResult = DCM_E_SECURITYACCESSDENIED;
        }
      }  
    }
  }
  else
  {
    /* Report the Request out of range NRC */
    LucResult = DCM_E_REQUESTOUTOFRANGE;
    LblSearchResult = DCM_FALSE; 
  }
  
  /* Update result */
  Dcm_GddNegRespError = LucResult;
  
  return LblSearchResult;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspClrDynDefinedDID                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x2C   **
**                        with subfunction 03 to clear dynamically defined DID**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusDynDIDIndex, Luc_TotalSourceElem                 **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GaaDymDefinedDIDInfoType  **
**                        Dcm_GaaDymMemDIDInfoType, Dcm_GddNegRespError       **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if(DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON)
static FUNC(void, DCM_CODE) Dcm_DspClrDynDefinedDID(
  uint16 LusDynDIDIndex,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint8 Luc_TotalSourceElem)
{
  uint32 LulTotReqLen;
  uint8 LucIndex;

  /* Get the total request length from the request */
  LulTotReqLen = pMsgContext->reqDataLen;

  if(LulTotReqLen == DCM_ONE)
  {
    for(LusDynDIDIndex = DCM_ZERO; LusDynDIDIndex < Dcm_Total_Num_Of_Dym_DID;
        LusDynDIDIndex++)
    {
      /* Do it for Clear Dynamic ID */
      if(Dcm_GaaDymDefinedDIDInfoType[LusDynDIDIndex].blDidSet == DCM_TRUE)
      {
        for(LucIndex = DCM_ZERO; LucIndex < Luc_TotalSourceElem; LucIndex++)
        {
          /* clear the source ID */
          Dcm_GaaDymDefinedDIDInfoType[LusDynDIDIndex].pSrcIDInfo[LucIndex].usSrcID = DCM_ZERO;
          /* clear the Position in source data record */
          Dcm_GaaDymDefinedDIDInfoType[LusDynDIDIndex].pSrcIDInfo[LucIndex].ucPosInSrc = DCM_ZERO;
          /* clear the Memory size */
          Dcm_GaaDymDefinedDIDInfoType[LusDynDIDIndex].pSrcIDInfo[LucIndex].ucMemSize = DCM_ZERO;
        }
        
        Dcm_GaaDymDefinedDIDInfoType[LusDynDIDIndex].blDidSet = DCM_FALSE;
        Dcm_GaaDymDefinedDIDInfoType[LusDynDIDIndex].ucSrcIDCount = DCM_ZERO;

        /* No NRC was reported */
        Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
      }
      
      if(Dcm_GaaDymMemDIDInfoType[LusDynDIDIndex].blMemAddSet == DCM_TRUE)
      {
        for(LucIndex = DCM_ZERO; LucIndex < Luc_TotalSourceElem; LucIndex++)
        {
          /* Clear Memory address */
          Dcm_GaaDymMemDIDInfoType[LusDynDIDIndex].pMemAddInfo[LucIndex].ulMemAddrs = DCM_ZERO;
          /* Clear Memory Size */
          Dcm_GaaDymMemDIDInfoType[LusDynDIDIndex].pMemAddInfo[LucIndex].ulMemSize = DCM_ZERO;
        }

        Dcm_GaaDymMemDIDInfoType[LusDynDIDIndex].blMemAddSet = DCM_FALSE;

        /* Clear the Address range count from request */
        Dcm_GaaDymMemDIDInfoType[LusDynDIDIndex].ucMemAddressCount = DCM_ZERO;

        /* No NRC was reported */
        Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
      }
    }
  }
  else
  {
    if(LusDynDIDIndex >= Dcm_Total_Num_Of_Dym_DID)
    {
      /* For Misra-C check */
      Dcm_GddNegRespError = DCM_E_GENERALREJECT;    
    }
    else
    {
      if((Dcm_GaaDymDefinedDIDInfoType[LusDynDIDIndex].blDidSet == DCM_FALSE) &&
          (Dcm_GaaDymMemDIDInfoType[LusDynDIDIndex].blMemAddSet == DCM_FALSE))
      {
        /* Report the NRC */
        Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
      }
      else
      {
        /* Do it for Clear Dynamic ID */
        if(Dcm_GaaDymDefinedDIDInfoType[LusDynDIDIndex].blDidSet == DCM_TRUE)
        {
          for(LucIndex = DCM_ZERO; LucIndex < Luc_TotalSourceElem; LucIndex++)
          {
            /* clear the source ID */
            Dcm_GaaDymDefinedDIDInfoType[LusDynDIDIndex].pSrcIDInfo[LucIndex].usSrcID = DCM_ZERO;
  
            /* clear the Position in source data record */
            Dcm_GaaDymDefinedDIDInfoType[LusDynDIDIndex].pSrcIDInfo[LucIndex].ucPosInSrc = DCM_ZERO;
  
            /* clear the Memory size */
            Dcm_GaaDymDefinedDIDInfoType[LusDynDIDIndex].pSrcIDInfo[LucIndex].ucMemSize = DCM_ZERO;
          }
          
          Dcm_GaaDymDefinedDIDInfoType[LusDynDIDIndex].blDidSet = DCM_FALSE;
          Dcm_GaaDymDefinedDIDInfoType[LusDynDIDIndex].ucSrcIDCount = DCM_ZERO;
  
          /* No NRC was reported */
          Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
        }
        
        if(Dcm_GaaDymMemDIDInfoType[LusDynDIDIndex].blMemAddSet == DCM_TRUE)
        {
          for(LucIndex = DCM_ZERO; LucIndex < Luc_TotalSourceElem; LucIndex++)
          {
            /* Clear Memory address */
            Dcm_GaaDymMemDIDInfoType[LusDynDIDIndex].pMemAddInfo[LucIndex].ulMemAddrs = DCM_ZERO;
            /* Clear Memory Size */
            Dcm_GaaDymMemDIDInfoType[LusDynDIDIndex].pMemAddInfo[LucIndex].ulMemSize = DCM_ZERO;
          }
  
          Dcm_GaaDymMemDIDInfoType[LusDynDIDIndex].blMemAddSet = DCM_FALSE;
  
          /* Clear the Address range count from request */
          Dcm_GaaDymMemDIDInfoType[LusDynDIDIndex].ucMemAddressCount = DCM_ZERO;
  
          /* No NRC was reported */
          Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
        }
      }
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmECUResetService                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This ECUReset service is used to enable external    **
**                        tester to request a server reset.                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GucSubFunValue,           **
**                        Dcm_GucECUResPorCnt, Dcm_GddNegRespError,           **
**                                           Dcm_GaaSubServiceIdConfig,       **
**                        Function(s) invoked : Dcm_ExternalSetNegResponse,   **
**                        Dcm_ExternalProcessingDone, Dcm_DspECUReset,        **
**                        Dcm_GetSesCtrlType,                                 **
**                                                                            **
*******************************************************************************/
#if(DCM_ECURESET_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmECUResetService(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2CONST(Dcm_SubServiceIdConfigType, AUTOMATIC, DCM_APPL_CONST) subServiceCfg;
  Std_ReturnType requestResult = E_OK;  

  subServiceCfg = Dcm_DsdInternal_GetSubFunctionByMsgContext(pMsgContext);    
  if(NULL_PTR == subServiceCfg)
  { 
    /* Never be reached, but this code is added for MISRA-rules */  
    Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
  }
  /* External diagnostic subservice processing  */
  else if(NULL_PTR != subServiceCfg->pSubServiceFnc)
  {
    if ( (DCM_INITIAL == OpStatus) && (pMsgContext->reqDataLen > 0U))
    {
      /* @SWS_Dcm_00764 The pointer in pMsgContext shall point behind the SubFunction */  
      pMsgContext->reqData = &pMsgContext->reqData[1U];
      pMsgContext->reqDataLen--;
    }
    requestResult = subServiceCfg->pSubServiceFnc(OpStatus, pMsgContext);
  }
  /* Dcm-Internal diagnostic subservice processing  */  
  else
  {
    if (pMsgContext->reqDataLen != 1U)
    {
      Dcm_InternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    else
    {
      uint8 subFunctionId = subServiceCfg->ucSubServiceId;

      /* in case ES95590 , SchM_Switch_Dcm_DcmModeRapidPowerShutDown may be not configured */
      #if ((DCM_STANDARD_SUPPORT != DCM_ES96590_SUPPORT) && (DCM_STANDARD_SUPPORT != DCM_QZN04_SUPPORT))
      if(subFunctionId == DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET)
      {
        (void)SchM_Switch_Dcm_DcmModeRapidPowerShutDown(ENABLE_RAPIDPOWERSHUTDOWN);
        
        pMsgContext->resDataLen = 2U;
        pMsgContext->resData[0U] = subFunctionId;
        /* update the power down time , this variable can be configurable */
        pMsgContext->resData[1U] = Dcm_PowerDown_Time;
      }
      else if(subFunctionId == DCM_DISABLE_RAPID_POWER_SHUTDOWN_RESET)
      {
        (void)SchM_Switch_Dcm_DcmModeRapidPowerShutDown(DISABLE_RAPIDPOWERSHUTDOWN);

        pMsgContext->resDataLen = 1U;
        pMsgContext->resData[0U] = subFunctionId;
      }
      else
      #endif
      {
        (void)SchM_Switch_Dcm_DcmEcuReset(subFunctionId);

        pMsgContext->resDataLen = 1U;
        pMsgContext->resData[0U] = subFunctionId;

        /* Fixed by sg.baek */
        /* Dcm_GblExecuteECUReset = DCM_TRUE; */
      }
    }
    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
  }  
  
  return requestResult;  
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmCommunicationControl                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function used to control the Communication     **
**                        mode.                                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None.                                               **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_GucSubNetValue, Dcm_GucCommunicationModeType,   **
**                        Dcm_GaaCommControlConfig,                           **
**                        Dcm_GddNegRespError.                                **
**                        Function(s) invoked : Dcm_ExternalSetNegResponse,   **
**                        Dcm_ExternalProcessingDone                          **
**                                                                            **
*******************************************************************************/
#if(DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmCommunicationControl(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2CONST(Dcm_SubServiceIdConfigType, AUTOMATIC, DCM_APPL_CONST) subServiceCfg;
  Std_ReturnType requestResult = E_OK;  

  /*****************************************************************************
   *                            ES95486 Specification                          *
   ****************************************************************************/
  #if(DCM_STANDARD_SUPPORT == DCM_ES95486_SUPPORT)
  /* 00 enableRxAndTx, 01 diableNormalMessageTransmission (resp), 02 diableNormalMessageTransmission (noResp), 03 disableRxAndTx */  
  uint8 subRequestLength[DCM_LOCAL_NUM_OF_SUBREQ] = {2,1,1,2}; 
  /* 00: undefined, 01: normal, 02: nm, 03: nm and normal */
  uint8 supportedCommunicationType[DCM_LOCAL_NUM_OF_COMTYPE] = { DCM_FALSE, DCM_TRUE, DCM_TRUE, DCM_TRUE};  
  /* subnet number's range */
  struct {uint8 minSubNet; uint8 maxSubNet;} subNetRange = {0,0};

  /*****************************************************************************
   *                            ES96590 Specification                          *
   ****************************************************************************/
  #elif ((DCM_STANDARD_SUPPORT == DCM_ES96590_SUPPORT) || (DCM_STANDARD_SUPPORT == DCM_QZN04_SUPPORT))
  /* 00 enableRxAndTx , 01 enableRxAndDisable , 02 disableRxAndEnable, 03 disableRxAndTx */
  uint8 subRequestLength[DCM_LOCAL_NUM_OF_SUBREQ] = {2,2,2,2}; 
  /* 00: undefined, 01: normal, 02: nm, 03: nm and normal */
  uint8 supportedCommunicationType[DCM_LOCAL_NUM_OF_COMTYPE] = { DCM_FALSE, DCM_TRUE, DCM_TRUE, DCM_TRUE};  
  /* subnet number's range */
  struct {uint8 minSubNet; uint8 maxSubNet;} subNetRange = {0,0};

  /*****************************************************************************
   *                            AUTOSAR Specification                          *
   ****************************************************************************/  
  #else
  /* 00 enableRxAndTx , 01 enableRxAndDisable , 02 disableRxAndEnable, 03 disableRxAndTx */
  uint8 subRequestLength[DCM_LOCAL_NUM_OF_SUBREQ] = {2,2,2,2}; 
  /* 00: undefined, 01: normal, 02: nm, 03: nm and normal */
  uint8 supportedCommunicationType[DCM_LOCAL_NUM_OF_COMTYPE] = { DCM_FALSE, DCM_TRUE, DCM_TRUE, DCM_TRUE};  
  /* subnet number's range */
  struct {uint8 minSubNet; uint8 maxSubNet;} subNetRange = {0x0,0x0F};  
  #endif
  
  subServiceCfg = Dcm_DsdInternal_GetSubFunctionByMsgContext(pMsgContext);    
  if(NULL_PTR == subServiceCfg)
  { 
    /* Never be reached, but this code is added for MISRA-rules */  
    Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
    Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
  }
  /* External diagnostic subservice processing  */
  else if(NULL_PTR != subServiceCfg->pSubServiceFnc)
  {
    if ( (DCM_INITIAL == OpStatus) && (pMsgContext->reqDataLen > 0U))
    {
      /* @SWS_Dcm_00764 The pointer in pMsgContext shall point behind the SubFunction */  
      pMsgContext->reqData = &pMsgContext->reqData[1U];
      pMsgContext->reqDataLen--;
    }
    requestResult = subServiceCfg->pSubServiceFnc(OpStatus, pMsgContext);
  }
  else
  {
    /* Dcm-internal timeout handling */
    if (subServiceCfg->ucSubServiceId >= DCM_LOCAL_NUM_OF_SUBREQ) 
    {
      /* Never be reached, but this code is added for MISRA-rules */
      Dcm_InternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
    } 
    else if (subRequestLength[subServiceCfg->ucSubServiceId] != pMsgContext->reqDataLen)
    {
      Dcm_InternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    else
    {
      Dcm_GucSubFunction = subServiceCfg->ucSubServiceId;
      if (2U == subRequestLength[subServiceCfg->ucSubServiceId])
      {
        Dcm_GucSubNetValue = (uint8)(((pMsgContext->reqData[1U]) & DCM_SIG_SIZE_MASK_VALUE) >> 0x04u);
        Dcm_GucCommunicationModeType = ((pMsgContext->reqData[1U]) & DCM_SIG_BYTE_MASK_VALUE);
      }
      else
      {
        /* length may be 1, and therefore  pMsgContext->reqData[1U] is not defined(ES95486) */
        Dcm_GucSubNetValue = 0U;
        Dcm_GucCommunicationModeType = DCM_COMM_TYPE_NORMAL;
      }

      if ( /* range and supported sub function check */
        (Dcm_GucCommunicationModeType >= DCM_LOCAL_NUM_OF_COMTYPE) || 
        (DCM_FALSE == supportedCommunicationType[Dcm_GucCommunicationModeType]))
      {
        Dcm_InternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
      }
      else if(
        (Dcm_GucSubNetValue < subNetRange.minSubNet) ||
        (Dcm_GucSubNetValue > subNetRange.maxSubNet))
      {
        Dcm_InternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
      }
      else
      {
        boolean searchResult = DCM_FALSE;
        /* [ES95486 Annex. B], @SWS_Dcm_00512, @SWS_Dcm_00785 */
        if ((0x0F == Dcm_GucSubNetValue) || (0U == Dcm_GucSubNetValue))
        {        
          searchResult = DCM_TRUE;
        }
        else
        {
          /* [SWS_Dcm_00786]  ...the subnet parameter of the request between 0x01 and  0x0E.. */
          uint8 channelIdx;          
          for(channelIdx = 0U; channelIdx < Dcm_Total_Num_Of_Specific_Channel; channelIdx++)
          {
            if(Dcm_GaaCommControlConfig[channelIdx].ucSubNetNumber == Dcm_GucSubNetValue)
            {
              searchResult = DCM_TRUE;
              break;
            }
          }
        }
        
        if(searchResult == DCM_TRUE)
        {
          pMsgContext->resDataLen = 1U;
          pMsgContext->resData[0U] = pMsgContext->reqData[0U]; /* sub function number */
        }
        else
        {
          Dcm_InternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);    
        }
      }   
    }
    Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);    
  }
  /* TODO: return value shall be processed */
  return requestResult;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmWriteDataByIdentifier                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This WriteDataByIdentifier service is used to write **
**                        the DID and the the dataRecord which has the data   **
**                        to be written                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GaaDIDParaConfig,         **
**                        Dcm_GusMaxNoOfRespPend, Dcm_GusDataIdentifier,      **
**                        Dcm_GddNegRespError, Dcm_ExternalProcessingDone,    **
**                        Dcm_ServicePendingStatus, Dcm_GddOpStatus,          **
**                        Dcm_GusDIDIndexVal, Dcm_GblDIDRangePresent.         **
**                        Function(s) invoked : Dcm_DspDIDSearch,             **
**                        Dcm_DspValidateWriteDID, Dcm_DspWriteDidRangeData,  **
**                        Dcm_DcmWriteDataByIdentifierCall,                   **
**                        Dcm_ExternalSetNegResponse.                         **
**                                                                            **
*******************************************************************************/
#if(DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmWriteDataByIdentifier(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2VAR(Dcm_DIDRangeConfig, AUTOMATIC, DCM_APPL_DATA)pDIDRangeConfig = NULL_PTR;
  Dcm_NegativeResponseCodeType errorCode;
  uint16 dataIdentifier = 0;
  uint16 didIndex = 0U;
  
  boolean searchResult = DCM_FALSE;
  boolean didRangePresent = DCM_FALSE;

  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  Dcm_GddOpStatus = DCM_INITIAL;
  Dcm_GusMaxNoOfRespPend = 0U;
  
  /* Update Identifier from the request buffer */  
  DCM_GET_DATAID_FROM_REQUEST(dataIdentifier, pMsgContext->reqData, 0U);
  
  /* Check if the DID from the request is supported */
  searchResult = Dcm_DspDIDSearch(dataIdentifier, &didIndex, &didRangePresent);  
  Dcm_GusDataIdentifier = dataIdentifier;
  
  if(DCM_TRUE == searchResult)
  {
    /* Validate the session, security and mode rule configured for DID */
    errorCode = Dcm_DspValidateWriteDID(didIndex, didRangePresent);
    if(errorCode == DCM_E_POSITIVERESPONSE)
    {
      uint16 minDidLength = 0u;
      uint16 maxDidLength = 0u;    
      
      if((DCM_ZERO != Dcm_Num_Of_DcmDspDidRangeConfig) &&
                                                  (DCM_TRUE == didRangePresent))
      {
        pDIDRangeConfig = Dcm_CfgInternal_GetDIDRangeConfig(didIndex);

        /* DidRange is not configured */
        if(NULL_PTR == pDIDRangeConfig)
        {
          /* For Misra-C check */
          Dcm_GddNegRespError = DCM_E_GENERALREJECT;
        }
        else
        {
          maxDidLength = pDIDRangeConfig->usDidRangeMaxDataLength;
        }
      }
      else
      {
        if(didIndex >= Dcm_Num_Of_DidParaConfig)
        {
          /* For Misra-C check */
          Dcm_GddNegRespError = DCM_E_GENERALREJECT;
        }
        else
        {          
          Dcm_DspInternal_GetSizeOfDid(&Dcm_GaaDIDParaConfig[didIndex],
                                                  &minDidLength, &maxDidLength);    
          minDidLength = (minDidLength + 7U) / 8U;
          maxDidLength = (maxDidLength + 7U) / 8U;
        }
      }

      if(DCM_E_POSITIVERESPONSE == Dcm_GddNegRespError)
      {
        /* min <= length <= max , 2U = size of DataIdentifier */
        if((pMsgContext->reqDataLen < (Dcm_MsgLenType)((uint32)2U + (uint32)minDidLength)) ||
           (pMsgContext->reqDataLen > (Dcm_MsgLenType)((uint32)2U + (uint32)maxDidLength)))
        {
          /* Report the Incorrect Message Length NRC */
          Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
      }
    }
    else
    {
      /* Update Negative responsecode */
      Dcm_GddNegRespError = errorCode;
    }

    if(DCM_E_POSITIVERESPONSE == Dcm_GddNegRespError)
    {
      if((DCM_ZERO != Dcm_Num_Of_DcmDspDidRangeConfig) &&
                                                  (DCM_TRUE == didRangePresent))
      {
        Dcm_DspWriteDidRangeData(pMsgContext, dataIdentifier, didIndex);
      }
      else
      {
        /* Invoke Writedata By Id internal function */
        Dcm_DcmWriteDataByIdentifierCall(pMsgContext, didIndex);
      }
    }
  }
  else
  {
    /* Report the Request out of range NRC */
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
  }
  
  if(DCM_FALSE == Dcm_ServicePendingStatus.ucWriteDataByIdPendingStatus)
  {
    /* Check if the negative response needs to be updated here */
    if(DCM_E_POSITIVERESPONSE == Dcm_GddNegRespError)
    {
      Dcm_ResetWriteDIDOpStatus();

      Dcm_GddOpStatus = DCM_INITIAL;

      /* Response message length is Calculated */
      pMsgContext->resDataLen = 2U;

      /* Update First Byte DID */
      pMsgContext->resData[0U] = pMsgContext->reqData[0U];

      /* Update Second Byte DID */
      pMsgContext->resData[1U] = pMsgContext->reqData[1U];
    }
    
    if(DCM_E_POSITIVERESPONSE != Dcm_GddNegRespError)
    {
      Dcm_InternalSetNegResponse(pMsgContext, Dcm_GddNegRespError);
    }
    Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
  }
  else
  {
    Dcm_GusDIDIndexVal = didIndex;
    Dcm_GblDIDRangePresent = didRangePresent;
  }

  DCM_UNUSED(OpStatus);
  /* TODO: return value shall be processed */
  return E_OK;  
}

/*******************************************************************************
** Function Name        : Dcm_DcmWriteDataByIdentifierCall                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x2E   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusDIDIndex                                         **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DcmWriteDataByIdentifierCall(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint16 LusDIDIndex)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST)LpDcmDspData;
  P2CONST(Dcm_DIDUnPackSignal, AUTOMATIC, DCM_APPL_CONST)LpUnpackSignalConfig;
  Dcm_PackUnpackSignalData LddUnPackSignal;
  Dcm_NegativeResponseCodeType LddNegativeErrorCode;
  uint32 LulReqDataLen;
  uint8 LucSignalCount;
  uint8 LucSignalIndex;
  uint8 LucByteCount;
  uint8 LucSignalType;

    
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  LddNegativeErrorCode = DCM_E_POSITIVERESPONSE;

  /* Set response pending flag to False */
  Dcm_ServicePendingStatus.ucWriteDataByIdPendingStatus = DCM_FALSE;

  #if (DCM_DEV_ERROR_DETECT == STD_ON)
  if 
  (
    (NULL_PTR == pMsgContext) ||
    (LusDIDIndex >= Dcm_Num_Of_DidParaConfig)
  )
  {
    /* For Misra-C check */
	Dcm_GddNegRespError = DCM_E_GENERALREJECT;
  }
  else
  #endif
  {
    /* Get the request length from pMsgContext */
    LulReqDataLen = pMsgContext->reqDataLen - 2U;
    LucSignalCount = Dcm_GaaDIDParaConfig[LusDIDIndex].ucDcmDspSignalCount;
    LucByteCount = 0U;
    LucSignalIndex = 0U; 

    if ((0U == LucSignalCount) || (NULL_PTR == Dcm_GaaDIDParaConfig[LusDIDIndex].pDcmDspSignal))
    {
	  Dcm_GddNegRespError = DCM_E_GENERALREJECT;
    }
    else
    {    
      while (LucSignalIndex < LucSignalCount)
      {
        /*Get the configuration of Data's*/
        LpDcmDspData = 
          Dcm_GaaDIDParaConfig[LusDIDIndex].pDcmDspSignal[LucSignalIndex].pDcmDspData;

        /* Check if requested signal data is already read or not and if not
          then read the data */
        if(Dcm_GaaDIDParaConfig[LusDIDIndex].pDcmDspSignal[LucSignalIndex].ucDidSignalOpStatus 
            != DCM_OPSTATUS_COMPLETE)
        {
          Std_ReturnType LddReturnValue = E_NOT_OK;
            
          LpUnpackSignalConfig = 
            Dcm_GaaDIDParaConfig[LusDIDIndex].pDcmDspSignal[LucSignalIndex].pDidUnPackSignal;

          if((NULL_PTR != LpUnpackSignalConfig) && (NULL_PTR != LpDcmDspData))
          {  
            LucSignalType = LpUnpackSignalConfig->ucSignalType;
            LddUnPackSignal.ucShiftBits = LpUnpackSignalConfig->ucNoOfShiftBits;
            LddUnPackSignal.ucEndMask = LpUnpackSignalConfig->ucEndMask;
            LddUnPackSignal.ucSignalType = LucSignalType;
            LddUnPackSignal.ucSignalSize = LpUnpackSignalConfig->ucSignalSize;
            LddUnPackSignal.ucSignMask = LpUnpackSignalConfig->ucSignMask;
            /* for initialization */
            LddUnPackSignal.ucStartMask = (uint8)0x00;
  
            LddUnPackSignal.ucSignalTypeorSize = (uint8)0x00;
  
            LddUnPackSignal.ulSignalLength = (uint32)0x00;
            if(LucSignalType == DCM_FIVE)
            {
              LddUnPackSignal.ulSignalLength = LpUnpackSignalConfig->ulSignalLength;
            }
  
            Dcm_GpDIDSignalDataPtr = (P2VAR(void, AUTOMATIC, DCM_APPL_DATA))&Dcm_GaaDIDSignalData[LucByteCount];
  
            LpReqResData = &pMsgContext->reqData[2U + LpUnpackSignalConfig->ucSignalStartByte];
  
            if (
              (LpUnpackSignalConfig->ucRdFuncIndex >= Dcm_Num_Of_SigRdFuncPtr) ||
              (NULL_PTR == Dcm_GaaSigRdFuncPtr[LpUnpackSignalConfig->ucRdFuncIndex].pRdFuncPtr)
            )
            {
              /* For Misra-C check */
              LddReturnValue = E_NOT_OK;
              LddNegativeErrorCode = DCM_E_GENERALREJECT;
            }
            else
            { 
              /* Call the function Unpack Function */
              Dcm_GaaSigRdFuncPtr[LpUnpackSignalConfig->ucRdFuncIndex].pRdFuncPtr
                  (LddUnPackSignal, LpReqResData, Dcm_GpDIDSignalDataPtr);       
                  
              LucByteCount += LucSignalType;
              
              switch(LpDcmDspData->ucDcmDspDataUsePort)
              {
                case DCM_USEBLOCKID:      
                  LddReturnValue = Dcm_DspInternal_WriteSigTypeNvMBlock(
                    Dcm_GddOpStatus, LpDcmDspData, Dcm_GpDIDSignalDataPtr, &LddNegativeErrorCode);
                  break;
  
                case DCM_USE_DATA_ASYNCH_CLIENT_SERVER:
                case DCM_USE_DATA_ASYNCH_FNC:
                  if(LpDcmDspData->pWriteDataFixedAsync != NULL_PTR)
                  {             
                    LddReturnValue = LpDcmDspData->pWriteDataFixedAsync(
                      Dcm_GpDIDSignalDataPtr,Dcm_GddOpStatus, &LddNegativeErrorCode);
                  }
                  else if(LpDcmDspData->pWriteDataVarAsync != NULL_PTR)
                  {
                    /* size of reqeusted variable signal is the rest of all fixed signal */
                    uint16 dataLength = 
                      (uint16)(LulReqDataLen - Dcm_GaaDIDParaConfig[LusDIDIndex].pDcmDspSignal[LucSignalIndex].usDcmDspDidDataPos);
  
                    LddReturnValue = LpDcmDspData->pWriteDataVarAsync(
                      Dcm_GpDIDSignalDataPtr, dataLength, Dcm_GddOpStatus, &LddNegativeErrorCode);
                  }
                  else
                  { /* TODO : Det Error */ 
                  }
                  
                  break;
                case DCM_USE_DATA_SYNCH_CLIENT_SERVER:
                case DCM_USE_DATA_SYNCH_FNC:
                  if(LpDcmDspData->pWriteDataFixedSync != NULL_PTR)
                  {             
                    LddReturnValue = LpDcmDspData->pWriteDataFixedSync(
                      Dcm_GpDIDSignalDataPtr, &LddNegativeErrorCode);
                  }
                  else if(LpDcmDspData->pWriteDataVarSync != NULL_PTR)
                  {
                    /* size of reqeusted variable signal is the rest of all fixed signal */
                    uint16 dataLength = 
                      (uint16)(LulReqDataLen - Dcm_GaaDIDParaConfig[LusDIDIndex].pDcmDspSignal[LucSignalIndex].usDcmDspDidDataPos);
                    
                    LddReturnValue = LpDcmDspData->pWriteDataVarSync(
                      Dcm_GpDIDSignalDataPtr, dataLength, &LddNegativeErrorCode);
                  }
                  else 
                  { /* TODO : Det Error */ 
                  }
                  break;
                  
                case DCM_USE_DATA_SENDER_RECEIVER:
                  LddReturnValue = Dcm_CfgInternal_WriteSigTypeSenderReceiver
                    (LpDcmDspData, Dcm_GpDIDSignalDataPtr, &LddNegativeErrorCode);          
                  break;
  
                default:
                  /* Do Nothing */
                  break;
              }
            }
            
            if(Dcm_GddOpStatus != DCM_CANCEL)
            {        
              if(LddReturnValue == E_OK)
              {
                Dcm_GaaDIDParaConfig[LusDIDIndex].pDcmDspSignal[LucSignalIndex].ucDidSignalOpStatus = 
                  DCM_OPSTATUS_COMPLETE;
              }
              else if (
                (LddReturnValue == DCM_E_PENDING) &&
                (
                  (DCM_USE_DATA_ASYNCH_CLIENT_SERVER == LpDcmDspData->ucDcmDspDataUsePort) ||
                  (DCM_USE_DATA_ASYNCH_FNC == LpDcmDspData->ucDcmDspDataUsePort) ||
                  (DCM_USEBLOCKID == LpDcmDspData->ucDcmDspDataUsePort)
                )
              )
              {
                Dcm_GddOpStatus = DCM_PENDING;
                Dcm_GaaDIDParaConfig[LusDIDIndex].pDcmDspSignal[LucSignalIndex].ucDidSignalOpStatus = 
                  DCM_OPSTATUS_PENDING;
                Dcm_ServicePendingStatus.ucWriteDataByIdPendingStatus = DCM_TRUE;
              }
              else /* E_NOT_OK */
              {
                if (LddNegativeErrorCode == DCM_E_POSITIVERESPONSE)
                {
                  LddNegativeErrorCode = DCM_E_CONDITIONSNOTCORRECT;          
                }          
                Dcm_GddNegRespError = LddNegativeErrorCode;
              }
            }
            else
            {
              /* Reset OpStatus */
              Dcm_GddOpStatus = DCM_INITIAL;
            }
          }
          else
          {
            /* Fail-safety */
          }
        }
        LucSignalIndex++;/* next signal */        
      }      
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_DspValidateWriteDID                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x22   **
**                        to validate session and security for the DID        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusDIDIndex, LblDIDRangePresent                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GddNegRespError,          **
**                        Dcm_GaaDIDParaConfig, Dcm_GaaModeRuleConfig.        **
**                        Function(s) invoked : Dcm_DsdValidateSession,       **
**                        Dcm_DsdValidateSecurity, Dcm_DsdModeRuleCheck,      **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspValidateWriteDID(
  uint16 LusDIDIndex, boolean LblDIDRangePresent)
{
  Std_ReturnType result = E_NOT_OK;
  
  P2CONST(Dcm_DIDInfoType, AUTOMATIC, DCM_APPL_CONST)LpDidInfo = NULL_PTR;
  P2CONST(Dcm_DIDInfoTypeDidWrite, AUTOMATIC, DCM_APPL_CONST)LpDidWrite = NULL_PTR;  

  #if((DCM_MODE_RULE == STD_ON) && (DCM_DSP_MODE_RULE_NRC == STD_ON))
  P2CONST(Dcm_ModeRuleConfigType, AUTOMATIC, DCM_APPL_CONST)LpModeRule = NULL_PTR;
  #endif

  Dcm_NegativeResponseCodeType LddResult;
  boolean LblSearchResult = DCM_FALSE;

  result = Dcm_DspInternal_GetDidInfo(LusDIDIndex, LblDIDRangePresent, &LpDidInfo);

  if ((E_OK == result) && (NULL_PTR != LpDidInfo))
  {
    if(LpDidInfo->pDidWrite != NULL_PTR)
    {
      LpDidWrite = LpDidInfo->pDidWrite;
      if(LpDidWrite->pDidWriteSession != NULL_PTR)
      {
        /* Check DID has valid session configured */
        LblSearchResult = Dcm_DsdValidateSession(LpDidWrite->pDidWriteSession,
            LpDidWrite->ucDidWriteSesCount);
      }
      else
      {
        LblSearchResult = DCM_TRUE;
      }

      if(LblSearchResult == DCM_TRUE)
      {
        if(LpDidWrite->pDidWriteSecurity != NULL_PTR)
        {
          /* Check DID has valid security configured */
            LblSearchResult = Dcm_DsdValidateSecurity(
              LpDidWrite->pDidWriteSecurity, LpDidWrite->ucDidWriteSecCount);
        }

        /* Check whether session and security check returns no NRC */
        if(LblSearchResult == DCM_TRUE)
        {
          /* Check DID has valid mode rule configured */
          #if (DCM_MODE_RULE == STD_ON)
          if(LpDidWrite->blModeRuleConfigured  ==  DCM_TRUE )
          {
            LblSearchResult = Dcm_DsdModeRuleCheck
               (LpDidWrite->ucDIDmoderuleArrayindex);

            if(LblSearchResult == DCM_TRUE)
            {
              LddResult = DCM_E_POSITIVERESPONSE;
            }
            else
            {
              /* Response message length is 1 */
              #if(DCM_DSP_MODE_RULE_NRC == STD_ON)
              LpModeRule =
                &Dcm_GaaModeRuleConfig[LpDidWrite->ucDIDmoderuleArrayindex];
              LddResult =  LpModeRule->ucNRCType;
              #else
              /* Update Negative Response Code */
              LddResult  =  DCM_E_CONDITIONSNOTCORRECT;
              #endif
            }
          }
          else
          {
            LddResult = DCM_E_POSITIVERESPONSE;
          }
          #else
          LddResult = DCM_E_POSITIVERESPONSE;
          #endif
        }
        else
        {
          /* Security not supported in current state */
          LddResult = DCM_E_SECURITYACCESSDENIED;
        }
      }
      else
      {
         /* Session not supported in active session */
         LddResult = DCM_E_REQUESTOUTOFRANGE;
      }
    }
    else
    {
       LddResult = DCM_E_REQUESTOUTOFRANGE;
    }
  }
  else
  {
     LddResult = DCM_E_REQUESTOUTOFRANGE;
  }
  /* Update result */
  Dcm_GddNegRespError = LddResult;
  return LddResult;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspWriteDidRangeData                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to Write data to requested    **
**                        DID's using write data by id service.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusDataIdentifier, LusDIDIndex                      **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GddNegRespError,          **
**                        Dcm_GddOpStatus, Dcm_ServicePendingStatus.          **
**                        Function(s) invoked :                               **
**                        None                                                **
**                                                                            **
*******************************************************************************/
#if(DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspWriteDidRangeData(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint16 LusDataIdentifier, uint16 LusDIDIndex)
{
  P2VAR(Dcm_DIDRangeConfig, AUTOMATIC, DCM_APPL_DATA)pDIDRangeConfig = NULL_PTR;
  /* sg.baek 022705 - Task #2226 in redmine */
  Dcm_NegativeResponseCodeType LddNegativeErrorCode = DCM_E_GENERALPROGRAMMINGFAILURE;
  Std_ReturnType LddStdReturn;
  uint16 LusRangeDIDLength;

  pDIDRangeConfig = Dcm_CfgInternal_GetDIDRangeConfig(LusDIDIndex);

  if(NULL_PTR == pDIDRangeConfig)
  {
    /* DidRange is not configured */
    Dcm_GddNegRespError = DCM_E_GENERALREJECT;
    Dcm_ServicePendingStatus.ucWriteDataByIdPendingStatus = DCM_FALSE;   
  }
  else
  {    
    /* Get requested data length */
    LusRangeDIDLength = (uint16)(pMsgContext->reqDataLen - DCM_TWO);

    Dcm_ServicePendingStatus.ucWriteDataByIdPendingStatus = DCM_FALSE;

    /* Check if requested signal data is already read or not and
       if not then read the data */
    if(pDIDRangeConfig->ucDidRangeOpStatus != DCM_OPSTATUS_COMPLETE)
    {    
      if(NULL_PTR == pDIDRangeConfig->pDidRangeWriteDidFnc)
      {
        /* For Misra-C check */
        Dcm_GddNegRespError = DCM_E_GENERALREJECT;
        LddStdReturn = E_NOT_OK;
      }
      else
      {     
        LddStdReturn = pDIDRangeConfig->pDidRangeWriteDidFnc(
          LusDataIdentifier,
          &pMsgContext->reqData[DCM_TWO],
          Dcm_GddOpStatus, 
          LusRangeDIDLength, 
          &LddNegativeErrorCode
        );
      }
      
      if(Dcm_GddOpStatus != DCM_CANCEL)
      {
        if(LddStdReturn == E_OK)
        {
          /* Update OpStatus */
          Dcm_GddOpStatus = DCM_INITIAL;
          pDIDRangeConfig->ucDidRangeOpStatus = DCM_OPSTATUS_COMPLETE;
          /* Update OpStatus flag */
          Dcm_ServicePendingStatus.ucWriteDataByIdPendingStatus = DCM_FALSE;
        }
        else if(LddStdReturn == DCM_E_PENDING)
        {
          /* Update Opstatus flag */
          Dcm_GddOpStatus = DCM_PENDING;
          pDIDRangeConfig->ucDidRangeOpStatus = DCM_OPSTATUS_PENDING;
      
          /* Set response pending flag to True */
          Dcm_ServicePendingStatus.ucWriteDataByIdPendingStatus = DCM_TRUE;
        }
      
        else
        {
          /* Update Negative response code */
          Dcm_GddNegRespError = LddNegativeErrorCode;
          Dcm_ServicePendingStatus.ucWriteDataByIdPendingStatus = DCM_FALSE;
        }
      }
      else
      {
        /* Reset OpStatus */
        Dcm_GddOpStatus = DCM_INITIAL;
      }
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmReadDataByIdentifier                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This ReadDataByIdentifier service is used to get    **
**                        the value of one or more requested DID value.       **
**                        If the requested DID references several other DID   **
**                        the DCM module shall process the verification and   **
**                        the reading of every referenced DID                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :  NA                                                 **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GusMaxNoOfRespPend,       **
**                        Dcm_GddNegRespError,                                **
**                        Dcm_GaaReadDid, Dcm_GblDIDNotSupportedSession,      **
**                        Dcm_ServicePendingStatus,                           **
**                        Dcm_GblResOnPeriodicIdStatus, Dcm_GucPeriodicSID,   **
**                        Dcm_GaaDslPeriodicData,Dcm_IndexOfDslPeriodicData,  **
**                        Function(s) invoked : Dcm_IDSearch,                 **
**                        Dcm_DsdValidateSession, Dcm_DsdValidateSecurity,    **
**              Dcm_DspInternal_ReadSigTypeNvMBlock, IoHwAb_Dcm_Read_<>,      **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ExternalProcessingDone                          **
**                                                                            **
*******************************************************************************/
#if(DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmReadDataByIdentifier(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  uint32 LulMaxLen;
 
  P2VAR(Dcm_DidProcStateType, AUTOMATIC, DCM_APPL_DATA)
    pRdDid = &Dcm_DidProcState[0]; 
 
  Dcm_GusMaxNoOfRespPend = DCM_ZERO; 
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  
  #if (DCM_ZERO != DCM_MAX_DID_TO_READ)
  LulMaxLen = (uint32)((uint32)Dcm_Max_DID_To_Read << (uint32)1U);
  #else
  LulMaxLen = pMsgContext->reqDataLen;
  #endif

  if ((pMsgContext->reqDataLen < DCM_TWO) || 
     ((pMsgContext->reqDataLen % DCM_TWO) != DCM_ZERO))
  {
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  /* Check for the client exceeded the maximum number of dataIdentifiers
   * allowed to be requested at a time */  
  else if(pMsgContext->reqDataLen > LulMaxLen)
  {
    /* Report the Request out of range NRC */
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
  }
  else
  {
    pRdDid->atLeastOne = DCM_FALSE;
    
    pRdDid->iDid  = 0U;
    /* updates the number if Data Identifiers by request,
     * pRdDid->NumOfDid is greater than 1 */
    pRdDid->NumOfDid  = (uint16) (pMsgContext->reqDataLen / DCM_SIZEOF_DATAID);
    pRdDid->state.modeOfReadDid = DCM_READDID_STATE_READ_DID;
    pRdDid->state.did = DCM_DID_STATE_CONDITION_CHECK_READ;
    
    pMsgContext->resDataLen = 0U;
    Dcm_DspInternal_DcmReadDataByIdentifier(DCM_INITIAL,pMsgContext);
    
  }

  if (Dcm_ServicePendingStatus.ucReadDataPendingStatus != DCM_TRUE)
  {
    #if ((DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) && \
         (DCM_PROTOCOL_TRANSTYPE2 == STD_ON))
    if (DCM_IS_PDID_RUNNING)
    {
      
      SchM_Enter_Dcm_ProtclProtection();
      Dcm_GaaDslPeriodicData[Dcm_IndexOfDslPeriodicData].ucDataStatus = 
        DCM_PER_DATA_READY;
      Dcm_GaaDslPeriodicData[Dcm_IndexOfDslPeriodicData].ulDataLen =
        (uint16)pMsgContext->resDataLen;
      SchM_Exit_Dcm_ProtclProtection();
    }
    #endif
    
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  } 
  /* TODO: return value shall be processed */

  DCM_UNUSED(OpStatus);

  return E_OK;  
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_DcmReadDataByIdentifier             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This ReadDataByIdentifier service is used to get    **
**                        the value of one or more requested DID value.       **
**                        If the requested DID references several other DID   **
**                        the DCM module shall process the verification and   **
**                        the reading of every referenced DID                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :  NA                                                 **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GusMaxNoOfRespPend,       **
**                        Dcm_GddNegRespError,                                **
**                        Dcm_GaaReadDid, Dcm_GblDIDNotSupportedSession,      **
**                        Dcm_ServicePendingStatus,                           **
**                        Dcm_GblResOnPeriodicIdStatus, Dcm_GucPeriodicSID,   **
**                        Dcm_GaaDslPeriodicData,Dcm_IndexOfDslPeriodicData,  **
**                        Function(s) invoked : Dcm_IDSearch,                 **
**                        Dcm_DsdValidateSession, Dcm_DsdValidateSecurity,    **
**              Dcm_DspInternal_ReadSigTypeNvMBlock, IoHwAb_Dcm_Read_<>,      **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ExternalProcessingDone                          **
**                                                                            **
*******************************************************************************/
#if(DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspInternal_DcmReadDataByIdentifier(
  Dcm_OpStatusType anOpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) aMsgContext)
{
  P2VAR(Dcm_DidProcStateType, AUTOMATIC, DCM_APPL_DATA) pRdDid =
                                                           &Dcm_DidProcState[0];
  Dcm_NegativeResponseCodeType NRC = DCM_E_POSITIVERESPONSE;
  /*boolean atLeastOneDid = DCM_FALSE;*/
  Std_ReturnType retVal = E_OK;
  uint16 dataIdentifier = 0U; 

  DCM_SET_RDATA_PENDING_STATUS(DCM_FALSE);    

  /* Possible operation status
   *  (1) DCM_INITIAL
   *  (2) DCM_PENDING
   *  (3) DCM_CANCEL */
  pRdDid->ucOpStatus = anOpStatus;

  /* At least one DID is supported in the active session? */
  while ((pRdDid->iDid < pRdDid->NumOfDid) &&
         (DCM_E_POSITIVERESPONSE == NRC) &&
         ((E_OK == retVal) || (DCM_E_NO_DID == retVal)))
  {
    if (DCM_READDID_STATE_READ_DID == pRdDid->state.modeOfReadDid)
    {
      uint32 pos = ((uint32)DCM_SIZEOF_DATAID) * ((uint32)pRdDid->iDid);

      /* Gets 'Data Identifier' from request buffer of MsgContext.  */
      DCM_GET_DATAID_FROM_REQUEST(dataIdentifier, aMsgContext->reqData, pos);
      
      /* Read 'DID' through a speficic function base on the type of DID */
      retVal = Dcm_DspInternal_ReadDidType(dataIdentifier, aMsgContext, &NRC);
    
      if ((E_OK == retVal) && (pRdDid->iDidTable < Dcm_Num_Of_DidParaConfig))
      { 
        /* These get values from function Dcm_DspInternal_ReadDidType()
         *  (1) pRdDid->iDidTable
         *  (2) pRdDid->typeOfDid
         */
         
        /* Only Non-OBD DID can have the DidRef, TODO : True?*/
        if ((pRdDid->typeOfDid == DCM_NONOBD_ID) &&
            (Dcm_GaaDIDParaConfig[pRdDid->iDidTable].pDidRef != NULL_PTR))
        {
          /* This DID refer to one or server other DID's */
          pRdDid->iDidRef = 0U;
          /* iDidTableRef is a index of the parent DID of referenced DID */
          pRdDid->iDidTableRef = pRdDid->iDidTable;
          /* switch mode to reading the referenced DID(s) */
          pRdDid->state.modeOfReadDid = DCM_READDID_STATE_READ_DIDREF;
        }
        else
        {
          /* No DidRef 
           * Move to next DID */
          pRdDid->iDid++;
        }
      }
      else if (DCM_E_PENDING == retVal)
      {
        /* Do nothing
         *  (1) pending status is already true
         *  (2) The current values remains
         *  (3) Retries the pended operation on each Dcm_Mainfunction */
      }
      else if (DCM_E_NO_DID == retVal) 
      { 
        pRdDid->iDid++;
      }
      else/* E_NOT_OK */
      {
        /* NRC shall be responsed after exiting from this loop. */
        retVal = E_NOT_OK;
      }
    } 
    /* No else {} */
    
    if (DCM_READDID_STATE_READ_DIDREF == pRdDid->state.modeOfReadDid)
    {
      if (pRdDid->iDidTableRef < Dcm_Num_Of_DidParaConfig)
      {
        /* At this point in time, pRdDid->iDidTableRef is always valid. */
        uint16 numOfDidRef = Dcm_GaaDIDParaConfig[pRdDid->iDidTableRef].usDidRefCount;

        if (0 == numOfDidRef)
        {
          DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID,DCM_E_PARAM);
          retVal = E_NOT_OK;
          NRC = DCM_E_CONDITIONSNOTCORRECT;   
        }
        else
        {
          retVal = E_OK;
          NRC = DCM_E_POSITIVERESPONSE;        
        }
        
        while ((pRdDid->iDidRef < numOfDidRef) &&    
               (DCM_E_POSITIVERESPONSE == NRC) &&
               ((E_OK == retVal) || (DCM_E_NO_DID == retVal)))
        {        
          if(NULL_PTR == Dcm_GaaDIDParaConfig[pRdDid->iDidTableRef].pDidRef)
          {
            DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID,DCM_E_PARAM);
            retVal = E_NOT_OK; 
          }
          else
          {
            dataIdentifier = Dcm_GaaDIDParaConfig[pRdDid->iDidTableRef].pDidRef[pRdDid->iDidRef];
            retVal = Dcm_DspInternal_ReadDidType(dataIdentifier, aMsgContext, &NRC);

            if (E_OK == retVal)
            {
              pRdDid->iDidRef++;
            }
            else if (DCM_E_NO_DID == retVal) 
            { 
              pRdDid->iDidRef++;
            }
            else if (DCM_E_PENDING == retVal)
            {
              /* Do nothing
               *  (1) pending status is already true
               *  (2) The current values remains
               *  (3) Retries the pended operation on each Dcm_Mainfunction */
            }
            else /* E_NOT_OK */
            {          
              /* NRC = a negative response code.
               * NRC shall be responsed after exiting this loop. */
              retVal = E_NOT_OK;
            }
          }
        }
    
        /* Finished the DIDRef related operations. */
        if ((pRdDid->iDidRef == numOfDidRef) && ((E_OK == retVal) || (DCM_E_NO_DID == retVal)))
        {
          /* No more DidRef 
           * Move to next DID
           * last condition: 
           *  1) retVal is E_OK. 
           *  2) NRC is not negative response*/
          pRdDid->iDid++;
          pRdDid->state.modeOfReadDid = DCM_READDID_STATE_READ_DID;       
        }
        else
        {        
          /* Result: Not finished 'while loop' about all DidRefs,
           *         In other words, pRdDid->iDidRef is less than numOfDidRef.
           *
           * Possibe states base on the 'pRdDid->iDidRef < numOfDidRef'
           *  (1) E_NOT_OK      : NRC shall be responsed after exiting this loop.
           *  (2) DCM_E_PENDING : Retries last operation on each the Dcm_Mainfunction. 
           */
        }  
      }
      else
      {
        DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID,DCM_E_PARAM);
        NRC = DCM_E_CONDITIONSNOTCORRECT; 
        retVal = E_NOT_OK; 
      }
    }
      /* check runtime error */
    if ((DCM_READDID_STATE_READ_DIDREF != pRdDid->state.modeOfReadDid) &&
        (DCM_READDID_STATE_READ_DID != pRdDid->state.modeOfReadDid))
    {
      DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID,DCM_E_PARAM);
      NRC = DCM_E_CONDITIONSNOTCORRECT; 
      retVal = E_NOT_OK;
      /* Det Error */
    }
  } /* while ((pRdDid->iDid < pRdDid->NumOfDid) */

  /* At least one DID is supported in the active session? */
  if ((pRdDid->iDid == pRdDid->NumOfDid) && (DCM_FALSE == pRdDid->atLeastOne))
  {
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
  }
  else
  {
    Dcm_GddNegRespError = NRC;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspGetDIDType                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x22   **
**                        to validate the type of DID front the request       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusDataIdentifier                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : typeOfID                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GaaDIDParaConfig          **
**                        Dcm_GusDIDIndexVal                                  **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
    (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(Dcm_DidType, DCM_CODE) Dcm_DspGetDIDType(
  uint16 LusDataIdentifier)
{
  Dcm_DidType typeOfID = DCM_DIDTYPE_NO_TYPE;
  
  /* Dcm_GusDIDIndexVal  shall be removed */
  if(Dcm_GusDIDIndexVal < Dcm_Num_Of_DidParaConfig)
  {
    if(NULL_PTR != Dcm_GaaDIDParaConfig[Dcm_GusDIDIndexVal].pDidInfo)
    { 
      /* Check whether DID is of Dynamically defined */
      if((LusDataIdentifier >= DCM_DYNAMICID_LOWER_RANGE) &&
         (LusDataIdentifier <= DCM_DYNAMICID_UPPER_RANGE) &&
         (Dcm_GaaDIDParaConfig[Dcm_GusDIDIndexVal].pDidInfo->blDynamicallyDefined == DCM_TRUE))
      {
        /* Refers for Dynamically defined ID */
        typeOfID = DCM_DYN_ID;
      }
      /* Check whether DID is of periodically defined */
      else if((LusDataIdentifier >= DCM_OBDDID_LOWER_RANGE) &&
          (LusDataIdentifier <= DCM_OBDDID_UPPER_RANGE))
      {
        /* Refers for OBD defined ID */
        typeOfID = DCM_OBD_ID;
      }
      else if (LusDataIdentifier == DCM_READDATABYID_F186)
      {
        typeOfID = DCM_DIDTYPE_SESSION;
      }
      else
      {
        /* Refer For NON-OBD defined id */
        typeOfID = DCM_NONOBD_ID;
      }
    }
  }
  
  return typeOfID;
} 
#endif

/*******************************************************************************
** Function Name        : Dcm_ResetSignalOpStatus                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          :  This function is used to reset Operational         **
**                         status of the DIDs to INITIAL.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dcm_GaaReadDid, Dcm_GaaDIDParaConfig,               **
**                        Dcm_GaaDymDefinedDIDInfoType.                       **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) ||\
    (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
/* polyspace<MISRA-C:8.10:Not a defect:Justify with annotations> Whether the Dcm api function is required internal or external linkage, depends on user configuration */
FUNC(void, DCM_CODE) Dcm_ResetSignalOpStatus(uint16 aIteratorDid)
{                
  if(aIteratorDid < Dcm_Num_Of_DidParaConfig) 
  {   
    uint8 iteratorSignal;
    uint8 maxNumSignal;
    
    /* Initialise pointer to the parameters of requested DID */
    maxNumSignal = Dcm_GaaDIDParaConfig[aIteratorDid].ucDcmDspSignalCount;
     
    for (iteratorSignal = 0U; iteratorSignal < maxNumSignal; iteratorSignal++)
    {
      /* Reset signal status to INITIAL */
      Dcm_GaaDIDParaConfig[aIteratorDid].pDcmDspSignal[iteratorSignal].ucDidSignalOpStatus = 
        DCM_OPSTATUS_INITIAL;
    }              
  }
  else
  {
    DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID,DCM_E_PARAM);
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_ResetDIDOpStatus                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          :  This function is used to reset Operational         **
**                         status of the DIDs to INITIAL.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dcm_GaaReadDid, Dcm_GaaDIDParaConfig,               **
**                        Dcm_GaaDymDefinedDIDInfoType.                       **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
    (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
FUNC(void, DCM_CODE) Dcm_ResetDIDOpStatus(void)
{
  P2VAR(Dcm_DIDRangeConfig, AUTOMATIC, DCM_APPL_DATA)pDIDRangeConfig = NULL_PTR;
  uint16 LusDIDIndex = (uint16)0x00;
  uint16 LusDataIdentifier;
  uint8 LucDIDCount;
  uint8 LucTypeOfID = 0U;
  boolean LblDIDRangePresent;

  for(LucDIDCount = DCM_ZERO; LucDIDCount < Dcm_GusReadDIDCount; LucDIDCount++)
  {
    LusDataIdentifier = Dcm_GaaReadDid[LucDIDCount];
    (void)Dcm_DspDIDSearch(LusDataIdentifier, &LusDIDIndex, &LblDIDRangePresent);

    if((DCM_ZERO != Dcm_Num_Of_DcmDspDidRangeConfig) &&
                                               (DCM_TRUE == LblDIDRangePresent))
    {
      pDIDRangeConfig = Dcm_CfgInternal_GetDIDRangeConfig(LusDIDIndex);

      if(NULL_PTR != pDIDRangeConfig)
      {
        /* DidRange is configured correctly */
        pDIDRangeConfig->ucDidRangeOpStatus = DCM_OPSTATUS_INITIAL;
      }
    }    
    else
    {
      /* Invoke the internal function to get type of DID */
      LucTypeOfID = (uint8)Dcm_DspGetDIDType(LusDataIdentifier);

      /* Id DID is dynamic */
      if(LucTypeOfID == DCM_DYN_ID)
      {
        #if(DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON)
        uint8 LucDymDIDCount;
        uint16 LusDynDIDIndex;
      
        LusDynDIDIndex = LusDIDIndex - (Dcm_Total_Num_Of_Static_DID - Dcm_Total_Num_Of_OBD_DID);

        if (LusDynDIDIndex < Dcm_Total_Num_Of_Dym_DID)  
        { 
          /* FIXME: LucDymDIDCount, ucSrcIDCount -> uint8? or uint16?  */
          P2VAR(Dcm_DymDefinedDIDInfoType, AUTOMATIC, DCM_APPL_DATA) LpDymDIDInfo;
          P2VAR(Dcm_SrcIDInfoType, AUTOMATIC, DCM_APPL_DATA) LpSrcIDInfo;
        
          LpDymDIDInfo = &Dcm_GaaDymDefinedDIDInfoType[LusDynDIDIndex];
        
          LpSrcIDInfo = LpDymDIDInfo->pSrcIDInfo;
         
          /* Note : Index starts from 1 */
          for(LucDymDIDCount = DCM_ONE; 
              LucDymDIDCount <= LpDymDIDInfo->ucSrcIDCount; 
              LucDymDIDCount++)
          {
            if(LucDymDIDCount == LpSrcIDInfo->usPriority)
            {
              /* Check if the DID from the request is supported */
              (void) Dcm_DspDIDSearch(LpSrcIDInfo->usSrcID,  &LusDIDIndex, &LblDIDRangePresent);
              Dcm_ResetSignalOpStatus(LusDIDIndex);
            }
            /* fixed by youngjin.yun, 2014-11-20:  Next src did */
            LpSrcIDInfo = &LpSrcIDInfo[1u];            
          }
        }
        #endif
      }
      else
      {
        Dcm_ResetSignalOpStatus(LusDIDIndex);
        if ((LusDIDIndex < Dcm_Num_Of_DidParaConfig) &&
            (NULL_PTR != Dcm_GaaDIDParaConfig[LusDIDIndex].pDidRef))
        { 
          P2CONST(Dcm_DIDParaConfig, AUTOMATIC, DCM_APPL_CONST)LpDIDTAB;  
          P2CONST(uint16, AUTOMATIC, DCM_APPL_CONST)LpDidReferred;          
          uint16 LusDidRefCount;
          uint16 LusDIDRefIndex;
          /* Initialise pointer to the parameters of requested DID */    
          LpDIDTAB = &Dcm_GaaDIDParaConfig[LusDIDIndex];          
          LusDidRefCount = LpDIDTAB->usDidRefCount;
          LpDidReferred = LpDIDTAB->pDidRef;
          if(NULL_PTR != LpDidReferred)
          {  
            for ( LusDIDRefIndex = DCM_ZERO; LusDIDRefIndex < LusDidRefCount; LusDIDRefIndex++)
            {
              (void)Dcm_DspDIDSearch(LpDidReferred[LusDIDRefIndex], &LusDIDIndex, &LblDIDRangePresent);

              if((DCM_ZERO != Dcm_Num_Of_DcmDspDidRangeConfig) &&
                                               (LblDIDRangePresent == DCM_TRUE))
              {
                pDIDRangeConfig = Dcm_CfgInternal_GetDIDRangeConfig(LusDIDIndex);
                
                if(NULL_PTR != pDIDRangeConfig)  
                {
                  /* DidRange is configured correctly */
                  pDIDRangeConfig->ucDidRangeOpStatus = DCM_OPSTATUS_INITIAL;
                }
              }
              else
              {
                Dcm_ResetSignalOpStatus(LusDIDIndex);
              }
            }
          }
        }
      }
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspValidateDID                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x22   **
**                        to validate session and security for the DID        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusDIDIndex, LblDIDRangePresent                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GblDIDNotSupportedSession **
**                        Dcm_GddNegRespError, Dcm_GaaDIDParaConfig,          **
**                        Dcm_GaaModeRuleConfig.                              **
**                        Function(s) invoked :                               **
**                        Dcm_GetSesCtrlType, Dcm_GetSecurityLevel            **
**                                                                            **
*******************************************************************************/
#if((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
    (DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspValidateDID(
  uint16 LusDIDIndex, boolean LblDIDRangePresent)
{
  Std_ReturnType result = E_NOT_OK;
  
  P2CONST(Dcm_DIDInfoType, AUTOMATIC, DCM_APPL_CONST)LpDidInfo = NULL_PTR;
  P2CONST(Dcm_DIDInfoTypeDidRead, AUTOMATIC, DCM_APPL_CONST)LpDidRead = NULL_PTR;
 
  Dcm_NegativeResponseCodeType LddResult;
  
  #if (DCM_MODE_RULE == STD_ON)
  uint8 LucModeIndex;
  #endif
  
  /* Reset status of DID not supported in current session to false */
  Dcm_GblDIDNotSupportedSession = DCM_FALSE;
 
  result = Dcm_DspInternal_GetDidInfo(LusDIDIndex, LblDIDRangePresent, &LpDidInfo);

  if ((E_OK == result) && (NULL_PTR != LpDidInfo))
  {
    if(LpDidInfo->pDidRead != NULL_PTR)
    {
      boolean LblSearchResult;
  
      LpDidRead = LpDidInfo->pDidRead;
      if(LpDidRead->pDidReadSession != NULL_PTR)
      {
        /* Check DID has valid session configured */
        LblSearchResult = Dcm_DsdValidateSession(LpDidRead->pDidReadSession,
            LpDidRead->ucDidReadSesCount);
      }
      else
      {
        LblSearchResult = DCM_TRUE;
      }
      /* Check whether session and security check returns no NRC */
      if(LblSearchResult == DCM_TRUE)
      {
        /* Check if session is configured for the DID */
        if(LpDidRead->pDidReadSecurity != NULL_PTR)
        {
          /* Check DID has valid security configured */
          LblSearchResult = Dcm_DsdValidateSecurity(
              LpDidRead->pDidReadSecurity, LpDidRead->ucDidReadSecCount);
        }
        if(LblSearchResult == DCM_TRUE)
        {
          #if (DCM_MODE_RULE == STD_ON)
          LucModeIndex = LpDidRead->ucDIDmoderuleArrayindex;
          if(LpDidRead->blModeRuleConfigured  ==  DCM_TRUE )
          {
            LblSearchResult = Dcm_DsdModeRuleCheck(LucModeIndex);
            if(LblSearchResult == DCM_FALSE)
            {
              #if(DCM_DSP_MODE_RULE_NRC == STD_ON)
              LddResult =  Dcm_GaaModeRuleConfig[LucModeIndex].ucNRCType;
              #else
              /* Update Negative Response Code */
              LddResult  =  DCM_E_CONDITIONSNOTCORRECT;
              #endif
            }
            else
            {
              LddResult = DCM_E_POSITIVERESPONSE;
            }
          }
          else
          {
            LddResult = DCM_E_POSITIVERESPONSE;
          }
          #else
          LddResult = DCM_E_POSITIVERESPONSE;
          #endif
        }
        else
        {
          /* Security not supported in current state */
          LddResult = DCM_E_SECURITYACCESSDENIED;
        }
      }
      else
      {
        /* Set flag for DID not supported in current session */
        Dcm_GblDIDNotSupportedSession = DCM_TRUE;
        /* Session not supported in active session */
        LddResult = DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION;
      }

    }
    else
    {
      LddResult = DCM_E_REQUESTOUTOFRANGE;
    }
  }
  else
  {
    LddResult = DCM_E_REQUESTOUTOFRANGE;
  }

  return LddResult;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_GetPeriodicDidInRunning             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x22   **
**                        to Read the DID                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusDIDIndex ,LucDidCount                            **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GaaDymDefinedDIDInfoType, **
**                        Dcm_GaaDymMemDIDInfoType,                           **
**                        Dcm_GblResOnPeriodicIdStatus, Dcm_GusDidReadIndex,  **
**                        Dcm_GucRMBAMemoryIdentifier, Dcm_GddOpStatus,       **
**                        Dcm_GddNegRespError, Dcm_ServicePendingStatus,      **
**                        Dcm_GaaDidReadSignalData.                           **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_GetPeriodicDidInRunning(
  uint16 DataId,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) pIndex)
{
  Std_ReturnType retVal = E_NOT_OK;
  uint16 numOfSchSlot = Dcm_Dsp_Max_Periodic_DID_Scheduled;
  uint16 i = 0U;  
  
  while (i < numOfSchSlot)
  {
    if (Dcm_GaaPeriodicID[i][0U] == DataId)
    {
      *pIndex = i;
      retVal = E_OK;
      break;      
    }
    i++;
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadDidType                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x22   **
**                        to Read the DID                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusDIDIndex ,LucDidCount                            **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GaaDymDefinedDIDInfoType, **
**                        Dcm_GaaDymMemDIDInfoType,                           **
**                        Dcm_GblResOnPeriodicIdStatus, Dcm_GusDidReadIndex,  **
**                        Dcm_GucRMBAMemoryIdentifier, Dcm_GddOpStatus,       **
**                        Dcm_GddNegRespError, Dcm_ServicePendingStatus,      **
**                        Dcm_GaaDidReadSignalData.                           **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if(DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidType(
  uint16 DataIdentifier,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  Dcm_NegativeResponseCodeType *pNegRespCode)
{
  P2VAR(Dcm_DidProcStateType, AUTOMATIC, DCM_APPL_DATA) pRdDid;
  Std_ReturnType retVal = E_OK;

  *pNegRespCode = DCM_E_POSITIVERESPONSE;
  pRdDid = &Dcm_DidProcState[0];  

  /* I. DCM_DID_STATE_CONDITION_CHECK_READ 
   *
   * Possibe errors
   *  (1) E_OK: keep going - next step: 'II. DCM_DID_STATE_READ_DID'
   *  (2) E_NOT_OK : sends NRC 
   */
  if (DCM_DID_STATE_CONDITION_CHECK_READ == pRdDid->state.did)
  { 
    Dcm_NegativeResponseCodeType nrCode;
    boolean IsRange = DCM_FALSE;
    uint16 cfgDidIndex = 0U;

    nrCode = DCM_E_REQUESTOUTOFRANGE;    
    /* Check if the DID from the request is supported */
    if (DCM_TRUE == Dcm_DspDIDSearch(DataIdentifier, &cfgDidIndex, &IsRange))
    {
      /* Validate the session, security and mode rule configured for DID */
      nrCode = Dcm_DspValidateDID(cfgDidIndex, IsRange);   
    } 
    else
    {
      retVal = DCM_E_NO_DID;
      /* Don't care pNegRespCode. */
    }

    if (DCM_E_POSITIVERESPONSE == nrCode)
    {
      uint8 sizeOfDataId = (uint8)0x00;
      Dcm_DidType didKind;

      if((DCM_ZERO != Dcm_Num_Of_DcmDspDidRangeConfig) && (DCM_TRUE == IsRange))
      {
        didKind = DCM_DIDTYPE_DIDRANGE;
      }
      else
      {
        didKind = Dcm_DspGetDIDType(DataIdentifier);
      }
      
      /* periodic DID size = 1, static did size = 2*/
      if (DCM_IS_PDID_RUNNING)
      {
        sizeOfDataId = (uint8)0x01; 
      }
      else
      {
        sizeOfDataId = DCM_SIZEOF_DATAID;      
      }
 
      if ((pMsgContext->resDataLen + sizeOfDataId) > 
           pMsgContext->resMaxDataLen)
      {
        *pNegRespCode = DCM_E_RESPONSETOOLONG;
        retVal = E_NOT_OK;
      }
      else if (didKind >= DCM_DIDTYPE_NO_TYPE)
      {
        retVal = DCM_E_NO_DID;
        /* Don't care pNegRespCode */
      }
      else if (NULL_PTR == Dcm_FuncPtrList_ReadDidType[didKind])
      {
        retVal = DCM_E_NO_DID;
        /* Don't care pNegRespCode */
      }
      else
      {
        pRdDid->atLeastOne = DCM_TRUE;
        
        /* condition is always true : if (typeOfDid < DCM_DIDTYPE_NO_TYPE) */
        pRdDid->iDidTable = cfgDidIndex;
        pRdDid->typeOfDid = didKind;
        pRdDid->dataId = DataIdentifier;
        
        #if(DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON)
        pRdDid->iSrcDid = 0U;
        #endif
        
        /* signal status */
        pRdDid->SigIndex  = 0U;
        pRdDid->state.sig = DCM_SIG_STATE_CONDITION_CHECK_READ;
        
        /* next step : read did */
        pRdDid->state.did = DCM_DID_STATE_READ_DID;          

        DCM_SET_DATAID_IN_RESPONSE(pMsgContext->resData, pMsgContext->resDataLen, DataIdentifier);                
      }
    }
    /* checks *pNegRespCode */
    else if ((DCM_E_CONDITIONSNOTCORRECT == nrCode) ||
             (DCM_E_SECURITYACCESSDENIED == nrCode))
    {
      *pNegRespCode = nrCode;    

      /* Only when NRC is negative response, 
         retVal is E_NOT_OK */
      retVal = E_NOT_OK;
    }
    else /* (DCM_E_POSITIVERESPONSE != nrCode) */
    {
      retVal = DCM_E_NO_DID;
      /* Don't care pNegRespCode */
    }
  }

  /* II. DCM_DID_STATE_CONDITION_CHECK_READ 
   *
   * Possibe errors
   *  (1) E_OK: keep going - next step : 'I. DCM_DID_STATE_CONDITION_CHECK_READ'
   *  (2) E_NOT_OK : sends NRC
   *  (3) DCM_E_PENDING : Retries the current operation on each Dcm_Mainfunction
   *                      next step : 'II. DCM_DID_STATE_READ_DID'
   */
  if (DCM_DID_STATE_READ_DID == pRdDid->state.did)
  {
    if (pRdDid->typeOfDid < DCM_NUM_FUNCPTRLIST_READDIDTYPE)
    {    
      /*  (NULL_PTR != Dcm_FuncPtrList_ReadDidType[pRdDid->typeOfDid])*/
      retVal = Dcm_FuncPtrList_ReadDidType[pRdDid->typeOfDid](pMsgContext, pRdDid->iDidTable, pRdDid->iDid, pNegRespCode);  

      if (E_OK == retVal)
      {   
        pRdDid->state.did = DCM_DID_STATE_CONDITION_CHECK_READ;
        /* pRdDid->state.sig remains */
      }
      else if (DCM_E_PENDING == retVal)
      {
        /* Do nothing
         * pNegRespCode is ignored 
         * retVal is DCM_E_PENDING 
         * pRdDid->state.did remains */
      }
      else /* E_NOT_OK */
      {
        if (DCM_E_POSITIVERESPONSE == *pNegRespCode)
        {
          *pNegRespCode = DCM_E_CONDITIONSNOTCORRECT; 
        }
        retVal = E_NOT_OK;
      }
    }
    else
    {
      DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID,DCM_E_PARAM);
      *pNegRespCode = DCM_E_CONDITIONSNOTCORRECT; 
      retVal = E_NOT_OK;
    }    
  }

  /* bug */
  if ((DCM_DID_STATE_READ_DID != pRdDid->state.did) &&
      (DCM_DID_STATE_CONDITION_CHECK_READ != pRdDid->state.did))
  {
    *pNegRespCode = DCM_E_CONDITIONSNOTCORRECT; 
    retVal = E_NOT_OK;
  }
  
  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadDidTypeDDDID                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x22   **
**                        to Read the requested Dynamic DID value from the    **
**                        Application.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusDIDIndex ,LucDidCount                            **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GaaDymDefinedDIDInfoType, **
**                        Dcm_GaaDymMemDIDInfoType,                           **
**                        Dcm_GblResOnPeriodicIdStatus, Dcm_GusDidReadIndex,  **
**                        Dcm_GucRMBAMemoryIdentifier, Dcm_GddOpStatus,       **
**                        Dcm_GddNegRespError, Dcm_ServicePendingStatus,      **
**                        Dcm_GaaDidReadSignalData.                           **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) && \
    (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidTypeDDDID(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) aMsgContext,
  uint16 aDIdIndex, 
  uint16 aDidCount,
  Dcm_NegativeResponseCodeType *anOutNegRespCode)
{
  P2VAR(Dcm_DidProcStateType, AUTOMATIC, DCM_APPL_DATA) pRdDid;
  uint16 iDDDIDInfo;
  uint16 numOfDidSrc = (uint16)0x00;
  Std_ReturnType retVal;

  DCM_UNUSED(aDidCount);
  
  pRdDid = &Dcm_DidProcState[0];

  /* FIXME : if num of static did is 0 ? */
  /*--------------------------------------------------------*
   * | OBD Index  | Static DID Index | Dynamic  DID Index | *
   *--------------------------------------------------------*/
  /* Get the index for dynamically defined DID */
  iDDDIDInfo = aDIdIndex - (Dcm_Total_Num_Of_Static_DID - Dcm_Total_Num_Of_OBD_DID);

  if(iDDDIDInfo >= Dcm_Total_Num_Of_Dym_DID) 
  {
    DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID,DCM_E_PARAM);
    /* For Misra-C check */
    *anOutNegRespCode = DCM_E_GENERALREJECT;
    retVal = E_NOT_OK;
  }
  else  
  {
    numOfDidSrc = (uint16)Dcm_GaaDymDefinedDIDInfoType[iDDDIDInfo].ucSrcIDCount + 
               (uint16)Dcm_GaaDymMemDIDInfoType[iDDDIDInfo].ucMemAddressCount;
  
    if(0U == numOfDidSrc)
    {
      *anOutNegRespCode = DCM_E_REQUESTOUTOFRANGE;
      retVal = E_NOT_OK;
    }
    else
    {
      *anOutNegRespCode = DCM_E_POSITIVERESPONSE;
      retVal = E_OK;
    }

    while((pRdDid->iSrcDid < numOfDidSrc) &&
       (DCM_E_POSITIVERESPONSE == *anOutNegRespCode) &&
       (E_OK == retVal))
    {
      uint16 priority = pRdDid->iSrcDid + 1U;    
      /* retVal = E_NOT_OK; */

      /* FIXME: devide stage : validate and read did type */
      /**********************************
       *    defineByIdentifier          *
       **********************************/
      if(priority == Dcm_GaaDymDefinedDIDInfoType[iDDDIDInfo].pSrcIDInfo[pRdDid->iSrcDid].usPriority) 
      {
        boolean bDIDR;
        uint16 dataIdentifier = 
          Dcm_GaaDymDefinedDIDInfoType[iDDDIDInfo].pSrcIDInfo[pRdDid->iSrcDid].usSrcID;
        
        /* Check if the DID from the request is supported */
        if(DCM_TRUE != Dcm_DspDIDSearch(dataIdentifier, &aDIdIndex, &bDIDR))
        { 
          /* QUESTION : I don't know whether retVal is not ok or no DID */
          *anOutNegRespCode  = DCM_E_REQUESTOUTOFRANGE;
          /* retVal = E_NOT_OK;*/
        }
        else
        {        
          #if(DCM_DYNAMIC_DID_PER_SOURCE == STD_ON)
          *anOutNegRespCode = Dcm_DspValidateDID(aDIdIndex, bDIDR);
          #endif      
        }

        if(DCM_E_POSITIVERESPONSE != *anOutNegRespCode)
        {
          /* pNegRespCode is negative response code */
          retVal = E_NOT_OK;       
        }
        else
        {
          uint32 len;
          Dcm_DidType didKind;

          len = Dcm_GaaDymDefinedDIDInfoType[iDDDIDInfo].pSrcIDInfo[pRdDid->iSrcDid].ucMemSize;
          /* FIXME if type is non DCM_NONOBD_ID and did range ?*/
          if(DCM_TRUE == bDIDR)
          {
            didKind = DCM_DIDTYPE_DIDRANGE;
          }
          else
          {
            didKind = DCM_NONOBD_ID;                    
          }            

          if((aMsgContext->resDataLen + len) > aMsgContext->resMaxDataLen)
          {
            *anOutNegRespCode = DCM_E_RESPONSETOOLONG;
            retVal = E_NOT_OK;
          }
          else if(NULL_PTR != Dcm_FuncPtrList_ReadDidType[didKind])
          {
            uint32 resDataLenOld = aMsgContext->resDataLen;
            
            /*FIXME : dataId - pass it as paramter*/          
            pRdDid->dataId = dataIdentifier;
            
            retVal = Dcm_FuncPtrList_ReadDidType[didKind](aMsgContext, aDIdIndex, aDidCount, anOutNegRespCode);
            if(retVal == E_OK)
            {
              uint32 offsetResData = (uint32)Dcm_GaaDymDefinedDIDInfoType[iDDDIDInfo].pSrcIDInfo[pRdDid->iSrcDid].ucPosInSrc - (uint32)1U;
              P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pData = &aMsgContext->resData[resDataLenOld];
                
              Dcm_DspInternal_MemCopy(&pData[0U], &pData[offsetResData], len);

              /* Update the response length for the data updated */
              aMsgContext->resDataLen = resDataLenOld + len;

              /* signal status */
              pRdDid->SigIndex  = 0U;
              pRdDid->state.sig = DCM_SIG_STATE_CONDITION_CHECK_READ;          
            }
            else if(DCM_E_PENDING == retVal)
            {
              /* Do nothing */
            }
            else /* E_NOT_OK */
            {
              /* Nothing
               * pNegRespCode is negative response code or DCM_CANCEL */
            }
          }
          else
          {
          /* QUESTION : I don't know whether retVal is not ok or no DID */
            *anOutNegRespCode = DCM_E_CONDITIONSNOTCORRECT;
            retVal = E_NOT_OK;
          }
        } /* if (DCM_E_POSITIVERESPONSE == *pNegRespCode) */   
      }
       /**********************************
       *    defineByMemoryAddress       *
       **********************************/
      else if(priority == 
                 Dcm_GaaDymMemDIDInfoType[iDDDIDInfo].pMemAddInfo[pRdDid->iSrcDid].usPriority)
      {  

        retVal = Dcm_DspInternal_ReadSigTypeMemory(
         pRdDid->ucOpStatus, Dcm_GucRMBAMemoryIdentifier, 
          Dcm_GaaDymMemDIDInfoType[iDDDIDInfo].pMemAddInfo[pRdDid->iSrcDid].ulMemAddrs, 
          Dcm_GaaDymMemDIDInfoType[iDDDIDInfo].pMemAddInfo[pRdDid->iSrcDid].ulMemSize,
          &aMsgContext->resData[aMsgContext->resDataLen], 
          anOutNegRespCode);

        if(E_OK == retVal)
        {
          aMsgContext->resDataLen += 
            Dcm_GaaDymMemDIDInfoType[iDDDIDInfo].pMemAddInfo[pRdDid->iSrcDid].ulMemSize;
          *anOutNegRespCode = DCM_E_POSITIVERESPONSE;

          /* After completing the pended operation, 
           * call the next operation with OpStatus = DCM_INITIAL */
          pRdDid->ucOpStatus = DCM_INITIAL;
        }
        else if(DCM_E_PENDING == retVal)
        {
          /* Set response pending flag to True */     
          DCM_SET_RDATA_PENDING_STATUS(DCM_TRUE);
        }
        /* FIXME */
        else if(DCM_E_FORCE_RCRRP == retVal)
        {
          /* Set response pending flag to True */     
          DCM_SET_RDATA_PENDING_STATUS(DCM_TRUE);
          retVal = DCM_E_PENDING;
        }
        else /* E_NOT_OK */
        {
          /* Nothing
           * pNegRespCode is negative response code or DCM_CANCEL */
        }
      }
      /* else if (priority == pSrcDid[pRdDid->iSrcDid].usPriority)  */
      else 
      {
        *anOutNegRespCode = DCM_E_CONDITIONSNOTCORRECT;
        retVal = E_NOT_OK;
      }

      if(E_OK == retVal)
      {
        /* next source did */
        pRdDid->iSrcDid++;
      }
    } /* while (num of source did ) */
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadDidTypeNonOBDDID                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x22   **
**                        to Read the requested Non OBD DID value from the    **
**                        Application.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusDIDIndex, LucIDIndex, LblDIDReferred             **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if(DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidTypeNonOBDDID(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) aMsgContext,
  uint16 aDidIndex, 
  uint16 aDidCount,
  Dcm_NegativeResponseCodeType *anOutNegRespCode)
{
  P2VAR(Dcm_DidProcStateType, AUTOMATIC, DCM_APPL_DATA) pRdDid = &Dcm_DidProcState[0];
  uint8 numOfSig = (uint8)0x00;
  Std_ReturnType retVal;

  DCM_UNUSED(aDidCount);

  #if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (aDidIndex >= Dcm_Num_Of_DidParaConfig)  /*  Fix for MISRA 21.1 -BSH  */
  {
    DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID,DCM_E_PARAM);
    *anOutNegRespCode = DCM_E_GENERALREJECT;  
    retVal = E_NOT_OK;
  }
  else
  #endif
  {
    numOfSig = Dcm_GaaDIDParaConfig[aDidIndex].ucDcmDspSignalCount;

    *anOutNegRespCode = DCM_E_POSITIVERESPONSE;
    
    /* Checkes whether DID has at least one signal */
    if ((NULL_PTR != Dcm_GaaDIDParaConfig[aDidIndex].pDcmDspSignal) && (0U != numOfSig))
    {
      retVal = E_OK;
      if (0U == pRdDid->SigIndex)
      {
        /* Stores the base resDatalen because 
         * All signal is written from base position by ucSignalStartByte */
        pRdDid->baseOfRespBuf = aMsgContext->resDataLen;
      }
          
      while ((pRdDid->SigIndex < numOfSig) && (E_OK == retVal))
      {
        P2VAR(Dcm_DcmDspSignalconfig, AUTOMATIC, DCM_APPL_DATA) 
          pSignal = &Dcm_GaaDIDParaConfig[aDidIndex].pDcmDspSignal[pRdDid->SigIndex];   

        if (NULL_PTR == pSignal->pDcmDspData)
        {
          DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID,DCM_E_PARAM);
          *anOutNegRespCode = DCM_E_GENERALREJECT;  
          retVal = E_NOT_OK;
        }
        else
        {
          P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST)
            pDataElm = pSignal->pDcmDspData; 
          
          /* I. DCM_SIG_STATE_CONDITION_CHECK_READ phase 
           *
           * Possibe errors
           *  (1) E_OK: keep going - next step: DCM_SIG_STATE_READ_LEN for the current signal
           *  (2) E_NOT_OK : sends NRC
           *  (3) DCM_E_PENDING : retries the current operation on each Dcm_MainFunction */
          if (DCM_SIG_STATE_CONDITION_CHECK_READ == pRdDid->state.sig)
          {
            retVal = Dcm_DspInternal_ConditionCheckRead(pRdDid->ucOpStatus, pDataElm, anOutNegRespCode);      
            if (E_OK == retVal)
            {
              pRdDid->state.sig = DCM_SIG_STATE_READ_LEN;  
              /* After completing the pended operation, 
               * call the next operation with OpStatus = DCM_INITIAL */
              pRdDid->ucOpStatus = DCM_INITIAL;
            }
            else if (DCM_E_PENDING == retVal)
            {
              /* Set response pending flag to True */     
              DCM_SET_RDATA_PENDING_STATUS(DCM_TRUE);
              
              /* pNegRespCode is ignored 
               * retVal is DCM_E_PENDING 
               * pRdDid->state.sig,pRdDid->SigIndex remain
               * DCM will call the operation on each Dcm_MainFunction. */
            }
            else /* E_NOT_OK */
            {
              /* pNegRespCode is negative response code or DCM_CANCEL */
              retVal = E_NOT_OK; 
            }
          }
    
          /* II. DCM_SIG_STATE_READ_LEN
           *
           * Possibe errors
           *  (1) E_OK     : keep going - next step: DCM_SIG_STATE_READ_SIGNAL for current signal
           *  (2) E_NOT_OK : sends NRC
           */
          if (DCM_SIG_STATE_READ_LEN == pRdDid->state.sig)
          {
            uint16 sizeOfSignal = 0U;       
    
            retVal = Dcm_DspInternal_GetSizeOfDidSignal(pRdDid->ucOpStatus, pDataElm, &sizeOfSignal);
          
            if(E_OK == retVal)      
            {
              if (0U != sizeOfSignal)
              {
                if ((aMsgContext->resDataLen + sizeOfSignal) > 
                     aMsgContext->resMaxDataLen)
                {
                  *anOutNegRespCode = DCM_E_RESPONSETOOLONG;
                  retVal = E_NOT_OK;        
                }
                else 
                {
                  pRdDid->sizeOfSigInBytes = sizeOfSignal;
                  pRdDid->state.sig = DCM_SIG_STATE_READ_SIGNAL;
                }
              }
              else
              {
#if 1              
                /* Next signal */
                pRdDid->SigIndex++;
                pRdDid->state.sig = DCM_SIG_STATE_CONDITION_CHECK_READ;
#else                
                retVal = E_NOT_OK; 
                *anOutNegRespCode = DCM_E_CONDITIONSNOTCORRECT;        
#endif                
              }
            }
            else
            {
              retVal = E_NOT_OK; 
              *anOutNegRespCode = DCM_E_CONDITIONSNOTCORRECT;        
            }      
          }
          /* III. DCM_SIG_STATE_READ_SIGNAL
           *
           * Possibe errors
           *  (1) E_OK          : keep going - next step: DCM_SIG_STATE_CONDITION_CHECK_READ for a next signal
           *  (2_ E_NOT_OK      : sends NRC
           *  (3) DCM_E_PENDING : retries operation on each Dcm_MainFunction 
           */
          if (DCM_SIG_STATE_READ_SIGNAL == pRdDid->state.sig)
          {
            P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDst;
            P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)  pSrc;
            P2CONST(Dcm_DIDPackSignal, AUTOMATIC, DCM_APPL_CONST) readSig;
            Dcm_PackUnpackSignalData packSig;
            
            pSrc = &Dcm_GaaDidReadSignalData[0];
            retVal = Dcm_DspInternal_ReadSigType(pRdDid->ucOpStatus, pDataElm, (void*)pSrc);
            /* Verify return value of read function configured */
            if((E_OK == retVal) && (NULL_PTR != pSignal->pDidPackSignal))
            {     
              readSig = pSignal->pDidPackSignal;
              
              /* UNUSED :ucSignalSize,ucSignMask: 
                 These are used to unpacking data for WriteData~ */      
              packSig.ucShiftBits = readSig->ucNoOfShiftBits;
              packSig.ucStartMask = readSig->ucStartMask;
              packSig.ucEndMask = readSig->ucEndMask;
              packSig.ucSignalType = DCM_HI_NIBBLE(readSig->ucSignalTypeorSize, uint8);
              packSig.ucSignalTypeorSize = readSig->ucSignalTypeorSize;
              packSig.ulSignalLength = 
                (packSig.ucSignalType == DCM_DATA_TYPE_CSIF_GT32) ? 
                  (uint32)pRdDid->sizeOfSigInBytes : (uint32)0U;
              /* for initialization */
              packSig.ucSignalSize = (uint8)0x00;
              packSig.ucSignMask = (uint8)0x00;
        
              /* FIXME: constr_6007,constr_6006 AR 4.2.1      
                 Get the number of counts that signal spread across n bytes
                 in the response buffer */      
              if ((pDataElm->pDataInfo != NULL_PTR) &&
                  (pDataElm->pDataInfo->blDataFixedLength == TRUE) &&
                  (packSig.ucSignalType != DCM_DATA_TYPE_CSIF_GT32))      
              {
                pRdDid->sizeOfSigInBytes = DCM_LO_NIBBLE(readSig->ucSignalTypeorSize, uint16);
              }      
    
              /* Invoke packing function */      
              pDst = &aMsgContext->resData[pRdDid->baseOfRespBuf + readSig->ucSignalStartByte];
    
              if (
                (readSig->ucWrFuncIndex < Dcm_Num_Of_SigWrFuncPtr) &&
                (NULL_PTR != Dcm_GaaSigWrFuncPtr[readSig->ucWrFuncIndex].pWrFuncPtr)
              )
              {       
                Dcm_GaaSigWrFuncPtr[readSig->ucWrFuncIndex].pWrFuncPtr(packSig, pDst, pSrc);        
              
                /* Update response length as DID read data is copied to response buffer */
                aMsgContext->resDataLen += pRdDid->sizeOfSigInBytes;
    
                /* Next signal */
                pRdDid->SigIndex++;
                pRdDid->state.sig = DCM_SIG_STATE_CONDITION_CHECK_READ;
    
                /* [SWS_Dcm_00530] 
                 * If a DCM_E_PENDING value is returned from an operation 
                 * using the Dcm_OpStatusType, the DCM call the operation on each 
                 * Dcm_MainFunction call with OpStatus = DCM_PENDING as long as 
                 * DCM_E_PENDING is returned.*/
    
                /* After completing the pended operation, 
                 * call the next operation with OpStatus = DCM_INITIAL */
                pRdDid->ucOpStatus = DCM_INITIAL;
              }
              else
              {
                /* For Misra-C check */
                *anOutNegRespCode = DCM_E_GENERALREJECT;  
                retVal = E_NOT_OK;         
              }
            }
            else if (DCM_E_PENDING == retVal)
            {
              /* Set response pending flag to True */     
              DCM_SET_RDATA_PENDING_STATUS(DCM_TRUE);
            }       
            else /* E_NOT_OK */
            {   
              /* Negative response code shall be returned  or DCM_CANCEL */
              retVal = E_NOT_OK; 
            }
          }
    
          if ((DCM_SIG_STATE_READ_SIGNAL != pRdDid->state.sig) &&
          (DCM_SIG_STATE_CONDITION_CHECK_READ != pRdDid->state.sig) &&
          (DCM_SIG_STATE_READ_LEN != pRdDid->state.sig))
          {
            /* Never perform it */
            *anOutNegRespCode = DCM_E_CONDITIONSNOTCORRECT;  
            retVal = E_NOT_OK;
            /* Det Error */
          }
    
          /* DCM_E_PENDING shall be available in case of async C/S or block ID */
          if ((retVal == DCM_E_PENDING) &&
          (pDataElm->ucDcmDspDataUsePort != DCM_USEBLOCKID) &&
          (pDataElm->ucDcmDspDataUsePort != DCM_USE_DATA_ASYNCH_FNC) &&
          (pDataElm->ucDcmDspDataUsePort != DCM_USE_DATA_ASYNCH_CLIENT_SERVER))
          {
            /* Never perform it */
            *anOutNegRespCode = DCM_E_CONDITIONSNOTCORRECT;  
            retVal = E_NOT_OK;
          } 
        }
      }
    } 
    else
    {
       *anOutNegRespCode = DCM_E_CONDITIONSNOTCORRECT; 
      retVal = E_NOT_OK;
    }
  }

  return retVal;
}

 /* TODO: To clarify Possible Errors 

 SWS_Dcm_00686(ReadData):

 i) Sync/Async ClientService
 The server is not allowed to return E_NOT_OK, 
 but shall always provide a valid data value 
 (e.g. a default/replacement value in an error-case)
 to Dcm/Dem nevertheless the signature of 
 the operation includes E_NOT_OK to ensure compatibility 
 between server runnable and RTE 
 Call API, since the RTE may return negative 
 Std_Return values in certain cases (e.g. partition 
 of server stopped)  

 ii) USE_SIGNAL
 E_OK is Always returned 

 iii) USE_BLOCK_ID 

 iv) Sender Receiver
 E_OK is Always returned                   
 */
#endif

/*******************************************************************************
** Function Name        : Dcm_DspDidPackSignal                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x22   **
**                        to pack the data for all signals of an DID.         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusDidIndex                                         **
**                                                                            **
** Output Parameters    : pMsgContext                                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GaaDIDParaConfig          **
**                        Dcm_GddOpStatus, Dcm_GusDidReadIndex,               **
**                        Dcm_GulResBufferPosition, Dcm_GblDIDReferrenceStatus**
**                        DCM_GblIsDIDInResp,                                 **
**                        Dcm_GblResOnPeriodicIdStatus, Dcm_GucPeriodicSID    **
**                        Dcm_GaaDidReadSignalData, Dcm_GaaSigWrFuncPtr,      **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if 0 
((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
 (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON))
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspDidPackSignal(
  P2CONST(Dcm_DIDPackSignal, AUTOMATIC, DCM_APPL_CONST) signal,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint16 sizeOfSig,
  boolean FixedLength,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) src)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) dst;
  Dcm_PackUnpackSignalData packSig;
  uint32 lenOfResp;  

  lenOfResp = 0U;
  
  packSig.ucShiftBits   = signal->ucNoOfShiftBits;
  packSig.ucStartMask   = signal->ucStartMask;
  packSig.ucEndMask     = signal->ucEndMask;
  packSig.ucSignalType  = DCM_HI_NIBBLE(signal->ucSignalTypeorSize);
  packSig.ucSignalTypeorSize = signal->ucSignalTypeorSize;

  /* ucSignalTypeorSize: This variable represents signal type or size of the signal. 
    Higher nibble represents the type of the signal and Lower nibble represents the 
    size of the signal that is spread across I-PDU. 
    0x11     8 bit signal pack into one byte       uint8
    0x12     8 bit signal pack into two byte       uint8
    0x22    16 bit signal pack into two byte       uint16
    0x23    16 bit signal pack into three byte     uint16
    0x44    32 bit signal pack into four byte      uint32
    0x45    32 bit signal pack into five byte      uint32
    0x50    greater than 32 (ext) Client Servicer
  */
  if(packSig.ucSignalType == DCM_FIVE)
  {
    packSig.ulSignalLength = sizeOfSig;
  }
  dst = &pMsgContext->resData[pMsgContext->resDataLen + signal->ucSignalStartByte];
  
  /* Invoke packing function */
  Dcm_GaaSigWrFuncPtr[signal->ucWrFuncIndex].pWrFuncPtr(packSig, dst, src);


  if(FixedLength == DCM_FALSE)
  {
    lenOfResp = sizeOfSig;
  }
  else if(packSig.ucSignalType == DCM_FIVE)
  {
    lenOfResp = signal->ulSignalLength;
  }
  /* placed across n bytes */
  else
  {
    lenOfResp = DCM_LO_NIBBLE(signal->ucSignalTypeorSize);
  }
  
  /* Update response length as DID read data is copied to response buffer */
  pMsgContext->resDataLen += lenOfResp;

  return E_OK;
}
#endif

/********************************************************************************
** Function Name        : Dcm_DspInternal_ReadDidTypeOBDDID                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x22   **
**                        to Read the requested OBD DID value from the        **
**                        Application.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusDIDIndex, LucDidCount                            **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GaaDIDParaConfig          **
**                        Dcm_GddNegRespError, Dcm_GulMaxBufValue,            **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) && \
   ((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
    (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
    (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON)))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidTypeOBDDID(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint16 LusDIDIndex, 
  uint16 LusDidCount,
  Dcm_NegativeResponseCodeType *LddErrorCode)
{
  Std_ReturnType retVal; 

  P2CONST(Dcm_DIDParaConfig, AUTOMATIC, DCM_APPL_CONST)LpDIDTAB;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqData;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpResBuffer;
  uint16 LusDataIdentifier;
  uint16 LusRespLength;

  /* To baek, FIXME : Verify buffer size and 
   * buffer related varialbe -LucIndex is uint8 ? uint32 */
  uint8 LucIndex;
  uint8 LucReqBuffer[DCM_MAXVALUE];
  uint8 LucResBuffer[DCM_MAXVALUE];

  LpDIDTAB = &Dcm_GaaDIDParaConfig[LusDIDIndex];
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  LpReqData = &LucReqBuffer[DCM_ZERO];
  LpResBuffer = &LucResBuffer[DCM_ZERO];

  /* Validate DID Index */
  if(LusDidCount == DCM_ZERO)
  {
    /* Store globally the Tx buffer size */
    Dcm_GulMaxBufValue = pMsgContext->resMaxDataLen;
  }

  LusDataIdentifier = LpDIDTAB->usDcmDspDidIdentifier;
  /* Update the request buffer for OBD service */
  LpReqData[DCM_ZERO] = (uint8)(LusDataIdentifier & DCM_MAXVALUE);

  if((LusDataIdentifier >= DCM_OBDDID_LOWER_RANGE) &&
      (LusDataIdentifier <= DCM_OBDDID_RANGE_F4FF))
  {
    /* Invoke OBD service 0x01*/
    #if(DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
    (void)Dcm_DspReadOBD_1_DemInfo (LpReqData, LpResBuffer, &LusRespLength,
        DCM_ONE);
    #else
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    #endif
  }
  else if((LusDataIdentifier >= DCM_OBDDID_RANGE_F600) &&
      (LusDataIdentifier <= DCM_OBDDID_RANGE_F6FF))
  {
    /* Invoke OBD service 0x06*/
    #if(DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON)
    Dcm_DcmOBDReqOnboadMonitorResultCall(LpReqData, LpResBuffer,
        DCM_ONE, &LusRespLength);
    #else
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    #endif
  }
  else if((LusDataIdentifier >= DCM_OBDDID_RANGE_F800) &&
      (LusDataIdentifier <= DCM_OBDDID_UPPER_RANGE))
  {
    /* Invoke OBD service 0x09*/
    #if(DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON)
    Dcm_DcmOBDRegVehicleInfoCall(LpReqData, LpResBuffer, DCM_ONE,
        &LusRespLength);
    #else
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    #endif
  }
  else
  {
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    LusRespLength = DCM_ZERO;
  }

  if(Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE)
  {
    if(LusRespLength <= Dcm_GulMaxBufValue)
    {
      for(LucIndex = DCM_ONE; LucIndex < LusRespLength; LucIndex++)
      {
        pMsgContext->resData[pMsgContext->resDataLen] = LpResBuffer[LucIndex];

        pMsgContext->resDataLen += DCM_ONE;
      }
      /* Update the remaining buffer size */
      Dcm_GulMaxBufValue = (Dcm_GulMaxBufValue - LusRespLength);
    }
    else
    {
      /* Update NRC */
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }
  }

  *LddErrorCode = Dcm_GddNegRespError;

  /* FIXME : */
  if (DCM_E_POSITIVERESPONSE != *LddErrorCode)
  {
    retVal = E_NOT_OK;
  }
  else
  {
    retVal = E_OK;
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmInputOutputControlByIdentifier               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The IOControlByIdentifier service is used to        **
**                        control an input/output specific to the server      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GaaDIDParaConfig,         **
**                        Dcm_GddNegRespError, Dcm_GucInOutParameter,         **
**                        Dcm_ServicePendingStatus.                           **
**                        Function(s) invoked : Dcm_DspValidateInputOutputDid,**
**                        Dcm_DspInternal_DcmInputOutputControlByIdentifier,  **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ResetDIDOpStatus, Dcm_ExternalProcessingDone    **
**                                                                            **
*******************************************************************************/
#if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmInputOutputControlByIdentifier(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) rxData;

  /* Get the pointer to the request data buffer of pMsgContext */
  rxData = pMsgContext->reqData;
  Dcm_GucInOutParameter = rxData[2U];
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  

  if (pMsgContext->reqDataLen < 3U)
  {
    /* Report the Incorrect Message Length NRC */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else if (Dcm_GucInOutParameter > 3U)
  {
    /* Report the Request out of range NRC */
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
  }
  else
  {
    uint16 DidIndex = 0U;
    uint16 dataIdentifier;
  
    /* Update Identifier from the request buffer */
    dataIdentifier = ((uint16)rxData[0U]) << (uint16)8U;
    dataIdentifier = dataIdentifier | (uint16)rxData[1U];

    /* Check if requested DID is valid or not */
    Dcm_GddNegRespError = Dcm_DspValidateInputOutputDid(dataIdentifier, &DidIndex);

    if((Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE) && 
       (DidIndex < Dcm_Num_Of_DidParaConfig))
    {
      P2CONST(Dcm_DIDInfoType, AUTOMATIC, DCM_APPL_CONST) cfgDidInfo = Dcm_GaaDIDParaConfig[DidIndex].pDidInfo;      

      /* calculate the number of control mask : if numOfSignal is zero , controlEnableMaskRecord is zero */
      uint32 numOfcontrolEnableMaskRecord = 0;
      if (Dcm_GaaDIDParaConfig[DidIndex].ucDcmDspSignalCount > 1U) 
      {
        numOfcontrolEnableMaskRecord = ((uint32)Dcm_GaaDIDParaConfig[DidIndex].ucDcmDspSignalCount + 7)/8; 
      }

      /* ISO 14229 Figure 24, page 257
       * If  IOCP  ==  shortTermAdjustment,
       * 1 byte SI + 2 byte DID + 1 byte IOCP + nth byte controlState + nth byte controlMask (if applicable),
       *
       * If IOCP != shortTermAdjustment,
       * 1 byte SI + 2 byte DID + 1 byte IOCP + nth byte controlMask (if applicable)
       */      
      if (DCM_CTRL_SHRT_TRM_ADJ == Dcm_GucInOutParameter)
      {
        uint16 minDidLength = 0u;
        uint16 maxDidLength = 0u;
      
        Dcm_DspInternal_GetSizeOfDid((const Dcm_DIDParaConfig *)&Dcm_GaaDIDParaConfig[DidIndex], &minDidLength, &maxDidLength);    
        minDidLength = (minDidLength + 7) / 8;
        maxDidLength = (maxDidLength + 7) / 8;

        /* if signal is one, controlEnableMaskRecord in the req msg is 0 bytes 
         * 3U = 2 Bytes (DID) + 1 Byte (inputOutputControlParameter)
         */
        if 
        ( /* min <= length <= max */
          (pMsgContext->reqDataLen < (Dcm_MsgLenType)( (uint32)3U+(uint32)minDidLength+(uint32)numOfcontrolEnableMaskRecord)) ||
          (pMsgContext->reqDataLen > (Dcm_MsgLenType)( (uint32)3U+(uint32)maxDidLength+(uint32)numOfcontrolEnableMaskRecord))
        )
        {
          /* Report the Incorrect Message Length NRC */
          Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
      }
      else /*if (
        (DCM_CTRL_RET_CTRL_ECU == inputOutputControlParameter) ||
        (DCM_CTRL_RST_TO_DFLT == inputOutputControlParameter) ||
        (DCM_CTRL_FRZ_CUR_STATE == inputOutputControlParameter) 
      ) */
      {
        if (pMsgContext->reqDataLen != (Dcm_MsgLenType)((uint32)3U + (uint32)numOfcontrolEnableMaskRecord))
        {
          /* Report the Incorrect Message Length NRC */
          Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
      }      

      if (Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE)
      {
        if ((NULL_PTR == cfgDidInfo) ||
           (NULL_PTR == cfgDidInfo->pDidControl))
        {
          Dcm_GddNegRespError = DCM_E_GENERALREJECT;
        }
        else
        {  
          /* polyspace:<RTE: NIP : Not a defect : No Action Planned > pointer is not null */
          P2CONST(Dcm_DIDInfoTypeDidCtrl, AUTOMATIC, DCM_APPL_CONST) cfgControl = cfgDidInfo->pDidControl;
        
          if ( 
            ((DCM_CTRL_SHRT_TRM_ADJ == Dcm_GucInOutParameter) && (DCM_FALSE == cfgControl->blShrtTermAdj)) ||
            ((DCM_CTRL_RET_CTRL_ECU == Dcm_GucInOutParameter) && (DCM_FALSE == cfgControl->blRetCtrlToEcu)) ||
            ((DCM_CTRL_RST_TO_DFLT == Dcm_GucInOutParameter) && (DCM_FALSE == cfgControl->blResetToDefault)) ||
            ((DCM_CTRL_FRZ_CUR_STATE == Dcm_GucInOutParameter) && (DCM_FALSE == cfgControl->blFreezeCrntState))
          )
          {
            Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
          }
          else
          {
            (void)Dcm_DspInternal_DcmInputOutputControlByIdentifier(
              DCM_INITIAL, Dcm_GucInOutParameter, (const Dcm_DIDParaConfig *)&Dcm_GaaDIDParaConfig[DidIndex], pMsgContext);
          }
        }
      }
    }
  }
  
  if ((Dcm_ServicePendingStatus.ucIocontrolPendingStatus == DCM_FALSE) && 
      (Dcm_ServicePendingStatus.ucCheckReadPendingStatus == DCM_FALSE) && 
      (Dcm_ServicePendingStatus.ucReadDataPendingStatus == DCM_FALSE))
  {
    /* Check if the negative response needs to be updated here */
    if (Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE)
    {
      /* Report the NRC to the DSD layer */
      Dcm_InternalSetNegResponse(pMsgContext, Dcm_GddNegRespError);
    }
    else
    {
      pMsgContext->resDataLen = pMsgContext->resDataLen + 3U;
      /* Update First Byte DID */
      pMsgContext->resData[0U] = rxData[0U];
      /* Update Second Byte DID */
      pMsgContext->resData[1U] = rxData[1U];
      /* Update Third Byte inputOutputControlParameter*/
      pMsgContext->resData[2U] = rxData[2U];
    }
    Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
    Dcm_ResetDIDOpStatus();
  }

  /* TODO: return value shall be processed */

  DCM_UNUSED(OpStatus);
  
  return E_OK;  
}

static 
FUNC(void, DCM_CODE)  Dcm_DspInternal_UnpackSignal(
  P2CONST(Dcm_DIDUnPackSignal, AUTOMATIC, DCM_APPL_DATA)  aCfgUnpackSignal,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) aInputBuffer,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) anOutputBuffer)
{
  Dcm_PackUnpackSignalData unpackSignal; 

  unpackSignal.ucShiftBits = aCfgUnpackSignal->ucNoOfShiftBits;
  unpackSignal.ucEndMask = aCfgUnpackSignal->ucEndMask;
  unpackSignal.ucSignalType = aCfgUnpackSignal->ucSignalType;
  unpackSignal.ucSignalSize = aCfgUnpackSignal->ucSignalSize;
  unpackSignal.ucSignMask = 0U;
  unpackSignal.ucSignalTypeorSize = 0U;
  unpackSignal.ucStartMask = 0U;
  
  if(aCfgUnpackSignal->ucSignalType == DCM_DATA_TYPE_CSIF_GT32)
  {
    unpackSignal.ulSignalLength = aCfgUnpackSignal->ulSignalLength;
  }
  else
  {
    unpackSignal.ulSignalLength = 0U;
  }

  if(aCfgUnpackSignal->ucRdFuncIndex < Dcm_Num_Of_SigRdFuncPtr)
  {
    if (NULL_PTR != Dcm_GaaSigRdFuncPtr[aCfgUnpackSignal->ucRdFuncIndex].pRdFuncPtr)
    {
      Dcm_GaaSigRdFuncPtr[aCfgUnpackSignal->ucRdFuncIndex].pRdFuncPtr(
        unpackSignal,aInputBuffer,anOutputBuffer);    
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_IOControlResetToDefault             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x2F   **
**                        for the four input output control parameters        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : anOpStatus,aCfgData,aDataLength,                    **
**                        aNegResponceCode                                    **  
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
*******************************************************************************/
#if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOControlResetToDefault(
  Dcm_OpStatusType anOpStatus,  
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,  
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) aNegResponceCode)  
{
  Std_ReturnType retVal = E_NOT_OK;

  if ((NULL_PTR != aCfgData) && (NULL_PTR != aNegResponceCode))
  {
  
    *aNegResponceCode = DCM_E_POSITIVERESPONSE;
    
    /*Check which interface shall be used to access the data*/
    switch(aCfgData->ucDcmDspDataUsePort)
    {
      /* [constr_6019]  
       * DcmDspData elements used in service 0x2F shall not have 
       * DcmDspDataUsePorts set to USE_DATA_SENDER_RECEIVER */    
      case DCM_USE_DATA_ASYNCH_FNC:
      case DCM_USE_DATA_ASYNCH_CLIENT_SERVER:
        if (NULL_PTR != aCfgData->pResetToDefaultAsync)
        {
          retVal = aCfgData->pResetToDefaultAsync(anOpStatus, aNegResponceCode);
        }
        break;
        
      case DCM_USE_DATA_SYNCH_FNC:
      case DCM_USE_DATA_SYNCH_CLIENT_SERVER:        
        if (NULL_PTR != aCfgData->pResetToDefaultSync)
        {
          retVal = aCfgData->pResetToDefaultSync(aNegResponceCode);
        }
        break;

      case DCM_USEECUSIGNAL:     
          retVal = Dcm_CfgInternal_IOControlSigTypeEcuSignal(aCfgData, DCM_CTRL_RST_TO_DFLT,NULL_PTR, aNegResponceCode);
          break;
      default:
        /* Do Nothing */
        break;
    } 
  }

  if((E_NOT_OK == retVal) && (DCM_E_POSITIVERESPONSE == *aNegResponceCode))
  {
    *aNegResponceCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  
  return retVal;

}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_IOControlFreezeCurrentState         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x2F   **
**                        for the four input output control parameters        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : anOpStatus,aCfgData,aDataLength,                    **
**                        aNegResponceCode                                    **  
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
*******************************************************************************/
#if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOControlFreezeCurrentState(
  Dcm_OpStatusType anOpStatus,  
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,  
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) aNegResponceCode)
{
  Std_ReturnType retVal = E_NOT_OK;

  if ((NULL_PTR != aCfgData) && (NULL_PTR != aNegResponceCode))
  {
    *aNegResponceCode = DCM_E_POSITIVERESPONSE;
  
    /*Check which interface shall be used to access the data*/
    switch(aCfgData->ucDcmDspDataUsePort)
    {
      /* [constr_6019]  
       * DcmDspData elements used in service 0x2F shall not have 
       * DcmDspDataUsePorts set to USE_DATA_SENDER_RECEIVER */    
      case DCM_USE_DATA_ASYNCH_FNC:
      case DCM_USE_DATA_ASYNCH_CLIENT_SERVER:
        if (NULL_PTR != aCfgData->pFreezeCurrentStateAsync)
        {
          retVal = aCfgData->pFreezeCurrentStateAsync(anOpStatus, aNegResponceCode);
        }
        break;

      case DCM_USE_DATA_SYNCH_FNC:
      case DCM_USE_DATA_SYNCH_CLIENT_SERVER:
        if (NULL_PTR != aCfgData->pFreezeCurrentStateSync)
        {
          retVal = aCfgData->pFreezeCurrentStateSync(aNegResponceCode);
        }
        break;

      case DCM_USEECUSIGNAL:     
          retVal = Dcm_CfgInternal_IOControlSigTypeEcuSignal(aCfgData,DCM_CTRL_FRZ_CUR_STATE,NULL_PTR,aNegResponceCode);
          break;
      default:
        /* Do Nothing */
        break;
    } 
  }

  if((E_NOT_OK == retVal) && (DCM_E_POSITIVERESPONSE == *aNegResponceCode))
  {
    *aNegResponceCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  
  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_IOControlReturnControlToECU         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x2F   **
**                        for the four input output control parameters        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : anOpStatus,aCfgData,aDataLength,                    **
**                        aNegResponceCode                                    **  
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
*******************************************************************************/
#if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOControlReturnControlToECU(
  Dcm_OpStatusType anOpStatus,  
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,  
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) aNegResponceCode)  
{
  Std_ReturnType retVal = E_NOT_OK;
  *aNegResponceCode = DCM_E_POSITIVERESPONSE;

  if ((NULL_PTR != aCfgData) && (NULL_PTR != aNegResponceCode))
  {    
    /*Check which interface shall be used to access the data*/
    switch(aCfgData->ucDcmDspDataUsePort)
    {
      /* [constr_6019]  
       * DcmDspData elements used in service 0x2F shall not have 
       * DcmDspDataUsePorts set to USE_DATA_SENDER_RECEIVER */
      case DCM_USE_DATA_ASYNCH_FNC:
      case DCM_USE_DATA_ASYNCH_CLIENT_SERVER:
        if (NULL_PTR != aCfgData->pReturnControlToEcuAsync)                    
        {
          retVal = aCfgData->pReturnControlToEcuAsync(anOpStatus, aNegResponceCode);
        }
        break;

      case DCM_USE_DATA_SYNCH_FNC:
      case DCM_USE_DATA_SYNCH_CLIENT_SERVER:
        if (NULL_PTR != aCfgData->pReturnControlToEcuSync)                    
        {
          retVal = aCfgData->pReturnControlToEcuSync(aNegResponceCode);
        }
        break;

      case DCM_USEECUSIGNAL:     
          retVal = Dcm_CfgInternal_IOControlSigTypeEcuSignal(aCfgData,DCM_CTRL_RET_CTRL_ECU, NULL_PTR, aNegResponceCode);
          break;
      default:
        /* Do Nothing */
        break;
    }  
  }
   /* polyspace +1 DEFECT:NON_INIT_VAR [Justified:Low] "Not a defect" */
  if((E_NOT_OK == retVal) && (DCM_E_POSITIVERESPONSE == *aNegResponceCode))
  {
    *aNegResponceCode = DCM_E_CONDITIONSNOTCORRECT;
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_IOControlFreezeCurrentState         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x2F   **
**                        for the four input output control parameters        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : anOpStatus,aCfgData,aDataLength,aControlOptionRecord**
**                        aNegResponceCode                                    **  
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
*******************************************************************************/
#if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOControlShortTermAdjustment(
  Dcm_OpStatusType anOpStatus,  
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,  
  Dcm_MsgLenType aDataLength,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) aControlOptionRecord,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) aNegResponceCode)  
{
  Std_ReturnType retVal = E_NOT_OK;

  if ((NULL_PTR != aCfgData) && (NULL_PTR != aControlOptionRecord ) && (NULL_PTR != aNegResponceCode))
  {
    *aNegResponceCode = DCM_E_POSITIVERESPONSE;
  
    /*Check which interface shall be used to access the data*/
    switch(aCfgData->ucDcmDspDataUsePort)
    {
      /* [constr_6019]  
       * DcmDspData elements used in service 0x2F shall not have 
       * DcmDspDataUsePorts set to USE_DATA_SENDER_RECEIVER */
      case DCM_USE_DATA_ASYNCH_FNC:
      case DCM_USE_DATA_ASYNCH_CLIENT_SERVER:
        /*  no need check cfgDidControl->blShrtTermAdj */
        if (NULL_PTR != aCfgData->pShortTermAdjustmentFixedAsync)
        {
          retVal = aCfgData->pShortTermAdjustmentFixedAsync(
            aControlOptionRecord, anOpStatus, aNegResponceCode);
        }
        else if (NULL_PTR != aCfgData->pShortTermAdjustmentVarAsync)
        {
          /* variable length = size of all signal - size of signal with fixed length */
          retVal = aCfgData->pShortTermAdjustmentVarAsync(
            aControlOptionRecord, (uint16)aDataLength , anOpStatus, aNegResponceCode);
        }
        else { }
        break;
        
      case DCM_USE_DATA_SYNCH_FNC:
      case DCM_USE_DATA_SYNCH_CLIENT_SERVER:
        if (NULL_PTR != aCfgData->pShortTermAdjustmentFixedSync)
        {
          retVal = aCfgData->pShortTermAdjustmentFixedSync(aControlOptionRecord, aNegResponceCode);
        }  
        else if (NULL_PTR != aCfgData->pShortTermAdjustmentVarSync)
        {
          /* dataLength =  size of all signal - size of signal with fixed length */ 
          retVal = aCfgData->pShortTermAdjustmentVarSync(aControlOptionRecord, (uint16)aDataLength, aNegResponceCode);
        }
        else  { }
        break;
        
      case DCM_USEECUSIGNAL:     
          retVal = Dcm_CfgInternal_IOControlSigTypeEcuSignal(
            aCfgData, DCM_CTRL_SHRT_TRM_ADJ, aControlOptionRecord, aNegResponceCode);
          break;
          
      default:
        /* Do Nothing */
        break;
    }      
  }

  if((E_NOT_OK == retVal) && (DCM_E_POSITIVERESPONSE == *aNegResponceCode))
  {
    *aNegResponceCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  
  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_DcmInputOutputControlByIdentifier   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x2F   **
**                        for the four input output control parameters        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucCtrlType,LusDIDIndex                             **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DcmInputOutputControlByIdentifier(
  Dcm_OpStatusType anOpStatus,
  uint8 anInputOutputControlParameter, 
  P2CONST(Dcm_DIDParaConfig, AUTOMATIC, DCM_APPL_CONST) aCfgDid,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) aMsgContext)
{
  Std_ReturnType retVal = E_NOT_OK;
  P2CONST(Dcm_DIDInfoType, AUTOMATIC, DCM_APPL_CONST) cfgDidInfo;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) controlEnableMaskRecord;

  uint16 signalIndex = 0U;
  uint16 numOfSignal;
  Dcm_MsgLenType DidLenInBytes;
  uint16 numOfcontrolEnableMaskRecord;

  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  Dcm_ServicePendingStatus.ucIocontrolPendingStatus = DCM_FALSE;

  /* Get signal count for requested DID */
  numOfSignal = aCfgDid->ucDcmDspSignalCount;   
  cfgDidInfo =  aCfgDid->pDidInfo;

  numOfcontrolEnableMaskRecord = 0;
  if (numOfSignal > 1U) 
  {
    numOfcontrolEnableMaskRecord = (numOfSignal + 7)/8;
  }

  /* Bytes of controlEnableMaskRecord is (numOfSignal + 7)/8
   * reqDataLen - (2<DID> + 1<inputOutputControlParameter> + bytes of controlEnableMaskRecord) */
  DidLenInBytes = aMsgContext->reqDataLen - (3U + (Dcm_MsgLenType)numOfcontrolEnableMaskRecord);

  /* reqData[3U + DidLenInBytes + 0] is controlMask#1 in the controlEnableMaskRecord */
  controlEnableMaskRecord = &aMsgContext->reqData[3U + DidLenInBytes];
  
  while ((signalIndex < numOfSignal) &&
         (DCM_E_POSITIVERESPONSE == Dcm_GddNegRespError))
  {
     /********************************************************************
     #1d        | InputOutputControlByIdentifer Request Service ID
     ----------------------------------------------------------------       
     #2d        | dataIdentifier MSB
     #3d        | dataIdentifier LSB
     ----------------------------------------------------------------       
     #4d        | inputOutputControlParameter 
     ----------------------------------------------------------------
     #5d        | controlOptionRecord #2[] = [       
                |            controlState#1 
                |            .. 
     #5+(m-1)d  |            controlState#m 
     ----------------------------------------------------------------
     #5+md      | controlEnableMaskRecord #1[] = [ 
     ..         |            controlMask#1 
     #5+m+(r-1)d|            ..
                |            controlMask#r ]
     ----------------------------------------------------------------                  
     *********************************************************************/
     
    /* Ex) if the bit 7 of the controlMask#1 is set , controlState#1 is valid */ 
    if (
      (numOfSignal == 1U) || 
      (0U != (controlEnableMaskRecord[signalIndex/8U] & ((uint8)( ((uint8)0x80U) >> ((uint8)(signalIndex % 8U)) ))))
    )
    {    
      P2VAR(Dcm_DcmDspSignalconfig, AUTOMATIC, DCM_APPL_DATA) cfgSignal = &aCfgDid->pDcmDspSignal[signalIndex];
      P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST)cfgData = cfgSignal->pDcmDspData;

      /* Check if requested signal data is already read or not and if not then read the data */
      if ((NULL_PTR != cfgData) && (DCM_OPSTATUS_COMPLETE != cfgSignal->ucDidSignalOpStatus))
      {
        Dcm_NegativeResponseCodeType errorCode = DCM_E_POSITIVERESPONSE;
        
        switch (anInputOutputControlParameter)
        {
          /* The DCM shall call the Api IoHwAb_Dcm_<symbolic name of ECU signal (parameter 
           * DcmDspDataEcuSignal)>() with InputOutputControlParameter for the "action"
           * parameter and in case of InputOutputControlParameter is set to 
           * 'shortTermAdjustment' the signal value for the  "signal" parameter. */
          case DCM_CTRL_SHRT_TRM_ADJ:
          {
            P2VAR(void, AUTOMATIC, DCM_APPL_DATA) outUnpackedSigBuffer;
            Dcm_MsgLenType dataLength = 0U;       
            
            Dcm_GaaDIDSignalData[0U] = 0U;    
            outUnpackedSigBuffer = (void*)&Dcm_GaaDIDSignalData[0U];             

            if (NULL_PTR != cfgData->pDataInfo)
            {
              /* Only last signal shall has a data with variable length.
               * So, We assume that this signal is last one. */
              if (DCM_FALSE == cfgData->pDataInfo->blDataFixedLength)
              {
                /* size of reqeusted variable signal is the rest of all fixed signal */
                dataLength = DidLenInBytes - (Dcm_MsgLenType)cfgSignal->usDcmDspDidDataPos;
              }
              else
              {
                dataLength = cfgData->usDcmDspDataSize;
              }                
            }  
            if (0U != dataLength)
            {
              Dcm_MsgLenType offsetReqData = 3U + (Dcm_MsgLenType)cfgSignal->pDidUnPackSignal->ucSignalStartByte;
              P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) inPackedSigBuffer = &aMsgContext->reqData[offsetReqData];
              Dcm_DspInternal_UnpackSignal(cfgSignal->pDidUnPackSignal, inPackedSigBuffer, outUnpackedSigBuffer);
            }

            /* input parameter dataLength is valid , if signal has a data with variable length */
            retVal = Dcm_DspInternal_IOControlShortTermAdjustment(
              anOpStatus, cfgData, dataLength, outUnpackedSigBuffer, &errorCode);
            break;
          }
          case DCM_CTRL_RET_CTRL_ECU: /*  no need to check DidControl */
            retVal = Dcm_DspInternal_IOControlReturnControlToECU(anOpStatus, cfgData, &errorCode);
            break;

          case DCM_CTRL_RST_TO_DFLT: /*  no need to check DidControl */
            retVal = Dcm_DspInternal_IOControlResetToDefault(anOpStatus, cfgData, &errorCode);
            break;

          case DCM_CTRL_FRZ_CUR_STATE: /*  no need to check DidControl */
            retVal = Dcm_DspInternal_IOControlFreezeCurrentState(anOpStatus, cfgData, &errorCode);
            break;
          default:
            /* Do Nothing */
            break;
        }          
        
        if (anOpStatus != DCM_CANCEL)
        {
          if (retVal == E_OK)
          { 
            cfgSignal->ucDidSignalOpStatus = DCM_OPSTATUS_COMPLETE;
          }
          else if (
            (retVal == DCM_E_PENDING) &&          
            (
              (DCM_USE_DATA_ASYNCH_FNC == cfgData->ucDcmDspDataUsePort) ||
              (DCM_USE_DATA_ASYNCH_CLIENT_SERVER== cfgData->ucDcmDspDataUsePort)
            )
          )
          {
            cfgSignal->ucDidSignalOpStatus = DCM_OPSTATUS_PENDING;              
            Dcm_ServicePendingStatus.ucIocontrolPendingStatus = DCM_TRUE;
          }
          else if(retVal == E_NOT_OK)
          {
            Dcm_GddNegRespError = errorCode;
          }
          else
          {
            /* To avoid QAC warning */
          }
        }
      }
    }
    /* Next signal */
    signalIndex++;
  }

  /* TODO : FIXME , Use ReadDidType internal functions */
  if ((Dcm_ServicePendingStatus.ucIocontrolPendingStatus == DCM_FALSE) &&
      (Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE))
  {
    if(Dcm_ServicePendingStatus.ucIoCtrlReadCdtChkPendingStatus == DCM_FALSE)
    {
      Dcm_GusReadDIDCount = DCM_ONE;
      Dcm_GaaReadDid[0U] = aCfgDid->usDcmDspDidIdentifier;
      Dcm_ResetDIDOpStatus();
    }
    /* [SWS_Dcm_00682]  The controlState in the ControlStatusRecord in the positive 
     * response message of for the IoControl service shall be retrieved using the 
     * associated ReadData operation/function/SenderReceiver after applicaton processing 
     * on the IO control request is positively finalized.*/    
    if (NULL_PTR != cfgDidInfo->pDidRead)
    {
      (void)Dcm_DspConditionCheckRead(anOpStatus, aCfgDid);
      if(Dcm_ServicePendingStatus.ucIoCtrlReadCdtChkPendingStatus == DCM_FALSE)
      {
        (void)Dcm_DspReadData(anOpStatus, aMsgContext, aCfgDid);
      }
    }
  }
  
  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_DspConditionCheckRead                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x2F   **
**                        and 0x22 with inputcontrol parameter                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusDIDIndex                                         **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspConditionCheckRead(
  Dcm_OpStatusType anOpStatus,   
  P2CONST(Dcm_DIDParaConfig, AUTOMATIC, DCM_APPL_CONST) aCfgDid)
{
  Std_ReturnType retVal = E_OK;  

  P2VAR(Dcm_DcmDspSignalconfig, AUTOMATIC, DCM_APPL_DATA) cfgSignal = aCfgDid->pDcmDspSignal;
  
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_E_POSITIVERESPONSE;
  uint8 numSignals = aCfgDid->ucDcmDspSignalCount;
  uint8 idxSignal = 0;

  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  Dcm_ServicePendingStatus.ucIoCtrlReadCdtChkPendingStatus = DCM_FALSE;

  while (
    (idxSignal < numSignals) && 
    (Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE)
  )
  { 
    if(cfgSignal->ucDidSignalOpStatus != DCM_OPSTATUS_COMPLETE)
    {
      retVal = Dcm_DspInternal_ConditionCheckRead(anOpStatus, cfgSignal->pDcmDspData, &LddErrorCode);
      if(retVal == DCM_E_PENDING)
      {
        /* TODO only async port shall return pending */
        cfgSignal->ucDidSignalOpStatus = DCM_OPSTATUS_PENDING;        
        Dcm_ServicePendingStatus.ucIoCtrlReadCdtChkPendingStatus = DCM_TRUE;
      }
      else if(retVal == E_NOT_OK)
      {
        Dcm_GddNegRespError = LddErrorCode;
      }
      else
      {
        /* To avoid QAC warning */
      }
    }
    idxSignal++;
    cfgSignal = &cfgSignal[1];
  }
  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_DspReadData                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x2F   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusDIDIndex                                         **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspReadData(
  Dcm_OpStatusType anOpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2CONST(Dcm_DIDParaConfig, AUTOMATIC, DCM_APPL_CONST) aCfgDid)
{
  P2VAR(Dcm_DcmDspSignalconfig, AUTOMATIC, DCM_APPL_DATA)LpDcmDspSignal;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpResponseData;
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST)LpDcmDspData;
  P2CONST(Dcm_DIDPackSignal, AUTOMATIC, DCM_APPL_CONST)LpPackSignalConfig;
  P2CONST(Dcm_DataInfoType, AUTOMATIC, DCM_APPL_CONST)LpDidInfo;
  Dcm_PackUnpackSignalData LddPackSignal;
  Std_ReturnType LddReturnValue;
  uint16 LusDIDsize;
  uint16 LusDIDBitsize;
  uint8 LucSignalCount;
  uint8 LucIndex;
  uint8 LucSignalType;
  boolean LblSignFlag;

  LddReturnValue = E_OK;
  LusDIDsize = DCM_ZERO;
  LblSignFlag = DCM_FALSE;
  LusDIDBitsize = DCM_ZERO;

  /* Set response pending flag to False */
  Dcm_MemServicePendingStatus.ucIoCtrlReadDataPendingStatus = DCM_FALSE;

  /*Initialize pointer to get the parameters of requested DID */
  LucSignalCount = aCfgDid->ucDcmDspSignalCount;
  LpDcmDspSignal = aCfgDid->pDcmDspSignal;
  /* LpDcmDspData = LpDcmDspSignal->pDcmDspData;
  LpPackSignalConfig = LpDcmDspSignal->pDidPackSignal; */

  LucIndex = DCM_ZERO;
  while((LucIndex < LucSignalCount) && (Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE))
  { 
    if((NULL_PTR != LpDcmDspSignal) && 
       (NULL_PTR != LpDcmDspSignal->pDidPackSignal) && 
       (NULL_PTR != LpDcmDspSignal->pDcmDspData))
    {
      LpDcmDspData = LpDcmDspSignal->pDcmDspData;
      LpPackSignalConfig = LpDcmDspSignal->pDidPackSignal;
  
      if ((DCM_OPSTATUS_COMPLETE != LpDcmDspSignal->ucDidSignalOpStatus) && 
          (NULL_PTR != LpDcmDspData->pDataInfo))
      {
        LpDidInfo = LpDcmDspData->pDataInfo;
        LddReturnValue = E_OK;
        if (LpDidInfo->blDataFixedLength == DCM_FALSE)
        {        
          if 
          (
            (
              (LpDcmDspData->ucDcmDspDataUsePort == DCM_USE_DATA_ASYNCH_FNC) ||
              (LpDcmDspData->ucDcmDspDataUsePort == DCM_USE_DATA_ASYNCH_CLIENT_SERVER)
            ) &&
            (LpDcmDspData->pReadDataLengthAsync != NULL_PTR)
          )
          {
            LddReturnValue = LpDcmDspData->pReadDataLengthAsync(anOpStatus, &LusDIDsize);          
            LusDIDBitsize = LusDIDsize * DCM_EIGHT;
          }
          else if 
          (
            (
              (LpDcmDspData->ucDcmDspDataUsePort == DCM_USE_DATA_SYNCH_FNC) ||
              (LpDcmDspData->ucDcmDspDataUsePort == DCM_USE_DATA_SYNCH_CLIENT_SERVER)
            ) &&
            (LpDcmDspData->pReadDataLengthSync != NULL_PTR)
          )
          {
            LddReturnValue = LpDcmDspData->pReadDataLengthSync(&LusDIDsize);         
            LusDIDBitsize = LusDIDsize * DCM_EIGHT;
          }
          else
          {
            LddReturnValue = E_NOT_OK;
            /* TODO : Det Error*/
          }
        }
        else
        {
          /* bits per 1 byte = 8 */
          if(LpDcmDspData->usDcmDspDataSize <= 8U)
          {
            LusDIDsize = DCM_HI_NIBBLE(LpPackSignalConfig->ucSignalTypeorSize, uint16);
            LusDIDsize = DCM_8B_ALIGN(LusDIDsize);
            LusDIDBitsize = LpDcmDspData->usDcmDspDataSize;
          }
          else
          {
            LusDIDBitsize = LpDcmDspData->usDcmDspDataSize;
            LusDIDsize = DCM_8B_ALIGN(LusDIDBitsize);
          }
        }
        
        /* LusResDataLength += LusDIDsize; */
  
        /* Note: S/R is not configured  by generator*/
        if ((0U != LusDIDsize) && (LddReturnValue == E_OK))
        {
          LddReturnValue = Dcm_DspInternal_ReadSigType(anOpStatus, LpDcmDspData, &Dcm_GaaDIDSignalOutData[DCM_ZERO]);
        } 
      }
  
      if (LddReturnValue == E_OK)
      {
        LpDcmDspSignal->ucDidSignalOpStatus = DCM_OPSTATUS_COMPLETE;
        if (0U != LusDIDsize)
        {
          LucSignalType = ((LpPackSignalConfig->ucSignalTypeorSize >> DCM_FOUR) & DCM_SIG_BYTE_MASK_VALUE);
  
          /* for initialization */
          LddPackSignal.ulSignalLength = (uint32)0x00;
          LddPackSignal.ucShiftBits = (uint8)0x00;
          LddPackSignal.ucStartMask = (uint8)0x00;
          LddPackSignal.ucEndMask = (uint8)0x00;
          LddPackSignal.ucSignalType = (uint8)0x00;
          LddPackSignal.ucSignalTypeorSize = (uint8)0x00;
          LddPackSignal.ucSignalSize = (uint8)0x00;
          LddPackSignal.ucSignMask = (uint8)0x00;
  
          if(LusDIDBitsize == LpDcmDspData->usDcmDspDataSize)
          {
            LddPackSignal.ucShiftBits = LpPackSignalConfig->ucNoOfShiftBits;
            LddPackSignal.ucStartMask = LpPackSignalConfig->ucStartMask;
            LddPackSignal.ucEndMask = LpPackSignalConfig->ucEndMask;
            LddPackSignal.ucSignalType = LucSignalType;
            LddPackSignal.ucSignalTypeorSize = LpPackSignalConfig->ucSignalTypeorSize;
          }
          else
          {
            if((LpDcmDspData->ucDcmDspDataType == DCM_DSP_DATA_TYPE_SINT8) ||
             (LpDcmDspData->ucDcmDspDataType  == DCM_DSP_DATA_TYPE_SINT16) ||
             (LpDcmDspData->ucDcmDspDataType  == DCM_DSP_DATA_TYPE_SINT32))
            {
              LblSignFlag = DCM_TRUE;
            }
             Dcm_DspCalculateSignalPackParameters(&LddPackSignal,
              LpDcmDspSignal->usDcmDspDidDataPos, LusDIDBitsize,
              LpPackSignalConfig->ucSignalStartByte, LblSignFlag);
            
             LddPackSignal.ucSignalTypeorSize =
              ((LpPackSignalConfig->ucSignalTypeorSize & DCM_SIG_SIZE_MASK_VALUE) |
              (LddPackSignal.ucSignalSize));
          }
  
          LddPackSignal.ulSignalLength = LusDIDsize;
          LpResponseData = &pMsgContext->resData[DCM_THREE +
                                                 (LpPackSignalConfig->ucSignalStartByte)];
  
          /*  for Outof bound -0424 bsh*/
          if (
            (LpPackSignalConfig->ucWrFuncIndex < Dcm_Num_Of_SigWrFuncPtr) &&
            (NULL_PTR != Dcm_GaaSigWrFuncPtr[LpPackSignalConfig->ucWrFuncIndex].pWrFuncPtr)
          )
          {
            /* sg.baek 022705 - Task #2226 in redmine */        
            Dcm_GaaSigWrFuncPtr[LpPackSignalConfig->ucWrFuncIndex].pWrFuncPtr
                  (LddPackSignal, LpResponseData, &Dcm_GaaDIDSignalOutData[DCM_ZERO]);      
        
            /* pMsgContext->resDataLen = LusResDataLength; */
            pMsgContext->resDataLen += LusDIDsize;
          }
          else
          {
            /* For Misra-C check */
            Dcm_GddNegRespError = DCM_E_GENERALREJECT;
          }
        }
      }
      else if(LddReturnValue == DCM_E_PENDING)
      {
        /* Set response pending flag to True */
        Dcm_MemServicePendingStatus.ucIoCtrlReadDataPendingStatus = DCM_TRUE;
        LpDcmDspSignal->ucDidSignalOpStatus = DCM_OPSTATUS_PENDING;
      }
      else
      {
        Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;    
      }
    }
    else
    {
      DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID,DCM_E_PARAM);
    }
    
    LucIndex++;
    LpDcmDspSignal = &LpDcmDspSignal[1];
  }

  return LddReturnValue;
}

/*******************************************************************************
** Function Name        : Dcm_DspReturnControlToEcu                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x2F   **
**                        with inputcontrol parameter ReturnCOntrolToECU      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DspReturnControlToEcu(void)
{
  P2CONST(Dcm_DIDParaConfig, AUTOMATIC, DCM_APPL_CONST) cfgDID;
  P2CONST(Dcm_DcmDspSignalconfig, AUTOMATIC, DCM_APPL_CONST) cfgSignal;
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) cfgData;
  P2CONST(Dcm_DIDInfoType, AUTOMATIC, DCM_APPL_CONST) cfgDidInfo;

  Dcm_NegativeResponseCodeType LddErrorCode;
  uint16 idx;

  for(idx = DCM_ZERO; idx < Dcm_Total_Num_Of_Static_DID; idx++)
  {
    /*Initialize pointer to get the parameters of requested DID */
    cfgDID = &Dcm_GaaDIDParaConfig[idx];
    
    /*Get the position of the data defined by DcmDspDidDataRef*/
    cfgSignal = cfgDID->pDcmDspSignal;
    cfgData = cfgSignal->pDcmDspData;

    /*Get the configuration of Data's*/
    cfgDidInfo = cfgDID->pDidInfo;
    if(cfgDidInfo->pDidControl != NULL_PTR)
    {            
      (void)Dcm_DspInternal_IOControlReturnControlToECU(DCM_INITIAL, cfgData, &LddErrorCode);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_DspValidateInputOutputDid                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to validate IO service        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusDataIdentifier                                   **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : LpDIDIndex                                          **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GusDIDIndexVal            **
**                        Dcm_GaaDIDParaConfig, Dcm_GaaModeRuleConfig,        **
**                        Dcm_GddNegRespError                                 **
**                        Function(s) invoked :                               **
**                        Dcm_DsdValidateSession, Dcm_DsdValidateSecurity,    **
**                        Dcm_DsdModeRuleCheck                                **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspValidateInputOutputDid(
  uint16 LusDataIdentifier,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpDIDIndex)
{
  #if((DCM_MODE_RULE  ==  STD_ON) && (DCM_DSP_MODE_RULE_NRC == STD_ON))
  P2CONST(Dcm_ModeRuleConfigType,  AUTOMATIC,  DCM_APPL_CONST)
  LpModeRule;
  #endif
  uint16 LusDIDIndex = (uint16)0x00;
  Dcm_NegativeResponseCodeType LddErrorCode;
  boolean LblSearchResult;

  LddErrorCode = DCM_E_POSITIVERESPONSE;

  /* Check if the DID from the request is supported */
  LblSearchResult = Dcm_IDSearch(DCM_GET_DID, LusDataIdentifier,
      &LusDIDIndex);

  Dcm_GusDIDIndexVal =  LusDIDIndex;

  *LpDIDIndex = LusDIDIndex;

  if(LblSearchResult == DCM_TRUE)
  {
    if((Dcm_GaaDIDParaConfig[LusDIDIndex].blDspDidUsed == DCM_TRUE) &&
       (Dcm_GaaDIDParaConfig[LusDIDIndex].pDidInfo != NULL_PTR) &&
       (Dcm_GaaDIDParaConfig[LusDIDIndex].pDidInfo->pDidControl != NULL_PTR))
    {
      if(Dcm_GaaDIDParaConfig[LusDIDIndex].pDidInfo->pDidControl->pDidCtrlSession != NULL_PTR)
      {
        /*Invoke function for session validation*/
        LblSearchResult = Dcm_DsdValidateSession(
            Dcm_GaaDIDParaConfig[LusDIDIndex].pDidInfo->pDidControl->pDidCtrlSession,
            Dcm_GaaDIDParaConfig[LusDIDIndex].pDidInfo->pDidControl->ucDidCtrlSesCount);
      }

      if(LblSearchResult == DCM_TRUE)
      {
        if(Dcm_GaaDIDParaConfig[LusDIDIndex].pDidInfo->pDidControl->pDidCtrlSecurity != NULL_PTR)
        {
          /*Invoke function for security validation*/
          LblSearchResult = Dcm_DsdValidateSecurity(
              Dcm_GaaDIDParaConfig[LusDIDIndex].pDidInfo->pDidControl->pDidCtrlSecurity, 
              Dcm_GaaDIDParaConfig[LusDIDIndex].pDidInfo->pDidControl->ucDidCtrlSecCount);
        }

        if(LblSearchResult == DCM_TRUE)
        {
          #if(DCM_MODE_RULE  ==  STD_ON)
          if(Dcm_GaaDIDParaConfig[LusDIDIndex].pDidInfo->pDidControl->blModeRuleConfigured == DCM_TRUE)
          {
            LblSearchResult  =  Dcm_DsdModeRuleCheck
                (Dcm_GaaDIDParaConfig[LusDIDIndex].pDidInfo->pDidControl->ucDIDmoderuleArrayindex);
          }
          if(LblSearchResult == DCM_FALSE)
          {
            #if(DCM_DSP_MODE_RULE_NRC == STD_ON)
            LpModeRule =
                &Dcm_GaaModeRuleConfig[Dcm_GaaDIDParaConfig[LusDIDIndex].pDidInfo->pDidControl->ucDIDmoderuleArrayindex];
            LddErrorCode = LpModeRule->ucNRCType;
            #else
            /* Update Negative Response Code */
            LddErrorCode  =  DCM_E_CONDITIONSNOTCORRECT;
            #endif
          }
          #endif
        }
        else
        {
          /* Security not supported in active session */
          LddErrorCode = DCM_E_SECURITYACCESSDENIED;
        }
      }
      else
      {
        /* Report the Request out of range NRC */
        LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
      }
    }
    else
    {
      /* Report the Request out of range NRC */
      LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
    }
  }
  else
  {
    /* Report the Request out of range NRC */
    LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
  }
  return(LddErrorCode);
}

/*******************************************************************************
** Function Name        : Dcm_DspCalculateSignalPackParameters                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal function for service InputOutputControl by **
**                        Identifier                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusSignalBitPosition,LusDIDsize,LucSignalStartByte, **
**                        LblSignFlag                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : LpPackSignal                                        **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : Dcm_DspCalculateBitPosition,  **
**                        Dcm_DspCalShiftBitAndStartMask,                     **
**                        Dcm_DspCalculateEndMask                             **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_DspCalculateSignalPackParameters(
  P2VAR(Dcm_PackUnpackSignalData, AUTOMATIC, DCM_APPL_DATA)LpPackSignal,
  uint16 LusSignalBitPosition, uint16 LusDIDsize, uint8 LucSignalStartByte,
  boolean LblSignFlag)
{
  uint16 LusNewOffset;
  uint16 LusOffset;
  uint16 LusSignalEndByte;
  uint8 LucShiftBits;
  uint8 LucStartMask;
  boolean LblBigEndian;

  LusOffset = LusSignalBitPosition;

  /* Check if the endianness configured is little endian or big endian */
  if((LusOffset / DCM_EIGHT) == LucSignalStartByte)
  {
    LblBigEndian = DCM_FALSE;
  }
  else
  {
    LblBigEndian = DCM_TRUE;
  }

  /* Calculate the offset position for the new data size */
  if(LblBigEndian == DCM_TRUE)
  {
    LusNewOffset = Dcm_DspCalculateBitPosition(LusOffset, LusDIDsize);

    LusOffset = LusNewOffset;
  }
  /* Invoke the function to calculate the shift bit,
  start mask and end mask for the
   new signal size */
  Dcm_DspCalShiftBitAndStartMask
  (LusOffset, LusDIDsize, &LucShiftBits, &LucStartMask);

  LpPackSignal->ucShiftBits = LucShiftBits;

  LpPackSignal->ucStartMask = LucStartMask;

  LpPackSignal->ucEndMask =
      Dcm_DspCalculateEndMask(LusOffset, LusDIDsize, LblSignFlag);

  if((LusOffset % DCM_EIGHT) ==
      (((LusOffset+ LusDIDsize) - DCM_ONE) % DCM_EIGHT))
  {
    LpPackSignal->ucSignalSize = DCM_ONE;
  }
  else
  {
    LusSignalEndByte = (uint16)
          (((LusOffset+ LusDIDsize) - DCM_ONE) / DCM_EIGHT);

    LpPackSignal->ucSignalSize =
        (uint8)(LusSignalEndByte - LucSignalStartByte) + DCM_ONE;
  }
}

/*******************************************************************************
** Function Name        : Dcm_DspCalculateEndMask                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal function for service InputOutputControl by **
**                        Identifier                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusSignalOffset,LusSignalSize,LblSignFlag           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LucEndMask                                          **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
static FUNC(uint8, DCM_CODE) Dcm_DspCalculateEndMask(
  uint16 LusSignalOffset,
  uint16 LusSignalSize, boolean LblSignFlag)
{
  uint16 LusTemp;
  uint16 LusTemp1;
  uint16 LusOffset;
  uint16 LusSize;
  uint8 LucEndMask;
  LusOffset = LusSignalOffset;
  LusSize = LusSignalSize;

  if (LblSignFlag == DCM_ONE)
  {
    /* If the size of Signal is exactly integer multiple of 8 and the Signal
     offset is exactly integer multiple of 8 then return
     read. For such Signals MASK is 0xFF and right shift number bytes = 0 */
    if(((LusSize % DCM_EIGHT) == DCM_ZERO) &&
        ((LusOffset % DCM_EIGHT) == DCM_ZERO))
    {
      LucEndMask = DCM_ZERO;
    }
    else
    {
      /* Check whether the whole Signal is present in the same byte
        in the frame */
      if((LusOffset / DCM_EIGHT) ==
          (((LusOffset - DCM_ONE) + LusSize) / DCM_EIGHT))
      {
        LusOffset %= DCM_EIGHT;
      }
      else
      {
        LusOffset %= DCM_EIGHT;
        LusSize = (LusSize + LusOffset) % DCM_EIGHT;
        if (LusSize == DCM_ZERO)
        {
          LusSize = DCM_EIGHT;
        }
        LusOffset = DCM_ZERO;
      }

      LusSize += LusOffset;
      LusTemp = DCM_ONE;

      while(LusSize > DCM_ZERO)
      {
        LusTemp = LusTemp * DCM_TWO;
        LusSize--;
      }

      LusTemp1 = DCM_ONE;

      while(LusOffset > DCM_ZERO)
      {
        LusTemp1 = LusTemp1 * DCM_TWO;
        LusOffset--;
      }

      /* Convert the mask value into hex and
        return RightShiftOrNumberOfBytes and  Mask */
      if((LusTemp >= LusTemp1) &&
         ((LusTemp - LusTemp1) <= 0xFFU))
      {
        LucEndMask = (uint8)(LusTemp - LusTemp1);
      }
      else
      {
        // Call Det report
      }
    }
  }
  else
  {
    /* If the size of Signal is exactly integer multiple of 8 and the Signal
      offset is exactly integer multiple of 8 then return
      read. For such Signals MASK is 0xFF and right shift number bytes = 0. */

    if(((LusSize % DCM_EIGHT) == DCM_ZERO) &&
        ((LusOffset % DCM_EIGHT) == DCM_ZERO))
    {
      LucEndMask = DCM_MAXVALUE;
    }

    else
    {
      /* Check whether the whole Signal is present
        in the same byte in the frame */
      if((LusOffset / DCM_EIGHT) ==
          (((LusOffset - DCM_ONE) + LusSize) / DCM_EIGHT))
      {
        LusOffset %= DCM_EIGHT;
      }
      else
      {
        LusOffset %= DCM_EIGHT;
        LusSize = (LusSize + LusOffset) % DCM_EIGHT;

        if (LusSize == DCM_ZERO)
        {
          LusSize = DCM_EIGHT;
        }
        LusOffset = DCM_ZERO;
      }

      LusSize += LusOffset;
      LusTemp = DCM_ONE;

      while(LusSize > (uint16)DCM_ZERO)
      {
        LusTemp = LusTemp * DCM_TWO;
        LusSize--;
      }

      LusTemp1 = DCM_ONE;

      while(LusOffset > DCM_ZERO)
      {
        LusTemp1 = LusTemp1 * DCM_TWO;
        LusOffset--;
      }
      if((LusTemp >= LusTemp1) &&
         ((LusTemp - LusTemp1) <= 0xFFU))
      {
        LucEndMask = (uint8)(LusTemp - LusTemp1);
      }
      else
      {
        // Call Det report
      }
    }
  }
  return (LucEndMask);
}

/*******************************************************************************
** Function Name        : Dcm_DspCalShiftBitAndStartMask                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal function for service InputOutputControl by **
**                        Identifier                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusSignalOffset,LusSignalSize                       **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : LucShiftBits,LucStartMask                           **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_DspCalShiftBitAndStartMask(
  uint16 LusSignalOffset, uint16 LusSignalSize,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)LucShiftBits,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)LucStartMask)
{
  uint16 LusTemp;
  uint16 LusTemp1;
  uint16 LusOffset;
  uint16 LusSize;

  LusOffset = LusSignalOffset;
  LusSize = LusSignalSize;

  /* If the size of Signal is exactly integer multiple of 8 and the Signal
     offset is exactly integer multiple of 8 then return
     read. For such Signals MASK is 0xFF and RightShiftOrNumberOfBytes = 0 */
  if(((LusSize % DCM_EIGHT) == DCM_ZERO) &&
      ((LusOffset % DCM_EIGHT) == DCM_ZERO))
  {
    *LucShiftBits = DCM_ZERO;
    *LucStartMask = DCM_MAXVALUE;
  }
  else
  {
    /* Check whether the whole Signal is present
      in the same byte in the frame */
    if((LusOffset / DCM_EIGHT) ==
        (((LusOffset - DCM_ONE) + LusSize) / DCM_EIGHT))
    {
      LusOffset %= DCM_EIGHT;
    }

    else
    {
      LusOffset %= DCM_EIGHT;
      LusSize = DCM_EIGHT - LusOffset;
    }
    *LucShiftBits = (uint8)LusOffset;

    LusSize += LusOffset;
    LusTemp = DCM_ONE;

    while(LusSize >DCM_ZERO)
    {
      LusTemp = LusTemp * DCM_TWO;
      LusSize--;
    }

    LusTemp1 = DCM_ONE;
    while(LusOffset > DCM_ZERO)
    {
      LusTemp1 = LusTemp1 * DCM_TWO;
      LusOffset--;
    }

    /* Convert the mask value into hex and return RightShiftOrNumberOfBytes and
      Mask */
    if((LusTemp >= LusTemp1) &&
       ((LusTemp - LusTemp1) <= 0xFFU))
    {
      *LucStartMask = (uint8)(LusTemp - LusTemp1);
    }
    else
    {
      #if(DCM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(DCM_MODULE_ID, DCM_INSTANCE_ID,
      DCM_MAIN_FUNCTION_SID,  DCM_E_PARAM);
      #endif
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_DspCalculateBitPosition                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal function for service InputOutputControl by **
**                        Identifier                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusSignalOffset,LusSignalSize                       **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LusSignalOffset                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
static FUNC(uint16, DCM_CODE) Dcm_DspCalculateBitPosition(
  uint16 LusSignalOffset, uint16 LusSignalSize)
{
  uint16 LusLeastBit;
  uint16 LusMaximumBit;
  uint16 LusSize;
  uint16 LusCount;

  LusCount = DCM_ONE;
  LusSize = LusSignalSize;
  LusLeastBit  = LusSignalOffset;
  LusMaximumBit = LusSignalOffset;

  while (LusCount < LusSize)
  {
    while ((LusCount < LusSize) && ((LusSignalOffset % DCM_EIGHT) != DCM_ZERO))
    {
      LusSignalOffset--;
      if (LusLeastBit > LusSignalOffset)
      {
        LusLeastBit   = LusSignalOffset;
      }
      if (LusMaximumBit < LusSignalOffset)
      {
        LusMaximumBit = LusSignalOffset;
      }
      LusCount++;
    }
    if (((LusSignalOffset % DCM_EIGHT) == DCM_ZERO) && (LusCount < LusSize))
    {
      LusCount++;
      LusSignalOffset = LusSignalOffset + DCM_FIFTEEN;

      if (LusLeastBit > LusSignalOffset)
      {
        LusLeastBit   = LusSignalOffset;
      }
      else if (LusMaximumBit < LusSignalOffset)
      {
        LusMaximumBit = LusSignalOffset;
      }
      else
      {
        /* To avoid QAC warning */
      }
    }
  }
  return(LusSignalOffset);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmLinkControlService                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Link service is used to gain bus bandwidth     **
**                        for diagnostic purposes                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GddNegRespError,          **
**                        Dcm_GddProtocolId, Dcm_GaaSubServiceIdConfig,       **
**                        Dcm_GaaProtocolConfig, Dcm_GaaSIdConfig,            **
**                        Function(s) invoked :                               **
**                                                                            **
*******************************************************************************/
#if(DCM_LINK_CONTROL_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmLinkControlService(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2CONST(Dcm_SubServiceIdConfigType, AUTOMATIC, DCM_APPL_CONST) subServiceCfg;
  Std_ReturnType requestResult = E_OK;  

  subServiceCfg = Dcm_DsdInternal_GetSubFunctionByMsgContext(pMsgContext);    
  if(NULL_PTR == subServiceCfg)
  { 
    /* Never be reached, but this code is added for MISRA-rules */  
    Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
  }
  /* External diagnostic subservice processing  */
  else if(NULL_PTR != subServiceCfg->pSubServiceFnc)
  {
    if ( (DCM_INITIAL == OpStatus) && (pMsgContext->reqDataLen > 0U))
    {
      /* @SWS_Dcm_00764 The pointer in pMsgContext shall point behind the SubFunction */  
      pMsgContext->reqData = &pMsgContext->reqData[1U];
      pMsgContext->reqDataLen--;
    }
    requestResult = subServiceCfg->pSubServiceFnc(OpStatus, pMsgContext);
  }
  /* Dcm-Internal diagnostic subservice processing  */  
  else
  {
    uint8 subFunctionId = subServiceCfg->ucSubServiceId;

    if((subFunctionId == DCM_ONE) && (pMsgContext->reqDataLen != DCM_TWO))
    {
      Dcm_InternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);    
    }
    else if((subFunctionId == DCM_TWO) && (pMsgContext->reqDataLen != DCM_FOUR))
    {
      Dcm_InternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);    
    }
    else if((subFunctionId == DCM_THREE) && (pMsgContext->reqDataLen != DCM_ONE))
    {
      Dcm_InternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);    
    }
    else
    {
      pMsgContext->resData[0U] = subFunctionId;
      pMsgContext->resDataLen = 1U;
    }
    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
  }
  
  /* TODO: return value shall be processed */
  return requestResult;  
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmReadDataByPeriodicIdentifier                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This ReadDataByPeriodicIdentifier service is used   **
**                        to schedule data in the server for periodic         **
**                        transmission                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GddNegRespError,          **
**                        Dcm_GaaPeriodicID,                                  **
**                        Dcm_GaaReadDid, Dcm_ServicePendingStatus,           **
**                                                                            **
**                        Function(s) invoked : Dcm_ExternalSetNegResponse,   **
**                        Dcm_ExternalProcessingDone                          **
**                                                                            **
*******************************************************************************/
#if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmReadDataByPeriodicIdentifier(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Dcm_MsgLenType maxNumOfDidAvailable;
  Dcm_MsgLenType numOfDids;
  uint8  tmMode;
  Std_ReturnType retVal = E_NOT_OK;

  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;

  /* Update Transmission mode */
  tmMode = pMsgContext->reqData[0U];
  /*To Get the Periodic DID count by removing Transmission mode in request */
  numOfDids = pMsgContext->reqDataLen - 1U;
  
  #if(DCM_DSP_MAX_PERIODIC_DID == DCM_ZERO)
  maxNumOfDidAvailable = numOfDids;
  #else
  maxNumOfDidAvailable = (Dcm_MsgLenType)Dcm_Dsp_Max_Periodic_DID;
  #endif

  /* Check if the requested length is satisfying the minimal length */
  if (
    (pMsgContext->reqDataLen < 1U) || 
    (
      (tmMode != DCM_PERODIC_STOP_TM) && 
      (pMsgContext->reqDataLen < DCM_TWO)
    )
  )
  {
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  /* Check if the requested transmission mode/request
    length is equal to the calculated maximum length */
  else if (
    (tmMode > DCM_PERODIC_STOP_TM) || 
    (tmMode < DCM_PERODIC_SLOWRATE_TM) || 
    (numOfDids > maxNumOfDidAvailable)
  )
  {
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
  }
  /* Stop the individual Periodic DIDs if the requested
  transmission mode is stop */
  else if (tmMode == DCM_PERODIC_STOP_TM)
  {
    Dcm_StopPeriodicTransmission(pMsgContext);
    retVal = E_OK;
  }
  else
  {  
    /* TODO : Dcm_GetPeriodicDidProcState */
    P2VAR(Dcm_PeriodicDidProcStateType, AUTOMATIC, DCM_APPL_DATA) pPeriodicRdDid = &Dcm_PeriodicDidProcState[0];

    pPeriodicRdDid->iDID = 0U;
    /* TODO : Dcm_MsgLenType or uint16 ? */
    pPeriodicRdDid->NumOfDid = (uint16)numOfDids; 
    
    pPeriodicRdDid->state.pDID = DCM_PDID_STATE_VERIFICATION_PDID;
    pPeriodicRdDid->atLeastOne = DCM_FALSE;

    /* FIXME : return value*/
    retVal = Dcm_DspInternal_DcmReadDataByPeriodicIdentifier(DCM_INITIAL, pMsgContext);
  }
  
  if (DCM_E_PENDING != retVal)
  {
    Dcm_HandlePeriodicResponse(pMsgContext);
  }

  DCM_UNUSED(OpStatus);
  /* TODO: return value shall be processed */
  return E_OK;  
}

/*******************************************************************************
** Function Name        : Dcm_DspInternal_DcmReadDataByPeriodicIdentifier     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function invokes the function         **
**                        configured for the signals of DIDs.                 **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GaaDIDParaConfig,         **
**                        Dcm_GaaPeriodicID, Dcm_GddNegRespError              **
**                        Function(s) invoked : Dcm_DsdSetNegResponse,        **
**                        Dcm_DsdProcessingDone                               **
**                                                                            **
*******************************************************************************/
#if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DcmReadDataByPeriodicIdentifier(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType retVal = E_OK;
  P2VAR(Dcm_PeriodicDidProcStateType, AUTOMATIC, DCM_APPL_DATA) pPeriodicRdDid = &Dcm_PeriodicDidProcState[0];

  Dcm_ServicePendingStatus.ucReadPerDIDPendingStatus = DCM_FALSE;
      
  while ((pPeriodicRdDid->iDID < pPeriodicRdDid->NumOfDid) && (E_OK == retVal))
  {  
    Dcm_NegativeResponseCodeType negRespCode;  

    if (DCM_PDID_STATE_VERIFICATION_PDID == pPeriodicRdDid->state.pDID)
    {
      uint16 indexOfDidTable = 0U;
      uint16 dataIdentifier;
          
      /* Update Identifier from the request buffer */
      dataIdentifier = DCM_PERIODIC_ID_F200;
      dataIdentifier = dataIdentifier | ((uint16)pMsgContext->reqData[1U + pPeriodicRdDid->iDID]);  

      /* FIXME : Except DID Range?  */
      negRespCode = DCM_E_REQUESTOUTOFRANGE;    
      /* Check if the DID from the request is supported */
      if (DCM_TRUE == Dcm_IDSearch(DCM_GET_DID, dataIdentifier, &indexOfDidTable)) 
      {
        /* Invoke function to validate DID for session and security  */
        negRespCode = Dcm_DspValidateDID(indexOfDidTable, DCM_FALSE);    
      }      
      if(DCM_E_POSITIVERESPONSE == negRespCode)
      {
        pPeriodicRdDid->atLeastOne = DCM_TRUE;   
        pPeriodicRdDid->state.pDID = DCM_PDID_STATE_CONDITION_CHECK_READ;
        pPeriodicRdDid->iDidTable = indexOfDidTable;

        /* signal status */
        pPeriodicRdDid->SigIndex  = 0U;
      }
      /*Check if the security is not supported for the DID */
      else if ((DCM_E_SECURITYACCESSDENIED == negRespCode) || (DCM_E_CONDITIONSNOTCORRECT == negRespCode))
      {
        Dcm_GddNegRespError = negRespCode;
        retVal = E_NOT_OK;
      }
      else
      {
        pPeriodicRdDid->iDID++;
      }
    }
    if (DCM_PDID_STATE_CONDITION_CHECK_READ== pPeriodicRdDid->state.pDID)
    {
      P2CONST(Dcm_DIDParaConfig, AUTOMATIC, DCM_APPL_CONST) 
        pCfgDid = &Dcm_GaaDIDParaConfig[pPeriodicRdDid->iDidTable];
      uint8 numOfSig = 0U;
      uint16 schSlot = 0U;

      retVal = E_OK;
      numOfSig = pCfgDid->ucDcmDspSignalCount;
      /* Checkes whether DID has at least one signal */
      while ((pPeriodicRdDid->SigIndex < numOfSig) && (E_OK == retVal))
      {
        P2VAR(Dcm_DcmDspSignalconfig, AUTOMATIC, DCM_APPL_DATA) 
          pSignal = &pCfgDid->pDcmDspSignal[pPeriodicRdDid->SigIndex];

        negRespCode = DCM_E_POSITIVERESPONSE;
        retVal = Dcm_DspInternal_ConditionCheckRead(OpStatus, pSignal->pDcmDspData, &negRespCode);
        if (E_OK == retVal)
        {
          /* for next signal */
          pPeriodicRdDid->SigIndex++;
        }
        else if (E_NOT_OK == retVal)
        {
          Dcm_GddNegRespError = negRespCode;
        }
        else if (DCM_E_PENDING == retVal)
        {
          Dcm_ServicePendingStatus.ucReadPerDIDPendingStatus = DCM_TRUE;
        }      
        else
        {
          /* TODO: Det Error */
          Dcm_GddNegRespError = DCM_E_GENERALREJECT;
          retVal = E_NOT_OK;          
        }
      } /* end of while for signals */
      
      /* if retVal is E_OK then all signals is OK */
      if (E_OK == retVal)
      {
        /* check whether the requested DID already is running */
        if (E_OK == Dcm_DspInternal_GetPeriodicDidInRunning(pCfgDid->usDcmDspDidIdentifier, &schSlot))
        {
          /* changes transmission mode */
          Dcm_GaaPeriodicID[schSlot][1U] = pMsgContext->reqData[0U];
        }
        else
        {
          /* Store the Periodic DIDs in the global array for processing in mainfunction.
           * If first paramter value  is zero, it returns the index of free slot */
          if (E_OK == Dcm_DspInternal_GetPeriodicDidInRunning(0U, &schSlot))
          {        
            Dcm_GaaPeriodicID[schSlot][0U] = pCfgDid->usDcmDspDidIdentifier;;            
            /* transmission Mode */
            Dcm_GaaPeriodicID[schSlot][1U] = pMsgContext->reqData[0U]; 
          }
          else
          {            
            Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
            retVal = E_NOT_OK;
          }
        }
        {
          pPeriodicRdDid->state.pDID = DCM_PDID_STATE_VERIFICATION_PDID;
          pPeriodicRdDid->iDID++;
        }
      }
    }
  }
  
  if ( /* When All DIDs is finished, if any one is not successful */
    (pPeriodicRdDid->iDID == pPeriodicRdDid->NumOfDid) &&
    (DCM_FALSE == pPeriodicRdDid->atLeastOne)
  )
  {   
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    retVal = E_NOT_OK;
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_StopPeriodicTransmission                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function stops the periodic           **
**                        transmission of the requested DIDs by removing the  **
**                        DIDs from the global array of periodic DIDs.        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dcm_GaaPeriodicID, Dcm_GaaActivePeriodicTimer       **
**                        Dcm_PrtclTxBufStatus, Dcm_GddNegRespError.          **
**                        Function(s) invoked : Dcm_DsdSetNegResponse,        **
**                        Dcm_DsdProcessingDone                               **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_StopPeriodicTransmission(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  uint32 LulTotReqLen;
  uint32 LulIDIndex;
  uint16 LusCount;
  uint16 LusEmptyCount;
  uint16 LusDataIdentifier;
  uint16 LusPeriodicIdIndex;
  uint8 LucTimerCount;

  LusEmptyCount = DCM_ZERO;
  LucTimerCount = DCM_ZERO;

  LulTotReqLen = (pMsgContext->reqDataLen) - DCM_ONE;
  /* Check if all the periodic DID transmission should be stopped */
  if(LulTotReqLen == DCM_ZERO)
  {
    for(LusCount = (uint16)DCM_ZERO; LusCount <
    Dcm_Dsp_Max_Periodic_DID_Scheduled; LusCount++)
    {
      /* Remove the periodic DID from the global array */
      Dcm_GaaPeriodicID[LusCount][DCM_ZERO] = DCM_ZERO;
      Dcm_GaaPeriodicID[LusCount][DCM_ONE] = DCM_ZERO;
    }
    LusEmptyCount = LusCount;
  }
  else
  {
    /* Search for the periodic DID in the array to stop the periodic
       transmission */
    for(LulIDIndex = DCM_ZERO; LulIDIndex < LulTotReqLen; LulIDIndex++)
    {    
      /* Update Identifier from the request buffer */
      LusDataIdentifier = DCM_PERIODIC_ID_F200;
      LusDataIdentifier = LusDataIdentifier | ((uint16)pMsgContext->reqData[LulIDIndex + 1U]);  

      for(LusCount = (uint16)DCM_ZERO;
          LusCount < Dcm_Dsp_Max_Periodic_DID_Scheduled; LusCount++)
      {
        if(Dcm_GaaPeriodicID[LusCount][DCM_ZERO] == DCM_ZERO)
        {
          LusEmptyCount++;
        }
        else if(Dcm_GaaPeriodicID[LusCount][DCM_ZERO] == LusDataIdentifier)
        {
          /* Remove the periodic DID from the global array and
          clear the transmission mode */
          Dcm_GaaPeriodicID[LusCount][DCM_ZERO] = DCM_ZERO;
          Dcm_GaaPeriodicID[LusCount][DCM_ONE] = DCM_ZERO;
          LusEmptyCount++;
        }
        else
        {
          /* To avoid QAC warning */
        }
      }
    }
  }
  /* Check if all the periodic DIDs are stopped */
  if(LusEmptyCount == Dcm_Dsp_Max_Periodic_DID_Scheduled)
  {
    /* Stop all the periodic transmission timers */
    for(LusCount = (uint16)DCM_ZERO; LusCount < DCM_THREE_UINT16; LusCount++)
    {
      Dcm_GaaActivePeriodicTimer[LusCount] = DCM_FALSE;
      DCM_STOP_TIMER(LusCount + DCM_SIX);
    }
    Dcm_PrtclTxBufStatus.ucPeriodicIdStatus = DCM_FALSE;
  }
  else
  {
    /* Check if one a specific periodic timer should be stopped */
    for(LusCount = DCM_ONE; LusCount <= DCM_THREE; LusCount++)
    {
      for(LusPeriodicIdIndex = DCM_ZERO;
          LusPeriodicIdIndex < Dcm_Dsp_Max_Periodic_DID_Scheduled;
          LusPeriodicIdIndex++)
      {
        if(Dcm_GaaPeriodicID[LusPeriodicIdIndex][DCM_ONE] == LusCount)
        {
          LucTimerCount++;
        }
      }
      if(LucTimerCount == DCM_ZERO)
      {
        /* Stop the timer if no periodic DID belongs to specific
        transmission mode */
        DCM_STOP_TIMER(LusCount + DCM_FIVE);
        Dcm_GaaActivePeriodicTimer[LusCount - DCM_ONE] = DCM_FALSE;
      }
      LucTimerCount = DCM_ZERO;
    }
  }
  /*update the response message length  */
  pMsgContext->resDataLen = DCM_ZERO;
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
}

/*******************************************************************************
** Function Name        : Dcm_HandlePeriodicResponse                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function stops the periodic           **
**                        transmission of the requested DIDs by removing the  **
**                        DIDs from the global array of periodic DIDs.        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GucPeriodicRxPduId,       **
**                        Dcm_ServicePendingStatus, Dcm_GpMsgContext,         **
**                        Dcm_GddNegRespError, Dcm_PrtclTxBufStatus,          **
**                        Dcm_GaaActivePeriodicTimer.                         **
**                        Function(s) invoked : Dcm_DsdSetNegResponse,        **
**                        Dcm_DsdProcessingDone                               **
**                                                                            **
*******************************************************************************/
/* MISRA Rule         : 16.7
   Message            : A pointer parameter in a function prototype should be
                        declared as pointer to const if the pointer is not
                        used to modify the addressed object.
   Reason             : This is the prototype specified in the specification.
   Verification       : However, part of the code is verified
                        manually and it is not having any impact.
 */
FUNC(void, DCM_CODE)Dcm_HandlePeriodicResponse(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  /* Check if all the periodic DIDs are processed */
  if(Dcm_ServicePendingStatus.ucReadPerDIDPendingStatus == DCM_FALSE)
  {
    Dcm_GucPeriodicRxPduId =  Dcm_GstMsgContext.dcmRxPduId;
    Dcm_GstMsgContext.resDataLen = DCM_ZERO;

    if(Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE)
    {    
      uint8 LusTransMode;
      uint8 LucTimerName;
      uint16 LusTimerValue;
      LusTransMode = pMsgContext->reqData[DCM_ZERO];
      
      Dcm_PrtclTxBufStatus.ucPeriodicIdStatus = DCM_TRUE;

      /* Check the transmission mode and load the timers that has
      to be started */
      if(LusTransMode == DCM_ONE)
      {
        LucTimerName = DCM_PERIODIC_SLOW_TIMER;
        LusTimerValue = Dcm_Send_At_Low_Rate_Timer;
      }
      else if(LusTransMode == DCM_TWO)
      {
        LucTimerName = DCM_PERIODIC_MEDIUM_TIMER;
        LusTimerValue = Dcm_Send_At_Med_Rate_Timer;
      }
      else
      {
        LucTimerName = DCM_PERIODIC_FAST_TIMER;
        LusTimerValue = Dcm_Send_At_Fast_Rate_Timer;
      }

      /* Start the corresponding timers */
      if(Dcm_GaaActivePeriodicTimer[LusTransMode - DCM_ONE] == DCM_FALSE)
      {
        Dcm_GaaActivePeriodicTimer[LusTransMode - DCM_ONE] = DCM_TRUE;
        DCM_START_TIMER(LucTimerName, LusTimerValue);
      }
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_ResetWriteDIDOpStatus                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          :                                                     **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusDataIdentifier, LpTypeOfID                       **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GusDataIdentifier,        **
**                        Dcm_GaaDIDParaConfig.                               **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if(DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
FUNC(void, DCM_CODE) Dcm_ResetWriteDIDOpStatus(void)
{
  P2VAR(Dcm_DIDRangeConfig, AUTOMATIC, DCM_APPL_DATA)pDIDRangeConfig = NULL_PTR;
  uint16 didIndex = (uint16)0x00;
  uint16 dataIdentifier = Dcm_GusDataIdentifier;
  uint8 iterator = 0U; 
  boolean didRangePresent = DCM_FALSE;

  (void)Dcm_DspDIDSearch(dataIdentifier, &didIndex, &didRangePresent);

  if((DCM_ZERO != Dcm_Num_Of_DcmDspDidRangeConfig) &&
                                                  (DCM_TRUE == didRangePresent))
  {
    for(iterator = 0U;
        iterator < Dcm_Num_Of_DcmDspDidRangeConfig;
        iterator++)
    {
      pDIDRangeConfig = Dcm_CfgInternal_GetDIDRangeConfig(iterator);
      pDIDRangeConfig->ucDidRangeOpStatus = DCM_OPSTATUS_INITIAL;
    }
  }
  else
  {
    if (didIndex < Dcm_Num_Of_DidParaConfig)
    {
      if (NULL_PTR != Dcm_GaaDIDParaConfig[didIndex].pDcmDspSignal)
      {
        for(iterator = DCM_ZERO;
            iterator < Dcm_GaaDIDParaConfig[didIndex].ucDcmDspSignalCount; 
            iterator++)
        {
          Dcm_GaaDIDParaConfig[didIndex].pDcmDspSignal[iterator]
                                    .ucDidSignalOpStatus = DCM_OPSTATUS_INITIAL;
        }
      }
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspDIDSearch                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function is used to check if the      **
**                        requested DID is in DIDRange.                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusDataIdentifier                                   **
**                                                                            **
** Output Parameters    : LusDIDIndex, LblDIDRangePresent                     **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variables : Dcm_Num_Of_DcmDspDidRangeConfig  **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
    (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
    (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON))
static FUNC(boolean, DCM_CODE) Dcm_DspDIDSearch(
  uint16 aDataIdentifier,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) aDidIndex,
  P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA) aDidRangePresent)
{
  P2VAR(Dcm_DIDRangeConfig, AUTOMATIC, DCM_APPL_DATA)pDIDRangeConfig = NULL_PTR;
  boolean searchResult;

  /* Update variable as DCM_FALSE */
  *aDidRangePresent = DCM_FALSE;

  /* Check if the DID from the request is supported */
  searchResult = Dcm_IDSearch(DCM_GET_DID, aDataIdentifier, aDidIndex);

  if((DCM_ZERO != Dcm_Num_Of_DcmDspDidRangeConfig) &&
                                                    (DCM_FALSE == searchResult))
  {
    /* Verify if requested DID is in the configured DIDRange */
    if(((aDataIdentifier >= DCM_MAXVALUE) &&
        (aDataIdentifier <= DCM_DID_RANGE_F1FF)) ||
       ((aDataIdentifier >= DCM_OBDDID_LOWER_RANGE) &&
        (aDataIdentifier <= DCM_DID_RANGE_FEFF)))
    {
      uint16 iteratorDid;

      for(iteratorDid = 0U;
          iteratorDid < Dcm_Num_Of_DcmDspDidRangeConfig;
          iteratorDid++)
      {
        pDIDRangeConfig = Dcm_CfgInternal_GetDIDRangeConfig(iteratorDid);

        /* Verify if requested DID is in the configured DIDRange */
        if((aDataIdentifier >= pDIDRangeConfig->usDidRangeIdLowerLimit) &&
           (aDataIdentifier <= pDIDRangeConfig->usDidRangeIdUpperLimit))
        {
          if(DCM_TRUE == pDIDRangeConfig->blDidRangeHasGaps)
          {
            /* check if the requested DID is in the DIDRange provided */
            if(NULL_PTR != pDIDRangeConfig->pIsDidAvailableFnc)
            {
              uint8 didSupported = 0U;
              Std_ReturnType result;

              result = pDIDRangeConfig->pIsDidAvailableFnc(aDataIdentifier, &didSupported);

              if((E_OK == result) && (0U != didSupported))
              {
                searchResult = DCM_TRUE;
              }
            }
          }
          else
          {
            searchResult = DCM_TRUE;
          }

          if(DCM_TRUE == searchResult)
          {
            *aDidRangePresent = DCM_TRUE;
            *aDidIndex = iteratorDid;
            break;
          }
        }
      }
    }
  }

  if(DCM_TRUE == searchResult)
  {
    /* global Dcm_GusDIDIndexVal shall be remove */  
    Dcm_GusDIDIndexVal = *aDidIndex;          
  }

  return searchResult;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmEnableNormalMsgTransmission                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function used to enable normal message         **
**                        transmission.                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None.                                               **
**                                                                            **
** Remarks              : Global Variable(s) :Dcm_GddNegRespError,            **
**                        Dcm_GucSubNetValue,                                 **
**                        Dcm_GucCommunicationModeType                        **
**                        Function(s) invoked : Dcm_ExternalProcessingDone,   **
**                                              Dcm_ExternalSetNegResponse    **
**                                                                            **
*******************************************************************************/
#if(DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmEnableNormalMsgTransmission(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Dcm_DspInternal_DcmEnableNormalMsgTransmission(pMsgContext);

  DCM_UNUSED(OpStatus);
  
  return E_OK;  
}
#endif

/********************************************************************************
** Function Name        : Dcm_DspInternal_GetSizeOfDid                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used to get size of a DID          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : aCfgDid                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : aIsVariableLength                                   **
**                                                                            **
** Return parameter     : the length of the DID                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : if DID don't have signal,                           ** 
**                        this function returns zero                          **
**                                                                            **
*******************************************************************************/
#if(DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON)
static FUNC(void, DCM_CODE) Dcm_DspInternal_GetSizeOfDid(
  P2CONST(Dcm_DIDParaConfig, AUTOMATIC, DCM_APPL_CONST) aCfgDid,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) aMinDataLength,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) aMaxDataLength)
{
  P2VAR(Dcm_DcmDspSignalconfig, AUTOMATIC, DCM_APPL_DATA) cfgSignal;
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) cfgData;
  
  if ((NULL_PTR != aMaxDataLength) && (NULL_PTR != aMinDataLength) && (NULL_PTR != aCfgDid))
  {
    uint16 i;
    uint16 prevDataPos = 0U;
    uint16 numOfSignal = aCfgDid->ucDcmDspSignalCount;

    *aMinDataLength = 0U;  
    *aMaxDataLength = 0U;  

    /* PRECONDITION: 
     * 1) [constr_6039] 
     *    Signals with variable datalength: Only the last signal 
     *    (DcmDspDidSignal) of a DID can have variable datalength (DcmDspDataType is 
     *    set to UINT8_DYN). 
     *
     * 2) order of the signals
     *    all signal are ordered by usDcmDspDidDataPos(by generator[Error code 206])
     *    we are no need to check the data positions.
     */     

    /* if numOfSignal is zero, this function returns zero. */
    for(i = 0U; i < numOfSignal; i++)
    {
      cfgSignal = &aCfgDid->pDcmDspSignal[i];       
      
      if((prevDataPos <= cfgSignal->usDcmDspDidDataPos) && (NULL_PTR != cfgSignal->pDcmDspData))
      { 
        cfgData = cfgSignal->pDcmDspData;        
        *aMaxDataLength = cfgSignal->usDcmDspDidDataPos + cfgData->usDcmDspDataSize;
        
        /* case 1) if last signal is a variable lenth, aMinDataLength is not equal to aMaxDataLength.
         * case 2) if all signals are the fixed length, aMinDataLength is equal to aMaxDataLength.
         * case 3) if a DID has a signal with variable length, aMinDataLength is zero
         */
        if(NULL_PTR != cfgData->pDataInfo)
        {
          if (DCM_TRUE == cfgData->pDataInfo->blDataFixedLength)
          {
            *aMinDataLength = *aMaxDataLength;
          }
        }
        
        prevDataPos = cfgSignal->usDcmDspDidDataPos;
      }
    }
  }
}
#endif

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace:end<MISRA-C:13.7:Not a defect:Justify with annotations> It has not any impact. */
/* polyspace:end<MISRA-C:8.7:Not a defect:Justify with annotations> No Impact of this rule violation. */
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Nesting of control structures to achieve better throughput. */
/* polyspace:end<RTE: NIP : Not a defect : No Action Planned > pointer is not null */
/* polyspace:end<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:end<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */
/* polyspace:end<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
/* polyspace:end<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace-end MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.5 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:10.4 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:11.5 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:17.8 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:19.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.2 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:9.1 [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:USELESS_WRITE [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:UINT_CONV_OVFL [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-end CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-end CERT-C:EXP36-C [Justified:Low] "Module do not know user data type so before using user data, pointer need to be cast" */
/*******************************************************************************
 **                      End of File                                           **
 *******************************************************************************/
