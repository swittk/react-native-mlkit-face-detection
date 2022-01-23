#include <react-native-mlkit-face-detection.h>
#include <jni.h>

#ifndef ANDROID_SKANDROIDMLKITNATIVEVIDEOCPP_H
#define ANDROID_SKANDROIDMLKITNATIVEVIDEOCPP_H

#ifndef HAS_SKRN_NATIVE_VIDEO
#if __has_include("react-native-native-video.h")
#define HAS_SKRN_NATIVE_VIDEO 1
#include "react-native-native-video.h"
#endif
#endif

namespace SKRNMLKitFaceDetection {
    class JavaInteger {
    public:
        static jclass javaClass;
        static jmethodID m_value;
        static void initializeJNI(JNIEnv *env);
        static int value(JNIEnv *env, jobject obj);
    };
    class JavaFloat {
    public:
        static jclass javaClass;
        static jmethodID m_value;
        static void initializeJNI(JNIEnv *env);
        static float value(JNIEnv *env, jobject obj);
    };
    class JavaList {
    public:
        static jclass java_util_List;
        static jmethodID java_util_List_;
        static jmethodID java_util_List_size;
        static jmethodID java_util_List_get;
        static jmethodID java_util_List_add;
        static void initializeJNI(JNIEnv *env);
        static std::vector<jobject> toVector(JNIEnv *env, jobject arrayList);
    };

    class AndroidJavaRect {
    public:
        // For convenience doing JNI bridge stuff
        static jclass javaClass;
        static jmethodID m_width;
        static jmethodID m_height;
        static jfieldID f_top;
        static jfieldID f_left;
        static void initializeJNI(JNIEnv *env);
        static SKRNMLKitMLKFaceRect toSKRNMLKitMLKFaceRect(JNIEnv *env, jobject rect);
    };

    class AndroidJavaPointF {
    public:
        // For convenience doing JNI bridge stuff
        static jclass javaClass;
        static jfieldID f_x;
        static jfieldID f_y;
        static float x(JNIEnv *env, jobject point);
        static float y(JNIEnv *env, jobject point);
        static void initializeJNI(JNIEnv *env);
    };

    class MLKitJavaFaceLandmark {
    public:
        // For convenience doing JNI bridge stuff
        static jclass javaClass;
        static jmethodID m_getLandmarkType; // returns int
        static jmethodID m_getPosition; // returns PointF
        static std::map<std::string, int> mapLandmarkCrossToNative;
        static std::map<int, std::string> mapLandmarkNativeToCross;

        static std::string getLandmarkTypeString(JNIEnv *env, jobject obj);
        static SKRNMLKitMLKFacePoint getPosition(JNIEnv *env, jobject obj);
        static void initializeJNI(JNIEnv *env);
    };
    class MLKitJavaFaceContour {
    public:
        // For convenience doing JNI bridge stuff
        static jclass javaClass;
        static jmethodID m_getFaceContourType; // returns int
        static jmethodID m_getPoints; // returns list of PointF
        static std::map<std::string, int> mapContourCrossToNative;
        static std::map<int, std::string> mapContourNativeToCross;

        static std::string getContourTypeString(JNIEnv *env, jobject obj);
        static std::vector<SKRNMLKitMLKFacePoint> getPoints(JNIEnv *env, jobject obj);
        static void initializeJNI(JNIEnv *env);
    };


    class SKRNMLKitAndroidMLKFace : public SKRNMLKitMLKFace {
    public:
        // For convenience doing JNI bridge stuff
        static jclass javaClass;
        static std::map<std::string, jmethodID> nativeMethodIDs;
        static void initializeJNI(JNIEnv *env);
        JavaVM *jvm;
        JNIEnv *getJNIEnv() {
            JNIEnv *env;
            jvm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6);
            return env;
        }
        jobject face;
        SKRNMLKitAndroidMLKFace(JavaVM *_vm, jobject faceObject);
        ~SKRNMLKitAndroidMLKFace();

        virtual SKRNMLKitMLKFaceRect frame();
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

        // Native method to get dict
        jobject createNativeDictionary();
    };

    class SKRNMLKitAndroidFaceDetector : public SKRNMLKitFaceDetector {
    public:
        JavaVM *jvm;
        JNIEnv *getJNIEnv() {
            JNIEnv *env;
            jvm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6);
            return env;
        }

        // For convenience doing JNI bridge stuff
        static jclass javaClass;
        static jmethodID constructorID;
        static std::map<std::string, jmethodID> nativeMethodIDs;
        static void initializeJNI(JNIEnv *env);
        // Constants from MLKit Face Options (populated after initializeJNI() is called)
        static int kLandmarkModeNone;
        static int kLandmarkModeAll;
        static int kContourModeNone;
        static int kContourModeAll;
        static int kClassificationModeNone;
        static int kClassificationModeAll;
        static int kPerformanceModeFast;
        static int kPerformanceModeAccurate;

        jobject faceDetector;

        SKRNMLKitAndroidFaceDetector(
                JavaVM *_vm,
                PerformanceMode _performanceMode = PerformanceModeFast,
                LandmarkMode _landmarkMode = LandmarkModeNone,
                ContourMode _contourMode = ContourModeNone,
                float _minFaceSize = 0.1,
                bool _trackingEnabled = false);
        ~SKRNMLKitAndroidFaceDetector();
#ifdef HAS_SKRN_NATIVE_VIDEO
        virtual std::vector<std::shared_ptr<SKRNMLKitMLKFace>> process(std::shared_ptr<SKRNNativeVideo::SKNativeFrameWrapper>);
#endif
    };
}

extern "C"
jint JNI_OnLoad(JavaVM *vm, void *reserved);

#endif // ANDROID_SKANDROIDMLKITNATIVEVIDEOCPP_H
