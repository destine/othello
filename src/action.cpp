#include "action.h"

Action::Action(PlayerColor color, int row, int col) {
    m_color = color;
    m_row = row;
    m_col = col;
}

unsigned int Action::getRow() {
    return m_row;
}

unsigned int Action::getCol() {
    return m_col;
}

PlayerColor Action::getColor() {
    return m_color;
}
