//
//  DetailVC.swift
//  DominiqueSenteza-Lab4
//
//  Created by labuser on 7/17/18.
//  Copyright © 2018 DominiqueSenteza. All rights reserved.
//

import Foundation
import UIKit

class DetailVC: UIViewController {
    
    //GLOBAL VARIABLES
    var image: UIImage!
    var name: String! 
    var releaseDate: String!
    var summary: String!
    var rating: Double!
    
    //OUTLETS
    @IBOutlet weak var released: UILabel!
    @IBOutlet weak var avgRating: UILabel!
    @IBOutlet weak var poster: UIImageView!
    @IBOutlet weak var navBar: UINavigationItem!
    @IBOutlet weak var testArea: UITextView!
    
    //VIEW DID LOAD
    override func viewDidLoad() {
        super.viewDidLoad()
        //PULL USER DEFAULTS
        if var favoritesArray = UserDefaults.standard.stringArray(forKey: "key"){
            
        }
        //CREATE NEW ARRAY IF EMPTY
        else {
            var temp :[String] = []
            UserDefaults.standard.set(temp, forKey: "key")
        }
        
        //SET LOCAL VARIABLES
        navigationItem.title = name
        poster.image = image
        testArea.text = summary
        avgRating.text = String(rating)
        released.text = releaseDate
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    //ADD MOVIE TO FAVORITES LIST AND SAVE IN USER DEFAULTS
    @IBAction func addToFavs(_ sender: Any) {
        if var favoritesArray = UserDefaults.standard.stringArray(forKey: "key"){
            for items in favoritesArray {
                if items == name {
                    let alert = UIAlertController(title: "This movie is already in your favorites list", message: " ", preferredStyle: .alert)
                    alert.addAction(UIAlertAction(title: "Ok", style: .cancel, handler: nil))
                    self.present(alert, animated: true)
                    return
                }
            }
            favoritesArray.append(name)
            UserDefaults.standard.set(favoritesArray, forKey: "key")
            let alert = UIAlertController(title: "This movie has been added to your favorites list", message: " ", preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "Ok", style: .cancel, handler: nil))
            self.present(alert, animated: true)
        }
    }
}
