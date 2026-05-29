/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem_Obd.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : Provision of OnBoard Diagnostic functionality                 **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision Date:DD-MM-YYYY By            Description                         **
********************************************************************************
** 3.3.4    31-12-2021    LanhLT         Changes made As per Redmine #33335   **
**                                                                            **
** 3.3.3    19-10-2021    LanhLT         Changes made As per Redmine #31306,  **
**                                       #31128                               **
**                                                                            **
** 1.1.4    18-02-2021    EunKyung.Kim   Changes made As per Redmine #25380   **
**                                                                            **
** 1.1.3    04-09-2020    EunKyung.Kim   Changes made As per Redmine #25254   **
**                                                                            **
** 1.1.2    01-06-2020    EunKyung.Kim    Changes made As per Redmine #20595  **
**                                                                            **    
** 1.1.1    02-04-2019    EunKyung.Kim    Changes made As per Redmine #16687  **
**                                                                            **
** 1.1.0    10-12-2018    EunKyung.Kim    Changes made As per Redmine #8561   **
**                                                                            **
** 1.0.8     16-05-2016     YoungJin.Yun  Changes made As per Redmine #1164   **
**                                                                            **
** 1.0.7     11-01-2014     YoungJin.Yun  Changes made As per Redmine #366,   **
**                                        #368,#371,#372,#405,#366,#367,#368, **
**                                        #371,#372,#405,#369,#373,#374,#375, **
**                                        #376,#370,#377,#381,#382,#383,#384, **
**                                        #385,#386,#387,#388,#389,#390,#391, **
**                                        #397,#398,#399,#400,#378,#380,#401, **
**                                        #403,#404,#406,#409,#410,#411,#412  **
**                                        #367,                               **
**                                                                            **
** 1.0.0     01-Jan-2013   Autron      Initial Version                        **
*******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dem.h"                /* DEM module Header File */
#include "Dem_Ram.h"            /* DEM Ram Header File */
#include "SchM_Dem.h"       /* Basic s/w module Scheduler symbols Header File */
#include "NvM.h"              /* NVRAM manager symbols Header File */
#include "Dem_EventRelatedData.h"
#include "Dem_Event.h"
#include "Dem_EventMemory.h"
#include "Dem_ObdRam.h"

#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                /* Det Header File */
#endif

#if (DEM_FIM_INTEGRATED == STD_ON)
#include "FiM.h"
#endif

/*******************************************************************************
**                           Global Data                                      **
*******************************************************************************/
#if(DEM_OBD_SUPPORT == STD_ON)
/* Used to calculate time in sec */
VAR(uint16, DEM_VAR) Dem_GulDemMilOnTimeObdSecCount;

/* Used to calculate time in sec */
VAR(uint16, DEM_VAR) Dem_GulDemClearTimeObdSecCount;
#endif
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && (DEM_OBD_SUPPORT == STD_ON))
FUNC(void, DEM_CODE)Dem_GetFimPermission(
    uint8 RatioIndex,
    boolean* permission );
FUNC(void, DEM_CODE)Dem_GetRatioIndex(
  Dem_EventParameterCPCType event,
  uint32 ArrayIndex,
  P2VAR(uint8, AUTOMATIC,DEM_VAR) RatioId);
#endif

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DEM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Dem_InitOBD                                         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Initialize OBD variables                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Dem_EventIdType EventId                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GulEventIdDisabled                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
**                        SchM_Exit_Dem_CAPTURE_OBD_DATA()                    **
*******************************************************************************/
#if(DEM_OBD_SUPPORT == STD_ON)
FUNC(void, DEM_CODE) Dem_InitOBD(void)
{
  #if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
  uint16 LusRatioIdLockCount;
  uint8 LucGroupRatioCount;
  #endif

  /* Initialise the obd event stored in permanent memory to zero */
  Dem_GusEventstoredinPermanent = DEM_ZERO;
  /* Initialise the obd dtc stored to zero */
  Dem_GusObdDtcFirstStored =  DEM_ZERO;
  /* Initialise the obd event store to false */
  Dem_ObdEventStored = DEM_FALSE;
  /* Initialise the  Milli Second Count to zero */
  Dem_GulDemTimeObdmsCount = DEM_ZERO;
  /* Initialise the Second Count to zero */
  Dem_GulDemMilOnTimeObdSecCount = DEM_ZERO;
  /* Initialise the Second Count to zero */
  Dem_GulDemClearTimeObdSecCount = DEM_ZERO;
  /* Initialise the Time since mil is on to zero */
  Dem_GulTimeSinceMilOn = DEM_ZERO;
  /* Initialise the Mil on flag to false */
  Dem_GucMilonFlag = DEM_ZERO;
  /* Initialise the time since clear function is called to false */
  Dem_GulDemClearTimeCount = DEM_ZERO;

  Dem_GblDtcCleared = Dem_EventStatusNvRamData.DtcClear;
  /* Initialise the warmup cycle count to zero */
  Dem_GusWarmUpCycleCount = DEM_ZERO;

  Dem_GstRecordDisableDTC.usObdDtc = 0U;

  #if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
  Dem_GblRatioInit = DEM_FALSE;
  /* Initialise the ignition cycle count to zero */
  Dem_GusIgnitionCylCnt = Dem_EventStatusNvRamData.IgnitionCylCnt;
  /* Initialise the general denominator for infotype08 and infotype0b as zero
   */
  Dem_GusGeneralDenominator = Dem_EventStatusNvRamData.GeneralDenCnt;
  
  /* Initialise all the ratioid to disable (release) */
  for(LusRatioIdLockCount = DEM_ZERO;
    LusRatioIdLockCount < Dem_Num_Ratio_Info; LusRatioIdLockCount++)
  {
     Dem_GusRatioIdDisable[LusRatioIdLockCount] = DEM_FALSE;
  }
  /* Initialise the numerator and denominator of IUMPR group to zero */
  for(LucGroupRatioCount = DEM_ZERO; LucGroupRatioCount < DEM_SIXTEEN;
   LucGroupRatioCount++)
  {
    Dem_GaaIumprDenominator[LucGroupRatioCount] = Dem_EventStatusNvRamData.IumprDenominator[LucGroupRatioCount];
    Dem_GaaIumprNumerator[LucGroupRatioCount] = Dem_EventStatusNvRamData.IumprNumerator[LucGroupRatioCount];
    Dem_GusRatioMonitored[LucGroupRatioCount] = DEM_FALSE;
  }  
  #endif

  #ifdef DEM_MIL_INDICATORID
  Dem_SetMalfuntionOnOff();
  #endif
}
#endif

/*******************************************************************************
** Function Name        : Dem_MainFunctionOBD                                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Interface for BSW Components to report Errors       **
**                        during start up (even before DEM initialization)    **
**                                                                            **
** Timing:              : FIXED_CYCLIC                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
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
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_GblMilStarted                                   **
**                        Dem_GulTimeSinceMilOn                               **
**                        Dem_GulDemTimeObdmsCount                            **
**                        Dem_GucMilonFlag                                    **
**                        Dem_GblClearTimeStartObd                            **
**                        Dem_GulDemClearTimeCount                            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
/* Check if DEM_OBD_SUPPORT == STD_ON */
#if (DEM_OBD_SUPPORT == STD_ON)
FUNC(void, DEM_CODE) Dem_MainFunctionOBD(void)
{

#if 0
  /* Start the timer in the obd */
  Dem_GulDemTimeObdmsCount = Dem_GulDemTimeObdmsCount + Dem_Task_Time;

  /* Check that mil flag is set or not */
  if(Dem_GucMilonFlag == DEM_BIT7_MASK1)
  {
    /* Check first time after miloff is Mil flag is set*/
    if(Dem_GblMilStarted == DEM_TRUE)
    {
      /* Reset the Mil On time to zero*/
      Dem_GulTimeSinceMilOn = DEM_ZERO;

      Dem_GulDemMilOnTimeObdSecCount = DEM_ZERO;

      /* Reset the flag */
      Dem_GblMilStarted = FALSE;
    }
  }

  if(Dem_GblClearTimeStartObd == DEM_TRUE)
  {
    /* Check first time after miloff is Mil flag is set*/
    if(Dem_GblDtcCleared == DEM_TRUE)
    {
      /* Reset the Mil On time to zero*/
      Dem_GulDemClearTimeCount = DEM_ZERO;

      Dem_GulDemClearTimeObdSecCount = DEM_ZERO;

      /* Reset the flag */
      Dem_GblDtcCleared = FALSE;
    }
  }
  

  /* Check DemTimeObdmsCount is passed 1000sec */
  if(Dem_GulDemTimeObdmsCount >= DEM_THOUSAND_SEC)
  {
    /* Increment the second by one */
    Dem_GulDemMilOnTimeObdSecCount = Dem_GulDemMilOnTimeObdSecCount + DEM_ONE;
    Dem_GulDemClearTimeObdSecCount = Dem_GulDemClearTimeObdSecCount + DEM_ONE;

    /* Reset the milli second to zero */
    Dem_GulDemTimeObdmsCount = DEM_ZERO;

    /* Check 60sec is passed  */
    if(Dem_GulDemMilOnTimeObdSecCount >= DEM_SIXTY_SEC)
    {
      /* Check that mil flag is set or not */
      if(Dem_GucMilonFlag == DEM_BIT7_MASK1)
      {
        /* Increment the mil on count by one */
        Dem_GulTimeSinceMilOn = Dem_GulTimeSinceMilOn + DEM_ONE;
        Dem_EventStatusNvRamData.TimeSinceMilOn = Dem_GulTimeSinceMilOn;
      }

      /* Reset the second count to zero */
      Dem_GulDemMilOnTimeObdSecCount = DEM_ZERO;
    }

    /* Check 60sec is passed  */
    if(Dem_GulDemClearTimeObdSecCount >= DEM_SIXTY_SEC)
    {

      /* Check that Dem_ClearDtc function is called */
      if(Dem_GblClearTimeStartObd == DEM_TRUE)
      {
       /* Increment the count of Dem_ClearDtc is called by one */
       Dem_GulDemClearTimeCount = Dem_GulDemClearTimeCount + DEM_ONE;
       Dem_EventStatusNvRamData.TimeSinceLastClear = Dem_GulDemClearTimeCount;
      }
      /* Reset the second count to zero */
      Dem_GulDemClearTimeObdSecCount = DEM_ZERO;
    }
  }
#endif

}
#endif


