/*******************************************************************************
**                                                                            **
**  (C) 2020-2021 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CDD_DataLog.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : DataLog CDD                                                   **
**                                                                            **
**  PURPOSE   : Header file for DataLog                                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.1.0     09-Jun-2021    MJ.Woo        Redmine #29944, #30055              **
** 1.0.0     17-Nov-2020    MJ.Woo        Redmine #25497                      **
*******************************************************************************/

#ifndef CDD_DATALOG_H
#define CDD_DATALOG_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "Dem_Cfg.h"
#include "Rte_Cfg.h"
#if ((RTE_AR_RELEASE_MAJOR_VERSION == 4)&&(RTE_AR_RELEASE_MINOR_VERSION >= 3))
#include "SchM_DataLog_Type.h"
#else
#include "Rte_DataLog_Type.h"
#endif
#include "HwResource.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/**
* @addtogroup DATALOG_ESDD_000
* @{ */
#define DATALOG_CUSTOM_DATA_BYTE_SIZE (DATALOG_DATA_BYTE_SIZE - 4)

#if (DATALOG_DATA_BYTE_SIZE < 4)
#error "DATALOG_DATA_BYTE_SIZE should be greater than or equal to 4"
#endif

/** Types for Log Data
 *
 * | 7         2 |      1     |       0       |
 * | ----------- | ---------- | ------------- |
 * | ResetReason | LpAllowNvM | LpAllowRamTst |
 * | 6bit        | 1bit       | 1bit          |
 *
 * |       7       |       6       |         5        | 4         0 |
 * | ------------- | ------------- | ---------------- | ----------- |
 * | LpAllowRomTst | LpAllowIoHwAb | WakeupEventMulti | WakeupEvent |
 * | 1bit          | 1bit          | 1bit             | 5bit        |
 *
 * | 7         0 |
 * | ----------- |
 * | ComModeErr0 |
 * | 8bit        |
 *
 * | 7         2 |   1   |    0    |
 * | ----------- | ----- | ------- |
 * | ComModeErr1 | RunOK | SleepOK |
 * | 6bit        | 1bit  | 1bit    |
 *
 * | 7         0 | 7         0  | 7         0 | 7         0 | 7         0 |...
 * | ----------- | -----------  | ----------- | ----------- | ----------- |---
 * | CustomData0 | CustomData1  | CustomData2 | CustomData3 | CustomData4 |...
 * | 8bit        | 8bit         | 8bit        | 8bit        | 8bit        |...
 */
/* polyspace-begin MISRA-C3:6.1 [Justified:Medium] "AUTRON_MISRA_6_1" */
typedef struct
{
  uint8 ResetReason      :6; /**< Reset Reason */
  uint8 LpAllowNvM       :1; /**< LowPowerAllow status of NvM */
  uint8 LpAllowRamTst    :1; /**< LowPowerAllow status of RamTst */
  uint8 LpAllowRomTst    :1; /**< LowPowerAllow status of RomTst */
  uint8 LpAllowIoHwAb    :1; /**< LowPowerAllow status of IoHwAb */
  uint8 WakeupEventMulti :1; /**< Multiple Wakeup Event occurred */
  uint8 WakeupEvent      :5; /**< Wakeup Event ID */

  uint8 ComModeErr0      :8; /**< Sleep requested when FULL_COMM for CH0 ~ 7 */
  uint8 ComModeErr1      :6; /**< Sleep requested when FULL_COMM for CH8 ~ 13 */
  uint8 RunOK            :1; /**< ECU RUN mode status */
  uint8 SleepOK          :1; /**< BswM SLEEP condition passed */

  #if (DATALOG_CUSTOM_DATA_BYTE_SIZE > 0)
  uint8  CustomData[DATALOG_CUSTOM_DATA_BYTE_SIZE]; /**< User custom data */
  #endif
} DataLog_DataType;
/* polyspace-end MISRA-C3:6.1 */

/** This type indicates DataLog is initialized or not */
typedef enum
{
  DATALOG_INIT_NONE,         /**< DataLog is not initialized */
  DATALOG_INIT_COMPLETED,    /**< DataLog is initialized */
} DataLog_InitStatusType;

/** This type indicates Sleep and Wakeup sequence */
typedef enum
{
  DATALOG_SEQ_INIT,          /**< From Power On Reset to before ECU RUN */
  DATALOG_SEQ_SLEEP_REQ,     /**< SLEEP was requested */
  DATALOG_SEQ_SLEEP_DELAYED, /**< SLEEP was requested but not performed */
  DATALOG_SEQ_H2L,           /**< SLEEP condition of BswM has been passed */
  DATALOG_SEQ_L2H,           /**< Wakeup and getting out of SLEEP */
  DATALOG_SEQ_RUN_DELAYED,   /**< Wakeup but state transition to RUN fail */
  DATALOG_SEQ_RUN,           /**< Normal ECU RUN state */
} DataLog_SleepSeqType;
/** @}  */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define DATALOG_START_SEC_VAR_NO_INIT_8
#include "MemMap.h"
extern DataLog_DataType DataLog_Data;
extern DataLog_DataType DataLog_SavedData;
#define DATALOG_STOP_SEC_VAR_NO_INIT_8
#include "MemMap.h"

#define DATALOG_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, DATALOG_CODE) DataLog_SetSleepConditionLog(void);
extern FUNC(void, DATALOG_CODE) DataLog_SetSleepOKLog(void);
extern FUNC(void, DATALOG_CODE) DataLog_SetWakeupEventLog(void);
#if (DATALOG_CUSTOM_DATA_BYTE_SIZE > 0)
extern FUNC(Std_ReturnType, DATALOG_CODE) DataLog_SetCustomData(
                                      uint8 customData, uint32 customDataIndex);
#endif
extern FUNC(DataLog_SleepSeqType, DATALOG_CODE) DataLog_GetSleepSequence(void);
extern FUNC(void, DATALOG_CODE) DataLog_SetSleepSequence(DataLog_SleepSeqType seq);
#define DATALOG_STOP_SEC_CODE
#include "MemMap.h"

#endif /* CDD_DATALOG_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

