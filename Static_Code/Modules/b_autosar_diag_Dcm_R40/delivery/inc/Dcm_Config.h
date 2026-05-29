/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE: Dcm_Config.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 2.3.2.0   05-Nov-2020   EunKyung Kim     #26432                            **
**                                                                            **
** 1.0.6     23-07-2019    Y.S     Jeon     #17648                            **
**                                                                            **
** 1.0.5     29-01-2019    Y.S     Jeon     #15566                            **
**                                                                            **
** 1.0.4     09-11-2018    Y.S     Jeon     #13923                            **
**                                                                            **
** 1.0.3     13-09-2018    Y.S     Jeon     #14010                            **
**                                                                            **
** 1.0.2     08-06-2017    Jin     Jung     #7008                             **
**                                                                            **
** 1.0.1     03-03-2016    Sungeol Baek     #3750                             **
**                                                                            **
** 1.0.0     18-11-2013    Autron           Initial Version                   **
*******************************************************************************/

#ifndef DCM_CONFIG_H
#define DCM_CONFIG_H

#include "Dcm.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* Pre-compile option for Manufacturer Indication Support */
extern CONST(uint8, DCM_CONST) Dcm_Number_Of_Request_Manufacturer_Indication;

/* Pre-compile option for Supplier Indication Support */
extern CONST(uint8, DCM_CONST) Dcm_Number_Of_Request_Supplier_Indication;

/* Pre-compile option for Task Time */
extern CONST(uint16, DCM_CONST) Dcm_Task_Time;

/* Pre-compile option for Timeout for Paged Buffer */
extern CONST(uint16, DCM_CONST) Dcm_PagedBufferTimeout;

/* Pre-compile option for Response Maximum Respend */
extern CONST(uint8, DCM_CONST) Dcm_diag_Resp_Max_Num_Respend;

/* Pre-compile option for Maximum Did to Read */
extern CONST(uint16, DCM_CONST) Dcm_Max_DID_To_Read;

/* Pre-compile option for Total number of PIDs Configured */
extern CONST(uint8, DCM_CONST) Dcm_Total_Num_Of_PIDs;

/* Pre-compile option for Total number of ObdMids Configured */
extern CONST(uint8, DCM_CONST) Dcm_Total_Num_Of_OBDMIDs;

/* Pre-compile option for Total number of TIDs Configured */
extern CONST(uint8, DCM_CONST) Dcm_Total_Num_Of_TIDs;

/* Pre-compile option for Total number of VIDs Configured */
extern CONST(uint8, DCM_CONST) Dcm_Total_Num_OF_VIDs;

/* Pre-compile option for Total number of DIDs Configured */
extern CONST(uint16, DCM_CONST) Dcm_Total_Num_Of_DIDs;

/* Pre-compile option for Total number of Data Info type Configured */
extern CONST(uint8, DCM_CONST) Dcm_Num_Of_Gaa_Data_InfoType_Config;

/* Pre-compile option for Total number of Routine Control Configured */
extern CONST(uint8, DCM_CONST) Dcm_Num_Of_Gaa_Routine_Control_Config;

/* Pre-compile option for Total number of Security Levels Configured */
extern CONST(uint8, DCM_CONST) Dcm_Total_Num_Sec_Level;

/* Pre-compile option for Total number of Protocols Configured */
extern CONST(uint8, DCM_CONST) Dcm_Num_Protocol_Configd;

/* Pre-compile option for Power Down Time */
extern CONST(uint8, DCM_CONST) Dcm_PowerDown_Time;

/* Pre-compile option for Total number of DIDs Configured */
extern CONST(uint16, DCM_CONST) Dcm_Total_Num_Of_RIDs;

/* Pre-compile option for Dynamic Dids */
extern CONST(uint16, DCM_CONST) Dcm_Total_Num_Of_Dym_DID;

/* Pre-compile option for Ststic Dids */
extern CONST(uint16, DCM_CONST) Dcm_Total_Num_Of_Static_DID;

