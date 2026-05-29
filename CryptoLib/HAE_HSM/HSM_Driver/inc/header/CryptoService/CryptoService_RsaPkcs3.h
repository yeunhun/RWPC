/*!
  @file CryptoService_RsaPkcs3.h
  @brief Crypto API header file for RSA PKCS#3
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef CRYPTOSERVICE_RSA_PKCS3_H_
#define CRYPTOSERVICE_RSA_PKCS3_H_

#include "Hsm_Types.h"

/******************************************************************************/
/*                                  Type Define                               */
/******************************************************************************/
#include "CryptoService_Def.h"

/******************************************************************************/
/*                   PKCS3 DiffieHellman - Keypair Generate                    */
/******************************************************************************/
/*!
  @brief This API requests the HSM framework's RSA PKCS#3 Keypair Generate Start service
  @param[in, out] pkcs3Ctx  RSA PKCS#3 context
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
Std_ReturnType HSM_RsaPkcs3DHKeypairGenStart(HSMAPI_CTX_t *pkcs3Ctx);

/*!
  @brief This API requests the HSM framework's RSA PKCS#3 Keypair Generate Update service
  @details The function does not wait for HSM response. \n
        After calling the function, the user need to check the execution result of the HSM by calling the 'HSM_WaitResp()' function of the HSM driver. \n
        To use the user¡¯s private value, enter a Private Value into privValue argument. \n
        To use a private value generated in the HSM framework, enter NULL value in the ¡®PrivValue¡¯ argument. \n
        If ¡®NULL¡¯ is entered for the ¡®baseG¡¯ and ¡®primeP¡¯ variable, the defined values are used internally.
  @param[in, out] pkcs3Ctx  RSA PKCS#3 context
  @param[in] privValue      Pointer to the user¡¯s Private Value
  @param[in] baseG          Pointer to base G value to be used for DH
  @param[in] primeP         Pointer to the modular prime number to be used for DH
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
Std_ReturnType HSM_RsaPkcs3DHKeypairGenUpdate(const HSMAPI_CTX_t *pkcs3Ctx, const UINT8 *privValue, const UINT8 *baseG, const UINT8 *primeP);

/*!
  @brief This API requests the HSM framework's RSA PKCS#3 Keypair Generate Finish service
  @details This function operates ¡®(publicValue) = (baseG) ^ (privateValue) mod (primP)¡¯. \n
        If the user does not enter the user¡¯s private value in the Update function, the HSM framework generates the private value randomly \n
        and outputs it to the ¡®privateValue¡¯ variable. \n
        If the user enters the user¡¯s private value in the Update function, the value is output to the ¡®privateValue¡¯ variable.
  @param[in, out] pkcs3Ctx  RSA PKCS#3 context
  @param[out] privValue     Pointer to the generated DH public key value
  @param[out] privateValue  Pointer to the generated DH private key value
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
Std_ReturnType HSM_RsaPkcs3DHKeypairGenFinish(const HSMAPI_CTX_t *pkcs3Ctx, UINT8 *publicValue, UINT8 *privateValue);

/******************************************************************************/
/*                 PKCS3 DiffieHellman - Shared Value Generate                 */
/******************************************************************************/
/*!
  @brief This API requests the HSM framework's RSA PKCS#3 Shared Value Generate Start service
  @param[in, out] pkcs3Ctx  RSA PKCS#3 context
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
Std_ReturnType HSM_RsaPkcs3DHSharedValueGenStart(HSMAPI_CTX_t *pkcs3Ctx);

/*!
  @brief This API requests the HSM framework's RSA PKCS#3 Shared Value Generate Update service
  @details The function does not wait for HSM response. \n
        After calling the function, the user need to check the execution result of the HSM by calling the 'HSM_WaitResp()' function of the HSM driver.
  @param[in, out] pkcs3Ctx  RSA PKCS#3 context
  @param[in] publicValue    Pointer to public key value of the other party
  @param[in] privateValue   Pointer to private key value of the user
  @param[in] primeP         Pointer to the modular prime number to be used for DH
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
Std_ReturnType HSM_RsaPkcs3DHSharedValueGenUpdate(const HSMAPI_CTX_t *pkcs3Ctx, const UINT8 *publicValue, const UINT8 *privateValue, const UINT8 *primeP);

/*!
  @brief This API requests the HSM framework's RSA PKCS#3 Shared Value Generate Finish service
  @details This function operates ¡®(secretValue) = (publicValue) ^ (privateValue) mod (primP)¡¯. \n
        The secret value is generated by the other party's public key and the user¡¯s private key. \n
        If the public key is exchanged, the user can have the same secret value as the other party.
  @param[in, out] pkcs3Ctx  RSA PKCS#3 context
  @param[out] secretValue   Pointer to the value generated by the user¡¯s private key and the public key of the other party
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
Std_ReturnType HSM_RsaPkcs3DHSharedValueGenFinish(const HSMAPI_CTX_t *pkcs3Ctx, UINT8 *secretValue);

#endif /* CRYPTOSERVICE_RSA_PKCS3_H_ */
