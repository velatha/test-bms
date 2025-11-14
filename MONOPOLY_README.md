# 🎲 Monopoly Game - C++ Implementation

A complete, feature-rich implementation of the classic Monopoly board game in C++.

## 📚 Overview

This project provides a fully functional text-based Monopoly game that includes all standard game mechanics, property management, banking system, and turn-based gameplay for 2-8 players.

## ✨ Features

### Core Game Mechanics
- ✅ **Complete Game Board**: All 40 authentic Monopoly spaces
  - 28 Properties across 8 color groups
  - 4 Railroads
  - 2 Utilities
  - 6 Special spaces (GO, Jail, Free Parking, Go To Jail, Income Tax, Luxury Tax)

- ✅ **Player Management**: Support for 2-8 players
  - Individual player tracking
  - Money management ($1500 starting balance)
  - Property ownership tracking
  - Bankruptcy handling

- ✅ **Dice Rolling**: Two six-sided dice
  - Doubles detection
  - Triple doubles jail rule
  - Proper random number generation

- ✅ **Property System**:
  - Purchase mechanics
  - Rent calculation based on development
  - Color set bonuses
  - House and hotel building
  - Different rent levels (0-4 houses, hotel)

- ✅ **Railroad & Utility Mechanics**:
  - Railroad rent scales with number owned (1-4)
  - Utility rent based on dice roll × multiplier

- ✅ **Banking System**:
  - Money transactions
  - Property purchases
  - Rent payments
  - Building purchases
  - Tax payments

- ✅ **Game Rules**:
  - Pass GO to collect $200
  - Pay rent when landing on owned properties
  - Buy available properties
  - Build houses/hotels on complete color sets
  - Jail mechanics (pay $50, roll doubles, or use card)
  - Bankruptcy and elimination
  - Win condition (last player standing)

- ✅ **Turn-Based Gameplay**:
  - Sequential turn order
  - Multiple rolls on doubles
  - Interactive decision making
  - Real-time game state display

## 🏗️ Architecture

### Class Structure

```
Space (Abstract Base)
├── Property
├── Railroad
├── Utility
└── SpecialSpace

Player
├── Money management
├── Position tracking
├── Property ownership
└── Jail status

Board
└── 40 Space objects

Dice
└── Two six-sided dice

Game (Controller)
├── Game loop
├── Turn management
├── Player management
└── Rule enforcement
```

### Design Principles

- **Object-Oriented Design**: Clear class hierarchy with proper encapsulation
- **RAII**: Resource management through smart pointers
- **Modern C++**: Uses C++17 features including `std::unique_ptr`, `std::vector`, and STL algorithms
- **Separation of Concerns**: Each class has a single, well-defined responsibility
- **Polymorphism**: Virtual functions for space-specific behavior

## 📁 File Structure

```
monopoly/
├── main.cpp           # Entry point
├── Game.h/.cpp        # Game controller
├── Board.h/.cpp       # Board with all 40 spaces
├── Player.h/.cpp      # Player management
├── Space.h/.cpp       # Space classes (Property, Railroad, Utility, Special)
├── Dice.h/.cpp        # Dice mechanics
├── Makefile           # Build configuration
└── MONOPOLY_README.md # Documentation
```

## 🚀 Building and Running

### Prerequisites

- C++ compiler with C++17 support (g++ 7.0+ or clang++ 5.0+)
- Make utility

### Compilation

```bash
# Build the game
make

# Build and run in one command
make run

# Clean build artifacts
make clean
```

### Manual Compilation

```bash
g++ -std=c++17 -Wall -Wextra -O2 main.cpp Game.cpp Board.cpp Player.cpp Space.cpp Dice.cpp -o monopoly
```

### Running the Game

```bash
./monopoly
```

## 🎮 How to Play

### Starting the Game

1. Run the executable
2. Enter the number of players (2-8)
3. Enter names for each player
4. Game begins with Player 1

### During Your Turn

1. **Roll Dice**: Press Enter to roll two dice
2. **Movement**: Automatically move based on dice roll
3. **Landing Actions**:
   - **Unowned Property**: Choose to buy or pass
   - **Owned Property**: Pay rent to owner
   - **Your Property**: Option to build houses/hotels
   - **Special Spaces**: Automatic handling

### Game Actions

- **Buying Properties**: 
  - Land on unowned property
  - Choose 'y' to purchase if you have enough money

- **Building Houses**:
  - Own all properties in a color group
  - Land on your property
  - Choose to build when prompted
  - Max 4 houses per property

