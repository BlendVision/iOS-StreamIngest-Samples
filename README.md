# BlendVision Stream Ingest
Stream From Your App
To set up a streaming source and transmit it to BlendVision's live streaming service via a RTMP link from your own applications.

## Examples
Examples project are available for iOS with UIKit
- [x] Camera and microphone publish.

## Requirements

### Development
|Version|Xcode|Swift|
|:----:|:----:|:----:|
|1.7.0+|15.0+|5.9+|
|1.6.0+|15.0+|5.8+|
|1.5.0+|14.0+|5.7+|

Please contains Info.plist.
**iOS 14.0+**
* NSMicrophoneUsageDescription
* NSCameraUsageDescription

## Prerequisites
Make sure you setup and activate your AVAudioSession iOS.
```swift
import AVFoundation
let session = AVAudioSession.sharedInstance()
do {
    try session.setCategory(.playAndRecord, mode: .default, options: [.defaultToSpeaker, .allowBluetooth])
    try session.setActive(true)
} catch {
    print(error)
}
```

## RTMP Usage
### Ingest
```swift
// Create an StreamIngest instance with your desired configurations
lazy var stream: StreamIngest = {
    let quality = Preference.shared.streamIngestQuality
    let stream = StreamIngest()
    stream.videoSize = quality.videoSize
    stream.videoBitrate = quality.videoBitRate
    stream.audioBitrate = quality.audioBitRate
    return stream
}()

// Create a StreamRenderView and add it into your subview
previewView = StreamRenderView()
previewView.translatesAutoresizingMaskIntoConstraints = false
view.addSubview(previewView)

// Attach audio device
stream.attachAudio(AVCaptureDevice.default(for: .audio)) { error in
    debugPrint("attaching audio with error=\(String(describing: error))")
}

// Ingesting your stream
stream.startPublish(rtmpUrl: "Your RTMP URL", stream: "Your stream name")
```

## Settings
### Capture
```swift
/// Specifies the video capture settings.
let camera = AVCaptureDevice.default(.builtInWideAngleCamera, for: .video, position: currentPosition)
stream.attachCamera(camera, channel: 0) { error in
    debugPrint("attaching camera with error=\(String(describing: error))")
}
```
### Stream Ingest Quality Settings
Predefined settings configurations used to configure the quality of video streaming ingestion. 
These configurations are:

- StreamIngestQualityLow(): This setting configures the ingestion quality to be low, which may reduce the resolution or frame rate of the video to conserve bandwidth and network traffic.

- StreamIngestQualityMedium(): This setting provides a balanced option suitable for most scenarios, maintaining good video quality while not excessively consuming bandwidth.

- StreamIngestQualityHigh(): This setting is ideal for scenarios requiring high definition and high frame rates, offering superior video quality but potentially consuming more bandwidth and network resources.


### Audio Settings
```swift
let quality = StreamIngestQualityMedium()
stream.audioBitrate = quality.audioBitRate
```
### Video Settings
```swift
let quality = StreamIngestQualityMedium()
stream.videoSize = quality.videoSize
stream.videoBitrate = quality.videoBitRate
```
