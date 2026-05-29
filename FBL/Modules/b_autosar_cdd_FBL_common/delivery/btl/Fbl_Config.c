/*******************************************************************************
**                                                                            **
**  (C) 2019~2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fbl_Config.c                                                  **
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
** 1.21.0    27-Sep-2021   JYS          Redmine #29449, #31609                **
** 1.20.0.0  03-Sep-2021   Sungwook     Redmine #29451                        **
** 1.19.0    30-Jul-2021   JYS          Redmine #29874                        **
** 1.17.0.0  16-Jul-2021   Sungwook     Redmine #29464                        **
** 1.15.0    12-May-2021   JYS          Redmine #28950                        **
** 1.12.0.0  12-Mar-2021   JHLim        Redmine #24088, #23964                **
** 1.11.0.0  17-Feb-2021   JYS          Redmine #28341                        **
** 1.10.0.0  07-Feb-2021   JYS          Redmine #28298 #27968                 **
** 1.0.13    22-Jan-2021   JYS          Redmine #27881 #27643                 **
** 1.0.12    06-Nov-2020   JYS          Redmine #26457                        **
** 1.0.11    05-Nov-2020   JYS          Redmine #26443                        **
** 1.0.10    19-Oct-2020   JYS          Redmine #26135                        **
** 1.0.9     13-Oct-2020   JYS          Redmine #25778                        **
** 1.0.8     12-Oct-2020   JYS          Redmine #26029                        **
** 1.0.7     25-Aug-2020   JYS          Redmine #25301                        **
** 1.0.6     11-Aug-2020   JYS          Redmine #23962                        **
** 1.0.5     29-Jul-2020   JYS          Redmine #24231                        **
** 1.0.4     10-Apr-2020   JaeHyun      Redmine #22713                        **
** 1.0.3     07-Feb-2020   Sinil        Redmine #21592, #21604                **
** 1.0.2     08-Jan-2020   Sinil        Redmine #21079                        **
** 1.0.1     06-Dec-2019   Sinil        Redmine #20402                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Fbl_Config.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
/* Define flags for the access rights */
#define FBL_ERASE_ENABLED_BIT                                            (0x01U)
#define FBL_WRITE_ENABLED_BIT                                            (0x02U)
#define FBL_READ_ENABLED_BIT                                             (0x04U)

/*******************************************************************************
**                              Check Validity                                **
*******************************************************************************/


#if ((FBL_SUPPORT_MCU == FBL_MCU_TC23X) || (FBL_SUPPORT_MCU == FBL_MCU_TC29X))

/* Check Cpu & Quartz clock */
#if (FBL_CPU_CLOCK != FBL_CPU_200MHZ)
#error "Not supported CPU clock"
#endif
#if ((FBL_QUARTZ_CLOCK != FBL_QUARTZ_20MHZ) && (FBL_QUARTZ_CLOCK != FBL_QUARTZ_40MHZ))
#error "Not supported Quartz clock"
#endif

#elif (FBL_SUPPORT_MCU == FBL_MCU_TC38X) || (FBL_SUPPORT_MCU == FBL_MCU_TC39X) || \
		(FBL_SUPPORT_MCU == FBL_MCU_TC36X) || (FBL_SUPPORT_MCU == FBL_MCU_TC37X) || \
		(FBL_SUPPORT_MCU == FBL_MCU_TC33X)

/* Check Cpu & Quartz clock */
#if (FBL_CPU_CLOCK != FBL_CPU_300MHZ)
#error "Not supported CPU clock"
#endif
#if ((FBL_QUARTZ_CLOCK != FBL_QUARTZ_20MHZ) && (FBL_QUARTZ_CLOCK != FBL_QUARTZ_40MHZ))
#error "Not supported Quartz clock"
#endif

#elif (FBL_SUPPORT_MCU == FBL_MCU_SPC58X)

/* Check Cpu & Quartz clock */
#if (FBL_CPU_CLOCK != FBL_CPU_80MHZ) && (FBL_CPU_CLOCK != FBL_CPU_160MHZ)
#error "Not supported CPU clock"
#endif

#elif (FBL_SUPPORT_MCU == FBL_MCU_RH850F1KM)

