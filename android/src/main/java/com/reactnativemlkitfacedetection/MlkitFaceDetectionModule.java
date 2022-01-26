package com.reactnativemlkitfacedetection;

import android.util.Log;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.JavaScriptContextHolder;
import com.facebook.react.bridge.NativeMap;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.module.annotations.ReactModule;

@ReactModule(name = MlkitFaceDetectionModule.NAME)
public class MlkitFaceDetectionModule extends ReactContextBaseJavaModule {
  public static final String NAME = "SKRNMlkitFaceDetection";
  private final ReactApplicationContext reactContext;

  public MlkitFaceDetectionModule(ReactApplicationContext reactContext) {
    super(reactContext);
    this.reactContext = reactContext;
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
      Log.d("SKRNMLKitFace", "Loaded SKRNMLKitFaceDetection SO");
    } catch (Exception ignored) {
      Log.d("SKRNMLKitFace", "Failed to load SKRNMLKitFaceDetection");
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
  public void clearDetector() {
    clearDetectorAtIndex(0);
  }

  public static native int nativeMultiply(int a, int b);

  private static native void initialize(long jsiRuntimePointer);

  private static native void cleanup(long jsiRuntimePointer);

  // This method is called automatically (defined in BaseJavaModule.java)
  // "called on the appropriate method when a life cycle event occurs.
  @Override
  public void initialize() {
    loadClassIfNeeded();
    ReactApplicationContext context = this.reactContext;
    JavaScriptContextHolder jsContext = context.getJavaScriptContextHolder();
    MlkitFaceDetectionModule.initialize(jsContext.get());
  }

  // This method is called automatically (defined in BaseJavaModule.java)
  // "called on the appropriate method when a life cycle event occurs.
  // This method is equivalent to Objective-C's 'invalidate'
  @Override
  public void onCatalystInstanceDestroy() {
    MlkitFaceDetectionModule.cleanup(this.reactContext.getJavaScriptContextHolder().get());
    // FlexibleHttpModule.cleanup(this.getReactApplicationContext());
  }

  void loadClassIfNeeded() {
    try {
      Class thing = SKRNMLKitAndroidFaceDetectionJava.class;
      thing.getClassLoader().loadClass("com.reactnativemlkitfacedetection.SKRNMLKitAndroidFaceDetectionJava");
      Log.d("SKRNMLKitFace", "Supposedly loaded class");
      this.reactContext.getClassLoader().loadClass("com.reactnativemlkitfacedetection.SKRNMLKitAndroidFaceDetectionJava");
      Log.d("SKRNMLKitFace", "ReactContext loaded class");
      Class<?> driverClass = Thread.currentThread().getContextClassLoader().loadClass("com.reactnativemlkitfacedetection.SKRNMLKitAndroidFaceDetectionJava");
//      Class<?> skNativeVideoWrapperJavaSide = ClassLoader.getSystemClassLoader().loadClass("com.reactnativenativevideo.SKNativeVideoWrapperJavaSide");
    } catch (ClassNotFoundException e) {
      e.printStackTrace();
      Log.d("SKRNMLKitFace", "Failed to load SKRNMLKitAndroidFaceDetectionJava");
    }
  }
}
