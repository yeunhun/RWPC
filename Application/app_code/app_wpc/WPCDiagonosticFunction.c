#include "Cdd_UserDefinedService.h"

#include "WPCType.h"
#include "define.h"
#include "WPCTimer.h"
#include "Data.h"

#include "app_input_type.h"
#include "app_input.h"
#include "app_output_type.h"
#include "app_output.h"
#include "WPCLogicControl.h"
#include "WPCEepControl.h"

/********************************************************************************
* Defines
********************************************************************************/


/********************************************************************************
* Variables
********************************************************************************/
static uint8 b_BCAN_BUSOFF_Present = Off;
static uint8 b_BCAN_BUSOFF_Memory = Off;
static uint8 b_LCAN_BUSOFF_Present = Off;
static uint8 b_LCAN_BUSOFF_Memory = Off;
static uint8 b_BCAN_ERROR_Present = Off;
static uint8 b_BCAN_ERROR_Memory = Off;
uint8 b_DTC_B1621_Present = Off;

// Clear Count for DTC
static uint8 Count_DTC_Clear_BCAN_BusOff = 0u;
static uint8 Count_DTC_Clear_LCAN_BusOff = 0u;

uint8 DTC_Set_Status;

/********************************************************************************
* Modules
********************************************************************************/
uint8 Get_DTC_BCAN_BusOff_Memorize(void)
{
	return	b_BCAN_BUSOFF_Memory;
}

void Set_DTC_BCAN_BusOff_Memorize(uint8 value)
{
	b_BCAN_BUSOFF_Memory = value;
}

uint8 Get_DTC_BCAN_BusOff_Present(void)
{
	return	b_BCAN_BUSOFF_Present;
}

void Set_DTC_BCAN_BusOff_Present(uint8 value)
{
	b_BCAN_BUSOFF_Present = value;
}

uint8 Get_DTC_LCAN_BusOff_Memorize(void)
{
	return	b_LCAN_BUSOFF_Memory;
}

void Set_DTC_LCAN_BusOff_Memorize(uint8 value)
{
	b_LCAN_BUSOFF_Memory = value;
}

uint8 Get_DTC_LCAN_BusOff_Present(void)
{
	return	b_LCAN_BUSOFF_Present;
}

void Set_DTC_LCAN_BusOff_Present(uint8 value)
{
	b_LCAN_BUSOFF_Present = value;
}

uint8 Get_DTC_BCAN_Error_Memorize(void)
{
	return	b_BCAN_ERROR_Memory;
}

/* TSCR-734 */
void Set_DTC_B1621_TemperatureSensorFault_Present(uint8 value)
{ 
	if(value > 0u)
	{
		b_DTC_B1621_Present |= (uint8)0x01u;
	}
	else
	{
		b_DTC_B1621_Present &= (uint8)0xFEu;
	}
}
/* TSCR-734 */
void Set_DTC_B1621_FANFault_Present(uint8 value)
{ 
	if(value > 0u)
	{
		b_DTC_B1621_Present |= (uint8)0x02u;
	}
	else
	{
		b_DTC_B1621_Present &= (uint8)0xFDu;
	}
}
/* TSCR-734 */
void Set_DTC_B1621_WPCInternalError_Present(uint8 value)
{ 
	if(value > 0u)
	{
		b_DTC_B1621_Present |= (uint8)0x03u;
	}
	else
	{
		b_DTC_B1621_Present &= (uint8)0xFCu;
	}
}
/* TSCR-734 */
void Set_DTC_B1621_TxCoilFault_Present(uint8 value)
{ 
	if(value > 0u)
	{
		//b_DTC_B1621_Present |= (uint8)0x04u;
	}
	else
	{
		//b_DTC_B1621_Present &= (uint8)0xFBu;
	}
}



uint8 Get_DTC_B1621_Present(void)
{
	return b_DTC_B1621_Present;
}

void Set_DTC_B1621_Present(uint8 value)
{
	b_DTC_B1621_Present = value;
}

uint8 Get_DTCClear_Count_BCAN_BusOff(void)
{
	return	Count_DTC_Clear_BCAN_BusOff;
}

void Set_DTCClear_Count_BCAN_BusOff(uint8 value)
{
	Count_DTC_Clear_BCAN_BusOff = value;
}

uint8 Get_DTCClear_Count_LCAN_BusOff(void)
{
	return	Count_DTC_Clear_LCAN_BusOff;
}

void Set_DTCClear_Count_LCAN_BusOff(uint8 value)
{
	Count_DTC_Clear_LCAN_BusOff = value;
}

void Init_UDS(void)
{    
	DTC_Set_Status = On;
}



