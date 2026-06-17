#pragma once
#include <cstdint>

struct Block {
    enum {
        AIR = 0,
        DIRT = 1,
        STONE = 2,
        // Add more block types here
        BLOCKS_COUNT
    };

    uint16_t id; // Block type ID
    // Add more block properties here (e.g., durability, texture index, etc.)
};