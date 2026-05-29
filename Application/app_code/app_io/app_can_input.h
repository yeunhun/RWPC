/******************************************************************************
 * Project        :   IBU
 * File Name      :   app_can_input.h
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
#ifndef __APP_CAN_INPUT_H__
#define __APP_CAN_INPUT_H__

#include "WPCType.h"


/*******************************************************************************
  Declare External  Function
*******************************************************************************/
extern void Input_BCAN(void);
extern void Input_LCAN(void);





/*******************************************************************************
  Declare External  Variables
*******************************************************************************/
extern  tAPP_CAN_INPUT  APP_CAN_INPUT_IF;

extern  stCanAppFlag  BCANTimeOutFlag;
extern  stCanAppFlag  BCANTimeOutFlag1;
extern  stCanAppFlag  LCANTimeOutFlag;
//extern  stCanAppFlag  BCANTimeOutFlag2;
extern  stCanAppFlag  BCANIndFlag;
extern  stCanAppFlag  BCANIndFlag1;
extern  stCanAppFlag  LCANIndFlag;
//extern  stCanAppFlag  BCANIndFlag2;
extern  stCanAppFlag  BCANNmIndFlag;

/* INPUT B-CAN */
/* BCM_07_200ms */
#define  kC_Lamp_IntTailLmpOnReq         APP_CAN_INPUT_IF.Lamp_IntTailLmpOnReq
/* BCM_12_200ms */
#define  kC_BCM_SmkOptTyp                APP_CAN_INPUT_IF.BCM_SmkOptTyp
/* CLU_01_20ms_1 */
#define  kC_CLU_DtntOutSta               APP_CAN_INPUT_IF.CLU_DtntOutSta
#define  kC_CLU_RhstaLvlSta              APP_CAN_INPUT_IF.CLU_RhstaLvlSta
/* CLU_01_20ms_2 */
#define  kC_CLU_DisSpdVal_KPH            APP_CAN_INPUT_IF.CLU_DisSpdVal_KPH
#define  kC_CLU_AutoBrightSta            APP_CAN_INPUT_IF.CLU_AutoBrightSta
/* CLU_05_00ms_1 */
#define  kC_USM_StaRst1Req               APP_CAN_INPUT_IF.USM_StaRst1Req
/* CLU_09_00ms_1 */
#define  kC_USM_WpcSetReq                APP_CAN_INPUT_IF.USM_WpcSetReq
/* CLU_20_200ms_1 */
#define  kC_CLU_ClusterUSM               APP_CAN_INPUT_IF.CLU_ClusterUSM
/* EMS_02_10ms_1 */
#define  kC_ENG_EngSta                   APP_CAN_INPUT_IF.ENG_EngSta
/* EMS_07_10ms_2 */
#define  kC_HEV_EngOpSta                 APP_CAN_INPUT_IF.HEV_EngOpSta
/* HCU_03_10ms_2 */
#define  kC_HCU_HevRdySta                APP_CAN_INPUT_IF.HCU_HevRdySta
/* HU_GW_PE_01 */
#define  kC_CF_AVN_ProfileIDRValue       APP_CAN_INPUT_IF.CF_AVN_ProfileIDRValue
/* HU_USM_E_02 */
#define  kC_CF_Gway_RWPCNValueSet         APP_CAN_INPUT_IF.CF_Gway_RWPCNValueSet
/* HU_USM_E_04 */
#define  kC_CF_AVN_CluUSMReset           APP_CAN_INPUT_IF.CF_AVN_CluUSMReset
/* HU_USM_E_14 */
#define  kC_CF_Gway_WPCAnimationNvalueSet APP_CAN_INPUT_IF.CF_Gway_WPCAnimationNvalueSet
/* IAU_16_200ms */
#define  kC_IAU_DigitalKey2Opt           APP_CAN_INPUT_IF.IAU_DigitalKey2Opt
#define  kC_IAU_ProfileIDRVal            APP_CAN_INPUT_IF.IAU_ProfileIDRVal
/* ICU_02_200ms */
#define  kC_Warn_AsstDrSwSta             APP_CAN_INPUT_IF.Warn_AsstDrSwSta
#define  kC_Warn_RrRtDrSwSta             APP_CAN_INPUT_IF.Warn_RrRtDrSwSta
#define  kC_Warn_DrvDrSwSta              APP_CAN_INPUT_IF.Warn_DrvDrSwSta
#define  kC_Warn_RrLftDrSwSta            APP_CAN_INPUT_IF.Warn_RrLftDrSwSta
/* SBCM_AST_02_200ms */
#define  kC_Warn_AsstDrSwSta_SBCM        APP_CAN_INPUT_IF.Warn_AsstDrSwSta_SBCM
/* SBCM_DRV_01_200ms */
#define  kC_Latch_TypeOption_DRV         APP_CAN_INPUT_IF.Latch_TypeOption_DRV
#define  kC_Warn_DrvDrSwSta_SBCM         APP_CAN_INPUT_IF.Warn_DrvDrSwSta_SBCM
/* SBCM_RL_01_200ms */
#define  kC_Warn_RrLftDrSwSta_SBCM       APP_CAN_INPUT_IF.Warn_RrLftDrSwSta_SBCM
/* SBCM_RR_01_200ms */
#define  kC_Warn_RrRtDrSwSta_SBCM        APP_CAN_INPUT_IF.Warn_RrRtDrSwSta_SBCM
/* SMK_06_200ms */
#define  kC_LFAnt_SrchSta                APP_CAN_INPUT_IF.LFAnt_SrchSta
/* VCU_01_10ms_1 */
#define  kC_VCU_EvDrvRdySta              APP_CAN_INPUT_IF.VCU_EvDrvRdySta
/* WPC2_01_200ms */
#define  kC_WPC2_IndSyncVal				 APP_CAN_INPUT_IF.WPC2_IndSyncVal
/* WPC_01_200ms */
#define  kC_WPC_IndSyncVal				 APP_CAN_INPUT_IF.WPC_IndSyncVal
#define  kC_USM_CmdWPCIndSta			 APP_CAN_INPUT_IF.USM_CmdWPCIndSta
/* ATS_00_00ms */
#define  kC_ATS_RWPC_RWPCNValueSet		 APP_CAN_INPUT_IF.ATS_RWPC_RWPCNValueSet

