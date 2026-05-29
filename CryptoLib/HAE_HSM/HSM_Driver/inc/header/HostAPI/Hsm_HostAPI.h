/*!
  @file Hsm_HostAPI.h
  @brief HSM API header file for HOST
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef HSM_HOSTAPI_H_
#define HSM_HOSTAPI_H_

#include "Hsm_Types.h"
#include "Hsm_AppInfo.h"

/* For Common APIs */
/*!
  @brief Initialize HSM Driver
  @return E_OK: This is returned when a function execution is successful. \n
        E_NOT_OK: This is returned when a function execution fails. \n
        HSM_E_BUSY: HSM internal task is busy. \n
        HSM_E_WAIT: HSM is still working with HOST's request. \n
        HSM_E_WRONG_SEQ: API call sequence is incorrect. \n
        HSM_E_NOT_SUPPORTED: Not supported feature in HSM Framework. \n
        HSM_E_LENGTH_NOT_VALID: Invalid parameter length. \n
        HSM_E_VALUE_NOT_VALID: Invalid parameter value. \n
        HSM_E_KEY_NOT_VALID: Invalid key index parameter.
*/
Std_ReturnType HSM_DriverInitialize(void);

/*!
  @brief Set the Interrupt Handling Core and Priority according to the conf and priority entered as parameters.\n
        Enable HSM Interrupt Service.
  @param[in] conf           The HOST core number that handling ISR
  @param[in] priority       The priority of ISR
  @return E_OK: This is returned when a function execution is successful. \n
        E_NOT_OK: This is returned when a function execution fails. \n
        HSM_E_VALUE_NOT_VALID: Invalid parameter value.
*/
Std_ReturnType HSM_EnableService(UINT32 conf, UINT32 priority);

/*!
  @brief Set the Interrupt Handling Core and Priority according to the conf and priority entered as parameters
  @param[in] conf           The HOST core number that handling ISR
  @param[in] priority       The priority of ISR
  @return E_OK: This is returned when a function execution is successful. \n
        E_NOT_OK: This is returned when a function execution fails. \n
        HSM_E_VALUE_NOT_VALID: Invalid parameter value.
*/
Std_ReturnType HSM_SetInterruptConfig(UINT32 coreNum, UINT32 priority);

/*!
  @brief Enable HSM Interrupt Service
*/
void HSM_EnableInterruptService(void);

/*!
  @brief Disable HSM Interrupt Service
*/
void HSM_DisableInterruptService(void);

/*!
  @brief This API is HSM interrupt handler. Register this interrupt handler on the interrupt vector table when porting HSM driver
*/
void HSM_IrqHandler(void);

/*!
  @brief If the API returns 'E_NOT_OK', check the error code
  @return Error code value entered last
*/
UINT32 HSM_GetLastErrorCode(void);

/*!
  @brief Set the interval time to execute call-back function 
  @param[in] ms         The interval Time, millisecond unit
*/
void HSM_SetCallbackFuncWaitCount(UINT32 ms);

/*!
  @brief Set the time-out time to wait response
  @param[in] ms         The time-out time, millisecond unit
*/
void HSM_SetApiWaitRespTime(UINT32 ms);

/* For Crypto APIs */
/*!
  @brief After API calling of ASYNC MODE, This API must call to check current status of internal task of HSM
  @param[in] jobId          JOB ID to check
  @return E_OK: This is returned when a function execution is successful. \n
        E_NOT_OK: This is returned when a function execution fails. \n
        HSM_E_BUSY: HSM internal task is busy. \n
        HSM_E_WAIT: HSM is still working with HOST's request. \n
        HSM_E_WRONG_SEQ: API call sequence is incorrect. \n
        HSM_E_NOT_SUPPORTED: Not supported feature in HSM Framework. \n
        HSM_E_LENGTH_NOT_VALID: Invalid parameter length. \n
        HSM_E_VALUE_NOT_VALID: Invalid parameter value. \n
        HSM_E_KEY_NOT_VALID: Invalid key index parameter. \n
        HSM_E_UNINIT: HSM_DriverInitialize is not performed
*/
Std_ReturnType HSM_WaitResp(UINT16 jobId);

