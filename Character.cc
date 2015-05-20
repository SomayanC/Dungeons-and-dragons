#include "Character.h"
#include <cmath>

//constructor
Character::Character() :
	hitpoints(0), maxHitpoints(0), attack(0), defense(0), isTurn(0)
{
}

//destructor
Character::~Character()
{
}

//public methods

//getObjType returns the map object type, character in this case
ObjectType Character::getObjType() const
{
	return CTYPE;
}

//getCharType pure virtual
//die pure virtual

//attack algorithm
int Character::atk(Character *enemy)
{
    if (this->getCharType() == ENEMY_C) {
        if ((rand()%2) == 0) {
            return 0;
        }
    }
    //algorithm for damage
	int damage = (int)ceil(100.0 / (100.0 + enemy->getDef()) * this->getAtk());
	//subtract damage from enemy hp
	enemy->setHP(enemy->getHP() - damage);
	if (enemy->isDead()) //when enemy health reaches 0 call die method
		enemy->die(this);
	return damage;
}

//isMovable pure virtual

//isDead returns true when hp reaches 0
bool Character::isDead()
{
	bool dead = false;
	if (hitpoints <= 0) //check for hp <= 0
		dead = true;
	return dead;
}

//setMaxHP sets the maximum hp of the character (constant) to val
void Character::setMaxHP(int val)
{
	maxHitpoints = val;
}

//getMaxHP returns the maximum hp of the character
int Character::getMaxHP() const
{
	return maxHitpoints;
}

//setHP sets the temporary hp of the character
//      hp is set to 0 if val is negative
//      hp is set to maxHP if val is greather than maxHP
//      otherwise hp is set to val
void Character::setHP(int val)
{
	int hp;
	if (val < 0) //check for negative val
		hp = 0;
	else if (val > maxHitpoints) //check for val larger than maxHP
		hp = maxHitpoints;
	else //otherwise set val
		hp = val;
    
    hitpoints = hp;
}

//getHP returns the current hp of the character
int Character::getHP() const
{
	return hitpoints;
}

//setAtk sets the current Atk of the character to val
void Character::setAtk(int val)
{
	attack = val;
}

//getAtk returns the current Atk of the character
int Character::getAtk() const
{
	return attack;
}

//setDef sets the current Def of the character to val
void Character::setDef(int val)
{
	defense = val;
}

//getDef returns the current Def of the character
int Character::getDef() const
{
	return defense;
}

//moveTo moves the character to the coordinates (r, c) ont he game floor
void Character::moveTo(int r, int c)
{
    //set old position to unoccupied before moving the Player
    GameFloor *floor = getFloor(); //get current floor
    (floor->getCell(getRCoord(), getCCoord()))->cellObject = NULL; //clear obj at current position
    floor->setCellType(getRCoord(), getCCoord(), (floor->getOriginalCellType(getRCoord(), getCCoord())));
    setRCoord(r);
    setCCoord(c);
    floor->setCellType(r, c, getSymbol()); //set obj at new location
}