/* Pre-compile option for Total number of Read Memory Configured */
extern CONST(uint8, DCM_CONST) Dcm_Total_Num_Read_Memory_Configured;

/* Pre-compile option for Total number of Write Memory Configured */
extern CONST(uint8, DCM_CONST) Dcm_Total_Num_Write_Memory_Configured;

/* Pre-compile option for Total number of Rx Configured */
extern CONST(PduIdType, DCM_CONST) Dcm_Total_Num_Of_RxPduID ;

/* Pre-compile option for Total number ofAll ComM Configured */
extern CONST(uint8, DCM_CONST) Dcm_Total_Num_Of_All_Channel ;

/* Pre-compile option for Total number of Specific ComM Configured */
extern CONST(uint8, DCM_CONST) Dcm_Total_Num_Of_Specific_Channel;

/* Pre-compile option for Periodic Transmission for slow rate (0x01) */
extern CONST(uint16, DCM_CONST) Dcm_Send_At_Low_Rate_Timer;

/* Pre-compile option for Periodic Transmission for Medium rate (0x02) */
extern CONST(uint16, DCM_CONST) Dcm_Send_At_Med_Rate_Timer;

/* Pre-compile option for Periodic Transmission for Fast rate (0x03) */
extern CONST(uint16, DCM_CONST) Dcm_Send_At_Fast_Rate_Timer;

/* Pre-compile option for Max Periodic DID to Read */
extern CONST(uint16, DCM_CONST) Dcm_Dsp_Max_Periodic_DID;

/* Pre-compile option for Periodic Response Type */
extern CONST(uint16, DCM_CONST) Dcm_Dsp_Max_Periodic_DID_Scheduled;

/* Macro total number of Support Address configured */
extern CONST(uint8, DCM_CONST) Dcm_Num_Of_Address_Length_Format_ID_Config;

/* Pre-compile option for Total number of Callback request Configured */
extern CONST(uint8, DCM_CONST) Dcm_Total_Num_Of_Callback_Request;

/* Pre-compile option for Total number of Session level Configured */
extern CONST(uint8, DCM_CONST) Dcm_Num_Of_Diag_Session_Config;

/* Pre-compile option for Total number of Security level Configured */
extern CONST(uint8, DCM_CONST) Dcm_Num_Of_Security_Level_Config;

/* Macro total number of Support Address configured */
extern CONST(uint16, DCM_CONST) Dcm_Total_Num_Of_OBD_DID;

/* Macro for Number of DcmDspDidRange configured */
extern CONST(uint32, DCM_CONST) Dcm_ROE_Max_Event_Length;

/* Macro for Number of DcmDspDidRange configured */
extern CONST(uint8, DCM_CONST) Dcm_ROE_Max_Number_Of_Retry;

/* Macro for Number of DcmDspDidRange configured */
extern CONST(uint8, DCM_CONST) Dcm_ROE_Max_Queue_Length;

/* Macro for Number of DcmDspDidRange configured */
extern CONST(uint16, DCM_CONST) Dcm_ROE_Inter_Message_Time;

/* To indicate PID Config list */
extern CONST(uint8, DCM_CONST) Dcm_PID_AVL_Config_List_FreezeFrame;

/* To indicate PID Config list */
extern CONST(uint8, DCM_CONST) Dcm_PID_AVL_Config_List;

/* To indicate VID Config list */
extern CONST(uint8, DCM_CONST) Dcm_VID_AVL_Config_List;

/* To indicate TID Config list */
extern CONST(uint8, DCM_CONST) Dcm_TID_AVL_Config_List;

/* To indicate OBDMID Config list */
extern CONST(uint8, DCM_CONST) DCM_OBDMID_AVL_Config_List;

/* To indicate OBDMID Config list */
extern CONST(uint8, DCM_CONST) Dcm_Dsp_Max_Periodic_Did_Len;

