/*!
  @file SecurityApp_FeatureOnDemand.h
  @brief Security API header file for FOD(Feature On Demand)
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef SECURITYAPP_FEATURE_ON_DEMAND_H_
#define SECURITYAPP_FEATURE_ON_DEMAND_H_

/******************************************************************************/
/*                    			Includes         		                      */
/******************************************************************************/
#include "Hsm_Types.h"
#include "Hsm_AppInfo.h"

/******************************************************************************/
/*                    			Feature On Demand Data Types                   */
/******************************************************************************/
#define FOD_NUMBER_OF_SET (10u)

#define FOD_VERSION_LEN 1
#define FOD_CERT_SN_LEN 4
#define FOD_CERT_TAG_LEN 1
#define FOD_CERT_VIN_LEN 17
#define FOD_CERT_EID_LEN 2
#define FOD_CERT_FV_LEN 4
#define FOD_CERT_SP_LEN 16
#define FOD_CERT_ISSUER_LEN 1
#define FOD_CERT_ORDERID_LEN 4
#define FOD_CERT_ISSUEDDATE_LEN 8
#define FOD_CERT_EFFECTIVEDATE_LEN 8
#define FOD_CERT_EXPIREDDATE_LEN 8
#define FOD_CERT_RESERVED_LEN 22

/*
* FoDCert Size = 96 Byte
*/
typedef struct {
    UINT8 version[FOD_VERSION_LEN];
	UINT8 serialNumber[FOD_CERT_SN_LEN];
	UINT8 tag[FOD_CERT_TAG_LEN];
	UINT8 vin[FOD_CERT_VIN_LEN];
	UINT8 eId[FOD_CERT_EID_LEN];
	UINT8 fv[FOD_CERT_FV_LEN];
	UINT8 sP[FOD_CERT_SP_LEN];
	UINT8 issuer[FOD_CERT_ISSUER_LEN];
	UINT8 orderId[FOD_CERT_ORDERID_LEN];
	UINT8 issuedDate[FOD_CERT_ISSUEDDATE_LEN];
	UINT8 effectiveDate[FOD_CERT_EFFECTIVEDATE_LEN];    /*!< RSA Modulus value to be saved in UDK area */
	UINT8 expiredDate[FOD_CERT_EXPIREDDATE_LEN];        /*!< RSA Exponent value to be saved in UDK area */
    UINT8 reserved[FOD_CERT_RESERVED_LEN];
} FoDCert;

/*! Error State value for FOD interface */
typedef enum
{ //HSM-Driver Sync Need
    HSM_FOD_INIT = 0,                                   /*!< FoD initialization in progress */
    HSM_FOD_READY,                                      /*!< FoD available */
    HSM_FOD_NOT_PERFORMED,                              /*!< Without FoD set */
    HSM_FOD_SUCCESS,                                    /*!< FoD API running normally */
    HSM_FOD_FAIL,                                       /*!< Fail to run FoD API */
    HSM_FOD_HEADER_ERR,                                 /*!< FoD Cert integrity verification failure */
    HSM_FOD_CMAC_GEN_FAIL,                              /*!< FoD Cert (Encrypted Information) integrity data generation failure */
    HSM_FOD_CMAC_FAIL,                                  /*!< FoD Cert (Encrypted Information) integrity verification failure */
    HSM_FOD_DECRYPT_FAIL,                               /*!< FoD Cert (encrypted information) decryption failure */
    HSM_FOD_XOR_SUM_FAIL,                               /*!< FoD Cert integrity verification failure */
    HSM_FOD_SIGN_FAIL,                                  /*!< FoD Cert signature verification failure */
    HSM_FOD_WR_INFO_FAIL,                               /*!< Fail to write to HSM storage when saving FoD Cert */
    HSM_FOD_LOAD_INFO_FAIL,                             /*!< Failed to load FoD Cert information */
    HSM_FOD_CERT_NOT_FOUND,                             /*!< When requesting FoD Cert deletion, the corresponding Cert does not exist */
    HSM_FOD_FULLED,                                     /*!< FoD Cert storage space exceeded */
	HSM_FOD_STATE_ENUM_SET_UINT32 = 0x7FFFFFFF,         /*!< Field for fixing enum type */
} HSM_FOD_ERR_STATE_t;

typedef struct
{
      FoDCert fodCert;
      HSM_SIGN_t signInfo;
} HSM_FOD_CERT_INPUT_t;

