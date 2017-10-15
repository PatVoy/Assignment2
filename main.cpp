/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: petioptrv
 *
 * Created on October 14, 2017, 11:23 AM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Indexer.h"
#include "QueryResult.h"


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    Indexer index;
    
    // Open index file
    string docName = "index.txt";
    ifstream file(docName.c_str());
    
    // Open each document and push it into index object
    string line;
    while (getline(file, line)) {
        line >> index;
    }
    
    index.normalize();
    
    //cout << index;
    
    vector<QueryResult> results;
    string usrInput;
    
    cout << index[0].content() << endl;

    index.printMatrix();
    
    return 0;
    
    cout << "Welcome!" << endl;
    cout << "Please insert first query: ";
    getline(cin, usrInput);
    
    while (usrInput != "exit") {        
        results = index.query(usrInput);

        for (vector<QueryResult>::iterator result = results.begin();
                result != results.end();
                ++result) {
            cout << *result;
        }
        
        cout << "Insert next query or 'exit' to quit: ";
        getline(cin, usrInput);
    }
    
    cout << "\nThank you for using the query app.\n"
            "Next step in our journey: take over Google." << endl;
    
    return 0;
}

