#include "Game.h"
#include "Space.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>

Game::Game() : currentPlayerIndex(0), gameOver(false), turnNumber(1), lastDiceRoll(0) {}

// ============================================================================
// Game Setup
// ============================================================================

void Game::setupGame() {
    std::cout << "\n" << std::string(80, '=') << "\n";
    std::cout << "                    WELCOME TO MONOPOLY!\n";
    std::cout << std::string(80, '=') << "\n\n";
    
    int numPlayers = 0;
    while (numPlayers < 2 || numPlayers > 8) {
        std::cout << "Enter number of players (2-8): ";
        std::cin >> numPlayers;
        
        if (std::cin.fail() || numPlayers < 2 || numPlayers > 8) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 2 and 8.\n";
            numPlayers = 0;
        }
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    for (int i = 0; i < numPlayers; ++i) {
        std::string name;
        std::cout << "Enter name for Player " << (i + 1) << ": ";
        std::getline(std::cin, name);
        
        if (name.empty()) {
            name = "Player " + std::to_string(i + 1);
        }
        
        addPlayer(name);
    }
    
    std::cout << "\nGame setup complete! Starting with " << numPlayers << " players.\n";
    std::cout << "Each player starts with $1500.\n";
    std::cout << "\nPress Enter to begin...";
    std::cin.get();
}

void Game::addPlayer(const std::string& name) {
    players.push_back(std::make_unique<Player>(name));
}

// ============================================================================
// Main Game Loop
// ============================================================================

void Game::start() {
    while (!gameOver) {
        Player* currentPlayer = getCurrentPlayer();
        
        if (!currentPlayer->isBankrupt()) {
            displayGameState();
            playTurn(*currentPlayer);
        }
        
        // Check win condition
        if (checkWinCondition()) {
            gameOver = true;
            break;
        }
        
        // Move to next player
        do {
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        } while (players[currentPlayerIndex]->isBankrupt() && !checkWinCondition());
        
        // Increment turn number when back to first player
        if (currentPlayerIndex == 0) {
            turnNumber++;
        }
    }
    
    // Game over - display winner
    std::cout << "\n" << std::string(80, '=') << "\n";
    std::cout << "                         GAME OVER!\n";
    std::cout << std::string(80, '=') << "\n\n";
    
    Player* winner = nullptr;
    int maxAssets = 0;
    
    for (const auto& player : players) {
        if (!player->isBankrupt()) {
            int assets = player->getTotalAssets();
            std::cout << player->getName() << " - Total Assets: $" << assets << "\n";
            
            if (assets > maxAssets) {
                maxAssets = assets;
                winner = player.get();
            }
        }
    }
    
    if (winner) {
        std::cout << "\n🏆 " << winner->getName() << " WINS! 🏆\n";
        std::cout << "Total Assets: $" << maxAssets << "\n";
    }
    
    std::cout << "\nThank you for playing Monopoly!\n";
}

// ============================================================================
// Turn Management
// ============================================================================

