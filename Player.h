#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include "Character.h"

class Item;
struct Coord;

//enumerates character races for race selection
enum Race
{
	HUMAN = 0, //default
	DWARF,
	ELF,
	ORC
};

//Player is a Character object
class Player : public Character
{
private:
	static double goldCount; //gold static variable
    
	Race r;
	int atkEffect;
	int defEffect;
	double gold;

public:
	Player();
	virtual ~Player();

	//highscore get/set gold highscore
	static void setGoldCount(double val);
	static double getGoldCount();

	//setRace sets the race of the Character to newRace and all associated fields
	void setRace(char newRace);
	//returns the character's race race
	Race getRace();
	//converts the race of the character to a string
	std::string getRacestr();

	//returns the character type (PLAYER_C)
	virtual CharType getCharType() const;

	//returns symbol PLAYER
	virtual Symbol getSymbol() const;
	//returns objecttype(CTYPE)
	virtual ObjectType getObjType() const;

	//sets attack defense (potion effects)
	void setAtkEffect(int val); //+/- val from total if not <0
	int getAtkEffect();
	void setDefEffect(int val);
	int getDefEffect();

	//returns attack with effects of potions
	int getAtk();

	//returns defense with potion effects
	int getDef();

	//get/set gold amount
	double getGold();
	void setGold(double val); //+/- val from total if not <0

	//race gold effects awards gold
	void goldBonus(double val);

	//hp reaches 0
	void die(Character *killer);

	//determines if player's turn
	bool action();


};

#endif /* PLAYER_H_ */
