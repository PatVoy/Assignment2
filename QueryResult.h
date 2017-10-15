/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   QuerryResult.h
 * Author: petioptrv
 *
 * Created on October 14, 2017, 1:06 PM
 */

#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <iostream>

#include "Document.h"

class QueryResult {
public:
    QueryResult(const Document & d, const double & s);
    const bool sortByScore(const QueryResult & r1, const QueryResult & r2);
    friend std::ostream & operator<<(std::ostream & os, 
                                     QueryResult & queryResult);
    friend const bool operator<(const QueryResult & r1, const QueryResult & r2);
private:
    Document doc;
    double score;
};

#endif /* QUERRYRESULT_H */

