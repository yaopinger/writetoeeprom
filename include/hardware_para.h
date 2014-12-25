/** \file hardware_para.h
 * \brief  UESTC ES FGEN SERIES
 *
 *  ES1653任意波形发生器硬件参数宏定义
 *  对于控制字 存放多个地址代表控制字位数大于16位 每个地
 *  址最多能存放16位数据 请根据实际硬件设计修改控制字位数
 *  和相应占据的地址个数
 *  对于地址 根据FPGA逻辑程序可能会有较大的变化
 * \author li_chaoran
 * \date 2001 - 2013
 * \copyright (c) 2001-2013, UESTC.  All Rights Reserved.
 *
 */
#ifndef HARDWARE_PARA_H
#define HARDWARE_PARA_H

#include <math.h>

#define pi M_PI        /**< 圆周率 */
/** \name 通道相关宏定义
 * @{
 */

#define CHANNEL_1_OFFSET      (0UL)     /**< 普通模块中通道1对应基地址的偏移量 */
#define CHANNEL_2_OFFSET      (0x40000UL)  /**< 普通模块中通道2对应基地址的偏移量*/
#define CHANNEL_1_RAML_OFFSET (0UL)       /**< 低速ram模块中通道1对应基地址的偏移量 */
#define CHANNEL_2_RAML_OFFSET (0x40000UL)    /**< 低速ram模块中通道2对应基地址的偏移量 */
#define CHANNEL_1_RAMH_OFFSET (0UL)       /**< 高速ram模块中通道1对应基地址的偏移量 */
#define CHANNEL_2_RAMH_OFFSET (0x40000UL)    /**< 高速ram模块中通道2对应基地址的偏移量 */

#define CHANNEL_1_ANALOG_OFFSET (0UL)       /**< 高速ram模块中通道1对应基地址的偏移量 */
#define CHANNEL_2_ANALOG_OFFSET (0x8UL)    /**< 高速ram模块中通道2对应基地址的偏移量 */
#define ANALOG_MODU_OFFSET (0x100UL)    /**< 高速ram模块中通道2对应基地址的偏移量 */
/**@}*/
/** \brief 普通模块中的通道自动选择函数
 *
 * \param channel 通道号（1通道对应1,2通道对应2，以此类推）
 * \return 通道对应地址的偏移量
 */
inline static ViUInt32 select_channel(ViInt8 channel)
{
    switch(channel)
    {
        case 1:
        case 3:
            return CHANNEL_1_OFFSET;
        case 2:
        case 4:
            return CHANNEL_2_OFFSET;
        default:
            return CHANNEL_1_OFFSET;
    }
}

/** \brief 高速ram模块中的通道自动选择函数
 *
 * \param channel 通道号（1通道对应1,2通道对应2，以此类推）
 * \return 通道对应地址的偏移量
 */
inline static ViUInt32 ramh_select_channel(ViInt8 channel)
{
    switch(channel)
    {
        case 1:
        case 3:
            return CHANNEL_1_RAMH_OFFSET;
        case 4:
        case 2:
            return CHANNEL_2_RAMH_OFFSET;
        default:
            return CHANNEL_1_RAMH_OFFSET;
    }
}

/** \brief 低速ram模块中的通道自动选择函数
 *
 * \param channel 通道号（1通道对应1,2通道对应2，以此类推）
 * \return 通道对应地址的偏移量
 */
inline static ViUInt32 raml_select_channel(ViInt8 channel)
{
    switch(channel)
    {
        case 1:
        case 3:
            return CHANNEL_1_RAML_OFFSET;
        case 4:
        case 2:
            return CHANNEL_2_RAML_OFFSET;
        default:
            return CHANNEL_1_RAML_OFFSET;
    }
}

