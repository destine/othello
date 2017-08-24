#include <iostream>
#include <cstdlib>
#include <ctime>

#include "src/player.h"
#include "src/reversi.h"

int match(Player* player1, Player* player2);

int main(int argc, char** argv) {
    // Signal to the user that the program has successfully executed.
    std::cout << "initializing.." << std::endl;
    // Set the seed for players relying on probabalistic algorithms.
    std::srand(time(NULL));

    GreedyPlayer playerOne(DARK);
    NaivePlayer playerTwo(LIGHT);
    bool isSwitched = false;
    int scoreDiff = 0;

    int playerOneWins = 0;
    int playerTwoWins = 0;
    const int SIM_RUNS = 100;
    for (int i = 0; i < SIM_RUNS; ++i) {
        if (isSwitched) {
            scoreDiff = match(&playerTwo, &playerOne);
        } else {
            scoreDiff = match(&playerOne, &playerTwo);
        }

        if (scoreDiff > 0) {
            if (isSwitched) {
                ++playerTwoWins;
            } else {
                ++playerOneWins;
            }
        } else if (scoreDiff < 0) {
            if (isSwitched) {
                ++playerOneWins;
            } else {
                ++playerTwoWins;
            }
        }
    }

    float playerOneWinRate = (playerOneWins * 100.0f) / SIM_RUNS;
    float playerTwoWinRate = (playerTwoWins * 100.0f) / SIM_RUNS;

    std::cout << "Player One - " << playerOneWins << " wins - "
              << playerOneWinRate << "% win rate" << std::endl;
    std::cout << "Player Two - " << playerTwoWins << " wins - "
              << playerTwoWinRate << "% win rate" << std::endl;
}

int match(Player* playerOne, Player* playerTwo) {
    Reversi game(*playerOne, *playerTwo);
    game.init();

    while (!game.over()) {
        game.forward();
    }

    return game.getScore(playerOne->getColor()) -
           game.getScore(playerTwo->getColor());
}