void Game::playTurn(Player& player) {
    std::cout << "\n" << std::string(80, '-') << "\n";
    std::cout << player.getName() << "'s Turn (Turn #" << turnNumber << ")\n";
    std::cout << std::string(80, '-') << "\n";
    
    displayPlayerInfo(player);
    
    // Handle jail
    if (player.isInJail()) {
        handleJail(player);
        if (player.isInJail()) {
            return; // Still in jail, turn ends
        }
    }
    
    std::cout << "\nPress Enter to roll dice...";
    std::cin.get();
    
    int doublesCount = 0;
    bool turnContinues = true;
    
    while (turnContinues && !player.isBankrupt()) {
        // Roll dice
        dice.roll();
        lastDiceRoll = dice.getTotal();
        
        std::cout << "\n🎲 Rolled: " << dice.getDie1() << " + " << dice.getDie2() 
                  << " = " << dice.getTotal();
        
        if (dice.isDoubles()) {
            doublesCount++;
            std::cout << " (DOUBLES!)";
            
            if (doublesCount == 3) {
                std::cout << "\n⚠️  Three doubles in a row! Go to Jail!\n";
                player.sendToJail();
                return;
            }
        }
        std::cout << "\n";
        
        // Move player
        int oldPosition = player.getPosition();
        player.move(dice.getTotal());
        int newPosition = player.getPosition();
        
        std::cout << "Moved from position " << oldPosition << " to position " << newPosition << "\n";
        
        if (newPosition < oldPosition) {
            std::cout << "💰 Passed GO! Collected $200\n";
        }
        
        // Get the space
        Space* space = board.getSpace(newPosition);
        if (!space) {
            turnContinues = false;
            continue;
        }
        
        std::cout << "\nLanded on: " << space->getName() << "\n";
        
        // Handle the space
        Property* property = dynamic_cast<Property*>(space);
        Railroad* railroad = dynamic_cast<Railroad*>(space);
        Utility* utility = dynamic_cast<Utility*>(space);
        SpecialSpace* special = dynamic_cast<SpecialSpace*>(space);
        
        if (property) {
            if (property->canBePurchased()) {
                handlePurchaseOption(player, space);
            } else if (property->getOwner() != &player) {
                handleRentPayment(player, property);
            } else {
                std::cout << "You own this property.\n";
                
                // Offer to build houses/hotels
                if (property->canBuildHouse() && player.getMoney() >= property->getHouseCost()) {
                    if (getUserConfirmation("Build a house for $" + std::to_string(property->getHouseCost()) + "?")) {
                        if (player.subtractMoney(property->getHouseCost())) {
                            property->buildHouse();
                            std::cout << "🏠 Built a house on " << property->getName() << "!\n";
                        }
                    }
                } else if (property->canBuildHotel() && player.getMoney() >= property->getHouseCost()) {
                    if (getUserConfirmation("Build a hotel for $" + std::to_string(property->getHouseCost()) + "?")) {
                        if (player.subtractMoney(property->getHouseCost())) {
                            property->buildHotel();
                            std::cout << "🏨 Built a hotel on " << property->getName() << "!\n";
                        }
                    }
                }
            }
        } else if (railroad) {
            if (railroad->canBePurchased()) {
                handlePurchaseOption(player, space);
            } else if (railroad->getOwner() != &player) {
                handleRailroadRent(player, railroad);
            } else {
                std::cout << "You own this railroad.\n";
            }
        } else if (utility) {
            if (utility->canBePurchased()) {
                handlePurchaseOption(player, space);
            } else if (utility->getOwner() != &player) {
                handleUtilityRent(player, utility);
            } else {
                std::cout << "You own this utility.\n";
            }
        } else if (special) {
            special->landOn(player);
            
            if (special->getType() == "GO_TO_JAIL") {
                std::cout << "🚔 Go directly to Jail!\n";
                return;
            } else if (special->getType() == "INCOME_TAX") {
                std::cout << "💸 Paid $200 Income Tax\n";
            } else if (special->getType() == "LUXURY_TAX") {
                std::cout << "💸 Paid $75 Luxury Tax\n";
            }
        }
        
        // Check if player is bankrupt
        if (player.getMoney() < 0) {
            std::cout << "\n⚠️  " << player.getName() << " is bankrupt!\n";
            player.declareBankruptcy();
            return;
        }
        
        // Continue if rolled doubles
        if (dice.isDoubles() && doublesCount < 3) {
            std::cout << "\nYou rolled doubles! Roll again.\n";
            std::cout << "Press Enter to continue...";
            std::cin.get();
            turnContinues = true;
        } else {
            turnContinues = false;
        }
    }
    
    std::cout << "\n" << player.getName() << "'s turn complete.\n";
    std::cout << "Current money: $" << player.getMoney() << "\n";
    std::cout << "\nPress Enter to continue to next player...";
    std::cin.get();
}

// ============================================================================
// Space Handling
// ============================================================================

void Game::handlePurchaseOption(Player& player, Space* space) {
    Property* property = dynamic_cast<Property*>(space);
    Railroad* railroad = dynamic_cast<Railroad*>(space);
    Utility* utility = dynamic_cast<Utility*>(space);
    
    int price = 0;
    if (property) {
        price = property->getPrice();
        std::cout << property->getDescription() << "\n";
    } else if (railroad) {
        price = railroad->getPrice();
        std::cout << railroad->getDescription() << "\n";
    } else if (utility) {
        price = utility->getPrice();
        std::cout << utility->getDescription() << "\n";
    }
    
    if (player.getMoney() >= price) {
        if (getUserConfirmation("Buy for $" + std::to_string(price) + "?")) {
            if (player.subtractMoney(price)) {
                if (property) {
                    player.addProperty(property);
                    std::cout << "✅ Purchased " << property->getName() << "!\n";
                } else if (railroad) {
                    player.addRailroad(railroad);
                    std::cout << "✅ Purchased " << railroad->getName() << "!\n";
                } else if (utility) {
                    player.addUtility(utility);
                    std::cout << "✅ Purchased " << utility->getName() << "!\n";
                }
            }
        } else {
            std::cout << "Declined to purchase.\n";
        }
    } else {
        std::cout << "❌ Insufficient funds to purchase (Need $" << price << ", have $" << player.getMoney() << ")\n";
    }
}

void Game::handleRentPayment(Player& player, Property* property) {
    Player* owner = property->getOwner();
    if (!owner || owner == &player) return;
    
    int rent = property->getCurrentRent();
    std::cout << "💸 Paying $" << rent << " rent to " << owner->getName() << "\n";
    
    if (player.subtractMoney(rent)) {
        owner->addMoney(rent);
    } else {
        std::cout << "❌ Insufficient funds! Bankruptcy imminent.\n";
        player.declareBankruptcy();
    }
}

