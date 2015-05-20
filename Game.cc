#include <time.h>
#include "Game.h"
using namespace std;

Game::Game():
	maxEnemies(20), numOfNonDragonEnemies(20), maxPotions(10), maxGold(10), maxLevels(5),
	player(NULL)
{
    score = 0;
    turnTracker = 0;
    currentLevel = 1;
    gameFloor = NULL;
    gameDisplay = NULL;
    gameStarted = false;
    suddenDeath = false;
    actionScript = "";
    fileName = "";
}

Game *Game::instance = NULL;

Game *Game::getInstance() {
    if (instance == NULL) {
        instance = new Game();
        atexit(cleanUp);
    }
    return instance;
}

// Handle Input

bool Game::passInput(const string command) {
    
    if (!gameStarted) { // If game hasn't started yet
        
        if (command == "q") {
            delete this;
            return true;
        }
        else if (raceInput(command)) { // If Player's race is correctly inputted, next get the file name and ensure it's legit
            string fileName;
            bool fileExists = false;
            
            while (!fileExists && (cin >> fileName)) {
                ifstream mapFile(fileName.c_str());
                if (mapFile) {
                    fileExists = true;
                    this->fileName = fileName;
                    newGame(fileName, command[0]);
                    return false;
                }
            }
            
            if (!fileExists) {
                delete this;
                return true;
            }
        }
        else { // wrong command
            return incorrectCommand();
        }
    }
    else {
        if (directionInput(command)) { // move Player
            
            //these r and c values will represent the row and col values of the next position of the Player in the GameFloor
            
            int r = player->getRCoord();
            int c = player->getCCoord();
            gameFloor->nextPosition(r, c, command);
            
            if ((gameFloor->getCell(r, c))->isStairs()) {
                if (currentLevel == 5) {
                    score = (int)player->getGold();
                    if (player->getRacestr() == "HUMAN") {
                        score = score * 1.5;
                    }
                    
                    cout << "Congratulations!" << endl;
                    cout << score << endl;
                    
                    string rOrq;
                    cout << "Restart or Quit?" << endl;
                    cin >> rOrq;
                    return passInput(rOrq);
                }
                else {
                    nextLevel();
                }
            }
            else if ((gameFloor->getCell(r, c))->isOccupied()) {
                actionScript = "Player can't move there because there's a " + symbolToString((gameFloor->getCell(r, c))->getCellSymbol()) + ".";
            }
            else if (!((gameFloor->getCell(r, c))->isBlocked())) {
                player->moveTo(r, c);
                ((gameFloor->getCell(r, c))->cellObject) = player;
                actionScript = "Player moves " + directionToString(command);
                if (objectsAroundPosition(r, c) != "") {
                    actionScript = actionScript + " and sees " + objectsAroundPosition(r, c);
                }
                actionScript += ". ";
            }
        }
        else if (command == "u") { // use potion
            string direction = askForDirection();
            if (direction == "Failed") {
                endGame();
                return true;
            }
            int r = player->getRCoord();
            int c = player->getCCoord();
            gameFloor->nextPosition(r, c, direction);
            
            if (gameFloor->getCellType(r, c) == GOLD) {
                Treasure *tempTreasure = (Treasure *)((gameFloor->getCell(r, c))->cellObject);
                tempTreasure->use(player);
            }
            else if (gameFloor->getCellType(r, c) == POTION) {
                Item *tempItem = (Item *)((gameFloor->getCell(r, c))->cellObject);
                if (tempItem->isIdentified()) {
                    tempItem->use(player);
                }
                else {
                    tempItem->use(player);
                    tempItem->setIdentified(true);
                }
            }
        }
        else if (command == "a") { //attack
            string direction = askForDirection();
            if (direction == "Failed") {
                endGame();
                return true;
            }
            int r = player->getRCoord();
            int c = player->getCCoord();
            gameFloor->nextPosition(r, c, direction);
            
            if (isEnemy(gameFloor->getCellType(r, c)) || (gameFloor->getCellType(r, c) == MERCHANT)) {
                Enemy *enemyBeingAttacked = (Enemy *)((gameFloor->getCell(r, c))->cellObject);
                actionScript = "Player deals " + itos(player->atk(enemyBeingAttacked)) + " damage to " + symbolToString(gameFloor->getCellType(r, c)) + " (" + itos(enemyBeingAttacked->getHP()) + " HP). ";
                
                if (gameFloor->getCellType(r, c) == MERCHANT) {
                    Merchant::hostile = true;
                }
            }
            else {
                cout << "Player doesn't hit anything" << endl;
            }
        }
        else if (command == "r") { //restart
            restartGame();
            return false;
        }
        else if (command == "q") { //quit
            endGame();
            return true;
        }
        else {
            return incorrectCommand();
        }
    }
    
    // Make all the enemies move randomly. Look at line 54 and the Player's moveTo function to get an idea
    // Restricted movement for dragons (must always be around the dragon hoard)
    
    bool playerDead = false;
    
    for (int r = 0; r < gameFloor->getWidth(); r++) {
        for (int c = 0; c < gameFloor->getLength(); c++) {
            
            Enemy *tempEnemy = ((Enemy*)((gameFloor->getCell(r, c))->cellObject));
            
            if (((isEnemy(gameFloor->getCellType(r, c))) || ((gameFloor->getCellType(r, c)) == MERCHANT)) && (turnTracker == tempEnemy->isTurn)) {
                if (tempEnemy->isTurn == 1) {
                    tempEnemy->isTurn--;
                }
                else {
                    tempEnemy->isTurn++;
                }
                
                if ((gameFloor->getCell(r, c))->getCellSymbol() == DRAGON) {
                    if (isPlayerClose(r, c) && playerIsCloseToDragonPile()) {
                        actionScript += (symbolToString((gameFloor->getCellType(r, c))) + " deals " + itos(tempEnemy->atk(player)) + " damage to PC. ");
                    }
                }
                else if (((isPlayerClose(r, c)) && ((gameFloor->getCellType(r, c)) != MERCHANT)) || ((isPlayerClose(r, c)) && ((gameFloor->getCellType(r, c)) == MERCHANT) && Merchant::hostile)) {
                    
                    actionScript += (symbolToString((gameFloor->getCellType(r, c))) + " deals " + itos(tempEnemy->atk(player)) + " damage to PC. ");
                }
                else {
                    int newRow = r;
                    int newCol = c;
                    
                    if ((gameFloor->getCell(r, c))->getCellSymbol() == DRAGON) {
                        Dragon *tempDragon = ((Dragon *)((gameFloor->getCell(r, c))->cellObject));
                        gameFloor->nextPosition(newRow, newCol, getRandomDirection(r, c, tempDragon));
                        ((gameFloor->getCell(newRow, newCol))->cellObject) = tempDragon;
                        tempDragon->moveTo(newRow, newCol);
                    }
                    else {
                        gameFloor->nextPosition(newRow, newCol, getRandomDirection(r, c, NULL));
                        ((gameFloor->getCell(newRow, newCol))->cellObject) = ((Character *)((gameFloor->getCell(r, c))->cellObject));
                        ((Character *)((gameFloor->getCell(r, c))->cellObject))->moveTo(newRow, newCol);
                    }
                }
            }
            
            if (player->getHP() == 0) {
                playerDead = true;
                break;
            }
        }
        if (playerDead) {
            break;
        }
    }
    
    if (playerDead) {
        string rOrq;
        cout << "Restart or Quit?" << endl;
        cin >> rOrq;
        passInput(rOrq);
        if (rOrq == "r") {
            return false;
        }
        else {
            return true;
        }
    }
    
    if (turnTracker == 1) {
        turnTracker--;
    }
    else {
        turnTracker++;
    }
    
    cout << *gameFloor;
    displayScoreBoard();
    
    return (false || suddenDeath);
}

