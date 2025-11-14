#include "Player.h"
#include "Space.h"
#include "Board.h"
#include <algorithm>
#include <sstream>

Player::Player(const std::string& name, int startingMoney)
    : name(name), money(startingMoney), position(0), inJail(false),
      jailTurns(0), getOutOfJailCards(0), bankrupt(false) {}

// ============================================================================
// Money Management
// ============================================================================

void Player::addMoney(int amount) {
    if (amount > 0) {
        money += amount;
    }
}

bool Player::subtractMoney(int amount) {
    if (amount <= money) {
        money -= amount;
        return true;
    }
    return false;
}

// ============================================================================
// Position Management
// ============================================================================

void Player::move(int spaces) {
    int oldPosition = position;
    position = (position + spaces) % 40;
    
    // Check if passed GO (position wrapped around)
    if (position < oldPosition) {
        addMoney(200);
    }
}

void Player::moveTo(int newPosition) {
    if (newPosition >= 0 && newPosition < 40) {
        // Check if passed GO
        if (newPosition < position) {
            addMoney(200);
        }
        position = newPosition;
    }
}

// ============================================================================
// Property Management
// ============================================================================

void Player::addProperty(Property* property) {
    if (property) {
        properties.push_back(property);
        property->setOwner(this);
    }
}

void Player::addRailroad(Railroad* railroad) {
    if (railroad) {
        railroads.push_back(railroad);
        railroad->setOwner(this);
    }
}

void Player::addUtility(Utility* utility) {
    if (utility) {
        utilities.push_back(utility);
        utility->setOwner(this);
    }
}

void Player::removeProperty(Property* property) {
    auto it = std::find(properties.begin(), properties.end(), property);
    if (it != properties.end()) {
        properties.erase(it);
        property->setOwner(nullptr);
    }
}

void Player::removeRailroad(Railroad* railroad) {
    auto it = std::find(railroads.begin(), railroads.end(), railroad);
    if (it != railroads.end()) {
        railroads.erase(it);
        railroad->setOwner(nullptr);
    }
}

void Player::removeUtility(Utility* utility) {
    auto it = std::find(utilities.begin(), utilities.end(), utility);
    if (it != utilities.end()) {
        utilities.erase(it);
        utility->setOwner(nullptr);
    }
}

int Player::countPropertiesInColorGroup(const std::string& colorGroup) const {
    int count = 0;
    for (const auto& prop : properties) {
        if (prop->getColorGroup() == colorGroup) {
            count++;
        }
    }
    return count;
}

int Player::getPropertiesInColorGroupSize(const std::string& colorGroup) const {
    return Board::getColorGroupSize(colorGroup);
}

// ============================================================================
// Jail Management
// ============================================================================

void Player::sendToJail() {
    inJail = true;
    jailTurns = 0;
    position = 10; // Jail position
}

void Player::releaseFromJail() {
    inJail = false;
    jailTurns = 0;
}

// ============================================================================
// Bankruptcy
// ============================================================================

void Player::declareBankruptcy() {
    bankrupt = true;
    
    // Return all properties to bank
    for (auto* prop : properties) {
        prop->setOwner(nullptr);
    }
    for (auto* rail : railroads) {
        rail->setOwner(nullptr);
    }
    for (auto* util : utilities) {
        util->setOwner(nullptr);
    }
    
    properties.clear();
    railroads.clear();
    utilities.clear();
}

// ============================================================================
// General Methods
// ============================================================================

int Player::getTotalAssets() const {
    int total = money;
    
    for (const auto* prop : properties) {
        total += prop->getPrice();
        total += prop->getHouses() * prop->getHouseCost();
        if (prop->getHasHotel()) {
            total += prop->getHouseCost(); // Hotel cost
        }
    }
    
    for (const auto* rail : railroads) {
        total += rail->getPrice();
    }
    
    for (const auto* util : utilities) {
        total += util->getPrice();
    }
    
    return total;
}

std::string Player::getStatus() const {
    std::ostringstream oss;
    oss << name << " - Position: " << position << " | Money: $" << money;
    
    if (inJail) {
        oss << " [IN JAIL - Turn " << jailTurns << "/3]";
    }
    
    if (bankrupt) {
        oss << " [BANKRUPT]";
    }
    
    oss << "\n  Properties: " << properties.size()
        << " | Railroads: " << railroads.size()
        << " | Utilities: " << utilities.size()
        << " | Total Assets: $" << getTotalAssets();
    
    return oss.str();
}
