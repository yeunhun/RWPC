/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Com.c                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of initialization and its functionality.            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 2.7.3     18-Jun-2021   SM Kwon     Internal Redmine #30089                **
** 2.7.1     07-Jan-2021   SM kwon     Internal Redmine #27557                **
** 2.6.0     10-Sep-2020   SM Kwon     Internal Redmine #25614                **
** 2.5.0     19-Feb-2020   SM Kwon     Internal Redmine #21472                **
** 2.4.2     22-Apr-2019   SM Kwon     Internal Redmine #16805                **
** 2.4.0     18-Dec-2018   SM Kwon     Internal Redmine #14067, #15053        **
** 2.2.3     08-Dec-2017   Chan Kim    Internal Redmine #10849, #10851        **
** 2.2.0     16-Apr-2017   Chan Kim    Internal Redmine #7707, #7525          **
** 2.1.7     30-Nov-2016   Chan Kim    Internal Redmine #6807                 **
** 2.1.0     25-May-2016   Chan Kim    Internal Redmine #4998                 **
** 2.0.10    25-Feb-2016   Chan Kim    Internal Redmine #4250                 **
** 2.0.3     24-Nov-2015   Chan Kim    Internal Redmine #3544, #3535          **
** 1.0.0     29-Apr-2013   Autron      Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Com.h"         /* Com header file */
#include "SchM_Com.h"     /* SchM Com header file */
#include "Com_Error.h"    /* Com Error header file */
#include "Com_IpduGrp.h"  /* Com Ipdu Group header file */
#if(COM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"         /* Det header file */
#endif
#include "Com_Init.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define COM_C_AR_RELEASE_MAJOR_VERSION  4
#define COM_C_AR_RELEASE_MINOR_VERSION  0
#define COM_C_AR_RELEASE_REVISION_VERSION  3

/* Software Version Information */
#define COM_C_SW_MAJOR_VERSION  2
#define COM_C_SW_MINOR_VERSION  7

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (COM_AR_RELEASE_MAJOR_VERSION != COM_C_AR_RELEASE_MAJOR_VERSION)
  #error "Com.c : Mismatch in Com Specification Major Version"
#endif

#if (COM_AR_RELEASE_MINOR_VERSION != COM_C_AR_RELEASE_MINOR_VERSION)
  #error "Com.c : Mismatch in Com Specification Minor Version"
#endif

#if (COM_AR_RELEASE_REVISION_VERSION != COM_C_AR_RELEASE_REVISION_VERSION)
  #error "Com.c : Mismatch in Com Specification Revision Version"
#endif

#if (COM_SW_MAJOR_VERSION != COM_C_SW_MAJOR_VERSION)
  #error "Com.c : Mismatch in Com Software Major Version"
#endif

#if (COM_SW_MINOR_VERSION != COM_C_SW_MINOR_VERSION)
  #error "Com.c : Mismatch in Com Software Minor Version"
