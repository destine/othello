#include "player.h"
#include <limits>
#include <iostream>

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

    return 12 * mobility + 34 * corners + points;
}

int heuristic(const Board board, PlayerColor color) {
    return heuristicHelper(board, color);
}

/* Estimates the value of a given game state BOARD for side COLOR at depth
 * DEPTH.
 */
int getNextActionHelper(const Board board, PlayerColor color, int depth = 4) {
    // If the game has ended..
    if (!board.existMovesFor(color) && !board.existMovesFor(reverse(color))) {
        if (board.count(color) > board.count(reverse(color))) {
            return std::numeric_limits<int>::max() -
                   board.count(reverse(color));
        } else if (board.count(color) < board.count(reverse(color))) {
            return std::numeric_limits<int>::min();
        }
    }

    if (depth == 0) {
        return heuristic(board, color);
    }

    int current = board.count(color);
    std::vector<Action> actionList = board.getMovesFor(color);
    std::vector<Action>::iterator it = actionList.begin();
    int bestReward = std::numeric_limits<int>::min();
    for (; it != actionList.end(); ++it) {
        Board testBoard = board.getCopy();
        testBoard.attempt(*it);
        int reward = getNextActionHelper(testBoard, reverse(color), depth - 1);
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
    int bestReward = std::numeric_limits<int>::min();
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
