/*
 * Treasure.cc
 *
 *  Created on: Apr 1, 2014
 *      Author: XinTong
 */

#include "Treasure.h"
#include "Dragon.h"

Treasure::Treasure(double goldVal) :
    guard(NULL), goldVal(goldVal)
{
    setIType(TREASURE);
}

Treasure::~Treasure()
{}


Symbol Treasure::getSymbol() const
{
	return GOLD;
}

double Treasure::getGoldVal()
{
	return goldVal;
}

void Treasure::setGuard(Character *g)
{
	guard = g;
}

Character * Treasure::getGuard()
{
	return guard;
}

bool Treasure::isUse()
{
	bool r = false;
	if (getGuard() == NULL)
		r = true;
	return r;
}

void Treasure::use(Player *p)
{
	if (isUse()) {
        double cheque = getGoldVal();
        if (p->getRacestr() == "DWARF") {
            cheque*=2;
        }
        else if (p->getRacestr() == "ORC") {
            cheque/=2;
        }
        p->goldBonus(cheque);
        pickUp();
    }
}


