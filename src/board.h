#ifndef __BOARD_H__
#define __BOARD_H__

#include "action.h"
#include "playercolor.h"

#include <vector>

#define BOARD_SIZE 8

class Board {
    PlayerColor board_array[BOARD_SIZE * BOARD_SIZE];
public:
    Board();
    bool attempt(Action action);
    bool existMovesFor(PlayerColor playerColor) const;
    void print() const;
    std::vector<Action> getMovesFor(PlayerColor playerColor) const;
    int count(PlayerColor color) const;
    Board getCopy() const;
    PlayerColor get(int r, int c) const;
private:
    bool set(int r, int c, PlayerColor color);
    bool isValid(Action action, PlayerColor playerColor) const;
    bool _isValidHelper(Action& action, int rowIncr, int colIncr) const;
    void _attemptHelper(Action& action, int rowIncr, int colIncr);
};

#endif
