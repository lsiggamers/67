#include "game.hpp"
#include "gameClasses.hpp"
#include "raylib.h"
#include "globalSettings.hpp"

#include <cstdint>
#include <chrono>
#include <atomic>
#include <vector>

std::vector<Level> levels;
std::vector<Character> characters;

static std::atomic<uint8_t> currentLevel(1);
static bool firstLaunch = true;

// Main input handling function for the game application
static void input() {
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_C)) {
        openApplication = 0;
    }
}

// Main rendering function for the game application
static void render() {
    ClearBackground(primaryColor);
    if (levels.empty()) {
        return; // No levels to render
    } else {
        levels.at(int(currentLevel) - 1).render();  
    }
}

// Resets the game state variables
static void resetGame() {
    currentLevel = 1;
}

// Main function to run the game application
void runGameApplication() {
    // If this is the first launch of the game, load the game textures and reset
    if (firstLaunch) {
        loadGameTextures();
        resetGame();
        firstLaunch = false;
    }

    input();
    render();

    if (openApplication == 0) {
        unloadGameTextures();
        firstLaunch = true;
    }
}