#include <SKRNMLKitAndroidFaceDetectionCPP.h>
#if HAS_SKRN_NATIVE_VIDEO
#include "SKAndroidNativeVideoCPP.h"
#include "react-native-native-video.h"
#endif
using namespace SKRNMLKitFaceDetection;

//SKRNMLKitMLKFaceRect SKRNMLKitAndroidMLKFace::frame() {
//    return (SKRNMLKitMLKFaceRect) {
//            face.frame.origin.x, face.frame.origin.y, face.frame.size.width,
//            face.frame.size.height};
//};
#pragma mark - Face Object
jclass SKRNMLKitAndroidMLKFace::javaClass;
std::map<std::string, jmethodID> SKRNMLKitAndroidMLKFace::nativeMethodIDs;// = std::map<std::string, jmethodID>();
SKRNMLKitAndroidMLKFace::SKRNMLKitAndroidMLKFace(JavaVM *_vm, jobject faceObject) : SKRNMLKitMLKFace(), jvm(_vm) {
    face = getJNIEnv()->NewGlobalRef(faceObject);
}

SKRNMLKitAndroidMLKFace::~SKRNMLKitAndroidMLKFace() {
    JNIEnv *env = getJNIEnv();
    env->DeleteGlobalRef(face);
}

SKRNMLKitMLKFaceRect SKRNMLKitAndroidMLKFace::frame() {
    jobject jRect = getJNIEnv()->CallObjectMethod(face, SKRNMLKitAndroidMLKFace::nativeMethodIDs["getBoundingBox"]);
    return AndroidJavaRect::toSKRNMLKitMLKFaceRect(getJNIEnv(), jRect);
}
std::vector<std::shared_ptr<SKRNMLKitMLKFaceLandmark>> SKRNMLKitAndroidMLKFace::landmarks() {
    JNIEnv *env = getJNIEnv();
    jobject landmarksList = env->CallObjectMethod(face, SKRNMLKitAndroidMLKFace::nativeMethodIDs["getAllLandmarks"]);
    std::vector<jobject> list = JavaList::toVector(env, landmarksList);
    std::vector<std::shared_ptr<SKRNMLKitMLKFaceLandmark>> ret;
    for (jobject landmark : list) {
        ret.push_back(
                std::make_shared<SKRNMLKitMLKFaceLandmark>
                        (
                                MLKitJavaFaceLandmark::getLandmarkTypeString(env, landmark),
                                MLKitJavaFaceLandmark::getPosition(env, landmark)
                        )
        );
    }
    return ret;
}
std::vector<std::shared_ptr<SKRNMLKitMLKFaceContour>> SKRNMLKitAndroidMLKFace::contours() {
    JNIEnv *env = getJNIEnv();
    jobject _list = env->CallObjectMethod(face, SKRNMLKitAndroidMLKFace::nativeMethodIDs["getAllContours"]);
    std::vector<jobject> list = JavaList::toVector(env, _list);
    std::vector<std::shared_ptr<SKRNMLKitMLKFaceContour>> ret;
    for (jobject obj : list) {
        ret.push_back(
                std::make_shared<SKRNMLKitMLKFaceContour>
                        (
                                MLKitJavaFaceContour::getContourTypeString(env, obj),
                                MLKitJavaFaceContour::getPoints(env, obj)
                        )
        );
    }
    return ret;
}
bool SKRNMLKitAndroidMLKFace::hasTrackingID() {
    jobject tid = getJNIEnv()->CallObjectMethod(face, SKRNMLKitAndroidMLKFace::nativeMethodIDs["getTrackingID"]);
    if(tid == nullptr) {return false;}
    return true;
}
size_t SKRNMLKitAndroidMLKFace::trackingID() {
    jobject tid = getJNIEnv()->CallObjectMethod(face, SKRNMLKitAndroidMLKFace::nativeMethodIDs["getTrackingID"]);
    return JavaInteger::value(getJNIEnv(), tid);
}
bool SKRNMLKitAndroidMLKFace::hasHeadEulerAngleX() {
    jobject tid = getJNIEnv()->CallObjectMethod(face, SKRNMLKitAndroidMLKFace::nativeMethodIDs["getHeadEulerAngleX"]);
    if(tid == nullptr) {return false;}
    return true;
}
double SKRNMLKitAndroidMLKFace::headEulerAngleX() {
    jobject tid = getJNIEnv()->CallObjectMethod(face, SKRNMLKitAndroidMLKFace::nativeMethodIDs["getHeadEulerAngleX"]);
    return JavaFloat::value(getJNIEnv(), tid);
}
bool SKRNMLKitAndroidMLKFace::hasHeadEulerAngleY() {
    jobject tid = getJNIEnv()->CallObjectMethod(face, SKRNMLKitAndroidMLKFace::nativeMethodIDs["getHeadEulerAngleY"]);
    if(tid == nullptr) {return false;}
    return true;
}
double SKRNMLKitAndroidMLKFace::headEulerAngleY() {
    jobject tid = getJNIEnv()->CallObjectMethod(face, SKRNMLKitAndroidMLKFace::nativeMethodIDs["getHeadEulerAngleY"]);
    return JavaFloat::value(getJNIEnv(), tid);
}
bool SKRNMLKitAndroidMLKFace::hasHeadEulerAngleZ() {
    jobject tid = getJNIEnv()->CallObjectMethod(face, SKRNMLKitAndroidMLKFace::nativeMethodIDs["getHeadEulerAngleZ"]);
    if(tid == nullptr) {return false;}
    return true;
}
double SKRNMLKitAndroidMLKFace::headEulerAngleZ() {
    jobject tid = getJNIEnv()->CallObjectMethod(face, SKRNMLKitAndroidMLKFace::nativeMethodIDs["getHeadEulerAngleZ"]);
    return JavaFloat::value(getJNIEnv(), tid);
}

