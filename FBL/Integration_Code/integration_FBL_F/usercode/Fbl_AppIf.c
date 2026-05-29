/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fbl_AppIf.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Application interface in FBL                                  **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.5.1.0   06-Jun-2022   JSCHOI       Redmine #36032                        **
** 1.2.0     16-Jul-2021   Sungwook     #29464                                **
** 1.1.11    13-May-2021   JH Lim       Redmine #29129                        **
** 1.0.4     05-Feb-2021   JH Lim       Redmine #28215                        **
** 1.0.3     29-Jul-2020   JYS          Redmine #24231                        **
** 1.0.2     02-Jul-2020   EK.KIM       #23953, #23954                        **
** 1.0.1     10-April-2020 Jaehyun      #22902                                **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Fbl_AppIf.h"
#include "Fbl_Cfg.h"

#include "WdgIf.h"
#include "Syst.h"

#include "Port.h"
/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#define SYST_P11_PCSR_VAL                                            0x0000005FU

#define SYST_PORTPIN_ZERO                                                     0U
#define SYST_PORTPIN_ONE                                                      1U
#define SYST_PORTPIN_TWO                                                      2U
#define SYST_PORTPIN_THREE                                                    3U
#define SYST_PORTPIN_FOUR                                                     4U
#define SYST_PORTPIN_FIVE                                                     5U
#define SYST_PORTPIN_SIX                                                      6U
#define SYST_PORTPIN_SEVEN                                                    7U
#define SYST_PORTPIN_EIGHT                                                    8U
#define SYST_PORTPIN_NINE                                                     9U
#define SYST_PORTPIN_TEN                                                     10U
#define SYST_PORTPIN_ELEVEN                                                  11U
#define SYST_PORTPIN_TWELVE                                                  12U

#define SYST_PORT_P11                                                        11U
#define SYST_PORT_P12                                                        12U
#define SYST_PORT_P21                                                        21U
#define EXT_WDG_PORT_P5                                                      5U
#define EXT_WDG_PIN_P1                                                        1U
#define GPIO_MODE                                                            (0)
#define CAN_HSIOM_PRT_PORT_SEL0_GPIO                                       0x00U
#define FBL_PORT_GPIO_DM_STRONG                                             0xEU

/*******************************************************************************
**                        Global Function Definition                          **
*******************************************************************************/
#define BTL_START_SEC_USER_CODE
#include "Btl_MemMap.h"

/* 
  Function called before Hsm_TempStop during RoutineControlErase service.
*/
uint32 Fbl_BeforeRoutineCtrlEraseInit(void)
{
  uint32 Ldt_RetValue;

  Ldt_RetValue = E_OK;

  return Ldt_RetValue;
}

/* 
  Function called after writing PartitionFlag during RoutineCtrlCheck service.
*/
uint32 Fbl_AfterRoutineCtrlChkInit(void)
{
  uint32 Ldt_RetValue;

  Ldt_RetValue = E_OK;

  return Ldt_RetValue;
}

/* 
  Function called upon completion of RoutineControlCheck service 
  and delivers BlockID. 
*/
uint32 Fbl_CheckBlockId(uint8 Block_Id)
{
  uint32 Ldt_RetValue;

  Ldt_RetValue = E_OK;

  return Ldt_RetValue;
}

