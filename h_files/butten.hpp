#pragma once
#include "raylib.h"
#include <functional>
#include <string>

class Butten {
    private:

    std::string buttenName;

    std::function<void()> buttenFunction;

    Rectangle rectanglePosition;

    int fontSize;

    public:

    void activate() {
        buttenFunction();
    }

    void draw(int x, int y, int fontSize, Color color) {
        this->fontSize = fontSize > 0 ? fontSize : 1;
        
    }

    Butten(std::string name, std::function<void()> function = nullptr) {
        buttenName = name;
        buttenFunction = function;
    }
};