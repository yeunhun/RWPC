/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dcm_Cfg.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides Dcm configuration                                    **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.23.1.0  06-Jun-2022   JSCHOI       Redmine #36032                        **
** 1.21.0    27-Oct-2021   JYS          Redmine #29277 #29449                 **
** 1.15.1.0  17-May-2021   SK Park      Redmine #29359                        **
** 1.14.0    07-May-2021   JYS          Redmine #29660 #29285                 **
** 1.12.0.0  12-Mar-2021   JHLim        Redmine #24088                        **
** 1.0.2     06-Nov-2020   JYS          Redmine #26489                        **
** 1.0.1     26-Oct-2020   JYS          Redmine #26261                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Dcm.h"
#include "Dcm_Internal.h"
#include "Dcm_Cfg.h"
#include "Dcm_Types.h"

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/
#define BTL_START_SEC_VAR_INIT
#include "Btl_MemMap.h"

Dcm_PduIdTable_Styp Dcm_Gast_PduIdConfigTab[DCM_PDUID_COUNT] =
{
  /* PduId 0 - RxPduId_0 */
  {
    /* dt_TxPduId */
    0x00,

    /* u16_RxCopiedLength */
    0x0000,

    /* u16_TxCopiedLength */
    0x0000,

    /* u16_TxConfirmationPduId */
    0x00,
    
    /* u16_ProRxTesterSrcAddr */
    #if (FBL_COMM_CAN_ENABLE == STD_ON)
    FBL_CAN_DIAG_MSG_PHY_REQ_ID,
    #elif (FBL_COMM_ENET_ENABLE == STD_ON)
    FBL_TESTER_PHYSICAL_LOCAL_ADDRESS,
    #endif

    /* u8_RxAddrType */
    DCM_ADDR_PHYSICAL,
  },

  /* PduId 1 - RxPduId_1 */
  {
    /* dt_TxPduId */
    0x00,

    /* u16_RxCopiedLength */
    0x0000,

    /* u16_TxCopiedLength */
    0x0000,

    /* u16_TxConfirmationPduId */
    0x00,
    
    /* u16_ProRxTesterSrcAddr */
    #if (FBL_COMM_CAN_ENABLE == STD_ON)
    FBL_CAN_DIAG_MSG_FUNC_REQ_ID,
    #elif (FBL_COMM_ENET_ENABLE == STD_ON)
    FBL_ECU_FUNCTIONAL_LOCAL_ADDRESS,
    #endif

    /* u8_RxAddrType */
    DCM_ADDR_FUNCTIONAL,
  }
};

#define BTL_STOP_SEC_VAR_INIT
#include "Btl_MemMap.h"

/*******************************************************************************
**                             Global Constants                               **
*******************************************************************************/
#define BTL_START_SEC_CONST
#include "Btl_MemMap.h"

const Dcm_LookUpTable_Styp Dcm_Kast_SecMaskList[DCM_MAX_SEC_LEVEL_COUNT] =
{
  {
    /* u8_LookUpTableID */
    DCM_SECURITY_LEVEL_0,

    /* u8_Mask */
    DCM_SECURITY_LEVEL_0_MASK,

    /* u8_SecurityLevel */
    DCM_SECURITY_LEVEL_0_L0
  },
  {
    /* u8_LookUpTableID */
    DCM_SECURITY_LEVEL_11,

    /* u8_Mask */
    DCM_SECURITY_LEVEL_11_MASK,

    /* u8_SecurityLevel */
    DCM_SECURITY_LEVEL_11_L9
  },
  {
    /* u8_LookUpTableID */
    DCM_SECURITY_LEVEL_41,

    /* u8_Mask */
    DCM_SECURITY_LEVEL_41_MASK,

    /* u8_SecurityLevel */
    DCM_SECURITY_LEVEL_41_L21
  },
  {
    /* u8_LookUpTableID */
    DCM_SECURITY_LEVEL_01,

    /* u8_Mask */
    DCM_SECURITY_LEVEL_01_MASK,

    /* u8_SecurityLevel */
    DCM_SECURITY_LEVEL_01_L1
  }

};

