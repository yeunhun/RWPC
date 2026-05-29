/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE:  Dcm_DsdInternal.c                                            **
**                                                                            **
**  TARGET    :  All                                                          **
**                                                                            **
**  PRODUCT    :  AUTOSAR  Diagnostic Communication Manager Module            **
**                                                                            **
**  PURPOSE    :  This  file  contains  the  internal  functions  definitions **
**                for  DSD layer  of  Dcm  module                             **
**                                                                            **
**  PLATFORM  DEPENDANT  [yes/no]:  no                                        **
**                                                                            **
**  TO  BE  CHANGED  BY  USER  [yes/no]:  no                                  **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision  History                                     **
********************************************************************************
** Revision  Date         By              Description                         **
********************************************************************************
** 2.3.2.0   05-Nov-2020   EunKyung Kim   #26432                              **
**                                                                            **
** 1.0.19    02-28-2020  EunKyung Kim     #21905                              **
**                                                                            **
** 1.0.18    09-04-2019   Y.S     Jeon    #16582                              **
**                                                                            **
** 1.0.17    29-01-2019   Y.S     Jeon    #15566                              **
**                                                                            **
** 1.0.16    09-11-2018   Y.S     Jeon    #13923                              **
**                                                                            **
** 1.0.15    12-09-2018   Y.S     Jeon    #13457                              **
**                                                                            **
** 1.0.14    01-06-2018   Y.S     Jeon    #11159                              **
**                                                                            **
** 1.0.13    10-11-2017   YoungJin Yun    #10534                              **
**                                                                            **
** 1.0.12    08-06-2017   Jin     Jung    #7008                               **
**                                                                            **
** 1.0.11    25-05-2017   Jin     Jung    #8656                               **
**                                                                            **
** 1.0.10    28-03-2017   Jin     Jung    #4718                               **
**                                                                            **
** 1.0.9     28-10-2016   Jin     Jung    #5535                               **
**                                                                            **
** 1.0.8     05-07-2016   Jin     Jung    #3581, #5397, #5401, #5436          **
**                                                                            **
** 1.0.7     02-06-2016   Jin     Jung    #5097                               **
**                                                                            **
** 1.0.6     25-05-2016   Sungeol Baek    #5006                               **
**                                                                            **
** 1.0.5     03-03-2016   Sungeol Baek    #3750, #4148, #4267, RTRT reflection**
**                                                                            **
** 1.0.4     18-11-2015   YoungJin Yun    #3492                               **
**                                                                            **
** 1.0.3     19-06-2015   YoungJin Yun    #2171                               **
**                                                                            **
** 1.0.2     16-04-2015   Sungeol Baek    #2171                               **
**                                                                            **
** 1.0.1     24-05-2015   Sungeol Baek    #2370                               **
**                                                                            **
** 1.0.0     09-01-2013   Autron          Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include  Section                                      **
*******************************************************************************/
#include  "Dcm.h"
#include  "Dcm_Ram.h"
#include  "Dem.h"

#if(DCM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#include  "Rte_Dcm.h"
#include  "ComM_Dcm.h"
#include  "SchM_Dcm.h"
#include  "Dcm_DspMain.h"
#include  "Dcm_Dsl.h"
#include  "PduR_Dcm.h"
#include "Dcm_DspServices.h"
#include "Dcm_DspMemoryServices.h"
#include  "Dcm_DsdInternal.h"
#if(DCM_ROUTINECONTROL_SERVICE == STD_ON)
#include "Dcm_Routine.h"
#endif
#if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
#include "Dcm_DspResponseOnEvent.h"
#endif
#include "Dcm_Config.h"
#include "Dcm_Lib.h"

/* polyspace-begin MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:10.4 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:20.7 [Justify with annotations:Low] "Not a defect" */
/* polyspace-begin DEFECT:OUT_BOUND_PTR [Justified:Low] "Not a defect" */
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Nesting of control structures to achieve better throughput. */
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
/* polyspace:begin<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > pointer is not null */
/* polyspace:begin<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */
/* polyspace:begin<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-begin CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */

/*******************************************************************************
**                      Global  Data  Types                                   **
*******************************************************************************/

/*******************************************************************************
**                      Function  Definitions                                 **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

static FUNC(boolean, DCM_CODE) Dcm_DsdPostValidation
  (uint8 LucSID, uint8 LucSubFunction);

static FUNC(boolean, DCM_CODE) Dcm_DsdServiceValidation
  (uint8 LucSID);

static FUNC(boolean, DCM_CODE) Dcm_DsdSubServiceValidation(
  P2CONST(Dcm_ServiceIdConfigType,  AUTOMATIC,  DCM_APPL_CONST)LpSIDTAB,
  uint8 LucSubFunction);

static boolean  Dcm_DsdValidateSubServiceId(
  P2CONST(Dcm_SubServiceIdConfigType,  AUTOMATIC,  DCM_APPL_CONST) aCfgSubService, 
  uint8  aMaxSubSrv,  
  uint8  aSubSrvID,
  P2VAR(uint8,  AUTOMATIC,  DCM_APPL_DATA) aSubSrvIndex );

static FUNC(void,  DCM_CODE)  
Dcm_DsdInternal_SetMsgContext(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  PduIdType DcmRxPduId,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) RxDataBufferPtr,
  boolean SubFunctionExist);

static FUNC(boolean, DCM_CODE) Dcm_DsdReqManufacCallback(
   P2VAR(uint8,  AUTOMATIC,  DCM_APPL_DATA)  LpRxBufferId,
   PduIdType LddRxPduId, Dcm_MsgLenType LddresDataLen,
   P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA)\
    LddNegativeResponseCode);
    
static FUNC(boolean, DCM_CODE) Dcm_DsdReqSupplCallback(
   P2VAR(uint8,  AUTOMATIC,  DCM_APPL_DATA)  LpRxBufferId,
   PduIdType LddRxPduId, Dcm_MsgLenType LddresDataLen,
   P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA)\
    LddNegativeResponseCode);
    
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
**  Function  Name     :  Dcm_DsdSIdIndex                                     **
**                                                                            **
**  Service  ID        :  NA                                                  **
**                                                                            **
**  Description        :  This  function  will  give  the  index  of  the     **
**                        requested  Service  Id  in  the  array  of  Service **
**                        Id  parameter structure                             **
**                                                                            **
** Sync/Async          : Synchronous                                          **
**                                                                            **
**  Re-entrancy        :  Non-Reentrant                                       **
**                                                                            **
**  Input  Parameters  :  ServiceId                                           **
**                                                                            **
** InOut parameter     : None                                                 **
**                                                                            **
**  Output  Parameters :  uint8                                               **
**                                                                            **
**  Return  parameter  :  None                                                **
**                                                                            **
**  Preconditions      :  None                                                **
**                                                                            **
**  Remarks            :  Global  Variable(s)  :  Dcm_GaaProtocolConfig       **
**                        Dcm_GddProtocolId                                   **
**                        Function(s)  invoked  :  Dcm_GetProtocolIDIndex     **
**                                                                            **
*******************************************************************************/
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_START_SEC_CODE
#include "MemMap.h"
/* polyspace<MISRA-C:8.10:Not a defect:Justify with annotations> Whether the Dcm api function is required internal or external linkage, depends on user configuration */
FUNC(uint8, DCM_CODE)  Dcm_DsdSIdIndex(uint8  aServiceID)
{
  uint8  iProtocolTable;
  uint8  sidTableIndex = DCM_SERVICE_NOT_CONFIGURED;

  iProtocolTable = Dcm_GetProtocolIDIndex(Dcm_GddProtocolId);

  /*  Check  is  service  Id  configured  in  the  service  Id  table  */
  if (iProtocolTable  < Dcm_Num_Of_ProtocolConfig)
  {
    P2CONST(Dcm_ProtocolConfig,  AUTOMATIC,  DCM_APPL_CONST) cfgProtocol;
    P2CONST(Dcm_ServiceIdConfigType,  AUTOMATIC,  DCM_APPL_CONST) cfgSidTable;

    cfgProtocol = &Dcm_GaaProtocolConfig[iProtocolTable];
    cfgSidTable = cfgProtocol->pServiceIdTable;
  
    if (cfgSidTable != NULL_PTR)  
    {
      uint8 iServiceID;
      
      for (iServiceID  =  0; iServiceID < cfgProtocol->ucServiceCount; iServiceID++)
      {
        if (cfgSidTable[iServiceID].ucServiceId == aServiceID)
        {
          sidTableIndex = iServiceID;

          /* if the configured dcm have the multiple protocol,
           * Index of Dcm_GaaSIdConfig shall be calculated 
           * according to the ucServiceCountof  Dcm_GaaProtocolConfig 
           
                             |--------------------------|---------------------------|
                             |       protocol 0         |          protocol 1       |
                             |--------------------------|---------------------------|
           Dcm_GaaSIdConfig  | &Dcm_GaaSIdConfig[0]     |   &Dcm_GaaSIdConfig[19]   |
                             |--------------------------|---------------------------|
           Num of service    |        19                |          10               |
                             |--------------------------|---------------------------|

           Protocol 1's SID index = 19 + nth
           */
          #if (DCM_NUM_OF_PROTOCOLCONFIG > 1U)
          {
              uint8 iteratorProtocol = 0U;
              for(; iteratorProtocol < iProtocolTable; iteratorProtocol++)
              {
                sidTableIndex += Dcm_GaaProtocolConfig[iteratorProtocol].ucServiceCount;
              }
          }
          #endif
          break;
        }
      }
    }
  }

  /*  Return  the  index  of  the  Service  Id  in  the  Service  Id  table  */
  return sidTableIndex;
}

/*******************************************************************************
**  Function  Name        : Dcm_DsdModeConditionCheck                         **
**                                                                            **
**  Service  ID           : NA                                                **
**                                                                            **
**  Description           : This  function  validates the mode condition.     **
**                                                                            **
** Sync/Async             : Synchronous                                       **
**                                                                            **
**  Re-entrancy           : Non-Reentrant                                     **
**                                                                            **
**  Input  Parameters     : LucModeRuleIndex                                  **
**                                                                            **
** InOut parameter        : None                                              **
**                                                                            **
**  Output  Parameters    : None                                              **
**                                                                            **
**  Return  parameter     : boolean                                           **
**                                                                            **
**  Preconditions         : None                                              **
**                                                                            **
**  Remarks               : Global  Variable(s)  :Dcm_GddNegRespError ,       **
**                          Dcm_GaaModeRuleConfig , Dcm_GddNegRespError       **
**                          Dcm_GaaModeConditionIndexArray                    **
**                          Function(s)  invoked  : None                      **
**                                                                            **
*******************************************************************************/
#if(DCM_MODE_CONDITION  ==  STD_ON)
/* polyspace-begin MISRA-C3:10.1 [Justified:Unset] "Not a defect" */
boolean  Dcm_DsdModeConditionCheck(uint8  LucModeRuleIndex)
{
  uint8  LucModeCondition;
  uint8  LucMode;
  uint8  LucCount;
  uint8 LucCurrentMode;
  uint8 LucLogicalOperator;
  uint8 LaaCurArgumentStatus[DCM_MAXVALUE];
  boolean  LblArgumentStatus;
  boolean LblArgumentStatus1;
  boolean LblBreakLoop;

  LblArgumentStatus  =  DCM_TRUE;
  LblArgumentStatus1 = DCM_FALSE;
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  LblBreakLoop = DCM_FALSE;

  /* Loop to get current mode out of configured mode conditions */
  for ( 
    LucCount  =  DCM_ZERO;  
    ((LucCount  < Dcm_GaaModeRuleConfig[LucModeRuleIndex].ucDcmNoOfModeCondnArg) && (LblBreakLoop == DCM_FALSE));  
    LucCount++)
  {
    if(Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE)
    {
      uint8 indexArray = 
        Dcm_GaaModeConditionIndexArray[Dcm_GaaModeRuleConfig[LucModeRuleIndex].ucIndexOfModeConditionIndexArray + LucCount];
      
      /* Get mode condition type*/
      LucModeCondition  =  Dcm_GaaModeConditionConfig[indexArray].ucConditionType;
      /* Get Configured mode */
      LucMode  =  Dcm_GaaModeConditionConfig[indexArray].ucBsworSwcMode;

      /* For Misra-C Check */
      if (NULL_PTR == Dcm_GaaModeConditionConfig[Dcm_GaaModeConditionIndexArray[indexArray]].pGetCurrentMode)
      {
        /* Never be reached . pGetCurrentMode is checeked by generator */
        Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
        LblBreakLoop = DCM_TRUE;
      }
      else
      {      
        /* Invoke function to get current Mode */
        LucCurrentMode = Dcm_GaaModeConditionConfig[Dcm_GaaModeConditionIndexArray[indexArray]].pGetCurrentMode();
        if(LucModeCondition  ==  DCM_EQUALS)
        {
          /* Check current mode and configured mode is same or not */
          if(LucCurrentMode  ==  LucMode)
          {
            LaaCurArgumentStatus[LucCount]  =  DCM_TRUE;
          }
          else
          {
            LaaCurArgumentStatus[LucCount]  =  DCM_FALSE;
            LblBreakLoop = DCM_TRUE;
          }
        }
        else
        {
          /* Check current mode and configured mode is same or not */
          if(LucCurrentMode  !=  LucMode)
          {
            LaaCurArgumentStatus[LucCount]  =  DCM_TRUE;

          }
          else
          {
            LaaCurArgumentStatus[LucCount]  =  DCM_FALSE;
            LblBreakLoop = DCM_TRUE;
          }
        }

        LucLogicalOperator  = Dcm_GaaModeRuleConfig[LucModeRuleIndex].ucLogicalOperator;
        if(LucLogicalOperator  ==  DCM_AND)
        {
          LaaCurArgumentStatus[LucCount] = (uint8)((LblArgumentStatus) && (LaaCurArgumentStatus[LucCount]));
          LblArgumentStatus  = LaaCurArgumentStatus[LucCount];
          
          if(LaaCurArgumentStatus[LucCount]  ==  DCM_ZERO)
          {
            /*  Update  the  configured  NRC  Value  */
            #if(DCM_DSP_MODE_RULE_NRC == STD_ON)
            Dcm_GddNegRespError  = Dcm_GaaModeRuleConfig[LucModeRuleIndex].ucNRCType;
            #else
            Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
            #endif

            /* To break loop */
            LblBreakLoop = DCM_TRUE;
          }
        }
        else
        {
          LaaCurArgumentStatus[LucCount] = (uint8)((LblArgumentStatus1) || (LaaCurArgumentStatus[LucCount]));
          LblArgumentStatus1  =  LaaCurArgumentStatus[LucCount];
          LblArgumentStatus = LblArgumentStatus1;
          
          if(LaaCurArgumentStatus[LucCount]  ==  DCM_ZERO)
          {
            /*  Update  the  configured  NRC  Value  */
            #if(DCM_DSP_MODE_RULE_NRC == STD_ON)
            Dcm_GddNegRespError  = Dcm_GaaModeRuleConfig[LucModeRuleIndex].ucNRCType;
            #else
            Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
            #endif
            /* To break loop */
            LblBreakLoop = DCM_TRUE;
          }
        }
      }
    }
    else
    {
      /* Break the loop */
      LblBreakLoop = DCM_TRUE;
    }
  }
  return  LblArgumentStatus;
}
/* polyspace-end MISRA-C3:10.1 [Justified:Unset] "Not a defect" */
#endif

