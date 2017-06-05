/// <reference types="node" />
import * as EventEmitter from 'events';
export interface Options {
    width: number;
    height: number;
    title: string;
    vsync: boolean;
}
export declare class NativeWindow extends EventEmitter {
    static defaults: Options;
    glfw: any;
    gl: GLESRenderingContext;
    handle: number;
    _width: number;
    _height: number;
    _title: string;
    fbWidth: number;
    fbHeight: number;
    isListenerAddedCursorPos: boolean;
    isListenerAddedKey: boolean;
    isListenerAddedMouseButton: boolean;
    isOpen: boolean;
    constructor(options: any);
    onNewListener(event: string): void;
    onFramebufferSize(handle: any, width: any, height: any): void;
    onWindowSize(handle: any, width: any, height: any): void;
    onWindowClose(handle: any): void;
    onMousemove(handle: any, x: any, y: any): void;
    onKey(handle: any, key: any, scancode: any, action: any, modes: any): void;
    onMouseButton(handle: any, button: any, action: any, mods: any): void;
    close(): void;
    makeContextCurrent(): void;
    requestFrame(cb: (time: number) => void): void;
    setSize(width: any, height: any): void;
    title: string;
    width: number;
    height: number;
}
