/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: RamTst.c                                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR RAMTST                                                **
**                                                                            **
**  PURPOSE   : Ram Test API Functionality                                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By       Description                               **
********************************************************************************
** 1.3.2     30-Dec-2020   CY Song          RedMine #27378                    **
** 1.2.7     15-Nov-2015   CY Song    Redmine #6608                           **
** 1.2.5     16-May-2016   CY Song    RedMine #4902                           **
** 1.2.3     05-Oct-2015   CY Song    Correct Misra Rule Error and            **
                                      Redmine#2256 change pRamTstAlg variable **
** 1.0.4     17-Oct-2014   CY Song    Rd#1452 Correct PolySpace               **
** 1.0.3     07-Dec-2013   CY Song    As per SCR 500,RamTst_Dem_Cfg.h         **
**                                    was added in the Include section        **
** 1.0.2     14-Jun-2013   CY Song      CR~104, XAR~580 : RamTst library      **
**                                      Add global variable                   **
**                                      RamTst_GucNumberOfAlgParaSets         **
**                                      RamTst_GucDefaultAlgParaID            **
**                                      RamTst_GulMinNumberOfTestedCells      **
** 1.0.0     07-Jun-2013   CY Song          Initial Version                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "RamTst.h"              /* Ram Test Module Header File */
#include "RamTst_Ram.h"          /* Ram Test Module Header File */
#include "RamTst_Config.h"       /* Ram Test Module Header File */
#include "RamTst_Crc.h"
#include "BswM.h"
#if(RAMTST_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                 /* Ram Test Module Header File */
#endif
#include "RamTst_Internal.h"     /* Ram Test Module Internal Header File */
#include "SchM_RamTst.h"          /* SchM header file for data protection API*/
#if(RAMTST_DEMERROR_REPORT == STD_ON)
#include "RamTst_Dem_Cfg.h"
#endif

/* polyspace-begin MISRA-C3:20.1 [Not a defect:Low] "It is implemented according to autosar specification" */
/* polyspace-begin RTE:UNR [Not a defect:Low] "Not a defect" */
/* polyspace-begin RTE:IDP [Not a defect:Low] "Not a defect" */
/* polyspace-begin RTE:NIV [Not a defect:Low] "Not a defect" */
/* polyspace-begin RTE:OBAI [Not a defect:Low] "Not a defect" */
/* polyspace-begin VARIABLE:ALL [Not a defect:Low] "Not a defect" */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define RAMTST_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : RamTst_GetVersionInfo                               **
**                                                                            **
** Service ID           : 0x0A                                                **
**                                                                            **
** Description          : This Service returns the version information of Ram **
**                        Test Module.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : versioninfo                                         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    :                            **
**                        Det_ReportError                                     **
*******************************************************************************/
#if(RAMTST_GET_VERSION_INFO_API == STD_ON)
FUNC(void, RAMTST_CODE) RamTst_GetVersionInfo
(P2VAR(Std_VersionInfoType, AUTOMATIC, RAMTST_APPL_DATA)versioninfo)
{
  #if(RAMTST_DEV_ERROR_DETECT == STD_ON)
  /* check NULL pointer */
  if(NULL_PTR == versioninfo)
  {
    /* Report to DET */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID,
      RAMTST_GETVERSIONINFO_SID, RAMTST_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "This parameter shall be checked by user " */
    /* Load the vendor Id */
    versioninfo->vendorID = RAMTST_VENDOR_ID;
    /* Load the module Id */
    versioninfo->moduleID = RAMTST_MODULE_ID;
    /* Load Software Major Version */
    versioninfo->sw_major_version = RAMTST_SW_MAJOR_VERSION;
    /* Load Software Minor Version */
    versioninfo->sw_minor_version = RAMTST_SW_MINOR_VERSION;
    /* Load Software Patch Version */
    versioninfo->sw_patch_version = RAMTST_SW_PATCH_VERSION;
    /* polyspace-end MISRA-C3:14.3 [Justified:Low] "This parameter shall be checked by user " */    
  }
}
#endif /* (RAMTST_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
** Function Name        : RamTst_Init                                         **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This Service initializes the Ram Test Module        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
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
*******************************************************************************/

FUNC(void, RAMTST_CODE)RamTst_Init(void)
{
  RamTst_NumberOfBlocksType LddBlkIndex;
  RamTst_NumberOfBlocksType LusBlcks;
  uint16 LusNumberOfBlock;

  /* Is module not initialized */ /* SWS_RamTst_00007 */
  if(RamTst_GddExecuStatus != RAMTST_EXECUTION_UNINIT)
  {
    RAMTST_REPORT_ERROR(RAMTST_INIT_SID, RAMTST_E_STATUS_FAILURE);
  }
  /* Module is initialized */
  else
  {
    /* The test is initialized to use the default test parameter set
     * (RamTstDefaultAlgParamsId) as configured by its RamTstAlgParams container
     */
    /* Required only if the RamTstSelectAlgParams is on,
     * which enables to change the default value to new value using API
     * RamTst_SelectAlgParams  else not req.
     */
    RamTst_GddNewAlgParamsId = RamTst_GucDefaultAlgParaID;

    LddBlkIndex =
     RamTst_GaaAlgParam[RamTst_GddNewAlgParamsId - RAMTST_ONE].usRamTstBlkIndex;

    /* Set the Algorithm Type */
    RamTst_GddNewAlgType = RamTst_GaaAlgParam
                    [RamTst_GddNewAlgParamsId - RAMTST_ONE].ddRamTstAlgCoverage;
    RamTst_GddNumOfTstCells = RamTst_GaaAlgParam
            [RamTst_GddNewAlgParamsId - RAMTST_ONE].ulRamTstNumberOfTestedCells;
    /* Starting Block ID used for BackGround Testing */
    RamTst_GddBckGrdTstRamVar.ddRunningBlockID =
                                RamTst_GaaBlkParam[LddBlkIndex].usRamTstBlockId;
    /* Starting Address for BackGround Testing */
    RamTst_GddBckGrdTstRamVar.ulBckGrdAddress =
                           RamTst_GaaBlkParam[LddBlkIndex].ulRamTstStartAddress;
    /* Size of the Block To be Tested in background testing */
    RamTst_GddBckGrdTstRamVar.ddBalNumOfCells =
                                 RamTst_GaaBlkParam[LddBlkIndex].ulRamBlockSize;
    LusNumberOfBlock = RamTst_GaaAlgParam
                 [RamTst_GddNewAlgParamsId - RAMTST_ONE].usRamTstNumberOfBlocks;
    /* Error Flag Set to False */
    RamTst_GddBckGrdTstRamVar.blGblBckGrdTstError = RAMTST_PASSED;
    RamTst_GddTestStatus = RAMTST_RESULT_NOT_TESTED;

    /* initialize the test result status */
    for(LusBlcks = RAMTST_ZERO; LusBlcks< LusNumberOfBlock; LusBlcks++)
    {
      *(RamTst_GaaBlkParam[LddBlkIndex].pTestBlockStatus) =
                                                      RAMTST_RESULT_NOT_TESTED;
      /* Next Block index */
      LddBlkIndex++;
    }

    /* Error Flag Set to False */
    RamTst_GddBckGrdTstRamVar.blBlkBckGrdTstError = RAMTST_PASSED;
    #if(RAMTST_HIGH_COVERAGE_TEST_SELECTED == STD_ON)

    #if(RAMTST_CRC_8_SUPPORT == STD_ON)
    RamTst_GddBckGrdTstRamVar.ucCrcInitialVal = RAMTST_CRC_INITIAL_VALUE8;
    #endif

    #if(RAMTST_CRC_8H2F_SUPPORT == STD_ON)
    RamTst_GddBckGrdTstRamVar.ucCrcInitialVal = RAMTST_CRC_INITIAL_VALUE8H2F;
    #endif

    #if(RAMTST_CRC_16_SUPPORT == STD_ON)
    RamTst_GddBckGrdTstRamVar.usCrcInitialVal = RAMTST_CRC_INITIAL_VALUE16;
    #endif

    #if(RAMTST_CRC_32_SUPPORT == STD_ON)
    RamTst_GddBckGrdTstRamVar.ulCrcInitialVal = RAMTST_CRC_INITIAL_VALUE32;
    #endif

    #endif

    /* Set the variable RamTst_GddExecuStatus to indicate RamTst is
     * initialized. No need critical section */
    RamTst_GddExecuStatus = RAMTST_EXECUTION_STOPPED;
    #if((RAMTST_STOP_API == STD_ON) || (RAMTST_SUSPEND_API == STD_ON))
    RamTst_TriggerStopOrSuspend = RAMTST_BGEXE_DONE;
    #endif
  }
}

