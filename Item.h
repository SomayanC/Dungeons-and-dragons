/*
 * Item.h
 *
 *  Created on: Mar 25, 2014
 *      Author: XinTong
 */

#ifndef ITEM_H_
#define ITEM_H_

#include "MapObject.h"
#include "Player.h"
#include "Symbol.h"

enum ItemType
{
	//indicate in potion if neg or pos
	HEALTH = 0,
	ATTACK,
	DEFENSE,
	TREASURE
};

class Item : public MapObject
{
private:
	ItemType Itype;
	bool neg; //true if negative effect
	bool identified; //true if known potion (set to true after first use)

public:
	Item();
	virtual ~Item();

	//determines if the potion is identified
	bool isIdentified() const;

	//set item (potion only) to identified
	void setIdentified(bool val);

	//get symbol associated with item
	virtual Symbol getSymbol() const;

	//get map object type
	virtual ObjectType getObjType() const;

	//determine if object is usable (true only for potions)
	virtual bool isUsable() const;

	//determines if object has negative effects
	bool isNeg() const;

	//sets item to have negative effect
	void setNeg(bool effect);

	//get item type
	const ItemType getIType() const;
    
    //set item type
    void setIType(ItemType val);
    
	//Player calls this when using potion
	virtual void use(Player *p);

	//picks up item from floor
	void pickUp();

	std::string getPotType();
    void setPotType(std::string potion);
    
};

#endif /* ITEM_H_ */
