//
//  SKRNMLKitFaceDetectionVisionCameraFrameProcessor.h
//  react-native-mlkit-face-detection
//
//  Created by Switt Kongdachalert on 21/1/2565 BE.
//

#import "SKRNMLKitFaceDetection.h"

#if HAS_VISION_CAMERA
@interface SKRNMLKitFaceDetectionVisionCameraFrameProcessor : NSObject
+(SKRNMLKitFaceDetectionVisionCameraFrameProcessor *)sharedInstance;
-(void)initializeDetectorWithOptions:(NSDictionary *)options;
-(void)initializeDetectorAtIndex:(int)index withOptions:(NSDictionary *)options;
-(void)clearDetectorAtIndex:(int)index;
-(void)invalidate;
-(void)initialize;
@end
#endif
