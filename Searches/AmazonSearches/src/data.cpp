#include "data.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void Data::read_from_file(string name) {
    ifstream file;
    string line;
    const char * word = name.c_str();
    file.open(word);
    unsigned i = 0; // keeps track of index of current character in a line of the text file

    if(!file.is_open()) {
        throw std::invalid_argument("Invalid file path(s) given");
    }
    
    while (file) { // iterate through each line in file
        i = 0;
        string first; // fromNodeID
        string second; // toNodeID
        getline(file, line); // get next line
        while (line[i] > 47 && line[i] < 58) { // get all chars with ASCII value between 0-9 - [48,57], append them to first number string until the next char is not a number
            first += line[i];
            i++;
        }
        while (i < line.size()) { // continue for the rest of the line
            if (line[i] > 47 && line[i] < 58) { // only append numbers to the second number string 
                second += line[i];
            }
            i++;
        }
        if (!nodesFrom.empty() && stoi(first) == nodesFrom.back() && stoi(second) == nodesTo.back()) {
            continue; // skip if there are duplicates in the data... also stops the last element from being added twice as I found out was happening with the current implementation
        }
        nodesFrom.push_back(stoi(first)); // push back the numbers into their respective vectors after converting them to integers
        nodesTo.push_back(stoi(second));
    }
    file.close();
}

// getter for nodes From
vector<int> Data::getNodesFrom() const {
    return nodesFrom;
}

// getter for nodes To
vector<int> Data::getNodesTo() const {
    return nodesTo;
}
