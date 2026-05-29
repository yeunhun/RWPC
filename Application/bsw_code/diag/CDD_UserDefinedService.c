/*******************************************************************************
**                       HYUNDAI-AUTOEVER PVT LTD                             **
********************************************************************************
** Copyright (C) HYUNDAI-AUTOEVER PVT LTD - All Rights Reserved               **
** Unauthorized copying of this file, via any medium is strictly prohibited   **
** Auto generated file                                                        **
*******************************************************************************/
#include "Cdd_UserDefinedService.h"
#include "Dcm_DsdInternal.h"
#include "Rte_CDD_UDS.h"

#include "WPCType.h"
#include "define.h"
#include "Data.h"
#include "WPCI2CControl.h"

#include "app_input_type.h"
#include "app_input.h"
#include "app_output_type.h"
#include "app_output.h"
#include "WPCOutput.h"
#include "WPCEepControl.h"

#include "Dem_Types.h"


typedef enum
{
  DTCSetCtl_ON=0U,
  DTCSetCtl_OFF
}Vtype_DTCSetCtl;

#define Par_DTCClearCount 30u


extern uint8 GetReprogrammingProgress(void);
extern uint8 b_UpdateFlashCmd;
extern e_EraseFlashCtrl sts_EraseFlashCtrl;

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

static	rom_tbl	u8	tbl_DTC_number[][3]=
{
	{0x96,0x03,0x00},	/* BCAN BusOff */
	{0x96,0x0F,0x00},	/* LocalCAN BusOff */
	{0x96,0x21,0x01},	/* Temp Sensor Fault */
	{0x96,0x21,0x02},	/* FAN Fault */
	{0x96,0x21,0x03},   /* WPC ECU Internal Error */
};
/*******************************************************************************
	Define Constant and Macro
*******************************************************************************/
#define	BCAN_BUSOFF				(0u)
#define	LocalCAN_BUSOFF			(1u)
#define	DTC_B1621_01			(2u)
#define	DTC_B1621_02			(3u)
#define	DTC_B1621_03			(4u)

tFD_Condition_WPC tbl_ForcedDrive_WPC[7]=
{
/*	 sid		index			status	repeat_cnt		initiated		on_time  			off_time	*/
	{0x11u,	IO_Amber_OUT, 	Off, 	5u, 			Off, 		Time_ms(1000),	Time_ms(1000)},
	{0x12u,	IO_Green_OUT, 	Off, 	5u, 			Off, 		Time_ms(1000),	Time_ms(1000)},
	{0x31u,	IO_Amber_OUT, 	Off, 	0u, 			Off, 		Time_ms(1000),	0u},
	{0x32u,	IO_Green_OUT, 	Off, 	0u, 			Off, 		Time_ms(1000),	0u},
	{0x33u,	IO_Fan_OUT, 	Off, 	0u, 			Off, 		Time_ms(1000),	0u},
	{0x13u,	IO_Fan_OUT, 	Off, 	0u, 			Off, 		Time_sec(5),	0u},
	{0xFFu,	0xFFu, 			0u,		0u,				0u,			0u,				0u}
};

/*
	number : dataIdentifier byte #2(LSB)
	active : inputOutputControlParameter

	���� ���� ��� ���� Ȯ��
*/

