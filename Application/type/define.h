/*******************************************************************************
 * Project        :   SP2 IBU
 * File Name      :   define.h
 * Compiler   :   Eclipse
 * Author         :   MyoungKwon Choi (mk210@seoyonelec.com)
 * Created at     :   2017-06-15
 * Code Editor  :   Source Insight (Recomended Font : D2Coding / Size 10)
 * Revision       :   Version 0.1
 * Copyright    :   (c) Copyright Seoyon Electronisc Co.Ltd. All Rights Reserved
 * Description    :   This is a header file associated with constants & macro.
 *
 *******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------*/
#ifndef __DEFINE_H__
#define __DEFINE_H__




/*******************************************************************************
  Define Constants
*******************************************************************************/

/* LowPower */
#define   LP_OK 1u
#define   LP_NO 0u

#define kOn       1u
#define kOff      0u

#define On        1u
#define Off       0u

#define kHigh     1u
#define kLow      0u


/*******************************************************************************
  Define Macro
*******************************************************************************/
#define Time5msTASK_sec(x)      ((x)*200u)
#define Time_ms(x)              ((x)/10u)
#define	Time_sec(x)			        ((x)*100U)


#define GetX(var)               (var).New                                       // GetQue
#define GetXOld(var)            (var).Old                                       // GetQueOld


#define SetX(var,val)           {(var).Old = (var).New; (var).New = (val);}    	// SetQue
#define IsChgEvt(var,val)       (((var).Old!=(val))&&((var).New==(val)))     	  // GetQueChange
#define	IsDiffEvt(var)		      ((var).Old!=(var).New)							              // GetQueDiff
#define ClrEvt(var)             ((var).Old=(var).New)                         	// ClrQueChange


#define SetOutput(var,val)      {(var).Old = (var).New; (var).New = (val);}    // #define SetOutput(x,y)    {u8_OutputValue[x] = y;}  /* x(u8), y(u8) */
#define GetOutput(var)          (var).New                                      // #define GetOutput(x)   u8_OutputValue[x]
#define GetOutput_IOCBI(x)		u8_OutputValue[x]

#define Set_All(var,val)        {var.Old = (val);var.New = (val);}

/* Wait Sleep */
#define Par_Sleep_Wait_Time Time_sec(5)
#define Par_PowerOn_Wait_Time Time_sec(5)

#define Par_DiagStateTime       Time_sec(5)

//#define ERR_NONE 0

extern uint8 Hash_Calculation_Check;
extern uint8 Diag_HashData[];









#endif  /* __DEFINE_H__ */
