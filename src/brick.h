class Brick : Game{
public:
	Brick(int , int);
	int x;
	int y;
	void setInGamefield(int,int,bool);
	void print();
	void printSpace();
	int hit();
	void del();
    bool isGold;
    int hits;
	};

Brick::Brick(int x, int y) {
    this->x=x;
    this->y=y;
    this->hits=WALL_HITS;
   }

void Brick::setInGamefield(int x,int y, bool isSet)
{
    int ttt;
    if (isGold) ttt=OBJECT_GOLD_BRICK; else ttt=OBJECT_ORD_BRICK ;
    if (!isSet) ttt=0;
    gameField->setCoords(x,y,ttt, this);
    };

void Brick::print() {
   gotoxy(this->x, this->y);
   if (isGold) printf("%c", CHAR_GOLD); else printf("%c", CHAR_WALL);
}

void Brick::printSpace() {
   gotoxy(x, y); printf(" ");
   }

void Brick::del(){
printSpace();
setInGamefield(x,y,false);
}

int Brick::hit(){
hits--;
return(hits);
}

class OrdinaryBrick : Brick{
public:
	OrdinaryBrick(int x , int y)
	:Brick(x,y){
	    isGold=false;
	    this->hits=WALL_HITS;
	    setInGamefield(x,y,true);
	};
    };

class GoldBrick : Brick{
public:
	GoldBrick(int x , int y)
	:Brick(x,y){
	    isGold=true;
	    this->hits=1;
	    setInGamefield(x,y,true);
	    };
    };
