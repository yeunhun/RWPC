/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Mem_Integration.c                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR MemStack Integration Module                           **
**                                                                            **
**  PURPOSE   : Provision of Version information                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "Os.h"
#include "Mem_Integration.h" /* NvM.h */
#include "SchM_NvM.h"
#include "NvM_Ram.h"
#include "NvM_Config.h"
/* backward compatibility for Dem */
#if (NVM_BSWM_DEM_WRITENVDATA_CALL == STD_ON)
#include "Dem_EventMemory.h"    
#endif

#if(NVM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#if (MEM_FLS_USED == STD_ON)
#include "Fls.h"

/* not declared Fls_MainFunction in the Fls.h */
#if (\
  ((defined(HWRESOURCE_S32G2X))  && HWRESOURCE_FAMILY(HWRESOURCE_S32G2X)  ) || \
  ((defined(HWRESOURCE_CYT2BXX)) && HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX) ) || \
  ((defined(HWRESOURCE_CYT4BXX)) && HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX) )    \
)
#include "SchM_Fls.h"
#endif

#endif

#if (MEM_FEE_USED == STD_ON)
#include "Fee.h" /* Fee_Version.h */

#if ((defined(HWRESOURCE_S32G2X))  && HWRESOURCE_FAMILY(HWRESOURCE_S32G2X) )
#include "SchM_Fee.h"
#endif

#endif

#if (MEM_EA_USED == STD_ON)
#include "Ea.h"
#include "SchM_Eep.h"
#endif

#if (HWRESOURCE_FAMILY(HWRESOURCE_S6J32XX) || \
     HWRESOURCE_FAMILY(HWRESOURCE_S6J33XX) )
#include "mcu_settings.h"
#endif

/* polyspace-begin MISRA-C3:8.4 [Justified:Low] "Not a defect" */
/* polyspace-begin RTE:UNR [Not a defect:Low] "Not a defect" */
/* polyspace-begin RTE:IDP [Not a defect:Low] "Not a defect" */
/* polyspace-begin RTE:NIV [Not a defect:Low] "Not a defect" */
/* polyspace-begin RTE:OBAI [Not a defect:Low] "Not a defect" */
/* polyspace-begin VARIABLE:ALL [Not a defect:Low] "Not a defect" */

#if(NVM_DRV_MODE_SWITCH == STD_OFF)
#error "1 NvMDrvModeSwitch should be true."
#error "2 FlsDefaultMode should be configured as MEMIF_MODE_FAST"
#error "3 FlsSetModeApi should be true."
#error "4 FeeSetModeSupported should be true."
#error "5 EepDefaultMode should be configured as MEMIF_MODE_FAST"
#error "6 EaSetModeSupported should be true."
#endif

#if (MEM_FEE_USED == STD_ON)

#if (HWRESOURCE_VENDOR(HWRESOURCE_ST) && \
  (FEE_SW_MAJOR_VERSION >= 1) && (FLS_SW_MAJOR_VERSION >= 1))
#define MEM_FEE_INIT_WHILE_LOOP  (STD_OFF)  
#else
#define MEM_FEE_INIT_WHILE_LOOP  (STD_ON)
#endif

#endif

#if defined(NVM_USER_JOB_FUNCTION)
extern FUNC(NvM_OpStatusType, NVM_CODE) NVM_USER_JOB_FUNCTION(void);
#endif 
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
uint8 ConfigIDRamBlock[2];

#ifdef NvMConf_NvMBlockDescriptor_NvMBlock_IntTst_TestBlock1
uint8 NvMBlock_IntTst_TestBlock1_Ram_Block[10];
#endif

