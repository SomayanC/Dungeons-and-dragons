#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "MapObject.h"
#include "GameFloor.h"

enum CharType
{
	PLAYER_C,
	ENEMY_C
};

//abstract class
class Character : public MapObject
{
private:
	int hitpoints, maxHitpoints; //current hp, and total hp
	int attack;
	int defense;
    
public:
	Character();
	virtual ~Character();

    int isTurn; //true when it is enemies turn to attack
    
	//getMapObject() returns the object type (CTYPE, ITEM)
	virtual ObjectType getObjType() const;
	//getCharType() returns the type of Character (PLAYER_C, ENEMY_C)
	virtual CharType getCharType() const = 0;
	//void die(Character *killer) rewards the killer with gold
	virtual void die(Character *killer) = 0;
	//int atk(Character *other) deals with all attack effects (combat)
	virtual int atk(Character *enemy);

	//bool isDead() returns true when character is dead
	virtual bool isDead();

	//setMaxHP(val) sets the maxHP to val
	void setMaxHP(int val);
	//getMaxHP() returns the maxHP
	int getMaxHP() const;
	//setHP(val) sets the current HP to val
	void setHP(int val);
	//getHP() returns the temporary HP (current)
	int getHP() const;
	//setAtk(val) sets the attack to val
	void setAtk(int val);
	//getAtk() returns the attack
	int getAtk() const;
	//setDef(val) sets the defense to val
	void setDef(int val);
	//getDef() returns the defense
	int getDef() const;

	//determines if characters turn (true)
	virtual bool action() = 0;

	//moveTo(r, c) moves the object to coordinates (r, c) on the game floor
	void moveTo(int r, int c);

};

#endif /* CHARACTER_H_ */
