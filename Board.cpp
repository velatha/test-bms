#include "Board.h"
#include <iostream>
#include <iomanip>

Board::Board() {
    initializeSpaces();
}

void Board::initializeSpaces() {
    // Position 0: GO
    spaces.push_back(std::make_unique<SpecialSpace>("GO", 0, "GO"));
    
    // Position 1: Mediterranean Avenue
    spaces.push_back(std::make_unique<Property>("Mediterranean Avenue", 1, 60, 2, 4, 10, 30, 90, 160, 250, 50, "Brown"));
    
    // Position 2: Community Chest
    spaces.push_back(std::make_unique<SpecialSpace>("Community Chest", 2, "COMMUNITY_CHEST"));
    
    // Position 3: Baltic Avenue
    spaces.push_back(std::make_unique<Property>("Baltic Avenue", 3, 60, 4, 8, 20, 60, 180, 320, 450, 50, "Brown"));
    
    // Position 4: Income Tax
    spaces.push_back(std::make_unique<SpecialSpace>("Income Tax", 4, "INCOME_TAX"));
    
    // Position 5: Reading Railroad
    spaces.push_back(std::make_unique<Railroad>("Reading Railroad", 5));
    
    // Position 6: Oriental Avenue
    spaces.push_back(std::make_unique<Property>("Oriental Avenue", 6, 100, 6, 12, 30, 90, 270, 400, 550, 50, "Light Blue"));
    
    // Position 7: Chance
    spaces.push_back(std::make_unique<SpecialSpace>("Chance", 7, "CHANCE"));
    
    // Position 8: Vermont Avenue
    spaces.push_back(std::make_unique<Property>("Vermont Avenue", 8, 100, 6, 12, 30, 90, 270, 400, 550, 50, "Light Blue"));
    
    // Position 9: Connecticut Avenue
    spaces.push_back(std::make_unique<Property>("Connecticut Avenue", 9, 120, 8, 16, 40, 100, 300, 450, 600, 50, "Light Blue"));
    
    // Position 10: Jail (Just Visiting)
    spaces.push_back(std::make_unique<SpecialSpace>("Jail / Just Visiting", 10, "JAIL"));
    
    // Position 11: St. Charles Place
    spaces.push_back(std::make_unique<Property>("St. Charles Place", 11, 140, 10, 20, 50, 150, 450, 625, 750, 100, "Pink"));
    
    // Position 12: Electric Company
    spaces.push_back(std::make_unique<Utility>("Electric Company", 12));
    
    // Position 13: States Avenue
    spaces.push_back(std::make_unique<Property>("States Avenue", 13, 140, 10, 20, 50, 150, 450, 625, 750, 100, "Pink"));
    
    // Position 14: Virginia Avenue
    spaces.push_back(std::make_unique<Property>("Virginia Avenue", 14, 160, 12, 24, 60, 180, 500, 700, 900, 100, "Pink"));
    
    // Position 15: Pennsylvania Railroad
    spaces.push_back(std::make_unique<Railroad>("Pennsylvania Railroad", 15));
    
    // Position 16: St. James Place
    spaces.push_back(std::make_unique<Property>("St. James Place", 16, 180, 14, 28, 70, 200, 550, 750, 950, 100, "Orange"));
    
    // Position 17: Community Chest
    spaces.push_back(std::make_unique<SpecialSpace>("Community Chest", 17, "COMMUNITY_CHEST"));
    
    // Position 18: Tennessee Avenue
    spaces.push_back(std::make_unique<Property>("Tennessee Avenue", 18, 180, 14, 28, 70, 200, 550, 750, 950, 100, "Orange"));
    
    // Position 19: New York Avenue
    spaces.push_back(std::make_unique<Property>("New York Avenue", 19, 200, 16, 32, 80, 220, 600, 800, 1000, 100, "Orange"));
    
    // Position 20: Free Parking
    spaces.push_back(std::make_unique<SpecialSpace>("Free Parking", 20, "FREE_PARKING"));
    
    // Position 21: Kentucky Avenue
    spaces.push_back(std::make_unique<Property>("Kentucky Avenue", 21, 220, 18, 36, 90, 250, 700, 875, 1050, 150, "Red"));
    
    // Position 22: Chance
    spaces.push_back(std::make_unique<SpecialSpace>("Chance", 22, "CHANCE"));
    
    // Position 23: Indiana Avenue
    spaces.push_back(std::make_unique<Property>("Indiana Avenue", 23, 220, 18, 36, 90, 250, 700, 875, 1050, 150, "Red"));
    
    // Position 24: Illinois Avenue
    spaces.push_back(std::make_unique<Property>("Illinois Avenue", 24, 240, 20, 40, 100, 300, 750, 925, 1100, 150, "Red"));
    
    // Position 25: B&O Railroad
    spaces.push_back(std::make_unique<Railroad>("B&O Railroad", 25));
    
    // Position 26: Atlantic Avenue
    spaces.push_back(std::make_unique<Property>("Atlantic Avenue", 26, 260, 22, 44, 110, 330, 800, 975, 1150, 150, "Yellow"));
    
    // Position 27: Ventnor Avenue
    spaces.push_back(std::make_unique<Property>("Ventnor Avenue", 27, 260, 22, 44, 110, 330, 800, 975, 1150, 150, "Yellow"));
    
    // Position 28: Water Works
    spaces.push_back(std::make_unique<Utility>("Water Works", 28));
    
    // Position 29: Marvin Gardens
    spaces.push_back(std::make_unique<Property>("Marvin Gardens", 29, 280, 24, 48, 120, 360, 850, 1025, 1200, 150, "Yellow"));
    
    // Position 30: Go To Jail
    spaces.push_back(std::make_unique<SpecialSpace>("Go To Jail", 30, "GO_TO_JAIL"));
    
    // Position 31: Pacific Avenue
    spaces.push_back(std::make_unique<Property>("Pacific Avenue", 31, 300, 26, 52, 130, 390, 900, 1100, 1275, 200, "Green"));
    
    // Position 32: North Carolina Avenue
    spaces.push_back(std::make_unique<Property>("North Carolina Avenue", 32, 300, 26, 52, 130, 390, 900, 1100, 1275, 200, "Green"));
    
    // Position 33: Community Chest
    spaces.push_back(std::make_unique<SpecialSpace>("Community Chest", 33, "COMMUNITY_CHEST"));
    
    // Position 34: Pennsylvania Avenue
    spaces.push_back(std::make_unique<Property>("Pennsylvania Avenue", 34, 320, 28, 56, 150, 450, 1000, 1200, 1400, 200, "Green"));
    
    // Position 35: Short Line Railroad
    spaces.push_back(std::make_unique<Railroad>("Short Line Railroad", 35));
    
    // Position 36: Chance
    spaces.push_back(std::make_unique<SpecialSpace>("Chance", 36, "CHANCE"));
    
    // Position 37: Park Place
    spaces.push_back(std::make_unique<Property>("Park Place", 37, 350, 35, 70, 175, 500, 1100, 1300, 1500, 200, "Dark Blue"));
    
    // Position 38: Luxury Tax
    spaces.push_back(std::make_unique<SpecialSpace>("Luxury Tax", 38, "LUXURY_TAX"));
    
    // Position 39: Boardwalk
    spaces.push_back(std::make_unique<Property>("Boardwalk", 39, 400, 50, 100, 200, 600, 1400, 1700, 2000, 200, "Dark Blue"));
}

Space* Board::getSpace(int position) const {
    if (position >= 0 && position < static_cast<int>(spaces.size())) {
        return spaces[position].get();
    }
    return nullptr;
}

void Board::displayBoard() const {
    std::cout << "\n" << std::string(80, '=') << "\n";
    std::cout << "                          MONOPOLY BOARD\n";
    std::cout << std::string(80, '=') << "\n\n";
    
    for (int i = 0; i < static_cast<int>(spaces.size()); ++i) {
        std::cout << std::setw(2) << i << ". " << spaces[i]->getDescription() << "\n";
    }
    
    std::cout << "\n" << std::string(80, '=') << "\n";
}

int Board::getColorGroupSize(const std::string& colorGroup) {
    if (colorGroup == "Brown" || colorGroup == "Dark Blue") {
        return 2;
    } else if (colorGroup == "Pink" || colorGroup == "Orange" || 
               colorGroup == "Red" || colorGroup == "Yellow" || 
               colorGroup == "Green" || colorGroup == "Light Blue") {
        return 3;
    }
    return 0;
}
