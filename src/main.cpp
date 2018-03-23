#include <iostream>
#include <windows.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include "rlutil.h"

#include "constants.h"

struct xy {
  int x;
  int y;
  int ret;
};


using namespace std;

class Game{
public:
    Game();
    };
Game::Game(){};


#include "gamefield.h"
int gameTime;
GameField* gameField= new GameField();


#include "brick.h"

std::vector <class OrdinaryBrick *> vectorOfBrick;

#include "bullet.h"

std::vector <class Bullet *> vectorOfBullet;

#include "tank.h"

std::vector <class EnemyTank *> vectorOfEnemyTank;


void paint_borders()
{

   for (int i = LIMIT_LEFT; i <= LIMIT_RIGHT; ++i) {
      gotoxy(i, LIMIT_UP); printf("%c", 205);
      gotoxy(LIMIT_RIGHT - i + LIMIT_LEFT, LIMIT_DOWN); printf("%c", 205);
      Sleep(10);
   }

   for (int i = LIMIT_UP; i <= LIMIT_DOWN; ++i) {
      gotoxy(LIMIT_LEFT, i); printf("%c", 186);
      gotoxy(LIMIT_RIGHT, LIMIT_DOWN - i + LIMIT_UP); printf("%c", 186);
      Sleep(10);
   }

   // corners
   gotoxy(LIMIT_LEFT, LIMIT_UP); printf("%c", 201);
   gotoxy(LIMIT_RIGHT, LIMIT_UP); printf("%c", 187);
   gotoxy(LIMIT_LEFT, LIMIT_DOWN); printf("%c", 200);
   gotoxy(LIMIT_RIGHT, LIMIT_DOWN); printf("%c", 188);
}

void printGameTime(){
   gotoxy(60, 1); printf("%5d", gameTime / (1000/SLEEP_TIME) );
   }


int main()
{
srand(time(NULL));

paint_borders();

int tempX;
int tempY;
//create bricks
for (int tempI=1 ; tempI<=10 ; tempI++){
   do{
   tempX=(LIMIT_RIGHT-LIMIT_LEFT) /2  + (rand() % (LIMIT_RIGHT/2-3) + LIMIT_LEFT);
   tempY=(LIMIT_DOWN -LIMIT_UP) / 2 + (rand() % (LIMIT_DOWN/2-3) + LIMIT_UP);
   }while( gameField->checkCoords(tempX,tempY) >0 );

   OrdinaryBrick* brickT = new OrdinaryBrick(tempX,tempY);
   vectorOfBrick.push_back(brickT);
   Brick* ttt1=(Brick*)brickT;
   ttt1->print();

   bool xyflag = rand() % 2;
   for (int tempII=1 ; tempII<=(rand() % 7 + 1) ; tempII++){
   if (gameField->checkCoords(tempX+(xyflag*tempII),tempY+(1-xyflag)*tempII)>0) break;
   brickT = new OrdinaryBrick(tempX+(xyflag*tempII),tempY+(1-xyflag)*tempII);
   vectorOfBrick.push_back(brickT);
   ttt1=(Brick*)brickT;
   ttt1->print();
   }
   };


   //create enemy tanks
   for (int tempI=1 ; tempI<=7 ; tempI++){
   bool tempFl;
   do{
   tempFl=false;
   tempX=(LIMIT_RIGHT - LIMIT_LEFT) /2  + (rand() % (LIMIT_RIGHT/2-3) + 1);
   tempY=(LIMIT_DOWN - LIMIT_UP) / 2 -7 + (rand() % (LIMIT_DOWN/2-3) + 1);
   for(int tempXx=tempX-2 ; tempXx<=tempX+3+2 ; tempXx++)
   for(int tempYy=tempY-2 ; tempYy<=tempY+3+2 ; tempYy++)
   if ( gameField->checkCoords(tempXx,tempYy) > 0 ) tempFl=true;
   }while( tempFl );
   EnemyTank* tankT = new EnemyTank(tempX,tempY , false);
   vectorOfEnemyTank.push_back(tankT);
   Tank* ttt2=(Tank*)tankT;
   ttt2->print();
   };


   //create our tank
   OurTank* ourTank = new OurTank( (LIMIT_RIGHT - LIMIT_LEFT) /2, (LIMIT_DOWN + LIMIT_UP) -4 , false);
   Tank* ourTankO=(Tank*)ourTank;
   ourTankO->print();

   gameTime=0;

   int bypassMove=0;

   while(true){ //gameloop

//move bullets
xy tempxy;
for (int tempI = 0; tempI <  vectorOfBullet.size(); ++tempI){
tempxy=vectorOfBullet[tempI]->mover();
//gotoxy(1,1);
//cout << tempxy.ret;

if ( (tempxy.ret==OBJECT_ENEMY_TANK)&&!(vectorOfBullet[tempI]->isEnemy) )
{
Game* tempRef;
tempRef=gameField->getRefCoords(tempxy.x,tempxy.y);
Tank* tempRefT=(Tank*)tempRef;
tempRefT->animateDie();
tempRefT->del();

gameField->delRefCoords( tempRef);

//vectorOfEnemyTank
EnemyTank* tempRefTt=(EnemyTank*)tempRef;
size_t j = 0;
for (size_t i = 0; i < vectorOfEnemyTank.size(); ++i) {
    if (vectorOfEnemyTank[i] != tempRefTt) vectorOfEnemyTank[j++] = vectorOfEnemyTank[i];
  }
vectorOfEnemyTank.resize(j);

delete tempRefT;
vectorOfBullet[tempI]->del();
vectorOfBullet.erase(vectorOfBullet.begin() + tempI);
delete vectorOfBullet[tempI];
}

}

bypassMove=1-bypassMove;
if(bypassMove)
{

//move our tank
char kbchar =0;
if (kbhit()) {
      kbchar = getch();
      if ( (kbchar == MOVE_LEFT) || (kbchar == MOVE_RIGHT) || (kbchar == MOVE_DOWN) || (kbchar == MOVE_UP) )  ourTankO->direction=kbchar;

   };

ourTankO->mover();

 if (kbchar ==SHOOT)
      {
          ourTankO->fire();
       }

//move enemy tanks
for (int tempI = 0; tempI <  vectorOfEnemyTank.size(); ++tempI) {
    Tank* ttt3=(Tank*)vectorOfEnemyTank[tempI];
    if ( (rand() % 10 + 1)>7 )    {
            int tempII=rand() % 4 + 1;
           switch(tempII) {
            case 1:
            tempII=MOVE_LEFT;
            break;
            case 2:
            tempII=MOVE_RIGHT;
            break;
            case 3:
            tempII=MOVE_DOWN;
            break;
            case 4:
            tempII=MOVE_UP;
            break;
            };
            ttt3->direction=tempII;
}

    ttt3->mover();
}

}//bypass move



gameTime++;
printGameTime();

Sleep(SLEEP_TIME);
   };//end gameloop

};

