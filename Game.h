#ifndef __cc3k__Game__
#define __cc3k__Game__

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include "GameFloor.h"
#include "GameDispaly.h"
#include "Player.h"
#include "Enemy.h"
#include "Merchant.h"
#include "Dragon.h"
#include "Symbol.h"

class Game {
    
    const int maxEnemies;
    int numOfNonDragonEnemies;
    const int maxPotions;
    const int maxGold;
    const int maxLevels;
    
    int turnTracker;
    std::string actionScript;
    
    Player *player;
    
    int score;
    int currentLevel;
    bool gameStarted;
    
    std::string fileName;
    
    static Game *instance;
    
    GameFloor* gameFloor;
    GameDisplay* gameDisplay;
    
    bool directionInput(std::string command);
    bool raceInput(std::string command);
    bool isEnemy(const Symbol race);
    std::string askForDirection();
    std::string getRandomDirection(const int currentRow, const int currentCol, Dragon *d);
    bool incorrectCommand();
    
    void placeMapObjectsRandomlyInTextDisplay(char playerRace);
    Cell* selectRandomCell(Dragon *d);
    std::string symbolToString(const Symbol s);
    std::string directionToString(const std::string command);
    std::string objectsAroundPosition(const int r, const int c);
    bool isPlayerClose(int r, int c);
    bool playerIsCloseToDragonPile();
    std::string itos(int i);
    
    void displayScoreBoard();
    
    Game();
    ~Game();
    static void cleanUp();
    void reset();
    bool suddenDeath; // = false;
    
public:
    static Game *getInstance();
    bool passInput(const std::string command);
    
    void newGame(std::string fileName, char playerRace);
    void nextLevel();
    void restartGame();
    void endGame();
};

#endif
