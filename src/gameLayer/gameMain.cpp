#include "raylib.h"
#include "gameMain.h"

bool initGame() {
    // Initialize game resources here
    return true; // Return false if initialization fails
}

bool updateGame() {
    // Update game logic here
    // Return false if the game should be closed
    DrawRectangle(150, 150, 200, 150, Color{ 0, 121, 241, 127 });
    DrawRectangle(100, 100, 200, 150, Color{ 230, 41, 55, 127 });

    return true;
}

void closeGame() {
    // Free game resources here
}