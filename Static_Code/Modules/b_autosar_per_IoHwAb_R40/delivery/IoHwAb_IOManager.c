/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: IoHwAb_IOManager.c                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_IOMDelayTicks                                          **
**              IoHwAb_IOMInit                                                **
**              IoHwAb_IOMDeInit                                              **
**              IoHwAb_IOMDigInInit                                           **
**              IoHwAB_IOMDigInSample                                         **
**              IoHwAb_IOMAnaInAcqEnd                                         **
**              IoHwAb_IOML2H                                                 **
**              IoHwAb_IOMH2L                                                 **
**              IoHwAb_IOMInputsLP                                            **
**              IoHwAb_IOMOutputsLP                                           **
**              IoHwAb_IOMOnTimer                                             **
**              IoHwAb_IOM_5ms                                                **
**              IoHwAb_IOM_10ms                                               **
**              IOHWAB_IOM_TASK_FG2_FUNC                                      **
**              IOHWAB_IOM_TASK_FG1_FUNC                                      **
**                                                                            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.15.0.2  09-Sep-2021   Yangjin    #31974                                  **
** 1.10.0    26-Jun-2020   Yangjin    #24033, #24095, #24234                  **
** 1.9.0     04-Jun-2020   Yangjin    #23413                                  **
** 1.1.12    05-Apr-2018   Jongyoung  #12280                                  **
** 1.1.11    17-Jan-2018   Jongyoung  #11222                                  **
** 1.1.10    29-Mar-2017   Jongyoung  #7890                                   **
** 1.1.9     05-Mar-2017   Jongyoung  #7764                                   **
** 1.1.8     17-Jan-2017   Jongyoung  #6529                                   **
** 1.1.7     11-Dec-2016   Jongyoung  #6845, #6929                            **
** 1.1.6     02_Sep-2016   Jongyoung  #6240                                   **
** 1.1.5     02_Sep-2016   Jongyoung  #5930                                   **
** 1.1.4     26_Jul-2016   Jongyoung  #5686                                   **
** 1.1.3     01_Feb-2016   Jongyoung  #4038                                   **
** 1.1.2     19-Jan-2015   Jongyoung  #3665                                   **
*******************************************************************************/
/* polyspace-begin MISRA-C3:8.7 MISRA-C3:2.2 MISRA-C3:16.1 MISRA-C3:16.4 MISRA-C3:D4.5 [Justified:Unset] "Not a defect" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_IOManager.h"
#include "IoHwAb_Config.h"
#include "SchM_IoHwAb.h"
#include "Rte_IoHwAb.h"
#include "IoHwAb_Util.h"

#if (IOHWAB_USE_IO_MAN == STD_ON)
#include "Os.h"
#endif /* (IOHWAB_USE_IO_MAN == STD_ON) */
#if ((IOHWAB_USE_ANA_IN == STD_ON) || (IOHWAB_USE_ANA_IN_DIR == STD_ON))
#include "IoHwAb_AnaIn.h"
#endif /* ((IOHWAB_USE_ANA_IN == STD_ON) || (IOHWAB_USE_ANA_IN_DIR == STD_ON)) */
#if (IOHWAB_USE_DIG_IN == STD_ON)
#include "IoHwAb_DigIn.h"
#if (IOHWAB_USE_MC33972 == STD_ON)
#include "IoHwAb_DigInMC33972.h"
#endif /* (IOHWAB_USE_MC33972 == STD_ON) */
#endif /* (IOHWAB_USE_DIG_IN == STD_ON) */
#if (IOHWAB_USE_DIG_OUT == STD_ON)
#include "IoHwAb_DigOut.h"
#if (IOHWAB_USE_L9826 == STD_ON)
#include "IoHwAb_DigOutL9826.h"
#endif /* (IOHWAB_USE_L9826 == STD_ON) */
#if (IOHWAB_USE_L99MC6 == STD_ON)
#include "IoHwAb_DigOutL99MC6.h"
#endif /* (IOHWAB_USE_L99MC6 == STD_ON) */
#if (IOHWAB_USE_TLE7240SL == STD_ON)
#include "IoHwAb_DigOutTLE7240SL.h"
#endif /* (IOHWAB_USE_TLE7240SL == STD_ON) */
#endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */
#if (IOHWAB_USE_IN_SUP_SWT == STD_ON)
#include "IoHwAb_InputSupply.h"
#endif /* (IOHWAB_USE_IN_SUP_SWT == STD_ON) */
#if (IOHWAB_USE_VOL_MON == STD_ON)
#include "IoHwAb_VolMon.h"
#endif /* (IOHWAB_USE_VOL_MON == STD_ON) */
#if (IOHWAB_USE_LP_FLAG == STD_ON)
#include "BswM.h"
#endif /* (IOHWAB_USE_LP_FLAG == STD_ON) */
#if (IOHWAB_USE_PM_MODULE == STD_ON)
#include "Pm_Types.h"
#endif /* (IOHWAB_USE_PM_MODULE == STD_ON) */
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define IOHWAB_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
VAR(IoHwAb_AcqState, IOHWAB_VAR)IoHwAb_GucInAcqState;
#define IOHWAB_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if (IOHWAB_USE_IO_MAN == STD_ON)

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
static FUNC(StatusType, IOHWAB_CODE)IoHwAb_IOMActivateTask(TaskType TaskId);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, IOHWAB_CODE)IoHwAb_IOMDigInInit(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, IOHWAB_CODE)IoHwAB_IOMDigInSample(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (IOHWAB_USE_IO_MAN == STD_ON) */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"

#if (IOHWAB_USE_IO_MAN == STD_ON)

#if (IOHWAB_USE_DIG_SUP_SWT == STD_ON)
#if (IOHWAB_USE_DIG_SUP_SWT_LP == STD_ON)
/* MCU dependent Code */
/*polyspace:begin<MISRA-C:8.1:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace:begin<MISRA-C:10.1:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace:begin<MISRA-C:11.3:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace:begin<RTE: ABS_ADDR : Not a defect : No Action Planned >  */
/* polyspace-begin RTE:UNR [Not a defect:Unset] "Reachable code" */

/*******************************************************************************
** Function Name        : IoHwAb_IOMDelayTicks                                **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void, IOHWAB_CODE)IoHwAb_IOMDelayTicks(uint32 ticks)
{
  volatile uint32 requestedTime;
  
#if (defined(IOHWAB_MCAL_INFINEON_TC21X) || defined(IOHWAB_MCAL_INFINEON_TC22X) \
  || defined(IOHWAB_MCAL_INFINEON_TC23X) || defined(IOHWAB_MCAL_INFINEON_TC26X) \
  || defined(IOHWAB_MCAL_INFINEON_TC27X) || defined(IOHWAB_MCAL_INFINEON_TC29X) )


  uint32 previousTime;
  uint32 currentTime;
  uint32 elapsedTime;

  requestedTime = ticks;
  previousTime = IOHWAB_CURRENT_CLOCK_TICK();
  do
  {
/*polyspace:begin<MISRA-C:2.1:Not a defect:Justify with annotations> No Impact of this rule violation*/
    IOHWAB_NOP();
    IOHWAB_NOP();
    IOHWAB_NOP();
    IOHWAB_NOP();
    IOHWAB_NOP();
/*polyspace:end<MISRA-C:2.1:Not a defect:Justify with annotations> No Impact of this rule violation*/


    currentTime = IOHWAB_CURRENT_CLOCK_TICK();

    if (currentTime > previousTime)
    {
      elapsedTime = currentTime - previousTime;
    }
    else
    {
      elapsedTime = 0xFFFFFFFFu - previousTime;
      elapsedTime += currentTime + IOHWAB_ONE;
    }

    previousTime = currentTime;

    if (requestedTime > elapsedTime)
    {
      requestedTime -= elapsedTime;
    }
    else
    {
      requestedTime = IOHWAB_ZERO;
    }
  } while (requestedTime != IOHWAB_ZERO);

