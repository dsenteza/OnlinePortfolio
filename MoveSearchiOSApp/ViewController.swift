//
//  ViewController.swift
//  DominiqueSenteza-Lab4
//
//  Created by labuser on 7/16/18.
//  Copyright © 2018 DominiqueSenteza. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UICollectionViewDataSource, UICollectionViewDelegate, UISearchBarDelegate, UICollectionViewDelegateFlowLayout{
    
    //OUTLETS
    @IBOutlet weak var navigationBar: UINavigationItem!
    @IBOutlet weak var searchBar: UISearchBar!
    @IBOutlet weak var collectionView: UICollectionView!
    @IBOutlet weak var spinner: UIActivityIndicatorView!
    
    //GLOBAL VARIABLES
    var theData: [Movie] = []
    var favorites: [Movie] = []
    var images: [UIImage] = []
    var myResults: APIResults!
    
    //VIEW DID LOAD
    override func viewDidLoad() {
        super.viewDidLoad()
        //SET LOCAL VARIABLES
        navigationBar.title = "Movies"
        searchBar.delegate = self
        collectionView.delegate = self
        collectionView.dataSource = self
        
        spinner.isHidden = true
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    //***COLLECTION VIEW FUNCTIONS***
    //NUM ITEMS IN SECTION
    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection: Int) -> Int {
        return theData.count
    }
    
    //NUM SECTIONS
    func numberOfSections(in collectionView: UICollectionView) -> Int {
        return 1
    }
    
    //DISPLAY CELLS WITH IMAGES AND TITLES
    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        let cell = collectionView.dequeueReusableCell(withReuseIdentifier: "moviceCell", for: indexPath)
        print("cell count \(theData.count)")
        
        //IMAGE CELL SUBVIEW
        let image:UIImageView = UIImageView(frame: CGRect(x: 0, y: 0, width: cell.frame.width, height: cell.frame.height))
        image.image = images[indexPath.row]
        image.sizeToFit()
        cell.addSubview(image)
        
        //TITLE SUBVIEW
        let point = CGPoint(x: CGFloat(0), y: CGFloat(((cell.frame.height)-((cell.frame.height)/3))))
        let size = CGSize(width: cell.frame.width, height: (cell.frame.height)/3)
        let text:UITextView = UITextView(frame: CGRect(origin: point, size: size))
        text.text = theData[indexPath.row].title
        text.backgroundColor = UIColor.gray
        text.textColor = UIColor.white
        text.sizeToFit()
        cell.addSubview(text)
        
        //SHOW CELL
        return cell
    }
    
    //SEARCHING TMDB
    func searchBarSearchButtonClicked(_ searchBar:UISearchBar){
        theData = []
        images = []
        //REPLACING SPACES WITH %20: https://stackoverflow.com/questions/3439853/replace-occurrences-of-space-in-url
        let searchString = searchBar.text?.addingPercentEncoding(withAllowedCharacters: CharacterSet.urlQueryAllowed)
        let url = URL(string: "https://api.themoviedb.org/3/search/movie?api_key=959eb4093dc3dde86a72eb1742c9cade&language=en-US&query=\(searchString!)&page=1&include_adult=false")
        
        //GRABBING DATA ON BACKEND QUEUE
        DispatchQueue.global().async {
            
            //SHOW AND START ANIMATING SPINNER -- MUST CALL ON MAIN QUEUE
            DispatchQueue.main.async {
                self.spinner.isHidden = false
                self.spinner.startAnimating()
            }
            
            //FETCH JSON
            let data = try! Data(contentsOf: url!)
            self.myResults = try! JSONDecoder().decode(APIResults.self, from: data)
            for result in self.myResults.results{
                self.theData.append(result)
            }
            self.grabImages()
            
            //MUST CALL ON MAIN QUEUE
            DispatchQueue.main.async {
                self.collectionView.reloadData()
                //HIDE AND STOP ANIMATING SPINNER
                self.spinner.stopAnimating()
                self.spinner.isHidden = true
            }
        }
    }
    
    //PULLING IMAGES FROM URL
    func grabImages() {
        for item in theData {
            print("the item loop \(item)")
            let url = URL(string: "https://image.tmdb.org/t/p/w154/\(item.poster_path!)")
            let data = try? Data(contentsOf: url!)
            let image = UIImage(data: data!)
            images.append(image!)
        }
    }
    
    //NAVIGATE TO DETAILEDVC WHEN A CELL IS PRESSED
    func collectionView(_ collectionView: UICollectionView, didSelectItemAt indexPath: IndexPath) {
        //SET VARIABLES
        let detailedView = self.storyboard?.instantiateViewController(withIdentifier: "detailedVC") as! DetailVC
        detailedView.image = images[indexPath.row]
        detailedView.name = theData[indexPath.row].title
        detailedView.releaseDate = theData[indexPath.row].release_date
        detailedView.summary = theData[indexPath.row].overview
        detailedView.rating = theData[indexPath.row].vote_average
        
        //PUSH NEW VIEW CONTROLLER ON TOP
        navigationController?.pushViewController(detailedView, animated: true)
    }
    
}