/* Check if DEM_OBD_SUPPORT == STD_ON */
#if (DEM_OBD_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventDisabled(Dem_EventIdType EventId)
{
  /* EventId Index */
  Dem_EventIdType LddEventParameterIndex;
  Std_ReturnType LddReturnValue;
  uint32 LulReadinessGroup;

  /* Get the Event Parameter Index */
  LddEventParameterIndex = EventId - DEM_ONE;

  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Module Initialization check */
  if(DEM_INIT != Dem_GucInit)
  {
    /* Report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
    DEM_SETEVENTDISABLED_SID, DEM_E_UNINIT);

    /* Return appropriate value */
    LddReturnValue = E_NOT_OK;
  }
  else if((EventId > Dem_Number_Of_Events) || (DEM_ZERO == EventId))
  {
    /* Report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_SETEVENTDISABLED_SID, DEM_E_PARAM_CONFIG);

    /* Return appropriate value */
    LddReturnValue = E_NOT_OK;
  }
  else
  #endif
  {
    LulReadinessGroup =
      Dem_Event[LddEventParameterIndex].ulEventOBDReadinessGroup;

    SchM_Enter_Dem_CAPTURE_OBD_DATA();

    switch(LulReadinessGroup)
    {

      case DEM_OBD_RDY_MISF:
           {
            /* Disable the event with masking 0x01 */
            Dem_GulEventIdDisabled = Dem_GulEventIdDisabled | DEM_J1939RDY_DISABLE_MISF;
           }
      break;

      case DEM_OBD_RDY_FLSYS:
           {
            /* Disable the event with masking 0x02 */
            Dem_GulEventIdDisabled = Dem_GulEventIdDisabled | DEM_J1939RDY_DISABLE_FLSYS;
           }
      break;

      case DEM_OBD_RDY_CMPRCMPT:
           {
            /* Disable the event with masking 0x04 */
            Dem_GulEventIdDisabled = Dem_GulEventIdDisabled | DEM_J1939RDY_DISABLE_CMPRCMPT;
           }
      break;

      case DEM_OBD_RDY_CAT:
           {
            /* Disable the event with masking 0x08 */
            Dem_GulEventIdDisabled = Dem_GulEventIdDisabled | DEM_J1939RDY_DISABLE_CAT;
           }
      break;

      case DEM_OBD_RDY_HTCAT:
           {
            /* Disable the event with masking 0x10 */
            Dem_GulEventIdDisabled = Dem_GulEventIdDisabled | DEM_J1939RDY_DISABLE_HTCAT;
           }
      break;

      case DEM_OBD_RDY_EVAP:
           {
            /* Disable the event with masking 0x20 */
            Dem_GulEventIdDisabled = Dem_GulEventIdDisabled | DEM_J1939RDY_DISABLE_EVAP;
           }
      break;

      case DEM_OBD_RDY_SECAIR:
           {
            /* Disable the event with masking 0x40 */
            Dem_GulEventIdDisabled = Dem_GulEventIdDisabled | DEM_J1939RDY_DISABLE_SECAIR;
           }
      break;

      case DEM_OBD_RDY_O2SENS:
           {
            /* Disable the event with masking 0x80 */
            Dem_GulEventIdDisabled = Dem_GulEventIdDisabled | DEM_J1939RDY_DISABLE_O2SENS;
           }
      break;

      case DEM_OBD_RDY_O2SENSHT:
           {
            /* Disable the event with masking 0x100 */
            Dem_GulEventIdDisabled = Dem_GulEventIdDisabled | DEM_J1939RDY_DISABLE_O2SENSHT;
           }
      break;

      case DEM_OBD_RDY_ERG:
           {
            /* Disable the event with masking 0x200 */
            Dem_GulEventIdDisabled = Dem_GulEventIdDisabled | DEM_J1939RDY_DISABLE_EGR;
           }
      break;

      case DEM_OBD_RDY_HCCAT:
           {
            /* Disable the event with masking 0x400 */
            Dem_GulEventIdDisabled = Dem_GulEventIdDisabled | DEM_J1939RDY_DISABLE_HCCAT;
           }
      break;

      case DEM_OBD_RDY_NOXCAT:
           {
            /* Disable the event with masking 0x800 */
            Dem_GulEventIdDisabled = Dem_GulEventIdDisabled | DEM_J1939RDY_DISABLE_NOXCAT;
           }
      break;

      case DEM_OBD_RDY_BOOSTPR:
           {
            /* Disable the event with masking 0x1000 */
            Dem_GulEventIdDisabled = Dem_GulEventIdDisabled | DEM_J1939RDY_DISABLE_BOOSTPR;
           }
      break;

      case DEM_OBD_RDY_EGSENS:
           {
            /* Disable the event with masking 0x2000 */
            Dem_GulEventIdDisabled = Dem_GulEventIdDisabled | DEM_J1939RDY_DISABLE_EGSENS;
           }
      break;

      case DEM_OBD_RDY_PMFLT:
           {
            /* Disable the event with masking 0x4000 */
            Dem_GulEventIdDisabled = Dem_GulEventIdDisabled | DEM_J1939RDY_DISABLE_PMFLT;
           }
      break;

      case DEM_OBD_RDY_AC:
           {
            /* Disable the event with masking 0x8000 */
            Dem_GulEventIdDisabled = Dem_GulEventIdDisabled | DEM_J1939RDY_DISABLE_AC;
           }
      break;
      default:
      break;
    }
    SchM_Exit_Dem_CAPTURE_OBD_DATA();

    LddReturnValue = E_OK;
  }
  /* Return E_OK or E_NOT_OK */
  return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dem_DcmReadDataOfPID01                              **
**                                                                            **
** Service ID           : 0x61                                                **
**                                                                            **
** Description          : Service to report the value of PID 01 for Dem       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PID01value                                          **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GulPid01Value                                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError, Dem_CalcPIDValue                   **
*******************************************************************************/
#if (DEM_OBD2_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID01(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID01Value)
{
  Std_ReturnType LddReturnValue;
  #if(DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
  uint8 LaaPid01data[DEM_FOUR];
  Dem_EventIdType LusEventCount;
  Dem_EventIdType LusConfirmedDtcCount;
  uint8 LucByteCount;
  #endif

  LddReturnValue = E_OK;
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Module Initialization check */
  if(DEM_INIT != Dem_GucInit)
  {
     /* Error report to DET */
      (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
        DEM_DCMREADDATAOFPID01_SID, DEM_E_UNINIT);
  }
  else if(NULL_PTR == PID01Value)
  {
    /* Report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_DCMREADDATAOFPID01_SID, DEM_E_PARAM_POINTER);
  }
  else
  #endif
  {
    #if(DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)

    /* Initialise the event count to zero */
    LusEventCount = DEM_ZERO;
    LusConfirmedDtcCount = DEM_ZERO;
    /* Loop to find that number of events whose confirmed bit is set */
    while(LusEventCount < Dem_Number_Of_Events)
    {
      Dem_EventIdType EventId = LusEventCount + 1u;
      Dem_UdsStatusByteType EventStatusMask = 0u;
      
      EventStatusMask = Dem_AllEventStatusByte[EventId];
      /* Check if confirmedDtc bit is set or not */
      if((DEM_BIT3_MASK1 == (EventStatusMask & DEM_BIT3_MASK1)) &&
        (Dem_GaaCombinedDtc[Dem_Event[LusEventCount].e_PointToDTC].ddDtcFormat !=
        DEM_DTC_FORMAT_UDS))
      {
        /* confirmedDtcCount is incremented by 1 */
        LusConfirmedDtcCount = LusConfirmedDtcCount + DEM_ONE;
      }
      /* Increment the count by 1 */
      LusEventCount++;
    }
    /* Check LusConfirmedDtcCountcount is greater than zero or not */
    if(LusConfirmedDtcCount > DEM_ZERO)
    {
      /* Store the bit0 to bit6 of byteA with 0x7f*/
      LaaPid01data[DEM_ZERO] = (uint8)(LusConfirmedDtcCount & DEM_BIT7_MASK2);

      /* update the bit7 to byteA */
      LaaPid01data[DEM_ZERO] = LaaPid01data[DEM_ZERO] | Dem_GucMilonFlag;
    }
    else
    {
      /* Update the byteA of pid01 with 0 as there is no confirmed dtc */
      LaaPid01data[DEM_ZERO] = DEM_ZERO;
    }

    /* PID01 ByteB lowernibble */
    LaaPid01data[DEM_ONE] = DEM_PID01_ByteB_Lower_Nibble &
      DEM_MASK_LOWER_NIBBLE;

    /* Check Misfire is supported or not */
    #if((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_BIT0_MASK) == DEM_BIT0_MASK)
    {
      /* Calculate Byte-2 Bit4 value*/
      Dem_CalcPIDValue(&LaaPid01data[DEM_ONE], (DEM_ONE << BIT_POS_4),
        DEM_OBD_RDY_MISF);
    }
    #else
    {
      /* Misfire not supported then bit4 of byteB is set to 0 */
      LaaPid01data[DEM_ONE] = LaaPid01data[DEM_ONE] & DEM_BIT4_MASK2;
    }
    #endif
    /* Check Fuel system is supported or not */
    #if((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_BIT1_MASK) == DEM_BIT1_MASK)
    {
      /* Calculate Byte-2 Bit5 value*/
      Dem_CalcPIDValue(&LaaPid01data[DEM_ONE], (DEM_ONE << BIT_POS_5),
        DEM_OBD_RDY_FLSYS);
    }
    #else
    {
      /* Fuel system not supported then bit5 is set of byteB to 0 */
      LaaPid01data[DEM_ONE] = LaaPid01data[DEM_ONE] & DEM_BIT5_MASK2;
    }
    #endif

    /* Check Comprehensive component is supported or not */
    #if((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_BIT2_MASK) == DEM_BIT2_MASK)
    {
      /* Calculate Byte-2 Bit6 value*/
      Dem_CalcPIDValue(&LaaPid01data[DEM_ONE], (DEM_ONE << BIT_POS_6),
        DEM_OBD_RDY_CMPRCMPT);
    }
    #else
    {
      /* Comprehensive component not supported then bit6 of byteB is set to 0*/
      LaaPid01data[DEM_ONE] = LaaPid01data[DEM_ONE] & DEM_BIT6_MASK2;
    }
    #endif
    /* bit7 of byteB is set to 0 as it is ISO/SAE reserved */
    LaaPid01data[DEM_ONE] = LaaPid01data[DEM_ONE] & DEM_BIT7_MASK2;

    /* Check for the engine is spark */
    #if((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_BIT3_MASK) == DEM_ZERO)
    {
      /* PID01 ByteC */
      LaaPid01data[DEM_TWO] = DemM_PID01_ByteC_Spark;

      /* Check Catalyst monitoring is supported or not */
      #if((DEM_PID01_BYTEC_SPARK & DEM_BIT0_MASK) == DEM_BIT0_MASK)
      {
        /* Calculate Byte-3 Bit-1 value*/
        Dem_CalcPIDValue(&LaaPid01data[DEM_THREE], DEM_ONE, DEM_OBD_RDY_CAT);
      }
      #else
      {
        /*  Catalyst monitoring not supported then bit0 of byteD is set to 0 */
        LaaPid01data[DEM_THREE] = LaaPid01data[DEM_THREE] & DEM_BIT0_MASK2;
      }
      #endif

      /* Check Heated Catalyst monitoring is supported or not */
      #if((DEM_PID01_BYTEC_SPARK & DEM_BIT1_MASK) == DEM_BIT1_MASK)
      {
        /* Calculate Byte-3 Bit-2 value*/
        Dem_CalcPIDValue(&LaaPid01data[DEM_THREE], (DEM_ONE << BIT_POS_1),
          DEM_OBD_RDY_HTCAT);
      }
      #else
      {
        /* Heated Catalyst monitoring not supported then bit1 of byteD is set to
         0 */
        LaaPid01data[DEM_THREE] = LaaPid01data[DEM_THREE] & DEM_BIT1_MASK2;
      }
      #endif

      /* Check Evaporative system monitoring is supported or not */
      #if((DEM_PID01_BYTEC_SPARK & DEM_BIT2_MASK) == DEM_BIT2_MASK)
      {
        /* Calculate Byte-3 Bit-2 value*/
        Dem_CalcPIDValue(&LaaPid01data[DEM_THREE], (DEM_ONE << BIT_POS_2),
          DEM_OBD_RDY_EVAP);
      }
      #else
      {
        /*  Evaporative system monitoring not supported then bit2 of byteD is
          set to 0 */
        LaaPid01data[DEM_THREE] = LaaPid01data[DEM_THREE] & DEM_BIT2_MASK2;
      }
      #endif

      /* Check Secondary air system monitoring is supported or not */
      #if((DEM_PID01_BYTEC_SPARK & DEM_BIT3_MASK) == DEM_BIT3_MASK)
      {
        /* Calculate Byte-3 Bit-3 value*/
        Dem_CalcPIDValue(&LaaPid01data[DEM_THREE], (DEM_ONE << BIT_POS_3),
          DEM_OBD_RDY_SECAIR);
      }
      #else
      {
        /*  Secondary air system monitoring not supported then bit3 of byteD
          is set to 0 */
        LaaPid01data[DEM_THREE] = LaaPid01data[DEM_THREE] & DEM_BIT3_MASK2;
      }
      #endif
 /* As per ISO 0 is set to 0 */
      LaaPid01data[DEM_THREE] = LaaPid01data[DEM_THREE] & DEM_BIT4_MASK2;

      /*  As per ISO 0 is set to 0 */
      LaaPid01data[DEM_THREE] = LaaPid01data[DEM_THREE] & DEM_BIT4_MASK2;

      /* Check Oxygen sensor monitoring is supported or not */
      #if((DEM_PID01_BYTEC_SPARK & DEM_BIT5_MASK) == DEM_BIT5_MASK)
      {
        /* Calculate Byte-3 Bit-5 value*/
        Dem_CalcPIDValue(&LaaPid01data[DEM_THREE], (DEM_ONE << BIT_POS_5),
          DEM_OBD_RDY_O2SENS);
      }
      #else
      {
        /* Oxygen sensor monitoring not supported then bit5 of byteD
          is set to 0 */
        LaaPid01data[DEM_THREE] = LaaPid01data[DEM_THREE] & DEM_BIT5_MASK2;
      }
      #endif

      /* Check Oxygen sensor heater monitoring is supported or not */
      #if((DEM_PID01_BYTEC_SPARK & DEM_BIT6_MASK) == DEM_BIT6_MASK)
      {
        /* Calculate Byte-3 Bit-6 value*/
        Dem_CalcPIDValue(&LaaPid01data[DEM_THREE], (DEM_ONE << BIT_POS_6),
          DEM_OBD_RDY_O2SENSHT);
      }
      #else
      {
        /* Oxygen sensor heater monitoring not supported then bit6 of byteD
          is set to 0 */
        LaaPid01data[DEM_THREE] = LaaPid01data[DEM_THREE] & DEM_BIT6_MASK2;
      }
      #endif

      /* Check EGR system monitoring is supported or not */
      #if((DEM_PID01_BYTEC_SPARK & DEM_BIT7_MASK) == DEM_BIT7_MASK)
      {
        /* Calculate Byte-3 Bit-7 value*/
        Dem_CalcPIDValue(&LaaPid01data[DEM_THREE], (DEM_ONE << BIT_POS_7),
          DEM_OBD_RDY_ERG);
      }
      #else
      {
        /* EGR system monitoring not supported then bit6 of byteD
          is set to 0 */
        LaaPid01data[DEM_THREE] = LaaPid01data[DEM_THREE] & DEM_BIT7_MASK2;
      }
      #endif
    } /* Check for the engine is spark */
    #else
    {
      /* PID01 ByteC If compression engine */
      LaaPid01data[DEM_TWO] = Dem_PID01_ByteC_Compression;

      /* Check NMHC catalyst monitoring is supported or not */
      #if((DEM_PID01_BYTEC_COMPRESSION & DEM_BIT0_MASK) == DEM_BIT0_MASK)
      {
        /* Calculate Byte-3 Bit-0 value*/
        Dem_CalcPIDValue(&LaaPid01data[DEM_THREE], DEM_ONE, DEM_OBD_RDY_HCCAT);
      }
      #else
      {
        /* NMHC Catalyst monitoring not supported then bit0 of byteD is set to 0
         */
        LaaPid01data[DEM_THREE] = LaaPid01data[DEM_THREE] & DEM_BIT0_MASK2;
      }
      #endif

      /* Check NOx aftertreatment system monitoring is supported or not */
      #if((DEM_PID01_BYTEC_COMPRESSION & DEM_BIT1_MASK) == DEM_BIT1_MASK)
      {
        /* Calculate Byte-3 Bit-1 value*/
        Dem_CalcPIDValue(&LaaPid01data[DEM_THREE], DEM_ONE << BIT_POS_1,
          DEM_OBD_RDY_NOXCAT);
      }
      #else
      {
        /*  NOx aftertreatment system monitoring not supported then bit1 of
            byteD is set to 0
         */
        LaaPid01data[DEM_THREE] = LaaPid01data[DEM_THREE] & DEM_BIT1_MASK2;
      }
      #endif

      /* Set Bit2 of byteD to zero */
      LaaPid01data[DEM_THREE] = LaaPid01data[DEM_THREE] & DEM_BIT2_MASK2;

      /* Check Boost pressure system monitoring is supported or not */
      #if((DEM_PID01_BYTEC_COMPRESSION & DEM_BIT3_MASK) == DEM_BIT3_MASK)
      {
        /* Calculate Byte-3 Bit-3 value*/
        Dem_CalcPIDValue(&LaaPid01data[DEM_THREE], DEM_ONE << BIT_POS_3,
          DEM_OBD_RDY_BOOSTPR);
      }
      #else
      {
        /* Boost pressure system monitoring not supported then bit3 of byteD
           is set to 0
         */
        LaaPid01data[DEM_THREE] = LaaPid01data[DEM_THREE] & DEM_BIT3_MASK2;
      }
      #endif

      /* Set Bit4 of byteD to zero */
      LaaPid01data[DEM_THREE] = LaaPid01data[DEM_THREE] & DEM_BIT4_MASK2;

      /* Check Exhaust gas sensor monitoring is supported or not */
      #if((DEM_PID01_BYTEC_COMPRESSION & DEM_BIT5_MASK) == DEM_BIT5_MASK)
      {
        /* Calculate Byte-3 Bit- value*/
        Dem_CalcPIDValue(&LaaPid01data[DEM_THREE], (DEM_ONE << BIT_POS_5),
          DEM_OBD_RDY_EGSENS);
      }
      #else
      {
        /* Exhaust gas sensor not supported then bit5 of byteD
          is set to 0 */
        LaaPid01data[DEM_THREE] = LaaPid01data[DEM_THREE] & DEM_BIT5_MASK2;
      }
      #endif

      /* Check PM filter monitoring is supported or not */
      #if((DEM_PID01_BYTEC_COMPRESSION & DEM_BIT6_MASK) == DEM_BIT6_MASK)
      {
        /* Calculate Byte-3 Bit-6 value*/
        Dem_CalcPIDValue(&LaaPid01data[DEM_THREE], (DEM_ONE << BIT_POS_6),
          DEM_OBD_RDY_PMFLT);
      }
      #else
      {
        /* PM filter monitoring not supported then bit6 of byteD
          is set to 0 */
        LaaPid01data[DEM_THREE] = LaaPid01data[DEM_THREE] & DEM_BIT6_MASK2;
      }
      #endif

      /* Check EGR system monitoring is supported or not */
      #if((DEM_PID01_BYTEC_COMPRESSION & DEM_BIT7_MASK) == DEM_BIT7_MASK)
      {
        /* Calculate Byte-3 Bit-7 value*/
        Dem_CalcPIDValue(&LaaPid01data[DEM_THREE], (DEM_ONE << BIT_POS_7),
          DEM_OBD_RDY_ERG);

      }
      #else
      {
        /* EGR system monitoring not supported then bit6 of byteD
          is set to 0 */
        LaaPid01data[DEM_THREE] = LaaPid01data[DEM_THREE] & DEM_BIT7_MASK2;
      }
      #endif
    }
    #endif

    /* Initialise  the count value to zero */
    LucByteCount = DEM_ZERO;

    /* Loop for giving the data */
   while (LucByteCount < DEM_FOUR)
   {
     /* Output data into destination buffer */
     *PID01Value = LaaPid01data[LucByteCount];

     /*
      * MISRA Rule        : 17.4
      * Message           : Increment or decrement operation performed
      *                     on pointer.
      * Reason            : Increment operator is used to achieve better
      *                     throughput.
      * Verification      : However, part of the code is verified manually
                            and it is not having any impact
      */
      PID01Value++;

     LucByteCount++;
   }
   #else
   /*No event is present in primary memory */
    *PID01Value = DEM_ZERO;
   #endif
  }/*Det check */
  return(LddReturnValue);
}
#endif
/*******************************************************************************
** Function Name        : Dem_DcmReadDataOfPID21                              **
**                                                                            **
** Service ID           : 0x64                                                **
**                                                                            **
** Description          : Service to report the value of PID 21 for Dem       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PID21value                                          **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GaaPid, Dem_GulTimeSinceMilOn                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError, Dem_GetReadDataOfPID                     **
*******************************************************************************/
/* Check if DEM_OBD_SUPPORT == STD_ON */
#if (DEM_OBD_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID21(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID21Value)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Module Initialization check */
  if(DEM_INIT != Dem_GucInit)
  {
    /* Error report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_DCMREADDATAOFPID21_SID, DEM_E_UNINIT);
    LddReturnValue = E_NOT_OK;
  }
  else if(NULL_PTR == PID21Value)
  {
    /* Report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_DCMREADDATAOFPID21_SID, DEM_E_PARAM_POINTER);
    LddReturnValue = E_NOT_OK;
  }
  else
  #endif
  {

    #if(DEM_MAX_NUMBER_OF_PID_RECDS > DEM_ZERO)
    uint8 LucPidNum;
    uint8 LucCount;

    for(LucCount = DEM_ZERO; LucCount < Dem_Max_Number_Of_PID_Recds; LucCount++)
    {
      LucPidNum = Dem_GaaPid[LucCount].ucPid;
      if(DEM_PID_21 == LucPidNum)
      {
        CONSTP2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
       elementClass = &Dem_DataElementClass[Dem_GaaDataElementRefAry[LucCount].ucDataElementIndex];

        if (NULL_PTR != elementClass->ReadFunc)
        {
          elementClass->ReadFunc(PID21Value);
      

         /* MISRA Rule         : 13.6
          * Message : LucCount being modified in the  body of the loop.
          * Reason : Once the search element found, control exiting
          *          from the for loop to terminate next iteration.
          *Verification : However, part of the code is verified
          *             manually and it is not having any impact.
          */

          /* Exit the loop */
          LucCount = Dem_Max_Number_Of_PID_Recds;
          
        }
      }
    }
    /* Speed is not found */
    if(DEM_PID_21 != LucPidNum)
    {
       /* Km with MIL On is set to zero if speed is not found  */
      *PID21Value = (uint8)DEM_ZERO;

      /*
       * MISRA Rule        : 17.4
       * Message           : Increment or decrement operation performed
       *                     on pointer.
       * Reason            : Increment operator is used to achieve better
       *                     throughput.
       * Verification      : However, part of the code is verified manually
                            and it is not having any impact
       */
       PID21Value++;

      /* Km with MIL On is set to zero if speed is not found  */
      *PID21Value = (uint8)DEM_ZERO;
      LddReturnValue = E_NOT_OK;
    }
      
    #else
       /* Km with MIL On is set to zero if speed is not found  */
      *PID21Value = (uint8)DEM_ZERO;

      /*
       * MISRA Rule        : 17.4
       * Message           : Increment or decrement operation performed
       *                     on pointer.
       * Reason            : Increment operator is used to achieve better
       *                     throughput.
       * Verification      : However, part of the code is verified manually
                            and it is not having any impact
       */
       PID21Value++;

      /* Km with MIL On is set to zero if speed is not found  */
      *PID21Value = (uint8)DEM_ZERO;
      LddReturnValue = E_NOT_OK;
    #endif

    
  #if 0
    /* MISRA Rule : 10.1
     * Message : Implicit conversion from unsigned long to double.
     * Reason : The result will never be greater than unsigned long
     * Verification : However, part of the code is verified
     * manually and it is not having any impact.
     */
    CONSTP2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
     elementClass = Dem_GstGeneralOBDInfo->pOBDInputVehicleSpeed;

    if (NULL_PTR != elementClass->ReadFunc)
    {
      elementClass->ReadFunc(&PID0DValue);

      LulDistanceWithMilOn = (PID0DValue * ((Dem_GulTimeSinceMilOn)*((DEM_CONVERT_MIN_HR)*1000)))/1000;

        if(LulDistanceWithMilOn < DEM_MAXIMUM_DISTANCE_DTC_WITHMILON_OBD)
        {

          /* Store the LSB byte */
          *PID21Value = (uint8)(LulDistanceWithMilOn & DEM_MASK_LOWER_BYTE);


          /*
           * MISRA Rule        : 17.4
           * Message           : Increment or decrement operation performed
           *                     on pointer.
           * Reason            : Increment operator is used to achieve better
           *                     throughput.
           * Verification      : However, part of the code is verified manually
                                 and it is not having any impact
           */           
          /* Increment the address */
          PID21Value++;

          /* Store the MSB byte */
          *PID21Value = (uint8)(LulDistanceWithMilOn & DEM_MASK_UPPER_BYTE);

        }
        else
        {
          *PID21Value = DEM_MAX_0BD_VAL_ALLOWED;
           /*
            * MISRA Rule        : 17.4
            * Message           : Increment or decrement operation performed
            *                     on pointer.
            * Reason            : Increment operator is used to achieve better
            *                     throughput.
            * Verification      : However, part of the code is verified manually
                                  and it is not having any impact
            */
           PID21Value++;

          *PID21Value = DEM_MAX_0BD_VAL_ALLOWED;
        }

        
    }
    else
    {
       /* Km with MIL On is set to zero if speed is not found  */
      *PID21Value = (uint8)DEM_ZERO;

      /*
       * MISRA Rule        : 17.4
       * Message           : Increment or decrement operation performed
       *                     on pointer.
       * Reason            : Increment operator is used to achieve better
       *                     throughput.
       * Verification      : However, part of the code is verified manually
                            and it is not having any impact
       */
       PID21Value++;

      /* Km with MIL On is set to zero if speed is not found  */
      *PID21Value = (uint8)DEM_ZERO;

    }

