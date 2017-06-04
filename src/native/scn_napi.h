#define EXPORT_NAPI_METHOD(name, func) \
    desc = DECLARE_NAPI_PROPERTY(name, func); \
    NAPI_CALL_RETURN_VOID(env, napi_define_properties(env, exports, 1, &desc))

#define EXPORT_NAPI_CONST_NUMBER(name, value) \
    NAPI_CALL_RETURN_VOID(env, napi_create_number(env, value, &val)); \
    NAPI_CALL_RETURN_VOID(env, napi_set_named_property(env, exports, name, val));

#define EXPORT_NAPI_CONST_GLFW(name) \
    EXPORT_NAPI_CONST_NUMBER(#name, GLFW_##name);

#define RETURN_NAPI_BASE(getValueCall) \
    napi_value returnValue; \
    NAPI_CALL(env, getValueCall); \
    return returnValue;

#define RETURN_NAPI_UNDEFINED() RETURN_NAPI_BASE(napi_get_undefined(env, &returnValue))
#define RETURN_NAPI_NUMBER(val) RETURN_NAPI_BASE(napi_create_number(env, val, &returnValue))
#define RETURN_NAPI_BOOL(val) RETURN_NAPI_BASE(napi_get_boolean(env, val, &returnValue))
#define RETURN_NAPI_STRING(val) RETURN_NAPI_BASE(napi_create_string_utf8(env, val, -1, &returnValue));

#define GET_NAPI_PARAMS_INFO(expectedArgc) \
    napi_valuetype valuetype; \
    size_t argc; \
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, NULL, NULL, NULL)); \
    napi_value args[argc]; \
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr)); \
    NAPI_ASSERT(env, argc >= expectedArgc, "Wrong number of arguments");

#define GET_NAPI_PARAM_BASE(name, i, napiType, cType, napiGetCall, readableType) \
    NAPI_CALL(env, napi_typeof(env, args[i], &valuetype)); \
    NAPI_ASSERT(env, valuetype == napiType, "Expected argument " #name "(" #i ") to be of type " readableType "."); \
    cType name; \
    NAPI_CALL(env, napiGetCall(env, args[i], &name));

#define GET_NAPI_PARAM_STRING(name, i) \
    NAPI_CALL(env, napi_typeof(env, args[i], &valuetype)); \
    NAPI_ASSERT(env, valuetype == napi_string, "Expected argument " #name "(" #i ") to be of type string."); \
    size_t bufferSize_##name; \
    NAPI_CALL(env, napi_get_value_string_utf8(env, args[i], nullptr, 0, &bufferSize_##name)); \
    bufferSize_##name++; \
    char name[bufferSize_##name]; \
    NAPI_CALL(env, napi_get_value_string_utf8(env, args[i], name, bufferSize_##name, nullptr));

#define GET_NAPI_PARAM_FUNCTION(name, i) \
    NAPI_CALL(env, napi_typeof(env, args[i], &valuetype)); \
    NAPI_ASSERT(env, valuetype == napi_function, "Expected argument " #name "(" #i ") to be of type function"); \
    napi_value name = args[i];

#define GET_NAPI_PARAM_INT64(name, i) GET_NAPI_PARAM_BASE(name, i, napi_number, int64_t, napi_get_value_int64, "number");
#define GET_NAPI_PARAM_INT32(name, i) GET_NAPI_PARAM_BASE(name, i, napi_number, int32_t, napi_get_value_int32, "number");
#define GET_NAPI_PARAM_DOUBLE(name, i) GET_NAPI_PARAM_BASE(name, i, napi_number, double, napi_get_value_double, "number");

#define DECLARE_NAPI_METHOD(name) napi_value name(napi_env env, napi_callback_info info)

#define CALL_NAPI_FUNCTION_GLFW_CALLBACK(callbackRefName, argc, args) \
    napi_value nullValue; \
    napi_value callbackValue; \
    NAPI_CALL_RETURN_VOID(_env, napi_get_null(_env, &nullValue)); \
    NAPI_CALL_RETURN_VOID(_env, napi_get_reference_value(_env, callbackRefName, &callbackValue)); \
    NAPI_CALL_RETURN_VOID(_env, napi_call_function(_env, nullValue, callbackValue, argc, args, NULL));
