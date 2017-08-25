#include "player.h"
#include <iostream>

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

    return 11 * mobility + 23 * corners + board.count(color);
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
int getNextActionHelper(const Board& board, PlayerColor color, int depth) {
    // Retrieve the list of available actions for this board state.
    std::vector<Action> actionList = board.getMovesFor(color);
    // If we are forced to pass..
    if (actionList.empty() && depth > 0) {
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
            return -getNextActionHelper(board, reverse(color), depth - 1);
        }
    }

    if (depth == 0) {
        return heuristic(board, color);
    }

    std::vector<Action>::iterator it = actionList.begin();
    int bestReward = -BOUND;
    for (; it != actionList.end(); ++it) {
        Board testBoard = board.getCopy();
        testBoard.attempt(*it);
        int reward = -getNextActionHelper(testBoard, reverse(color), depth - 1);
        if (reward > bestReward) {
            bestReward = reward;
        }
    }
    return bestReward;
}

Action GreedyPlayer::getNextAction(const Board& board) {
    std::vector<Action> actionList = board.getMovesFor(getColor());
    std::vector<Action>::iterator it = actionList.begin();
    int current = board.count(getColor());
    int bestReward = -BOUND;
    std::vector<Action>::iterator bestAction = actionList.begin();
    for (; it != actionList.end(); ++it) {
        Board testBoard = board.getCopy();
        testBoard.attempt(*it);
        int reward = 0 - getNextActionHelper(testBoard,
                                             reverse(getColor()),
                                             m_iQ);
        if (reward > bestReward) {
            bestReward = reward;
            bestAction = it;
        }
    }
    std::cout << "Found action with expected value of: " << bestReward <<
                 std::endl;
    return *bestAction;
}
