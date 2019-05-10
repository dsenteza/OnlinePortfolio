//
//  Line.swift
//  DominiqueSenteza-Lab3
//
//  Created by labuser on 7/6/18.
//  Copyright © 2018 EricMason. All rights reserved.
//

import Foundation
import UIKit

struct Line {
    var startPoint: CGPoint
    var endPoint: CGPoint
    var color: UIColor
    var thickness: CGFloat
    var points:[CGPoint]
    
    func lineToArray() -> [CGPoint]{
        return points
    }
    
}
