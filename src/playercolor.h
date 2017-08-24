#ifndef __PLAYERCOLOR_H__
#define __PLAYERCOLOR_H__

/*
#include <algorithm>

class PlayerColor {
    const unsigned short _value;
public:
    friend inline bool operator==(const PlayerColor&, const PlayerColor&);
    friend inline bool operator!=(const PlayerColor&, const PlayerColor&);
    PlayerColor(): _value(0) {}
    PlayerColor(unsigned short value): _value(value) {}
    PlayerColor(const PlayerColor& obj): _value(obj._value) {}
    PlayerColor& operator=(const PlayerColor& obj) {
        std::swap(_value, obj._value);
        return *this;
    }
};

extern const PlayerColor NONE;
extern const PlayerColor DARK;
extern const PlayerColor LIGHT;

inline bool operator==(const PlayerColor& lhs, const PlayerColor& rhs) {
    return &lhs == &rhs;
}
inline bool operator!=(const PlayerColor& lhs, const PlayerColor& rhs) {
    return &lhs != &rhs;
}
*/

typedef unsigned short PlayerColor;

const PlayerColor NONE = 0;
const PlayerColor DARK = 1;
const PlayerColor LIGHT = 2;

PlayerColor reverse(PlayerColor color);

#endif
