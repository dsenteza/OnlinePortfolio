//
//  FavoritesVC.swift
//  DominiqueSenteza-Lab4
//
//  Created by labuser on 7/17/18.
//  Copyright © 2018 DominiqueSenteza. All rights reserved.
//

import Foundation
import UIKit

class FavoritesVC: UIViewController,UITableViewDataSource, UITableViewDelegate {

    //OUTLET AND GLOBAL VARIABLES
    @IBOutlet weak var tableView: UITableView!
    var index = 0
    var values: [String]! = [] {
        didSet {
            tableView.reloadData()
        }
    }
    
    //VIEW DID LOAD
    override func viewDidLoad() {
        super.viewDidLoad()
        //SETUP THE TABLEVIEW
        tableView.dataSource = self
        tableView.delegate = self
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    //RUNS WHENEVER SWITCH TO FAVORITES TAB
    override func viewWillAppear(_ animated: Bool) {
        //PULL USER DEFAULTS
        if var favoritesArray = UserDefaults.standard.stringArray(forKey: "key"){
            values = favoritesArray
        }
    }
    
    //***TABLEVIEW FUNCTIONS***
    //NUM ROWS
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return values.count
    }

    //TEXT IN EACH ROW
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = UITableViewCell(style: .subtitle, reuseIdentifier: nil)
        cell.textLabel?.text = values[indexPath.row]
        return cell
    }
    
    //WHEN A CELL IS CLICKED -- SHOW ALERT ASKING USER IF THEY WOULD LIKE TO DELETE
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        index = indexPath.row
        let alert = UIAlertController(title: "Would you like to delete this movie from your favorites list?", message: " ", preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "Yes", style: .default, handler: remove))
        alert.addAction(UIAlertAction(title: "No", style: .cancel, handler: nil))
        self.present(alert, animated: true)
    }
    
    //REMOVES DELETED MOVIE FROM LOCAL ARRAY AND USER DEFAULTS
    func remove(action: UIAlertAction) {
        var favoritesArray = UserDefaults.standard.stringArray(forKey: "key")
        favoritesArray?.remove(at: index)
        UserDefaults.standard.set(favoritesArray, forKey: "key")
        values = favoritesArray
    }

}
