/**
 * \file Demo_FeatureonDemand.c
 */

/******************************************************************************/
/*                    			Includes         		                      */
/******************************************************************************/
#include "TC_Def.h"
#include "Hsm_HostAPI.h"

#include "SecurityApp_FeatureOnDemand.h"
#include "SecurityApp_Rng.h"
#include "Demo_FeatureonDemand.h"
#include "Demo_KeyManagement.h"
#include "Demo_Aes.h"
#include "Demo_Hash.h"
#include "Demo_Pbkdf2.h"
#include "HsmDrv_API.h"

/******************************************************************************/
/*                    			Definitions      		                      */
/******************************************************************************/
/******************************************************************************/
/*                    			Global Variable  		                      */
/******************************************************************************/
HSM_FOD_ERR_STATE_t s_fodState;
UINT32 s_fodNumOfCert;
FoDCert s_fodCertList[FOD_NUMBER_OF_SET];
extern HSM_ERROR_CODE g_ErrorCode;

/******************************************************************************/
/*                         Func (Blocking Function)        			          */
/******************************************************************************/
Std_ReturnType HostTest_HSM_FeatureOnDemandCertStore(HSM_FOD_TestVector_t hsmFoDTv)
{
	Std_ReturnType result = E_OK;
	HSM_FOD_ERR_STATE_t fodState;
	HSMAPI_OBJ_t hsmApiObj;
	hsmApiObj.apiCtx.apiProcessMode = HSM_API_BLOCKING_MODE;


	do
	{
		result = HSM_FeatureOnDemandCertStore(&hsmFoDTv.fodCert, &hsmFoDTv.eccSignInfo, &fodState, &hsmApiObj);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			break;
		}
	}
	while (result == HSM_E_BUSY);

	if (result != E_OK)
	{
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}

	s_fodState = fodState;
	return result;
}

Std_ReturnType HostTest_HSM_FeatureOnDemandCertStore_Rev1(HSM_FOD_TestVector_t hsmFoDTv)
{
	Std_ReturnType result = E_OK;
	HSM_FOD_ERR_STATE_t fodState;
	HSMAPI_OBJ_t hsmApiObj;
	hsmApiObj.apiCtx.apiProcessMode = HSM_API_BLOCKING_MODE;

	do
	{
		result = HSM_FeatureOnDemandCertStore_Rev1(&hsmFoDTv.fodCert, &hsmFoDTv.eccSignInfo, hsmFoDTv.UserFV, &fodState, &hsmApiObj);
	}
	while (result == HSM_E_BUSY);
	if (result != E_OK)
	{
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}

	s_fodState = fodState;
	return result;
}

Std_ReturnType HostTest_HSM_FeatureOnDemandCertDelete(HSM_FOD_TestVector_t hsmFoDTv)
{
	Std_ReturnType result = E_OK;
	HSM_FOD_ERR_STATE_t fodState;
	HSMAPI_OBJ_t hsmApiObj;
	hsmApiObj.apiCtx.apiProcessMode = HSM_API_BLOCKING_MODE;


	do
	{
		result = HSM_FeatureOnDemandCertDelete(&hsmFoDTv.fodCert, &hsmFoDTv.eccSignInfo, &fodState, &hsmApiObj);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			break;
		}
	}
	while (result == HSM_E_BUSY);

	if (result != E_OK)
	{
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}

	s_fodState = fodState;
	return result;
}

Std_ReturnType HostTest_HSM_FeatureOnDemandCertDelete_Rev1(HSM_FOD_TestVector_t hsmFoDTv)
{
	Std_ReturnType result = E_OK;
	HSM_FOD_ERR_STATE_t fodState;
	HSMAPI_OBJ_t hsmApiObj;
	hsmApiObj.apiCtx.apiProcessMode = HSM_API_BLOCKING_MODE;

	do
	{
		result = HSM_FeatureOnDemandCertDelete_Rev1(&hsmFoDTv.fodCert, &hsmFoDTv.eccSignInfo, hsmFoDTv.UserFV, &fodState, &hsmApiObj);
	}
	while (result == HSM_E_BUSY);
	if (result != E_OK)
	{
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}

	s_fodState = fodState;
	return result;
}

Std_ReturnType HostTest_HSM_FeatureOnDemandGetCertList(void)
{
	Std_ReturnType result = E_OK;
	HSM_FOD_CERT_OUTPUT_t fodInfo;
	HSMAPI_OBJ_t hsmApiObj;
	hsmApiObj.apiCtx.apiProcessMode = HSM_API_BLOCKING_MODE;


	do
	{
		result = HSM_FeatureOnDemandGetCertList(&fodInfo, &hsmApiObj);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			break;
		}
	}
	while (result == HSM_E_BUSY);

	if (result != E_OK)
	{
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	else
	{
		Hae_Memcpy(s_fodCertList, fodInfo.fodCertList, sizeof(FoDCert) * FOD_NUMBER_OF_SET);
		s_fodNumOfCert = fodInfo.numOfFodCert;
	}

	s_fodState = fodInfo.fodErrState;
	return result;
}

