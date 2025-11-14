#include "Dice.h"
#include <cstdlib>
#include <ctime>

Dice::Dice() : die1(0), die2(0), doubles(false) {
    // Seed random number generator
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }
}

std::pair<int, int> Dice::roll() {
    die1 = (std::rand() % 6) + 1;
    die2 = (std::rand() % 6) + 1;
    doubles = (die1 == die2);
    
    return std::make_pair(die1, die2);
}
