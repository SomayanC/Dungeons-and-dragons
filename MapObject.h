#ifndef MAPOBJECT_H_
#define MAPOBJECT_H_

#include "Symbol.h"

class GameFloor;

//enumerates all object types
enum ObjectType
{
	CTYPE, //charcter type
	ITEM, //item object
};

//mapobject class is any object which will be placed on the game floor
class MapObject
{
	GameFloor *floor;
	int rCoord;
	int cCoord;
	Symbol cell;
    
public:
	MapObject();
	virtual ~MapObject();

	//returns the symbol associated with the current map object
	virtual Symbol getSymbol() const = 0;
	//returns the object type associated with the current map object
	virtual ObjectType getObjType() const = 0;

	//returns current floor
	GameFloor* getFloor() const;
	//sets the floor of the map object to gf
    void setFloor(GameFloor *gf);

    //returns the rCoord of the current game object
	int getRCoord() const;
	//sets the rCoord of the current game object
	void setRCoord(int val);
	//returns the cCoord of the current game object
	int getCCoord() const;
	//sets the cCoord of the current game object
	void setCCoord(int val);

	//sets the position of the current map object on a floor
	virtual void setPos(int r, int c, GameFloor* nfloor);
};

#endif /* MAPOBJECT_H_ */

//(floor->getCell(row, col))->getCellSymbol
//(floor->getCell(row, col))->getCellObject
