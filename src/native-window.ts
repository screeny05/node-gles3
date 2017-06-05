import { rawGlfw, rawGles } from '.';

import * as EventEmitter from 'events';

interface Options {
    width: number;
    height: number;
    title: string;
    vsync: boolean;
}

export class NativeWindow extends EventEmitter {
    static defaults: Options = {
        width: 800,
        height: 600,
        title: '',
        vsync: false,
    };

    glfw: any;
    gl: WebGLRenderingContext;
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

        this.glfw = rawGlfw;
        this.gl = rawGles;

        if(!this.glfw.initOnce()){
            throw new Error('NativeWindow: unable to initialize GLFW');
        }

        this._width = options.width;
        this._height = options.height;
        this._title = options.title;
        this.handle = this.glfw.createWindow(this.width, this.height, this.title);
        this.isOpen = true;

        if(!this.handle){
            this.glfw.terminate();
            throw new Error('NativeWindow: unable to initialize Window');
        }

        this.glfw.setErrorCallback((code, message) => this.emit('error', { code, message }));
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

    onNewListener(event, listener){
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

    onFramebufferSize(handle, width, height){
        if(handle !== this.handle){ return; }
        this.fbWidth = width;
        this.fbHeight = height;
        this.emit('framebufferResize');
    }

    onWindowSize(handle, width, height){
        if(handle !== this.handle){ return; }
        this._width = width;
        this._height = height;
        this.emit('resize');
    }

    onWindowClose(handle){
        if(handle !== this.handle){ return; }
        this.close();
    }

    onMousemove(handle, x, y){
        if(handle !== this.handle){ return; }
        this.emit('mousemove', { x, y });
    }

    onKey(handle, key, scancode, action, modes){
        if(handle !== this.handle){ return; }
        const data = { key, scancode, action, modes };
        this.emit('key', data);

        if(action === rawGlfw.PRESS){
            this.emit('keydown', data);
        } else if(action === rawGlfw.RELEASE){
            this.emit('keyup', data);
        }
    }

    onMouseButton(handle, button, action, mods){
        if(handle !== this.handle){ return; }
        const data = { handle, button, action, mods };
        this.emit('mousebutton', data);

        if(action === rawGlfw.PRESS){
            this.emit('mousedown', data);
        } else if(action === rawGlfw.RELEASE){
            this.emit('mouseup', data);
        }
    }

    close(){
        this.isOpen = false;
        this.emit('close');
        this.glfw.destroyWindow(this.handle);
    }

    makeContextCurrent(){
        this.glfw.makeContextCurrent(this.handle);
    }

    requestFrame(cb){
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

    setSize(width, height){
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

// following events have to get implemented:
// * resize
// * mousedown