bool SKRNMLKitAndroidMLKFace::hasSmilingProbability() {
    jobject tid = getJNIEnv()->CallObjectMethod(face, SKRNMLKitAndroidMLKFace::nativeMethodIDs["getSmilingProbability"]);
    if(tid == nullptr) {return false;}
    return true;
}
double SKRNMLKitAndroidMLKFace::smilingProbability() {
    jobject tid = getJNIEnv()->CallObjectMethod(face, SKRNMLKitAndroidMLKFace::nativeMethodIDs["getSmilingProbability"]);
    return JavaFloat::value(getJNIEnv(), tid);
}

bool SKRNMLKitAndroidMLKFace::hasLeftEyeOpenProbability() {
    jobject tid = getJNIEnv()->CallObjectMethod(face, SKRNMLKitAndroidMLKFace::nativeMethodIDs["getLeftEyeOpenProbability"]);
    if(tid == nullptr) {return false;}
    return true;
}

double SKRNMLKitAndroidMLKFace::leftEyeOpenProbability() {
    jobject tid = getJNIEnv()->CallObjectMethod(face, SKRNMLKitAndroidMLKFace::nativeMethodIDs["getLeftEyeOpenProbability"]);
    return JavaFloat::value(getJNIEnv(), tid);
}
bool SKRNMLKitAndroidMLKFace::hasRightEyeOpenProbability() {
    jobject tid = getJNIEnv()->CallObjectMethod(face, SKRNMLKitAndroidMLKFace::nativeMethodIDs["getRightEyeOpenProbability"]);
    if(tid == nullptr) {return false;}
    return true;
}
double SKRNMLKitAndroidMLKFace::rightEyeOpenProbability() {
    jobject tid = getJNIEnv()->CallObjectMethod(face, SKRNMLKitAndroidMLKFace::nativeMethodIDs["getRightEyeOpenProbability"]);
    return JavaFloat::value(getJNIEnv(), tid);
}
std::shared_ptr<SKRNMLKitMLKFaceLandmark> SKRNMLKitAndroidMLKFace::landmarkOfType(std::string landmarkType) {
    JNIEnv *env = getJNIEnv();
    int _map = MLKitJavaFaceLandmark::mapLandmarkCrossToNative[landmarkType];
    jobject l = env->CallObjectMethod(face, SKRNMLKitAndroidMLKFace::nativeMethodIDs["getLandmark"], _map);
    return std::make_shared<SKRNMLKitMLKFaceLandmark>(
            MLKitJavaFaceLandmark::getLandmarkTypeString(env, l),
            MLKitJavaFaceLandmark::getPosition(env, l)
            );
}

