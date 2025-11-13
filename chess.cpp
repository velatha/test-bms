#include "chess.h"
#include <algorithm>
#include <sstream>

// Pawn movement logic
std::vector<Position> Pawn::getPossibleMoves(const Position& pos) const {
    std::vector<Position> moves;
    int direction = (color == Color::WHITE) ? -1 : 1;
    
    // Forward move
    Position forward(pos.row + direction, pos.col);
    if (forward.isValid()) {
        moves.push_back(forward);
    }
    
    // Initial two-square move
    if (!hasMoved) {
        Position twoForward(pos.row + 2 * direction, pos.col);
        if (twoForward.isValid()) {
            moves.push_back(twoForward);
        }
    }
    
    // Diagonal captures
    Position diagLeft(pos.row + direction, pos.col - 1);
    Position diagRight(pos.row + direction, pos.col + 1);
    if (diagLeft.isValid()) moves.push_back(diagLeft);
    if (diagRight.isValid()) moves.push_back(diagRight);
    
    return moves;
}

// Rook movement logic
std::vector<Position> Rook::getPossibleMoves(const Position& pos) const {
    std::vector<Position> moves;
    
    // Horizontal and vertical directions
    int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    
    for (auto& dir : directions) {
        for (int i = 1; i < 8; i++) {
            Position newPos(pos.row + dir[0] * i, pos.col + dir[1] * i);
            if (newPos.isValid()) {
                moves.push_back(newPos);
            } else {
                break;
            }
        }
    }
    
    return moves;
}

// Knight movement logic
std::vector<Position> Knight::getPossibleMoves(const Position& pos) const {
    std::vector<Position> moves;
    
    int knightMoves[8][2] = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        {1, -2}, {1, 2}, {2, -1}, {2, 1}
    };
    
    for (auto& move : knightMoves) {
        Position newPos(pos.row + move[0], pos.col + move[1]);
        if (newPos.isValid()) {
            moves.push_back(newPos);
        }
    }
    
    return moves;
}

// Bishop movement logic
std::vector<Position> Bishop::getPossibleMoves(const Position& pos) const {
    std::vector<Position> moves;
    
    // Diagonal directions
    int directions[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    
    for (auto& dir : directions) {
        for (int i = 1; i < 8; i++) {
            Position newPos(pos.row + dir[0] * i, pos.col + dir[1] * i);
            if (newPos.isValid()) {
                moves.push_back(newPos);
            } else {
                break;
            }
        }
    }
    
    return moves;
}

// Queen movement logic (combination of Rook and Bishop)
std::vector<Position> Queen::getPossibleMoves(const Position& pos) const {
    std::vector<Position> moves;
    
    // All 8 directions
    int directions[8][2] = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };
    
    for (auto& dir : directions) {
        for (int i = 1; i < 8; i++) {
            Position newPos(pos.row + dir[0] * i, pos.col + dir[1] * i);
            if (newPos.isValid()) {
                moves.push_back(newPos);
            } else {
                break;
            }
        }
    }
    
    return moves;
}

// King movement logic
std::vector<Position> King::getPossibleMoves(const Position& pos) const {
    std::vector<Position> moves;
    
    // All adjacent squares
    int directions[8][2] = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };
    
    for (auto& dir : directions) {
        Position newPos(pos.row + dir[0], pos.col + dir[1]);
        if (newPos.isValid()) {
            moves.push_back(newPos);
        }
    }
    
    return moves;
}

// Board implementation
Board::Board() : currentTurn(Color::WHITE), enPassantTarget(-1, -1), 
                 gameOver(false), gameResult("") {
    initializeBoard();
}

