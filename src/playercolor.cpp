#include "playercolor.h"

PlayerColor reverse(PlayerColor color) {
    if (color == DARK) {
        return LIGHT;
    } else if (color == LIGHT) {
        return DARK;
    } else {
        return NONE;
    }
}