inline static ViUInt32 analog_select_channel(ViInt8 channel)
{
    switch(channel)
    {
        case 1:
            return CHANNEL_1_ANALOG_OFFSET;
            break;
        case 2:
            return CHANNEL_2_ANALOG_OFFSET;
            break;
        case 3:
            return CHANNEL_1_ANALOG_OFFSET + ANALOG_MODU_OFFSET;
            break;
        case 4:
            return CHANNEL_2_ANALOG_OFFSET + ANALOG_MODU_OFFSET;
            break;
        default:
            return CHANNEL_1_ANALOG_OFFSET;
    }
}


/** \brief eeprom模块中的通道自动选择函数
 *
 * \param channel 通道号（1通道对应1,2通道对应2，以此类推）
 * \return 通道对应地址的偏移量
 */
inline static ViUInt32 analog_select_eeprom_channel(ViInt8 channel)
{
    switch(channel)
    {
        case 1:
        case 2:
            return 0;
        case 3:
        case 4:
            return ANALOG_MODU_OFFSET;
        default:
            return 0;
    }
}

/** \name 调制模式宏定义
 * @{
 */
#define STANDARD_WAVE		(0)
#define FM_WAVE				(1)
#define SWEEP_WAVE			(2)
#define AM_WAVE				(3)
#define BURST_WAVE	        (4)
#define FSK_WAVE			(5)
#define PSK_WAVE			(6)
#define PM_WAVE				(7)
/**@}*/
#define SAMPLE_RATE			(600e6)      /**< 最大采样率 */
#define ADDR_STEP           (1)         /**< 地址分配的间距 */
/** \name 常规和任意波形数据参数宏定义
 * @{
 */
#define WFM_DAC_BIT             (14L)    /**< 常规波波形DAC位宽 */
#define WFM_ADDR_BIT            (16)
#define ARB_ADDR_BIT            (22)
#define RAMH_ADDR_BIT           (ARB_ADDR_BIT)
#define WFM_TOTAL_SIZE          (1 << WFM_ADDR_BIT)    /**< 常规波形数据点数 */
#define ARB_TOTAL_SIZE          (1 << ARB_ADDR_BIT)    /**< 任意波形数据点数 */

#define WFM_DATA_BIT            (WFM_ADDR_BIT)	/**< 常规波形数据位宽 */
#define WFM_DATA_QUANTUM        ( (1 << WFM_DAC_BIT) - 1.0 )  /**<  DAC输出数据最大值*/

#define WFM_FAN_SIZE            (WFM_TOTAL_SIZE/2)     /**< 常规波扇区数据点数 */
#define ARB_FAN_SIZE            (WFM_FAN_SIZE)    /**< 任意波扇区数据点数 */
#define WFM_SEG_SIZE            (8192L)	    /**< 常规波形数据段点数 */
#define WFM_SEG_NUM             (WFM_TOTAL_SIZE/WFM_SEG_SIZE)   /**< 常规波形数据段个数 */
#define ARB_SEG_NUM             (ARB_TOTAL_SIZE/WFM_SEG_SIZE)   /**< 任意波形数据段个数 */
#define ARB_SEG_NUM_256K        (ARB_TOTAL_SIZE/WFM_SEG_SIZE/32L)    /**< 任意波形中，256kb数据段个数 */

#define WFM_RAM_NUMBER          (4)	    /**< sram数量 */
#define DDSH_ACCUM_N            (38)    /**< 高速DDS累加器位宽 */

#define PHASE_WORD_BIT          (ARB_ADDR_BIT)    /**< 相位控制字位宽 */
/**@}*/
/** \name 调制波形数据参数宏定义
 * @{
 */
#define DDSL_ADDR_BIT           (14)
#define MODUWAVE_TOTAL_SIZE     (0x01 << DDSL_ADDR_BIT) /**< 调制波波形数据大小 */
#define MODUWAVE_DATA_BIT       (13)        /**< 调制波数据位宽 */
#define MODUWAVE_DATA_QUANTUM   ( (0x01 << MODUWAVE_DATA_BIT) - 1.0 )   /**< 调制波数据宽度 */
#define MODUWAVE_SEG_NUM        (MODUWAVE_TOTAL_SIZE/WFM_SEG_SIZE)  /**< 调制波形数据段个数 */
#define RAML_ADDR_BIT           (DDSL_ADDR_BIT)

