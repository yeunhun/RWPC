/******************************************************************************/
/*                              Header Include                                */
/******************************************************************************/
#include "Demo_RsaPkcs1.h"

#include "Hsm_KeyTypes.h"
#include "CryptoService_RsaPkcs1.h"
#include "Hsm_HostAPI.h"
#include "HsmDrv_API.h"

/******************************************************************************/
/*                                 Global Veriable                            */
/******************************************************************************/
extern HSM_ERROR_CODE g_ErrorCode;

/******************************************************************************/
/*                        PKCS#1 DEMO CODE  - V1.5 Sign Generate              */
/******************************************************************************/
Std_ReturnType pkcs1v15SignTest_Simple(HSM_Rsa_Pkcs1_v15_Sign_TestVector pkcs1v15SignTv)
{
	volatile Std_ReturnType result = E_OK;
	UINT8 resultSign[HAC_RSA_BYTES_SIZE];
	UINT32 i;

	result = HSM_Pkcs1v15SignGenerate(pkcs1v15SignTv.keyNum, pkcs1v15SignTv.digest, resultSign);
	if(result == E_OK)
	{
		for (i = 0; i < HAC_RSA_BYTES_SIZE; i++)
		{
			if (resultSign[i] != pkcs1v15SignTv.sign[i])
			{
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
/*                        PKCS#1 DEMO CODE  - V1.5 Sign Verify                */
/******************************************************************************/
Std_ReturnType pkcs1v15VerifyTest_Simple(HSM_Rsa_Pkcs1_v15_Sign_TestVector pkcs1v15SignTv)
{
	volatile Std_ReturnType result = E_OK;
	UINT8 verifyResult = HSM_VERIFY_FAILURE;

	result = HSM_Pkcs1v15SignVerify(pkcs1v15SignTv.keyNum, pkcs1v15SignTv.digest, pkcs1v15SignTv.sign, &verifyResult);
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
/*                        PKCS#1 DEMO CODE  - V1.5 Sign Sha160 Verify         */
/******************************************************************************/
Std_ReturnType pkcs1v15Sha160VerifyTest_Simple(HSM_Rsa_Pkcs1_v15_Sign_TestVector pkcs1v15SignTv)
{
	volatile Std_ReturnType result = E_OK;
	UINT8 verifyResult = HSM_VERIFY_FAILURE;

	result = HSM_Pkcs1v15Sha160SignVerify(pkcs1v15SignTv.keyNum, pkcs1v15SignTv.digest, pkcs1v15SignTv.sign, &verifyResult);
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
/*                        PKCS#1 DEMO CODE  - V1.5 Encryption                 */
/******************************************************************************/
Std_ReturnType pkcs1v15EncTest_Simple(HSM_Rsa_Pkcs1_v15_Enc_TestVector pkcs1v15EncTv)
{
	volatile Std_ReturnType result = E_OK;
	UINT8 cipher[HAC_RSA_BYTES_SIZE];
	UINT8 msg[HAC_RSA_BYTES_SIZE];
	UINT32 msgLen;
	UINT32 i;

	result = HSM_Pkcs1v15Enc(pkcs1v15EncTv.keyNum, pkcs1v15EncTv.msg, pkcs1v15EncTv.mLen, cipher);
	if(result == E_OK)
	{
		result = HSM_Pkcs1v15Dec(pkcs1v15EncTv.keyNum, cipher, msg, &msgLen);
		if(result == E_OK)
		{
			if(msgLen != pkcs1v15EncTv.mLen)
			{
				result = E_NOT_OK;
			}
			else
			{
				for (i = 0; i < pkcs1v15EncTv.mLen; i++)
				{
					if (msg[i] != pkcs1v15EncTv.msg[i])
					{
						result = E_NOT_OK;
						break;
					}
				}
			}
		}
	}

	if(result != E_OK)
	{
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}

	return result;
}

/******************************************************************************/
/*                        PKCS#1 DEMO CODE  - PSS Sign Generate              */
/******************************************************************************/
Std_ReturnType pkcs1PssSignTest_Simple(HSM_Rsa_Pkcs1_Pss_Sign_TestVector pkcsPssSignTv)
{
	volatile Std_ReturnType result = E_OK;
	UINT8 resultSign[HAC_RSA_BYTES_SIZE];
	UINT32 i;

	result = HSM_Pkcs1PssSignGenerate(pkcsPssSignTv.keyNum, pkcsPssSignTv.digest, pkcsPssSignTv.salt, pkcsPssSignTv.saltLen, resultSign);
	if(result == E_OK)
	{
		for (i = 0; i < HAC_RSA_BYTES_SIZE; i++)
		{
			if (resultSign[i] != pkcsPssSignTv.sign[i])
			{
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
/*                        PKCS#1 DEMO CODE  - PSS Sign Verify                */
/******************************************************************************/
Std_ReturnType pkcs1PssVerifyTest_Simple(HSM_Rsa_Pkcs1_Pss_Sign_TestVector pkcsPssSignTv)
{
	volatile Std_ReturnType result = E_OK;
	UINT8 verifyResult = HSM_VERIFY_FAILURE;

	result = HSM_Pkcs1PssSignVerify(pkcsPssSignTv.keyNum, pkcsPssSignTv.digest, pkcsPssSignTv.sign, pkcsPssSignTv.saltLen, &verifyResult);
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
/*                        PKCS#1 DEMO CODE  - OAEP Encryption                 */
/******************************************************************************/
Std_ReturnType pkcs1OaepEncTest_Simple(HSM_Rsa_Pkcs1_Oaep_Enc_TestVector pkcs1OaepEncTv)
{
	volatile Std_ReturnType result = E_OK;
	UINT8 cipher[HAC_RSA_BYTES_SIZE];
	UINT32 i;

	result = HSM_Pkcs1OaepEnc(pkcs1OaepEncTv.keyNum, pkcs1OaepEncTv.msg, pkcs1OaepEncTv.mLen, pkcs1OaepEncTv.seed, cipher);
	if(result == E_OK)
	{
		for (i = 0; i < HAC_RSA_BYTES_SIZE; i++)
		{
			if (cipher[i] != pkcs1OaepEncTv.cipher[i])
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
/*                        PKCS#1 DEMO CODE  - OAEP Decryption                 */
/******************************************************************************/
Std_ReturnType pkcs1OaepDecTest_Simple(HSM_Rsa_Pkcs1_Oaep_Enc_TestVector pkcs1OaepDecTv)
{
	volatile Std_ReturnType result = E_OK;
	UINT8 msg[HAC_RSA_BYTES_SIZE];
	UINT32 msgLen;
	UINT32 i;

	result = HSM_Pkcs1OaepDec(pkcs1OaepDecTv.keyNum, pkcs1OaepDecTv.cipher, msg,  &msgLen);
	if(result == E_OK)
	{
		if(msgLen != pkcs1OaepDecTv.mLen)
		{
			result = E_NOT_OK;
		}
		else
		{
			for (i = 0; i < pkcs1OaepDecTv.mLen; i++)
			{
				if (msg[i] != pkcs1OaepDecTv.msg[i])
				{
					result = E_NOT_OK;
					break;
				}
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
/*                             PKCS1 v1.5-SIGN FUNC                           */
/******************************************************************************/
Std_ReturnType HSM_Pkcs1v15SignGenerate(const UINT16 keyNum, const UINT8 *digest, UINT8 *sign)
{
	volatile Std_ReturnType result = E_OK;
	HSMAPI_CTX_t pkcs1v15Ctx;

	volatile UINT32 timeout = 0;
			

	do
	{
		result = HSM_RsaPkcs1v15SignStart(&pkcs1v15Ctx, keyNum);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	do
	{
		result = HSM_RsaPkcs1v15SignUpdate(&pkcs1v15Ctx, digest);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			HSM_CancelJob(pkcs1v15Ctx.jobId);
			return result;
		}
	} while (result == HSM_E_BUSY);

	do
	{
		result = HSM_WaitResp(pkcs1v15Ctx.jobId);
		if (result != HSM_E_WAIT)
		{
			break;
		}
		timeout++;
	} while (timeout < WAIT_RESP_TIMEOUT);
	if (result != E_OK)
	{
		
		HSM_CancelJob(pkcs1v15Ctx.jobId);
		return result;
	}

	do
	{
		result = HSM_RsaPkcs1v15SignFinish(&pkcs1v15Ctx, sign);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	} while (result == HSM_E_BUSY);

	return result;
}

/******************************************************************************/
/*                             PKCS1 v1.5-VERIFY FUNC                         */
/******************************************************************************/
Std_ReturnType HSM_Pkcs1v15SignVerify(const UINT16 keyNum, const UINT8 *digest, const UINT8* sign, UINT8 *verifyResult)
{
	volatile Std_ReturnType result = E_OK;
	HSMAPI_CTX_t pkcs1v15Ctx;

	volatile UINT32 timeout = 0;
		

	do
	{
		result = HSM_RsaPkcs1v15VerifyStart(&pkcs1v15Ctx, keyNum);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	do
	{
		result = HSM_RsaPkcs1v15VerifyUpdate(&pkcs1v15Ctx, digest, sign);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			HSM_CancelJob(pkcs1v15Ctx.jobId);
			return result;
		}
	} while (result == HSM_E_BUSY);

	do
	{
		result = HSM_WaitResp(pkcs1v15Ctx.jobId);
		if (result != HSM_E_WAIT)
		{
			break;
		}
		timeout++;
	} while (timeout < WAIT_RESP_TIMEOUT);

	if (result != E_OK)
	{
		HSM_CancelJob(pkcs1v15Ctx.jobId);
		return result;
	}

	do
	{
		result = HSM_RsaPkcs1v15VerifyFinish(&pkcs1v15Ctx, verifyResult);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			return result;
		}
	} while (result == HSM_E_BUSY);

	return result;
}

/******************************************************************************/
/*                      PKCS1 v1.5 SHA1 - VERIFY FUNC                         */
/******************************************************************************/
Std_ReturnType HSM_Pkcs1v15Sha160SignVerify(const UINT16 keyNum, const UINT8 *digest, const UINT8* sign, UINT8 *verifyResult)
{
	volatile Std_ReturnType result = E_OK;
	HSMAPI_CTX_t pkcs1v15Sha160Ctx;

	volatile UINT32 timeout = 0;
		
	do
	{
		result = HSM_RsaPkcs1v15VerifyStart(&pkcs1v15Sha160Ctx, keyNum);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	do
	{
		result = HSM_RsaPkcs1v15Sha160VerifyUpdate(&pkcs1v15Sha160Ctx, digest, sign);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			HSM_CancelJob(pkcs1v15Sha160Ctx.jobId);
			return result;
		}
	} while (result == HSM_E_BUSY);

	do
	{
		result = HSM_WaitResp(pkcs1v15Sha160Ctx.jobId);
		if (result != HSM_E_WAIT)
		{
			break;
		}
		timeout++;
	} while (timeout < WAIT_RESP_TIMEOUT);
	if (result != E_OK)
	{
		HSM_CancelJob(pkcs1v15Sha160Ctx.jobId);
		return result;
	}

	do
	{
		result = HSM_RsaPkcs1v15VerifyFinish(&pkcs1v15Sha160Ctx, verifyResult);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			return result;
		}
	} while (result == HSM_E_BUSY);

	return result;
}

/******************************************************************************/
/*                             PKCS1 v1.5-ENC FUNC                            */
/******************************************************************************/
Std_ReturnType HSM_Pkcs1v15Enc(const UINT16 keyNum, const UINT8 *msg, const UINT32 mLen, UINT8 *cipher)
{
	HSMAPI_CTX_t pkcs1v15Ctx;

	volatile Std_ReturnType result = E_OK;
	volatile UINT32 timeout = 0;
		

	do
	{
		result = HSM_RsaPkcs1v15EncStart(&pkcs1v15Ctx, keyNum);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	do
	{
		result = HSM_RsaPkcs1v15EncUpdate(&pkcs1v15Ctx, msg, mLen);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			HSM_CancelJob(pkcs1v15Ctx.jobId);
			return result;
		}
	} while (result == HSM_E_BUSY);

	do
	{
		result = HSM_WaitResp(pkcs1v15Ctx.jobId);
		if (result != HSM_E_WAIT)
		{
			break;
		}
		timeout++;
	} while (timeout < WAIT_RESP_TIMEOUT);
	if (result != E_OK)
	{
		HSM_CancelJob(pkcs1v15Ctx.jobId);
		return result;
	}

	do
	{
		result = HSM_RsaPkcs1v15EncFinish(&pkcs1v15Ctx, cipher);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			return result;
		}
	} while (result == HSM_E_BUSY);

	return result;
}

/******************************************************************************/
/*                               PKCS1 V1.5-DEC FUNC                          */
/******************************************************************************/
Std_ReturnType HSM_Pkcs1v15Dec(const UINT16 keyNum, const UINT8 *cipher, UINT8 *msg, UINT32 *mLen)
{
	volatile Std_ReturnType result = E_OK;
	HSMAPI_CTX_t pkcs1v15Ctx;

	volatile UINT32 timeout = 0;
		

	do
	{
		result = HSM_RsaPkcs1v15DecStart(&pkcs1v15Ctx, keyNum);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	do
	{
		result = HSM_RsaPkcs1v15DecUpdate(&pkcs1v15Ctx, cipher);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			HSM_CancelJob(pkcs1v15Ctx.jobId);
			return result;
		}
	} while (result == HSM_E_BUSY);

	do
	{
		result = HSM_WaitResp(pkcs1v15Ctx.jobId);
		if (result != HSM_E_WAIT)
		{
			break;
		}
		timeout++;
	} while (timeout < WAIT_RESP_TIMEOUT);
	if (result != E_OK)
	{
		HSM_CancelJob(pkcs1v15Ctx.jobId);
		return result;
	}

	do
	{
		result = HSM_RsaPkcs1v15DecFinish(&pkcs1v15Ctx, msg, mLen);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			return result;
		}
	} while (result == HSM_E_BUSY);

	return result;
}

/******************************************************************************/
/*                             PKCS1 PSS-SIGN FUNC                            */
/******************************************************************************/
Std_ReturnType HSM_Pkcs1PssSignGenerate(const UINT16 keyNum, const UINT8 *digest, const UINT8 *salt, const UINT8 saltLen, UINT8 *sign)
{
	volatile Std_ReturnType result = E_OK;
	HSMAPI_CTX_t pkcs1PssCtx;

	volatile UINT32 timeout = 0;
		

	do
	{
		result = HSM_RsaPkcs1PssSignStart(&pkcs1PssCtx, keyNum);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	do
	{
		result = HSM_RsaPkcs1PssSignUpdate(&pkcs1PssCtx, digest, salt, saltLen);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			HSM_CancelJob(pkcs1PssCtx.jobId);
			return result;
		}
	} while (result == HSM_E_BUSY);

	do
	{
		result = HSM_WaitResp(pkcs1PssCtx.jobId);
		if (result != HSM_E_WAIT)
		{
			break;
		}
		timeout++;
	} while (timeout < WAIT_RESP_TIMEOUT);
	if (result != E_OK)
	{
		HSM_CancelJob(pkcs1PssCtx.jobId);
		return result;
	}

	do
	{
		result = HSM_RsaPkcs1PssSignFinish(&pkcs1PssCtx, sign);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			return result;
		}
	} while (result == HSM_E_BUSY);

	return result;
}

/******************************************************************************/
/*                             PKCS1 PSS-VERIFY FUNC                          */
/******************************************************************************/
Std_ReturnType HSM_Pkcs1PssSignVerify(const UINT16 keyNum, const UINT8 *digest, const UINT8* sign, const UINT8 saltLen, UINT8 *verifyResult)
{
	volatile Std_ReturnType result = E_OK;
	HSMAPI_CTX_t pkcs1PssCtx;

	volatile UINT32 timeout = 0;
		

	do
	{
		result = HSM_RsaPkcs1PssVerifyStart(&pkcs1PssCtx, keyNum);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	do
	{
		result = HSM_RsaPkcs1PssVerifyUpdate(&pkcs1PssCtx, digest, sign, saltLen);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			HSM_CancelJob(pkcs1PssCtx.jobId);
			return result;
		}
	} while (result == HSM_E_BUSY);

	do
	{
		result = HSM_WaitResp(pkcs1PssCtx.jobId);
		if (result != HSM_E_WAIT)
		{
			break;
		}
		timeout++;
	} while (timeout < WAIT_RESP_TIMEOUT);
	if (result != E_OK)
	{
		HSM_CancelJob(pkcs1PssCtx.jobId);
		return result;
	}

	do
	{
		result = HSM_RsaPkcs1PssVerifyFinish(&pkcs1PssCtx, verifyResult);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			return result;
		}
	} while (result == HSM_E_BUSY);

	return result;
}

/******************************************************************************/
/*                               PKCS1 OAEP-ENC FUNC                          */
/******************************************************************************/
Std_ReturnType HSM_Pkcs1OaepEnc(const UINT16 keyNum, const UINT8 *msg, const UINT32 mLen, const UINT8 *seed, UINT8 *cipher)
{
	volatile Std_ReturnType result = E_OK;
	HSMAPI_CTX_t pkcs1oaepCtx;

	volatile UINT32 timeout = 0;
		

	do
	{
		result = HSM_RsaPkcs1oaepEncStart(&pkcs1oaepCtx, keyNum);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	do
	{
		result = HSM_RsaPkcs1oaepEncUpdate(&pkcs1oaepCtx, msg, mLen, 0, 0, seed);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			HSM_CancelJob(pkcs1oaepCtx.jobId);
			return result;
		}
	} while (result == HSM_E_BUSY);

	do
	{
		result = HSM_WaitResp(pkcs1oaepCtx.jobId);
		if (result != HSM_E_WAIT)
		{
			break;
		}
		timeout++;
	} while (timeout < WAIT_RESP_TIMEOUT);
	if (result != E_OK)
	{
		HSM_CancelJob(pkcs1oaepCtx.jobId);
		return result;
	}

	do
	{
		result = HSM_RsaPkcs1oaepEncFinish(&pkcs1oaepCtx, cipher);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			return result;
		}
	} while (result == HSM_E_BUSY);

	return result;
}

/******************************************************************************/
/*                             PKCS1 OAEP-DEC FUNC                            */
/******************************************************************************/
Std_ReturnType HSM_Pkcs1OaepDec(const UINT16 keyNum, const UINT8 *cipher, UINT8 *msg, UINT32 *mLen)
{
	volatile Std_ReturnType result = E_OK;
	HSMAPI_CTX_t pkcs1oaepCtx;

	volatile UINT32 timeout = 0;
		

	do
	{
		result = HSM_RsaPkcs1oaepDecStart(&pkcs1oaepCtx, keyNum);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	do
	{
		result = HSM_RsaPkcs1oaepDecUpdate(&pkcs1oaepCtx, cipher, 0, 0);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			HSM_CancelJob(pkcs1oaepCtx.jobId);
			return result;
		}
	} while (result == HSM_E_BUSY);

	do
	{
		result = HSM_WaitResp(pkcs1oaepCtx.jobId);
		if (result != HSM_E_WAIT)
		{
			break;
		}
		timeout++;
	} while (timeout < WAIT_RESP_TIMEOUT);
	if (result != E_OK)
	{
		HSM_CancelJob(pkcs1oaepCtx.jobId);
		return result;
	}

	do
	{
		result = HSM_RsaPkcs1oaepDecFinish(&pkcs1oaepCtx, msg, mLen);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			return result;
		}
	} while (result == HSM_E_BUSY);

	return result;
}
