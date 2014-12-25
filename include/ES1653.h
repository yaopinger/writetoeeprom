/** \file ES1653.h
 * \brief  UESTC ES FGEN SERIES
 *
 * ES1653任意波形发生器接口层函数声明和宏定义
 * \author li_chaoran
 * \date 2001 - 2013
 * \copyright (c) 2001-2013, UESTC.  All Rights Reserved.
 *
 */

#ifndef _ES1653_H_
#define _ES1653_H_

#include <ivifgen.h>
#include <ivi.h>
#include <visatype.h>
#include <list.h>
#include "hardware_para.h"
//#define SIZE                (50L)
//#define BUF_SIZE            (100L)
//#define build_ES1653
#ifdef build_ES1653
#define ES1653_dll __declspec(dllexport)
#else
#define ES1653_dll __declspec(dllimport)
#endif
#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif

#define get_fpga(phch) (ViInt8)(~(phch->channel/3)&0x01)
inline static  ViUInt32 convert_signed(ViUInt32 data)
{
    if((data & 0x2000))
    {
        data &= 0x1fff;
    }
    else //12λ?0
    {
        data |= 0x02000;
    }

    return data;
}
/****************************************************************************
 *--------------------- Instrument Driver Information ----------------------*
 ****************************************************************************/
#define ES1653_MAJOR_VERSION                1     /* Instrument driver major version   */
#define ES1653_MINOR_VERSION                0     /* Instrument driver minor version   */

#define ES1653_CLASS_SPEC_MAJOR_VERSION     1     /* Class specification major version */
#define ES1653_CLASS_SPEC_MINOR_VERSION     0     /* Class specification minor version */

#define ES1653_SUPPORTED_INSTRUMENT_MODELS  "ES1653"

#define ES1653_DRIVER_VENDOR                "UESTC"

#ifdef	_IVI_mswin64_
#define ES1653_DRIVER_DESCRIPTION           "UESTC ES Series Arbitrary Function Generator [Compiled for 64-bit.]"
#else
#define ES1653_DRIVER_DESCRIPTION	    "UESTC ES Series Arbitrary Function Generator"
#endif

#define ES1653_IO_SESSION_TYPE              "VISA"
#define ES1653_VAL_CHANNEL_TABLE			"1,2,3,4"
#define ES1653_VAL_CHANNEL_COUNT			 4
/*****************************************************************************
**--------------------- Hidden Attribute Declarations -----------------------*
******************************************************************************/
/** \name 参数范围宏定义
 *
 *  根据指标修改其中的上下限值 其中幅度 偏移单位为伏(v) 频率单位为赫兹Hz
 * @{
*/
#define ES1653_VAL_OFFSET_MIN              (-2.5)  /**< 偏移最小值 */
#define ES1653_VAL_OFFSET_MAX              (2.5)   /**< 偏移最大值 */

#define ES1653_VAL_DC_AMPLITUDE_MIN           (0.01)  /**< DC幅度最小值 */
#define ES1653_VAL_DC_AMPLITUDE_MAX           (10)    /**< DC幅度最大值 */

#define ES1653_VAL_WFM_AMPLITUDE_MIN       (0.01)  /**< 常规波幅度最小值 */
#define ES1653_VAL_WFM_AMPLITUDE_MAX       (4.5)   /**< 常规波幅度最大值 */

#define ES1653_VAL_SINE_WFM_FREQ_MIN       (10e-3) /**< 正弦波最小频率 */
#define ES1653_VAL_SINE_WFM_FREQ_MAX       (240e6)  /**< 正弦波最大频率 */

#define ES1653_VAL_SQUARE_WFM_FREQ_MIN     (10e-3) /**< 方波最小频率 */
#define ES1653_VAL_SQUARE_WFM_FREQ_MAX     (100e6)  /**< 方波最大频率 */

#define ES1653_VAL_PULSE_WFM_FREQ_MIN      (10e-3) /**< 脉冲波最小频率 */
#define ES1653_VAL_PULSE_SQUARE_FREQ_MAX   (1e6)
#define ES1653_VAL_PULSE_BURST_FREQ_MIN    ES1653_VAL_PULSE_SQUARE_FREQ_MAX
#define ES1653_VAL_PULSE_WFM_FREQ_MAX      (100e6)  /**< 脉冲波最大频率 */

#define ES1653_VAL_WFM_FREQ_MIN            (10e-6) /**< 常规波形最小频率 */
#define ES1653_VAL_WFM_FREQ_MAX            (240e6)  /**< 常规波形最大频率 */

#define ES1653_VAL_ARB_FREQ_MIN            (10e-6) /**< 任意波形最小频率 */
#define ES1653_VAL_ARB_FREQ_MAX            (10e6)  /**< 任意波形最大频率 */

#define ES1653_VAL_MODULATION_FREQ_MIN     (10e-3) /**< 调制波最小频率 */
#define ES1653_VAL_MODULATION_FREQ_MAX     (50e3)  /**< 调制波最大频率 */

#define ES1653_VAL_SQUARE_WFM_DUTY_MIN     (20)    /**< 方波最小占空比 */
#define ES1653_VAL_SQUARE_WFM_DUTY_MAX     (80)    /**< 方波最大占空比 */
#define ES1653_VAL_SQUARE_HF_DUTY_MIN      (40)    /**< 高频方波最小占空比 */
#define ES1653_VAL_SQUARE_HF_DUTY_MAX      (60)    /**< 高频方波最大占空比 */

#define ES1653_VAL_HF_SQUARE_FREQ_MIN     (1e6)   /**< 高频方波最小频率 */
/****************************************************************************
 *------------------------------ User Macros -------------------------------*
 ****************************************************************************/
    /* Channel Name */
#define ES1653_VAL_CHANNEL_1                "1"    /*channel one          */
#define ES1653_VAL_CHANNEL_2                "2"    /*channel two          */
#define ES1653_VAL_CHANNEL_3                "3"    /*channel three        */
#define ES1653_VAL_CHANNEL_4                "4"    /*channel four         */
    /* Trigger Slope Standard */
#define TRIGGER_SLOPE_TTL
#define TRIGGER_SLOPE_ECL
#define TRIGGER_SLOPE_RTSI
#define TRIGGER_SLOPE_PXI
	/* Arb Waveform Length */
#define ES1653_ARB_WAVEFORM_NAME_LEN				(50L)
/****************************************************************************
 *---------------------------- Attribute ID Defines ---------------------------*
 ****************************************************************************/

    /*- IVI Inherent Instrument Attributes ---------------------------------*/

        /* User Options */
#define ES1653_ATTR_RANGE_CHECK                   IVI_ATTR_RANGE_CHECK                    /* ViBoolean */
#define ES1653_ATTR_QUERY_INSTRUMENT_STATUS       IVI_ATTR_QUERY_INSTRUMENT_STATUS        /* ViBoolean */
#define ES1653_ATTR_RECORD_COERCIONS              IVI_ATTR_RECORD_COERCIONS               /* ViBoolean */

#define ES1653_ATTR_DRIVER_SETUP                  IVI_ATTR_DRIVER_SETUP
#define ES1653_ATTR_INTERCHANGE_CHECK             IVI_ATTR_INTERCHANGE_CHECK
                /* ViInt32,  read-only  */

        /* Driver Information  */
#define ES1653_ATTR_INSTRUMENT_MODEL              IVI_ATTR_INSTRUMENT_MODEL               /* ViString, read-only  */
#define ES1653_ATTR_INSTRUMENT_FIRMWARE_REVISION  IVI_ATTR_INSTRUMENT_FIRMWARE_REVISION   /* ViString, read-only  */


/*- Instrument-Specific Attributes -------------------------------------*/

    /*- Basic Instrument Operation -----------------------------------------*/
#define ES1653_ATTR_CHANNEL_COUNT			 IVIFGEN_ATTR_CHANNEL_COUNT
#define ES1653_ATTR_OPERATION_MODE           IVIFGEN_ATTR_OPERATION_MODE          /* ViInt32    multi-channel        */
#define ES1653_ATTR_OUTPUT_MODE              IVIFGEN_ATTR_OUTPUT_MODE             /* ViInt32                         */
#define ES1653_ATTR_REF_CLOCK_SOURCE         IVIFGEN_ATTR_REF_CLOCK_SOURCE        /* ViInt32                         */
#define ES1653_ATTR_OUTPUT_ENABLED           IVIFGEN_ATTR_OUTPUT_ENABLED          /* ViBoolean, multi-channel        */
#define ES1653_ATTR_OUTPUT_IMPEDANCE         IVIFGEN_ATTR_OUTPUT_IMPEDANCE        /* ViReal64,  multi-channel, ohms  */
#define ES1653_ATTR_RELAY_REG                (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 1L)
    /*- Standard Waveform Generation ---------------------------------------*/

#define ES1653_ATTR_FUNC_WAVEFORM            IVIFGEN_ATTR_FUNC_WAVEFORM           /* ViInt32,  multi-channel           */
#define ES1653_ATTR_FUNC_AMPLITUDE           IVIFGEN_ATTR_FUNC_AMPLITUDE          /* ViReal64, multi-channel, volts    */
#define ES1653_ATTR_FUNC_DC_OFFSET           IVIFGEN_ATTR_FUNC_DC_OFFSET          /* ViReal64, multi-channel, volts    */
#define ES1653_ATTR_FUNC_FREQUENCY           IVIFGEN_ATTR_FUNC_FREQUENCY          /* ViReal64, multi-channel, hertz    */
#define ES1653_ATTR_FUNC_START_PHASE         IVIFGEN_ATTR_FUNC_START_PHASE        /* ViReal64, multi-channel, degrees  */
#define ES1653_ATTR_FUNC_DUTY_CYCLE_HIGH     IVIFGEN_ATTR_FUNC_DUTY_CYCLE_HIGH    /* ViReal64, multi-channel, percent  */

    /*- Arbitrary Waveform Generation --------------------------------------*/