const Dcm_LookUpTable_Styp Dcm_Kast_SesMaskList[DCM_MAX_SESSION_COUNT] =
{
  {
    /* u8_LookUpTableID */
    DCM_DEFAULT_SESSION ,

    /* u8_Mask */
    DCM_DEFAULT_SESSION_MASK
  },
  {
    /* u8_LookUpTableID */
    DCM_PROG_SESSION,

    /* u8_Mask */
    DCM_PROG_SESSION_MASK
  },
  {
    /* u8_LookUpTableID */
    DCM_EXTENDED_SESSION,

    /* u8_Mask */
    DCM_EXTENDED_SESSION_MASK
  }
#if (FBL_SUPPORT_DIAGNOSTIC_STANDARD == FBL_ES95486_00)
  ,
  {
    /* u8_LookUpTableID */
	DCM_ECU_PROG_MODE,

    /* u8_Mask */
    DCM_ECU_PROG_MODE_MASK
  },
  {
    /* u8_LookUpTableID */
	DCM_EXTENDED_DIAGNOSTIC_MODE,

    /* u8_Mask */
	DCM_EXTENDED_DIAGNOSTIC_MODE_MASK
  }

#endif
};

const uint8 Dcm_Kau8_RxPduIdMaskList[DCM_PDUID_COUNT] =
{
  DCM_ADDR_PHYSICAL_MASK,
  DCM_ADDR_FUNCTIONAL_MASK
};

#if (DCM_DIAGSESSIONCONTROL_SERVICE == STD_ON)
const Dcm_SubServiceConfig_Styp Dcm_Kast_SesCtrlSubFunc[DCM_MAX_SESSION_COUNT] =
{
  {
    /* SubFunctionID */
    DCM_DEFAULT_SESSION,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  },
  {
    /* SubFunctionID */
    DCM_PROG_SESSION,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    #if ((FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SECUREACCESS_1_0)\
    || (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SECUREACCESS_2_0))
    DCM_SECURITY_LEVEL_41_MASK
    #else
    DCM_SECURITY_LEVEL_0_MASK
    #endif
  },
  {
    /* SubFunctionID */
    DCM_EXTENDED_SESSION,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_DEFAULT_SESSION_MASK | DCM_EXTENDED_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  }
#if (FBL_SUPPORT_DIAGNOSTIC_STANDARD == FBL_ES95486_00)
  ,
  {
	/* SubFunctionID */
	DCM_ECU_PROG_MODE,

	/* AddrModeSupportMask */
	DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

	/* SessionSupportMask */
	DCM_ALL_SESSION_MASK,

	/* SecLevelMask */
	#if ((FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SECUREACCESS_1_0)\
	|| (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SECUREACCESS_2_0))
	DCM_SECURITY_LEVEL_41_MASK
	#else
	DCM_SECURITY_LEVEL_0_MASK
	#endif
  },
  {
	/* SubFunctionID */
	DCM_EXTENDED_DIAGNOSTIC_MODE,

	/* AddrModeSupportMask */
	DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

	/* SessionSupportMask */
    DCM_DEFAULT_SESSION_MASK | DCM_EXTENDED_DIAGNOSTIC_MODE_MASK,

	/* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  }
#endif
};
#endif

#if (DCM_ECURESET_SERVICE == STD_ON)
const Dcm_SubServiceConfig_Styp
Dcm_Kast_ECUResetSubFunc[DCM_MAX_RESET_TYPE_COUNT] =
{
  {
   /* SubFunctionID */
    DCM_RESET_HARD,

   /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

   /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

   /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  }
};
#endif

