# BlendVision Stream Ingest iOS Samples

Stream From Your App
To set up a streaming source and transmit it to BlendVision's live streaming service via a RTMP link from your own applications.

## Examples
Examples project are available for iOS with UIKit
- [x] Camera and microphone publish.
- [x] Camera and microphone publish with beauty effects.

## Requirements
To run this example, a valid license configuration needs to be set. Please inform our contact window for assistance.

### Development
|SDK Version|Xcode|Swift|iOS|
|:----:|:----:|:----:|:----:|
|3.0.0+|15.0+|5.9+|14.0+|
|2.x.x|15.0+|5.8+|14.0+|

Please contains Info.plist.
**iOS 14.0+**
* NSMicrophoneUsageDescription
* NSCameraUsageDescription

## Installation
### Using Swift Package Manager
[Swift Package Manager](https://www.swift.org/documentation/package-manager/) is a tool for managing the distribution of Swift frameworks. It integrates with the Swift build system to automate the process of downloading, compiling, and linking dependencies.

#### Using Xcode
To integrate using Xcode 14, open your Project file and specify it in `Project > Package Dependencies` using the following URL:
```swift
https://github.com/BlendVision/iOS-StreamIngest-SDK.git
```

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

### StreamIngest Initialization (v3.0.0+)
```swift
// Create configuration and initialize StreamIngest instance
guard let licenseKey = "your_license_key" else {
    // Handle license key validation
    return
}

let config = StreamIngestConfig(key: licenseKey)
let streamIngest = try await StreamIngest.create(with: config)

// Configure quality settings
let quality = StreamIngestQualityMedium()
streamIngest?.videoSize = await quality.videoSize()
streamIngest?.videoBitrate = await quality.videoBitRate()
streamIngest?.audioBitrate = await quality.audioBitRate()
```

### Basic Usage Example
```swift
class IngestViewController: UIViewController {
    var stream: StreamIngest
    
    init(streamIngest: StreamIngest) {
        self.stream = streamIngest
        super.init(nibName: nil, bundle: nil)
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        // Create a StreamRenderView and add it into your subview
        previewView = StreamRenderView()
        previewView.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(previewView)
        
        // Attach camera
        let camera = AVCaptureDevice.default(.builtInWideAngleCamera, for: .video, position: .back)
        stream.attachCamera(camera, channel: 0) { error in
            debugPrint("attaching camera with error=\(String(describing: error))")
        }
        
        // Attach audio device
        stream.attachAudio(AVCaptureDevice.default(for: .audio)) { error in
            debugPrint("attaching audio with error=\(String(describing: error))")
        }
        
        // Attach stream to preview
        previewView.attachStream(stream)
        
        // Start publishing
        stream.startPublish(rtmpUrl: "Your RTMP URL", stream: "Your stream name")
    }
}
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

- StreamIngestQualityAuto(): Automatically selects Medium or Low quality based on network type.

### Audio Settings
```swift
let quality = StreamIngestQualityMedium()
stream.audioBitrate = await quality.audioBitRate()
```

### Video Settings
```swift
let quality = StreamIngestQualityMedium()
stream.videoSize = await quality.videoSize()
stream.videoBitrate = await quality.videoBitRate()
```

## Beauty Effects (v3.0.0+)

### Enable Beauty Effects
```swift
// Create EffectStreamIngest instance
let effectStreamIngest = EffectStreamIngest(streamIngest: streamIngest)

// Set skin smoothing effect
let skinSmoothEffect = SkinSmoothEffect(intensity: 50) // Intensity 0-100
effectStreamIngest.setEffects([skinSmoothEffect])

// Set skin tone adjustment effect
let skinToneEffect = SkinToneEffect(intensity: 30) // Intensity 0-100
effectStreamIngest.setEffects([skinToneEffect])

// Enable/disable beauty features
effectStreamIngest.isBeautifyEnabled = true
```

### Beauty Effect Controls
```swift
// Skin smoothing adjustment
@objc func skinSmoothValueChanged(_ sender: UISlider) {
    let intensity = Int(sender.value * 100)
    effectStreamIngest?.setEffects([SkinSmoothEffect(intensity: intensity)])
}

// Skin tone adjustment
@objc func skinToneValueChanged(_ sender: UISlider) {
    let intensity = Int(sender.value * 100)
    effectStreamIngest?.setEffects([SkinToneEffect(intensity: intensity)])
}
```

---
## Migration from v2.x to v3.0.0

### Major Changes:

1. **License Key Management**:
   - v3.0.0 requires a valid license key during StreamIngest initialization
   - License key validation must be performed before creating StreamIngest instance

2. **StreamIngest Initialization**:
   - Now requires pre-creating StreamIngest instance and passing it through initialization method to view controllers
   - Quality settings need to be configured immediately after creation

3. **New Beauty Effects Feature**:
   - Support for SkinSmoothEffect (skin smoothing)
   - Support for SkinToneEffect (skin tone adjustment)
   - Dynamic enable/disable beauty features

### Migration Steps:

```swift
// v2.x legacy approach
let stream = try await StreamIngest.create(with: config)

// v3.0.0 new approach
guard let licenseKey = "your_license_key", !licenseKey.isEmpty else {
    throw StreamIngestError.invalidLicense
}
let config = StreamIngestConfig(key: licenseKey)
let stream = try await StreamIngest.create(with: config)

// Configure quality settings immediately
let quality = StreamIngestQualityMedium()
stream?.videoSize = await quality.videoSize()
stream?.videoBitrate = await quality.videoBitRate()
stream?.audioBitrate = await quality.audioBitRate()
```

---
## FAQ

### Q: Why doesn't the remote stream update when changing screen orientation during streaming?

**A:**  
Changing screen orientation during an active stream is not supported.  
To update the remote display with the correct orientation, please stop the current stream first, then restart streaming after changing the orientation.

### Q: How to handle License Key validation failure in v3.0.0?

**A:**  
In v3.0.0, invalid license keys will throw errors during StreamIngest creation. It's recommended to use do-catch statements for error handling:

```swift
do {
    let config = StreamIngestConfig(key: licenseKey)
    let stream = try await StreamIngest.create(with: config)
    // Continue setup...
} catch {
    let errorCode = (error as NSError).code
    let errorMessage = (error as NSError).domain
    // Display error message to user
}
```

---
