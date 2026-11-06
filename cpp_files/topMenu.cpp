#include "topMenu.hpp"
#include "batteryMenu.hpp"
#include "globalSettings.hpp"

#include <thread>

int topMenuSpot;

int topMenuPadding = 5;

void topMenu() {
    topMenuSpot = topMenuPadding;
    drawBatteryMenu();
    if (developerMode) {DrawRectangle(windowSize.x - topMenuSpot, 0, 5, 5, secondaryColor);}
}