/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: RamTst_Types.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR RAMTST                                                **
**                                                                            **
**  PURPOSE   : Type definitions of Ram Test module                           **
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
** 1.3.2     30-Dec-2020   CY Song          RedMine #27378                    **
** 1.2.5     16-May-2016   CY Song          RedMine #4902                     **
** 1.2.3     05-Oct-2015   CY Song          Correct Misra Rule Error          **
** 1.0.4     17-Oct-2014   CY Song        Rd#1452 Add Macro                   **
** 1.0.0     07-Jun-2013   CY Song          Initial Version                   **
*******************************************************************************/

#ifndef RAMTST_TYPES_H
#define RAMTST_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "RamTst_Cfg.h"
#include "HwResource.h"

/* polyspace-begin MISRA-C3:2.5 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.3 [Justified:Low] "Not a defect" */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/* RamTst_ExecutionStatusType: status value returned by the API service
 * RamTst_GetExecutionStatus()
 */
typedef enum
{
  RAMTST_EXECUTION_UNINIT,
  RAMTST_EXECUTION_STOPPED,
  RAMTST_EXECUTION_RUNNING,
  RAMTST_EXECUTION_ALLOWED,  
  RAMTST_EXECUTION_SUSPENDED,
} RamTst_ExecutionStatusType;

typedef enum
{
  /* status for background test */
  RAMTST_BGEXE_DONE,
  RAMTST_BGEXE_TRYING_STOP,
  RAMTST_BGEXE_TRYING_SUSPEND,
} RamTst_TriggerStopOrSuspendType;

/* RamTst_TestResultType: status value returned by the API service
 * RamTst_GetTestResult()
 */
typedef enum
{
  RAMTST_RESULT_NOT_TESTED,
  RAMTST_RESULT_OK,
  RAMTST_RESULT_NOT_OK,
  RAMTST_RESULT_UNDEFINED,
} RamTst_TestResultType;

/* RamTstTestPolicy: Policy regarding destruction or non-destruction of memory
 * content.
 */
 typedef enum
{
  RAMTEST_DESTRUCTIVE,
  RAMTEST_NON_DESTRUCTIVE,
} RamTstTestPolicy;

/* Data type used to identify a set of configuration parameters for a
 * test algorithm
 */
typedef uint8 RamTst_AlgParamsIdType;

/* Data type of number of tested RAM cells */
typedef uint32 RamTst_NumberOfTestedCellsType;

/* Data type used to identify or count RAM blocks given in the test
 * configuration parameters
 */
typedef uint16 RamTst_NumberOfBlocksType;


typedef P2FUNC(boolean, RAMTST_CODE, RamTst_AlgBckGrdTstType)
              (uint32 RamTstStrtAddress,
               RamTst_NumberOfTestedCellsType RamTstNumOfCells);

/* polyspace +3 MISRA-C3:2.3 [Justified:Low] "Not a defect" */         
typedef P2FUNC(boolean, RAMTST_CODE, RamTst_AlgType)
              (RamTst_NumberOfBlocksType RamTstBlockId);

/* DET Errors */
/* Det Error ID Reported when a particular API is called in an
 * unexpected state */
#define RAMTST_E_STATUS_FAILURE         0x01
/* Det Error ID Reported when API parameter out of specified range */
#define RAMTST_E_OUT_OF_RANGE           0x02
/* Det Error ID Reported when API service used without module initialization */
#define RAMTST_E_UNINIT                 0x03
/* Det Error ID Reported when API service called with a NULL pointer */
#define RAMTST_E_PARAM_POINTER          0x04

#define RAMTST_FAILED                   ((boolean)0x00)

#define RAMTST_PASSED                   ((boolean)0x01)

#define RAMTST_FALSE                    0x00

#define RAMTST_TRUE                     0x01

#define RAMTST_ZERO                     0x00

#define RAMTST_ONE                      0x01

#define RAMTST_FOUR                     0x04

#define RAMTST_EIGHT                    0x08

#define RAMTST_SIXTEEN                  0x10

#define RAMTST_TWENTYFOUR               0x18

#define RAMTST_FF                       0xFF

#define EVEN_PARITY   0
#define ODD_PARITY    1

#if(RAMTST_DEV_ERROR_DETECT == STD_ON)  
/* polyspace<MISRA-C:19.7:Not a defect:No action planned> Not a defect */
#define RAMTST_REPORT_ERROR(sid, error) \
  do {\
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, (sid), (error));\
  } while(0)
#else
/* polyspace<MISRA-C:19.7:Not a defect:No action planned> Not a defect */
#define RAMTST_REPORT_ERROR(sid, error)     do{}while(0)
#endif

/* polyspace<MISRA-C:19.7:Not a defect:No action planned> Not a defect */
#if ((HWRESOURCE_GET_MCU() == HWRESOURCE_RH850F1H) || \
     (HWRESOURCE_GET_MCU() == HWRESOURCE_RH850F1L) || \
     (HWRESOURCE_GET_MCU() == HWRESOURCE_RH850F1K))
/* polyspace +2 MISRA-C3:D4.9 [Justified:Low] "Not a defect" */
#define RAMTST_NOP()                    do { __asm("nop"); } while(0)
#else
/* polyspace +2 MISRA-C3:D4.9 [Justified:Low] "Not a defect" */
#define RAMTST_NOP()                    do {} while(0)
#endif

/* polyspace-end MISRA-C3:2.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.5 [Justified:Low] "Not a defect" */

#endif /* RAMTST_TYPES_H */
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
