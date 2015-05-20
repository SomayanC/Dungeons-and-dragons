/*
 * Item.cc
 *
 *  Created on: Mar 25, 2014
 *      Author: XinTong
 */

#include "Item.h"

Item::Item() :
	Itype((ItemType)0), neg(false), identified(false)
{
}

Item::~Item()
{
}

bool Item::isIdentified() const
{
	return identified;
}

void Item::setIdentified(bool val)
{
	identified = val;
}

const ItemType Item::getIType() const
{
	return Itype;
}

void Item::setIType(ItemType val)
{
    Itype = val;
}

Symbol Item::getSymbol() const
{
	return POTION;
}

ObjectType Item::getObjType() const
{
	return ITEM;
}

bool Item::isUsable() const
{
	return true;
}

bool Item::isNeg() const
{
	return neg;
}

void Item::setNeg(bool effect)
{
	neg = effect;
}

void Item::pickUp()
{
    getFloor()->removeObject(getRCoord(), getCCoord());
}

std::string Item::getPotType()
{
	ItemType i = getIType();
	std::string s;
	if (i == HEALTH)
	{
		if (isNeg())
			s = "NH";
		else if (!isNeg())
			s = "PH";
	}
	else if (i == ATTACK)
	{
		if (isNeg())
			s = "NA";
		else if (!isNeg())
			s = "PA";
	}
	else if (i == DEFENSE)
	{
		if (isNeg())
			s = "ND";
		else if (!isNeg())
			s = "PD";
	}
	return s;
}

void Item::setPotType(std::string potion) {
    if (potion == "NH") {
        setIType(HEALTH);
        setNeg(true);
    }
    else if (potion == "PH") {
        setIType(HEALTH);
        setNeg(false);
    }
    else if (potion == "NA") {
        setIType(ATTACK);
        setNeg(true);
    }
    else if (potion == "PA") {
        setIType(ATTACK);
        setNeg(false);
    }
    else if (potion == "ND") {
        setIType(DEFENSE);
        setNeg(true);
    }
    else if (potion == "PD") {
        setIType(DEFENSE);
        setNeg(false);
    }
}

void Item::use(Player *p)
{
    int elfEffect = 1;
    if (p->getRacestr() == "ELF") {
        elfEffect = -1;
    }
    
	ItemType i = getIType();
		if (i == HEALTH)
		{
			int hp = p->getHP();
			if (isNeg())
				p->setHP((hp - (elfEffect*10)) * 2);
			else if (!isNeg())
				p->setHP(hp + 10);
		}
		else if (i == ATTACK)
		{
			int atk = p->getAtkEffect();
			if (isNeg())
				p->setAtkEffect(atk - (elfEffect*5));
			else if (!isNeg())
				p->setAtkEffect(atk + 5);
		}
		else if (i == DEFENSE)
		{
			int def = p->getDefEffect();
			if (isNeg())
				p->setDefEffect(def - (elfEffect*5));
			else if (!isNeg())
				p->setDefEffect(def + 5);
		}
		setIdentified(true);
		pickUp();
}
