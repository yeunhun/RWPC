#include "Rte_SWC_NvM.h"
#include "WPCEepControl.h"
#include "Data.h"
#include "define.h"
#include "app_input_type.h"
#include "app_input.h"
#include "app_output_type.h"
#include "app_output.h"
#include "App_NvM_RamBlock.h"
#include "WPCVehicleOption.h"

/*******************************************************************************
  Declare Function Prototypes
*******************************************************************************/
void Clear_EepromBlock_OPTION(void);
void Clear_EepromBlock_FUNCTION(void);
void Clear_EepromBlock_DTC(void);
void Clear_EepromBlock_FACTORY_SN(void);
void Clear_EepromBlock_FACTORY_MD(void);
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
void Clear_EepromBlock_DUMMY(void);
#endif

/*******************************************************************************
  Define Constant
*******************************************************************************/


/*******************************************************************************
  Declare  Variables
*******************************************************************************/
/* INPUT OUTPUT --------------------------------------------------------------*/


/* INTERNAL ------------------------------------------------------------------*/


/* EEPROM Image */
static Std_ReturnType EEP_reload_err = RTE_E_OK;
static u16 Update_eeprom_Err = 0x0000U;
static u16  Reload_eeprom_Err = 0x0000U;
u16 StoreEepromEnableFlag = 0x0000U;
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++DATA_STATIC++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  
void Set_EepromData_OPTION(u8 item, u8 value)
{
  rub_Option[item] = value;
  WriteEepData(e_NvmSvcBlock_Option, 1, rub_Option);
}

void Set_EepromData_FUNCTION(u8 item, u8 value)
{
  rub_Function[item] = value;
  WriteEepData(e_NvmSvcBlock_Function, 1, rub_Function);
}

void Set_EepromData_DTC(uint8 item, uint8 value)
{
  rub_DTCInfo[item] = value;
  WriteEepData(e_NvmSvcBlock_DTCInfo, 1, rub_DTCInfo);
}

void Set_EepromData_FACTORY_SN(uint8 item, uint8 value)
{
  rub_SerialNO[item] = value;
  WriteEepData(e_NvmSvcBlock_SerialNO, 1, rub_SerialNO);
}

void Set_EepromData_FACTORY_MD(uint8 item, u8 value)
{
  rub_MDate[item] = value;
  WriteEepData(e_NvmSvcBlock_MDate, 1, rub_MDate);
}

#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
void Set_EepromData_DUMMY(uint8 item, u8 value)
{
  rub_Dummy[item] = value;
  WriteEepData(e_NvmSvcBlock_Dummy, 1, rub_Dummy);
}
#endif

u8 Get_EepromData_OPTION(uint8 item)
{
  return rub_Option[item];
}

u8 Get_EepromData_FUNCTION(uint8 item)
{
  return rub_Function[item];
}

u8 Get_EepromData_DTC(uint8 item)
{
  return rub_DTCInfo[item];
}

u8 Get_EepromData_FACTORY_SN(uint8 item)
{
  return rub_SerialNO[item];
}

u8 Get_EepromData_FACTORY_MD(uint8 item)
{
  return rub_MDate[item];
}

#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
u8 Get_EepromData_DUMMY(uint8 item)
{
  return rub_Dummy[item];
}
#endif

void Clear_EepromBlock_OPTION(void)
{
  uint8 i=0u;

  for(i=0; i<sizeEEBlk_OPTION; i++)
  {
    rub_Option[i]=kMemory_Virgin;
  }

  WriteEepData(e_NvmSvcBlock_Option, 1, rub_Option);
}

void Clear_EepromBlock_FUNCTION(void)
{
  uint8 i=0u;

  for(i=0; i<sizeEEBlk_FUNCTION; i++)
  {
    rub_Function[i]=kMemory_Virgin;
  }

  WriteEepData(e_NvmSvcBlock_Function, 1, rub_Function);
}

void Clear_EepromBlock_DTC(void)
{
  uint8 i=0u;

  for(i=0; i<sizeEEBlk_DTC; i++)
  {
    rub_DTCInfo[i]=kMemory_Virgin;
  }

  WriteEepData(e_NvmSvcBlock_DTCInfo, 1, rub_DTCInfo);
}

void Clear_EepromBlock_FACTORY_SN(void)
{
  uint8 i=0u;

  for(i=0; i<sizeEEBlk_FACTORY_SN; i++)
  {
    rub_SerialNO[i]=kMemory_Virgin;
  }

  WriteEepData(e_NvmSvcBlock_SerialNO, 1, rub_SerialNO);
}

void Clear_EepromBlock_FACTORY_MD(void)
{
  uint8 i=0u;

  for(i=0; i<sizeEEBlk_FACTORY_MD; i++)
  {
    rub_MDate[i]=kMemory_Virgin;
  }

  WriteEepData(e_NvmSvcBlock_MDate, 1, rub_MDate);
}

#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
void Clear_EepromBlock_DUMMY(void)
{
  uint8 i=0u;

  for(i=0; i<sizeEEBlk_Dummy; i++)
  {
    rub_Dummy[i]=kMemory_Virgin;
  }

  WriteEepData(e_NvmSvcBlock_Dummy, 1, rub_Dummy);
}
#endif