#else /* All Mcus but Aurix platform */
  requestedTime = ((uint32)IoHwAb_GddISupplyMcuClkLp*ticks)/IOHWAB_MCU_CLK_DIV;
  if (requestedTime > 0u)
  {
	  for (;requestedTime!=0u; requestedTime--){/* Do Nothing */};
  }  
#endif /* #if Aurix */
}

#endif /* (IOHWAB_USE_DIG_SUP_SWT_LP == STD_ON) */
#endif /* (IOHWAB_USE_DIG_SUP_SWT == STD_ON)      */
/*polyspace:end<MISRA-C:11.3:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*******************************************************************************
** Function Name        : IoHwAb_IOMInit                                      **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service initilize IO Manager module.           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     : none                       **
**                        Function(s) invoked    :                            **
**                          IoHwAb_AnaInInit,                                 **
**                          IoHwAb_AnaInConvertStart,                         **
**                          IoHwAb_IOMDigInInit,                              **
**                          IoHwAb_DigInInit1,                                **
**                          IoHwAB_IOMDigInSample,                            **
**                          IoHwAb_DigInInit2,                                **
**                          IoHwAb_DigOutInit,                                **
**                          IoHwAb_DigOutWriteOutputsToHW,                    **
**                          IoHwAb_DigOutL9826,                               **
**                          IoHwAb_DigOutL99MC6,                              **
**                          IoHwAb_VolMonInit,                                **
**                          Gpt_EnableNotification                            **
*******************************************************************************/
FUNC(void, IOHWAB_CODE)IoHwAb_IOMInit(void)
{
  #if (defined(IOHWAB_MCAL_RENESAS_RH850F1L) || defined(IOHWAB_MCAL_RENESAS_RH850F1L_413) \
    || defined(IOHWAB_MCAL_RENESAS_RH850F1K) || defined(IOHWAB_MCAL_RENESAS_RH850F1KM))
  IoHwAb_IOManager_AssignTaskID();  
  #endif /* RH850 */
  
  #if (IOHWAB_USE_IN_SUP_SWT == STD_ON)
  IoHwAb_InputSupplyInit();
  #endif /* (IOHWAB_USE_IN_SUP_SWT == STD_ON) */

  #if (IOHWAB_USE_ANA_IN == STD_ON)
  IoHwAb_AnaInInit();

  /* initialise analog inputs */
  /* only the converter is initialised, it would be to long to update the     */
  /* values of all ananlog inputs                                             */
  IoHwAb_AnaInConvertStart();
  #endif /* (IOHWAB_USE_ANA_IN == STD_ON) */

  #if (IOHWAB_USE_DIG_IN == STD_ON)
  /* call of digital input init functions (must be after biostartup_Startup) */
  IoHwAb_IOMDigInInit();

  /* first sample of digital inputs acquisition and filtering */
  IoHwAb_DigInInit1();

  /* the second sample of digital inputs acquisition and filtering  */
  IoHwAB_IOMDigInSample();

  /* the third sample of digital inputs acquisition and filtering  */
  IoHwAB_IOMDigInSample();

  /* Initialize debounce function for all digital inputs*/
  /* (fast, slow, mux) */
  IoHwAb_DigInInit2();
  #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

  #if (IOHWAB_USE_DIG_OUT == STD_ON)
  /* initialisation of all digital outputs with default values */
  IoHwAb_DigOutInit();
  #endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */

  #if (IOHWAB_USE_VOL_MON == STD_ON)
  /* battery monitoring initialisation */
  IoHwAb_VolMonInit();
  #endif /* (IOHWAB_USE_VOL_MON == STD_ON) */

  #if (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON)
  Gpt_EnableNotification(IoHwAb_GddIOMGptTimerID);
  #endif /* (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON) */
}


