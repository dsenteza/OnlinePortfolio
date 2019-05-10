//
//  lineView.swift
//  DominiqueSenteza-Lab3
//
//  Created by labuser on 7/6/18.
//  Copyright © 2018 EricMason. All rights reserved.
//

import Foundation
import UIKit

class LineView: UIView {
    var theLine:Line?{
        didSet {
            setNeedsDisplay()
        }
    }
    
    var lines:[Line] = []{
        didSet {
            setNeedsDisplay()
        }
    }
    
    var whiteLine:[Line] = []{
        didSet {
            setNeedsDisplay()
        }
    }
    
    var blackLine:[Line] = []{
        didSet {
            setNeedsDisplay()
        }
    }
    
    override init(frame: CGRect) {
        super.init(frame: frame)
    }

    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
        self.backgroundColor = UIColor.clear
    }
    
    func drawLine(_ points: [CGPoint]) -> UIBezierPath {
        let path = UIBezierPath()
        if points.count < 2 {
//            path.move(to: points[0])
//            path.addLine(to: points[0])
            print("dot \(points.count)")
        } else {
            let firstPoint = points[0]
            let secondPoint = points[1]
            let firstMidpoint = Formulas.findMidpoint(first: firstPoint, second: secondPoint)
            path.move(to: firstPoint)
            path.addLine(to: firstMidpoint)
            for index in 1 ..< points.count-1 {
                let currentPoint = points[index]
                let nextPoint = points[index + 1]
                let midPoint = Formulas.findMidpoint(first: currentPoint, second: nextPoint)
                path.addQuadCurve(to: midPoint, controlPoint: currentPoint)
                path.lineJoinStyle = .round
                path.lineCapStyle = .round
            }
        }
        return path
    }
    
    // Only override draw() if you perform custom drawing.
    //An empty implementation adversely affects performance during animation.
    override func draw(_ rect: CGRect) {
        guard let array:[CGPoint] = theLine?.lineToArray() else {return}
        var currPath = drawLine(array)
        currPath.lineCapStyle = .round
        theLine?.color.setStroke()
        currPath.lineWidth = (theLine?.thickness)!
        currPath.stroke()
        
        for line in lines {
            let path = drawLine(line.lineToArray())
            path.lineCapStyle = .round
            line.color.setStroke()
            path.lineWidth = line.thickness
            path.stroke()
        }
    }
}