#define  kC_AccInSta                  	 APP_CAN_INPUT_IF.AccInSta
#define  kC_Ign1Insta                    APP_CAN_INPUT_IF.Ign1Insta

/* INPUT LOCAL-CAN */
/* LOCALCAN_BDC_01 */
#define  kC_WPCNFCcmd                    APP_CAN_INPUT_IF.WPCNFCcmd
#define  kC_BDCWPCNFCCmd                 APP_CAN_INPUT_IF.BDCWPCNFCCmd
/* LOCALCAN_BDC_10 */
#define  kC_DeviceOnWPC                  APP_CAN_INPUT_IF.DeviceOnWPC
#define  kC_BDC_Status                   APP_CAN_INPUT_IF.BDC_Status
#define  kC_OwnerKeyRegStatus			 APP_CAN_INPUT_IF.OwnerKeyRegStatus

/* BCAN TimeOut */
#define TimeOut_BCM_07_200ms			 APP_CAN_INPUT_IF.TimeOut_BCM_07_200ms	        
#define TimeOut_BCM_12_200ms       		 APP_CAN_INPUT_IF.TimeOut_BCM_12_200ms      
#define TimeOut_CLU_01_20ms_1      		 APP_CAN_INPUT_IF.TimeOut_CLU_01_20ms_1     
#define TimeOut_CLU_01_20ms_2      		 APP_CAN_INPUT_IF.TimeOut_CLU_01_20ms_2     
#define TimeOut_CLU_05_00ms_1      		 APP_CAN_INPUT_IF.TimeOut_CLU_05_00ms_1     
#define TimeOut_CLU_09_00ms_1      		 APP_CAN_INPUT_IF.TimeOut_CLU_09_00ms_1     
#define TimeOut_CLU_20_200ms_1     		 APP_CAN_INPUT_IF.TimeOut_CLU_20_200ms_1    
#define TimeOut_EMS_02_10ms_1            APP_CAN_INPUT_IF.TimeOut_EMS_02_10ms_1     
#define TimeOut_EMS_07_10ms_2      		 APP_CAN_INPUT_IF.TimeOut_EMS_07_10ms_2     
#define TimeOut_HCU_03_10ms_2      		 APP_CAN_INPUT_IF.TimeOut_HCU_03_10ms_2     
#define TimeOut_HU_GW_PE_01        		 APP_CAN_INPUT_IF.TimeOut_HU_GW_PE_01       
#define TimeOut_HU_USM_E_02        		 APP_CAN_INPUT_IF.TimeOut_HU_USM_E_02       
#define TimeOut_HU_USM_E_04        		 APP_CAN_INPUT_IF.TimeOut_HU_USM_E_04
#define TimeOut_HU_USM_E_14        		 APP_CAN_INPUT_IF.TimeOut_HU_USM_E_14
#define TimeOut_IAU_16_200ms       		 APP_CAN_INPUT_IF.TimeOut_IAU_16_200ms      
#define TimeOut_ICU_02_200ms       		 APP_CAN_INPUT_IF.TimeOut_ICU_02_200ms      

