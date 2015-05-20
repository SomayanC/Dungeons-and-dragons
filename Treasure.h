/*
 * Treasure.h
 *
 *  Created on: Apr 1, 2014
 *      Author: XinTong
 */

#ifndef TREASURE_H_
#define TREASURE_H_

#include "Item.h"

enum TreasureType
{
	NORMAL = 0,
	HOARD_S,
	HOARD_M,
	HOARD_D
};

class Treasure : public Item
{
private:
	Character *guard;
	double goldVal;
public:
	Treasure(double goldVal);
	virtual ~Treasure();

	virtual Symbol getSymbol() const;
	virtual double getGoldVal();
	void setGuard(Character *g);
	Character * getGuard();

	virtual void use(Player *p);
	bool isUse();

};

#endif /* TREASURE_H_ */
