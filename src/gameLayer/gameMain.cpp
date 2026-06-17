#include "assetManager.h"
#include "raylib.h"
#include "gameMain.h"

struct GameState {
    // Add game state variables here
} gameState;

AssetManager assetManager;

bool initGame() {
    // Initialize game resources here
    assetManager.loadAll();
    return true; // Return false if initialization fails
}

bool updateGame() {
    // Update game logic here
    // Return false if the game should be closed
    float deltaTime = GetFrameTime();
    if (deltaTime > 0.1f) deltaTime = 0.1f; // Cap deltaTime to avoid big jumps

    DrawTexturePro(assetManager.dirt, { 0, 0, (float)assetManager.dirt.width, (float)assetManager.dirt.height }, 
        { 50, 50, 100, 100 }, {}, 0, WHITE); // Example of drawing the dirt texture at the top-left corner

    return true;
}

void closeGame() {
    // Free game resources here
}