import { NativeModules, Platform } from 'react-native';
export * from './types';
import type { SKRNMLKitFaceDetectionOptions, SKRNMLKitFaceDetector } from './types';
export { scanSKRNMLKitFace } from './FrameProcessor'
const LINKING_ERROR =
  `The package 'react-native-mlkit-face-detection' doesn't seem to be linked. Make sure: \n\n` +
  Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
  '- You rebuilt the app after installing the package\n' +
  '- You are not using Expo managed workflow\n';

const SKRNMLKitFaceDetection = NativeModules.SKRNMlkitFaceDetection
  ? NativeModules.SKRNMlkitFaceDetection
  : new Proxy(
    {},
    {
      get() {
        throw new Error(LINKING_ERROR);
      },
    }
  );

export function multiply(a: number, b: number): Promise<number> {
  return SKRNMLKitFaceDetection.multiply(a, b);
}


export function MLKitFaceDetector(options?: Partial<SKRNMLKitFaceDetectionOptions>): SKRNMLKitFaceDetector {
  return (global as any).SKRNMLKitFaceDetectionNewFaceDetector(options || {});
}


// Methods for visionCamera
/**
 * Same as initializeDetectorAtIndex(0)
 * @param opts 
 * @returns 
 */
export function initializeVisionCameraDetector(opts?: Partial<SKRNMLKitFaceDetectionOptions>) {
  return SKRNMLKitFaceDetection.initializeDetector(opts || {});
}
export function initializeVisionCameraDetectorAtIndex(index: number, opts?: Partial<SKRNMLKitFaceDetectionOptions>) {
  return SKRNMLKitFaceDetection.initializeDetectorAtIndex(index, opts || {});
}
export function clearVisionCameraDetectorAtIndex(index: number) {
  return SKRNMLKitFaceDetection.clearDetectorAtIndex(index);
}
export function clearVisionCameraDetector() {
  return SKRNMLKitFaceDetection.clearDetector();
}