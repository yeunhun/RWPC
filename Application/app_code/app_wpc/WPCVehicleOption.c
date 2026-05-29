/****************************************************************************************
* Project         :	WPC																	*
* File Name       : 																	*
* Compiler        : IAR																	*
* Author          : Limjo Hong								                            *
* Created at      : 2018-05-25			                                                *
* Code Editor     : Source Insight														*
* Revision        : 0.1																	*
* Copyright       : (c) Copyright Seoyon Electronics Co.Ltd. All Rights Reserved		*
* Description     : Mass production																	*
****************************************************************************************/

#include "WPCType.h"
#include "data.h"
#include "WPCVehicleOption.h"


ECUData ECU_Read;


#if defined(USE_CHARGE_IC_FWver_READ)
void Set_ECU_Read_SubSWVer(uint8 dataArr[4])
{
  ECU_Read.SubSWVer[0] = dataArr[0];
  ECU_Read.SubSWVer[1] = dataArr[1];
  ECU_Read.SubSWVer[2] = dataArr[2];
  ECU_Read.SubSWVer[3] = dataArr[3];
  ECU_Read.SubSWVer[4] = 0x00u;
}
#endif
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
uint8 Get_P9450_Header_Software_Version(uint8 idx);
#endif
void Set_ECU_Identifier(void)
{
	ECU_Read.PartNumber[0] = (u8)'9';
	ECU_Read.PartNumber[1] = (u8)'5';
	ECU_Read.PartNumber[2] = (u8)'5';
	ECU_Read.PartNumber[3] = (u8)'6';
	ECU_Read.PartNumber[4] = (u8)'0';

#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
 #if defined(USE_CHARGE_IC_FWver_READ)
  ECU_Read.SubSWVer[0] = 0x00u;
  ECU_Read.SubSWVer[1] = 0x00u;
  ECU_Read.SubSWVer[2] = 0x00u;
  ECU_Read.SubSWVer[3] = 0x00u;
  ECU_Read.SubSWVer[4] = 0x00u;
 #else
  ECU_Read.SubSWVer[0] = Get_P9450_Header_Software_Version(0u);
  ECU_Read.SubSWVer[1] = Get_P9450_Header_Software_Version(1u);
  ECU_Read.SubSWVer[2] = Get_P9450_Header_Software_Version(2u);
  ECU_Read.SubSWVer[3] = Get_P9450_Header_Software_Version(3u);
  ECU_Read.SubSWVer[4] = Get_P9450_Header_Software_Version(4u);
 #endif
#else
	ECU_Read.SubSWVer[0] = (u8)'C';		
	ECU_Read.SubSWVer[1] = (u8)'0';
	ECU_Read.SubSWVer[2] = (u8)'0';
	ECU_Read.SubSWVer[3] = (u8)'1';
	ECU_Read.SubSWVer[4] = (u8)'4';
#endif

	/* RWPC (JX1_PE_R) :	95560-T6800 UNIT ASSY-Wireless Charging -NFC */
	/* RWPC (JX1_PE_R_Coupe) : 95560-T6800 UNIT ASSY-Wireless Charging -NFC */
#if defined (JX1_PE_R)
	ECU_Read.PartNumber[5] = (u8)'T';
	ECU_Read.PartNumber[6] = (u8)'6';
	ECU_Read.PartNumber[7] = (u8)'8';
	ECU_Read.PartNumber[8] = (u8)'0';
	ECU_Read.PartNumber[9] = (u8)'0';
	/* 1.00 */
	ECU_Read.HWVer[0] = (u8)'1';
	ECU_Read.HWVer[1] = (u8)'.';
	ECU_Read.HWVer[2] = (u8)'0';
	ECU_Read.HWVer[3] = (u8)'0';
	/* 1.30 */
	ECU_Read.SWVer[0] = (u8)'1';
	ECU_Read.SWVer[1] = (u8)'.';
	ECU_Read.SWVer[2] = (u8)'3';
	ECU_Read.SWVer[3] = (u8)'0';
	/* 50 -> 51 */
	ECU_Read.SWInVer[0] = (u8)'.';
	ECU_Read.SWInVer[1] = (u8)'5';
	ECU_Read.SWInVer[2] = (u8)'1';
	/* 1.00 */
	ECU_Read.DBVer[0] = (u8)'1';
	ECU_Read.DBVer[1] = (u8)'.';
	ECU_Read.DBVer[2] = (u8)'0';
	ECU_Read.DBVer[3] = (u8)'0';

	ECU_Read.CorpCode[0] = (u8)'S';
	ECU_Read.CorpCode[1] = (u8)'1';
	ECU_Read.CorpCode[2] = (u8)'1';
	ECU_Read.CorpCode[3] = (u8)'0';

	ECU_Read.SystemName[0] = (u8)'W';
	ECU_Read.SystemName[1] = (u8)'P';
	ECU_Read.SystemName[2] = (u8)'C';
	ECU_Read.SystemName[3] = (u8)' ';
	/* 02.00.00.00 */
	ECU_Read.PlatHWVer[0] =  (u8)'0';
	ECU_Read.PlatHWVer[1] =  (u8)'2';
	ECU_Read.PlatHWVer[2] =  (u8)'.';
	ECU_Read.PlatHWVer[3] =  (u8)'0';
	ECU_Read.PlatHWVer[4] =  (u8)'0';
	ECU_Read.PlatHWVer[5] =  (u8)'.';
	ECU_Read.PlatHWVer[6] =  (u8)'0';
	ECU_Read.PlatHWVer[7] =  (u8)'0';
	ECU_Read.PlatHWVer[8] =  (u8)'.';
	ECU_Read.PlatHWVer[9] =  (u8)'0';
	ECU_Read.PlatHWVer[10] = (u8)'0';
	/* 18.10.00.04 -> 19.10.00.05 */
	ECU_Read.PlatVer[0] =  (u8)'1';
	ECU_Read.PlatVer[1] =  (u8)'9';
	ECU_Read.PlatVer[2] =  (u8)'.';
	ECU_Read.PlatVer[3] =  (u8)'1';
	ECU_Read.PlatVer[4] =  (u8)'0';
	ECU_Read.PlatVer[5] =  (u8)'.';
	ECU_Read.PlatVer[6] =  (u8)'0';
	ECU_Read.PlatVer[7] =  (u8)'0';
	ECU_Read.PlatVer[8] =  (u8)'.';
	ECU_Read.PlatVer[9] =  (u8)'0';
	ECU_Read.PlatVer[10] = (u8)'5';
#endif

#if defined (RG3_PE_R)
	/* RWPC (RG3_PE_R) : 95560-T1900 UNIT ASSY-Wireless Charging -NFC */
	ECU_Read.PartNumber[5] = (u8)'T';
	ECU_Read.PartNumber[6] = (u8)'1';
	ECU_Read.PartNumber[7] = (u8)'9';
	ECU_Read.PartNumber[8] = (u8)'0';
	ECU_Read.PartNumber[9] = (u8)'0';
	/* 1.00 */
	ECU_Read.HWVer[0] = (u8)'1';
	ECU_Read.HWVer[1] = (u8)'.';
	ECU_Read.HWVer[2] = (u8)'0';
	ECU_Read.HWVer[3] = (u8)'0';
	/* 1.40 -> 1.50*/		
	ECU_Read.SWVer[0] = (u8)'1';
	ECU_Read.SWVer[1] = (u8)'.';
	ECU_Read.SWVer[2] = (u8)'5';
	ECU_Read.SWVer[3] = (u8)'0';
	/* 51 -> 50 */	
	ECU_Read.SWInVer[0] = (u8)'.';
	ECU_Read.SWInVer[1] = (u8)'5';
	ECU_Read.SWInVer[2] = (u8)'1';
	/* 1.00 -> 1.20 */	
	ECU_Read.DBVer[0] = (u8)'1';
	ECU_Read.DBVer[1] = (u8)'.';
	ECU_Read.DBVer[2] = (u8)'2';
	ECU_Read.DBVer[3] = (u8)'0';

	ECU_Read.CorpCode[0] = (u8)'S';
	ECU_Read.CorpCode[1] = (u8)'1';
	ECU_Read.CorpCode[2] = (u8)'1';
	ECU_Read.CorpCode[3] = (u8)'0';

	ECU_Read.SystemName[0] = (u8)'W';
	ECU_Read.SystemName[1] = (u8)'P';
	ECU_Read.SystemName[2] = (u8)'C';
	ECU_Read.SystemName[3] = (u8)' ';
	/* 02.00.00.00 */
	ECU_Read.PlatHWVer[0] =  (u8)'0';
	ECU_Read.PlatHWVer[1] =  (u8)'2';
	ECU_Read.PlatHWVer[2] =  (u8)'.';
	ECU_Read.PlatHWVer[3] =  (u8)'0';
	ECU_Read.PlatHWVer[4] =  (u8)'0';
	ECU_Read.PlatHWVer[5] =  (u8)'.';
	ECU_Read.PlatHWVer[6] =  (u8)'0';
	ECU_Read.PlatHWVer[7] =  (u8)'0';
	ECU_Read.PlatHWVer[8] =  (u8)'.';
	ECU_Read.PlatHWVer[9] =  (u8)'0';
	ECU_Read.PlatHWVer[10] = (u8)'0';
	/* 19.10.00.05 */
	ECU_Read.PlatVer[0] =  (u8)'2';
	ECU_Read.PlatVer[1] =  (u8)'0';
	ECU_Read.PlatVer[2] =  (u8)'.';
	ECU_Read.PlatVer[3] =  (u8)'1';
	ECU_Read.PlatVer[4] =  (u8)'2';
	ECU_Read.PlatVer[5] =  (u8)'.';
	ECU_Read.PlatVer[6] =  (u8)'0';
	ECU_Read.PlatVer[7] =  (u8)'0';
	ECU_Read.PlatVer[8] =  (u8)'.';
	ECU_Read.PlatVer[9] =  (u8)'0';
	ECU_Read.PlatVer[10] = (u8)'0';
#endif 	
#if defined (RG3_PE_EV_R)
	/* RWPC (RG3_PE_EV_R) : 95560-J1900 UNIT ASSY-Wireless Charging -NFC */
	ECU_Read.PartNumber[5] = (u8)'J';
	ECU_Read.PartNumber[6] = (u8)'I';
	ECU_Read.PartNumber[7] = (u8)'9';
	ECU_Read.PartNumber[8] = (u8)'0';
	ECU_Read.PartNumber[9] = (u8)'0';
	/* 1.00 */
	ECU_Read.HWVer[0] = (u8)'1';
	ECU_Read.HWVer[1] = (u8)'.';
	ECU_Read.HWVer[2] = (u8)'0';
	ECU_Read.HWVer[3] = (u8)'0';
	/* 1.10 */	
	ECU_Read.SWVer[0] = (u8)'1';
	ECU_Read.SWVer[1] = (u8)'.';
	ECU_Read.SWVer[2] = (u8)'1';
	ECU_Read.SWVer[3] = (u8)'0';
	/* 50 -> 51 */
	ECU_Read.SWInVer[0] = (u8)'.';
	ECU_Read.SWInVer[1] = (u8)'5';
	ECU_Read.SWInVer[2] = (u8)'1';
	/* 1.00 */
	ECU_Read.DBVer[0] = (u8)'1';
	ECU_Read.DBVer[1] = (u8)'.';
	ECU_Read.DBVer[2] = (u8)'0';
	ECU_Read.DBVer[3] = (u8)'0';

	ECU_Read.CorpCode[0] = (u8)'S';
	ECU_Read.CorpCode[1] = (u8)'1';
	ECU_Read.CorpCode[2] = (u8)'1';
	ECU_Read.CorpCode[3] = (u8)'0';

	ECU_Read.SystemName[0] = (u8)'W';
	ECU_Read.SystemName[1] = (u8)'P';
	ECU_Read.SystemName[2] = (u8)'C';
	ECU_Read.SystemName[3] = (u8)' ';
	/* 02.00.00.00 */
	ECU_Read.PlatHWVer[0] =  (u8)'0';
	ECU_Read.PlatHWVer[1] =  (u8)'2';
	ECU_Read.PlatHWVer[2] =  (u8)'.';
	ECU_Read.PlatHWVer[3] =  (u8)'0';
	ECU_Read.PlatHWVer[4] =  (u8)'0';
	ECU_Read.PlatHWVer[5] =  (u8)'.';
	ECU_Read.PlatHWVer[6] =  (u8)'0';
	ECU_Read.PlatHWVer[7] =  (u8)'0';
	ECU_Read.PlatHWVer[8] =  (u8)'.';
	ECU_Read.PlatHWVer[9] =  (u8)'0';
	ECU_Read.PlatHWVer[10] = (u8)'0';
	/* 19.10.00.05 */
	ECU_Read.PlatVer[0] =  (u8)'1';
	ECU_Read.PlatVer[1] =  (u8)'9';
	ECU_Read.PlatVer[2] =  (u8)'.';
	ECU_Read.PlatVer[3] =  (u8)'1';
	ECU_Read.PlatVer[4] =  (u8)'0';
	ECU_Read.PlatVer[5] =  (u8)'.';
	ECU_Read.PlatVer[6] =  (u8)'0';
	ECU_Read.PlatVer[7] =  (u8)'0';
	ECU_Read.PlatVer[8] =  (u8)'.';
	ECU_Read.PlatVer[9] =  (u8)'0';
	ECU_Read.PlatVer[10] = (u8)'5';
#endif
}

/* end of file */