/*******************************************************************************
** Function Name        : RamTst_DeInit                                       **
**                                                                            **
** Service ID           : 0x0C                                                **
**                                                                            **
** Description          : This Service deinitialization RAM Test Modules      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
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
*******************************************************************************/
FUNC(void, RAMTST_CODE) RamTst_DeInit(void)
{
  SchM_Enter_RamTst_RAM_PROTECTION();
  /* Is module not initialized */
  if(RamTst_GddExecuStatus == RAMTST_EXECUTION_UNINIT)
  {
    SchM_Exit_RamTst_RAM_PROTECTION();  
    RAMTST_REPORT_ERROR(RAMTST_DEINIT_SID, RAMTST_E_UNINIT);
  }
  /* Module is initialized */
  else
  {
    /* Set the variable RamTst_GddExecuStatus to indicate RamTst is
     * uninitialized
     */
    RamTst_GddExecuStatus = RAMTST_EXECUTION_UNINIT;
    
    SchM_Exit_RamTst_RAM_PROTECTION();    
  }
}

/*******************************************************************************
** Function Name        : RamTst_Stop                                         **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : This service will stop the ram test                 **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The Ram test module must be initialized.            **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
*******************************************************************************/
#if(RAMTST_STOP_API == STD_ON)
FUNC(void, RAMTST_CODE) RamTst_Stop(void)
{
  SchM_Enter_RamTst_RAM_PROTECTION();
  /* Is module not initialized */
  if(RamTst_GddExecuStatus == RAMTST_EXECUTION_UNINIT)
  {  
    SchM_Exit_RamTst_RAM_PROTECTION();
    RAMTST_REPORT_ERROR(RAMTST_STOP_SID, RAMTST_E_UNINIT);
  }
  /* Is module not initialized or API not called in the correct state */
  else if ((RamTst_GddExecuStatus != RAMTST_EXECUTION_ALLOWED) && /* ok background */
    (RamTst_GddExecuStatus != RAMTST_EXECUTION_SUSPENDED)) /* background */
  {
    SchM_Exit_RamTst_RAM_PROTECTION();
    RAMTST_REPORT_ERROR(RAMTST_STOP_SID, RAMTST_E_STATUS_FAILURE);
  }
  else
  {
    /****
     * [RamTst014]
     *
     *  When  the  RamTst_Stop   function  is  called, 
     * RamTst_MainFunction   shall  still  finish  the  current  atomic  sequence  (if  it  is 
     * executing), afterward the status shall be set to  RAMTST_EXECUTION_STOPPED . The 
     * test result is retained, but test parameters and loop data are not.
     * 
     * Note: stop immediately after current atomic, save status RamTst_MainFunction() only */
    #if(RAMTST_ALLOW_API == STD_ON)
    RamTst_TriggerStopOrSuspend = RAMTST_BGEXE_TRYING_STOP;
    #else
    RamTst_GddExecuStatus = RAMTST_EXECUTION_STOPPED;
    #endif

    SchM_Exit_RamTst_RAM_PROTECTION();
  }
}
#endif /* (RAMTST_STOP_API == STD_ON) */

/*******************************************************************************
** Function Name        : RamTst_Allow                                        **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This service will start the ram test if it is       **
**                        previously stopped by API RamTst_Stop               **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The Ram test module must be initialized.            **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
*******************************************************************************/
#if(RAMTST_ALLOW_API == STD_ON)
FUNC(void, RAMTST_CODE) RamTst_Allow(void)
{
  SchM_Enter_RamTst_RAM_PROTECTION();
  /* Is module not initialized */
  if(RamTst_GddExecuStatus == RAMTST_EXECUTION_UNINIT)
  {
    SchM_Exit_RamTst_RAM_PROTECTION();
    RAMTST_REPORT_ERROR(RAMTST_ALLOW_SID, RAMTST_E_UNINIT);
  }
  /* [RamTst170]  If  DET  is  enabled  and  the  execution  status  is  not 
   * RAMTST_EXECUTION_STOPPED , the function  RamTst_Allow  shall report the error 
   * value  RAMTST_E_STATUS_FAILURE   to  the  DET,  and  then  immediately  return. 
   */
  else if(RamTst_GddExecuStatus != RAMTST_EXECUTION_STOPPED)
  {
    SchM_Exit_RamTst_RAM_PROTECTION();
    RAMTST_REPORT_ERROR(RAMTST_ALLOW_SID, RAMTST_E_STATUS_FAILURE);
  }
  /* Module is initialized */
  else
  { 
    RamTst_NumberOfBlocksType LddBlkIndex;
    
    RamTst_GddExecuStatus = RAMTST_EXECUTION_ALLOWED;    

    #if((RAMTST_STOP_API == STD_ON) || (RAMTST_SUSPEND_API == STD_ON))
    RamTst_TriggerStopOrSuspend = RAMTST_BGEXE_DONE;
    #endif

    /* Change the execution status to running to start the RAM test in the
     * next mainfunction call. SWS_RamTst_00169
     *
     * OverAll test result is set to UNDEFINED as Test will start from Next
       Mainfunction */
    RamTst_GddTestStatus = RAMTST_RESULT_UNDEFINED;    

    /* the test status of first block changes to 'undefined' */
    LddBlkIndex = RamTst_GaaAlgParam[RamTst_GddNewAlgParamsId - RAMTST_ONE].usRamTstBlkIndex;
    /* polyspace +2 MISRA-C3:14.3 [Justified:Low] "To avoid the rule violation" */
    if (LddBlkIndex < RamTst_GulNumberOfBlocks)
    {
      *(RamTst_GaaBlkParam[LddBlkIndex].pTestBlockStatus) = RAMTST_RESULT_UNDEFINED;
    }
      
    SchM_Exit_RamTst_RAM_PROTECTION();

    BswM_RequestMode((BswM_UserType)RAMTST_MODULE_ID,
                       (BswM_ModeType)RAMTST_LOWPOWER_PREVENT);
  }
}
#endif /* (RAMTST_ALLOW_API == STD_ON) */

