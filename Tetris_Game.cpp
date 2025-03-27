#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

const int width = 10;
const int height = 20;
bool gameOver;
int board[height][width] = {0}; // Game board grid
int colorBoard[height][width] = {0}; // Stores colors of locked blocks
int score = 0;
int highScore = 0;
int difficulty = 1; // 1 = Easy, 2 = Medium, 3 = Hard
int speed = 300; // Initial speed

// Tetromino shapes and colors
int tetrominoes[7][4][4] = {
    {{1, 1, 1, 1}},  // I
    {{1, 1}, {1, 1}}, // O
    {{0, 1, 0}, {1, 1, 1}}, // T
    {{1, 1, 0}, {0, 1, 1}}, // S
    {{0, 1, 1}, {1, 1, 0}}, // Z
    {{1, 1, 1}, {1, 0, 0}}, // L
    {{1, 1, 1}, {0, 0, 1}}  // J
};

int colors[7] = {11, 14, 13, 10, 12, 6, 9}; // Light blue, Yellow, Purple, Green, Red, Orange, Blue

struct Block {
    int shape[4][4];
    int size;
    int x, y;
    int color;
} currentBlock;

void copyShape(int shape[4][4], int id) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            shape[i][j] = tetrominoes[id][i][j];
}

void generateBlock() {
    int id = rand() % 7;
    copyShape(currentBlock.shape, id);
    currentBlock.size = (id == 0) ? 4 : 3;
    currentBlock.x = width / 2 - 1;
    currentBlock.y = 0;
    currentBlock.color = colors[id];
}

// Set console text color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void initializeGame() {
    gameOver = false;
    score = 0;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            board[i][j] = colorBoard[i][j] = 0;
    generateBlock();
}

void drawBoard() {
    COORD cursorPosition = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
    int tempBoard[height][width];
    int tempColors[height][width];

    // Copy existing board
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            tempBoard[i][j] = board[i][j];
            tempColors[i][j] = colorBoard[i][j];
        }

    // Merge current moving block into tempBoard
    for (int i = 0; i < currentBlock.size; i++) {
        for (int j = 0; j < currentBlock.size; j++) {
            if (currentBlock.shape[i][j] && currentBlock.y + i >= 0) {
                tempBoard[currentBlock.y + i][currentBlock.x + j] = 1;
                tempColors[currentBlock.y + i][currentBlock.x + j] = currentBlock.color;
            }
        }
    }

    // Draw game board
    for (int i = 0; i < height; i++) {
        cout << "| ";
        for (int j = 0; j < width; j++) {
            if (tempBoard[i][j]) {
                setColor(tempColors[i][j]);
                cout << "# ";
                setColor(15); // Reset to white
            } else {
                cout << "  ";
            }
        }
        cout << "|\n";
    }
    cout << "Score: " << score << " | High Score: " << highScore << " | Difficulty: " 
         << (difficulty == 1 ? "Easy" : difficulty == 2 ? "Medium" : "Hard") << endl;
}

bool isValidMove(int newX, int newY) {
    for (int i = 0; i < currentBlock.size; i++) {
        for (int j = 0; j < currentBlock.size; j++) {
            if (currentBlock.shape[i][j]) {
                int nx = newX + j, ny = newY + i;
                if (nx < 0 || nx >= width || ny >= height || (ny >= 0 && board[ny][nx]))
                    return false;
            }
        }
    }
    return true;
}

void clearLines() {
    for (int i = 0; i < height; i++) {
        bool full = true;
        for (int j = 0; j < width; j++) {
            if (!board[i][j]) {
                full = false;
                break;
            }
        }
        if (full) {
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < width; j++) {
                    board[k][j] = board[k - 1][j];
                    colorBoard[k][j] = colorBoard[k - 1][j];
                }
            }
            score += 10;
        }
    }
}

void rotateBlock() {
    int temp[4][4];
    for (int i = 0; i < currentBlock.size; i++)
        for (int j = 0; j < currentBlock.size; j++)
            temp[j][currentBlock.size - 1 - i] = currentBlock.shape[i][j];

    for (int i = 0; i < currentBlock.size; i++) {
        for (int j = 0; j < currentBlock.size; j++) {
            if (temp[i][j]) {
                int nx = currentBlock.x + j, ny = currentBlock.y + i;
                if (nx < 0 || nx >= width || ny >= height || board[ny][nx])
                    return;
            }
        }
    }

    for (int i = 0; i < currentBlock.size; i++)
        for (int j = 0; j < currentBlock.size; j++)
            currentBlock.shape[i][j] = temp[i][j];
}

void moveBlock(int dx, int dy) {
    if (isValidMove(currentBlock.x + dx, currentBlock.y + dy)) {
        currentBlock.x += dx;
        currentBlock.y += dy;
    } else if (dy == 1) {
        for (int i = 0; i < currentBlock.size; i++) {
            for (int j = 0; j < currentBlock.size; j++) {
                if (currentBlock.shape[i][j]) {
                    board[currentBlock.y + i][currentBlock.x + j] = 1;
                    colorBoard[currentBlock.y + i][currentBlock.x + j] = currentBlock.color;
                }
            }
        }
        clearLines();
        generateBlock();
        if (!isValidMove(currentBlock.x, currentBlock.y)) {
            gameOver = true;
        }
    }
}

void gameLoop() {
    while (!gameOver) {
        drawBoard();
        if (_kbhit()) {
            switch (_getch()) {
                case 'a': moveBlock(-1, 0); break;
                case 'd': moveBlock(1, 0); break;
                case 's': moveBlock(0, 1); break;
                case 'w': rotateBlock(); break;
            }
        }
        Sleep(speed);
        moveBlock(0, 1);
    }
    cout << "Game Over! Final Score: " << score << endl;
}

int main() {
    srand(time(0));
    while (true) {
        cout << "Select Difficulty: 1. Easy  2. Medium  3. Hard\n";
        cin >> difficulty;
        speed = (difficulty == 1) ? 400 : (difficulty == 2) ? 250 : 100;
        initializeGame();
        gameLoop();
        cout << "Play again? (y/n): ";
        char choice;
        cin >> choice;
        if (choice != 'y') break;
    }
    return 0;
}
