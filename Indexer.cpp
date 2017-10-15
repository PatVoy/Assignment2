/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Indexer.cpp
 * Author: petioptrv
 * 
 * Created on October 14, 2017, 1:31 PM
 */

#include "Indexer.h"

typedef std::map<std::string, float> OneMap;
typedef std::map<std::string, std::map<std::string, float> > TwoMap;
typedef std::map<std::string, 
                 std::map<std::string, 
                          std::map<std::string, float> > > ThreeMap;

Indexer::Indexer() {
    normalized = false;
}

void Indexer::printMatrix() {
    std::string wordColHead = "Dictionary";
    int wordColHeadLen = wordColHead.length();
    int maxWordLen=0;
    int maxFileNameLen=0;
    int maxMetricLen = 0;

    // Iterate over each word to get the maximum word length
    for (ThreeMap::iterator word = wordMap.begin();
         word != wordMap.end();
         ++word)
    {
        if(word->first.length() > maxWordLen)
            maxWordLen = word->first.length();
    }

    // Iterate over each document in the vector of documents to get the maximum
    // document name
    for (int i = 0; i < docVector.size(); i++)
    {
        if(docVector[i].name().length() > maxFileNameLen)
            maxFileNameLen = docVector[i].name().length();
    }
    
    // Iterate over the frequencies of the first document of the first word
    // in the map to collect the maximum frequency name length
    for (OneMap::iterator metric = wordMap.begin()->second.begin()->second.begin();
            metric != wordMap.begin()->second.begin()->second.end();
            ++metric) {
        if (metric->first.length() > maxMetricLen) {
            maxMetricLen = metric->first.length();
        }
    }
    
    // If the word column header is longer than the maximum word length,
    // update the values
    maxWordLen = maxWordLen ? maxWordLen > wordColHeadLen : wordColHeadLen;
    
    // Keeps track of the totals for the matrix
    std::map< std::string , int > fullWordTotals;

    int indexColLen = 1 + 1 + maxWordLen + 1;
    int docColLen = 1 + 1 + maxFileNameLen + 1;
    int metricColLen = 1 + 1 + maxMetricNameLen + 1;
    docColLen = docColLen ? docColLen > 2*metricColLen : 2*metricColLen;
    int separationLineLen = indexColLen + (docColLen * docVector.size()) + 1;
    std::string separationLine(separationLineLen, '-');
    std::string leftBorder = "| ";
    std::string rightBorder = " |";
    std::string midBorder = " | ";

    // MATRIX HEADER

    std::cout << "FULL MATRIX" << std::endl;
    std::cout << separationLine << std::endl;
    std::cout << leftBorder << std::setw(maxWordLen) << std::left << "Dictionary";
    // Print out the file names
    for (int i = 0; i < docVector.size(); i++) {
        std::cout << std::setw(3) << midBorder
                << std::setw(maxFileNameLen) << std::left << docVector[i].name();
    }
    std::cout << rightBorder << "\n" << separationLine << std::endl;

    // MATRIX BODY

    // Print each row
    for (ThreeMap::iterator word = wordMap.begin();
         word != wordMap.end();
         ++word) {
        std::cout << leftBorder << std::setw(maxWordLen) << std::left << word->first;

        // Print each column for that row
        for (int i = 0; i < docVector.size(); i++) {
            std::cout << std::setw(3) << midBorder
                    << std::setw(maxFileNameLen) << std::right
                    << word->second[docVector[i].name()]["frequency"] << " | " << word->second[docVector[i].name()]["weight"];
            fullWordTotals[docVector[i].name()] += word->second[docVector[i].name()]["frequency"];
        }
        std::cout << std::setw(2) << rightBorder << std::endl;  // Close last column
    }
    std::cout << separationLine << "\n" << std::setw(2) << leftBorder
            << std::setw(maxWordLen) << std::left << "Total";
    for (std::map<std::string, int>::iterator fileN = fullWordTotals.begin();
            fileN != fullWordTotals.end();
            ++fileN) {
        std::cout << std::setw(3) << midBorder << std::setw(maxFileNameLen) << std::right
                << fileN->second;
    }
    std::cout << std::setw(2) << rightBorder << "\n" << separationLine << "\n\n" << std::endl;
}