/*******************************************************************************
** Function Name        : RamTst_Suspend                                      **
**                                                                            **
** Service ID           : 0x0D                                                **
**                                                                            **
** Description          : This service will suspend current operation of      **
**                        background RAM test until resume is called          **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The Ram test module must be initialized.            **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
*******************************************************************************/
#if(RAMTST_SUSPEND_API == STD_ON)
FUNC(void, RAMTST_CODE) RamTst_Suspend(void)
{

  SchM_Enter_RamTst_RAM_PROTECTION();

  /* Is module not initialized */
  if(RamTst_GddExecuStatus == RAMTST_EXECUTION_UNINIT)
  {
    SchM_Exit_RamTst_RAM_PROTECTION();
    RAMTST_REPORT_ERROR(RAMTST_SUSPEND_SID, RAMTST_E_UNINIT);
  }

  /* Is module not initialized or API not called in the correct state */
  else if(RamTst_GddExecuStatus != RAMTST_EXECUTION_ALLOWED)
  {
    SchM_Exit_RamTst_RAM_PROTECTION();
    RAMTST_REPORT_ERROR(RAMTST_SUSPEND_SID, RAMTST_E_STATUS_FAILURE);
  }
  /* Module is initialized */
  else
  {    
    /* Change the execution status to suspend to stop the RAM test in the
     * next mainfunction call. SWS_RamTst_00171
     * if 'stop request' is running, 'Suspend request' shall be ignored
     */
    if (RAMTST_BGEXE_TRYING_STOP != RamTst_TriggerStopOrSuspend)
    {
      RamTst_TriggerStopOrSuspend = RAMTST_BGEXE_TRYING_SUSPEND;
    }
    SchM_Exit_RamTst_RAM_PROTECTION();
  }
}
#endif /* (RAMTST_SUSPEND_API == STD_ON) */

/*******************************************************************************
** Function Name        : RamTst_Resume                                       **
**                                                                            **
** Service ID           : 0x0E                                                **
**                                                                            **
** Description          : This service will allow to continue the background  **
**                        RAM Test at the point is was suspended.             **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The Ram test module must be initialized.            **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
*******************************************************************************/
#if(RAMTST_RESUME_API == STD_ON)
FUNC(void, RAMTST_CODE) RamTst_Resume(void)
{
  SchM_Enter_RamTst_RAM_PROTECTION();
  /* Is module not initialized */
  if(RamTst_GddExecuStatus == RAMTST_EXECUTION_UNINIT)
  {
    SchM_Exit_RamTst_RAM_PROTECTION();
    RAMTST_REPORT_ERROR(RAMTST_RESUME_SID, RAMTST_E_UNINIT);
  }

  /* Is module not initialized or API not called in the correct state */
  else if(RamTst_GddExecuStatus != RAMTST_EXECUTION_SUSPENDED)
  {
    SchM_Exit_RamTst_RAM_PROTECTION();
    RAMTST_REPORT_ERROR(RAMTST_RESUME_SID, RAMTST_E_STATUS_FAILURE);
  }
  /* Module is initialized */
  else
  {
    /* Change the execution status to running to start the RAM test in the
     * next mainfunction call. SWS_RamTst_00018
     */
    RamTst_GddExecuStatus = RAMTST_EXECUTION_ALLOWED;
    SchM_Exit_RamTst_RAM_PROTECTION();      
  }
}
#endif /* (RAMTST_RESUME_API == STD_ON) */

/*******************************************************************************
** Function Name        : RamTst_GetExecutionStatus                           **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : This service returns the current RAM Test execution **
**                      : status.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : RamTst_ExecutionStatusType                          **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if(RAMTST_GET_EXECUTION_STATUS_API == STD_ON)
FUNC(RamTst_ExecutionStatusType, RAMTST_CODE) RamTst_GetExecutionStatus(void)
{
  RamTst_ExecutionStatusType execStatus;

  SchM_Enter_RamTst_RAM_PROTECTION();
  if (RAMTST_EXECUTION_ALLOWED == RamTst_GddExecuStatus)
  {
    execStatus = RAMTST_EXECUTION_RUNNING;
  }
  else
  {
    execStatus = RamTst_GddExecuStatus;
  }
  SchM_Exit_RamTst_RAM_PROTECTION();

  /* Is module not initialized */
  if(execStatus == RAMTST_EXECUTION_UNINIT)
  {
    RAMTST_REPORT_ERROR(RAMTST_GETEXECUTIONSTATUS_SID, RAMTST_E_UNINIT);
  }
  /* Return current execution status */
  return execStatus;  
}
#endif /* (RAMTST_GET_EXECUTION_STATUS_API == STD_ON) */

/*******************************************************************************
** Function Name        : RamTst_GetTestResult                                **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : This service returns the current RAM Test  result   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : RamTst_TestResultType                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if(RAMTST_GET_TEST_RESULT_API == STD_ON)
FUNC(RamTst_TestResultType, RAMTST_CODE) RamTst_GetTestResult(void)
{
  RamTst_TestResultType result;

  SchM_Enter_RamTst_RAM_PROTECTION();  

  /* Is module not initialized */
  if(RamTst_GddExecuStatus == RAMTST_EXECUTION_UNINIT)
  {
    SchM_Exit_RamTst_RAM_PROTECTION();  

    RAMTST_REPORT_ERROR(RAMTST_GETTESTRESULT_SID, RAMTST_E_UNINIT);
    /* RamTst202 : if no test was started yet (after reset or de-init). */
    result = RAMTST_RESULT_NOT_TESTED;
  }
  else
  {    
    result = RamTst_GddTestStatus;
    SchM_Exit_RamTst_RAM_PROTECTION(); 
  }
  
  /* Return current execution status */
  return result;
}
#endif /* (RAMTST_GET_TEST_RESULT_API == STD_ON) */

/*******************************************************************************
** Function Name        : RamTst_GetTestResultPerBlock                        **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : This service returns the current RAM Test result of **
**                        a block                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : RamTst_NumberOfBlocksType                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : RamTst_TestResultType                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if(RAMTST_GET_TEST_RESULT_PER_BLOCK_API == STD_ON)
FUNC(RamTst_TestResultType, RAMTST_CODE) RamTst_GetTestResultPerBlock(
                                              RamTst_NumberOfBlocksType BlockId)
{
  RamTst_TestResultType  LddBlkTstResult;

  SchM_Enter_RamTst_RAM_PROTECTION();
  
  /* Is module not initialized */
  if(RamTst_GddExecuStatus == RAMTST_EXECUTION_UNINIT)
  {
    SchM_Exit_RamTst_RAM_PROTECTION();   
    RAMTST_REPORT_ERROR(RAMTST_GETTESTRESULTPERBLOCK_SID, RAMTST_E_UNINIT);
    /* if this block is considered as not yet tested. */
    LddBlkTstResult = RAMTST_RESULT_NOT_TESTED;
  }
  else if((BlockId > RamTst_GusMaxBlockId) || (BlockId == RAMTST_ZERO))
  {
    SchM_Exit_RamTst_RAM_PROTECTION();
    
    RAMTST_REPORT_ERROR(RAMTST_GETTESTRESULTPERBLOCK_SID, RAMTST_E_OUT_OF_RANGE);
    LddBlkTstResult = RAMTST_RESULT_UNDEFINED;
  }
  else
  {
    /* fetch the ram result for the block */
    LddBlkTstResult = RamTst_GaaBlockStatus[BlockId -  RAMTST_ONE];
    SchM_Exit_RamTst_RAM_PROTECTION();
  }

  /* Return current execution status */
  return LddBlkTstResult;
}
#endif /* (RAMTST_GET_TEST_RESULT_PER_BLOCK_API == STD_ON) */

