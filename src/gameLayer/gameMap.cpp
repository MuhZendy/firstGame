#include "gameMap.h"
#include "asserts.h"

void GameMap::create(int w, int h) {
    width = w;
    height = h;
    mapData.resize(width * height);
    // Initialize the map with default blocks (e.g., AIR)
    for (Block& block : mapData) {
        block = {};
    }
}

Block& GameMap::getBlock(int x, int y) {
    permaAssertCommentDevelopement(mapData.size() == width * height, "getBlock: Map data size mismatch");
    permaAssertCommentDevelopement(x >= 0 && x < width && y >= 0 && y < height, "getBlock: Coordinates out of bounds");
    return mapData[y * width + x];
}

Block* GameMap::getBlockSafe(int x, int y) {
    permaAssertCommentDevelopement(mapData.size() == width * height, "getBlockSafe: Map data size mismatch");
    if (x < 0 || x >= width || y < 0 || y >= height)
        return nullptr; // Out of bounds, return nullptr
    return &mapData[y * width + x];
}