#define TimeOut_SBCM_AST_02_200ms  		 APP_CAN_INPUT_IF.TimeOut_SBCM_AST_02_200ms 
#define TimeOut_SBCM_DRV_01_200ms  		 APP_CAN_INPUT_IF.TimeOut_SBCM_DRV_01_200ms 
#define TimeOut_SBCM_RL_01_200ms   		 APP_CAN_INPUT_IF.TimeOut_SBCM_RL_01_200ms  
#define TimeOut_SBCM_RR_01_200ms   		 APP_CAN_INPUT_IF.TimeOut_SBCM_RR_01_200ms  
#define TimeOut_SMK_06_200ms      	     APP_CAN_INPUT_IF.TimeOut_SMK_06_200ms      
#define TimeOut_VCU_01_10ms_1      		 APP_CAN_INPUT_IF.TimeOut_VCU_01_10ms_1   
#define TimeOut_WPC2_01_200ms      		 APP_CAN_INPUT_IF.TimeOut_WPC2_01_200ms   
#define TimeOut_WPC_01_200ms			 APP_CAN_INPUT_IF.TimeOut_WPC_01_200ms
#define TimeOut_ATS_00_00ms				 APP_CAN_INPUT_IF.TimeOut_ATS_00_00ms

/* LCAN TimeOut */
#define TimeOut_WPCNFCcmd				 APP_CAN_INPUT_IF.TimeOut_WPCNFCcmd
#define TimeOut_BDCWPCNFCCmd			 APP_CAN_INPUT_IF.TimeOut_BDCWPCNFCCmd
#define TimeOut_DeviceOnWPC				 APP_CAN_INPUT_IF.TimeOut_DeviceOnWPC
#define TimeOut_BDC_Status				 APP_CAN_INPUT_IF.TimeOut_BDC_Status


/* CAN IND & Timeout Flag */
#define BCANTimeOut_BCM_07_200ms          BCANTimeOutFlag.Bit.b0
#define BCANTimeOut_BCM_12_200ms          BCANTimeOutFlag.Bit.b1
#define BCANTimeOut_CLU_01_20ms_1         BCANTimeOutFlag.Bit.b2
#define BCANTimeOut_CLU_01_20ms_2         BCANTimeOutFlag.Bit.b3
#define BCANTimeOut_CLU_05_00ms_1         BCANTimeOutFlag.Bit.b4
#define BCANTimeOut_CLU_09_00ms_1         BCANTimeOutFlag.Bit.b5
#define BCANTimeOut_CLU_20_200ms_1        BCANTimeOutFlag.Bit.b6
#define BCANTimeOut_EMS_02_10ms_1         BCANTimeOutFlag.Bit.b7
#define BCANTimeOut_EMS_07_10ms_2         BCANTimeOutFlag.Bit.b8
#define BCANTimeOut_HCU_03_10ms_2         BCANTimeOutFlag.Bit.b9
#define BCANTimeOut_HU_GW_PE_01           BCANTimeOutFlag.Bit.b10
#define BCANTimeOut_HU_USM_E_02           BCANTimeOutFlag.Bit.b11
#define BCANTimeOut_HU_USM_E_04           BCANTimeOutFlag.Bit.b12
#define BCANTimeOut_IAU_16_200ms          BCANTimeOutFlag.Bit.b13
#define BCANTimeOut_ICU_02_200ms          BCANTimeOutFlag.Bit.b14