/*******************************************************************************
**  Function  Name        : Dcm_DsdModeRuleCheck                              **
**                                                                            **
**  Service  ID           : NA                                                **
**                                                                            **
**  Description           : This  function  to  validates  mode rule.         **
**                                                                            **
** Sync/Async             : Synchronous                                       **
**                                                                            **
**  Re-entrancy           : Non-Reentrant                                     **
**                                                                            **
**  Input  Parameters     : LucModeRuleIndex                                  **
**                                                                            **
** InOut parameter        : None                                              **
**                                                                            **
**  Output  Parameters    : None                                              **
**                                                                            **
**  Return  parameter     : boolean                                           **
**                                                                            **
**  Preconditions         : None                                              **
**                                                                            **
**  Remarks               : Global  Variable(s)  :  Dcm_GaaModeRuleConfig ,   **
**                          Dcm_GddNegRespError                               **
**                          Function(s)  invoked  :                           **
**                          Dcm_DsdModeRuleCheck,Dcm_DsdModeConditionCheck    **
**                                                                            **
*******************************************************************************/
#if(DCM_MODE_RULE == STD_ON)
/* polyspace-begin MISRA-C3:10.1 [Justified:Unset] "Not a defect" */
boolean  Dcm_DsdModeRuleCheck(Dcm_ModeType  LucModeRuleIndex)
{

  uint8 LucCount;
  uint8 LucLogicalOperator;
  #if(DCM_MODE_RULE_INDEX == STD_OFF)
  uint8 LucArgModeRuleIndex;
  #endif
  uint8 LucModeIndex;
  boolean  LblModeRuleArgumentStatus;
  boolean LblModeRuleArgumentStatus1;
  boolean  LblModeConditionArgumentStatus;
  boolean LaaModeRuleSuccess[DCM_MAXVALUE];

  LblModeRuleArgumentStatus = DCM_TRUE;
  LblModeRuleArgumentStatus1 = DCM_FALSE;
  #if(DCM_MODE_RULE_INDEX == STD_OFF)
  LblModeConditionArgumentStatus = DCM_TRUE;
  #endif
  LaaModeRuleSuccess[DCM_ZERO] = DCM_ONE;
  LucModeIndex = DCM_ZERO;
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  LucLogicalOperator  =
    Dcm_GaaModeRuleConfig[LucModeRuleIndex].ucLogicalOperator;

  if(LucLogicalOperator == DCM_AND)
  {
    LaaModeRuleSuccess[DCM_ZERO] = DCM_ONE;
  }
  else
  {
    LaaModeRuleSuccess[DCM_ZERO] = DCM_ZERO;
  }

  for(LucCount  =  DCM_ZERO;
    LucCount  <  (Dcm_GaaModeRuleConfig[LucModeRuleIndex].
      ucDcmNoOfModeRuleArg + DCM_ONE); LucCount++)
  {
    if(Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE)
    {
      #if(DCM_MODE_RULE_INDEX == STD_OFF)
      if(Dcm_GaaModeRuleConfig[LucModeRuleIndex].ucDcmNoOfModeRuleArg !=
        DCM_ZERO)
      {
        if(LucCount != DCM_ZERO)
        {
          LucCount--;
        }

        LucArgModeRuleIndex  =
          Dcm_GaaModeRuleIndexArray[(Dcm_GaaModeRuleConfig[LucModeRuleIndex].
          ucIndexOfModeRuleIndexArray + LucCount)];
        LaaModeRuleSuccess[LucModeIndex] =
          Dcm_DsdModeRuleCheck(LucArgModeRuleIndex);
        LucCount++;
      }
      #endif
      #if(DCM_MODE_RULE_INDEX == STD_OFF)
      if(Dcm_GaaModeRuleConfig[LucModeRuleIndex].ucDcmNoOfModeCondnArg !=
        DCM_ZERO)
       #endif
      {
        LblModeConditionArgumentStatus = Dcm_DsdModeConditionCheck(LucModeRuleIndex);
      }
      if(LucLogicalOperator  ==  DCM_AND)
      {
        LaaModeRuleSuccess[LucModeIndex] = (boolean)((LblModeConditionArgumentStatus &&
          LblModeRuleArgumentStatus) && (LaaModeRuleSuccess[LucModeIndex]));
        if(LaaModeRuleSuccess[LucModeIndex]  ==  DCM_ZERO)
        {
          /*  Update  the  configured  NRC  Value  */
          #if(DCM_DSP_MODE_RULE_NRC == STD_ON)
          Dcm_GddNegRespError  =
            Dcm_GaaModeRuleConfig[LucModeRuleIndex].ucNRCType;
          #else
           Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
          #endif

          /* MISRA Rule        : 13.6
            Message            : Control variable, LucCount,
                                 modified in body of loop
            Reason             : Once the search element found, control
                                 exiting from the for loop to terminate
                                 next iteration.
            Verification       : However, part of the code
                                 is verified manually and
                                 it is not having any impact.
          */
          /* To break loop */
          LucCount  =  Dcm_GaaModeRuleConfig[LucModeRuleIndex].
            ucDcmNoOfModeRuleArg + DCM_ONE;
        }
        LblModeRuleArgumentStatus = LaaModeRuleSuccess[LucModeIndex];
      }
      else
      {
        LaaModeRuleSuccess[LucModeIndex] = (boolean)((LblModeConditionArgumentStatus ||
          LblModeRuleArgumentStatus1) || (LaaModeRuleSuccess[LucModeIndex]));
        if(LaaModeRuleSuccess[LucModeIndex]  ==  DCM_ZERO)
        {
          /*  Update  the  configured  NRC  Value  */
          #if(DCM_DSP_MODE_RULE_NRC == STD_ON)
          Dcm_GddNegRespError  =
            Dcm_GaaModeRuleConfig[LucModeRuleIndex].ucNRCType;
          #else
           Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
          #endif
          /* MISRA Rule        : 13.6
            Message            : Control variable, LucCount,
                                 modified in body of loop
            Reason             : Once the search element found, control
                                 exiting from the for loop to terminate
                                 next iteration.
            Verification       : However, part of the code
                                 is verified manually and
                                 it is not having any impact.
          */
          /* To break loop */
          LucCount  =  Dcm_GaaModeRuleConfig[LucModeRuleIndex].
            ucDcmNoOfModeRuleArg + DCM_ONE;
        }
        LblModeRuleArgumentStatus1 = LaaModeRuleSuccess[LucModeIndex];
        LblModeRuleArgumentStatus = LblModeRuleArgumentStatus1;
      }

    }
    else
    {
      /* MISRA Rule        : 13.6
        Message            : Control variable, LucCount,
                             modified in body of loop
        Reason             : Once the search element found, control
                             exiting from the for loop to terminate
                             next iteration.
        Verification       : However, part of the code
                             is verified manually and
                             it is not having any impact.
      */
      /* Break the loop */
      LucCount  =  Dcm_GaaModeRuleConfig[LucModeRuleIndex].
      ucDcmNoOfModeRuleArg + DCM_ONE;
    }
    LucModeIndex++;
  }

  return  LblModeRuleArgumentStatus;
}
/* polyspace-end MISRA-C3:10.1 [Justified:Unset] "Not a defect" */
#endif

/*******************************************************************************
**  Function  Name       : Dcm_DsdInternal_SetMsgContext                      **
**                                                                            **
**  Service  ID          : NA                                                 **
**                                                                            **
**  Description          : This  function  will  give  the  indication  to    **
**                         the  DSD layer  on  the  arrival  of  the          **
**                         new  request.                                      **
**                                                                            **
** Sync/Async            : Synchronous                                        **
**                                                                            **
**  Re-entrancy          : Non-Reentrant                                      **
**                                                                            **
**  Input  Parameters    : DcmRxPduId RxDataBufferPtr,SubFunctionExist        **
**                                                                            **
** InOut parameter       : pMsgContext                                        **
**                                                                            **
**  Output  Parameters   : None                                               **
**                                                                            **
**  Return  parameter    : void                                               **
**                                                                            **
**  Preconditions        : None                                               **
**                                                                            **
**  Remarks              :                                                    **
*******************************************************************************/
static FUNC(void,  DCM_CODE)  
Dcm_DsdInternal_SetMsgContext(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  PduIdType DcmRxPduId,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) RxDataBufferPtr,
  boolean SubFunctionExist)
{
  P2CONST(Dcm_PduIdTable,  AUTOMATIC,  DCM_APPL_CONST) rxPduCfg;

  if ((NULL_PTR == pMsgContext) || (NULL_PTR == RxDataBufferPtr) || (DcmRxPduId >= Dcm_Num_Of_PduidTableConfig))
  {
    /* TODO : DET ERROR */
  }
  else
  {
    rxPduCfg = &Dcm_GaaPduIdTableConfig[DcmRxPduId];

    /* Update the parameters of the MsgContext Structure  */
    pMsgContext->idContext = (Dcm_IdContextType)(RxDataBufferPtr[DCM_ZERO]  |  DCM_RESPONSE_ID); /* SID */
    pMsgContext->reqData = &RxDataBufferPtr[1U];
    
    pMsgContext->dcmRxPduId  =  DcmRxPduId;
    /*
     *  Check  if  the  Suppress  positive  bit  is  set  and  Sub
     *  function  is  available  for  the  requested  service  Id
     */
    if(Dcm_GddProtocolId != 0U)
    {
      #if (DCM_STANDARD_SUPPORT == DCM_ES95486_SUPPORT)
      Std_ReturnType ret = E_NOT_OK;
      
      ret = Dcm_ChkSuppressPosResponse(RxDataBufferPtr, pMsgContext->reqDataLen);
      
      if(ret == E_OK)
      {
        pMsgContext->msgAddInfo.suppressPosResponse = DCM_TRUE;
      }
      else
      #endif
      {
        if(((pMsgContext->reqData[0U] & DCM_SUPRESSBIT_MASK) == DCM_SUPRESSBIT_MASK) &&
          (SubFunctionExist == DCM_TRUE))
        {
          pMsgContext->msgAddInfo.suppressPosResponse =  DCM_TRUE;
          pMsgContext->reqData[0U] = pMsgContext->reqData[0U] & DCM_SUBFUNCTION_MASK;
        }
        else
        {
          pMsgContext->msgAddInfo.suppressPosResponse = DCM_FALSE;
        }
      }
    }
    else
    {
      pMsgContext->msgAddInfo.suppressPosResponse = DCM_FALSE;
    }
    pMsgContext->msgAddInfo.reqType = rxPduCfg->ucRxAddrType;
  }
}

