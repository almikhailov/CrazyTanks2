class Tank : Game{
public:
    Tank(int,int);
    int x;
    int y;
	void setDirection(int);
	int direction;
	void print();
	void printSpace();
	void del();
	void mover();
	bool isEnemy;
	void setInGamefield(int x,int y, bool isSet);
	void fire();
	void animateDie();
private:
   int numBullets;
   void printUp();
   void printDown();
   void printRight();
   void printLeft();
   };

void Tank::setInGamefield(int x,int y, bool isSet)
{
   int ttt;
    if (isEnemy) ttt=OBJECT_ENEMY_TANK; else ttt=OBJECT_OUR_TANK ;
    if (!isSet) ttt=0;
    for(int tempXx=x ; tempXx<=x+2 ; tempXx++)
     for(int tempYy=y ; tempYy<=y+2 ; tempYy++)
      gameField->setCoords(tempXx,tempYy,ttt, this);
};

Tank::Tank(int x, int y) {
   this->x = x;
   this->y = y;
   this->direction = MOVE_UP;
   }

void Tank::mover(){
   int oldX=this->x;
   int oldY=this->y;
   int newX=oldX; int newY=oldY;
   int oldDirection=this->direction;
   int newDirection=oldDirection;

   bool tempFl=false;


   if (newDirection==oldDirection)
   {//check if move
     if (newDirection == MOVE_LEFT)
       if (newX > LIMIT_LEFT + 1) newX--;

     if (newDirection == MOVE_RIGHT)
       if ((newX + 2) < LIMIT_RIGHT - 1) newX++;

     if (newDirection == MOVE_DOWN)
       if ((newY + 2) < LIMIT_DOWN - 1) newY++;

     if (newDirection == MOVE_UP)
       if (newY > LIMIT_UP + 1) newY--;


     if (newDirection == MOVE_LEFT){
        for(int tempYy=newY ; tempYy<=newY+2 ; tempYy++)
          if ( (gameField->checkCoords(newX,tempYy)) > 0 ) tempFl=true;
        if (tempFl) {
                newX=oldX;
                     }
     };

     if (newDirection == MOVE_RIGHT){
        for(int tempYy=newY ; tempYy<=newY+2 ; tempYy++)
          if ( gameField->checkCoords(newX+3,tempYy) > 0 ) tempFl=true;
        if (tempFl) {
                newX=oldX;
                   }
        }


     if (newDirection == MOVE_UP){
        for(int tempXx=newX ; tempXx<=newX+2 ; tempXx++)
          if ( gameField->checkCoords(tempXx,newY) > 0 ) tempFl=true;
        if (tempFl) {
            newY=oldY;
                   }
     };

     if (newDirection == MOVE_DOWN){
        for(int tempXx=newX ; tempXx<=newX+2 ; tempXx++)
          if ( gameField->checkCoords(tempXx,newY+3) > 0 ) tempFl=true;
        if (tempFl) {
            newY=oldY;
                    }
     };



   };//check if move

   if ( (newX!=oldX)||(newY!=oldY) )
       {//move
           printSpace();
           setInGamefield(oldX,oldY, false);
           this->x=newX; this->y=newY;
           setInGamefield(newX,newY, true);
           print();
       };//move

   }

void Tank::printSpace() {
   gotoxy(x, y); printf("   ");
   gotoxy(x, y + 1); printf("   ");
   gotoxy(x, y + 2); printf("   ");
}
void Tank::printUp() {
	gotoxy(x, y); printf(" %c", CHARACTER_ENEMY);
	gotoxy(x, y + 1);	printf("%c%c%c", CHARACTER_ENEMY, CHARACTER_ENEMY, CHARACTER_ENEMY);
	gotoxy(x, y + 2);	printf("%c %c", CHARACTER_ENEMY, CHARACTER_ENEMY);
}

void Tank::printDown() {
	gotoxy(x, y);	printf("%c %c", CHARACTER_ENEMY, CHARACTER_ENEMY);
	gotoxy(x, y + 1); printf("%c%c%c", CHARACTER_ENEMY, CHARACTER_ENEMY, CHARACTER_ENEMY);
	gotoxy(x, y + 2); printf(" %c ", CHARACTER_ENEMY);
}

