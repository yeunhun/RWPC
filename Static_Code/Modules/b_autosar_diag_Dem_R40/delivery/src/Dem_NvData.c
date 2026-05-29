/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem_NvData.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Provision of NvM related functionality                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision Date:DD-MM-YYYY By            Description                         **
********************************************************************************
** 3.3.4    31-12-2021    LanhLT         Changes made As per Redmine #33335   **
**                                                                            **
** 1.3.3    01-02-2021    EunKyung.Kim   Changes made As per Redmine #28081   **
**                                                                            **
** 1.3.2    04-09-2020    EunKyung.Kim   Changes made As per Redmine #25254   **
**                                                                            **
** 1.3.1    01-06-2020    EunKyung.Kim    Changes made As per Redmine #20595  **
**                                                                            **    
** 1.3.0    10-12-2018    EunKyung.Kim   Changes made As per Redmine #8561    **
**                                                                            **
** 1.2.2     09-11-2018  EunKyung.Kim  Changes made As per Redmine #14481     **
**                                                                            **
** 1.2.1     20-07-2017  EunKyung.Kim  Changes made As per Redmine #9294      **
**                                                                            **
** 1.2.0     16-11-2016  YoungJin.Yun  Changes made As per Redmine #6549      **
**                                                                            **
** 1.1.0     05-16-2016  youngjin.yun  Redmine #1164                          **
**                                                                            **
** 1.0.1     05-11-2016  youngjin.yun  Redmine #4833                          **
**                                                                            **
** 1.0.0     02-07-2015  youngjin.yun  Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"            /* DEM module Header File */
#include "Dem_Ram.h"        /* DEM Ram Header File */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"            /* Det Module Header File */
#endif

#include "NvM.h"              /* NVRAM manager symbols Header File */

#include "SchM_Dem.h"       /* Basic s/w module Scheduler symbols Header File */
#include "Dem_EventMemory.h"
#include "Dem_NvData.h"
#include "Dem_Config.h"

/* polyspace-begin MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-begin DEFECT:USELESS_IF [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#if ((DEM_NUM_OF_PRIMARY_EVENTMEMORY_NVBLOCKID > 0U) ||(DEM_NUM_OF_SECONDARY_EVENTMEMORY_NVBLOCKID > 0U) )
static FUNC(boolean, DEM_CODE) Dem_NvData_RequestNvmFinishJobOnDTCOrigin(
  const Dem_DTCOriginType DTCOrigin,
  const uint8 Filter,
  const boolean Direction);
#endif

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */
#define DEM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
 ** Function Name       : Dem_NvData_GetNvMBlockId > 2                        **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Description         : Get NvM blockId to write non-volatile data in NvRam **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : DTCOrigin, IndexOfNvRamBlockId                      **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : BlockId                                             **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s)     : None                       **
 **                       Dem_ListOfPrimaryNvmBlockId                         **
 **                       Function(s) invoked    : None                       **
 *******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvData_GetNvMBlockId(
  const Dem_NvDataIdType NvDataId,
  const Dem_DTCOriginType DTCOrigin,
  const Dem_NumOfEventMemoryEntryType MemLocation,  
  P2VAR(NvM_BlockIdType, AUTOMATIC, DEM_APPL_DATA) BlockId)
{
  Std_ReturnType retVal = E_NOT_OK;

  *BlockId = 0U;  
  if (DEM_NVDATA_EVENT_MEMORY_ID == NvDataId)
  {
    switch(DTCOrigin)
    {
    #if (DEM_NUM_OF_PRIMARY_EVENTMEMORY_NVBLOCKID > 0U)
    case DEM_DTC_ORIGIN_PRIMARY_MEMORY:
       /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid the runtime error of the polyspace */
      if (MemLocation < Dem_Num_Of_Primary_EventMemory_NvBlockId)
      {
	/* polyspace +2 MISRA-C3:18.1 [Justified:Low] "Not a defect" */  
	/* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */  
        *BlockId = Dem_PrimaryEventMemoryNvmBlockId[MemLocation];
        retVal = E_OK;
      }
      break;  
    #endif
    
    #if (DEM_NUM_OF_SECONDARY_EVENTMEMORY_NVBLOCKID > 0U)
    case DEM_DTC_ORIGIN_SECONDARY_MEMORY:
      /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid the runtime error of the polyspace */  
      if (MemLocation < Dem_Num_Of_Secondary_EventMemory_NvBlockId)
      {
	/* polyspace +2 MISRA-C3:18.1 [Justified:Low] "Not a defect" */  
	/* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */  
        *BlockId = Dem_SecondaryEventMemoryNvmBlockId[MemLocation];
        retVal = E_OK;
      }
      break;
    #endif

    #if (DEM_NUM_OF_PERMANENT_EVENTMEMORY_NVBLOCKID > 0U)
    case DEM_DTC_ORIGIN_PERMANENT_MEMORY:
      /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid the runtime error of the polyspace */  
      if (MemLocation < Dem_Num_Of_Permanent_EventMemory_NvBlockId)
      {
        *BlockId = Dem_PermanentEventMemoryNvmBlockId[MemLocation];
        retVal = E_OK;
      }
      break;
    #endif

    /* polyspace<RTE:UNR:Not a defect:No action planned> Default switch clause is unreachable. switch-expression */
    default :
    /*	Do Nothing	*/
      break;
    }
  }
  else if (DEM_NVDATA_ALL_EVENT_STATUS_ID == NvDataId)
  {
    /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */
    #if (0U != DEM_NVM_BLK_ID_EVENT_STATUS)
    *BlockId = Dem_EventStatusNvRamBlkId;
    retVal = E_OK;
    #endif
  }
  else if (DEM_NVDATA_GENERIC_NVRAM_DATA_ID == NvDataId)
  {
    /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */
    #if (0U != DEM_NVM_BLK_ID_NON_VOLATILE_DATA)
    *BlockId = Dem_NonVolatileDataBlkId;
    retVal = E_OK;
    #endif
  }
  else
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */  
  {
  }

  return retVal;
}