#define ES1653_ATTR_ARB_WAVEFORM_HANDLE       IVIFGEN_ATTR_ARB_WAVEFORM_HANDLE    /* ViInt32,  multi-channel         */
#define ES1653_ATTR_ARB_GAIN                  IVIFGEN_ATTR_ARB_GAIN               /* ViReal64, multi-channel         */
#define ES1653_ATTR_ARB_OFFSET                IVIFGEN_ATTR_ARB_OFFSET             /* ViReal64, multi-channel, volts  */
#define ES1653_ATTR_ARB_SAMPLE_RATE           IVIFGEN_ATTR_ARB_SAMPLE_RATE        /* ViReal64, samples-per-second    */

#define ES1653_ATTR_MAX_NUM_WAVEFORMS         IVIFGEN_ATTR_MAX_NUM_WAVEFORMS      /* ViInt32,  read-only             */
#define ES1653_ATTR_WAVEFORM_QUANTUM          IVIFGEN_ATTR_WAVEFORM_QUANTUM       /* ViInt32,  read-only             */
#define ES1653_ATTR_MIN_WAVEFORM_SIZE         IVIFGEN_ATTR_MIN_WAVEFORM_SIZE      /* ViInt32,  read-only             */
#define ES1653_ATTR_MAX_WAVEFORM_SIZE         IVIFGEN_ATTR_MAX_WAVEFORM_SIZE      /* ViInt32,  read-only             */
#define ES1653_ATTR_MAX_NUM_SEQUENCES		   IVIFGEN_ATTR_MAX_NUM_SEQUENCES	   /* ViInt32,  read-only			  */
#define ES1653_ATTR_MAX_NUM_WAVEFORMS 		   IVIFGEN_ATTR_MAX_NUM_WAVEFORMS 	   /* ViInt32,  read-only			  */
#define ES1653_ATTR_MAX_NUM_SUB_SEQUENCES     (IVI_CLASS_PUBLIC_ATTR_BASE + 216L) /* ViInt32,  read-only			  */
#define ES1653_ATTR_MAX_NUM_SUB_IN_SEQ        (IVI_CLASS_PUBLIC_ATTR_BASE + 217L) /* ViInt32,  read-only			  */
#define ES1653_ATTR_ARB_SEQUENCE_HANDLE       IVIFGEN_ATTR_ARB_SEQUENCE_HANDLE    /* ViInt32,  read-only			  */
#define ES1653_ATTR_MAX_LOOP_COUNT 	       IVIFGEN_ATTR_MAX_LOOP_COUNT	       /* ViInt32,  read-only             */
#define ES1653_ATTR_MAX_SEQUENCE_LENGTH       IVIFGEN_ATTR_MAX_SEQUENCE_LENGTH    /* ViInt32,  read-only             */
#define ES1653_ATTR_MIN_SEQUENCE_LENGTH       IVIFGEN_ATTR_MIN_SEQUENCE_LENGTH    /* ViInt32,  read-only             */

    /*- Arbitrary Waveform FREQUENCY --------------------------------------*/
#define ES1653_ATTR_ARB_FREQUENCY             IVIFGEN_ATTR_ARB_FREQUENCY          /* ViReal64, multi-channel         */
    /*- Sample Clock -------------------------------------------------------*/
#define ES1653_ATTR_SAMPLE_CLOCK_SOURC        IVIFGEN_ATTR_SAMPLE_CLOCK_SOURCE
#define ES1653_ATTR_SAMPLE_CLOCK_OUTPUT_ENABLED IVIFGEN_ATTR_SAMPLE_CLOCK_OUTPUT_ENABLED
    /*- Ampitude Modulation Generation -------------------------------------*/

#define ES1653_ATTR_AM_ENABLED                IVIFGEN_ATTR_AM_ENABLED             /* ViBoolean, multi-channel */
#define ES1653_ATTR_AM_SOURCE                 IVIFGEN_ATTR_AM_SOURCE              /* ViInt32,   multi-channel */
#define ES1653_ATTR_AM_INTERNAL_DEPTH         IVIFGEN_ATTR_AM_INTERNAL_DEPTH      /* ViReal64,  percent       */
#define ES1653_ATTR_AM_INTERNAL_WAVEFORM      IVIFGEN_ATTR_AM_INTERNAL_WAVEFORM   /* ViInt32                  */
#define ES1653_ATTR_AM_INTERNAL_FREQUENCY     IVIFGEN_ATTR_AM_INTERNAL_FREQUENCY  /* ViReal64,  hertz         */

    /*- Frequency Modulation Generation ------------------------------------*/

#define ES1653_ATTR_FM_ENABLED                IVIFGEN_ATTR_FM_ENABLED             /* ViBoolean, multi-channel */
#define ES1653_ATTR_FM_SOURCE                 IVIFGEN_ATTR_FM_SOURCE              /* ViInt32,   multi-channel */
#define ES1653_ATTR_FM_INTERNAL_DEVIATION     IVIFGEN_ATTR_FM_INTERNAL_DEVIATION  /* ViReal64,  hertz         */
#define ES1653_ATTR_FM_INTERNAL_WAVEFORM      IVIFGEN_ATTR_FM_INTERNAL_WAVEFORM   /* ViInt32                  */
#define ES1653_ATTR_FM_INTERNAL_FREQUENCY     IVIFGEN_ATTR_FM_INTERNAL_FREQUENCY  /* ViReal64,  hertz         */

    /*- Phase Modulation Generation ----------------------------------------*/

#define ES1653_ATTR_PM_ENABLED                (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 501L) /* ViBoolean, multi-channel */
#define ES1653_ATTR_PM_SOURCE                 (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 502L) /* ViInt32,   multi-channel */
#define ES1653_ATTR_PM_INTERNAL_DEVIATION     (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 503L) /* ViReal64,  degrees       */
#define ES1653_ATTR_PM_INTERNAL_WAVEFORM      (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 504L) /* ViInt32                  */
#define ES1653_ATTR_PM_INTERNAL_FREQUENCY     (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 505L) /* ViReal64,  hertz         */

    /*- Pulse Width Modulation Generation ----------------------------------*/

#define ES1653_ATTR_PWM_ENABLED               (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 601L) /* ViBoolean, multi-channel */
#define ES1653_ATTR_PWM_SOURCE                (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 602L) /* ViInt32,   multi-channel */
#define ES1653_ATTR_PWM_INTERNAL_DEVIATION    (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 603L) /* ViReal64,  seconds       */
#define ES1653_ATTR_PWM_INTERNAL_WAVEFORM     (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 604L) /* ViInt32                  */
#define ES1653_ATTR_PWM_INTERNAL_FREQUENCY    (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 605L) /* ViReal64,  hertz         */
#define ES1653_ATTR_PWM_DUTY_CYCLE_DEVIATION  (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 606L) /* ViReal64,  percentages   */

    /*- Frequency Shift Key Modulation Generation --------------------------*/

#define ES1653_ATTR_FSK_ENABLED              (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 101L) /* ViBoolean, multi-channel */
#define ES1653_ATTR_FSK_HOP_FREQUENCY        (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 102L) /* ViReal64,  multi-channel */
#define ES1653_ATTR_FSK_SOURCE               (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 103L) /* ViInt32,   multi-channel */
#define ES1653_ATTR_FSK_INTERNAL_RATE        (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 104L) /* ViReal64,  multi-channel */
#define ES1653_ATTR_FSK_MODE                 (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 105L)
    /*- Frequency Shift Key Modulation Generation --------------------------*/

#define ES1653_ATTR_PSK_ENABLED              (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 701L) /* ViBoolean, multi-channel */
#define ES1653_ATTR_PSK_HOP_PHASE            (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 702L) /* ViReal64,  multi-channel */
#define ES1653_ATTR_PSK_SOURCE               (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 703L) /* ViInt32,   multi-channel */
#define ES1653_ATTR_PSK_INTERNAL_RATE        (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 704L) /* ViReal64,  multi-channel */
#define ES1653_ATTR_PSK_MODE                 (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 705L)
    /*- Frequency Sweep Generation -----------------------------------------*/
#define ES1653_ATTR_SWEEP_SOURCE             (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 201L)
#define ES1653_ATTR_SWEEP_START_FREQ         (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 202L) /* ViReal64,  multi-channel */
#define ES1653_ATTR_SWEEP_STOP_FREQ          (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 203L) /* ViReal64,  multi-channel */
#define ES1653_ATTR_SWEEP_SPACING            (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 204L) /* ViInt32,   multi-channel */
#define ES1653_ATTR_SWEEP_TIME               (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 205L) /* ViReal64,  multi-channel */
#define ES1653_ATTR_SWEEP_ENABLED            (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 207L)
    /*- Burst Modulation Generation ----------------------------------------*/
#define ES1653_ATTR_BURST_COUNT              IVIFGEN_ATTR_BURST_COUNT               /* ViInt32,   multi-channel */
#define ES1653_ATTR_BURST_GATE_POLARITY      (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 411L) /* ViInt32,   multi-channel */
#define ES1653_ATTR_BURST_PHASE              (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 305L) /* ViReal64,  multi-channel */
#define ES1653_ATTR_BURST_ENABLED            (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 306L)

    /*- TTL lines available on VXIbus backplane of HPE1441A ----------------*/
#define ES1653_ATTR_TTL1_ENABLED  (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 306L)   /* ViBoolean */
#define ES1653_ATTR_TTL2_ENABLED  (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 307L)   /* ViBoolean */
#define ES1653_ATTR_TTL3_ENABLED  (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 308L)   /* ViBoolean */
#define ES1653_ATTR_TTL4_ENABLED  (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 309L)   /* ViBoolean */
#define ES1653_ATTR_TTL5_ENABLED  (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 310L)   /* ViBoolean */
#define ES1653_ATTR_TTL6_ENABLED  (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 311L)   /* ViBoolean */
#define ES1653_ATTR_TTL7_ENABLED  (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 312L)   /* ViBoolean */
#define ES1653_ATTR_TTL0_ENABLED  (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 313L)   /* ViBoolean */

    /*- VXI Phase synchronization ------------------------------------------*/
#define ES1653_ATTR_PHASE_REF     (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 314L)   /* ViReal64 */
#define ES1653_ATTR_PHASE_ADJUST  (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 315L)   /* ViReal64 */

    /*- Polarity -----------------------------------------------------------*/
#define ES1653_ATTR_OUTPUT_POLARITY (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 401L) /* ViInt32,   multi-channel */

    /*- Pulse --------------------------------------------------------------*/
