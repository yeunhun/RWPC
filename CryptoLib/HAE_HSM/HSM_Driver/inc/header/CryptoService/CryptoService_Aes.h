/*!
  @file CryptoService_Aes.h
  @brief Crypto API header file for AES
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef CRYPTOSERVICE_AES_H_
#define CRYPTOSERVICE_AES_H_

#include "Hsm_Types.h"

/******************************************************************************/
/*                                    Define                                  */
/******************************************************************************/
#include "CryptoService_Def.h"

/******************************************************************************/
/*                                  AES MODE                                  */
/******************************************************************************/
/*! AES mode using encryption and decryption interface parameter */
typedef enum
{
	HSM_AES_ECB_MODE,   /*!< ECB mode */
	HSM_AES_CBC_MODE,   /*!< CBC mode */
	HSM_AES_CTR_MODE,   /*!< CTR mode */
	HSM_AES_OFB_MODE    /*!< OFB mode */
} AES_MODE;

/****************************************************************************/
/*                                 AES ENC-DEC                              */
/****************************************************************************/
/*!
  @brief This API requests the HSM Framework¡¯s AES Encryption Start service
  @param[in, out] aesCtx    AES context
  @param[in] aesMode        Encryption Mode
  @param[in] aesKeyNum      AES key number
  @param[in] ivBuff         16 bytes initial vector. NULL for ECB mode
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
Std_ReturnType HSM_AesEncStart(HSMAPI_CTX_t *aesCtx, AES_MODE aesMode, UINT16 aesKeyNum, const UINT8 *ivBuff);

/*!
  @brief This API requests the HSM Framework¡¯s AES Encryption Update service
  @details The maximum length of the input data is 1024 Bytes \n
        If input data length exceeds 1024 bytes, call Update API repeatedly until all data is transferred. \n
        The function does not wait for HSM response. \n
        After calling the function, the user need to check the execution result of the HSM by calling the 'HSM_WaitResp()' function of the HSM driver. \n
        When the HSM finishes the update service, call the 'HSM_ReadRxBuff()' function of the HSM driver and receive the resulting cipher text.
  @param[in, out] aesCtx    AES context
  @param[in] plain          plaintext data
  @param[in] plainLen       plaintext data length(up to 1024 bytes)
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
Std_ReturnType HSM_AesEncUpdate(const HSMAPI_CTX_t *aesCtx, const UINT8 *plain, UINT32 plainLen);

/*!
  @brief This API requests the HSM framework¡¯s AES Encryption Finish service
  @param[in, out] aesCtx    AES context
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
Std_ReturnType HSM_AesEncFinish(const HSMAPI_CTX_t *aesCtx);

/*!
  @brief This API requests the HSM framework¡¯s AES Decryption Start service
  @param[in, out] aesCtx    AES context
  @param[in] aesMode        Encryption Mode
  @param[in] aesKeyNum      AES key number
  @param[in] ivBuff         16 bytes initial vector. NULL for ECB mode
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
Std_ReturnType HSM_AesDecStart(HSMAPI_CTX_t *aesCtx, AES_MODE aesMode, UINT16 aesKeyNum, const UINT8 *ivBuff);

/*!
  @brief This API requests the HSM framework's AES Decryption Update service
  @details The maximum length of the input data is 1024 bytes. \n
        If the length of the input data exceeds 1024 bytes, call Update function repeatedly until all data is transferred. \n
        The function does not wait for HSM response. \n
        After calling the function, the user need to check the execution result of the HSM by calling the 'HSM_WaitResp()' function of the HSM driver. \n
        When the HSM finishes the update service, call the 'HSM_ReadRxBuff()' function of the HSM driver and receive the resulting plaintext.
  @param[in, out] aesCtx    AES context
  @param[in] cipher         ciphertext data
  @param[in] cipherLen      ciphertext data length  (up to 1024Bytes)
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
Std_ReturnType HSM_AesDecUpdate(const HSMAPI_CTX_t *aesCtx, const UINT8 *cipher, UINT32 cipherLen);

/*!
  @brief This API requests the HSM Framework¡¯s AES Decryption Finish service
  @param[in, out] aesCtx    AES context
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
Std_ReturnType HSM_AesDecFinish(const HSMAPI_CTX_t *aesCtx);

/****************************************************************************/
/*                                 AES CMAC                                 */
/****************************************************************************/
/*!
  @brief This API requests the HSM framework's AES CMAC Start service
  @param[in, out] aesCmacCtx    AES context
  @param[in] aesCmacKeyNum      AES key number
  @param[in] totalMsgLen        Length of total input data to calculate for CMAC 
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
Std_ReturnType HSM_AesCmacStart(HSMAPI_CTX_t *aesCmacCtx, UINT16 aesCmacKeyNum, UINT32 totalMsgLen);

/*!
  @brief This API requests the HSM framework's AES CMAC Update service
  @details The maximum length of the input data is 1024 bytes. \n
        If the length of the input data exceeds 1024 bytes, call Update function repeatedly until all data is transferred. \n
        The function does not wait for HSM response. \n
        After calling the function, the user should check the execution result of HSM by calling the ¡®HSM_WaitResp()¡¯function of the HSM driver.
  @param[in, out] aesCmacCtx    AES context
  @param[in] data               Input data to calculate for CMAC
  @param[in] dataLen            Input data length to calculate for CMAC(up to 1024 bytes)
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
Std_ReturnType HSM_AesCmacUpdate(const HSMAPI_CTX_t *aesCmacCtx, const UINT8 *data, UINT32 dataLen);

/*!
  @brief This API requests the HSM framework's AES CMAC Finish service
  @details The CMAC result data is stored in the ¡®digest¡¯variable.
  @param[in, out] aesCmacCtx    AES context
  @param[out] digest            CMAC result data
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
Std_ReturnType HSM_AesCmacFinish(const HSMAPI_CTX_t *aesCmacCtx, UINT8 *digest);

#endif /* CRYPTOSERVICE_AES_H_ */
