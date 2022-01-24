#include "react-native-mlkit-face-detection.h"
#include "CPPNumericStringHashCompare.h"

using namespace facebook;
using namespace jsi;

namespace SKRNMLKitFaceDetection {
int multiply(float a, float b) {
    return a * b;
}

SKRNMLKitFaceDetector::SKRNMLKitFaceDetector(PerformanceMode _performanceMode, LandmarkMode _landmarkMode, ContourMode _contourMode, float _minFaceSize, bool _trackingEnabled) :
performanceMode(_performanceMode), landmarkMode(_landmarkMode), contourMode(_contourMode), minFaceSize(_minFaceSize), isTrackingEnabled(_trackingEnabled) {

}
facebook::jsi::Value SKRNMLKitFaceDetector::get(facebook::jsi::Runtime &runtime, const facebook::jsi::PropNameID &name) {
    std::string methodName = name.utf8(runtime);
    long long methodSwitch = string_hash(methodName.c_str());
    switch (methodSwitch) {
#if HAS_SKRN_NATIVE_VIDEO
        case "process"_sh:{
            return jsi::Function::createFromHostFunction(runtime, name, 1, [&](jsi::Runtime &runtime, const jsi::Value &thisValue, const jsi::Value *arguments,
                                                                               size_t count) -> jsi::Value
                                                         {
                if(count < 1) {
                    throw jsi::JSError(runtime, "1 argument is expected for `process`");
                }
                std::shared_ptr<SKRNNativeVideo::SKNativeFrameWrapper> obj = arguments[0].asObject(runtime).asHostObject<SKRNNativeVideo::SKNativeFrameWrapper>(runtime);
                std::vector<std::shared_ptr<SKRNMLKitMLKFace>> results = process(obj);
                jsi::Array ret = jsi::Array(runtime, results.size());
                for(int i = 0; i < results.size(); i++) {
                    ret.setValueAtIndex(runtime, i, jsi::Object::createFromHostObject(runtime, results[i]));
                }
                return ret;
            });
        } break;
#endif
        default: return jsi::Value::undefined();
    }
    return jsi::Value::undefined();
}

static std::vector<std::string> nativeSKRNMLKitFaceDetectorKeys = {
#ifdef HAS_SKRN_NATIVE_VIDEO
    "process"
#endif
};

std::vector<facebook::jsi::PropNameID> SKRNMLKitFaceDetector::getPropertyNames(facebook::jsi::Runtime& rt) {
    std::vector<jsi::PropNameID> ret;
    for(std::string key : nativeSKRNMLKitFaceDetectorKeys) {
        ret.push_back(jsi::PropNameID::forUtf8(rt, key));
    }
    return ret;
}

#pragma mark - MLKFace stuff

static std::vector<std::string> nativeMLKFaceDetectionHostObjectKeys = {
    "frame",
    "landmarks",
    "contours",
    "hasTrackingID",
    "trackingID",
    "hasHeadEulerAngleX",
    "headEulerAngleX",
    "hasHeadEulerAngleY",
    "headEulerAngleY",
    "hasHeadEulerAngleZ",
    "headEulerAngleZ",
    "hasSmilingProbability",
    "smilingProbability",
    "hasLeftEyeOpenProbability",
    "leftEyeOpenProbability",
    "hasRightEyeOpenProbability",
    "rightEyeOpenProbability"
};
facebook::jsi::Value SKRNMLKitMLKFace::get(facebook::jsi::Runtime &runtime, const facebook::jsi::PropNameID &name) {
    std::string methodName = name.utf8(runtime);
    long long methodSwitch = string_hash(methodName.c_str());
    switch (methodSwitch) {
            // Generated switch cases + slight manual modifications
        case "frame"_sh: {
            return jsi::Value(frame().toJSI(runtime));
        } break;
        case "landmarks"_sh: {
            auto val = landmarks();
            size_t len = val.size();
            jsi::Array ret = jsi::Array(runtime, len);
            for(int i = 0; i < len; i++) { ret.setValueAtIndex(runtime, i, val[i].get()->toJSI(runtime)); }
            return ret;
        } break;
        case "contours"_sh: {
            auto val = contours();
            size_t len = val.size();
            jsi::Array ret = jsi::Array(runtime, len);
            for(int i = 0; i < len; i++) { ret.setValueAtIndex(runtime, i, val[i].get()->toJSI(runtime)); }
            return ret;
        } break;
        case "hasTrackingID"_sh: {
            return jsi::Value(hasTrackingID());
        } break;
        case "trackingID"_sh: {
            return jsi::Value((int)trackingID());
        } break;
        case "hasHeadEulerAngleX"_sh: {
            return jsi::Value(hasHeadEulerAngleX());
        } break;
        case "headEulerAngleX"_sh: {
            return jsi::Value(headEulerAngleX());
        } break;
        case "hasHeadEulerAngleY"_sh: {
            return jsi::Value(hasHeadEulerAngleY());
        } break;
        case "headEulerAngleY"_sh: {
            return jsi::Value(headEulerAngleY());
        } break;
        case "hasHeadEulerAngleZ"_sh: {
            return jsi::Value(hasHeadEulerAngleZ());
        } break;
        case "headEulerAngleZ"_sh: {
            return jsi::Value(headEulerAngleZ());
        } break;
        case "hasSmilingProbability"_sh: {
            return jsi::Value(hasSmilingProbability());
        } break;
        case "smilingProbability"_sh: {
            return jsi::Value(smilingProbability());
        } break;
        case "hasLeftEyeOpenProbability"_sh: {
            return jsi::Value(hasLeftEyeOpenProbability());
        } break;
        case "leftEyeOpenProbability"_sh: {
            return jsi::Value(leftEyeOpenProbability());
        } break;
        case "hasRightEyeOpenProbability"_sh: {
            return jsi::Value(hasRightEyeOpenProbability());
        } break;
        case "rightEyeOpenProbability"_sh: {
            return jsi::Value(rightEyeOpenProbability());
        } break;
        case "landmarkOfType"_sh: {
            return jsi::Function::createFromHostFunction
            (runtime, name, 1, [&](jsi::Runtime &runtime, const jsi::Value &thisValue, const jsi::Value *arguments, size_t count) -> jsi::Value
             {
                if(count < 1) {
                    throw jsi::JSError(runtime, "1 argument is expected for `landmarkOfType`");
                }
                std::string str = arguments[0].asString(runtime).utf8(runtime);
                std::shared_ptr<SKRNMLKitMLKFaceLandmark> res = landmarkOfType(str);
                if(res.get() == nullptr) {
                    return jsi::Value::undefined();
                }
                return res.get()->toJSI(runtime);
            });
        } break;
        case "contourOfType"_sh: {
            return jsi::Function::createFromHostFunction
            (runtime, name, 1, [&](jsi::Runtime &runtime, const jsi::Value &thisValue, const jsi::Value *arguments, size_t count) -> jsi::Value
             {
                if(count < 1) {
                    throw jsi::JSError(runtime, "1 argument is expected for `contourOfType`");
                }
                std::string str = arguments[0].asString(runtime).utf8(runtime);
                std::shared_ptr<SKRNMLKitMLKFaceContour> res = contourOfType(str);
                if(res.get() == nullptr) {
                    return jsi::Value::undefined();
                }
                return res.get()->toJSI(runtime);
            });
        } break;
        default: return jsi::Value::undefined();
    }
    return jsi::Value::undefined();
}
std::vector<facebook::jsi::PropNameID> SKRNMLKitMLKFace::getPropertyNames(facebook::jsi::Runtime& rt) {
    std::vector<jsi::PropNameID> ret;
    for(std::string key : nativeMLKFaceDetectionHostObjectKeys) {
        ret.push_back(jsi::PropNameID::forUtf8(rt, key));
    }
    return ret;
}

#pragma mark - small classes
facebook::jsi::Object SKRNMLKitMLKFaceRect::toJSI(facebook::jsi::Runtime &runtime) {
    facebook::jsi::Object obj = facebook::jsi::Object(runtime);
    obj.setProperty(runtime, "x", x); obj.setProperty(runtime, "y", y); obj.setProperty(runtime, "width", width); obj.setProperty(runtime, "height", height);
    return obj;
};

facebook::jsi::Object SKRNMLKitMLKFaceLandmark::toJSI(facebook::jsi::Runtime &runtime) {
    facebook::jsi::Object obj = facebook::jsi::Object(runtime);
    obj.setProperty(runtime, "type", jsi::String::createFromUtf8(runtime, type));
    obj.setProperty(runtime, "position", position.toJSI(runtime));
    return obj;
}
facebook::jsi::Object SKRNMLKitMLKFacePoint::toJSI(facebook::jsi::Runtime &runtime) {
    facebook::jsi::Object obj = facebook::jsi::Object(runtime);
    obj.setProperty(runtime, "x", x); obj.setProperty(runtime, "y", y);
    return obj;
}
facebook::jsi::Object SKRNMLKitMLKFaceContour::toJSI(facebook::jsi::Runtime &runtime) {
    facebook::jsi::Object obj = facebook::jsi::Object(runtime);
    obj.setProperty(runtime, "type", jsi::String::createFromUtf8(runtime, type));
    size_t pLen = points.size();
    jsi::Array arr = jsi::Array(runtime, pLen);
    for(size_t i = 0; i < pLen; i++) {
        arr.setValueAtIndex(runtime, i, points[i].toJSI(runtime));
    }
    obj.setProperty(runtime, "points", arr);
    return obj;
}
}

