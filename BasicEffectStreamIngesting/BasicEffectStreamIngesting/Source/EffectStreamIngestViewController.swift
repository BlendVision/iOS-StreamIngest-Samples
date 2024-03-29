//
//  EffectStreamIngestViewController.swift
//  StreamIngestExample
//
//  Created by Tsung Cheng Lo on 2024/3/4.
//

import UIKit
import AVFoundation
import BVStreamIngest

class EffectStreamIngestViewController: UIViewController {
    
    lazy var streamIngest: StreamIngest = {
        let quality = Preference.shared.streamIngestQuality
        let stream = StreamIngest()
        stream.videoSize = quality.videoSize
        stream.videoBitrate = quality.videoBitRate
        stream.audioBitrate = quality.audioBitRate
        return stream
    }()
    
    let authorizer = StreamIngestAuthorizer(debugMode: true)
    
    lazy var cameraPreviewView: UIView = {
        let view = UIView()
        view.translatesAutoresizingMaskIntoConstraints = false
        return view
    }()
    
    lazy var skinSmoothSlider: UISlider = {
        let slider = UISlider()
        slider.translatesAutoresizingMaskIntoConstraints = false
        return slider
    }()
    
    var infoLabel: UILabel = {
        let label = UILabel()
        label.numberOfLines = 0
        label.translatesAutoresizingMaskIntoConstraints = false
        label.backgroundColor = .darkGray.withAlphaComponent(0.7)
        return label
    }()
    
    let controlView: ControlView = {
        let view = ControlView()
        view.translatesAutoresizingMaskIntoConstraints = false
        view.pauseButton.isHidden = true
        return view
    }()
    
    var currentPosition: AVCaptureDevice.Position = .back
    
    var effectStreamIngest: EffectStreamIngest?
    
    var isRunning = false
    
    private var appActiveObserver: NSObjectProtocol? = nil
    
    private var appInactiveObserver: NSObjectProtocol? = nil

