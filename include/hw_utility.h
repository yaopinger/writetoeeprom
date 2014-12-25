/** \file hw_utility.h
 * \brief  UESTC ES FGEN SERIES
 *
 * ES1653位运算和延时函数声明
 * \author li_chaoran
 * \date 2001 - 2013
 * \copyright (c) 2001-2013, UESTC.  All Rights Reserved.
 *
 */
#ifndef  _HW_UTILITY_H_
#define  _HW_UTILITY_H_

	#include "vpptype.h"

	ViUInt32 setbit32(ViUInt32 data, ViUInt32 bit);
	ViUInt32 clrbit32(ViUInt32 data, ViUInt32 bit);
	void delay_us(ViUInt32 t) ;
	void delay_ns(ViUInt32 dly);
	void delay(ViInt32 i);
#endif