typedef struct
{
      FoDCert fodCert;
      HSM_SIGN_t signInfo;
      UINT8 UserFV[FOD_CERT_FV_LEN];
} HSM_FOD_CERT_INPUT_REV1_t;

typedef struct
{
      HSM_FOD_ERR_STATE_t fodErrState;
      UINT32 numOfFodCert;
      FoDCert fodCertList[FOD_NUMBER_OF_SET];
} HSM_FOD_CERT_OUTPUT_t;

typedef struct
{
    UINT8 UserFV[FOD_CERT_FV_LEN];                          /*!< Store or read user FV(Feature Vector) */
    HSM_FOD_ERR_STATE_t errState;                           /*!< Return the result from HSM */
} HSM_FOD_USERFV_t;
/******************************************************************************/
/*                    	Feature On Demand Function API                        */
/******************************************************************************/
/*!
  @brief Save FoD certificate in HSM
  @details The certificate is classified by the SerialNumber Field, and when the corresponding SerialNumber value is already stored \n
        and the certificate of the same SerialNumber is saved, a new certificate is updated. \n
        If the FoD certificate storage is full, you can save it after deleting the saved certificate. \n
        The signKeyNum of the certificate information writes the HSM Key slot index where the public key of the key used \n
        when creating the signature is stored. \n
        Ex) When creating a signature in aSIMS, enter the aSIMS public key index (0x1) \n
        In other signature creation tools, when creating a signature, pre-inject the relevant public key \n
        into the HSM and write the index set at the time of injection. \n
        If api 'Blocking' mode is setted, API waits for an HSM response. If the result of the API is returned, it means that the HSM operation has also been completed with output parameter. \n
        If api 'Non-blocking' mode is setted, API return immediately witout output parameter. \n
        Caution : Aafter API returns in Non-Blocking Mode, must take HSM response values in order to use next HSM APIs. \n
            HSM_ApiHandler(HSMAPI_OBJ_t *obj) API is for handling of Non-blocking Mode. \n
            For more details, refer to the HSM_ApiHandler API description defined in the 'Hsm_HostAPI.h' header file.
  @param[in] fodCert        FoD certificate information to be saved
  @param[in] signInfo       Signature of FoD certificate to be saved
  @param[in] UserFV         User's feature vector to be saved. The array size(byte) is FOD_CERT_FV_LEN defined in SecurityApp_FeatureOnDemand.h.
  @param[out] errState      Error State value to analyze the cause when returning a value other than E_OK when executing API
  @param[inout] apiObj  Set API process mode and context data(Blocking / Non-Blocking mode)
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
Std_ReturnType HSM_FeatureOnDemandCertStore(const FoDCert *fodCert, const HSM_SIGN_t *signInfo, HSM_FOD_ERR_STATE_t* errState, HSMAPI_OBJ_t *apiObj);
Std_ReturnType HSM_FeatureOnDemandCertStore_Rev1(const FoDCert *fodCert, const HSM_SIGN_t *signInfo, const UINT8 *UserFV, HSM_FOD_ERR_STATE_t* errState, HSMAPI_OBJ_t *apiObj);

/*!
  @brief Delete FoD certificate from HSM
  @details The certificate is classified by the SerialNumber Field, and if the serial number value of the entered certificate is stored in the HSM, \n
        the certificate is deleted. E_NOT_OK is returned when requested without a certificate. \n
        The signKeyNum of the certificate information writes the HSM Key slot index where the public key of the key used when creating the signature is stored. \n
        Ex) When creating a signature in aSIMS, enter the aSIMS public key index (0x1) \n
        In other signature creation tools, when creating a signature, pre-inject the relevant public key \n
        into the HSM and write the index set at the time of injection. \n
        If api 'Blocking' mode is setted, API waits for an HSM response. If the result of the API is returned, it means that the HSM operation has also been completed with output parameter. \n
        If api 'Non-blocking' mode is setted, API return immediately witout output parameter. \n
        Caution : Aafter API returns in Non-Blocking Mode, must take HSM response values in order to use next HSM APIs. \n
            HSM_ApiHandler(HSMAPI_OBJ_t *obj) API is for handling of Non-blocking Mode. \n
            For more details, refer to the HSM_ApiHandler API description defined in the 'Hsm_HostAPI.h' header file.
  @param[in] fodCert        FoD certificate information to be deleted
  @param[in] signInfo       Signature of FoD certificate to be deleted
  @param[in] UserFV         User's feature vector to be saved. The array size(byte) is FOD_CERT_FV_LEN defined in SecurityApp_FeatureOnDemand.h.
  @param[out] errState      Error State value to analyze the cause when returning a value other than E_OK when executing API
  @param[inout] apiObj  Set API process mode and context data(Blocking / Non-Blocking mode)
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
Std_ReturnType HSM_FeatureOnDemandCertDelete(const FoDCert *fodCert, const HSM_SIGN_t *signInfo, HSM_FOD_ERR_STATE_t* errState, HSMAPI_OBJ_t *apiObj);
Std_ReturnType HSM_FeatureOnDemandCertDelete_Rev1(const FoDCert *fodCert, const HSM_SIGN_t *signInfo, const UINT8 *UserFV, HSM_FOD_ERR_STATE_t* errState, HSMAPI_OBJ_t *apiObj);

/*!
  @brief Get the FoD certificates stored in HSM
  @details Return as FoDCert Infomation structure through output parameter. \n
        If api 'Blocking' mode is setted, API waits for an HSM response. If the result of the API is returned, it means that the HSM operation has also been completed with output parameter. \n
        If api 'Non-blocking' mode is setted, API return immediately witout output parameter. \n
        Caution : Aafter API returns in Non-Blocking Mode, must take HSM response values in order to use next HSM APIs. \n
            HSM_ApiHandler(HSMAPI_OBJ_t *obj) API is for handling of Non-blocking Mode. \n
            For more details, refer to the HSM_ApiHandler API description defined in the 'Hsm_HostAPI.h' header file.
  @param[out] fodListInfo   Return the certificate stored on the HSM
  @param[inout] apiObj  Set API process mode and context data(Blocking / Non-Blocking mode)
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
Std_ReturnType HSM_FeatureOnDemandGetCertList(HSM_FOD_CERT_OUTPUT_t *fodListInfo, HSMAPI_OBJ_t *apiObj);

/*!
  @brief Store user's feature vector in HSM
  @details User (or application) can use this API to store usr's FV(feature vector) in HSM storage. \n
        HSM only provides storage to be saved a feature vector that is not directly related to certificate stored on the HSM.
  @param[in] fodUserFV      User's feature vector and return value to be saved. The array size(byte) of FV is FOD_CERT_FV_LEN defined in SecurityApp_FeatureOnDemand.h.
  @param[inout] apiObj      Set API process mode and context data(Blocking / Non-Blocking mode)
  @return E_OK: This is returned when a function execution is successful. \n
        E_NOT_OK: This is returned when a function execution fails. \n
        HSM_E_BUSY: HSM internal task is busy. \n
        HSM_E_NOT_SUPPORTED: Not supported feature in HSM Framework. \n
        HSM_E_LENGTH_NOT_VALID: Invalid parameter length. \n
        HSM_E_VALUE_NOT_VALID: Invalid parameter value. \n
        HSM_E_UNINIT: HSM_DriverInitialize is not performed
*/
Std_ReturnType HSM_FeatureOnDemandUserFVStore(HSM_FOD_USERFV_t *fodUserFV, HSMAPI_OBJ_t *apiObj);

