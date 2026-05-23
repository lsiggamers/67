#pragma once
#include <functional>
#include <string>

class application {
    private:
    std::function<void()> applicationFunc;
    
    public:
    std::string applicationName;

    ScreenPosition applicationPosition;

    void open() {
        applicationFunc();
    }

    application() {};

    application(std::function<void()> func, std::string name) {
        applicationFunc = func;
        applicationName = name;
    }
};

void renderMainMenu();

void createApplications();