#define DDSL_ACCUM_N            (35)        /**< 低速DDS累加器位宽 */
#define DDL_CLK_FREQ            (10e6) /**< 低速DDS时钟频率 */
#define COUNTER_CLK_FREQ        (20e6) /**< 计数时钟频率 */
#define AM_DEPTH_DATABIT        (11)            /**< AM调制深度位宽 */
#define AM_DEPTH_QUANTUM        ((1<<(AM_DEPTH_DATABIT))-1)   /**< AM调制深度总数据点数 */
#define MODU_ADC_DATABIT        (12)            /**< 调制波ADC数据位宽 */
#define MODU_ADC_QUANTUM        ((1<<(MODU_ADC_DATABIT))-1.0) /**< 调制波ADC数据总点数 */
/**@}*/

/** \name 模拟电路参数
 * @{
 */
#define WFM_AMP_DAC_BIT         (10)

#define WFM_OFFSET_DAC_BIT      (16)

#define WFM_DUTY_DAC_BIT        (16)
#define WFM_DUTY_DAC_QUANTUM    ((1<<(WFM_DUTY_DAC_BIT-1))-1.0)

#define SQU_AMP_DAC_BIT         (16)
#define SQU_OFFSET_DAC_BIT      (16)

#define RISING_EDGE_DAC_BIT     (16)
#define FALLING_EDGE_DAC_BIT    (16)

#define OFFSET_CAL_DAC_BIT      (16)
/**@}*/

/** \name 继电器位宏定义
 *
 *  继电器状态量中各个继电器所占的位的位置
 * @{
 */
#define CH1_ATT10               (0)     /**< 1通道10db衰减 */
#define CH1_FILTER_CTRL         (1)     /**< 1通道前级滤波器 */
#define CH2_OUTPUT_CTRL         (2)     /**< 2通道输出*/
#define CH1_OUTPUT_CTRL         (3)     /**< 1通道输出 */
#define CH1_FILTER_2K_CTRL      (4)     /**< 1通道2KHz后级滤波器 */
#define CH1_FILTER_20K_CTRL     (5)     /**< 1通道20KHz后级滤波器 */
#define CH2_FILTER_2K_CTRL      (6)     /**< 2通道2KHz后级滤波器 */
#define CH1_SQUARE_CTRL         (7)     /**< 1波形选择继电器 */
#define CH1_FILTER_2M_CTRL      (8)     /**< 1通道2MHz后级 */
#define CH2_ATT10               (9)     /**< 2通道10db衰减 */
#define CH2_ATT20               (10)    /**< 2通道20db衰减 */
#define CH1_AMP_CTRL            (11)    /**< 1通道20db放大 */
#define CH1_ATT20               (12)    /**< 1通道20db衰减 */
#define CH2_FILTER_CTRL         (13)    /**< 2通道前级滤波器 */
#define CH2_SQUARE_CTRL         (14)    /**< 2通道波形选择 */
#define CH1_FILTER_200K_CTRL    (15)    /**< 1通道200KHz后级滤波器 */
#define CH2_AMP_CTRL            (16)    /**< 2通道20db放大 */
#define CH2_FILTER_200K_CTRL    (17)    /**< 2通道200KHz后级滤波器 */
#define CH2_FILTER_2M_CTRL      (18)    /**< 2通道2MHz后级滤波器 */
#define CH2_FILTER_20K_CTRL     (19)    /**< 2通道20KHz后级滤波器 */
/**@}*/
/** \name 时钟模块
 * @{
 */
