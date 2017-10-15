/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Stopwords.h
 * Author: petioptrv
 *
 * Created on October 14, 2017, 11:25 AM
 */

#ifndef STOPWORDS_H
#define STOPWORDS_H

#include <string>
#include <vector>
#include <fstream>

class Stopwords
{
public:
    Stopwords();
    Stopwords(const std::string & fileName);
    // Returns true if a word is found in stopword list
    const bool operator()(const std::string & word);
    friend std::ostream & operator<<(std::ostream & os, const Stopwords & st);
private:
    std::vector<std::string> vectorStopwords;
};

#endif /* STOPWORDS_H */

