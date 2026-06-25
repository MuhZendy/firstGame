#include <FastNoise/FastNoise.h>
#include "worldGenerator.h"
#include "randomStuff.h"

void generateWorld(GameMap& gameMap, int seed) {
    int width = gameMap.width;
    int height = gameMap.height;

    int dirtHeight = height / 4; // Example: Half the height is dirt

    std::ranlux24_base rng(seed); // Random number generator
    int previousHeight = dirtHeight; // Start with the initial dirt height

    // Example: Fill the bottom half with dirt and the top half with air
    for (int x = 0; x < width; ++x) {

        int offset = getRandomInt(rng, -1, 1); // Random offset for terrain variation
        int adjustedDirtHeight = previousHeight + offset;
        previousHeight = adjustedDirtHeight;

        int stoneHeight = adjustedDirtHeight + 10;

        for (int y = 0; y < height; ++y) {
            if (y == adjustedDirtHeight) {
                gameMap.getBlock(x, y).id = Block::grassBlock; // Grass block at the surface
            } else if (y > adjustedDirtHeight && y <= stoneHeight) {
                gameMap.getBlock(x, y).id = Block::dirt;
            } else if (y > stoneHeight) {
                gameMap.getBlock(x, y).id = Block::stone;
            }
        }
    }
}