#include "ConnectFour.h"
#include "Player.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>

// Play a single game between two players
void playGame(Player& player1, Player& player2, ConnectFour& game, bool verbose = true) {
    game.reset();

    while (!game.isGameOver()) {
        Player& currentPlayer = (game.getCurrentPlayer() == 'X') ? player1 : player2;

        int move = currentPlayer.getMove(game, game.getCurrentPlayer());
        game.makeMove(move);

        if (verbose) {
            std::cout << game.toString();
        }
    }

    char winner = game.getWinner();
    if (winner == 'X') {
        player1.recordWin();
        player2.recordLoss();
        if (verbose) {
            std::cout << player1.getName() << " wins!\n";
        }
    } else if (winner == 'O') {
        player2.recordWin();
        player1.recordLoss();
        if (verbose) {
            std::cout << player2.getName() << " wins!\n";
        }
    } else {
        player1.recordTie();
        player2.recordTie();
        if (verbose) {
            std::cout << "It's a tie!\n";
        }
    }
}

// Run a round-robin tournament between all strategies
void runTournament(std::vector<Player>& players, int gamesPerMatchup) {
    ConnectFour game;

    std::cout << "\n=== CONNECT FOUR TOURNAMENT ===\n";
    std::cout << "Running round-robin with " << players.size()
              << " players, " << gamesPerMatchup << " games per matchup...\n\n";

    // Play round-robin tournament (each player plays every other player)
    for (size_t i = 0; i < players.size(); i++) {
        for (size_t j = i + 1; j < players.size(); j++) {
            std::cout << "Matchup: " << players[i].getName()
                      << " vs " << players[j].getName() << std::endl;

            for (int g = 0; g < gamesPerMatchup; g++) {
                // Alternate who goes first to be fair
                if (g % 2 == 0) {
                    playGame(players[i], players[j], game, false);
                } else {
                    playGame(players[j], players[i], game, false);
                }
            }
        }
    }

    // Display results sorted by wins
    std::cout << "\n=== TOURNAMENT RESULTS ===\n";
    std::cout << std::left << std::setw(25) << "Player"
              << std::right << std::setw(6) << "Wins"
              << std::setw(8) << "Losses"
              << std::setw(7) << "Ties"
              << std::setw(8) << "Total" << std::endl;
    std::cout << std::string(54, '-') << std::endl;

    for (const auto& player : players) {
        int total = player.getWins() + player.getLosses() + player.getTies();
        std::cout << std::left << std::setw(25) << player.getName()
                  << std::right << std::setw(6) << player.getWins()
                  << std::setw(8) << player.getLosses()
                  << std::setw(7) << player.getTies()
                  << std::setw(8) << total << std::endl;
    }
}

int main(int argc, char** argv) {
    // Check if tournament mode
    bool tournamentMode = (argc == 2 && std::string(argv[1]) == "--tournament");

    if (tournamentMode) {
        // Tournament mode: create AI players with lambda strategies
        std::vector<Player> players;

        // Example strategy: First available column
        players.push_back(Player("First Available", [](const ConnectFour& game, char) {
            for (int col = 0; col < 7; col++) {
                if (game.isValidMove(col)) {
                    return col;
                }
            }
            return 0;
        }));

        // Student Strategy 1 - TODO: Implement your strategy using a lambda
        players.push_back(Player("Strategy 1", [](const ConnectFour& game, char symbol) {
            // TODO: Replace this with your own strategy!
            // This is just a placeholder that will crash
            std::cerr << "ERROR: Strategy 1 not implemented!\n";
            std::cerr << "Please implement this strategy using a lambda function.\n";
            exit(1);
            return 0;
        }));

        // Student Strategy 2 - TODO: Implement your strategy using a lambda
        players.push_back(Player("Strategy 2", [](const ConnectFour& game, char symbol) {
            // TODO: Replace this with your own strategy!
            std::cerr << "ERROR: Strategy 2 not implemented!\n";
            std::cerr << "Please implement this strategy using a lambda function.\n";
            exit(1);
            return 0;
        }));

        // Student Strategy 3 - TODO: Implement your strategy using a lambda
        players.push_back(Player("Strategy 3", [](const ConnectFour& game, char symbol) {
            // TODO: Replace this with your own strategy!
            std::cerr << "ERROR: Strategy 3 not implemented!\n";
            std::cerr << "Please implement this strategy using a lambda function.\n";
            exit(1);
            return 0;
        }));

        // Student Strategy 4 - TODO: Implement your strategy using a lambda
        players.push_back(Player("Strategy 4", [](const ConnectFour& game, char symbol) {
            // TODO: Replace this with your own strategy!
            std::cerr << "ERROR: Strategy 4 not implemented!\n";
            std::cerr << "Please implement this strategy using a lambda function.\n";
            exit(1);
            return 0;
        }));

        // Student Strategy 5 - TODO: Implement your strategy using a lambda
        players.push_back(Player("Strategy 5", [](const ConnectFour& game, char symbol) {
            // TODO: Replace this with your own strategy!
            std::cerr << "ERROR: Strategy 5 not implemented!\n";
            std::cerr << "Please implement this strategy using a lambda function.\n";
            exit(1);
            return 0;
        }));

        // Student Strategy 6 - TODO: Implement your strategy using a lambda
        players.push_back(Player("Strategy 6", [](const ConnectFour& game, char symbol) {
            // TODO: Replace this with your own strategy!
            std::cerr << "ERROR: Strategy 6 not implemented!\n";
            std::cerr << "Please implement this strategy using a lambda function.\n";
            exit(1);
            return 0;
        }));

        // Run tournament with 10 games per matchup
        runTournament(players, 10);

    } else {
        // Default mode: Human vs Human
        std::cout << "=== CONNECT FOUR - HUMAN VS HUMAN ===\n";
        std::cout << "Player 1 is 'X', Player 2 is 'O'\n\n";

        // Create two human players using lambda for strategy
        Player player1("Player 1", [](const ConnectFour& game, char symbol) {
            int col;
            std::cout << game.toString();
            std::cout << "Player " << symbol << ", enter column (0-6): ";
            std::cin >> col;

            while (!game.isValidMove(col)) {
                std::cout << "Invalid move! Enter column (0-6): ";
                std::cin >> col;
            }

            return col;
        });

        Player player2("Player 2", [](const ConnectFour& game, char symbol) {
            int col;
            std::cout << game.toString();
            std::cout << "Player " << symbol << ", enter column (0-6): ";
            std::cin >> col;

            while (!game.isValidMove(col)) {
                std::cout << "Invalid move! Enter column (0-6): ";
                std::cin >> col;
            }

            return col;
        });

        ConnectFour game;
        playGame(player1, player2, game, true);

        std::cout << "\nFinal Stats:\n";
        std::cout << player1.getName() << ": " << player1.getWins() << " wins\n";
        std::cout << player2.getName() << ": " << player2.getWins() << " wins\n";
    }

    return 0;
}