/* For Crypto APIs */
/*!
  @brief After API calling of NON-BLOCKING MODE, This API must call to check current status of internal task of HSM
  @details This API is used for API NON-BLOCKING mode. \n
          The requested API is identified by the jobId in HSMAPI_OBJ_t of API parameter. \n
          If HSM_ApiHandler result is 'E_WAIT', it means that the HSM is executing the API corresponding to requested jobId. \n
          If HSM_ApiHandler result is 'E_OK', it means that the API is finished and API result was returned from HSM. \n 
          The API result value is stored in the output pointer memory in HSMAPI_OBJ_t set when executing the API.
  @param[inout] HSMAPI_OBJ_t obj  job Id and Output Pointer included
  @return E_OK: This is returned when a function execution is successful. \n
        E_NOT_OK: This is returned when a function execution fails. \n
        HSM_E_BUSY: HSM internal task is busy. \n
        HSM_E_WAIT: HSM is still working with HOST's request. \n
        HSM_E_WRONG_SEQ: API call sequence is incorrect. \n
        HSM_E_NOT_SUPPORTED: Not supported feature in HSM Framework. \n
        HSM_E_LENGTH_NOT_VALID: Invalid parameter length. \n
        HSM_E_VALUE_NOT_VALID: Invalid parameter value. \n
        HSM_E_KEY_NOT_VALID: Invalid key index parameter. \n
        HSM_E_UNINIT: HSM_DriverInitialize is not performed
*/
Std_ReturnType HSM_ApiHandler(HSMAPI_OBJ_t *obj);

/*!
  @brief The HSM reads data from the Rx buffer by the requested length
  @param[in] jobId          JOB ID to read RX buffer
  @param[in] count          Specifies how many bytes of the data to be read bytes
  @param[in] data           Pointer of RX buffer to be written
  @return E_OK: This is returned when a function execution is successful. \n
        E_NOT_OK: This is returned when a function execution fails. \n
        HSM_E_BUSY: HSM internal task is busy. \n
        HSM_E_WAIT: HSM is still working with HOST's request. \n
        HSM_E_WRONG_SEQ: API call sequence is incorrect. \n
        HSM_E_NOT_SUPPORTED: Not supported feature in HSM Framework. \n
        HSM_E_LENGTH_NOT_VALID: Invalid parameter length. \n
        HSM_E_VALUE_NOT_VALID: Invalid parameter value. \n
        HSM_E_KEY_NOT_VALID: Invalid key index parameter. \n
        HSM_E_UNINIT: HSM_DriverInitialize is not performed
*/
Std_ReturnType HSM_ReadRxBuff(UINT16 jobId, UINT32 count, UINT8 *data);

/*!
  @brief This API returns the maximum data length in byte unit that can be transmitted from HOST to HSM at once
  @return Maximum transmission data bytes
*/
UINT32 HSM_GetMaxTranSizeByte(void);

/*!
  @brief Cancel Job
  @details If 'E_NOT_OK' returned after calling Update API, it means crypto API service failure. \n
        The user should call this function to clear HSM internal job context.
  @param[in] jobId          JOB ID to be cancelled
  @return E_OK: This is returned when a function execution is successful. \n
        E_NOT_OK: This is returned when a function execution fails. \n
        HSM_E_BUSY: HSM internal task is busy. \n
        HSM_E_WAIT: HSM is still working with HOST's request. \n
        HSM_E_WRONG_SEQ: API call sequence is incorrect. \n
        HSM_E_NOT_SUPPORTED: Not supported feature in HSM Framework. \n
        HSM_E_LENGTH_NOT_VALID: Invalid parameter length. \n
        HSM_E_VALUE_NOT_VALID: Invalid parameter value. \n
        HSM_E_KEY_NOT_VALID: Invalid key index parameter. \n
        HSM_E_UNINIT: HSM_DriverInitialize is not performed
*/
Std_ReturnType HSM_CancelJob(UINT16 jobId);

/* For Appclication APIs */
/*!
  @brief Read Unique ID of MCU from HSM
  @param[out] uid       Pointer of 16-byte array variable to be stored MCU Unique ID
  @return E_OK: This is returned when a function execution is successful. \n
        E_NOT_OK: This is returned when a function execution fails. \n
        HSM_E_BUSY: HSM internal task is busy. \n
        HSM_E_WAIT: HSM is still working with HOST's request. \n
        HSM_E_WRONG_SEQ: API call sequence is incorrect. \n
        HSM_E_NOT_SUPPORTED: Not supported feature in HSM Framework. \n
        HSM_E_LENGTH_NOT_VALID: Invalid parameter length. \n
        HSM_E_VALUE_NOT_VALID: Invalid parameter value. \n
        HSM_E_KEY_NOT_VALID: Invalid key index parameter. \n
        HSM_E_UNINIT: HSM_DriverInitialize is not performed
*/
Std_ReturnType HSM_GetMcuUid(UINT8 *uid);