/* Check Cpu & Quartz clock */
#if (FBL_CPU_CLOCK != FBL_CPU_80MHZ)
#error "Not supported CPU clock"
#endif
#if ((FBL_QUARTZ_CLOCK != FBL_QUARTZ_8MHZ) && (FBL_QUARTZ_CLOCK != FBL_QUARTZ_16MHZ) && \
     (FBL_QUARTZ_CLOCK != FBL_QUARTZ_20MHZ) && (FBL_QUARTZ_CLOCK != FBL_QUARTZ_24MHZ))
#error "Not supported Quartz clock"
#endif

#elif (FBL_SUPPORT_MCU == FBL_MCU_CYTXXX)
#if ((FBL_MCU_NAME == CYT2B7XX) || (FBL_MCU_NAME == CYT2B9XX) || (FBL_MCU_NAME == CYT2BLXX))
/* Check Cpu & Quartz clock */
#if (FBL_CPU_CLOCK != FBL_CPU_160MHZ)
#error "Not supported CPU clock"
#endif
#if ((FBL_QUARTZ_CLOCK != FBL_QUARTZ_8MHZ) && (FBL_QUARTZ_CLOCK != FBL_QUARTZ_16MHZ) && \
     (FBL_QUARTZ_CLOCK != FBL_QUARTZ_20MHZ) && (FBL_QUARTZ_CLOCK != FBL_QUARTZ_24MHZ) && \
     (FBL_QUARTZ_CLOCK != FBL_QUARTZ_32MHZ))
#error "Not supported Quartz clock"
#endif
#endif

#else
#error "Not supported MCU"
#endif

#if ((FBL_SUPPORT_MCU != FBL_MCU_SPC58X) && (FBL_SUPPORT_MCU != FBL_MCU_RH850F1KM))
#if (FBL_SUPPORT_HSM == FBL_HSM_AUTHSM_1_0)
#error "Not supported HSM Version"
#endif
#endif


#if (FBL_MEMORY_SWAP_ENABLE == STD_ON)
#if (!defined(FBL_PARTITION_FLAG_ADDRESS)) || (!defined(FBL_PARTITION_FLAG_SIZE))
#error "If you use the memory swap function, you need to configure the partition flag"
#endif
#endif

#if ((FBL_USE_HAE_HSM == STD_ON) && (FBL_USE_AUT_HSM == STD_ON))
#error "You can not use Autoever HSM and Autron HSM at the same time"
#endif

#if (FBL_SUPPORT_MCU == FBL_MCU_CYTXXX)
#if (!defined(FBL_CLK_TRIM_ECO_WDTRIM)) || (!defined(FBL_CLK_TRIM_ECO_ATRIM)) || (!defined(FBL_CLK_TRIM_ECO_FTRIM)) || \
  (!defined(FBL_CLK_TRIM_ECO_RTRIM)) || (!defined(FBL_CLK_TRIM_ECO_GTRIM)) || (!defined(FBL_CLK_ECO_AGC_EN))
#error "You must enter the Extenral Crystal ECO Trim Information : WDTRIM, ATRIM, FTRIM, RTRIM, GTRIM, AGC_EN"
#endif
#endif
/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/
#define BTL_START_SEC_CONST
#include "Btl_MemMap.h"

/* FBL_SUPPORT_MCU */
const uint32 Fbl_Gu32_SupportMCU = FBL_SUPPORT_MCU;

/* FBL_SUPPORT_HSM */
const uint32 Fbl_Gu32_SupportHSM = FBL_SUPPORT_HSM;

/* FBL_SUPPORT_VERSION_CHECK */
#if (FBL_SOFTWARE_VERSION_CHECK == STD_ON)
const boolean Fbl_Gbl_SupportVersionCheck = TRUE;
#else
const boolean Fbl_Gbl_SupportVersionCheck = FALSE;
#endif

/* FBL_PARTITION_FLAG_ADDRESS, FBL_PARTITION_FLAG_SIZE */
#if (FBL_MEMORY_SWAP_ENABLE == STD_ON)
const uint32 Fbl_Gu32_PartitionFlasgSize = FBL_PARTITION_FLAG_SIZE;
#else
const uint32 Fbl_Gu32_PartitionFlasgSize = 4U;
#endif

/* FBL_CPU_CLOCK */
const uint32 Fbl_Gu32_CpuClock = FBL_CPU_CLOCK;
/* FBL_QUARTZ_CLOCK */
const uint32 Fbl_Gu32_QuartzClock = FBL_QUARTZ_CLOCK;
/* TIMER_PRESCALER_FACTOR */
const uint32 Fbl_Gu32_TimerPrescaler = TIMER_PRESCALER_FACTOR;