#define ES1653_ATTR_PULSE_PERIOD                     (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 402L)  /* ViReal64,   multi-channel */
#define ES1653_ATTR_PULSE_WIDTH                      (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 403L)  /* ViReal64,   multi-channel */
#define ES1653_ATTR_PULSE_TRANSITION                 (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 404L)  /* ViReal64,   multi-channel */
#define ES1653_ATTR_PULSE_DUTY_CYCLE				   (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 415L)  /* ViReal64 */
#define ES1653_ATTR_PULSE_HOLD					   (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 416L)  /* ViInt32  */

    /*- Ramp Symmetry ------------------------------------------------------*/
#define ES1653_ATTR_RAMP_SYMMETRY                    (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 406L)  /* ViReal64 */

    /*- Trigger ------------------------------------------------------------*/
#define ES1653_ATTR_TRIGGER_SLOPE                    (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 408L)  /* ViInt32  */
#define ES1653_ATTR_TRIGGER_THRESHOLD                    (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 409L)  /* ViReal64 */
#define ES1653_ATTR_TRIGGER_SOURCE                   IVIFGEN_ATTR_TRIGGER_SOURCE
#define ES1653_ATTR_INTERNAL_TRIGGER_RATE            IVIFGEN_ATTR_INTERNAL_TRIGGER_RATE     /* ViReal64                 */
#define ES1653_ATTR_TRIGGER_MODE                     (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 410L)
#define ES1653_ATTR_SOFTWARE_TRIGGER                     (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 332L)
    /*- Phase unlock error state -------------------------------------------*/
#define ES1653_ATTR_PHASE_UNLOCK_ERROR_STATE_ENABLED (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 412L)  /* ViBoolean */

    /*- Voltage autoranging ------------------------------------------------*/
#define ES1653_ATTR_VOLT_RANGE_AUTO                  (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 413L)  /* ViBoolean */

    /*- Sync Signal Enabled ------------------------------------------------*/
#define ES1653_ATTR_SYNC_SIGNAL_ENABLED              (IVI_SPECIFIC_PUBLIC_ATTR_BASE + 414L)  /* ViBoolean */
    /*- Seq Arb -*/
#define ES1653_ATTR_SEQ_LOOP_COUNT                   (IVI_CLASS_PUBLIC_ATTR_BASE + 216L)
#define ES1653_ATTR_SEQ_LENGTH                       (IVI_CLASS_PUBLIC_ATTR_BASE + 217L)
#define ES1653_ATTR_SEQ_SIZE                         (IVI_CLASS_PUBLIC_ATTR_BASE + 218L)
#define ES1653_ATTR_SEQ_HANDLE                       (IVI_CLASS_PUBLIC_ATTR_BASE + 219L)
#define ES1653_ATTR_SEQ_ENABLED                      (IVI_CLASS_PUBLIC_ATTR_BASE + 220L)

/*- channel information ------------------------------------------------*/
#define ES1653_ATTR_CHANNEL_1_SESSION                  (IVI_SPECIFIC_PRIVATE_ATTR_BASE + 1L)
#define ES1653_ATTR_CHANNEL_2_SESSION                  (IVI_SPECIFIC_PRIVATE_ATTR_BASE + 2L)
#define ES1653_ATTR_CHANNEL_3_SESSION                  (IVI_SPECIFIC_PRIVATE_ATTR_BASE + 3L)
#define ES1653_ATTR_CHANNEL_4_SESSION                  (IVI_SPECIFIC_PRIVATE_ATTR_BASE + 4L)
/****************************************************************************
 *------------------------ Attribute Value Defines -------------------------*
 ****************************************************************************/
    /*- Defined values for attribute ES1653_VAL_SEGMENT_NUMBER_MAX---------*/

//#define ES1653_VAL_SEGMENT_NUMBER_MAX       (6L)


    /*- Defined values for attribute ES1653_VAL_FILTER_FREQ---------*/
/** \name 频率档位
 * @{
 */
#define ES1653_VAL_FILTER_FREQ_2K             (2e3L)
#define ES1653_VAL_FILTER_FREQ_20K            (20e3L)
#define ES1653_VAL_FILTER_FREQ_200K           (200e3L)
#define ES1653_VAL_FILTER_FREQ_2M             (2e6L)
/**@}*/


    /*- Defined values for attribute ES1653_ATTR_OUTPUT_MODE --------------*/

#define ES1653_VAL_OUTPUT_FUNC           1//IVIFGEN_VAL_OUTPUT_FUNC
#define ES1653_VAL_OUTPUT_ARB            2//IVIFGEN_VAL_OUTPUT_ARB
#define ES1653_VAL_OUTPUT_SEQ            0//IVIFGEN_VAL_OUTPUT_SEQ
    /*- Defined values for attribute ES1653_ATTR_REF_CLOCK_SOURCE ------*/

#define ES1653_VAL_REF_CLOCK_INTERNAL    IVIFGEN_VAL_REF_CLOCK_INTERNAL
#define ES1653_VAL_REF_CLOCK_EXTERNAL    IVIFGEN_VAL_REF_CLOCK_EXTERNAL

    /*- Defined values for attribute ES1653_ATTR_PULSE ------*/

#define ES1653_VAL_PULSE_HOLD_WIDTH     (0L)
#define ES1653_VAL_PULSE_HOLD_DCYCLE    (1L)

    /*- Defined values for attribute ES1653_ATTR_FUNC_WAVEFORM ---------*/
#define ES1653_VAL_WFM_NO_WAVE           0
#define ES1653_VAL_WFM_SINE              IVIFGEN_VAL_WFM_SINE
#define ES1653_VAL_WFM_SQUARE            IVIFGEN_VAL_WFM_SQUARE
#define ES1653_VAL_WFM_TRIANGLE          IVIFGEN_VAL_WFM_TRIANGLE
#define ES1653_VAL_WFM_RAMP_UP           IVIFGEN_VAL_WFM_RAMP_UP
#define ES1653_VAL_WFM_DC                IVIFGEN_VAL_WFM_DC
#define ES1653_VAL_WFM_RAMP_DOWN         IVIFGEN_VAL_WFM_RAMP_DOWN
#define ES1653_VAL_WFM_PULSE             (IVIFGEN_VAL_WFM_SPECIFIC_EXT_BASE + 3)
#define ES1653_VAL_WFM_USER              (IVIFGEN_VAL_WFM_SPECIFIC_EXT_BASE + 2)
#define ES1653_VAL_WFM_NOISE             (IVIFGEN_VAL_WFM_SPECIFIC_EXT_BASE + 1)
#define ES1653_VAL_WFM_EXP_UP            (IVIFGEN_VAL_WFM_SPECIFIC_EXT_BASE + 5)
#define ES1653_VAL_WFM_EXP_DOWN          (IVIFGEN_VAL_WFM_SPECIFIC_EXT_BASE + 6)

    /*- Defined values for Arbitrary Waveform Handles ---------------------------------*/
#define ES1653_VAL_ALL_WAVEFORMS         IVIFGEN_VAL_ALL_WAVEFORMS
#define ES1653_VAL_ALL_SEQUENCES 	      IVIFGEN_VAL_ALL_SEQUENCES

    /*- Defined values for attribute ES1653_ATTR_AM_SOURCE -*/
#define ES1653_VAL_AM_EXTERNAL           IVIFGEN_VAL_AM_EXTERNAL
#define ES1653_VAL_AM_INTERNAL           IVIFGEN_VAL_AM_INTERNAL

   /*- Defined values for attribute ES1653_ATTR_AM_INTERNAL_WAVEFORM -*/
#define ES1653_VAL_AM_INTERNAL_SINE      IVIFGEN_VAL_AM_INTERNAL_SINE
#define ES1653_VAL_AM_INTERNAL_SQUARE    IVIFGEN_VAL_AM_INTERNAL_SQUARE
#define ES1653_VAL_AM_INTERNAL_TRIANGLE  IVIFGEN_VAL_AM_INTERNAL_TRIANGLE
#define ES1653_VAL_AM_INTERNAL_RAMP_UP   IVIFGEN_VAL_AM_INTERNAL_RAMP_UP
#define ES1653_VAL_AM_INTERNAL_RAMP_DOWN IVIFGEN_VAL_AM_INTERNAL_RAMP_DOWN
#define ES1653_VAL_AM_INTERNAL_NOISE     (IVIFGEN_VAL_AM_SOURCE_SPECIFIC_EXT_BASE + 1L)
#define ES1653_VAL_AM_INTERNAL_ARBITRARY (IVIFGEN_VAL_AM_SOURCE_SPECIFIC_EXT_BASE + 2L)
#define ES1653_VAL_AM_INTERNAL_EXP_UP	 (IVIFGEN_VAL_AM_SOURCE_SPECIFIC_EXT_BASE + 3L)
#define ES1653_VAL_AM_INTERNAL_EXP_DOWN  (IVIFGEN_VAL_AM_SOURCE_SPECIFIC_EXT_BASE + 4L)
#define ES1653_VAL_AM_INTERNAL_DC        (IVIFGEN_VAL_AM_SOURCE_SPECIFIC_EXT_BASE + 5L)


/*- Defined values for attribute ES1653_ATTR_FM_SOURCE -*/
#define ES1653_VAL_FM_INTERNAL           IVIFGEN_VAL_FM_INTERNAL
#define ES1653_VAL_FM_EXTERNAL           IVIFGEN_VAL_FM_EXTERNAL

   /*- Defined values for attribute ES1653_ATTR_FM_INTERNAL_WAVEFORM -*/
