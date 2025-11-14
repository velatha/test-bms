#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "Dice.h"
#include "Space.h"
#include <iostream>
#include <cassert>

/**
 * Test suite for Monopoly game components
 */

void testDice() {
    std::cout << "Testing Dice..." << std::endl;
    Dice dice;
    
    // Test rolling
    auto roll = dice.roll();
    assert(roll.first >= 1 && roll.first <= 6);
    assert(roll.second >= 1 && roll.second <= 6);
    assert(dice.getDie1() == roll.first);
    assert(dice.getDie2() == roll.second);
    assert(dice.getTotal() == roll.first + roll.second);
    
    std::cout << "  ✓ Dice rolling works correctly" << std::endl;
}

void testPlayer() {
    std::cout << "Testing Player..." << std::endl;
    Player player("Test Player", 1500);
    
    // Test initial state
    assert(player.getName() == "Test Player");
    assert(player.getMoney() == 1500);
    assert(player.getPosition() == 0);
    assert(!player.isInJail());
    assert(!player.isBankrupt());
    
    // Test money management
    player.addMoney(200);
    assert(player.getMoney() == 1700);
    
    bool success = player.subtractMoney(500);
    assert(success);
    assert(player.getMoney() == 1200);
    
    success = player.subtractMoney(2000);
    assert(!success);
    assert(player.getMoney() == 1200);
    
    // Test movement
    player.move(7);
    assert(player.getPosition() == 7);
    
    player.move(5);
    assert(player.getPosition() == 12);
    
    // Test passing GO
    int moneyBefore = player.getMoney();
    player.move(30); // Should wrap around and pass GO
    assert(player.getPosition() == 2);
    assert(player.getMoney() == moneyBefore + 200);
    
    // Test jail
    player.sendToJail();
    assert(player.isInJail());
    assert(player.getPosition() == 10);
    
    player.releaseFromJail();
    assert(!player.isInJail());
    
    std::cout << "  ✓ Player mechanics work correctly" << std::endl;
}

void testBoard() {
    std::cout << "Testing Board..." << std::endl;
    Board board;
    
    // Test board has correct number of spaces
    assert(board.getTotalSpaces() == 40);
    
    // Test specific spaces
    Space* go = board.getSpace(0);
    assert(go != nullptr);
    assert(go->getName() == "GO");
    
    Space* boardwalk = board.getSpace(39);
    assert(boardwalk != nullptr);
    assert(boardwalk->getName() == "Boardwalk");
    
    // Test property
    Space* space1 = board.getSpace(1);
    Property* mediterranean = dynamic_cast<Property*>(space1);
    assert(mediterranean != nullptr);
    assert(mediterranean->getName() == "Mediterranean Avenue");
    assert(mediterranean->getPrice() == 60);
    assert(mediterranean->canBePurchased());
    
    // Test railroad
    Space* space5 = board.getSpace(5);
    Railroad* reading = dynamic_cast<Railroad*>(space5);
    assert(reading != nullptr);
    assert(reading->getName() == "Reading Railroad");
    assert(reading->getPrice() == 200);
    
    // Test utility
    Space* space12 = board.getSpace(12);
    Utility* electric = dynamic_cast<Utility*>(space12);
    assert(electric != nullptr);
    assert(electric->getName() == "Electric Company");
    assert(electric->getPrice() == 150);
    
    std::cout << "  ✓ Board initialized correctly with all spaces" << std::endl;
}

void testProperty() {
    std::cout << "Testing Property..." << std::endl;
    
    Property property("Test Property", 1, 100, 10, 20, 50, 100, 200, 300, 400, 50, "Test Color");
    Player player1("Player 1");
    Player player2("Player 2");
    
    // Test initial state
    assert(property.canBePurchased());
    assert(property.getOwner() == nullptr);
    assert(property.getPrice() == 100);
    
    // Test purchase
    property.setOwner(&player1);
    player1.addProperty(&property);
    assert(!property.canBePurchased());
    assert(property.getOwner() == &player1);
    
    // Test rent calculation
    int baseRent = property.getCurrentRent();
    assert(baseRent == 10); // Base rent without color set
    
    // Test building
    assert(property.getHouses() == 0);
    assert(!property.getHasHotel());
    
    std::cout << "  ✓ Property mechanics work correctly" << std::endl;
}

