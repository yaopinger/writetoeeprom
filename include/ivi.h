#ifndef _IVI_H_
#define _IVI_H_
#include "visa.h"
#include "vpptype.h"

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

#ifdef __cplusplus
extern "C"{
#endif

/*****************************************************************************/
/*= Typedefs and related constants for the range tables             ======== */
/*****************************************************************************/
/* Defined values for the type of IviRangeTable */
#define IVI_VAL_DISCRETE            0       /* Discrete set - discreteOrMinValue, and cmdString (or cmdValue) fields used */
#define IVI_VAL_RANGED              1       /* Ranged value - discreteOrMinValue, maxValue, and cmdString (or cmdValue) fields used */
#define IVI_VAL_COERCED             2       /* Coerced value - discreteOrMinValue, maxValue, coercedValue, and cmdString (or cmdValue) fields used */

typedef struct      /* IviRangeTable contains an array of IviRangeTableEntry structures */
{
    ViReal64     discreteOrMinValue;
    ViReal64     maxValue;
    ViReal64     coercedValue;
    ViString     cmdString;          /* optional */
    ViInt32      cmdValue;           /* optional */
} IviRangeTableEntry;
typedef struct
    {
    ViInt32                     type;
    ViBoolean                   hasMin;
    ViBoolean                   hasMax;
    /* The hasMin and hasMax fields are used by the                      */
    /* Ivi_GetAttrMinMaxViInt32 and Ivi_GetAttrMinMaxViReal64 functions  */
    /* to determine whether they can calculate the minimum and maximum   */
    /* values that the instrument implements for an attribute.           */
    /* They are NOT used to indicate the inclusion or exclusion of the   */
    /* boundary value in the range                                       */
    ViString                    customInfo;
    void*                       rangeValues;
    /* the end of rangeValues[] is marked by the entry  */
    /* IVI_RANGE_TABLE_LAST_ENTRY                       */
    /*                                                  */
    } IviRangeTable;

typedef IviRangeTable*  IviRangeTablePtr;
typedef void* IviConfigStoreHandle;

#define IVI_RANGE_TABLE_END_STRING      ((ViString)(-1))  /* The value for the command string of the last entry in an IviRangeTable */
#define IVI_RANGE_TABLE_LAST_ENTRY      VI_NULL, VI_NULL, VI_NULL, IVI_RANGE_TABLE_END_STRING, VI_NULL  /* Marks the last entry in an IviRangeTable */

/*****************************************************************************/
/*= Typedef and related constants for the IVI attribute flags.     ========= */
/*= The flags determine how the attributes operate.                ========= */
/*****************************************************************************/
typedef ViInt32 IviAttrFlags;

#define IVI_VAL_NOT_SUPPORTED                (1L << 0)  /* attribute automatically returns IVI_ERROR_ATTRIBUTE_NOT_SUPPORTED when Set/Get/Checked/Invalidated */
#define IVI_VAL_NOT_READABLE                 (1L << 1)  /* attribute cannot be Got */
#define IVI_VAL_NOT_WRITABLE                 (1L << 2)  /* attribute cannot be Set */
#define IVI_VAL_NOT_USER_READABLE            (1L << 3)  /* attribute cannot be Got by end-user */
#define IVI_VAL_NOT_USER_WRITABLE            (1L << 4)  /* attribute cannot be Set by end-user */
#define IVI_VAL_NEVER_CACHE                  (1L << 5)  /* always write/read to set/get attribute, i.e., never use a cached value, regardless of the state of IVI_ATTR_CACHE */
#define IVI_VAL_ALWAYS_CACHE                 (1L << 6)  /* specifies to always cache the value, regardless of the state of IVI_ATTR_CACHE */
#define IVI_VAL_NO_DEFERRED_UPDATE           (1L << 7)  /* always write the attribute immediately when it is set */
#define IVI_VAL_DONT_RETURN_DEFERRED_VALUE   (1L << 8)  /* don't return a set value that hasn't been updated to the instrument, return the instrument's current value */
#define IVI_VAL_FLUSH_ON_WRITE               (1L << 9)  /* send IVI_MSG_FLUSH to the BufferIOCallback (which by default calls viFlush) after the write callback */
#define IVI_VAL_MULTI_CHANNEL                (1L << 10) /* specified when the attribute is added.  If set, the attribute has a separate value for each channel */
#define IVI_VAL_COERCEABLE_ONLY_BY_INSTR     (1L << 11) /* specifies that the instrument coerces the attribue value in a way that the driver cannot anticipate in software.  Do NOT use this flag UNLESS ABSOLUTELY NECESSARY !!! */
#define IVI_VAL_WAIT_FOR_OPC_BEFORE_READS    (1L << 12) /* specifies to wait for operation complete before reads */
#define IVI_VAL_WAIT_FOR_OPC_AFTER_WRITES    (1L << 13) /* specifies to wait for operation complete after writes */
#define IVI_VAL_USE_CALLBACKS_FOR_SIMULATION (1L << 14) /* specifies to call the read and write callbacks even in simulation mode */
#define IVI_VAL_DONT_CHECK_STATUS            (1L << 15) /* specifies to not call the checkStatus callback even when IVI_ATTR_QUERY_INSTR_STATUS is VI_TRUE */

#define IVI_VAL_HIDDEN     (IVI_VAL_NOT_USER_READABLE | IVI_VAL_NOT_USER_WRITABLE)

/*****************************************************************************/
/*= Constants for optionFlags argument to Set/Check/GetAttribute functions ==*/
/*****************************************************************************/
#define IVI_VAL_DIRECT_USER_CALL            (1<<0)  /* applies to Set/Check/Get;  if 1, then:  the IVI_VAL_NOT_USER_READABLE/WRITEABLE flags can apply,                                                   */
                                                    /* and the engine automatically checks status on a Set if IVI_ATTR_QUERY_INSTR_STATUS is TRUE and the attribute's IVI_VAL_DONT_CHECK_STATUS flag is 0 */
#define IVI_VAL_SET_CACHE_ONLY              (1<<1)  /* applies to Set only;  if 1, then only the cached value is set and no instrument I/O is performed;                                               */
                                                    /* use this when you set multiple instrument attributes with one I/O command;  if you call Set calls with this flag, the update is never deferred */
#define IVI_VAL_DONT_MARK_AS_SET_BY_USER    (1<<2)  /* applies to Set only;  if 0 (which is the typical case), then Ivi_AttributeWasSetByUser will return TRUE;  important for interchangeability checking  */

/*****************************************************************************/
/*= Error constants                                                ========= */
/*****************************************************************************/
#define IVI_STATUS_CODE_BASE                    0x3FFA0000L

#define IVI_WARN_BASE                           (IVI_STATUS_CODE_BASE)
#define IVI_CROSS_CLASS_WARN_BASE               (IVI_WARN_BASE + 0x1000)
#define IVI_CLASS_WARN_BASE                     (IVI_WARN_BASE + 0x2000)
#define IVI_SPECIFIC_WARN_BASE                  (IVI_WARN_BASE + 0x4000)
#define IVI_MAX_SPECIFIC_WARN_CODE              (IVI_WARN_BASE + 0x7FFF)
#define IVI_NI_WARN_BASE                        (IVI_WARN_BASE + 0x6000)

#define IVI_ERROR_BASE                          (_VI_ERROR + IVI_STATUS_CODE_BASE)
#define IVI_CROSS_CLASS_ERROR_BASE              (IVI_ERROR_BASE + 0x1000)
#define IVI_CLASS_ERROR_BASE                    (IVI_ERROR_BASE + 0x2000)
#define IVI_SPECIFIC_ERROR_BASE                 (IVI_ERROR_BASE + 0x4000)
#define IVI_MAX_SPECIFIC_ERROR_CODE             (IVI_ERROR_BASE + 0x7FFF)
#define IVI_NI_ERROR_BASE                       (IVI_ERROR_BASE + 0x6000)
#define IVI_SHARED_COMPONENT_ERROR_BASE         (IVI_ERROR_BASE + 0x1000)

    /* IVI Foundation defined warnings */
#define IVI_WARN_NSUP_ID_QUERY                  (IVI_WARN_BASE + 0x65)
#define IVI_WARN_NSUP_RESET                     (IVI_WARN_BASE + 0x66)
#define IVI_WARN_NSUP_SELF_TEST                 (IVI_WARN_BASE + 0x67)
#define IVI_WARN_NSUP_ERROR_QUERY               (IVI_WARN_BASE + 0x68)
#define IVI_WARN_NSUP_REV_QUERY                 (IVI_WARN_BASE + 0x69)

    /* IVI Foundation defined errors */
#define IVI_ERROR_CANNOT_RECOVER                (IVI_ERROR_BASE + 0x00)
#define IVI_ERROR_INSTRUMENT_STATUS             (IVI_ERROR_BASE + 0x01)
#define IVI_ERROR_CANNOT_OPEN_FILE              (IVI_ERROR_BASE + 0x02)
#define IVI_ERROR_READING_FILE                  (IVI_ERROR_BASE + 0x03)
#define IVI_ERROR_WRITING_FILE                  (IVI_ERROR_BASE + 0x04)
#define IVI_ERROR_INVALID_PATHNAME              (IVI_ERROR_BASE + 0x0B)
#define IVI_ERROR_INVALID_ATTRIBUTE             (IVI_ERROR_BASE + 0x0C)
#define IVI_ERROR_IVI_ATTR_NOT_WRITABLE         (IVI_ERROR_BASE + 0x0D)
#define IVI_ERROR_IVI_ATTR_NOT_READABLE         (IVI_ERROR_BASE + 0x0E)
#define IVI_ERROR_INVALID_VALUE                 (IVI_ERROR_BASE + 0x10)
#define IVI_ERROR_FUNCTION_NOT_SUPPORTED        (IVI_ERROR_BASE + 0x11)
#define IVI_ERROR_ATTRIBUTE_NOT_SUPPORTED       (IVI_ERROR_BASE + 0x12)
#define IVI_ERROR_VALUE_NOT_SUPPORTED           (IVI_ERROR_BASE + 0x13)
#define IVI_ERROR_TYPES_DO_NOT_MATCH            (IVI_ERROR_BASE + 0x15)
#define IVI_ERROR_NOT_INITIALIZED               (IVI_ERROR_BASE + 0x1D)
#define IVI_ERROR_UNKNOWN_CHANNEL_NAME          (IVI_ERROR_BASE + 0x20)
#define IVI_ERROR_TOO_MANY_OPEN_FILES           (IVI_ERROR_BASE + 0x23)
#define IVI_ERROR_CHANNEL_NAME_REQUIRED         (IVI_ERROR_BASE + 0x44)
#define IVI_ERROR_CHANNEL_NAME_NOT_ALLOWED      (IVI_ERROR_BASE + 0x45)
#define IVI_ERROR_MISSING_OPTION_NAME           (IVI_ERROR_BASE + 0x49)
#define IVI_ERROR_MISSING_OPTION_VALUE          (IVI_ERROR_BASE + 0x4A)
#define IVI_ERROR_BAD_OPTION_NAME               (IVI_ERROR_BASE + 0x4B)
#define IVI_ERROR_BAD_OPTION_VALUE              (IVI_ERROR_BASE + 0x4C)
#define IVI_ERROR_OUT_OF_MEMORY                 (IVI_ERROR_BASE + 0x56)
#define IVI_ERROR_OPERATION_PENDING             (IVI_ERROR_BASE + 0x57)
#define IVI_ERROR_NULL_POINTER                  (IVI_ERROR_BASE + 0x58)
#define IVI_ERROR_UNEXPECTED_RESPONSE           (IVI_ERROR_BASE + 0x59)
#define IVI_ERROR_FILE_NOT_FOUND                (IVI_ERROR_BASE + 0x5B)
#define IVI_ERROR_INVALID_FILE_FORMAT           (IVI_ERROR_BASE + 0x5C)
#define IVI_ERROR_STATUS_NOT_AVAILABLE          (IVI_ERROR_BASE + 0x5D)
#define IVI_ERROR_ID_QUERY_FAILED               (IVI_ERROR_BASE + 0x5E)
#define IVI_ERROR_RESET_FAILED                  (IVI_ERROR_BASE + 0x5F)
#define IVI_ERROR_RESOURCE_UNKNOWN              (IVI_ERROR_BASE + 0x60)
#define IVI_ERROR_CANNOT_CHANGE_SIMULATION_STATE       (IVI_ERROR_BASE + 0x62)
#define IVI_ERROR_INVALID_NUMBER_OF_LEVELS_IN_SELECTOR (IVI_ERROR_BASE + 0x63)
#define IVI_ERROR_INVALID_RANGE_IN_SELECTOR     (IVI_ERROR_BASE + 0x64)
#define IVI_ERROR_UNKOWN_NAME_IN_SELECTOR       (IVI_ERROR_BASE + 0x65)
#define IVI_ERROR_BADLY_FORMED_SELECTOR         (IVI_ERROR_BASE + 0x66)
#define IVI_ERROR_UNKNOWN_PHYSICAL_IDENTIFIER   (IVI_ERROR_BASE + 0x67)

/* IVI Foundation reserved (grandfathered) errors */
#define IVI_ERROR_DRIVER_MODULE_NOT_FOUND       (IVI_ERROR_BASE + 0x05)
#define IVI_ERROR_CANNOT_OPEN_DRIVER_MODULE     (IVI_ERROR_BASE + 0x06)
#define IVI_ERROR_INVALID_DRIVER_MODULE         (IVI_ERROR_BASE + 0x07)
#define IVI_ERROR_UNDEFINED_REFERENCES          (IVI_ERROR_BASE + 0x08)
#define IVI_ERROR_FUNCTION_NOT_FOUND            (IVI_ERROR_BASE + 0x09)
#define IVI_ERROR_LOADING_DRIVER_MODULE         (IVI_ERROR_BASE + 0x0A)
#define IVI_ERROR_INVALID_PARAMETER             (IVI_ERROR_BASE + 0x0F)
#define IVI_ERROR_INVALID_TYPE                  (IVI_ERROR_BASE + 0x14)
#define IVI_ERROR_MULTIPLE_DEFERRED_SETTING     (IVI_ERROR_BASE + 0x16)
#define IVI_ERROR_ITEM_ALREADY_EXISTS           (IVI_ERROR_BASE + 0x17)
#define IVI_ERROR_INVALID_CONFIGURATION         (IVI_ERROR_BASE + 0x18)
#define IVI_ERROR_VALUE_NOT_AVAILABLE           (IVI_ERROR_BASE + 0x19)
#define IVI_ERROR_ATTRIBUTE_VALUE_NOT_KNOWN     (IVI_ERROR_BASE + 0x1A)
#define IVI_ERROR_NO_RANGE_TABLE                (IVI_ERROR_BASE + 0x1B)
#define IVI_ERROR_INVALID_RANGE_TABLE           (IVI_ERROR_BASE + 0x1C)
#define IVI_ERROR_NON_INTERCHANGEABLE_BEHAVIOR  (IVI_ERROR_BASE + 0x1E)
#define IVI_ERROR_NO_CHANNEL_TABLE              (IVI_ERROR_BASE + 0x1F)
#define IVI_ERROR_SYS_RSRC_ALLOC                (IVI_ERROR_BASE + 0x21)
#define IVI_ERROR_ACCESS_DENIED                 (IVI_ERROR_BASE + 0x22)
#define IVI_ERROR_UNABLE_TO_CREATE_TEMP_FILE    (IVI_ERROR_BASE + 0x24)
#define IVI_ERROR_NO_UNUSED_TEMP_FILENAMES      (IVI_ERROR_BASE + 0x25)
#define IVI_ERROR_DISK_FULL                     (IVI_ERROR_BASE + 0x26)
#define IVI_ERROR_CONFIG_FILE_NOT_FOUND         (IVI_ERROR_BASE + 0x27)
#define IVI_ERROR_CANNOT_OPEN_CONFIG_FILE       (IVI_ERROR_BASE + 0x28)
#define IVI_ERROR_ERROR_READING_CONFIG_FILE     (IVI_ERROR_BASE + 0x29)
#define IVI_ERROR_BAD_INTEGER_IN_CONFIG_FILE    (IVI_ERROR_BASE + 0x2A)
#define IVI_ERROR_BAD_DOUBLE_IN_CONFIG_FILE     (IVI_ERROR_BASE + 0x2B)
#define IVI_ERROR_BAD_BOOLEAN_IN_CONFIG_FILE    (IVI_ERROR_BASE + 0x2C)
#define IVI_ERROR_CONFIG_ENTRY_NOT_FOUND        (IVI_ERROR_BASE + 0x2D)
#define IVI_ERROR_DRIVER_DLL_INIT_FAILED        (IVI_ERROR_BASE + 0x2E)
#define IVI_ERROR_DRIVER_UNRESOLVED_SYMBOL      (IVI_ERROR_BASE + 0x2F)
#define IVI_ERROR_CANNOT_FIND_CVI_RTE           (IVI_ERROR_BASE + 0x30)
#define IVI_ERROR_CANNOT_OPEN_CVI_RTE           (IVI_ERROR_BASE + 0x31)
#define IVI_ERROR_CVI_RTE_INVALID_FORMAT        (IVI_ERROR_BASE + 0x32)
#define IVI_ERROR_CVI_RTE_MISSING_FUNCTION      (IVI_ERROR_BASE + 0x33)
#define IVI_ERROR_CVI_RTE_INIT_FAILED           (IVI_ERROR_BASE + 0x34)
#define IVI_ERROR_CVI_RTE_UNRESOLVED_SYMBOL     (IVI_ERROR_BASE + 0x35)
#define IVI_ERROR_LOADING_CVI_RTE               (IVI_ERROR_BASE + 0x36)
#define IVI_ERROR_CANNOT_OPEN_DLL_FOR_EXPORTS   (IVI_ERROR_BASE + 0x37)
#define IVI_ERROR_DLL_CORRUPTED                 (IVI_ERROR_BASE + 0x38)
#define IVI_ERROR_NO_DLL_EXPORT_TABLE           (IVI_ERROR_BASE + 0x39)
#define IVI_ERROR_UNKNOWN_DEFAULT_SETUP_ATTR    (IVI_ERROR_BASE + 0x3A)
#define IVI_ERROR_INVALID_DEFAULT_SETUP_VAL     (IVI_ERROR_BASE + 0x3B)
#define IVI_ERROR_UNKNOWN_MEMORY_PTR            (IVI_ERROR_BASE + 0x3C)
#define IVI_ERROR_EMPTY_CHANNEL_LIST            (IVI_ERROR_BASE + 0x3D)
#define IVI_ERROR_DUPLICATE_CHANNEL_STRING      (IVI_ERROR_BASE + 0x3E)
#define IVI_ERROR_DUPLICATE_VIRT_CHAN_NAME      (IVI_ERROR_BASE + 0x3F)
#define IVI_ERROR_MISSING_VIRT_CHAN_NAME        (IVI_ERROR_BASE + 0x40)
#define IVI_ERROR_BAD_VIRT_CHAN_NAME            (IVI_ERROR_BASE + 0x41)
#define IVI_ERROR_UNASSIGNED_VIRT_CHAN_NAME     (IVI_ERROR_BASE + 0x42)
#define IVI_ERROR_BAD_VIRT_CHAN_ASSIGNMENT      (IVI_ERROR_BASE + 0x43)
#define IVI_ERROR_ATTR_NOT_VALID_FOR_CHANNEL    (IVI_ERROR_BASE + 0x46)
#define IVI_ERROR_ATTR_MUST_BE_CHANNEL_BASED    (IVI_ERROR_BASE + 0x47)
#define IVI_ERROR_CHANNEL_ALREADY_EXCLUDED      (IVI_ERROR_BASE + 0x48)
#define IVI_ERROR_NOT_CREATED_BY_CLASS          (IVI_ERROR_BASE + 0x4D)
#define IVI_ERROR_IVI_INI_IS_RESERVED           (IVI_ERROR_BASE + 0x4E)
#define IVI_ERROR_DUP_RUNTIME_CONFIG_ENTRY      (IVI_ERROR_BASE + 0x4F)
#define IVI_ERROR_INDEX_IS_ONE_BASED            (IVI_ERROR_BASE + 0x50)
#define IVI_ERROR_INDEX_IS_TOO_HIGH             (IVI_ERROR_BASE + 0x51)
#define IVI_ERROR_ATTR_NOT_CACHEABLE            (IVI_ERROR_BASE + 0x52)
#define IVI_ERROR_ADDR_ATTRS_MUST_BE_HIDDEN     (IVI_ERROR_BASE + 0x53)
#define IVI_ERROR_BAD_CHANNEL_NAME              (IVI_ERROR_BASE + 0x54)
#define IVI_ERROR_BAD_PREFIX_IN_CONFIG_FILE     (IVI_ERROR_BASE + 0x55)
/////////////////////////////////////////////////
//错误机制//
/* Specific errors */
#define IVI_ERROR_CANNOT_MODIFY_REPEATED_CAPABILITY_TABLE  (IVI_NI_ERROR_BASE + 0)
#define IVI_ERROR_CANNOT_RESTRICT_ATTRIBUTE_TWICE          (IVI_NI_ERROR_BASE + 1)
#define IVI_ERROR_REPEATED_CAPABILITY_ALREADY_EXISTS       (IVI_NI_ERROR_BASE + 2)
#define IVI_ERROR_REPEATED_CAPABILITY_NOT_DEFINED          (IVI_NI_ERROR_BASE + 3)
#define IVI_ERROR_INVALID_REPEATED_CAPABILITY_NAME         (IVI_NI_ERROR_BASE + 4)
#define IVI_ERROR_CONFIG_SERVER_NOT_PRESENT                (IVI_NI_ERROR_BASE + 0xD)


/*****************************************************************************/
/*= Macros for checking for errors.                                 ======== */
/*= The checkErr and viCheckErr macros discard warnings.            ======== */
/*= The checkWarn and viCheckWarn macros preserve warnings.         ======== */
/*****************************************************************************/
#ifndef checkAlloc
#define checkAlloc(fCall)    if ((fCall) == 0) \
                                 {error = VI_ERROR_ALLOC; goto Error;}  else error = error
#endif

#ifndef checkErr
#define checkErr(fCall)      if (error = (fCall), (error = (error < 0) ? error : VI_SUCCESS)) \
                                 {goto Error;}  else error = error
#endif

#ifndef checkWarn
#define checkWarn(fCall)     if (1) {ViStatus _code_; if (_code_ = (fCall), _code_ < 0)    \
                                                {error = _code_;goto Error;}        \
                                               else error = (error==0)?_code_:error;} else error = error