#ifdef NvMConf_NvMBlockDescriptor_NvMBlock_IntTst_TestBlock2
uint8 NvMBlock_IntTst_TestBlock2_Ram_Block[10];
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Mem_Driver_StartUp                                  **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : Service for basic Memory Stack Initialization       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : Eep_Init, Ea_Init             **
**                             Fls_17_Pmu_Init, Mem_FlsInitPerform, Fee_Init  **
**                             Mem_FeeInitPerform, NvM_Init, NvM_ReadAll      **
**                             Mem_Call_NvM_BITP                              **
*******************************************************************************/
FUNC(void, NVM_CODE) Mem_Driver_StartUp(void)
{
  #if (MEM_EA_USED == STD_ON)
  Eep_Init(NULL_PTR);
  Ea_Init();
  #endif

  #if (MEM_FLS_USED == STD_ON)    
  Mem_FlsInitPerform();       
  #endif

  #if (MEM_FEE_USED == STD_ON)      
  Mem_FeeInitPerform();
  #endif

  NvM_Init();
  NvM_ReadAll();
  
  if (E_OK != ActivateTask(OsTask_BSW_Mem_Process))
  {
    MEM_REPORT_ERROR(MEM_OSTASK_BSW_MEM_PROCESS_SID, MEM_E_ALARM);
  }     
}
/*******************************************************************************
** Function Name        : Mem_Driver_ShutDown                                 **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : Service for WriteAll Perform                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : NvM_WriteAll,                 **
**                             Mem_Call_NvM_BITP                              **
*******************************************************************************/
FUNC(void, NVM_CODE) Mem_Driver_ShutDown(void)
{
  /* Reset the task sequence control variable */    
  NvM_WriteAll();
}
/*******************************************************************************
** Function Name        : Mem_FlsInitPerform                                  **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : Service for basic FLS Initialization                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : Fls_GetStatus, Fls_MainFunction*
*******************************************************************************/
#if (MEM_FLS_USED == STD_ON) 
FUNC(void, NVM_CODE) Mem_FlsInitPerform(void)
{
  uint32 timeOut = 0xFFFFU;

  /* ASR 4.2.2 ~ */
  #if ((FLS_AR_RELEASE_MAJOR_VERSION == 4) && (FLS_AR_RELEASE_MINOR_VERSION >= 2))
    #if HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)  
      Fls_17_Dmu_Init(&Fls_17_Dmu_Config);
    
    /* Cypress Traveo II */
    #elif (\
      ((defined(HWRESOURCE_CYT2BXX)) && HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX) ) || \
      ((defined(HWRESOURCE_CYT4BXX)) && HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX) )    \
    )
      Fls_Init(NULL_PTR);
    #else
      /* ex) SCons : DefaultDefineOption : FLS_CONFIGSET = FlsConfigSet_0 */
      #ifdef FLS_CONFIGSET
        Fls_Init(FLS_CONFIGSET);    
        
      #else            
        #error "MCU is not supported yet"
        
      #endif      
    #endif  
  /* ~ ASR 4.1.2 */
  #else 
    #if HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
      Fls_17_Pmu_Init(&Fls_17_Pmu_ConfigRoot[0]);      

    /* Freescale(NXP) or ST mpc family */
    #elif (HWRESOURCE_VENDOR(HWRESOURCE_FREESCALE) || HWRESOURCE_VENDOR(HWRESOURCE_ST))
      Fls_Init(&FlsConfigSet_0);

    #elif (HWRESOURCE_FAMILY(HWRESOURCE_S6J32XX) || \
           HWRESOURCE_FAMILY(HWRESOURCE_S6J33XX) )
      #ifndef MEM_DISABLE_WFCFG_EMENR_LIMITATION
      /* Fee Limitation 
       * 
       * Set WFCFG_EMENR(WorkFLASH Extra Mode Enable Register:) : AEE "1". */
      /* [bit8] AEE: Read Arbitration Error Enable = 1 */
      WFCFG_EMENR |= 0x00000100;
      #endif
    
      Fls_Init(NULL_PTR);
  
    #elif HWRESOURCE_VENDOR(HWRESOURCE_NXP)
      Fls_Init(&FlsConfigSet_0);

    #else
      #error "MCU is not supported yet"
    #endif     
  #endif
  
  while( (Fls_GetStatus() != MEMIF_IDLE) && (timeOut > 0U) )
  {
    MEM_MAINFUNCTION_FLS();
    timeOut--;
  };
  
}
#endif
/*******************************************************************************
** Function Name        : Mem_FeeInitPerform                                  **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : Service for basic FEE Initialization                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : Fee_GetStatus                 **
**                             Fls_MainFunction, Fee_MainFunctions            **
*******************************************************************************/
#if (MEM_FEE_USED == STD_ON)
FUNC(void, NVM_CODE) Mem_FeeInitPerform(void)
{
  #if (MEM_FEE_INIT_WHILE_LOOP == STD_ON)
  boolean loopBrk = MEM_TRUE;  
  uint32 timeout = 0xFFFFFFUL;
  #endif  

  /* polyspace +2 MISRA-C3:2.2 [Justified:Low] "This function is implemented by user." */
  Mem_PostFeeInitCallback();  

  /* ASR 4.2.2 ~  : void Fee_Init(const Fee_ConfigType* ConfigPtr) */
  #if ((FEE_AR_RELEASE_MAJOR_VERSION == 4) && (FEE_AR_RELEASE_MINOR_VERSION >= 2))

    #if (HWRESOURCE_VENDOR(HWRESOURCE_NXP))
      Fee_Init(NULL_PTR);  
      
    #elif (HWRESOURCE_VENDOR(HWRESOURCE_INFINEON))
      Fee_Init(&Fee_Config);      
      
    /* Cypress Traveo II */
    #elif (\
      ((defined(HWRESOURCE_CYT2BXX)) && HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX) ) || \
      ((defined(HWRESOURCE_CYT4BXX)) && HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX) )    \
    )
      Fee_Init(NULL_PTR);
      
    #else
      /* ex) SCons : DefaultDefineOption : FEE_CONFIGSET = FlsConfigSet_0 */
      #ifdef FEE_CONFIGSET
        Fee_Init(FEE_CONFIGSET);    
        
      #else    
        #error "MCU is not supported yet"
        
      #endif /* #ifdef FEE_CONFIGSET */
    #endif /* #if (HWRESOURCE_VENDOR(HWRESOURCE_NXP)) */  
  /* ~ ASR 4.1.2 : void Fee_Init( void ) */
  #else
    Fee_Init();
  
  #endif /* #if((FEE_AR_RELEASE_MAJOR_VERSION==4)&&(FEE_AR_RELEASE_MINOR_VERSION>=2))*/

  #if (MEM_FEE_INIT_WHILE_LOOP == STD_ON) 
  while(MEM_TRUE == loopBrk)
  {
    MEM_MAINFUNCTION_FLS();    
    MEM_MAINFUNCTION_FEE();
    timeout--;

    if (timeout == 0U) 
    {
      loopBrk = MEM_FALSE;
    }    
    else if (Fee_GetStatus() == MEMIF_IDLE)
    {
      loopBrk = MEM_FALSE;
    }  
    
    #if HWRESOURCE_VENDOR(HWRESOURCE_CYPRESS)    
    else if (Fee_GetStatus() == MEMIF_UNINIT)
    {
      loopBrk = Mem_Cypress_IllegalStateCallback();
    }
    #endif
    else
    {
      /* do nothing */
    }    
  }
  #endif
}
#endif

