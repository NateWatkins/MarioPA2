/*
Marshall Longtin and Nate Watkins
2438966 and 2443602
longtin@chapman.edu and nwatkins@chapman.edu
CPSC 350-02 and 350-01
PA2
*/

#include <iostream>

#ifndef MARIO_H
#define MARIO_H

class Level;
class Enemy;

using namespace std;


class Mario{
    public:
        Mario(int inputLives, int inputRow, int inputColumn); //overloading constructor
        ~Mario(); //deconstructor
        Mario(); // constructor

        
        
        //bool Move(Level* s,int NWSE);
        void collectCoin();
        void eatMushroom();
        bool fightEnemy(char enemyType);
        //void UpdateGame(Level* s);


        //Might be redundant

        void killedEnemy();
        int getLives();
        void getPosition(Level* s); // This function will set the member variables row and column
        bool needsWrap(char** grid, int NWSE, int dimensions);
        void checkWinStreak(int enemiesKilled);

        void displayStats();

        bool fightGooba();
        bool fightKoopa();
        bool fightBoss();
        void lostBattle();
        bool isGameOver();



        // Getters
        char getOldChar();
        int getNumCoins();
        int getNumLives();
        int getPwrLvl();
        int getEnemiesKilled();
        int getRow();
        int getColumn();
        string getEncounter();


        // Setters
        void setOldChar(char value);
        void setNumCoins(int value);
        void setNumLives(int value);
        void setPwrLvl(int value);
        void setEnemiesKilled(int value);
        void setRow(int value);
        void setColumn(int value);
        void setEncounter(string newEncounter);

    private:
        string encounter = "Mario visited an empty space.";
        char oldChar;
        int numCoins=0;
        int numLives;
        int pwrLvl = 1;
        int enemiesKilled = 0;
        int row;
        int column;
        int inputLives; 


};

#endif // MARIO_H