#endif

#ifndef viCheckAlloc
#define viCheckAlloc(fCall)  if ((fCall) == 0) \
                                 {error = VI_ERROR_ALLOC; Ivi_SetErrorInfo(vi, VI_FALSE, error, 0, VI_NULL); goto Error;}  else error = error
#endif

#ifndef viCheckErr
#define viCheckErr(fCall)    if (error = (fCall), (error = (error < 0) ? error : VI_SUCCESS)) \
                                 {Ivi_SetErrorInfo(vi, VI_FALSE, error, 0, VI_NULL); goto Error;}  else error = error
#endif

#ifndef viCheckErrElab
#define viCheckErrElab(fCall, elab) \
                             if (error = (fCall), (error = (error < 0) ? error : VI_SUCCESS)) \
                                 {Ivi_SetErrorInfo(vi, VI_FALSE, error, 0, elab); goto Error;}  else error = error
#endif

#ifndef viCheckParm
#define viCheckParm(fCall, parameterPosition, parameterName) \
                             if (error = (fCall), (error = (error < 0) ? (error) : VI_SUCCESS)) \
                                 {Ivi_SetErrorInfo(vi, VI_FALSE, error, Ivi_ParamPositionError(parameterPosition), parameterName); goto Error;}  else error = error
#endif