void Board::initializeBoard() {
    // Initialize empty squares
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            squares[i][j] = nullptr;
        }
    }
    
    // Place black pieces
    squares[0][0] = std::make_unique<Rook>(Color::BLACK);
    squares[0][1] = std::make_unique<Knight>(Color::BLACK);
    squares[0][2] = std::make_unique<Bishop>(Color::BLACK);
    squares[0][3] = std::make_unique<Queen>(Color::BLACK);
    squares[0][4] = std::make_unique<King>(Color::BLACK);
    squares[0][5] = std::make_unique<Bishop>(Color::BLACK);
    squares[0][6] = std::make_unique<Knight>(Color::BLACK);
    squares[0][7] = std::make_unique<Rook>(Color::BLACK);
    
    for (int i = 0; i < 8; i++) {
        squares[1][i] = std::make_unique<Pawn>(Color::BLACK);
    }
    
    // Place white pieces
    squares[7][0] = std::make_unique<Rook>(Color::WHITE);
    squares[7][1] = std::make_unique<Knight>(Color::WHITE);
    squares[7][2] = std::make_unique<Bishop>(Color::WHITE);
    squares[7][3] = std::make_unique<Queen>(Color::WHITE);
    squares[7][4] = std::make_unique<King>(Color::WHITE);
    squares[7][5] = std::make_unique<Bishop>(Color::WHITE);
    squares[7][6] = std::make_unique<Knight>(Color::WHITE);
    squares[7][7] = std::make_unique<Rook>(Color::WHITE);
    
    for (int i = 0; i < 8; i++) {
        squares[6][i] = std::make_unique<Pawn>(Color::WHITE);
    }
}

void Board::display() const {
    std::cout << "\n  a b c d e f g h\n";
    for (int i = 0; i < 8; i++) {
        std::cout << 8 - i << " ";
        for (int j = 0; j < 8; j++) {
            if (squares[i][j]) {
                std::cout << squares[i][j]->getSymbol() << " ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << 8 - i << "\n";
    }
    std::cout << "  a b c d e f g h\n\n";
    
    std::cout << "Current turn: " 
              << (currentTurn == Color::WHITE ? "WHITE" : "BLACK") << "\n";
}

Piece* Board::getPiece(const Position& pos) const {
    if (!pos.isValid()) return nullptr;
    return squares[pos.row][pos.col].get();
}

bool Board::isPathClear(const Position& from, const Position& to) const {
    int rowDir = (to.row > from.row) ? 1 : (to.row < from.row) ? -1 : 0;
    int colDir = (to.col > from.col) ? 1 : (to.col < from.col) ? -1 : 0;
    
    Position current(from.row + rowDir, from.col + colDir);
    
    while (!(current == to)) {
        if (getPiece(current) != nullptr) {
            return false;
        }
        current.row += rowDir;
        current.col += colDir;
    }
    
    return true;
}

bool Board::isValidMove(const Move& move) const {
    if (!move.from.isValid() || !move.to.isValid()) {
        return false;
    }
    
    Piece* piece = getPiece(move.from);
    if (!piece || piece->getColor() != currentTurn) {
        return false;
    }
    
    Piece* target = getPiece(move.to);
    if (target && target->getColor() == piece->getColor()) {
        return false;
    }
    
    std::vector<Position> possibleMoves = piece->getPossibleMoves(move.from);
    bool moveFound = false;
    for (const auto& pos : possibleMoves) {
        if (pos == move.to) {
            moveFound = true;
            break;
        }
    }
    
    if (!moveFound) return false;
    
    // Check path clearance for sliding pieces
    PieceType type = piece->getType();
    if (type == PieceType::ROOK || type == PieceType::BISHOP || type == PieceType::QUEEN) {
        if (!isPathClear(move.from, move.to)) {
            return false;
        }
    }
    
    // Special pawn movement rules
    if (type == PieceType::PAWN) {
        int direction = (piece->getColor() == Color::WHITE) ? -1 : 1;
        
        // Forward move must be to empty square
        if (move.to.col == move.from.col) {
            if (target != nullptr) return false;
            
            // Two square move must have clear path
            if (abs(move.to.row - move.from.row) == 2) {
                Position intermediate(move.from.row + direction, move.from.col);
                if (getPiece(intermediate) != nullptr) return false;
            }
        } else {
            // Diagonal move must be a capture or en passant
            if (target == nullptr && !(move.to == enPassantTarget)) {
                return false;
            }
        }
    }
    
    return true;
}

Position Board::findKing(Color color) const {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece* piece = squares[i][j].get();
            if (piece && piece->getType() == PieceType::KING && 
                piece->getColor() == color) {
                return Position(i, j);
            }
        }
    }
    return Position(-1, -1);
}

