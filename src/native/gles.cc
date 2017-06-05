#include <iostream>
#include <node_api.h>

#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <common.h>

#include "scn_napi.h"

//#define LOAD_GLES_EXT

DECLARE_NAPI_METHOD(ActiveTexture){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_GLENUM(texture, 0);

    glActiveTexture(texture);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(AttachShader){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_UINT32(program, 0);
    GET_NAPI_PARAM_UINT32(shader, 1);

    glAttachShader(program, shader);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(BindAttribLocation){
    GET_NAPI_PARAMS_INFO(3);
    GET_NAPI_PARAM_UINT32(program, 0);
    GET_NAPI_PARAM_UINT32(index, 1);
    GET_NAPI_PARAM_STRING(name, 2);

    glBindAttribLocation(program, index, name);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(BindBuffer){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_UINT32(buffer, 1);

    glBindBuffer(target, buffer);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(BindFramebuffer){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_UINT32(framebuffer, 1);

    glBindFramebuffer(target, framebuffer);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(BindRenderbuffer){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_UINT32(renderbuffer, 1);

    glBindRenderbuffer(target, renderbuffer);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(BindTexture){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_GLENUM(texture, 1);

    glBindTexture(target, texture);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(BlendColor){
    GET_NAPI_PARAMS_INFO(4);
    GET_NAPI_PARAM_DOUBLE(red, 0);
    GET_NAPI_PARAM_DOUBLE(green, 1);
    GET_NAPI_PARAM_DOUBLE(blue, 2);
    GET_NAPI_PARAM_DOUBLE(alpha, 3);

    glBlendColor(red, green, blue, alpha);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(BlendEquation){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_GLENUM(mode, 0);

    glBlendEquation(mode);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(BlendEquationSeparate){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_GLENUM(modeRGB, 0);
    GET_NAPI_PARAM_GLENUM(modeAlpha, 1);

    glBlendEquationSeparate(modeRGB, modeAlpha);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(BlendFunc){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_GLENUM(sfactor, 0);
    GET_NAPI_PARAM_GLENUM(dfactor, 1);

    glBlendFunc(sfactor, dfactor);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(BlendFuncSeparate){
    GET_NAPI_PARAMS_INFO(4);
    GET_NAPI_PARAM_GLENUM(sfactorRGB, 0);
    GET_NAPI_PARAM_GLENUM(dfactorRGB, 1);
    GET_NAPI_PARAM_GLENUM(sfactorAlpha, 0);
    GET_NAPI_PARAM_GLENUM(dfactorAlpha, 1);

    glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
    RETURN_NAPI_UNDEFINED();
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(BufferData){
    GET_NAPI_PARAMS_INFO(3);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_GLENUM(usage, 2);

    NAPI_CALL(env, napi_typeof(env, args[1], &valuetype));
    bool isSize = valuetype == napi_number;
    bool isObject = valuetype == napi_object;
    NAPI_ASSERT(env, isSize || isObject, "Expected argument size/data(1) to be of type number or ArrayBuffer.");

    if(isObject){
        GET_NAPI_PARAM_ARRAY_BUFFER(data, 1);
        glBufferData(target, byteLength_data, data, usage);
    } else {
        int32_t size;
        NAPI_CALL(env, napi_get_value_int32(env, args[1], &size));
        glBufferData(target, size, NULL, usage);
    }

    RETURN_NAPI_UNDEFINED();
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(BufferSubData){
    GET_NAPI_PARAMS_INFO(3);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_INT32(offset, 1);
    GET_NAPI_PARAM_ARRAY_BUFFER(srcData, 2);

    glBufferSubData(target, offset, byteLength_srcData, srcData);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(CheckFramebufferStatus){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_GLENUM(target, 0);

    RETURN_NAPI_NUMBER(glCheckFramebufferStatus(target));
}

DECLARE_NAPI_METHOD(Clear){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(mask, 0);

    glClear(mask);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(ClearColor){
    GET_NAPI_PARAMS_INFO(4);
    GET_NAPI_PARAM_DOUBLE(red, 0);
    GET_NAPI_PARAM_DOUBLE(green, 1);
    GET_NAPI_PARAM_DOUBLE(blue, 2);
    GET_NAPI_PARAM_DOUBLE(alpha, 3);

    glClearColor(red, green, blue, alpha);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(ClearDepthf){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_DOUBLE(depth, 0);

    glClearDepthf(depth);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(ClearStencil){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_INT32(stencil, 0);

    glClearStencil(stencil);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(ColorMask){
    GET_NAPI_PARAMS_INFO(4);
    GET_NAPI_PARAM_BOOL(red, 0);
    GET_NAPI_PARAM_BOOL(green, 1);
    GET_NAPI_PARAM_BOOL(blue, 2);
    GET_NAPI_PARAM_BOOL(alpha, 3);

    glColorMask(red, green, blue, alpha);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(CompileShader){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(shader, 0);

    glCompileShader(shader);
    RETURN_NAPI_UNDEFINED();
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(CompressedTexImage2D){
    GET_NAPI_PARAMS_INFO(7);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_INT32(level, 1);
    GET_NAPI_PARAM_GLENUM(internalformat, 2);
    GET_NAPI_PARAM_INT32(width, 3);
    GET_NAPI_PARAM_INT32(height, 4);
    GET_NAPI_PARAM_INT32(border, 5);
    GET_NAPI_PARAM_ARRAY_BUFFER(data, 6);

    glCompressedTexImage2D(target, level, internalformat, width, height, border, byteLength_data, data);
    RETURN_NAPI_UNDEFINED();
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(CompressedTexSubImage2D){
    GET_NAPI_PARAMS_INFO(7);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_INT32(level, 1);
    GET_NAPI_PARAM_INT32(xoffset, 2);
    GET_NAPI_PARAM_INT32(yoffset, 3);
    GET_NAPI_PARAM_INT32(width, 4);
    GET_NAPI_PARAM_INT32(height, 5);
    GET_NAPI_PARAM_GLENUM(format, 6);
    GET_NAPI_PARAM_ARRAY_BUFFER(data, 7);

    glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, byteLength_data, data);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(CopyTexImage2D){
    GET_NAPI_PARAMS_INFO(8);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_INT32(level, 1);
    GET_NAPI_PARAM_GLENUM(internalformat, 2);
    GET_NAPI_PARAM_INT32(x, 3);
    GET_NAPI_PARAM_INT32(y, 4);
    GET_NAPI_PARAM_INT32(width, 5);
    GET_NAPI_PARAM_INT32(height, 6);
    GET_NAPI_PARAM_INT32(border, 7);

    glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(CopyTexSubImage2D){
    GET_NAPI_PARAMS_INFO(8);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_INT32(level, 1);
    GET_NAPI_PARAM_INT32(xoffset, 2);
    GET_NAPI_PARAM_INT32(yoffset, 3);
    GET_NAPI_PARAM_INT32(x, 4);
    GET_NAPI_PARAM_INT32(y, 5);
    GET_NAPI_PARAM_INT32(width, 6);
    GET_NAPI_PARAM_INT32(height, 7);

    glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
    RETURN_NAPI_UNDEFINED();
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(CreateBuffer){
    GLuint buffer;

    glGenBuffers(1, &buffer);
    RETURN_NAPI_NUMBER(buffer);
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(CreateFramebuffer){
    GLuint buffer;

    glGenFramebuffers(1, &buffer);
    RETURN_NAPI_NUMBER(buffer);
}

DECLARE_NAPI_METHOD(CreateProgram){
    RETURN_NAPI_NUMBER(glCreateProgram());
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(CreateRenderbuffer){
    GLuint buffer;

    glGenRenderbuffers(1, &buffer);
    RETURN_NAPI_NUMBER(buffer);
}

DECLARE_NAPI_METHOD(CreateShader){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_GLENUM(type, 0);

    RETURN_NAPI_NUMBER(glCreateShader(type));
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(CreateTexture){
    GLuint texture;

    glGenTextures(1, &texture);
    RETURN_NAPI_NUMBER(texture);
}

DECLARE_NAPI_METHOD(CullFace){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_GLENUM(mode, 0);

    glCullFace(mode);
    RETURN_NAPI_UNDEFINED();
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(DeleteBuffer){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(buffer, 0);

    glDeleteBuffers(1, &buffer);
    RETURN_NAPI_UNDEFINED();
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(DeleteFramebuffer){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(buffer, 0);

    glDeleteFramebuffers(1, &buffer);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(DeleteProgram){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(program, 0);

    glDeleteProgram(program);
    RETURN_NAPI_UNDEFINED();
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(DeleteRenderbuffer){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(buffer, 0);

    glDeleteRenderbuffers(1, &buffer);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(DeleteShader){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(shader, 0);

    glDeleteShader(shader);
    RETURN_NAPI_UNDEFINED();
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(DeleteTexture){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(texture, 0);

    glDeleteTextures(1, &texture);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(DepthFunc){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_GLENUM(func, 0);

    glDepthFunc(func);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(DepthMask){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_BOOL(mask, 0);

    glDepthMask(mask);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(DepthRangef){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_DOUBLE(n, 0);
    GET_NAPI_PARAM_DOUBLE(f, 1);

    glDepthRangef(n, f);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(DetachShader){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_UINT32(program, 0);
    GET_NAPI_PARAM_UINT32(shader, 1);

    glDetachShader(program, shader);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(Disable){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_GLENUM(cap, 0);

    glDisable(cap);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(DisableVertexAttribArray){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(index, 0);

    glDisableVertexAttribArray(index);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(DrawArrays){
    GET_NAPI_PARAMS_INFO(3);
    GET_NAPI_PARAM_GLENUM(mode, 0);
    GET_NAPI_PARAM_INT32(first, 1);
    GET_NAPI_PARAM_INT32(count, 2);

    glDrawArrays(mode, first, count);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(DrawElements){
    GET_NAPI_PARAMS_INFO(4);
    GET_NAPI_PARAM_GLENUM(mode, 0);
    GET_NAPI_PARAM_INT32(count, 1);
    GET_NAPI_PARAM_GLENUM(type, 2);
    GET_NAPI_PARAM_UINT32(_offset, 3);
    GLvoid *offset = reinterpret_cast<GLvoid*>(_offset);

    glDrawElements(mode, count, type, offset);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(Enable){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_GLENUM(cap, 0);

    glEnable(cap);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(EnableVertexAttribArray){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(index, 0);

    glEnableVertexAttribArray(index);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(Finish){
    glFinish();
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(Flush){
    glFlush();
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(FramebufferRenderbuffer){
    GET_NAPI_PARAMS_INFO(4);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_GLENUM(attachment, 1);
    GET_NAPI_PARAM_GLENUM(renderbuffertarget, 2);
    GET_NAPI_PARAM_UINT32(renderbuffer, 3);

    glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(FramebufferTexture2D){
    GET_NAPI_PARAMS_INFO(5);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_GLENUM(attachment, 1);
    GET_NAPI_PARAM_GLENUM(textarget, 2);
    GET_NAPI_PARAM_UINT32(texture, 3);
    GET_NAPI_PARAM_UINT32(level, 4);

    glFramebufferTexture2D(target, attachment, textarget, texture, level);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(FrontFace){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_GLENUM(mode, 0);

    glFrontFace(mode);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(GenerateMipmap){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_GLENUM(target, 0);

    glGenerateMipmap(target);
    RETURN_NAPI_UNDEFINED();
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetActiveAttrib){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_UINT32(program, 0);
    GET_NAPI_PARAM_UINT32(index, 1);

    char name[1024];
    GLsizei length = 0;
    GLenum type;
    GLsizei size;
    glGetActiveAttrib(program, index, 1024, &length, &size, &type, name);

    RETURN_NAPI_GL_ACTIVE_INFO(name, size, type);
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetActiveUniform){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_UINT32(program, 0);
    GET_NAPI_PARAM_UINT32(index, 1);

    char name[1024];
    GLsizei length = 0;
    GLenum type;
    GLsizei size;
    glGetActiveUniform(program, index, 1024, &length, &size, &type, name);

    RETURN_NAPI_GL_ACTIVE_INFO(name, size, type);
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetAttachedShaders){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(program, 0);


    GLuint shaders[1024];
    GLsizei count;
    glGetAttachedShaders(program, 1024, &count, shaders);

    RETURN_NAPI_ARRAY_NUMBER(shaders, count);
}

DECLARE_NAPI_METHOD(GetAttribLocation){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_UINT32(program, 0);
    GET_NAPI_PARAM_STRING(name, 1);

    RETURN_NAPI_NUMBER(glGetAttribLocation(program, name));
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetBooleanv){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_GLENUM(pname, 0);

    GLboolean ret;
    glGetBooleanv(pname, &ret);
    RETURN_NAPI_BOOL(ret);
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetBufferParameteriv){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_GLENUM(pname, 1);

    GLint ret;
    glGetBufferParameteriv(target, pname, &ret);
    RETURN_NAPI_NUMBER(ret);
}

DECLARE_NAPI_METHOD(GetError){
    RETURN_NAPI_NUMBER(glGetError());
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetFloatv){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_GLENUM(pname, 0);

    GLfloat ret;
    glGetFloatv(pname, &ret);
    RETURN_NAPI_NUMBER(ret);
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetFramebufferAttachmentParameteriv){
    GET_NAPI_PARAMS_INFO(3);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_GLENUM(attachment, 1);
    GET_NAPI_PARAM_GLENUM(pname, 2);

    GLint ret;
    glGetFramebufferAttachmentParameteriv(target, attachment, pname, &ret);
    RETURN_NAPI_NUMBER(ret);
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetIntegerv){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_GLENUM(pname, 0);

    GLint ret;
    glGetIntegerv(pname, &ret);
    RETURN_NAPI_NUMBER(ret);
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetProgramiv){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(program, 0);
    GET_NAPI_PARAM_GLENUM(pname, 1);

    GLint ret;
    glGetProgramiv(program, pname, &ret);
    RETURN_NAPI_NUMBER(ret);
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetProgramInfoLog){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(program, 0);

    int len = 1024;
    char error[1024];
    glGetProgramInfoLog(program, 1024, &len, error);
    RETURN_NAPI_STRING(error);
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetRenderbufferParameteriv){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_GLENUM(pname, 1);

    GLint ret;
    glGetRenderbufferParameteriv(target, pname, &ret);
    RETURN_NAPI_NUMBER(ret);
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetShaderiv){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_UINT32(shader, 0);
    GET_NAPI_PARAM_GLENUM(pname, 1);

    GLint ret;
    glGetShaderiv(shader, pname, &ret);
    RETURN_NAPI_NUMBER(ret);
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetShaderInfoLog){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(shader, 0);

    int len = 1024;
    char error[1024];
    glGetShaderInfoLog(shader, 1024, &len, error);
    RETURN_NAPI_STRING(error);
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetShaderPrecisionFormat){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_GLENUM(shadertype, 0);
    GET_NAPI_PARAM_GLENUM(precisiontype, 1);

    GLint* range = new GLint[2];
    GLint precision;
    glGetShaderPrecisionFormat(shadertype, precisiontype, range, &precision);


    napi_value val;
    napi_value returnValue;
    NAPI_CALL(env, napi_create_object(env, &returnValue));
    NAPI_CALL(env, napi_create_number(env, range[0], &val));
    NAPI_CALL(env, napi_set_named_property(env, returnValue, "rangeMin", val));
    NAPI_CALL(env, napi_create_number(env, range[1], &val));
    NAPI_CALL(env, napi_set_named_property(env, returnValue, "rangeMax", val));
    NAPI_CALL(env, napi_create_number(env, precision, &val));
    NAPI_CALL(env, napi_set_named_property(env, returnValue, "precision", val));
    return returnValue;
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetShaderSource){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_GLENUM(shader, 0);

    GLint len;
    glGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH, &len);
    GLchar* source = new GLchar[len];
    glGetShaderSource(shader, len, NULL, source);
    RETURN_NAPI_STRING(source);
}

DECLARE_NAPI_METHOD(GetString){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_GLENUM(name, 0);

    RETURN_NAPI_STRING((char*)glGetString(name));
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetTexParameterfv){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_GLENUM(pname, 1);

    GLfloat ret;
    glGetTexParameterfv(target, pname, &ret);
    RETURN_NAPI_NUMBER(ret);
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetTexParameteriv){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_GLENUM(pname, 1);

    GLint ret;
    glGetTexParameteriv(target, pname, &ret);
    RETURN_NAPI_NUMBER(ret);
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetUniformfv){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_UINT32(program, 0);
    GET_NAPI_PARAM_INT32(location, 1);

    GLfloat ret;
    glGetUniformfv(program, location, &ret);
    RETURN_NAPI_NUMBER(ret);
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetUniformiv){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_UINT32(program, 0);
    GET_NAPI_PARAM_INT32(location, 1);

    GLint ret;
    glGetUniformiv(program, location, &ret);
    RETURN_NAPI_NUMBER(ret);
}

DECLARE_NAPI_METHOD(GetUniformLocation){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_UINT32(program, 0);
    GET_NAPI_PARAM_STRING(name, 1);

    RETURN_NAPI_NUMBER(glGetUniformLocation(program, name));
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetVertexAttribfv){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_UINT32(index, 0);
    GET_NAPI_PARAM_GLENUM(pname, 1);

    GLfloat ret;
    glGetVertexAttribfv(index, pname, &ret);
    RETURN_NAPI_NUMBER(ret);
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetVertexAttribiv){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_UINT32(index, 0);
    GET_NAPI_PARAM_GLENUM(pname, 1);

    GLint ret;
    glGetVertexAttribiv(index, pname, &ret);
    RETURN_NAPI_NUMBER(ret);
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(GetVertexAttribPointerv){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_UINT32(index, 0);
    GET_NAPI_PARAM_GLENUM(pname, 1);

    void* ret = NULL;
    glGetVertexAttribPointerv(index, pname, &ret);
    RETURN_NAPI_NUMBER(static_cast<GLuint>(reinterpret_cast<size_t>(ret)));
}

DECLARE_NAPI_METHOD(Hint){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_GLENUM(mode, 1);

    glHint(target, mode);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(IsBuffer){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(buffer, 0);

    RETURN_NAPI_BOOL(glIsBuffer(buffer));
}

DECLARE_NAPI_METHOD(IsEnabled){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_GLENUM(cap, 0);

    RETURN_NAPI_BOOL(glIsEnabled(cap));
}

DECLARE_NAPI_METHOD(IsFramebuffer){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(framebuffer, 0);

    RETURN_NAPI_BOOL(glIsFramebuffer(framebuffer));
}

DECLARE_NAPI_METHOD(IsProgram){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(program, 0);

    RETURN_NAPI_BOOL(glIsProgram(program));
}

DECLARE_NAPI_METHOD(IsRenderbuffer){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(renderbuffer, 0);

    RETURN_NAPI_BOOL(glIsRenderbuffer(renderbuffer));
}

DECLARE_NAPI_METHOD(IsShader){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(shader, 0);

    RETURN_NAPI_BOOL(glIsShader(shader));
}

DECLARE_NAPI_METHOD(IsTexture){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(texture, 0);

    RETURN_NAPI_BOOL(glIsTexture(texture));
}

DECLARE_NAPI_METHOD(LineWidth){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_DOUBLE(width, 0);

    glLineWidth(width);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(LinkProgram){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(program, 0);

    glLinkProgram(program);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(PixelStorei){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_GLENUM(pname, 0);
    GET_NAPI_PARAM_INT32(param, 1);

    glPixelStorei(pname, param);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(PolygonOffset){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_DOUBLE(factor, 0);
    GET_NAPI_PARAM_DOUBLE(units, 1);

    glPolygonOffset(factor, units);
    RETURN_NAPI_UNDEFINED();
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(ReadPixels){
    GET_NAPI_PARAMS_INFO(7);
    GET_NAPI_PARAM_UINT32(x, 0);
    GET_NAPI_PARAM_UINT32(y, 1);
    GET_NAPI_PARAM_UINT32(width, 2);
    GET_NAPI_PARAM_UINT32(height, 3);
    GET_NAPI_PARAM_GLENUM(format, 4);
    GET_NAPI_PARAM_GLENUM(type, 5);
    GET_NAPI_PARAM_ARRAY_BUFFER(pixels, 6);

    glReadPixels(x, y, width, height, format, type, pixels);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(ReleaseShaderCompiler){
    glReleaseShaderCompiler();
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(RenderbufferStorage){
    GET_NAPI_PARAMS_INFO(4);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_GLENUM(internalformat, 1);
    GET_NAPI_PARAM_UINT32(width, 2);
    GET_NAPI_PARAM_UINT32(height, 3);

    glRenderbufferStorage(target, internalformat, width, height);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(SampleCoverage){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_GLENUM(value, 0);
    GET_NAPI_PARAM_BOOL(invert, 1);

    glSampleCoverage(value, invert);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(Scissor){
    GET_NAPI_PARAMS_INFO(4);
    GET_NAPI_PARAM_INT32(x, 0);
    GET_NAPI_PARAM_INT32(y, 1);
    GET_NAPI_PARAM_INT32(width, 2);
    GET_NAPI_PARAM_INT32(height, 3);

    glScissor(x, y, width, height);
    RETURN_NAPI_UNDEFINED();
}

// WEBGL1-COMPAT
DECLARE_NAPI_METHOD(ShaderSource){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_INT32(shader, 0);
    GET_NAPI_PARAM_STRING(code, 1);

    const char* codes[1];
    codes[0] = code;
    GLint length = bufferSize_code;
    glShaderSource(shader, 1, codes, &length);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(StencilFunc){
    GET_NAPI_PARAMS_INFO(3);
    GET_NAPI_PARAM_GLENUM(func, 0);
    GET_NAPI_PARAM_INT32(ref, 1);
    GET_NAPI_PARAM_UINT32(mask, 2);

    glStencilFunc(func, ref, mask);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(StencilFuncSeparate){
    GET_NAPI_PARAMS_INFO(4);
    GET_NAPI_PARAM_GLENUM(face, 0);
    GET_NAPI_PARAM_GLENUM(func, 1);
    GET_NAPI_PARAM_INT32(ref, 2);
    GET_NAPI_PARAM_UINT32(mask, 3);

    glStencilFuncSeparate(face, func, ref, mask);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(StencilMask){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_UINT32(mask, 0);

    glStencilMask(mask);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(StencilMaskSeparate){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_GLENUM(face, 0);
    GET_NAPI_PARAM_UINT32(mask, 1);

    glStencilMaskSeparate(face, mask);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(StencilOp){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_GLENUM(fail, 0);
    GET_NAPI_PARAM_GLENUM(zfail, 1);
    GET_NAPI_PARAM_GLENUM(zpass, 2);

    glStencilOp(fail, zfail, zpass);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(StencilOpSeparate){
    GET_NAPI_PARAMS_INFO(4);
    GET_NAPI_PARAM_GLENUM(face, 0);
    GET_NAPI_PARAM_GLENUM(sfail, 1);
    GET_NAPI_PARAM_GLENUM(dpfail, 2);
    GET_NAPI_PARAM_GLENUM(dppass, 3);

    glStencilOpSeparate(face, sfail, dpfail, dppass);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(TexImage2D){
    GET_NAPI_PARAMS_INFO(9);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_INT32(level, 1);
    GET_NAPI_PARAM_INT32(internalformat, 2);
    GET_NAPI_PARAM_INT32(width, 3);
    GET_NAPI_PARAM_INT32(height, 4);
    GET_NAPI_PARAM_INT32(border, 5);
    GET_NAPI_PARAM_GLENUM(format, 6);
    GET_NAPI_PARAM_GLENUM(type, 7);
    GET_NAPI_PARAM_ARRAY_BUFFER(pixels, 8);

    glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(TexParameterf){
    GET_NAPI_PARAMS_INFO(3);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_GLENUM(pname, 1);
    GET_NAPI_PARAM_DOUBLE(param, 2);

    glTexParameterf(target, pname, param);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(TexParameteri){
    GET_NAPI_PARAMS_INFO(3);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_GLENUM(pname, 1);
    GET_NAPI_PARAM_INT32(param, 2);

    glTexParameteri(target, pname, param);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(TexSubImage2D){
    GET_NAPI_PARAMS_INFO(9);
    GET_NAPI_PARAM_GLENUM(target, 0);
    GET_NAPI_PARAM_INT32(level, 1);
    GET_NAPI_PARAM_INT32(xoffset, 2);
    GET_NAPI_PARAM_INT32(yoffset, 3);
    GET_NAPI_PARAM_INT32(width, 4);
    GET_NAPI_PARAM_INT32(height, 5);
    GET_NAPI_PARAM_GLENUM(format, 6);
    GET_NAPI_PARAM_GLENUM(type, 7);
    GET_NAPI_PARAM_ARRAY_BUFFER(pixels, 8);

    glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(Uniform1f){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_INT32(location, 0);
    GET_NAPI_PARAM_DOUBLE(v0, 1);

    glUniform1f(location, v0);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(Uniform1fv){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_INT32(location, 0);
    GET_NAPI_PARAM_TYPED_ARRAY_FLOAT32(values, 1);

    glUniform1fv(location, length_values, (float*)values);

    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(Uniform1i){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_INT32(location, 0);
    GET_NAPI_PARAM_INT32(v0, 1);

    glUniform1i(location, v0);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(Uniform1iv){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_INT32(location, 0);
    GET_NAPI_PARAM_TYPED_ARRAY_INT32(values, 1);

    glUniform1iv(location, length_values, (int32_t*)values);
    RETURN_NAPI_UNDEFINED();
}






void _ModuleInit(napi_env env, napi_value exports, napi_value module, void* priv){
    napi_property_descriptor desc;
    napi_value val;

    // GLES 2.0 functions
    EXPORT_NAPI_METHOD("activeTexture", ActiveTexture);
    EXPORT_NAPI_METHOD("attachShader", AttachShader);

    EXPORT_NAPI_METHOD("bindAttribLocation", BindAttribLocation);
    EXPORT_NAPI_METHOD("bindBuffer", BindBuffer);
    EXPORT_NAPI_METHOD("bindFramebuffer", BindFramebuffer);
    EXPORT_NAPI_METHOD("bindRenderbuffer", BindRenderbuffer);
    EXPORT_NAPI_METHOD("bindTexture", BindTexture);
    EXPORT_NAPI_METHOD("blendColor", BlendColor);
    EXPORT_NAPI_METHOD("blendEquation", BlendEquation);
    EXPORT_NAPI_METHOD("blendEquationSeparate", BlendEquationSeparate);
    EXPORT_NAPI_METHOD("blendFunc", BlendFunc);
    EXPORT_NAPI_METHOD("blendFuncSeparate", BlendFuncSeparate);
    EXPORT_NAPI_METHOD("bufferData", BufferData);
    EXPORT_NAPI_METHOD("bufferSubData", BufferSubData);

    // WEBGL1-COMPAT:
    // createBuffer, createFramebuffer, createRenderbuffer, createTexture => single buffer
    EXPORT_NAPI_METHOD("checkFramebufferStatus", CheckFramebufferStatus);
    EXPORT_NAPI_METHOD("clear", Clear);
    EXPORT_NAPI_METHOD("clearColor", ClearColor);
    EXPORT_NAPI_METHOD("clearDepthf", ClearDepthf);
    EXPORT_NAPI_METHOD("clearStencil", ClearStencil);
    EXPORT_NAPI_METHOD("colorMask", ColorMask);
    EXPORT_NAPI_METHOD("compileShader", CompileShader);
    EXPORT_NAPI_METHOD("compressedTexImage2D", CompressedTexImage2D);
    EXPORT_NAPI_METHOD("compressedTexSubImage2D", CompressedTexSubImage2D);
    EXPORT_NAPI_METHOD("copyTexImage2D", CopyTexImage2D);
    EXPORT_NAPI_METHOD("copyTexSubImage2D", CopyTexSubImage2D);
    EXPORT_NAPI_METHOD("createBuffer", CreateBuffer);
    EXPORT_NAPI_METHOD("createFramebuffer", CreateFramebuffer);
    EXPORT_NAPI_METHOD("createProgram", CreateProgram);
    EXPORT_NAPI_METHOD("createRenderbuffer", CreateRenderbuffer);
    EXPORT_NAPI_METHOD("createShader", CreateShader);
    EXPORT_NAPI_METHOD("createTexture", CreateTexture);
    EXPORT_NAPI_METHOD("cullFace", CullFace);

    // WEBGL1-COMPAT:
    // glDeleteBuffers, glDeleteFramebuffers, glDeleteRenderbuffers, glDeleteTextures => single buffer
    EXPORT_NAPI_METHOD("deleteBuffer", DeleteBuffer);
    EXPORT_NAPI_METHOD("deleteFramebuffer", DeleteFramebuffer);
    EXPORT_NAPI_METHOD("deleteProgram", DeleteProgram);
    EXPORT_NAPI_METHOD("deleteRenderbuffer", DeleteRenderbuffer);
    EXPORT_NAPI_METHOD("deleteShader", DeleteShader);
    EXPORT_NAPI_METHOD("deleteTexture", DeleteTexture);
    EXPORT_NAPI_METHOD("depthFunc", DepthFunc);
    EXPORT_NAPI_METHOD("depthMask", DepthMask);
    EXPORT_NAPI_METHOD("depthRangef", DepthRangef);
    EXPORT_NAPI_METHOD("detachShader", DetachShader);
    EXPORT_NAPI_METHOD("disable", Disable);
    EXPORT_NAPI_METHOD("disableVertexAttribArray", DisableVertexAttribArray);
    EXPORT_NAPI_METHOD("drawArrays", DrawArrays);
    EXPORT_NAPI_METHOD("drawElements", DrawElements);

    EXPORT_NAPI_METHOD("enable", Enable);
    EXPORT_NAPI_METHOD("enableVertexAttribArray", EnableVertexAttribArray);

    EXPORT_NAPI_METHOD("finish", Finish);
    EXPORT_NAPI_METHOD("flush", Flush);
    EXPORT_NAPI_METHOD("framebufferRenderbuffer", FramebufferRenderbuffer);
    EXPORT_NAPI_METHOD("framebufferTexture2D", FramebufferTexture2D);
    EXPORT_NAPI_METHOD("frontFace", FrontFace);

    // WEBGL1-COMPAT:
    // no glGen*-functions (see create*)
    EXPORT_NAPI_METHOD("generateMipmap", GenerateMipmap);
    EXPORT_NAPI_METHOD("getActiveAttrib", GetActiveAttrib);
    EXPORT_NAPI_METHOD("getActiveUniform", GetActiveUniform);
    EXPORT_NAPI_METHOD("getAttachedShaders", GetAttachedShaders);
    EXPORT_NAPI_METHOD("getAttribLocation", GetAttribLocation);
    EXPORT_NAPI_METHOD("getBooleanv", GetBooleanv);
    EXPORT_NAPI_METHOD("getBufferParameteriv", GetBufferParameteriv);
    EXPORT_NAPI_METHOD("getError", GetError);
    EXPORT_NAPI_METHOD("getFloatv", GetFloatv);
    EXPORT_NAPI_METHOD("getFramebufferAttachmentParameteriv", GetFramebufferAttachmentParameteriv);
    EXPORT_NAPI_METHOD("getIntegerv", GetIntegerv);
    EXPORT_NAPI_METHOD("getProgramiv", GetProgramiv);
    EXPORT_NAPI_METHOD("getProgramInfoLog", GetProgramInfoLog);
    EXPORT_NAPI_METHOD("getRenderbufferParameteriv", GetRenderbufferParameteriv);
    EXPORT_NAPI_METHOD("getShaderiv", GetShaderiv);
    EXPORT_NAPI_METHOD("getShaderInfoLog", GetShaderInfoLog);
    EXPORT_NAPI_METHOD("getShaderPrecisionFormat", GetShaderPrecisionFormat);
    EXPORT_NAPI_METHOD("getShaderSource", GetShaderSource);
    EXPORT_NAPI_METHOD("getString", GetString);
    EXPORT_NAPI_METHOD("getTexParameterfv", GetTexParameterfv);
    EXPORT_NAPI_METHOD("getTexParameteriv", GetTexParameteriv);
    EXPORT_NAPI_METHOD("getUniformfv", GetUniformfv);
    EXPORT_NAPI_METHOD("getUniformiv", GetUniformiv);
    EXPORT_NAPI_METHOD("getUniformLocation", GetUniformLocation);
    EXPORT_NAPI_METHOD("getVertexAttribfv", GetVertexAttribfv);
    EXPORT_NAPI_METHOD("getVertexAttribiv", GetVertexAttribiv);
    EXPORT_NAPI_METHOD("getVertexAttribPointerv", GetVertexAttribPointerv);

    EXPORT_NAPI_METHOD("hint", Hint);

    EXPORT_NAPI_METHOD("isBuffer", IsBuffer);
    EXPORT_NAPI_METHOD("isEnabled", IsEnabled);
    EXPORT_NAPI_METHOD("isFramebuffer", IsFramebuffer);
    EXPORT_NAPI_METHOD("isProgram", IsProgram);
    EXPORT_NAPI_METHOD("isRenderbuffer", IsRenderbuffer);
    EXPORT_NAPI_METHOD("isShader", IsShader);
    EXPORT_NAPI_METHOD("isTexture", IsTexture);

    EXPORT_NAPI_METHOD("lineWidth", LineWidth);
    EXPORT_NAPI_METHOD("linkProgram", LinkProgram);

    EXPORT_NAPI_METHOD("pixelStorei", PixelStorei);
    EXPORT_NAPI_METHOD("polygonOffset", PolygonOffset);

    EXPORT_NAPI_METHOD("readPixels", ReadPixels);
    EXPORT_NAPI_METHOD("releaseShaderCompiler", ReleaseShaderCompiler);
    EXPORT_NAPI_METHOD("renderbufferStorage", RenderbufferStorage);

    EXPORT_NAPI_METHOD("sampleCoverage", SampleCoverage);
    EXPORT_NAPI_METHOD("scissor", Scissor);
    //#EXPORT_NAPI_METHOD("shaderBinary", ShaderBinary); - needed?
    EXPORT_NAPI_METHOD("shaderSource", ShaderSource);
    EXPORT_NAPI_METHOD("stencilFunc", StencilFunc);
    EXPORT_NAPI_METHOD("stencilFuncSeparate", StencilFuncSeparate);
    EXPORT_NAPI_METHOD("stencilMask", StencilMask);
    EXPORT_NAPI_METHOD("stencilMaskSeparate", StencilMaskSeparate);
    EXPORT_NAPI_METHOD("stencilOp", StencilOp);
    EXPORT_NAPI_METHOD("stencilOpSeparate", StencilOpSeparate);

    EXPORT_NAPI_METHOD("texImage2D", TexImage2D);
    EXPORT_NAPI_METHOD("texParameterf", TexParameterf);
    //#EXPORT_NAPI_METHOD("texParameterfv", TexParameterfv); - needed?
    EXPORT_NAPI_METHOD("texParameteri", TexParameteri);
    //#EXPORT_NAPI_METHOD("texParameteriv", TexParameteriv); - needed?
    EXPORT_NAPI_METHOD("texSubImage2D", TexSubImage2D);

    EXPORT_NAPI_METHOD("uniform1f", Uniform1f);
    EXPORT_NAPI_METHOD("uniform1fv", Uniform1fv);
    EXPORT_NAPI_METHOD("uniform1i", Uniform1i);
    EXPORT_NAPI_METHOD("uniform1iv", Uniform1iv);
    //EXPORT_NAPI_METHOD("uniform2f", Uniform2f);
    //EXPORT_NAPI_METHOD("uniform2fv", Uniform2fv);
    //EXPORT_NAPI_METHOD("uniform2i", Uniform2i);
    //EXPORT_NAPI_METHOD("uniform2iv", Uniform2iv);
    //EXPORT_NAPI_METHOD("uniform3f", Uniform3f);
    //EXPORT_NAPI_METHOD("uniform3fv", Uniform3fv);
    //EXPORT_NAPI_METHOD("uniform3i", Uniform3i);
    //EXPORT_NAPI_METHOD("uniform3iv", Uniform3iv);
    //EXPORT_NAPI_METHOD("uniform4f", Uniform4f);
    //EXPORT_NAPI_METHOD("uniform4fv", Uniform4fv);
    //EXPORT_NAPI_METHOD("uniform4i", Uniform4i);
    //EXPORT_NAPI_METHOD("uniform4iv", Uniform4iv);
    //EXPORT_NAPI_METHOD("uniformMatrix2fv", UniformMatrix2fv);
    //EXPORT_NAPI_METHOD("uniformMatrix3fv", UniformMatrix3fv);
    //EXPORT_NAPI_METHOD("uniformMatrix4fv", UniformMatrix4fv);
    //EXPORT_NAPI_METHOD("useProgram", UseProgram);

    //EXPORT_NAPI_METHOD("validateProgram", ValidateProgram);
    //EXPORT_NAPI_METHOD("vertexAttrib1f", VertexAttrib1f);
    //EXPORT_NAPI_METHOD("vertexAttrib1fv", VertexAttrib1fv);
    //EXPORT_NAPI_METHOD("vertexAttrib2f", VertexAttrib2f);
    //EXPORT_NAPI_METHOD("vertexAttrib2fv", VertexAttrib2fv);
    //EXPORT_NAPI_METHOD("vertexAttrib3f", VertexAttrib3f);
    //EXPORT_NAPI_METHOD("vertexAttrib3fv", VertexAttrib3fv);
    //EXPORT_NAPI_METHOD("vertexAttrib4f", VertexAttrib4f);
    //EXPORT_NAPI_METHOD("vertexAttrib4fv", VertexAttrib4fv);
    //EXPORT_NAPI_METHOD("vertexAttribPointer", VertexAttribPointer);
    //EXPORT_NAPI_METHOD("viewport", Viewport);

    // GLES 3.0 functions



    // consts
    EXPORT_NAPI_CONST_GL(DEPTH_BUFFER_BIT);
    EXPORT_NAPI_CONST_GL(STENCIL_BUFFER_BIT);
    EXPORT_NAPI_CONST_GL(COLOR_BUFFER_BIT);
    EXPORT_NAPI_CONST_GL(FALSE);
    EXPORT_NAPI_CONST_GL(TRUE);
    EXPORT_NAPI_CONST_GL(POINTS);
    EXPORT_NAPI_CONST_GL(LINES);
    EXPORT_NAPI_CONST_GL(LINE_LOOP);
    EXPORT_NAPI_CONST_GL(LINE_STRIP);
    EXPORT_NAPI_CONST_GL(TRIANGLES);
    EXPORT_NAPI_CONST_GL(TRIANGLE_STRIP);
    EXPORT_NAPI_CONST_GL(TRIANGLE_FAN);
    EXPORT_NAPI_CONST_GL(ZERO);
    EXPORT_NAPI_CONST_GL(ONE);
    EXPORT_NAPI_CONST_GL(SRC_COLOR);
    EXPORT_NAPI_CONST_GL(ONE_MINUS_SRC_COLOR);
    EXPORT_NAPI_CONST_GL(SRC_ALPHA);
    EXPORT_NAPI_CONST_GL(ONE_MINUS_SRC_ALPHA);
    EXPORT_NAPI_CONST_GL(DST_ALPHA);
    EXPORT_NAPI_CONST_GL(ONE_MINUS_DST_ALPHA);
    EXPORT_NAPI_CONST_GL(DST_COLOR);
    EXPORT_NAPI_CONST_GL(ONE_MINUS_DST_COLOR);
    EXPORT_NAPI_CONST_GL(SRC_ALPHA_SATURATE);
    EXPORT_NAPI_CONST_GL(FUNC_ADD);
    EXPORT_NAPI_CONST_GL(BLEND_EQUATION);
    EXPORT_NAPI_CONST_GL(BLEND_EQUATION_RGB);
    EXPORT_NAPI_CONST_GL(BLEND_EQUATION_ALPHA);
    EXPORT_NAPI_CONST_GL(FUNC_SUBTRACT);
    EXPORT_NAPI_CONST_GL(FUNC_REVERSE_SUBTRACT);
    EXPORT_NAPI_CONST_GL(BLEND_DST_RGB);
    EXPORT_NAPI_CONST_GL(BLEND_SRC_RGB);
    EXPORT_NAPI_CONST_GL(BLEND_DST_ALPHA);
    EXPORT_NAPI_CONST_GL(BLEND_SRC_ALPHA);
    EXPORT_NAPI_CONST_GL(CONSTANT_COLOR);
    EXPORT_NAPI_CONST_GL(ONE_MINUS_CONSTANT_COLOR);
    EXPORT_NAPI_CONST_GL(CONSTANT_ALPHA);
    EXPORT_NAPI_CONST_GL(ONE_MINUS_CONSTANT_ALPHA);
    EXPORT_NAPI_CONST_GL(BLEND_COLOR);
    EXPORT_NAPI_CONST_GL(ARRAY_BUFFER);
    EXPORT_NAPI_CONST_GL(ELEMENT_ARRAY_BUFFER);
    EXPORT_NAPI_CONST_GL(ARRAY_BUFFER_BINDING);
    EXPORT_NAPI_CONST_GL(ELEMENT_ARRAY_BUFFER_BINDING);
    EXPORT_NAPI_CONST_GL(STREAM_DRAW);
    EXPORT_NAPI_CONST_GL(STATIC_DRAW);
    EXPORT_NAPI_CONST_GL(DYNAMIC_DRAW);
    EXPORT_NAPI_CONST_GL(BUFFER_SIZE);
    EXPORT_NAPI_CONST_GL(BUFFER_USAGE);
    EXPORT_NAPI_CONST_GL(CURRENT_VERTEX_ATTRIB);
    EXPORT_NAPI_CONST_GL(FRONT);
    EXPORT_NAPI_CONST_GL(BACK);
    EXPORT_NAPI_CONST_GL(FRONT_AND_BACK);
    EXPORT_NAPI_CONST_GL(TEXTURE_2D);
    EXPORT_NAPI_CONST_GL(CULL_FACE);
    EXPORT_NAPI_CONST_GL(BLEND);
    EXPORT_NAPI_CONST_GL(DITHER);
    EXPORT_NAPI_CONST_GL(STENCIL_TEST);
    EXPORT_NAPI_CONST_GL(DEPTH_TEST);
    EXPORT_NAPI_CONST_GL(SCISSOR_TEST);
    EXPORT_NAPI_CONST_GL(POLYGON_OFFSET_FILL);
    EXPORT_NAPI_CONST_GL(SAMPLE_ALPHA_TO_COVERAGE);
    EXPORT_NAPI_CONST_GL(SAMPLE_COVERAGE);
    EXPORT_NAPI_CONST_GL(NO_ERROR);
    EXPORT_NAPI_CONST_GL(INVALID_ENUM);
    EXPORT_NAPI_CONST_GL(INVALID_VALUE);
    EXPORT_NAPI_CONST_GL(INVALID_OPERATION);
    EXPORT_NAPI_CONST_GL(OUT_OF_MEMORY);
    EXPORT_NAPI_CONST_GL(CW);
    EXPORT_NAPI_CONST_GL(CCW);
    EXPORT_NAPI_CONST_GL(LINE_WIDTH);
    EXPORT_NAPI_CONST_GL(ALIASED_POINT_SIZE_RANGE);
    EXPORT_NAPI_CONST_GL(ALIASED_LINE_WIDTH_RANGE);
    EXPORT_NAPI_CONST_GL(CULL_FACE_MODE);
    EXPORT_NAPI_CONST_GL(FRONT_FACE);
    EXPORT_NAPI_CONST_GL(DEPTH_RANGE);
    EXPORT_NAPI_CONST_GL(DEPTH_WRITEMASK);
    EXPORT_NAPI_CONST_GL(DEPTH_CLEAR_VALUE);
    EXPORT_NAPI_CONST_GL(DEPTH_FUNC);
    EXPORT_NAPI_CONST_GL(STENCIL_CLEAR_VALUE);
    EXPORT_NAPI_CONST_GL(STENCIL_FUNC);
    EXPORT_NAPI_CONST_GL(STENCIL_FAIL);
    EXPORT_NAPI_CONST_GL(STENCIL_PASS_DEPTH_FAIL);
    EXPORT_NAPI_CONST_GL(STENCIL_PASS_DEPTH_PASS);
    EXPORT_NAPI_CONST_GL(STENCIL_REF);
    EXPORT_NAPI_CONST_GL(STENCIL_VALUE_MASK);
    EXPORT_NAPI_CONST_GL(STENCIL_WRITEMASK);
    EXPORT_NAPI_CONST_GL(STENCIL_BACK_FUNC);
    EXPORT_NAPI_CONST_GL(STENCIL_BACK_FAIL);
    EXPORT_NAPI_CONST_GL(STENCIL_BACK_PASS_DEPTH_FAIL);
    EXPORT_NAPI_CONST_GL(STENCIL_BACK_PASS_DEPTH_PASS);
    EXPORT_NAPI_CONST_GL(STENCIL_BACK_REF);
    EXPORT_NAPI_CONST_GL(STENCIL_BACK_VALUE_MASK);
    EXPORT_NAPI_CONST_GL(STENCIL_BACK_WRITEMASK);
    EXPORT_NAPI_CONST_GL(VIEWPORT);
    EXPORT_NAPI_CONST_GL(SCISSOR_BOX);
    EXPORT_NAPI_CONST_GL(COLOR_CLEAR_VALUE);
    EXPORT_NAPI_CONST_GL(COLOR_WRITEMASK);
    EXPORT_NAPI_CONST_GL(UNPACK_ALIGNMENT);
    EXPORT_NAPI_CONST_GL(PACK_ALIGNMENT);
    EXPORT_NAPI_CONST_GL(MAX_TEXTURE_SIZE);
    EXPORT_NAPI_CONST_GL(MAX_VIEWPORT_DIMS);
    EXPORT_NAPI_CONST_GL(SUBPIXEL_BITS);
    EXPORT_NAPI_CONST_GL(RED_BITS);
    EXPORT_NAPI_CONST_GL(GREEN_BITS);
    EXPORT_NAPI_CONST_GL(BLUE_BITS);
    EXPORT_NAPI_CONST_GL(ALPHA_BITS);
    EXPORT_NAPI_CONST_GL(DEPTH_BITS);
    EXPORT_NAPI_CONST_GL(STENCIL_BITS);
    EXPORT_NAPI_CONST_GL(POLYGON_OFFSET_UNITS);
    EXPORT_NAPI_CONST_GL(POLYGON_OFFSET_FACTOR);
    EXPORT_NAPI_CONST_GL(TEXTURE_BINDING_2D);
    EXPORT_NAPI_CONST_GL(SAMPLE_BUFFERS);
    EXPORT_NAPI_CONST_GL(SAMPLES);
    EXPORT_NAPI_CONST_GL(SAMPLE_COVERAGE_VALUE);
    EXPORT_NAPI_CONST_GL(SAMPLE_COVERAGE_INVERT);
    EXPORT_NAPI_CONST_GL(NUM_COMPRESSED_TEXTURE_FORMATS);
    EXPORT_NAPI_CONST_GL(COMPRESSED_TEXTURE_FORMATS);
    EXPORT_NAPI_CONST_GL(DONT_CARE);
    EXPORT_NAPI_CONST_GL(FASTEST);
    EXPORT_NAPI_CONST_GL(NICEST);
    EXPORT_NAPI_CONST_GL(GENERATE_MIPMAP_HINT);
    EXPORT_NAPI_CONST_GL(BYTE);
    EXPORT_NAPI_CONST_GL(UNSIGNED_BYTE);
    EXPORT_NAPI_CONST_GL(SHORT);
    EXPORT_NAPI_CONST_GL(UNSIGNED_SHORT);
    EXPORT_NAPI_CONST_GL(INT);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT);
    EXPORT_NAPI_CONST_GL(FLOAT);
    EXPORT_NAPI_CONST_GL(FIXED);
    EXPORT_NAPI_CONST_GL(DEPTH_COMPONENT);
    EXPORT_NAPI_CONST_GL(ALPHA);
    EXPORT_NAPI_CONST_GL(RGB);
    EXPORT_NAPI_CONST_GL(RGBA);
    EXPORT_NAPI_CONST_GL(LUMINANCE);
    EXPORT_NAPI_CONST_GL(LUMINANCE_ALPHA);
    EXPORT_NAPI_CONST_GL(UNSIGNED_SHORT_4_4_4_4);
    EXPORT_NAPI_CONST_GL(UNSIGNED_SHORT_5_5_5_1);
    EXPORT_NAPI_CONST_GL(UNSIGNED_SHORT_5_6_5);
    EXPORT_NAPI_CONST_GL(FRAGMENT_SHADER);
    EXPORT_NAPI_CONST_GL(VERTEX_SHADER);
    EXPORT_NAPI_CONST_GL(MAX_VERTEX_ATTRIBS);
    EXPORT_NAPI_CONST_GL(MAX_VERTEX_UNIFORM_VECTORS);
    EXPORT_NAPI_CONST_GL(MAX_VARYING_VECTORS);
    EXPORT_NAPI_CONST_GL(MAX_COMBINED_TEXTURE_IMAGE_UNITS);
    EXPORT_NAPI_CONST_GL(MAX_VERTEX_TEXTURE_IMAGE_UNITS);
    EXPORT_NAPI_CONST_GL(MAX_TEXTURE_IMAGE_UNITS);
    EXPORT_NAPI_CONST_GL(MAX_FRAGMENT_UNIFORM_VECTORS);
    EXPORT_NAPI_CONST_GL(SHADER_TYPE);
    EXPORT_NAPI_CONST_GL(DELETE_STATUS);
    EXPORT_NAPI_CONST_GL(LINK_STATUS);
    EXPORT_NAPI_CONST_GL(VALIDATE_STATUS);
    EXPORT_NAPI_CONST_GL(ATTACHED_SHADERS);
    EXPORT_NAPI_CONST_GL(ACTIVE_UNIFORMS);
    EXPORT_NAPI_CONST_GL(ACTIVE_UNIFORM_MAX_LENGTH);
    EXPORT_NAPI_CONST_GL(ACTIVE_ATTRIBUTES);
    EXPORT_NAPI_CONST_GL(ACTIVE_ATTRIBUTE_MAX_LENGTH);
    EXPORT_NAPI_CONST_GL(SHADING_LANGUAGE_VERSION);
    EXPORT_NAPI_CONST_GL(CURRENT_PROGRAM);
    EXPORT_NAPI_CONST_GL(NEVER);
    EXPORT_NAPI_CONST_GL(LESS);
    EXPORT_NAPI_CONST_GL(EQUAL);
    EXPORT_NAPI_CONST_GL(LEQUAL);
    EXPORT_NAPI_CONST_GL(GREATER);
    EXPORT_NAPI_CONST_GL(NOTEQUAL);
    EXPORT_NAPI_CONST_GL(GEQUAL);
    EXPORT_NAPI_CONST_GL(ALWAYS);
    EXPORT_NAPI_CONST_GL(KEEP);
    EXPORT_NAPI_CONST_GL(REPLACE);
    EXPORT_NAPI_CONST_GL(INCR);
    EXPORT_NAPI_CONST_GL(DECR);
    EXPORT_NAPI_CONST_GL(INVERT);
    EXPORT_NAPI_CONST_GL(INCR_WRAP);
    EXPORT_NAPI_CONST_GL(DECR_WRAP);
    EXPORT_NAPI_CONST_GL(VENDOR);
    EXPORT_NAPI_CONST_GL(RENDERER);
    EXPORT_NAPI_CONST_GL(VERSION);
    EXPORT_NAPI_CONST_GL(EXTENSIONS);
    EXPORT_NAPI_CONST_GL(NEAREST);
    EXPORT_NAPI_CONST_GL(LINEAR);
    EXPORT_NAPI_CONST_GL(NEAREST_MIPMAP_NEAREST);
    EXPORT_NAPI_CONST_GL(LINEAR_MIPMAP_NEAREST);
    EXPORT_NAPI_CONST_GL(NEAREST_MIPMAP_LINEAR);
    EXPORT_NAPI_CONST_GL(LINEAR_MIPMAP_LINEAR);
    EXPORT_NAPI_CONST_GL(TEXTURE_MAG_FILTER);
    EXPORT_NAPI_CONST_GL(TEXTURE_MIN_FILTER);
    EXPORT_NAPI_CONST_GL(TEXTURE_WRAP_S);
    EXPORT_NAPI_CONST_GL(TEXTURE_WRAP_T);
    EXPORT_NAPI_CONST_GL(TEXTURE);
    EXPORT_NAPI_CONST_GL(TEXTURE_CUBE_MAP);
    EXPORT_NAPI_CONST_GL(TEXTURE_BINDING_CUBE_MAP);
    EXPORT_NAPI_CONST_GL(TEXTURE_CUBE_MAP_POSITIVE_X);
    EXPORT_NAPI_CONST_GL(TEXTURE_CUBE_MAP_NEGATIVE_X);
    EXPORT_NAPI_CONST_GL(TEXTURE_CUBE_MAP_POSITIVE_Y);
    EXPORT_NAPI_CONST_GL(TEXTURE_CUBE_MAP_NEGATIVE_Y);
    EXPORT_NAPI_CONST_GL(TEXTURE_CUBE_MAP_POSITIVE_Z);
    EXPORT_NAPI_CONST_GL(TEXTURE_CUBE_MAP_NEGATIVE_Z);
    EXPORT_NAPI_CONST_GL(MAX_CUBE_MAP_TEXTURE_SIZE);
    EXPORT_NAPI_CONST_GL(TEXTURE0);
    EXPORT_NAPI_CONST_GL(TEXTURE1);
    EXPORT_NAPI_CONST_GL(TEXTURE2);
    EXPORT_NAPI_CONST_GL(TEXTURE3);
    EXPORT_NAPI_CONST_GL(TEXTURE4);
    EXPORT_NAPI_CONST_GL(TEXTURE5);
    EXPORT_NAPI_CONST_GL(TEXTURE6);
    EXPORT_NAPI_CONST_GL(TEXTURE7);
    EXPORT_NAPI_CONST_GL(TEXTURE8);
    EXPORT_NAPI_CONST_GL(TEXTURE9);
    EXPORT_NAPI_CONST_GL(TEXTURE10);
    EXPORT_NAPI_CONST_GL(TEXTURE11);
    EXPORT_NAPI_CONST_GL(TEXTURE12);
    EXPORT_NAPI_CONST_GL(TEXTURE13);
    EXPORT_NAPI_CONST_GL(TEXTURE14);
    EXPORT_NAPI_CONST_GL(TEXTURE15);
    EXPORT_NAPI_CONST_GL(TEXTURE16);
    EXPORT_NAPI_CONST_GL(TEXTURE17);
    EXPORT_NAPI_CONST_GL(TEXTURE18);
    EXPORT_NAPI_CONST_GL(TEXTURE19);
    EXPORT_NAPI_CONST_GL(TEXTURE20);
    EXPORT_NAPI_CONST_GL(TEXTURE21);
    EXPORT_NAPI_CONST_GL(TEXTURE22);
    EXPORT_NAPI_CONST_GL(TEXTURE23);
    EXPORT_NAPI_CONST_GL(TEXTURE24);
    EXPORT_NAPI_CONST_GL(TEXTURE25);
    EXPORT_NAPI_CONST_GL(TEXTURE26);
    EXPORT_NAPI_CONST_GL(TEXTURE27);
    EXPORT_NAPI_CONST_GL(TEXTURE28);
    EXPORT_NAPI_CONST_GL(TEXTURE29);
    EXPORT_NAPI_CONST_GL(TEXTURE30);
    EXPORT_NAPI_CONST_GL(TEXTURE31);
    EXPORT_NAPI_CONST_GL(ACTIVE_TEXTURE);
    EXPORT_NAPI_CONST_GL(REPEAT);
    EXPORT_NAPI_CONST_GL(CLAMP_TO_EDGE);
    EXPORT_NAPI_CONST_GL(MIRRORED_REPEAT);
    EXPORT_NAPI_CONST_GL(FLOAT_VEC2);
    EXPORT_NAPI_CONST_GL(FLOAT_VEC3);
    EXPORT_NAPI_CONST_GL(FLOAT_VEC4);
    EXPORT_NAPI_CONST_GL(INT_VEC2);
    EXPORT_NAPI_CONST_GL(INT_VEC3);
    EXPORT_NAPI_CONST_GL(INT_VEC4);
    EXPORT_NAPI_CONST_GL(BOOL);
    EXPORT_NAPI_CONST_GL(BOOL_VEC2);
    EXPORT_NAPI_CONST_GL(BOOL_VEC3);
    EXPORT_NAPI_CONST_GL(BOOL_VEC4);
    EXPORT_NAPI_CONST_GL(FLOAT_MAT2);
    EXPORT_NAPI_CONST_GL(FLOAT_MAT3);
    EXPORT_NAPI_CONST_GL(FLOAT_MAT4);
    EXPORT_NAPI_CONST_GL(SAMPLER_2D);
    EXPORT_NAPI_CONST_GL(SAMPLER_CUBE);
    EXPORT_NAPI_CONST_GL(VERTEX_ATTRIB_ARRAY_ENABLED);
    EXPORT_NAPI_CONST_GL(VERTEX_ATTRIB_ARRAY_SIZE);
    EXPORT_NAPI_CONST_GL(VERTEX_ATTRIB_ARRAY_STRIDE);
    EXPORT_NAPI_CONST_GL(VERTEX_ATTRIB_ARRAY_TYPE);
    EXPORT_NAPI_CONST_GL(VERTEX_ATTRIB_ARRAY_NORMALIZED);
    EXPORT_NAPI_CONST_GL(VERTEX_ATTRIB_ARRAY_POINTER);
    EXPORT_NAPI_CONST_GL(VERTEX_ATTRIB_ARRAY_BUFFER_BINDING);
    EXPORT_NAPI_CONST_GL(IMPLEMENTATION_COLOR_READ_TYPE);
    EXPORT_NAPI_CONST_GL(IMPLEMENTATION_COLOR_READ_FORMAT);
    EXPORT_NAPI_CONST_GL(COMPILE_STATUS);
    EXPORT_NAPI_CONST_GL(INFO_LOG_LENGTH);
    EXPORT_NAPI_CONST_GL(SHADER_SOURCE_LENGTH);
    EXPORT_NAPI_CONST_GL(SHADER_COMPILER);
    EXPORT_NAPI_CONST_GL(SHADER_BINARY_FORMATS);
    EXPORT_NAPI_CONST_GL(NUM_SHADER_BINARY_FORMATS);
    EXPORT_NAPI_CONST_GL(LOW_FLOAT);
    EXPORT_NAPI_CONST_GL(MEDIUM_FLOAT);
    EXPORT_NAPI_CONST_GL(HIGH_FLOAT);
    EXPORT_NAPI_CONST_GL(LOW_INT);
    EXPORT_NAPI_CONST_GL(MEDIUM_INT);
    EXPORT_NAPI_CONST_GL(HIGH_INT);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER);
    EXPORT_NAPI_CONST_GL(RENDERBUFFER);
    EXPORT_NAPI_CONST_GL(RGBA4);
    EXPORT_NAPI_CONST_GL(RGB5_A1);
    EXPORT_NAPI_CONST_GL(RGB565);
    EXPORT_NAPI_CONST_GL(DEPTH_COMPONENT16);
    EXPORT_NAPI_CONST_GL(STENCIL_INDEX8);
    EXPORT_NAPI_CONST_GL(RENDERBUFFER_WIDTH);
    EXPORT_NAPI_CONST_GL(RENDERBUFFER_HEIGHT);
    EXPORT_NAPI_CONST_GL(RENDERBUFFER_INTERNAL_FORMAT);
    EXPORT_NAPI_CONST_GL(RENDERBUFFER_RED_SIZE);
    EXPORT_NAPI_CONST_GL(RENDERBUFFER_GREEN_SIZE);
    EXPORT_NAPI_CONST_GL(RENDERBUFFER_BLUE_SIZE);
    EXPORT_NAPI_CONST_GL(RENDERBUFFER_ALPHA_SIZE);
    EXPORT_NAPI_CONST_GL(RENDERBUFFER_DEPTH_SIZE);
    EXPORT_NAPI_CONST_GL(RENDERBUFFER_STENCIL_SIZE);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_OBJECT_NAME);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT0);
    EXPORT_NAPI_CONST_GL(DEPTH_ATTACHMENT);
    EXPORT_NAPI_CONST_GL(STENCIL_ATTACHMENT);
    EXPORT_NAPI_CONST_GL(NONE);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_COMPLETE);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_INCOMPLETE_ATTACHMENT);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_INCOMPLETE_DIMENSIONS);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_UNSUPPORTED);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_BINDING);
    EXPORT_NAPI_CONST_GL(RENDERBUFFER_BINDING);
    EXPORT_NAPI_CONST_GL(MAX_RENDERBUFFER_SIZE);
    EXPORT_NAPI_CONST_GL(INVALID_FRAMEBUFFER_OPERATION);
    EXPORT_NAPI_CONST_GL(READ_BUFFER);
    EXPORT_NAPI_CONST_GL(UNPACK_ROW_LENGTH);
    EXPORT_NAPI_CONST_GL(UNPACK_SKIP_ROWS);
    EXPORT_NAPI_CONST_GL(UNPACK_SKIP_PIXELS);
    EXPORT_NAPI_CONST_GL(PACK_ROW_LENGTH);
    EXPORT_NAPI_CONST_GL(PACK_SKIP_ROWS);
    EXPORT_NAPI_CONST_GL(PACK_SKIP_PIXELS);
    EXPORT_NAPI_CONST_GL(COLOR);
    EXPORT_NAPI_CONST_GL(DEPTH);
    EXPORT_NAPI_CONST_GL(STENCIL);
    EXPORT_NAPI_CONST_GL(RED);
    EXPORT_NAPI_CONST_GL(RGB8);
    EXPORT_NAPI_CONST_GL(RGBA8);
    EXPORT_NAPI_CONST_GL(RGB10_A2);
    EXPORT_NAPI_CONST_GL(TEXTURE_BINDING_3D);
    EXPORT_NAPI_CONST_GL(UNPACK_SKIP_IMAGES);
    EXPORT_NAPI_CONST_GL(UNPACK_IMAGE_HEIGHT);
    EXPORT_NAPI_CONST_GL(TEXTURE_3D);
    EXPORT_NAPI_CONST_GL(TEXTURE_WRAP_R);
    EXPORT_NAPI_CONST_GL(MAX_3D_TEXTURE_SIZE);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_2_10_10_10_REV);
    EXPORT_NAPI_CONST_GL(MAX_ELEMENTS_VERTICES);
    EXPORT_NAPI_CONST_GL(MAX_ELEMENTS_INDICES);
    EXPORT_NAPI_CONST_GL(TEXTURE_MIN_LOD);
    EXPORT_NAPI_CONST_GL(TEXTURE_MAX_LOD);
    EXPORT_NAPI_CONST_GL(TEXTURE_BASE_LEVEL);
    EXPORT_NAPI_CONST_GL(TEXTURE_MAX_LEVEL);
    EXPORT_NAPI_CONST_GL(MIN);
    EXPORT_NAPI_CONST_GL(MAX);
    EXPORT_NAPI_CONST_GL(DEPTH_COMPONENT24);
    EXPORT_NAPI_CONST_GL(MAX_TEXTURE_LOD_BIAS);
    EXPORT_NAPI_CONST_GL(TEXTURE_COMPARE_MODE);
    EXPORT_NAPI_CONST_GL(TEXTURE_COMPARE_FUNC);
    EXPORT_NAPI_CONST_GL(CURRENT_QUERY);
    EXPORT_NAPI_CONST_GL(QUERY_RESULT);
    EXPORT_NAPI_CONST_GL(QUERY_RESULT_AVAILABLE);
    EXPORT_NAPI_CONST_GL(BUFFER_MAPPED);
    EXPORT_NAPI_CONST_GL(BUFFER_MAP_POINTER);
    EXPORT_NAPI_CONST_GL(STREAM_READ);
    EXPORT_NAPI_CONST_GL(STREAM_COPY);
    EXPORT_NAPI_CONST_GL(STATIC_READ);
    EXPORT_NAPI_CONST_GL(STATIC_COPY);
    EXPORT_NAPI_CONST_GL(DYNAMIC_READ);
    EXPORT_NAPI_CONST_GL(DYNAMIC_COPY);
    EXPORT_NAPI_CONST_GL(MAX_DRAW_BUFFERS);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER0);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER1);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER2);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER3);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER4);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER5);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER6);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER7);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER8);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER9);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER10);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER11);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER12);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER13);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER14);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER15);
    EXPORT_NAPI_CONST_GL(MAX_FRAGMENT_UNIFORM_COMPONENTS);
    EXPORT_NAPI_CONST_GL(MAX_VERTEX_UNIFORM_COMPONENTS);
    EXPORT_NAPI_CONST_GL(SAMPLER_3D);
    EXPORT_NAPI_CONST_GL(SAMPLER_2D_SHADOW);
    EXPORT_NAPI_CONST_GL(FRAGMENT_SHADER_DERIVATIVE_HINT);
    EXPORT_NAPI_CONST_GL(PIXEL_PACK_BUFFER);
    EXPORT_NAPI_CONST_GL(PIXEL_UNPACK_BUFFER);
    EXPORT_NAPI_CONST_GL(PIXEL_PACK_BUFFER_BINDING);
    EXPORT_NAPI_CONST_GL(PIXEL_UNPACK_BUFFER_BINDING);
    EXPORT_NAPI_CONST_GL(FLOAT_MAT2x3);
    EXPORT_NAPI_CONST_GL(FLOAT_MAT2x4);
    EXPORT_NAPI_CONST_GL(FLOAT_MAT3x2);
    EXPORT_NAPI_CONST_GL(FLOAT_MAT3x4);
    EXPORT_NAPI_CONST_GL(FLOAT_MAT4x2);
    EXPORT_NAPI_CONST_GL(FLOAT_MAT4x3);
    EXPORT_NAPI_CONST_GL(SRGB);
    EXPORT_NAPI_CONST_GL(SRGB8);
    EXPORT_NAPI_CONST_GL(SRGB8_ALPHA8);
    EXPORT_NAPI_CONST_GL(COMPARE_REF_TO_TEXTURE);
    EXPORT_NAPI_CONST_GL(MAJOR_VERSION);
    EXPORT_NAPI_CONST_GL(MINOR_VERSION);
    EXPORT_NAPI_CONST_GL(NUM_EXTENSIONS);
    EXPORT_NAPI_CONST_GL(RGBA32F);
    EXPORT_NAPI_CONST_GL(RGB32F);
    EXPORT_NAPI_CONST_GL(RGBA16F);
    EXPORT_NAPI_CONST_GL(RGB16F);
    EXPORT_NAPI_CONST_GL(VERTEX_ATTRIB_ARRAY_INTEGER);
    EXPORT_NAPI_CONST_GL(MAX_ARRAY_TEXTURE_LAYERS);
    EXPORT_NAPI_CONST_GL(MIN_PROGRAM_TEXEL_OFFSET);
    EXPORT_NAPI_CONST_GL(MAX_PROGRAM_TEXEL_OFFSET);
    EXPORT_NAPI_CONST_GL(MAX_VARYING_COMPONENTS);
    EXPORT_NAPI_CONST_GL(TEXTURE_2D_ARRAY);
    EXPORT_NAPI_CONST_GL(TEXTURE_BINDING_2D_ARRAY);
    EXPORT_NAPI_CONST_GL(R11F_G11F_B10F);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_10F_11F_11F_REV);
    EXPORT_NAPI_CONST_GL(RGB9_E5);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_5_9_9_9_REV);
    EXPORT_NAPI_CONST_GL(TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH);
    EXPORT_NAPI_CONST_GL(TRANSFORM_FEEDBACK_BUFFER_MODE);
    EXPORT_NAPI_CONST_GL(MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS);
    EXPORT_NAPI_CONST_GL(TRANSFORM_FEEDBACK_VARYINGS);
    EXPORT_NAPI_CONST_GL(TRANSFORM_FEEDBACK_BUFFER_START);
    EXPORT_NAPI_CONST_GL(TRANSFORM_FEEDBACK_BUFFER_SIZE);
    EXPORT_NAPI_CONST_GL(TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
    EXPORT_NAPI_CONST_GL(RASTERIZER_DISCARD);
    EXPORT_NAPI_CONST_GL(MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS);
    EXPORT_NAPI_CONST_GL(MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS);
    EXPORT_NAPI_CONST_GL(INTERLEAVED_ATTRIBS);
    EXPORT_NAPI_CONST_GL(SEPARATE_ATTRIBS);
    EXPORT_NAPI_CONST_GL(TRANSFORM_FEEDBACK_BUFFER);
    EXPORT_NAPI_CONST_GL(TRANSFORM_FEEDBACK_BUFFER_BINDING);
    EXPORT_NAPI_CONST_GL(RGBA32UI);
    EXPORT_NAPI_CONST_GL(RGB32UI);
    EXPORT_NAPI_CONST_GL(RGBA16UI);
    EXPORT_NAPI_CONST_GL(RGB16UI);
    EXPORT_NAPI_CONST_GL(RGBA8UI);
    EXPORT_NAPI_CONST_GL(RGB8UI);
    EXPORT_NAPI_CONST_GL(RGBA32I);
    EXPORT_NAPI_CONST_GL(RGB32I);
    EXPORT_NAPI_CONST_GL(RGBA16I);
    EXPORT_NAPI_CONST_GL(RGB16I);
    EXPORT_NAPI_CONST_GL(RGBA8I);
    EXPORT_NAPI_CONST_GL(RGB8I);
    EXPORT_NAPI_CONST_GL(RED_INTEGER);
    EXPORT_NAPI_CONST_GL(RGB_INTEGER);
    EXPORT_NAPI_CONST_GL(RGBA_INTEGER);
    EXPORT_NAPI_CONST_GL(SAMPLER_2D_ARRAY);
    EXPORT_NAPI_CONST_GL(SAMPLER_2D_ARRAY_SHADOW);
    EXPORT_NAPI_CONST_GL(SAMPLER_CUBE_SHADOW);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_VEC2);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_VEC3);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_VEC4);
    EXPORT_NAPI_CONST_GL(INT_SAMPLER_2D);
    EXPORT_NAPI_CONST_GL(INT_SAMPLER_3D);
    EXPORT_NAPI_CONST_GL(INT_SAMPLER_CUBE);
    EXPORT_NAPI_CONST_GL(INT_SAMPLER_2D_ARRAY);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_SAMPLER_2D);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_SAMPLER_3D);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_SAMPLER_CUBE);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_SAMPLER_2D_ARRAY);
    EXPORT_NAPI_CONST_GL(BUFFER_ACCESS_FLAGS);
    EXPORT_NAPI_CONST_GL(BUFFER_MAP_LENGTH);
    EXPORT_NAPI_CONST_GL(BUFFER_MAP_OFFSET);
    EXPORT_NAPI_CONST_GL(DEPTH_COMPONENT32F);
    EXPORT_NAPI_CONST_GL(DEPTH32F_STENCIL8);
    EXPORT_NAPI_CONST_GL(FLOAT_32_UNSIGNED_INT_24_8_REV);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_RED_SIZE);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_GREEN_SIZE);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_BLUE_SIZE);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_DEFAULT);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_UNDEFINED);
    EXPORT_NAPI_CONST_GL(DEPTH_STENCIL_ATTACHMENT);
    EXPORT_NAPI_CONST_GL(DEPTH_STENCIL);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_24_8);
    EXPORT_NAPI_CONST_GL(DEPTH24_STENCIL8);
    EXPORT_NAPI_CONST_GL(UNSIGNED_NORMALIZED);
    EXPORT_NAPI_CONST_GL(DRAW_FRAMEBUFFER_BINDING);
    EXPORT_NAPI_CONST_GL(READ_FRAMEBUFFER);
    EXPORT_NAPI_CONST_GL(DRAW_FRAMEBUFFER);
    EXPORT_NAPI_CONST_GL(READ_FRAMEBUFFER_BINDING);
    EXPORT_NAPI_CONST_GL(RENDERBUFFER_SAMPLES);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER);
    EXPORT_NAPI_CONST_GL(MAX_COLOR_ATTACHMENTS);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT1);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT2);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT3);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT4);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT5);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT6);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT7);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT8);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT9);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT10);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT11);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT12);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT13);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT14);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT15);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT16);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT17);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT18);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT19);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT20);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT21);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT22);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT23);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT24);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT25);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT26);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT27);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT28);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT29);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT30);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT31);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_INCOMPLETE_MULTISAMPLE);
    EXPORT_NAPI_CONST_GL(MAX_SAMPLES);
    EXPORT_NAPI_CONST_GL(HALF_FLOAT);
    EXPORT_NAPI_CONST_GL(MAP_READ_BIT);
    EXPORT_NAPI_CONST_GL(MAP_WRITE_BIT);
    EXPORT_NAPI_CONST_GL(MAP_INVALIDATE_RANGE_BIT);
    EXPORT_NAPI_CONST_GL(MAP_INVALIDATE_BUFFER_BIT);
    EXPORT_NAPI_CONST_GL(MAP_FLUSH_EXPLICIT_BIT);
    EXPORT_NAPI_CONST_GL(MAP_UNSYNCHRONIZED_BIT);
    EXPORT_NAPI_CONST_GL(RG);
    EXPORT_NAPI_CONST_GL(RG_INTEGER);
    EXPORT_NAPI_CONST_GL(R8);
    EXPORT_NAPI_CONST_GL(RG8);
    EXPORT_NAPI_CONST_GL(R16F);
    EXPORT_NAPI_CONST_GL(R32F);
    EXPORT_NAPI_CONST_GL(RG16F);
    EXPORT_NAPI_CONST_GL(RG32F);
    EXPORT_NAPI_CONST_GL(R8I);
    EXPORT_NAPI_CONST_GL(R8UI);
    EXPORT_NAPI_CONST_GL(R16I);
    EXPORT_NAPI_CONST_GL(R16UI);
    EXPORT_NAPI_CONST_GL(R32I);
    EXPORT_NAPI_CONST_GL(R32UI);
    EXPORT_NAPI_CONST_GL(RG8I);
    EXPORT_NAPI_CONST_GL(RG8UI);
    EXPORT_NAPI_CONST_GL(RG16I);
    EXPORT_NAPI_CONST_GL(RG16UI);
    EXPORT_NAPI_CONST_GL(RG32I);
    EXPORT_NAPI_CONST_GL(RG32UI);
    EXPORT_NAPI_CONST_GL(VERTEX_ARRAY_BINDING);
    EXPORT_NAPI_CONST_GL(R8_SNORM);
    EXPORT_NAPI_CONST_GL(RG8_SNORM);
    EXPORT_NAPI_CONST_GL(RGB8_SNORM);
    EXPORT_NAPI_CONST_GL(RGBA8_SNORM);
    EXPORT_NAPI_CONST_GL(SIGNED_NORMALIZED);
    EXPORT_NAPI_CONST_GL(PRIMITIVE_RESTART_FIXED_INDEX);
    EXPORT_NAPI_CONST_GL(COPY_READ_BUFFER);
    EXPORT_NAPI_CONST_GL(COPY_WRITE_BUFFER);
    EXPORT_NAPI_CONST_GL(COPY_READ_BUFFER_BINDING);
    EXPORT_NAPI_CONST_GL(COPY_WRITE_BUFFER_BINDING);
    EXPORT_NAPI_CONST_GL(UNIFORM_BUFFER);
    EXPORT_NAPI_CONST_GL(UNIFORM_BUFFER_BINDING);
    EXPORT_NAPI_CONST_GL(UNIFORM_BUFFER_START);
    EXPORT_NAPI_CONST_GL(UNIFORM_BUFFER_SIZE);
    EXPORT_NAPI_CONST_GL(MAX_VERTEX_UNIFORM_BLOCKS);
    EXPORT_NAPI_CONST_GL(MAX_FRAGMENT_UNIFORM_BLOCKS);
    EXPORT_NAPI_CONST_GL(MAX_COMBINED_UNIFORM_BLOCKS);
    EXPORT_NAPI_CONST_GL(MAX_UNIFORM_BUFFER_BINDINGS);
    EXPORT_NAPI_CONST_GL(MAX_UNIFORM_BLOCK_SIZE);
    EXPORT_NAPI_CONST_GL(MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS);
    EXPORT_NAPI_CONST_GL(MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS);
    EXPORT_NAPI_CONST_GL(UNIFORM_BUFFER_OFFSET_ALIGNMENT);
    EXPORT_NAPI_CONST_GL(ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH);
    EXPORT_NAPI_CONST_GL(ACTIVE_UNIFORM_BLOCKS);
    EXPORT_NAPI_CONST_GL(UNIFORM_TYPE);
    EXPORT_NAPI_CONST_GL(UNIFORM_SIZE);
    EXPORT_NAPI_CONST_GL(UNIFORM_NAME_LENGTH);
    EXPORT_NAPI_CONST_GL(UNIFORM_BLOCK_INDEX);
    EXPORT_NAPI_CONST_GL(UNIFORM_OFFSET);
    EXPORT_NAPI_CONST_GL(UNIFORM_ARRAY_STRIDE);
    EXPORT_NAPI_CONST_GL(UNIFORM_MATRIX_STRIDE);
    EXPORT_NAPI_CONST_GL(UNIFORM_IS_ROW_MAJOR);
    EXPORT_NAPI_CONST_GL(UNIFORM_BLOCK_BINDING);
    EXPORT_NAPI_CONST_GL(UNIFORM_BLOCK_DATA_SIZE);
    EXPORT_NAPI_CONST_GL(UNIFORM_BLOCK_NAME_LENGTH);
    EXPORT_NAPI_CONST_GL(UNIFORM_BLOCK_ACTIVE_UNIFORMS);
    EXPORT_NAPI_CONST_GL(UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES);
    EXPORT_NAPI_CONST_GL(UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER);
    EXPORT_NAPI_CONST_GL(UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER);
    EXPORT_NAPI_CONST_GL(INVALID_INDEX);
    EXPORT_NAPI_CONST_GL(MAX_VERTEX_OUTPUT_COMPONENTS);
    EXPORT_NAPI_CONST_GL(MAX_FRAGMENT_INPUT_COMPONENTS);
    EXPORT_NAPI_CONST_GL(MAX_SERVER_WAIT_TIMEOUT);
    EXPORT_NAPI_CONST_GL(OBJECT_TYPE);
    EXPORT_NAPI_CONST_GL(SYNC_CONDITION);
    EXPORT_NAPI_CONST_GL(SYNC_STATUS);
    EXPORT_NAPI_CONST_GL(SYNC_FLAGS);
    EXPORT_NAPI_CONST_GL(SYNC_FENCE);
    EXPORT_NAPI_CONST_GL(SYNC_GPU_COMMANDS_COMPLETE);
    EXPORT_NAPI_CONST_GL(UNSIGNALED);
    EXPORT_NAPI_CONST_GL(SIGNALED);
    EXPORT_NAPI_CONST_GL(ALREADY_SIGNALED);
    EXPORT_NAPI_CONST_GL(TIMEOUT_EXPIRED);
    EXPORT_NAPI_CONST_GL(CONDITION_SATISFIED);
    EXPORT_NAPI_CONST_GL(WAIT_FAILED);
    EXPORT_NAPI_CONST_GL(SYNC_FLUSH_COMMANDS_BIT);
    EXPORT_NAPI_CONST_GL(TIMEOUT_IGNORED);
    EXPORT_NAPI_CONST_GL(VERTEX_ATTRIB_ARRAY_DIVISOR);
    EXPORT_NAPI_CONST_GL(ANY_SAMPLES_PASSED);
    EXPORT_NAPI_CONST_GL(ANY_SAMPLES_PASSED_CONSERVATIVE);
    EXPORT_NAPI_CONST_GL(SAMPLER_BINDING);
    EXPORT_NAPI_CONST_GL(RGB10_A2UI);
    EXPORT_NAPI_CONST_GL(TEXTURE_SWIZZLE_R);
    EXPORT_NAPI_CONST_GL(TEXTURE_SWIZZLE_G);
    EXPORT_NAPI_CONST_GL(TEXTURE_SWIZZLE_B);
    EXPORT_NAPI_CONST_GL(TEXTURE_SWIZZLE_A);
    EXPORT_NAPI_CONST_GL(GREEN);
    EXPORT_NAPI_CONST_GL(BLUE);
    EXPORT_NAPI_CONST_GL(INT_2_10_10_10_REV);
    EXPORT_NAPI_CONST_GL(TRANSFORM_FEEDBACK);
    EXPORT_NAPI_CONST_GL(TRANSFORM_FEEDBACK_PAUSED);
    EXPORT_NAPI_CONST_GL(TRANSFORM_FEEDBACK_ACTIVE);
    EXPORT_NAPI_CONST_GL(TRANSFORM_FEEDBACK_BINDING);
    EXPORT_NAPI_CONST_GL(PROGRAM_BINARY_RETRIEVABLE_HINT);
    EXPORT_NAPI_CONST_GL(PROGRAM_BINARY_LENGTH);
    EXPORT_NAPI_CONST_GL(NUM_PROGRAM_BINARY_FORMATS);
    EXPORT_NAPI_CONST_GL(PROGRAM_BINARY_FORMATS);
    EXPORT_NAPI_CONST_GL(COMPRESSED_R11_EAC);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SIGNED_R11_EAC);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RG11_EAC);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SIGNED_RG11_EAC);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGB8_ETC2);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ETC2);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA8_ETC2_EAC);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ETC2_EAC);
    EXPORT_NAPI_CONST_GL(TEXTURE_IMMUTABLE_FORMAT);
    EXPORT_NAPI_CONST_GL(MAX_ELEMENT_INDEX);
    EXPORT_NAPI_CONST_GL(NUM_SAMPLE_COUNTS);
    EXPORT_NAPI_CONST_GL(TEXTURE_IMMUTABLE_LEVELS);
    EXPORT_NAPI_CONST_GL(ES_VERSION_2_0);

