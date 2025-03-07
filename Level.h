#include <iostream>
#include "Mario.h"




#ifndef LEVEL_H
#define LEVEL_H
using namespace std;




class Level{
    public:

        Level(int dimensions, int coinPct, int emptyPct, int goombaPct,int koopaPct, int mushPct, bool isLastLevel, int numInitialLives);
        ~Level();

        bool Move(int NWSE);
        string getMarioPosition();
        Mario& getMario();



        int initLives;
        int dimensions;

        void printLostToBoss();

        void fightBossAgain();     

        void printUpdate(int currentLevelIndex, int NWSE);
        void printGrid();
        char** grid;
        void placeMario(int numInitialLives);
        bool isGameOver();

        int oldCordX;
        int oldCordY;
        bool lostBossBattle;
        int MarioStartX;
        int MarioStartY;
        
        bool warped = false;

        bool beatBoss = false;
        int currentLevelIndex;

    private:
        
        int moves;
        Mario M;
        bool isLastLevel;

        


    
};

#endif