std::shared_ptr<SKRNMLKitMLKFaceContour> SKRNMLKitAndroidMLKFace::contourOfType(std::string contourType) {
    JNIEnv *env = getJNIEnv();
    int _map = MLKitJavaFaceContour::mapContourCrossToNative[contourType];
    jobject c = env->CallObjectMethod(face, SKRNMLKitAndroidMLKFace::nativeMethodIDs["getContour"], _map);
    return std::make_shared<SKRNMLKitMLKFaceContour>(
            MLKitJavaFaceContour::getContourTypeString(env, c),
            MLKitJavaFaceContour::getPoints(env, c)
    );
}



#pragma mark - Face detector

jclass SKRNMLKitAndroidFaceDetector::javaClass;
jmethodID SKRNMLKitAndroidFaceDetector::constructorID;
std::map<std::string, jmethodID> SKRNMLKitAndroidFaceDetector::nativeMethodIDs;
int SKRNMLKitAndroidFaceDetector::kLandmarkModeNone;
int SKRNMLKitAndroidFaceDetector::kLandmarkModeAll;
int SKRNMLKitAndroidFaceDetector::kContourModeNone;
int SKRNMLKitAndroidFaceDetector::kContourModeAll;
int SKRNMLKitAndroidFaceDetector::kClassificationModeNone;
int SKRNMLKitAndroidFaceDetector::kClassificationModeAll;
int SKRNMLKitAndroidFaceDetector::kPerformanceModeFast;
int SKRNMLKitAndroidFaceDetector::kPerformanceModeAccurate;
SKRNMLKitAndroidFaceDetector::SKRNMLKitAndroidFaceDetector(
        JavaVM *_vm,
PerformanceMode _performanceMode,
        LandmarkMode _landmarkMode,
        ContourMode _contourMode,
float _minFaceSize,
bool _trackingEnabled) : SKRNMLKitFaceDetector(_performanceMode, _landmarkMode, _contourMode, _minFaceSize, _trackingEnabled),
jvm(_vm)
{
    JNIEnv *env = getJNIEnv();
    int perf = performanceMode == PerformanceModeAccurate ? kPerformanceModeAccurate : kPerformanceModeFast;
    int lm = landmarkMode == LandmarkModeAll ? kLandmarkModeAll : kLandmarkModeNone;
    int cnt = contourMode == ContourModeAll ? kContourModeAll : kContourModeNone;
    faceDetector = env->NewGlobalRef(env->NewObject(javaClass, constructorID, perf, lm, cnt, minFaceSize, isTrackingEnabled));
}
SKRNMLKitAndroidFaceDetector::~SKRNMLKitAndroidFaceDetector() {
    JNIEnv *env = getJNIEnv();
    env->DeleteGlobalRef(faceDetector);
}

#if HAS_SKRN_NATIVE_VIDEO
std::vector<std::shared_ptr<SKRNMLKitMLKFace>> SKRNMLKitAndroidFaceDetector::process
(std::shared_ptr<SKRNNativeVideo::SKNativeFrameWrapper> _frameWrapper) {
    std::shared_ptr<SKRNNativeVideo::SKAndroidNativeFrameWrapper> frameWrapper =
            std::dynamic_pointer_cast<SKRNNativeVideo::SKAndroidNativeFrameWrapper>(_frameWrapper);
    jobject bitmap = frameWrapper->bitmap;
    JNIEnv *env = getJNIEnv();
    jobject listRet = env->CallObjectMethod(faceDetector, nativeMethodIDs["processBitmap"], bitmap);
    std::vector<jobject> vecRet = JavaList::toVector(env, listRet);
    std::vector<std::shared_ptr<SKRNMLKitMLKFace>> ret;
    for(jobject obj : vecRet) {
        ret.push_back(std::make_shared<SKRNMLKitAndroidMLKFace>(jvm, obj));
//        ret.push_back(std::make_shared<SKRNMLKitMLKFace>())
    }
    return ret;
}
#endif