//

void Game::newGame(string fileName, char playerRace) {
    gameFloor = new GameFloor(fileName);
    gameDisplay = GameDisplay::getInstance(gameFloor->getLength(), gameFloor->getWidth());
    gameFloor->generateMap(fileName, gameDisplay);
    
    placeMapObjectsRandomlyInTextDisplay(playerRace);
    actionScript = "Player character has spawned.";
    cout << *gameFloor;
    displayScoreBoard();
    
    gameStarted = true;
}

void Game::nextLevel() {
    reset();
    
    player->setAtkEffect(0);
    player->setDefEffect(0);
    
    gameFloor = new GameFloor(fileName);
    gameDisplay = GameDisplay::getInstance(gameFloor->getLength(), gameFloor->getWidth());
    gameFloor->generateMap(fileName, gameDisplay);
    
    currentLevel++;
    
    placeMapObjectsRandomlyInTextDisplay('h');
    
    actionScript = ("PC is now in Floor " + itos(currentLevel));
    cout << *gameFloor;
    displayScoreBoard();
}

void Game::restartGame() {
    gameStarted = false;
    reset();
}

void Game::endGame() {
    if (gameFloor != NULL) {
        reset();
    }
}

void Game::reset() {
	numOfNonDragonEnemies = maxEnemies;

    int r = gameFloor->getWidth();
    int c = gameFloor->getLength();
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if ((gameFloor->getCell(i, j))->isOccupied()) {
                if ((gameFloor->getCellType(i, j)) != PLAYER) {
                    (gameFloor->getCell(i, j))->cellObject = NULL;
                }
                else {
                    gameFloor->removeObject(i, j);
                }
            }
        }
    }
    
    delete gameFloor;
    gameDisplay = NULL;
    gameFloor = NULL;
}

