#include "raylib.h"
#include "snake.hpp"
#include "globalFunc.hpp"
#include "globalSettings.hpp"
#include <vector>
#include <fstream>

class Square {
    public:
    bool head;
    bool body;
    bool food;
    Vector2 position;
    int snakePosition;

    void clear() {
        head = false;
        body = false;
        food = false;
        snakePosition = -1;
    }

    bool canBeApple() {
        if (!head && !body && !food) {
            return true;
        } else {
            return false;
        }
    }
};

static Vector2 headPosition;
static Vector2 lastHeadPosition;
static const int gridPixelSize = 50;
static int moveDirection, lastDirection, cols, rows, snakeLength, appleAmount, currentApples, highScore;
static bool isDead, isPaused, escape, quit, foundHighScore;
static float moveTimer = 0.0f;
static float moveDelay; 
static std::vector<std::vector<Square>> grid;


static void input() {

    if (IsKeyPressed(KEY_ESCAPE)) {
        escape = !escape;
    }

    if (!escape) {

        if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    && lastDirection != 2) {moveDirection = 1;}
        if ((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  && lastDirection != 1) {moveDirection = 2;}
        if ((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  && lastDirection != 4) {moveDirection = 3;}
        if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && lastDirection != 3) {moveDirection = 4;}

    } else if (escape) {
        if (IsKeyDown(KEY_ONE)) {appleAmount = 1;}
        if (IsKeyDown(KEY_TWO)) {appleAmount = 5;}
        if (IsKeyDown(KEY_THREE)) {appleAmount = 10;}
        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_C)) {
            quit = true;
        }
    }
}


static void renderEscapeMenu() {
    ClearBackground(RAYWHITE);
    DrawCenteredText("Press ESC to open game", windowSize.x / 2, windowSize.y / 2, 50, BLACK);
    DrawCenteredText(TextFormat("Highscore: %d", highScore), windowSize.x / 2, windowSize.y / 2 + 60, 40, BLACK);

    DrawText("Press 1 to set Apple amount to 1",  windowSize.x / 40, windowSize.y / 20,       25, BLACK);
    DrawText("Press 2 to set Apple amount to 5",  windowSize.x / 40, windowSize.y / 20 + 40,  25, BLACK);
    DrawText("Press 3 to set Apple amount to 10", windowSize.x / 40, windowSize.y / 20 + 80,  25, BLACK);
    DrawText(TextFormat("Amount of Apples: %d", appleAmount), windowSize.x / 40, windowSize.y / 20 + 120, 25, BLACK);

    DrawText("Press ctrl+c to quit application", windowSize .x / 40, windowSize.y - 25, 20, BLACK);
    DrawRightText(TextFormat("Width: %d Width: %d", (int)windowSize.x, (int)windowSize.y), windowSize.x - 100, windowSize.y - 25, 20, BLACK);
}


static void initGrid() {
    ClearBackground(RAYWHITE);
    for (int i = gridPixelSize; i < windowSize.x; i += gridPixelSize) {
        for (int j = gridPixelSize; j < windowSize.y; j += gridPixelSize) {
            DrawRectangle(i, j, 3, 3, BLACK);
        }
    }
}


static void countApples() {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (grid[y][x].food) {
                currentApples++;
            }
        }
    }
}


static void createApples() {
    countApples();
    while (currentApples < appleAmount) {
    int r1 = randomInt(0, rows - 1);
    int r2 = randomInt(0, cols - 1);
        if (!grid[r1][r2].food) {
            grid[r1][r2].food = true;
            currentApples++;
        }
        r1 = 0;
        r2 = 0;
    }
    currentApples = 0;
}


static void moveSnake() {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (grid[y][x].head) {
                headPosition = {(float)x, (float)y};
            }
        }
    }

    //Return of it will move out of bounds
    if ((moveDirection == 1 && headPosition.y <= 0) ||
        (moveDirection == 2 && headPosition.y >= rows - 1) ||
        (moveDirection == 3 && headPosition.x <= 0) ||
        (moveDirection == 4 && headPosition.x >= cols - 1)) 
        {
        isDead = true;
        return;
    }

    lastHeadPosition = headPosition;

    //move head
    switch (moveDirection) {
        case 1: grid[headPosition.y - 1][headPosition.x].head = true; break;
        case 2: grid[headPosition.y + 1][headPosition.x].head = true; break;
        case 3: grid[headPosition.y][headPosition.x - 1].head = true; break;
        case 4: grid[headPosition.y][headPosition.x + 1].head = true; break;
    }


    //Check if inside body
    if (grid[headPosition.y][headPosition.x].body) {
        isDead = true;
        return;
    }


    //delete back
    if (!(grid[headPosition.y][headPosition.x].head && grid[headPosition.y][headPosition.x].food)) {
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                if (grid[y][x].snakePosition >= snakeLength) {
                    grid[y][x].clear();
                }
            }
        }

    } else {
        snakeLength++;
        if (moveDelay > 0.1f) {
            moveDelay -= moveDelay / 100;
        }
    }


    //create front of body
    grid[lastHeadPosition.y][lastHeadPosition.x].clear();
    grid[lastHeadPosition.y][lastHeadPosition.x].body = true;
    grid[lastHeadPosition.y][lastHeadPosition.x].snakePosition = 0;

    //increase snakePosition
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (grid[y][x].snakePosition != -1) {
                grid[y][x].snakePosition += 1;
            }
        }
    }
    
    lastDirection = moveDirection;
}


