#pragma once
#include "raylib.h"

#include <vector>
#include <cstdint>


class Level {
private:
    Texture2D levelTexture;
public:

    void render() {
        // Implement rendering logic for the level here
        DrawTexture(levelTexture, 0, 0, WHITE);
    }

    Level(Texture2D texture) : levelTexture(texture) {
        // Constructor implementation
    };
};


class Character {
private:

public:
    Character();
};


class Player : public Character {
private:

public:
    Player();
};

extern std::vector<Level> levels;
extern std::vector<Character> characters;