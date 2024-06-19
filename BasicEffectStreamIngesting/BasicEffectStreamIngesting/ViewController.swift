//
//  ViewController.swift
//  Example
//
//  Created by Tsung Cheng Lo on 2024/1/10.
//

import UIKit
import BVStreamIngest

class ViewController: UIViewController {
    
    let licenseTextField: UITextField = {
        let field = UITextField()
        field.tag = 0
        field.translatesAutoresizingMaskIntoConstraints = false
        field.text = Preference.shared.licenseKey
        field.backgroundColor = .darkText
        field.textColor = .white
        field.clearButtonMode = .whileEditing
        return field
    }()
    
    let urlTextField: UITextField = {
        let field = UITextField()
        field.tag = 1
        field.translatesAutoresizingMaskIntoConstraints = false
        field.text = Preference.shared.uri
        field.backgroundColor = .darkText
        field.textColor = .white
        field.clearButtonMode = .whileEditing
        return field
    }()
    
    let streamNameTextField: UITextField = {
        let field = UITextField()
        field.tag = 2
        field.translatesAutoresizingMaskIntoConstraints = false
        field.text = Preference.shared.streamName
        field.backgroundColor = .darkText
        field.textColor = .white
        field.clearButtonMode = .whileEditing
        return field
    }()

    let goLiveButton: UIButton = {
        let button = UIButton()
        button.setImage(UIImage(systemName: "livephoto.play")?.superLargeImage, for: .normal)
        return button
    }()
    
    let effectGoLiveButton: UIButton = {
        let button = UIButton()
        button.setImage(UIImage(systemName: "camera.filters")?.superLargeImage, for: .normal)
        return button
    }()
    
    let settingButton: UIButton = {
        let button = UIButton()
        button.setImage(UIImage(systemName: "gearshape")?.superLargeImage, for: .normal)
        return button
    }()
    
    lazy var stackView: UIStackView = {
        let view = UIStackView(arrangedSubviews: [goLiveButton, effectGoLiveButton, settingButton])
        view.translatesAutoresizingMaskIntoConstraints = false
        view.distribution = .fillEqually
        return view
    }()

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        
        view.backgroundColor = Preference.backgroundColor
        
        licenseTextField.delegate = self
        view.addSubview(licenseTextField)
        NSLayoutConstraint.activate([
            licenseTextField.topAnchor.constraint(
                equalTo: view.safeAreaLayoutGuide.topAnchor
            ),
            licenseTextField.leadingAnchor.constraint(
                equalTo: view.safeAreaLayoutGuide.leadingAnchor, constant: 16.0
            ),
            licenseTextField.trailingAnchor.constraint(
                equalTo: view.safeAreaLayoutGuide.trailingAnchor, constant: -16.0
            ),
            licenseTextField.heightAnchor.constraint(
                equalToConstant: 44.0
            )
        ])
        
        urlTextField.delegate = self
        view.addSubview(urlTextField)
        NSLayoutConstraint.activate([
            urlTextField.topAnchor.constraint(
                equalTo: licenseTextField.bottomAnchor, constant: 8.0
            ),
            urlTextField.leadingAnchor.constraint(
                equalTo: view.safeAreaLayoutGuide.leadingAnchor, constant: 16.0
            ),
            urlTextField.trailingAnchor.constraint(
                equalTo: view.safeAreaLayoutGuide.trailingAnchor, constant: -16.0
            ),
            urlTextField.heightAnchor.constraint(
                equalToConstant: 44.0
            )
        ])
        
        streamNameTextField.delegate = self
        view.addSubview(streamNameTextField)
        NSLayoutConstraint.activate([
            streamNameTextField.topAnchor.constraint(
                equalTo: urlTextField.bottomAnchor, constant: 8.0
            ),
            streamNameTextField.leadingAnchor.constraint(
                equalTo: view.safeAreaLayoutGuide.leadingAnchor, constant: 16.0
            ),
            streamNameTextField.trailingAnchor.constraint(
                equalTo: view.safeAreaLayoutGuide.trailingAnchor, constant: -16.0
            ),
            streamNameTextField.heightAnchor.constraint(
                equalToConstant: 44.0
            )
        ])
        
        goLiveButton.addTarget(self, action: #selector(on(goLive:)), for: .touchUpInside)
        effectGoLiveButton.addTarget(self, action: #selector(on(effectGoLive:)), for: .touchUpInside)
        settingButton.addTarget(self, action: #selector(on(setting:)), for: .touchUpInside)
        
        view.addSubview(stackView)
        NSLayoutConstraint.activate([
            stackView.leadingAnchor.constraint(equalTo: view.leadingAnchor),
            stackView.trailingAnchor.constraint(equalTo: view.trailingAnchor),
            stackView.centerYAnchor.constraint(equalTo: view.centerYAnchor)
        ])
    }
    
    @objc
    func on(goLive: UIButton) {
        Task {
            do {
                guard let licenseKey = licenseTextField.text, licenseKey.count > 0 else {
                    showAlert(with: -999, message: "License Key is empty")
                    return
                }
                let config = StreamIngestConfig(key: licenseKey)
                guard let streamIngest = try await createStreamIngest(with: config) else { return }
                
                let liveController = IngestViewController(streamIngest: streamIngest)
                let navController = UINavigationController(rootViewController: liveController)
                navController.modalPresentationStyle = .fullScreen
                present(navController, animated: true)
            } catch {
                let errorCode = (error as NSError).code
                let errorMessage = (error as NSError).domain
                showAlert(with: errorCode, message: errorMessage)
            }
        }
    }
    
    @objc
    func on(setting: UIButton) {
        let settingViewController = SettingsViewController()
        let navController = UINavigationController(rootViewController: settingViewController)
        present(navController, animated: true)
    }
    
    @objc
    func on(effectGoLive: UIButton) {
        Task {
            do {
                guard let licenseKey = licenseTextField.text, licenseKey.count > 0 else {
                    showAlert(with: -999, message: "License Key is empty")
                    return
                }
                let config = StreamIngestConfig(key: licenseKey)
                guard let streamIngest = try await createStreamIngest(with: config) else { return }
                
                let liveController = EffectStreamIngestViewController(streamIngest: streamIngest)
                let navController = UINavigationController(rootViewController: liveController)
                navController.modalPresentationStyle = .fullScreen
                present(navController, animated: true)
            } catch {
                let errorCode = (error as NSError).code
                let errorMessage = (error as NSError).domain
                showAlert(with: errorCode, message: errorMessage)
            }
        }
    }
    
    func createStreamIngest(with config: StreamIngestConfig) async throws -> StreamIngest? {
        let stream = try await StreamIngest.create(with: config)
        let quality = Preference.shared.streamIngestQuality
        stream?.videoSize = quality.videoSize
        stream?.videoBitrate = quality.videoBitRate
        stream?.audioBitrate = quality.audioBitRate
        return stream
    }
    
    func showAlert(with code: Int, message: String) {
        let controller = UIAlertController(title: "Error",
                                           message: "\(message) (\(code))",
                                           preferredStyle: .alert)
        let action = UIAlertAction(title: "OK", style: .cancel)
        controller.addAction(action)
        present(controller, animated: true)
    }
}

extension ViewController: UITextFieldDelegate {
    
    func textFieldDidEndEditing(_ textField: UITextField) {
        if textField.tag == 0 {
            Preference.shared.licenseKey = textField.text!
        } else if textField.tag == 1 {
            Preference.shared.uri = textField.text
        } else {
            Preference.shared.streamName = textField.text
        }
    }
}
