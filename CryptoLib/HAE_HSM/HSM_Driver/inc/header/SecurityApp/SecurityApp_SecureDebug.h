/*!
  @file SecurityApp_SecureDebug.h
  @brief Security API header file for Secure Debug
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef SECURITYAPP_SECURE_DEBUG_H_
#define SECURITYAPP_SECURE_DEBUG_H_

#include "Hsm_Types.h"
#include "Hsm_AppInfo.h"

/*!
  @brief Debugger Protection Enable
  @details Set JTAG Password based on the password entered with pw. \n
        Return E_NOT_OK when used after calling HSM_FactoryHsmConfigurationLock. \n
        These functions can be limited to a target, so refer to the target guide's manual for details.
  @param[in] password       Passwords to be used to activate JTAG (32 Bytes required)
  @param[in] pwByteLen      Number of bytes in the passwords to enter (32 Bytes)
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
Std_ReturnType HSM_FactoryDebuggerProtectionEnable(const UINT8 *password, UINT32 pwByteLen);

/*!
  @brief Debugger Protection Disable
  @details Restore JTAG Protection configuration. \n
        Return E_NOT_OK when used after calling HSM_FactoryHsmConfigurationLock. \n
        These functions can be limited to a target, so refer to the target guide's manual for details.
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
Std_ReturnType HSM_FactoryDebuggerProtectionDisable(void);

/*!
  @brief Debugger Protection Temp Stop
  @details Secure Debug is temporarily canceled based on the password entered with pw. \n
        Basically, the temporary release of Debug Protection is performed by entering the password entered \n
        in the "HSM_FactoryDebuggerProtectionEnable" function from an external tool (such as Trace32). \n
        These functions can be limited to a target, so refer to the target guide's manual for details.
  @param[in] password       Passwords to be used to activate JTAG (32 Bytes required)
  @param[in] pwByteLen      Number of bytes in the passwords to enter (32 Bytes)
  @param[out] debugState    Debug status information
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
Std_ReturnType HSM_DebuggerProtectionTempStop(const UINT8 *password, UINT32 pwByteLen, HSM_SECUREDEBUG_STATE_t *debugState);


#endif /* SECURITYAPP_SECURE_DEBUG_H_ */
