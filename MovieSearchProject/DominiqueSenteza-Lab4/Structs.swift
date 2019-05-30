//
//  Structs.swift
//  DominiqueSenteza-Lab4
//
//  Created by labuser on 7/16/18.
//  Copyright © 2018 DominiqueSenteza. All rights reserved.
//

import Foundation

struct APIResults: Decodable {
    let page: Int
    let total_results: Int
    let total_pages: Int
    let results: [Movie]
}
struct Movie: Decodable {
    let id: Int!
    let poster_path: String?
    let title: String
    let release_date: String
    let vote_average: Double
    let overview: String
}
