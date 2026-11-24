#include "game.hpp"
#include "gameClasses.hpp"
#include "raylib.h"
#include "globalSettings.hpp"

#include <cstdint>
#include <chrono>
#include <atomic>
#include <vector>

std::vector<Level> levels;
std::vector<NPC> NPCs;
std::vector<Player> players;

static std::atomic<uint8_t> currentLevel(0);
static bool firstLaunch = true;

// Main input handling function for the game application
static void input() {
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_C)) {
        openApplication = 0;
    }
    if (!players.empty()) {
        players.at(0).input();
    }
}

// Main rendering function for the game application
static void render() {
    ClearBackground(primaryColor);
    if (!levels.empty()) {
        levels.at(int(currentLevel)).render();  
    }
    if (!NPCs.empty()) {
        for (int i = 0; i < NPCs.size(); i++) {
            NPCs.at(i).render();
        }
    }
    if (!players.empty()) {
        players.at(0).render();
    }
}

// Resets the game state variables
static void resetGame() {
    currentLevel = 0;
}

// Initialize variables, textures and others for the first launch (and relaunches)
static void launchFunc() {
    ClearBackground(primaryColor);
    DrawCenteredText("Loading Textures...", windowSize.x / 2, windowSize.y / 2, 30, secondaryColor);
    loadGameTextures();
    resetGame();
    firstLaunch = false;
}

// Main function to run the game application
void runGameApplication() {
    // If this is the first launch of the game, load the game textures and reset
    if (firstLaunch) {launchFunc(); return;}

    input();
    render();

    if (openApplication == 0) {
        unloadGameTextures();
        firstLaunch = true;
    }
}