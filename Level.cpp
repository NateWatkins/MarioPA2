/*
Marshall Longtin and Nate Watkins
2438966 and 2443602
longtin@chapman.edu and nwatkins@chapman.edu
CPSC 350-02 and 350-01
PA2
*/

#include "Level.h"
#include <random>
#include <cstdlib>  
#include <ctime> 
#include "Mario.h"


using namespace std;



//Used ChatGpt to add the default Mario case to the constructor so that it is initialized before placing Mario in the World. Giving Mario (x,y) is temporary so it shouldn't effect anything


Level::Level(int dimensions, int coinPct, int emptyPct, int goombaPct,int koopaPct, int mushPct, bool isLastLevel, int numInitialLives) : M(0,0,0){ 
    this->dimensions = dimensions;
    grid = new char*[dimensions];
    for (int i = 0; i < dimensions; i++) {
        grid[i] = new char[dimensions];
    }
    srand(time(0));
    // put boss and warp into random place on grid
    int bossX = rand() % dimensions; 
    int bossY = rand() % dimensions;
    int warpX = rand() % dimensions;
    int warpY = rand() % dimensions;

    //Edge Case Protection. Makes sure boss and warp cannot be put in the same place on the grid.
    while (bossX == warpX && bossY == warpY) {
        warpX = rand() % dimensions;
        warpY = rand() % dimensions;
    }       
    //This creates a populated standard grid without warps or bosses
    for(int i = 0; i < dimensions; i++){
        for(int j = 0; j < dimensions; j++){
            int randPercent = rand() % 100;

            if(randPercent < coinPct){
                grid[i][j] = 'c';
            }else if(randPercent < (coinPct + emptyPct)){
                grid[i][j] = 'x';
            }else if(randPercent < (coinPct+emptyPct+goombaPct)){
                grid[i][j] = 'g';
            }else if(randPercent<(coinPct+emptyPct+goombaPct+koopaPct)){
                grid[i][j] = 'k';
            }else{
                grid[i][j] = 'm';
            }

        }
    }
    if(!isLastLevel){ // makes sure there is no warp in last level
        grid[warpY][warpX] = 'w';
        
    } // puts in a boss
    grid[bossY][bossX] = 'b';
};


Mario& Level::getMario() {
    return M;
}


string directions[] = {"North", "West", "South", "East"};

void Level::printUpdate(int NWSE){
    cout << "Level: 0. Mario is at position: (" << dimensions - M.getRow() - 1 << "," << M.getColumn() << "). "
        << "Mario is at power level " << M.getPwrLvl() << ". "
        << "Mario visited " << M.getEncounter() << ". "
        << "Mario has " << M.getNumLives() << " lives left. "
        << "Mario has " << M.getNumCoins() << " coins. "
        << "Mario will move " << directions[NWSE] << "." << endl;
}

//Use the built in to_string function
string Level::getMarioPosition(){
    string s = ("(" + to_string(M.getRow()) + ", " + to_string(M.getColumn()) + ")");
};

