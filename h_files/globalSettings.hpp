#pragma once
#include "globalFunc.hpp"
#include "raylib.h"

#include <functional>
#include <string>
#include <vector>

class application {
    private:
    std::function<void()> applicationFunc;
    
    std::function<void()> applicationTextureLoader;
    std::function<void()> applicationTextureUnloader;
    
    public:
    std::string applicationName;

    ScreenPosition applicationPosition;

    void open() {
        applicationFunc();
    }

    bool hasTextureLoader() {
        return applicationTextureLoader != nullptr;
    }

    void loadTexture() {
        applicationTextureLoader();
    }

    bool hasTextureUnloader() {
        return applicationTextureUnloader != nullptr;
    }

    void unloadTexture() {
        applicationTextureUnloader();
    }

    application() {};

    application(std::function<void()> func, std::string name, std::function<void()> textureLoader = nullptr, std::function<void()> textureUnloader = nullptr) {
        applicationFunc = func;
        applicationName = name;
        applicationTextureLoader = textureLoader;
        applicationTextureUnloader = textureUnloader;
    }
};

// System Settings
extern ScreenPosition windowSize;
extern bool globalShutoff, developerMode, restart;
extern std::vector<application> desktop;
extern int openApplication;

// User Edited Settingsvaribles
extern Color primaryColor;
extern Color secondaryColor;

void importApplauncherSettings();