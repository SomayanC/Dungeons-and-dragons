#include "GameFloor.h"
using namespace std;

GameFloor::GameFloor(string fileName): Dungeon(NULL), length(0), width(0), gameDisplay(NULL)
{
    readMap(fileName);
}

void GameFloor::readMap(string fileName) {
    
    ifstream mapFile(fileName.c_str());
    string line;
    
    while (getline(mapFile, line)) {
        int index = 0;
        for (int i = 0; i < line.length(); i++) {
            index = i;
        }
        index++;
        length = (index > length) ? index : length;
        ++width;
    }
    
    
}

void GameFloor::generateMap(string fileName, GameDisplay *gd) {
    
    gameDisplay = gd;
    Dungeon = new Cell*[width];
    ifstream fin(fileName.c_str());
    string line;
    
    for (int r = 0; r < width; r++) {
        
        getline(fin, line);
        Dungeon[r] = new Cell[length];
        int whiteSpaces = 0;
        
        for (int c = 0; c < length; c++) {
            initCoordsAndType(r, c, (Symbol)line[c]);
            whiteSpaces++;
            if ('.' == line[c]) {
                emptyCells.push_back(&Dungeon[r][c]);
                
                if (((r > 2) && (r < 7)) && ((c > 2) && (c < 29))) {
                    chamberOne.push_back(&Dungeon[r][c]);
                }
                else if (((r > 14) && (r < 22)) && ((c > 3) && (c < 25))) {
                    chamberFour.push_back(&Dungeon[r][c]);
                }
                else if (((r > 9) && (r < 13)) && ((c > 37) && (c < 50))) {
                    chamberFive.push_back(&Dungeon[r][c]);
                }
                else if (((r > 15) && (r < 22)) && ((c > 36) && (c < 76))) {
                    if (!(((r > 15) && (r < 18)) && ((c > 36) && (c < 64)))) {
                        chamberThree.push_back(&Dungeon[r][c]);
                    }
                }
                else {
                    chamberTwo.push_back(&Dungeon[r][c]);
                }
            }
        }
        
        for (int i = whiteSpaces; i < length; i++) {
            initCoordsAndType(r, i, VACANT);
            gameDisplay->notify(r, i, VACANT);
        }
    }
}

//

void GameFloor::nextPosition(int &r, int &c, const string dir) {
    if (dir == "no") {
        r--;
    }
    else if (dir == "so") {
        r++;
    }
    else if (dir == "we") {
        c--;
    }
    else if (dir == "ea") {
        c++;
    }
    else if (dir == "nw") {
        r--;
        c--;
    }
    else if (dir == "ne") {
        r--;
        c++;
    }
    else if (dir == "sw") {
        r++;
        c--;
    }
    else if (dir == "se") {
        r++;
        c++;
    }
}

int GameFloor::getLength() const {
    return length;
}

int GameFloor::getWidth() const {
    return width;
}

Cell* GameFloor::getCell(int row, int col) {
    return &(Dungeon[row][col]);
}

//

void GameFloor::initCoordsAndType(const int row, const int col, const Symbol cellType) {
    (Dungeon[row][col]).initCoordsAndType(row, col, cellType);
    gameDisplay->notify(row, col, cellType);
}

Symbol GameFloor::getOriginalCellType(const int row, const int col) const {
    return (Dungeon[row][col]).getOriginalCellSymbol();
}

Symbol GameFloor::getCellType(const int row, const int col) const {
    return (Dungeon[row][col]).getCellSymbol();
}

void GameFloor::setCellType(const int row, const int col, const Symbol cellType) {
    (Dungeon[row][col]).setCellType(cellType);
    if (((Dungeon[row][col]).cellObject) != NULL) {
        ((Dungeon[row][col]).cellObject)->setPos(row, col, this);
    }
    if ((cellType == UNOCCUPIED) || (cellType == DOORWAY) || (cellType == PASSAGE) || (cellType == STAIRS)) {
        (Dungeon[row][col]).setOccupied(false);
    }
    else {
        (Dungeon[row][col]).setOccupied(true);
    }
    gameDisplay->notify(row, col, cellType);
}

void GameFloor::removeObject(const int row, const int col) {
    (Dungeon[row][col]).removeObject();
    gameDisplay->notify(row, col, (Dungeon[row][col]).getCellSymbol());
}

//

ostream &operator<<(ostream &out, const GameFloor &gf) {
    out << *gf.gameDisplay;
    return out;
}

GameFloor::~GameFloor() {
    for (int r = 0; r < width; r++) {
        delete [] Dungeon[r];
    }
    delete [] Dungeon;
    
    emptyCells.clear();
    
    length = 0;
    width = 0;
    
    gameDisplay->clearDisplay();
}
