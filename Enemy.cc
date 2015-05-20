#include "Enemy.h"
#include "Character.h"
#include "Symbol.h"
#include "MapObject.h"
#include "Player.h"
#include "Merchant.h"
#include "Dragon.h"
#include "GameFloor.h"

//constructor
Enemy::Enemy() :
	type((EnemyType)NULL)
{
}

//destructor
Enemy::~Enemy()
{
}

//returns type of enemy
EnemyType Enemy::getType() const
{
	return type;
}

//returns ENEMY_C as chartype
CharType Enemy::getCharType() const
{
	return ENEMY_C;
}

//converts symbol to enemy type
EnemyType Enemy::symbolToEnemy(Symbol s)
{
	EnemyType e;
	if (s == VAMPIRE)
		e = TVAMPIRE;
	else if (s == WEREWOLF)
		e = TWEREWOLF;
	else if (s == TROLL)
		e = TTROLL;
	else if (s == GOBLIN)
		e = TGOBLIN;
	else if (s == MERCHANT)
		e = TMERCHANT;
	else if (s == PHOENIX)
		e = TPHOENIX;
	else if (s == DRAGON)
		e = TDRAGON;
	return e;
}

//constructs enemy from type e
Enemy::Enemy(EnemyType e) :
		type(e)
{
	EnemyType newEnemy = getType();
	if (newEnemy ==  TVAMPIRE)
	{
		setMaxHP(50);
		setAtk(25);
		setDef(25);
	}
	else if (newEnemy == TWEREWOLF)
	{
		setMaxHP(120);
		setAtk(30);
		setDef(5);
	}
	else if (newEnemy == TTROLL)
	{
		setMaxHP(120);
		setAtk(25);
		setDef(15);
	}
	else if (newEnemy == TGOBLIN)
	{
		setMaxHP(70);
		setAtk(5);
		setDef(10);
	}
	else if (newEnemy == TPHOENIX)
	{
		setMaxHP(50);
		setAtk(35);
		setDef(20);
	}
	setHP(getMaxHP());
}

//converts enemy type to symbol
Symbol Enemy::getSymbol() const
{
	Symbol s;
	EnemyType e = getType();
	if (e ==  TVAMPIRE)
		s = VAMPIRE;
	else if (e == TWEREWOLF)
		s = WEREWOLF;
	else if (e == TTROLL)
		s = TROLL;
	else if (e == TGOBLIN)
		s = GOBLIN;
	else if (e == TMERCHANT)
		s = MERCHANT;
	else if (e == TPHOENIX)
		s = PHOENIX;
	else if (e == TDRAGON)
		s = DRAGON;

	return s;
}

//when general enemydies return 1 gold (shadowed in merchand and dragon)
double Enemy::goldDrop() const
{
	return 1;
}

//called when enemy dies, awards goldDrop to killer
void Enemy::die(Character *killer)
{
	if (killer->getCharType() == PLAYER_C) //check if killer is the player
	{
		((Player*)killer)->goldBonus(this->goldDrop()); //award gold to player
		(this->getFloor())->removeObject(getRCoord(), getCCoord()); //delete from map
	}
}

//all general enemies roam (shadowed in merchant, dragon)
bool Enemy::isRoamer()
{
	return true;
}

//all general enemies are hostile (shadowed in merhcant, dragon)
bool Enemy::isHostile()
{
	return true;
}

//determines if next location is movable
bool Enemy::isMovable(/*int x, int y, Floor *floor*/)
{
	return false;
}

//action
bool Enemy::action()
{
	bool act = false;
	int currR = getRCoord();
	int currC = getCCoord();
    
	GameFloor* currFloor = getFloor();

	for (int i = currR-1; i < currR+1; i++)
	{
		for (int j = currC-1; j <currC+1; j++)
		{
			if ((i < (currFloor->getLength())) && (j < (currFloor->getWidth())))
			{
				act = (currFloor->getCell(i, j))->isOccupiedByPlayer();
                std::cout << (char)((getFloor())->getCellType(i, j)) << std::endl;
			}
		}
	}
	return act;
}


/*Enemy * Enemy::create(EnemyType type)
{

	Enemy * newEnemy;
	if (type == TMERCHANT)
		newEnemy = new Merchant;
	else if (type == TDRAGON)
		newEnemy = new Dragon(NULL);
	else
		newEnemy =  new Enemy(type);
	return newEnemy;
}*/

void Enemy::create (EnemyType type)
{

	this->type = type;
	if (type ==  TVAMPIRE)
	{
		setMaxHP(50);
		setAtk(25);
		setDef(25);
	}
	else if (type == TWEREWOLF)
	{
		setMaxHP(120);
		setAtk(30);
		setDef(5);
	}
	else if (type == TTROLL)
	{
		setMaxHP(120);
		setAtk(25);
		setDef(15);
	}
	else if (type == TGOBLIN)
	{
		setMaxHP(70);
		setAtk(5);
		setDef(10);
	}
	else if (type == TPHOENIX)
	{
		setMaxHP(50);
		setAtk(35);
		setDef(20);
	}
	setHP(getMaxHP());
}


