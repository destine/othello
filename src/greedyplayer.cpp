#include "player.h"

int heuristic(const Board board, PlayerColor color) {
    return board.count(color) - board.count(reverse(color));
}

/* Estimates the value of a given game state BOARD for side COLOR at depth
 * DEPTH.
 */
int getNextActionHelper(const Board board, PlayerColor color, int depth = 3) {
    // Our base case. Our heuristic is simply the number of disks we have on
    // the board.
    if (depth == 0) {
        return heuristic(board, color);
    }

    int current = board.count(color);
    std::vector<Action> actionList = board.getMovesFor(color);
    std::vector<Action>::iterator it = actionList.begin();
    int bestReward = -64;
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
    int bestReward = 0;
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
    return *bestAction;
}
