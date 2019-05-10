//
//  ViewController.swift
//  DominiqueSenteza-Lab2
//
//  Created by labuser on 6/26/18.
//  Copyright © 2018 EricMason. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    //OUTLETS
    @IBOutlet weak var alertBox: UILabel!
    @IBOutlet weak var image: UIImageView!
    @IBOutlet weak var background: UIView!
    @IBOutlet weak var happyNum: UILabel!
    @IBOutlet weak var foodNum: UILabel!
    @IBOutlet weak var happyBar: DisplayView!
    @IBOutlet weak var foodBar: DisplayView!
    
    //INSTANCE OF EACH ANIMAL
    var kitty = Cat(numPlay :0, numFed : 0, image : #imageLiteral(resourceName: "cat"), color : UIColor.blue)
    var doggy = Dog(numPlay :0, numFed : 0, image : #imageLiteral(resourceName: "dog"), color : UIColor.red)
    var birdy = Bird(numPlay :0, numFed : 0, image : #imageLiteral(resourceName: "bird"), color : UIColor.yellow)
    var bun = Bunny(numPlay :0, numFed : 0, image : #imageLiteral(resourceName: "bunny"), color : UIColor.green)
    var fishy = Fish(numPlay :0, numFed : 0, image : #imageLiteral(resourceName: "fish"), color : UIColor.purple)
    
    //MAIN STRUCT INITIALIZATION
    var coolPets = myPets()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        alertBox.text = "Welcome to your pet app! Select a pet to get started."
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be rec
    }

    //UPDATE THE BARS
    func updateBars() {
        switch coolPets.active {
            case "doggy":
                image.isHidden = false
                //HAPPY BAR
                if (coolPets.doggy.numPlay < 10 && coolPets.doggy.numPlay > 0) {
                    let dogPlayFloat = CGFloat((coolPets.doggy.numPlay/10.0))
                    happyBar.animateValue(to: dogPlayFloat)
                }
                //FOOD BAR
                if (coolPets.doggy.numFed < 10 && coolPets.doggy.numFed > 0){
                    let dogFoodFloat = CGFloat((coolPets.doggy.numFed)/10.0)
                    foodBar.animateValue(to: dogFoodFloat)
                }
            case "kitty":
                image.isHidden = false
                //HAPPY BAR
                if (coolPets.kitty.numPlay < 10 && coolPets.kitty.numPlay > 0) {
                    let catPlayFloat = CGFloat((coolPets.kitty.numPlay)/10.0)
                    happyBar.animateValue(to: catPlayFloat)
                }
                //FOOD BAR
                if (coolPets.kitty.numFed < 10 && coolPets.kitty.numFed > 0){
                    let catFoodFloat = CGFloat((coolPets.kitty.numFed)/10.0)
                    foodBar.animateValue(to: catFoodFloat)
                }
            case "birdy":
                image.isHidden = false
                //HAPPY BAR
                if (coolPets.birdy.numPlay < 10 && coolPets.birdy.numPlay > 0) {
                    let birdPlayFloat = CGFloat((coolPets.birdy.numPlay)/10.0)
                    happyBar.animateValue(to: birdPlayFloat)
                }
                //FOOD BAR
                if (coolPets.birdy.numFed < 10 && coolPets.birdy.numFed > 0){
                    let birdFoodFloat = CGFloat((coolPets.birdy.numFed)/10.0)
                    foodBar.animateValue(to: birdFoodFloat)
            }
            case "bunny":
                image.isHidden = false
                //HAPPY BAR
                if (coolPets.bun.numPlay < 10 && coolPets.bun.numPlay > 0) {
                    let bunnyPlayFloat = CGFloat((coolPets.bun.numPlay)/10.0)
                    happyBar.animateValue(to: bunnyPlayFloat)
                }
                //FOOD BAR
                if (coolPets.bun.numFed < 10 && coolPets.bun.numFed > 0){
                    let bunnyFoodFloat = CGFloat((coolPets.bun.numFed)/10.0)
                    foodBar.animateValue(to: bunnyFoodFloat)
            }
            case "fishy":
                image.isHidden = false
                //HAPPY BAR
                if (coolPets.fishy.numPlay < 10 && coolPets.fishy.numPlay > 0) {
                    let fishPlayFloat = CGFloat((coolPets.fishy.numPlay)/10.0)
                    happyBar.animateValue(to: fishPlayFloat)
                }
                //FOOD BAR
                if (coolPets.fishy.numFed < 10 && coolPets.fishy.numFed > 0){
                    let fishFoodFloat = CGFloat((coolPets.fishy.numFed)/10.0)
                    foodBar.animateValue(to: fishFoodFloat)
            }
            default:
                return
            }
        
        return
    }
    
    //UPDATING VALUES ABOVE BARS
    func updateVals() {
        switch coolPets.active {
        case "doggy":
            happyNum.text = "\(coolPets.doggy.numPlay)"
            foodNum.text = "\(coolPets.doggy.numFed)"
        case "kitty":
            happyNum.text = "\(coolPets.kitty.numPlay)"
            foodNum.text = "\(coolPets.kitty.numFed)"
        case "birdy":
            happyNum.text = "\(coolPets.birdy.numPlay)"
            foodNum.text = "\(coolPets.birdy.numFed)"
        case "bunny":
            happyNum.text = "\(coolPets.bun.numPlay)"
            foodNum.text = "\(coolPets.bun.numFed)"
        case "fishy":
            happyNum.text = "\(coolPets.fishy.numPlay)"
            foodNum.text = "\(coolPets.fishy.numFed)"
        default:
            return
        }
    }

    //PLAY BUTTON PRESSED
    @IBAction func play(_ sender: Any) {
        switch coolPets.active {
        case "doggy":
            //CAN'T PLAY WITH ANIMAL IF IT HASN'T BEEN FED
            if coolPets.doggy.numFed == 0 {
                alertBox.text = "Must feed pet before you can play"
                return
            }
            //UPDATES GLOBAL VARIABLE
            coolPets.doggy.numPlay += 1
            coolPets.doggy.numFed -= 1
            updateVals()
            alertBox.text = "You have played with your pet."
            //ANIMATING BARS
            updateBars()
        case "kitty":
            //CAN'T PLAY WITH ANIMAL IF IT HASN'T BEEN FED
            if coolPets.kitty.numFed == 0 {
                alertBox.text = "Must feed pet before you can play"
                return
            }
            //UPDATES GLOBAL VARIABLE
            coolPets.kitty.numPlay += 1
            coolPets.kitty.numFed -= 1
            updateVals()
            alertBox.text = "You have played with your pet."
            //ANIMATING BARS
            updateBars()
        case "birdy":
            //CAN'T PLAY WITH ANIMAL IF IT HASN'T BEEN FED
            if coolPets.birdy.numFed == 0 {
                alertBox.text = "Must feed pet before you can play"
                return
            }
            //UPDATES GLOBAL VARIABLE
            coolPets.birdy.numPlay += 1
            coolPets.birdy.numFed -= 1
            updateVals()
            alertBox.text = "You have played with your pet."
            //ANIMATING BARS
            updateBars()
        case "bunny":
            //CAN'T PLAY WITH ANIMAL IF IT HASN'T BEEN FED
            if coolPets.bun.numFed == 0 {
                alertBox.text = "Must feed pet before you can play"
                return
            }
            //UPDATES GLOBAL VARIABLE
            coolPets.bun.numPlay += 1
            coolPets.bun.numFed -= 1
            updateVals()
            alertBox.text = "You have played with your pet."
            //ANIMATING BARS
            updateBars()
        case "fishy":
            //CAN'T PLAY WITH ANIMAL IF IT HASN'T BEEN FED
            if coolPets.fishy.numFed == 0 {
                alertBox.text = "Must feed pet before you can play"
                return
            }
            //UPDATES GLOBAL VARIABLE
            coolPets.fishy.numPlay += 1
            coolPets.fishy.numFed -= 1
            updateVals()
            alertBox.text = "You have played with your pet."
            //ANIMATING BARS
            updateBars()
        default:
            return
        }
    }

    //FEED BUTTON PRESSED
    @IBAction func feed(_ sender: Any) {
        switch coolPets.active {
        case "doggy":
            coolPets.doggy.numFed += 1
            updateVals()
            //WHEN FED BAR IS FULL (CAN STILL BE PRESSED EVEN WHEN FULL)
            if coolPets.doggy.numFed >= 10 {
                alertBox.text = "Your pet is full, try playing with it"
            }
            alertBox.text = "You have fed your pet."
            //ANIMATES THE FOOD BAR
            updateBars()
        case "kitty":
            coolPets.kitty.numFed += 1
            updateVals()
            //WHEN FED BAR IS FULL (CAN STILL BE PRESSED EVEN WHEN FULL)
            if coolPets.kitty.numFed >= 10 {
                alertBox.text = "Your pet is full, try playing with it"
            }
            alertBox.text = "You have fed your pet."
            //ANIMATES THE FOOD BAR
            updateBars()
        case "birdy":
            coolPets.birdy.numFed += 1
            updateVals()
            //WHEN FED BAR IS FULL (CAN STILL BE PRESSED EVEN WHEN FULL)
            if coolPets.birdy.numFed >= 10 {
                alertBox.text = "Your pet is full, try playing with it"
            }
            alertBox.text = "You have fed your pet."
            //ANIMATES THE FOOD BAR
            updateBars()
        case "bunny":
            coolPets.bun.numFed += 1
            updateVals()
            //WHEN FED BAR IS FULL (CAN STILL BE PRESSED EVEN WHEN FULL)
            if coolPets.bun.numFed >= 10 {
                alertBox.text = "Your pet is full, try playing with it"
            }
            alertBox.text = "You have fed your pet."
            //ANIMATES THE FOOD BAR
            updateBars()
        case "fishy":
            coolPets.fishy.numFed += 1
            updateVals()
            //WHEN FED BAR IS FULL (CAN STILL BE PRESSED EVEN WHEN FULL)
            if coolPets.fishy.numFed >= 10 {
                alertBox.text = "Your pet is full, try playing with it"
            }
            alertBox.text = "You have fed your pet."
            //ANIMATES THE FOOD BAR
            updateBars()
        default:
            return
        }
    }

    //DOG BUTTON PRESSED
    @IBAction func nowDog(_ sender: Any) {
        coolPets.active = "doggy"
        alertBox.text = "Pet changed to Dog"
        image.image = coolPets.doggy.image
        background.backgroundColor = coolPets.doggy.color
        updateBars()
        updateVals()
    }

    //CAT BUTTON PRESSED
    @IBAction func nowCat(_ sender: Any) {
        coolPets.active = "kitty"
        alertBox.text = "Pet changed to Cat"
        image.image = coolPets.kitty.image
        background.backgroundColor = coolPets.kitty.color
        updateBars()
        updateVals()
    }
    
    //BIRD BUTTON PRESSED
    @IBAction func nowBird(_ sender: Any) {
        coolPets.active = "birdy"
        alertBox.text = "Pet changed to Bird"
        image.image = coolPets.birdy.image
        background.backgroundColor = coolPets.birdy.color
        updateBars()
        updateVals()
    }
    
    //BUNNY BUTTON PRESSED
    @IBAction func nowBunny(_ sender: Any) {
      coolPets.active = "bunny"
        alertBox.text = "Pet changed to Bunny"
        image.image = coolPets.bun.image
        background.backgroundColor = coolPets.bun.color
        updateBars()
        updateVals()
    }
    
    //FISH BUTTON PRESSED
    @IBAction func nowFish(_ sender: Any) {
        coolPets.active = "fishy"
        alertBox.text = "Pet changed to Fish"
        image.image = coolPets.fishy.image
        background.backgroundColor = coolPets.fishy.color
        updateBars()
        updateVals()
    }
}

//SEPARATE STRUCTS FOR EACH ANIMAL WITH IDENTICAL VARIABLE NAMES
struct myPets {
    var active : String = "null"
    var kitty = Cat(numPlay : 0, numFed : 0, image : #imageLiteral(resourceName: "cat"), color : UIColor.blue)
    var doggy = Dog(numPlay :0, numFed : 0, image : #imageLiteral(resourceName: "dog"), color : UIColor.red)
    var birdy = Bird(numPlay :0, numFed : 0, image : #imageLiteral(resourceName: "bird"), color : UIColor.yellow)
    var bun = Bunny(numPlay :0, numFed : 0, image : #imageLiteral(resourceName: "bunny"), color : UIColor.green)
    var fishy = Fish(numPlay :0, numFed : 0, image : #imageLiteral(resourceName: "fish"), color : UIColor.purple)
}

struct Cat {
    var numPlay : Double = 0
    var numFed : Double = 0
    var image = #imageLiteral(resourceName: "cat")
    var color = UIColor.red
}

struct Dog {
    var numPlay : Double = 0
    var numFed : Double = 0
    var image = #imageLiteral(resourceName: "dog")
    var color = UIColor.blue
}

struct Bird {
    var numPlay : Double = 0
    var numFed : Double = 0
    var image = #imageLiteral(resourceName: "bird")
    var color = UIColor.yellow
}

struct Bunny {
    var numPlay : Double = 0
    var numFed : Double = 0
    var image = #imageLiteral(resourceName: "bunny")
    var color = UIColor.green
}
struct Fish {
    var numPlay : Double = 0
    var numFed : Double = 0
    var image = #imageLiteral(resourceName: "fish")
    var color = UIColor.purple
}
