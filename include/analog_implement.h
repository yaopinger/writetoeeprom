/** \file analog_implement.h
 * \brief  UESTC ES FGEN SERIES
 *
 * 模拟通道硬件层声明
 * \author li_chaoran
 * \date 2001 - 2013
 * \copyright (c) 2001-2013, UESTC.  All Rights Reserved.
 *
 */
#ifndef ANALOG_IMPLEMENT_H_INCLUDE
#define ANALOG_IMPLEMENT_H_INCLUDE
/** \name 继电器变量中，具体位的意义，0代表第一位
 * @{
 */
#define DDS_FILTER_CTRL_BIT             (0)
#define WAVEFORM_CTRL_BIT               (1)
#define ATTENTUATION_10DBC_CTRL_BIT     (2)
#define ATTENTUATION_20DBC_CTRL_BIT     (3)
#define AMPLIFIER_CTRL_BIT              (4)
#define OUTPUT_FILTER_CTRL_BIT          (5)
#define ANALOG_OUTPUT_ENABLE_BIT        (6)

#define ES1653_VAL_SEGMENT_NUMBER_MAX   (6)
#define ES1653_VAL_FREQ_SEGMENT_NUMBER_MAX   (6)

#define OFFSET_CH1  0
#define ANALOG_CH1_CTL_RELAY  2
#define AMP_CH1     3
#define DUTY_CH1    4
#define SQUARE_MODULATE 5
#define ANALOG_CH1_START  6
#define ANALOG_CH1_RESET  7

/*
1V左右的幅度做特殊的处理
*/
#define UNIQUE_1V_AMP_FREQ_CAL_POINT_MAX 1000000

#define UNIQUE_1V_AMP_POINT_MAX 1.2
#define UNIQUE_1V_AMP_POINT_MIN 0.8

/**@}*/
/** \name EEPROM相关定义
 * @{
 */
#define EEPROM_MODE_WR              (0x01)      /**< eepROM写模式 */
#define EEPROM_MODE_RD              (0x00)      /**< eepROM读模式 */
#define EEPROM_BASE_ADDR            (0x0000)
/**@}*/
/** \def ANALOG_MODULE
 *
 * 定义该宏，表示已经安装了模拟通道，如果取消定义该宏，则表示未使用模拟通道
 */
#define ANALOG_MODULE

/************		参数设置 		***************/
void set_DAC8560_amp(ES1653_Ch* phch, ViUInt32 ctrl_code);
void set_DAC8560_offset(ES1653_Ch* phch, ViUInt32 ctrl_code);
void set_DAC8560_duty(ES1653_Ch* phch, ViUInt32 ctrl_code);
void set_DAC8560_square_modulate(ES1653_Ch* phch, ViUInt32 ctrl_code);
void switch_analog_relays(ES1653_Ch* phch, ViUInt32 ctrl_code);
/************		继电器控制		***************/
ViUInt32 sel_attenuation(ES1653_Ch* phch, ViInt32 amp_segment_number);
ViUInt32 sel_amplifier(ES1653_Ch* phch, ViInt32 amp_segment_number);
ViUInt32 sel_waveform(ES1653_Ch* phch, ViInt32 waveform);
ViUInt32 sel_output_filter(ES1653_Ch* phch,  ViInt32 waveform);
ViUInt32 sel_dds_filter(ES1653_Ch* phch, ViInt32 waveform);
ViUInt32 sel_frequency_filter(ES1653_Ch *phch, ViReal64 frequency);

/************		校正函数		****************/
ViReal64 map_function(ViReal64 var, ViPReal64 cal_data_point);
ViInt32 get_amplitude_segment_number(ES1653_Ch* phch, ViReal64 amplitude);
ViInt32 get_frequency_segment_number(ES1653_Ch* phch, ViInt32 amp_segment_number, ViReal64 amplitude);

/************		eeprom控制		****************/
void eeprom_sel_mode(ES1653_Ch *phch, ViInt16 mode);
ViUInt16 eeprom_read_data(ES1653_Ch *phch);
void eeprom_write_data(ES1653_Ch *phch, ViUInt16 data);
void eeprom_enable(ES1653_Ch *phch);
void eeprom_set_addr(ES1653_Ch *phch, ViInt32 page_addr);
void eeprom_reset(ES1653_Ch *phch);

#endif
