/******************************************************************************/
/*                              Header Include                                */
/******************************************************************************/
#include "Demo_Aes.h"

#include "CryptoService_Aes.h"
#include "Hsm_HostAPI.h"
#include "HsmDrv_API.h"

/******************************************************************************/
/*                                 Global Veriable                            */
/******************************************************************************/
extern HSM_ERROR_CODE g_ErrorCode;

/******************************************************************************/
/*                             AES DEMO CODE - Encryption                     */
/******************************************************************************/
Std_ReturnType HSM_AesEncCancel(const AES_MODE mode, const UINT16 keyIndex, const UINT8 *iv, const UINT32 dataLen, const UINT8 *plain, UINT8 *cipher);

Std_ReturnType aesEncTest_Simple(HSM_AES_TestVector hsmAesTestVector)
{
	volatile Std_ReturnType result = E_OK;
	UINT32 i;
	UINT8 output[2048] = {
		0,
	};
	
	result = HSM_AesEnc(hsmAesTestVector.mode, hsmAesTestVector.keyNum, hsmAesTestVector.iv, hsmAesTestVector.mLen, hsmAesTestVector.plain, output);
	if(result == E_OK)
	{
		for (i = 0; i < hsmAesTestVector.mLen; i++)
		{
			if (output[i] != hsmAesTestVector.cipher[i])
			{
				return E_NOT_OK;
			}
		}
	}
	else
	{
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	
	result = HSM_AesEncCancel(hsmAesTestVector.mode, hsmAesTestVector.keyNum, hsmAesTestVector.iv, hsmAesTestVector.mLen, hsmAesTestVector.plain, output);
	if(result == E_OK)
	{
		for (i = 0; i < hsmAesTestVector.mLen; i++)
		{
			if (output[i] != hsmAesTestVector.cipher[i])
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
/*                             AES DEMO CODE - Decryption                     */
/******************************************************************************/
Std_ReturnType aesDecTest_Simple(HSM_AES_TestVector hsmAesTestVector)
{
	volatile Std_ReturnType result = E_OK;
	UINT32 i;
	UINT8 output[2048] = {
		0,
	};

	result = HSM_AesDec(hsmAesTestVector.mode, hsmAesTestVector.keyNum, hsmAesTestVector.iv, hsmAesTestVector.mLen, hsmAesTestVector.cipher, output);
	if(result == E_OK)
	{
		for (i = 0; i < hsmAesTestVector.mLen; i++)
		{
			if (output[i] != hsmAesTestVector.plain[i])
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
/*                             AES DEMO CODE - CMAC                           */
/******************************************************************************/
Std_ReturnType aesCmacTest_Simple(HSM_AES_CMAC_TestVector aesCmacTv)
{
	volatile Std_ReturnType result = E_OK;
	UINT32 i;
	UINT8 resultCmac[HSM_AES128_CMAC_LEN] = { 0u, };

	result = HSM_AesCmacGenerate(aesCmacTv.keyNum, aesCmacTv.msg, aesCmacTv.mLen, resultCmac);
	if(result == E_OK)
	{
		for (i = 0; i < aesCmacTv.digestLen; i++)
		{
			if (resultCmac[i] != aesCmacTv.digest[i])
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
/*                             AES FUNC SAMPLE (ENCRYPTION)                   */
/******************************************************************************/
Std_ReturnType HSM_AesEnc(const AES_MODE mode, const UINT16 keyIndex, const UINT8 *iv, const UINT32 dataLen, const UINT8 *plain, UINT8 *cipher)
{
	volatile Std_ReturnType result = E_OK;
	HSMAPI_CTX_t aesCtx;

	UINT32 remainDataLen = dataLen;
	UINT32 txLen = 0;
	UINT32 i = 0;
	volatile UINT32 timeout = 0;
	UINT32 maxTxLen = HSM_GetMaxTranSizeByte();


	do
	{
		result = HSM_AesEncStart(&aesCtx, mode, keyIndex, iv);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	while (remainDataLen > 0)
	{
		if (remainDataLen > maxTxLen)
		{
			txLen = maxTxLen;
		}
		else
		{
			txLen = remainDataLen;
		}

		do
		{
			result = HSM_AesEncUpdate(&aesCtx, &plain[i], txLen);
			if((result != E_OK) && (result != HSM_E_BUSY))
			{
				
				HSM_CancelJob(aesCtx.jobId);
				return result;
			}
		}
		while (result == HSM_E_BUSY);

		do
		{
			result = HSM_WaitResp(aesCtx.jobId);
			if (result != HSM_E_WAIT)
			{
				break;
			}
			timeout++;
		} while (timeout < WAIT_RESP_TIMEOUT);
		
		if (result != E_OK)
		{
			
			HSM_CancelJob(aesCtx.jobId);
			return result;
		}

		if (HSM_ReadRxBuff(aesCtx.jobId, txLen, &cipher[i]) != E_OK)
		{
			
			return result;
		}

		remainDataLen -= txLen;
		i += txLen;
	}

	do
	{
		result = HSM_AesEncFinish(&aesCtx);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	return result;
}

Std_ReturnType HSM_AesEncCancel(const AES_MODE mode, const UINT16 keyIndex, const UINT8 *iv, const UINT32 dataLen, const UINT8 *plain, UINT8 *cipher)
{
	Std_ReturnType 	result = E_OK;
	HSMAPI_CTX_t 	aesCtx;

	UINT32 			remainDataLen = dataLen;
	UINT32 			txLen = 0;
	UINT32 			i = 0;
	volatile UINT32 timeout = 0;
	UINT32 			maxTxLen = HSM_GetMaxTranSizeByte();


	do
	{
		result = HSM_AesEncStart(&aesCtx, mode, keyIndex, iv);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	result = HSM_AesEncUpdate(&aesCtx, &plain[i], maxTxLen);
	if((result != E_OK) && (result != HSM_E_BUSY))
	{
		
		HSM_CancelJob(aesCtx.jobId);
		return result;
	}

	//job cancel
	do {
		result = HSM_CancelJob(aesCtx.jobId);
		if((result != HSM_E_BUSY) && (result != HSM_E_WAIT))
		{
			break;
		}

		timeout++;
	} while(timeout < WAIT_RESP_TIMEOUT);
	if(result == E_NOT_OK)
	{
		return result;
	}

	//restart AES service
	timeout = 0;
	do
	{
		result = HSM_AesEncStart(&aesCtx, mode, keyIndex, iv);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	while (remainDataLen > 0)
	{
		if (remainDataLen > maxTxLen)
		{
			txLen = maxTxLen;
		}
		else
		{
			txLen = remainDataLen;
		}

		do
		{
			result = HSM_AesEncUpdate(&aesCtx, &plain[i], txLen);
			if((result != E_OK) && (result != HSM_E_BUSY))
			{
				
				HSM_CancelJob(aesCtx.jobId);
				return result;
			}
		}
		while (result == HSM_E_BUSY);

		do
		{
			result = HSM_WaitResp(aesCtx.jobId);
			if (result != HSM_E_WAIT)
			{
				break;
			}
			timeout++;
		} while (timeout < WAIT_RESP_TIMEOUT);
		
		if (result != E_OK)
		{
			
			HSM_CancelJob(aesCtx.jobId);
			return result;
		}

		if (HSM_ReadRxBuff(aesCtx.jobId, txLen, &cipher[i]) != E_OK)
		{
			
			return result;
		}

		remainDataLen -= txLen;
		i += txLen;
	}

	do
	{
		result = HSM_AesEncFinish(&aesCtx);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	return result;
}

/******************************************************************************/
/*                             AES FUNC SAMPLE (DECRYPTION)                   */
/******************************************************************************/
Std_ReturnType HSM_AesDec(const AES_MODE mode, const UINT16 keyIndex, const UINT8 *iv, const UINT32 dataLen, const UINT8 *cipher, UINT8 *plain)
{
	volatile Std_ReturnType result = E_OK;
	HSMAPI_CTX_t aesCtx;

	UINT32 remainDataLen = dataLen;
	UINT32 txLen = 0;
	UINT32 i = 0;
	volatile UINT32 timeout = 0;
	UINT32 maxTxLen = HSM_GetMaxTranSizeByte();
	

	do
	{
		result = HSM_AesDecStart(&aesCtx, mode, keyIndex, iv);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	while (remainDataLen > 0)
	{
		if (remainDataLen > maxTxLen)
		{
			txLen = maxTxLen;
		}
		else
		{
			txLen = remainDataLen;
		}

		do
		{
			result = HSM_AesDecUpdate(&aesCtx, &cipher[i], txLen);
			if((result != E_OK) && (result != HSM_E_BUSY))
			{
				
				HSM_CancelJob(aesCtx.jobId);
				return result;
			}
		}
		while (result == HSM_E_BUSY);


		do
		{
			result = HSM_WaitResp(aesCtx.jobId);
			if (result != HSM_E_WAIT)
			{
				break;
			}
			timeout++;
		} while (timeout < WAIT_RESP_TIMEOUT);

		if (result != E_OK)
		{
			
			HSM_CancelJob(aesCtx.jobId);
			return result;
		}

		if (HSM_ReadRxBuff(aesCtx.jobId, txLen, &plain[i]) != E_OK)
		{
			
			return result;
		}

		remainDataLen -= txLen;
		i += txLen;
	}

	do
	{
		result = HSM_AesDecFinish(&aesCtx);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	return result;
}

/******************************************************************************/
/*                             AES FUNC SAMPLE (CMAC)                         */
/******************************************************************************/
Std_ReturnType HSM_AesCmacGenerate(const UINT16 keyIndex, const UINT8 *msg, const UINT32 mLen, UINT8 *cmac)
{
	volatile Std_ReturnType result = E_OK;
	HSMAPI_CTX_t aesCtx = {
		0,
	};

	UINT32 remainDataLen = mLen;
	UINT32 txLen = 0;
	UINT32 i = 0;
	volatile UINT32 timeout = 0;
	UINT32 maxTxLen = HSM_GetMaxTranSizeByte();
			

	do
	{
		result = HSM_AesCmacStart(&aesCtx, keyIndex, mLen);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	while (remainDataLen > 0)
	{
		if (remainDataLen > maxTxLen)
		{
			txLen = maxTxLen;
		}
		else
		{
			txLen = remainDataLen;
		}

		do
		{
			result = HSM_AesCmacUpdate(&aesCtx, &msg[i], txLen);
			if((result != E_OK) && (result != HSM_E_BUSY))
			{
				
				HSM_CancelJob(aesCtx.jobId);
				return result;
			}
		}
		while (result == HSM_E_BUSY);

		do
		{
			result = HSM_WaitResp(aesCtx.jobId);
			if (result != HSM_E_WAIT)
			{
				break;
			}
			timeout++;
		} while (timeout < WAIT_RESP_TIMEOUT);

		if (result != E_OK)
		{
			
			HSM_CancelJob(aesCtx.jobId);
			return result;
		}

		remainDataLen -= txLen;
		i += txLen;
	}

	do
	{
		result = HSM_AesCmacFinish(&aesCtx, cmac);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	return result;
}
