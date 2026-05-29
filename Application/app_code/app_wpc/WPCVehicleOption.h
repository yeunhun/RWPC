/*
 *  WPCVehicleOption.h
 *
 *  Created on: 2018. 10. 15.
 *  Author: Seoyon
 */

#ifndef WPC_VEHICLE_OPTION_H_
#define WPC_VEHICLE_OPTION_H_

/* Vehicle */ /* Non NFC : ����_N */
#define RG3_PE_R
#define USE_OVER_VOLTAGE_CHARGE_IC_PROTECT
#define USE_CHARGE_IC_RUN_MODE_7sec_RESET
#define USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF
#define USE_CHARGE_IC_FWver_READ
/* Vehicle Option */


/* LED Output Option : Rheostat */
/* LED Control Option */
#if defined(JX1_PE_R) || defined(RG3_PE_R) || defined(RG3_PE_EV_R) 
#define USE_DETENTOUT
	#if defined (JX1_PE_R) || defined(RG3_PE_R) || defined(RG3_PE_EV_R)
	#define USE_AUTOBRIGHT
	#endif
#endif

#endif /* WPC_VEHICLE_OPTION_H_ */

