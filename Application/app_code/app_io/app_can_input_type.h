/******************************************************************************
 * Project        :   IBU
 * File Name      :   app_can_input_type.h
 * Compiler     :   Eclipse
 * Author         :   MyoungKwon Choi (mk210@seoyonelec.com)
 * Created at     :   2020-07-03
 * Code Editor    :   Source Insight (Recomended Font : D2Coding / Size 10)
 * Revision       :   Version 0.1
 * Copyright      :   Copyright Seoyon Electronics Co.Ltd. All Rights Reserved
 * Description    :
 *
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------*/
#ifndef __APP_CAN_INPUT_TYPE_H__
#define __APP_CAN_INPUT_TYPE_H__

#include "WPCType.h"

#if 1

/*******************************************************************************
  Define Variables Type
*******************************************************************************/
typedef struct
{
  /* INPUT B-CAN */
  /* BCM_07_200ms */
  tVAR  Lamp_IntTailLmpOnReq;
  /* BCM_12_200ms */
  tVAR  BCM_SmkOptTyp;
  /* CLU_01_20ms_1 */
  tVAR  CLU_DtntOutSta;
  tVAR  CLU_RhstaLvlSta;
  /* CLU_01_20ms_2 */
  tVARu16  CLU_DisSpdVal_KPH;
  tVARu16  CLU_AutoBrightSta;
  /* CLU_05_00ms_1 */
  tVAR  USM_StaRst1Req;
  /* CLU_09_00ms_1 */
  tVAR  USM_WpcSetReq;
  /* CLU_20_200ms_1 */
  tVAR  CLU_ClusterUSM;
  /* EMS_02_10ms_1 */
  tVAR  ENG_EngSta;
  /* EMS_07_10ms_2 */
  tVAR  HEV_EngOpSta;
  /* HCU_03_10ms_2 */
  tVAR  HCU_HevRdySta;
  /* HU_GW_PE_01 */
  tVAR  CF_AVN_ProfileIDRValue;
  /* HU_USM_E_02 */
  tVAR  CF_Gway_RWPCNValueSet;
  /* HU_USM_E_04 */
  tVAR  CF_AVN_CluUSMReset;
  /* HU_USM_E_14 */
  tVAR  CF_Gway_WPCAnimationNvalueSet;
  /* IAU_16_200ms */
  tVAR  IAU_DigitalKey2Opt;
  tVAR  IAU_ProfileIDRVal;
  /* ICU_02_200ms */
  tVAR  Warn_AsstDrSwSta;
  tVAR  Warn_RrRtDrSwSta;
  tVAR  Warn_DrvDrSwSta;
  tVAR  Warn_RrLftDrSwSta;
  /* SBCM_AST_02_200ms */
  tVAR  Warn_AsstDrSwSta_SBCM;
  /* SBCM_DRV_01_200ms */
  tVAR  Latch_TypeOption_DRV;
  tVAR  Warn_DrvDrSwSta_SBCM;
  /* SBCM_RL_01_200ms */
  tVAR  Warn_RrLftDrSwSta_SBCM;
  /* SBCM_RR_01_200ms */
  tVAR  Warn_RrRtDrSwSta_SBCM;
  /* SMK_06_200ms */
  tVAR  LFAnt_SrchSta;
  /* VCU_01_10ms_1 */
  tVAR  VCU_EvDrvRdySta;
  /* WPC2_01_200ms */
  tVAR  WPC2_IndSyncVal;
  /* RWPC_01_200ms */
  tVAR  WPC_IndSyncVal;
  tVAR  USM_CmdWPCIndSta;
  /* ATS_00_00ms */
  tVAR  ATS_RWPC_RWPCNValueSet;

  tVAR  AccInSta;
  tVAR  Ign1Insta;
  
  /* INPUT LOCAL-CAN */
  /* LOCALCAN_BDC_01 */
  tVAR  WPCNFCcmd;
  tVAR  BDCWPCNFCCmd;
  /* LOCALCAN_BDC_10 */
  tVAR  DeviceOnWPC;
  tVAR  BDC_Status;
  tVAR  OwnerKeyRegStatus;

  /* BCAN TimeOut */
  tVAR 	TimeOut_BCM_07_200ms;	   
  tVAR	TimeOut_BCM_12_200ms;     
  tVAR	TimeOut_CLU_01_20ms_1;    
  tVARu16 TimeOut_CLU_01_20ms_2;   
  tVAR	TimeOut_CLU_05_00ms_1;    
  tVAR	TimeOut_CLU_09_00ms_1;    
  tVAR	TimeOut_CLU_20_200ms_1;   
  tVAR	TimeOut_EMS_02_10ms_1;    
  tVAR	TimeOut_EMS_07_10ms_2;    
  tVAR	TimeOut_HCU_03_10ms_2;    
  tVAR	TimeOut_HU_GW_PE_01;      
  tVAR	TimeOut_HU_USM_E_02;      
  tVAR	TimeOut_HU_USM_E_04;
  tVAR  TimeOut_HU_USM_E_14;
  tVAR	TimeOut_IAU_16_200ms;     
  tVAR	TimeOut_ICU_02_200ms;     
 
  tVAR	TimeOut_SBCM_AST_02_200ms;
  tVAR	TimeOut_SBCM_DRV_01_200ms;
  tVAR	TimeOut_SBCM_RL_01_200ms; 
  tVAR	TimeOut_SBCM_RR_01_200ms; 
  tVAR	TimeOut_SMK_06_200ms;     
  tVAR	TimeOut_VCU_01_10ms_1;
  tVAR	TimeOut_WPC2_01_200ms;
  tVAR	TimeOut_WPC_01_200ms;
  tVAR  TimeOut_ATS_00_00ms;
  
  /* LCAN TimeOut */
  tVAR	TimeOut_WPCNFCcmd;
  tVAR	TimeOut_BDCWPCNFCCmd;
  tVAR	TimeOut_DeviceOnWPC;
  tVAR	TimeOut_BDC_Status;
  tVAR	TimeOut_OwnerKeyRegStatus;
}tAPP_CAN_INPUT;

#endif

#endif  /* __APP_CAN_INPUT_TYPE_H__ */
