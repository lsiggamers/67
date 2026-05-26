#include "globalFunc.hpp"
#include "globalSettings.hpp"
#include "raylib.h"
#include "dropDown.hpp"

#include <vector>

static int botNum, humanNum;

static std::vector<int> botNumbers;

static DropdownMenu testMenu(&botNum, 10, 10);

static DropdownMenuItem testItem1("Option 1", 1);
static DropdownMenuItem testItem2("Option 2", 2);

static void input() {

}

static void startReset() {
    botNum = randomInt(1, 100);
    humanNum = randomInt(1,100);
}


static void botSelect() {
    BeginDrawing();
    testMenu.draw(10, 10, 20, BLACK);
    EndDrawing();
}


static void humanSelect() {

}


static void findWinner() {
    
}


void runHigherOrLower() {
    testMenu.appendOption(testItem1);
    testMenu.appendOption(testItem2);
    while (!WindowShouldClose() && !globalShutoff) {
        //humanSelect();
        botSelect();
        //findWinner();
    }
}