#ifdef LOAD_GLES_EXT
    EXPORT_NAPI_CONST_GL(3DC_X_AMD);
    EXPORT_NAPI_CONST_GL(3DC_XY_AMD);
    EXPORT_NAPI_CONST_GL(ATC_RGB_AMD);
    EXPORT_NAPI_CONST_GL(ATC_RGBA_EXPLICIT_ALPHA_AMD);
    EXPORT_NAPI_CONST_GL(ATC_RGBA_INTERPOLATED_ALPHA_AMD);
    EXPORT_NAPI_CONST_GL(COUNTER_TYPE_AMD);
    EXPORT_NAPI_CONST_GL(COUNTER_RANGE_AMD);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT64_AMD);
    EXPORT_NAPI_CONST_GL(PERCENTAGE_AMD);
    EXPORT_NAPI_CONST_GL(PERFMON_RESULT_AVAILABLE_AMD);
    EXPORT_NAPI_CONST_GL(PERFMON_RESULT_SIZE_AMD);
    EXPORT_NAPI_CONST_GL(PERFMON_RESULT_AMD);
    EXPORT_NAPI_CONST_GL(Z400_BINARY_AMD);
    EXPORT_NAPI_CONST_GL(DEPTH_STENCIL_OES);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_24_8_OES);
    EXPORT_NAPI_CONST_GL(DEPTH_COMPONENT32_OES);
    EXPORT_NAPI_CONST_GL(DEPTH24_STENCIL8_OES);
    EXPORT_NAPI_CONST_GL(READ_FRAMEBUFFER_ANGLE);
    EXPORT_NAPI_CONST_GL(DRAW_FRAMEBUFFER_ANGLE);
    EXPORT_NAPI_CONST_GL(DRAW_FRAMEBUFFER_BINDING_ANGLE);
    EXPORT_NAPI_CONST_GL(READ_FRAMEBUFFER_BINDING_ANGLE);
    EXPORT_NAPI_CONST_GL(RENDERBUFFER_SAMPLES_ANGLE);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_ANGLE);
    EXPORT_NAPI_CONST_GL(MAX_SAMPLES_ANGLE);
    EXPORT_NAPI_CONST_GL(VERTEX_ATTRIB_ARRAY_DIVISOR_ANGLE);
    EXPORT_NAPI_CONST_GL(PACK_REVERSE_ROW_ORDER_ANGLE);
    EXPORT_NAPI_CONST_GL(PROGRAM_BINARY_ANGLE);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_S3TC_DXT3_ANGLE);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_S3TC_DXT5_ANGLE);
    EXPORT_NAPI_CONST_GL(TEXTURE_USAGE_ANGLE);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_ANGLE);
    EXPORT_NAPI_CONST_GL(TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE);
    EXPORT_NAPI_CONST_GL(MAX_CLIP_DISTANCES_APPLE);
    EXPORT_NAPI_CONST_GL(CLIP_DISTANCE0_APPLE);
    EXPORT_NAPI_CONST_GL(CLIP_DISTANCE1_APPLE);
    EXPORT_NAPI_CONST_GL(CLIP_DISTANCE2_APPLE);
    EXPORT_NAPI_CONST_GL(CLIP_DISTANCE3_APPLE);
    EXPORT_NAPI_CONST_GL(CLIP_DISTANCE4_APPLE);
    EXPORT_NAPI_CONST_GL(CLIP_DISTANCE5_APPLE);
    EXPORT_NAPI_CONST_GL(CLIP_DISTANCE6_APPLE);
    EXPORT_NAPI_CONST_GL(CLIP_DISTANCE7_APPLE);
    EXPORT_NAPI_CONST_GL(RENDERBUFFER_SAMPLES_APPLE);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE);
    EXPORT_NAPI_CONST_GL(MAX_SAMPLES_APPLE);
    EXPORT_NAPI_CONST_GL(READ_FRAMEBUFFER_APPLE);
    EXPORT_NAPI_CONST_GL(DRAW_FRAMEBUFFER_APPLE);
    EXPORT_NAPI_CONST_GL(DRAW_FRAMEBUFFER_BINDING_APPLE);
    EXPORT_NAPI_CONST_GL(READ_FRAMEBUFFER_BINDING_APPLE);
    EXPORT_NAPI_CONST_GL(RGB_422_APPLE);
    EXPORT_NAPI_CONST_GL(UNSIGNED_SHORT_8_8_APPLE);
    EXPORT_NAPI_CONST_GL(UNSIGNED_SHORT_8_8_REV_APPLE);
    EXPORT_NAPI_CONST_GL(RGB_RAW_422_APPLE);
    EXPORT_NAPI_CONST_GL(SYNC_OBJECT_APPLE);
    EXPORT_NAPI_CONST_GL(MAX_SERVER_WAIT_TIMEOUT_APPLE);
    EXPORT_NAPI_CONST_GL(OBJECT_TYPE_APPLE);
    EXPORT_NAPI_CONST_GL(SYNC_CONDITION_APPLE);
    EXPORT_NAPI_CONST_GL(SYNC_STATUS_APPLE);
    EXPORT_NAPI_CONST_GL(SYNC_FLAGS_APPLE);
    EXPORT_NAPI_CONST_GL(SYNC_FENCE_APPLE);
    EXPORT_NAPI_CONST_GL(SYNC_GPU_COMMANDS_COMPLETE_APPLE);
    EXPORT_NAPI_CONST_GL(UNSIGNALED_APPLE);
    EXPORT_NAPI_CONST_GL(SIGNALED_APPLE);
    EXPORT_NAPI_CONST_GL(ALREADY_SIGNALED_APPLE);
    EXPORT_NAPI_CONST_GL(TIMEOUT_EXPIRED_APPLE);
    EXPORT_NAPI_CONST_GL(CONDITION_SATISFIED_APPLE);
    EXPORT_NAPI_CONST_GL(WAIT_FAILED_APPLE);
    EXPORT_NAPI_CONST_GL(SYNC_FLUSH_COMMANDS_BIT_APPLE);
    EXPORT_NAPI_CONST_GL(TIMEOUT_IGNORED_APPLE);
    EXPORT_NAPI_CONST_GL(BGRA_EXT);
    EXPORT_NAPI_CONST_GL(BGRA8_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_MAX_LEVEL_APPLE);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_10F_11F_11F_REV_APPLE);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_5_9_9_9_REV_APPLE);
    EXPORT_NAPI_CONST_GL(R11F_G11F_B10F_APPLE);
    EXPORT_NAPI_CONST_GL(RGB9_E5_APPLE);
    EXPORT_NAPI_CONST_GL(MALI_PROGRAM_BINARY_ARM);
    EXPORT_NAPI_CONST_GL(MALI_SHADER_BINARY_ARM);
    EXPORT_NAPI_CONST_GL(FETCH_PER_SAMPLE_ARM);
    EXPORT_NAPI_CONST_GL(FRAGMENT_SHADER_FRAMEBUFFER_FETCH_MRT_ARM);
    EXPORT_NAPI_CONST_GL(SMAPHS30_PROGRAM_BINARY_DMP);
    EXPORT_NAPI_CONST_GL(SMAPHS_PROGRAM_BINARY_DMP);
    EXPORT_NAPI_CONST_GL(DMP_PROGRAM_BINARY_DMP);
    EXPORT_NAPI_CONST_GL(SHADER_BINARY_DMP);
    EXPORT_NAPI_CONST_GL(SAMPLER_EXTERNAL_2D_Y2Y_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_EXTERNAL_OES);
    EXPORT_NAPI_CONST_GL(TEXTURE_BINDING_EXTERNAL_OES);
    EXPORT_NAPI_CONST_GL(REQUIRED_TEXTURE_IMAGE_UNITS_OES);
    EXPORT_NAPI_CONST_GL(SRC1_COLOR_EXT);
    EXPORT_NAPI_CONST_GL(SRC1_ALPHA_EXT);
    EXPORT_NAPI_CONST_GL(ONE_MINUS_SRC1_COLOR_EXT);
    EXPORT_NAPI_CONST_GL(ONE_MINUS_SRC1_ALPHA_EXT);
    EXPORT_NAPI_CONST_GL(SRC_ALPHA_SATURATE_EXT);
    EXPORT_NAPI_CONST_GL(LOCATION_INDEX_EXT);
    EXPORT_NAPI_CONST_GL(MAX_DUAL_SOURCE_DRAW_BUFFERS_EXT);
    EXPORT_NAPI_CONST_GL(MIN_EXT);
    EXPORT_NAPI_CONST_GL(MAX_EXT);
    EXPORT_NAPI_CONST_GL(FUNC_ADD_EXT);
    EXPORT_NAPI_CONST_GL(BLEND_EQUATION_EXT);
    EXPORT_NAPI_CONST_GL(MAP_PERSISTENT_BIT_EXT);
    EXPORT_NAPI_CONST_GL(MAP_COHERENT_BIT_EXT);
    EXPORT_NAPI_CONST_GL(DYNAMIC_STORAGE_BIT_EXT);
    EXPORT_NAPI_CONST_GL(CLIENT_STORAGE_BIT_EXT);
    EXPORT_NAPI_CONST_GL(CLIENT_MAPPED_BUFFER_BARRIER_BIT_EXT);
    EXPORT_NAPI_CONST_GL(BUFFER_IMMUTABLE_STORAGE_EXT);
    EXPORT_NAPI_CONST_GL(BUFFER_STORAGE_FLAGS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_CLIP_DISTANCES_EXT);
    EXPORT_NAPI_CONST_GL(MAX_CULL_DISTANCES_EXT);
    EXPORT_NAPI_CONST_GL(MAX_COMBINED_CLIP_AND_CULL_DISTANCES_EXT);
    EXPORT_NAPI_CONST_GL(CLIP_DISTANCE0_EXT);
    EXPORT_NAPI_CONST_GL(CLIP_DISTANCE1_EXT);
    EXPORT_NAPI_CONST_GL(CLIP_DISTANCE2_EXT);
    EXPORT_NAPI_CONST_GL(CLIP_DISTANCE3_EXT);
    EXPORT_NAPI_CONST_GL(CLIP_DISTANCE4_EXT);
    EXPORT_NAPI_CONST_GL(CLIP_DISTANCE5_EXT);
    EXPORT_NAPI_CONST_GL(CLIP_DISTANCE6_EXT);
    EXPORT_NAPI_CONST_GL(CLIP_DISTANCE7_EXT);
    EXPORT_NAPI_CONST_GL(RGBA16F_EXT);
    EXPORT_NAPI_CONST_GL(RGB16F_EXT);
    EXPORT_NAPI_CONST_GL(RG16F_EXT);
    EXPORT_NAPI_CONST_GL(R16F_EXT);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE_EXT);
    EXPORT_NAPI_CONST_GL(UNSIGNED_NORMALIZED_EXT);
    EXPORT_NAPI_CONST_GL(PROGRAM_PIPELINE_OBJECT_EXT);
    EXPORT_NAPI_CONST_GL(PROGRAM_OBJECT_EXT);
    EXPORT_NAPI_CONST_GL(SHADER_OBJECT_EXT);
    EXPORT_NAPI_CONST_GL(BUFFER_OBJECT_EXT);
    EXPORT_NAPI_CONST_GL(QUERY_OBJECT_EXT);
    EXPORT_NAPI_CONST_GL(VERTEX_ARRAY_OBJECT_EXT);
    EXPORT_NAPI_CONST_GL(SAMPLER);
    EXPORT_NAPI_CONST_GL(COLOR_EXT);
    EXPORT_NAPI_CONST_GL(DEPTH_EXT);
    EXPORT_NAPI_CONST_GL(STENCIL_EXT);
    EXPORT_NAPI_CONST_GL(QUERY_COUNTER_BITS_EXT);
    EXPORT_NAPI_CONST_GL(CURRENT_QUERY_EXT);
    EXPORT_NAPI_CONST_GL(QUERY_RESULT_EXT);
    EXPORT_NAPI_CONST_GL(QUERY_RESULT_AVAILABLE_EXT);
    EXPORT_NAPI_CONST_GL(TIME_ELAPSED_EXT);
    EXPORT_NAPI_CONST_GL(TIMESTAMP_EXT);
    EXPORT_NAPI_CONST_GL(GPU_DISJOINT_EXT);
    EXPORT_NAPI_CONST_GL(MAX_COLOR_ATTACHMENTS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_DRAW_BUFFERS_EXT);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER0_EXT);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER1_EXT);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER2_EXT);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER3_EXT);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER4_EXT);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER5_EXT);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER6_EXT);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER7_EXT);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER8_EXT);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER9_EXT);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER10_EXT);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER11_EXT);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER12_EXT);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER13_EXT);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER14_EXT);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER15_EXT);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT0_EXT);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT1_EXT);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT2_EXT);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT3_EXT);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT4_EXT);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT5_EXT);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT6_EXT);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT7_EXT);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT8_EXT);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT9_EXT);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT10_EXT);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT11_EXT);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT12_EXT);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT13_EXT);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT14_EXT);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT15_EXT);
    EXPORT_NAPI_CONST_GL(GEOMETRY_SHADER_EXT);
    EXPORT_NAPI_CONST_GL(GEOMETRY_SHADER_BIT_EXT);
    EXPORT_NAPI_CONST_GL(GEOMETRY_LINKED_VERTICES_OUT_EXT);
    EXPORT_NAPI_CONST_GL(GEOMETRY_LINKED_INPUT_TYPE_EXT);
    EXPORT_NAPI_CONST_GL(GEOMETRY_LINKED_OUTPUT_TYPE_EXT);
    EXPORT_NAPI_CONST_GL(GEOMETRY_SHADER_INVOCATIONS_EXT);
    EXPORT_NAPI_CONST_GL(LAYER_PROVOKING_VERTEX_EXT);
    EXPORT_NAPI_CONST_GL(LINES_ADJACENCY_EXT);
    EXPORT_NAPI_CONST_GL(LINE_STRIP_ADJACENCY_EXT);
    EXPORT_NAPI_CONST_GL(TRIANGLES_ADJACENCY_EXT);
    EXPORT_NAPI_CONST_GL(TRIANGLE_STRIP_ADJACENCY_EXT);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_UNIFORM_COMPONENTS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_UNIFORM_BLOCKS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_INPUT_COMPONENTS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_OUTPUT_COMPONENTS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_OUTPUT_VERTICES_EXT);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_SHADER_INVOCATIONS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_ATOMIC_COUNTERS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_IMAGE_UNIFORMS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_SHADER_STORAGE_BLOCKS_EXT);
    EXPORT_NAPI_CONST_GL(FIRST_VERTEX_CONVENTION_EXT);
    EXPORT_NAPI_CONST_GL(LAST_VERTEX_CONVENTION_EXT);
    EXPORT_NAPI_CONST_GL(UNDEFINED_VERTEX_EXT);
    EXPORT_NAPI_CONST_GL(PRIMITIVES_GENERATED_EXT);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_DEFAULT_LAYERS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_FRAMEBUFFER_LAYERS_EXT);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_LAYERED_EXT);
    EXPORT_NAPI_CONST_GL(REFERENCED_BY_GEOMETRY_SHADER_EXT);
    EXPORT_NAPI_CONST_GL(VERTEX_ATTRIB_ARRAY_DIVISOR_EXT);
    EXPORT_NAPI_CONST_GL(MAP_READ_BIT_EXT);
    EXPORT_NAPI_CONST_GL(MAP_WRITE_BIT_EXT);
    EXPORT_NAPI_CONST_GL(MAP_INVALIDATE_RANGE_BIT_EXT);
    EXPORT_NAPI_CONST_GL(MAP_INVALIDATE_BUFFER_BIT_EXT);
    EXPORT_NAPI_CONST_GL(MAP_FLUSH_EXPLICIT_BIT_EXT);
    EXPORT_NAPI_CONST_GL(MAP_UNSYNCHRONIZED_BIT_EXT);
    EXPORT_NAPI_CONST_GL(MULTISAMPLE_EXT);
    EXPORT_NAPI_CONST_GL(SAMPLE_ALPHA_TO_ONE_EXT);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT);
    EXPORT_NAPI_CONST_GL(RENDERBUFFER_SAMPLES_EXT);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT);
    EXPORT_NAPI_CONST_GL(MAX_SAMPLES_EXT);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT_EXT);
    EXPORT_NAPI_CONST_GL(MULTIVIEW_EXT);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER_EXT);
    EXPORT_NAPI_CONST_GL(READ_BUFFER_EXT);
    EXPORT_NAPI_CONST_GL(MAX_MULTIVIEW_BUFFERS_EXT);
    EXPORT_NAPI_CONST_GL(ANY_SAMPLES_PASSED_EXT);
    EXPORT_NAPI_CONST_GL(ANY_SAMPLES_PASSED_CONSERVATIVE_EXT);
    EXPORT_NAPI_CONST_GL(POLYGON_OFFSET_CLAMP_EXT);
    EXPORT_NAPI_CONST_GL(PRIMITIVE_BOUNDING_BOX_EXT);
    EXPORT_NAPI_CONST_GL(CONTEXT_FLAG_PROTECTED_CONTENT_BIT_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_PROTECTED_EXT);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB_PVRTC_2BPPV1_EXT);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB_PVRTC_4BPPV1_EXT);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV2_IMG);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV2_IMG);
    EXPORT_NAPI_CONST_GL(RASTER_MULTISAMPLE_EXT);
    EXPORT_NAPI_CONST_GL(RASTER_SAMPLES_EXT);
    EXPORT_NAPI_CONST_GL(MAX_RASTER_SAMPLES_EXT);
    EXPORT_NAPI_CONST_GL(RASTER_FIXED_SAMPLE_LOCATIONS_EXT);
    EXPORT_NAPI_CONST_GL(MULTISAMPLE_RASTERIZATION_ALLOWED_EXT);
    EXPORT_NAPI_CONST_GL(EFFECTIVE_RASTER_SAMPLES_EXT);
    EXPORT_NAPI_CONST_GL(UNSIGNED_SHORT_4_4_4_4_REV_EXT);
    EXPORT_NAPI_CONST_GL(UNSIGNED_SHORT_1_5_5_5_REV_EXT);
    EXPORT_NAPI_CONST_GL(R16_SNORM_EXT);
    EXPORT_NAPI_CONST_GL(RG16_SNORM_EXT);
    EXPORT_NAPI_CONST_GL(RGBA16_SNORM_EXT);
    EXPORT_NAPI_CONST_GL(GUILTY_CONTEXT_RESET_EXT);
    EXPORT_NAPI_CONST_GL(INNOCENT_CONTEXT_RESET_EXT);
    EXPORT_NAPI_CONST_GL(UNKNOWN_CONTEXT_RESET_EXT);
    EXPORT_NAPI_CONST_GL(CONTEXT_ROBUST_ACCESS_EXT);
    EXPORT_NAPI_CONST_GL(RESET_NOTIFICATION_STRATEGY_EXT);
    EXPORT_NAPI_CONST_GL(LOSE_CONTEXT_ON_RESET_EXT);
    EXPORT_NAPI_CONST_GL(NO_RESET_NOTIFICATION_EXT);
    EXPORT_NAPI_CONST_GL(SRGB_EXT);
    EXPORT_NAPI_CONST_GL(SRGB_ALPHA_EXT);
    EXPORT_NAPI_CONST_GL(SRGB8_ALPHA8_EXT);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_SRGB_EXT);
    EXPORT_NAPI_CONST_GL(ACTIVE_PROGRAM_EXT);
    EXPORT_NAPI_CONST_GL(VERTEX_SHADER_BIT_EXT);
    EXPORT_NAPI_CONST_GL(FRAGMENT_SHADER_BIT_EXT);
    EXPORT_NAPI_CONST_GL(ALL_SHADER_BITS_EXT);
    EXPORT_NAPI_CONST_GL(PROGRAM_SEPARABLE_EXT);
    EXPORT_NAPI_CONST_GL(PROGRAM_PIPELINE_BINDING_EXT);
    EXPORT_NAPI_CONST_GL(FRAGMENT_SHADER_DISCARDS_SAMPLES_EXT);
    EXPORT_NAPI_CONST_GL(MAX_SHADER_PIXEL_LOCAL_STORAGE_FAST_SIZE_EXT);
    EXPORT_NAPI_CONST_GL(MAX_SHADER_PIXEL_LOCAL_STORAGE_SIZE_EXT);
    EXPORT_NAPI_CONST_GL(SHADER_PIXEL_LOCAL_STORAGE_EXT);
    EXPORT_NAPI_CONST_GL(MAX_SHADER_COMBINED_LOCAL_STORAGE_FAST_SIZE_EXT);
    EXPORT_NAPI_CONST_GL(MAX_SHADER_COMBINED_LOCAL_STORAGE_SIZE_EXT);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_INCOMPLETE_INSUFFICIENT_SHADER_COMBINED_LOCAL_STORAGE_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_COMPARE_MODE_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_COMPARE_FUNC_EXT);
    EXPORT_NAPI_CONST_GL(COMPARE_REF_TO_TEXTURE_EXT);
    EXPORT_NAPI_CONST_GL(SAMPLER_2D_SHADOW_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_SPARSE_EXT);
    EXPORT_NAPI_CONST_GL(VIRTUAL_PAGE_SIZE_INDEX_EXT);
    EXPORT_NAPI_CONST_GL(NUM_SPARSE_LEVELS_EXT);
    EXPORT_NAPI_CONST_GL(NUM_VIRTUAL_PAGE_SIZES_EXT);
    EXPORT_NAPI_CONST_GL(VIRTUAL_PAGE_SIZE_X_EXT);
    EXPORT_NAPI_CONST_GL(VIRTUAL_PAGE_SIZE_Y_EXT);
    EXPORT_NAPI_CONST_GL(VIRTUAL_PAGE_SIZE_Z_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_CUBE_MAP_ARRAY_OES);
    EXPORT_NAPI_CONST_GL(MAX_SPARSE_TEXTURE_SIZE_EXT);
    EXPORT_NAPI_CONST_GL(MAX_SPARSE_3D_TEXTURE_SIZE_EXT);
    EXPORT_NAPI_CONST_GL(MAX_SPARSE_ARRAY_TEXTURE_LAYERS_EXT);
    EXPORT_NAPI_CONST_GL(SPARSE_TEXTURE_FULL_ARRAY_CUBE_MIPMAPS_EXT);
    EXPORT_NAPI_CONST_GL(PATCHES_EXT);
    EXPORT_NAPI_CONST_GL(PATCH_VERTICES_EXT);
    EXPORT_NAPI_CONST_GL(TESS_CONTROL_OUTPUT_VERTICES_EXT);
    EXPORT_NAPI_CONST_GL(TESS_GEN_MODE_EXT);
    EXPORT_NAPI_CONST_GL(TESS_GEN_SPACING_EXT);
    EXPORT_NAPI_CONST_GL(TESS_GEN_VERTEX_ORDER_EXT);
    EXPORT_NAPI_CONST_GL(TESS_GEN_POINT_MODE_EXT);
    EXPORT_NAPI_CONST_GL(ISOLINES_EXT);
    EXPORT_NAPI_CONST_GL(QUADS_EXT);
    EXPORT_NAPI_CONST_GL(FRACTIONAL_ODD_EXT);
    EXPORT_NAPI_CONST_GL(FRACTIONAL_EVEN_EXT);
    EXPORT_NAPI_CONST_GL(MAX_PATCH_VERTICES_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TESS_GEN_LEVEL_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TESS_CONTROL_UNIFORM_COMPONENTS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TESS_EVALUATION_UNIFORM_COMPONENTS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TESS_CONTROL_OUTPUT_COMPONENTS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TESS_PATCH_COMPONENTS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TESS_CONTROL_UNIFORM_BLOCKS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TESS_EVALUATION_UNIFORM_BLOCKS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TESS_CONTROL_INPUT_COMPONENTS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TESS_EVALUATION_INPUT_COMPONENTS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TESS_CONTROL_ATOMIC_COUNTERS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TESS_EVALUATION_ATOMIC_COUNTERS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TESS_CONTROL_IMAGE_UNIFORMS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TESS_EVALUATION_IMAGE_UNIFORMS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS_EXT);
    EXPORT_NAPI_CONST_GL(PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED);
    EXPORT_NAPI_CONST_GL(IS_PER_PATCH_EXT);
    EXPORT_NAPI_CONST_GL(REFERENCED_BY_TESS_CONTROL_SHADER_EXT);
    EXPORT_NAPI_CONST_GL(REFERENCED_BY_TESS_EVALUATION_SHADER_EXT);
    EXPORT_NAPI_CONST_GL(TESS_CONTROL_SHADER_EXT);
    EXPORT_NAPI_CONST_GL(TESS_EVALUATION_SHADER_EXT);
    EXPORT_NAPI_CONST_GL(TESS_CONTROL_SHADER_BIT_EXT);
    EXPORT_NAPI_CONST_GL(TESS_EVALUATION_SHADER_BIT_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_BORDER_COLOR_EXT);
    EXPORT_NAPI_CONST_GL(CLAMP_TO_BORDER_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_BUFFER_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_BUFFER_BINDING_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TEXTURE_BUFFER_SIZE_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_BINDING_BUFFER_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_BUFFER_DATA_STORE_BINDING_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_BUFFER_OFFSET_ALIGNMENT_EXT);
    EXPORT_NAPI_CONST_GL(SAMPLER_BUFFER_EXT);
    EXPORT_NAPI_CONST_GL(INT_SAMPLER_BUFFER_EXT);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_SAMPLER_BUFFER_EXT);
    EXPORT_NAPI_CONST_GL(IMAGE_BUFFER_EXT);
    EXPORT_NAPI_CONST_GL(INT_IMAGE_BUFFER_EXT);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_IMAGE_BUFFER_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_BUFFER_OFFSET_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_BUFFER_SIZE_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_ASTC_DECODE_PRECISION_EXT);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGB_S3TC_DXT1_EXT);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_S3TC_DXT1_EXT);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_S3TC_DXT3_EXT);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_S3TC_DXT5_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_CUBE_MAP_ARRAY_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_BINDING_CUBE_MAP_ARRAY_EXT);
    EXPORT_NAPI_CONST_GL(SAMPLER_CUBE_MAP_ARRAY_EXT);
    EXPORT_NAPI_CONST_GL(SAMPLER_CUBE_MAP_ARRAY_SHADOW_EXT);
    EXPORT_NAPI_CONST_GL(INT_SAMPLER_CUBE_MAP_ARRAY_EXT);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_EXT);
    EXPORT_NAPI_CONST_GL(IMAGE_CUBE_MAP_ARRAY_EXT);
    EXPORT_NAPI_CONST_GL(INT_IMAGE_CUBE_MAP_ARRAY_EXT);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_MAX_ANISOTROPY_EXT);
    EXPORT_NAPI_CONST_GL(MAX_TEXTURE_MAX_ANISOTROPY_EXT);
    EXPORT_NAPI_CONST_GL(R16_EXT);
    EXPORT_NAPI_CONST_GL(RG16_EXT);
    EXPORT_NAPI_CONST_GL(RGBA16_EXT);
    EXPORT_NAPI_CONST_GL(RGB16_EXT);
    EXPORT_NAPI_CONST_GL(RGB16_SNORM_EXT);
    EXPORT_NAPI_CONST_GL(RED_EXT);
    EXPORT_NAPI_CONST_GL(RG_EXT);
    EXPORT_NAPI_CONST_GL(R8_EXT);
    EXPORT_NAPI_CONST_GL(RG8_EXT);
    EXPORT_NAPI_CONST_GL(SR8_EXT);
    EXPORT_NAPI_CONST_GL(SRG8_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_SRGB_DECODE_EXT);
    EXPORT_NAPI_CONST_GL(DECODE_EXT);
    EXPORT_NAPI_CONST_GL(SKIP_DECODE_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_IMMUTABLE_FORMAT_EXT);
    EXPORT_NAPI_CONST_GL(ALPHA8_EXT);
    EXPORT_NAPI_CONST_GL(LUMINANCE8_EXT);
    EXPORT_NAPI_CONST_GL(LUMINANCE8_ALPHA8_EXT);
    EXPORT_NAPI_CONST_GL(RGBA32F_EXT);
    EXPORT_NAPI_CONST_GL(RGB32F_EXT);
    EXPORT_NAPI_CONST_GL(ALPHA32F_EXT);
    EXPORT_NAPI_CONST_GL(LUMINANCE32F_EXT);
    EXPORT_NAPI_CONST_GL(LUMINANCE_ALPHA32F_EXT);
    EXPORT_NAPI_CONST_GL(ALPHA16F_EXT);
    EXPORT_NAPI_CONST_GL(LUMINANCE16F_EXT);
    EXPORT_NAPI_CONST_GL(LUMINANCE_ALPHA16F_EXT);
    EXPORT_NAPI_CONST_GL(RGB10_A2_EXT);
    EXPORT_NAPI_CONST_GL(RGB10_EXT);
    EXPORT_NAPI_CONST_GL(R32F_EXT);
    EXPORT_NAPI_CONST_GL(RG32F_EXT);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_2_10_10_10_REV_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_VIEW_MIN_LEVEL_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_VIEW_NUM_LEVELS_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_VIEW_MIN_LAYER_EXT);
    EXPORT_NAPI_CONST_GL(TEXTURE_VIEW_NUM_LAYERS_EXT);
    EXPORT_NAPI_CONST_GL(UNPACK_ROW_LENGTH_EXT);
    EXPORT_NAPI_CONST_GL(UNPACK_SKIP_ROWS_EXT);
    EXPORT_NAPI_CONST_GL(UNPACK_SKIP_PIXELS_EXT);
    EXPORT_NAPI_CONST_GL(INCLUSIVE_EXT);
    EXPORT_NAPI_CONST_GL(EXCLUSIVE_EXT);
    EXPORT_NAPI_CONST_GL(WINDOW_RECTANGLE_EXT);
    EXPORT_NAPI_CONST_GL(WINDOW_RECTANGLE_MODE_EXT);
    EXPORT_NAPI_CONST_GL(MAX_WINDOW_RECTANGLES_EXT);
    EXPORT_NAPI_CONST_GL(NUM_WINDOW_RECTANGLES_EXT);
    EXPORT_NAPI_CONST_GL(GCCSO_SHADER_BINARY_FJ);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_AND_DOWNSAMPLE_IMG);
    EXPORT_NAPI_CONST_GL(NUM_DOWNSAMPLE_SCALES_IMG);
    EXPORT_NAPI_CONST_GL(DOWNSAMPLE_SCALES_IMG);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_TEXTURE_SCALE_IMG);
    EXPORT_NAPI_CONST_GL(RENDERBUFFER_SAMPLES_IMG);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG);
    EXPORT_NAPI_CONST_GL(MAX_SAMPLES_IMG);
    EXPORT_NAPI_CONST_GL(TEXTURE_SAMPLES_IMG);
    EXPORT_NAPI_CONST_GL(SGX_PROGRAM_BINARY_IMG);
    EXPORT_NAPI_CONST_GL(BGRA_IMG);
    EXPORT_NAPI_CONST_GL(UNSIGNED_SHORT_4_4_4_4_REV_IMG);
    EXPORT_NAPI_CONST_GL(SGX_BINARY_IMG);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGB_PVRTC_4BPPV1_IMG);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGB_PVRTC_2BPPV1_IMG);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_PVRTC_4BPPV1_IMG);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_PVRTC_2BPPV1_IMG);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_PVRTC_2BPPV2_IMG);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_PVRTC_4BPPV2_IMG);
    EXPORT_NAPI_CONST_GL(CUBIC_IMG);
    EXPORT_NAPI_CONST_GL(CUBIC_MIPMAP_NEAREST_IMG);
    EXPORT_NAPI_CONST_GL(CUBIC_MIPMAP_LINEAR_IMG);
    EXPORT_NAPI_CONST_GL(CONSERVATIVE_RASTERIZATION_INTEL);
    EXPORT_NAPI_CONST_GL(PERFQUERY_SINGLE_CONTEXT_INTEL);
    EXPORT_NAPI_CONST_GL(PERFQUERY_GLOBAL_CONTEXT_INTEL);
    EXPORT_NAPI_CONST_GL(PERFQUERY_WAIT_INTEL);
    EXPORT_NAPI_CONST_GL(PERFQUERY_FLUSH_INTEL);
    EXPORT_NAPI_CONST_GL(PERFQUERY_DONOT_FLUSH_INTEL);
    EXPORT_NAPI_CONST_GL(PERFQUERY_COUNTER_EVENT_INTEL);
    EXPORT_NAPI_CONST_GL(PERFQUERY_COUNTER_DURATION_NORM_INTEL);
    EXPORT_NAPI_CONST_GL(PERFQUERY_COUNTER_DURATION_RAW_INTEL);
    EXPORT_NAPI_CONST_GL(PERFQUERY_COUNTER_THROUGHPUT_INTEL);
    EXPORT_NAPI_CONST_GL(PERFQUERY_COUNTER_RAW_INTEL);
    EXPORT_NAPI_CONST_GL(PERFQUERY_COUNTER_TIMESTAMP_INTEL);
    EXPORT_NAPI_CONST_GL(PERFQUERY_COUNTER_DATA_UINT32_INTEL);
    EXPORT_NAPI_CONST_GL(PERFQUERY_COUNTER_DATA_UINT64_INTEL);
    EXPORT_NAPI_CONST_GL(PERFQUERY_COUNTER_DATA_FLOAT_INTEL);
    EXPORT_NAPI_CONST_GL(PERFQUERY_COUNTER_DATA_DOUBLE_INTEL);
    EXPORT_NAPI_CONST_GL(PERFQUERY_COUNTER_DATA_BOOL32_INTEL);
    EXPORT_NAPI_CONST_GL(PERFQUERY_QUERY_NAME_LENGTH_MAX_INTEL);
    EXPORT_NAPI_CONST_GL(PERFQUERY_COUNTER_NAME_LENGTH_MAX_INTEL);
    EXPORT_NAPI_CONST_GL(PERFQUERY_COUNTER_DESC_LENGTH_MAX_INTEL);
    EXPORT_NAPI_CONST_GL(PERFQUERY_GPA_EXTENDED_COUNTERS_INTEL);
    EXPORT_NAPI_CONST_GL(MULTIPLY_KHR);
    EXPORT_NAPI_CONST_GL(SCREEN_KHR);
    EXPORT_NAPI_CONST_GL(OVERLAY_KHR);
    EXPORT_NAPI_CONST_GL(DARKEN_KHR);
    EXPORT_NAPI_CONST_GL(LIGHTEN_KHR);
    EXPORT_NAPI_CONST_GL(COLORDODGE_KHR);
    EXPORT_NAPI_CONST_GL(COLORBURN_KHR);
    EXPORT_NAPI_CONST_GL(HARDLIGHT_KHR);
    EXPORT_NAPI_CONST_GL(SOFTLIGHT_KHR);
    EXPORT_NAPI_CONST_GL(DIFFERENCE_KHR);
    EXPORT_NAPI_CONST_GL(EXCLUSION_KHR);
    EXPORT_NAPI_CONST_GL(HSL_HUE_KHR);
    EXPORT_NAPI_CONST_GL(HSL_SATURATION_KHR);
    EXPORT_NAPI_CONST_GL(HSL_COLOR_KHR);
    EXPORT_NAPI_CONST_GL(HSL_LUMINOSITY_KHR);
    EXPORT_NAPI_CONST_GL(BLEND_ADVANCED_COHERENT_KHR);
    EXPORT_NAPI_CONST_GL(CONTEXT_RELEASE_BEHAVIOR);
    EXPORT_NAPI_CONST_GL(CONTEXT_RELEASE_BEHAVIOR_FLUSH);
    EXPORT_NAPI_CONST_GL(CONTEXT_RELEASE_BEHAVIOR_KHR);
    EXPORT_NAPI_CONST_GL(CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_OUTPUT_SYNCHRONOUS);
    EXPORT_NAPI_CONST_GL(DEBUG_NEXT_LOGGED_MESSAGE_LENGTH);
    EXPORT_NAPI_CONST_GL(DEBUG_CALLBACK_FUNCTION);
    EXPORT_NAPI_CONST_GL(DEBUG_CALLBACK_USER_PARAM);
    EXPORT_NAPI_CONST_GL(DEBUG_SOURCE_API);
    EXPORT_NAPI_CONST_GL(DEBUG_SOURCE_WINDOW_SYSTEM);
    EXPORT_NAPI_CONST_GL(DEBUG_SOURCE_SHADER_COMPILER);
    EXPORT_NAPI_CONST_GL(DEBUG_SOURCE_THIRD_PARTY);
    EXPORT_NAPI_CONST_GL(DEBUG_SOURCE_APPLICATION);
    EXPORT_NAPI_CONST_GL(DEBUG_SOURCE_OTHER);
    EXPORT_NAPI_CONST_GL(DEBUG_TYPE_ERROR);
    EXPORT_NAPI_CONST_GL(DEBUG_TYPE_DEPRECATED_BEHAVIOR);
    EXPORT_NAPI_CONST_GL(DEBUG_TYPE_UNDEFINED_BEHAVIOR);
    EXPORT_NAPI_CONST_GL(DEBUG_TYPE_PORTABILITY);
    EXPORT_NAPI_CONST_GL(DEBUG_TYPE_PERFORMANCE);
    EXPORT_NAPI_CONST_GL(DEBUG_TYPE_OTHER);
    EXPORT_NAPI_CONST_GL(DEBUG_TYPE_MARKER);
    EXPORT_NAPI_CONST_GL(DEBUG_TYPE_PUSH_GROUP);
    EXPORT_NAPI_CONST_GL(DEBUG_TYPE_POP_GROUP);
    EXPORT_NAPI_CONST_GL(DEBUG_SEVERITY_NOTIFICATION);
    EXPORT_NAPI_CONST_GL(MAX_DEBUG_GROUP_STACK_DEPTH);
    EXPORT_NAPI_CONST_GL(DEBUG_GROUP_STACK_DEPTH);
    EXPORT_NAPI_CONST_GL(BUFFER);
    EXPORT_NAPI_CONST_GL(SHADER);
    EXPORT_NAPI_CONST_GL(PROGRAM);
    EXPORT_NAPI_CONST_GL(VERTEX_ARRAY);
    EXPORT_NAPI_CONST_GL(QUERY);
    EXPORT_NAPI_CONST_GL(PROGRAM_PIPELINE);
    EXPORT_NAPI_CONST_GL(MAX_LABEL_LENGTH);
    EXPORT_NAPI_CONST_GL(MAX_DEBUG_MESSAGE_LENGTH);
    EXPORT_NAPI_CONST_GL(MAX_DEBUG_LOGGED_MESSAGES);
    EXPORT_NAPI_CONST_GL(DEBUG_LOGGED_MESSAGES);
    EXPORT_NAPI_CONST_GL(DEBUG_SEVERITY_HIGH);
    EXPORT_NAPI_CONST_GL(DEBUG_SEVERITY_MEDIUM);
    EXPORT_NAPI_CONST_GL(DEBUG_SEVERITY_LOW);
    EXPORT_NAPI_CONST_GL(DEBUG_OUTPUT);
    EXPORT_NAPI_CONST_GL(CONTEXT_FLAG_DEBUG_BIT);
    EXPORT_NAPI_CONST_GL(STACK_OVERFLOW);
    EXPORT_NAPI_CONST_GL(STACK_UNDERFLOW);
    EXPORT_NAPI_CONST_GL(DEBUG_OUTPUT_SYNCHRONOUS_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_CALLBACK_FUNCTION_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_CALLBACK_USER_PARAM_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_SOURCE_API_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_SOURCE_WINDOW_SYSTEM_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_SOURCE_SHADER_COMPILER_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_SOURCE_THIRD_PARTY_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_SOURCE_APPLICATION_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_SOURCE_OTHER_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_TYPE_ERROR_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_TYPE_DEPRECATED_BEHAVIOR_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_TYPE_UNDEFINED_BEHAVIOR_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_TYPE_PORTABILITY_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_TYPE_PERFORMANCE_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_TYPE_OTHER_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_TYPE_MARKER_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_TYPE_PUSH_GROUP_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_TYPE_POP_GROUP_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_SEVERITY_NOTIFICATION_KHR);
    EXPORT_NAPI_CONST_GL(MAX_DEBUG_GROUP_STACK_DEPTH_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_GROUP_STACK_DEPTH_KHR);
    EXPORT_NAPI_CONST_GL(BUFFER_KHR);
    EXPORT_NAPI_CONST_GL(SHADER_KHR);
    EXPORT_NAPI_CONST_GL(PROGRAM_KHR);
    EXPORT_NAPI_CONST_GL(VERTEX_ARRAY_KHR);
    EXPORT_NAPI_CONST_GL(QUERY_KHR);
    EXPORT_NAPI_CONST_GL(PROGRAM_PIPELINE_KHR);
    EXPORT_NAPI_CONST_GL(SAMPLER_KHR);
    EXPORT_NAPI_CONST_GL(MAX_LABEL_LENGTH_KHR);
    EXPORT_NAPI_CONST_GL(MAX_DEBUG_MESSAGE_LENGTH_KHR);
    EXPORT_NAPI_CONST_GL(MAX_DEBUG_LOGGED_MESSAGES_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_LOGGED_MESSAGES_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_SEVERITY_HIGH_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_SEVERITY_MEDIUM_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_SEVERITY_LOW_KHR);
    EXPORT_NAPI_CONST_GL(DEBUG_OUTPUT_KHR);
    EXPORT_NAPI_CONST_GL(CONTEXT_FLAG_DEBUG_BIT_KHR);
    EXPORT_NAPI_CONST_GL(STACK_OVERFLOW_KHR);
    EXPORT_NAPI_CONST_GL(STACK_UNDERFLOW_KHR);
    EXPORT_NAPI_CONST_GL(DISPLAY_LIST);
    EXPORT_NAPI_CONST_GL(CONTEXT_FLAG_NO_ERROR_BIT_KHR);
    EXPORT_NAPI_CONST_GL(CONTEXT_ROBUST_ACCESS);
    EXPORT_NAPI_CONST_GL(LOSE_CONTEXT_ON_RESET);
    EXPORT_NAPI_CONST_GL(GUILTY_CONTEXT_RESET);
    EXPORT_NAPI_CONST_GL(INNOCENT_CONTEXT_RESET);
    EXPORT_NAPI_CONST_GL(UNKNOWN_CONTEXT_RESET);
    EXPORT_NAPI_CONST_GL(RESET_NOTIFICATION_STRATEGY);
    EXPORT_NAPI_CONST_GL(NO_RESET_NOTIFICATION);
    EXPORT_NAPI_CONST_GL(CONTEXT_LOST);
    EXPORT_NAPI_CONST_GL(CONTEXT_ROBUST_ACCESS_KHR);
    EXPORT_NAPI_CONST_GL(LOSE_CONTEXT_ON_RESET_KHR);
    EXPORT_NAPI_CONST_GL(GUILTY_CONTEXT_RESET_KHR);
    EXPORT_NAPI_CONST_GL(INNOCENT_CONTEXT_RESET_KHR);
    EXPORT_NAPI_CONST_GL(UNKNOWN_CONTEXT_RESET_KHR);
    EXPORT_NAPI_CONST_GL(RESET_NOTIFICATION_STRATEGY_KHR);
    EXPORT_NAPI_CONST_GL(NO_RESET_NOTIFICATION_KHR);
    EXPORT_NAPI_CONST_GL(CONTEXT_LOST_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_4x4_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_5x4_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_5x5_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_6x5_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_6x6_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_8x5_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_8x6_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_8x8_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_10x5_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_10x6_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_10x8_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_10x10_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_12x10_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_12x12_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR);
    EXPORT_NAPI_CONST_GL(BLEND_OVERLAP_NV);
    EXPORT_NAPI_CONST_GL(BLEND_PREMULTIPLIED_SRC_NV);
    EXPORT_NAPI_CONST_GL(BLUE_NV);
    EXPORT_NAPI_CONST_GL(COLORBURN_NV);
    EXPORT_NAPI_CONST_GL(COLORDODGE_NV);
    EXPORT_NAPI_CONST_GL(CONJOINT_NV);
    EXPORT_NAPI_CONST_GL(CONTRAST_NV);
    EXPORT_NAPI_CONST_GL(DARKEN_NV);
    EXPORT_NAPI_CONST_GL(DIFFERENCE_NV);
    EXPORT_NAPI_CONST_GL(DISJOINT_NV);
    EXPORT_NAPI_CONST_GL(DST_ATOP_NV);
    EXPORT_NAPI_CONST_GL(DST_IN_NV);
    EXPORT_NAPI_CONST_GL(DST_NV);
    EXPORT_NAPI_CONST_GL(DST_OUT_NV);
    EXPORT_NAPI_CONST_GL(DST_OVER_NV);
    EXPORT_NAPI_CONST_GL(EXCLUSION_NV);
    EXPORT_NAPI_CONST_GL(GREEN_NV);
    EXPORT_NAPI_CONST_GL(HARDLIGHT_NV);
    EXPORT_NAPI_CONST_GL(HARDMIX_NV);
    EXPORT_NAPI_CONST_GL(HSL_COLOR_NV);
    EXPORT_NAPI_CONST_GL(HSL_HUE_NV);
    EXPORT_NAPI_CONST_GL(HSL_LUMINOSITY_NV);
    EXPORT_NAPI_CONST_GL(HSL_SATURATION_NV);
    EXPORT_NAPI_CONST_GL(INVERT_OVG_NV);
    EXPORT_NAPI_CONST_GL(INVERT_RGB_NV);
    EXPORT_NAPI_CONST_GL(LIGHTEN_NV);
    EXPORT_NAPI_CONST_GL(LINEARBURN_NV);
    EXPORT_NAPI_CONST_GL(LINEARDODGE_NV);
    EXPORT_NAPI_CONST_GL(LINEARLIGHT_NV);
    EXPORT_NAPI_CONST_GL(MINUS_CLAMPED_NV);
    EXPORT_NAPI_CONST_GL(MINUS_NV);
    EXPORT_NAPI_CONST_GL(MULTIPLY_NV);
    EXPORT_NAPI_CONST_GL(OVERLAY_NV);
    EXPORT_NAPI_CONST_GL(PINLIGHT_NV);
    EXPORT_NAPI_CONST_GL(PLUS_CLAMPED_ALPHA_NV);
    EXPORT_NAPI_CONST_GL(PLUS_CLAMPED_NV);
    EXPORT_NAPI_CONST_GL(PLUS_DARKER_NV);
    EXPORT_NAPI_CONST_GL(PLUS_NV);
    EXPORT_NAPI_CONST_GL(RED_NV);
    EXPORT_NAPI_CONST_GL(SCREEN_NV);
    EXPORT_NAPI_CONST_GL(SOFTLIGHT_NV);
    EXPORT_NAPI_CONST_GL(SRC_ATOP_NV);
    EXPORT_NAPI_CONST_GL(SRC_IN_NV);
    EXPORT_NAPI_CONST_GL(SRC_NV);
    EXPORT_NAPI_CONST_GL(SRC_OUT_NV);
    EXPORT_NAPI_CONST_GL(SRC_OVER_NV);
    EXPORT_NAPI_CONST_GL(UNCORRELATED_NV);
    EXPORT_NAPI_CONST_GL(VIVIDLIGHT_NV);
    EXPORT_NAPI_CONST_GL(XOR_NV);
    EXPORT_NAPI_CONST_GL(BLEND_ADVANCED_COHERENT_NV);
    EXPORT_NAPI_CONST_GL(QUERY_WAIT_NV);
    EXPORT_NAPI_CONST_GL(QUERY_NO_WAIT_NV);
    EXPORT_NAPI_CONST_GL(QUERY_BY_REGION_WAIT_NV);
    EXPORT_NAPI_CONST_GL(QUERY_BY_REGION_NO_WAIT_NV);
    EXPORT_NAPI_CONST_GL(CONSERVATIVE_RASTERIZATION_NV);
    EXPORT_NAPI_CONST_GL(SUBPIXEL_PRECISION_BIAS_X_BITS_NV);
    EXPORT_NAPI_CONST_GL(SUBPIXEL_PRECISION_BIAS_Y_BITS_NV);
    EXPORT_NAPI_CONST_GL(MAX_SUBPIXEL_PRECISION_BIAS_BITS_NV);
    EXPORT_NAPI_CONST_GL(CONSERVATIVE_RASTER_MODE_NV);
    EXPORT_NAPI_CONST_GL(CONSERVATIVE_RASTER_MODE_POST_SNAP_NV);
    EXPORT_NAPI_CONST_GL(CONSERVATIVE_RASTER_MODE_PRE_SNAP_TRIANGLES_NV);
    EXPORT_NAPI_CONST_GL(COPY_READ_BUFFER_NV);
    EXPORT_NAPI_CONST_GL(COPY_WRITE_BUFFER_NV);
    EXPORT_NAPI_CONST_GL(COVERAGE_COMPONENT_NV);
    EXPORT_NAPI_CONST_GL(COVERAGE_COMPONENT4_NV);
    EXPORT_NAPI_CONST_GL(COVERAGE_ATTACHMENT_NV);
    EXPORT_NAPI_CONST_GL(COVERAGE_BUFFERS_NV);
    EXPORT_NAPI_CONST_GL(COVERAGE_SAMPLES_NV);
    EXPORT_NAPI_CONST_GL(COVERAGE_ALL_FRAGMENTS_NV);
    EXPORT_NAPI_CONST_GL(COVERAGE_EDGE_FRAGMENTS_NV);
    EXPORT_NAPI_CONST_GL(COVERAGE_AUTOMATIC_NV);
    EXPORT_NAPI_CONST_GL(COVERAGE_BUFFER_BIT_NV);
    EXPORT_NAPI_CONST_GL(DEPTH_COMPONENT16_NONLINEAR_NV);
    EXPORT_NAPI_CONST_GL(MAX_DRAW_BUFFERS_NV);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER0_NV);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER1_NV);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER2_NV);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER3_NV);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER4_NV);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER5_NV);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER6_NV);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER7_NV);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER8_NV);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER9_NV);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER10_NV);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER11_NV);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER12_NV);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER13_NV);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER14_NV);
    EXPORT_NAPI_CONST_GL(DRAW_BUFFER15_NV);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT0_NV);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT1_NV);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT2_NV);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT3_NV);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT4_NV);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT5_NV);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT6_NV);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT7_NV);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT8_NV);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT9_NV);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT10_NV);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT11_NV);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT12_NV);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT13_NV);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT14_NV);
    EXPORT_NAPI_CONST_GL(COLOR_ATTACHMENT15_NV);
    EXPORT_NAPI_CONST_GL(MAX_COLOR_ATTACHMENTS_NV);
    EXPORT_NAPI_CONST_GL(ALL_COMPLETED_NV);
    EXPORT_NAPI_CONST_GL(FENCE_STATUS_NV);
    EXPORT_NAPI_CONST_GL(FENCE_CONDITION_NV);
    EXPORT_NAPI_CONST_GL(FILL_RECTANGLE_NV);
    EXPORT_NAPI_CONST_GL(FRAGMENT_COVERAGE_TO_COLOR_NV);
    EXPORT_NAPI_CONST_GL(FRAGMENT_COVERAGE_COLOR_NV);
    EXPORT_NAPI_CONST_GL(READ_FRAMEBUFFER_NV);
    EXPORT_NAPI_CONST_GL(DRAW_FRAMEBUFFER_NV);
    EXPORT_NAPI_CONST_GL(DRAW_FRAMEBUFFER_BINDING_NV);
    EXPORT_NAPI_CONST_GL(READ_FRAMEBUFFER_BINDING_NV);
    EXPORT_NAPI_CONST_GL(COVERAGE_MODULATION_TABLE_NV);
    EXPORT_NAPI_CONST_GL(COLOR_SAMPLES_NV);
    EXPORT_NAPI_CONST_GL(DEPTH_SAMPLES_NV);
    EXPORT_NAPI_CONST_GL(STENCIL_SAMPLES_NV);
    EXPORT_NAPI_CONST_GL(MIXED_DEPTH_SAMPLES_SUPPORTED_NV);
    EXPORT_NAPI_CONST_GL(MIXED_STENCIL_SAMPLES_SUPPORTED_NV);
    EXPORT_NAPI_CONST_GL(COVERAGE_MODULATION_NV);
    EXPORT_NAPI_CONST_GL(COVERAGE_MODULATION_TABLE_SIZE_NV);
    EXPORT_NAPI_CONST_GL(RENDERBUFFER_SAMPLES_NV);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_NV);
    EXPORT_NAPI_CONST_GL(MAX_SAMPLES_NV);
    EXPORT_NAPI_CONST_GL(INT64_NV);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT64_NV);
    EXPORT_NAPI_CONST_GL(INT8_NV);
    EXPORT_NAPI_CONST_GL(INT8_VEC2_NV);
    EXPORT_NAPI_CONST_GL(INT8_VEC3_NV);
    EXPORT_NAPI_CONST_GL(INT8_VEC4_NV);
    EXPORT_NAPI_CONST_GL(INT16_NV);
    EXPORT_NAPI_CONST_GL(INT16_VEC2_NV);
    EXPORT_NAPI_CONST_GL(INT16_VEC3_NV);
    EXPORT_NAPI_CONST_GL(INT16_VEC4_NV);
    EXPORT_NAPI_CONST_GL(INT64_VEC2_NV);
    EXPORT_NAPI_CONST_GL(INT64_VEC3_NV);
    EXPORT_NAPI_CONST_GL(INT64_VEC4_NV);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT8_NV);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT8_VEC2_NV);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT8_VEC3_NV);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT8_VEC4_NV);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT16_NV);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT16_VEC2_NV);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT16_VEC3_NV);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT16_VEC4_NV);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT64_VEC2_NV);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT64_VEC3_NV);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT64_VEC4_NV);
    EXPORT_NAPI_CONST_GL(FLOAT16_NV);
    EXPORT_NAPI_CONST_GL(FLOAT16_VEC2_NV);
    EXPORT_NAPI_CONST_GL(FLOAT16_VEC3_NV);
    EXPORT_NAPI_CONST_GL(FLOAT16_VEC4_NV);
    EXPORT_NAPI_CONST_GL(PATCHES);
    EXPORT_NAPI_CONST_GL(VERTEX_ATTRIB_ARRAY_DIVISOR_NV);
    EXPORT_NAPI_CONST_GL(TEXTURE_2D_MULTISAMPLE);
    EXPORT_NAPI_CONST_GL(TEXTURE_2D_MULTISAMPLE_ARRAY);
    EXPORT_NAPI_CONST_GL(MULTISAMPLES_NV);
    EXPORT_NAPI_CONST_GL(SUPERSAMPLE_SCALE_X_NV);
    EXPORT_NAPI_CONST_GL(SUPERSAMPLE_SCALE_Y_NV);
    EXPORT_NAPI_CONST_GL(CONFORMANT_NV);
    EXPORT_NAPI_CONST_GL(FLOAT_MAT2x3_NV);
    EXPORT_NAPI_CONST_GL(FLOAT_MAT2x4_NV);
    EXPORT_NAPI_CONST_GL(FLOAT_MAT3x2_NV);
    EXPORT_NAPI_CONST_GL(FLOAT_MAT3x4_NV);
    EXPORT_NAPI_CONST_GL(FLOAT_MAT4x2_NV);
    EXPORT_NAPI_CONST_GL(FLOAT_MAT4x3_NV);
    EXPORT_NAPI_CONST_GL(PATH_FORMAT_SVG_NV);
    EXPORT_NAPI_CONST_GL(PATH_FORMAT_PS_NV);
    EXPORT_NAPI_CONST_GL(STANDARD_FONT_NAME_NV);
    EXPORT_NAPI_CONST_GL(SYSTEM_FONT_NAME_NV);
    EXPORT_NAPI_CONST_GL(FILE_NAME_NV);
    EXPORT_NAPI_CONST_GL(PATH_STROKE_WIDTH_NV);
    EXPORT_NAPI_CONST_GL(PATH_END_CAPS_NV);
    EXPORT_NAPI_CONST_GL(PATH_INITIAL_END_CAP_NV);
    EXPORT_NAPI_CONST_GL(PATH_TERMINAL_END_CAP_NV);
    EXPORT_NAPI_CONST_GL(PATH_JOIN_STYLE_NV);
    EXPORT_NAPI_CONST_GL(PATH_MITER_LIMIT_NV);
    EXPORT_NAPI_CONST_GL(PATH_DASH_CAPS_NV);
    EXPORT_NAPI_CONST_GL(PATH_INITIAL_DASH_CAP_NV);
    EXPORT_NAPI_CONST_GL(PATH_TERMINAL_DASH_CAP_NV);
    EXPORT_NAPI_CONST_GL(PATH_DASH_OFFSET_NV);
    EXPORT_NAPI_CONST_GL(PATH_CLIENT_LENGTH_NV);
    EXPORT_NAPI_CONST_GL(PATH_FILL_MODE_NV);
    EXPORT_NAPI_CONST_GL(PATH_FILL_MASK_NV);
    EXPORT_NAPI_CONST_GL(PATH_FILL_COVER_MODE_NV);
    EXPORT_NAPI_CONST_GL(PATH_STROKE_COVER_MODE_NV);
    EXPORT_NAPI_CONST_GL(PATH_STROKE_MASK_NV);
    EXPORT_NAPI_CONST_GL(COUNT_UP_NV);
    EXPORT_NAPI_CONST_GL(COUNT_DOWN_NV);
    EXPORT_NAPI_CONST_GL(PATH_OBJECT_BOUNDING_BOX_NV);
    EXPORT_NAPI_CONST_GL(CONVEX_HULL_NV);
    EXPORT_NAPI_CONST_GL(BOUNDING_BOX_NV);
    EXPORT_NAPI_CONST_GL(TRANSLATE_X_NV);
    EXPORT_NAPI_CONST_GL(TRANSLATE_Y_NV);
    EXPORT_NAPI_CONST_GL(TRANSLATE_2D_NV);
    EXPORT_NAPI_CONST_GL(TRANSLATE_3D_NV);
    EXPORT_NAPI_CONST_GL(AFFINE_2D_NV);
    EXPORT_NAPI_CONST_GL(AFFINE_3D_NV);
    EXPORT_NAPI_CONST_GL(TRANSPOSE_AFFINE_2D_NV);
    EXPORT_NAPI_CONST_GL(TRANSPOSE_AFFINE_3D_NV);
    EXPORT_NAPI_CONST_GL(UTF8_NV);
    EXPORT_NAPI_CONST_GL(UTF16_NV);
    EXPORT_NAPI_CONST_GL(BOUNDING_BOX_OF_BOUNDING_BOXES_NV);
    EXPORT_NAPI_CONST_GL(PATH_COMMAND_COUNT_NV);
    EXPORT_NAPI_CONST_GL(PATH_COORD_COUNT_NV);
    EXPORT_NAPI_CONST_GL(PATH_DASH_ARRAY_COUNT_NV);
    EXPORT_NAPI_CONST_GL(PATH_COMPUTED_LENGTH_NV);
    EXPORT_NAPI_CONST_GL(PATH_FILL_BOUNDING_BOX_NV);
    EXPORT_NAPI_CONST_GL(PATH_STROKE_BOUNDING_BOX_NV);
    EXPORT_NAPI_CONST_GL(SQUARE_NV);
    EXPORT_NAPI_CONST_GL(ROUND_NV);
    EXPORT_NAPI_CONST_GL(TRIANGULAR_NV);
    EXPORT_NAPI_CONST_GL(BEVEL_NV);
    EXPORT_NAPI_CONST_GL(MITER_REVERT_NV);
    EXPORT_NAPI_CONST_GL(MITER_TRUNCATE_NV);
    EXPORT_NAPI_CONST_GL(SKIP_MISSING_GLYPH_NV);
    EXPORT_NAPI_CONST_GL(USE_MISSING_GLYPH_NV);
    EXPORT_NAPI_CONST_GL(PATH_ERROR_POSITION_NV);
    EXPORT_NAPI_CONST_GL(ACCUM_ADJACENT_PAIRS_NV);
    EXPORT_NAPI_CONST_GL(ADJACENT_PAIRS_NV);
    EXPORT_NAPI_CONST_GL(FIRST_TO_REST_NV);
    EXPORT_NAPI_CONST_GL(PATH_GEN_MODE_NV);
    EXPORT_NAPI_CONST_GL(PATH_GEN_COEFF_NV);
    EXPORT_NAPI_CONST_GL(PATH_GEN_COMPONENTS_NV);
    EXPORT_NAPI_CONST_GL(PATH_STENCIL_FUNC_NV);
    EXPORT_NAPI_CONST_GL(PATH_STENCIL_REF_NV);
    EXPORT_NAPI_CONST_GL(PATH_STENCIL_VALUE_MASK_NV);
    EXPORT_NAPI_CONST_GL(PATH_STENCIL_DEPTH_OFFSET_FACTOR_NV);
    EXPORT_NAPI_CONST_GL(PATH_STENCIL_DEPTH_OFFSET_UNITS_NV);
    EXPORT_NAPI_CONST_GL(PATH_COVER_DEPTH_FUNC_NV);
    EXPORT_NAPI_CONST_GL(PATH_DASH_OFFSET_RESET_NV);
    EXPORT_NAPI_CONST_GL(MOVE_TO_RESETS_NV);
    EXPORT_NAPI_CONST_GL(MOVE_TO_CONTINUES_NV);
    EXPORT_NAPI_CONST_GL(CLOSE_PATH_NV);
    EXPORT_NAPI_CONST_GL(MOVE_TO_NV);
    EXPORT_NAPI_CONST_GL(RELATIVE_MOVE_TO_NV);
    EXPORT_NAPI_CONST_GL(LINE_TO_NV);
    EXPORT_NAPI_CONST_GL(RELATIVE_LINE_TO_NV);
    EXPORT_NAPI_CONST_GL(HORIZONTAL_LINE_TO_NV);
    EXPORT_NAPI_CONST_GL(RELATIVE_HORIZONTAL_LINE_TO_NV);
    EXPORT_NAPI_CONST_GL(VERTICAL_LINE_TO_NV);
    EXPORT_NAPI_CONST_GL(RELATIVE_VERTICAL_LINE_TO_NV);
    EXPORT_NAPI_CONST_GL(QUADRATIC_CURVE_TO_NV);
    EXPORT_NAPI_CONST_GL(RELATIVE_QUADRATIC_CURVE_TO_NV);
    EXPORT_NAPI_CONST_GL(CUBIC_CURVE_TO_NV);
    EXPORT_NAPI_CONST_GL(RELATIVE_CUBIC_CURVE_TO_NV);
    EXPORT_NAPI_CONST_GL(SMOOTH_QUADRATIC_CURVE_TO_NV);
    EXPORT_NAPI_CONST_GL(RELATIVE_SMOOTH_QUADRATIC_CURVE_TO_NV);
    EXPORT_NAPI_CONST_GL(SMOOTH_CUBIC_CURVE_TO_NV);
    EXPORT_NAPI_CONST_GL(RELATIVE_SMOOTH_CUBIC_CURVE_TO_NV);
    EXPORT_NAPI_CONST_GL(SMALL_CCW_ARC_TO_NV);
    EXPORT_NAPI_CONST_GL(RELATIVE_SMALL_CCW_ARC_TO_NV);
    EXPORT_NAPI_CONST_GL(SMALL_CW_ARC_TO_NV);
    EXPORT_NAPI_CONST_GL(RELATIVE_SMALL_CW_ARC_TO_NV);
    EXPORT_NAPI_CONST_GL(LARGE_CCW_ARC_TO_NV);
    EXPORT_NAPI_CONST_GL(RELATIVE_LARGE_CCW_ARC_TO_NV);
    EXPORT_NAPI_CONST_GL(LARGE_CW_ARC_TO_NV);
    EXPORT_NAPI_CONST_GL(RELATIVE_LARGE_CW_ARC_TO_NV);
    EXPORT_NAPI_CONST_GL(RESTART_PATH_NV);
    EXPORT_NAPI_CONST_GL(DUP_FIRST_CUBIC_CURVE_TO_NV);
    EXPORT_NAPI_CONST_GL(DUP_LAST_CUBIC_CURVE_TO_NV);
    EXPORT_NAPI_CONST_GL(RECT_NV);
    EXPORT_NAPI_CONST_GL(CIRCULAR_CCW_ARC_TO_NV);
    EXPORT_NAPI_CONST_GL(CIRCULAR_CW_ARC_TO_NV);
    EXPORT_NAPI_CONST_GL(CIRCULAR_TANGENT_ARC_TO_NV);
    EXPORT_NAPI_CONST_GL(ARC_TO_NV);
    EXPORT_NAPI_CONST_GL(RELATIVE_ARC_TO_NV);
    EXPORT_NAPI_CONST_GL(BOLD_BIT_NV);
    EXPORT_NAPI_CONST_GL(ITALIC_BIT_NV);
    EXPORT_NAPI_CONST_GL(GLYPH_WIDTH_BIT_NV);
    EXPORT_NAPI_CONST_GL(GLYPH_HEIGHT_BIT_NV);
    EXPORT_NAPI_CONST_GL(GLYPH_HORIZONTAL_BEARING_X_BIT_NV);
    EXPORT_NAPI_CONST_GL(GLYPH_HORIZONTAL_BEARING_Y_BIT_NV);
    EXPORT_NAPI_CONST_GL(GLYPH_HORIZONTAL_BEARING_ADVANCE_BIT_NV);
    EXPORT_NAPI_CONST_GL(GLYPH_VERTICAL_BEARING_X_BIT_NV);
    EXPORT_NAPI_CONST_GL(GLYPH_VERTICAL_BEARING_Y_BIT_NV);
    EXPORT_NAPI_CONST_GL(GLYPH_VERTICAL_BEARING_ADVANCE_BIT_NV);
    EXPORT_NAPI_CONST_GL(GLYPH_HAS_KERNING_BIT_NV);
    EXPORT_NAPI_CONST_GL(FONT_X_MIN_BOUNDS_BIT_NV);
    EXPORT_NAPI_CONST_GL(FONT_Y_MIN_BOUNDS_BIT_NV);
    EXPORT_NAPI_CONST_GL(FONT_X_MAX_BOUNDS_BIT_NV);
    EXPORT_NAPI_CONST_GL(FONT_Y_MAX_BOUNDS_BIT_NV);
    EXPORT_NAPI_CONST_GL(FONT_UNITS_PER_EM_BIT_NV);
    EXPORT_NAPI_CONST_GL(FONT_ASCENDER_BIT_NV);
    EXPORT_NAPI_CONST_GL(FONT_DESCENDER_BIT_NV);
    EXPORT_NAPI_CONST_GL(FONT_HEIGHT_BIT_NV);
    EXPORT_NAPI_CONST_GL(FONT_MAX_ADVANCE_WIDTH_BIT_NV);
    EXPORT_NAPI_CONST_GL(FONT_MAX_ADVANCE_HEIGHT_BIT_NV);
    EXPORT_NAPI_CONST_GL(FONT_UNDERLINE_POSITION_BIT_NV);
    EXPORT_NAPI_CONST_GL(FONT_UNDERLINE_THICKNESS_BIT_NV);
    EXPORT_NAPI_CONST_GL(FONT_HAS_KERNING_BIT_NV);
    EXPORT_NAPI_CONST_GL(ROUNDED_RECT_NV);
    EXPORT_NAPI_CONST_GL(RELATIVE_ROUNDED_RECT_NV);
    EXPORT_NAPI_CONST_GL(ROUNDED_RECT2_NV);
    EXPORT_NAPI_CONST_GL(RELATIVE_ROUNDED_RECT2_NV);
    EXPORT_NAPI_CONST_GL(ROUNDED_RECT4_NV);
    EXPORT_NAPI_CONST_GL(RELATIVE_ROUNDED_RECT4_NV);
    EXPORT_NAPI_CONST_GL(ROUNDED_RECT8_NV);
    EXPORT_NAPI_CONST_GL(RELATIVE_ROUNDED_RECT8_NV);
    EXPORT_NAPI_CONST_GL(RELATIVE_RECT_NV);
    EXPORT_NAPI_CONST_GL(FONT_GLYPHS_AVAILABLE_NV);
    EXPORT_NAPI_CONST_GL(FONT_TARGET_UNAVAILABLE_NV);
    EXPORT_NAPI_CONST_GL(FONT_UNAVAILABLE_NV);
    EXPORT_NAPI_CONST_GL(FONT_UNINTELLIGIBLE_NV);
    EXPORT_NAPI_CONST_GL(CONIC_CURVE_TO_NV);
    EXPORT_NAPI_CONST_GL(RELATIVE_CONIC_CURVE_TO_NV);
    EXPORT_NAPI_CONST_GL(FONT_NUM_GLYPH_INDICES_BIT_NV);
    EXPORT_NAPI_CONST_GL(STANDARD_FONT_FORMAT_NV);
    EXPORT_NAPI_CONST_GL(2_BYTES_NV);
    EXPORT_NAPI_CONST_GL(3_BYTES_NV);
    EXPORT_NAPI_CONST_GL(4_BYTES_NV);
    EXPORT_NAPI_CONST_GL(EYE_LINEAR_NV);
    EXPORT_NAPI_CONST_GL(OBJECT_LINEAR_NV);
    EXPORT_NAPI_CONST_GL(CONSTANT_NV);
    EXPORT_NAPI_CONST_GL(PATH_FOG_GEN_MODE_NV);
    EXPORT_NAPI_CONST_GL(PRIMARY_COLOR);
    EXPORT_NAPI_CONST_GL(PRIMARY_COLOR_NV);
    EXPORT_NAPI_CONST_GL(SECONDARY_COLOR_NV);
    EXPORT_NAPI_CONST_GL(PATH_GEN_COLOR_FORMAT_NV);
    EXPORT_NAPI_CONST_GL(PATH_PROJECTION_NV);
    EXPORT_NAPI_CONST_GL(PATH_MODELVIEW_NV);
    EXPORT_NAPI_CONST_GL(PATH_MODELVIEW_STACK_DEPTH_NV);
    EXPORT_NAPI_CONST_GL(PATH_MODELVIEW_MATRIX_NV);
    EXPORT_NAPI_CONST_GL(PATH_MAX_MODELVIEW_STACK_DEPTH_NV);
    EXPORT_NAPI_CONST_GL(PATH_TRANSPOSE_MODELVIEW_MATRIX_NV);
    EXPORT_NAPI_CONST_GL(PATH_PROJECTION_STACK_DEPTH_NV);
    EXPORT_NAPI_CONST_GL(PATH_PROJECTION_MATRIX_NV);
    EXPORT_NAPI_CONST_GL(PATH_MAX_PROJECTION_STACK_DEPTH_NV);
    EXPORT_NAPI_CONST_GL(PATH_TRANSPOSE_PROJECTION_MATRIX_NV);
    EXPORT_NAPI_CONST_GL(FRAGMENT_INPUT_NV);
    EXPORT_NAPI_CONST_GL(SHARED_EDGE_NV);
    EXPORT_NAPI_CONST_GL(POLYGON_MODE_NV);
    EXPORT_NAPI_CONST_GL(POLYGON_OFFSET_POINT_NV);
    EXPORT_NAPI_CONST_GL(POLYGON_OFFSET_LINE_NV);
    EXPORT_NAPI_CONST_GL(POINT_NV);
    EXPORT_NAPI_CONST_GL(LINE_NV);
    EXPORT_NAPI_CONST_GL(FILL_NV);
    EXPORT_NAPI_CONST_GL(READ_BUFFER_NV);
    EXPORT_NAPI_CONST_GL(SLUMINANCE_NV);
    EXPORT_NAPI_CONST_GL(SLUMINANCE_ALPHA_NV);
    EXPORT_NAPI_CONST_GL(SRGB8_NV);
    EXPORT_NAPI_CONST_GL(SLUMINANCE8_NV);
    EXPORT_NAPI_CONST_GL(SLUMINANCE8_ALPHA8_NV);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB_S3TC_DXT1_NV);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB_ALPHA_S3TC_DXT1_NV);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB_ALPHA_S3TC_DXT3_NV);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB_ALPHA_S3TC_DXT5_NV);
    EXPORT_NAPI_CONST_GL(ETC1_SRGB8_NV);
    EXPORT_NAPI_CONST_GL(SAMPLE_LOCATION_SUBPIXEL_BITS_NV);
    EXPORT_NAPI_CONST_GL(SAMPLE_LOCATION_PIXEL_GRID_WIDTH_NV);
    EXPORT_NAPI_CONST_GL(SAMPLE_LOCATION_PIXEL_GRID_HEIGHT_NV);
    EXPORT_NAPI_CONST_GL(PROGRAMMABLE_SAMPLE_LOCATION_TABLE_SIZE_NV);
    EXPORT_NAPI_CONST_GL(SAMPLE_LOCATION_NV);
    EXPORT_NAPI_CONST_GL(PROGRAMMABLE_SAMPLE_LOCATION_NV);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_PROGRAMMABLE_SAMPLE_LOCATIONS_NV);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_SAMPLE_LOCATION_PIXEL_GRID_NV);
    EXPORT_NAPI_CONST_GL(SAMPLER_2D_ARRAY_SHADOW_NV);
    EXPORT_NAPI_CONST_GL(SAMPLER_CUBE_SHADOW_NV);
    EXPORT_NAPI_CONST_GL(TEXTURE_BORDER_COLOR_NV);
    EXPORT_NAPI_CONST_GL(CLAMP_TO_BORDER_NV);
    EXPORT_NAPI_CONST_GL(MAX_VIEWPORTS_NV);
    EXPORT_NAPI_CONST_GL(VIEWPORT_SUBPIXEL_BITS_NV);
    EXPORT_NAPI_CONST_GL(VIEWPORT_BOUNDS_RANGE_NV);
    EXPORT_NAPI_CONST_GL(VIEWPORT_INDEX_PROVOKING_VERTEX_NV);
    EXPORT_NAPI_CONST_GL(VIEWPORT_SWIZZLE_POSITIVE_X_NV);
    EXPORT_NAPI_CONST_GL(VIEWPORT_SWIZZLE_NEGATIVE_X_NV);
    EXPORT_NAPI_CONST_GL(VIEWPORT_SWIZZLE_POSITIVE_Y_NV);
    EXPORT_NAPI_CONST_GL(VIEWPORT_SWIZZLE_NEGATIVE_Y_NV);
    EXPORT_NAPI_CONST_GL(VIEWPORT_SWIZZLE_POSITIVE_Z_NV);
    EXPORT_NAPI_CONST_GL(VIEWPORT_SWIZZLE_NEGATIVE_Z_NV);
    EXPORT_NAPI_CONST_GL(VIEWPORT_SWIZZLE_POSITIVE_W_NV);
    EXPORT_NAPI_CONST_GL(VIEWPORT_SWIZZLE_NEGATIVE_W_NV);
    EXPORT_NAPI_CONST_GL(VIEWPORT_SWIZZLE_X_NV);
    EXPORT_NAPI_CONST_GL(VIEWPORT_SWIZZLE_Y_NV);
    EXPORT_NAPI_CONST_GL(VIEWPORT_SWIZZLE_Z_NV);
    EXPORT_NAPI_CONST_GL(VIEWPORT_SWIZZLE_W_NV);
    EXPORT_NAPI_CONST_GL(SAMPLER_EXTERNAL_OES);
    EXPORT_NAPI_CONST_GL(ETC1_RGB8_OES);
    EXPORT_NAPI_CONST_GL(PALETTE4_RGB8_OES);
    EXPORT_NAPI_CONST_GL(PALETTE4_RGBA8_OES);
    EXPORT_NAPI_CONST_GL(PALETTE4_R5_G6_B5_OES);
    EXPORT_NAPI_CONST_GL(PALETTE4_RGBA4_OES);
    EXPORT_NAPI_CONST_GL(PALETTE4_RGB5_A1_OES);
    EXPORT_NAPI_CONST_GL(PALETTE8_RGB8_OES);
    EXPORT_NAPI_CONST_GL(PALETTE8_RGBA8_OES);
    EXPORT_NAPI_CONST_GL(PALETTE8_R5_G6_B5_OES);
    EXPORT_NAPI_CONST_GL(PALETTE8_RGBA4_OES);
    EXPORT_NAPI_CONST_GL(PALETTE8_RGB5_A1_OES);
    EXPORT_NAPI_CONST_GL(DEPTH_COMPONENT24_OES);
    EXPORT_NAPI_CONST_GL(GEOMETRY_SHADER_OES);
    EXPORT_NAPI_CONST_GL(GEOMETRY_SHADER_BIT_OES);
    EXPORT_NAPI_CONST_GL(GEOMETRY_LINKED_VERTICES_OUT_OES);
    EXPORT_NAPI_CONST_GL(GEOMETRY_LINKED_INPUT_TYPE_OES);
    EXPORT_NAPI_CONST_GL(GEOMETRY_LINKED_OUTPUT_TYPE_OES);
    EXPORT_NAPI_CONST_GL(GEOMETRY_SHADER_INVOCATIONS_OES);
    EXPORT_NAPI_CONST_GL(LAYER_PROVOKING_VERTEX_OES);
    EXPORT_NAPI_CONST_GL(LINES_ADJACENCY_OES);
    EXPORT_NAPI_CONST_GL(LINE_STRIP_ADJACENCY_OES);
    EXPORT_NAPI_CONST_GL(TRIANGLES_ADJACENCY_OES);
    EXPORT_NAPI_CONST_GL(TRIANGLE_STRIP_ADJACENCY_OES);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_UNIFORM_COMPONENTS_OES);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_UNIFORM_BLOCKS_OES);
    EXPORT_NAPI_CONST_GL(MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS_OES);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_INPUT_COMPONENTS_OES);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_OUTPUT_COMPONENTS_OES);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_OUTPUT_VERTICES_OES);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_OES);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_SHADER_INVOCATIONS_OES);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_OES);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS_OES);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_ATOMIC_COUNTERS_OES);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_IMAGE_UNIFORMS_OES);
    EXPORT_NAPI_CONST_GL(MAX_GEOMETRY_SHADER_STORAGE_BLOCKS_OES);
    EXPORT_NAPI_CONST_GL(FIRST_VERTEX_CONVENTION_OES);
    EXPORT_NAPI_CONST_GL(LAST_VERTEX_CONVENTION_OES);
    EXPORT_NAPI_CONST_GL(UNDEFINED_VERTEX_OES);
    EXPORT_NAPI_CONST_GL(PRIMITIVES_GENERATED_OES);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_DEFAULT_LAYERS_OES);
    EXPORT_NAPI_CONST_GL(MAX_FRAMEBUFFER_LAYERS_OES);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_OES);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_LAYERED_OES);
    EXPORT_NAPI_CONST_GL(REFERENCED_BY_GEOMETRY_SHADER_OES);
    EXPORT_NAPI_CONST_GL(PROGRAM_BINARY_LENGTH_OES);
    EXPORT_NAPI_CONST_GL(NUM_PROGRAM_BINARY_FORMATS_OES);
    EXPORT_NAPI_CONST_GL(PROGRAM_BINARY_FORMATS_OES);
    EXPORT_NAPI_CONST_GL(WRITE_ONLY_OES);
    EXPORT_NAPI_CONST_GL(BUFFER_ACCESS_OES);
    EXPORT_NAPI_CONST_GL(BUFFER_MAPPED_OES);
    EXPORT_NAPI_CONST_GL(BUFFER_MAP_POINTER_OES);
    EXPORT_NAPI_CONST_GL(PRIMITIVE_BOUNDING_BOX_OES);
    EXPORT_NAPI_CONST_GL(ALPHA8_OES);
    EXPORT_NAPI_CONST_GL(DEPTH_COMPONENT16_OES);
    EXPORT_NAPI_CONST_GL(LUMINANCE4_ALPHA4_OES);
    EXPORT_NAPI_CONST_GL(LUMINANCE8_ALPHA8_OES);
    EXPORT_NAPI_CONST_GL(LUMINANCE8_OES);
    EXPORT_NAPI_CONST_GL(RGBA4_OES);
    EXPORT_NAPI_CONST_GL(RGB5_A1_OES);
    EXPORT_NAPI_CONST_GL(RGB565_OES);
    EXPORT_NAPI_CONST_GL(RGB8_OES);
    EXPORT_NAPI_CONST_GL(RGBA8_OES);
    EXPORT_NAPI_CONST_GL(SAMPLE_SHADING_OES);
    EXPORT_NAPI_CONST_GL(MIN_SAMPLE_SHADING_VALUE_OES);
    EXPORT_NAPI_CONST_GL(MIN_FRAGMENT_INTERPOLATION_OFFSET_OES);
    EXPORT_NAPI_CONST_GL(MAX_FRAGMENT_INTERPOLATION_OFFSET_OES);
    EXPORT_NAPI_CONST_GL(FRAGMENT_INTERPOLATION_OFFSET_BITS_OES);
    EXPORT_NAPI_CONST_GL(FRAGMENT_SHADER_DERIVATIVE_HINT_OES);
    EXPORT_NAPI_CONST_GL(STENCIL_INDEX1_OES);
    EXPORT_NAPI_CONST_GL(STENCIL_INDEX4_OES);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_UNDEFINED_OES);
    EXPORT_NAPI_CONST_GL(PATCHES_OES);
    EXPORT_NAPI_CONST_GL(PATCH_VERTICES_OES);
    EXPORT_NAPI_CONST_GL(TESS_CONTROL_OUTPUT_VERTICES_OES);
    EXPORT_NAPI_CONST_GL(TESS_GEN_MODE_OES);
    EXPORT_NAPI_CONST_GL(TESS_GEN_SPACING_OES);
    EXPORT_NAPI_CONST_GL(TESS_GEN_VERTEX_ORDER_OES);
    EXPORT_NAPI_CONST_GL(TESS_GEN_POINT_MODE_OES);
    EXPORT_NAPI_CONST_GL(ISOLINES_OES);
    EXPORT_NAPI_CONST_GL(QUADS_OES);
    EXPORT_NAPI_CONST_GL(FRACTIONAL_ODD_OES);
    EXPORT_NAPI_CONST_GL(FRACTIONAL_EVEN_OES);
    EXPORT_NAPI_CONST_GL(MAX_PATCH_VERTICES_OES);
    EXPORT_NAPI_CONST_GL(MAX_TESS_GEN_LEVEL_OES);
    EXPORT_NAPI_CONST_GL(MAX_TESS_CONTROL_UNIFORM_COMPONENTS_OES);
    EXPORT_NAPI_CONST_GL(MAX_TESS_EVALUATION_UNIFORM_COMPONENTS_OES);
    EXPORT_NAPI_CONST_GL(MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_OES);
    EXPORT_NAPI_CONST_GL(MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_OES);
    EXPORT_NAPI_CONST_GL(MAX_TESS_CONTROL_OUTPUT_COMPONENTS_OES);
    EXPORT_NAPI_CONST_GL(MAX_TESS_PATCH_COMPONENTS_OES);
    EXPORT_NAPI_CONST_GL(MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS_OES);
    EXPORT_NAPI_CONST_GL(MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_OES);
    EXPORT_NAPI_CONST_GL(MAX_TESS_CONTROL_UNIFORM_BLOCKS_OES);
    EXPORT_NAPI_CONST_GL(MAX_TESS_EVALUATION_UNIFORM_BLOCKS_OES);
    EXPORT_NAPI_CONST_GL(MAX_TESS_CONTROL_INPUT_COMPONENTS_OES);
    EXPORT_NAPI_CONST_GL(MAX_TESS_EVALUATION_INPUT_COMPONENTS_OES);
    EXPORT_NAPI_CONST_GL(MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS_OES);
    EXPORT_NAPI_CONST_GL(MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS_OES);
    EXPORT_NAPI_CONST_GL(MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS_OES);
    EXPORT_NAPI_CONST_GL(MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS_OES);
    EXPORT_NAPI_CONST_GL(MAX_TESS_CONTROL_ATOMIC_COUNTERS_OES);
    EXPORT_NAPI_CONST_GL(MAX_TESS_EVALUATION_ATOMIC_COUNTERS_OES);
    EXPORT_NAPI_CONST_GL(MAX_TESS_CONTROL_IMAGE_UNIFORMS_OES);
    EXPORT_NAPI_CONST_GL(MAX_TESS_EVALUATION_IMAGE_UNIFORMS_OES);
    EXPORT_NAPI_CONST_GL(MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS_OES);
    EXPORT_NAPI_CONST_GL(MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS_OES);
    EXPORT_NAPI_CONST_GL(PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED_OES);
    EXPORT_NAPI_CONST_GL(IS_PER_PATCH_OES);
    EXPORT_NAPI_CONST_GL(REFERENCED_BY_TESS_CONTROL_SHADER_OES);
    EXPORT_NAPI_CONST_GL(REFERENCED_BY_TESS_EVALUATION_SHADER_OES);
    EXPORT_NAPI_CONST_GL(TESS_CONTROL_SHADER_OES);
    EXPORT_NAPI_CONST_GL(TESS_EVALUATION_SHADER_OES);
    EXPORT_NAPI_CONST_GL(TESS_CONTROL_SHADER_BIT_OES);
    EXPORT_NAPI_CONST_GL(TESS_EVALUATION_SHADER_BIT_OES);
    EXPORT_NAPI_CONST_GL(TEXTURE_WRAP_R_OES);
    EXPORT_NAPI_CONST_GL(TEXTURE_3D_OES);
    EXPORT_NAPI_CONST_GL(TEXTURE_BINDING_3D_OES);
    EXPORT_NAPI_CONST_GL(MAX_3D_TEXTURE_SIZE_OES);
    EXPORT_NAPI_CONST_GL(SAMPLER_3D_OES);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_OES);
    EXPORT_NAPI_CONST_GL(TEXTURE_BORDER_COLOR_OES);
    EXPORT_NAPI_CONST_GL(CLAMP_TO_BORDER_OES);
    EXPORT_NAPI_CONST_GL(TEXTURE_BUFFER_OES);
    EXPORT_NAPI_CONST_GL(TEXTURE_BUFFER_BINDING_OES);
    EXPORT_NAPI_CONST_GL(MAX_TEXTURE_BUFFER_SIZE_OES);
    EXPORT_NAPI_CONST_GL(TEXTURE_BINDING_BUFFER_OES);
    EXPORT_NAPI_CONST_GL(TEXTURE_BUFFER_DATA_STORE_BINDING_OES);
    EXPORT_NAPI_CONST_GL(TEXTURE_BUFFER_OFFSET_ALIGNMENT_OES);
    EXPORT_NAPI_CONST_GL(SAMPLER_BUFFER_OES);
    EXPORT_NAPI_CONST_GL(INT_SAMPLER_BUFFER_OES);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_SAMPLER_BUFFER_OES);
    EXPORT_NAPI_CONST_GL(IMAGE_BUFFER_OES);
    EXPORT_NAPI_CONST_GL(INT_IMAGE_BUFFER_OES);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_IMAGE_BUFFER_OES);
    EXPORT_NAPI_CONST_GL(TEXTURE_BUFFER_OFFSET_OES);
    EXPORT_NAPI_CONST_GL(TEXTURE_BUFFER_SIZE_OES);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_3x3x3_OES);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_4x3x3_OES);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_4x4x3_OES);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_4x4x4_OES);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_5x4x4_OES);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_5x5x4_OES);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_5x5x5_OES);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_6x5x5_OES);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_6x6x5_OES);
    EXPORT_NAPI_CONST_GL(COMPRESSED_RGBA_ASTC_6x6x6_OES);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_3x3x3_OES);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_4x3x3_OES);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_4x4x3_OES);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_4x4x4_OES);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_5x4x4_OES);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_5x5x4_OES);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_5x5x5_OES);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_6x5x5_OES);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_6x6x5_OES);
    EXPORT_NAPI_CONST_GL(COMPRESSED_SRGB8_ALPHA8_ASTC_6x6x6_OES);
    EXPORT_NAPI_CONST_GL(TEXTURE_BINDING_CUBE_MAP_ARRAY_OES);
    EXPORT_NAPI_CONST_GL(SAMPLER_CUBE_MAP_ARRAY_OES);
    EXPORT_NAPI_CONST_GL(SAMPLER_CUBE_MAP_ARRAY_SHADOW_OES);
    EXPORT_NAPI_CONST_GL(INT_SAMPLER_CUBE_MAP_ARRAY_OES);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_OES);
    EXPORT_NAPI_CONST_GL(IMAGE_CUBE_MAP_ARRAY_OES);
    EXPORT_NAPI_CONST_GL(INT_IMAGE_CUBE_MAP_ARRAY_OES);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_OES);
    EXPORT_NAPI_CONST_GL(HALF_FLOAT_OES);
    EXPORT_NAPI_CONST_GL(STENCIL_INDEX_OES);
    EXPORT_NAPI_CONST_GL(STENCIL_INDEX8_OES);
    EXPORT_NAPI_CONST_GL(TEXTURE_2D_MULTISAMPLE_ARRAY_OES);
    EXPORT_NAPI_CONST_GL(TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY_OES);
    EXPORT_NAPI_CONST_GL(SAMPLER_2D_MULTISAMPLE_ARRAY_OES);
    EXPORT_NAPI_CONST_GL(INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES);
    EXPORT_NAPI_CONST_GL(TEXTURE_VIEW_MIN_LEVEL_OES);
    EXPORT_NAPI_CONST_GL(TEXTURE_VIEW_NUM_LEVELS_OES);
    EXPORT_NAPI_CONST_GL(TEXTURE_VIEW_MIN_LAYER_OES);
    EXPORT_NAPI_CONST_GL(TEXTURE_VIEW_NUM_LAYERS_OES);
    EXPORT_NAPI_CONST_GL(VERTEX_ARRAY_BINDING_OES);
    EXPORT_NAPI_CONST_GL(UNSIGNED_INT_10_10_10_2_OES);
    EXPORT_NAPI_CONST_GL(INT_10_10_10_2_OES);
    EXPORT_NAPI_CONST_GL(MAX_VIEWPORTS_OES);
    EXPORT_NAPI_CONST_GL(VIEWPORT_SUBPIXEL_BITS_OES);
    EXPORT_NAPI_CONST_GL(VIEWPORT_BOUNDS_RANGE_OES);
    EXPORT_NAPI_CONST_GL(VIEWPORT_INDEX_PROVOKING_VERTEX_OES);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_TEXTURE_NUM_VIEWS_OVR);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_ATTACHMENT_TEXTURE_BASE_VIEW_INDEX_OVR);
    EXPORT_NAPI_CONST_GL(MAX_VIEWS_OVR);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_INCOMPLETE_VIEW_TARGETS_OVR);
    EXPORT_NAPI_CONST_GL(ALPHA_TEST_QCOM);
    EXPORT_NAPI_CONST_GL(ALPHA_TEST_FUNC_QCOM);
    EXPORT_NAPI_CONST_GL(ALPHA_TEST_REF_QCOM);
    EXPORT_NAPI_CONST_GL(BINNING_CONTROL_HINT_QCOM);
    EXPORT_NAPI_CONST_GL(CPU_OPTIMIZED_QCOM);
    EXPORT_NAPI_CONST_GL(GPU_OPTIMIZED_QCOM);
    EXPORT_NAPI_CONST_GL(RENDER_DIRECT_TO_FRAMEBUFFER_QCOM);
    EXPORT_NAPI_CONST_GL(TEXTURE_WIDTH_QCOM);
    EXPORT_NAPI_CONST_GL(TEXTURE_HEIGHT_QCOM);
    EXPORT_NAPI_CONST_GL(TEXTURE_DEPTH_QCOM);
    EXPORT_NAPI_CONST_GL(TEXTURE_INTERNAL_FORMAT_QCOM);
    EXPORT_NAPI_CONST_GL(TEXTURE_FORMAT_QCOM);
    EXPORT_NAPI_CONST_GL(TEXTURE_TYPE_QCOM);
    EXPORT_NAPI_CONST_GL(TEXTURE_IMAGE_VALID_QCOM);
    EXPORT_NAPI_CONST_GL(TEXTURE_NUM_LEVELS_QCOM);
    EXPORT_NAPI_CONST_GL(TEXTURE_TARGET_QCOM);
    EXPORT_NAPI_CONST_GL(TEXTURE_OBJECT_VALID_QCOM);
    EXPORT_NAPI_CONST_GL(STATE_RESTORE);
    EXPORT_NAPI_CONST_GL(FOVEATION_ENABLE_BIT_QCOM);
    EXPORT_NAPI_CONST_GL(FOVEATION_SCALED_BIN_METHOD_BIT_QCOM);
    EXPORT_NAPI_CONST_GL(PERFMON_GLOBAL_MODE_QCOM);
    EXPORT_NAPI_CONST_GL(FRAMEBUFFER_FETCH_NONCOHERENT_QCOM);
    EXPORT_NAPI_CONST_GL(COLOR_BUFFER_BIT0_QCOM);
    EXPORT_NAPI_CONST_GL(COLOR_BUFFER_BIT1_QCOM);
    EXPORT_NAPI_CONST_GL(COLOR_BUFFER_BIT2_QCOM);
    EXPORT_NAPI_CONST_GL(COLOR_BUFFER_BIT3_QCOM);
    EXPORT_NAPI_CONST_GL(COLOR_BUFFER_BIT4_QCOM);
    EXPORT_NAPI_CONST_GL(COLOR_BUFFER_BIT5_QCOM);
    EXPORT_NAPI_CONST_GL(COLOR_BUFFER_BIT6_QCOM);
    EXPORT_NAPI_CONST_GL(COLOR_BUFFER_BIT7_QCOM);
    EXPORT_NAPI_CONST_GL(DEPTH_BUFFER_BIT0_QCOM);
    EXPORT_NAPI_CONST_GL(DEPTH_BUFFER_BIT1_QCOM);
    EXPORT_NAPI_CONST_GL(DEPTH_BUFFER_BIT2_QCOM);
    EXPORT_NAPI_CONST_GL(DEPTH_BUFFER_BIT3_QCOM);
    EXPORT_NAPI_CONST_GL(DEPTH_BUFFER_BIT4_QCOM);
    EXPORT_NAPI_CONST_GL(DEPTH_BUFFER_BIT5_QCOM);
    EXPORT_NAPI_CONST_GL(DEPTH_BUFFER_BIT6_QCOM);
    EXPORT_NAPI_CONST_GL(DEPTH_BUFFER_BIT7_QCOM);
    EXPORT_NAPI_CONST_GL(STENCIL_BUFFER_BIT0_QCOM);
    EXPORT_NAPI_CONST_GL(STENCIL_BUFFER_BIT1_QCOM);
    EXPORT_NAPI_CONST_GL(STENCIL_BUFFER_BIT2_QCOM);
    EXPORT_NAPI_CONST_GL(STENCIL_BUFFER_BIT3_QCOM);
    EXPORT_NAPI_CONST_GL(STENCIL_BUFFER_BIT4_QCOM);
    EXPORT_NAPI_CONST_GL(STENCIL_BUFFER_BIT5_QCOM);
    EXPORT_NAPI_CONST_GL(STENCIL_BUFFER_BIT6_QCOM);
    EXPORT_NAPI_CONST_GL(STENCIL_BUFFER_BIT7_QCOM);
    EXPORT_NAPI_CONST_GL(MULTISAMPLE_BUFFER_BIT0_QCOM);
    EXPORT_NAPI_CONST_GL(MULTISAMPLE_BUFFER_BIT1_QCOM);
    EXPORT_NAPI_CONST_GL(MULTISAMPLE_BUFFER_BIT2_QCOM);
    EXPORT_NAPI_CONST_GL(MULTISAMPLE_BUFFER_BIT3_QCOM);
    EXPORT_NAPI_CONST_GL(MULTISAMPLE_BUFFER_BIT4_QCOM);
    EXPORT_NAPI_CONST_GL(MULTISAMPLE_BUFFER_BIT5_QCOM);
    EXPORT_NAPI_CONST_GL(MULTISAMPLE_BUFFER_BIT6_QCOM);
    EXPORT_NAPI_CONST_GL(MULTISAMPLE_BUFFER_BIT7_QCOM);
    EXPORT_NAPI_CONST_GL(WRITEONLY_RENDERING_QCOM);
    EXPORT_NAPI_CONST_GL(SHADER_BINARY_VIV);
#endif
}

NAPI_MODULE(gles, _ModuleInit);
