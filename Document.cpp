/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Document.cpp
 * Author: petioptrv
 * 
 * Created on October 14, 2017, 11:35 AM
 */

#include "Document.h"

// Constructor accepts a file name and reads content into document object
Document::Document(const std::string & name) {
    fileName = name;  // Store file name
    std::ifstream file(name.c_str()); // Load the file
    
    std::string line;
    while (getline(file, line)) {
        docContent += line;
    }
    file.close();
}

// Returns the file name of the document
const std::string Document::name()
{
    return fileName;
}

// Size in characters
const size_t Document::size()
{
    return docContent.length();
}
// Returns the text of the document
const std::string Document::content()
{
    return docContent;
}

std::ostream & operator<<(std::ostream & os, Document & doc) {
    os << "Name: " << doc.name() << "\n";;
    
    return os;
}


