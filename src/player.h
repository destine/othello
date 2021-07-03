#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "action.h"
#include "board.h"

class Player {
    PlayerColor m_color;
public:
    Player(PlayerColor color): m_color(color) {}
    PlayerColor getColor() { return m_color; }
    virtual Action getNextAction(const Board& gameState) = 0;
    virtual ~Player() {}
};

class HumanPlayer : public Player {
public:
    HumanPlayer(PlayerColor color):
        Player(color) {
    }
    virtual Action getNextAction(const Board& gameState);
};

class RemotePlayer : public Player {
    int m_clientSocket;
public:
    RemotePlayer(PlayerColor color, int serverSocket);
    virtual Action getNextAction(const Board& gameState);
};

class NaivePlayer : public Player {
public:
    NaivePlayer(PlayerColor color):
        Player(color) {
    }
    virtual Action getNextAction(const Board& gameState);
};

class GreedyPlayer : public Player {
    int m_lookAhead;
public:
    GreedyPlayer(PlayerColor color, int lookAhead):
        Player(color), m_lookAhead(lookAhead) {
    }
    virtual Action getNextAction(const Board& gameState);
};

#endif