/*******************************************************************************
** Function Name        : IoHwAb_IOMDeInit                                    **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service deinitilize IO Manager module.         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     : none                       **
**                        Function(s) invoked    :                            **
**                          Gpt_DisableNotification                           **
*******************************************************************************/
FUNC(void, IOHWAB_CODE)IoHwAb_IOMDeInit(void)
{
  #if (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON)
  Gpt_DisableNotification(IoHwAb_GddIOMGptTimerID);
  #endif /* (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON) */

  #if (IOHWAB_USE_DIG_OUT == STD_ON)
  /* deinitialisation of all digital outputs with default values */
  IoHwAb_DigOutDeInit();
  #endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */
}


/*******************************************************************************
** Function Name        : IoHwAb_IOMDigInInit                                 **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_DigInFilteringStart                        **
**                        Function(s) invoked    :                            **
**                          IoHwAb_InputSupplyDigitalControl,                 **
**                          IoHwAb_DigInMC33972Init                           **
*******************************************************************************/
static FUNC(void, IOHWAB_CODE)IoHwAb_IOMDigInInit(void)
{
  #if (IOHWAB_USE_DIG_IN == STD_ON)
  #if (IOHWAB_USE_DIG_SUP_SWT == STD_ON)
  IoHwAb_InputSupplyDigitalControl(TRUE, TRUE);
  #endif /* (IOHWAB_USE_DIG_SUP_SWT == STD_ON) */


  #if (IOHWAB_USE_MC33972 == STD_ON)
  /* initialise multiplexed digital inputs */
  (void)IoHwAb_DigInMC33972Init();
  #endif /* (IOHWAB_USE_MC33972 == STD_ON) */

  IoHwAb_DigInFilteringStart = TRUE;
  #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */
}


/*******************************************************************************
** Function Name        : IoHwAB_IOMDigInSample                               **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
**                          IoHwAb_DigInReadHwInputs,                         **
**                          IoHwAb_DigInMC33972Acq,                           **
**                          IoHwAb_DigInDebounce                              **
*******************************************************************************/
static FUNC(void, IOHWAB_CODE)IoHwAB_IOMDigInSample(void)
{
  #if (IOHWAB_USE_DIG_IN == STD_ON)
  IoHwAb_DigInReadHwInputs(FALSE);      /* acquisition of non multiplexed digital inputs   */

  #if (IOHWAB_USE_MC33972 == STD_ON)
  /* acquire values of multiplexed inputs in mc33972 */
  (void)IoHwAb_DigInMC33972Acq();
  #endif /* (IOHWAB_USE_MC33972 == STD_ON) */

  /* filtering of all digital inputs  */
  IoHwAb_DigInDebounce(0, IoHwAb_GddNumDigInFast + IoHwAb_GddNumDigInSlow);
  #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */
}


/*******************************************************************************
** Function Name        : IoHwAb_IOMAnaInAcqEnd                               **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GucInAcqState                              **
**                        Function(s) invoked    :                            **
**                          IoHwAb_InputSupplyAnalogControl,                  **
**                          IOMActivateTask,                                  **
**                          CoSvAb_FastTimerStart,                            **
**                          Gpt_StartTimer                                    **
*******************************************************************************/
FUNC(void, IOHWAB_CODE)IoHwAb_IOMAnaInAcqEnd (void)
{
  StatusType LddError = E_NOT_OK;

  /* callback called when all analog acquisition is finished */


  #if ((IOHWAB_USE_ANA_IN == STD_ON) && (IOHWAB_USE_IN_SUP_SWT == STD_ON) &&   \
       (IOHWAB_USE_ANA_SUP_SWT == STD_ON))
  /* switch off switched battery for analog inputs */
  IoHwAb_InputSupplyAnalogControl(FALSE);
  #endif /* ((IOHWAB_USE_ANA_IN == STD_ON) && (IOHWAB_USE_IN_SUP_SWT == STD_ON) &&
             (IOHWAB_USE_ANA_SUP_SWT == STD_ON)) */

  /* start task for analog filtering */

  LddError = IoHwAb_IOMActivateTask(IoHwAb_GddIOMTaskFG1);

  if (LddError == E_OK)
  {
	IoHwAb_GstIOManagerCounter.ucAcqEndToFG1++;
  }
}


