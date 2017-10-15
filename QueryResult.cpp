/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   QuerryResult.cpp
 * Author: petioptrv
 * 
 * Created on October 14, 2017, 1:06 PM
 */

#include "QueryResult.h"

QueryResult::QueryResult(const Document & d, const double & s) : doc(d), score(s) {
}

const bool QueryResult::sortByScore(const QueryResult & r1, const QueryResult & r2) {
    return r1.score < r2.score;
}

std::ostream & operator<<(std::ostream & os, QueryResult & queryResult) {
    os << "\nDOC SCORE: " << queryResult.score << "\n";
    os << queryResult.doc;
    
    return os;
}

const bool operator<(const QueryResult & r1, const QueryResult & r2) {
    return r1.score < r2.score;
}
