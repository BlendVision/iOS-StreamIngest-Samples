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
    
    var streamIngest: StreamIngest
    
    var cameraPreviewView: CameraPreviewView?
    
    lazy var skinSmoothSlider: UISlider = {
        let slider = UISlider()
        slider.translatesAutoresizingMaskIntoConstraints = false
        return slider
    }()
    
    lazy var skinToneSlider: UISlider = {
        let slider = UISlider()
        slider.translatesAutoresizingMaskIntoConstraints = false
        return slider
    }()
    
    lazy var skinSmoothLabel: UILabel = {
        let label = UILabel()
        label.text = "✨ 磨皮"
        label.textColor = .white
        label.translatesAutoresizingMaskIntoConstraints = false
        return label
    }()
    
    lazy var skinToneLabel: UILabel = {
        let label = UILabel()
        label.text = "🎨 膚色"
        label.textColor = .white
        label.translatesAutoresizingMaskIntoConstraints = false
        return label
    }()
    
    lazy var skinSmoothValueLabel: UILabel = {
        let label = UILabel()
        label.text = "0%"
        label.textColor = .white
        label.translatesAutoresizingMaskIntoConstraints = false
        return label
    }()
    
    lazy var skinToneValueLabel: UILabel = {
        let label = UILabel()
        label.text = "0%"
        label.textColor = .white
        label.translatesAutoresizingMaskIntoConstraints = false
        return label
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
    
    private let spinner = UIActivityIndicatorView(style: .large)
    
    private let logView = LogViewController()
    
    private var currentBufferStatus: StreamIngestBufferState?
    
    private var scaleModeIconName: String {
        cameraPreviewView?.scaleMode == .aspectFill ? "rectangle.compress.vertical" : "rectangle.expand.vertical"
    }
    
    private var logViewIconName: String {
        logView.view.isHidden ? "eye.slash" : "eye"
    }
    
    private var beautifyIconName: String {
        effectStreamIngest?.isBeautifyEnabled == true ? "bubbles.and.sparkles.fill" : "bubbles.and.sparkles"
    }
    
    init(streamIngest: StreamIngest) {
        self.streamIngest = streamIngest
        super.init(nibName: nil, bundle: nil)
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    deinit {
        debugPrint("The object \(self) has been deallocated")
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
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
        
        if SampleTestingManager.shared.crashButtonState.isEnabled {
            navigationItem.leftBarButtonItems?.append(UIBarButtonItem(title: "Crash！",
                                                                      style: .plain,
                                                                      target: self,
                                                                      action: #selector(self.crashButtonTapped(_:))))
        }
        
        navigationItem.rightBarButtonItems = [
            UIBarButtonItem(
                image: UIImage(systemName: "arrow.triangle.2.circlepath.camera.fill"),
                style: .plain,
                target: self,
                action: #selector(on(switch:))
            ),
            UIBarButtonItem(
                image: UIImage(systemName: beautifyIconName),
                style: .plain,
                target: self,
                action: #selector(on(beautify:))
            ),
            UIBarButtonItem(
                image: UIImage(systemName: scaleModeIconName),
                style: .plain,
                target: self,
                action: #selector(changeMode)
            ),
            UIBarButtonItem(
                image: UIImage(systemName: logViewIconName),
                style: .plain,
                target: self,
                action: #selector(showLogView))
        ]
        
        // Do any additional setup after loading the view.
        requestCameraAuthentication { [weak self] authorized in
            if authorized {
                guard let self = self else { return }
                guard let previewView = effectStreamIngest?.createCameraView(
                    mode: .aspectFit
                ) else { return }
                
                setupCameraView(previewView)
                setupLogView()
                setupViews()
            }
            else {
                self?.showCameraAccessDenied()
            }
        }
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        streamIngest.addObserver(self, forKeyPath: "currentFPS", options: .new, context: nil)
        
        if let audio = AVCaptureDevice.default(for: .audio) {
            try? effectStreamIngest?.attachAudio(device: audio)
        }
        
        if let camera = AVCaptureDevice.default(.builtInWideAngleCamera,
                                                for: .video,
                                                position: currentPosition) {
            try? effectStreamIngest?.attachCamera(device: camera)
            
            DispatchQueue.global(qos: .background).async { [weak self] in
                guard let self = self else { return }
                effectStreamIngest?.startRunning()
            }
        }
        
        appActiveObserver = NotificationCenter.default.addObserver(
            forName: UIApplication.didBecomeActiveNotification,
            object: nil,
            queue: nil
        ) { [weak self] (notification) in
            
            DispatchQueue.global(qos: .background).async { [weak self] in
                guard let self = self else { return }
                self.effectStreamIngest?.startRunning()
                
                if isRunning {
                    self.reconnect()
                }
            }
        }
        
        appInactiveObserver = NotificationCenter.default.addObserver(
            forName: UIApplication.didEnterBackgroundNotification,
            object: nil,
            queue: nil
        ) { [weak self] (notification) in
            
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
            self.appActiveObserver = nil
        }
        if let appInactiveObserver = appInactiveObserver {
            NotificationCenter.default.removeObserver(appInactiveObserver)
            self.appActiveObserver = nil
        }
        
        UIApplication.shared.isIdleTimerDisabled = false
    }
    
    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
    }
    
    override func viewWillTransition(to size: CGSize, with coordinator: UIViewControllerTransitionCoordinator) {
        let scene = UIApplication.shared.connectedScenes.first as? UIWindowScene
        streamIngest.videoOrientation = scene?.interfaceOrientation ?? .unknown
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
        skinSmoothValueLabel.text = "\(intensity)%"
        effectStreamIngest?.setEffects([SkinSmoothEffect(intensity: intensity)])
    }
    
    @objc
    func skinToneValueChanged(_ sender: UISlider) {
        let intensity = Int(sender.value * 100)
        skinToneValueLabel.text = "\(intensity)%"
        effectStreamIngest?.setEffects([SkinToneEffect(intensity: intensity)])
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
    func on(beautify: UIBarButtonItem) {
        effectStreamIngest?.isBeautifyEnabled.toggle()
        syncEffectSlidersWithState()
        beautify.image = UIImage(systemName: beautifyIconName)
    }
    
    @objc
    func changeMode(sender: UIBarButtonItem) {
        changeScaleMode()
        sender.image = UIImage(systemName: scaleModeIconName)
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
        cameraPreviewView?.activateCamera(isFrontCamera: currentPosition == .front)
        if let camera = AVCaptureDevice.default(.builtInWideAngleCamera, for: .video, position: currentPosition) {
            try? effectStreamIngest?.attachCamera(device: camera)
        }
    }
    
    private func setupCameraView(_ preview: CameraPreviewView) {
        if let oldPreview = cameraPreviewView,
           let index = self.view.subviews.firstIndex(of: oldPreview) {
            oldPreview.removeFromSuperview()
            self.view.insertSubview(preview, at: index)
        } else {
            self.view.addSubview(preview)
        }
        
        preview.activateCamera(isFrontCamera: currentPosition == .front)
        
        preview.translatesAutoresizingMaskIntoConstraints = false
        NSLayoutConstraint.activate([
            preview.leadingAnchor.constraint(equalTo: self.view.leadingAnchor),
            preview.trailingAnchor.constraint(equalTo: self.view.trailingAnchor),
            preview.topAnchor.constraint(equalTo: self.view.topAnchor),
            preview.bottomAnchor.constraint(equalTo: self.view.bottomAnchor)
        ])
        self.cameraPreviewView = preview
    }
    
    private func setupLogView() {
        guard let logView = logView.view else { return }
        logView.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(logView)
        NSLayoutConstraint.activate([
            logView.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor),
            logView.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor),
            logView.leadingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.leadingAnchor),
            logView.trailingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.trailingAnchor)
        ])
    }
    
    private func setupViews() {
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
        
        view.addSubview(skinSmoothLabel)
        view.addSubview(skinSmoothSlider)
        view.addSubview(skinSmoothValueLabel)
        NSLayoutConstraint.activate([
            skinSmoothLabel.leadingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.leadingAnchor, constant: 16),
            skinSmoothLabel.bottomAnchor.constraint(equalTo: infoLabel.topAnchor, constant: -16),
            
            skinSmoothSlider.leadingAnchor.constraint(equalTo: skinSmoothLabel.trailingAnchor, constant: 16),
            skinSmoothSlider.trailingAnchor.constraint(equalTo: skinSmoothValueLabel.leadingAnchor, constant: -8),
            skinSmoothSlider.centerYAnchor.constraint(equalTo: skinSmoothLabel.centerYAnchor),
            
            skinSmoothValueLabel.trailingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.trailingAnchor, constant: -16),
            skinSmoothValueLabel.centerYAnchor.constraint(equalTo: skinSmoothLabel.centerYAnchor),
            skinSmoothValueLabel.widthAnchor.constraint(equalToConstant: 50)
        ])
        
        view.addSubview(skinToneLabel)
        view.addSubview(skinToneSlider)
        view.addSubview(skinToneValueLabel)
        NSLayoutConstraint.activate([
            skinToneLabel.leadingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.leadingAnchor, constant: 16),
            skinToneLabel.bottomAnchor.constraint(equalTo: skinSmoothLabel.topAnchor, constant: -16),
            
            skinToneSlider.leadingAnchor.constraint(equalTo: skinToneLabel.trailingAnchor, constant: 16),
            skinToneSlider.trailingAnchor.constraint(equalTo: skinToneValueLabel.leadingAnchor, constant: -8),
            skinToneSlider.centerYAnchor.constraint(equalTo: skinToneLabel.centerYAnchor),
            
            skinToneValueLabel.trailingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.trailingAnchor, constant: -16),
            skinToneValueLabel.centerYAnchor.constraint(equalTo: skinToneLabel.centerYAnchor),
            skinToneValueLabel.widthAnchor.constraint(equalToConstant: 50)
        ])
        
        skinSmoothSlider.addTarget(self, action: #selector(skinSmoothValueChanged(_:)), for: .valueChanged)
        skinToneSlider.addTarget(self, action: #selector(skinToneValueChanged(_:)), for: .valueChanged)
        
        spinner.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(spinner)
        NSLayoutConstraint.activate([
            spinner.centerXAnchor.constraint(equalTo: view.centerXAnchor),
            spinner.centerYAnchor.constraint(equalTo: view.centerYAnchor)
        ])
        
        syncEffectSlidersWithState()
    }
    
    func syncEffectSlidersWithState() {
        if let effect = effectStreamIngest?.getEffect(with: .skinSmooth) as? SkinSmoothEffect {
            skinSmoothSlider.value = Float(effect.intensity) / 100
            skinSmoothValueLabel.text = "\(effect.intensity)%"
        }
        if let effect = effectStreamIngest?.getEffect(with: .skinTone) as? SkinToneEffect {
            skinToneSlider.value = Float(effect.intensity) / 100
            skinToneValueLabel.text = "\(effect.intensity)%"
        }
    }
}

