#ifndef __cc3k__GameDispaly__
#define __cc3k__GameDispaly__

#include <iostream>
#include <cstdlib>
#include "Symbol.h"

class GameDisplay {
    
    char **textDisplay;
    const int rMax;
    const int cMax;
    
    GameDisplay(int l, int w);
    ~GameDisplay();
    
public:
    static GameDisplay *instance;
    static GameDisplay *getInstance(int l, int w);
    
    void notify(int row, int col, const Symbol cellType);
    friend std::ostream &operator<<(std::ostream &out, const GameDisplay &gd);
    
    static void clearDisplay();
};

#endif