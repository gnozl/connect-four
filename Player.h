#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <functional>

// Forward declaration
class ConnectFour;

// Strategy function type: takes game state, returns column (0-6)
using Strategy = std::function<int(const ConnectFour&, char)>;

class Player {
private:
    std::string name;
    Strategy strategy;
    int wins;
    int losses;
    int ties;

public:
    Player(const std::string& playerName, Strategy strat);

    // Get the player's next move using their strategy
    int getMove(const ConnectFour& game, char symbol) const;

    // Getters
    std::string getName() const;
    int getWins() const;
    int getLosses() const;
    int getTies() const;

    // Record game results
    void recordWin();
    void recordLoss();
    void recordTie();

    // Reset stats
    void resetStats();
};

#endif
