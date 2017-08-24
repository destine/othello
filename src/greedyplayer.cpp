#include "player.h"

int heuristic(Board board, PlayerColor color) {
    return board.count(color) - board.count(reverse(color));
}

/* Computes the minimum reward or cost for a given game tree depth level given
 * a certain action and assuming optimal play.
 */
int getBestActionHelper(Board board, PlayerColor color, int depth = 4) {
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
        int reward = getBestActionHelper(testBoard, reverse(color), depth - 1);
        if (reward > bestReward) {
            bestReward = reward;
        }
    }
    return bestReward;
}

Action getBestAction(Board board, PlayerColor color) {
    std::vector<Action> actionList = board.getMovesFor(color);
    std::vector<Action>::iterator it = actionList.begin();
    int current = board.count(color);
    int bestReward = 0;
    std::vector<Action>::iterator bestAction = actionList.begin();
    for (; it != actionList.end(); ++it) {
        Board testBoard = board.getCopy();
        testBoard.attempt(*it);        
        int reward = 0 - getBestActionHelper(testBoard, reverse(color));
        if (reward > bestReward) {
            bestReward = reward;
            bestAction = it;
        }
    }
    return *bestAction;
}

Action GreedyPlayer::getNextAction(Board board) {
    return getBestAction(board, getColor());
}
