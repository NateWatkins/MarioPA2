/*
Marshall Longtin and Nate Watkins
2438966 and 2443602
longtin@chapman.edu and nwatkins@chapman.edu
CPSC 350-02 and 350-01
PA2
*/

#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include "Mario.h"


using namespace std;


// Declare methods and functions so we can implement them in the cpp files
class FileProcessor{
    public:
        void WriteToFile(string line);
        int* ReadFile();


        FileProcessor* FP;
        int* FileContents;
        FileProcessor(string inFilename,string outFilename);
        ~FileProcessor();

    private:
        ifstream inFile;
        ofstream outFile;
        
         // int pointer in class
};

#endif