/*!
  @brief Read the version information of HSM
  @param[out] version       HSM Version information
  @return E_OK: This is returned when a function execution is successful. \n
        E_NOT_OK: This is returned when a function execution fails. \n
        HSM_E_BUSY: HSM internal task is busy. \n
        HSM_E_WAIT: HSM is still working with HOST's request. \n
        HSM_E_WRONG_SEQ: API call sequence is incorrect. \n
        HSM_E_NOT_SUPPORTED: Not supported feature in HSM Framework. \n
        HSM_E_LENGTH_NOT_VALID: Invalid parameter length. \n
        HSM_E_VALUE_NOT_VALID: Invalid parameter value. \n
        HSM_E_KEY_NOT_VALID: Invalid key index parameter. \n
        HSM_E_UNINIT: HSM_DriverInitialize is not performed
*/
Std_ReturnType HSM_GetVersionInfo(HSM_VERSION_CTX_t *version);

/*!
  @brief Read the Security Application satus of HSM
  @param[out] info      HSM Security information
  @return E_OK: This is returned when a function execution is successful. \n
        E_NOT_OK: This is returned when a function execution fails. \n
        HSM_E_BUSY: HSM internal task is busy. \n
        HSM_E_WAIT: HSM is still working with HOST's request. \n
        HSM_E_WRONG_SEQ: API call sequence is incorrect. \n
        HSM_E_NOT_SUPPORTED: Not supported feature in HSM Framework. \n
        HSM_E_LENGTH_NOT_VALID: Invalid parameter length. \n
        HSM_E_VALUE_NOT_VALID: Invalid parameter value. \n
        HSM_E_KEY_NOT_VALID: Invalid key index parameter. \n
        HSM_E_UNINIT: HSM_DriverInitialize is not performed
*/
Std_ReturnType HSM_GetAllSecurityInfo(HSM_SECURITY_INFO_t *info);

/*!
  @brief Read Pause status of HSM Framework 
  @details This API's return is only valid after HSM_DriverInitialize executed.
  @return True: HSM Framework is pause State. \n
          False: HSM Framework is run State.
*/
BOOL HSM_CheckHsmTempStopState(void);

/*!
  @brief HSM Framework Pause API
  @details Restricts the use of all HSM APIs except for the HSM_Restart API. \n
        HSM Core does not actually stop when executing this API. \n
        This is a function to prevent collision due to simultaneous access \n
        when the host and HSM are physically sharing code flash by switching the HSM to wait in Ramcode. \n
        Since HSM Core is restarted after MCU power reset, the setting is valid only until reset. \n
        This API must be executed before executing Code Flash operation such as Write/Erase/Ecc Check of Code Flash in Host Core. \n
        If not, HSM Core may stop and HSM API may not be available until MCU power reset. \n
        In the case of FTD enabled MCU, before executing this API, you must perform the FTD Temp Stop API to stop the FTD function \n
        and then execute this API.
  @return E_OK: This is returned when a function execution is successful. \n
        E_NOT_OK: This is returned when a function execution fails. \n
        HSM_E_BUSY: HSM internal task is busy. \n
        HSM_E_WAIT: HSM is still working with HOST's request. \n
        HSM_E_WRONG_SEQ: API call sequence is incorrect. \n
        HSM_E_NOT_SUPPORTED: Not supported feature in HSM Framework. \n
        HSM_E_LENGTH_NOT_VALID: Invalid parameter length. \n
        HSM_E_VALUE_NOT_VALID: Invalid parameter value. \n
        HSM_E_KEY_NOT_VALID: Invalid key index parameter. \n
        HSM_E_UNINIT: HSM_DriverInitialize is not performed
*/
Std_ReturnType HSM_TempStop(void);

/*!
  @brief Suspended HSM Framework Restart API
  @details To use HSM API after executing HSM_TempStop API, this API must be executed. \n
        Since HSM Core is restarted after MCU power reset, the API does not need to be executed at boot time.
  @return E_OK: This is returned when a function execution is successful. \n
        E_NOT_OK: This is returned when a function execution fails. \n
        HSM_E_BUSY: HSM internal task is busy. \n
        HSM_E_WAIT: HSM is still working with HOST's request. \n
        HSM_E_WRONG_SEQ: API call sequence is incorrect. \n
        HSM_E_NOT_SUPPORTED: Not supported feature in HSM Framework. \n
        HSM_E_LENGTH_NOT_VALID: Invalid parameter length. \n
        HSM_E_VALUE_NOT_VALID: Invalid parameter value. \n
        HSM_E_KEY_NOT_VALID: Invalid key index parameter. \n
        HSM_E_UNINIT: HSM_DriverInitialize is not performed
*/
Std_ReturnType HSM_Restart(void);

