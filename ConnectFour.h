#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include <string>

class ConnectFour {
private:
    char board[6][7];  // 6 rows, 7 columns
    int moveCount;
    char currentPlayer;

public:
    ConnectFour();

    // Side-effect free functions (easy to test!)
    char getCell(int row, int col) const;
    char getCurrentPlayer() const;
    bool isFull() const;
    char getWinner() const;
    bool isGameOver() const;
    int getMoveCount() const;
    bool isValidMove(int col) const;

    // Functions with side effects
    bool makeMove(int col);
    void reset();

    // Display
    std::string toString() const;
};

#endif