extension EffectStreamIngestViewController: EffectStreamIngestDelegate {
    
    func effectStreamIngest(
        _ effectStreamIngest: EffectStreamIngest,
        didOutputVideo sampleBuffer: CMSampleBuffer
    ) -> CMSampleBuffer {
        sampleBuffer
    }
    
    func effectStreamIngest(
        _ effectStreamIngest: EffectStreamIngest,
        didOutputAudio sampleBuffer: CMSampleBuffer
    ) -> CMSampleBuffer {
        sampleBuffer
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
            let queuedBytes = String(currentBufferStatus?.bufferInfo.queuedBytes ?? 0)
            infoLabel.text = """
                           FPS: \(fps)
                           Bytes Per Second: \(bps)
                           Queued Bytes: \(queuedBytes)
                           """
        }
    }
}

extension EffectStreamIngestViewController: StreamIngestDelegate {
    func streamIngestDidUpdateBufferStatus(
        _ streamIngest: BVStreamIngest.StreamIngest,
        with status: StreamIngestBufferState
    ) {
        self.currentBufferStatus = status
        switch status.status {
        case .normal:
            self.view.backgroundColor = UIColor.green.withAlphaComponent(0.3)
        case .warning:
            self.view.backgroundColor = UIColor.yellow.withAlphaComponent(0.3)
        case .critical:
            self.view.backgroundColor = UIColor.red.withAlphaComponent(0.3)
        }
    }
    