/******************************************************************************/
/*                        Func (Non-Blocking Function)       			      */
/******************************************************************************/
Std_ReturnType waitHsmResp(HSMAPI_OBJ_t *hsmApiObj)
{
	Std_ReturnType result = E_OK;
	volatile UINT32 timeout = 0;
	do
	{
		result = HSM_ApiHandler(hsmApiObj);
		if (result != HSM_E_WAIT)
		{
			break;
		}
	} while (timeout < WAIT_RESP_TIMEOUT);

	if (result != E_OK)
	{
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}


Std_ReturnType HostTest_HSM_FeatureOnDemandCertStore_NBMode(HSM_FOD_TestVector_t hsmFoDTv)
{
	Std_ReturnType result = E_OK;
	HSM_FOD_ERR_STATE_t fodState;
	HSMAPI_OBJ_t hsmApiObj;
	hsmApiObj.apiCtx.apiProcessMode = HSM_API_NON_BLOCKING_MODE;

	do
	{
		result = HSM_FeatureOnDemandCertStore(&hsmFoDTv.fodCert, &hsmFoDTv.eccSignInfo, &fodState, &hsmApiObj);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			break;
		}
	}
	while (result == HSM_E_BUSY);
	
	result = waitHsmResp(&hsmApiObj);
	if(result == E_OK)
	{
		s_fodState = fodState;
	}

	return result;
}

Std_ReturnType HostTest_HSM_FeatureOnDemandCertStore_Rev1_NBMode(HSM_FOD_TestVector_t hsmFoDTv)
{
	Std_ReturnType result = E_OK;
	HSM_FOD_ERR_STATE_t fodState;
	HSMAPI_OBJ_t hsmApiObj;
	hsmApiObj.apiCtx.apiProcessMode = HSM_API_NON_BLOCKING_MODE;

	do
	{
		result = HSM_FeatureOnDemandCertStore_Rev1(&hsmFoDTv.fodCert, &hsmFoDTv.eccSignInfo, hsmFoDTv.UserFV, &fodState, &hsmApiObj);
	}
	while (result == HSM_E_BUSY);
	
	result = waitHsmResp(&hsmApiObj);
	if(result == E_OK)
	{
		s_fodState = fodState;
	}

	return result;
}

Std_ReturnType HostTest_HSM_FeatureOnDemandCertDelete_NBMode(HSM_FOD_TestVector_t hsmFoDTv)
{
	Std_ReturnType result = E_OK;
	HSM_FOD_ERR_STATE_t fodState;
	HSMAPI_OBJ_t hsmApiObj;
	hsmApiObj.apiCtx.apiProcessMode = HSM_API_NON_BLOCKING_MODE;

	do
	{
		result = HSM_FeatureOnDemandCertDelete(&hsmFoDTv.fodCert, &hsmFoDTv.eccSignInfo, &fodState, &hsmApiObj);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			break;
		}
	}
	while (result == HSM_E_BUSY);

	result = waitHsmResp(&hsmApiObj);
	if(result == E_OK)
	{
		s_fodState = fodState;
	}

	return result;
}

Std_ReturnType HostTest_HSM_FeatureOnDemandCertDelete_Rev1_NBMode(HSM_FOD_TestVector_t hsmFoDTv)
{
	Std_ReturnType result = E_OK;
	HSM_FOD_ERR_STATE_t fodState;
	HSMAPI_OBJ_t hsmApiObj;
	hsmApiObj.apiCtx.apiProcessMode = HSM_API_NON_BLOCKING_MODE;

	do
	{
		result = HSM_FeatureOnDemandCertDelete_Rev1(&hsmFoDTv.fodCert, &hsmFoDTv.eccSignInfo, hsmFoDTv.UserFV, &fodState, &hsmApiObj);
	}
	while (result == HSM_E_BUSY);

	result = waitHsmResp(&hsmApiObj);
	if(result == E_OK)
	{
		s_fodState = fodState;
	}

	return result;
}

Std_ReturnType HostTest_HSM_FeatureOnDemandGetCertList_NBMode(void)
{
	Std_ReturnType result = E_OK;
	HSM_FOD_CERT_OUTPUT_t fodInfo;
	HSMAPI_OBJ_t hsmApiObj;
	hsmApiObj.apiCtx.apiProcessMode = HSM_API_NON_BLOCKING_MODE;

	do
	{
		result = HSM_FeatureOnDemandGetCertList(&fodInfo, &hsmApiObj);
		if((result != E_OK) && (result != HSM_E_BUSY))
		{
			break;
		}
	}
	while (result == HSM_E_BUSY);

	result = waitHsmResp(&hsmApiObj);
	if(result == E_OK)
	{
		Hae_Memcpy(s_fodCertList, fodInfo.fodCertList, sizeof(FoDCert) * FOD_NUMBER_OF_SET);
		s_fodNumOfCert = fodInfo.numOfFodCert;
		s_fodState = fodInfo.fodErrState;
	}

	return result;
}

