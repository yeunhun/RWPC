/******************************************************************************/
/*                              Header Include                                */
/******************************************************************************/
#include "Demo_Hash.h"

#include "Hsm_KeyTypes.h"
#include "CryptoService_Hash.h"
#include "Hsm_HostAPI.h"

#include "Util.h"
#include "HsmDrv_API.h"

/******************************************************************************/
/*                                 Global Veriable                            */
/******************************************************************************/
extern HSM_ERROR_CODE g_ErrorCode;

/******************************************************************************/
/*                             HASH DEMO CODE - SHA160                        */
/******************************************************************************/
Std_ReturnType HSM_Sha160Cancel(const UINT8 *msg, const UINT32 mLen, UINT8 *digest);
Std_ReturnType HSM_Sha256Cancel(const UINT8 *msg, const UINT32 mLen, UINT8 *digest);

Std_ReturnType sha160Test_Simple(HSM_Hash_TestVector shaTv)
{
	Std_ReturnType result;
	UINT32 i;
	UINT8 output[SHA160_DIGEST_SIZE] = {
		0,
	};
	
	result = HSM_Sha160(shaTv.msg, shaTv.mLen, output);
	if(result == E_OK)
	{
		for (i = 0; i < SHA160_DIGEST_SIZE; i++)
		{
			if (output[i] != shaTv.digest[i])
			{
				return E_NOT_OK;
			}
		}
	}
	else
	{
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	
	result = HSM_Sha160Cancel(shaTv.msg, shaTv.mLen, output);
	if(result == E_OK)
	{
		for (i = 0; i < SHA160_DIGEST_SIZE; i++)
		{
			if (output[i] != shaTv.digest[i])
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
/*                             HASH DEMO CODE - SHA256                        */
/******************************************************************************/
Std_ReturnType sha256Test_Simple(HSM_Hash_TestVector shaTv)
{
	Std_ReturnType result;
	UINT32 i;
	UINT8 output[SHA256_DIGEST_SIZE] = {
		0,
	};
	
	result = HSM_Sha256(shaTv.msg, shaTv.mLen, output);
	if(result == E_OK)
	{
		for (i = 0; i < SHA256_DIGEST_SIZE; i++)
		{
			if (output[i] != shaTv.digest[i])
			{
				return E_NOT_OK;
			}
		}
	}
	else
	{
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	
	result = HSM_Sha256Cancel(shaTv.msg, shaTv.mLen, output);
	if(result == E_OK)
	{
		for (i = 0; i < SHA256_DIGEST_SIZE; i++)
		{
			if (output[i] != shaTv.digest[i])
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
/*                             HASH DEMO CODE - Hashed-MAC_SHA256             */
/******************************************************************************/
Std_ReturnType hmacSha256Test_Simple(HSM_Hash_HMAC_TestVector hmacTv)
{
	Std_ReturnType result;
	UINT32 i;
	UINT8 output[SHA256_DIGEST_SIZE] = {
		0,
	};
	
	result = HSM_HmacSha256Gen(hmacTv.keyNum, hmacTv.msg, hmacTv.mLen, output);
	if(result == E_OK)
	{
		for (i = 0; i < SHA256_DIGEST_SIZE; i++)
		{
			if (output[i] != hmacTv.digest[i])
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
/*                                 HASH (SHA160) FUNC                         */
/******************************************************************************/
Std_ReturnType HSM_Sha160(const UINT8 *msg, const UINT32 mLen, UINT8 *digest)
{
	HSMAPI_CTX_t sha160Ctx;

	UINT32 i = 0;
	UINT32 remainDataLen = mLen;
	UINT32 txLen = 0;
	volatile Std_ReturnType result = E_OK;
	UINT32 maxTxLen = 1020; //Sha160 한번에 전송할 수 있는 최대 크기는 1020 byte
	volatile UINT32 timeout = 0;
		

	do
	{
		result = HSM_Sha160Start(&sha160Ctx);
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
			result = HSM_Sha160Update(&sha160Ctx, &msg[i], txLen);
			if((result != E_OK) && (result != HSM_E_BUSY))
			{
				
				HSM_CancelJob(sha160Ctx.jobId);
				return result;
			}
		} while (result == HSM_E_BUSY);

		do
		{
			result = HSM_WaitResp(sha160Ctx.jobId);
			if (result != HSM_E_WAIT)
			{
				break;
			}
			timeout++;
		} while (timeout < WAIT_RESP_TIMEOUT);

		if (result != E_OK)
		{
			
			HSM_CancelJob(sha160Ctx.jobId);
			return result;
		}

		remainDataLen -= txLen;
		i += txLen;
	}

	do
	{
		result = HSM_Sha160Finish(&sha160Ctx, digest);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	} while (result == HSM_E_BUSY);	


	return result;
}

Std_ReturnType HSM_Sha160Cancel(const UINT8 *msg, const UINT32 mLen, UINT8 *digest)
{
	HSMAPI_CTX_t sha160Ctx;

	UINT32 i = 0;
	UINT32 remainDataLen = mLen;
	UINT32 txLen = 0;
	volatile Std_ReturnType result = E_OK;
	UINT32 maxTxLen = 1020; //Sha160 한번에 전송할 수 있는 최대 크기는 1020 byte
	volatile UINT32 timeout = 0;
		
	do
	{
		result = HSM_Sha160Start(&sha160Ctx);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	result = HSM_Sha160Update(&sha160Ctx, &msg[i], maxTxLen);
	if((result != E_OK) && (result != HSM_E_BUSY))
	{
		
		HSM_CancelJob(sha160Ctx.jobId);
	}

	//job cancel
	do {
		result = HSM_CancelJob(sha160Ctx.jobId);
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

	//restart	
	timeout = 0;
	do
	{
		result = HSM_Sha160Start(&sha160Ctx);
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
			result = HSM_Sha160Update(&sha160Ctx, &msg[i], txLen);
			if((result != E_OK) && (result != HSM_E_BUSY))
			{
				
				HSM_CancelJob(sha160Ctx.jobId);
				return result;
			}
		} while (result == HSM_E_BUSY);

		do
		{
			result = HSM_WaitResp(sha160Ctx.jobId);
			if (result != HSM_E_WAIT)
			{
				break;
			}
			timeout++;
		} while (timeout < WAIT_RESP_TIMEOUT);

		if (result != E_OK)
		{
			
			HSM_CancelJob(sha160Ctx.jobId);
			return result;
		}

		remainDataLen -= txLen;
		i += txLen;
	}

	do
	{
		result = HSM_Sha160Finish(&sha160Ctx, digest);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	} while (result == HSM_E_BUSY);	


	return result;
}

/******************************************************************************/
/*                                 HASH (SHA256) FUNC                         */
/******************************************************************************/
Std_ReturnType HSM_Sha256(const UINT8 *msg, const UINT32 mLen, UINT8 *digest)
{
	volatile Std_ReturnType result = E_OK;
	HSMAPI_CTX_t sha256Ctx;

	UINT32 i = 0;
	UINT32 remainDataLen = mLen;
	UINT32 txLen = 0;
	UINT32 maxTxLen = 1020; //Sha256 한번에 전송할 수 있는 최대 크기는 1020 byte
	volatile UINT32 timeout = 0;


	do
	{
		result = HSM_Sha256Start(&sha256Ctx);
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
			result = HSM_Sha256Update(&sha256Ctx, &msg[i], txLen);
			if((result != E_OK) && (result != HSM_E_BUSY))
			{
				
				HSM_CancelJob(sha256Ctx.jobId);
				return result;
			}
		} while (result == HSM_E_BUSY);

		do
		{
			result = HSM_WaitResp(sha256Ctx.jobId);
			if (result != HSM_E_WAIT)
			{
				break;
			}
			timeout++;
		} while (timeout < WAIT_RESP_TIMEOUT);

		if (result != E_OK)
		{
			
			HSM_CancelJob(sha256Ctx.jobId);
			return result;
		}

		remainDataLen -= txLen;
		i += txLen;
	}

	do
	{
		result = HSM_Sha256Finish(&sha256Ctx, digest);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	} while (result == HSM_E_BUSY);	

	return result;
}

Std_ReturnType HSM_Sha256Cancel(const UINT8 *msg, const UINT32 mLen, UINT8 *digest)
{
	volatile Std_ReturnType result = E_OK;
	HSMAPI_CTX_t sha256Ctx;

	UINT32 i = 0;
	UINT32 remainDataLen = mLen;
	UINT32 txLen = 0;
	UINT32 maxTxLen = 1020; //Sha256 한번에 전송할 수 있는 최대 크기는 1020 byte
	volatile UINT32 timeout = 0;

	do
	{
		result = HSM_Sha256Start(&sha256Ctx);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	}
	while (result == HSM_E_BUSY);


	result = HSM_Sha256Update(&sha256Ctx, &msg[i], maxTxLen);
	if((result != E_OK) && (result != HSM_E_BUSY))
	{
		
		HSM_CancelJob(sha256Ctx.jobId);
	}

	//job cancel
	do {
		result = HSM_CancelJob(sha256Ctx.jobId);
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

	//restart
	timeout = 0;
	do
	{
		result = HSM_Sha256Start(&sha256Ctx);
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
			result = HSM_Sha256Update(&sha256Ctx, &msg[i], txLen);
			if((result != E_OK) && (result != HSM_E_BUSY))
			{
				
				HSM_CancelJob(sha256Ctx.jobId);
				return result;
			}
		} while (result == HSM_E_BUSY);

		do
		{
			result = HSM_WaitResp(sha256Ctx.jobId);
			if (result != HSM_E_WAIT)
			{
				break;
			}
			timeout++;
		} while (timeout < WAIT_RESP_TIMEOUT);

		if (result != E_OK)
		{
			
			HSM_CancelJob(sha256Ctx.jobId);
			return result;
		}

		remainDataLen -= txLen;
		i += txLen;
	}

	do
	{
		result = HSM_Sha256Finish(&sha256Ctx, digest);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	} while (result == HSM_E_BUSY);	

	return result;
}

/******************************************************************************/
/*                                 HMAC-SHA256 FUNC                           */
/******************************************************************************/
Std_ReturnType HSM_HmacSha256Gen(const UINT16 keyNum, const UINT8 *msg, const UINT32 mLen, UINT8 *digest)
{
	volatile Std_ReturnType result = E_OK;
	HSMAPI_CTX_t sha256Ctx;

	UINT32 i = 0;
	UINT32 remainDataLen = mLen;
	UINT32 txLen = 0;
	volatile UINT32 timeout = 0;
	UINT32 maxTxLen = 1020; //HMAC Sha256 한번에 전송할 수 있는 최대 크기는 1020 byte
		

	do
	{
		result = HSM_HmacSha256Start(&sha256Ctx, keyNum);
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
			result = HSM_HmacSha256Update(&sha256Ctx, &msg[i], txLen);
			if((result != E_OK) && (result != HSM_E_BUSY))
			{
				
				HSM_CancelJob(sha256Ctx.jobId);
				return result;
			}
		} while (result == HSM_E_BUSY);

		do
		{
			result = HSM_WaitResp(sha256Ctx.jobId);
			if (result != HSM_E_WAIT)
			{
				break;
			}
			timeout++;
		} while (timeout < WAIT_RESP_TIMEOUT);

		if (result != E_OK)
		{
			
			HSM_CancelJob(sha256Ctx.jobId);
			return result;
		}
		remainDataLen -= txLen;
		i += txLen;
	}

	do
	{
		result = HSM_HmacSha256Finish(&sha256Ctx, digest);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	} while (result == HSM_E_BUSY);

	return result;
}
