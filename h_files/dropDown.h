#pragma once
#include "globalFunc.h"
#include "raylib.h"
#include <vector>
#include <string>


enum varType {
    INT,
    STR,
    FLOAT,
    DOUBLE,

};

class DropdownMenuItem {
    private:
    std::string name;
    public:
    std::string getName() {
        return name;
    }


    DropdownMenuItem(std::string itemName, auto itemValue) {

    }
};

class DropdownMenu {
    private:
    
    void* modifyVariable;

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

    DropdownMenu(void* modify, int x, int y) {
        modifyVariable = modify;
        cornerPosition.x = x;
        cornerPosition.y = y;
        rectanglePosition.x = x;
        rectanglePosition.y = y;        
    }
};