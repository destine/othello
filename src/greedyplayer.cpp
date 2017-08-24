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

    return 11 * mobility + 23 * corners;
}

int heuristic(const Board board, PlayerColor color) {
    return heuristicHelper(board, color);
}

/* Estimates the value of a given game state BOARD for side COLOR at depth
 * DEPTH.
 */
int getNextActionHelper(const Board board, PlayerColor color, int depth = 3) {
    // If the game has ended..
    if (!board.existMovesFor(color) && !board.existMovesFor(reverse(color))) {
        if (board.count(color) > board.count(reverse(color))) {
            return BOUND - board.count(reverse(color)) - board.count(color);
        } else if (board.count(color) < board.count(reverse(color))) {
            return -BOUND;
        }
    }

    if (depth == 0) {
        return heuristic(board, color);
    }

    int current = board.count(color);
    std::vector<Action> actionList = board.getMovesFor(color);
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

Action GreedyPlayer::getNextAction(Board board) {
    std::vector<Action> actionList = board.getMovesFor(getColor());
    std::vector<Action>::iterator it = actionList.begin();
    int current = board.count(getColor());
    int bestReward = -BOUND;
    std::vector<Action>::iterator bestAction = actionList.begin();
    for (; it != actionList.end(); ++it) {
        Board testBoard = board.getCopy();
        testBoard.attempt(*it);
        int reward = 0 - getNextActionHelper(testBoard, reverse(getColor()));
        if (reward > bestReward) {
            bestReward = reward;
            bestAction = it;
        }
    }
    std::cout << "Found action with expected value of: " << bestReward <<
                 std::endl;
    return *bestAction;
}