uint8 SetDiag_Supported_IOCBI(uint8 number, uint8 active)
{
	u32	i = 0;
	u8	ret_val=0;

	for(i=0; tbl_ForcedDrive_WPC[i].service_id != 0xffu; i++)
	{ /* Service id Searching */
		if(tbl_ForcedDrive_WPC[i].service_id == number)
		{
			break;
		}
	}

	if(tbl_ForcedDrive_WPC[i].service_id == 0xffu)
	{ /* Range Out */
		ret_val = DCM_E_SUBFUNCTIONNOTSUPPORTED;
	}
	else if(active == ForceOn)
	{ /* Start */
		if((tbl_ForcedDrive_WPC[i].status == On) ||
			(GetOutput_IOCBI(tbl_ForcedDrive_WPC[i].index) == On))
		{
			ret_val = DCM_E_BUSYREPEATREQUEST;
		}
		else
		{
			if((tbl_ForcedDrive_WPC[i].index == IO_Amber_OUT) ||
				(tbl_ForcedDrive_WPC[i].index == IO_Green_OUT) ||
				(tbl_ForcedDrive_WPC[i].index == IO_Fan_OUT))
			{
				if(GetX(kb_IGN_IN) == On)
				{
					tbl_ForcedDrive_WPC[i].status = On;
					tbl_ForcedDrive_WPC[i].initiated = Off;
					//IOCBI_Status = On;
				}
				else
				{
					ret_val = DCM_E_CONDITIONSNOTCORRECT;
				}
			}
		}
	}
	else if(active == ForceOff) 
	{ /* Stop */
		if(tbl_ForcedDrive_WPC[i].status == Off)
		{
			ret_val = DCM_E_CONDITIONSNOTCORRECT;
		}
		else
		{
			tbl_ForcedDrive_WPC[i].status = Off;
			//IOCBI_Status = Off;
		}
	}
	else
	{
		ret_val = DCM_E_SUBFUNCTIONNOTSUPPORTED;
	}
	
	return	ret_val;
}


uint8 SetDiag_Supported_IOCBI_SY(uint8 number, uint8 duty)
{
	u32	i = 0;
	u8	ret_val=0;

	for(i=0; tbl_ForcedDrive_WPC[i].service_id != 0xffu; i++)
	{ /* Service id Searching */
		if(tbl_ForcedDrive_WPC[i].service_id == number)
		{
			break;
		}
	}
	
	if(tbl_ForcedDrive_WPC[i].service_id == 0xffu)
	{ /* Range Out */
		ret_val = DCM_E_SUBFUNCTIONNOTSUPPORTED;
	}
	else if(duty > ForceOff)
	{ /* Start */
		if((tbl_ForcedDrive_WPC[i].status == On) ||
			(GetOutput_IOCBI(tbl_ForcedDrive_WPC[i].index) == On))
		{
			ret_val = DCM_E_BUSYREPEATREQUEST;
		}
		else
		{
			if((tbl_ForcedDrive_WPC[i].index == IO_Amber_OUT) ||
				(tbl_ForcedDrive_WPC[i].index == IO_Green_OUT) ||
				(tbl_ForcedDrive_WPC[i].index == IO_Fan_OUT))
			{
				/* ���� ���� Ȯ�� */
				if(GetX(kb_IGN_IN) == On)
				{
					tbl_ForcedDrive_WPC[i].status = On;
					tbl_ForcedDrive_WPC[i].repeat_cnt = duty;
					tbl_ForcedDrive_WPC[i].initiated = Off;
					//IOCBI_Status = On;
				}
				else
				{
					ret_val = DCM_E_CONDITIONSNOTCORRECT;
				}
			}
			else 
			{
				/* MISRA-C RULE */
			}
		}
	}
	else if(duty == ForceOff) 
	{ /* Stop */
		if(tbl_ForcedDrive_WPC[i].status == Off)
		{
			ret_val = DCM_E_CONDITIONSNOTCORRECT;
		}
		else
		{
			tbl_ForcedDrive_WPC[i].status = Off;
			//IOCBI_Status = Off;
		}
	}
	else
	{
		ret_val = DCM_E_SUBFUNCTIONNOTSUPPORTED;
	}
	
	return	ret_val;
}

void RE_UDS(void)
{
	/* Function For Signal Mappping */
}


uint8 test[8] = {0, };
uint8 b_DTCInhibitFlag = Off;	//수정필요
extern uint8 b_DTC_B1621_Present;
uint8 b_DTC_B1621_01_Oldvalue = 0;
uint8 b_DTC_B1621_02_Oldvalue = 0;
uint8 b_DTC_B1621_03_Oldvalue = 0;