#define RAMH_CLK_SEL               (0x2000)
#define CLK_REG_LOW_600M           (0x6000)  /**< 600M reg_low */
#define CLK_REG_HIGH_600M          (0x6001)  /**< 600M reg_high */
#define CLK_SEND_DATA_600M         (0x6002)
#define CLK_SRC_SEL                (0x00)     /**< 选择时钟源 */
#define CLK_SYNC_600M              (0x6003)
#define CLK_REG_LOW_150M           (0x8000)  /**< 150M reg_low */
#define CLK_REG_HIGH_150M          (0x8001)  /**< 150M reg_high */
#define CLK_SEND_DATA_150M         (0x8002)
#define CLK_SYNC_150M              (0x8003)
/**@}*/
/** \name DDS模块
 * @{
 */
#define FTW1_15_0                  (0x00)   /**< 高速DDS的频率控制字 */
#define FTW1_31_16                 (0x01)
#define FTW1_47_32                 (0x02)

#define FTW2_15_0                  (0x03)   /**< FSK的跳变频率控制字*/
#define FTW2_31_16                 (0x04)
#define FTW2_47_32                 (0x05)

#define PTW1_15_0                  (0x06)   /**< 常规波形的相位控制字 */
#define PTW1_31_16                 (0x07)

#define PTW2_15_0                  (0x08)   /**< PSK的跳变相位控制字 */
#define PTW2_31_16                 (0x09)

#define DELTA_FTW_15_0             (0x0a)   /**< FM的步进相位控制字 */
#define DELTA_FTW_31_16            (0x0b)

#define DELTA_PTW_15_0             (0x0c)   /**< PM的步进相位控制字 */

#define ADDR_WIDTH_SEL             (0x0d)  /**< 波形宽度设置 */

#define RAMH_WR_CTRL               (0x0e)  /**< ramh写控制 */
#define RAMH_RD_CTRL               (0x0f)  /**< ramh读控制 */
#define RAMH_ADDR_SEL              (0x10)
#define RAMH_SEL                   (0x12)
#define RAMH_FAN_SEL               (0x00)  /**< ramh扇区选择 */
/**@}*/
/** \name modu模块
 * @{
 */
#define PLL_CLK                    (0x16)
#define EXT_MODU_EN                (0x00)  /**< 外部调制使能 */
#define MODU_SRC_SEL               (0x01)  /**< 调制源选择 */

#define BURST_RESET                (0x05)   /**<触发信号的初始化*/

#define INT_TRIG_COUNTER_15_0      (0x02)  /**< 触发信号频率控制字 */
#define INT_TRIG_COUNTER_31_16     (0x03)
#define RESET_COUNTER               (0x04)  /**< 设置counter后需要重置counter */
#define EXT_TRIG_SEL                (0x05)  /**< 外部触发信号选择 */
#define TRIG_POLAR_SEL              (0x06)  /**< 触发极性 */
#define TRIG_SRC_SEL                (0x07)  /**< 触发源选择 */
#define SINGLE_TRIG                 (0x08)  /**< 软件触发选择 */
#define MODU_MODE_SEL               (0x09)  /**< 调制模式选择 */
#define OPERATION_MODE_SEL          (0x0a)  /**< 触发方式 */
#define CLR_DDSH_CTRL               (0x0b)  /**< DDS使能信号 */
#define CTRL_TRIG_OUT               (0x0d)  /**< 对外提供触发信号的端口 */

#define BURST_COUNTER_15_0          (0x0e)  /**< busrt计数 */
#define BURST_COUNTER_31_16         (0x0f)
#define MODU_DEPTH                  (0x10)  /**< 调制深度 */
#define SYNC_OUT_ENABLE             (0x11)  /**< 同步时钟信号使能 */

#define DDSL_FTW_15_0               (0x12)  /**< 调制波DDS频率控制字 */
#define DDSL_FTW_31_16              (0x13)
#define DDSL_FTW_47_32              (0x14)

#define BURST_POL_SEL               (0x15)  /**< burst 触发极性 */
//#define SEL_CH                      (0x54)  /**< 同步信号输出通道选择 */
#define CTRL_SYNC                   (0x0003)  /**< 同步输出使能 */
/**@}*/
/** \name DAC模块
 * @{
 */
