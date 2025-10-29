# Connect Four Strategy Tournament

**Date**: 2025-10-29
**Points**: 20 points
**Time**: 30-60 minutes (in-class completable)
**Group Work**: Encouraged but optional

**Academic Integrity**: Complete this assignment independently without the use of AI tools (ChatGPT, Claude, Copilot, etc.) unless explicitly permitted by the instructor.

---

## Overview
In this mini-lab, you'll implement **6 different AI strategies** for playing Connect Four using **lambda functions**. Your strategies will compete in a round-robin tournament to see which performs best.

## What's Provided
- `ConnectFour.h` and `ConnectFour.cpp`: The game engine (6x7 board, win detection, move validation)
- `Player.h` and `Player.cpp`: Player class that uses strategy functions
- `strategies.cpp`: Main program with two modes:
  - **Default mode**: Human vs AI play (for testing your strategies)
  - **Tournament mode**: AI strategies compete in round-robin tournament

## Your Task
Implement **6 different Connect Four strategies** using **lambda functions** in `strategies.cpp`. Each strategy must have a **unique name**.

---

## Step-by-Step: Creating and Testing Your First Player

### Step 1: Open `strategies.cpp`

Find the tournament mode section. Look for the comment `// Tournament mode: create AI players with lambda strategies`:

```cpp
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
```

### Step 2: Add Your First Strategy

Below the "First Available" example, add your first strategy. Here's an example:

```cpp
    // Student Strategy 1: Center Preference
    players.push_back(Player("Center Lover", [](const ConnectFour& game, char symbol) {
        // Try center column first (column 3)
        if (game.isValidMove(3)) {
            return 3;
        }
        // Otherwise, try columns outward from center
        for (int offset = 1; offset <= 3; offset++) {
            if (game.isValidMove(3 - offset)) return 3 - offset;
            if (game.isValidMove(3 + offset)) return 3 + offset;
        }
        return 0;  // Fallback (should never happen)
    }));
```

### Step 3: Test Your Strategy by Playing Against It

To test your strategy, you need to play against it in non-tournament mode. Find the `else` block where the default human vs human mode is defined (look for `// Default mode: Human vs Human`).

**Copy your strategy lambda** and paste it as `player2`:

```cpp
    } else {
        // Default mode: Human vs Human (change player2 to test your AI)
        std::cout << "=== CONNECT FOUR - HUMAN VS HUMAN ===\n";
        std::cout << "Player 1 is 'X', Player 2 is 'O'\n\n";

        // Human player
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

        // AI player - PASTE YOUR STRATEGY HERE TO TEST IT
        Player player2("Center Lover", [](const ConnectFour& game, char symbol) {
            // Try center column first (column 3)
            if (game.isValidMove(3)) {
                return 3;
            }
            // Otherwise, try columns outward from center
            for (int offset = 1; offset <= 3; offset++) {
                if (game.isValidMove(3 - offset)) return 3 - offset;
                if (game.isValidMove(3 + offset)) return 3 + offset;
            }
            return 0;
        });

        ConnectFour game;
        playGame(player1, player2, game, true);

        std::cout << "\nFinal Stats:\n";
        std::cout << player1.getName() << ": " << player1.getWins() << " wins\n";
        std::cout << player2.getName() << ": " << player2.getWins() << " wins\n";
    }
```

### Step 4: Compile and Test

Run in default mode (play against your AI):
```bash
./connect-four
```

Play a few games to see if your strategy works as expected!

### Step 5: Add Your Remaining 5 Strategies

Now that you've tested one strategy, add 5 more strategies to the tournament section. Each must:
- Have a **unique name** (no duplicates!)
- Use **lambda syntax**
- Return a valid column number (0-6)
- Show intelligent behavior

### Step 6: Test Each Strategy

As you add each new strategy:
1. Copy the lambda to the non-tournament mode `player2`
2. Run: `./connect-four`
3. Play against it to verify it works

### Step 7: Run the Tournament

Once all 6 strategies are implemented, run the full tournament:

```bash
./connect-four --tournament
```

You should see output like:
```
=== CONNECT FOUR TOURNAMENT ===
Running round-robin with 7 players, 10 games per matchup...

Matchup: First Available vs Center Lover
Matchup: First Available vs Strategy 2
...

=== TOURNAMENT RESULTS ===
Player                     Wins  Losses   Ties   Total
------------------------------------------------------
Center Lover                 35      15     10      60
Strategy 2                   32      20      8      60
...
```

