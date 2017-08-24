#ifndef __ACTION_H__
#define __ACTION_H__

#include "playercolor.h"

class Action {
    PlayerColor m_color;
    unsigned int m_row;
    unsigned int m_col;
public:
    Action(PlayerColor playerColor, int row, int col);
    unsigned int getRow();
    unsigned int getCol();
    PlayerColor getColor();
};

#endif
