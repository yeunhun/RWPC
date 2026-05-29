/*******************************************************************************
**                                                                            **
**  (C) 2013-2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Os_IocInternalTypes.h                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of IOC type internally used macros,                 **
**              structure declarations and extern declarations of variables   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 2.6.3     04-Jun-2020    MJ.Woo        Redmine #21784                      **
** 2.0.13    30-Jun-2016    MJ.Woo        Redmine #4592, #4595, #4566, #5368  **
** 2.0.12    25-Apr-2016    JH.Lee        Redmine #4295                       **
** 2.0.11    22-Dec-2015    MJ.Woo        Redmine: #3684                      **
** 2.0.9     13-Oct-2014    MJ.Woo        Redmine: #1427                      **
** 2.0.8     27-Feb-2014    SH.Yoo        TASK: xar~842, Redmine #626         **
** 2.0.7     13-Feb-2014    MJ.Woo        TASK: xar~819                       **
** 2.0.6     08-Jan-2014    SH.Yoo        TASK: xar~810                       **
** 2.0.5     23-Dec-2013    MJ.Woo        CR: xar~212, TASK: xar~796          **
** 2.0.4     11-Nov-2013    SH.Yoo        CR: xar~179, TASK: xar~736          **
**           23-Oct-2013    DG.Lee        CR: xar~179, TASK: xar~736          **
** 2.0.3     25-Sep-2013    MJ.Woo        CR: xar~172, TASK: xar~691          **
** 2.0.2     21-Aug-2013    MJ.Woo        CR: xar~168, TASK: xar~675          **
** 2.0.1     13-Aug-2013    MJ.Woo        CR: xar~160, TASK: xar~655          **
** 2.0.0     22-Jul-2013    JH.Son,SH.Yoo CR: xar~107, TASK: xar~543          **
**                          DG.Lee,MJ.Woo                                     **
** 1.0.0     10-Jan-2013    JH.Son,SH.Yoo Initial version                     **
**                          DG.Lee,MJ.Woo                                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C:8.12:Not a defect:Justify with annotations> External linkage with array size makes error because of compiler optimization  */
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> see MEMMAP003 of AUTOSAR */

#ifndef OS_IOCINTERNALTYPES_H
#define OS_IOCINTERNALTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os.h"

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/* IOC Internal buffer Status*/
#if (OS_APPLICATION == STD_ON)

/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "AUTRON_MISRA_D4_8" */
typedef struct
{
  P2VAR(void, AUTOMATIC, OS_VAR) pIocBuf;
  uint32 ulDataSize;
} Os_IocBufType;

typedef struct
{
  P2CONST(Os_IocBufType, AUTOMATIC, OS_CONST) pBuffer;
  /* Count of parameters for Ioc[Write/Read]Group */
  uint32 ulDataCount;
} Os_IocUnqueuedCfgType;

typedef struct
{
  P2CONST(Os_IocBufType, AUTOMATIC, OS_CONST) pBuffer;
  /* Count of parameters for Ioc[Send/Receive]Group */
  uint32 ulDataCount;
  /* Internal transmission buffer size */
  uint32 ulQueueLen;
  /* Queue read Index */
  uint32 ulQueueRead;
  /* Queue Write Index */
  uint32 ulQueueWrite;
  /* Current Queue Count */
  uint32 ulQueueCount;
  /* Data Lost */
  boolean blDataLost;
} Os_IocQueuedCfgType;

#define OS_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(Os_IocQueuedCfgType, OS_VAR)Os_GaaIocQueuedCfg[];
extern CONST(Os_IocUnqueuedCfgType, OS_CONST)Os_GaaIocUnqueuedCfg[];
#define OS_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#endif /* if (OS_APPLICATION == STD_ON) */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* OS_IOCINTERNALTYPES_H */


/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<MISRA-C:8.12:Not a defect:Justify with annotations> External linkage with array size makes error because of compiler optimization  */
/* polyspace:end<MISRA-C3:20.1> */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