#if (FBL_SUPPORT_MCU == FBL_MCU_CYTXXX)
/* FBL External Crystal Configuration for TV-II */
const uint32 Fbl_Gu32_ECO_WDTRIM= FBL_CLK_TRIM_ECO_WDTRIM;
const uint32 Fbl_Gu32_ECO_ATRIM= FBL_CLK_TRIM_ECO_ATRIM;
const uint32 Fbl_Gu32_ECO_FTRIM= FBL_CLK_TRIM_ECO_FTRIM;
const uint32 Fbl_Gu32_ECO_RTRIM= FBL_CLK_TRIM_ECO_RTRIM;
const uint32 Fbl_Gu32_ECO_GTRIM= FBL_CLK_TRIM_ECO_GTRIM;
const uint32 Fbl_Gu32_ECO_AGC_EN= FBL_CLK_ECO_AGC_EN;
#else
/* FBL External Crystal Configuration for TV-II */
const uint32 Fbl_Gu32_ECO_WDTRIM = 0U;
const uint32 Fbl_Gu32_ECO_ATRIM  = 0U;
const uint32 Fbl_Gu32_ECO_FTRIM = 0U;
const uint32 Fbl_Gu32_ECO_RTRIM = 0U;
const uint32 Fbl_Gu32_ECO_GTRIM = 0U;
const uint32 Fbl_Gu32_ECO_AGC_EN = 0U;
#endif


/* FBL_FLASH_ALIGNMENT */
const uint32 Fbl_Gu32_FlashAlignment = FBL_FLASH_ALIGNMENT;
/* FBL_FLASH_ERASE_UNIT */
const uint32 Fbl_Gu32_FlashEraseUnit = FBL_FLASH_ERASE_UNIT;
/* FBL_STARTUP_COMMAND_ADDRESS */
const uint32 Fbl_Gu32_StartupCommandAddress = FBL_STARTUP_COMMAND_ADDRESS;
/* FBL_COMMON_RAM_ADDRESS */
const uint32 Fbl_Gu32_CommonRamAddress = FBL_COMMON_RAM_ADDRESS;

/* FBL_DIAG_MAX_NUM_RESPONSE_PENDING */
const uint8 Fbl_Gu8_DiagMaxNumResponsePending = FBL_DIAG_MAX_NUM_RESPONSE_PENDING;
/* FBL_SUPPORT_DIAGNOSTIC_STANDARD */
const uint8 Fbl_Gu8_SupportDiagnosticStandard = FBL_SUPPORT_DIAGNOSTIC_STANDARD;
/* FBL_DIAG_SIGNATURE_TX_MODE */
const uint8 Fbl_Gu8_DiagSignatureTxMode = FBL_DIAG_SIGNATURE_TX_MODE;

/* FBL_INT_WDG_TIMEOUT_MS */
const uint32 Fbl_Gu32_IntWdgTimeoutMS = FBL_INT_WDG_TIMEOUT_MS;

/* FBL_SECURITY_ACCESS_LEVEL */
const uint32 Fbl_Gu32_SecurityAccessLevel = FBL_SECURITY_ACCESS_LEVEL;

/* FBL_SECURE_ACCESS_HASH_ALGORITHM */
const uint32 Fbl_Gu32_SecureAccessHashAlgorithm = FBL_SECURE_ACCESS_HASH_ALGORITHM;
/* FBL_SECURE_FLASH_VERSION */
const uint32 Fbl_Gu32_SecureFlashVersion = FBL_SECURE_FLASH_VERSION;

/* FBL_SECURE_FLASH_HASH_ALGORITHM */
const uint32 Fbl_Gu32_SecureFlashHashAlgorithm = FBL_SECURE_FLASH_HASH_ALGORITHM;

/* FBL_CRC16_BLOCK_SIZE */
const uint32 Fbl_Gu32_Crc16BlockSize = FBL_CRC16_BLOCK_SIZE;

const uint16 Fbl_Gu16_MaxReceivedDataFufferSize = 
#if (FBL_COMM_CAN_ENABLE == STD_ON)
  /* FBL_CAN_RECEIVED_DATA_BUFFER_SIZE */
  FBL_CAN_RECEIVED_DATA_BUFFER_SIZE;
