import { GLESRenderingContext } from '../types/gles';
import * as bindings from 'bindings';

const rawGlfw: any = bindings('glfw');
const rawGles: GLESRenderingContext = bindings('gles');

// hide both from the console
(<any>rawGlfw).inspect = (depth, options) => options.stylize('[object GLFW]', 'special');
(<any>rawGles).inspect = (depth, options) => options.stylize('[object GLES]', 'special');

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
