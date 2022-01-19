#ifndef react_native_mlkit_face_detection_h
#define react_native_mlkit_face_detection_h
#include <memory>
#include <jsi/jsi.h>
#include <map>
#if __has_include(<react-native-native-video/react-native-native-video.h>)
#define HAS_SKRN_NATIVE_VIDEO 1
#include <react-native-native-video/react-native-native-video.h>
#endif

// Stub classes
namespace facebook { namespace jsi {
class Runtime;
class Value;
class Object;
}
namespace react {
class CallInvoker;
}
}

// Start of actual content stuff
namespace SKRNMLKitFaceDetection {

class SKRNMLKitMLKFacePoint {
public:
    double x;
    double y;
    SKRNMLKitMLKFacePoint(double _x, double _y) : x(_x), y(_y) {};
    facebook::jsi::Object toJSI(facebook::jsi::Runtime &runtime);
};

class SKRNMLKitMLKFaceRect {
public:
    double x;
    double y;
    double width;
    double height;
    SKRNMLKitMLKFaceRect(double _x, double _y, double _w, double _h) : x(_x), y(_y), width(_w), height(_h) {};
    static SKRNMLKitMLKFaceRect Zero() {
        return SKRNMLKitMLKFaceRect(0,0,0,0);
    }
    facebook::jsi::Object toJSI(facebook::jsi::Runtime &runtime);
};
class SKRNMLKitMLKFaceLandmark  {
public:
    std::string type;
    SKRNMLKitMLKFacePoint position;
    SKRNMLKitMLKFaceLandmark(std::string _type, SKRNMLKitMLKFacePoint _pos) : type(_type), position(_pos) {};
    facebook::jsi::Object toJSI(facebook::jsi::Runtime &runtime);
};
class SKRNMLKitMLKFaceContour {
public:
    std::string type;
    std::vector<SKRNMLKitMLKFacePoint> points;
    SKRNMLKitMLKFaceContour(std::string _type, std::vector<SKRNMLKitMLKFacePoint> _ps) : type(_type), points(_ps) {};
    facebook::jsi::Object toJSI(facebook::jsi::Runtime &runtime);
};

class SKRNMLKitMLKFace : public facebook::jsi::HostObject {
    facebook::jsi::Value get(facebook::jsi::Runtime &runtime, const facebook::jsi::PropNameID &name);
    std::vector<facebook::jsi::PropNameID> getPropertyNames(facebook::jsi::Runtime& rt);
    
    //Override all these below
    virtual SKRNMLKitMLKFaceRect frame() {return SKRNMLKitMLKFaceRect::Zero();}
    virtual std::vector<std::shared_ptr<SKRNMLKitMLKFaceLandmark>> landmarks() {
        return std::vector<std::shared_ptr<SKRNMLKitMLKFaceLandmark>>();
    }
    virtual std::vector<std::shared_ptr<SKRNMLKitMLKFaceContour>> contours() {
        return std::vector<std::shared_ptr<SKRNMLKitMLKFaceContour>>();
    }
    virtual bool hasTrackingID() {return false;}
    virtual size_t trackingID() {return 0;}
    virtual bool hasHeadEulerAngleX() {return false;}
    virtual double headEulerAngleX() {return 0;}
    virtual bool hasHeadEulerAngleY() {return false;}
    virtual double headEulerAngleY() {return 0;}
    virtual bool hasHeadEulerAngleZ() {return false;}
    virtual double headEulerAngleZ() {return 0;}
    virtual bool hasSmilingProbability() {return false;}
    virtual double smilingProbability() {return 0;}
    virtual bool hasLeftEyeOpenProbability() {return false;}
    virtual double leftEyeOpenProbability() {return 0;}
    virtual bool hasRightEyeOpenProbability() {return false;}
    virtual double rightEyeOpenProbability() {return 0;}
    // Result is nullable
    virtual std::shared_ptr<SKRNMLKitMLKFaceLandmark> landmarkOfType(std::string landmarkType) {return std::shared_ptr<SKRNMLKitMLKFaceLandmark>();}
    // Result is nullable.
    virtual std::shared_ptr<SKRNMLKitMLKFaceContour> contourOfType(std::string contourType) {return std::shared_ptr<SKRNMLKitMLKFaceContour>();};
};

int multiply(float a, float b);

//class SKRNCommonFrameProcessor {
//    SKRNCommonFrameProcessor(std::map<std::string, std::string> options);
//public:
//#ifdef HAS_SKRN_NATIVE_VIDEO
//    virtual facebook::jsi::Value process(facebook::jsi::Runtime &runtime, std::shared_ptr<SKRNNativeVideo::SKNativeFrameWrapper>) {return facebook::jsi::Value::undefined(); };
//#endif
//};
//
//class SKRNCommonFrameProcessorHostObject : public facebook::jsi::HostObject {
//public:
//    facebook::jsi::Runtime &runtime;
//    SKRNCommonFrameProcessorHostObject(facebook::jsi::Runtime &_runtime, std::map<std::string, std::string> options);
//    facebook::jsi::Value get(facebook::jsi::Runtime &runtime, const facebook::jsi::PropNameID &name);
//    std::vector<facebook::jsi::PropNameID> getPropertyNames(facebook::jsi::Runtime& rt);
//};

class SKRNMLKitFaceDetector : public facebook::jsi::HostObject {
public:
    enum PerformanceMode { PerformanceModeFast = 0, PerformanceModeAccurate = 1 };
    enum LandmarkMode { LandmarkModeNone = 0, LandmarkModeAll = 1 };
    enum ContourMode { ContourModeNone = 0, ContourModeAll = 1 };
    enum ClassificationMode { ClassificationModeNone = 0, ClassificationModeAll = 1 };
    
    PerformanceMode performanceMode;
    LandmarkMode landmarkMode;
    ContourMode contourMode;
    ClassificationMode classificationMode;
    float minFaceSize;
    bool isTrackingEnabled;
    
    SKRNMLKitFaceDetector(PerformanceMode _performanceMode = PerformanceModeFast, LandmarkMode _landmarkMode = LandmarkModeNone, ContourMode _contourMode = ContourModeNone, float _minFaceSize = 0.1, bool _trackingEnabled = false);
    //    SKRNMLKitFaceDetector(std::map<std::string, std::string> options);
    facebook::jsi::Value get(facebook::jsi::Runtime &runtime, const facebook::jsi::PropNameID &name);
    std::vector<facebook::jsi::PropNameID> getPropertyNames(facebook::jsi::Runtime& rt);
#ifdef HAS_SKRN_NATIVE_VIDEO
    virtual std::vector<std::shared_ptr<SKRNMLKitMLKFace>> process(std::shared_ptr<SKRNNativeVideo::SKNativeFrameWrapper>) {return std::vector<std::shared_ptr<SKRNMLKitMLKFace>>(); };
#endif
};

void install(
             facebook::jsi::Runtime &jsiRuntime,
             std::function<std::shared_ptr<SKRNMLKitFaceDetector>
(facebook::jsi::Runtime& _runtime,
 SKRNMLKitFaceDetector::PerformanceMode _performanceMode,
 SKRNMLKitFaceDetector::LandmarkMode _landmarkMode,
 SKRNMLKitFaceDetector::ContourMode _contourMode,
 float _minFaceSize,
 bool _trackingEnabled
 )> detectorConstructor
             );
//void install(facebook::jsi::Runtime &jsiRuntime, std::shared_ptr<facebook::react::CallInvoker> invoker);
void cleanup(facebook::jsi::Runtime &jsiRuntime);


}

#endif /* react_native_mlkit_face_detection_h */
