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


        int dimensions;


        void printUpdate(int NWSE);
        void printGrid();
        char** grid;
        void placeMario(int numInitialLives);
        bool isGameOver();
        
        
    private:
        Mario M;
        bool isLastLevel;

        


    
};

#endif