Fbl_SwEntryPointType Fbl_SelectEntryPoint(void)
{
  Fbl_SwEntryPointType Ldt_SwEntryPoint;

  #if (FBL_MEMORY_SWAP_ENABLE == STD_ON)
  /**************************************************************************/
  /*                           메모리 이중화 기능 적용                      */
  /**************************************************************************/
  #if ((FBL_SUPPORT_MCU == FBL_MCU_TC38X) || (FBL_SUPPORT_MCU == FBL_MCU_TC39X) || \
		(FBL_SUPPORT_MCU == FBL_MCU_TC36X) || (FBL_SUPPORT_MCU == FBL_MCU_TC37X))
  /***************************************************************************
  * HW MEMORY SWAP 기능이 지원되는 MCU 는
  * partition A, B swap 에 따른 memory mapping 을 MCU 에서 해주므로
  * partition 에 따른 별도의 start address 제어가 필요없다.
  * Fbl_SelectEntryPoint callout 내에서
  * 정상적인 RTSW 펌웨어 리프로그래밍 성공 여부만 판단하면 된다.
  ***************************************************************************/

  /*
     정상적인 RTSW 펌웨어가 있는지 판단 로직 구현
     ex) 사전에 정해놓은 플래시 영역에 특정 패턴이 있는지 검사
         패턴은 OTA 과정에서 펌웨어 flashing 성공시 writing(Fbl_WritePartitionFlag callout)
  */
  if (0)
  {
    /* RTSW 모드 */
    Ldt_SwEntryPoint = FBL_SW_ENTRY_POINT_1;
  }
  else
  {
    /* FBL 모드 */
    Ldt_SwEntryPoint = FBL_SW_NO_RTSW;
  }

  #elif (FBL_SUPPORT_MCU == FBL_MCU_CYTXXX)
  /***************************************************************************
  * HW MEMORY SWAP 기능이 지원되는 MCU 는
  * partition A, B swap 에 따른 memory mapping 을 MCU 에서 해주므로
  * partition 에 따른 별도의 start address 제어가 필요없다.
  * Fbl_SelectEntryPoint callout 내에서
  * 정상적인 RTSW 펌웨어 리프로그래밍 성공 여부만 판단하면 된다.
  * FBL_MCU_CYTXXX 의 경우는 HW 특성상 Reset 이후 Dual Memory Enable 
  * & Memory Swap 진행이 되어야 한다. 
  ***************************************************************************/
  
  /*
     1) Dual Memory 기능 활성화  

     2)  정상적인 RTSW 펌웨어가 있는지 판단 로직 구현 & Active Bank 선정
        ex) 사전에 정해놓은 플래시 영역에 특정 패턴이 있는지 검사
            패턴은 OTA 과정에서 펌웨어 flashing 성공시 writing(Fbl_WritePartitionFlag callout)
            이 결과를 통해 Active Bank를 선정

     3) Memory Swap

 
        ex) 선정된 Bank 를 Active Bank 로 적용
  */
  
  if (0)
  {
    /* RTSW 모드 */
    Ldt_SwEntryPoint = FBL_SW_ENTRY_POINT_1;
  }
  else
  {
    /* FBL 모드 */
    Ldt_SwEntryPoint = FBL_SW_NO_RTSW;
  }
        
  #else
  /***************************************************************************
  * HW MEMORY SWAP 기능이 지원되지 MCU 계열은
  * 부팅시 partition A, B swap 에 따른 start address 제어가 필요하다.
  * Fbl_SelectEntryPoint callout 내에서
  * 어떤 partition 의 start address 를 수행할지를 결정해야 한다.
  ***************************************************************************/

  /*
     Partition A or Partition B 에 정상적인 펌웨어가 있는지 판단 로직 구현
     ex) 사전에 정해놓은 플래시 영역에 어떤 partition RTSW 를 수행할지 특정 패턴을 확인
         패턴은 OTA 과정에서 펌웨어 flashing 성공시 writing(Fbl_WritePartitionFlag callout)
  */
  if (0)
  {
    /* Partition A RTSW 모드 */
    Ldt_SwEntryPoint = FBL_SW_ENTRY_POINT_1;
  }
  else if (0)
  {
    /* Partition B RTSW 모드 */
    Ldt_SwEntryPoint = FBL_SW_ENTRY_POINT_2;
  }
  else
  {
    /* FBL 모드 */
    Ldt_SwEntryPoint = FBL_SW_NO_RTSW;
  }
  #endif

  #else

  /**************************************************************************/
  /*                           메모리 이중화 기능 미적용                              */
  /**************************************************************************/
  if ((*(const uint32*)MAIN_SW_SECURITY_KEY_ADDR) == FBL_SECURITY_KEY_VALUE)
  {
    /* RTSW 모드 */
    Ldt_SwEntryPoint = FBL_SW_ENTRY_POINT_1;
  }
  else
  {
    /* FBL 모드 */
    Ldt_SwEntryPoint = FBL_SW_NO_RTSW;
  }

  #endif

  return Ldt_SwEntryPoint;
}

