/******************************************************************************/
/*                              Header Include                                */
/******************************************************************************/
#include "Demo_Pbkdf2.h"

#include "CryptoService_Pbkdf2.h"
#include "Hsm_HostAPI.h"
#include "HsmDrv_API.h"

/******************************************************************************/
/*                                 Global Veriable                            */
/******************************************************************************/
extern HSM_ERROR_CODE g_ErrorCode;

/******************************************************************************/
/*                           PBKDF2 DEMO CODE                                 */
/******************************************************************************/
Std_ReturnType pbkdf2Test_Simple(Hmg_Pbkdf2_TestVector pbkdf2Tv)
{
	Std_ReturnType result;
	UINT32 i;
	UINT8 output[PBKDF2_MAX_OUTPUT_BUFFER_SIZE];

	result = HSM_Pbkdf2(pbkdf2Tv.keyNum, pbkdf2Tv.password, pbkdf2Tv.pLen, pbkdf2Tv.salt, pbkdf2Tv.sLen, pbkdf2Tv.cnt, pbkdf2Tv.dkLen, output);
	if(result == E_OK)
	{
		for (i = 0; i < pbkdf2Tv.dkLen; i++)
		{
			if (output[i] != pbkdf2Tv.dk[i])
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
/*                           PBKDF2 SAMPLE FUNCTION                           */
/******************************************************************************/
Std_ReturnType HSM_Pbkdf2(const UINT16 keyNum, const UINT8* password, const UINT32 pwLen, const UINT8* salt, const UINT32 sLen, const UINT32 cnt, const UINT32 dkLen, UINT8 *dk)
{
	volatile Std_ReturnType result = E_OK;
	HSMAPI_CTX_t pbkdf2Ctx;

	volatile UINT32 timeout = 0;
			

	do
	{
		result = HSM_Pbkdf2Start(&pbkdf2Ctx, keyNum);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	}
	while (result == HSM_E_BUSY);
	if (result != E_OK)
	{
		return result;
	}

	do
	{
		result = HSM_Pbkdf2Update(&pbkdf2Ctx, keyNum ,dkLen, password, pwLen, salt, sLen, cnt);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			HSM_CancelJob(pbkdf2Ctx.jobId);
			return result;
		}
	} while (result == HSM_E_BUSY);

	do
	{
		result = HSM_WaitResp(pbkdf2Ctx.jobId);
		if (result != HSM_E_WAIT)
		{
			break;
		}
		timeout++;
	} while (timeout < WAIT_RESP_TIMEOUT);
	if (result != E_OK)
	{
		
		HSM_CancelJob(pbkdf2Ctx.jobId);
		return result;
	}

	do
	{
		result = HSM_Pbkdf2Finish(&pbkdf2Ctx, dkLen, dk);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			
			return result;
		}
	} while (result == HSM_E_BUSY);

	return result;
}