/*******************************************************************************
** Function Name        : RamTst_GetAlgParams                                 **
**                                                                            **
** Service ID           : 0x12                                                **
**                                                                            **
** Description          : This service returns the ID of the current RAM Test **
**                        algorithm parameter set                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : RamTst_AlgParamsIdType                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if(RAMTST_GET_ALG_PARAMS_API == STD_ON)
FUNC(RamTst_AlgParamsIdType, RAMTST_CODE) RamTst_GetAlgParams(void)
{  
  RamTst_AlgParamsIdType algId;
  
  SchM_Enter_RamTst_RAM_PROTECTION();

  algId = RamTst_GddNewAlgParamsId;
  
  /* Is module not initialized */
  if(RamTst_GddExecuStatus == RAMTST_EXECUTION_UNINIT)
  {
    SchM_Exit_RamTst_RAM_PROTECTION();
    RAMTST_REPORT_ERROR(RAMTST_GETALGPARAMS_SID, RAMTST_E_UNINIT);
  }
  else
  {
    SchM_Exit_RamTst_RAM_PROTECTION();
  }
 
  /* Return ID of current algorithm parameter set */
  return algId; 
}
#endif /* (RAMTST_GET_ALG_PARAMS_API == STD_ON) */

/*******************************************************************************
** Function Name        : RamTst_GetTestAlgorithm                             **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : This service returns the the current RAM Test       **
**                        algorithm                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : RamTst_AlgorithmType                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
*******************************************************************************/
#if(RAMTST_GET_TEST_ALGORITHM_API == STD_ON)
FUNC(RamTst_AlgorithmType, RAMTST_CODE) RamTst_GetTestAlgorithm(void)
{
  RamTst_AlgorithmType algType;

  SchM_Enter_RamTst_RAM_PROTECTION();

  algType = RamTst_GddNewAlgType;
  
  /* Is module not initialized */
  if(RamTst_GddExecuStatus == RAMTST_EXECUTION_UNINIT)
  {
    SchM_Exit_RamTst_RAM_PROTECTION();
    RAMTST_REPORT_ERROR(RAMTST_GETTESTALGORITHM_SID, RAMTST_E_UNINIT);
  }
  else
  {
    SchM_Exit_RamTst_RAM_PROTECTION();
  }

  /* Return the current ram test algorithm */
  return algType;
}
#endif /* (RAMTST_GET_TEST_ALGORITHM_API == STD_ON) */

/*******************************************************************************
** Function Name        : RamTst_GetNumberOfTestedCells                       **
**                                                                            **
** Service ID           : 0x09                                                **
**                                                                            **
** Description          : This service returns the the current RAM Test       **
**                        algorithm                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : RamTst_NumberOfTestedCellsType                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
*******************************************************************************/
#if(RAMTST_GET_NUMBER_OF_TESTED_CELLS_API == STD_ON)
FUNC(RamTst_NumberOfTestedCellsType, RAMTST_CODE) RamTst_GetNumberOfTestedCells(void)
{
  RamTst_NumberOfTestedCellsType numOfCells;
  
  SchM_Enter_RamTst_RAM_PROTECTION();

  numOfCells = RamTst_GddNumOfTstCells;
  
  /* Is module not initialized */
  if(RamTst_GddExecuStatus == RAMTST_EXECUTION_UNINIT)
  {
    SchM_Exit_RamTst_RAM_PROTECTION();
    RAMTST_REPORT_ERROR(RAMTST_GETNUMBEROFTESTEDCELLS_SID, RAMTST_E_UNINIT);
  }
  else
  {
    SchM_Exit_RamTst_RAM_PROTECTION();
  }
  
  /* Return the current ram test algorithm */
  return numOfCells;

}
#endif /* (RAMTST_GET_NUMBER_OF_TESTED_CELLS_API == STD_ON) */

/*******************************************************************************
** Function Name        : RamTst_SelectAlgParams                              **
**                                                                            **
** Service ID           : 0x0B                                                **
**                                                                            **
** Description          : This service used to set the test algorithm and its **
**                        parameter set                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : RamTst_AlgParamsIdType                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
*******************************************************************************/
#if(RAMTST_SELECT_ALG_PARAMS_API == STD_ON)
FUNC(void, RAMTST_CODE) RamTst_SelectAlgParams(
                                          RamTst_AlgParamsIdType NewAlgParamsId)
{
  SchM_Enter_RamTst_RAM_PROTECTION();
  /* Is module not initialized */
  if(RamTst_GddExecuStatus == RAMTST_EXECUTION_UNINIT)
  {
    SchM_Exit_RamTst_RAM_PROTECTION();
    RAMTST_REPORT_ERROR(RAMTST_SELECTALGPARAMS_SID, RAMTST_E_UNINIT);
  }
  else if((NewAlgParamsId > RamTst_GucNumberOfAlgParaSets)||
       (NewAlgParamsId == RAMTST_ZERO))
  {
    SchM_Exit_RamTst_RAM_PROTECTION();
    RAMTST_REPORT_ERROR(RAMTST_SELECTALGPARAMS_SID, RAMTST_E_OUT_OF_RANGE);
  }
  else if(RamTst_GddExecuStatus != RAMTST_EXECUTION_STOPPED)
  {
    SchM_Exit_RamTst_RAM_PROTECTION();
    RAMTST_REPORT_ERROR(RAMTST_SELECTALGPARAMS_SID, RAMTST_E_STATUS_FAILURE);
  }
  else
  {
    uint16 LusNumberOfBlock;
    RamTst_NumberOfBlocksType LddBlkIndex;
  
    /* Set the latest algorithm ID */
    RamTst_GddNewAlgParamsId = NewAlgParamsId;
    /* Update the latest algorithm type */
    RamTst_GddNewAlgType =
          RamTst_GaaAlgParam[NewAlgParamsId - RAMTST_ONE].ddRamTstAlgCoverage;
    /* Reset the number of tested cells to default value of algorithm */
    RamTst_GddNumOfTstCells = RamTst_GaaAlgParam
                    [NewAlgParamsId - RAMTST_ONE].ulRamTstNumberOfTestedCells;
    /* Reset the Module test status */
    RamTst_GddTestStatus = RAMTST_RESULT_NOT_TESTED;
    
    SchM_Exit_RamTst_RAM_PROTECTION();
    
    /* Block Index */
    LddBlkIndex = RamTst_GaaAlgParam
                     [RamTst_GddNewAlgParamsId - RAMTST_ONE].usRamTstBlkIndex;

    /* Number of Blocks configured for Algorithm */
    LusNumberOfBlock = LddBlkIndex + RamTst_GaaAlgParam
                        [NewAlgParamsId - RAMTST_ONE].usRamTstNumberOfBlocks;  

    /* polyspace +2 MISRA-C3:14.3 [Justified:Low] "To avoid the rule violation" */
    if (LusNumberOfBlock <= RamTst_GulNumberOfBlocks) /* Note <= */
    {
      /* Starting Block ID used for BackGround Testing */
      RamTst_GddBckGrdTstRamVar.ddRunningBlockID =
                                RamTst_GaaBlkParam[LddBlkIndex].usRamTstBlockId;
      /* Starting Address for BackGround Testing */
      RamTst_GddBckGrdTstRamVar.ulBckGrdAddress =
                           RamTst_GaaBlkParam[LddBlkIndex].ulRamTstStartAddress;
      /* Size of the Block To be Tested in background testing */
      RamTst_GddBckGrdTstRamVar.ddBalNumOfCells =
                                 RamTst_GaaBlkParam[LddBlkIndex].ulRamBlockSize;
      /* Error Flag Set to False */
      RamTst_GddBckGrdTstRamVar.blGblBckGrdTstError = RAMTST_PASSED;

      /* Error Flag Set to False */
      RamTst_GddBckGrdTstRamVar.blBlkBckGrdTstError = RAMTST_PASSED;

      #if(RAMTST_HIGH_COVERAGE_TEST_SELECTED == STD_ON)

      #if(RAMTST_CRC_8_SUPPORT == STD_ON)
      RamTst_GddBckGrdTstRamVar.ucCrcInitialVal = RAMTST_CRC_INITIAL_VALUE8;
      #endif

      #if(RAMTST_CRC_8H2F_SUPPORT == STD_ON)
      RamTst_GddBckGrdTstRamVar.ucCrcInitialVal = RAMTST_CRC_INITIAL_VALUE8H2F;
      #endif

      #if(RAMTST_CRC_16_SUPPORT == STD_ON)
      RamTst_GddBckGrdTstRamVar.usCrcInitialVal = RAMTST_CRC_INITIAL_VALUE16;
      #endif

      #if(RAMTST_CRC_32_SUPPORT == STD_ON)
      RamTst_GddBckGrdTstRamVar.ulCrcInitialVal = RAMTST_CRC_INITIAL_VALUE32;
      #endif

      #endif    

      /* initialize the test result status */
      for(; LddBlkIndex< LusNumberOfBlock; LddBlkIndex++)
      {
        *(RamTst_GaaBlkParam[LddBlkIndex].pTestBlockStatus) =
                                                 RAMTST_RESULT_NOT_TESTED;
      }
    /* polyspace +3 MISRA-C3:2.1 [Justified:Low] "To avoid the rule violation" */
    }
    else
    {
      RAMTST_REPORT_ERROR(RAMTST_SELECTALGPARAMS_SID, RAMTST_E_OUT_OF_RANGE);
    }
  }
}
#endif /* (RAMTST_SELECT_ALG_PARAMS_API == STD_ON) */

