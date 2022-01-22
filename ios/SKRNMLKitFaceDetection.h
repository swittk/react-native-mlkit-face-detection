#import <React/RCTBridgeModule.h>

#ifdef __cplusplus

#import "react-native-mlkit-face-detection.h"

#endif

#ifndef HAS_VISION_CAMERA
#if __has_include(<VisionCamera/Frame.h>)
#define HAS_VISION_CAMERA 1
@class Frame;
#endif
#endif

@interface SKRNMlkitFaceDetection : NSObject <RCTBridgeModule>
@property (nonatomic, assign) BOOL setBridgeOnMainQueue;
@end
