# Tetris Console Game 🎮

## 📝 Overview
This is a simple **Tetris-inspired** game built in **C++** that runs in the console. The game challenges players to manipulate falling blocks (Tetrominoes) to clear lines and score points. With three difficulty levels, players can test their reflexes and strategic thinking.

## 🚀 Features
- **Classic Tetris Gameplay**: Rotate and move Tetrominoes to fit them into the grid.
- **Three Difficulty Levels**: Choose from Easy, Medium, or Hard.
- **Score Tracking**: Compete to beat your high score.
- **Real-time Controls**: Move blocks left, right, down, or rotate them using keyboard inputs.
- **Auto-Down Movement**: Blocks drop at increasing speed based on difficulty.
- **Game Over Detection**: When the grid fills up, the game ends.

## 🎮 Controls
| Key | Action |
|-----|--------|
| `A` | Move Left |
| `D` | Move Right |
| `S` | Move Down Faster |
| `W` | Rotate Block |

## 🏆 Scoring
- **10 points** for each completed row.
- The game **ends** when no more blocks can be placed.

## 🔧 Installation & Usage
### Prerequisites
- **Windows OS** (Recommended, due to `windows.h` dependency)
- **C++ Compiler** (MinGW or MSVC)

### Steps to Run
1. **Clone or Download** this repository.
2. Compile the program using:
   ```sh
   g++ tetris.cpp -o tetris.exe
   ```
3. Run the executable:
   ```sh
   tetris.exe
   ```
4. Select a difficulty and start playing!

## 📜 Code Explanation
### 1️⃣ Game Initialization
- `initializeGame()`: Resets the board, generates the first block, and sets `gameOver = false`.
- `generateBlock()`: Creates a new random Tetromino at the top of the board.

### 2️⃣ Game Logic
- `moveBlock(dx, dy)`: Moves the block horizontally (`dx`) or downwards (`dy`), checking for collisions.
- `rotateBlock()`: Rotates the current block if space allows.
- `isValidMove(newX, newY)`: Ensures the block stays within the grid and doesn't overlap with placed blocks.
- `clearLines()`: Detects full rows and shifts remaining rows downward.

### 3️⃣ Display and Interaction
- `drawBoard()`: Uses **Windows Console functions** to render the board dynamically.
- `_kbhit()` & `_getch()`: Detects key presses for movement and rotation.
- `gameLoop()`: The main loop that updates the board, checks for input, and moves blocks automatically.

### 4️⃣ Difficulty & Speed
- User selects difficulty at the start, adjusting the game speed.
- Speed values:
  - **Easy**: 400 ms per move
  - **Medium**: 250 ms per move
  - **Hard**: 100 ms per move

## 🛠️ Future Improvements
- Implement a leaderboard system.
- Introduce music and sound effects.
- Improve UI for a better gaming experience.
- Add multiplayer mode for competitive play.
- Implement customizable controls.

## ⚠️ Common Issues & Fixes
### 1️⃣ Compilation Errors
- **Error:** `fatal error: windows.h: No such file or directory`
- **Solution:** Ensure you are using a Windows-compatible compiler like MinGW or MSVC.

- **Error:** `undefined reference to '_kbhit' or '_getch'`
- **Solution:** Include `<conio.h>` in your program.

### 2️⃣ Game Crashes on Start
- **Possible Cause:** Incorrect handling of memory or array out-of-bounds access.
- **Solution:** Run with a debugger to trace the issue.

## 👥 Contributors
- [HARSHILTEJOT](https://github.com/HARSHILTEJOT)