bool Board::isInCheck(Color color) const {
    Position kingPos = findKing(color);
    if (!kingPos.isValid()) return false;
    
    // Check if any opponent piece can attack the king
    Color opponentColor = (color == Color::WHITE) ? Color::BLACK : Color::WHITE;
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece* piece = squares[i][j].get();
            if (piece && piece->getColor() == opponentColor) {
                Position pos(i, j);
                std::vector<Position> moves = piece->getPossibleMoves(pos);
                
                for (const auto& move : moves) {
                    if (move == kingPos) {
                        // Check if path is clear for sliding pieces
                        PieceType type = piece->getType();
                        if (type == PieceType::KNIGHT || type == PieceType::KING || 
                            type == PieceType::PAWN) {
                            return true;
                        } else if (isPathClear(pos, kingPos)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    
    return false;
}

bool Board::wouldBeInCheck(const Move& move, Color playerColor) {
    // Temporarily make the move
    std::unique_ptr<Piece> fromPiece = std::move(squares[move.from.row][move.from.col]);
    std::unique_ptr<Piece> toPiece = std::move(squares[move.to.row][move.to.col]);
    
    squares[move.to.row][move.to.col] = std::move(fromPiece);
    
    bool inCheck = isInCheck(playerColor);
    
    // Restore the board
    squares[move.from.row][move.from.col] = std::move(squares[move.to.row][move.to.col]);
    squares[move.to.row][move.to.col] = std::move(toPiece);
    
    return inCheck;
}

std::vector<Move> Board::getLegalMoves(const Position& pos) {
    std::vector<Move> legalMoves;
    Piece* piece = getPiece(pos);
    
    if (!piece || piece->getColor() != currentTurn) {
        return legalMoves;
    }
    
    std::vector<Position> possibleMoves = piece->getPossibleMoves(pos);
    
    for (const auto& to : possibleMoves) {
        Move move(pos, to);
        if (isValidMove(move) && !wouldBeInCheck(move, currentTurn)) {
            legalMoves.push_back(move);
        }
    }
    
    return legalMoves;
}

bool Board::makeMove(const Move& move) {
    if (!isValidMove(move)) {
        return false;
    }
    
    if (wouldBeInCheck(move, currentTurn)) {
        std::cout << "Invalid move: would put king in check!\n";
        return false;
    }
    
    Piece* piece = getPiece(move.from);
    
    // Handle en passant capture
    if (piece->getType() == PieceType::PAWN && move.to == enPassantTarget) {
        int captureRow = (piece->getColor() == Color::WHITE) ? move.to.row + 1 : move.to.row - 1;
        squares[captureRow][move.to.col] = nullptr;
    }
    
    // Set en passant target for next turn
    if (piece->getType() == PieceType::PAWN && 
        abs(move.to.row - move.from.row) == 2) {
        int targetRow = (move.from.row + move.to.row) / 2;
        enPassantTarget = Position(targetRow, move.from.col);
    } else {
        enPassantTarget = Position(-1, -1);
    }
    
    // Move the piece
    squares[move.to.row][move.to.col] = std::move(squares[move.from.row][move.from.col]);
    squares[move.to.row][move.to.col]->setMoved();
    
    // Switch turn
    currentTurn = (currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
    
    // Check for checkmate or stalemate
    if (isCheckmate(currentTurn)) {
        gameOver = true;
        gameResult = (currentTurn == Color::WHITE) ? "Black wins by checkmate!" 
                                                     : "White wins by checkmate!";
    } else if (isStalemate(currentTurn)) {
        gameOver = true;
        gameResult = "Draw by stalemate!";
    } else if (isInCheck(currentTurn)) {
        std::cout << "Check!\n";
    }
    
    return true;
}

bool Board::isCheckmate(Color color) {
    if (!isInCheck(color)) {
        return false;
    }
    
    // Check if any move can get out of check
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece* piece = squares[i][j].get();
            if (piece && piece->getColor() == color) {
                Position pos(i, j);
                std::vector<Move> legalMoves = getLegalMoves(pos);
                if (!legalMoves.empty()) {
                    return false;
                }
            }
        }
    }
    
    return true;
}

bool Board::isStalemate(Color color) {
    if (isInCheck(color)) {
        return false;
    }
    
    // Check if any legal move exists
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece* piece = squares[i][j].get();
            if (piece && piece->getColor() == color) {
                Position pos(i, j);
                std::vector<Move> legalMoves = getLegalMoves(pos);
                if (!legalMoves.empty()) {
                    return false;
                }
            }
        }
    }
    
    return true;
}

// ChessGame implementation
ChessGame::ChessGame() : running(false) {}

Position ChessGame::parsePosition(const std::string& pos) const {
    if (pos.length() != 2) {
        return Position(-1, -1);
    }
    
    int col = pos[0] - 'a';
    int row = 8 - (pos[1] - '0');
    
    Position result(row, col);
    return result.isValid() ? result : Position(-1, -1);
}

std::string ChessGame::positionToString(const Position& pos) const {
    if (!pos.isValid()) return "invalid";
    
    char col = 'a' + pos.col;
    char row = '8' - pos.row;
    return std::string(1, col) + std::string(1, row);
}

void ChessGame::printHelp() const {
    std::cout << "\n=== Chess Game Help ===\n";
    std::cout << "Commands:\n";
    std::cout << "  move <from> <to>  - Make a move (e.g., 'move e2 e4')\n";
    std::cout << "  show              - Display the board\n";
    std::cout << "  legal <pos>       - Show legal moves for a piece (e.g., 'legal e2')\n";
    std::cout << "  help              - Show this help message\n";
    std::cout << "  quit              - Exit the game\n";
    std::cout << "\nPositions are specified using algebraic notation (e.g., e2, d4)\n";
    std::cout << "====================\n\n";
}

void ChessGame::start() {
    running = true;
    std::cout << "=================================\n";
    std::cout << "   Welcome to Chess Game!\n";
    std::cout << "=================================\n";
    std::cout << "Type 'help' for available commands\n";
    
    board.display();
    
    while (running && !board.isGameOver()) {
        playTurn();
    }
    
    if (board.isGameOver()) {
        std::cout << "\n=================================\n";
        std::cout << "Game Over!\n";
        std::cout << board.getGameResult() << "\n";
        std::cout << "=================================\n";
    }
}

void ChessGame::playTurn() {
    std::string command;
    std::cout << "> ";
    std::getline(std::cin, command);
    
    std::istringstream iss(command);
    std::string action;
    iss >> action;
    
    if (action == "quit" || action == "exit") {
        running = false;
        std::cout << "Thanks for playing!\n";
    } else if (action == "help") {
        printHelp();
    } else if (action == "show") {
        board.display();
    } else if (action == "move") {
        std::string from, to;
        iss >> from >> to;
        
        Position fromPos = parsePosition(from);
        Position toPos = parsePosition(to);
        
        if (!fromPos.isValid() || !toPos.isValid()) {
            std::cout << "Invalid position format! Use algebraic notation (e.g., e2)\n";
            return;
        }
        
        Move move(fromPos, toPos);
        if (board.makeMove(move)) {
            std::cout << "Move successful: " << from << " to " << to << "\n";
            board.display();
        } else {
            std::cout << "Invalid move!\n";
        }
    } else if (action == "legal") {
        std::string pos;
        iss >> pos;
        
        Position position = parsePosition(pos);
        if (!position.isValid()) {
            std::cout << "Invalid position format!\n";
            return;
        }
        
        std::vector<Move> legalMoves = board.getLegalMoves(position);
        if (legalMoves.empty()) {
            std::cout << "No legal moves for this piece.\n";
        } else {
            std::cout << "Legal moves: ";
            for (const auto& move : legalMoves) {
                std::cout << positionToString(move.to) << " ";
            }
            std::cout << "\n";
        }
    } else if (!action.empty()) {
        std::cout << "Unknown command. Type 'help' for available commands.\n";
    }
}