void Indexer::printReducedMatrix() {
    
}

const size_t Indexer::size() {
    return docVector.size();
}

const float Indexer::weight(const float & freq, 
                            const int & numDoc, 
                            const size_t & appearances) {
    
    
    
    
    if (freq != 0) {
        std::cout << "\nIN WEIGHT " << freq << " " << numDoc << " " << appearances << std::endl;
    }
    
    
    
    
    // Check if the frequency is zero or if the term appears once in all
    // documents, which should result in a zero in both cases
    if (freq) {
        return roundf((1+log(freq))*log(float(numDoc)/appearances));
    } else {
        return 0;
    }
}

void Indexer::normalize() {
    size_t numDoc = size();
    float freq = 0;
    size_t appearances = 0;
    //traverses the map to get all the numbers needed for the weight calculation
    for (ThreeMap::const_iterator word = wordMap.begin();
         word != wordMap.end();
         ++word) {
        appearances = word->second.size();
        //traverses inner map to get the frequency of each word/document
        for(TwoMap::const_iterator iter = word->second.begin(); 
                iter != word->second.end(); 
                ++iter) {
            freq = wordMap[word->first][iter->first]["frequency"];
            float wordWeight = weight(freq, numDoc, appearances);
            wordMap[word->first][iter->first]["weight"] = wordWeight;
        }

    }
    
    normalized = true;
}

const double Indexer::similarityScore(TwoMap & tokenMap, 
                                      const std::string & docName) {
    // Make sure the passed map is of same length as the word map
    // assert (tokenMap.size() == wordMap.size() && 
    //        "The two maps are not of equal size");
    
    // Calculate the score
    double num = 0;
    double denomLeft = 0;
    double denomRight = 0;
    for (TwoMap::iterator token = tokenMap.begin();
            token != tokenMap.end();
            ++token) {
        float tokenWeight = token->second["weight"];
        float wordWeight = wordMap[token->first][docName]["weight"];
        
        num += tokenWeight * wordWeight;
        denomLeft += pow(tokenWeight, 2);
        denomRight += pow(wordWeight, 2);
        
        
        
        
        
        std::cout << "\nWord: " << token->first;
        std::cout << "\n" << tokenWeight << " " << wordWeight << " " << num << " " << denomLeft << " " << denomRight;
    
    
    
    
    
    }
    double denom = sqrt(denomLeft) * sqrt(denomRight);
    double docScore = num/denom ? denom : 0;  // Check for division by zero
    
    return docScore;
}

const std::vector<QueryResult> Indexer::query(const std::string & usrQuery) {
    // If the index has not been normalized, run the normalize function
    if (!normalized) {
        normalize();
    }
    
    Tokenizer tokenizer;
    std::vector<std::string> tokens = tokenizer(usrQuery);
    
    // Create a map for each token and its metrics with respect to the query
    TwoMap tokenMap;
    for (std::vector<std::string>::const_iterator token = tokens.begin();
            token != tokens.end();
            ++token) {
        tokenMap[*token]["frequency"]++;
    }
    
    // Traverse map to insert the rest of the words in the token map and
    // calculate weights
    size_t numDoc = size();
    for (ThreeMap::iterator word = wordMap.begin();
         word != wordMap.end();
         ++word) {
        int freq = tokenMap[word->first]["frequency"];
        int appearances = 0;
         
        for (TwoMap::iterator doc = word->second.begin();
                doc != word->second.end();
                ++doc) {
            std::cout << "\nFREQUENCY " << word->first << " " << doc->first << " " << doc->second["frequency"] << std::endl;
            if (doc->second["frequency"] > 0) {
                appearances++;
                std::cout << "appearances: " << appearances << std::endl;
            }
        }
        
        // Add the missing words and all of the weights to the tokens map
        tokenMap[word->first]["weight"] = weight(freq, numDoc, appearances);
    }
    
    // Get vector of results
    std::vector<QueryResult> results;
    for (std::vector<Document>::iterator doc = docVector.begin();
            doc != docVector.end();
            ++doc) {
        double docScore = similarityScore(tokenMap, doc->name());
        results.push_back(QueryResult(*doc, docScore));
    }
    
    return results;
}