#endif   
      
#if 0
    #if(DEM_MAX_NUMBER_OF_PID_RECDS > DEM_ZERO)
    for(LucCount = DEM_ZERO; LucCount < Dem_Max_Number_Of_PID_Recds; LucCount++)
    {
      if(DEM_PID_0D == Dem_GaaPid[LucCount].ucPid)
      {
        /* Store the pid value into the variable LucPidNum */
        LucPidNum = Dem_GaaPid[LucCount].ucPid;

        /*Get the speed from the rte */
        /* @IF_REQ :  The size of specific PidClass  is not defined. */
        result = Dem_GetReadDataOfPID(entry, &PID0DValue,
                                      DEM_FALSE, LucPidNum,
                                      DEM_TRUE, 0U);/* ignore data index */ 

        LulDistanceWithMilOn = (PID0DValue * LulTimeWithMilon);

        if(LulDistanceWithMilOn < DEM_MAXIMUM_DISTANCE_DTC_WITHMILON_OBD)
        {
          /* Store the LSB byte */
          *PID21Value = (uint8)(LulDistanceWithMilOn & DEM_MASK_LOWER_BYTE);

          /*
           * MISRA Rule        : 17.4
           * Message           : Increment or decrement operation performed
           *                     on pointer.
           * Reason            : Increment operator is used to achieve better
           *                     throughput.
           * Verification      : However, part of the code is verified manually
                                 and it is not having any impact
           */
          /* Increment the address */
          PID21Value++;

          /* Store the MSB byte */
          *PID21Value = (uint8)(LulDistanceWithMilOn >> DEM_EIGHT);
        }
        else
        {
          *PID21Value = DEM_MAX_0BD_VAL_ALLOWED;
           /*
            * MISRA Rule        : 17.4
            * Message           : Increment or decrement operation performed
            *                     on pointer.
            * Reason            : Increment operator is used to achieve better
            *                     throughput.
            * Verification      : However, part of the code is verified manually
                                  and it is not having any impact
            */
           PID21Value++;

          *PID21Value = DEM_MAX_0BD_VAL_ALLOWED;
        }

       /* MISRA Rule         : 13.6
        * Message : LucCount being modified in the  body of the loop.
        * Reason : Once the search element found, control exiting
        *          from the for loop to terminate next iteration.
        *Verification : However, part of the code is verified
        *             manually and it is not having any impact.
        */

        /* Exit the loop */
        LucCount = Dem_Max_Number_Of_PID_Recds;
      }
    }
    /* Speed is not found */
    if(DEM_PID_0D != LucPidNum)
    {
       /* Km with MIL On is set to zero if speed is not found  */
      *PID21Value = (uint8)DEM_ZERO;

      /*
       * MISRA Rule        : 17.4
       * Message           : Increment or decrement operation performed
       *                     on pointer.
       * Reason            : Increment operator is used to achieve better
       *                     throughput.
       * Verification      : However, part of the code is verified manually
                            and it is not having any impact
       */
       PID21Value++;

      /* Km with MIL On is set to zero if speed is not found  */
      *PID21Value = (uint8)DEM_ZERO;
    }
    #else

       /* Km with MIL On is set to zero if speed is not found  */
      *PID21Value = (uint8)DEM_ZERO;

      /*
       * MISRA Rule        : 17.4
       * Message           : Increment or decrement operation performed
       *                     on pointer.
       * Reason            : Increment operator is used to achieve better
       *                     throughput.
       * Verification      : However, part of the code is verified manually
                            and it is not having any impact
       */
       PID21Value++;

      /* Km with MIL On is set to zero if speed is not found  */
      *PID21Value = (uint8)DEM_ZERO;
    #endif