void Game::handleRailroadRent(Player& player, Railroad* railroad) {
    Player* owner = railroad->getOwner();
    if (!owner || owner == &player) return;
    
    int railroadsOwned = static_cast<int>(owner->getRailroads().size());
    int rent = railroad->getRent(railroadsOwned);
    
    std::cout << "💸 Paying $" << rent << " rent to " << owner->getName() 
              << " (owns " << railroadsOwned << " railroad(s))\n";
    
    if (player.subtractMoney(rent)) {
        owner->addMoney(rent);
    } else {
        std::cout << "❌ Insufficient funds! Bankruptcy imminent.\n";
        player.declareBankruptcy();
    }
}

void Game::handleUtilityRent(Player& player, Utility* utility) {
    Player* owner = utility->getOwner();
    if (!owner || owner == &player) return;
    
    int utilitiesOwned = static_cast<int>(owner->getUtilities().size());
    int rent = utility->getRent(utilitiesOwned, lastDiceRoll);
    
    std::cout << "💸 Paying $" << rent << " rent to " << owner->getName()
              << " (owns " << utilitiesOwned << " utility/utilities, dice roll × " 
              << (utilitiesOwned == 2 ? "10" : "4") << ")\n";
    
    if (player.subtractMoney(rent)) {
        owner->addMoney(rent);
    } else {
        std::cout << "❌ Insufficient funds! Bankruptcy imminent.\n";
        player.declareBankruptcy();
    }
}

void Game::handleJail(Player& player) {
    std::cout << "\n🔒 You are in Jail (Turn " << player.getJailTurns() + 1 << "/3)\n";
    std::cout << "Options:\n";
    std::cout << "1. Try to roll doubles\n";
    std::cout << "2. Pay $50 fine\n";
    
    if (player.hasGetOutOfJailCard()) {
        std::cout << "3. Use Get Out of Jail Free card\n";
    }
    
    std::string choice = getUserInput("Enter choice: ");
    
    if (choice == "2" && player.getMoney() >= 50) {
        if (player.subtractMoney(50)) {
            player.releaseFromJail();
            std::cout << "✅ Paid $50 fine. You are free!\n";
        }
    } else if (choice == "3" && player.hasGetOutOfJailCard()) {
        player.useGetOutOfJailCard();
        player.releaseFromJail();
        std::cout << "✅ Used Get Out of Jail Free card. You are free!\n";
    } else {
        // Try to roll doubles
        std::cout << "\nPress Enter to roll for doubles...";
        std::cin.get();
        
        dice.roll();
        std::cout << "🎲 Rolled: " << dice.getDie1() << " + " << dice.getDie2() << "\n";
        
        if (dice.isDoubles()) {
            std::cout << "✅ Rolled doubles! You are free!\n";
            player.releaseFromJail();
        } else {
            player.incrementJailTurns();
            
            if (player.getJailTurns() >= 3) {
                std::cout << "⚠️  Failed to roll doubles 3 times. Must pay $50.\n";
                if (player.subtractMoney(50)) {
                    player.releaseFromJail();
                    std::cout << "✅ Paid $50 fine. You are free!\n";
                } else {
                    std::cout << "❌ Insufficient funds! Bankruptcy imminent.\n";
                    player.declareBankruptcy();
                }
            } else {
                std::cout << "❌ Did not roll doubles. Still in jail.\n";
            }
        }
    }
}

// ============================================================================
// Display and UI
// ============================================================================

void Game::displayGameState() const {
    std::cout << "\n\n";
    std::cout << std::string(80, '=') << "\n";
    std::cout << "Turn " << turnNumber << " - Current Game State\n";
    std::cout << std::string(80, '=') << "\n";
    
    for (const auto& player : players) {
        if (!player->isBankrupt()) {
            std::cout << player->getStatus() << "\n\n";
        }
    }
}

void Game::displayPlayerInfo(const Player& player) const {
    std::cout << "\n" << player.getStatus() << "\n";
    
    Space* currentSpace = board.getSpace(player.getPosition());
    if (currentSpace) {
        std::cout << "Current position: " << currentSpace->getName() << "\n";
    }
}

bool Game::checkWinCondition() {
    int activePlayers = 0;
    
    for (const auto& player : players) {
        if (!player->isBankrupt()) {
            activePlayers++;
        }
    }
    
    return activePlayers <= 1;
}

// ============================================================================
// Helper Methods
// ============================================================================

Player* Game::getCurrentPlayer() const {
    if (currentPlayerIndex < static_cast<int>(players.size())) {
        return players[currentPlayerIndex].get();
    }
    return nullptr;
}

std::string Game::getUserInput(const std::string& prompt) const {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

bool Game::getUserConfirmation(const std::string& prompt) const {
    std::cout << prompt << " (y/n): ";
    std::string input;
    std::getline(std::cin, input);
    return !input.empty() && (input[0] == 'y' || input[0] == 'Y');
}
