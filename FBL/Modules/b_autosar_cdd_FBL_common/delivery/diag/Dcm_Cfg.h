/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dcm_Cfg.h                                                     **
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
** 1.21.0    27-Oct-2021   JYS          Redmine #29277 #29449                 **
** 1.19.0    30-Jul-2021   JYS          Redmine #29874                        **
** 1.15.1.0  17-May-2021   SK Park      Redmine #29359                        **
** 1.0.3     05-Nov-2020   JYS          Redmine #26443                        **
** 1.0.2     26-Oct-2020   JYS          Redmine #26261                        **
** 1.0.1     13-Oct-2020   JYS          Redmine #25778                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef DCM_CFG_H
#define DCM_CFG_H
/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Fbl_Cfg.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
/* Instance id */
#define DCM_INSTANCE_ID                                               ((uint8)0)

#define DCM_TRANSFERDATA_CUSTOMISATION                                   STD_OFF

#define DCM_DIAGSESSIONCONTROL_SERVICE                                    STD_ON
#define DCM_ECURESET_SERVICE                                              STD_ON
#define DCM_SECURITYACCESS_SERVICE                                        STD_ON
#define DCM_READDATABYID_SERVICE                                          STD_ON
#define DCM_ROUTINECONTROL_SERVICE                                        STD_ON
#define DCM_TESTERPRESENT_SERVICE                                         STD_ON
#define DCM_REQUESTDOWNLOAD_SERVICE                                       STD_ON
#define DCM_TRANSFERDATA_SERVICE                                          STD_ON
#define DCM_REQTRANSFEREXIT_SERVICE                                       STD_ON
#define DCM_LINKCONTROL_SERVICE                                          STD_OFF
#define DCM_COMMUNICATIONCONTROL_SERVICE                                  STD_ON
#define DCM_CONTROLDTCSETTING_SERVICE                                     STD_ON
#define DCM_ACCESSTIMINGPARAMETERS_SERVICE                               STD_OFF
#define DCM_WRITEDATABYID_SERVICE                                        STD_OFF
#define DCM_UPLOAD_SERVICE                                               STD_OFF
#define DCM_READ_MEMORY                                                  STD_OFF
#define DCM_WRITE_MEMORY                                                 STD_OFF

#define DCM_MAX_RESPONSE_LENGTH                                            4096U

#define DCM_TOTAL_NUM_OF_RXPDUID                                              2U
  
#if (FBL_COMM_CAN_ENABLE == STD_ON)
#define DCM_MAX_RX_BUFFER_SIZE          (FBL_CAN_RECEIVED_DATA_BUFFER_SIZE + 2U)
#elif (FBL_COMM_ENET_ENABLE == STD_ON)
#define DCM_MAX_RX_BUFFER_SIZE          (FBL_ETH_RECEIVED_DATA_BUFFER_SIZE + 2U)
#endif
#define DCM_MAX_TX_BUFFER_SIZE                                              255U
#define DCM_TPRX_BUFFER_SIZE                                                  2U
#define DCM_RESP_BUFFER_SIZE                                                  3U

#if (DCM_WRITEDATABYID_SERVICE == STD_ON)
#define DCM_WRITE_DID_COUNT                                                   0U
#endif

#define DCM_MAX_DID_COUNT                                                     1U
#define DCM_MAX_RID_COUNT                                                     3U
#define DCM_MAX_SERVICE_COUNT                                                11U

#if (FBL_OTA_ENABLE == STD_ON)
#if (FBL_MEMORY_SWAP_ENABLE == STD_ON)
#define DCM_ERASEMEMORY_REQ_LENGTH                                         0x06U
#else /* (FBL_MEMORY_SWAP_ENABLE == STD_OFF) */
#define DCM_ERASEMEMORY_REQ_LENGTH                                         0x07U
#endif
#define DCM_SECUREFLASHING_CHECK_REQ_LENGTH                                0x06U
#define DCM_OTA_READY_REQ_LENGTH                                           0x03U
#else /* (FBL_OTA_ENABLE == STD_OFF) */
#define DCM_ERASEMEMORY_REQ_LENGTH                                         0x04U
#define DCM_SECUREFLASHING_CHECK_REQ_LENGTH                                0x04U
#define DCM_OTA_READY_REQ_LENGTH                                           0x03U
#endif

#define DCM_SECUREFLASHING_METADATA_LENGTH                                   61U
#define DCM_REVISED_SECUREFLASHING_METADATA_LENGTH                           72U

/* Security Levels */
#define DCM_SUPPORTED_SEC_LEVEL_COUNT                                         3U

#define DCM_SECURITY_LEVEL_11                                              0x11U
#define DCM_SECURITY_LEVEL_11_MASK                                         0x01U
#define DCM_SECURITY_LEVEL_11_L9                                           0x09U
#define DCM_SECURITY_LEVEL_11_SEED                                         0x11U
#define DCM_SECURITY_LEVEL_11_KEY                                          0x12U

#define DCM_SECURITY_LEVEL_41                                              0x41U
#define DCM_SECURITY_LEVEL_41_MASK                                         0x02U
#define DCM_SECURITY_LEVEL_41_L21                                          0x21U
#define DCM_SECURITY_LEVEL_41_SEED                                         0x41U
#define DCM_SECURITY_LEVEL_41_KEY                                          0x42U

#define DCM_SECURITY_LEVEL_01                                              0x01U
#define DCM_SECURITY_LEVEL_01_MASK                                         0x04U
#define DCM_SECURITY_LEVEL_01_L1                                           0x01U
#define DCM_SECURITY_LEVEL_01_SEED                                         0x01U
#define DCM_SECURITY_LEVEL_01_KEY                                          0x02U

/* Max Session Configuration */
#if (FBL_SUPPORT_DIAGNOSTIC_STANDARD == FBL_ES95486_00)
#define DCM_MAX_SESSION_COUNT                                                 5U
#else
#define DCM_MAX_SESSION_COUNT                                                 3U
#endif

/* Max Reset type Configuration */
#define DCM_MAX_RESET_TYPE_COUNT                                              1U

#define DCM_PDUID_COUNT                                                       2U

/* DCM task is configured to 200us */
#define DCM_TASK_TIME                                                     (200U)
/* Session Timing Configuration */
/* S3 server timeout is configured to 5 Seconds */
#define DCM_TIMERS3SERVERTIME                   (5000U * (1000U /DCM_TASK_TIME))
/* P2 server time is configured to 10ms */
#define DCM_DSL_TIMERP2SERVERADJUST               (10U * (1000U /DCM_TASK_TIME))
/* P2* server time is configured to 2Seconds */
#define DCM_DSL_TIMERP2STARTSERVERADJUST        (2000U * (1000U /DCM_TASK_TIME))

/* Request Download Configuration */
#define DCM_RD_ADDRESS_LENGTH_FORMAT_ID                                    0x44U

/* Queue buffer */
#define DCM_MAX_RX_QUEUE_ALLOWED                                           0x10U
/* Communication type */
#define DCM_DSP_COMM_NOR_MSG_TYPE                                    (uint8)0x01
#define DCM_DSP_COMM_NET_MSG_TYPE                                    (uint8)0x02
#define DCM_DSP_COMM_NET_NOR_MSG_TYPE                                (uint8)0x03

#endif /* DCM_CFG_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