#if (DCM_TESTERPRESENT_SERVICE == STD_ON)
const Dcm_SubServiceConfig_Styp Dcm_Kast_TesterPresentSubFunc[DCM_ONE] =
{
  {
    /* SubFunctionID */
    DCM_TESTERPRESENT_SUBFUNC,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  }
};
#endif

#if (DCM_SECURITYACCESS_SERVICE == STD_ON)
const Dcm_SubServiceConfig_Styp
Dcm_Gast_SecAccessSubFunc[DCM_MAX_SEC_SUBFUNC_COUNT] =
{
  #if (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_ADVANCED_SEEDKEY)
  {
    /* SubFunctionID */
    DCM_SECURITY_LEVEL_11_SEED,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  },
  {
    /* SubFunctionID */
    DCM_SECURITY_LEVEL_11_KEY,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  },
  #elif ((FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SECUREACCESS_1_0)\
    || (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SECUREACCESS_2_0))
  {
    /* SubFunctionID */
    DCM_SECURITY_LEVEL_41_SEED,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  },
  {
    /* SubFunctionID */
    DCM_SECURITY_LEVEL_41_KEY,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  },
  #elif (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SEEDKEY)
  {
    /* SubFunctionID */
    DCM_SECURITY_LEVEL_01_SEED,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  },
  {
    /* SubFunctionID */
    DCM_SECURITY_LEVEL_01_KEY,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  }
  #endif
};
#endif

#if (DCM_SECURITYACCESS_SERVICE == STD_ON)
const Dcm_SecurityLevConfig_Styp
Dcm_Kast_SecurityLevConfig[DCM_SUPPORTED_SEC_LEVEL_COUNT] =
{
  /* Security Level 11 */
  {
    /* dt_SecLevel */
    DCM_SECURITY_LEVEL_11,

    /* ulSizeOfKey */
    DCM_EIGHT,

    /* ulSizeOfSeed */
    DCM_EIGHT,

    /* usSecDelayInvKey */
    DCM_ZERO,

    /* ucSecNumMaxAttDelay */
    2U,

    /* u16_SeedRequestMaxLength */
    2U
  },
  /* Security Level 41 */
  {
    /* dt_SecLevel */
    DCM_SECURITY_LEVEL_41,

    /* ulSizeOfKey */
    256U,

    /* ulSizeOfSeed */
    DCM_EIGHT,

    /* usSecDelayInvKey */
    DCM_ZERO,

    /* ucSecNumMaxAttDelay */
    2U,

    /* u16_SeedRequestMaxLength */
    #if (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SECUREACCESS_2_0)
    1101U
    #else
    602U
    #endif
  },
  /* Security Level 01 */
  {
    /* dt_SecLevel */
    DCM_SECURITY_LEVEL_01,

    /* ulSizeOfKey */
    DCM_FOUR,

    /* ulSizeOfSeed */
    DCM_FOUR,

    /* usSecDelayInvKey */
    DCM_ZERO,

    /* ucSecNumMaxAttDelay */
    2U,

    /* u16_SeedRequestMaxLength */
    2U
  }
};
#endif

#if (DCM_READDATABYID_SERVICE == STD_ON)
const Dcm_DspDIDConfig_Styp Dcm_Kast_DIDConfig[DCM_MAX_DID_COUNT] =
{
  {
    /* DID Number */
    DCM_READDATABYID_DID_F186,

    /* Size of DID */
    DCM_READDATABYID_DID_F186_SIZE
  }
};
#endif

#if (DCM_WRITEDATABYID_SERVICE == STD_ON)
Dcm_SubServiceConfig_Styp Dcm_Kast_WriteDIDSubFunc[DCM_WRITE_DID_COUNT] =
{
  /* Dummy implementation- for reference only */
  {
    /* DID Number */
    DCM_READDATABYID_DID_F186,

    /* Size of DID */
    DCM_READDATABYID_DID_F186_SIZE
  }
};
#endif

