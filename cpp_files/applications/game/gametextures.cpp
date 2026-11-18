#include "game.hpp"
#include "gameClasses.hpp"
#include "raylib.h"
#include "globalSettings.hpp"
#include "globalFunc.hpp"

// Loads the game textures
void loadGameTextures() {
    levels.push_back(Level("assets/game/level1.png", "assets/game/tileMaps/debugTiles2/debugTexture1.png", "assets/game/levels/level1.json"));
}

// Unloads the game textures
void unloadGameTextures() {
    levels.clear();     // Clear the levels vector to free up memory
    characters.clear(); // Clear the characters vector to free up memory
}