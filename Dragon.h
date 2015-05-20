#ifndef DRAGON_H_
#define DRAGON_H_

#include "Enemy.h"
#include "Treasure.h"
#include <math.h>

//dragon is a subclass of enemy
class Dragon : public Enemy
{
private:
	Treasure *hoard; //all dragons have a hoard

public:
	Dragon(Treasure *h); //construct dragon when hoard created
	virtual ~Dragon();

	//sets the hoard of the dragon
	void setHoard(Treasure *h);
	//returns a pointer to the dragon hoard
	Treasure * getHoard();
    
	//checks if dragon is close to hoard
    bool isCloseToHoard(int row, int col);

    //get Dragon symbol
	virtual Symbol getSymbol() const;

	//true when player is next to hoard
	virtual bool isHostile();
	//false
	virtual bool isRoamer();

	//sets hoard to unguarded when dragon dies, calls Enemy::die
	virtual void die(Character *killer);

	//returns 0, dragon doesn't drop gold
	virtual double goldDrop() const;
};

#endif /* DRAGON_H_ */
