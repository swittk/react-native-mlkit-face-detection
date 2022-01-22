//
//  SKRNMLKitFaceDetectionVisionCameraFrameProcessor.m
//  react-native-mlkit-face-detection
//
//  Created by Switt Kongdachalert on 21/1/2565 BE.
//

#import "SKRNMLKitFaceDetectionVisionCameraFrameProcessor.h"


#if HAS_VISION_CAMERA
#import <MLKitVision/MLKitVision.h>
#import "SKRNMLKitiOSFaceDetector.h"
#import <map>
#import <VisionCamera/FrameProcessorPlugin.h>
#import <VisionCamera/Frame.h>

using namespace SKRNMLKitFaceDetection;
//#import <MLKitFaceDetection/MLKit>
//#import <MLKitPoseDetection/MLKitPoseDetection.h>
//#import <MLKitPoseDetectionAccurate/MLKitPoseDetectionAccurate.h>

@implementation SKRNMLKitFaceDetectionVisionCameraFrameProcessor
{
    std::map<int, std::shared_ptr<SKRNMLKitiOSFaceDetector>> detectors;
}
static SKRNMLKitFaceDetectionVisionCameraFrameProcessor *__shared_face_detector_frame_processor;

+(SKRNMLKitFaceDetectionVisionCameraFrameProcessor *)sharedInstance {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        __shared_face_detector_frame_processor = [SKRNMLKitFaceDetectionVisionCameraFrameProcessor new];
    });
    return __shared_face_detector_frame_processor;
}
-(void)initializeDetectorWithOptions:(NSDictionary *)options {
    [self initializeDetectorAtIndex:0 withOptions:options];
}
BOOL dictPropertyIsEqualToString(NSDictionary *dict, NSString *propKey, NSString *compareWith) {
    return [dict[propKey] isEqualToString:compareWith];
}
-(void)initializeDetectorAtIndex:(int)index withOptions:(NSDictionary *)obj {
    SKRNMLKitFaceDetector::PerformanceMode performanceMode = SKRNMLKitFaceDetector::PerformanceModeFast;
    SKRNMLKitFaceDetector::LandmarkMode landmarkMode = SKRNMLKitFaceDetector::LandmarkModeNone;
    SKRNMLKitFaceDetector::ContourMode contourMode = SKRNMLKitFaceDetector::ContourModeNone;
    float minFaceSize = 0.1;
    bool trackingEnabled = false;
    if(obj && obj.count) {
        performanceMode = dictPropertyIsEqualToString(obj, @"performanceMode", @"accurate")  ? SKRNMLKitFaceDetector::PerformanceModeAccurate : SKRNMLKitFaceDetector::PerformanceModeFast;
        landmarkMode = dictPropertyIsEqualToString(obj, @"landmarkMode", @"all")
        ? SKRNMLKitFaceDetector::LandmarkModeAll : SKRNMLKitFaceDetector::LandmarkModeNone;
        contourMode = dictPropertyIsEqualToString(obj, @"contourMode", @"all")
        ? SKRNMLKitFaceDetector::ContourModeAll : SKRNMLKitFaceDetector::ContourModeNone;
        id minFaceVal = obj[@"minFaceSize"];
        if([minFaceVal isKindOfClass:[NSNumber class]]) {
            minFaceSize = [minFaceVal floatValue];
        }
        id trackingEnabledVal = obj[@"trackingEnabled"];
        if([trackingEnabledVal isKindOfClass:[NSNumber class]]) {
            trackingEnabled = [trackingEnabledVal boolValue];
        }
    }
    @synchronized (self) {
        detectors.insert
        (std::pair<int, std::shared_ptr<SKRNMLKitiOSFaceDetector>>
         (index, std::make_shared<SKRNMLKitiOSFaceDetector>
          (
           performanceMode, landmarkMode, contourMode, minFaceSize, trackingEnabled
           )
          )
         );
    }
}
-(std::shared_ptr<SKRNMLKitiOSFaceDetector>)detectorAtIndex:(int)index {
    @synchronized(self) {
        return detectors.at(index);
    }
}
-(void)clearDetectorAtIndex:(int)index {
    @synchronized (self) {
        detectors.erase(index);
    }
}
-(void)clearAllDetectors {
    @synchronized (self) {
        detectors = std::map<int, std::shared_ptr<SKRNMLKitiOSFaceDetector>>();
    }
}
-(void)invalidate {
    [self clearAllDetectors];
}
-(void)initialize {
    
}

static inline id SKRNMLKitFaceDetectionVisionCameraFrameProcessorPlugin(Frame* frame, NSArray* arguments) {
    SKRNMLKitFaceDetectionVisionCameraFrameProcessor *processor = [SKRNMLKitFaceDetectionVisionCameraFrameProcessor sharedInstance];
    std::shared_ptr<SKRNMLKitiOSFaceDetector> detector;
    if([arguments count]) {
        detector = [processor detectorAtIndex:[[arguments objectAtIndex:1] intValue]];
    }
    else {
        detector = [processor detectorAtIndex:0];
    }
    if(detector.get() == nullptr) {
        NSLog(@"No detector, please initialize a detector first");
        return nil;
    }
    std::vector<std::shared_ptr<SKRNMLKitMLKFace>> res = detector.get()->processNative(frame.buffer, frame.orientation);
    NSMutableArray *ret = [NSMutableArray new];
    for(std::shared_ptr<SKRNMLKitMLKFace> _face : res) {
        std::shared_ptr<SKRNMLKitiOSMLKFace> face = std::dynamic_pointer_cast<SKRNMLKitiOSMLKFace>(_face);
        NSDictionary *dict = face->createNativeDictionary();
        [ret addObject:dict];
    }
    return ret;
}

VISION_EXPORT_FRAME_PROCESSOR(SKRNMLKitFaceDetectionVisionCameraFrameProcessorPlugin);

@end
#endif
