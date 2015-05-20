#include <iostream>
using namespace std;

#include "MapObject.h"
#include "Cell.h"

Cell::Cell():
	rCoord(0), cCoord(0),
	originalCellSymbol((Symbol)0),
	cellSymbol((Symbol)0),
	occupied(false), blocked(true),
	cellObject(NULL)
{}

void Cell::initCoordsAndType(const int row, const int col, const Symbol cellType) {
    rCoord = row;
    cCoord = col;
    cellSymbol = cellType;
    originalCellSymbol = cellType;
    
    if ((cellType == UNOCCUPIED) || (cellType == DOORWAY) || (cellType == PASSAGE) || (cellType == STAIRS)) {
        blocked = false;
    }
}

void Cell::setCellType(const Symbol cellType) {
    cellSymbol = cellType;
}

bool Cell::isBlocked() {
    return blocked;
}

bool Cell::isStairs() {
    return (STAIRS == cellSymbol);
}

bool Cell::isDoor() {
    return (DOORWAY == cellSymbol);
}

bool Cell::isOccupiedByPlayer() {
    return (PLAYER == cellSymbol);
}

bool Cell::isOccupied() {
    return occupied;
}

void Cell::setOccupied(bool val)
{
	occupied = val;
}

int Cell::getRCoord() {
    return rCoord;
}

int Cell::getCCoord() {
    return cCoord;
}

Symbol Cell::getCellSymbol() {
    return cellSymbol;
}

Symbol Cell::getOriginalCellSymbol() {
    return originalCellSymbol;
}

void Cell::removeObject() {
    if (!(this->isStairs()) && (cellObject != NULL)) {
        delete cellObject;
    }
    
    cellSymbol = originalCellSymbol;
    cellObject = NULL;
    occupied = false;
}

Cell::~Cell() {
    if (cellObject != NULL) {
        removeObject();
    }
}
