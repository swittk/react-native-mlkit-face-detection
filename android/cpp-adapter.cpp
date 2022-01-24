#include <jni.h>
#include "react-native-mlkit-face-detection.h"
#include "SKRNMLKitAndroidFaceDetectionCPP.h"

using namespace SKRNMLKitFaceDetection;
extern "C"
JNIEXPORT jint JNICALL
Java_com_reactnativemlkitfacedetection_MlkitFaceDetectionModule_nativeMultiply(JNIEnv *env, jclass type, jint a, jint b) {
    return SKRNMLKitFaceDetection::multiply(a, b);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_reactnativemlkitfacedetection_MlkitFaceDetectionModule_initialize(JNIEnv *env,
                                                                           jclass clazz,
                                                                           jlong jsi_runtime_pointer) {
    JavaVM *jvm;
    env->GetJavaVM(&jvm);
    printf("javaVM was %d", jvm);
    SKRNMLKitFaceDetection::install(
            *reinterpret_cast<facebook::jsi::Runtime *>(jsi_runtime_pointer),
            [&, jvm](facebook::jsi::Runtime& _runtime,
               SKRNMLKitFaceDetector::PerformanceMode _performanceMode,
               SKRNMLKitFaceDetector::LandmarkMode _landmarkMode,
               SKRNMLKitFaceDetector::ContourMode _contourMode,
               float _minFaceSize,
               bool _trackingEnabled) -> std::shared_ptr<SKRNMLKitFaceDetector> {
                std::shared_ptr<SKRNMLKitAndroidFaceDetector>ret =  std::make_shared<SKRNMLKitAndroidFaceDetector>(jvm, _performanceMode, _landmarkMode, _contourMode, _minFaceSize, _trackingEnabled);
                return ret;
            }
    );

    // TODO: ADD VISIONCAMERA STUFF
}
extern "C"
JNIEXPORT void JNICALL
Java_com_reactnativemlkitfacedetection_MlkitFaceDetectionModule_cleanup(JNIEnv *env, jclass clazz,
                                                                        jlong jsi_runtime_pointer) {
    // TODO: ADD VISIONCAMERA STUFF
}