/* srvId_0x19_ReadDTCInformation */
Std_ReturnType Dcm_ReadDTCInformation(Dcm_OpStatusType OpStatus, Dcm_MsgContextType *pMsgContext)
{
	Std_ReturnType retVal = E_NOT_OK;
	Dcm_NegativeResponseCodeType ErrorCode = DCM_E_POSITIVERESPONSE;

	uint8 i=0u;
	uint8 NumberOfDTC = 0u;
	uint8 Get_BCAN_EventStatus=0u;
	uint8 Get_LCAN_EventStatus = 0u;
	
	
	Rte_Call_EventInfo_CANSM_E_BUS_OFF_BCAN_GetEventStatus(&Get_BCAN_EventStatus);	/* B-CAN Bus Off */
	Rte_Call_EventInfo_CANSM_E_BUS_OFF_LCAN_GetEventStatus(&Get_LCAN_EventStatus);	/* L-CAN Bus Off */

	switch(OpStatus)
	{
		case DCM_INITIAL:
			if(b_DTCInhibitFlag == Off)
			{
				if(pMsgContext->reqDataLen == 2u)
				{ /* Request Length Check */
					pMsgContext->resData[i] = pMsgContext->reqData[i];	/* Report Number of DTC By Status Mask : 0x01 or 0x02 */
					i++;
					pMsgContext->resData[i] = 0x09u;/* 0x08(Historic) or 0x09(Active) : DTCSAM */ /* 20161212 Fix G-SCAN bug */
					i++;

					switch(*(pMsgContext->reqData))
					{
						case	kReportNumberOfDTCByStatusMask:                         // 0x01u;
							if ((Get_BCAN_EventStatus>>kTestFailed)&0x01)
							{/* BCAN BusOff */
								NumberOfDTC++;
							}
							else if ((Get_BCAN_EventStatus>>kConfirmedDTC)&0x01)
							{/* BCAN BusOff Memorize */
								NumberOfDTC++;
							}
							else
							{ /*MISRA*/	}
							if ((Get_LCAN_EventStatus>>kTestFailed)&0x01)
							{/* LocalCAN BusOff */
								NumberOfDTC++;
							}
							else if ((Get_LCAN_EventStatus>>kConfirmedDTC)&0x01)
							{/* LocalCAN BusOff Memorize */
								NumberOfDTC++;
							}
							else
							{ /*MISRA*/	}
							if (Get_DTC_B1621_Present() >  0x00u)
							{/* WPC ECU Internal Error, Temp Sensor Fault, FAN Fault*/
								NumberOfDTC++;
							}
							
							pMsgContext->resData[i] = 0x00u;	/* ISO 15031-6 DTC Format : 0x00 */
							i++;
							pMsgContext->resData[i]	= 0x00u;	/* DTC Count High Byte */
							i++;
							pMsgContext->resData[i] = NumberOfDTC;	/* DTC Count Low Byte */
							i++;
							pMsgContext->resDataLen = i;

							ErrorCode = DCM_E_POSITIVERESPONSE;
							retVal = E_OK;
						break;

						case	kReportDTCByStatusMask:                               // 0x02u;
							if ((Get_BCAN_EventStatus>>kTestFailed)&0x01)
							{/* BCAN BusOff */
								pMsgContext->resData[(NumberOfDTC*4)+2u] = tbl_DTC_number[BCAN_BUSOFF][0];
								pMsgContext->resData[(NumberOfDTC*4)+3u] = tbl_DTC_number[BCAN_BUSOFF][1];
								pMsgContext->resData[(NumberOfDTC*4)+4u] = tbl_DTC_number[BCAN_BUSOFF][2];
								pMsgContext->resData[(NumberOfDTC*4)+5u] = 0x09u;
								NumberOfDTC++;
							}
							else if ((Get_BCAN_EventStatus>>kConfirmedDTC)&0x01)
							{/* BCAN BusOff Memorize */
								pMsgContext->resData[(NumberOfDTC*4)+2u] = tbl_DTC_number[BCAN_BUSOFF][0];
								pMsgContext->resData[(NumberOfDTC*4)+3u] = tbl_DTC_number[BCAN_BUSOFF][1];
								pMsgContext->resData[(NumberOfDTC*4)+4u] = tbl_DTC_number[BCAN_BUSOFF][2];
								pMsgContext->resData[(NumberOfDTC*4)+5u] = 0x08u;
								NumberOfDTC++;
							}
							else
							{ /*MISRA*/	}
							if ((Get_LCAN_EventStatus>>kTestFailed)&0x01)
							{/* LocalCAN BusOff */
								pMsgContext->resData[(NumberOfDTC*4)+2u] = tbl_DTC_number[LocalCAN_BUSOFF][0];
								pMsgContext->resData[(NumberOfDTC*4)+3u] = tbl_DTC_number[LocalCAN_BUSOFF][1];
								pMsgContext->resData[(NumberOfDTC*4)+4u] = tbl_DTC_number[LocalCAN_BUSOFF][2];
								pMsgContext->resData[(NumberOfDTC*4)+5u] = 0x09u;
								NumberOfDTC++;
							}
							else if ((Get_LCAN_EventStatus>>kConfirmedDTC)&0x01)
							{/* LocalCAN BusOff Memorize */
								pMsgContext->resData[(NumberOfDTC*4)+2u] = tbl_DTC_number[LocalCAN_BUSOFF][0];
								pMsgContext->resData[(NumberOfDTC*4)+3u] = tbl_DTC_number[LocalCAN_BUSOFF][1];
								pMsgContext->resData[(NumberOfDTC*4)+4u] = tbl_DTC_number[LocalCAN_BUSOFF][2];
								pMsgContext->resData[(NumberOfDTC*4)+5u] = 0x08u;
								NumberOfDTC++;
							}
							else
							{ /*MISRA*/	}
							if (Get_DTC_B1621_Present() > 0x00u)
							{/* DTC B1621 */
								if(b_DTC_B1621_Present == 0x01)
								{
									pMsgContext->resData[(NumberOfDTC*4)+2u] = tbl_DTC_number[DTC_B1621_01][0];
									pMsgContext->resData[(NumberOfDTC*4)+3u] = tbl_DTC_number[DTC_B1621_01][1];
									pMsgContext->resData[(NumberOfDTC*4)+4u] = tbl_DTC_number[DTC_B1621_01][2];
									pMsgContext->resData[(NumberOfDTC*4)+5u] = 0x09u;
									NumberOfDTC++;
									b_DTC_B1621_01_Oldvalue = b_DTC_B1621_Present;
									if(b_DTC_B1621_02_Oldvalue == 0x02)
									{
										pMsgContext->resData[(NumberOfDTC*4)+2u] = tbl_DTC_number[DTC_B1621_02][0];
										pMsgContext->resData[(NumberOfDTC*4)+3u] = tbl_DTC_number[DTC_B1621_02][1];
										pMsgContext->resData[(NumberOfDTC*4)+4u] = tbl_DTC_number[DTC_B1621_02][2];
										pMsgContext->resData[(NumberOfDTC*4)+5u] = 0x09u;
										NumberOfDTC++;
									}
									if(b_DTC_B1621_03_Oldvalue == 0x03)
									{
										pMsgContext->resData[(NumberOfDTC*4)+2u] = tbl_DTC_number[DTC_B1621_03][0];
										pMsgContext->resData[(NumberOfDTC*4)+3u] = tbl_DTC_number[DTC_B1621_03][1];
										pMsgContext->resData[(NumberOfDTC*4)+4u] = tbl_DTC_number[DTC_B1621_03][2];
										pMsgContext->resData[(NumberOfDTC*4)+5u] = 0x09u;
										NumberOfDTC++;
									}
								}
								if(b_DTC_B1621_Present == 0x02)
								{
									pMsgContext->resData[(NumberOfDTC*4)+2u] = tbl_DTC_number[DTC_B1621_02][0];
									pMsgContext->resData[(NumberOfDTC*4)+3u] = tbl_DTC_number[DTC_B1621_02][1];
									pMsgContext->resData[(NumberOfDTC*4)+4u] = tbl_DTC_number[DTC_B1621_02][2];
									pMsgContext->resData[(NumberOfDTC*4)+5u] = 0x09u;
									NumberOfDTC++;
									b_DTC_B1621_02_Oldvalue = b_DTC_B1621_Present;
									if(b_DTC_B1621_01_Oldvalue == 0x01)
									{
										pMsgContext->resData[(NumberOfDTC*4)+2u] = tbl_DTC_number[DTC_B1621_01][0];
										pMsgContext->resData[(NumberOfDTC*4)+3u] = tbl_DTC_number[DTC_B1621_01][1];
										pMsgContext->resData[(NumberOfDTC*4)+4u] = tbl_DTC_number[DTC_B1621_01][2];
										pMsgContext->resData[(NumberOfDTC*4)+5u] = 0x09u;
										NumberOfDTC++;
									}
									if(b_DTC_B1621_03_Oldvalue == 0x03)
									{
										pMsgContext->resData[(NumberOfDTC*4)+2u] = tbl_DTC_number[DTC_B1621_03][0];
										pMsgContext->resData[(NumberOfDTC*4)+3u] = tbl_DTC_number[DTC_B1621_03][1];
										pMsgContext->resData[(NumberOfDTC*4)+4u] = tbl_DTC_number[DTC_B1621_03][2];
										pMsgContext->resData[(NumberOfDTC*4)+5u] = 0x09u;
										NumberOfDTC++;
									}
								}
								if(b_DTC_B1621_Present == 0x03)
								{
									pMsgContext->resData[(NumberOfDTC*4)+2u] = tbl_DTC_number[DTC_B1621_03][0];
									pMsgContext->resData[(NumberOfDTC*4)+3u] = tbl_DTC_number[DTC_B1621_03][1];
									pMsgContext->resData[(NumberOfDTC*4)+4u] = tbl_DTC_number[DTC_B1621_03][2];
									pMsgContext->resData[(NumberOfDTC*4)+5u] = 0x09u;
									NumberOfDTC++;
									b_DTC_B1621_03_Oldvalue = b_DTC_B1621_Present;
									if(b_DTC_B1621_01_Oldvalue == 0x01)
									{
										pMsgContext->resData[(NumberOfDTC*4)+2u] = tbl_DTC_number[DTC_B1621_01][0];
										pMsgContext->resData[(NumberOfDTC*4)+3u] = tbl_DTC_number[DTC_B1621_01][1];
										pMsgContext->resData[(NumberOfDTC*4)+4u] = tbl_DTC_number[DTC_B1621_01][2];
										pMsgContext->resData[(NumberOfDTC*4)+5u] = 0x09u;
										NumberOfDTC++;
									}
									if(b_DTC_B1621_02_Oldvalue == 0x02)
									{
										pMsgContext->resData[(NumberOfDTC*4)+2u] = tbl_DTC_number[DTC_B1621_02][0];
										pMsgContext->resData[(NumberOfDTC*4)+3u] = tbl_DTC_number[DTC_B1621_02][1];
										pMsgContext->resData[(NumberOfDTC*4)+4u] = tbl_DTC_number[DTC_B1621_02][2];
										pMsgContext->resData[(NumberOfDTC*4)+5u] = 0x09u;
										NumberOfDTC++;
									}
								}
								
							}
							else
							{ /*MISRA*/	}
							pMsgContext->resDataLen = (NumberOfDTC*4)+2u;
							test[0] = pMsgContext->resData[0];
							test[1] = pMsgContext->resData[1];
							test[2] = pMsgContext->resData[2];
							test[3] = pMsgContext->resData[3];
							test[4] = pMsgContext->resData[4];
							test[5] = pMsgContext->resData[5];
							test[6] = pMsgContext->resData[6];
							ErrorCode = DCM_E_POSITIVERESPONSE;
							retVal = E_OK;
						break;

						default:
							ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
							retVal = E_NOT_OK;
						break;
					}
				}
				else
				{/* Negative */
					ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
					retVal = E_NOT_OK;
				}
			}
			else
			{/* Negative */
				ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
				retVal = E_NOT_OK;
			}
			break;

		case DCM_PENDING:
			ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
			retVal = E_NOT_OK;
			break;

		case DCM_CANCEL:
			ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
			retVal = E_NOT_OK;
			break;

		default:
			ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
			retVal = E_NOT_OK;
			break;
	}

	/* ReturnValue ?�쏙??Response 처占?�옙 */
	if(retVal == (Std_ReturnType)E_NOT_OK)
	{
		/* Negative Response */
		Dcm_ExternalSetNegResponse(pMsgContext, ErrorCode);
		Dcm_ExternalProcessingDone(pMsgContext);
	}
	else
	{
		/* Positive Response */
		Dcm_ExternalProcessingDone(pMsgContext);
	}
	return retVal;
}


