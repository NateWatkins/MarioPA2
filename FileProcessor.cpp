/*
Marshall Longtin and Nate Watkins
2438966 and 2443602
longtin@chapman.edu and nwatkins@chapman.edu
CPSC 350-02 and 350-01
PA2
*/

#include "FileProcessor.h"
#include <string>
#include <fstream>


using namespace std;


FileProcessor::FileProcessor(string inFilename,string outFilename){
    inFile.open(inFilename); // open input file
    outFile.open(outFilename); // open output file
    FileContents = new int[8]; // establish/assign FileContents
    ReadFile(); // read the file output
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
        std::cout << "File is open " << std::endl; // Making sure file is open and then writing to it
        outFile << line << endl;
    } else {
        std::cout << "File not open."; // If its not open print this
    }
    //outFile.close();
}




int* FileProcessor::ReadFile(){
    int i = 0; 
    string line;
    while (inFile >> line){
        FileContents[i] = stoi(line); // Changing from string to an int
        ++i;
    }
    return FileContents; 
}
