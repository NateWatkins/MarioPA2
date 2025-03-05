#include <iostream>
#include "Mario.h"

#ifndef ENEMY_H
#define ENEMY_H





using namespace std;

class Enemy{
    public:

        Enemy();
        ~Enemy();
        

        bool fightGooba();
        bool fightKoopa();
        bool fightBoss();
        //void applyFight(bool won, Mario mario, char enemyType);

};


#endif //ENEMY_H



