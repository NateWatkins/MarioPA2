/*
Marshall Longtin and Nate Watkins
2438966 and 2443602
longtin@chapman.edu and nwatkins@chapman.edu
CPSC 350-02 and 350-01
PA2
*/
#include <iostream>
#include "Mario.h"

#ifndef ENEMY_H
#define ENEMY_H





using namespace std;

class Enemy{
    public:

        Enemy(); // constructor 
        ~Enemy(); // deconstructor 
        

        bool fightGooba(); // fight Gooba
        bool fightKoopa(); // fight Koopa
        bool fightBoss(); // fight Boss
        //void applyFight(bool won, Mario mario, char enemyType);

};


#endif //ENEMY_H



