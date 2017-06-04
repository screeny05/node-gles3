import * as bindings from 'bindings';

const rawGlfw = bindings('glfw');
const rawGles = bindings('gles');

export { rawGlfw, rawGles };

console.log(rawGlfw.init());
console.log(rawGlfw.getMonitors());
const win = rawGlfw.createWindow(640, 480, "foobar");
console.log(rawGlfw.getVersion());
console.log(rawGlfw.getVersionString());
//rawGlfw.setCursorPosCallback(win, (x, y) => console.log('mousepos', x, y));

const raf = cb => setImmediate(_ => {
    rawGlfw.pollEvents();
    cb(rawGlfw.getTime() * 1000);
    rawGlfw.swapBuffers(win);
}, 16);

const frame = () => raf(delta => {
    rawGles.clear(rawGles.COLOR_BUFFER_BIT)
    frame();
});



rawGlfw.setErrorCallback((code, msg) => console.error(`GLFW ERR #${code}: ${msg}`));

console.log(rawGlfw.VERSION_MAJOR, rawGlfw.VERSION_MINOR, rawGlfw.VERSION_REVISION)

const cursor = rawGlfw.createStandardCursor(rawGlfw.CROSSHAIR_CURSOR);

rawGlfw.destroyCursor(cursor);

console.log(rawGlfw.getClipboardString(win));
console.log(rawGlfw.getCursorPos(win));
console.log(rawGlfw.getInputMode(win, rawGlfw.CURSOR));
console.log(rawGlfw.getKey(win, rawGlfw.KEY_SPACE));
console.log(rawGlfw.getKeyName(rawGlfw.KEY_W, 0));
console.log(rawGlfw.getTimerFrequency());
console.log(rawGlfw.getTimerValue());
console.log(rawGlfw.joystickPresent(0));

console.log(rawGlfw.makeContextCurrent(win));
console.log('ext', rawGlfw.extensionSupported("GL_ARB_debug_output"));
console.log(rawGlfw.initGlad());

console.log('crtbuffer', rawGles.createBuffer());
console.log('bfbuffer', rawGles.bufferData(rawGles.ARRAY_BUFFER, (new Uint8Array([255, 0, 254, 1, 253, 2, 252, 3])).buffer, rawGles.STATIC_DRAW));
console.log('subbuffer', rawGles.bufferSubData(rawGles.ARRAY_BUFFER, 2, (new Uint8Array([255, 0, 254, 1, 253, 2, 252, 3])).buffer));

rawGles.compressedTexImage2D(rawGles.TEXTURE_2D, 0, 0, 1, 1, 0, new Uint8Array([0, 0, 0, 0]));

console.log(rawGles.getActiveAttrib(0, 0))
console.log('isShader', rawGles.isShader(0));

frame();
