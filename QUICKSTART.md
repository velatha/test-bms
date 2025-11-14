# 🎲 Monopoly Game - Quick Start Guide

## Installation

### Build the Game

```bash
make
```

### Run Tests

```bash
make test
```

### Clean Build Files

```bash
make clean
```

## Playing the Game

### Start a Game

```bash
./monopoly
```

or

```bash
make run
```

### Game Setup

1. Enter the number of players (2-8)
2. Enter names for each player
3. Press Enter to begin

### During Your Turn

1. **Press Enter** to roll the dice
2. Your token moves automatically
3. Choose actions based on where you land:
   - **Unowned Property**: Type `y` to buy, `n` to pass
   - **Your Property**: Option to build houses/hotels
   - **Opponent's Property**: Pay rent automatically
   - **Special Spaces**: Handled automatically

### Game Controls

- **Enter/Return**: Continue to next action
- **y/Y**: Yes/Accept
- **n/N**: No/Decline

### Example Game Flow

```
========================================
Turn 1 - Current Game State
========================================

Alice - Position: 0 | Money: $1500
  Properties: 0 | Railroads: 0 | Utilities: 0 | Total Assets: $1500

----------------------------------------
Alice's Turn (Turn #1)
----------------------------------------

Press Enter to roll dice...

🎲 Rolled: 3 + 4 = 7
Moved from position 0 to position 7

Landed on: Chance

Press Enter to continue to next player...
```

## Winning Strategy Tips

1. **Buy Properties Early**: Get a monopoly (color set) quickly
2. **Focus on Color Sets**: You need complete color sets to build
3. **Railroads Are Valuable**: Steady income, no development needed
4. **Manage Cash Flow**: Keep enough money to pay rent
5. **Build Strategically**: Orange and Red properties get landed on most
6. **Watch Opponents**: Track their properties and cash

## Common Scenarios

### Buying a Property

```
Landed on: Mediterranean Avenue
Mediterranean Avenue (Brown)
  Price: $60 | Rent: $2 | Available for purchase

Buy for $60? (y/n): y
✅ Purchased Mediterranean Avenue!
```

### Paying Rent

```
Landed on: Park Place
💸 Paying $35 rent to Bob
Current money: $1315
```

### Building a House

```
Landed on: Baltic Avenue
You own this property.
Build a house for $50? (y/n): y
🏠 Built a house on Baltic Avenue!
```

### Going to Jail

```
🚔 Go directly to Jail!

🔒 You are in Jail (Turn 1/3)
Options:
1. Try to roll doubles
2. Pay $50 fine
3. Use Get Out of Jail Free card

Enter choice: 2
✅ Paid $50 fine. You are free!
```

## Game Rules Summary

### Money
- Start with: **$1500**
- Pass GO: **+$200**
- Income Tax: **-$200**
- Luxury Tax: **-$75**
- Jail Fine: **-$50**

### Properties
- **Buy**: Pay listed price
- **Rent**: Pay owner when landing
- **Build**: Need complete color set
- **Houses**: Max 4 per property
- **Hotels**: Replace 4 houses

### Jail
Get in by:
- Landing on "Go To Jail"
- Rolling doubles 3 times

Get out by:
- Paying $50
- Rolling doubles (3 attempts)
- Using "Get Out of Jail Free" card

### Winning
Last player not bankrupt wins!

## Keyboard Tips

- Use **Enter** key to advance through the game
- Type **y** or **n** when prompted for decisions
- Game is case-insensitive (Y = y, N = n)

## Troubleshooting

### Game won't compile
```bash
make clean
make
```

### Need to see the full board
The board is displayed at the start of each turn. All 40 spaces are shown with their details.

### Want to quit mid-game
Press `Ctrl+C` to exit

## Files Overview

- `monopoly` - Main game executable
- `test_monopoly` - Test suite executable
- `MONOPOLY_README.md` - Full documentation
- `QUICKSTART.md` - This file

## Have Fun! 🎉

Enjoy your game of Monopoly! May the dice be ever in your favor! 🎲
