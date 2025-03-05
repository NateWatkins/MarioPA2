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
        if (enemiesKilled == 7){
            numLives++;
            enemiesKilled=0;
        }
};





//string directions[] = {"North", "West", "South", "East"};






void Mario::killedEnemy(){
    enemiesKilled++;
};




//Reduces power level or reduces a life. Breaks the enemyKilled streak 
void Mario::lostBattle(){
    pwrLvl--;
    enemiesKilled = 0;
    if(pwrLvl<= 0){ // Lose a life and power level stays 0
        numLives--;
        pwrLvl = 0;
        // or do we put oldChar = 'x' in the lostBattle
    }
};




//Return True if Mario Wins
bool Mario::fightGooba(){
    return !((rand() % 5)==0); // returns true 4/5-> 80% chance
};


bool Mario::fightKoopa(){
    return ((rand() % 100) <= 65);
};


bool Mario::fightBoss(){
    return((rand()%2 == 0));
};

void Mario::collectCoin(){ 
    numCoins++;
    if(numCoins==20){
        numCoins = 0;
        numLives++;
    } 
};

void Mario::eatMushroom(){
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
