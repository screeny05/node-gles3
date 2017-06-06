import { GLESRenderingContext } from './gles';

declare const rawGlfw: any;
declare const rawGles: GLESRenderingContext;
export { rawGlfw, rawGles };
export * from './native-window';
export * from './gles';
