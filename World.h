
#include "Mario.h"

#include "FileProcessor.h"
#include "Level.h"

using namespace std;


#ifndef WORLD_H
#define WORLD_H



class World{
    public:
        World();
        World(int numWorlds,int dimensions, int coinPct, int emptyPct, int goombaPct,int koopaPct, int mushPct, int numInitialLives);
        ~World();
        

        string FinalMessage;


        int numWorlds;
        Level** levels;
        
        void printWorld();
        Level* getCurrentLevel();
        void nextLevel();
        
        void RunGame();

        void setAttributes(int* values);
        void printFirstStatus();
        //Getters
        int getNumLevels();
        int getDimensions();
        int getInitialLives();
        int getCoinPct();
        int getNothingPct();
        int getGoobaPct();
        int getKoopaPct();
        int getMushPct();


        int getMoves();
        int addMove();
        bool didWeWin();


    private:
        int numLevels;
        int dimensions;
        int initialLives;
        int coinPct;
        int nothingPct;
        int goobaPct;
        int koopaPct;
        int mushPct;

        int currentLevelIndex;
        

        int moves = 0;
};




#endif //WORLD.H