/*******************************************************************************
** Function Name        : IoHwAb_IOML2H                                       **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     : none                       **
**                        Function(s) invoked    :                            **
**                          IoHwAb_DigOutL99MC6SwitchOn,                      **
**                          IoHwAb_DigInMC33972L2H                            **
*******************************************************************************/
FUNC(void, IOHWAB_CODE)IoHwAb_IOML2H(void)
{
  #if (IOHWAB_USE_DIG_OUT == STD_ON)
  #if (IOHWAB_USE_L9826 == STD_ON)
  (void)IoHwAb_DigOutL9826SwitchOn();
  #endif /* (IOHWAB_USE_L9826 == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */

  #if (IOHWAB_USE_DIG_OUT == STD_ON)
  #if (IOHWAB_USE_L99MC6 == STD_ON)
  (void)IoHwAb_DigOutL99MC6SwitchOn();
  #endif /* (IOHWAB_USE_L99MC6 == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */

  #if (IOHWAB_USE_DIG_OUT == STD_ON)
  #if (IOHWAB_USE_TLE7240SL == STD_ON)
  /* switch on the TLE7240SL devices after they were deselected */
  (void)IoHwAb_DigOutTLE7240SLSwitchOn();
  #endif /* (IOHWAB_USE_TLE7240SL == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */

  #if (IOHWAB_USE_DIG_IN == STD_ON)
  /* call the low to high function of each module present in th eproject */
  #if (IOHWAB_USE_MC33972 == STD_ON)
  (void)IoHwAb_DigInMC33972L2H();
  #endif /* (IOHWAB_USE_MC33972 == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */
}


/*******************************************************************************
** Function Name        : IoHwAb_IOMH2L                                       **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     : none                       **
**                        Function(s) invoked    :                            **
**                          IoHwAb_DigOutL99MC6SwitchOff,                     **
**                          IoHwAb_DigInMC33972H2L,                           **
**                          IoHwAb_DigInH2L                                   **
*******************************************************************************/
FUNC(void, IOHWAB_CODE)IoHwAb_IOMH2L(void)
{
  #if (IOHWAB_USE_DIG_OUT == STD_ON)
  #if (IOHWAB_USE_L9826 == STD_ON)
  IoHwAb_DigOutL9826SwitchOff();
  #endif /* (IOHWAB_USE_L9826 == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */

  #if (IOHWAB_USE_DIG_OUT == STD_ON)
  #if (IOHWAB_USE_L99MC6 == STD_ON)
  /* switch on the L99MC6 devices after they were deselected */
  (void)IoHwAb_DigOutL99MC6SwitchOff();
  #endif /* (IOHWAB_USE_L99MC6 == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */

  #if (IOHWAB_USE_DIG_OUT == STD_ON)
  #if (IOHWAB_USE_TLE7240SL == STD_ON)
  /* switch on the TLE7240SL devices after they were deselected */
  (void)IoHwAb_DigOutTLE7240SLSwitchOff();
  #endif /* (IOHWAB_USE_TLE7240SL == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */
  

  #if (IOHWAB_USE_DIG_IN == STD_ON)
  /* call the high to low function of each module present in th eproject */
  #if (IOHWAB_USE_MC33972 == STD_ON)
  (void)IoHwAb_DigInMC33972H2L();
  #endif /* (IOHWAB_USE_MC33972 == STD_ON) */

  IoHwAb_DigInH2L();
  #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */
}


/*******************************************************************************
** Function Name        : IoHwAb_IOMInputsLP                                  **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     : none                       **
**                        Function(s) invoked    :                            **
**                          IoHwAb_InputSupplyDigitalControl,                 **
**                          IoHwAb_DigInReadHwInputs,                         **
**                          IoHwAb_DigInSampleLP                              **
*******************************************************************************/
FUNC(void, IOHWAB_CODE)IoHwAb_IOMInputsLP(void)
{
  #if (IOHWAB_USE_DIG_IN == STD_ON)
  #if (IOHWAB_USE_DIG_SUP_SWT == STD_ON)
  #if (IOHWAB_USE_DIG_SUP_SWT_LP == STD_ON)
  /* switch on switched battery for digital inputs */
  IoHwAb_InputSupplyDigitalControl(FALSE, TRUE);
  /* wait DIGITAL_SUPPLY_SWITCH_DELAY ms */
  IoHwAb_IOMDelayTicks((uint32)IoHwAb_GddISupplyDigSwitchDelay);
  #endif /* (IOHWAB_USE_DIG_SUP_SWT_LP == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_SUP_SWT == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

  #if (IOHWAB_USE_DIG_IN == STD_ON)
  /* update value of fast and slow buffered digital inputs */
  IoHwAb_DigInReadHwInputs(FALSE);
  #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

  #if (IOHWAB_USE_DIG_IN == STD_ON)
  #if (IOHWAB_USE_DIG_SUP_SWT == STD_ON)
  #if (IOHWAB_USE_DIG_SUP_SWT_LP == STD_ON)
  /* switch off switched battery for digital inputs */
  IoHwAb_InputSupplyDigitalControl(FALSE, FALSE);
  #endif /* (IOHWAB_USE_DIG_SUP_SWT_LP == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_SUP_SWT == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

  #if (IOHWAB_USE_DIG_IN == STD_ON)
  /* update raw values of all digital inputs available in low power */
  IoHwAb_DigInSampleLP();
  #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */
}


/*******************************************************************************
** Function Name        : IoHwAb_IOMOutputsLP                                 **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     : none                       **
**                        Function(s) invoked    :                            **
**                          IoHwAb_DigOutWriteOutputsToHW                     **
*******************************************************************************/
FUNC(void, IOHWAB_CODE)IoHwAb_IOMOutputsLP(void)
{
  #if (IOHWAB_USE_DIG_OUT == STD_ON)
  /* update buffered outputs except demultiplexed outputs */
  IoHwAb_DigOutWriteOutputsToHW();
  #endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */
}


