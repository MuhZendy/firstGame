#include <math.h>

#include "assetManager.h"
#include "raylib.h"
#include "gameMain.h"
#include "gameMap.h"
#include "helpers.h"
struct GameState {
    // Add game state variables here
    GameMap gameMap;
    Camera2D camera;
} gameState;

AssetManager assetManager;

bool initGame() {
    // Initialize game resources here
    assetManager.loadAll();

    gameState.gameMap.create(30, 30); // Example: create a 30x30 game map
    for (int y = 0; y < gameState.gameMap.height; ++y) {
        for (int x = 0; x < gameState.gameMap.width; ++x) {
            if ((x - 10)*(x - 10) + (y - 10)*(y - 10) < 25) gameState.gameMap.getBlock(x, y).id = Block::pearl; // Create a circular dirt area
        }
    }

    gameState.camera.target = { 0, 0 };
    gameState.camera.rotation = 0.0f;
    gameState.camera.zoom = 100.0f;

    return true; // Return false if initialization fails
}

bool updateGame() {
    // Update game logic here
    // Return false if the game should be closed
    ClearBackground({75, 75, 150, 255});

    float deltaTime = GetFrameTime();
    if (deltaTime > 0.1f) deltaTime = 0.1f; // Cap deltaTime to avoid big jumps

    if (IsKeyDown(KEY_W)) gameState.camera.target.y -= 7.0f * deltaTime;
    if (IsKeyDown(KEY_S)) gameState.camera.target.y += 7.0f * deltaTime;
    if (IsKeyDown(KEY_A)) gameState.camera.target.x -= 7.0f * deltaTime;
    if (IsKeyDown(KEY_D)) gameState.camera.target.x += 7.0f * deltaTime;

    Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), gameState.camera);
    int blockX = (int)std::floor(worldPos.x);
    int blockY = (int)std::floor(worldPos.y);

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Block* block = gameState.gameMap.getBlockSafe(blockX, blockY);
        if (block) {
            *block = {};
        }
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        Block* block = gameState.gameMap.getBlockSafe(blockX, blockY);
        if (block) {
            block->id = Block::dirt;
        }
    }

    gameState.camera.offset = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
    BeginMode2D(gameState.camera);

    for (int y = 0; y < gameState.gameMap.height; ++y) {
        for (int x = 0; x < gameState.gameMap.width; ++x) {
            Block& block = gameState.gameMap.getBlock(x, y);
            if (block.id != Block::air) {
                Rectangle textureUV = getTextureAtlasUV(block.id, 0, 32, 32); // Assuming each block texture is 32x32 pixels
                DrawTexturePro(assetManager.texture, textureUV, 
                    { (float)x, (float)y, 1.0f, 1.0f }, {}, 0, WHITE);
            }
        }
    }

    DrawTexturePro(assetManager.frame, {0, 0, (float)assetManager.frame.width, (float)assetManager.frame.height}, 
        {(float)blockX, (float)blockY, 1.0f, 1.0f}, {}, 0, WHITE);

    EndMode2D();

    return true;
}

void closeGame() {
    // Free game resources here
}