#if (DCM_ROUTINECONTROL_SERVICE == STD_ON)
const Dcm_SubServiceConfig_Styp Dcm_Kast_RoutineCtrlSubFunc[DCM_ONE] =
{
  {
    /* SubFunctionID */
    DCM_ROUTINE_START,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

     /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  }
};
#endif

#if (DCM_ROUTINECONTROL_SERVICE == STD_ON)
const Dcm_DspRIDConfig_Styp Dcm_Kast_RIDConfig[DCM_MAX_RID_COUNT] =
{
  {
    /* u16_RID */
    DCM_ROUTINE_ERASE_MEMORY,

    /* SecLevelMask */
    #if (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_ADVANCED_SEEDKEY)
    DCM_SECURITY_LEVEL_11_MASK,
    #elif ((FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SECUREACCESS_1_0)\
    || (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SECUREACCESS_2_0))
    DCM_SECURITY_LEVEL_41_MASK,
    #elif (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SEEDKEY)
    DCM_SECURITY_LEVEL_01_MASK,
    #endif

    /* SessionSupportMask */
#if (FBL_SUPPORT_DIAGNOSTIC_STANDARD == FBL_ES95486_00)
	DCM_PROG_SESSION_MASK | DCM_ECU_PROG_MODE_MASK,
#else
	DCM_PROG_SESSION_MASK,
#endif

    /* u8_ReqMsgLenStart */
    DCM_ERASEMEMORY_REQ_LENGTH,

    /* u8_ReqMsgLenReqRes */
    DCM_ZERO,

    /* u8_ReqMsgLenStop */
    DCM_ZERO
  },
  {
    /* u16_RID */
    DCM_ROUTINE_SECUREFLASHING_CHECK,

    /* SecLevelMask */
    #if (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_ADVANCED_SEEDKEY)
    DCM_SECURITY_LEVEL_11_MASK,
    #elif ((FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SECUREACCESS_1_0)\
    || (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SECUREACCESS_2_0))
    DCM_SECURITY_LEVEL_41_MASK,
    #elif (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SEEDKEY)
    DCM_SECURITY_LEVEL_01_MASK,
    #endif

    /* SessionSupportMask */
#if (FBL_SUPPORT_DIAGNOSTIC_STANDARD == FBL_ES95486_00)
	DCM_PROG_SESSION_MASK | DCM_ECU_PROG_MODE_MASK,
#else
	DCM_PROG_SESSION_MASK,
#endif

    /* u8_ReqMsgLenStart */
    DCM_SECUREFLASHING_CHECK_REQ_LENGTH,

    /* u8_ReqMsgLenReqRes */
    DCM_ZERO,

    /* u8_ReqMsgLenStop */
    DCM_ZERO
  },
  {
    /* u16_RID */
    DCM_ROUTINE_OTA_READY,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* u8_ReqMsgLenStart */
    DCM_OTA_READY_REQ_LENGTH,

    /* u8_ReqMsgLenReqRes */
    DCM_ZERO,

    /* u8_ReqMsgLenStop */
    DCM_ZERO
  }
};
#endif

#if (DCM_LINKCONTROL_SERVICE == STD_ON)
const Dcm_SubServiceConfig_Styp Dcm_Kast_LinkCtrlSubFunc[DCM_THREE] =
{
  {
    /* SubFunctionID */
    DCM_VERIFY_MODE_TRANSITION_FIXED_PARAM,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  },
  {
    /* SubFunctionID */
    DCM_VERIFY_MODE_TRANSITION_SPECIFIC_PARAM,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  },
  {
    /* SubFunctionID */
    DCM_TRANSITION_MODE,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  }
};
#endif

#if (DCM_COMMUNICATIONCONTROL_SERVICE == STD_ON)
const Dcm_SubServiceConfig_Styp Dcm_Kast_CommCtrlSubFunc[DCM_FOUR] =
{
  {
    /* SubFunctionID */
    DCM_ENABLE_RX_TX,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  },
  {
    /* SubFunctionID */
    DCM_ENABLE_RX_DISABLE_TX,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  },
  {
    /* SubFunctionID */
    DCM_DISABLE_RX_ENABLE_TX,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  },
  {
    /* SubFunctionID */
    DCM_DISABLE_RX_TX,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  }
};
#endif