#define ES1653_VAL_FM_INTERNAL_SINE      IVIFGEN_VAL_FM_INTERNAL_SINE
#define ES1653_VAL_FM_INTERNAL_SQUARE    IVIFGEN_VAL_FM_INTERNAL_SQUARE
#define ES1653_VAL_FM_INTERNAL_TRIANGLE  IVIFGEN_VAL_FM_INTERNAL_TRIANGLE
#define ES1653_VAL_FM_INTERNAL_RAMP_UP   IVIFGEN_VAL_FM_INTERNAL_RAMP_UP
#define ES1653_VAL_FM_INTERNAL_RAMP_DOWN IVIFGEN_VAL_FM_INTERNAL_RAMP_DOWN
#define ES1653_VAL_FM_INTERNAL_NOISE     (IVIFGEN_VAL_FM_SOURCE_SPECIFIC_EXT_BASE + 1L)
#define ES1653_VAL_FM_INTERNAL_ARBITRARY (IVIFGEN_VAL_FM_SOURCE_SPECIFIC_EXT_BASE + 2L)
#define ES1653_VAL_FM_INTERNAL_EXP_UP	 (IVIFGEN_VAL_FM_SOURCE_SPECIFIC_EXT_BASE + 3L)
#define ES1653_VAL_FM_INTERNAL_EXP_DOWN  (IVIFGEN_VAL_FM_SOURCE_SPECIFIC_EXT_BASE + 4L)
#define ES1653_VAL_FM_INTERNAL_DC        (IVIFGEN_VAL_FM_SOURCE_SPECIFIC_EXT_BASE + 5L)

    /*- Defined values for attribute ES1653_ATTR_FM_SOURCE -*/
#define ES1653_VAL_PM_INTERNAL           IVIFGEN_VAL_FM_INTERNAL
#define ES1653_VAL_PM_EXTERNAL           IVIFGEN_VAL_FM_EXTERNAL

   /*- Defined values for attribute ES1653_ATTR_PM_INTERNAL_WAVEFORM -*/
#define ES1653_VAL_PM_INTERNAL_SINE      IVIFGEN_VAL_FM_INTERNAL_SINE
#define ES1653_VAL_PM_INTERNAL_SQUARE    IVIFGEN_VAL_FM_INTERNAL_SQUARE
#define ES1653_VAL_PM_INTERNAL_TRIANGLE  IVIFGEN_VAL_FM_INTERNAL_TRIANGLE
#define ES1653_VAL_PM_INTERNAL_RAMP_UP   IVIFGEN_VAL_FM_INTERNAL_RAMP_UP
#define ES1653_VAL_PM_INTERNAL_RAMP_DOWN IVIFGEN_VAL_FM_INTERNAL_RAMP_DOWN
#define ES1653_VAL_PM_INTERNAL_NOISE     (IVIFGEN_VAL_FM_SOURCE_SPECIFIC_EXT_BASE + 1L)
#define ES1653_VAL_PM_INTERNAL_ARBITRARY (IVIFGEN_VAL_FM_SOURCE_SPECIFIC_EXT_BASE + 2L)
#define ES1653_VAL_PM_INTERNAL_EXP_UP	 (IVIFGEN_VAL_FM_SOURCE_SPECIFIC_EXT_BASE + 3L)
#define ES1653_VAL_PM_INTERNAL_EXP_DOWN  (IVIFGEN_VAL_FM_SOURCE_SPECIFIC_EXT_BASE + 4L)
#define ES1653_VAL_PM_INTERNAL_DC        (IVIFGEN_VAL_FM_SOURCE_SPECIFIC_EXT_BASE + 5L)

    /*- Defined values for attribute ES1653_ATTR_FM_SOURCE -*/
#define ES1653_VAL_PWM_INTERNAL           IVIFGEN_VAL_FM_INTERNAL
#define ES1653_VAL_PWM_EXTERNAL           IVIFGEN_VAL_FM_EXTERNAL

   /*- Defined values for attribute ES1653_ATTR_PM_INTERNAL_WAVEFORM -*/
#define ES1653_VAL_PWM_INTERNAL_SINE      IVIFGEN_VAL_FM_INTERNAL_SINE
#define ES1653_VAL_PWM_INTERNAL_SQUARE    IVIFGEN_VAL_FM_INTERNAL_SQUARE
#define ES1653_VAL_PWM_INTERNAL_TRIANGLE  IVIFGEN_VAL_FM_INTERNAL_TRIANGLE
#define ES1653_VAL_PWM_INTERNAL_RAMP_UP   IVIFGEN_VAL_FM_INTERNAL_RAMP_UP
#define ES1653_VAL_PWM_INTERNAL_RAMP_DOWN IVIFGEN_VAL_FM_INTERNAL_RAMP_DOWN
#define ES1653_VAL_PWM_INTERNAL_NOISE     (IVIFGEN_VAL_FM_SOURCE_SPECIFIC_EXT_BASE + 1L)
#define ES1653_VAL_PWM_INTERNAL_ARBITRARY (IVIFGEN_VAL_FM_SOURCE_SPECIFIC_EXT_BASE + 2L)
#define ES1653_VAL_PWM_INTERNAL_EXP_UP	  (IVIFGEN_VAL_FM_SOURCE_SPECIFIC_EXT_BASE + 3L)
#define ES1653_VAL_PWM_INTERNAL_EXP_DOWN  (IVIFGEN_VAL_FM_SOURCE_SPECIFIC_EXT_BASE + 4L)
#define ES1653_VAL_PWM_INTERNAL_DC        (IVIFGEN_VAL_FM_SOURCE_SPECIFIC_EXT_BASE + 5L)

#define ES1653_VAL_EXTERNAL                IVIFGEN_VAL_EXTERNAL
#define ES1653_VAL_SOFTWARE_TRIG           IVIFGEN_VAL_SOFTWARE_TRIG
#define ES1653_VAL_INTERNAL_TRIGGER        IVIFGEN_VAL_INTERNAL_TRIGGER
#define ES1653_VAL_TTL0                    IVIFGEN_VAL_TTL0
#define ES1653_VAL_TTL1                    IVIFGEN_VAL_TTL1
#define ES1653_VAL_TTL2                    IVIFGEN_VAL_TTL2
#define ES1653_VAL_TTL3                    IVIFGEN_VAL_TTL3
#define ES1653_VAL_TTL4                    IVIFGEN_VAL_TTL4
#define ES1653_VAL_TTL5                    IVIFGEN_VAL_TTL5
#define ES1653_VAL_TTL6                    IVIFGEN_VAL_TTL6
#define ES1653_VAL_TTL7                    IVIFGEN_VAL_TTL7
#define ES1653_VAL_ECL0                    IVIFGEN_VAL_ECL0
#define ES1653_VAL_ECL1                    IVIFGEN_VAL_ECL1
#define ES1653_VAL_RTSI_0                  IVIFGEN_VAL_RTSI_0
#define ES1653_VAL_RTSI_1                  IVIFGEN_VAL_RTSI_1
#define ES1653_VAL_RTSI_2                  IVIFGEN_VAL_RTSI_2
#define ES1653_VAL_RTSI_3                  IVIFGEN_VAL_RTSI_3
#define ES1653_VAL_RTSI_4                  IVIFGEN_VAL_RTSI_4
#define ES1653_VAL_RTSI_5                  IVIFGEN_VAL_RTSI_5
#define ES1653_VAL_RTSI_6                  IVIFGEN_VAL_RTSI_6
#define ES1653_VAL_PXI_STAR                IVIFGEN_VAL_PXI_STAR

