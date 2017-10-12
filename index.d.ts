/// <reference path="./types/gles.d.ts" />
/// <reference path="./types/native-window.d.ts" />

declare const glfw: any;
declare const gles: GLESRenderingContext;

export { glfw, gles };
export * from './types/native-window';

/*
b=require('bindings')
glfw=b('glfw')
glace=b('glace')
gles=b('gles')
glfw.init()
glfw.setErrorCallback(console.log.bind(console,'errglfw'))

glfw.windowHint(glfw.CONTEXT_VERSION_MAJOR, 4);
glfw.windowHint(glfw.CONTEXT_VERSION_MINOR, 1);
glfw.windowHint(glfw.OPENGL_PROFILE, glfw.OPENGL_CORE_PROFILE);
glfw.windowHint(glfw.OPENGL_FORWARD_COMPAT, gles.TRUE);
handle=glfw.createWindow(600,600,'foobar');
glfw.makeContextCurrent(handle);
glfw.initGlace();
glace.getString(0x1F02)

 */
