#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include "Mario.h"


using namespace std;


// start
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