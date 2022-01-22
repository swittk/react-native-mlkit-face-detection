#import "SKRNMLKitFaceDetection.h"
#import "react-native-mlkit-face-detection.h"
#import <React/RCTUtils.h>
#import <React/RCTBridge+Private.h>
#import <jsi/jsi.h>
#import <ReactCommon/CallInvoker.h>
#import "SKRNMLKitiOSFaceDetector.h"
#import "SKRNMLKitFaceDetectionVisionCameraFrameProcessor.h"

using namespace SKRNMLKitFaceDetection;
@implementation SKRNMlkitFaceDetection
@synthesize bridge = _bridge;

RCT_EXPORT_MODULE()

// Example method for C++
// See the implementation of the example module in the `cpp` folder
RCT_EXPORT_METHOD(multiply:(nonnull NSNumber*)a withB:(nonnull NSNumber*)b
                  withResolver:(RCTPromiseResolveBlock)resolve
                  withReject:(RCTPromiseRejectBlock)reject)
{
    NSNumber *result = @(SKRNMLKitFaceDetection::multiply([a floatValue], [b floatValue]));
    resolve(result);
}
#pragma mark - Vision Camera methods
#if HAS_VISION_CAMERA

RCT_EXPORT_METHOD(initializeDetector:(NSDictionary *)dict
                  withResolver:(RCTPromiseResolveBlock)resolve
                  withReject:(RCTPromiseRejectBlock)reject)
{
    [[SKRNMLKitFaceDetectionVisionCameraFrameProcessor sharedInstance] initializeDetectorWithOptions:dict];
}
RCT_REMAP_METHOD(initializeDetectorAtIndex,
                 initializeDetectorAtIndex:(int)index
                 withOptions:(NSDictionary *)dict
                  withResolver:(RCTPromiseResolveBlock)resolve
                  withReject:(RCTPromiseRejectBlock)reject)
{
    [[SKRNMLKitFaceDetectionVisionCameraFrameProcessor sharedInstance] initializeDetectorAtIndex:index withOptions:dict];
}
RCT_EXPORT_METHOD(clearDetectorAtIndex:(int)index
                 withResolver:(RCTPromiseResolveBlock)resolve
                 withReject:(RCTPromiseRejectBlock)reject)
{
    [[SKRNMLKitFaceDetectionVisionCameraFrameProcessor sharedInstance] clearDetectorAtIndex:index];
}
RCT_REMAP_METHOD(clearDetector,
                 clearDetector:(int)index
                 withResolver:(RCTPromiseResolveBlock)resolve
                 withReject:(RCTPromiseRejectBlock)reject)
{
    [[SKRNMLKitFaceDetectionVisionCameraFrameProcessor sharedInstance] clearDetectorAtIndex:0];
}
#endif
#pragma mark - End Vision Camera methods

+ (BOOL)requiresMainQueueSetup {
    return YES;
}



- (void)setBridge:(RCTBridge *)bridge {
    _bridge = bridge;
    _setBridgeOnMainQueue = RCTIsMainQueue();
    [self installLibrary];
}

-(void)installLibrary {
//    self.bridge.reactInstance;
    RCTCxxBridge *cxxBridge = (RCTCxxBridge *)self.bridge;
    if (!cxxBridge.runtime) {
        
        /**
         * This is a workaround to install library
         * as soon as runtime becomes available and is
         * not recommended. If you see random crashes in iOS
         * global.xxx not found etc. use this.
         */
        
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.001 * NSEC_PER_SEC),
                       dispatch_get_main_queue(), ^{
            /**
             When refreshing the app while debugging, the setBridge
             method is called too soon. The runtime is not ready yet
             quite often. We need to install library as soon as runtime
             becomes available.
             */
            [self installLibrary];
            
        });
        return;
    }
    facebook::jsi::Runtime *runtime = (facebook::jsi::Runtime *)cxxBridge.runtime;
    SKRNMLKitFaceDetection::install(*runtime, [](facebook::jsi::Runtime& _runtime,
                         SKRNMLKitFaceDetector::PerformanceMode _performanceMode,
                         SKRNMLKitFaceDetector::LandmarkMode _landmarkMode,
                         SKRNMLKitFaceDetector::ContourMode _contourMode,
                         float _minFaceSize,
                         bool _trackingEnabled) -> std::shared_ptr<SKRNMLKitFaceDetector> {
        std::shared_ptr<SKRNMLKitiOSFaceDetector>ret =  std::make_shared<SKRNMLKitiOSFaceDetector>(_performanceMode, _landmarkMode, _contourMode, _minFaceSize, _trackingEnabled);
        return ret;
    });
#if HAS_VISION_CAMERA
    [[SKRNMLKitFaceDetectionVisionCameraFrameProcessor sharedInstance] initialize];
#endif
}

- (void)invalidate {
    RCTCxxBridge *cxxBridge = (RCTCxxBridge *)self.bridge;
    facebook::jsi::Runtime *runtime = (facebook::jsi::Runtime *)cxxBridge.runtime;
    SKRNMLKitFaceDetection::cleanup(*runtime);
#if HAS_VISION_CAMERA
    [[SKRNMLKitFaceDetectionVisionCameraFrameProcessor sharedInstance] invalidate];
#endif
}


//#if HAS_VISION_CAMERA
//
//RCT_REMAP_METHOD(initializeVisionCameraFrameProcessorWithOptions,
//                 initializeVisionCameraFrameProcessorWithOptions:(NSDictionary *)optionsDict
//                  withResolver:(RCTPromiseResolveBlock)resolve
//                  withReject:(RCTPromiseRejectBlock)reject)
//{
//    BOOL result = [[SKRNMLKitPoseDetectionVisionCameraFrameProcessor sharedInstance] initializePoseDetectorWithOptions:optionsDict];
//    resolve(@(result));
//}
//
//#endif


@end
