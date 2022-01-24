# react-native-mlkit-face-detection

Face Detection using MLKit
(Currently iOS Only)

Right now Android compiles when neither `react-native-native-video` or `react-native-vision-camera` is installed (which isn't very helpful), but right now has a problem with multiple definitions of JNI_OnLoad, which would cause compilation failures. Once that is solved then it should be usable.

## Installation

```sh
npm install react-native-mlkit-face-detection
```

## Usage

See example app. And Typescript types.
```ts
import { MLKitFaceDetector } from "react-native-mlkit-face-detection";

// ...
const detector = MLKitFaceDetector({
    landmarkMode: 'all'
});
// `frame` is a frame of video from `react-native-native-video`
detector.process(frame)
```

For Vision Camera to work, you must add the babel plugin
````ts
module.exports = {
  plugins: [
    [
      'react-native-reanimated/plugin',
      {
        globals: ['__SKRNMLKitFaceDetectionVisionCameraFrameProcessorPlugin'],
      },
    ],
````
and call initialize to one of the frame processor slots (calling `initializeVisionCameraDetector(options)` is equivalent to calling `initializeVisionCameraDetectorAtIndex(0, options)`)

Example:
```ts
initializeVisionCameraDetector({
  landmarkMode: 'all',
  performanceMode: 'accurate'
})
```

## Contributing

See the [contributing guide](CONTRIBUTING.md) to learn how to contribute to the repository and the development workflow.

## License

MIT
