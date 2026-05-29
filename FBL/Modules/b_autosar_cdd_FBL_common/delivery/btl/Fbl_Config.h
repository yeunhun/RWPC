/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fbl_Config.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Variable and functions affected when creating a library       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.23.0    27-Dec-2021   JH Lim       R40-Redmine #31776                    **
** 1.22.0    09-Nov-2021   JYS          Redmine #32899, #29462 #29282         **
** 1.21.0    27-Sep-2021   JYS          Redmine #31609                        **
** 1.19.0    30-Jul-2021   JYS          Redmine #29874                        **
** 1.17.0.0  16-Jul-2021   Sungwook     Redmine #29464                        **
** 1.15.0    12-May-2021   JYS          Redmine #28950                        **
** 1.12.0.0  12-Mar-2021   JHLim        Redmine #24088, #23964                **
** 1.11.0.0  17-Feb-2021   JYS          Redmine #28341                        **
** 1.10.0.0  07-Feb-2021   JYS          Redmine #28298 #27968                 **
** 1.0.10    22-Jan-2021   JYS          Redmine #27881                        **
** 1.0.9     06-Nov-2020   JYS          Redmine #26457                        **
** 1.0.8     05-Nov-2020   JYS          Redmine #26443                        **
** 1.0.7     19-Oct-2020   JYS          Redmine #26135                        **
** 1.0.6     13-Oct-2020   JYS          Redmine #25778                        **
** 1.0.5     12-Oct-2020   JYS          Redmine #26029                        **
** 1.0.4     29-Jul-2020   JYS          Redmine #24231                        **
** 1.0.3     02-Jul-2020   EK.Kim       Redmine #24460                        **
** 1.0.2     07-Feb-2020   Sinil        Redmine #21592, #21604                **
** 1.0.1     06-Dec-2019   Sinil        Redmine #20402                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef FBL_CONFIG_H
#define FBL_CONFIG_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Fbl_Cfg.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#define SEC_SEEDKEY_SEED_LEN                                                (4U)
#define SEC_SEEDKEY_KEY_LEN                                                 (4U)
#define SEC_HSAC_SEED_LEN                                                   (8U)
#define SEC_HSAC_KEY_LEN                                                    (8U)
#define SEC_CSAC_SEED_LEN                                                   (8U)
#define SEC_CSAC_RXKEY_LEN                                                (256U)
#define FBL_MAC_ADDR_SIZE                                                   (6U)

#if ((FBL_SUPPORT_MCU == FBL_MCU_TC38X) || (FBL_SUPPORT_MCU == FBL_MCU_TC39X) || \
	(FBL_SUPPORT_MCU == FBL_MCU_TC36X) || (FBL_SUPPORT_MCU == FBL_MCU_TC37X) || (FBL_SUPPORT_MCU == FBL_MCU_TC33X) || \
    (FBL_SUPPORT_MCU == FBL_MCU_TC23X) || (FBL_SUPPORT_MCU == FBL_MCU_TC29X))

#define FBL_FILL_BYTE                                                    (0x00U)

#elif ((FBL_SUPPORT_MCU == FBL_MCU_SPC58X) || (FBL_SUPPORT_MCU == FBL_MCU_RH850F1KM) || \
    (FBL_SUPPORT_MCU == FBL_MCU_CYTXXX))

#define FBL_FILL_BYTE                                                    (0xFFU)

#endif

#if (FBL_SECURE_FLASH_VERSION == FBL_SF_CRC)
#define FBL_USE_SECURE_FLASH                                           (STD_OFF)
#else
#define FBL_USE_SECURE_FLASH                                            (STD_ON)
#endif

#if (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SECUREACCESS_1_0) || (FBL_SECURITY_ACCESS_LEVEL == FBL_SA_SECUREACCESS_2_0) 
#define FBL_USE_SECURE_ACCESS                                           (STD_ON)
#else
#define FBL_USE_SECURE_ACCESS                                          (STD_OFF)
#endif