void Tank::printRight() {
    gotoxy(x, y); printf("%c%c", CHARACTER_ENEMY, CHARACTER_ENEMY);
	gotoxy(x, y + 1); printf(" %c%c", CHARACTER_ENEMY, CHARACTER_ENEMY);
	gotoxy(x, y + 2);	printf("%c%c", CHARACTER_ENEMY, CHARACTER_ENEMY);
}

void Tank::printLeft() {
	gotoxy(x, y); printf(" %c%c", CHARACTER_ENEMY, CHARACTER_ENEMY);
	gotoxy(x, y + 1); printf("%c%c", CHARACTER_ENEMY, CHARACTER_ENEMY);
	gotoxy(x, y + 2);	printf(" %c%c", CHARACTER_ENEMY, CHARACTER_ENEMY);
}

void Tank::print() {

  switch(direction) {
      case MOVE_UP:
         printUp();
         break;
      case MOVE_DOWN:
         printDown();
         break;
      case MOVE_LEFT:
         printLeft();
         break;
      case MOVE_RIGHT:
         printRight();
         break;
   }

   gotoxy(x + 1, y + 1);
   if (isEnemy)
   {
   rlutil::setColor(LIGHTRED); rlutil::setBackgroundColor(LIGHTBLUE);
   printf("E");
   rlutil::setColor(LIGHTGRAY); rlutil::setBackgroundColor(BLACK);
   }
   else
   {
   rlutil::setColor(LIGHTRED); rlutil::setBackgroundColor(YELLOW);
   printf("H");
   rlutil::setColor(LIGHTGRAY); rlutil::setBackgroundColor(BLACK);
   };
}

void Tank::fire()
{
int tempX; int tempY;

    switch(direction) {
      case MOVE_UP:
         tempX=x+1;tempY=y-1;
         break;
      case MOVE_DOWN:
         tempX=x+1;tempY=y+3;
         break;
      case MOVE_LEFT:
         tempX=x-1;tempY=y+1;
         break;
      case MOVE_RIGHT:
         tempX=x+3;tempY=y+1;
         break;
   }


          if ( (gameField->checkCoords(tempX,tempY) <1) && (tempX>(LIMIT_LEFT+1)) && (tempX<(LIMIT_RIGHT-1)) && (tempY>(LIMIT_UP+1)) && (tempY<(LIMIT_DOWN-1)) ){
          Bullet* bulletT = new Bullet(tempX,tempY,direction,isEnemy);
          vectorOfBullet.push_back(bulletT);
          bulletT->print();
          }
}

void Tank::animateDie()
{
   printSpace();
   rlutil::setColor(WHITE);
   gotoxy(x, y);     printf("* *");
   gotoxy(x, y + 1); printf(" *");
   gotoxy(x, y + 2); printf("* *");
   Sleep(100);


   printSpace();
   rlutil::setColor(LIGHTGRAY);
   gotoxy(x, y);     printf(" * ");
   gotoxy(x, y + 1); printf("***");
   gotoxy(x, y + 2); printf(" * ");
   Sleep(100);

   printSpace();
   rlutil::setColor(WHITE);
   gotoxy(x, y);     printf("* *");
   gotoxy(x, y + 1); printf(" *");
   gotoxy(x, y + 2); printf("* *");
   Sleep(100);

   printSpace();
   rlutil::setColor(LIGHTGRAY);
   gotoxy(x, y);     printf(" * ");
   gotoxy(x, y + 1); printf("***");
   gotoxy(x, y + 2); printf(" * ");
   Sleep(100);

   printSpace();
   rlutil::setColor(WHITE);
   gotoxy(x, y);     printf(" * ");
   gotoxy(x, y + 1); printf("***");
   gotoxy(x, y + 2); printf(" * ");
   Sleep(100);

   printSpace();
   rlutil::setColor(LIGHTGRAY);
}

void Tank::del()
{
printSpace();
this->setInGamefield(x,y,false);
}

class EnemyTank : Tank{
public:
	EnemyTank(int x,int y)
	:Tank(x,y){
    this->isEnemy=true;
    setInGamefield(x,y, true);
    };
};

class OurTank : Tank{
public:
	OurTank(int x,int y)
	:Tank(x,y){
    this->isEnemy=false;
    kills=0;
    lives=MAX_LIVES;
    setInGamefield(x,y, true);
    };
    int kills;
    int lives;
};


