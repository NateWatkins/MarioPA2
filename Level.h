#include <iostream>
#include "Enemy.h"
#include "Mario.h"




#ifndef LEVEL_H
#define LEVEL_H
using namespace std;




class Level{
    public:

        Level(int dimensions, int coinPct, int emptyPct, int goombaPct,int koopaPct, int mushPct, bool isLastLevel, int numInitialLives);
        ~Level();
        
        bool Move(Mario& M, int NWSE);
        string getMarioPosition();
        Mario& getMario();


        int dimensions;
        void updatePosition(int x, int y, char Obj);
        bool checkWarp(int x, int y);


        void printUpdate(int NWSE);
        void printGrid();
        char** grid;
        void placeMario(int numInitialLives);
        
    private:
        Mario M;
        bool isLastLevel;

        


    
};

#endif