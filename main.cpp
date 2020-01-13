/*
 * Filename: main.cpp
 * Contains: Driver for homework 5 
 *
 * Modified by:   Rosa Vitiello
 * Last modified: Nov. 19, 2018
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "SixDegrees.h"

using namespace std;

int main(int argc, char *argv[]) 
{
    SixDegrees sd;

    if (argc > 2) {
        cout << "Error, this function takes at most 1 parameters:\n";
        cout << "0 - program reads from cin outputs to cout\n";
        cout << "1 - [filename], program reads from file and outputs to cout\n";
    }
    else if (argc == 2) { // I/O file, stdout
        string filename = argv[1];
        ifstream inputFile;
        inputFile.open(filename);

        if (not inputFile.is_open()) {
            cerr << "Unable to open file " << filename << endl;
            return 1;
        }
        else {
            sd.run(inputFile, cout);
            inputFile.close();
        }
    }

    else { // I/O stdin, stdout
        sd.run(cin, cout);  
    } 
 
    return 0;
}
