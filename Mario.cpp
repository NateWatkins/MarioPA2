/*
Marshall Longtin and Nate Watkins
2438966 and 2443602
longtin@chapman.edu and nwatkins@chapman.edu
CPSC 350-02 and 350-01
PA2
*/
#include "Mario.h"
#include "Level.h"
#include <cstdlib>  
#include <ctime> 
#include "World.h"

using namespace std;

Mario::Mario(){
}



Mario::Mario(int inputLives, int inputRow, int inputColumn){
    this->numLives = inputLives; 
    this->row = inputRow;
    this->column = inputColumn;
};

Mario::~Mario(){};


//Test Function
void Mario::displayStats() {
    cout << "Mario Stats:" << endl;
    cout << "Lives: " << numLives << endl;
    cout << "Position: (" << row << ", " << column << ")" << endl;
    cout << "Power Level: " << pwrLvl << endl;
    cout << "Coins: " << numCoins << endl;
    cout << "Enemies Killed: " << enemiesKilled << endl;
};


bool Mario::isGameOver(){
    return numLives <= 0;
};







void Mario::getPosition(Level* s){
    int dim = s->dimensions;

    for(int i = 0; i<dim; i++){
        for(int j =0; j<dim; j++){
            if(s->grid[i][j] == 'H'){
                this->row = i;
                this-> column = j;
            }
        }
    }



};


//To Check whether it needs to be wrapped around the array
bool Mario::needsWrap(char** grid, int NWSE, int dimensions){
    int dim = dimensions- 1;
    
    //This was the first attempt 
    /*
    if(row==0||column==0||row==dim||column==dim){ // All this did was create a frame around the array that pings if Mario is there 
        return true;
    }else{
        return false;
    }
    */

    if(row == 0 && NWSE==0){
        return true;
    }else if(row==dim && NWSE==2){
        return true;
    }else if(column ==0 && NWSE==1){
        return true;
    }else if(column==dim && NWSE==3){
        return true;
    } else{
        return false;
    }

};




// void Mario::UpdateGame(Level* s){
//     srand(time(0));
//     int NWSE;
//     //Get the direction
//     NWSE = rand() % 4;
//     if(!Move(s,NWSE) && !isGameOver()){
//         return; //END THE GAMMEEEEE
//     }
    
//     s->printGrid();
// };    


void Mario::checkWinStreak(int enemiesKilled){
        if (enemiesKilled == 7){ // following game logic and adding a life to mario if he kills 7 enemies in the span of one life
            numLives++;
            enemiesKilled=0;
        }
};





//string directions[] = {"North", "West", "South", "East"};






void Mario::killedEnemy(){
    enemiesKilled++; // adding to kill count
};




//Reduces power level or reduces a life. Breaks the enemyKilled streak 
void Mario::lostBattle(){
    pwrLvl--;
    enemiesKilled = 0;
    if(pwrLvl<= 0){ // Lose a life and power level stays 0
        numLives--;
        pwrLvl = 0; // reset pwrLvl
    }
};




//Return True if Mario Wins
bool Mario::fightGooba(){
    return !((rand() % 5)==0); // returns true 4/5-> 80% chance
};


bool Mario::fightKoopa(){
    return ((rand() % 100) <= 65); // 65% chance to win
};


bool Mario::fightBoss(){ // 50% chance to defeat boss
    return((rand()%2 == 0));
};

void Mario::collectCoin(){ // adding to coin count and if he gets 20 in a lifespan he earns another life and his coin count goes back to zero
    numCoins++; 
    if(numCoins==20){
        numCoins = 0;
        numLives++;
    } 
};

void Mario::eatMushroom(){ // Mario gains a pwrLvl unless he already is at PL2
    if(pwrLvl<2){
        pwrLvl++;
    }
};



//Getters
string Mario::getEncounter(){
    return encounter; 
}

char Mario::getOldChar(){ 
    return oldChar; 
};
int Mario::getNumCoins(){ 
    return numCoins; 
};
int Mario::getNumLives(){ 
    return numLives; 
};
int Mario::getPwrLvl(){ 
    return pwrLvl; 
};
int Mario::getEnemiesKilled(){ 
    return enemiesKilled; 
};
int Mario::getRow(){ 
    return row;
};
int Mario::getColumn(){ 
    return column; 
};

// Setters
void Mario::setEncounter(string newEncounter) { 
    encounter = newEncounter; 

}
void Mario::setOldChar(char value){ 
    oldChar = value; 
};
void Mario::setNumCoins(int value){ 
    numCoins = value; 
};
void Mario::setNumLives(int value){ 
    numLives = value; 
};
void Mario::setPwrLvl(int value){ 
    pwrLvl = value; 
};
void Mario::setEnemiesKilled(int value){ 
    enemiesKilled = value; 
};
void Mario::setRow(int value){ 
    row = value; 
};
void Mario::setColumn(int value){ 
    column = value; 
};
