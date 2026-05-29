/******************************************************************************/
/*                              Header Include                                */
/******************************************************************************/
#include "Demo_Ecc.h"

#include "Hsm_KeyTypes.h"
#include "CryptoService_Ecc.h"
#include "Hsm_HostAPI.h"
#include "HsmDrv_API.h"

/******************************************************************************/
/*                                 Global Veriable                            */
/******************************************************************************/
extern HSM_ERROR_CODE g_ErrorCode;

/******************************************************************************/
/*                             ECC DEMO CODE - Sign Generate                  */
/******************************************************************************/
Std_ReturnType eccEcdsaSignTest_Simple(HSM_Ecc_Ecdsa_TestVector ecdsaTv)
{
	volatile Std_ReturnType result = E_OK;
	UINT32 i;
	ECC_ECDSA_SIGN_t resultSign;

	result = HSM_EcdsaSign(ecdsaTv.keyNum, ecdsaTv.digest, ecdsaTv.secret, &resultSign);
	if(result == E_OK)
	{
		for (i = 0; i < ECC_BYTES_SIZE; i++)
		{
			if ((resultSign.r[i] != ecdsaTv.sign.r[i])
			||(resultSign.s[i] != ecdsaTv.sign.s[i]))
			{
				result = E_NOT_OK;
				break;
			}
		}
	}
	else
	{
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}

	return result;
}

/******************************************************************************/
/*                             ECC DEMO CODE - Sign Verify                    */
/******************************************************************************/
Std_ReturnType eccEcdsaVerifyTest_Simple(HSM_Ecc_Ecdsa_TestVector ecdsaTv)
{
	volatile Std_ReturnType result = E_OK;
	UINT8 verifyResult = HSM_VERIFY_FAILURE;

	result = HSM_EcdsaSignVerify(ecdsaTv.keyNum, ecdsaTv.digest, &ecdsaTv.sign, &verifyResult);
	if(result == E_OK)
	{
		if (verifyResult == HSM_VERIFY_FAILURE)
		{
			result = E_NOT_OK;
		}
	}
	else
	{
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}

	return result;
}

/******************************************************************************/
/*                   ECC DEMO CODE - Diffie Hellman key exchange              */
/******************************************************************************/
Std_ReturnType eccEcdhTest_Simple(HSM_Ecc_Ecdh_TestVector ecdhTv)
{
	volatile Std_ReturnType result = E_OK;
	UINT32 i;
	UINT8 output[ECC_BYTES_SIZE];

	result = HSM_Ecdh(ecdhTv.keyNum, &ecdhTv.pubkeyOtherSide, output);
	if(result == E_OK)
	{
		for (i = 0; i < ECC_BYTES_SIZE; i++)
		{
			if (output[i] != ecdhTv.secretValue[i])
			{
				result = E_NOT_OK;
				break;
			}
		}
	}
	else
	{
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}

	return result;
}

/******************************************************************************/
/*                             ECC ECDSA-SIGN FUNC                            */
/******************************************************************************/
Std_ReturnType HSM_EcdsaSign(const UINT16 keyNum, const UINT8 *digest, const UINT8 *secret, ECC_ECDSA_SIGN_t *sign)
{
	volatile Std_ReturnType result = E_OK;
	HSMAPI_CTX_t eccCtx;

	volatile UINT32 timeout = 0;
			

	do
	{
		result = HSM_EccEcdsaSignStart(&eccCtx, keyNum);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	do
	{
		result = HSM_EccEcdsaSignUpdate(&eccCtx, digest, secret);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			HSM_CancelJob(eccCtx.jobId);
			return result;
		}
	} while (result == HSM_E_BUSY);

	do
	{
		result = HSM_WaitResp(eccCtx.jobId);
		if (result != HSM_E_WAIT)
		{
			break;
		}
		timeout++;
	} while (timeout < WAIT_RESP_TIMEOUT);

	if (result != E_OK)
	{
		
		HSM_CancelJob(eccCtx.jobId);
		return result;
	}

	do
	{
		result = HSM_EccEcdsaSignFinish(&eccCtx, sign);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	} while (result == HSM_E_BUSY);

	return result;
}

/******************************************************************************/
/*                               ECC ECDSA-VERIFY FUNC                        */
/******************************************************************************/
Std_ReturnType HSM_EcdsaSignVerify(const UINT16 keyNum, const UINT8 *digest, const ECC_ECDSA_SIGN_t *sign, UINT8 *verifyResult)
{
	volatile Std_ReturnType result = E_OK;
	HSMAPI_CTX_t eccCtx;

	volatile UINT32 timeout = 0;
			

	do
	{
		result = HSM_EccEcdsaVerifyStart(&eccCtx, keyNum);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	do
	{
		result = HSM_EccEcdsaVerifyUpdate(&eccCtx, digest, sign);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			HSM_CancelJob(eccCtx.jobId);
			return result;
		}
	} while (result == HSM_E_BUSY);


	do
	{
		result = HSM_WaitResp(eccCtx.jobId);
		if (result != HSM_E_WAIT)
		{
			break;
		}
		timeout++;
	} while (timeout < WAIT_RESP_TIMEOUT);

	if (result != E_OK)
	{
		
		HSM_CancelJob(eccCtx.jobId);
		return result;
	}

	do
	{
		result = HSM_EccEcdsaVerifyFinish(&eccCtx, verifyResult);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			return result;
		}
	} while (result == HSM_E_BUSY);

	return result;
}

/******************************************************************************/
/*                               ECC ECDH-Key Exchange FUNC                   */
/******************************************************************************/
Std_ReturnType HSM_Ecdh(const UINT16 keyNum, const ECC_PUBLICKEY_t *pubkey, UINT8 *secretValue)
{
	volatile Std_ReturnType result = E_OK;
	HSMAPI_CTX_t eccCtx;

	volatile UINT32 timeout = 0;
					

	do
	{
		result = HSM_EccEcdhStart(&eccCtx, keyNum);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	do
	{
		result = HSM_EccEcdhUpdate(&eccCtx, pubkey);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			HSM_CancelJob(eccCtx.jobId);
			return result;
		}
	} while (result == HSM_E_BUSY);

	do
	{
		result = HSM_WaitResp(eccCtx.jobId);
		if (result != HSM_E_WAIT)
		{
			break;
		}
		timeout++;
	} while (timeout < WAIT_RESP_TIMEOUT);

	if (result != E_OK)
	{
		
		HSM_CancelJob(eccCtx.jobId);
		return result;
	}

	do
	{
		result = HSM_EccEcdhFinish(&eccCtx, secretValue);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
		return result;
		}
	} while (result == HSM_E_BUSY);

	return result;
}
