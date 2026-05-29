

/**********************************************************
 * HearFile
 *********************************************************/
#include "Rte_SWC_NVM.h"
#include "NvM.h"
#include "App_NvM_RamBlock.h"
#include "WPCSleepVarTYpe.h"
#include "WPCSleepVar.h"
#include "define.h"

/**********************************************************
 * NVM RAM Images
 *********************************************************/
uint8 rub_Option[8];
uint8 rub_Function[16];
uint8 rub_DTCInfo[8];
uint8 rub_SerialNO[24];
uint8 rub_MDate[8];
uint8 rub_PartNO[16];
uint8 rub_Dummy[16];

uint8 Init_Option[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8 Init_Function[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                          0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8 Init_DTCInfo[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8 Init_SerialNO[24] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                          0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                          0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8 Init_MDate[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8 Init_PartNO[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8 Init_Dummy[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};



tAPP_SLEEP APP_SLEEP_IF;


void WriteEepData(uint8 Block, uint8 WriteReq, ConstVoidPtr *EepData);
/**********************************************************
 * NVM Control Types
 *********************************************************/
typedef enum
{
  fSts_NvmMainCtl_Idle = 0u,
  fSts_NvmMainCtl_Write = 1u
}Ftype_NvmMainCtl;

typedef struct
{
  uint8 REQ_NvmWrite;
  uint8 PowerOnReset;   /* Unused */
  Ftype_NvmMainCtl Mode_NvmMainCtl;
  NvM_RequestResultType JobResult;
  NvM_RequestResultType RequestResult;
  Std_ReturnType  GetErrorStatusRetval;
  Std_ReturnType  ReadBlockRetval;  /* Unused */
  Std_ReturnType  WriteBlockRetval;
  ConstVoidPtr InitRam;
  ConstVoidPtr NvmRam;
  uint8 RamSize;
  Std_ReturnType (*GetErrorStatus)(NvM_RequestResultType *RequestResult);
  Std_ReturnType (*ReadBlock)(VoidPtr Destination);   /* Unused */
  Std_ReturnType (*WriteBlock)(IN VAR(ConstVoidPtr, RTE_DATA) Source);
  void (*PowerOnResetInit)(NvM_RequestResultType Result);   /* Unused */
}TypeAsw_NVMService;
/*
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
*/

/**********************************************************
 * NVM Block Table
 *********************************************************/
static void Callback_POR_Option(NvM_RequestResultType Result);
static void Callback_POR_Function(NvM_RequestResultType Result);
static void Callback_POR_DTCInfo(NvM_RequestResultType Result);
static void Callback_POR_SerialNO(NvM_RequestResultType Result);
static void Callback_POR_MDate(NvM_RequestResultType Result);
static void Callback_POR_PartNO(NvM_RequestResultType Result);
static void Callback_POR_Dummy(NvM_RequestResultType Result);
extern void Init_Eeprom_OK(void);


void NvmServiceMainHadle(Vtype_NvmServiceBlock NvmBlock);

TypeAsw_NVMService Tbl_NVMService[e_NvmSvcBlock_Max] =
{
  {   /* Option */
    0u, /* REQ_NvmWrite */
    NVM_REQ_NOT_OK,
    fSts_NvmMainCtl_Idle,
    0u,
    0u,
    0u,
    0u,
    0u,
    /********************************************************/
    Init_Option,
    rub_Option,
    8u,
    Rte_Call_SWC_NvM_PS_NvMBlock_Option_GetErrorStatus,
    Rte_Call_SWC_NvM_PS_NvMBlock_Option_ReadBlock,
    Rte_Call_SWC_NvM_PS_NvMBlock_Option_WriteBlock,
    Callback_POR_Option
    /*********************************************************/
  },
  {   /* Function */
    0u, /* REQ_NvmWrite */
    NVM_REQ_NOT_OK,
    fSts_NvmMainCtl_Idle,
    0u,
    0u,
    0u,
    0u,
    0u,
    /********************************************************/
    Init_Function,
    rub_Function,
    16u,
    Rte_Call_SWC_NvM_PS_NvMBlock_Function_GetErrorStatus,
    Rte_Call_SWC_NvM_PS_NvMBlock_Function_ReadBlock,
    Rte_Call_SWC_NvM_PS_NvMBlock_Function_WriteBlock,
    Callback_POR_Function
    /*********************************************************/
  },
  {   /* DTCInfo */
    0u, /* REQ_NvmWrite */
    NVM_REQ_NOT_OK,
    fSts_NvmMainCtl_Idle,
    0u,
    0u,
    0u,
    0u,
    0u,
    /********************************************************/
    Init_DTCInfo,
    rub_DTCInfo,
    8u,
    Rte_Call_SWC_NvM_PS_NvMBlock_DTCInfo_GetErrorStatus,
    Rte_Call_SWC_NvM_PS_NvMBlock_DTCInfo_ReadBlock,
    Rte_Call_SWC_NvM_PS_NvMBlock_DTCInfo_WriteBlock,
    Callback_POR_DTCInfo
    /*********************************************************/
  },
  {   /* SerialNO */
    0u, /* REQ_NvmWrite */
    NVM_REQ_NOT_OK,
    fSts_NvmMainCtl_Idle,
    0u,
    0u,
    0u,
    0u,
    0u,
    /********************************************************/
    Init_SerialNO,
    rub_SerialNO,
    24u,
    Rte_Call_SWC_NvM_PS_NvMBlock_SerialNO_GetErrorStatus,
    Rte_Call_SWC_NvM_PS_NvMBlock_SerialNO_ReadBlock,
    Rte_Call_SWC_NvM_PS_NvMBlock_SerialNO_WriteBlock,
    Callback_POR_SerialNO
    /*********************************************************/
  },
  {   /* MDate */
    0u, /* REQ_NvmWrite */
    NVM_REQ_NOT_OK,
    fSts_NvmMainCtl_Idle,
    0u,
    0u,
    0u,
    0u,
    0u,
    /********************************************************/
    Init_MDate,
    rub_MDate,
    8u,
    Rte_Call_SWC_NvM_PS_NvMBlock_MDate_GetErrorStatus,
    Rte_Call_SWC_NvM_PS_NvMBlock_MDate_ReadBlock,
    Rte_Call_SWC_NvM_PS_NvMBlock_MDate_WriteBlock,
    Callback_POR_MDate
    /*********************************************************/
  },
  {   /* PartNO */
    0u, /* REQ_NvmWrite */
    NVM_REQ_NOT_OK,
    fSts_NvmMainCtl_Idle,
    0u,
    0u,
    0u,
    0u,
    0u,
    /********************************************************/
    Init_PartNO,
    rub_PartNO,
    16u,
    Rte_Call_SWC_NvM_PS_NvMBlock_PartNO_GetErrorStatus,
    Rte_Call_SWC_NvM_PS_NvMBlock_PartNO_ReadBlock,
    Rte_Call_SWC_NvM_PS_NvMBlock_PartNO_WriteBlock,
    Callback_POR_PartNO
    /*********************************************************/
  },
  {   /* Dummy */
    0u, /* REQ_NvmWrite */
    NVM_REQ_NOT_OK,
    fSts_NvmMainCtl_Idle,
    0u,
    0u,
    0u,
    0u,
    0u,
    /********************************************************/
    Init_Dummy,
    rub_Dummy,
    16u,
    Rte_Call_SWC_NvM_PS_NvMBlock_Dummy_GetErrorStatus,
    Rte_Call_SWC_NvM_PS_NvMBlock_Dummy_ReadBlock,
    Rte_Call_SWC_NvM_PS_NvMBlock_Dummy_WriteBlock,
    Callback_POR_Dummy
    /*********************************************************/
  }
};

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
static void Clear_E2pRAM(uint8 *RAMBuf, uint8 size)
{
  uint8 Loop_i;

  for(Loop_i = 0 ; Loop_i < size ; Loop_i++)
  {
    RAMBuf[Loop_i] = 0xFF;
  }
}

static void Copy_E2pRAM(const uint8 *From, uint8 *To, uint8 size)
{
  uint8 Loop_i;

  for(Loop_i = 0 ; Loop_i < size ; Loop_i++)
  {
    To[Loop_i] = From[Loop_i];
  }
}

static uint8 Compare_E2pRAM(const uint8 *From, const uint8 *To, uint8 size)
{
  uint8 Loop_i;
  uint8 RetVal = 0u;

  for(Loop_i = 0 ; Loop_i < size ; Loop_i++)
  {
    if( To[Loop_i] != From[Loop_i])
    {
      RetVal = 1u;
    }
  }
  return RetVal;
}

/*******************************************************************************
** Function Name        : Eeprom_Control                                      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
uint8 AppNvM_BlockRetryCnt = 3u;
Vtype_NvmServiceBlock CurOpNvmBlock = e_NvmSvcBlock_Option;

void Eeprom_Control(void)
{
  NvmServiceMainHadle(CurOpNvmBlock);

  if(Tbl_NVMService[CurOpNvmBlock].JobResult == NVM_REQ_OK)                           // 0
  {
    CurOpNvmBlock++;

    if(CurOpNvmBlock == e_NvmSvcBlock_Max)
    {
      CurOpNvmBlock = e_NvmSvcBlock_Option;
    }
  }
  else if((Tbl_NVMService[CurOpNvmBlock].JobResult == NVM_REQ_NOT_OK) ||              // 1
          (Tbl_NVMService[CurOpNvmBlock].JobResult == NVM_REQ_INTEGRITY_FAILED) ||    // 3
          (Tbl_NVMService[CurOpNvmBlock].JobResult == NVM_REQ_NV_INVALIDATED))        // 5
  {
    if(AppNvM_BlockRetryCnt != 0u)
    {
      AppNvM_BlockRetryCnt--;
    }
    else
    {
      AppNvM_BlockRetryCnt = 3u;
      CurOpNvmBlock++;
    }
  }
  else if((Tbl_NVMService[CurOpNvmBlock].JobResult == NVM_REQ_BLOCK_SKIPPED) ||       // 4
          (Tbl_NVMService[CurOpNvmBlock].JobResult == NVM_REQ_CANCELED) ||            // 6
          (Tbl_NVMService[CurOpNvmBlock].JobResult == NVM_REQ_REDUNDANCY_FAILED) ||   // 7
          (Tbl_NVMService[CurOpNvmBlock].JobResult == NVM_REQ_RESTORED_FROM_ROM))     // 8
  {   /* NVM Block Service Fail */
    CurOpNvmBlock = e_NvmSvcBlock_Max;
  }
  else
  {

  }

#if 0
  for(idx=0; idx<e_NvmSvcBlock_Max; idx++)
  {
    WriteEepData(idx, 1, &Tbl_NVMService[idx].NvmRam);
  }
#endif

  /* For NvM Sleep Condition Check */
  if((Tbl_NVMService[e_NvmSvcBlock_Option].JobResult == NVM_REQ_OK) &&          // 0
      (Tbl_NVMService[e_NvmSvcBlock_Function].JobResult == NVM_REQ_OK) &&
      (Tbl_NVMService[e_NvmSvcBlock_DTCInfo].JobResult == NVM_REQ_OK) &&
      (Tbl_NVMService[e_NvmSvcBlock_SerialNO].JobResult == NVM_REQ_OK) &&
      (Tbl_NVMService[e_NvmSvcBlock_MDate].JobResult == NVM_REQ_OK) &&
      (Tbl_NVMService[e_NvmSvcBlock_PartNO].JobResult == NVM_REQ_OK) &&
      (Tbl_NVMService[e_NvmSvcBlock_Dummy].JobResult == NVM_REQ_OK))
  {
    //VAR(tVAR, AUTOMATIC) RE_NvM_10ms_Process_0;
    //RE_NvM_10ms_Process_0 = 1;
    SetX(Slpwup_NvMJobFinished, 1);
    (void)Rte_Write_SWC_NvM_P_Slpwup_NvMJobFinished_SR_u8(&Slpwup_NvMJobFinished);
    Init_Eeprom_OK();
  }
  else
  {
    SetX(Slpwup_NvMJobFinished, 0);
    (void)Rte_Write_SWC_NvM_P_Slpwup_NvMJobFinished_SR_u8(&Slpwup_NvMJobFinished);
  }
}
/*******************************************************************************
** Function Name        : NvmServiceMainHadle                                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
void NvmServiceMainHadle(Vtype_NvmServiceBlock NvmBlock)
{
  Tbl_NVMService[NvmBlock].GetErrorStatusRetval = \
      Tbl_NVMService[NvmBlock].GetErrorStatus(&Tbl_NVMService[NvmBlock].RequestResult);

  switch(Tbl_NVMService[NvmBlock].Mode_NvmMainCtl)
  {
    case fSts_NvmMainCtl_Idle:
    {
      if((Tbl_NVMService[NvmBlock].GetErrorStatusRetval == RTE_E_OK) && // 0
          (Tbl_NVMService[NvmBlock].RequestResult != NVM_REQ_NOT_OK)) // 1
      {
        if(Tbl_NVMService[NvmBlock].RequestResult == NVM_REQ_NV_INVALIDATED)  //5  /* Eeprom Initial */
        {
          Tbl_NVMService[NvmBlock].JobResult = 0xFFu;

          Copy_E2pRAM(Tbl_NVMService[NvmBlock].InitRam, (uint8 *)Tbl_NVMService[NvmBlock].NvmRam, Tbl_NVMService[NvmBlock].RamSize);

          Tbl_NVMService[NvmBlock].WriteBlockRetval = \
              Tbl_NVMService[NvmBlock].WriteBlock(Tbl_NVMService[NvmBlock].NvmRam);

          if(Tbl_NVMService[NvmBlock].WriteBlockRetval == RTE_E_OK) // 0
          {
            Tbl_NVMService[NvmBlock].Mode_NvmMainCtl = fSts_NvmMainCtl_Write;
          }
        }
        else if(Tbl_NVMService[NvmBlock].REQ_NvmWrite != 0u)
        {
          Tbl_NVMService[NvmBlock].REQ_NvmWrite = 0u;
          Tbl_NVMService[NvmBlock].JobResult = 0xFFu;

          Copy_E2pRAM(Tbl_NVMService[NvmBlock].NvmRam, (uint8 *)Tbl_NVMService[NvmBlock].InitRam, Tbl_NVMService[NvmBlock].RamSize);

          Tbl_NVMService[NvmBlock].WriteBlockRetval = \
              Tbl_NVMService[NvmBlock].WriteBlock(Tbl_NVMService[NvmBlock].NvmRam);

          if(Tbl_NVMService[NvmBlock].WriteBlockRetval == RTE_E_OK) // 0
          {
            Tbl_NVMService[NvmBlock].Mode_NvmMainCtl = fSts_NvmMainCtl_Write;
          }
          else
          {

          }
        }
        else
        {

        }
      }
      break;
    }
    case fSts_NvmMainCtl_Write :
    {
      if(Tbl_NVMService[NvmBlock].RequestResult != NVM_REQ_PENDING) // 2
      {
        if((Tbl_NVMService[NvmBlock].GetErrorStatusRetval == RTE_E_OK) && // 0
            (Tbl_NVMService[NvmBlock].RequestResult == NVM_REQ_OK))       // 0
        {
          Tbl_NVMService[NvmBlock].Mode_NvmMainCtl = fSts_NvmMainCtl_Idle;
        }
        else
        {   /* NVM Block Write Service Fail */
          Tbl_NVMService[NvmBlock].Mode_NvmMainCtl = fSts_NvmMainCtl_Idle;
        }
      }
      break;
    }
    default :
    {
      Tbl_NVMService[NvmBlock].Mode_NvmMainCtl = fSts_NvmMainCtl_Idle;
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : PNJF_NvMBlock_JobFinish                             **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
void PNJF_NvMBlock_JobFinish(Vtype_NvmServiceBlock NvmBlock, uint8 ServiceId, NvM_RequestResultType Result)
{
  Tbl_NVMService[NvmBlock].JobResult = Result;

  if((ServiceId == NVM_READBLOCK_SID) || (ServiceId == NVM_READALL_SID))  // 0x06, 0x0C
  {
    if((Tbl_NVMService[NvmBlock].JobResult == NVM_REQ_NOT_OK) ||           // 1
        (Tbl_NVMService[NvmBlock].JobResult == NVM_REQ_INTEGRITY_FAILED))  // 3
    {
      Clear_E2pRAM((uint8 *)Tbl_NVMService[NvmBlock].NvmRam, Tbl_NVMService[NvmBlock].RamSize);
      Copy_E2pRAM(Tbl_NVMService[NvmBlock].InitRam, (uint8 *)Tbl_NVMService[NvmBlock].NvmRam, Tbl_NVMService[NvmBlock].RamSize);

      Tbl_NVMService[NvmBlock].REQ_NvmWrite = 1u;
    }
    else if(Tbl_NVMService[NvmBlock].JobResult == NVM_REQ_NV_INVALIDATED) // 5
    {
      Copy_E2pRAM(Tbl_NVMService[NvmBlock].InitRam, (uint8 *)Tbl_NVMService[NvmBlock].NvmRam, Tbl_NVMService[NvmBlock].RamSize);
    }
  }
  else if(ServiceId == NVM_WRITEBLOCK_SID)                    // 7
  {
    if(Tbl_NVMService[NvmBlock].JobResult == NVM_REQ_NOT_OK)  // 1
    {
      Clear_E2pRAM((uint8 *)Tbl_NVMService[NvmBlock].NvmRam, Tbl_NVMService[NvmBlock].RamSize);
      Copy_E2pRAM(Tbl_NVMService[NvmBlock].InitRam, (uint8 *)Tbl_NVMService[NvmBlock].NvmRam, Tbl_NVMService[NvmBlock].RamSize);

      Tbl_NVMService[NvmBlock].REQ_NvmWrite = 1u;
    }
  }
  else
  {

  }

  if(Tbl_NVMService[NvmBlock].PowerOnReset == NVM_REQ_NOT_OK) // 1
  {
    Tbl_NVMService[NvmBlock].PowerOnReset = NVM_REQ_OK;       // 0
    Tbl_NVMService[NvmBlock].PowerOnResetInit(Tbl_NVMService[NvmBlock].JobResult);
  }
}

#if 1
void WriteEepData(uint8 Block, uint8 WriteReq, ConstVoidPtr *EepData)
{
  Vtype_NvmServiceBlock NvmBlock;
  NvmBlock = (Vtype_NvmServiceBlock) Block;

  Tbl_NVMService[NvmBlock].REQ_NvmWrite = WriteReq;
  Tbl_NVMService[NvmBlock].NvmRam = (ConstVoidPtr)EepData;
}
#endif
#if 0
void WriteEepData(uint8 Block, uint8 WriteReq, uint8 * EepData, uint8 item)
{
  Vtype_NvmServiceBlock NvmBlock;
  NvmBlock = Block;

  Tbl_NVMService[NvmBlock].REQ_NvmWrite = WriteReq;
  Tbl_NVMService[NvmBlock].NvmRam =(ConstVoidPtr)EepData;
}
#endif

#if 0
void ReadEepData(uint8 Block, uint8 *EepData)
{
  Vtype_NvmServiceBlock NvmBlock;
  NvmBlock = Block;

  EepData = (uint8 *)Tbl_NVMService[NvmBlock].NvmRam;
}
#endif
#if 0
void ReadEepData(uint8 Block, uint8 *EepData, uint8 item)
{
  Vtype_NvmServiceBlock NvmBlock;
  NvmBlock = Block;

  EepData = (uint8 *)Tbl_NVMService[NvmBlock].NvmRam[item];
}
#endif

static void Callback_POR_Option(NvM_RequestResultType Result)
{

}

static void Callback_POR_Function(NvM_RequestResultType Result)
{

}

static void Callback_POR_DTCInfo(NvM_RequestResultType Result)
{

}

static void Callback_POR_SerialNO(NvM_RequestResultType Result)
{

}

static void Callback_POR_MDate(NvM_RequestResultType Result)
{

}

static void Callback_POR_PartNO(NvM_RequestResultType Result)
{

}

static void Callback_POR_Dummy(NvM_RequestResultType Result)
{

}