/*******************************************************************************
** Function Name        : IoHwAb_IOMOnTimer                                   **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GucInAcqState                              **
**                        Function(s) invoked    :                            **
**                          IOMActivateTask,                                  **
**                          CoSvAb_FastTimerStart,                            **
**                          Gpt_StartTimer                                    **
*******************************************************************************/
FUNC(void, IOHWAB_CODE)IoHwAb_IOMOnTimer(void)
{
  StatusType LddError = E_NOT_OK;
  IoHwAb_GstIOManagerCounter.ucOnTimerCalled++;
  switch (IoHwAb_GucInAcqState)
  {
  case IOHWAB_ACQ_ANALOG_END :
    LddError = IoHwAb_IOMActivateTask(IoHwAb_GddIOMTaskFG1);

    if (LddError == E_OK)
    {
    	IoHwAb_GstIOManagerCounter.ucOnTimerToFG1++;
    }
    break;

  case IOHWAB_ACQ_DIGITAL :
  case IOHWAB_ACQ_ANALOG :
    LddError = IoHwAb_IOMActivateTask(IoHwAb_GddIOMTaskFG2);

    if (LddError == E_OK)
    {
    	IoHwAb_GstIOManagerCounter.ucOnTimerToFG2++;
    }
    break;

  default :
  /* Do nothing */
    break;
  }
}


/*
  polyspace:begin<MISRA-C:8.8:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard : Rte SWS #7283)
*/
/*******************************************************************************
** Function Name        : IoHwAb_IOM_5ms                                      **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
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
** Remarks              : Global Variable(s)     : none                       **
**                        Function(s) invoked    :                            **
**                          IoHwAb_VolMon,                                    **
**                          IoHwAb_DigInReadHwInputs,                         **
**                          IoHwAb_DigInDebounce                              **
*******************************************************************************/
FUNC(void, IOHWAB_CODE)IoHwAb_IOM_5ms(void)
{
  #if (IOHWAB_USE_VOL_MON == STD_ON)
  /* battery monitoring management*/
  IoHwAb_VolMon();
  #endif /* (IOHWAB_USE_VOL_MON == STD_ON) */

  #if (IOHWAB_USE_DIG_IN == STD_ON)
  /* fast digital input acquisition and debounce */
  IoHwAb_DigInReadHwInputs(TRUE);
  IoHwAb_DigInDebounce((IoHwAb_IndexType)0, IoHwAb_GddNumDigInFast);
  #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */ 
}



