/*!
  @file CryptoService_Hash.h
  @brief Crypto API header file for HASH
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef CRYPTOSERVICE_HASH_H_
#define CRYPTOSERVICE_HASH_H_

#include "Hsm_Types.h"

/******************************************************************************/
/*                                    Define                                  */
/******************************************************************************/
#include "CryptoService_Def.h"

/******************************************************************************/
/*                                 HASH (SHA1)                                */
/******************************************************************************/
/*!
  @brief This API requests the HSM framework's SHA160 Start service
  @param[in, out] sha160Ctx     Hash context
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
Std_ReturnType HSM_Sha160Start(HSMAPI_CTX_t *sha160Ctx);

/*!
  @brief This API requests the HSM framework's SHA160 Update service
  @details The maximum length of the input data is 1020bytes. \n
        If the length of the input data exceeds 1020 bytes, call the Update function repeatedly until all data is transferred. \n
        The function does not wait for HSM response. \n
        After calling the function, the user need to check the execution result of the HSM by calling the 'HSM_WaitResp()' function of the HSM driver.
  @param[in, out] sha160Ctx     Hash context
  @param[in] data               Input data to calculate for SHA160
  @param[in] dataLen            Input data length to calculate for SHA160 (up to 1020 bytes)
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
Std_ReturnType HSM_Sha160Update(const HSMAPI_CTX_t *sha160Ctx, const UINT8 *data, UINT32 dataLen);

/*!
  @brief This API requests the HSM framework's SHA160 Finish service
  @details The hash result is stored in the ¡®digest¡¯variable.
  @param[in, out] sha160Ctx     Hash context
  @param[out] digest            Sha160 Hash calculated hash value(message digest)
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
Std_ReturnType HSM_Sha160Finish(const HSMAPI_CTX_t *sha160Ctx, UINT8 *digest);

/******************************************************************************/
/*                                 HASH (SHA256)                              */
//*****************************************************************************/
/*!
  @brief This API requests the HSM framework's SHA256 Start service
  @param[in, out] sha256Ctx     Hash context
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
Std_ReturnType HSM_Sha256Start(HSMAPI_CTX_t *sha256Ctx);

/*!
  @brief This API requests the HSM framework's SHA256 Update service
  @details The maximum length of the input data is 1020bytes. \n
        If the length of the input data exceeds 1020 bytes, call the Update function repeatedly until all data is transferred. \n
        The function does not wait for HSM response. \n
        After calling the function, the user need to check the execution result of the HSM by calling the 'HSM_WaitResp()' function of the HSM driver.
  @param[in, out] sha256Ctx     Hash context
  @param[in] data               Input data to calculate for SHA256
  @param[in] dataLen            Input data length to calculate for SHA256 (up to 1020 bytes)
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
Std_ReturnType HSM_Sha256Update(const HSMAPI_CTX_t *sha256Ctx, const UINT8 *data, UINT32 dataLen);

/*!
  @brief This API requests the HSM framework's SHA256 Finish service
  @details The hash result is stored in the ¡®digest¡¯variable
  @param[in, out] sha256Ctx     Hash context
  @param[out] digest            Sha256 Hash calculated hash value(message digest)
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
Std_ReturnType HSM_Sha256Finish(const HSMAPI_CTX_t *sha256Ctx, UINT8 *digest);

/******************************************************************************/
/*                                 MAC (SHA256)                               */
/******************************************************************************/
/*!
  @brief This API requests the HSM framework's HMAC(SHA256) Start service
  @param[in, out] hmacSha256Ctx     HMAC Sha256 context
  @param[in] keyNum                 HMAC Sha256 key number
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
Std_ReturnType HSM_HmacSha256Start(HSMAPI_CTX_t *hmacSha256Ctx, UINT16 keyNum);

/*!
  @brief This API requests the HSM framework's HMAC(SHA256) Update service
  @details The maximum length of the input data is 1020 bytes. \n
        If the length of the input data exceeds 1020 bytes, call the Update function repeatedly until all data is transferred. \n
        The function does not wait for HSM response. \n
        After calling the function, the user need to check the execution result of the HSM by calling the 'HSM_WaitResp()' function of the HSM driver.
  @param[in, out] hmacSha256Ctx     HMAC Sha256 context
  @param[in] data                   Input data to calculate for HMAC(SHA256)
  @param[in] dataLen                Input data length to calculate for MAC(SHA256)(maximum 1020 bytes)
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
Std_ReturnType HSM_HmacSha256Update(const HSMAPI_CTX_t *hmacSha256Ctx, const UINT8 *data, UINT32 dataLen);

/*!
  @brief This API requests the HSM framework's HMAC(SHA256) Finish service
  @details The result of HMAC(SHA256)is stored in the ¡®digest¡¯variable.
  @param[in, out] hmacSha256Ctx     HMAC Sha256 context
  @param[out] digest                HMAC Sha256 calculated hash value(message digest)
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
Std_ReturnType HSM_HmacSha256Finish(const HSMAPI_CTX_t *hmacSha256Ctx, UINT8 *digest);

#endif /* CRYPTOSERVICE_HASH_H_ */
