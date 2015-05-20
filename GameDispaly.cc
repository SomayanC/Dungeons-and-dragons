#include "GameDispaly.h"
using namespace::std;

GameDisplay::GameDisplay(int l, int w): rMax(w), cMax(l) {
    
    textDisplay = new char*[rMax];
    
    for (int r = 0; r < rMax; r++) {
        textDisplay[r] = new char[cMax];
        for (int c = 0; c < cMax; c++) {
            textDisplay[r][c] = '.';
        }
    }
}

GameDisplay *GameDisplay::instance = NULL;

GameDisplay *GameDisplay::getInstance(int l, int w) {
    if (instance == NULL) {
        instance = new GameDisplay(l, w);
    }
    return instance;
}

//

void GameDisplay::notify(int row, int col, const Symbol cellType) {
    textDisplay[row][col] = (char)cellType;
}

ostream &operator<<(ostream &out, const GameDisplay &gd) {
    
    for (int r = 0; r < gd.rMax; r++) {
        for (int c = 0; c < (gd.cMax - 1); c++) {
            out << gd.textDisplay[r][c];
        }
        out << gd.textDisplay[r][gd.cMax - 1] << endl;
    }
    
    return out;
}

//

void GameDisplay::clearDisplay() {
    delete instance;
    instance = NULL;
}

GameDisplay::~GameDisplay() {
    
    for (int r = 0; r < rMax; r++) {
        delete [] textDisplay[r];
    }
    delete [] textDisplay;
}