#include "othello.h"

#include <iostream>

void Othello::init() {
    if (m_player1->getColor() != DARK || m_player2->getColor() != LIGHT) {
        std::cerr << "Player configuration invalid! " << std::endl;
    }
}

void Othello::forward() {
    print();
    ++move_num;

    if (m_board.existMovesFor(nextToMove)) {
        Player* player = m_player1;
        if (nextToMove == LIGHT) {
            player = m_player2;
        }
        while (!m_board.attempt(player->getNextAction(m_board))) {
            std::cerr << "Invalid Move!" << std::endl;
        }
    } else {
        if (!m_board.existMovesFor(reverse(nextToMove))) {
            end();
            return;
        }
        std::cout << ">> PASS <<" << std::endl;
    }

    nextToMove = reverse(nextToMove);
}

void Othello::print() {
    m_board.print(std::cout);

    std::cout << "Move #" << move_num << " - ";

    if (nextToMove == DARK) {
        std::cout << "Dark to move.";
    }
    if (nextToMove == LIGHT) {
        std::cout << "Light to move.";
    }

    std::cout << std::endl;
}

bool Othello::over() {
    return m_isOver;
}

void Othello::end() {
    m_board.print(std::cout);

    std::cout << ">> GAME OVER <<" << std::endl;
    std::cout << "DARK:  " << m_board.count(DARK) << std::endl;
    std::cout << "LIGHT: " << m_board.count(LIGHT) << std::endl;

    m_isOver = true;
}

int Othello::getScore(PlayerColor color) {
    return m_board.count(color);
}
