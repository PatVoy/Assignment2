/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tokenizer.cpp
 * Author: petioptrv
 * 
 * Created on October 14, 2017, 11:58 AM
 */

#include "Tokenizer.h"

Tokenizer::Tokenizer() {
    std::string fileName = "delimiters.txt";
    std::ifstream file(fileName.c_str());
    
    // Extract file content and store in delimiter variable
    std::string line;
    while (getline(file, line)) {
        delimiters += line;
    }
    file.close();
}

Tokenizer::Tokenizer(const std::string & fileName) {
    std::ifstream file(fileName.c_str());
    
    std::string line;
    while (getline(file, line)) {
        delimiters += line;
    }
    file.close();
}

std::vector<std::string> Tokenizer::operator()(const std::string & inputStr) {
    std::vector<std::string> tokens; // Stores the tokens
    
    size_t currPos = 0;
    size_t newPos;
    std::string nextWord = "";
    
    // Extract each word character by character
    for (std::string::const_iterator character = inputStr.begin();
        character != inputStr.end();
        ++character) {
        // Compare character to delimiters to see if there is a match
        if (delimiters.find_first_of(*character, currPos) == 
                std::string::npos) {
            nextWord += std::tolower(*character);
        } else {
            if (nextWord != "") {  // If word is not empty
                tokens.push_back(nextWord);  // Insert word into vector
                nextWord = "";  // Reset string
            }
        }
    }
    
    // Add the last word
    if (nextWord != "") {  // If word is not empty
        tokens.push_back(nextWord);  // Insert word into vector
    }
    
    return tokens;
}

std::ostream & operator<<(std::ostream & os, Tokenizer & tokenizer) {
    os << tokenizer.delimiters;
    
    return os;
}
