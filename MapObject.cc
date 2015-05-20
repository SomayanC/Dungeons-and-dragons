#include "MapObject.h"
#include "GameFloor.h"

//default constructor
//	sets the floor to point at NULL, rCoord/cCoord to 0 and
//  null symbol
MapObject::MapObject() :
	floor(NULL), rCoord(0), cCoord(0), cell((Symbol)NULL)
{
}

//default destructor
//	does not delete the floor each object uses the same floor
MapObject::~MapObject()
{
}


//getFloor() returns a GameFloor pointer to the floor the object is on
GameFloor* MapObject::getFloor() const
{
	return floor;
}

//setFloor(GameFloor *gf) sets the current floor of the object to point at gf
void MapObject::setFloor(GameFloor *gf) {
    floor = gf;
}


//getRCoord() returns the row the object in on the map
int MapObject::getRCoord() const
{
	return rCoord;
}

//setRCoord(int val) sets the row of the object on the map to val
void MapObject::setRCoord(int val)
{
	rCoord = val;
}

//getCCoord() returns the column the object in is on the map
int MapObject::getCCoord() const
{
	return cCoord;
}

//setCCoord(int val) sets the column of the object on the map to val
void MapObject::setCCoord(int val)
{
	cCoord = val;
}


//setPos(r, c, nfloor) sets the coordinates and floor of the object
void MapObject::setPos(int r, int c, GameFloor* nfloor)
{
	if (!(floor == nfloor && rCoord == r && cCoord == c)) //check if parameters are same position
	{
		rCoord = r;
		cCoord = c;
		floor = nfloor;
	}
}

