#ifndef CHESS_H
#define CHESS_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Enum for piece colors
enum class Color {
    WHITE,
    BLACK,
    NONE
};

// Enum for piece types
enum class PieceType {
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING,
    EMPTY
};

// Structure to represent a position on the board
struct Position {
    int row;
    int col;
    
    Position(int r = 0, int c = 0) : row(r), col(c) {}
    
    bool isValid() const {
        return row >= 0 && row < 8 && col >= 0 && col < 8;
    }
    
    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }
};

// Structure to represent a move
struct Move {
    Position from;
    Position to;
    bool isCapture;
    bool isCastling;
    bool isEnPassant;
    
    Move(Position f, Position t) : from(f), to(t), isCapture(false), 
                                     isCastling(false), isEnPassant(false) {}
};

// Base class for chess pieces
class Piece {
protected:
    Color color;
    PieceType type;
    bool hasMoved;
    
public:
    Piece(Color c, PieceType t) : color(c), type(t), hasMoved(false) {}
    virtual ~Piece() {}
    
    Color getColor() const { return color; }
    PieceType getType() const { return type; }
    bool hasMovedBefore() const { return hasMoved; }
    void setMoved() { hasMoved = true; }
    
    virtual std::vector<Position> getPossibleMoves(const Position& pos) const = 0;
    virtual char getSymbol() const = 0;
    virtual std::unique_ptr<Piece> clone() const = 0;
};

// Forward declaration
class Board;

// Specific piece classes
class Pawn : public Piece {
public:
    Pawn(Color c) : Piece(c, PieceType::PAWN) {}
    std::vector<Position> getPossibleMoves(const Position& pos) const override;
    char getSymbol() const override { return (color == Color::WHITE) ? 'P' : 'p'; }
    std::unique_ptr<Piece> clone() const override { return std::make_unique<Pawn>(*this); }
};

class Rook : public Piece {
public:
    Rook(Color c) : Piece(c, PieceType::ROOK) {}
    std::vector<Position> getPossibleMoves(const Position& pos) const override;
    char getSymbol() const override { return (color == Color::WHITE) ? 'R' : 'r'; }
    std::unique_ptr<Piece> clone() const override { return std::make_unique<Rook>(*this); }
};

class Knight : public Piece {
public:
    Knight(Color c) : Piece(c, PieceType::KNIGHT) {}
    std::vector<Position> getPossibleMoves(const Position& pos) const override;
    char getSymbol() const override { return (color == Color::WHITE) ? 'N' : 'n'; }
    std::unique_ptr<Piece> clone() const override { return std::make_unique<Knight>(*this); }
};

class Bishop : public Piece {
public:
    Bishop(Color c) : Piece(c, PieceType::BISHOP) {}
    std::vector<Position> getPossibleMoves(const Position& pos) const override;
    char getSymbol() const override { return (color == Color::WHITE) ? 'B' : 'b'; }
    std::unique_ptr<Piece> clone() const override { return std::make_unique<Bishop>(*this); }
};

class Queen : public Piece {
public:
    Queen(Color c) : Piece(c, PieceType::QUEEN) {}
    std::vector<Position> getPossibleMoves(const Position& pos) const override;
    char getSymbol() const override { return (color == Color::WHITE) ? 'Q' : 'q'; }
    std::unique_ptr<Piece> clone() const override { return std::make_unique<Queen>(*this); }
};

class King : public Piece {
public:
    King(Color c) : Piece(c, PieceType::KING) {}
    std::vector<Position> getPossibleMoves(const Position& pos) const override;
    char getSymbol() const override { return (color == Color::WHITE) ? 'K' : 'k'; }
    std::unique_ptr<Piece> clone() const override { return std::make_unique<King>(*this); }
};

// Chess board class
class Board {
private:
    std::unique_ptr<Piece> squares[8][8];
    Color currentTurn;
    Position enPassantTarget;
    bool gameOver;
    std::string gameResult;
    
    void initializeBoard();
    bool isPathClear(const Position& from, const Position& to) const;
    bool wouldBeInCheck(const Move& move, Color playerColor);
    Position findKing(Color color) const;
    
public:
    Board();
    
    void display() const;
    bool isValidMove(const Move& move) const;
    bool makeMove(const Move& move);
    bool isInCheck(Color color) const;
    bool isCheckmate(Color color);
    bool isStalemate(Color color);
    std::vector<Move> getLegalMoves(const Position& pos);
    
    Piece* getPiece(const Position& pos) const;
    Color getCurrentTurn() const { return currentTurn; }
    bool isGameOver() const { return gameOver; }
    std::string getGameResult() const { return gameResult; }
    void setEnPassantTarget(const Position& pos) { enPassantTarget = pos; }
    Position getEnPassantTarget() const { return enPassantTarget; }
};

// Game class to manage the chess game
class ChessGame {
private:
    Board board;
    bool running;
    
    Position parsePosition(const std::string& pos) const;
    std::string positionToString(const Position& pos) const;
    void printHelp() const;
    
public:
    ChessGame();
    void start();
    void playTurn();
    bool isRunning() const { return running; }
};

#endif // CHESS_H
