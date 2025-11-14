# 📁 Monopoly Game - Complete File Index

## 🎯 Main Game Files

### Source Code

#### Header Files (*.h)
| File | Lines | Purpose |
|------|-------|---------|
| `Space.h` | ~130 | Base Space class and derived classes (Property, Railroad, Utility, SpecialSpace) |
| `Player.h` | ~70 | Player management class with money, position, properties |
| `Dice.h` | ~20 | Dice rolling mechanics for two six-sided dice |
| `Board.h` | ~25 | Game board with all 40 spaces |
| `Game.h` | ~45 | Main game controller and game loop |

#### Implementation Files (*.cpp)
| File | Lines | Purpose |
|------|-------|---------|
| `Space.cpp` | ~175 | Implementation of all Space classes and their behaviors |
| `Player.cpp` | ~180 | Player state management, movement, property tracking |
| `Dice.cpp` | ~20 | Random dice rolling implementation |
| `Board.cpp` | ~190 | Board initialization with all 40 authentic Monopoly spaces |
| `Game.cpp` | ~470 | Game loop, turn management, user interaction |
| `main.cpp` | ~15 | Entry point for the game |

#### Test Files
| File | Lines | Purpose |
|------|-------|---------|
| `test_monopoly.cpp` | ~230 | Comprehensive test suite for all game components |

### Build System

| File | Purpose |
|------|---------|
| `Makefile` | Build configuration with targets: all, clean, run, test |

## 📚 Documentation Files

| File | Size | Purpose |
|------|------|---------|
| `README.md` | ~2.5 KB | Repository overview and quick reference |
| `MONOPOLY_README.md` | ~8.7 KB | Complete game documentation and features |
| `QUICKSTART.md` | ~3.6 KB | Quick start guide for players |
| `PROJECT_SUMMARY.md` | ~9.1 KB | Technical project summary and implementation details |
| `BOARD_LAYOUT.md` | ~6.5 KB | Visual board layout and property reference |
| `FILE_INDEX.md` | - | This file - complete file listing |

## 🔨 Generated Files (after build)

### Object Files (*.o)
- `main.o` - Compiled main entry point
- `Game.o` - Compiled game controller
- `Board.o` - Compiled board logic
- `Player.o` - Compiled player management
- `Space.o` - Compiled space classes
- `Dice.o` - Compiled dice mechanics

### Executables
- `monopoly` - Main game executable (~84 KB)
- `test_monopoly` - Test suite executable (~80 KB)

## 📊 File Statistics

### Code Metrics
```
Total Source Files:    11 files
Header Files:          5 files
Implementation Files:  6 files
Test Files:            1 file
Documentation Files:   6 files
Build Files:           1 file

Total Lines of Code:   ~1,400+ lines
Comments:              Extensive inline documentation
```

### Compilation
```
Compiler:      g++ (C++17)
Warnings:      0 (with -Wall -Wextra -Wpedantic)
Optimizations: -O2
Standard:      C++17
```

## 🎯 File Dependencies

### Main Program Flow
```
main.cpp
  └─> Game.h
       ├─> Player.h
       ├─> Board.h
       │    └─> Space.h
       │         └─> Player.h (forward declaration)
       └─> Dice.h
```

### Test Suite Flow
```
test_monopoly.cpp
  ├─> Game.h
  ├─> Board.h
  ├─> Player.h
  ├─> Dice.h
  └─> Space.h
```

## 📝 File Purposes by Category

### Core Game Logic
- `Game.h/cpp` - Orchestrates entire game flow
- `Board.h/cpp` - Manages 40 game spaces
- `Player.h/cpp` - Tracks individual player state

### Game Mechanics
- `Space.h/cpp` - Implements space behaviors
- `Dice.h/cpp` - Handles randomization

### Entry & Testing
- `main.cpp` - Program entry point
- `test_monopoly.cpp` - Validation suite

### Build & Documentation
- `Makefile` - Automated building
- `*.md` files - Comprehensive docs

## 🚀 Quick File Reference

### To Understand the Game
1. Start with `MONOPOLY_README.md` - Overview
2. Read `QUICKSTART.md` - How to play
3. Check `BOARD_LAYOUT.md` - Board reference

