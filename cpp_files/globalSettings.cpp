#include "globalFunc.hpp"
#include "globalSettings.hpp"
#include "raylib.h"
#include <fstream>
#include <iostream>

std::vector<application> desktop;

int openApplication;

ScreenPosition windowSize;
bool globalShutoff;

static int resolutionSelection, width, height;
static bool foundWidth, foundHeight;

void importApplauncherSettings() {
    int resolutionSelection;
    int width, height;
    bool foundWidth = false, foundHeight = false;
    std::string line;
    std::ifstream file("settings_files/appLauncherSettings.txtsettings");

    if (!file.is_open()) {
        std::cout << "Failed to open settings file\n";
        file.close();
    } else {
        while (std::getline(file, line)) {
            if (line.find("resolutionWidth=") == 0) {
                windowSize.x = std::stoi(line.substr(16));
                foundWidth = true;
            }
            if (line.find("resolutionHeight=") == 0) {
                windowSize.y = std::stoi(line.substr(17));
                foundHeight = true;
            }
        }
        file.close();
    }

    if (!foundHeight || !foundWidth) {
        std::cout << "No settings Found\n\n";
        std::cout << "Please select your monitor size:\n"
                << "1. Autodetect\n"
                << "2. 1280/720 (720p)\n"
                << "3. 1920/1080 (1080p)\n"
                << "4. 2560/1440 (1440p)\n\n"
                << "Select here: ";
        std::cin >> resolutionSelection;
        switch (resolutionSelection) {
            case 1: {
                if (GetMonitorCount() > 0) {
                    windowSize.x = GetMonitorWidth(0);
                    windowSize.y = GetMonitorHeight(0);
                } else {
                    std::cout << "Multiple monitors detected. Closing program\n";
                    globalShutoff = true;
                    return;
                }
                break;
            }
            case 2: windowSize.x = 1280; windowSize.y = 720; break;
            case 3: windowSize.x = 1920; windowSize.y = 1080; break;
            case 4: windowSize.x = 2560; windowSize.y = 1440; break;
        }


        if (!globalShutoff) {
            std::ofstream file("settings_files/appLauncherSettings.txtsettings", std::ios::app);
            if (!file.is_open()) {
                std::cout << "Failed to open or create settings file";
            } else {
                if (!foundWidth)  {file << "resolutionWidth="  << windowSize.x  << "\n";}
                if (!foundHeight) {file << "resolutionHeight=" << windowSize.y << "\n";}
            }
        }
    }
    file.close();
}