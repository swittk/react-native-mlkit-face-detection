package com.reactnativemlkitfacedetection;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.NativeMap;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.module.annotations.ReactModule;

@ReactModule(name = MlkitFaceDetectionModule.NAME)
public class MlkitFaceDetectionModule extends ReactContextBaseJavaModule {
    public static final String NAME = "SKRNMlkitFaceDetection";

    public MlkitFaceDetectionModule(ReactApplicationContext reactContext) {
        super(reactContext);
    }

    @Override
    @NonNull
    public String getName() {
        return NAME;
    }

    static {
        try {
            // Used to load the 'native-lib' library on application startup.
            System.loadLibrary("SKRNMLKitFaceDetection");
        } catch (Exception ignored) {
        }
    }

    // Example method
    // See https://reactnative.dev/docs/native-modules-android
    @ReactMethod
    public void multiply(int a, int b, Promise promise) {
        promise.resolve(nativeMultiply(a, b));
    }

    @ReactMethod
    public void initializeDetector(NativeMap dict, Promise promise) {
      initializeDetectorAtIndex(dict, 0, promise);
    }
    @ReactMethod
    public void initializeDetectorAtIndex(NativeMap dict, int index, Promise promise) {

    }
    @ReactMethod
    public void clearDetectorAtIndex(int index) {

    }
    @ReactMethod
    public void clearDetector() { clearDetectorAtIndex(0); }

    public static native int nativeMultiply(int a, int b);
}