- **Building Hotels**:
  - Have 4 houses on a property
  - Own complete color group
  - Choose to build when prompted

- **Jail**:
  - Land on "Go To Jail" space
  - Roll doubles three times in a row
  - **Get Out**: Pay $50, roll doubles, or use Get Out of Jail card

### Winning

The game ends when only one player remains solvent. The winner is the player with the highest total assets (cash + property values).

## 📊 Property Details

### Brown (Mediterranean & Baltic)
- Price: $60
- Rent: $2-$4 base
- House Cost: $50

### Light Blue (Oriental, Vermont, Connecticut)
- Price: $100-$120
- Rent: $6-$8 base
- House Cost: $50

### Pink (St. Charles, States, Virginia)
- Price: $140-$160
- Rent: $10-$12 base
- House Cost: $100

### Orange (St. James, Tennessee, New York)
- Price: $180-$200
- Rent: $14-$16 base
- House Cost: $100

### Red (Kentucky, Indiana, Illinois)
- Price: $220-$240
- Rent: $18-$20 base
- House Cost: $150

### Yellow (Atlantic, Ventnor, Marvin Gardens)
- Price: $260-$280
- Rent: $22-$24 base
- House Cost: $150

### Green (Pacific, North Carolina, Pennsylvania)
- Price: $300-$320
- Rent: $26-$28 base
- House Cost: $200

### Dark Blue (Park Place, Boardwalk)
- Price: $350-$400
- Rent: $35-$50 base
- House Cost: $200

### Railroads (4 total)
- Price: $200 each
- Rent: $25 (1), $50 (2), $100 (3), $200 (4 owned)

### Utilities (2 total)
- Price: $150 each
- Rent: Dice roll × 4 (1 owned) or × 10 (2 owned)

## 🎯 Game Rules Summary

### Money Rules
- Start with $1500
- Collect $200 when passing GO
- Pay rent when landing on opponent's property
- Pay $200 Income Tax at position 4
- Pay $75 Luxury Tax at position 38

### Property Rules
- Can only build with complete color set
- Must build evenly across color group
- Houses must be sold before property
- Hotels replace 4 houses

### Jail Rules
- Sent to jail by:
  - Landing on "Go To Jail"
  - Rolling doubles three times in a row
- Get out by:
  - Paying $50 fine
  - Rolling doubles (3 attempts)
  - Using Get Out of Jail Free card
- Can still collect rent while in jail

### Bankruptcy
- Occurs when unable to pay debts
- All properties return to bank
- Player is eliminated

## 🔍 Code Examples

### Creating a Game

```cpp
#include "Game.h"

int main() {
    Game game;
    game.setupGame();  // Interactive setup
    game.start();      // Begin gameplay
    return 0;
}
```

### Property Management

```cpp
// Properties automatically handle rent calculation
int rent = property->getCurrentRent();

// Building houses (if conditions met)
if (property->canBuildHouse()) {
    property->buildHouse();
}

// Building hotels
if (property->canBuildHotel()) {
    property->buildHotel();
}
```

### Player Actions

```cpp
// Moving a player
player.move(diceTotal);  // Handles passing GO

// Managing money
player.addMoney(200);           // Collect money
bool success = player.subtractMoney(100);  // Pay money

// Property ownership
player.addProperty(property);
int colorGroupOwned = player.countPropertiesInColorGroup("Red");
```

## 🧪 Testing Considerations

The implementation includes:
- Input validation for player count and names
- Boundary checking for position calculations
- Null pointer checks for space access
- Money transaction validation
- Property ownership verification

## 🚀 Future Enhancements

Potential additions for extended functionality:
- Chance and Community Chest card implementations
- Trading system between players
- Mortgage system for properties
- Auction system for declined purchases
- Save/Load game functionality
- AI players
- GUI interface
- Network multiplayer

## 💡 Educational Value

This implementation demonstrates:
- Object-oriented programming principles
- Polymorphism and inheritance
- Resource management with smart pointers
- STL container usage
- Game loop design
- State management
- User input handling
- Code organization and modularity

## 📝 Notes

- This is a text-based implementation for educational purposes
- Chance and Community Chest cards are simplified in this version
- Some house rules are not implemented (e.g., Free Parking jackpot)
- The game follows standard Monopoly rules as closely as possible

## 🏆 Credits

Classic Monopoly game mechanics © Hasbro
C++ Implementation for educational purposes

## 📄 License

This is an educational implementation. Monopoly is a registered trademark of Hasbro.

---

**Enjoy your game of Monopoly! 🎲🏠🏨**
