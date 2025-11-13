# Chess Program in C++

A comprehensive chess game implementation in C++ featuring complete board representation, piece movement logic, game rules enforcement, and interactive gameplay.

## Features

### Core Components
- **Board Representation**: 8x8 grid with proper piece placement and state management
- **Piece Movement Logic**: Accurate implementation for all six piece types:
  - Pawn (including en passant and promotion setup)
  - Rook (horizontal and vertical movement)
  - Knight (L-shaped movement)
  - Bishop (diagonal movement)
  - Queen (combination of rook and bishop)
  - King (one square in any direction)

### Game Rules Enforcement
- **Move Validation**: Ensures moves are legal according to chess rules
- **Check Detection**: Identifies when kings are in check
- **Checkmate Detection**: Determines game-ending positions
- **Stalemate Detection**: Identifies draw conditions
- **Path Clearance**: Validates clear paths for sliding pieces
- **Turn Management**: Alternates between white and black players

### Interactive Gameplay
- **Command Interface**: User-friendly text-based commands
- **Board Display**: Clear ASCII representation of the current position
- **Move Input**: Algebraic notation support (e.g., "e2 e4")
- **Legal Move Display**: Shows available moves for selected pieces
- **Game Status**: Real-time feedback on check, checkmate, and stalemate

## Build Instructions

```bash
# Compile the program
make

# Run the game
make run

# Clean build files
make clean
```

## How to Play

1. **Start the game**: Run `./chess` after compilation
2. **Make moves**: Use the format `move <from> <to>` (e.g., `move e2 e4`)
3. **View board**: Type `show` to display the current position
4. **Check legal moves**: Use `legal <position>` to see available moves
5. **Get help**: Type `help` for command reference
6. **Exit**: Type `quit` to end the game

## Game Commands

- `move <from> <to>` - Make a move using algebraic notation
- `show` - Display the current board state
- `legal <position>` - Show legal moves for a piece
- `help` - Display command help
- `quit` - Exit the game

## Technical Implementation

### Architecture
- **Object-Oriented Design**: Clean separation of concerns with classes for pieces, board, and game management
- **Polymorphism**: Base `Piece` class with derived classes for each piece type
- **Memory Management**: Smart pointers for automatic resource management
- **STL Integration**: Extensive use of standard library containers and algorithms

### Key Classes
- `Piece` (abstract base class)
- `Pawn`, `Rook`, `Knight`, `Bishop`, `Queen`, `King` (piece implementations)
- `Board` (game state management)
- `ChessGame` (user interface and game flow)
- `Position` and `Move` (data structures)

### Safety Features
- Input validation and error handling
- Bounds checking for all board operations
- Prevention of illegal moves that would result in check
- Robust state management to prevent invalid game states

This implementation provides a solid foundation for a chess game with room for future enhancements such as AI opponents, network play, or advanced features like castling and pawn promotion.
