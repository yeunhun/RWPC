/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: IoHwAb_McuSpecific.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_McuSpecificControlIBE                                  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By         Description                             **
********************************************************************************
** 1.15.0.2  09-Sep-2021   Yangjin    #31974                                  **
** 1.10.1    04-Aug-2020   Yangjin    #24902                                  **
** 1.7.1     26-Feb-2020   Yangjin    #21555                                  **
** 1.0.1     16-SEP-2015   Jongyoung  1.MISRA-C Rule violation fix            **
** 1.0.0     01-Jun-2015   Jongyoung  Initial version                         **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_DigDir.h"
#include "IoHwAb_Config.h"
#include "Rte_Type.h"
#include "HwResource.h"
#include "Rte_IoHwAb.h"
#include "SchM_IoHwAb.h"

#if defined(IOHWAB_MCAL_FREESCALE_MPC560XB)
#include "Reg_eSys_SIUL.h"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* polyspace-begin RTE:UNR [Justified:Low] "This if statement is needed for the validation." */
/*polyspace:begin<MISRA-C:10.3:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace:begin<MISRA-C:11.3:Not a defect:Justify with annotations> No Impact of this rule violation*/
/* polyspace-begin RTE:IDP RTE:NIV [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-begin MISRA-C3:18.1 [Justified:Unset] "Not a defect" */
/* polyspace-begin DEFECT:DEAD_CODE MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on the configuration." */
/*******************************************************************************
** Function Name        : IoHwAb_McuSpecificControlIBE                        **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service updates the PortPin's IBE value        **
**                        for Bolero (leackage current issues)                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : PortGroup - IOHWAB_PORT_X [X is A~H]                **
**                        PinConfig - 0x0000~0xFFFF (ex. 0x0003 -> pin0, pin1)**
**                        Level     - 1(Set) or 0(Clear)                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Result                                              **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : none                       **
**                        Function(s) invoked    : none                       **
*******************************************************************************/
#if defined(IOHWAB_MCAL_FREESCALE_MPC560XB)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_McuSpecificControlIBE(IoHwAb_IndexType PortGroup,
IoHwAb_IndexType PinConfig, IoHwAb_LevelType Level )
{
  IoHwAb_IndexType LucIdx = 0U;
  Std_ReturnType LddError = (Std_ReturnType)E_OK;
  IoHwAb_IndexType LucPinConfig  = 0U;
  IoHwAb_IndexType LucPinMaskSet = 0xFFFFU;  
   

  #if HWRESOURCE_PACKAGE(HWRESOURCE_LQFP64)
    if (PortGroup == IOHWAB_PORT_C)
    {
      LucPinMaskSet = 0x07FFU;
    }
    else if ( (PortGroup == IOHWAB_PORT_D) || (PortGroup == IOHWAB_PORT_E) ||
              (PortGroup == IOHWAB_PORT_F) || (PortGroup == IOHWAB_PORT_G) ||
              (PortGroup == IOHWAB_PORT_H) || (PortGroup == IOHWAB_PORT_I) ||
              (PortGroup == IOHWAB_PORT_J) )
    {
       LddError = (Std_ReturnType)E_NOT_OK;      
    }

  #elif HWRESOURCE_PACKAGE(HWRESOURCE_LQFP100)
    if (PortGroup == IOHWAB_PORT_E)
    {
      LucPinMaskSet = 0x1FFFU;
    }
    else if (PortGroup == IOHWAB_PORT_H)
    {
      LucPinMaskSet = 0x0600U;
    }
    else if ( (PortGroup == IOHWAB_PORT_F) || (PortGroup == IOHWAB_PORT_G) ||
              (PortGroup == IOHWAB_PORT_I) || (PortGroup == IOHWAB_PORT_J) )
    {
       LddError = (Std_ReturnType)E_NOT_OK;      
    }
  #elif HWRESOURCE_PACKAGE(HWRESOURCE_LQFP144)
    if (PortGroup == IOHWAB_PORT_H)
    {
      LucPinMaskSet = 0x07FFU;
    }
    else if ( (PortGroup == IOHWAB_PORT_I) || (PortGroup == IOHWAB_PORT_J) )
    {
       LddError = (Std_ReturnType)E_NOT_OK;      
    }
  #endif

  SchM_Enter_IoHwAb_IoHwAbProtection();
  if((Std_ReturnType)LddError != (Std_ReturnType)E_OK)
  {
    SchM_Exit_IoHwAb_IoHwAbProtection();
    #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
      (uint8)IOHWAB_MCUSPECIFIC_SID, (uint8)IOHWAB_E_DET_WRONG_PARAM);
    #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
    #if (IOHWAB_USE_DEM_EVENT == STD_ON)
    Dem_ReportErrorStatus(IOHWAB_E_WRONG_PARAM, DEM_EVENT_STATUS_FAILED);
    #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
  }
  else
  {
    
    LucPinConfig = PinConfig & LucPinMaskSet;  
    for (LucIdx = 0U; LucIdx < 16U ; LucIdx++)
    {
      if ( (LucPinConfig & 0x01U) != 0U)
      {
        if ( Level == 1U)
        {
           REG_BIT_SET16(SIUL_PCR(PortGroup + LucIdx), SIUL_PCR_IBE);
        }
        else
        {
           REG_BIT_CLEAR16(SIUL_PCR(PortGroup + LucIdx), SIUL_PCR_IBE);
        }
      }
      LucPinConfig = LucPinConfig >> 1;
    }

    SchM_Exit_IoHwAb_IoHwAbProtection();  
  }  
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif
/* polyspace-end RTE:UNR [Justified:Low] "This if statement is needed for the validation." */
/*polyspace:end<MISRA-C:10.3:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace:end<MISRA-C:11.3:Not a defect:Justify with annotations> No Impact of this rule violation*/
/* polyspace-end RTE:IDP RTE:NIV [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-end MISRA-C3:18.1 [Justified:Unset] "Not a defect" */
/* polyspace-end DEFECT:DEAD_CODE MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on the configuration." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
