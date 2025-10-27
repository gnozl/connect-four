#include "ConnectFour.h"
#include <sstream>

ConnectFour::ConnectFour() : moveCount(0), currentPlayer('X') {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            board[i][j] = ' ';
        }
    }
}

char ConnectFour::getCell(int row, int col) const {
    if (row < 0 || row >= 6 || col < 0 || col >= 7) {
        return '\0';  // Invalid position
    }
    return board[row][col];
}

char ConnectFour::getCurrentPlayer() const {
    return currentPlayer;
}

bool ConnectFour::isFull() const {
    return moveCount == 42;  // 6 rows * 7 columns
}

char ConnectFour::getWinner() const {
    // Check horizontal
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 4; col++) {
            if (board[row][col] != ' ' &&
                board[row][col] == board[row][col+1] &&
                board[row][col] == board[row][col+2] &&
                board[row][col] == board[row][col+3]) {
                return board[row][col];
            }
        }
    }

    // Check vertical
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 7; col++) {
            if (board[row][col] != ' ' &&
                board[row][col] == board[row+1][col] &&
                board[row][col] == board[row+2][col] &&
                board[row][col] == board[row+3][col]) {
                return board[row][col];
            }
        }
    }

    // Check diagonal (down-right)
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 4; col++) {
            if (board[row][col] != ' ' &&
                board[row][col] == board[row+1][col+1] &&
                board[row][col] == board[row+2][col+2] &&
                board[row][col] == board[row+3][col+3]) {
                return board[row][col];
            }
        }
    }

    // Check diagonal (down-left)
    for (int row = 0; row < 3; row++) {
        for (int col = 3; col < 7; col++) {
            if (board[row][col] != ' ' &&
                board[row][col] == board[row+1][col-1] &&
                board[row][col] == board[row+2][col-2] &&
                board[row][col] == board[row+3][col-3]) {
                return board[row][col];
            }
        }
    }

    return ' ';  // No winner
}

bool ConnectFour::isGameOver() const {
    return getWinner() != ' ' || isFull();
}

int ConnectFour::getMoveCount() const {
    return moveCount;
}

bool ConnectFour::isValidMove(int col) const {
    if (col < 0 || col >= 7) {
        return false;
    }
    if (isGameOver()) {
        return false;
    }
    // Column is valid if top row is empty
    return board[0][col] == ' ';
}

bool ConnectFour::makeMove(int col) {
    if (!isValidMove(col)) {
        return false;
    }

    // Find the lowest empty row in this column
    for (int row = 5; row >= 0; row--) {
        if (board[row][col] == ' ') {
            board[row][col] = currentPlayer;
            moveCount++;
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            return true;
        }
    }

    return false;  // Should never happen if isValidMove passed
}

void ConnectFour::reset() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            board[i][j] = ' ';
        }
    }
    currentPlayer = 'X';
    moveCount = 0;
}

std::string ConnectFour::toString() const {
    std::ostringstream oss;
    oss << " 0 1 2 3 4 5 6 \n";
    for (int i = 0; i < 6; i++) {
        oss << "|";
        for (int j = 0; j < 7; j++) {
            oss << board[i][j] << "|";
        }
        oss << "\n";
    }
    oss << "---------------\n";
    return oss.str();
}
