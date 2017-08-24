#include "player.h"

#include <iostream>

Action
HumanPlayer::getNextAction(Board board) {
    char input_buffer[3];
    std::cin.getline(input_buffer, 100);
    Action action(getColor(), input_buffer[0] - 'a', input_buffer[1] - '1');
    return action;
}