extern CONST(uint8, DCM_CONST) Dcm_Max_No_Of_Preconfigured_Did;

extern CONST(Dcm_ModeType, DCM_CONST) Dcm_Dsp_Control_Dtc_Reenable_Mode_Rule;

extern CONST(Dcm_ModeType, DCM_CONST) Dcm_Dsp_Comm_Control_Reenable_Mode_Rule;

extern CONST(uint8, DCM_CONST) Dcm_No_Of_Comm_Channels;

extern CONST(PduIdType, DCM_CONST) Dcm_Num_Of_PduidTableConfig;

extern CONST(uint8, DCM_CONST) Dcm_Num_Of_Buffer_Config;

extern CONST(uint8, DCM_CONST) Dcm_Num_Of_SidConfig;

extern CONST(uint8, DCM_CONST) Dcm_Num_Of_CommControlConfig;

extern CONST(uint8, DCM_CONST) Dcm_Num_Of_SubserviceIdConfig;

extern CONST(uint8, DCM_CONST) Dcm_Num_Of_SigWrFuncPtr;

extern CONST(uint16, DCM_CONST) Dcm_Num_Of_DidParaConfig;

extern CONST(uint8, DCM_CONST) Dcm_Num_Of_SigRdFuncPtr;

extern CONST(boolean, DCM_CONST) Dcm_Respond_All_Request;

extern CONST(uint8, DCM_CONST) Dcm_Num_Of_ProtocolConfig;

extern CONST(uint16, DCM_CONST) Dcm_Num_Of_DcmDspDidRangeConfig;

extern CONST(boolean, DCM_CONST) Dcm_Remain_Unlock_Condition;

extern CONST(boolean, DCM_CONST) Dcm_Request_Manufacturer_Indication_Enabled;

extern CONST(boolean, DCM_CONST) Dcm_Request_Supplier_Indication_Enabled;

extern CONST(boolean, DCM_CONST) Dcm_Forced_Ecu_Reset;

#define DCM_STOP_SEC_CONST_UNSPECIFIED
/* polyspace +1 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#if (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE)
Dcm_CfgInternal_WriteSigTypeSenderReceiver(
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aData,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) aInputBuffer,
  Dcm_NegativeResponseCodeType *anOutNegRespCode);
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) ||\
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
extern FUNC(Std_ReturnType, DCM_CODE)
Dcm_CfgInternal_ReadSigTypeEcuSignal(
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aData,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) aOutputBuffer);
#endif


#if (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE)
Dcm_CfgInternal_IOControlSigTypeEcuSignal(
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,
  uint8 anAction,
  P2CONST(void, AUTOMATIC, DCM_APPL_DATA) anInputBuffer,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) aNegResponceCode);  
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
extern FUNC(Std_ReturnType, DCM_CODE)
Dcm_CfgInternal_ReadSigTypeSenderReceiver(
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) anOutputBuffer);
#endif

/* polyspace-begin MISRA-C3:20.7 [Justify with annotations:Low] "Not a defect" */
#if(DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON)
extern FUNC(P2VAR(Dcm_DIDRangeConfig, AUTOMATIC, DCM_APPL_DATA), DCM_CODE)
  Dcm_CfgInternal_GetDIDRangeConfig(uint16 LusDIDIndex);
#endif

extern FUNC(Dcm_ConfirmationFunType, DCM_CODE) Dcm_GetManuConfirmationFun(uint8 index);

extern FUNC(Dcm_IndicationFunType, DCM_CODE) Dcm_GetManuIndicationFun(uint8 index);

extern FUNC(Dcm_ConfirmationFunType, DCM_CODE) Dcm_GetSuppConfirmationFun(uint8 index);

extern FUNC(Dcm_IndicationFunType, DCM_CODE) Dcm_GetSuppIndicationFun(uint8 index);
/* polyspace-end MISRA-C3:20.7 [Justify with annotations:Low] "Not a defect" */
#endif /* DCM_CFG_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

