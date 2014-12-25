/** \file hw_utility.c
 * \brief  UESTC ES FGEN SERIES
 *
 * ES1653位运算和延时函数实现
 * \author li_chaoran
 * \date 2001 - 2013
 * \copyright (c) 2001-2013, UESTC.  All Rights Reserved.
 *
 */
#include "hw_utility.h"
#if (defined (_WIN32)||defined(_WIN64))
#define WIN_TIME
#include <windows.h>
#elif (defined (__unix)||defined(__linux)||defined(linux)|| defined(__unix__))
#define LINUX_TIME
#include <unistd.h>
#else
#error no platform info
#endif // if

/** \brief 置位函数.
 *
 * 将bit位置1
 * \param data 要操作的32位数据
 * \param bit 要设置的位
 * \return 操作后的32位数据
 *
 */
ViUInt32 setbit32(ViUInt32 data, ViUInt32 bit)
{
	data = (data | (0x0001UL<<bit));
	return data;
}

/** \brief 清零函数.
 *
 * 将bit位清零
 * \param data 要操作的32位数据
 * \param bit 要清零的位
 * \return 操作后的32位数据
 *
 */
ViUInt32 clrbit32(ViUInt32 data, ViUInt32 bit)
{
	data = ( data & ( ~(0x0001UL<<bit) ) );
	return data;
}

/** \brief 延时函数 us级
 *
 *  windows下的Sleep函数精度较低
 * \param t 延时的时间长度 单位us
 *
 */

void delay_us(ViUInt32 t)     //延迟 t us
{
#ifdef WIN_TIME
	Sleep(t/1000);
#else
    usleep(t);
#endif

}

/** \brief 延时函数 ns级
 *
 *  精度不太可靠
 * \param dly 延时的时间长度 单位ns
 *
 */
void delay_ns(ViUInt32 dly) //延时dly ns
{
	ViUInt32  i,j,t = 0;

	for(i=0; i<dly; i++)
	{
		for(j=0; j<40; j++)
		{
			t += j;
		}
	}
}

void delay(ViInt32 i)
{
    while(i--)
        ;
}