#endif

  }
  return(LddReturnValue);
}
#endif
/*******************************************************************************
** Function Name        : Dem_DcmReadDataOfPID30                              **
**                                                                            **
** Service ID           : 0x65                                                **
**                                                                            **
** Description          : Service to report the value of PID 30 for Dem       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PID30value                                          **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Function(s) invoked :                               **
**                        Det_ReportError                     **
**                        SchM_Exit_Dem_CAPTURE_OBD_DATA                      **
*******************************************************************************/
/* Check if DEM_OBD_SUPPORT == STD_ON */
#if (DEM_OBD_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID30(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID30Value)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Module Initialization check */
  if(DEM_INIT != Dem_GucInit)
  {
     /* Error report to DET */
      (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
        DEM_DCMREADDATAOFPID30_SID, DEM_E_UNINIT);
  }
  else if(NULL_PTR == PID30Value)
  {
    /* Report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_DCMREADDATAOFPID30_SID, DEM_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* Check count is not maximum */
    if(Dem_EventStatusNvRamData.NumOfWUCSinceLC < DEM_MAX_WARM_UP_COUNT)
    {
      /* Store the LSB byte */
      *PID30Value = Dem_EventStatusNvRamData.NumOfWUCSinceLC;

    }
    else
    {
      *PID30Value = DEM_MAX_WARM_UP_COUNT;
    }

  }
  return(LddReturnValue);
}
#endif
/*******************************************************************************
** Function Name        : Dem_DcmReadDataOfPID31                              **
**                                                                            **
** Service ID           : 0x66                                                **
**                                                                            **
** Description          : Service to report the value of PID 31 for Dem       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PID31value                                          **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):Dem_GulDemClearTimeCount,        **
**                        Dem_GaaPid                                          **
**                        Function(s) invoked :                               **
**                        Det_ReportError, Dem_GetReadDataOfPID               **
*******************************************************************************/
/* Check if DEM_OBD_SUPPORT == STD_ON */
#if (DEM_OBD_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID31(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID31Value)
{
  Std_ReturnType LddReturnValue;


  LddReturnValue = E_OK;
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Module Initialization check */
  if(DEM_INIT != Dem_GucInit)
  {
   /* Error report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_DCMREADDATAOFPID31_SID, DEM_E_UNINIT);
  }
  else if(NULL_PTR == PID31Value)
  {
    /* Report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_DCMREADDATAOFPID31_SID, DEM_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* MISRA Rule : 10.1
     * Message : Implicit conversion from unsigned long to double.
     * Reason : The result will never be greater than unsigned long
     * Verification : However, part of the code is verified
     * manually and it is not having any impact.
     */

    #if(DEM_MAX_NUMBER_OF_PID_RECDS > DEM_ZERO)
    uint8 LucPidNum;
    uint8 LucCount;

    for(LucCount = DEM_ZERO; LucCount < Dem_Max_Number_Of_PID_Recds; LucCount++)
    {
      LucPidNum = Dem_GaaPid[LucCount].ucPid;
      if(DEM_PID_31 == LucPidNum)
      {
        CONSTP2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
       elementClass = &Dem_DataElementClass[Dem_GaaDataElementRefAry[LucCount].ucDataElementIndex];

        if (NULL_PTR != elementClass->ReadFunc)
        {
          elementClass->ReadFunc(PID31Value);
      
          /* Exit the loop */
          LucCount = Dem_Max_Number_Of_PID_Recds;

        }

      }

    }
    
    /* Speed is not found */
    if(DEM_PID_31 != LucPidNum)
    {
       /* Km with MIL On is set to zero if speed is not found  */
      *PID31Value = (uint8)DEM_ZERO;

      /*
       * MISRA Rule        : 17.4
       * Message           : Increment or decrement operation performed
       *                     on pointer.
       * Reason            : Increment operator is used to achieve better
       *                     throughput.
       * Verification      : However, part of the code is verified manually
                            and it is not having any impact
       */
       PID31Value++;

      /* Km with MIL On is set to zero if speed is not found  */
      *PID31Value = (uint8)DEM_ZERO;
      LddReturnValue = E_NOT_OK;
    }
      
    #else
       /* Km with MIL On is set to zero if speed is not found  */
      *PID31Value = (uint8)DEM_ZERO;

      /*
       * MISRA Rule        : 17.4
       * Message           : Increment or decrement operation performed
       *                     on pointer.
       * Reason            : Increment operator is used to achieve better
       *                     throughput.
       * Verification      : However, part of the code is verified manually
                            and it is not having any impact
       */
       PID31Value++;

      /* Km with MIL On is set to zero if speed is not found  */
      *PID31Value = (uint8)DEM_ZERO;
      LddReturnValue = E_NOT_OK;
    #endif

     
#if 0     
    P2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
     elementClass = Dem_GstGeneralOBDInfo->pOBDInputVehicleSpeed;


    if (NULL_PTR != elementClass->ReadFunc)
    {
      elementClass->ReadFunc(&PID0DValue);

      /* Km with DTC clear */
      LulDistanceDtcClear = (PID0DValue * (Dem_GulDemClearTimeCount * ((DEM_CONVERT_MIN_HR)*1000)))/1000;

      if(LulDistanceDtcClear < DEM_MAXIMUM_DISTANCE_DTC_CLEAR_OBD)
      {
        /* Store the LSB of with DTC clear  */
        *PID31Value = (uint8)(LulDistanceDtcClear & DEM_MASK_LOWER_BYTE);

               /*
        * MISRA Rule        : 17.4
        * Message           : Increment or decrement operation performed
        *                     on pointer.
        * Reason            : Increment operator is used to achieve better
        *                     throughput.
        * Verification      : However, part of the code is verified manually
                              and it is not having any impact
        */

        PID31Value++;
        
        /* Store the MSB of Km with DTC clear */
        *PID31Value = (uint8)(LulDistanceDtcClear & DEM_MASK_UPPER_BYTE);


      }
      else
      {
        /* Store the LSB of Km with DTC clear */
        *PID31Value = DEM_MAX_0BD_VAL_ALLOWED;

       /*
        * MISRA Rule        : 17.4
        * Message           : Increment or decrement operation performed
        *                     on pointer.
        * Reason            : Increment operator is used to achieve better
        *                     throughput.
        * Verification      : However, part of the code is verified manually
                              and it is not having any impact
        */
        PID31Value++;

        /* Store the MSB of with DTC clear  */
        *PID31Value = DEM_MAX_0BD_VAL_ALLOWED;
      }/* Exit the loop */

     /* MISRA Rule         : 13.6
      * Message : LucCount being modified in the
      *           body of the loop.
      * Reason : Once the search element found, control exiting
      *          from the for loop to terminate next iteration.
      *Verification : However, part of the code is verified
      *             manually and it is not having any impact.
      */
    }
    else
    {
       /* Km with DTC clear is set to zero if speed is not found  */
      *PID31Value = (uint8)DEM_ZERO;

       /*
        * MISRA Rule        : 17.4
        * Message           : Increment or decrement operation performed
        *                     on pointer.
        * Reason            : Increment operator is used to achieve better
        *                     throughput.
        * Verification      : However, part of the code is verified manually
                              and it is not having any impact
        */
        PID31Value++;

      /* Km with DTC clear is set to zero if speed is not found  */
      *PID31Value = (uint8)DEM_ZERO;
    }
#endif

      
#if 0
    #if(DEM_MAX_NUMBER_OF_PID_RECDS > DEM_ZERO)

    for(LucCount = DEM_ZERO; LucCount < Dem_Max_Number_Of_PID_Recds; LucCount++)
    {
      if(DEM_PID_0D == Dem_GaaPid[LucCount].ucPid)
      {
        /* Store the pid value into the variable LucPidNum */
        LucPidNum = Dem_GaaPid[LucCount].ucPid;

        /*Get the speed from the rte */
        /* @IF_REQ :  The size of specific PidClass  is not defined. */
        Dem_GetReadDataOfPID(entry, &PID0DValue,
                                      DEM_FALSE, LucPidNum,
                                      DEM_TRUE, 0U);/* ignore data index */         

        /* Km with DTC clear */
        LulDistanceDtcClear = (PID0DValue * LulTimeWithDtcClear);

        if(LulDistanceDtcClear < DEM_MAXIMUM_DISTANCE_DTC_CLEAR_OBD)
        {
          /* Store the LSB of Km with DTC clear */
          *PID31Value = (uint8)(LulDistanceDtcClear & DEM_MASK_LOWER_BYTE);

         /*
          * MISRA Rule        : 17.4
          * Message           : Increment or decrement operation performed
          *                     on pointer.
          * Reason            : Increment operator is used to achieve better
          *                     throughput.
          * Verification      : However, part of the code is verified manually
                                and it is not having any impact
          */

          PID31Value++;

          /* Store the MSB of with DTC clear  */
          *PID31Value = (uint8)(LulDistanceDtcClear >> DEM_EIGHT);
        }
        else
        {
          /* Store the LSB of Km with DTC clear */
          *PID31Value = DEM_MAX_0BD_VAL_ALLOWED;

         /*
          * MISRA Rule        : 17.4
          * Message           : Increment or decrement operation performed
          *                     on pointer.
          * Reason            : Increment operator is used to achieve better
          *                     throughput.
          * Verification      : However, part of the code is verified manually
                                and it is not having any impact
          */
          PID31Value++;

          /* Store the MSB of with DTC clear  */
          *PID31Value = DEM_MAX_0BD_VAL_ALLOWED;
        }/* Exit the loop */

       /* MISRA Rule         : 13.6
        * Message : LucCount being modified in the
        *           body of the loop.
        * Reason : Once the search element found, control exiting
        *          from the for loop to terminate next iteration.
        *Verification : However, part of the code is verified
        *             manually and it is not having any impact.
        */

        LucCount = Dem_Max_Number_Of_PID_Recds;
      }
    }
    /* Speed is not found */
    if(DEM_PID_0D != LucPidNum)
    {
       /* Km with DTC clear is set to zero if speed is not found  */
      *PID31Value = (uint8)DEM_ZERO;

       /*
        * MISRA Rule        : 17.4
        * Message           : Increment or decrement operation performed
        *                     on pointer.
        * Reason            : Increment operator is used to achieve better
        *                     throughput.
        * Verification      : However, part of the code is verified manually
                              and it is not having any impact
        */
        PID31Value++;

      /* Km with DTC clear is set to zero if speed is not found  */
      *PID31Value = (uint8)DEM_ZERO;
    }
    #else

       /* Km with DTC clear is set to zero if speed is not found  */
      *PID31Value = (uint8)DEM_ZERO;

       /*
        * MISRA Rule        : 17.4
        * Message           : Increment or decrement operation performed
        *                     on pointer.
        * Reason            : Increment operator is used to achieve better
        *                     throughput.
        * Verification      : However, part of the code is verified manually
                              and it is not having any impact
        */
        PID31Value++;

      /* Km with DTC clear is set to zero if speed is not found  */
      *PID31Value = (uint8)DEM_ZERO;
    #endif
    
#endif

  }
  return(LddReturnValue);
}
#endif
/*******************************************************************************
** Function Name        : Dem_DcmReadDataOfPID41                              **
**                                                                            **
** Service ID           : 0x67                                                **
**                                                                            **
** Description          : Service to report the value of PID 41 for Dem       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PID41value                                          **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError, Dem_GetReadDataOfPID                     **
**                        SchM_Exit_Dem_CAPTURE_OBD_DATA                      **
*******************************************************************************/
/* Check if DEM_OBD_SUPPORT == STD_ON */
#if (DEM_OBD_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID41(
 P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID41Value)
{
  Std_ReturnType LddReturnValue;
  uint8 LaaPid41data[DEM_FOUR];
  uint8 LucByteCount;

  LddReturnValue = E_OK;

  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Module Initialization check */
  if(DEM_INIT != Dem_GucInit)
  {
    /* Error report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_DCMREADDATAOFPID41_SID, DEM_E_UNINIT);
  }
  else if(NULL_PTR == PID41Value)
  {
    /* Report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_DCMREADDATAOFPID41_SID, DEM_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* Set byte1 of Pid41 to Zero as per SAEJ1979 */
    LaaPid41data[DEM_ZERO] = DEM_ZERO;

    /* Initialize local variables to zero */
    LaaPid41data[DEM_ONE] = DEM_ZERO;
    LaaPid41data[DEM_TWO] = DEM_ZERO;
    LaaPid41data[DEM_THREE] = DEM_ZERO;

    /* Check that event is disabled for Misfire monitoring or it is not
     * supported.
     */
    #if((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_BIT0_MASK) != DEM_BIT0_MASK)
    {
    /* Bit0, Bit4 of byte-2 are set to 0 WITH MASK 0XEE*/
      LaaPid41data[DEM_ONE] = LaaPid41data[DEM_ONE] & DEM_MASK;
    }
    #else
    {
      /* check for Enabled */
       if(DEM_ZERO == (Dem_GulEventIdDisabled & DEM_BIT0_MASK1))
       {
         /* Bit0 of byte2 is set to 1 if monitor is Enabled */
         LaaPid41data[DEM_ONE] = LaaPid41data[DEM_ONE] | DEM_BIT0_MASK1;

         /* Calculate Byte-2 Bit4 value*/
         Dem_CalcPIDValue(&LaaPid41data[DEM_ONE], (DEM_ONE << BIT_POS_4),
           DEM_OBD_RDY_MISF);
       }
       else
       {
         /* Bit0 of byte2 is set to 1 if monitor is disabled */
         LaaPid41data[DEM_ONE] = LaaPid41data[DEM_ONE] & DEM_BIT0_MASK2;

         /* Bit-4 of byte2 is set to 1 if monitor is disabled */
         LaaPid41data[DEM_ONE] = LaaPid41data[DEM_ONE] | DEM_BIT4_MASK1;
       }/* If misfire is supported and not disabled */
    }
    #endif

    /* Check that event is disabled for Fuel system monitoring */
    #if((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_BIT1_MASK) != DEM_BIT1_MASK)
    {
      /* Bit1, Bit5 of byte-2 are set to 0 */
      LaaPid41data[DEM_ONE] = LaaPid41data[DEM_ONE] & DEM_MASK_BIT1_BIT5;
    }
    #else
    {
     /* check for Enabled */
     if(DEM_ZERO == (Dem_GulEventIdDisabled & DEM_BIT1_MASK1))
     {
       /* Bit1 of byte2 is set to 1 if monitor is Enabled */
       LaaPid41data[DEM_ONE] = LaaPid41data[DEM_ONE] | DEM_BIT1_MASK1;

       /* Calculate Byte-2 Bit5 value*/
       Dem_CalcPIDValue(&LaaPid41data[DEM_ONE], (DEM_ONE << BIT_POS_5),
         DEM_OBD_RDY_FLSYS);
     }
     else
     {
       /* Bit-1 of byte2 is set to 1 if monitor is disabled */
       LaaPid41data[DEM_ONE] = LaaPid41data[DEM_ONE] & DEM_BIT1_MASK2;

       /* Bit-5 of byte2 is set to 1 if monitor is disabled */
       LaaPid41data[DEM_ONE] = LaaPid41data[DEM_ONE] | DEM_BIT5_MASK1;
     }
    }/* Fuel system enabled */
    #endif

    /* Check that event is disabled for Comprehensive component monitoring */
    #if((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_BIT2_MASK) != DEM_BIT2_MASK)
    {
      /* Bit-2, Bit-6 of byte-2 are set to 0 */
      LaaPid41data[DEM_ONE] = LaaPid41data[DEM_ONE] & DEM_MASK2;
    }
    #else
    {
     /* check for Enabled */
     if(DEM_ZERO == (Dem_GulEventIdDisabled & DEM_UDS_STATUS_PDTC))
     {
       /* Bit-2 of byte2 is set to 1 if monitor is Enabled */
       LaaPid41data[DEM_ONE] = LaaPid41data[DEM_ONE] | DEM_UDS_STATUS_PDTC;

       /* Calculate Byte-2 Bit6 value*/
       Dem_CalcPIDValue(&LaaPid41data[DEM_ONE], (DEM_ONE << BIT_POS_6),
         DEM_OBD_RDY_CMPRCMPT);
     }
     else
     {
       /* Bit-2 of byte2 is set to 0 if monitor is disabled */
       LaaPid41data[DEM_ONE] = LaaPid41data[DEM_ONE] & DEM_BIT2_MASK2;

       /* Bit-6 of byte2 is set to 1 to indicate monitor is not completed */
       LaaPid41data[DEM_ONE] = LaaPid41data[DEM_ONE] | DEM_BIT6_MASK1;
     }
    }/* If Comprehensive component is supported and not disabled */
    #endif

    /* Check Compression ignition monitoring supported*/
    #if((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_BIT3_MASK) == DEM_BIT3_MASK)
    {
      /* Bit3 of byte2 is set to 1 if Compression ignition  supported */
      LaaPid41data[DEM_ONE] = LaaPid41data[DEM_ONE] | DEM_BIT3_MASK1;
    }
    #else
    {
      /* Bit3 of byte2 is set to 0 if Spark ignition monitors supported */
      LaaPid41data[DEM_ONE] = LaaPid41data[DEM_ONE] & DEM_BIT3_MASK2;
    }
    #endif

    /* Set bit7 is set of byte2 to 0 as it is ISO reserved */
    LaaPid41data[DEM_ONE] = LaaPid41data[DEM_ONE] & DEM_BIT7_MASK2;

    /* For calculating PID41 3rd and 4th bytes */
    Dem_CalcPID41_34(&LaaPid41data[DEM_TWO]);

   /* Initialise  the count value to zero */
    LucByteCount = DEM_ZERO;

    /* Loop for giving the data */
    while (LucByteCount < DEM_FOUR)
    {
      /* Output data into destination buffer */
      *PID41Value = LaaPid41data[LucByteCount];
       /*
        *  MISRA Rule        : 17.4
        * Message           : Increment or decrement operation
        *                     performed on pointer.
        * Reason            : Increment operator is used to achieve
        *                     better throughput.
        * Verification      : However, part of the code is verified
        *                     manually and it is not having any impact.
        */
        PID41Value++;

      LucByteCount++;
    }
  }/* Det check */
  return(LddReturnValue);
}
#endif
/*******************************************************************************
** Function Name        : Dem_DcmReadDataOfPID4D                              **
**                                                                            **
** Service ID           : 0x68                                                **
**                                                                            **
** Description          : Service to report the value of PID  4D for Dem      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PID4Dvalue                                          **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GulTimeSinceMilOn                               **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
/* Check if DEM_OBD_SUPPORT == STD_ON */
#if (DEM_OBD_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID4D(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID4DValue)
{
  Std_ReturnType LddReturnValue;


  LddReturnValue = E_OK;
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Module Initialization check */
  if(DEM_INIT != Dem_GucInit)
  {
   /* Error report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_DCMREADDATAOFPID4D_SID, DEM_E_UNINIT);
  }
  else if(NULL_PTR == PID4DValue)
  {
    /* Report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_DCMREADDATAOFPID4D_SID, DEM_E_PARAM_POINTER);
  }
  else
  #endif
  {
    #if(DEM_MAX_NUMBER_OF_PID_RECDS > DEM_ZERO)
    uint8 LucPidNum;
    uint8 LucCount;

    for(LucCount = DEM_ZERO; LucCount < Dem_Max_Number_Of_PID_Recds; LucCount++)
    {
      LucPidNum = Dem_GaaPid[LucCount].ucPid;
      if(DEM_PID_4D == LucPidNum)
      {
        CONSTP2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
       elementClass = &Dem_DataElementClass[Dem_GaaDataElementRefAry[LucCount].ucDataElementIndex];

        if (NULL_PTR != elementClass->ReadFunc)
        {
          elementClass->ReadFunc(PID4DValue);
      


          /* Exit the loop */
          LucCount = Dem_Max_Number_Of_PID_Recds;
          
        }

      }

    }

    /* Speed is not found */
    if(DEM_PID_4D != LucPidNum)
    {
       /* Km with MIL On is set to zero if speed is not found  */
      *PID4DValue = (uint8)DEM_ZERO;

      /*
       * MISRA Rule        : 17.4
       * Message           : Increment or decrement operation performed
       *                     on pointer.
       * Reason            : Increment operator is used to achieve better
       *                     throughput.
       * Verification      : However, part of the code is verified manually
                            and it is not having any impact
       */
       PID4DValue++;

      /* Km with MIL On is set to zero if speed is not found  */
      *PID4DValue = (uint8)DEM_ZERO;
      LddReturnValue = E_NOT_OK;
    }
      
    #else
       /* Km with MIL On is set to zero if speed is not found  */
      *PID4DValue = (uint8)DEM_ZERO;

      /*
       * MISRA Rule        : 17.4
       * Message           : Increment or decrement operation performed
       *                     on pointer.
       * Reason            : Increment operator is used to achieve better
       *                     throughput.
       * Verification      : However, part of the code is verified manually
                            and it is not having any impact
       */
       PID4DValue++;

      /* Km with MIL On is set to zero if speed is not found  */
      *PID4DValue = (uint8)DEM_ZERO;
      LddReturnValue = E_NOT_OK;
    #endif

  

  #if 0
    /* Time since MIL on */
    LulTimeCount = Dem_GulTimeSinceMilOn;

    /* Check the time count is maximum or not */
    if(LulTimeCount < DEM_MAXTIME_COUNT_IN_MIN_PID4E)
    {
      /* Return the time since mil on lsb */
      *PID4DValue = (uint8)(LulTimeCount  & DEM_MASK_LOWER_BYTE);

     /*
      *  MISRA Rule        : 17.4
      * Message           : Increment or decrement operation
      *                     performed on pointer.
      * Reason            : Increment operator is used to achieve
      *                     better throughput.
      * Verification      : However, part of the code is verified
      *                     manually and it is not having any impact.
      */
      PID4DValue++;
      
     /* Return the time since mil on msb */
      *PID4DValue = (uint8)(LulTimeCount & DEM_MASK_UPPER_BYTE);

    }
    else
    {
      /* Return the time since mil on as maximum LSB */
      *PID4DValue = DEM_MAX_0BD_VAL_ALLOWED;
      /*
      *  MISRA Rule        : 17.4
      * Message           : Increment or decrement operation
      *                     performed on pointer.
      * Reason            : Increment operator is used to achieve
      *                     better throughput.
      * Verification      : However, part of the code is verified
      *                     manually and it is not having any impact.
      */
       PID4DValue++;

      /* Return the time since mil on as maximum MSB */
      *PID4DValue = DEM_MAX_0BD_VAL_ALLOWED;
    }
    #endif
  }
  return(LddReturnValue);
}
#endif
/*******************************************************************************
** Function Name        : Dem_DcmReadDataOfPID4E                              **
**                                                                            **
** Service ID           : 0x69                                                **
**                                                                            **
** Description          : Service to report the value of PID  4E for Dem      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PID4Dvalue                                          **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GulDemClearTimeCount                            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
**                        SchM_Exit_Dem_CAPTURE_OBD_DATA                      **
*******************************************************************************/
/* Check if DEM_OBD_SUPPORT == STD_ON */
#if (DEM_OBD_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID4E(
 P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID4EValue)
{
  Std_ReturnType LddReturnValue;
  
  LddReturnValue = E_OK;
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Module Initialization check */
  if(DEM_INIT != Dem_GucInit)
  {
    /* Error report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_DCMREADDATAOFPID4E_SID, DEM_E_UNINIT);
  }
  else if(NULL_PTR == PID4EValue)
  {
    /* Report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_DCMREADDATAOFPID4E_SID, DEM_E_PARAM_POINTER);
  }
  else
  #endif
  {

    #if(DEM_MAX_NUMBER_OF_PID_RECDS > DEM_ZERO)
    uint8 LucPidNum;
    uint8 LucCount;
    for(LucCount = DEM_ZERO; LucCount < Dem_Max_Number_Of_PID_Recds; LucCount++)
    {
      LucPidNum = Dem_GaaPid[LucCount].ucPid;
      if(DEM_PID_4E == LucPidNum)
      {
        CONSTP2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
       elementClass = &Dem_DataElementClass[Dem_GaaDataElementRefAry[LucCount].ucDataElementIndex];

        if (NULL_PTR != elementClass->ReadFunc)
        {
          elementClass->ReadFunc(PID4EValue);
      

          /* Exit the loop */
          LucCount = Dem_Max_Number_Of_PID_Recds;
          
        }

      }

    }

    /* Speed is not found */
    if(DEM_PID_4E != LucPidNum)
    {
       /* Km with MIL On is set to zero if speed is not found  */
      *PID4EValue = (uint8)DEM_ZERO;

      /*
       * MISRA Rule        : 17.4
       * Message           : Increment or decrement operation performed
       *                     on pointer.
       * Reason            : Increment operator is used to achieve better
       *                     throughput.
       * Verification      : However, part of the code is verified manually
                            and it is not having any impact
       */
       PID4EValue++;

      /* Km with MIL On is set to zero if speed is not found  */
      *PID4EValue = (uint8)DEM_ZERO;
      LddReturnValue = E_NOT_OK;
    }
      
    #else
       /* Km with MIL On is set to zero if speed is not found  */
      *PID4EValue = (uint8)DEM_ZERO;

      /*
       * MISRA Rule        : 17.4
       * Message           : Increment or decrement operation performed
       *                     on pointer.
       * Reason            : Increment operator is used to achieve better
       *                     throughput.
       * Verification      : However, part of the code is verified manually
                            and it is not having any impact
       */
       PID4EValue++;

      /* Km with MIL On is set to zero if speed is not found  */
      *PID4EValue = (uint8)DEM_ZERO;
      LddReturnValue = E_NOT_OK;
    #endif

#if 0
    /* Check the time count is maximum or not */
    if(Dem_GulDemClearTimeCount < DEM_MAXTIME_COUNT_IN_MIN_PID4E)
    {

      /* Return the time since the last fault clear happens lsb */
      *PID4EValue = (uint8)(Dem_GulDemClearTimeCount & DEM_MASK_LOWER_BYTE);

     /*
      *  MISRA Rule        : 17.4
      * Message           : Increment or decrement operation
      *                     performed on pointer.
      * Reason            : Increment operator is used to achieve
      *                     better throughput.
      * Verification      : However, part of the code is verified
      *                     manually and it is not having any impact.
      */

      /* Increment the address */
      PID4EValue++;

      /* Return the time since the last fault clear happens msb */
      *PID4EValue = (uint8)(Dem_GulDemClearTimeCount & DEM_MASK_UPPER_BYTE);

    }
    else
    {
      /* Return the time since last fault clear happens as maximum LSB */
      *PID4EValue = DEM_MAX_0BD_VAL_ALLOWED;

     /*
      *  MISRA Rule        : 17.4
      * Message           : Increment or decrement operation
      *                     performed on pointer.
      * Reason            : Increment operator is used to achieve
      *                     better throughput.
      * Verification      : However, part of the code is verified
      *                     manually and it is not having any impact.
      */
       PID4EValue++;

      /* Return the time since last fault clear happens as maximum MSB */
      *PID4EValue = DEM_MAX_0BD_VAL_ALLOWED;
    }
#endif

  }
  return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dem_DcmReadDataOfPID1C                              **
**                                                                            **
** Service ID           : 0x63                                                **
**                                                                            **
** Description          : Service to report the value of PID  1C for Dem      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PID1Cvalue                                          **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GulPid1CValue                                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
**                        SchM_Exit_Dem_CAPTURE_OBD_DATA                      **
*******************************************************************************/
/* Check if DEM_OBD_SUPPORT == STD_ON */
#if (DEM_OBD2_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID1C(
 P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID1CValue)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Module Initialization check */
  if(DEM_INIT != Dem_GucInit)
  {
     /* Error report to DET */
      (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
        DEM_DCMREADDATAOFPID1C_SID, DEM_E_UNINIT);
  }
  else if(NULL_PTR == PID1CValue)
  {
    /* Report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_DCMREADDATAOFPID1C_SID, DEM_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* update the pid1cvalue with OBD compliance */
    *PID1CValue = DEM_OBD_COMPLIANCE;
  }
  return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dem_ReadDataOfTimeEngineStart                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Service to report the value of time since engine    **
