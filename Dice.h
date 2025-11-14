#ifndef DICE_H
#define DICE_H

#include <utility>

/**
 * Represents a pair of six-sided dice
 */
class Dice {
private:
    int die1;
    int die2;
    bool doubles;

public:
    Dice();

    // Roll both dice
    std::pair<int, int> roll();
    
    // Get results of last roll
    int getDie1() const { return die1; }
    int getDie2() const { return die2; }
    int getTotal() const { return die1 + die2; }
    bool isDoubles() const { return doubles; }
};

#endif // DICE_H
