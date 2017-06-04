import * as bindings from 'bindings';

const rawGlfw = bindings('glfw');

export { rawGlfw };

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
    rawGlfw.testFrame();
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

frame();
