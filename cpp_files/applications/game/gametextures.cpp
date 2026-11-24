#include "game.hpp"
#include "gameClasses.hpp"
#include "raylib.h"
#include "globalSettings.hpp"
#include "globalFunc.hpp"

// Loads the game textures
void loadGameTextures() {
    levels.push_back(Level("assets/game/level1.png", "assets/game/tileMaps/debugTiles2/debugTexture1.png", "assets/game/levels/level1.json"));
    players.push_back(Player("assets/game/1debug.png", float(windowSize.x / 2), float(windowSize.y / 2)));
}

// Unloads the game textures
void unloadGameTextures() {
    levels.clear();     // Clear the levels vector to free up memory
    NPCs.clear(); // Clear the characters vector to free up memory
    players.clear(); // Clear the character to save memory
}