# Connect Four Strategy Tournament

## Overview
In this mini-lab, you'll implement different AI strategies for playing Connect Four using **lambda functions**. Your strategies will compete in a round-robin tournament to see which performs best.

## What's Provided
- `ConnectFour.h` and `ConnectFour.cpp`: The game engine (6x7 board, win detection, move validation)
- `Player.h` and `Player.cpp`: Player class that uses strategy functions
- `strategies.cpp`: Main program with two modes:
  - **Default mode**: Human vs Human play (for testing)
  - **Tournament mode**: AI strategies compete in round-robin tournament

## Your Task
Implement 4 different Connect Four strategies **using lambda functions** in `strategies.cpp`.

Find these sections in the code:
```cpp
// Student Strategy 1 - TODO: Implement your strategy using a lambda
players.push_back(Player("Strategy 1", [](const ConnectFour& game, char symbol) {
    // TODO: Replace this with your own strategy!
    // This is just a placeholder that will crash
    std::cerr << "ERROR: Strategy 1 not implemented!\n";
    exit(1);
    return 0;
}));
```

Replace the TODO code with your own strategy logic using lambda syntax.

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

## Building and Running

### Compile
```bash
make
```

### Default Mode: Human vs Human
```bash
./tournament
```

This lets you play Connect Four against another human. Great for:
- Understanding how the game works
- Testing the game engine
- Having fun!

### Tournament Mode: AI Competition
```bash
./tournament --tournament
```

This runs a round-robin tournament where:
- Each strategy plays against every other strategy
- 10 games per matchup (alternating who goes first)
- Results show wins, losses, and ties

**NOTE**: The tournament will crash with unimplemented strategies! This is intentional - it forces you to implement them.

### Example Tournament Output
```
=== CONNECT FOUR TOURNAMENT ===
Running round-robin with 5 players, 10 games per matchup...

Matchup: First Available vs Strategy 1
ERROR: Strategy 1 not implemented!
Please implement this strategy using a lambda function.
```

Once all strategies are implemented, you'll see:
```
=== TOURNAMENT RESULTS ===
Player                     Wins  Losses   Ties   Total
------------------------------------------------------
Center Preference            25      10      5      40
Block & Win                  22      15      3      40
First Available              15      20      5      40
Edge Preference              12      25      3      40
Random Player                 6      30      4      40
```

## Requirements
You must implement **4 strategies** using **lambda functions**. Each strategy should:
- Always return a valid column number (0-6)
- Use the lambda syntax `[](const ConnectFour& game, char symbol) { ... }`
- Show intelligent behavior (not just first available)
- Be different from your other strategies

## Testing Your Strategies
1. Start by implementing one simple strategy (e.g., center preference)
2. Test it by playing human vs human first to understand the game
3. Run `./tournament --tournament` to see if your strategy works
4. Implement the remaining strategies
5. Run the full tournament to see which strategy performs best

## Grading (20 points)
- **5 points per strategy** (4 strategies total)
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
