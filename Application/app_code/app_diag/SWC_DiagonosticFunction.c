/*******************************************************************************
**                       HYUNDAI-AUTOEVER PVT LTD                             **
********************************************************************************
** Copyright (C) HYUNDAI-AUTOEVER PVT LTD - All Rights Reserved               **
** Unauthorized copying of this file, via any medium is strictly prohibited   **
** Auto generated file                                                        **
*******************************************************************************/
/* Generate On : �� 5�� 23 2022 12:19:17 KST                                    */
/* Generate from : Y:/01_SWP_Backup/kkh_backup/e_ka4_pe_wpc_v200_220519_1     */
/* Code Generation Version : 1.0.2                                            */

#include "Rte_SWC_WPC_Process.h"
#include "Rte_Dcm_Type.h"
#include "Dcm_Types.h"
#include "WPCVehicleOption.h"
/* PROTECTED REGION START ID(User Defined File Inclusion):(SWC_WPC_Process) */
/* Start of user defined code  - Do not remove this comment */
#include "WPCType.h"
#include "Define.h"
#include "WPCTimer.h"
#include "Data.h"

#include "app_input_type.h"
#include "app_input.h"
#include "app_can_input_type.h"
#include "app_can_input.h"

#include "app_output_type.h"
#include "app_output.h"
#include "app_can_output_type.h"
#include "app_can_output.h"

#include "App_NvM_RamBlock.h"

#include "WPCInitialization.h"
#include "WPCI2CControl.h"
#include "WPCEepControl.h"
#include "WPCLogicControl.h"
#include "WPCOutput.h"

#include "WPCSleepControl.h"
#include "Rte_SWC_AppMode_Type.h"
#include "SlpWup.h"

#if defined (JX1_PE_R)
static u8 RXSWIN_DATA[] = {
	0x07, 0x24,																		/* CAN TX ID */	
	0x0B, 'R','1','0',	  ' ','J','X','1','/','1','/','0',							/* INDEX 0 */
	0x0C, 'R','1','5','5',' ','J','X','1','/','1','/','0',							/* INDEX 1 */
	0x0C, 'R','1','5','6',' ','J','X','1','/','1','/','0',							/* INDEX 2 */
};
#elif defined (RG3_PE_R) || defined (RG3_PE_EV_R)
static u8 RXSWIN_DATA[] = {
	0x07, 0x24,																		/* CAN TX ID */	
	0x0B, 'R','1','0',	  ' ','R','G','3','/','1','/','0',							/* INDEX 0 */
	0x0C, 'R','1','5','5',' ','R','G','3','/','1','/','0',							/* INDEX 1 */
	0x0C, 'R','1','5','6',' ','R','G','3','/','1','/','0',							/* INDEX 2 */
};
#endif
extern uint16 APP_BAT_Source;
extern uint16 APP_IGN_Source;
extern uint8 b_BlinkState;
extern uint8 b_UpdateFlashCmd;
extern uint8 SessionNontify;
extern uint8 f_ComMModeState_BCAN; 

/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined File Inclusion):(SWC_WPC_Process) */

/* PROTECTED REGION START ID(User Defined Constants):(SWC_WPC_Process) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Constants):(SWC_WPC_Process) */

/* PROTECTED REGION START ID(User Defined Global Variables):(SWC_WPC_Process) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Global Variables):(SWC_WPC_Process) */


