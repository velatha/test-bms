#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "Space.h"

/**
 * Represents the Monopoly game board with all 40 spaces
 */
class Board {
private:
    std::vector<std::unique_ptr<Space>> spaces;
    
    void initializeSpaces();

public:
    Board();
    
    Space* getSpace(int position) const;
    int getTotalSpaces() const { return static_cast<int>(spaces.size()); }
    void displayBoard() const;
    
    // Helper methods for color group sizes
    static int getColorGroupSize(const std::string& colorGroup);
};

#endif // BOARD_H
