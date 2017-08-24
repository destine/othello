#ifndef __PLAYERCOLOR_H__
#define __PLAYERCOLOR_H__

#include <bitset>

/* PlayerColor is represented as a two bit bitset, with the left bit
 * representing the presence or lack of a piece, and the right bit
 * representing the parity of the piece if the left bit is set.
 */
typedef std::bitset<2> PlayerColor;

/* Represented as 0b00. */
const PlayerColor NONE = PlayerColor(0);
/* Represented as 0b01. */
const PlayerColor LIGHT = PlayerColor(1);
/* Represented as 0b11. */
const PlayerColor DARK = PlayerColor(3);

PlayerColor reverse(PlayerColor color);

#endif