#pragma mark - Convenience class implementations

#pragma mark - Initialization Methods

extern "C"
jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if(vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    JavaInteger::initializeJNI(env);
    JavaFloat::initializeJNI(env);
    JavaList::initializeJNI(env);
    AndroidJavaRect::initializeJNI(env);
    AndroidJavaPointF::initializeJNI(env);
    SKRNMLKitAndroidMLKFace::initializeJNI(env);
    SKRNMLKitAndroidFaceDetector::initializeJNI(env);
    return JNI_VERSION_1_6;
}


// Static variables need to be defined too..
jclass JavaInteger::javaClass;
jmethodID JavaInteger::m_value;
void JavaInteger::initializeJNI(JNIEnv *env) {
    jclass _javaClass = static_cast<jclass>(env->NewGlobalRef(env->FindClass("java/lang/Integer")));
    javaClass = _javaClass;
    m_value = env->GetMethodID(_javaClass, "intValue", "()I");
}
int JavaInteger::value(JNIEnv *env, jobject obj) {
    if(obj == nullptr) return 0;
    return env->CallIntMethod(obj, m_value);
}
jclass JavaFloat::javaClass;
jmethodID JavaFloat::m_value;
void JavaFloat::initializeJNI(JNIEnv *env) {
    jclass _javaClass = static_cast<jclass>(env->NewGlobalRef(env->FindClass("java/lang/Float")));
    javaClass = _javaClass;
    m_value = env->GetMethodID(_javaClass, "floatValue", "()F");
}
float JavaFloat::value(JNIEnv *env, jobject obj) {
    if(obj == nullptr) return 0;
    return env->CallFloatMethod(obj, m_value);
}

jclass JavaList::java_util_List;
jmethodID JavaList::java_util_List_;
 jmethodID JavaList::java_util_List_size;
 jmethodID JavaList::java_util_List_get;
 jmethodID JavaList::java_util_List_add;
void JavaList::initializeJNI(JNIEnv *env) {
    java_util_List      = static_cast<jclass>(env->NewGlobalRef(env->FindClass("java/util/List")));
    java_util_List_     = env->GetMethodID(java_util_List, "<init>", "()V");
    java_util_List_size = env->GetMethodID (java_util_List, "size", "()I");
    java_util_List_get  = env->GetMethodID(java_util_List, "get", "(I)Ljava/lang/Object;");
    java_util_List_add  = env->GetMethodID(java_util_List, "add", "(Ljava/lang/Object;)Z");
}
std::vector<jobject> JavaList::toVector(JNIEnv *env, jobject arrayList) {
    jint len = env->CallIntMethod(arrayList, java_util_List_size);
    std::vector<jobject> result;
    result.reserve(len);
    for (jint i = 0; i < len; i++) {
        jobject element = static_cast<jobject>(env->CallObjectMethod(arrayList, java_util_List_get,
                                                                     i));
        result.push_back(element);
    }
    return result;
}

 jclass AndroidJavaRect::javaClass;
 jmethodID AndroidJavaRect::m_width;
 jmethodID AndroidJavaRect::m_height;
 jfieldID AndroidJavaRect::f_top;
 jfieldID AndroidJavaRect::f_left;
void AndroidJavaRect::initializeJNI(JNIEnv *env) {
    jclass _javaClass = static_cast<jclass>(env->NewGlobalRef(env->FindClass("android/graphics/Rect")));
    javaClass = _javaClass;
    f_left = env->GetFieldID(_javaClass, "left", "I");
    f_top = env->GetFieldID(_javaClass, "top", "I");
    m_width = env->GetMethodID(_javaClass, "width", "()I");
    m_height = env->GetMethodID(_javaClass, "height", "()I");
}
 jclass AndroidJavaPointF::javaClass;
 jfieldID AndroidJavaPointF::f_x;
 jfieldID AndroidJavaPointF::f_y;