/*******************************************************************************
** Function Name        : IoHwAb_IOM_10ms                                     **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
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
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GucInAcqState                              **
**                        Function(s) invoked    :                            **
**                          Pm_GetPowerMode,                                  **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus,                            **
**                          IoHwAb_DigOutWriteOutputsToHW,                    **
**                          IoHwAb_DigOutL9826,                               **
**                          IoHwAb_DigOutL99MC6,                              **
**                          IoHwAb_InputSupplyDigitalControl,                 **
**                          CoSvAb_FastTimerStart,                            **
**                          Gpt_StartTimer,                                   **
**                          IOMActivateTask,                                  **
**                          IoHwAb_InputSupplyAnalogControl                   **
*******************************************************************************/
FUNC(void, IOHWAB_CODE)IoHwAb_IOM_10ms(void)
{
  #if (((IOHWAB_USE_DIG_IN == STD_ON) && (IOHWAB_USE_DIG_SUP_SWT != STD_ON)) \
    || ((IOHWAB_USE_DIG_IN != STD_ON) \
      && (IOHWAB_USE_ANA_IN == STD_ON) && (IOHWAB_USE_ANA_SUP_SWT != STD_ON)))
  StatusType LddError = E_NOT_OK;
  #endif /* (((IOHWAB_USE_DIG_IN == STD_ON) && (IOHWAB_USE_DIG_SUP_SWT == STD_OFF)) \
    || ((IOHWAB_USE_ANA_IN == STD_ON) && (IOHWAB_USE_ANA_SUP_SWT == STD_OFF))) */

  #if (IOHWAB_USE_LP_FLAG == STD_ON)
  #if (IOHWAB_USE_PM_MODULE == STD_ON)
  Pm_PowerModeType LddPmMode = 0U;

  (void)Pm_GetPowerMode(&LddPmMode);
  if ((Pm_PowerModeType)LddPmMode != (Pm_PowerModeType)PM_POWERMODE_LOW)
  {
    #endif /* (IOHWAB_USE_PM_MODULE == STD_ON) */
    /* Set the Lowpower Flag */
    BswM_RequestMode((BswM_UserType)IOHWAB_MODULE_ID, (BswM_ModeType)IOHWAB_LOWPOWER_PREVENT);
    #endif /* (IOHWAB_USE_LP_FLAG == STD_ON) */

    IoHwAb_GstIOManagerCounter.uc10msCalled++;
    /* if the previous IO processing is not yet finished send error to system   */
    /* and skip IO processing                                                   */
    if(IoHwAb_GucInAcqState != IOHWAB_ACQ_NO_ACTION)
    {
      IoHwAb_GstIOManagerCounter.uc10msNormalCnt = 0;
      if (IoHwAb_GstIOManagerCounter.uc10msRecoveryCnt < IOHWAB_THREE)
      {
        if (IoHwAb_GstIOManagerCounter.uc10msErrorCnt >= IOHWAB_THREE)
        {
          IoHwAb_GucInAcqState = IOHWAB_ACQ_NO_ACTION;
          IoHwAb_GstIOManagerCounter.uc10msRecoveryCnt++;
        }
        else
        {
          IoHwAb_GstIOManagerCounter.uc10msErrorCnt++;
        }
      }
      else
      {
        #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
          (uint8)IOHWAB_IOM_10MS_SID, (uint8)IOHWAB_E_DET_WRONG_STATE);
        #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
        #if (IOHWAB_USE_DEM_EVENT == STD_ON)
        Dem_ReportErrorStatus(IOHWAB_E_WRONG_STATE, DEM_EVENT_STATUS_FAILED);
        #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
      }
    }
    else
    {
      IoHwAb_GstIOManagerCounter.uc10msErrorCnt = 0;
      if (IoHwAb_GstIOManagerCounter.uc10msNormalCnt == IOHWAB_NORMAL_MAX)
      {
        IoHwAb_GstIOManagerCounter.uc10msRecoveryCnt = 0;
      }
      else
      {
        IoHwAb_GstIOManagerCounter.uc10msNormalCnt++;
      }
      #if (IOHWAB_USE_DIG_OUT == STD_ON)
      /* currently updating digital outputs */
      IoHwAb_GucInAcqState = IOHWAB_ACQ_DIGITAL_OUT;

      /* update buffered outputs except demultiplexed digital outputs  */
      IoHwAb_DigOutWriteOutputsToHW();
      
      #if (IOHWAB_USE_L9826 == STD_ON)
      /* update the L9826 demultiplexed outputs */
      (void)IoHwAb_DigOutL9826();
      #endif /* (IOHWAB_USE_L9826 == STD_ON) */

	  #if (IOHWAB_USE_L99MC6 == STD_ON)
      /* update the L99MC6 demultiplexed outputs */
      (void)IoHwAb_DigOutL99MC6();
      #endif /* (IOHWAB_USE_L99MC6 == STD_ON) */

      #if (IOHWAB_USE_TLE7240SL == STD_ON)
      /* update the TLE7240SL demultiplexed outputs */
      (void)IoHwAb_DigOutTLE7240SL();
      #endif /* (IOHWAB_USE_TLE7240SL == STD_ON) */
      #endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */

      /* If any kind of digital inputs is present */
      #if (IOHWAB_USE_DIG_IN == STD_ON)
      /* Next step will be acquisition and filtering of digital inputs */
      IoHwAb_GucInAcqState = IOHWAB_ACQ_DIGITAL;

      #if ((IOHWAB_USE_IN_SUP_SWT == STD_ON) && (IOHWAB_USE_DIG_SUP_SWT == STD_ON))
      /* switch on switched battery for digital inputs */
      IoHwAb_InputSupplyDigitalControl(TRUE, TRUE);
      /* start timer for switched battery delay */
      #if (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON)
      (void) CoSvAb_FastTimerStart(IoHwAb_GddIOMFastTimerID, IoHwAb_GddISupplyDigSwitchDelay);
      #endif /* (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON) */

 	  #if (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON)
      Gpt_StartTimer(IoHwAb_GddIOMGptTimerID,
       (IoHwAb_GddISupplyDigSwitchDelay * IoHwAb_GusIOMGptTicksFor1us));
      #endif /* (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON) */
      IoHwAb_GstIOManagerCounter.ucStartTimerCalled++;
      #else /* ((IOHWAB_USE_IN_SUP_SWT == STD_ON) && (IOHWAB_USE_DIG_SUP_SWT == STD_ON)) */
      /* activate acquisition task */
      LddError = IoHwAb_IOMActivateTask(IoHwAb_GddIOMTaskFG2);

      if (LddError == E_OK)
      {
        IoHwAb_GstIOManagerCounter.uc10msToFG2++;
      }

      #endif /* ((IOHWAB_USE_IN_SUP_SWT == STD_ON) && (IOHWAB_USE_DIG_SUP_SWT == STD_ON)) */

      #else /* (IOHWAB_USE_DIG_IN == STD_ON) */
      /* If any kind of analog inputs is present and no digital input is present */
      #if (IOHWAB_USE_ANA_IN == STD_ON)
      /* Next step will be acquisition and filtering of analog inputs */
      IoHwAb_GucInAcqState = IOHWAB_ACQ_ANALOG;
      #if ((IOHWAB_USE_IN_SUP_SWT == STD_ON) && (IOHWAB_USE_ANA_SUP_SWT == STD_ON))
      /* switch on switched battery for analog inputs */
      IoHwAb_InputSupplyAnalogControl(TRUE);
      #if (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON)
      /* Start Timer for switched battery delay */
      (void) CoSvAb_FastTimerStart(IoHwAb_GddIOMFastTimerID, IoHwAb_GddISupplyAnaSwitchDelay);
      #endif /* (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON) */
      #if (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON)
      /* Start Timer for switched battery delay */
      Gpt_StartTimer(IoHwAb_GddIOMGptTimerID,
        (IoHwAb_GddISupplyAnaSwitchDelay * IoHwAb_GusIOMGptTicksFor1us));
      #endif /* (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON) */
      IoHwAb_GstIOManagerCounter.ucStartTimerCalled++;
      #else /* (IOHWAB_USE_IN_SUP_SWT == STD_ON)&&(IOHWAB_USE_ANA_SUP_SWT == STD_ON) */
      /* start acquisition of analog inputs directly, activate acquisition task */

      LddError = IoHwAb_IOMActivateTask(IoHwAb_GddIOMTaskFG2);
      
      if (LddError == E_OK)
      {
        IoHwAb_GstIOManagerCounter.uc10msToFG2++;
      }

      #endif /* ((IOHWAB_USE_ANA_SUP_SWT == STD_ON)&&(IOHWAB_USE_IN_SUP_SWT == STD_ON))  */
      /* If there is no digital inputs or analog inputs */
      #else /* (IOHWAB_USE_ANA_IN == STD_ON) */
      /* Acquisition is finished */
      IoHwAb_GucInAcqState = IOHWAB_ACQ_NO_ACTION;
      #if (IOHWAB_USE_LP_FLAG == STD_ON)
      /* Clear the Lowpower Flag */
      BswM_RequestMode((BswM_UserType)IOHWAB_MODULE_ID, (BswM_ModeType)IOHWAB_LOWPOWER_ALLOW);
      #endif /* (IOHWAB_USE_LP_FLAG == STD_ON) */
      #endif /* (IOHWAB_USE_ANA_IN == STD_ON) */
      #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */
    }
  #if ((IOHWAB_USE_LP_FLAG == STD_ON) && (IOHWAB_USE_PM_MODULE == STD_ON))
  }
  #endif
}

