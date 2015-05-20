/*
 * Merchant.cc
 *
 *  Created on: Apr 1, 2014
 *      Author: XinTong
 */


#include "Merchant.h"
#include <iostream>
#include "Random.h"
#include "Treasure.h"

bool Merchant::hostile = false;

Merchant::Merchant() :
	Enemy(TMERCHANT)
{
    setMaxHP(30);
    setAtk(70);
    setDef(5);
	setHP(getMaxHP());
    /*int n = randGen(1, 4);
	for (int i = 0; i < n; i++)
	{
		stock[i] = new Item;
	}*/
}

Merchant::~Merchant()
{
	/*if (stock)
	{
		int i = 0;
		while (stock[i])
		{
			delete stock[i];
			i++;
		}
	}*/
}

Symbol Merchant::getSymbol() const
{
	return MERCHANT;
}

bool Merchant::isHostile()
{
 	return hostile;
}

void Merchant::die(Character *killer)
{
	Enemy::die(killer);
    hostile = true;
	GameFloor* thisFloor = this->getFloor();
	Treasure * dropHoard = new Treasure(4);
	Cell* c = thisFloor->getCell(this->getRCoord(), this->getCCoord());

	c->cellObject = dropHoard;
	thisFloor->setCellType(this->getRCoord(), this->getCCoord(), GOLD);
}

double Merchant::goldDrop() const
{
	return 0;
}
