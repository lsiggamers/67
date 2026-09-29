#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>
#include "raylib.h"
#include "globalFunc.hpp"
#include "visualAid.hpp"
#include "globalSettings.hpp"

static int speedModifier = 1;

static int selectedBackground = 0;
static const double MOVE_INTERVAL = 1.0 / 5.0;
static double lastMoveTime = 0.0;
static double currentTime;
static ScreenPosition PlayerPosition(
    windowSize.x / 2,
    windowSize.y / 2
);
static bool debugMenuActive = false;

static std::vector<Texture2D> backgroundTextures;
static Texture2D playerTexture;

void unloadVisualAidTextures() {
    for (const auto& texture : backgroundTextures) {
        UnloadTexture(texture);
    }
    UnloadTexture(playerTexture);
    backgroundTextures.clear();
}

void loadVisualAidTextures() {
    // Unload any previously loaded textures to avoid leaks
    unloadVisualAidTextures();
    backgroundTextures.clear();

    const std::filesystem::path imagesDir("assets/visualAid/backgroundimages");
    if (!std::filesystem::exists(imagesDir) || !std::filesystem::is_directory(imagesDir)) {
        return;
    }

    for (const auto& entry : std::filesystem::directory_iterator(imagesDir)) {
        if (!entry.is_regular_file()) continue;
        auto path = entry.path();
        std::string ext = path.extension().string();
        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
        if (ext == ".jpg" || ext == ".jpeg" || ext == ".png" || ext == ".bmp") {
            Image img = LoadImage(path.string().c_str());
            if (img.data != nullptr) {
                ImageResize(&img, windowSize.x, windowSize.y);
                backgroundTextures.push_back(LoadTextureFromImage(img));
                UnloadImage(img);
            }
        }
    }

    Image playerImg = LoadImage("assets/visualAid/player.png");
    ImageResize(&playerImg, windowSize.x / 20, windowSize.x / 20);
    playerTexture = LoadTextureFromImage(playerImg);
    UnloadImage(playerImg);
}


static void drawBackground() {
    if (selectedBackground == 0) {
        ClearBackground(WHITE);
    } else if (selectedBackground > 0) {
        DrawTexture(backgroundTextures[selectedBackground - 1], 0, 0, WHITE);
    }
}


static void input() {
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_C)) {
            openApplication = 0;
            return;
    }
    if (IsKeyPressed(KEY_F1)) {
        debugMenuActive = !debugMenuActive;
    }
    if (IsKeyPressed(KEY_UP)) {
        speedModifier++;
        if (speedModifier > 10) {
            speedModifier = 10;
        }
    } else if (IsKeyPressed(KEY_DOWN)) {
        speedModifier--;
        if (speedModifier < -10) {
            speedModifier = -10;
        }
    }
    if (IsKeyPressed(KEY_LEFT)) {
        selectedBackground--;
        if (selectedBackground < 0) {
            selectedBackground = 0;
        }
    } else if (IsKeyPressed(KEY_RIGHT)) {
        selectedBackground++;
        if (selectedBackground > backgroundTextures.size()) {
            selectedBackground = backgroundTextures.size();
        }
    }
}


static void playerInput() {
    currentTime = GetTime();
    if (currentTime - lastMoveTime < MOVE_INTERVAL) {
        return;
    }

    if (IsKeyDown(KEY_W)) {
        PlayerPosition.y -= 5 * speedModifier;
    } else if (IsKeyDown(KEY_S)) {
        PlayerPosition.y += 5 * speedModifier;
    }

    if (IsKeyDown(KEY_D)) {
        PlayerPosition.x += 5 * speedModifier;
    } else if (IsKeyDown(KEY_A)) {
        PlayerPosition.x -= 5 * speedModifier;
    }

    // Check if outside of window bounds
    if (PlayerPosition.x < 0) {
        PlayerPosition.x = 0;
    } 
    else if (PlayerPosition.x > windowSize.x - windowSize.x / 20) {
        PlayerPosition.x = windowSize.x - windowSize.x / 20;
    }

    if (PlayerPosition.y < 0) {
        PlayerPosition.y = 0;
    } 
    else if (PlayerPosition.y > windowSize.y - windowSize.x / 20) {
        PlayerPosition.y = windowSize.y - windowSize.x / 20;
    }

    lastMoveTime = currentTime;
}


static void debugmenu() {
    if (debugMenuActive) {
        DrawText("Debug Menu", 10, 10, windowSize.y / 20, BLACK);
        DrawText("Player Position:", 10, windowSize.y / 20 + windowSize.y / 40, windowSize.y / 20, BLACK);
        DrawText(("(x:" + std::to_string(PlayerPosition.x) + ", y:" + std::to_string(PlayerPosition.y) + ")").c_str(), 10, windowSize.y / 20 + 2 * windowSize.y / 20, windowSize.y / 20, BLACK);
        DrawText(("Speed Modifier: " + std::to_string(speedModifier)).c_str(), 10, windowSize.y / 20 + 3 * windowSize.y / 20, windowSize.y / 20, BLACK);
        DrawText(("FPS: " + std::to_string(GetFPS())).c_str(), 10, windowSize.y / 20 + 4 * windowSize.y / 20, windowSize.y / 20, BLACK);
    }
}


static void draw() {
    drawBackground();
    if (debugMenuActive) {
        DrawRectangle(0, 0, windowSize.x / 4 * 1.1, windowSize.y / 4 * 1.2, RAYWHITE);
    }
    DrawTexture(playerTexture, PlayerPosition.x, PlayerPosition.y, WHITE);
    if (debugMenuActive) {
        DrawRectangle(PlayerPosition.x, PlayerPosition.y, 4, 4, BLACK);
    }
}

void runVisualAidApplication() {
    input();
    if (!openApplication) {
        return;
    }
    playerInput();
    draw();
    debugmenu();
}