/*!
  @brief APIs that lock configuration of factory-related APIs to HSM
  @details These functions can be limited to a target, so refer to the target guide's manual for details.
  @return E_OK: This is returned when a function execution is successful. \n
        E_NOT_OK: This is returned when a function execution fails. \n
        HSM_E_BUSY: HSM internal task is busy. \n
        HSM_E_WAIT: HSM is still working with HOST's request. \n
        HSM_E_WRONG_SEQ: API call sequence is incorrect. \n
        HSM_E_NOT_SUPPORTED: Not supported feature in HSM Framework. \n
        HSM_E_LENGTH_NOT_VALID: Invalid parameter length. \n
        HSM_E_VALUE_NOT_VALID: Invalid parameter value. \n
        HSM_E_KEY_NOT_VALID: Invalid key index parameter. \n
        HSM_E_UNINIT: HSM_DriverInitialize is not performed
*/
Std_ReturnType HSM_FactoryHsmConfigurationLock(void);

/*!
  @brief Get the current state of lock configuration
  @param[out] state         The state of lock configuration
  @return E_OK: This is returned when a function execution is successful. \n
        E_NOT_OK: This is returned when a function execution fails. \n
        HSM_E_BUSY: HSM internal task is busy. \n
        HSM_E_WAIT: HSM is still working with HOST's request. \n
        HSM_E_WRONG_SEQ: API call sequence is incorrect. \n
        HSM_E_NOT_SUPPORTED: Not supported feature in HSM Framework. \n
        HSM_E_LENGTH_NOT_VALID: Invalid parameter length. \n
        HSM_E_VALUE_NOT_VALID: Invalid parameter value. \n
        HSM_E_KEY_NOT_VALID: Invalid key index parameter. \n
        HSM_E_UNINIT: HSM_DriverInitialize is not performed
*/
Std_ReturnType HSM_GetConfigurationLockState(HSM_CONFIG_LOCK_STATE_t *state);

Std_ReturnType HSM_SetHsmHandlerIrqN(UINT8 irqN);
Std_ReturnType HSM_Sleep(void);
Std_ReturnType HSM_Wakeup(void);
Std_ReturnType HSM_SetWakeupTrigger(const UINT16 *list, UINT16 idxNum);
Std_ReturnType HSM_ClearWakeupTrigger(void);
BOOL HSM_IsSleepStatus(void);

Std_ReturnType HSM_ChallengeRequest(UINT8 *ChallengeValue);
Std_ReturnType HSM_ResponseForward(UINT8 *ResponseValue);

Std_ReturnType HSM_RegSetConfigRegulator(UINT32 *sromApiResult, UINT32 regArg1, UINT32 regArg2);
Std_ReturnType HSM_RegSetSwitchOverRegulator(UINT32 *sromApiResult, UINT32 regArg1);
Std_ReturnType HSM_RegSetLoadRegulatorTrim(UINT32 *sromApiResult, UINT32 regArg1);

/* Only Used in Targets which don't have HSM DFlash */
Std_ReturnType HSM_StartUsingDFlash(void);
Std_ReturnType HSM_FinishUsingDFlash(void);

#if (defined TARGET_F1KM)
/*!
  @brief HOST Core(CPUP) Opbion Byte 0,1 Change API
  @details After setting Configuration Lock, CPUP restricts the use of 'Configuration Setting command' of Renesas Flash Mcal(FACI command).
        This API can change the 'Opbion Byte' through HSM even after Configuration Lock is set.
  @param[in] opbt0   OptionByte0
  @param[in] opbt1   OptionByte1
  @return E_OK: This is returned when a function execution is successful. \n
        E_NOT_OK: This is returned when a function execution fails. \n
        HSM_E_BUSY: HSM internal task is busy. \n
        HSM_E_WAIT: HSM is still working with HOST's request. \n
        HSM_E_WRONG_SEQ: API call sequence is incorrect. \n
        HSM_E_NOT_SUPPORTED: Not supported feature in HSM Framework. \n
        HSM_E_LENGTH_NOT_VALID: Invalid parameter length. \n
        HSM_E_VALUE_NOT_VALID: Invalid parameter value. \n
        HSM_E_KEY_NOT_VALID: Invalid key index parameter. \n
        HSM_E_UNINIT: HSM_DriverInitialize is not performed
*/
Std_ReturnType HSM_SetHostOptionByte(UINT32 opbt0, UINT32 opbt1);
Std_ReturnType HSM_SetIdAuthentication(const UINT32 *idAuth);
#endif

#endif /* HSM_HOSTAPI */