/*******************************************************************************
**  Function  Name       : Dcm_DsdIndication                                  **
**                                                                            **
**  Service  ID          : NA                                                 **
**                                                                            **
**  Description          : This  function  will  give  the  indication  to    **
**                         the  DSD layer  on  the  arrival  of  the          **
**                         new  request.                                      **
**                                                                            **
** Sync/Async            : Synchronous                                        **
**                                                                            **
**  Re-entrancy          : Non-Reentrant                                      **
**                                                                            **
**  Input  Parameters    : LddRxPduId,  LblStopProtocol                       **
**                                                                            **
** InOut parameter       : None                                               **
**                                                                            **
**  Output  Parameters   : None                                               **
**                                                                            **
**  Return  parameter    : boolean                                            **
**                                                                            **
**  Preconditions        : None                                               **
**                                                                            **
**  Remarks              : Global  Variable(s)  :  Dcm_GaaPduIdTableConfig    **
**                         Dcm_GddDcmTxPduId,  Dcm_GddDcmTxConfPduId,         **
**                         Dcm_GaaBufferConfig , Dcm_GucPeriodicRxPduId       **
**                                             Dcm_GaaSIdConfig,              **
**                         Dcm_GpMsgContext,  Dcm_GddProtocolId,              **
**                         Dcm_GddNegRespError , Dcm_GpPerMsgContext          **
**                         Dcm_TxRespStatus , Dcm_GaaDslPeriodicData          **
**                         Dcm_GaaCbkReqServices,  Dcm_GblNormalReq           **
**                         Dcm_GucPeriodicSID , Dcm_DspSerPgStatus            **
**                         Dcm_PrtclTxBufStatus,                              **
**                         Dcm_GblFaultDetcetionCounter                       **
**                         Function(s)  invoked  :  Dcm_DsdSIdIndex,          **
**                         Dcm_ExternalProcessingDone,                        **
**                         Dcm_ExternalSetNegResponse, Dcm_DsdPostValidation  **
**                         Dcm_DslTransmit,  Dcm_DslStatusReset               **
**                                                                            **
*******************************************************************************/
FUNC(boolean,  DCM_CODE)  Dcm_DsdIndication  (PduIdType  LddRxPduId,
  boolean  LblStopProtocol,  boolean  LblPerTransmission,
    boolean LblROETransmission)
{
  P2CONST(Dcm_PduIdTable,  AUTOMATIC,  DCM_APPL_CONST)LpPduIdTable;
  P2CONST(Dcm_ServiceIdConfigType,  AUTOMATIC,  DCM_APPL_CONST)LpSIDTAB;
  P2VAR(uint8,  AUTOMATIC,  DCM_APPL_DATA)  LpTxBufferId;
  P2VAR(uint8,  AUTOMATIC,  DCM_APPL_DATA)  LpRxBufferId;
  
  #if((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
  (DCM_PROTOCOL_TRANSTYPE2 == STD_ON))
  P2CONST(Dcm_DslRoeTrans, AUTOMATIC, DCM_PRIVATE_CONST)LpRoeTxId;
  #endif
  
  PduIdType  LddTxPduId;
  uint32 LulResBuffersize;
  uint16 LucIndex2;
  
  #if ( (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE  ==  STD_ON) &&\
        (DCM_PROTOCOL_TRANSTYPE2  ==  STD_ON) )
  uint16  LusIndex;
  uint8  LucDataStatus;
  #endif
  

  Dcm_NegativeResponseCodeType LddNegativeResponseCodeType;
  Dcm_MsgLenType LddresDataLen;

  uint8  LucProtocolIDIndex;
  uint8  LucSID;
  uint8  LucSIDIndex;
  uint8  LucRxBufferId;
  uint8  LucTxBufferId;
  uint8  LucreqType;
  uint8  LucSubFunction;

  boolean  LblSearchResult;
  boolean  LblErrorOccured;
  boolean  LblStatus = DCM_FALSE;

  /* Check if the pre compile option DCM_DEV_ERROR_DETECT is enabled */
  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  if (LddRxPduId >= Dcm_Num_Of_PduidTableConfig)
  {
    DCM_REPORT_ERROR(DCM_RX_INDICATION_SID, DCM_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /*  Initialize  variables  */
    LblErrorOccured = DCM_FALSE;
    LblStatus = DCM_TRUE;
  
    Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
    LddNegativeResponseCodeType = DCM_E_POSITIVERESPONSE;
  
    /* Initialize  pointer  to  the  RxPduId  in  the  PduId  table
         configuration
      */
    LpPduIdTable = &Dcm_GaaPduIdTableConfig[LddRxPduId];
  
    /*  Check  for  protocol  preemption  */
    if (LblStopProtocol == DCM_FALSE)
    {
      /*  Initialize  RxBuffer  Id  configured  for  the  RxPduId  */
      LucRxBufferId = LpPduIdTable->ucRxBufferId;
  
      /*  Initialize  TxBuffer  Id  configured  for  the  RxPduId  */
      LucTxBufferId = LpPduIdTable->ucTxBufferId;
    
      /*  Check  for  protocol  preemption  */
      if ((LucRxBufferId < Dcm_Num_Of_Buffer_Config) && (LucTxBufferId < Dcm_Num_Of_Buffer_Config) &&
          (NULL_PTR != Dcm_GaaBufferConfig[LucRxBufferId].pBufferArea) && 
          (NULL_PTR != Dcm_GaaBufferConfig[LucTxBufferId].pBufferArea))
      {
        /*  Initialize  pointer  to  the  Rx  buffer  Id  */
        LpRxBufferId = Dcm_GaaBufferConfig[LucRxBufferId].pBufferArea;
        LpTxBufferId = Dcm_GaaBufferConfig[LucTxBufferId].pBufferArea;
    
        LddTxPduId = LpPduIdTable->ddTxPduId;
        /*  Initialize  TxPduId  configured  for  the  RxPduId  */
        Dcm_GddDcmTxPduId = LpPduIdTable->ddTxPduId;
    
        /* To get protocol id Index */
        LucProtocolIDIndex = Dcm_GetProtocolIDIndex(Dcm_GddProtocolId);
    
        /*Get  the  Handle  Id  to  be  used  by  the  Lower  Layer  to  confirm
          the transmission  of  the  DcmDsProtocolTxPdu
        */
        Dcm_GddDcmTxConfPduId = (uint8)LpPduIdTable->usTxConfirmationPduId;
    
        /*  Initialize  the  addressing  type  for  the  requested  RxPduId  */
        LucreqType = LpPduIdTable->ucRxAddrType;

        /* Dcm_GpMsgContext = &Dcm_GstMsgContext in Dcm_Init */
        Dcm_GstMsgContext.resMaxDataLen = Dcm_GaaBufferConfig[LucTxBufferId].ulBufferSize - DCM_ONE;
        Dcm_GstMsgContext.resDataLen = (Dcm_MsgLenType)0x00;
        
        #if ((DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) && \
             (DCM_PROTOCOL_TRANSTYPE2 == STD_ON))       
        if(LblPerTransmission == DCM_TRUE)
        {
          if(Dcm_GaaPduIdTableConfig[LddRxPduId].pPeriodicTxId != NULL_PTR)
          {
            LucRxBufferId = Dcm_GaaPduIdTableConfig[Dcm_GucPeriodicRxPduId].ucPeriTransRxBufferIndex;
            LpRxBufferId = Dcm_GaaBufferConfig[LucRxBufferId].pBufferArea;
            Dcm_GpPerMsgContext->resMaxDataLen = Dcm_Dsp_Max_Periodic_Did_Len - 1U;
    
            for  (LusIndex = 0;LusIndex < Dcm_Dsp_Max_Periodic_DID_Scheduled;  LusIndex++)
            {
              SchM_Enter_Dcm_ProtclProtection();
              LucDataStatus = Dcm_GaaDslPeriodicData[LusIndex].ucDataStatus;
              SchM_Exit_Dcm_ProtclProtection();
              
              if (LucDataStatus == DCM_PER_DATA_IDLE)
              {
                /*  Initialize  pointer  to  the  Tx  buffer  Id  */
                SchM_Enter_Dcm_ProtclProtection();
                LpTxBufferId = Dcm_GaaDslPeriodicData[LusIndex].pPerData;
                SchM_Exit_Dcm_ProtclProtection();
                Dcm_IndexOfDslPeriodicData = LusIndex;
                
                break;
              }
            }
          }
        }
        #endif      
        #if ((DCM_RESPONSE_ON_EVENT_SERVICE  ==  STD_ON) && \
             (DCM_PROTOCOL_TRANSTYPE2  ==  STD_ON))
        if (LblROETransmission == DCM_TRUE)
        {
          LpPduIdTable = &Dcm_GaaPduIdTableConfig[LddRxPduId];
          LpRoeTxId = LpPduIdTable->pRoeTxId;
          LddTxPduId = LpRoeTxId->ddRoeTxPduId;
          LucRxBufferId = LpRoeTxId->ucRoeRxBufferId;
          LucTxBufferId = LpRoeTxId->ucRoeTxBufferId;
          LpRxBufferId = Dcm_GaaBufferConfig[LucRxBufferId].pBufferArea;
          LpTxBufferId = Dcm_GaaBufferConfig[LucTxBufferId].pBufferArea;
          Dcm_GpRoeMsgContext->resMaxDataLen = Dcm_GaaBufferConfig[LucTxBufferId].ulBufferSize - DCM_ONE;
        }
        #endif


        #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE  ==  STD_ON)
        if(LblPerTransmission == DCM_TRUE)
        {
          LddresDataLen  =  DCM_TWO;
        }
        else
        #endif
        {
          /* polyspace +1 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "Not a defect" */
          if (LucProtocolIDIndex < Dcm_Num_Of_ProtocolConfig)
          {
            LddresDataLen  = Dcm_GaaReqLength[LucProtocolIDIndex] - DCM_ONE;
          }
        }

        /*  Get  the  Service  Id  from  the  first  byte  of  the  Rx  buffer  */
        LucSID = LpRxBufferId[DCM_ZERO];

        LblSearchResult = Dcm_DsdReqManufacCallback(LpRxBufferId, LddRxPduId, LddresDataLen, &LddNegativeResponseCodeType);

        if ((LblSearchResult == DCM_FALSE) && (LddNegativeResponseCodeType != DCM_E_POSITIVERESPONSE))
        {
          /* CASE I
           *
           * [SWS_Dcm_00463] 
           * 
           * If at least a single Xxx_Indication() function called 
           * according to SWS_Dcm_00218 has returned E_NOT_OK and no function has 
           * returned E_REQUEST_NOT_ACCEPTED, the DSD submodule shall trigger a 
           * negative response with NRC from the ErrorCode parameter.
           */
          LblErrorOccured = DCM_TRUE;
          LpTxBufferId[DCM_TWO] = (uint8)LddNegativeResponseCodeType;
          Dcm_GddNegRespError = LddNegativeResponseCodeType;
        }
        else if(LblSearchResult == DCM_FALSE)
        {
          /* CASE II
           *
           * [SWS_Dcm_00462]  
           * If at least a single Xxx_Indication() function called 
           * according to SWS_Dcm_00218 returns E_REQUEST_NOT_ACCEPTED, the DSD 
           * submodule shall give no response.
           */   

          /* FIXME:
           *
           * [SWS_Dcm_01172]                  *
           * In case of [SWS_Dcm_00462, the DSD shall only call 
           * Xxx_Confirmation but not DspInternal_DcmConfirmation. */  

          /*  Clear  the  Normal  request  status  to  FALSE  */
          Dcm_GblNormalReq = DCM_FALSE;
      
          /* Reset the status of the RxPduId */
          Dcm_DslStatusReset();
        }
        else
        {

          LblSearchResult = Dcm_DsdServiceValidation(LucSID);  
          
          if (LblSearchResult == DCM_TRUE)
          {
            LblSearchResult = Dcm_DsdReqSupplCallback(LpRxBufferId, LddRxPduId, LddresDataLen, &LddNegativeResponseCodeType);
  
            if ((LblSearchResult == DCM_FALSE) && (LddNegativeResponseCodeType != DCM_E_POSITIVERESPONSE))
            {
              /* CASE I
               *
               * [SWS_Dcm_00463] 
               * 
               * If at least a single Xxx_Indication() function called 
               * according to SWS_Dcm_00218 has returned E_NOT_OK and no function has 
               * returned E_REQUEST_NOT_ACCEPTED, the DSD submodule shall trigger a 
               * negative response with NRC from the ErrorCode parameter.
               */
              LblErrorOccured = DCM_TRUE;
              LpTxBufferId[DCM_TWO] = (uint8)LddNegativeResponseCodeType;
              Dcm_GddNegRespError = LddNegativeResponseCodeType;
            }
            else if(LblSearchResult == DCM_FALSE)
            {
              /* CASE II
               *
               * [SWS_Dcm_00462]  
               * If at least a single Xxx_Indication() function called 
               * according to SWS_Dcm_00218 returns E_REQUEST_NOT_ACCEPTED, the DSD 
               * submodule shall give no response.
               */   
  
              /* FIXME:
               *
               * [SWS_Dcm_01172]                  *
               * In case of [SWS_Dcm_00462, the DSD shall only call 
               * Xxx_Confirmation but not DspInternal_DcmConfirmation. */  
  
              /*  Clear  the  Normal  request  status  to  FALSE  */
              Dcm_GblNormalReq = DCM_FALSE;
          
              /* Reset the status of the RxPduId */
              Dcm_DslStatusReset();
        
            }
            else
            {
              /*  Get  the  index  of  the  requested  service  Id  from  the  serviceId  table*/
              LucSIDIndex = Dcm_DsdSIdIndex(LucSID);
              /*  Initialize  pointer  to  the  parameters  of  requested  service  Id*/
              LpSIDTAB = NULL_PTR;
              if (LucSIDIndex < Dcm_Num_Of_SidConfig)
              {
                LpSIDTAB = &Dcm_GaaSIdConfig[LucSIDIndex];
              }

              /*  Get  the  Subfunction from the first byte of the Rx buffer  */
              if(LucSID == DCM_RESPONSEONEVENT)
              {
                LucSubFunction = (LpRxBufferId[DCM_ONE] & DCM_ROE_SUBFUNCTION_MASK);
              }
              else
              {
                LucSubFunction = (LpRxBufferId[DCM_ONE] & DCM_SUBFUNCTION_MASK);
              }
                
              LblSearchResult = Dcm_DsdPostValidation(LucSID, LucSubFunction);
              
              if ((NULL_PTR != LpSIDTAB) &&
                  (LblSearchResult == DCM_TRUE))
              {
                #if(DCM_PROTOCOL_TRANSTYPE2 == STD_ON)
                if ((LblPerTransmission == DCM_TRUE) ||
                    (LblROETransmission == DCM_TRUE)
                   )
                {
                  #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE  ==  STD_ON)
                  if (
                    (LblPerTransmission == DCM_TRUE) &&
                    (Dcm_GaaPduIdTableConfig[LddRxPduId].pPeriodicTxId != NULL_PTR)
                  )
                  {
                    /* Dcm_GpPerMsgContext = &Dcm_GstPerMsgContext in Dcm_Init*/
                    Dcm_GpPerMsgContext->reqDataLen = DCM_TWO;
        
                    /*  Clear  the  first  byte  of  the  response  buffer
                        since  this byte is used  to  realize  if  API
                        Dcm_ExternalSetNegResponse  was
                        called by any of the  service  in  the  API
                        Dcm_ExternalProcessingDone
                    */
                    LpTxBufferId[DCM_ZERO] = DCM_ZERO;
                    Dcm_GucPeriodicSID = DCM_READDATABYPERIODICIDENTIFIER;
        
                    /* Update the parameters of the MsgContext Structure  */
                    Dcm_GpPerMsgContext->idContext = LucSID | DCM_RESPONSE_ID;
                    Dcm_GpPerMsgContext->reqData = &LpRxBufferId[DCM_ONE]; /* without SID */
                    Dcm_GpPerMsgContext->resData = &LpTxBufferId[DCM_ZERO];
                    Dcm_GpPerMsgContext->dcmRxPduId = LddRxPduId;
                    Dcm_GpPerMsgContext->msgAddInfo.reqType = LucreqType;   
        
                    
                    if(NULL_PTR != LpSIDTAB->pDiagnosticService)
                    {
                      /* Invoke  Diagnostic  service  
                       * TODO: requestResult shall be processed 
                       */
                      (void)LpSIDTAB->pDiagnosticService(DCM_INITIAL, Dcm_GpPerMsgContext);
                    }
                   
                  }
                  #endif
        
                  #if(DCM_RESPONSE_ON_EVENT_SERVICE  ==  STD_ON)
                  if(LblROETransmission  ==  DCM_TRUE)
                  {
                    Dcm_GpRoeMsgContext->reqDataLen  =  Dcm_GddRoeReqLength - DCM_ONE;
        
                    /*  Clear  the  first  byte  of  the  response  buffer
                        since  this byte is used  to  realize  if  API
                        Dcm_ExternalSetNegResponse  was
                        called by any of the  service  in  the  API
                        Dcm_ExternalProcessingDone
                    */
                    LpTxBufferId[DCM_ZERO] = DCM_ZERO;
        
                    /* Update the parameters of the MsgContext Structure  */
                    Dcm_GpRoeMsgContext->idContext = (LucSID | DCM_RESPONSE_ID);
                    Dcm_GpRoeMsgContext->reqData = &LpRxBufferId[DCM_ONE];
                    Dcm_GpRoeMsgContext->resData = &LpTxBufferId[DCM_ONE];
                    Dcm_GpRoeMsgContext->dcmRxPduId = LddRxPduId;
                    Dcm_GpRoeMsgContext->msgAddInfo.reqType = LucreqType;
        
                    if(NULL_PTR != LpSIDTAB->pDiagnosticService)
                    {
                      /* Invoke  Diagnostic  service  
                       * TODO: requestResult shall be processed 
                       */
                      (void)LpSIDTAB->pDiagnosticService(DCM_INITIAL, Dcm_GpRoeMsgContext);
                    }
                  }
                  #endif
                }
                else
                #endif
                {
                  P2VAR(Dcm_RequestContextType, AUTOMATIC, DCM_APPL_DATA) requestContext;  
                  
                  #if((DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE  ==  STD_ON) && \
                  (DCM_PROTOCOL_TRANSTYPE2 == STD_OFF))
                  if(LblPerTransmission == DCM_TRUE)
                  {
                    Dcm_GucPeriodicSID = DCM_READDATABYPERIODICIDENTIFIER;
                    Dcm_GstMsgContext.reqDataLen  =  LddresDataLen;
        
                    Dcm_GstMsgContext.resData  =  &LpTxBufferId[DCM_ZERO];
                  }
                  else
                  #endif
                  {
                    Dcm_GstMsgContext.reqDataLen  = LddresDataLen;  
                    Dcm_GstMsgContext.resData  =  &LpTxBufferId[DCM_ONE];
                  }

                  /* Clear the first byte of the response buffer since this
                   * byte is used to realize if API Dcm_ExternalSetNegResponse
                   * was called by any of the service in the API
                   *   Dcm_ExternalProcessingDone
                   */
                  LpTxBufferId[DCM_ZERO]  =  DCM_ZERO;
                  
                  Dcm_DsdInternal_SetMsgContext(&Dcm_GstMsgContext, LddRxPduId, 
                                                 LpRxBufferId, LpSIDTAB->blSubFunctionAvailable);
                                               
                  requestContext = Dcm_DsdInternal_GetRequestContextByRxPduId(Dcm_GddRxPduId);
      
                  /* polyspace +1 DEFECT:NULL_PTR [Justified:Low] "Not a defect" */
                  if (NULL_PTR != requestContext)
                  {
                    requestContext->rct_ServiceIndex = LucSIDIndex;
                    requestContext->rct_SubFunctionId = LucSubFunction;  
                    requestContext->rct_RequestResult = E_OK;
                    requestContext->rct_MsgContext = &Dcm_GstMsgContext;
                  }
                
                  LulResBuffersize = Dcm_GaaBufferConfig[LucTxBufferId].ulBufferSize;
                  if (LucSID != DCM_TRANSFERDATA)
                  {
                    Dcm_MsgLenType maxDataSize = (Dcm_MsgLenType)(LulResBuffersize - 1U);
                    Dcm_DspInternal_MemClear(Dcm_GstMsgContext.resData, maxDataSize);
                  }
                  
                  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
      
                  /* Invoke  Diagnostic  service  
                   * TODO: requestResult shall be processed 
                   */
                  if((NULL_PTR != requestContext) && (NULL_PTR != LpSIDTAB->pDiagnosticService))
                  {
                    if (DCM_E_PENDING == LpSIDTAB->pDiagnosticService(DCM_INITIAL, &Dcm_GstMsgContext))
                    {
                      requestContext->rct_RequestResult = DCM_E_PENDING;
                    }
                  }
                }
              }
              else
              {
                LblErrorOccured = DCM_TRUE;
                LpTxBufferId[DCM_TWO] = (uint8)Dcm_GddNegRespError;
              }
            }
          }
          else
          {
            LblErrorOccured = DCM_TRUE;
            LpTxBufferId[DCM_TWO] = (uint8)Dcm_GddNegRespError;
          }
        }

        /* LblErrorOccured will be true if Xxx_Indication called has returned E_NOT_OK */
        if (
          (LblErrorOccured == DCM_FALSE) &&
          (
          /**
          (LucSID == DCM_ECURESET)  ||
          (LucSID == DCM_TESTERPRESENT)  ||
          (LucSID == DCM_CONTROLDTCSETTING)|| 
          (LucSID == DCM_LINKCONTROL)  || */
          (LucSID == DCM_OBD_REQ_CURRENTPOWERTRAINDIAGDATA)  ||
          (LucSID == DCM_OBD_REQ_ONBOAD_MONITOR_RESULT)  ||
          (LucSID == DCM_OBD_REQ_CTLR_ONBOAD_SYSTEM)  ||
          (LucSID == DCM_OBD_REQ_VEHICLEINFO)||
          (LucSID == DCM_READDATABYPERIODICIDENTIFIER)||
          (LucSID == DCM_DYNAMICALLYDEFINEDATAIDENTIFIER))
        )
        { 
          /* Check if any NRC is updated, if updated then invoke Dcm_ExternalSetNegResponse
           * before calling Dcm_ExternalProcessingDone  API */              
          if(Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE)
          {
            Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
          }
          /* Invoke the Dcm_ExternalProcessingDone only if it is not of  paged  transmission  type  */
          #if(DCM_PAGEDBUFFER_ENABLED  ==  STD_ON)
          if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
          #endif
          {
            Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
          }
        }
        
        /*
         * Initialize  the  global  bit  flag  indicating  that  all  the
         * verifications  were  successful
        */
        Dcm_TxRespStatus.ucFailedInd  =  DCM_FALSE;
        /*  Check  if  the  error  flag  is  set  */
        if(LblErrorOccured  ==  DCM_TRUE)
        {
          /*  Update  the  return  value  */
          LblStatus  =  DCM_FALSE;
          
          /* [SWS_Dcm_00001]
           * In the case of a Negative Result of the execution and active 
           * Functional Addressing the DSD submodule shall activate the suppression of the 
           * following Negative Responses: 
           * NRC 0x11 (Service not supported), 
           * NRC 0x12 (SubFunction not supported), 
           * NRC 0x31 (Request out of range), 
           * NRC 0x7E (Subfunction not supported in active session), 
           * NRC 0x7F (Service not supported in active session) ( BSW04020) */

          /* Check  if  the  NRC  error  is  to  be  suppressed   */
          if ((LucreqType == DCM_ADDR_FUNCTIONAL)  
            &&
            (
              (LpTxBufferId[DCM_TWO] == DCM_E_SERVICENOTSUPPORTED)
              ||
              (LpTxBufferId[DCM_TWO] == DCM_E_SUBFUNCTIONNOTSUPPORTED) 
              ||
              (LpTxBufferId[DCM_TWO] == DCM_E_REQUESTOUTOFRANGE) 
              ||
              (LpTxBufferId[DCM_TWO] == DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION) 
              ||
              (LpTxBufferId[DCM_TWO] == DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION)              
            )
          )
          {
            /*  Clear  the  Normal  request  status  to  FALSE  */
            Dcm_GblNormalReq = DCM_FALSE;
            /*  Reset  the  status  of  the  RxPduId  */
            Dcm_DslStatusReset();
          }
          else
          {
            /*  Update  the  response  data  buffer  pointer  */
            Dcm_GstMsgContext.resData  =  LpTxBufferId;
            /*  Update  the  first  byte  with  the  negative  response  Id  */
            LpTxBufferId[DCM_ZERO] = DCM_NEGATIVE_RESPONSE_SID;
            /*  Update  the  second  byte  with  the  service  Id  */
            LpTxBufferId[DCM_ONE] = LucSID;
            /*  Update  the  response  length  */
            Dcm_GstMsgContext.resDataLen  =  DCM_THREE;
            /* Invoke the internal transmit function to transmit the NRC  */
            Dcm_DslTransmit(LddTxPduId,  DCM_FALSE, DCM_FALSE);

            /*  Check  if  the  current  processing  is  for  normal  request  */
            if(Dcm_GblNormalReq == DCM_TRUE)
            {
              /* The global bit flag is made true, so that no confirmation
               * to the upper layer is given */
              Dcm_TxRespStatus.ucFailedInd  =  DCM_TRUE;
            }
            
          }
        }
      }
      else
      {
        /*  Clear  the  Normal  request  status  to  FALSE  */
        Dcm_GblNormalReq = DCM_FALSE;
        /*  Reset  the  status  of  the  RxPduId  */
        Dcm_DslStatusReset();
      }
    }
    else
    {
      if (
        (Dcm_TxRespStatus.ucNegResp == DCM_TRUE) ||
        (Dcm_TxRespStatus.ucNormResponse == DCM_TRUE)
        #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
        || 
        (
          (Dcm_TxRespStatus.ucPagedTrans == DCM_TRUE) &&
          (Dcm_TxRespStatus.ucDslPagedTrans == DCM_TRUE)
        )
        #endif
      )
      {
        #if(DCM_PDUR_CANCEL_TRANSMIT == STD_ON)
        (void)PduR_DcmCancelTransmit(LpPduIdTable->ddTxPduId);
        #endif
      }
      Dem_DcmCancelOperation();
    
      /* To Stop processing active diagnostic request */
      Dcm_DsdCancelOperation();
    
      Dcm_PrtclTxBufStatus.ucClearDTCStatus = DCM_FALSE;
      Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus = DCM_FALSE;
      Dcm_PrtclTxBufStatus.ReportNumOfDtc = DCM_FALSE;
      Dcm_GblDTCFDCPending = DCM_FALSE;
      Dcm_PrtclTxBufStatus.ucReportOBDDtc = DCM_FALSE;
      Dcm_GblFaultDetcetionCounter = DCM_FALSE;

      #if ((DCM_CLEAR_ITC_SERVICE_SUPPRT == STD_ON) || (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON))
      Dcm_InternalTroubleCodeService = DCM_FALSE;
      #endif
      
      /*  Invoking  of  DSP  internal  function  to  stop  the  current  protocol  */
      #if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
      Dcm_DspReturnControlToEcu();
      #endif

      /*  Invoke  DSP  internal  function  to  stop  the  current  protocol */
      for  (LucIndex2  =  0U; LucIndex2 < Dcm_Total_Num_Of_Callback_Request;  LucIndex2++)
      {
        if(NULL_PTR != Dcm_GaaCbkReqServices[LucIndex2].pStopProtocolFun)
        { 
          (void)Dcm_GaaCbkReqServices[LucIndex2].pStopProtocolFun(Dcm_GddProtocolId);
        }
      }
    
      /* Invoke the API to inactivate the diagnostic session on protocol preemption */
      (void)ComM_DCM_InactiveDiagnostic((NetworkHandleType)Dcm_GulChannelIdentifier);
    }
  }
  
  return(LblStatus);
}