/*******************************************************************************
 ** Function Name       : Dem_NvData_ReadNonVolatileData                      **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Description         : Read the stored data from nv block                  **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : NvDataId                                            **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : BlockId                                             **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE) Dem_NvData_ReadNonVolatileData(const Dem_NvDataIdType NvDataId)
{
  Std_ReturnType retVal = E_NOT_OK;  

  switch(NvDataId)
  {
    case DEM_NVDATA_ALL_EVENT_STATUS_ID:
      #ifdef DEM_NVM_BLK_ID_EVENT_STATUS    
      if (E_OK == NvM_ReadBlock(Dem_EventStatusNvRamBlkId, &Dem_EventStatusNvRamData))
      {
        /* Write request is accepted. */
        retVal = E_OK;
      }
      else
      {
        retVal = DEM_E_PENDING;
      }
      #else
      /* returns E_NOT_OK to initialize event memory */
      retVal = E_NOT_OK;  
      #endif
      
      break;
   case DEM_NVDATA_GENERIC_NVRAM_DATA_ID:
      #ifdef DEM_NVM_BLK_ID_NON_VOLATILE_DATA    
      if (E_OK == NvM_ReadBlock(Dem_NonVolatileDataBlkId, &Dem_NonVolatileData))
      {
        /* Write request is accepted. */
        retVal = E_OK;
      }
      else
      {
        retVal = DEM_E_PENDING;
      }      
      #else
      /* returns E_NOT_OK to initialize event memory */
      retVal = E_NOT_OK;  
      #endif
      
      break;
     
    /* case Xxx_ID */
    /* case Yyy_ID */
    /* polyspace<RTE:UNR:Not a defect:No action planned> Default switch clause is unreachable. switch-expression */    
    default: break;
  }
   
  return retVal;
}

