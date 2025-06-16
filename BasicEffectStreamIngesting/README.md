# BasicEffectStreamIngesting - Live Streaming with Beauty Effects Sample

This sample demonstrates how to implement live streaming with beauty effects using the BlendVision StreamIngest SDK.

## Features

- 📹 **Real-time Video Streaming** - Support for RTMP live streaming
- ✨ **Beauty Effects** - Including skin smoothing and skin tone adjustment
- 🔄 **Camera Switching** - Support for front and rear camera switching
- 📱 **Screen Orientation** - Automatic adaptation to screen rotation
- 📊 **Real-time Monitoring** - Display streaming status, FPS, and bandwidth information
- 📝 **Logging System** - Built-in log viewing functionality

## System Requirements

- iOS 14.0+
- Xcode 15.0+
- Swift 5.9+

### Required Permissions

Add the following permission descriptions to `Info.plist`:
```xml
<key>NSCameraUsageDescription</key>
<string>Camera access is required for live streaming</string>
<key>NSMicrophoneUsageDescription</key>
<string>Microphone access is required for live streaming</string>
```

## Core Class Overview

### EffectStreamIngestViewController

This is the main controller of the sample, inheriting from `UIViewController`, providing complete live streaming functionality.

#### Initialization

```swift
// Create StreamIngest instance
let config = StreamIngestConfig(key: "your_license_key")
let streamIngest = try await StreamIngest.create(with: config)

// Initialize EffectStreamIngestViewController
let effectController = EffectStreamIngestViewController(streamIngest: streamIngest)
```

#### Main Properties

```swift
class EffectStreamIngestViewController: UIViewController {
    var streamIngest: StreamIngest              // Core streaming instance
    var effectStreamIngest: EffectStreamIngest? // Beauty effect processing instance
    var cameraPreviewView: CameraPreviewView?   // Camera preview view
    var currentPosition: AVCaptureDevice.Position = .back // Current camera position
}
```

## Main Feature Implementation

### 1. Beauty Effect Control

#### Skin Smoothing Effect
```swift
@objc
func skinSmoothValueChanged(_ sender: UISlider) {
    let intensity = Int(sender.value * 100)
    skinSmoothValueLabel.text = "\(intensity)%"
    effectStreamIngest?.setEffects([SkinSmoothEffect(intensity: intensity)])
}
```

#### Skin Tone Adjustment
```swift
@objc
func skinToneValueChanged(_ sender: UISlider) {
    let intensity = Int(sender.value * 100)
    skinToneValueLabel.text = "\(intensity)%"
    effectStreamIngest?.setEffects([SkinToneEffect(intensity: intensity)])
}
```

#### Beauty Toggle
```swift
@objc
func on(beautify: UIBarButtonItem) {
    effectStreamIngest?.isBeautifyEnabled.toggle()
    syncEffectSlidersWithState()
    beautify.image = UIImage(systemName: beautifyIconName)
}
```

### 2. Camera Control

#### Front/Rear Camera Switching
```swift
func rotateCamera() {
    currentPosition = currentPosition == .back ? .front : .back
    cameraPreviewView?.activateCamera(isFrontCamera: currentPosition == .front)
    
    if let camera = AVCaptureDevice.default(.builtInWideAngleCamera, 
                                            for: .video, 
                                            position: currentPosition) {
        try? effectStreamIngest?.attachCamera(device: camera)
    }
}
```

#### Camera Permission Check
```swift
func requestCameraAuthentication(_ completion: @escaping (_ authorized: Bool)->Void) {
    let status = AVCaptureDevice.authorizationStatus(for: .video)
    if status == .notDetermined {
        AVCaptureDevice.requestAccess(for: .video) { authorized in
            DispatchQueue.main.async {
                completion(authorized)
            }
        }
    } else {
        DispatchQueue.main.async {
            completion(status == .authorized)
        }
    }
}
```

### 3. Streaming Control

#### Start/Stop Streaming
```swift
@objc
func on(publish: UIButton) {
    guard let rtmpUrl = Preference.shared.uri, 
          let streamName = Preference.shared.streamName else { return }
    
    if publish.isSelected {
        streamIngest.stopPublish()
        isRunning = false
    } else {
        streamIngest.startPublish(rtmpUrl: rtmpUrl, stream: streamName)
        isRunning = true
    }
    publish.isSelected.toggle()
}
```

#### Pause/Resume Streaming
```swift
@objc
func on(pause: UIButton) {
    guard controlView.publishButton.isSelected else {
        // Show streaming not started alert
        return
    }
    
    pause.isSelected.toggle()
    streamIngest.paused = pause.isSelected
}
```

### 4. Lifecycle Management