#define ES1653_VAL_TRIGGER_SOURCE_NONE             IVIFGEN_VAL_TRIGGER_SOURCE_NONE
#define ES1653_VAL_TRIGGER_SOURCE_IMMEDIATE        IVIFGEN_VAL_TRIGGER_SOURCE_IMMEDIATE
#define ES1653_VAL_TRIGGER_SOURCE_EXTERNAL         IVIFGEN_VAL_TRIGGER_SOURCE_EXTERNAL
#define ES1653_VAL_TRIGGER_SOURCE_INTERNAL         IVIFGEN_VAL_TRIGGER_SOURCE_INTERNAL
#define ES1653_VAL_TRIGGER_SOURCE_SOFTWARE         IVIFGEN_VAL_TRIGGER_SOURCE_SOFTWARE
#define ES1653_VAL_TRIGGER_SOURCE_PXI_STAR         IVIFGEN_VAL_TRIGGER_SOURCE_PXI_STAR
#define ES1653_VAL_TRIGGER_SOURCE_PXI_TRIG0        IVIFGEN_VAL_TRIGGER_SOURCE_PXI_TRIG0
#define ES1653_VAL_TRIGGER_SOURCE_PXI_TRIG1        IVIFGEN_VAL_TRIGGER_SOURCE_PXI_TRIG1
#define ES1653_VAL_TRIGGER_SOURCE_PXI_TRIG2        IVIFGEN_VAL_TRIGGER_SOURCE_PXI_TRIG2
#define ES1653_VAL_TRIGGER_SOURCE_PXI_TRIG3        IVIFGEN_VAL_TRIGGER_SOURCE_PXI_TRIG3
#define ES1653_VAL_TRIGGER_SOURCE_PXI_TRIG4        IVIFGEN_VAL_TRIGGER_SOURCE_PXI_TRIG4
#define ES1653_VAL_TRIGGER_SOURCE_PXI_TRIG5        IVIFGEN_VAL_TRIGGER_SOURCE_PXI_TRIG5
#define ES1653_VAL_TRIGGER_SOURCE_PXI_TRIG6        IVIFGEN_VAL_TRIGGER_SOURCE_PXI_TRIG6
#define ES1653_VAL_TRIGGER_SOURCE_PXI_TRIG7        IVIFGEN_VAL_TRIGGER_SOURCE_PXI_TRIG7
#define ES1653_VAL_TRIGGER_SOURCE_LAN0             IVIFGEN_VAL_TRIGGER_SOURCE_LAN0
#define ES1653_VAL_TRIGGER_SOURCE_LAN1             IVIFGEN_VAL_TRIGGER_SOURCE_LAN1
#define ES1653_VAL_TRIGGER_SOURCE_LAN2             IVIFGEN_VAL_TRIGGER_SOURCE_LAN2
#define ES1653_VAL_TRIGGER_SOURCE_LAN3             IVIFGEN_VAL_TRIGGER_SOURCE_LAN3
#define ES1653_VAL_TRIGGER_SOURCE_LAN4             IVIFGEN_VAL_TRIGGER_SOURCE_LAN4
#define ES1653_VAL_TRIGGER_SOURCE_LAN5             IVIFGEN_VAL_TRIGGER_SOURCE_LAN5
#define ES1653_VAL_TRIGGER_SOURCE_LAN6             IVIFGEN_VAL_TRIGGER_SOURCE_LAN6
#define ES1653_VAL_TRIGGER_SOURCE_LAN7             IVIFGEN_VAL_TRIGGER_SOURCE_LAN7
#define ES1653_VAL_TRIGGER_SOURCE_LXI0             IVIFGEN_VAL_TRIGGER_SOURCE_LXI0
#define ES1653_VAL_TRIGGER_SOURCE_LXI1              IVIFGEN_VAL_TRIGGER_SOURCE_LXI1
#define ES1653_VAL_TRIGGER_SOURCE_LXI2              IVIFGEN_VAL_TRIGGER_SOURCE_LXI2
#define ES1653_VAL_TRIGGER_SOURCE_LXI3              IVIFGEN_VAL_TRIGGER_SOURCE_LXI3
#define ES1653_VAL_TRIGGER_SOURCE_LXI4              IVIFGEN_VAL_TRIGGER_SOURCE_LXI4
#define ES1653_VAL_TRIGGER_SOURCE_LXI5              IVIFGEN_VAL_TRIGGER_SOURCE_LXI5
#define ES1653_VAL_TRIGGER_SOURCE_LXI6              IVIFGEN_VAL_TRIGGER_SOURCE_LXI6
#define ES1653_VAL_TRIGGER_SOURCE_LXI7              IVIFGEN_VAL_TRIGGER_SOURCE_LXI7
#define ES1653_VAL_TRIGGER_SOURCE_TTL0             IVIFGEN_VAL_TRIGGER_SOURCE_TTL0
#define ES1653_VAL_TRIGGER_SOURCE_TTL1             IVIFGEN_VAL_TRIGGER_SOURCE_TTL1
#define ES1653_VAL_TRIGGER_SOURCE_TTL2             IVIFGEN_VAL_TRIGGER_SOURCE_TTL2
#define ES1653_VAL_TRIGGER_SOURCE_TTL3             IVIFGEN_VAL_TRIGGER_SOURCE_TTL3
#define ES1653_VAL_TRIGGER_SOURCE_TTL4             IVIFGEN_VAL_TRIGGER_SOURCE_TTL4
#define ES1653_VAL_TRIGGER_SOURCE_TTL5             IVIFGEN_VAL_TRIGGER_SOURCE_TTL5
#define ES1653_VAL_TRIGGER_SOURCE_TTL6             IVIFGEN_VAL_TRIGGER_SOURCE_TTL6
#define ES1653_VAL_TRIGGER_SOURCE_TTL7             IVIFGEN_VAL_TRIGGER_SOURCE_TTL7
#define ES1653_VAL_TRIGGER_SOURCE_PXIE_DSTARA      IVIFGEN_VAL_TRIGGER_SOURCE_PXIE_DSTARA
#define ES1653_VAL_TRIGGER_SOURCE_PXIE_DSTARB      IVIFGEN_VAL_TRIGGER_SOURCE_PXIE_DSTARB
#define ES1653_VAL_TRIGGER_SOURCE_PXIE_DSTARC      IVIFGEN_VAL_TRIGGER_SOURCE_PXIE_DSTARC
#define ES1653_VAL_TRIGGER_SOURCE_RTSI0            IVIFGEN_VAL_TRIGGER_SOURCE_RTSI0
#define ES1653_VAL_TRIGGER_SOURCE_RTSI1            IVIFGEN_VAL_TRIGGER_SOURCE_RTSI1
#define ES1653_VAL_TRIGGER_SOURCE_RTSI2            IVIFGEN_VAL_TRIGGER_SOURCE_RTSI2
#define ES1653_VAL_TRIGGER_SOURCE_RTSI3            IVIFGEN_VAL_TRIGGER_SOURCE_RTSI3
#define ES1653_VAL_TRIGGER_SOURCE_RTSI4            IVIFGEN_VAL_TRIGGER_SOURCE_RTSI4
#define ES1653_VAL_TRIGGER_SOURCE_RTSI5            IVIFGEN_VAL_TRIGGER_SOURCE_RTSI5
#define ES1653_VAL_TRIGGER_SOURCE_RTSI6            IVIFGEN_VAL_TRIGGER_SOURCE_RTSI6

#define ES1653_VAL_SWEEP_LINEAR                    (1L)
#define ES1653_VAL_SWEEP_LOGARITHMIC               (2L)

#define ES1653_VAL_TRIGGER_POSITIVE                IVIFGEN_VAL_TRIGGER_POSITIVE
#define ES1653_VAL_TRIGGER_NEGATIVE                IVIFGEN_VAL_TRIGGER_NEGATIVE

#define ES1653_VAL_SAMPLE_CLOCK_SOURCE_INTERNAL    IVIFGEN_VAL_SAMPLE_CLOCK_SOURCE_INTERNAL
#define ES1653_VAL_SAMPLE_CLOCK_SOURCE_EXTERNAL    IVIFGEN_VAL_SAMPLE_CLOCK_SOURCE_EXTERNAL
    /*- Define values for atttribute ES1653_ATTR_BURST_COUNT -----------*/
#define ES1653_VAL_GENERATE_CONTINUOUS             (-1L)

    /*-  values for atttribute ES1653_ATTR_OPERATION_MODE-----------*/
#define ES1653_VAL_OPERATE_CONTINUOUS              IVIFGEN_VAL_OPERATE_CONTINUOUS
#define ES1653_VAL_OPERATE_BURST                   IVIFGEN_VAL_OPERATE_BURST
#define ES1653_VAL_OP_MODE_CLASS_EXT_BASE          IVIFGEN_VAL_OP_MODE_CLASS_EXT_BASE
#define ES1653_VAL_OP_MODE_SPECIFIC_EXT_BASE       IVIFGEN_VAL_OP_MODE_SPECIFIC_EXT_BASE

    /*-  values for arb attributes --------------------*/
#define ES1653_VAL_MAX_WAVEFORM_SIZE               (1000L)
#define ES1653_VAL_MIN_WAVEFORM_SIZE               (100L)
#define ES1653_VAL_WAVEFORM_QUANTUM                (4L)
#define ES1653_VAL_FIRST_WAVEFORM_HANDLE             (10000L)
#define ES1653_VAL_FIRST_SEQ_HANDLE                  (20000L)
#define ES1653_VAL_MAX_WAVEFORMS                     (16000L)
#define ES1653_VAL_MIN_SEQUENCE_LENGTH				(1L)
#define ES1653_VAL_MAX_SEQUENCE_LENGTH				(65535L)
#define ES1653_VAL_MAX_NUM_SEQUENCES          		(10L)
#define ES1653_VAL_MAX_SEQ_POINT_NUM          		(10L)
#define ES1653_VAL_MAX_SEG_NUM                      (16000L)
#define ES1653_VAL_MAX_LOOP_COUNT 					(100L)
#define ES1653_VAL_MAX_NUM_SUB_IN_SEQ          	(5L)
#define ES1653_VAL_MAX_NUM_SUB_SEQUENCES       	(100L)
	/*- Define values for attribute ES1653_ATTR_TRIG_MODE-------*/
#define ES1653_VAL_MODU_MODE_TRIG                                 (0)
#define ES1653_VAL_MODU_MODE_GATE                                 (1)
#define ES1653_VAL_MODU_MODE_CONTINOUS                            (2)

#define ES1653_VAL_SWEEP_SOURCE_INTERNAL                        (0)
#define ES1653_VAL_SWEEP_SOURCE_EXTERNAL                        (1)
#define ES1653_VAL_SWEEP_SOURCE_MANUAL                          (2)

    /*- Define values for attribute ES1653_ATTR_VOLT_RANGE_AUTO-----------*/
#define ES1653_VAL_RANGE_AUTO_ON                                  (0)
#define ES1653_VAL_RANGE_AUTO_OFF                                 (1)

    /*- Define values for atttribute ES1653_ATTR_FSK_SOURCE-----------*/
#define ES1653_VAL_FSK_INTERNAL                                   0 //ES1653_VAL_INTERNAL_TRIGGER
#define ES1653_VAL_FSK_EXTERNAL                                   1 //ES1653_VAL_EXTERNAL
    /*- Define values for atttribute ES1653_ATTR_SWEEP_SOURCE-----------*/
#define ES1653_VAL_SWEEP_INTERNAL                                   (0)
#define ES1653_VAL_SWEEP_EXTERNAL                                   (1)
    /*- Define values for atttribute ES1653_ATTR_PSK_SOURCE-----------*/
#define ES1653_VAL_PSK_INTERNAL                                   0 //ES1653_VAL_INTERNAL_TRIGGER
#define ES1653_VAL_PSK_EXTERNAL                                   1 //ES1653_VAL_EXTERNAL

    /*- Define values for atttribute ES1653_ATTR_BURST_SOURCE-----------*/
#define ES1653_VAL_BURST_INTERNAL                                 0 //ES1653_VAL_INTERNAL_TRIGGER
#define ES1653_VAL_BURST_EXTERNAL                                 1 //ES1653_VAL_EXTERNAL

    /*- Define values for attribute ES1653_VAL_ERROR_MESSAGE_LENGTH-------*/
#define ES1653_VAL_ERROR_MESSAGE_LENGTH                          IVI_VAL_ERROR_MESSAGE_LENGTH

/****************************************************************************
 *---------------- Channel Object Declarations -----------------------------*
 ***************************************************************************/
typedef struct __AM_Parameter AM_Parameter;
struct __AM_Parameter
{
	ViInt32 am_waveform;
	ViInt32 am_src;
	ViReal64 am_frequency;
	ViReal64 am_depth;
	ViBoolean am_status;
};

typedef struct __FM_Parameter FM_Parameter;
struct __FM_Parameter
{
	ViInt32 fm_waveform;
	ViInt32 fm_src;
	ViReal64 fm_frequency;
	ViReal64 fm_devia;
	ViBoolean fm_status;
};

typedef struct __PM_Parameter PM_Parameter;
struct __PM_Parameter
{
	ViInt32 pm_waveform;
	ViInt32 pm_src;
	ViReal64 pm_frequency;
	ViReal64 pm_devia;
	ViBoolean pm_status;
};