void AndroidJavaPointF::initializeJNI(JNIEnv *env) {
    jclass _cls = static_cast<jclass>(env->NewGlobalRef(env->FindClass("android/graphics/PointF")));
    javaClass = _cls;
    f_x = env->GetFieldID(_cls, "x", "F");
    f_y = env->GetFieldID(_cls, "y", "F");
}
float AndroidJavaPointF::x(JNIEnv *env, jobject point) {
    return env->GetFloatField(point, f_x);
}
float AndroidJavaPointF::y(JNIEnv *env, jobject point) {
    return env->GetFloatField(point, f_y);
}
SKRNMLKitMLKFaceRect AndroidJavaRect::toSKRNMLKitMLKFaceRect(JNIEnv *env, jobject javaRect) {
    int left = env->GetIntField(javaRect, f_left);
    int top = env->GetIntField(javaRect, f_top);
    int width = env->CallIntMethod(javaRect, m_width);
    int height = env->CallIntMethod(javaRect, m_height);
    return (SKRNMLKitMLKFaceRect) {(double) left, (double) top, (double) width, (double) height};
}


void SKRNMLKitAndroidFaceDetector::initializeJNI(JNIEnv *env) {
    // Initialize face detection constants from options
    jclass a = env->FindClass("com/google/mlkit/vision/face/FaceDetectorOptions");
    kLandmarkModeNone = env->GetStaticIntField(a, env->GetStaticFieldID(a, "LANDMARK_MODE_NONE", "I"));
    kLandmarkModeAll = env->GetStaticIntField(a, env->GetStaticFieldID(a, "LANDMARK_MODE_ALL", "I"));
    kContourModeAll = env->GetStaticIntField(a, env->GetStaticFieldID(a, "CONTOUR_MODE_ALL", "I"));
    kContourModeNone = env->GetStaticIntField(a, env->GetStaticFieldID(a, "CONTOUR_MODE_NONE", "I"));
    kClassificationModeAll = env->GetStaticIntField(a, env->GetStaticFieldID(a, "CLASSIFICATION_MODE_ALL", "I"));
    kClassificationModeNone = env->GetStaticIntField(a, env->GetStaticFieldID(a, "CLASSIFICATION_MODE_NONE", "I"));
    kPerformanceModeAccurate = env->GetStaticIntField(a, env->GetStaticFieldID(a, "PERFORMANCE_MODE_ACCURATE", "I"));
    kPerformanceModeFast = env->GetStaticIntField(a, env->GetStaticFieldID(a, "PERFORMANCE_MODE_FAST", "I"));

    jclass _cls = static_cast<jclass>(env->NewGlobalRef(env->FindClass("com/reactnativemlkitfacedetection/SKRNMLKitAndroidFaceDetectionJava")));
    javaClass = _cls;
    jmethodID ctor = env->GetMethodID(_cls, "<init>",
                                      "(IIIFZ)V");
    constructorID = ctor;
//    jobject d = env->NewObject(_cls, ctor, 1, 1, 1, 0.0f, false); // just checking
    jmethodID processBitmap = env->GetMethodID(_cls, "processBitmap", "(Landroid/graphics/Bitmap;I)Ljava/util/List;");
    nativeMethodIDs["processBitmap"] = processBitmap;
    jmethodID processImageProxy = env->GetMethodID(_cls, "processImageProxy", "(Ljava/lang/Object;)Ljava/util/List;");
    nativeMethodIDs["processImageProxy"] = processImageProxy;
}

