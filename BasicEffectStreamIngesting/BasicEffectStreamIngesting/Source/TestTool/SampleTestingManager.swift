//
//  SampleTestingManager.swift
//  StreamIngestExample
//
//  Created by Sunny on 2024/8/26.
//

import Foundation

class SampleTestingManager {
    static let shared = SampleTestingManager()
    private(set) var crashButtonState: CrashButtonState
    
    struct CrashButtonState {
        var isEnabled: Bool
    }
    
    private init() {
        crashButtonState = CrashButtonState(isEnabled: false)
    }
    
    func setCrashButtonEnabled(_ enabled: Bool) -> CrashButtonState {
        crashButtonState = CrashButtonState(isEnabled: enabled)
        return crashButtonState
    }
}

