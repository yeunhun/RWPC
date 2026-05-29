/*!
  @file CryptoService_RsaPkcs1.h
  @brief Crypto API header file for RSA PKCS#1
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef CRYPTOSERVICE_RSA_PKCS1_H_
#define CRYPTOSERVICE_RSA_PKCS1_H_

#include "Hsm_Types.h"

/******************************************************************************/
/*                                    Define                                  */
/******************************************************************************/
#include "CryptoService_Def.h"

/******************************************************************************/
/*                                  Type Define                               */
/******************************************************************************/

/******************************************************************************/
/*                                 PKCS1v15 - SIGN                            */
/******************************************************************************/
/*!
  @brief This API requests the HSM framework's RSA PKCS#1 v1.5 Sign Start service
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[in] rsaKeyNum      RSA key number
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
Std_ReturnType HSM_RsaPkcs1v15SignStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum);

/*!
  @brief This API requests the HSM framework's RSA PKCS#1v1.5 Sign Update service
  @details Before calling the function, the digest value of the message data should be generated through a Sha256 hash function. \n
        The function does not wait for HSM response. \n
        After calling the function, the user should check the execution result of the HSM by calling the ¡®HSM_WaitResp()¡¯function of the HSM driver.
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[in] digest         32bytes of Sha256 hash value
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
Std_ReturnType HSM_RsaPkcs1v15SignUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *digest);

/*!
  @brief This API requests the HSM framework's RSA PKCS#1v1.5 Sign Finish service
  @details The resulting data are stored in the ¡®sign¡¯ variable.
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[out] sign          256-bytes Generated signature value
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
Std_ReturnType HSM_RsaPkcs1v15SignFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *sign);

/******************************************************************************/
/*                                 PKCS1v15 - VERIFY                          */
/******************************************************************************/
/*!
  @brief This API requests the HSM framework's RSA PKCS#1 v1.5 Verify Start service
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[in] rsaKeyNum      RSA key number
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
Std_ReturnType HSM_RsaPkcs1v15VerifyStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum);

/*!
  @brief This API requests the HSM framework's RSA PKCS#1 v1.5 Verify Update service
  @details Before calling the function, the digest value of the message data should be generated through aSha256 hash function. \n
        The function does not wait for HSM response. \n
        After calling the function, the user should check the execution result of the HSM by calling the ¡®HSM_WaitResp()¡¯ function of the HSM driver.
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[in] digest         32-bytes Sha256 hash value
  @param[in] sign           256-bytes Signature value to validate 
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
Std_ReturnType HSM_RsaPkcs1v15VerifyUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *digest, const UINT8 *sign);

/*!
  @brief Same as PKCS#1 v1.5 Verify Update API, but digest uses SHA160
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[in] digest         20bytes of Sha160 hash value
  @param[in] sign           256-bytes Signature value to validate
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
Std_ReturnType HSM_RsaPkcs1v15Sha160VerifyUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *digest, const UINT8 *sign);

/*!
  @brief This API requests the HSM framework's RSA PKCS#1 v1.5 Verify Finish service
  @details The resulting value is stored in the ¡®result¡¯ variable. \n
        If the validation succeeds, the value of HSM_VERIFY_SUCCESS (0) is stored in the ¡®result¡¯ variable. \n
        If unsuccessful, the value of HSM_VERIFY_FAILURE (1) is stored.
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[out] verifyResult  1-byte verification result value
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
Std_ReturnType HSM_RsaPkcs1v15VerifyFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *verifyResult);

/******************************************************************************/
/*                                 PKCS1v15 - ENC                             */
/******************************************************************************/
/*!
  @brief This API requests the HSM framework's RSA PKCS#1v1.5 Encryption Start service
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[in] rsaKeyNum      RSA key number
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
Std_ReturnType HSM_RsaPkcs1v15EncStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum);

/*!
  @brief This API requests the HSM framework's RSA PKCS#1 v1.5 Encryption Update service
  @details The plaintext data length should be less than 245-bytes. \n
        The function does not wait for HSM response. \n
        After calling the function, the user need to check the execution result of the HSM by calling the 'HSM_WaitResp()' function of the HSM driver. \n
        If the plaintext data length is out of range, the return value of 'HSM_RT_FAIL' is returned as a result of the 'HSM_WaitResp()' function \n
        and the error code value of 'HSM_ERR_INVALID_INPUT_LENGTH' is stored.
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[in] msg            Plaintext data
  @param[in] msgLen         Plaintext data length (length should be less than 245-byte)
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
Std_ReturnType HSM_RsaPkcs1v15EncUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *msg, UINT32 msgLen);

/*!
  @brief This API requests the HSM framework's RSA PKCS#1 v1.5 Encryption Finish service
  @details The resulting ciphertext is stored in the ¡®cipher¡¯ variable.
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[out] cipher        256-bytes ciphertext data
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
Std_ReturnType HSM_RsaPkcs1v15EncFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *cipher);

/******************************************************************************/
/*                                 PKCS1v15 - DEC                             */
/******************************************************************************/
/*!
  @brief This API requests the HSM framework's RSA PKCS#1 v1.5 Decryption Start service
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[in] rsaKeyNum      RSA key number
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
Std_ReturnType HSM_RsaPkcs1v15DecStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum);

/*!
  @brief This API requests the HSM framework's RSA PKCS#1 v1.5 Decryption Update service
  @details The function does not wait for HSM response. \n
        After calling the function, the user need to check the execution result of the HSM by calling the 'HSM_WaitResp()' function of the HSM driver.
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[in] cipher         256-bytes ciphertext data
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
Std_ReturnType HSM_RsaPkcs1v15DecUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *cipher);

/*!
  @brief This API requests the HSM framework's RSA PKCS#1 v1.5 Decryption Finish service
  @details The resulting plaintext is stored in the ¡®msg¡¯ variable. \n
        The resulting plaintext length is stored in the ¡®msgLen¡¯ variable.
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[out] msg           Plaintext data
  @param[out] msgLen        Plaintext data length
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
Std_ReturnType HSM_RsaPkcs1v15DecFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *msg, UINT32 *msgLen);

/******************************************************************************/
/*                                 PKCS1pss - SIGN                            */
/******************************************************************************/
/*!
  @brief This API requests the HSM framework's RSA PKCS#1 PSS Sign Start service
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[in] rsaKeyNum      RSA key number
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
Std_ReturnType HSM_RsaPkcs1PssSignStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum);

/*!
  @brief This API requests the HSM framework's RSA PKCS#1 PSS Sign Update service
  @details Before calling the function, the digest value should be generated through aSha256 hash function. \n
        The function does not wait for HSM response. \n
        After calling the function, the user need to check the execution result of the HSM by calling the 'HSM_WaitResp()' function of the HSM driver. \n
        The ¡®salt¡¯ uses the value generated by the random generator. \n
        When verifying a signature, a ¡®salt¡¯ is not necessary, only a ¡®saltLen¡¯ is necessary.
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[in] digest         32-bytes Sha256 digest value
  @param[in] salt           The random number to be used to generate a signature
  @param[in] saltLen        The random number length to be used to generate a signature
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
Std_ReturnType HSM_RsaPkcs1PssSignUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *digest, const UINT8 *salt, UINT32 saltLen);

/*!
  @brief This API requests the HSM framework's RSA PKCS#1 PSS Sign Finish service
  @details The result is stored in the ¡®sign¡¯ variable.
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[out] sign          256-bytes Generated signature value
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
Std_ReturnType HSM_RsaPkcs1PssSignFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *sign);

/******************************************************************************/
/*                                 PKCS1pss - VERIFY                          */
/******************************************************************************/
/*!
  @brief This API requests the HSM framework's RSA PKCS#1 PSS Verify Start service
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[in] rsaKeyNum      RSA key number
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
Std_ReturnType HSM_RsaPkcs1PssVerifyStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum);

/*!
  @brief This API requests the HSM framework's RSA PKCS#1 PSS Verify Update service
  @details Before calling the function, the digest value should be generated through aSha256 hash function. \n
        The function does not wait for HSM response. \n
        After calling the function, the user need to check the execution result of the HSM by calling the 'HSM_WaitResp()' function of the HSM driver.
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[in] digest         32-bytes Sha256 digest value
  @param[in] sign           256-bytes signature value to validate
  @param[in] saltLen        The random number length used to generate the signature
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
Std_ReturnType HSM_RsaPkcs1PssVerifyUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *digest, const UINT8 *sign, UINT32 saltLen);

/*!
  @brief This API requests the HSM framework's RSA PKCS#1 PSS Verify Finish service
  @details The result is stored in the ¡®result¡¯ variable. \n
        If the validation succeeds, the value of 'HSM_VERIFY_SUCCESS(0) is stored in the ¡®result¡¯ variable. \n
        If unsuccessful, the value of HSM_VERIFY_FAILURE(1) is stored.
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[out] result        1-byte verification result value
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
Std_ReturnType HSM_RsaPkcs1PssVerifyFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *result);

/******************************************************************************/
/*                                 PKCS1oaep - ENC                            */
/******************************************************************************/
/*!
  @brief This API requests the HSM framework's RSA PKCS#1 OAEP Encryption Start service
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[in] rsaKeyNum      RSA key number
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
Std_ReturnType HSM_RsaPkcs1oaepEncStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum);

/*!
  @brief This API requests the HSM framework's RSA PKCS#1 OAEP Encryption Update service
  @details The function does not wait for HSM response. \n
        After calling the function, the user need to check the execution result of the HSM by calling the 'HSM_WaitResp()' function of the HSM driver. \n
        If the plaintext data length is out of range, the return value of ¡®HSM_RT_FAIL¡¯ is returned as a result of the 'HSM_WaitResp()' function \n
        and the error code value of 'HSM_ERR_INVALID_INPUT_LENGTH' is stored.
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[in] msg            plaintext data
  @param[in] msgLen         plaintext data length
  @param[in] label          Label data
  @param[in] labelLen       Label data length
  @param[in] seed           32-bytesrandom seed value
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
Std_ReturnType HSM_RsaPkcs1oaepEncUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *msg, UINT32 msgLen, const UINT8 *label, UINT32 labelLen, const UINT8 *seed);

/*!
  @brief This API requests the HSM framework's RSA PKCS#1OAEP Encryption Finish service
  @details The resulting ciphertext is stored in the ¡®cipher¡¯ variable.
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[out] cipher        256 bytes of ciphertext data
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
Std_ReturnType HSM_RsaPkcs1oaepEncFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *cipher);

/******************************************************************************/
/*                                 PKCS1oaep - DEC                            */
/******************************************************************************/
/*!
  @brief This API requests the HSM framework's RSA PKCS#1 OAEP Decryption Start service
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[in] rsaKeyNum      RSA key number
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
Std_ReturnType HSM_RsaPkcs1oaepDecStart(HSMAPI_CTX_t *pkcs1Ctx, UINT16 rsaKeyNum);

/*!
  @brief This API requests the HSM framework's RSA PKCS#1 OAEP Decryption Update service
  @details The function does not wait for HSM response. \n
        After calling the function, the user need to check the execution result of the HSM by calling the 'HSM_WaitResp()' function of the HSM driver.
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[in] cipher         256-Byte ciphertext data
  @param[in] label          Label data
  @param[in] labelLen       Label data length
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
Std_ReturnType HSM_RsaPkcs1oaepDecUpdate(const HSMAPI_CTX_t *pkcs1Ctx, const UINT8 *cipher, const UINT8 *label, UINT32 labelLen);

/*!
  @brief This API requests the HSM framework's RSA PKCS#1 OAEP Decryption Finish service
  @details The resulting plaintext is stored in the ¡®msg¡¯ variable. \n
        The resulting plaintext length is stored in the ¡®msgLen¡¯ variable.
  @param[in, out] pkcs1Ctx  RSA PKCS#1 context
  @param[out] msg           plaintext data
  @param[out] msgLen        plaintext data length
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
Std_ReturnType HSM_RsaPkcs1oaepDecFinish(const HSMAPI_CTX_t *pkcs1Ctx, UINT8 *msg, UINT32 *msgLen);

#endif /* CRYPTOSERVICE_RSA_PKCS1_H_ */
