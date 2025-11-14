#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>

class Property;
class Railroad;
class Utility;

/**
 * Represents a player in the Monopoly game
 */
class Player {
private:
    std::string name;
    int money;
    int position;
    bool inJail;
    int jailTurns;
    int getOutOfJailCards;
    bool bankrupt;
    std::vector<Property*> properties;
    std::vector<Railroad*> railroads;
    std::vector<Utility*> utilities;

public:
    Player(const std::string& name, int startingMoney = 1500);

    // Money management
    void addMoney(int amount);
    bool subtractMoney(int amount);
    int getMoney() const { return money; }
    
    // Position management
    void move(int spaces);
    void moveTo(int newPosition);
    int getPosition() const { return position; }
    
    // Property management
    void addProperty(Property* property);
    void addRailroad(Railroad* railroad);
    void addUtility(Utility* utility);
    void removeProperty(Property* property);
    void removeRailroad(Railroad* railroad);
    void removeUtility(Utility* utility);
    
    const std::vector<Property*>& getProperties() const { return properties; }
    const std::vector<Railroad*>& getRailroads() const { return railroads; }
    const std::vector<Utility*>& getUtilities() const { return utilities; }
    int countPropertiesInColorGroup(const std::string& colorGroup) const;
    int getPropertiesInColorGroupSize(const std::string& colorGroup) const;
    
    // Jail management
    void sendToJail();
    void releaseFromJail();
    bool isInJail() const { return inJail; }
    int getJailTurns() const { return jailTurns; }
    void incrementJailTurns() { jailTurns++; }
    void addGetOutOfJailCard() { getOutOfJailCards++; }
    bool hasGetOutOfJailCard() const { return getOutOfJailCards > 0; }
    void useGetOutOfJailCard() { if (getOutOfJailCards > 0) getOutOfJailCards--; }
    
    // Bankruptcy
    void declareBankruptcy();
    bool isBankrupt() const { return bankrupt; }
    
    // General
    std::string getName() const { return name; }
    int getTotalAssets() const;
    std::string getStatus() const;
};

#endif // PLAYER_H
