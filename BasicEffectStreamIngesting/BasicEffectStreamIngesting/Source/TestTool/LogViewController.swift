//
//  LogViewController.swift
//  StreamIngestExample
//
//  Created by Sunny on 2024/9/27.
//

import UIKit

class LogViewController: UIViewController {
    
    let tableView = UITableView()
    let maxLogs = 20
    private var logs: [String] = []
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.view.backgroundColor = UIColor.black.withAlphaComponent(0.1)
        
        setupTableView()
    }
    
    func addNewLog(_ log: String) {
        DispatchQueue.main.async { [self] in
            let innerLog = "\(self.getCurrentTime()) - " + log
            if logs.count >= self.maxLogs {
                reachLimitCount()
            }
            logs.insert(innerLog, at: 0)
            let topIndex = IndexPath(row: 0, section: 0)
            self.tableView.insertRows(at: [topIndex], with: .automatic)
        }
    }
    
    private func setupTableView() {
        tableView.backgroundColor = .clear
        tableView.isUserInteractionEnabled = false
        tableView.frame = self.view.bounds
        tableView.separatorStyle = .none
        tableView.dataSource = self
        self.view.addSubview(tableView)
        
        tableView.translatesAutoresizingMaskIntoConstraints = false
        NSLayoutConstraint.activate([
            tableView.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 0),
            tableView.leadingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.leadingAnchor, constant: 0),
            tableView.trailingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.trailingAnchor, constant: 0),
            tableView.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor, constant: 0),
        ])
    }
    
    private func reachLimitCount() {
        logs.removeLast()
        let lastIndexPath = IndexPath(row: self.logs.count, section: 0)
        self.tableView.deleteRows(at: [lastIndexPath], with: .automatic)
    }
    
    private func getCurrentTime() -> String {
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "HH:mm:ss"
        let currentTime = Date()
        return dateFormatter.string(from: currentTime)
    }
}

extension LogViewController: UITableViewDataSource {
    // MARK: - UITableViewDataSource
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return logs.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = UITableViewCell(style: .default, reuseIdentifier: nil)
        cell.textLabel?.text = logs[indexPath.row]
        cell.backgroundColor = .clear
        return cell
    }
}
