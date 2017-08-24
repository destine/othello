#include "player.h"

#include <vector>
#include <cstdlib>

Action NaivePlayer::getNextAction(Board board) {
    std::vector<Action> actionList = board.getMovesFor(getColor());

    std::vector<Action>::iterator rand_elem = actionList.begin();
    std::advance(rand_elem, std::rand() % actionList.size());

    return *rand_elem;
}