#define BCANTimeOut_SBCM_AST_02_200ms     BCANTimeOutFlag1.Bit.b0
#define BCANTimeOut_SBCM_DRV_01_200ms     BCANTimeOutFlag1.Bit.b1
#define BCANTimeOut_SBCM_RL_01_200ms      BCANTimeOutFlag1.Bit.b2
#define BCANTimeOut_SBCM_RR_01_200ms      BCANTimeOutFlag1.Bit.b3
#define BCANTimeOut_SMK_06_200ms          BCANTimeOutFlag1.Bit.b4
#define BCANTimeOut_VCU_01_10ms_1         BCANTimeOutFlag1.Bit.b5
#define BCANTimeOut_HU_USM_E_14			  BCANTimeOutFlag1.Bit.b6	
#define BCANTimeOut_WPC2_01_200ms		  BCANTimeOutFlag1.Bit.b7
#define BCANTimeOut_WPC_01_200ms		  BCANTimeOutFlag1.Bit.b8
#define BCANTimeOut_ATS_00_00ms		  	  BCANTimeOutFlag1.Bit.b9


/* LCAN Timeout */
#define LCANTimeOut_BDC_01				  LCANTimeOutFlag.Bit.b0
#define LCANTimeOut_BDC_10				  LCANTimeOutFlag.Bit.b1




/* BCAN */			
#define BCAN_App_Ind_BCM_07_200ms         BCANIndFlag.Bit.b0
#define BCAN_App_Ind_BCM_12_200ms         BCANIndFlag.Bit.b1
#define BCAN_App_Ind_CLU_01_20ms_1        BCANIndFlag.Bit.b2
#define BCAN_App_Ind_CLU_01_20ms_2        BCANIndFlag.Bit.b3
#define BCAN_App_Ind_CLU_05_00ms_1        BCANIndFlag.Bit.b4
#define BCAN_App_Ind_CLU_09_00ms_1        BCANIndFlag.Bit.b5
#define BCAN_App_Ind_CLU_20_200ms_1       BCANIndFlag.Bit.b6
#define BCAN_App_Ind_EMS_02_10ms_1        BCANIndFlag.Bit.b7
#define BCAN_App_Ind_EMS_07_10ms_2        BCANIndFlag.Bit.b8
#define BCAN_App_Ind_HCU_03_10ms_2        BCANIndFlag.Bit.b9
#define BCAN_App_Ind_HU_GW_PE_01          BCANIndFlag.Bit.b10
#define BCAN_App_Ind_HU_USM_E_02          BCANIndFlag.Bit.b11
#define BCAN_App_Ind_HU_USM_E_04          BCANIndFlag.Bit.b12
#define BCAN_App_Ind_HU_USM_E_14          BCANIndFlag.Bit.b13
#define BCAN_App_Ind_IAU_16_200ms         BCANIndFlag.Bit.b14
#define BCAN_App_Ind_ICU_02_200ms         BCANIndFlag.Bit.b15


#define BCAN_App_Ind_SBCM_AST_02_200ms    BCANIndFlag1.Bit.b0
#define BCAN_App_Ind_SBCM_DRV_01_200ms    BCANIndFlag1.Bit.b1
#define BCAN_App_Ind_SBCM_RL_01_200ms     BCANIndFlag1.Bit.b2
#define BCAN_App_Ind_SBCM_RR_01_200ms     BCANIndFlag1.Bit.b3
#define BCAN_App_Ind_SMK_06_200ms         BCANIndFlag1.Bit.b4
#define BCAN_App_Ind_VCU_01_10ms_1        BCANIndFlag1.Bit.b5
#define BCAN_App_Ind_WPC2_01_200ms		  BCANIndFlag1.Bit.b6
#define BCAN_App_Ind_WPC_01_200ms		  BCANIndFlag1.Bit.b7
#define BCAN_App_Ind_ATS_00_00ms		  BCANIndFlag1.Bit.b8



/* LCAN */
#define LCAN_App_Ind_BDC_01				  LCANIndFlag.Bit.b0
#define LCAN_App_Ind_BDC_10				  LCANIndFlag.Bit.b1
#define LCAN_App_Ind_TP_BDC_C_WPC		  LCANIndFlag.Bit.b2

/*******************************************************************************
  Define Parameter
*******************************************************************************/



/*******************************************************************************
  Define Constant and Macro
*******************************************************************************/
/*************** AUTOSAR API ********************/
//#include "Rte_swc_can_input.h"
/*************** AUTOSAR API ********************/
/* Client Server Interface */


#endif  /* __APP_CAN_INPUT_H__ */
