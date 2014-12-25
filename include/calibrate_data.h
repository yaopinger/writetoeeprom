/** \file calibrate_data.h
 * \brief  UESTC ES FGEN SERIES
 *
 * 模拟通道校正数据处理函数声明
 * \author li_chaoran
 * \date 2001 - 2013
 * \copyright (c) 2001-2013, UESTC.  All Rights Reserved.
 *
 */
#ifndef CALIBRATE_DATA_H_INCLUDED
#define CALIBRATE_DATA_H_INCLUDED

#include "ES1653.h"
/** \def INIT_EEPROM
 *
 * 定义该宏，则在初始化时将校正数据重新写入eepROM，用于更新校正数据和初次写入校正数据
 */
//#define INIT_EEPROM
/** \def CAL_DATA_BIT
 *
 * 校正数据的字数，通常采用ViReal64即64位浮点数
 */
#define CAL_DATA_BIT            (4UL)
/** \def EEPROM_MODULE
 *
 * 定义该宏，表示已加载eeprom模块
 */
//#define EEPROM_MODULE       //
/** \name 校正开关
 * @{
 */
#define AMP_CAL                     /* 定义该宏，则开启幅度校正 */
#define	DUTY_CAL                    /* 定义该宏，则开启占空比校正 */
#define OFFSET_CAL                  /* 定义该宏，则开启偏移校正 */
//#define AMP_FREQ_CAL                /* 定义该宏，则开启幅频校正 */
/**@}*/
/** \name 校正数据段的大小
 * @{
 */
#define BOARD_AMOUNT                (4)

#define AMP_SEG_POINT_NUMBER        (7)
#define AMP_CAL_POINT_NUMBER        (7)
#define AMP_CAL_DATA_NUMBER         (36)
#define FREQ_SEG_POINT_NUMBER       (42)
#define AMP_FREQ_DATA_NUMBER        (36*6)
#define AMP_FREQ_SEG_DATA_NUMBER    (36)

#define OFFSET_CAL_DATA_NUMBER      (36)
#define OFFSET_BIAS_CAL_DATA_NUMBER (36)
#define DUTY_CAL_DATA_NUMBER        (13)

#define UNIQUE_1V_AMP_DATA_NUMBER            6
#define UNIQUE_1V_OFFSET_DATA_NUMBER         6
#define UNIQUE_1V_OFFSET_BIAS_DATA_NUMBER    6
#define UNIQUE_1V_AMP_RANGE_MAX_NUMBER       1
#define UNIQUE_1V_AMP_RANGE_MIN_NUMBER       1


#define CAL_POINT_NUM           (1 + AMP_SEG_POINT_NUMBER + AMP_CAL_POINT_NUMBER + AMP_CAL_DATA_NUMBER + FREQ_SEG_POINT_NUMBER +    \
                                 AMP_FREQ_DATA_NUMBER + OFFSET_CAL_DATA_NUMBER + OFFSET_BIAS_CAL_DATA_NUMBER + DUTY_CAL_DATA_NUMBER + \
                                 UNIQUE_1V_AMP_DATA_NUMBER + UNIQUE_1V_OFFSET_DATA_NUMBER + UNIQUE_1V_OFFSET_BIAS_DATA_NUMBER + \
                                 UNIQUE_1V_AMP_RANGE_MAX_NUMBER + UNIQUE_1V_AMP_RANGE_MIN_NUMBER)     /* 每个通道总校正数据个数 */
/**@}*/


ViStatus cal_init(ES1653_Ch *phch);
ViStatus cal_close(ES1653_Ch *phch);
void cal_init_eeprom(ES1653_Ch *phch);
ViStatus cal_read_eeprom(ES1653_Ch *phch);
#endif /* CALIBRATE_DATA_H_INCLUDED*/
