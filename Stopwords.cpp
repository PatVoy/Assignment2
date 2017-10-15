/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Stopwords.cpp
 * Author: petioptrv
 * 
 * Created on October 14, 2017, 11:25 AM
 */

#include "Stopwords.h"

// Default constructor
Stopwords::Stopwords() {
    std::string fileName = "stopwords.txt";
    std::ifstream fin(fileName.c_str());
    
    std::string word;
    // insert words into list
    while (fin >> word)
        vectorStopwords.push_back(word);
    fin.close();
}

// Constructor reads the stopword list from this file
Stopwords::Stopwords(const std::string & fileName) {
    std::ifstream file(fileName.c_str());
    
    std::string word;
    // insert words into list
    while (getline(file, word)) {
        vectorStopwords.push_back(word);
    }
    file.close();
}

const bool Stopwords::operator() (const std::string & word) {
    for (std::vector<std::string>:: const_iterator i = vectorStopwords.begin();
         i != vectorStopwords.end();
         ++i)
        if (word == *i) return true;
    return false;
}

// overload operator<< returns stopword list content
std::ostream &operator<< (std::ostream & os,const Stopwords & st) {
    // Cannot use endl here because endl flushes the buffer
    os << "Stopwords: " << "\n";
    for (std::vector<std::string>::const_iterator i = st.vectorStopwords.begin();
         i != st.vectorStopwords.end();
         ++i)
        os << *i << "\n";
    return os;
}

