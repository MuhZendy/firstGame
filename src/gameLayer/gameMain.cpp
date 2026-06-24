#include <math.h>

#include "assetManager.h"
#include "raylib.h"
#include "imgui.h"
#include "gameMain.h"
#include "gameMap.h"
#include "helpers.h"
#include "randomStuff.h"
struct GameState {
    // Add game state variables here
    GameMap gameMap;
    Camera2D camera;
} gameState;

AssetManager assetManager;

bool initGame() {
    // Initialize game resources here
    assetManager.loadAll();

    gameState.gameMap.create(700, 500); // Example: create a 700x500 game map
    for (int y = 0; y < gameState.gameMap.height; ++y) {
        for (int x = 0; x < gameState.gameMap.width; ++x) {
            if (y > 20) gameState.gameMap.getBlock(x, y).id = Block::dirt;
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

    static int selected_index = 0;
    ImGui::Begin("Block Selecotor");
    ImGui::Combo("Block Type", &selected_index, Block::getNames(), Block::BLOCKS_COUNT);
    ImGui::End();

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
            block->id = selected_index;
        }
    }

    gameState.camera.offset = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
    BeginMode2D(gameState.camera);

    Vector2 topLeft = GetScreenToWorld2D({ 0, 0 }, gameState.camera);
    Vector2 bottomRight = GetScreenToWorld2D({ (float)GetScreenWidth(), (float)GetScreenHeight() }, gameState.camera);

    int startX = std::max(0, (int)std::floor(topLeft.x));
    int startY = std::max(0, (int)std::floor(topLeft.y));
    int endX = std::min(gameState.gameMap.width - 1, (int)std::ceil(bottomRight.x));
    int endY = std::min(gameState.gameMap.height - 1, (int)std::ceil(bottomRight.y));

    for (int y = startY; y <= endY; ++y) {
        for (int x = startX; x <= endX; ++x) {
            int blockVariation = (x + y) % 4; // Example: 4 variations for each block type
            Block& block = gameState.gameMap.getBlock(x, y);
            if (block.id == Block::woodLog) {
                Block* leftBlock = gameState.gameMap.getBlockSafe(x - 1, y);
                Block* rightBlock = gameState.gameMap.getBlockSafe(x + 1, y);
                Block* topBlock = gameState.gameMap.getBlockSafe(x, y - 1);
                Block* bottomBlock = gameState.gameMap.getBlockSafe(x, y + 1);

                int logId = 0;
                
                bool leftLeaf = (leftBlock && leftBlock->id == Block::leaves);
                bool rightLeaf = (rightBlock && rightBlock->id == Block::leaves);
                bool topLeaf = (topBlock && topBlock->id == Block::leaves);
                bool topLog = (topBlock && topBlock->id == Block::woodLog);
                bool bottomLog = (bottomBlock && bottomBlock->id == Block::woodLog);

                if (topLeaf) logId = 5; // Top has leaves
                else if (leftLeaf && rightLeaf) logId = 1; // Both sides have leaves
                else if (leftLeaf) logId = 3; // Left side has leaves
                else if (rightLeaf) logId = 2; // Right side has leaves
                else if (!topLog && !bottomLog) logId = 7; // Both sides have no logs
                else if (!topLog) logId = 6; // Top has no log
                else if (!bottomLog) logId = 4; // Bottom has no log
                else logId = 0; // No leaves but have logs on both sides

                Rectangle textureUV = getTextureAtlasUV(logId, blockVariation, 32, 32); // Assuming wood log texture is at (0, 0) in the atlas
                DrawTexturePro(assetManager.treeTexture, textureUV, 
                    { (float)x, (float)y, 1.0f, 1.0f }, {}, 0, WHITE);
            }
            else if (block.id != Block::air) {
                Rectangle textureUV = getTextureAtlasUV(block.id, blockVariation, 32, 32); // Assuming each block texture is 32x32 pixels
                DrawTexturePro(assetManager.texture, textureUV, 
                    { (float)x, (float)y, 1.0f, 1.0f }, {}, 0, WHITE);
            }
        }
    }

    DrawTexturePro(assetManager.frame, {0, 0, (float)assetManager.frame.width, (float)assetManager.frame.height}, 
        {(float)blockX, (float)blockY, 1.0f, 1.0f}, {}, 0, WHITE);

    EndMode2D();

    DrawFPS(10, 10);

    return true;
}

void closeGame() {
    // Free game resources here
}