#if (DCM_CONTROLDTCSETTING_SERVICE == STD_ON)
const Dcm_SubServiceConfig_Styp Dcm_Kast_CtrlDTCSettingsSubFunc[DCM_TWO] =
{
  {
    /* SubFunctionID */
    DCM_DTC_ON,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  },
  {
    /* SubFunctionID */
    DCM_DTC_OFF,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  }
};
#endif

#if (DCM_ACCESSTIMINGPARAMETERS_SERVICE == STD_ON)
const Dcm_SubServiceConfig_Styp Dcm_Kast_AccessTimingParamSubFunc[DCM_ONE] =
{
  {
    /* SubFunctionID */
    DCM_SET_TIMING_PARAMETERS_TO_GIVEN_VALUES,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
#if (FBL_SUPPORT_DIAGNOSTIC_STANDARD == FBL_ES95486_00)
	DCM_PROG_SESSION_MASK | DCM_ECU_PROG_MODE_MASK,
#else
	DCM_PROG_SESSION_MASK,
#endif
    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK
  }
};
#endif

const Dcm_SIDConfig_Styp Dcm_Kast_SIdConfig[DCM_MAX_SERVICE_COUNT] =
{

  #if (DCM_DIAGSESSIONCONTROL_SERVICE == STD_ON)
  /* Sid Config - DiagSessionControl service */
  {
    /* *p2Function */
    Dcm_DcmDiagnosticSessionControl,

    /* ucServiceId */
    DCM_DIAGNOSTICSESSIONCONTROL,

    /* ucMinReqLength */
    DCM_TWO,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK,

    /* blSubFunctionAvailable */
    DCM_TRUE,

    /* u8_SubFncCount */
	DCM_MAX_SESSION_COUNT,


    /* u8_SubFncIDSize */
    DCM_ONE,

    /* pdt_SubFuncRef */
    Dcm_Kast_SesCtrlSubFunc
  }
  #endif

  #if (DCM_ECURESET_SERVICE == STD_ON)
  ,
  /* Sid Config - ECU Reset service */
  {
    /* *p2Function */
    Dcm_DcmECUResetService,

    /* ucServiceId */
    DCM_ECURESET,

    /* ucMinReqLength */
    DCM_TWO,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* u8_SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK,

    /* blSubFunctionAvailable */
    DCM_TRUE,

    /* u8_SubFncCount */
    DCM_ONE,

    /* u8_SubFncIDSize */
    DCM_ONE,

    /* pdt_SubFuncRef */
    Dcm_Kast_ECUResetSubFunc
  }
  #endif

  #if (DCM_SECURITYACCESS_SERVICE == STD_ON)
  ,
  /* Sid Config - Security Access Service */
  {
    /* *p2Function */
    Dcm_DcmSecurityAccess,

    /* ucServiceId */
    DCM_SECURITYACCESS,

    /* ucMinReqLength */
    DCM_TWO,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK,

    /* blSubFunctionAvailable */
    DCM_TRUE,

    /* u8_SubFncCount */
    DCM_MAX_SEC_SUBFUNC_COUNT, /* For Seed and Key for each Level */

    /* u8_SubFncIDSize */
    DCM_ONE,

    /* pdt_SubFuncRef */
    Dcm_Gast_SecAccessSubFunc
  }
  #endif

  #if (DCM_READDATABYID_SERVICE == STD_ON)
  ,
  /* Sid Config - ReadDataById Service */
  {
    /* *p2Function */
    Dcm_DcmReadDataByIdentifier,

    /* ucServiceId */
    DCM_READDATABYIDENTIFIER,

    /* ucMinReqLength */
    DCM_THREE,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK,

    /* blSubFunctionAvailable */
    DCM_FALSE,

    /* u8_SubFncCount */
    DCM_MAX_DID_COUNT,

    /* u8_SubFncIDSize */
    DCM_TWO,

    /* pdt_SubFuncRef */
    NULL_PTR
  }
  #endif

  #if (DCM_ROUTINECONTROL_SERVICE == STD_ON)
  ,
  /* Sid Config - RoutineControl Service */
  {
    /* *p2Function */
    Dcm_DcmRoutineControl,

    /* ucServiceId */
    DCM_ROUTINECONTROL,

    /* ucMinReqLength */
    DCM_FOUR,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK,

    /* blSubFunctionAvailable */
    DCM_TRUE,

    /* u8_SubFncCount */
    DCM_ONE,

    /* u8_SubFncIDSize */
    DCM_ONE,

    /* pdt_SubFuncRef */
    Dcm_Kast_RoutineCtrlSubFunc
  },
  #endif

  #if (DCM_REQUESTDOWNLOAD_SERVICE == STD_ON)
  /* Sid Config - RequestDownload Service */
  {
    /* *p2Function */
    Dcm_DcmRequestDownload,

    /* ucServiceId */
    DCM_REQUESTDOWNLOAD,

    /* ucMinReqLength */
    DCM_FIVE,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
#if (FBL_SUPPORT_DIAGNOSTIC_STANDARD == FBL_ES95486_00)
	DCM_PROG_SESSION_MASK | DCM_ECU_PROG_MODE_MASK,
#else
	DCM_PROG_SESSION_MASK,
#endif

    /* SecLevelMask */
    #if (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_ADVANCED_SEEDKEY)
    DCM_SECURITY_LEVEL_11_MASK,
    #elif ((FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SECUREACCESS_1_0)\
    || (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SECUREACCESS_2_0))
    DCM_SECURITY_LEVEL_41_MASK,
    #elif (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SEEDKEY)
    DCM_SECURITY_LEVEL_01_MASK,
    #endif

    /* blSubFunctionAvailable */
    DCM_FALSE,

    /* u8_SubFncCount */
    DCM_ZERO,

    /* u8_SubFncIDSize */
    DCM_ZERO,

    /* pdt_SubFuncRef */
    NULL_PTR
  }
  #endif

  #if (DCM_TRANSFERDATA_SERVICE == STD_ON)
  ,
  /* Sid Config - TransferData Service */
  {
    /* *p2Function */
    Dcm_DcmTransferData,

    /* ucServiceId */
    DCM_TRANSFERDATA,

    /* ucMinReqLength */
    DCM_TWO,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
#if (FBL_SUPPORT_DIAGNOSTIC_STANDARD == FBL_ES95486_00)
	DCM_PROG_SESSION_MASK | DCM_ECU_PROG_MODE_MASK,
#else
	DCM_PROG_SESSION_MASK,
#endif

    /* SecLevelMask */
    #if (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_ADVANCED_SEEDKEY)
    DCM_SECURITY_LEVEL_11_MASK,
    #elif ((FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SECUREACCESS_1_0)\
    || (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SECUREACCESS_2_0))
    DCM_SECURITY_LEVEL_41_MASK,
    #elif (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SEEDKEY)
    DCM_SECURITY_LEVEL_01_MASK,
    #endif

    /* blSubFunctionAvailable */
    DCM_FALSE,

    /* u8_SubFncCount */
    DCM_ZERO,

    /* u8_SubFncIDSize */
    DCM_ZERO,

    /* pdt_SubFuncRef */
    NULL_PTR
  },
  #endif

  #if (DCM_REQTRANSFEREXIT_SERVICE == STD_ON)
  /* Sid Config - Request Transfer Exit Service */
  {
    /* *p2Function */
    Dcm_DcmRequestTransferExit,

    /* ucServiceId */
    DCM_REQUESTTRANSFEREXIT,

    /* ucMinReqLength */
    DCM_ONE,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
#if (FBL_SUPPORT_DIAGNOSTIC_STANDARD == FBL_ES95486_00)
	DCM_PROG_SESSION_MASK | DCM_ECU_PROG_MODE_MASK,
#else
	DCM_PROG_SESSION_MASK,
#endif

    /* SecLevelMask */
    #if (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_ADVANCED_SEEDKEY)
    DCM_SECURITY_LEVEL_11_MASK,
    #elif ((FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SECUREACCESS_1_0)\
    || (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SECUREACCESS_2_0))
    DCM_SECURITY_LEVEL_41_MASK,
    #elif (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SEEDKEY)
    DCM_SECURITY_LEVEL_01_MASK,
    #endif

    /* blSubFunctionAvailable */
    DCM_FALSE,

    /* u8_SubFncCount */
    DCM_ZERO,

    /* u8_SubFncIDSize */
    DCM_ZERO,

    /* pdt_SubFuncRef */
    NULL_PTR
  }
  #endif

  #if (DCM_TESTERPRESENT_SERVICE == STD_ON)
  ,
  /* Sid Config - Tester Present Service */
  {
    /* *p2Function */
    Dcm_DcmTesterPresent,

    /* ucServiceId */
    DCM_TESTERPRESENT,

    /* ucMinReqLength */
    DCM_TWO,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK,

    /* blSubFunctionAvailable */
    DCM_TRUE,

    /* u8_SubFncCount */
    DCM_ONE,

    /* u8_SubFncIDSize */
    DCM_ONE,

    /* pdt_SubFuncRef */
    Dcm_Kast_TesterPresentSubFunc
  }
  #endif

  #if (DCM_WRITEDATABYID_SERVICE == STD_ON)
  ,
  /* Sid Config - WriteDataByIdentifier Service */
  {
    /* *p2Function */
    Dcm_DcmWriteDataByIdentifier,

    /* ucServiceId */
    DCM_WRITEDATABYIDENTIFIER,

    /* ucMinReqLength */
    DCM_THREE,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    #if (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_ADVANCED_SEEDKEY)
    DCM_SECURITY_LEVEL_11_MASK,
    #elif ((FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SECUREACCESS_1_0)\
    || (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SECUREACCESS_2_0))
    DCM_SECURITY_LEVEL_41_MASK,
    #elif (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SEEDKEY)
    DCM_SECURITY_LEVEL_01_MASK,
    #endif

    /* blSubFunctionAvailable */
    DCM_FALSE,

    /* u8_SubFncCount */
    DCM_WRITE_DID_COUNT,

    /* u8_SubFncIDSize */
    DCM_TWO,

    /* pdt_SubFuncRef */
    Dcm_Kast_WriteDIDSubFunc
  }
  #endif

  #if (DCM_LINKCONTROL_SERVICE == STD_ON)
  ,
  /* Sid Config - Link Control Service */
  {
    /* *p2Function */
    Dcm_DcmLinkControl,

    /* ucServiceId */
    DCM_LINKCONTROL,

    /* ucMinReqLength */
    DCM_TWO,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
#if (FBL_SUPPORT_DIAGNOSTIC_STANDARD == FBL_ES95486_00)
	DCM_PROG_SESSION_MASK | DCM_ECU_PROG_MODE_MASK,
#else
	DCM_PROG_SESSION_MASK,
#endif

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK,

    /* blSubFunctionAvailable */
    DCM_TRUE,

    /* u8_SubFncCount */
    DCM_THREE,

    /* u8_SubFncIDSize */
    DCM_ONE,

    /* pdt_SubFuncRef */
    Dcm_Kast_LinkCtrlSubFunc
  }
  #endif

  #if (DCM_COMMUNICATIONCONTROL_SERVICE == STD_ON)
  ,
  /* Sid Config - Communication Control Service */
  {
    /* *p2Function */
    Dcm_DcmCommControl,

    /* ucServiceId */
    DCM_COMMUNICATIONCONTROL,

    /* ucMinReqLength */
    DCM_THREE,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK,

    /* blSubFunctionAvailable */
    DCM_TRUE,

    /* u8_SubFncCount */
    DCM_FOUR,

    /* u8_SubFncIDSize */
    DCM_ONE,

    /* pdt_SubFuncRef */
    Dcm_Kast_CommCtrlSubFunc
  }
  #endif

  #if (DCM_CONTROLDTCSETTING_SERVICE == STD_ON)
  ,
  /* Sid Config - Control DTC Settings Service */
  {
    /* *p2Function */
    Dcm_DcmCtrlDTCSettings,

    /* ucServiceId */
    DCM_CONTROLDTCSETTING,

    /* ucMinReqLength */
    DCM_TWO,

    /* AddrModeSupportMask */
    DCM_ADDR_PHYSICAL_MASK | DCM_ADDR_FUNCTIONAL_MASK,

    /* SessionSupportMask */
    DCM_ALL_SESSION_MASK,

    /* SecLevelMask */
    DCM_SECURITY_LEVEL_0_MASK,

    /* blSubFunctionAvailable */
    DCM_TRUE,

    /* u8_SubFncCount */
    DCM_TWO,

    /* u8_SubFncIDSize */
    DCM_ONE,

    /* pdt_SubFuncRef */
    Dcm_Kast_CtrlDTCSettingsSubFunc
  }
  #endif
};

