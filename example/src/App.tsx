import * as React from 'react';

import { StyleSheet, View, Text, Alert, Button, TextInput } from 'react-native';
import * as ImagePicker from 'expo-image-picker';
import { openVideo, NativeVideoWrapper, NativeVideoFrameView, NativeFrameWrapper } from 'react-native-native-video';

import { MLKitFaceDetector } from 'react-native-mlkit-face-detection';
// import { TestVisionCamera } from './TestVisionCamera';
// import { TestVisionCamera } from './TestVisionCamera';
// initializeVisionCameraFrameProcessor();

export default function App() {
  const [frameIdx, setFrameIdx] = React.useState(0);
  const [goToFrame, setGoToFrame] = React.useState<string>(String(frameIdx));
  const [frame, setFrame] = React.useState<NativeFrameWrapper>();
  const [pickedUri, setPickedUri] = React.useState<string>();
  const vidRef = React.useRef<NativeVideoWrapper>();
  const faceDetector = React.useRef(MLKitFaceDetector({
    landmarkMode: 'all'
  }));
  const [showVisionCamera, setShowVisionCamera] = React.useState(false);
  const switchMode = React.useCallback(() => { setShowVisionCamera(v => !v) }, []);

  const onPickVideo = async () => {
    await ImagePicker.getMediaLibraryPermissionsAsync();
    const res = await ImagePicker.launchImageLibraryAsync({ mediaTypes: ImagePicker.MediaTypeOptions.Videos });
    if (res.cancelled) return;
    const uri = res.uri;
    setPickedUri(uri);
  }
  React.useEffect(() => {
    if (!pickedUri) return;
    vidRef.current = openVideo(pickedUri);
    setFrame(vidRef.current.getFrameAtIndex(0));
  }, [pickedUri]);
  const onVideoProperties = async () => {
    if (!pickedUri) return;
    let video = vidRef.current;
    if (!vidRef.current || vidRef.current.sourceUri != pickedUri) {
      video = openVideo(pickedUri);
      vidRef.current = video;
    }
    video = video!; // Make typescript not complain.
    Alert.alert(`Opened video`, `Video props are duration : ${video.duration}, frameRate: ${video.frameRate}, numFrames ${video.numFrames}, size ${video.size}`);
  }

  const onMLKitFrame = async () => {
    if (!frame) { Alert.alert('Please pick a video frame first'); return; }

    const results = faceDetector.current.process(frame);
    // console.log('results are', results.map((v) => v.landmarks()));
    console.log('result landmarks', results[0].landmarks);
  }


  return (
    <View style={styles.container}>
      <View style={{ height: 20 }}></View>
      <Button title='Switch Mode' onPress={switchMode} />
      {
        !showVisionCamera ? <View style={{ flex: 1 }}>
          <Button title='Pick Video' onPress={onPickVideo} />
          <TextInput style={{ fontSize: 16, padding: 8, borderRadius: 6, borderWidth: 1, borderColor: '#888' }} value={goToFrame} onChangeText={setGoToFrame} onEndEditing={() => {
            let num = Number(goToFrame);
            if (Number.isNaN(num)) {
              Alert.alert('enter valid number pls');
              return;
            }
            setFrameIdx(num);
          }} />
          <Text>Video uri: {pickedUri}</Text>
          <Button title='Get video properties' onPress={onVideoProperties} />
          <Button title='Try MLKit Face' onPress={onMLKitFrame} />
          <NativeVideoFrameView
            style={{ backgroundColor: 'green', borderWidth: 1, borderRadius: 8, flex: 1, alignSelf: 'stretch' }}
            frameData={frame}
          />
        </View>
          :
          <></>
          // <TestVisionCamera />
      }

    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
  },
  box: {
    width: 60,
    height: 60,
    marginVertical: 20,
  },
});