#ifndef viCheckWarn
#define viCheckWarn(fCall)   if (1) {ViStatus _code_; if (_code_ = (fCall), _code_?Ivi_SetErrorInfo(vi, VI_FALSE, _code_, 0, VI_NULL) : 0, _code_ < 0)    \
                                                {error = _code_;goto Error;}        \
                                               else error = (error==0)?_code_:error;} else error = error
#endif


/*****************************************************************************/
/*= Typedef for function pointer passed to Ivi_BuildChannelTable    ======== */
/*= when you want to allow virtual channel names in the IVI         ======== */
/*= configuration file to reference channel strings not passed      ======== */
/*= into Ivi_BuildChannelTable.                                     ======== */
/*****************************************************************************/
typedef ViStatus    (_VI_FUNC *Ivi_ValidateChannelStringFunc)(ViSession vi, ViConstString channelString, ViBoolean *isValid, ViStatus *secondaryError);
    /*
        You should return an error code only if you are unable to determine
        whether the channel string is valid or not.
        If the channel string is not a valid one, you should set *isValid
        to VI_FALSE but return VI_SUCCESS.
        If you set *isValid to VI_FALSE, IVI sets the primary error to
        IVI_ERROR_BAD_VIRT_CHAN_ASSIGNMENT and formats the error elaboration
        to include both the virtual channel name and the channel string.
        You can optionally set *secondaryError to specify what is wrong
        with the channel string.
    */