**                        starts for Dem                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PIDValue                                            **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GulPid1CValue                                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
#if (DEM_OBD_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_ReadDataOfTimeEngineStart(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PIDValue)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Module Initialization check */
  if(DEM_INIT != Dem_GucInit)
  {
   /* Error report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_DCMREADDATAOFPID31_SID, DEM_E_UNINIT);
  }
  else if(NULL_PTR == PIDValue)
  {
    /* Report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_DCMREADDATAOFPID31_SID, DEM_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* MISRA Rule : 10.1
     * Message : Implicit conversion from unsigned long to double.
     * Reason : The result will never be greater than unsigned long
     * Verification : However, part of the code is verified
     * manually and it is not having any impact.
     */
     
    P2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
     elementClass = Dem_GstGeneralOBDInfo->pOBDTimeSinceEngineStart;


    if (NULL_PTR != elementClass->ReadFunc)
    {
      elementClass->ReadFunc(PIDValue);

    }
    else
    {
       /* Km with DTC clear is set to zero if speed is not found  */
      *PIDValue = (uint8)DEM_ZERO;

       /*
        * MISRA Rule        : 17.4
        * Message           : Increment or decrement operation performed
        *                     on pointer.
        * Reason            : Increment operator is used to achieve better
        *                     throughput.
        * Verification      : However, part of the code is verified manually
                              and it is not having any impact
        */
        PIDValue++;

      /* Km with DTC clear is set to zero if speed is not found  */
      *PIDValue = (uint8)DEM_ZERO;
    }

  }
  return(LddReturnValue);
}
#endif


  /*******************************************************************************
  ** Function Name        : Dem_ReadDataOfOBDFreezeFrame                        **
  **                                                                            **
  ** Service ID           : 0x52                                                **
  **                                                                            **
  ** Description          : This function shall be used to copy a specific      **
  **                        FreezeFrame selected via the associated PID number  **
  **                                                                            **
  ** Sync/Async           : Synchronous                                         **
  **                                                                            **
  ** Re-entrancy          : Non-Reentrant                                       **
  **                                                                            **
  ** Input Parameters     : PID                                                 **
  **                                                                            **
  ** InOut parameter      : BufSize                                             **
  **                                                                            **
  ** Output Parameters    : uint8 *DestBuffer,                                  **
  **                                                                            **
  ** Return parameter     : Std_Returntype                                      **
  **                                                                            **
  ** Preconditions        : None                                                **
  **                                                                            **
  ** Remarks              : Global Variable(s)  :                               **
  **                        Dem_GulEventIdDisabled                              **
  **                                                                            **
  **                        Function(s) invoked :                               **
  **                        Det_ReportError                                     **
  *******************************************************************************/
#if (DEM_OBD2_SUPPORT == STD_ON)
/* @IF_REQ : Dem_ReturnGetFreezeFrameDataByRecordType should be changed to 
          Std_ReturnType in future. */
FUNC(Dem_ReturnGetFreezeFrameDataByRecordType, DEM_CODE)
Dem_DcmGetOBDFreezeFrameData(
  P2VAR(Dem_DTCType, AUTOMATIC, DEM_VAR) DTC,
  P2VAR(uint8, AUTOMATIC, DEM_VAR)DestBuffer,
  P2VAR(uint8, AUTOMATIC, DEM_VAR)BufSize)
{
  Std_ReturnType result = E_NOT_OK;
  Dem_ReturnGetFreezeFrameDataByRecordType retVal = DEM_GET_FFBYRECORD_WRONG_RECORD;
  
  Dem_SizeOfOBDFreezeFrameDataType size = 0U;
  Dem_EventMemoryEntryPtrType entry = NULL_PTR; 
  Dem_EventParameterCPCType event = NULL_PTR;

  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Module Initialization check */
  if(DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_GETOBDFREEZEFRAMEDATA_SID, DEM_E_UNINIT);
    return DEM_GET_FFBYRECORD_WRONG_RECORD;
  }

  if(NULL_PTR == DestBuffer)
  {
    DEM_REPORT_ERROR(DEM_GETOBDFREEZEFRAMEDATA_SID, DEM_E_PARAM_POINTER);
    return DEM_GET_FFBYRECORD_WRONG_RECORD;
  }

  if(NULL_PTR == BufSize)
  {
    DEM_REPORT_ERROR(DEM_GETOBDFREEZEFRAMEDATA_SID, DEM_E_PARAM_POINTER);
    return DEM_GET_FFBYRECORD_WRONG_RECORD;
  }

  if(NULL_PTR == DTC)
  {
    DEM_REPORT_ERROR(DEM_GETOBDFREEZEFRAMEDATA_SID, DEM_E_PARAM_POINTER);
    return DEM_GET_FFBYRECORD_WRONG_RECORD;
  }
  
  #endif
  
  #if(DEM_MAX_NUMBER_OF_PID_RECDS == 0U)
  DEM_REPORT_ERROR(DEM_GETOBDFREEZEFRAMEDATA_SID, DEM_E_PARAM_CONFIG);
  return E_NOT_OK;
  #else

  @IF_REQ : Find obd event.
  /* Get the Primary memory address */
  entry = &Dem_PrimaryEventMemory[DEM_ZERO];

  result = Dem_GetSizeOfOBDFreezeFrameData(event, DEM_TRUE, 0U, &size);
  if (E_NOT_OK == result)
  {
    /*No OBD Freeze Frame configured */   
    DEM_REPORT_ERROR(DEM_GETOBDFREEZEFRAMEDATA_SID, DEM_E_PARAM_CONFIG);
    return DEM_GET_FFBYRECORD_WRONG_RECORD;
  }

  if (0U == size)
  {
    /*No OBD Freeze Frame configured */
    DEM_REPORT_ERROR(DEM_GETOBDFREEZEFRAMEDATA_SID, DEM_E_PARAM_CONFIG);
    return DEM_GET_FFBYRECORD_WRONG_RECORD;
  }
  
  if(*BufSize < size)
  {  
    /* Target buff size is too small. */
    DEM_REPORT_ERROR(DEM_GETOBDFREEZEFRAMEDATA_SID, DEM_E_PARAM_LENGTH);
    return DEM_GET_FFBYRECORD_WRONG_RECORD;
  }

  /* @IF_REQ : FIND OBD EVENT ENTRY !!! */      
  /* Retrieve  a OBD freeze frame data */
  result = Dem_GetReadDataOfPID(entry,DestBuffer,DEM_TRUE, 0U, DEM_TRUE, 0U);
  if (E_NOT_OK == result)
  {
    DEM_REPORT_ERROR(DEM_GETOBDFREEZEFRAMEDATA_SID, DEM_E_PARAM_LENGTH);
    return DEM_GET_FFBYRECORD_WRONG_RECORD;
  }

  result = Dem_GetEventDTC(event,DTC, DEM_DTC_FORMAT_OBD);
  if (E_NOT_OK == result)
  {
    DEM_REPORT_ERROR(DEM_GETOBDFREEZEFRAMEDATA_SID, DEM_E_PARAM_LENGTH);
    return DEM_GET_FFBYRECORD_NO_DTC_FOR_RECORD;            
  }

  *BufSize = size;
  
  return DEM_GET_FFBYRECORD_OK;
  #endif
}
#endif


/*******************************************************************************
** Function Name        : Dem_ReadDataOfOBDFreezeFrame                        **
**                                                                            **
** Service ID           : 0x52                                                **
**                                                                            **
** Description          : This function shall be used to copy a specific      **
**                        FreezeFrame selected via the associated PID number  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : PID                                                 **
**                                                                            **
** InOut parameter      : BufSize                                             **
**                                                                            **
** Output Parameters    : uint8 *DestBuffer,                                  **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GulEventIdDisabled                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
#if (DEM_OBD2_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE)
Dem_ReadDataOfOBDFreezeFrame(
  uint8 PID,
  uint8 DataElementIndexOfPID, 
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)DestBuffer,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)BufSize)
{
  Std_ReturnType retVal = E_NOT_OK;
  P2VAR(Dem_EventMemoryEntryType, AUTOMATIC, DEM_APPL_DATA) entry;
  Dem_EventParameterCPCType event;
  Std_ReturnType result = E_NOT_OK;

  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Module Initialization check */
  if(DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_READDATAOFOBDFREEZEFRAME_SID, DEM_E_UNINIT);
    retVal = E_NOT_OK;
  }
  else if(NULL_PTR == DestBuffer)
  {
    DEM_REPORT_ERROR(DEM_READDATAOFOBDFREEZEFRAME_SID, DEM_E_PARAM_POINTER);
    retVal = E_NOT_OK;
  }
  else if(NULL_PTR == BufSize)
  {
    DEM_REPORT_ERROR(DEM_READDATAOFOBDFREEZEFRAME_SID, DEM_E_PARAM_POINTER);

    retVal = E_NOT_OK;
  }
  else if(DataElementIndexOfPID > Dem_Max_Number_Of_Pid_DataElement)
  {
    DEM_REPORT_ERROR(DEM_READDATAOFOBDFREEZEFRAME_SID, DEM_E_PARAM_CONFIG);
    retVal = E_NOT_OK;
  }
  else
  #endif
  {
    #if(DEM_MAX_NUMBER_OF_PID_RECDS == 0U)
    DEM_REPORT_ERROR(DEM_READDATAOFOBDFREEZEFRAME_SID, DEM_E_PARAM_CONFIG);
    retVal = E_NOT_OK;
    #else
    Dem_SizeOfOBDFreezeFrameDataType size = 0U;
    
    /* Get the Primary memory address */
    /* @IF_REQ:  DO NOT ACCESS VARIABLE, USE FUNCTION */
    entry = &Dem_PrimaryEventMemory[DEM_ZERO];

    //need to fix later
    size = Dem_GetSizeOfOBDFreezeFrameData(event);
    if(*BufSize < size)
    {  
      DEM_REPORT_ERROR(DEM_GETFREEZEFRAMEDATABYDTC_SID,
                        DEM_E_PARAM_LENGTH);
      retVal = DEM_GET_FFBYRECORD_NO_DTC_FOR_RECORD;
    }
    else
    {
      /* @IF_REQ : FIND OBD EVENT ENTRY !!! */
    
      /* @IF_REQ: DTC Format should be verified by 
      Dem_VerifyRecordNumberOfFreezeFrame in future */
      result = Dem_GetReadDataOfPID(entry,DestBuffer,
                          DEM_FALSE, PID, 
                          DEM_FALSE, DataElementIndexOfPID);

      if (E_OK == result)
      {
        *BufSize = size;
        retVal = E_OK;
      }
    } 
    #endif
  }
  return retVal;
}
#endif
/*******************************************************************************
** Function Name        : Dem_RepIUMPRFaultDetect                             **
**                                                                            **
** Service ID           : 0x73                                                **
**                                                                            **
** Description          : Service for reporting that faults are possibly found**
**                        because all conditions are fulfilled.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : RatioID                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_GaaRatioIdInfo                                  **
**                        Dem_Event                                           **
**                        Dem_GaaIumprNumerator                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
#if((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && (DEM_OBD_SUPPORT == STD_ON))
FUNC(Std_ReturnType, DEM_CODE) Dem_RepIUMPRFaultDetect(Dem_RatioIdType RatioID)
{
  Std_ReturnType LddReturnValue;
  uint8 LucIumprGroupId;
  boolean permission, dirty = DEM_FALSE;

  LddReturnValue = E_NOT_OK;

  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Module Initialization check */
  if(DEM_INIT != Dem_GucInit)
  {
    /* Report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
    DEM_REPIUMPRFAULTDETECT_SID, DEM_E_UNINIT);
  }
  else if(RatioID > Dem_Num_Ratio_Info)
  {
    /* Report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_REPIUMPRFAULTDETECT_SID, DEM_E_PARAM_CONFIG);
  }
  else
  #endif
  {
    if(DEM_RATIO_API == Dem_GaaRatioIdInfo[RatioID].ucRatioIdType)
    {
      Dem_GetFimPermission(RatioID, &permission);
      if(permission == DEM_TRUE)
      {     
        Dem_UdsStatusByteType EventStatusMask = 0u;
        Dem_OperationCycleStateType CycleState = (Dem_OperationCycleStateType)DEM_CYCLE_STATE_END;
        
        EventStatusMask = Dem_AllEventStatusByte[Dem_GaaRatioIdInfo[RatioID].rid_EventId];
        (void)Dem_GetOpCycleStateByEvent(Dem_GaaRatioIdInfo[RatioID].rid_EventId, &CycleState);
        if ((CycleState == DEM_CYCLE_STATE_START) &&
            ((EventStatusMask & DEM_UDS_STATUS_PDTC) != DEM_UDS_STATUS_PDTC))
        {
          /* Get the group id for a particular ratioid */
          LucIumprGroupId = Dem_GaaRatioIdInfo[RatioID].ucIUMPRGroup;

          if(Dem_GusRatioMonitored[LucIumprGroupId] == DEM_FALSE)
          {

           /*In IUMPR, if either the numerator or denominator for a specific
           *component reaches the maximum value of 65535, both numbers shall
           *be divided by two before either is incremented again to avoid
           *overflow problems
           */
            if(Dem_GaaIumprDenominator[LucIumprGroupId] ==
                DEM_MAX_DENOMINATOR_NUMERATOR_VALUE)
            {
              Dem_GaaIumprNumerator[LucIumprGroupId] =
                  ((Dem_GaaIumprNumerator[LucIumprGroupId] - DEM_ONE) / DEM_TWO);

              Dem_GaaIumprDenominator[LucIumprGroupId] =
                  ((Dem_GaaIumprDenominator[LucIumprGroupId] - DEM_ONE) / DEM_TWO);
            }
          
            /* Increment the numerator for the requested group */
            Dem_GaaIumprNumerator[LucIumprGroupId]++;
             Dem_GusRatioMonitored[LucIumprGroupId] = DEM_TRUE;
              
            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
            Dem_EventStatusNvRamData.IumprNumerator[LucIumprGroupId] = Dem_GaaIumprNumerator[LucIumprGroupId];
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();            
           
            dirty = DEM_TRUE;
            /* Set return value as true */
            LddReturnValue = E_OK;
          }
        }
      }
    }

  }/* Det check */

  if(dirty == DEM_TRUE)
  {
    Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_DIRTY_NVM);
    Dem_EvMem_TriggerWriteAllBlocks(); 
  }
  
  return(LddReturnValue);
}
#endif
/*******************************************************************************
** Function Name        : Dem_RepIUMPRDenLock                                 **
**                                                                            **
** Service ID           : 0x71                                                **
**                                                                            **
** Description          : Service is used to lock a denominator of a specific **
**                        monitor.                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : RatioID                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_GusRatioIdDisable                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
#if((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && (DEM_OBD_SUPPORT == STD_ON))
FUNC(Std_ReturnType, DEM_CODE) Dem_RepIUMPRDenLock(Dem_RatioIdType RatioID)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_NOT_OK;
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
    /* Module Initialization check */
    if(DEM_INIT != Dem_GucInit)
    {
      /* Report to DET */
      (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
        DEM_REPIUMPRDENLOCK_SID, DEM_E_UNINIT);

    }
    else if(RatioID > Dem_Num_Ratio_Info)
    {
      /* Report to DET */
      (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
        DEM_REPIUMPRDENLOCK_SID, DEM_E_PARAM_CONFIG);
    }
    else
  #endif
    {
      #if (DEM_DEV_ERROR_DETECT == STD_OFF)
      if(RatioID < Dem_Num_Ratio_Info)
      {
      #endif
        /* Lock the ratioid */
        Dem_GusRatioIdDisable[RatioID] = DEM_TRUE;

        LddReturnValue = E_OK;
      #if (DEM_DEV_ERROR_DETECT == STD_OFF)
      }
      #endif
    }/* Det check */
    return(LddReturnValue);
}
#endif
/*******************************************************************************
** Function Name        : Dem_RepIUMPRDenRelease                              **
**                                                                            **
** Service ID           : 0x72                                                **
**                                                                            **
** Description          : This Service is used to release a denominator of a  **
**                        specific monitor                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : RatioID                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_GusRatioIdDisable                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
#if((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && (DEM_OBD_SUPPORT == STD_ON))
FUNC(Std_ReturnType, DEM_CODE) Dem_RepIUMPRDenRelease(Dem_RatioIdType RatioID)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_NOT_OK;
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
    /* Module Initialization check */
    if(DEM_INIT != Dem_GucInit)
    {
      /* Report to DET */
      (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
        DEM_REPIUMPRDENRELEASE_SID, DEM_E_UNINIT);
    }
    else if(RatioID > Dem_Num_Ratio_Info)
    {
      /* Report to DET */
      (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
        DEM_REPIUMPRDENRELEASE_SID, DEM_E_PARAM_CONFIG);
    }
    else
  #endif
    {
      #if (DEM_DEV_ERROR_DETECT == STD_OFF)
      if(RatioID < Dem_Num_Ratio_Info)
      {
      #endif
        /* Release the ratioid */
        Dem_GusRatioIdDisable[RatioID] = DEM_FALSE;

        LddReturnValue = E_OK;
      #if (DEM_DEV_ERROR_DETECT == STD_OFF)
      }
      #endif
    }/* Det check */
    return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dem_SetIUMPRDenCondition                            **
