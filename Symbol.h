/*
 * Symbol.h
 *
 *  Created on: Mar 25, 2014
 *      Author: XinTong
 */

#ifndef SYMBOL_H_
#define SYMBOL_H_

struct Coord {
    int rCoord;
    int cCoord;
};

enum Symbol
{
	//floorplan
	VACANT = ' ',
	UNOCCUPIED = '.',
	V_WALL = '|',
	H_WALL = '-',
	DOORWAY = '+', //possible feature: open/close (take on extra turn)
	PASSAGE = '#',
	STAIRS = '\\',

	//pc
	PLAYER = '@',

	//items
	POTION = 'P',
	GOLD = 'G',

	//enemies
	DRAGON = 'D',
	WEREWOLF = 'W',
	VAMPIRE = 'V',
	GOBLIN = 'N',
	MERCHANT = 'M',
	TROLL = 'T',
	PHOENIX = 'X'
};

#endif /* SYMBOL_H_ */