/*******************************************************************************
 ** Function Name       : Dem_NvData_WriteNonVolatileData                     **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Description         : Write the data to nv block                          **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : NvDataId                                            **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : BlockId                                             **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE) Dem_NvData_WriteNonVolatileData(const Dem_NvDataIdType NvDataId)
{
  Std_ReturnType retVal = E_NOT_OK;  
  NvM_RequestResultType nvResult = NVM_REQ_PENDING;
 
  switch(NvDataId)
  {
    case DEM_NVDATA_ALL_EVENT_STATUS_ID:
      #ifdef DEM_NVM_BLK_ID_EVENT_STATUS
      if (E_OK == NvM_GetErrorStatus(Dem_EventStatusNvRamBlkId, &nvResult))
      {
        /* polyspace<MISRA-C:13.7:Not a defect:No action planned> This is output parameter of NvM Api */            
        if (NVM_REQ_PENDING != nvResult)
        {
          if (E_OK == NvM_WriteBlock(Dem_EventStatusNvRamBlkId, &Dem_EventStatusNvRamData))
          {
            retVal = E_OK;
          }
          else
          {
            retVal = DEM_E_PENDING;
          }          
        }        
        else
        {
          retVal = DEM_E_PENDING;
        }
      } 
      #else
      /* returns E_NOT_OK to initialize event memory */
      retVal = E_NOT_OK;        
      #endif
      break;

    case DEM_NVDATA_GENERIC_NVRAM_DATA_ID:
      #ifdef DEM_NVM_BLK_ID_NON_VOLATILE_DATA
      if (E_OK == NvM_GetErrorStatus(Dem_NonVolatileDataBlkId, &nvResult))
      {
        /* polyspace<MISRA-C:13.7:Not a defect:No action planned> This is output parameter of NvM Api */      
        if (NVM_REQ_PENDING != nvResult)
        { 
          if (E_OK == NvM_WriteBlock(Dem_NonVolatileDataBlkId, &Dem_NonVolatileData))
          {          
            retVal = E_OK;         
          }          
          else
          {
            retVal = DEM_E_PENDING;
          }          
        }        
        else
        {
          retVal = DEM_E_PENDING;
        }
      } 
      #else
      /* returns E_NOT_OK to initialize event memory */
      retVal = E_NOT_OK;        
      #endif
      break;
      
    /* case Xxx_ID */
    /* case Yyy_ID */
    /* polyspace<RTE:UNR:Not a defect:No action planned> Default switch clause is unreachable. switch-expression */    
    default: break;
  }
   
  return retVal;
}

/*******************************************************************************
 ** Function Name       : Dem_NvData_RequestNvmFinishJobOnDTCOrigin           **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Description         : Wait until writing jobs are finished                **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : -                                                   **
 **                                                                           **
 ** InOut parameter     : -                                                   **
 **                                                                           **
 ** Output Parameters   : -                                                   **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if ((DEM_NUM_OF_PRIMARY_EVENTMEMORY_NVBLOCKID > 0U) ||(DEM_NUM_OF_SECONDARY_EVENTMEMORY_NVBLOCKID > 0U) )
static FUNC(boolean, DEM_CODE) Dem_NvData_RequestNvmFinishJobOnDTCOrigin(
  const Dem_DTCOriginType DTCOrigin,
  const uint8 Filter,
  const boolean Direction)
{
  boolean pending = DEM_FALSE;
/* polyspace +1 MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
  NvM_BlockIdType blockId = 0U;
  NvM_RequestResultType nvDataResult = NVM_REQ_OK;    
  
  Dem_NumOfEventMemoryEntryType memLoc;

  for (memLoc = 0U; memLoc < Dem_SizeOfEventMemory[DTCOrigin]; memLoc++)  
  {
    if ((boolean)DEM_TRUE == Dem_EvMem_IsEvMemNvBlockStatusFilter(DTCOrigin, memLoc, Filter))
    {      
      /* polyspace<RTE:UNR:Not a defect:No action planned>If-condition always evaluates to true  */
      if (E_OK == Dem_NvData_GetNvMBlockId (DEM_NVDATA_EVENT_MEMORY_ID, DTCOrigin, memLoc, &blockId))
      {
        nvDataResult = Dem_NvData_GetNvMErrorStatus(blockId);        
        if ((NVM_REQ_OK == nvDataResult) || (NVM_REQ_BLOCK_SKIPPED == nvDataResult))
        {
          Dem_EvMem_ClearEvMemNvBlockStatus(DTCOrigin, memLoc, Filter);
        }
        else if(NVM_REQ_PENDING == nvDataResult)
        {
          /* Dcm will invoke NvM_GetErrorStatus on next mainfunction call again */
          pending = DEM_TRUE;
          break;
        }          
        else if(NVM_REQ_NV_INVALIDATED == nvDataResult) /* Read */
        {
          /* At least one block is not written, event memory entry shall be initialized. */
          Dem_EvMem_ClearEvMemNvBlockStatus(DTCOrigin, memLoc, Filter);
        }      
        else 
        { 
          /* if result is any fault, block will be skipped */        
          DEM_REPORT_ERROR(DEM_MAINFUNCTION_SID, DEM_E_NODATAAVAILABLE);
          Dem_EvMem_ClearEvMemNvBlockStatus(DTCOrigin, memLoc, Filter);            
          Dem_EvMem_SetNvmResult(E_NOT_OK);       
        }
      }
    } 
  } /* else {} */ 

  DEM_UNUSED(Direction);
  
  /* Wait to read all event status from NvM */
  return pending;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_NvData_WaitNvmFinishJob                         **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Description         : Wait until writing jobs are finished (all blocks)   **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : -                                                   **
 **                                                                           **
 ** InOut parameter     : -                                                   **
 **                                                                           **
 ** Output Parameters   : -                                                   **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