/*****************************************************************************/
/*= Function pointer typedefs for ViInt32 attribute callbacks       ======== */
/*****************************************************************************/

typedef ViStatus    (_VI_FUNC *ReadAttrViInt32_CallbackPtr)(ViSession vi, ViSession io, ViConstString repCapName, ViAttr attributeId, ViInt32 *value);
typedef ViStatus    (_VI_FUNC *WriteAttrViInt32_CallbackPtr)(ViSession vi, ViSession io, ViConstString repCapName, ViAttr attributeId, ViInt32 value);
typedef ViStatus    (_VI_FUNC *CheckAttrViInt32_CallbackPtr)(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 value);
typedef ViStatus    (_VI_FUNC *CompareAttrViInt32_CallbackPtr)(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 coercedNewValue, ViInt32 cacheValue, ViInt32 *result);
typedef ViStatus    (_VI_FUNC *CoerceAttrViInt32_CallbackPtr)(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 value, ViInt32 *coercedValue);

/*****************************************************************************/
/*= Function pointer typedefs for ViReal64 attribute callbacks      ======== */
/*****************************************************************************/
typedef ViStatus    (_VI_FUNC *ReadAttrViReal64_CallbackPtr)(ViSession vi, ViSession io, ViConstString repCapName, ViAttr attributeId, ViReal64 *value);
typedef ViStatus    (_VI_FUNC *WriteAttrViReal64_CallbackPtr)(ViSession vi, ViSession io, ViConstString repCapName, ViAttr attributeId, ViReal64 value);
typedef ViStatus    (_VI_FUNC *CheckAttrViReal64_CallbackPtr)(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViReal64 value);
typedef ViStatus    (_VI_FUNC *CompareAttrViReal64_CallbackPtr)(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViReal64 coercedNewValue, ViReal64 cacheValue, ViInt32 *result);
typedef ViStatus    (_VI_FUNC *CoerceAttrViReal64_CallbackPtr)(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViReal64 value, ViReal64 *coercedValue);