/*******************************************************************************
** Function Name        : RamTst_ChangeNumberOfTestedCells                    **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : This service used to change the number of tested    **
**                        cells                                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : RamTst_NumberOfTestedCellsType                      **
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
*******************************************************************************/
#if(RAMTST_CHANGE_NUMBER_OF_TESTED_CELLS_API == STD_ON)
FUNC(void, RAMTST_CODE) RamTst_ChangeNumberOfTestedCells(
                          RamTst_NumberOfTestedCellsType NewNumberOfTestedCells)

{
  uint8 LucParaId = RamTst_GddNewAlgParamsId - RAMTST_ONE;

  if ((RamTst_GddNewAlgParamsId != 0U) && (LucParaId < RamTst_GucNumberOfAlgParaSets))
  {
    /* Maximum Number of Tested Cells accepted for the current Alg Config */
    uint32 LulMaxNumberOfTestedCells = RamTst_GaaAlgParam
                                    [LucParaId].ulRamTstMaxNumberOfTestedCells;

    SchM_Enter_RamTst_RAM_PROTECTION();
    
    /* Is module not initialized */
    if(RamTst_GddExecuStatus == RAMTST_EXECUTION_UNINIT)
    {
      SchM_Exit_RamTst_RAM_PROTECTION();  
      RAMTST_REPORT_ERROR(RAMTST_CHANGENUMBEROFTESTEDCELLS_SID, RAMTST_E_UNINIT);
    }
    else if ((NewNumberOfTestedCells < RamTst_GulMinNumberOfTestedCells) ||
      (NewNumberOfTestedCells > LulMaxNumberOfTestedCells))
    {
      SchM_Exit_RamTst_RAM_PROTECTION();  
      RAMTST_REPORT_ERROR(RAMTST_CHANGENUMBEROFTESTEDCELLS_SID, RAMTST_E_OUT_OF_RANGE);
    }
    else if (RamTst_GddExecuStatus != RAMTST_EXECUTION_STOPPED)
    {
      SchM_Exit_RamTst_RAM_PROTECTION();  
      RAMTST_REPORT_ERROR(RAMTST_CHANGENUMBEROFTESTEDCELLS_SID, RAMTST_E_STATUS_FAILURE);
    }
    else 
    {
      /* Reset the number of tested cells to default value of algorithm */
      RamTst_GddNumOfTstCells = NewNumberOfTestedCells;
      SchM_Exit_RamTst_RAM_PROTECTION();  
    }      
  }
  else
  {
    RAMTST_REPORT_ERROR(RAMTST_CHANGENUMBEROFTESTEDCELLS_SID, RAMTST_E_OUT_OF_RANGE);
  }
}
#endif /* (RAMTST_CHANGE_NUMBER_OF_TESTED_CELLS_API == STD_ON) */