uint32 Fbl_WritePartitionFlag(uint8 Block_Id)
{
  uint32 Lu32_Ret;

  #if (FBL_MEMORY_SWAP_ENABLE == STD_ON)
  /**************************************************************************/
  /*                           메모리 이중화 기능 적용                               */
  /**************************************************************************/

  #if ((FBL_SUPPORT_MCU == FBL_MCU_TC38X) || (FBL_SUPPORT_MCU == FBL_MCU_TC39X) ||\
		(FBL_SUPPORT_MCU == FBL_MCU_TC36X) || (FBL_SUPPORT_MCU == FBL_MCU_TC37X))
  /***************************************************************************
  * HW MEMORY SWAP 기능이 지원되는 MCU 이므로
  * Fbl_SelectEntryPoint callout 에서 정상적인 RTSW 펌웨어가 있는지 판단할 수 있는
  * 사용자만의 PartitionFlag 를 writing 해야한다.
  ***************************************************************************/

  /*
    RTSW 펌웨어가 정상적으로 flashing(Secure Flash 절차 성공)
    되었는지에 대한  PartitionFlag writing 로직 구현
    writing 성공시 E_OK 리턴, writing 실패시 E_NOT_OK 리턴
  */
  if (0)
  {
    Lu32_Ret = E_OK;
  }
  else
  {
    Lu32_Ret = E_NOT_OK;
  }
  #else
  /***************************************************************************
  * HW MEMORY SWAP 기능이 지원되지 않는 MCU 계열이므로
  * 부팅시 어떤 partition 을 수행해야 할지에 대한 정보가 필요하다.
  * Fbl_SelectEntryPoint callout 에서 어떤 partition 의 RTSW 펌웨어가 수행되어야 하는지
  * 사용자만의 PartitionFlag 를 writing 해야한다.
  ***************************************************************************/

  /*
    어떤 partition 의 RTSW 펌웨어가 정상적으로 flashing(Secure Flash 절차 성공)
    되었는지에 대한 PartitionFlag writing 로직 구현
    writing 성공시 E_OK 리턴, writing 실패시 E_NOT_OK 리턴
  */
  if (0)
  {
    Lu32_Ret = E_OK;
  }
  else
  {
    Lu32_Ret = E_NOT_OK;
  }
  #endif

  #else
  /**************************************************************************/
  /*                           메모리 이중화 기능 미적용                              */
  /**************************************************************************/
  /***************************************************************************
  * FBL 에서 RTSW 펌웨어 리프로그래밍 성공 후 자체적으로
  * MAIN_SW_SECURITY_KEY_ADDR 에 FBL_SECURITY_KEY_VALUE 패턴을 기록하므로 별도의 로직 필요없음
  ***************************************************************************/
  Lu32_Ret = E_OK;

  #endif

  return Lu32_Ret;
}

void Fbl_GetActivePartitionBlkAddress(uint32* headerAddr, uint32* trailerAddr)
{
  /* If OTA memory Swap is enabled, 
   * current version should be parsed in the active partition 
   * User must select the active partition's header Address and trailer address */

   /* Step 1 : Find out what is the active partition */


   /* Step 2 : If Active Partition is B, headerAddr and trailerAddr should
    *          be plus the offset. 
    *          ex) *headerAddr = *headerAddr + offset, 
    *              *trailerAddr = *trailerAddr + offset
    */
}

uint32 Fbl_SvcCheckVersion(uint32 currentVersion, uint32 newVer)
{
  uint32 Ldt_RetValue;

  /* This is HAE test code, Do not use this. */
  /*
  if (newVer >= currentVersion)
  {
    Ldt_RetValue = E_OK;
  }
  else
  {
    Ldt_RetValue = E_NOT_OK;
  }
  */

  /* User should make own version check logic here. */

  Ldt_RetValue = E_NOT_OK;
  return Ldt_RetValue;
}

void Fbl_BeforeFblSpecificInit(void)
{
  /* Initialize before FBL specific initialization 
     This function is called Before FBL PLL initalization */
}