/*******************************************************************************
**  Function  Name        : Dcm_DsdReqManufacCallback                         **
**                                                                            **
**  Service  ID           : NA                                                **
**                                                                            **
**  Description           : This  function  used to check the Manufacturer    **
**                          permission/environment. This function will call   **
**                          Manufacturer Application  to check permission     **
**                          /environment.                                     **
**                                                                            **
** Sync/Async             : Synchronous                                       **
**                                                                            **
**  Re-entrancy           : Non-Reentrant                                     **
**                                                                            **
**  Input  Parameters     : pMsgContext,  LddRxPduId, LddresDataLen           **
**                                                                            **
** InOut parameter        : None                                              **
**                                                                            **
**  Output  Parameters    : LddNegativeResponseCode                           **
**                                                                            **
**  Return  parameter     : boolean                                           **
**                                                                            **
**  Preconditions         : None                                              **
**                                                                            **
**  Remarks               : Global  Variable(s)  : Dcm_GaaPduIdTableConfig    **
**                                       Dcm_GaaManuIndConfigType             **
**                          Dcm_GaaSuppIndConfigType                          **
**                          Function(s)  invoked  : None                      **
**                                                                            **
*******************************************************************************/
/* MISRA Rule         : 16.7
   Message            : A pointer parameter in a function prototype should be
                        declared as pointer to const if the pointer is not
                        used to modify the addressed object.
   Reason             : This is the prototype specified in the specification.
   Verification       : However, part of the code is verified
                        manually and it is not having any impact.
*/
static FUNC(boolean, DCM_CODE) Dcm_DsdReqManufacCallback(
   P2VAR(uint8,  AUTOMATIC,  DCM_APPL_DATA)  LpRxBufferId,
   PduIdType LddRxPduId, Dcm_MsgLenType LddresDataLen, 
   P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA)
   LddNegativeResponseCode)
{
  boolean LblTransmitReqToDSP;
  #if (DCM_REQUEST_MANUFACTURER_INDICATION_ENABLED == STD_ON)
  P2CONST(Dcm_PduIdTable,  AUTOMATIC,  DCM_APPL_CONST)LpPduIdTable;
  Dcm_NegativeResponseCodeType LddErrorCode;
  Dcm_NegativeResponseCodeType LddNegResp;
  Std_ReturnType LaaReturnType;
  uint8 LucSid;
  uint8 LucreqType;
  uint8 LucIndex;
  uint8 LucNotAcceptedCount;
  uint8 LucENotOkCount;
  
  boolean LblLoopFlag;
  Dcm_IndicationFunType LppIndicationFun;
  LblTransmitReqToDSP = DCM_TRUE;
  LucNotAcceptedCount = DCM_ZERO;
  LucENotOkCount = DCM_ZERO;
  LddErrorCode = DCM_E_POSITIVERESPONSE;
  LddNegResp = DCM_E_POSITIVERESPONSE;
  LblLoopFlag = DCM_FALSE;

  LpPduIdTable = &Dcm_GaaPduIdTableConfig[LddRxPduId];
  /* Initialize the addressing type for the requested RxPduId */
  LucreqType = LpPduIdTable->ucRxAddrType;
  LucSid = LpRxBufferId[DCM_ZERO];

  
 /* 
  * Invoke the API xxx_Indication to do the request
  * message environment verification
  */
  /* polyspace +3 MISRA-C3:10.1 [Justified:Low] "Not a defect" */
  for(LucIndex = DCM_ZERO;
    (LucIndex < Dcm_Number_Of_Request_Manufacturer_Indication) && (DCM_FALSE == LblLoopFlag);
    LucIndex++)
  {  
    LppIndicationFun = Dcm_GetManuIndicationFun(LucIndex);
    if(LppIndicationFun != NULL_PTR)
    {
      LaaReturnType = LppIndicationFun(
                                      LucSid, &LpRxBufferId[DCM_ONE],
                                      (uint16)LddresDataLen, LucreqType,
                                      (uint16)LpPduIdTable->ucProRxTesterSrcAddr,
                                      &LddErrorCode);
      
      /* Store the NRC error and set the error flag */
      if(LaaReturnType == E_NOT_OK)
      {
        LddNegResp = LddErrorCode;
        LblTransmitReqToDSP = DCM_FALSE;
        LucENotOkCount++;
      }
      /* Store the NRC error and set the error flag */
      else if(LaaReturnType == E_REQUEST_NOT_ACCEPTED)
      {
        LblLoopFlag = DCM_TRUE;
        LblTransmitReqToDSP = DCM_FALSE;
        LucNotAcceptedCount++;
      }
      else
      {
        /* Set a flag to transfer request to DSP layer */
        LblTransmitReqToDSP = DCM_TRUE;
      }
    }
  }
    
  if((LucNotAcceptedCount == DCM_ZERO) && (LucENotOkCount > DCM_ZERO))
  {
    *LddNegativeResponseCode = LddNegResp;
    LblTransmitReqToDSP = DCM_FALSE;
  }
  #else
  LblTransmitReqToDSP = DCM_TRUE;
  #endif
  
  return(LblTransmitReqToDSP);
}
/*******************************************************************************
**  Function  Name        : Dcm_DsdReqSupplCallback                           **
**                                                                            **
**  Service  ID           : NA                                                **
**                                                                            **
**  Description           : This  function  used to check the Supplier        **
**                          permission/environment. This function will call   **
**                          Supplier Application  to check permission         **
**                          /environment.                                     **
**                                                                            **
** Sync/Async             : Synchronous                                       **
**                                                                            **
**  Re-entrancy           : Non-Reentrant                                     **
**                                                                            **
**  Input  Parameters     : pMsgContext,  LddRxPduId, LddresDataLen           **
**                                                                            **
** InOut parameter        : None                                              **
**                                                                            **
**  Output  Parameters    : LddNegativeResponseCode                           **
**                                                                            **
**  Return  parameter     : boolean                                           **
**                                                                            **
**  Preconditions         : None                                              **
**                                                                            **
**  Remarks               : Global  Variable(s)  : Dcm_GaaPduIdTableConfig    **
**                                       Dcm_GaaManuIndConfigType             **
**                          Dcm_GaaSuppIndConfigType                          **
**                          Function(s)  invoked  : None                      **
**                                                                            **
*******************************************************************************/
/* MISRA Rule         : 16.7
   Message            : A pointer parameter in a function prototype should be
                        declared as pointer to const if the pointer is not
                        used to modify the addressed object.
   Reason             : This is the prototype specified in the specification.
   Verification       : However, part of the code is verified
                        manually and it is not having any impact.
*/
static FUNC(boolean, DCM_CODE) Dcm_DsdReqSupplCallback(
   P2VAR(uint8,  AUTOMATIC,  DCM_APPL_DATA)  LpRxBufferId,
   PduIdType LddRxPduId, Dcm_MsgLenType LddresDataLen, 
   P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA)
   LddNegativeResponseCode)
{
  boolean LblTransmitReqToDSP;
  #if(DCM_REQUEST_SUPPLIER_INDICATION_ENABLED == STD_ON)
  P2CONST(Dcm_PduIdTable,  AUTOMATIC,  DCM_APPL_CONST)LpPduIdTable;
  Dcm_NegativeResponseCodeType LddErrorCode;
  Dcm_NegativeResponseCodeType LddNegResp;
  Std_ReturnType LaaReturnType;
  uint8 LucSid;
  uint8 LucreqType;
  uint8 LucIndex;
  uint8 LucNotAcceptedCount;
  uint8 LucENotOkCount;
  Dcm_IndicationFunType LppIndicationFun;

  LucNotAcceptedCount = DCM_ZERO;
  LucENotOkCount = DCM_ZERO;
  LddErrorCode = DCM_E_POSITIVERESPONSE;
  LddNegResp = DCM_E_POSITIVERESPONSE;

  LpPduIdTable = &Dcm_GaaPduIdTableConfig[LddRxPduId];
  /* Initialize the addressing type for the requested RxPduId */
  LucreqType = LpPduIdTable->ucRxAddrType;
  LucSid = LpRxBufferId[DCM_ZERO];

  
 /* 
  * Invoke the API xxx_Indication to do the request
  * message environment verification
  */
  /* polyspace +1 DEFECT:USELESS_IF [Justified:Low] "Not a defect" */
  for(LucIndex = DCM_ZERO;
      LucIndex < Dcm_Number_Of_Request_Supplier_Indication;
      LucIndex++)
  {
    LppIndicationFun = Dcm_GetSuppIndicationFun(LucIndex);
    if(LppIndicationFun != NULL_PTR)
    {
      LaaReturnType = LppIndicationFun(
                                    LucSid, &LpRxBufferId[DCM_ONE],
                                    (uint16)LddresDataLen, LucreqType,
                                    (uint16)LpPduIdTable->ucProRxTesterSrcAddr,
                                    &LddErrorCode);
      
      /* Store the NRC error and set the error flag */
      if(LaaReturnType == E_NOT_OK)
      {
        LddNegResp = LddErrorCode;
        LblTransmitReqToDSP = DCM_FALSE;
        LucENotOkCount++;
      }
      /* Store the NRC error and set the error flag */
      else if(LaaReturnType == E_REQUEST_NOT_ACCEPTED)
      {
        /* Should not send response  */
        LblTransmitReqToDSP = DCM_FALSE;
        LucNotAcceptedCount++;
      }
      else
      {
        /* Set a flag to transfer request to DSP layer */
        LblTransmitReqToDSP = DCM_TRUE;
      }
    }
  }
  
  if((LucNotAcceptedCount == DCM_ZERO) && (LucENotOkCount > DCM_ZERO))
  {
    *LddNegativeResponseCode = LddNegResp;
    LblTransmitReqToDSP = DCM_FALSE;
  }
  #else
  LblTransmitReqToDSP = DCM_TRUE;
  #endif
  
  return(LblTransmitReqToDSP);
}