void Game::cleanUp() {
    delete instance;
    instance = NULL;
}

Game::~Game() {
    
}

// Random generation

void Game::placeMapObjectsRandomlyInTextDisplay(char playerRace) {
    
    Cell *playerCell = selectRandomCell(NULL);
    if (currentLevel == 1) {
        player = new Player;
    	player->setRace(playerRace);
        player->setFloor(gameFloor);
    }
    playerCell->cellObject = player;
    gameFloor->setCellType(playerCell->getRCoord(), playerCell->getCCoord(), PLAYER);
    //player->setPos(playerCell->getRCoord(), playerCell->getCCoord(), gameFloor);
    
    // Stairs
    
    int tempR = playerCell->getRCoord();
    int tempC = playerCell->getCCoord();
    int randomChamber = 0;
    
    if (((tempR > 2) && (tempR < 7)) && ((tempC > 2) && (tempC < 29))) {
        int chambers[] = {2, 3, 4, 5};
        randomChamber = chambers[(rand() % 4)];
    }
    else if (((tempR > 14) && (tempR < 22)) && ((tempC > 3) && (tempC < 25))) {
        int chambers[] = {1, 2, 3, 5};
        randomChamber = chambers[(rand() % 4)];
    }
    else if (((tempR > 9) && (tempR < 13)) && ((tempC > 37) && (tempC < 50))) {
        int chambers[] = {1, 2, 3, 4};
        randomChamber = chambers[(rand() % 4)];
    }
    else if (((tempR > 15) && (tempR < 22)) && ((tempC > 36) && (tempC < 76))) {
        if (!(((tempR > 15) && (tempR < 18)) && ((tempC > 36) && (tempC < 64)))) {
            int chambers[] = {1, 2, 4, 5};
            randomChamber = chambers[(rand() % 4)];
        }
    }
    else {
        int chambers[] = {1, 3, 4, 5};
        randomChamber = chambers[(rand() % 4)];
    }
    
    Cell *stairCell;
    
    if (randomChamber == 1) {
        stairCell = (gameFloor->chamberOne)[rand() % (gameFloor->chamberOne).size()];
    }
    else if (randomChamber == 2) {
        stairCell = (gameFloor->chamberTwo)[rand() % (gameFloor->chamberTwo).size()];
    }
    else if (randomChamber == 3) {
        stairCell = (gameFloor->chamberThree)[rand() % (gameFloor->chamberThree).size()];
    }
    else if (randomChamber == 4) {
        stairCell = (gameFloor->chamberFour)[rand() % (gameFloor->chamberFour).size()];
    }
    else if (randomChamber == 5) {
        stairCell = (gameFloor->chamberFive)[rand() % (gameFloor->chamberFive).size()];
    }
    
    gameFloor->setCellType(stairCell->getRCoord(), stairCell->getCCoord(), STAIRS);
    
    //
    
    Cell *potionCell;
    string potionTypes[] = {"NH", "PH", "NA", "PA", "ND", "PD"};
    for (int i = 0; i < maxPotions; i++) {
        potionCell = selectRandomCell(NULL);
        string randomPotion = potionTypes[rand()%6];
        
        Item *item = new Item;
        item->setFloor(gameFloor);
        item->setPotType(randomPotion);
        potionCell->cellObject = item;
        gameFloor->setCellType(potionCell->getRCoord(), potionCell->getCCoord(), POTION);
    }
    
    int goldTypes[] = {1, 1, 1, 1, 1, 2, 2, 6};
    Cell *goldCell;
    for (int i = 0; i < maxGold; i++) {
    	goldCell = selectRandomCell(NULL);
        int randomGoldType = goldTypes[rand()%8];
        
        Treasure *treasure = new Treasure(randomGoldType);
        treasure->setFloor(gameFloor);
        goldCell->cellObject = treasure;
        gameFloor->setCellType(goldCell->getRCoord(), goldCell->getCCoord(), GOLD);
        
        if (randomGoldType == 6) {
            
            Dragon *dragon = new Dragon(treasure);
            Cell *dragonCell = selectRandomCell(dragon);
            
            dragon->setFloor(gameFloor);
            dragonCell->cellObject = dragon;
            gameFloor->setCellType(dragonCell->getRCoord(), dragonCell->getCCoord(), DRAGON);
            treasure->setGuard(dragon);
            
            numOfNonDragonEnemies--;
        }
    }
    
    Cell *enemyCell;
    Symbol enemies[] = {VAMPIRE, VAMPIRE, VAMPIRE, WEREWOLF, WEREWOLF, WEREWOLF, WEREWOLF, TROLL, TROLL, GOBLIN, GOBLIN, GOBLIN, GOBLIN, GOBLIN, MERCHANT, MERCHANT, PHOENIX, PHOENIX};
    for (int i = 0; i < numOfNonDragonEnemies; i++) {
    	enemyCell = selectRandomCell(NULL);
        Symbol randomEnemyType = enemies[rand()%18];
        if (randomEnemyType == MERCHANT) {
            Merchant *merchant = new Merchant;
            merchant->setFloor(gameFloor);
            enemyCell->cellObject = merchant;
            gameFloor->setCellType(enemyCell->getRCoord(), enemyCell->getCCoord(), MERCHANT);
        }
        else {
            Enemy *newEnemy = new Enemy;
            newEnemy->setFloor(gameFloor);
            newEnemy->create(newEnemy->symbolToEnemy(randomEnemyType));
            enemyCell->cellObject = newEnemy;
            gameFloor->setCellType(enemyCell->getRCoord(), enemyCell->getCCoord(), randomEnemyType);
        }
    }
}



