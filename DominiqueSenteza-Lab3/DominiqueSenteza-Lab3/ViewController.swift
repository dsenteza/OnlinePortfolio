//
//  ViewController.swift
//  DominiqueSenteza-Lab3
//
//  Created by labuser on 7/6/18.
//  Copyright © 2018 EricMason. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    //Variables
    @IBOutlet weak var sliderVal: UISlider!
    @IBOutlet weak var opacity: UILabel!
    @IBOutlet weak var neutralColor: UIButton!
    @IBOutlet weak var drawView: LineView!
    @IBOutlet weak var slider: UISlider!
    var start = CGPoint.zero
    var currentLine: Line?
    var thickness: CGFloat = 5.0
    var color:UIColor = UIColor.black
    var index:Int = 0
    var beginning: [Int] = []
    var end:Int = 0
    var firstPoint: Int = 0
    var isWhite:Bool = true
    var dot:Bool = true
    var neutralPressed:Bool = false
    
    //Main Struct that holds all color values
    var penColor = Color()
    
    //Booleans for colors
    var penRed:Bool = false
    var penBlue:Bool = false
    var penYellow:Bool = false
    var penGreen:Bool = false
    var penWhite:Bool = false
    var penBlack:Bool = true
    
    override func viewDidLoad() {
        super.viewDidLoad()
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    //Red circle button
    @IBAction func red(_ sender: Any) {
        //Booleans for colors
        penRed = true
        penBlue = false
        penYellow = false
        penGreen = false
        penWhite = false
        penBlack = false
        color = UIColor(displayP3Red: penColor.red.r, green: penColor.red.g, blue: penColor.red.b, alpha: CGFloat(sliderVal.value))
        neutralPressed = false
    }
    
    //Blue circle button
    @IBAction func blue(_ sender: Any) {
        //Booleans for colors
        penRed = false
        penBlue = true
        penYellow = false
        penGreen = false
        penWhite = false
        penBlack = false
        color = UIColor(displayP3Red: penColor.blue.r, green: penColor.blue.g, blue: penColor.blue.b, alpha: CGFloat(sliderVal.value))
        neutralPressed = false    }
    
    //Green Circle button
    @IBAction func green(_ sender: Any) {
        //Booleans for colors
        penRed = false
        penBlue = false
        penYellow = false
        penGreen = true
        penWhite = false
        penBlack = false
        color = UIColor(displayP3Red: penColor.green.r, green: penColor.green.g, blue: penColor.green.b, alpha: CGFloat(sliderVal.value))
        neutralPressed = false
    }
    
    //Yellow circle button
    @IBAction func yellow(_ sender: Any) {
        //Booleans for colors
        penRed = false
        penBlue = false
        penYellow = true
        penGreen = false
        penWhite = false
        penBlack = false
        color = UIColor(displayP3Red: penColor.yellow.r, green: penColor.yellow.g, blue: penColor.yellow.b, alpha: CGFloat(sliderVal.value))
        neutralPressed = false
    }
  
    //Black/white circle button
    @IBAction func neutral(_ sender: Any) {
        if isWhite {
            //Booleans for colors
            penRed = false
            penBlue = false
            penYellow = false
            penGreen = false
            penWhite = false
            penBlack = true
            color = UIColor(displayP3Red: penColor.black.r, green: penColor.black.g, blue: penColor.black.b, alpha: CGFloat(sliderVal.value))
            neutralPressed = true
        }
        else {
            //Booleans for colors
            penRed = false
            penBlue = false
            penYellow = false
            penGreen = false
            penWhite = true
            penBlack = false
            color = UIColor(displayP3Red: penColor.white.r, green: penColor.white.g, blue: penColor.white.b, alpha: CGFloat(sliderVal.value))
            neutralPressed = true
        }
    }

    //Change alpha value of color
    @IBAction func changeAlpha(_ sender: Any) {
        //Booleans for colors
        if penRed {
            color = UIColor(displayP3Red: penColor.red.r, green: penColor.red.g, blue: penColor.red.b, alpha: CGFloat(sliderVal.value))
        }
        if penBlue {
           color = UIColor(displayP3Red: penColor.blue.r, green: penColor.blue.g, blue: penColor.blue.b, alpha: CGFloat(sliderVal.value))
        }
        if penYellow {
            color = UIColor(displayP3Red: penColor.yellow.r, green: penColor.yellow.g, blue: penColor.yellow.b, alpha: CGFloat(sliderVal.value))
        }
        if penGreen {
            color = UIColor(displayP3Red: penColor.green.r, green: penColor.green.g, blue: penColor.green.b, alpha: CGFloat(sliderVal.value))
        }
        if penWhite {
            color = UIColor(displayP3Red: penColor.white.r, green: penColor.white.g, blue: penColor.white.b, alpha: CGFloat(sliderVal.value))
        }
        if penBlack {
            color = UIColor(displayP3Red: penColor.black.r, green: penColor.black.g, blue: penColor.black.b, alpha: CGFloat(sliderVal.value))
        }
    }
    
    @IBAction func change(_ sender: Any) {
        if isWhite {
            drawView.backgroundColor = UIColor.black
            neutralColor.setImage(#imageLiteral(resourceName: "whiteCircle"), for: UIControlState.normal)
            opacity.textColor = UIColor.white
            isWhite = false
            if neutralPressed {
                //Booleans for colors
                penRed = false
                penBlue = false
                penYellow = false
                penGreen = false
                penWhite = true
                penBlack = false
                color = UIColor(displayP3Red: penColor.white.r, green: penColor.white.g, blue: penColor.white.b, alpha: CGFloat(sliderVal.value))
            }
        }
        else {
            drawView.backgroundColor = UIColor.white
            neutralColor.setImage(#imageLiteral(resourceName: "blackCircle"), for: UIControlState.normal)
            opacity.textColor = UIColor.black
            isWhite = true
            if neutralPressed {
                //Booleans for colors
                penRed = false
                penBlue = false
                penYellow = false
                penGreen = false
                penWhite = false
                penBlack = true
                color = UIColor(displayP3Red: penColor.black.r, green: penColor.black.g, blue: penColor.black.b, alpha: CGFloat(sliderVal.value))
            }
        }
    }
    
    @IBAction func undo(_ sender: Any) {
        print("inside")
        if drawView.lines.isEmpty {
            print("index = 0")
            drawView.theLine = nil
            drawView.lines = []
            return
        }
        else{
            drawView.lines.popLast()
        }
    }
    
    //Clear button
    @IBAction func clear(_ sender: Any) {
        print("clear")
        drawView.theLine = nil
        drawView.lines = []
    }
    
    //Line width slider
    @IBAction func width(_ sender: Any) {
        thickness = CGFloat(slider.value)
        print(thickness)
    }
    
    //Touched began
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        let touchPoint = (touches.first)!.location(in: drawView) as CGPoint
        print("touch began")
        currentLine = Line(startPoint: touchPoint, endPoint: touchPoint, color: color, thickness: thickness, points: [])
        currentLine?.points.append(touchPoint)
        drawView.theLine = currentLine
        
        dot = false
    }
    
    //Touches moved
    override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?) {
        let touchPoint = (touches.first)!.location(in: drawView) as CGPoint
        print("touch moved")
        currentLine?.endPoint = touchPoint
        currentLine?.points.append(touchPoint)
        drawView.theLine?.points.append(touchPoint)
        dot = false
    }

    //Touches ended
    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
        let touchPoint = (touches.first)!.location(in: drawView) as CGPoint

        drawView.theLine?.points.append(touchPoint)
   
//        currentLine?.endPoint = touchPoint
//        currentLine?.points.append(touchPoint)
//        if let newLine = currentLine {
        print("touch ended")
            drawView.lines.append(drawView.theLine!)
            print("line count \(drawView.lines.count)")
//            end = drawView.lines.endIndex
//        }
    }
    
}

