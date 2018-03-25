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
   gotoxy((LIMIT_RIGHT-LIMIT_LEFT)/2, LIMIT_UP); printf("%5d", gameTime / (1000/SLEEP_TIME) );
   }


void printLivesKills(OurTank* tank)
{
gotoxy(LIMIT_LEFT+2, LIMIT_UP); printf("Lives:%2d Kills:%2d", tank->lives , tank->kills );
};

int main()
{
srand(time(NULL));

paint_borders();

int tempX;
int tempY;

//create bricks for castle
int castleBaseX=(LIMIT_RIGHT - LIMIT_LEFT) /2 -7;
int castleBaseY=(LIMIT_DOWN - LIMIT_UP) -2 ;

OrdinaryBrick* brickC = new OrdinaryBrick(castleBaseX,castleBaseY);
((Brick *)brickC)->print();
brickC = new OrdinaryBrick(castleBaseX+1,castleBaseY);
((Brick *)brickC)->print();
brickC = new OrdinaryBrick(castleBaseX+2,castleBaseY);
((Brick *)brickC)->print();
brickC = new OrdinaryBrick(castleBaseX+3,castleBaseY);
((Brick *)brickC)->print();
brickC = new OrdinaryBrick(castleBaseX+4,castleBaseY);
((Brick *)brickC)->print();
brickC = new OrdinaryBrick(castleBaseX+5,castleBaseY);
((Brick *)brickC)->print();
brickC = new OrdinaryBrick(castleBaseX+6,castleBaseY);
((Brick *)brickC)->print();
brickC = new OrdinaryBrick(castleBaseX,castleBaseY+1);
((Brick *)brickC)->print();
brickC = new OrdinaryBrick(castleBaseX,castleBaseY+2);
((Brick *)brickC)->print();
brickC = new OrdinaryBrick(castleBaseX+6,castleBaseY+1);
((Brick *)brickC)->print();
brickC = new OrdinaryBrick(castleBaseX+6,castleBaseY+2);
((Brick *)brickC)->print();
brickC = new OrdinaryBrick(castleBaseX,castleBaseY-1);
((Brick *)brickC)->print();
brickC = new OrdinaryBrick(castleBaseX+3,castleBaseY-1);
((Brick *)brickC)->print();
brickC = new OrdinaryBrick(castleBaseX+6,castleBaseY-1);
((Brick *)brickC)->print();

//create GOLD
GoldBrick* brickG = new GoldBrick(castleBaseX+3,castleBaseY+1);
((Brick *)brickG)->print();




//create bricks
for (int tempI=1 ; tempI<=20 ; tempI++){
   do{
   tempX=LIMIT_LEFT  + (rand() % (LIMIT_RIGHT-3) + LIMIT_LEFT);
   tempY=LIMIT_UP + (rand() % (LIMIT_DOWN-3) + LIMIT_UP);
   }while( gameField->checkCoords(tempX,tempY) >0 );

   OrdinaryBrick* brickT = new OrdinaryBrick(tempX,tempY);
   ((Brick *)brickT)->print();

   bool xyflag = rand() % 2;
   for (int tempII=1 ; tempII<=(rand() % 10 + 1) ; tempII++){
   if ( ((tempX+(xyflag*tempII))>(LIMIT_RIGHT-2)) ||   ((tempY+(1-xyflag)*tempII)> (LIMIT_DOWN-5)) ) break;
   if (gameField->checkCoords(tempX+(xyflag*tempII),tempY+(1-xyflag)*tempII)>0) break;

   brickT = new OrdinaryBrick(tempX+(xyflag*tempII),tempY+(1-xyflag)*tempII);
   ((Brick *)brickT)->print();
   }
   };


   //create enemy tanks
   for (int tempI=1 ; tempI<=ENEMY_TANKS ; tempI++){
   bool tempFl;
   do{
   tempFl=false;
   tempX=(LIMIT_RIGHT - LIMIT_LEFT) /2  + (rand() % (LIMIT_RIGHT/2-3) + 1);
   tempY=(LIMIT_DOWN - LIMIT_UP) / 2 -7 + (rand() % (LIMIT_DOWN/2-3) + 1);
   for(int tempXx=tempX-2 ; tempXx<=tempX+3+2 ; tempXx++)
   for(int tempYy=tempY-2 ; tempYy<=tempY+3+2 ; tempYy++)
   if ( gameField->checkCoords(tempXx,tempYy) > 0 ) tempFl=true;
   }while( tempFl );

   EnemyTank* tankT = new EnemyTank(tempX,tempY);
   vectorOfEnemyTank.push_back(tankT);
   ((Tank *)tankT)->print();
   };


   //create our tank
   OurTank* ourTank = new OurTank( (LIMIT_RIGHT - LIMIT_LEFT) /2 +7, (LIMIT_DOWN - LIMIT_UP) -4);
   Tank* ourTankO=(Tank*)ourTank;
   ourTankO->print();

   gameTime=0;

   int bypassMove=0;

   while(true){ //gameloop

//move bullets
xy tempxy;

for (int tempI = 0; tempI <  vectorOfBullet.size(); tempI++){ //bullets move & check collision
tempxy=vectorOfBullet[tempI]->mover();
int tempisEnemy=vectorOfBullet[tempI]->isEnemy;

if ( tempxy.ret>0 ) //remove bullet if collision
{
vectorOfBullet[tempI]->del();
delete vectorOfBullet[tempI];
vectorOfBullet.erase(vectorOfBullet.begin() + tempI);
};

if ( (tempxy.ret==OBJECT_ENEMY_TANK)&&!(tempisEnemy) ) //kill enemy tank
{
ourTank->kills++;

Game* tempRef=gameField->getRefCoords(tempxy.x,tempxy.y);
Tank* tempRefT=(Tank *)tempRef;
EnemyTank* tempRefTT=(EnemyTank *)tempRef;
tempRefT->animateDie();
tempRefT->del();

delete tempRefTT;
//del tank from vectorOfEnemyTank
for (size_t tempIII = 0; tempIII < vectorOfEnemyTank.size(); tempIII++) {
if (vectorOfEnemyTank[tempIII] == tempRefTT) {
    vectorOfEnemyTank.erase(vectorOfEnemyTank.begin() + tempIII);
    break;
     }};

};//kill enemy tank

if ( (tempxy.ret==OBJECT_OUR_TANK)&& tempisEnemy ) //kill our tank
{
ourTank->lives--;
ourTankO->animateDie();
};//kill our tank

if ( tempxy.ret==OBJECT_ORD_BRICK ) //destroy brick
{
Game* tempRef=gameField->getRefCoords(tempxy.x,tempxy.y);
Brick* tempRefB=(Brick *)tempRef;
int tempHits=tempRefB->hit();

if (tempHits<=0)
{
tempRefB->del();
delete (OrdinaryBrick *)tempRef;
};
};//destroy brick

if ( tempxy.ret==OBJECT_GOLD_BRICK && !tempisEnemy) //our tank destroys gold
{
Game* tempRef=gameField->getRefCoords(tempxy.x,tempxy.y);
Brick* tempRefB=(Brick *)tempRef;
int tempHits=tempRefB->hit();

if (tempHits<=0)
{
tempRefB->del();
delete (GoldBrick *)tempRef;
gotoxy(1, 5); cout << "You win! Gold is yours!!!" << endl;
         cout << "\a\a\a" << endl;
         system("pause>nul");
         return 0;
};
};//our tank destroy gold

if ( tempxy.ret==OBJECT_GOLD_BRICK && tempisEnemy) //our tank destroys gold
{
Game* tempRef=gameField->getRefCoords(tempxy.x,tempxy.y);
Brick* tempRefB=(Brick *)tempRef;
int tempHits=tempRefB->hit();

if (tempHits<=0)
{
tempRefB->del();
delete (GoldBrick *)tempRef;
gotoxy(1, 5); cout << "You loose! Gold is in enemy's hands!!!" << endl;
         cout << "\a\a\a" << endl;
         system("pause>nul");
         return 0;
};
};//enemy tank destroy gold

};//bullets move & check collision

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
    Tank* enemtTankT=(Tank*)vectorOfEnemyTank[tempI];
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
            enemtTankT->direction=tempII;
}

enemtTankT->mover();

    if ( ((rand() % 10 + 1)>9) && (vectorOfBullet.size()<20) )
      {
          enemtTankT->fire();
       }

}

}//bypass move



gameTime++;
printGameTime();
printLivesKills(ourTank);




if (ourTank->lives<=0)
{
         gotoxy(1, 6); cout << "You loose!" << endl;
         cout << "\a\a\a" << endl;
         system("pause>nul");
         return 0;
}

if (ourTank->kills>=ENEMY_TANKS)
{
         gotoxy(1, 4); cout << "You win!" << endl;
         cout << "\a\a\a" << endl;
         system("pause>nul");
         return 0;
};


Sleep(SLEEP_TIME);
   };//end gameloop

};

