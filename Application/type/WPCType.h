/*
 * Type.h
 *
 *  Created on: 2017. 9. 13.
 *      Author: Seoyon
 */

/* Define to prevent recursive inclusion -------------------------------------------------------*/
#ifndef WPC_TYPE_H_
#define WPC_TYPE_H_


/*******************************************************************************
	Define tVARs Type
*******************************************************************************/
/* Common Type defines -------------------------------------------------------*/
typedef	signed char		s8;
typedef	unsigned char	u8;
typedef	signed short	s16;
typedef	unsigned short	u16;
typedef	signed long	    s32;
typedef	unsigned long	u32;
typedef	float		    f32;
typedef	double		    f64;

typedef unsigned char		T_UBYTE;
typedef unsigned int		T_UWORD;
typedef unsigned long		T_ULONG;
typedef signed char			T_SBYTE;
typedef signed int			T_SWORD;
typedef signed long			T_SLONG;
typedef unsigned int		T_FLAG_ARRAY;

/* Super State Type defines --------------------------------------------------*/
typedef const struct _tSTATE{
	void (*en)();
	const struct _tSTATE* (*init)();
	void (*du)();
	void (*ex)();
	unsigned char (*run)();
	const struct _tSTATE* parent;
}tSTATE;

#define rom_tbl const

typedef struct
{
	u8	new_input;
	u8	old_input;
} QueInput;

typedef struct
{
	u16	new_input_u16;
	u16	old_input_u16;
} QueInput_u16;

/*******************************************************************************
	Define Timer tVARs
*******************************************************************************/
typedef struct
{
	u8	run;
	u8	time;
} tTimer8;

typedef struct
{
	u8	run;
	u16	time;
} tTimer16;

typedef struct
{
	u8	run;
	u32	time;
} tTimer32;

/* bit assign type */
typedef union
{
	struct{
		unsigned	b0:1;
		unsigned	b1:1;
		unsigned	b2:1;
		unsigned	b3:1;
		unsigned	b4:1;
		unsigned	b5:1;
		unsigned	b6:1;
		unsigned	b7:1;
	}bit;
	u8 byte;
} flag8;

/* bit assign type */
typedef union
{
	u16 word;
	struct{
		u8	b0:1;
		u8	b1:1;
		u8	b2:1;
		u8	b3:1;
		u8	b4:1;
		u8	b5:1;
		u8	b6:1;
		u8	b7:1;
		u8	b8:1;
		u8	b9:1;
		u8	b10:1;
		u8	b11:1;
		u8	b12:1;
		u8	b13:1;
		u8	b14:1;
		u8	b15:1;
	}bit;
} flag16;

typedef union
{
  struct
  {
    unsigned  b0: 1;
    unsigned  b1: 1;
    unsigned  b2: 1;
    unsigned  b3: 1;
    unsigned  b4: 1;
    unsigned  b5: 1;
    unsigned  b6: 1;
    unsigned  b7: 1;
    unsigned  b8: 1;
    unsigned  b9: 1;
    unsigned  b10: 1;
    unsigned  b11: 1;
    unsigned  b12: 1;
    unsigned  b13: 1;
    unsigned  b14: 1;
    unsigned  b15: 1;
  }Bit;
  u16 Word;
}stCanAppFlag;

// ST RFAL
#define ST_MEMMOVE          memmove     /*!< map memmove to string library code */
#define ST_MEMCPY           memcpy      /*!< map memcpy to string library code  */
#define ST_MEMSET           memset      /*!< map memset to string library code  */
#define ST_BYTECMP          memcmp      /*!< map bytecmp to string library code */



/*************** AUTOSAR API ********************/
#include "Rte_Type.h"
/*************** AUTOSAR API ********************/

#endif /* 10W_TYPE_H_ */
