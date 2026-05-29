/*!
  @file SecurityApp_KeyManagement.h
  @brief Security API header file for Key Management
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef SECURITYAPP_KEY_MANAGEMENT_H_
#define SECURITYAPP_KEY_MANAGEMENT_H_

#include "Hsm_Types.h"
#include "Hsm_AppInfo.h"

/******************************************************************************/
/*                       Key Manangement - Define                              */
/******************************************************************************/
#include "Hsm_KeyTypes.h"

/******************************************************************************/
/*                        Key Manangement - API                               */
/******************************************************************************/
/*!
  @brief Save AES Key in UDK DFlash area
  @details If KeyLock is set to 1, it cannot be modified later and HSM_E_WRONG_SEQ is returned. \n
        The Byte Order of AES Key to be stored must be Big Endian.
  @param[in] keyIndex       KeyIndex(201 ~ 210) to store in UDK / HOST Temp Key 301
  @param[in] key            Address value of key to store
  @param[in] keyLock        Key lock setting (Lock:1 / Unlock: 0)
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
Std_ReturnType HSM_KeyManagementSetAesKey(const UINT16 keyIndex, const UINT8* key, UINT16 keyLock);

/*!
  @brief Save RSA Key in UDK DFlash area
  @details If KeyLock is set to 1, it cannot be modified later and HSM_E_WRONG_SEQ is returned. \n
        Byte Order uses Big-Endian. In case of Little-Endian MCU, HSM Framework is converted internally.
  @param[in] keyIndex       KeyIndex(201 ~ 210) to store in UDK / HOST Temp Key 301
  @param[in] key            Address value of key to store
  @param[in] keyLock        Key lock setting (Lock:1 / Unlock: 0)
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
Std_ReturnType HSM_KeyManagementSetRsaKey(const UINT16 keyIndex, const Rsa_Keypair_t* key, UINT16 keyLock);

/*!
  @brief Save ECC Key in UDK DFlash area
  @details If KeyLock is set to 1, it cannot be modified later and HSM_E_WRONG_SEQ is returned. \n
        Byte Order uses Big-Endian. In case of Little-Endian MCU, HSM Framework is converted internally.
  @param[in] keyIndex       KeyIndex(201 ~ 210) to store in UDK / HOST Temp Key 301
  @param[in] key            Address value of key to store
  @param[in] keyLock        Key lock setting (Lock:1 / Unlock: 0)
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
Std_ReturnType HSM_KeyManagementSetEccKey(const UINT16 keyIndex, const Ecc_Keypair_t* key, UINT16 keyLock);

/*!
  @brief Check the validity of the key according to the KeyType and KeyIndex
  @details It is recommended to check the validity of the key through this API before using the key stored in the UDK area.
  @param[in] keyType        Key Type for Validation (AES_KEY, ECC_KEY, RSA_KEY)
  @param[in] keyIndex       Key index for Validation (AES: 201~210 / 301, RSA: 201~202 / 301, ECC: 201~202 / Temp: 301)
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
Std_ReturnType HSM_KeyManagementValidateKey(KEY_TYPE keyType, const UINT16 keyIndex);

#endif /* SECURITYAPP_KEY_MANAGEMENT_H_ */