/*SHA is not needed when SeedKey or ASK & CRC */
#if (FBL_SECURE_ACCESS_HASH_ALGORITHM == FBL_SA_HASH_SHA160) || (FBL_SECURE_FLASH_HASH_ALGORITHM == FBL_SF_HASH_SHA160)
#if (FBL_USE_SECURE_FLASH == STD_ON) || (FBL_USE_SECURE_ACCESS == STD_ON)
#define FBL_USE_SHA160                                                  (STD_ON)
#else
#define FBL_USE_SHA160                                                 (STD_OFF)
#endif
#endif

#if (FBL_SECURE_ACCESS_HASH_ALGORITHM == FBL_SA_HASH_SHA256) || (FBL_SECURE_FLASH_HASH_ALGORITHM == FBL_SF_HASH_SHA256)
#if (FBL_USE_SECURE_FLASH == STD_ON) || (FBL_USE_SECURE_ACCESS == STD_ON)
#define FBL_USE_SHA256                                                  (STD_ON)
#else
#define FBL_USE_SHA256                                                 (STD_OFF)
#endif
#endif
/*end of SHA is not needed when SeedKey or ASK & CRC */

#if (FBL_SUPPORT_HSM == FBL_HSM_NONE)
#define FBL_USE_HSM                                                    (STD_OFF)
#else
#define FBL_USE_HSM                                                     (STD_ON)
#endif

#if (FBL_SUPPORT_HSM == FBL_HSM_AUTHSM_1_0)
#define FBL_USE_AUT_HSM                                                 (STD_ON)
#else
#define FBL_USE_AUT_HSM                                                (STD_OFF)
#endif

#if (FBL_SUPPORT_HSM == FBL_HSM_HAEHSM_2_0)
#define FBL_USE_HAE_HSM                                                 (STD_ON)
#else
#define FBL_USE_HAE_HSM                                                (STD_OFF)
#endif

#if (FBL_SECURITY_ACCESS_LEVEL != FBL_SA_SEEDKEY) && (FBL_SUPPORT_HSM == FBL_HSM_NONE)
#define FBL_USE_HAESWLIB_PRNG                                           (STD_ON)
#else
#define FBL_USE_HAESWLIB_PRNG                                          (STD_OFF)
#endif


/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/
/* FBL_SUPPORT_MCU */
extern const uint32 Fbl_Gu32_SupportMCU;

/* FBL_SUPPORT_HSM */
extern const uint32 Fbl_Gu32_SupportHSM;

/* FBL_SUPPORT_VERSION_CHECK */
extern const boolean Fbl_Gbl_SupportVersionCheck;

/* FBL_PARTITION_FLAG_ADDRESS */
extern uint32 Fbl_Gu32_PartitionFlasgAddress;
/* FBL_PARTITION_FLAG_SIZE */
extern const uint32 Fbl_Gu32_PartitionFlasgSize;

/* FBL_CPU_CLOCK */
extern const uint32 Fbl_Gu32_CpuClock;
/* FBL_QUARTZ_CLOCK */
extern const uint32 Fbl_Gu32_QuartzClock;
/* TIMER_PRESCALER_FACTOR */
extern const uint32 Fbl_Gu32_TimerPrescaler;

/* FBL_FLASH_ALIGNMENT */
extern const uint32 Fbl_Gu32_FlashAlignment;
/* FBL_FLASH_ERASE_UNIT */
extern const uint32 Fbl_Gu32_FlashEraseUnit;
/* FBL_STARTUP_COMMAND_ADDRESS */
extern const uint32 Fbl_Gu32_StartupCommandAddress;
/* FBL_COMMON_RAM_ADDRESS */
extern const uint32 Fbl_Gu32_CommonRamAddress;

/* FBL_DIAG_MAX_NUM_RESPONSE_PENDING */
extern const uint8 Fbl_Gu8_DiagMaxNumResponsePending;
/* FBL_SUPPORT_DIAGNOSTIC_STANDARD */
extern const uint8 Fbl_Gu8_SupportDiagnosticStandard;
/* FBL_DIAG_SIGNATURE_TX_MODE */
extern const uint8 Fbl_Gu8_DiagSignatureTxMode;

