#include <iostream>
#include <cstdlib>
#include <ctime>

#include "src/player.h"
#include "src/othello.h"

int match(Player* player1, Player* player2);

/* Parse command line options ARGV and set parameters accordingly.
 * Guarantees that all parameters will be initialized to a valid non-null
 * value.
 */
void parseCommandOptions(int argc, char** argv,
                         Player*& player1, Player*& player2,
                         int& rounds,
                         int& displayMode);

int main(int argc, char** argv) {
    // Signal to the user that the program has successfully executed.
    std::cout << "initializing.." << std::endl;
    // Set the seed for players relying on probabalistic algorithms.
    std::srand(time(NULL));

    Player* playerOne = NULL;
    Player* playerTwo = NULL;
    int SIM_RUNS = 1;
    int displayMode = 0;
    parseCommandOptions(argc, argv,
                        playerOne, playerTwo,
                        SIM_RUNS,
                        displayMode);
    if (playerOne == NULL || playerTwo == NULL) {
        std::cerr << "Something went horribly wrong! " << std::endl;
        exit(1);
    }

    bool isSwitched = false;
    int scoreDiff = 0;

    int playerOneWins = 0;
    int playerTwoWins = 0;
    for (int i = 0; i < SIM_RUNS; ++i) {
        if (isSwitched) {
            scoreDiff = match(playerTwo, playerOne);
        } else {
            scoreDiff = match(playerOne, playerTwo);
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
    Othello game(playerOne, playerTwo);
    game.init();

    while (!game.over()) {
        game.forward();
    }

    return game.getScore(playerOne->getColor()) -
           game.getScore(playerTwo->getColor());
}

void help() {
    std::cout << "Flags:" << std::endl;
    std::cout << " * -playerOne: Set player one to one of the following " <<
                 " player types.\n * * human\n * * greedy\n";
    std::cout << " * -playerTwo: Set player two to one of the above player " <<
                 "types.\n";
    std::cout << " * -rounds: Set the number of rounds to be played. " <<
                 " Followed by an integer representing the number of rounds.\n";
}

void parseCommandOptions(int argc, char** argv,
                         Player*& player1, Player*& player2,
                         int& rounds,
                         int& displayMode) {
    for (int i = 1; i < argc; ++i) {
        std::cout << i << ": " << argv[i] << std::endl;
    }
    player1 = new HumanPlayer(DARK);
    player2 = new HumanPlayer(LIGHT);
    rounds = 10;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-playerOne") == 0) {
            if (i + 1 < argc) {
                ++i;
                if (strcmp(argv[i], "human") == 0) {
                    delete player1;
                    player1 = new HumanPlayer(DARK);
                    std::cout << "Player One ... HumanPlayer" << std::endl;
                } else if (strcmp(argv[i], "greedy") == 0) {
                    delete player1;
                    player1 = new GreedyPlayer(DARK, 3);
                    std::cout << "Player One ... GreedyPlayer" << std::endl;
                } else {
                    std::cerr << "Error: Invalid player type! " << std::endl;
                    exit(1);
                }
            } else {
                std::cerr << "Error: Invalid command options! " << std::endl;
                exit(1);
            }
        } else if (strcmp(argv[i], "-playerTwo") == 0) {
            if (i + 1 < argc) {
                ++i;
                if (strcmp(argv[i], "human") == 0) {
                    delete player2;
                    player2 = new HumanPlayer(LIGHT);
                    std::cout << "Player Two ... HumanPlayer" << std::endl;
                } else if (strcmp(argv[i], "greedy") == 0) {
                    delete player2;
                    player2 = new GreedyPlayer(LIGHT, 3);
                    std::cout << "Player Two ... GreedyPlayer" << std::endl;
                } else {
                    std::cerr << "Error: Invalid player type! " << std::endl;
                    exit(1);
                }
            } else {
                std::cerr << "Error: Invalid command options! " << std::endl;
                exit(1);
            }
        } else if (strcmp(argv[i], "-rounds") == 0) {
            if (i + 1 < argc) {
                ++i;
                rounds = atoi(argv[i]);
            }
        } else {
            std::cerr << "Error: Invalid command options! " << std::endl;
            help();
            exit(1);
        }
    }
}