static bool objectPropertyIsEqualToString(jsi::Runtime &runtime, jsi::Object &obj, std::string propName, std::string compare) {
    jsi::Value v = obj.getProperty(runtime, propName.c_str());
    bool isStr = v.isString();
    if(!isStr) return false;
    auto str = v.toString(runtime);
    return str.utf8(runtime) == compare;
}

void SKRNMLKitFaceDetection::install(
                                     facebook::jsi::Runtime &jsiRuntime,
                                     std::function<std::shared_ptr<SKRNMLKitFaceDetector>
                                     (facebook::jsi::Runtime& _runtime,
                                      SKRNMLKitFaceDetector::PerformanceMode _performanceMode,
                                      SKRNMLKitFaceDetector::LandmarkMode _landmarkMode,
                                      SKRNMLKitFaceDetector::ContourMode _contourMode,
                                      float _minFaceSize,
                                      bool _trackingEnabled
                                      )> detectorConstructor
                                     ) {

    auto poseDetectorConstructorFunction =
    jsi::Function::createFromHostFunction
    (
     jsiRuntime,
     PropNameID::forAscii(jsiRuntime, "SKRNMLKitFaceDetectionNewFaceDetector"),
     0,
     //                                          [&, invoker](Runtime &runtime, const Value &thisValue, const Value *arguments,
     [&, detectorConstructor](Runtime &runtime, const Value &thisValue, const Value *arguments,
                              size_t count) -> Value
     {
         SKRNMLKitFaceDetector::PerformanceMode performanceMode = SKRNMLKitFaceDetector::PerformanceModeFast;
         SKRNMLKitFaceDetector::LandmarkMode landmarkMode = SKRNMLKitFaceDetector::LandmarkModeNone;
         SKRNMLKitFaceDetector::ContourMode contourMode = SKRNMLKitFaceDetector::ContourModeNone;
         float minFaceSize = 0.1;
         bool trackingEnabled = false;

         if(count > 0) {
             jsi::Object obj = arguments[0].asObject(runtime);
             performanceMode = objectPropertyIsEqualToString(runtime, obj, "performanceMode", "accurate")  ? SKRNMLKitFaceDetector::PerformanceModeAccurate : SKRNMLKitFaceDetector::PerformanceModeFast;
             landmarkMode = objectPropertyIsEqualToString(runtime, obj, "landmarkMode", "all")
             ? SKRNMLKitFaceDetector::LandmarkModeAll : SKRNMLKitFaceDetector::LandmarkModeNone;
             contourMode = objectPropertyIsEqualToString(runtime, obj, "contourMode", "all")
             ? SKRNMLKitFaceDetector::ContourModeAll : SKRNMLKitFaceDetector::ContourModeNone;
             jsi::Value minFaceVal = obj.getProperty(runtime, "minFaceSize");
             if(minFaceVal.isNumber()) {
                 minFaceSize = minFaceVal.getNumber();
             }
             jsi::Value trackingEnabledVal = obj.getProperty(runtime, "trackingEnabled");
             if(trackingEnabledVal.isBool()) {
                 trackingEnabled = trackingEnabledVal.getBool();
             }
         }
         std::shared_ptr<SKRNMLKitFaceDetector> obj = detectorConstructor(runtime, performanceMode, landmarkMode, contourMode, minFaceSize, trackingEnabled);
         jsi::Object object = jsi::Object::createFromHostObject(runtime, obj);
         return object;
     });
    jsiRuntime.global().setProperty(jsiRuntime, "SKRNMLKitFaceDetectionNewFaceDetector",
                                    std::move(poseDetectorConstructorFunction));
}
//void install(facebook::jsi::Runtime &jsiRuntime, std::shared_ptr<facebook::react::CallInvoker> invoker);
void SKRNMLKitFaceDetection::cleanup(facebook::jsi::Runtime &jsiRuntime) {

}