/*******************************************************************************
** Function Name        : RamTst_RunFullTest                                  **
**                                                                            **
** Service ID           : 0x10                                                **
**                                                                            **
** Description          : This service executing the full RAM Test in the     **
**                        foreground                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
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
*******************************************************************************/
#if(RAMTST_RUN_FULL_TEST_API == STD_ON)
FUNC(void, RAMTST_CODE) RamTst_RunFullTest(void)
{
  RamTst_AlgType pRamTstAlg[] =
  {
    #if(RAMTST_LOW_COVERAGE_TEST_SELECTED == STD_ON)
    &RamTst_RunParityBitTst,
    #endif
    #if(RAMTST_MEDIUM_COVERAGE_TEST_SELECTED == STD_ON)
    &RamTst_RunPatternChk,
    #endif
    #if(RAMTST_HIGH_COVERAGE_TEST_SELECTED == STD_ON)
    &RamTst_RunCrcTst
    #endif
  };
  uint8 LucParaId;

  SchM_Enter_RamTst_RAM_PROTECTION();  
  /* Is module not initialized */
  if(RamTst_GddExecuStatus == RAMTST_EXECUTION_UNINIT)
  {
    SchM_Exit_RamTst_RAM_PROTECTION();
    RAMTST_REPORT_ERROR(RAMTST_RUNFULLTEST_SID, RAMTST_E_UNINIT);
  }
  else if(RamTst_GddExecuStatus != RAMTST_EXECUTION_STOPPED)
  {
    SchM_Exit_RamTst_RAM_PROTECTION();
    RAMTST_REPORT_ERROR(RAMTST_RUNFULLTEST_SID, RAMTST_E_STATUS_FAILURE);
  }
  else
  { 
    /* Change the Execution Status of the Module to RUNNING */
    RamTst_GddExecuStatus = RAMTST_EXECUTION_RUNNING;
    SchM_Exit_RamTst_RAM_PROTECTION();    
    BswM_RequestMode((BswM_UserType)RAMTST_MODULE_ID,
                       (BswM_ModeType)RAMTST_LOWPOWER_PREVENT);

    LucParaId = RamTst_GddNewAlgParamsId - RAMTST_ONE;      
    if (LucParaId < RamTst_GucNumberOfAlgParaSets)
    {
      /* Number of Blocks configured for Algorithm */
      uint16 LusBlkIndex = RamTst_GaaAlgParam[LucParaId].usRamTstBlkIndex;
      uint16 LusNumberOfBlock = LusBlkIndex + RamTst_GaaAlgParam[LucParaId].usRamTstNumberOfBlocks;   

      /* polyspace +2 MISRA-C3:14.3 [Justified:Low] "To avoid the rule violation" */
      if (LusNumberOfBlock <= RamTst_GulNumberOfBlocks) /* Note !! <= less than or equal to */
      {
        boolean blockIsFailed = (boolean)RAMTST_FALSE;
        /* [RamTst202]
         * if a test was started, not all blocks have yet been tested and 
         * no block result is RAMTST_RESULT_NOT_OK.*/
        RamTst_GddTestStatus = RAMTST_RESULT_UNDEFINED;
        
        for(; LusBlkIndex < LusNumberOfBlock; LusBlkIndex++)
        {
          P2CONST(RamTst_BlockParams, AUTOMATIC, RAMTST_VAR) block = &RamTst_GaaBlkParam[LusBlkIndex];            
          
          if(RamTst_GddNewAlgType != RAMTST_ALGORITHM_UNDEFINED) /* != 0U */ 
          {
            uint8 algIdx = (uint8)RamTst_GddNewAlgType - (uint8)RAMTST_ONE;          

            /* polyspace +3 MISRA-C3:14.3 [Justified:Low] "To avoid the rule violation" */
            if (NULL_PTR != pRamTstAlg[algIdx])
            {
              /* if a test on this block is running. */
              *(block->pTestBlockStatus) = RAMTST_RESULT_UNDEFINED;
              if (RAMTST_PASSED == (*pRamTstAlg[algIdx])(block->usRamTstBlockId))
              {
                /* if all memory cells in this block have been tested sucessfully. */
                *(block->pTestBlockStatus) = RAMTST_RESULT_OK;
              }
              else
              {
                /* if a failure has been detected for at least one memory cell in this block */
                *(block->pTestBlockStatus) = RAMTST_RESULT_NOT_OK;
                /* if at least one block test result is RAMTST_RESULT_NOT_OK 
                 * regardless whether all blocks have been already tested or not. */                
                blockIsFailed = (boolean)RAMTST_TRUE;
              }
            /* polyspace +3 MISRA-C3:2.1 [Justified:Low] "To avoid the rule violation" */ 
            }
            else
            {     
              /* undefined algorithm ignore the block */
              *(block->pTestBlockStatus) = RAMTST_RESULT_NOT_TESTED;            
              RAMTST_REPORT_ERROR(RAMTST_RUNFULLTEST_SID, RAMTST_E_STATUS_FAILURE);
            }          
          }
          else
          {
            /* undefined algorithm ignore the block */
            *(block->pTestBlockStatus) = RAMTST_RESULT_NOT_TESTED;
          }                                                    
        } /* for loop */

        if(RAMTST_TRUE == blockIsFailed)
        {
          #if(RAMTST_DEMERROR_REPORT == STD_ON)
          /* Raise DEM Error and set the RamTst_GddTestStatus to Failed */
          Dem_ReportErrorStatus(RamTst_GusRamFailure, DEM_EVENT_STATUS_FAILED);
          #endif
          RamTst_GddTestStatus = RAMTST_RESULT_NOT_OK;                          
        }
        else
        {
          /* if all blocks have been tested with result status RAMTST_RESULT_OK */
          RamTst_GddTestStatus = RAMTST_RESULT_OK;
        }
      }    
    }
    else
    {     
      RAMTST_REPORT_ERROR(RAMTST_RUNFULLTEST_SID, RAMTST_E_STATUS_FAILURE);
    } 
    
    SchM_Enter_RamTst_RAM_PROTECTION();
    RamTst_GddExecuStatus = RAMTST_EXECUTION_STOPPED;
    SchM_Exit_RamTst_RAM_PROTECTION();

    BswM_RequestMode((BswM_UserType)RAMTST_MODULE_ID,
                     (BswM_ModeType)RAMTST_LOWPOWER_ALLOW);
  }
}
#endif /* (RAMTST_RUN_FULL_TEST_API == STD_ON) */

/*******************************************************************************
** Function Name        : RamTst_RunPartialTest                               **
**                                                                            **
** Service ID           : 0x11                                                **
**                                                                            **
** Description          : This service is for testing one RAM block in the    **
**                        foreground                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : RamTst_NumberOfBlocksType                           **
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
*******************************************************************************/
#if(RAMTST_RUN_PARTIAL_TEST_API == STD_ON)
FUNC(void, RAMTST_CODE) RamTst_RunPartialTest(RamTst_NumberOfBlocksType BlockId)
{
  RamTst_AlgType pRamTstAlg[] =
  {
    #if(RAMTST_LOW_COVERAGE_TEST_SELECTED == STD_ON)
    &RamTst_RunParityBitTst,
    #endif
    #if(RAMTST_MEDIUM_COVERAGE_TEST_SELECTED == STD_ON)
    &RamTst_RunPatternChk,
    #endif
    #if(RAMTST_HIGH_COVERAGE_TEST_SELECTED == STD_ON)
    &RamTst_RunCrcTst
    #endif
  };

  SchM_Enter_RamTst_RAM_PROTECTION(); 

  /* Is module not initialized */
  if(RamTst_GddExecuStatus == RAMTST_EXECUTION_UNINIT)
  {
    SchM_Exit_RamTst_RAM_PROTECTION();    
    RAMTST_REPORT_ERROR(RAMTST_RUNPARTIALTEST_SID, RAMTST_E_UNINIT);
  }
  else if((RamTst_GddExecuStatus != RAMTST_EXECUTION_STOPPED) &&
    (RamTst_GddExecuStatus != RAMTST_EXECUTION_SUSPENDED))
  {
    SchM_Exit_RamTst_RAM_PROTECTION();    
    RAMTST_REPORT_ERROR(RAMTST_RUNPARTIALTEST_SID, RAMTST_E_STATUS_FAILURE);  
  }
  else if((BlockId > RamTst_GusMaxBlockId) || (BlockId == RAMTST_ZERO))
  {
    SchM_Exit_RamTst_RAM_PROTECTION();    
    RAMTST_REPORT_ERROR(RAMTST_RUNPARTIALTEST_SID, RAMTST_E_OUT_OF_RANGE);
  }
  else 
  {
    P2CONST(RamTst_BlockParams,AUTOMATIC, RAMTST_VAR) block = &RamTst_GaaBlkParam[BlockId - RAMTST_ONE];  
  
    /* Change the Execution Status of the Module to RUNNING */
    RamTst_GddExecuStatus = RAMTST_EXECUTION_RUNNING;
    SchM_Exit_RamTst_RAM_PROTECTION(); 
    
    BswM_RequestMode((BswM_UserType)RAMTST_MODULE_ID,
                       (BswM_ModeType)RAMTST_LOWPOWER_PREVENT);

    if(RamTst_GddNewAlgType == RAMTST_ALGORITHM_UNDEFINED)
    {
      *(block->pTestBlockStatus) = RAMTST_RESULT_NOT_TESTED;
    }
    else
    {
      /* if a test on this block is running */
      *(block->pTestBlockStatus) = RAMTST_RESULT_UNDEFINED; 

      /* polyspace<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */
      if (RAMTST_PASSED == (*pRamTstAlg[(uint32)RamTst_GddNewAlgType - RAMTST_ONE])(BlockId))
      {
        *(block->pTestBlockStatus) = RAMTST_RESULT_OK;      
      }
      else 
      {
        *(block->pTestBlockStatus) = RAMTST_RESULT_NOT_OK;

        #if(RAMTST_DEMERROR_REPORT == STD_ON)
        /* Raise DEM Error and set the RamTst_GddTestStatus to Failed */
        Dem_ReportErrorStatus(RamTst_GusRamFailure, DEM_EVENT_STATUS_FAILED);
        #endif
        RamTst_GddTestStatus = RAMTST_RESULT_NOT_OK;
      }
    }

    SchM_Enter_RamTst_RAM_PROTECTION();
    RamTst_GddExecuStatus = RAMTST_EXECUTION_STOPPED;
    SchM_Exit_RamTst_RAM_PROTECTION();

    BswM_RequestMode((BswM_UserType)RAMTST_MODULE_ID,
                     (BswM_ModeType)RAMTST_LOWPOWER_ALLOW);
  }
}
#endif /* (RAMTST_RUN_PARTIAL_TEST_API == STD_ON) */

