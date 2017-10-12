import * as bindings from 'bindings';

const glfw: any = bindings('glfw');
const gles: GLESRenderingContext = bindings('gles');

// hide both from the console
(<any>glfw).inspect = (depth, options) => options.stylize('[object GLFW]', 'special');
(<any>gles).inspect = (depth, options) => options.stylize('[object GLES]', 'special');

// make sure we don't init more than once
glfw.isInitialized = false;
glfw.initOnce = () => {
    if(glfw.isInitialized){
        return true;
    }

    glfw.isInitialized = true;
    return glfw.init();
}

export { glfw, gles };

export * from './native-window';
