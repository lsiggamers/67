#include "raylib.h"
#include "batteryMenu.hpp"
#include "globalFunc.hpp"
#include "globalSettings.hpp"
#include <fstream>
#include <filesystem>
#include <vector>

std::vector<Texture2D> batteryTextures;

void loadBatteryTextures() {
    Image batteryImg100 = LoadImage("assets/batteryIcons/100battery.png");
    Image batteryImg75 = LoadImage("assets/batteryIcons/75battery.png");
    Image batteryImg50 = LoadImage("assets/batteryIcons/50battery.png");
    Image batteryImg25 = LoadImage("assets/batteryIcons/25battery.png");
    Image batteryImg0 = LoadImage("assets/batteryIcons/0battery.png");

    Texture2D batteryTexture100 = LoadTextureFromImage(resizeAndUpload(batteryImg100, batteryIconWidth, batteryIconHeight));
    Texture2D batteryTexture75 =  LoadTextureFromImage(resizeAndUpload(batteryImg75,  batteryIconWidth, batteryIconHeight));
    Texture2D batteryTexture50 =  LoadTextureFromImage(resizeAndUpload(batteryImg50,  batteryIconWidth, batteryIconHeight));
    Texture2D batteryTexture25 =  LoadTextureFromImage(resizeAndUpload(batteryImg25,  batteryIconWidth, batteryIconHeight));
    Texture2D batteryTexture0 =   LoadTextureFromImage(resizeAndUpload(batteryImg0,   batteryIconWidth, batteryIconHeight));

    batteryTextures.push_back(batteryTexture100);
    batteryTextures.push_back(batteryTexture75);
    batteryTextures.push_back(batteryTexture50);
    batteryTextures.push_back(batteryTexture25);
    batteryTextures.push_back(batteryTexture0);

    UnloadImage(batteryImg100);
    UnloadImage(batteryImg75);
    UnloadImage(batteryImg50);
    UnloadImage(batteryImg25);
    UnloadImage(batteryImg0);
}

void batteryMenu() {
    if (std::filesystem::exists("/sys/class/power_supply/BAT0/capacity")) {
        std::ifstream file(       "/sys/class/power_supply/BAT0/capacity");
        int capacity;
        file >> capacity;
        file.close();
        
        if (capacity >= 90) {
            DrawTexture(batteryTextures[0], windowSize.x - (windowSize.x / 50) - batteryIconWidth, windowSize.y / 50, WHITE);
        } else if (capacity >= 70) {
            DrawTexture(batteryTextures[1], windowSize.x - (windowSize.x / 50) - batteryIconWidth, windowSize.y / 50, WHITE);
        } else if (capacity >= 45) {
            DrawTexture(batteryTextures[2], windowSize.x - (windowSize.x / 50) - batteryIconWidth, windowSize.y / 50, WHITE);
        } else if (capacity >= 20) {
            DrawTexture(batteryTextures[3], windowSize.x - (windowSize.x / 50) - batteryIconWidth, windowSize.y / 50, WHITE);
        } else {
            DrawTexture(batteryTextures[4], windowSize.x - (windowSize.x / 50) - batteryIconWidth, windowSize.y / 50, WHITE);
        }

        DrawRightText(TextFormat("%d\%", capacity), windowSize.x - windowSize.x / 30, windowSize.y / 30, windowSize.y / 40, BLACK);
    } else {
        DrawRightText("No Battery"                , windowSize.x - windowSize.x / 30, windowSize.y / 30, windowSize.y / 60, BLACK);
    }
}

void unloadBatteryTextures() {
    for (auto& texture : batteryTextures) {
        UnloadTexture(texture);
    }
    batteryTextures.clear();
}