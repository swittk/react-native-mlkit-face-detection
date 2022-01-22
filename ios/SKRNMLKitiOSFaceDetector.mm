//
//  SKRNMLKitiOSFaceDetector.m
//  react-native-mlkit-face-detection
//
//  Created by Switt Kongdachalert on 19/1/2565 BE.
//

#import "SKRNMLKitiOSFaceDetector.h"
#ifdef HAS_SKRN_NATIVE_VIDEO
#import <react-native-native-video/SKiOSNativeVideoCPP.h>
using namespace SKRNNativeVideo;
#endif
extern NSDictionary *SKRNMLKitiOSFaceDetectionMappingFaceLandmarkToNative;
extern NSDictionary *SKRNMLKitiOSFaceDetectionMappingFaceContourToNative;
extern NSDictionary *SKRNMLKitiOSFaceDetectionMappingFaceLandmarkToCrossPlatform;
extern NSDictionary *SKRNMLKitiOSFaceDetectionMappingFaceContourToCrossPlatform;

using namespace SKRNMLKitFaceDetection;

#pragma mark - FaceDetector Class

static BOOL dictPropertyIsEqualToString(NSDictionary *dict, NSString *propKey, NSString *compareWith) {
    return [dict[propKey] isEqualToString:compareWith];
}

//SKRNMLKitiOSFaceDetector SKRNMLKitiOSFaceDetector::createWithNativeOptions(NSDictionary *obj) {
//    SKRNMLKitFaceDetector::PerformanceMode performanceMode = SKRNMLKitFaceDetector::PerformanceModeFast;
//    SKRNMLKitFaceDetector::LandmarkMode landmarkMode = SKRNMLKitFaceDetector::LandmarkModeNone;
//    SKRNMLKitFaceDetector::ContourMode contourMode = SKRNMLKitFaceDetector::ContourModeNone;
//    float minFaceSize = 0.1;
//    bool trackingEnabled = false;
//    if(obj && obj.count) {
//        performanceMode = dictPropertyIsEqualToString(obj, @"performanceMode", @"accurate")  ? SKRNMLKitFaceDetector::PerformanceModeAccurate : SKRNMLKitFaceDetector::PerformanceModeFast;
//        landmarkMode = dictPropertyIsEqualToString(obj, @"landmarkMode", @"all")
//        ? SKRNMLKitFaceDetector::LandmarkModeAll : SKRNMLKitFaceDetector::LandmarkModeNone;
//        contourMode = dictPropertyIsEqualToString(obj, @"contourMode", @"all")
//        ? SKRNMLKitFaceDetector::ContourModeAll : SKRNMLKitFaceDetector::ContourModeNone;
//        id minFaceVal = obj[@"minFaceSize"];
//        if([minFaceVal isKindOfClass:[NSNumber class]]) {
//            minFaceSize = [minFaceVal floatValue];
//        }
//        id trackingEnabledVal = obj[@"trackingEnabled"];
//        if([trackingEnabledVal isKindOfClass:[NSNumber class]]) {
//            trackingEnabled = [trackingEnabledVal boolValue];
//        }
//    }
//    return SKRNMLKitiOSFaceDetector(performanceMode, landmarkMode, contourMode, minFaceSize, trackingEnabled);
//}

SKRNMLKitiOSFaceDetector::SKRNMLKitiOSFaceDetector(PerformanceMode _performanceMode, LandmarkMode _landmarkMode, ContourMode _contourMode, float _minFaceSize, bool _trackingEnabled) : SKRNMLKitFaceDetector(_performanceMode, _landmarkMode, _contourMode, _minFaceSize, _trackingEnabled) {
    if(performanceMode == PerformanceModeFast
       ) {
        MLKFaceDetectorOptions *options = [MLKFaceDetectorOptions new];
        options.performanceMode = performanceMode == PerformanceModeFast ? MLKFaceDetectorPerformanceModeFast : MLKFaceDetectorPerformanceModeAccurate;
        options.landmarkMode = landmarkMode == LandmarkModeNone ? MLKFaceDetectorLandmarkModeNone : MLKFaceDetectorLandmarkModeAll;
        options.contourMode = contourMode == ContourModeNone ? MLKFaceDetectorContourModeNone : MLKFaceDetectorContourModeAll;
        options.minFaceSize = minFaceSize;
        options.trackingEnabled = isTrackingEnabled;
        faceDetector = [MLKFaceDetector faceDetectorWithOptions:options];
    }
}

SKRNMLKitiOSFaceDetector::~SKRNMLKitiOSFaceDetector() {
    faceDetector = nil;
}