/*******************************************************************************
**  Function  Name        :  Dcm_DsdPostValidation                            **
**                                                                            **
**  Service  ID           :  NA                                               **
**                                                                            **
**  Description           :  This  function  will  validate the service and   **
**                          subfunction requested.                            **
**                                                                            **
**  Sync/Async            :  Synchronous                                      **
**                                                                            **
**  Re-entrancy           :  Non-Reentrant                                    **
**                                                                            **
**  Input  Parameters     :  LucSID,  LucSubFunction                          **
**                                                                            **
**  InOut parameter       :  None                                             **
**                                                                            **
**  Output  Parameters    :  LddNegativeResponseCode                          **
**                                                                            **
**  Return  parameter     :  boolean                                          **
**                                                                            **
**  Preconditions         :  None                                             **
**                                                                            **
**  Remarks               :  Global  Variable(s)  : Dcm_GddProtocolId         **
**                           Dcm_GaaSIdConfig , Dcm_GaaReqLength              **
**                           Dcm_GaaModeRuleConfig                            **
**                           Dcm_GddNegRespError , Dcm_GblDownLoadActive      **
**                           Dcm_GblUpLoadActive , Dcm_GaaPduIdTableConfig    **
**                           Function(s)  invoked  :                          **
**                           Dcm_DsdSIdIndex, Dcm_DsdSubServiceValidation     **
**                           Dcm_GaaModeRuleConfig, Dcm_GetProtocolIDIndex    **
**                           Dcm_DsdModeRuleCheck                             **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_DsdPostValidation
  (uint8 LucSID, uint8 LucSubFunction)
{
  P2CONST(Dcm_ServiceIdConfigType,  AUTOMATIC,  DCM_APPL_CONST)LpSIDTAB;
  uint8 LucSIDIndex;
  uint8 LucProtocolIDIndex = DCM_SERVICE_NOT_CONFIGURED;
  boolean  LblSearchResult = DCM_TRUE;

  if(LucSID != DCM_ROUTINECONTROL)
  {
    /*  Get  the  index  of  the  requested  service  Id  from  the  service Id  table */
    LucSIDIndex = Dcm_DsdSIdIndex(LucSID);
  
    /* To get protocol id Index */
    LucProtocolIDIndex = Dcm_GetProtocolIDIndex(Dcm_GddProtocolId);
  
    /*  Initialize  pointer  to  the  parameters  of  requested  service  Id*/
    LpSIDTAB = NULL_PTR;
    if (LucSIDIndex < Dcm_Num_Of_SidConfig)
    {
      LpSIDTAB  =  &Dcm_GaaSIdConfig[LucSIDIndex];
    }
    
  
    #if(DCM_MODE_RULE  ==  STD_ON)
    if((NULL_PTR != LpSIDTAB) &&
       (LpSIDTAB->blModeRuleConfigured == DCM_TRUE))
    {
      LblSearchResult = Dcm_DsdModeRuleCheck(LpSIDTAB->ucseviceModeruleindexarray);
    }
    
    if(LblSearchResult != DCM_TRUE)
    {
      #if(DCM_DSP_MODE_RULE_NRC == STD_ON)
      if (NULL_PTR != LpSIDTAB)
      {
        Dcm_GddNegRespError = Dcm_GaaModeRuleConfig[LpSIDTAB->ucseviceModeruleindexarray].ucNRCType;
      }
      #else
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
      #endif
    }
    else
    #endif
    {
      if((NULL_PTR != LpSIDTAB) &&
         (LucProtocolIDIndex < Dcm_Num_Of_ProtocolConfig))
      {
        if (Dcm_GaaReqLength[LucProtocolIDIndex] < LpSIDTAB->ucMinReqLength)
        {
          LblSearchResult = DCM_FALSE;
          /* Requested Session is not supported */
          Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
          
          #if((DCM_TRANSFER_DATA_SERVICE == STD_ON) || (DCM_TRANSFER_EXIT_SERVICE == STD_ON))
          if ((LucSID == DCM_TRANSFERDATA) ||  (LucSID == DCM_REQUESTTRANSFEREXIT))
          {
            /* Why here? */
            Dcm_GblDownLoadActive = DCM_FALSE;
            Dcm_GblUpLoadActive = DCM_FALSE;
          }          
          #endif
        }
        else
        {
          if(NULL_PTR != LpSIDTAB->pSubServiceId)
          {    
            LblSearchResult = Dcm_DsdSubServiceValidation(LpSIDTAB, LucSubFunction);
          }
        }
      }
      else
      {
        LblSearchResult = DCM_FALSE;
        Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
        /* Det Error */
      }
    }
  }

  return LblSearchResult;
}

/*******************************************************************************
**  Function  Name        :  Dcm_DsdServiceValidation                         **
**                                                                            **
**  Service  ID           :  NA                                               **
**                                                                            **
**  Description           :  This  function  will  validate the service and   **
**                          subfunction requested.                            **
**                                                                            **
** Sync/Async             : Synchronous                                       **
**                                                                            **
**  Re-entrancy           :  Non-Reentrant                                    **
**                                                                            **
**  Input  Parameters     :  LucSID                                           **
**                                                                            **
** InOut parameter        : None                                              **
**                                                                            **
**  Output  Parameters    :  None                                             **
**                                                                            **
**  Return  parameter     :  boolean                                          **
**                                                                            **
**  Preconditions         :  None                                             **
**                                                                            **
**  Remarks               :  Global  Variable(s)  : Dcm_GddProtocolId         **
**                           Dcm_GaaSIdConfig ,                               **
**                           Dcm_GddNegRespError                              **
**                                                                            **
**                           Function(s)  invoked  :                          **
**                           Dcm_GetProtocolIDIndex,Dcm_DsdValidateSession    **
**                           Dcm_DsdValidateSecurity                          **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_DsdServiceValidation
  (uint8 LucSID)
{
  P2CONST(Dcm_ServiceIdConfigType,  AUTOMATIC,  DCM_APPL_CONST)LpSIDTAB;
  uint8 LucSIDIndex;
  uint8 LucProtocolIDIndex = DCM_SERVICE_NOT_CONFIGURED;
  boolean LblSearchResult = DCM_FALSE;

  /*  Get  the  index  of  the  requested  service  Id  from  the  service Id  table */
  LucSIDIndex = Dcm_DsdSIdIndex(LucSID);

  /* To get protocol id Index */
  LucProtocolIDIndex = Dcm_GetProtocolIDIndex(Dcm_GddProtocolId);

  /*  Check  is  service  Id  configured  in  the  service  Id  table  */
  if ((LucSIDIndex == DCM_SERVICE_NOT_CONFIGURED) || (LucProtocolIDIndex == DCM_SERVICE_NOT_CONFIGURED))
  {
    /* Requested  Service  ID  is  not  configured  in  the  active  service
       table
    */
    Dcm_GddNegRespError = DCM_E_SERVICENOTSUPPORTED;
  }
  else
  {
    #if (DCM_DEV_ERROR_DETECT == STD_ON)
    if (LucSIDIndex >= Dcm_Num_Of_SidConfig)
    {  
      Dcm_GddNegRespError = DCM_E_GENERALREJECT; 
    }
    else
    #endif
    {
      /*  Initialize  pointer  to  the  parameters  of  requested  service  Id*/
      LpSIDTAB  =  &Dcm_GaaSIdConfig[LucSIDIndex];
    
      /*  Invoke  function  to  validate  session  */
      if(LpSIDTAB->pSession  !=  NULL_PTR)
      {
        LblSearchResult = Dcm_DsdValidateSession(LpSIDTAB->pSession, LpSIDTAB->ucSessionCount);
      }
      else
      {
        LblSearchResult = DCM_TRUE;
      }
    
      /* Check  is  the  current  security  level  supported  by  the  service Id */
      if(LblSearchResult != DCM_TRUE)
      {      
        Dcm_GddNegRespError = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
      }
      else
      {
        if(LpSIDTAB->pSecurity != NULL_PTR)
        {
          /*  Invoke  function  for  security  validation  */
          LblSearchResult = Dcm_DsdValidateSecurity(LpSIDTAB->pSecurity,
          LpSIDTAB->ucSecurityCount);
        }
        
        /* Check  is  the  current  security  level  supported  by  the   service  Id */
        if(LblSearchResult !=  DCM_TRUE)      
        {
          Dcm_GddNegRespError = DCM_E_SECURITYACCESSDENIED;
        }
      }
    }
  }
  return (LblSearchResult);
}

/*******************************************************************************
**  Function  Name        :  Dcm_DsdServiceValidation                         **
**                                                                            **
**  Service  ID           :  NA                                               **
**                                                                            **
**  Description           :  This  function  will  validate the service and   **
**                          subfunction requested.                            **
**                                                                            **
** Sync/Async             : Synchronous                                       **
**                                                                            **
**  Re-entrancy           :  Non-Reentrant                                    **
**                                                                            **
**  Input  Parameters     :  LucSID,  LucSubFunction                          **
**                                                                            **
** InOut parameter        : None                                              **
**                                                                            **
**  Output  Parameters    :  None                                             **
**                                                                            **
**  Return  parameter     :  boolean                                          **
**                                                                            **
**  Preconditions         :  None                                             **
**                                                                            **
**  Remarks               :  Global  Variable(s)  : Dcm_GddProtocolId         **
**                           Dcm_GaaSIdConfig , Dcm_GaaReqLength              **
**                           Dcm_GucSubSerIdIndex , Dcm_GaaModeRuleConfig     **
**                           Dcm_GddNegRespError , Dcm_GblDownLoadActive      **
**                           Dcm_GblUpLoadActive                              **
**                           Function(s)  invoked  :                          **
**                           Dcm_GetProtocolIDIndex,Dcm_DsdValidateSession,   **
**                           Dcm_DsdValidateSecurity,Dcm_DsdModeRuleCheck,    **
**                           Dcm_DsdValidateSubServiceId                      **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_DsdSubServiceValidation(
  P2CONST(Dcm_ServiceIdConfigType,  AUTOMATIC,  DCM_APPL_CONST)LpSIDTAB,
  uint8 LucSubFunction)
{
  P2CONST(Dcm_SubServiceIdConfigType, AUTOMATIC, DCM_APPL_CONST) LpSubServiceId;
  uint8 LucSubFunctionIndex = DCM_SERVICE_NOT_CONFIGURED;
  boolean LblSearchResult = DCM_FALSE;


  #if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (NULL_PTR == LpSIDTAB)
  {  
    Dcm_GddNegRespError = DCM_E_GENERALREJECT; 
  }
  else
  #endif
  {
    /*  Initialize  pointer  to  the  parameters  of  requested Subservice  Id*/
    LpSubServiceId = LpSIDTAB->pSubServiceId;
    if(LpSubServiceId != NULL_PTR)
    {    
      LblSearchResult = Dcm_DsdValidateSubServiceId(LpSubServiceId,
        LpSIDTAB->ucSubServiceCount, 
        LucSubFunction,
        &LucSubFunctionIndex);                
      
      if (LblSearchResult != DCM_TRUE)
      {
        /* Requested Session is not supported */
        Dcm_GddNegRespError = DCM_E_SUBFUNCTIONNOTSUPPORTED;
      }
      else
      {
        LpSubServiceId = &LpSubServiceId[LucSubFunctionIndex];  
        
        if (LpSubServiceId->pSubSerSession != NULL_PTR)
        {
          LblSearchResult = Dcm_DsdValidateSession
            (LpSubServiceId->pSubSerSession, LpSubServiceId->ucSubSerSessionCount);
        }

        if(LblSearchResult != DCM_TRUE)
        {
          Dcm_GddNegRespError = DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION;
        }
        else
        {
          if(LpSubServiceId->pSubSerSecurity != NULL_PTR)
          {
            LblSearchResult = Dcm_DsdValidateSecurity(
              LpSubServiceId->pSubSerSecurity,
              LpSubServiceId->ucSubSerSecurityCount);
          }
          
          /* Check is the  security level supported by the service Id */
          if(LblSearchResult != DCM_TRUE)
          {
            Dcm_GddNegRespError = DCM_E_SECURITYACCESSDENIED;
          }
          else
          {
            #if (DCM_MODE_RULE == STD_ON)
            if(LpSubServiceId->blModeRuleConfigured == DCM_TRUE)
            {
              LblSearchResult = Dcm_DsdModeRuleCheck(LpSubServiceId->ucsubmoderuleArrayindex);

              if(LblSearchResult != DCM_TRUE)
              {
                #if(DCM_DSP_MODE_RULE_NRC == STD_ON)
                Dcm_GddNegRespError = Dcm_GaaModeRuleConfig[LpSubServiceId->ucsubmoderuleArrayindex].ucNRCType;
                #else
                Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
                #endif
              }
            }
            #endif
          }
        }
      }
    }
  }
  
  return (LblSearchResult);
}

