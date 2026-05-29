#ifndef APP_NVM_RAM_H
#define APP_NVM_RAM_H

extern uint8 rub_Option[8];
extern uint8 rub_Function[16];
extern uint8 rub_DTCInfo[8];
extern uint8 rub_SerialNO[24];
extern uint8 rub_MDate[8];
extern uint8 rub_PartNO[16];
extern uint8 rub_Dummy[16];


typedef enum
{
  e_NvmSvcBlock_Option = 0u,
  e_NvmSvcBlock_Function,
  e_NvmSvcBlock_DTCInfo,
  e_NvmSvcBlock_SerialNO,
  e_NvmSvcBlock_MDate,
  e_NvmSvcBlock_PartNO,
  e_NvmSvcBlock_Dummy,
  e_NvmSvcBlock_Max
}Vtype_NvmServiceBlock;

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
void Eeprom_Control(void);
void PNJF_NvMBlock_JobFinish(Vtype_NvmServiceBlock NvmBlock, uint8 ServiceId, NvM_RequestResultType Result);
void WriteEepData(uint8 Block, uint8 WriteReq, ConstVoidPtr *EepData);

#endif /*APP_NVM_RAM_H*/
