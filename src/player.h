#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "action.h"
#include "board.h"

class Player {
    PlayerColor m_color;
public:
    Player(PlayerColor color): m_color(color) {}
    PlayerColor getColor() { return m_color; }
    virtual Action getNextAction(Board gameState) = 0;
};

class HumanPlayer : public Player {
public:
    HumanPlayer(PlayerColor color):
        Player(color) {
    }
    virtual Action getNextAction(Board gameState);
};

class NaivePlayer : public Player {
public:
    NaivePlayer(PlayerColor color):
        Player(color) {
    }
    virtual Action getNextAction(Board gameState);
};

class GreedyPlayer : public Player {
public:
    GreedyPlayer(PlayerColor color):
        Player(color) {
    }
    virtual Action getNextAction(Board gameState);
};

#endif