### To Understand the Code
1. Start with `main.cpp` - Entry point
2. Read `Game.h` - High-level flow
3. Study `Space.h` - Core abstractions
4. Review `Board.cpp` - See all 40 spaces

### To Build and Test
1. `Makefile` - See all build commands
2. Run `make test` - Run test suite
3. Run `make` - Build game
4. Run `./monopoly` - Play!

### To Extend the Game
1. `Space.h/cpp` - Add new space types
2. `Game.cpp` - Modify game rules
3. `Board.cpp` - Change board layout
4. `Player.h/cpp` - Add player features

## 📦 Complete File Listing

```
test-bms/
├── Source Code Files
│   ├── Space.h              (3.3 KB)
│   ├── Space.cpp            (5.9 KB)
│   ├── Player.h             (2.2 KB)
│   ├── Player.cpp           (5.1 KB)
│   ├── Dice.h               (478 B)
│   ├── Dice.cpp             (470 B)
│   ├── Board.h              (569 B)
│   ├── Board.cpp            (6.8 KB)
│   ├── Game.h               (1.3 KB)
│   ├── Game.cpp             (17 KB)
│   └── main.cpp             (321 B)
│
├── Test Files
│   └── test_monopoly.cpp    (8.0 KB)
│
├── Build System
│   └── Makefile             (788 B)
│
├── Documentation
│   ├── README.md            (2.5 KB)
│   ├── MONOPOLY_README.md   (8.7 KB)
│   ├── QUICKSTART.md        (3.6 KB)
│   ├── PROJECT_SUMMARY.md   (9.1 KB)
│   ├── BOARD_LAYOUT.md      (6.5 KB)
│   └── FILE_INDEX.md        (this file)
│
├── Generated (after build)
│   ├── *.o files            (object files)
│   ├── monopoly             (game executable)
│   └── test_monopoly        (test executable)
│
└── Other
    └── fibonacci.ts         (TypeScript example)
```

## 🎓 Learning Path

### Beginner Path
1. Read `QUICKSTART.md`
2. Run `make test` to see it work
3. Run `./monopoly` to play
4. Read `main.cpp` - simple entry point
5. Browse `BOARD_LAYOUT.md` for board reference

### Intermediate Path
1. Study `Game.h` - understand game flow
2. Read `Player.h` - see state management
3. Review `Space.h` - learn polymorphism
4. Check `test_monopoly.cpp` - see testing

### Advanced Path
1. Deep dive into `Game.cpp` - complex logic
2. Analyze `Board.cpp` - data initialization
3. Study `Space.cpp` - class hierarchy
4. Modify and extend the codebase

## 🔧 Maintenance Reference

### To Add a New Feature
1. Identify which class handles it
2. Update relevant .h file
3. Implement in .cpp file
4. Add test to test_monopoly.cpp
5. Update documentation

### To Fix a Bug
1. Run `make test` to identify issue
2. Check relevant .cpp file
3. Fix and recompile
4. Verify with `make test`
5. Test manually with `./monopoly`

### To Update Documentation
1. `MONOPOLY_README.md` - Features/rules
2. `QUICKSTART.md` - User instructions
3. `PROJECT_SUMMARY.md` - Technical details
4. `BOARD_LAYOUT.md` - Game board info

## 📈 Project Statistics

### Code Distribution
- Game Logic: ~470 lines (Game.cpp)
- Board Setup: ~190 lines (Board.cpp)
- Space Behavior: ~175 lines (Space.cpp)
- Player Management: ~180 lines (Player.cpp)
- Tests: ~230 lines (test_monopoly.cpp)

### Documentation
- Total docs: ~30 KB of markdown
- Code comments: Inline throughout
- Test coverage: 8 comprehensive tests

## ✅ Quality Indicators

- ✅ Zero compilation warnings
- ✅ All tests passing
- ✅ Modern C++ (C++17)
- ✅ Smart pointer usage
- ✅ RAII principles
- ✅ Clean architecture
- ✅ Comprehensive documentation

---

**This index provides a complete overview of all project files and their purposes.**

*Last updated: Implementation complete*