/*******************************************************************************
** Function Name        : Mem_GetAlarmOffset                                  **
**                                                                            **
** Service ID           : N/a                                                 **
**                                                                            **
** Description          : Get alarm offset according to the current job status**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Alarm offset                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if defined(NVM_OS_ALARM)
FUNC(TickType, NVM_CODE) Mem_GetAlarmOffset(void)
{
  TickType alarmOffset;

   if ( 
    (NVM_IDLE != NvM_GucState) ||    /* block is in progress */
    (0U       != NvM_GucStdQueEnDis) /* queue is not empty */
    #if (MEM_WRITEALL_FAST_MODE == STD_OFF)    
    || (NVM_MULTIBLK_UNREQUESTED != NvM_GucWriteAllRequest)
    #endif
  )  
  { /* about 1ms~3ms */
    alarmOffset = NVM_TICKS_BURST_MODE;
  }
  else
  {
    /* about 5ms~6ms */  
    alarmOffset = NVM_TICKS_NORMAL_MODE;
  }

  return alarmOffset;
}
#endif

/*******************************************************************************
** Function Name        : OsTask_BSW_Mem_Process                              **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : Service for Call MemoryStack Mainfunction           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : This function is invoked by OsAlarm                 **
**                                                                            **
*******************************************************************************/
TASK( OsTask_BSW_Mem_Process )
{
  static boolean callSeq = MEM_FALSE;
  EventMaskType eventMask;
  #if defined(NVM_OS_ALARM)
  TickType alarmOffset;
  #endif
  if (E_OK ==  SetEvent(OsTask_BSW_Mem_Process, OsEvent_BSW_Mem_Process))
  {
    /* for ReadAll function */
    MEM_MAINFUNCTION_NVM();
    MEM_MAINFUNCTION_NVM();  

    while (1)
    {
      (void)WaitEvent(OsEvent_BSW_Mem_Process);
      (void)GetEvent(OsTask_BSW_Mem_Process, &eventMask);
      (void)ClearEvent(OsEvent_BSW_Mem_Process); 

      #if defined(NVM_USER_JOB_FUNCTION)
      if ( NVM_OPSTATUS_IDLE == NVM_USER_JOB_FUNCTION() )
      #endif
      {      
        do
        {
          if (MEM_FALSE == callSeq)   
          {
            MEM_MAINFUNCTION_NVM();
            MEM_MAINFUNCTION_FEE();
            MEM_MAINFUNCTION_FLS();
            MEM_MAINFUNCTION_EA();
            MEM_MAINFUNCTION_EEP();
            callSeq = MEM_TRUE;            
          }
          else
          {
            MEM_MAINFUNCTION_FLS();
            MEM_MAINFUNCTION_FEE();      
            MEM_MAINFUNCTION_EEP();
            MEM_MAINFUNCTION_EA();      
            MEM_MAINFUNCTION_NVM();      
            callSeq = MEM_FALSE;            
          }
        }
        while( (NVM_MULTIBLK_UNREQUESTED != NvM_GucReadAllRequest) 
        #if (MEM_WRITEALL_FAST_MODE == STD_ON)    
          || (NVM_MULTIBLK_UNREQUESTED != NvM_GucWriteAllRequest)
          #if (NVM_BSWM_DEM_WRITENVDATA_CALL == STD_ON)
          || (DEM_JOB_TRIGGER == Dem_EvMem_WriteNvDataEndModeTriggered())
          #endif    
        #endif
        );          
      }

      #if defined(NVM_OS_ALARM)
      alarmOffset = Mem_GetAlarmOffset();
      if (E_OK != SetRelAlarm(NVM_OS_ALARM, alarmOffset, 0))
      {
        MEM_REPORT_ERROR(MEM_OSTASK_BSW_MEM_PROCESS_SID, MEM_E_ALARM);    
        break;
      }
      #endif      
    }
  }
  else
  {
    MEM_REPORT_ERROR(MEM_OSTASK_BSW_MEM_PROCESS_SID, MEM_E_EVENT);
  }
  
  (void)TerminateTask();
}