void SKRNMLKitAndroidMLKFace::initializeJNI(JNIEnv *env) {
    /*
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
 */
    jclass _faceClass = static_cast<jclass>(env->NewGlobalRef(
            env->FindClass("com/google/mlkit/vision/face/Face")));
    javaClass = _faceClass;

    // Initialize method IDs
    jmethodID getBoundingBox = env->GetMethodID(_faceClass, "getBoundingBox",
                                          "()Landroid/graphics/Rect;");
    nativeMethodIDs.insert(std::pair<std::string, jmethodID>("getBoundingBox", getBoundingBox));
    jmethodID _getAllLandmarks = env->GetMethodID(_faceClass, "getAllLandmarks", "()Ljava/util/List;");
    nativeMethodIDs.insert(std::pair<std::string, jmethodID>("getAllLandmarks", _getAllLandmarks));
    jmethodID _getLandmark = env->GetMethodID(_faceClass, "getLandmark",
                                              "(I)Lcom/google/mlkit/vision/face/FaceLandmark;");
    nativeMethodIDs.insert(std::pair<std::string, jmethodID>("getLandmark", _getLandmark));
    jmethodID _getAllContours = env->GetMethodID(_faceClass, "getAllContours", "()Ljava/util/List;");
    nativeMethodIDs.insert(std::pair<std::string, jmethodID>("getAllContours", _getAllContours));
    jmethodID _getContour = env->GetMethodID(_faceClass, "getContour",
                                             "(I)Lcom/google/mlkit/vision/face/FaceContour;");
    nativeMethodIDs.insert(std::pair<std::string, jmethodID>("_getContour", _getContour));
    jmethodID _getTrackingID = env->GetMethodID(_faceClass, "getTrackingId",
                                                "()Ljava/lang/Integer;");
    nativeMethodIDs.insert(std::pair<std::string, jmethodID>("getTrackingID", _getTrackingID));
    jmethodID _getHeadEulerAngleX = env->GetMethodID(_faceClass, "getHeadEulerAngleX", "()F");
    nativeMethodIDs.insert(std::pair<std::string, jmethodID>("getHeadEulerAngleX", _getHeadEulerAngleX));
    jmethodID _getHeadEulerAngleY = env->GetMethodID(_faceClass, "getHeadEulerAngleY", "()F");
    nativeMethodIDs.insert(std::pair<std::string, jmethodID>("getHeadEulerAngleY", _getHeadEulerAngleY));
    jmethodID _getHeadEulerAngleZ = env->GetMethodID(_faceClass, "getHeadEulerAngleZ", "()F");
    nativeMethodIDs.insert(std::pair<std::string, jmethodID>("getHeadEulerAngleZ", _getHeadEulerAngleZ));
    jmethodID _getSmilingProbability = env->GetMethodID(_faceClass, "getSmilingProbability",
                                                        "()Ljava/lang/Float;");
    nativeMethodIDs.insert(std::pair<std::string, jmethodID>("getSmilingProbability", _getSmilingProbability));
    jmethodID _getLeftEyeOpenProbability = env->GetMethodID(_faceClass, "getLeftEyeOpenProbability",
                                                          "()Ljava/lang/Float;");
    nativeMethodIDs.insert(std::pair<std::string, jmethodID>("getLeftEyeOpenProbability", _getLeftEyeOpenProbability));
    jmethodID _getRightEyeOpenProbability = env->GetMethodID(_faceClass, "getRightEyeOpenProbability",
                                                          "()Ljava/lang/Float;");
    nativeMethodIDs.insert(std::pair<std::string, jmethodID>("getRightEyeOpenProbability", _getRightEyeOpenProbability));
}