**                                                                            **
** Service ID           : 0xae                                                **
**                                                                            **
** Description          : This Service is used to set condition of denominator**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConditionID                                         **
**                        ConditionStatus                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_GusRatioIdDisable                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
#if((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && (DEM_OBD_SUPPORT == STD_ON))
FUNC(Std_ReturnType, DEM_CODE) Dem_SetIUMPRDenCondition(
  Dem_IumprDenomCondIdType ConditionId,
  Dem_IumprDenomCondStatusType CondidtionStatus)
{

  Std_ReturnType LddReturnValue;

  LddReturnValue = E_NOT_OK;
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
    /* Module Initialization check */
    if(DEM_INIT != Dem_GucInit)
    {
      /* Report to DET */
      (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
        DEM_REPIUMPRDENLOCK_SID, DEM_E_UNINIT);

    }
    else if(ConditionId > DEM_IUMPR_MAX_CONDITION_NUMBER)
    {
      /* Report to DET */
      (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
        DEM_REPIUMPRDENLOCK_SID, DEM_E_PARAM_CONFIG);
    }
    else
  #endif
    {  
      if((ConditionId < DEM_IUMPR_MAX_CONDITION_NUMBER) /*&& ()*/)
      {

        /* Lock the ratioid */
        Dem_GusRatioDenCondState[ConditionId] = DEM_TRUE;

        LddReturnValue = E_OK;

      }

    }/* Det check */
    return(LddReturnValue);
    
}
#endif

/*******************************************************************************
** Function Name        : Dem_GetIUMPRDenCondition                            **
**                                                                            **
** Service ID           : 0xaf                                                **
**                                                                            **
** Description          : This Service is used to get condition of denominator**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConditionID                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ConditionStatus                                     **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_GusRatioIdDisable                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
#if((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && (DEM_OBD_SUPPORT == STD_ON))
FUNC(Std_ReturnType, DEM_CODE) Dem_GetIUMPRDenCondition(
  Dem_IumprDenomCondIdType ConditionId,
  Dem_IumprDenomCondStatusType* CondidtionStatus)
{
  *CondidtionStatus = Dem_GusRatioDenCondState[ConditionId];
  return E_OK;
}
#endif

/*******************************************************************************
** Function Name        : Dem_GetInfoTypeValue08                              **
**                                                                            **
** Service ID           : 0x6b                                                **
**                                                                            **
** Description          : This Service is used to request for IUMPR data      **
**                        according InfoType 08.                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Iumprdata08                                         **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_GaaIumprDenominator                             **
**                        Dem_GusGeneralDenominator                           **
**                        Dem_GusIgnitionCylCnt                               **
**                        Dem_GaaIumprNumerator                               **
**                                                                            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
#if (DEM_OBD_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_GetInfoTypeValue08(
  Dcm_OpStatusType OpStatus, uint8* Iumprdata08)
{
  Std_ReturnType LddReturnValue;

  uint8 LucIndex;

  LddReturnValue = E_OK;
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
    /* Module Initialization check */
    if(DEM_INIT != Dem_GucInit)
    {
      /* Report to DET */
      (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
        DEM_GETINFOTYPEVALUE08_SID, DEM_E_UNINIT);
    }
    else if(DCM_INITIAL != OpStatus)
    {
      /* Report to DET */
      (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
        DEM_GETINFOTYPEVALUE08_SID, DEM_E_PARAM_CONFIG);
    }
    else if(NULL_PTR == Iumprdata08)
    {
      /* Report to DET */
      (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
        DEM_GETINFOTYPEVALUE08_SID, DEM_E_PARAM_POINTER);
    }
    else
  #endif
    {

      /* Check if op status is dcm_initial */
      #if (DEM_DEV_ERROR_DETECT != STD_ON)
      if(DCM_INITIAL == OpStatus)
      {
      #endif
        LucIndex = DEM_ZERO;

        /* OBD Monitoring Conditions Encountered Counts */
        /* Higher byte */
        Iumprdata08[LucIndex] = (uint8)(Dem_GusGeneralDenominator >> DEM_EIGHT);

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata08[LucIndex] = (uint8)Dem_GusGeneralDenominator;

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Ignition Cycle Counter */
        /* Higher byte */
        Iumprdata08[LucIndex] = (uint8)(Dem_GusIgnitionCylCnt >> DEM_EIGHT);

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata08[LucIndex] = (uint8)Dem_GusIgnitionCylCnt;

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Catalyst Monitor Completion Counts Bank 1 (Numerator) */
        /* Higher byte */
        Iumprdata08[LucIndex] =
          (uint8)(Dem_GaaIumprNumerator[DEM_ONE] >> DEM_EIGHT);

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata08[LucIndex] = (uint8)Dem_GaaIumprNumerator[DEM_ONE];

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Catalyst Monitor Conditions Encountered Counts Bank 1 (Denominator)
         */
        /* Higher byte */
        Iumprdata08[LucIndex] =
          (uint8)(Dem_GaaIumprDenominator[DEM_ONE] >> DEM_EIGHT);

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata08[LucIndex] = (uint8)Dem_GaaIumprDenominator[DEM_ONE];

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Catalyst Monitor Completion Counts Bank 2 (Numerator) */
        /* Higher byte */
        Iumprdata08[LucIndex] =
          (uint8)(Dem_GaaIumprNumerator[DEM_TWO] >> DEM_EIGHT);

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata08[LucIndex] = (uint8)Dem_GaaIumprNumerator[DEM_TWO];

         /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Catalyst Monitor Conditions Encountered Counts Bank 2 (Denominator)
         */
        /* Higher byte */
        Iumprdata08[LucIndex] =
          (uint8)(Dem_GaaIumprDenominator[DEM_TWO] >> DEM_EIGHT);

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata08[LucIndex] = (uint8)Dem_GaaIumprDenominator[DEM_TWO];

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* O2 Sensor Monitor Completion Counts Bank 1 (Numerator) */
        /* Higher byte */
        Iumprdata08[LucIndex] =
          (uint8)(Dem_GaaIumprNumerator[DEM_NINE] >> DEM_EIGHT);

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata08[LucIndex] = (uint8)Dem_GaaIumprNumerator[DEM_NINE];

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* O2 Sensor Monitor Conditions Encountered Counts Bank 1 (Denominator)
         */
        /* Higher byte */
        Iumprdata08[LucIndex] =
          (uint8)(Dem_GaaIumprDenominator[DEM_NINE] >> DEM_EIGHT);

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata08[LucIndex] = (uint8)Dem_GaaIumprDenominator[DEM_NINE];

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* O2 Sensor Monitor Completion Counts Bank 2 (Numerator) */
        /* Higher byte */
        Iumprdata08[LucIndex] =
          (uint8)(Dem_GaaIumprNumerator[DEM_TEN] >> DEM_EIGHT);

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata08[LucIndex] = (uint8)Dem_GaaIumprNumerator[DEM_TEN];

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* O2 Sensor Monitor Conditions Encountered Counts Bank2 (Denominator)
         */
        /* Higher byte */
        Iumprdata08[LucIndex] =
          (uint8)(Dem_GaaIumprDenominator[DEM_TEN] >> DEM_EIGHT);

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata08[LucIndex] = (uint8)Dem_GaaIumprDenominator[DEM_TEN];

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* EGR and/or VVT Monitor Completion Condition Counts (Numerator) */
        /* Higher byte */
        Iumprdata08[LucIndex] =
          (uint8)(Dem_GaaIumprNumerator[DEM_THREE] >> DEM_EIGHT);

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata08[LucIndex] = (uint8)Dem_GaaIumprNumerator[DEM_THREE];

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* EGR and/or VVT Monitor Conditions Encountered counts (Denominator) */
        /* Higher byte */
        Iumprdata08[LucIndex] =
          (uint8)(Dem_GaaIumprDenominator[DEM_THREE] >> DEM_EIGHT);

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata08[LucIndex] = (uint8)Dem_GaaIumprDenominator[DEM_THREE];

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* AIR Monitor Completion Condition Counts (Secondary AIR) (Numerator)
         */
        /* Higher byte */
        Iumprdata08[LucIndex] =
          (uint8)(Dem_GaaIumprNumerator[DEM_THIRTEEN] >> DEM_EIGHT);

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata08[LucIndex] = (uint8)Dem_GaaIumprNumerator[DEM_THIRTEEN];

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* AIR Monitor Conditions Encountered Counts (Secondary AIR)
         * (Denominator)
         */
        /* Higher byte */
        Iumprdata08[LucIndex] =
          (uint8)(Dem_GaaIumprDenominator[DEM_THIRTEEN] >> DEM_EIGHT);

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata08[LucIndex] =
          (uint8)Dem_GaaIumprDenominator[DEM_THIRTEEN];

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* EVAP Monitor Completion Condition Counts (Numerator) */
        /* Higher byte */
        Iumprdata08[LucIndex] =
          (uint8)(Dem_GaaIumprNumerator[DEM_FIVE] >> DEM_EIGHT);

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata08[LucIndex] = (uint8)Dem_GaaIumprNumerator[DEM_FIVE];

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* EVAP Monitor Conditions Encountered Counts (Denominator) */
        /* Higher byte */
        Iumprdata08[LucIndex] =
          (uint8)(Dem_GaaIumprDenominator[DEM_FIVE] >> DEM_EIGHT);

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata08[LucIndex] = (uint8)Dem_GaaIumprDenominator[DEM_FIVE];

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Secondary O2 Sensor Monitor Completion Counts Bank 1 (Numerator) */
        /* Higher byte */
        Iumprdata08[LucIndex] =
          (uint8)(Dem_GaaIumprNumerator[DEM_FOURTEEN] >> DEM_EIGHT);

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata08[LucIndex] = (uint8)Dem_GaaIumprNumerator[DEM_FOURTEEN];

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Secondary O2 Sensor Monitor Conditions Encountered Counts Bank 1
         * (Denominator)
         */
        /* Higher byte */
        Iumprdata08[LucIndex] =
          (uint8)(Dem_GaaIumprDenominator[DEM_FOURTEEN] >> DEM_EIGHT);

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata08[LucIndex] = (uint8)Dem_GaaIumprDenominator[DEM_FOURTEEN];

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Secondary O1 Sensor Monitor Completion Counts Bank 1 (Numerator) */
        /* Higher byte */
        Iumprdata08[LucIndex] =
          (uint8)(Dem_GaaIumprNumerator[DEM_FIFTEEN] >> DEM_EIGHT);

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata08[LucIndex] = (uint8)Dem_GaaIumprNumerator[DEM_FIFTEEN];

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Secondary O1 Sensor Monitor Conditions Encountered Counts Bank 1
         * (Denominator)
         */
        /* Higher byte */
        Iumprdata08[LucIndex] =
          (uint8)(Dem_GaaIumprDenominator[DEM_FIFTEEN] >> DEM_EIGHT);

        /* Increment index by one */
        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata08[LucIndex] = (uint8)Dem_GaaIumprDenominator[DEM_FIFTEEN];
      #if (DEM_DEV_ERROR_DETECT != STD_ON)
      }/* End of if(OpStatus != DCM_INITIAL)*/
      #endif
    }/* Det check */
    return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dem_GetInfoTypeValue0B                              **
**                                                                            **
** Service ID           : 0x6c                                                **
**                                                                            **
** Description          : This Service is used to request for IUMPR data      **
**                        according InfoType0B.                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Iumprdata0B                                         **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_GusGeneralDenominator                           **
**                        Dem_GusIgnitionCylCnt                               **
**                        Dem_GaaIumprNumerator                               **
**                        Dem_GaaIumprDenominator                             **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
#if (DEM_OBD_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_GetInfoTypeValue0B(
  Dcm_OpStatusType OpStatus, uint8* Iumprdata0B)
{
  Std_ReturnType LddReturnValue;
  uint8 LucIndex;

  LddReturnValue = E_OK;
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
    /* Module Initialization check */
    if(DEM_INIT != Dem_GucInit)
    {
      /* Report to DET */
      (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
        DEM_GETINFOTYPEVALUE0B_SID, DEM_E_UNINIT);
    }
    else if(DCM_INITIAL != OpStatus)
    {
      /* Report to DET */
      (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
        DEM_GETINFOTYPEVALUE0B_SID, DEM_E_PARAM_CONFIG);
    }
    else if(NULL_PTR == Iumprdata0B)
    {
      /* Report to DET */
      (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
        DEM_GETINFOTYPEVALUE0B_SID, DEM_E_PARAM_POINTER);
    }
    else
  #endif
    {
      #if (DEM_DEV_ERROR_DETECT != STD_ON)
      if(DCM_INITIAL == OpStatus)
      {
      #endif
        LucIndex = DEM_ZERO;

        /* OBD Monitoring Conditions Encountered Counts */
        /* Higher byte */
        Iumprdata0B[LucIndex] = (uint8)(Dem_GusGeneralDenominator >> DEM_EIGHT);

        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata0B[LucIndex] = (uint8)Dem_GusGeneralDenominator;

        LucIndex = LucIndex + DEM_ONE;

        /* Ignition Cycle Counter */
        /* Higher byte */
        Iumprdata0B[LucIndex] = (uint8)(Dem_GusIgnitionCylCnt >> DEM_EIGHT);

        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata0B[LucIndex] = (uint8)Dem_GusIgnitionCylCnt;

        LucIndex = LucIndex + DEM_ONE;

        /* NMHC Catalyst Monitor Completion Condition Counts (Numerator) */
        /* Higher byte */
        Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprNumerator[DEM_SIX] >>
          DEM_EIGHT);

        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata0B[LucIndex] = (uint8)Dem_GaaIumprNumerator[DEM_SIX];

        LucIndex = LucIndex + DEM_ONE;

        /* NMHC Catalyst Monitor Conditions Encountered Counts (Denominator) */
        /* Higher byte */
        Iumprdata0B[LucIndex] =
          (uint8)(Dem_GaaIumprDenominator[DEM_SIX] >> DEM_EIGHT);

        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata0B[LucIndex] = (uint8)Dem_GaaIumprDenominator[DEM_SIX];

        LucIndex = LucIndex + DEM_ONE;

        /* NOx Catalyst Monitor Completion Condition Counts (Numerator) */
        /* Higher byte */
        Iumprdata0B[LucIndex] =
          (uint8)(Dem_GaaIumprNumerator[DEM_EIGHT] >> DEM_EIGHT);

        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata0B[LucIndex] = (uint8)Dem_GaaIumprNumerator[DEM_EIGHT];

        LucIndex = LucIndex + DEM_ONE;

        /* NOx Catalyst Monitor Conditions Encountered Counts (Denominator) */
        /* Higher byte */
        Iumprdata0B[LucIndex] =
          (uint8)(Dem_GaaIumprDenominator[DEM_EIGHT] >> DEM_EIGHT);

        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata0B[LucIndex] = (uint8)Dem_GaaIumprDenominator[DEM_EIGHT];

        LucIndex = LucIndex + DEM_ONE;

        /* NOx Adsorber Monitor Completion Condition Counts (Numerator) */
        /* Higher byte */
        Iumprdata0B[LucIndex] =
          (uint8)(Dem_GaaIumprNumerator[DEM_SEVEN] >> DEM_EIGHT);

        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata0B[LucIndex] = (uint8)Dem_GaaIumprNumerator[DEM_SEVEN];

        LucIndex = LucIndex + DEM_ONE;

        /* NOx Adsorber Monitor Conditions Encountered Counts (Denominator) */
        /* Higher byte */
        Iumprdata0B[LucIndex] =
          (uint8)(Dem_GaaIumprDenominator[DEM_SEVEN] >> DEM_EIGHT);

        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata0B[LucIndex] = (uint8)Dem_GaaIumprDenominator[DEM_SEVEN];

        LucIndex = LucIndex + DEM_ONE;

        /* PM Filter Monitor Completion Condition Counts (Numerator) */
        /* Higher byte */
        Iumprdata0B[LucIndex] =
          (uint8)(Dem_GaaIumprNumerator[DEM_ELEVEN] >> DEM_EIGHT);

        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata0B[LucIndex] = (uint8)Dem_GaaIumprNumerator[DEM_ELEVEN];

        LucIndex = LucIndex + DEM_ONE;

        /* PM Filter Monitor Conditions Encountered Counts (Denominator) */
        /* Higher byte */
        Iumprdata0B[LucIndex] =
          (uint8)(Dem_GaaIumprDenominator[DEM_ELEVEN] >> DEM_EIGHT);

        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata0B[LucIndex] = (uint8)Dem_GaaIumprDenominator[DEM_ELEVEN];

        LucIndex = LucIndex + DEM_ONE;

        /* Exhaust Gas Sensor Monitor Completion Condition Counts (Numerator) */
        /* Higher byte */
        Iumprdata0B[LucIndex] =
          (uint8)(Dem_GaaIumprNumerator[DEM_FOUR] >> DEM_EIGHT);

        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata0B[LucIndex] = (uint8)Dem_GaaIumprNumerator[DEM_FOUR];

        LucIndex = LucIndex + DEM_ONE;

        /* Exhaust Gas Sensor Monitor Conditions Encountered counts
         * (Denominator)
         */
        /* Higher byte */
        Iumprdata0B[LucIndex] =
          (uint8)(Dem_GaaIumprDenominator[DEM_FOUR] >> DEM_EIGHT);

        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata0B[LucIndex] = (uint8)Dem_GaaIumprDenominator[DEM_FOUR];

        LucIndex = LucIndex + DEM_ONE;

        /* EGR and/or VVT Monitor Completion Condition Counts (Numerator) */
        /* Higher byte */
        Iumprdata0B[LucIndex] =
          (uint8)(Dem_GaaIumprNumerator[DEM_THREE] >> DEM_EIGHT);

        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata0B[LucIndex] = (uint8)Dem_GaaIumprNumerator[DEM_THREE];

        LucIndex = LucIndex + DEM_ONE;

        /* EGR and/or VVT Monitor Conditions Encountered counts (Denominator) */
        /* Higher byte */
        Iumprdata0B[LucIndex] =
          (uint8)(Dem_GaaIumprDenominator[DEM_THREE] >> DEM_EIGHT);

        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata0B[LucIndex] = (uint8)Dem_GaaIumprDenominator[DEM_THREE];

         LucIndex = LucIndex + DEM_ONE;

        /* Boost Pressure Monitor Completion Condition Counts (Numerator) */
        /* Higher byte */
        Iumprdata0B[LucIndex] =
          (uint8)(Dem_GaaIumprNumerator[DEM_ZERO] >> DEM_EIGHT);

        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata0B[LucIndex] = (uint8)Dem_GaaIumprNumerator[DEM_ZERO];

        LucIndex = LucIndex + DEM_ONE;

        /* Boost Pressure Monitor Conditions Encountered counts (Denominator) */
        /* Higher byte */
        Iumprdata0B[LucIndex] =
          (uint8)(Dem_GaaIumprDenominator[DEM_ZERO] >> DEM_EIGHT);

        LucIndex = LucIndex + DEM_ONE;

        /* Lower byte */
        Iumprdata0B[LucIndex] = (uint8)Dem_GaaIumprDenominator[DEM_ZERO];
      #if (DEM_DEV_ERROR_DETECT != STD_ON)
      }
      #endif
    }/* Det check */
    return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dem_GetDTCOfOBDFreezeFrame                          **
