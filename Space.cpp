#include "Space.h"
#include "Player.h"
#include <sstream>

// ============================================================================
// Space Base Class
// ============================================================================

Space::Space(const std::string& name, int position)
    : name(name), position(position) {}

std::string Space::getDescription() const {
    return name + " (Position: " + std::to_string(position) + ")";
}

// ============================================================================
// Property Class
// ============================================================================

Property::Property(const std::string& name, int position, int price, int rent,
                   int rentColorSet, int rent1H, int rent2H, int rent3H, int rent4H,
                   int rentHotel, int houseCost, const std::string& colorGroup)
    : Space(name, position), price(price), rent(rent),
      rentWithColorSet(rentColorSet), rentWithOneHouse(rent1H),
      rentWithTwoHouses(rent2H), rentWithThreeHouses(rent3H),
      rentWithFourHouses(rent4H), rentWithHotel(rentHotel),
      houseCost(houseCost), colorGroup(colorGroup),
      owner(nullptr), houses(0), hasHotel(false) {}

void Property::landOn([[maybe_unused]] Player& player) {
    // Landing logic is handled by Game class
}

std::string Property::getDescription() const {
    std::ostringstream oss;
    oss << name << " (" << colorGroup << ")\n";
    oss << "  Price: $" << price << " | Rent: $" << rent;
    if (owner) {
        oss << " | Owner: " << owner->getName();
        if (hasHotel) {
            oss << " [HOTEL]";
        } else if (houses > 0) {
            oss << " [" << houses << " house(s)]";
        }
    } else {
        oss << " | Available for purchase";
    }
    return oss.str();
}

int Property::getCurrentRent() const {
    if (!owner) return 0;
    
    if (hasHotel) {
        return rentWithHotel;
    }
    
    switch (houses) {
        case 0: {
            // Check if owner has color set
            int owned = owner->countPropertiesInColorGroup(colorGroup);
            int total = owner->getPropertiesInColorGroupSize(colorGroup);
            return (owned == total) ? rentWithColorSet : rent;
        }
        case 1: return rentWithOneHouse;
        case 2: return rentWithTwoHouses;
        case 3: return rentWithThreeHouses;
        case 4: return rentWithFourHouses;
        default: return rent;
    }
}

bool Property::canBuildHouse() const {
    if (!owner || houses >= 4 || hasHotel) return false;
    
    // Check if owner has complete color set
    int owned = owner->countPropertiesInColorGroup(colorGroup);
    int total = owner->getPropertiesInColorGroupSize(colorGroup);
    
    return owned == total;
}

void Property::buildHouse() {
    if (canBuildHouse()) {
        houses++;
    }
}

bool Property::canBuildHotel() const {
    if (!owner || houses != 4 || hasHotel) return false;
    
    int owned = owner->countPropertiesInColorGroup(colorGroup);
    int total = owner->getPropertiesInColorGroupSize(colorGroup);
    
    return owned == total;
}

void Property::buildHotel() {
    if (canBuildHotel()) {
        houses = 0;
        hasHotel = true;
    }
}

// ============================================================================
// Railroad Class
// ============================================================================

Railroad::Railroad(const std::string& name, int position)
    : Space(name, position), price(200), owner(nullptr) {}

void Railroad::landOn([[maybe_unused]] Player& player) {
    // Landing logic is handled by Game class
}

std::string Railroad::getDescription() const {
    std::ostringstream oss;
    oss << name << " [Railroad]\n";
    oss << "  Price: $" << price;
    if (owner) {
        oss << " | Owner: " << owner->getName();
    } else {
        oss << " | Available for purchase";
    }
    return oss.str();
}

int Railroad::getRent(int railroadsOwned) const {
    switch (railroadsOwned) {
        case 1: return 25;
        case 2: return 50;
        case 3: return 100;
        case 4: return 200;
        default: return 0;
    }
}

// ============================================================================
// Utility Class
// ============================================================================

Utility::Utility(const std::string& name, int position)
    : Space(name, position), price(150), owner(nullptr) {}

void Utility::landOn([[maybe_unused]] Player& player) {
    // Landing logic is handled by Game class
}

std::string Utility::getDescription() const {
    std::ostringstream oss;
    oss << name << " [Utility]\n";
    oss << "  Price: $" << price;
    if (owner) {
        oss << " | Owner: " << owner->getName();
    } else {
        oss << " | Available for purchase";
    }
    return oss.str();
}

int Utility::getRent(int utilitiesOwned, int diceRoll) const {
    int multiplier = (utilitiesOwned == 2) ? 10 : 4;
    return diceRoll * multiplier;
}

// ============================================================================
// SpecialSpace Class
// ============================================================================

SpecialSpace::SpecialSpace(const std::string& name, int position, const std::string& type)
    : Space(name, position), type(type) {}

void SpecialSpace::landOn(Player& player) {
    if (type == "GO") {
        // Already collected $200 for passing Go
    } else if (type == "GO_TO_JAIL") {
        player.sendToJail();
    } else if (type == "INCOME_TAX") {
        player.subtractMoney(200);
    } else if (type == "LUXURY_TAX") {
        player.subtractMoney(75);
    }
    // Other special spaces (Chance, Community Chest, Free Parking) 
    // are simplified in this implementation
}

std::string SpecialSpace::getDescription() const {
    std::ostringstream oss;
    oss << name;
    if (type == "INCOME_TAX") {
        oss << " - Pay $200";
    } else if (type == "LUXURY_TAX") {
        oss << " - Pay $75";
    }
    return oss.str();
}
