//#include "constants.h"

class GameField : Game {
public:
   GameField();
   int checkCoords(int,int);
   Game* getRefCoords(int ,int);
   void setCoords(int,int,int,Game*);
private:
   int gameFieldArrOfType[LIMIT_RIGHT-LIMIT_LEFT+1][LIMIT_DOWN-LIMIT_UP+1];
   Game* gameFieldArrOfRef[LIMIT_RIGHT-LIMIT_LEFT+1][LIMIT_DOWN-LIMIT_UP+1];
};

GameField::GameField() {  };

int GameField::checkCoords(int x,int y) {
    return(gameFieldArrOfType[x][y]);
}

Game* GameField::getRefCoords(int x,int y) {
    return(gameFieldArrOfRef[x][y]);
}
void GameField::setCoords(int x,int y, int typeOfObject, Game* refOfObject) {
gameFieldArrOfType[x][y]=typeOfObject;
gameFieldArrOfRef[x][y]=refOfObject;
}


