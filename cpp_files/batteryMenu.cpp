#include "raylib.h"
#include "batteryMenu.hpp"
#include "globalFunc.hpp"
#include "globalSettings.hpp"
#include <fstream>
#include <filesystem>
#include <vector>

std::vector<Texture2D> batteryTextures;

int batteryIconWidth;
int batteryIconHeight;

void loadBatteryTextures() {
    batteryIconHeight = windowSize.y / 40;
    batteryIconWidth = batteryIconHeight * 130 / 80;

    Image desktopImg =    LoadImage("assets/batteryIcons/desktop.png");
    Image batteryImg100 = LoadImage("assets/batteryIcons/battery100.png");
    Image batteryImg75 =  LoadImage("assets/batteryIcons/battery75.png");
    Image batteryImg50 =  LoadImage("assets/batteryIcons/battery50.png");
    Image batteryImg25 =  LoadImage("assets/batteryIcons/battery25.png");
    Image batteryImg0 =   LoadImage("assets/batteryIcons/battery0.png");

    Texture2D desktopTexture =    LoadTextureFromImage(ImageResizeReturn(desktopImg,    batteryIconWidth, batteryIconHeight));
    Texture2D batteryTexture100 = LoadTextureFromImage(ImageResizeReturn(batteryImg100, batteryIconWidth, batteryIconHeight));
    Texture2D batteryTexture75 =  LoadTextureFromImage(ImageResizeReturn(batteryImg75,  batteryIconWidth, batteryIconHeight));
    Texture2D batteryTexture50 =  LoadTextureFromImage(ImageResizeReturn(batteryImg50,  batteryIconWidth, batteryIconHeight));
    Texture2D batteryTexture25 =  LoadTextureFromImage(ImageResizeReturn(batteryImg25,  batteryIconWidth, batteryIconHeight));
    Texture2D batteryTexture0 =   LoadTextureFromImage(ImageResizeReturn(batteryImg0,   batteryIconWidth, batteryIconHeight));

    batteryTextures.clear();
    batteryTextures.push_back(desktopTexture);
    batteryTextures.push_back(batteryTexture100);
    batteryTextures.push_back(batteryTexture75);
    batteryTextures.push_back(batteryTexture50);
    batteryTextures.push_back(batteryTexture25);
    batteryTextures.push_back(batteryTexture0);

    UnloadImage(desktopImg);
    UnloadImage(batteryImg100);
    UnloadImage(batteryImg75);
    UnloadImage(batteryImg50);
    UnloadImage(batteryImg25);
    UnloadImage(batteryImg0);
}

void batteryMenu() {
    if (std::filesystem::exists("/sys/class/power_supply/BAT0/capacity")) {
        std::ifstream file(     "/sys/class/power_supply/BAT0/capacity");
        int capacity;
        file >> capacity;
        file.close();
        if (capacity >= 90) {
            DrawTexture(batteryTextures[1], windowSize.x - batteryIconWidth, 0, WHITE);
        } else if (capacity >= 70) {
            DrawTexture(batteryTextures[2], windowSize.x - batteryIconWidth, 0, WHITE);
        } else if (capacity >= 45) {
            DrawTexture(batteryTextures[3], windowSize.x - batteryIconWidth, 0, WHITE);
        } else if (capacity >= 20) {
            DrawTexture(batteryTextures[4], windowSize.x - batteryIconWidth, 0, WHITE);
        } else {
            DrawTexture(batteryTextures[5], windowSize.x - batteryIconWidth, 0, WHITE);
        }

        DrawRightText(TextFormat("%d\%", capacity), windowSize.x - batteryIconWidth - windowSize.x / 60, 0, windowSize.y / 40, BLACK);
    } else {
        DrawTexture(    batteryTextures[0], windowSize.x - batteryIconWidth, 0, WHITE);
        DrawRightText("Desktop",                    windowSize.x - batteryIconWidth - windowSize.x / 60, 0, windowSize.y / 40, BLACK);
    }
}

void unloadBatteryTextures() {
    for (auto& texture : batteryTextures) {
        UnloadTexture(texture);
    }
    batteryTextures.clear();
}