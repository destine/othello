#include "playercolor.h"

PlayerColor reverse(PlayerColor color) {
    return LIGHT ^ color ^ DARK;
}
