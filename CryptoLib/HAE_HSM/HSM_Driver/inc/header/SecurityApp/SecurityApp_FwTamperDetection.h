/*!
  @file SecurityApp_FwTamperDetection.h
  @brief Security API header file for FTD(Firmware Tamper Detection)
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef SECURITYAPP_FW_TAMPER_DETECTION_H_
#define SECURITYAPP_FW_TAMPER_DETECTION_H_

#include "Hsm_Types.h"
#include "Hsm_AppInfo.h"

/*!
  @brief FTD operation status check API
  @param[out] state         FTD operation status
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
Std_ReturnType HSM_FwTamperDetectionStatus(HSM_FTD_STATE_t *state);

/*!
  @brief FTD log status check API
  @param[out] ftdLog        FTD log status
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
Std_ReturnType HSM_FwTamperDetectionLog(HSM_FTD_LOG_t *ftdLog);

/*!
  @brief FTD Temp Stop API
  @details Execute this function to stop FTD temporarily when reprogramming the area of FTD
  @param[in] password       Password(8byte)
  @param[in] pwByteLen      Password length
  @param[out] errState      Password verification result
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
Std_ReturnType HSM_FwTamperDetectionTempStop(const UINT8 *password, UINT32 pwByteLen, HSM_PASSWORD_VERIFY_STATE_t *errState);

/*!
  @brief FTD resume API
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
Std_ReturnType HSM_FwTamperDetectionRestart(void);

/*!
  @brief FTD configuration
  @details Used when changing the number of targets and multiple target information after FTD is activated through Factory API. \n
        Only works when FTD is enabled. \n
        Similar to FTD Factory API, but cannot be used instead because of its different usage. \n
        This API is a function created based on use after calling HSM_FactoryHsmConfigurationLock. \n
        When creating an FTD table, signature check is performed on all FTD targets.
  @param[in] ftdConfig      FTD area setting
  @param[in] cbFunc         Callback function used for FTD function
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
Std_ReturnType HSM_FwTamperDetectionConfig(const HSM_FTD_CONFIG_t *ftdConfig, HSM_CallbackFunc cbFunc);

/*!
  @brief FTD update target
  @details Used to create a new MAC when reprogramming an area with a preset target. \n
        It works only when FTD is enabled. \n
        It can take a very long time, depending on the FTD setup area, because it generates new MACs and verifies signatures. \n
        When using aSIMS public key for signature verification, #1 of signKeyNum Index in ftdConfig is used. \n
        To use the FST public key when verifying the signature, save the public key using the KeyManagement API and set the corresponding index to signKeyNum in the target.
  @param[in] ftdTarget      FTD target setting
  @param[in] cbFunc         Callback function used for FTD function
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
Std_ReturnType HSM_FwTamperDetectionUpdtTarget(const HSM_FTD_TARGET_t *ftdTarget, HSM_CallbackFunc cbFunc);

/*!
  @brief FTD function enable and setting function
  @details Similar to the HSM_FwTamperDetectionConfig function, but only for process line functions. \n
        Input values ftdConfig->target->signKeyNum and signAddr information are not used in this API. \n
        Use HW acceleration for table generation and MAC generation to reduce process time(general function SW). \n
        Do not validate firmware signatures to reduce process time (requires correct firmware injection). \n
        Can be used in development stage or process line. \n
        Return E_NOT_OK when used after calling HSM_FactoryHsmConfigurationLock.
  @param[in] ftdConfig      FTD area setting
  @param[in] cbFunc         Callback function used for FTD function
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
Std_ReturnType HSM_FactoryFwTamperDetectionEnable(const HSM_FTD_CONFIG_t *ftdConfig, HSM_CallbackFunc cbFunc);

/*!
  @brief FTD function disable
  @details Can be used in development stage or process line. \n
        Return E_NOT_OK when used after calling HSM_FactoryHsmConfigurationLock.
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
Std_ReturnType HSM_FactoryFwTamperDetectionDisable(void);

#endif /* SECURITYAPP_FW_TAMPER_DETECTION_H_ */