/*******************************************************************************
** Function Name        : Fee_IllegalStateNotification                        **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Aurix Fee IllegalStateNotification                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
*******************************************************************************/
#if (HWRESOURCE_VENDOR(HWRESOURCE_INFINEON))
FUNC(void, NVM_CODE) Fee_IllegalStateNotification (void)
{
  /* Indicate job is completed with error */
  NvM_GddJobResultLowLevel = NVM_REQ_NOT_OK;
  
  /* Because application user could modify Fee_IllegalStateCallback function */
  Mem_Infineon_IllegalStateCallback();
}
#endif


#if HWRESOURCE_FAMILY(HWRESOURCE_S32K14X)
/* polyspace +4 MISRA-C3:8.5 [Justified:Low] "This function is invoked by Os." */
/* polyspace +3 MISRA-C3:8.4[Justified:Low] "This function is invoked by Os." */
FUNC(boolean, NVM_CODE) Fls_DataEccHandler(uint8 ** instr_pt2pt, uint32 * addr_CFSR, uint32 * addr_BFAR)
{
  Fls_InstructionAddressType instr_pt;
  Fls_DataAddressType data_pt;
  uint32 syndrome;
  Fls_ExceptionDetailsType excDetails;
  Fls_CompHandlerReturnType specificHandlerResult = FLS_UNHANDLED;
  uint16 instrOpcode;     /* The instruction opcode(or the first 16 bits) value, stored in memory, for the instruction which caused the fault */
  uint8 thumbInstrSize;   /* Size of the instruction opcode stored in memory, 2 or 4 bytes */
  boolean skipOrRetry = FALSE;

  instr_pt = *instr_pt2pt;
  data_pt  = (void const *)(*((uint32*)addr_BFAR));
  syndrome = *((uint32*)addr_CFSR);;

  /* Compute the instruction opcode size for the instruction which caused the hardfault. *
   * The value will be used to compute the address of the following instruction */
  /* polyspace +4 MISRA-C3:11.3 [Justified:Low] "Not a defect." */
  /* polyspace +3 MISRA-C3:11.8 [Justified:Low] "Not a defect." */  
  instrOpcode =  *((uint16*)instr_pt);
  /* Compute the size of the instruction which caused the fault */
  if (((instrOpcode & (uint16)0xE800) == (uint16)0xE800) ||   /* 0b11101x... */
      ((instrOpcode & (uint16)0xF000) == (uint16)0xF000) ||   /* 0b11110x... */
      ((instrOpcode & (uint16)0xF800) == (uint16)0xF800))     /* 0b11111x... */
  {
      /* Instruction size is 32 bits, 4 bytes */
      thumbInstrSize = 4;
  }
  else
  {
      /* Instruction size is 16 bits, 2 bytes */
      thumbInstrSize = 2;
  }

  excDetails.instruction_pt = instr_pt;
  excDetails.data_pt        = data_pt;
  excDetails.syndrome_u32   = syndrome;

  specificHandlerResult = Fls_DsiHandler(&excDetails);

  switch(specificHandlerResult)
  {
    case FLS_HANDLED_SKIP:
      /* exception was handled by one of the functions called above,                       *
       * continue execution, skipping the causing instruction                              *
       * In the test code we assume that the exception was caused by 16-bit/32-bit         *
       * load Thumb instruction => increment return address by the size of the instruction */
      /* polyspace +3 MISRA-C3:18.4 [Justified:Low] "Not a defect." */         
      *((Fls_InstructionAddressType *)instr_pt2pt) = instr_pt + thumbInstrSize;
      /* clear the flags and address register */
      *((volatile uint32*)addr_CFSR) = *((volatile uint32*)addr_CFSR);
      *((uint32*)addr_BFAR) = 0x0;
      skipOrRetry = OS_TRUE;
      break;
    case FLS_HANDLED_RETRY:
      /* exception was handled by one of the functions called above,                          *
       * Continue execution, retrying the causing instruction                                 *
       * Thus, we don't need to modify instr_pt                                               */
      skipOrRetry = OS_TRUE;
      break;
    case FLS_UNHANDLED:
      /* special handling: try to store some info that nobody handled this exception          *
       * Then, try to shut-down in a controlled way. For this purpose we just fall through ...*/
    case FLS_HANDLED_STOP:
      /* Try to shut-down in a controlled way.                                               */
      /* If there's no chance to shut down in a controlled way, just fall through ...        */
    default:
      /* unexpected return - we end in an endless loop                                           */
      break;
  }

  return skipOrRetry;
}
#endif