Cell* Game::selectRandomCell(Dragon *d) {
    //srand(0);
    if (d != NULL) {
        vector<int> dragonCells;
        for (int i = 0; i < (gameFloor->emptyCells.size()); i++) {
            if (d->isCloseToHoard((gameFloor->emptyCells[i])->getRCoord(), (gameFloor->emptyCells[i])->getCCoord())) {
                dragonCells.push_back(i);
            }
        }
        int randomNum = dragonCells[rand()%(dragonCells.size())];
        Cell *tempCell = gameFloor->emptyCells[randomNum];
        (gameFloor->emptyCells).erase((gameFloor->emptyCells).begin() + randomNum);
        return tempCell;
    }
    
    unsigned int randomNum = rand()%(gameFloor->emptyCells.size());
    Cell *tempCell = gameFloor->emptyCells[randomNum];
    (gameFloor->emptyCells).erase((gameFloor->emptyCells).begin() + randomNum);
    return tempCell;
}

// Helper Functions

void Game::displayScoreBoard() {
    
    
    cout << "Race: " << player->getRacestr() << " Gold: " << player->getGold() << endl;
    cout << "HP: " << player->getHP() << endl;
    cout << "Atk: " << player->getAtk() << endl;
    cout << "Def: " << player->getDef() << endl;
    cout << "Action: " << actionScript << endl << endl;
}

