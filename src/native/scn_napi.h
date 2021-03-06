#define EXPORT_NAPI_METHOD(name, func) \
    desc = DECLARE_NAPI_PROPERTY(name, func); \
    NAPI_CALL_RETURN_VOID(env, napi_define_properties(env, exports, 1, &desc))

#define EXPORT_NAPI_CONST_NUMBER(name, value) \
    NAPI_CALL_RETURN_VOID(env, napi_create_number(env, value, &val)); \
    NAPI_CALL_RETURN_VOID(env, napi_set_named_property(env, exports, name, val));

#define EXPORT_NAPI_CONST_GLFW(name) \
    EXPORT_NAPI_CONST_NUMBER(#name, GLFW_##name);

#define EXPORT_NAPI_CONST_GL(name) \
    EXPORT_NAPI_CONST_NUMBER(#name, GL_##name);

#define RETURN_NAPI_BASE(getValueCall) \
    napi_value returnValue; \
    NAPI_CALL(env, getValueCall); \
    return returnValue;

#define RETURN_NAPI_GL_ACTIVE_INFO(name, size, type) \
    napi_value val; \
    napi_value returnValue; \
    NAPI_CALL(env, napi_create_object(env, &returnValue)); \
    NAPI_CALL(env, napi_create_string_utf8(env, name, -1, &val)); \
    NAPI_CALL(env, napi_set_named_property(env, returnValue, "name", val)); \
    NAPI_CALL(env, napi_create_number(env, size, &val)); \
    NAPI_CALL(env, napi_set_named_property(env, returnValue, "size", val)); \
    NAPI_CALL(env, napi_create_number(env, type, &val)); \
    NAPI_CALL(env, napi_set_named_property(env, returnValue, "type", val)); \
    return returnValue;

#define RETURN_NAPI_2NUMBER_OBJECT(a, b) \
    napi_value val; \
    napi_value returnValue; \
    NAPI_CALL(env, napi_create_object(env, &returnValue)); \
    NAPI_CALL(env, napi_create_number(env, a, &val)); \
    NAPI_CALL(env, napi_set_named_property(env, returnValue, #a, val)); \
    NAPI_CALL(env, napi_create_number(env, b, &val)); \
    NAPI_CALL(env, napi_set_named_property(env, returnValue, #b, val)); \
    return returnValue;

#define RETURN_NAPI_ARRAY_NUMBER(array, count) \
    napi_value arrayValue; \
    napi_value singleValue; \
    napi_create_array_with_length(env, count, &arrayValue); \
    for(int i = 0; i < count; i++){ \
        NAPI_CALL(env, napi_create_number(env, array[i], &singleValue)); \
        NAPI_CALL(env, napi_set_element(env, arrayValue, i, singleValue)); \
    } \
    return arrayValue;

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

#define GET_NAPI_PARAM_BASE_NULLABLE(name, i, napiType, cType, napiGetCall, readableType, defaultValue) \
    NAPI_CALL(env, napi_typeof(env, args[i], &valuetype)); \
    NAPI_ASSERT(env, valuetype == napiType || valuetype == napi_null, "Expected argument " #name "(" #i ") to be of type " readableType " or null."); \
    cType name; \
    if(valuetype == napi_null){ \
        name = defaultValue; \
    } else { \
        NAPI_CALL(env, napiGetCall(env, args[i], &name)); \
    }

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

#define GET_NAPI_PARAM_ARRAY_BUFFER(name, i) \
    size_t byteLength_##name; \
    void* name; \
    bool isTypedArray_##name; \
    bool isArrayBuffer_##name; \
    NAPI_CALL(env, napi_is_typedarray(env, args[i], &isTypedArray_##name)); \
    NAPI_CALL(env, napi_is_arraybuffer(env, args[i], &isArrayBuffer_##name)); \
    NAPI_ASSERT(env, isTypedArray_##name || isArrayBuffer_##name, "Expected argument " #name "(" #i ") to be of type TypedArray or ArrayBuffer"); \
    if(isTypedArray_##name){ \
        napi_value bufferValue_##name; \
        NAPI_CALL(env, napi_get_typedarray_info(env, args[i], NULL, NULL, NULL, &bufferValue_##name, NULL)); \
        NAPI_CALL(env, napi_get_arraybuffer_info(env, bufferValue_##name, &name, &byteLength_##name)); \
    } else { \
        NAPI_CALL(env, napi_get_arraybuffer_info(env, args[i], &name, &byteLength_##name)); \
    }

#define GET_NAPI_PARAM_TYPED_ARRAY(name, i, cType, napiType, readableType) \
    size_t byteLength_##name; \
    void* name; \
    bool isTypedArray_##name; \
    napi_typedarray_type arrayType_##name; \
    size_t length_##name; \
    NAPI_CALL(env, napi_is_typedarray(env, args[i], &isTypedArray_##name)); \
    NAPI_ASSERT(env, isTypedArray_##name, "Expected argument " #name "(" #i ") to be of type " #readableType); \
    napi_value bufferValue_##name; \
    NAPI_CALL(env, napi_get_typedarray_info(env, args[i], &arrayType_##name, &length_##name, NULL, &bufferValue_##name, NULL)); \
    NAPI_ASSERT(env, arrayType_##name == napiType, "Expected argument " #name "(" #i ") to be of type " #readableType); \
    NAPI_CALL(env, napi_get_arraybuffer_info(env, bufferValue_##name, &name, &byteLength_##name));

#define GET_NAPI_PARAM_TYPED_ARRAY_FLOAT32(name, i) GET_NAPI_PARAM_TYPED_ARRAY(name, i, float, napi_float32_array, "Float32Array");
#define GET_NAPI_PARAM_TYPED_ARRAY_FLOAT64(name, i) GET_NAPI_PARAM_TYPED_ARRAY(name, i, double, napi_float64_array, "Float64Array");
#define GET_NAPI_PARAM_TYPED_ARRAY_INT32(name, i) GET_NAPI_PARAM_TYPED_ARRAY(name, i, int32_t, napi_int32_array, "Int32Array");


#define GET_NAPI_PARAM_ARRAY_BASE(name, i, cType, orgType, napiGetCall, readableType) \
    bool isArray_##name; \
    NAPI_CALL(env, napi_typeof(env, args[i], &valuetype)); \
    NAPI_CALL(env, napi_is_array(env, args[i], &isArray_##name)); \
    NAPI_ASSERT(env, valuetype == napi_object && isArray_##name, "Expected argument " #name "(" #i ") to be of type array<" readableType ">"); \
    uint32_t length_##name; \
    NAPI_CALL(env, napi_get_array_length(env, args[i], &length_##name)); \
    cType name[length_##name]; \
    napi_value singleValue_##name; \
    orgType single_##name; \
    for(uint32_t _i = 0; _i < length_##name; _i++){ \
        NAPI_CALL(env, napi_get_element(env, args[i], _i, &singleValue_##name)); \
        NAPI_CALL(env, napiGetCall(env, singleValue_##name, &single_##name)); \
        name[_i] = (cType)single_##name; \
    }

#define GET_NAPI_PARAM_GLENUM_NULLABLE(name, i) GET_NAPI_PARAM_BASE_NULLABLE(name, i, napi_number, uint32_t, napi_get_value_uint32, "number", 0);

#define GET_NAPI_PARAM_ARRAY_INT32(name, i) GET_NAPI_PARAM_ARRAY_BASE(name, i, int32_t, int32_t, napi_get_value_int32, "number");
#define GET_NAPI_PARAM_ARRAY_DOUBLE(name, i) GET_NAPI_PARAM_ARRAY_BASE(name, i, double, double, napi_get_value_double, "number");
#define GET_NAPI_PARAM_ARRAY_FLOAT(name, i) GET_NAPI_PARAM_ARRAY_BASE(name, i, float, double, napi_get_value_double, "number");

#define GET_NAPI_PARAM_INT64(name, i) GET_NAPI_PARAM_BASE(name, i, napi_number, int64_t, napi_get_value_int64, "number");
#define GET_NAPI_PARAM_INT32(name, i) GET_NAPI_PARAM_BASE(name, i, napi_number, int32_t, napi_get_value_int32, "number");
#define GET_NAPI_PARAM_UINT32(name, i) GET_NAPI_PARAM_BASE(name, i, napi_number, uint32_t, napi_get_value_uint32, "number");
#define GET_NAPI_PARAM_DOUBLE(name, i) GET_NAPI_PARAM_BASE(name, i, napi_number, double, napi_get_value_double, "number");
#define GET_NAPI_PARAM_BOOL(name, i) GET_NAPI_PARAM_BASE(name, i, napi_boolean, bool, napi_get_value_bool, "bool");

#define GET_NAPI_PARAM_GLENUM GET_NAPI_PARAM_UINT32

#define DECLARE_NAPI_METHOD(name) napi_value name(napi_env env, napi_callback_info info)

#define CALL_NAPI_FUNCTION_GLFW_CALLBACK(callbackRefName, argc, args) \
    napi_value nullValue; \
    napi_value callbackValue; \
    NAPI_CALL_RETURN_VOID(_env, napi_get_null(_env, &nullValue)); \
    NAPI_CALL_RETURN_VOID(_env, napi_get_reference_value(_env, callbackRefName, &callbackValue)); \
    NAPI_CALL_RETURN_VOID(_env, napi_call_function(_env, nullValue, callbackValue, argc, args, NULL));
