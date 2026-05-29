#include "RomTst.h"
#include "Cdd_RomTst.h"

void RomTst_TestCompletedNotification(void)
{
  /* Do something */
  // TestRomTst_CddCompletedNotif = TRUE;
}

RomTst_CodeFlashIdType RomTst_GetActiveCodeFlashId(void)
{
  RomTst_CodeFlashIdType retVal;

  if (1)
  {
    retVal = ROMTST_CODE_FLASH_ID_1;
  }
  else
  {
    retVal = ROMTST_CODE_FLASH_ID_2;
  }

  return retVal;
}