const Dcm_SessionConfig_Styp Dcm_Kast_SessionConfigTable[DCM_MAX_SESSION_COUNT]=
{
  /* Session Control 0 - 1 */
  {
    /* SesP2StrServerMax */
    (uint16)(50U*1000 / DCM_TASK_TIME),

    /* SesP2ServerMax */
    (uint16)(5000U*1000 / DCM_TASK_TIME),

    /* SesCtrlLevel */

    DCM_DEFAULT_SESSION,

    /* SesForBootLevel */
    0x00
  },

  /* Session Control 1 - 2 */
  {
    /* SesP2StrServerMax */
    (uint16)(50U*1000 / DCM_TASK_TIME),

    /* SesP2ServerMax */
    (uint16)(5000U*1000 / DCM_TASK_TIME),

    /* SesCtrlLevel */
    DCM_PROG_SESSION,

    /* SesForBootLevel */
    0x00
  },
  /* Session Control 2 - 4 */
  {
    /* SesP2StrServerMax */
    (uint16)(50U*1000 / DCM_TASK_TIME),

    /* SesP2ServerMax */
    (uint16)(5000U*1000 / DCM_TASK_TIME),

    /* SesCtrlLevel */
    DCM_EXTENDED_SESSION,

    /* SesForBootLevel */
    0x00
  }
#if (FBL_SUPPORT_DIAGNOSTIC_STANDARD == FBL_ES95486_00)
  ,
  /* Session Control 3  */
  {
	/* SesP2StrServerMax */
	(uint16)(50U*1000 / DCM_TASK_TIME),

	/* SesP2ServerMax */
	(uint16)(5000U*1000 / DCM_TASK_TIME),

	/* SesCtrlLevel */
	DCM_ECU_PROG_MODE,

	/* SesForBootLevel */
	0x00
  },
  /* Session Control 4 */
  {
	/* SesP2StrServerMax */
	(uint16)(50U*1000 / DCM_TASK_TIME),

	/* SesP2ServerMax */
	(uint16)(5000U*1000 / DCM_TASK_TIME),

	/* SesCtrlLevel */
	DCM_EXTENDED_DIAGNOSTIC_MODE,

	/* SesForBootLevel */
	0x00
  }
#endif
};

#define BTL_STOP_SEC_CONST
#include "Btl_MemMap.h"

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
