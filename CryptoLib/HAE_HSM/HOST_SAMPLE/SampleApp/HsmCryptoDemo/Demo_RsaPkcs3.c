/******************************************************************************/
/*                              Header Include                                */
/******************************************************************************/
#include "Demo_RsaPkcs3.h"

#include "Hsm_KeyTypes.h"
#include "CryptoService_RsaPkcs3.h"
#include "Hsm_HostAPI.h"
#include "HsmDrv_API.h"

/******************************************************************************/
/*                                 Global Veriable                            */
/******************************************************************************/
extern HSM_ERROR_CODE g_ErrorCode;

/******************************************************************************/
/*                             PKCS#3 DEMO CODE  - Key Generate               */
/******************************************************************************/
Std_ReturnType pkcs3DHKeypairGenTest_Simple(HSM_Rsa_Pkcs3_DiffieHellman_TestVector pkcs3DiffieHellmanTv)
{
	Std_ReturnType result;
	UINT32 i;
	UINT8 resultPublic[HAC_RSA_BYTES_SIZE];
	UINT8 resultPrivate[HAC_RSA_BYTES_SIZE];

	result = HSM_Pkcs3DHKeypairGenerate(pkcs3DiffieHellmanTv.xa, pkcs3DiffieHellmanTv.dh_base, pkcs3DiffieHellmanTv.dh_prime, resultPublic, resultPrivate);
	if(result == E_OK)
	{
		for (i = 0; i < HAC_RSA_BYTES_SIZE; i++)
		{
			if (resultPublic[i] != pkcs3DiffieHellmanTv.ya[i])
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
/*                             PKCS#3 DEMO CODE  - Shared Value Generate      */
/******************************************************************************/
Std_ReturnType pkcs3DHSharedValueGenTest_Simple(HSM_Rsa_Pkcs3_DiffieHellman_TestVector pkcs3DiffieHellmanTv)
{
	volatile Std_ReturnType result = E_OK;
	UINT32 i;
	UINT8 resultSecretValue1[HAC_RSA_BYTES_SIZE];
	UINT8 resultSecretValue2[HAC_RSA_BYTES_SIZE];

	result += HSM_Pkcs3DHSharedValueGenerate(pkcs3DiffieHellmanTv.ya, pkcs3DiffieHellmanTv.xb, pkcs3DiffieHellmanTv.dh_prime, resultSecretValue1);
	result += HSM_Pkcs3DHSharedValueGenerate(pkcs3DiffieHellmanTv.yb, pkcs3DiffieHellmanTv.xa, pkcs3DiffieHellmanTv.dh_prime, resultSecretValue2);
	if(result == E_OK)
	{
		for (i = 0; i < HAC_RSA_BYTES_SIZE; i++)
		{
			if (resultSecretValue1[i] != resultSecretValue2[i])
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
/*                  PKCS3 DiffieHellman - Keypair Generate FUNC               */
/******************************************************************************/
Std_ReturnType HSM_Pkcs3DHKeypairGenerate(const UINT8 *xa, const UINT8 *dh_base, const UINT8 *dh_prime, UINT8* public, UINT8 *private)
{
	volatile Std_ReturnType result = E_OK;
	HSMAPI_CTX_t pkcs3Ctx;

	volatile UINT32 timeout = 0;
	
	do
	{
		result = HSM_RsaPkcs3DHKeypairGenStart(&pkcs3Ctx);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	do
	{
		result = HSM_RsaPkcs3DHKeypairGenUpdate(&pkcs3Ctx, xa, dh_base, dh_prime);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			HSM_CancelJob(pkcs3Ctx.jobId);
			return result;
		}
	} while (result == HSM_E_BUSY);

	do
	{
		result = HSM_WaitResp(pkcs3Ctx.jobId);
		if (result != HSM_E_WAIT)
		{
			break;
		}
		timeout++;
	} while (timeout < WAIT_RESP_TIMEOUT);
	if (result != E_OK)
	{
		
		HSM_CancelJob(pkcs3Ctx.jobId);
		return result;
	}

	do
	{
		result = HSM_RsaPkcs3DHKeypairGenFinish(&pkcs3Ctx, public, private);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	} while (result == HSM_E_BUSY);

	return result;
}

/******************************************************************************/
/*               PKCS3 DiffieHellman - Shared Value Generate FUNC              */
/******************************************************************************/
Std_ReturnType HSM_Pkcs3DHSharedValueGenerate(const UINT8* y, const UINT8* x, const UINT8* dh_prime, UINT8* secretValue)
{
	volatile Std_ReturnType result = E_OK;
	HSMAPI_CTX_t pkcs3Ctx;

	volatile UINT32 timeout = 0;
	
	//Generate secretValue 1
	do
	{
		result = HSM_RsaPkcs3DHSharedValueGenStart(&pkcs3Ctx);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	}
	while (result == HSM_E_BUSY);

	do
	{
		result = HSM_RsaPkcs3DHSharedValueGenUpdate(&pkcs3Ctx, y, x, dh_prime);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			HSM_CancelJob(pkcs3Ctx.jobId);
			return result;
		}
	} while (result == HSM_E_BUSY);

	do
	{
		result = HSM_WaitResp(pkcs3Ctx.jobId);
		if (result != HSM_E_WAIT)
		{
			break;
		}
		timeout++;
	} while (timeout < WAIT_RESP_TIMEOUT);
	if (result != E_OK)
	{
		
		HSM_CancelJob(pkcs3Ctx.jobId);
		return result;
	}

	do
	{
		result = HSM_RsaPkcs3DHSharedValueGenFinish(&pkcs3Ctx, secretValue);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			return result;
		}
	} while (result == HSM_E_BUSY);

	return result;
}