#elif (FBL_COMM_ENET_ENABLE == STD_ON)
  /* FBL_ETH_RECEIVED_DATA_BUFFER_SIZE */
  FBL_ETH_RECEIVED_DATA_BUFFER_SIZE;
#endif

const uint32 Fbl_Gu32_ProgramDataFufferSize = 
#if (FBL_COMM_CAN_ENABLE == STD_ON)
  /* FBL_CAN_PROGRAM_DATA_BUFFER_SIZE */
  FBL_CAN_PROGRAM_DATA_BUFFER_SIZE;
#elif (FBL_COMM_ENET_ENABLE == STD_ON)
  /* FBL_ETH_PROGRAM_DATA_BUFFER_SIZE */
  FBL_ETH_PROGRAM_DATA_BUFFER_SIZE;
#endif

/* FBL_DIAG_MAX_NUMOFBLOCK_LENGTH */
const uint16 Fbl_Gu16_DiagMaxNumOfBlockLength = FBL_DIAG_MAX_NUMOFBLOCK_LENGTH;

/* FBL_ETH_DIAG_PROTOCOL_VERSION */
const uint8 Fbl_Gu8_EthDiagProtocolVersion = FBL_ETH_DIAG_PROTOCOL_VERSION;
const uint8 Fbl_Gu8_EthDiagInvProtocolVersion = (uint8)(~FBL_ETH_DIAG_PROTOCOL_VERSION);

/* FBL_ECU_IP_ADDRESS */
const uint32 Fbl_Gu32_EcuIPAddress = FBL_ECU_IP_ADDRESS;
/* FBL_ECU_MAC_ADDRESS */
const uint8 Fbl_Gau8_MACAddress[FBL_MAC_ADDR_SIZE] = FBL_ECU_MAC_ADDRESS;
/* FBL_ECU_TCP_PORT */
const uint16 Fbl_Gu16_EcuTcpPort = FBL_ECU_TCP_PORT;
/* FBL_TESTER_PHYSICAL_LOCAL_ADDRESS */
const uint16 Fbl_Gu16_TesterPhysicalLocalAddress = FBL_TESTER_PHYSICAL_LOCAL_ADDRESS;
/* FBL_REMOTE_PHYSICAL_LOCAL_ADDRESS */
const uint16 Fbl_Gu16_RemotePhysicalLocalAddress = FBL_REMOTE_PHYSICAL_LOCAL_ADDRESS;

/* FBL_CAN_BAUD_RATE */
const uint32 Fbl_Gu32_CanBaudRate = FBL_CAN_BAUD_RATE;
/* FBL_CAN_PROP_SEG */
const uint32 Fbl_Gu32_CanPropSeg = FBL_CAN_PROP_SEG;
/* FBL_CAN_SEG1 */
const uint32 Fbl_Gu32_CanSeg1 = FBL_CAN_SEG1;
/* FBL_CAN_SEG2 */
const uint32 Fbl_Gu32_CanSeg2 = FBL_CAN_SEG2;
/* FBL_CAN_SYNC_JUMP_WITH */
const uint32 Fbl_Gu32_CanSyncJumpWith = FBL_CAN_SYNC_JUMP_WITH;
#if ((FBL_SUPPORT_MCU == FBL_MCU_TC23X) || (FBL_SUPPORT_MCU == FBL_MCU_TC29X) || (FBL_SUPPORT_MCU == FBL_MCU_SPC58X) || \
  (FBL_SUPPORT_MCU == FBL_MCU_RH850F1KM) ||(FBL_SUPPORT_MCU == FBL_MCU_TC23X) || (FBL_SUPPORT_MCU == FBL_MCU_CYTXXX))
/* FBL_CAN_PRESCALER */
const uint32 Fbl_Gu32_CanPrescaler = FBL_CAN_PRESCALER;
#endif

