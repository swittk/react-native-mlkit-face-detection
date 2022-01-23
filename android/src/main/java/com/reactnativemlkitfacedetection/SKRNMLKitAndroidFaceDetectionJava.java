package com.reactnativemlkitfacedetection;

import android.annotation.SuppressLint;
import android.graphics.Bitmap;
import android.media.Image;
import android.os.Build;

import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;

import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.android.gms.tasks.Task;
import com.google.android.gms.tasks.Tasks;
import com.google.mlkit.vision.common.InputImage;
import com.google.mlkit.vision.face.Face;
import com.google.mlkit.vision.face.FaceDetection;
import com.google.mlkit.vision.face.FaceDetector;
import com.google.mlkit.vision.face.FaceDetectorOptions;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutionException;

public class SKRNMLKitAndroidFaceDetectionJava {
  FaceDetector detector;
  Class imageProxyClass;
  Method imageProxyGetImageMethod;
  Method imageProxyGetImageInfoMethod;
  Method androidXCameraImageInfoGetRotationDegreesMethod;

  public SKRNMLKitAndroidFaceDetectionJava(
    int performanceMode,
    int landmarkMode,
    int contourMode,
    float minFaceSize,
    boolean trackingEnabled
  ) {
    FaceDetectorOptions.Builder optionsBuilder = new FaceDetectorOptions.Builder()
      .setPerformanceMode(performanceMode)
      .setLandmarkMode(landmarkMode)
      .setContourMode(contourMode)
      .setMinFaceSize(minFaceSize);
    if(trackingEnabled) optionsBuilder.enableTracking();
    FaceDetectorOptions options = optionsBuilder.build();
//    detector = new FaceDetector();
    detector = FaceDetection.getClient(options);
  }

  List<Face> processBitmap(Bitmap bitmap, int rotationDegree) throws ExecutionException, InterruptedException {
    InputImage image = InputImage.fromBitmap(bitmap, rotationDegree);

    Task<List<Face>> result = detector.process(image);
    // Not gonna do the async `addOnSuccessListener`, `addOnFailureListener`, since
    // I have no idea how to do async in android and then go over the JSI bridge, sounds complicated
    // So... https://developers.google.com/android/guides/tasks#blocking I just all Tasks.await() and
    // this should work right?
    return Tasks.await(result);
  }

  // Just for visionCamera I think
  // Hopefully this syntax without using "import androidx.camera.core.ImageProxy" will be enough to
  // perform dynamic imports for when visioncamera or androidx.camera isn't installed
  @SuppressLint("UnsafeOptInUsageError")
  @RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
  List<Face> processImageProxy(Object imageProxy) throws ExecutionException, InterruptedException, NoSuchMethodException, ClassNotFoundException, InvocationTargetException, IllegalAccessException {
    // It is androidx.camera.core.ImageProxy but I just don't want to call it explicitly
    if(imageProxyClass == null) {
        Class cls = Class.forName("androidx.camera.core.ImageProxy");
      imageProxyClass = cls;
      imageProxyGetImageMethod = cls.getMethod("getImage");
      imageProxyGetImageInfoMethod = cls.getMethod("getImageInfo");
      androidXCameraImageInfoGetRotationDegreesMethod = Class.forName("androidx.camera.core.ImageInfo").getMethod("getRotationDegrees");
    }
    Image _image = (Image)imageProxyGetImageMethod.invoke(imageProxy);
    if(_image != null) {
      Object imageInfo = imageProxyGetImageInfoMethod.invoke(imageProxy);
      int rotation = (int)androidXCameraImageInfoGetRotationDegreesMethod.invoke(imageInfo);
      InputImage image = InputImage.fromMediaImage(_image, rotation);
      Task<List<Face>> result = detector.process(image);
      return Tasks.await(result);
    }
    return new ArrayList<Face>();
  }

//  void processImageProxy(ImageProxy image) {
//
//  }
}