**                                                                            **
** Service ID           : 0x53                                                **
**                                                                            **
** Description          : Gets DTC by freeze frame record number              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : FrameNumber                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint8 *DTC,                                         **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
#if (DEM_OBD_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_GetDTCOfOBDFreezeFrame(uint8
  FrameNumber, P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA)DTC)
{
  Std_ReturnType LddReturnValue;

  uint32 LulDTC;

  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Module Initialization check */
  if(DEM_INIT != Dem_GucInit)
  {
    /* Error report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_GETDTCOFOBDFREEZEFRAME_SID, DEM_E_UNINIT);

    /* Return Value is set to not ok */
    LddReturnValue = E_NOT_OK;
  }
  else if(DTC == NULL_PTR)
  {
    /* Report to DET */
   (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
    DEM_GETDTCOFOBDFREEZEFRAME_SID, DEM_E_PARAM_POINTER);

    /* Return Value is set to not ok */
    LddReturnValue = E_NOT_OK;
  }
  else
  #endif
  {
    /* Check if Freeze Frame number is zero or not*/
    if(DEM_ZERO == FrameNumber)
    {
      LulDTC = (uint32)Dem_GusObdDtcFirstStored;

      /* Most important freeze frame dtc */
      *DTC = (LulDTC << 8) & 0xFFFF00;

      LddReturnValue = E_OK;
    }/* Check Freeze frame record number */
    else
    {
       #if (DEM_DEV_ERROR_DETECT == STD_ON)
        /* Error report to DET */
        (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
          DEM_GETDTCOFOBDFREEZEFRAME_SID, DEM_E_PARAM_CONFIG);
       #endif

      /* Return Value is set to not ok */
      LddReturnValue = E_NOT_OK;
    }
  }/* Det check */
  return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dem_SetPtoStatus                                    **
**                                                                            **
** Service ID           : 0x79                                                **
**                                                                            **
** Description          : This API is available for support of pid 1E         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : PtoStatus                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GblPtoStatus                                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
#if (DEM_OBD_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetPtoStatus(boolean PtoStatus)
{
  Std_ReturnType LddReturnValue;

  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Module Initialization check */
  if(DEM_INIT != Dem_GucInit)
  {
    /* Error report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_SETPTOSTATUS_SID, DEM_E_UNINIT);

    /* Return Value is set to not ok */
    LddReturnValue = E_NOT_OK;
  }

  else if((PtoStatus != DEM_TRUE) && (PtoStatus != DEM_FALSE))
  {
   /* Report to DET */
   (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
    DEM_SETPTOSTATUS_SID, DEM_E_PARAM_CONFIG);

    /* Return Value is set to not ok */
    LddReturnValue = E_NOT_OK;
   }
  else
  #endif
  {    /* Check new status is same as old status */
    if(PtoStatus !=  Dem_GblPtoStatus)
    {
      Dem_GblPtoStatus = PtoStatus;

      LddReturnValue = E_OK;
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }
  }
  return(LddReturnValue);
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_GetFimPermission                                **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Function is used to get Fim permission              **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : RatioIndex                                          **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : permission                                          **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && (DEM_OBD_SUPPORT == STD_ON))
FUNC(void, DEM_CODE)Dem_GetFimPermission(
    uint8 RatioIndex,
    boolean* permission )
{

  #if (DEM_FIM_INTEGRATED == STD_ON)
  uint8 i = 0;
  FiM_GetFunctionPermission(Dem_GaaRatioIdInfo[RatioIndex].ucPrimaryFid, permission);
  if(*permission == DEM_TRUE)
  {
    if(Dem_GaaRatioIdInfo[RatioIndex].ucNumofSecFid >0)
    {
      for(i = 0; i < Dem_GaaRatioIdInfo[RatioIndex].ucNumofSecFid; i++)
      {
        FiM_GetFunctionPermission(Dem_GaaRatioIdInfo[RatioIndex].ucSecondaryFid[i], permission);
        if(*permission == DEM_FALSE)
        {
          break;
        }

      }

    }
  }
  #endif

  return;
}
#endif


/*******************************************************************************
 ** Function Name       : Dem_ProcessIumpr                                    **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Function is used to get ratio index                 **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : event, EventStatus                                  **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && (DEM_OBD_SUPPORT == STD_ON))
FUNC(Std_ReturnType, DEM_CODE)Dem_ProcessIumpr(
    Dem_EventParameterCPCType event,
    Dem_UdsStatusByteType EventStatus)
{
  Std_ReturnType LddReturnValue = E_OK;
  uint16 num = 0U;
  uint16 i = 0U;
  boolean permission, dirty = DEM_FALSE;

  num = event->usRatioIdCount;

  
  for (i = 0; i < num; i++)
  {
    uint8 RatioIndex = 0;

    Dem_GetRatioIndex(event,i, &RatioIndex);
    
    if((Dem_GaaRatioIdInfo[RatioIndex].ucRatioIdType == DEM_RATIO_OBSERVER) /*&& (Dem_GusRatioFaultFound[RatioIndex] == DEM_FALSE)*/)
    {
      Dem_GetFimPermission(RatioIndex, &permission);

      if(permission == TRUE)
      {      
        /* Get the group id for a particular ratioid */
        const uint8  IumprGroupId = Dem_GaaRatioIdInfo[RatioIndex].ucIUMPRGroup;

        if((Dem_GusRatioMonitored[IumprGroupId] == DEM_FALSE) && ((EventStatus & DEM_UDS_STATUS_PDTC) != DEM_UDS_STATUS_PDTC))
        {
          /*In IUMPR, if either the numerator or denominator
            for a specific component reaches the maximum value
              of 65535, both numbers shall be divided by two
            before either is incremented again to avoid overflow
            problems */
          if(Dem_GaaIumprNumerator[IumprGroupId] ==
              DEM_MAX_DENOMINATOR_NUMERATOR_VALUE)
          {
            Dem_GaaIumprNumerator[IumprGroupId] =
                (Dem_GaaIumprNumerator[IumprGroupId] - 1U)  / 2U;

            Dem_GaaIumprDenominator[IumprGroupId] =
                (Dem_GaaIumprDenominator[IumprGroupId] - 1U) / 2U;
          }

          /* Increment the numerator for the requested group */
          Dem_GaaIumprNumerator[IumprGroupId]++;
          Dem_GusRatioMonitored[IumprGroupId] = DEM_TRUE;
          
          SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
          Dem_EventStatusNvRamData.IumprNumerator[IumprGroupId] = Dem_GaaIumprNumerator[IumprGroupId];  
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          
          dirty = DEM_TRUE;
        }

      }
    }
  }

  if(dirty == DEM_TRUE)
  {
    Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_DIRTY_NVM);
    Dem_EvMem_TriggerWriteAllBlocks(); 
  }
  
  return LddReturnValue;
}
#endif


/*******************************************************************************
 ** Function Name       : Dem_ProcessDen                                      **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : The function is used for incrementing of denominator**
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : LucOperationCycleId                                 **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s)  :                               **
 **                       Dem_GaaOperationCycleIdsList, Dem_GaaRatioIdInfo    **
 **                       Dem_Event, Dem_GusRatioIdDisable        **
 **                       Dem_GaaIumprDenominator, Dem_GaaIumprNumerator      **
 **                       Function(s) invoked :  None                         **
 *******************************************************************************/
#if((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && (DEM_OBD_SUPPORT == STD_ON))
FUNC(void, DEM_CODE) Dem_ProcessDen(uint8 LucOperationCycleId, Dem_EventIdType eventId)
    {

  uint16 LusTotalRatioCount;
  uint16 LusRatioCount;

  uint8 LucIumprGroupId;
  uint8 LucRatioIdIndex;
  boolean permission, dirty = DEM_FALSE;
  uint8 LaaIumprGrp[DEM_SIXTEEN];
  uint8 LucTempGroupCount;
  

  if(Dem_GblRatioInit == DEM_FALSE)
  {
    for(LucTempGroupCount = DEM_ZERO; LucTempGroupCount < DEM_SIXTEEN;
        LucTempGroupCount++)
    {
      /* Initialise the local variable to false */
      LaaIumprGrp[LucTempGroupCount] = DEM_FALSE;
      Dem_GusRatioMonitored[LucTempGroupCount] = DEM_FALSE;    
    }
    
    if(Dem_GusRatioDenCondState[DEM_IUMPR_GENERAL_DENOMINATOR] == DEM_TRUE)
    {
      if(Dem_GusGeneralDenominator < DEM_MAX_DENOMINATOR_NUMERATOR_VALUE)
      {
        Dem_GusGeneralDenominator++;
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        Dem_EventStatusNvRamData.GeneralDenCnt = Dem_GusGeneralDenominator;
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
        dirty = DEM_TRUE;
      }
      
    }
    Dem_GblRatioInit = DEM_TRUE;
 
  }

  
  /* Store the total ratioid configured for that event */
  LusTotalRatioCount = Dem_Event[eventId-1U].usRatioIdCount;

  LusRatioCount = DEM_ZERO;

  /* Loop for incrementing the denominator */
  while(LusRatioCount < LusTotalRatioCount)
  {
    Dem_UdsStatusByteType EventStatusMask = 0u;

    EventStatusMask = Dem_AllEventStatusByte[eventId];
    Dem_GetRatioIndex(&Dem_Event[eventId-1U],LusRatioCount,&LucRatioIdIndex);

    LucIumprGroupId = Dem_GaaRatioIdInfo[LucRatioIdIndex].ucIUMPRGroup;

    Dem_GetFimPermission(LucRatioIdIndex, &permission);

    if((permission == DEM_TRUE) && (LaaIumprGrp[LucIumprGroupId] == DEM_FALSE) &&
        (Dem_GusRatioIdDisable[LucRatioIdIndex] == DEM_FALSE) &&
        ((EventStatusMask & DEM_UDS_STATUS_PDTC) != DEM_UDS_STATUS_PDTC))
    {
      /* Set the variable */
      LaaIumprGrp[LucIumprGroupId] = DEM_TRUE;
      /*In IUMPR, if either the numerator or denominator for a specific
       *component reaches the maximum value of 65535, both numbers shall
       *be divided by two before either is incremented again to avoid
       *overflow problems
       */
      if(Dem_GaaIumprDenominator[LucIumprGroupId] ==
          DEM_MAX_DENOMINATOR_NUMERATOR_VALUE)
      {
        Dem_GaaIumprNumerator[LucIumprGroupId] =
            ((Dem_GaaIumprNumerator[LucIumprGroupId] - DEM_ONE) / DEM_TWO);

        Dem_GaaIumprDenominator[LucIumprGroupId] =
            ((Dem_GaaIumprDenominator[LucIumprGroupId] - DEM_ONE) / DEM_TWO);
      }
      /* Increment the denominator for the requested group */       
      Dem_GaaIumprDenominator[LucIumprGroupId]++;
      
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      Dem_EventStatusNvRamData.IumprDenominator[LucIumprGroupId] = Dem_GaaIumprDenominator[LucIumprGroupId];
      Dem_EventStatusNvRamData.IumprNumerator[LucIumprGroupId] = Dem_GaaIumprNumerator[LucIumprGroupId];
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      
      dirty = DEM_TRUE;
      
    }
    LusRatioCount++;
  }/* Loop for incrementing the denominator */



  if(dirty == DEM_TRUE)
  {
    Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_DIRTY_NVM);
    Dem_EvMem_TriggerWriteAllBlocks(); 
  }

}
#endif


/*******************************************************************************
 ** Function Name       : Dem_CalcPIDValue                                    **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : API to calculate the value of PID Byte              **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : LucOBDReadinessGrp                                  **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : PIDValue                                            **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s)  :                               **
 **                       Dem_Event                                           **
 **                                                                           **
 **                       Function(s) invoked : None                          **
 *******************************************************************************/
/* Check if DEM_OBD_SUPPORT == STD_ON */
#if (DEM_OBD_SUPPORT == STD_ON)
FUNC(void, DEM_CODE) Dem_CalcPIDValue(
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PIDValue, uint8 LusByteValue, uint8
    LucOBDReadinessGrp)
    {
  Dem_EventIdType LusEventCount;

  /* Initialize the count to zero */
  LusEventCount = DEM_ZERO;

  *PIDValue = (uint8)(*PIDValue & (uint8)(~LusByteValue));

  while(LusEventCount < Dem_Number_Of_Events)
  {
    if(Dem_Event[LusEventCount].ulEventOBDReadinessGroup ==
        LucOBDReadinessGrp)
    {
      Dem_EventIdType EventId = LusEventCount + 1u;
      Dem_UdsStatusByteType EventStatusMask = 0u;

      EventStatusMask = Dem_AllEventStatusByte[EventId];
      /* Check if test is failed/Passed this operation cycle */
      if((EventStatusMask & DEM_BIT6_MASK1) == DEM_BIT6_MASK1)
      {

        *PIDValue = *PIDValue | LusByteValue;

        LusEventCount = Dem_Number_Of_Events;
      }
      else
      {
        /*Do nothing. To avoid warnings*/
      }
    }/* End the loop */
    /* Increment the count by one */
    LusEventCount++;
  }
    }
#endif


/*******************************************************************************
 ** Function Name       : Dem_CalcPID41_34                                    **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : API to calculate the value of PID 41 for Dem        **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : PID41value                                          **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s)  :                               **
 **                       Dem_GulEventIdDisabled                              **
 **                                                                           **
 **                       Function(s) invoked :                               **
 **                       Dem_CalcPIDValue                                    **
 *******************************************************************************/