/*******************************************************************************
** Function Name      : NvM_CddGetStatus                                      **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Service to return the status                          **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Reentrancy         : Non-Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : MemIf_StatusType                                      **
**                                                                            **
**                     MEMIF_UNINIT:The memory stack has not been initialized.**
**                     MEMIF_IDLE:The memory stack is currently idle.         **
**                     MEMIF_BUSY:The memory stack is currently busy.         **
**                                                                            **
** Remarks            : Mem_GetStatus and memory stack operations and cannot  **
**                      execute simultaneously. In order to avoid conflicts   ** 
**                      this API should be used in the exclusive area         **
*******************************************************************************/
FUNC(NvM_OpStatusType, NVM_CODE) NvM_CddGetStatus(void)
{
  NvM_OpStatusType retVal = NVM_OPSTATUS_UNINIT;
  
  if(NvM_GblInitDone == NVM_TRUE)
  {
    #if (MEM_FLS_USED == STD_ON)
    if(Fls_GetStatus() != MEMIF_IDLE)
    {
      retVal = NVM_OPSTATUS_BUSY;
    }
    else
    #endif
    
    #if (MEM_FEE_USED == STD_ON)
    if(Fee_GetStatus() != MEMIF_IDLE)
    {
      retVal = NVM_OPSTATUS_BUSY;
    }
    else
    #endif    
    /* The state of external epromes should also be checked. 
     * If a user job is performed without checking the status, 
     * it is possible that ea/eep/nvm mainfunction are not called in task.
     * during a user job is performing.*/
    #if (MEM_EA_USED == STD_ON)
    if(Ea_GetStatus() != MEMIF_IDLE)
    {
      retVal = NVM_OPSTATUS_BUSY;
    }
    else if(Eep_GetStatus() != MEMIF_IDLE)
    {
      retVal = NVM_OPSTATUS_BUSY;
    }
    else 
    #endif
    if (
      (NVM_MULTIBLK_UNREQUESTED != NvM_GucReadAllRequest)   ||
      (NVM_MULTIBLK_UNREQUESTED != NvM_GucWriteAllRequest)  ||
      (NVM_IDLE != NvM_GucState)                            ||
      (0U       != NvM_GucStdQueEnDis)
    )
    {
      retVal = NVM_OPSTATUS_BUSY;
    }
    else
    {
      retVal = NVM_OPSTATUS_IDLE;
    }    
  }
  
  return retVal;
}


