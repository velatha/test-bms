# test-bms

## Repository Contents

This repository contains multiple projects and examples:

### 🎲 Monopoly Game (C++)

A complete, feature-rich implementation of the classic Monopoly board game in C++.

**Quick Start:**
```bash
# Build and test
make test

# Build and run the game
make run
```

**Documentation:**
- [MONOPOLY_README.md](MONOPOLY_README.md) - Complete game documentation
- [QUICKSTART.md](QUICKSTART.md) - Quick start guide
- [PROJECT_SUMMARY.md](PROJECT_SUMMARY.md) - Technical project summary

**Features:**
- ✅ All 40 authentic Monopoly spaces
- ✅ 2-8 player support
- ✅ Complete property system with houses/hotels
- ✅ Dice mechanics with doubles
- ✅ Banking and money management
- ✅ Turn-based gameplay
- ✅ Win/lose conditions
- ✅ Comprehensive test suite

**Files:**
```
Monopoly Game Files:
├── main.cpp              - Entry point
├── Game.h/cpp            - Game controller
├── Board.h/cpp           - Game board (40 spaces)
├── Player.h/cpp          - Player management
├── Space.h/cpp           - Space classes
├── Dice.h/cpp            - Dice mechanics
├── test_monopoly.cpp     - Test suite
├── Makefile              - Build system
└── Documentation files
```

### 📊 Other Examples

- `fibonacci.ts` - TypeScript Fibonacci implementation

---

## Building the Monopoly Game

### Prerequisites
- C++ compiler with C++17 support (g++ 7.0+ or clang++ 5.0+)
- Make utility

### Commands

```bash
# Compile the game
make

# Run tests
make test

# Play the game
make run

# Clean build artifacts
make clean
```

### Manual Compilation

```bash
g++ -std=c++17 -Wall -Wextra -O2 main.cpp Game.cpp Board.cpp Player.cpp Space.cpp Dice.cpp -o monopoly
```

---

## Quick Play Guide

1. **Start the game**: `./monopoly`
2. **Enter number of players**: 2-8
3. **Enter player names**
4. **Play**: Press Enter to roll, type y/n for decisions
5. **Win**: Be the last player standing!

---

## Project Highlights

### Modern C++ Practices
- ✅ C++17 standard
- ✅ Zero compilation warnings
- ✅ Smart pointers (RAII)
- ✅ STL containers and algorithms
- ✅ Object-oriented design
- ✅ Polymorphism and inheritance

### Code Quality
- ✅ Clean architecture
- ✅ Separation of concerns
- ✅ Comprehensive documentation
- ✅ Full test coverage
- ✅ Professional code style

### Game Features
- ✅ Complete Monopoly rules
- ✅ Interactive gameplay
- ✅ Property management
- ✅ Building houses/hotels
- ✅ Jail mechanics
- ✅ Bankruptcy handling

---

## Repository Structure

```
test-bms/
├── Monopoly Game (C++)
│   ├── Source files (*.h, *.cpp)
│   ├── Test suite
│   ├── Makefile
│   └── Documentation
├── Other examples
│   └── fibonacci.ts
└── README.md (this file)
```

---

## License

Educational implementation for learning purposes.

Monopoly is a registered trademark of Hasbro.

---

**Enjoy the games! 🎲🎮**
