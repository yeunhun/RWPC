

#include "WPCType.h"
#include "Define.h"
#include "WPCTimer.h"
#include "Data.h"

#include "app_can_output_type.h"
#include "app_can_output.h"

#include "WPCDiagonostic.h"

typedef enum
{
  DiagState_Off = 0,
  DiagState_On
} e_DiagState_List;

void DiagStateTimer(void)
{
  static  e_DiagState_List  Sts_DiagStep = DiagState_Off;
  static  tTimer16          tmr_DiagStateTime = {Off, 0U};

  //ClrEvt(b_BCMDiagStateTimerStart);

  UpTimer16(tmr_DiagStateTime);

  switch(Sts_DiagStep)
  {
    case  DiagState_Off:
      if(GetX(kb_WPCDiagStateTimerStart) == On)
      {
        StartTimer(tmr_DiagStateTime);
        SetX(kb_WPCDiagStateTimerStart, Off);
        Sts_DiagStep = DiagState_On;
      }
      break;
    case  DiagState_On:
      if(GetOutput(kC_WPCDiagState) == Off)
      {
        //StopDiag_BCMForcedOutput();
        CancelTimer(tmr_DiagStateTime);
        Sts_DiagStep = DiagState_Off;
      }
      else if(GetX(kb_WPCDiagStateTimerStart) == On)
      {
        StartTimer(tmr_DiagStateTime);
        SetX(kb_WPCDiagStateTimerStart, Off);
      }
      else if((tmr_DiagStateTime.run==On)&&
          (tmr_DiagStateTime.time>=Par_DiagStateTime))
      {
        //StopDiag_BCMForcedOutput();
        CancelTimer(tmr_DiagStateTime);
        SetOutput(kC_WPCDiagState, Off);


        DTC_Set_Status = On;


        Sts_DiagStep = DiagState_Off;
      }
      else
      {
        /* MISRA-Rule */
      }
      break;
    default:
      Sts_DiagStep = DiagState_Off;
      break;
  }
}
