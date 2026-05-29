/******************************************************************************/
/*                              Header Include                                */
/******************************************************************************/
#include "Demo_Rng.h"
#include "Hsm_HostAPI.h"
#include "SecurityApp_Rng.h"
#include "HsmDrv_API.h"

/******************************************************************************/
/*                             Global veriables                               */
/******************************************************************************/
volatile UINT32 g_randValue = 1234u;
UINT32 s_rngByteLength = 16u;
extern HSM_ERROR_CODE g_ErrorCode;

/******************************************************************************/
/*                           TRNG DEMO CODE                                   */
/******************************************************************************/
Std_ReturnType trngTest_Simple(HSM_RNG_TestVector hsmRngTestVector)
{
	volatile Std_ReturnType result = E_OK;
	

	do
	{
		result = HSM_TrueRandomGenerate(hsmRngTestVector.randValue, hsmRngTestVector.len);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			break;
		}
	}
	while (result == HSM_E_BUSY);
		
	if(result != E_OK)
	{
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
			
	return result;
}

Std_ReturnType trngTest_RandomLength(void)
{
	UINT8 output[2048] = {0,};
	volatile Std_ReturnType result = E_OK;
	UINT32 maxTxLen = HSM_GetMaxTranSizeByte();
	UINT32 remainDataLen = s_rngByteLength;
	UINT32 txLen = 0, j =0;
	

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
			result = HSM_TrueRandomGenerate(&output[j], txLen);
			if((result != E_OK) && (result != HSM_E_BUSY))
			{
				break;
			}
		}
		while (result == HSM_E_BUSY);

		if(result == E_OK)
		{
			j += txLen;
			remainDataLen -= txLen;
		}
		else
		{
			g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
			break;
		}
	}

	if(result == E_OK)
	{
		g_randValue = (output[0]<<24u) | (output[1] << 16) | (output[2] << 8) | output[3];
		s_rngByteLength = (g_randValue % 2048) + 1u; 
	}
	else
	{
	}
			
	return result;
}

Std_ReturnType trngTest_allLength(void)
{
	UINT8 			output[2048] = {0,};
	Std_ReturnType 	result = E_OK;
	UINT32			i, trxMax;
	trxMax = HSM_GetMaxTranSizeByte();
	

	for(i=1; i<trxMax; i++)
	{
		result = HSM_TrueRandomGenerate(output, i);

		if(result != E_OK)
		{
		}
	}
			
	return result;
}


/******************************************************************************/
/*                           PRNG DEMO CODE                                   */
/******************************************************************************/
Std_ReturnType prngTest_Simple(HSM_RNG_TestVector hsmRngTestVector)
{
	volatile Std_ReturnType result = E_OK;
	

	do
	{
		result = HSM_PseudoRandomGenerate(hsmRngTestVector.randValue, hsmRngTestVector.len);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			break;
		}
	}
	while (result == HSM_E_BUSY);
		
	if(result != E_OK)
	{
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
			
	return result;
}

Std_ReturnType prngTest_RandomLength(void)
{
	UINT8 output[2048] = {0,};
	volatile Std_ReturnType result = E_OK;
	UINT32 maxTxLen = HSM_GetMaxTranSizeByte();
	UINT32 remainDataLen = s_rngByteLength;
	UINT32 txLen = 0, j =0;
	

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
			result = HSM_PseudoRandomGenerate(&output[j], txLen);
			if((result != E_OK) && (result != HSM_E_BUSY))
			{
				break;
			}
		}
		while (result == HSM_E_BUSY);

		if(result == E_OK)
		{
			j += txLen;
			remainDataLen -= txLen;
		}
		else
		{
			g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
			break;
		}
	}

	if(result == E_OK)
	{
		g_randValue = (output[0]<<24u) | (output[1] << 16) | (output[2] << 8) | output[3];
		s_rngByteLength = (g_randValue % 2048) + 1u; 
	}
	else
	{
	}
			
	return result;
}