/* Check if DEM_OBD_SUPPORT == STD_ON */
#if (DEM_OBD_SUPPORT == STD_ON)
FUNC(void, DEM_CODE) Dem_CalcPID41_34(
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID41Value)
    {
  uint32 LulEventIdDisabledMask;
  uint8 LaaPid41data[DEM_TWO];
  uint8 LucByteCSpark;
  uint8 LucBitPos;
  uint8 LucReadynessGruoupIndex;
  /*For spark engines*/
#if((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_EIGHT) == DEM_ZERO)
  uint8 LaaReadynessGruoup[DEM_SEVEN] = { DEM_OBD_RDY_CAT, DEM_OBD_RDY_HTCAT,
      DEM_OBD_RDY_EVAP, DEM_OBD_RDY_SECAIR, DEM_OBD_RDY_O2SENS,
      DEM_OBD_RDY_O2SENSHT, DEM_OBD_RDY_ERG};

#else /*For Ignition engines*/
  uint8 LaaReadynessGruoup[DEM_SIX] = { DEM_OBD_RDY_HCCAT, DEM_OBD_RDY_NOXCAT,
      DEM_OBD_RDY_BOOSTPR, DEM_OBD_RDY_EGSENS,
      DEM_OBD_RDY_PMFLT, DEM_OBD_RDY_ERG};
  LucByteCSpark = Dem_PID01_ByteC_Compression;
#endif

#if((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_EIGHT) == DEM_ZERO)
  LucByteCSpark = DemM_PID01_ByteC_Spark;
#endif

  LaaPid41data[DEM_ZERO] = *PID41Value;

  /*
   *  MISRA Rule       : 17.4
   * Message          : Increment or decrement operation
   *                    performed on pointer.
   * Reason           : Increment operator is used to achieve
   *                    better throughput.
   * Verification     : However, part of the code is verified
   *                    manually and it is not having any impact.
   */

  LaaPid41data[DEM_ONE] = *(PID41Value + DEM_ONE);

  LucBitPos = DEM_ONE;

  LucReadynessGruoupIndex = DEM_ZERO;

  /* For spark engines*/
#if((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_EIGHT) == DEM_ZERO)

  LulEventIdDisabledMask = DEM_EIGHT;

  /*
   *  MISRA Rule       : 13.2
   * Message           : Testing a value should be made explicit.
   * Reason           : Increment operator is used to achieve
   *                    better throughput.
   * Verification     : However, part of the code is verified
   *                    manually and it is not having any impact.
   */
  while(LucByteCSpark != DEM_ZERO)
  {
    if (((LucByteCSpark & DEM_ONE) == DEM_ONE))
    {
      /* Check that event is disabled or readiness state Catalyst monitoring
           is supported.
       */
      if((Dem_GulEventIdDisabled & LulEventIdDisabledMask) ==
          LulEventIdDisabledMask)
      {
        /*
         *  MISRA Rule       : 21.1
         * Message           : An integer expression with a value that is
         *                     apparently negative is being converted to an
         *                     unsigned type.
         * Reason            : Negation operator is used to achieve
         *                     better throughput.
         * Verification      : However, part of the code is verified
         *                     manually and it is not having any impact.
         */

        /* Bit0 of Byte-3 is set to 0 to indicate monitor is disabled */
        LaaPid41data[DEM_ZERO] = (LaaPid41data[DEM_ZERO] &
            ((uint8)(~LucBitPos)));

        /* Bit0 of Byte-4 is set to 1 to indicate monitor is not completed  */
        LaaPid41data[DEM_ONE] = LaaPid41data[DEM_ONE] | LucBitPos;
      }
      else
      {
        /* Bit0 of Byte-3 is set to 1 if Catalyst monitoring
         is enabled*/
        LaaPid41data[DEM_ZERO] = LaaPid41data[DEM_ZERO] | LucBitPos;

        Dem_CalcPIDValue(&LaaPid41data[DEM_ONE], LucBitPos,
            LaaReadynessGruoup[LucReadynessGruoupIndex]);
      }

    }
    else /* Catalyst monitoring is not supported*/
    {
      /*
       *  MISRA Rule       : 21.1
       * Message           : An integer expression with a value that is
       *                     apparently negative is being converted to an
       *                     unsigned type.
       * Reason            : Negation operator is used to achieve
       *                     better throughput.
       * Verification      : However, part of the code is verified
       *                     manually and it is not having any impact.
       */
      /* Bit-0 of Byte-3 is set to 0   */
      LaaPid41data[DEM_ZERO] = (LaaPid41data[DEM_ZERO] &
          ((uint8)(~LucBitPos)));

      /*
       *  MISRA Rule       : 21.1
       * Message           : An integer expression with a value that is
       *                     apparently negative is being converted to an
       *                   : unsigned type.
       * Reason            : Negation operator is used to achieve
       *                     better throughput.
       * Verification      : However, part of the code is verified
       *                     manually and it is not having any impact.
       */
      /* Bit0 of Byte-4 is set to 1 to indicate monitor is not completed  */
      LaaPid41data[DEM_ONE] = (LaaPid41data[DEM_ONE] & ((uint8)(~LucBitPos)));
    }

    LucByteCSpark = LucByteCSpark >> DEM_ONE;

    LucBitPos = LucBitPos << DEM_ONE;

    if (LucBitPos != DEM_BIT4_MASK1)
    {
      LulEventIdDisabledMask = LulEventIdDisabledMask << DEM_ONE;

      LucReadynessGruoupIndex++;
    }
    else
    {
      /* Do nothing. To avoid warnings */
    }
  }
#else /* For compression engines*/
  {
    /* EventId Disabled Mask is 0x400 */
    LulEventIdDisabledMask = DEM_BIT10_MASK1;

    while(LucByteCSpark != DEM_ZERO)
    {
      if (((LucByteCSpark & DEM_ONE) == DEM_ONE))
      {
        /* Check that event is disabled or readiness state Catalyst monitoring
         is supported.
         */
        if((Dem_GulEventIdDisabled & LulEventIdDisabledMask) ==
            LulEventIdDisabledMask)
        {
          /*
           *  MISRA Rule       : 21.1
           * Message           : An integer expression with a value that is
           *                     apparently negative is being converted to an
           *                   : unsigned type.
           * Reason            : Negation operator is used to achieve
           *                     better throughput.
           * Verification      : However, part of the code is verified
           *                     manually and it is not having any impact.
           */

          /* Bit0 of Byte-3 is set to 0 to indicate monitor is disabled */
          LaaPid41data[DEM_ZERO] = (LaaPid41data[DEM_ZERO] &
              ((uint8)(~LucBitPos)));

          /* Bit0 of Byte-4 is set to 1 to indicate monitor is not completed  */
          LaaPid41data[DEM_ONE] = LaaPid41data[DEM_ONE] | LucBitPos;
        }
        else
        {
          /* Bit0 of Byte-3 is set to 1 if Catalyst monitoring
           is enabled*/
          LaaPid41data[DEM_ZERO] = LaaPid41data[DEM_ZERO] | LucBitPos;

          Dem_CalcPIDValue(&LaaPid41data[DEM_ONE], LucBitPos,
              LaaReadynessGruoup[LucReadynessGruoupIndex]);
        }

      }
      else /* Catalyst monitoring is not supported*/
      {
        /* Bit-0 of Byte-3 is set to 0   */
        LaaPid41data[DEM_ZERO] = LaaPid41data[DEM_ZERO] & (~LucBitPos);

        /* Bit0 of Byte-4 is set to 1 to indicate monitor is not completed  */
        LaaPid41data[DEM_ONE] = LaaPid41data[DEM_ONE] & (~LucBitPos);
      }

      LucByteCSpark = LucByteCSpark >> DEM_ONE;
      LucBitPos = LucBitPos << DEM_ONE;

      if ((LucBitPos != DEM_BIT2_MASK1) && (LucBitPos != DEM_BIT4_MASK1))
      {
        if(LucBitPos != DEM_BIT7_MASK1)
        {
          LulEventIdDisabledMask = LulEventIdDisabledMask << DEM_ONE;
        }
        else
        {
          /* EventId Disabled Mask is 0x200 */
          LulEventIdDisabledMask = Dem_GulEventIdDisabled | DEM_BIT9_MASK1;
        }

        LucReadynessGruoupIndex++;
      }
      else
      {
        /* Do nothing. To avoid warnings*/
      }
    }
  }
#endif
  PID41Value[DEM_ZERO] = LaaPid41data[DEM_ZERO];

  PID41Value[DEM_ONE]  = LaaPid41data[DEM_ONE];
}
#endif


/*******************************************************************************
 ** Function Name       : Dem_SetMalfuntionOnOff  = *1                        **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Function is used to process the indicator bit for   **
 **                       obd                                                 **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : LucIndicatorIndex, LusCount, EventStatusMask        **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if (DEM_OBD_SUPPORT == STD_ON)
#ifdef DEM_MIL_INDICATORID
FUNC(void, DEM_CODE)
Dem_SetMalfuntionOnOff(void)
{
  boolean indicatorAttributeStatus;
  Dem_NumOfIndicatorAttributeType idx;
  P2CONST(Dem_IndicatorAttributeType , AUTOMATIC, DEM_VAR)  indicator;

  for (idx = 0U; idx < Dem_Number_Of_Indicators; idx++)
  {
    indicator = Dem_GetCfgIndicatorAtt(idx);
    if(DEM_MIL_INDICATORID == indicator->IndicatorIdRef)
    {
      indicatorAttributeStatus = Dem_EvMem_GetIndicatorAttStatus(indicator->EventIdRef, indicator->IndicatorAttStatusPos);
      Dem_GucMilonFlag = indicatorAttributeStatus << 7U;
      if(Dem_GucMilonFlag == DEM_BIT7_MASK1)
      {
        break;
      }
    }

  }

#if 0
  uint8 i = 0u;
  P2VAR(Dem_IndicatorAttributeType , AUTOMATIC, DEM_VAR)
  indicator = NULL_PTR;

  @IF_REQ : input parameter shall be added, indicator, EventStatus(or getStatus)

        /* Check event is referring to misfire, fuel system or  evaporative */
#if((((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_BIT0_MASK1_BITWISE)==DEM_BIT0_MASK1_BITWISE)||\
    ((DEM_PID01_BYTEB_LOWER_NIBBLE&DEM_BIT1_MASK1_BITWISE)==DEM_BIT1_MASK1_BITWISE))||\
    ((DEM_PID01_BYTEC_SPARK & DEM_BIT4_MASK1_BITWISE)==DEM_BIT4_MASK1_BITWISE))

      if(((event->ulEventOBDReadinessGroup == DEM_OBD_RDY_MISF) ||
          (event->ulEventOBDReadinessGroup == DEM_OBD_RDY_EVAP)) ||
          (event->ulEventOBDReadinessGroup == DEM_OBD_RDY_FLSYS))
      {
        /* Check if the event has passed or failed in this
        operation cycle */
        if((EventStatusMask & DEM_BIT1_MASK1) == 0u)
        {
          uint8 MilCounter = ++(*indicator->ObdMilCycleCounter);

          if(MilCounter == DEM_THREE)
          {
            /* Mil status bit7 of pid01 is set to zero */
            Dem_GucMilonFlag = DEM_ZERO;
          }
        }
        else
        {
          *indicator->ObdMilCycleCounter = 0u;
        }
      }
      else
      {
        /* Check if the event has passed or failed in this
        operation cycle */
        if((EventStatusMask & DEM_BIT1_MASK1) ==
            DEM_ZERO)
        {
          uint8 MilCounter = ++(*indicator->ObdMilCycleCounter);

          if(MilCounter == DEM_THREE)
          {
            /* Mil status bit7 of pid01 is set to zero */
            Dem_GucMilonFlag = DEM_ZERO;
          }/*Healing threshold of obd is reached */
        }
        else
        {
          *indicator->ObdMilCycleCounter = 0u;
        }
      }
#else
  /* Check if the event has passed or failed in this
      operation cycle */
  if((EventStatusMask & DEM_BIT1_MASK1) ==
      DEM_ZERO)
  {
    uint8 MilCounter = ++(*indicator->ObdMilCycleCounter);

    if(MilCounter == DEM_THREE)
    {
      /* Mil status bit7 of pid01 is set to zero */
      Dem_GucMilonFlag = DEM_ZERO;
    }/*Healing threshold of obd is reached */
  }
#endif
#endif
}
#endif
#endif

/*******************************************************************************
 ** Function Name       : Dem_GetRatioIndex                                   **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Function is used to get ratio index                 **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : event, ArrayIndex, EventStatusMask                  **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : RatioId                                             **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && (DEM_OBD_SUPPORT == STD_ON))
FUNC(void, DEM_CODE)
Dem_GetRatioIndex(
  Dem_EventParameterCPCType event,
  uint32 ArrayIndex,
  P2VAR(uint8, AUTOMATIC,DEM_VAR) RatioId)
{
  *RatioId = event->aaRatioIndex[ArrayIndex];
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_SetPfcCycleSetPfcCycleQualified                 **
 **                                                                           **
 ** Service ID          : 0xaa                                                **
 **                                                                           **
 ** Description         : Function is used to set pfc qualifed flag           **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if((DEM_OBD_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U))
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetPfcCycleSetPfcCycleQualified(void)
{
  Dem_NumOfEventMemoryEntryType memLoc = DEM_NO_EVMEM_ENTRY;
  Dem_NumOfEventMemoryEntryType numOfMemEntries = Dem_SizeOfEventMemory[DEM_DTC_ORIGIN_PERMANENT_MEMORY];
  
  for(memLoc = 0U; memLoc < numOfMemEntries; memLoc++)
  {
    SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
    Dem_PerDtcState[memLoc].PfcQualified = DEM_TRUE;
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
  }

  return E_OK;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_GetPfcCycleQualified                            **
 **                                                                           **
 ** Service ID          : 0xab                                                **
 **                                                                           **
 ** Description         : Function is used to get pfc qualifed flag           **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if((DEM_OBD_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U))
FUNC(Std_ReturnType, Dem_CODE) 
Dem_GetPfcCycleQualified(P2VAR(boolean, AUTOMATIC, DEM_VAR) pfcCycleisqualified)
{
  
  *pfcCycleisqualified = Dem_PerDtcState[0].PfcQualified;
  
  return E_OK;
}
#endif



/*******************************************************************************
 ** Function Name       : Dem_GetMalfuntionOnOff                              **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Function is used to get the indicator bit for obd   **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : Dem_GucMilonFlag                                    **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if(DEM_OBD_SUPPORT == STD_ON)
FUNC(boolean, Dem_CODE)
Dem_GetMalfuntionOnOff(void)
{

  return Dem_GucMilonFlag;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_SetObdCycle                                     **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Function is used to set OBD Cyle                     **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if(DEM_OBD_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetObdCycle(uint8 LucOperationCycleId)
{
  boolean dirty = DEM_FALSE;

  SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
  if( (DEM_OPCYC_WARMUP == Dem_GstOperationCycleName[LucOperationCycleId].ucOperationCycle) && (DEM_TRUE == Dem_EventStatusNvRamData.DtcClear))
  {
    if(Dem_EventStatusNvRamData.NumOfWUCSinceLC < DEM_MAX_WARM_UP_COUNT)
    {
      Dem_EventStatusNvRamData.NumOfWUCSinceLC++;
    }
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
  }
  #if(DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
  else if(DEM_OPCYC_IGNITION == Dem_GstOperationCycleName[LucOperationCycleId].ucOperationCycle)
  {
    if(Dem_GusIgnitionCylCnt < DEM_MAX_DENOMINATOR_NUMERATOR_VALUE)
    {
      Dem_GusIgnitionCylCnt++;
      
      Dem_EventStatusNvRamData.IgnitionCylCnt = Dem_GusIgnitionCylCnt;
      dirty = DEM_TRUE;
    }
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
  }
  #endif
  else
  {
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
  }

  

  if(dirty == DEM_TRUE)
  {
    Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_DIRTY_NVM);
    Dem_EvMem_TriggerWriteAllBlocks(); 
  }
  
  return E_OK;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_ClearObdInfomation                              **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Function is used to clear OBD information           **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if(DEM_OBD_SUPPORT == STD_ON)
FUNC(void, DEM_CODE)
Dem_ClearObdInfomation(void)
{
  Dem_GblClearTimeStartObd = DEM_TRUE;
  Dem_GblDtcCleared = DEM_TRUE;
  Dem_GulTimeSinceMilOn = 0;
  Dem_GulDemClearTimeCount = 0;

  SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
  Dem_EventStatusNvRamData.DtcClear = Dem_GblDtcCleared; 
  Dem_EventStatusNvRamData.NumOfWUCSinceLC = 0;
  SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
  
}
#endif


/*******************************************************************************
 ** Function Name       : Dem_OPStartInit                                     **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Function is used to set OBD Cyle                    **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && (DEM_OBD_SUPPORT == STD_ON))
FUNC(Std_ReturnType, DEM_CODE)
Dem_OCStartInit(void)
{
  #if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
  Dem_GblRatioInit = DEM_FALSE;
  #endif

  return E_OK;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_SetDataOfPID21                                  **
 **                                                                           **
 ** Service ID          : 0xa6                                                **
 **                                                                           **
 ** Description         : Function is used to set the value of PID $21 in the **
 **                       Dem by a software component.                        **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : PID21value                                          **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if(DEM_OBD_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetDataOfPID21( uint8* PID21value )
{

  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Module Initialization check */
  if(DEM_INIT != Dem_GucInit)
  {
    /* Report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_GETINFOTYPEVALUE08_SID, DEM_E_UNINIT);
  }
  else
  #endif
  {

  }

  return E_OK;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_SetDataOfPID31                                  **
 **                                                                           **
 ** Service ID          : 0xa7                                                **
 **                                                                           **
 ** Description         : Function is used to set the value of PID $31 in the **
 **                       Dem by a software component.                        **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : PID31value                                          **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if(DEM_OBD_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetDataOfPID31( uint8* PID31value )
{

  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Module Initialization check */
  if(DEM_INIT != Dem_GucInit)
  {
    /* Report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_GETINFOTYPEVALUE08_SID, DEM_E_UNINIT);
  }
  else
  #endif
  {

  }
  
  return E_OK;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_SetDataOfPID4D                                  **
 **                                                                           **
 ** Service ID          : 0xa8                                                **
 **                                                                           **
 ** Description         : Function is used to set the value of PID $4D in the **
 **                       Dem by a software component.                        **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : PID4Dvalue                                          **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if(DEM_OBD_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetDataOfPID4D( uint8* PID4Dvalue )
{

  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Module Initialization check */
  if(DEM_INIT != Dem_GucInit)
  {
    /* Report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_GETINFOTYPEVALUE08_SID, DEM_E_UNINIT);
  }
  else
  #endif
  {


  }
  
  return E_OK;
}
#endif


/*******************************************************************************
 ** Function Name       : Dem_SetDataOfPID4E                                  **
 **                                                                           **
 ** Service ID          : 0xa9                                                **
 **                                                                           **
 ** Description         : Function is used to set the value of PID $4E in the **
 **                       Dem by a software component.                        **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : PID4Evalue                                          **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if(DEM_OBD_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetDataOfPID4E( uint8* PID4Evalue )
{
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Module Initialization check */
  if(DEM_INIT != Dem_GucInit)
  {
    /* Report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_GETINFOTYPEVALUE08_SID, DEM_E_UNINIT);
  }
  else
  #endif
  {

  }
  
  return E_OK;
}
#endif
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
