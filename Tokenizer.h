/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tokenizer.h
 * Author: petioptrv
 *
 * Created on October 14, 2017, 11:58 AM
 */

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <fstream>
#include <vector>

class Tokenizer {
public:
    Tokenizer();
    Tokenizer(const std::string & fileName);
    const std::string getDelimiters();
    std::vector<std::string> operator()(const std::string & inputStr);
    friend std::ostream & operator<<(std::ostream & os, Tokenizer & tokenizer);
private:
    std::string delimiters;
};

#endif /* TOKENIZER_H */