jclass MLKitJavaFaceLandmark::javaClass;
jmethodID MLKitJavaFaceLandmark::m_getLandmarkType; // returns int
jmethodID MLKitJavaFaceLandmark::m_getPosition; // returns PointF
std::map<std::string, int> MLKitJavaFaceLandmark::mapLandmarkCrossToNative;
std::map<int, std::string> MLKitJavaFaceLandmark::mapLandmarkNativeToCross;
void MLKitJavaFaceLandmark::initializeJNI(JNIEnv *env) {
    jclass _cls = static_cast<jclass>(env->NewGlobalRef(
            env->FindClass("com/google/mlkit/vision/face/FaceLandmark")));
    m_getLandmarkType = env->GetMethodID(_cls, "getLandmarkType", "()I");
    m_getPosition = env->GetMethodID(_cls, "getPosition", "()Landroid/graphics/PointF;");

    int _MouthBottom = env->GetStaticIntField(_cls,
                                              env->GetStaticFieldID(_cls, "MOUTH_BOTTOM", "I"));
    mapLandmarkCrossToNative["MouthBottom"] = _MouthBottom;
    mapLandmarkNativeToCross[_MouthBottom] = "MouthBottom";

    int _MouthRight = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "MOUTH_RIGHT", "I"));
    mapLandmarkCrossToNative["MouthRight"] = _MouthRight;
    mapLandmarkNativeToCross[_MouthRight] = "MouthRight";

    int _MouthLeft = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "MOUTH_LEFT", "I"));
    mapLandmarkCrossToNative["MouthLeft"] = _MouthLeft;
    mapLandmarkNativeToCross[_MouthLeft] = "MouthLeft";

    int _RightEye = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "RIGHT_EYE", "I"));
    mapLandmarkCrossToNative["RightEye"] = _RightEye;
    mapLandmarkNativeToCross[_RightEye] = "RightEye";

    int _LeftEye = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "LEFT_EYE", "I"));
    mapLandmarkCrossToNative["LeftEye"] = _LeftEye;
    mapLandmarkNativeToCross[_LeftEye] = "LeftEye";

    int _RightEar = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "RIGHT_EAR", "I"));
    mapLandmarkCrossToNative["RightEar"] = _RightEar;
    mapLandmarkNativeToCross[_RightEar] = "RightEar";

    int _LeftEar = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "LEFT_EAR", "I"));
    mapLandmarkCrossToNative["LeftEar"] = _LeftEar;
    mapLandmarkNativeToCross[_LeftEar] = "LeftEar";

    int _RightCheek = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "RIGHT_CHEEK", "I"));
    mapLandmarkCrossToNative["RightCheek"] = _RightCheek;
    mapLandmarkNativeToCross[_RightCheek] = "RightCheek";

    int _LeftCheek = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "LEFT_CHEEK", "I"));
    mapLandmarkCrossToNative["LeftCheek"] = _LeftCheek;
    mapLandmarkNativeToCross[_LeftCheek] = "LeftCheek";

    int _NoseBase = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "NOSE_BASE", "I"));
    mapLandmarkCrossToNative["NoseBase"] = _NoseBase;
    mapLandmarkNativeToCross[_NoseBase] = "NoseBase";
}
std::string MLKitJavaFaceLandmark::getLandmarkTypeString(JNIEnv *env, jobject obj) {
    int _type = env->CallIntMethod(obj, m_getLandmarkType);
    return mapLandmarkNativeToCross[_type];
}
SKRNMLKitMLKFacePoint MLKitJavaFaceLandmark::getPosition(JNIEnv *env, jobject obj) {
    jobject pos = env->CallObjectMethod(obj, m_getPosition);
    return SKRNMLKitMLKFacePoint((double)AndroidJavaPointF::x(env, pos), (double)AndroidJavaPointF::y(env, pos));
}
jclass MLKitJavaFaceContour::javaClass;
jmethodID MLKitJavaFaceContour::m_getFaceContourType; // returns int
jmethodID MLKitJavaFaceContour::m_getPoints; // returns list of PointF
std::map<std::string, int> MLKitJavaFaceContour::mapContourCrossToNative;
std::map<int, std::string> MLKitJavaFaceContour::mapContourNativeToCross;
void MLKitJavaFaceContour::initializeJNI(JNIEnv *env) {
    jclass _cls = static_cast<jclass>(env->NewGlobalRef(
            env->FindClass("com/google/mlkit/vision/face/FaceContour")));
    int _Face = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "FACE", "I"));
    mapContourCrossToNative["Face"] = _Face;
    mapContourNativeToCross[_Face] = "Face";

    int _LeftEyebrowTop = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "LEFT_EYEBROW_TOP", "I"));
    mapContourCrossToNative["LeftEyebrowTop"] = _LeftEyebrowTop;
    mapContourNativeToCross[_LeftEyebrowTop] = "LeftEyebrowTop";

    int _LeftEyebrowBottom = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "LEFT_EYEBROW_BOTTOM", "I"));
    mapContourCrossToNative["LeftEyebrowBottom"] = _LeftEyebrowBottom;
    mapContourNativeToCross[_LeftEyebrowBottom] = "LeftEyebrowBottom";

    int _RightEyebrowTop = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "RIGHT_EYEBROW_TOP", "I"));
    mapContourCrossToNative["RightEyebrowTop"] = _RightEyebrowTop;
    mapContourNativeToCross[_RightEyebrowTop] = "RightEyebrowTop";

    int _RightEyebrowBottom = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "RIGHT_EYEBROW_BOTTOM", "I"));
    mapContourCrossToNative["RightEyebrowBottom"] = _RightEyebrowBottom;
    mapContourNativeToCross[_RightEyebrowBottom] = "RightEyebrowBottom";

    int _LeftEye = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "LEFT_EYE", "I"));
    mapContourCrossToNative["LeftEye"] = _LeftEye;
    mapContourNativeToCross[_LeftEye] = "LeftEye";

    int _RightEye = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "RIGHT_EYE", "I"));
    mapContourCrossToNative["RightEye"] = _RightEye;
    mapContourNativeToCross[_RightEye] = "RightEye";

    int _UpperLipTop = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "UPPER_LIP_TOP", "I"));
    mapContourCrossToNative["UpperLipTop"] = _UpperLipTop;
    mapContourNativeToCross[_UpperLipTop] = "UpperLipTop";

    int _UpperLipBottom = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "UPPER_LIP_BOTTOM", "I"));
    mapContourCrossToNative["UpperLipBottom"] = _UpperLipBottom;
    mapContourNativeToCross[_UpperLipBottom] = "UpperLipBottom";

    int _LowerLipTop = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "LOWER_LIP_TOP", "I"));
    mapContourCrossToNative["LowerLipTop"] = _LowerLipTop;
    mapContourNativeToCross[_LowerLipTop] = "LowerLipTop";

    int _LowerLipBottom = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "LOWER_LIP_BOTTOM", "I"));
    mapContourCrossToNative["LowerLipBottom"] = _LowerLipBottom;
    mapContourNativeToCross[_LowerLipBottom] = "LowerLipBottom";

    int _NoseBridge = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "NOSE_BRIDGE", "I"));
    mapContourCrossToNative["NoseBridge"] = _NoseBridge;
    mapContourNativeToCross[_NoseBridge] = "NoseBridge";

    int _NoseBottom = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "NOSE_BOTTOM", "I"));
    mapContourCrossToNative["NoseBottom"] = _NoseBottom;
    mapContourNativeToCross[_NoseBottom] = "NoseBottom";

    int _LeftCheek = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "LEFT_CHEEK", "I"));
    mapContourCrossToNative["LeftCheek"] = _LeftCheek;
    mapContourNativeToCross[_LeftCheek] = "LeftCheek";

    int _RightCheek = env->GetStaticIntField(_cls, env->GetStaticFieldID(_cls, "RIGHT_CHEEK", "I"));
    mapContourCrossToNative["RightCheek"] = _RightCheek;
    mapContourNativeToCross[_RightCheek] = "RightCheek";
}
std::string MLKitJavaFaceContour::getContourTypeString(JNIEnv *env, jobject obj) {
    int _type = env->CallIntMethod(obj, m_getFaceContourType);
    return mapContourNativeToCross[_type];
}
std::vector<SKRNMLKitMLKFacePoint> MLKitJavaFaceContour::getPoints(JNIEnv *env, jobject obj) {
    jobject _list = env->CallObjectMethod(obj, m_getPoints);
    std::vector<jobject> list = JavaList::toVector(env, _list);
    std::vector<SKRNMLKitMLKFacePoint> ret;
    for(jobject p : list) {
        ret.push_back(SKRNMLKitMLKFacePoint(AndroidJavaPointF::x(env, p), AndroidJavaPointF::y(env, p)));
    }
    return ret;
}

