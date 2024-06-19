//
//  IngestViewController.swift
//  RTMPusherExample
//
//  Created by Tsung Cheng Lo on 2024/1/9.
//

import UIKit
import AVFoundation
import BVStreamIngest

class IngestViewController: UIViewController {
    
    var stream: StreamIngest
    
    var previewView: StreamRenderView!
    
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
        return view
    }()
    
    private var currentPosition: AVCaptureDevice.Position = .back
    
    init(streamIngest: StreamIngest) {
        self.stream = streamIngest
        super.init(nibName: nil, bundle: nil)
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        title = "Live Room"
        
        view.backgroundColor = Preference.backgroundColor
        
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
        
        previewView = StreamRenderView()
        previewView.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(previewView)
        
        NSLayoutConstraint.activate([
            previewView.leadingAnchor.constraint(equalTo: view.leadingAnchor),
            previewView.trailingAnchor.constraint(equalTo: view.trailingAnchor),
            previewView.topAnchor.constraint(equalTo: view.topAnchor),
            previewView.bottomAnchor.constraint(equalTo: view.bottomAnchor)
        ])
        
        controlView.publishButton.addTarget(self, action: #selector(on(publish:)), for: .touchUpInside)
        controlView.pauseButton.addTarget(self, action: #selector(on(pause:)), for: .touchUpInside)
        
        view.addSubview(controlView)
        NSLayoutConstraint.activate([
            controlView.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor),
            controlView.leadingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.leadingAnchor),
            controlView.trailingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.trailingAnchor)
        ])
        
        view.addSubview(infoLabel)
        NSLayoutConstraint.activate([
            infoLabel.leadingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.leadingAnchor),
            infoLabel.trailingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.trailingAnchor),
            infoLabel.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor, constant: -44.0),
            infoLabel.heightAnchor.constraint(equalToConstant: 88.0)
        ])

        // Do any additional setup after loading the view.
        NotificationCenter.default.addObserver(
            self,
            selector: #selector(on(_:)),
            name: UIDevice.orientationDidChangeNotification,
            object: nil
        )
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        stream.delegate = self
        stream.addObserver(self, forKeyPath: "currentFPS", options: .new, context: nil)
        
        let camera = AVCaptureDevice.default(.builtInWideAngleCamera, for: .video, position: currentPosition)
        stream.attachCamera(camera, channel: 0) { error in
            debugPrint("attaching camera with error=\(String(describing: error))")
        }
        
        stream.attachAudio(AVCaptureDevice.default(for: .audio)) { error in
            debugPrint("attaching audio with error=\(String(describing: error))")
        }
        
        previewView.attachStream(stream)
        UIApplication.shared.isIdleTimerDisabled = true
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        
        stream.delegate = nil
        stream.removeObserver(self, forKeyPath: "currentFPS")
        stream.close()
        stream.attachCamera(nil, channel: 0)
        stream.attachAudio(nil)
        
        UIApplication.shared.isIdleTimerDisabled = false
    }
    
    @objc
    func on(_ sender: Notification) {
        let scene = UIApplication.shared.connectedScenes.first as? UIWindowScene
        stream.videoOrientation = scene?.interfaceOrientation ?? .unknown
    }
    
    @objc
    func on(publish: UIButton) {
        guard let rtmpUrl = Preference.shared.uri, let streamName = Preference.shared.streamName else { return }
        
        if publish.isSelected {
            stream.stopPublish()
        } else {
            stream.startPublish(rtmpUrl: rtmpUrl, stream: streamName)
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
        stream.paused = pause.isSelected
    }
    
    @objc
    func on(close: UIBarButtonItem) {
        dismiss(animated: true)
    }
    
    @objc
    func on(switch: UIBarButtonItem) {
        switchCamera()
    }
    
    func switchCamera() {
        currentPosition = currentPosition == .back ? .front : .back
        let camera = AVCaptureDevice.default(.builtInWideAngleCamera, for: .video, position: currentPosition)
        stream.attachCamera(camera, channel: 0)
    }
}

extension IngestViewController {
    
    override public func observeValue(forKeyPath keyPath: String?,
                                      of object: Any?,
                                      change: [NSKeyValueChangeKey: Any]?,
                                      context: UnsafeMutableRawPointer?) {
        if Thread.isMainThread {
            let fps = stream.currentFPS
            let bps = stream.info?.currentBytesPerSecond ?? 0
            infoLabel.text = "FPS: \(fps)\nBytes Per Seconds: \(bps)"
        }
    }
}

extension IngestViewController: StreamIngestDelegate {
    
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
}
