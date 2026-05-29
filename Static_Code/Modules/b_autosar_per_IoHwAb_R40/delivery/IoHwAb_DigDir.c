/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: IoHwAb_DigDir.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_DigDirInit                                             **
**              IoHwAb_DigDirReadDirect                                       **
**              IoHwAb_DigDirWriteDirect                                      **
**              IoHwAb_DigDirSetToInput                                       **
**              IoHwAb_DigDirSetToOutput                                      **
**              IoHwAb_DigDirIsInput                                          **
**              IoHwAb_DigDirIsOutput                                         **
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
** 1.10.1    04-Aug-2020   Yangjin    #24902                                  **
** 1.8.1     08-May-2020   Yangjin    #23100                                  **
** 1.8.0     21-Apr-2020   Yangjin    #22141                                  **
** 1.0.4     25-Mar-2015   Jongyoung  1.Manage the single module version      **
** 1.0.3     27-Sep-2014   Jongyoung  1. Polyspace result Adaption            **
** 1.0.2     18-Apr-2014   Sinil      Task ID : 853                           **
**                                    Change the index of                     **
**                                    IoHwAb_GaaDigDirPinDir                  **
** 1.0.1     03-Apr-2014   Sinil      Task ID : 853                           **
**                                    Update IoHwAb_DigDirSetToInput and      **
**                                    IoHwAb_DigDirSetToOutput                **
** 1.0.0     07-Mar-2014   Sinil      Initial version                         **
*******************************************************************************/
/* polyspace-begin MISRA-C3:11.5 [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-begin RTE:UNR [Justified:Low] "it depends on the configuration." */
/* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "It is checked by an if statement above." */
/* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on the configuration." */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_DigDir.h"
#include "IoHwAb_Config.h"
#include "Rte_IoHwAb.h"
#include "Rte_Type.h"
#include "IoHwAb_Util.h"

#if (IOHWAB_USE_DIG_DIR == STD_ON)
#ifndef IOHWAB_MCAL_TI_TDA4X
#include "Port.h"
#endif
#include "Dio.h"
#endif /* (IOHWAB_USE_DIG_DIR == STD_ON) */