typedef struct __FSK_Parameter FSK_Parameter;
struct __FSK_Parameter
{
	ViInt32 fsk_src;
	ViReal64 fsk_rate;
	ViBoolean fsk_status;
	ViReal64 fsk_hop_frequency;
	ViInt32 fsk_mode;
};

typedef struct __PSK_Parameter PSK_Parameter;
struct __PSK_Parameter
{
	ViInt32 psk_src;
	ViReal64 psk_rate;
	ViReal64 psk_phase;
	ViBoolean psk_status;
	ViInt32 psk_mode;
};

typedef struct __Burst_Parameter Burst_Parameter;
struct __Burst_Parameter
{
	ViInt32 burst_src;
	ViReal64 burst_rate;
	ViReal64 burst_phase;
	ViReal64 burst_count_number;
	ViBoolean burst_status;
	ViInt32 burst_gatePolarity;
	ViInt32 burst_mode;
};

typedef struct __Sweep_Parameter Sweep_Parameter;
struct __Sweep_Parameter
{
    ViInt32 sweep_mode;
	ViInt32 sweep_src;
	ViReal64 sweep_time;
	ViReal64 sweep_start_freq;
	ViReal64 sweep_stop_freq;
	ViInt32 sweep_spacing;
	ViBoolean sweep_status;
};

typedef struct __Cal_Parameter Cal_Parameter;
struct __Cal_Parameter
{
//	ViInt32 board_number;			/*版号*/

	ViInt64 amp_segment_number_max;		/*幅度段的段个数*/
//	ViInt32 freq_segment_number_max;		/*频率段的段个数*/

//	ViPReal64 square_sine_amplitude_point;
	ViPReal64 freq_segment_point;		/*频率分段点*/

	ViPReal64 unique_1V_amp_data;		/*1V左右的幅度校正参数*/
	ViPReal64 unique_1V_offset_bias_data;		/*1V左右的乘法器偏移校正参数*/
	ViPReal64 unique_1V_offset_data;		/*1V左右的偏移校正参数*/

	ViPReal64 amp_segment_point;		/*非校正模式下 幅度分段点*/
	ViPReal64 amp_cal_segment_point;	/*校正模式下 幅度分段点*/

	ViPReal64 sine_amp_cal_data;		/*正弦波幅度校正数据*/
	ViPReal64 sine_offset_cal_data;		/*正弦波偏移校正数据*/
    ViPReal64 sine_offset_bias_cal_data;		/*正弦波偏移校正数据*/
	ViPReal64 sine_amp_freq_cal_data;		/*正弦波幅频校正数据*/

//	ViPReal64 square_amp_cal_data;		/*方波幅度校正数据*/
	ViPReal64 duty_cal_data;			/*方波占空比校正数据*/
	ViPReal64 zero_offset_cal_data;		/*零偏校正数据*/

    ViReal64 caled_amplitude;            /*幅度校正后的数据幅度数据*/
    ViReal64 unique_1v_amp_range_min;            /*1v特殊校正的幅度范围*/
    ViReal64 unique_1v_amp_range_max;            /*1v特殊校正的幅度范围*/
};

typedef struct __Analog_Register Analog_Register;
struct __Analog_Register
{
	ViUInt32 relay_reg;
	ViInt32 amp_segment_number;
	ViInt32 freq_segment_number;
};

typedef struct __Trigger_Parameter Trigger_Parameter;
struct __Trigger_Parameter
{
    ViInt32 trigger_source;
    ViUInt16 trigger_wave;
    ViInt32 trigger_slope;
    ViBoolean trigger_status;
    ViInt32 trigger_ext;
    ViReal64 trigger_delay;
    ViInt32 trigger_threshold;
    ViInt32 trigger_mode;
    ViReal64 rate;
};

typedef struct __Pulse_Parameter Pulse_Parameter;
struct __Pulse_Parameter
{
    ViReal64	pulsePeriod;
    ViReal64	pulseWidth;
    ViReal64	pulseTransition;
    ViInt32		pulseHold;
    ViReal64	pulseDutyCycle;
};

typedef struct __StdWaveform_Parameter StdWaveform_Parameter;
struct __StdWaveform_Parameter
{
    ViInt32 waveform;
	ViReal64 amplitude;
	ViReal64 frequency;
	ViReal64 DCoffset;
	ViReal64 dutyCycleHigh;/*百分数*/
	ViReal64 startphase;
	ViReal64 squareZeroOffset;
};

typedef struct __Output_Parameter Output_Parameter;
struct __Output_Parameter
{
    ViInt32 outputCount;
    ViInt32 operationMode ;
    ViBoolean outputEnabled ;
    ViReal64 outputImpedance ;
    ViInt32 outputMode ;
 //   ViInt32 refClockSource;
    ViInt32 outputPolarity;
};
typedef struct _Clk_Parameter Clk_Parameter;
struct _Clk_Parameter
{
    ViReal64 sample_rate;
    ViInt32 data_sample_src;
    ViInt32 ref_src;
    ViBoolean data_sample_output_status;
    ViBoolean ref_output_status;
};
typedef struct __Arb_Parameter Arb_Parameter;
struct __Arb_Parameter
{
	//ViChar name[ES1653_ARB_WAVEFORM_NAME_LEN];
    ViInt32 handle;
    ViInt32 size;
    ViReal64 gain;
    ViReal64 offset;
	ViReal64 *data;
	list_head node;
	ViReal64 freq;
};

typedef struct __ArbSeq_Parameter ArbSeq_Parameter;
struct __ArbSeq_Parameter
{
    ViInt32 length;       //波形段数
    ViInt32 *loop_count;   //loop times of each arb waveform
	ViInt32 handle;
	ViInt32 *wfm_handle;  // arb handle array
    ViReal64 gain;
    ViReal64 offset;
    list_head node;
};

typedef  struct __Modu_Parameter Modu_Parameter;
struct __Modu_Parameter
{
    ViInt32 waveform;
    ViReal64 freq;
    ViInt32 source;
};

typedef  struct __ES1653_Ch ES1653_Ch;
struct __ES1653_Ch
{
	ViSession io;
	ViInt8 channel;

    //ViReal64 sample_rate;


	ViInt32 modu_mode;
    Clk_Parameter clk_para;
	Analog_Register analog_register;

    StdWaveform_Parameter stdWfm_para;
	Arb_Parameter *arb_para;
	ArbSeq_Parameter *seq_para;
	list_head *arb;
	list_head *seq;
    Pulse_Parameter pulse_para;
    Output_Parameter output_para;

    Modu_Parameter modu;
	AM_Parameter am_para;
	FM_Parameter fm_para;
	PM_Parameter pm_para;
	FSK_Parameter fsk_para;
	PSK_Parameter psk_para;
	Burst_Parameter burst_para;
	Sweep_Parameter sweep_para;
    Trigger_Parameter trig_para;

	Cal_Parameter cal_parameter;  /*通道的校准参数*/
};


/****************************************************************************
 *---------------- Instrument Driver Function Declarations -----------------*
 ****************************************************************************/
    /*- Init and Close Functions -------------------------------------------*/
ViStatus ES1653_dll _VI_FUNC   ES1653_init (ViRsrc resourceName, ViBoolean IDQuery,
                                  ViBoolean resetDevice, ViSession *vi);
ViStatus ES1653_dll _VI_FUNC   ES1653_close (ViSession vi);
ViStatus ES1653_dll _VI_FUNC   ES1653_InitWithOptions (ViRsrc resourceName, ViBoolean IDQuery,
        ViBoolean resetDevice, ViConstString optionString,
        ViSession *newVi);

    /*- Basic Instrument Operation -----------------------------------------*/
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureOperationMode (ViSession vi, ViConstString ChannelName, ViInt32 OperationMode);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureOutputMode(ViSession vi, ViInt32 OutputMode);

ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureOutputFilter (ViSession vi, ViConstString	channelName, ViReal64 frequency);

ViStatus ES1653_dll _VI_FUNC ES1653_ConfigureRefClockSource (ViSession vi,
        ViInt32 refClockSourceSample);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureClockOutputEnable(ViSession vi, ViBoolean enable);
ViStatus ES1653_dll _VI_FUNC  ES1653_InitiateGeneration (ViSession vi);

ViStatus ES1653_dll _VI_FUNC  ES1653_AbortGeneration (ViSession vi);


ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureOutputEnabled (ViSession vi,
                                                  ViConstString channelName,
                                                  ViBoolean outputEnabled);

    /*- Standard Function Output --------------------------------------------*/

ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigurePulse (
	ViSession		vi,
	ViConstString	channelName,
	ViReal64		pulsePeriod,
	ViReal64		pulseWidth,
	ViReal64		pulseTransition
);

ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureStandardWaveform (
	ViSession		vi,
	ViConstString	channelName,
	ViInt32			waveform,
	ViReal64		amplitude,
	ViReal64		dcOffset,
	ViReal64		frequency,
	ViReal64		startPhase
);

ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigurePulseHold (
	ViSession	vi,
	ViInt32		hold
);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigurePulseDutyCycle (
	ViSession	vi,
	ViConstString	channelName,
	ViReal64	dutyCycle
);


    /*- Arbitrary Waveform Output -------------------------------------------*/
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureSampleRate (ViSession vi, ViReal64 sampleRate);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureArbFrequency (ViSession vi,
                                                ViConstString channelName,
                                                ViReal64 frequency);
ViStatus ES1653_dll _VI_FUNC  ES1653_ClearArbWaveform (ViSession vi,
                                           ViInt32 Handle);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureArbWaveform (ViSession vi,
                                             ViConstString channelName,
                                             ViInt32 Handle,
                                             ViReal64 Gain,
                                             ViReal64 Offset);
ViStatus ES1653_dll _VI_FUNC ES1653_ConfigureArbOffset(ViSession vi, ViConstString channelName, ViReal64 offset);
ViStatus ES1653_dll _VI_FUNC ES1653_ConfigureArbGain(ViSession vi, ViConstString channelName, ViReal64 gain);
ViStatus ES1653_dll _VI_FUNC ES1653_ConfigureArbWaveformHandle(ViSession vi, ViConstString channelName, ViInt32 handle);
ViStatus ES1653_dll _VI_FUNC ES1653_CreateArbWaveform (ViSession vi,
                                              ViInt32 Size,
                                              ViReal64 Data[],
                                              ViInt32 *Handle);