void testRailroad() {
    std::cout << "Testing Railroad..." << std::endl;
    
    Railroad railroad("Test Railroad", 5);
    Player player("Player 1");
    
    // Test initial state
    assert(railroad.canBePurchased());
    assert(railroad.getPrice() == 200);
    
    // Test rent scaling
    assert(railroad.getRent(1) == 25);
    assert(railroad.getRent(2) == 50);
    assert(railroad.getRent(3) == 100);
    assert(railroad.getRent(4) == 200);
    
    // Test ownership
    railroad.setOwner(&player);
    player.addRailroad(&railroad);
    assert(railroad.getOwner() == &player);
    assert(!railroad.canBePurchased());
    
    std::cout << "  ✓ Railroad mechanics work correctly" << std::endl;
}

void testUtility() {
    std::cout << "Testing Utility..." << std::endl;
    
    Utility utility("Test Utility", 12);
    Player player("Player 1");
    
    // Test initial state
    assert(utility.canBePurchased());
    assert(utility.getPrice() == 150);
    
    // Test rent calculation
    assert(utility.getRent(1, 7) == 28);  // 7 * 4
    assert(utility.getRent(2, 7) == 70);  // 7 * 10
    
    // Test ownership
    utility.setOwner(&player);
    player.addUtility(&utility);
    assert(utility.getOwner() == &player);
    assert(!utility.canBePurchased());
    
    std::cout << "  ✓ Utility mechanics work correctly" << std::endl;
}

void testColorGroups() {
    std::cout << "Testing Color Groups..." << std::endl;
    
    assert(Board::getColorGroupSize("Brown") == 2);
    assert(Board::getColorGroupSize("Dark Blue") == 2);
    assert(Board::getColorGroupSize("Light Blue") == 3);
    assert(Board::getColorGroupSize("Pink") == 3);
    assert(Board::getColorGroupSize("Orange") == 3);
    assert(Board::getColorGroupSize("Red") == 3);
    assert(Board::getColorGroupSize("Yellow") == 3);
    assert(Board::getColorGroupSize("Green") == 3);
    
    std::cout << "  ✓ Color group sizes correct" << std::endl;
}

void testBankruptcy() {
    std::cout << "Testing Bankruptcy..." << std::endl;
    
    Player player("Test Player");
    Board board;
    
    // Get a property and assign it to player
    Property* prop = dynamic_cast<Property*>(board.getSpace(1));
    assert(prop != nullptr);
    
    prop->setOwner(&player);
    player.addProperty(prop);
    
    assert(!player.isBankrupt());
    assert(player.getProperties().size() == 1);
    assert(prop->getOwner() == &player);
    
    // Declare bankruptcy
    player.declareBankruptcy();
    
    assert(player.isBankrupt());
    assert(player.getProperties().size() == 0);
    assert(prop->getOwner() == nullptr);
    
    std::cout << "  ✓ Bankruptcy handling works correctly" << std::endl;
}

int main() {
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "Running Monopoly Game Test Suite" << std::endl;
    std::cout << std::string(80, '=') << "\n" << std::endl;
    
    try {
        testDice();
        testPlayer();
        testBoard();
        testProperty();
        testRailroad();
        testUtility();
        testColorGroups();
        testBankruptcy();
        
        std::cout << "\n" << std::string(80, '=') << std::endl;
        std::cout << "✅ All tests passed successfully!" << std::endl;
        std::cout << std::string(80, '=') << std::endl;
        
        std::cout << "\nMonopoly game components validated:" << std::endl;
        std::cout << "  • Dice mechanics" << std::endl;
        std::cout << "  • Player management" << std::endl;
        std::cout << "  • Board initialization" << std::endl;
        std::cout << "  • Property system" << std::endl;
        std::cout << "  • Railroad mechanics" << std::endl;
        std::cout << "  • Utility mechanics" << std::endl;
        std::cout << "  • Color groups" << std::endl;
        std::cout << "  • Bankruptcy handling" << std::endl;
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "❌ Test failed: " << e.what() << std::endl;
        return 1;
    }
}