/*******************************************************************************
** Function Name        : RamTst_MainFunction                                 **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This is Scheduled function for executing the RAM    **
**                        Test in the background                              **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : None                                                **
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
*******************************************************************************/
/* polyspace +2 MISRA-C3:8.4 [Justified:Low] "It is invoked by RTE" */
FUNC(void, RAMTST_CODE) RamTst_MainFunction(void)
{
  uint8 LucParaId;
  uint16 LusRunBlkID;
  RamTst_NumberOfTestedCellsType LddCurrNumOfCells;
  RamTst_NumberOfTestedCellsType LddMaxNumOfCellsPerMF;
  RamTst_NumberOfBlocksType LddBlkIndex;
  RamTst_NumberOfBlocksType LusBlkID;
  RamTst_NumberOfBlocksType LusNumberOfBlock;
  
  RamTst_AlgBckGrdTstType pRamTstAlgBckGrdTst[] = 
  {
    #if(RAMTST_LOW_COVERAGE_TEST_SELECTED == STD_ON)
    &RamTst_ParityBitBckGrdTst,
    #endif

    #if(RAMTST_MEDIUM_COVERAGE_TEST_SELECTED == STD_ON)
    &RamTst_PatternChkBckGrdTst,
    #endif

    #if(RAMTST_HIGH_COVERAGE_TEST_SELECTED == STD_ON)
    &RamTst_CrcBckGrdTst
    #endif
  };

  SchM_Enter_RamTst_RAM_PROTECTION();
  if(RAMTST_EXECUTION_ALLOWED == RamTst_GddExecuStatus)
  {
    SchM_Exit_RamTst_RAM_PROTECTION();
    
    LucParaId = RamTst_GddNewAlgParamsId - RAMTST_ONE;
    if (LucParaId < RamTst_GucNumberOfAlgParaSets)
    {
      /* A background test is performed by the scheduler periodically calling the 
       * RamTst_MainFunction() to test a RamTstNumberOfTestedCells of memory using the 
       * selected algorithm
       * RamTst_GddNumOfTstCells = RamTst_GaaAlgParam[n].ulRamTstNumberOfTestedCells; */

      /* ddBalNumOfCells = RamTst_GaaBlkParam[LddBlkIndex].ulRamBlockSize
       * ulRamBlockSize = (ulRamTstEndAddress - ulRamTstStartAddress)/Ram Cell Size */
      if(RamTst_GddNumOfTstCells <= RamTst_GddBckGrdTstRamVar.ddBalNumOfCells)
      {
        if(RamTst_GddNewAlgType == RAMTST_ALGORITHM_UNDEFINED)
        {
           LddBlkIndex = RamTst_GaaAlgParam[LucParaId].usRamTstBlkIndex;
          /* UNDEFINED ALGORITHM IGNORE THE BLOCK */
          *(RamTst_GaaBlkParam[LddBlkIndex].pTestBlockStatus) =
                                                    RAMTST_RESULT_NOT_TESTED;
        }
        else
        {
          /* polyspace +2  MISRA-C3:10.4 [Justified:Low] "Not a defect" */
          (void) (*pRamTstAlgBckGrdTst[(uint8)RamTst_GddNewAlgType - RAMTST_ONE])
           (RamTst_GddBckGrdTstRamVar.ulBckGrdAddress, RamTst_GddNumOfTstCells);
        }

        /* Balance Cells of the Block to be tested in next mainfunction */
        RamTst_GddBckGrdTstRamVar.ddBalNumOfCells =
            RamTst_GddBckGrdTstRamVar.ddBalNumOfCells - RamTst_GddNumOfTstCells;

        /* A block is completed */
        if(RamTst_GddBckGrdTstRamVar.ddBalNumOfCells == RAMTST_ZERO)
        {
          RamTst_SetBlockResult();
          /* Number of Blocks configured for Algorithm */
          LusNumberOfBlock = RamTst_GaaAlgParam[LucParaId].usRamTstNumberOfBlocks;
            /* Block Index */
          LddBlkIndex = RamTst_GaaAlgParam[LucParaId].usRamTstBlkIndex;
          /* Block Index */
          LusBlkID = RamTst_GaaBlkParam[LddBlkIndex].usRamTstBlockId;

          /* RamTst_GddBckGrdTstRamVar.ddRunningBlockID =
                                RamTst_GaaBlkParam[LddBlkIndex].usRamTstBlockId; */
          /* Check if it Last Block */
          if(RamTst_GddBckGrdTstRamVar.ddRunningBlockID >=
            (LusBlkID + (LusNumberOfBlock - RAMTST_ONE)))
          {
            RamTst_SetOverAllResult(LusBlkID);
          }
          else
          {
            /* Next Block */
            RamTst_GddBckGrdTstRamVar.ddRunningBlockID++;
            LusBlkID = RamTst_GddBckGrdTstRamVar.ddRunningBlockID-RAMTST_ONE;
            if (LusBlkID < RamTst_GulNumberOfBlocks)
            {
              /* Next Block size */
              RamTst_GddBckGrdTstRamVar.ddBalNumOfCells = RamTst_GaaBlkParam[LusBlkID].ulRamBlockSize;
              RamTst_GddBckGrdTstRamVar.ulBckGrdAddress = RamTst_GaaBlkParam[LusBlkID].ulRamTstStartAddress;
              *(RamTst_GaaBlkParam[LusBlkID].pTestBlockStatus) = RAMTST_RESULT_UNDEFINED;              
            }
          }
        }        
      }
      else /* RamTst_GddNumOfTstCells > RamTst_GddBalNumOfCells */
      {
        /* A background test is performed by the scheduler periodically calling the 
         * RamTst_MainFunction() to test a RamTstNumberOfTestedCells of memory using the 
         * selected algorithm
         * RamTst_GddNumOfTstCells = RamTst_GaaAlgParam[n].ulRamTstNumberOfTestedCells; */
       
        /* ddBalNumOfCells = RamTst_GaaBlkParam[LddBlkIndex].ulRamBlockSize
         * ulRamBlockSize = (ulRamTstEndAddress - ulRamTstStartAddress)/Ram Cell Size */      
        LddMaxNumOfCellsPerMF = RamTst_GddNumOfTstCells;
        LddCurrNumOfCells = RamTst_GddBckGrdTstRamVar.ddBalNumOfCells;

        while(LddMaxNumOfCellsPerMF != RAMTST_ZERO)
        {
          if(RamTst_GddNewAlgType == RAMTST_ALGORITHM_UNDEFINED)
          {
            LddBlkIndex = RamTst_GaaAlgParam[LucParaId].usRamTstBlkIndex;
            /* UNDEFINED ALGORITHM IGNORE THE BLOCK */
            *(RamTst_GaaBlkParam[LddBlkIndex].pTestBlockStatus) =
                                                      RAMTST_RESULT_NOT_TESTED;
          }
          else
          {
            /* polyspace +2 MISRA-C3:10.4 [Justified:Low] "Not a defect" */
            (void) (*pRamTstAlgBckGrdTst[(uint8)RamTst_GddNewAlgType - RAMTST_ONE])
                 (RamTst_GddBckGrdTstRamVar.ulBckGrdAddress, LddCurrNumOfCells);
          }

          LddMaxNumOfCellsPerMF = LddMaxNumOfCellsPerMF - LddCurrNumOfCells;
          RamTst_GddBckGrdTstRamVar.ddBalNumOfCells =
                  RamTst_GddBckGrdTstRamVar.ddBalNumOfCells - LddCurrNumOfCells;

          /* A block is completed */                  
          if(RamTst_GddBckGrdTstRamVar.ddBalNumOfCells == RAMTST_ZERO)
          {
            RamTst_SetBlockResult();
            /* Number of Blocks configured for Algorithm */
            LusNumberOfBlock = RamTst_GaaAlgParam
                 [LucParaId].usRamTstNumberOfBlocks;
            LddBlkIndex = RamTst_GaaAlgParam[LucParaId].usRamTstBlkIndex;
            /* Block Index */
            LusBlkID = RamTst_GaaBlkParam[LddBlkIndex].usRamTstBlockId;
            /* Check if it Last Block */
            if(RamTst_GddBckGrdTstRamVar.ddRunningBlockID >=
              (LusBlkID + (LusNumberOfBlock - RAMTST_ONE)))
            {
              RamTst_SetOverAllResult(LusBlkID);
              /* Exit the Loop and Start from 1st Block from Next Mainfunction*/
              break;
            }
            
            /* Next Block */
            RamTst_GddBckGrdTstRamVar.ddRunningBlockID++;

            LusRunBlkID= RamTst_GddBckGrdTstRamVar.ddRunningBlockID-RAMTST_ONE;
            if (LusRunBlkID < RamTst_GulNumberOfBlocks)
            {
              /* Next Block Cells */
              RamTst_GddBckGrdTstRamVar.ddBalNumOfCells = RamTst_GaaBlkParam[LusRunBlkID].ulRamBlockSize;
              RamTst_GddBckGrdTstRamVar.ulBckGrdAddress = RamTst_GaaBlkParam[LusRunBlkID].ulRamTstStartAddress;
              *(RamTst_GaaBlkParam[LusRunBlkID].pTestBlockStatus) = RAMTST_RESULT_UNDEFINED;              
              LddCurrNumOfCells = (RamTst_GddBckGrdTstRamVar.ddBalNumOfCells >= LddMaxNumOfCellsPerMF) ? 
                  LddMaxNumOfCellsPerMF : RamTst_GddBckGrdTstRamVar.ddBalNumOfCells;                  
            }
            else
            {
              RAMTST_REPORT_ERROR(RAMTST_MAINFUNCTION_SID, RAMTST_E_STATUS_FAILURE);
            }
          }
          
                                    
        } /* End of while(LddCurrNumOfCells != RAMTST_ZERO) */
      }
    }
    else
    {
      RAMTST_REPORT_ERROR(RAMTST_MAINFUNCTION_SID, RAMTST_E_STATUS_FAILURE);
    }
    
    #if((RAMTST_STOP_API == STD_ON) || (RAMTST_SUSPEND_API == STD_ON))
    SchM_Enter_RamTst_RAM_PROTECTION();
    #endif
    
    #if(RAMTST_STOP_API == STD_ON)
    if (RAMTST_BGEXE_TRYING_STOP == RamTst_TriggerStopOrSuspend)
    {
      SchM_Exit_RamTst_RAM_PROTECTION();

      LucParaId = RamTst_GddNewAlgParamsId - RAMTST_ONE;
      if (LucParaId < RamTst_GucNumberOfAlgParaSets) /* always true */
      {
        LddBlkIndex = RamTst_GaaAlgParam[LucParaId].usRamTstBlkIndex;

        /* Starting Block ID used for BackGround Testing */
        RamTst_GddBckGrdTstRamVar.ddRunningBlockID =
                                RamTst_GaaBlkParam[LddBlkIndex].usRamTstBlockId;
        /* Starting Address for BackGround Testing */
        RamTst_GddBckGrdTstRamVar.ulBckGrdAddress =
                           RamTst_GaaBlkParam[LddBlkIndex].ulRamTstStartAddress;
        /* Size of the Block To be Tested in background testing */
        RamTst_GddBckGrdTstRamVar.ddBalNumOfCells =
                                 RamTst_GaaBlkParam[LddBlkIndex].ulRamBlockSize;
        /* Error Flag Set to False */
        RamTst_GddBckGrdTstRamVar.blGblBckGrdTstError = RAMTST_PASSED;

        /* Error Flag Set to False */
        RamTst_GddBckGrdTstRamVar.blBlkBckGrdTstError = RAMTST_PASSED;
        #if(RAMTST_HIGH_COVERAGE_TEST_SELECTED == STD_ON)

        #if(RAMTST_CRC_8_SUPPORT == STD_ON)
        RamTst_GddBckGrdTstRamVar.ucCrcInitialVal = RAMTST_CRC_INITIAL_VALUE8;
        #endif

        #if(RAMTST_CRC_8H2F_SUPPORT == STD_ON)
        RamTst_GddBckGrdTstRamVar.ucCrcInitialVal 
                                               = RAMTST_CRC_INITIAL_VALUE8H2F;
        #endif

        #if(RAMTST_CRC_16_SUPPORT == STD_ON)
        RamTst_GddBckGrdTstRamVar.usCrcInitialVal = RAMTST_CRC_INITIAL_VALUE16;
        #endif

        #if(RAMTST_CRC_32_SUPPORT == STD_ON)
        RamTst_GddBckGrdTstRamVar.ulCrcInitialVal = RAMTST_CRC_INITIAL_VALUE32;
        #endif

        #endif
      }
      
      SchM_Enter_RamTst_RAM_PROTECTION();
      RamTst_GddExecuStatus = RAMTST_EXECUTION_STOPPED;
      RamTst_TriggerStopOrSuspend = RAMTST_BGEXE_DONE;
      SchM_Exit_RamTst_RAM_PROTECTION();   

      BswM_RequestMode((BswM_UserType)RAMTST_MODULE_ID,
                       (BswM_ModeType)RAMTST_LOWPOWER_ALLOW);      
    }
    else
    #endif
    
    #if(RAMTST_SUSPEND_API == STD_ON)        
    if (RAMTST_BGEXE_TRYING_SUSPEND == RamTst_TriggerStopOrSuspend)
    {
      RamTst_GddExecuStatus = RAMTST_EXECUTION_SUSPENDED;
      RamTst_TriggerStopOrSuspend = RAMTST_BGEXE_DONE;
      SchM_Exit_RamTst_RAM_PROTECTION();
    }
    else
    #endif
    
    {
      #if((RAMTST_STOP_API == STD_ON) || (RAMTST_SUSPEND_API == STD_ON))
      SchM_Exit_RamTst_RAM_PROTECTION();
      #endif
    }    
  } /* End Of if(RamTst_GddExecuStatus == RAMTST_EXECUTION_RUNNING) */
  else
  {
    SchM_Exit_RamTst_RAM_PROTECTION();
  }
}

#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end VARIABLE:ALL [Not a defect:Low] "Not a defect" */
/* polyspace-end RTE:UNR [Not a defect:Low] "Not a defect" */
/* polyspace-end RTE:IDP [Not a defect:Low] "Not a defect" */
/* polyspace-end RTE:NIV [Not a defect:Low] "Not a defect" */
/* polyspace-end RTE:OBAI [Not a defect:Low] "Not a defect" */
/* polyspace-end MISRA-C3:20.1 [Not a defect:Low] "It is implemented according to autosar specification" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
