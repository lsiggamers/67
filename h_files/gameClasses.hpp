#pragma once
#include "raylib.h"
#include "globalFunc.hpp"
#include "globalSettings.hpp"

#include <vector>
#include <cstdint>
#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

#define TILE_GRID_SIZE_X 10 // Define the size of a tile grid in a level
#define TILE_GRID_SIZE_Y 10 // Define the size of a tile grid in a level


class TileMap {
private:
    Texture2D tileTextures[9]; // Array to hold 9 different tile textures for the tile map
public:
    // Returns it Texture at n's position
    Texture2D at(int n) {
        if (n < 0 || n > 9) {
            std::cout << "ERROR: Out of bounds. The position in the array yo uare trying to reach is out of bounds. Closing program";
            globalShutoff = true;
            return;
        }
        return tileTextures[n];
    }

    TileMap(const char* file) {
        std::string filePath = file ? file : "";
        if (filePath.size() >= 5 && filePath.compare(filePath.size() - 5, 5, "1.png") == 0) {
            for (int i = 0; i < 9; i++) {
                filePath[filePath.size() - 5] = static_cast<char>('1' + i);
                tileTextures[i] = loadTexture(filePath.c_str(), windowSize.x / TILE_GRID_SIZE_X, windowSize.y / TILE_GRID_SIZE_Y);
            }
        } else {
            std::cout << "Error: Invalid file format. Expected a PNG file ending in \"1.png\" in creation of TileMap.\n";
            globalShutoff = true; // Set globalShutoff to true to indicate an error
        }
    }
};


class LevelTiles {
private:
    TileMap tileMap; // Instance of TileMap to manage tile textures
    uint8_t tileData[TILE_GRID_SIZE_X][TILE_GRID_SIZE_Y]; // TILE_GRID_SIZE_X x TILE_GRID_SIZE_Y grid of tiles, each tile represented by a uint8_t

    // Logic only implemented in void tileDataRecalculate()
    static void tileDataRecalculationLogic(int x, int y) {
        if (tileData[x][y + 1] != 10) {
            if (tileData[x + 1][y] != 10) {
                if (tileData[x - 1][y] != 10) {
                    if (tileData[x][y - 1] != 10) {
                        tileData[x][y] = 4;
                    } else {
                        tileData[x][y] = 1;
                    }
                } else {
                    if (tileData[x][y - 1] != 10) {
                        tileData[x][y] = 3;
                    } else {
                        tileData[x][y] = 0;
                    }
                }
            } else {
                if (tileData[x - 1][y] != 10) {
                    if (tileData[x][y - 1] != 10) {
                        tileData[x][y] = 5;
                    } else {
                        tileData[x][y] = 2;
                    }
                } else {
                    if (tileData[x][y - 1] != 10) {
                        tileData[x][y] = 4;
                    } else {
                        tileData[x][y] = 1;
                    }
                }
            }
        } else {
            if (tileData[x + 1][y] != 10) {
                if (tileData[x - 1][y] != 10) {
                    if (tileData[x][y - 1] != 10) {
                        tileData[x][y] = 7;
                    } else {
                        tileData[x][y] = 1;
                    }
                } else {
                    if (tileData[x][y - 1] != 10) {
                        tileData[x][y] = 6;
                    } else {
                        tileData[x][y] = 0;
                    }
                }
            } else {
                if (tileData[x - 1][y] != 10) {
                    if (tileData[x][y - 1] != 10) {
                        tileData[x][y] = 8;
                    } else {
                        tileData[x][y] = 2;
                    }
                } else {
                    if (tileData[x][y - 1] != 10) {
                        tileData[x][y] = 7;
                    } else {
                        tileData[x][y] = 1;
                    }
                }
            }
        }
    }
    