/******************************************************************************/
/*                                   UserFV          		                  */
/******************************************************************************/
Std_ReturnType HostTest_HSM_FeatureOnDemandUserFVStoreRead(HSM_FOD_TestVector_t hsmFoDTv)
{
	Std_ReturnType result;
    UINT32 n, i;
    HSM_FOD_USERFV_t fodUserFVStore;
    HSM_FOD_USERFV_t fodUserFVRead;
    HSMAPI_OBJ_t apiObj;
	apiObj.apiCtx.apiProcessMode = HSM_API_BLOCKING_MODE;

    /* HostTest_HSM_FeatureOnDemandCertStore_Rev1 is just called to set the initial UserFV for test purpose */
    result = HostTest_HSM_FeatureOnDemandCertStore_Rev1(hsmFoDTv);
    if(result == E_OK)
    {
        Hae_Memcpy(fodUserFVStore.UserFV, hsmFoDTv.UserFV, FOD_CERT_FV_LEN);
        for(n = 0; n < 8; n++)
        {
            do {
                /* Store UserFV */
                result = HSM_FeatureOnDemandUserFVStore(&fodUserFVStore, &apiObj);
            } while (result == HSM_E_BUSY);
            if(result == E_OK)
            {
                do {
                    /* Read UserFV */
                    result = HSM_FeatureOnDemandUserFVRead(&fodUserFVRead, &apiObj);
                } while (result == HSM_E_BUSY);
                if(result == E_OK)
                {
                    /* Check Validation */
                    for(i = 0; i < FOD_CERT_FV_LEN; i++)
                    {
                        if(fodUserFVStore.UserFV[i] != fodUserFVRead.UserFV[i])
                        {
                            result = E_NOT_OK;
                            break;
                        }
                    }
                }
            }

            if (result == E_OK)
            {
                /* Change UserFV to be saved */
                for(i = 0; i < FOD_CERT_FV_LEN; i++)
                {
                    fodUserFVStore.UserFV[i] = (UINT8)(fodUserFVStore.UserFV[i] & ~((UINT8)1 << n));
                }
            }
            else
            {
                break;
            }
        }

        if (result != E_OK)
        {
            g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
        }
    }
    else
    {
        g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
    }

	return result;
}

Std_ReturnType HostTest_HSM_FeatureOnDemandUserFVStore_Fixed(HSM_FOD_TestVector_t hsmFoDTv)
{
	Std_ReturnType result;
	HSM_FOD_USERFV_t fodUserFV = {{0xEF, 0xCD, 0xAB, 0x89}, 0};
    HSMAPI_OBJ_t apiObj;
	apiObj.apiCtx.apiProcessMode = HSM_API_BLOCKING_MODE;

    /* HostTest_HSM_FeatureOnDemandCertStore_Rev1 is just called to set the initial UserFV for test purpose */
    result = HostTest_HSM_FeatureOnDemandCertStore_Rev1(hsmFoDTv);
    if(result == E_OK)
    {
        do {
            /* Store UserFV */
            result = HSM_FeatureOnDemandUserFVStore(&fodUserFV, &apiObj);
        } while (result == HSM_E_BUSY);
        if (result != E_OK)
        {
            g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
        }
    }
    else
    {
        g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
    }

	return result;
}

Std_ReturnType HostTest_HSM_FeatureOnDemandUserFVRead_Fixed(void)
{
	Std_ReturnType result;
    UINT32 i;
	UINT8 UserFVStore[FOD_CERT_FV_LEN] = {0xEF, 0xCD, 0xAB, 0x89};
    HSM_FOD_USERFV_t fodUserFV;
    HSMAPI_OBJ_t apiObj;
	apiObj.apiCtx.apiProcessMode = HSM_API_BLOCKING_MODE;

    do {
        /* Read UserFV */
        result = HSM_FeatureOnDemandUserFVRead(&fodUserFV, &apiObj);
    } while (result == HSM_E_BUSY);
    if (result != E_OK)
	{
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}

    if(result == E_OK)
    {
        /* Check Validation */
        for(i = 0; i < FOD_CERT_FV_LEN; i++)
        {
            if(UserFVStore[i] != fodUserFV.UserFV[i])
            {
                result = E_NOT_OK;
                break;
            }
        }
    }

	return result;
}