/*******************************************************************************
**  Function  Name      : Dcm_DsdConfirmation                                 **
**                                                                            **
**  Service  ID         : NA                                                  **
**                                                                            **
**  Description         : This  function  will  give  the  confirmation  to   **
**                        upper  layer.  It  is  invoked  by  the  API        **
**                        Dcm_TpTxConfirmation.                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
**  Re-entrancy         : Non-Reentrant                                       **
**                                                                            **
**  Input  Parameters   : LddResult                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
**  Output  Parameters  : None                                                **
**                                                                            **
**  Return  parameter   : void                                                **
**                                                                            **
**  Preconditions       : None                                                **
**                                                                            **
**  Remarks             : Global  Variable(s)  :  Dcm_GpMsgContext            **
**                        Dcm_GaaPduIdTableConfig,  Dcm_GaaBufferConfig,      **
**                        Dcm_TxRespStatus,  Dcm_TimerReqFlagStatus           **
**                        Dcm_GblResOnPeriodicIdStatus                        **
**                        Dcm_GaaManuIndConfigType, Dcm_GaaSuppIndConfigType  **
**                        Function(s)  invoked  :DspInternal_DcmConfirmation, **
**                        Dcm_DspUpdatePage,                                  **
**                        Dcm_DspCancelPagedBufferProcessing                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DsdConfirmation(NotifResultType  LddResult)
{
  P2VAR(uint8,  AUTOMATIC,  DCM_APPL_DATA)LpTxBufferId;
  P2CONST(Dcm_BufferConfig,  AUTOMATIC,  DCM_APPL_CONST)LpBufferConfig;
  
  P2CONST(Dcm_PduIdTable,  AUTOMATIC,  DCM_APPL_CONST)LpPduIdTable1;
  
  #if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
  P2CONST(Dcm_ProtocolConfig, AUTOMATIC, DCM_APPL_CONST)LpProtocolConfig;
  #endif
  
  #if  (((DCM_PROTOCOL_TRANSTYPE2  ==  STD_ON)  &&  \
    (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE  ==  STD_ON)) || \
    (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON))
  P2CONST(Dcm_PduIdTable,  AUTOMATIC,  DCM_APPL_CONST)LpPduIdTable;
  #endif
  
  #if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
  uint8 LucProtocolIDIndex;
  #endif
  
  #if  ((DCM_PROTOCOL_TRANSTYPE2  ==  STD_ON)  &&  \
    (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE  ==  STD_ON))
  uint8  LucMaxNumTxPduid;
  uint8  LucIndex;
  uint8  LucBusyCount;
  #endif
  
  uint8 LucIndex1;
  
  #if(DCM_PAGEDBUFFER_ENABLED  ==  STD_ON)
  uint32 LulBufferSize;
  #endif
  
  PduIdType LddRxPduId;
  uint8 LucTxBufferId = (uint8)0x00;
  uint8 LucResp = (uint8)0x00;
  boolean LblNrcOccured;

  /* Check if the pre compile option DCM_DEV_ERROR_DETECT is enabled */
  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  if(Dcm_GstMsgContext.dcmRxPduId >= Dcm_Num_Of_PduidTableConfig)
  {
    /* Report to DET */
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID, 
                            DCM_TX_CONFIRMATION_SID, DCM_E_INTERFACE_BUFFER_OVERFLOW);  
  }
  else
  #endif
  {
    /*  Initialize  RxPduId  from  the  MsgContext  */
    LddRxPduId  =  Dcm_GstMsgContext.dcmRxPduId;    
    /*  Initialize  Tx  buffer  Id  configured  for  the  RxPduId  */
    LucTxBufferId = (uint8)Dcm_GaaPduIdTableConfig[LddRxPduId].ucTxBufferId;
      
    if(LucTxBufferId < Dcm_Num_Of_Buffer_Config) 
    {
      /*  Initialize  pointer  to  corresponding  buffer  Id  structure  */
      LpBufferConfig = &Dcm_GaaBufferConfig[LucTxBufferId];
      /*  Initialize  pointer  to  the  Tx  buffer  area  */
      LpTxBufferId = LpBufferConfig->pBufferArea;
    
      LpPduIdTable1 = &Dcm_GaaPduIdTableConfig[LddRxPduId];
      /*  Check if the pre compile option DCM_PAGEDBUFFER_ENABLED is enabled
      */
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      /*  Check  if  the  paged  transmission  is  currently  in  progress  */
      if(Dcm_TxRespStatus.ucPagedTrans == DCM_FALSE)
      #endif
      {
        Dcm_ConfirmationFunType LpConfirmationFun;
        Dcm_IdContextType SID = Dcm_GstMsgContext.idContext & DCM_SID_MASK;
        /*  Check  if  Dcm_ExternalSetNegResponse  was  called  before  calling
        *  Dcm_ExternalProcessingDone
        */
        if (DCM_TRUE == Dcm_TxRespStatus.ucNeedFailedConfiramtion)
        {
          LblNrcOccured  =  DCM_TRUE;       
          Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_FALSE;
        }
        else
        {
          if(LpTxBufferId[0U] == DCM_NEGATIVE_RESPONSE_SID)
          {          
            /*  Clear  the  negative  response  Id  */
            LpTxBufferId[0U] = DCM_ZERO;                  
            LblNrcOccured = DCM_TRUE;
          }
          else
          {
            LblNrcOccured  =  DCM_FALSE;       
          }
        }        
            
        if (DCM_TRUE == LblNrcOccured)
        {
          if (NTFRSLT_OK == LddResult)
          {
            LucResp = DCM_RES_NEG_OK;
          }
          else
          {
            LucResp = DCM_RES_NEG_NOT_OK;
          }         
        }
        else
        {         
          if (NTFRSLT_OK == LddResult)
          {
            LucResp = DCM_RES_POS_OK;
          }
          else
          {
            LucResp = DCM_RES_POS_NOT_OK;
          }         
        }  

        /* The global bit flag is made true, so that no confirmation
         * to the upper layer is given 
         *
         * Dcm_TxRespStatus.ucFailedInd is true in case of Dcm_GblNormalReq is true and 
         * 1. Xxx_Indication has returned E_NOT_OK or 
         * 2. NRC is generated by DSD
         * 
         * [SWS_Dcm_01000]  
         * In case a NRC is generated by DSD, the API 
         * DspInternal_DcmConfirmation is not called, but only XXX_Confirmation         
         *
         * [SWS_Dcm_00218]  
         * If configured (configuration parameter 
         * DcmDsdRequestManufacturerNotificationEnabled=TRUE), the DSD submodule 
         * shall call the operation Xxx_Indication() on all configured 
         * ServiceRequestIndication ports (see configuration parameter 
         * DcmDsdServiceRequestManufacturerNotification).
         * 
         * [SWS_Dcm_00462] 
         * If at least a single Xxx_Indication() function called 
         * according to SWS_Dcm_00218 returns E_REQUEST_NOT_ACCEPTED, the DSD 
         * submodule shall give no response.
         * 
         * [SWS_Dcm_01172]
         * In case of [SWS_Dcm_00462, the DSD shall only call 
         * Xxx_Confirmation but not DspInternal_DcmConfirmation.         
         */        
        if(Dcm_TxRespStatus.ucFailedInd == DCM_FALSE)
        {

          DspInternal_DcmConfirmation(Dcm_GstMsgContext.idContext,  LddRxPduId,
            (Dcm_ConfirmationStatusType)LucResp);
        }
        
        /* [SWS_Dcm_00742]  
         * The call of Xxx_Confirmation() shall be done right after the 
         * call of DspInternal_DcmConfirmation() */    
        #if (DCM_REQUEST_MANUFACTURER_INDICATION_ENABLED == STD_ON)
        for(LucIndex1 = DCM_ZERO;
            LucIndex1 < Dcm_Number_Of_Request_Manufacturer_Indication;
            LucIndex1++)
        {
          LpConfirmationFun = Dcm_GetManuConfirmationFun(LucIndex1);
          if(LpConfirmationFun != NULL_PTR)
          {
            (void)LpConfirmationFun
              (SID, LpPduIdTable1->ucRxAddrType,
              (uint16)LpPduIdTable1->ucProRxTesterSrcAddr,
              (Dcm_ConfirmationStatusType)LucResp);
          }
        }
        #endif
        /* polyspace +1 DEFECT:USELESS_IF [Justified:Low] "Not a defect" */
        #if (DCM_REQUEST_SUPPLIER_INDICATION_ENABLED == STD_ON)
        for(LucIndex1 = DCM_ZERO;
            LucIndex1 < Dcm_Number_Of_Request_Supplier_Indication;
            LucIndex1++)
        {
          LpConfirmationFun = Dcm_GetSuppConfirmationFun(LucIndex1);
          if(LpConfirmationFun != NULL_PTR)
          {
            (void)LpConfirmationFun
              (SID, LpPduIdTable1->ucRxAddrType,
              (uint16)LpPduIdTable1->ucProRxTesterSrcAddr,
              (Dcm_ConfirmationStatusType)LucResp);
          }
        }
        #endif
      }
      #if(DCM_PAGEDBUFFER_ENABLED  ==  STD_ON)
      else
      {
        /*  Check  if  the  previous  page  was  transmitted  successfully  */
        if(LddResult  ==  NTFRSLT_OK)
        {
          /*  Get  the  buffer  size  where  the  next  page  is  to be updated */
          LulBufferSize  =  LpBufferConfig->ulBufferSize;
          /*
           *  Invoke  the  update  function  of  DSP/RTE  based  on  where
           *  the requested service  is  implemented
          */
          Dcm_DspUpdatePage(LpTxBufferId,  LulBufferSize);
    
          /*  Start  the  paged  buffer  timeout  timer  */
          DCM_START_TIMER(DCM_PAGED_BUFFER_TIMER,  Dcm_PagedBufferTimeout);
          SchM_Enter_Dcm_TimerProtection();
          Dcm_TimerReqFlagStatus.ucPagedBufferTimer = DCM_TRUE;
          SchM_Exit_Dcm_TimerProtection();
        }
        else
        {
          /*
           *  Invoke  the  cancel  paged  buffer  function  of  DSP/RTE  based  on
           *  where the  requested  service  is  implemented
          */
          Dcm_DspCancelPagedBufferProcessing();
    
          /*  Update  the  bit  for  the  paged  transmission  to  FALSE  */
          Dcm_TxRespStatus.ucPagedTrans = DCM_FALSE;
        }
      }
      #endif

      #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)      
      /* Type 2*/
      #if (DCM_PROTOCOL_TRANSTYPE2 == STD_ON)
      if((Dcm_GblResOnPeriodicIdStatus == DCM_TRUE)  &&
        (Dcm_GaaPduIdTableConfig[Dcm_GucPeriodicRxPduId].pPeriodicTxId  != NULL_PTR))
      {
        LucBusyCount = DCM_ZERO;
        LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GucPeriodicRxPduId];
        LucMaxNumTxPduid  =  LpPduIdTable->ucNoofPeriodicCon;
        for(LucIndex = DCM_ZERO;  LucIndex  <  LucMaxNumTxPduid;  LucIndex++)
        {
          if(Dcm_GaaDslPeriodicData[LucIndex].ucDataStatus  ==  DCM_PER_DATA_BUSY)
          {
            LucBusyCount++;
          }
        }
        if(LucBusyCount == DCM_ZERO)
        {
          Dcm_GblResOnPeriodicIdStatus  =  DCM_FALSE;
        }
      }
      /* Type 1*/
      #else  
      if(Dcm_GblResOnPeriodicIdStatus == DCM_TRUE)
      {
        Dcm_GblResOnPeriodicIdStatus = DCM_FALSE;
      }
      #endif /* (DCM_PROTOCOL_TRANSTYPE2  ==  STD_ON) */
      #endif /* (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE  ==  STD_ON)  */
    
      /* Check if the pre compile option DCM_RESPONSE_ON_EVENT_SERVICE is enabled */
      #if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
      /* Check if the current request under process is of ROE event */
      if(Dcm_GucResOnEventStatus == DCM_ROEONGOING)
      {
        /* Check if the previous page was transmitted successfully */
        if(LddResult == NTFRSLT_OK)
        {
          #if(DCM_ROE_QUEUE_ENABLED == STD_ON)
          /* Count up Queue Read Index */
          Dcm_DspSetQueueIndex(DCM_ROE_QUEUE_READ);
    
          /* Queue is Empty */
          if((Dcm_GddRoeQueueProcessInfo.blQueueEmpty) == DCM_TRUE)
          {
            /* Stop Inter Message Timer */
            Dcm_TimerReqFlagStatus.ucRoeInterMsgTimer = DCM_FALSE;
          }
          /* Queue is not empty */
          else
          {
            /* Restart ROE Inter-message Timer */
            DCM_START_TIMER(DCM_ROE_INTERMESSAGE_TIMER, \
            Dcm_ROE_Inter_Message_Time);
            Dcm_TimerReqFlagStatus.ucRoeInterMsgTimer = DCM_TRUE;
          }
    
          Dcm_GddRoeQueueProcessInfo.blQueueElementInProcess = DCM_FALSE;
          #else
          /* Restart ROE Inter-message Timer */
          DCM_START_TIMER(DCM_ROE_INTERMESSAGE_TIMER, \
          Dcm_ROE_Inter_Message_Time);
          Dcm_TimerReqFlagStatus.ucRoeInterMsgTimer = DCM_TRUE;
          #endif
          /* Clear Retry Counter */
          Dcm_GddRoeRetryProcessInfo.blRetryRoeEvent = DCM_FALSE;
          Dcm_GddRoeRetryProcessInfo.ucRoeTxRetryCount = DCM_ZERO;
          Dcm_GucResOnEventStatus = DCM_IDLE;
        }
        else /* NOT OK  */
        {
          /* Check Retry Mechanism is on and
            Counter is not reached at the threshold */
          if(((Dcm_ROE_Max_Number_Of_Retry) > DCM_ZERO) &&
          ((Dcm_GddRoeRetryProcessInfo.ucRoeTxRetryCount + DCM_ONE) <
                                             Dcm_ROE_Max_Number_Of_Retry + DCM_ONE))
          {
            Dcm_GddRoeRetryProcessInfo.ucRoeTxRetryCount++;
            Dcm_GddRoeRetryProcessInfo.blRetryRoeEvent = DCM_TRUE;
          }
          /* Retry Mechanism is OFF or Counter is expired */
          else
          {
            /* Reset Retry Counter */
            Dcm_GddRoeRetryProcessInfo.ucRoeTxRetryCount = DCM_ZERO;
            Dcm_GucResOnEventStatus = DCM_IDLE;
            Dcm_GddRoeRetryProcessInfo.blRetryRoeEvent = DCM_FALSE;
    
            #if(DCM_ROE_QUEUE_ENABLED == STD_ON)
            /* Count up Queue Read Index (Drop the event from queue) */
            Dcm_DspSetQueueIndex(DCM_ROE_QUEUE_READ);
    
            /* Check the queue is empty */
            if((Dcm_GddRoeQueueProcessInfo.blQueueEmpty) == DCM_TRUE)
            {
              Dcm_TimerReqFlagStatus.ucRoeInterMsgTimer = DCM_FALSE;
              Dcm_GddRoeQueueProcessInfo.blQueueElementInProcess = DCM_FALSE;
            }
            #endif
          }
          DCM_START_TIMER(DCM_ROE_INTERMESSAGE_TIMER, \
            Dcm_ROE_Inter_Message_Time);
          Dcm_TimerReqFlagStatus.ucRoeInterMsgTimer = DCM_TRUE;
        }
      }
      else if(Dcm_GucResOnEventStatus == DCM_IDLE)
      {
        #if(DCM_ROE_QUEUE_ENABLED == STD_ON)
        /* Check queue is empty */
        if((Dcm_GddRoeQueueProcessInfo.blQueueEmpty) == DCM_TRUE)
        {
          /* do nothing */
        }
        else
        {
          DCM_START_TIMER(DCM_ROE_INTERMESSAGE_TIMER, \
          Dcm_ROE_Inter_Message_Time);
          Dcm_TimerReqFlagStatus.ucRoeInterMsgTimer = DCM_TRUE;
        }
        #endif
      }
      else
      {
        /* To avoid QAC warning */
      }
      #endif /* (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) */
      /*
       * Check if the current request under process is of normal request or periodic
       * request and if the confirmation was not called during paged transmission
       */
      if ((Dcm_GblNormalReq == DCM_TRUE) 
           #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
           && (Dcm_GblResOnPeriodicIdStatus == DCM_FALSE)
           #endif
           && (Dcm_TxRespStatus.ucPagedTrans == DCM_FALSE))
      {
        /* Insert stuck protection code (#5397) by Jin 160705 begin */
        /*  Clear  the  Normal  request  status  to  FALSE  */
        Dcm_GblNormalReq = DCM_FALSE;
        /* Reset the pending response count */
        Dcm_GusMaxNoOfRespPend = DCM_ZERO;
        /* Reset the status of the RxPduId */
        Dcm_DslStatusReset();
        /* Insert stuck protection code (#5397) by Jin 160705 end */
        
        #if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
        if(Dcm_GucResOnEventStatus == DCM_ROEPENDING)
        {
          /* Set the ROE status has Ongoing */
          Dcm_GucResOnEventStatus = DCM_ROEONGOING;
    
          /* Initialize pointer to PduId table corresponding to the RxPduId */
          LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRoeRxPduId];
          /* Enter the DC */
          SchM_Enter_Dcm_RxPduIdProtection();
          /* Set the status of RxPduId */
          *(LpPduIdTable->pPduIdStatus) |= LpPduIdTable->ucPduIdStatusMask;
          /* Exit the DC */
          SchM_Exit_Dcm_RxPduIdProtection();
    
          /* Get Protocol Index */
          LucProtocolIDIndex = Dcm_GetProtocolIDIndex(LpPduIdTable->ddProtocolId);
    
          LpProtocolConfig = &Dcm_GaaProtocolConfig[LucProtocolIDIndex];
          SchM_Enter_Dcm_ProtclProtection();
           *(LpProtocolConfig->pProtocolStatus) |=  (LpProtocolConfig->ucPrtclStatusMask);
          SchM_Exit_Dcm_ProtclProtection();
          /*
           * Update the global variable for RxPduId with the ROE request
           * RxPduId
           */
          Dcm_GddRxPduId = Dcm_GddRoeRxPduId;
          /* Invoke the Dsd Indication for the pending request */
          LblNrcOccured = Dcm_DsdIndication(Dcm_GddRxPduId, DCM_FALSE, DCM_FALSE, DCM_FALSE);
          /*
           * Change the status of ROE to ongoing or FALSE based on the value
           * returned
           */
          Dcm_GucResOnEventStatus = LblNrcOccured;
        }
        #endif /*(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) */
      }
    }        
    else 
    {
      DCM_REPORT_ERROR(DCM_TX_CONFIRMATION_SID, DCM_E_INTERFACE_BUFFER_OVERFLOW);    
    }
  } 

  /* Clears flag */
  Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_FALSE;
}