    // Recalculates which texture each tile should be
    void tileDataRecalculate() {
        for (int x = 0; x < TILE_GRID_SIZE_X; x++) {
            for (int y = 0; y < TILE_GRID_SIZE_Y; y++) {
                if (tileData[x][y] != 10) { // If the tile is not blank
                    if (tileData[x][y] < 0 || tileData[x][y] > 9) { // If the tile type is out of bounds
                        std::cout << "Error: Tile type out of bounds in tileDataRecalculate.\n";
                        globalShutoff = true; // Set globalShutoff to true to indicate an error
                        return;
                    }
                    
                    // Logic here
                    tileDataRecalculationLogic(x, y);
                }
            }
        }
    }
public:
    // Method to set a tile at a specific position in the grid
    void setTile(int x, int y, uint8_t tileType) {
        if (x >= 0 && x < TILE_GRID_SIZE_X && y >= 0 && y < TILE_GRID_SIZE_Y) {
            tileData[x][y] = tileType;
        } else {
            std::cout << "Error: Tile coordinates out of bounds in setTile.\n";
        }
        tileDataRecalculate();
    }

    // Method to render the tiles
    void render() {
        for (int x = 0; x < TILE_GRID_SIZE_X; x++) {
            for (int y = 0; y < TILE_GRID_SIZE_Y; y++) {
                if (tileData[x][y] != 10) { // Render blank tiles
                    DrawTexture(tileMap.at(tileData[x][y]), x * (windowSize.x / TILE_GRID_SIZE_X), y * (windowSize.y / TILE_GRID_SIZE_Y), WHITE);
                }
            }
        }
    }

    // Constructor to load textures and initialize tileData from a file
    LevelTiles(TileMap tileMap, const char* file) : tileMap(tileMap) {
        std::string filePath = file ? file : "";
        if (filePath.size() >= 5 && filePath.compare(filePath.size() - 5, 5, ".json") == 0) {
            // Load tile data from the specified file
            // Implement tile data loading logic here so that a true is set to "1" in tileData and false is set to "10" in tileData for each tile based on the file content
            std::ifstream fileStream(file);
            nlohmann::json jsonData = nlohmann::json::parse(fileStream, nullptr, false);

            for (int x = 0; x < TILE_GRID_SIZE_X; x++) {
                for (int y = 0; y < TILE_GRID_SIZE_Y; y++) {
                    if (jsonData["tileData"][x][y] == true) {
                        tileData[x][y] = 4; // Set to the fifth tile texture
                    } else {
                        tileData[x][y] = 10; // Set to blank tile
                    }
                }
            }
            fileStream.close(); // Close the file stream after reading
            jsonData.clear(); // Clear the JSON data to free up memory
        } else {
            std::cout << "Error: Invalid file format. Expected a JSON file in creation of LevelTiles.\n";
            globalShutoff = true; // Set globalShutoff to true to indicate an error
        }
        tileDataRecalculate();
    }

    // Constructor to load textures and manually initialize tileData
    LevelTiles(TileMap tileMap) : tileMap(tileMap) {
        // Constructor implementation
        for (int x = 0; x < TILE_GRID_SIZE_X; x++) {
            for (int y = 0; y < TILE_GRID_SIZE_Y; y++) {
                tileData[x][y] = 10; // Initialize all tiles to be blank (represented by 10)
            }
        }
    }
};


class Level {
private:
    Texture2D levelBackgroundTexture;
public:
    LevelTiles levelTiles; // Instance of LevelTiles to manage tile data
    
    // Method to render the level
    void render() {
        DrawTexture(levelBackgroundTexture, 0, 0, WHITE);
        levelTiles.render();
    }

    // Default constructor to initialize a level
    Level(Texture2D backgroundTexture, LevelTiles tileMap) : levelBackgroundTexture(backgroundTexture), levelTiles(tileMap) {
        // Constructor implementation
    };
};

class CharacterPosition {
private:
    float x;
    float y;
public:
    // Default constructor, 
    CharacterPosition(float x, float y) : x(x), y(y) {
        // Constructor implementation
    }
};


class Character {
private:

    bool hostile;
public:



    void move(float lenght, uint8_t, direction) {

    }

    Character();
};


class Player : public Character {
private:

public:
    Player();
};


extern std::vector<Level> levels;
extern std::vector<Character> characters;