/*****************************************************************************/
/*= Function pointer typedefs for ViString attribute callbacks      ======== */
/*****************************************************************************/
typedef ViStatus    (_VI_FUNC *ReadAttrViString_CallbackPtr)(ViSession vi, ViSession io, ViConstString repCapName, ViAttr attributeId, const ViConstString cacheValue);
typedef ViStatus    (_VI_FUNC *WriteAttrViString_CallbackPtr)(ViSession vi, ViSession io, ViConstString repCapName, ViAttr attributeId, ViConstString value);
typedef ViStatus    (_VI_FUNC *CheckAttrViString_CallbackPtr)(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViConstString value);
typedef ViStatus    (_VI_FUNC *CompareAttrViString_CallbackPtr)(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViConstString coercedNewValue, ViConstString cacheValue, ViInt32 *result);
typedef ViStatus    (_VI_FUNC *CoerceAttrViString_CallbackPtr)(ViSession vi, ViConstString repCapName, ViAttr attributeId, const ViConstString value);

/*****************************************************************************/
/*= Function pointer typedefs for ViBoolean attribute callbacks     ======== */
/*****************************************************************************/
typedef ViStatus    (_VI_FUNC *ReadAttrViBoolean_CallbackPtr)(ViSession vi, ViSession io, ViConstString repCapName, ViAttr attributeId, ViBoolean *value);
typedef ViStatus    (_VI_FUNC *WriteAttrViBoolean_CallbackPtr)(ViSession vi, ViSession io, ViConstString repCapName, ViAttr attributeId, ViBoolean value);
typedef ViStatus    (_VI_FUNC *CheckAttrViBoolean_CallbackPtr)(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViBoolean value);
typedef ViStatus    (_VI_FUNC *CompareAttrViBoolean_CallbackPtr)(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViBoolean coercedNewValue, ViBoolean cacheValue, ViInt32 *result);
typedef ViStatus    (_VI_FUNC *CoerceAttrViBoolean_CallbackPtr)(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViBoolean value, ViBoolean *coercedValue);

/*****************************************************************************/
/*= Function pointer typedefs for ViSession attribute callbacks     ======== */
/*****************************************************************************/
typedef ViStatus    (_VI_FUNC *ReadAttrViSession_CallbackPtr)(ViSession vi, ViSession io, ViConstString repCapName, ViAttr attributeId, ViSession *value);
typedef ViStatus    (_VI_FUNC *WriteAttrViSession_CallbackPtr)(ViSession vi, ViSession io, ViConstString repCapName, ViAttr attributeId, ViSession value);
typedef ViStatus    (_VI_FUNC *CheckAttrViSession_CallbackPtr)(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViSession value);
typedef ViStatus    (_VI_FUNC *CompareAttrViSession_CallbackPtr)(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViSession coercedNewValue, ViSession cacheValue, ViInt32 *result);
typedef ViStatus    (_VI_FUNC *CoerceAttrViSession_CallbackPtr)(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViSession value, ViSession *coercedValue);

/*****************************************************************************/
/*= Function pointer typedefs for ViAddr attribute callbacks        ======== */
/*****************************************************************************/
typedef ViStatus    (_VI_FUNC *ReadAttrViAddr_CallbackPtr)(ViSession vi, ViSession io, ViConstString repCapName, ViAttr attributeId, ViAddr *value);
typedef ViStatus    (_VI_FUNC *WriteAttrViAddr_CallbackPtr)(ViSession vi, ViSession io, ViConstString repCapName, ViAttr attributeId, ViAddr value);
typedef ViStatus    (_VI_FUNC *CheckAttrViAddr_CallbackPtr)(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViAddr value);
typedef ViStatus    (_VI_FUNC *CompareAttrViAddr_CallbackPtr)(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViAddr coercedNewValue, ViAddr cacheValue, ViInt32 *result);
typedef ViStatus    (_VI_FUNC *CoerceAttrViAddr_CallbackPtr)(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViAddr value, ViAddr *coercedValue);
/*****************************************************************************/
/*= Function pointer typedef for the callback that retrieves        ======== */
/*= the range table.   Applies only to ViInt32, ViReal64,           ======== */
/*= ViInt64, and ViBoolean attributes.                              ======== */
/*****************************************************************************/
typedef ViStatus    (_VI_FUNC *RangeTable_CallbackPtr)(ViSession vi, ViConstString repCapName, ViAttr attributeId, IviRangeTablePtr *rangeTablePtr);
/*****************************************************************************/
/*= Base values for attribute constants.                            ======== */
/*= A private attribute is one that is defined for use within       ======== */
/*= that module and is not exported via an include file.            ======== */
/*****************************************************************************/
#define IVI_ATTR_BASE                   1000000
#define IVI_ENGINE_PRIVATE_ATTR_BASE    (IVI_ATTR_BASE +  00000)   /* base for private attributes of the IVI engine */
#define IVI_ENGINE_PUBLIC_ATTR_BASE     (IVI_ATTR_BASE +  50000)   /* base for public attributes of the IVI engine */
#define IVI_SPECIFIC_PUBLIC_ATTR_BASE   (IVI_ATTR_BASE + 150000)   /* base for public attributes of specific drivers */
#define IVI_SPECIFIC_PRIVATE_ATTR_BASE  (IVI_ATTR_BASE + 200000)   /* base for private attributes of specific drivers */
                                                                   /* This value was changed from IVI_ATTR_BASE + 10000 in the version of this file released in August 2013 (ICP 4.6). */
                                                                   /* A private attribute, by its very definition, should not be passed to another module; it should stay private to the compiled module. */
#define IVI_CLASS_PUBLIC_ATTR_BASE      (IVI_ATTR_BASE + 250000)   /* base for public attributes of class drivers */
#define IVI_CLASS_PRIVATE_ATTR_BASE     (IVI_ATTR_BASE + 300000)   /* base for private attributes of class drivers */
                                                                   /* This value was changed from IVI_ATTR_BASE + 20000 in the version of this file released in August 2013 (ICP 4.6). */
                                                                   /* A private attribute, by its very definition, should not be passed to another module; it should stay private to the compiled module. */
/*****************************************************************************/
/*= Public IVI engine attributes                                    ======== */
/*= The data type of each attribute is listed, followed by the      ======== */
/*= default value or a remark.                                      ======== */
/*= Note:  "hidden" means not readable or writable by the end-user. ======== */
/*****************************************************************************/
#define IVI_ATTR_NONE                   /* no attribute */              0xFFFFFFFF

#define IVI_ATTR_RANGE_CHECK            /* ViBoolean, VI_TRUE */        (IVI_ENGINE_PUBLIC_ATTR_BASE + 2)
#define IVI_ATTR_QUERY_INSTRUMENT_STATUS /* ViBoolean, VI_FALSE */      (IVI_ENGINE_PUBLIC_ATTR_BASE + 3)   /* If VI_TRUE, the specific driver is allowed to query the instrument error status after each operation */
#define IVI_ATTR_CACHE                  /* ViBoolean, VI_TRUE */        (IVI_ENGINE_PUBLIC_ATTR_BASE + 4)
#define IVI_ATTR_SIMULATE               /* ViBoolean, VI_FALSE */       (IVI_ENGINE_PUBLIC_ATTR_BASE + 5)
#define IVI_ATTR_RECORD_COERCIONS       /* ViBoolean, VI_FALSE */       (IVI_ENGINE_PUBLIC_ATTR_BASE + 6)
#define IVI_ATTR_DRIVER_SETUP           /* ViString,  "" */             (IVI_ENGINE_PUBLIC_ATTR_BASE + 7)