/*******************************************************************************
**  Function  Name       : Dcm_GetProtocolIDIndex                             **
**                                                                            **
**  Service  ID          : NA                                                 **
**                                                                            **
**  Description          : This  function  will  give  the  protocol  index   **
**                                                                            **
** Sync/Async            : Synchronous                                        **
**                                                                            **
**  Re-entrancy          : Non-Reentrant                                      **
**                                                                            **
**  Input  Parameters    : LddProtocolId                                      **
**                                                                            **
** InOut parameter       : None                                               **
**                                                                            **
**  Output  Parameters   : LpProtocolIDIndex                                  **
**                                                                            **
**  Return  parameter    : void                                               **
**                                                                            **
**  Preconditions        : None                                               **
**                                                                            **
**  Remarks              : Global  Variable(s)  :Dcm_GaaProtocolIds           **
**                         Function(s)  invoked  :  None                      **
**                                                                            **
*******************************************************************************/
FUNC(uint8,  DCM_CODE)  Dcm_GetProtocolIDIndex(uint8  aProtocolID)
{
  uint8 iteratorProtocol;
  uint8 protocolIDIndex = DCM_SERVICE_NOT_CONFIGURED;
  
  for(
    iteratorProtocol = 0U;  
    iteratorProtocol < Dcm_Num_Protocol_Configd;  
    iteratorProtocol++)
  {
    /*  Check  the  ID  value  with  the  respective  buffer  to  get  index  */
    if (aProtocolID == Dcm_GaaProtocolIds[iteratorProtocol])
    {
      protocolIDIndex = iteratorProtocol;    
      break;
    }
  }

  return protocolIDIndex;
}

/*******************************************************************************
**  Function  Name        : Dcm_DsdValidateSecurity                           **
**                                                                            **
**  Service  ID           : NA                                                **
**                                                                            **
**  Description           : This  function  is  used  to  validate  security  **
**                                                                            **
** Sync/Async             : Synchronous                                       **
**                                                                            **
**  Re-entrancy           : Non-Reentrant                                     **
**                                                                            **
**  Input  Parameters     : LpSecLevel,  LucNoOfSec                           **
**                                                                            **
** InOut parameter        : None                                              **
**                                                                            **
**  Output  Parameters    : None                                              **
**                                                                            **
**  Return  parameter     : boolean                                           **
**                                                                            **
**  Preconditions         : None                                              **
**                                                                            **
**  Remarks               : Global  Variable(s)  : None                       **
**                          Function(s)  invoked  :  Dcm_GetSecurityLevel,    **
**                                                                            **
*******************************************************************************/
boolean Dcm_DsdValidateSecurity(
  P2CONST(uint8,  AUTOMATIC,  DCM_APPL_CONST) pSecurityLevelTable,
  uint8  numOfSecurityLevelEntry)
{
  boolean  validateResult = DCM_FALSE;

  if (pSecurityLevelTable == NULL_PTR)
  {
    /* if parameter is not configured , return true (it means N/A) */
    validateResult = DCM_TRUE;
  }
  else if (numOfSecurityLevelEntry < 1U)
  {
    /* if parameter is not configured , return true (it means N/A) */
    validateResult = DCM_TRUE;
  }
  else
  {
    Dcm_SecLevelType currentLevel = 0U;
    
    if (E_OK == Dcm_GetSecurityLevel(&currentLevel))
    {
      uint8 iteratorSecLvl;
      
      for (iteratorSecLvl = 0U; iteratorSecLvl < numOfSecurityLevelEntry; iteratorSecLvl++)
      {
        if 
        ( (pSecurityLevelTable[iteratorSecLvl] == DCM_SEC_LEV_ALL) || 
          (pSecurityLevelTable[iteratorSecLvl] == currentLevel))
        {
          validateResult = DCM_TRUE;
          break;
        }
      }
    }
  }

  return  validateResult;
}

/*******************************************************************************
**  Function  Name        : Dcm_DsdValidateSession                            **
**                                                                            **
**  Service  ID           : NA                                                **
**                                                                            **
**  Description           : This  function  is  to  validate  session         **
**                                                                            **
** Sync/Async             : Synchronous                                       **
**                                                                            **
**  Re-entrancy           : Non-Reentrant                                     **
**                                                                            **
**  Input  Parameters     : LpSesLevel,  LucNoOfSes                           **
**                                                                            **
** InOut parameter        : None                                              **
**                                                                            **
**  Output  Parameters    : None                                              **
**                                                                            **
**  Return  parameter     : boolean                                           **
**                                                                            **
**  Preconditions         : None                                              **
**                                                                            **
**  Remarks               : Global  Variable(s)  :  None                      **
**                          Function(s)  invoked :  Dcm_GetSesCtrlType,       **
**                                                                            **
*******************************************************************************/
boolean Dcm_DsdValidateSession(
  P2CONST(uint8,  AUTOMATIC,  DCM_APPL_CONST)LpSesLevel,
  uint8  LucNoOfSes)
{
  boolean  validateResult = DCM_FALSE;

  if (LpSesLevel == NULL_PTR)
  {
    /* if parameter is not configured , return true (it means N/A) */
    validateResult = DCM_TRUE;
  }
  else if (LucNoOfSes < 1U)
  {
    /* TODO: ignore the session validation 
     * but Det error code shall be reported */
    validateResult = DCM_TRUE;
  }
  else 
  {
    Dcm_SesCtrlType currentSessionLevel = 0U;
    if (E_OK == Dcm_GetSesCtrlType(&currentSessionLevel))
    {
      uint8 sessionIndex;
      for (sessionIndex = 0U; sessionIndex < LucNoOfSes; sessionIndex++)
      {
        /*  Are  all  the  session  levels  supported  for  the  service  Id  */   
        if 
        ( (DCM_ALL_SESSION_LEVEL == LpSesLevel[sessionIndex]) || 
          (currentSessionLevel == LpSesLevel[sessionIndex])
        )
        {
          validateResult = DCM_TRUE;
          break;
        }
      }    
    }
  }

  /*  return  result  */
  return  validateResult;
}

/*******************************************************************************
**  Function  Name        : Dcm_DsdValidateSubServiceId                       **
**                                                                            **
**  Service  ID           : NA                                                **
**                                                                            **
**  Description           : This  function  to  validate  the subservice id   **
**                          for session, security and mode rule               **
**                                                                            **
** Sync/Async             : Synchronous                                       **
**                                                                            **
**  Re-entrancy           : Non-Reentrant                                     **
**                                                                            **
**  Input  Parameters     : LpSubService,  LucSubfucCount,  LucSubfucion      **
**                                                                            **
** InOut parameter        : None                                              **
**                                                                            **
**  Output  Parameters    : None                                              **
**                                                                            **
**  Return  parameter     : boolean                                           **
**                                                                            **
**  Preconditions         : None                                              **
**                                                                            **
**  Remarks               : Global  Variable(s)  : None                       **
**                          Function(s)  invoked :  None                      **
**                                                                            **
*******************************************************************************/
static boolean  Dcm_DsdValidateSubServiceId(
  P2CONST(Dcm_SubServiceIdConfigType,  AUTOMATIC,  DCM_APPL_CONST) aCfgSubService, 
  uint8  aMaxSubSrv,  
  uint8  aSubSrvID,
  P2VAR(uint8,  AUTOMATIC,  DCM_APPL_DATA) aSubSrvIndex 
)
{
  boolean foundSubService = DCM_FALSE;

  if (aCfgSubService != NULL_PTR)  /*  Fix For MISRA 21.1 - BSH  */
  {
    uint8 iteratorSubSrv;
    for (iteratorSubSrv = 0U; iteratorSubSrv < aMaxSubSrv; iteratorSubSrv++)
    {
      P2CONST(Dcm_SubServiceIdConfigType,  AUTOMATIC,  DCM_APPL_CONST) subService;
      
      subService = &aCfgSubService[iteratorSubSrv];
      if (aSubSrvID == subService->ucSubServiceId)
      {
        *aSubSrvIndex = iteratorSubSrv;
        foundSubService = DCM_TRUE;
        
        break;
      }
    }
  }

  return  foundSubService;
}

/*******************************************************************************
**  Function  Name        : Dcm_DsdGetSubServiceModeRuleIndex                 **
**                                                                            **
**  Service  ID           : NA                                                **
**                                                                            **
**  Description           : This  function provides the mode rule             **
**                          index for requested subservice.                   **
**                                                                            **
** Sync/Async             : Synchronous                                       **
**                                                                            **
**  Re-entrancy           : Non-Reentrant                                     **
**                                                                            **
**  Input  Parameters     : LpSubService,  LucSubfucCount,  LucSubfucion      **
**                                                                            **
** InOut parameter        : None                                              **
**                                                                            **
**  Output  Parameters    : None                                              **
**                                                                            **
**  Return  parameter     : uint8                                             **
**                                                                            **
**  Preconditions         : None                                              **
**                                                                            **
**  Remarks               : Global  Variable(s)  :  None                      **
**                          Function(s)  invoked :  None                      **
**                                                                            **
*******************************************************************************/
FUNC(uint8,  DCM_CODE)  Dcm_DsdGetSubServiceModeRuleIndex(
P2CONST(Dcm_SubServiceIdConfigType,  AUTOMATIC,  DCM_APPL_CONST)
  LpSubService,  uint8  LucSubfucCount,  uint8  LucSubfucion)
{
  uint8 LucSearchResult;
  uint8 LucCount;
  LucSearchResult  =  DCM_MAXVALUE;
  LucCount = LucSubfucCount;

  /* Check if the pre compile option DCM_DEV_ERROR_DETECT is enabled */
  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  if (LpSubService == NULL_PTR)
  {
    /* Report to DET */
    (void)Det_ReportError (DCM_MODULE_ID, DCM_INSTANCE_ID, 
                                       DCM_SYNC_READ_DATA_SID, DCM_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /*Check  whether  subfunction  is  supported*/
    do
    {
      if(LucSubfucion  ==  LpSubService->ucSubServiceId)
      {
        #if(DCM_MODE_RULE  ==  STD_ON)
        LucSearchResult  =  LpSubService->ucsubmoderuleArrayindex;
        #endif
        LucCount  =  DCM_ZERO;
      }
      else
      {
        /* polyspace +1 MISRA-C3:17.8 [Justified:Low] "Not a defect" */
        LpSubService = &LpSubService[1u];
  
        LucCount--;
      }
  
    }while(LucCount  !=  DCM_ZERO);
  }
  
  /*  return  result  */
  return  LucSearchResult;
}

/*******************************************************************************
** Function Name       : Dcm_DsdCancelOperation                               **
**                                                                            **
** Service ID          : NA                                                   **
**                                                                            **
** Description         : This function is used to stop the current active     **
**                       service when max number of pending responses         **
**                       exceeds configured limit                             **
**                                                                            **
** Sync/Async          : Synchronous                                          **
**                                                                            **
** Re-entrancy         : Non-Reentrant                                        **
**                                                                            **
** Input Parameters    : None                                                 **
**                                                                            **
** InOut parameter     : None                                                 **
**                                                                            **
** Output Parameters   : None                                                 **
**                                                                            **
** Return parameter    :  void                                                **
**                                                                            **
** Preconditions       : Dcm_Init should be called before calling this API.   **
**                                                                            **
** Remarks             : Global Variable(s) : Dcm_GddOpStatus ,               **
**                       Dcm_MemServicePendingStatus , Dcm_GpMsgContext    **
**                       Dcm_DcmUpLoadCall , Dcm_GblDownLoadActive            **
**                       Dcm_GblDIDRangePresent , Dcm_GusDataIdentifier       **
**                       Dcm_GusDIDIndexVal, Dcm_GucInOutParameter            **
**                       Function Invoked : None                              **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DsdCancelOperation(void)
{
  P2VAR(Dcm_RequestContextType, AUTOMATIC, DCM_APPL_DATA) requestContext; 
  
  requestContext = Dcm_DsdInternal_GetRequestContextByRxPduId(Dcm_GddRxPduId);
  if (NULL_PTR == requestContext)
  {
    /* DET Error */
  }
  else if (DCM_E_PENDING == requestContext->rct_RequestResult)
  {        
    Dcm_DiagnosticSerivceDispatch(DCM_CANCEL, requestContext);
  }
  else
  {
  }

  /* Update Dcm_GddOpStatus */
  Dcm_GddOpStatus = DCM_CANCEL;

  /* else */
  
  /* TODO : Shall be redesigned , running service is only one
  switch (sid)
  case read : cancel if (in total != true) break;
  case write : cancel if (in total != true) break; */
  #if(DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
  /* Check for DCM_E_PENDING */
  if(Dcm_MemServicePendingStatus.ucReadMemPendingStatus ==  DCM_TRUE)
  {
    /* Invoke internal function to cancel active request */
    (void)Dcm_DcmReadMemoryCall(&Dcm_GstMsgContext);
  }
  #endif

  #if(DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
  if(Dcm_MemServicePendingStatus.ucWriteMemPendingStatus == DCM_TRUE)
  {
    /* Invoke internal function to cancel active request */
    (void)Dcm_DcmWriteMemoryCall(&Dcm_GstMsgContext);
  }
  #endif

  #if(DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON)
  if(Dcm_MemServicePendingStatus.ucDlPendingStatus == DCM_TRUE)
  {
    /* Invoke internal function to cancel active request */
    (void)Dcm_DcmDownLoadCall(&Dcm_GstMsgContext);
  }
  #endif

  #if(DCM_REQUEST_UPLOAD_SERVICE == STD_ON)
  if(Dcm_MemServicePendingStatus.ucUlPendingStatus == DCM_TRUE)
  {
    /* Invoke internal function to cancel active request */
    (void)Dcm_DcmUpLoadCall(&Dcm_GstMsgContext);
  }
  #endif

  #if(DCM_TRANSFER_DATA_SERVICE == STD_ON)
  if(Dcm_MemServicePendingStatus.ucTransferDataPendingStatus == DCM_TRUE)
  {
    if(Dcm_GblDownLoadActive == DCM_TRUE)
    {
      #if(DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON)
      /* Invoke internal function to cancel active request */
      (void)Dcm_DownLoadTransferCall(&Dcm_GstMsgContext);
      #endif
    }
    else
    {
      #if(DCM_REQUEST_UPLOAD_SERVICE == STD_ON)
      /* Invoke internal function to cancel active request */
      (void)Dcm_UpLoadTransferCall(&Dcm_GstMsgContext);
      #endif
    }
  }
  #endif
  
  #if(DCM_TRANSFER_EXIT_SERVICE == STD_ON)
  if(Dcm_MemServicePendingStatus.
  ucTransferExitPendingStatus == DCM_TRUE)
  {
    /* Invoke internal function to cancel active request */
    (void)Dcm_RequestTransferExitCall(&Dcm_GstMsgContext);
  }
  #endif
  
  #if(DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
  if(Dcm_ServicePendingStatus.ucWriteDataByIdPendingStatus == DCM_TRUE)
  {
    if((DCM_ZERO != Dcm_Num_Of_DcmDspDidRangeConfig) &&
                                           (DCM_TRUE == Dcm_GblDIDRangePresent))
    {
      /* Invoke internal function */
      Dcm_DspWriteDidRangeData(&Dcm_GstMsgContext, Dcm_GusDataIdentifier,
                                                            Dcm_GusDIDIndexVal);
    }
    else
    {
      Dcm_DcmWriteDataByIdentifierCall(&Dcm_GstMsgContext, Dcm_GusDIDIndexVal);
    }
    Dcm_ServicePendingStatus.ucWriteDataByIdPendingStatus = DCM_FALSE;
  }
  #endif
  
  #if(DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
  if(Dcm_ServicePendingStatus.ucReadDataPendingStatus == DCM_TRUE)
  {
    Dcm_DspInternal_DcmReadDataByIdentifier(DCM_CANCEL, &Dcm_GstMsgContext);
  }
  #endif
  
  #if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
  if ((Dcm_ServicePendingStatus.ucIocontrolPendingStatus == DCM_TRUE) || 
      (Dcm_ServicePendingStatus.ucIoCtrlReadCdtChkPendingStatus == DCM_TRUE) ||
    (Dcm_MemServicePendingStatus.ucIoCtrlReadDataPendingStatus == DCM_TRUE))
  {
    (void)Dcm_DspInternal_DcmInputOutputControlByIdentifier(
      DCM_CANCEL, Dcm_GucInOutParameter, &Dcm_GaaDIDParaConfig[Dcm_GusDIDIndexVal], &Dcm_GstMsgContext);

    Dcm_ResetDIDOpStatus();  
    Dcm_ServicePendingStatus.ucIocontrolPendingStatus = DCM_FALSE;
    Dcm_ServicePendingStatus.ucIoCtrlReadCdtChkPendingStatus = DCM_FALSE;
    Dcm_MemServicePendingStatus.ucIoCtrlReadDataPendingStatus = DCM_FALSE;
  }
  #endif

  #if(DCM_ROUTINECONTROL_SERVICE == STD_ON)
  if(Dcm_ServicePendingStatus.ucRoutinePendingStatus == DCM_TRUE)
  {
    (void)Dcm_RoutineSignalFunction((uint8)Dcm_GucRoutineSubFunction, Dcm_GusRoutineIdentifier);
    Dcm_ServicePendingStatus.ucRoutinePendingStatus = DCM_FALSE;
  }
  #endif
  
  #if(DCM_DSP_SECURITY_SERVICE == STD_ON)
  if ((Dcm_DspServiceProcessingSts.ucSecSeedReqPending == DCM_TRUE) || 
      (Dcm_DspServiceProcessingSts.ucSecCompareKeyReqPending == DCM_TRUE))
  {
    if 
    ( (Dcm_GstMsgContext.reqData != NULL_PTR) &&
      (Dcm_GstMsgContext.resData != NULL_PTR) && 
      (Dcm_GucDspStIndex < Dcm_Num_Of_Security_Level_Config)
    )
    {
      Dcm_NegativeResponseCodeType LddErrorCode; /* Dummy */
      uint8 LucSecLvl = Dcm_GstMsgContext.reqData[DCM_ZERO] & DCM_SUBFUNCTION_MASK;
  
      (void)Dcm_DspInternal_DcmSecurityAccess(
        DCM_CANCEL, &Dcm_GaaSecurityLevConfig[Dcm_GucDspStIndex], Dcm_GstMsgContext.resData, &LddErrorCode, LucSecLvl);
      Dcm_DspServiceProcessingSts.ucSecSeedReqPending = DCM_FALSE;
      Dcm_DspServiceProcessingSts.ucSecCompareKeyReqPending = DCM_FALSE;
    }    
  }
  #endif

  #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  if(Dcm_ServicePendingStatus.ucReadPerDIDPendingStatus == DCM_TRUE)
  {
    (void)Dcm_DspInternal_DcmReadDataByPeriodicIdentifier(DCM_CANCEL, &Dcm_GstMsgContext);
    Dcm_ServicePendingStatus.ucReadPerDIDPendingStatus = DCM_FALSE;
  }
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_DsdInternal_GetMsgTxBuffer                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function returns the address of tx buffer for  **
**                        Tx PDU.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : aMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              :                                                     **
********************************************************************************/
FUNC(Dcm_MsgType, DCM_CODE) 
Dcm_DsdInternal_GetMsgTxBuffer(
  PduIdType aPduId,
  Dcm_BufferKindType aBufferKind
)
{
  /* Local pointer for the Tx buffer */
  Dcm_MsgType txMsgPtr = NULL_PTR;

  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  /*  for Outof bound -0424 bsh, -2015.06.16 yj.yun */
  if (aPduId >=  Dcm_Num_Of_PduidTableConfig) 
  {
    DCM_REPORT_ERROR(DCM_COPY_TXDATA_SID, DCM_E_PARAM);  
  }
  else
  #endif
  {
    /* Initialize Tx buffer Id configured for RxPduID */
    uint8 txBufferIndex =0;
    boolean checkedBuffer = DCM_FALSE;
    
    switch(aBufferKind)
    {
      case DCM_BUFFER_KIND_TX:
        txBufferIndex = Dcm_GaaPduIdTableConfig[aPduId].ucTxBufferId;
        checkedBuffer = DCM_TRUE;
        break;
        
      case DCM_BUFFER_KIND_RX:              
        break;

      #if ((DCM_RESPONSE_ON_EVENT_SERVICE  ==  STD_ON) && \
       (DCM_PROTOCOL_TRANSTYPE2  ==  STD_ON))
      case DCM_BUFFER_KIND_TX_ROE:
        #if(DCM_DEV_ERROR_DETECT == STD_ON)
        if (NULL_PTR == Dcm_GaaPduIdTableConfig[aPduId].pRoeTxId)
        {
          DCM_REPORT_ERROR(DCM_COPY_TXDATA_SID, DCM_E_PARAM_POINTER);  
        }
        else
        #endif
        {
          if (NULL_PTR != Dcm_GaaPduIdTableConfig[aPduId].pRoeTxId)
          {
            txBufferIndex = Dcm_GaaPduIdTableConfig[aPduId].pRoeTxId->ucRoeTxBufferId;
            checkedBuffer = DCM_TRUE;
          }
        }
        break;
      #endif
      case DCM_BUFFER_KIND_TX_PERIODIC:   
        #if (\
          (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) && \
          (DCM_PROTOCOL_TRANSTYPE2 == STD_ON))        
        if(Dcm_GaaPduIdTableConfig[aPduId].pPeriodicTxId != NULL_PTR)
        {
          SchM_Enter_Dcm_ProtclProtection();
          txMsgPtr = Dcm_GaaDslPeriodicData[Dcm_IndexOfDslPeriodicData].pPerData;
          SchM_Exit_Dcm_ProtclProtection();
        }        
        else
        #endif
        {
          /* Initialize the Rx buffer Id for periodic event request */
          txBufferIndex = Dcm_GaaPduIdTableConfig[aPduId].ucTxBufferId;
          checkedBuffer = DCM_TRUE;
        }
        break;
        
      default:
    /* Do Nothing */
    break;
    }
    
    if (DCM_TRUE == checkedBuffer)
    {
      #if(DCM_DEV_ERROR_DETECT == STD_ON)
      if (txBufferIndex >= Dcm_Num_Of_Buffer_Config)
      {
        DCM_REPORT_ERROR(DCM_COPY_TXDATA_SID, DCM_E_PARAM);  
      }
      else
      #endif
      {
        /* Initialize pointer to the Tx buffer area */
        txMsgPtr = Dcm_GaaBufferConfig[txBufferIndex].pBufferArea;
      }
    }
  }

  return txMsgPtr;
}