FUNC(boolean, DEM_CODE) Dem_NvData_WaitNvmFinishJob(
  const uint8 Filter,
  const boolean Direction)
{
  boolean pending = DEM_FALSE;
  Dem_NvDataIdType idx;
  /* @IF_REQ x 100, NOTE, @IF_REQ
   *
   * EventMemory[Num primary entry + num secondary entry...]
   * Regardles of DTCOrigin, only shall use MemLocation 
   */
  Dem_EvMem_SetNvmResult(E_OK);
  #if (DEM_NUM_OF_PRIMARY_EVENTMEMORY_NVBLOCKID > 0U)  
  pending = Dem_NvData_RequestNvmFinishJobOnDTCOrigin(DEM_DTC_ORIGIN_PRIMARY_MEMORY, Filter,Direction);
  #endif
  #if(DEM_MAX_NUMBER_EVENT_ENTRY_SEC > 0u)
  #if (DEM_NUM_OF_SECONDARY_EVENTMEMORY_NVBLOCKID > 0U)
  /* polyspace +1 MISRA-C3:10.1 [Justified:Low] "Not a defect" */
  pending |= Dem_NvData_RequestNvmFinishJobOnDTCOrigin(DEM_DTC_ORIGIN_SECONDARY_MEMORY, Filter,Direction);
  #endif
  #endif

  for (idx = 0U; idx < Dem_NumOfSupportedSingleNvBlocks; idx++)
  {
    Dem_NvDataIdType dataId = Dem_DataIdOfSingleNvBlocks[idx];      
    if ((boolean)DEM_TRUE == Dem_EvMem_NonVolatieDataStatusFilter(dataId, Filter))
    {
      /* polyspace +1 MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
      NvM_BlockIdType blockId;
      /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */
      if (E_OK == Dem_NvData_GetNvMBlockId (dataId, 0U, 0U, &blockId))
      {
        NvM_RequestResultType nvDataResult = NVM_REQ_OK;      
        
        nvDataResult = Dem_NvData_GetNvMErrorStatus(blockId);        
        if ((NVM_REQ_OK == nvDataResult) || (NVM_REQ_BLOCK_SKIPPED == nvDataResult))
        {
          Dem_EvMem_ClearNonVolatieDataStatus(dataId, Filter); 
        }
        else if(NVM_REQ_PENDING == nvDataResult)
        {
          /* Dcm will invoke NvM_GetErrorStatus on next mainfunction call again */
          pending = DEM_TRUE;
        }          
        else if(NVM_REQ_NV_INVALIDATED == nvDataResult) 
        {
          /* At least one block is not written, event memory entry shall be initialized. */
          Dem_EvMem_ClearNonVolatieDataStatus(dataId, Filter);       
        }      
        else 
        { 
          DEM_REPORT_ERROR(DEM_MAINFUNCTION_SID, DEM_E_NODATAAVAILABLE);          
          /* if result is any fault, block will be skipped */
          Dem_EvMem_ClearNonVolatieDataStatus(dataId, Filter);
          Dem_EvMem_SetNvmResult(E_NOT_OK);       
        }
      }
      /* Unreachable code
      else
      {
        Dem_EvMem_ClearNonVolatieDataStatus(dataId, Filter); 
      }
      */
    }  
  }

  DEM_UNUSED(Direction);

  /* Wait to read all event status from NvM */
  return pending;
}

