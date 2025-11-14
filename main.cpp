#include "Game.h"
#include <iostream>

/**
 * Main entry point for the Monopoly game
 */
int main() {
    try {
        Game game;
        game.setupGame();
        game.start();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
