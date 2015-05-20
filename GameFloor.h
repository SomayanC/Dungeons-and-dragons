#ifndef __cc3k__GameFloor__
#define __cc3k__GameFloor__

#include <iostream>
#include <fstream>
#include <vector>
#include "Symbol.h"
#include "Cell.h"
#include "MapObject.h"
#include "GameDispaly.h"

//"c" or "cCoord" to denotes the x-coordinate of something's location on the GameFloor
//"r" or "rCoord" to denotes the y-coordinate of something's location on the GameFloor

class GameFloor {
    
    Cell **Dungeon;
    int length, width;
    GameDisplay *gameDisplay;
    
    //(2, 2) to (2, 29) to (7, 29) to (7, 2) to (2, 2)

    //(2, 38) to (2, 62) to (4, 62) to (4, 70) to (5, 70) to (5, 73) to (6, 73) to (6, 76) to (13, 76) to (13, 60) to (7, 60) to (7, 38) to (2, 38)

    //(18, 36) to (18, 64), (15, 64) to (15, 76), (22, 76) to (22, 36), (18, 36)

    //(14, 3) to (14, 25), (22, 25) to (22, 3) to (14, 3)
    
    //(9, 37) to (9, 50) to (13, 50) to (13, 37) to (9, 37)
    
public:
    //this is the vector of cells that are UNOCCUPIED
    std::vector<Cell*> emptyCells;
    
    std::vector<Cell*> chamberOne;
    std::vector<Cell*> chamberTwo;
    std::vector<Cell*> chamberThree;
    std::vector<Cell*> chamberFour;
    std::vector<Cell*> chamberFive;
    
    GameFloor(std::string fileName);
    ~GameFloor();
    
    void readMap(std::string fileName);
    void generateMap(std::string fileName, GameDisplay *gameDisplay);
    
    //These three methods affect the Cell at the given row and col coordinates and the display.
    //Calling these methods will suffice to change the Cell and display
    
    //Initializes the cell with row for rCoord, col for cCoord and cellType with cellSymbol
    void initCoordsAndType(const int row, const int col, const Symbol cellType);
    
    //Just changes the cellSymbol to cellType for the Cell at (col, row)
    Symbol getOriginalCellType(const int row, const int col) const;
    Symbol getCellType(const int row, const int col) const;
    void setCellType(const int row, const int col, const Symbol cellType);
    
    //Commpletely removes an object from the GameFloor, the GameDisplay, the individual cell and even deletes the object itself
    void removeObject(const int row, const int col);
    
    
    //r is the current rCoord of the MapObject, c is the current cCoord of the MapObject and dir is the direction we're moving or attacking or whatever.
    //Sets r and c to the next rCoord and cCoord of the next position
    void nextPosition(int &r, int &c, const std::string dir);
    Cell* getCell(int row, int col);

    int getLength() const;
    int getWidth() const;
    
    friend std::ostream &operator<<(std::ostream &out, const GameFloor &gf);
};

#endif
