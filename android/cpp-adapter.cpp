#include <jni.h>
#include "react-native-mlkit-face-detection.h"

extern "C"
JNIEXPORT jint JNICALL
Java_com_reactnativemlkitfacedetection_MlkitFaceDetectionModule_nativeMultiply(JNIEnv *env, jclass type, jint a, jint b) {
    return SKRNMLKitFaceDetection::multiply(a, b);
}
