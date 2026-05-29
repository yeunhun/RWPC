/*!
  @file SecurityApp_ProactiveDataProtection.h
  @brief Security API header file for PDP(Proactive Data Protection)
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef SECURITYAPP_PROACTIVE_DATA_PROTECTION_H_
#define SECURITYAPP_PROACTIVE_DATA_PROTECTION_H_

#include "Hsm_Types.h"
#include "Hsm_AppInfo.h"

/******************************************************************************/
/*                  Proactive Data Protectioin(PDP) - Define                   */
/******************************************************************************/
#define HSM_MAX_PDP_SEG_NUM   4

typedef struct
{
    UINT32 startAddr;                               /*!< HOST Data Flash area start address to check for forgery and alteration */
    UINT32 size;                                    /*!< HOST Data Flash area size to check for forgery and alteration */
} HSM_PDP_SEGMENT_t;

typedef struct
{
    UINT16 cmacKeyNum;                              /*!< Symmetric key number to use for integrity verification */
    UINT16 segmentNum;                              /*!< Number of segments to check for forgery and alteration */
    HSM_PDP_SEGMENT_t segInfo[HSM_MAX_PDP_SEG_NUM]; /*!< Address and size for each segment */
} HSM_PDP_CONFIG_t;

/******************************************************************************/
/*                  Proactive Data Protectioin(PDP) - API                     */
/******************************************************************************/
/*!
  @brief PDP Configuration setting
  @details Return E_NOT_OK if the number of Segment is 0 or startAddr, size is invalid
  @param[in] pdpConfig      Integrity verification symmetric key number, number of segments, PDP area setting value
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
Std_ReturnType HSM_PDPConfig(HSM_PDP_CONFIG_t* pdpConfig);

/*!
  @brief Update CMAC value of the configured PDP area
  @details Return HSM_E_WRONG_SEQ on call after disable
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
Std_ReturnType HSM_PDPDataUpdate(void);

/*!
  @brief Check for forgery and alteration of the configured PDP area
  @details Return HSM_E_WRONG_SEQ on call after disable
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
Std_ReturnType HSM_PDPDataVerify(void);

/*!
  @brief Initialize PDP Configuration
  @details Keep the Update Count information
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
Std_ReturnType HSM_PDPDisable(void);

#endif /* SECURITYAPP_PROACTIVE_DATA_PROTECTION_H_ */
