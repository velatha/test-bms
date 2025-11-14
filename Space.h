#ifndef SPACE_H
#define SPACE_H

#include <string>
#include <memory>

class Player;

/**
 * Base class representing a space on the Monopoly board
 */
class Space {
protected:
    std::string name;
    int position;

public:
    Space(const std::string& name, int position);
    virtual ~Space() = default;

    virtual void landOn(Player& player) = 0;
    virtual std::string getDescription() const;
    
    std::string getName() const { return name; }
    int getPosition() const { return position; }
};

/**
 * Property space that can be owned and developed
 */
class Property : public Space {
private:
    int price;
    int rent;
    int rentWithColorSet;
    int rentWithOneHouse;
    int rentWithTwoHouses;
    int rentWithThreeHouses;
    int rentWithFourHouses;
    int rentWithHotel;
    int houseCost;
    std::string colorGroup;
    Player* owner;
    int houses;
    bool hasHotel;

public:
    Property(const std::string& name, int position, int price, int rent,
             int rentColorSet, int rent1H, int rent2H, int rent3H, int rent4H,
             int rentHotel, int houseCost, const std::string& colorGroup);

    void landOn(Player& player) override;
    std::string getDescription() const override;
    
    bool canBePurchased() const { return owner == nullptr; }
    void setOwner(Player* newOwner) { owner = newOwner; }
    Player* getOwner() const { return owner; }
    int getPrice() const { return price; }
    int getCurrentRent() const;
    std::string getColorGroup() const { return colorGroup; }
    
    bool canBuildHouse() const;
    void buildHouse();
    bool canBuildHotel() const;
    void buildHotel();
    int getHouses() const { return houses; }
    bool getHasHotel() const { return hasHotel; }
    int getHouseCost() const { return houseCost; }
};

/**
 * Railroad space
 */
class Railroad : public Space {
private:
    int price;
    Player* owner;

public:
    Railroad(const std::string& name, int position);

    void landOn(Player& player) override;
    std::string getDescription() const override;
    
    bool canBePurchased() const { return owner == nullptr; }
    void setOwner(Player* newOwner) { owner = newOwner; }
    Player* getOwner() const { return owner; }
    int getPrice() const { return price; }
    int getRent(int railroadsOwned) const;
};

/**
 * Utility space (Electric Company, Water Works)
 */
class Utility : public Space {
private:
    int price;
    Player* owner;

public:
    Utility(const std::string& name, int position);

    void landOn(Player& player) override;
    std::string getDescription() const override;
    
    bool canBePurchased() const { return owner == nullptr; }
    void setOwner(Player* newOwner) { owner = newOwner; }
    Player* getOwner() const { return owner; }
    int getPrice() const { return price; }
    int getRent(int utilitiesOwned, int diceRoll) const;
};

/**
 * Special spaces (Go, Jail, Free Parking, Go To Jail, Tax, Chance, Community Chest)
 */
class SpecialSpace : public Space {
private:
    std::string type;

public:
    SpecialSpace(const std::string& name, int position, const std::string& type);

    void landOn(Player& player) override;
    std::string getDescription() const override;
    std::string getType() const { return type; }
};

#endif // SPACE_H
