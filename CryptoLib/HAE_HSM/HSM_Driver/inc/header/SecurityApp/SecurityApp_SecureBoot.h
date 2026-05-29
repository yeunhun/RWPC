/*!
  @file SecurityApp_SecureBoot.h
  @brief Security API header file for Secure Boot
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef SECURITYAPP_SECURE_BOOT_H_
#define SECURITYAPP_SECURE_BOOT_H_

#include "Hsm_Types.h"
#include "Hsm_AppInfo.h"

typedef struct
{
    UINT32 bootStartAddr;           /*!< Bootloader Start Address */
    UINT32 bootSize;                /*!< Bootloader Size */
    UINT16 cmacKeyNum;              /*!< Number of symmetric keys that generate the internal MAC (Use among Tier PSK #101~#105) */
    UINT16 signKeyNum;              /*!< Public key number for signature verification (When using aSIMS, enter 1 / When using FST, enter the usage number) */
    UINT32 signStartAddr;           /*!< Signature start address */
} HSM_SB_CONFIG_t;

/*!
  @brief Secure Boot Results and Status Returns
  @param[out] state         Secure Boot status
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
Std_ReturnType HSM_SecureBootResult(HSM_SECUREBOOT_STATE_t *state);

/*!
  @brief Secure Boot Mac Update
  @details Available with Secure Boot enabled through HSM_FactorySecureBootEnable API. \n
        Used only when the boot loader area set in Secure Boot Enable is changed during reprogramming. \n
        Use to update the bootloader's MAC when reprogramming the bootloader. \n
        Bootloader firmware signature authentication required. \n
        When using aSIMS public key for signature verification, #1 of sbKeyNum Index in sbConfig is used. \n
        To use the FST public key when verifying the signature, save the public key using the KeyManagement API and set the index to sbKeyNum in sbConfig.
  @param[out] sbConfig          Secure Boot area configuration
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
Std_ReturnType HSM_SecureBootMacUpdate(const HSM_SB_CONFIG_t *sbConfig);

/*!
  @brief Function to activate Secure Boot and set the area before HSM LOCK
  @details Available for process line or development. \n
        Among the fields of the input parameter sbConfig, the signature information signStartAddr and signKeyNum are not used in this API. \n
        Secure Boot is activated by restarting the controller after using the API. (No Mac Update required) \n
        Return E_NOT_OK when used after calling HSM_FactoryHsmConfigurationLock.
  @param[out] sbConfig          Secure Boot area configuration
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
Std_ReturnType HSM_FactorySecureBootEnable(const HSM_SB_CONFIG_t *sbConfig);

/*!
  @brief Secure Boot disable setting function before HSM LOCK
  @details Available for process line or development. \n
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
Std_ReturnType HSM_FactorySecureBootDisable(void);

///Dual Bank
typedef struct
{
    UINT32 bootStartAddrBankA;
    UINT32 bootSizeBankA;
    UINT32 bootStartAddrBankB;
    UINT32 bootSizeBankB;
    UINT16 cmacKeyNum;
} HSM_SB_DUAL_CONFIG_t;

typedef struct
{
    UINT32 bootStartAddrBankA;
    UINT32 bootSizeBankA;
    UINT32 bootStartAddrBankB;
    UINT32 bootSizeBankB;
    UINT16 cmacKeyNum;
    UINT16 signKeyNum;
    UINT32 signStartAddr;
} HSM_SB_MAC_DUALBANK_CONFIG_t;

Std_ReturnType HSM_FactorySecureBootEnableDualBank(const HSM_SB_DUAL_CONFIG_t *sbConfig);
Std_ReturnType HSM_SecureBootMacUpdateDualBank(const HSM_SB_MAC_DUALBANK_CONFIG_t *sbConfig);

#if (defined TARGET_F1KM)
/*!
  @brief HOST Core(CPUP) Reset Vector Change API
  @details After setting Configuration Lock, CPUP restricts the use of 'Configuration Setting command' of Renesas Flash Mcal(FACI command). \n
        This API can change the Reset Vector through HSM even after Configuration Lock is set . \n
        The input parameter 'resetVectorAddr' can be set only within the range of the bootloader setted when Secure Boot if Secure Boot is enabled. \n
  @param[in] resetVectorAddr   CPUP reset vector address
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
Std_ReturnType HSM_SetHostResetVector(UINT32 resetVectorAddr);
#endif

#endif /* SECURITYAPP_SECURE_BOOT_H_ */
