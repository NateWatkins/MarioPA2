#include "Level.h"
#include <random>
#include <cstdlib>  
#include <ctime> 
#include "Mario.h"


using namespace std;



//Used ChatGpt to add the default Mario case to the constructor so that it is initialized before placing Mario in the World. Giving Mario (x,y) is temporary so it shouldn't effect anything


Level::Level(int dimensions, int coinPct, int emptyPct, int goombaPct,int koopaPct, int mushPct, bool isLastLevel, int numInitialLives){ 
    this->initLives = numInitialLives;

    this->dimensions = dimensions;
    this->grid = new char*[dimensions];
    for (int i = 0; i < dimensions; i++) {
        this->grid[i] = new char[dimensions];
    }
    int bossX = rand() % dimensions;
    int bossY = rand() % dimensions;
    int warpX = rand() % dimensions;
    int warpY = rand() % dimensions;

    //Edge Case Protection
    while (bossX == warpX && bossY == warpY) {
        warpX = rand() % dimensions;
        warpY = rand() % dimensions;
    }       
    
    MarioStartX = rand() % dimensions;
    MarioStartY = rand() % dimensions;

    while((MarioStartX == warpX || MarioStartX == bossX) && (MarioStartY == warpY || MarioStartY == bossY)){
        MarioStartX = rand() % dimensions;
        MarioStartY = rand() % dimensions;
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
    if(!isLastLevel){
        grid[warpY][warpX] = 'w';
        
    }
    grid[bossY][bossX] = 'b';
};







Mario& Level::getMario() {
    return M;
}


string directions[] = {"UP", "LEFT", "DOWN", "RIGHT"};




void Level::printUpdate(int currentLevelIndex, int NWSE){
    if(warped && M.getNumLives()>0){
        cout << "Level: "<< currentLevelIndex <<". Mario is at position: (" << M.getColumn() << "," << M.getRow() << "). "
        << "Mario is at power level " << M.getPwrLvl() << ". "
        << "Mario visited " << M.getEncounter() << ". "
        << "Mario has " << M.getNumLives() << " lives left. "
        << "Mario has " << M.getNumCoins() << " coins. "
        << "Mario will go to the next level!!." << endl;
    cout<<"=========="<<endl;
    }else if(beatBoss && M.getNumLives()>0){
        cout << "Level: "<< currentLevelIndex <<". Mario is at position: (" << M.getColumn() << "," << M.getRow() << "). "
        << "Mario is at power level " << M.getPwrLvl() << ". "
        << "Mario visited " << M.getEncounter() << ". "
        << "Mario has " << M.getNumLives() << " lives left. "
        << "Mario has " << M.getNumCoins() << " coins. "
        << "Mario will move " << directions[NWSE] << "." << endl;
    cout<<"=========="<<endl;
    }
    cout << "Level: "<< currentLevelIndex <<". Mario is at position: (" << M.getColumn() << "," << M.getRow() << "). "
        << "Mario is at power level " << M.getPwrLvl() << ". "
        << "Mario visited " << M.getEncounter() << ". "
        << "Mario has " << M.getNumLives() << " lives left. "
        << "Mario has " << M.getNumCoins() << " coins. "
        << "Mario will move " << directions[NWSE] << "." << endl;
    cout<<"=========="<<endl;
}


void Level::printLostToBoss(int currentLevelIndex){
    cout<<"Mario Lost to the Boss on Level: "<< currentLevelIndex <<". Mario is at position: (" << M.getColumn() << "," << M.getRow() << "). "
        << "Mario is at power level " << M.getPwrLvl() << ". "
        << "Mario has " << M.getNumLives() << " lives left. "
        << "Mario has " << M.getNumCoins() << " coins. "<<endl;
    cout<<"=========="<<endl;
}




//Use the built in to_string function
string Level::getMarioPosition(){
    return ("(" + to_string(M.getColumn()) + ", " + to_string(M.getRow()) + ")");
};




//Move function-> where I move mario and encounter the new space and update the board accourdingly. This will be the main driver of the program. 
bool Level::Move(int NWSE){
    beatBoss = false;
    if(isGameOver()){
        return true;
    }
    oldCordX = M.getColumn();
    oldCordY = M.getRow(); 

    int newCordX = M.getColumn(); 
    int newCordY = M.getRow();

 
    M.setOldChar(grid[oldCordY][oldCordX]); //This is the last character
    

    //These chunks are pulling the cordinates of marios next position
    if(NWSE == 0){ //North
        if(M.needsWrap(grid, 0, dimensions)){
            newCordY = dimensions-1;
        }else{
            newCordY = M.getRow() - 1;
        }
    }else if(NWSE == 2){ //South
        if(M.needsWrap(grid, 2, dimensions)){
            newCordY = 0;
        }else{
            newCordY = M.getRow()+1 ;
        }
    }if(NWSE == 1){ //West
        if(M.needsWrap(grid, 1,dimensions )){
            newCordX = dimensions -1 ;
        }else{
            newCordX = M.getColumn() -1;
        }
    }else if(NWSE == 3){ // East
        if(M.needsWrap(grid, 3, dimensions)){
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
    if(occupiedSpace == 'c'){
        M.collectCoin();
        M.setOldChar('x');
        M.setEncounter("a coin");
    }else if(occupiedSpace == 'g'){
        if(M.fightGooba()){ // If mario wins -> Add to enemies killed, 
            M.killedEnemy();
            M.checkWinStreak(M.getEnemiesKilled());
            M.setOldChar('x');
            M.setEncounter("a Goomba and won");
        }else{ // If mario loses
            M.lostBattle();
            M.setOldChar('g');
            M.setEnemiesKilled(0);
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
            M.setOldChar('k');
            M.setEnemiesKilled(0);
            M.setEncounter("a Koopa and lost");
        }
    }else if(occupiedSpace == 'b'){
        while(!isGameOver()){
            if(M.fightBoss()){//Move on to next Level
                M.setOldChar('H');
                M.setEncounter("the Boss and won!");
                printGrid();
                //return true;
                beatBoss = true;
            }else{ // If mario loses
                M.lostBossBattle();
                M.setEnemiesKilled(0);
                M.setEncounter("a Boss and lost");
                lostBossBattle = false;
            }
        }
        printGrid();
        return true;
    }else if(occupiedSpace == 'm'){
        M.eatMushroom();
        M.setOldChar('x');
        M.setEncounter("a mushroom");
    }else if(occupiedSpace =='w'){
        M.setEncounter("a warp portal and was teleported to the Next Level");
        M.setOldChar('x');
        printGrid();
        return true;
    }else{
        M.setOldChar('x');
        M.setEncounter("an empty space");
    }


    grid[M.getRow()][M.getColumn()] = 'H';
    grid[oldCordY][oldCordX] = M.getOldChar();
    
    printGrid();


    
    

    return false;
};


bool Level::isGameOver(){
    return (M.getNumLives()<=0);
};


void Level::fightBossAgain(){
        while(!isGameOver()){
            if(M.fightBoss()){
                M.setEncounter("the Boss and won!");
                beatBoss = true;
                this->lostBossBattle = true;
                break;
            }else{ // If mario loses
                M.lostBossBattle();
                M.setEnemiesKilled(0);
                M.setEncounter("a Boss and lost");
            }
        }
}



Level::~Level(){
    for (int i = 0; i < dimensions; i++) {
        delete[] grid[i];
    }
    delete[] grid;

};





void Level::printGrid() {
    for (int i = 0; i < this->dimensions; i++) {
        for (int j = 0; j < this->dimensions; j++) {
            cout << this->grid[i][j] << " ";
        }
        cout << endl;
    }
    cout<<"=========="<<endl;
};



void Level::placeMario(int numInitialLives) {
 


    grid[MarioStartY][MarioStartX] = 'H';
    M.setRow(MarioStartY);
    M.setColumn(MarioStartX);
    M.setNumLives(initLives);


}