#endif
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* polyspace:begin <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
/*******************************************************************************
** Function Name        : Com_Init                                            **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This service initializes internal and external      **
**                        interfaces and variables of the AUTOSAR COM module  **
**                        layer for the further processing. After calling this**
**                        the inter-ECU communication is still disabled.      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : config                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GddComStatus           **
**                                                 Com_GaaTxIpduCountVal      **
**                                                 Com_GaaRxIpduCountVal      **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Init
                     (P2CONST(Com_ConfigType, AUTOMATIC, COM_CONST) config)
{
  #if(COM_TX_IPDU == STD_ON)
  uint16 LusNoOfTxIpdu;
  #endif
  #if(COM_TX_IPDU_NOTINCL_COUNT > COM_MACRO_ZERO)
  uint16 LusNoOfTxIpduNotIncl = 0;
  PduIdType LddTxPduId;
  #endif
  #if(COM_RX_IPDU_NOTINCL_COUNT > COM_MACRO_ZERO)
  uint16 LusNoOfRxIpduNotIncl = 0;
  PduIdType LddRxPduId;
  #endif

  /* Initialize the Com Module */
  Com_GddComStatus = COM_INIT;
  #if(COM_RX_IPDU == STD_ON)
  Com_GusRxWriteIndex = (uint16)COM_ZERO;
  #if(COM_RX_IPDU_HISTORY_LIST > 1)
  Com_GusRxReadStatus = (uint16)COM_ZERO;
  #endif
  #endif
  
  COM_UNUSED_PTR(config);

  #if(COM_TX_IPDU == STD_ON)
  LusNoOfTxIpdu = COM_TX_IPDU_COUNT;

  while(LusNoOfTxIpdu > 0)
  {
    Com_GaaTxIpduStatusBit[LusNoOfTxIpdu-1] |= COM_TX_TMS_STATUS_MASK;
    LusNoOfTxIpdu --;
  }
  #if(COM_TX_IPDU_NOTINCL_COUNT > COM_MACRO_ZERO)
  while(LusNoOfTxIpduNotIncl < COM_TX_IPDU_NOTINCL_COUNT)
  {
    LddTxPduId = Com_GaaTxIpduNotIncl[LusNoOfTxIpduNotIncl++];
    Com_StartTxIpdu(LddTxPduId, COM_TRUE);
  }
  #endif /* End of #if(COM_TX_IPDU_NOTINCL_COUNT > COM_MACRO_ZERO) */
  #endif /* End of #if(COM_TX_IPDU == STD_ON)*/

  #if(COM_RX_IPDU == STD_ON)
  #if(COM_RX_IPDU_NOTINCL_COUNT > COM_MACRO_ZERO)
  while(LusNoOfRxIpduNotIncl < COM_RX_IPDU_NOTINCL_COUNT)
  {
    LddRxPduId = Com_GaaRxIpduNotIncl[LusNoOfRxIpduNotIncl++];
    Com_StartRxIpdu(LddRxPduId, COM_TRUE);
  }
  #endif /* End of #if(COM_RX_IPDU == STD_ON) */
  #endif /* End of #if(COM_RX_IPDU_NOTINCL_COUNT > COM_MACRO_ZERO) */
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_DeInit                                          **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : This service stops the inter-ECU communication. All **
**                        started I-PDU groups are stopped and have to be     **
**                        started again, if needed, after Com_Init is called. **
**                        By a call to Com_DeInit the AUTOSAR COM module is   **
**                        put into an not initialized state.                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaIpduGrpEnStatus     **
**                                                 Com_GaaIpduGrpDmStatus     **
**                                                 Com_GaaTxIpduStatusBit     **
**                                                 Com_GaaTxIpduStatus        **
**                                                 Com_GaaRxIpduStatus        **
**                                                 Com_GaaRxDmStatus          **
**                                                 Com_GddComStatus           **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_DeInit(void)
{
  uint8 LucIpduGroupStsCount;
  PduIdType LddIpduCount;
  LucIpduGroupStsCount = COM_IPDU_GRP_VECTOR_SIZE;
  /* Loop for all Ipdu Group */
  do
  {
    LucIpduGroupStsCount--;
    Com_GaaIpduGrpEnStatus[LucIpduGroupStsCount] = COM_ZERO;
    Com_GaaIpduGrpDmStatus[LucIpduGroupStsCount] = COM_ZERO;

  }while(LucIpduGroupStsCount != COM_ZERO);

  #if(COM_TX_IPDU == STD_ON)
  LddIpduCount = (PduIdType) COM_TX_IPDU_COUNT;
  do
  {
        
    --LddIpduCount;
    Com_GaaTxIpduStatusBit[LddIpduCount] = (uint16) COM_ZERO;
   
    Com_GaaTxIpduStatus[LddIpduCount] = (uint16) COM_ZERO;

  }while(LddIpduCount != (PduIdType)COM_ZERO);
  #endif

  #if(COM_RX_IPDU == STD_ON)
  LddIpduCount = (PduIdType)COM_RX_IPDU_COUNT;
  do
  {
    --LddIpduCount;
    Com_GaaRxIpduStatus[LddIpduCount] = (uint16)COM_ZERO;
  }while(LddIpduCount != (PduIdType)COM_ZERO);
  #endif
  
  #if((COM_RX_IPDU_DM == STD_ON) || \
   (COM_RX_SIGNAL_UBDM == STD_ON) || \
   (COM_RX_SIGGROUP_UBDM == STD_ON))
  LddIpduCount = (PduIdType)COM_RX_IPDU_DM_COUNT;
  do
  {
    --LddIpduCount;
    
    Com_GaaRxDmStatus[LddIpduCount] = (uint16)COM_ZERO;

  }while(LddIpduCount != (PduIdType)COM_ZERO);
  #endif

  /* Set the Com module status variable to uninitialized */
  Com_GddComStatus = COM_UNINIT;
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_GetVersionInfo                                  **
**                                                                            **
** Service ID           : 0x09                                                **
**                                                                            **
** Description          : This function returns the version information of the**
**                        Com Module.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
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
**                        Function(s) invoked    : Det_ReportError()          **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:D4.14 :: Not a defect Justify with annotations> Pointer is not a NULL and valid */
#if(COM_VERSIONINFO_API == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_GetVersionInfo
              (P2VAR(Std_VersionInfoType, AUTOMATIC, COM_VAR) versioninfo)
{
  /* #7707 */
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  uint8 LucReturnValue;
  /* Initialize DET error flag to E_OK */
  LucReturnValue = (uint8)E_OK; 
  /* Check whether version information is equal to NULL */
  COM_DET_COMMON_PTR_CHECK_FLAG(versioninfo, COMSERVICEID_GETVERSIONINFO);
  if(LucReturnValue == (uint8)E_OK)
  #endif
  {
    /* Copy the vendor ID */
    versioninfo->vendorID = COM_VENDOR_ID;
    /* Copy the module ID */
    versioninfo->moduleID = COM_MODULE_ID;
    /* Copy software major version */
    versioninfo->sw_major_version = (uint8)COM_SW_MAJOR_VERSION;
    /* Copy software minor version */
    versioninfo->sw_minor_version = (uint8)COM_SW_MINOR_VERSION;
    /* Copy software patch version */
    versioninfo->sw_patch_version = (uint8)COM_SW_PATCH_VERSION;
  }
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/* polyspace:end<MISRA-C3:D4.14 :: Not a defect Justify with annotations> Pointer is not a NULL and valid */
/*******************************************************************************
** Function Name        : Com_GetStatus                                       **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : This function returns the Returns the status of the **
**                        COM module.                                         **
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
** Return parameter     : Com_StatusType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GddComStatus           **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(Com_StatusType, COM_CODE) Com_GetStatus(void)
{
  return Com_GddComStatus;
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_GetConfigurationId                              **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : This function Provides the unique identifier of the **
**                        configuration.                                      **
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
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(uint32, COM_CODE) Com_GetConfigurationId(void)
{
  return COM_CONFIGURATION_ID;
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace:end <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
