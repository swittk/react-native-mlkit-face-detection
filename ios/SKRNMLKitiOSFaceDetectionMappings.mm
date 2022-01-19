//
//  SKRNMLKitiOSFaceDetectionMappings.m
//  react-native-mlkit-face-detection
//
//  Created by Switt Kongdachalert on 19/1/2565 BE.
//

#import <Foundation/Foundation.h>
#import <MLKitFaceDetection/MLKitFaceDetection.h>

NSDictionary *SKRNMLKitiOSFaceDetectionMappingFaceLandmarkToNative = @{
    @"MouthBottom": MLKFaceLandmarkTypeMouthBottom,
    @"MouthRight": MLKFaceLandmarkTypeMouthRight,
    @"MouthLeft": MLKFaceLandmarkTypeMouthLeft,
    @"LeftEar": MLKFaceLandmarkTypeLeftEar,
    @"RightEar": MLKFaceLandmarkTypeRightEar,
    @"LeftEye": MLKFaceLandmarkTypeLeftEye,
    @"RightEye": MLKFaceLandmarkTypeRightEye,
    @"LeftCheek": MLKFaceLandmarkTypeLeftCheek,
    @"RightCheek": MLKFaceLandmarkTypeRightCheek,
    @"NoseBase": MLKFaceLandmarkTypeNoseBase
};

NSDictionary *SKRNMLKitiOSFaceDetectionMappingFaceContourToNative = @{
    @"Face": MLKFaceContourTypeFace,
    @"LeftEyebrowTop": MLKFaceContourTypeLeftEyebrowTop,
    @"LeftEyebrowBottom": MLKFaceContourTypeLeftEyebrowBottom,
    @"RightEyebrowTop": MLKFaceContourTypeRightEyebrowTop,
    @"RightEyebrowBottom": MLKFaceContourTypeRightEyebrowBottom,
    @"LeftEye": MLKFaceContourTypeLeftEye,
    @"RightEye": MLKFaceContourTypeRightEye,
    @"UpperLipTop": MLKFaceContourTypeUpperLipTop,
    @"UpperLipBottom": MLKFaceContourTypeUpperLipBottom,
    @"LowerLipTop": MLKFaceContourTypeLowerLipTop,
    @"LowerLipBottom": MLKFaceContourTypeLowerLipBottom,
    @"NoseBridge": MLKFaceContourTypeNoseBridge,
    @"NoseBottom": MLKFaceContourTypeNoseBottom,
    @"LeftCheek": MLKFaceContourTypeLeftCheek,
    @"RightCheek": MLKFaceContourTypeRightCheek
};

NSDictionary *SKRNMLKitiOSFaceDetectionMappingFaceLandmarkToCrossPlatform = @{
    MLKFaceLandmarkTypeMouthBottom: @"MouthBottom",
    MLKFaceLandmarkTypeMouthRight: @"MouthRight",
    MLKFaceLandmarkTypeMouthLeft: @"MouthLeft",
    MLKFaceLandmarkTypeLeftEar: @"LeftEar",
    MLKFaceLandmarkTypeRightEar: @"RightEar",
    MLKFaceLandmarkTypeLeftEye: @"LeftEye",
    MLKFaceLandmarkTypeRightEye: @"RightEye",
    MLKFaceLandmarkTypeLeftCheek: @"LeftCheek",
    MLKFaceLandmarkTypeRightCheek: @"RightCheek",
    MLKFaceLandmarkTypeNoseBase: @"NoseBase"
};

NSDictionary *SKRNMLKitiOSFaceDetectionMappingFaceContourToCrossPlatform = @{
    MLKFaceContourTypeFace: @"Face",
    MLKFaceContourTypeLeftEyebrowTop: @"LeftEyebrowTop",
    MLKFaceContourTypeLeftEyebrowBottom: @"LeftEyebrowBottom",
    MLKFaceContourTypeRightEyebrowTop: @"RightEyebrowTop",
    MLKFaceContourTypeRightEyebrowBottom: @"RightEyebrowBottom",
    MLKFaceContourTypeLeftEye: @"LeftEye",
    MLKFaceContourTypeRightEye: @"RightEye",
    MLKFaceContourTypeUpperLipTop: @"UpperLipTop",
    MLKFaceContourTypeUpperLipBottom: @"UpperLipBottom",
    MLKFaceContourTypeLowerLipTop: @"LowerLipTop",
    MLKFaceContourTypeLowerLipBottom: @"LowerLipBottom",
    MLKFaceContourTypeNoseBridge: @"NoseBridge",
    MLKFaceContourTypeNoseBottom: @"NoseBottom",
    MLKFaceContourTypeLeftCheek: @"LeftCheek",
    MLKFaceContourTypeRightCheek: @"RightCheek"
};
