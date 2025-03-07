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
        levels[i]->currentLevelIndex=i;
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

    levels[currentLevelIndex]->placeMario(getInitialLives());
    cout<<"Mario is starting at position"<<levels[currentLevelIndex]->getMarioPosition()<<endl;
    cout<<"=========="<<endl;     
    levels[currentLevelIndex]->printGrid();  
    cout<<"=========="<<endl;  
};



void World::RunGame(){
    FileProcessor* FP = new FileProcessor("Input.txt", "Output.txt");
    int* FileContents = FP->ReadFile();

    ostringstream outputBuffer;
    streambuf* oldCout = cout.rdbuf(outputBuffer.rdbuf());  // THIS CAUSES THE CRASH
    cout.rdbuf(oldCout); // Restore std::cout


    setAttributes(FileContents);

    World* W = new World(getNumLevels(), getDimensions(), getCoinPct(), getNothingPct(), getGoobaPct(), getKoopaPct(), getMushPct(), getInitialLives());
    W->printWorld();

   
    //W->printFirstStatus(); // Redirects printed output to buffer
    for(int i = 0; i < getNumLevels(); i++){
        Level* currentLevel = W->getCurrentLevel();
        if(i>0){currentLevel->placeMario(getInitialLives());}
        int NWSE = rand() % 4;
        

        W->printFirstStatus(); 
        currentLevel->printUpdate(W->currentLevelIndex, NWSE);
        while(!currentLevel->isGameOver()){
            //if(W->levels[0]->Move(NWSE)){break;
            //cout << "Mario is moving in direction: " << NWSE << endl;
            // Move Mario and check if he reaches the boss or warp
            if (currentLevel->Move(NWSE)) {
                if(currentLevelIndex == getNumLevels()-1 && !currentLevel->isGameOver()){
                    cout << "You Beat the Game and Saved the Princess!!"<< endl;
                    return;
                }

                if(currentLevel->isGameOver()) {
                    cout << "WE LOST THE GAME! :(" << endl;
                    return;
                }
                if(currentLevel->lostBossBattle){
                    W->addMove();
                    currentLevel->fightBossAgain();
                    while(currentLevel->lostBossBattle){
                        W->addMove();
                        currentLevel->fightBossAgain();
                    }
                    cout << "You Beat the Game and Saved the Princess!!"<< endl;
                    return;
                        //currentLevel->printUpdate(W->currentLevelIndex, NWSE);'
                }
                if(currentLevelIndex <= getNumLevels()-1 && currentLevel->warped){
                    cout<< "Youve Warped to the Next Level"<< endl;
                    break;
                }
            // if(didWeWin()){
            //     cout << "You Beat the Game and Saved the Princess!!"<< endl;
            // }
            // if(currentLevel->isGameOver()){cout<<"You lost to da boss"<<endl;}
            //if(currentLevel->beatBoss){return;}
            //currentLevel->printUpdate(W->currentLevelIndex, NWSE);
            break; 
        
            }
            W->addMove();
            NWSE = rand() % 4;
            currentLevel->printUpdate(W->currentLevelIndex, NWSE);

        }                                                           





        // If game over, stop game

        if(W->getCurrentLevel()->beatBoss && W->currentLevelIndex == W->getNumLevels()){
            cout << "You Beat the Game and Saved the Princess!!"<< endl;
            return;
        } 


        //currentLevel->printGrid();
        // Advance to the next level if Mario wins or finds a warp
        W->nextLevel();
        

    }
    // if(W->getCurrentLevel()->beatBoss){
    //     cout << "You Beat the Game and Saved the Princess!!"<< endl;
    // } 
        
    
    cout << "Mario moved: " << W->getMoves() << " times!" << endl;
    
   // cout.rdbuf(oldCout); // Restore std::cout
    FP->WriteToFile(outputBuffer.str());
    


    //M.UpdateGame(W.getCurrentLevel(),10);
    delete W;
    delete FP;




};



int World::getMoves(){
    return moves;
};


int World::addMove(){
    moves++;
};


bool World::didWeWin(){
    return (currentLevelIndex == numLevels) && (getCurrentLevel()->beatBoss == true);
}






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