ViStatus ES1653_dll _VI_FUNC  ES1653_QueryArbWfmCapabilities (ViSession vi,
                                              ViInt32 *MaxNumWfms,
                                              ViInt32 *WfmQuantum,
                                              ViInt32 *MinWfmSize,
                                              ViInt32 *MaxWfmSize);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureSampleClockSource(ViSession vi,
                                              ViInt32 ClockSource);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureSampleClockOutputEnable(ViSession vi,
                                              ViBoolean enable);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureSampleRate (ViSession vi,
                                              ViReal64 SampleRate);

ViStatus ES1653_dll _VI_FUNC  ES1653_CreateArbSequence (ViSession vi,
		                            ViInt32 Length,
									ViInt32 WfmHandle[],
									ViInt32 LoopCount[],
									ViInt32 *Handle);

ViStatus ES1653_dll _VI_FUNC  ES1653_ClearArbSequence (ViSession vi,
		                            ViInt32 Handle);

//ViStatus ES1653_dll _VI_FUNC  ES1653_ClearArbMemory (ViSession vi);

ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureArbSequence (ViSession vi,
		                                     ViConstString channelName,
					                         ViInt32 Handle,
					                         ViReal64 Gain,
					                         ViReal64 Offset);

ViStatus ES1653_dll _VI_FUNC  ES1653_QueryArbSeqCapabilities (ViSession vi,
		                                        ViInt32 *MaxNumSeqs,
					                            ViInt32 *MinSeqLength,
								                ViInt32 *MaxSeqLength,
								                ViInt32 *MaxLoopCount);

ViStatus ES1653_dll _VI_FUNC ES1653_Seq_config(ViSession vi, ViConstString channelName, ViBoolean enable);
ViStatus ES1653_dll _VI_FUNC ES1653_Seq_SetLoopCount(ViSession vi, ViConstString channelName, ViInt32 *LoopCount, ViInt32 num);
ViStatus ES1653_dll _VI_FUNC ES1653_Seq_SetWaveform(ViSession vi, ViConstString channelName, ViUInt32 *data, ViInt32 *size, ViInt32 num);
ViStatus ES1653_dll _VI_FUNC ES1653_Seq_SetNumber(ViSession vi, ViConstString channelName, ViInt32 num);
ViStatus ES1653_dll _VI_FUNC ES1653_Seq_SetStartAddr(ViSession vi, ViConstString channelName, ViInt32 *addr, ViInt32 num);

/*--   configure stardard waveform single parameter   --*/
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureWfmFrequency(ViSession vi, ViConstString	channelName, ViReal64 frequency);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureWfmPhase(ViSession vi, ViConstString channelName, ViReal64 startPhase);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureFuncWaveform(ViSession vi, ViConstString	channelName,ViInt32 waveform);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureSquareDutyCycle(ViSession vi, ViConstString channelName, ViReal64 dutyCycle);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureWfmAmplitude(ViSession vi, ViConstString	channelName, ViReal64 amplitude);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureWfmOffset(ViSession vi, ViConstString channelName, ViReal64 offset);

/*--   configure AM function single parameter  --*/
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureAMEnabled (ViSession vi, ViConstString channelName, ViBoolean AMEnabled);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureAMSource (ViSession vi, ViConstString	channelName, ViInt32 source);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureAMDepth (ViSession vi, ViConstString channelName, ViReal64 depth);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureAMWaveform (ViSession vi, ViConstString channelName, ViInt32 waveform);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureAMFrequency (ViSession vi, ViConstString channelName, ViReal64 frequency);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureAMInternal (ViSession vi, ViConstString channelName,
                                                ViReal64 amDepth,ViInt32 amWaveform, ViReal64 amFrequency);

/*--   configure FM function single parameter  --*/
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureFMEnabled (ViSession vi, ViConstString channelName, ViBoolean FMEnabled);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureFMSource (ViSession vi, ViConstString channelName,ViInt32 source);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureFMDeviation(ViSession vi, ViConstString channelName, ViReal64 deviation);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureFMWaveform(ViSession vi, ViConstString channelName,ViInt32 waveform);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureFMFrequency(ViSession vi, ViConstString channelName,ViReal64 frequency);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureFMInternal (ViSession vi,ViConstString channelName,
                                                ViReal64 fmDeviation,ViInt32 fmWaveform,ViReal64 fmFrequency);

/*--   configure PM function single parameter  --*/
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigurePMEnabled (ViSession vi, ViConstString channelName, ViBoolean enabled);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigurePMSource (ViSession vi, ViConstString channelName,ViInt32 source);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigurePMDeviation(ViSession vi, ViConstString channelName, ViReal64 deviation);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigurePMWaveform(ViSession vi, ViConstString channelName, ViInt32 waveform);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigurePMFrequency(ViSession vi, ViConstString channelName, ViReal64 frequency);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigurePMInternal (ViSession vi, ViConstString channelName,
                                                ViReal64 pmDeviation, ViInt32 pmWaveform, ViReal64 pmFrequency);

//Burst_function
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureBurstCount (ViSession vi, ViConstString channelName, ViInt32 burstCount);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureBurstPhase (ViSession vi, ViConstString channelName, ViReal64 phase);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureBurstEnabled (ViSession vi, ViConstString channelName, ViBoolean BurstEnabled);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureBurstInternal (ViSession vi, ViConstString channelName, ViReal64 burstRate);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureBurstMode (ViSession vi, ViConstString channelName, ViInt32 mode);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureBurstSource(ViSession vi, ViConstString channelName, ViInt32 source);
//FSK function
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureFSKEnabled (ViSession vi, ViConstString channelName, ViBoolean FSKEnabled);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureFSKHopFrequency(ViSession vi, ViConstString channelName, ViReal64 hopFrequency);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureFSKInternal (ViSession vi, ViConstString channelName, ViReal64 fskRate);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureFSKMode (ViSession vi, ViConstString channelName, ViInt32 mode);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureFSKSource(ViSession vi, ViConstString channelName, ViInt32 source);
//PSK function
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigurePSKEnabled(ViSession vi,ViConstString channelName, ViBoolean enabled);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigurePSKHopPhase (ViSession vi, ViConstString channelName, ViReal64 hopPhase);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigurePSKInternal (ViSession vi, ViConstString channelName, ViReal64 pskRate);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigurePSKMode (ViSession vi, ViConstString channelName, ViInt32 mode);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigurePSKSource(ViSession vi, ViConstString channelName, ViInt32 source);
//Sweep function

ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureSweep (ViSession vi, ViConstString channelName, ViInt32 sweepSpacing, ViReal64 startFreq,ViReal64 stopFreq, ViReal64 sweepTime);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureSweepSource (	ViSession vi,  ViConstString channelName, ViInt32 source);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureSweepEnabled(	ViSession vi,  ViConstString channelName,ViBoolean SWEEPEnabled);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureSweepStartFreq(ViSession vi, ViConstString channelName,ViReal64 start_freq);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureSweepStopFreq(ViSession vi, ViConstString channelName,ViReal64 stop_freq);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureSweepSpacing(ViSession vi, ViConstString channelName,ViInt32 spacing);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureSweepTime(ViSession vi, ViConstString channelName,ViReal64 time);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureSweepMode (ViSession vi, ViConstString channelName, ViInt32 mode);
//trigger function
ViStatus ES1653_dll _VI_FUNC ES1653_ConfigureTriggerLevel(ViSession vi, ViReal64 vol);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureTriggerInternal(ViSession vi, ViConstString channelName, ViReal64 rate);
ViStatus ES1653_dll _VI_FUNC  ES1653_SendSoftwareTrigger(ViSession vi, ViConstString channelName, ViBoolean value);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureTriggerSource (ViSession vi,ViConstString channelName,ViInt32 source);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureTriggerSlope (ViSession vi,ViConstString channelName,ViInt32 slope);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureTriggerDelay (ViSession vi,ViConstString channelName,ViReal64 delay);
ViStatus ES1653_dll _VI_FUNC ES1653_ConfigureTriggerMode (
											 ViSession vi,
											 ViConstString channelName,
											 ViInt32 mode);
ViStatus ES1653_dll _VI_FUNC  ES1653_ConfigureTriggerEnabled (ViSession vi, ViConstString channelName, ViBoolean outputTrig);
    /*- Set, Get, and Check Attribute Functions ----------------------------*/

ViStatus ES1653_dll _VI_FUNC   ES1653_GetAttributeViInt32 (ViSession vi, ViConstString channelName, ViAttr attributeId, ViInt32 *value);
ViStatus ES1653_dll _VI_FUNC   ES1653_GetAttributeViReal64 (ViSession vi, ViConstString channelName, ViAttr attributeId, ViReal64 *value);
ViStatus ES1653_dll _VI_FUNC   ES1653_GetAttributeViString (ViSession vi, ViConstString channelName, ViAttr attributeId, ViInt32 bufSize, ViChar value[]);
ViStatus ES1653_dll _VI_FUNC   ES1653_GetAttributeViSession (ViSession vi, ViConstString channelName, ViAttr attributeId, ViSession *value);
ViStatus ES1653_dll _VI_FUNC   ES1653_GetAttributeViBoolean (ViSession vi, ViConstString channelName, ViAttr attributeId, ViBoolean *value);

ViStatus ES1653_dll _VI_FUNC   ES1653_SetAttributeViInt32 (ViSession vi, ViConstString channelName, ViAttr attributeId, ViInt32 value);
ViStatus ES1653_dll _VI_FUNC   ES1653_SetAttributeViReal64 (ViSession vi, ViConstString channelName, ViAttr attributeId, ViReal64 value);
ViStatus ES1653_dll _VI_FUNC   ES1653_SetAttributeViString (ViSession vi, ViConstString channelName, ViAttr attributeId, ViConstString value);
ViStatus ES1653_dll _VI_FUNC   ES1653_SetAttributeViSession (ViSession vi, ViConstString channelName, ViAttr attributeId, ViSession value);
ViStatus ES1653_dll _VI_FUNC   ES1653_SetAttributeViBoolean (ViSession vi, ViConstString channelName, ViAttr attributeId, ViBoolean value);

