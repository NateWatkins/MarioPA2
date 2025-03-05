#include "Mario.h"
#include "World.h"
#include "FileProcessor.h"
#include "Level.h"
#include <iostream>
#include <sstream>






World::World(){
    this->numWorlds = 0;
    this->levels = nullptr;
    this->currentLevelIndex = 0;
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
        cout<<"=========="<<endl;
    }
};


Level* World::getCurrentLevel() {
    return levels[currentLevelIndex];
}


// Add a function to advance to the next level
void World::nextLevel() {
    if (this->currentLevelIndex < this->numWorlds - 1) {
        this->currentLevelIndex++;  
    }

}



World::~World(){
    if (levels) { 
    for (int i = 0; i < numWorlds; i++) {
        if (levels[i]) {
            delete levels[i];
            levels[i] = nullptr;  
        }
    }
    delete[] levels;
    levels = nullptr;  
    }
}



void World::setAttributes(int* values) {
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
    levels[0]->printGrid();  
    cout<<"=========="<<endl;  
};



void World::RunGame(){
    FileProcessor* FP = new FileProcessor("input.txt", "output.txt");
    int* FileContents = FP->ReadFile();

    ostringstream outputBuffer;

cout << "After redirection" << endl;

    setAttributes(FileContents);
    cout<<getInitialLives()<<endl;

    cout << "numLevels: " << getNumLevels() << endl;
    cout << "dimensions: " << getDimensions() << endl;
    cout << "initialLives: " << getInitialLives() << endl;
    cout << "coinPct: " << getCoinPct() << endl;
    cout << "nothingPct: " << getNothingPct() << endl;
    cout << "goobaPct: " << getGoobaPct() << endl;
    cout << "koopaPct: " << getKoopaPct() << endl;
    cout << "mushPct: " << getMushPct()<<endl;
    

    World* W = new World(getNumLevels(), getDimensions(), getCoinPct(), getNothingPct(), getGoobaPct(), getKoopaPct(), getMushPct(), getInitialLives());


   
    //Comment THIS IS CHATGPT
    W->printFirstStatus(); // Redirects printed output to buffer
    for(int i = 0; i < getNumLevels(); i++){
        if(i>0){levels[currentLevelIndex]->placeMario(getInitialLives());}
        
        int NWSE = rand() % 4;
        
        Level* currentLevel = W->getCurrentLevel();


        while(!currentLevel->isGameOver()){
            //if(W->levels[0]->Move(NWSE)){break;
            currentLevel->printUpdate(W->currentLevelIndex, NWSE);
            //cout << "Mario is moving in direction: " << NWSE << endl;
            // Move Mario and check if he reaches the boss or warp
            if (currentLevel->Move(NWSE)) {
                break;  // Move to the next level
            }
            NWSE = rand() % 4;
        }  

        // If game over, stop game
        if(!currentLevel->isGameOver()) {
            cout << "Game Over! Mario has run out of lives." << endl;
            break;
        }

        // Advance to the next level if Mario wins or finds a warp
        W->nextLevel();
    }

    streambuf* oldCout = cout.rdbuf(outputBuffer.rdbuf());  // THIS CAUSES THE CRASH
    cout.rdbuf(oldCout); // Restore std::cout
    FP->WriteToFile(outputBuffer.str());
    //M.UpdateGame(W.getCurrentLevel(),10);
    delete W;
    delete FP;

    //FP = nullptr;
    
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

