//
//  ViewController.swift
//  DominiqueSenteza-Lab1
//
//  Created by labuser on 6/18/18.
//  Copyright © 2018 labuser. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    //Outlets
    @IBOutlet weak var ogVal: UITextField!
    @IBOutlet weak var discVal: UITextField!
    @IBOutlet weak var taxVal: UITextField!
    @IBOutlet weak var final: UILabel!
    
    
    //Global Variables
    var originalValue:Float = 0.0
    var discountValue:Float = 0.0
    var taxValue:Float = 0.0
    var finalValue:Float = 0.0
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    //Calculating Function that does all the work
    func calculate() {
        finalValue = (originalValue) * (1 - (discountValue * (0.01))) * (1 + (taxValue * (0.01)))
        finalValue = round(100*finalValue)/100
        final.text = String(finalValue)
    }

    //Action Functions
    //When value is typed into original value field
    @IBAction func original(_ sender: Any) {
        //Guard let to check if input can be converted into a float
        guard let unwrapOriginal = Float(ogVal.text!) else {
            final.text = "Price input must be a number"
            originalValue = 0.0
            return
        }
        //Makes sure the input is a positive
        if(unwrapOriginal <= 0){
            final.text = "Price input must be a positive number"
            return
        }
        //If passes, value saved to global variable and calculate function runs
        originalValue = unwrapOriginal
        calculate()
    }
    //When value is typed into discount percentage field
    @IBAction func discount(_ sender: Any) {
        //Guard let to check if input can be converted into a float
        guard let unwrapDiscount = Float(discVal.text!) else {
            final.text = "Discount input must be a number"
            discountValue = 0.0
            return
        }
        //Makes sure the input is a positive
        if(unwrapDiscount <= 0){
            final.text = "Disount input must be a positive number"
            return
        }
        //Makes sure percentage is less than 100
        if(unwrapDiscount > 100){
            final.text = "Discount input must be less than 100"
            return
        }
        //If passes, value saved to global variable and calculate function runs
        discountValue = unwrapDiscount
        calculate()
    }
    //When value is typed into sales tax field
    @IBAction func tax(_ sender: Any) {
        //Guard let to check if input can be converted into a float
        guard let unwrapTax = Float(taxVal.text!) else {
            final.text = "Tax input must be a number"
            taxValue = 0.0
            return
        }
        //Makes sure the input is a positive
        if(unwrapTax <= 0){
            final.text = "Tax input must be a positive number"
            return
        }
        //Makes sure percentage is less than 100
        if(unwrapTax > 100){
            final.text = "Tax input must be less than 100"
            return
        }
        //If passes, value saved to global variable and calculate function runs
        taxValue = unwrapTax
        calculate()
    }
    //When decrease discount percentage arrow is pressed
    @IBAction func decreaseDiscount(_ sender: Any) {
        if(discountValue == 0){
        } else {
            discountValue -= 1
        }
        discVal.text = String(discountValue)
        calculate()
    }
    //When increase discount percentage arrow is pressed
    @IBAction func increaseDiscount(_ sender: Any) {
        if(discountValue == 100){
        } else {
            discountValue += 1
        }
        discVal.text = String(discountValue)
        calculate()
    }
    //When decrease sales tax arrow is pressed
    @IBAction func decreaseTax(_ sender: Any) {
        if(taxValue == 0){
        } else {
            taxValue -= 1
        }
        taxVal.text = String(taxValue)
        calculate()
    }
    //When increase sales tax arrow is pressed
    @IBAction func increaseTax(_ sender: Any) {
        if(taxValue == 100){
        } else {
            taxValue += 1
        }
        taxVal.text = String(taxValue)
        calculate()
    }
}

