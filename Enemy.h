#ifndef ENEMY_H_
#define ENEMY_H_

#include "Character.h"

//enumerate enemy types
enum EnemyType
{
	TVAMPIRE = 0,
	TWEREWOLF,
	TTROLL,
	TGOBLIN,
	TMERCHANT,
	TPHOENIX,
	TDRAGON
};

//Enemy is a Character object
class Enemy : public Character
{
private:
	EnemyType type;

public:
	Enemy();
	virtual ~Enemy();

	//construct enemy from type
	Enemy(EnemyType e);

	//get random enemy (random generator)
	//generate game symbol
	static EnemyType symbolToEnemy(Symbol s);
	//create enemy from type (associated stats set)
	void create(EnemyType type);

	//returns type of current character (ENEMY_C)
	virtual CharType getCharType() const;

	//returns EnemyType
	EnemyType getType() const;

	//get symbol associated with Enemy
	virtual Symbol getSymbol() const;

	//determines if enemy roams
	virtual bool isRoamer();

	//determines whether if enemy is hostile
	virtual bool isHostile();

	//dies, gold is awarded to killer if killer is a player
	virtual void die(Character *killer);

	//determines if Enemy's turn
	virtual bool action();

	//moving (see character)
	virtual bool isMovable();

	//get automatic gold award when die (awarded to pc)
	virtual double goldDrop() const;

};

#endif /* ENEMY_H_ */
