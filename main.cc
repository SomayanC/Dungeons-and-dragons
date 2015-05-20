#include <iostream>
#include "Game.h"
using namespace std;

int main() {
    
    Game *cc3k = NULL;
    string inputText;
    bool gameEnded = false;
    
    while ((cin >> inputText) && !gameEnded) {
        if (cc3k != NULL) {
            gameEnded = cc3k->passInput(inputText);
        }
        else {
            cc3k = Game::getInstance();
            gameEnded = cc3k->passInput(inputText);
        }
        
        if (gameEnded) {
            break;
        }
    }
    
    if (!gameEnded) {
        cc3k->endGame();
    }
}

//int main(int argc, const char * argv[]) {
//
//    Game *cc3k = NULL;
//    string inputText;
//    bool gameEnded = false;
//
//    if (argc == 2) {
//        cc3k = Game::getInstance();
//
//        while ((cin >> inputText) && !gameEnded) {
//            gameEnded = cc3k->passInput(inputText);
//            if (gameEnded) {
//               break;
//            }
//        }
//
//        if (!gameEnded) {
//            cc3k->endGame();
//        }
//    }
//}