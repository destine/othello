#ifndef __BOARD_H__
#define __BOARD_H__

#include "action.h"
#include "playercolor.h"

#include <bitset>
#include <vector>

#define BOARD_SIZE 8

class Board {
    std::bitset<128> board_array;
public:
    Board();
    bool attempt(Action action);
    bool existMovesFor(PlayerColor playerColor) const;
    void print(std::ostream& out) const;
    std::vector<Action> getMovesFor(PlayerColor playerColor) const;
    int count(PlayerColor color) const;
    Board getCopy() const;
    PlayerColor get(int r, int c) const;
private:
    bool set(int r, int c, PlayerColor color);
    bool isValid(Action action, PlayerColor playerColor) const;
    bool _isValidHelper(Action& action, int rowIncr, int colIncr) const;
    bool _attemptHelper(Action& action, int rowIncr, int colIncr);
};

#endif
