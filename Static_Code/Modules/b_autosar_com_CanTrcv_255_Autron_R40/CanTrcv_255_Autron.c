
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanTrcv_255_Autron.h"
#include "CanIf.h"             /* CAN Interface module header file */
#include "CanIf_Cbk.h"
#include "Dio.h"               /* Dio module header file */
#include "Compiler.h"
#include "Det.h"                /* DET module header file */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CanTrcvChannel_BCAN       0  /* BCAN  */
#define CanTrcvChannel_LCAN       1  /* LCAN  */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : CanTrcv_43Autron_Init                               **
**                                                                            **
** Service ID           : 0x00                                                **
*******************************************************************************/
#define CANTRCV_START_SEC_CODE
#include "MemMap.h"

FUNC(void,CANTRCV_CODE)CanTrcv_255_Autron_Init(P2CONST(void,
                                      AUTOMATIC, CANTRCV_CONST)ConfigPtr)
{
  Dio_WriteChannel((Dio_ChannelType)DioConf_DioChannel_DioChannel_P006_4, (Dio_LevelType)STD_HIGH);   /* BCAN STB */
  Dio_WriteChannel((Dio_ChannelType)DioConf_DioChannel_DioChannel_P007_2, (Dio_LevelType)STD_HIGH);   /* LCAN STB */
}
/*******************************************************************************
** Function Name        : CanTrcv_43_Autron_SetOpMode                         **
**                                                                            **
** Service ID           : 0x01                                                **
*******************************************************************************/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_255_Autron_SetOpMode(uint8 Transceiver, CanTrcv_TrcvModeType OpMode)
{
 
  Std_ReturnType LddReturnValue;
  LddReturnValue = (Std_ReturnType)E_OK;
  
  /* Invoke the Dio_WriteChannel to set the Standby pin to level-High     
    Dio_WriteChannel(포트넘버, (Dio_LevelType)STD_HIGH);
    
    (void)CanIf_TrcvModeIndication(Transceiver, OpMode);
  */

  if(Transceiver == CanTrcvChannel_BCAN)
  {
    if(OpMode == CANTRCV_TRCVMODE_NORMAL)
      {
        Dio_WriteChannel((Dio_ChannelType)DioConf_DioChannel_DioChannel_P006_4, (Dio_LevelType)STD_LOW);    /* BCAN STB */
      }
      else if(OpMode == CANTRCV_TRCVMODE_STANDBY)
      {
        Dio_WriteChannel((Dio_ChannelType)DioConf_DioChannel_DioChannel_P006_4, (Dio_LevelType)STD_HIGH);   /* BCAN STB */
      }
      else
      {
      }
  }
  else if(Transceiver == CanTrcvChannel_LCAN)
  {
    if(OpMode == CANTRCV_TRCVMODE_NORMAL)
      {
        Dio_WriteChannel((Dio_ChannelType)DioConf_DioChannel_DioChannel_P007_2, (Dio_LevelType)STD_LOW);    /* LCAN STB */
      }
      else if(OpMode == CANTRCV_TRCVMODE_STANDBY)
      {
        Dio_WriteChannel((Dio_ChannelType)DioConf_DioChannel_DioChannel_P007_2, (Dio_LevelType)STD_HIGH);   /* LCAN STB */
      }
      else
      {
      }
  }
  else
  {
  }


#if 0
  if(OpMode == CANTRCV_TRCVMODE_NORMAL)
  {
    /* B CAN */
    Dio_WriteChannel((Dio_ChannelType)DioConf_DioChannel_DioChannel_P006_4, (Dio_LevelType)STD_LOW);    /* BCAN STB */
    //Dio_WriteChannel((Dio_ChannelType)DioConf_DioChannel_DioChannel_P006_3, (Dio_LevelType)STD_LOW);
    /* LOCAL CAN */
    Dio_WriteChannel((Dio_ChannelType)DioConf_DioChannel_DioChannel_P007_2, (Dio_LevelType)STD_LOW);    /* LCAN STB */
    //Dio_WriteChannel((Dio_ChannelType)DioConf_DioChannel_DioChannel_P008_1, (Dio_LevelType)STD_LOW);

  }
  else if(OpMode == CANTRCV_TRCVMODE_STANDBY)
  {
    /* B CAN */
    Dio_WriteChannel((Dio_ChannelType)DioConf_DioChannel_DioChannel_P006_4, (Dio_LevelType)STD_HIGH);   /* BCAN STB */
    //Dio_WriteChannel((Dio_ChannelType)DioConf_DioChannel_DioChannel_P006_3, (Dio_LevelType)STD_HIGH);
    /* LOCAL CAN */
    Dio_WriteChannel((Dio_ChannelType)DioConf_DioChannel_DioChannel_P007_2, (Dio_LevelType)STD_HIGH);   /* LCAN STB */
    //Dio_WriteChannel((Dio_ChannelType)DioConf_DioChannel_DioChannel_P008_1, (Dio_LevelType)STD_HIGH);
  }
  else if(OpMode == CANTRCV_TRCVMODE_SLEEP)
  {

  }
  else
  {

  }
#endif

  (void)CanIf_TrcvModeIndication(Transceiver, OpMode);

  return (LddReturnValue);/* Return Std_ReturnType */
}

/*******************************************************************************
** Function Name        : CanTrcv_43_Autron_GetOpMode                         **
**                                                                            **
** Service ID           : 0x02                                                **
*******************************************************************************/
FUNC(Std_ReturnType, CANTRCV_CODE)CanTrcv_255_Autron_GetOpMode(uint8 Transceiver, P2VAR(CanTrcv_TrcvModeType, AUTOMATIC,
  CANTRCV_APPL_DATA)OpMode)
{
  
  Std_ReturnType LddReturnValue;
  LddReturnValue = (Std_ReturnType)E_OK;
  
  return (LddReturnValue); /* Return Std_ReturnType */
}
#define CANTRCV_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