    func streamIngestDidStartPublishing(_ streamIngest: StreamIngest) {
        debugPrint("streamIngestDidStartPublishing")
        logView.addNewLog("streamIngestDidStartPublishing")
    }
    
    func streamIngestDidStopPublishing(_ streamIngest: StreamIngest) {
        debugPrint("streamIngestDidStopPublishing")
        logView.addNewLog("streamIngestDidStopPublishing")
    }
    
    func streamIngestDidFailToPublish(_ streamIngest: StreamIngest, with error: StreamIngestErrorEvent) {
        DispatchQueue.main.async {
            let controller = UIAlertController(title: "Oops, Fail to publish",
                                               message: error.code,
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
    
    func streamIngestDidStartRetrying(_ streamIngest: BVStreamIngest.StreamIngest) {
        DispatchQueue.main.async {
            debugPrint("Retrying connection...")
            self.logView.addNewLog("Retrying connection...")
            self.spinner.startAnimating()
        }
    }
    
    func streamIngestDidStopRetrying(_ streamIngest: BVStreamIngest.StreamIngest) {
        DispatchQueue.main.async {
            debugPrint("Retrying connection stopped.")
            self.logView.addNewLog("Retrying connection stopped.")
            self.spinner.stopAnimating()
            self.isRunning = false
        }
    }
}

extension EffectStreamIngestViewController {
    @objc
    func showLogView(sender: UIBarButtonItem) {
        logView.view.isHidden.toggle()
        sender.image = UIImage(systemName: logViewIconName)
    }
    
    func changeScaleMode() {
        cameraPreviewView?.switchScaleMode()
        if let button = navigationItem.rightBarButtonItems?.first(where: { $0.tag == 1 }) {
            button.image = UIImage(systemName: scaleModeIconName)
        }
    }
    
    @objc
    func crashButtonTapped(_ sender: AnyObject) {
        let numbers = [0]
        let _ = numbers[1]
    }
}
