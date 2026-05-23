#include "globalFunc.h"
#include "globalSettings.h"
#include "raylib.h"
#include <fstream>
#include <iostream>

ScreenPosition windowSize;
bool globalShutoff;

static int resolutionSelection, width, height;
static bool foundWidth, foundHeight;

static void importMonitorSize() {
    std::string line;
    std::ifstream file("settings_files/appLauncherSettings");
    foundWidth = false;
    foundHeight = false;

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
                << "1. 1280/720 (720p)\n"
                << "2. 1920/1080 (1080p)\n"
                << "3. 2560/1440 (1440p)\n\n"
                << "Select here: ";
        std::cin >> resolutionSelection;
        switch (resolutionSelection) {
            case 1: width = 1280; height = 720; break;
            case 2: width = 1920; height = 1080; break;
            case 3: width = 2560; height = 1440; break;
        }

        windowSize.x = width;
        windowSize.y = height;

        std::ofstream file("settings_files/appLauncherSettings", std::ios::app);
        if (!file.is_open()) {
            std::cout << "Failed to open or create settings file";
        } else {
            if (!foundWidth)  {file << "resolutionWidth="  << width  << "\n";}
            if (!foundHeight) {file << "resolutionHeight=" << height << "\n";}
        }
    }
    file.close();
}

void inportApplauncherSettings() {
    importMonitorSize();
}