Std_ReturnType Dcm_InputOutputControlByIdentifier(Dcm_OpStatusType OpStatus, Dcm_MsgContextType *pMsgContext)
{
	Std_ReturnType retVal = E_NOT_OK;
	Dcm_NegativeResponseCodeType ErrorCode = DCM_E_POSITIVERESPONSE;
	
	
	switch(OpStatus)
	{
		case DCM_INITIAL:
			/* Request Length Check */
			if(pMsgContext->reqDataLen == 3u)
			{
				pMsgContext->resData[0] = pMsgContext->reqData[0];	//0xF0
				pMsgContext->resData[1] = pMsgContext->reqData[1];	//0x11, 0x12, 0x13
				pMsgContext->resData[2] = pMsgContext->reqData[2];	//0x00, 0x03

				/* Check reqData */
				if(pMsgContext->reqData[0] == kDID_F0)
				{
					if((pMsgContext->reqData[1]==0x00u) || (pMsgContext->reqData[1] == 0x10u)) /* Supported check DID F000 */
					{
						pMsgContext->resDataLen = 7u;

						pMsgContext->resData[2] = pMsgContext->reqData[2];
						pMsgContext->resData[3] = 0x00u;	// Supperted DID 0x01 ~ 0x08	0000 | 0000
						pMsgContext->resData[4] = 0x00u;	// Supperted DID 0x09 ~ 0x10	0000 | 0000
						pMsgContext->resData[5] = 0xE0u;	// Supperted DID 0x11 ~ 0x18	1110 | 0000
						pMsgContext->resData[6] = 0x00u;	// Supperted DID 0x19 ~ 0x20	0000 | 0000

						retVal = E_OK;
						ErrorCode = E_OK;
					
					}
					else if(pMsgContext->reqData[1] == 0x20u) /* Supported check DID F020 */
					{
						pMsgContext->resDataLen = 7u;

						pMsgContext->resData[2] = pMsgContext->reqData[2];
						pMsgContext->resData[3] = 0x80u;	// Supperted DID 0x01 ~ 0x08	1000 | 0000
						pMsgContext->resData[4] = 0x00u;	// Supperted DID 0x09 ~ 0x10	0000 | 0000
						pMsgContext->resData[5] = 0x00u;	// Supperted DID 0x11 ~ 0x18	0000 | 0000
						pMsgContext->resData[6] = 0x00u;	// Supperted DID 0x19 ~ 0x20	0000 | 0000

						retVal = E_OK;
						ErrorCode = E_OK;
					}
					else if(pMsgContext->reqData[1] == 0x40u) /* Supported check DID F040 */
					{
						
						pMsgContext->resDataLen = 7u;
						
						pMsgContext->resData[2] = pMsgContext->reqData[2];
						pMsgContext->resData[3] = 0x00u;	// Supperted DID 0x01 ~ 0x08	0000 | 0000
						pMsgContext->resData[4] = 0x00u;	// Supperted DID 0x09 ~ 0x10	0000 | 0000
						pMsgContext->resData[5] = 0x00u;	// Supperted DID 0x11 ~ 0x18	0000 | 0000
						pMsgContext->resData[6] = 0x00u;	// Supperted DID 0x19 ~ 0x20	0000 | 0000

						retVal = E_OK;
						ErrorCode = E_OK;

					}
					else if((pMsgContext->reqData[1] == kAmberLED_11) || 
						    (pMsgContext->reqData[1] == kGreenLED_12) ||
						    (pMsgContext->reqData[1] == kFANON_13))
					{
						ErrorCode = SetDiag_Supported_IOCBI(pMsgContext->reqData[1], pMsgContext->reqData[2]);

						if(ErrorCode != Off)
						{
							retVal = ErrorCode;
						}
						else
						{
							pMsgContext->resDataLen = 3u;
							retVal = E_OK;
							ErrorCode = E_OK;
						}
					}
					else if(pMsgContext->reqData[1] == KWCTCancel)
					{
						pMsgContext->resDataLen = 3u;
						
						sts_EraseFlashCtrl = EraseFlashCtrl_Start;
						b_UpdateFlashCmd = 0u;

						ErrorCode = DCM_E_SERVICENOTSUPPORTED;
						retVal = E_NOT_OK;
					}

					else if(pMsgContext->reqData[1] == kWCTStuats)
					{
						pMsgContext->resDataLen = 4u;

						if(b_UpdateFlashCmd == On)
						{
							if((sts_EraseFlashCtrl == Delay_Erase_Flash) ||
								(sts_EraseFlashCtrl == Erase_Flash_1st) ||
								(sts_EraseFlashCtrl == Erase_Flash_2nd) ||
								(sts_EraseFlashCtrl == Write_Flash_Cmd))
								
							{
								pMsgContext->resData[3] = 0; /* WCT Reprogramming progress */
							}
							else if((sts_EraseFlashCtrl == Write_Flash_Data) ||
									(sts_EraseFlashCtrl == Verify_Flash))
							{
								pMsgContext->resData[3] = GetReprogrammingProgress(); /* WCT Reprogramming progress */
							}
							else
							{
								pMsgContext->resData[3] = 0u; /* WCT Reprogramming progress */
							}
						}
						else
						{
							pMsgContext->resData[3] = 100u; /* WCT Reprogramming progress */
						}

						retVal = E_OK;
						ErrorCode = E_OK;

					}
					
					else if(pMsgContext->reqData[1] == kWCTReprogram)
					{
						pMsgContext->resDataLen = 3u;
							
						b_UpdateFlashCmd = On;

						retVal = E_OK;
						ErrorCode = E_OK;
					}
					else if((pMsgContext->reqData[1] == kAmberLEDPWMDuty_31) || // For LED/FAN PWM Duty Rate Control
							(pMsgContext->reqData[1] == kGreenLEDPWMDuty_32) ||
							(pMsgContext->reqData[1] == kFANOnPWMDuty_33))
					{
						ErrorCode = SetDiag_Supported_IOCBI_SY(pMsgContext->reqData[1], pMsgContext->reqData[2]);

						if(ErrorCode != Off)
						{
							retVal = ErrorCode;
						}
						else
						{
							pMsgContext->resDataLen = 3u;
							retVal = E_OK;
							ErrorCode = E_OK;
						}
					}
					else
					{
						ErrorCode = DCM_E_SERVICENOTSUPPORTED;
						retVal = E_NOT_OK;
					}
				}
				else
				{
					ErrorCode = DCM_E_REQUESTOUTOFRANGE;
					retVal = E_NOT_OK;
				}
			}
			else
			{
				/* Request Length Error : DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT (NRC13) */
				ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
				retVal = E_NOT_OK;
			}
		break;

		case DCM_PENDING:
			/* Do something */
			ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
			break;
		case DCM_CANCEL:
			/* Do something */
			ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
			break;
		
		default:
			/* QAC */
			break;
	}

	/* ReturnValue ?�쏙??Response 처占?�옙 */
	if(retVal == (Std_ReturnType)E_NOT_OK)
	{
		/* Negative Response */
		Dcm_ExternalSetNegResponse(pMsgContext, ErrorCode);
		Dcm_ExternalProcessingDone(pMsgContext);
	}
	else
	{
		/* Positive Response */
		Dcm_ExternalProcessingDone(pMsgContext);
	}
	return retVal;
}

