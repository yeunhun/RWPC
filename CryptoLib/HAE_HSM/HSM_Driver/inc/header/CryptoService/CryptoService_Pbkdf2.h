/*!
  @file CryptoService_Pbkdf2.h
  @brief Crypto API header file for PBKDF2
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef CRYPTOSERVICE_PBKDF2_H_
#define CRYPTOSERVICE_PBKDF2_H_

#include "Hsm_Types.h"

/******************************************************************************/
/*                                   PBKDF2                                   */
/******************************************************************************/
/*!
  @brief This function requests the HSM framework's PBKDF2 Start service
  @details If ¡®0¡¯ is entered as ¡®pbkdf2KeyNum¡¯, the password value entered by the user in the Update function is used. \n
        If a ¡®pbkdf2KeyNum¡¯of ¡®1¡¯ or greater is entered a key value (16 bytes) stored in the security domain of the HSM framework is used as a password.
  @param[in, out] pbkdf2Ctx     PBKDF2 context
  @param[in] pbkdf2KeyNum       The key number to use as a password
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
Std_ReturnType HSM_Pbkdf2Start(HSMAPI_CTX_t *pbkdf2Ctx, UINT16 pbkdf2KeyNum);

/*!
  @brief This API requests the HSM framework's PBKDF2 Update service
  @details The function does not wait for the HSM to respond. \n
        After calling the function, the user must check the execution result calling the 'HSM_WaitResp()' function of the HSM driver. \n
        The password required as an input of PBKDF2 can be received by user input or can be replaced with a key value stored in the security domain of the HSM framework.  \n
        When Start function is called, if key number is entered as ¡®0¡¯ the user¡¯s input value is used as a password. \n
        If key number is equal or greater than1, a key value from the HSM domain is used as a password. \n
        If using a key value from the HSM framework as a password, enter NULL for the variable ¡®password¡¯ and 0 for the variable ¡®pLen¡¯. \n
        The ¡®salt¡¯ is a value used to prevent security vulnerabilities such as reuse attacks. \n
        The ¡®icount¡¯ is the number of iterations of the internal hash function. The larger the number, the longer the computation time is.
  @param[in, out] pbkdf2Ctx     PBKDF2 context
  @param[in] pbkdf2KeyNum       Password key number. USER MUST USE same value pbkdf2KeyNum in Start API
  @param[in] dkLen              Length of key to derive
  @param[in] password           Pointer to the password to be entered from the user (Enter ¡®NULL¡¯ value if the key value stored in the HSM framework is used as a password)
  @param[in] pLen               Length of the password to be entered (Enter ¡®0¡¯ value if the key value stored in the HSM framework is used as a password)
  @param[in] salt               Pointer to the input salt (random number) value
  @param[in] sLen               Length of the salt (random number)
  @param[in] icount             Number of internal operation iterations
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
Std_ReturnType HSM_Pbkdf2Update(const HSMAPI_CTX_t *pbkdf2Ctx, UINT16 pbkdf2KeyNum, UINT32 dkLen, const UINT8 *password, UINT32 pLen, const UINT8 *salt, UINT32 sLen, UINT32 icount);

/*!
  @brief This API requests the HSM framework's PBKDF2 Finish service
  @details A derived key of the length requested by the user(¡®dkLen¡¯ variable of the update function)is generated and output to the ¡®derivedkey¡¯ variable.
  @param[in, out] pbkdf2Ctx     PBKDF2 context
  @param[in] dkLen              output key length
  @param[out] derivedKey        Pointer to the output derived key
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
Std_ReturnType HSM_Pbkdf2Finish(const HSMAPI_CTX_t *pbkdf2Ctx, UINT32 dkLen, UINT8 *derivedKey);

#endif /* CRYPTOSERVICE_PBKDF2_H_ */
