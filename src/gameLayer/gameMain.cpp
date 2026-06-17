#include "assetManager.h"
#include "raylib.h"
#include "gameMain.h"
#include "gameMap.h"

struct GameState {
    // Add game state variables here
    GameMap gameMap;
} gameState;

AssetManager assetManager;

bool initGame() {
    // Initialize game resources here
    assetManager.loadAll();

    gameState.gameMap.create(10, 10); // Example: create a 10x10 game map
    gameState.gameMap.getBlock(0, 0).id = Block::DIRT;
    gameState.gameMap.getBlock(1, 1).id = Block::DIRT;
    gameState.gameMap.getBlock(2, 2).id = Block::DIRT;
    gameState.gameMap.getBlock(3, 3).id = Block::DIRT;
    gameState.gameMap.getBlock(4, 4).id = Block::DIRT;

    return true; // Return false if initialization fails
}

bool updateGame() {
    // Update game logic here
    // Return false if the game should be closed
    float deltaTime = GetFrameTime();
    if (deltaTime > 0.1f) deltaTime = 0.1f; // Cap deltaTime to avoid big jumps

    for (int y = 0; y < gameState.gameMap.height; ++y) {
        for (int x = 0; x < gameState.gameMap.width; ++x) {
            Block& block = gameState.gameMap.getBlock(x, y);
            if (block.id != Block::AIR) {
                float size = 50.0f; // Size of the block to draw
                float posX = x * size;
                float posY = y * size;
                DrawTexturePro(assetManager.dirt, { 0, 0, (float)assetManager.dirt.width, (float)assetManager.dirt.height }, 
                    { posX, posY, size, size }, {}, 0, WHITE);
            }
        }
    }

    return true;
}

void closeGame() {
    // Free game resources here
}