static void renderGridSquares() {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (grid[y][x].head) {
                DrawRectangle(grid[y][x].position.x + 2,  grid[y][x].position.y + 2,  48, 48, DARKGREEN);
                DrawRectangle(grid[y][x].position.x + 10, grid[y][x].position.y + 10, 5,  5,  WHITE);
                DrawRectangle(grid[y][x].position.x + 38, grid[y][x].position.y + 10, 5,  5,  WHITE);
                DrawRectangle(grid[y][x].position.x + 12, grid[y][x].position.y + 12, 2,  2,  BLACK);
                DrawRectangle(grid[y][x].position.x + 40, grid[y][x].position.y + 12, 2,  2,  BLACK);
            } else if (grid[y][x].body) {
                DrawRectangle(grid[y][x].position.x + 2,  grid[y][x].position.y + 2,  48, 48, DARKGREEN);
            } else if (grid[y][x].food) {
                DrawRectangle(grid[y][x].position.x + 5,  grid[y][x].position.y + 5,  42, 42, RED);
            }
        }
    }

    DrawCenteredText(TextFormat("Score: %d", snakeLength - 2), windowSize.x / 2, 50, 50, BLACK);
}


static void importSettings() {
    foundHighScore = false;
    std::string line;
    std::ifstream file("settings_files/snakeSettings");

    if (!file.is_open()) {
        file.close();
    } else {
        while (std::getline(file, line)) {
            if (line.find("highScore=") == 0) {
                highScore = std::stoi(line.substr(10));
                foundHighScore = true;
            }
        }
        file.close();
    }

    if (!foundHighScore) {
        std::ofstream file("settings_files/snakeSettings", std::ios::app);
        if (!file.is_open()) {
            file.close();
        } else {
            file << "highScore=0" << "\n";
        }
    }
    file.close();
}


static void updateHighScore() {
    std::ifstream inFile("settings_files/snakeSettings");
    std::vector<std::string> lines;
    std::string line;

    if (!inFile.is_open()) {
        inFile.close();
        return;
    }

    while (std::getline(inFile, line)) {
        if (line.rfind("highScore=", 0) == 0) {
            // Replace the line
            line = "highScore=" + std::to_string(highScore);
        }
        lines.push_back(line);
    }
    inFile.close();

    std::ofstream outFile("settings_files/snakeSettings", std::ios::trunc);
    for (const auto& l : lines) {
        outFile << l << "\n";
    }
    return;
}


static void reset() {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            grid[y][x].clear();
        }
    }

    if (snakeLength - 2 > highScore) {highScore = snakeLength - 2;}

    isDead = false;
    escape = true;
    moveDirection = 4;
    lastDirection = 4;
    appleAmount = 1;
    snakeLength = 2;
    moveDelay = 0.5f;
    grid[rows / 2][cols / 2].head = true;
    grid[rows / 2][cols / 2 - 1].body = true; grid[rows / 2][cols / 2 - 1].snakePosition = 1;
    grid[rows / 2][cols / 2 - 2].body = true; grid[rows / 2][cols / 2 - 2].snakePosition = 2;
}


void runSnake() {
    quit = false;
    importSettings();
    cols = windowSize.x / gridPixelSize;
    rows = windowSize.y / gridPixelSize;

    grid.resize(rows, std::vector<Square>(cols));

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            grid[y][x].position = {(float)(x * gridPixelSize), (float)(y * gridPixelSize)};
        }
    }

    while (!quit && !WindowShouldClose()) {

        reset();
        createApples();

        while (!quit && !isDead && !WindowShouldClose()) {

            input();
            moveTimer += GetFrameTime();

            if (moveTimer >= moveDelay && !escape) {
                moveSnake();
                createApples();
                moveTimer = 0.0f;
            }

            BeginDrawing();
            if (escape) {
                renderEscapeMenu();
            } else if (!escape && !isDead) {
                initGrid();
                    renderGridSquares();
            }
            EndDrawing();
        }
    }
    updateHighScore();
    return;
}