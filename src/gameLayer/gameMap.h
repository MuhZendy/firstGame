#pragma once
#include <vector>
#include "blocks.h"

struct GameMap {
    int width;
    int height;
    std::vector<Block> mapData; // 1D array representing the 2D map (row-major order)

    void create(int w, int h);
    
    Block& getBlock(int x, int y);

    Block* getBlockSafe(int x, int y); // Returns a pointer to the block at (x, y) or a default block if out of bounds
};