const std::vector<QueryResult> Indexer::query(const std::string & usrQuery, 
                                              int & querySize) {
    if (!normalized) {
        normalize();
    }
    
    Tokenizer tokenizer = Tokenizer(usrQuery);
    std::vector<std::string> tokens = tokenizer(usrQuery);
    
    // Create a map for each token and its metrics with respect to the query
    TwoMap tokenMap;
    for (std::vector<std::string>::const_iterator token = tokens.begin();
            token != tokens.end();
            ++token) {
        tokenMap[*token]["frequency"]++;
    }
    
    // Traverse map to insert the rest of the words in the token map and to
    // calculate weights
    size_t numDoc = size();
    int freq = 0;
    int appearances = 0;
    for (ThreeMap::const_iterator word = wordMap.begin();
         word != wordMap.end();
         ++word) {
        appearances = word->second.size();
        // Add the missing words and all of the weights to the tokens map
        tokenMap[word->first]["weight"] = weight(freq, numDoc, appearances);
    }
    
    // Get vector of results
    std::vector<QueryResult> results;
    for (std::vector<Document>::iterator doc = docVector.begin();
            doc != docVector.end();
            ++doc) {
        double docScore = similarityScore(tokenMap, doc->name());
        results.push_back(QueryResult(*doc, docScore));
    }
    
    return results;
}

Document & Indexer::operator[](const int & idx) {
    return docVector[idx];
}

void operator>>(const std::string & docName, Indexer & i) {
    Document doc(docName);
    i.docVector.push_back(doc);
    
    // Extract words from doc content
    Tokenizer tokenizer;  // Create tokenizer object
    // Feed the content of the doc to the tokenizer overloaded bracket operator
    // to get a vector of words in return
    std::vector<std::string> tokens = tokenizer(doc.content());
    
    // Traverse the vector of tokens and add it to the data structure
    for (std::vector<std::string>::const_iterator token = tokens.begin();
         token != tokens.end();
         ++token) {
        i.wordMap[*token][docName]["frequency"]++;
    }
    
    i.normalized = false;  // The index is no longer normalized
}

void operator>>(Document & doc, Indexer & i) {
    std::string docName = doc.name();
    i.docVector.push_back(doc);
    
    // Extract words from doc content
    Tokenizer tokenizer;  // Create tokenizer object
    // Feed the content of the doc to the tokenizer overloaded bracket operator
    // to get a vector of words in return
    std::vector<std::string> tokens = tokenizer(doc.content());
    
    // Traverse the vector of tokens and add it to the data structure
    for (std::vector<std::string>::const_iterator token = tokens.begin();
         token != tokens.end();
         ++token) {
        i.wordMap[*token][docName]["frequency"]++;
    }
    
    i.normalized = false;  // The index is no longer normalized
}

std::ostream & operator<<(std::ostream & os, Indexer & i) {
    // Print the normalized boolean
    os << "Normalized: " << i.normalized << "\n";
    
    // Iterate through every word
    for (ThreeMap::iterator word = i.wordMap.begin();
         word != i.wordMap.end();
         ++word) {
        
        os << word->first << "\n";  // Print out the word
        // Iterate over every document
        for (std::vector<Document>::iterator doc = i.docVector.begin();
             doc != i.docVector.end();
             ++doc) {
            
            os << "    " << doc->name() << "\n";  // Print out the doc name
            // Iterate over the different metrics for that word within that document
            for (OneMap::const_iterator 
                    metric = word->second[doc->name()].begin();
                 metric != word->second[doc->name()].end();
                 ++metric) {
                
                // Print out the metric string and the value associated with it
                os << "        ";  // Indent output
                os << metric->first << ": " << metric->second << "\n";
            }
        }
    }
    
    return os;
}