#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_VehicleManufacturerSparePartNumberDataIdentifier_0xF187(OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data) 
{
	/* 0xF187 - VehicleManufacturerSparePartNumberDataIdentifier */

	Std_ReturnType retVal = RTE_E_OK;

	Data[0] = ECU_Read.PartNumber[0];
	Data[1] = ECU_Read.PartNumber[1];
	Data[2] = ECU_Read.PartNumber[2];
	Data[3] = ECU_Read.PartNumber[3];
	Data[4] = ECU_Read.PartNumber[4];
	Data[5] = ECU_Read.PartNumber[5];
	Data[6] = ECU_Read.PartNumber[6];
	Data[7] = ECU_Read.PartNumber[7];
	Data[8] = ECU_Read.PartNumber[8];
	Data[9] = ECU_Read.PartNumber[9];
	
	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_VehicleManufacturerSparePartNumberDataIdentifier_0xF187_CC(OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode) 
{
	/* 0xF187 - VehicleManufacturerSparePartNumberDataIdentifier ConditionCheckRead */

	Std_ReturnType retVal = RTE_E_OK;

	*ErrorCode = DCM_E_POSITIVERESPONSE;

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_ECUManufacturingDateDataIdentifier_0xF18B(OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data) 
{
	/* 0xF18B - ECUManufacturingDateDataIdentifier */

	Std_ReturnType retVal = RTE_E_OK;
	
	Data[0] = Get_EepromData_FACTORY_MD(0);
	Data[1] = Get_EepromData_FACTORY_MD(1);
	Data[2] = Get_EepromData_FACTORY_MD(2);
	Data[3] = Get_EepromData_FACTORY_MD(3);

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_ECUManufacturingDateDataIdentifier_0xF18B_CC(OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode) 
{
	/* 0xF18B - ECUManufacturingDateDataIdentifier ConditionCheckRead */

	Std_ReturnType retVal = RTE_E_OK;

	*ErrorCode = DCM_E_POSITIVERESPONSE;

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_ECUSerialNumberDataIdentifier_0xF18C(OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data) 
{
	/* 0xF18C - ECUSerialNumberDataIdentifier : 15 bytes */

	Std_ReturnType retVal = RTE_E_OK;
	
	Data[0] = Get_EepromData_FACTORY_SN(0);
	Data[1] = Get_EepromData_FACTORY_SN(1);
	Data[2] = Get_EepromData_FACTORY_SN(2);
	Data[3] = Get_EepromData_FACTORY_SN(3);
	Data[4] = Get_EepromData_FACTORY_SN(4);
	Data[5] = Get_EepromData_FACTORY_SN(5);
	Data[6] = Get_EepromData_FACTORY_SN(6);
	Data[7] = Get_EepromData_FACTORY_SN(7);
	Data[8] = Get_EepromData_FACTORY_SN(8);
	Data[9] = Get_EepromData_FACTORY_SN(9);
	Data[10] = Get_EepromData_FACTORY_SN(10);
	Data[11] = Get_EepromData_FACTORY_SN(11);
	Data[12] = Get_EepromData_FACTORY_SN(12);
	Data[13] = Get_EepromData_FACTORY_SN(13);
	Data[14] = Get_EepromData_FACTORY_SN(14);

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_ECUSerialNumberDataIdentifier_0xF18C_CC(OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode) 
{
	/* 0xF18C - ECUSerialNumberDataIdentifier ConditionCheckRead */

	Std_ReturnType retVal = RTE_E_OK;

	*ErrorCode = DCM_E_POSITIVERESPONSE;

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_ECUSupplierCodeDataIdentifier_0xF1A1(OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data) 
{
	/* 0xF1A1 - ECUSupplierCodeDataIdentifier : MOBASE ELECTRONICS: S110 -> 0x53 31 31 30  */

	Std_ReturnType retVal = RTE_E_OK;

	Data[0] = ECU_Read.CorpCode[0];
	Data[1] = ECU_Read.CorpCode[1];
	Data[2] = ECU_Read.CorpCode[2];
	Data[3] = ECU_Read.CorpCode[3];

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"


#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_ECUSupplierCodeDataIdentifier_0xF1A1_CC(OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode) 
{
	/* 0xF1A1 - ECUSupplierCodeDataIdentifier ConditionCheckRead */
	
	Std_ReturnType retVal = RTE_E_OK;

	*ErrorCode = DCM_E_POSITIVERESPONSE;

	return retVal;

}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_ECUSoftwareUNITnumberDataIdentifier_0xF1B0(OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data) 
{
	/* 0xF1B0 - ECUSoftwareUNITnumberDataIdentifier : 1byte */

	Std_ReturnType retVal = RTE_E_OK;

	Data[0] = 0x01;
	
	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_ECUSoftwareUNITnumberDataIdentifier_0xF1B0_CC(OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode) 
{
	/* 0xF1B0 - ECUSoftwareUNITnumberDataIdentifier ConditionCheckRead */

	Std_ReturnType retVal = RTE_E_OK;

	*ErrorCode = DCM_E_POSITIVERESPONSE;

	return retVal;

}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_ECUSoftwareUNIT1VersionDataIdentifier_0xF1B1(OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)		/* SCR-210824-003 : WPC Version DID 3Byte -> 4Byte */ 
{
	/* 0xF1B1 - ECUSoftwareUNIT1VersionDataIdentifier */

	Std_ReturnType retVal = RTE_E_OK;

	Data[0] = ECU_Read.SWVer[0];
	Data[1] = ECU_Read.SWVer[1];
	Data[2] = ECU_Read.SWVer[2];
	Data[3] = ECU_Read.SWVer[3];

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_ECUSoftwareUNIT1VersionDataIdentifier_0xF1B1_CC(OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode) 
{
	/* 0xF1B1 - ECUSoftwareUNIT1VersionDataIdentifier ConditionCheckRead */

	Std_ReturnType retVal = RTE_E_OK;

	*ErrorCode = DCM_E_POSITIVERESPONSE;

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_VehicleManufacturerECUHardwareNumberDataIdentifier_0xF191(OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)		/* SCR-210824-003 : WPC Version DID 3Byte -> 4Byte */ 
{
	/* 0xF191 - VehicleManufacturerECUHardwareNumberDataIdentifier */

	Std_ReturnType retVal = RTE_E_OK;

	Data[0] = ECU_Read.HWVer[0];
	Data[1] = ECU_Read.HWVer[1];
	Data[2] = ECU_Read.HWVer[2];
	Data[3] = ECU_Read.HWVer[3];

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_VehicleManufacturerECUHardwareNumberDataIdentifier_0xF191_CC(OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode) 
{
	/* 0xF191 - VehicleManufacturerECUHardwareNumberDataIdentifier ConditionCheckRead */

	Std_ReturnType retVal = RTE_E_OK;

	*ErrorCode = DCM_E_POSITIVERESPONSE;

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_SystemSupplierECUHardwareVersionNumberDataIdentifier_0xF193(OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)		/* SCR-210824-003 : WPC Version DID 3Byte -> 4Byte */ 
{
	/* 0xF193 - SystemSupplierECUHardwareVersionNumberDataIdentifier  */

	Std_ReturnType retVal = RTE_E_OK;

	Data[0] = ECU_Read.HWVer[0];
	Data[1] = ECU_Read.HWVer[1];
	Data[2] = ECU_Read.HWVer[2];
	Data[3] = ECU_Read.HWVer[3];

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_SystemSupplierECUHardwareVersionNumberDataIdentifier_0xF193_CC(OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode) 
{
	/* 0xF193 - SystemSupplierECUHardwareVersionNumberDataIdentifier ConditionCheckRead */

	Std_ReturnType retVal = RTE_E_OK;

	*ErrorCode = DCM_E_POSITIVERESPONSE;

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_CANDataBaseVersionNumberDataIdentifier_0xF100(OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)		/* SCR-210824-003 : WPC Version DID 3Byte -> 4Byte */ 
{
	/* 0xF100 - CANDataBaseVersionNumberDataIdentifier  */

	Std_ReturnType retVal = RTE_E_OK;

	Data[0] = ECU_Read.DBVer[0];
	Data[1] = ECU_Read.DBVer[1];
	Data[2] = ECU_Read.DBVer[2];
	Data[3] = ECU_Read.DBVer[3];

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_CANDataBaseVersionNumberDataIdentifier_0xF100_CC(OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode) 
{
	/* 0xF100 - CANDataBaseVersionNumberDataIdentifier ConditionCheckRead */

	Std_ReturnType retVal = RTE_E_OK;

	*ErrorCode = DCM_E_POSITIVERESPONSE;

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_ReadECUIdentificationLocalRXSWINDataIdentifier_0xF1EF(IN VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)	/* SCR-210524-007 RXSWIN Diag */ 
{
	Std_ReturnType LddRetVal = E_NOT_OK;
	uint8 i=0u;
	uint32	DataLength = 0u;
	u8 NumberOfData = 0u;
	
	static tTimer32	tmr_RXSWINData_Check;

	DataLength = sizeof(RXSWIN_DATA);

	UpTimer32(tmr_RXSWINData_Check);

	switch(OpStatus)
	{
		case DCM_INITIAL:
			StartTimer(tmr_RXSWINData_Check);
			LddRetVal = DCM_E_PENDING;
			break;

		case DCM_PENDING:
			for(i=0u; i<=DataLength; i++)
			{
				Data[i] = RXSWIN_DATA[i];
				NumberOfData++;
			}

			if(tmr_RXSWINData_Check.time>=Time_sec(60u))
			{
				CancelTimer(tmr_RXSWINData_Check);
				LddRetVal = RTE_E_INVALID;
			}
			else if(NumberOfData>=DataLength)
			{
				CancelTimer(tmr_RXSWINData_Check);
				LddRetVal = RTE_E_OK;
			}
			else
			{
				LddRetVal = DCM_E_PENDING;
			}
			break;

		case DCM_CANCEL:
			/* MISRA-C */
			break;
		default:
			/* MISRA-C */
			break;
	}
	
	return LddRetVal;		
}
	
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"


#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_ReadECUIdentificationLocalRXSWINDataIdentifier_0xF1EF_CC(IN VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode) 
{
	Std_ReturnType LddRetVal = E_NOT_OK;
		
	switch(OpStatus)
	{
		case DCM_INITIAL:
			LddRetVal = RTE_E_OK;
			*ErrorCode = DCM_E_POSITIVERESPONSE;
			break;

		case DCM_PENDING:
			break;

		case DCM_CANCEL:
			*ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
			break;
		default:
			*ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
			break;
	}
	
	return LddRetVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_ECUSoftwareUnit1IVDDataIdentifier_0xF1C1(IN VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)		/* SCR-211108-003 Output hash value when requesting IVD */
{
#if 1
	Std_ReturnType LddRetVal = RTE_E_OK;
	uint8 i;

	switch(OpStatus)
	{
		case DCM_INITIAL:
			
			for(i=0u; i<32u; i++)
			{
				Data[i] = Diag_HashData[i];
			}
			LddRetVal = RTE_E_OK;
			break;
		case DCM_PENDING:
			/* MISRA-C */
			break;
		case DCM_CANCEL:
			/* MISRA-C */
			break;
		default:
			/* MISRA-C */
			break;
	}

	return LddRetVal;

#endif	
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_ECUSoftwareUnit1IVDDataIdentifier_0xF1C1_CC(IN VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode) 
{
#if 1
	Std_ReturnType LddRetVal = RTE_E_OK;

	switch(OpStatus)
	{
		case DCM_INITIAL:
			if( (Hash_Calculation_Check==Off) && (GetX(kb_IGN_IN)==On) )
			{ /* Hash(IVD) Calculating */
				LddRetVal = DCM_E_PENDING;
				*ErrorCode = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
			}
			else if( (Hash_Calculation_Check==Off) && (GetX(kb_IGN_IN)==Off) )
			{ /* Hash(IVD) Calculating */
				LddRetVal = RTE_E_DataServices_ECUSoftwareUnit1IVDDataIdentifier_0xF1C1_E_NOT_OK;
				*ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
			}	
			else if( (Hash_Calculation_Check==On) && (GetX(kb_IGN_IN)==On) )
			{
				LddRetVal = RTE_E_OK;
				*ErrorCode = DCM_E_POSITIVERESPONSE;
			}
			else
			{
				LddRetVal = DCM_E_PENDING;
				*ErrorCode = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
			}
			break;
		case DCM_PENDING:
			if( (Hash_Calculation_Check==Off) && (GetX(kb_IGN_IN)==On) )
			{ /* Hash(IVD) Calculating */
				LddRetVal = DCM_E_PENDING;
				*ErrorCode = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
			}
			else if( (Hash_Calculation_Check==Off) && (GetX(kb_IGN_IN)==Off) )
			{ /* Hash(IVD) Calculating */
				LddRetVal = RTE_E_DataServices_ECUSoftwareUnit1IVDDataIdentifier_0xF1C1_E_NOT_OK;
				*ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
			}	
			else if( (Hash_Calculation_Check==On) && (GetX(kb_IGN_IN)==On) )
			{
				LddRetVal = RTE_E_OK;
				*ErrorCode = DCM_E_POSITIVERESPONSE;
			}
			else
			{
				LddRetVal = DCM_E_PENDING;
				*ErrorCode = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
			}
			break;
		case DCM_CANCEL:
			/* MISRA-C */
			break;
		default:
			/* MISRA-C */
			break;
	}

	return LddRetVal;
#endif
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_WDBI_Factory_SerialNumber_0x12A3(IN P2CONST(uint8, AUTOMATIC, RTE_APPL_DATA) Data, OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode) 
{
	/* Manufacturing SerialNumber */

	Std_ReturnType retVal = RTE_E_OK;
	
	Set_EepromData_FACTORY_SN((u8)kFactory_ECUSerialNumber, Data[0]);
	Set_EepromData_FACTORY_SN((u8)kFactory_ECUSerialNumber+1u, Data[1]);
	Set_EepromData_FACTORY_SN((u8)kFactory_ECUSerialNumber+2u, Data[2]);
	Set_EepromData_FACTORY_SN((u8)kFactory_ECUSerialNumber+3u, Data[3]);
	Set_EepromData_FACTORY_SN((u8)kFactory_ECUSerialNumber+4u, Data[4]);
	Set_EepromData_FACTORY_SN((u8)kFactory_ECUSerialNumber+5u, Data[5]);
	Set_EepromData_FACTORY_SN((u8)kFactory_ECUSerialNumber+6u, Data[6]);
	Set_EepromData_FACTORY_SN((u8)kFactory_ECUSerialNumber+7u, Data[7]);
	Set_EepromData_FACTORY_SN((u8)kFactory_ECUSerialNumber+8u, Data[8]);
	Set_EepromData_FACTORY_SN((u8)kFactory_ECUSerialNumber+9u, Data[9]);
	Set_EepromData_FACTORY_SN((u8)kFactory_ECUSerialNumber+10u, Data[10]);
	Set_EepromData_FACTORY_SN((u8)kFactory_ECUSerialNumber+11u, Data[11]);
	Set_EepromData_FACTORY_SN((u8)kFactory_ECUSerialNumber+12u, Data[12]);
	Set_EepromData_FACTORY_SN((u8)kFactory_ECUSerialNumber+13u, Data[13]);
	Set_EepromData_FACTORY_SN((u8)kFactory_ECUSerialNumber+14u, Data[14]);

	*ErrorCode = DCM_E_POSITIVERESPONSE;

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_WDBI_ManufacturingDate_0x12A4(IN P2CONST(uint8, AUTOMATIC, RTE_APPL_DATA) Data, OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode) 
{
	/* Manufacturing Date */

	Std_ReturnType retVal = RTE_E_OK;

	Set_EepromData_FACTORY_MD((u8)kFactory_ManufacturingDate, Data[0]);
	Set_EepromData_FACTORY_MD((u8)kFactory_ManufacturingDate+1u, Data[1]);
	Set_EepromData_FACTORY_MD((u8)kFactory_ManufacturingDate+2u, Data[2]);
	Set_EepromData_FACTORY_MD((u8)kFactory_ManufacturingDate+3u, Data[3]);

	*ErrorCode = DCM_E_POSITIVERESPONSE;

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_ECUSoftwareInternalVersion_0xF189(OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data) 
{
	Std_ReturnType retVal = RTE_E_OK;

	Data[0] = ECU_Read.SWVer[0];
	Data[1] = ECU_Read.SWVer[1];
	Data[2] = ECU_Read.SWVer[2];
	Data[3] = ECU_Read.SWVer[3];
	Data[4] = ECU_Read.SWInVer[0];
	Data[5] = ECU_Read.SWInVer[1];
	Data[6] = ECU_Read.SWInVer[2];

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_ECUSoftwareInternalVersion_0xF189_CC(OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode) 
{
	Std_ReturnType retVal = RTE_E_OK;
	
	*ErrorCode = DCM_E_POSITIVERESPONSE;

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_ChargingECUSoftwareVersionMobase_0xF101(OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data) 
{
	/* 0xF101 - ChargingECUSoftwareVersion Mobase : P9261 Version  */

	Std_ReturnType retVal = RTE_E_OK;

	Data[0] = ECU_Read.SubSWVer[0];
	Data[1] = ECU_Read.SubSWVer[1];
	Data[2] = ECU_Read.SubSWVer[2];
	Data[3] = ECU_Read.SubSWVer[3];
	Data[4] = ECU_Read.SubSWVer[4];
	Data[5] = ECU_Read.SubSWVer[5];

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_ChargingECUSoftwareVersionMobase_0xF101_CC(OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode) 
{
	/* 0xF101 - ChargingECUSoftwareVersion Mobase ConditionCheckRead : P9261 Version  */

	Std_ReturnType retVal = RTE_E_OK;

	*ErrorCode = DCM_E_POSITIVERESPONSE;

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_UserOptionRecordLocalIdentifier_0xBE01(OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data) 
{
	Std_ReturnType retVal = RTE_E_OK;
	
	Data[0] = 0xF0u;	/* Supported PID */
	Data[1] = 0x00u;	/* Supported PID */
	Data[2] = 0x00u;	/* Supported PID */
	Data[3] = 0x00u;	/* Supported PID */
	Data[4] = 0x00u;	/*  */
	Data[5] = 0x00u;	/*  */
	Data[6] = 0x00u;	/*  */
	Data[7] = 0x00u;	/*  */

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_UserOptionRecordLocalIdentifier_0xBE01_CC(OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode) 
{


	Std_ReturnType retVal = RTE_E_OK;

	*ErrorCode = DCM_E_POSITIVERESPONSE;

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_InputOutputRecordLocalIdentifier_0xBE02(OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data) 
{

	Std_ReturnType retVal = RTE_E_OK;
	uint8	FanDuty = 0u;
	float32 Charging_Voltage = 0;
	float32 Charging_Current = 0;
	float32 Charging_Power = 0;
	
	Charging_Voltage = (float32)GetTxData_chargingcoilvol() / (float32)1000;
	Charging_Current = (float32)GetTxData_chargingcoilcurr() / (float32)1000;
	Charging_Power = Charging_Voltage * Charging_Current;
		
	Data[0] = 0xFEu;	/* Supported PID */
	Data[1] = 0x40u;	/* Supported PID */
	Data[2] = 0x00u;	/* Supported PID */
	Data[3] = 0x00u;	/* Supported PID */
	Data[4] = (uint8)(Charging_Voltage / 0.08f);	/* Charging Voltage : 0.08 * X [V] : 0 ~ 20.4 V */
	Data[5] = (uint8)(Charging_Current / 0.0393f);	/* Charging Current : 0.0393 * X [A] : 0 ~ 8.415 A */
	Data[6] = (uint8)(Charging_Power / 0.196f);	/* Charging Power : 0.196 * X [W] : 0 ~ 49.98 W */	
	//Data[7] = (uint8)(((float32)APP_BAT_Source * 0.01968f) / 0.08f);	/* BAT+ Voltage : 0.08 * X [V] : 0 ~ 20.4 V */
	//Data[8] = (uint8)(((float32)APP_IGN_Source * 0.01968f) / 0.08f); /* IGN Voltage : 0.08 * X [V] : 0 ~ 20.4 V */
	Data[7] = (uint8)(((float32)APP_BAT_Source * 0.004882f) / 0.08f);	/* BAT+ Voltage : 0.08 * X [V] : 0 ~ 20.4 V */
	Data[8] = (uint8)(((float32)APP_IGN_Source * 0.004882f) / 0.08f); /* IGN Voltage : 0.08 * X [V] : 0 ~ 20.4 V */
	Data[9] = GetTxData_selectedcoil();	/* Coil Temperature 1(0) */
	Data[10] = GetTxData_CoilTempN_UDS(1u);	/* Coil Temperature 1(0) */
	Data[11] = GetTxData_CoilTempN_UDS(2u); /* Coil Temperature 2(1) */
	Data[12] = GetTxData_CoilTempN_UDS(3u); /* Coil Temperature 3(2) */
	FanDuty = GetX(kb_FAN_PWM);
	if(FanDuty == Par_FANValueLow) {Data[13] = Par_FANValueLow;}	/* 20% */
	else if((FanDuty == Par_FANValueMedium) || (tbl_ForcedDrive_WPC[5u].status == On)) {Data[13] = Par_FANValueMedium;} /* 50% */
	else if(FanDuty == Par_FANValueHigh) {Data[13] = Par_FANValueHigh;}	/* 70% */
	else {Data[13] = 0u;}

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_InputOutputRecordLocalIdentifier_0xBE02_CC(OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode) 
{
	Std_ReturnType retVal = RTE_E_OK;

	*ErrorCode = DCM_E_POSITIVERESPONSE;

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_InputOutputRecordLocalIdentifier_0xBE03(OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data) 
{
	Std_ReturnType retVal = RTE_E_OK;
	uint8 DID_BE03 = 0u;

	Data[0] = 0xF6u;		/* Supported PID */
	Data[1] = 0x00u;		/* Supported PID */
	Data[2] = 0x00u;		/* Supported PID */
	Data[3] = 0x00u;		/* Supported PID */

	if(GetX(kb_IGN_IN) == On) {DID_BE03 = DID_BE03 | 0x01u;}						/* Bit0 : IGN1 : 0=Off, 1=On */
	if((GetOutput(kC_WPC_PhnLftWrngRWPCSta) == (u8)kWPCWarning_Charging) ||
	   ((GetOutput(kC_WPC_PhnLftWrngRWPCSta) != (u8)kWPCWarning_Error) &&
	   (GetOutput(kL_Amber_OUT) == On))) {DID_BE03 = DID_BE03 | 0x02u;}				/* Bit1 : Amber LED On/Off Status : 0=Off, 1=On */
	if((GetOutput(kC_WPC_PhnLftWrngRWPCSta) == (u8)kWPCWarning_Error) &&
	   (b_BlinkState != (u8)Blink_State_Complete)) {DID_BE03 = DID_BE03 | 0x04u;} 	/* Bit2 : Amber Blinking Status : 0=Off, 1=Blinking */  
	if((GetOutput(kC_WPC_PhnLftWrngRWPCSta) == (u8)kWPCWarning_ChargingComplete) ||
	   (GetOutput(kL_Green_OUT) == On)) {DID_BE03 = DID_BE03 | 0x08u;}				/* Bit3 : Green LED On/Off Status : 0=Off, 1=On */
	/* Bit4 : SMK LF Searching Signal Status : 0=Off, 1=On : Local Input signal is not used : Off */
	/* Bit5~6 : Charging Status : 0=Charging Off, 1=Charging, 2=Charging Complete, 3=Invlid */   
	if(GetX(kb_DeviceState) == (u8)DeviceStates_Charging)	{DID_BE03 = DID_BE03 | 0x20u;}
	else if(GetX(kb_DeviceState) == (u8)DeviceStates_Full_Charge) {DID_BE03 = DID_BE03 | 0x40u;}
	else { /* MISRA CODING RULE */ }
	Data[4] = DID_BE03;   
	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_InputOutputRecordLocalIdentifier_0xBE03_CC(OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode) 
{

	Std_ReturnType retVal = RTE_E_OK;

	*ErrorCode = DCM_E_POSITIVERESPONSE;

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) OTAReady_Start_0x0300(IN VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, OUT P2VAR(StartDataOutType_RID_0300h_OTAReady_Out_RoutineStatus, AUTOMATIC, RTE_APPL_DATA) DataOut_Out_RoutineStatus, OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
	Std_ReturnType LddRetVal = RTE_E_OK;
	switch(OpStatus)
	{
		case DCM_INITIAL:
			LddRetVal = RTE_E_OK;
			*DataOut_Out_RoutineStatus = 0x01;
			*ErrorCode = DCM_E_POSITIVERESPONSE;
			break;
		case DCM_PENDING:
		case DCM_CANCEL:
		default:
			/* MISRA-C */
			break;
	}
	return LddRetVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) SystemName_0xF197_CC(OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
	Std_ReturnType retVal = RTE_E_OK;
	*ErrorCode = DCM_E_POSITIVERESPONSE;
	return retVal;
}

#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) SystemName_0xF197(OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
	Std_ReturnType retVal = RTE_E_OK;
	
	Data[0] = ECU_Read.SystemName[0];
	Data[1] = ECU_Read.SystemName[1];
	Data[2] = ECU_Read.SystemName[2];
	Data[3] = ECU_Read.SystemName[3];

	return retVal;
}

#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) PlatformHardwareVersion_0xF17D_CC(OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
	Std_ReturnType retVal = RTE_E_OK;
	*ErrorCode = DCM_E_POSITIVERESPONSE;
	return retVal;
}

#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) PlatformHardwareVersion_0xF17D(OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
	Std_ReturnType retVal = RTE_E_OK;
	
	Data[0] =  ECU_Read.PlatHWVer[0];
	Data[1] =  ECU_Read.PlatHWVer[1];
	Data[2] =  ECU_Read.PlatHWVer[2];
	Data[3] =  ECU_Read.PlatHWVer[3];
	Data[4] =  ECU_Read.PlatHWVer[4];
	Data[5] =  ECU_Read.PlatHWVer[5];
	Data[6] =  ECU_Read.PlatHWVer[6];
	Data[7] =  ECU_Read.PlatHWVer[7];
	Data[8] =  ECU_Read.PlatHWVer[8];
	Data[9] =  ECU_Read.PlatHWVer[9];
	Data[10] = ECU_Read.PlatHWVer[10];

	return retVal;
}

#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) PlatformVersion_0xF17F_CC(OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
	Std_ReturnType retVal = RTE_E_OK;
	*ErrorCode = DCM_E_POSITIVERESPONSE;
	return retVal;
}

#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) PlatformVersion_0xF17F(OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
	Std_ReturnType retVal = RTE_E_OK;
	
	Data[0] =  ECU_Read.PlatVer[0];
	Data[1] =  ECU_Read.PlatVer[1];
	Data[2] =  ECU_Read.PlatVer[2];
	Data[3] =  ECU_Read.PlatVer[3];
	Data[4] =  ECU_Read.PlatVer[4];
	Data[5] =  ECU_Read.PlatVer[5];
	Data[6] =  ECU_Read.PlatVer[6];
	Data[7] =  ECU_Read.PlatVer[7];
	Data[8] =  ECU_Read.PlatVer[8];
	Data[9] =  ECU_Read.PlatVer[9];
	Data[10] = ECU_Read.PlatVer[10];

	return retVal;
}

#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

static uint8 FD_index_FD_B2CAN = On;  
static uint8 FD_index_Local_CAN = Off;
static uint8 FD_index_Local_CAN_2 = Off;
static uint8 FD_index_ECU_Internal = On;
static uint8 FD_index_HW_Input = On;
static uint8 FD_index_Network_Condition = On;
FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_NonSleepCollectedEachEcuDataIdentifier_0xED90 (OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
	Std_ReturnType retVal = RTE_E_OK;

	uint8 FD_index_0BYTE = 0u;
	uint8 FD_B2CAN_0BYTE = 0u;
	uint8 FD_B2CAN_1BYTE = 0u;
	uint8 FD_B2CAN_2BYTE = 0u;
	uint8 FD_B2CAN_3BYTE = 0u;
	uint8 LCAN_0BYTE = 0u;
	uint8 LCAN_1BYTE = 0u;
	uint8 LCAN2_0BYTE = 0u;
	uint8 LCAN2_1BYTE = 0u;
	uint8 ECU_Internal_0BYTE = 0u;
	uint8 ECU_Internal_1BYTE = 0u;
	uint8 ECU_Internal_2BYTE = 0u;
	uint8 ECU_Internal_3BYTE = 0u;
	uint8 HW_Input_0BYTE = 0u;
	uint8 Network_Condition_0BYTE = 0u;
	if(FD_index_FD_B2CAN == On) {FD_index_0BYTE = FD_index_0BYTE | 0x01u;}			/* Off */
	if(FD_index_ECU_Internal == On) {FD_index_0BYTE = FD_index_0BYTE | 0x08u;}		/* On */
	if(FD_index_HW_Input == On) {FD_index_0BYTE = FD_index_0BYTE | 0x10u;}			/* On */
	if(FD_index_Network_Condition == On) {FD_index_0BYTE = FD_index_0BYTE | 0x20u;}	/* On */
	else { /* MISRA CODING RULE */ }
	Data[0] = FD_index_0BYTE;

	if(GetX(kC_AccInSta) == On) {FD_B2CAN_0BYTE = FD_B2CAN_0BYTE | 0x01u;}                        	/* Bit0 : ACC : 0=Off, 1=On */
	if(GetX(kC_Ign1Insta) == On) {FD_B2CAN_0BYTE = FD_B2CAN_0BYTE | 0x02u;}                       	/* Bit1 : IGN1 : 0=Off, 1=On */
	if(GetX(kC_Warn_DrvDrSwSta) == (u8)kDoorSw_Open) {FD_B2CAN_0BYTE = FD_B2CAN_0BYTE | 0x04u;}     /* Bit2 : Drive Door : 0=Off, 1=On */
	if(GetX(kC_Warn_AsstDrSwSta) == (u8) kDoorSw_Open) {FD_B2CAN_0BYTE = FD_B2CAN_0BYTE | 0x08u;} 	/* Bit3 : Asist Door : 0=Off, 1=On */
	if(GetX(kC_Warn_RrLftDrSwSta) == (u8)kDoorSw_Open) {FD_B2CAN_0BYTE = FD_B2CAN_0BYTE | 0x10u;} 	/* Bit4 : Rear Left Door : 0=Off, 1=On */
	if(GetX(kC_Warn_RrRtDrSwSta) == (u8) kDoorSw_Open) {FD_B2CAN_0BYTE = FD_B2CAN_0BYTE | 0x20u;} 	/* Bit5 : Rear Right Door : 0=Off, 1=On */
	if(GetX(kC_CLU_AutoBrightSta) != 0u) {FD_B2CAN_0BYTE = FD_B2CAN_0BYTE | 0x40u;}               	/* Bit6 : AutoBrightValue : 0=Off, 1=On */
	if(GetX(kC_BCM_SmkOptTyp) == On) {FD_B2CAN_0BYTE = FD_B2CAN_0BYTE | 0x80u;}                   	/* Bit7 : SMKOption : 0=Off, 1=On */
	else { /* MISRA CODING RULE */ }
	Data[1] = FD_B2CAN_0BYTE;
	Data[2] = FD_B2CAN_1BYTE;
	Data[3] = FD_B2CAN_2BYTE;
	Data[4] = FD_B2CAN_3BYTE;
	Data[5] = LCAN_0BYTE;
    Data[6] = LCAN_1BYTE;
    Data[7] = LCAN2_0BYTE;
    Data[8] = LCAN2_1BYTE;

	if(GetX(kC_WPCDiagState) == Off) {ECU_Internal_0BYTE = ECU_Internal_0BYTE | 0x1u;}						/* Bit0 : UDS LP Condition : 0=logic is in High Power Mode, 1=logic is in Low Power Mode */
	if(u8_Sleep_Flag[WPC_SLEEP_LP_FLAG] == LP_OK)	{ECU_Internal_0BYTE = ECU_Internal_0BYTE | 0x02u;}		/* Bit1 : WPC LP Condition : 0=logic is in High Power Mode, 1=logic is in Low Power Mode */
	if(GetX(kb_WPCPower) == Off) {ECU_Internal_0BYTE = ECU_Internal_0BYTE | 0x4u;}						    /* Bit2 : WCT LP Condition : 0=logic is in High Power Mode, 1=logic is in Low Power Mode */
  	if((stateNFC == stsNFC_Init) || (stateNFC == stsNFC_Deactivated)) {ECU_Internal_0BYTE = ECU_Internal_0BYTE | 0x08u;}					/* Bit3 : NFC LP Condition : 0=logic is in High Power Mode, 1=logic is in Low Power Mode */
	Data[9] = ECU_Internal_0BYTE;
	Data[10] = ECU_Internal_1BYTE;
	Data[11] = ECU_Internal_2BYTE;
	Data[12] = ECU_Internal_3BYTE;

	if(GetX(kb_IGN_IN) == On) {HW_Input_0BYTE = HW_Input_0BYTE | 0x01u;}		/* Bit0 : 0x0:Off, 0x1:On*/
	else { /* MISRA CODING RULE */ }
	Data[13] = HW_Input_0BYTE;

	if((SessionNontify == kDefaultSession_NoSec)     ||
	   (SessionNontify == kProgrammingSession_NoSec) ||
	   (SessionNontify == kExtendedSession_NoSec)    ||
	   (SessionNontify == kSafetySystemSession_Nosec)) { Network_Condition_0BYTE = Network_Condition_0BYTE | 0x01;}	          /* 0x0:Off(inactive), 0x1:On(active) */
	if(f_ComMModeState_BCAN == RTE_MODE_MDG_ComMMode_FULL_COM) {Network_Condition_0BYTE = Network_Condition_0BYTE | 0x04;} /*Bit2 : CAN Wake up */        /* 0x0:Off(inactive), 0x1:On(active) */
	Data[14] = Network_Condition_0BYTE;

	return retVal;
}
#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

#define SWC_WPC_Process_START_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

FUNC(Std_ReturnType, SWC_WPC_Process_CODE) RE_NonSleepCollectedEachEcuDataIdentifier_0xED90_CC(OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType retVal = RTE_E_OK;
  *ErrorCode = DCM_E_POSITIVERESPONSE;
  return retVal;
}

#define SWC_WPC_Process_STOP_SEC_CODE
#include "SWC_WPC_Process_MemMap.h"

