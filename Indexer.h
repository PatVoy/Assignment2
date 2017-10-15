/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Indexer.h
 * Author: petioptrv
 *
 * Created on October 14, 2017, 1:31 PM
 */

#ifndef INDEXER_H
#define INDEXER_H

#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <utility>
#include <fstream>
#include <iostream>

#include "Document.h"
#include "Tokenizer.h"
#include "QueryResult.h"

typedef std::map<std::string, std::map<std::string, float> > TwoMap;
typedef std::map<std::string, 
                 std::map<std::string, 
                          std::map<std::string, float> > > ThreeMap;

class Indexer {
public:
    Indexer();
    void printMatrix();
    void printReducedMatrix();
    const size_t size();
    const float weight(const float & freq, 
                         const int & numDoc, 
                         const size_t & appearances);
    void normalize();
    const double similarityScore(TwoMap & tokenMap, 
                                 const std::string & docName);
    const std::vector<QueryResult> query(const std::string & usrQuery);
    const std::vector<QueryResult> query(const std::string & usrQuery, int & querySize);
    Document & operator[](const int & idx);
    friend void operator>>(const std::string & docName, Indexer & i);
    friend void operator>>(Document & doc, Indexer & i);
    friend std::ostream & operator<<(std::ostream & os,
                                     Indexer & i);
private:
    ThreeMap wordMap;
    std::vector<Document> docVector;
    bool normalized;
};

#endif /* INDEXER_H */