/* FBL_INT_WDG_TIMEOUT_MS */
extern const uint32 Fbl_Gu32_IntWdgTimeoutMS;

/* FBL_RANDOM_ALGORITHM */
extern const uint32 Fbl_Gu32_RandomAlgorithm;
/* FBL_SECURITY_ACCESS_LEVEL */
extern const uint32 Fbl_Gu32_SecurityAccessLevel;
/* FBL_SECURE_ACCESS_VERSION */
extern const uint32 Fbl_Gu32_SecureAccessVersion;
/* FBL_SECURE_ACCESS_HASH_ALGORITHM */
extern const uint32 Fbl_Gu32_SecureAccessHashAlgorithm;
/* FBL_SECURE_FLASH_VERSION */
extern const uint32 Fbl_Gu32_SecureFlashVersion;
/* FBL_SECURE_FLASH_HASH_ALGORITHM */
extern const uint32 Fbl_Gu32_SecureFlashHashAlgorithm;
/* FBL_SECURE_FLASH_2_0_HSM */
extern const uint32 Fbl_Gu32_SecureFlash2Hsm;
/* FBL_CRC16_BLOCK_SIZE */
extern const uint32 Fbl_Gu32_Crc16BlockSize;

/* FBL_CAN_RECEIVED_DATA_BUFFER_SIZE */
/* FBL_ETH_RECEIVED_DATA_BUFFER_SIZE */
extern const uint16 Fbl_Gu16_MaxReceivedDataFufferSize;
/* FBL_PROGRAM_DATA_BUFFER_SIZE */
extern const uint32 Fbl_Gu32_ProgramDataFufferSize;

/* FBL_DIAG_MAX_NUMOFBLOCK_LENGTH */
extern const uint16 Fbl_Gu16_DiagMaxNumOfBlockLength;

/* FBL_ETH_DIAG_PROTOCOL_VERSION */
extern const uint8 Fbl_Gu8_EthDiagProtocolVersion;
extern const uint8 Fbl_Gu8_EthDiagInvProtocolVersion;

/* FBL_ECU_IP_ADDRESS */
extern const uint32 Fbl_Gu32_EcuIPAddress;
/* FBL_ECU_MAC_ADDRESS */
extern const uint8 Fbl_Gau8_MACAddress[FBL_MAC_ADDR_SIZE];
/* FBL_ECU_TCP_PORT */
extern const uint16 Fbl_Gu16_EcuTcpPort;
/* FBL_ECU_PHYSICAL_LOCAL_ADDRESS_FOR_REQUEST */
extern const uint16 Fbl_Gu16_EcuPhysicalLocalAddressForRequest;
/* FBL_ECU_PHYSICAL_LOCAL_ADDRESS_FOR_RESPONSE */
extern const uint16 Fbl_Gu16_EcuPhysicalLocalAddressForResponse;
/* FBL_ECU_FUNCTIONAL_LOCAL_ADDRESS */
extern const uint16 Fbl_Gu16_EcuFunctionalLocalAddress;
/* FBL_TESTER_PHYSICAL_LOCAL_ADDRESS */
extern const uint16 Fbl_Gu16_TesterPhysicalLocalAddress;
/* FBL_REMOTE_PHYSICAL_LOCAL_ADDRESS */
extern const uint16 Fbl_Gu16_RemotePhysicalLocalAddress;

/* FBL_CAN_BAUD_RATE */
extern const uint32 Fbl_Gu32_CanBaudRate;
/* FBL_CAN_PROP_SEG */
extern const uint32 Fbl_Gu32_CanPropSeg;
/* FBL_CAN_SEG1 */
extern const uint32 Fbl_Gu32_CanSeg1;
/* FBL_CAN_SEG2 */
extern const uint32 Fbl_Gu32_CanSeg2;
/* FBL_CAN_SYNC_JUMP_WITH */
extern const uint32 Fbl_Gu32_CanSyncJumpWith;
/* FBL_CAN_PRESCALER */
extern const uint32 Fbl_Gu32_CanPrescaler;