bool Game::directionInput(std::string command) {
    return ((command == "no") || (command == "so") || (command == "ea") || (command == "we") || (command == "ne") || (command == "nw") || (command == "se") || (command == "sw"));
}

bool Game::raceInput(std::string command) {
    return ((command == "h") || (command == "e") || (command == "d") || (command == "o"));
}

bool Game::isEnemy(const Symbol race) {
    return ((race == GOBLIN) || (race == PHOENIX) || (race == DRAGON) || (race == TROLL) || (race == WEREWOLF) || (race == VAMPIRE) || ((race == MERCHANT) && Merchant::hostile));
}

string Game::askForDirection() {
    
    string direction;
    bool correctInput = false;
    
    while (!correctInput && (cin >> direction)) {
        correctInput = directionInput(direction);
    }
    
    if (!correctInput) {
        return "Failed";
    }
    
    return direction;
}

string Game::getRandomDirection(const int currentRow, const int currentCol, Dragon *d) {
    vector<string> possibleDirection;
    possibleDirection.push_back("no");
    possibleDirection.push_back("so");
    possibleDirection.push_back("ea");
    possibleDirection.push_back("we");
    possibleDirection.push_back("nw");
    possibleDirection.push_back("ne");
    possibleDirection.push_back("se");
    possibleDirection.push_back("sw");
    
    int tempRow = currentRow;
    int tempCol = currentCol;
    int index = 0;
    
    while ((unsigned int)index < possibleDirection.size()) {
        gameFloor->nextPosition(tempRow, tempCol, possibleDirection[index]);
        if (((gameFloor->getCell((tempRow), tempCol))->isBlocked()) || ((gameFloor->getCell((tempRow), tempCol))->isOccupied()) || ((gameFloor->getCell((tempRow), tempCol))->isStairs()) || ((gameFloor->getCell((tempRow), tempCol))->isDoor())) {
            possibleDirection.erase(possibleDirection.begin() + index);
        }
        else if ((d != NULL) && (!(d->isCloseToHoard(tempRow, tempCol)))) {
            possibleDirection.erase(possibleDirection.begin() + index);
        }
        else {
            index++;
        }
        tempRow = currentRow;
        tempCol = currentCol;
    }
    
    return possibleDirection[rand()%possibleDirection.size()];
}

bool Game::incorrectCommand() {
    
    cout << "Unrecognized input, please re-enter" << endl;
    
    string command;
    if (cin >> command) {
        return passInput(command);
    }
    else {
        endGame();
        return true;
    }
}

bool Game::isPlayerClose(int row, int col) {
	for (int i = (row - 1); i <= (row + 1); i++)
	{
		for (int j = (col - 1); j <= (col + 1); j++)
		{
			if ((i < (gameFloor->getWidth())) && (j < (gameFloor->getLength())) && ((i == player->getRCoord()) && (j == player->getCCoord())))
			{
                return true;
			}
		}
	}
	return false;
}

