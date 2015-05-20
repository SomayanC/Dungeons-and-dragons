#ifndef __cc3k__Cell__
#define __cc3k__Cell__

//#include <iostream>
#include "Symbol.h"

class MapObject;

class Cell {
    int rCoord, cCoord;
    Symbol originalCellSymbol;
    Symbol cellSymbol;
    bool occupied;
    bool blocked;
    
public:
    MapObject *cellObject;
    
    Cell();
    ~Cell();
    
    void initCoordsAndType(const int row, const int col, const Symbol cellType);
    void setCellType(const Symbol cellType);
    
    bool isOccupied();
    bool isOccupiedByPlayer();
    void setOccupied(bool val);
    bool isBlocked();
    bool isStairs();
    bool isDoor();
    int getRCoord();
    int getCCoord();
    Symbol getCellSymbol();
    Symbol getOriginalCellSymbol();
    
    void removeObject();
};

#endif
