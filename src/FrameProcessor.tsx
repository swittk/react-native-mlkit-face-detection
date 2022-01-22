import type { Frame } from 'react-native-vision-camera'
import type { SKRNMLKitMLKVisionCameraFace } from './types';

/**
 * Scans frame for MLKit faces.
 */
export function scanSKRNMLKitFace(frame: Frame): SKRNMLKitMLKVisionCameraFace[] {
  'worklet'
  // @ts-expect-error
  return __SKRNMLKitFaceDetectionVisionCameraFrameProcessorPlugin(frame);
}
