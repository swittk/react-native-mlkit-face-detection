# react-native-mlkit-face-detection

Face Detection using MLKit
(Currently iOS Only)

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

## Contributing

See the [contributing guide](CONTRIBUTING.md) to learn how to contribute to the repository and the development workflow.

## License

MIT