#define IVI_ATTR_INTERCHANGE_CHECK      /* ViBoolean, VI_TRUE */        (IVI_ENGINE_PUBLIC_ATTR_BASE + 21)
#define IVI_ATTR_SPY                    /* ViBoolean, VI_FALSE */       (IVI_ENGINE_PUBLIC_ATTR_BASE + 22)
#define IVI_ATTR_USE_SPECIFIC_SIMULATION  /* ViBoolean */               (IVI_ENGINE_PUBLIC_ATTR_BASE + 23)  /* simulate values in specific rather than class driver;  default is VI_TRUE if session opened through class driver, VI_FALSE otherwise */

#define IVI_ATTR_PRIMARY_ERROR          /* ViInt32  */                  (IVI_ENGINE_PUBLIC_ATTR_BASE + 101)
#define IVI_ATTR_SECONDARY_ERROR        /* VIInt32  */                  (IVI_ENGINE_PUBLIC_ATTR_BASE + 102)
#define IVI_ATTR_ERROR_ELABORATION      /* ViString */                  (IVI_ENGINE_PUBLIC_ATTR_BASE + 103)

#define IVI_ATTR_CHANNEL_COUNT          /* ViInt32,  not writable*/     (IVI_ENGINE_PUBLIC_ATTR_BASE + 203)   /* set by the specific-driver;  default: 1 */

#define IVI_ATTR_CLASS_DRIVER_PREFIX    /* ViString, not writable*/     (IVI_ENGINE_PUBLIC_ATTR_BASE + 301)  /* instrument prefix for the class driver;  empty string if not using class driver */
#define IVI_ATTR_SPECIFIC_DRIVER_PREFIX /* ViString, not writable*/     (IVI_ENGINE_PUBLIC_ATTR_BASE + 302)  /* instrument prefix for the specific driver */
#define IVI_ATTR_SPECIFIC_DRIVER_LOCATOR/* ViString, not writable*/     (IVI_ENGINE_PUBLIC_ATTR_BASE + 303)  /* the pathnname of the specific driver code module; from the configuration file */
#define IVI_ATTR_IO_RESOURCE_DESCRIPTOR /* ViString, not writable*/     (IVI_ENGINE_PUBLIC_ATTR_BASE + 304)  /* the string that describes how to find the physical instrument; from the configuration file */
#define IVI_ATTR_LOGICAL_NAME           /* ViString, not writable*/     (IVI_ENGINE_PUBLIC_ATTR_BASE + 305)  /* for class drivers, the logical name used in the Init call to identify the specific instrument */
#define IVI_ATTR_VISA_RM_SESSION        /* ViSession,hidden      */     (IVI_ENGINE_PUBLIC_ATTR_BASE + 321)
#define IVI_ATTR_IO_SESSION             /* ViSession,not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 322)
#define IVI_ATTR_IO_SESSION_TYPE        /* ViString, not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 324)
#define IVI_ATTR_SUPPORTED_INSTRUMENT_MODELS   /* ViString, not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 327)

#define IVI_ATTR_GROUP_CAPABILITIES     /* ViString, not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 401)
#define IVI_ATTR_FUNCTION_CAPABILITIES  /* ViString, not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 402)

#define IVI_ATTR_ENGINE_MAJOR_VERSION       /* ViInt32,  not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 501)
#define IVI_ATTR_ENGINE_MINOR_VERSION       /* ViInt32,  not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 502)
#define IVI_ATTR_SPECIFIC_DRIVER_MAJOR_VERSION /* ViInt32,  not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 503)
#define IVI_ATTR_SPECIFIC_DRIVER_MINOR_VERSION /* ViInt32,  not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 504)
#define IVI_ATTR_CLASS_DRIVER_MAJOR_VERSION /* ViInt32,  not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 505)
#define IVI_ATTR_CLASS_DRIVER_MINOR_VERSION /* ViInt32,  not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 506)

#define IVI_ATTR_INSTRUMENT_FIRMWARE_REVISION /* ViString, not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 510)
#define IVI_ATTR_INSTRUMENT_MANUFACTURER    /* ViString, not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 511)
#define IVI_ATTR_INSTRUMENT_MODEL           /* ViString, not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 512)
#define IVI_ATTR_SPECIFIC_DRIVER_VENDOR     /* ViString, not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 513)
#define IVI_ATTR_SPECIFIC_DRIVER_DESCRIPTION/* ViString, not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 514)
#define IVI_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION /* ViInt32, not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 515)
#define IVI_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION /* ViInt32, not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 516)
#define IVI_ATTR_CLASS_DRIVER_VENDOR        /* ViString, not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 517)
#define IVI_ATTR_CLASS_DRIVER_DESCRIPTION   /* ViString, not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 518)
#define IVI_ATTR_CLASS_DRIVER_CLASS_SPEC_MAJOR_VERSION /* ViInt32, not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 519)
#define IVI_ATTR_CLASS_DRIVER_CLASS_SPEC_MINOR_VERSION /* ViInt32, not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 520)

#define IVI_ATTR_SPECIFIC_DRIVER_REVISION   /* ViString, not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 551)
#define IVI_ATTR_CLASS_DRIVER_REVISION      /* ViString, not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 552)
#define IVI_ATTR_ENGINE_REVISION            /* ViString, not user-writable*/(IVI_ENGINE_PUBLIC_ATTR_BASE + 553)

#define IVI_ATTR_OPC_CALLBACK               /* ViAddr,    hidden */     (IVI_ENGINE_PUBLIC_ATTR_BASE + 602)  /* see Ivi_OPCCallbackPtr  typedef */
#define IVI_ATTR_CHECK_STATUS_CALLBACK      /* ViAddr,    hidden */     (IVI_ENGINE_PUBLIC_ATTR_BASE + 603)  /* see Ivi_CheckStatusCallbackPtr  typedef */

#define IVI_ATTR_USER_INTERCHANGE_CHECK_CALLBACK /* ViAddr, hidden */   (IVI_ENGINE_PUBLIC_ATTR_BASE + 801)  /* see Ivi_InterchangeCheckCallbackPtr typedef */

/*****************************************************************************/
/*= Public IVI Engine Functions                                     ======== */
/*= These functions have a function panel                                    */
/*****************************************************************************/
/*****************************************************************************/
/*= Specific   Drivers                                              ======== */
/*****************************************************************************/
ViStatus DLL_EXPORT  _VI_FUNC    Ivi_SpecificDriverNew(ViConstString specificPrefix, ViConstString optionsString, ViSession *vi);