std::vector<std::shared_ptr<SKRNMLKitMLKFace>> SKRNMLKitiOSFaceDetector::processNative(CMSampleBufferRef buffer, UIImageOrientation orientation) {
    MLKVisionImage *image = [[MLKVisionImage alloc] initWithBuffer:buffer];
    image.orientation = orientation;
    NSError *error;
    NSArray <MLKFace *>*faces = [faceDetector resultsInImage:image error:&error];
    if(error) {
        NSLog(@"Error processing frame %@", error);
    }
    //    NSLog(@"poses are %@", poses);
    if(![faces count]) {
        return std::vector<std::shared_ptr<SKRNMLKitMLKFace>>();
    }
    std::vector<std::shared_ptr<SKRNMLKitMLKFace>> ret;
    
    for(MLKFace *face in faces) {
        ret.push_back(std::make_shared<SKRNMLKitiOSMLKFace>(face));
    }
    return ret;
}


#ifdef HAS_SKRN_NATIVE_VIDEO
std::vector<std::shared_ptr<SKRNMLKitMLKFace>> SKRNMLKitiOSFaceDetector::process(std::shared_ptr<SKRNNativeVideo::SKNativeFrameWrapper> frameWrapper) {
    SKiOSNativeFrameWrapper *frame = (SKiOSNativeFrameWrapper *)(frameWrapper.get());
    return processNative(frame->buffer, frame->orientation);
};

#endif

#pragma mark - Face class
SKRNMLKitiOSMLKFace::SKRNMLKitiOSMLKFace(MLKFace *_face) {
    face = _face;
}

SKRNMLKitiOSMLKFace::~SKRNMLKitiOSMLKFace() {
    face = nil;
}
std::vector<std::shared_ptr<SKRNMLKitMLKFaceLandmark>> SKRNMLKitiOSMLKFace::landmarks() {
    std::vector<std::shared_ptr<SKRNMLKitMLKFaceLandmark>> ret;
    for(MLKFaceLandmark *l in face.landmarks) {
        ret.push_back(std::make_shared<SKRNMLKitMLKFaceLandmark>([l.type cStringUsingEncoding:NSUTF8StringEncoding], SKRNMLKitMLKFacePoint(l.position.x, l.position.y)));
    }
    return ret;
}
std::vector<std::shared_ptr<SKRNMLKitMLKFaceContour>> SKRNMLKitiOSMLKFace::contours() {
    std::vector<std::shared_ptr<SKRNMLKitMLKFaceContour>> ret;
    for(MLKFaceContour *c in face.contours) {
        std::vector<SKRNMLKitMLKFacePoint> pnts;
        for(MLKVisionPoint *p in c.points) {
            pnts.push_back(SKRNMLKitMLKFacePoint(p.x, p.y));
        }
        ret.push_back(std::make_shared<SKRNMLKitMLKFaceContour>([c.type cStringUsingEncoding:NSUTF8StringEncoding], pnts));
    }
    return ret;
}

bool SKRNMLKitiOSMLKFace::hasTrackingID() {return face.hasTrackingID;}
size_t SKRNMLKitiOSMLKFace::trackingID() {return face.trackingID;}
bool SKRNMLKitiOSMLKFace::hasHeadEulerAngleX() {return face.hasHeadEulerAngleX;}
double SKRNMLKitiOSMLKFace::headEulerAngleX() {return face.headEulerAngleX;}
bool SKRNMLKitiOSMLKFace::hasHeadEulerAngleY() {return face.hasHeadEulerAngleY;}
double SKRNMLKitiOSMLKFace::headEulerAngleY() {return face.headEulerAngleY;}
bool SKRNMLKitiOSMLKFace::hasHeadEulerAngleZ() {return face.hasHeadEulerAngleZ;}
double SKRNMLKitiOSMLKFace::headEulerAngleZ() {return face.headEulerAngleZ;}
bool SKRNMLKitiOSMLKFace::hasSmilingProbability() {return face.hasSmilingProbability;}
double SKRNMLKitiOSMLKFace::smilingProbability() {return face.smilingProbability;}
bool SKRNMLKitiOSMLKFace::hasLeftEyeOpenProbability() {return face.hasLeftEyeOpenProbability;}
double SKRNMLKitiOSMLKFace::leftEyeOpenProbability() {return face.leftEyeOpenProbability;}
bool SKRNMLKitiOSMLKFace::hasRightEyeOpenProbability() {return face.hasRightEyeOpenProbability;}
double SKRNMLKitiOSMLKFace::rightEyeOpenProbability() {return face.rightEyeOpenProbability;}
// Result is nullable
std::shared_ptr<SKRNMLKitMLKFaceLandmark> SKRNMLKitiOSMLKFace::landmarkOfType(std::string landmarkType) {
    MLKFaceLandmark *landmark = [face landmarkOfType:SKRNMLKitiOSFaceDetectionMappingFaceLandmarkToNative[[NSString stringWithUTF8String:landmarkType.c_str()]]];
    if(landmark) {
        return std::make_shared<SKRNMLKitMLKFaceLandmark>
        (
         [SKRNMLKitiOSFaceDetectionMappingFaceLandmarkToCrossPlatform[landmark.type] cStringUsingEncoding:NSUTF8StringEncoding],
         SKRNMLKitMLKFacePoint(landmark.position.x, landmark.position.y)
         );
    }
    return std::shared_ptr<SKRNMLKitMLKFaceLandmark>();
}
// Result is nullable.
std::shared_ptr<SKRNMLKitMLKFaceContour> SKRNMLKitiOSMLKFace::contourOfType(std::string contourType) {
    MLKFaceContour *contour = [face contourOfType:SKRNMLKitiOSFaceDetectionMappingFaceContourToNative[[NSString stringWithUTF8String:contourType.c_str()]]];
    if(contour) {
        std::vector<SKRNMLKitMLKFacePoint> ps;
        for(MLKVisionPoint *p in contour.points) {
            ps.push_back(SKRNMLKitMLKFacePoint(p.x, p.y));
        }
        return std::make_shared<SKRNMLKitMLKFaceContour>
        (
         [SKRNMLKitiOSFaceDetectionMappingFaceContourToCrossPlatform[contour.type] cStringUsingEncoding:NSUTF8StringEncoding],
         ps
         );
    }
    
    return std::shared_ptr<SKRNMLKitMLKFaceContour>();
};