/* FBL_CAN_FD_BAUD_RATE */
const uint32 Fbl_Gu32_CanFdBaudRate = FBL_CAN_FD_BAUD_RATE;
/* FBL_CAN_FD_PROP_SEG */
const uint32 Fbl_Gu32_CanFdPropSeg = FBL_CAN_FD_PROP_SEG;
/* FBL_CAN_FD_SEG1 */
const uint32 Fbl_Gu32_CanFdSeg1 = FBL_CAN_FD_SEG1;
/* FBL_CAN_FD_SEG2 */
const uint32 Fbl_Gu32_CanFdSeg2 = FBL_CAN_FD_SEG2;
/* FBL_CAN_FD_SYNC_JUMP_WITH */
const uint32 Fbl_Gu32_CanFdSyncJumpWith = FBL_CAN_FD_SYNC_JUMP_WITH;
/* FBL_CAN_FD_TRCV_DELAY_COMP_OFFSET */
const uint32 Fbl_Gu32_CanFdTrcvDelayCompOffset = FBL_CAN_FD_TRCV_DELAY_COMP_OFFSET;
#if ((FBL_SUPPORT_MCU == FBL_MCU_TC23X) || (FBL_SUPPORT_MCU == FBL_MCU_TC29X) || (FBL_SUPPORT_MCU == FBL_MCU_SPC58X) || \
  (FBL_SUPPORT_MCU == FBL_MCU_RH850F1KM) ||(FBL_SUPPORT_MCU == FBL_MCU_TC23X) || (FBL_SUPPORT_MCU == FBL_MCU_CYTXXX))
/* FBL_CAN_FD_PRESCALER */
const uint32 Fbl_Gu32_CanFdPrescaler = FBL_CAN_FD_PRESCALER;
#endif

/* FBL_CAN_TYPE */
const uint8 Fbl_Gu8_CanType = FBL_CAN_TYPE;
#if ((FBL_SUPPORT_MCU == FBL_MCU_SPC58X) || (FBL_SUPPORT_MCU == FBL_MCU_RH850F1KM))
/* FBL_CAN_CLOCK_DIVIDER */
const uint8 Fbl_Gu8_CanClkDivider = FBL_CAN_CLOCK_DIVIDER;
/* FBL_CAN_CLKSRC_CFG */
const uint8 Fbl_Gu8_CanClkSrcCfg = FBL_CAN_CLKSRC_CFG;
#endif

/* FBL_CAN_RX_PORT_PIN_IOCR_ADDRESS */
const uint32 Fbl_Gu32_CanRxPortPinIOCRAddr = FBL_CAN_RX_PORT_PIN_IOCR_ADDRESS;
/* FBL_CAN_RX_PORT_PIN_INIT_VALUE */
const uint32 Fbl_Gu32_CanRxPortPinInitVal = FBL_CAN_RX_PORT_PIN_INIT_VALUE;
/* FBL_CAN_RX_PORT_PIN_MASK */
const uint32 Fbl_Gu32_CanRxPortPinMask = FBL_CAN_RX_PORT_PIN_MASK;
/* FBL_CAN_TX_PORT_PIN_IOCR_ADDRESS */
const uint32 Fbl_Gu32_CanTxPortPinIOCRAddr = FBL_CAN_TX_PORT_PIN_IOCR_ADDRESS;
/* FBL_CAN_TX_PORT_PIN_INIT_VALUE */
const uint32 Fbl_Gu32_CanTxPortPinInitVal = FBL_CAN_TX_PORT_PIN_INIT_VALUE;
/* FBL_CAN_TX_PORT_PIN_MASK */
const uint32 Fbl_Gu32_CanTxPortPinMask = FBL_CAN_TX_PORT_PIN_MASK;
/* FBL_CAN_CELL_ADDRESS */
const uint32 Fbl_Gu32_CanCellAddr = FBL_CAN_CELL_ADDRESS;
/* FBL_CAN_NODE_ADDRESS */
const uint32 Fbl_Gu32_CanNodeAddr = FBL_CAN_NODE_ADDRESS;
/* FBL_CAN_DIAG_MSG_PHY_RES_ID */
const uint16 Fbl_Gu16_CanDiagMsgPhyTxID = FBL_CAN_DIAG_MSG_PHY_RES_ID;
/* FBL_CAN_DIAG_MSG_PHY_REQ_ID */
const uint16 Fbl_Gu16_CanDiagMsgPhyRxID = FBL_CAN_DIAG_MSG_PHY_REQ_ID;
/* FBL_CAN_DIAG_MSG_FUNC_REQ_ID */
const uint16 Fbl_Gu16_CanDiagMsgFuncTxID = FBL_CAN_DIAG_MSG_FUNC_REQ_ID;

/* FBL_NUM_OF_MEM_BLOCKS */
const uint8 Fbl_Gu8_NumOfMemBlocks = FBL_NUM_OF_MEM_BLOCKS;

