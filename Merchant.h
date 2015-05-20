/*
 * Merchant.h
 *
 *  Created on: Apr 1, 2014
 *      Author: XinTong
 */

#ifndef MERCHANT_H_
#define MERCHANT_H_

#include "Enemy.h"
#include "Item.h"

class Merchant : public Enemy
{
private:
	//Item *stock[4];
public:
	static bool hostile;

	Merchant();
	virtual ~Merchant();

	Symbol getSymbol() const;
	bool isHostile();
	void die(Character *killer);
	double goldDrop() const;

};

#endif /* MERCHANT_H_ */