ViStatus ES1653_dll _VI_FUNC   ES1653_CheckAttributeViInt32 (ViSession vi, ViConstString channelName, ViAttr attributeId, ViInt32 value);
ViStatus ES1653_dll _VI_FUNC   ES1653_CheckAttributeViReal64 (ViSession vi, ViConstString channelName, ViAttr attributeId, ViReal64 value);
ViStatus ES1653_dll _VI_FUNC   ES1653_CheckAttributeViString (ViSession vi, ViConstString channelName, ViAttr attributeId, ViConstString value);
ViStatus ES1653_dll _VI_FUNC   ES1653_CheckAttributeViSession (ViSession vi, ViConstString channelName, ViAttr attributeId, ViSession value);
ViStatus ES1653_dll _VI_FUNC   ES1653_CheckAttributeViBoolean (ViSession vi, ViConstString channelName, ViAttr attributeId, ViBoolean value);


/****************************************************************************
 *------------------------ Error And Completion Codes ----------------------*
 ****************************************************************************/

#define ES1653_ERROR_NO_WFMS_AVAILABLE         IVIFGEN_ERROR_NO_WFMS_AVAILABLE
#define ES1653_ERROR_WFM_IN_USE                IVIFGEN_ERROR_WFM_IN_USE
#define ES1653_ERROR_TRIGGER_NOT_SOFTWARE      IVIFGEN_ERROR_TRIGGER_NOT_SOFTWARE
#define ES1653_ERROR_INVALID_WFM_CHANNEL       IVIFGEN_ERROR_INVALID_WFM_CHANNEL
//#define IVI_ERROR_BASE                      (_VI_ERROR + IVI_STATUS_CODE_BASE)
#define ES1653_ERROR_SEQ_IN_USE                IVIFGEN_ERROR_SEQ_IN_USE
#define ES1653_ERROR_NO_SEQS_AVAILABLE         IVIFGEN_ERROR_NO_SEQS_AVAILABLE
#define ES1653_ERROR_WFM_IN_USE                IVIFGEN_ERROR_WFM_IN_USE
#define ES1653_ERROR_NO_WFMS_AVAILABLE         IVIFGEN_ERROR_NO_WFMS_AVAILABLE
#define ES1653_ERROR_TRIGGER_NOT_SOFTWARE      IVIFGEN_ERROR_TRIGGER_NOT_SOFTWARE
#define ES1653_ERROR_INVALID_WFM_CHANNEL       IVIFGEN_ERROR_INVALID_WFM_CHANNEL
#define ES1653_ERROR_NOT_CONFIGURABLE          IVIFGEN_ERROR_NOT_CONFIGURABLE
#define ES1653_ERROR_NOT_GENERATING            IVIFGEN_ERROR_NOT_GENERATING
//#define ES1653_ERROR_INVALID_MODE              IVIFGEN_ERROR_INVALID_MODE
//#define ES1653_ERROR_INVALID_WFM_LENGTH        IVIFGEN_ERROR_INVALID_WFM_LENGTH
#define ES1653_ERROR_INVALID_WFM_ELEMENT       IVIFGEN_ERROR_INVALID_WFM_ELEMENT
#define ES1653_ERROR_INVALID_WAVEFORM          IVIFGEN_ERROR_INVALID_WAVEFORM
#define ES1653_ERROR_INVALID_SEQ_LENGTH        IVIFGEN_ERROR_INVALID_SEQ_LENGTH
#define ES1653_ERROR_INVALID_LOOP_COUNT        IVIFGEN_ERROR_INVALID_LOOP_COUNT
#define ES1653_ERROR_INVALID_SEQUENCE          IVIFGEN_ERROR_INVALID_SEQUENCE

#define ES1653_ERROR_CANNOT_RECOVER            IVI_ERROR_CANNOT_RECOVER
#define ES1653_ERROR_INSTRUMENT_STATUS         IVI_ERROR_INSTRUMENT_STATUS
#define ES1653_ERROR_CANNOT_OPEN_FILE          IVI_ERROR_CANNOT_OPEN_FILE
#define ES1653_ERROR_READING_FILE              IVI_ERROR_READING_FILE
#define ES1653_ERROR_WRITING_FILE              IVI_ERROR_WRITING_FILE
#define ES1653_ERROR_INVALID_PATHNAME          IVI_ERROR_INVALID_PATHNAME
#define ES1653_ERROR_INVALID_ATTRIBUTE         IVI_ERROR_INVALID_ATTRIBUTE
#define ES1653_ERROR_ATTR_NOT_WRITEABLE        IVI_ERROR_ATTR_NOT_WRITEABLE
#define ES1653_ERROR_ATTR_NOT_READABLE         IVI_ERROR_ATTR_NOT_READABLE
#define ES1653_ERROR_INVALID_VALUE             IVI_ERROR_INVALID_VALUE
#define ES1653_ERROR_FUNCTION_NOT_SUPPORTED    IVI_ERROR_FUNCTION_NOT_SUPPORTED
#define ES1653_ERROR_ATTRIBUTE_NOT_SUPPORTED   IVI_ERROR_ATTRIBUTE_NOT_SUPPORTED
#define ES1653_ERROR_ERROR_VALUE_NOT_SUPPORTED IVI_ERROR_VALUE_NOT_SUPPORTED
#define ES1653_ERROR_TYPES_DO_NOT_MATCH        IVI_ERROR_TYPES_DO_NOT_MATCH
#define ES1653_ERROR_NOT_INITIALIZED           IVI_ERROR_NOT_INITIALIZED
#define ES1653_ERROR_UNKNOWN_CHANNEL_NAME      IVI_ERROR_UNKNOWN_CHANNEL_NAME
#define ES1653_ERROR_TOO_MANY_OPEN_FILES       IVI_ERROR_TOO_MANY_OPEN_FILES
#define ES1653_ERROR_CHANNEL_NAME_REQUIRED     IVI_ERROR_CHANNEL_NAME_REQUIRED
#define ES1653_ERROR_CHANNEL_NAME_NOT_ALLOWED  IVI_ERROR_CHANNEL_NAME_NOT_ALLOWED
#define ES1653_ERROR_MISSING_OPTION_NAME       IVI_ERROR_MISSING_OPTION_NAME
#define ES1653_ERROR_MISSING_OPTION_VALUE      IVI_ERROR_MISSING_OPTION_VALUE
#define ES1653_ERROR_BAD_OPTION_NAME           IVI_ERROR_BAD_OPTION_NAME
#define ES1653_ERROR_BAD_OPTION_VALUE          IVI_ERROR_BAD_OPTION_VALUE
#define ES1653_ERROR_OUT_OF_MEMORY             IVI_ERROR_OUT_OF_MEMORY
#define ES1653_ERROR_OPERATION_PENDING         IVI_ERROR_OPERATION_PENDING
#define ES1653_ERROR_NULL_POINTER              IVI_ERROR_NULL_POINTER
#define ES1653_ERROR_UNEXPECTED_RESPONSE       IVI_ERROR_UNEXPECTED_RESPONSE
#define ES1653_ERROR_FILE_NOT_FOUND            IVI_ERROR_FILE_NOT_FOUND
#define ES1653_ERROR_INVALID_FILE_FORMAT       IVI_ERROR_INVALID_FILE_FORMAT
#define ES1653_ERROR_STATUS_NOT_AVAILABLE      IVI_ERROR_STATUS_NOT_AVAILABLE
#define ES1653_ERROR_ID_QUERY_FAILED           IVI_ERROR_ID_QUERY_FAILED
#define ES1653_ERROR_RESET_FAILED              IVI_ERROR_RESET_FAILED
#define ES1653_ERROR_RESOURCE_UNKNOWN          IVI_ERROR_RESOURCE_UNKNOWN
#define ES1653_ERROR_ALREADY_INITIALIZED        IVI_ERROR_ALREADY_INITIALIZED
#define ES1653_ERROR_CANNOT_CHANGE_SIMULATION_STATE    IVI_ERROR_CANNOT_CHANGE_SIMULATION_STATE
#define ES1653_ERROR_INVALID_NUMBER_OF_LEVELS_IN_SELECTOR  IVI_ERROR_INVALID_NUMBER_OF_LEVELS_IN_SELECTOR
#define ES1653_ERROR_INVALID_RANGE_IN_SELECTOR IVI_ERROR_INVALID_RANGE_IN_SELECTOR
#define ES1653_ERROR_UNKNOWN_NAME_IN_SELECTOR  IVI_ERROR_UNKNOWN_NAME_IN_SELECTOR
#define ES1653_ERROR_BADLY_FORMED_SELECTOR     IVI_ERROR_BADLY_FORMED_SELECTOR
#define ES1653_ERROR_UNKNOWN_PHYSICAL_IDENTIFIER       IVI_ERROR_UNKNOWN_PHYSICAL_IDENTIFIER
#define ES1653_WARN_NSUP_ID_QUERY              IVI_WARN_NSUP_ID_QUERY
#define ES1653_WARN_NSUP_RESET                 IVI_WARN_NSUP_RESET
#define ES1653_WARN_NSUP_SELF_TEST             IVI_WARN_NSUP_SELF_TEST
#define ES1653_WARN_NSUP_ERROR_QUERY           IVI_WARN_NSUP_ERROR_QUERY
#define ES1653_WARN_NSUP_REV_QUERY             IVI_WARN_NSUP_REV_QUERY
#define ES1653_ATTR_IO_SESSION		            IVI_ATTR_IO_SESSION

#define ES1653_ERROR_ABORT_GENERATION_UNSUPPORTED (IVI_SPECIFIC_ERROR_BASE + 0x21L)
#define ES1653_ERROR_NOT_INITIALIZED           IVI_ERROR_NOT_INITIALIZED
#define ES1653_ERROR_INVALID_HANDLE            (IVI_SPECIFIC_ERROR_BASE + 0x22L)
/****************************************************************************
 *---------------------------- End Include File ----------------------------*
 ****************************************************************************/
#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif
#endif /* __ES1653_HEADER */
