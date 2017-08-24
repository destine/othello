#include "board.h"

#include <iostream>

Board::Board() {
    // Prepare an empty board.
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            set(r, c, NONE);
        }
    }

    // Initialize board position for reversi match.
    set(3, 3, DARK);
    set(4, 4, DARK);
    set(3, 4, LIGHT);
    set(4, 3, LIGHT);
}

Board Board::getCopy() const {
    Board copy;
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            copy.set(r, c, get(r, c));
        }
    }
    return copy; 
}

int Board::count(PlayerColor color) const {
    int r_count;
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            if (get(r, c) == color) {
                ++r_count;
            } 
        }
    }
    return r_count;
}

bool isWithinBoard(int r, int c) {
    if (r < 0 || r >= BOARD_SIZE) {
        return false;
    }
    if (c < 0 || c >= BOARD_SIZE) {
        return false;
    }
    return true;
}

bool Board::isValid(Action action, PlayerColor color) const {
    // Check if square is empty.
    if (get(action.getRow(), action.getCol()) != NONE) {
        return false;
    }
   
    // Check if move is within the board.
    if (!isWithinBoard(action.getRow(), action.getCol())) {
        std::cerr << "Error! Cannot place pieces outside the board. \n";
        return false;
    }

    // Make sure that the player is placing a piece of his own color.
    if (action.getColor() != color) {
        std::cerr << "Error! Cannot place piece of opponent's color. \n";
        return false;
    }

    // Find directions with opponent pieces to turn over.
    bool isLeft      = _isValidHelper(action, -1, 0);
    bool isRight     = _isValidHelper(action, +1, 0);
    bool isUp        = _isValidHelper(action, 0, -1);
    bool isDown      = _isValidHelper(action, 0, +1);
    bool isUpLeft    = _isValidHelper(action, -1, -1);
    bool isUpRight   = _isValidHelper(action, +1, -1);
    bool isDownLeft  = _isValidHelper(action, -1, +1);
    bool isDownRight = _isValidHelper(action, +1, +1);

    if (isLeft || isRight || isUp || isDown ||
        isUpLeft || isUpRight || isDownLeft || isDownRight) {
        return true;
    } else {
        // No pieces can be turned over.
        return false;
    }
}

bool Board::attempt(Action action) {
    // Check if square is empty.
    if (get(action.getRow(), action.getCol()) != NONE) {
        return false;
    }
    // Check if move is within the board.
    if (!isWithinBoard(action.getRow(), action.getCol())) {
        return false;
    }

    // Find directions with opponent pieces to turn over.
    bool isLeft      = _isValidHelper(action, -1, 0);
    bool isRight     = _isValidHelper(action, 1, 0);
    bool isUp        = _isValidHelper(action, 0, -1);
    bool isDown      = _isValidHelper(action, 0, 1);
    bool isUpLeft    = _isValidHelper(action, -1, -1);
    bool isUpRight   = _isValidHelper(action, 1, -1);
    bool isDownLeft  = _isValidHelper(action, -1, 1);
    bool isDownRight = _isValidHelper(action, 1, 1);

    if (isLeft || isRight || isUp || isDown ||
        isUpLeft || isUpRight || isDownLeft || isDownRight) {
        // Set the piece.
        set(action.getRow(), action.getCol(), action.getColor());
        // Flip opponent pieces.
        if (isLeft) { _attemptHelper(action, -1, 0); }
        if (isRight) { _attemptHelper(action, 1, 0); }
        if (isUp) { _attemptHelper(action, 0, -1); }
        if (isDown) { _attemptHelper(action, 0, 1); }
        if (isUpLeft) { _attemptHelper(action, -1, -1); }
        if (isUpRight) { _attemptHelper(action, 1, -1); }
        if (isDownLeft) { _attemptHelper(action, -1, 1); }
        if (isDownRight) { _attemptHelper(action, 1, 1); }
        return true;
    } else {
        // No pieces can be turned over.
        return false;
    }
}

bool Board::existMovesFor(PlayerColor playerColor) const {
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            Action testAction(playerColor, r, c);
            if (isValid(testAction, playerColor)) {
                return true;
            }
        }
    }
    return false;
}

std::vector<Action> Board::getMovesFor(PlayerColor playerColor) const {
    std::vector<Action> myActions;
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            Action testAction(playerColor, r, c);
            if (isValid(testAction, playerColor)) {
                myActions.push_back(testAction);
            }
        }
    }
    return myActions;
}

void printCell(PlayerColor cellColor) {
    if (cellColor == DARK) {
        std::cout << " X ";
    } else if (cellColor == LIGHT) {
        std::cout << " O ";
    } else if (cellColor == NONE) {
        std::cout << " - ";
    } else {
        // TODO: Handle error.
        std::cout << "Board::printCell >> Invalid cell! \n";
    }
}

void Board::print() const {
    std::cout << "   ";
    for (int i = 1; i <= BOARD_SIZE; ++i) {
        std::cout << " " << i << " ";
    }
    std::cout << std::endl;

    for (int r = 0; r < BOARD_SIZE; ++r) {
        std::cout << " " << (char) ('a' + r) << " ";
        for (int c = 0; c < BOARD_SIZE; ++c) {
            printCell(get(r, c));
        }
        std::cout << std::endl;
    } 
}

bool Board::set(int r, int c, PlayerColor color) {
    if (isWithinBoard(r, c)) {
        board_array[BOARD_SIZE * r + c] = color;
        return true;
    } else {
        // TODO: Handle error.
        return false;
    }
}

PlayerColor Board::get(int r, int c) const {
    if (isWithinBoard(r, c)) {
        return board_array[BOARD_SIZE * r + c];
    } else {
        // TODO: Handle error.
        std::cerr << "Board::get >> Bad value! \n";
        return NONE;
    }
}

bool Board::_isValidHelper(Action& action, int rIncr, int cIncr) const {
    int r = action.getRow() + rIncr;
    int c = action.getCol() + cIncr;
    bool found = false;
    while (isWithinBoard(r, c)) {
        if (get(r, c) == reverse(action.getColor())) {
            found = true;
        } else if (get(r, c) == action.getColor()) {
            return found;
        } else {
            return false;
        }

        r += rIncr;
        c += cIncr;
    }

    // No matching piece of own color was found.
    return false;
}

void Board::_attemptHelper(Action& action, int rIncr, int cIncr) {
    int r = action.getRow() + rIncr;
    int c = action.getCol() + cIncr;
    while (isWithinBoard(r, c)) {
        if (get(r, c) == action.getColor()) {
            break;
        } else {
            set(r, c, action.getColor());
        }
        r += rIncr;
        c += cIncr; 
    }
}
