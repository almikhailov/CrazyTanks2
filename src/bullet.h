class Bullet : Game{
public:
    Bullet(int,int,int,bool);
    int x;
    int y;
	int direction;
	void print();
	void printSpace();
	void del();
	xy mover();
	bool isEnemy;
	void setInGamefield(int x,int y, bool isSet);
};

void Bullet::setInGamefield(int x,int y, bool isSet)
{
 int ttt;
    if (isEnemy) ttt=OBJECT_ENEMY_BULLET; else ttt=OBJECT_OUR_BULLET ;
    if (!isSet) ttt=0;
    gameField->setCoords(x,y,ttt, this);
    };

Bullet::Bullet(int x, int y, int direction, bool isEnemy) {
   setInGamefield(x,y, true);
   this->x = x;
   this->y = y;
   this->direction = direction;
   this->isEnemy=isEnemy;
}

xy Bullet::mover(){
   int oldX=this->x;
   int oldY=this->y;
   int newX=oldX; int newY=oldY;
   int newDirection=this->direction;
   int tempRetT=0;int tempRet=0;
   xy xytemp;

     if (newDirection == MOVE_LEFT)
       if (newX > LIMIT_LEFT + 2) newX--; else tempRet=OBJECT_BORDER;

     if (newDirection == MOVE_RIGHT)
       if ((newX + 2) < LIMIT_RIGHT - 1) newX++;  else tempRet=OBJECT_BORDER;

     if (newDirection == MOVE_DOWN)
       if ((newY + 2) < LIMIT_DOWN - 1) newY++;  else tempRet=OBJECT_BORDER;

     if (newDirection == MOVE_UP)
       if (newY > LIMIT_UP + 1) newY--;  else tempRet=OBJECT_BORDER;

xytemp.x=newX;
xytemp.y=newY;

       if ( (tempRetT=gameField->checkCoords(newX,newY)) > 0 ) {
                newX=oldX; newY=oldY;
                if ( (tempRetT>tempRet)  ) //&& !( (tempRetT==OBJECT_ENEMY_TANK) &&(isEnemy==true) ) && !( (tempRetT==OBJECT_OUR_TANK) &&(isEnemy==false) )
                    tempRet=tempRetT;
                   }

xytemp.ret=tempRet;

   if ( (newX!=oldX)||(newY!=oldY) )
       {//move
           printSpace();
           setInGamefield(oldX,oldY, false);
           x=newX; y=newY;
           setInGamefield(newX,newY, true);
           print();
       };//move


return(xytemp);
}

void Bullet::printSpace() {
   gotoxy(x, y); printf(" ");
   }

void Bullet::print() {
gotoxy(x, y); rlutil::setColor(LIGHTRED); printf("%c", CHARACTER_BULLET); rlutil::setColor(LIGHTGRAY);
}

void Bullet::del()
{
printSpace();
setInGamefield(x,y, false);
}