    override func viewDidLoad() {
        super.viewDidLoad()
        
        authorizer.requestAuthentication { error in
            if let error {
                debugPrint("Authority error = \(error)")
            } else {
                debugPrint("StreamIngest SDK authority success")
            }
        }
        
        streamIngest.delegate = self
        
        effectStreamIngest = EffectStreamIngest(streamIngest: streamIngest)
        effectStreamIngest?.delegate = self
        
        view.backgroundColor = .black
        
        navigationItem.leftBarButtonItems = [
            UIBarButtonItem(
                image: UIImage(systemName: "xmark"),
                style: .plain,
                target: self,
                action: #selector(on(close:))
            )
        ]
        
        navigationItem.rightBarButtonItems = [
            UIBarButtonItem(
                image: UIImage(systemName: "arrow.triangle.2.circlepath.camera.fill"),
                style: .plain,
                target: self,
                action: #selector(on(switch:))
            )
        ]

        // Do any additional setup after loading the view.
        view.addSubview(cameraPreviewView)
        NSLayoutConstraint.activate([
            cameraPreviewView.leadingAnchor.constraint(equalTo: view.leadingAnchor),
            cameraPreviewView.trailingAnchor.constraint(equalTo: view.trailingAnchor),
            cameraPreviewView.topAnchor.constraint(equalTo: view.topAnchor),
            cameraPreviewView.bottomAnchor.constraint(equalTo: view.bottomAnchor)
        ])
        
        view.addSubview(controlView)
        NSLayoutConstraint.activate([
            controlView.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor),
            controlView.leadingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.leadingAnchor),
            controlView.trailingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.trailingAnchor)
        ])
        
        controlView.publishButton.addTarget(self, action: #selector(on(publish:)), for: .touchUpInside)
        controlView.pauseButton.addTarget(self, action: #selector(on(pause:)), for: .touchUpInside)
        
        view.addSubview(infoLabel)
        NSLayoutConstraint.activate([
            infoLabel.leadingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.leadingAnchor),
            infoLabel.trailingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.trailingAnchor),
            infoLabel.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor, constant: -44.0),
            infoLabel.heightAnchor.constraint(equalToConstant: 88.0)
        ])
        
        skinSmoothSlider.addTarget(self, action: #selector(skinSmoothValueChanged(_:)), for: .valueChanged)
        view.addSubview(skinSmoothSlider)
        NSLayoutConstraint.activate([
            skinSmoothSlider.leadingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.leadingAnchor),
            skinSmoothSlider.trailingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.trailingAnchor),
            skinSmoothSlider.bottomAnchor.constraint(equalTo: infoLabel.topAnchor, constant: -16.0)
        ])
    }
    
    deinit {
        debugPrint("The object \(self) has been deallocated")
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        streamIngest.addObserver(self, forKeyPath: "currentFPS", options: .new, context: nil)
        
        if let audio = AVCaptureDevice.default(for: .audio) {
            try? effectStreamIngest?.attachAudio(device: audio)
        }
        
        if let camera = AVCaptureDevice.default(.builtInWideAngleCamera, for: .video, position: currentPosition) {
            try? effectStreamIngest?.attachCamera(device: camera)
            
            DispatchQueue.global(qos: .background).async { [weak self] in
                guard let self = self else { return }
                effectStreamIngest?.startRunning()
            }
        }
        
        appActiveObserver = NotificationCenter.default.addObserver(forName: UIApplication.didBecomeActiveNotification, object: nil, queue: nil) { [weak self] (notification) in
            
            DispatchQueue.global(qos: .background).async { [weak self] in
                guard let self = self else { return }
                self.effectStreamIngest?.startRunning()
                
                if isRunning {
                    self.reconnect()
                }
            }
        }
        
        appInactiveObserver = NotificationCenter.default.addObserver(forName: UIApplication.didEnterBackgroundNotification, object: nil, queue: nil) { [weak self] (notification) in
            
            DispatchQueue.global(qos: .background).async { [weak self] in
                guard let self = self else {
                    return
                }
                self.effectStreamIngest?.stopRunning()
                
                if isRunning {
                    self.streamIngest.stopPublish()
                }
            }
            
        }
        
        UIApplication.shared.isIdleTimerDisabled = true
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        
        streamIngest.removeObserver(self, forKeyPath: "currentFPS")
        
        DispatchQueue.global(qos: .background).async { [weak self] in
            guard let self = self else { return }
            effectStreamIngest?.stopRunning()
        }
        
        if let appActiveObserver = appActiveObserver {
            NotificationCenter.default.removeObserver(appActiveObserver)
        }
        if let appInactiveObserver = appInactiveObserver {
            NotificationCenter.default.removeObserver(appInactiveObserver)
        }
        
        UIApplication.shared.isIdleTimerDisabled = false
    }

    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        requestCameraAuthentication { [weak self] authorized in
            if authorized {
                self?.effectStreamIngest?.createCameraView(self!.cameraPreviewView)
            }
            else {
                self?.showCameraAccessDenied()
            }
        }
        return
    }
    
    override func viewWillTransition(to size: CGSize, with coordinator: UIViewControllerTransitionCoordinator) {
        correctView(to: size)
    }
    
    func requestCameraAuthentication(_ completion: @escaping (_ authorized: Bool)->Void) {
        let status = AVCaptureDevice.authorizationStatus(for: .video)
        if status == .notDetermined {
            AVCaptureDevice.requestAccess(for: .video) { authorized in
                DispatchQueue.main.async {
                    completion(authorized)
                }
            }
        }
        else {
            DispatchQueue.main.async {
                completion(status == .authorized)
            }
        }
    }
    
    func showCameraAccessDenied() {
        DispatchQueue.main.async { [weak self] in
            guard let self = self else { return }
            let alert = UIAlertController(title: "Camera Access Denied", 
                                          message: "Camera access is required. Please enable camera access for the app in Settings -> Privacy -> Camera.",
                                          preferredStyle: .alert)
            
            alert.addAction(UIAlertAction(title: "Dismiss", style: .cancel, handler: { (_) in
                self.navigationController?.popViewController(animated: true)
            }))
            
            self.present(alert, animated: true, completion: nil)
        }
    }
    
    @objc
    func skinSmoothValueChanged(_ sender: UISlider) {
        let intensity = Int(sender.value * 100)
        effectStreamIngest?.setEffects([SkinSmoothEffect(intensity: intensity)])
    }
    
    @objc
    func on(close: UIBarButtonItem) {
        effectStreamIngest = nil
        dismiss(animated: true)
    }
    
    @objc
    func on(switch: UIBarButtonItem) {
        rotateCamera()
    }
    
    @objc
    func on(publish: UIButton) {
        guard let rtmpUrl = Preference.shared.uri, let streamName = Preference.shared.streamName else { return }
        
        if publish.isSelected {
            streamIngest.stopPublish()
            isRunning = false
        } else {
            streamIngest.startPublish(rtmpUrl: rtmpUrl, stream: streamName)
            isRunning = true
        }
        publish.isSelected.toggle()
    }
    
    @objc
    func on(pause: UIButton) {
        guard controlView.publishButton.isSelected else {
            let controller = UIAlertController(title: "Oops",
                                               message: "Publish is not starting",
                                               preferredStyle: .alert)
            
            let okButton = UIAlertAction(title: "OK", style: .destructive)
            controller.addAction(okButton)
            self.present(controller, animated: true)
            return
        }
        
        pause.isSelected.toggle()
        streamIngest.paused = pause.isSelected
    }
    
    func rotateCamera() {
        currentPosition = currentPosition == .back ? .front : .back
        if let camera = AVCaptureDevice.default(.builtInWideAngleCamera, for: .video, position: currentPosition) {
            try? effectStreamIngest?.attachCamera(device: camera)
        }
    }
    
    func correctView(to size: CGSize? = nil) {
        // Set device orientation based on UI
        let height = size?.height ?? UIScreen.main.bounds.height
        let width = size?.width ?? UIScreen.main.bounds.width
        
        cameraPreviewView.center = CGPoint(x: width / 2, y: height / 2)
        
        switch currentDeviceOrientation() {
        case .portrait:
            cameraPreviewView.transform = .identity
        case .portraitUpsideDown:
            cameraPreviewView.transform = CGAffineTransform(rotationAngle: .pi)
        case .landscapeLeft:
            cameraPreviewView.transform = CGAffineTransform(rotationAngle: -.pi / 2)
        case .landscapeRight:
            cameraPreviewView.transform = CGAffineTransform(rotationAngle: .pi / 2)
        default:
            cameraPreviewView.transform = .identity
        }
    }
    
    func currentDeviceOrientation() -> UIDeviceOrientation {
        guard (UIDevice.current.orientation != .portrait && 
               UIDevice.current.orientation != .portraitUpsideDown &&
               UIDevice.current.orientation != .landscapeRight && 
               UIDevice.current.orientation != .landscapeLeft) else {
            return UIDevice.current.orientation
        }
        
        var orientation : UIInterfaceOrientation?
        if #available(iOS 13.0, *) {
            orientation = UIApplication.shared.windows.first?.windowScene?.interfaceOrientation
        } else {
            orientation = UIApplication.shared.statusBarOrientation
        }
        
        switch orientation {
        case .unknown:
            return .portrait
        case .portrait:
            return .portrait
        case .portraitUpsideDown:
            return .portraitUpsideDown
        case .landscapeLeft:
            return .landscapeRight
        case .landscapeRight:
            return .landscapeLeft
        default:
            return .portrait
        }
    }
}