Std_ReturnType HostTest_HSM_FeatureOnDemandUserFVStore_illegalFeature(void)
{
	Std_ReturnType result;
    HSM_FOD_USERFV_t fodUserFV;
    HSMAPI_OBJ_t apiObj;
	apiObj.apiCtx.apiProcessMode = HSM_API_BLOCKING_MODE;

    Hae_Memset(&fodUserFV, 0, (UINT32)sizeof(HSM_FOD_USERFV_t));

    do {
        result = HSM_FeatureOnDemandUserFVStore(&fodUserFV, &apiObj);
    } while (result == HSM_E_BUSY);
    if (result == E_OK)
    {
        /* Activate illegal Feature and Try to Store */
        fodUserFV.UserFV[1] = 0x02;
        
        do {
            /* Store UserFV */
            result = HSM_FeatureOnDemandUserFVStore(&fodUserFV, &apiObj);
        } while (result == HSM_E_BUSY);
        if (result != E_OK)
        {
            /* It is the expected return value */
            result = E_OK;
        }
        else
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

Std_ReturnType HostTest_HSM_FeatureOnDemandUserFVStoreRead_NBMode(HSM_FOD_TestVector_t hsmFoDTv)
{
	Std_ReturnType result;
    volatile UINT32 timeout = 0;
    UINT32 n, i;
    HSM_FOD_USERFV_t fodUserFVStore;
    HSM_FOD_USERFV_t fodUserFVRead;
    HSMAPI_OBJ_t apiObj;
	apiObj.apiCtx.apiProcessMode = HSM_API_NON_BLOCKING_MODE;

    /* HostTest_HSM_FeatureOnDemandCertStore_Rev1 is just called to set the initial UserFV for test purpose */
    result = HostTest_HSM_FeatureOnDemandCertStore_Rev1(hsmFoDTv);
    if(result == E_OK)
    {
        Hae_Memcpy(fodUserFVStore.UserFV, hsmFoDTv.UserFV, FOD_CERT_FV_LEN);
        for(n = 0; n < 8; n++)
        {
            do {
                /* Store UserFV */
                result = HSM_FeatureOnDemandUserFVStore(&fodUserFVStore, &apiObj);
            } while (result == HSM_E_BUSY);

            do {
                result = HSM_ApiHandler(&apiObj);
                if (result != HSM_E_WAIT)
                {
                    break;
                }
            } while (timeout < WAIT_RESP_TIMEOUT);

            if (result == E_OK)
            {
                if(fodUserFVStore.errState != HSM_FOD_SUCCESS)
                {
                    result = E_NOT_OK;
                }
            }

            if(result == E_OK)
            {
                do {
                    /* Read UserFV */
                    result = HSM_FeatureOnDemandUserFVRead(&fodUserFVRead, &apiObj);
                } while (result == HSM_E_BUSY);

                do {
                    result = HSM_ApiHandler(&apiObj);
                    if (result != HSM_E_WAIT)
                    {
                        break;
                    }
                } while (timeout < WAIT_RESP_TIMEOUT);

                if (result == E_OK)
                {
                    if(fodUserFVRead.errState != HSM_FOD_SUCCESS)
                    {
                        result = E_NOT_OK;
                    }
                }

                if(result == E_OK)
                {
                    /* Check Validation */
                    for(i = 0; i < FOD_CERT_FV_LEN; i++)
                    {
                        if(fodUserFVStore.UserFV[i] != fodUserFVRead.UserFV[i])
                        {
                            result = E_NOT_OK;
                            break;
                        }
                    }
                }
            }

            if (result == E_OK)
            {
                /* Change UserFV to be saved */
                for(i = 0; i < FOD_CERT_FV_LEN; i++)
                {
                    fodUserFVStore.UserFV[i] = (UINT8)(fodUserFVStore.UserFV[i] & ~((UINT8)1 << n));
                }
            }
            else
            {
                break;
            }
        }

        if (result != E_OK)
        {
            g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
        }
    }
    else
    {
        g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
    }

	return result;
}

/******************************************************************************/
/*                                   Test Case        		                  */
/******************************************************************************/
#include "Demo_Hash.h"
#include "Demo_Ecc.h"

FoDCert s_PlainFoDCertSample_1 = {
/* version  	*/	{0x01},
/* serialNumber */	{0x00, 0x00, 0x00, 0x01},
/* tag 			*/	{0x01,},
/* vin 			*/	{0x41, 0x4B, 0x4B, 0x4D, 0x48, 0x45, 0x4D, 0x34, 0x32, 0x41, 0x50, 0x58, 0x41, 0x31, 0x32, 0x33, 0x34},
/* eId 			*/	{0x35, 0x36},
/* fv 			*/	{0x00, 0x00, 0xC4, 0x04},
/* sP 			*/	{0x06, 0x8C, 0xB6, 0x4D, 0xD8, 0xB3, 0xE9, 0xB9, 0xFA, 0x99, 0xFD, 0xF7, 0xFD, 0x43, 0x48, 0x4B},
/* issuer 		*/	{0x4D},
/* orderId 		*/	{0x43, 0x32, 0x30, 0x2D},
/* issuedDate 	*/	{0x42, 0x4C, 0x48, 0x2D, 0x30, 0x30, 0x30, 0x30},
/* effectiveDate*/	{0x30, 0x30, 0x30, 0x30, 0x35, 0x43, 0x35, 0x34},
/* expiredDate 	*/	{0x43, 0x46, 0x44, 0x46, 0x35, 0x43, 0x35, 0x34},
/* reserved 	*/	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
};

FoDCert s_PlainFoDCertSample_2 = {
/* version  	*/	{0x01},
/* serialNumber */	{0x00, 0x00, 0x00, 0x01},
/* tag 			*/	{0x02,},
/* vin 			*/	{0x41, 0x4B, 0x4B, 0x4D, 0x48, 0x45, 0x4D, 0x34, 0x32, 0x41, 0x50, 0x58, 0x41, 0x31, 0x32, 0x33, 0x34},
/* eId 			*/	{0x35, 0x36},
/* fv 			*/	{0x00, 0x00, 0xC4, 0x04},
/* sP 			*/	{0x06, 0x8C, 0xB6, 0x4D, 0xD8, 0xB3, 0xE9, 0xB9, 0xFA, 0x99, 0xFD, 0xF7, 0xFD, 0x43, 0x48, 0x4B},
/* issuer 		*/	{0x4D},
/* orderId 		*/	{0x43, 0x32, 0x30, 0x2D},
/* issuedDate 	*/	{0x42, 0x4C, 0x48, 0x2D, 0x30, 0x30, 0x30, 0x30},
/* effectiveDate*/	{0x30, 0x30, 0x30, 0x30, 0x35, 0x43, 0x35, 0x34},
/* expiredDate 	*/	{0x43, 0x46, 0x44, 0x46, 0x35, 0x43, 0x35, 0x34},
/* reserved 	*/	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
};

Std_ReturnType Demo_EccMakeSign(const UINT8 *msg, const UINT32 msgLen, const UINT32 signKeyNum, UINT8 *sign);

Std_ReturnType Demo_FoDTest(void)
{
	Std_ReturnType result = E_OK;
	UINT32 keyIndex = 401u;
	UINT32 i;
	UINT8 tempSN;

	FoDCert fodCert;
	HSM_SIGN_t signInfo;
	HSM_FOD_CERT_OUTPUT_t fodInfo;

	HSMAPI_OBJ_t hsmApiObj;
	hsmApiObj.apiCtx.apiProcessMode = HSM_API_BLOCKING_MODE;

	/* FoD TestCase #1 - Store FoDCert SN 0x00000001*/
	/* Result : SUCCESS (FodList is stored)*/
	// 1. Set Cert Data
	Hae_Memcpy((void *)&fodCert, &s_PlainFoDCertSample_1, sizeof(FoDCert));
	// 2. Signature
	result += Demo_EccMakeSign((UINT8 *)&fodCert, sizeof(FoDCert), keyIndex, signInfo.sign);
	signInfo.signKeyNum = keyIndex;
	// 3. Store FoDCert to HSM
	result += HSM_FeatureOnDemandCertStore(&fodCert, &signInfo, &s_fodState, &hsmApiObj);
	// 4. Confirm FoDCert Data
	result += HSM_FeatureOnDemandGetCertList(&fodInfo, &hsmApiObj);
	if(result != E_OK)
	{
		s_fodState = fodInfo.fodErrState;
		while(1);
	}
	else
	{
		Hae_Memcpy(s_fodCertList, fodInfo.fodCertList, sizeof(FoDCert) * FOD_NUMBER_OF_SET);
		s_fodNumOfCert = fodInfo.numOfFodCert;
		s_fodState = fodInfo.fodErrState;
	}

	/* FoD TestCase #2 - Delete FoDCert SN 0x00000001*/
	/* Result : SUCCESS (FodList is empty)*/
	// 1. Set Cert Data
	Hae_Memcpy((void *)&fodCert, &s_PlainFoDCertSample_2, sizeof(FoDCert));
	// 2. Signature
	result += Demo_EccMakeSign((UINT8 *)&fodCert, sizeof(FoDCert), keyIndex, signInfo.sign);
	signInfo.signKeyNum = keyIndex;
	// 3. Delete FoDCert to HSM
	result += HSM_FeatureOnDemandCertDelete(&fodCert, &signInfo, &s_fodState, &hsmApiObj);
	// 4. Confirm FoDCert Data
	result += HSM_FeatureOnDemandGetCertList(&fodInfo, &hsmApiObj);
	if(result != E_OK)
	{
		s_fodState = fodInfo.fodErrState;
		while(1);
	}
	else
	{
		Hae_Memcpy(s_fodCertList, fodInfo.fodCertList, sizeof(FoDCert) * FOD_NUMBER_OF_SET);
		s_fodNumOfCert = fodInfo.numOfFodCert;
		s_fodState = fodInfo.fodErrState;
	}

	/* FoD TestCase #3 - Store FoDCert SN 0x01020304 (aSIMS Key #1)*/
	/* Result : SUCCESS (FodList is stored)*/
	// 1. Store FoDCert to HSM
	result += HSM_FeatureOnDemandCertStore(&g_HsmFoDTv3.fodCert, &g_HsmFoDTv3.eccSignInfo, &s_fodState, &hsmApiObj);
	// 2. Confirm FoDCert Data
	result += HSM_FeatureOnDemandGetCertList(&fodInfo, &hsmApiObj);
	if(result != E_OK)
	{
		while(1);
	}
	else
	{
		Hae_Memcpy(s_fodCertList, fodInfo.fodCertList, sizeof(FoDCert) * FOD_NUMBER_OF_SET);
		s_fodNumOfCert = fodInfo.numOfFodCert;
		s_fodState = fodInfo.fodErrState;
	}

	/* FoD TestCase #4 - Delete FoDCert SN 0x01020304 (aSIMS Key #1)*/
	/* Result : SUCCESS (FodList is empty)*/
	// 1. Store FoDCert to HSM
	result += HSM_FeatureOnDemandCertDelete(&g_HsmFoDTv4.fodCert, &g_HsmFoDTv4.eccSignInfo, &s_fodState, &hsmApiObj);
	// 2. Confirm FoDCert Data
	result += HSM_FeatureOnDemandGetCertList(&fodInfo, &hsmApiObj);
	if(result != E_OK)
	{
		s_fodState = fodInfo.fodErrState;
		while(1);
	}

	/* FoD TestCase #5 - Store FoD Certificate up to the maximum size*/
	/* Result : SUCCESS (FodList is fulled)*/
	tempSN = s_fodCertList[s_fodNumOfCert-1].serialNumber[2];
	for(i=s_fodNumOfCert; i<10; i++)
	{
		fodCert.serialNumber[2] = ++tempSN;
		// 2. Signature
		result += Demo_EccMakeSign((UINT8 *)&fodCert, sizeof(FoDCert), keyIndex, signInfo.sign);
		signInfo.signKeyNum = keyIndex;
		// 3. Store FoDCert to HSM
		result += HSM_FeatureOnDemandCertStore(&fodCert, &signInfo, &s_fodState, &hsmApiObj);
		// 4. Confirm FoDCert Data
		result += HSM_FeatureOnDemandGetCertList(&fodInfo, &hsmApiObj);
		if(result != E_OK)
		{
			s_fodState = fodInfo.fodErrState;
		while(1);
		}
		else
		{
			Hae_Memcpy(s_fodCertList, fodInfo.fodCertList, sizeof(FoDCert) * FOD_NUMBER_OF_SET);
			s_fodNumOfCert = fodInfo.numOfFodCert;
			s_fodState = fodInfo.fodErrState;
		}
	}

	return result;
}

Std_ReturnType Demo_EccMakeSign(const UINT8 *msg, const UINT32 msgLen, const UINT32 signKeyNum, UINT8 *sign)
{
	Std_ReturnType result = E_OK;
	UINT8 digest[ECC_BYTES_SIZE] = {0,};
	UINT8 secret[ECC_BYTES_SIZE] = {0,};

	result += HSM_PseudoRandomGenerate(secret, ECC_BYTES_SIZE);
	result += HSM_Sha256(msg, msgLen, digest);
	result += HSM_EcdsaSign((UINT16)signKeyNum, digest, secret, (ECC_ECDSA_SIGN_t *)sign);
	return result;
}


/******************************************************************************/
/*                                   Test NB Case     		                  */
/******************************************************************************/
//#define PRESHARED_KEY_NUM 10
#define PRESHARED_KEY_NUM 5

Std_ReturnType Demo_FoDTest_aSIMS(void)
{
	Std_ReturnType result = E_OK;

	HSMAPI_OBJ_t hsmApiObj;
	HSM_FOD_ERR_STATE_t fodState;
	HSM_FOD_CERT_OUTPUT_t fodInfo;
	FoDCert fodCert;
	HSM_SIGN_t signInfo;

    #if 0
	UINT32 i;
    #endif
	UINT16 preSharedkeyIndex;
    #if 0
	UINT32 SaltDigestMSB32 = 0;
    #endif
	UINT32 saltLen = 16;
	UINT32 dkLen = 16;
	UINT32 dkCount = 1024;
	UINT8 saltDigest[16u];
	UINT8 deriveKey[16u];
	UINT8 dec_certificate[160] = {0,};

	/* aSIMS Sample Data */
	UINT32 eccKeyIndex = 401u;
	UINT32 decKeyIndex = 404u;

	/* #########################################
	 *       SAMPLE DATA FROM ASIMS 
	   #########################################  */

	/*1. FoD Cert Data from aSIMS Server */
	/*1) Encrypted certificate*/
	unsigned char enc_certificate[160] = {
		0x75, 0x13, 0x4E, 0x8C, 0xB5, 0x22, 0x91, 0xCA, 0x44, 0x53, 0x82, 0x21, 0xC2, 0xE4, 0x91, 0x87,
		0x03, 0xEE, 0xE4, 0x9F, 0x01, 0xCC, 0x30, 0xE1, 0x11, 0xDA, 0x9B, 0xAC, 0xFE, 0xFE, 0xA5, 0x77,
		0xF5, 0x45, 0x80, 0x4F, 0xA3, 0x8C, 0x3A, 0xE4, 0xE6, 0x4A, 0xB5, 0x2A, 0x45, 0xD6, 0x6A, 0xCB,
		0xD4, 0x4F, 0x8D, 0x1C, 0xD8, 0x97, 0x47, 0x33, 0x8F, 0xDE, 0xEF, 0x35, 0xE0, 0x5D, 0x5A, 0xB5,
		0x3B, 0xD3, 0x49, 0x15, 0x73, 0xB6, 0xD1, 0xF0, 0x82, 0xDA, 0xA7, 0xFA, 0xCA, 0x1A, 0x83, 0xB5,
		0x6A, 0x42, 0x39, 0x1C, 0x43, 0x93, 0xE5, 0x31, 0xE5, 0xB9, 0x9A, 0x36, 0xAD, 0xBF, 0x2F, 0x7E,
		0x89, 0x3C, 0xA3, 0x51, 0x91, 0x08, 0x1F, 0x56, 0x00, 0x1F, 0x80, 0x00, 0xBC, 0x15, 0x23, 0xBC,
		0x0E, 0xFA, 0x47, 0x6B, 0x7D, 0x49, 0x16, 0x7B, 0x9B, 0x24, 0xB6, 0xA9, 0x5B, 0x09, 0xD7, 0x11,
		0x2A, 0xE2, 0x50, 0x02, 0xA4, 0xFD, 0x3A, 0x52, 0x32, 0x76, 0x83, 0x28, 0x38, 0x3F, 0xF5, 0x35,
		0xF2, 0xBD, 0xB0, 0x40, 0x8E, 0x52, 0x7D, 0xC3, 0x1E, 0xEE, 0xE2, 0xEE, 0xB2, 0xC8, 0x33, 0x40 
	};

	/*2) salt for derivation key*/
	unsigned char salt[16] = {
  		0xF6, 0x54, 0x64, 0xAC, 0x70, 0x3A, 0xBA, 0x68, 0xFE, 0x75, 0x67, 0x40, 0xF3, 0xD9, 0xA5, 0xFD 
	};

	/*3) Secret Payload for MAC verification*/
    #if 0
	unsigned char secretPayload[16] = {
  		0xB0, 0x0F, 0xC7, 0xBD, 0xB8, 0x64, 0xC2, 0x60, 0x8C, 0x5A, 0x47, 0x4A, 0x6F, 0x05, 0x7B, 0x45 
	};
    #endif

	/* 2. FoD Cert Data from aSIMS Server */
	/* 1) Decrypted Certificate data( Decryption of enc_certificate by derive key )*/
	unsigned char certificate[160] = {
		0x31, 0x43, 0x44, 0x33, 0x34, 0x41, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30,
		0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x45, 0x49, 0x31, 0x32, 0x33, 0x34, 0xB0, 0x0F, 0xC7,
		0xBD, 0xB8, 0x64, 0xC2, 0x60, 0x8C, 0x5A, 0x47, 0x4A, 0x6F, 0x05, 0x7B, 0x45, 0x49, 0x39, 0x38,
		0x37, 0x34, 0x32, 0x30, 0x32, 0x31, 0x30, 0x34, 0x31, 0x33, 0x32, 0x30, 0x32, 0x31, 0x30, 0x34,
		0x31, 0x34, 0x32, 0x30, 0x32, 0x32, 0x30, 0x34, 0x31, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x72, 0x3C, 0x16, 0xB4, 0x11, 0x78, 0x45, 0x03, 0x56, 0x73, 0x5F, 0xB7, 0xA4, 0x6B, 0xA1, 0xE3,
		0xBA, 0xA4, 0x92, 0x52, 0x0A, 0x42, 0xD9, 0x87, 0x6A, 0xF5, 0xD3, 0xD7, 0xDC, 0x08, 0x49, 0xDC,
		0x8C, 0x34, 0x33, 0x7E, 0x7E, 0x26, 0xF7, 0x0B, 0xC8, 0x0A, 0x58, 0xD6, 0x79, 0x2B, 0xC8, 0x0B,
		0x60, 0x5B, 0xFF, 0xAF, 0x53, 0xF3, 0x3C, 0x58, 0x97, 0x1F, 0xE3, 0xD2, 0xEA, 0x72, 0xEC, 0x90 
	};

	/* 2) Hashed Data from salt*/
	unsigned char iv[16] = {
	    0x62, 0x70, 0xBE, 0xFB, 0x37, 0x0E, 0x73, 0xDB, 0xB2, 0xB5, 0x88, 0xA7, 0x1B, 0x18, 0x04, 0x6F 
	};

	/* 3) Cetificate signature*/
    #if 0
	unsigned char signature[64] = {
		0x72, 0x3C, 0x16, 0xB4, 0x11, 0x78, 0x45, 0x03, 0x56, 0x73, 0x5F, 0xB7, 0xA4, 0x6B, 0xA1, 0xE3,
		0xBA, 0xA4, 0x92, 0x52, 0x0A, 0x42, 0xD9, 0x87, 0x6A, 0xF5, 0xD3, 0xD7, 0xDC, 0x08, 0x49, 0xDC,
		0x8C, 0x34, 0x33, 0x7E, 0x7E, 0x26, 0xF7, 0x0B, 0xC8, 0x0A, 0x58, 0xD6, 0x79, 0x2B, 0xC8, 0x0B,
		0x60, 0x5B, 0xFF, 0xAF, 0x53, 0xF3, 0x3C, 0x58, 0x97, 0x1F, 0xE3, 0xD2, 0xEA, 0x72, 0xEC, 0x90 
	};
    #endif

	
	/* #########################################
	 *    KEY DERIVATION AND DECRYPTE CERTIFICATE  
	   #########################################  */

	/* FoD TestCase #1 - Test Data from aSIMS */
	/* Result : SUCCESS */
	// 1. Key derivation
	// 1) Make salt Digest for extract psk and iv 
	result += HSM_Sha256(salt, 16u, saltDigest);

#if 0 
	/* 2) extract preSharedKey from salf digest
	    ( PRESHARED_KEY_NUM = 10)
	*/
	for(i = 0;i < 4;i++) { SaltDigestMSB32 |= ((UINT32)saltDigest[i] << ((3-i)*8)); }
	preSharedkeyIndex = (UINT16)((SaltDigestMSB32 % PRESHARED_KEY_NUM) + 11); //PSK first index = 1
#else
	preSharedkeyIndex = (UINT16)decKeyIndex; //#404
#endif
	/* 3) make derivedKey
		saltLen = 16Byte
		dkLen = 16Byte
	*/
	result += HSM_Pbkdf2(preSharedkeyIndex, NULL, 0, salt, saltLen, dkCount, dkLen, deriveKey);
	Hae_swap_byteOrder(deriveKey, 16u);
	// 4) Store Key to HSM
	result += HSM_KeyManagementSetAesKey(301u, deriveKey, FALSE);
	if(result == E_OK) {
		result = HSM_KeyManagementValidateKey(AES_KEY, 301u);
	}
	else
	{
		while(1);
	}

	// 2. Decryption
	// 1) set AES CTR Decrypt iv form salfDigest
	Hae_Memcpy(iv, saltDigest, 16);
	result += HSM_AesDec(HSM_AES_CTR_MODE, 301u, iv, 160, enc_certificate, dec_certificate);

	// 2) Compare result
	result += Hae_Memcmp(dec_certificate, certificate, 160);
	if(result != E_OK)
	{
		while(1);
	}


	/* #########################################
	 *    STORE, DELETE, GET FOD CERTIFICATE  
	   #########################################  */

	/* FoD TestCase #1 - Store FoDCert SN 0x43443334*/
	/* Result : SUCCESS (FodList is stored)*/
	// 1. Set Cert Data
	Hae_Memcpy(&fodCert, &certificate[0], 96);
	Hae_Memcpy(&signInfo.sign, &certificate[96], 64);
	signInfo.signKeyNum = eccKeyIndex;
	// 3. Store FoDCert to HSM
	
	hsmApiObj.apiCtx.apiProcessMode = HSM_API_NON_BLOCKING_MODE;
	result += HSM_FeatureOnDemandCertStore(&fodCert, &signInfo, &fodState, &hsmApiObj);
	result += waitHsmResp(&hsmApiObj);
	if(result == E_OK)
	{
		s_fodState = fodState;
	}
	else
	{
		while(1);
	}

	// 4. Confirm FoDCert Data
	hsmApiObj.apiCtx.apiProcessMode = HSM_API_NON_BLOCKING_MODE;
	result += HSM_FeatureOnDemandGetCertList(&fodInfo, &hsmApiObj);
	result += waitHsmResp(&hsmApiObj);
	if(result == E_OK)
	{
		Hae_Memcpy(s_fodCertList, fodInfo.fodCertList, sizeof(FoDCert) * FOD_NUMBER_OF_SET);
		s_fodNumOfCert = fodInfo.numOfFodCert;
		s_fodState = fodInfo.fodErrState;
	}
	else
	{
		while(1);
	}

	/* FoD TestCase #2 - Delete FoDCert SN 0x43443334*/
	/* Result : SUCCESS (FodList is empty)*/
	// 1. Set Cert Data
	// 3. Store FoDCert to HSM
	hsmApiObj.apiCtx.apiProcessMode = HSM_API_NON_BLOCKING_MODE;
	result += HSM_FeatureOnDemandCertDelete(&fodCert, &signInfo, &s_fodState, &hsmApiObj);
	result += waitHsmResp(&hsmApiObj);
	if(result == E_OK)
	{
		s_fodState = fodState;
	}
	else
	{
		while(1);
	}

	// 4. Confirm FoDCert Data
	hsmApiObj.apiCtx.apiProcessMode = HSM_API_NON_BLOCKING_MODE;
	result += HSM_FeatureOnDemandGetCertList(&fodInfo, &hsmApiObj);
	result += waitHsmResp(&hsmApiObj);
	if(result == E_OK)
	{
		Hae_Memcpy(s_fodCertList, fodInfo.fodCertList, sizeof(FoDCert) * FOD_NUMBER_OF_SET);
		s_fodNumOfCert = fodInfo.numOfFodCert;
		s_fodState = fodInfo.fodErrState;
	}
	else
	{
		while(1);
	}

	return result;
}