#ifdef IOHWAB_MCAL_TI_TDA4X
#include "gpio.h"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (IOHWAB_USE_DIG_DIR == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_DigDirInit                                   **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service initilize DigDir module.               **
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
**                          IoHwAb_GaaDigDirChIdx,                            **
**                          IoHwAb_GaaDigDirPinDir,                           **
**                          IoHwAb_GaaGenInfos                                **
**                        Function(s) invoked    : none                       **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigDirInit(void)
{
  IoHwAb_IndexType LucIdx;
  IoHwAb_IndexType LucChRefIdx;

  /* update the direction information */
  for(LucIdx = 0; LucIdx < IoHwAb_GddDigDirNumLgc; LucIdx++)
  {
    LucChRefIdx = IoHwAb_GaaDigDirChIdx[LucIdx];
    IoHwAb_GaaDigDirPinDir[LucIdx] = IoHwAb_GaaGenInfos[LucChRefIdx].ddCfgPinDir;
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigDirReadDirect                             **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service reads the level value of DIO channel.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Level                                               **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigDirChIdx,                            **
**                          IoHwAb_GaaGenInfos                                **
**                        Function(s) invoked    :                            **
**                          Dio_ReadChannel                                   **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigDirReadDirect(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_LevelType, AUTOMATIC, IOHWAB_APPL_DATA) Level)
{
  IoHwAb_IndexType LucChRefIdx = 0U;
  if ( ChIdx < IoHwAb_GddDigDirNumLgc)
  {
     LucChRefIdx = IoHwAb_GaaDigDirChIdx[ChIdx];

     if (Level != NULL_PTR)
     {
        if (Dio_ReadChannel(IoHwAb_GaaGenInfos[LucChRefIdx].ddDioChType) == STD_LOW)
        {
           if (IoHwAb_GaaGenInfos[LucChRefIdx].ucPolar == IOHWAB_POL_LOW)
           {
             *Level = IOHWAB_HIGH;
           }
           else
           {
             *Level = IOHWAB_LOW;
           }
        }
        else
        {
           if (IoHwAb_GaaGenInfos[LucChRefIdx].ucPolar == IOHWAB_POL_LOW)
           {
              *Level = IOHWAB_LOW;
           }
           else
           {
              *Level = IOHWAB_HIGH;
           }
        }
     }
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigDirWriteDirect                            **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service writes the level value of DIO channel. **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx, Level                                        **
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
**                          IoHwAb_GaaDigDirChIdx,                            **
**                          IoHwAb_GaaGenInfos                                **
**                        Function(s) invoked    :                            **
**                          Dio_WriteChannel                                  **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigDirWriteDirect(IoHwAb_IndexType ChIdx,
  IoHwAb_LevelType Level)
{
  Dio_LevelType LvBuf;
  IoHwAb_IndexType LucChRefIdx = 0U;
  if (ChIdx < IoHwAb_GddDigDirNumLgc )
  {
    LucChRefIdx = IoHwAb_GaaDigDirChIdx[ChIdx];

    if (Level == IOHWAB_LOW)
    {
       if (IoHwAb_GaaGenInfos[LucChRefIdx].ucPolar == IOHWAB_POL_LOW)
       {
          LvBuf = (Dio_LevelType)STD_HIGH;
       }
       else 
       {
          LvBuf = (Dio_LevelType)STD_LOW;
       }   
    }
    else
    {
       if (IoHwAb_GaaGenInfos[LucChRefIdx].ucPolar == IOHWAB_POL_LOW)
       {
          LvBuf = STD_LOW;
       }
       else
       {
          LvBuf = STD_HIGH;
       }
    }
    Dio_WriteChannel(IoHwAb_GaaGenInfos[LucChRefIdx].ddDioChType, LvBuf);
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DioSetPinDirection                           **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This function changes the DIO pin direction         **
**                        in case of TDA4X only.                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx, Dir                                          **
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
**                          GPIOSetDirMode_v0                                 **
*******************************************************************************/
#ifdef IOHWAB_MCAL_TI_TDA4X
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DioSetPinDirection(Dio_ChannelType ChIdx, Port_PinDirectionType Dir)
{
  uint32 LulGpioAddress = 0;
  uint32 LulGpioModuleNum = ChIdx / 144;

  switch(LulGpioModuleNum)
  {
    case 0:
      LulGpioAddress = IOHWAB_ADDRESS_WKUP_GPIO0;
      break;

    case 1:
      LulGpioAddress = IOHWAB_ADDRESS_WKUP_GPIO1;
      break;

    case 2:
      LulGpioAddress = IOHWAB_ADDRESS_GPIO0;
      break;

    case 3:
      LulGpioAddress = IOHWAB_ADDRESS_GPIO1;
      break;

    case 4:
      LulGpioAddress = IOHWAB_ADDRESS_GPIO2;
      break;

    case 5:
      LulGpioAddress = IOHWAB_ADDRESS_GPIO3;
      break;

    case 6:
      LulGpioAddress = IOHWAB_ADDRESS_GPIO4;
      break;

    case 7:
      LulGpioAddress = IOHWAB_ADDRESS_GPIO5;
      break;

    case 8:
      LulGpioAddress = IOHWAB_ADDRESS_GPIO6;
      break;

    case 9:
      LulGpioAddress = IOHWAB_ADDRESS_GPIO7;
      break;

    default:
    /* Default Case */
      break;
  }
/* polyspace-begin MISRA-C3:10.3 [Justified:Low] "It is validated by test cases. It works as intended." */
  GPIOSetDirMode_v0(LulGpioAddress,ChIdx % 144, Dir);
/* polyspace-end MISRA-C3:10.3 [Justified:Low] "It is validated by test cases. It works as intended." */
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif
/* polyspace-begin MISRA-C3:17.7 [Justified:Low] "False diagnosis. The return type of the function is void." */
/*******************************************************************************
** Function Name        : IoHwAb_DigDirSetToInput                             **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service changes the pin direction to input.    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
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
**                          IoHwAb_GaaDigDirChIdx,                            **
**                          IoHwAb_GaaDigDirPinDir,                           **
**                          IoHwAb_GaaGenInfos                                **
**                        Function(s) invoked    :                            **
**                          Port_SetPinDirection                              **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigDirSetToInput(IoHwAb_IndexType ChIdx)
{
  IoHwAb_IndexType LucChRefIdx = 0U;
  if (ChIdx < IoHwAb_GddDigDirNumLgc )
  {
    LucChRefIdx = IoHwAb_GaaDigDirChIdx[ChIdx];
    IoHwAb_GaaDigDirPinDir[ChIdx] = PORT_PIN_IN;
    #ifdef IOHWAB_MCAL_TI_TDA4X
      IoHwAb_DioSetPinDirection(IoHwAb_GaaGenInfos[LucChRefIdx].ddDioChType, PORT_PIN_IN);
    #else
      Port_SetPinDirection(IoHwAb_GaaGenInfos[LucChRefIdx].ddPortPinType, PORT_PIN_IN);
    #endif
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigDirSetToOutput                            **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service changes the pin direction to output.   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
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
**                          IoHwAb_GaaDigDirChIdx,                            **
**                          IoHwAb_GaaDigDirPinDir,                           **
**                          IoHwAb_GaaGenInfos                                **
**                        Function(s) invoked    :                            **
**                          Port_SetPinDirection                              **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigDirSetToOutput(IoHwAb_IndexType ChIdx)
{
  IoHwAb_IndexType LucChRefIdx = 0U;
  if (ChIdx < IoHwAb_GddDigDirNumLgc )
  {
    LucChRefIdx = IoHwAb_GaaDigDirChIdx[ChIdx];
    IoHwAb_GaaDigDirPinDir[ChIdx] = PORT_PIN_OUT;
    #ifdef IOHWAB_MCAL_TI_TDA4X
      IoHwAb_DioSetPinDirection(IoHwAb_GaaGenInfos[LucChRefIdx].ddDioChType, PORT_PIN_OUT);
    #else
      Port_SetPinDirection(IoHwAb_GaaGenInfos[LucChRefIdx].ddPortPinType, PORT_PIN_OUT);
    #endif
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace-end MISRA-C3:17.7 [Justified:Low] "False diagnosis. The return type of the function is void." */
/*******************************************************************************
** Function Name        : IoHwAb_DigDirIsInput                                **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service checks whether the pin direction is    **
**                        input.                                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Result                                              **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigDirChIdx,                            **
**                          IoHwAb_GaaDigDirPinDir                            **
**                        Function(s) invoked    : none                       **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigDirIsInput(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_BoolType, AUTOMATIC, IOHWAB_APPL_DATA) blResult)
{
  if ((blResult != NULL_PTR) && (ChIdx < IoHwAb_GddDigDirNumLgc ))
  {
    *blResult = (IoHwAb_GaaDigDirPinDir[ChIdx] == PORT_PIN_IN)
      ? IOHWAB_TRUE : IOHWAB_FALSE;
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigDirIsOutput                               **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service checks whether the pin direction is    **
**                        output.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Result                                              **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigDirChIdx,                            **
**                          IoHwAb_GaaDigDirPinDir                            **
**                        Function(s) invoked    : none                       **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigDirIsOutput(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_BoolType, AUTOMATIC, IOHWAB_APPL_DATA) blResult)
{
  if ((blResult != NULL_PTR) && (ChIdx < IoHwAb_GddDigDirNumLgc ))
  {
    *blResult = (IoHwAb_GaaDigDirPinDir[ChIdx] == PORT_PIN_OUT)
      ? IOHWAB_TRUE : IOHWAB_FALSE;
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (IOHWAB_USE_DIG_DIR == STD_ON) */
/* polyspace-end MISRA-C3:11.5 [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-end RTE:UNR [Justified:Low] "it depends on the configuration." */
/* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "It is checked by an if statement above." */
/* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on the configuration." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