bool Game::playerIsCloseToDragonPile() {
    for (int i = (player->getRCoord() - 1); i <= (player->getRCoord() + 1); i++)
	{
		for (int j = (player->getCCoord() - 1); j <= (player->getCCoord() + 1); j++)
		{
			if ((i < (gameFloor->getWidth())) && (j < (gameFloor->getLength())))
			{
                if ((gameFloor->getCellType(i, j)) == GOLD) {
                    Treasure *nearTreasure = ((Treasure *)((gameFloor->getCell(i, j))->cellObject));
                    if ((nearTreasure->getGoldVal() == 6)) {
                        return true;
                    }
                }
			}
		}
	}
    return false;
}

string Game::symbolToString(const Symbol s) {
    if ((s == V_WALL) || (s == H_WALL)) {
        return "Wall";
    }
    else if (s == VACANT) {
        return "Worm hole";
    }
    else if (s == POTION) {
        return "Potion";
    }
    else if (s == GOLD) {
        return "Gold";
    }
    else if (s == DRAGON) {
        return "Dragon";
    }
    else if (s == WEREWOLF) {
        return "Werewolf";
    }
    else if (s == VAMPIRE) {
        return "Vampire";
    }
    else if (s == GOBLIN) {
        return "Goblin";
    }
    else if (s == MERCHANT) {
        return "Merchant";
    }
    else if (s == TROLL) {
        return "Troll";
    }
    else if (s == PHOENIX) {
        return "Phoneix";
    }
    return "NA";
}

string Game::directionToString(const std::string command) {
    if (command == "ea") {
        return "East";
    }
    else if (command == "we") {
        return "West";
    }
    else if (command == "no") {
        return "North";
    }
    else if (command == "so") {
        return "South";
    }
    else if (command == "se") {
        return "South East";
    }
    else if (command == "ne") {
        return "North East";
    }
    else if (command == "nw") {
        return "North West";
    }
    else {
        return "South West";
    }
}

string Game::objectsAroundPosition(const int r, const int c) {
    string outputText = "";
    for (int i = (r - 1); i <= (r + 1); i++)
	{
		for (int j = (c - 1); j <= (c + 1); j++)
		{
			if ((i < (gameFloor->getWidth())) && (j < (gameFloor->getLength())))
			{
                if ((gameFloor->getCellType(i, j)) == POTION) {
                    Item *nearItem = ((Item *)((gameFloor->getCell(i, j))->cellObject));
                    if (nearItem->isIdentified()) {
                        outputText += ("a " + nearItem->getPotType() + " potion, ");
                    }
                    else {
                        outputText += "an unknown potion, ";
                    }
                }
                else if ((gameFloor->getCellType(i, j)) == GOLD) {
                    Treasure *nearTreasure = ((Treasure *)((gameFloor->getCell(i, j))->cellObject));
                    if ((nearTreasure->getGoldVal() == 6)) {
                        outputText += ("a dragon horde, ");
                    }
                    else if ((nearTreasure->getGoldVal() == 1)) {
                        outputText += ("a normal gold pile, ");
                    }
                    else if ((nearTreasure->getGoldVal() == 2)) {
                        outputText += ("a small horde, ");
                    }
                    else if ((nearTreasure->getGoldVal() == 4)) {
                        outputText += ("a merchant horde, ");
                    }
                }
                else if (isEnemy((gameFloor->getCellType(i, j)))) {
                    outputText += ("a " + symbolToString((gameFloor->getCellType(i, j))) + ", ");
                }
                
			}
		}
	}
    if (outputText.size() > 2) {
        outputText.erase(outputText.size()-2, outputText.size()-1);
        return outputText;
    }
    return outputText;
}

std::string Game::itos(int i)
{
    std::string s;
    std::ostringstream convert;
    convert << i;
    s = convert.str();
    return s;
}