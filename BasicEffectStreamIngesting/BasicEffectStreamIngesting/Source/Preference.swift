import UIKit
import BVStreamIngest

struct Preference {
    static var shared = Preference()

    var uri: String? = "rtmp://93ab7d2777517f95b66457199b9fe9d4-main.jcl-prod-coco-d3.centre.kkstream.tech:1935/live/98df564b7b034917a80d2854095c27cf"
    var streamName: String? = "98df564b7b034917a80d2854095c27cf"
    
    static let backgroundColor = UIColor(red: 22.0/255, green: 20.0/255.0, blue: 21.0/255.0, alpha: 1.0)
    
    var streamIngestQuality: StreamIngestQuality = StreamIngestQualityMedium()
}
