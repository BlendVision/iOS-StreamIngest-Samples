//
//  ViewController.swift
//  BasicStreamIngesting
//
//  Created by Tsung Cheng Lo on 2024/1/18.
//

import UIKit
import BVStreamIngest

class ViewController: UIViewController {
    
    let urlTextField: UITextField = {
        let field = UITextField()
        field.tag = 0
        field.translatesAutoresizingMaskIntoConstraints = false
        field.text = Preference.shared.uri
        field.backgroundColor = .darkText
        field.textColor = .white
        field.clearButtonMode = .whileEditing
        return field
    }()
    
    let streamNameTextField: UITextField = {
        let field = UITextField()
        field.tag = 1
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
    
    let settingButton: UIButton = {
        let button = UIButton()
        button.setImage(UIImage(systemName: "gearshape")?.superLargeImage, for: .normal)
        return button
    }()
    
    lazy var stackView: UIStackView = {
        let view = UIStackView(arrangedSubviews: [goLiveButton, settingButton])
        view.translatesAutoresizingMaskIntoConstraints = false
        view.distribution = .fillEqually
        return view
    }()

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        
        view.backgroundColor = Preference.backgroundColor
        
        urlTextField.delegate = self
        view.addSubview(urlTextField)
        NSLayoutConstraint.activate([
            urlTextField.topAnchor.constraint(
                equalTo: view.safeAreaLayoutGuide.topAnchor
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
        let liveController = IngestViewController()
        let navController = UINavigationController(rootViewController: liveController)
        navController.modalPresentationStyle = .fullScreen
        present(navController, animated: true)
    }
    
    @objc
    func on(setting: UIButton) {
        let settingViewController = SettingsViewController()
        let navController = UINavigationController(rootViewController: settingViewController)
        present(navController, animated: true)
    }
}

extension ViewController: UITextFieldDelegate {
    
    func textFieldDidEndEditing(_ textField: UITextField) {
        if textField.tag == 0 {
            guard textField.text?.hasPrefix("rtmp://") == true else {
                let controller = UIAlertController(title: "Oops",
                                                   message: "Invalid URL",
                                                   preferredStyle: .alert)
                let okButton = UIAlertAction(title: "OK", style: .destructive)
                controller.addAction(okButton)
                present(controller, animated: true)
                return
            }
            
            Preference.shared.uri = textField.text
        } else {
            guard textField.text?.isEmpty == true else {
                let controller = UIAlertController(title: "Oops",
                                                   message: "Invalid Stream Name",
                                                   preferredStyle: .alert)
                let okButton = UIAlertAction(title: "OK", style: .destructive)
                controller.addAction(okButton)
                present(controller, animated: true)
                return
            }
            
            Preference.shared.streamName = textField.text
        }
    }
}