/*****************************************************************************/
/*= Channels                                                        ======== */
/*****************************************************************************/
ViStatus DLL_EXPORT  _VI_FUNC   Ivi_BuildChannelTable(ViSession vi, ViConstString defaultChannelList, ViBoolean allowUnknownChannelStrings, Ivi_ValidateChannelStringFunc chanStrValidationFunc);
ViStatus DLL_EXPORT  _VI_FUNC   Ivi_GetNthChannelString(ViSession vi, ViInt32 index, ViConstString *channelString);  /* 1-based index */
/*****************************************************************************/
/*= Attributes                                                      ======== */
/*****************************************************************************/
ViStatus DLL_EXPORT  _VI_FUNC    Ivi_DeleteAttribute(ViSession vi, ViAttr attributeId);
/*= Creation                                                    ======== */
ViStatus DLL_EXPORT  _VI_FUNC    Ivi_AddAttributeViInt32(ViSession    vi,
                                                     ViAttr    id,
                                                    ViConstString  attrName,
                                                    ViInt32     defaultValue,
                                                    IviAttrFlags   attributeFlags,
                                                    ReadAttrViInt32_CallbackPtr  readCallback,
                                                    WriteAttrViInt32_CallbackPtr  writeCallback,
                                                    IviRangeTablePtr   rangeTable);

ViStatus DLL_EXPORT  _VI_FUNC    Ivi_AddAttributeViReal64(ViSession   vi,
                                                     ViAttr    id,
                                                     ViConstString    attrName,
                                                     ViReal64     defaultValue,
                                                     IviAttrFlags    attributeFlags,
                                                     ReadAttrViReal64_CallbackPtr    readCallback,
                                                     WriteAttrViReal64_CallbackPtr   writeCallback,
                                                     IviRangeTablePtr   rangeTable,
                                                     ViInt32   comparePrecision);

ViStatus DLL_EXPORT  _VI_FUNC    Ivi_AddAttributeViString(ViSession   vi,
                                                     ViAttr    id,
                                                     ViConstString    attrName,
                                                     ViConstString    defaultValue,
                                                     IviAttrFlags     attributeFlags,
                                                     ReadAttrViString_CallbackPtr    readCallback,
                                                     WriteAttrViString_CallbackPtr   writeCallback);

ViStatus DLL_EXPORT  _VI_FUNC    Ivi_AddAttributeViBoolean(  ViSession    vi,
                                                        ViAttr     id,
                                                        ViConstString    attrName,
                                                        ViBoolean   defaultValue,
                                                        IviAttrFlags     attributeFlags,
                                                        ReadAttrViBoolean_CallbackPtr   readCallback,
                                                        WriteAttrViBoolean_CallbackPtr  writeCallback);

ViStatus DLL_EXPORT  _VI_FUNC    Ivi_AddAttributeViSession(  ViSession   vi,
                                                        ViAttr     id,
                                                        ViConstString   attrName,
                                                        ViSession   defaultValue,
                                                        IviAttrFlags  attributeFlags,
                                                        ReadAttrViSession_CallbackPtr   readCallback,
                                                        WriteAttrViSession_CallbackPtr  writeCallback);

ViStatus DLL_EXPORT  _VI_FUNC    Ivi_AddAttributeViAddr( ViSession   vi,
                                                         ViAttr   id,
                                                         ViConstString   attrName,
                                                         ViAddr      defaultValue,
                                                         IviAttrFlags    attributeFlags,
                                                         ReadAttrViAddr_CallbackPtr  readCallback,
                                                         WriteAttrViAddr_CallbackPtr  writeCallback);
ViStatus DLL_EXPORT  _VI_FUNC    Ivi_AddRepeatedAttributeViInt32(ViSession  vi,
                                                                 ViConstString repCapName,
                                                                 ViAttr id,
                                                                 ViConstString  attrName,
                                                                 ViInt32  defaultValue,
                                                                 IviAttrFlags  attributeFlags,
                                                                 ReadAttrViInt32_CallbackPtr  readCallback,
                                                                 WriteAttrViInt32_CallbackPtr writeCallback,
                                                                 IviRangeTablePtr rangeTable);
ViStatus DLL_EXPORT _VI_FUNC    Ivi_AddRepeatedAttributeViString(ViSession                       vi,
                                                                ViConstString                   repCapName,
                                                                ViAttr                          id,
                                                                ViConstString                   attrName,
                                                                ViConstString                   defaultValue,
                                                                IviAttrFlags                    attributeFlags,
                                                                ReadAttrViString_CallbackPtr    readCallback,
                                                                WriteAttrViString_CallbackPtr   writeCallback);
ViStatus DLL_EXPORT _VI_FUNC    Ivi_AddRepeatedAttributeViBoolean( ViSession                       vi,
                                                                ViConstString                   repCapName,
                                                                ViAttr                          id,
                                                                ViConstString                   attrName,
                                                                ViBoolean                       defaultValue,
                                                                IviAttrFlags                    attributeFlags,
                                                                ReadAttrViBoolean_CallbackPtr   readCallback,
                                                                WriteAttrViBoolean_CallbackPtr  writeCallback);
ViStatus DLL_EXPORT _VI_FUNC    Ivi_AddRepeatedAttributeViSession( ViSession                       vi,
                                                                ViConstString                   repCapName,
                                                                ViAttr                          id,
                                                                ViConstString                   attrName,
                                                                ViSession                       defaultValue,
                                                                IviAttrFlags                    attributeFlags,
                                                                ReadAttrViSession_CallbackPtr   readCallback,
                                                                WriteAttrViSession_CallbackPtr  writeCallback);
ViStatus DLL_EXPORT _VI_FUNC    Ivi_AddRepeatedAttributeViAddr(ViSession                       vi,
                                                            ViConstString                   repCapName,
                                                            ViAttr                          id,
                                                            ViConstString                   attrName,
                                                            ViAddr                          defaultValue,
                                                            IviAttrFlags                    attributeFlags,
                                                            ReadAttrViAddr_CallbackPtr      readCallback,
                                                            WriteAttrViAddr_CallbackPtr     writeCallback);
ViStatus DLL_EXPORT _VI_FUNC    Ivi_AddRepeatedAttributeViReal64(  ViSession                       vi,
                                                                ViConstString                   repCapName,
                                                                ViAttr                          id,
                                                                ViConstString                   attrName,
                                                                ViReal64                        defaultValue,
                                                                IviAttrFlags                    attributeFlags,
                                                                ReadAttrViReal64_CallbackPtr    readCallback,
                                                                WriteAttrViReal64_CallbackPtr   writeCallback,
                                                                IviRangeTablePtr                rangeTable,
                                                                ViInt32                         comparePrecision);


 /*= Set/Get/Check Attribute                                         ======== */
