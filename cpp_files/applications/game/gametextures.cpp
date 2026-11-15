#include "game.hpp"
#include "gameClasses.hpp"
#include "raylib.h"
#include "globalSettings.hpp"
#include "globalFunc.hpp"

void loadGameTextures() {

    levels.push_back(Level(loadTexture("assets/game/level1.png", windowSize.x, windowSize.y)));
}

void unloadGameTextures() {
    // Unload game textures here
    levels.clear(); // Clear the levels vector to free up memory
    characters.clear(); // Clear the characters vector to free up memory
}