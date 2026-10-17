#include "raylib.h"
#include "batteryMenu.hpp"
#include "globalFunc.hpp"
#include "globalSettings.hpp"
#include "topMenu.hpp"
#include <fstream>
#include <filesystem>
#include <vector>
#include <iostream>

std::vector<Texture2D> batteryTextures;

int batteryIconWidth;
int batteryIconHeight;
int chargingIconWidth;

void loadBatteryTextures() {
    batteryIconHeight = windowSize.y / 40;
    batteryIconWidth = batteryIconHeight * 130 / 80;

    Image desktopImg =    LoadImage("assets/batteryIcons/desktop.png");
    Image batteryImg100 = LoadImage("assets/batteryIcons/battery100.png");
    Image batteryImg75 =  LoadImage("assets/batteryIcons/battery75.png");
    Image batteryImg50 =  LoadImage("assets/batteryIcons/battery50.png");
    Image batteryImg25 =  LoadImage("assets/batteryIcons/battery25.png");
    Image batteryImg0 =   LoadImage("assets/batteryIcons/battery0.png");
    Image chargingImg =   LoadImage("assets/batteryIcons/charging.png");

    Texture2D desktopTexture =    LoadTextureFromImage(ImageResizeReturn(desktopImg,    batteryIconWidth,  batteryIconHeight));
    Texture2D batteryTexture100 = LoadTextureFromImage(ImageResizeReturn(batteryImg100, batteryIconWidth,  batteryIconHeight));
    Texture2D batteryTexture75 =  LoadTextureFromImage(ImageResizeReturn(batteryImg75,  batteryIconWidth,  batteryIconHeight));
    Texture2D batteryTexture50 =  LoadTextureFromImage(ImageResizeReturn(batteryImg50,  batteryIconWidth,  batteryIconHeight));
    Texture2D batteryTexture25 =  LoadTextureFromImage(ImageResizeReturn(batteryImg25,  batteryIconWidth,  batteryIconHeight));
    Texture2D batteryTexture0 =   LoadTextureFromImage(ImageResizeReturn(batteryImg0,   batteryIconWidth,  batteryIconHeight));
    Texture2D chargingTexture =   LoadTextureFromImage(ImageResizeReturn(chargingImg,   chargingIconWidth, batteryIconHeight));

    batteryTextures.clear();
    batteryTextures.push_back(desktopTexture);
    batteryTextures.push_back(batteryTexture100);
    batteryTextures.push_back(batteryTexture75);
    batteryTextures.push_back(batteryTexture50);
    batteryTextures.push_back(batteryTexture25);
    batteryTextures.push_back(batteryTexture0);
    batteryTextures.push_back(chargingTexture);

    UnloadImage(desktopImg);
    UnloadImage(batteryImg100);
    UnloadImage(batteryImg75);
    UnloadImage(batteryImg50);
    UnloadImage(batteryImg25);
    UnloadImage(batteryImg0);
    UnloadImage(chargingImg);
}

void batteryMenu() {
    if (std::filesystem::exists("/sys/class/power_supply/BAT0/capacity")) {
        std::ifstream file(     "/sys/class/power_supply/BAT0/capacity");
        int capacity;
        file >> capacity;
        file.close();
        if (capacity >= 90) {
            DrawTexture(batteryTextures[1], windowSize.x - topMenuSpot - batteryIconWidth, 5, WHITE);
        } else if (capacity >= 70) {
            DrawTexture(batteryTextures[2], windowSize.x - topMenuSpot - batteryIconWidth, 5, WHITE);
        } else if (capacity >= 45) {
            DrawTexture(batteryTextures[3], windowSize.x - topMenuSpot - batteryIconWidth, 5, WHITE);
        } else if (capacity >= 20) {
            DrawTexture(batteryTextures[4], windowSize.x - topMenuSpot - batteryIconWidth, 5, WHITE);
        } else {
            DrawTexture(batteryTextures[5], windowSize.x - topMenuSpot - batteryIconWidth, 5, WHITE);
        }
        topMenuSpot += batteryIconWidth + 5;

        DrawRightText(TextFormat("%d\%", capacity), windowSize.x - topMenuSpot, 5, windowSize.y / 40, BLACK);
        topMenuSpot += MeasureText(TextFormat("%d\%", capacity), windowSize.x / 40);
    } else {
        DrawTexture(    batteryTextures[0], windowSize.x - topMenuSpot - batteryIconWidth, 5, WHITE);
        topMenuSpot += batteryIconWidth + 5;
        DrawRightText("Desktop",                    windowSize.x - topMenuSpot, 5, windowSize.y / 40, BLACK);
        topMenuSpot += MeasureText("Desktop", windowSize.x / 40);
    }
}

void unloadBatteryTextures() {
    for (auto& texture : batteryTextures) {
        UnloadTexture(texture);
    }
    batteryTextures.clear();
}