void ClearDTCByUDS(void);
void ClearDTCByUDS(void)
{
/* BCAN Bus Off */
  Set_DTC_BCAN_BusOff_Memorize(Off);
  Set_DTC_BCAN_BusOff_Present(Off);
  Set_DTCClear_Count_BCAN_BusOff(0u);
  Set_EepromData_DTC((u8)kDTC_BCAN_BUSOFF, Off);
/* LCAN Bus Off */
  Set_DTC_LCAN_BusOff_Memorize(Off);
  Set_DTC_LCAN_BusOff_Present(Off);
  Set_DTCClear_Count_LCAN_BusOff(0u);
  Set_EepromData_DTC((u8)kDTC_LCAN_BUSOFF, Off);
/* B16B2-00 */
  Set_DTC_B1621_Present(Off);
  //Set_DTCClear_Count_B1621(0u);
}


/* srvId_0x14_ClearDiagnosticInformation */
Std_ReturnType Dcm_ClearDiagnosticInformation(Dcm_OpStatusType OpStatus, Dcm_MsgContextType *pMsgContext)
{
  Std_ReturnType retVal = E_NOT_OK;
  Dcm_NegativeResponseCodeType ErrorCode = DCM_E_POSITIVERESPONSE;
  Std_ReturnType returnValue = 0u;

  /*
   * Input Parameter OpStatus �� ���� �б� ó���Ѵ�.
   * OpStatus == DCM_INITIAL : �Լ� ���� ���� ����
   * OpStatus == DCM_PENDING : PENDING ó�� ���� ������ ����
   * OpStatus == DCM_CANCEL : ���� ���� ����
  */

  switch(OpStatus)
  {
    case DCM_INITIAL:
      /* Request Length Check */
      if(pMsgContext->reqDataLen == 3u)
      {
        /* Check Subfunction */
        if(((pMsgContext->reqData[0] == 0x80) &&  /* BODY GROUP */
            (pMsgContext->reqData[1] == 0x00) &&
          (pMsgContext->reqData[2] == 0x00)) ||
          ((pMsgContext->reqData[0] == 0xFF) && /* ALL GROUP */
          (pMsgContext->reqData[1] == 0xFF) &&
          (pMsgContext->reqData[2] == 0xFF)))
        {
          /*  8000FF : Body Group
            8001XX ~ 8FFFXX : Body DTC's // todolist
            FFFFFF : All Groups
          */
          /* Clear BodyGroup */
          b_DTC_B1621_01_Oldvalue = 0x0u;
		  b_DTC_B1621_02_Oldvalue = 0x0u;
		  b_DTC_B1621_03_Oldvalue = 0x0u;
          returnValue = Rte_Call_R_Cdd_ClearDTC(DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_FORMAT_UDS, DEM_DTC_ORIGIN_PRIMARY_MEMORY);

          if(returnValue == DEM_CLEAR_PENDING)
          {
            ErrorCode = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING; // 120 == 0x78
          }
          else
          {
            ErrorCode = DCM_E_POSITIVERESPONSE;
          }

          ClearDTCByUDS();
        }
        else
        {
          ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        }
      }
      else
      {
        /* Negative */
        ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
      }
      break;

    case DCM_PENDING:
      /*
      DEM_CLEAR_WRONG_DTC : Input parameter �� �߸��� DTC �� ������� ���
      DEM_CLEAR_WRONG_DTCORIGIN : Input parameter �� �߸��� DTCOrigin �� ������� ���
      DEM_CLEAR_FAILED:* DTC �� �����ϴ� �� ���� ���� ���
      DEM_CLEAR_PENDING
      1. ClearDTC �� �񵿱� �Լ��̹Ƿ� ������ �Ϸ� �� ������ DEM_CLEAR_PENDING �� ����
      2. ClearDiagnosticInformation ���� ���񽺸� ���� DTC �� ���� ���� ���
      */
      returnValue = Rte_Call_R_Cdd_ClearDTC(DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_FORMAT_UDS, DEM_DTC_ORIGIN_PRIMARY_MEMORY);

      if(returnValue == DEM_CLEAR_PENDING)
      {
        ErrorCode = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
        /* ���ϰ��� DEM_CLEAR_PENDING �� ��� �Ϸ� �� ������
        Xxx_ClearDTC Operation �� ȣ���ؾ� �Ѵ�. */
      }
      else
      {
        ErrorCode = DCM_E_POSITIVERESPONSE;
      }
      break;

    case DCM_CANCEL:
      ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      break;

    default:
      ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      break;
  }

  /* ReturnValue �� Response ó�� */
  if(ErrorCode == DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING)
  {
    /* Pending Response */
    retVal = DCM_E_PENDING;
  }
  else if(ErrorCode == DCM_E_POSITIVERESPONSE)
  {
    /* Positive Response */
    retVal = E_OK;
    Dcm_ExternalProcessingDone(pMsgContext);
  }
  else
  {
    /* Negative Response */
    Dcm_ExternalSetNegResponse(pMsgContext, ErrorCode);
    Dcm_ExternalProcessingDone(pMsgContext);
  }

  return retVal;
}

