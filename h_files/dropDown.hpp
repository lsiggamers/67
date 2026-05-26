#pragma once
#include "globalFunc.hpp"
#include "raylib.h"
#include <vector>
#include <string>


class DropdownMenuItem {
    private:
    std::string name;
    int value;
    public:
    std::string getName() {
        return name;
    }

    int getValue() {
        return value;
    }

    DropdownMenuItem(std::string itemName, int itemValue) {
        name = itemName;
        value = itemValue;
    }
};


class DropdownMenu {
    private:
    
    int* modifyVariable;

    std::vector<DropdownMenuItem> menuOptions;

    Rectangle rectanglePosition;
    ScreenPosition cornerPosition;

    int fontSize;

    void rectangleResize() {
        int textWidth;
        for (DropdownMenuItem i : menuOptions) {
            int textSize = MeasureText(i.getName().c_str(), fontSize);
            if (textSize > textWidth) {
                textWidth = textSize;
            }
        }
        rectanglePosition.width = textWidth;
    }

    public:

    void appendOption(DropdownMenuItem appendable) {
        rectangleResize();
        menuOptions.push_back(appendable);
    }

    DropdownMenuItem optionAt(int at) {
        return menuOptions.at(at);
    }

    void draw(int x, int y, int fontSize, Color color) {
        DrawRectangleRoundedLines(rectanglePosition, 0.1f, 10, BLACK);
    }

    DropdownMenu(int* modifyVariable, int x, int y) {
        this->modifyVariable = modifyVariable;
        cornerPosition.x = x;
        cornerPosition.y = y;
        rectanglePosition.x = x;
        rectanglePosition.y = y;        
    }
};