/* FBL_CAN_FD_BAUD_RATE */
extern const uint32 Fbl_Gu32_CanFdBaudRate;
/* FBL_CAN_FD_PROP_SEG */
extern const uint32 Fbl_Gu32_CanFdPropSeg;
/* FBL_CAN_FD_SEG1 */
extern const uint32 Fbl_Gu32_CanFdSeg1;
/* FBL_CAN_FD_SEG2 */
extern const uint32 Fbl_Gu32_CanFdSeg2;
/* FBL_CAN_FD_SYNC_JUMP_WITH */
extern const uint32 Fbl_Gu32_CanFdSyncJumpWith;
/* FBL_CAN_FD_TRCV_DELAY_COMP_OFFSET */
extern const uint32 Fbl_Gu32_CanFdTrcvDelayCompOffset;
/* FBL_CAN_FD_PRESCALER */
extern const uint32 Fbl_Gu32_CanFdPrescaler;

/* FBL_CAN_TYPE */
extern const uint8 Fbl_Gu8_CanType;
/* FBL_CAN_CELL */
extern const uint8 Fbl_Gu8_CanCell;
/* FBL_CAN_NODE */
extern const uint8 Fbl_Gu8_CanNode;
/* FBL_CAN_RXD */
extern const uint8 Fbl_Gu8_CanRXD;
/* FBL_CAN_CLOCK_DIVIDER */
extern const uint8 Fbl_Gu8_CanClkDivider;
/* FBL_CAN_CLKSRC_CFG */
extern const uint8 Fbl_Gu8_CanClkSrcCfg;

/* MCAN_RX_PAD */
extern const uint8 Fbl_Gu8_McanRxPad;
/* MCAN_RX_INPUT_SSS */
extern const uint8 Fbl_Gu8_McanRxInputSss;
/* MCAN_TX_PAD */
extern const uint8 Fbl_Gu8_McanTxPad;
/* MCAN_TX_PAD_SSS */
extern const uint8 Fbl_Gu8_McanTxSss;

/* FBL_CAN_DIAG_MSG_PHY_REQ_ID */
extern const uint16 Fbl_Gu16_CanDiagMsgPhyRxID;
/* FBL_CAN_DIAG_MSG_PHY_RES_ID */
extern const uint16 Fbl_Gu16_CanDiagMsgPhyTxID;
/* FBL_CAN_DIAG_MSG_FUNC_REQ_ID */
extern const uint16 Fbl_Gu16_CanDiagMsgFuncTxID;

/* FBL_CAN_RX_PORT_PIN_IOCR_ADDRESS */
extern const uint32 Fbl_Gu32_CanRxPortPinIOCRAddr;
/* FBL_CAN_RX_PORT_PIN_INIT_VALUE */
extern const uint32 Fbl_Gu32_CanRxPortPinInitVal;
/* FBL_CAN_RX_PORT_PIN_MASK */
extern const uint32 Fbl_Gu32_CanRxPortPinMask;
/* FBL_CAN_TX_PORT_PIN_IOCR_ADDRESS */
extern const uint32 Fbl_Gu32_CanTxPortPinIOCRAddr;
/* FBL_CAN_TX_PORT_PIN_INIT_VALUE */
extern const uint32 Fbl_Gu32_CanTxPortPinInitVal;
/* FBL_CAN_TX_PORT_PIN_MASK */
extern const uint32 Fbl_Gu32_CanTxPortPinMask;
/* FBL_CAN_CELL_ADDRESS */
extern const uint32 Fbl_Gu32_CanCellAddr;
/* FBL_CAN_NODE_ADDRESS */
extern const uint32 Fbl_Gu32_CanNodeAddr;

/* FBL_NUM_OF_MEM_BLOCKS */
extern const uint8 Fbl_Gu8_NumOfMemBlocks;

/* DCM_ROUTINE_ERASE_MEMORY */
extern const uint16 Fbl_Gu16_EraseRID;
/* DCM_ROUTINE_SECUREFLASHING_CHECK */
extern const uint16 Fbl_Gu16_ChkProgDepRID;
/* DCM_ROUTINE_OTA_READY */
extern const uint16 Fbl_Gu16_OTAReadyRID;

