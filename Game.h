#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include "Player.h"
#include "Board.h"
#include "Dice.h"

/**
 * Main game controller for Monopoly
 */
class Game {
private:
    std::vector<std::unique_ptr<Player>> players;
    Board board;
    Dice dice;
    int currentPlayerIndex;
    bool gameOver;
    int turnNumber;
    int lastDiceRoll;

    void playTurn(Player& player);
    void handlePurchaseOption(Player& player, Space* space);
    void handleRentPayment(Player& player, Property* property);
    void handleRailroadRent(Player& player, Railroad* railroad);
    void handleUtilityRent(Player& player, Utility* utility);
    void handleJail(Player& player);
    bool checkWinCondition();
    void displayGameState() const;
    void displayPlayerInfo(const Player& player) const;
    std::string getUserInput(const std::string& prompt) const;
    bool getUserConfirmation(const std::string& prompt) const;

public:
    Game();
    
    void setupGame();
    void start();
    void addPlayer(const std::string& name);
    
    Player* getCurrentPlayer() const;
    int getLastDiceRoll() const { return lastDiceRoll; }
    bool isGameOver() const { return gameOver; }
    int getTurnNumber() const { return turnNumber; }
};

#endif // GAME_H
