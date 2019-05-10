//
//  background.swift
//  DominiqueSenteza-Lab3
//
//  Created by labuser on 7/6/18.
//  Copyright © 2018 EricMason. All rights reserved.
//

import Foundation
import UIKit

struct Color {
    var red = Red (r: 255, g: 0, b: 0, alpha: 1)
    var blue = Blue (r: 0, g: 0, b: 255, alpha: 1)
    var yellow = Yellow (r: 255, g: 255, b: 0, alpha: 1)
    var green = Green (r: 0, g: 255, b: 0, alpha: 1)
    var black = Black (r: 0, g: 0, b: 0, alpha: 1)
    var white = White (r: 255, g: 255, b: 255, alpha: 1)
}

struct Red {
    var r:CGFloat = 255
    var g:CGFloat = 0
    var b:CGFloat = 0
    var alpha:CGFloat = 1
}

struct Blue {
    var r:CGFloat = 0
    var g:CGFloat = 0
    var b:CGFloat = 255
    var alpha:CGFloat = 1
}

struct Yellow {
    var r:CGFloat = 255
    var g:CGFloat = 255
    var b:CGFloat = 0
    var alpha:CGFloat = 1
}

struct Green {
    var r:CGFloat = 0
    var g:CGFloat = 255
    var b:CGFloat = 0
    var alpha:CGFloat = 1
}

struct Black {
    var r:CGFloat = 255
    var g:CGFloat = 0
    var b:CGFloat = 0
    var alpha:CGFloat = 1
}

struct White {
    var r:CGFloat = 0
    var g:CGFloat = 0
    var b:CGFloat = 0
    var alpha:CGFloat = 0
}