extension EffectStreamIngestViewController {
    
    override public func observeValue(forKeyPath keyPath: String?,
                                      of object: Any?,
                                      change: [NSKeyValueChangeKey: Any]?,
                                      context: UnsafeMutableRawPointer?) {
        if Thread.isMainThread {
            let fps = streamIngest.currentFPS
            let bps = streamIngest.info?.currentBytesPerSecond ?? 0
            infoLabel.text = "FPS: \(fps)\nBytes Per Seconds: \(bps)"
        }
    }
}

extension EffectStreamIngestViewController: EffectStreamIngestDelegate {
    
    func effectStreamIngest(_ ingest: EffectStreamIngest, didChange loadStatus: EffectStreamIngestLoadStatus) {
        if loadStatus == .ready {
            if let effect = ingest.getEffect(with: .skinSmooth) as? SkinSmoothEffect {
                skinSmoothSlider.value = Float(effect.intensity) / 100
            }
        }
    }
}

extension EffectStreamIngestViewController: StreamIngestDelegate {
    
    func streamIngestDidStartPublishing(_ streamIngest: StreamIngest) {
        debugPrint("streamIngestDidStartPublishing")
    }
    
    func streamIngestDidStopPublishing(_ streamIngest: StreamIngest) {
        debugPrint("streamIngestDidStopPublishing")
    }
    
    func streamIngestDidFailToPublish(_ streamIngest: StreamIngest) {
        DispatchQueue.main.async {
            let controller = UIAlertController(title: "Oops",
                                               message: "Fail to publish",
                                               preferredStyle: .alert)
            
            let okButton = UIAlertAction(title: "OK", style: .destructive) { _ in
                self.controlView.publishButton.isSelected.toggle()
            }
            
            controller.addAction(okButton)
            self.present(controller, animated: true)
        }
    }
    
    func reconnect() {
        guard let rtmpUrl = Preference.shared.uri,
              let streamName = Preference.shared.streamName else { return }
        streamIngest.startPublish(rtmpUrl: rtmpUrl, stream: streamName)
    }
}