#if ((defined(HWRESOURCE_S32G2X))  && HWRESOURCE_FAMILY(HWRESOURCE_S32G2X))

/* Function to enable DTR OPI mode
 * /Fls/FlsConfigSet/FlsQspiInitCallout */
void FlsQspiDtrOpiEnable(void)
{
  uint8 status_config_reg0[4] = {0x02, 0x02, 0x02, 0x02};      /* DTR OPI enable */

  VAR(uint8, AUTOMATIC) u8Iter = 0U;

  /* Iterate and init all external hardware units. */
  for(u8Iter = 0U; u8Iter < Fls_pConfigPtr->pFlsQspiCfgConfig->u8QspiUnitsCount; u8Iter++)
  {
    CONST(Fls_QspiUnitNameType, FLS_CONST) HwUnit 
      = (*(Fls_pConfigPtr->pFlsQspiCfgConfig->paQspiUnitCfg))[u8Iter].eHwUnitName;
    
    Fls_QspiSetSfarAddr(HwUnit, 0x00000000);

    /*********** write enable ***********/
    /* WRITE_ENABLE_SPI_MODE Index 2 */
    Fls_QspiLaunchLUTNumber(HwUnit, 2*5, 0, 0);
    while (Fls_QspiCheckControllerIdle(HwUnit) == E_NOT_OK)
    {
    }

    /*********** write control reg2 address 0x00000000 ***********/
    Fls_QspiSetSfarAddr(HwUnit, 0x00000000);
    Fls_QspiLoadTXBuffer(HwUnit, &status_config_reg0[0], 4);
    /* WRITE_CONFIG2_REGISTER_SPI_MODE Index 11 */
    Fls_QspiLaunchLUTNumber(HwUnit, 11*5, 1, 0);
    while (Fls_QspiCheckControllerIdle(HwUnit) == E_NOT_OK)
    {
    }
    Fls_QspiResetFlags(HwUnit);
  }
}

#endif

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end RTE:UNR [Not a defect:Low] "Not a defect" */
/* polyspace-end RTE:IDP [Not a defect:Low] "Not a defect" */
/* polyspace-end RTE:NIV [Not a defect:Low] "Not a defect" */
/* polyspace-end RTE:OBAI [Not a defect:Low] "Not a defect" */
/* polyspace-end VARIABLE:ALL [Not a defect:Low] "Not a defect" */
/* polyspace-end MISRA-C3:8.4 [Justified:Low] "Not a defect" */

/*******************************************************************************
**                         End of File                                        **
*******************************************************************************/
