#ifndef __REVERSI_H__
#define __REVERSI_H__

#include "player.h"
#include "board.h"

class Othello {
    Player* m_player1;
    Player* m_player2;
    Board m_board;
    int move_num = 1;
    PlayerColor nextToMove = DARK;
    bool m_isOver = false;
public:
    Othello(Player* player1, Player* player2):
        m_player1(player1), m_player2(player2) {
    }
    void init();
    void forward();
    bool over();
    int getScore(PlayerColor color);
private:
    void print();
    void end();
};

#endif