/*
  polyspace:end<MISRA-C:8.8:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard : Rte SWS #7283)
*/

/*******************************************************************************
** Function Name        : TASK(IOHWAB_IOM_TASK_FG2)                           **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
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
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GucInAcqState                              **
**                        Function(s) invoked    :                            **
**                          IoHwAb_DigInReadHwInputs,                         **
**                          IoHwAb_DigInMC33972Acq,                           **
**                          IoHwAb_InputSupplyDigitalControl,                 **
**                          IoHwAb_AnaInConvertAllChannels,                   **
**                          CoSvAb_FastTimerStart,                            **
**                          Gpt_StartTimer,                                   **
**                          ChainTask,                                        **
**                          TerminateTask                                     **
*******************************************************************************/
IOHWAB_IOM_TASK_FG2_FUNC
{
  /* Default: activate task not needed, only terminate current task */
  boolean LblActivateFiltering = FALSE;
  IoHwAb_GstIOManagerCounter.ucFG2Called++;

  /* This task is used to acquire all inputs */
  switch (IoHwAb_GucInAcqState)
  {
  case IOHWAB_ACQ_DIGITAL :
    #if (IOHWAB_USE_DIG_IN == STD_ON)
    /* update value of fast and slow buffered digital inputs */
    IoHwAb_DigInReadHwInputs(FALSE);

    #if (IOHWAB_USE_MC33972 == STD_ON)
    /* read multiplexed inputs */
    (void)IoHwAb_DigInMC33972Acq();
    #endif /* (IOHWAB_USE_MC33972 == STD_ON) */
    #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

    #if (IOHWAB_USE_DIG_IN == STD_ON)
    #if (IOHWAB_USE_DIG_SUP_SWT == STD_ON)
    /* switch off switched battery for digital inputs */
    IoHwAb_InputSupplyDigitalControl(TRUE, FALSE);
    #endif /* (IOHWAB_USE_DIG_SUP_SWT == STD_ON) */
    #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */
    LblActivateFiltering = TRUE;
    break;

  case IOHWAB_ACQ_ANALOG :
    /* start analog acquisition, CB when finished to start analog mux acquisition */
    #if (IOHWAB_USE_ANA_IN == STD_ON)
    if (IoHwAb_AnaInConvertAllChannels() != E_OK)
    {
      #if (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON)
      /* if task is already in use, wait IoHwAb_GddIOMMultiActDelay us */
      (void) CoSvAb_FastTimerStart(IoHwAb_GddIOMFastTimerID, IoHwAb_GddIOMMultiActDelay);
      #endif /* (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON) */
      #if (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON)
      /* if task is already in use, wait IoHwAb_GddIOMMultiActDelay us */
      Gpt_StartTimer(IoHwAb_GddIOMGptTimerID,
        (IoHwAb_GddIOMMultiActDelay * IoHwAb_GusIOMGptTicksFor1us));
      #endif /* (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON) */
      IoHwAb_GstIOManagerCounter.ucStartTimerCalled++;
    }
    else
    {
      IoHwAb_GstIOManagerCounter.ucConvertAllChannelsCalled++;
    }
    #endif /* (IOHWAB_USE_ANA_IN == STD_ON) */
    break;

  default :
  /* Do nothing */
    break;
  }

  /****end user code******/
  if (LblActivateFiltering != 0U)
  {
    IoHwAb_GstIOManagerCounter.ucFG2ToFG1++;
    (void)ChainTask(IoHwAb_GddIOMTaskFG1);
  }
  else
  {
    (void)TerminateTask();
  }
}