#### App Foreground/Background Handling
```swift
override func viewWillAppear(_ animated: Bool) {
    super.viewWillAppear(animated)
    
    // Start camera and audio capture
    if let audio = AVCaptureDevice.default(for: .audio) {
        try? effectStreamIngest?.attachAudio(device: audio)
    }
    
    if let camera = AVCaptureDevice.default(.builtInWideAngleCamera,
                                            for: .video,
                                            position: currentPosition) {
        try? effectStreamIngest?.attachCamera(device: camera)
        
        DispatchQueue.global(qos: .background).async {
            self.effectStreamIngest?.startRunning()
        }
    }
    
    // Listen for app state changes
    setupAppStateObservers()
}

override func viewWillDisappear(_ animated: Bool) {
    super.viewWillDisappear(animated)
    
    // Stop camera capture
    DispatchQueue.global(qos: .background).async {
        self.effectStreamIngest?.stopRunning()
    }
    
    // Remove state observers
    removeAppStateObservers()
}
```

## Configuration Settings

### Streaming Configuration (Preference.swift)

```swift
struct Preference {
    static var shared = Preference()
    
    var uri: String? = "rtmp://your-rtmp-server.com:1935/live"
    var streamName: String? = "your_stream_name"
    var licenseKey: String = "your_license_key"
    var streamIngestQuality: StreamIngestQuality = StreamIngestQualityAuto()
}
```

### Video Quality Settings

```swift
// Auto quality (adjusts based on network conditions)
let autoQuality = StreamIngestQualityAuto()

// High quality settings
let highQuality = StreamIngestQualityHigh()

// Medium quality settings
let mediumQuality = StreamIngestQualityMedium()

// Low quality settings
let lowQuality = StreamIngestQualityLow()
```

## Delegate Implementation

### StreamIngestDelegate

```swift
extension EffectStreamIngestViewController: StreamIngestDelegate {
    func streamIngestDidStartPublishing(_ streamIngest: StreamIngest) {
        debugPrint("Streaming started")
        logView.addNewLog("Streaming started")
    }
    
    func streamIngestDidStopPublishing(_ streamIngest: StreamIngest) {
        debugPrint("Streaming stopped")
        logView.addNewLog("Streaming stopped")
    }
    
    func streamIngestDidFailToPublish(_ streamIngest: StreamIngest, with error: StreamIngestErrorEvent) {
        DispatchQueue.main.async {
            // Show error alert
            let alert = UIAlertController(title: "Streaming Failed", 
                                        message: error.code, 
                                        preferredStyle: .alert)
            self.present(alert, animated: true)
        }
    }
    
    func streamIngestDidUpdateBufferStatus(_ streamIngest: StreamIngest, with status: StreamIngestBufferState) {
        // Change background color based on buffer status
        switch status.status {
        case .normal:
            self.view.backgroundColor = UIColor.green.withAlphaComponent(0.3)
        case .warning:
            self.view.backgroundColor = UIColor.yellow.withAlphaComponent(0.3)
        case .critical:
            self.view.backgroundColor = UIColor.red.withAlphaComponent(0.3)
        }
    }
}
```

### EffectStreamIngestDelegate

```swift
extension EffectStreamIngestViewController: EffectStreamIngestDelegate {
    func effectStreamIngest(_ effectStreamIngest: EffectStreamIngest, 
                          didOutputVideo sampleBuffer: CMSampleBuffer) -> CMSampleBuffer {
        return sampleBuffer
    }
    
    func effectStreamIngest(_ effectStreamIngest: EffectStreamIngest, 
                          didOutputAudio sampleBuffer: CMSampleBuffer) -> CMSampleBuffer {
        return sampleBuffer
    }
}
```

## Usage Steps

1. **Configure Streaming Parameters**
   - Set your RTMP URL, stream name, and license key in `Preference.swift`

2. **Initialize Controller**
   ```swift
   let config = StreamIngestConfig(key: Preference.shared.licenseKey)
   let streamIngest = try await StreamIngest.create(with: config)
   let effectController = EffectStreamIngestViewController(streamIngest: streamIngest)
   ```

3. **Start Camera**
   - The app will automatically request camera and microphone permissions
   - Camera preview will start automatically after permissions are granted

4. **Adjust Beauty Effects**
   - Use the skin smoothing slider to adjust smoothing intensity (0-100%)
   - Use the skin tone slider to adjust skin tone effects (0-100%)
   - Tap the beauty button to enable/disable beauty features

5. **Start Streaming**
   - Tap the streaming button to start live broadcast
   - Monitor streaming status and network quality
   - Can pause/resume streaming

## Important Notes

- 🔑 **License Key**: Ensure you have a valid BlendVision SDK license key
- 🌐 **Network Connection**: Streaming requires a stable network connection
- 🔋 **Battery Management**: Live streaming consumes significant battery, recommend connecting to power
- 📱 **Screen Rotation**: Recommend setting screen orientation before starting streaming
- 🎯 **Performance Optimization**: Beauty effects impact performance, adjust based on device capabilities

## Troubleshooting

### Common Issues

1. **Camera Cannot Start**
   - Check if camera permissions have been granted
   - Ensure no other applications are using the camera

2. **Streaming Fails**
   - Verify RTMP URL and stream name are correct
   - Check network connection status
   - Verify license key is valid

3. **Beauty Effects Not Working**
   - Confirm beauty features are enabled
   - Check if slider values are greater than 0

4. **Performance Issues**
   - Try lowering streaming quality settings
   - Reduce beauty effect intensity
   - Ensure device has sufficient available memory

## Support

For additional technical support, please contact the BlendVision technical team. 