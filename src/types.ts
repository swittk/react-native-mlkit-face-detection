import type { NativeFrameWrapper } from "react-native-native-video";

/**
 * (Default is fast)
 * Favor speed or accuracy when detecting faces
 */
export type PerformanceMode = 'fast' | 'accurate';
/**
 * (Default is none)
 * Whether to attempt to detect the facial "landmarks"—eyes, ears, nose, cheeks, mouth—of all detected faces.
 */
export type LandmarkMode = 'none' | 'all';
/** (Default is none)
 * Whether to detect the contours of facial features. Contours are detected for only the most prominent face in an image
 */
export type ContourMode = 'none' | 'all';
/**
 * (Default is none)
 * Whether or not to classify faces into categories such as "smiling" and "eyes open".
 */
export type ClassificationMode = 'none' | 'all';

export type SKRNMLKitFaceDetectionOptions = {
  /**
   * (Default is fast)
   * Favor speed or accuracy when detecting faces
   */
  performanceMode: PerformanceMode,
  /**
   * (Default is none)
   * Whether to attempt to detect the facial "landmarks"—eyes, ears, nose, cheeks, mouth—of all detected faces.
   */
  landmarkMode: LandmarkMode,
  /** (Default is none)
   * Whether to detect the contours of facial features. Contours are detected for only the most prominent face in an image
   */
  contourMode: ContourMode,
  /**
   * (Default is none)
   * Whether or not to classify faces into categories such as "smiling" and "eyes open".
   */
  classificationMode: ClassificationMode,
  /** float (default: 0.1)
   * 
   * Sets the smallest desired face size, expressed as the ratio of the width of the head to width of the image. 
   */
  minFaceSize: number,
  /** false (default) | true
   * 
   * Whether or not to assign faces an ID, which can be used to track faces across images.
   * 
   * Note that when contour detection is enabled, only one face is detected, so face tracking doesn't produce useful results. 
   * For this reason, and to improve detection speed, don't enable both contour detection and face tracking
   */
  trackingEnabled: false | true
}


export const SKRNMLKitFaceDetectionLandmarkTypes = ["MouthBottom", "MouthRight", "MouthLeft", "LeftEar", "RightEar", "LeftEye", "RightEye", "LeftCheek", "RightCheek", "NoseBase"] as const;
export type SKRNMLKitFaceDetectionLandmarkType = (typeof SKRNMLKitFaceDetectionLandmarkTypes)[number];
export const SKRNMLKitFaceDetectionContourTypes = ["Face", "LeftEyebrowTop", "LeftEyebrowBottom", "RightEyebrowTop", "RightEyebrowBottom", "LeftEye", "RightEye", "UpperLipTop", "UpperLipBottom", "LowerLipTop", "LowerLipBottom", "NoseBridge", "NoseBottom", "LeftCheek", "RightCheek"] as const;
export type SKRNMLKitFaceDetectionContourType = (typeof SKRNMLKitFaceDetectionContourTypes)[number];


export interface SKRNMLKitRect {
  x: number, y: number,
  width: number, height: number
};

export interface SKRNMLKitMLKVisionPoint {
  x: number, y: number
}
export interface SKRNMLKitMLKFaceLandmark {
  type: SKRNMLKitFaceDetectionLandmarkType;
  position: SKRNMLKitMLKVisionPoint;
}
export interface SKRNMLKitMLKFaceContour {
  type: SKRNMLKitFaceDetectionContourType;
  points: SKRNMLKitMLKVisionPoint[];
}

export interface SKRNMLKitMLKFace {
  frame: SKRNMLKitRect;
  landmarks: SKRNMLKitMLKFaceLandmark[];
  contours: SKRNMLKitMLKFaceContour[];
  hasTrackingID: boolean;
  trackingID: number;
  hasHeadEulerAngleX: boolean;
  headEulerAngleX: number;
  hasHeadEulerAngleY: boolean;
  headEulerAngleY: number;
  hasHeadEulerAngleZ: boolean;
  headEulerAngleZ: number;
  hasSmilingProbability: boolean;
  smilingProbability: number;
  hasLeftEyeOpenProbability: boolean;
  leftEyeOpenProbability: number;
  hasRightEyeOpenProbability: boolean;
  rightEyeOpenProbability: number;
  contourOfType(type: SKRNMLKitFaceDetectionContourType): SKRNMLKitMLKFaceContour | undefined;
  landmarkOfType(type: SKRNMLKitFaceDetectionLandmarkType): SKRNMLKitMLKFaceLandmark | undefined;
}

export interface SKRNMLKitMLKVisionCameraFace {
  frame: SKRNMLKitRect;
  landmarks: Record<SKRNMLKitFaceDetectionLandmarkType, SKRNMLKitMLKFaceLandmark>;
  contours: Record<SKRNMLKitFaceDetectionContourType, SKRNMLKitMLKFaceContour>;
  hasTrackingID: boolean;
  trackingID: number;
  hasHeadEulerAngleX: boolean;
  headEulerAngleX: number;
  hasHeadEulerAngleY: boolean;
  headEulerAngleY: number;
  hasHeadEulerAngleZ: boolean;
  headEulerAngleZ: number;
  hasSmilingProbability: boolean;
  smilingProbability: number;
  hasLeftEyeOpenProbability: boolean;
  leftEyeOpenProbability: number;
  hasRightEyeOpenProbability: boolean;
  rightEyeOpenProbability: number;
}

export interface SKRNMLKitFaceDetector {
  process(frame: NativeFrameWrapper): SKRNMLKitMLKFace[];
}