/*******************************************************************************
** Function Name        : TASK(IOHWAB_IOM_TASK_FG1)                           **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
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
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GucInAcqState                              **
**                        Function(s) invoked    :                            **
**                          IoHwAb_DigInDebounce,                             **
**                          IoHwAb_InputSupplyAnalogControl,                  **
**                          CoSvAb_FastTimerStart,                            **
**                          Gpt_StartTimer,                                   **
**                          IOMActivateTask,                                  **
**                          IoHwAb_AnaInFilter,                               **
**                          TerminateTask                                     **
*******************************************************************************/
IOHWAB_IOM_TASK_FG1_FUNC
{
  #if (IOHWAB_USE_ANA_SUP_SWT == STD_OFF)
  StatusType LddError = E_NOT_OK;
  #endif /* (IOHWAB_USE_ANA_SUP_SWT == STD_OFF) */

  IoHwAb_GstIOManagerCounter.ucFG1Called++;
  /* This task is used to filter all inputs */
  switch (IoHwAb_GucInAcqState)
  {
  case IOHWAB_ACQ_DIGITAL :
    /* slow digital inputs debouncing (direct, mux) */
    #if (IOHWAB_USE_DIG_IN == STD_ON)
    IoHwAb_DigInDebounce(IoHwAb_GddNumDigInFast, IoHwAb_GddNumDigInSlow);
    #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

    #if (IOHWAB_USE_ANA_IN == STD_ON)
    /* Next step will be acquisition of analog inputs */
    IoHwAb_GucInAcqState = IOHWAB_ACQ_ANALOG;
    #if (IOHWAB_USE_ANA_SUP_SWT == STD_ON)
    /* switch on switched battery for analog inputs */
    IoHwAb_InputSupplyAnalogControl(TRUE);
    #if (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON)
    /* Start Timer for switched battery delay */
    (void) CoSvAb_FastTimerStart(IoHwAb_GddIOMFastTimerID, IoHwAb_GddISupplyAnaSwitchDelay);
    #endif /* (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON) */
    #if (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON)
    /* Start Timer for switched battery delay */
    Gpt_StartTimer(IoHwAb_GddIOMGptTimerID,
      (IoHwAb_GddISupplyAnaSwitchDelay * IoHwAb_GusIOMGptTicksFor1us));
    #endif /* (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON) */
    IoHwAb_GstIOManagerCounter.ucStartTimerCalled++;
    #else /* (IOHWAB_USE_ANA_SUP_SWT == STD_ON) */
    /* start acquisition of analog inputs directly, activate acquisition task */

    LddError = IoHwAb_IOMActivateTask(IoHwAb_GddIOMTaskFG2);
    if(LddError == E_OK)
    {
      IoHwAb_GstIOManagerCounter.ucFG1ToFG2++;
    }

    #endif /* (IOHWAB_USE_ANA_SUP_SWT == STD_ON) */
    #else /* (IOHWAB_USE_ANA_IN == STD_ON) */
    /* IO acquisition and filtering is finished */
    IoHwAb_GucInAcqState = IOHWAB_ACQ_NO_ACTION;

    #if (IOHWAB_USE_LP_FLAG == STD_ON)
    /* Clear the Lowpower Flag */
    BswM_RequestMode((BswM_UserType)IOHWAB_MODULE_ID, (BswM_ModeType)IOHWAB_LOWPOWER_ALLOW);
    #endif /* (IOHWAB_USE_LP_FLAG == STD_ON) */
    #endif /* (IOHWAB_USE_ANA_IN == STD_ON) */
    break;

  case IOHWAB_ACQ_ANALOG :
  case IOHWAB_ACQ_ANALOG_MUX :
  case IOHWAB_ACQ_ANALOG_END :
    /* do analog filtering for analog inputs (direct and mux) */
    #if (IOHWAB_USE_ANA_IN == STD_ON)
    IoHwAb_AnaInFilter();
    #endif /* (IOHWAB_USE_ANA_IN == STD_ON) */
    /* IO acquisition and filtering is finished */
    IoHwAb_GucInAcqState = IOHWAB_ACQ_NO_ACTION;

    #if (IOHWAB_USE_LP_FLAG == STD_ON)
    /* Clear the Lowpower Flag */
    BswM_RequestMode((BswM_UserType)IOHWAB_MODULE_ID, (BswM_ModeType)IOHWAB_LOWPOWER_ALLOW);
    #endif /* (IOHWAB_USE_LP_FLAG == STD_ON) */
    break;

  default:
  /* Do nothing */
    break;
  }

  /****end user code******/
  (void) TerminateTask();
}

/*******************************************************************************
** Function Name        : IoHwAb_IOMActivateTask                              **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
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
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                          GetTaskState,                                     **
**                          ActivateTask,                                     **
**                          CoSvAb_FastTimerStart,                            **
**                          Gpt_StartTimer,                                   **
*******************************************************************************/
static FUNC(StatusType, IOHWAB_CODE)IoHwAb_IOMActivateTask(TaskType TaskId)
{
  StatusType LddError = E_NOT_OK;
  TaskStateType LddTaskState = RUNNING;

  LddError = GetTaskState(TaskId, &LddTaskState);

  if ((LddError == E_OK)
    && (LddTaskState == SUSPENDED))
  {
    LddError = ActivateTask(TaskId);
  }

  if ((LddError != E_OK)
    || (LddTaskState != SUSPENDED))
  {
    #if (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON)
    /* if task is already in use, wait IoHwAb_GddIOMMultiActDelay us */
    (void) CoSvAb_FastTimerStart(IoHwAb_GddIOMFastTimerID, IoHwAb_GddIOMMultiActDelay);
    #endif /* (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON) */
    #if (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON)
    /* if task is already in use, wait IoHwAb_GddIOMMultiActDelay us */
    Gpt_StartTimer(IoHwAb_GddIOMGptTimerID,
      (IoHwAb_GddIOMMultiActDelay * IoHwAb_GusIOMGptTicksFor1us));
    #endif /* (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON) */
    IoHwAb_GstIOManagerCounter.ucStartTimerCalled++;
    LddError = E_NOT_OK;
  }

  return LddError;
}

/*polyspace:end<MISRA-C:8.1:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace:end<MISRA-C:10.1:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace:end<RTE: ABS_ADDR : Not a defect : No Action Planned >  */
/* polyspace-end RTE:UNR [Not a defect:Unset] "Reachable code" */
/* polyspace-begin MISRA-C3:8.7 MISRA-C3:2.2 MISRA-C3:16.1 MISRA-C3:16.4 MISRA-C3:D4.5 [Justified:Unset] "Not a defect" */
#endif /* (IOHWAB_USE_IO_MAN == STD_ON) */

#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