/* FBL_PORTPIN_CTRL_NUM */
const uint8 Fbl_Gu8_NumOfPortPinCtrl = FBL_PORTPIN_CTRL_NUM;
#if (FBL_CAN_FD_TX_BITRATE_SWITCH == STD_ON)
const boolean Fbl_Gbl_CanFdTxBitrateSwitch = TRUE;
#else
const boolean Fbl_Gbl_CanFdTxBitrateSwitch = FALSE;
#endif

#if (FBL_MEMORY_SWAP_ENABLE == STD_ON)
const boolean Fbl_Gbl_MemorySwapEnable = TRUE;
#else
const boolean Fbl_Gbl_MemorySwapEnable = FALSE;
#endif

#if (FBL_DECOMPRESS_ENABLE == STD_ON)
const boolean Fbl_Gbl_DecompressEnable = TRUE;
#else
const boolean Fbl_Gbl_DecompressEnable = FALSE;
#endif

#if (FBL_OTA_ENABLE == STD_ON)
const boolean Fbl_Gbl_OTAEnable = TRUE;
#else
const boolean Fbl_Gbl_OTAEnable = FALSE;
#endif

#if (FBL_DIAG_RESPONSE_BEFORE_RESET_ENABLE == STD_ON)
const boolean Fbl_Gbl_DiagResponseBeforeResetEnable = TRUE;
#else
const boolean Fbl_Gbl_DiagResponseBeforeResetEnable = FALSE;
#endif

#if (FBL_DIAG_RESPONSE_BEFORE_SESSION_CHANGE_ENABLE == STD_ON)
const boolean Fbl_Gbl_DiagResponseBeforeSessionEnable = TRUE;
#else
const boolean Fbl_Gbl_DiagResponseBeforeSessionEnable = FALSE;
#endif

#if (FBL_USE_SECURE_FLASH == STD_ON)
const boolean Fbl_Gbl_UseSecureFlash = TRUE;
#else
const boolean Fbl_Gbl_UseSecureFlash = FALSE;
#endif

#if (FBL_REVISED_SECURE_FLASH_2_0 == STD_ON)
const boolean Fbl_Gbl_Revised_SF2_0 = TRUE;
#else
const boolean Fbl_Gbl_Revised_SF2_0 = FALSE;
#endif

#if (FBL_WRITE_SIGNATURE == STD_ON)
const boolean Fbl_Gbl_WriteSignature = TRUE;
#else
const boolean Fbl_Gbl_WriteSignature = FALSE;
#endif

#if (FBL_WRITE_SIGNATURE_DELIMITER == STD_ON)
const boolean Fbl_Gbl_WriteSignatureDelimiter = TRUE;
#else
const boolean Fbl_Gbl_WriteSignatureDelimiter = FALSE;
#endif

/* DCM_ROUTINE_ERASE_MEMORY */
const uint16 Fbl_Gu16_EraseRID = DCM_ROUTINE_ERASE_MEMORY;
/* DCM_ROUTINE_SECUREFLASHING_CHECK */
const uint16 Fbl_Gu16_ChkProgDepRID = DCM_ROUTINE_SECUREFLASHING_CHECK;
/* DCM_ROUTINE_OTA_READY */
const uint16 Fbl_Gu16_OTAReadyRID = DCM_ROUTINE_OTA_READY;

/* FBL_SECURITY_NUM_ATT_DELAY */
const uint8 Fbl_Gu8_SecAccessMaxAttDelay = FBL_SECURITY_NUM_ATT_DELAY;
/* FBL_SECURITY_DELAY_TIME */
const uint32 Fbl_Gu32_SecDelayTimer = FBL_SECURITY_DELAY_TIME;

#define BTL_STOP_SEC_CONST
#include "Btl_MemMap.h"


#define BTL_START_SEC_VAR_NO_INIT
#include "Btl_MemMap.h"

/* MAIN_SW_START_ADDR */
uint32 Fbl_Gu32_MainSwStartAddr;
/* MAIN_SW_END_ADDR */
uint32 Fbl_Gu32_MainSwEndAddr;

uint32 Fbl_Gu32_MainSignAddr;

uint32 Fbl_Gu32_BlkHeaderAddr;

uint32 Fbl_Gu32_BlkTrailerAddr;

uint16 Fbl_Gu16_SwUnitMemBlock;

uint16 Fbl_Gu16_SwUnitBlockId;

boolean Fbl_Gbl_MemBlkFlag;

boolean Fbl_Gbl_CheckCompressed;

