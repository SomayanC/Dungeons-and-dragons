/*
 * Dragon.cc
 *
 *  Created on: Apr 1, 2014
 *      Author: XinTong
 */

#include "Dragon.h"

Dragon::Dragon(Treasure *h) :
	Enemy(TDRAGON),
	hoard(h)
{
    setMaxHP(150);
    setAtk(20);
    setDef(20);
	setHP(getMaxHP());

}

Dragon::~Dragon()
{
}

void Dragon::setHoard(Treasure *h)
{
	hoard = h;
}

Treasure * Dragon::getHoard()
{
	return hoard;
}

Symbol Dragon::getSymbol() const
{
	return DRAGON;
}

bool Dragon::isHostile()
{
	//TODO
	return false;
}

bool Dragon::isRoamer()
{
	return false;
}

void Dragon::die(Character *killer)
{
	Enemy::die(killer);
	hoard->setGuard(NULL);
}

double Dragon::goldDrop() const
{
	return 0;
}

bool Dragon::isCloseToHoard(int row, int col) {
    if ((abs(row - (getHoard())->getRCoord()) <= 1) && (abs(col - (getHoard())->getCCoord()) <= 1)) {
        return true;
    }
    return false;
}
