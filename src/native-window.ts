import { glfw, gles } from '.';

import * as EventEmitter from 'events';

export interface Options {
    width: number;
    height: number;
    title: string;
    vsync: boolean;
    msaa: number;
}

export const availableErrorCodes = {
    [glfw.NOT_INITIALIZED]: 'GLFW NOT_INITIALIZED',
    [glfw.NO_CURRENT_CONTEXT]: 'GLFW NO_CURRENT_CONTEXT',
    [glfw.INVALID_ENUM]: 'GLFW INVALID_ENUM',
    [glfw.INVALID_VALUE]: 'GLFW INVALID_VALUE',
    [glfw.OUT_OF_MEMORY]: 'GLFW OUT_OF_MEMORY',
    [glfw.API_UNAVAILABLE]: 'GLFW API_UNAVAILABLE',
    [glfw.VERSION_UNAVAILABLE]: 'GLFW VERSION_UNAVAILABLE',
    [glfw.PLATFORM_ERROR]: 'GLFW PLATFORM_ERROR',
    [glfw.FORMAT_UNAVAILABLE]: 'GLFW FORMAT_UNAVAILABLE',
    [glfw.NO_WINDOW_CONTEXT]: 'GLFW NO_WINDOW_CONTEXT',
}

export class NativeWindow extends EventEmitter {
    static defaults: Options = {
        width: 800,
        height: 600,
        title: '',
        vsync: false,
        msaa: 4
    };

    glfw: any;
    gl: GLESRenderingContext;
    handle: number;

    _width: number;
    _height: number;
    _title: string;

    fbWidth: number;
    fbHeight: number;

    isListenerAddedCursorPos: boolean = false;
    isListenerAddedKey: boolean = false;
    isListenerAddedMouseButton: boolean = false;

    isOpen: boolean = false;

    constructor(options){
        super();
        options = { ...NativeWindow.defaults, ...options };

        this.glfw = glfw;
        this.gl = gles;

        if(!this.glfw.initOnce()){
            throw new Error('NativeWindow: unable to initialize GLFW');
        }

        this.glfw.setErrorCallback((code, message) => this.onError.bind(this));


        //this.glfw.windowHint(this.glfw.CONTEXT_VERSION_MAJOR, 4);
        //this.glfw.windowHint(this.glfw.CONTEXT_VERSION_MINOR, 1);
        //this.glfw.windowHint(this.glfw.OPENGL_FORWARD_COMPAT, this.gl.TRUE);
        //this.glfw.windowHint(this.glfw.OPENGL_PROFILE, this.glfw.OPENGL_CORE_PROFILE);
        this.glfw.windowHint(this.glfw.SAMPLES, options.msaa);

        this._width = options.width;
        this._height = options.height;
        this._title = options.title;
        this.handle = this.glfw.createWindow(this.width, this.height, this.title);
        this.isOpen = true;

        if(!this.handle){
            this.glfw.terminate();
            throw new Error('NativeWindow: unable to initialize Window');
        }

        this.glfw.setFramebufferSizeCallback(this.handle, this.onFramebufferSize.bind(this));
        this.glfw.setWindowSizeCallback(this.handle, this.onWindowSize.bind(this));
        this.glfw.setWindowCloseCallback(this.handle, this.onWindowClose.bind(this));
        this.on('newListener', this.onNewListener.bind(this));

        // init gles
        this.makeContextCurrent();

        if(!this.glfw.initGlad()){
            throw new Error('NativeWindow: unable to initialize GLES3.0');
        }

        this.glfw.swapInterval(options.vsync ? 1 : 0);

        const fbSize = this.glfw.getFramebufferSize(this.handle);
        this.fbWidth = fbSize.width;
        this.fbHeight = fbSize.height;
    }

    onNewListener(event: string): void {
        if(event === 'mousemove' && !this.isListenerAddedCursorPos){
            this.isListenerAddedCursorPos = true;
            return this.glfw.setCursorPosCallback(this.handle, this.onMousemove.bind(this));
        }

        if((event === 'mousebutton' || event === 'mousedown' || event === 'mouseup') && !this.isListenerAddedKey){
            this.isListenerAddedKey = true;
            return this.glfw.setKeyCallback(this.handle, this.onKey.bind(this));
        }

        if((event === 'key' || event === 'keydown' || event === 'keyup') && !this.isListenerAddedMouseButton){
            this.isListenerAddedMouseButton = true;
            return this.glfw.setMouseButtonCallback(this.handle, this.onMouseButton.bind(this));
        }
    }

    onError(code, message){
        this.emit('error', { code, message });
        console.log('GLFW ERR:', code, message);
    }

    onFramebufferSize(handle, width, height): void {
        if(handle !== this.handle){ return; }
        this.fbWidth = width;
        this.fbHeight = height;
        this.emit('framebufferResize');
    }

    onWindowSize(handle, width, height): void {
        if(handle !== this.handle){ return; }
        this._width = width;
        this._height = height;
        this.emit('resize');
    }

    onWindowClose(handle): void {
        if(handle !== this.handle){ return; }
        this.close();
    }

    onMousemove(handle, x, y): void {
        if(handle !== this.handle){ return; }
        this.emit('mousemove', { x, y });
    }

    onKey(handle, key, scancode, action, modes): void {
        if(handle !== this.handle){ return; }
        const data = { key, scancode, action, modes };
        this.emit('key', data);

        if(action === glfw.PRESS){
            this.emit('keydown', data);
        } else if(action === glfw.RELEASE){
            this.emit('keyup', data);
        }
    }

    onMouseButton(handle, button, action, mods): void {
        if(handle !== this.handle){ return; }
        const data = { handle, button, action, mods };
        this.emit('mousebutton', data);

        if(action === glfw.PRESS){
            this.emit('mousedown', data);
        } else if(action === glfw.RELEASE){
            this.emit('mouseup', data);
        }
    }

    close(): void {
        this.isOpen = false;
        this.emit('close');
        this.glfw.destroyWindow(this.handle);
    }

    makeContextCurrent(): void {
        this.glfw.makeContextCurrent(this.handle);
    }

    requestFrame(cb: (time: number) => void): void {
        if(!this.isOpen){
            return;
        }

        setImmediate(() => {
            const time = this.glfw.getTime();

            cb(time);

            this.glfw.swapBuffers(this.handle);
            this.glfw.pollEvents();
        });
    }

    setSize(width, height): void {
        this.glfw.setWindowSize(this.handle, width, height);
        this._width = width;
        this._height = height;
    }

    get title(){
        return this._title;
    }

    set title(val){
        this.glfw.setWindowTitle(this.handle, val);
    }

    get width(){
        return this._width;
    }

    set width(width){
        this.glfw.setWindowSize(this.handle, width, this._height);
        this._width = width;
    }

    get height(){
        return this._height;
    }

    set height(height){
        this.glfw.setWindowSize(this.handle, this._width, height);
        this._height = height;
    }
}
