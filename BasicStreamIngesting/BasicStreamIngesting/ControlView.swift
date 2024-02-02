//
//  ControlView.swift
//  Example
//
//  Created by Tsung Cheng Lo on 2024/1/11.
//

import UIKit

extension UIImage {
    
    var largeImage: UIImage? {
        self.withConfiguration(UIImage.SymbolConfiguration(pointSize: 30.0))
    }
    
    var superLargeImage: UIImage? {
        self.withConfiguration(UIImage.SymbolConfiguration(pointSize: 60.0))
    }
}

class ControlView: UIView {
    
    let publishButton: UIButton = {
        let button = UIButton()
        button.setImage(UIImage(systemName: "video.bubble")?.largeImage, for: .normal)
        button.setImage(UIImage(systemName: "video.bubble.fill")?.largeImage, for: .selected)
        return button
    }()
    
    let pauseButton: UIButton = {
        let button = UIButton()
        button.setImage(UIImage(systemName: "pause.circle")?.largeImage, for: .normal)
        button.setImage(UIImage(systemName: "pause.circle.fill")?.largeImage, for: .selected)
        return button
    }()
    
    lazy var stackView: UIStackView = {
        let view = UIStackView(arrangedSubviews: [publishButton, pauseButton])
        view.translatesAutoresizingMaskIntoConstraints = false
        view.distribution = .fillEqually
        return view
    }()
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        
        self.addSubview(stackView)
        NSLayoutConstraint.activate([
            stackView.leadingAnchor.constraint(equalTo: self.leadingAnchor),
            stackView.trailingAnchor.constraint(equalTo: self.trailingAnchor),
            stackView.topAnchor.constraint(equalTo: self.topAnchor),
            stackView.bottomAnchor.constraint(equalTo: self.bottomAnchor)
        ])
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
