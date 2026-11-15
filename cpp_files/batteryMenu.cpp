#include "raylib.h"
#include "batteryMenu.hpp"
#include "globalFunc.hpp"
#include "globalSettings.hpp"
#include "topMenu.hpp"

#include <fstream>
#include <filesystem>
#include <vector>
#include <iostream>
#include <thread>
#include <atomic>

static std::atomic<bool> charging(false), batteryPresent(false);
static std::atomic<uint8_t> capacity(0);

static std::vector<Texture2D> batteryTextures;

static int batteryIconWidth;
static int batteryIconHeight;
static int chargingIconWidth;


void loadBatteryTextures() {
    batteryIconHeight = windowSize.y / 40;
    batteryIconWidth = batteryIconHeight * 130 / 80;

    batteryTextures.clear();
    batteryTextures.push_back(loadTexture("assets/batteryIcons/desktop.png", batteryIconWidth, batteryIconHeight));
    batteryTextures.push_back(loadTexture("assets/batteryIcons/battery100.png", batteryIconWidth, batteryIconHeight));
    batteryTextures.push_back(loadTexture("assets/batteryIcons/battery75.png", batteryIconWidth, batteryIconHeight));
    batteryTextures.push_back(loadTexture("assets/batteryIcons/battery50.png", batteryIconWidth, batteryIconHeight));
    batteryTextures.push_back(loadTexture("assets/batteryIcons/battery25.png", batteryIconWidth, batteryIconHeight));
    batteryTextures.push_back(loadTexture("assets/batteryIcons/battery0.png", batteryIconWidth, batteryIconHeight));
    batteryTextures.push_back(loadTexture("assets/batteryIcons/charging.png", chargingIconWidth, batteryIconHeight));
}

void batteryMeasure() {
    int newCapacity;
    while (!globalShutoff) {
        if (std::filesystem::exists("/sys/class/power_supply/BAT0/status")) {
            std::ifstream file("/sys/class/power_supply/BAT0/status");
            std::string status;
            file >> status;
            charging = (status == "Charging");
            batteryPresent = true;
            file.close();
        } else {
            batteryPresent = false;
        }

        if (batteryPresent && std::filesystem::exists("/sys/class/power_supply/BAT0/capacity")) {
            std::ifstream file("/sys/class/power_supply/BAT0/capacity");
            if (file >> newCapacity) {
                capacity = newCapacity;
            }
            file.close();
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
        if (globalShutoff) {
            return;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void drawBatteryMenu() {
    if (!batteryPresent) {
        DrawTexture(batteryTextures[0], windowSize.x - topMenuSpot - batteryIconWidth, 5, WHITE);
    } else if (capacity >= 90) {
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
    topMenuSpot += batteryIconWidth + topMenuPadding;

    if (batteryPresent) {
        DrawRightText(TextFormat("%d\%", int(capacity)), windowSize.x - topMenuSpot, 5, windowSize.y / 40, BLACK);
        topMenuSpot += MeasureText(TextFormat("%d\%", int(capacity)), windowSize.x / 40) + topMenuPadding;
    } else {
        DrawRightText("Desktop", windowSize.x - topMenuSpot, 5, windowSize.y / 40, BLACK);
        topMenuSpot += MeasureText("Desktop", windowSize.x / 40) + topMenuPadding;
    }
}

void unloadBatteryTextures() {
    for (auto& texture : batteryTextures) {
        UnloadTexture(texture);
    }
    batteryTextures.clear();
}