FUNC(P2VAR(Dcm_RequestContextType, AUTOMATIC, DCM_APPL_DATA), DCM_CODE) 
Dcm_DsdInternal_GetRequestContextByRxPduId(PduIdType DcmRxPduId)
{
  P2VAR(Dcm_RequestContextType, AUTOMATIC, DCM_APPL_DATA) requestContext = NULL_PTR;

  if (DcmRxPduId < Dcm_Num_Of_PduidTableConfig)
  {
    uint8 indexOfProtocol;    

    /* Get Protocol Index */
    indexOfProtocol = Dcm_GetProtocolIDIndex(Dcm_GaaPduIdTableConfig[DcmRxPduId].ddProtocolId);
    if (indexOfProtocol < Dcm_Num_Protocol_Configd)
    {    
      requestContext = &Dcm_RequestContext[indexOfProtocol];
    }
  }
        
  return requestContext;
}

FUNC(void, DCM_CODE) 
Dcm_DsdInternal_InitRequestContext(void)
{
  uint8 reqCtxIdx;

  for (reqCtxIdx = 0U; reqCtxIdx < Dcm_Num_Protocol_Configd; reqCtxIdx++)
  {
    Dcm_RequestContext[reqCtxIdx].rct_MsgContext = NULL_PTR;
    Dcm_RequestContext[reqCtxIdx].rct_ServiceIndex = (uint8)0xFF;
    Dcm_RequestContext[reqCtxIdx].rct_SubFunctionId = (uint8)0xFF;  
    Dcm_RequestContext[reqCtxIdx].rct_RxPduId = (uint8)0xFF;  
    Dcm_RequestContext[reqCtxIdx].rct_RequestResult = E_NOT_OK;
  }
}

/*******************************************************************************
**  Function  Name        : Dcm_DsdInternal_GetSubFunctionByMsgContext        **
**                                                                            **
**  Service  ID           : NA                                                **
**                                                                            **
**  Description           : This  function provides the subfunction           **
**                          information of request in progressing             **
**                                                                            **
**  Sync/Async            : Synchronous                                       **
**                                                                            **
**  Re-entrancy           : Non-Reentrant                                     **
**                                                                            **
**  Input  Parameters     : pMsgContext                                       **
**                                                                            **
**  InOut parameter       : None                                              **
**                                                                            **
**  Output  Parameters    : None                                              **
**                                                                            **
**  Return  parameter     : Dcm_SubServiceIdConfigType *                      **
**                                                                            **
**  Preconditions         : None                                              **
**                                                                            **
**  Remarks               :                                                   **
*******************************************************************************/
FUNC(P2CONST(Dcm_SubServiceIdConfigType, AUTOMATIC, DCM_CONST), DCM_CODE) 
Dcm_DsdInternal_GetSubFunctionByMsgContext(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2CONST(Dcm_SubServiceIdConfigType, AUTOMATIC, DCM_CONST) cfgSubSerivce = NULL_PTR;

  if (NULL_PTR != pMsgContext)
  {
    P2VAR(Dcm_RequestContextType, AUTOMATIC, DCM_APPL_DATA) requestContext;
    
    requestContext = Dcm_DsdInternal_GetRequestContextByRxPduId(pMsgContext->dcmRxPduId);        
    if ((NULL_PTR != requestContext) && (requestContext->rct_ServiceIndex < Dcm_Num_Of_SidConfig))
    {
      P2CONST(Dcm_ServiceIdConfigType, AUTOMATIC, DCM_CONST) cfgSid = NULL_PTR;

       /* polyspace +1 DEFECT:USELESS_IF [Justified:Low] "Not a defect" */
      if (requestContext->rct_ServiceIndex < Dcm_Num_Of_SidConfig)
      {      
        cfgSid =  &Dcm_GaaSIdConfig[requestContext->rct_ServiceIndex];  
        if ((NULL_PTR != cfgSid->pSubServiceId) && (DCM_TRUE == cfgSid->blSubFunctionAvailable))
        {
          uint8 iteratorSubSrv;
          for (iteratorSubSrv = 0U; iteratorSubSrv < cfgSid->ucSubServiceCount; iteratorSubSrv++)
          {                
            if (requestContext->rct_SubFunctionId == cfgSid->pSubServiceId[iteratorSubSrv].ucSubServiceId)
            {
              cfgSubSerivce = &cfgSid->pSubServiceId[iteratorSubSrv];
              break;
            }
          }
        }
      }
    }
  }

  return cfgSubSerivce;
}

/*******************************************************************************
**  Function  Name        : Dcm_DsdInternal_GetProcotocolByRxPduId            **
**                                                                            **
**  Service  ID           : NA                                                **
**                                                                            **
**  Description           : This  function provides the protocol              **
**                          information of request in progressing             **
**                                                                            **
**  Sync/Async            : Synchronous                                       **
**                                                                            **
**  Re-entrancy           : Non-Reentrant                                     **
**                                                                            **
**  Input  Parameters     : pMsgContext                                       **
**                                                                            **
**  InOut parameter       : None                                              **
**                                                                            **
**  Output  Parameters    : None                                              **
**                                                                            **
**  Return  parameter     : Dcm_ProtocolConfig *                              **
**                                                                            **
**  Preconditions         : None                                              **
**                                                                            **
**  Remarks               :                                                   **
*******************************************************************************/
FUNC(P2CONST(Dcm_ProtocolConfig, AUTOMATIC, DCM_CONST), DCM_CODE) 
Dcm_DsdInternal_GetProcotocolByRxPduId(
  PduIdType DcmRxPduId)
{
  P2CONST(Dcm_ProtocolConfig, AUTOMATIC, DCM_CONST) protocolCfg = NULL_PTR;
  
  if (DcmRxPduId < Dcm_Num_Of_PduidTableConfig)
  {
    uint8 protoIndex = 0xFFU;

    protoIndex = Dcm_GetProtocolIDIndex(Dcm_GaaPduIdTableConfig[DcmRxPduId].ddProtocolId);
    if (protoIndex < Dcm_Num_Protocol_Configd)
    {
      /* Get the Pointer to the corresponding protocol structure */
      protocolCfg = &Dcm_GaaProtocolConfig[protoIndex];
    }
  }

  return protocolCfg;
}

/* FIXME : uint8->uint16*/
FUNC(P2CONST(Dcm_DiagSessionConfigType, AUTOMATIC, DCM_APPL_CONST), DCM_CODE) 
Dcm_DsdInternal_GetSessionCfg(
  P2CONST(Dcm_ProtocolConfig, AUTOMATIC, DCM_APPL_CONST) protocolCfg,
  Dcm_SesCtrlType requestSession,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) outSessionIndex)
{ 
  P2CONST(Dcm_DiagSessionConfigType, AUTOMATIC, DCM_APPL_CONST) sessionCfg = NULL_PTR;

  #if(DCM_DSP_SESSION_REF == STD_ON)
  if (NULL_PTR != protocolCfg)
  {    
    uint8 sessionIndex = protocolCfg->ucSesTableIndex;
    /* if sessionLimit is overflowed*/
    uint8 sessionLimit = protocolCfg->ucSesTableIndex + protocolCfg->ucSesCntInTable;

    if (sessionLimit <= Dcm_Num_Of_Diag_Session_Config)    
    {
      while (sessionIndex < sessionLimit)
      {
        if (requestSession == Dcm_GaaDiagSessionConfig[sessionIndex].ddSesCtrlLevel)
        {
          sessionCfg = &Dcm_GaaDiagSessionConfig[sessionIndex];
          if (NULL_PTR != outSessionIndex)
          {
            *outSessionIndex = sessionIndex;
          }
          break;
        }
        sessionIndex++;
      }
    }
  }
  #endif
  return sessionCfg;
}

FUNC(  P2CONST(Dcm_BufferConfig, AUTOMATIC, DCM_APPL_CONST), DCM_CODE) 
Dcm_DsdInternal_GetBuffferConfig(PduIdType DcmRxPduId)
{
  P2CONST(Dcm_BufferConfig, AUTOMATIC, DCM_APPL_CONST) cfgBuffer = NULL_PTR;

  if (DcmRxPduId < Dcm_Num_Of_PduidTableConfig)
  {
    if (Dcm_GaaPduIdTableConfig[DcmRxPduId].ucRxBufferId < Dcm_Num_Of_Buffer_Config)
    {
      /* Initialize pointer to corresponding buffer Id structure */
      cfgBuffer = &Dcm_GaaBufferConfig[Dcm_GaaPduIdTableConfig[DcmRxPduId].ucRxBufferId];
    }
  }
  return cfgBuffer;
}

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Nesting of control structures to achieve better throughput. */
/* polyspace:end<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */
/* polyspace:end<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:end<RTE: NIP : Not a defect : No Action Planned > pointer is not null */
/* polyspace:end<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
/* polyspace:end<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
/* polyspace-end MISRA-C3:20.7 [Justify with annotations:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace-end MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:10.4 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:OUT_BOUND_PTR [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-end CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */

/*******************************************************************************
**                      End  of  File                                         **
*******************************************************************************/