/*
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
 */
static NSDictionary *dictForMLKFacePoint(SKRNMLKitMLKFacePoint pos) {
    return @{ @"x": @(pos.x), @"y": @(pos.y) };
}
static NSArray *arrayForMLKFacePoints(std::vector<SKRNMLKitMLKFacePoint> &ps) {
    NSMutableArray *points = [NSMutableArray new];
    for(auto p : ps) {
        [points addObject:dictForMLKFacePoint(p)];
    }
    return points;
}

NSDictionary *SKRNMLKitiOSMLKFace::createNativeDictionary() {
    NSMutableDictionary *ret = [NSMutableDictionary new];
    SKRNMLKitMLKFaceRect rect = frame();
    ret[@"frame"] = @{@"x":@(rect.x), @"y":@(rect.y), @"width":@(rect.width), @"height":@(rect.height)};
    NSMutableDictionary *landmarksDict = [NSMutableDictionary new];
    std::vector<std::shared_ptr<SKRNMLKitMLKFaceLandmark>> lms = landmarks();
    for(std::shared_ptr<SKRNMLKitMLKFaceLandmark> lm : lms) {
        NSString *typeStr = [NSString stringWithUTF8String:lm->type.c_str()];
        NSDictionary *landmark = @{
            @"type": typeStr,
            @"position": dictForMLKFacePoint(lm.get()->position)
        };
        landmarksDict[typeStr] = landmark;
    }
    ret[@"landmarks"] = landmarksDict;
    NSMutableDictionary *contoursDict = [NSMutableDictionary new];
    std::vector<std::shared_ptr<SKRNMLKitMLKFaceContour>> cnts = contours();
    for(std::shared_ptr<SKRNMLKitMLKFaceContour> cnt : cnts) {
        NSArray *facePoints = arrayForMLKFacePoints(cnt->points);
        NSString *typeStr = [NSString stringWithUTF8String:cnt->type.c_str()];
        contoursDict[typeStr] = @{
            @"type": typeStr,
            @"points": facePoints
        };
    }
    // Generate code from strings array
    ret[@"hasTrackingID"] = @(hasTrackingID());
    ret[@"trackingID"] = @(trackingID());
    ret[@"hasHeadEulerAngleX"] = @(hasHeadEulerAngleX());
    ret[@"headEulerAngleX"] = @(headEulerAngleX());
    ret[@"hasHeadEulerAngleY"] = @(hasHeadEulerAngleY());
    ret[@"headEulerAngleY"] = @(headEulerAngleY());
    ret[@"hasHeadEulerAngleZ"] = @(hasHeadEulerAngleZ());
    ret[@"headEulerAngleZ"] = @(headEulerAngleZ());
    ret[@"hasSmilingProbability"] = @(hasSmilingProbability());
    ret[@"smilingProbability"] = @(smilingProbability());
    ret[@"hasLeftEyeOpenProbability"] = @(hasLeftEyeOpenProbability());
    ret[@"leftEyeOpenProbability"] = @(leftEyeOpenProbability());
    ret[@"hasRightEyeOpenProbability"] = @(hasRightEyeOpenProbability());
    ret[@"rightEyeOpenProbability"] = @(rightEyeOpenProbability());
    return ret;
}

