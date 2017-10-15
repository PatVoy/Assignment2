/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Document.h
 * Author: petioptrv
 *
 * Created on October 14, 2017, 11:35 AM
 */

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>
#include <fstream>

class Document
{
public:
    Document(const std::string & name);
    const std::string name();
    const size_t size();
    const std::string content();
    friend std::ostream & operator<<(std::ostream & os, Document & doc);    
private:
    std::string fileName;
    std::string docContent;
};

#endif /* DOCUMENT_H */

