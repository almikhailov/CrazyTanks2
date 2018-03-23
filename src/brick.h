class Brick : Game{
public:
	Brick(int , int);
	int x;
	int y;
	void print();
    bool isGold;
	};

Brick::Brick(int x, int y) {
    int ttt;
    if (isGold) ttt=OBJECT_GOLD_BRICK; else ttt=OBJECT_ORD_BRICK ;
gameField->setCoords(x,y,ttt, this);
this->x=x;
this->y=y;
   }

void Brick::print() {
   gotoxy(this->x, this->y); printf("%c", CHAR_WALL);
}


class OrdinaryBrick : Brick{
public:
	OrdinaryBrick(int x , int y)
	:Brick(x,y){
	    isGold=false;
	};
    };