/*= Typesafe Set Attribute functions for use in drivers         ======== */
ViStatus DLL_EXPORT _VI_FUNC    Ivi_SetAttributeViInt32(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 optionFlags, ViInt32 value);
ViStatus DLL_EXPORT _VI_FUNC    Ivi_SetAttributeViReal64(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 optionFlags, ViReal64 value);
ViStatus DLL_EXPORT _VI_FUNC    Ivi_SetAttributeViString(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 optionFlags, ViConstString value);
ViStatus DLL_EXPORT _VI_FUNC    Ivi_SetAttributeViBoolean(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 optionFlags, ViBoolean value);
ViStatus DLL_EXPORT _VI_FUNC    Ivi_SetAttributeViSession(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 optionFlags, ViSession value);
ViStatus DLL_EXPORT _VI_FUNC    Ivi_SetAttributeViAddr(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 optionFlags, ViAddr value);
/*= Typesafe Get Attribute functions for use in drivers         ======== */
ViStatus DLL_EXPORT _VI_FUNC    Ivi_GetAttributeViInt32(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 optionFlags, ViInt32 *value);
ViStatus DLL_EXPORT _VI_FUNC    Ivi_GetAttributeViReal64(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 optionFlags, ViReal64 *value);
ViStatus DLL_EXPORT _VI_FUNC    Ivi_GetAttributeViString(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 optionFlags, ViInt32 bufSize, ViChar value[]);
ViStatus DLL_EXPORT _VI_FUNC    Ivi_GetAttributeViBoolean(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 optionFlags, ViBoolean *value);
ViStatus DLL_EXPORT _VI_FUNC    Ivi_GetAttributeViSession(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 optionFlags, ViSession *value);
ViStatus DLL_EXPORT _VI_FUNC    Ivi_GetAttributeViAddr(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 optionFlags, ViAddr *value);
/*= Typesafe Check Attribute functions for use in drivers       ======== */
ViStatus DLL_EXPORT _VI_FUNC    Ivi_CheckAttributeViInt32(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 optionFlags, ViInt32 value);
ViStatus DLL_EXPORT _VI_FUNC    Ivi_CheckAttributeViReal64(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 optionFlags, ViReal64 value);
ViStatus DLL_EXPORT _VI_FUNC    Ivi_CheckAttributeViString(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 optionFlags, ViConstString value);
ViStatus DLL_EXPORT _VI_FUNC    Ivi_CheckAttributeViBoolean(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 optionFlags, ViBoolean value);
ViStatus DLL_EXPORT _VI_FUNC    Ivi_CheckAttributeViSession(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 optionFlags, ViSession value);
ViStatus DLL_EXPORT _VI_FUNC    Ivi_CheckAttributeViAddr(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 optionFlags, ViAddr value);
 /*= Locking                                                     ======== */
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_LockSession(ViSession vi, ViBoolean *callerHasLock);
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_UnlockSession(ViSession vi, ViBoolean *callerHasLock);

/*= Information                                                 ======== */
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_GetAttributeFlags(ViSession vi, ViAttr attributeId, IviAttrFlags *flags);
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_SetAttributeFlags(ViSession vi, ViAttr attributeId, IviAttrFlags flags);
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_GetAttrMinMaxViInt32(ViSession vi, ViConstString repCapName, ViAttr attr, ViInt32 *min,
                                                         ViInt32 *max, ViBoolean *hasMin, ViBoolean *hasMax);
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_GetAttrMinMaxViReal64(ViSession vi, ViConstString repCapName, ViAttr attr, ViReal64 *min,
                                                          ViReal64 *max, ViBoolean *hasMin, ViBoolean *hasMax);
/*= Set Attribute Read Callback functions                   ======== */
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_SetAttrReadCallbackViInt32(ViSession vi, ViAttr attributeId, ReadAttrViInt32_CallbackPtr readCallback);
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_SetAttrReadCallbackViString(ViSession vi, ViAttr attributeId, ReadAttrViString_CallbackPtr readCallback);
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_SetAttrReadCallbackViBoolean(ViSession vi, ViAttr attributeId, ReadAttrViBoolean_CallbackPtr readCallback);
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_SetAttrReadCallbackViSession (ViSession vi, ViAttr attributeId, ReadAttrViSession_CallbackPtr readCallback);
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_SetAttrReadCallbackViAddr(ViSession vi, ViAttr attributeId, ReadAttrViAddr_CallbackPtr readCallback);
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_SetAttrReadCallbackViReal64(ViSession vi, ViAttr attributeId, ReadAttrViReal64_CallbackPtr readCallback);
/*= Set Attribute Write Callback functions                  ======== */
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_SetAttrWriteCallbackViInt32(ViSession vi, ViAttr attributeId, WriteAttrViInt32_CallbackPtr writeCallback);
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_SetAttrWriteCallbackViString(ViSession vi, ViAttr attributeId, WriteAttrViString_CallbackPtr writeCallback);
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_SetAttrWriteCallbackViBoolean(ViSession vi, ViAttr attributeId, WriteAttrViBoolean_CallbackPtr writeCallback);
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_SetAttrWriteCallbackViSession(ViSession vi, ViAttr attributeId, WriteAttrViSession_CallbackPtr writeCallback);
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_SetAttrWriteCallbackViAddr(ViSession vi, ViAttr attributeId, WriteAttrViAddr_CallbackPtr writeCallback);
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_SetAttrWriteCallbackViReal64(ViSession vi, ViAttr attributeId, WriteAttrViReal64_CallbackPtr writeCallback);
/*= RangeTable Callback functions                  ======== */
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_SetAttrRangeTableCallback (ViSession vi, ViAttr attributeId, RangeTable_CallbackPtr rangeTableCallback);
/*= Set Attribute Check Callback functions                  ======== */
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_SetAttrCheckCallbackViInt32(ViSession vi, ViAttr attributeId, CheckAttrViInt32_CallbackPtr checkCallback);
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_SetAttrCheckCallbackViReal64(ViSession vi, ViAttr attributeId, CheckAttrViReal64_CallbackPtr checkCallback);
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_SetAttrCheckCallbackViString(ViSession vi, ViAttr attributeId, CheckAttrViString_CallbackPtr checkCallback);
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_SetAttrCheckCallbackViBoolean(ViSession vi, ViAttr attributeId, CheckAttrViBoolean_CallbackPtr checkCallback);
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_SetAttrCheckCallbackViSession(ViSession vi, ViAttr attributeId, CheckAttrViSession_CallbackPtr checkCallback);
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_SetAttrCheckCallbackViAddr(ViSession vi, ViAttr attributeId, CheckAttrViAddr_CallbackPtr checkCallback);
/*= Default callbacks                                              ========= */
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_DefaultCheckCallbackViInt32(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViInt32 value);
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_DefaultCheckCallbackViReal64(ViSession vi, ViConstString repCapName, ViAttr attributeId, ViReal64 value);
/*= Range Table Entries                                         ======== */
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_GetViInt32EntryFromValue (ViInt32 value, IviRangeTablePtr table, ViInt32 *discreteOrMin, ViInt32 *max,
                                                              ViInt32 *coercedValue, ViInt32 *tableIndex, ViString *cmdString, ViInt32 *cmdValue);
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_GetViReal64EntryFromValue (ViReal64 value, IviRangeTablePtr table, ViReal64 *discreteOrMin, ViReal64 *max,
                                                               ViReal64 *coercedValue, ViInt32 *tableIndex, ViString *cmdString, ViInt32 *cmdValue);
/*= Sessions                                                 ======== */
ViStatus  DLL_EXPORT _VI_FUNC   Ivi_Dispose(ViSession vi);



#ifdef __cplusplus
}
#endif
#endif /* _IVI_H */
