/** \file ivifgen.h
 * \brief  UESTC IVI Class Driver
 *
 * 任意波形发生器类驱动函数声明和宏定义
 * \author yang_long_qiong
 * \date 2014 - 2015
 */
#ifndef _IVIFGEN_H_
#define _IVIFGEN_H_

#ifdef  _WIN32
#ifndef   BUILD_DLL
    #define  DLL_EXPORT __declspec(dllexport)
#else
    #define  DLL_EXPORT __declspec(dllimport)
#endif
#endif // _WIN32
#ifdef  linux
#define  DLL_EXPORT
#endif // linux

#include "visatype.h"
#ifdef __cplusplus
extern "C"{
#endif


/******************************************************************************
 *---------------------- IviFgen Class Attribute Defines ---------------------*
 ******************************************************************************/
/////TODO
  /*- IVI Inherent Attributes -*/
        /*- User Options -*/
#define IVIFGEN_ATTR_CACHE                     IVI_ATTR_CACHE                       /* ViBoolean */
#define IVIFGEN_ATTR_RANGE_CHECK               IVI_ATTR_RANGE_CHECK                 /* ViBoolean */
#define IVIFGEN_ATTR_QUERY_INSTRUMENT_STATUS   IVI_ATTR_QUERY_INSTRUMENT_STATUS     /* ViBoolean */
#define IVIFGEN_ATTR_RECORD_COERCIONS          IVI_ATTR_RECORD_COERCIONS            /* ViBoolean */
#define IVIFGEN_ATTR_SIMULATE                  IVI_ATTR_SIMULATE                    /* ViBoolean */
#define IVIFGEN_ATTR_INTERCHANGE_CHECK         IVI_ATTR_INTERCHANGE_CHECK           /* ViBoolean */
#define IVIFGEN_ATTR_SPY                       IVI_ATTR_SPY                         /* ViBoolean */
#define IVIFGEN_ATTR_USE_SPECIFIC_SIMULATION   IVI_ATTR_USE_SPECIFIC_SIMULATION     /* ViBoolean */

        /*- Instrument Capabilities -*/
#define IVIFGEN_ATTR_GROUP_CAPABILITIES        IVI_ATTR_GROUP_CAPABILITIES          /* ViString, read-only */
#define IVIFGEN_ATTR_FUNCTION_CAPABILITIES     IVI_ATTR_FUNCTION_CAPABILITIES       /* ViString, read-only */

        /*- Class Driver Information -*/
#define IVIFGEN_ATTR_CLASS_DRIVER_PREFIX                         IVI_ATTR_CLASS_DRIVER_PREFIX         /* ViString, read-only */
#define IVIFGEN_ATTR_CLASS_DRIVER_VENDOR                         IVI_ATTR_CLASS_DRIVER_VENDOR         /* ViString, read-only */
#define IVIFGEN_ATTR_CLASS_DRIVER_DESCRIPTION                    IVI_ATTR_CLASS_DRIVER_DESCRIPTION    /* ViString, read-only */
#define IVIFGEN_ATTR_CLASS_DRIVER_CLASS_SPEC_MAJOR_VERSION       IVI_ATTR_CLASS_DRIVER_CLASS_SPEC_MAJOR_VERSION  /* ViInt32,  read-only */
#define IVIFGEN_ATTR_CLASS_DRIVER_CLASS_SPEC_MINOR_VERSION       IVI_ATTR_CLASS_DRIVER_CLASS_SPEC_MINOR_VERSION  /* ViInt32,  read-only */

        /*- Specific Driver Information -*/
#define IVIFGEN_ATTR_SPECIFIC_DRIVER_PREFIX                      IVI_ATTR_SPECIFIC_DRIVER_PREFIX      /* ViString, read-only */
#define IVIFGEN_ATTR_SPECIFIC_DRIVER_LOCATOR                     IVI_ATTR_SPECIFIC_DRIVER_LOCATOR     /* ViString, read-only */
#define IVIFGEN_ATTR_IO_RESOURCE_DESCRIPTOR                      IVI_ATTR_IO_RESOURCE_DESCRIPTOR      /* ViString, read-only */
#define IVIFGEN_ATTR_LOGICAL_NAME                                IVI_ATTR_LOGICAL_NAME                /* ViString, read-only */
#define IVIFGEN_ATTR_SPECIFIC_DRIVER_VENDOR                      IVI_ATTR_SPECIFIC_DRIVER_VENDOR      /* ViString, read-only */
#define IVIFGEN_ATTR_SPECIFIC_DRIVER_DESCRIPTION                 IVI_ATTR_SPECIFIC_DRIVER_DESCRIPTION /* ViString, read-only */
#define IVIFGEN_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION    IVI_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION  /* ViInt32,  read-only */
#define IVIFGEN_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION    IVI_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION  /* ViInt32,  read-only */

        /*- Instrument Information -*/
#define IVIFGEN_ATTR_INSTRUMENT_FIRMWARE_REVISION     IVI_ATTR_INSTRUMENT_FIRMWARE_REVISION /* ViString, read-only */
#define IVIFGEN_ATTR_INSTRUMENT_MANUFACTURER          IVI_ATTR_INSTRUMENT_MANUFACTURER      /* ViString, read-only */
#define IVIFGEN_ATTR_INSTRUMENT_MODEL                 IVI_ATTR_INSTRUMENT_MODEL             /* ViString, read-only */
#define IVIFGEN_ATTR_SUPPORTED_INSTRUMENT_MODELS      IVI_ATTR_SUPPORTED_INSTRUMENT_MODELS

        /*- Version Information -*/
#define IVIFGEN_ATTR_CLASS_DRIVER_REVISION            IVI_ATTR_CLASS_DRIVER_REVISION              /* ViString, read-only */

#define IVIFGEN_ATTR_SPECIFIC_DRIVER_REVISION         IVI_ATTR_SPECIFIC_DRIVER_REVISION             /* ViString, read-only */

        /*- Driver Setup Information -*/
#define IVIFGEN_ATTR_DRIVER_SETUP                     IVI_ATTR_DRIVER_SETUP                /* ViString */

 /*- IviFgen Fundamental Attributes -*/
#define IVIFGEN_ATTR_CHANNEL_COUNT              IVI_ATTR_CHANNEL_COUNT              /* (ViInt32), read-only */
#define IVIFGEN_ATTR_OUTPUT_MODE                (IVI_CLASS_PUBLIC_ATTR_BASE + 1L)   /* (ViInt32) */
#define IVIFGEN_ATTR_REF_CLOCK_SOURCE           (IVI_CLASS_PUBLIC_ATTR_BASE + 2L)   /* (ViInt32) */
#define IVIFGEN_ATTR_OPERATION_MODE             (IVI_CLASS_PUBLIC_ATTR_BASE + 5L)   /* (ViInt32,    Multi-Channel) */
#define IVIFGEN_ATTR_OUTPUT_ENABLED             (IVI_CLASS_PUBLIC_ATTR_BASE + 3L)   /* (ViBoolean,  Multi-Channel) */
#define IVIFGEN_ATTR_OUTPUT_IMPEDANCE           (IVI_CLASS_PUBLIC_ATTR_BASE + 4L)   /* (ViReal64,   Multi-Channel) */

/*- IviFgenSampleClock Extended Attributes -*/
#define IVIFGEN_ATTR_SAMPLE_CLOCK_SOURCE         (IVI_CLASS_PUBLIC_ATTR_BASE + 21L)  /* (ViInt32)   */
#define IVIFGEN_ATTR_SAMPLE_CLOCK_OUTPUT_ENABLED (IVI_CLASS_PUBLIC_ATTR_BASE + 22L) /* (ViBoolean) */

 /*- IviFgenTerminalConfiguration Extended Attributes -*/
#define IVIFGEN_ATTR_TERMINAL_CONFIGURATION      (IVI_CLASS_PUBLIC_ATTR_BASE + 31L)  /* (ViInt32,    Multi-Channel) */

/*- IviFgenStdFunc Extended Attributes -*/
#define IVIFGEN_ATTR_FUNC_WAVEFORM              (IVI_CLASS_PUBLIC_ATTR_BASE + 101L)  /* (ViInt32,  Multi-Channel)   */
#define IVIFGEN_ATTR_FUNC_AMPLITUDE             (IVI_CLASS_PUBLIC_ATTR_BASE + 102L)  /* (ViReal64,  Multi-Channel)  */
#define IVIFGEN_ATTR_FUNC_DC_OFFSET             (IVI_CLASS_PUBLIC_ATTR_BASE + 103L)  /* (ViReal64,  Multi-Channel)  */
#define IVIFGEN_ATTR_FUNC_FREQUENCY             (IVI_CLASS_PUBLIC_ATTR_BASE + 104L)  /* (ViReal64,  Multi-Channel)  */
#define IVIFGEN_ATTR_FUNC_START_PHASE           (IVI_CLASS_PUBLIC_ATTR_BASE + 105L)  /* (ViReal64,  Multi-Channel)  */
#define IVIFGEN_ATTR_FUNC_DUTY_CYCLE_HIGH       (IVI_CLASS_PUBLIC_ATTR_BASE + 106L)  /* (ViReal64,  Multi-Channel)  */

 /*- IviFgenArbWfm Extended Attributes -*/
#define IVIFGEN_ATTR_ARB_WAVEFORM_HANDLE        (IVI_CLASS_PUBLIC_ATTR_BASE + 201L)  /* (ViInt32,  Multi-Channel)   */
#define IVIFGEN_ATTR_ARB_GAIN                   (IVI_CLASS_PUBLIC_ATTR_BASE + 202L)  /* (ViReal64, Multi-Channel)  */
#define IVIFGEN_ATTR_ARB_OFFSET                 (IVI_CLASS_PUBLIC_ATTR_BASE + 203L)  /* (ViReal64, Multi-Channel)  */
#define IVIFGEN_ATTR_ARB_SAMPLE_RATE            (IVI_CLASS_PUBLIC_ATTR_BASE + 204L)  /* (ViReal64)  */

#define IVIFGEN_ATTR_MAX_NUM_WAVEFORMS          (IVI_CLASS_PUBLIC_ATTR_BASE + 205L)  /* (ViInt32, Read-only)   */
#define IVIFGEN_ATTR_WAVEFORM_QUANTUM           (IVI_CLASS_PUBLIC_ATTR_BASE + 206L)  /* (ViInt32, Read-only)   */
#define IVIFGEN_ATTR_MIN_WAVEFORM_SIZE          (IVI_CLASS_PUBLIC_ATTR_BASE + 207L)  /* (ViInt32, Read-only)   */
#define IVIFGEN_ATTR_MAX_WAVEFORM_SIZE          (IVI_CLASS_PUBLIC_ATTR_BASE + 208L)  /* (ViInt32, Read-only)   */

    /*- IviFgenArbFrequency Extended Attributes -*/
#define IVIFGEN_ATTR_ARB_FREQUENCY              (IVI_CLASS_PUBLIC_ATTR_BASE + 209L)  /* (ViReal64, Multi-Channel)  */

    /*- IviFgenArbSeq Extended Attributes -*/
#define IVIFGEN_ATTR_ARB_SEQUENCE_HANDLE        (IVI_CLASS_PUBLIC_ATTR_BASE + 211L)  /* (ViInt32, Multi-Channel)   */
#define IVIFGEN_ATTR_MAX_NUM_SEQUENCES          (IVI_CLASS_PUBLIC_ATTR_BASE + 212L)  /* (ViInt32, Read-only)   */
#define IVIFGEN_ATTR_MIN_SEQUENCE_LENGTH        (IVI_CLASS_PUBLIC_ATTR_BASE + 213L)  /* (ViInt32, Read-only)   */
#define IVIFGEN_ATTR_MAX_SEQUENCE_LENGTH        (IVI_CLASS_PUBLIC_ATTR_BASE + 214L)  /* (ViInt32, Read-only)   */
#define IVIFGEN_ATTR_MAX_LOOP_COUNT             (IVI_CLASS_PUBLIC_ATTR_BASE + 215L)  /* (ViInt32, Read-only)   */

    /*- IviFgenArbWfmSize64 Extended Attributes -*/
#define IVIFGEN_ATTR_MIN_WAVEFORM_SIZE64        (IVI_CLASS_PUBLIC_ATTR_BASE + 221L)  /* (ViInt64, Read-only)   */
#define IVIFGEN_ATTR_MAX_WAVEFORM_SIZE64        (IVI_CLASS_PUBLIC_ATTR_BASE + 222L)  /* (ViInt64, Read-only)   */

    /*- IviFgenArbWfmBinary Extended Attributes -*/
#define IVIFGEN_ATTR_BINARY_ALIGNMENT           (IVI_CLASS_PUBLIC_ATTR_BASE + 241L)  /* (ViInt32, Read-only)   */
#define	IVIFGEN_ATTR_SAMPLE_BIT_RESOLUTION      (IVI_CLASS_PUBLIC_ATTR_BASE + 242L)  /* (ViInt32, Read-only)   */

    /*- IviFgenArbDataMask Extended Attributes -*/
#define IVIFGEN_ATTR_OUTPUT_DATA_MASK           (IVI_CLASS_PUBLIC_ATTR_BASE + 261L)  /* (ViInt32) */

    /*- IviFgenArbSeqDepth Extended Attributes -*/
#define IVIFGEN_ATTR_SEQUENCE_DEPTH_MAX         (IVI_CLASS_PUBLIC_ATTR_BASE + 281L)  /* (ViInt32, Read-only)   */

    /*- IviFgenTrigger Extended Attributes -*/
#define IVIFGEN_ATTR_TRIGGER_SOURCE             (IVI_CLASS_PUBLIC_ATTR_BASE + 302L)  /* (ViInt32, Multi-Channel)   */

    /*- IviFgenInternalTrigger Extended Attributes -*/
#define IVIFGEN_ATTR_INTERNAL_TRIGGER_RATE      (IVI_CLASS_PUBLIC_ATTR_BASE + 310L)  /* (ViReal64)   */

    /*- IviFgenStartTrigger Extended Attributes -*/
#define IVIFGEN_ATTR_START_TRIGGER_DELAY        (IVI_CLASS_PUBLIC_ATTR_BASE + 320L)  /* (ViReal64, Multi-Channel)  */
#define IVIFGEN_ATTR_START_TRIGGER_SLOPE        (IVI_CLASS_PUBLIC_ATTR_BASE + 321L)  /* (ViInt32,  Multi-Channel)  */
#define IVIFGEN_ATTR_START_TRIGGER_SOURCE       (IVI_CLASS_PUBLIC_ATTR_BASE + 322L)  /* (ViString, Multi-Channel)  */
#define IVIFGEN_ATTR_START_TRIGGER_THRESHOLD    (IVI_CLASS_PUBLIC_ATTR_BASE + 323L)  /* (ViReal64, Multi-Channel)  */

    /*- IviFgenStopTrigger Extended Attributes -*/
#define IVIFGEN_ATTR_STOP_TRIGGER_DELAY         (IVI_CLASS_PUBLIC_ATTR_BASE + 330L)  /* (ViReal64, Multi-Channel)  */
#define IVIFGEN_ATTR_STOP_TRIGGER_SLOPE         (IVI_CLASS_PUBLIC_ATTR_BASE + 331L)  /* (ViInt32,  Multi-Channel)  */
#define IVIFGEN_ATTR_STOP_TRIGGER_SOURCE        (IVI_CLASS_PUBLIC_ATTR_BASE + 332L)  /* (ViString, Multi-Channel)  */
#define IVIFGEN_ATTR_STOP_TRIGGER_THRESHOLD     (IVI_CLASS_PUBLIC_ATTR_BASE + 333L)  /* (ViReal64, Multi-Channel)  */

    /*- IviFgenHoldTrigger Extended Attributes -*/
#define IVIFGEN_ATTR_HOLD_TRIGGER_DELAY         (IVI_CLASS_PUBLIC_ATTR_BASE + 340L)  /* (ViReal64, Multi-Channel)  */
#define IVIFGEN_ATTR_HOLD_TRIGGER_SLOPE         (IVI_CLASS_PUBLIC_ATTR_BASE + 341L)  /* (ViInt32,  Multi-Channel)  */
#define IVIFGEN_ATTR_HOLD_TRIGGER_SOURCE        (IVI_CLASS_PUBLIC_ATTR_BASE + 342L)  /* (ViString, Multi-Channel)  */
#define IVIFGEN_ATTR_HOLD_TRIGGER_THRESHOLD      (IVI_CLASS_PUBLIC_ATTR_BASE + 343L)  /* (ViReal64, Multi-Channel)  */

    /*- IviFgenBurst Extended Attributes -*/
#define IVIFGEN_ATTR_BURST_COUNT                (IVI_CLASS_PUBLIC_ATTR_BASE + 350L)  /* (ViInt32, Multi-Channel)   */

    /*- IviFgenResumeTrigger Extended Attributes -*/
#define IVIFGEN_ATTR_RESUME_TRIGGER_DELAY       (IVI_CLASS_PUBLIC_ATTR_BASE + 360L)  /* (ViReal64, Multi-Channel)  */
#define IVIFGEN_ATTR_RESUME_TRIGGER_SLOPE       (IVI_CLASS_PUBLIC_ATTR_BASE + 361L)  /* (ViInt32,  Multi-Channel)  */
#define IVIFGEN_ATTR_RESUME_TRIGGER_SOURCE      (IVI_CLASS_PUBLIC_ATTR_BASE + 362L)  /* (ViString, Multi-Channel)  */
#define IVIFGEN_ATTR_RESUME_TRIGGER_THRESHOLD   (IVI_CLASS_PUBLIC_ATTR_BASE + 363L)  /* (ViReal64, Multi-Channel)  */

    /*- IviFgenAdvanceTrigger Extended Attributes -*/
#define IVIFGEN_ATTR_ADVANCE_TRIGGER_DELAY      (IVI_CLASS_PUBLIC_ATTR_BASE + 370L)  /* (ViReal64, Multi-Channel)  */
#define IVIFGEN_ATTR_ADVANCE_TRIGGER_SLOPE      (IVI_CLASS_PUBLIC_ATTR_BASE + 371L)  /* (ViInt32,  Multi-Channel)  */
#define IVIFGEN_ATTR_ADVANCE_TRIGGER_SOURCE     (IVI_CLASS_PUBLIC_ATTR_BASE + 372L)  /* (ViString, Multi-Channel)  */
#define IVIFGEN_ATTR_ADVANCE_TRIGGER_THRESHOLD  (IVI_CLASS_PUBLIC_ATTR_BASE + 373L)  /* (ViReal64, Multi-Channel)  */

    /*- IviFgenModulateAM Extended Attributes -*/
#define IVIFGEN_ATTR_AM_ENABLED                 (IVI_CLASS_PUBLIC_ATTR_BASE + 401L)  /* (ViBoolean, Multi-Channel) */
#define IVIFGEN_ATTR_AM_SOURCE                  (IVI_CLASS_PUBLIC_ATTR_BASE + 402L)  /* (ViInt32, Multi-Channel)   */
#define IVIFGEN_ATTR_AM_INTERNAL_DEPTH          (IVI_CLASS_PUBLIC_ATTR_BASE + 403L)  /* (ViReal64)  */
#define IVIFGEN_ATTR_AM_INTERNAL_WAVEFORM       (IVI_CLASS_PUBLIC_ATTR_BASE + 404L)  /* (ViInt32)   */
#define IVIFGEN_ATTR_AM_INTERNAL_FREQUENCY      (IVI_CLASS_PUBLIC_ATTR_BASE + 405L)  /* (ViReal64)  */

    /*- IviFgenModulateFM Extended Attributes -*/
#define IVIFGEN_ATTR_FM_ENABLED                 (IVI_CLASS_PUBLIC_ATTR_BASE + 501L)  /* (ViBoolean, Multi-Channel) */
#define IVIFGEN_ATTR_FM_SOURCE                  (IVI_CLASS_PUBLIC_ATTR_BASE + 502L)  /* (ViInt32, Multi-Channel)   */
#define IVIFGEN_ATTR_FM_INTERNAL_DEVIATION      (IVI_CLASS_PUBLIC_ATTR_BASE + 503L)  /* (ViReal64)  */
#define IVIFGEN_ATTR_FM_INTERNAL_WAVEFORM       (IVI_CLASS_PUBLIC_ATTR_BASE + 504L)  /* (ViInt32)   */
#define IVIFGEN_ATTR_FM_INTERNAL_FREQUENCY      (IVI_CLASS_PUBLIC_ATTR_BASE + 505L)  /* (ViReal64)  */

    /*- IviFgenDataMarker Extended Attributes -*/
#define IVIFGEN_ATTR_DATAMARKER_AMPLITUDE       (IVI_CLASS_PUBLIC_ATTR_BASE + 601L)  /* (ViReal64) */
#define IVIFGEN_ATTR_DATAMARKER_BIT_POSITION    (IVI_CLASS_PUBLIC_ATTR_BASE + 602L)  /* (ViInt32)  */
#define IVIFGEN_ATTR_DATAMARKER_COUNT           (IVI_CLASS_PUBLIC_ATTR_BASE + 603L)  /* (ViInt32, Read-only )      */
#define IVIFGEN_ATTR_DATAMARKER_DELAY           (IVI_CLASS_PUBLIC_ATTR_BASE + 604L)  /* (ViReal64) */
#define IVIFGEN_ATTR_DATAMARKER_DESTINATION     (IVI_CLASS_PUBLIC_ATTR_BASE + 605L)  /* (ViString) */
#define IVIFGEN_ATTR_DATAMARKER_POLARITY        (IVI_CLASS_PUBLIC_ATTR_BASE + 606L)  /* (ViInt32)  */
#define IVIFGEN_ATTR_DATAMARKER_SOURCE_CHANNEL  (IVI_CLASS_PUBLIC_ATTR_BASE + 607L)  /* (ViString) */

    /*- IviFgenSparseMarker Extended Attributes -*/
#define IVIFGEN_ATTR_SPARSEMARKER_AMPLITUDE     (IVI_CLASS_PUBLIC_ATTR_BASE + 701L)  /* (ViReal64, Multi-Channel)  */
#define IVIFGEN_ATTR_SPARSEMARKER_COUNT         (IVI_CLASS_PUBLIC_ATTR_BASE + 702L)  /* (ViInt32,  Read-only)      */
#define IVIFGEN_ATTR_SPARSEMARKER_DELAY         (IVI_CLASS_PUBLIC_ATTR_BASE + 703L)  /* (ViReal64, Multi-Channel)  */
#define IVIFGEN_ATTR_SPARSEMARKER_DESTINATION   (IVI_CLASS_PUBLIC_ATTR_BASE + 704L)  /* (ViString, Multi-Channel)  */
#define IVIFGEN_ATTR_SPARSEMARKER_POLARITY      (IVI_CLASS_PUBLIC_ATTR_BASE + 705L)  /* (ViInt32,  Multi-Channel)  */
#define IVIFGEN_ATTR_SPARSEMARKER_WFMHANDLE     (IVI_CLASS_PUBLIC_ATTR_BASE + 706L)  /* (ViInt32,  Multi-Channel)  */

/* user-defined attribute */
#define IVIFGEN_ATTR_TESTATTR                   (IVI_SPECIFIC_PRIVATE_ATTR_BASE + 103L)
#define IVIFGEN_ATTR_RUN_MODE                   (IVI_SPECIFIC_PRIVATE_ATTR_BASE+10)   /* ViInt32 */
#define IVIFGEN_ATTR_INSTRUMENT_RUN             (IVI_SPECIFIC_PRIVATE_ATTR_BASE+11)   /* ViBoolean */
#define IVIFGEN_ATTR_INSTRUMENT_STOP             (IVI_SPECIFIC_PRIVATE_ATTR_BASE+12)   /* ViBoolean */
/******************************************************************************
 *------------------- IviFgen Class Attribute Value Defines ------------------*
 ******************************************************************************/
 /////////////////
/*- Defined valued for attribute IVIFGEN_ATTR_OUTPUT_MODE -*/
#define IVIFGEN_VAL_OUTPUT_FUNC                         (0L)
#define IVIFGEN_VAL_OUTPUT_ARB                          (1L)
#define IVIFGEN_VAL_OUTPUT_SEQ                          (2L)

#define IVIFGEN_VAL_OUT_MODE_CLASS_EXT_BASE             (500L)
#define IVIFGEN_VAL_OUT_MODE_SPECIFIC_EXT_BASE          (1000L)
 /*- Defined valued for attribute IVIFGEN_ATTR_OPERATION_MODE -*/
#define IVIFGEN_VAL_OPERATE_CONTINUOUS                  (0L)
#define IVIFGEN_VAL_OPERATE_BURST                       (1L)

#define IVIFGEN_VAL_OP_MODE_CLASS_EXT_BASE              (500L)
#define IVIFGEN_VAL_OP_MODE_SPECIFIC_EXT_BASE           (1000L)
/*- Defined values for attribute IVIFGEN_ATTR_REF_CLOCK_SOURCE -*/
#define IVIFGEN_VAL_REF_CLOCK_INTERNAL                  (0L)
#define IVIFGEN_VAL_REF_CLOCK_EXTERNAL                  (1L)
#define IVIFGEN_VAL_REF_CLOCK_RTSI_CLOCK                (101L)

#define IVIFGEN_VAL_CLK_SRC_CLASS_EXT_BASE              (500L)
#define IVIFGEN_VAL_CLK_SRC_SPECIFIC_EXT_BASE           (1000L)

/*- Defined values for attribute IVIFGEN_ATTR_FUNC_WAVEFORM -*/
#define IVIFGEN_VAL_WFM_SINE                            (1L)
#define IVIFGEN_VAL_WFM_SQUARE                          (2L)
#define IVIFGEN_VAL_WFM_TRIANGLE                        (3L)
#define IVIFGEN_VAL_WFM_RAMP_UP                         (4L)
#define IVIFGEN_VAL_WFM_RAMP_DOWN                       (5L)
#define IVIFGEN_VAL_WFM_DC                              (6L)

#define IVIFGEN_VAL_WFM_CLASS_EXT_BASE                  (500L)
#define IVIFGEN_VAL_WFM_SPECIFIC_EXT_BASE               (1000L)

    /*- Defined values for attribute IVIFGEN_ATTR_TRIGGER_SOURCE -*/
#define IVIFGEN_VAL_EXTERNAL                            (1L)
#define IVIFGEN_VAL_SOFTWARE_TRIG                       (2L)
#define IVIFGEN_VAL_INTERNAL_TRIGGER                    (3L)
#define IVIFGEN_VAL_TTL0                                (111L)
#define IVIFGEN_VAL_TTL1                                (112L)
#define IVIFGEN_VAL_TTL2                                (113L)
#define IVIFGEN_VAL_TTL3                                (114L)
#define IVIFGEN_VAL_TTL4                                (115L)
#define IVIFGEN_VAL_TTL5                                (116L)
#define IVIFGEN_VAL_TTL6                                (117L)
#define IVIFGEN_VAL_TTL7                                (118L)
#define IVIFGEN_VAL_ECL0                                (119L)
#define IVIFGEN_VAL_ECL1                                (120L)
#define IVIFGEN_VAL_PXI_STAR                            (131L)
#define IVIFGEN_VAL_RTSI_0                              (141L)
#define IVIFGEN_VAL_RTSI_1                              (142L)
#define IVIFGEN_VAL_RTSI_2                              (143L)
#define IVIFGEN_VAL_RTSI_3                              (144L)
#define IVIFGEN_VAL_RTSI_4                              (145L)
#define IVIFGEN_VAL_RTSI_5                              (146L)
#define IVIFGEN_VAL_RTSI_6                              (147L)

#define IVIFGEN_VAL_TRIG_SRC_CLASS_EXT_BASE             (500L)
#define IVIFGEN_VAL_TRIG_SRC_SPECIFIC_EXT_BASE          (1000L)

  /*- Defined values for attribute IVIFGEN_ATTR_START_TRIGGER_SOURCE -*/
  /*- Defined values for attribute IVIFGEN_ATTR_STOP_TRIGGER_SOURCE -*/
  /*- Defined values for attribute IVIFGEN_ATTR_HOLD_TRIGGER_SOURCE -*/
  /*- Defined values for attribute IVIFGEN_ATTR_RESUME_TRIGGER_SOURCE -*/
  /*- Defined values for attribute IVIFGEN_ATTR_ADVANCE_TRIGGER_SOURCE -*/
  /*- Defined values for attribute IVIFGEN_ATTR_RESUME_TRIGGER_SOURCE -*/
  /*- Defined values for attribute IVIFGEN_ATTR_DATA_MARKER_DESTINATION -*/
  /*- Defined values for attribute IVIFGEN_ATTR_SPARSE_MARKER_DESTINATION -*/
#define IVIFGEN_VAL_TRIGGER_SOURCE_NONE                 ""
#define IVIFGEN_VAL_TRIGGER_SOURCE_IMMEDIATE            "Immediate"
#define IVIFGEN_VAL_TRIGGER_SOURCE_EXTERNAL             "External"
#define IVIFGEN_VAL_TRIGGER_SOURCE_INTERNAL             "Internal"
#define IVIFGEN_VAL_TRIGGER_SOURCE_SOFTWARE             "Software"
#define IVIFGEN_VAL_TRIGGER_SOURCE_LAN0                 "LAN0"
#define IVIFGEN_VAL_TRIGGER_SOURCE_LAN1                 "LAN1"
#define IVIFGEN_VAL_TRIGGER_SOURCE_LAN2                 "LAN2"
#define IVIFGEN_VAL_TRIGGER_SOURCE_LAN3                 "LAN3"
#define IVIFGEN_VAL_TRIGGER_SOURCE_LAN4                 "LAN4"
#define IVIFGEN_VAL_TRIGGER_SOURCE_LAN5                 "LAN5"
#define IVIFGEN_VAL_TRIGGER_SOURCE_LAN6                 "LAN6"
#define IVIFGEN_VAL_TRIGGER_SOURCE_LAN7                 "LAN7"
#define IVIFGEN_VAL_TRIGGER_SOURCE_LXI0                 "LXI0"
#define IVIFGEN_VAL_TRIGGER_SOURCE_LXI1                 "LXI1"
#define IVIFGEN_VAL_TRIGGER_SOURCE_LXI2                 "LXI2"
#define IVIFGEN_VAL_TRIGGER_SOURCE_LXI3                 "LXI3"
#define IVIFGEN_VAL_TRIGGER_SOURCE_LXI4                 "LXI4"
#define IVIFGEN_VAL_TRIGGER_SOURCE_LXI5                 "LXI5"
#define IVIFGEN_VAL_TRIGGER_SOURCE_LXI6                 "LXI6"
#define IVIFGEN_VAL_TRIGGER_SOURCE_LXI7                 "LXI7"
#define IVIFGEN_VAL_TRIGGER_SOURCE_TTL0                 "TTL0"
#define IVIFGEN_VAL_TRIGGER_SOURCE_TTL1                 "TTL1"
#define IVIFGEN_VAL_TRIGGER_SOURCE_TTL2                 "TTL2"
#define IVIFGEN_VAL_TRIGGER_SOURCE_TTL3                 "TTL3"
#define IVIFGEN_VAL_TRIGGER_SOURCE_TTL4                 "TTL4"
#define IVIFGEN_VAL_TRIGGER_SOURCE_TTL5                 "TTL5"
#define IVIFGEN_VAL_TRIGGER_SOURCE_TTL6                 "TTL6"
#define IVIFGEN_VAL_TRIGGER_SOURCE_TTL7                 "TTL7"
#define IVIFGEN_VAL_TRIGGER_SOURCE_PXI_STAR             "PXI_STAR"
#define IVIFGEN_VAL_TRIGGER_SOURCE_PXI_TRIG0            "PXI_TRIG0"
#define IVIFGEN_VAL_TRIGGER_SOURCE_PXI_TRIG1            "PXI_TRIG1"
#define IVIFGEN_VAL_TRIGGER_SOURCE_PXI_TRIG2            "PXI_TRIG2"
#define IVIFGEN_VAL_TRIGGER_SOURCE_PXI_TRIG3            "PXI_TRIG3"
#define IVIFGEN_VAL_TRIGGER_SOURCE_PXI_TRIG4            "PXI_TRIG4"
#define IVIFGEN_VAL_TRIGGER_SOURCE_PXI_TRIG5            "PXI_TRIG5"
#define IVIFGEN_VAL_TRIGGER_SOURCE_PXI_TRIG6            "PXI_TRIG6"
#define IVIFGEN_VAL_TRIGGER_SOURCE_PXI_TRIG7            "PXI_TRIG7"
#define IVIFGEN_VAL_TRIGGER_SOURCE_PXIE_DSTARA          "PXIe_DSTARA"
#define IVIFGEN_VAL_TRIGGER_SOURCE_PXIE_DSTARB          "PXIe_DSTARB"
#define IVIFGEN_VAL_TRIGGER_SOURCE_PXIE_DSTARC          "PXIe_DSTARC"
#define IVIFGEN_VAL_TRIGGER_SOURCE_RTSI0                "RTSI0"
#define IVIFGEN_VAL_TRIGGER_SOURCE_RTSI1                "RTSI1"
#define IVIFGEN_VAL_TRIGGER_SOURCE_RTSI2                "RTSI2"
#define IVIFGEN_VAL_TRIGGER_SOURCE_RTSI3                "RTSI3"
#define IVIFGEN_VAL_TRIGGER_SOURCE_RTSI4                "RTSI4"
#define IVIFGEN_VAL_TRIGGER_SOURCE_RTSI5                "RTSI5"
#define IVIFGEN_VAL_TRIGGER_SOURCE_RTSI6                "RTSI6"

  /*- Defined values for attribute IVIFGEN_ATTR_SAMPLE_CLOCK_SOURCE -*/
#define IVIFGEN_VAL_SAMPLE_CLOCK_SOURCE_INTERNAL        (0L)
#define IVIFGEN_VAL_SAMPLE_CLOCK_SOURCE_EXTERNAL        (1L)

  /*- Defined values for attribute IVIFGEN_ATTR_DATAMARKER_POLARITY -*/
#define IVIFGEN_VAL_MARKER_POLARITY_ACTIVE_HIGH         (0L)
#define IVIFGEN_VAL_MARKER_POLARITY_ACTIVE_LOW          (1L)

  /*- Defined values for attribute IVIFGEN_ATTR_AM_SOURCE -*/
#define IVIFGEN_VAL_AM_INTERNAL                         (0L)
#define IVIFGEN_VAL_AM_EXTERNAL                         (1L)

#define IVIFGEN_VAL_AM_SOURCE_CLASS_EXT_BASE            (500L)
#define IVIFGEN_VAL_AM_SOURCE_SPECIFIC_EXT_BASE         (1000L)

  /*- Defined values for attribute IVIFGEN_ATTR_AM_INTERNAL_WAVEFORM -*/
#define IVIFGEN_VAL_AM_INTERNAL_SINE                    (1L)
#define IVIFGEN_VAL_AM_INTERNAL_SQUARE                  (2L)
#define IVIFGEN_VAL_AM_INTERNAL_TRIANGLE                (3L)
#define IVIFGEN_VAL_AM_INTERNAL_RAMP_UP                 (4L)
#define IVIFGEN_VAL_AM_INTERNAL_RAMP_DOWN               (5L)

#define IVIFGEN_VAL_AM_INTERNAL_WFM_CLASS_EXT_BASE      (500L)
#define IVIFGEN_VAL_AM_INTERNAL_WFM_SPECIFIC_EXT_BASE   (1000L)

  /*- Defined values for attribute IVIFGEN_ATTR_FM_SOURCE -*/
#define IVIFGEN_VAL_FM_INTERNAL                         (0L)
#define IVIFGEN_VAL_FM_EXTERNAL                         (1L)

#define IVIFGEN_VAL_FM_SOURCE_CLASS_EXT_BASE            (500L)
#define IVIFGEN_VAL_FM_SOURCE_SPECIFIC_EXT_BASE         (1000L)

  /*- Defined values for attribute IVIFGEN_ATTR_FM_INTERNAL_WAVEFORM -*/
#define IVIFGEN_VAL_FM_INTERNAL_SINE                    (1L)
#define IVIFGEN_VAL_FM_INTERNAL_SQUARE                  (2L)
#define IVIFGEN_VAL_FM_INTERNAL_TRIANGLE                (3L)
#define IVIFGEN_VAL_FM_INTERNAL_RAMP_UP                 (4L)
#define IVIFGEN_VAL_FM_INTERNAL_RAMP_DOWN               (5L)

#define IVIFGEN_VAL_FM_INTERNAL_WFM_CLASS_EXT_BASE      (500L)
#define IVIFGEN_VAL_FM_INTERNAL_WFM_SPECIFIC_EXT_BASE   (1000L)

  /*- Defined values for attribute IVIFGEN_ATTR_BINARY_ALIGNMENT -*/
#define IVIFGEN_VAL_BINARY_ALIGNMENT_LEFT               (0L)
#define IVIFGEN_VAL_BINARY_ALIGNMENT_RIGHT              (1L)

#define IVIFGEN_VAL_BINARY_ALIGNMENT_CLASS_EXT_BASE     (500L)
#define IVIFGEN_VAL_BINARY_ALIGNMENT_SPECIFIC_EXT_BASE  (1000L)

  /*- Defined values for attribute IVIFGEN_ATTR_OUTPUT_TERMINAL_CONFIGURATION -*/
#define IVIFGEN_VAL_TERMINAL_CONFIGURATION_SINGLE_ENDED         (0L)
#define IVIFGEN_VAL_TERMINAL_CONFIGURATION_DIFFERENTIAL         (1L)

#define IVIFGEN_VAL_TERMINAL_CONFIGURATION_CLASS_EXT_BASE       (500L)
#define IVIFGEN_VAL_TERMINAL_CONFIGURATION_SPECIFIC_EXT_BASE    (1000L)

  /*- Defined values for attribute IVIFGEN_ATTR_START_TRIGGER_SLOPE -*/
  /*- Defined values for attribute IVIFGEN_ATTR_STOP_TRIGGER_SLOPE -*/
  /*- Defined values for attribute IVIFGEN_ATTR_HOLD_TRIGGER_SLOPE -*/
  /*- Defined values for attribute IVIFGEN_ATTR_RESUME_TRIGGER_SLOPE -*/
  /*- Defined values for attribute IVIFGEN_ATTR_ADVANCE_TRIGGER_SLOPE -*/
#define IVIFGEN_VAL_TRIGGER_POSITIVE                    (0L)
#define IVIFGEN_VAL_TRIGGER_NEGATIVE                    (1L)
#define IVIFGEN_VAL_TRIGGER_EITHER                      (2L)

#define IVIFGEN_VAL_TRIGGER_CLASS_EXT_BASE              (500L)
#define IVIFGEN_VAL_TRIGGER_SPECIFIC_EXT_BASE           (1000L)

   /*- Defined values for waveformHandle parameter for function IviFgen_ClearArbWaveform -*/
#define IVIFGEN_VAL_ALL_WAVEFORMS                       (-1L)

   /*- Defined values for sequenceHandle parameter for function IviFgen_ClearArbSequence -*/
#define IVIFGEN_VAL_ALL_SEQUENCES                       (-1L)

 /******************************************************************************
 *----------- IviFgen Class Instrument Driver Function Declarations ----------*
 ******************************************************************************/
 /*- Required VXIplug&play Functions -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_init (ViRsrc logicalName,
                                           ViBoolean IDQuery,
                                           ViBoolean resetDevice,
                                           ViSession *vi);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_close (ViSession vi);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_reset (ViSession vi);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_self_test (ViSession vi,
                                                ViInt16* selfTestResult,
                                                ViChar selfTestMessage[]);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_error_query (ViSession vi,
                                                  ViInt32 *errorCode,
                                                  ViChar errorMessage[]);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_error_message (ViSession vi,
                                                    ViStatus statusCode,
                                                    ViChar message[]);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_revision_query (ViSession vi,
                                                     ViChar driverRev[],
                                                     ViChar instrRev[]);
 /*- Utility Functions -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_InvalidateAllAttributes (ViSession vi);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_ResetWithDefaults (ViSession vi);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_Disable (ViSession vi);

 /*- Required IVI Functions -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_InitWithOptions (ViRsrc logicalName,
                                                      ViBoolean IDQuery,
                                                      ViBoolean resetDevice,
                                                      ViConstString optionString,
                                                      ViSession *vi);
   /*- Set, Get, and Check Attribute Functions -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_GetAttributeViInt32 (ViSession vi,
                                                          ViConstString channelName,
                                                          ViAttr attributeId,
                                                          ViInt32 *value);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_SetAttributeViInt32 (ViSession vi,
                                                          ViConstString channelName,
                                                          ViAttr attributeId,
                                                          ViInt32 value);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_CheckAttributeViInt32 (ViSession vi,
                                                            ViConstString channelName,
                                                            ViAttr attributeId,
                                                            ViInt32 value);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_GetAttributeViString (ViSession vi,
                                                           ViConstString channelName,
                                                           ViAttr attributeId,
                                                           ViInt32 bufferSize,
                                                           ViChar value[]);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_SetAttributeViString (ViSession vi,
                                                           ViConstString channelName,
                                                           ViAttr attributeId,
                                                           ViConstString value);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_CheckAttributeViString (ViSession vi,
                                                             ViConstString channelName,
                                                             ViAttr attributeId,
                                                             ViConstString value);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_GetAttributeViBoolean (ViSession vi,
                                                            ViConstString channelName,
                                                            ViAttr attributeId,
                                                            ViBoolean *value);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_SetAttributeViBoolean (ViSession vi,
                                                            ViConstString channelName,
                                                            ViAttr attributeId,
                                                            ViBoolean value);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_CheckAttributeViBoolean (ViSession vi,
                                                              ViConstString channelName,
                                                              ViAttr attributeId,
                                                              ViBoolean value);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_GetAttributeViSession (ViSession vi,
                                                            ViConstString channelName,
                                                            ViAttr attributeId,
                                                            ViSession *value);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_SetAttributeViSession (ViSession vi,
                                                            ViConstString channelName,
                                                            ViAttr attributeId,
                                                            ViSession value);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_CheckAttributeViSession (ViSession vi,
                                                              ViConstString channelName,
                                                              ViAttr attributeId,
                                                              ViSession value);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_GetAttributeViReal64 (ViSession vi,
                                                           ViConstString channelName,
                                                           ViAttr attributeId,
                                                           ViReal64 *value);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_SetAttributeViReal64 (ViSession vi,
                                                           ViConstString channelName,
                                                           ViAttr attributeId,
                                                           ViReal64 value);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_CheckAttributeViReal64 (ViSession vi,
                                                             ViConstString channelName,
                                                             ViAttr attributeId,
                                                             ViReal64 value);
/*- Lock and Unlock Functions -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_LockSession (ViSession vi,
                                                  ViBoolean *callerHasLock);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_UnlockSession (ViSession vi,
                                                    ViBoolean *callerHasLock);
/*- IviFgenBase Capability Group  -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureOutputMode (ViSession vi,
                                                          ViInt32 outputMode);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureOperationMode (ViSession vi,
                                                             ViConstString channelName,
                                                             ViInt32 operationMode);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureRefClockSource (ViSession vi,
                                                              ViInt32 refClockSource);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureOutputImpedance (ViSession vi,
                                                               ViConstString channelName,
                                                               ViReal64 outputImpedance);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureOutputEnabled (ViSession vi,
                                                             ViConstString channelName,
                                                             ViBoolean enabled);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_GetChannelName (ViSession vi,
                                                     ViInt32 index,
                                                     ViInt32 bufferSize,
                                                     ViChar name[]);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_InitiateGeneration (ViSession vi);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_AbortGeneration (ViSession vi);
/*- IviFgenStdFunc Extension Group -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureStandardWaveform (ViSession vi,
                                                                ViConstString channelName,
                                                                ViInt32 waveform,
                                                                ViReal64 amplitude,
                                                                ViReal64 dcOffset,
                                                                ViReal64 frequency,
                                                                ViReal64 startPhase);
/*- IviFgenArbWfm Extension Group -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_QueryArbWfmCapabilities (ViSession vi,
                                                              ViInt32 *maxNumWfms,
                                                              ViInt32 *wfmQuantum,
                                                              ViInt32 *minWfmSize,
                                                              ViInt32 *maxWfmSize);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_CreateArbWaveform (ViSession vi,
                                                        ViInt32 wfmSize,
                                                        ViReal64 wfmData[],
                                                        ViInt32 *wfmHandle);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureSampleRate (ViSession vi,
                                                          ViReal64 sampleRate);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureArbWaveform (ViSession vi,
                                                           ViConstString channelName,
                                                           ViInt32 wfmHandle,
                                                           ViReal64 arbGain,
                                                           ViReal64 arbOffset);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_ClearArbWaveform (ViSession vi,
                                                       ViInt32 wfmHandle);
  /*- IviFgenArbFrequency Extension Group -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureArbFrequency (ViSession vi,
                                                            ViConstString channelName,
                                                            ViReal64 frequency);
 /*- IviFgenArbSeq Extension Group -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_QueryArbSeqCapabilities (ViSession vi,
                                                              ViInt32 *maxNumSeqs,
                                                              ViInt32 *minSeqLength,
                                                              ViInt32 *maxSeqLength,
                                                              ViInt32 *maxLoopCount);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_CreateArbSequence (ViSession vi,
                                                        ViInt32 seqLength,
                                                        ViInt32 wfmHandle[],
                                                        ViInt32 wfmLoopCount[],
                                                        ViInt32 *seqHandle);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureArbSequence (ViSession vi,
                                                           ViConstString channelName,
                                                           ViInt32 seqHandle,
                                                           ViReal64 arbGain,
                                                           ViReal64 arbOffset);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_ClearArbSequence (ViSession vi,
                                                       ViInt32 seqHandle);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_ClearArbMemory (ViSession vi);

/*- IviFgenTrigger Extension Group -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureTriggerSource (ViSession vi,
                                                             ViConstString channelName,
                                                             ViInt32 trigSource);

/*- IviFgenStartTrigger Extension Group -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureStartTrigger (ViSession vi,
                                                            ViConstString channelName,
                                                            ViConstString source,
                                                            ViInt32 slope);

/*- IviFgenStopTrigger Extension Group -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureStopTrigger (ViSession vi,
                                                           ViConstString channelName,
                                                           ViConstString source,
                                                           ViInt32 slope);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_SendSoftwareStopTrigger (ViSession vi);

/*- IviFgenHoldTrigger Extension Group -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureHoldTrigger (ViSession vi,
                                                           ViConstString channelName,
                                                           ViConstString source,
                                                           ViInt32 slope);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_SendSoftwareHoldTrigger (ViSession vi);

/*- IviFgenResumeTrigger Extension Group -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureResumeTrigger (ViSession vi,
                                                             ViConstString channelName,
                                                             ViConstString source,
                                                             ViInt32 slope);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_SendSoftwareResumeTrigger (ViSession vi);

/*- IviFgenAdvanceTrigger Extension Group -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureAdvanceTrigger (ViSession vi,
                                                              ViConstString channelName,
                                                              ViConstString source,
                                                              ViInt32 slope);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_SendSoftwareAdvanceTrigger (ViSession vi);

/*- IviFgenInternalTrigger Extension Group -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureInternalTriggerRate (ViSession vi,
                                                                   ViReal64 rate);

/*- IviFgenSoftwareTrigger Extension Group -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_SendSoftwareTrigger (ViSession vi);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureOutputTriggerSlope (ViSession vi,
                                                                  ViInt32 slope);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureTriggerSlope (ViSession vi,
                                                            ViConstString channelName,
                                                            ViInt32 slope);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureTriggerDelay (ViSession vi,
                                                            ViConstString channelName,
                                                            ViReal64 delay);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureTriggerEnabled (ViSession vi,
                                                              ViBoolean outputTrig);
/*- IviFgenBurst Extension Group -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureBurstCount (ViSession vi,
                                                          ViConstString channelName,
                                                          ViInt32 count);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureBurstPhase (ViSession vi,
                                                          ViConstString channelName,
                                                          ViReal64 phase);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureBurstInternal (ViSession vi,
                                                             ViConstString channelName,
                                                             ViReal64 burstRate);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureBurstSource (ViSession vi,
                                                           ViConstString channelName,
                                                           ViInt32 source);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureBurstEnabled (ViSession vi,
                                                            ViConstString channelName,
                                                            ViBoolean enabled);

/*- IviFgenModulateAM Extension Group -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureAMEnabled (ViSession vi,
                                                         ViConstString channelName,
                                                         ViBoolean enabled);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureAMSource (ViSession vi,
                                                        ViConstString channelName,
                                                        ViInt32 source);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureAMInternal (ViSession vi,
                                                          ViReal64 amdepth,
                                                          ViInt32 amWaveform,
                                                          ViReal64 amFrequency);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureAMDepth (ViSession vi,
                                                       ViConstString channelName,
                                                       ViReal64 depth);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureAMWaveform (ViSession vi,
                                                          ViConstString channelName,
                                                          ViInt32 waveform);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureAMFrequency (ViSession vi,
                                                           ViConstString channelName,
                                                           ViReal64 frequency);
 /*- IviFgenModulateFM Extension Group -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureFMEnabled (ViSession vi,
                                                         ViConstString channelName,
                                                         ViBoolean enabled);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureFMSource (ViSession vi,
                                                        ViConstString channelName,
                                                        ViInt32 source);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureFMInternal (ViSession vi,
                                                          ViReal64 fmdeviation,
                                                          ViInt32 fmWaveform,
                                                          ViReal64 fmFrequency);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureFMDeviation(ViSession vi,
                                                          ViConstString channelName,
                                                          ViReal64 deviation);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureFMWaveform(ViSession vi,
                                                         ViConstString channelName,
                                                         ViInt32 waveform);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureFMFrequency(ViSession vi,
                                                          ViConstString channelName,
                                                          ViReal64 frequency);
/*configure PM function single parameter*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigurePMEnabled (ViSession vi,
                                                         ViConstString channelName,
                                                         ViBoolean enabled);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigurePMSource (ViSession vi,
                                                        ViConstString channelName,
                                                        ViInt32 source);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigurePMInternal(ViSession vi,
                                                         ViConstString channelName,
                                                         ViReal64 pmDeviation,
                                                         ViInt32 pmWaveform,
                                                         ViReal64 pmFrequency);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigurePMDeviation(ViSession vi,
                                                          ViConstString channelName,
                                                          ViReal64 deviation);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigurePMWaveform(ViSession vi,
                                                         ViConstString channelName,
                                                         ViInt32 waveform);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigurePMFrequency(ViSession vi,
                                                          ViConstString channelName,
                                                          ViReal64 frequency);
 /*FSK function*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureFSKEnabled (ViSession vi,
                                                          ViConstString channelName,
                                                          ViBoolean enabled);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureFSKSource (ViSession vi,
                                                         ViConstString channelName,
                                                         ViInt32 source);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureFSKHopFrequency (ViSession vi,
                                                               ViReal64 hopFrequency);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureFSKInternal (ViSession vi,
                                                           ViConstString channelName,
                                                           ViReal64 fskRate);
 /*PSK function*/
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigurePSKEnabled (ViSession vi,
                                                           ViConstString channelName,
                                                           ViBoolean enabled);
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigurePSKSource (ViSession vi,
                                                          ViConstString channelName,
                                                          ViInt32 source);
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigurePSKHopPhase(ViSession vi,
                                                           ViReal64 hop_phase);
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigurePSKInternal (ViSession vi,
                                                            ViReal64 pskRate);
   /*Sweep function*/
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureSweepEnabled (ViSession vi,
                                                             ViConstString channelName,
                                                             ViBoolean enabled);
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureSweepMode (ViSession vi,
                                                          ViConstString channelName,
                                                          ViInt32 sweepMode);
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureSweep (ViSession vi,
                                                      ViInt32 sweepSpacing,
                                                      ViReal64 startFreq,
                                                      ViReal64 stopFreq,
                                                      ViReal64 sweepTime);
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureSweepSource (ViSession vi,
                                                            ViConstString channelName,
                                                            ViInt32 source);
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureSweepBurstCount (ViSession vi,
                                                                ViConstString channelName,
                                                                ViReal64 sweepTime,
                                                                ViInt32 burstCount);
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureSweepStartFreq(ViSession vi,
                                                              ViConstString channelName,
                                                              ViReal64 start_freq);
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureSweepStopFreq(ViSession vi,
                                                             ViConstString channelName,
                                                             ViReal64 stop_freq);
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureSweepSpacing(ViSession vi,
                                                            ViConstString channelName,
                                                            ViInt32 spacing);
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureSweepTime(ViSession vi,
                                                         ViConstString channelName,
                                                         ViReal64 time);
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_SweepMarkerEnabled (ViSession vi,
                                                          ViConstString channelName,
                                                          ViBoolean sweepMark);
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureSweepMarkerFreq (ViSession vi,
                                                                ViConstString channelName,
                                                                ViReal64 markerFreq);
/*Pulse Width Modulation*/
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigurePWMEnabled (ViSession vi,
                                                           ViConstString channelName,
                                                           ViBoolean PWMEnabled);
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigurePWMSource (ViSession vi,
                                                          ViConstString channelName,
                                                          ViInt32 source);
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigurePWMInternal (ViSession vi,
                                                            ViReal64 pwmDeviation,
                                                            ViInt32	pwmWaveform,
                                                            ViReal64 pwmFrequency,
                                                            ViReal64 pwmDutyCycleDev);
/*configure stardard waveform single parameter*/
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureWfmFrequency(ViSession vi,
                                                            ViConstString	channelName,
                                                            ViReal64 frequency);
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureWfmPhase(ViSession vi,
                                                        ViConstString channelName,
                                                        ViReal64 startPhase);
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureFuncWaveform(ViSession vi,
                                                            ViConstString	channelName,
                                                            ViInt32 waveform);
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureSquareDutyCycle(ViSession vi,
                                                               ViConstString channelName,
                                                               ViReal64 dutyCycle);
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureAmplitude(ViSession vi,
                                                         ViConstString	channelName,
                                                         ViReal64 amplitude);
 ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureOffset(ViSession vi,
                                                      ViConstString channelName,
                                                      ViReal64 offset);

/*- IviFgenSampleClock Extension Group -*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureSampleClock (ViSession vi,
                                                           ViInt32 source);

ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureSampleClockOutputEnabled (ViSession vi,
                                                                        ViBoolean enabled);
/*-Out of IVI function-*/
ViStatus DLL_EXPORT _VI_FUNC IviFgen_GetNextCoercionRecord (ViSession vi,
                                                            ViInt32 bufferSize,
                                                            ViChar record[]);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureSyncSignal (ViSession vi,
                                                          ViBoolean outputEnabled);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureOutputPolarity (ViSession vi,
                                                              ViConstString channelName,
                                                              ViInt32 polarity);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureVoltAutoRanging (ViSession vi,
                                                               ViInt32 voltRange);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_PhaseUnlockErrorState (ViSession vi,
                                                            ViBoolean lock);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_TestSampleRate(ViSession vi,
                                                    ViUInt32 positive_number);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureRampSymmetry (ViSession	vi,
                                                            ViConstString channelName,
                                                            ViReal64 rampSymmetry);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigurePulse (ViSession vi,
                                                     ViConstString channelName,
                                                     ViReal64 pulsePeriod,
                                                     ViReal64 pulseWidth,
                                                     ViReal64 pulseTransition);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigurePulseHold (ViSession vi,
                                                         ViInt32 hold);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigurePulseDutyCycle (ViSession vi,
                                                              ViReal64 dutyCycle);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_SetWfmRamData(ViSession vi,
                                                   ViConstString channelName,
                                                   ViUInt32 count,
                                                   ViUInt32* val);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_SetWfmRamDataTest(ViSession vi,
                                                       ViConstString channelName,
                                                       ViUInt32 count,
                                                       ViUInt32* val);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_SetModuWaveRamData(ViSession vi,
                                                        ViConstString channelName,
                                                        ViUInt32* val);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_GetWfmNameFromHandle (ViSession vi,
                                                           ViInt32 wfmHandle,
                                                           ViInt32 arraySize,
                                                           ViChar wfmName[]);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_GetWfmHandleFromName (ViSession vi,
                                                           ViConstString wfmName,
                                                           ViInt32 *wfmHandle);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_GetWfmNames (ViSession vi,
                                                  ViInt32 arraySize,
                                                  ViChar wfmNames[]);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureSyncSignalEnabled(ViSession vi,
                                                                ViBoolean output_enabled);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigureTTLLineEnabled (ViSession vi,
                                                              ViInt32 Line,
                                                              ViBoolean state);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigurePhaseRef (ViSession vi,
                                                        ViReal64 phaseReference);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ConfigurePhaseAdjust (ViSession vi,
                                                           ViReal64 phaseAdjust);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_VoltAutoRangingOnce (ViSession vi);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_SendExternalTrigger (ViSession vi);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_WriteInstrData (ViSession vi,
                                                     ViConstString writeBuffer);
ViStatus DLL_EXPORT _VI_FUNC IviFgen_ReadInstrData  (ViSession vi,
                                                     ViInt32 numBytes,
                                                     ViChar rdBuf[],
                                                     ViInt32 *bytesRead);
/******************************************************************************
 *----------------- IviFgen Class Error And Completion Codes -----------------*
 ******************************************************************************/
#define IVIFGEN_ERROR_NO_WFMS_AVAILABLE       (IVI_CLASS_ERROR_BASE + 4L)
#define IVIFGEN_ERROR_WFM_IN_USE              (IVI_CLASS_ERROR_BASE + 8L)
#define IVIFGEN_ERROR_NO_SEQS_AVAILABLE       (IVI_CLASS_ERROR_BASE + 9L)
#define IVIFGEN_ERROR_SEQ_IN_USE              (IVI_CLASS_ERROR_BASE + 13L)
#define IVIFGEN_ERROR_INVALID_WFM_CHANNEL     (IVI_CLASS_ERROR_BASE + 14L)
#define IVIFGEN_ERROR_TRIGGER_NOT_SOFTWARE    (IVI_CROSS_CLASS_ERROR_BASE + 1L)

#define IVIFGEN_ERRMSG_NO_WFMS_AVAILABLE      "The function generator's waveform memory is full."
#define IVIFGEN_ERRMSG_WFM_IN_USE             "The waveform is currently in use."
#define IVIFGEN_ERRMSG_NO_SEQS_AVAILABLE      "The function generator's sequence memory is full."
#define IVIFGEN_ERRMSG_SEQ_IN_USE             "The sequence is currently in use."
#define IVIFGEN_ERRMSG_INVALID_WFM_CHANNEL    "The waveform was created on a different channel than the one for which it is being configured."
#define IVIFGEN_ERRMSG_TRIGGER_NOT_SOFTWARE   "The trigger source is not software trigger."

#define IVIFGEN_ERROR_CODES_AND_MSGS \
        { IVIFGEN_ERROR_NO_WFMS_AVAILABLE,    IVIFGEN_ERRMSG_NO_WFMS_AVAILABLE   }, \
        { IVIFGEN_ERROR_WFM_IN_USE,           IVIFGEN_ERRMSG_WFM_IN_USE          }, \
        { IVIFGEN_ERROR_NO_SEQS_AVAILABLE,    IVIFGEN_ERRMSG_NO_SEQS_AVAILABLE   }, \
        { IVIFGEN_ERROR_SEQ_IN_USE,           IVIFGEN_ERRMSG_SEQ_IN_USE          }, \
        { IVIFGEN_ERROR_INVALID_WFM_CHANNEL,  IVIFGEN_ERRMSG_INVALID_WFM_CHANNEL }, \
        { IVIFGEN_ERROR_TRIGGER_NOT_SOFTWARE, IVIFGEN_ERRMSG_TRIGGER_NOT_SOFTWARE}

#ifdef __cplusplus
}
#endif
#endif
