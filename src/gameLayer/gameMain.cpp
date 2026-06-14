#include "raylib.h"
#include "gameMain.h"

struct GameState {
    // Add game state variables here
    float playerX = 100.0f;
    float playerY = 100.0f;
} gameState;

bool initGame() {
    // Initialize game resources here
    return true; // Return false if initialization fails
}

bool updateGame() {
    // Update game logic here
    // Return false if the game should be closed
    float deltaTime = GetFrameTime();
    if (IsKeyDown(KEY_RIGHT)) gameState.playerX += 200.0f * deltaTime;
    if (IsKeyDown(KEY_LEFT)) gameState.playerX -= 200.0f * deltaTime;
    if (IsKeyDown(KEY_DOWN)) gameState.playerY += 200.0f * deltaTime;
    if (IsKeyDown(KEY_UP)) gameState.playerY -= 200.0f * deltaTime;

    DrawRectangle(gameState.playerX, gameState.playerY, 50, 50, Color{ 255, 255, 255, 255 });

    return true;
}

void closeGame() {
    // Free game resources here
}