/* FBL_SECURITY_NUM_ATT_DELAY */
extern const uint8 Fbl_Gu8_SecAccessMaxAttDelay;
/* FBL_SECURITY_DELAY_TIME */
extern const uint32 Fbl_Gu32_SecDelayTimer;

/* FBL_DIAG_MAX_NUM_SIGN_AREA */
extern Fbl_SignArea Fbl_SigningArea[FBL_DIAG_MAX_NUM_SIGN_AREA];
extern uint32 Fbl_SigningAreaIndex;

/* MAIN_SW_START_ADDR */
extern uint32 Fbl_Gu32_MainSwStartAddr;
/* MAIN_SW_END_ADDR */
extern uint32 Fbl_Gu32_MainSwEndAddr;

extern uint32 Fbl_Gu32_MainSignAddr;

extern uint32 Fbl_Gu32_BlkHeaderAddr;

extern uint32 Fbl_Gu32_BlkTrailerAddr;

extern uint16 Fbl_Gu16_SwUnitMemBlock;

extern uint16 Fbl_Gu16_SwUnitBlockId;

extern boolean Fbl_Gbl_MemBlkFlag;

extern boolean Fbl_Gbl_CheckCompressed;

extern const boolean Fbl_Gbl_CanFdTxBitrateSwitch;

extern const boolean Fbl_Gbl_MemorySwapEnable;

extern const boolean Fbl_Gbl_DecompressEnable;

extern const boolean Fbl_Gbl_OTAEnable;

extern const boolean Fbl_Gbl_DiagResponseBeforeResetEnable;

extern const boolean Fbl_Gbl_DiagResponseBeforeSessionEnable;

extern const boolean Fbl_Gbl_UseSecureFlash;

extern const boolean Fbl_Gbl_Revised_SF2_0;

extern const boolean Fbl_Gbl_WriteSignature;

extern const boolean Fbl_Gbl_WriteSignatureDelimiter;

extern const Fbl_SwModuleInfo Fbl_Gdt_SwModuleInfoFbl;

extern const uint8 Fbl_Gu8_NumOfPortPinCtrl;

/* Stores the generated seedkey algorithm seed value */
extern uint8 Sec_Gau8_SeedKeySeed[SEC_SEEDKEY_SEED_LEN];

/* Stores the calculated seedkey algorithm key value */
extern uint8 Sec_Gau8_SeedKeyKey[SEC_SEEDKEY_KEY_LEN];

/* Stores the generated HSAC algorithm seed value */
extern uint8 Sec_Gau8_HSACSeed[SEC_HSAC_SEED_LEN];

/* Stores the calculated HSAC algorithm key value */
extern uint8 Sec_Gau8_HSACKey[SEC_HSAC_KEY_LEN];

/* Stores the generated CSAC algorithm seed value */
extern uint8 Sec_Gau8_CSACSeed[SEC_CSAC_SEED_LEN];

/* Stores the key received for verifying signature */
extern uint8 Sec_Gau8_CSACKey[SEC_RSA_PUBLIC_KEY_MODULUS_LENGTH \
  + SEC_RSA_PUBLIC_KEY_EXPONENT_LENGTH];
  
/* Page wise erase status information */
/* Moved in this file to reduce the configuration for the bootloader */
extern uint8 MCfg_Gau8_ErsStsTab[FBL_NUM_OF_MEM_BLOCKS];

extern boolean Fbl_Gbl_IntWdgEnable;

extern uint32 Fbl_Gu32_FlsFlashBusyMask;

extern const uint32 Fbl_Gu32_ECO_WDTRIM;

extern const uint32 Fbl_Gu32_ECO_ATRIM;

extern const uint32 Fbl_Gu32_ECO_FTRIM;

extern const uint32 Fbl_Gu32_ECO_RTRIM;

extern const uint32 Fbl_Gu32_ECO_GTRIM;

extern const uint32 Fbl_Gu32_ECO_AGC_EN;

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"


#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* FBL_CONFIG_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
