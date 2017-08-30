#include "player.h"
#include <iostream>
#include <thread>
#include <mutex>

#define BOUND 1000000

/* Evaluates the game state BOARD from the point of view of player COLOR.
 */
int heuristicHelper(const Board board, PlayerColor color) {
    int mobility = board.getMovesFor(color).size();

    int corners = 0;
    if (board.get(0, 0) == color) {
        ++corners;
    }
    if (board.get(7, 0) == color) {
        ++corners;
    }
    if (board.get(0, 7) == color) {
        ++corners;
    }
    if (board.get(7, 7) == color) {
        ++corners;
    }

    int points = board.count(color);
    int stage = (points + board.count(reverse(color))) / 10;

    return 50 * mobility + 150 * corners + (stage - 2) * points;
}

int heuristic(const Board board, PlayerColor color) {
    if (!board.existMovesFor(color)) {
        if (!board.existMovesFor(reverse(color))) {
            if (board.count(color) > board.count(reverse(color))) {
                /* Win */
                return BOUND - 1;
            } else if (board.count(color) < board.count(reverse(color))) {
                /* Loss */
                return 1 - BOUND;
            }
            /* Draw */
            return 0;
        }
    }
    return heuristicHelper(board, color) -
           heuristicHelper(board, reverse(color));
}

/* Estimates the value of a given game state BOARD for side COLOR at depth
 * DEPTH.
 */
int getNextActionHelper(const Board& board,
                        PlayerColor color,
                        int depth,
                        int alpha,
                        int beta) {
    // Retrieve the list of available actions for this board state.
    std::vector<Action> actionList = board.getMovesFor(color);

    // Our base case.
    if (depth < 1) {
        return heuristic(board, color);
    }
    // If we are forced to pass..
    if (actionList.empty()) {
        // If the game has ended..
        if (!board.existMovesFor(reverse(color))) {
            if (board.count(color) > board.count(reverse(color))) {
                /* Win */
                return BOUND - 1;
            } else if (board.count(color) < board.count(reverse(color))) {
                /* Loss */
                return 1 - BOUND;
            }
            /* Draw */
            return 0;
        } else {
            return -getNextActionHelper(board,
                                        reverse(color),
                                        depth - 1,
                                        beta,
                                        alpha);
        }
    }

    std::vector<Action>::iterator it = actionList.begin();
    int bestReward = -BOUND;
    for (; it != actionList.end(); ++it) {
        Board testBoard = board.getCopy();
        testBoard.attempt(*it);
        int reward = -getNextActionHelper(testBoard,
                                          reverse(color),
                                          depth - 1,
                                          beta,
                                          alpha);
        if (reward > bestReward) {
            bestReward = reward;
        }
        // Alpha-Beta Pruning
        if (bestReward > alpha) {
            alpha = bestReward;
        }
        if (beta >= -alpha) {
            break;
        }
    }
    return bestReward;
}

std::mutex g_updateBestLock;
void _evaluateBranch(const Board& board,
                     Action action,
                     PlayerColor color,
                     int depth,
                     int& bestReward,
                     Action& bestAction) {
    Board testBoard = board.getCopy();
    testBoard.attempt(action);
    int reward = 0 - getNextActionHelper(testBoard,
                                         reverse(color),
                                         depth,
                                         -BOUND,
                                         -BOUND);

    std::lock_guard<std::mutex> lock(g_updateBestLock);
    if (reward > bestReward) {
        bestReward = reward;
        bestAction = action;
    }
}

Action GreedyPlayer::getNextAction(const Board& board) {
    std::vector<Action> actionList = board.getMovesFor(getColor());
    std::thread* threadList[actionList.size()];

    std::vector<Action>::iterator it = actionList.begin();
    int bestReward = -BOUND;
    Action bestAction = *actionList.begin();
    int threadNum = 0;
    for (; it != actionList.end(); ++it) {
        threadList[threadNum] = new std::thread(_evaluateBranch,
                                                std::ref(board),
                                                *it,
                                                getColor(),
                                                m_lookAhead,
                                                std::ref(bestReward),
                                                std::ref(bestAction));
        ++threadNum;
    }

    for (int i = 0; i < threadNum; ++i) {
        threadList[i]->join();
        delete threadList[i];
    }

    std::cout << "Found action with expected value of: " << bestReward <<
                 std::endl;
    return bestAction;
}
