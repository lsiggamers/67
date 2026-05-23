#include "globalFunc.hpp"
#include "globalSettings.hpp"
#include "raylib.h"

#include <vector>

static int botNum, humanNum;

static std::vector<int> botNumbers;


static void startReset() {
    botNum = randomInt(1, 100);
    humanNum = randomInt(1,100);
}


static void botSelect() {

}


static void humanSelect() {

}


static void findWinner() {
    
}


void runHigherOrLower() {
    while (!WindowShouldClose() && !globalShutoff) {
        humanSelect();
        botSelect();
        findWinner();
    }
}