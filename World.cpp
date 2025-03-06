#include "Mario.h"
#include "World.h"
#include "FileProcessor.h"
#include "Level.h"
#include <iostream>
#include <sstream>






World::World(){

}

World::World(int numWorlds,int dimensions, int coinPct, int emptyPct, int goombaPct,int koopaPct, int mushPct, int numInitialLives){
    this->numWorlds = numWorlds;
    levels = new Level*[numWorlds];

    for(int i = 0; i< numWorlds; i++){ 
        if(i==(numWorlds-1)){
            levels[i] = new Level(dimensions,coinPct, emptyPct,goombaPct, koopaPct,  mushPct, true, numInitialLives);
        }else{
            levels[i] = new Level(dimensions,coinPct, emptyPct,goombaPct, koopaPct,  mushPct, false, numInitialLives);
        }



    }

};





void World::printWorld(){
    
    for(int i =0; i< numWorlds; i++){
        levels[i]->printGrid(); // Used a pointer becasue it points to the Level object inside of the array
        cout<<endl;
        cout<<"=========="<<endl;
    }
};


Level* World::getCurrentLevel() {
    return levels[currentLevelIndex];
}


// Add a function to advance to the next level
void World::nextLevel() {
    if (currentLevelIndex < numWorlds - 1) {
        currentLevelIndex++;  
    }
}

World::~World(){ 
    for (int i = 0; i < numWorlds; i++) {
        delete levels[i];  
    }
    delete[] levels;

}



void World::setAttributes(int* values) { // setting values
    numLevels = values[0];
    dimensions = values[1];
    initialLives = values[2];
    coinPct = values[3];
    nothingPct = values[4];
    goobaPct = values[5];
    koopaPct = values[6];
    mushPct = values[7];
};


void World::printFirstStatus(){
    printWorld();
    levels[0]->placeMario(getInitialLives());
    cout<<"Mario is starting at position"<<levels[0]->getMarioPosition()<<endl;
    cout<<"=========="<<endl;       
    
};



void World::RunGame(){
    FileProcessor FP = FileProcessor("Input.txt", "Output.txt");
    int* FileContents = FP.ReadFile();
    setAttributes(FileContents);
    
    World W = World(getNumLevels(), getDimensions(), getCoinPct(), getNothingPct(), getGoobaPct(), getKoopaPct(), getMushPct(), getInitialLives());
    //Goes through Each Level
    
    //Make mario
    
    //Comment THIS IS CHATGPT
    
    ostringstream outputBuffer;
    streambuf* oldCout = cout.rdbuf(outputBuffer.rdbuf());
    W.printFirstStatus(); // Redirects printed output to buffer
    cout.rdbuf(oldCout); // Restore std::cout
    FP.WriteToFile(outputBuffer.str());
    for(int i = 0; i < getNumLevels(); i++){
    
    }
    //M.UpdateGame(W.getCurrentLevel(),10);

};
























int World::getNumLevels() {
    return numLevels;
};

int World::getDimensions(){
    return dimensions;
};

int World::getInitialLives(){
    return initialLives;
};

int World::getCoinPct() {
    return coinPct;
};

int World::getNothingPct() {
    return nothingPct;
};

int World::getGoobaPct() {
    return goobaPct;
};

int World::getKoopaPct() {
    return koopaPct;
};

int World::getMushPct() {
    return mushPct;
};

