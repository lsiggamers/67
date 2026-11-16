#include "game.hpp"
#include "gameClasses.hpp"
#include "raylib.h"
#include "globalSettings.hpp"
#include "globalFunc.hpp"

// Loads the game textures
void loadGameTextures() {
    levels.push_back(Level(
        loadTexture(       "assets/game/level1.png", windowSize.x, windowSize.y), 
        LevelTiles(TileMap("assets/game/tileMaps/debugTiles2/debugTexture1.png"), "assets/game/levels/level1.json")
    ));
    levels.at(0).levelTiles.setTile(0, 0, 1);
    levels.at(0).levelTiles.setTile(1, 0, 1);
}

// Unloads the game textures
void unloadGameTextures() {
    levels.clear();     // Clear the levels vector to free up memory
    characters.clear(); // Clear the characters vector to free up memory
}