//Move function-> where I move mario and encounter the new space and update the board accourdingly. This will be the main driver of the program. 
bool Level::Move(Mario& M, int NWSE){
    if(M.isGameOver()){
        return true;
    }
    int oldCordX = M.getColumn(); 
    int oldCordY = M.getRow(); 

    int newCordX = M.getColumn(); 
    int newCordY = M.getRow();

 
    M.setOldChar(grid[oldCordY][oldCordX]); //This is the last character
    

    //These chunks are pulling the cordinates of marios next position
    if(NWSE == 0){ //North
        if(M.needsWrap(grid, 0, dimensions)){
            newCordY = dimensions-1; // moves from top of grid to the bottom of the grid (in the case mario goes outside the dimensions established)
        }else{
            newCordY = M.getRow() - 1;
        }
    }else if(NWSE == 2){ //South
        if(M.needsWrap(grid, 2, dimensions)){ // moves from bottom of grid to the top of the grid (in the case mario goes outside the dimensions established)
            newCordY = 0;
        }else{
            newCordY = M.getRow()+1 ;
        }
    }if(NWSE == 1){ //West
        if(M.needsWrap(grid, 1,dimensions )){ // far left side of the grid to the far right side (in the case mario goes outside the dimensions established)
            newCordX = dimensions -1 ;
        }else{
            newCordX = M.getColumn() -1;
        }
    }else if(NWSE == 3){ // East
        if(M.needsWrap(grid, 3, dimensions)){ // far right side to the far left side (in the case mario goes outside the dimensions established)
            newCordX = 0;
        }else{
            newCordX = M.getColumn() + 1;
        }
    }

    M.setRow(newCordY); //Row is now the Mario's Next Position
    M.setColumn(newCordX); //Column is now Mario's Next Position


    //========================================================================
    //THis section handles the interactions with the enemies

    //Everyloss I need to reset Enemies Killed to reset the win streak

    char occupiedSpace = grid[M.getRow()][M.getColumn()];
    if(occupiedSpace == 'c'){ // mario adds coin to inventory and leaves an 'x' behind him to mark that its empty
        M.collectCoin();
        M.setOldChar('x');
        M.setEncounter("a coin");
    }else if(occupiedSpace == 'g'){ 
        if(M.fightGooba()){ // If mario wins -> Add to enemies killed, 
            M.killedEnemy(); // kills the enemy
            M.checkWinStreak(M.getEnemiesKilled()); //adds and checks win streak
            M.setOldChar('x'); // leaves an 'x' behind him to mark that its empty
            M.setEncounter("a Goomba and won");
        }else{ // If mario loses
            M.lostBattle(); //if he loses the battle
            M.setOldChar('x'); // moves on and leaves an 'x'
            M.setEnemiesKilled(0); // since he lost a life enemy kill count is reset
            M.setEncounter("a Goomba and lost");
        }
    }else if(occupiedSpace == 'k'){
        if(M.fightKoopa()){
            M.killedEnemy();
            M.checkWinStreak(M.getEnemiesKilled());
            M.setOldChar('x');
            M.setEncounter("a Koopa and won");
        }else{ // If mario loses
            M.lostBattle();
            M.setOldChar('x');
            M.setEnemiesKilled(0);
            M.setEncounter("a Koopa and lost");
        
        }
    }else if(occupiedSpace == 'b'){
        if(M.fightBoss()){//Move on to next Level
            return true;
        }else{ // If mario loses
            M.lostBattle();
            M.setEnemiesKilled(0);
            M.setEncounter("a Boss and lost");//Go onto next Levtl
            return false;
        }
    }else if(occupiedSpace == 'm'){
        M.eatMushroom(); // eats a mushroom
        M.setOldChar('x'); // leaves an 'x' for empty space
        M.setEncounter("a mushroom");
    }else if(occupiedSpace =='w'){
        M.setEncounter("a warp portal and was teleported to the Next Level");
        M.setOldChar('x'); 
        return true;
    }else{
        M.setOldChar('x');
        M.setEncounter("an empty space");
    }




    grid[M.getRow()][M.getColumn()] = 'H';
    grid[oldCordY][oldCordX] = M.getOldChar();

    
    

    return false;
};



Level::~Level(){
    for (int i = 0; i < dimensions; i++) {
        delete[] grid[i];
    }
    delete[] grid;


};


void Level::printGrid() {
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) { // loops through grid elements and prints out a 2d grid
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
};

void Level::placeMario(int numInitialLives) { // lives is up to input file

    int numX = 0;

    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) {
            if (grid[i][j] == 'x') {
                numX++;
            }
        }
    }

    if (numX == 0){
        return; 
    }  

    int target = rand() % numX;
    numX = 0; 

    for (int first = 0; first < dimensions; first++) {
        for (int sec = 0; sec < dimensions; sec++) {
            if (grid[first][sec] == 'x') {
                if (numX == target) {  
                    grid[first][sec] = 'H';
                    M = Mario(numInitialLives, first, sec); // Need to define these 
                    return; 
                }
                numX++;
            }
        }
    }
}



