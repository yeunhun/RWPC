/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: NvM_Config.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NVM                                                   **
**                                                                            **
**  PURPOSE   : Provides Variable for upper layers                            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.5.1     30-Dec-2020   Yun YJ      Redmine #27374                      **
** 1.3.5     20-Sep-2017   Yun  YJ     Redmine #9669                          **
** 1.3.4     07-Dec-2016   Song CY     Redmine #6889                          **
** 1.3.2     10-Oct-2016   Song CY     Redmine #6215                          **
** 1.2.3     24-Mar-2016   Song CY     Redmine #4276                          **
** 1.1.8     02-Oct-2015   Song CY     For Runtime Err, add library variable  **
** 1.1.0     18-Apr-2014   Song CY     RedMine718 Version is updated          **
** 1.0.8     30-Sep-2013   Song CY         Dem Header is changed.             **
** 1.0.1     04-Jun-2013   CY Song         XAR~603 : NvM library              **
**                                          Add global variable               **
**                                          NvM_GusTotalNumOfBlock            **
** 1.0.0     25-Jan-2013   CY Song     Initial version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "NvM_PCTypes.h"
#include "NvM_Cfg.h"
#include "NvM_Config.h"
#if(NVM_DEMERROR_REPORT == STD_ON)
#include "NvM_Dem_Cfg.h"                            /* Dem header file */
#endif
/* polyspace-begin VARIABLE:ALL [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification" */
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

const uint8  NvM_GucRepeatMirrorOperations   = NVM_REPEAT_MIRROR_OPERATIONS;
const uint8  NvM_GucSizeImmediateJobQueue    = NVM_SIZE_IMMEDIATE_JOB_QUEUE;
const uint8  NvM_GucSizeStadardJobQueue      = NVM_SIZE_STANDARD_JOB_QUEUE;
const uint8  NvM_GucCrcSidSize               = NVM_CRC_SID_SIZE;

#if(NVM_DEMERROR_REPORT == STD_ON)
const uint16 NvM_GusIntegrityFailed          = NVM_E_INTEGRITY_FAILED;
const uint16 NvM_GusLossOfRedundancy         = NVM_E_LOSS_OF_REDUNDANCY;
const uint16 NvM_GusQueueOverflow            = NVM_E_QUEUE_OVERFLOW;
const uint16 NvM_GusReqFailed                = NVM_E_REQ_FAILED;
const uint16 NvM_GusVerifyFailed             = NVM_E_VERIFY_FAILED;
const uint16 NvM_GusWriteProtected           = NVM_E_WRITE_PROTECTED;
const uint16 NvM_GusWrongBlockId             = NVM_E_WRONG_BLOCK_ID;
#endif

const uint16 NvM_GusTotalNumOfWriteAllBlocks = NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS;
const uint16 NvM_GusBlockNotConFigWriteAll   = NVM_BLOCKS_NOT_CONFIG_WRITEALL;
const uint16 NvM_GusTotalNumOfBlock          = NVM_TOTAL_NUM_OF_NVRAM_BLOCKS;
const uint16 NvM_GusMirrorBufferSize         = NVM_MIRROR_BUFFER;

/* It is possible for the following consts to be used for library.
   So it is declared even though it is not used now. */
const uint8  NvM_GucDataSetSlectionBits      = NVM_DATASET_SELECTION_BITS;
const uint16 NvM_GusCRCNumOfBytes            = NVM_CRC_NUM_OF_BYTES;
const uint16 NvM_GusDataSetIndex             = NVM_DATASET_INDEX;

#if(NVM_WRITE_VERIFICATION == STD_ON)
const uint16 NvM_GusMaxWriteVerBlkLength     = NVM_MAX_WRITE_VER_BLK_LENGTH;
#endif /* (NVM_WRITE_VERIFICATION == STD_ON) */

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification" */
/* polyspace-end VARIABLE:ALL [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
