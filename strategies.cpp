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
        players.push_back(Player("Strategy 1 - Random", [](const ConnectFour& game, char symbol) {
            int col;
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<> dist(0, 6);

            do {col = dist(mt);} while(!game.isValidMove(col));

            return col;
        }));

        // Student Strategy 2 - // Play center, then play next to other plays
        players.push_back(Player("Strategy 2 - Center", [](const ConnectFour& game, char symbol) {
            if (game.getMoveCount() < 4) {
                return 3;
            }
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<> dist(-1, 1);
            for (int col = 0; col < 7; col++) {
                    for (int row = 0; row < 6; row++) {
                        if (game.getCell(row,col) != ' ') {
                            int tempInt = dist(mt) + col;
                            if (game.isValidMove(tempInt)) {return tempInt;}
                        }
                    }
                }
            // Play random
            std::random_device rd2;
            std::mt19937 mt2(rd());
            std::uniform_int_distribution<> dist2(0, 6);
            int randomInt;
            do {randomInt = dist2(mt2);} while(!game.isValidMove(randomInt));
            return randomInt;
        }));

        // Student Strategy 3 - Gerardo
        players.push_back(Player("Gerardo Gonzalez", [](const ConnectFour& game, char symbol) {
            int returnColumn;
            //CREATE TEMPORARY BOARD
            char testBoard[6][7] = {};

            //SET PLAYER ORDER
            char first;
            char second;
            if (symbol == 'X') {
                first = 'X';
                second = 'O';
            } else if (symbol == 'O') {
                first = 'O';
                second = 'X';
            }
            char players[2] = {first, second};

            // FOR EACH PLAYER, CHECK EACH COLUMN
            for (char player : players) {
                for (int returnColumn = 0; returnColumn < 7; returnColumn++) {
                    //std::cout << "testing " << player << " in column " << returnColumn << std::endl;

                    // MAKE A COPY OF REAL BOARD
                    for (int i = 0; i < 6; i++) {
                        for (int j = 0; j < 7; j++) {
                            testBoard[i][j] = game.getCell(i,j);
                        }
                    }

                    // MAKE A MOVE IN LOWEST EMPTY SPOT IN CURRENT COLUMN
                    for (int row = 5; row >= 0; row--) {
                        if (testBoard[row][returnColumn] == ' ') {
                            testBoard[row][returnColumn] = player;
                            break;
                        }
                    }

                    // CHECK FOR WINNER

                    // Check horizontal
                    for (int row = 0; row < 6; row++) {
                        for (int col = 0; col < 4; col++) {
                            if (testBoard[row][col] != ' ' &&
                                testBoard[row][col] == testBoard[row][col+1] &&
                                testBoard[row][col] == testBoard[row][col+2] &&
                                testBoard[row][col] == testBoard[row][col+3]) {
                                return returnColumn;
                            }
                        }
                    }

                    // Check vertical
                    for (int row = 0; row < 3; row++) {
                        for (int col = 0; col < 7; col++) {
                            if (testBoard[row][col] != ' ' &&
                                testBoard[row][col] == testBoard[row+1][col] &&
                                testBoard[row][col] == testBoard[row+2][col] &&
                                testBoard[row][col] == testBoard[row+3][col]) {
                                return returnColumn;
                            }
                        }
                    }
                    // Check diagonal (down-right)
                    for (int row = 0; row < 3; row++) {
                        for (int col = 0; col < 4; col++) {
                            if (testBoard[row][col] != ' ' &&
                                testBoard[row][col] == testBoard[row+1][col+1] &&
                                testBoard[row][col] == testBoard[row+2][col+2] &&
                                testBoard[row][col] == testBoard[row+3][col+3]) {
                                return returnColumn;
                            }
                        }
                    }
                    // Check diagonal (down-left)
                    for (int row = 0; row < 3; row++) {
                        for (int col = 3; col < 7; col++) {
                            if (testBoard[row][col] != ' ' &&
                                testBoard[row][col] == testBoard[row+1][col-1] &&
                                testBoard[row][col] == testBoard[row+2][col-2] &&
                                testBoard[row][col] == testBoard[row+3][col-3]) {
                                return returnColumn;
                            }
                        }
                    }
                }
            }

            // If no winning move found, make a random move
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<> dist(0, 6);

            do {returnColumn = dist(mt);} while(!game.isValidMove(returnColumn));

            return returnColumn;
            }));

        // Student Strategy 4 - Jay Kress Jones
        players.push_back(Player("Jay Kress Jones", [](const ConnectFour& game, char symbol) {
            // Check if next move will win game
            for (int col = 0; col < 7; col++) {
                if (game.isValidMove(col)) {
                    ConnectFour tempGame = game;
                    tempGame.makeMove(col);
                    if (tempGame.getWinner() == symbol) {
                        return col;
                    }
                }
            }

            // Check if opposing player move will win, if so then block it.
            char opponentSymbol = (symbol == 'X') ? 'O' : 'X';
            for (int col = 0; col < 7; col++) {
                if (game.isValidMove(col)) {
                    ConnectFour tempGame = game;
                    tempGame.makeMove(col);
                    if (tempGame.getWinner() == opponentSymbol) {
                        return col;
                    }
                }
            }

            // If neither moves apply, play random move.
            int col;
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<> dist(0, 6);

            do {col = dist(mt);} while(!game.isValidMove(col));

            return col;
        }));

        // Student Strategy 5 - Beth Le
        players.push_back(Player("Beth Le", [](const ConnectFour& game, char symbol) {
            static int last_opponent_move = -1;
            int column;
            if (game.getMoveCount() == 0) {
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

        // // Student Strategy 6 - Leo Boon
        // players.push_back(Player("Leo Boon", [](const ConnectFour& game, char symbol) {
        //     int col;
        //     for (col = 0; col < 7; col++) {
        //         ConnectFour temp = game;
        //         temp.makeMove(col);
        //         if (temp.getWinner() == symbol) {
        //             return col;
        //         }
        //         temp.makeMove(col);
        //         if (temp.getWinner() != symbol) {
        //             return col-1;
        //         }
        //         temp.makeMove(col);
        //         if (!temp.isFull()) {
        //             return col+1;
        //         }
        //     }
        //     return col;
        // }));


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