void Fbl_BeforeCommExtInit(void)
{
  /* Initialize external devices before communication device initialization. */
  Fbl_Gpio_Init(EXT_WDG_PORT_P5, EXT_WDG_PIN_P1, CAN_HSIOM_PRT_PORT_SEL0_GPIO, FBL_PORT_GPIO_DM_STRONG, STD_LOW, GPIO_MODE);
}

void Fbl_AfterCommExtInit(void)
{
  /* Initialize external devices after communication device initialization. */
}

void Fbl_ExtDeinit(void)
{
  /* Deinitialize the external devices just before the reset */
}

#if ((FBL_SUPPORT_MCU == FBL_MCU_TC38X) || (FBL_SUPPORT_MCU == FBL_MCU_TC39X) || \
		(FBL_SUPPORT_MCU == FBL_MCU_TC36X) || (FBL_SUPPORT_MCU == FBL_MCU_TC37X))
void Fbl_EthPortInit(void)
{
  /* RGMII */
  Mcu_UnlockSafetyWdg();
  P11_PCSR.U = SYST_P11_PCSR_VAL;
  Mcu_LockSafetyWdg();
  /* Mdc   */
  Syst_PortSetPinModeOutput(SYST_PORT_P12, SYST_PORTPIN_ZERO, Syst_PortOutputModePushPull, Syst_PortOutIdxAlt6);
  /* Txclk */
  Syst_PortSetPinModeOutput(SYST_PORT_P11, SYST_PORTPIN_FOUR, Syst_PortOutputModePushPull, Syst_PortOutIdxAlt7);
  /* Txctl */
  Syst_PortSetPinModeOutput(SYST_PORT_P11, SYST_PORTPIN_SIX, Syst_PortOutputModePushPull, Syst_PortOutIdxAlt6);
  /* Txd0  */
  Syst_PortSetPinModeOutput(SYST_PORT_P11, SYST_PORTPIN_THREE, Syst_PortOutputModePushPull, Syst_PortOutIdxAlt6);
  /* Txd1  */
  Syst_PortSetPinModeOutput(SYST_PORT_P11, SYST_PORTPIN_TWO, Syst_PortOutputModePushPull, Syst_PortOutIdxAlt6);
  /* Txd2  */
  Syst_PortSetPinModeOutput(SYST_PORT_P11, SYST_PORTPIN_ONE, Syst_PortOutputModePushPull, Syst_PortOutIdxAlt6);
  /* Txd3  */
  Syst_PortSetPinModeOutput(SYST_PORT_P11, SYST_PORTPIN_ZERO, Syst_PortOutputModePushPull, Syst_PortOutIdxAlt6);

  Syst_PortSetPinPadDriver(SYST_PORT_P12,SYST_PORTPIN_ZERO, Syst_PortPadDriverCmosAutomotiveSpeed4);   /* Mdc */
  Syst_PortSetPinPadDriver(SYST_PORT_P11,SYST_PORTPIN_FOUR, Syst_PortPadDriverCmosAutomotiveSpeed4);   /* Txclk */
  Syst_PortSetPinPadDriver(SYST_PORT_P11,SYST_PORTPIN_SIX, Syst_PortPadDriverCmosAutomotiveSpeed4);    /* Txctl */
  Syst_PortSetPinPadDriver(SYST_PORT_P11,SYST_PORTPIN_THREE, Syst_PortPadDriverCmosAutomotiveSpeed4);  /* Txd0 */
  Syst_PortSetPinPadDriver(SYST_PORT_P11,SYST_PORTPIN_TWO, Syst_PortPadDriverCmosAutomotiveSpeed4);    /* Txd1 */
  Syst_PortSetPinPadDriver(SYST_PORT_P11,SYST_PORTPIN_ONE, Syst_PortPadDriverCmosAutomotiveSpeed4);    /* Txd2 */
  Syst_PortSetPinPadDriver(SYST_PORT_P11,SYST_PORTPIN_ZERO, Syst_PortPadDriverCmosAutomotiveSpeed4);   /* Txd3 */

  GETH_GPCTL.B.ALTI0 = Syst_RxSel_c;   /* Mdio In */
  GETH_GPCTL.B.ALTI1 = Syst_RxSel_a;   /* RefClk */
  GETH_GPCTL.B.ALTI4 = Syst_RxSel_a;   /* rxctl */
  GETH_GPCTL.B.ALTI6 = Syst_RxSel_a;   /* RxD0 */
  GETH_GPCTL.B.ALTI7 = Syst_RxSel_a;   /* RxD1 */
  GETH_GPCTL.B.ALTI8 = Syst_RxSel_a;   /* RxD2 */
  GETH_GPCTL.B.ALTI9 = Syst_RxSel_a;   /* RxD3 */

  Syst_PortSetPinModeInput(SYST_PORT_P11,SYST_PORTPIN_ELEVEN, Syst_PortInModeNoPullDevice);  /* CRSDIV */
  Syst_PortSetPinModeInput(SYST_PORT_P11,SYST_PORTPIN_TWELVE, Syst_PortInModeNoPullDevice);  /* RefClk */
  Syst_PortSetPinModeInput(SYST_PORT_P11,SYST_PORTPIN_TEN, Syst_PortInModeNoPullDevice);     /* Rxd0 */
  Syst_PortSetPinModeInput(SYST_PORT_P11,SYST_PORTPIN_NINE, Syst_PortInModeNoPullDevice);    /* RxD1 */
  Syst_PortSetPinModeInput(SYST_PORT_P11,SYST_PORTPIN_EIGHT, Syst_PortInModeNoPullDevice);   /* RxD2 */
  Syst_PortSetPinModeInput(SYST_PORT_P11,SYST_PORTPIN_SEVEN, Syst_PortInModeNoPullDevice);   /* RxD3 */
  Syst_PortSetPinModeInput(SYST_PORT_P11,SYST_PORTPIN_FIVE, Syst_PortInModeNoPullDevice);    /* GrefClk */

  Syst_PortSetPinPadDriver(SYST_PORT_P11,SYST_PORTPIN_ELEVEN, Syst_PortPadDriverCmosAutomotiveSpeed4);  /* Rxctl */
  Syst_PortSetPinPadDriver(SYST_PORT_P11,SYST_PORTPIN_TWELVE, Syst_PortPadDriverCmosAutomotiveSpeed4);  /* RefClk */
  Syst_PortSetPinPadDriver(SYST_PORT_P11,SYST_PORTPIN_TEN, Syst_PortPadDriverCmosAutomotiveSpeed4);     /* Rxd0 */
  Syst_PortSetPinPadDriver(SYST_PORT_P11,SYST_PORTPIN_NINE, Syst_PortPadDriverCmosAutomotiveSpeed4);    /* RxD1 */
  Syst_PortSetPinPadDriver(SYST_PORT_P11,SYST_PORTPIN_EIGHT, Syst_PortPadDriverCmosAutomotiveSpeed4);   /* RxD2 */
  Syst_PortSetPinPadDriver(SYST_PORT_P11,SYST_PORTPIN_SEVEN, Syst_PortPadDriverCmosAutomotiveSpeed4);   /* RxD3 */
  Syst_PortSetPinPadDriver(SYST_PORT_P11,SYST_PORTPIN_FIVE, Syst_PortPadDriverCmosAutomotiveSpeed4);    /* GrefClk */
}
#endif

boolean Fbl_GetSwitchInit (void)
{
	boolean SwitchInit = FALSE;

  /*
   * Callout shall be filled by the system designer
   */


  return SwitchInit;
}

#define BTL_STOP_SEC_USER_CODE
#include "Btl_MemMap.h"

#define BTL_START_SEC_USER_RAM_CODE
#include "Btl_MemMap.h"

/* Since the code is executed in RAM, it should be implemented
  without additional function call */

/* Since the code is executed in RAM, it should be implemented
  without additional function call */
static uint8 extWdgCount = 0;
static ExtWdg_PortPinNum = 1;
void Fbl_ExtPolling(void)
{
  /* Performed aperiodically */
  extWdgCount++;
  if(extWdgCount == 2)
  {
    GPIO_PRT5->unOUT_INV.u32Register = 0x01 << ExtWdg_PortPinNum;
    extWdgCount =0;
  }
}

#define BTL_STOP_SEC_USER_RAM_CODE
#include "Btl_MemMap.h"

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
