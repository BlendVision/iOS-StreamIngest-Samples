//
//  SettingDetailViewController.swift
//  Example
//
//  Created by Tsung Cheng Lo on 2024/1/15.
//

import UIKit
import BVStreamIngest

class SettingsViewController: UITableViewController {
    
    let options: [StreamIngestQuality] = [
        StreamIngestQualityLow(),
        StreamIngestQualityMedium(),
        StreamIngestQualityHigh(),
        StreamIngestQualityAuto()
    ]

    override func viewDidLoad() {
        super.viewDidLoad()

        // Uncomment the following line to preserve selection between presentations
        // self.clearsSelectionOnViewWillAppear = false

        // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
        // self.navigationItem.rightBarButtonItem = self.editButtonItem
        
        title = "Stream Ingest Qualities"
        tableView.register(UITableViewCell.self, forCellReuseIdentifier: "optionCell")
    }

    // MARK: - Table view data source

    override func numberOfSections(in tableView: UITableView) -> Int {
        // #warning Incomplete implementation, return the number of sections
        return 1
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        // #warning Incomplete implementation, return the number of rows
        return options.count
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "optionCell", for: indexPath)
        var configuration = cell.defaultContentConfiguration()
        let option = options[indexPath.row]
        configuration.image = UIImage(systemName: "doc.badge.gearshape")
        configuration.text = option.level.rawValue
        cell.contentConfiguration = configuration
        cell.accessoryType = option.level == Preference.shared.streamIngestQuality.level ? .checkmark : .none
        return cell
    }
    
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        Preference.shared.streamIngestQuality = options[indexPath.row]
        tableView.reloadData()
    }
}
