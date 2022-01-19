//
//  SKRNMLKitiOSFaceDetector.h
//  react-native-mlkit-face-detection
//
//  Created by Switt Kongdachalert on 19/1/2565 BE.
//

#import <Foundation/Foundation.h>
#ifdef __cplusplus
#import "react-native-mlkit-face-detection.h"
#import <Foundation/Foundation.h>
#import "react-native-mlkit-face-detection.h"
#import <MLKitVision/MLKitVision.h>
#import <MLKitFaceDetection/MLKitFaceDetection.h>

namespace SKRNMLKitFaceDetection {

class SKRNMLKitiOSMLKFace : public SKRNMLKitMLKFace {
public:
    MLKFace *face;
    SKRNMLKitiOSMLKFace(MLKFace *face);
    ~SKRNMLKitiOSMLKFace();
    
    virtual SKRNMLKitMLKFaceRect frame() {return (SKRNMLKitMLKFaceRect){face.frame.origin.x, face.frame.origin.y, face.frame.size.width, face.frame.size.height }; };
    virtual std::vector<std::shared_ptr<SKRNMLKitMLKFaceLandmark>> landmarks();
    virtual std::vector<std::shared_ptr<SKRNMLKitMLKFaceContour>> contours();
    virtual bool hasTrackingID();
    virtual size_t trackingID();
    virtual bool hasHeadEulerAngleX();
    virtual double headEulerAngleX();
    virtual bool hasHeadEulerAngleY();
    virtual double headEulerAngleY();
    virtual bool hasHeadEulerAngleZ();
    virtual double headEulerAngleZ();
    virtual bool hasSmilingProbability();
    virtual double smilingProbability();
    virtual bool hasLeftEyeOpenProbability();
    virtual double leftEyeOpenProbability();
    virtual bool hasRightEyeOpenProbability();
    virtual double rightEyeOpenProbability();
    // Result is nullable
    virtual std::shared_ptr<SKRNMLKitMLKFaceLandmark> landmarkOfType(std::string landmarkType);
    // Result is nullable.
    virtual std::shared_ptr<SKRNMLKitMLKFaceContour> contourOfType(std::string contourType);
};

class SKRNMLKitiOSFaceDetector : public SKRNMLKitFaceDetector {
public:
    MLKFaceDetector *faceDetector;
    
    SKRNMLKitiOSFaceDetector(PerformanceMode _performanceMode = PerformanceModeFast, LandmarkMode _landmarkMode = LandmarkModeNone, ContourMode _contourMode = ContourModeNone, float _minFaceSize = 0.1, bool _trackingEnabled = false);
    ~SKRNMLKitiOSFaceDetector();
#ifdef HAS_SKRN_NATIVE_VIDEO
    virtual std::vector<std::shared_ptr<SKRNMLKitMLKFace>> process(std::shared_ptr<SKRNNativeVideo::SKNativeFrameWrapper>);
#endif
};
}

#endif

