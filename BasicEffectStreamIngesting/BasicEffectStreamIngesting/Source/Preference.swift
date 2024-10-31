import UIKit
import BVStreamIngest

struct Preference {
    static var shared = Preference()

    var uri: String? = "rtmp://7c2f5dc49e9c3337ca32b574041d69e4-main.jcl-prod-coco-d3.centre.kkstream.tech:1935/live"
    
    var streamName: String? = "0ea216396fcd429eab7dfc42ddfc23f4"
    
    var licenseKey: String = "Your-License-Key"
    
    static let backgroundColor = UIColor(red: 22.0/255, green: 20.0/255.0, blue: 21.0/255.0, alpha: 1.0)
    
    var streamIngestQuality: StreamIngestQuality = StreamIngestQualityAuto()
}