/*!
  @brief Read user's feature vector stored in HSM
  @details User (or application) can use this API to read the FV(feature vector) value stored. \n
        HSM only provides storage to be saved a feature vector that is not directly related to certificate stored on the HSM.
  @param[out] fodUserFV     The saved address of feature vector and result value. The array size(byte) of FV is FOD_CERT_FV_LEN defined in SecurityApp_FeatureOnDemand.h.
  @param[inout] apiObj      Set API process mode and context data(Blocking / Non-Blocking mode)
  @return E_OK: This is returned when a function execution is successful. \n
        E_NOT_OK: This is returned when a function execution fails. \n
        HSM_E_BUSY: HSM internal task is busy. \n
        HSM_E_NOT_SUPPORTED: Not supported feature in HSM Framework. \n
        HSM_E_LENGTH_NOT_VALID: Invalid parameter length. \n
        HSM_E_VALUE_NOT_VALID: Invalid parameter value. \n
        HSM_E_UNINIT: HSM_DriverInitialize is not performed
*/
Std_ReturnType HSM_FeatureOnDemandUserFVRead(HSM_FOD_USERFV_t *fodUserFV, HSMAPI_OBJ_t *apiObj);

#endif /* SECURITYAPP_FEATURE_ON_DEMAND_H_ */
