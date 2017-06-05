import * as bindings from 'bindings';

const rawGlfw = bindings('glfw');
const rawGles = bindings('gles');

// hide both from the console
rawGlfw.inspect = (depth, options) => options.stylize('[object GLFW]', 'special');
rawGles.inspect = (depth, options) => options.stylize('[object GLES]', 'special');

// make sure we don't init more than once
rawGlfw.isInitialized = false;
rawGlfw.initOnce = () => {
    if(rawGlfw.isInitialized){
        return true;
    }

    rawGlfw.isInitialized = true;
    return rawGlfw.init();
}

export { rawGlfw, rawGles };

export * from './native-window';
