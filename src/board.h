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
    bool existMovesFor(PlayerColor playerColor);
    void print();
    std::vector<Action> getMovesFor(PlayerColor playerColor);
    int count(PlayerColor color);
    Board getCopy();
private:
    bool isValid(Action action, PlayerColor playerColor);
    bool set(int r, int c, PlayerColor color);
    PlayerColor get(int r, int c);
    bool _isValidHelper(Action& action, int rowIncrement, int colIncrement);
    void _attemptHelper(Action& action, int rowIncrement, int colIncrement);
};

#endif
