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



