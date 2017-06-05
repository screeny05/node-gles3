#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <node_api.h>

#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <common.h>

#include "scn_napi.h"


napi_env _env;

napi_ref _errorCallbackReference;
napi_ref _cursorPosCallbackReference;
napi_ref _keyCallbackReference;
napi_ref _framebufferSizeCallbackReference;
napi_ref _mouseButtonCallbackReference;
napi_ref _windowCloseCallbackReference;
napi_ref _windowSizeCallbackReference;

DECLARE_NAPI_METHOD(MakeContextCurrent){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_INT64(_window, 0);
    GLFWwindow* window = (GLFWwindow*)_window;

    glfwMakeContextCurrent(window);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(GetCurrentContext){
    RETURN_NAPI_NUMBER((uint64_t)glfwGetCurrentContext());
}

DECLARE_NAPI_METHOD(SwapInterval){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_INT64(interval, 0);

    glfwSwapInterval(interval);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(ExtensionSupported){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_STRING(extension, 0);

    RETURN_NAPI_BOOL(glfwExtensionSupported(extension));
}

DECLARE_NAPI_METHOD(GetProcAddress){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_STRING(procname, 0);

    RETURN_NAPI_NUMBER((uint64_t)glfwGetProcAddress(procname));
}




DECLARE_NAPI_METHOD(Init){
    RETURN_NAPI_BOOL(glfwInit());
}

DECLARE_NAPI_METHOD(Terminate){
    glfwTerminate();
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(GetVersion){
    int major;
    int minor;
    int rev;
    glfwGetVersion(&major, &minor, &rev);

    napi_value val;
    napi_value returnValue;

    NAPI_CALL(env, napi_create_object(env, &returnValue));

    NAPI_CALL(env, napi_create_number(env, major, &val));
    NAPI_CALL(env, napi_set_named_property(env, returnValue, "major", val));

    NAPI_CALL(env, napi_create_number(env, minor, &val));
    NAPI_CALL(env, napi_set_named_property(env, returnValue, "minor", val));

    NAPI_CALL(env, napi_create_number(env, rev, &val));
    NAPI_CALL(env, napi_set_named_property(env, returnValue, "rev", val));

    return returnValue;
}

DECLARE_NAPI_METHOD(GetVersionString){
    RETURN_NAPI_STRING(glfwGetVersionString());
}

void napiGlfwErrorCallback(int error, const char* description){
    napi_value callbackArgs[2];
    NAPI_CALL_RETURN_VOID(_env, napi_create_number(_env, error, &callbackArgs[0]));
    NAPI_CALL_RETURN_VOID(_env, napi_create_string_utf8(_env, description, -1, &callbackArgs[1]));

    CALL_NAPI_FUNCTION_GLFW_CALLBACK(_errorCallbackReference, 2, callbackArgs);
}

DECLARE_NAPI_METHOD(SetErrorCallback){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_FUNCTION(errorCallback, 0);

    NAPI_CALL(env, napi_create_reference(env, errorCallback, 1, &_errorCallbackReference));

    glfwSetErrorCallback(napiGlfwErrorCallback);
    RETURN_NAPI_UNDEFINED();
}



DECLARE_NAPI_METHOD(GetTime){
    double time = glfwGetTime();
    RETURN_NAPI_NUMBER(time);
}

DECLARE_NAPI_METHOD(CreateStandardCursor){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_INT64(shape, 0);

    GLFWcursor* cursor = glfwCreateStandardCursor(shape);
    RETURN_NAPI_NUMBER((uint64_t)cursor);
}

DECLARE_NAPI_METHOD(DestroyCursor){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_INT64(_cursor, 0);
    GLFWcursor* cursor = (GLFWcursor*)_cursor;

    glfwDestroyCursor(cursor);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(GetClipboardString){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_INT64(_window, 0);
    GLFWwindow* window = (GLFWwindow*)_window;

    RETURN_NAPI_STRING(glfwGetClipboardString(window));
}

DECLARE_NAPI_METHOD(GetCursorPos){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_INT64(_window, 0);
    GLFWwindow* window = (GLFWwindow*)_window;

    double xpos;
    double ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    RETURN_NAPI_2NUMBER_OBJECT(xpos, ypos);
}

DECLARE_NAPI_METHOD(GetInputMode){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_INT64(_window, 0);
    GET_NAPI_PARAM_INT64(mode, 1);
    GLFWwindow* window = (GLFWwindow*)_window;

    RETURN_NAPI_NUMBER(glfwGetInputMode(window, mode));
}

DECLARE_NAPI_METHOD(GetJoystickAxes){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_INT64(joy, 0);

    int count;
    const float* values;

    values = glfwGetJoystickAxes(joy, &count);

    RETURN_NAPI_ARRAY_NUMBER(values, count);
}

DECLARE_NAPI_METHOD(GetJoystickButtons){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_INT64(joy, 0);

    int count;
    const unsigned char* values;

    values = glfwGetJoystickButtons(joy, &count);

    RETURN_NAPI_ARRAY_NUMBER(values, count);
}

DECLARE_NAPI_METHOD(GetJoystickName){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_INT64(joy, 0);

    RETURN_NAPI_STRING(glfwGetJoystickName(joy));
}

DECLARE_NAPI_METHOD(GetKey){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_INT64(_window, 0);
    GET_NAPI_PARAM_INT64(key, 1);
    GLFWwindow* window = (GLFWwindow*)_window;

    RETURN_NAPI_NUMBER(glfwGetKey(window, key));
}

DECLARE_NAPI_METHOD(GetKeyName){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_INT64(key, 0);
    GET_NAPI_PARAM_INT64(scancode, 0);

    RETURN_NAPI_STRING(glfwGetKeyName(key, scancode));
}

DECLARE_NAPI_METHOD(GetMouseButton){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_INT64(_window, 0);
    GET_NAPI_PARAM_INT64(button, 1);
    GLFWwindow* window = (GLFWwindow*)_window;

    RETURN_NAPI_NUMBER(glfwGetMouseButton(window, button));
}

DECLARE_NAPI_METHOD(GetTimerFrequency){
    RETURN_NAPI_NUMBER(glfwGetTimerFrequency());
}

DECLARE_NAPI_METHOD(GetTimerValue){
    RETURN_NAPI_NUMBER(glfwGetTimerValue());
}

DECLARE_NAPI_METHOD(JoystickPresent){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_INT64(joy, 0);

    RETURN_NAPI_BOOL(glfwJoystickPresent(joy));
}

DECLARE_NAPI_METHOD(SetClipboardString){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_INT64(_window, 0);
    GET_NAPI_PARAM_STRING(content, 1);
    GLFWwindow* window = (GLFWwindow*)_window;

    glfwSetClipboardString(window, content);

    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(SetCursor){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_INT64(_window, 0);
    GET_NAPI_PARAM_INT64(_cursor, 1);
    GLFWwindow* window = (GLFWwindow*)_window;
    GLFWcursor* cursor = (GLFWcursor*)_cursor;

    glfwSetCursor(window, cursor);

    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(SetCursorPos){
    GET_NAPI_PARAMS_INFO(3);
    GET_NAPI_PARAM_INT64(_window, 0);
    GET_NAPI_PARAM_DOUBLE(xpos, 1);
    GET_NAPI_PARAM_DOUBLE(ypos, 2);
    GLFWwindow* window = (GLFWwindow*)_window;

    glfwSetCursorPos(window, xpos, ypos);

    RETURN_NAPI_UNDEFINED();
}

void napiGlfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos){
    napi_value callbackArgs[3];
    NAPI_CALL_RETURN_VOID(_env, napi_create_number(_env, (uint64_t)window, &callbackArgs[0]));
    NAPI_CALL_RETURN_VOID(_env, napi_create_number(_env, xpos, &callbackArgs[1]));
    NAPI_CALL_RETURN_VOID(_env, napi_create_number(_env, ypos, &callbackArgs[2]));

    CALL_NAPI_FUNCTION_GLFW_CALLBACK(_cursorPosCallbackReference, 3, callbackArgs);
}

DECLARE_NAPI_METHOD(SetCursorPosCallback){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_INT64(_window, 0);
    GET_NAPI_PARAM_FUNCTION(cursorPosCallback, 1);
    GLFWwindow* window = (GLFWwindow*)_window;

    NAPI_CALL(env, napi_create_reference(env, cursorPosCallback, 1, &_cursorPosCallbackReference));

    glfwSetCursorPosCallback(window, napiGlfwCursorPosCallback);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(SetInputMode){
    GET_NAPI_PARAMS_INFO(3);
    GET_NAPI_PARAM_INT64(_window, 0);
    GET_NAPI_PARAM_DOUBLE(mode, 1);
    GET_NAPI_PARAM_DOUBLE(value, 2);
    GLFWwindow* window = (GLFWwindow*)_window;

    glfwSetInputMode(window, mode, value);

    RETURN_NAPI_UNDEFINED();
}

void napiGlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    napi_value callbackArgs[5];
    NAPI_CALL_RETURN_VOID(_env, napi_create_number(_env, (uint64_t)window, &callbackArgs[0]));
    NAPI_CALL_RETURN_VOID(_env, napi_create_number(_env, key, &callbackArgs[1]));
    NAPI_CALL_RETURN_VOID(_env, napi_create_number(_env, scancode, &callbackArgs[2]));
    NAPI_CALL_RETURN_VOID(_env, napi_create_number(_env, action, &callbackArgs[3]));
    NAPI_CALL_RETURN_VOID(_env, napi_create_number(_env, mods, &callbackArgs[4]));

    CALL_NAPI_FUNCTION_GLFW_CALLBACK(_keyCallbackReference, 5, callbackArgs);
}

DECLARE_NAPI_METHOD(SetKeyCallback){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_INT64(_window, 0);
    GET_NAPI_PARAM_FUNCTION(keyCallback, 1);
    GLFWwindow* window = (GLFWwindow*)_window;

    NAPI_CALL(env, napi_create_reference(env, keyCallback, 1, &_keyCallbackReference));

    glfwSetKeyCallback(window, napiGlfwKeyCallback);
    RETURN_NAPI_UNDEFINED();
}

void napiGlfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
    napi_value callbackArgs[4];
    NAPI_CALL_RETURN_VOID(_env, napi_create_number(_env, (uint64_t)window, &callbackArgs[0]));
    NAPI_CALL_RETURN_VOID(_env, napi_create_number(_env, button, &callbackArgs[1]));
    NAPI_CALL_RETURN_VOID(_env, napi_create_number(_env, action, &callbackArgs[2]));
    NAPI_CALL_RETURN_VOID(_env, napi_create_number(_env, mods, &callbackArgs[3]));

    CALL_NAPI_FUNCTION_GLFW_CALLBACK(_mouseButtonCallbackReference, 4, callbackArgs);
}

DECLARE_NAPI_METHOD(SetMouseButtonCallback){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_INT64(_window, 0);
    GET_NAPI_PARAM_FUNCTION(mouseButtonCallback, 1);
    GLFWwindow* window = (GLFWwindow*)_window;

    NAPI_CALL(env, napi_create_reference(env, mouseButtonCallback, 1, &_mouseButtonCallbackReference));

    glfwSetMouseButtonCallback(window, napiGlfwMouseButtonCallback);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(SetTime){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_DOUBLE(time, 0);

    glfwSetTime(time);

    RETURN_NAPI_UNDEFINED();
}





DECLARE_NAPI_METHOD(CreateWindow){
    GET_NAPI_PARAMS_INFO(3);
    GET_NAPI_PARAM_INT32(width, 0);
    GET_NAPI_PARAM_INT32(height, 1);
    GET_NAPI_PARAM_STRING(title, 2);

    GLFWmonitor* monitor = NULL;
    GLFWwindow* share = NULL;

    if(argc >= 4){
        GET_NAPI_PARAM_INT64(_monitor, 3);
        monitor = (GLFWmonitor*)_monitor;
    }

    if(argc >= 5){
        GET_NAPI_PARAM_INT64(_share, 4);
        share = (GLFWwindow*)_share;
    }

    RETURN_NAPI_NUMBER((uint64_t)glfwCreateWindow(width, height, title, monitor, share));
}

DECLARE_NAPI_METHOD(DestroyWindow){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_INT64(_window, 0);
    GLFWwindow* window = (GLFWwindow*)_window;

    glfwDestroyWindow(window);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(WindowShouldClose){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_INT64(_window, 0);
    GLFWwindow* window = (GLFWwindow*)_window;

    RETURN_NAPI_BOOL(glfwWindowShouldClose(window));
}

DECLARE_NAPI_METHOD(SetWindowTitle){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_INT64(_window, 0);
    GET_NAPI_PARAM_STRING(title, 1);
    GLFWwindow* window = (GLFWwindow*)_window;

    glfwSetWindowTitle(window, title);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(GetWindowSize){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_INT64(_window, 0);
    GLFWwindow* window = (GLFWwindow*)_window;

    int width;
    int height;

    glfwGetWindowSize(window, &width, &height);
    RETURN_NAPI_2NUMBER_OBJECT(width, height);
}

DECLARE_NAPI_METHOD(SetWindowSize){
    GET_NAPI_PARAMS_INFO(3);
    GET_NAPI_PARAM_INT64(_window, 0);
    GET_NAPI_PARAM_INT32(width, 1);
    GET_NAPI_PARAM_INT32(height, 2);
    GLFWwindow* window = (GLFWwindow*)_window;

    glfwSetWindowSize(window, width, height);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(GetFramebufferSize){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_INT64(_window, 0);
    GLFWwindow* window = (GLFWwindow*)_window;

    int width;
    int height;

    glfwGetFramebufferSize(window, &width, &height);
    RETURN_NAPI_2NUMBER_OBJECT(width, height);
}

void napiGlfwWindowSizeCallback(GLFWwindow* window, int width, int height){
    napi_value callbackArgs[3];
    NAPI_CALL_RETURN_VOID(_env, napi_create_number(_env, (uint64_t)window, &callbackArgs[0]));
    NAPI_CALL_RETURN_VOID(_env, napi_create_number(_env, width, &callbackArgs[1]));
    NAPI_CALL_RETURN_VOID(_env, napi_create_number(_env, height, &callbackArgs[2]));

    CALL_NAPI_FUNCTION_GLFW_CALLBACK(_windowSizeCallbackReference, 3, callbackArgs);
}

DECLARE_NAPI_METHOD(SetWindowSizeCallback){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_INT64(_window, 0);
    GET_NAPI_PARAM_FUNCTION(windowSizeCallback, 1);
    GLFWwindow* window = (GLFWwindow*)_window;

    NAPI_CALL(env, napi_create_reference(env, windowSizeCallback, 1, &_windowSizeCallbackReference));

    glfwSetWindowSizeCallback(window, napiGlfwWindowSizeCallback);
    RETURN_NAPI_UNDEFINED();
}

void napiGlfwWindowCloseCallback(GLFWwindow* window){
    napi_value callbackArgs[1];
    NAPI_CALL_RETURN_VOID(_env, napi_create_number(_env, (uint64_t)window, &callbackArgs[0]));

    CALL_NAPI_FUNCTION_GLFW_CALLBACK(_windowCloseCallbackReference, 1, callbackArgs);
}

DECLARE_NAPI_METHOD(SetWindowCloseCallback){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_INT64(_window, 0);
    GET_NAPI_PARAM_FUNCTION(windowCloseCallback, 1);
    GLFWwindow* window = (GLFWwindow*)_window;

    NAPI_CALL(env, napi_create_reference(env, windowCloseCallback, 1, &_windowCloseCallbackReference));

    glfwSetWindowCloseCallback(window, napiGlfwWindowCloseCallback);
    RETURN_NAPI_UNDEFINED();
}

void napiGlfwFramebufferSizeCallback(GLFWwindow* window, int width, int height){
    napi_value callbackArgs[3];
    NAPI_CALL_RETURN_VOID(_env, napi_create_number(_env, (uint64_t)window, &callbackArgs[0]));
    NAPI_CALL_RETURN_VOID(_env, napi_create_number(_env, width, &callbackArgs[1]));
    NAPI_CALL_RETURN_VOID(_env, napi_create_number(_env, height, &callbackArgs[2]));

    CALL_NAPI_FUNCTION_GLFW_CALLBACK(_framebufferSizeCallbackReference, 3, callbackArgs);
}


DECLARE_NAPI_METHOD(SetFramebufferSizeCallback){
    GET_NAPI_PARAMS_INFO(2);
    GET_NAPI_PARAM_INT64(_window, 0);
    GET_NAPI_PARAM_FUNCTION(framebufferSizeCallback, 1);
    GLFWwindow* window = (GLFWwindow*)_window;

    NAPI_CALL(env, napi_create_reference(env, framebufferSizeCallback, 1, &_framebufferSizeCallbackReference));

    glfwSetFramebufferSizeCallback(window, napiGlfwFramebufferSizeCallback);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(PollEvents){
    glfwPollEvents();
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(SwapBuffers){
    GET_NAPI_PARAMS_INFO(1);
    GET_NAPI_PARAM_INT64(_window, 0);
    GLFWwindow* window = (GLFWwindow*)_window;

    glfwSwapBuffers(window);
    RETURN_NAPI_UNDEFINED();
}

DECLARE_NAPI_METHOD(GetMonitors){
    int monitorCount;
    glfwGetMonitors(&monitorCount);
    RETURN_NAPI_NUMBER(monitorCount);
}


DECLARE_NAPI_METHOD(InitGlad){
    RETURN_NAPI_BOOL(gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress));
}

void onExit(){
    glfwTerminate();
}

void onSigInt(int dummy){
    exit(0);
}

void _ModuleInit(napi_env env, napi_value exports, napi_value module, void* priv) {
    napi_property_descriptor desc;
    napi_value val;

    _env = env;

    atexit(onExit);
    signal(SIGINT, onSigInt);

    EXPORT_NAPI_METHOD("initGlad", InitGlad);

    // context
    EXPORT_NAPI_METHOD("makeContextCurrent", MakeContextCurrent);
    EXPORT_NAPI_METHOD("getCurrentContext", GetCurrentContext);
    EXPORT_NAPI_METHOD("swapInterval", SwapInterval);
    EXPORT_NAPI_METHOD("extensionSupported", ExtensionSupported);
    EXPORT_NAPI_METHOD("getProcAddress", GetProcAddress);

    // init
    EXPORT_NAPI_METHOD("init", Init);
    EXPORT_NAPI_METHOD("terminate", Terminate);
    EXPORT_NAPI_METHOD("getVersion", GetVersion);
    EXPORT_NAPI_METHOD("getVersionString", GetVersionString);
    EXPORT_NAPI_METHOD("setErrorCallback", SetErrorCallback);


    // input
    //#EXPORT_NAPI_METHOD("createCursor", CreateCursor); - no GLFWImage support yet
    EXPORT_NAPI_METHOD("createStandardCursor", CreateStandardCursor);
    EXPORT_NAPI_METHOD("getClipboardString", GetClipboardString);
    EXPORT_NAPI_METHOD("destroyCursor", DestroyCursor);
    EXPORT_NAPI_METHOD("getCursorPos", GetCursorPos);
    EXPORT_NAPI_METHOD("getInputMode", GetInputMode);
    EXPORT_NAPI_METHOD("getJoystickAxes", GetJoystickAxes);
    EXPORT_NAPI_METHOD("getJoystickButtons", GetJoystickButtons);
    EXPORT_NAPI_METHOD("getJoystickName", GetJoystickName);
    EXPORT_NAPI_METHOD("getKey", GetKey);
    EXPORT_NAPI_METHOD("getKeyName", GetKeyName);
    EXPORT_NAPI_METHOD("getMouseButton", GetMouseButton);
    EXPORT_NAPI_METHOD("getTime", GetTime);
    EXPORT_NAPI_METHOD("getTimerFrequency", GetTimerFrequency);
    EXPORT_NAPI_METHOD("getTimerValue", GetTimerValue);
    EXPORT_NAPI_METHOD("joystickPresent", JoystickPresent);
    //#EXPORT_NAPI_METHOD("setCharCallback", SetCharCallback); - needed?
    //#EXPORT_NAPI_METHOD("setCharModsCallback", SetCharModsCallback); - needed?
    EXPORT_NAPI_METHOD("setClipboardString", SetClipboardString);
    EXPORT_NAPI_METHOD("setCursor", SetCursor);
    //#EXPORT_NAPI_METHOD("setCursorEnterCallback", SetCursorEnterCallback); - TODO
    EXPORT_NAPI_METHOD("setCursorPos", SetCursorPos);
    EXPORT_NAPI_METHOD("setCursorPosCallback", SetCursorPosCallback);
    //#EXPORT_NAPI_METHOD("setDropCallback", SetDropCallback); - TODO
    EXPORT_NAPI_METHOD("setInputMode", SetInputMode);
    //#EXPORT_NAPI_METHOD("setJoystickCallback", SetJoystickCallback); - TODO
    EXPORT_NAPI_METHOD("setKeyCallback", SetKeyCallback);
    EXPORT_NAPI_METHOD("setMouseButtonCallback", SetMouseButtonCallback);
    //#EXPORT_NAPI_METHOD("setScrollCallback", SetScrollCallback); - TODO
    EXPORT_NAPI_METHOD("setTime", SetTime);

    // monitor
    EXPORT_NAPI_METHOD("getMonitors", GetMonitors);
    //EXPORT_NAPI_METHOD("getPrimaryMonitor", GetPrimaryMonitor);
    //EXPORT_NAPI_METHOD("getMonitorPos", GetMonitorPos);
    //EXPORT_NAPI_METHOD("getMonitorPhysicalSize", GetMonitorPhysicalSize);
    //EXPORT_NAPI_METHOD("getMonitorName", GetMonitorName);
    //EXPORT_NAPI_METHOD("setMonitorCallback", SetMonitorCallback);
    //EXPORT_NAPI_METHOD("getVideoModes", GetVideoModes);
    //EXPORT_NAPI_METHOD("getVideoMode", GetVideoMode);
    //EXPORT_NAPI_METHOD("setGamma", SetGamma);
    //EXPORT_NAPI_METHOD("getGammaRamp", GetGammaRamp);
    //EXPORT_NAPI_METHOD("setGammaRamp", SetGammaRamp);


    // window
    //EXPORT_NAPI_METHOD("defaultWindowHints", DefaultWindowHints);
    //EXPORT_NAPI_METHOD("windowHint", WindowHint);
    EXPORT_NAPI_METHOD("createWindow", CreateWindow);
    EXPORT_NAPI_METHOD("destroyWindow", DestroyWindow);
    EXPORT_NAPI_METHOD("windowShouldClose", WindowShouldClose);
    //EXPORT_NAPI_METHOD("setWindowShouldClose", SetWindowShouldClose);
    EXPORT_NAPI_METHOD("setWindowTitle", SetWindowTitle);
    //EXPORT_NAPI_METHOD("setWindowIcon", SetWindowIcon);
    //EXPORT_NAPI_METHOD("getWindowPos", GetWindowPos);
    //EXPORT_NAPI_METHOD("setWindowPos", SetWindowPos);
    EXPORT_NAPI_METHOD("getWindowSize", GetWindowSize);
    //EXPORT_NAPI_METHOD("setWindowSizeLimit", SetWindowSizeLimit);
    //EXPORT_NAPI_METHOD("setWindowAspectRatio", SetWindowAspectRatio);
    EXPORT_NAPI_METHOD("setWindowSize", SetWindowSize);
    EXPORT_NAPI_METHOD("getFramebufferSize", GetFramebufferSize);
    //EXPORT_NAPI_METHOD("getWindowFrameSize", GetWindowFrameSize);
    //EXPORT_NAPI_METHOD("iconifyWindow", IconifyWindow);
    //EXPORT_NAPI_METHOD("restoreWindow", RestoreWindow);
    //EXPORT_NAPI_METHOD("maximizeWindow", MaximizeWindow);
    //EXPORT_NAPI_METHOD("showWindow", ShowWindow);
    //EXPORT_NAPI_METHOD("hideWindow", HideWindow);
    //EXPORT_NAPI_METHOD("focusWindow", FocusWindow);
    //EXPORT_NAPI_METHOD("getWindowMonitor", GetWindowMonitor);
    //EXPORT_NAPI_METHOD("setWindowMonitor", SetWindowMonitor);
    //EXPORT_NAPI_METHOD("getWindowAttrib", GetWindowAttrib);
    //EXPORT_NAPI_METHOD("setWindowUserPointer", SetWindowUserPointer);
    //EXPORT_NAPI_METHOD("getWindowUserPointer", GetWindowUserPointer);
    //EXPORT_NAPI_METHOD("setWindowPosCallback", SetWindowPosCallback);
    EXPORT_NAPI_METHOD("setWindowSizeCallback", SetWindowSizeCallback);
    EXPORT_NAPI_METHOD("setWindowCloseCallback", SetWindowCloseCallback);
    //EXPORT_NAPI_METHOD("setWindowRefreshCallback", SetWindowRefreshCallback);
    //EXPORT_NAPI_METHOD("setWindowIconifyCallback", SetWindowIconifyCallback);
    EXPORT_NAPI_METHOD("setFramebufferSizeCallback", SetFramebufferSizeCallback);
    EXPORT_NAPI_METHOD("pollEvents", PollEvents);
    //EXPORT_NAPI_METHOD("waitEvents", WaitEvents);
    //EXPORT_NAPI_METHOD("waitEventsTimeout", WaitEventsTimeout);
    //EXPORT_NAPI_METHOD("postEmptyEvent", PostEmptyEvent);
    EXPORT_NAPI_METHOD("swapBuffers", SwapBuffers);

    // consts
    EXPORT_NAPI_CONST_GLFW(VERSION_MAJOR);
    EXPORT_NAPI_CONST_GLFW(VERSION_MINOR);
    EXPORT_NAPI_CONST_GLFW(VERSION_REVISION);

    EXPORT_NAPI_CONST_GLFW(NOT_INITIALIZED);
    EXPORT_NAPI_CONST_GLFW(NO_CURRENT_CONTEXT);
    EXPORT_NAPI_CONST_GLFW(INVALID_ENUM);
    EXPORT_NAPI_CONST_GLFW(INVALID_VALUE);
    EXPORT_NAPI_CONST_GLFW(OUT_OF_MEMORY);
    EXPORT_NAPI_CONST_GLFW(API_UNAVAILABLE);
    EXPORT_NAPI_CONST_GLFW(VERSION_UNAVAILABLE);
    EXPORT_NAPI_CONST_GLFW(PLATFORM_ERROR);
    EXPORT_NAPI_CONST_GLFW(FORMAT_UNAVAILABLE);
    EXPORT_NAPI_CONST_GLFW(NO_WINDOW_CONTEXT);

    EXPORT_NAPI_CONST_GLFW(PRESS);
    EXPORT_NAPI_CONST_GLFW(RELEASE);
    EXPORT_NAPI_CONST_GLFW(REPEAT);

    EXPORT_NAPI_CONST_GLFW(JOYSTICK_1);
    EXPORT_NAPI_CONST_GLFW(JOYSTICK_2);
    EXPORT_NAPI_CONST_GLFW(JOYSTICK_3);
    EXPORT_NAPI_CONST_GLFW(JOYSTICK_4);
    EXPORT_NAPI_CONST_GLFW(JOYSTICK_5);
    EXPORT_NAPI_CONST_GLFW(JOYSTICK_6);
    EXPORT_NAPI_CONST_GLFW(JOYSTICK_7);
    EXPORT_NAPI_CONST_GLFW(JOYSTICK_8);
    EXPORT_NAPI_CONST_GLFW(JOYSTICK_9);
    EXPORT_NAPI_CONST_GLFW(JOYSTICK_10);
    EXPORT_NAPI_CONST_GLFW(JOYSTICK_12);
    EXPORT_NAPI_CONST_GLFW(JOYSTICK_13);
    EXPORT_NAPI_CONST_GLFW(JOYSTICK_14);
    EXPORT_NAPI_CONST_GLFW(JOYSTICK_15);
    EXPORT_NAPI_CONST_GLFW(JOYSTICK_16);
    EXPORT_NAPI_CONST_GLFW(JOYSTICK_LAST);

    EXPORT_NAPI_CONST_GLFW(KEY_UNKNOWN);
    EXPORT_NAPI_CONST_GLFW(KEY_SPACE);
    EXPORT_NAPI_CONST_GLFW(KEY_APOSTROPHE);
    EXPORT_NAPI_CONST_GLFW(KEY_COMMA);
    EXPORT_NAPI_CONST_GLFW(KEY_MINUS);
    EXPORT_NAPI_CONST_GLFW(KEY_PERIOD);
    EXPORT_NAPI_CONST_GLFW(KEY_SLASH);
    EXPORT_NAPI_CONST_GLFW(KEY_0);
    EXPORT_NAPI_CONST_GLFW(KEY_1);
    EXPORT_NAPI_CONST_GLFW(KEY_2);
    EXPORT_NAPI_CONST_GLFW(KEY_3);
    EXPORT_NAPI_CONST_GLFW(KEY_4);
    EXPORT_NAPI_CONST_GLFW(KEY_5);
    EXPORT_NAPI_CONST_GLFW(KEY_6);
    EXPORT_NAPI_CONST_GLFW(KEY_7);
    EXPORT_NAPI_CONST_GLFW(KEY_8);
    EXPORT_NAPI_CONST_GLFW(KEY_9);
    EXPORT_NAPI_CONST_GLFW(KEY_SEMICOLON);
    EXPORT_NAPI_CONST_GLFW(KEY_EQUAL);
    EXPORT_NAPI_CONST_GLFW(KEY_A);
    EXPORT_NAPI_CONST_GLFW(KEY_B);
    EXPORT_NAPI_CONST_GLFW(KEY_C);
    EXPORT_NAPI_CONST_GLFW(KEY_D);
    EXPORT_NAPI_CONST_GLFW(KEY_E);
    EXPORT_NAPI_CONST_GLFW(KEY_F);
    EXPORT_NAPI_CONST_GLFW(KEY_G);
    EXPORT_NAPI_CONST_GLFW(KEY_H);
    EXPORT_NAPI_CONST_GLFW(KEY_I);
    EXPORT_NAPI_CONST_GLFW(KEY_J);
    EXPORT_NAPI_CONST_GLFW(KEY_K);
    EXPORT_NAPI_CONST_GLFW(KEY_L);
    EXPORT_NAPI_CONST_GLFW(KEY_M);
    EXPORT_NAPI_CONST_GLFW(KEY_N);
    EXPORT_NAPI_CONST_GLFW(KEY_O);
    EXPORT_NAPI_CONST_GLFW(KEY_P);
    EXPORT_NAPI_CONST_GLFW(KEY_Q);
    EXPORT_NAPI_CONST_GLFW(KEY_R);
    EXPORT_NAPI_CONST_GLFW(KEY_S);
    EXPORT_NAPI_CONST_GLFW(KEY_T);
    EXPORT_NAPI_CONST_GLFW(KEY_U);
    EXPORT_NAPI_CONST_GLFW(KEY_V);
    EXPORT_NAPI_CONST_GLFW(KEY_W);
    EXPORT_NAPI_CONST_GLFW(KEY_X);
    EXPORT_NAPI_CONST_GLFW(KEY_Y);
    EXPORT_NAPI_CONST_GLFW(KEY_Z);
    EXPORT_NAPI_CONST_GLFW(KEY_LEFT_BRACKET);
    EXPORT_NAPI_CONST_GLFW(KEY_BACKSLASH);
    EXPORT_NAPI_CONST_GLFW(KEY_RIGHT_BRACKET);
    EXPORT_NAPI_CONST_GLFW(KEY_GRAVE_ACCENT);
    EXPORT_NAPI_CONST_GLFW(KEY_WORLD_1);
    EXPORT_NAPI_CONST_GLFW(KEY_WORLD_2);
    EXPORT_NAPI_CONST_GLFW(KEY_ESCAPE);
    EXPORT_NAPI_CONST_GLFW(KEY_ENTER);
    EXPORT_NAPI_CONST_GLFW(KEY_TAB);
    EXPORT_NAPI_CONST_GLFW(KEY_BACKSPACE);
    EXPORT_NAPI_CONST_GLFW(KEY_INSERT);
    EXPORT_NAPI_CONST_GLFW(KEY_DELETE);
    EXPORT_NAPI_CONST_GLFW(KEY_RIGHT);
    EXPORT_NAPI_CONST_GLFW(KEY_LEFT);
    EXPORT_NAPI_CONST_GLFW(KEY_DOWN);
    EXPORT_NAPI_CONST_GLFW(KEY_UP);
    EXPORT_NAPI_CONST_GLFW(KEY_PAGE_UP);
    EXPORT_NAPI_CONST_GLFW(KEY_PAGE_DOWN);
    EXPORT_NAPI_CONST_GLFW(KEY_HOME);
    EXPORT_NAPI_CONST_GLFW(KEY_END);
    EXPORT_NAPI_CONST_GLFW(KEY_CAPS_LOCK);
    EXPORT_NAPI_CONST_GLFW(KEY_SCROLL_LOCK);
    EXPORT_NAPI_CONST_GLFW(KEY_NUM_LOCK);
    EXPORT_NAPI_CONST_GLFW(KEY_PRINT_SCREEN);
    EXPORT_NAPI_CONST_GLFW(KEY_PAUSE);
    EXPORT_NAPI_CONST_GLFW(KEY_F1);
    EXPORT_NAPI_CONST_GLFW(KEY_F2);
    EXPORT_NAPI_CONST_GLFW(KEY_F3);
    EXPORT_NAPI_CONST_GLFW(KEY_F4);
    EXPORT_NAPI_CONST_GLFW(KEY_F5);
    EXPORT_NAPI_CONST_GLFW(KEY_F6);
    EXPORT_NAPI_CONST_GLFW(KEY_F7);
    EXPORT_NAPI_CONST_GLFW(KEY_F8);
    EXPORT_NAPI_CONST_GLFW(KEY_F9);
    EXPORT_NAPI_CONST_GLFW(KEY_F10);
    EXPORT_NAPI_CONST_GLFW(KEY_F11);
    EXPORT_NAPI_CONST_GLFW(KEY_F12);
    EXPORT_NAPI_CONST_GLFW(KEY_F13);
    EXPORT_NAPI_CONST_GLFW(KEY_F14);
    EXPORT_NAPI_CONST_GLFW(KEY_F15);
    EXPORT_NAPI_CONST_GLFW(KEY_F16);
    EXPORT_NAPI_CONST_GLFW(KEY_F17);
    EXPORT_NAPI_CONST_GLFW(KEY_F18);
    EXPORT_NAPI_CONST_GLFW(KEY_F19);
    EXPORT_NAPI_CONST_GLFW(KEY_F20);
    EXPORT_NAPI_CONST_GLFW(KEY_F21);
    EXPORT_NAPI_CONST_GLFW(KEY_F22);
    EXPORT_NAPI_CONST_GLFW(KEY_F23);
    EXPORT_NAPI_CONST_GLFW(KEY_F24);
    EXPORT_NAPI_CONST_GLFW(KEY_F25);
    EXPORT_NAPI_CONST_GLFW(KEY_KP_0);
    EXPORT_NAPI_CONST_GLFW(KEY_KP_1);
    EXPORT_NAPI_CONST_GLFW(KEY_KP_2);
    EXPORT_NAPI_CONST_GLFW(KEY_KP_3);
    EXPORT_NAPI_CONST_GLFW(KEY_KP_4);
    EXPORT_NAPI_CONST_GLFW(KEY_KP_5);
    EXPORT_NAPI_CONST_GLFW(KEY_KP_6);
    EXPORT_NAPI_CONST_GLFW(KEY_KP_7);
    EXPORT_NAPI_CONST_GLFW(KEY_KP_8);
    EXPORT_NAPI_CONST_GLFW(KEY_KP_9);
    EXPORT_NAPI_CONST_GLFW(KEY_KP_DECIMAL);
    EXPORT_NAPI_CONST_GLFW(KEY_KP_DIVIDE);
    EXPORT_NAPI_CONST_GLFW(KEY_KP_MULTIPLY);
    EXPORT_NAPI_CONST_GLFW(KEY_KP_SUBTRACT);
    EXPORT_NAPI_CONST_GLFW(KEY_KP_ADD);
    EXPORT_NAPI_CONST_GLFW(KEY_KP_ENTER);
    EXPORT_NAPI_CONST_GLFW(KEY_KP_EQUAL);
    EXPORT_NAPI_CONST_GLFW(KEY_LEFT_SHIFT);
    EXPORT_NAPI_CONST_GLFW(KEY_LEFT_CONTROL);
    EXPORT_NAPI_CONST_GLFW(KEY_LEFT_ALT);
    EXPORT_NAPI_CONST_GLFW(KEY_LEFT_SUPER);
    EXPORT_NAPI_CONST_GLFW(KEY_RIGHT_SHIFT);
    EXPORT_NAPI_CONST_GLFW(KEY_RIGHT_CONTROL);
    EXPORT_NAPI_CONST_GLFW(KEY_RIGHT_ALT);
    EXPORT_NAPI_CONST_GLFW(KEY_RIGHT_SUPER);
    EXPORT_NAPI_CONST_GLFW(KEY_MENU);
    EXPORT_NAPI_CONST_GLFW(KEY_LAST);

    EXPORT_NAPI_CONST_GLFW(MOD_SHIFT);
    EXPORT_NAPI_CONST_GLFW(MOD_CONTROL);
    EXPORT_NAPI_CONST_GLFW(MOD_ALT);
    EXPORT_NAPI_CONST_GLFW(MOD_SUPER);

    EXPORT_NAPI_CONST_GLFW(MOUSE_BUTTON_1);
    EXPORT_NAPI_CONST_GLFW(MOUSE_BUTTON_2);
    EXPORT_NAPI_CONST_GLFW(MOUSE_BUTTON_3);
    EXPORT_NAPI_CONST_GLFW(MOUSE_BUTTON_4);
    EXPORT_NAPI_CONST_GLFW(MOUSE_BUTTON_5);
    EXPORT_NAPI_CONST_GLFW(MOUSE_BUTTON_6);
    EXPORT_NAPI_CONST_GLFW(MOUSE_BUTTON_7);
    EXPORT_NAPI_CONST_GLFW(MOUSE_BUTTON_8);
    EXPORT_NAPI_CONST_GLFW(MOUSE_BUTTON_LAST);
    EXPORT_NAPI_CONST_GLFW(MOUSE_BUTTON_LEFT);
    EXPORT_NAPI_CONST_GLFW(MOUSE_BUTTON_RIGHT);
    EXPORT_NAPI_CONST_GLFW(MOUSE_BUTTON_MIDDLE);

    EXPORT_NAPI_CONST_GLFW(ARROW_CURSOR);
    EXPORT_NAPI_CONST_GLFW(IBEAM_CURSOR);
    EXPORT_NAPI_CONST_GLFW(CROSSHAIR_CURSOR);
    EXPORT_NAPI_CONST_GLFW(HAND_CURSOR);
    EXPORT_NAPI_CONST_GLFW(HRESIZE_CURSOR);
    EXPORT_NAPI_CONST_GLFW(VRESIZE_CURSOR);

    EXPORT_NAPI_CONST_GLFW(RESIZABLE);
    EXPORT_NAPI_CONST_GLFW(VISIBLE);
    EXPORT_NAPI_CONST_GLFW(DECORATED);
    EXPORT_NAPI_CONST_GLFW(FOCUSED);
    EXPORT_NAPI_CONST_GLFW(AUTO_ICONIFY);
    EXPORT_NAPI_CONST_GLFW(FLOATING);
    EXPORT_NAPI_CONST_GLFW(MAXIMIZED);
    EXPORT_NAPI_CONST_GLFW(RED_BITS);
    EXPORT_NAPI_CONST_GLFW(GREEN_BITS);
    EXPORT_NAPI_CONST_GLFW(BLUE_BITS);
    EXPORT_NAPI_CONST_GLFW(ALPHA_BITS);
    EXPORT_NAPI_CONST_GLFW(DEPTH_BITS);
    EXPORT_NAPI_CONST_GLFW(STENCIL_BITS);
    EXPORT_NAPI_CONST_GLFW(ACCUM_RED_BITS);
    EXPORT_NAPI_CONST_GLFW(ACCUM_GREEN_BITS);
    EXPORT_NAPI_CONST_GLFW(ACCUM_BLUE_BITS);
    EXPORT_NAPI_CONST_GLFW(ACCUM_ALPHA_BITS);
    EXPORT_NAPI_CONST_GLFW(AUX_BUFFERS);
    EXPORT_NAPI_CONST_GLFW(SAMPLES);
    EXPORT_NAPI_CONST_GLFW(REFRESH_RATE);
    EXPORT_NAPI_CONST_GLFW(STEREO);
    EXPORT_NAPI_CONST_GLFW(SRGB_CAPABLE);
    EXPORT_NAPI_CONST_GLFW(DOUBLEBUFFER);
    EXPORT_NAPI_CONST_GLFW(CLIENT_API);
    EXPORT_NAPI_CONST_GLFW(CONTEXT_CREATION_API);
    EXPORT_NAPI_CONST_GLFW(CONTEXT_VERSION_MAJOR);
    EXPORT_NAPI_CONST_GLFW(CONTEXT_VERSION_MINOR);
    EXPORT_NAPI_CONST_GLFW(CONTEXT_ROBUSTNESS);
    EXPORT_NAPI_CONST_GLFW(CONTEXT_RELEASE_BEHAVIOR);
    EXPORT_NAPI_CONST_GLFW(OPENGL_FORWARD_COMPAT);
    EXPORT_NAPI_CONST_GLFW(OPENGL_DEBUG_CONTEXT);
    EXPORT_NAPI_CONST_GLFW(OPENGL_PROFILE);

    EXPORT_NAPI_CONST_GLFW(DONT_CARE);
    EXPORT_NAPI_CONST_GLFW(ICONIFIED);
    EXPORT_NAPI_CONST_GLFW(OPENGL_API);
    EXPORT_NAPI_CONST_GLFW(OPENGL_ES_API);
    EXPORT_NAPI_CONST_GLFW(NO_API);
    EXPORT_NAPI_CONST_GLFW(NATIVE_CONTEXT_API);
    EXPORT_NAPI_CONST_GLFW(EGL_CONTEXT_API);
    EXPORT_NAPI_CONST_GLFW(NO_ROBUSTNESS);
    EXPORT_NAPI_CONST_GLFW(NO_RESET_NOTIFICATION);
    EXPORT_NAPI_CONST_GLFW(LOSE_CONTEXT_ON_RESET);
    EXPORT_NAPI_CONST_GLFW(ANY_RELEASE_BEHAVIOR);
    EXPORT_NAPI_CONST_GLFW(RELEASE_BEHAVIOR_FLUSH);
    EXPORT_NAPI_CONST_GLFW(RELEASE_BEHAVIOR_NONE);
    EXPORT_NAPI_CONST_GLFW(OPENGL_ANY_PROFILE);
    EXPORT_NAPI_CONST_GLFW(OPENGL_COMPAT_PROFILE);
    EXPORT_NAPI_CONST_GLFW(OPENGL_CORE_PROFILE);

    EXPORT_NAPI_CONST_GLFW(CURSOR);
    EXPORT_NAPI_CONST_GLFW(STICKY_KEYS);
    EXPORT_NAPI_CONST_GLFW(STICKY_MOUSE_BUTTONS);
    EXPORT_NAPI_CONST_GLFW(CURSOR_NORMAL);
    EXPORT_NAPI_CONST_GLFW(CURSOR_HIDDEN);
    EXPORT_NAPI_CONST_GLFW(CURSOR_DISABLED);

    EXPORT_NAPI_CONST_GLFW(CONNECTED);
    EXPORT_NAPI_CONST_GLFW(DISCONNECTED);
}

NAPI_MODULE(glfw, _ModuleInit);
