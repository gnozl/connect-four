#include "ConnectFour.h"
#include "Player.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <random>

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

        // Student Strategy 1 - RANDOM
        players.push_back(Player("Strategy 1", [](const ConnectFour& game, char symbol) {
            int col;
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<> dist(0, 6);

            do {col = dist(mt);} while(!game.isValidMove(col));

            return col;
        }));

        // Student Strategy 2 - // Gerardo - Check for winning move, or block opponent from winning, otherwise random
        players.push_back(Player("Strategy 2", [](const ConnectFour& game, char symbol) {
            int col;

            //Create a temporary board
            ConnectFour temp = ConnectFour();
            std::vector<int> x_array;
            std::vector<int> o_array;

            // Check each column for a winning move
            for (int col = 0; col < 7; col++) {

                temp.reset();
                x_array.clear();
                o_array.clear();

                //Find move on real board
                for (int i = 0; i < 6; i++) {
                    for (int j = 0; j < 7; j++) {
                        if (game.getCell(i,j) == 'X') {
                            x_array.push_back(j);
                        } else if (game.getCell(i,j) == 'O') {
                            o_array.push_back(j);
                        }
                    }
                }
                //play moves on temp board
                char turn = 'X';
                while (!x_array.empty() && !o_array.empty()) {
                    if (turn == 'O') {
                        turn = 'X';
                        temp.makeMove(x_array.front());
                        x_array.erase(x_array.begin());
                    } else if (turn == 'X') {
                        turn = 'O';
                        temp.makeMove(o_array.front());
                        o_array.erase(o_array.begin());
                    }
                }

                //test column for a win
                temp.makeMove(col);
                char winner = temp.getWinner();
                if (winner == symbol) {
                    return col;
                }
                if (winner == 'X' || winner == 'O') {
                    return col;
                }
            }

            // If no winning move found, make a random move
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<> dist(0, 6);

            do {col = dist(mt);} while(!game.isValidMove(col));

            return col;
        }));

        // Student Strategy 3 - TODO: Implement strat3
        players.push_back(Player("Strategy 3", [](const ConnectFour& game, char symbol) {
            int col;
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<> dist(0, 6);

            do {col = dist(mt);} while(!game.isValidMove(col));

            return col;
        }));

        // Student Strategy 4 - Beth Le
        players.push_back(Player("Strategy 4", [](const ConnectFour& game, char symbol) {
            bool firstMove = true;
            static int last_opponent_move = -1;
            int column;
            if (firstMove) {
                firstMove = false;
                do {
                    column = rand() % 7;
                } while (!game.isValidMove(column));
                last_opponent_move = column;
                return column;
            }

            if (last_opponent_move != -1 && game.isValidMove(last_opponent_move)) {
                column = last_opponent_move;
            } else {

                if (last_opponent_move > 0 && game.isValidMove(last_opponent_move - 1)) {
                    column = last_opponent_move - 1;
                } else if (last_opponent_move < 6 && game.isValidMove(last_opponent_move + 1)) {
                    column = last_opponent_move + 1;
                } else {

                    for (int i = 0; i < 7; ++i) {
                        if (game.isValidMove(i)) {
                            column = i;
                            break;
                        }
                    }
                }
            }

            last_opponent_move = column;

            return column;
        }));

        // Student Strategy 5 - Leo Boon
        players.push_back(Player("Strategy 5", [](const ConnectFour& game, char symbol) {
            int col;
            for (col = 0; col < 7; col++) {  // For every move
                ConnectFour temp = ConnectFour(); // Simulate the current board
                std::vector<int> x_array;
                std::vector<int> o_array;
                for (int i = 0; i < 6; i++) {
                    for (int j = 0; j < 7; j++) {
                        if (game.getCell(i,j) == 'X') {
                            x_array.push_back(j);
                        } else if (game.getCell(i,j) == 'O') {
                            o_array.push_back(j);
                        }
                    }
                }
                char turn = 'X';
                while (!x_array.empty() && !o_array.empty()) {
                    if (turn == 'O') {
                        turn = 'X';
                        temp.makeMove(x_array.front());
                        x_array.erase(x_array.begin());
                    } else {
                        turn = 'O';
                        temp.makeMove(o_array.front());
                        o_array.erase(o_array.begin());
                    }
                }

                temp.makeMove(col);
                if (temp.getWinner() == symbol) {
                    return col;
                }
                temp.makeMove(col);
                if (temp.getWinner() != symbol) {
                    return col-1;
                }
                temp.makeMove(col);
                if (!temp.isFull()) {
                    return col+1;
                }
            }

            for (int col = 0; col < 7; col++) {
                if (game.isValidMove(col)) {
                    return col;
                }
            };
        return 0;
        }));

        // Student Strategy 6 - TODO: Implement strat6
        players.push_back(Player("Strategy 6", [](const ConnectFour& game, char symbol) {
            int col;
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<> dist(0, 6);

            do {col = dist(mt);} while(!game.isValidMove(col));

            return col;
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

            //Create a temporary board
            ConnectFour temp = ConnectFour();
            std::vector<int> x_array;
            std::vector<int> o_array;

            // Check each column for a winning move
            for (int col = 0; col < 7; col++) {

                temp.reset();
                x_array.clear();
                o_array.clear();

                //Find move on real board
                for (int i = 0; i < 6; i++) {
                    for (int j = 0; j < 7; j++) {
                        if (game.getCell(i,j) == 'X') {
                            x_array.push_back(j);
                        } else if (game.getCell(i,j) == 'O') {
                            o_array.push_back(j);
                        }
                    }
                }
                //play moves on temp board
                char turn = 'X';
                while (!x_array.empty() && !o_array.empty()) {
                    if (turn == 'O') {
                        turn = 'X';
                        temp.makeMove(x_array.front());
                        x_array.erase(x_array.begin());
                    } else if (turn == 'X') {
                        turn = 'O';
                        temp.makeMove(o_array.front());
                        o_array.erase(o_array.begin());
                    }
                }

                //test column for a win
                temp.makeMove(col);
                char winner = temp.getWinner();
                if (winner == symbol) {
                    return col;
                }
                if (winner == 'X' || winner == 'O') {
                    return col;
                }
            }

            // If no winning move found, make a random move
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<> dist(0, 6);

            do {col = dist(mt);} while(!game.isValidMove(col));

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