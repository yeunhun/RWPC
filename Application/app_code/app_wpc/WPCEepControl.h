/******************************************************************************
 * Project        :   SP2 IBU
 * File Name      :   Eeprom.h
 * Compiler     :   Eclipse
 * Author         :   MyoungKwon Choi (mk210@seoyonelec.com)
 * Created at     :   2017-06-23
 * Code Editor    :   Source Insight (Recomended Font : D2Coding / Size 10)
 * Revision       :   Version 0.1
 * Copyright      :   Copyright Seoyon Electronics Co.Ltd. All Rights Reserved
 * Description    :
 *
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------*/
#ifndef __EEPROM_H__
#define __EEPROM_H__


#include "WPCType.h"
#include "define.h"
#include "WPCVehicleOption.h"



enum UserOPTION_OffsetList
{
  kOption_Status = 0u, // ó�� ���� �� EEPROM ������ Ȯ�� ��...

  kMax_Option = 4u
};

enum FUNCTION_offsetList
{
  kFunc_WPCOnOff = 0u,    /* from CLU(CGWmsg01) */
  kFunc_WPCOneUSM,
  kFunc_WPCTwoUSM,
  kFunc_WPCUnknownUSM,
  kFunc_NFCOnOff,
  kFunc_NFCOneUSM,
  kFunc_NFCTwoUSM,
  kFunc_NFCUnknownUSM,
  kFunc_AnimationINDOnOff,
  kFunc_AnimationINDOneUSM,
  kFunc_AnimationINDTwoUSM,
  kFunc_AnimationINDUnknownUSM,
  
  kMax_FuncOption = 16u
};

enum DTC_offsetList
{
	kDTC_BCAN_BUSOFF = 0u, // CAN Bus Off
	kDTC_LCAN_BUSOFF,

	kMax_DTC = 8u
};

enum Factory_SN_offsetList
{
	kFactory_ECUSerialNumber = 0u,

	kMax_Factory_SN = 24u
};

enum Factory_MD_offsetList
{
	kFactory_ManufacturingDate = 0u,

	kMax_Factory_MD = 8u
};

#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
enum DUMMY_offsetList
{
  kDummy_ChargeICver_0 = 0u,
  kDummy_ChargeICver_1,
  kDummy_ChargeICver_2,
  kDummy_ChargeICver_3,
  kDummy_ChargeICver_4,

  kMax_Dummy = 16u
};
#endif

#define kMemory_Virgin      0xFFu
#define kMemory_Learnt      0x55u

#define EEBlk_OPTION        0x00000001U
#define EEBlk_FUNCTION      0x00000002U
#define EEBlk_DTC           0x00000004U
#define EEBlk_FACTORY_SN    0x00000008U
#define EEBlk_FACTORY_MD    0x00000010U
//#define EEBlk_FACTORY_PN    0x00000020U
//#define EEBlk_DUMMY         0x00000040U
#define EEBlk_NONE          0x00000000U
#define EEBlk_ALL           0x001FU
#define EEBlk_INIT_OK       0x001FU


/*******************************************************************************
  Declare External  Variables
*******************************************************************************/

/* Internal Variables */
extern uint8 rub_OptionEepromData[];


/*******************************************************************************
  Define Constant
*******************************************************************************/
/* EEPROM Block Size */
#define sizeEEBlk_OPTION      8
#define sizeEEBlk_FUNCTION    16
#define sizeEEBlk_DTC         8
#define sizeEEBlk_FACTORY_SN  24
#define sizeEEBlk_FACTORY_MD  8
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
#define sizeEEBlk_Dummy       16
#endif

/* Client Server Interface */

/* Eeprom Err */
#define Set_Update_Eeprom_Err(x)		(Update_eeprom_Err |= (x))
#define Get_Update_Eeprom_Err(x)		(Update_eeprom_Err&(x))
#define Clear_Update_Eeprom_Err(x)		(Update_eeprom_Err = Update_eeprom_Err&(EEBlk_ALL^(x)))


/* Eeprom Reload Err */
#define Set_Reload_Eeprom_Err(x)      (Reload_eeprom_Err |= (x))
#define Get_Reload_Eeprom_Err(x)      (Reload_eeprom_Err&(x))
#define Clear_Reload_Eeprom_Err(x)    (Reload_eeprom_Err = Reload_eeprom_Err&(EEBlk_ALL^(x)))
#define RELOAD_ERROR                  ((EEP_reload_err==NVM_REQ_OK)?0u:1u)



/* Set Eeprom */
extern uint16  StoreEepromEnableFlag;
#define Set_EepromStoreEnable(x)    (StoreEepromEnableFlag |= (x))
#define	Get_EepromStoreEnable(x)		(StoreEepromEnableFlag&(x))
#define	Clear_EepromStoreEnable(x)		(StoreEepromEnableFlag = StoreEepromEnableFlag&(EEBlk_ALL^(x)))

extern void Set_EepromData_OPTION(u8 item, u8 value);
extern void Set_EepromData_FUNCTION(u8 item, u8 value);
extern void Set_EepromData_DTC(u8 item, u8 value);
extern void Set_EepromData_FACTORY_SN(u8 item, u8 value);
extern void Set_EepromData_FACTORY_MD(u8 item, u8 value);
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
extern void Set_EepromData_DUMMY(u8 item, u8 value);
#endif

extern u8 Get_EepromData_OPTION(u8 item);
extern u8 Get_EepromData_FUNCTION(u8 item);
extern u8 Get_EepromData_DTC(u8 item);
extern u8 Get_EepromData_FACTORY_SN(u8 item);
extern u8 Get_EepromData_FACTORY_MD(u8 item);
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
extern u8 Get_EepromData_DUMMY(u8 item);
#endif

extern void Clear_EepromBlock_OPTION(void);
extern void Clear_EepromBlock_FUNCTION(void);
extern void Clear_EepromBlock_DTC(void);
extern void Clear_EepromBlock_FACTORY_SN(void);
extern void Clear_EepromBlock_FACTORY_MD(void);
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
extern void Clear_EepromBlock_DUMMY(void);
#endif

extern void EEPROM_Control(void);
extern void EEPROM_Reload_Control(void);

#endif  /* __EEPROM_H__ */
