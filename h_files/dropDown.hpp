#pragma once
#include "globalFunc.hpp"
#include "globalSettings.hpp"
#include "raylib.h"
#include <vector>
#include <string>


template <typename T = int>
class DropdownMenuItem {
    private:
    std::string name;
    T value;
    public:
    const std::string& getName() const {
        return name;
    }

    const T& getValue() const {
        return value;
    }

    DropdownMenuItem(std::string itemName, const T& itemValue) {
        name = itemName;
        value = itemValue;
    }
};


template <typename T = int>
class DropdownMenu {
    private:
    
    T* modifyVariable;
    bool isOpen;

    std::vector<DropdownMenuItem<T>> menuOptions;

    Rectangle rectanglePosition;

    int fontSize;

    void rectangleResize() {
        int textWidth = 0;
        for (const DropdownMenuItem<T>& item : menuOptions) {
            int textSize = MeasureText(item.getName().c_str(), fontSize);
            if (textSize > textWidth) {
                textWidth = textSize;
            }
        }
        rectanglePosition.width = textWidth + 20;
        rectanglePosition.height = fontSize + 12;
    }

    public:

    void appendOption(const DropdownMenuItem<T>& appendable) {
        menuOptions.push_back(appendable);
        rectangleResize();
    }

    DropdownMenuItem<T> optionAt(int at) const {
        return menuOptions.at(at);
    }

    void draw(int x, int y, int fontSize, Color color) {
        this->fontSize = fontSize > 0 ? fontSize : 1;
        rectanglePosition.x = static_cast<float>(x);
        rectanglePosition.y = static_cast<float>(y);
        rectangleResize();

        Vector2 mousePosition = GetMousePosition();
        Rectangle menuBounds = {
            rectanglePosition.x,
            rectanglePosition.y + rectanglePosition.height,
            rectanglePosition.width,
            rectanglePosition.height * menuOptions.size()
        };

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isOpen && CheckCollisionPointRec(mousePosition, menuBounds)) {
                int selectedIndex = static_cast<int>((mousePosition.y - menuBounds.y) / rectanglePosition.height);
                if (selectedIndex >= 0 && selectedIndex < static_cast<int>(menuOptions.size())) {
                    if (modifyVariable != nullptr) {
                        *modifyVariable = menuOptions.at(selectedIndex).getValue();
                    }
                    isOpen = false;
                }
            } else if (CheckCollisionPointRec(mousePosition, rectanglePosition)) {
                isOpen = !isOpen;
            } else if (isOpen) {
                isOpen = false;
            }
        }

        DrawRectangleRounded(rectanglePosition, 0.1f, 10, primaryColor);
        DrawRectangleRoundedLines(rectanglePosition, 0.1f, 10, color);

        const char* selectedName = "";
        if (!menuOptions.empty()) {
            selectedName = menuOptions.front().getName().c_str();
            if (modifyVariable != nullptr) {
                for (const DropdownMenuItem<T>& item : menuOptions) {
                    if (item.getValue() == *modifyVariable) {
                        selectedName = item.getName().c_str();
                        break;
                    }
                }
            }
        }
        DrawText(selectedName, x + 10, y + 6, this->fontSize, secondaryColor);

        if (isOpen) {
            for (std::size_t index = 0; index < menuOptions.size(); ++index) {
                Rectangle optionBounds = {
                    rectanglePosition.x,
                    rectanglePosition.y + rectanglePosition.height * (index + 1),
                    rectanglePosition.width,
                    rectanglePosition.height
                };
                DrawRectangleRec(optionBounds, primaryColor);
                DrawRectangleLinesEx(optionBounds, 1, color);
                DrawText(menuOptions.at(index).getName().c_str(), x + 10,
                    static_cast<int>(optionBounds.y) + 6, this->fontSize, secondaryColor);
            }
        }
    }

    DropdownMenu(T* modifyVariable, int x, int y)
        : modifyVariable(modifyVariable), isOpen(false), fontSize(16) {
        rectanglePosition = {static_cast<float>(x), static_cast<float>(y), 0, 0};
        rectangleResize();
    }
};

template <typename T>
DropdownMenu(T*, int, int) -> DropdownMenu<T>;

template <typename T>
DropdownMenuItem(std::string, T) -> DropdownMenuItem<T>;