#include "WPCCANcontrol.h"
#include "WPCSleepControl.h"

#include "WPCType.h"
#include "Define.h"
#include "WPCTimer.h"
#include "Data.h"

tTimer16 Timer_PowerOn = {Off, 0u};

void Init_CAN(void)
{
  /* Still 5sec Normal */
  StartTimer(Timer_PowerOn);
  //f_CANStatus = (u8) eN_CAN_Normal;
}