/*******************************************************************************
 ** Function Name       : Dem_NvData_GetNvMErrorStatus                         **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Description         : Get the status of the block                         **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : -                                                   **
 **                                                                           **
 ** InOut parameter     : -                                                   **
 **                                                                           **
 ** Output Parameters   : -                                                   **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
FUNC(NvM_RequestResultType, DEM_CODE)
/* polyspace +1 MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
Dem_NvData_GetNvMErrorStatus(NvM_BlockIdType BlockId)
{
  NvM_RequestResultType nvStatus = NVM_REQ_OK;
  NvM_RequestResultType retVal = NVM_REQ_NOT_OK;

  if (0U != BlockId)
  {
    /* get status from NvM of DEM memory block */
    if (E_OK == NvM_GetErrorStatus(BlockId, &nvStatus))
    {
      switch(nvStatus)
      {
      case NVM_REQ_OK:
        retVal = NVM_REQ_OK;
        break;
      case NVM_REQ_RESTORED_FROM_ROM: /* @REQ : NVM_REQ_NOT_OK or  NVM_REQ_OK ? */
        retVal = NVM_REQ_OK;
        break;
      case NVM_REQ_PENDING :
        retVal = NVM_REQ_PENDING;
        break;   
      case NVM_REQ_NV_INVALIDATED:
        retVal = NVM_REQ_NV_INVALIDATED;
      break; 
      
      #if defined(DEM_NVBLOCKS_CANBE_SKIPPED_ON_SWRESET)
      case NVM_REQ_BLOCK_SKIPPED: /* Skpped NvMReadAll or NvMWriteAll */
        retVal = NVM_REQ_BLOCK_SKIPPED;
        break;
      #else
        /* NVM_REQ_NOT_OK : failed */
      #endif      

      default:
        /* NVM_REQ_REDUNDANCY_FAILED */
        /* NVM_REQ_NOT_OK : failed */
        /* NVM_REQ_INTEGRITY_FAILED : failed */
        /* NVM_REQ_CANCELED : N/A */
        retVal = NVM_REQ_NOT_OK;
        break;
      }
    }
  }
  
  return retVal;
 
}
/*******************************************************************************
 ** Function Name       : Dem_NvData_WriteBlock                               **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Description         : Write the data to the nv block                      **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : -                                                   **
 **                                                                           **
 ** InOut parameter     : -                                                   **
 **                                                                           **
 ** Output Parameters   : -                                                   **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvData_WriteBlock(
  /* polyspace +1 MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
  NvM_BlockIdType BlockId,
  P2CONST(void, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr)
{
  Std_ReturnType retVal = E_OK;
  NvM_RequestResultType nvResult = E_NOT_OK;
  
  if (E_OK == NvM_GetErrorStatus(BlockId, &nvResult))
  {
    if (NVM_REQ_PENDING != nvResult)
    {            
      if (E_OK != NvM_WriteBlock(BlockId, NvM_SrcPtr))
      {        
        retVal = DEM_E_PENDING;
      }
      else
      {
       /* Operation is accepted
        * result = E_OK;
        */       
      }      
    }
    else
    {
      retVal = DEM_E_PENDING;
    }
  }
  else
  {
    retVal = E_NOT_OK;
  }

  return retVal;
}

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:USELESS_IF [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