/* Stores the generated seedkey algorithm seed value */
uint8 Sec_Gau8_SeedKeySeed[SEC_SEEDKEY_SEED_LEN];

/* Stores the calculated seedkey algorithm key value */
uint8 Sec_Gau8_SeedKeyKey[SEC_SEEDKEY_KEY_LEN];

/* Stores the generated HSAC algorithm seed value */
uint8 Sec_Gau8_HSACSeed[SEC_HSAC_SEED_LEN];

/* Stores the calculated HSAC algorithm key value */
uint8 Sec_Gau8_HSACKey[SEC_HSAC_KEY_LEN];

/* Stores the generated CSAC algorithm seed value */
uint8 Sec_Gau8_CSACSeed[SEC_CSAC_SEED_LEN];

/* Stores the key received for verifying signature */
uint8 Sec_Gau8_CSACKey[SEC_RSA_PUBLIC_KEY_MODULUS_LENGTH \
  + SEC_RSA_PUBLIC_KEY_EXPONENT_LENGTH];

 /* Page wise erase status information */
/* Moved in this file to reduce the configuration for the bootloader */
uint8 MCfg_Gau8_ErsStsTab[FBL_NUM_OF_MEM_BLOCKS];

#define BTL_STOP_SEC_VAR_NO_INIT
#include "Btl_MemMap.h"


#define BTL_START_SEC_SVAR_NO_INIT
#include "Btl_MemMap.h"
 
#define BTL_STOP_SEC_SVAR_NO_INIT
#include "Btl_MemMap.h"


#define BTL_START_SEC_VAR_INIT
#include "Btl_MemMap.h"

/* FBL_DIAG_MAX_NUM_SIGN_AREA */
Fbl_SignArea Fbl_SigningArea[FBL_DIAG_MAX_NUM_SIGN_AREA] = {0,};
uint32 Fbl_SigningAreaIndex = 0;

/* FBL_PARTITION_FLAG_ADDRESS, FBL_PARTITION_FLAG_SIZE */
#if (FBL_MEMORY_SWAP_ENABLE == STD_OFF)
uint32 Fbl_Gu32_PartitionFlasgAddress = MAIN_SW_SECURITY_KEY_ADDR;
#else
uint32 Fbl_Gu32_PartitionFlasgAddress = FBL_PARTITION_FLAG_ADDRESS;
#endif

#if (FBL_INT_WDG_ENABLE == STD_ON)
boolean Fbl_Gbl_IntWdgEnable = TRUE;
#else
boolean Fbl_Gbl_IntWdgEnable = FALSE;
#endif


#if ((FBL_SUPPORT_MCU == FBL_MCU_TC23X) || (FBL_SUPPORT_MCU == FBL_MCU_TC29X))
uint32 Fbl_Gu32_FlsFlashBusyMask = 0x0000003DUL;
#elif (FBL_SUPPORT_MCU == FBL_MCU_TC38X)
uint32 Fbl_Gu32_FlsFlashBusyMask = 0x0000003DUL;
#elif (FBL_SUPPORT_MCU == FBL_MCU_TC39X)
uint32 Fbl_Gu32_FlsFlashBusyMask = 0x000000FDUL;
#elif (FBL_SUPPORT_MCU == FBL_MCU_TC33X)
uint32 Fbl_Gu32_FlsFlashBusyMask = 0x00000005UL;	/* TC33x has PF0 : [2:2] Program Flash PF0BUSY */
#elif (FBL_SUPPORT_MCU == FBL_MCU_TC36X)
uint32 Fbl_Gu32_FlsFlashBusyMask = 0x0000000DUL;	/* TC36x has PF0, PF1 : [2:2] Program Flash PF0BUSY, [3:3] Program Flash PF1BUSY */
#elif (FBL_SUPPORT_MCU == FBL_MCU_TC37X)
uint32 Fbl_Gu32_FlsFlashBusyMask = 0x0000000DUL;	/* TC37x has PF0, PF1 : [2:2] Program Flash PF0BUSY, [3:3] Program Flash PF1BUSY */
#elif (FBL_SUPPORT_MCU == FBL_MCU_CYTXXX)
uint32 Fbl_Gu32_FlsFlashBusyMask = 0x000000FDUL;
#endif

#define BTL_STOP_SEC_VAR_INIT
#include "Btl_MemMap.h"

/*******************************************************************************
**                        Global Function Definition                          **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"


#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