---

### Lambda Syntax Reminder
```cpp
[capture](parameters) { body }
```

Example strategy using a lambda:
```cpp
players.push_back(Player("Center Preference", [](const ConnectFour& game, char symbol) {
    // Try center column first (column 3)
    if (game.isValidMove(3)) {
        return 3;
    }
    // Otherwise, try columns outward from center
    for (int offset = 1; offset <= 3; offset++) {
        if (game.isValidMove(3 - offset)) return 3 - offset;
        if (game.isValidMove(3 + offset)) return 3 + offset;
    }
    return 0;
}));
```

### Strategy Function Details
Your lambda receives:
- **`game`**: Current game state (read-only)
  - `game.getCell(row, col)`: Returns 'X', 'O', or ' ' (empty)
  - `game.isValidMove(col)`: Returns true if column isn't full
  - `game.getCurrentPlayer()`: Returns 'X' or 'O'
- **`symbol`**: Your player's symbol ('X' or 'O')

Your lambda must return:
- An integer from 0-6 (the column number where you want to play)

### Strategy Ideas
- **Random**: Pick a random valid column
- **Center preference**: Prefer playing in center columns (3, then 2/4, etc.)
- **Block opponent**: Look for opponent's three-in-a-row and block it
- **Win if possible**: Check if you can win this turn
- **Defensive scan**: Look for any threats and respond
- **Prefer edges**: Try edges first (columns 0 and 6)

## Running the Program

### Default Mode: Play Against Your AI
```bash
./connect-four
```

This lets you test your strategies by playing against them. Great for:
- Testing your strategy implementations
- Understanding how strategies behave
- Debugging your lambda functions

### Tournament Mode: AI Competition
```bash
./connect-four --tournament
```

This runs a round-robin tournament where:
- Each strategy plays against every other strategy
- 10 games per matchup (alternating who goes first)
- Results show wins, losses, and ties

**NOTE**: Make sure all 6 strategies are implemented before running the tournament!

### Example Tournament Output
```
=== CONNECT FOUR TOURNAMENT ===
Running round-robin with 7 players, 10 games per matchup...

Matchup: First Available vs Center Lover
Matchup: First Available vs Strategy 2
...

=== TOURNAMENT RESULTS ===
Player                     Wins  Losses   Ties   Total
------------------------------------------------------
Center Lover                 35      15     10      60
Strategy 2                   32      20      8      60
...
```

## Requirements
You must implement **6 strategies** using **lambda functions**. Each strategy should:
- Always return a valid column number (0-6)
- Use the lambda syntax `[](const ConnectFour& game, char symbol) { ... }`
- Show intelligent behavior (not just first available)
- Be different from your other strategies
- Have a unique name (no duplicates)

## Group Work
If working in a group:
1. Each member should implement 1-2 strategies in their own copy of `strategies.cpp`
2. Test each strategy individually using the steps above
3. One member creates the final submission by combining all strategies into their `strategies.cpp`
4. **Add all group member names at the top of `strategies.cpp` as a comment** (e.g., `// Names: Alice Smith, Bob Jones, Carol Lee`)
5. All group members should test the final combined version together
6. Submit only ONE `strategies.cpp` file with all 6 strategies from the group

## Testing Your Strategies
1. Start by implementing one simple strategy (e.g., center preference)
2. Test it by playing against it (copy lambda to non-tournament mode)
3. Run `./connect-four --tournament` to see if your strategy works
4. Implement the remaining strategies
5. Run the full tournament to see which strategy performs best

## Grading (20 points)
- **3 points per strategy** (6 strategies total = 18 points)
- **2 points** for successful tournament completion (all strategies have unique names and don't crash)
- Each strategy must:
  - Use lambda syntax (not named functions)
  - Always return a valid column (0-6)
  - Not crash the tournament
  - Show intelligent behavior beyond "first available"

## Tips
- Start simple! A "center preference" strategy is easy to implement
- Test incrementally - implement one strategy at a time
- The example strategy "First Available" is provided as reference
- Remember: the lambda captures nothing `[]` because all needed info comes from parameters
- Look at `ConnectFour.h` to see what methods are available on the `game` object