#define DAC_W1_EN                    (0x00)  /**< DAC地址 */
#define DAC_INIT                     (0x01)
#define DAC_RESET                    (0x02)
#define DAC_R2_EN                    (0x03)
#define DAC_CHECK                    (0x04)
#define DAC_READ                     (0)
/**@}*/
/** \name analog模块
 * @{
 */
#define EEPROM_SEL_MODE             (0x01)  /**< eepROM模式选择地址 */
#define EEPROM_ADDR_15_0            (0x02)  /**< eepROM页面地址 */
#define EEPROM_ADDR_31_16           (0x03)
#define EEPROM_WRITE_DATA           (0x4)  /**< eepROM写数据地址 */
#define EEPROM_ENABLE               (0x5)  /**< eepROM使能 */
#define EEPROM_RESET                (0x06)
#define EEPROM_COMFIR_MODE          (0x09)
#define EEPROM_READ_DATA            (0xe)  /**< eepROM读数据地址 */
#define EEPROM_STATUS               (0xf)  /**< eepROM状态 */
/**@}*/
/** \name TPCI6595模块
 * @{
 */
#define TPCI_RELAY_15_0             (0x04)  /**< 继电器状态量 */
#define TPCI_RELAY_31_16            (0x08)
#define TPCI_RELAY_ENABLE           (0x0C)  /**< 继电器使能 */
/**@}*/
/** \name DAC8560模块
 * @{
 */
#define TRIGGER_SLOPE_15_0          (0x00)  /**< 外部触发电平 */
#define TRIGGER_SLOPE_31_16         (0x01)
#define TRIGGER_SLOPE_ENABLE        (0x03)  /**< 外部触发电平配置使能 */
#define DAC8560_OFFSET_CAL_CH1      (0)     /**< 1通道偏移设置 */
#define DAC8560_AMP_CAL_CH1         (1)     /**< 1通道幅度设置 */
#define DAC8560_DUTY_CAL_CH1        (2)     /**< 1通道占空比设置 */
#define DAC8560_OFFSET_CAL_CH2      (3)     /**< 2通道偏移设置 */
#define DAC8560_DUTY_CAL_CH2        (4)     /**< 2通道占空比设置 */
#define DAC8560_AMP_CAL_CH2         (6)     /**< 2通道幅度设置 */
/**@}*/

/**@}*/
/** \name 9747模块
 * @{
 */
#define ZERO_OFFSET_CH1             (1.465)     /**< 9747 1通道削偏参数 */
#define ZERO_OFFSET_SQUARE_CH1      (1.449)     /**< 9747 1通道方波削偏参数 */
#define ZERO_OFFSET_CH2             (1.429)     /**< 9747 2通道削偏参数 */
#define ZERO_OFFSET_SQUARE_CH2      (1.419)     /**< 9747 2通道方波削偏参数 */
/**@}*/
/** \name 8560系数
 * @{
 */
#define DAC8560_SCOPE              (2.5)
#define DAC8560_BIT_WIDTH          (16)
/**@}*/

/** \name RAM读写模式
 * @{
 */
#define RAM_MODE_CPU_ADDR           (0)
#define RAM_MODE_DDS_ADDR           (1)
/**@}*/

/** \name SEQ模块
 * @{
 */
#define SEQ_LENGTH_15_0                 (0x0000)
#define SEQ_COUNT_15_0                  (0x8000)
#define SEQ_ADDR_15_0                   (0xC000)
#define SEQ_NUM                         (0x4003)
#define SEQ_LENGTH_31_16                (0x4000)
#define SEQ_COUNT_31_16                 (0x4001)
#define SEQ_ADDR_31_16                  (0x4002)
#define SEQ_RESET                       (0x4004)
#define OPT_MODE_CH1                    (0x4005)
#define OPT_MODE_CH3                    (0x4005)
#define OPT_MODE_CH2                    (0x4006)
#define OPT_MODE_CH4                    (0x4006)

/**@}*/
#endif /* HARDWARE_PARA_H*/
