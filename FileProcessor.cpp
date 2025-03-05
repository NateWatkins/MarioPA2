#include "FileProcessor.h"

#include <string>
#include <fstream>






using namespace std;


FileProcessor::FileProcessor(string inFilename,string outFilename){
    inFile.open(inFilename);
    outFile.open(outFilename);
    FileContents = new int[8]; 
    ReadFile();
    // intializing memory and allowing other files to access it
} // need to know the constructor belongs to the file processor class


FileProcessor::~FileProcessor(){
    delete[] FileContents;  // Free allocated memory
    
    if (inFile.is_open()) inFile.close();  // Close files if open
    if (outFile.is_open()) outFile.close();
}



void FileProcessor::WriteToFile(string line){
    if (outFile.is_open()){
        std::cout << "Writing to file: " << line << std::endl;
        std::cout << "File is open " << std::endl;
        outFile << line << endl;
    } else {
        std::cout << "File not open.";
    }
    //outFile.close();
}




int* FileProcessor::ReadFile(){
    int i = 0;
    string line;
    while (inFile >> line){
        FileContents[i] = stoi(line);
        ++i;
    }
    return FileContents; 
}