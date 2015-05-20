#include "Player.h"
#include "Symbol.h"
#include "MapObject.h"
#include "GameFloor.h"

//static variable goldCount starts at 0
double Player::goldCount = 0;

//constructor sets default human race and stats
Player::Player() :
	r((Race)HUMAN), atkEffect(0), defEffect(0), gold(0)
{
	setMaxHP(140);
	setAtk(20);
	setDef(20);
    setHP(140);
}

//default destructor
Player::~Player()
{
}

//highscore
//set total goldcount to val
void Player::setGoldCount(double val)
{
	goldCount = val;
}

//getGoldCount returns the highscore goldcount
double Player::getGoldCount()
{
	return goldCount;
}

//sets the race of the Player object to newRace along with all associated stats
void Player::setRace(char newRace)
{
	if (newRace == 'h')
	{
		setMaxHP(140);
		setAtk(20);
		setDef(20);
        r = HUMAN;
	}
	else if (newRace == 'd')
	{
		setMaxHP(100);
		setAtk(20);
		setDef(30);
        r = DWARF;
	}
	else if (newRace == 'e')
	{
		setMaxHP(140);
		setAtk(30);
		setDef(10);
        r = ELF;
	}
	else if (newRace == 'o')
	{
		setMaxHP(180);
		setAtk(30);
		setDef(25);
        r = ORC;
	}
	setHP(getMaxHP());
}

//returns player race
Race Player::getRace()
{
	return this->r;
}

//returns race string of player race
std::string Player::getRacestr()
{
	Race nrace = getRace();
	std::string race;
	if (nrace == HUMAN)
		race = "HUMAN";
	else if (nrace == DWARF)
		race = "DWARF";
	else if (nrace == ELF)
		race = "ELF";
	else if (nrace == ORC)
		race = "ORC";
	return race;
}

//returns the gold amount the player is holding
double Player::getGold()
{
	return gold;
}

//sets the gold amount the player is holding
void Player::setGold(double val)
{
	gold = val;
}

//awards gold to a character depending on race
void Player::goldBonus(double val)
{
	gold += val;
}


//map usage
//returns the Chartype of the the player
CharType Player::getCharType() const
{
	return PLAYER_C;
}

//returns the symbol associated with the player character
Symbol Player::getSymbol() const
{
	return PLAYER;
}

//returns the objectype of the player
ObjectType Player::getObjType() const
{
	return CTYPE;
}

//atk/def (potion effects)
//set the temporary atk effect to val
void Player::setAtkEffect(int val)
{
	atkEffect = val;
}

//returns the temporary atk effect
int Player::getAtkEffect()
{
	return atkEffect;
}

//set the temporary def effect to val
void Player::setDefEffect(int val)
{
	defEffect = val;
}

//returns the def effect
int Player::getDefEffect()
{
	return defEffect;
}

//returns the total attack statistic of the player
int Player::getAtk()
{
	return ((Character::getAtk() + getAtkEffect()) >= 0) ? (Character::getAtk() + getAtkEffect()) : 0;
}

//returns the total defense statistic of the player
int Player::getDef()
{
	return ((Character::getDef() + getDefEffect()) >= 0) ? (Character::getDef() + getDefEffect()) : 0;
}

//does nothing (gameover)
void Player::die(Character *killer)
{
    (this->getFloor())->removeObject(getRCoord(), getCCoord()); //delete from map
}

//not used
bool Player::action()
{
	return false;
}


